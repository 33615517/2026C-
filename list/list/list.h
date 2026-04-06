#pragma once
#include<iostream>
#include<cassert>
namespace bit
{
	template<class T>
	struct list_node
	{
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;
		list_node(const T& val = T())
			:_data(val)
			, _next(nullptr)
			, _prev(nullptr)
		{ }
	};

	template<class T>
	struct __list_iterator
	{ 
		typedef list_node<T> Node;
		typedef __list_iterator<T> self;

		Node* _node; // 迭代器本质上封装了一个节点指针

		__list_iterator(Node* node) : _node(node) {}

		// 解引用魔法：返回数据的引用
		T& operator*() {
			return _node->_data;
		}

		// 前置++魔法：让指针走向下一个节点
		self& operator++() {
			_node = _node->_next;
			return *this;
		}
		self operator++(int) {
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		self& operator--() {
			_node = _node->_prev;
			return *this;
		}
		self operator--(int) {
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		// 判不相等魔法
		bool operator!=(const self& it) const {
			return _node != it._node;
		}
		bool operator==(const self& it) const {
			return _node == it._node;
		}
	};
	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef __list_iterator<T> iterator;
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end() {
			return iterator(_head);
		}
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
				it = erase(it);
		}
		void push_back(const T& x)
		{
			insert(end(), x);
		}
		iterator insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);
			newnode->_next = cur;
			cur->_prev = newnode;
			newnode->_prev = prev;
			prev->_next = newnode;
			++_size;
			return iterator(newnode);
		}
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;
			prev->_next = next;
			next->_prev = prev;
			delete pos._node;
			--_size;
			return iterator(next);
		}
		void pop_back()
		{
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}
		size_t size() const 
		{
			return _size;
		}

	private:
		Node* _head;
		size_t _size;
	};
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
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}

}
