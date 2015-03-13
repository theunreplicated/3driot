#include "Physics_App_Handler.h"
#include "../Main/Physics_Input_Data.h"
#include "../window2/Thread.h"
#include "../gyp_workspace2/my_defined_messages.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
Physics_App_Handler*phandler;
HANDLE thread_end_event;
HWND main_window_handle;
DWORD alte_zeit = 0;
CRITICAL_SECTION glm_cs;
DWORD WINAPI physics_thread(void*dummy_arg){
	while (true){
		
		phandler->physics_main->simulate_ActionHandler(/*1 / 1.0f*/GetTickCount()-alte_zeit);//typisch:1/60.0f=>60frames
		alte_zeit = GetTickCount();//Das mit der Zeit stimmt ja net
		for (unsigned int i = 0; i < phandler->physics_main->fallRigidBodies.size(); i++){
			//einfach jetzt mal rigidbody-id->mesh id

			btTransform transform = phandler->physics_main->simulate_AfterActionHandler_getTransform(i);
			//nun Differenz berechnen
			btVector3 aktueller = transform.getOrigin();
			btVector3 vorheriger = phandler->transform_vorherige_daten[i].getOrigin();
			//zuerst nur mal x,y,z
			//::EnterCriticalSection(&glm_cs);
			phandler->m_glmain->draw_elements[i].matrix = glm::translate(phandler->m_glmain->draw_elements[i].matrix, glm::vec3(
				aktueller.getX() - vorheriger.getX(), aktueller.getY() - vorheriger.getY(), aktueller.getZ() - vorheriger.getZ()));
			//::LeaveCriticalSection(&glm_cs);


			phandler->transform_vorherige_daten[i] = transform;
		}

		//::Sleep(5000);//@TODO:wegmachen,nur zum testen


		//::PostMessage(main_window_handle,MY_MSG_RENDER, 0, 0);//@TODO:delay render messages
		::PostThreadMessage(phandler->m_renderer_thread_id,phandler->render_message,0,0);
		int err = GetLastError();

		if (::WaitForSingleObject(thread_end_event, 0) == WAIT_OBJECT_0){
			::ResetEvent(thread_end_event);
			return 0;

		}

	}
	return 0;

}
Physics_App_Handler::Physics_App_Handler(GLMain<swapBuffersFunc, OpenGLContext, THREEDObject>*glmain, HWND mwh, DWORD renderer_thread_id, const UINT render_command, CRITICAL_SECTION &acs_glamin_render_elements) :m_glmain(glmain),
physics_main(new Physics::Main()), render_message(render_command), m_renderer_thread_id(renderer_thread_id)
{
	glm_cs = acs_glamin_render_elements;
	main_window_handle = mwh;
	thread_end_event = Threading::event_create();
	::ResetEvent(thread_end_event);
	phandler = this;
	//physics_main = new Physics::Main();
	physics_main->createStaticPlaneShape();
}


Physics_App_Handler::~Physics_App_Handler()
{
}

void Physics_App_Handler::start(){
	btQuaternion rotation = btQuaternion(0, 0, 0, 1);//@TODO:rotation richtig machem,das hier nacher entfernen
	btVector3 default_position = btVector3(0, 50, 0);
	btScalar default_mass = 3;
	
	//for (auto& de : m_glmain->draw_elements){
	unsigned int pos;
	if (old_pos !=0){
		pos = old_pos;

	}
	else{ pos = 0; }
	for (unsigned int i = pos; i < m_glmain->draw_elements.size();i++){
		auto de = m_glmain->draw_elements[i];
		int num_vertices = de.vertices_totalsize;
		//::MessageBoxA(NULL, std::to_string(de.vertices_totalsize).c_str(), "dsads", MB_OK);
		physics_main->add_Mesh({ de.vertices, rotation, default_position, de.indices, de.indices_totalsize / sizeof(unsigned int), de.vertices_totalsize / sizeof(float), default_mass }, PHY_INTEGER);
		transform_vorherige_daten.push_back(btTransform(rotation,default_position));
	}
	old_pos = m_glmain->draw_elements.size();
	
	alte_zeit = GetTickCount();//ne murks-lösung
	Thread t(physics_thread);

}
void Physics_App_Handler::stop(){
	::SetEvent(thread_end_event);

}