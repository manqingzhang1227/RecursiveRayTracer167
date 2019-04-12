
#include "Camera.h"


Camera::Camera() {
  lookFrom = Vec3( 0.0, 0.0, 5.0 ); //camera at z direction
  upDir = Vec3( 0.0, 1.0, 0.0 );  //default up is y axis in the world
  lookAt = Vec3( 0.0, 0.0, 0.0 ); //looking at origin
  fovy = 90;

  w = lookFrom - lookAt;
  w = w.normalize();
  u = upDir.cross( w ).normalize();
  v = w.cross( u );
}


Camera::Camera( float lf1, float lf2, float lf3, float up1, float up2, float up3, 
    float la1, float la2, float la3, float fov ){
  lookFrom = Vec3(lf1, lf2, lf3);
  upDir = Vec3(up1, up2, up3);
  lookAt = Vec3(la1, la2, la3);
  fovy = fov;

  w = lookFrom - lookAt;
  w = w.normalize();
  u = upDir.cross( w ).normalize();
  v = w.cross( u );

//  printf("initializing uvw...\n");
//  lookFrom.display();
//  upDir.display();
//  lookAt.display();
//  u.display();
//  v.display();
//  w.display();

}
