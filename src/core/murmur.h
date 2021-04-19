#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/types.h"

namespace crown
{
	u32 murmur32(const void* key, u32 len, u32 seed);
	u64 murmur64(const void* key, u32 len, u32 seed);
}// namespace crown