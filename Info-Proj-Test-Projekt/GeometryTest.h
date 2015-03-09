#pragma once
#include <gtest\gtest.h>
#include "../Main/Physics_Input_Data.h"
#include "../gyp_workspace2/Geometry.h"
unsigned short indices[] = {
	0, 1, 2,
	2, 3, 0,
	// Back
	4, 6, 5,
	4, 7, 6,
	// Left
	2, 7, 3,
	7, 6, 2,
	// Right
	0, 4, 1,
	4, 1, 5,
	// Top
	6, 2, 1,
	1, 6, 5,
	// Bottom
	0, 3, 7,
	0, 7, 4 };
btVector3 Vertices[] = {
	{ 1, -1, 0 },
	{ 1, 1, 0 },
	{ -1, 1, 0 },
	{ -1, -1, 0 },
	{ 1, -1, -1 },
	{ 1, 1, -1 },
	{ -1, 1, -1 },
	{ -1, -1, -1 }
};

TEST(GEOM, Geometry_Test){

	auto d = Geometry::basic_Cube<unsigned short, btVector3>();
	ASSERT_EQ(d->num_vertices,sizeof(Vertices)/sizeof(btVector3));
	ASSERT_EQ(d->num_indices, sizeof(indices) / sizeof(unsigned short));
	for (int i = 0; i < d->num_vertices; i++){
		ASSERT_EQ(d->vertices[i].x(),Vertices[i].x());
		ASSERT_EQ(d->vertices[i].y(), Vertices[i].y());
		ASSERT_EQ(d->vertices[i].z(), Vertices[i].z());
	}
	for (int i = 0; i < d->num_indices; i++){
		ASSERT_EQ(d->indices[i], indices[i]);

	}




}