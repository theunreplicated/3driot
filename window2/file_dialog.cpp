#include "file_dialog.h"
namespace Windows{
	namespace Dialogs{
		File_Dialog::File_Dialog(){
			//http://cboard.cprogramming.com/windows-programming/42191-getopenfilename.html
			//http://stackoverflow.com/questions/7392164/very-strange-getopenfilename-problem
			//OPENFILENAME ofn;
			//LPSTR file_name = "C:\\";
			WCHAR flnm[MAX_PATH];
			
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof (ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = flnm;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(flnm);
			ofn.lpstrFilter =L"Alles\0*.*\0Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			
			//ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY; 
			ofn.lpstrDefExt = L"txt";
			
			


		}
		LPWSTR File_Dialog::OpenFileName(LPCWSTR initial_dir){//stdafx. mitlinken bedeutetn unicode(W),also sonst doch keien Unterscheide
			
			ofn.lpstrInitialDir =initial_dir;
			::GetOpenFileNameW(&ofn);
			
			return ofn.lpstrFile;
		}
		LPWSTR File_Dialog::SaveFileName(LPCWSTR initial_dir){//@TODO:copy n paste wegmachen
			ofn.lpstrInitialDir = initial_dir;
			::GetSaveFileNameW(&ofn);

			return ofn.lpstrFile;

		}

	};

};