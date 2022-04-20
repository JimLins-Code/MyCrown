#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

/// @defgroup FileSystem Filesystem
/// @ingroup Core

namespace crown
{
	struct File;
	struct FileMonitor;
	struct Filesystem;

	/// Enumerates file open modes.
	/// 
	/// @ingroup Filesystem
	struct FileOpenMode 
	{
		enum Enum
		{
			READ,
			WRITE
		};
	};

}// namespace crown