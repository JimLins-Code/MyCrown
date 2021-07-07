#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * thread thread.h
 *
 */
#include "core/types.h"

namespace crown
{

	typedef s32(*ThreadFunction)(void*data);

	struct Thread 
	{
		struct Private* _priv;
		CE_ALIGN_DECL(16, u8 _data[256]);

		//////////////////////////////////////////////////////////////////////////
		Thread();
		~Thread();

		// delete 2 copy construct fucns; because too many problems, make it sample~
		Thread(const Thread&) = delete;

		Thread& operator=(const Thread&) = delete;

		void start(ThreadFunction func, void* user_data = NULL, u32 stack_size = 0);

		void stop();

		bool is_running();

		s32 exit_code();

	};

}// namespace crown