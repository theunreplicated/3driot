#include "File_Parser.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <Windows.h>
#include "GLStruct_Copy.h"
#include <sstream>
#include <glm\gtc\type_ptr.hpp>
#include <glm\mat4x4.hpp>
#include "../window2/WinUtils.h"
struct simple_Vector{
	float *x, *y, *z;
	bool operator==(simple_Vector * comp){
	
		return (*x == *(comp->x)) && (*y == *(comp->y)) && (*z == *(comp->z));
	};
};
using std::ifstream; using std::string; using std::vector;
THREEDObject optimize_THREEDOBJECT(THREEDObject obj){
	int count = 0;
	int num_vertices = (obj.vertices_totalsize / sizeof(float)) / 3;
	bool * erase_represenation = new bool[num_vertices];
	for (unsigned short i = 0; i < num_vertices; i++){
		erase_represenation[i] = false;

	}//have to be removed=erase_represenation !!unwcitchtuig eger
	simple_Vector* rrr/*hat nichts zu bedeuten,wie immer,roobert der rrrroadster*/ = new simple_Vector[num_vertices];
	for (unsigned int i = 0; i < num_vertices; i++){
		rrr[i] = { &(obj.vertices[(i * 3)]), &(obj.vertices[(i * 3)+1]), &(obj.vertices[(i * 3)+2]) };

	}

	for (unsigned int i = 0; i < num_vertices; i++){
		for (unsigned int j = i; j < num_vertices; j++){
			if (rrr[i] == &rrr[j]){
				if (erase_represenation[j] != false){
					erase_represenation[j] = true;
					continue;
				}
			}

		}

	}

	
	int dv = count;
	return obj;
}

FileParser::FileParser(std::string file_name){


	img_loader = new ImageLoader();
	ifstream VertexShaderStream(file_name, std::ios::in);

	if (VertexShaderStream.is_open())
	{
		
		while (getline(VertexShaderStream, file_contents))
			//file_contents += "\n" + Line;
		VertexShaderStream.close();
	}
	else{
		throw std::runtime_error("Could not be opened-Datei kann nicht ge�ffnet werden");

	}
	//parse();


}
vector<string> explode(char expchar, string data){
	vector<string>ret;
	string push_data = "";
	for (unsigned int i = 0; i < data.length(); i++){
		push_data += data[i];
		if (data[i] == expchar){
			ret.push_back(push_data);
			push_data = "";
		}

	}
	ret.push_back(push_data);
	return ret;
}
vector<string> strtoarray(string str){
	str = str.substr(0, str.size() - 1);
	str = str.substr(1, str.size());
	vector<string>data = explode(';',str);

	return data;
}

vector<THREEDObject> FileParser::parse(){
	//string mode = "begin";
	//{}{}
	vector<THREEDObject> vvvv;
	vector<string> splitted_into_objects = explode('}',file_contents);
	
	vector<string>sep;
	for (string d : splitted_into_objects){
		d.erase(d.begin());
		if (d!=""){
			
			THREEDObject data = handle_object(d);
			data = optimize_THREEDOBJECT(data);
			vvvv.push_back(data);



		}


	}//@TODO:kann aktuell nur mit einem Objekt umgehen
	
	

	return vvvv;//aaaa!!!!
}
THREEDObject FileParser::handle_object(std::string dat){
	Win_Utils*wn = new Win_Utils();
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);
	std::string pathx = wn->getdirpath(path);
	vector<string>exp_commas = explode(',', dat);
	THREEDObject obj;  int texture_id;
	bool texture_id_gibts = false;//@TODO:k�nnte auch in for-Schleife kommen,Position unklar,nochmals checken
	for (std::vector<string>::size_type i = 0; i != exp_commas.size(); i++)//http://stackoverflow.com/questions/409348/iteration-over-vector-in-c
	{
		//if (i % 2 == 0){
		//gerade

		string name = exp_commas[i];
		vector<string> st = explode(':', name);
		string str = st[1];
		if (str[str.size() - 1] == ','){
			str = str.substr(0, str.size() - 1);
		}
		if (st[0][st[0].size() - 1] == ':'){
			st[0] = st[0].substr(0, st[0].size() - 1);
		}

		string sf = st[0];
		if (st[0] == "has_texture"){
			obj.has_texture = (str == "1" ? true : false);

		}
		if (st[0] == "has_tex_coord"){
			obj.has_tex_coord = (str == "1" ? true : false);

		}
		if (st[0] == "tex_coords_totalsize"){
			obj.texcoords_totalsize = atoi(str.c_str());

		}
		if (st[0] == "tex_coords"){

			vector<string> data = strtoarray(str);
			int num_data = obj.texcoords_totalsize / sizeof(float);
			obj.tex_coords = new float[num_data];
			if (data.size() != num_data){ throw std::runtime_error("Schluss jetzt-mismatsch bei Tex Coords"); }
			for (int i = 0; i < num_data; i++){
				std::stringstream sstr;
				sstr << data[i];
				float f;
				sstr >> f;//http://www.c-plusplus.de/forum/111034-full
				obj.tex_coords[i] = f;
			}

		}
		if (st[0] == "texture_width"){
			obj.texture_data.width = atoi(str.c_str());
		}
		if (st[0] == "texture_height"){
			obj.texture_data.height = atoi(str.c_str());

		}
		if (st[0] == "draw_primitive"){
			obj.draw_primitive = static_cast<PrimitiveType>(atoi(str.c_str()));

		}
		if (st[0] == "draw_method"){
			obj.dm = static_cast<draw_method>(atoi(str.c_str()));

		}
		if (st[0] == "draw_call_num_elements"){
			obj.draw_call_num_elements = atoi(str.c_str());

		}
		if (st[0] == "enable_matrix"){//eigentlich veraltet
			obj.enable_matrix = (str == "1" ? true : false);
		}
		if (st[0] == "has_indices"){
			obj.has_indices = (str == "1" ? true : false);

		}//@TODO:matrix auslesen
		if (st[0] == "indices_totalsize"){
			obj.indices_totalsize = atoi(str.c_str());

		}
		if (st[0] == "indices"){
			vector<string>data = strtoarray(str);
			int num_data = obj.indices_totalsize / sizeof(unsigned int);

			if (num_data != data.size()) { throw std::runtime_error("mismatch"); }
			obj.indices = new unsigned int[num_data];
			for (int i = 0; i < num_data; i++){
				std::stringstream sstr;
				sstr << data[i];
				unsigned int f;
				sstr >> f;//http://www.c-plusplus.de/forum/111034-full
				obj.indices[i] = f;
			}
		}
		if (st[0] == "vertices_totalsize"){
			obj.vertices_totalsize = atoi(str.c_str());

		}
		if (st[0] == "vertices"){
			vector<string>data = strtoarray(str);
			int num_data = obj.vertices_totalsize / sizeof(float);

			if (num_data != data.size()) { throw std::runtime_error("mismatch-musicmatch jukebox"); }
			obj.vertices = new float[num_data];
			for (int i = 0; i < num_data; i++){
				std::stringstream sstr;
				sstr << data[i];
				float f;
				sstr >> f;//http://www.c-plusplus.de/forum/111034-full
				obj.vertices[i] = f;
			}


		}
		if (st[0] == "texture_format"){
			obj.texture_data.format = atoi(str.c_str());

		}
		/*if (st[0] == "texture_id"){
		//str = str.substr(0, st[0].size() - 2);
		std::stringstream ssd;
		ssd << atoi(str.c_str());
		string svv;
		ssd >> svv;
		string filename = "texture"+svv+".blubtex";
		typedef std::basic_ifstream<unsigned char, std::char_traits<unsigned char> > uifstream;

		uifstream VertexShaderStream(filename, std::ios::in);
		string tex_file;
		unsigned char *tex_data = new unsigned char[obj.texture_data.width*obj.texture_data.height];
		if (VertexShaderStream.is_open())
		{
		VertexShaderStream.read(/*reinterpret_cast<char*>(*//*tex_data)*//*, obj.texture_data.width*obj.texture_data.height);
		//while (getline(VertexShaderStream, tex_file))
		//file_contents += "\n" + Line;
		/*VertexShaderStream.close();//hmm.komisch
		//}



		}
		else{
		throw std::runtime_error("Could not be opened-textureDatei kann nicht ge�ffnet werden");

		}

		//string dcc = tex_file;

		//strcpy((char*)tex_data, dcc.c_str());
		obj.texture_data.bits = tex_data;
		}*/

		if (st[0] == "texture_id"){
			//texture_id = str.substr(0, str.size() - 1);
			texture_id = atoi(str.c_str());
			texture_id_gibts = true;
		}
		if (st[0] == "texture_file_extension"){
			if (obj.has_texture){
				string tex = str.substr(0, str.size() - 1);
				std::stringstream ss;
				if (!texture_id_gibts){ throw std::runtime_error("no occurence of texture_id in this part of the render-model description(aka threedobject),but a texture should exists due to the description of a texture file extension"); }
				ss << texture_id;
				string texture_id_s;
				ss >> texture_id_s;
				string filename = pathx+"\\"+"texture" + texture_id_s + "." + tex;
				image_stor res = img_loader->load(filename.c_str());//@TODO:�ndern,und zwar abh�ngig vom path von main shotgun!!AK-47,viel mehr kenn ich net
				obj.texture_data.bits = res.bits;
				//@TODO:devil id's mitkopieren,und zwar f�r das free() nach dem Laden
			}
		}
		//if (st)


		//}
		//else{
		//ungerade

		//}


	}

	//int dc = 5 / 0;
	//Optimierung
	//mehrmals vorhandene l�schen

	





	return obj;


}