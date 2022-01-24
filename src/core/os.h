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
	struct DeleteRusult
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



}// namespace crown