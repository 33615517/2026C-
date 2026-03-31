#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#pragma once // 防止头文件被重复包含

#include<iostream>
//#include<string>
#include<assert.h>
using namespace std;

// 使用自定义命名空间 bit，防止和标准库的 std::string 发生冲突
namespace bit
{
	class string
	{
	public:
		// 迭代器本质是原生指针的 typedef（在 string 和 vector 中通常如此）
		typedef char* iterator;
		typedef const char* const_iterator;

		// --- 迭代器获取函数 ---
		iterator begin()
		{
			return _str; // 指向第一个字符
		}

		iterator end()
		{
			return _str + _size; // 指向最后一个有效字符的下一个位置（即 '\0' 的位置）
		}

		// 提供给 const 对象使用的只读迭代器
		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		// --- 构造函数与析构函数 ---

		// 带缺省参数的默认构造函数。短小频繁调用的函数直接在类内定义，默认成为 inline 内联函数
		// 注意：缺省值 "" 默认带有一个 '\0'，所以即便不传参，_str 也不是空指针，而是一个指向 '\0' 的合法字符串
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size; // _capacity 表示有效字符容量，不包含底层为 '\0' 预留的那 1 个字节
			_str = new char[_capacity + 1]; // +1 是为了给 '\0' 留空间
			strcpy(_str, str); // strcpy 会把 '\0' 一起拷贝过去
		}

		// 拷贝构造函数：解决“深拷贝”问题
		// 如果不写，编译器默认生成浅拷贝，会导致两个对象的 _str 指向同一块内存，析构时会崩溃（二次释放）
		string(const string& s)
		{
			_str = new char[s._capacity + 1]; // 重新开辟一块一样大的独立空间
			strcpy(_str, s._str);             // 把数据完整拷贝过来
			_size = s._size;
			_capacity = s._capacity;
		}

		// 赋值运算符重载：s1 = s2
		string& operator=(const string& s)
		{
			if (this != &s) // 防止极端的自己给自己赋值（s1 = s1），那会导致自己的数据先被清理，全变成乱码
			{
				// 传统写法的深拷贝：先释放旧空间，再开辟新空间拷贝
				delete[] _str;

				_str = new char[s._capacity + 1];
				strcpy(_str, s._str);
				_size = s._size;
				_capacity = s._capacity;
			}
			return *this; // 支持连续赋值：s1 = s2 = s3;
		}

		~string()
		{
			delete[] _str; // 释放堆区数组内存
			_str = nullptr;// 指针置空，防止野指针
			_size = _capacity = 0;
		}

		// --- 容量与访问接口 ---

		// 兼容 C 语言的接口，返回原生 C 字符串指针
		const char* c_str() const
		{
			return _str;
		}

		// 清空字符串内容（假删除，只是把长度置 0，空间不释放）
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		size_t size() const
		{
			return _size;
		}

		size_t capacity() const
		{
			return _capacity;
		}

		// [] 运算符重载，提供像数组一样的随机访问
		char& operator[](size_t pos)
		{
			assert(pos < _size); // 越界检查（严格断言，比标准库更猛）
			return _str[pos];    // 返回引用，意味着可以修改该字符：s[0] = 'x';
		}

		// const 版本的 []，提供给 const string 对象调用（只能读不能改）
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}

		// --- 修改与扩容接口（声明，实现在 cpp） ---
		void reserve(size_t n); // 扩容
		void push_back(char ch); // 尾插单字符
		void append(const char* str); // 尾插字符串
		string& operator+=(char ch); // 重载 +=，复用 push_back
		string& operator+=(const char* str); // 重载 +=，复用 append

		void insert(size_t pos, char ch); // 任意位置插入单字符
		void insert(size_t pos, const char* str); // 任意位置插入字符串
		void erase(size_t pos, size_t len = npos); // 任意位置删除一段字符

		// --- 查找与截取（声明，实现在 cpp） ---
		size_t find(char ch, size_t pos = 0);
		size_t find(const char* str, size_t pos = 0);
		string substr(size_t pos = 0, size_t len = npos);

	private:
		char* _str;       // 指向动态开辟的字符数组
		size_t _size;     // 当前有效字符个数（不含 \0）
		size_t _capacity; // 当前能容纳的最大有效字符数（不含 \0）

		// npos 代表“未找到”或者“直到字符串末尾”，是无符号整型的最大值
		static const size_t npos;
	};

	// --- 全局非成员函数（操作符重载） ---
	// 之所以写在类外，是为了保证左右操作数的对称性（比如支持 "hello" == s1）
	bool operator<(const string& s1, const string& s2);
	bool operator<=(const string& s1, const string& s2);
	bool operator>(const string& s1, const string& s2);
	bool operator>=(const string& s1, const string& s2);
	bool operator==(const string& s1, const string& s2);
	bool operator!=(const string& s1, const string& s2);

	// 流插入、流提取重载
	ostream& operator<<(ostream& out, const string& s);
	istream& operator>>(istream& in, string& s);
}
