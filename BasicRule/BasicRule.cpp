#include <iostream>
#include <vector>
using namespace std;

// 示例1：嵌套的模板标识
template <int i>  class X {};
template <class T> class Y {};


Y<X<1> > x1; // 编译成功
Y<X<1>> x2;  // 编译失败



int main()
{
	// 示例2：强制转换
	const vector<int> v1 = static_cast<vector<int>>(v1); // 编译成功
	const vector<int> v = static_cast<vector<int>>(v);  // 编译失败
	std::cout << "Hello World!\n";
}