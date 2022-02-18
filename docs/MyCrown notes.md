## MyCrown notes

### Crown结构（置顶）

 * memory

   HeapAllocator 

   ScratchAllocator 

 * containers struct

   * HashMap

   * Array

   * Vector

   * DynamicString

     implement by Array

 * threads

 * filesystem

   * os

     open/close files, create/delete directory, open/read files

	* error





#### 2022-1-24

crown robin hood hash

https://www.sebastiansylvan.com/post/robin-hood-hashing-should-be-your-default-hash-table-implementation/

Robin Hood hash,是一种基于开放寻址的hash算法的变体，相对std::unordermap（标准的链表实现方式），提高了空间利用率，也提高了查找效率。



### 2021-12-8

https://www.interviewcake.com/concept/java/hash-map

### Hash Table review:

#### 优点：

①快速查找。查询复杂度平均为O(1)

②灵活使用key。也就是可以使用任意类型的类型作为key

#### 缺点：

①查询最大复杂度为O(n)。

②存储无序。键值存储是无序的，插叙最大值、最小、范围值都需要遍历所有。

③单方向查询。通过key查询value，只需要O(1)；然而通过value查询key，则需要O(n)。

④缓存不友好。大部分的hash table实现都使用链表，导致数据并不连续。从计算机的寻址的角度来说cache并不友好。

### HashMap review:

①hashmap相对于table来说，cache是友好的。因为hashmap使用的是array来存储数据。

②快速理解：hashmap 是array的变体。这里的变体指的是：array使用index作为"key"，而map使用的"key"可以是任意数据类型；最终hashmap通过hashfunc也是把"key"转换成了index。所以说hashmap是array的变体，多了一层hashfunc转换。

![image-20220125114214484](images/MyCrown%20notes.assert/image-20220125114214484.png)



### 2021-11-25

* Plain Old Data(POD)

   https://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special/7189821#7189821

  * 保证编译后的数据内存结构保持C和C++一样。
  * 基础数据类型。没有继承、静态变量、用户自定义构造函数、析构函数、虚函数等影响到整个数据结构的操作。

  

### 2021-11-24

* .inl文件的使用意义（inline内联）

  https://stackoverflow.com/questions/1208028/significance-of-a-inl-file-in-c/1208062

### 2021-11-20

* 代码中通常会使用如下的宏来定义一个操作：

  ```c++
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
  ```

  明明是一个操作，为什么要写成do...while(0)?

  Google了一下do...while(0)，以下做一个记录：

  http://www.spongeliu.com/415.html

  [https://www.pixelstech.net/article/1390482950-do-%7B-%7D-while-%280%29-in-macros#:~:text=do%20%7B](https://www.pixelstech.net/article/1390482950-do-{-}-while-(0)-in-macros#:~:text=do {)

  个人理解比较中一点是：

  宏展开后，c/c++需要补充“;”作为结束符。这个结束符可能会导致if...else...宏展开有问题。

### 2021-05-24

CROWN_CPU_ENDIAN_BIG   和 CROWN_CPU_ENDIAN_LITTLE

* 在计算机系统中，以字节为单位，每一个地址单元对应一个字节，一字节 = 8bit

  但是在C语言中除了8bit的char之外，还有16bit的short型，32bit的int型。另外，对于位数大于8位的处理器，例如16位或者32位的处理器，由于寄存器宽度大于一个字节，那么必然存在着一个如果将多个字节安排的问题。因此就导致了大端存储模式和小端存储模式

  例如一个16bit的short型x，在内存中的地址为0x0010，x的值为0x1122，那么0x11为高字节，0x22为低字节。

  而对于大端模式，就将0x11放在低地址中，即0x0010中，0x22放在高地址中，即0x0011中。小端模式，刚好相反

![image-20210524193711025](images/MyCrown%20notes.assert/image-20210524193711025.png)

![image-20210524193921216](images/MyCrown%20notes.assert/image-20210524193921216.png)

---

### 2021-05-19

sscanf函数
对输入字符串做格式化输出；另一个相似函数：scanf，输入源是控制台。

```
1,例如："184263"字符串做为输入，把该字符串转换成16进制数组18，42，63
{
	//char testhere[6] = { 0x31,0x38,0x34,0x32,0x36,0x33 };//ascii码
	char testhere[6] = { '1','8','4','2','6','3' };
	unsigned int a[3];
	int result = 0;
	result =  sscanf_s(testhere, "%2x%2x%2x", &a[0], &a[1], &a[2]);
}
上述sscanf参数：取两个字符转换成16进制数给a[0],a[1],a[2]
输出:
	a[0] == 24
	a[1] == 66
	a[2] == 99
```

```
2,修改代码如下：
{
	char testhere[8] = { '1','8','4','2','6','3','1','8' };
	unsigned long long r;
	int result = 0;
	result =  sscanf_s(testhere, "%8x", &r);
	std::cout << a[0] << std::endl;
}
输出：
	r == 3435973836

```

```
3,修改testhere的长度
{
	char testhere[9] = { '1','8','4','2','6','3','1','8','9' };
}
输出：
	a[0] == 3435973836
```

### 说明 sscanf_s(testhere, "%8x", &r) 是读取8个字符转换成16进制数。

---

### 2021-05-11

ScratchAllocator由RingBuffer原理实现，维护了一个四个成员：

```
char* _begin;	// 整个ring buffer的起始地址
char* _end;		// 整个ring buffer的终止地址
char* _allocate; // 当前申请的ring buffer的位置，是一个移动指针。
char* _free;	// 当前已经回收的内存指针位置，也就是说，在_free之前、_begin之后的内存可以被重新使用。
```

以下对ring buffer的原理做如下分析：

![image-20210511210049052](images/MyCrown%20notes.assert/image-20210511210049052.png)

注：这里的设计遵循先入先出规则，如上代码：

```
a.deallocate(q);
a.deallocate(p);
q是后申请的内存，先执行deallocate操作，这样会直接跳过；
当a.deallocate(p)的时候,直接会把所有的内存标记为free；
所以使用内存的
```



### 2021-04-29

```
globals.cpp
// p:当前指向的指针
// p[-1]上一指针指向的值。while相当于逆向遍历内存
inline Header* header(const void* data)
{
	u32* p = (u32*)data;
	while(p[-1] == HEADER_PAD_VALUE)
	{
		--P;
	}
	return (Header*)p -1;
}
```

这里的写法比较巧妙，HEADER_PAD_VALUE其实针对align字节大小不等于4字节的时候，(因为#define HEADER_PAD_VALUE 0xffffffffu)。

### 2021-04-27

* 内存大小

  ```c++
  1 Byte = 8 Bits
  
  1 KB = 1024 Bytes
  
  1MB = 1024 KBs
  
  1G = 1024 MBs
  ```

* void*

  ```
  x64:
  	sizeof(void*) == 8 Byte
  x86:
  	sizeof(void*) == 4 Byte
  ```

  void* 是指针，可以指向任何指针。（除了函数地址，有些平台下函数的地址超过了void*大小能够指示的范围）。由编译器决定void* 的大小。

  C-FAQ:http://c-faq.com/ptrs/generic.html

  



---

### 2021-04-26

* memory的内存管理对象global.cpp的实现中用到了两个内存分配器

  1，HeapAllocator:基于标准C的接口malloc()实现。

  2，ScratchAllocator:实现一个Ring Buffer,用于维护一段环形内存，其实相当于一个memory manager，正真申请内存的是_backing（HeapAllocator）

* Ring Buffer 的实现原理？

* const u32 HEADER_PAD_VALUE = 0xffffffffu；32位无符号整数。即2^32 = 4294967295

  ```c++
  /*
      从给定的data中找到这段内存对应的header
      while (p[-1] == HEADER_PAD_VALUE)
      {
      	--p;
      }
      p[-1]返回当前地址的上一字节内容，while的结构相当于逆向遍历指针
  */
  ```

  

---

### 2021-04-19

* murmur hash2算法的实现原理？
* .inl文件实现的必要性？
* 

