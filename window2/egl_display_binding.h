#pragma once
#include <EGL\egl.h>
#include <EGL\eglext.h>
#include <Windows.h>
class EGL_Display_Binding{//@TODO.vllt. umbenennen in EGLContext
private:
	EGLDisplay mDisplay;
	EGLConfig mConfig;
	EGLSurface mSurface;
	EGLContext mContext;
	int mClientVersion;
	int mWidth;
	int mHeight;
	int mRedBits;
	int mGreenBits;
	int mBlueBits;
	int mAlphaBits;
	int mDepthBits;
	int mStencilBits;
	bool mMultisample;

public:
	void swapBuffers();
	const char* GetLastEGLErrorString();
	EGLNativeDisplayType mNativeDisplay;
	EGLNativeWindowType mNativeWindow;
	EGL_Display_Binding(EGLNativeDisplayType device_context, EGLNativeWindowType native_window);
	bool createContext();

};
typedef void(EGL_Display_Binding::*EGLswapBuffersFunc)(void);