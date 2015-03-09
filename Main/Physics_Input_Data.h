#ifndef INC_PHYSICS_INPUT_DATA_H
#define INC_PHYSICS_INPUT_DATA_H
#include <btBulletDynamicsCommon.h>
#include <vector>
namespace Physics{
	struct Physics_TriangleMesh__description_info{
		btVector3 * vertices;
		btQuaternion rotation; btVector3 position;
		unsigned short * indices;unsigned int num_indices; unsigned int num_vertices;
		btScalar mass;
		

	};
	class Main{
	public:
		Main();
		void createStaticPlaneShape();
		void add_Mesh(const Physics_TriangleMesh__description_info& inp);//http://www.bulletphysics.org/Bullet/phpBB3/viewtopic.php?p=&f=&t=3627
		void simulate_ActionHandler(float frequency/*z.b. 1/60.0f*/);
		btTransform simulate_AfterActionHandler_getTransform(int Mesh_uid);
		btDiscreteDynamicsWorld* dynamicsWorld;
		std::vector<btRigidBody*>fallRigidBodies;
	private:
		
		template <typename T>
		T* constructShapeFromTriangle(btVector3 * gVertices, unsigned short * gIndices, unsigned int num_indices,unsigned  int num_vertices);
		

	};


}


#endif