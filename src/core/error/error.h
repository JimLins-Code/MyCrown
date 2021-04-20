#pragma once

/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/types.h"

/// @defgroup Error Error
/// @ingroup Core
namespace crown
{
	/// Error management
	/// 
	/// @ingroup Error
	namespace error
	{
		void abort(const char* format, ...);
	}// namespace error

}// namespace crown
