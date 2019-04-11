#include "Geometry.h"

//Shape::Shape() {}
//Point Shape::intersect( Ray &r ) {}

Triangle::Triangle() {
  p1 = Point( 0, 0, 0 );
  p2 = Point( 5, 5, 5 );
  p3 = Point( 0, 6, 0 );

  ambient[0] = 0;
  ambient[1] = 0;
  ambient[2] = 0;

  diffuse[0] = 0;
  diffuse[1] = 0;
  diffuse[2] = 0;

  specular[0] = 0;
  specular[1] = 0;
  specular[2] = 0;

  emission[0] = 0;
  emission[1] = 0;
  emission[2] = 0;

  shininess = 0;

  transform = Mat4( 1 );

  inverseTransform = transform.inverse();

}


Triangle::Triangle( const Point &pt1, const Point &pt2, const Point &pt3 ) {
  p1 = Point( pt1 );
  p2 = Point( pt2 );
  p3 = Point( pt3 );

  ambient[0] = 0;
  ambient[1] = 0;
  ambient[2] = 0;

  diffuse[0] = 0;
  diffuse[1] = 0;
  diffuse[2] = 0;

  specular[0] = 0;
  specular[1] = 0;
  specular[2] = 0;

  emission[0] = 0;
  emission[1] = 0;
  emission[2] = 0;

  shininess = 0;

  transform = Mat4( 1 );

  inverseTransform = transform.inverse();

}


Triangle::Triangle( const Point &pt1, const Point &pt2, const Point &pt3,
                    float ambientArr[4], float diffuseArr[4],
                    float specularArr[4],
                    float emissionArr[4], float shininessVal, Mat4 &tranfMat ) {
  p1 = Point( pt1 );
  p2 = Point( pt2 );
  p3 = Point( pt3 );

  ambient[0] = ambientArr[0];
  ambient[1] = ambientArr[1];
  ambient[2] = ambientArr[2];

  diffuse[0] = diffuseArr[0];
  diffuse[1] = diffuseArr[1];
  diffuse[2] = diffuseArr[2];

  specular[0] = specularArr[0];
  specular[1] = specularArr[1];
  specular[2] = specularArr[2];

  emission[0] = emissionArr[0];
  emission[1] = emissionArr[1];
  emission[2] = emissionArr[2];

  shininess = shininessVal;

  transform = Mat4( tranfMat );

  inverseTransform = transform.inverse();

}


bool sameSide( const Point &p1, const Point &p2,
               const Point &A, const Point &B ) {
  Vec3 AB = Vec3( A, B );
  return AB.cross( Vec3( p1, A ) ) * AB.cross( Vec3( p2, A ) ) >= 0;
}


bool checkInTriangle( const Point &P, const Point &A,
                      const Point &B, const Point &C ) {
  return sameSide( P, A, B, C ) && sameSide( P, B, A, C ) &&
         sameSide( P, C, A, B );
}


bool Triangle::getIntersectPoint( Ray &r, Point &intersectPt, Vec3& normal,
  bool print) {

  Vec3 aTrans = ( transform * Vec4( Vec3( p3 ), 1 ) ).dehomo();
  Vec3 bTrans = ( transform * Vec4( Vec3( p2 ), 1 ) ).dehomo();
  Vec3 cTrans = ( transform * Vec4( Vec3( p1 ), 1 ) ).dehomo();
  Vec3 AC = cTrans - aTrans; //C-A ac
  Vec3 AB = bTrans - aTrans;; // B-A ac

  Vec3 planeNormal = ( cTrans - aTrans )
    .cross( ( bTrans - aTrans ) ).normalize();


  if( r.dir * planeNormal == 0 ) {  //ray parallel to plane, no intersection
    return false;
  }

  float t = ( aTrans * planeNormal - r.origin * planeNormal )

            / ( r.dir * planeNormal );

  if( t < 0 ) { //in the negative side of the origin, no intersection
    return false;
  }

  Vec3 intersectAt = r.origin + r.dir * t;
  Point p = intersectAt.toPoint();

  if( !checkInTriangle( p, cTrans.toPoint(),
                        bTrans.toPoint(), aTrans.toPoint() ) ) {
    return false;
  }

  intersectPt.x = intersectAt.x;
  intersectPt.y = intersectAt.y;
  intersectPt.z = intersectAt.z;

  normal = planeNormal;
  if( print) {
//    printf("planeNormal ");planeNormal.display();
  }

  return true;
}


void Triangle::display() {

  printf( "Triangle:( Vertex1: Point( %.2f, %.2f, %.2f ), "
          "Vertex2: Point( %.2f, %.2f, %.2f ),"
          " Vertex3: Point( %.2f, %.2f, %.2f ) )",
          p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z );
}


Triangle::~Triangle() {}


Sphere::Sphere() {
  center = Point( 10, 0, 0 );
  radius = 3;

  ambient[0] = 0;
  ambient[1] = 0;
  ambient[2] = 0;

  diffuse[0] = 0;
  diffuse[1] = 0;
  diffuse[2] = 0;

  specular[0] = 0;
  specular[1] = 0;
  specular[2] = 0;

  emission[0] = 0;
  emission[1] = 0;
  emission[2] = 0;

  shininess = 0;

  transform = Mat4( 1 );

  inverseTransform = transform.inverse();

}


Sphere::Sphere( float x, float y, float z, float rad ) {
  center = Point( x, y, z );
  radius = rad;

  ambient[0] = 0;
  ambient[1] = 0;
  ambient[2] = 0;

  diffuse[0] = 0;
  diffuse[1] = 0;
  diffuse[2] = 0;

  specular[0] = 0;
  specular[1] = 0;
  specular[2] = 0;

  emission[0] = 0;
  emission[1] = 0;
  emission[2] = 0;

  shininess = 0;

  transform = Mat4( 1 );


  inverseTransform = transform.inverse();

}


Sphere::Sphere( float x, float y, float z, float r,
                float ambientArr[4], float diffuseArr[4], float specularArr[4],
                float emissionArr[4], float shininessVal, Mat4 &tranfMat ) {
  center = Point( x, y, z );
  radius = r;

  ambient[0] = ambientArr[0];
  ambient[1] = ambientArr[1];
  ambient[2] = ambientArr[2];

  diffuse[0] = diffuseArr[0];
  diffuse[1] = diffuseArr[1];
  diffuse[2] = diffuseArr[2];

  specular[0] = specularArr[0];
  specular[1] = specularArr[1];
  specular[2] = specularArr[2];

  emission[0] = emissionArr[0];
  emission[1] = emissionArr[1];
  emission[2] = emissionArr[2];

  shininess = shininessVal;

  transform = Mat4( tranfMat );

  inverseTransform = transform.inverse();

}


void Sphere::display() {

  printf( "Sphere:( Center: Point( %.2f, %.2f, %.2f ), Radius: %.2f )",
          center.x, center.y, center.z, radius );
}


bool Sphere::getIntersectPoint( Ray &r, Point &intersectPt, Vec3 &normal ) {
  Vec4 rayOrigin = inverseTransform * Vec4( r.origin, 1 );
  Vec4 rayDir = inverseTransform * Vec4( r.dir, 0 );

  //unit sphere at origin
  Vec4 ctr = Vec4( center, 1 );//Vec4( 0,0,0,0 );
  float rad = radius;// 1;

  //consider a*t^2+bt+c;
  float a = rayDir * rayDir;

  float b = rayDir * ( rayOrigin - ctr ) * 2;
  float c = ( rayOrigin - ctr ) * ( rayOrigin - ctr ) - rad * rad;


  float delta = b * b - 4 * a * c;

  float root = 0;

  if( delta < 0 ) {
    return false;
  }

  float root1 = ( -b + sqrt( delta ) ) / ( 2.0 * a );
  float root2 = ( -b - sqrt( delta ) ) / ( 2.0 * a );


  if( root1 < 0 && root2 < 0 ) {
    return false;
  }
  else if( root1 < 0 && root2 > 0 ) {
    root = root2;
  }
  else if( root1 > 0 && root2 < 0 ) {
    root = root1;
  }
  else { //root1 root2 both positive
    if( root1 <= root2 ) {
      root = root1;
    }
    else {
      root = root2;
    }
  }

  Vec4 result = rayOrigin + rayDir * root;
  Vec3 resultTrans = ( transform * result ).dehomo(); //tranform back
  intersectPt.x = resultTrans.x;
  intersectPt.y = resultTrans.y;
  intersectPt.z = resultTrans.z;


  normal = ( inverseTransform.transpose() * result ).dehomo().normalize();
// normal = (transform * (result - Vec4(0, 0, 0, 1))).dehomo().normalize();
  return true;
}


Sphere::~Sphere() {}