#include "ApplicationWindow.h"
#include "MessageLoop.h"
#include "Window.h"
#include <Windows.h>
#include <stdio.h>
#include "ApplicationUI_Control_Mgr.h"
#include "file_dialog.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLContext.h"
#include "SysUtils_Load_Library.h"
#include "OpenGLImport.h"
#include "GLMain.h"
#include "Assimp_Mesh_Importer.h"
#include "Assimp_Utils_m_convert_16.h"
#include <stringapiset.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

glm::mat4 transformmat = glm::mat4(1.0f);
bool CLICK_FUNC(HWND global_wnd, WPARAM wParam, LPARAM lParam, HWND caller_wnd)
{
	
	return /*(lParam == (LPARAM)caller_wnd)&&*/(HIWORD(wParam) == BN_CLICKED);
	
	
}

void winproc_callback_function5(HWND hWnd, WPARAM wParam, LPARAM lParam){
	//MessageBox(NULL, "dd","cc", MB_OK);
	PAINTSTRUCT   ps;
	HDC           hDC;
	hDC = BeginPaint(hWnd, &ps);
	{RECT rect;
	rect.left = 40;
	rect.top = 10;
	const char* message = "My First Window";
	DrawText(hDC, message, -1, &rect, DT_SINGLELINE | DT_NOCLIP); }
}
void keydown(HWND hWnd, WPARAM wParam, LPARAM lParam){

	switch (wParam)
	{
	case VK_LEFT:transformmat/*or...*/ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); break;
	default:
		break;
	}
		

}
SysUtils_Load_Library *dll_opengl = new SysUtils_Load_Library("opengl32.dll");
PROC __stdcall getProcAddresswglintf(LPCSTR name){

	return dll_opengl->get_ProcAddress(name);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	using namespace Windows;
	int width=1024, height=768;
	ApplicationWindow*aw = new ApplicationWindow(hInstance, { "t1", "t2" }, { width, height }, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
	//Window*wedit = new Window(hInstance, { "edit", "freetext" }, { 155, 155 }, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE |ES_AUTOVSCROLL, aw);
	//Window*wbtn = new Window(hInstance, { "button", "button" }, { 555, 555,200,200 }, WS_CHILD | WS_VISIBLE, aw);
	aw->addOnMessageInvoke(WM_KEYDOWN,keydown);//WM_CREATE shafft er net


	//aw->addOnMessageInvoke(WM_PAINT,winproc_callback_function5);
	//MessageBox(NULL, wedit->Text_get(), wedit->Text_get(), MB_OK);

	winproc_promise_event BTN_CLICK = {CLICK_FUNC, WM_COMMAND, true /*default=false*/};
	//wbtn->on(BTN_CLICK,onclick);
	
	//erstelle controls am rechten Rand

	//dc->SaveFileName(L"C:\\");

	//aw->Position_set({1920,1080});
	ApplicationUI_Control_Mgr*uicontrol = new ApplicationUI_Control_Mgr(aw,width,height);
	uicontrol->addEditControls();
	uicontrol->addButtons(BTN_CLICK);


	sd_wgl_getProcAddress gl_layer_getProcAddress = dll_opengl->import<sd_wgl_getProcAddress>("wglGetProcAddress");


	OpenGLContext*ctx = new OpenGLContext(uicontrol->static_draw_field->window_handle, dll_opengl);
	OpenGLImport imp(gl_layer_getProcAddress, getProcAddresswglintf);


	GLMain<swapBuffersFunc, OpenGLContext> *glm = new GLMain<swapBuffersFunc, OpenGLContext>(&OpenGLContext::SwapBuffers, ctx);
	glm->setViewPort(uicontrol->static_draw_field->Position_get()/*wohl so nicht richtig*/);
	//RECT lpp = uicontrol->static_draw_field->Rect_get();
	//glm->setViewPort({730,608});
	using Windows::Dialogs::File_Dialog;
	File_Dialog*dc = new File_Dialog();
	//dc->ofn.hwndOwner = aw->native_window_handle;//unnötig
	LPWSTR dcc = dc->OpenFileName(L"C:\\Users\\ultimateFORCE\\Desktop");
	Assimp_Mesh_Importer*aiimport; 
	
	if (*dcc/*!=*L""*/){///bei Abbruch==L""
		//open

		char buffer[MAX_PATH];

		// First arg is the pointer to destination char, second arg is
		// the pointer to source wchar_t, last arg is the size of char buffer
		//wcstom
		//wcstombs_s(buffer, dcc, MAX_PATH);
		size_t CharactersConverted = 0;
		wcstombs_s(&CharactersConverted, buffer, sizeof(buffer), dcc, _TRUNCATE);
		/*Assimp_Mesh_Importer**/aiimport = new Assimp_Mesh_Importer(buffer);
		//		Mesh_RenderObject o = *aiimport->stor_meshes_render[0];
		//Mesh_RenderObject oo = aiimport->get_render_obj(0);
		glm->setNumDrawElements(1);
		//float* mmmm = Assimp_Utils::convert_aiMatrix_to_float16(aiimport->ScaleAsset());
		using glm::mat4; using glm::scale; using glm::vec3;
		//mat4 scalematrix = scale(mat4(1.0f), vec3(0.5f));
		//float aspectRatio = uicontrol->static_draw_field->Position_get().width / uicontrol->static_draw_field->Position_get().height;
		Windows::WindowRect re = uicontrol->static_draw_field->Position_get();
		float aspectRatio = float(re.width)/float(re.height);
		//mat4 proj_matrix = glm::perspective(50.0f, aspectRatio, 0.1f, 50000.0f);
		//mat4 mat = proj_matrix*scalematrix;
			
			
		//mat4 model_matrix=glm::make_mat4(mmmm);
		//mat4 model_matrix = glm::translate(glm::mat4(),glm::vec3(-0.5f,-0.5f,0.5f));
		//mat4 model_matrix = glm::mat4(1.0f);
		//glm::mat4 View = glm::lookAt(
		//	glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		//	glm::vec3(0, 0, 0), // and looks at the origin
		//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		//	);
		//glm::mat4 finalm = proj_matrix*View*model_matrix;
		//glm::mat4 finalm = model_matrix;
		//glm->addMesh_RenderObject_struct(&aiimport->get_render_obj(0), glm::value_ptr(finalm));
		glm->initGL();
		
		//OutputDebugStringA(aiimport->stor_meshes_render[0]->node_name);
		//int d2 = oo.indices[2]
	}





		//(new MessageLoop())->GetMessage_Approach();
	MessageLoop* ml = new MessageLoop();
	while (ml->Message_Get()){
		//glm::mat4 mc = glm::mat4(1.0f)*transformmat;
		//glm->draw_elements[0].matrix = glm::value_ptr(mc);
		//float * mat = glm->draw_elements[0].matrix;
		//glm::mat4 m = glm::make_mat4(mat);
		//glm::mat4 mm = transformmat;
		//glm->draw_elements[0].matrix = glm::value_ptr(mm);
		//THREEDObject dc=glm->draw_elements[1];
		glm->render();//@TODO:in proc am Schluss
		ml->Message_Pump();
		
	}
	return ml->Message_Pump_End();
}