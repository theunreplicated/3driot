#include "Physics_App_Handler.h"
#include "../Main/Physics_Input_Data.h"
#include "../window2/Thread.h"
#include "../gyp_workspace2/my_defined_messages.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
Physics_App_Handler*phandler;
HANDLE thread_end_event;
HWND main_window_handle;

DWORD WINAPI physics_thread(void*dummy_arg){
	while (true){
		phandler->physics_main->simulate_ActionHandler(1 / 1.0f);//typisch:1/60.0f=>60frames
		for (unsigned int i = 0; i < phandler->physics_main->fallRigidBodies.size(); i++){
			//einfach jetzt mal rigidbody-id->mesh id

			btTransform transform = phandler->physics_main->simulate_AfterActionHandler_getTransform(i);
			//nun Differenz berechnen
			btVector3 aktueller = transform.getOrigin();
			btVector3 vorheriger = phandler->transform_vorherige_daten[i].getOrigin();
			//zuerst nur mal x,y,z
			phandler->m_glmain->draw_elements[i].matrix = glm::translate(phandler->m_glmain->draw_elements[i].matrix, glm::vec3(
				aktueller.getX() - vorheriger.getX(), aktueller.getY() - vorheriger.getY(), aktueller.getZ() - vorheriger.getZ()));



			phandler->transform_vorherige_daten[i] = transform;
		}

		::Sleep(5000);//@TODO:wegmachen,nur zum testen

		::PostMessage(main_window_handle,MY_MSG_RENDER, 0, 0);//@TODO:delay render messages
		int err = GetLastError();

		if (::WaitForSingleObject(thread_end_event, 0) == WAIT_OBJECT_0){
			::ResetEvent(thread_end_event);
			return 0;

		}

	}
	return 0;

}
Physics_App_Handler::Physics_App_Handler(GLMain<swapBuffersFunc, OpenGLContext, THREEDObject>*glmain,HWND mwh) :m_glmain(glmain)
{
	main_window_handle = mwh;
	thread_end_event = Threading::event_create();
	::ResetEvent(thread_end_event);
	phandler = this;
	physics_main = new Physics::Main();
	physics_main->createStaticPlaneShape();
}


Physics_App_Handler::~Physics_App_Handler()
{
}

void Physics_App_Handler::start(){
	btQuaternion rotation = btQuaternion(0, 0, 0, 1);//@TODO:rotation richtig machem,das hier nacher entfernen
	btVector3 default_position = btVector3(0, 50, 0);
	btScalar default_mass = 3;
	for (auto& de : m_glmain->draw_elements){
		int num_vertices = de.vertices_totalsize;
		//::MessageBoxA(NULL, std::to_string(de.vertices_totalsize).c_str(), "dsads", MB_OK);
		physics_main->add_Mesh({ de.vertices, rotation, default_position, de.indices, de.indices_totalsize / sizeof(unsigned int), de.vertices_totalsize / sizeof(float), default_mass }, PHY_INTEGER);
		transform_vorherige_daten.push_back(btTransform(rotation,default_position));
	}

	Thread t(physics_thread);

}
void Physics_App_Handler::stop(){
	::SetEvent(thread_end_event);

}