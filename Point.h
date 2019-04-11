#ifndef POINT_H
#define POINT_H


#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


class Point {
public:
  float x, y, z;


  Point();


  Point( Point const &pt);


  Point( float xCord, float yCord, float zCord );


  void display();


  virtual ~Point();


};


#endif