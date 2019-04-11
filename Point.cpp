#include "Point.h"


//default ctor to 000
Point::Point() {
  x = 0;
  y = 0;
  z = 0;
}


Point::Point( Point const &pt ) {
  x = pt.x;
  y = pt.y;
  z = pt.z;
}


Point::Point( float xCord, float yCord, float zCord ) {
  x = xCord;
  y = yCord;
  z = zCord;
}


void Point::display() {
  printf( "Point( %.2f, %.2f, %.2f )\n", x, y, z );
}


Point::~Point() {}