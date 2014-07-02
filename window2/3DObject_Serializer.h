#ifndef THREED_OBJECT_SERIALIZER_H
#define THREED_OBJECT_SERIALIZER_H
#include <string>
#include "GLStructs.h"
#include <vector>
class THREED_Object_Serializer{
public:
	std::string serialize(THREEDObject * obj,int num_objects);
	std::string serialize(std::vector<THREEDObject> v);	
private:
	std::string split_char = ",";
	std::string getoutput(THREEDObject * obj);
	std::string get_Statement(std::string name,bool data);
	std::string get_Statement(std::string name, float* data, size_t data_size);
	std::string get_Statement(std::string name, int data);
	std::string get_Statement(std::string name, size_t data);
	std::string get_Statement(std::string name, unsigned int *data, size_t data_size);
};

#endif // !THREED_OBJECT_SERIALIZER_H
