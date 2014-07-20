/* Copyright (c) <2009> <Newton Game Dynamics>
* 
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely
*/


// most the work for the tire model comes from this paper
// http://code.eng.buffalo.edu/dat/sites/tire/tire.html 
// I do not really use their Simplified Tire Model Equations, 
// instead I use the explanation of the empirical tire model and use the slip and 
// side slip coefficients to determine friction limits from piecewise normalized tire force curves.
// I use these friction forces in a full analytical Lagrangian rigid body model of the vehicle. 
// Surprisingly the results are more realistic than I would expect.
//
// the only time the empirical tire model fall far from realistic behaviors 
// is when the tire liner velocity at the cent is too close to zero.
// but for this I case is handles with the constraints joints that keep the car stable.
// in fact the constraint joint effect is negligible so it can be left on during the entire simulation.
// when the car is moving a at any speed the constraint joint act a dry dolling friction.

// replaced the tire model base of Pacejkas (which seems to always produce a very poor tire behavior) 
// with the the method use in this paper 
// http://www.ricblues.nl/techniek/Technisch%20Specialist%2093430/6%20Remgedrag%20ABS%20weggedrag/Carsim%20-%20remsimulatieprogramma/Handleiding%20carsim.pdf
// basically th replace the Pajecka equation with the with the two series expansions 
// f = x - |x| * x / 3 + x * x * x / 27
// T = x - |x| * x + x * x * x / 3 - |x| * x * x * x / 27 
// they also have a better tire fristion modle that teh naive friction cilcle projection

// NewtonCustomJoint.cpp: implementation of the NewtonCustomJoint class.
//
//////////////////////////////////////////////////////////////////////
#include <CustomJointLibraryStdAfx.h>
#include <CustomJoint.h>
#include <CustomVehicleControllerJoint.h>
#include <CustomVehicleControllerManager.h>
#include <CustomVehicleControllerComponent.h>
#include <CustomVehicleControllerBodyState.h>

#define VEHICLE_CONTROLLER_MAX_JOINTS								32
#define VEHICLE_CONTROLLER_MAX_JACOBIANS_PAIRS						(VEHICLE_CONTROLLER_MAX_JOINTS * 4)
#define VEHICLE_PSD_DAMP_TOL										dFloat(1.0e-4f)
#define VEHICLE_SIDESLEP_NORMALIZED_FRICTION_AT_MAX_SLIP_ANGLE		dFloat(0.75f)
#define VEHICLE_SIDESLEP_NORMALIZED_FRICTION_AT_MAX_SIDESLIP_RATIO	dFloat(0.95f)

#if 0
void CustomVehicleController::UpdateTireTransforms ()
{
	for (TireList::CustomListNode* node = m_tireList.GetFirst(); node; node = node->GetNext()) {
		TireBodyState* const tire = &node->GetInfo();
		tire->UpdateTransform();
	}
}
#endif



class CustomVehicleController::dWeightDistibutionSolver: public dSymmetricBiconjugateGradientSolve
{
	public:
	dWeightDistibutionSolver ()
		:dSymmetricBiconjugateGradientSolve()
		,m_count(0)
	{

	}

	virtual void MatrixTimeVector (dFloat64* const out, const dFloat64* const v) const
	{
		CustomVehicleControllerJoint::dJacobian invMassJacobians [VEHICLE_CONTROLLER_MAX_JOINTS];
		for (int i = 0; i < m_count; i ++) {
			out[i] = m_diagRegularizer[i] * v[i];
			invMassJacobians[i].m_linear = m_invMassJacobians[i].m_linear.Scale (dFloat(v[i]));
			invMassJacobians[i].m_angular = m_invMassJacobians[i].m_angular.Scale (dFloat(v[i]));
		}

		for (int i = 0; i < m_count; i ++) {
			out[i] = invMassJacobians[i].m_linear % m_jacobians[i].m_linear + invMassJacobians[i].m_angular % m_jacobians[i].m_angular;
		}
	}

	virtual bool InversePrecoditionerTimeVector (dFloat64* const out, const dFloat64* const v) const
	{
		for (int i = 0; i < m_count; i ++) {
			out[i] = v[i] * m_invDiag[i];
		}
		return true;
	}

	CustomVehicleControllerJoint::dJacobian m_jacobians [VEHICLE_CONTROLLER_MAX_JOINTS];
	CustomVehicleControllerJoint::dJacobian m_invMassJacobians [VEHICLE_CONTROLLER_MAX_JOINTS];
	dFloat m_invDiag[VEHICLE_CONTROLLER_MAX_JOINTS];
	dFloat m_diagRegularizer[VEHICLE_CONTROLLER_MAX_JOINTS];

	int m_count;
};


CustomVehicleControllerManager::CustomVehicleControllerManager(NewtonWorld* const world)
	:CustomControllerManager<CustomVehicleController> (world, VEHICLE_PLUGIN_NAME)
{
}

CustomVehicleControllerManager::~CustomVehicleControllerManager()
{
}

void CustomVehicleControllerManager::DestroyController (CustomVehicleController* const controller)
{
	controller->Cleanup();
	CustomControllerManager<CustomVehicleController>::DestroyController(controller);
}


CustomVehicleController* CustomVehicleControllerManager::CreateVehicle (NewtonCollision* const chassisShape, const dMatrix& vehicleFrame, dFloat mass, const dVector& gravityVector)
{
	CustomVehicleController* const controller = CreateController();
	controller->Init(chassisShape, vehicleFrame, mass, gravityVector);
	return controller;
}




void CustomVehicleController::Init (NewtonCollision* const chassisShape, const dMatrix& vehicleFrame, dFloat mass, const dVector& gravityVector)
{
	m_finalized = false;
	CustomVehicleControllerManager* const manager = (CustomVehicleControllerManager*) GetManager(); 
	NewtonWorld* const world = manager->GetWorld(); 

	// create a compound collision 	
	NewtonCollision* const vehShape = NewtonCreateCompoundCollision(world, 0);
	NewtonCompoundCollisionBeginAddRemove(vehShape);

	// if the shape is a compound collision ass all the pieces one at a time
	int shapeType = NewtonCollisionGetType (chassisShape);
	if (shapeType == SERIALIZE_ID_COMPOUND) {
		dAssert (0);
	} else {
		dAssert ((shapeType == SERIALIZE_ID_CONVEXHULL) || (shapeType == SERIALIZE_ID_BOX));
		NewtonCompoundCollisionAddSubCollision (vehShape, chassisShape);
	}
	NewtonCompoundCollisionEndAddRemove (vehShape);	

	// create the rigid body for this vehicle
	dMatrix locationMatrix (GetIdentityMatrix());
	m_body = NewtonCreateDynamicBody(world, vehShape, &locationMatrix[0][0]);

	// set vehicle mass, inertia and center of mass
	NewtonBodySetMassProperties (m_body, mass, vehShape);

	// set linear and angular drag to zero
	dVector drag(0.0f, 0.0f, 0.0f, 0.0f);
	NewtonBodySetLinearDamping(m_body, 0);
	NewtonBodySetAngularDamping(m_body, &drag[0]);

	// destroy the collision help shape
	NewtonDestroyCollision (vehShape);

	// initialize vehicle internal components
	NewtonBodyGetCentreOfMass (m_body, &m_chassisState.m_com[0]);

	m_chassisState.m_gravity = gravityVector;
	m_chassisState.m_gravityMag = dSqrt (gravityVector % gravityVector);
	m_chassisState.Init(this, vehicleFrame);

	m_stateList.Append(&m_staticWorld);
	m_stateList.Append(&m_chassisState);

	// create the normalized size tire shape
	m_tireCastShape = NewtonCreateChamferCylinder(world, 0.5f, 1.0f, 0, NULL);

	// initialize all components to empty
	m_engine = NULL;
	m_brakes = NULL;
	m_steering = NULL;
	m_handBrakes = NULL;

	SetDryRollingFrictionTorque (100.0f/4.0f);
	SetAerodynamicsDownforceCoefficient (0.5f * dSqrt (gravityVector % gravityVector), 60.0f * 0.447f);
}


void CustomVehicleController::Cleanup()
{
	SetBrakes(NULL);
	SetEngine(NULL);
	SetSteering(NULL);
	SetHandBrakes(NULL);
	NewtonDestroyCollision(m_tireCastShape);
}

const CustomVehicleControllerBodyStateChassis& CustomVehicleController::GetChassisState () const
{
	return m_chassisState;
}

dFloat CustomVehicleController::GetAerodynamicsDowforceCoeficient () const
{
	return m_chassisState.GetAerodynamicsDowforceCoeficient();
}

void CustomVehicleController::SetAerodynamicsDownforceCoefficient (dFloat maxDownforceInGravity, dFloat topSpeed)
{
	m_chassisState.SetAerodynamicsDownforceCoefficient (maxDownforceInGravity, topSpeed);
}


void CustomVehicleController::SetDryRollingFrictionTorque (dFloat dryRollingFrictionTorque)
{
	m_chassisState.SetDryRollingFrictionTorque (dryRollingFrictionTorque);
}

dFloat CustomVehicleController::GetDryRollingFrictionTorque () const
{
	return m_chassisState.GetDryRollingFrictionTorque();
}


CustomVehicleControllerBodyStateTire* CustomVehicleController::GetFirstTire () const
{
	return m_tireList.GetFirst() ? &m_tireList.GetFirst()->GetInfo() : NULL;
}

CustomVehicleControllerBodyStateTire* CustomVehicleController::GetNextTire (CustomVehicleControllerBodyStateTire* const tire) const
{
	TireList::dListNode* const tireNode = m_tireList.GetNodeFromInfo(*tire);
	return tireNode->GetNext() ? &tireNode->GetNext()->GetInfo() : NULL;
}


void CustomVehicleController::SetCenterOfGravity(const dVector& comRelativeToGeomtriCenter)
{
	dMatrix localFrame (m_chassisState.m_localFrame);
	m_chassisState.m_comOffset = comRelativeToGeomtriCenter;
	m_chassisState.Init(this, localFrame);
}


CustomVehicleControllerBodyStateTire* CustomVehicleController::AddTire (const CustomVehicleControllerBodyStateTire::TireCreationInfo& tireInfo)
{
	TireList::dListNode* const tireNode = m_tireList.Append();
	CustomVehicleControllerBodyStateTire& tire = tireNode->GetInfo();
	tire.Init(this, tireInfo);

	m_stateList.Append(&tire);
	return &tireNode->GetInfo();
}


CustomVehicleControllerComponentEngine* CustomVehicleController::GetEngine() const
{
	return m_engine;
}

CustomVehicleControllerComponentSteering* CustomVehicleController::GetSteering() const
{
	return m_steering;
}

CustomVehicleControllerComponentBrake* CustomVehicleController::GetBrakes() const
{
	return m_brakes;
}

CustomVehicleControllerComponentBrake* CustomVehicleController::GetHandBrakes() const
{
	return m_handBrakes;
}

void CustomVehicleController::SetEngine(CustomVehicleControllerComponentEngine* const engine)
{
	if (m_engine) {
		for (dList<CustomVehicleControllerBodyState*>::dListNode* node = m_stateList.GetFirst(); node; node = node->GetNext()) {
			if (node->GetInfo() == &m_engineState) {
				m_stateList.Remove(node);
				break;
			}
		}
		delete m_engine;
	}

	m_engine = engine;
	if (m_engine) {
		m_stateList.Append(&m_engineState);
		m_engineState.Init(this);
	}
}

void CustomVehicleController::SetSteering(CustomVehicleControllerComponentSteering* const steering)
{
	if (m_steering) {
		delete m_steering;
	}
	m_steering = steering;
}


void CustomVehicleController::SetBrakes(CustomVehicleControllerComponentBrake* const brakes)
{
	if (m_brakes) {
		delete m_brakes;
	}
	m_brakes = brakes;
}

void CustomVehicleController::SetHandBrakes(CustomVehicleControllerComponentBrake* const brakes)
{
	if (m_handBrakes) {
		delete m_handBrakes;
	}
	m_handBrakes = brakes;
}


int CustomVehicleController::GetActiveJoints(CustomVehicleControllerJoint** const jointArray)
{
	// add the engine joints
	int jointCount = m_engineState.CalculateActiveJoints(this, &jointArray[0]);
//return jointCount;

	// add all contact joints if any
	for (TireList::dListNode* node = m_tireList.GetFirst(); node; node = node->GetNext()) {
		CustomVehicleControllerBodyStateTire* const tire = &node->GetInfo();
		if (tire->m_contactJoint.m_contactCount) {
			jointArray[jointCount] = &tire->m_contactJoint;
			jointCount ++;
			dAssert (jointCount < VEHICLE_CONTROLLER_MAX_JOINTS);
		}
	}

	// add the joints that connect tire to chassis
	for (TireList::dListNode* node = m_tireList.GetFirst(); node; node = node->GetNext()) {
		CustomVehicleControllerBodyStateTire* const tire = &node->GetInfo();
		jointArray[jointCount] = &tire->m_chassisJoint;
		jointCount ++;
		dAssert (jointCount < VEHICLE_CONTROLLER_MAX_JOINTS);
	}


	//	for (int i = 0; i < m_angularJointCount; i ++) {
	//		constraintArray[jointCount] = &m_angularVelocityLinks[i];
	//		jointCount ++;
	//	}
	//	for (int i = 0; i < m_trackSteeringCount; i ++) {
	//		constraintArray[jointCount] = &m_trackSteering[i];
	//		jointCount ++;
	//	}

	//	if (m_dryFriction.m_maxForce > 1.0f) {
	//		constraintArray[jointCount] = &m_dryFriction;
	//		jointCount ++;
	//	}
	return jointCount;
}





int CustomVehicleController::BuildJacobianMatrix (int jointCount, CustomVehicleControllerJoint** const jointArray, dFloat timestep, CustomVehicleControllerJoint::dJacobianPair* const jacobianArray, CustomVehicleControllerJoint::dJacobianColum* const jacobianColumnArray)
{
	int rowCount = 0;

	CustomVehicleControllerJoint::dParamInfo constraintParams;
	constraintParams.m_timestep = timestep;
	constraintParams.m_timestepInv = 1.0f / timestep;

	// calculate Jacobian derivative for each active joint	
	for (int j = 0; j < jointCount; j ++) {
		CustomVehicleControllerJoint* const joint = jointArray[j];
		constraintParams.m_count = 0;
		joint->JacobianDerivative (&constraintParams); 

		int dofCount = constraintParams.m_count;
		joint->m_count = dofCount;
		joint->m_start = rowCount;

		// copy the rows and columns from the Jacobian derivative descriptor
		for (int i = 0; i < dofCount; i ++) {
			CustomVehicleControllerJoint::dJacobianColum* const col = &jacobianColumnArray[rowCount];
			jacobianArray[rowCount] = constraintParams.m_jacobians[i]; 
			col->m_diagDamp = 1.0f;
			col->m_coordenateAccel = constraintParams.m_jointAccel[i];
			col->m_jointLowFriction = constraintParams.m_jointLowFriction[i];
			col->m_jointHighFriction = constraintParams.m_jointHighFriction[i];

			rowCount ++;
			dAssert (rowCount < VEHICLE_CONTROLLER_MAX_JACOBIANS_PAIRS);
		}


		// complete the derivative matrix for this joint
		int index = joint->m_start;
		CustomVehicleControllerBodyState* const state0 = joint->m_state0;
		CustomVehicleControllerBodyState* const state1 = joint->m_state1;

		const dMatrix& invInertia0 = state0->m_invInertia;
		const dMatrix& invInertia1 = state1->m_invInertia;

		dFloat invMass0 = state0->m_invMass;
		dFloat invMass1 = state1->m_invMass;
		dFloat weight = 0.9f;
		for (int i = 0; i < dofCount; i ++) {
			CustomVehicleControllerJoint::dJacobianPair* const row = &jacobianArray[index];
			CustomVehicleControllerJoint::dJacobianColum* const col = &jacobianColumnArray[index];

			dVector JMinvIM0linear (row->m_jacobian_IM0.m_linear.Scale (invMass0));
			dVector JMinvIM1linear (row->m_jacobian_IM1.m_linear.Scale (invMass1));
			dVector JMinvIM0angular = invInertia0.UnrotateVector(row->m_jacobian_IM0.m_angular);
			dVector JMinvIM1angular = invInertia1.UnrotateVector(row->m_jacobian_IM1.m_angular);

			dVector tmpDiag (JMinvIM0linear.CompProduct(row->m_jacobian_IM0.m_linear) + 
				JMinvIM0angular.CompProduct(row->m_jacobian_IM0.m_angular) +
				JMinvIM1linear.CompProduct(row->m_jacobian_IM1.m_linear) + 
				JMinvIM1angular.CompProduct(row->m_jacobian_IM1.m_angular));

			dVector tmpAccel (JMinvIM0linear.CompProduct (state0->m_externalForce) + 
				JMinvIM0angular.CompProduct(state0->m_externalTorque) + 
				JMinvIM1linear.CompProduct (state1->m_externalForce) + 
				JMinvIM1angular.CompProduct(state1->m_externalTorque));

			dFloat extenalAcceleration = -(tmpAccel[0] + tmpAccel[1] + tmpAccel[2]);

			col->m_deltaAccel = extenalAcceleration;
			col->m_coordenateAccel += extenalAcceleration;

			col->m_force = joint->m_jointFeebackForce[i] * weight;

			dFloat stiffness = VEHICLE_PSD_DAMP_TOL * col->m_diagDamp;
			dFloat diag = (tmpDiag[0] + tmpDiag[1] + tmpDiag[2]);
			dAssert (diag > dFloat (0.0f));
			col->m_diagDamp = diag * stiffness;

			diag *= (dFloat(1.0f) + stiffness);
			col->m_invDJMinvJt = dFloat(1.0f) / diag;
			index ++;
		}
	}
	return rowCount;
}

void CustomVehicleController::CalculateReactionsForces (int jointCount, CustomVehicleControllerJoint** const jointArray, dFloat timestepSrc, CustomVehicleControllerJoint::dJacobianPair* const jacobianArray, CustomVehicleControllerJoint::dJacobianColum* const jacobianColumnArray)
{
	CustomVehicleControllerJoint::dJacobian stateVeloc[VEHICLE_CONTROLLER_MAX_JOINTS / 2];
	CustomVehicleControllerJoint::dJacobian internalForces[VEHICLE_CONTROLLER_MAX_JOINTS / 2];

	int stateIndex = 0;
	dVector zero(dFloat (0.0f), dFloat (0.0f), dFloat (0.0f), dFloat (0.0f));
	for (dList<CustomVehicleControllerBodyState*>::dListNode* stateNode = m_stateList.GetFirst(); stateNode; stateNode = stateNode->GetNext()) {
		CustomVehicleControllerBodyState* const state = stateNode->GetInfo();
		stateVeloc[stateIndex].m_linear = state->m_veloc;
		stateVeloc[stateIndex].m_angular = state->m_omega;

		internalForces[stateIndex].m_linear = zero;
		internalForces[stateIndex].m_angular = zero;

		state->m_myIndex = stateIndex;
		stateIndex ++;
		dAssert (stateIndex < int (sizeof (stateVeloc)/sizeof (stateVeloc[0])));
	}

	for (int i = 0; i < jointCount; i ++) {
		CustomVehicleControllerJoint::dJacobian y0;
		CustomVehicleControllerJoint::dJacobian y1;
		y0.m_linear = zero;
		y0.m_angular = zero;
		y1.m_linear = zero;
		y1.m_angular = zero;
		CustomVehicleControllerJoint* const constraint = jointArray[i];
		int first = constraint->m_start;
		int count = constraint->m_count;
		for (int j = 0; j < count; j ++) { 
			CustomVehicleControllerJoint::dJacobianPair* const row = &jacobianArray[j + first];
			const CustomVehicleControllerJoint::dJacobianColum* const col = &jacobianColumnArray[j + first];
			dFloat val = col->m_force; 
			y0.m_linear += row->m_jacobian_IM0.m_linear.Scale(val);
			y0.m_angular += row->m_jacobian_IM0.m_angular.Scale(val);
			y1.m_linear += row->m_jacobian_IM1.m_linear.Scale(val);
			y1.m_angular += row->m_jacobian_IM1.m_angular.Scale(val);
		}
		int m0 = constraint->m_state0->m_myIndex;
		int m1 = constraint->m_state1->m_myIndex;
		internalForces[m0].m_linear += y0.m_linear;
		internalForces[m0].m_angular += y0.m_angular;
		internalForces[m1].m_linear += y1.m_linear;
		internalForces[m1].m_angular += y1.m_angular;
	}


	dFloat invTimestepSrc = dFloat (1.0f) / timestepSrc;
	dFloat invStep = dFloat (0.25f);
	dFloat timestep = timestepSrc * invStep;
	dFloat invTimestep = invTimestepSrc * dFloat (4.0f);

	int maxPasses = 5;
	dFloat firstPassCoef = dFloat (0.0f);
	dFloat maxAccNorm = dFloat (1.0e-2f);

	for (int step = 0; step < 4; step ++) {
		CustomVehicleControllerJoint::dJointAccelerationDecriptor joindDesc;
		joindDesc.m_timeStep = timestep;
		joindDesc.m_invTimeStep = invTimestep;
		joindDesc.m_firstPassCoefFlag = firstPassCoef;

		for (int curJoint = 0; curJoint < jointCount; curJoint ++) {
			CustomVehicleControllerJoint* const constraint = jointArray[curJoint];
			joindDesc.m_rowsCount = constraint->m_count;
			joindDesc.m_rowMatrix = &jacobianArray[constraint->m_start];
			joindDesc.m_colMatrix = &jacobianColumnArray[constraint->m_start];
			constraint->JointAccelerations (&joindDesc);
		}
		firstPassCoef = dFloat (1.0f);

		dFloat accNorm = dFloat (1.0e10f);
		for (int passes = 0; (passes < maxPasses) && (accNorm > maxAccNorm); passes ++) {
			accNorm = dFloat (0.0f);
			for (int curJoint = 0; curJoint < jointCount; curJoint ++) {

				CustomVehicleControllerJoint* const constraint = jointArray[curJoint];
				int index = constraint->m_start;
				int rowsCount = constraint->m_count;
				int m0 = constraint->m_state0->m_myIndex;
				int m1 = constraint->m_state1->m_myIndex;

				dVector linearM0 (internalForces[m0].m_linear);
				dVector angularM0 (internalForces[m0].m_angular);
				dVector linearM1 (internalForces[m1].m_linear);
				dVector angularM1 (internalForces[m1].m_angular);

				CustomVehicleControllerBodyState* const state0 = constraint->m_state0;
				CustomVehicleControllerBodyState* const state1 = constraint->m_state1;
				const dMatrix& invInertia0 = state0->m_invInertia;
				const dMatrix& invInertia1 = state1->m_invInertia;
				dFloat invMass0 = state0->m_invMass;
				dFloat invMass1 = state1->m_invMass;

				for (int k = 0; k < rowsCount; k ++) {
					CustomVehicleControllerJoint::dJacobianPair* const row = &jacobianArray[index];
					CustomVehicleControllerJoint::dJacobianColum* const col = &jacobianColumnArray[index];

					dVector JMinvIM0linear (row->m_jacobian_IM0.m_linear.Scale (invMass0));
					dVector JMinvIM1linear (row->m_jacobian_IM1.m_linear.Scale (invMass1));
					dVector JMinvIM0angular = invInertia0.UnrotateVector(row->m_jacobian_IM0.m_angular);
					dVector JMinvIM1angular = invInertia1.UnrotateVector(row->m_jacobian_IM1.m_angular);
					dVector acc (JMinvIM0linear.CompProduct(linearM0) + JMinvIM0angular.CompProduct(angularM0) + JMinvIM1linear.CompProduct(linearM1) + JMinvIM1angular.CompProduct(angularM1));

					dFloat a = col->m_coordenateAccel - acc.m_x - acc.m_y - acc.m_z - col->m_force * col->m_diagDamp;
					dFloat f = col->m_force + col->m_invDJMinvJt * a;

					dFloat lowerFrictionForce = col->m_jointLowFriction;
					dFloat upperFrictionForce = col->m_jointHighFriction;

					if (f > upperFrictionForce) {
						a = dFloat (0.0f);
						f = upperFrictionForce;
					} else if (f < lowerFrictionForce) {
						a = dFloat (0.0f);
						f = lowerFrictionForce;
					}

					accNorm = dMax (accNorm, dAbs (a));
					dFloat prevValue = f - col->m_force;
					col->m_force = f;

					linearM0 += row->m_jacobian_IM0.m_linear.Scale (prevValue);
					angularM0 += row->m_jacobian_IM0.m_angular.Scale (prevValue);
					linearM1 += row->m_jacobian_IM1.m_linear.Scale (prevValue);
					angularM1 += row->m_jacobian_IM1.m_angular.Scale (prevValue);
					index ++;
				}
				internalForces[m0].m_linear = linearM0;
				internalForces[m0].m_angular = angularM0;
				internalForces[m1].m_linear = linearM1;
				internalForces[m1].m_angular = angularM1;
			}
		}

		for (dList<CustomVehicleControllerBodyState*>::dListNode* stateNode = m_stateList.GetFirst()->GetNext(); stateNode; stateNode = stateNode->GetNext()) {
			CustomVehicleControllerBodyState* const state = stateNode->GetInfo();
			int index = state->m_myIndex;
			dVector force (state->m_externalForce + internalForces[index].m_linear);
			dVector torque (state->m_externalTorque + internalForces[index].m_angular);
			state->IntegrateForce(timestep, force, torque);
		}
	}

	for (int i = 0; i < jointCount; i ++) {
		CustomVehicleControllerJoint* const constraint = jointArray[i];
		int first = constraint->m_start;
		int count = constraint->m_count;
		for (int j = 0; j < count; j ++) { 
			const CustomVehicleControllerJoint::dJacobianColum* const col = &jacobianColumnArray[j + first];
			dFloat val = col->m_force; 
			constraint->m_jointFeebackForce[j] = val;
		}
	}

	for (dList<CustomVehicleControllerBodyState*>::dListNode* stateNode = m_stateList.GetFirst()->GetNext(); stateNode; stateNode = stateNode->GetNext()) {
		CustomVehicleControllerBodyState* const state = stateNode->GetInfo();
		int index = state->m_myIndex;
		state->ApplyNetForceAndTorque (invTimestepSrc, stateVeloc[index].m_linear, stateVeloc[index].m_angular);
	}

	for (int i = 0; i < jointCount; i ++) {
		CustomVehicleControllerJoint* const constraint = jointArray[i];
		constraint->UpdateSolverForces (jacobianArray);
	}
}


void CustomVehicleController::Finalize()
{
	dWeightDistibutionSolver solver;
	dFloat64 unitAccel[VEHICLE_CONTROLLER_MAX_JOINTS];
	dFloat64 sprungMass[VEHICLE_CONTROLLER_MAX_JOINTS];

	dAssert (m_tireList.GetCount() <= 4);

	// make sure tire are aligned
/*
	memset (unitAccel, sizeof (unitAccel), 0);
	int index = 0;
	for (TireList::dListNode* node0 = m_tireList.GetFirst(); node0; node0 = node0->GetNext()) {
		if (unitAccel[index] == 0) {
			CustomVehicleControllerBodyStateTire* const tire0 = &node0->GetInfo();
			for (TireList::dListNode* node1 = node0->GetNext(); node1; node1 = node1->GetNext()) {
				CustomVehicleControllerBodyStateTire* const tire1 = &node->GetInfo();
			}
		}
	}
*/
	
	int count = 0;
	m_chassisState.m_matrix = GetIdentityMatrix();
	m_chassisState.UpdateInertia();
	dVector dir (m_chassisState.m_localFrame[1]);
	for (TireList::dListNode* node = m_tireList.GetFirst(); node; node = node->GetNext()) {
		CustomVehicleControllerBodyStateTire* const tire = &node->GetInfo();
		dVector posit  (tire->m_localFrame.m_posit);  
		CustomVehicleControllerJoint::dJacobian &jacobian0 = solver.m_jacobians[count];
		CustomVehicleControllerJoint::dJacobian &invMassJacobian0 = solver.m_invMassJacobians[count];
		jacobian0.m_linear = dir;
		jacobian0.m_angular = posit * dir;
		jacobian0.m_angular.m_w = 0.0f;

		invMassJacobian0.m_linear = jacobian0.m_linear.Scale(m_chassisState.m_invMass);
		invMassJacobian0.m_angular = jacobian0.m_angular.CompProduct(m_chassisState.m_localInvInertia);

		dFloat diagnal = jacobian0.m_linear % invMassJacobian0.m_linear + jacobian0.m_angular % invMassJacobian0.m_angular;
		solver.m_diagRegularizer[count] = diagnal * 0.005f;
		solver.m_invDiag[count] = 1.0f / (diagnal + solver.m_diagRegularizer[count]);

		unitAccel[count] = 1.0f;
		sprungMass[count] = 0.0f;
		count ++;
	}

	solver.m_count = count;
	solver.Solve (count, 1.0e-6f, sprungMass, unitAccel);

	int index = 0;
	for (TireList::dListNode* node = m_tireList.GetFirst(); node; node = node->GetNext()) {
		CustomVehicleControllerBodyStateTire* const tire = &node->GetInfo();
		tire->m_restSprunMass = dFloat (5.0f * dFloor (sprungMass[index] / 5.0f + 0.5f));
		index ++;
	}

	m_finalized = true;
}



void CustomVehicleController::PostUpdate(dFloat timestep, int threadIndex)
{
	if (m_finalized) {
		NewtonBody* const body = GetBody();
		NewtonBodyGetMatrix(body, &m_chassisState.m_matrix[0][0]);
		for (TireList::dListNode* node = m_tireList.GetFirst(); node; node = node->GetNext()) {
			CustomVehicleControllerBodyStateTire* const tire = &node->GetInfo();
			tire->UpdateTransform();
		}
	}
}


void CustomVehicleController::PreUpdate(dFloat timestep, int threadIndex)
{
	if (!m_finalized) {
		return;
	}
	CustomVehicleControllerJoint* jointArray[VEHICLE_CONTROLLER_MAX_JOINTS];
	CustomVehicleControllerJoint::dJacobianColum jacobianColumn[VEHICLE_CONTROLLER_MAX_JACOBIANS_PAIRS];
	CustomVehicleControllerJoint::dJacobianPair jacobianPairArray[VEHICLE_CONTROLLER_MAX_JACOBIANS_PAIRS];

	// apply all external forces and torques to chassis and all tire velocities
	dFloat timestepInv = 1.0f / timestep;
	NewtonBody* const body = GetBody();
	CustomControllerConvexCastPreFilter castFilter (body);
	m_chassisState.UpdateDynamicInputs();

	for (TireList::dListNode* node = m_tireList.GetFirst(); node; node = node->GetNext()) {
		CustomVehicleControllerBodyStateTire* const tire = &node->GetInfo();
		tire->Collide(castFilter, timestepInv);
		tire->UpdateDynamicInputs(timestep);
	}

static int xxx;
xxx ++;
if (xxx > 1780)
xxx *=1;

//dVector xxxxx;
//NewtonBodyGetOmega(body, &xxxxx[0]);
//dAssert (dAbs(xxxxx.m_y) < 0.01f);
//NewtonBodySetOmega(body, &xxxxx[0]);
//m_chassisState.m_externalForce += m_chassisState.m_matrix[0].Scale (2.0f * m_chassisState.m_mass);
//m_chassisState.m_externalForce = dVector (0, 0, 0, 0);

	// update all components
	if (m_engine) {
		m_engine->Update(timestep);
	}

	if (m_steering) {
		m_steering->Update(timestep);
	}

	if (m_handBrakes) {
		m_handBrakes->Update(timestep);
	}

	if (m_brakes) {
		m_brakes->Update(timestep);
	}

	// Get the number of active joints for this integration step
	int jointCount = GetActiveJoints(jointArray);
	BuildJacobianMatrix (jointCount, jointArray, timestep, jacobianPairArray, jacobianColumn);
	CalculateReactionsForces (jointCount, jointArray, timestep, jacobianPairArray, jacobianColumn);

/*
dTrace (("%f %f %f  ", m_engine->GetSpeed(), m_engineState.m_radianPerSecund, m_engine->GetGearBox()->GetGearRatio(m_engine->GetGear())));
//for (TireList::dListNode* node = m_tireList.GetFirst()->GetNext()->GetNext(); node; node = node->GetNext()) {
for (TireList::dListNode* node = m_tireList.GetFirst(); node; node = node->GetNext()) {
CustomVehicleControllerBodyStateTire* const tire = &node->GetInfo();
dTrace (("%f ", tire->m_rotatonSpeed * tire->m_radio));
}
dTrace (("\n"));
*/
//dTrace (("f(%f %f %f) T(%f %f %f)\n", m_chassisState.m_externalForce.m_x, m_chassisState.m_externalForce.m_y, m_chassisState.m_externalForce.m_z, m_chassisState.m_externalTorque.m_x, m_chassisState.m_externalTorque.m_y, m_chassisState.m_externalTorque.m_z));
}


