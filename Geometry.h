#ifndef GEOMETRY_H
#define GEOMETRY_H


#include "Matrix.h"
#include "Ray.h"
#include <math.h>


//class Triangle : public Shape {
class Triangle {
public:

  Point p1, p2, p3;

  float ambient[3];


  float diffuse[3];


  float specular[3];


  float emission[3];


  float shininess;


  Mat4 transform;

  Mat4 inverseTransform;


  Triangle();


  Triangle( const Point &pt1, const Point &pt2, const Point &pt3 );


  Triangle( const Point &pt1, const Point &pt2, const Point &pt3,
            float ambientArr[4], float diffuseArr[4], float specularArr[4],
            float emissionArr[4], float shininessVal, Mat4 &tranfMat );


  void display();

  
  bool getIntersectPoint( Ray &r, Point &intersectPt, Vec3& normal, bool
  print );


  virtual ~Triangle();


};


//class Sphere : public Shape {
class Sphere {
public:

  Point center;


  float radius;


  float ambient[3];


  float diffuse[3];


  float specular[3];


  float emission[3];


  float shininess;


  Mat4 transform;

  Mat4 inverseTransform;


  Sphere();


  Sphere(float x, float y, float z, float rad);


  Sphere(float x, float y, float z, float r,
          float ambientArr[4], float diffuseArr[4], float specularArr[4],
          float emissionVal[4], float shininessVal, Mat4 &tranfMat );

  void display();


  bool getIntersectPoint( Ray &r, Point &intersectPt, Vec3 &normal );


  virtual ~Sphere();


};


#endif
