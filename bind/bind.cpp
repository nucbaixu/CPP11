#include <iostream>
#include <functional>

int TestFunc(int a, char c, float f)
{
	std::cout << a << std::endl;
	std::cout << c << std::endl;
	std::cout << f << std::endl;
	return a;
}

class TestClass
{
public:
	int ClassMember(int a) { return 55 + a; }
	int ClassMember2(int a, char ch, float f)
	{
		std::cout << ch << " " << f << " " << a << std::endl;
		return 55 + a;
	}
	static int StaticMember(int a) { return 66 + a; }
};


class TestClass2
{
public:
	TestClass2()
		:m_a(100)
	{}
public:
	int m_a;
};


class TestClass3
{
public:
	TestClass3() = default;
	TestClass3(const TestClass3& obj)
	{
		std::cout << "TestClass3 copy construct." << std::endl;
	}
	void operator()(int a)
	{
		std::cout << a << std::endl;
	}
};

class TestClass4
{
public:
	TestClass4(int a) :m_a(a) {}
	TestClass4(const TestClass4& obj)
	{
		m_a = obj.m_a + 100;
		std::cout << "copy construct." << std::endl;
	}
	int ClassMember(int a) { std::cout << " this:" << this << " :" << &m_a << " " << m_a << std::endl; return 55 + a; }
	int ClassMember2(int a, char ch, float f)
	{
		std::cout << ch << " " << f << " " << a << std::endl;
		return 55 + a;
	}
	static int StaticMember(int a) { return 66 + a; }
public:
	int m_a;
};


int main()
{
	//普通绑定
	auto fun1 = std::bind(TestFunc, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	auto fun2 = std::bind(TestFunc, std::placeholders::_2, std::placeholders::_3, std::placeholders::_1);
	auto fun3 = std::bind(TestFunc, std::placeholders::_1, std::placeholders::_2, 98.77);


	fun1(30, 'C', 100.1);
	fun2(100.1, 30, 'C');
	fun3(30, 'C');

	//绑定成员函数
	TestClass test;
	auto fun4 = std::bind(&TestClass::ClassMember, test, std::placeholders::_1);
	fun4(4);

	auto fun5 = std::bind(&TestClass::ClassMember2, test, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	fun5(1, 'A', 3.1);

	auto fun6 = &TestClass::StaticMember;
	fun6(3);

	std::function<int(int)> fun7 = &TestClass::StaticMember;
	fun7(4);

	//绑定变量
	TestClass2 test2;
	auto fun8 = std::bind(&TestClass2::m_a, std::placeholders::_1);
	int var = fun8(test2);
	std::cout << var << std::endl;

	//绑定仿函数
	//这里多定义了一个拷贝构造函数，多验证了一个东西，即绑定时调用了拷贝构造
	//即用test3拷贝构造了一个新的对象，并绑定这个对象，所以fun9是新的对象，跟test3没关系了。
	//实际上其他的类成员函数也是一样的，拷贝构造完再绑定
	TestClass3 test3;
	auto fun9 = test3;
	fun9(2018);

	//验证通过拷贝构建新对像
	std::cout << "------" << std::endl;
	TestClass4 test4(67);
	std::cout << "&test " << &test4 << " " << test4.m_a << " &test4.m_a " << &test4.m_a << std::endl;
	auto fun10 = std::bind(&TestClass4::ClassMember, test4, std::placeholders::_1);
	fun10(4);
	fun10(4);
	std::cout << "------" << std::endl;

	//绑定静态成员函数就是直接绑定，没用拷贝构造
	std::cout << "-----" << std::endl;
	auto fun11 = &TestClass4::StaticMember;
	fun11(3);
	std::cout << "-----" << std::endl;

	//同样的，绑定成员对象也没有拷贝构造
	std::cout << "------" << std::endl;
	auto fun12 = std::bind(&TestClass4::m_a, std::placeholders::_1);
	std::cout << "TT:" << fun12(test4) << " " << test4.m_a << std::endl;
	std::cout << "------" << std::endl;

	//通过指针，取消拷贝构造
	//先定义一个对象，再利用std::function保存成员函数，在调用时候把test对象传进去即可，测试代码
	TestClass4 test5(67);
	std::cout << "############" << std::endl;
	std::function<int(TestClass4*, int)> fg = &TestClass4::ClassMember;
	fg(&test5, 5);
	std::cout << "#################" << std::endl;

	//通过引用保存，取消拷贝构造
	std::function<int(TestClass4&, int)> hj = &TestClass4::ClassMember;
	TestClass4 tt(8);
	std::cout << &tt << " " << &tt.m_a << std::endl;
	hj(tt, 45);

    std::cout << "Hello World!\n";
}

