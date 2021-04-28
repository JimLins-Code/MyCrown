/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * memory globals.h
 *
 */
#include "globals.h"
#include "core/error/error.inl"
#include "core/memory/memory.inl"
#include "core/memory/allocator.h"

#include <stdlib.h>

namespace crown
{
	namespace memory
	{
		// 所申请内存头，size是该段内存的大小
		struct Header
		{
			u32 size;
		};

		// 0xffffffffu => 32位无符号整数。即2^32 = 4294967295
		const u32 HEADER_PAD_VALUE = 0xffffffffu;

		inline void* data_pointer(Header* header, u32 align) {
			void* p = header + 1;
			return memory::align_top(p, align);
		}

		/*
			从给定的data中找到这段内存对应的header
			while (p[-1] == HEADER_PAD_VALUE)
			{
				--p;
			}
			p[-1]返回当前地址的上一字节内容，while的结构相当于逆向遍历指针
		*/
		inline Header* header(const void* data)
		{
			u32* p = (u32*)data;
			while (p[-1] == HEADER_PAD_VALUE)
			{
				--p;
			}
			return (Header*)p - 1;
		}

		inline void fill(Header*header, void* data, u32 size)
		{
			header->size = size;
			u32*p = (u32*)(header + 1);
			while (p < data)
			{
				*p++ = HEADER_PAD_VALUE;
			}
		}

		inline u32 actual_allocation_size(u32 size, u32 align)
		{
			return size + align + sizeof(Header);
		}

		inline void pad(Header* header, void* data)
		{
			u32* p = (u32*)(header + 1);
			while (p != data)
			{
				*p = HEADER_PAD_VALUE;
				p++;
			}
		}

		struct HeapAllocator :public Allocator
		{
			//Mutex _mutex;
			u32 _allocated_size;
			u32 _allocation_count;
			HeapAllocator()
				:_allocation_count(0)
				, _allocated_size(0)
			{

			}
			~HeapAllocator()
			{
				CE_ASSERT(_allocation_count == 0 && total_allocated() == 0
					, "Missing %u deallocations causing leak of %u bytes"
					, _allocation_count
					, total_allocated()
				);
			}

			void *allocate(u32 size, u32 align = Allocator::DEFAULT_ALIGN)
			{
				//ScopeMutex sm(_mutex);
				u32 actual_size = actual_allocation_size(size, align);
				Header* h = (Header*)malloc(actual_size);
				h->size = actual_size;
				void* data = memory::align_top(h + 1, align);
				pad(h, data);
				_allocated_size += actual_size;
				_allocation_count++;
				return data;
			}

			void deallocate(void* data)
			{
				//ScopeMutex sm(_mutex);
				if (!data)
					return;
				Header* h = header(data);
				_allocated_size -= h->size;
				_allocation_count--;
				free(h);
			}

			u32 allocated_size(const void* ptr)
			{
				return get_size(ptr);
			}

			u32 total_allocated()
			{
				//ScopedMutex sm(_mutex);
				return _allocated_size;
			}

			u32 get_size(const void* data)
			{
				//ScopedMutex sm(_mutex);
				Header* h = header(data);
				return h->size;
			}
		};


		struct ScratchAllocator : public Allocator
		{
			//Mutex _mutex;
			Allocator &_backing;
			char* _begin, *_end;
			char* _allocate, *_free;

			ScratchAllocator(Allocator& backing, u32 size)
				:_backing(backing)
			{
				_begin = (char*)_backing.allocate(size);
				_end = _begin + size;
				_allocate = _begin;
				_free = _begin;
			}
			~ScratchAllocator()
			{
				CE_ASSERT(_free == _allocate, "Memory leak");
				_backing.deallocate(_begin);
			}

			bool in_use(void* p)
			{
				if (_free == _allocate)
					return false;
				if (_allocate > _free)
					return p >= _free && p < _allocate;
				return p >= _free || p < _allocate;
			}

			void* allocate(u32 size, u32 align)
			{
				//ScopedMutex sm(_mutex);
				CE_ASSERT(align % 4 == 0, "Must be 4-byte aligned");
				size = ((size + 3) / 4) * 4;

				char* p = _allocate;
				Header* h = (Header*)p;
				char* data = (char*)data_pointer(h, align);
				p = data + size;

				if (p > _end)
				{
					h->size = u32(_end - (char*)h) | 0x80000000u;
					p = _begin;
					h = (Header*)p;
					data = (char*)data_pointer(h, align);
					p = data + size;
				}

				if (in_use(p))
					return _backing.allocate(size, align);

				fill(h, data, u32(p - (char*)h));
				_allocate = p;
				return data;
			}

			void deallocate(void* p)
			{
				//ScopedMutex sm(_mutex);
				if (!p)
					return;
				if (p < _begin || p >= _end)
					return;
				Header* h = header(p);
				CE_ASSERT((h->size & 0x80000000u) == 0, "Not free");
				h->size = h->size | 0x80000000u;
				
				while (_free != _allocate)
				{
					Header* h = (Header*)_free;
					if ((h->size & 0x80000000u) == 0)
						break;
					_free += h->size & 0x7fffffffu;
					if (_free == _end)
						_free = _begin;
				}
			}

			u32 allocated_size(const void* p)
			{
				//ScopedMutex sm(_mutex);
				Header* h = header(p);
				return h->size = u32((char*)p - (char*)h);
			}

			u32 total_allocated()
			{
				//ScopedMetex sm(_mutex);
				return u32(_end - _begin);
			}

		};

	}

	namespace memory_globals
	{
		using namespace memory;

		static char _buffer[sizeof(HeapAllocator) + sizeof(ScratchAllocator)];
		static HeapAllocator* _default_allocator;
		static ScratchAllocator* _default_scratch_allocator;

		void init()
		{
			//_default_allocator = new(_buffer)HeapAllocator();
			_default_allocator = new HeapAllocator();
			//_default_scratch_allocator = new(_buffer+sizeof(HeapAllocator))ScratchAllocator(*_default_allocator,1024*1024);
			_default_scratch_allocator = new ScratchAllocator(*_default_allocator, 1024 * 1024);
		}

		void shutdown()
		{
			_default_scratch_allocator->~ScratchAllocator();
			_default_allocator->~HeapAllocator();
		}
	}// namespace memory_globals

	Allocator& default_allocator()
	{
		return *memory_globals::_default_allocator;
	}

	Allocator& default_scratch_allocator()
	{
		return *memory_globals::_default_scratch_allocator;
	}

} // namespace crown

