#include "Ray.h"


Ray::Ray() {
  origin = Vec3( 0, 0, 0 );
  t = 1;
  dir = Vec3( 1, 0, 0 );
}


Ray::Ray( const Vec3 &p, float val, const Vec3 &d ) {
  origin = Vec3( p );
  t = val;
  dir = Vec3( d );
}

void Ray::display() {
  printf( "Ray: Origin(%.2f, %.2f, %.2f) + t * dir(%.2f, %.2f, %.2f)\n",
    origin.x, origin.y, origin.z, dir.x, dir.y, dir.z );
}

Ray::~Ray() {}