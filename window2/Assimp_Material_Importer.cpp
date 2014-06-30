#include "Assimp_Material_Importer.h"

Assimp_Material_Importer::Assimp_Material_Importer(const aiScene*scene){
	m_scene = scene;
	image_loader = new ImageLoader();//@TODO:gehört hier nicht hin
	//if (scene->HasMaterials()){
		//for (unsigned int i = 0; i < scene->mNumMaterials; i++){
			//process_Material(scene->mMaterials[i]);


		//}

	//}

}
image_stor Assimp_Material_Importer::process_Material(int material_key){
	aiMaterial*material = m_scene->mMaterials[material_key];
	aiTextureType type = aiTextureType_DIFFUSE;//@TODO:textur-typ muss änderbar sein
	//@TODO:mit mat->getTextureCount testen
	unsigned int num_textures = material->GetTextureCount(type);
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
	return import_texture(path);

}
image_stor Assimp_Material_Importer::import_texture(aiString texture_file_path){
	bool found = false;
	image_stor is;
	for (image_stor/*&*/ stor : loaded_image_files_data){
		if (stor.texture_name == texture_file_path){ found = true; is = stor; break; }
		//@TODO:check ob geht
	}
	if (!found){//falls 2mal gleiche Referenz
		Image_Load_Result data = image_loader->load(texture_file_path.C_Str());
		
		is.bits = data.bits;
		is.dib = data.dib;
		is.width = data.width;
		is.height = data.height;
		is.texture_name = texture_file_path;
		loaded_image_files_data.push_back(is);
	}
	return is;

}