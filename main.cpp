#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>


#define MAINPROGRAM


#include "World.h"
#include "readfile.h"
#include "Camera.h"
#include <FreeImage.h>


using namespace std;


void setColor( RGBQUAD &color, int r, int g, int b ) {
  color.rgbRed = b;
  color.rgbGreen = g;
  color.rgbBlue = r;
}


void setWhite( RGBQUAD &color ) {
  color.rgbRed = 255;
  color.rgbGreen = 255;
  color.rgbBlue = 255;
}


void setBlack( RGBQUAD &color ) {
  color.rgbRed = 0;
  color.rgbGreen = 0;
  color.rgbBlue = 0;
}


bool computeColor( World &w, light_features lf, Point &p,
                   Ray &r, bool intersected, int currentDepth,
                   float* specularIn, Ray &recursiveRay, Vec3 &color, bool print
) {
  if( intersected ) {
    Vec3 allColors = Vec3( 0, 0, 0 );
    Vec3 rayDirection = r.dir;
    Vec3 recDir = r.dir - lf.normal * ( r.dir * lf.normal ) * 2;
    recDir = recDir.normalize();
    Point pAdjusted = ( Vec3( p ) + recDir * 0.001 ).toPoint();
    recursiveRay = Ray( pAdjusted, 1, recDir );

    for( int i = 0; i < w.lights.size(); i++ ) {
      Vec3 position0 = w.lights.at( i ).getLightDir();
      if( print){printf("position0 ");position0.display();}
      Vec3 direction0;
      float L = 1;
      float V = 1;
      if( w.lights.at( i ).type == 'p' ) {
        direction0 =  position0 - Vec3( p ) ;
        if( print){
          printf("direction0 ");direction0.display();}
        float d = direction0.norm();
        direction0 = direction0.normalize();
        if( print){
          printf(" distance %.2f \n", d);
          printf("direction0 normalized ");direction0.display();}

        L = 1 / ( w.attenuation.constant + w.attenuation.linear * d
                  + w.attenuation.quadratic * d * d );
        if(print) printf("attenuation %.2f, %.2f, %.2f,%.2f  \n", w.attenuation
        .constant,
          w.attenuation.linear, w.attenuation.quadratic, L );
        Ray rayToLight =
          Ray( ( Vec3( p ) + direction0 * 0.001 ).toPoint(), 1, direction0 );
        if(print){
          printf("ray to light "); rayToLight.display();
        }
        Point pCaptured;
        light_features hit;
        float tmax = ( position0 - p ).norm();
        bool  blocked = w.s.getClosestIntersection( rayToLight, w.spheres, w
        .triangles,pCaptured, hit, tmax, false );
        if(print){
//          printf("%d, distance %.2f, tmax %.2f\nlight at ", blocked, lf.d,tmax);
          position0.display();
          printf("p at ");p.display();
          printf("pCaptured at "); pCaptured.display();
          printf("hitting obj index %d of %c list\n", hit.objIndex, hit.objType);
        }

        if( lf.objType == hit.objType && lf.objIndex == hit.objIndex ) {
          //hitting itself
          V = 0;
        }
//        if( tmax - lf.d> 0.001) {
//          V=0;
//        }

        if( print ) {
          printf("Turns out V = %.2f\n ", V);

        }
        direction0 = direction0.normalize();
      }
//      else { //directional light
//        direction0 = position0.normalize();
//        Ray rayToLight = Ray(
//          ( Vec3( p ) + direction0 * 0.001 ).toPoint(), 1, direction0 );
//        Point pCaptured;
//        light_features hit;
//        w.s.getClosestIntersection( r, w.spheres, w.triangles, pCaptured,
//                                    hit, INFINITY );
//        if( lf.objIndex != -1 ) {//hit.d != INFINITY
//          V = 0;
//        }
//      }
      Vec3 half0 = ( direction0 - rayDirection ).normalize();
//      Vec4 lightClolorTMP = vec4( lightcolor[i * 4], lightcolor[i * 4 + 1],
//                                  lightcolor[i * 4 + 2], 1 );
//      Vec4 diffuseTMP = vec4( 1 );
//      Vec4 specularTMP = vec4( 1 );
//      for( int j = 0; j < 4; j++ ) {
//        diffuseTMP[j] = ( obj->diffuse )[j];
//        specularTMP[j] = ( obj->specular )[j];
//      }
//
//      Vec4 col0 = ComputeLight( direction0, lightClolorTMP, intersectTmp->N,
//                                half0, diffuseTMP, specularTMP, obj->shininess,
//                                obj->type == triangle );
//      if(lf.normal * direction0 < 0 ) direction0 = direction0 * (-1);
      Vec3 SD = lf.diffuse * max( lf.normal * direction0, 0.0f ) +
                lf.specular *
                pow( max( lf.normal * half0, 0.0f ), lf.shininess );
      if( print ) {
        printf("computed SD ");SD.display();
//        printf("lf specular ");lf.specular.display();
//        printf("lf diffuse ");lf.diffuse.display();
//        printf("lf shini %.2f\n", lf.shininess);
//        printf("compare %.2f with 0\n", lf.normal * direction0);
//        printf("lf obj index %d of %c list\n", lf.objIndex, lf.objType);
//        printf("lf SD ");SD.display();
        printf("normal ");lf.normal.display();
////        printf("direction0 not unit ");( position0 - Vec3( p ) ).display();
////        printf("direction0 ");direction0.display();
        printf("nDotL %.2f\n", lf.normal * direction0 );
      }
      Vec3 lightIntensity = w.lights.at( i ).getLightColor();
      SD.x = SD.x * lightIntensity.x;
      SD.y = SD.y * lightIntensity.y;
      SD.z = SD.z * lightIntensity.z;
      SD = SD * L * V;
      allColors = allColors + SD;
    }
    Vec3 currentColor = ( lf.ambient + lf.emission + allColors ) * 255;

    if( currentDepth > 1 ) {
      for( int i = 0; i < currentDepth - 1; i++ ) {
        currentColor.x = currentColor.x * specularIn[( i ) * 3];
        currentColor.y = currentColor.y * specularIn[( i ) * 3 + 1];
        currentColor.z = currentColor.z * specularIn[( i ) * 3 + 2];
      }
      color = color + currentColor;

    }
    else {
      color = currentColor;
    }
    if( print ) {

      printf( "compute color get Color" );
      color.display();
      printf( "\n" );
    }

    return true;
  }
  else {
    if( currentDepth > 1 ) {
//none
    }
    else {
//first ray
      color = Vec3( 0, 0, 0 );
    }

    if( print ) {

      printf( "no intersection\n" );
    }
    return false;
  }

}


void rayTracer( Ray &r, float* specularIn, int currentDepth,
                World &w, Vec3 &color, bool print ) {
  light_features lf;

  Point p = Point( 1.0, 1.0, 1.0 );

  bool hasIntersection = w.s.getClosestIntersection( r, w.spheres,
                                                     w.triangles, p, lf,
                                                     INFINITY,print );

  if( hasIntersection ) {
    specularIn[currentDepth * 3] = lf.specular.x;
    specularIn[currentDepth * 3 + 1] = lf.specular.y;
    specularIn[currentDepth * 3 + 2] = lf.specular.z;
  }

  Ray recursiveRay;
  currentDepth++;
  bool inter = computeColor( w, lf, p, r, hasIntersection,
                             currentDepth, specularIn, recursiveRay, color,
                             print );
  if( print ) {
    printf( "Ray tracer get Color" );
    color.display();
    printf( "\n" );
  }


  if( inter && currentDepth < w.maxDepth ) {

//    printf( "entering recursion\n" );

    rayTracer( recursiveRay, specularIn, currentDepth, w, color, print );
  }
//  color.display();
}


int main( int argc, char* argv[] ) {
  if( argc < 2 ) {
    cerr << "Usage: transforms scenefile (optional outputfilename)\n";
    exit( -1 );
  }

  FreeImage_Initialise();

  World w = readfile( argv[1] );

  FIBITMAP* bitmap = FreeImage_Allocate( w.s.w, w.s.h, 24 );
  RGBQUAD color;

  int totalTask = w.s.w * w.s.h;
  int numDone = 0;
  float percent = 0;

  for( float i = 0; i < w.s.w; ++i ) {
    for( float j = 0; j < w.s.h; ++j ) {
      Ray r = w.s.getRay( i, j );


//      w.maxDepth = 5; //todo

      Vec3 pixelColor;
      int currentDepth = 0;
      float allSpecularLights[w.maxDepth * 3];
      Ray recursiveRay;

//      if( j == 45 && i == 2 ) {
//        printf( "@@@@@@Debugging pixel (%.0f,%.0f)\n", i, j );
//        rayTracer( r, allSpecularLights, currentDepth, w, pixelColor, true );
//      }
//      else {
        rayTracer( r, allSpecularLights, currentDepth, w, pixelColor, false );
//      }
//      light_features lf;
//      Point p = Point( 1.0, 1.0, 1.0 );
//      bool hasIntersection = w.s.getClosestIntersection( r, w.spheres,
//                                                         w.triangles, p, lf );
//
//      if( hasIntersection ) {
//        computeColor(w, lf, p, r, true, currentDepth, allSpecularLights,
//                     recursiveRay, pixelColor);
//        setColor( color, pixelColor.x, pixelColor.y, pixelColor.z );
//
//      }
//      else {
//        setBlack( color );
//      }

//      if( j == 45 && i == 2 ) {
//
//        setColor( color, 0,0, 255 );
//      }
//      else {
        setColor( color, pixelColor.x, pixelColor.y, pixelColor.z );

//      }

      FreeImage_SetPixelColor( bitmap, i, j, &color );

      numDone++;
      if( numDone * 100.0 / totalTask - percent > 5 ) {
        percent = 100 * numDone * 1.0 / totalTask;
        printf( "Processing %%%.0f \nComputing pixel %d/%d\n",
                percent, numDone, totalTask );
      }

    }
  }
  printf( "Processing %%100 \nDone.\n",
          percent, numDone, totalTask );

  if( argc == 3 ) {
    FreeImage_Save( FIF_PNG, bitmap, argv[2], 0 );
  }
  else {
    FreeImage_Save( FIF_PNG, bitmap, "compile.png", 0 );
  }
  FreeImage_DeInitialise();

  return 0;
}
