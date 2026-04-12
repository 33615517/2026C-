#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
void Test_string5()
{
	//字符串查找：find() 找字符/子串
	//找字符
	string s1 = "hello world";
	// 1. 找字符'w'
	size_t pos1 = s1.find('w');
	if (pos1 != string::npos)
	{
		cout << "'w'在位置：" << pos1 << endl;// 输出6
	}
	// 2. 找子串"world"
	size_t pos2 = s1.find("world");
	if (pos2 != string::npos)
	{
		cout << "world在位置：" << pos2 << endl;// 输出6
	}
	// 3. 从下标5开始找字符'o'
	size_t pos3 = s1.find('o', 5);  // 从下标为5的位置 ' ' 往后找
	cout << "'o'在位置：" << pos3 << endl;// 输出7（s[7]是'o'）
}

int main()
{
	Test_string5();
	return 0;
}