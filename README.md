# Practical Assignment 4
**Name:** .......
## Problem 4.1 
### Vertex Normals (? Points)
Rather then storing a single _geometry normal_ for a triangle, it is often useful to store at each ```vertex``` a corresponding _vertex normal_. The advantage is that if we have a hit point on a triangle, the shading normal can be smoothly interpolated between the vertex normals. If neighboring triangles share the same vertex normals, a smooth appearance can be generated over non-smooth tesselated geometry.  
Proceed as follows:
1. Fork the current repository.
2. Modify the README.md file in your fork and put your name (or names if you work in a group) above.
3. Extend ```CScene::ParseOBJ()``` to also support vertex normals. Take a look at the included .obj files in the data folder.
4. Turn off BSP-support by disabling the flag `ENABLE_BSP` in types.h file or in cmake-gui.exe application. 
5. Your ray class is extended with two additional ```float``` values calles ```Ray::u``` and ```Ray::v```.
6. In ```bool CPrimTriangle::Intersect(Ray& ray)```, store the computed barycentric coordinates into ```Ray::u``` and ```Ray::v```.  
Note: As long as your other classes (_e.g._ ```CPrimSphere```) don’t need local surface coordinates, there is no need to compute them yet.
7. In the framework is a new class ```CPrimTriangleSmooth``` which stores the vertex normals (```na```, ```nb``` and ```nc```) additionaly to the original vertex positions.
8. In ```Vec3f CPrimTriangleSmooth::GetNormal(const Ray& ray)``` use the u/v coordinates of the hitpoint to interpolate between the vertex normals.  
Note: Interpolating normalized vectors will not return a normalized vector! Make sure to normalize your interpolated normal!
9. Test your implementation with cylinder16.obj and cone32.obj using the appropriate camera you can choose in Scene.h. Compare the difference between the regular and the smooth triangles.  
If everything is correct your images should look like this:  
<img src="./doc/cylinder.jpg" width="400px"><img src="./doc/cylinder_smooth.jpg" width="400px">  
<img src="./doc/cone.jpg" width="400px"><img src="./doc/cone_smooth.jpg" width="400px">

## Problem 4.2
### Procedual Bump Mapping (? Points)
In the last exercise you have learned that the appearence of a surface can be changed by using a modified _surface normal_. In this exercise we will implement a technique called _bump mapping_ which bumps the surface normal sideways such that a surface has the impression of beeing bumped. This often allows to generate the appearance of highly complex surface with only very few primitives. In order to do this, three parameters have to be known for each surface point:
1. The original surface normal _N_.
2. A local coordinate frame for this surface point. Though any coordinate frame can be used (as long as it is consistent), the usual way is to use the surface derivates in _u_ and _v_ direction, called _dPdu_ and _dPdv_.
3. The amount _delta_u_, _delta_v_ of deviation along these tangent vectors. The deviation is usually either read from a texture, or is computed procedurally. The final normal during shading (also for reflections) is then _N' = Normalized(N + delta_u * dPdu + delta_v * dPdv)_.  
In this exercise, you will implement a very basic version of this:
- As surface derivatives, use _dPdu = (1, 0, 0)_ and dPdv = _(0, 0, 1)_.
- For the amount of deviation, use a simple procedural approach, by computing _delta_u = 0.5 * cos(3 * H_x * sin(H_z))_, _delta_v = 0.5 * sin(13 * H_z)_. _H_ denotes the hit point of the ray with the surface.  
For your implementation, proceed as follows:
1. Implement the Shade-method in ShaderPhongBumpMapped.h by first copying the ```Shade()```-method from the basic phong shader and then modifying the normal at the beginning of the ```Shade()``` function, following the guidlines given above.
If your shader work correct you should get an image like this using the scene description in main.cpp:


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
