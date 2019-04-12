This is a recursive ray tracer program written in c++ that takes an input file and output images with the ray tracing technique.
Check the sample output images in the directory "Output_Images".

[[[Compile:]]]

Makefile is provided, use cmake to compile.

[[[Run:]]]

After compile, "./RecursiveRayTracer" or follow the usage specified.


[[[Write Input Files:]]]

You can write your own input files. The input file consists of a sequence of lines, each of which has a command. For examples and clarifications, see the example input files. The lines have the following form. 

BASICS:

Any line starting with # is recognized as commets.
The input file can have blank lines that should be ignored.
command parameter1 parameter2 ... The first part of the line is always the command. Based on what the command is, it has certain parameters which should be parsed appropriately.
size width height: The size command must be the first command of the file, which controls the image size.
maxdepth depth: The maximum depth (number of bounces) for a ray (default should be 5).
camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov specifies the camera in the standard way.

GEOMETRY:

Only pheres and triangles are allowed. 
sphere x y z radius Defines a sphere with a given position and radius.
vertex x y z Defines a vertex at the given location. The vertex is put into a pile, starting to be numbered at 0.
tri v1 v2 v3 Create a triangle out of the vertices involved (which have previously been specified with the vertex command). The vertices are assumed to be specified in counter-clockwise order. Your code should internally compute a face normal for this triangle.

TANSFORMATIONS:

translate x y z A translation 3-vector.
rotate x y z angle Rotate by angle (in degrees) about the given axis as in OpenGL.
scale x y z Scale by the corresponding amount in each axis (a non-uniform scaling).
pushTransform Push the current modeling transform on the stack.
popTransform Pop the current transform from the stack.

LIGHTS:

directional x y z r g b The direction to the light source, and the color, as in OpenGL.
point x y z r g b The location of a point source and the color, as in OpenGL.
attenuation const linear quadratic Sets the constant, linear and quadratic attenuations (default 1,0,0) as in OpenGL. By default there is no attenuation (the constant term is 1, linear and quadratic are 0; that's what we mean by 1,0,0).
ambient r g b The global ambient color to be added for each object (default is .2,.2,.2).
Note that we allow the ambient value to be changed between objects, which means different objects will be rendered with a different ambient term.
Note also that if no ambient color or attenuation is specified, the default values specified above will be used.

MATERIALS:

diffuse r g b specifies the diffuse color of the surface.
specular r g b specifies the specular color of the surface.
shininess s specifies the shininess of the surface.
emission r g b gives the emissive color of the surface.

