#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// C++11引入了一种新的枚举类型，即“枚举类”，又称“强类型枚举”。声明请类型枚举非常简单，只需要在enum后加上使用class或struct。
enum Old { Yes, No };         // old style
enum class New1 { Yes, No };  // new style
enum struct New2 { Yes, No }; // new style

int main()
{
	/**
	*“传统”的C++枚举类型有一些缺点：
	*/
	enum Status1 { Ok, Error };
	//  enum Status2{Ok, Error};     // error:导致命名冲突, Status1已经有成员叫Ok, Error

	// 在C++11中，强类型枚举解决了这些问题
	enum class StatusN1 { Ok, Error };
	enum struct StatusN2 { Ok, Error };
	//enum class { Wang, Liu, Sun, Zhao }; // error:匿名强类型枚举编译报错

	//  StatusN1 flagN1 = Ok;         // error:必须使用强类型名称
	StatusN2 flagN2 = StatusN2::Ok;

	enum class C : char { C1 = 1, C2 = 2 }; // 指定枚举的底层数据类型char
	enum class D : unsigned int { E1 = 1, E2 = 2, Ebig = 0xFFFFFFF0U };
	cout << sizeof(C::C1) << endl;    // 1
	cout << sizeof(D::E1) << endl;    // 4
	cout << sizeof(D::Ebig) << endl;  // 4

	system("pause");
}