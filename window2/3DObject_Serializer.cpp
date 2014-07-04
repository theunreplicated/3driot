#include "3DObject_Serializer.h"
#include <sstream>
#include <ostream>
#include <fstream>
#include <iostream>
#include "WinUtils.h"
using std::string;

string THREED_Object_Serializer::serialize(THREEDObject * obj, int num_objects){
	string ret = "";
	for (unsigned int i = 0; i < num_objects; i++){
		ret += "{"+getoutput(&obj[i])+"}";


	}
	return ret;
}
string THREED_Object_Serializer::serialize(std::vector<THREEDObject>v){
	string ret = "";
	//for (unsigned int i = 0; i < num_objects; i++){
	//	ret += "{" + getoutput(&obj[i]) + "}";


	//}
	for (THREEDObject data : v){
		ret += "{" + getoutput(&data) + "}";

	}
	return ret;
}
string THREED_Object_Serializer::get_Statement(string name, bool data){

	return name + ":" + (data ? "1" : "0");
}
string THREED_Object_Serializer::get_Statement(std::string name, size_t data){


	return name + ":" + std::to_string(data);
}
string THREED_Object_Serializer::get_Statement(std::string name, float* data, size_t data_size){
	unsigned int num_data_items = data_size / sizeof(float);
	string ret=name+":[";
	for (unsigned int i = 0; i < num_data_items; i++){
		std::ostringstream ss;
		ss<<data[i];
		ret += ss.str();
		ret += ";";


	}
	ret.pop_back();
	ret += "]";
	return ret;
}
string THREED_Object_Serializer::get_Statement(std::string name, int data){
	

	return name + ":" + std::to_string(data);
}
string THREED_Object_Serializer::get_Statement(std::string name, unsigned int *data, size_t data_size){/*@TODO:templates*/
	unsigned int num_data_items =data_size / sizeof(unsigned int);
	string ret = name + ":[";
	for (unsigned int i = 0; i < num_data_items; i++){
		std::stringstream ss;
		ss << data[i];
		ret += ss.str();
		ret += ";";


	}
	ret.pop_back();
	ret += "]";
	return ret;
}
string getFileName(string file_name){
	return file_name.substr(file_name.find_last_of("\\") + 1);

}
string getFileExtensionName(string file_name){
	
	return file_name.substr(file_name.find_last_of(".") + 1);

}
string THREED_Object_Serializer::getoutput(THREEDObject * obj){
	//zuerst RenderStructBase

	string ret = "";
	ret += get_Statement("has_texture", obj->has_texture);

	ret += split_char + get_Statement("has_tex_coord", obj->has_tex_coord);
	if (obj->has_tex_coord){
		ret += split_char + get_Statement("tex_coords_totalsize", obj->texcoords_totalsize);
		ret += split_char + get_Statement("tex_coords", obj->tex_coords, obj->texcoords_totalsize);
		

	}
	//if (obj->has_texture){
	ret += split_char + get_Statement("texture_width",obj->texture_data.width);
	ret += split_char + get_Statement("texture_height", obj->texture_data.height);
	//@TODO:texture bytes+color Format
//}
	
	ret += split_char + get_Statement("draw_primitive",obj->draw_primitive);
	ret += split_char + get_Statement("draw_method", obj->dm);//dm markt
	ret += split_char + get_Statement("draw_call_num_elements",obj->draw_call_num_elements);
	ret += split_char + get_Statement("enable_matrix",obj->enable_matrix);//@TODO:in GLMain auf das zurückgreifen
	if (obj->enable_matrix){

		ret += split_char + get_Statement("matrix", obj->matrix,sizeof(float)*16/*4*4matrix*/);
	}
	ret += split_char + get_Statement("has_indices", (obj->indices != NULL));
	if (obj->indices != NULL){
		ret += split_char + get_Statement("indices_totalsize", obj->indices_totalsize);
		ret += split_char + get_Statement("indices", obj->indices,obj->indices_totalsize);
	


	}

	ret += split_char + get_Statement("vertices_totalsize", obj->vertices_totalsize);
	ret += split_char + get_Statement("vertices", obj->vertices, obj->vertices_totalsize);
	ret += split_char + get_Statement("texture_format", obj->texture_data.format);
	
	
	/*unsigned char* tex_bits = new unsigned char[obj->texture_data.width*obj->texture_data.height];

	for (int j = 0; j < obj->texture_data.width*obj->texture_data.height; j++)
	{
		tex_bits[j] = obj->texture_data.texture_bytes[j];

	}//falls das überhaupt nötig ist
	std::string sName(reinterpret_cast<char*>(tex_bits));*/
	Win_Utils*wn = new Win_Utils();
	string p2ath = /*obj->texture_data.file_path + "\\" +*/ obj->texture_data.file_name;
	//string fn=getFileName(obj->texture_data.file_name);
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);//path von exe//da assimp wohl den include path auf desktop setzt irgendwie?
	//string d = "texture" + std::to_string(num_texture_file_ids) + ".blubtex";
	//string realpath = wn->getdirpath(path) + "\\"+d;
	//wn->saveToFile(realpath.c_str(),sName.c_str());
	std::string file_extension = getFileExtensionName(p2ath);
	std::string n_copy_d = wn->getdirpath(path) + "\\" + "texture" + std::to_string(num_texture_file_ids)+"."+file_extension;
	
	::CopyFile(p2ath.c_str(),n_copy_d.c_str(), FALSE);
	//typedef std::basic_ofstream<unsigned char, std::char_traits<unsigned char> > uofstream;
	//uofstream out;
	//out.open(realpath, std::ios::out | std::ios::binary);
	//uofstream.ope
	//out.write(/*reinterpret_cast<char*>(*/obj->texture_data.bits/*)*/, obj->texture_data.width*obj->texture_data.height);
	//out.close();
	ret += split_char + "texture_id:" + std::to_string(num_texture_file_ids);
	//ret += split_char + 
	num_texture_file_ids++;
	ret += split_char + "texture_file_extension:" + file_extension;
	return ret;
}