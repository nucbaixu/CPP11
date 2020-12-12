#include <atomic>
#include <iostream>
#include <thread>
#include <cassert>
#include <vector>
#include <string>
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


std::atomic<int> cnt = { 0 };
void f()
{
	for (int n = 0; n < 1000; ++n) {
		cnt.fetch_add(1, std::memory_order_relaxed);
	}
}
int test1()
{
	std::vector<std::thread> v;
	for (int n = 0; n < 10; ++n) {
		v.emplace_back(f);
	}
	for (auto& t : v) {
		t.join();
	}
	assert(cnt == 10000);    // never failed
	return 0;
}

std::atomic<std::string*> ptr;
int data1;

void producer()
{
	std::string* p = new std::string("Hello");
	data1 = 42;
	ptr.store(p, std::memory_order_release);
}

void consumer()
{
	std::string* p2;
	while (!(p2 = ptr.load(std::memory_order_consume)))
		;
	assert(*p2 == "Hello");  // never fires: *p2 carries dependency from ptr
	assert(data1 == 42);      // may or may not fire: data does not carry dependency from ptr
}


volatile int icount = 0;

void increase() {
	for (int i = 0; i < 1000000; i++) 
	{
		icount++;
	}
}

void decrease() {
	for (int i = 0; i < 1000000; i++) {
		icount--;
	}
}


int main() 
{

	std::thread t111(increase);
	std::thread t222(decrease);
	t111.join();
	t222.join();

	std::cout << icount << std::endl;
	
	test1();

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