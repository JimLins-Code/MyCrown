#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/containers/types.h"
#include "core/strings/string_id.h"
#include "core/strings/string_view.h"
#include "core/strings/types.h"

namespace crown
{
	/// Hashed string
	/// Dynamic array of characters.
	/// 
	/// @ingroup String

	struct DynamicString 
	{
		ALLOCATOR_AWARE;

		Array<char> _data;

		DynamicString(Allocator& a);
		~DynamicString();

		DynamicString& operator=(const char* str);
		DynamicString& operator=(const char c);
		DynamicString& operator=(const StringView& fs);

		void set(const char* str, u32 len);

		void from_guid(const Guid& guid);

		void from_string_id(const StringId32& id);
		void from_string_id(const StringId64& id);

		void reserve(u32 n);

		u32 length()const;

		bool empty()const;

		void ltrim();
		void rtrim();
		void trim();

		bool has_prefix(const char* prefix)const;
		bool has_suffix(const char* suffix)const;

		StringId32 to_string_id()const;

		const char* c_str()const;
	};
	
}// namespace crown