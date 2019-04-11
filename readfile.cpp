
#include "readfile.h"


void matransform( stack <Mat4> &transfstack, float* values ) {
  Mat4 transform = transfstack.top();
  Vec4 valvec( values[0], values[1], values[2], values[3] );
  float val1 = transform.r1 * valvec;
  float val2 = transform.r2 * valvec;
  float val3 = transform.r3 * valvec;
  float val4 = transform.r4 * valvec;
  Vec4 newval( val1, val2, val3, val4 );

  values[0] = newval.x;
  values[1] = newval.y;
  values[2] = newval.z;
  values[3] = newval.w;
}


void rightmultiply( Mat4 &M, stack <Mat4> &transfstack ) {
  Mat4 &T = transfstack.top();
  T = T * M;
}


// Function to read the input data values
// Use is optional, but should be very helpful in parsing.
bool readvals( stringstream &s, const int numvals, float* values ) {
  for( int i = 0; i < numvals; i++ ) {
    s >> values[i];
    if( s.fail() ) {
      cout << "Failed reading value " << i << " will skip\n";
      return false;
    }
  }
  return true;
}


World readfile( const char* filename ) {
  string str, cmd;
  ifstream in;
  in.open( filename );
  World world;
  world.s = Scene();

  vector <Point> vertices;
  vector <Point> vertexNormals;
  float diffuse[3];
  float specular[3];
  float emission[3];
  float shininess;

  float globalAmbient[3];
  globalAmbient[0] = 0.2;
  globalAmbient[1] = 0.2;
  globalAmbient[2] = 0.2;


  if( in.is_open() ) {
    stack <Mat4> transfstack;
    transfstack.push( Mat4( 1 ) );

    getline( in, str );
    while( in ) {
      if( ( str.find_first_not_of( " \t\r\n" ) != string::npos ) &&
          ( str[0] != '#' ) ) {
        stringstream s( str );
        s >> cmd;
        float values[10];
        bool validinput;

        if( cmd == "size" ) {
          validinput = readvals( s, 2, values );
          if( validinput ) {
            world.s.w = ( int ) values[0];
            world.s.h = ( int ) values[1];
          }
        }

        else if( cmd == "maxdepth" ) {
          validinput = readvals( s, 1, values );
          if( validinput )
            world.maxDepth = values[0];
        }

        else if( cmd == "output" ) {
          validinput = readvals( s, 1, values );
          if( validinput )
            world.outputFilename = values[0];
        }

        else if( cmd == "camera" ) {
          validinput = readvals( s, 10, values );
          if( validinput )

            world.s.ca = Camera( values[0], values[1], values[2], values[6],
                                 values[7], values[8], values[3], values[4],
                                 values[5], values[9] );
        }

        else if( cmd == "sphere" ) {
          validinput = readvals( s, 4, values );
          if( validinput ) {
            Sphere s( values[0], values[1], values[2], values[3],
                      globalAmbient, diffuse, specular, emission, shininess,
                      transfstack.top() );
            world.spheres.push_back( s );
          }
        }

        else if( cmd == "maxverts" ) {
          validinput = readvals( s, 1, values );
          if( validinput )
            world.maxVert = values[0];
        }

        else if( cmd == "maxvertnorms" ) {
          validinput = readvals( s, 1, values );
          if( validinput )
            world.maxVertNormal = values[0];
        }

        else if( cmd == "vertex" ) {
//          if( world.numVert == world.maxVert ) { // No more vertex
//            cerr << "Reached Maximum Number of vertices " << world.numVert
//                 << " Will ignore further vertices\n";
//          }
//          else {
          validinput = readvals( s, 3, values );
          if( validinput )
            vertices.push_back( Point( values[0], values[1], values[2] ) );
          world.numVert++;
//          }
        }

        else if( cmd == "vertexnormal" ) { //TODO
          if( world.numVertNormal == world.maxVertNormal ) { // No more vertex
            cerr << "Reached Maximum Number of vertex Normals "
                 << world.numVertNormal
                 << " Will ignore further vertex Normals\n";
          }
          else {
            validinput = readvals( s, 6, values );
            if( validinput ) {}
            //todo vertices.push_back( Point( values[0], values[1], values[2]
          }
        }

        else if( cmd == "tri" ) {
          validinput = readvals( s, 3, values );
          Triangle tri;
          if( validinput ) {
            Triangle t( vertices.at( values[0] ), vertices.at( values[1] ),
                        vertices.at( values[2] ), globalAmbient, diffuse,
                        specular, emission, shininess, transfstack.top() );
            world.triangles.push_back( t );
          }
        }

        else if( cmd == "trinormal" ) { //TODO
          validinput = readvals( s, 3, values );
          Triangle tri;
          if( validinput ) {
            world.triangles.push_back( Triangle( vertices.at( values[0] ),
                                                 vertices.at( values[1] ),
                                                 vertices.at( values[2] ) ) );
          }
        }

        else if( cmd == "translate" ) {
          validinput = readvals( s, 3, values );
          if( validinput ) {
            // Think about how the transformation stack is affected
            // Also keep in mind what order your matrix is!
            Mat4 translationMatrix = Transform::translate(
              values[0], values[1], values[2] );
            rightmultiply( translationMatrix, transfstack );
          }
        }

        else if( cmd == "rotate" ) {
          validinput = readvals( s, 4, values );
          if( validinput ) {
            // values[0..2] are the axis, values[3] is the angle.
            // You may want to normalize the axis (or in Transform::rotate)
            // See how the stack is affected, as above.
            // Note that rotate returns a mat3.
            // Also keep in mind what order your matrix is!
            Mat4 rotationMatrix = Mat4( Transform::rotate(
              values[3], Vec3( values[0], values[1], values[2] ) ) );
            rightmultiply( rotationMatrix, transfstack );
          }
        }

        else if( cmd == "scale" ) {
          validinput = readvals( s, 3, values );
          if( validinput ) {
            // Think about how the transformation stack is affected
            // You might want to use helper functions on top of file.
            // Also keep in mind what order your matrix is!
            Mat4 scaleMatrix = Transform::scale(
              values[0], values[1], values[2] );
            rightmultiply( scaleMatrix, transfstack );
          }
        }

        else if( cmd == "pushTransform" ) {
          transfstack.push( transfstack.top() );
        }

        else if( cmd == "popTransform" ) {
          if( transfstack.size() <= 1 ) {
            cerr << "Stack has no elements.  Cannot Pop\n";
          }
          else {
            transfstack.pop();
          }
        }

        else if( cmd == "directional" ) {
          validinput = readvals( s, 6, values ); // Position/color for lts.
          if( validinput ) {
            world.lights.push_back(
              Light( values[3], values[4], values[5], 'd',
                     values[0], values[1], values[2] ) );
            world.numLights++;
          }
        }

        else if( cmd == "point" ) {
          validinput = readvals( s, 6, values ); // Position/color for lts.
          if( validinput ) {
            world.lights.push_back(
              Light( values[3], values[4], values[5], 'p',
                     values[0], values[1], values[2] ) );
            world.numLights++;
          }
        }

        else if( cmd == "attenuation" ) {
          validinput = readvals( s, 3, values ); // Position/color for lts.
          if( validinput ) {
            world.attenuation = Attenuation( values[0], values[1], values[2] );
          }
        }

        else if( cmd == "ambient" ) {
          validinput = readvals( s, 3, values ); // Position/color for lts.
          if( validinput ) {
            world.globalAmbient = Ambient( values[0], values[1], values[2] );
            globalAmbient[0] = values[0];
            globalAmbient[1] = values[1];
            globalAmbient[2] = values[2];
          }
        }

        else if( cmd == "diffuse" ) {
          validinput = readvals( s, 3, values ); // Position/color for lts.
          if( validinput ) {
            diffuse[0] = values[0];
            diffuse[1] = values[1];
            diffuse[2] = values[2];
          }
        }

        else if( cmd == "specular" ) {
          validinput = readvals( s, 3, values ); // Position/color for lts.
          if( validinput ) {
            specular[0] = values[0];
            specular[1] = values[1];
            specular[2] = values[2];
          }
        }

        else if( cmd == "shininess" ) {
          validinput = readvals( s, 1, values ); // Position/color for lts.
          if( validinput ) {
            shininess = values[0];
          }
        }

        else if( cmd == "emission" ) {
          validinput = readvals( s, 3, values ); // Position/color for lts.
          if( validinput ) {
            emission[0] = values[0];
            emission[1] = values[1];
            emission[2] = values[2];
          }
        }

        else {
          cerr << "Unknown Command: " << cmd << " Skipping \n";
        }
      }

      getline( in, str );
    }
  }

  return world;
}

