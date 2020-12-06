#include <atomic>
#include <iostream>
#include <thread>
using namespace std;

atomic<int> a;
atomic<int> b;

int Thread1(int) 
{
	int t = 1;
	a = t;
	b = 2;

	return 0;
}

int Thread2(int)
{
	while (b != 2)
		;  // 自旋等待 
	cout << a << endl;  // 总是期待a的值为1

	return 0;
}


atomic_llong total{ 0 };     // 原子数据类型

void func(int) {
	for (long long i = 0; i < 100000000LL; ++i)
	{
		total += i;
	}
}


int main() 
{

	thread t1(func, 0);
	thread t2(func, 0);

	t1.join();
	t2.join();
	
	cout << total << endl;  // 9999999900000000
	thread t11(Thread1, 0);
	thread t21(Thread2, 0);

	t11.join();
	t21.join();
	return 0;
}