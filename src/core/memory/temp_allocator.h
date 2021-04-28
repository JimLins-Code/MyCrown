/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * memory globals.h
 *
 */

#pragma once

#include "core/memory/allocator.h"
#include "core/memory/globals.h"
#include "core/memory/memory.inl"

namespace crown
{
	template<int BUFFER_SIZE>
	struct TempAllocator :public Allocator
	{
		char _buffer[BUFFER_SIZE];
		Allocator &_backing;
		char* _start;
		char* _end;
		char*_p;
		unsigned _chunk_size;

		TempAllocator(Allocator &backing = default_scratch_allocator());
		virtual ~TempAllocator();
		virtual void* allocate(u32 size, u32 align = DEFAULT_ALIGN);
		virtual void* deallocate(void*){}
		virtual u32 allocated_size(const void*){return SIZE_NOT_TRACKED}
		virtual u32 total_allocated(){return SIZE_NOT_TRACKED}
	};

	template<int BUFFER_SIZE>
	TempAllocator<BUFFER_SIZE>::TempAllocator(Allocator &backing) :_backing(backing), _chunk_size(4 * 1024)
	{
		_p = _start = _buffer;
		_end = _start + BUFFER_SIZE;
		*(void**)_start = 0;
		_p += sizeof(void*);
	}

	template<int BUFFER_SIZE>
	TempAllocator<BUFFER_SIZE>::~TempAllocator()
	{
		char* start = _buffer;
		void* p = *(void**)start;
		while (p)
		{
			void* next = *(void**)p;
			_backing->deallocate(p);
			p = next;
		}
	}

}// namespace crown