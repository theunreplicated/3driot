#include "Assimp_Material_Importer.h"
#include <Windows.h>
unsigned int Assimp_Material_Importer::texture_id = 0;//sollte global sein
Assimp_Material_Importer::Assimp_Material_Importer(const aiScene*scene,char*model_file_path){
	m_scene = scene;
	image_loader = new ImageLoader();//@TODO:geh�rt hier nicht hin
	//if (scene->HasMaterials()){
		//for (unsigned int i = 0; i < scene->mNumMaterials; i++){
			//process_Material(scene->mMaterials[i]);

	m_model_file_path = model_file_path;
		//}

	//}

}
std::string Assimp_Material_Importer::getdirpath(char* chr){
	int len = strlen(chr); int lastlength; int last = len - 1;

	//chr+=(len-1);
	//for(int i=0;i<=len;i++){
	//if(strstr(chr,"\\")==NULL){break;}else{
	//lastlength=strlen(chr);
	//qDebug()<<"--"<<chr<<lastlength;chr++;};

	//}
	char * l = "\\";

	while (chr[last] != *l){
		last--;
	}
	//delete l;
	//last ist letztes Element,von 0 bis dahin brauchen wir die Strings


	//buffer[0]=l[0];
	//buffer=
	std::string buffer;
	for (int i = 0; i<last/*extra -1*/; i++){
		buffer += chr[i];

	}

	return buffer;

}
image_stor Assimp_Material_Importer::process_Material(int material_key){
	aiMaterial*material = m_scene->mMaterials[material_key];
	aiTextureType type = aiTextureType_DIFFUSE;//@TODO:textur-typ muss �nderbar sein
	//@TODO:mit mat->getTextureCount testen
	unsigned int num_textures = material->GetTextureCount(type);
	if (num_textures == 0){ image_stor is; is.operation_failed = true; return is; }
	int texIndex = 0;
	aiString path;  // filename
	//http://www.lighthouse3d.com/cg-topics/code-samples/importing-3d-models-with-assimp/
	aiReturn texFound = material->GetTexture(type, texIndex, &path);
	while (texFound == AI_SUCCESS) {
		//fill map with textures, OpenGL image ids set to 0
		//textureIdMap[path.data] = 0;
		// more textures?
		texIndex++;
		texFound = material->GetTexture(type, texIndex, &path);
	}
	std::string real_texture_path = getdirpath(m_model_file_path);
	const char*assimp_path_c = path.C_Str();
	std::string assimp_path = std::string(assimp_path_c); std::string real_texture_path_final;
	//if (assimp_path.length() >= 2){
	if (assimp_path_c[1] == ':'){//@TODO:richtiger check o path relativ ist,das hier geht nur auf den laufwerksbuchstaben
		//also nicht anhaengen
		real_texture_path_final = assimp_path;//sinnlos hier mit den casts
	}
	else{
		real_texture_path_final = real_texture_path + "\\" + assimp_path;

	}
	
	
	return import_texture(real_texture_path_final.c_str());//anstatt real_texture_path.c_str()

}
image_stor Assimp_Material_Importer::import_texture(const char* texture_file_path){
	bool found = false;
	image_stor is;
	for (image_stor/*&*/ stor : loaded_image_files_data){
		if (stor.texture_name == texture_file_path){ found = true; is = stor; break; }
		//@TODO:check ob geht
	}
	if (!found){//falls 2mal gleiche Referenz
		Image_Load_Result data = image_loader->load(texture_file_path);
		
		//int *test_ret = data.test;
		//int d2 = *test_ret;
		is.color_type = data.color_type;
		is.bits = data.bits;
		//is.dib = data.dib;
		is.width = data.width;
		is.height = data.height;
		is.format = data.format;
		//is.unload = data.unload;
		is.texture_name = texture_file_path;
//		is.texture_bytes = data.texture_bytes;
		is.global_texture_id = texture_id;

		//unsigned int i1 = Assimp_Material_Importer::texture_id;
	    texture_id++;
		is.file_name = data.file_path;
		is.file_path = getdirpath(m_model_file_path);
		loaded_image_files_data.push_back(is);
	}
	//std::string hohohohhiihihhahatrololol = std::to_string(is.global_texture_id);
	//OutputDebugStringA("here comes the winner");
	//OutputDebugStringA(hohohohhiihihhahatrololol.c_str());
	return is;

}