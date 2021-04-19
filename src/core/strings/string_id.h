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
		explicit StringId32(const char* str);
		explicit StringId32(const char* str, u32 len);

		void hash(const char* str, u32 len);

		/// Parses the id from @a str.
		void parse(const char* str);

		///
		const char* to_string(char* buf, u32 len)const;

	};
}// namespace crown