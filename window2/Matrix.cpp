#include "Matrix.h"

Matrix::Matrix(){

	set_to_identity();

}
void Matrix::set_to_identity(){
	mat[0][0] = 1.0f;
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
			retmat[(i * 4)+j] = mat[i][j];
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
	(v.x !=0.0f ? mat[0][0] *= v.x:0);
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