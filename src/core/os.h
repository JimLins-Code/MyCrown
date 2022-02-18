#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/containers/types.h"
#include "core/strings/types.h"
#include "core/types.h"

/*
*
*	 os means operating system. an access to systems
*
*/


namespace crown
{
	// Holds information about a file.
	// @ingroup OS
	struct Stat
	{
		enum FileType
		{
			REGULAR,
			DIRECTORY,
			NO_ENTRY
		} file_type;
		u64 size;
		u64 mtime;
	};

	// Result from os::delete_file() or os::delete_directory().
	// @ingroup OS
	struct DeleteResult
	{
		enum
		{
			SUCCESS,
			NO_ENTRY,
			UNKNOWN
		} error;
	};
	// Result from os::create_directory()
	// @ingroup OS
	struct CreateResult
	{
		enum 
		{
			SUCCESS,
			ALREADY_EXISTS,
			UNKNOWN
		} error;
	};
	// File access flags to be used with os::access().
	// @ingroup OS 
	struct AccessFlags
	{
		enum Enum
		{
			EXISTS = 0x0,
			EXECUTE = 0x1,
			WRITE = 0x2,
			READ = 0X4
		};
	};

	namespace os
	{
		// suspends execution for @ms milliseconds.
		void sleep(u32 ms);

		// opens the library at @path
		void* library_open(const char* path);

		// closes a @library previously opened by library_open.
		void library_close(void* library);

		// returns a pointer to the symbol @name in the given @library.
		void* library_symbol(void* library, const char* name);

		// logs the message @msg.
		void log(const char* msg);

#if  CROWN_PLATFORM_POSIX
		// returns information about @fd
		void stat(Stat& info, int fd);
#endif

		void stat(Stat& info, const char* path);

		DeleteResult delete_file(const char* path);

		CreateResult create_directory(const char* path);

		DeleteResult delete_directory(const char* path);

		void list_files(const char* path, Vector<DynamicString>& files);

		const char* getcwd(char* buf, u32 size);

		const char* getenv(const char* name);

		s32 access(const char* path, u32 flags);

	}// namespace os

}// namespace crown