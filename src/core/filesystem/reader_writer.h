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
	struct BinaryWriter
	{
		File& _file;

		BinaryWriter(File& file);

		void align(const u32 align);

		void write(const void* data, u32 size);

		template<typename T>
		void write(const T& data);

		template <typename T>
		void write_unaligned(const T& data);

		void skip(u32 bytes);
	};

	struct BinaryReader
	{
		File& _file;
		BinaryReader(File& file);

		void align(const u32 align);

		void read(void* data, u32 size);

		template <typename T>
		void read(T& data);

		template <typename T>
		void read_unaligned(T& data);

		void skip(u32 bytes);

	};


}// namespace crown