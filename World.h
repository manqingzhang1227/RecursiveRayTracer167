#ifndef HW4_WORLD_H
#define HW4_WORLD_H


#include "Geometry.h"
#include "Ray.h"
#include <vector>
#include <string>


using namespace std;


#include "Vector.h"
#include "Camera.h"


struct light_features {  // Object features concerning light
  Vec3 diffuse;
  Vec3 specular;
  Vec3 normal;
  Vec3 ambient;
  Vec3 emission;
  float shininess;
  float d;
  int objIndex;
  char objType;
};



class Attenuation {
public:
  float constant, linear, quadratic;


  Attenuation();


  Attenuation( float c, float l, float q );


  virtual ~Attenuation();
};


class Ambient {
public:
  float r, g, b;


  Ambient();


  Ambient( float red, float green, float blue );


  virtual ~Ambient();
};


class Light {
public:
  float r, g, b; // Light Colors

  float x, y, z; // Light Positions

  float xt, yt, zt; // Lights transformed by modelview

  char type;


  Light();


  Light( const Light &l );


  Light( float red, float green, float blue, char typeLight,
         float xCord, float yCord, float zCord );


  Light( float red, float green, float blue, char typeLight,
         float xCord, float yCord, float zCord,
         float xTrans, float yTrans, float zTrans );

  Vec3 getLightDir();
  Vec3 getLightColor();

  virtual ~Light();
};


class Scene {
public:
  ///the four corners of the image plane
  Point center;

  Camera ca;

  ///the output image dimensions in pixels width and height
  int w; //horizontalDim;

  int h; //verticalDim;

  // vector <vector <vector <int> > > film;
  // bool intersect( Ray &r,  Sphere s, Point &p  );

  Scene();

  void setScene();

  Ray getRay( float i, float j);

  bool getClosestIntersection(Ray &r, vector <Sphere> sList, 
    vector <Triangle> tList, Point &p, light_features& lf, float tMax, bool
    print);

//   Point intersect( Ray &r,  vector <Sphere> &obj );
  virtual ~Scene();
};



class World {
public:

  ///object list
  vector <Sphere> spheres;
  vector <Triangle> triangles;


  Scene s;


  vector <Light> lights;


  // Lighting parameter array, similar to that in the fragment shader
  int maxVert;


  int maxVertNormal;


  int numLights;       // How many lights are used
  int numVert;


  int numVertNormal;


  int maxDepth;


  string outputFilename; //todo


  Attenuation attenuation;


  Ambient globalAmbient;




  ///constructors
  World();



  virtual ~World();
};


#endif //HW4_WORLD_H
