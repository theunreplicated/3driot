#ifndef INC_ASSIMP_MATERIAL_IMPORTER_H
#define INC_ASSIMP_MATERIAL_IMPORTER_H
#include <assimp\scene.h>
#include "ImageLoader.h"
#include <vector>
#include <string>
struct image_stor :Image_Load_Result{
	const char* texture_name; 

};
class Assimp_Material_Importer{
private:
	const aiScene *m_scene;
	ImageLoader * image_loader;
	char* m_model_file_path;
public:
	std::string getdirpath(char* chr);
	std::vector<image_stor> loaded_image_files_data;
	Assimp_Material_Importer(const aiScene*scene, char*model_file_path);
	image_stor process_Material(int material_key);
	image_stor import_texture(const char* texture_file_path);
};
#endif