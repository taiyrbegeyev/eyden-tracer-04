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

## Problem 4.4
### Supersampling (? Points)
