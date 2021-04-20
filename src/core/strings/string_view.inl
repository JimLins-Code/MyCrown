#include "string_view.h"
#include "core/strings/string.inl"

namespace crown
{

	inline StringView::StringView()
		:_length(0)
		, _data(NULL)
	{
	}

	inline StringView::StringView(const char * str)
		:_length(strlen32(str))
		, _data(str)
	{
	}

	inline StringView::StringView(const char * str, u32 len)
		: _length(len)
		, _data(str)
	{
	}

	inline StringView & crown::StringView::operator=(const char * str)
	{
		// TODO: insert return statement here
		this->_length = strlen32(str);
		this->_data = str;
		return *this;
	}

	inline u32 StringView::length() const
	{
		return _length;
	}

	inline const char * StringView::data() const
	{
		return _data;
	}

	// operator
	inline bool operator==(const StringView& a, const char* str)
	{
		const u32 len = strlen32(str);
		return a._length == len && strncmp(a._data, str, len) == 0;
	}

	inline bool operator==(const StringView& a, const StringView& b)
	{
		return a._length == b._length&&strncmp(a._data, b._data, a._length);
	}

	inline bool operator!=(const StringView& a, const StringView& b)
	{
		return a._length != b._length || strncmp(a._data, b._data, a._length) != 0;
	}

	inline bool operator<(const StringView& a, const StringView& b)
	{
		const u32 len = std::min(a._length, b._length);
		const int cmp = strncmp(a._data, b._data, len);
		return cmp < 0 || (cmp == 0 && a._length < b._length);
	}

}