#include "core/murmur.h"

namespace crown
{

	/*
	murmurhash2 �㷨ʵ�֡�
	ע�⣺���㷨����������������²������ᵼ�±�����
	1���������ַ��ȡ4-bytesֵ���ᵼ�³�crash
	2��sizeof(int) = 4
	�㷨���ƣ�
	1��
	2��
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