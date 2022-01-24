#pragma once

/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * containers types define
 */

#include "core/functional.h"
#include "core/memory/types.h"
#include "core/pair.h"
#include "core/types.h"


namespace crown
{
	/*
	Dynamic array of POD items.

	POD¿ÌΩ‚£∫

	POD is Plian Old Data

	A Plain Old Data Structure in C++ is an aggregate class that contains only PODS as members,
	has no user-defined destructor, no user-defined copy assignment operator, 
	and no nonstatic members of pointer-to-member type.

	In short, it is all built-in data types (e.g. int, char, float, long, unsigned char, double, etc.) 
	and all aggregation of POD data. Yes, it's a recursive definition. ;)
	To be more clear, a POD is what we call "a struct": a unit or a group of units that just store data.


	cppreference:
	https://en.cppreference.com/w/cpp/types/is_pod

	about requirement:
	https://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special/7189821#7189821
	
	@note
	Does not call constructors/destructors, use memcpy to move stuff around.
	*/

	template <typename T>
	struct Array
	{
		ALLOCATOR_AWARE;
		Allocator* _allocator;
		u32 _capacity;
		u32 _size;
		T* _data;

		Array(Allocator& a);
		Array(const Array<T>& other);
		~Array();
		// operate Array index value
		T& operator[](u32 index);
		// get Array index value
		const T& operator[](u32 index) const;
		// copy Array
		Array<T>& operator=(const Array<T>& other);
	};
	typedef Array<char> Buffer;

	/*
	Dynamic array of objects.
	@note
	calls constructors and destructors.
	if your data is POD, use Array<T> instead.
	*/
	template<typename T>
	struct Vector
	{
		ALLOCATOR_AWARE;
		Allocator* _allocator;
		u32 _capacity;
		u32 _size;
		T* _data;
		Vector(Allocator& a);
		Vector(const Vector<T>& other);
		~Vector();
		T& operator[](u32 index);
		const T& operator[](u32 index)const;
		const Vector<T>& operator=(const Vector<T>& other);
	};


	template<typename TKey,typename TValue, typename Hash = hash<TKey>,typename KeyEqual = equal_to<TKey>>
	struct HashMap
	{
		ALLOCATOR_AWARE;
		typedef PAIR(TKey, TValue) Entry;
		struct Index
		{
			u32 hash;
			u32 index;
		};
		Allocator* _allocator;
		u32 _capacity;
		u32 _size;
		u32 _mask;
		Index* _index;
		Entry* _data;
		char* _buffer;

		HashMap(Allocator& a);
		HashMap(const HashMap& other);
		~HashMap();
		HashMap<TKey, TValue, Hash, KeyEqual>& operator=(const HashMap<TKey, TValue, Hash, KeyEqual>& other);
	};

}// namespace crown