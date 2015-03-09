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
public:
	Physics::Main*physics_main;
	GLMain<swapBuffersFunc, OpenGLContext, THREEDObject>*m_glmain;
	std::vector<btTransform>transform_vorherige_daten;
	Physics_App_Handler(GLMain<swapBuffersFunc, OpenGLContext, THREEDObject>*glmain,HWND mwh);
	~Physics_App_Handler();
	void start();
	void stop();
};

