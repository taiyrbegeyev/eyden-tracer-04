# Practical Assignment 4
## Problem 4.1 
### Vertex Normals (? Points)
Rather then storing a single _geometry normal_ for a triangle, it is often useful to store at each ```vertex``` a corresponding _vertex normal_. The advantage is that if we have a hit point on a triangle, the shading normal can be smoothly interpolated between the vertex normals. If neighboring triangles share the same vertex normals, a smooth appearance can be generated over non-smooth tesselated geometry.  
Proceed as follows:
1. Fork the current repository.
2. Extend ```Scene::ParseOBJ()``` to also support vertex normals. Take a look at the included .obj files.
3. Turn off BSP-support.
4. Your ray class is extended with two additional ```float``` values calles ```Ray::u``` and ```Ray::v```.
5. In ```Triangle::Intersect```, store the computed barycentric coordinates into ```Ray::u``` and ```Ray::v```.
Note: As long as your other classes (_e.g._ Sphere) don’t need local surface coordinates, there is no need to compute them yet.
6. In the framework is a new class ```SmoothTriangle``` which stores the vertex normals (```na```, ```nb``` and ```nc```) additionaly to the original vertex positions.
7. In ```SmoothTriangle::GetNormal()``` use the u/v coordinates of the hitpoint to interpolate between the vertex normals. Note: Interpolating normalized vectors will not return a normalized vector! Make sure to normalize your interpolated normal!
8. Test your implementation with cylinder16.obj cone32.obj using the appropriate camera you can choose in Scene.h. Compare the difference between the regular and the smooth triangles.  
If everything is correct your images should look like this:

## Problem 4.2
### Procedual Bump Mapping (? Points)

## Problem 4.3
### Texturing (? Points)
Until now we have only used one color per object. Nevertheless, in reality, _e.g._ in games, objects are very often colorful because of the usage of textures. This is also a way of making a surface look more geometrically complex. Usually, textures are used by storing _texture coordinates_ at the vertices of each triangles, and interpolating those to find the correct texel that has to be used for a surface point.
1. Turn BSP-support on
2. In the framework is a new class ```TexturedSmoothTriangle``` (derived from ```SmoothTriangle```), that additionally has the three fields ```Vec3f ta,tb,tc```, which correspond to the texture coordinates at vertex ```a```, ```b```, or ```c```, respectively. For the sake of simplicity we will use ```Vec3f```’s to store the texture coordinates, even though they usually require only 2 coordinates (barycentric coordinates). Add support for texture coordinates to your parser (```ParseOBJ()```).
3. Implemet the method ```Vec3f TexturedSmoothTriangle::GetUV(Ray& ray, float& u, float& v)``` which is now a virtual method in your primitive base class. In ```TexturedSmoothTriangle```, implement this function to return the ```x``` and ```y``` coordinates of the interpolated vertex texture coordinates. (For other primitives, just ignore it for now, we’ll only use texture-shaders with triangles for now).
4. Implement the ```TexturedEyeLightShader::Shade()``` method to use the texture coordinates returned by ```getUV()``` and combine the texel color with the calculated eyelight color using the vector product. 

Test your implementation on barney.obj with barney.ppm. If everything is correct your image should look like this:

## Problem 4.4
### Supersampling (? Points)
