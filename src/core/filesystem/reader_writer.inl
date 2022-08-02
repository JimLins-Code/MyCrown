#pragma once
/*
 * Copyright (c) 2012-2030 @banlinhuo al.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 * Copy crown
 */

#include "core/filesystem/file.h"
#include "core/filesystem/reader_writer.h"

namespace crown
{
	/////////////////////////////////BinaryWriter////////////////////////////////////////

	inline BinaryWriter::BinaryWriter(File& file)
		: _file(file)
	{}

	inline void BinaryWriter::align(const u32 align)
	{
		const u32 mask = align - 1;
		const u32 pos = (_file.position() + mask) & ~mask;//计算align的下一个位置pos，pos是align对齐后下一个下入的位置
		const u32 pad = pos - _file.position();// 计算当前位置到下一个align后写入位置的差值；也就是因对齐后无用的内存（碎片）
		const char val = 0;
		// 碎片位置全部补齐0
		for (u32 ii = 0; ii < pad; ++ii)
			_file.write(&val, 1);
	}

	inline void BinaryWriter::write(const void* data, u32 size)
	{
		_file.write(data, size);
	}

	template <typename T>
	inline void BinaryWriter::write(const T& data)
	{
		align(alignof(T));
		_file.write(&data, sizeof(T));
	}

	template <typename T>
	inline void BinaryWriter::write_unaligned(const T& data)
	{
		_file.write(&data, sizeof(T));
	}

	inline void BinaryWriter::skip(u32 bytes)
	{
		_file.skip(bytes);
	}


	/////////////////////////////////BinaryReader////////////////////////////////////////


	inline BinaryReader::BinaryReader(File& file)
		: _file(file)
	{}

	inline void BinaryReader::align(const u32 align)
	{
		const u32 mask = align - 1;
		const u32 pos = (_file.position() + mask) & ~mask;
		const u32 pad = pos - _file.position();
		_file.skip(pad);
	}

	inline void BinaryReader::read(void* data, u32 size)
	{
		_file.read(data, size);
	}

	template <typename T> 
	inline void BinaryReader::read(T& data)
	{
		align(alignof(T));
		_file.read(data, sizeof(T));
	}


	template <typename T>
	inline void BinaryReader::read_unaligned(T& data)
	{
		_file.read(data,sizeof(T));
	}

	inline void BinaryReader::skip(u32 bytes)
	{
		_file.skip(bytes);
	}

}// namespace crown