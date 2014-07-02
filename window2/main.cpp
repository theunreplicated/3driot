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
#include "Matrix.h"
#include <CommCtrl.h>
#include "3DObject_Serializer.h"
#include <ostream>
#include <sstream>
#include <fstream>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
HHOOK mouse_hook;
Windows::ApplicationWindow* aw;
glm::mat4 scalemat,rotmat = glm::mat4(1.0f);
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
	//case VK_LEFT:transformmat/*or...*/ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); break;
	case /*VK_OEM_PLUS*/107:scalemat/*or...*/ = glm::scale(scalemat, glm::vec3(2.0f, 2.0f, 2.0f)); break;
	case /*VK_OEM_MINUS*/109:scalemat/*or...*/ = glm::scale(scalemat, glm::vec3(0.5f, 0.5f, 0.5f)); break;
	case VK_LEFT:rotmat/*or...*/ = glm::rotate(rotmat, 15.0f, glm::vec3(0.0f, 1.0f, 0.0f)); break;
	case VK_RIGHT:rotmat/*or...*/ = glm::rotate(rotmat, -15.0f, glm::vec3(0.0f, 1.0f, 0.0f)); break;
	case VK_UP:rotmat/*or...*/ = glm::rotate(rotmat, 15.0f, glm::vec3(1.0f, 1.0f, 0.0f)); break;
	case VK_DOWN:rotmat/*or...*/ = glm::rotate(rotmat, -15.0f, glm::vec3(1.0f, 0.0f, 0.0f)); break;//todo:vllt.eigene matrizen

	default:
		break;
	}
		

}
void mousedown(HWND hWnd, WPARAM wParam, LPARAM lParam){//Quelle:irgendwo im INternet
	POINT p;
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(aw->native_window_handle, &mousePos);

	glm::mat4 matProjection = glm::perspective(45.0f,(1024.0f/768.0f),0.1f,3000.0f);
	glm::mat4 matInverse = glm::inverse(matProjection);
	float in[4];
	float winZ = 1.0;


	in[0] = (2.0f*((float)(mousePos.x - 0) / (1024 - 0))) - 1.0f,
		in[1] = 1.0f - (2.0f*((float)(mousePos.y - 0) / (768/*height*/ - 0)));
	in[2] = 2.0* winZ - 1.0;
	in[3] = 1.0;

	glm::vec4 vIn = glm::vec4(in[0], in[1], in[2], in[3]);
	glm::vec4 pos = vIn * matInverse;

	pos.w = 1.0 / pos.w;

	pos.x *= pos.w;
	pos.y *= pos.w;
	pos.z *= pos.w;


	new Windows::Window({ "button", "Click" }, { 175, 30, 30, 50 + 50 }, WS_CHILD | WS_VISIBLE, aw);
}
SysUtils_Load_Library *dll_opengl = new SysUtils_Load_Library("opengl32.dll");
PROC __stdcall getProcAddresswglintf(LPCSTR name){

	return dll_opengl->get_ProcAddress(name);
}
/*
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam)
{
	POINT p;
	if (wParam == WM_LBUTTONDOWN)
	{
		//new Windows::Window({ "button", "Click" }, { 175, 30, 30, 50 + 50 }, WS_CHILD | WS_VISIBLE,aw);
		GetCursorPos(&p);
	}

	//return CallNextHookEx(mouse_hook, code, wParam, lParam);
	return NULL;
}*/
bool cvtLPW2stdstring(std::string& s, const LPWSTR pw,
	UINT codepage = CP_ACP)
{
	bool res = false;
	char* p = 0;
	int bsz;
	bsz = WideCharToMultiByte(codepage,
		0,
		pw, -1,
		0, 0,
		0, 0);
	if (bsz > 0) {
		p = new char[bsz];
		int rc = WideCharToMultiByte(codepage,
			0,
			pw, -1,
			p, bsz,
			0, 0);
		if (rc != 0) {
			p[bsz - 1] = 0;
			s = p;
			res = true;
		}
	}
	delete[] p;
	return res;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	using namespace Windows;
	int width=1024, height=768;
	aw = new ApplicationWindow(hInstance, { "t1", "t2" }, { width, height }, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
	//Window*wedit = new Window(hInstance, { "edit", "freetext" }, { 155, 155 }, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE |ES_AUTOVSCROLL, aw);
	//Window*wbtn = new Window(hInstance, { "button", "button" }, { 555, 555,200,200 }, WS_CHILD | WS_VISIBLE, aw);
	aw->addOnMessageInvoke(WM_KEYDOWN,keydown);//WM_CREATE shafft er net
	aw->addOnMessageInvoke(WM_LBUTTONDOWN,mousedown);
	//mouse_hook=::SetWindowsHookEx(WH_MOUSE_LL,MouseProc,hInstance,0/*alle Threads*/);

	//aw->addOnMessageInvoke(WM_PAINT,winproc_callback_function5);
	//MessageBox(NULL, wedit->Text_get(), wedit->Text_get(), MB_OK);

	winproc_promise_event BTN_CLICK = {CLICK_FUNC, WM_COMMAND, true /*default=false*/};
	//wbtn->on(BTN_CLICK,onclick);
	
	//erstelle controls am rechten Rand

	//dc->SaveFileName(L"C:\\");

	//aw->Position_set({1920,1080});

	InitCommonControls(); // Force the common controls DLL to be loaded.
	HWND list;
	//http://stackoverflow.com/questions/13979371/win32-api-listview-creation-c
	// window is a handle to my window that is already created.
	int lwidth = 200; int lheight = 200;
	list = CreateWindowExW(0, WC_LISTVIEWW, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT, width - lwidth, 0, lwidth, lheight, aw->native_window_handle, NULL, NULL, NULL);

	/*LVCOLUMN lvc;
	//lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.iSubItem = 0;
	lvc.pszText = "Tdsdsadsitle";
	lvc.cx = 50;
	lvc.fmt = LVCFMT_LEFT;
	ListView_InsertColumn(list, 0, &lvc);
	http://www.cplusplus.com/forum/windows/47702/
	//http://stackoverflow.com/questions/3217362/adding-items-to-a-listview

	*/
	//http://stackoverflow.com/questions/11923925/disable-horizontal-scroll-bar-in-list-view
	//LONG lStyle = GetWindowLong(list, GWL_STYLE);
	//lStyle |=WS_VSCROLL;
	//SetWindowLong(list, GWL_STYLE, lStyle);
	LVCOLUMN lvc;
	
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.cx = lwidth;
	lvc.pszText = TEXT("Property");
	ListView_InsertColumn(list, 0, &lvc);

	//lvc.cx = 500;
	//lvc.pszText = TEXT("Value");
	//ListView_InsertColumn(list, 1, &lvc);

	LVITEM lvi;

	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	lvi.pszText = TEXT("File Name");
	ListView_InsertItem(list, &lvi);
	lvi.iItem = 1; 
	lvi.pszText = TEXT("File Size");
	ListView_InsertItem(list, &lvi);
	for (int i = 2; i < 100; i++){
		lvi.iItem = i;
		ListView_InsertItem(list, &lvi);
	}



	//ListView_SetItemText(list, 0, 1, TEXT("123425244525"));
	ApplicationUI_Control_Mgr*uicontrol = new ApplicationUI_Control_Mgr(aw,width,height);
	//uicontrol->addEditControls();
	//uicontrol->addButtons(BTN_CLICK);

	sd_wgl_getProcAddress gl_layer_getProcAddress = dll_opengl->import<sd_wgl_getProcAddress>("wglGetProcAddress");


	OpenGLContext*ctx = new OpenGLContext(uicontrol->static_draw_field->window_handle, dll_opengl);
	OpenGLImport imp(gl_layer_getProcAddress, getProcAddresswglintf);


	GLMain<swapBuffersFunc, OpenGLContext> *glm = new GLMain<swapBuffersFunc, OpenGLContext>(&OpenGLContext::SwapBuffers, ctx);
	//glm->setViewPort(uicontrol->static_draw_field->Position_get()/*wohl so nicht richtig*/);
	//RECT lpp = uicontrol->static_draw_field->Rect_get();
	RECT pos = uicontrol->static_draw_field->Rect_get();
	glm->setViewPort({pos.bottom,pos.right});
	using Windows::Dialogs::File_Dialog;
	File_Dialog*dc = new File_Dialog();
	//dc->ofn.hwndOwner = aw->native_window_handle;//unnötig
	
	Assimp_Mesh_Importer*aiimport; 
	Windows::WindowRect re = uicontrol->static_draw_field->Position_get();
	float aspectRatio = float(re.width) / float(re.height);//@TODO:mit Rect

	glm::mat4 matt2 = glm::perspective(45.0f, (1024.0f / 768.0f), 0.01f, 5000.0f);
	glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 camera_mat = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
		);
	glm::mat4 std_res = matt2*camera_mat;
	LPWSTR dcc = dc->OpenFileName(L"C:\\Users\\ultimateFORCE\\Desktop");
	if (*dcc!=*L""){///bei Abbruch==L""
		//open
		
		char buffer[MAX_PATH];

		// First arg is the pointer to destination char, second arg is
		// the pointer to source wchar_t, last arg is the size of char buffer
		//wcstom
		//wcstombs_s(buffer, dcc, MAX_PATH);
		
		size_t CharactersConverted = 0;
		wcstombs_s(&CharactersConverted, buffer, sizeof(buffer), dcc, _TRUNCATE);

		/*std::wstring nnWString(MAX_PATH, 0);
		nnWString.resize(MAX_PATH);
		std::wstring ws = /*L"C:\\oo ga\\Dokument.obj"*//*dcc;
		std::string s(ws.begin(), ws.end());
		const char*dch = s.c_str();
		*/
		
		//std::setlocale(LC_ALL, "en_US.utf8");
		// UTF-8 narrow multibyte encoding
		//const wchar_t* wstr = L"z\u00df\u6c34\U0001d10b"; // or L"zß水𝄋"
		
		aiimport = new Assimp_Mesh_Importer(buffer);
		//		Mesh_RenderObject o = *aiimport->stor_meshes_render[0];
		//Mesh_RenderObject oo = aiimport->get_render_obj(0);
	
		//float* mmmm = Assimp_Utils::convert_aiMatrix_to_float16(aiimport->ScaleAsset());
		using glm::mat4; using glm::scale; using glm::vec3;
		//mat4 scalematrix = scale(mat4(1.0f), vec3(0.5f));
		//float aspectRatio = uicontrol->static_draw_field->Position_get().width / uicontrol->static_draw_field->Position_get().height;
		
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
		glm->setNumDrawElements(aiimport->stor_meshes_render.size());
		for (int i = 0; i < aiimport->stor_meshes_render.size(); i++){
			glm->addMesh_RenderObject_struct(&aiimport->get_render_obj(i),glm::value_ptr(std_res));
		}
		
		
		//OutputDebugStringA(aiimport->stor_meshes_render[0]->node_name);
		//int d2 = oo.indices[2]
	}
	
	glm->initGL();
	delete aiimport;
	THREED_Object_Serializer*tosz = new THREED_Object_Serializer();
	std::string data=tosz->serialize(glm->draw_elements,1);

	std::ofstream fs;
	fs.open("file.shotgun");

	fs << "hey";//http://www.cplusplus.com/reference/fstream/fstream/open/
	fs.close();


		//(new MessageLoop())->GetMessage_Approach();
	MessageLoop* ml = new MessageLoop();
	Matrix proj_matrix,model_matrix;
	proj_matrix.perspective(199, aspectRatio, 0.01f, 5000.0f);
	float v = 0.75f;
	model_matrix.scale(Vector3(v,v,v));
	Matrix m1 = proj_matrix.multiply_with(model_matrix);
	//Matrix m = m1.multiply_with(glm->m);
	Matrix m = proj_matrix;
	
	
	
//	glm::mat4 matt = glm::mat4();
	//m.rotate(Quaternion(0.0f, 0.0f, 1.0f, 45));
	while (ml->Message_Get()){
		glm::mat4 transformmat = scalemat*rotmat;
		glm::mat4 matt = matt2*camera_mat*model_mat*transformmat;
		for (int i = 0; i < glm->num_draw_elements; i++){
			glm->draw_elements[i].matrix = glm::value_ptr(matt);
		}
		//glm->draw_elements[0].matrix = m.get_as_float16();
		//glm->draw_elements[0].matrix = glm::value_ptr(matt);
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