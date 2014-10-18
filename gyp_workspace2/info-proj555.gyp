{
  'target_defaults': {
    'default_configuration': 'Debug',
    'configurations': {
      'Debug': {
        #'defines': [ 'DEBUG', '_DEBUG' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 1, # static debug
		'Optimization':0,
		'InlineFunctionExpansion':0
          },
	 'VCLinkerTool': {
	'GenerateDebugInformation': 'true' #Das hier ist das,was die Fehlermeldung verhindert#https://code.google.com/p/gyp/source/browse/trunk/pylib/gyp/MSVSSettings.py?r=904
	},
        },
      },
      'Release': {
        'defines': [ 'NDEBUG' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 0, # static release
          },
        },
      }
    },
    'msvs_settings': {
      'VCLinkerTool': {
       
	'AdditionalDependencies':['libEGL.lib','ILUT.lib','ILU.lib','DevIL.lib','gdi32.lib','user32.lib'],
	'AdditionalLibraryDirectories':['D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\Programmierung\\angle_tracking_repository\\build\\Debug_Win32\\lib','D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\Visual Studio 2013\\Projects\\window2\\window2\\ext\\DevIL-1.7.8-x86\\lib']
      },
    },
'include_dirs':['D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\Programmierung\\angle_tracking_repository\\include','D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\Visual Studio 2013\\Projects\\window2\\window2\\ext\\glm\\glm-0.9.5.3','D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\Visual Studio 2013\\Projects\\window2\\window2\\ext\\DevIL-1.7.8-x86\\include']
  },
'variables':{'editor_dir':'../window2','main':'../Main'},
  'targets': [{
'target_name': 'main555',
		'type': 'executable',
		
		'sources':['<(main)/main.cpp','<(main)/File_Parser.h','<(main)/File_Parser.cpp','<(main)/GLStruct_Copy.h','<(main)/ImageLoader_Copy.h','<(main)/ImageLoader_Copy.cpp',
		'<(main)/my_gfx_rect.h','<(main)/my_gfx_rect.cpp','<(editor_dir)/resource_script.rc','<(editor_dir)/resource.h','<(editor_dir)/WinUtils.h','<(editor_dir)/Win_Utils.cpp',
		'<(editor_dir)/MessageLoop.cpp','<(editor_dir)/MessageLoop.h','<(editor_dir)/OpenGLContext.cpp','<(editor_dir)/OpenGLContext.h','<(editor_dir)/SysUtils_Load_Library.cpp','<(editor_dir)/SysUtils_Load_Library.h','<(editor_dir)/GLMain.h',
		'<(editor_dir)/ApplicationWindow.h','<(editor_dir)/ApplicationWindow.cpp','<(editor_dir)/WindowStructs.h','<(editor_dir)/standard_window.cpp','<(editor_dir)/standard_window.h'
	]

	 },
{
'target_name':'editor555',
'type':'executable',
'include_dirs':['D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\Programmierung\\ai_build\\src\\include'],
'msvs_settings':{
'VCLinkerTool':{
'AdditionalLibraryDirectories':['D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\Programmierung\\ai_build\\build\\code\\Debug'],
'AdditionalDependencies':['assimpd.lib','comctl32.lib','comdlg32.lib','Shell32.lib']
}
},
'sources':['<(editor_dir)/main.cpp','<(editor_dir)/dingens_struct_base.h','<(editor_dir)/egl_display_binding.h','<(editor_dir)/GLMain.h','<(editor_dir)/GLStructs.h','<(editor_dir)/ext/skia/GrGLFunctions.h','<(editor_dir)/IMGSTRUCTS.h','<(editor_dir)/OpenGL_Data_Types.h',
'<(editor_dir)/OpenGL_Utils.h','<(editor_dir)/OpenGLContext.h','<(editor_dir)/OpenGLImport.h','<(editor_dir)/3DObject_Serializer.h','<(editor_dir)/ApplicationUI_Control_Mgr.h','<(editor_dir)/ApplicationWindow.h','<(editor_dir)/Assimp_Material_Importer.h','<(editor_dir)/Assimp_Mesh_Importer.h',
'<(editor_dir)/Assimp_Utils.h','<(editor_dir)/Assimp_Utils_m_convert_16.h','<(editor_dir)/file_dialog.h','<(editor_dir)/ImageLoader.h','<(editor_dir)/Import_Object_Struct.h','<(editor_dir)/MessageLoop.h','<(editor_dir)/resource.h','<(editor_dir)/Resource_Loading.h','<(editor_dir)/standard_window.h',
'<(editor_dir)/SysUtils_Load_Library.h','<(editor_dir)/Window.h','<(editor_dir)/WindowStructs.h','<(editor_dir)/WinUtils.h',#uff jetzt noch die .cpp
'<(editor_dir)/egl_display_binding.cpp','<(editor_dir)/OpenGLContext.cpp','<(editor_dir)/3DObject_Serializer.cpp','<(editor_dir)/ApplicationUI_Control_Mgr.cpp','<(editor_dir)/ApplicationWindow.cpp','<(editor_dir)/Assimp_Material_Importer.cpp',
'<(editor_dir)/Assimp_Mesh_Importer.cpp','<(editor_dir)/Assimp_Utils.cpp','<(editor_dir)/file_dialog.cpp','<(editor_dir)/ImageLoader.cpp','<(editor_dir)/main.cpp','<(editor_dir)/MessageLoop.cpp','<(editor_dir)/standard_window.cpp','<(editor_dir)/SysUtils_Load_Library.cpp',
'<(editor_dir)/Win_Utils.cpp','<(editor_dir)/Window.cpp','<(editor_dir)/resource_script.rc','<(editor_dir)/APIs/OS/Win/UI_Controls/List_View.cpp','<(editor_dir)/APIs/OS/Win/UI_Controls/List_View.h','<(editor_dir)/APIs/OS/Win/UI_Controls/CheckBox.h',
'<(editor_dir)/APIs/OS/Win/UI_Controls/CheckBox.cpp','<(editor_dir)/APIs/OS/Win/UI_Controls/TrackBar.cpp','<(editor_dir)/APIs/OS/Win/UI_Controls/TrackBar.h','<(editor_dir)/APIs/OS/Win/UI_Controls/Menu.cpp','<(editor_dir)/APIs/OS/Win/UI_Controls/Menu.h'

]
},
  ]
}