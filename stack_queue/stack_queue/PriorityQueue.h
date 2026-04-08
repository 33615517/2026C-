#pragma once
#include<vector>

namespace bit
{
	template<class T,class Container=vector<T>>
	class priority_queue
	{
	public:
		void AdjustUp(int child)
		{
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (_con[child] > _con[parent])
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else break;
			}
		}
		void AdjustDown(int parent)
		{
			int child = parent * 2 + 1;
			while (child < _con.size())
			{
				if (child + 1 < _con.size()-1 && _con[child + 1] > _con[child])
				{
					++child;
				}
				if (_con[child] > _con[parent])
				{
					swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else break;
			}
		}
		void push(const T& x)
		{
			_con.push_back(x);
			AdjustUp(_con.size() - 1);
		}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown();
		}
		const T& top() const
		{
			return _con[0];
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
