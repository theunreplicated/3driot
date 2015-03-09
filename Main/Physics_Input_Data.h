#ifndef INC_PHYSICS_INPUT_DATA_H
#define INC_PHYSICS_INPUT_DATA_H
#include <btBulletDynamicsCommon.h>
#include <vector>
namespace Physics{
	//template <typename indices_type>
	struct Physics_TriangleMesh__description_info{
		float * vertices;
		btQuaternion rotation; btVector3 position;
		unsigned int * indices; unsigned int num_indices; unsigned int num_vertices;
		btScalar mass;
		

	};
	class Main{
	public:
		Main();
		void createStaticPlaneShape();
		//template <typename indices_type>//Das ist echt nervig bei templates
		
		void simulate_ActionHandler(float frequency/*z.b. 1/60.0f*/);
		btTransform simulate_AfterActionHandler_getTransform(int Mesh_uid);
		btDiscreteDynamicsWorld* dynamicsWorld;
		std::vector<btRigidBody*>fallRigidBodies;
		//template <typename indices_type>
		void add_Mesh(const Physics_TriangleMesh__description_info& inp, PHY_ScalarType indices_scalartype);//http://www.bulletphysics.org/Bullet/phpBB3/viewtopic.php?p=&f=&t=3627
	

	private:
		
		template <typename T>
		T* constructShapeFromTriangle(float * gVertices, unsigned int * gIndices, unsigned int num_indices, unsigned  int num_vertices, PHY_ScalarType indices_scalartype);
		

	};


}

//#include "../Info-Proj-Test-Projekt/Physics_Input_data_templated_impl.cpp"
#endif