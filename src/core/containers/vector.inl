#pragma once

#include "core/containers/types.h"
#include "core/error/error.h"
#include "core/memory/allocator.h"
#include "core/memory/memory.inl"


namespace crown
{
	namespace vector
	{
		template <typename T>
		bool empty(const Vector<T>& v);

		template <typename T>
		u32 size(const Vector<T>& v);


		template <typename T>
		inline u32 capacity(const Vector<T>& v);

		template <typename T>
		inline void resize(Vector<T>& v, u32 size);

		template <typename T>
		inline void set_capacity(Vector<T>& v, u32 capacity);

		template <typename T>
		inline void reserve(Vector<T>& v, u32 capacity);

		template <typename T>
		inline void grow(Vector<T>&v, u32 min_capacity);

		template <typename T> 
		inline void condense(Vector<T>& v);

		template <typename T>
		inline u32 push_back(Vector<T>&v, const T& item);

		template <typename T>
		inline void pop_back(Vector<T>&v);

		template <typename T>
		inline u32 push(Vector<T>& v, const T* items, u32 count);

		template <typename T>
		inline void clear(Vector<T>& v);

		template <typename T>
		inline T* begin(const Vector<T>&v);

		template <typename T>
		inline T* begin(Vector<T>&v);

		template <typename T>
		inline T* end(const Vector<T>&v);

		template <typename T>
		inline T* end(Vector<T>& v);

		template <typename T>
		inline T& front(Vector<T>& v);

		template <typename T>
		inline T& front(const Vector<T>& v);

		template <typename T>
		inline T& back(const Vector<T>& v);

		template <typename T>
		inline T& back(Vector<T>& v);

	}

	// implement
	namespace vector
	{
		template<typename T>
		inline bool empty(const Vector<T>& v)
		{
			return v._size == 0;
		}

		template<typename T> 
		u32 size(const Vector<T>& v)
		{
			return v._size;
		}

		template<typename T>
		u32 capacity(const Vector<T>& v)
		{
			return v._capacity;
		}

		template<typename T>
		void resize(Vector<T>& v, u32 size)
		{
			if (size > v._capacity)
				set_capacity(v, size);
			v._size = size;
		}

		template<typename T>
		void set_capacity(Vector<T>& v, u32 capacity)
		{
			if (capacity == v._capacity)
				return;
			if (capacity < v._size)
				resize(v, capacity);
			if (capacity > 0)
			{
				T* tmp = v._data;
				v._capacity = capacity;
				v._data = (T*)v._allocator->allocate(capacity * sizeof(T), alignof(T));
				for (u32 i = 0; i< v._size;++i)
					new(&v._data[i]) T(tmp[i]);
				for (u32 i = 0; i < v._size; ++i)
					tmp[i].~T();
				v._allocator->deallocate(tmp);
			}	
		}

		template<typename T>
		void reserve(Vector<T>& v, u32 capacity)
		{
			if (capacity > v._capacity)
				grow(v, capacity);
		}

		template<typename T>
		void grow(Vector<T>& v, u32 min_capacity)
		{
			u32 new_capacity = v._capacity * 2 + 1;
			if (new_capacity < min_capacity)
				new_capacity = min_capacity;
			set_capacity(v, new_capacity);
		}

		template<typename T>
		void condense(Vector<T>& v)
		{
			resize(v, v._size);
		}

		template<typename T>
		u32 push_back(Vector<T>& v, const T & item)
		{
			if (v._capacity == v._size)
				grow(v, 0);
			construct<T>(v._data + v._size, *v._allocator, IS_ALLOCATOR_AWARE_TYPE(T)());
			v._data[v._size] = item;
			return v._size++;
		}

		template<typename T>
		void pop_back(Vector<T>& v)
		{
			CE_ASSERT(v._size > 0, "the vector is empty");
			v._data[v._size - 1].~T();
			--v._size;
		}

		template<typename T>
		u32 push(Vector<T>& v, const T * items, u32 count)
		{
			if (v._capacity <= v._size + count)
				grow(v, v._size + count);
			T* arr = &v._data[v._size];
			for (u32 i = 0; i < count; ++i)
				arr[i] = items[i];
			v._size += count;
			return v._size;
		}

		template<typename T>
		void clear(Vector<T>& v)
		{
			for (u32 i = 0; i < v._size; i++)
				v._data[i].~T();
			v._size = 0;
		}

		template<typename T>
		T * begin(const Vector<T>& v)
		{
			return v._data;
		}

		template<typename T>
		T* begin(Vector<T>&v)
		{
			return v._data;
		}

		template<typename T>
		T * end(const Vector<T>& v)
		{
			return v._data + v._size;
		}

		template<typename T>
		T & front(Vector<T>& v)
		{
			// TODO: insert return statement here
			CE_ASSERT(v._size > 0, "The vector is empty");
			return v._data[0];
		}

		template<typename T>
		T & front(const Vector<T>& v)
		{
			// TODO: insert return statement here
			CE_ASSERT(v._size > 0, "The vector is empty");
			return v._data[0];
		}

		template<typename T>
		T & back(const Vector<T>& v)
		{
			// TODO: insert return statement here
			CE_ASSERT(v._size > 0, "The vector is empty");
			return v._data[v.size - 1];
		}

		template<typename T>
		T & back(Vector<T>& v)
		{
			// TODO: insert return statement here
			CE_ASSERT(v._size > 0, "The vector is empty");
			return v._data[v.size - 1];
		}
	}


	template <typename T>
	inline Vector<T>::Vector(Allocator& a)
		:_allocator(&a)
		, _capacity(0)
		, _size(0)
		, _data(NULL)
	{}

	template<typename T>
	inline Vector<T>::Vector(const Vector<T>&other)
		:_allocator(other._allocator)
		,_capacity(0)
		,_size(0)
		,_data(NULL)
	{
		const u32 size = vector::size(other);
		vector::resize(*this, size);
		for (u32 i = 0;i < size;++i)
		{
			new(&_data[i]) T(other._data[i]);
		}
	}

	template<typename T>
	inline Vector<T>::~Vector()
	{
		for (u32 i = 0;i < _size;++i)
		{
			_data[i].~T();
		}
		_allocator->deallocate(_data);
	}

	template<typename T>
	inline T& Vector<T>::operator[](u32 index) 
	{
		CE_ASSERT(index < _size, "Index out of bounds");
		return _data[index];
	}

	template<typename T>
	inline const T& Vector<T>::operator[](u32 index)const
	{
		CE_ASSERT(index < _size, "Index out of bounds");
		return _data[index];
	}

	template<typename T>
	inline const Vector<T>& Vector<T>::operator=(const Vector<T>& other)
	{
		const u32 size = vector::size(other);
		vector::resize(*this, size);
		for (u32 i = 0; i < size; ++i)
		{
			construct<T>(_data + i, *_allocator, IS_ALLOCATOR_AWARE_TYPE(T)());
			_data[i] = other._data[i];
		}
		return *this;
	}

}// namespace crown