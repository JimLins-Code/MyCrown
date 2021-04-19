#include "core/murmur.h"

namespace crown
{

	/*
	murmurhash2 算法实现。
	注意：此算法假设机器可以做如下操作不会导致奔溃：
	1，从任意地址读取4-bytes值不会导致成crash
	2，sizeof(int) = 4
	算法限制：
	1，
	2，
	*/
	u32 murmur32(const void * key, u32 len, u32 seed)
	{
		return u32();
	}

	u64 murmur64(const void * key, u32 len, u32 seed)
	{
		return u64();
	}

}