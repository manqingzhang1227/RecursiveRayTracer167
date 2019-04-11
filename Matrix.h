#ifndef HW4_MATRIX_H
#define HW4_MATRIX_H


#include "Vector.h"
//#include "glm-0.9.7.1/glm/"

#include "glm-0.9.7.1/glm/glm.hpp"
#include "glm-0.9.7.1/glm/matrix.hpp"

class Mat3 {
public:
  Vec3 r1, r2, r3;  // Row vectors

  Mat3();


  Mat3( float r11, float r12, float r13,
        float r21, float r22, float r23,
        float r31, float r32, float r33 );


  Mat3( Vec3 &pr1, Vec3 &pr2, Vec3 &pr3 );


  Mat3( const Mat3 &m );


  //identity matrix constructor
  Mat3( float diag );


  //matrix vector multiplication
  Vec3 operator*( Vec3 v );


  // matrix constant multiplication
  Mat3 operator*( float f );


  // 3x3 matrix multiplication
  Mat3 operator*( Mat3 m );


  Mat3 operator+( Mat3 &m );


  void display();

};


class Mat4 {
public:
  Vec4 r1, r2, r3, r4;


  Mat4( float r11, float r12, float r13, float r14,
        float r21, float r22, float r23, float r24,
        float r31, float r32, float r33, float r34,
        float r41, float r42, float r43, float r44 );


  //default 0
  Mat4();


  //identity matrix constructor
  Mat4( float diag );


  //+0001 at the end of mat3
  Mat4( const Mat3 &m3 );


  Mat4( const Mat4 &m );


  Mat4( const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4 );


  Vec4 operator*( Vec4 v );


  // matrix constant multiplication
  Mat4 operator*( float f );


  Mat4 operator*( Mat4 &m );


  Mat4 operator+( Mat4 &m );

  Mat4 inverse();

  Mat4 transpose();

  void display();

};


#endif //HW4_MATRIX_H
