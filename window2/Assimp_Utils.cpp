#include "Assimp_Utils.h"
namespace Assimp_Utils{
	std::array<std::array<float, 4>, 4> convert_aiMatrix_to_float4x4(aiMatrix4x4& data){
		std::array<std::array<float, 4>, 4>d;
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

		return d;
	}

	


}
