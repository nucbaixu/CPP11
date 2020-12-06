#include <iostream>
#include <memory>
using namespace std;

void test_unique_ptr()
{
	unique_ptr<int> up1(new int(2020));  // 无法复制的unique_ptr
//   unique_ptr<int> up2 = up1;           // 不能通过编译
	cout << (*up1) << endl;              // 2020
	unique_ptr<int> up3 = move(up1);     // 现在up3是数据唯一的unique_ptr智能指针
	cout << (*up3) << endl;              // 2020
//   cout << (*up1) << endl;              // 运行时错误
	up3.reset();                         // 显式释放内存
	up1.reset();                         // 不会导致运行时错误
//   cout << (*up3) << endl;              // 运行时错误
}

void test_shared_ptr()
{
	shared_ptr<int> sp1(new int(131));
	shared_ptr<int> sp2 = sp1;
	cout << (*sp1) << endl;  // 131
	cout << (*sp2) << endl;  // 131
	sp1.reset();
	//   cout << (*sp1) << endl;
	cout << (*sp2) << endl;  // 131
}

void check(weak_ptr<int> & wp)
{
	shared_ptr<int> sp = wp.lock(); // 转换为shared_ptr
	if (sp != nullptr)
	{
		cout << "still " << (*sp) << endl;
	}
	else
	{
		cout << "pointer is invalid." << endl;
	}

}
void test_weak_ptr()
{
	shared_ptr<int> sp1(new int(2020));
	shared_ptr<int> sp2 = sp1;
	weak_ptr<int> wp = sp1;  // 指向shared_ptr<int>所指对象
	cout << (*sp1) << endl;  // 2020
	cout << (*sp2) << endl;  // 2020

	check(wp);               // still 2020
	sp1.reset();
	cout << (*sp2) << endl;  // 2020
	check(wp);               // still 2020
	sp2.reset();
	check(wp);               // pointer is invalid
}

int main()
{
	test_unique_ptr();
	test_shared_ptr();
	test_weak_ptr();
}