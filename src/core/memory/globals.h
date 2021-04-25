#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * memory globals.h
 *
 */

#include "core/memory/types.h"

namespace crown
{
	Allocator& default_allocator();
	Allocator& default_scratch_allocator();
	namespace memory_globals
	{
		/// constructs the initial default allocators.
		/// @note
		/// has to be called before anything else during the engine startup.
		void init();
		/// destroys the allocators created with memory_globals::init().
		/// @note
		/// should be the last call of the program.
		void shutdown();
	}//namespace memory_globals
}// namespace crown