#include <iostream>
#include <typeinfo>
using namespace std;

class White {};
class Black {};


template <typename T1, typename T2>
void Sum(T1& t1, T2& t2, decltype(t1 + t2)& s)
{
	s = t1 + t2;
}


class CTest
{
public:
	int m_nNo;
};

void overloadfunc(int)
{}

void overloadfunc(char)
{}

int&& rfvalue() { return 0; };

const bool func()
{
	return true;
}


double foo(int a)
{
	return (double)a + 0.1;
}

int foo(double b)
{
	return (int)b;
}

template <class T>
auto Forward(T t) -> decltype(foo(t))
{
	return foo(t);
}



int main()
{
	////////////////////////////////////////////////////////////////
	White a;
	Black b;
	cout << typeid(a).name() << endl; // class White
	cout << typeid(b).name() << endl; // class Black
	
	White c;
	bool a_b_sametype = (typeid(a).hash_code() == typeid(b).hash_code());
	bool a_c_sametype = (typeid(a).hash_code() == typeid(c).hash_code());
	
	cout << "Same type? " << endl;
	cout << "A and B? " << (int)a_b_sametype << endl; // 0
	cout << "A and C? " << (int)a_c_sametype << endl; // 1

	//////////////////////////////////////////
	int i;
	decltype(i) j = 0;
	cout << typeid(j).name() << endl; // int
	float aa;
	double bb;
	decltype(aa + bb) cc;
	cout << typeid(cc).name() << endl; // double

	//////////////////////////////////

	enum { K1, K2, K3 } anon_e; // 匿名的枚举

	union
	{
		decltype(anon_e) key;
		char* name;
	} anon_u;             // 匿名的union联合体

	struct
	{
		int d;
		decltype(anon_u) id;
	} anon_s[100];         // 匿名的struct数组


	decltype(anon_s) as;
	as[0].id.key = decltype(anon_e)::K1; // 引用匿名类型枚举中的值
	

	int ia = 3;
	long ib = 5;
	float fc = 1.0f, fd = 2.3f;
	long le;
	float ff;
	Sum(ia, ib,le);    // s的类型被推导为long
	Sum(fc, fd, ff);  // s的类型被推导为float


	///////////////////////////////////////////////////////
	int itest = 3;
	int arr[3] = { 0 };
	int* pInt = arr;

	// 不带括号
	decltype(itest) ditest; // int
	decltype(arr) darr;     // int [3]
	decltype(pInt) dpInt;   // int *

	CTest clTest;
	decltype(clTest.m_nNo) dClTestNo; // int

	//decltype(overloadfunc);      // 编译不通过

	// 带括号 规则1 将亡值
	decltype(rfvalue()) r_value_f = 100;    // 将亡值 int &&

	// 带括号 规则2
	decltype(true ? itest : itest) ditest1 = itest;    // int & 三目运算符，这里返回一个左值
	decltype((itest)) ditest2 = itest;      // int&  返回左值
	decltype((++itest)) ditest3 = itest;    // int&  返回左值
	decltype(arr[1]) darr1 = itest;         // int&  []操作返回左值
	decltype(*pInt) dpInt1 = itest;         // int&  *操作返回左值
	decltype("hello") dstr = "world";       // const char(&)[6]  字符串字面常量为左值

	// 带括号 规则3
	decltype(12) dNum = 100;                // int
	decltype(itest++) dNum1 = 0;            // int   itest++返回右值
	decltype(func()) dFunc;                 // const bool  推导为bool


	///////////////////////////////////////////////////
	cout << Forward(2) << endl;    // 2.1
	cout << Forward(0.5) << endl;  // 0

	
	system("pause");
}