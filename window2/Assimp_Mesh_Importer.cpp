#include "Assimp_Mesh_Importer.h"
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

using std::string;
Assimp_Mesh_Importer::Assimp_Mesh_Importer(const char * file_path){
	Assimp::Importer importer; //ändert irgendwie import path
	/*const aiScene **/scene = importer.ReadFile(file_path, /*aiProcessPreset_TargetRealtime_Quality*/  aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
		|aiProcess_GenUVCoords
		| aiProcess_OptimizeMeshes
		);

	if (!scene)
	{
		throw new std::runtime_error("cannot import scene");
	}
	else{
		processScene();

	}

}
void ASSERT(bool cond){
	if (!cond) throw std::runtime_error("Assertion failed in a very hard way");

}
void Assimp_Mesh_Importer::node_traverse(aiNode * node, std::vector<aiMatrix4x4>matrices)
{
	if (node != 0){
		(!node->mTransformation.IsIdentity() ? matrices.push_back(node->mTransformation):0);
		node_handler(node,matrices);
		for (int i = 0; i < node->mNumChildren; i++){


			node_traverse(node->mChildren[i],matrices);
		}
	}

}
Mesh_RenderObject Assimp_Mesh_Importer::get_render_obj(int index){


	return /***/stor_meshes_render[index];
}
void Assimp_Mesh_Importer::processScene(){
	
	for (int i = 0; i < scene->mNumMeshes; i++){
		stor_meshes.push_back(/*&*/mesh_read(scene->mMeshes[i]));

	}
	std::vector<aiMatrix4x4> s;
	node_traverse(scene->mRootNode,s);

}//TODO:nodes zu einer eigenen Klasse
void Assimp_Mesh_Importer::node_handler(aiNode*node,std::vector<aiMatrix4x4/***/>matrices){
	//const char * s = node->mName.C_Str();
	//aiMesh * mesh;
	for (unsigned int i = 0; i < node->mNumMeshes; i++){
		//mesh = scene->mMeshes[node->mMeshes[i]];
		//const char* s = mesh->mName.C_Str();
		//Name steht wohl im Mesh_Name nicht immer zuverlässig drin,besser direkt von der Node
		std::vector<std::array<std::array<float, 4>, 4>> mat_vec;
		for (aiMatrix4x4 data : matrices){
			std::array<std::array<float, 4>, 4>d ;
			d[0][0] = data.a1;
			d[0][1] = data.a2;
			d[0][2] = data.a3;
			d[0][3] = data.a4;

			d[1][0] = data.b1;
			d[1][1] = data.b2;
			d[1][2] = data.b3;
			d[1][3] = data.b4;

			d[2][0] = data.c1;
			d[2][1] = data.c2;
			d[2][2] = data.c3;
			d[2][3] = data.c4;

			d[3][0] = data.d1;
			d[3][1] = data.d2;
			d[3][2] = data.d3;
			d[3][3] = data.d4;



			mat_vec.push_back(d);


		}
		const char* node_name = node->mName.C_Str();
		char* nnew_node_name = new char[strlen(node_name)];
		//memcpy(nnew_node_name, node_name, sizeof(node_name));
		strcpy_s(nnew_node_name, strlen(node_name)+1, node_name);
		stor_meshes[node->mMeshes[i]]/*->*/.transform_matrices = mat_vec;
		stor_meshes[node->mMeshes[i]].node_name = nnew_node_name;
		stor_meshes_render.push_back(stor_meshes[node->mMeshes[i]]);
	
		//Wenn ich hier allokiere gehts
		//stor_meshes_render.back().node_name =nnew_node_name;//Das bringt nichts imBezug des Fix des Heap-PRobbll
	}



}
Mesh_RenderObject Assimp_Mesh_Importer::mesh_read(aiMesh * mesh){
	Mesh_RenderObject ret_mesh;
	ret_mesh.mesh_name = mesh->mName.C_Str();
	(mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE ? throw std::runtime_error("Primitive nicht supported/unterstützt") : (ret_mesh.draw_primitive = PR_TRIANGLE));
	ret_mesh.vertices = new float[mesh->mNumVertices * 3];
	for (unsigned int i = 0; i < mesh->mNumVertices; i++){

		ret_mesh.vertices[(i*3)] = mesh->mVertices[i].x;//TODO:get aiVector3d
		ret_mesh.vertices[(i * 3) + 1] = mesh->mVertices[i].y;
		ret_mesh.vertices[(i * 3) + 2] = mesh->mVertices[i].z;
		
	}
	ret_mesh.size_vertices = mesh->mNumVertices * 3;

	if (mesh->HasFaces())
	{

		//INDICES
		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			const struct aiFace  face = mesh->mFaces[j];

			//zuerst mal auf dem Stack um keine Memory Leaks zu erzeugen(bin mir aber nicht ganz sicher ob welche entstehen,da s n error bei delete gibt)
			ret_mesh.num_indices += face.mNumIndices;

		}

		 ret_mesh.indices = new unsigned int[ret_mesh.num_indices];
		//copy n paste->am besten wären hier Coroutinen
		int ins_indices_count = 0;
		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			const struct aiFace  face = mesh->mFaces[j];
			for (unsigned int i = 0; i < face.mNumIndices; i++){

				ret_mesh.indices[ins_indices_count] = face.mIndices[i];//TODO:numIndices
				//aiIndices[vcount+2]=face.mIndices[1];
				//aiIndices[vcount+3]=face.mIndices[2];
				//vcount += 1;
				ins_indices_count++;
				//qDebug()<<face.mIndices[0]<<face.mIndices[1]<<face.mIndices[2];
			}
		}
	}
	if (mesh->HasTextureCoords(0)/*wohl ? @TODO*/){
		ret_mesh.has_tex_coord = true;
		ret_mesh.tex_coords = new float[2 * mesh->mNumVertices];
		for (unsigned int i = 0; i<mesh->mNumVertices; i++){
			ret_mesh.tex_coords[i * 2] = mesh->mTextureCoords[0][i].x;
			ret_mesh.tex_coords[(i * 2) + 1] = mesh->mTextureCoords[0][i].y;

		}


	}
	return ret_mesh;
}