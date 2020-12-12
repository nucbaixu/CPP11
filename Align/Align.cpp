#include <iostream>
#include <stdio.h>
using namespace std;
/////////////////////////////////////////内存大小测试/////////////////////////////////////////////

// g++空结构体的内存大小为1，需要分配1字节用于占位，C++编译器不允许对象为0长度，无法获取地址等
// gcc中为0
struct A1
{
};

struct A2
{
	;
};

struct A3
{
	char a;               // 1
	int b;                // 4
	unsigned short c;     // 2
	long d;               // 4
	unsigned long long e; // 8
	char f;               // 1
};
// A3大小为1+(3)+4+4+4+8+1+(7)=36，括号内是为了内存对齐加的padding大小

struct A4
{
	int b;
	char a;
	unsigned short c;
	long d;
	unsigned long long e;
	char f;
};
// A4大小为4+1+(1)+2+8+8+1+(7)=32

//pragma pack(n)
//alignment must be a power of two
#pragma pack(2) //指定按两字节对齐
struct B1
{
	char a;
	int b;
	unsigned short c;
	long d;
	unsigned long long e;
	char f;
};
// B1大小为1+(1)+4+2+8+8+1+(1)=26
#pragma pack() //取消指定对齐

#pragma pack(4)
struct B2
{
	char a;
	int b;
	unsigned short c;
	long d;
	unsigned long long e;
	char f;
};
// B2大小为1+(3)+4+2+(2)+8+8+1+(3)=32
#pragma pack()

#pragma pack(8)
struct B3
{
	char a;
	int b;
	unsigned short c;
	long d;
	unsigned long long e;
	char f;
};
// B3大小为1+(3)+4+2+(6)+8+8+1+(7)=40
#pragma pack()

#pragma pack(16)
struct B4
{
	char a;
	int b;
	unsigned short c;
	long d;
	unsigned long long e;
	char f;
};
// B4大小为1+(3)+4+2+(6)+8+8+1+(7)=40
#pragma pack()

class A
{
	int a;
	char d;
};

// 自定义的ColorVector，对齐到32byte的边界
struct alignas(32) ColorVector 
{
	double r;
	double g;
	double b;
	double a;
};

// 创建给定类型对象大小满足对齐要求的未初始化内存块，在一个内存对齐的缓冲区上创建对象
// C++11后可以这样操作
void align_cpp11_after()
{
	static std::aligned_storage<sizeof(A),
		alignof(A)>::type data;
	A *attr = new (&data) A;
}

// C++11之前
void align_cpp11_before()
{
	static char data[sizeof(void *) + sizeof(A)];
	const uintptr_t kAlign = sizeof(void *) - 1;
	char *align_ptr =
		reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(data + kAlign) & ~kAlign);
	A *attr = new (align_ptr) A;
}

struct alignas(64) Empty64 {};


template<class  T, std::size_t N>
class static_vector
{
	typename std::aligned_storage<sizeof(T), __alignof(T)>::type data[N];
	std::size_t m_size = 0;
public:

	//类似于vector的push_back，使用了变长模板参数
	//和placement new
	template<typename ...Args>
	void emplace_back(Args&&... args)
	{
		if (m_size >= N)
			throw std::bad_alloc{};
		new(data + m_size) T(std::forward<Args>(args)...);
		++m_size;
	}
	const T & operator[](std::size_t pos) const
	{
		const T *  ret = reinterpret_cast<const T*>(data + pos);
		return *ret;
	}
	~static_vector()
	{
		for (std::size_t pos = 0; pos < m_size; ++pos)
			reinterpret_cast<T*>(data + pos)->~T();
	}
};

int main()
{
	printf("sizeof(char):%2d...sizeof(int):%2d...sizeof(ushort):%2d...sizeof(long):%2d...sizeof(ulonglong):%2d\n\r",
		sizeof(char), sizeof(int), sizeof(unsigned short), sizeof(long), sizeof(unsigned long long));

	printf("sizeof(A1):%2d...sizeof(A2):%2d...sizeof(A3):%2d...sizeof(A4):%2d\n\r",
		sizeof(struct A1), sizeof(struct A2), sizeof(struct A3), sizeof(struct A4));

	printf("sizeof(B1):%2d...sizeof(B2):%2d...sizeof(B3):%2d...sizeof(B4):%2d\n\r",
		sizeof(struct B1), sizeof(struct B2), sizeof(struct B3), sizeof(struct B4));

	std::cout << offsetof(A3, a) << offsetof(A3, b) << offsetof(A3, c) << offsetof(A3, d) << offsetof(A3, e) << offsetof(A3, f) <<endl;;
	
	// 使用C++11中的alignof来查询ColorVector的对齐方式
	std::cout << alignof(A3) << endl;
	std::cout << alignof(B1) << endl;

	// 使用C++11中的alignof来查询ColorVector的对齐方式
	std::cout << __alignof(std::string) << std::endl;

	static_vector<std::string, 10> v1;
	v1.emplace_back(5, '*');
	v1.emplace_back(10, '*');

	//std::cout << v1[0] << '\n' << v1[1] << '\n';
	
	
	std::cout << "Hello World!\n";
}