#ifndef INC_PHYSICS_INPUT_DATA_H
#define INC_PHYSICS_INPUT_DATA_H
#include <btBulletDynamicsCommon.h>
#include <vector>
namespace Physics{
	struct Physics_TriangleMesh__description_info{
		btVector3 * vertices;
		btQuaternion rotation; btVector3 position;
		int * indices; int num_indices; int num_vertices;
		btScalar mass;
		

	};
	class Main{
	public:
		Main();
		void createStaticPlaneShape();
		void add_Mesh(const Physics_TriangleMesh__description_info& inp);//http://www.bulletphysics.org/Bullet/phpBB3/viewtopic.php?p=&f=&t=3627
	private:
		//std::vector<btRigidBody*>fallRigidBodies;
		template <typename T>
		T* constructShapeFromTriangle(btVector3 * gVertices, int * gIndices, int num_indices, int num_vertices);
		btDiscreteDynamicsWorld* dynamicsWorld;

	};


}


#endif