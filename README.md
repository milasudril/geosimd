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

The two most fundamental classes in the application domain are `basic_vector` and `basic_point`. These are class templates that accepts a suitable vector space. `basic_point` requires the vector space to be an affine space. The requirements on different kinds of vector spaces are specified in `abstract_spaces.hpp`. Basically, a vector space is implemented as a struct, containing using aliases and static member functions. The minimal requirement on a vector space, is that it specifies the vector type, and the scalar type. An affine space, must also specify the point type. An example of an affine space, that would work with both `basic_point` and `basic_vector` is

```c++
struct writable_address_space
{
	using vector_type = intptr_t;
	using scalar_type = intptr_t;
	using point_type = std::byte*;
};
```

Since it is possible to compute the distance between two pointers, `writable_address_space` is also a metric space. It is also possible to create similar mappings for the `std::chrono` library.

In computer graphics it is common to use homogenous coordinates. This requires that points and vectors has an extra coordinate that should be 1 for points and 0 for vectors. To enable this behaviour, there has to be a type called `enable_homogenous_coordinates_t` in the vector space struct.

If there is an associated norm, a vector space is called normed. If no norm is specified, the vector space is normed if there is a function to compute the norm of `vector_type`, visible through ADL. If there is a function called `norm`, it will be used. For som types it is possible to compute the absolute value. If no `norm` function is found `abs` will be used as a substitute. If the vector space defines a custom norm, that one will override the norm found by ADL. To specify a custom norm, add a function called `norm` accepting a `vector_type` to the vector space:

```c++
struct your_vector_space
{
	// Other definitions

	static auto norm(vector_type x)
	{
	// compute the norm of x
	}

	// More definitions
};
```

For a norm to be valid, the return value has to satisfy the `std::totally_ordered` requirement.

A commonly used family of vector spaces are Hilbert spaces. A Hilbert space defines its norm as the square root of the inner product of a vector with itself. Hilbert space behaviour is enabled by inheriting from the `hilbert_space_mixin` class template.

```c++
template<class VectorType, class ScalarType>
struct your_vector_space : public geosimd::hilbert_space_mixin<VectorType, ScalarType>
{
};
```

In addition to adding a norm, this will add `using`-aliases for `VectorType` and `ScalarType`. In addition to that, `norm_squared` is defined. This is because is common to use the square of the norm rather than the norm itself, and using `norm_squared` may be required to eliminate the computation of the square root.

It is also possible to customize the distance function in a metric space. By default, the absolute value of the difference between two points is used. If `abs` cannot be used on the associated `vector`, or another distance function is desired, it has to be specified by the vector space struct:

```c++
struct your_vector_space
{
	// Other definitions

	static auto distance(point_type a, point_type b)
	{
	// Compute the distance between a and b
	}

	// More definitions
};
```

Notice that the return value must satisfy the `std::totally_ordered` requirement.

Often, the norm of the difference between two point is used as the distance function. This behaviour can be enabled by inheriting from `metric_normed_space_mixin` class template:

```c++
template<class PointType, normed_space V>
struct your_vector_space : public geosimd::metric_normed_space_mixin<PointType, V>
{
};
```

`your_vector_space` is now a metric normed space, with PointType added to the normed space `V`. For the same reason as `hilbert_space_mixin` adds `normed_squared`, `metric_normed_space_mixin` adds the `distance_squared` function.

By combining `metric_normed_space_mixin` with a suitable Hilbert space as `normed_space`, and adding `enable_homogenous_coordinates_t`, a model of the 3-dimensional Euclidan space can be described:

```c++
struct euclidian_3space :
	geosimd::metric_normed_space_mixin<geosimd::vec4f32_t,
		geosimd::hilbert_space_mixin<geosimd::vec4f32_t>>
{
	using enable_homogenous_coordinates_t = void;
};

using e3_point = geosimd::basic_point<euclidian_3space>;
using e3_vector = geosimd::basic_vector<euclidian_3space>;

constexpr auto dot(e3_vector a, e3_vector b)
{ return inner_product(a, b); }

//...

```




A note on performance
---------------------
While efforts has been made to force the compiler to optimize away abstractions also without any optimizations turned on, it is still recommended to enable all optimizations when using this library. This means that the following options are recommended

`-O3 -ffast-math -ftree-vectorize`