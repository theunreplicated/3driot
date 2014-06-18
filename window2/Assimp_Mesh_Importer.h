#ifndef Assimp_Mesh_Importer_H
#define Assimp_Mesh_Importer_H
#include <string>
#include <assimp\scene.h>
#include <vector>
#include "GLStructs.h"
class Assimp_Mesh_Importer{

public:
	Assimp_Mesh_Importer(const char * file_path);
	std::vector<Mesh_RenderObject> stor_meshes_render;//@TODO: wieder auf den Heap machen,alten Code bezüglich Heap fixen,ich wette es  lag an diesem Konstrukt push_back(&vert)-und war nur noch zufällig im Speicher
	Mesh_RenderObject get_render_obj(int index);
private:
	std::vector<Mesh_RenderObject> stor_meshes;
	const char * file_path;
	const aiScene *scene;
	void processScene();
	void node_traverse(aiNode * node, std::vector<aiMatrix4x4/***/>matrices);
	void node_handler(aiNode*node, std::vector<aiMatrix4x4/***/>matrices);
	Mesh_RenderObject mesh_read(aiMesh * mesh);
};
#endif