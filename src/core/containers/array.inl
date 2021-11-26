#pragma once

/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/containers/types.h"
#include "core/error/error.h"
#include "core/memory/allocator.h"

namespace crown
{

	namespace array
	{
		template <typename T>
		bool empty(const Array<T>& a);
		
		template <typename T>
		u32 size(const Array<T>& a);

		template <typename T>
		u32 capacity(const Array<T> & a);

		template <typename T>
		void resize(Array<T>& a, u32 size);

		template <typename T>
		void reserve(Array<T>&a, u32 capacity);

		template <typename T>
		void set_capacity(Array<T>& a, u32 capacity);

		template <typename T>
		void grow(Array<T>&a, u32 min_capacity);

		template <typename T>
		void condense(Array<T>&a);

		template <typename T>
		u32 push_back(Array<T>&a, const T& item);

		template <typename T>
		void pop_back(Array<T>& a);

		template <typename T>
		u32 push(Array<T>&a, const T* items, u32 count);

		template <typename T>
		void clear(Array<T>& a);

		template <typename T>
		T* begin(Array<T>& a);

		template <typename T>
		const T* begin(const Array<T>& a);

		template <typename T>
		T* end(Array<T>&a);

		template <typename T>
		const T* end(const Array<T>&a);

		template <typename T>
		T& front(Array<T>& a);

		template <typename T>
		const T& front(const Array<T>&a);

		template <typename T>
		T& back(Array<T>&a);

		template <typename T>
		const T& back(const Array<T>&a);

	}// namespace array 


	namespace array
	{
		template <typename T>
		inline bool empty(const Array<T>& a)
		{
			return a._size == 0;
		}

		template <typename T>
		inline u32 size(const Array<T>& a)
		{
			return a._size;
		}

		template <typename T>
		u32 capacity(const Array<T> & a)
		{
			return a._capacity;
		}

		template <typename T>
		void resize(Array<T>& a, u32 size)
		{
			if (size > a._capacity)
				set_capacity(a, size);
			a._size = size;
		}

		template <typename T>
		inline void reserve(Array<T>&a, u32 capacity)
		{
			if(capacity > a._capacity)
				grow(a,capacity)
		}

		template <typename T>
		void set_capacity(Array<T>& a, u32 capacity)
		{
			if (a._capacity == capacity)
				return;
			if (capacity < a._size)
				resize(a,capacity)
			if (capacity > 0)
			{
				T* tmp = a._data;
				a._capacity = capacity;
				a._data = (T*)a._allocator->allocate(capacity * sizeof(T), alignof(T));
				memcpy(a._data, tmp, a._size * sizeof(T));
				a._allocator->deallocate(tmp);                          
			}
		}

		template <typename T>
		inline void grow(Array<T>&a, u32 min_capacity)
		{
			u32 new_capacity = a._capacity * 2 + 1;
			if (new_capacity < min_capacity)
				new_capacity = min_capacity;
			set_capacity(a, new_capacity);
		}

		template <typename T>
		inline void condense(Array<T>&a)
		{
			resize(a, a._size);
		}

		template <typename T>
		inline u32 push_back(Array<T>&a, const T& item)
		{
			if (a._capacity == a.size)
				grow(a, 0);
			memcpy(&a._data[a._size], &item, sizeof(T));
			return a._size++;
		}

		template <typename T>
		inline void pop_back(Array<T>& a)
		{
			CE_ASSERT(a._size > 0, "The array is empty");
			--a._size;
		}

		template <typename T>
		inline u32 push(Array<T>&a, const T* items, u32 count)
		{
			if (a._capacity <= a._size +count)
				grow(a, a._size + count);
			memcpy(&a._data[a.size], items, sizeof(T)*count);
			a._size += count;
			return a._size;
		}

		template <typename T>
		inline void clear(Array<T>& a)
		{
			a._size = 0;
		}

		template <typename T>
		inline T* begin(Array<T>& a)
		{
			return a._data;
		}

		template <typename T>
		inline const T* begin(const Array<T>&a)
		{
			return a._data;
		}

		template <typename T>
		inline const T* end(const Array<T>&a)
		{
			return a._data + a._size;
		}

		template <typename T>
		inline T* end(Array<T>&a)
		{
			return a._data + a._size;
		}

		template <typename T>
		inline T& front(Array<T>&a)
		{
			CE_ASSERT(a._size > 0, "The array is empty");
			return a._data[0];
		}

		template <typename T>
		inline const T& front(const Array<T>&a)
		{
			CE_ASSERT(a._size > 0, "The array is empty");
			return a._data[0];
		}

		template <typename T>
		inline T& back(Array<T>&a)
		{
			CE_ASSERT(a.size > 0, "The array is empty");
			return a._data[a._size - 1];
		}

		template <typename T> 
		inline const T& back(const Array<T>&a)
		{
			CE_ASSERT(a.size > 0, "The array is empty");
			return a._data[a._size - 1];
		}

	}


	template <typename T>
	inline Array<T>::Array(Allocator& a)
		:_allocator(a)
		, _capacity(0)
		, _size(0)
		, _data(NULL)
	{
	}

	template<typename T>
	inline Array<T>::Array(const Array<T>& other)
		:_allocator(other._allocator)
		, _capacity(0)
		, _size(0)
		, _data(NULL)
	{
		const u32 size = other._size;
		array::resize(*this, size);
		memcpy(_data, other, _data, sizeof(T)*size);
	}

	template <typename T>
	inline Array<T>::~Array()
	{
		_allocator->deallocate(_data);
	}

	template <typename T>
	inline T& Array<T>::operator[](u32 index)
	{
		CE_ASSERT(index < _size, "Index out of bounds");
		return _data[index];
	}

	template<typename T>
	inline const T& Array<T>::operator[](u32 index) const
	{
		CE_ASSERT(index < _size, "Index out of bounds");
		return _data[index];
	}

	template <typename T> 
	inline Array<T>& Array<T>::operator=(const Array<T>&other)
	{
		const u32 size = other._size;
		array::resize(*this, size);
		memcpy(_data, other._data, sizeof(T)*size);
		return *this;
	}

}// namespace crown
