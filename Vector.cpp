#include "Vector.h"


Vec3::Vec3() {
  x = 0;
  y = 0;
  z = 0;
}


Vec3::Vec3( float px, float py, float pz ) {
  x = px;
  y = py;
  z = pz;
}


Vec3::Vec3( Point from, Point to ) {
  x = to.x - from.x;
  y = to.y - from.y;
  z = to.z - from.z;
}


Vec3::Vec3( const Vec3 &v ) {
  x = v.x;
  y = v.y;
  z = v.z;
}

Vec3::Vec3( const Point &p ) {
  x = p.x;
  y = p.y;
  z = p.z;
}

Vec3 Vec3::operator+( const Vec3 &v ) {
  Vec3 ret( x + v.x, y + v.y, z + v.z );
  return ret;
}


Vec3 Vec3::operator-( const Vec3 &v ) {
  Vec3 ret( x - v.x, y - v.y, z - v.z );
  return ret;
}


Vec3 Vec3::operator*( float f ) {
  Vec3 v( x * f, y * f, z * f );
  return v;
}


Vec3 Vec3::operator/( float f ) {
  Vec3 v( x / f, y / f, z / f );
  return v;
}


float Vec3::operator*( const Vec3 &v ) {
  return x * v.x + y * v.y + z * v.z;
}


Vec3 Vec3::cross( const Vec3 &v ) {
  Vec3 ret( y * v.z - z * v.y, z * v.x - x * v.z,
            x * v.y - y * v.x );
  return ret;
}


float Vec3::norm() {
  return sqrt( x * x + y * y + z * z );
}


const Vec3 Vec3::normalize() {
  float n = 1.0 / norm();
  Vec3 copy( *this );
  copy = copy * n;
  return copy;
}


Point Vec3::toPoint(){
  return Point(x, y, z);
}


void Vec3::display() {
  printf( "( %.2f, %.2f, %.2f )\n", x, y, z );
}


Vec3::~Vec3() {}


Vec4::Vec4() {
  x = 0;
  y = 0;
  z = 0;
  w = 0;
}


Vec4::Vec4( float px, float py, float pz, float pw ) {
  x = px;
  y = py;
  z = pz;
  w = pw;
}


Vec4::Vec4( const Vec4 &v ) {
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
}

Vec4::Vec4( const Point &v, float fourth ) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = fourth;
}
Vec4::Vec4( const Vec3 &v, float fourth ) {
  x = v.x;
  y = v.y;
  z = v.z;
  w = fourth;
}


Vec4 Vec4::operator+( const Vec4 &v ) {
  Vec4 ret( x + v.x, y + v.y, z + v.z, w + v.w );
  return ret;
}

Vec4 Vec4::operator-( const Vec4 &v ) {
  return Vec4( x - v.x, y - v.y, z - v.z, w-v.w );
}


Vec4 Vec4::operator*( float f ) {
  Vec4 v( x * f, y * f, z * f, w * f );
  return v;
}


float Vec4::operator*( const Vec4 &v ) {
  return x * v.x + y * v.y + z * v.z + w * v.w;
}


float Vec4::norm() {
  return sqrt( x * x + y * y + z * z + w * w );
}


Vec4 Vec4::normalize() {
  float n = 1.0 / norm();
  Vec4 copy( *this );
  copy = copy * n;
  return copy;
}


Vec3 Vec4::dehomo() {
  Vec3 v( x, y, z );
  return v;
}


void Vec4::display() {
  printf( "( %.2f, %.2f, %.2f. %.2f )\n", x, y, z, w );
}


Vec4::~Vec4() {}