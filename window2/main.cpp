﻿#include "ApplicationWindow.h"
#include "MessageLoop.h"
#include "Window.h"
#include <Windows.h>
#include <stdio.h>
#include <map>
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
//#include <stringapiset.h>
#include "Matrix.h"
#include <CommCtrl.h>
#include "3DObject_Serializer.h"
#include <ostream>
#include <sstream>
#include <fstream>
#include "Thread.h"
#include "WinUtils.h"
#include "GLStructs.h"
#include <stdio.h>
#include "APIs\OS\Win\UI_Controls\List_View.h"
#include "APIs\OS\Win\UI_Controls\Menu.h"
#include "APIs\OS\Win\UI_Controls\TrackBar.h"
#include "../gyp_workspace2/App_Initialize_Components.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

Windows::ApplicationWindow* aw;
ApplicationUI_Control_Mgr*uicontrol;
Win_Utils*wn;
List_View*lv;
HWND default_focus;
glm::mat4 scalemat,rotmat,translatemat = glm::mat4(1.0f);
vector<glm::mat4>scalemat_s, rotmat_s, translatemat_s;
glm::mat4 std_res = glm::mat4(1.0f);

GLMain<swapBuffersFunc,OpenGLContext, THREEDObject> * glmain;
struct sp_endp_type{ int startp, endp; unsigned int index; };
vector<sp_endp_type> startp_endp_list_objs;/*zum Gruppieren*/
sp_endp_type * current_obj_selection=nullptr;//@TODO:header controls winapi
bool CLICK_FUNC(HWND global_wnd, WPARAM wParam, LPARAM lParam, HWND caller_wnd)
{
	
	return /*(lParam == (LPARAM)caller_wnd)&&*/(HIWORD(wParam) == BN_CLICKED);
	
	
}
bool LISTVIEW_SELECT_FUNC(HWND global_wnd, WPARAM wParam, LPARAM lParam, HWND caller_wnd){
http://www.rohitab.com/discuss/topic/35738-c-win32-listview-clicking-an-item/
	LPNMHDR pa = reinterpret_cast<LPNMHDR>(lParam);//@kommt hier wirklich reinterpret_cast hin anstatt c-style?
	//das hier ist ein Einzeiler,erinnert mich an Einzeller
	//;//@TODO:vllt. gehts auch so mit dem lparam wie bei button


	return (pa->hwndFrom == caller_wnd) && ((pa->code == NM_CLICK) || (pa->code == NM_RETURN));
}


//__declspec(dllimport)bool saveToFile(const char* fileName, const char * data);//,-) piraten-smilie-einäugig für harte Jungs(so hart wie Piraten)
void winproc_callback_function5(HWND hWnd, WPARAM wParam, LPARAM lParam){
	MessageBox(NULL, "dd","cc", MB_OK);
	PAINTSTRUCT   ps;
	HDC           hDC;
	hDC = BeginPaint(hWnd, &ps);
	{RECT rect;
	rect.left = 40;//gdi
	rect.top = 10;
	const char* message = "hi";
	DrawText(hDC, message, -1, &rect, DT_SINGLELINE | DT_NOCLIP); }
}
void listview_handle_click(HWND hWnd, WPARAM wParam, LPARAM lParam){

	LPNMITEMACTIVATE lpNMItem = reinterpret_cast<LPNMITEMACTIVATE>(lParam);
	int clicked_item_number = lpNMItem->iItem;
	//::MessageBoxA(NULL,std::to_string(lpNMItem->iItem).c_str(),"fdfd",MB_OK);//Diagramme auf Klick bei Varialben Zustands-Veränderung(alle oder ausgewähleter Bereich) wären ganz nett hier
	if ((clicked_item_number!=0)&&(current_obj_selection!=nullptr/*@TODO:gucken ob das da hier und jetzt(oder auch später) entfernen*/)){
		current_obj_selection = &startp_endp_list_objs[clicked_item_number - 1/*@TODO:-1 entferen,da ihc ja noch den Default-Text habe*/];
		scalemat = scalemat_s[clicked_item_number - 1];
		translatemat = translatemat_s[clicked_item_number - 1];
		rotmat = rotmat_s[clicked_item_number - 1];
	}
	::SetFocus(default_focus);
	
	/*LPNMLVCUSTOMDRAW lpnmCustomdraw;
	NMCUSTOMDRAW nd;
	nd.dwItemSpec = clicked_item_number;
	//nd.lItemlParam=
	
	lpnmCustomdraw->nmcd = nd;
	::SendMessage(hWnd, WM_NOTIFY, wParam, (LPARAM)lpnmCustomdraw);*/
	}
//UNprojection vllt. so :in jedes Depth_Fragment wird eine eindeutige ID geschrieben,mouse-picking erst als letzten Draw-Schritt,dann checken bei welcher ID=>Objekt hersausfinden
//@TODO:focus fix bei listview
void assimp_import_file(const char* path){
	
	
	try{
	Assimp_Mesh_Importer*aiimport = new Assimp_Mesh_Importer(path);


	//		Mesh_RenderObject o = *aiimport->stor_meshes_render[0];
	//Mesh_RenderObject oo = aiimport->get_render_obj(0);

	//float* mmmm = Assimp_Utils::convert_aiMatrix_to_float16(aiimport->ScaleAsset());
	using glm::mat4; using glm::scale; using glm::vec3;
	//mat4 scalematrix = scale(mat4(1.0f), vec3(0.5f));
	//float aspectRatio = uicontrol->static_draw_field->Position_get().width / uicontrol->static_draw_field->Position_get().height;

	//glm::mat4 finalm = proj_matrix*View*model_matrix;
	//glm::mat4 finalm = model_matrix;
	//glm->setNumDrawElements(aiimport->stor_meshes_render.size());
	//for (int i = 0; i < aiimport->stor_meshes_render.size(); i++){
	//glm->addMesh_RenderObject_struct(&aiimport->get_render_obj(i),glm::value_ptr(std_res));
	//}
	if (aiimport->stor_meshes_render.size() > 0){//also nur falls mehr als 0 draw-bare Element(draw-bare das Wort gibts ja gar net,wer hätte das gedacht)
		int startp = glmain->draw_elements.size();
		for (Mesh_RenderObject d : aiimport->stor_meshes_render){
			//glmain->addMesh_RenderObject_struct(&d, glm::value_ptr(std_res));
			glmain->add_to_buffer_and_add_to_draw_list(&d, glm::value_ptr(std_res));
		}
		int endp = glmain->draw_elements.size();
		startp_endp_list_objs.push_back({ startp, endp, startp_endp_list_objs.size() });

		lv->items->add("Received complex command(contagious).mhhhh.");
		current_obj_selection = &startp_endp_list_objs[startp_endp_list_objs.size() - 1];//muss gesetzt werden,da ansonseten fail bei click wg. nullptr check,und es macht auch Sinn so
		scalemat_s.push_back(glm::mat4()); translatemat_s.push_back(glm::mat4()); rotmat_s.push_back(glm::mat4());
		glmain->render();
	}
	//delete aiimport
	}
	catch (const std::runtime_error& error)
	{
		::MessageBox(NULL, TEXT(error.what()), TEXT("Importing Meshes failed"), MB_OK);
	}

}

void action_dialog_onclick(HWND hWnd, WPARAM wParam, LPARAM lParam){
	Windows::Dialogs::File_Dialog dccs;
	LPWSTR dcc = dccs.OpenFileName(L"C:\\");
	
	if (*dcc != *L""){///bei Abbruch==L""
		//open
		char buffer[MAX_PATH];

		
	
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

		assimp_import_file(buffer);
		//OutputDebugStringA(aiimport->stor_meshes_render[0]->node_name);
		//int d2 = oo.indices[2]
	}
	
}
void ui_close_window(HWND hWnd, WPARAM wParam, LPARAM lParam){

	::PostQuitMessage(0);
}
void action_save_state(HWND hWnd, WPARAM wParam, LPARAM lParam){
	//::MessageBoxA(NULL,"fds","dfd",MB_ICONASTERISK);
	THREED_Object_Serializer*tosz = new THREED_Object_Serializer();
	std::string data = tosz->serialize(glmain->draw_elements);
	//ShellExecute(NULL,"open","cmd.exe","fsutil file createnew test.txt 52428800",NULL,SW_SHOWDEFAULT);

	wn = new Win_Utils();
	std::string paths = wn->getdirpath(wn->getExePath());
	std::string dingens_ding_path = "\\";
	std::string finalpath = paths + dingens_ding_path + "scene.shotgun";
	wn->saveToFile(finalpath.c_str(), data.c_str());
	delete wn;
}



	
void keydown(HWND hWnd, WPARAM wParam, LPARAM lParam){
	//funktionsaufrufe gruppieren wäre bei vector nett,vor allem bei push_back,z.b. sowas[scalemat,translatemat].push_back(glm::mat4)
	//Das hier mit dem Keydown handling mit matrizen usw. ist alles schlimmer Murks so wie ichs gecodet, habe,daher @TODO:viel besser machen
	if (current_obj_selection != nullptr){
		scalemat = scalemat_s[current_obj_selection->index];
		rotmat = rotmat_s[current_obj_selection->index];
		translatemat = translatemat_s[current_obj_selection->index];
	
	switch (wParam)
	{
	//case VK_LEFT:transformmat/*or...*/ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); break;
	case /*VK_OEM_PLUS*/107:scalemat/*or...*/ = glm::scale(scalemat, glm::vec3(2.0f, 2.0f, 2.0f)); break;
	case /*VK_OEM_MINUS*/109:scalemat/*or...*/ = glm::scale(scalemat, glm::vec3(0.5f, 0.5f, 0.5f)); break;
	case VK_RIGHT:rotmat/*or...*/ = glm::rotate(rotmat, 15.0f, glm::vec3(0.0f, 1.0f, 0.0f)); break;
	case VK_LEFT:rotmat/*or...*/ = glm::rotate(rotmat, -15.0f, glm::vec3(0.0f, 1.0f, 0.0f)); break;
	case VK_DOWN:rotmat/*or...*/ = glm::rotate(rotmat, 15.0f, glm::vec3(0.0f,0.0f, 1.0f)); break;
	case VK_UP:rotmat/*or...*/ = glm::rotate(rotmat, -15.0f, glm::vec3(0.0f, 0.0f, 1.0f)); break;//todo:vllt.eigene matrizen
	case VK_NUMPAD7:rotmat/*or...*/ = glm::rotate(rotmat, 15.0f, glm::vec3(1.0f, 0.0f, 0.0f)); break;
	case VK_NUMPAD9:rotmat/*or...*/ = glm::rotate(rotmat, -15.0f, glm::vec3(1.0f, 0.0f, 0.0f)); break;
	case VK_NUMPAD4:translatemat = glm::translate(translatemat, glm::vec3(-1.0f, 0.0f, 0.0f)); break;
	case VK_NUMPAD6:translatemat = glm::translate(translatemat, glm::vec3(1.0f, 0.0f, 0.0f)); break;
	case VK_NUMPAD2:translatemat = glm::translate(translatemat, glm::vec3(0.0f, -1.0f, 0.0f)); break;
	case VK_NUMPAD8:translatemat = glm::translate(translatemat, glm::vec3(0.0f, 1.0f, 0.0f)); break;
	
	default:
		return;
	}
	scalemat_s[current_obj_selection->index] = scalemat;
	rotmat_s[current_obj_selection->index] = rotmat;
	translatemat_s[current_obj_selection->index] =translatemat;
	glm::mat4 model_mat = translatemat*scalemat*rotmat;
	//glmain->setCameraTransformMatrix(model_mat);
	if (current_obj_selection != nullptr){

		for (unsigned int i = current_obj_selection->startp; i < current_obj_selection->endp;i++){

			glmain->draw_elements[i].matrix = /*glm::value_ptr(*/model_mat/*)*/;

		}
	}
	glmain->render();//@TODO:es darf nicht sein,dass bei jedem Tastendruck gerendert wird,oder doch????????????!.!:.-magisches Ladezeichen
	}
}

/*
DWORD WINAPI threadFunc(LPVOID lpParam){
	std::ofstream fs;
	fs.open("file.shotgun", std::ios::out | std::ios::trunc);//binary

	fs << "hey";
	fs.close();
	return 0;
}*/
void on_opengl_click_moue_pos(int x, int y,int width,int height){

	//::MessageBox(NULL,(std::to_string(x)+"-"+std::to_string(y)).c_str(),"dfsfds",MB_OK);
	////http://gamedev.stackexchange.com/questions/29977/how-do-i-get-the-correct-values-from-glreadpixels-in-opengl-3-0
	//@TODO: steht da hinten,noch so ein TODO,dass so dumm do derumm steht,wie überall;-)
	glmain->set_framebuffer_to_position(true);
	glmain->TEST_create_dummy_texture();
	glmain->render(false);
	int y_pos_lower_left = height - y-1;
	auto *p = glmain->get_pixels_at_position<GLubyte>(x, y_pos_lower_left, GL_RGBA, GL_UNSIGNED_BYTE);
	
	glmain->set_framebuffer_to_position(false);
	glmain->TEST_restore_dummy_texture();
	//glmain->render();//render istwohl net nötig
	
	
	auto d1 = p[0];
	auto d2 = p[1];
	auto d3 = p[2];//@TODO:falsche werte,z.b. 255,weil er den hintergrund erwischt
	auto d4 = p[3]; 
	OutputDebugString(std::to_string(d3).c_str());//@TODO:jetzt das mit den ID'S
}

void winapi_suitable_glmain_render(HWND hWnd, WPARAM wParam, LPARAM lParam){
	glmain->render();
}

void ondropfiles(HWND hWnd, WPARAM wParam, LPARAM lParam){
//TEXT wenn möglich verwenden http://www.cplusplus.com/forum/articles/16820/
	//::MessageBox(NULL,TEXT("text"),TEXT("text2"),MB_COMPOSITE);//@TODO:point herausbekommen,und genau dort hin schieben(aber nur falls innerhalb opengl window(cleint,context??-da kommt man leicht durcheinander bei den Begriffen))@TODO:exra abstraktionsschichten dafür
	HDROP file_drop = reinterpret_cast<HDROP>(wParam);
	char file_path[MAX_PATH]; auto file_path_size = sizeof(file_path);
	UINT num_dropped_elements = ::DragQueryFile(file_drop, 0xFFFFFFFF, NULL, NULL);//auch ordner landen da
	//danach inspiiert,aber alles selbst geschrieben(kann man da stolz drauf sein??eher nein) http://forums.mydigitallife.info/threads/42527-C-Implementing-Drag-amp-Drop-with-Windows-API
	//http://winapi.freetechsecrets.com/win32/WIN32Using_the_DragDrop_Feature.htm
	for (unsigned int i = 0; i < num_dropped_elements; i++){
		
		::DragQueryFile(file_drop, i, file_path, file_path_size);
		DWORD attrib = ::GetFileAttributes(file_path);
		if (((attrib != FILE_ATTRIBUTE_REPARSE_POINT)&& (attrib != FILE_ATTRIBUTE_DIRECTORY)))
		{	//symbolic links(Verknüpfungen )könne nicht erkannt werden,hab auch keine ahnung wie ich das so richtig hinkriegen soll,vllt. jre source bei filemode.symlink
			//@TODO:nachricht bei ordner
			
				assimp_import_file(file_path);
		

		}

	}

}

//http://stackoverflow.com/questions/13078953/code-analysis-says-inconsistent-annotation-for-wwinmain-this-instance-has-no
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int iCmdShow)
{
	using namespace Windows;
	int width=1024, height=768;//@TODO:bind struct proggen
	//Hinweis:http://stackoverflow.com/questions/12796501/detect-clicking-inside-listview-and-show-context-menu
	//Designentscheidung:eine oder mehrere message-loops?? //DeferWindowPos zum gleichzeitngen Verschieben von mehreren Windows auf einmal,besser mehrere wegen performance,dann wohl hui in Teile aufsplitten//@TODO:das was hier vornedran stand
	aw = new ApplicationWindow(hInstance, { "t1", "t2" }, { width, height },WS_VISIBLE | WS_OVERLAPPEDWINDOW/*,WndProc*/);//@TODO:->show erst später aufrufen,daher kein ws_visible
	//ApplicationWindow*aw2 = new ApplicationWindow(hInstance, { "t122", "t222" }, { width, height }, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
	//
	//@TODO: WM_KILLFOCUS
/*	MSG  msg;
	WNDCLASS wc = { 0 };
	wc.lpszClassName = TEXT("Check Box");
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	char *title = TEXT("Check Box");

	RegisterClass(&wc);
	HWND wnd2 = CreateWindow(wc.lpszClassName, title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		150, 150, 830, 350, 0, 0, hInstance, 0);
		
	HWND wnd = CreateWindowA(TEXT("button"), TEXT("Show Title"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		710, 150, 200, 200,
		wnd2, (HMENU)1, NULL, NULL);
	CheckDlgButton(wnd2, 1, BST_CHECKED);
	*/
	//HWND hCtrl0_0 = CreateWindowEx(0, WC_BUTTON, ("Check"), WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTOCHECKBOX, 125, 111, 149, 37, aw->window_handle, (HMENU)0, hInstance, 0);
	//Window*wedit = new Window(hInstance, { "edit", "freetext" }, { 155, 155 }, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE |ES_AUTOVSCROLL, aw);
	//Window*wbtn = new Window(hInstance, { "button", "button" }, { 555, 555,200,200 }, WS_CHILD | WS_VISIBLE, aw);
	//aw->addOnMessageInvoke(WM_KEYDOWN,keydown);//WM_CREATE shafft er net
	//aw->addOnMessageInvoke(WM_COMMAND,oncommand);
	//aw->addOnMessageInvoke(WM_LBUTTONDOWN,mousedown);
	//mouse_hook=::SetWindowsHookEx(WH_MOUSE_LL,MouseProc,hInstance,0/*alle Threads*/);
	default_focus = ::GetFocus();//@TODO:vllt. was anderes machen als gelicht den Fokus umzukehren,ich denke ,dass KOnzept mit dem Fokus kann ja wohl nicht so sinnlo sein
	aw->addOnMessageInvoke(WM_KEYDOWN, keydown);
	::DragAcceptFiles(aw->window_handle,true);
	aw->addOnMessageInvoke(WM_DROPFILES, ondropfiles);

	//MessageBox(NULL, wedit->Text_get(), wedit->Text_get(), MB_OK);
	InitCommonControls();
	TrackBar* tb = new TrackBar("hallo", { 200, 50, 610, 370 }, aw, { 4, 6 }, {4,5});
	winproc_promise_event BTN_CLICK = {CLICK_FUNC, WM_COMMAND, true };//default=false
	winproc_promise_event LISTVIEW_SELECT = { LISTVIEW_SELECT_FUNC, WM_NOTIFY,false };

	//wbtn->on(BTN_CLICK,onclick);
	
	//erstelle controls am rechten Rand

	//dc->SaveFileName(L"C:\\");

	//aw->Position_set({1920,1080});
	
	
	Menu * m = new Menu(aw);
	//PopUp_Menu<char*> *p = new PopUp_Menu<char*>("s");
	PopUp_Menu * p1 = m->add_PopUp_Menu(new PopUp_Menu("Datei"));
	for (int i = 0; i < 75; i++){
		p1->add_Menu_Item(new Menu_Item("Schließen", ui_close_window));
	}
m->showMenu();



	//http://stackoverflow.com/questions/13979371/win32-api-listview-creation-c
	int lwidth = 200; int lheight = 200;
	

	Windows::Window*w = new Windows::Window({ WC_LISTVIEWW, NULL }, { lwidth, lheight, width - lwidth - 50, 0 + 100 }, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT, aw, NULL);
	w->on(LISTVIEW_SELECT,listview_handle_click);
	lv = new List_View(w);
	lv->columns->add("verkacktes Objeccckkt");

	lv->items->add("Hallo,kann ich behilflich sein??");

	uicontrol = new ApplicationUI_Control_Mgr(aw,width,height);
	//uicontrol->open_file_btn->on(BTN_CLICK,onMeshImportButton);
	//uicontrol->addEditControls();
	//uicontrol->addButtons(BTN_CLICK);
	uicontrol->open_file_btn->on(BTN_CLICK, action_dialog_onclick);
	uicontrol->save_threed_objects->on(BTN_CLICK, action_save_state);
	uicontrol->set_mouse_pos_callback(on_opengl_click_moue_pos);
	//commanddata.push_back(handle_add);
	//commanddata.push_back(save_handle);

	glmain = Application::setup_system_gl_opengl_layer<swapBuffersFunc, OpenGLContext, THREEDObject>(uicontrol->static_draw_field->window_handle);


	//glm->setViewPort(uicontrol->static_draw_field->Position_get());//wohl so nicht richtig
	//RECT lpp = uicontrol->static_draw_field->Rect_get();
	RECT pos = uicontrol->static_draw_field->ClientRect_get();//client rect besser,gucken ob das so stimmt,sieht nämllich etwas verzerrt aus imho,jetzt nicht mehr,trotzdem im Auge behalten
	//@TODO.  uicontrol->static_draw_field->Position_get().height checken,dennursprüngl. rect.height
	glmain->setViewPort({ pos.right, pos.bottom, pos.left, pos.top/*@TODO:check ob reihenfolge von left und top stimmt,kann auch sein dass ichs vertauscht hab*/ });
	//bsp.nach sequenzen(neuses wort,ist overkill->headshot) gruppieren:zb.b strut x_follwed_by_y_by_widthbyheight->das dann auch für viewport oder readpixels verwende(gl)
	glmain->initGL();//vieles wenn möglich als const markieren wegen thread-safety(überblick)
	//Windows::Dialogs::File_Dialog*dc
	//dc->ofn.hwndOwner = aw->native_window_handle;//unnötig
	
	
	//Windows::WindowRect re = uicontrol->static_draw_field->Position_get();
	/*float aspectRatio = float(/*re.width*//*pos.right) / float(/*re.height*//*pos.bottom);//@TODO:mit Rect

	//glm::mat4 matt2 = glm::perspective(45.0f, aspectRatio, 0.01f, 5000.0f);
	projection_matrix = glm::perspective(45.0f, aspectRatio, 0.01f, 5000.0f);
	glm::mat4 model_mat = glm::mat4(1.0f);


//	glmain->setCameraandProjMatrix(std_res);
	glmain->setProjectionMatrix(projection_matrix);
	glmain->setCameraMatrix(camera_mat);
	//LPWSTR dcc = dc->OpenFileName(L"C:\\Users\\ultimateFORCE\\Desktop");

	*/
	Application::set_std_camera_projection_matrices(glmain,pos.right,pos.bottom);

	//Thread*t = new Thread(threadFunc, NULL);
	
	
	//delete aiimport;

	//glm::mat4 proj_cam_matrix=projection_matrix*camera_mat;
	

	//http://stackoverflow.com/questions/466354/how-can-i-tell-if-a-window-has-focus-win32-api
	//aw->addOnMessageInvoke(WM_ACTIVATE, winapi_suitable_glmain_render);
	//aw->addOnMessageInvoke(WM_SETFOCUS, winapi_suitable_glmain_render);
	//aw->addOnMessageInvoke(WM_ERASEBKGND, winapi_suitable_glmain_render);WM_CTLCOLORBTN
	aw->addOnMessageInvoke(WM_PRINTCLIENT, winapi_suitable_glmain_render);//baruch man vllt. nicht//geht immer noch nicht bei drag drop
	aw->addOnMessageInvoke(WM_PAINT, winapi_suitable_glmain_render);//WM_PAINT scheint wohl zu reichen http://www.cplusplus.com/forum/windows/98867/
	//es kann sein,dass ein WM_PAINT auf das opengl feld reicht,da controls gesubcalssed msg könnte hier net ankommen
	//aw->addOnMessageInvoke(WM_SHOWWINDOW, winapi_suitable_glmain_render);
	

	return (new MessageLoop())->GetMessage_Approach();
}