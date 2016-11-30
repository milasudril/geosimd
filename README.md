GeoSIMD
=======
This is a header-only library that contains functions using SIMD for 3D geometry. Features

 * Strict distinction between Points, Vectors, and Directions
 * Different types for translations and rotations
 * A special type for angles

These abstractions are implemented following the ZOAP principle.

Directions
----------
A Direction is a Vector with unit length. Directions can only be transformed by rotations, but share most of their behaviors with Vectors.

Vectors
-------
Vectors are translation invariant. They can be rotated and scaled. The latter transformation is not yet implemented. Vectors can be added, subtraceted, and multiplied by a scalar. It is also possible to use dot product, and cross product on them.

Points
------
Points in space. Any transformation can be applied to a point. It is possible to add Vectors to points, and to subtract Points. The latter will produce a Vector. It is not possible to add two points.