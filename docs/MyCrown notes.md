## MyCrown notes



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

