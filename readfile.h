#ifndef READFILE_H
#define READFILE_H


#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>

#include "World.h"
#include "Transform.h"


using namespace std;


// Readfile definitions
void matransform( stack <Mat4> &transfstack, float* values );


void rightmultiply( const Mat4 &M, stack <Mat4> &transfstack );
bool readvals ( stringstream &s, const int numvals, float * values) ;


//void readfile (const char * filename, World &w );
World readfile( const char* filename);


#endif