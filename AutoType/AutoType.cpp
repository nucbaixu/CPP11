// AutoType.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

double foo() { return 0; };

#define MAX1(a, b) ((a) > (b)) ? (a) : (b)

#define MAX2(a, b, max) { \
    auto _a = (a); \
    auto _b = (b); \
    max = (_a > _b) ? _a : _b; }



int main()
{
	
	auto x = foo();    // x的类型为double
	auto y = 1;        // y的类型为int
	struct m { int i; } str{0};
	auto str1 = str;  // str1的类型是struct m
	
	//auto z;           // 无法推导，无法通过编译
	//z = x;

	int m1 = MAX1(1 * 2 * 3 * 4, 5 + 6 + 7 + 8);
	cout << m1 << endl;  // 26
	
	int m2 = 0;
	MAX2(1 * 2 * 3 * 4, 5 + 6 + 7 + 8, m2);
	cout << m2 << endl;  // 26





    std::cout << "Hello World!\n";
}
