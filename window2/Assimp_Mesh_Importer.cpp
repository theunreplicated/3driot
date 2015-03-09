#include "Assimp_Mesh_Importer.h"

#include <assimp\postprocess.h>
#include <assimp\cimport.h>
#include <d3dx9math.h>
#include "Assimp_Utils.h"
#pragma comment(lib, "D3dx9.lib")

using std::string;
Assimp_Mesh_Importer::Assimp_Mesh_Importer(const char * file_path){
	//Assimp::Importer importer; //ändert irgendwie import path
	/*const aiScene **//*scene = import->ReadFile(file_path, /*aiProcessPreset_TargetRealtime_Quality*//*  aiProcess_CalcTangentSpace |
		/*aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
		|aiProcess_GenUVCoords
		| aiProcess_OptimizeMeshes
		);*/
	scene = aiImportFile(file_path, aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
		|aiProcess_GenUVCoords
		| aiProcess_OptimizeMeshes);

	if (!scene)
	{//witzigerweise akzeptiert assimp einige dlls,wie z.b. easyhook32.dll
		throw std::runtime_error("cannot import scene");
	}
	else{
		material_importer = new Assimp_Material_Importer(scene, const_cast<char *>(file_path));
		processScene();
		
	}

}
Assimp_Mesh_Importer::~Assimp_Mesh_Importer(){
	aiReleaseImport(scene);
	//import->FreeScene();
	delete import;
	delete material_importer;
	//delete scene;
	delete file_path;

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
			auto d = Assimp_Utils::convert_aiMatrix_to_float4x4(data);



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
	if (scene->HasMaterials()){
	unsigned int mat_index = mesh->mMaterialIndex;//nur ein Material
	ret_mesh.texture_data = material_importer->process_Material(mat_index);

	if (ret_mesh.texture_data.operation_failed){
		ret_mesh.has_texture = false;
	}
	else{
		ret_mesh.has_texture = true;
	}



}
	else{
		ret_mesh.has_texture = false;
	}

	if (mesh->HasTextureCoords(0)/*wohl ? @TODO*/){
		ret_mesh.has_tex_coord = true;
		ret_mesh.num_tex_coords = 2 * mesh->mNumVertices;
		ret_mesh.tex_coords = new float[ret_mesh.num_tex_coords];
		for (unsigned int i = 0; i<mesh->mNumVertices; i++){
			ret_mesh.tex_coords[i * 2] = mesh->mTextureCoords[0][i].x;
			ret_mesh.tex_coords[(i * 2) + 1] = mesh->mTextureCoords[0][i].y;

		}


	}
	else{
		ret_mesh.has_tex_coord = false;
	}
	ret_mesh.mesh_name = mesh->mName.C_Str();
	(mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE ? throw std::runtime_error("Primitive nicht supported/unterstützt") : (ret_mesh.draw_primitive = PR_TRIANGLE));
	ret_mesh.vertices = new float[mesh->mNumVertices * 3];
	for (unsigned int i = 0; i < mesh->mNumVertices; i++){

		ret_mesh.vertices[(i*3)] = mesh->mVertices[i].x;//TODO:get aiVector3d //ist das nötig
		ret_mesh.vertices[(i * 3) + 1] = mesh->mVertices[i].y;
		ret_mesh.vertices[(i * 3) + 2] = mesh->mVertices[i].z;
		
	}




	ret_mesh.size_vertices = mesh->mNumVertices * 3;//mal 3 muss wohl so sein

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
	
	return ret_mesh;
}
int Assimp_Mesh_Importer::CalculateBounds(aiNode* piNode, aiVector3D* p_avOut,
	const aiMatrix4x4& piMatrix)
{
	ai_assert(NULL != piNode);
	ai_assert(NULL != p_avOut);

	aiMatrix4x4 mTemp = piNode->mTransformation;
	mTemp.Transpose();
	aiMatrix4x4 aiMe = mTemp * piMatrix;

	for (unsigned int i = 0; i < piNode->mNumMeshes; ++i)
	{
		for (unsigned int a = 0; a < scene->mMeshes[
			piNode->mMeshes[i]]->mNumVertices; ++a)
			{
			aiVector3D pc = scene->mMeshes[piNode->mMeshes[i]]->mVertices[a];

			aiVector3D pc1;
			D3DXVec3TransformCoord((D3DXVECTOR3*)&pc1, (D3DXVECTOR3*)&pc,
				(D3DXMATRIX*)&aiMe);

			p_avOut[0].x = std::min(p_avOut[0].x, pc1.x);
			p_avOut[0].y = std::min(p_avOut[0].y, pc1.y);
			p_avOut[0].z = std::min(p_avOut[0].z, pc1.z);
			p_avOut[1].x = std::max(p_avOut[1].x, pc1.x);
			p_avOut[1].y = std::max(p_avOut[1].y, pc1.y);
			p_avOut[1].z = std::max(p_avOut[1].z, pc1.z);
		}
	}
	for (unsigned int i = 0; i < piNode->mNumChildren; ++i)
	{
		CalculateBounds(piNode->mChildren[i], p_avOut, aiMe);
	}
	return 1;//Quelle:assimp_view
}
aiMatrix4x4 Assimp_Mesh_Importer::ScaleAsset(void)
{//Quelle:assimp_view
	aiVector3D aiVecs[2] = { aiVector3D(1e10f, 1e10f, 1e10f),
		aiVector3D(-1e10f, -1e10f, -1e10f) };

	if (scene->mRootNode)
	{
		aiMatrix4x4 m;
		CalculateBounds(scene->mRootNode, aiVecs, m);
	}

	aiVector3D vDelta = aiVecs[1] - aiVecs[0];
	aiVector3D vHalf = aiVecs[0] + (vDelta / 2.0f);
	float fScale = 10.0f / vDelta.Length();

	aiMatrix4x4 g_mWorlds=aiMatrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-vHalf.x, -vHalf.y, -vHalf.z, 1.0f);
	aiMatrix4x4 gw2=aiMatrix4x4(
		fScale, 0.0f, 0.0f, 0.0f,
		0.0f, fScale, 0.0f, 0.0f,
		0.0f, 0.0f, fScale, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	aiMatrix4x4 g_mWorld = g_mWorlds*gw2;
	return g_mWorld;
}