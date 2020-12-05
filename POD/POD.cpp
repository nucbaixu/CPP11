#include <type_traits>
#include <iostream>
using namespace std;

/******************************************************
 @ function : 	POD类型需要满足平凡条件
				[1] 有平凡的构造函数
				[2] 有平凡的拷贝构造函数
				[3] 有平凡的移动构造函数
				[4] 有平凡的拷贝赋值运算符
				[5] 有平凡的移动赋值运算符
				[6] 有平凡的析构函数
				[7] 不能包含虚函数
				[8] 不能包含虚基类
 @ Access 	:	
 @ Parameter:	
 @ Returns  :	
 @ Remarks 	:   
 @ author   :   
******************************************************/
class A { A() {} };
class B { B(B&) {} };
class C { C(C&&) {} };
class D { D operator=(D&) {} };
class E { E operator=(E&&) {} };
class F { ~F() {} };
class G { virtual void foo() = 0; };
class H : G {};
class I {};


//POD需要满足标准布局
namespace stand {
	class A
	{
	private:
		int a;
	public:
		int b;
	};

	class B1
	{
		static int x1;
	};

	class B2
	{
		int x2;
	};

	class B : B1, B2
	{
		int x;
	};

	class C1 {};
	class C : C1
	{
		C1 c;
	};

	class D { virtual void foo() = 0; };
	class E : D {};
	class F { A x; };
}

/******************************************************
 @ function : 	POD类型的应用
 @ Access 	:	
 @ Parameter:	
 @ Returns  :	
 @ Remarks 	:   
 @ author   :   
******************************************************/
class PODType
{
public:
	int x;
	double y;
};


int main()
{
	//一个对象是普通、标准布局还是POD类型，可以根据标准库函数模板来判断
	cout << is_trivial<int>::value << endl;          // 1
	cout << is_standard_layout<int>::value << endl;  // 1
	cout << is_pod<int>::value << endl;              // 1


	//是否满足平凡条件
	std::cout << std::is_trivial<A>::value << std::endl;  // 有不平凡的构造函数
	std::cout << std::is_trivial<B>::value << std::endl;  // 有不平凡的拷贝构造函数
	std::cout << std::is_trivial<C>::value << std::endl;  // 有不平凡的拷贝赋值运算符
	std::cout << std::is_trivial<D>::value << std::endl;  // 有不平凡的拷贝赋值运算符
	std::cout << std::is_trivial<E>::value << std::endl;  // 有不平凡的移动赋值运算符
	std::cout << std::is_trivial<F>::value << std::endl;  // 有不平凡的析构函数
	std::cout << std::is_trivial<G>::value << std::endl;  // 有虚函数
	std::cout << std::is_trivial<H>::value << std::endl;  // 有虚基类
	std::cout << std::is_trivial<I>::value << std::endl;  // 平凡的类

	//判断是否满足标准布局
	std::cout << std::is_standard_layout<stand::A>::value << std::endl;  // 违反定义1：成员a和b具有不同的访问权限
	std::cout << std::is_standard_layout<stand::B>::value << std::endl;  // 违反定义2：继承树有两个(含)以上的类有非静态成员
	std::cout << std::is_standard_layout<stand::C>::value << std::endl;  // 违反定义3：第一个非静态成员是基类类型
	std::cout << std::is_standard_layout<stand::D>::value << std::endl;  // 违反定义4：有虚函数
	std::cout << std::is_standard_layout<stand::E>::value << std::endl;  // 违反定义5：有虚基类
	std::cout << std::is_standard_layout<stand::F>::value << std::endl;  // 违反定义6：非静态成员x不符合标准布局类型


	//POD是可以进行二进制拷贝的

	if (std::is_pod<PODType>::value)
	{
		std::cout << "before" << std::endl;
		PODType a;
		a.x = 8;
		a.y = 10.5;
		std::cout << a.x << std::endl;
		std::cout << a.y << std::endl;

		size_t size = sizeof(a);
		char* p = new char[size];
		memcpy(p, &a, size);
		PODType* pA = (PODType*)p;

		std::cout << "after" << std::endl;
		std::cout << pA->x << std::endl;
		std::cout << pA->y << std::endl;

		delete p;
	}
	system("pause");
}