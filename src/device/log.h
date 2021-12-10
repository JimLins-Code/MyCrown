#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include<stdarg.h>

namespace crown
{
	struct LogSeverity
	{
		enum Enum
		{
			LOG_INFO,
			LOG_WARN,
			LOG_ERROR,
			COUNT
		};
	};
	namespace log_internal
	{
		struct System 
		{
			const char* name;
		};

		void vlogx(LogSeverity::Enum sev, System system, const char* msg, va_list args);
		void logx(LogSeverity::Enum sev, System system, const char* msg, ...);

	}// namespace log_internal
}// namespace crown