#ifndef HW4_TRANSFORM_H
#define HW4_TRANSFORM_H

#include "Matrix.h"
#include <math.h>
// glm provides vector, matrix classes like glsl
// Typedefs to make code more readable 

const float pi = 3.14159265; // For portability across platforms


class Transform {
public:
  Transform();


  virtual ~Transform();


//  static void left( float degrees, Vec3 &eye, Vec3 &up );
//
//
//  static void up( float degrees, Vec3 &eye, Vec3 &up );


//  static Mat4 lookAt( const Vec3 &eye, const Vec3 &center, const Vec3 &up );


  static Mat4 perspective( float fovy, float aspect, float zNear, float zFar );


  static Mat3 rotate( const float degrees, const Vec3 &axis );


  static Mat4 scale( const float &sx, const float &sy, const float &sz );


  static Mat4 translate( const float &tx, const float &ty, const float
  &tz );


//  static Vec3 upvector( const Vec3 &up, const Vec3 &zvec );
};


#endif