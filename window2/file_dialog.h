#ifndef INC_FILE_DIALOG_H
#define INC_FILE_DIALOG_H
#include <Windows.h>
#include <commdlg.h>
namespace Windows{
	namespace Dialogs{
		class File_Dialog{
		public:
			File_Dialog();

			OPENFILENAMEW ofn;
			LPWSTR OpenFileName(LPCWSTR initial_dir);
			LPWSTR SaveFileName(LPCWSTR initial_dir);

		};
	}


}

#endif