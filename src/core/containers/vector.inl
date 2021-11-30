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
		:_allocator(&a)
		,_capacity(0)
		,_size(0)
		,_data(NULL)
	{
		const u32 size = vector::size(other);
		vector::resize(*this, size);
		for (u32 i = 0;i < size;++i)
		{
			new(&_data[i]) T(other._data[i])
		}
	}

	template<typename T>
	inline Vector<T>::~Vector()
	{
		for (u32 i = 0;i < _size;++i)
		{
			_data.[i].~T();
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