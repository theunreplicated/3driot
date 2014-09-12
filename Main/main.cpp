#include <Windows.h>
#include "../window2/MessageLoop.h"

#include "File_Parser.h"
#include "../window2/OpenGLContext.h"
//#include "../window2/SysUtils_Load_Library.h"
#include "../window2/ApplicationWindow.h"
#define HIDE_IMG_STRUCT_FROM_MAIN
#define UNSCHOENER_STIL_BACKGROUND_COLOR_BLACK
//#define USE_GLESV2
//#define TEST_MODE
//#define SCHLECHTER_STIL_KEIN_FULLSCREEN
#define SCHLECHTER_STIL_SHOW_WINDOW_AFTER_FINISHED
//jo,ma wissens dass es kein guter Stil ist,is gud
#define SCHLECHTER_STIL_FRAMED_WINDOW //NEBEN SCHLECHTEM STIL HIER AuCH NOCH SEHR SCHLECHT IMPLEMENTIERT,fast so wie der fullscreen code,könnte man afaik auch mit einem createwindow ohne die setwindowlongs erledigen(aber vllt. probleme mit anfangswert x0>hab ich jetzt auhc,null darf wohl nicht so genommen werden)

#include "../window2/App_Initialize_Components.h"
//#include "../window2/GLMain.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Physics_Input_Data.h"
#include "../window2/WinUtils.h"





//http://stackoverflow.com/questions/13078953/code-analysis-says-inconsistent-annotation-for-wwinmain-this-instance-has-no
inline int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int iCmdShow)
{
	Windows::ApplicationWindow*aw = new Windows::ApplicationWindow(hInstance, { "hey", "" }, { 500, 500 }, NULL, Application::Basic_WndProc, { (HBRUSH)GetStockObject(BLACK_BRUSH) });
	HWND native_window_handle = aw->window_handle;
	Application::fullscreen(aw);
#ifndef SCHLECHTER_STIL_SHOW_WINDOW_AFTER_FINISHED
	::ShowWindow(native_window_handle,SW_SHOW);
#endif
	//Window wird nun gezeigt,Fullscreen,ok

	
	Win_Utils*wn = new Win_Utils();
		//path von exe//da assimp wohl den include path auf desktop setzt irgendwie?
	WCHAR *path55 = wn->getExePath();
	std::string dir_path = wn->getdirpath(path55);
	std::string fpath = dir_path +"\\"+ "scene.shotgun";
	FileParser*ps = new FileParser(fpath);

	std::vector<THREEDObject> obj=ps->parse();
	glm::mat4 dummy_mat = glm::mat4();
	for (THREEDObject& v : obj){
		
		v.matrix = dummy_mat;
	}


	Windows::WindowRect current_window_rect=aw->ClientRect_get();
	//@TODO:
	//float current_resolution_w = ::GetSystemMetrics(SM_CXSCREEN);//window breite
	//float current_resolution_h = ::GetSystemMetrics(SM_CYSCREEN);
	float current_resolution_w = current_window_rect.width;//@TODO:x und y koord auch auslesen
	float current_resolution_h = current_window_rect.height;
	GLMain<swapBuffersFunc, OpenGLContext, THREEDObject> *glmain = Application::setup_system_gl_opengl_layer<swapBuffersFunc, OpenGLContext, THREEDObject>(native_window_handle);
	

	
	glmain->setViewPort(current_window_rect);//@TODO:vierpoer teste,das hier löschen
#ifndef TEST_MODE
	//@TODO:das hier entfernen
	std::vector<THREEDObject> obj_c;//nicht objective-c
	obj_c.push_back(obj[0]);
	obj = obj_c;
	//entfernen ende
	glmain->draw_elements = obj;//draw elemente setzen
	Application::set_std_camera_projection_matrices(glmain, current_resolution_w, current_resolution_h);
#else
	
	std::vector<THREEDObject>objc;
	THREEDObject oha;
	oha.dm =kElements;
	oha.draw_call_num_elements = 6;
	oha.draw_primitive = PR_TRIANGLE;
	oha.enable_matrix = false;
	oha.matrix = dummy_mat;
	oha.has_indices = true;
	oha.has_texture = true; oha.has_tex_coord = true;//zusammenfassung wäre nett
	unsigned int indicessss[] = { 0, 1, 2, 0, 2, 3 };
	oha.indices =new unsigned int[sizeof(indicessss)/sizeof(unsigned int)] ;
	memcpy(oha.indices,indicessss,sizeof(indicessss));
	float verticesesesesel[] = { -1.0f, 1.0f, 0.0f ,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};
	oha.vertices = new float[sizeof(verticesesesesel) / sizeof(float)];
	memcpy(oha.vertices, verticesesesesel, sizeof(verticesesesesel));
	float texcoords666[] = {
		0.0f, 0.0f,
		0.0f,0.0f,
		0.0f,0.0f,
		0.0f,0.0f
	};
	oha.tex_coords = new float[sizeof(texcoords666)/sizeof(float)];
	memcpy(oha.tex_coords,texcoords666,sizeof(texcoords666));


	oha.indices_totalsize=sizeof(verticesesesesel);
	oha.texcoords_totalsize = sizeof(texcoords666);
	oha.texture_data.width = 1;
	oha.texture_data.height = 1;
	oha.texture_data.format = GL_RGBA;
	unsigned char * texture_bits = new unsigned char[4];
	texture_bits[0] = 255; texture_bits[1] = 255; texture_bits[2] = 0; texture_bits[3] = 1;
	oha.texture_data.bits = texture_bits;

	oha.vertices_totalsize = sizeof(verticesesesesel);
	objc.push_back(oha);
	glmain->draw_elements = objc;
	glmain->setCameraMatrix(dummy_mat);
	glmain->setProjectionMatrix(dummy_mat);
	//glm::vec3 scalessss=glm::vec3(0.2, 0.2, 0.2);
	glm::vec3 scalessss = glm::vec3(1.0,1.0,1.0);
	glmain->setCameraTransformMatrix(glm::scale(dummy_mat,scalessss));

#endif
	//for (THREEDObject& d : glmain->draw_elements){
	//	glm::mat4 matt = glm::mat4();
		//d.matrix = glm::value_ptr(matt);

	//}
	
	
	Physics::Main*ph = new Physics::Main();
	ph->createStaticPlaneShape();
	int num_vertices = glmain->draw_elements[0].vertices_totalsize / sizeof(float);
	btVector3 * v = new btVector3[num_vertices / 3];
	for (int i = 0; i < (num_vertices/3); i++){
		v[i] = btVector3(glmain->draw_elements[0].vertices[(i * 3) + 0], glmain->draw_elements[0].vertices[(i * 3) + 1], glmain->draw_elements[0].vertices[(i * 3) + 2]);


	}

	ph->add_Mesh({ v, btQuaternion::getIdentity(), btVector3(50, 50, 0), (int*)glmain->draw_elements[0].indices, (glmain->draw_elements[0].indices_totalsize/sizeof(unsigned int)),num_vertices,1});

	ph->simulate_ActionHandler(1/60.0f);
	btTransform trans=ph->simulate_AfterActionHandler_getTransform(0);
	float y_wert=trans.getOrigin().getY();
	
	glmain->initGL();
#ifdef SCHLECHTER_STIL_SHOW_WINDOW_AFTER_FINISHED
	::ShowWindow(native_window_handle, SW_SHOW);
#endif
	glmain->render();
	/*Windows::MessageLoop* ml = new Windows::MessageLoop();
	
	while (ml->Message_Get()){//@TODO:peekmessage
		//glm::mat4 transformmat = scalemat*rotmat;
		//glm::mat4 matt = matt2*camera_mat*model_mat;
		//	for (int i = 0; i < glm->num_draw_elements; i++){
		//glm->draw_elements[i].matrix = glm::value_ptr(matt);
		//}
	
		//glm->draw_elements[0].matrix = m.get_as_float16();
		//glm->draw_elements[0].matrix = glm::value_ptr(matt);
		//glm::mat4 mc = glm::mat4(1.0f)*transformmat;
		//glm->draw_elements[0].matrix = glm::value_ptr(mc);
		//float * mat = glm->draw_elements[0].matrix;
		//glm::mat4 m = glm::make_mat4(mat);
		//glm::mat4 mm = transformmat;
		//glm->draw_elements[0].matrix = glm::value_ptr(mm);
		//THREEDObject dc=glm->draw_elements[1];
		//Beo:bei den ersteren Draw Calls wird nix angezeigt//@TODO:fixen,wohl erst beim Zweiten?
		glmain->render();//@TODO:in proc am Schluss//gehört eigentlich in main loop,da z.z nur statusch hier über der main loop
		ml->Message_Pump();

	}
	return ml->Message_Pump_End();
*/
	//@TODO: bei case WM_PAINT zeichnen
	return (new Windows::MessageLoop)->GetMessage_Approach();
}