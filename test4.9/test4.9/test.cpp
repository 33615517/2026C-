#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<queue>
#include<algorithm>
#include<array>
using namespace std;

#include"Stack.h"
#include"Queue.h"

//int main()
//{
//	//bit::stack<int, vector<int>> st;
//	//bit::stack<int, list<int>> st;
//	bit::stack<int, vector<int>> st;
//
//	// 类模板实例化时，按需实例化，使用哪些成员函数就实例化哪些，不会全实例化
//	st.push(1);
//	st.push(2);
//	st.push(3);
//	st.push(4);
//
//	cout << st.top() << endl;
//	st.pop();
//
//	//bit::queue<int, list<int>> q;
//	bit::queue<int> q;
//	q.push(1);
//	q.push(2);
//	q.push(3);
//	q.push(4);
//
//	cout << q.front() << endl;
//	q.pop();
//
//	return 0;
//}

void test_op1()
{
	srand(time(0));
	const int N = 1000000;

	deque<int> dq;
	vector<int> v;

	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i;
		v.push_back(e);
		dq.push_back(e);
	}

	int begin1 = clock();
	sort(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	sort(dq.begin(), dq.end());
	int end2 = clock();

	printf("vector:%d\n", end1 - begin1);
	printf("deque:%d\n", end2 - begin2);
}

void test_op2()
{
	srand(time(0));
	const int N = 1000000;

	deque<int> dq1;
	deque<int> dq2;

	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i;
		dq1.push_back(e);
		dq2.push_back(e);
	}

	int begin1 = clock();
	sort(dq1.begin(), dq1.end());
	int end1 = clock();

	int begin2 = clock();
	// 拷贝到vector
	vector<int> v(dq2.begin(), dq2.end());
	sort(v.begin(), v.end());
	dq2.assign(v.begin(), v.end());
	int end2 = clock();

	printf("deque sort:%d\n", end1 - begin1);
	printf("deque copy vector sort, copy back deque:%d\n", end2 - begin2);
}

//int main()
//{
//	test_op2();
//
//	return 0;
//}

//int main()
//{
//	//priority_queue<int> pq;
//	// 17:13继续
//	bit::priority_queue<int, vector<int>, Greater<int>> pq;
//	//bit::priority_queue<int> pq;
//	pq.push(4);
//	pq.push(1);
//	pq.push(5);
//	pq.push(7);
//	pq.push(9);
//	while (!pq.empty())
//	{
//		cout << pq.top() << " ";
//		pq.pop();
//	}
//	cout << endl;
//
//	return 0;
//}

//int main()
//{
//	int myints[] = { 10,20,30,5,15 };
//	sort(myints, myints + 5);
//
//	std::vector<int> v(myints, myints + 5);
//	cout << is_heap(v.begin(), v.end()) << endl;
//
//	cout << is_heap(myints, myints + 5) << endl;
//
//	make_heap(v.begin(), v.end());
//	cout << is_heap(v.begin(), v.end()) << endl;
//	std::sort_heap(v.begin(), v.end());
//	for (auto e : v)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	return 0;
//}

// 仿函数：本质是一个类，这个类重载operator(),他的对象可以像函数一样使用
//template<class T>
//class Less
//{
//public:
//	bool operator()(const T& x, const T& y)
//	{
//		return x < y;
//	}
//};
//
//template<class T>
//class Greater
//{
//public:
//	bool operator()(const T& x, const T& y)
//	{
//		return x > y;
//	}
//};

// < 升序
// > 降序
//template<class Compare>
//void BubbleSort(int* a, int n, Compare com)
//{
//	for (int j = 0; j < n; j++)
//	{
//		// 单趟
//		int flag = 0;
//		for (int i = 1; i < n - j; i++)
//		{
//			//if (a[i] < a[i - 1])
//			if (com(a[i], a[i - 1]))
//			{
//				swap(a[i - 1], a[i]);
//				flag = 1;
//			}
//		}
//
//		if (flag == 0)
//		{
//			break;
//		}
//	}
//}
//
//int main()
//{
//	Less<int> LessFunc;
//	Greater<int> GreaterFunc;
//	// 函数对象
//	cout << LessFunc(1, 2) << endl;
//	cout << LessFunc.operator()(1, 2) << endl;
//
//	int a[] = { 9,1,2,5,7,4,6,3 };
//	BubbleSort(a, 8, LessFunc);
//	BubbleSort(a, 8, GreaterFunc);
//
//	BubbleSort(a, 8, Less<int>());
//	BubbleSort(a, 8, -));
//
//	return 0;
//}

class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{
	}

	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}

	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}

class DateLess
{
public:
	bool operator()(Date* p1, Date* p2)
	{
		return *p1 < *p2;
	}
};

#include"PriorityQueue.h"

//int main()
//{
//	bit::priority_queue<Date> q1;
//	q1.push(Date(2018, 10, 29));
//	q1.push(Date(2018, 10, 28));
//	q1.push(Date(2018, 10, 30));
//	cout << q1.top() << endl;
//	q1.pop();
//
//	cout << q1.top() << endl;
//	q1.pop();
//
//	cout << q1.top() << endl;
//	q1.pop();
//
//	cout << endl;
//
//	// 1、类类型不支持比较大小
//	// 2、支持比较大小，但是比较的逻辑不是你想要的
//	// 需要自己实现仿函数
//
//	//bit::priority_queue<Date*, vector<Date*>, DateLess> q2;
//	bit::priority_queue<Date*> q2;
//	q2.push(new Date(2018, 10, 29));
//	q2.push(new Date(2018, 10, 28));
//	q2.push(new Date(2018, 10, 30));
//	cout << *q2.top() << endl;
//	q2.pop();
//
//	cout << *q2.top() << endl;
//	q2.pop();
//
//	cout << *q2.top() << endl;
//	q2.pop();
//
//	bit::priority_queue<int*> q3;
//	q3.push(new int(2));
//	q3.push(new int(1));
//	q3.push(new int(3));
//
//	cout << *q3.top() << endl;
//	q3.pop();
//
//	cout << *q3.top() << endl;
//	q3.pop();
//
//	cout << *q3.top() << endl;
//	q3.pop();
//
//
//	return 0;
//}

//#define N 10

template<size_t N = 10, bool flag = false>
class Stack
{
private:
	int _a[N];
	int _top;
};

// C++20
//template<double D>
//class A
//{
//private:
//
//};

//int main()
//{
//	Stack<> s0;
//	Stack<5> s1;
//	Stack<10> s2;
//
//	return 0;
//}

//template<class T, size_t N = 10>
//class array
//{
//public:
//	T& operator[](size_t index) { 
//		assert(index < N);
//		return _array[index];
//	}
//private:
//	T _array[N];
//	size_t _size;
//};

//int main()
//{
//	// 栈
//	array<int, 10> a1;
//	array<int, 100> a2;
//
//	int a3[10];
//	// 越界检查的问题
//	// 静态数组，抽查
//	// 越界读不检查，越界写抽查
//	cout << a3[10] << endl;
//	//a3[10] = 10;
//	//a3[11] = 10;
//	a3[12] = 10;
//	a3[20] = 10;
//
//	// array越界读写都可以检查
//	//a1[10];
//	//a1[12] = 10;
//
//	// 堆
//	vector<int> v(100, 1);
//	cout << sizeof(a2) << endl;
//	cout << sizeof(v) << endl;
//
//	return 0;
//}
//

//void func()
//{
//	int a = 1;
//	cout << &a << endl;
//}
//
//int main()
//{
//	int a = 0;
//	cout << &a << endl;
//
//	func();
//
//	return 0;
//}

// 函数模板 -- 参数匹配
template<class T>
//bool LessFunc(T const & left, T const & right)
bool LessFunc(const T& left, const T& right)
{
	return left < right;
}

// 特化
//template<>
//bool LessFunc<const Date*>(const Date* const& left, const Date* const& right)
//{
//	return *left < *right;
//}
//
//template<>
//bool LessFunc<Date*>(Date* const& left, Date* const& right)
//{
//	return *left < *right;
//}

// 推荐
bool LessFunc(const Date* left, const Date* right)
{
	return *left < *right;
}

bool LessFunc(Date* left, Date* right)
{
	return *left < *right;
}

//int main()
//{
//	cout << LessFunc(1, 2) << endl; // 可以比较，结果正确
//
//	Date d1(2022, 7, 7);
//	Date d2(2022, 7, 8);
//	cout << LessFunc(d1, d2) << endl; // 可以比较，结果正确
//
//	Date* p1 = &d1;
//	Date* p2 = &d2;
//	cout << LessFunc(p1, p2) << endl; // 可以比较，结果错误
//
//	const Date* p3 = &d1;
//	const Date* p4 = &d2;
//	cout << LessFunc(p3, p4) << endl; // 可以比较，结果错误
//
//	const int i = 0;
//	int const j = 0;
//	const int& rx = i;
//	int const& ry = i;
//
//	return 0;
//}

template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};

// 全特化
template<>
class Data<int, char>
{
public:
	Data() { cout << "Data<int, char>" << endl; }
};

// 偏特化/半特化
template<class T1>
class Data<T1, double>
{
public:
	Data() { cout << "Data<T1, double>" << endl; }
};

template<class T1>
class Data<T1, char>
{
public:
	Data() { cout << "Data<T1, char>" << endl; }
};

// 偏特化，传的类型是指针
template <typename T1, typename T2>
class Data <T1*, T2*>
{
public:
	Data()
	{
		cout << "Data<T1*, T2*>" << endl;
	}
};

template <typename T1, typename T2>
class Data <T1&, T2&>
{
public:
	Data()
	{
		cout << "Data<T1&, T2&>" << endl;
	}
};

// 17:06
template <typename T1, typename T2>
class Data <T1&, T2*>
{
public:
	Data()
	{
		cout << "Data<T1&, T2*>" << endl;

		int a = 0;
		T1& x = a;
		T2* y = &a;
		T1 z = a;

		cout << typeid(x).name() << endl;
		cout << typeid(y).name() << endl;
	}

	void Push(const T1& x)
	{
	}
};

//int main()
//{
//	Data<int, int> d1;
//	Data<int, char> d2;
//	Data<int, double> d3;
//	Data<char, double> d4;
//	Data<char, char> d5;
//	Data<char*, char*> d6;
//	Data<int*, char*> d7;
//	Data<int&, char&> d8;
//	Data<int&, double&> d9;
//	Data<int&, int*> d10;
//
//	return 0;
//}

int main()
{


	return 0;
}