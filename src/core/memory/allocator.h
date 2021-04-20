#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * memory allocator.h
 *
 */

#include "core/types.h"

namespace crown
{
	struct Allocator
	{
		Allocator() {}
		virtual ~Allocator(){}
		Allocator(const Allocator&) = delete;
		Allocator& operator=(const Allocator&) = delete;


		/// allocates @a size bytes of memory aligned to the specified
		/// @a align byte and returns a pointer to the first allocated byte.
		virtual void* allocator(u32 size, u32 align = DEFAULT_ALIGN) = 0;

		/// deallocates a previously allocated block of memory pointed by @a data.
		virtual void deallocator(void* data) = 0;

		/// returns the size of the memory block pointed by @a ptr or SIZE_NOT_TRACKED 
		/// if the allocator does not support memory tracking.
		/// @a ptr must be a pointer returned by Allocator::allocator
		virtual u32 allocated_size(const void* prt) = 0;

		/// returns the total number of bytes allocated.
		virtual u32 total_allocated() = 0;

		static const u32 DEFAULT_ALIGN = 4;
		static const u32 SIZE_NOT_TRACKED = 0xffffffffu;
	};
}// namespace crown