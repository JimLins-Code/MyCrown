#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/containers/types.h"

namespace crown
{
	typedef Array<char> StringStream;

	namespace string_stream
	{
		const char* c_str(StringStream& ss);

		template <typename T> StringStream& stream_printf(StringStream& s, const char* format, T& val);

	}// namespace string_stream
}// namespace crown