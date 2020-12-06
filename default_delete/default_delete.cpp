#include <iostream>
using namespace std;

class Test
{
public:
	Test() = default;             // 声明时在函数末尾加上”= default”来显式地指示编译器去生成该函数的默认版本，这样就保证了类还是POD类型
	Test(int i) : data(i) {}      //声明带参数的构造函数，此时就不会生成默认构造函数，这样会导致类不再是POD类型

private:
	int data;
};

class Test2
{
public:
	Test2() = default;               // 显式指定缺省函数
	Test2(int i) : data(i) {}
	Test2(const Test2& t) = delete;  // 显式删除拷贝构造函数,需要禁止拷贝构造函数的使用

private:
	int data;
};


//f防止隐式转换
class Example
{
public:
	Example(int i) {}
	Example(char c) = delete;
};


int main()
{
	std::cout << std::is_pod<Test>::value << std::endl;  // 1
	
	Test2 objT1;
	//Test2 objT2(objT1); // 无法通过编译
	std::cout << std::is_pod<Test2>::value << std::endl;  // 0

	//Example e('a');
}