#include <Windows.h>
#include "../window2/MessageLoop.cpp"
#include "my_gfx_rect.h"
#include "File_Parser.h"
#include "../window2/OpenGLContext.cpp"
#include "../window2/SysUtils_Load_Library.cpp"
#define HIDE_IMG_STRUCT_FROM_MAIN
#define UNSCHOENER_STIL_BACKGROUND_COLOR_BLACK
#include "../window2/GLMain.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Physics_Input_Data.h"
//#define SCHLECHTER_STIL_SHOW_WINDOW_AFTER_FINISHED
SysUtils_Load_Library *dll_opengl;
PROC __stdcall getProcAddresswglintf(LPCSTR name){

	return dll_opengl->get_ProcAddress(name);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message)
	{

	case WM_CREATE:

		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_DESTROY:
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;

		}
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}

}	struct window_info{
	bool maximized;
	LONG style, ex_style;
	RECT window_rect;

};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASS wc;
	LPCSTR className = "hey";
	LPCSTR windowName = "hey";
	// register window class
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//einfach IDC_* ändern
	//	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//win-api.de
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	RegisterClass(&wc);

	//int sz=GetSystemMetrics(SM_CXSIZE);
	HWND native_window_handle = CreateWindow(
		className, windowName,
		NULL,
		0,0, 200, 200,
		NULL, NULL, hInstance, NULL);

	//http://stackoverflow.com/questions/2382464/win32-full-screen-and-hiding-taskbar
	//CHromium source
	window_info saved_window_info_;
	saved_window_info_.maximized = !!::IsZoomed(native_window_handle);
	if (saved_window_info_.maximized)
		::SendMessage(native_window_handle, WM_SYSCOMMAND, SC_RESTORE, 0);
	saved_window_info_.style = GetWindowLongA(native_window_handle, GWL_STYLE);
	saved_window_info_.ex_style = GetWindowLong(native_window_handle, GWL_EXSTYLE);
		GetWindowRect(native_window_handle, &saved_window_info_.window_rect);


		SetWindowLong(native_window_handle, GWL_STYLE,
			saved_window_info_.style & ~(WS_CAPTION | WS_THICKFRAME));
		SetWindowLong(native_window_handle, GWL_EXSTYLE,
			saved_window_info_.ex_style & ~(WS_EX_DLGMODALFRAME |
			WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

		// On expand, if we're given a window_rect, grow to it, otherwise do
		// not resize.
		
			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			GetMonitorInfo(MonitorFromWindow(native_window_handle, MONITOR_DEFAULTTONEAREST),
				&monitor_info);
			
			My_GFX_Rect window_rect(monitor_info.rcMonitor);
			SetWindowPos(native_window_handle, NULL, window_rect.x, window_rect.y,
				window_rect.width, window_rect.height,
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

#ifndef SCHLECHTER_STIL_SHOW_WINDOW_AFTER_FINISHED
	::ShowWindow(native_window_handle,SW_SHOW);
#endif
	//Window wird nun gezeigt,Fullscreen,ok

	FileParser*ps = new FileParser("scene.shotgun");
	std::vector<THREEDObject> obj=ps->parse();
	glm::mat4 dummy_mat = glm::mat4();
	for (THREEDObject& v : obj){
		
		v.matrix = glm::value_ptr(dummy_mat);

	}
	



	dll_opengl = new SysUtils_Load_Library("opengl32.dll");
	sd_wgl_getProcAddress gl_layer_getProcAddress = dll_opengl->import<sd_wgl_getProcAddress>("wglGetProcAddress");
	OpenGLContext*ctx = new OpenGLContext(native_window_handle, dll_opengl);
	OpenGLImport imp(gl_layer_getProcAddress, getProcAddresswglintf);
	GLMain<swapBuffersFunc, OpenGLContext, THREEDObject> *glmain = new GLMain<swapBuffersFunc, OpenGLContext, THREEDObject>(&OpenGLContext::SwapBuffers, ctx);
	glm::mat4 matt2 = glm::perspective(45.0f, (1920.0f / 1080.0f), 0.01f, 5000.0f);
	glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 camera_mat = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
		);

	glm::mat4 std_res = matt2*camera_mat;
	//glmain->setCameraandProjMatrix(std_res);
	glmain->draw_elements = obj;// glmain->draw_elements.push_back(myobj);
	glmain->setCameraMatrix(camera_mat);
	glmain->setProjectionMatrix(matt2);
	glmain->setCameraTransformMatrix(model_mat);
	//for (THREEDObject& d : glmain->draw_elements){
	//	glm::mat4 matt = glm::mat4();
		//d.matrix = glm::value_ptr(matt);

	//}
	
	
	Physics::Main*ph = new Physics::Main();
	ph->createStaticPlaneShape();
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
	while (ml->Message_Get()){
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
		glmain->render();//@TODO:in proc am Schluss
		ml->Message_Pump();

	}
	(new Windows::MessageLoop())->GetMessage_Approach();
}