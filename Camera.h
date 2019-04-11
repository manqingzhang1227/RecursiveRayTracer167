#ifndef HW4_CAMERA_H
#define HW4_CAMERA_H


#include "Ray.h"


class Camera {
public:
  Vec3 lookFrom;

  ///the up direction
  Vec3 upDir;


  ///looking at
  Vec3 lookAt;


  ///camera xyz
  Vec3 u, v, w;


  ///position in the world coordinate
  Point pos;


  float fovy;


  Camera();


  Camera( float lf1, float lf2, float lf3, float up1, float up2, float up3,
          float la1, float la2, float la3, float fov );
};


#endif //HW4_CAMERA_H