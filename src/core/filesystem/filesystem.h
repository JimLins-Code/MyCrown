#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include"core/containers/types.h"
#include"core/filesystem/types.h"
#include"core/os.h"
#include"core/strings/types.h"

namespace crown
{
	/// Provides a platform-independent way to access files and directories

	/// on the host filesystem.

	/// @ingroup Filesystem
	struct Filesystem
	{
		/// 
		Filesystem() {};

		virtual ~Filesystem() {};

		Filesystem& operator=(const Filesystem&) = delete;

		virtual File* open(const char* path, FileOpenMode::Enum mode) = 0;

		virtual void close(File& file) = 0;

		virtual Stat stat(const char* path) = 0;

		virtual bool exists(const char* path) = 0;

		virtual bool is_directory(const char* path) = 0;

		virtual bool is_file(const char* path) = 0;

		virtual u64 last_modified_time(const char* path) = 0;

		virtual CreateResult create_directory(const char* path) = 0;

		virtual DeleteResult delete_directory(const char* path) = 0;

		virtual DeleteResult delete_file(const char* path) = 0;

		virtual void list_files(const char* path, Vector<DynamicString>& files) = 0;

		virtual void absolute_path(DynamicString& os_path, const char* path) = 0;
	};
}