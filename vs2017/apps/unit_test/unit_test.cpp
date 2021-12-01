// unit_test_memory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "core/memory/allocator.h"
#include "core/memory/globals.h"
#include "core/error/error.inl"
#include "core/strings/string_view.inl"
#include "core/strings/string_id.h"
#include "core/strings/string_id.inl"
#include "core/thread/thread.h"
#include "core/containers/array.inl"
#include "core/containers/vector.inl"


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

static void test_string_id()
{
	memory_globals::init();

	{
		StringId32 a("murmur32");
		ENSURE(a._id == 0x7c2365dbu);

		StringId32 b("murmur32", 8);
		ENSURE(b._id == 0x7c2365dbu);

		char str[9];
		a.to_string(str, sizeof(str));
		ENSURE(strcmp(str, "7c2365db") == 0);
	}
	{
		// 任意一个字符串都会返回一个固有_id
		StringId64 a("murmur64");
		ENSURE(a._id == 0x90631502d1a3432bu);
		StringId64 b("murmur64", 8);
		ENSURE(b._id == 0x90631502d1a3432bu);
		char str[17];
		a.to_string(str, sizeof(str));
		ENSURE(strcmp(str, "90631502d1a3432b") == 0);
	}

	{
		StringId32 id(0x2dd65fa6u);
		char str[9];
		id.to_string(str, sizeof(str));
		StringId32 parsed;
		parsed.parse(str);
		ENSURE(id == parsed);
	}

	{
		StringId64 id(0xa73491922dd65fa6u);
		char str[17];
		id.to_string(str, strlen32(str));
		StringId64 parsed;
		parsed.parse(str);
		ENSURE(id == parsed);
	}

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
		ENSURE(sv2 < sv1);
	}
	{
		StringView sv1("foo");
		StringView sv2("fooo");
		ENSURE(sv1 < sv2);
	}
	memory_globals::shutdown();
}


static void test_thread()
{
	Thread thread;
	ENSURE(!thread.is_running());
	thread.start([](void*) {return 0xbadc0d3;},NULL);
	thread.stop();
	ENSURE(thread.exit_code() == 0xbadc0d3);
}

static void test_array()
{
	memory_globals::init();
	Allocator& a = default_allocator();
	{
		Array<int> v(a);
		ENSURE(array::size(v) == 0);
		array::push_back(v,10);
		ENSURE(array::size(v) == 1);
		ENSURE(v[0] == 10);
		int arr[] = {1,2,3,4,5};
		int _size = sizeof(arr) / sizeof(int);
		array::push(v, arr, _size);
 		ENSURE(array::size(v) == 6);
		ENSURE(v[3] == 3);
	}
	memory_globals::shutdown();
}

static void test_vector()
{
	memory_globals::init();
	Allocator& a = default_allocator();
	{
		Vector<int> v(a);
		ENSURE(vector::size(v) == 0);
		vector::push_back(v, 2);
		ENSURE(vector::size(v) == 1);
		int arr[] = { 10,20,30,40 };
		int _size = sizeof(arr) / sizeof(int);
		vector::push(v, arr, _size);
		ENSURE(vector::size(v) == 5);
		ENSURE(v[3] == 30);
	}
	memory_globals::shutdown();
}



#define RUN_TEST(name)		\
	do{						\
		printf(#name "\n");	\
		name();				\
	}while(0)				\



int main()
{
	//char testhere[6] = { 0x31,0x38,0x34,0x32,0x36,0x33 };
	char testhere[8] = { '1','8','4','2','6','3','1','8' };
	unsigned int a[3];
	unsigned int r;
	int result = 0;
	result = sscanf_s(testhere, "%2x%2x%2x", &a[0], &a[1], &a[2]);
	result =  sscanf_s(testhere, "%8x", &r);
	std::cout << a[0] << std::endl;
	std::cout << a[1] << std::endl;
	std::cout << a[2] << std::endl;

	RUN_TEST(test_memory);
	RUN_TEST(test_string_view);
	RUN_TEST(test_string_id);
	//RUN_TEST(test_thread); //crash need to check
	RUN_TEST(test_array);
	RUN_TEST(test_vector);


	system("pause");
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
