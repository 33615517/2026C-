#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<deque>
namespace bit
{
	template<class T, class Container = deque<T>>
	class queue
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_front();
		}
		const T& front() const
		{
			return _con.front();
		}
		const T& back() const
		{
			return _con.back();
		}
		size_t size() const
		{
			return _con.size();
		}
		bool empty() const
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
}
