#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<list>
#include<algorithm>
using namespace std;
void test_list1()
{
	list<int>lt;
	lt.push_back(1);
	lt.push_back(3);
	lt.push_back(5);
	lt.push_back(7);
	list<int>::iterator it = lt.begin();
	while (it != lt.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for(auto e:lt)
	{
		cout << e << " ";
	}
	cout << endl;
	 //sort(lt.begin(), lt.end());
	string s("dssddcfdwe");
	cout << s << endl;
	sort(s.begin(), s.end());
	cout << s << endl;
}
struct A
{
public:
	A(int a1=1,int a2=1)
		:_a1(a1)
		,_a2(a2)
	{ }
	void print()const
	{
		cout << _a1 << " " << _a2 << " ";
	}
private:
	int _a1;
	int _a2;
};
void test_list2()
{
	list<int>lt;
	lt.push_back(1);
	lt.emplace_back(1);
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
	list<A>it1;
	A aa1(1, 1);
	it1.push_back(aa1);
	it1.push_back(A(1,1));
	it1.push_back({ 1,1 });
	it1.emplace_back(1, 1);
	for (const auto& e : it1)
	{
		e.print();
	}
}
void test_list3()
{
	list<int>lt;
	lt.push_back(1);
	lt.push_back(1);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(1);
	auto it = lt.begin();
	int k = 3;
	while (k--)it++;
	lt.insert(it, 10);
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
	int x = 3; cin >> x;
	it = find(lt.begin(), lt.end(), x);
	if (it != lt.end())
	{
		lt.erase(it);
	}
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
	//lt.reverse();
	//reverse(lt.begin(), lt.end());
	/*lt.sort(greater<int>());

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;*/
	lt.unique();
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//test_list1();
	test_list3();
	return 0;
}