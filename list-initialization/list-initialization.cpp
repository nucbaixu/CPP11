// list-initialization.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <vector>
#include <iostream>
#include <string>
struct A
{
	int x;
	int y;
}a = { 1,2 };

struct B
{
	int x;
	int y;
	B(int, int) :x(0), y(0) {}
}b = { 123,321 };


class Foo
{
public:
	Foo(int) {}
private:
	Foo(const Foo &);
};

struct Foo1
{
	int x;
	int y;
	//Foo(int, int, double){}
protected:
	static double z;
};


struct Foo3
{
	int x;
	int y = 5;
	virtual void func() {}
private:
	int z;
public:
	Foo3(int i, int j, int k) :x(i), y(j), z(k) { std::cout << z << std::endl; }
};

struct Foo4
{
	int x;
	int y;
	int z;
	Foo4(std::initializer_list<int> list)
	{
		auto it = list.begin();
		x = *it++;
		y = *it++;
		z = *it++;
	}
};

class FooVec
{
public:
	std::vector<int> m_vec;
	FooVec(std::initializer_list<int> list)
	{
		for (auto it = list.begin(); it != list.end(); it++)
			m_vec.push_back(*it);
	}
};


int main()
{

	Foo a1(123);         //调用Foo(int)构造函数初始化
	Foo a2 = 123;        //error Foo的拷贝构造函数声明为私有的，该处的初始化方式是隐式调用Foo(int)构造函数生成一个临时的匿名对象，再调用拷贝构造函数完成初始化
	Foo a3 = { 123 };    //列表初始化
	Foo a4{ 123 };       //列表初始化
	int a5 = { 3 };
	int a6{ 3 };

	Foo1 fool1{ 12,12 };


	Foo3 foo33{ 123,456,789 };
	std::cout << foo33.x << " " << foo33.y;


	Foo4 foo1{ 123,456,789 };
	Foo4 foo2{ 123, 456 };
	Foo4 foo3{ 123 };
	Foo4 foo4{ 123, 456, 789,258 };

	using namespace std;
	
	cout << foo1.x << " " << foo1.y << " " << foo1.z << endl;
	cout << foo2.x << " " << foo2.y << " " << foo2.z << endl;
	cout << foo3.x << " " << foo3.y << " " << foo3.z << endl;
	cout << foo4.x << " " << foo4.y << " " << foo4.z << endl;


	FooVec foo1{ 1, 2, 3, 4, 5, 6 };
	FooVec foo2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };


    std::cout << "Hello World!\n";
}

