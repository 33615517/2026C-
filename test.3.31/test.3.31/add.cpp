#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<map>
#include<list>
#include"astring.h"
using namespace std;

// =========================================================================
// 第一部分：测试 C++ 标准库的 std::string 
// (用于观察标准库的行为，方便我们自己模拟实现时抄作业)
// =========================================================================

void test_string1()
{
	string s1;
	string s2("hello world");

	cout << s1 << s2 << endl;

	s2[0] = 'x'; // 测试 operator[] 的修改功能
	cout << s1 << s2 << endl;

	// 1、下标 + [] 遍历法
	for (size_t i = 0; i < s2.size(); i++)
	{
		cout << s2[i] << " ";
	}
	cout << endl;

	// 2、迭代器遍历法 (C++ 最正统的遍历方式，所有容器通用)
	auto it = s2.begin(); // 等价于 string::iterator it = s2.begin();
	while (it != s2.end())
	{
		*it += 2; // 通过迭代器修改字符的 ASCII 码
		cout << *it << " ";
		++it;
	}
	cout << endl;
	cout << s2 << endl;

	// 演示其他容器（如 map）的迭代器用法，证明迭代器是通用的
	map<string, string> dict;
	auto mit = dict.begin();

	// 3、范围 for 循环（C++11新语法）
	// 底层其实就是被编译器替换成了上面的迭代器 while 循环
	for (auto& ch : s2) // 加了引用 & 才能修改里面的值
	{
		ch -= 2; // 把刚才加的 2 减回来
		cout << ch << " ";
	}
	cout << endl;
	cout << s2 << endl;
}

void test_string2()
{
	// 测试正向迭代器
	string s2("hello world");
	string::iterator it = s2.begin();
	while (it != s2.end())
	{
		*it += 2;
		cout << *it << " ";
		++it;
	}
	cout << endl;

	// 测试反向迭代器 (reverse_iterator)
	// rbegin() 指向最后一个字符，rend() 指向第一个字符的前面
	string::reverse_iterator rit = s2.rbegin();
	while (rit != s2.rend())
	{
		cout << *rit << " ";
		++rit; // 注意：反向迭代器的 ++，实际上是往前走！
	}
	cout << endl;

	// 测试 const 对象的只读迭代器 (const_iterator)
	const string s3("hello world");
	auto cit = s3.begin();
	while (cit != s3.end())
	{
		// *cit += 2; // 编译报错！const 迭代器只能读不能写
		cout << *cit << " ";
		++cit;
	}
	cout << endl;

	// 测试 const 对象的反向只读迭代器
	auto rcit = s3.rbegin();
	while (rcit != s3.rend())
	{
		cout << *rcit << " ";
		++rcit;
	}
	cout << endl;
}

// 观察标准库 string 的扩容机制（不同编译器的扩容倍数不同，VS下大概是1.5倍扩）
void TestPushBack()
{
	string s;
	// reserve: 预留空间，提前开好 100 个字节，避免后续频繁扩容浪费性能
	s.reserve(100);
	size_t sz = s.capacity();
	cout << "capacity changed: " << sz << '\n';

	cout << "making s grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity()) // 只要容量发生变化，就打印出来
		{
			sz = s.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}

void test_string3()
{
	string s2("hello world");
	cout << s2.length() << endl; // length 和 size 是一模一样的，size是为了和其他STL容器统一加的
	cout << s2.size() << endl;

	cout << s2.max_size() << endl; // 字符串理论最大长度，一般是个极其巨大的数字

	cout << s2.capacity() << endl;
	TestPushBack();
}

void test_string4()
{
	string s2("hello worldxxxxxxxxxxxxx");
	cout << s2.size() << endl;
	cout << s2.capacity() << endl << endl;

	// 测试 reserve 的行为：如果 n < 当前容量，标准库通常不会缩容（为了效率）
	s2.reserve(20);
	cout << s2.size() << endl;
	cout << s2.capacity() << endl << endl;

	s2.reserve(40); // 扩容
	cout << s2.size() << endl;
	cout << s2.capacity() << endl << endl;

	// 测试 clear：只清空数据（size 变 0），但不释放空间（capacity 不变）
	s2.clear();
	cout << s2.size() << endl;
	cout << s2.capacity() << endl << endl;

	// 打印迭代器的底层真实类型名
	cout << typeid(string::iterator).name() << endl;
	cout << typeid(string::reverse_iterator).name() << endl;
}

void test_string5()
{
	string s("hello world");
	s.push_back(' ');   // 尾插单字符
	s.push_back('x');
	s.append("yyyyyy"); // 尾插字符串
	cout << s << endl;

	s += ' ';           // += 单字符 (底层调用 push_back)
	s += "33333333333"; // += 字符串 (底层调用 append)
	cout << s << endl;

	// insert 测试：可能导致大量数据往后挪动，效率较低，尽量少用
	s.insert(0, "hello bit ");
	cout << s << endl;

	s.insert(10, "zzzz");
	cout << s << endl;
}

void test_string6()
{
	string s("hello world");
	s.erase(6, 1); // 删掉下标为6的1个字符
	cout << s << endl;

	s.erase(0, 1); // 头删1个字符
	cout << s << endl;

	s.erase(s.begin()); // 传入迭代器删除
	cout << s << endl;

	s.erase(--s.end()); // 尾删
	cout << s << endl;

	string ss("hello world");
	ss.erase(6); // 没传第二个参数，默认 npos，直接从下标 6 删到结尾
	cout << ss << endl;

	// 经典面试题：把字符串里所有的空格替换成 "%20" (这里用 "%%" 演示)
	string sss("hello                  world hello bit");

	// 【思路1】直接用 replace（效率低，因为每次替换长度不同都会导致后面数据挪动）
	/*size_t pos = sss.find(' ');
	while (pos != string::npos) {
		sss.replace(pos, 1, "%%");
		pos = sss.find(' ', pos+2);
	}*/

	// 【思路2】空间换时间：开个新字符串，遍历旧的，不是空格就拷贝，是空格就追加 "%%"
	string tmp;
	tmp.reserve(sss.size()); // 提前开空间，绝杀优化
	for (auto ch : sss)
	{
		if (ch == ' ')
			tmp += "%%";
		else
			tmp += ch;
	}
	cout << tmp << endl;

	sss.swap(tmp); // 用新做好的字符串交换给原字符串，极速！
	cout << sss << endl;
}

// 分离路径和文件名测试
void SplitFilename(const std::string& str)
{
	std::cout << "Splitting: " << str << '\n';
	// find_last_of：找参数字符串里任意一个字符最后出现的位置（找最后的一个 / 或 \）
	std::size_t found = str.find_last_of("/\\");

	// substr 截取前后两段
	std::cout << " path: " << str.substr(0, found) << '\n';
	std::cout << " file: " << str.substr(found + 1) << '\n';
}

void test_string7()
{
	// 取文件后缀名
	string s("test.cpp.zip");
	size_t pos = s.rfind('.'); // 从右往左找 '.'
	string suffix = s.substr(pos);
	cout << suffix << endl; // 输出 .zip

	// 把元音字母全部替换成 '*'
	std::string str("Please, replace the vowels in this sentence by asterisks.");
	std::size_t found = str.find_first_not_of("abcdef"); // 找第一个不是这些字母的字符
	// ... 测试代码省略了部分 ...

	std::string str1("/usr/bin/man");
	std::string str2("D:\\1-教学服务团队\\1-比特课件");
	SplitFilename(str1);
	SplitFilename(str2);
}

void test_string8()
{
	// 测试全局的 operator+ (注意这不是 +=)
	// 会产生新的临时对象，效率一般
	string s1("hello");
	string s2 = s1 + "world";
	cout << s2 << endl;

	string s3 = "world" + s1;
	cout << s3 << endl;
}


// =========================================================================
// 第二部分：测试我们自己手写的 bit::string (在 string.h 和 string.cpp 里)
// (检查我们自己写的接口有没有 bug)
// =========================================================================
#include"string.h"

namespace bit
{
	void test_string1()
	{
		string s1;
		string s2("hello world");
		// 测试 c_str() 接口
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;

		// 测试自己写的 operator[]
		for (size_t i = 0; i < s2.size(); i++)
		{
			s2[i] += 2;
		}
		cout << s2.c_str() << endl;

		// 测试自己写的 begin() 和 end() 能否支持范围 for
		for (auto e : s2)
		{
			cout << e << " ";
		}
		cout << endl;

		// 测试自己写的普通迭代器
		string::iterator it = s2.begin();
		while (it != s2.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_string2()
	{
		// 测试自己写的扩容和追加逻辑 (+=)
		string s1("hello world");
		s1 += 'x';
		s1 += '#';
		cout << s1.c_str() << endl;

		s1 += "hello bit";
		cout << s1.c_str() << endl;

		// 测试自己写的 insert (之前这里有数据挪动写反的 Bug，现在测一下修复情况)
		s1.insert(5, '$');
		cout << s1.c_str() << endl;

		s1.insert(0, '$'); // 头插单字符
		cout << s1.c_str() << endl;

		string s2("hello world");
		s2.insert(5, "$$$"); // 中间插入字符串
		cout << s2.c_str() << endl;

		s2.insert(0, "$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"); // 头插超长字符串（触发内部扩容）
		cout << s2.c_str() << endl;
	}

	void test_string3()
	{
		// 测试自己写的 erase (删除)
		string s1("hello world");
		s1.erase(6, 100); // 删的长度超过剩余长度，测试截断逻辑
		cout << s1.c_str() << endl;

		string s2("hello world");
		s2.erase(6); // 不传 len，默认使用 npos，删到尾部
		cout << s2.c_str() << endl;

		string s3("hello world");
		s3.erase(6, 3); // 删中间一段，测试数据往前挪动的逻辑
		cout << s3.c_str() << endl;
	}

	void test_string4()
	{
		// 测试自己写的 find 和 substr
		string s("test.cpp.zip");
		size_t pos = s.find('.');
		string suffix = s.substr(pos); // 截取后缀
		cout << suffix.c_str() << endl;

		// 测试自己写的拷贝构造函数（深拷贝）
		string copy(s);
		cout << copy.c_str() << endl;

		// 测试自己写的赋值重载 operator=
		s = suffix;
		cout << suffix.c_str() << endl;
		cout << s.c_str() << endl;

		// 测试极端情况：自己给自己赋值（防“自杀”逻辑测试）
		s = s;
		cout << s.c_str() << endl;
	}

	void test_string5()
	{
		// 测试大小比较逻辑复用（我们只写了 < 和 ==，测试其他四个运算符能否正常工作）
		string s1("hello world");
		string s2("hello world");

		cout << (s1 < s2) << endl;
		cout << (s1 == s2) << endl;

		// 测试 C风格字符串 与 bit::string 的比较（得益于单参数构造函数的隐式类型转换）
		cout << ("hello world" < s2) << endl;
		cout << (s1 == "hello world") << endl;

		// 测试自己写的流插入 << 和 流提取 >>
		cout << s1 << s2 << endl;

		string s0;
		cin >> s0; // 测试输入流（内部有 256 字节的 buff 优化）
		cout << s0 << endl;
	}
}

int main()
{
	// 可以根据需要取消注释调用我们写的测试用例
	// bit::test_string5();

	// =========================================================
	// 补充知识测试：内存编码探秘 (ASCII码 与 字符的本质)
	// =========================================================

	// char 数组直接存入整型数字
	char buff[4];
	buff[0] = 97; // 对应 ASCII 字符 'a'
	buff[1] = 98; // 'b'
	buff[2] = 99; // 'c'
	buff[3] = 0;  // 对应 '\0'

	cout << buff << endl; // 打印结果为 "abc"

	// 汉字编码测试：汉字是由多个 char(字节) 拼凑而成的
	char str[] = "牛马";
	cout << strlen(str) << endl; // 打印字节长度

	// 暴力破坏汉字的某个字节
	str[1]++;
	cout << str << endl; // 打印出乱码或者奇怪的字

	str[3]--;
	cout << str << endl;

	return 0;
}