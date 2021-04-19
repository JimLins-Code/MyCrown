#include "core/strings/string_id.h"
#include "core/murmur.h"
#include "core/error/error.h"
#include "core/strings/string.inl"


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
	int num = sscanf(str, "%8x", &_id);
	CE_ENSURE(num == 1);
	CE_UNUSED(num);
}

const char * crown::StringId32::to_string(char * buf, u32 len) const
{
	snprintf(buf, len, "%.8x", _id);
	return buf;
}
