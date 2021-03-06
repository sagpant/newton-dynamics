/*
Copyright 2018 Ioannis Makris

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// This file was generated by glatter.py script.



#ifdef GLATTER_WGL
#if defined(__wgl_wglext_h_)
#if defined(WGL_3DL_stereo_control)
#ifndef wglSetStereoEmitterState3DL
#define wglSetStereoEmitterState3DL(hDC, uState) glatter_wglSetStereoEmitterState3DL((hDC), (uState))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglSetStereoEmitterState3DL, (HDC hDC, UINT uState))
#endif // defined(WGL_3DL_stereo_control)
#if defined(WGL_AMD_gpu_association)
#ifndef wglBlitContextFramebufferAMD
#define wglBlitContextFramebufferAMD(dstCtx, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter) glatter_wglBlitContextFramebufferAMD((dstCtx), (srcX0), (srcY0), (srcX1), (srcY1), (dstX0), (dstY0), (dstX1), (dstY1), (mask), (filter))
#endif
GLATTER_UBLOCK(VOID, WINAPI, wglBlitContextFramebufferAMD, (HGLRC dstCtx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter))
#ifndef wglCreateAssociatedContextAMD
#define wglCreateAssociatedContextAMD(id) glatter_wglCreateAssociatedContextAMD((id))
#endif
GLATTER_UBLOCK(HGLRC, WINAPI, wglCreateAssociatedContextAMD, (UINT id))
#ifndef wglCreateAssociatedContextAttribsAMD
#define wglCreateAssociatedContextAttribsAMD(id, hShareContext, attribList) glatter_wglCreateAssociatedContextAttribsAMD((id), (hShareContext), (attribList))
#endif
GLATTER_UBLOCK(HGLRC, WINAPI, wglCreateAssociatedContextAttribsAMD, (UINT id, HGLRC hShareContext, const int *attribList))
#ifndef wglDeleteAssociatedContextAMD
#define wglDeleteAssociatedContextAMD(hglrc) glatter_wglDeleteAssociatedContextAMD((hglrc))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDeleteAssociatedContextAMD, (HGLRC hglrc))
#ifndef wglGetContextGPUIDAMD
#define wglGetContextGPUIDAMD(hglrc) glatter_wglGetContextGPUIDAMD((hglrc))
#endif
GLATTER_UBLOCK(UINT, WINAPI, wglGetContextGPUIDAMD, (HGLRC hglrc))
#ifndef wglGetCurrentAssociatedContextAMD
#define wglGetCurrentAssociatedContextAMD() glatter_wglGetCurrentAssociatedContextAMD()
#endif
GLATTER_UBLOCK(HGLRC, WINAPI, wglGetCurrentAssociatedContextAMD, (void))
#ifndef wglGetGPUIDsAMD
#define wglGetGPUIDsAMD(maxCount, ids) glatter_wglGetGPUIDsAMD((maxCount), (ids))
#endif
GLATTER_UBLOCK(UINT, WINAPI, wglGetGPUIDsAMD, (UINT maxCount, UINT *ids))
#ifndef wglGetGPUInfoAMD
#define wglGetGPUInfoAMD(id, property, dataType, size, data) glatter_wglGetGPUInfoAMD((id), (property), (dataType), (size), (data))
#endif
GLATTER_UBLOCK(INT, WINAPI, wglGetGPUInfoAMD, (UINT id, int property, GLenum dataType, UINT size, void *data))
#ifndef wglMakeAssociatedContextCurrentAMD
#define wglMakeAssociatedContextCurrentAMD(hglrc) glatter_wglMakeAssociatedContextCurrentAMD((hglrc))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglMakeAssociatedContextCurrentAMD, (HGLRC hglrc))
#endif // defined(WGL_AMD_gpu_association)
#if defined(WGL_ARB_buffer_region)
#ifndef wglCreateBufferRegionARB
#define wglCreateBufferRegionARB(hDC, iLayerPlane, uType) glatter_wglCreateBufferRegionARB((hDC), (iLayerPlane), (uType))
#endif
GLATTER_UBLOCK(HANDLE, WINAPI, wglCreateBufferRegionARB, (HDC hDC, int iLayerPlane, UINT uType))
#ifndef wglDeleteBufferRegionARB
#define wglDeleteBufferRegionARB(hRegion) glatter_wglDeleteBufferRegionARB((hRegion))
#endif
GLATTER_UBLOCK(VOID, WINAPI, wglDeleteBufferRegionARB, (HANDLE hRegion))
#ifndef wglRestoreBufferRegionARB
#define wglRestoreBufferRegionARB(hRegion, x, y, width, height, xSrc, ySrc) glatter_wglRestoreBufferRegionARB((hRegion), (x), (y), (width), (height), (xSrc), (ySrc))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglRestoreBufferRegionARB, (HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc))
#ifndef wglSaveBufferRegionARB
#define wglSaveBufferRegionARB(hRegion, x, y, width, height) glatter_wglSaveBufferRegionARB((hRegion), (x), (y), (width), (height))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglSaveBufferRegionARB, (HANDLE hRegion, int x, int y, int width, int height))
#endif // defined(WGL_ARB_buffer_region)
#if defined(WGL_ARB_create_context)
#ifndef wglCreateContextAttribsARB
#define wglCreateContextAttribsARB(hDC, hShareContext, attribList) glatter_wglCreateContextAttribsARB((hDC), (hShareContext), (attribList))
#endif
GLATTER_UBLOCK(HGLRC, WINAPI, wglCreateContextAttribsARB, (HDC hDC, HGLRC hShareContext, const int *attribList))
#endif // defined(WGL_ARB_create_context)
#if defined(WGL_ARB_extensions_string)
#ifndef wglGetExtensionsStringARB
#define wglGetExtensionsStringARB(hdc) glatter_wglGetExtensionsStringARB((hdc))
#endif
GLATTER_UBLOCK(const char *, WINAPI, wglGetExtensionsStringARB, (HDC hdc))
#endif // defined(WGL_ARB_extensions_string)
#if defined(WGL_ARB_make_current_read)
#ifndef wglGetCurrentReadDCARB
#define wglGetCurrentReadDCARB() glatter_wglGetCurrentReadDCARB()
#endif
GLATTER_UBLOCK(HDC, WINAPI, wglGetCurrentReadDCARB, (void))
#ifndef wglMakeContextCurrentARB
#define wglMakeContextCurrentARB(hDrawDC, hReadDC, hglrc) glatter_wglMakeContextCurrentARB((hDrawDC), (hReadDC), (hglrc))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglMakeContextCurrentARB, (HDC hDrawDC, HDC hReadDC, HGLRC hglrc))
#endif // defined(WGL_ARB_make_current_read)
#if defined(WGL_ARB_pbuffer)
#ifndef wglCreatePbufferARB
#define wglCreatePbufferARB(hDC, iPixelFormat, iWidth, iHeight, piAttribList) glatter_wglCreatePbufferARB((hDC), (iPixelFormat), (iWidth), (iHeight), (piAttribList))
#endif
GLATTER_UBLOCK(HPBUFFERARB, WINAPI, wglCreatePbufferARB, (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList))
#ifndef wglDestroyPbufferARB
#define wglDestroyPbufferARB(hPbuffer) glatter_wglDestroyPbufferARB((hPbuffer))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDestroyPbufferARB, (HPBUFFERARB hPbuffer))
#ifndef wglGetPbufferDCARB
#define wglGetPbufferDCARB(hPbuffer) glatter_wglGetPbufferDCARB((hPbuffer))
#endif
GLATTER_UBLOCK(HDC, WINAPI, wglGetPbufferDCARB, (HPBUFFERARB hPbuffer))
#ifndef wglQueryPbufferARB
#define wglQueryPbufferARB(hPbuffer, iAttribute, piValue) glatter_wglQueryPbufferARB((hPbuffer), (iAttribute), (piValue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQueryPbufferARB, (HPBUFFERARB hPbuffer, int iAttribute, int *piValue))
#ifndef wglReleasePbufferDCARB
#define wglReleasePbufferDCARB(hPbuffer, hDC) glatter_wglReleasePbufferDCARB((hPbuffer), (hDC))
#endif
GLATTER_UBLOCK(int, WINAPI, wglReleasePbufferDCARB, (HPBUFFERARB hPbuffer, HDC hDC))
#endif // defined(WGL_ARB_pbuffer)
#if defined(WGL_ARB_pixel_format)
#ifndef wglChoosePixelFormatARB
#define wglChoosePixelFormatARB(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats) glatter_wglChoosePixelFormatARB((hdc), (piAttribIList), (pfAttribFList), (nMaxFormats), (piFormats), (nNumFormats))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglChoosePixelFormatARB, (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats))
#ifndef wglGetPixelFormatAttribfvARB
#define wglGetPixelFormatAttribfvARB(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues) glatter_wglGetPixelFormatAttribfvARB((hdc), (iPixelFormat), (iLayerPlane), (nAttributes), (piAttributes), (pfValues))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetPixelFormatAttribfvARB, (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues))
#ifndef wglGetPixelFormatAttribivARB
#define wglGetPixelFormatAttribivARB(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues) glatter_wglGetPixelFormatAttribivARB((hdc), (iPixelFormat), (iLayerPlane), (nAttributes), (piAttributes), (piValues))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetPixelFormatAttribivARB, (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues))
#endif // defined(WGL_ARB_pixel_format)
#if defined(WGL_ARB_render_texture)
#ifndef wglBindTexImageARB
#define wglBindTexImageARB(hPbuffer, iBuffer) glatter_wglBindTexImageARB((hPbuffer), (iBuffer))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglBindTexImageARB, (HPBUFFERARB hPbuffer, int iBuffer))
#ifndef wglReleaseTexImageARB
#define wglReleaseTexImageARB(hPbuffer, iBuffer) glatter_wglReleaseTexImageARB((hPbuffer), (iBuffer))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglReleaseTexImageARB, (HPBUFFERARB hPbuffer, int iBuffer))
#ifndef wglSetPbufferAttribARB
#define wglSetPbufferAttribARB(hPbuffer, piAttribList) glatter_wglSetPbufferAttribARB((hPbuffer), (piAttribList))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglSetPbufferAttribARB, (HPBUFFERARB hPbuffer, const int *piAttribList))
#endif // defined(WGL_ARB_render_texture)
#if defined(WGL_EXT_display_color_table)
#ifndef wglBindDisplayColorTableEXT
#define wglBindDisplayColorTableEXT(id) glatter_wglBindDisplayColorTableEXT((id))
#endif
GLATTER_UBLOCK(GLboolean, WINAPI, wglBindDisplayColorTableEXT, (GLushort id))
#ifndef wglCreateDisplayColorTableEXT
#define wglCreateDisplayColorTableEXT(id) glatter_wglCreateDisplayColorTableEXT((id))
#endif
GLATTER_UBLOCK(GLboolean, WINAPI, wglCreateDisplayColorTableEXT, (GLushort id))
#ifndef wglDestroyDisplayColorTableEXT
#define wglDestroyDisplayColorTableEXT(id) glatter_wglDestroyDisplayColorTableEXT((id))
#endif
GLATTER_UBLOCK(VOID, WINAPI, wglDestroyDisplayColorTableEXT, (GLushort id))
#ifndef wglLoadDisplayColorTableEXT
#define wglLoadDisplayColorTableEXT(table, length) glatter_wglLoadDisplayColorTableEXT((table), (length))
#endif
GLATTER_UBLOCK(GLboolean, WINAPI, wglLoadDisplayColorTableEXT, (const GLushort *table, GLuint length))
#endif // defined(WGL_EXT_display_color_table)
#if defined(WGL_EXT_extensions_string)
#ifndef wglGetExtensionsStringEXT
#define wglGetExtensionsStringEXT() glatter_wglGetExtensionsStringEXT()
#endif
GLATTER_UBLOCK(const char *, WINAPI, wglGetExtensionsStringEXT, (void))
#endif // defined(WGL_EXT_extensions_string)
#if defined(WGL_EXT_make_current_read)
#ifndef wglGetCurrentReadDCEXT
#define wglGetCurrentReadDCEXT() glatter_wglGetCurrentReadDCEXT()
#endif
GLATTER_UBLOCK(HDC, WINAPI, wglGetCurrentReadDCEXT, (void))
#ifndef wglMakeContextCurrentEXT
#define wglMakeContextCurrentEXT(hDrawDC, hReadDC, hglrc) glatter_wglMakeContextCurrentEXT((hDrawDC), (hReadDC), (hglrc))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglMakeContextCurrentEXT, (HDC hDrawDC, HDC hReadDC, HGLRC hglrc))
#endif // defined(WGL_EXT_make_current_read)
#if defined(WGL_EXT_pbuffer)
#ifndef wglCreatePbufferEXT
#define wglCreatePbufferEXT(hDC, iPixelFormat, iWidth, iHeight, piAttribList) glatter_wglCreatePbufferEXT((hDC), (iPixelFormat), (iWidth), (iHeight), (piAttribList))
#endif
GLATTER_UBLOCK(HPBUFFEREXT, WINAPI, wglCreatePbufferEXT, (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList))
#ifndef wglDestroyPbufferEXT
#define wglDestroyPbufferEXT(hPbuffer) glatter_wglDestroyPbufferEXT((hPbuffer))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDestroyPbufferEXT, (HPBUFFEREXT hPbuffer))
#ifndef wglGetPbufferDCEXT
#define wglGetPbufferDCEXT(hPbuffer) glatter_wglGetPbufferDCEXT((hPbuffer))
#endif
GLATTER_UBLOCK(HDC, WINAPI, wglGetPbufferDCEXT, (HPBUFFEREXT hPbuffer))
#ifndef wglQueryPbufferEXT
#define wglQueryPbufferEXT(hPbuffer, iAttribute, piValue) glatter_wglQueryPbufferEXT((hPbuffer), (iAttribute), (piValue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQueryPbufferEXT, (HPBUFFEREXT hPbuffer, int iAttribute, int *piValue))
#ifndef wglReleasePbufferDCEXT
#define wglReleasePbufferDCEXT(hPbuffer, hDC) glatter_wglReleasePbufferDCEXT((hPbuffer), (hDC))
#endif
GLATTER_UBLOCK(int, WINAPI, wglReleasePbufferDCEXT, (HPBUFFEREXT hPbuffer, HDC hDC))
#endif // defined(WGL_EXT_pbuffer)
#if defined(WGL_EXT_pixel_format)
#ifndef wglChoosePixelFormatEXT
#define wglChoosePixelFormatEXT(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats) glatter_wglChoosePixelFormatEXT((hdc), (piAttribIList), (pfAttribFList), (nMaxFormats), (piFormats), (nNumFormats))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglChoosePixelFormatEXT, (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats))
#ifndef wglGetPixelFormatAttribfvEXT
#define wglGetPixelFormatAttribfvEXT(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues) glatter_wglGetPixelFormatAttribfvEXT((hdc), (iPixelFormat), (iLayerPlane), (nAttributes), (piAttributes), (pfValues))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetPixelFormatAttribfvEXT, (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, FLOAT *pfValues))
#ifndef wglGetPixelFormatAttribivEXT
#define wglGetPixelFormatAttribivEXT(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues) glatter_wglGetPixelFormatAttribivEXT((hdc), (iPixelFormat), (iLayerPlane), (nAttributes), (piAttributes), (piValues))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetPixelFormatAttribivEXT, (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, int *piValues))
#endif // defined(WGL_EXT_pixel_format)
#if defined(WGL_EXT_swap_control)
#ifndef wglGetSwapIntervalEXT
#define wglGetSwapIntervalEXT() glatter_wglGetSwapIntervalEXT()
#endif
GLATTER_UBLOCK(int, WINAPI, wglGetSwapIntervalEXT, (void))
#ifndef wglSwapIntervalEXT
#define wglSwapIntervalEXT(interval) glatter_wglSwapIntervalEXT((interval))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglSwapIntervalEXT, (int interval))
#endif // defined(WGL_EXT_swap_control)
#if defined(WGL_I3D_digital_video_control)
#ifndef wglGetDigitalVideoParametersI3D
#define wglGetDigitalVideoParametersI3D(hDC, iAttribute, piValue) glatter_wglGetDigitalVideoParametersI3D((hDC), (iAttribute), (piValue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetDigitalVideoParametersI3D, (HDC hDC, int iAttribute, int *piValue))
#ifndef wglSetDigitalVideoParametersI3D
#define wglSetDigitalVideoParametersI3D(hDC, iAttribute, piValue) glatter_wglSetDigitalVideoParametersI3D((hDC), (iAttribute), (piValue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglSetDigitalVideoParametersI3D, (HDC hDC, int iAttribute, const int *piValue))
#endif // defined(WGL_I3D_digital_video_control)
#if defined(WGL_I3D_gamma)
#ifndef wglGetGammaTableI3D
#define wglGetGammaTableI3D(hDC, iEntries, puRed, puGreen, puBlue) glatter_wglGetGammaTableI3D((hDC), (iEntries), (puRed), (puGreen), (puBlue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetGammaTableI3D, (HDC hDC, int iEntries, USHORT *puRed, USHORT *puGreen, USHORT *puBlue))
#ifndef wglGetGammaTableParametersI3D
#define wglGetGammaTableParametersI3D(hDC, iAttribute, piValue) glatter_wglGetGammaTableParametersI3D((hDC), (iAttribute), (piValue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetGammaTableParametersI3D, (HDC hDC, int iAttribute, int *piValue))
#ifndef wglSetGammaTableI3D
#define wglSetGammaTableI3D(hDC, iEntries, puRed, puGreen, puBlue) glatter_wglSetGammaTableI3D((hDC), (iEntries), (puRed), (puGreen), (puBlue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglSetGammaTableI3D, (HDC hDC, int iEntries, const USHORT *puRed, const USHORT *puGreen, const USHORT *puBlue))
#ifndef wglSetGammaTableParametersI3D
#define wglSetGammaTableParametersI3D(hDC, iAttribute, piValue) glatter_wglSetGammaTableParametersI3D((hDC), (iAttribute), (piValue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglSetGammaTableParametersI3D, (HDC hDC, int iAttribute, const int *piValue))
#endif // defined(WGL_I3D_gamma)
#if defined(WGL_I3D_genlock)
#ifndef wglDisableGenlockI3D
#define wglDisableGenlockI3D(hDC) glatter_wglDisableGenlockI3D((hDC))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDisableGenlockI3D, (HDC hDC))
#ifndef wglEnableGenlockI3D
#define wglEnableGenlockI3D(hDC) glatter_wglEnableGenlockI3D((hDC))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglEnableGenlockI3D, (HDC hDC))
#ifndef wglGenlockSampleRateI3D
#define wglGenlockSampleRateI3D(hDC, uRate) glatter_wglGenlockSampleRateI3D((hDC), (uRate))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGenlockSampleRateI3D, (HDC hDC, UINT uRate))
#ifndef wglGenlockSourceDelayI3D
#define wglGenlockSourceDelayI3D(hDC, uDelay) glatter_wglGenlockSourceDelayI3D((hDC), (uDelay))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGenlockSourceDelayI3D, (HDC hDC, UINT uDelay))
#ifndef wglGenlockSourceEdgeI3D
#define wglGenlockSourceEdgeI3D(hDC, uEdge) glatter_wglGenlockSourceEdgeI3D((hDC), (uEdge))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGenlockSourceEdgeI3D, (HDC hDC, UINT uEdge))
#ifndef wglGenlockSourceI3D
#define wglGenlockSourceI3D(hDC, uSource) glatter_wglGenlockSourceI3D((hDC), (uSource))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGenlockSourceI3D, (HDC hDC, UINT uSource))
#ifndef wglGetGenlockSampleRateI3D
#define wglGetGenlockSampleRateI3D(hDC, uRate) glatter_wglGetGenlockSampleRateI3D((hDC), (uRate))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetGenlockSampleRateI3D, (HDC hDC, UINT *uRate))
#ifndef wglGetGenlockSourceDelayI3D
#define wglGetGenlockSourceDelayI3D(hDC, uDelay) glatter_wglGetGenlockSourceDelayI3D((hDC), (uDelay))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetGenlockSourceDelayI3D, (HDC hDC, UINT *uDelay))
#ifndef wglGetGenlockSourceEdgeI3D
#define wglGetGenlockSourceEdgeI3D(hDC, uEdge) glatter_wglGetGenlockSourceEdgeI3D((hDC), (uEdge))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetGenlockSourceEdgeI3D, (HDC hDC, UINT *uEdge))
#ifndef wglGetGenlockSourceI3D
#define wglGetGenlockSourceI3D(hDC, uSource) glatter_wglGetGenlockSourceI3D((hDC), (uSource))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetGenlockSourceI3D, (HDC hDC, UINT *uSource))
#ifndef wglIsEnabledGenlockI3D
#define wglIsEnabledGenlockI3D(hDC, pFlag) glatter_wglIsEnabledGenlockI3D((hDC), (pFlag))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglIsEnabledGenlockI3D, (HDC hDC, BOOL *pFlag))
#ifndef wglQueryGenlockMaxSourceDelayI3D
#define wglQueryGenlockMaxSourceDelayI3D(hDC, uMaxLineDelay, uMaxPixelDelay) glatter_wglQueryGenlockMaxSourceDelayI3D((hDC), (uMaxLineDelay), (uMaxPixelDelay))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQueryGenlockMaxSourceDelayI3D, (HDC hDC, UINT *uMaxLineDelay, UINT *uMaxPixelDelay))
#endif // defined(WGL_I3D_genlock)
#if defined(WGL_I3D_image_buffer)
#ifndef wglAssociateImageBufferEventsI3D
#define wglAssociateImageBufferEventsI3D(hDC, pEvent, pAddress, pSize, count) glatter_wglAssociateImageBufferEventsI3D((hDC), (pEvent), (pAddress), (pSize), (count))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglAssociateImageBufferEventsI3D, (HDC hDC, const HANDLE *pEvent, const LPVOID *pAddress, const DWORD *pSize, UINT count))
#ifndef wglCreateImageBufferI3D
#define wglCreateImageBufferI3D(hDC, dwSize, uFlags) glatter_wglCreateImageBufferI3D((hDC), (dwSize), (uFlags))
#endif
GLATTER_UBLOCK(LPVOID, WINAPI, wglCreateImageBufferI3D, (HDC hDC, DWORD dwSize, UINT uFlags))
#ifndef wglDestroyImageBufferI3D
#define wglDestroyImageBufferI3D(hDC, pAddress) glatter_wglDestroyImageBufferI3D((hDC), (pAddress))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDestroyImageBufferI3D, (HDC hDC, LPVOID pAddress))
#ifndef wglReleaseImageBufferEventsI3D
#define wglReleaseImageBufferEventsI3D(hDC, pAddress, count) glatter_wglReleaseImageBufferEventsI3D((hDC), (pAddress), (count))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglReleaseImageBufferEventsI3D, (HDC hDC, const LPVOID *pAddress, UINT count))
#endif // defined(WGL_I3D_image_buffer)
#if defined(WGL_I3D_swap_frame_lock)
#ifndef wglDisableFrameLockI3D
#define wglDisableFrameLockI3D() glatter_wglDisableFrameLockI3D()
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDisableFrameLockI3D, (void))
#ifndef wglEnableFrameLockI3D
#define wglEnableFrameLockI3D() glatter_wglEnableFrameLockI3D()
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglEnableFrameLockI3D, (void))
#ifndef wglIsEnabledFrameLockI3D
#define wglIsEnabledFrameLockI3D(pFlag) glatter_wglIsEnabledFrameLockI3D((pFlag))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglIsEnabledFrameLockI3D, (BOOL *pFlag))
#ifndef wglQueryFrameLockMasterI3D
#define wglQueryFrameLockMasterI3D(pFlag) glatter_wglQueryFrameLockMasterI3D((pFlag))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQueryFrameLockMasterI3D, (BOOL *pFlag))
#endif // defined(WGL_I3D_swap_frame_lock)
#if defined(WGL_I3D_swap_frame_usage)
#ifndef wglBeginFrameTrackingI3D
#define wglBeginFrameTrackingI3D() glatter_wglBeginFrameTrackingI3D()
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglBeginFrameTrackingI3D, (void))
#ifndef wglEndFrameTrackingI3D
#define wglEndFrameTrackingI3D() glatter_wglEndFrameTrackingI3D()
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglEndFrameTrackingI3D, (void))
#ifndef wglGetFrameUsageI3D
#define wglGetFrameUsageI3D(pUsage) glatter_wglGetFrameUsageI3D((pUsage))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetFrameUsageI3D, (float *pUsage))
#ifndef wglQueryFrameTrackingI3D
#define wglQueryFrameTrackingI3D(pFrameCount, pMissedFrames, pLastMissedUsage) glatter_wglQueryFrameTrackingI3D((pFrameCount), (pMissedFrames), (pLastMissedUsage))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQueryFrameTrackingI3D, (DWORD *pFrameCount, DWORD *pMissedFrames, float *pLastMissedUsage))
#endif // defined(WGL_I3D_swap_frame_usage)
#if defined(WGL_NV_DX_interop)
#ifndef wglDXCloseDeviceNV
#define wglDXCloseDeviceNV(hDevice) glatter_wglDXCloseDeviceNV((hDevice))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDXCloseDeviceNV, (HANDLE hDevice))
#ifndef wglDXLockObjectsNV
#define wglDXLockObjectsNV(hDevice, count, hObjects) glatter_wglDXLockObjectsNV((hDevice), (count), (hObjects))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDXLockObjectsNV, (HANDLE hDevice, GLint count, HANDLE *hObjects))
#ifndef wglDXObjectAccessNV
#define wglDXObjectAccessNV(hObject, access) glatter_wglDXObjectAccessNV((hObject), (access))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDXObjectAccessNV, (HANDLE hObject, GLenum access))
#ifndef wglDXOpenDeviceNV
#define wglDXOpenDeviceNV(dxDevice) glatter_wglDXOpenDeviceNV((dxDevice))
#endif
GLATTER_UBLOCK(HANDLE, WINAPI, wglDXOpenDeviceNV, (void *dxDevice))
#ifndef wglDXRegisterObjectNV
#define wglDXRegisterObjectNV(hDevice, dxObject, name, type, access) glatter_wglDXRegisterObjectNV((hDevice), (dxObject), (name), (type), (access))
#endif
GLATTER_UBLOCK(HANDLE, WINAPI, wglDXRegisterObjectNV, (HANDLE hDevice, void *dxObject, GLuint name, GLenum type, GLenum access))
#ifndef wglDXSetResourceShareHandleNV
#define wglDXSetResourceShareHandleNV(dxObject, shareHandle) glatter_wglDXSetResourceShareHandleNV((dxObject), (shareHandle))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDXSetResourceShareHandleNV, (void *dxObject, HANDLE shareHandle))
#ifndef wglDXUnlockObjectsNV
#define wglDXUnlockObjectsNV(hDevice, count, hObjects) glatter_wglDXUnlockObjectsNV((hDevice), (count), (hObjects))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDXUnlockObjectsNV, (HANDLE hDevice, GLint count, HANDLE *hObjects))
#ifndef wglDXUnregisterObjectNV
#define wglDXUnregisterObjectNV(hDevice, hObject) glatter_wglDXUnregisterObjectNV((hDevice), (hObject))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDXUnregisterObjectNV, (HANDLE hDevice, HANDLE hObject))
#endif // defined(WGL_NV_DX_interop)
#if defined(WGL_NV_copy_image)
#ifndef wglCopyImageSubDataNV
#define wglCopyImageSubDataNV(hSrcRC, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, hDstRC, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth) glatter_wglCopyImageSubDataNV((hSrcRC), (srcName), (srcTarget), (srcLevel), (srcX), (srcY), (srcZ), (hDstRC), (dstName), (dstTarget), (dstLevel), (dstX), (dstY), (dstZ), (width), (height), (depth))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglCopyImageSubDataNV, (HGLRC hSrcRC, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, HGLRC hDstRC, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth))
#endif // defined(WGL_NV_copy_image)
#if defined(WGL_NV_delay_before_swap)
#ifndef wglDelayBeforeSwapNV
#define wglDelayBeforeSwapNV(hDC, seconds) glatter_wglDelayBeforeSwapNV((hDC), (seconds))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDelayBeforeSwapNV, (HDC hDC, GLfloat seconds))
#endif // defined(WGL_NV_delay_before_swap)
#if defined(WGL_NV_gpu_affinity)
#ifndef wglCreateAffinityDCNV
#define wglCreateAffinityDCNV(phGpuList) glatter_wglCreateAffinityDCNV((phGpuList))
#endif
GLATTER_UBLOCK(HDC, WINAPI, wglCreateAffinityDCNV, (const HGPUNV *phGpuList))
#ifndef wglDeleteDCNV
#define wglDeleteDCNV(hdc) glatter_wglDeleteDCNV((hdc))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglDeleteDCNV, (HDC hdc))
#ifndef wglEnumGpuDevicesNV
#define wglEnumGpuDevicesNV(hGpu, iDeviceIndex, lpGpuDevice) glatter_wglEnumGpuDevicesNV((hGpu), (iDeviceIndex), (lpGpuDevice))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglEnumGpuDevicesNV, (HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice))
#ifndef wglEnumGpusFromAffinityDCNV
#define wglEnumGpusFromAffinityDCNV(hAffinityDC, iGpuIndex, hGpu) glatter_wglEnumGpusFromAffinityDCNV((hAffinityDC), (iGpuIndex), (hGpu))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglEnumGpusFromAffinityDCNV, (HDC hAffinityDC, UINT iGpuIndex, HGPUNV *hGpu))
#ifndef wglEnumGpusNV
#define wglEnumGpusNV(iGpuIndex, phGpu) glatter_wglEnumGpusNV((iGpuIndex), (phGpu))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglEnumGpusNV, (UINT iGpuIndex, HGPUNV *phGpu))
#endif // defined(WGL_NV_gpu_affinity)
#if defined(WGL_NV_present_video)
#ifndef wglBindVideoDeviceNV
#define wglBindVideoDeviceNV(hDC, uVideoSlot, hVideoDevice, piAttribList) glatter_wglBindVideoDeviceNV((hDC), (uVideoSlot), (hVideoDevice), (piAttribList))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglBindVideoDeviceNV, (HDC hDC, unsigned int uVideoSlot, HVIDEOOUTPUTDEVICENV hVideoDevice, const int *piAttribList))
#ifndef wglEnumerateVideoDevicesNV
#define wglEnumerateVideoDevicesNV(hDC, phDeviceList) glatter_wglEnumerateVideoDevicesNV((hDC), (phDeviceList))
#endif
GLATTER_UBLOCK(int, WINAPI, wglEnumerateVideoDevicesNV, (HDC hDC, HVIDEOOUTPUTDEVICENV *phDeviceList))
#ifndef wglQueryCurrentContextNV
#define wglQueryCurrentContextNV(iAttribute, piValue) glatter_wglQueryCurrentContextNV((iAttribute), (piValue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQueryCurrentContextNV, (int iAttribute, int *piValue))
#endif // defined(WGL_NV_present_video)
#if defined(WGL_NV_swap_group)
#ifndef wglBindSwapBarrierNV
#define wglBindSwapBarrierNV(group, barrier) glatter_wglBindSwapBarrierNV((group), (barrier))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglBindSwapBarrierNV, (GLuint group, GLuint barrier))
#ifndef wglJoinSwapGroupNV
#define wglJoinSwapGroupNV(hDC, group) glatter_wglJoinSwapGroupNV((hDC), (group))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglJoinSwapGroupNV, (HDC hDC, GLuint group))
#ifndef wglQueryFrameCountNV
#define wglQueryFrameCountNV(hDC, count) glatter_wglQueryFrameCountNV((hDC), (count))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQueryFrameCountNV, (HDC hDC, GLuint *count))
#ifndef wglQueryMaxSwapGroupsNV
#define wglQueryMaxSwapGroupsNV(hDC, maxGroups, maxBarriers) glatter_wglQueryMaxSwapGroupsNV((hDC), (maxGroups), (maxBarriers))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQueryMaxSwapGroupsNV, (HDC hDC, GLuint *maxGroups, GLuint *maxBarriers))
#ifndef wglQuerySwapGroupNV
#define wglQuerySwapGroupNV(hDC, group, barrier) glatter_wglQuerySwapGroupNV((hDC), (group), (barrier))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQuerySwapGroupNV, (HDC hDC, GLuint *group, GLuint *barrier))
#ifndef wglResetFrameCountNV
#define wglResetFrameCountNV(hDC) glatter_wglResetFrameCountNV((hDC))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglResetFrameCountNV, (HDC hDC))
#endif // defined(WGL_NV_swap_group)
#if defined(WGL_NV_vertex_array_range)
#ifndef wglAllocateMemoryNV
#define wglAllocateMemoryNV(size, readfreq, writefreq, priority) glatter_wglAllocateMemoryNV((size), (readfreq), (writefreq), (priority))
#endif
GLATTER_UBLOCK(void *, WINAPI, wglAllocateMemoryNV, (GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority))
#ifndef wglFreeMemoryNV
#define wglFreeMemoryNV(pointer) glatter_wglFreeMemoryNV((pointer))
#endif
GLATTER_UBLOCK(void, WINAPI, wglFreeMemoryNV, (void *pointer))
#endif // defined(WGL_NV_vertex_array_range)
#if defined(WGL_NV_video_capture)
#ifndef wglBindVideoCaptureDeviceNV
#define wglBindVideoCaptureDeviceNV(uVideoSlot, hDevice) glatter_wglBindVideoCaptureDeviceNV((uVideoSlot), (hDevice))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglBindVideoCaptureDeviceNV, (UINT uVideoSlot, HVIDEOINPUTDEVICENV hDevice))
#ifndef wglEnumerateVideoCaptureDevicesNV
#define wglEnumerateVideoCaptureDevicesNV(hDc, phDeviceList) glatter_wglEnumerateVideoCaptureDevicesNV((hDc), (phDeviceList))
#endif
GLATTER_UBLOCK(UINT, WINAPI, wglEnumerateVideoCaptureDevicesNV, (HDC hDc, HVIDEOINPUTDEVICENV *phDeviceList))
#ifndef wglLockVideoCaptureDeviceNV
#define wglLockVideoCaptureDeviceNV(hDc, hDevice) glatter_wglLockVideoCaptureDeviceNV((hDc), (hDevice))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglLockVideoCaptureDeviceNV, (HDC hDc, HVIDEOINPUTDEVICENV hDevice))
#ifndef wglQueryVideoCaptureDeviceNV
#define wglQueryVideoCaptureDeviceNV(hDc, hDevice, iAttribute, piValue) glatter_wglQueryVideoCaptureDeviceNV((hDc), (hDevice), (iAttribute), (piValue))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglQueryVideoCaptureDeviceNV, (HDC hDc, HVIDEOINPUTDEVICENV hDevice, int iAttribute, int *piValue))
#ifndef wglReleaseVideoCaptureDeviceNV
#define wglReleaseVideoCaptureDeviceNV(hDc, hDevice) glatter_wglReleaseVideoCaptureDeviceNV((hDc), (hDevice))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglReleaseVideoCaptureDeviceNV, (HDC hDc, HVIDEOINPUTDEVICENV hDevice))
#endif // defined(WGL_NV_video_capture)
#if defined(WGL_NV_video_output)
#ifndef wglBindVideoImageNV
#define wglBindVideoImageNV(hVideoDevice, hPbuffer, iVideoBuffer) glatter_wglBindVideoImageNV((hVideoDevice), (hPbuffer), (iVideoBuffer))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglBindVideoImageNV, (HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer, int iVideoBuffer))
#ifndef wglGetVideoDeviceNV
#define wglGetVideoDeviceNV(hDC, numDevices, hVideoDevice) glatter_wglGetVideoDeviceNV((hDC), (numDevices), (hVideoDevice))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetVideoDeviceNV, (HDC hDC, int numDevices, HPVIDEODEV *hVideoDevice))
#ifndef wglGetVideoInfoNV
#define wglGetVideoInfoNV(hpVideoDevice, pulCounterOutputPbuffer, pulCounterOutputVideo) glatter_wglGetVideoInfoNV((hpVideoDevice), (pulCounterOutputPbuffer), (pulCounterOutputVideo))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetVideoInfoNV, (HPVIDEODEV hpVideoDevice, unsigned long *pulCounterOutputPbuffer, unsigned long *pulCounterOutputVideo))
#ifndef wglReleaseVideoDeviceNV
#define wglReleaseVideoDeviceNV(hVideoDevice) glatter_wglReleaseVideoDeviceNV((hVideoDevice))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglReleaseVideoDeviceNV, (HPVIDEODEV hVideoDevice))
#ifndef wglReleaseVideoImageNV
#define wglReleaseVideoImageNV(hPbuffer, iVideoBuffer) glatter_wglReleaseVideoImageNV((hPbuffer), (iVideoBuffer))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglReleaseVideoImageNV, (HPBUFFERARB hPbuffer, int iVideoBuffer))
#ifndef wglSendPbufferToVideoNV
#define wglSendPbufferToVideoNV(hPbuffer, iBufferType, pulCounterPbuffer, bBlock) glatter_wglSendPbufferToVideoNV((hPbuffer), (iBufferType), (pulCounterPbuffer), (bBlock))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglSendPbufferToVideoNV, (HPBUFFERARB hPbuffer, int iBufferType, unsigned long *pulCounterPbuffer, BOOL bBlock))
#endif // defined(WGL_NV_video_output)
#if defined(WGL_OML_sync_control)
#ifndef wglGetMscRateOML
#define wglGetMscRateOML(hdc, numerator, denominator) glatter_wglGetMscRateOML((hdc), (numerator), (denominator))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetMscRateOML, (HDC hdc, INT32 *numerator, INT32 *denominator))
#ifndef wglGetSyncValuesOML
#define wglGetSyncValuesOML(hdc, ust, msc, sbc) glatter_wglGetSyncValuesOML((hdc), (ust), (msc), (sbc))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglGetSyncValuesOML, (HDC hdc, INT64 *ust, INT64 *msc, INT64 *sbc))
#ifndef wglSwapBuffersMscOML
#define wglSwapBuffersMscOML(hdc, target_msc, divisor, remainder) glatter_wglSwapBuffersMscOML((hdc), (target_msc), (divisor), (remainder))
#endif
GLATTER_UBLOCK(INT64, WINAPI, wglSwapBuffersMscOML, (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder))
#ifndef wglSwapLayerBuffersMscOML
#define wglSwapLayerBuffersMscOML(hdc, fuPlanes, target_msc, divisor, remainder) glatter_wglSwapLayerBuffersMscOML((hdc), (fuPlanes), (target_msc), (divisor), (remainder))
#endif
GLATTER_UBLOCK(INT64, WINAPI, wglSwapLayerBuffersMscOML, (HDC hdc, int fuPlanes, INT64 target_msc, INT64 divisor, INT64 remainder))
#ifndef wglWaitForMscOML
#define wglWaitForMscOML(hdc, target_msc, divisor, remainder, ust, msc, sbc) glatter_wglWaitForMscOML((hdc), (target_msc), (divisor), (remainder), (ust), (msc), (sbc))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglWaitForMscOML, (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder, INT64 *ust, INT64 *msc, INT64 *sbc))
#ifndef wglWaitForSbcOML
#define wglWaitForSbcOML(hdc, target_sbc, ust, msc, sbc) glatter_wglWaitForSbcOML((hdc), (target_sbc), (ust), (msc), (sbc))
#endif
GLATTER_UBLOCK(BOOL, WINAPI, wglWaitForSbcOML, (HDC hdc, INT64 target_sbc, INT64 *ust, INT64 *msc, INT64 *sbc))
#endif // defined(__wgl_wglext_h_)
#endif // defined(WGL_OML_sync_control)
#endif // GLATTER_WGL

