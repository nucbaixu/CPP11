#include <stdexcept>
#include <iostream>
#include <stdarg.h>

using namespace std;

/******************************************************
 @ function : 	可变长参数的函数，有局限性，请思考有何局限
 @ Access 	:	
 @ Parameter:	
 @ Returns  :	
 @ Remarks 	:   
 @ author   :   
******************************************************/
double SumOfFloat(int count, ...) 
{
	va_list ap;
	double sum = 0;
	va_start(ap, count);//获得变长列表的句柄ap
	
	for (int i = 0; i < count; i++)
		sum += va_arg(ap, double);//每次获得一个参数
	va_end(ap);
	
	return sum;
}


//可变参数模板函数的定义
template<class ... T> void func(T ... args)
{
	//可变参数模板函数
	//sizeof...（sizeof后面有3个小点）计算变参个数
	cout << "num = " << sizeof...(args) << endl;
}


//递归终止函数
void debug()
{
	cout << "empty\n";
}

//展开函数
template <class T, class ... Args>
void debug(T first, Args ... last)
{
	cout << "parameter " << first << endl;
	debug(last...);
}


template <class T>
void print(T arg)
{
	cout << arg << endl;
}

template <class ... Args>
void expand(Args ... args)
{
	int a[] = { (print(args), 0)... };
}


template<typename... A> class BMW {};  // 变长模板的声明

template<typename Head, typename... Tail>  // 递归的偏特化定义
class BMW<Head, Tail...> : public BMW<Tail...>
{
	//当实例化对象时，则会引起基类的递归构造
public:
	BMW()
	{
		printf("type: %s\n", typeid(Head).name());
	}

	Head head;
};

template<> class BMW<> {};  // 边界条件


template <long... nums> struct Multiply;// 变长模板的声明

template <long first, long... last>
struct Multiply<first, last...> // 变长模板类
{
	static const long val = first * Multiply<last...>::val;
};

template<>
struct Multiply<> // 边界条件
{
	static const long val = 1;
};



int main() 
{
	printf("%f\n", SumOfFloat(3, 1.2f, 3.4, 5.6));//10.200000

	func();     // num = 0
	func(1);    // num = 1
	func(2, 1.0);   // num = 2

	debug(1, 2, 3, 4);

	expand(1, 2, 3, 4);

	BMW<int, char, float> car;

	cout << Multiply<2, 3, 4, 5>::val << endl; // 120
}