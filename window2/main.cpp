#include "ApplicationWindow.h"
#include "MessageLoop.h"
#include "Window.h"
#include "ShaderSource.h"
#include "GLProgram.h"
//#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <map>
#include <vector>
#include "ApplicationUI_Control_Mgr.h"
#include "file_dialog.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLContext.h"
//#include "SysUtils_Load_Library.h"
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
#include "resource.h"
#include "APIs\OS\Win\UI_Controls\List_View.h"
#include "APIs\OS\Win\UI_Controls\Menu.h"
#include "APIs\OS\Win\UI_Controls\TrackBar.h"
#include "App_Initialize_Components.h"
#include "../gyp_workspace2/FreeTypeImplementation.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

Windows::ApplicationWindow* aw; //Windows::Window*ws;
Windows::Window*main_window;//so das window wo sich das main befindet
ApplicationUI_Control_Mgr*uicontrol; OpenGLContext*ctx;
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
/*
void copy_to_other(){
	HDC hPrinterDC = ws->DeviceContext_get();
	int cWidthPels = GetDeviceCaps(hPrinterDC, HORZRES);

	int cHeightPels = GetDeviceCaps(hPrinterDC, VERTRES);
	
	//BitBlt(hPrinterDC, 0, 0, cWidthPels, cHeightPels, uicontrol->static_draw_field->DeviceContext_get(), 0, 0, SRCCOPY);
	RECT r = uicontrol->static_draw_field->Rect_get();
	Windows::WindowRect wr = uicontrol->static_draw_field->Position_get();
	int start_x = r.left, start_y = r.top, end_x = r.right, end_y = r.bottom;
	//BitBlt(ws->DeviceContext_get(), 0, 0, end_x, end_y, GetWindowDC(aw->window_handle), start_x, start_y, SRCCOPY);
	//BitBlt(ws->DeviceContext_get(), 0, 0, 500, 500, GetWindowDC(aw->window_handle), 0,0, SRCCOPY);
	HDC hdc = hPrinterDC;
	RECT rt;
	GetClientRect(ws->window_handle, &rt);
	//HDC myHdc = CreateCompatibleDC(hdc);
	HDC myHdc = uicontrol->static_draw_field->DeviceContext_get();
	//HBITMAP bitmap = CreateCompatibleBitmap(hdc, 300, 300);
	//auto oldBitmap = SelectObject(myHdc, bitmap);
	//char*szHello = "dfdfs";
	//DrawText(myHdc, szHello, strlen(szHello), &rt, DT_CENTER);
	//BitBlt(hdc, 0, 0, rt.right - rt.left, rt.bottom - rt.top, myHdc, 0, 0, SRCCOPY);

	//::SelectObject(myHdc, oldBitmap);
	
	int nScreenWidth = 300, nScreenHeight = 300;
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biWidth = nScreenWidth;
	bmi.bmiHeader.biHeight = nScreenHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	// Allocate a buffer to receive the pixel data.
	RGBQUAD *pPixels = new RGBQUAD[nScreenWidth * nScreenHeight];
	
	// Call GetDIBits to copy the bits from the device dependent bitmap
	// into the buffer allocated above, using the pixel format you
	// chose in the BITMAPINFO.//http://stackoverflow.com/questions/2659932/how-to-read-the-screen-pixels
	HDC hCaptureDC = myHdc;
	HBITMAP hCaptureBitmap = CreateCompatibleBitmap(GetDC(0),nScreenWidth,nScreenHeight);
	::GetDIBits(hCaptureDC,
		hCaptureBitmap,
		0,  // starting scanline
		nScreenHeight,  // scanlines to copy
		pPixels,  // buffer for your copy of the pixels
		&bmi,  // format you want the data in
		DIB_RGB_COLORS);  // actual pixels, not palette references
	HDC targetDC = ws->DeviceContext_get();
	HBITMAP hTargetBitmap = CreateCompatibleBitmap(GetDC(0), nScreenWidth, nScreenHeight);

	SetDIBits(targetDC,hTargetBitmap, 0,nScreenHeight,pPixels, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
	ws->DeviceContext_release(targetDC);
	uicontrol->static_draw_field->DeviceContext_release(hCaptureDC);
}*///geht nicht
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
bool TABSELECTION_SELECT_FUNC(HWND global_wnd, WPARAM wParam, LPARAM lParam, HWND caller_wnd){
	return ((LPNMHDR)lParam)->code==TCN_SELCHANGE;
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
	if ((clicked_item_number!=0)&&(clicked_item_number!=-1)&&(current_obj_selection!=nullptr/*@TODO:gucken ob das da hier und jetzt(oder auch später) entfernen*/)){
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
/*
void WriteOpenGLPixelsToHBITMAP(HBITMAP dstHBITMAP, HDC dstDC, SIZE dims)
{

	BITMAPINFO bitmapInfo;
	{
		::memset(&bitmapInfo, 0, sizeof(BITMAPINFO));
		bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biBitCount = 32;
		bitmapInfo.bmiHeader.biCompression = BI_RGB;
		bitmapInfo.bmiHeader.biWidth = dims.cx;
		bitmapInfo.bmiHeader.biHeight = dims.cy;
		bitmapInfo.bmiHeader.biSizeImage = dims.cx * dims.cy * 4; // Size 4, assuming RGBA from OpenGL
	}

	void    *bmBits = NULL;
	HDC     memDC = ::CreateCompatibleDC(dstDC);
	HBITMAP memBM = ::CreateDIBSection(NULL, &bitmapInfo, DIB_RGB_COLORS, &bmBits, NULL, 0);


	/*::glReadPixels(0,
	0,
	dims.cx,
	dims.cy,
	GL_RGB,
	GL_UNSIGNED_BYTE,
	bmBits);*/
	/*glmain->set_framebuffer_to_position(true);
	glmain->render(false);
	bmBits = glmain->get_pixels_at_position<GLubyte>(0, 0, GL_BGR, GL_UNSIGNED_BYTE, dims.cx, dims.cy);
	glmain->set_framebuffer_to_position(false);
	HGDIOBJ prevBitmap = ::SelectObject(memDC, memBM);
	HGDIOBJ obj = ::SelectObject(dstDC, dstHBITMAP);

	// Remember that OpenGL origin is at bottom, left, but bitmaps are top, left
	if (false == BitBlt(dstDC, 0 /*left*///, dims.cy /*top*/, dims.cx, dims.cy, memDC, 0, 0, SRCCOPY))
	/*{
		assert(false && "Failed to write pixels to HBitmap from OpenGL glReadPixels");
	}//quelle:internet

	::SelectObject(memDC, prevBitmap);
	::DeleteObject(memBM);
	::DeleteDC(memDC);
}*/
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
		
		//SIZE sz; sz.cx = 300; sz.cy = 300; //HDC ddc = ws->DeviceContext_get();
		//HBITMAP bitmap = CreateCompatibleBitmap(ddc,300,300);
		//WriteOpenGLPixelsToHBITMAP(bitmap,ddc,sz);
		//ws->DeviceContext_release(ddc);
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

void ui_on_file_print(HWND hWnd, WPARAM wParam, LPARAM lParam){
	PRINTDLG pd = { 0 };
	pd.lStructSize = sizeof(pd);
	pd.Flags = PD_RETURNDC;
	pd.hwndOwner = main_window->window_handle;

	// Retrieve the printer DC
	if (!PrintDlg(&pd))
	{
		//TRACE("PrintDlg canceled");
		return;
	}

	DOCINFO di;
	memset(&di, 0, sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = _T("Scribble Printout");
	di.lpszOutput = (LPTSTR)NULL;
	di.lpszDatatype = (LPTSTR)NULL;
	di.fwType = 0;
	StartDoc(pd.hDC,&di);
	StartPage(pd.hDC);//danach passierts wohl,denn die auf die erste anweisung von Enable_to_DeviceContext wurde der breakpoint nicht getroffen,auch nicht for Enable_to_DeviceContext mit f10 von hier aus
	ctx->Enable_to_DeviceContext(pd.hDC);//fehler bei druckertreibern,hängt sioch so auf,dass ichs nocht mehr mitmdem taskmgr beenden kann//muss man mindestens 2x in der windows user session machen,beim ersten mal gibts
	glmain->draw_elements.clear();
	glmain->render();
	ctx->gl_layer_MakeCurrent(NULL,NULL);
	//ctx->Enable_to_DeviceContext(uicontrol->static_draw_field->DeviceContext_get());


	::EndPage(pd.hDC);
	::EndDoc(pd.hDC);

}
//void ui_on_file_print(HWND hWnd, WPARAM wParam, LPARAM lParam){
	/*Windows::WindowRect rect = aw->ClientRect_get();
	int Width = rect.width; int Height = rect.height;
	HWND m_View555 = aw->window_handle;
	WCXXClientDC dcView(&m_View555);
	WCXXCDC dccView;
	dccView.m_pData->hDC = dcView.m_pData->hDC;
	//dccView.m_pData->m_vGDIObjects=dcView.m_pData->m_vGDIObjects;
	dccView.m_pData->hWnd = dcView.m_pData->hWnd;
	WCXXMEMDC MemDC(&dccView);
	WCXXBitmap bmView;
	bmView.CreateCompatibleBitmap(&dccView, Width, Height);
	MemDC.SelectObject(&bmView);
	MemDC.BitBlt(0, 0, Width, Height, &dccView, 0, 0, SRCCOPY);

	// Bring up a dialog to choose the printer
	PRINTDLG pd = { 0 };
	pd.lStructSize = sizeof(pd);
	pd.Flags = PD_RETURNDC;
	pd.hwndOwner = aw->window_handle;

	// Retrieve the printer DC
	if (!PrintDlg(&pd))
	{
		//TRACE("PrintDlg canceled");
		return;
	}

	// Zero and then initialize the members of a DOCINFO structure.
	DOCINFO di;
	memset(&di, 0, sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = _T("Scribble Printout");
	di.lpszOutput = (LPTSTR)NULL;
	di.lpszDatatype = (LPTSTR)NULL;
	di.fwType = 0;

	// Begin a print job by calling the StartDoc function.
	if (SP_ERROR == StartDoc(pd.hDC, &di))
		throw std::runtime_error(_T("Failed to start print job"));

	// Inform the driver that the application is about to begin sending data.
	if (0 > StartPage(pd.hDC))
		throw std::runtime_error(_T("StartPage failed"));

	BITMAPINFOHEADER bi = { 0 };
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biHeight = Height;
	bi.biWidth = Width;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = BI_RGB;

	// Note: BITMAPINFO and BITMAPINFOHEADER are the same for 24 bit bitmaps
	// Get the size of the image data
	MemDC.GetDIBits(&bmView, 0, Height, NULL, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS);

	// Retrieve the image data
	std::vector<byte> vBits(bi.biSizeImage, 0);	// a vector to hold the byte array
	byte* pByteArray = &vBits.front();
	MemDC.GetDIBits(&bmView, 0, Height, pByteArray, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS);

	// Determine the scaling factors required to print the bitmap and retain its original proportions.
	float fLogPelsX1 = (float)GetDeviceCaps(dccView.m_pData->hDC, LOGPIXELSX);
	float fLogPelsY1 = (float)GetDeviceCaps(dccView.m_pData->hDC, LOGPIXELSY);
	float fLogPelsX2 = (float)GetDeviceCaps(pd.hDC, LOGPIXELSX);
	float fLogPelsY2 = (float)GetDeviceCaps(pd.hDC, LOGPIXELSY);
	float fScaleX = WINXX_MAX(fLogPelsX1, fLogPelsX2) / WINXX_MIN(fLogPelsX1, fLogPelsX2);
	float fScaleY = WINXX_MAX(fLogPelsY1, fLogPelsY2) / WINXX_MIN(fLogPelsY1, fLogPelsY2);

	// Compute the coordinates of the upper left corner of the centered bitmap.
	int cWidthPels = GetDeviceCaps(pd.hDC, HORZRES);
	int xLeft = ((cWidthPels / 2) - ((int)(((float)Width) * fScaleX)) / 2);
	int cHeightPels = GetDeviceCaps(pd.hDC, VERTRES);
	int yTop = ((cHeightPels / 2) - ((int)(((float)Height) * fScaleY)) / 2);

	// Use StretchDIBits to scale the bitmap and maintain its original proportions
	if (GDI_ERROR == (UINT)StretchDIBits(pd.hDC, xLeft, yTop, (int)((float)Width * fScaleX),
		(int)((float)Height * fScaleY), 0, 0, Width, Height, pByteArray, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS, SRCCOPY))
	{
		throw std::runtime_error("Failed to resize image for printing");
	}

	// Inform the driver that the page is finished.
	if (0 > EndPage(pd.hDC))
		throw std::runtime_error("EndPage failed");
	//throw CWinException(_T("EndPage failed"));

	// Inform the driver that document has ended.
	if (0 > EndDoc(pd.hDC))
		throw std::runtime_error("EndDoc failed");
*/

	// Extract the bitmap from the View window
	/*auto view_window = aw;
	
	int Width = view_window->ClientRect_get().width; int Height = view_window->ClientRect_get().width;
	HDC ViewDC = view_window->DeviceContext_get();
	HDC MemDC = CreateCompatibleDC(ViewDC);
	HBITMAP pBitmap = ::CreateCompatibleBitmap(ViewDC, Width, Height);//attach
	::SelectObject(ViewDC, pBitmap);
	//MemDC.CreateCompatibleBitmap(m_View.GetDC(), Width, Height);

	BitBlt(MemDC, 0, 0, Width, Height, ViewDC, 0, 0, SRCCOPY);




	//HBITMAP hbmView = MemDC.DetachBitmap();
	//detach bitmap beginn

	//CBitmap* pBitmap = new CBitmap;
	//pBitmap->CreateBitmap(1, 1, 1, 1, 0);
	HBITMAP h9Bitmap = ::CreateBitmap(1, 1, 1, 1, 0);
	//m_pData->m_vGDIObjects.push_back(pBitmap);

	// Select our new stock bitmap into the device context
	HBITMAP hbmView = (HBITMAP)::SelectObject(MemDC, h9Bitmap);

	// Detach the bitmap from our internally managed GDIObjects
	/*std::vector<GDIPtr>::iterator it;
	for (it = m_pData->m_vGDIObjects.begin(); it < m_pData->m_vGDIObjects.end(); ++it)
	{
		if ((*it)->GetHandle() == hBitmap)
			(*it)->Detach();
	}

	// Create a local CBitmap. We can return this by value because it is reference counted
	CBitmap Bitmap(hBitmap);
	return Bitmap;
	//end bitmap detach
	*/







/*







	// Bring up a dialog to choose the printer
	PRINTDLG pd = { 0 };
	pd.lStructSize = sizeof(pd);
	pd.Flags = PD_RETURNDC;

	// Retrieve the printer DC
	PrintDlg(&pd);

	DOCINFO di = { 0 };
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = _T("Scribble Printout");
	di.lpszOutput = (LPTSTR)NULL;
	di.lpszDatatype = (LPTSTR)NULL;
	di.fwType = 0;

	// Begin a print job by calling the StartDoc function.
	StartDoc(pd.hDC, &di);

	// Inform the driver that the application is about to begin sending data.
	StartPage(pd.hDC);

	RECT rcView;
	GetClientRect(view_window->window_handle, &rcView);
	 Width = rcView.right - rcView.left;
	Height = rcView.bottom - rcView.top;

	// Fill the BITMAPINFOHEADER structure
	BITMAPINFOHEADER bi = { 0 };
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biHeight = Height;
	bi.biWidth = Width;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = BI_RGB;

	// Note: BITMAPINFO and BITMAPINFOHEADER are the same for 24 bit bitmaps
	// Get the size of the image data
	GetDIBits(MemDC, hbmView, 0, Height, NULL, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	// Retrieve the image data
	byte* pBits = new byte[bi.biSizeImage];
	GetDIBits(MemDC, hbmView, 0, Height, pBits, (BITMAPINFO*)&bi, DIB_RGB_COLORS);




	// Determine the scaling factors required retain the bitmap's original proportions.
	float fLogPelsX1 = (float)GetDeviceCaps(ViewDC, LOGPIXELSX);
	float fLogPelsY1 = (float)GetDeviceCaps(ViewDC, LOGPIXELSY);
	float fLogPelsX2 = (float)GetDeviceCaps(pd.hDC, LOGPIXELSX);
	float fLogPelsY2 = (float)GetDeviceCaps(pd.hDC, LOGPIXELSY);
	float fScaleX = WINXX_MAX(fLogPelsX1, fLogPelsX2) / WINXX_MIN(fLogPelsX1, fLogPelsX2);
	float fScaleY = WINXX_MAX(fLogPelsY1, fLogPelsY2) / WINXX_MIN(fLogPelsY1, fLogPelsY2);

	// Compute the coordinates of the upper left corner of the centered bitmap.
	int cWidthPels = GetDeviceCaps(pd.hDC, HORZRES);
	int xLeft = ((cWidthPels / 2) - ((int)(((float)Width) * fScaleX)) / 2);
	int cHeightPels = GetDeviceCaps(pd.hDC, VERTRES);
	int yTop = ((cHeightPels / 2) - ((int)(((float)Height) * fScaleY)) / 2);

	// Use StretchDIBits to scale the bitmap and maintain its original proportions
	StretchDIBits(pd.hDC, xLeft, yTop, (int)((float)Width * fScaleX),
		(int)((float)Height * fScaleY), 0, 0, Width, Height, pBits,
		(BITMAPINFO*)&bi, DIB_RGB_COLORS, SRCCOPY);

	// Inform the driver that the page is finished.
	EndPage(pd.hDC);

	// Inform the driver that document has ended.
	EndDoc(pd.hDC);

	// Cleanup
	::DeleteObject(hbmView);
	delete[]pBits;

}*/
/*
void ui_menu_item_drucken(HWND hWnd, WPARAM wParam, LPARAM lParam){
	//printdlg wird nicht mehr empfohlen,kann ertfernt werden,daher printfdlgex(eigentlich komische entscheidung)
	//PRINTDLGEX pd = { 0 };
	//ZeroMemory(&pd, sizeof(PRINTDLGEX));//gleiches wie memset(,0,)
	//pd.Flags = PD_ENABLEPRINTTEMPLATE;
	//pd.lStructSize = sizeof(PRINTDLGEX);
	HRESULT hResult;
	PRINTDLGEX pdx = { 0 };
	LPPRINTPAGERANGE pPageRanges = NULL;
	HDC source_dc = ::GetDC(uicontrol->static_draw_field->window_handle);
	// Allocate an array of PRINTPAGERANGE structures.
	pPageRanges = (LPPRINTPAGERANGE)GlobalAlloc(GPTR, 10 * sizeof(PRINTPAGERANGE));
	if (!pPageRanges){ throw std::runtime_error("out of memory"); }
	//  Initialize the PRINTDLGEX structure.
	pdx.lStructSize = sizeof(PRINTDLGEX);
	pdx.hwndOwner = hWnd;
	pdx.hDevMode = NULL;
	pdx.hDevNames = NULL;
	pdx.hDC =NULL;
	pdx.Flags = PD_RETURNDC | PD_COLLATE;
	pdx.Flags2 = 0;
	pdx.ExclusionFlags = 0;
	pdx.nPageRanges = 0;
	pdx.nMaxPageRanges = 10;
	pdx.lpPageRanges = pPageRanges;
	pdx.nMinPage = 1;
	pdx.nMaxPage = 1000;
	pdx.nCopies = 1;
	pdx.hInstance = 0;
	pdx.lpPrintTemplateName = NULL;
	pdx.lpCallback = NULL;
	pdx.nPropertyPages = 0;
	pdx.lphPropertyPages = NULL;
	pdx.nStartPage = START_PAGE_GENERAL;
	pdx.dwResultAction = 0;
	hResult = PrintDlgEx(&pdx);
	if ((hResult == S_OK) && pdx.dwResultAction == PD_RESULT_PRINT)
	{

		/*DOCINFO di;

		memset(&di, 0, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = "drucktest";
		//if (pdx.hDC != NULL){ ::MessageBox(NULL,"fd","fdfd",MB_OK); }
		// drucken
		StartDoc(pdx.hDC, &di);
		
		StartPage(pdx.hDC);
		// Inhalt ausgeben
		//SelectObject(pdx.hDC, MyFont);
		//TextOut(pd.hDC, 70, 70, String, strlen(String));
		//TextOut(pd.hDC, 10, 17, String, strlen(String));
		
		Windows::WindowRect r = uicontrol->static_draw_field->ClientRect_get();
		BitBlt(pdx.hDC, 0, 0, r.width, r.height, source_dc, 0, 0, SRCCOPY);

		EndPage(pdx.hDC);

		EndDoc(pdx.hDC);  // Dokument wird geschlossen
		if (pdx.hDevMode != NULL) GlobalFree(pdx.hDevMode);
		if (pdx.hDevNames != NULL) GlobalFree(pdx.hDevNames);//http://www.willemer.de/informatik/windows/windruck.htm
		//::MessageBox(NULL,"dfdf","fds",MB_OK);
		// User clicked the Print button, so use the DC and other information returned in the 
		// PRINTDLGEX structure to print the document.*/
/*
		const LPDEVMODE devmode = (LPDEVMODE)GlobalLock(pdx.hDevMode);

		const LPDEVNAMES devnames = (LPDEVNAMES)GlobalLock(pdx.hDevNames);

		LPCTSTR driver = LPCTSTR(devnames) + devnames->wDriverOffset;
		LPCTSTR device = LPCTSTR(devnames) + devnames->wDeviceOffset;
		LPCTSTR output = LPCTSTR(devnames) + devnames->wOutputOffset;

		HDC hPrinterDC = CreateDC("WINSPOOL\0", device, NULL, NULL);

		DOCINFO di;

		memset(&di, 0, sizeof(DOCINFO));

		di.cbSize = sizeof(DOCINFO);

		di.lpszDocName = "PrintIt";

		di.lpszOutput = (LPTSTR)NULL;

		di.lpszDatatype = (LPTSTR)NULL;

		di.fwType = 0;
		int nError = StartDoc(hPrinterDC, &di);


		int cWidthPels, cHeightPels;

		cWidthPels = GetDeviceCaps(hPrinterDC, HORZRES);

		cHeightPels = GetDeviceCaps(hPrinterDC, VERTRES);
		RECT rcPrinter;

		rcPrinter.top = 5;

		rcPrinter.left = 5;

		rcPrinter.right = cWidthPels - 10;

		rcPrinter.bottom = cHeightPels - 10;
		nError = StartPage(hPrinterDC);
		LPCSTR text = "hhhe";
		//DrawText(hPrinterDC, text, strlen(text), &rcPrinter, DT_TOP | DT_LEFT | DT_WORDBREAK);
		BitBlt(pdx.hDC, 0, 0, rcPrinter.right, rcPrinter.left, source_dc, 0, 0, SRCCOPY);
		nError = EndPage(hPrinterDC);
		nError = EndDoc(hPrinterDC);
		DeleteDC(hPrinterDC);


		DeleteDC(pdx.hDC);
	}

	if (pdx.hDevMode != NULL)
		GlobalFree(pdx.hDevMode);
	if (pdx.hDevNames != NULL)
		GlobalFree(pdx.hDevNames);
	if (pdx.lpPageRanges != NULL)
		GlobalFree(pPageRanges);

	
		

}

*/

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
	//objekt auswählen //@TODO:mit mehr als 255 soll es gehn
	if ((d3 != 255)&&(d3>=0) ){
		//Treffer

		//current_obj_selection = &startp_endp_list_objs[d3];
		for (sp_endp_type& d : startp_endp_list_objs){
			if ((d3 >= d.startp) && (d3 <= (d.endp-1))){
				//dann in Range
				current_obj_selection = &d;
					break;

			}
			

		}


	}
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
//http://www.gamedev.net/topic/625972-choosing-a-network-library/ OVERLAPPED I/O -> IOCP
//http://stackoverflow.com/questions/10911294/potential-kind-of-asynchronous-overlapped-i-o-implementation-in-windows
//@TODO:addonmessageinvoke muss return werte unterstützen
void tab_handle_selection_change(HWND hWnd, WPARAM wParam, LPARAM lParam){
	int iPage = TabCtrl_GetCurSel(uicontrol->main_tab_control->window_handle);
	::MessageBox(NULL,std::to_string(iPage).c_str(),"fdfds",MB_OK);
}
bool capture_drag_drop = false;
void dragdropmousemove(HWND hWnd, WPARAM wParam, LPARAM lParam){
	OutputDebugString("mouse_move"); OutputDebugString(std::to_string(rand()).c_str()); OutputDebugString("\n");
	if (capture_drag_drop){
		/*DWORD mousepos = ::GetMessagePos();
		POINTS p = MAKEPOINTS(mousepos);
		//http://gamedev.stackexchange.com/questions/29977/how-do-i-get-the-correct-values-from-glreadpixels-in-opengl-3-0
		//@TODO:gucken->da,warhscheinlich falsche koordinaten
		LPPOINT pr = new tagPOINT; pr->x = p.x; pr->y = p.y;
		::ScreenToClient(hWnd, pr);
		Windows::WindowRect pxx = uicontrol->dragdropbutton->Position_get();*/
	POINT pos;
	pos.x = (int)(short)LOWORD(lParam);
	pos.y = (int)(short)HIWORD(lParam);
		//pxx.x = pos.x; pxx.y = pos.y;

		//TODO: send wm_poschanged und wm_poschaning



		//SWP_NOZORDER | (bool)bRepaint * SWP_NOREDRAW

		/*WINDOWPOS pos;
		pos.hwnd = uicontrol->dragdropbutton->window_handle;
		pos.hwndInsertAfter = NULL;
		pos.cx = pxx.width; pos.cy = pxx.height;
		pos.x = pxx.x; pos.y = pxx.y;
		pos.flags = SWP_NOACTIVATE |
			SWP_NOOWNERZORDER | SWP_NOZORDER ;
		//::SendMessage(uicontrol->dragdropbutton->window_handle, WM_WINDOWPOSCHANGED, 0,(LPARAM)&pos);*/
		//POINT pos;
		//pos.x = (int)(short)LOWORD(lParam);
		//pos.y = (int)(short)HIWORD(lParam);
		RECT prc;
		GetWindowRect(uicontrol->dragdropbutton->window_handle, &prc);
		//ClientToScreen(hWnd, &pos);
		MoveWindow(uicontrol->dragdropbutton->window_handle, pos.x,pos.y, prc.right - prc.left, prc.bottom - prc.top, TRUE);
		bool bRepaint = true;
		//setposition !=movewindow
		/*uicontrol->dragdropbutton->Position_set(pxx, SWP_NOACTIVATE |
			SWP_NOOWNERZORDER | SWP_NOZORDER |
			SWP_NOSIZE);
		*/
		
		/*RedrawWindow(uicontrol->dragdropbutton->window_handle,
			NULL,
			NULL,
			RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
			*/
		//InvalidateRect(uicontrol->dragdropbutton->window_handle, &(uicontrol->dragdropbutton->Rect_get()),true);
		//Hinweis: http://stackoverflow.com/questions/2325894/difference-between-invalidaterect-and-redrawwindow 
	}

}
void capture_release(HWND hWnd, WPARAM wParam, LPARAM lParam){
	capture_drag_drop = false;
	::ReleaseCapture();
//	aw->removeOnMessageInvoke(WM_MOUSEMOVE, dragdropmousemove);
	//aw->removeOnMessageInvoke(WM_LBUTTONDOWN, capture_release);
}

void dragdropstart(HWND hWnd, WPARAM wParam, LPARAM lParam){
	capture_drag_drop = true;
	SetCapture(hWnd);
	SetForegroundWindow(uicontrol->dragdropbutton->window_handle);//bringttop geht auch net
	
}//@TODO: http://codingmisadventures.wordpress.com/2009/03/06/dragging-or-moving-a-window-using-mouse-win32/
//klappt wohl net richtig wg. fokus,den die controls von mousemove kriegen(aber nur vllt.)

//http://stackoverflow.com/questions/13078953/code-analysis-says-inconsistent-annotation-for-wwinmain-this-instance-has-no
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int iCmdShow)
{
	using namespace Windows;
	int width=1024, height=768;//@TODO:bind struct proggen
	width += 300; height += 250;
	//Hinweis:http://stackoverflow.com/questions/12796501/detect-clicking-inside-listview-and-show-context-menu
	//Designentscheidung:eine oder mehrere message-loops?? //DeferWindowPos zum gleichzeitngen Verschieben von mehreren Windows auf einmal,besser mehrere wegen performance,dann wohl hui in Teile aufsplitten//@TODO:das was hier vornedran stand
	aw = new ApplicationWindow("t1",hInstance);//@TODO:->show erst später aufrufen,daher kein ws_visible

	/*aw->window_handle=CreateWindow(
		"t1", "t2",
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		0, 0, width, height,
		NULL, NULL, hInstance, NULL);*/
	aw->window_handle = NULL;
	main_window = new Windows::Window({ "t1", "t333" }, { width, height }, WS_VISIBLE | WS_OVERLAPPEDWINDOW, aw);
aw->window_handle = main_window->window_handle;
//es gibt auch noch showasync

	//@TODO:vllt. aus applicationwindow die window-funktionen entfernen->dann nur noch message loop und wclass erzeuger
	//Window*mainwindow = new Window(hInstance, { "t1", "t333" }, { width, height }, WS_VISIBLE | WS_OVERLAPPEDWINDOW,aw);
	
	
	
	//aw->addOnMessageInvoke(WM_NOTIFY,onnotify_tab);
	//ein und dieselbe window-klasse kriegt also dieselbe message loop,TODO:das in c++ nacbilden mit new XXx wenn möglich

	Windows::Window*ws = new Windows::Window({ "STATIC", "" }, { 300, 300, 1000, 250 }, WS_VISIBLE | WS_CHILD,main_window, WS_EX_CLIENTEDGE);
	Windows::Window*wx = new Windows::Window({ "EDIT", "123456789" }, { 100, 200, 1000, 250 }, WS_VISIBLE | WS_CHILD,main_window);


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

	//mouse_hook=::SetWindowsHookEx(WH_MOUSE_LL,MouseProc,hInstance,0/*alle Threads*/);
	default_focus = ::GetFocus();//@TODO:vllt. was anderes machen als gelicht den Fokus umzukehren,ich denke ,dass KOnzept mit dem Fokus kann ja wohl nicht so sinnlo sein
	aw->addOnMessageInvoke(WM_KEYDOWN, keydown);
	::DragAcceptFiles(aw->window_handle,true);
	aw->addOnMessageInvoke(WM_DROPFILES, ondropfiles);
	
	//MessageBox(NULL, wedit->Text_get(), wedit->Text_get(), MB_OK);
	InitCommonControls();
	
	TrackBar* tb = new TrackBar("hallo", { 200, 50, 610, 370 }, main_window, { 4, 6 }, {4,5});
	winproc_promise_event BTN_CLICK = {CLICK_FUNC, WM_COMMAND, true };//default=false
	winproc_promise_event LISTVIEW_SELECT = { LISTVIEW_SELECT_FUNC, WM_NOTIFY,false };
	winproc_promise_event TABSELECTION_CHANGED = { TABSELECTION_SELECT_FUNC, WM_NOTIFY, false };

	//am besten wäre die möglichkeit params an den on handler weiterzuschicken
	Menu * m = new Menu(aw);
	//PopUp_Menu<char*> *p = new PopUp_Menu<char*>("s");
	PopUp_Menu * p1 = m->add_PopUp_Menu(new PopUp_Menu("Datei"));
	m->add_Menu_Item(new Menu_Item("Prozess unsterblich machen-der epische Drucker dafür ist Adobe PDF-2x hintereinander",ui_on_file_print));
	for (int i = 0; i < 75; i++){
		p1->add_Menu_Item(new Menu_Item("Schließen", ui_close_window));
	}
m->showMenu();



	//http://stackoverflow.com/questions/13979371/win32-api-listview-creation-c
	int lwidth = 200; int lheight = 200;
	

	Windows::Window*w = new Windows::Window({ WC_LISTVIEWW, NULL }, { lwidth, lheight, width - lwidth - 50, 0 + 100 }, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT,main_window);
	w->on(LISTVIEW_SELECT,listview_handle_click);
	lv = new List_View(w);
	lv->columns->add("verkacktes Objeccckkt");

	lv->items->add("Hallo,kann ich behilflich sein??");


	//Window*ccc = new Window({ WC_TABCONTROL, "" }, /*{ 500, 500, 700, 700 }*/aw->ClientRect_get(), WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, aw);
	//DoCreateTabControl(ccc, hInstance);
	uicontrol = new ApplicationUI_Control_Mgr(main_window,width,height);
	//uicontrol->main_tab_control->on(TABSELECTION_CHANGED,tab_handle_selection_change);
	//uicontrol->open_file_btn->on(BTN_CLICK,onMeshImportButton);
	//uicontrol->addEditControls();
	//uicontrol->addButtons(BTN_CLICK);
	uicontrol->open_file_btn->on(BTN_CLICK, action_dialog_onclick);
	uicontrol->save_threed_objects->on(BTN_CLICK, action_save_state);
	uicontrol->set_mouse_pos_callback(on_opengl_click_moue_pos);

	uicontrol->dragdropbutton->on(BTN_CLICK,dragdropstart);
	aw->addOnMessageInvoke(WM_MOUSEMOVE, dragdropmousemove);
	aw->addOnMessageInvoke(WM_LBUTTONUP, capture_release);
	//SOCKET ss;
	//WSAAsyncSelect(ss,main_window->window_handle,104,FD_READ);

	//commanddata.push_back(handle_add);
	//commanddata.push_back(save_handle);


	
	App_Inizialize_GL_DLL::dll_opengl = new SysUtils_Load_Library("opengl32.dll");
	ctx = new OpenGLContext(uicontrol->static_draw_field->window_handle, App_Inizialize_GL_DLL::dll_opengl);

	glmain = Application::setup_system_gl_opengl_layer<swapBuffersFunc, OpenGLContext, THREEDObject>(uicontrol->static_draw_field->window_handle,ctx);
	WindowRect rect = uicontrol->static_draw_field->ClientRect_get();
	glmain->setViewPort(rect);
	//glm->setViewPort(uicontrol->static_draw_field->Position_get());//wohl so nicht richtig
	//RECT lpp = uicontrol->static_draw_field->Rect_get();
	//RECT pos = uicontrol->static_draw_field->ClientRect_get_();//client rect besser,gucken ob das so stimmt,sieht nämllich etwas verzerrt aus imho,jetzt nicht mehr,trotzdem im Auge behalten
	//
	//@TODO.  uicontrol->static_draw_field->Position_get().height checken,dennursprüngl. rect.height

	//glmain->setViewPort({ pos.right, pos.bottom, pos.left, pos.top/*@TODO:check ob reihenfolge von left und top stimmt,kann auch sein dass ichs vertauscht hab*/ });
	
	//bsp.nach sequenzen(neuses wort,ist overkill->headshot) gruppieren:zb.b strut x_follwed_by_y_by_widthbyheight->das dann auch für viewport oder readpixels verwende(gl)

	GL_Program*gp = new GL_Program();
	
	//Shader_Source*sc = new Shader_Source((m_use_legacy_system_opengl ? { IDR_MYVERTEXSHADER, VERTEX_SHADER_PATH } : {IDR_MYVERTEXSHADER_ESSL, VERTEX_SHADER_PATH_ESSL}),
	//	(m_use_legacy_system_opengl ? { IDR_MYFRAGMENTSHADER, FRAGMENT_SHADER_PATH } : {IDR_MYFRAGMENTSHADER_ESSL, FRAGMENT_SHADER_PATH_ESSL}));//unglaublich dass das net geht
	Shader_Source*sc = new Shader_Source(
#ifndef USE_GLESV2
	{ IDR_MYVERTEXSHADER, VERTEX_SHADER_PATH }, { IDR_MYFRAGMENTSHADER, FRAGMENT_SHADER_PATH }
#else
	{IDR_MYVERTEXSHADER_ESSL, VERTEX_SHADER_PATH_ESSL}, {IDR_MYFRAGMENTSHADER_ESSL, FRAGMENT_SHADER_PATH_ESSL}
#endif
	);//orgendwie komisch
	gp->assign_shaders(sc->setup_for_usage_by_program());
	glmain->initGL(gp);//vieles wenn möglich als const markieren wegen thread-safety(überblick)
	//Windows::Dialogs::File_Dialog*dc
	//dc->ofn.hwndOwner = aw->native_window_handle;//unnötig
	

	FreeType_Implementation*ft = new FreeType_Implementation();
	
	
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
	Application::set_std_camera_projection_matrices(glmain,rect.width,rect.height);

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