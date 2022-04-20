#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 * crown platform.h
 *
 */

#define CROWN_COMPILER_CLANG 0
#define CROWN_COMPILER_GCC 0

#define CROWN_PLATFORM_ANDROID 0
#define CROWN_PLATFORM_IOS 0
#define CROWN_PLATFORM_LINUX 0
#define CROWN_PLATFORM_OSX 0
#define CROWN_PLATFORM_WINDOWS 0

#define CROWN_CPU_ARM 0
#define CROWN_CPU_JIT 0
#define CROWN_CPU_MIPS 0
#define CROWN_CPU_PPC 0
#define CROWN_CPU_X86 0

#define CROWN_ARCH_32BIT 0
#define CROWN_ARCH_64BIT 0

// 
#define CROWN_CPU_ENDIAN_BIG 0
#define CROWN_CPU_ENDIAN_LITTLE 0 

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
#if defined(_MSC_VER)
	#define CROWN_COMPILER_MSVC 1
#elif defined(__clang__)
	// clang defines __GNUC__
	#undef CROWN_COMPILER_CLANG
	#define CROWN_COMPILER_CLANG 1
#elif defined(__GNUC__)
	#undef CROWN_COMPILER_GCC
	#define CROWN_COMPILER_GCC 1
#else
	#error "CROWN_COMPILER_* is not defined!"
#endif

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
#if defined(_WIN32) || defined(_WIN64)
	#undef CROWN_PLATFORM_WINDOWS
	// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
	#if !defined(WINVER) && !defined(_WIN32_WINNT)
	// Windows 7 and above
		#define WINVER 0x0601
		#define _WIN32_WINNT 0x0601
	#endif // !defined(WINVER) && !defined(_WIN32_WINNT)
	#define CROWN_PLATFORM_WINDOWS 1
#elif defined(__ANDROID__)
	// Android compiler defines __linux__
	#undef CROWN_PLATFORM_ANDROID
	#define CROWN_PLATFORM_ANDROID 1
#elif defined(__linux__)
	#undef CROWN_PLATFORM_LINUX
	#define CROWN_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
	#undef CROWN_PLATFORM_IOS
	#define CROWN_PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
	#undef CROWN_PLATFORM_OSX
	#define CROWN_PLATFORM_OSX 1
#else
	#	error "CROWN_PLATFORM_* is not defined!"
#endif

#define CROWN_PLATFORM_POSIX (CROWN_PLATFORM_ANDROID \
							|| CROWN_PLATFORM_IOS \
							|| CROWN_PLATFORM_LINUX \
							|| CROWN_PLATFORM_OSX)