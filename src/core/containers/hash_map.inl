#pragma once
#include "core/containers/types.h"
#include "core/functional.inl"
#include "core/memory/memory.inl"
#include <string.h>// memcpy

namespace crown
{
	// Functions to manipulate HashMap.
	namespace hash_map
	{

	}// namespace has_map
	template<typename TKey,typename TValue, typename Hash, typename KeyEqual>
	HashMap<TKey, TValue, Hash, KeyEqual>::HashMap(const HashMap<TKey, TValue, Hash, KeyEqual>&other)
		:_allocator(other._allocator)
		, _capacity(0)
		, _size(0)
		, _mask(0)
		, _index(NULL)
		, _data(NULL)
		, _buffer(NULL)
	{}

	template <typename TKey, typename TValue, typename Hash,typename KeyEqual>
	HashMap<TKey, TValue, Hash, KeyEqual>::HashMap(const HashMap<TKey, TValue, Hash, KeyEqual>& other)
		:_allocator(other._allocator)
		, _capacity(0)
		, _size(0)
		, _mask(0)
		, _index(NULL)
		, _data(NULL)
		, _buffer(NULL)
	{
		_capacity = other._capacity;
		_size = other._size;
		_mask = other._mask;
		if (other._capacity > 0)
		{
			_allocator->deallocate(_buffer);
			const u32 size = other._capacity*(sizeof(Index) + sizeof(Entry)) + alignof(Index) + alignof(Entry);
		}
	}
}// namespace crown