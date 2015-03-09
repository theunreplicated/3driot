#pragma once
#include "../window2/GLMain.h"
#include "../window2/OpenGLContext.h"
#include "../window2/GLStructs.h"
namespace Physics{
	class Main;
}
class Thread;
class btTransform;
class Physics_App_Handler
{
	
	//Thread*t;
	unsigned int old_pos=0;
public:
	DWORD m_renderer_thread_id; const UINT render_message;
	Physics::Main*physics_main;
	GLMain<swapBuffersFunc, OpenGLContext, THREEDObject>*m_glmain;
	std::vector<btTransform>transform_vorherige_daten;
	Physics_App_Handler(GLMain<swapBuffersFunc, OpenGLContext, THREEDObject>*glmain,HWND mwh,DWORD renderer_thread_id,const UINT render_command);
	~Physics_App_Handler();
	void start();
	void stop();
};

