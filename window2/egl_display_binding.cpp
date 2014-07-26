

#include "egl_display_binding.h"

const char* EGL_Display_Binding::GetLastEGLErrorString() {
	EGLint error = eglGetError();//@src chromium
	switch (error) {
	case EGL_NOT_INITIALIZED:
		return "EGL_NOT_INITIALIZED";
	case EGL_SUCCESS:
		return "EGL_SUCCESS";
	case EGL_BAD_ACCESS:
		return "EGL_BAD_ACCESS";
	case EGL_BAD_ALLOC:
		return "EGL_BAD_ALLOC";
	case EGL_BAD_ATTRIBUTE:
		return "EGL_BAD_ATTRIBUTE";
	case EGL_BAD_CONTEXT:
		return "EGL_BAD_CONTEXT";
	case EGL_BAD_CONFIG:
		return "EGL_BAD_CONFIG";
	case EGL_BAD_CURRENT_SURFACE:
		return "EGL_BAD_CURRENT_SURFACE";
	case EGL_BAD_DISPLAY:
		return "EGL_BAD_DISPLAY";
	case EGL_BAD_SURFACE:
		return "EGL_BAD_SURFACE";
	case EGL_BAD_MATCH:
		return "EGL_BAD_MATCH";
	case EGL_BAD_PARAMETER:
		return "EGL_BAD_PARAMETER";
	case EGL_BAD_NATIVE_PIXMAP:
		return "EGL_BAD_NATIVE_PIXMAP";
	case EGL_BAD_NATIVE_WINDOW:
		return "EGL_BAD_NATIVE_WINDOW";
	default:
		return "UNKNOWN";
	}
}

void EGL_Display_Binding::swapBuffers()
{
	eglSwapBuffers(mDisplay, mSurface);
}
EGL_Display_Binding::EGL_Display_Binding(EGLNativeDisplayType device_context, EGLNativeWindowType native_window){
	mNativeDisplay = device_context;
	mNativeWindow = native_window;
	if (!mNativeDisplay)
	{
		MessageBox(NULL, "Getting n.window Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		//return false;
	}
	//@TODO:vieles hier ändern,dx11 möglich über egl param

	mDisplay = eglGetDisplay(mNativeDisplay);

	if (mDisplay == EGL_NO_DISPLAY)
	{//wird anscheinend nicht aufgerufen,ist auch klar
		mDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
		OutputDebugStringA("no display");
	}



	EGLint majorVersion, minorVersion;
	if (!eglInitialize(mDisplay, &majorVersion, &minorVersion))
	{
		MessageBox(NULL, "egl error init!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		OutputDebugStringA(GetLastEGLErrorString());
		// return false;
	}

	eglBindAPI(EGL_OPENGL_ES_API);
	if (eglGetError() != EGL_SUCCESS)
	{
		MessageBox(NULL, "egl bind Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		//return false;
	}


	mWidth = 500;
	mHeight = 500;
	mRedBits = 8;
	mGreenBits = 8;
	mBlueBits = 8;
	mAlphaBits = 8;
	mDepthBits = 8;

	//wohl optional,bllt. vorher das auch
	mStencilBits = 24;
	mMultisample = true;

};
bool EGL_Display_Binding::createContext(){

	const EGLint configAttributes[] =
	{
		EGL_RED_SIZE, (mRedBits >= 0) ? mRedBits : EGL_DONT_CARE,
		EGL_GREEN_SIZE, (mGreenBits >= 0) ? mGreenBits : EGL_DONT_CARE,
		EGL_BLUE_SIZE, (mBlueBits >= 0) ? mBlueBits : EGL_DONT_CARE,
		EGL_ALPHA_SIZE, (mAlphaBits >= 0) ? mAlphaBits : EGL_DONT_CARE,
		EGL_DEPTH_SIZE, (mDepthBits >= 0) ? mDepthBits : EGL_DONT_CARE,
		EGL_STENCIL_SIZE, (mStencilBits >= 0) ? mStencilBits : EGL_DONT_CARE,
		EGL_SAMPLE_BUFFERS, mMultisample ? 1 : 0,
		EGL_NONE
	};

	EGLint config_attribs_565[] = {
		EGL_BUFFER_SIZE, 16,
		EGL_BLUE_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_RED_SIZE, 5,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
		EGL_NONE
	};

	EGLint config_attribs_8888[] = {
		EGL_BUFFER_SIZE, 32,
		EGL_ALPHA_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
		EGL_NONE
	};//mit configattriblist failed,vllt.wegen egl_opengl_es_2_bit
	EGLint configAttribList[] =
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 8,
		EGL_STENCIL_SIZE, 8,
		EGL_SAMPLE_BUFFERS, 1,
		EGL_NONE
	};


	EGLint configCount;

	if (!eglGetConfigs(mDisplay, NULL, 0, &configCount))
	{
		MessageBox(NULL, "get config Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	if (!eglChooseConfig(mDisplay, config_attribs_8888, &mConfig, 1, &configCount) || (configCount != 1))
	{
		//glgeterror gibt kein error hier
		OutputDebugStringA(GetLastEGLErrorString());
		MessageBox(NULL, "choose config Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);



		return false;
	}

	eglGetConfigAttrib(mDisplay, mConfig, EGL_RED_SIZE, &mRedBits);
	eglGetConfigAttrib(mDisplay, mConfig, EGL_GREEN_SIZE, &mGreenBits);
	eglGetConfigAttrib(mDisplay, mConfig, EGL_BLUE_SIZE, &mBlueBits);
	eglGetConfigAttrib(mDisplay, mConfig, EGL_ALPHA_SIZE, &mBlueBits);
	eglGetConfigAttrib(mDisplay, mConfig, EGL_DEPTH_SIZE, &mDepthBits);
	eglGetConfigAttrib(mDisplay, mConfig, EGL_STENCIL_SIZE, &mStencilBits);

	EGLint samples;
	eglGetConfigAttrib(mDisplay, mConfig, EGL_SAMPLE_BUFFERS, &samples);
	mMultisample = (samples != 0);

	mSurface = eglCreateWindowSurface(mDisplay, mConfig, mNativeWindow, NULL);
	if (mSurface == EGL_NO_SURFACE)
	{
		eglGetError(); // Clear error
		mSurface = eglCreateWindowSurface(mDisplay, mConfig, NULL, NULL);
	}

	if (eglGetError() != EGL_SUCCESS)
	{
		MessageBox(NULL, "egl surface error!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return false;
	}



	const EGLint kContextAttributes[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,/*2 steht für m_cleintversion*/
		EGL_NONE
	};//http://src.chromium.org/svn/trunk/src/ui/gl/gl_context_egl.cc
	mContext = eglCreateContext(mDisplay, mConfig, NULL, kContextAttributes);
	OutputDebugStringA(GetLastEGLErrorString());///egl_bad_config
	if (eglGetError() != EGL_SUCCESS)
	{
		OutputDebugStringA(GetLastEGLErrorString());
		MessageBox(NULL, "creating egl COntext Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	eglMakeCurrent(mDisplay, mSurface, mSurface, mContext);
	if (eglGetError() != EGL_SUCCESS)
	{
		MessageBox(NULL, "making current egl COntext Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	return true;


};
