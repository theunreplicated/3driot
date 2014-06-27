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
//@TODO:Matrix mit SIMD-Instructions https://software.intel.com/sites/landingpage/IntrinsicsGuide/
class Vector3{
public:
	float x,y,z;
	explicit Vector3(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f){ x = ix; y = iy; z = iz; }//explicit greift hier net
	void normalize(){
		float len = x * x +
			y*y+
			z*z;
		if((len - 1.0f) == 0.0f){
				throw std::runtime_error("Vector-normlizing-length=0");
			}
		len = sqrt(len);

		x = float(x / len);
		y = float(y / len);
		z = float(z / len);
		//normalize();
	}
	
};
//https://qt.gitorious.org/qt/qtbase/source/bab494e4d046f5617d19f5fec35eeff94377c51f:src/gui/math3d/qquaternion.h#L60
//https://qt.gitorious.org/qt/qtbase/source/bab494e4d046f5617d19f5fec35eeff94377c51f:src/gui/math3d/qmatrix4x4.cpp
//ist zwar eigentlich GPL,aber egal
struct Quaternion{
	float scalar;
	float xpos; float ypos; float zpos;//TODO:Vereinheitlichung mit Vector
	Quaternion(float x, float y, float z, float angle)
	{
		float Math_PI = 3.1415f;
		float length = sqrt(x * x + y * y + z * z);
		if ((length - 1.0f)!=0.0f && length!=0.0f) {
			x /= length;
			y /= length;
			z /= length;
		}
		float a = (angle / 2.0f) * Math_PI / 180.0f;
		float s = sinf(a);
		float c = cosf(a);
		//return QQuaternion(c, x * s, y * s, z * s).normalized();
		scalar = c;
		xpos = x*s;
		ypos = y*s;
		zpos = z*s;
		normalize();//@TODO:rotation klappt so net//vlt.. net auf qt impl schauen w. flagbits
	};
	void normalize/*Qt's normalized*/(){
		float len = float(xpos) * float(xpos) +
			float(ypos) * float(ypos) +
			float(zpos) * float(zpos) +
			float(scalar) * float(scalar);
		
		if (len != 0.0f){
			float sqrtlen = sqrt(len);
			xpos /= sqrtlen;
			ypos /= sqrtlen;
			zpos /= sqrtlen;
			scalar /= sqrtlen;


		}//@TODO:unten das noch machen
			//return this /Sqrt(len);
		//else
			//return QQuaternion(0.0f, 0.0f, 0.0f, 0.0f);

	};

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
	void perspective(float field_of_view, float aspectRatio, float near_plane, float far_plane);
	void rotate(const Quaternion& quaternion);//https://qt.gitorious.org/qt/qtbase/source/bab494e4d046f5617d19f5fec35eeff94377c51f:src/gui/math3d/qmatrix4x4.cpp#L1309
};



#endif