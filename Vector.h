

#ifndef HW4_VECTOR_H
#define HW4_VECTOR_H


#include "Point.h"


class Vec3 {
public:
  float x, y, z;


  Vec3();


  Vec3( float px, float py, float pz );


  Vec3( Point from, Point to );


  Vec3( const Vec3 &v );


  Vec3( const Point &p );


  Vec3 operator+( const Vec3 &v );


  Vec3 operator-( const Vec3 &v );


  Vec3 operator*( float f );


  Vec3 operator/( float f );


  float operator*( const Vec3 &v );


  Vec3 cross( const Vec3 &v );


  float norm();


  const Vec3 normalize();


  void display();


  Point toPoint();


  virtual ~Vec3();

};


class Vec4 {

public:
  float x, y, z, w;


  Vec4();


  Vec4( float px, float py, float pz, float pw );


  Vec4( const Vec4 &v );
  Vec4( const Point &v, float fourth );


  Vec4( const Vec3 &v, float fourth );


  virtual ~Vec4();


  Vec4 operator+( const Vec4 &v );

  Vec4 operator-( const Vec4 &v );

  Vec4 operator*( float f );


  float operator*( const Vec4 &v );


  float norm();


  Vec4 normalize();


  Vec3 dehomo();


  void display();

};


#endif //HW4_VECTOR_H
