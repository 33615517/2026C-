#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

namespace bit
{
	class string
	{
	public:
		// 【迭代器模拟】
		// 在当前的简单实现中，内存是连续的字符数组，所以可以直接用原生指针作为迭代器
		typedef char* iterator;
		typedef const char* const_iterator;

		// 获取指向字符串首字符的迭代器（非 const 版本，可修改内容）
		iterator begin()
		{
			return _str;
		}

		// 获取指向字符串末尾（'\0' 位置）的迭代器
		iterator end()
		{
			return _str + _size;
		}

		// 获取指向字符串首字符的常量迭代器（只读）
		const_iterator begin() const
		{
			return _str;
		}

		// 获取指向字符串末尾的常量迭代器（只读）
		const_iterator end() const
		{
			return _str + _size;
		}

		// 【构造函数】
		// 短小频繁调用的函数，可以直接定义到类里面，默认会成为 inline 内联函数
		// 参数给默认值 ""，这样无参调用时（比如 string s;）会构造一个只含 '\0' 的空字符串
		string(const char* str = "")
		{
			_size = strlen(str);
			// _capacity 代表有效字符的容量，不包含结尾的 '\0'
			_capacity = _size;
			// 开辟空间：容量 + 1（为了存放 '\0'）
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		// 【交换函数】
		// 将当前对象与另一个对象 s 的内部成员直接交换指针和数值
		// 这是一种极其高效的操作，不会发生深拷贝喵！
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		// 【拷贝构造函数】 (现代写法)
		// 目标：解决浅拷贝带来的同一块内存析构两次、互相影响的问题。
		// 思路：让 tmp 去干脏活累活（调用构造函数深拷贝一份数据），然后直接把 tmp 的劳动成果和我们自己（this）交换。
		// 离开作用域时，tmp 会自动析构，顺便帮我们把原来的垃圾内存（如果有的话）清理掉。
		string(const string& s)
		{
			string tmp(s._str); // 用 s 的 C 风格字符串构造一个 tmp 对象（深拷贝完成）
			swap(tmp);          // 窃取 tmp 的内部指针和数据
		}

		// 【赋值运算符重载】 (现代写法)
		// 类似于上面的拷贝构造，传值传参时编译器会自动调用拷贝构造生成 tmp，
		// 然后把 tmp 里的好东西直接交换给当前对象。
		// 无论是自己给自己赋值（s1 = s1），还是正常赋值（s1 = s2），都能完美且安全地运行！
		string& operator=(string tmp)
		{
			swap(tmp); // 交换后，原来的旧数据被 tmp 带走，随着 tmp 函数结束被自动销毁
			return *this;
		}

		// 【析构函数】
		// 清理堆区申请的内存，防止内存泄漏
		~string()
		{
			if (_str)
			{
				delete[] _str;
				_str = nullptr;     // 防御性编程，指针置空防野指针
				_size = _capacity = 0;
			}
		}

		// 【获取 C 风格字符串】
		// 兼容 C 语言接口，返回底层的 char* 指针
		const char* c_str() const
		{
			return _str;
		}

		// 【清空字符串】
		// 不需要释放内存，只需要把有效字符长度置为 0，并在开头打上结束标志 '\0' 即可
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		// 获取有效字符个数
		size_t size() const
		{
			return _size;
		}

		// 获取当前容量
		size_t capacity() const
		{
			return _capacity;
		}

		// 【重载 [] 运算符】（非 const，支持读写）
		char& operator[](size_t pos)
		{
			assert(pos < _size); // 严格检查越界喵！
			return _str[pos];
		}

		// 【重载 [] 运算符】（const 版本，只支持读）
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}

		// 【容量及增删查改接口声明】（实现在 cpp 文件中）
		void reserve(size_t n);                  // 扩容
		void push_back(char ch);                 // 尾插一个字符
		void append(const char* str);            // 尾插一个字符串
		string& operator+=(char ch);             // 追加字符的语法糖
		string& operator+=(const char* str);     // 追加字符串的语法糖

		void insert(size_t pos, char ch);        // 在 pos 位置插入一个字符
		void insert(size_t pos, const char* str);// 在 pos 位置插入一个字符串
		void erase(size_t pos, size_t len = npos); // 从 pos 位置删除 len 个字符

		size_t find(char ch, size_t pos = 0);          // 查找字符第一次出现的位置
		size_t find(const char* str, size_t pos = 0);  // 查找子串第一次出现的位置
		string substr(size_t pos = 0, size_t len = npos); // 提取子串

	private:
		char* _str = nullptr;   // 指向堆区动态开辟的字符数组
		size_t _size = 0;       // 当前有效字符个数（不包含 '\0'）
		size_t _capacity = 0;   // 当前最大容量（不包含 '\0'）

		// npos 通常定义为 size_t 的最大值，表示“直到字符串末尾”或“未找到”
		static const size_t npos;
	};

	// 【非成员函数重载全局运算符声明】
	// 让 string 对象支持比较大小，底层复用 strcmp
	bool operator<(const string& s1, const string& s2);
	bool operator<=(const string& s1, const string& s2);
	bool operator>(const string& s1, const string& s2);
	bool operator>=(const string& s1, const string& s2);
	bool operator==(const string& s1, const string& s2);
	bool operator!=(const string& s1, const string& s2);

	// 支持流插入和流提取（为了访问私有成员，通常在类里声明为 friend，但这里实现不需要，所以声明在外部即可）
	ostream& operator<<(ostream& out, const string& s);
	istream& operator>>(istream& in, string& s);
}
