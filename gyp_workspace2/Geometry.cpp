#ifndef INC_GEOMETRY_CPP
#define INC_GEOMETRY_CPP
#include "Geometry.h"
#include <stdio.h>
template <typename indices_type,typename vertices_type>
FORCE_INLINE Vertices_indices_data<indices_type, vertices_type> * Geometry::basic_Cube(){
	Vertices_indices_data<indices_type, vertices_type>*d = new Vertices_indices_data < indices_type, vertices_type > ;
	//Quelle: Vertices&Indices http://www.raywenderlich.com/3664/opengl-tutorial-for-ios-opengl-es-2-0

	indices_type indices[] = {
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

	vertices_type Vertices[] = {
		 { 1, -1, 0 },
		{ 1, 1, 0 },
		{ -1, 1, 0 },
		{ -1, -1, 0 },
		{ 1, -1, -1 },
		 { 1, 1, -1 },
		 { -1, 1, -1 },
		 { -1, -1, -1 }
	};


	d->num_indices/*unnötig auf heap->langsamere Zugriffszeit*/ = sizeof(indices) / sizeof(indices_type);
	d->indices = new indices_type[d->num_indices];
	memcpy(d->indices,indices,sizeof(indices));

	d->num_vertices = sizeof(Vertices) / sizeof(vertices_type);
	d->vertices = new vertices_type[d->num_vertices];
	memcpy(d->vertices,Vertices,sizeof(Vertices));

	//d->indices = indices;
	return d;
}
#endif