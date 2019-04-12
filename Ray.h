#ifndef HW4_RAY_H
#define HW4_RAY_H


#include "Vector.h"


class Ray {

public:

  ///Ray = origin + t * dir

  Vec3 origin;


  float t;


  Vec3 dir;


  Ray();


  Ray( const Vec3 &p, float val, const Vec3 &d );

  void display();


  virtual ~Ray();

};


#endif //HW4_RAY_H
