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
		template<typename TKey,typename TValue,typename Hash,typename KeyEqual> 
		u32 size(const HashMap<TKey, TValue, Hash, KeyEqual>& m);

		template<typename TKey,typename TValue,typename Hash,typename KeyEqual>
		u32 capacity(const HashMap<TKey, TValue, Hash, KeyEqual>&m);

		template<typename TKey, typename TValue, typename Hash, typename KeyEqual>
		bool has(const HashMap<TKey, TValue, Hash, KeyEqual>&m, const TKey& key);

		template<typename TKey,typename TValue,typename Hash, typename KeyEqual>
		const TValue& get(const HashMap<TKey, TValue, Hash, KeyEqual>& m, const TKey& key, const TValue& deffault);

		template<typename TKey, typename TValue, typename Hash, typename KeyEqual>
		TValue& get(HashMap<TKey, TValue, Hash, KeyEqual>& m, const TKey& key, const TValue& deffault);

		template<typename TKey,typename TValue,typename Hash, typename KeyEqual>
		void set(HashMap<TKey, TValue, Hash, KeyEqual>&m, const TKey& key, const TValue& value);

		template<typename TKey,typename TValue, typename Hash, typename KeyEqual>
		void remove(HashMap<TKey, TValue, Hash, KeyEqual>&m, const TKey& key);

		template<typename TKey,typename TValue,typename Hash,typename KeyEqual>
		void clear(HashMap<TKey, TValue, Hash, KeyEqual>&m);

		template<typename TKey,typename TValue,typename Hash,typename KeyEqual>
		bool is_hole(const HashMap<TKey, TValue, Hash, KeyEqual>& m, const typename HashMap<TKey, TValue, Hash, KeyEqual>::Entry* entry);

		template<typename TKey,typename TValue, typename Hash,typename KeyEqual>
		const typename HashMap<TKey, TValue, Hash, KeyEqual>::Entry* begin(const HashMap<TKey, TValue, Hash, KeyEqual>&m);
		template<typename TKey, typename TValue, typename Hash,typename KeyEqual>
		const typename HashMap<TKey, TValue, Hash, KeyEqual>::Entry* end(const HashMap<TKey, TValue, Hash, KeyEqual>&m);
	}// namespace hash_map


	namespace hash_map_internal
	{
		const u32 END_OF_LIST = 0xffffffffu;
		const u32 DELETED = 0x80000000u;
		const u32 FREE = 0x00000000u;
		template<typename TKey,typename Hash>
		inline u32 key_hash(const TKey& key)
		{
			const Hash hash;
			return hash(key);
		}

		template <typename TKey, typename KeyEqual>
		inline bool key_equals(const TKey& key_a, const TKey& key_b)
		{
			const KeyEqual equal;
			return equal(key_a, key_b);
		}

		inline bool is_deleted(u32 index)
		{
			return (index >> 31) != 0;
		}

		template<typename TKey,typename TValue,typename Hash,typename KeyEqual>
		inline u32 probe_distance(const HashMap<TKey, TValue, Hash, KeyEqual>&m, u32 hash, u32 slot_index)
		{
			const u32 hash_i = hash & m._mask;
			return (slot_index + m._capacity - hash_i)&m._mask;
		}

		template<typename TKey,typename TValue, typename Hash,typename KeyEqual>
		u32 find(const HashMap<TKey, TValue, Hash, KeyEqual>&m, const TKey& key)
		{
			if (m_size == 0)
				return END_OF_LIST;
			const u32 hash = key_hash<TKey, Hash>(key);
			u32 hash_i = hash & m._mask;
			u32 dist = 0;
			for (;;)
			{
				if (m._index[hash_i].index == FREE)
					return END_OF_LIST;
				else if (dist > probe_distance(m, m._index[hash_i].hash, hash_i))
					return END_OF_LIST;
				else if (!is_deleted(m._index[hash_i].index) && m._index[hash_i].hash == hash && key_equals<TKey, KeyEqual>(m._data[hash_i].first, key))
					return hash_i;
				hash_i = (hash_i + 1)&m._mask;
				++dist;
			}
		}

		template<typename TKey,typename TValue,typename Hash,typename KeyEqual>
		void insert(HashMap<TKey, TValue, Hash, KeyEqual>&m, u32 hash, const TKey& key, const TValue& value)
		{
			PAIR(TKey, TValue) new_item(*m._allocator);
			new_item.first = key;
			new_item.second = value;

			u32 hash_i = hash & m._mask;
			u32 dist = 0;
			for(;;)
			{
				if (m._index[hash_i].index == FREE)
					goto INSERT_AND_RETURN;
				u32 existing_elem_probe_dist = probe_distance(m, m._index[hash_i].hash, hash_i);
				if (is_deleted(m._index[hash_i].index)||existing_elem_probe_dist < dist)
				{
					if (is_deleted(m._index[hash_i].index))
						goto INSERT_AND_RETURN;
					exchange(hash, m._index[hash_i].index);
					m._index[hash_i].index = 0x0123abcd;
					swap(new_item, m._data[hash_i]);
					dist = existing_elem_probe_dist;
				}	
				hash_i = (hash_i + 1)&m._mask;
				++dist;
			}
		INSERT_AND_RETURN:
			memcpy((void*)(m._data + hash_i), &new_item, sizeof(new_item));
			m._index[hash_i].hash = hash;
			m._index[hash_i].index = 0x0123abcd;
			PAIR(TKey, TValue) empty(*m._allocator);
			memcpy((void*)&new_item, &empty, sizeof(new_item));
		}

		template<typename TKey,typename TValue, typename Hash,typename KeyEqual>
		void rehash(HashMap<TKey, TValue, Hash, KeyEqual>&m, u32 new_capacity)
		{
			typedef typename HashMap<TKey, TValue, Hash, KeyEqual>::Entry Entry;
			typedef typename HashMap<TKey, TValue, Hash, KeyEqual>::Index Index;

			HashMap<TKey, TValue, Hash, KeyEqual> nm(*m._allocator);
			const u32 size = new_capacity*(sizeof(Index) + sizeof(Entry)) + alignof(Index) + alignof(Entry);
			nm._buffer = (char*)nm._allocator->allocate(size);
			nm._index = (Index*)memory::align_top(nm._buffer, alignof(Index));
			nm._data = (Entry*)memory::align_top(nm._index + new_capacity, alignof(Entry));

		}

		template<typename TKey,typename TValue,typename Hash, typename KeyEqual>
		void grow(HashMap<TKey, TValue, Hash, KeyEqual>&m)
		{

			// why default is 16 ???
			const u32 new_capacity = (m._capacity == 0 ? 16 : m._capacity * 2);
			rehash(m, new_capacity);
		}

		template<typename TKey, typename TValue,typename Hash, typename KeyEqual>
		bool full(const HashMap<TKey, TValue, Hash, KeyEqual>&m)
		{
			//why not size  == capacity ???
			return m._size >= m._capacity*0.9f;
		}
	}// namespace hash_map_internal

	template<typename TKey,typename TValue, typename Hash, typename KeyEqual>
	inline HashMap<TKey, TValue, Hash, KeyEqual>::HashMap(Allocator& a)
		:_allocator(&a)
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
			_buffer = (char*)_allocator->allocate(size);
			_index = (Index*)memory::align_top(_buffer, alignof(Index));
			_data = (Entry*)memory::align_top(_index + _capacity, alignof(Entry));

			memcpy(_index, other._index, sizeof(Index)*other._capacity);
			for (u32 i=0;i<other._capacity;++i)
			{
				const u32 index = other._index[i].index;
// 				if (index != hash_map_internal::FREE && !hash_map_internal::is_deleted(index))
// 					new (&_data[i]) Entry(other._data[i]);
			}
		}
	}
	template<typename TKey, typename TValue, typename Hash, typename KeyEqual>
	inline HashMap<TKey, TValue, Hash, KeyEqual>::~HashMap()
	{
	}
}// namespace crown