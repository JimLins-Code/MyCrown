#pragma once
#include "core/error/error.h"
#include "core/types.h"
#include <ctype.h> // isspace
#include <stdarg.h>
#include <stdio.h> // sscanf,vsnprintf
#include <string.h> // strlen
#include <algorithm> // min, max

namespace crown
{
	inline s32 vsnprintf(char* str, size_t num, const char* format, va_list args)
	{
#if CROWN_COMPILER_MSVC
		s32 len = _vsnprintf_s(str, num, _TRUNCATE, format, args);
		return (len == 1) ? _vscprintf(format, args) : len;
#else
		return::vsnprintf(str, num, format, args);
#endif
	}

	inline u32 strlen32(const char* str)
	{
		return (u32)strlen(str);
	}

}// namespace crown

