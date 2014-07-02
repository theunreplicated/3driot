#include "3DObject_Serializer.h"
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
	unsigned int num_data_items = sizeof(data_size) / sizeof(float);
	string ret=name+":[";
	for (unsigned int i = 0; i < num_data_items; i++){
		ret += data[i];
		ret += ",";


	}
	ret.pop_back();
	ret += "]";
	return ret;
}
string THREED_Object_Serializer::get_Statement(std::string name, int data){
	

	return name + ":" + std::to_string(data);
}
string THREED_Object_Serializer::get_Statement(std::string name, unsigned int *data, size_t data_size){/*@TODO:templates*/
	unsigned int num_data_items = sizeof(data_size) / sizeof(unsigned int);
	string ret = name + ":[";
	for (unsigned int i = 0; i < num_data_items; i++){
		ret += data[i];
		ret += ",";


	}
	ret.pop_back();
	ret += "]";
	return ret;
}
string THREED_Object_Serializer::getoutput(THREEDObject * obj){
	//zuerst RenderStructBase

	string ret = "";
	ret += get_Statement("has_texture", obj->has_texture);

	ret += split_char + get_Statement("has_tex_coord", obj->has_tex_coord);
	if (obj->has_tex_coord){
		ret += split_char + get_Statement("tex_coords", obj->tex_coords, obj->texcoords_totalsize);
		ret += split_char + get_Statement("tex_coords_totalsize", obj->texcoords_totalsize);

	}
	if (obj->has_texture){
	ret += split_char + get_Statement("texture_width",obj->texture_data.width);
	ret += split_char + get_Statement("texture_height", obj->texture_data.height);
	//@TODO:texture bytes+color Format
}
	ret += split_char + get_Statement("draw_primitive",obj->draw_primitive);
	ret += split_char + get_Statement("draw_method", obj->dm);//dm markt
	ret += split_char + get_Statement("draw_call_num_elements",obj->draw_call_num_elements);
	ret += split_char + get_Statement("enable_matrix",obj->enable_matrix);//@TODO:in GLMain auf das zurückgreifen
	if (obj->enable_matrix){

		ret += split_char + get_Statement("matrix", obj->matrix,sizeof(float)*16/*4*4matrix*/);
	}
	ret += split_char + get_Statement("has_indices", (obj->indices != NULL));
	if (obj->indices != NULL){
		ret += split_char + get_Statement("indices", obj->indices,obj->indices_totalsize);
		ret += split_char + get_Statement("indices_totalsize", obj->indices_totalsize);


	}


	ret += split_char + get_Statement("vertices", obj->vertices, obj->vertices_totalsize);
	ret += split_char + get_Statement("vertices_totalsize",  obj->vertices_totalsize);

	return ret;
}