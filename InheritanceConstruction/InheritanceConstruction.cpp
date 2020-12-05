// InheritanceConstruction.cpp :说明继承构造函数的用途
#include <iostream>


struct A
{
	A(int i) {}
	A(double d, int i) {}
	A(float f, int i, const char* c) {}
	// ... 
};

/******************************************************
 @ function : 	类中有大量的构造函数，而派生类却只有一些成员函数时，如果B想要有A的多样的构造方法，就需要一一透传各个基类的接口
 @ Access 	:	
 @ Parameter:	
 @ Returns  :	
 @ Remarks 	:   
 @ author   :   
******************************************************/
struct B : A
{
	B(int i) : A(i) {}
	//B(double d, int i) : A(d, i) {}
	B(float f, int i, const char* c) : A(f, i, c) {}
	// ... 
	virtual void ExtraInterface() {}
};


//而引入继承构造函数的机制就是为了解决这种麻烦的
/******************************************************
 @ function : 	派生类可以通过使用using声明来继承基类的构造函数
 @ Access 	:
 @ Parameter:
 @ Returns  :
 @ Remarks 	:
 @ author   :
******************************************************/
struct C : A
{
	using A::A;
	// ... 
	virtual void ExtraInterface() {}
};

/******************************************************
 @ function : 	该片段说明为什么需要委培构造函数
 @ Access 	:	
 @ Parameter:	
 @ Returns  :	
 @ Remarks 	:   
 @ author   :   
******************************************************/
class Info
{
public:
	Info() : type(1), name('a')
	{
		InitRest();
	}
	Info(int i) : type(i), name('a')
	{
		InitRest();
	}
	Info(char e) : type(1), name(e)
	{
		InitRest();
	}
private:
	void InitRest()
	{
		/* 其他初始化 */
	}

	int type;
	char name;
	// ...
};


/******************************************************
 @ function : 	该代码段说明委培构造函数的工作原理
 @ Access 	:	
 @ Parameter:	
 @ Returns  :	
 @ Remarks 	:   
 @ author   :   
******************************************************/
class Info2
{
public:
	Info2() : Info2(1, 'a') { }
	Info2(int i) : Info2(i, 'a') { }
	Info2(char e) : Info2(1, e) { }
private:
	Info2(int i, char e) : type(i), name(e)
	{
		/* 其他初始化 */
	}
	int type{1};
	char name{'a'};
	// ...
};


class Info3
{
public:
	Info3() { InitRest(); }
	Info3(int i) : Info3() { }
	Info3(char e) : Info3() { }
private:
	void InitRest()
	{
		/* 其他初始化 */
	}
	int type;
	char name;
	// ...
};

int main()
{
	B b(1);

	C c1(1.0,1,"");
	C c2(1);

	system("pause");

}

