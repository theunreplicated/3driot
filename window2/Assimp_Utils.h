#ifndef INC_ASSIMP_UTILS_H
#define INC_ASSIMP_UTILS_H
#include <array>
#include <assimp\scene.h>
namespace Assimp_Utils{
	extern std::array<std::array<float, 4>, 4> convert_aiMatrix_to_float4x4(aiMatrix4x4& data);
	/*{
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
	}*/

	//extern float *convert_aiMatrix_to_float16(aiMatrix4x4& data);
	/*{
		float*d= new float[16];
		d[0] = data.a1;
		d[1] = data.a2;
		d[2] = data.a3;
		d[3] = data.a4;

		d[4] = data.b1;
		d[5] = data.b2;
		d[6] = data.b3;
		d[7] = data.b4;

		d[8] = data.c1;
		d[9] = data.c2;
		d[10] = data.c3;
		d[11] = data.c4;

		d[12] = data.d1;
		d[13] = data.d2;
		d[14] = data.d3;
		d[15] = data.d4;

		return d;
	}

	*/
}

#endif