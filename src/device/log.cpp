#include "device/log.h"
#include "core/types.h"
#include <stdio.h>

namespace crown
{
	namespace log_internal
	{

		void vlogx(LogSeverity::Enum sev, System system, const char * msg, va_list args)
		{
			char buf[8192];
			snprintf(buf, sizeof(buf), "%s: %s\n", system.name, msg);
			//os::log(buf);
		}

		void logx(LogSeverity::Enum sev, System system, const char * msg, ...)
		{

		}
	}
}// namespace crown
