// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
//#include "Matrix.hpp"
#include <stdlib.h>
#include <stdio.h>


// Helper rotation function.  Please implement this.
Mat3 Transform::rotate( const float degrees, const Vec3 &axis ) {
  Mat3 ret( 0 );
  Vec3 axisNorm( axis.x, axis.y, axis.z );
  axisNorm = axisNorm.normalize();

  double x = axisNorm.x;
  double y = axisNorm.y;
  double z = axisNorm.z;

  //components in the Axis-Angle formula
  Mat3 comp1( 1.0 );
  comp1 = comp1 * cos( degrees * pi / 180.0 );


  Mat3 comp2( x * x, x * y, x * z,
              x * y, y * y, y * z,
              x * z, y * z, z * z );
  comp2 = comp2 * ( 1 - cos( degrees * pi / 180.0 ) );


  Mat3 comp3( 0, -z, y,
              z, 0, -x,
              -y, x, 0 );
  comp3 = comp3 * sin( degrees * pi / 180.0 );

  ret = comp1 + comp2 + comp3;
  return ret;
}


//void Transform::left( float degrees, Vec3 &eye, Vec3 &up ) {
//  //set up a rotation matrix
//  Mat3 rotationMatrix( rotate( degrees, up ) );
//  eye = rotationMatrix * eye;
//}


//void Transform::up( float degrees, Vec3 &eye, Vec3 &up ) {
//  Mat3 rotationMatrix = rotate( degrees, eye.cross( up ) );
//  eye = rotationMatrix * eye;
//  up = rotationMatrix * up;
//}


//Mat4 Transform::lookAt( const Vec3 &eye, const Vec3 &center, const Vec3 &up ) {
//  Vec3 w( eye.x, eye.y, eye.z );
//  w = w.normalize();
//  Vec3 u( up.x, up.y, up.z );
//  u = u.cross( w ).normalize();
//  Vec3 v( w.x, w.y, w.z );
//  v = v.cross( u );
//
//  Mat4 transformationMatrix
//    ( u.x, u.y, u.z, -u.x * eye.x - u.y * eye.y - u.z * eye.z,
//      v.x, v.y, v.z, -v.x * eye.x - v.y * eye.y - v.z * eye.z,
//      w.x, w.y, w.z, -w.x * eye.x - w.y * eye.y - w.z * eye.z,
//      0.0, 0.0, 0.0, 1.0 );
//
//  return transformationMatrix;
//}


Mat4 Transform::perspective( float fovy, float aspect, float zNear, float zFar ) {
  //implement the perspective transform as well.
  float theta = ( fovy / 2.0 ) * pi / 180.0;
  float d = cos( theta ) / sin( theta );
  float A = -( zFar + zNear ) / ( zFar - zNear );
  float B = -2 * zFar * zNear / ( zFar - zNear );

  Mat4 perspectiveMatrix( d / aspect, 0.0, 0.0, 0.0,
                          0.0, d, 0.0, 0.0,
                          0.0, 0.0, A, B,
                          0.0, 0.0, -1, 0.0 );
  return perspectiveMatrix;
}


Mat4 Transform::scale( const float &sx, const float &sy, const float &sz ) {
  // Implement scaling
  Mat4 scaleMatrix( sx, 0.0, 0.0, 0.0,
                    0.0, sy, 0.0, 0.0,
                    0.0, 0.0, sz, 0.0,
                    0.0, 0.0, 0.0, 1.0 );
  return scaleMatrix;
}


Mat4 Transform::translate( const float &tx, const float &ty, const float &tz ) {
  // Implement translation
  Mat4 translationMatrix( 1.0, 0.0, 0.0, tx,
                          0.0, 1.0, 0.0, ty,
                          0.0, 0.0, 1.0, tz,
                          0.0, 0.0, 0.0, 1.0 );
  return translationMatrix;
}

//// To normalize the up direction and construct a coordinate frame.
//// As discussed in the lecture.  May be relevant to create a properly
//// orthogonal and normalized up.
//// This function is provided as a helper, in case you want to use it.
//// Using this function (in readfile.cpp or display.cpp) is optional.
//
//Vec3 Transform::upvector( const Vec3 &up, const Vec3 &zvec ) {
//  Vec3 x( up.x, up.y, up.z );
//  x = x.cross( zvec );
//  Vec3 y( zvec.x, zvec.y, zvec.z );
//  y = y.cross( x ).normalize();
//  Vec3 ret( y );
//  return ret;
//}


Transform::Transform() {

}


Transform::~Transform() {

}
