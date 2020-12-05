// literal.cpp : 用户自定义字面量
//

#include <iostream>
#include <stdio.h>

using namespace std;
typedef unsigned char uint8;

struct RGBA
{
	uint8 r;
	uint8 g;
	uint8 b;
	uint8 a;
	
	RGBA(uint8 R, uint8 G, uint8 B, uint8 A = 0)
		: r(R), g(G), b(B), a(A)
	{}
};

ostream & operator<<(ostream& out, RGBA& col)
{
	return out << "r: " << (int)col.r
		<< ", g: " << (int)col.g
		<< ", b: " << (int)col.b
		<< ", a: " << (int)col.a << endl;
}

void blend(RGBA& col1, RGBA& col2)
{
	cout << "blend " << endl << col1 << col2 << endl;
}

void blend(RGBA && col1, RGBA && col2)
{
	cout << "blend " << endl << col1 << col2 << endl;
}


RGBA operator "" _C(const char* col, size_t n)
{
	std::cout << col << n << endl;
	const char* p = col;
	const char* end = col + n;
	const char* r, *g, *b, *a;
	r = g = b = a = nullptr;
	for (; p != end; ++p)
	{
		if (*p == 'r') r = p;
		else if (*p == 'g') g = p;
		else if (*p == 'b') b = p;
		else if (*p == 'a') a = p;
	}
	if ((nullptr == r) || (nullptr == g) || (nullptr == b))
	{
		throw;
	}
	else if (nullptr == a)
		return RGBA(atoi(r + 1), atoi(g + 1), atoi(b + 1));
	else
		return RGBA(atoi(r + 1), atoi(g + 1), atoi(b + 1), atoi(a + 1));
}


// 浮点数操作符
long double operator"" _mm(long double x) { return x / 1000; }
long double operator"" _m(long double x) { return x; }
long double operator"" _km(long double x) { return x * 1000; }

// 字符串操作符，第二个参数会自动推断为字符串的长度
size_t operator"" _len(char const*, size_t n)
{
	return n;
}

// 原始字面量操作符1
char const* operator"" __r(char const* s)
{
	return s;
}

// 原始字面量操作符2
string operator"" __rs(char const* s)
{
	return 'x' + string(s) + 'y';
}


int main()
{
	RGBA col1(255, 240, 155);
	RGBA col2({ 15, 255, 10, 7 });
	//在程序中想通过blend函数对两个确定的RGBA对象进行运算。采用了传统的方式，即先声明两个RGBA的变量，并且赋予相应初值，再将其传给函数blend
	//这无疑是比较麻烦的
	blend(col1, col2);

	blend("r255 g240 b155"_C, "r15 g255 b10 a7"_C);


	cout << 1.0_mm << '\n';  // 0.001
	cout << 1.0_m << '\n';   // 1
	cout << 1.0_km << '\n';  // 1000

	cout << "ABCDEFGH"_len << '\n'; // 8

	cout << 12__r << '\n'; // 12
	std::string t = 5__rs;

	cout << t.c_str() << '\n'; // x5y

	system("pause");
}

