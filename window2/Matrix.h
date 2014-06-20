//Matrix-Der Film, kommt hier
#ifndef INC_MATRIX_H
#define INC_MATRIX_H
#include <array>
using std::array;
//4x4-Matrix ist das hier,habs nur Matrix genannt,da ich wohl keine anderen als 4*4-Matrizen verwende werde(vltt. nachher doch 3*3 wegen Speicherverbrauch,aber vor allem nicht hier)
/*
class Matrix;
typedef struct mat_translateVector3{
Matrix *m_p;
//array<array<float,4>,4>
mat_translateVector3(Matrix *m_ps){ m_p = m_ps; }
//float vx, vy, vz;
void x(float x_v){ m_p->mat[0][3] = x_v; }
void y(float y_v){ m_p->mat[1][3] = y_v; }
void z(float z_v){ m_p->mat[2][3] = z_v; }
//geht nicht ,wer hat sich nur diesen Scheiss da ausgedacht,so ein Mist,der gehört für ewig gefoltert
ich würde gern n eigenes C++ schreiben ohnde diese vielen Mackenund ohne diesen unsinnigen Schwachsinn dens zuhauf geibt
};
*/
//TODO:vererbung(oder auch nicht),dann mit vector1,vector2,...
class Vector3{
public:
	float x,y,z;
	explicit Vector3(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f){ x = ix; y = iy; z = iz; }//explicit greift hier net

};
class Matrix{
public:
	float mat[4][4];
	Matrix();
	void set_to_identity();
	float * get_as_float16();
	void translate(/*float x = 0.0f, float y = 0.0f, float z = 0.0f*/Vector3 v);
	void scale(Vector3 v);
	Matrix multiply_with(Matrix mmul);
	void operator*(Matrix mmul){ *this = multiply_with(mmul); };
};



#endif