#pragma once
//template<class T>
//class stack
//{
//private:
//	T* _a;
//	size_t _top;
//	size_t _capacity;
//};
#include<iostream>
#include<vector>
#include<list>
namespace bit
{
	template<class T,class Container=vector<T>>
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_back();
		}
		const T& top() const
		{
			return _con.back();
		}
		size_t size() const
		{
			return _con.size();
		}
		size_t empty() const
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
}
