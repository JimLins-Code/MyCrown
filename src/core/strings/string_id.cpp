#include "core/strings/string_id.h"
#include "core/murmur.h"
#include "core/error/error.inl"
#include "core/strings/string.inl"
#include <inttypes.h> // PRIx64


crown::StringId32::StringId32(const char * str)
{
	hash(str, strlen32(str));
}

crown::StringId32::StringId32(const char * str, u32 len)
{
	hash(str, len);
}

void crown::StringId32::hash(const char * str, u32 len)
{
	CE_ENSURE(NULL != str);
	_id = murmur32(str, len, 0);
}

void crown::StringId32::parse(const char * str)
{
	CE_ENSURE(NULL != str);
	// 取8个字符转换成16进制数表示的整型变量。
	int num = sscanf(str, "%8x", &_id);
	CE_ENSURE(num == 1);
	CE_UNUSED(num);
}

const char * crown::StringId32::to_string(char * buf, u32 len) const
{
	// .8 表示精度，即取字符串前8个字符。x表示以16进制数写入buf
	snprintf(buf, len, "%.8x", _id);
	return buf;
}

crown::StringId64::StringId64(const char * str)
{
	hash(str, strlen32(str));
}

crown::StringId64::StringId64(const char * str, u32 len)
{
	hash(str, len);
}

void crown::StringId64::hash(const char * str, u32 len)
{
	CE_ENSURE(NULL != str);
	_id = murmur64(str, len, 0);
}

void crown::StringId64::parse(const char * str)
{
	u32 id[2];
	CE_ENSURE(NULL != str);
	int num = sscanf(str, "%8x%8x", &id[0], &id[1]);
	_id = u64(id[0]) << 32;
	_id |= u64(id[1]) << 0;
	CE_ENSURE(num == 2);
	CE_UNUSED(num);
}

const char * crown::StringId64::to_string(char * buf, u32 len) const
{
	snprintf(buf, len, "%.16" PRIx64, _id);
	return buf;
}
