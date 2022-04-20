#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * error error.inl
 *
 */

#include "core/error/error.h"

#if CROWN_DEBUG
	#define CE_ASSERT(condition,msg, ...)						\
			do													\
			{													\
				if (CE_UNLIKELY(!(condition)))					\
				{												\
					crown::error::abort("Assert failed: %s\n"	\
					"	In:%s:%d\n"								\
					"	" msg "\n"								\
					, # condition								\
					, __FILE__									\
					, __LINE__									\
					, ## __VA_ARGS__							\
					);											\
					CE_UNREACHABLE();							\
				}												\
			} while (0)
#else
	#define CE_ASSERT(...) CE_NOOP()
#endif// CROWN_DEBUG

#define CE_FATAL(msg,...) CE_ASSERT(false,msg,## __VA_ARGS__)
#define CE_ENSURE(condition) CE_ASSERT(condition,"")