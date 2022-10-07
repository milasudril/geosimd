#ifndef GEOSMID_INLINE_HPP
#define GEOSIMD_INLINE_OPT_HPP

#define GEOSIMD_FORCE_OPT [[gnu::optimize(3)]] [[gnu::nocf_check]]
#define GEOSIMD_INLINE [[gnu::always_inline]]
#define GEOSIMD_FLATTEN [[gnu::flatten]]
#define GEOSIMD_INLINE_OPT GEOSIMD_FORCE_OPT GEOSIMD_INLINE
#define GEOSIMD_FULL_INLINE GEOSIMD_INLINE_OPT GEOSIMD_FLATTEN

#endif