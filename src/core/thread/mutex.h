#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * thread semaphore.h
 *
 */
#include "core/types.h"

namespace crown
{
	struct Mutex 
	{
		struct Private* _priv;
		CE_ALIGN_DECL(16, u8 _data[64]);

		Mutex();

		~Mutex();

		Mutex& operator=(const Mutex&) = delete;

		void lock();
		
		void unlock();

		void* native_handle();

	};
}