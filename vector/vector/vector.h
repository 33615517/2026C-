#pragma once
#include<iostream>
#include<vector>
#include <cassert>
#include <algorithm>
//using namespace std;
namespace bit
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin()const
		{
			return _start;
		}
		const_iterator end()const
		{
			return _finish;
		}
		/*vector() :
			_start(nullptr),
			_finish(nullptr),
			_end_of_storage(nullptr) {
		};*/
		vector() = default;
		/*vector(const vector<T>& v)
		{
			for (auto& e : v)
			{
				push_back(e);
			}
		}*/
		// 1. 抓虫核心防御：必须在初始化列表里把指针全部置空喵！
		vector(const vector<T>& v) :
			_start(nullptr),
			_finish(nullptr),
			_end_of_storage(nullptr)
		{
			// 2. 性能降维打击：既然已经知道对方有多大，直接一次性开辟好空间！
			// 避免 push_back 内部反复触发扩容喵！
			reserve(v.capacity());

			// 3. 安全且高效地尾插数据喵
			for (auto& e : v)
			{
				push_back(e);
			}
		}
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _end_of_storage = nullptr;

			}
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t old_size = size();
				T* tmp = new T[n];
				//memcpy(tmp, _start, size() * sizeof(T));
				if (_start)
				{
					for (size_t i = 0; i < old_size; ++i)
					{
						tmp[i] = std::move(_start[i]);
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + old_size;
				_end_of_storage = _start + n;
			}
		}
		void resize(size_t n, const T& val=T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}
		size_t size()const
		{
			return _finish - _start;
		}
		size_t capacity()const
		{
			return _end_of_storage - _start;
		}
		bool empty()const
		{
			return _start == _finish;
		}
		void push_back(const T& x)
		{
			//扩容
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());

			}
			*_finish = x;
			_finish++;
		}
		void pop_back()
		{
			assert(!empty());
			--_finish;
		}
		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start && pos <= _finish);
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				pos = _start + len;
			}
			iterator end = _finish;
			while (end > pos)
			{
				// 性能魔法：使用 std::move 榨干硬件性能喵！
				*end = std::move(*(end - 1));
				--end;
			}
			*pos = x;
			++_finish;
			return pos;
		}
		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos < _finish);
			iterator it = pos + 1;
			while (it != end())
			{
				*(it - 1) = std::move(*it);
				++it;
			}
			--_finish;
			return pos;
		}
		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;

	};
	template<class T>
	void print_vector(const vector<T>& v)
	{
		typename vector<T>::const_iterator it = v.begin();
		while (it != v.end())
		{
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
		for (auto e : v)
		{
			std::cout << e << " ";

		}
		std::cout << std::endl;
	}
	void test_vector1()
	{
		vector<int>v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(5);
		v.push_back(6);
		v.push_back(7);
		v.push_back(7);
		for (size_t i = 0; i < v.size(); i++)
		{
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
		print_vector(v);
		vector<double>vd;
		vd.push_back(1.2);
		vd.push_back(3.3);
		vd.push_back(5.5);
		vd.push_back(6.6);
		vd.push_back(7.7);
		vd.push_back(7.7);
		print_vector(vd);
	}
	void test_vector2()
	{
		vector<int>v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(5);
		v.push_back(6);
		v.push_back(6);
		v.push_back(6);
		v.push_back(1);
		v.insert(v.begin() + 2, 10);
		v.insert(v.begin() + 2, 10);
		v.insert(v.begin() + 2, 10);
		v.insert(v.begin() + 2, 10);
		print_vector(v);
		int x; std::cin >> x;
		auto pos = std::find(v.begin(), v.end(), x);
		if (pos != v.end())
		{
			pos=v.insert(pos, 300);
			(*pos) *= 100;
		}
		print_vector(v);
		// 演示：安全地删除 vector 中所有的偶数喵！
		bit::vector<int> v3;
		v3.push_back(1);
		v3.push_back(2);
		v3.push_back(2); // 连续的偶数，最容易踩坑！
		v3.push_back(3);
		v3.push_back(4);

		auto it = v3.begin();
		while (it != v3.end())
		{
			if (*it % 2 == 0)
			{
				// 必须用 it 接收返回值，否则迭代器失效崩溃喵！
				it = v3.erase(it);
				//v3.erase(it);
				//++it;
			}
			else
			{
				++it; // 只有没删除时才往后走喵
			}
		}

		std::cout << "删除偶数后喵: ";
		print_vector(v3); // 输出应该只有 1 3
	}
	void test_vector5()
	{
		vector<int>v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		print_vector(v);
		vector<int>v1 = v;
		print_vector(v1);
	}
}
