#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;
namespace bit
{
	class string
	{
	public:
		string()
			:_str(nullptr)
			,_size(0)
			,_capacity(0)
		{ }
		string(const char* str)
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1]; 
			strcpy(_str, str);
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	 void test_string1();
}
