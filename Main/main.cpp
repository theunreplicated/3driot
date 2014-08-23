#include <Windows.h>
#include "../window2/MessageLoop.h"
#include "my_gfx_rect.h"
#include "File_Parser.h"
#include "../window2/OpenGLContext.h"
#include "../window2/SysUtils_Load_Library.h"
#include "../window2/ApplicationWindow.cpp"
#define HIDE_IMG_STRUCT_FROM_MAIN
#define UNSCHOENER_STIL_BACKGROUND_COLOR_BLACK
//#define USE_GLESV2
#include "../window2/GLMain.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "Physics_Input_Data.h"
#include "../window2/WinUtils.h"

#ifdef USE_GLESV2
#include "../window2/egl_display_binding.cpp"
#endif
//#define TEST_MODE
//#define SCHLECHTER_STIL_KEIN_FULLSCREEN
#define SCHLECHTER_STIL_SHOW_WINDOW_AFTER_FINISHED
//jo,ma wissens dass es kein guter Stil ist,is gud
#define SCHLECHTER_STIL_FRAMED_WINDOW //NEBEN SCHLECHTEM STIL HIER AuCH NOCH SEHR SCHLECHT IMPLEMENTIERT,fast so wie der fullscreen code,k�nnte man afaik auch mit einem createwindow ohne die setwindowlongs erledigen(aber vllt. probleme mit anfangswert x0>hab ich jetzt auhc,null darf wohl nicht so genommen werden)
SysUtils_Load_Library *dll_opengl;
PROC __stdcall getProcAddresswglintf(LPCSTR name){

	return dll_opengl->get_ProcAddress(name);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message)
	{

	case WM_CREATE:
		
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE:

			PostQuitMessage(0);
			

		}
		return 0; break;
	case WM_CLOSE:
		PostQuitMessage(0); break;//Geht jetzt auch beim klick aufs x
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}

}	struct window_info{
	bool maximized;
	LONG style, ex_style;
	RECT window_rect;

};

//http://stackoverflow.com/questions/13078953/code-analysis-says-inconsistent-annotation-for-wwinmain-this-instance-has-no
inline int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int iCmdShow)
{
	Windows::ApplicationWindow*aw = new Windows::ApplicationWindow(hInstance, { "hey", "" }, { 500, 500 }, NULL, WndProc, { (HBRUSH)GetStockObject(BLACK_BRUSH) });
	HWND native_window_handle = aw->window_handle;
	//http://stackoverflow.com/questions/2382464/win32-full-screen-and-hiding-taskbar
	//CHromium source
#ifndef SCHLECHTER_STIL_KEIN_FULLSCREEN
	window_info saved_window_info_;
	saved_window_info_.maximized = !!::IsZoomed(native_window_handle);//ist es an dieser Stelle hier sicher nicht gezoomt
	if (saved_window_info_.maximized){//brauch man vllt. net immer
		::SendMessage(native_window_handle, WM_SYSCOMMAND, SC_RESTORE, 0);
	}
	saved_window_info_.style = GetWindowLong(native_window_handle, GWL_STYLE);
	saved_window_info_.ex_style = GetWindowLong(native_window_handle, GWL_EXSTYLE);
		GetWindowRect(native_window_handle, &saved_window_info_.window_rect);
		
#ifndef SCHLECHTER_STIL_FRAMED_WINDOW
		SetWindowLong(native_window_handle, GWL_STYLE,
			saved_window_info_.style & ~(WS_CAPTION | WS_THICKFRAME));//entfernt WS_CAPTION+ws_thickframe
		SetWindowLong(native_window_handle, GWL_EXSTYLE,
			saved_window_info_.ex_style & ~(WS_EX_DLGMODALFRAME |
			WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));//ist extended style
		//wenn ich das hier auskommentiere,kommt ein frame raus
#else
		SetWindowLong(native_window_handle, GWL_STYLE,
			saved_window_info_.style | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU);
#endif
		// On expand, if we're given a window_rect, grow to it, otherwise do
		// not resize.
		
			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			GetMonitorInfo(MonitorFromWindow(native_window_handle, MONITOR_DEFAULTTONEAREST),
				&monitor_info);//sucht wohl den richtigen Monitor aus,mit dem die APp am meisten(Schnittmenge) zu tun hat
			
			My_GFX_Rect window_rect(monitor_info.rcMonitor);
			SetWindowPos(native_window_handle, NULL, window_rect.x, window_rect.y,
				window_rect.width, window_rect.height,
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
#endif
#ifndef SCHLECHTER_STIL_SHOW_WINDOW_AFTER_FINISHED
	::ShowWindow(native_window_handle,SW_SHOW);
#endif
	//Window wird nun gezeigt,Fullscreen,ok


	Win_Utils*wn = new Win_Utils();
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);//path von exe//da assimp wohl den include path auf desktop setzt irgendwie?
	std::string dir_path = wn->getdirpath(path);
	std::string fpath = dir_path +"\\"+ "scene.shotgun";
	FileParser*ps = new FileParser(fpath);

	std::vector<THREEDObject> obj=ps->parse();
	glm::mat4 dummy_mat = glm::mat4();
	for (THREEDObject& v : obj){
		
		v.matrix = dummy_mat;
	}


	RECT current_window_rect;
	::GetClientRect(native_window_handle, &current_window_rect);
	//float current_resolution_w = ::GetSystemMetrics(SM_CXSCREEN);//window breite
	//float current_resolution_h = ::GetSystemMetrics(SM_CYSCREEN);
	float current_resolution_w = current_window_rect.right;//@TODO:width und height von window
	float current_resolution_h = current_window_rect.bottom;
#ifndef USE_GLESV2
	dll_opengl = new SysUtils_Load_Library("opengl32.dll");
	sd_wgl_getProcAddress gl_layer_getProcAddress = dll_opengl->import<sd_wgl_getProcAddress>("wglGetProcAddress");
	OpenGLContext*ctx = new OpenGLContext(native_window_handle, dll_opengl);
	OpenGLImport imp(gl_layer_getProcAddress, getProcAddresswglintf);
	GLMain<swapBuffersFunc, OpenGLContext, THREEDObject> *glmain = new GLMain<swapBuffersFunc, OpenGLContext, THREEDObject>(&OpenGLContext::SwapBuffers, ctx,true);
#else
	//@TODO:separate swapbuffers func ohne das mit den templates
	EGL_Display_Binding *g_display = new EGL_Display_Binding(::GetDC(native_window_handle), native_window_handle);
	g_display->createContext();
	
	std::string path22 = dir_path + "\\" + "libGLESv2.dll";//dynamisches dll laden jedoch langsamer als mit __declspec(dllimport)
	dll_opengl = new SysUtils_Load_Library(path22.c_str());//@TODO:verwendet standard dll,nicht die ,die ich will,also plus path
	OpenGLImport imp(getProcAddresswglintf, getProcAddresswglintf/*eigentlich egl*/);
	GLMain<EGLswapBuffersFunc, EGL_Display_Binding, THREEDObject> *glmain = new GLMain<EGLswapBuffersFunc, EGL_Display_Binding, THREEDObject>(&EGL_Display_Binding::swapBuffers,g_display,false);
#endif
	
	glm::mat4 matt2 = glm::perspective(45.0f, (current_resolution_w / current_resolution_h), 0.01f, 5000.0f);
	glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 camera_mat = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
		);



	glmain->setViewPort({current_resolution_w,current_resolution_h,0,0});//@TODO:vierpoer teste,das hier l�schen
#ifndef TEST_MODE
	glmain->draw_elements = obj;//draw elemente setzen
	glmain->setCameraMatrix(camera_mat);
	glmain->setProjectionMatrix(matt2);
	glmain->setCameraTransformMatrix(model_mat);
#else
	
	std::vector<THREEDObject>objc;
	THREEDObject oha;
	oha.dm =kElements;
	oha.draw_call_num_elements = 6;
	oha.draw_primitive = PR_TRIANGLE;
	oha.enable_matrix = false;
	oha.matrix = glm::value_ptr(dummy_mat);
	oha.has_indices = true;
	oha.has_texture = true; oha.has_tex_coord = true;//zusammenfassung w�re nett
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
	oha.texture_data.format = GL_RGB;
	unsigned char * texture_bits = new unsigned char[3];
	texture_bits[0] = 255; texture_bits[1] = 0; texture_bits[2] = 0;
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
	
	
	//Physics::Main*ph = new Physics::Main();
	//ph->createStaticPlaneShape();
	//int num_vertices = glmain->draw_elements[0].vertices_totalsize / sizeof(float);
	//btVector3 * v = new btVector3[num_vertices / 3];
	//for (int i = 0; i < num_vertices/3; i++){
	//	v[i] = btVector3(glmain->draw_elements[0].vertices[(i * 3) + 0], glmain->draw_elements[0].vertices[(i * 3) + 1], glmain->draw_elements[0].vertices[(i * 3) + 2]);


	//}

	//ph->add_Mesh({ v, btQuaternion::getIdentity(), btVector3(50, 0, 0), (int*)glmain->draw_elements[0].indices, (glmain->draw_elements[0].indices_totalsize/sizeof(unsigned int))/3,num_vertices,1});

	//ph->simulate_ActionHandler(1/60.0f);
//	ph->simulate_AfterActionHandler_getTransform(0);

	glmain->initGL();
#ifdef SCHLECHTER_STIL_SHOW_WINDOW_AFTER_FINISHED
	::ShowWindow(native_window_handle, SW_SHOW);
#endif
	
	Windows::MessageLoop* ml = new Windows::MessageLoop();
	
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
		glmain->render();//@TODO:in proc am Schluss//geh�rt eigentlich in main loop,da z.z nur statusch hier �ber der main loop
		ml->Message_Pump();

	}
	return ml->Message_Pump_End();
	
}