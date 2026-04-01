#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<map>
#include<list>
using namespace std;

// =========================================================================
// 第一部分：标准库 std::string 特性测试与 C++ 语法复习
// =========================================================================

void test_string1()
{
	string s1;
	string s2("hello world");

	cout << s1 << s2 << endl; // 测试默认构造和带参构造的输出

	s2[0] = 'x';              // 测试 operator[] 的写操作
	cout << s1 << s2 << endl;

	// 【遍历方式 1】：下标 + [] 
	// 最朴素的遍历方式，底层是指针偏移
	for (size_t i = 0; i < s2.size(); i++)
	{
		cout << s2[i] << " ";
	}
	cout << endl;

	// 【遍历方式 2】：迭代器
	// 迭代器是 STL 的精髓，它屏蔽了底层的物理结构（无论是数组还是链表），提供统一的遍历接口
	// string::iterator it = s2.begin(); // 老语法太长了
	auto it = s2.begin();                // 现代 C++ 强烈推荐用 auto 推导喵！
	while (it != s2.end())
	{
		*it += 2; // 迭代器不仅能读，还能直接修改底层数据
		cout << *it << " ";
		++it;
	}
	cout << endl;

	// 这里演示了迭代器的普适性，map 和 list 也能用同样的方式遍历
	map<string, string> dict;
	auto mit = dict.begin();

	// 【遍历方式 3】：范围 for 循环 (C++11 新特性)
	// 最简洁的遍历方式！但要注意，如果你想修改里面的字符，必须加引用 & 
	// 它的底层原理其实就是傻瓜式地替换成了迭代器（begin 和 end）
	for (auto& ch : s2)
	{
		ch -= 2;
		cout << ch << " ";
	}
	cout << endl;
}

void test_string2()
{
	// 这个函数主要测试四种迭代器：
	// 1. 正向可读写 iterator
	// 2. 反向可读写 reverse_iterator (rbegin -> rend)
	// 3. 正向只读 const_iterator (通常给 const 对象使用)
	// 4. 反向只读 const_reverse_iterator

	string s2("hello world");
	auto it = s2.begin();
	while (it != s2.end()) { /* ... */ ++it; }

	auto rit = s2.rbegin();
	while (rit != s2.rend()) { /* ... */ ++rit; }

	// const 对象只能调用 const 迭代器，防止权限放大喵！
	const string s3("hello world");
	auto cit = s3.begin();
	while (cit != s3.end()) { /* *cit += 2; 会报错，只读！ */ ++cit; }
}

void TestPushBack()
{
	string s;
	// reserve 预留空间。
	// 这里预先分配 100 个字符的空间，这样在后续 100 次 push_back 时，
	// 就不需要频繁地去堆区重新申请内存和拷贝数据了，极致的性能优化！
	s.reserve(100);
	size_t sz = s.capacity();
	cout << "capacity changed: " << sz << '\n';

	// 观察 string 底层是怎么偷偷扩容的
	for (int i = 0; i < 100; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity()) // 只要容量变了，就打印出来
		{
			sz = s.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}

void test_string4()
{
	// 测试 reserve 扩容机制的两个核心规则：
	// 1. reserve 扩大的容量如果比现有容量小，标准库通常什么都不做（不会缩容）。
	// 2. reserve 只改变 capacity，绝对不会改变 size（有效字符数）。
	string s2("hello worldxxxxxxxxxxxxx");
	s2.reserve(20); // 期望缩容到 20，但实际上 capacity 不会变小
	s2.reserve(40); // 扩容到 40，底层会去开辟新空间

	// clear 只清空数据，size 变 0，但 capacity 容量保留，房子还在。
	s2.clear();
}

void test_string5()
{
	// 测试尾插 (push_back / append) 和 指定位置插入 (insert)
	// 注意：insert 效率较低（需要往后挪动数据 $O(N)$），做算法题时尽量少用！
	string s("hello world");
	s.push_back(' ');
	s.append("yyyyyy");
	s += "33333333333"; // 最好用的还是 += 运算符重载喵！
}

void test_string6()
{
	// 测试 erase 删除功能
	string s("hello world");
	s.erase(6, 1);       // 从下标 6 开始，删 1 个
	s.erase(s.begin());  // 删掉迭代器指向的首字符 (头删)
	s.erase(--s.end());  // 删掉最后一个字符 (尾删)

	string sss("hello                  world hello bit");

	// 经典算法题：将字符串中的所有空格替换为 "%%"
	// 原地 replace 会导致后面的字符频繁后挪，效率极低（O(N^2)）
	// 高手写法：空间换时间！开一个 tmp 字符串，遍历原串，遇到空格填 "%%"，否则照抄，最后 swap！
	string tmp;
	tmp.reserve(sss.size()); // 提前开好空间，避免扩容
	for (auto ch : sss)
	{
		if (ch == ' ') tmp += "%%";
		else tmp += ch;
	}
	sss.swap(tmp); // $O(1)$ 交换指针，极其优雅喵！
}

void SplitFilename(const std::string& str)
{
	// 经典应用：提取文件路径和文件名
	// find_last_of：从后往前找，只要匹配 "/\\" 中的任意一个字符就停下
	std::size_t found = str.find_last_of("/\\");
	std::cout << " path: " << str.substr(0, found) << '\n';
	std::cout << " file: " << str.substr(found + 1) << '\n'; // 截取从斜杠后一个字符到末尾
}

void test_string7()
{
	// find_first_not_of 也是个好东西，找“第一个不包含在给定字符集里的字符”
	// 常用来做过滤操作
	std::string str("Please, replace the vowels in this sentence by asterisks.");
	std::size_t found = str.find_first_not_of("abcdef");
	while (found != std::string::npos)
	{
		str[found] = '*';
		found = str.find_first_not_of("abcdef", found + 1);
	}
}


// =========================================================================
// 第二部分：你手写的 bit::string 模拟实现测试区
// =========================================================================
#include"string.h"

namespace bit
{
	void test_string1()
	{
		// 测试基本构造和遍历
		string s1;
		string s2("hello world");

		// 范围 for 的底层就是你写的 begin() 和 end()。
		// 如果你把 string.h 里的 begin 改名叫 Begin，这里的范围 for 直接编译报错！
		for (auto e : s2)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_string2()
	{
		// 极限测试：多次追加，测试你写的扩容逻辑到底会不会崩
		string s1("hello world");
		s1 += 'x';
		s1 += '#';
		s1 += "hello bit";

		// 测试 insert 挪动数据的逻辑对不对
		s1.insert(5, '$');
		s1.insert(0, '$');
	}

	void test_string3()
	{
		// 极限测试：删除越界的情况
		string s1("hello world");
		s1.erase(6, 100); // 后面没 100 个字符了，测试你是否能正确触发 '\0' 截断机制
		cout << s1.c_str() << endl;
	}

	void test_string4()
	{
		// 测试 find 找字符和 substr 截取子串
		string s("test.cpp.zip");
		size_t pos = s.find('.'); // 只能找到第一个点
		string suffix = s.substr(pos);

		// 测试现代版的拷贝构造和赋值重载
		string copy(s);
		s = suffix;
		s = s; // 自己给自己赋值，测试你的 this != &s 逻辑或者 swap 临时对象的逻辑是否防身
	}

	void test_string5()
	{
		// 测试重载的大小比较运算符 (<, ==)
		string s1("hello world");
		string s2("hello world");

		cout << (s1 < s2) << endl;

		// 因为你的带参构造支持隐式类型转换 (const char* 隐式转 string)，
		// 所以即使左边是原生 C 串，也能比较！
		cout << ("hello world" < s2) << endl;
	}

	void test_string7()
	{
		string s1("hello world");
		string s2("xxxxxxxxxxxxxxxxxxxxxxxx");

		// 测试交换机制
		std::swap(s1, s2); // 调用全局模板，会产生 3 次深拷贝，效率极低！
		s1.swap(s2);       // 调用你手写的类成员函数，直接交换指针，效率直接拉满起飞！
	}
}

int main()
{
	// 这里可以自由切换你想跑的测试样例喵~
	// bit::test_string6();

	// 这里演示了 C++ 里的坑：浅拷贝（如果不写拷贝构造的话）
	// string s2(s1) 会让两个对象的指针指向同一块堆区内存。
	// 析构时会炸掉两次，导致程序崩溃！这也正是你为什么要手写深拷贝的原因。
	std::string s1("111111111111111111111111");
	std::string s2(s1);

	// 在原版 std::string 里，某些旧版本支持写时拷贝(COW)，打印地址可能一样，
	// 但现代 C++ 里基本都是各开各的空间了。
	printf("%p\n", s1.c_str());
	printf("%p\n", s2.c_str());

	return 0;
}