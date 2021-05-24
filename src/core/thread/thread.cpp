#include "core/thread/thread.h"

#include "core/error/error.inl"
#include "core/platform.h"
//#include "core/thread/semaphore.h"

#include <new>

namespace crown {


	Thread::Thread()
	{
	}

	Thread::~Thread()
	{
	}

	void Thread::start(ThreadFunction func, void * user_data, u32 stack_size)
	{
	}

	void Thread::stop()
	{
	}

	bool Thread::is_running()
	{
		return false;
	}

	s32 Thread::exit_code()
	{
		return s32();
	}

}// namespace crown