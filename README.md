# GeoSIMD

This is a header-only library whose main focus is to model Euclidian geometry with SIMD. The library contains abstractions for

 * Vectors
 * Points
 * Angles

While efforts has been made to force the compiler to optimize away abstractions also without any optimizations turned on (debugging an optimize build is a real pain), it is still recommended to enable all optimizations when using this library. This means that the following options are recommended

`-O3 -ffast-math -ftree-vectorize`


## Vectors and Points

A point can be defined as a 0-dimensional object with a distinct location in some space. It is possible to take the difference between two poins A and B. Doing so, results in a vector from A to B. Vectors can be added, and multiplied by a factor called a scalar. Furthermore, points and vectors can be added, which results in a different point. Since these concepts are interesting on their own, and also that C++ has types that describes points (such as pointers), and vectors (regular signed integers), these are described as `concepts`, see `abstract_spaces.hpp`.

Storage types for vectors (and also points), of a compile-time known dimensionality, are found in `vector_storage.hpp`. It uses `vector_limits.hpp` to determine whether or not a type is suitable for native vectorization. If not support is emulated through an `emulated_vector`. There is support for complex vectors. This works by using std::complex together with a vector type. Thus, a complex vector will consist of a real vector, and an imaginary vector. The main abstraction over SIMD operations is `vec_t`. In addition to arithmetic operations, `vec_t` defines the Hermitian `inner_product`, as well as vector complex conjugate.

Vectors and points are modelled by `basic_vector` and `basic_point`, respectively. These are class templates that accepts a suitable vector space. `basic_point` requires the vector space to be an affine space. The requirements on different kinds of vector spaces are specified in `abstract_spaces.hpp`. Basically, a vector space is implemented as a struct, containing using aliases and static member functions. The minimal requirement on a vector space, is that it specifies the vector type, and the scalar type. An affine space, must also specify the point type. An example of an affine space, that would work with both `basic_point` and `basic_vector` is

```c++
struct writable_address_space
{
	using vector_type = intptr_t;
	using scalar_type = intptr_t;
	using point_type = std::byte*;
};
```

Since it is possible to compute the distance between two pointers, `writable_address_space` is also a metric space. It is also possible to create similar mappings for the `std::chrono` library.

The Euclidian N-space is defined in `euclidian_sapce.hpp`. The Euclidian N-space is a metric normed space, with the norm defined as in a Hilbert space. Points are called `location`s and vectors are called `displacement`s. The implementation of the Euclidian N-space found in this library uses homogenous coordinates, which means that if the observable dimensionality is N, N+1 elements are allocated for each object. For example a, for a 3-dimensional quantity, 4 elements are used, the last being 0 for a vector, and 1 for a point.


### More about vector spaces

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

In computer graphics it is common to use homogenous coordinates. This requires that points and vectors has an extra coordinate that should be 1 for points and 0 for vectors. To enable this behaviour, there has to be a type called `enable_homogenous_coordinates_t` in the vector space struct.

## Unit "vectors"

In a normed space, there are unit "vectors". Unit "vectors" are not fully vectors. They only support multiplication by a scalare, which result in a proper vector. This means that a unit "vector" always has unit length.

## Angles

GeoSIMD features two models for an angle. A `rotation_angle` is inteded to be used as a representation of the total rotation of an object (mod 2 pi). A `turn_angle` can be used to increment or decrement a `rotation_angle`. The difference between two `rotation_angle`s results in a `turn_angle`. Furthermore `turn_angles` can be multiplied by a scalar. Thus, a `turn_angle` is the vector between two points of type `rotation_angle`.

Angles are represented as a binary angle, where one full turn equals 2^32. To make it easy to rotate an object with same precision infinitely, a `rotation_angle` is represented by an `uint32_t`. A `turn_angle` is stored as an `int64_t`, and thus it can store multiple turns.
