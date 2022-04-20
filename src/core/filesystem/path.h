#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/strings/types.h"

namespace crown
{
	namespace path
	{
		bool is_absolute(const char* path);

		bool is_relative(const char* path);

		bool is_root(const char* path);

		void join(DynamicString& path, const char* path_a, const char* path_b);

		const char* basename(const char* path);

		const char* extension(const char* path);

		bool has_trailing_separator(const char* path);

		void reduce(DynamicString& clean, const char* path);

	}// namespace path

}// namespace crown