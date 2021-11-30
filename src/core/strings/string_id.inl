#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/functional.h"
#include "core/error/error.inl"
#include "core/murmur.h"
#include "core/strings/string.inl"
#include "core/strings/string_id.h"

namespace crown
{

	/*
		notes:
		sometimes, we need overide "operator=="
		there is two ways:
		��"operator==" is member of class. there will be like this: 
			bool operator==(const Myclass& other) const{}
			note that const to function
		��"operator==" is global function. there will be like this:
			bool operator==(const StringId32& a, const StringId32& b);
			define const to function is not necessary
			
	*/

	// StringId32
	inline bool operator==(const StringId32& a, const StringId32& b)
	{
		return a._id == b._id;
	}

	inline bool operator==(const StringId32& a, const u32 id)
	{
		return a._id == id;
	}

	inline bool operator!=(const StringId32& a, const StringId32& b)
	{
		return a._id != b._id;
	}

	inline bool operator<(const StringId32& a, StringId32& b)
	{
		return a._id < b._id;
	}

	// StringId64
	inline bool operator==(const StringId64& a, StringId64& b)
	{
		return a._id == b._id;
	}

	inline bool operator==(const StringId64& a, const u64 id)
	{
		return a._id == id;
	}

	inline bool operator!=(const StringId64& a, const StringId64& b)
	{
		return a._id != b._id;
	}

	inline bool operator<(const StringId64& a, const StringId64& b)
	{
		return a._id < b._id;
	}

	// templete
	template <>
	struct hash<StringId32> 
	{
		u32 operator()(const StringId32& id)const
		{
			return id._id;
		}
	};

	template <>
	struct hash<StringId64>
	{
		u32 operator()(const StringId64& id)const 
		{
			return (u32)id._id;
		}
	};

#if CROWN_DEBUG && !CROWN_DEVELOPMENT
	inline u32 STRING_ID_32(const char* str, const u32 id)
	{
		CE_ASSERT(murmur32(str, strlen32(str), 0) == id, "Hash mismatch");
		return id;
	}
	inline u64 STRING_ID_64(const char* str, const u64 id)
	{
		CE_ASSERT(murmur64(str, strlen32(str), 0) == id, "Hash mismatch");
		return id;
	}
#endif
}