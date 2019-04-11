#include "World.h"
#include <iostream>


Attenuation::Attenuation() {
  constant = 1;
  linear = 0;
  quadratic = 0;
}


Attenuation::Attenuation( float c, float l, float q ) {
  constant = c;
  linear = l;
  quadratic = q;
}


Ambient::Ambient() {
  r = 0.2;
  g = 0.2;
  b = 0.2;
}


Attenuation::~Attenuation() {}


Ambient::Ambient( float red, float green, float blue ) {
  r = red;
  g = green;
  b = blue;
}


Ambient::~Ambient() {}


Light::Light() {}


Light::Light( const Light &l ) {
  r = l.r;
  g = l.g;
  b = l.b;
  type = l.type;
  x = l.x;
  y = l.y;
  z = l.z;
  xt = l.xt;
  yt = l.yt;
  zt = l.zt;
}


Light::Light( float red, float green, float blue, char typeLight, float xCord,
              float yCord, float zCord ) {
  r = red;
  g = green;
  b = blue;
  type = typeLight;
  x = xCord;
  y = yCord;
  z = zCord;
}


Light::Light( float red, float green, float blue, char typeLight, float xCord,
              float yCord, float zCord, float xTrans, float yTrans,
              float zTrans ) {
  r = red;
  g = green;
  b = blue;
  type = typeLight;
  x = xCord;
  y = yCord;
  z = zCord;
  xt = xTrans;
  yt = yTrans;
  zt = zTrans;
}


Vec3 Light::getLightDir() {
  return Vec3( x, y, z );
}


Vec3 Light::getLightColor() {
  return Vec3( r, g, b );
}


Light::~Light() {}


Scene::Scene() {
  w = 100;
  h = 100;
  center = Point( 0, 0, 0 );
}


Ray Scene::getRay( float i, float j ) {
  i += 0.5;
  j += 0.5; //Ray going through pixel //TODO
  float fovyRad = ca.fovy * 3.1415926 / 180.0;
  float tanFovy = tan( fovyRad / 2.0 );
  float tanFovx = ( float ) w / ( float ) h * tanFovy;

  float alpha = tanFovx * ( float ) ( ( i - w / 2.0 ) / ( w / 2.0 ) );
  float beta = tanFovy * ( float ) ( ( j - h / 2.0 ) / ( h / 2.0 ) );

  Vec3 au = ca.u * alpha;
  Vec3 bv = ca.v * beta;
  Vec3 aubvw = au + bv - ca.w;

  aubvw = aubvw.normalize();

  Ray r( ca.lookFrom.toPoint(), 1, aubvw );

  return r;
}


bool Scene::getClosestIntersection( Ray &r, vector <Sphere> sList,
                                    vector <Triangle> tList, Point &p,
                                    light_features &lf, float tMax, bool print
                                    ) {
  lf.objIndex = -1;
  float closestDistance = tMax;
  bool hasIntersection = false;
  float MINTALLOWED = 0.001;

//  for( int i = 0; i < sList.size(); ++i ) {
//    Sphere cur = sList.at(i);
//    Point interPtS;
//    Vec3 normal;
//    bool intersected = cur.getIntersectPoint( r, interPtS, normal );
//    if( !intersected ) { continue; } //if no intersection, skip this sphere
//    //calculate and compare distance
//    float distance = ( Vec3( interPtS ) - r.origin ).norm();
//    if( distance < closestDistance && distance > MINTALLOWED ) {
//      closestDistance = distance;
//      p.x = interPtS.x;
//      p.y = interPtS.y;
//      p.z = interPtS.z;
//      lf.normal = normal;
//      lf.objType = 's';
//      lf.objIndex = i;
//      lf.ambient = Vec3(cur.ambient[0], cur.ambient[1],cur.ambient[2]);
//      lf.emission = Vec3(cur.emission[0], cur.emission[1],cur.emission[2]);
//      lf.specular = Vec3(cur.specular[0], cur.specular[1],cur.specular[2]);
//      lf.diffuse = Vec3(cur.diffuse[0], cur.diffuse[1],cur.diffuse[2]);
//      lf.shininess = cur.shininess;
//      lf.d = distance;
//      hasIntersection = true;
//    }
//  }
//
//  for( int i = 0; i < tList.size(); ++i ) {
//    Triangle cur = tList.at(i);
//    Point interPtS;
//    Vec3 normal;
//    bool intersected = cur.getIntersectPoint( r, interPtS, normal );
//    if( !intersected ) { continue; } //if no intersection, skip this sphere
//    //calculate and compare distance
//    float distance = ( Vec3( interPtS ) - r.origin ).norm();
//    if( distance < closestDistance && distance > MINTALLOWED ) {
//      closestDistance = distance;
//      p.x = interPtS.x;
//      p.y = interPtS.y;
//      p.z = interPtS.z;
//      lf.normal = normal;
//      lf.objType = 't';
//      lf.objIndex = i;
//      lf.ambient = Vec3(cur.ambient[0], cur.ambient[1],cur.ambient[2]);
//      lf.emission = Vec3(cur.emission[0], cur.emission[1],cur.emission[2]);
//      lf.specular = Vec3(cur.specular[0], cur.specular[1],cur.specular[2]);
//      lf.diffuse = Vec3(cur.diffuse[0], cur.diffuse[1],cur.diffuse[2]);
//      lf.shininess = cur.shininess;
//      lf.d = distance;
//      hasIntersection = true;
//      if( lf.normal * r.dir > 0 ) lf.normal = lf.normal * -1;
//    }
//  }

  char closesType = 'n';
  lf.objType=closesType;

  vector <Sphere>::iterator itS;
  vector <Sphere>::iterator closestS = sList.end();
  int indexS = 0;
  Point interPtS;
  for( itS = sList.begin(); itS != sList.end(); itS++ ) {
    Sphere cur = *itS;

    Vec3 normal;
    bool intersected = cur.getIntersectPoint( r, interPtS, normal );
    indexS++;

    if( !intersected ) { continue; } //if no intersection, skip this sphere


    //calculate and compare distance
    float distance = ( Vec3( interPtS ) - r.origin ).norm();
    if( distance < closestDistance && distance > MINTALLOWED ) {
      closestDistance = distance;
      p.x = interPtS.x;
      p.y = interPtS.y;
      p.z = interPtS.z;
      if(print) {
        p.display();
      }
      closestS = itS;
      closesType = 's';
      lf.normal = normal;
      lf.d = closestDistance;
      hasIntersection = true;

    }
  }

  vector <Triangle>::iterator itT;
  vector <Triangle>::iterator closestT = tList.end();
  int indexT = 0;
  Point interPtT;

  for( itT = tList.begin(); itT != tList.end(); itT++ ) {
    Triangle cur = *itT;
    Vec3 normal;

    bool intersected = cur.getIntersectPoint( r, interPtT, normal, print );
    indexT++;

    if( !intersected ) { continue; } //if no intersection, skip this sphere


    //calculate and compare distance
    float distance = ( Vec3( interPtT ) - r.origin ).norm();
    if( distance < closestDistance && distance > MINTALLOWED ) {
      closestDistance = distance;
      p.x = interPtT.x;
      p.y = interPtT.y;
      p.z = interPtT.z;
      if(print) {
        p.display();
      }
      closestT = itT;
      closesType = 't';
      lf.d = closestDistance;
      lf.normal = normal;
//      printf("setting normal");lf.normal.display();

      hasIntersection = true;

    }
  }

  if( closesType = 't' && closestT != tList.end() ) {
    lf.objIndex = indexS;
    lf.objType = 't';

    lf.ambient = Vec3( closestT->ambient[0],
                       closestT->ambient[1], closestT->ambient[2] );
    lf.emission = Vec3( closestT->emission[0],
                        closestT->emission[1], closestT->emission[2] );
    lf.diffuse = Vec3( closestT->diffuse[0],
                       closestT->diffuse[1], closestT->diffuse[2] );
    lf.specular = Vec3( closestT->specular[0],
                        closestT->specular[1], closestT->specular[2] );
    lf.shininess = closestT->shininess;

    if( lf.normal * r.dir > 0 ) {
//      lf.normal = lf.normal * -1;
    }
  }
  else if( closesType = 's' && closestS != sList.end() ) {
    lf.objIndex = indexT;
    lf.objType = 's';
    lf.ambient = Vec3( closestS->ambient[0],
                       closestS->ambient[1], closestS->ambient[2] );
    lf.emission = Vec3( closestS->emission[0],
                        closestS->emission[1], closestS->emission[2] );
    lf.diffuse = Vec3( closestS->diffuse[0],
                       closestS->diffuse[1], closestS->diffuse[2] );
    lf.specular = Vec3( closestS->specular[0],
                        closestS->specular[1], closestS->specular[2] );
    lf.shininess = closestS->shininess;
    // lf.normal = Vec3(closestS->center, p).normalize();

  }

  if(print) {
    r.display();
//    printf("normal from world");lf.normal.display();
  }
  return hasIntersection;
}


Scene::~Scene() {}


///-------------- World class


World::World() {
  numLights = 0;
//  maxVert = 0;
  maxDepth = 5;
}


World::~World() {}

