#ifndef INC_OpenGL_UTILS_CPP
#define INC_OpenGL_UTILS_CPP
#include "../window2/OpenGLImport.h"
#include <fstream>
#include <string>
#include <iostream>
#include "../window2/Resource_Loading.h"
#include "../window2/resource.h"
namespace OpenGL_Utils{
	using namespace OGL;

	void LoadShaders(/*const char * vertex_file_path, const char * fragment_file_path,*/bool use_legacy_opengl_shaders, GLuint ProgramID){
		//Quelle:irgendwo her,keina Ahnung mehr
		//kann bei assimp dingens datei nicht �ffnen
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		//const char * filepath=vertex_file_path ;
		//vertex_file_path = "D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\Visual Studio 2013\\Projects\\window2\\window2\\";

		/*std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

		if (VertexShaderStream.is_open())
		{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
		VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
		}*/

		// Read the Fragment Shader code from the file
		/*std::string FragmentShaderCode;//streams werden nicht ge�ffnet-Problem
		std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
		if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
		FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
		}*/

		GLint Result = GL_FALSE;
		int InfoLogLength;


		// Compile Vertex Shader
		// printf("Compiling shader : %s\n", vertex_file_path);


		char const * VertexSourcePointer = (use_legacy_opengl_shaders ? Resource::CommonLoad(IDR_MYVERTEXSHADER, VERTEX_SHADER_PATH) : Resource::CommonLoad(IDR_MYVERTEXSHADER_ESSL, VERTEX_SHADER_PATH_ESSL));
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		//glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		//glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		// std::vector<char> VertexShaderErrorMessage(InfoLogLength);
		//glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		//fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

		// Compile Fragment Shader
		// printf("Compiling shader : %s\n", fragment_file_path);
		//char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		char const * FragmentSourcePointer = (use_legacy_opengl_shaders ? Resource::CommonLoad(IDR_MYFRAGMENTSHADER, FRAGMENT_SHADER_PATH) : Resource::CommonLoad(IDR_MYFRAGMENTSHADER_ESSL, FRAGMENT_SHADER_PATH_ESSL));
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		//glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		// glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		//std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
		//glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		//fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

		// Link the program
		//fprintf(stdout, "Linking program\n");

		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the program
		//glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		// glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		//std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
		//glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		//fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		//return ProgramID;
	}
};
#endif