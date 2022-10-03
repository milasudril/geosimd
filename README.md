GeoSIMD
=======
This is a header-only library that contains functions using SIMD for 3D geometry. Features

 * Strict distinction between Points, Vectors, and Directions
 * Different types for translations and rotations
 * A special type for angles

These abstractions are implemented with ZOAP in mind.

Directions
----------
A Direction is a Vector with unit length. Directions can only be transformed by rotations, but share most of their behaviors with Vectors.

Vectors
-------
Vectors are translation invariant. They can be rotated and scaled. The latter transformation is not yet implemented. Vectors can be added, subtracted, and multiplied by a scalar. It is also possible to use dot product, and cross product on them.

Points
------
Points in space. Any transformation can be applied to a point. It is possible to add Vectors to points, and to subtract Points. The latter will produce a Vector. It is not possible to add two points. However, it *is* possible to compute their centroid.

Library structure
-----------------
Storage types for vectors are found in `vector_storage.hpp`. It uses `vector_limits.hpp` to determine whether or not a type is suitable for native vectorization. If not support is emulated through an `emulated_vector`. There is support for complex vectors. This works by using std::complex together with a vector type. Thus, a complex vector will consist of a real vector, and an imaginary vector.

The main abstraction over SIMD operations is `vec_t`. In addition to arithmetic operations, `vec_t` defines the Hermitian `inner_product`, as well as vector complex conjugate. In order to save code, arithmetic operations are provided through the `arithmetic_mixin` class template.

A note on performance
---------------------
While efforts has been made to force the compiler to optimize away abstractions also without any optimizations turned on, it is still recommended to enable all optimizations when using this library. This means that the following options are recommended

`-O3 -ffast-math -ftree-vectorize`