#include "Matrix.h"


Mat3::Mat3() {
  Vec3 r1( 0, 0, 0 );
  Vec3 r2( 0, 0, 0 );
  Vec3 r3( 0, 0, 0 );
}


Mat3::Mat3( float r11, float r12, float r13, float r21, float r22, float r23,
            float r31, float r32, float r33 ) {

  r1 = Vec3 ( r11, r12, r13 );
  r2 =Vec3( r21, r22, r23 );
   r3=Vec3( r31, r32, r33 );
}


Mat3::Mat3( Vec3 &pr1, Vec3 &pr2, Vec3 &pr3 ) {
  r1.x = pr1.x;
  r1.y = pr1.y;
  r1.z = pr1.z;
  r2.x = pr2.x;
  r2.y = pr2.y;
  r2.z = pr2.z;
  r3.x = pr3.x;
  r3.y = pr3.y;
  r3.z = pr3.z;
}


Mat3::Mat3( float diag ) {
  r1 = Vec3( 1, 0, 0);
  r2 = Vec3( 0, 1, 0);
  r3 = Vec3(0, 0, 1);}


Mat3::Mat3( const Mat3 &m ) {
  r1 = Vec3(m.r1);
  r2 = Vec3(m.r2);
  r3 = Vec3(m.r3);;
}


Vec3 Mat3::operator*( Vec3 v ) {
  Vec3 ret( r1 * v, r2 * v, r3 * v );
  return ret;
}


Mat3 Mat3::operator*( float f ) {
  Vec3 v1( r1.x * f, r1.y * f, r1.z * f );
  Vec3 v2( r2.x * f, r2.y * f, r2.z * f );
  Vec3 v3( r3.x * f, r3.y * f, r3.z * f );
  return Mat3( v1, v2, v3 );
}


Mat3 Mat3::operator*( Mat3 m ) {
  Vec3 c1( m.r1.x, m.r2.x, m.r3.x ); // Column 1 of matrix m
  Vec3 c2( m.r1.y, m.r2.y, m.r3.y );
  Vec3 c3( m.r1.z, m.r2.z, m.r3.z );
  Vec3 v1( r1 * c1, r1 * c2, r1 * c3 );
  Vec3 v2( r2 * c1, r2 * c2, r2 * c3 );
  Vec3 v3( r3 * c1, r3 * c2, r3 * c3 );
  return Mat3( v1, v2, v3 );
}


Mat3 Mat3::operator+( Mat3 &m ) {
  Vec3 v1( r1.x + m.r1.x, r1.y + m.r1.y, r1.z + m.r1.z );
  Vec3 v2( r2.x + m.r2.x, r2.y + m.r2.y, r2.z + m.r2.z );
  Vec3 v3( r3.x + m.r3.x, r3.y + m.r3.y, r3.z + m.r3.z );
  return Mat3( v1, v2, v3 );
}


void Mat3::display() {
  printf( "[ %.2f, %.2f, %.2f;\n", r1.x, r1.y, r1.z );
  printf( "  %.2f, %.2f, %.2f;\n", r2.x, r2.y, r2.z );
  printf( "  %.2f, %.2f, %.2f ]\n", r3.x, r3.y, r3.z );
}


Mat4::Mat4( float r11, float r12, float r13, float r14, float r21, float r22,
            float r23, float r24, float r31, float r32, float r33, float r34,
            float r41, float r42, float r43, float r44 ) {
  r1.x = r11;
  r1.y = r12;
  r1.z = r13;
  r1.w = r14;
  r2.x = r21;
  r2.y = r22;
  r2.z = r23;
  r2.w = r24;
  r3.x = r31;
  r3.y = r32;
  r3.z = r33;
  r3.w = r34;
  r4.x = r41;
  r4.y = r42;
  r4.z = r43;
  r4.w = r44;
}


Mat4::Mat4() {
  r1 =Vec4(0, 0, 0, 0);
  r2 =Vec4(0, 0, 0, 0);
  r3 =Vec4(0, 0, 0, 0);
  r4 =Vec4(0, 0, 0, 0);
}


Mat4::Mat4( float diag ) {
  r1 = Vec4( 1, 0, 0, 0);
  r2 = Vec4( 0, 1, 0, 0);
  r3 = Vec4(0, 0, 1, 0);
  r4 = Vec4 (0, 0, 0, 1 );
}


Mat4::Mat4( const Mat3 &m3 ) {
  r1=Vec4( m3.r1,0);
  r2=Vec4( m3.r2,0);
  r3=Vec4( m3.r3,0);
 r4 = Vec4(0, 0, 0, 1 );
}


Mat4::Mat4( const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4 ) {
  r1=v1;
  r2=v2;
  r3=v3;
  r4=v4;
}


Mat4::Mat4( const Mat4 &m ) {
  r1 = Vec4(m.r1);
  r2 = Vec4(m.r2);
  r3 = Vec4(m.r3);
  r4 = Vec4(m.r4);
}


Vec4 Mat4::operator*( Vec4 v ) {
  float vr1 = r1 * v;
  float vr2 = r2 * v;
  float vr3 = r3 * v;
  float vr4 = r4 * v;
  Vec4 ret( vr1, vr2, vr3, vr4 );
  return ret;
}


Mat4 Mat4::operator*( float f ) {
  Vec4 v1( r1.x * f, r1.y * f, r1.z * f, r1.w * f );
  Vec4 v2( r2.x * f, r2.y * f, r2.z * f, r2.w * f );
  Vec4 v3( r3.x * f, r3.y * f, r3.z * f, r3.w * f );
  Vec4 v4( r4.x * f, r4.y * f, r4.z * f, r4.w * f );
  Mat4 ret( v1, v2, v3, v4 );
  return ret;
}


Mat4 Mat4::operator*( Mat4 &m ) {
  Vec4 c1( m.r1.x, m.r2.x, m.r3.x, m.r4.x );
  Vec4 c2( m.r1.y, m.r2.y, m.r3.y, m.r4.y );
  Vec4 c3( m.r1.z, m.r2.z, m.r3.z, m.r4.z );
  Vec4 c4( m.r1.w, m.r2.w, m.r3.w, m.r4.w );
  Vec4 v1( r1 * c1, r1 * c2, r1 * c3, r1 * c4 );
  Vec4 v2( r2 * c1, r2 * c2, r2 * c3, r2 * c4 );
  Vec4 v3( r3 * c1, r3 * c2, r3 * c3, r3 * c4 );
  Vec4 v4( r4 * c1, r4 * c2, r4 * c3, r4 * c4 );
  return Mat4( v1, v2, v3, v4 );
}


Mat4 Mat4::operator+( Mat4 &m ) {
  Vec4 v1( r1.x + m.r1.x, r1.y + m.r1.y, r1.z + m.r1.z, r1.w + m.r1.w );
  Vec4 v2( r2.x + m.r2.x, r2.y + m.r2.y, r2.z + m.r2.z, r2.w + m.r2.w );
  Vec4 v3( r3.x + m.r3.x, r3.y + m.r3.y, r3.z + m.r3.z, r3.w + m.r3.w );
  Vec4 v4( r4.x + m.r4.x, r4.y + m.r4.y, r4.z + m.r4.z, r4.w + m.r4.w );
  return Mat4( v1, v2, v3, v4 );

}

Mat4 Mat4::inverse() {
  glm::mat4 toBeInversed = glm::transpose(
    glm::mat4( r1.x,r1.y,r1.z,r1.w,
          r2.x,r2.y,r2.z,r2.w,
          r3.x,r3.y,r3.z,r3.w,
          r4.x,r4.y,r4.z,r4.w) ) ;

  glm::mat4 inversed = glm::inverse( toBeInversed );

  return Mat4( inversed[0][0], inversed[1][0], inversed[2][0], inversed[3][0],
               inversed[0][1], inversed[1][1], inversed[2][1], inversed[3][1],
               inversed[0][2], inversed[1][2], inversed[2][2], inversed[3][2],
               inversed[0][3], inversed[1][3], inversed[2][3], inversed[3][3]);
}


Mat4 Mat4::transpose() {
  return Mat4( r1.x, r2.x,r3.x,r4.x,
               r1.y, r2.y,r3.y,r4.y,
               r1.z, r2.z,r3.z,r4.z,
               r1.w, r2.w,r3.w,r4.w);
}


void Mat4::display() {
  printf( "[ %.2f, %.2f, %.2f, %.2f; \n", r1.x, r1.y, r1.z, r1.w );
  printf( "  %.2f, %.2f, %.2f, %.2f; \n", r2.x, r2.y, r2.z, r2.w );
  printf( "  %.2f, %.2f, %.2f, %.2f; \n", r3.x, r3.y, r3.z, r3.w );
  printf( "  %.2f, %.2f, %.2f, %.2f ]\n", r4.x, r4.y, r4.z, r4.w );
}