#pragma once
#include <gtest\gtest.h>
#include "../Main/Physics_Input_Data.h"
#include "../gyp_workspace2/Geometry.h"
Physics::Main*physics;
TEST(BT_DATA, Init){
	physics = new Physics::Main();

}


TEST(BT_DATA, Mesh_ADD){
	btVector3 * vertices;

	btQuaternion rotation = btQuaternion(0, 0, 0, 1); btVector3 position = btVector3(0, 50, 0);
	unsigned short * indices; int num_indices; int num_vertices;
	btScalar mass = 3;
	auto d = Geometry::basic_Cube<unsigned short, btVector3>();
	vertices = d->vertices;
	num_vertices = d->num_vertices;
	num_indices = d->num_indices;
	indices = d->indices;
	physics->add_Mesh({ vertices, rotation, position, indices, num_indices, num_vertices, mass });
	
};
TEST(BT_DATA, Mesh_After_ADD_RIGIDBODY){
	EXPECT_EQ(physics->fallRigidBodies.size(),1);
	btRigidBody*rb = physics->fallRigidBodies[0];
	
}
TEST(BT_DATA, simulate_rigidbody_transform){
	physics->createStaticPlaneShape();
	for (int i = 0; i < 200; i++){
		physics->simulate_ActionHandler(1/60.0f);
		btTransform transform = physics->simulate_AfterActionHandler_getTransform(0);
		
	}
	btTransform transform = physics->simulate_AfterActionHandler_getTransform(0);
	::OutputDebugString(std::to_string(transform.getOrigin().getY()).c_str());
	EXPECT_NE(transform.getOrigin().getY(),50);

}