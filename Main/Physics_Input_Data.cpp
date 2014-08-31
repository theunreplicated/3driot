#include "Physics_Input_Data.h"
namespace Physics{
	Main::Main(){
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();

		btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0, -10, 0));

	}

	//DynamicsWorld_is_initialized = true;
	//createStaticPlaneShape();
	void Main::createStaticPlaneShape(){
		btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);//nahe zu unendlich an einer Seite (hier vohl x ,trotz y spezifiziert)
		btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));/*btMotionState auch x,y,z, -Drehung; wenn hier y 0 dann res=2,da bie bullet die koord. die Mitte von dem Objekt ist*/
		btRigidBody::btRigidBodyConstructionInfo
			groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
		btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
		dynamicsWorld->addRigidBody(groundRigidBody);

	}
	void Main::add_Mesh(const Physics_TriangleMesh__description_info& inp){
		//somit kein statisches Mesh//@TODO: statisches hinzufuegen mit btbvhtrianglemeshshape
		btConvexTriangleMeshShape*fallShape = constructShapeFromTriangle<btConvexTriangleMeshShape>(inp.vertices,inp.indices, inp.num_indices, inp.num_vertices);

		//btBvhTriangleMeshShape* fallShape = unityStaticMeshTest<btBvhTriangleMeshShape>();//verboten f�r so was
		btTransform mesh_transform = btTransform(inp.rotation,inp.position);
		//btTransform *mesh_transform = &btTransform(Mesh_rotationQuat, Mesh_position);


		//btRigidBody*fallRigidBody;

		/*if (!is_vehicle){

		*/

		//btDefaultMotionState* fallMotionState =
		//	new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(mesh_transform);
		
		btVector3 fallInertia(0,0,0);
		fallShape->calculateLocalInertia(inp.mass, fallInertia);/*bei fallinteria o,0,0 brauch mans wohl nicht ungebdingt(vllt. falsche aussage),aber besser mit,da Widerstand http://stackoverflow.com/questions/16322080/what-does-having-an-inertia-tensor-of-zero-do-in-bullet*/
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(inp.mass, fallMotionState, fallShape, fallInertia);
		btRigidBody*fallRigidBody = new btRigidBody(fallRigidBodyCI);
		//vrb.RigidBody = fallRigidBody;
		/*}
		else{
		//is_vehicle
		ph_vehicle = new physics_vehiclespecific(dynamicsWorld);
		//btVector3* vertices_count = getVertices();
		//int* indices_count = getIndices();//@TODO: einiges,man kann noch nicht auf die Daten des AUtos zugreifen,aktuell
		ph_vehicle->add(fallShape,mesh_transform);
		fallRigidBody = ph_vehicle->m_pBody;
		}*/
		fallRigidBodies.push_back(fallRigidBody);
		dynamicsWorld->addRigidBody(fallRigidBody);


	}

	template <typename T>//@note:indices:Annahme:typ integer,Anzahl auch wichtig,da durch 3 geteilt wird
	T* Main::constructShapeFromTriangle(btVector3 * gVertices, int * gIndices, int num_indices, int num_vertices){

		//int num_indices = 36;
		//int num_vertices = 24;//vertexcount

		int vertStride = sizeof(btVector3);
		int indexStride = 3 * sizeof(int);

		//btVector3 * gVertices = new btVector3[num_vertices];
		//int * gIndices = new short[num_indices];
		//memcpy(gVertices, vertices, num_vertices*sizeof(btVector3));
		//memcpy(gIndices, indices, num_indices*sizeof(short));

		//impl
		//std::cout <<"<y"<< gVertices[23].x()<<"end";
		btTriangleIndexVertexArray * mesh = new btTriangleIndexVertexArray();
		btIndexedMesh indexed_mesh;
		indexed_mesh.m_vertexBase = (const unsigned char*)&gVertices[0].x();//oder mit &vertices[0]
		indexed_mesh.m_vertexStride = vertStride;
		indexed_mesh.m_vertexType = PHY_FLOAT;
		indexed_mesh.m_numVertices = num_vertices;

		indexed_mesh.m_triangleIndexBase = (const unsigned char*)&gIndices[0];
		indexed_mesh.m_triangleIndexStride = indexStride;
		indexed_mesh.m_indexType = PHY_INTEGER;
		indexed_mesh.m_numTriangles = num_indices / 3;

		mesh->addIndexedMesh(indexed_mesh);/*=default-Wert,typ der indices*///);

		//return new btBvhTriangleMeshShape(mesh, true);

		//	btTriangleIndexVertexArray* m_indexVertexArrays = new btTriangleIndexVertexArray(num_indices / 3, gIndices, indexStride, num_vertices, (btScalar*)&gVertices[0].x(), vertStride);


		//btVector3 aabbMin(-1, -1, -1), aabbMax(1, 1, 1);//nicht relevant
		//mesh->setPremadeAabb(aabbMin,aabbMax);
		//btTriangleIndexVertexArray*fst=NULL;
		//return new T(m_indexVertexArrays,true,aabbMin,aabbMax);
		return new T(mesh, true);
		//int dc = 5;
		//return &dc;

	}
	void Main::simulate_ActionHandler(float frequency/*z.b. 1/60.0f*/){
	dynamicsWorld->stepSimulation(frequency, 10);


	}
	btTransform Main::simulate_AfterActionHandler_getTransform(int Mesh_uid){//http://www.c-plusplus.de/forum/286796-full*/

		btTransform trans; btRigidBody*fallRigidBody = fallRigidBodies[Mesh_uid];//uid muss 0 sein
		//LOG("simulate[");
		//LOG(Mesh_uid);
		//LOG(trans.getOrigin().getY()); LOG("]");
		fallRigidBody->getMotionState()->getWorldTransform(trans);
		//myVector3 retpos = { trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() };
		//myQuaternion retquat = { trans.getRotation().getAxis().getX(), trans.getRotation().getAxis().getY(), trans.getRotation().getAxis().getZ(), trans.getRotation().getW() };
		//myTransform rettrf = { retpos, retquat };
		return trans;
	}
}