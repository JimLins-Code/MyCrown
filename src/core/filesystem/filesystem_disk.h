#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/filesystem/filesystem.h"
#include "core/strings/dynamic_string.h"

namespace crown
{
	struct FilesystemDisk:public Filesystem 
	{
		Allocator* _allocator;
		DynamicString _prefix;

		FilesystemDisk(Allocator& a);

		void set_prefix(const char* prefix);

		File* open(const char* path, FileOpenMode::Enum mode);

		void close(File& file);

		Stat stat(const char* path);

		bool exists(const char* path);

		bool is_directory(const char* path);

		bool is_file(const char* path);

		u64 last_modified_time(const char* path);

		CreateResult create_directory(const char* path);

		DeleteResult delete_directory(const char* path);

		DeleteResult delete_file(const char* path);

		void list_files(const char* path, Vector<DynamicString>& files);

		void absolute_path(DynamicString& os_path, const char* path);

	};

}// namespace crown 