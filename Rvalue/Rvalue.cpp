// Rvalue.cpp : 关于右值引用
#include <iostream>

using namespace std;

class HasPtrMem
{
public:
	HasPtrMem() :d(new int(0)) {};
	~HasPtrMem() { delete d; };

public:
	int * d;
};


class HasPtrMem2
{
public:
	HasPtrMem2() :d(new int(0)) { cout << "construct:" << ++n_cstr << endl; };
	HasPtrMem2(const HasPtrMem2 & h) :d(new int(*h.d)) { cout << "copy construct:" << ++n_cptr; };
	HasPtrMem2(HasPtrMem2 && h) :d(h.d) { h.d == nullptr; cout << "Move construct" << ++n_mvtr << endl; }
	~HasPtrMem2() { delete d; cout << "destruct:" << ++n_dstr; };

public:
	int *d;
	static int n_cstr;
	static int n_dstr;
	static int n_cptr;
	static int n_mvtr;

};

int HasPtrMem2::n_cptr = 0;
int HasPtrMem2::n_cstr = 0;
int HasPtrMem2::n_dstr = 0;
int HasPtrMem2::n_mvtr = 0;


HasPtrMem2 GetTemp() 
{ 
	HasPtrMem2 h;
	return h; 
}


int main()
{
	HasPtrMem a;
	HasPtrMem b(a);
	cout << *a.d << *b.d<<endl;
	//然后会发生运行时错误，因为析构了a.d 和b.d是相同的地址，析构了两次
	//为什么指向相同的地址，b的构造调用了拷贝构造函数，这个拷贝构造函数有编译器隐式生成，执行按位拷贝的操作
	//为了不发生上述的错误，通常要用户自定义实现深拷贝函数

	//下面的例子分析拷贝构造的原理，因为编译器对返回值有优化，所以看不到
	//原则上会调用一次构造函数和两次拷贝构造函数
	HasPtrMem2 P1 = GetTemp();
}

