#ifndef INC_GEOMETRY_H
#define INC_GEOMETRY_H
#define FORCE_INLINE __forceinline //warum ich das hier verwende weiﬂ ich net
template<typename indices_type, typename vertices_type>
struct Vertices_indices_data{
	indices_type *indices; vertices_type* vertices;
	unsigned int num_indices, num_vertices;
};
namespace Geometry{
	template <typename indices_type, typename vertices_type>
	extern FORCE_INLINE Vertices_indices_data<indices_type, vertices_type>* basic_Cube();


}
#include "Geometry.cpp"
#endif