#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * memory memory.inl
 *
 */

#include "core/error/error.inl"
#include "core/memory/allocator.h"
#include "core/memory/types.h"


namespace crown
{
	namespace memory
	{
		inline void* align_top(const void* p, u32 align)
		{
			CE_ASSERT(align >= 1, "Alignment must be > 1");
			CE_ASSERT(align % 2 == 0 || align == 1, "Alignment must be a power of two");
			const uintptr_t mask = align - 1;
			uintptr_t ptr = (uintptr_t)p;
			ptr = (ptr + mask) & ~mask;
			return(void*)(ptr);
		}

		// respects standard behaviour when calling on NULL @a ptr
		template<typename T>
		inline void call_destructor_and_deallocate(Allocator& a, T* ptr)
		{
			if (!ptr) return;
			ptr->~T();
			a.deallocate(ptr);
		}


	}// namespace memory


	// convert integer to type.
	template<int v>
	struct Int2Type{
		enum{
			value = v
		}; 
	};

	template <typename T>
	inline T &construct(void *p, Allocator& a, Int2Type<true>)
	{
		return *(T*)new (p) T(a);
	}

	template <typename T>
	inline T &construct(void *p, Allocator& /*a*/, Int2Type<false>)
	{
		return *(T*)new (p) T();
	}

	template<typename T>
	inline T &construct(void *p, Allocator& a)
	{
		return construct<T>(p, a, IS_ALLOCATOR_AWARE_TYPE(T)());
	}

}// namespace crown

// allocates memory with @a allocator for the given @a type
// and calls constructor on it.
// @note 
// @a allocator must be a reference to an existing allocator.
#define CE_NEW(allocator,T) new ((allocator).allocate(sizeof(T),alignof(T))) T

// calls destructot on @a ptr and deallocates memory using the given @a allocator.
// @note
// @a allocator must be a reference to an existing allocator.
#define CE_DELETE(allocator,ptr) crown::memory::call_destructor_and_deallocate(allocator,ptr) 