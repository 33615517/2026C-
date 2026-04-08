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

	template<class T,class Ref,class Ptr>
	struct __list_iterator
	{ 
		typedef list_node< T> Node;
		typedef __list_iterator<T, Ref, Ptr> self;

		Node* _node; // 迭代器本质上封装了一个节点指针

		__list_iterator(Node* node) : _node(node) {}

		// 解引用魔法：返回数据的引用
		Ref operator*() {
			return _node->_data;
		}
		Ptr operator->() {
			return &(_node->_data);
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
	//template<class T>
	//struct __list_const_iterator
	//{ 
	//	typedef list_node<T> Node;
	//	typedef __list_const_iterator<T> self;

	//	Node* _node; // 迭代器本质上封装了一个节点指针

	//// 允许使用普通迭代器来构造常量迭代器喵！
 //        __list_const_iterator(const __list_iterator<T>& it) : _node(it._node) {}

	//	// 解引用魔法：返回数据的引用
	//	const T& operator*() {
	//		return _node->_data;
	//	}
	//	const T* operator->() {
	//		return &(_node->_data);
	//	}
	//	// 前置++魔法：让指针走向下一个节点
	//	self& operator++() {
	//		_node = _node->_next;
	//		return *this;
	//	}
	//	self operator++(int) {
	//		self tmp(*this);
	//		_node = _node->_next;
	//		return tmp;
	//	}
	//	self& operator--() {
	//		_node = _node->_prev;
	//		return *this;
	//	}
	//	self operator--(int) {
	//		self tmp(*this);
	//		_node = _node->_prev;
	//		return tmp;
	//	}

	//	// 判不相等魔法
	//	bool operator!=(const self& it) const {
	//		return _node != it._node;
	//	}
	//	bool operator==(const self& it) const {
	//		return _node == it._node;
	//	}
	//};
	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		/*typedef __list_iterator<T> iterator;
		typedef __list_const_iterator<T> const_iterator;*/
		typedef __list_iterator<T, T&,T* > iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end() 
		{
			return iterator(_head);
		}
		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}
		list()
		{
			empty_init();
		}
		list(std::initializer_list<T> il)
		{
			empty_init();
			for (const auto& e : il)
			{
				push_back(e);
			}
		}
		void empty_init()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}
		list(const list<T>& lt)
		{
			empty_init();
			for (const auto& e : lt)
			{
				push_back(e);
			}
		}
		void swap(list<T>& lt)
		{
			std::swap(_head,lt._head);
			std::swap(_size,lt._size);
		}
		list<T>& operator=(list<T>lt)
		{
			swap(lt);
			return *this;
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
	struct AA
	{
		int _a1 = 1;
		int _a2 = 1;
	};
	std::ostream& operator<<(std::ostream& out, const AA& aa)
	{
		out << aa._a1 << " " << aa._a2;
		return out;
	}
	template<class Container>
	void print_container(const Container& v)
	{
		typename Container::const_iterator it = v.begin();
		while(it != v.end())
		{
			std::cout << *it << '\n';
			it++;
		}
		for (const auto& e : v)
		{
			std::cout << e << '\n';
		}
		std::cout << std::endl;
	}
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
		list<AA>lta;
		lta.push_back(AA());
		lta.push_back(AA());
		lta.push_back(AA());
		lta.push_back(AA());
		lta.push_back(AA());
		list<AA>::iterator ita = lta.begin();
		while (ita != lta.end())
		{
			std::cout << ita->_a1 << ":"<<ita->_a2<<'\n';
			++ita;
		}
		std::cout << std::endl;
		print_container(lta);
	}
	void test_list2()
	{
		list<int>lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		list<int>::iterator it = lt.begin();
		lt.insert(it, 10);
		print_container(lt);
		auto it1 = lt.begin();
		while (it1 != lt.end())
		{
			if (*it1 % 2 == 0)
			{
				it1 = lt.erase(it1);

			}
			else it1++;
		}
		print_container(lt);
	}
	void test_list3()
	{
		list<int>lt1;
		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);
		list<int>lt2(lt1);
		print_container(lt1);
		print_container(lt2);
		list<int>lt3;
		lt3 = lt1;
		print_container(lt3);
	}
	void test_list4()
	{
		list<int>lt1 ({ 1,2,3,4,2,5,6 });
		print_container(lt1);
	}
}
