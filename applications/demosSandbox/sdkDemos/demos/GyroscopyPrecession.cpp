/* Copyright (c) <2003-2016> <Newton Game Dynamics>
* 
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely
*/


#include "toolbox_stdafx.h"
#include "SkyBox.h"
#include "DemoEntityManager.h"
#include "DemoCamera.h"
#include "PhysicsUtils.h"
#include "DemoMesh.h"
#include "OpenGlUtil.h"


static void ZeroGravityForce(const NewtonBody* body, dFloat timestep, int threadIndex)
{
/*
	dMatrix inertia;
	dVector omega;

	NewtonBodyGetInertiaMatrix(body, &inertia[0][0]);
	NewtonBodyGetOmega(body, &omega[0]);
	dVector L(inertia.RotateVector(omega));
	dFloat e = L.DotProduct3(omega) * 0.5f;

//dMatrix ii(dGetIdentityMatrix());
//dMatrix matrix(dGetIdentityMatrix());
//NewtonBodyGetMatrix(body, &matrix[0][0]);
//NewtonBodyGetMass(body, &omega.m_w, &ii[0][0], &ii[1][1], &ii[2][2]);
//ii = matrix.Inverse() * ii * matrix;

	dTrace(("E=%f  L(%f %f %f) W(%f %f %f)\n", e, L.m_x, L.m_y, L.m_z, omega.m_x, omega.m_y, omega.m_z));
*/
}


static NewtonBody* DzhanibekovEffect(DemoEntityManager* const scene, const dVector& posit, dVector omega, dFloat radius, dFloat lenght)
{
	NewtonWorld* const world = scene->GetNewton();

	dMatrix offset(dYawMatrix (90.0f * dDegreeToRad));

	dFloat shortLength = lenght * 0.3f;
	offset.m_posit.m_z = radius * 0.75f + shortLength * 0.5f;
	NewtonCollision* const longCylinder = NewtonCreateCylinder(world, radius, radius, lenght, 0, NULL);
	NewtonCollision* const shortCylinder = NewtonCreateCylinder(world, radius, radius, shortLength, 0, &offset[0][0]);

	NewtonCollision* const dzhanibekovShape = NewtonCreateCompoundCollision(world, 0);
	NewtonCompoundCollisionBeginAddRemove(dzhanibekovShape);

	NewtonCompoundCollisionAddSubCollision(dzhanibekovShape, longCylinder);
	NewtonCompoundCollisionAddSubCollision(dzhanibekovShape, shortCylinder);
	NewtonCompoundCollisionEndAddRemove(dzhanibekovShape);

	dMatrix matrix(dGetIdentityMatrix());
	matrix.m_posit = posit;
	matrix.m_posit.m_x += lenght * 0.5f;
	matrix.m_posit.m_w = 1.0f;

	DemoMesh* const geometry = new DemoMesh("primitive", dzhanibekovShape, "smilli.tga", "smilli.tga", "smilli.tga");
	NewtonBody* const dzhanibekovBody = CreateSimpleSolid(scene, geometry, 10.0f, matrix, dzhanibekovShape, 0);

	NewtonBodySetMassProperties(dzhanibekovBody, 10.0f, dzhanibekovShape);

	dFloat m, x, y, z;
	NewtonBodyGetMass(dzhanibekovBody, &m, &x, &y, &z);
//NewtonBodySetMassMatrix(dzhanibekovBody, m, x, x, x);

	NewtonBodySetOmega(dzhanibekovBody, &omega[0]);

	dVector damp(0.0f);
	NewtonBodySetLinearDamping(dzhanibekovBody, 0.0f);
	NewtonBodySetAngularDamping(dzhanibekovBody, &damp[0]);
	NewtonBodySetForceAndTorqueCallback(dzhanibekovBody, ZeroGravityForce);

	geometry->Release();
	NewtonDestroyCollision(dzhanibekovShape);
	NewtonDestroyCollision(longCylinder);
	NewtonDestroyCollision(shortCylinder);

	return dzhanibekovBody;
}


static NewtonBody* TorqueFreePreccesion(DemoEntityManager* const scene, const dVector& posit, dFloat omega, dFloat radio, dFloat precessingAngle)
{
	NewtonWorld* const world = scene->GetNewton();

	dMatrix offset(dRollMatrix(90.0f * dDegreeToRad));
	NewtonCollision* const ballShape = NewtonCreateCylinder(world, radio, radio, radio * 0.25f, 0, &offset[0][0]);
	//NewtonCollision* const ballShape = NewtonCreateSphere(world, radio, 0, NULL);
	//NewtonCollisionSetScale(ballShape, 1.0f, 0.5f, 1.0f);

	dMatrix matrix(dGetIdentityMatrix());
	matrix.m_posit = posit;
	matrix.m_posit.m_w = 1.0f;

	DemoMesh* const geometry = new DemoMesh("primitive", ballShape, "smilli.tga", "smilli.tga", "smilli.tga");
	NewtonBody* const ball = CreateSimpleSolid(scene, geometry, 10.0f, matrix, ballShape, 0);

	NewtonBodySetMassProperties(ball, 10.0f, ballShape);

	dFloat m, Ixx, Iyy, Izz;
	NewtonBodyGetMass(ball, &m, &Ixx, &Iyy, &Izz);

	omega = 2.0f;
	dVector angVelocity (0.0f, omega, 0.0f, 0.0f);
	angVelocity = dPitchMatrix(15.0f * dDegreeToRad).RotateVector(angVelocity);

	NewtonBodySetOmega(ball, &angVelocity[0]);

	dVector damp(0.0f);
	NewtonBodySetLinearDamping(ball, 0.0f);
	NewtonBodySetAngularDamping(ball, &damp[0]);
	NewtonBodySetForceAndTorqueCallback(ball, ZeroGravityForce);

	geometry->Release();
	NewtonDestroyCollision(ballShape);

	return ball;
}


static NewtonBody* CreateFryWheel (DemoEntityManager* const scene, const dVector& posit, dFloat speed, dFloat radius, dFloat lenght)
{
	NewtonWorld* const world = scene->GetNewton();

	dMatrix offset(dGetIdentityMatrix());
	offset.m_posit.m_x = lenght * 0.5f;
	dFloat smallRadius = 0.0625f;
	NewtonCollision* const rod = NewtonCreateCapsule(world, smallRadius * 0.5f, smallRadius * 0.5f, lenght, 0, NULL);
	NewtonCollision* const wheel = NewtonCreateCylinder(world, radius, radius, 0.125f, 0, &offset[0][0]);

	NewtonCollision* const flyWheelShape = NewtonCreateCompoundCollision(world, 0);
	NewtonCompoundCollisionBeginAddRemove(flyWheelShape);

	NewtonCompoundCollisionAddSubCollision(flyWheelShape, rod);
	NewtonCompoundCollisionAddSubCollision(flyWheelShape, wheel);
	NewtonCompoundCollisionEndAddRemove(flyWheelShape);

	dMatrix matrix(dGetIdentityMatrix());
	matrix.m_posit = posit;
	matrix.m_posit.m_x += lenght * 0.5f;
	matrix.m_posit.m_w = 1.0f;

	DemoMesh* const geometry = new DemoMesh("primitive", flyWheelShape, "smilli.tga", "smilli.tga", "smilli.tga");
	NewtonBody* const wheelBody = CreateSimpleSolid(scene, geometry, 10.0f, matrix, flyWheelShape, 0);
	NewtonBodySetMassProperties(wheelBody, 10.0f, flyWheelShape);

	dFloat m;
	dFloat x;
	dFloat y;
	dFloat z;
	NewtonBodyGetMass(wheelBody, &m, &x, &y, &z);

	dVector damp(0.0f);
	NewtonBodySetLinearDamping(wheelBody, 0.0f);
	NewtonBodySetAngularDamping(wheelBody, &damp[0]);

	dVector omega(speed, 0.0f, 0.0f);
	NewtonBodySetOmega(wheelBody, &omega[0]);

	matrix.m_posit.m_x -= lenght * 0.5f;

	geometry->Release();
	NewtonDestroyCollision(flyWheelShape);
	NewtonDestroyCollision(wheel);
	NewtonDestroyCollision(rod);

	return wheelBody;
}


static void CreateBicycleWheel(DemoEntityManager* const scene, const dVector& posit, dFloat speed, dFloat radius, dFloat lenght, dFloat tiltAnsgle)
{
	NewtonBody* const flyWheel = CreateFryWheel(scene, posit, speed, radius, lenght);

	dMatrix matrix(dGetIdentityMatrix());
	NewtonBodyGetMatrix(flyWheel, &matrix[0][0]);


	dVector omega(speed, 0.0f, 0.0f);
	dMatrix rotation(dRollMatrix(tiltAnsgle * dDegreeToRad));
	NewtonBodyGetOmega(flyWheel, &omega[0]);
	omega = rotation.RotateVector(omega);
	matrix = rotation * matrix;
	NewtonBodySetMatrix(flyWheel, &matrix[0][0]);
	NewtonBodySetOmega(flyWheel, &omega[0]);

	matrix.m_posit -= matrix.m_front.Scale (lenght * 0.5f);
	new dCustomBallAndSocket(matrix, flyWheel, NULL);
}

static void PrecessingTop(DemoEntityManager* const scene, const dVector& posit)
{
	NewtonBody* const top = CreateFryWheel(scene, posit, 100.0f, 0.5f, 0.3f);

	dMatrix matrix;
	dVector omega;

	dMatrix rotation(dRollMatrix(75.0f * dDegreeToRad));
	
	NewtonBodyGetOmega(top, &omega[0]);
	NewtonBodyGetMatrix(top, &matrix[0][0]);

	omega = rotation.RotateVector(omega);
	matrix = rotation * matrix;

	NewtonBodySetMatrix(top, &matrix[0][0]);
	NewtonBodySetOmega(top, &omega[0]);
}


void GyroscopyPrecession(DemoEntityManager* const scene)
{
	scene->CreateSkyBox();
	dMatrix offsetMatrix(dGetIdentityMatrix());

	CreateLevelMesh(scene, "flatPlane.ngd", 1);

	NewtonWorld* const world = scene->GetNewton();
	int defaultMaterialID = NewtonMaterialGetDefaultGroupID(world);
	NewtonMaterialSetDefaultFriction(world, defaultMaterialID, defaultMaterialID, 1.0f, 1.0f);
	NewtonMaterialSetDefaultElasticity(world, defaultMaterialID, defaultMaterialID, 0.1f);

	// a body with an axis of symmetry should precesses 
	TorqueFreePreccesion(scene, dVector(0.0f, 3.0f, -10.0f, 1.0f), 10.0f, 1.0f, 10.0f);

	// should spins very slowly, with a tilt angle of 45 degrees
	CreateBicycleWheel(scene, dVector(0.0f, 3.0f, -8.0f, 1.0f), 100.0f, 0.6f, 0.3f, 30.0f);

	// spin twice as fast
	CreateBicycleWheel(scene, dVector(0.0f, 3.0f, -6.0f, 1.0f), 50.0f, 0.6f, 0.3f, 0.0f);

	// should spins very slowly
	CreateBicycleWheel(scene, dVector(0.0f, 3.0f, -4.0f, 1.0f), 100.0f, 0.6f, 0.3f, 0.0f);

	// should just flops
	CreateBicycleWheel(scene, dVector(0.0f, 3.0f, -2.0f, 1.0f), 0.0f, 0.6f, 0.3f, 0.0f);

	// intermediate Axis Theorem
	DzhanibekovEffect(scene, dVector(0.0f, 3.0f,  0.0f, 1.0f), dVector (0.01f, 0.01f, 20.0f), 0.25f, 2.0f);
	DzhanibekovEffect(scene, dVector(0.0f, 3.0f,  2.0f, 1.0f), dVector (0.01f, 20.0f, 0.01f), 0.25f, 2.0f);
	DzhanibekovEffect(scene, dVector(0.0f, 3.0f,  4.0f, 1.0f), dVector (20.0f, 0.01f, 0.01f), 0.25f, 2.0f);

	// test this only happens is there a residual angular velocity on the other two axis
	// for perfectly axis aligned velocity the the body is on unstable equilibrium and should not flip.
	DzhanibekovEffect(scene, dVector(3.0f, 3.0f,  6.0f, 1.0f), dVector (0.0f, 0.0f, 15.0f), 0.25f, 2.0f);

	// test a different angular velocity
	DzhanibekovEffect(scene, dVector(3.0f, 3.0f,  8.0f, 1.0f), dVector (0.01f, 0.01f, 15.0f), 0.25f, 2.0f);

	// place a toy top
	const int topsCount = 4;
	for (int i = 0; i < topsCount; i ++) {
		for (int j = 0; j < topsCount; j ++) {
	//			PrecessingTop(scene, dVector(-2.0f * i - 2.0f, 3.0f, 2.0f * j - 2.0f, 1.0f));
		}
	}


	// place camera into position
	dMatrix camMatrix(dGetIdentityMatrix());
	dQuaternion rot(camMatrix);
	dVector origin(-15.0f, 2.0f, 0.0f, 0.0f);
	scene->SetCameraMatrix(rot, origin);
}


