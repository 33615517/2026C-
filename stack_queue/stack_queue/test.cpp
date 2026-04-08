#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;
#include"Stack.h"
#include"Queue.h"
#include"PriorityQueue.h"
#include<iostream>
#include<algorithm>
void test()
{
	srand(time(0));
	const int N = 1000000;
	deque<int>dp;
	vector<int>v;
	for (int i = 0; i < N; i++)
	{
		auto e = rand() + i;
		v.push_back(e);
		dp.push_back(e);
	}
	int begin1 = clock();
	sort(v.begin(), v.end());
	int end1 = clock();
	int begin2 = clock();
	sort(dp.begin(), dp.end());
	int end2 = clock();
	cout << end1 - begin1 << '\n' << end2 - begin2 << '\n';
}
template<class T>
class Less
{
public:
	bool operator()(const T& x, const T& y)
	{
		return x < y;
	}
};
int main()
{
	Less<int>LessFunc;
	cout << LessFunc(1, 2) << '\n';
	return 0;
}