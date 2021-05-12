// unit_test_memory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "core/memory/allocator.h"
#include "core/memory/globals.h"
#include "core/error/error.inl"
#include "core/strings/string_view.inl"


using namespace crown;

#define ENSURE(condition)                                \
	do                                                   \
	{                                                    \
		if (!(condition))                                \
		{                                                \
			printf("Assertion failed: '%s' in %s:%d\n\n" \
				, #condition                             \
				, __FILE__                               \
				, __LINE__                               \
				);                                       \
			exit(EXIT_FAILURE);                          \
		}                                                \
	}                                                    \
	while (0)


static void test_memory()
{
	std::cout << "memory test worlk!\n";
	memory_globals::init();
	Allocator& a = default_scratch_allocator();
	void* p = a.allocate(32);
	ENSURE(a.allocated_size(p) >= 32);
	void* q = a.allocate(64);
	ENSURE(a.allocated_size(q) >= 64);
	a.deallocate(q);
	a.deallocate(p);

	void* v = a.allocate(128);
	ENSURE(a.allocated_size(v) >= 128);
	a.deallocate(v);

	memory_globals::shutdown();
}


static void test_string_view()
{
	std::cout << "string_view test worlk!\n";
	memory_globals::init();
	{
		const char* str = "foo";
		StringView sv(str);
		ENSURE(sv.length() == 3);
		ENSURE(sv.data() == &str[0]);
	}
	{
		StringView sv1("foo");
		StringView sv2("foo");
		ENSURE(sv1 == sv2);
	}
	{
		StringView sv1("foo");
		StringView sv2("bar");
		ENSURE(sv1 != sv2);
	}
	{
		StringView sv1("foo");
		StringView sv2("bar");
		ENSURE(sv1 < sv2);
	}
	{
		StringView sv1("foo");
		StringView sv2("fooo");
		ENSURE(sv1 < sv2);
	}
	memory_globals::shutdown();
}



int main()
{
	test_memory();
	test_string_view();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
