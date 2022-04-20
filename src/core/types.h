#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include <stdint.h>
#include <stddef.h>

#ifndef CROWN_DEBUG
	#define CROWN_DEBUG 0
#endif // CROWN_DEBUG

#ifndef CROWN_DEVELOPMENT
	#define CROWN_DEVELOPMENT 0
#endif

namespace crown
{
	typedef int8_t		s8;
	typedef uint8_t		u8;
	typedef int16_t		s16;
	typedef uint16_t	u16;
	typedef int32_t		s32;
	typedef uint32_t	u32;
	typedef float		f32;
	typedef double		f64;
	typedef int64_t		s64;
	typedef uint64_t	u64;
}// namespace crown

template<typename T>
inline void exchange(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

#define CE_NOOP(...) do { (void)0; } while (0)
#define CE_UNUSED(x) do { (void)(x); } while (0)
#define CE_STATIC_ASSERT(condition,...) static_assert(condition,"" # __VA_ARGS__)

#if CROWN_COMPILER_GCC || CROWN_COMPILER_CLANG
	#define CE_LIKELY(X) __builtin_expect((c,1))
	#define CE_UNLIKLY(X) __builtin_expect((x),0)
	#define CE_UNREACHABLE() __builtin_unreachable()
	#define CE_ALIGN_DECL(align,decl) decl __attribute__ ((aligned (align)))
	#define CE_THREAD __thread
#elif CROWN_COMPILER_MSVC
	#define CE_LIKELY(x) (x)
	#define CE_UNLIKELY(x) (x)
	#define CE_UNREACHABLE()
	#define CE_ALIGN_DECL(align_, decl) __declspec (align(align_)) decl
	#define CE_THREAD __declspec(thread)
#else
	#error "Unknown compiler"
#endif