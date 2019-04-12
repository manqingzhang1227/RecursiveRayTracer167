CC = g++
CFLAGS = -Wall -g

ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk   '{ print $$2}'),Mac)
INCFLAGS = -I./glm-0.9.7.1 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ \
                -L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
                -lGL -lGLU -lm -lstdc++ -lfreeimage
else
INCFLAGS = -I./glm-0.9.7.1 -I./include/ -I/usr/X11R6/include -I/sw/include \
                -I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L./lib/nix/ \
                -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lGLEW -lglut -lGLU -lGL -lX11 -lfreeimage
endif


RM = /bin/rm -f


all:  RecursiveRayTracer
RecursiveRayTracer: main.o World.o Camera.o Geometry.o Ray.o Transform.o readfile.o Matrix.o \
 	Vector.o Point.o
	$(CC) $(CFLAGS) $(INCFLAGS) -o hw4 main.o World.o Camera.o Ray.o \
	Geometry.o Transform.o readfile.o Matrix.o Vector.o Point.o $(LDFLAGS)
main.o: main.cpp World.h  Camera.h Geometry.h readfile.h

	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
readfile.o: readfile.cpp  Transform.h Matrix.h Vector.h Point.h
	$(CC) $(CFLAGS) -c readfile.cpp
World.o: World.cpp Camera.h Geometry.h Ray.h Matrix.h Vector.h Point.h
	$(CC) $(CFLAGS) -c World.cpp
Transform.o: Transform.cpp Matrix.h Vector.h Point.h
	$(CC) $(CFLAGS) -c Transform.cpp
Geometry.o: Geometry.cpp Geometry.h Ray.h Matrix.h Vector.h Point.h
	$(CC) $(CFLAGS) -c Geometry.cpp
Camera.o: Camera.cpp Ray.h Vector.h Point.h
	$(CC) $(CFLAGS) -c Camera.cpp
Ray.o: Ray.cpp Vector.h Point.h
	$(CC) $(CFLAGS) -c Ray.cpp
Matrix.o: Matrix.h Vector.h Point.h
Vector.o: Vector.h Point.h
Point.o: Point.h

clean:
	$(RM) *.o hw4 *.gch
