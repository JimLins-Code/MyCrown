/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/containers/vector.inl"
#include "core/error/error.h"
#include "core/memory/temp_allocator.inl"
#include "core/os.h"
#include "core/platform.h"
#include "core/strings/dynamic_string.inl"
//#include "core/strings/string_stream.h"
// sys
#include <string.h> // for strcmp
#include <sys/stat.h> // for stat, mkdir
#if CROWN_PLATFORM_POSIX
	#include<dirent.h>
	#include<dlfcn.h>
	#include<errno.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<sys/wait.h>
	#include<time.h>
	#include<unistd.h>
#elif CROWN_PLATFORM_WINDOWS
	#include<io.h>			// for _access
	#include<stdio.h>
	#include<windows.h>
#endif

#if CROWN_PLATFORM_ANDROID
	#include <android/log.h>
#endif


namespace crown
{
	namespace os
	{
		void sleep(u32 ms)
		{
#if CROWN_PLATFORM_POSIX
			usleep(ms * 1000);
#elif CROWN_PLATFORM_WINDOWS
			Sleep(ms);
#endif
		}

		void* library_open(const char* path)
		{
#if CROWN_PLATFORM_POSIX
			return ::dlopen(path,RTLD_LAZY);
#elif CROWN_PLATFORM_WINDOWS
			// path encode by ansi
			return (void*)LoadLibraryA(path);
#endif
		}

		void library_close(void* library)
		{
#if CROWN_PLATFORM_POSIX
			dlclose(library);
#elif CROWN_PLATFORM_WINDOWS
			FreeLibrary((HMODULE)library);
#endif
		}
		void* library_symbol(void* library, const char* name)
		{
#if CROWN_PLATFORM_POSIX
			return ::dlsym(library, name);
#elif CROWN_PLATFORM_WINDOWS
			return (void*)GetProcAddress(HMODULE(library), name);
#endif
		}

		void log(const char * msg)
		{
#if CROWN_PLATFORM_ANDROID
			__android_log_write(ANDROID_LOG_DEBUG, "crown", msg);
#else
			fputs(msg, stdout);
			fflush(stdout);
#endif
#if CROWN_PLATFORM_WINDOWS
			OutputDebugStringA(msg);
#endif

		}
#if CROWN_PLATFORM_POSIX
		void stat(Stat & info, int fd)
		{
		}
#endif
		void stat(Stat & info, const char * path)
		{
			info.file_type = Stat::NO_ENTRY;
			info.size = 0;
			info.mtime = 0;
#if CROWN_PLATFORM_POSIX
			struct stat buf;
			memset(&buf, 0, sizeof(buf));
			int err = ::stat(path, &buf);
			if (err != 0)
				return;

			if (S_ISREG(buf.st_mode) == 1)
				info.file_type = Stat::REGULAR;
			else if (S_ISDIR(buf.st_mode) == 1)
				info.file_type = Stat::DIRECTORY;
#elif CROWN_PLATFORM_WINDOWS
			struct _stat64 buf;
			int err = ::_stat64(path, &buf);
			if (err != 0)
				return;
			if ((buf.st_mode & _S_IFREG) != 0)
				info.file_type = Stat::REGULAR;
			else if ((buf.st_mode&_S_IFDIR) != 0)
				info.file_type = Stat::DIRECTORY;
#endif
			info.size = buf.st_size;
			info.mtime = buf.st_mtime;
		}

		DeleteResult delete_file(const char * path)
		{
			return DeleteResult();
		}

		CreateResult create_directory(const char * path)
		{
			CreateResult cr;
#if CROWN_PLATFORM_POSIX
			if (::mkdir(path, 0755) == 0)//0755 what???
				cr.error = CreateResult::SUCCESS;
			else if (errno == EEXIST)
				cr.error = CreateResult::ALREADY_EXISTS;
			else
				cr.error = CreateResult::UNKNOWN;
#elif CROWN_PLATFORM_WINDOWS
			if (CreateDirectoryA(path, NULL) != 0)
				cr.error = CreateResult::SUCCESS;
			else if (GetLastError() == ERROR_ALREADY_EXISTS)
				cr.error = CreateResult::ALREADY_EXISTS;
			else
				cr.error = CreateResult::UNKNOWN;
#endif
			return cr;
		}

		DeleteResult delete_directory(const char * path)
		{
			DeleteResult dr;
#if  CROWN_PLATFORM_POSIX
			if (::unlink(path) == 0)
				dr.error = DeleteResult::SUCCESS;
			else if (errno == ENOENT)
				dr.error = DeleteResult::NO_ENTRY;
			else
				dr.error = DeleteResult::UNKNOWN;
#elif CROWN_PLATFORM_WINDOWS
			if (RemoveDirectoryA(path) != 0)
				dr.error = DeleteResult::SUCCESS;
			else if (GetLastError() == ERROR_FILE_NOT_FOUND)
				dr.error = DeleteResult::NO_ENTRY;
			else
				dr.error = DeleteResult::UNKNOWN;
#endif
			return dr;
		}

		void list_files(const char * path, Vector<DynamicString>& files)
		{
#if CROWN_PLATFORM_POSIX
			struct dirent *entry;
			DIR *dir = opendir(path);
			if (dir != NULL)
			{
				while ((entry = readdir(dir)))
				{
					const char* dname = entry->d_name;

					if (!strcmp(dname, ".") || !strcmp(dname, ".."))
						continue;

					TempAllocator256 ta;
					DynamicString fname(ta);
					fname.set(dname, strlen32(dname));
					vector::push_back(files, fname);
				}

				closedir(dir);
			}
#elif CROWN_PLATFORM_WINDOWS
			TempAllocator256 ta_path;
			DynamicString cur_path(ta_path);
			cur_path += path;
			cur_path += "\\*";
			WIN32_FIND_DATAA ffd;
			HANDLE file = FindFirstFileA(cur_path.c_str(), &ffd);
			if (file != INVALID_HANDLE_VALUE)
			{
				do 
				{
					const char* dname = ffd.cFileName;
					if(!strcmp(dname,".") || !strcmp(dname,".."))
						continue;

					TempAllocator256 ta;
					DynamicString fname(ta);
					fname.set(dname, strlen32(dname));
					vector::push_back(files, fname);
				} while (FindNextFileA(file,&ffd)!=0);
				FindClose(file);
			}
#endif
		}

		const char * getcwd(char * buf, u32 size)
		{
#if CROWN_PLATFORM_POSIX
			return ::getcwd(buf, size);
#elif CROWN_PLATFORM_WINDOWS
			GetCurrentDirectoryA(size, buf);
			return buf;
#endif
		}

		const char * getenv(const char * name)
		{
#if CROWN_PLATFORM_POSIX
			return ::getenv(name);
#elif CROWN_PLATFORM_WINDOWS
			//GetEnvironmentVariableA(name, buf, size);
			return NULL;
#endif
		}

		s32 access(const char * path, u32 flags)
		{
#if CROWN_PLATFORM_POSIX
			return ::access(path, flags);
#elif CROWN_PLATFORM_WINDOWS
			return ::_access(path, flags == AccessFlags::EXECUTE ? AccessFlags::EXISTS : flags);
#endif
		}
	}// namespace os
}// namespace crown