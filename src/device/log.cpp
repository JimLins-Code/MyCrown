#include "device/log.h"
#include "core/types.h"
#include "core/os.h"
#include <stdio.h>

namespace crown
{
	namespace log_internal
	{

		static void stdout_log(LogSeverity::Enum sev, System system, const char* msg)
		{
			char buf[8192];
#if  CROWN_PLATFORM_POSIX
			#define ANSI_RESET "\x1b[0m"
			#define ANSI_YELLOW "\x1b[33m"
			#define  ANSI_RED	"\x1b[31m"
			const char* stt[] = { ANSI_RESET,ANSI_YELLOW,ANSI_RED };
			CE_STATIC_ASSERT(countof(stt) == LogSeverity::COUNT);
			snprintf(buf, sizeof(buf),"%s%s: %s\n" ANSI_RESET,stt[sev],system.name,msg);
#endif
			snprintf(buf, sizeof(buf), "%s: %s\n", system.name, msg);
			os::log(buf);
		}

		void vlogx(LogSeverity::Enum sev, System system, const char * msg, va_list args)
		{
			char buf[8192];
			vsnprintf(buf, sizeof(buf), msg, args);

			stdout_log(sev, system, buf);
		}

		void logx(LogSeverity::Enum sev, System system, const char * msg, ...)
		{
			va_list args;
			va_start(args, msg);
			vlogx(sev, system, msg, args);
			va_end(args);
		}
	}
}// namespace crown
