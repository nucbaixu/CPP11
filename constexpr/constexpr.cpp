#include <iostream>
using namespace std;

/////////////////////说明constexpr的作用///////////////////////
int fact(int n) 
{
	return (n == 1 ? 1 : n * fact(n - 1));
}

constexpr int fact_const(int n) 
{
	return (n == 1 ? 1 : n * fact_const(n - 1));
}


//////////////////////////////////////////////////////////////////
//对于自定义类型的数据，要想成为常量表达式值的话，需要定义自定义常量构造函数。如下示例//
struct Date {
	constexpr Date(int y, int m, int d) :
		year(y), month(m), day(d) {}

	constexpr int GetYear()const { return year; }
	constexpr int GetMonth()const { return month; }
	constexpr int GetDay() const { return day; }

private:
	int year;
	int month;
	int day;
};

constexpr Date PRCfound{ 1949, 10, 1 };
constexpr int foundmonth = PRCfound.GetMonth();


int main(int ac, char* av[]) {
	
	//int arr1[fact(4)];		// 错误，数组大小不确定无法编译，对未定义的函数或为未声明为“constexpr”的函数的调用导致了故障
	int array2[fact_const(4)];	//@1 正确。等价于写了 4 * 3 * 2
	char group[fact_const(6)];	//@2 正确

	if (ac > 1)
		std::cout << fact_const(ac);	// @3


	cout << foundmonth << endl;


	return 0;
}