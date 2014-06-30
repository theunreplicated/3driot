#include "Matrix.h"
//#include <immintrin.h>
//Komplett broken,nicht verwenden
Matrix::Matrix(){

	set_to_identity();

}
void Matrix::set_to_identity(){
	mat[0][0] = 1.0f;//row1
	mat[0][1] = 0.0f;
	mat[0][2] = 0.0f;
	mat[0][3] = 0.0f;

	mat[1][0] = 0.0f;
	mat[1][1] = 1.0f;
	mat[1][2] = 0.0f;
	mat[1][3] = 0.0f;

	mat[2][0] = 0.0f;
	mat[2][1] = 0.0f;
	mat[2][2] = 1.0f;
	mat[2][3] = 0.0f;

	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;



}
float* Matrix::get_as_float16(){
	float*retmat = new float[16];
	for (short i = 0; i < 4; i++){
		for (short j = 0; j < 4; j++){
			//retmat[(i * 4)+j] = mat[i][j];
			
			retmat[(j * 4) + i] = mat[j][i];
		}

	}

	return retmat;
}
void Matrix::translate(/*float x, float y, float z*/Vector3 v){

	 mat[0][3] = v.x; 
	 mat[1][3] = v.y;
	 mat[2][3] = v.z;

}
void Matrix::scale(Vector3 v){
	(v.x != 0.0f ? mat[0][0] *= v.x : 0);//float dc= _mm256_mul_ps();=>nur avx,also meiste pcs wohl gar net
	(v.y != 0.0f ? mat[1][1] *= v.y : 0);
	(v.z != 0.0f ? mat[2][2] *= v.z : 0);


}
Matrix Matrix::multiply_with(Matrix mmul){
	int row, col, k;
	Matrix mul;
	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++) {
			mul.mat[row][col] = 0;
			for (k = 0; k < 4; k++) {
				mul.mat[row][col] += mat[row][k] * mmul.mat[k][col];
			}
		}
	}
	return mul;//http://stackoverflow.com/questions/7637783/program-to-multiply-matrix
}
float degToRad(float degrees) {
	float Math_PI = 3.1415f;
	float degreeToRadiansFactor = Math_PI / 180;

	//return function ( degrees ) {

	return degrees * degreeToRadiansFactor;

};
/*
*@param field_of_fiew Winkel in Grad!!Wird in Radiant umgewandelt
*/
void Matrix::perspective(float field_of_view, float aspectRatio, float near_plane, float far_plane){
	//https://github.com/mrdoob/three.js/blob/master/src/math/Math.js +weiteres Repository von three.js
	float*te = new float[16];//left=-right
	//float*t2= new t1[4];

	//float x = 2 * nearv / ( right - left );
	//float y = 2 * nearv / ( top - bottom );

	//float a = ( right + left ) / ( right - left );
	//float b = ( top + bottom ) / ( top - bottom );
	//float c = - ( farv + nearv ) / ( farv - nearv );
	//float d = - 2 * farv * nearv / ( farv - nearv );
	
		//http://www.songho.ca/opengl/gl_projectionmatrix.html
	//http://www.scratchapixel.com/lessons/3d-advanced-lessons/perspective-and-orthographic-projection-matrix/perspective-projection-matrix/ aber schlecht
	//Quelle:GLM tmat4x4
	//float rad = glm::radians(fov);
	float rad = degToRad(field_of_view);
	float row3_3_v = -1 / (far_plane-near_plane);
	//@note Unterschiede in der Kalkulation von rad


	//detail::tmat4x4<valType, defaultp> Result(valType(0));
	//Result[0][0] = valType(1) / (aspect * tanHalfFovy);
	//Result[1][1] = valType(1) / (tanHalfFovy);

	//float S=1/tan(fov*0.5f*(Math_PI/180.0f));


	float tanHalfFovy = tan(rad / float(2));

	float S2 = float(1) / (tanHalfFovy);
	/*Result[0][0]*/float S1 = float(1) / (aspectRatio * tanHalfFovy);
	//float S1=S2*1/aspectRatio
	/*Result[1][1]*/
	//Result[2][2] = - (zFar + zNear) / (zFar - zNear);
	//Result[2][3] = - float(1);
	//Result[3][2] = - (float(2) * zFar * zNear) / (zFar - zNear);


	//S=1/aspectRatio*tanHalfFovy;
	mat[0][0] = S1;	/*te[4] = 0;*/	/*te[8] = 0/*a*/	//te[12] = 0;//w=(-2*farv*nearv)/(farv-nearv)
	/*te[1] = 0;*/	mat[1][1] = S2;	/*te[9] = 0/*b*/	//te[13] = 0;
	/*te[2] = 0;*/	/*te[6] = 0;*/	mat[2][2] = row3_3_v*(far_plane + near_plane)/*c*/;	mat[3][2] = row3_3_v * (2 * far_plane * near_plane);
	/*te[3] = 0;*/	/*te[7] = 0;*/	mat[2][3] = -1;	//mat[15] = 0; //std::cout << "!!" << te[14] << "!1";


}
array<float,4> Matrix::multiply_with(Vector3 vec){
	//w vom Vektor=1
	//danach implementiert: http://hotmath.com/hotmath_help/topics/multiplying-vector-by-a-matrix.html
	//http://simulationcorner.net/index.php?page=fastmatrixvector
	//zuerst erste Reihe vom Matrix mit Vektor
	array<float, 4> ret;
	array<float, 4>vecn = {vec.x,vec.y,vec.z,1.0f};
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			ret[i] += mat[i][j]*vecn[j];


		}

	}
	return ret;
}
void Matrix::proj_Matrix_resolve(){
	//am Ende:ndc_pos_x=(matrix[row_x]*x)/(matrix[row_w]*obj_w{Anm:obj_w=1})
	//1.Schritt:ndc_pos_x*(matrix[row_w]*obj_w)=(matrix[row_x]*x)
	//(ndc_pos_x*(matrix[row_w]*obj_w))/matrix[row_x]=x;
	//float world_coord_x=(ndc_pos_x*muled_matrix_w)/

}
void Matrix::rotate(const Quaternion& quaternion){

	
	float xx = quaternion.xpos * quaternion.xpos;
	float xy = quaternion.xpos * quaternion.ypos;
	float xz = quaternion.xpos * quaternion.zpos;
	float xw = quaternion.xpos * quaternion.scalar;
	float yy = quaternion.ypos * quaternion.ypos;
	float yz = quaternion.ypos * quaternion.zpos;
	float yw = quaternion.ypos * quaternion.scalar;
	float zz = quaternion.zpos * quaternion.zpos;
	float zw = quaternion.zpos * quaternion.scalar;
	mat[0][0] = 1.0f - 2 * (yy + zz);
	mat[1][0] = 2 * (xy - zw);
	mat[2][0] = 2 * (xz + yw);
	mat[3][0] = 0.0f;
	mat[0][1] = 2 * (xy + zw);
	mat[1][1] = 1.0f - 2 * (xx + zz);
	mat[2][1] = 2 * (yz - xw);
	mat[3][1] = 0.0f;
	mat[0][2] = 2 * (xz - yw);
	mat[1][2] = 2 * (yz + xw);
	mat[2][2] = 1.0f - 2 * (xx + yy);
	mat[3][2] = 0.0f;
	mat[0][3] = 0.0f;
	mat[1][3] = 0.0f;
	mat[2][3] = 0.0f;
	mat[3][3] = 1.0f;
	//m.flagBits = Rotation;
	//*this *= m;
}
