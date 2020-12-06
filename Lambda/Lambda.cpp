#include <iostream>
#include <vector>
#include <algorithm>
#include "time.h"
using namespace std;

void main()
{
	int a = 20, b = 10;

	auto totalAB = [](int x, int y)->int { return x + y; };
	int aAddb = totalAB(a, b);
	cout << "aAddb :" << aAddb << endl;

	auto totalAB2 = [a, &b]()->int { return a + b; };
	int aAddb2 = totalAB2();
	cout << "aAddb2 :" << aAddb2 << endl;

	auto totalAB3 = [=]()->int { return a + b; };
	int aAddb3 = totalAB3();
	cout << "aAddb3 :" << aAddb3 << endl;

	[] {}; // 最简lambda函数
	[=] { return a + b; }; // 省略了参数列表与返回类型，返回类型由编译器推断为int
	auto fun1 = [&](int c) { b = a + c; }; // 省略了返回类型，无返回值
	auto fun2 = [=, &b](int c)->int { return b += a + c; }; // 各部分都很完整的lambda函数
	cout << "fun2(100) :" << fun2(100) << endl;


	vector<int> nVec;
	for (int i = 0; i < 100000; ++i)
	{
		nVec.push_back(i);
	}

	double time_Start = (double)clock();
	for (vector<int>::const_iterator it = nVec.begin(); it != nVec.end(); ++it)
	{
		cout << *it << endl;
	}
	
	double time_Finish = (double)clock();
	double time_Interval_1 = (double)(time_Finish - time_Start) / 1000;

	time_Start = (double)clock();
	for_each(nVec.begin(), nVec.end(), [](int val) { cout << val << endl; });
	time_Finish = (double)clock();
	double time_Interval_2 = (double)(time_Finish - time_Start) / 1000;

	cout << "time_Interval_1 :" << time_Interval_1 << endl;
	cout << "time_Interval_2 :" << time_Interval_2 << endl;

}
