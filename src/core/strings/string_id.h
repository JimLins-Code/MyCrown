#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/types.h"
#define STRING_ID32_BUF_LEN 9
#define STRING_ID64_BUF_LEN 17

namespace crown
{
	/// Hashed string.
	/// 
	/// @ingroup String
	struct StringId32
	{
		u32 _id;
		StringId32():_id(0){}
		StringId32(u32 idx): _id(idx){}
		/*
		*A constructor with a single non-default parameter (until C++11) that is declared without the function
		*specifier explicit is called a converting constructor.
		*forbid compiler do non-explicit transform. if you no reason to tell compiler do non-explict transform, 
		*use explicit
		*/
		explicit StringId32(const char* str);
		explicit StringId32(const char* str, u32 len);

		void hash(const char* str, u32 len);

		/// Parses the id from @a str.
		void parse(const char* str);

		///
		const char* to_string(char* buf, u32 len)const;

	};

	struct StringId64 
	{
		u64 _id;
		StringId64() : _id(0) {}
		StringId64(u64 idx): _id(idx){}
		/*
		*A constructor with a single non-default parameter (until C++11) that is declared without the function
		*specifier explicit is called a converting constructor.
		*forbid compiler do non-explicit transform. if you no reason to tell compiler do non-explict transform,
		*use explicit
		*/
		explicit StringId64(const char* str);
		explicit StringId64(const char* str, u32 len);

		void hash(const char* str, u32 len);

		void parse(const char* str);

		const char* to_string(char* buf, u32 len) const;
	};

}// namespace crown