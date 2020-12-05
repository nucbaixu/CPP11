// Union.cpp : 说明非受限联合体的使用
//

#include <iostream>
#include <string>

using namespace std;

union T
{
	int x;
	double d;
	char b[sizeof(double)];
};

union T2
{
	string s; // string有非平凡的构造函数
	int n;
};


//由程序员自己为非受限联合体定义构造函数
union T3
{
	string s; // string有非平凡的构造函数
	int n;
public:
	T3() { new (&s) string; }  // 自定义构造函数
	~T3() { s.~string(); }     // 自定义析构函数
};


/******************************************************
 @ function : 	匿名非受限联合体可以运用于类的声明中，这样的类也称为“枚举式的类”。如下示例
 @ Access 	:	
 @ Parameter:	
 @ Returns  :	
 @ Remarks 	:   
 @ author   :   
******************************************************/
struct Student
{
	Student(bool g, int a) : gender(g), age(a) {}

	bool gender;
	int age;
};

class Singer
{
public:
	enum Type { STUDENT, NATIVE, FOREIGNER };

	Singer(bool g, int a) : s(g, a)
	{
		t = STUDENT;
	}
	Singer(int i) : id(i)
	{
		t = NATIVE;
	}
	Singer(const char* n, int s)
	{
		int size = (s > 9) ? 9 : s;
		memcpy(name, n, size);
		name[s] = '\0';
		t = FOREIGNER;
	}

	~Singer() {}
	
	void print()
	{
		switch (t)
		{
		case STUDENT:
			cout << "s.gender: " << s.gender << endl;
			cout << "s.age: " << s.age << endl;
			break;
		case NATIVE:
			cout << "id: " << id << endl;
			break;
		case FOREIGNER:
			cout << "name: " << name << endl;
			break;
		default:
			break;
		}
	}
private:
	Type t;
	
	union
	{
		Student s;
		int id;
		char name[10];
	};
};



int main()
{
	T t = { 0 }; // 到底是初始化第一个成员还是所有成员呢?
	//T2 t2;       // 构造失败，因为T的构造函数被删除; ERROR:尝试引用已删除的函数

	T3 t3;

	Singer objSer1(true, 13);
	objSer1.print();

	Singer objSer2(20200129);
	objSer2.print();

	Singer objSer3("kaizenliu", 9);
	objSer3.print();

    std::cout << "Hello World!\n";
}

