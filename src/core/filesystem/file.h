#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/filesystem/types.h"
#include "core/types.h"

namespace crown
{

	/// An abstraction to access data files.
	///
	/// @ingroup FileSystem
	struct File 
	{
		/// 
		File() {}
		virtual ~File() {}
		virtual void open(const char* path, FileOpenMode::Enum mode) = 0;
		virtual void close() = 0;
		virtual bool is_open() = 0;
		virtual u32 size() = 0;
		virtual u32 position() = 0;
		virtual bool end_of_file() = 0;
		virtual void seek(u32 position) = 0;
		virtual void seek_to_end() = 0;
		virtual void skip(u32 bytes) = 0;
		virtual u32 read(void* data, u32 size) = 0;
		virtual u32 write(const void* data, u32 size) = 0;
		// forces the previouses write operations to complete.
		virtual void flush() = 0;
	};

}// namespace crown