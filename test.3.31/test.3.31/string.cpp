#define _CRT_SECURE_NO_WARNINGS 1
#include "astring.h"

namespace bit
{
	// 静态成员变量必须在类外定义和初始化。-1 赋给无符号数会变成全 1 (即 4294967295)
	const size_t string::npos = -1;

	// 扩容函数：只扩不缩
	void string::reserve(size_t n)
	{
		if (n > _capacity) // 只有要求的新容量大于当前容量才去处理
		{
			char* tmp = new char[n + 1]; // +1 留给 '\0'
			strcpy(tmp, _str);           // 把旧数据搬到新家
			delete[] _str;               // 炸毁旧家
			_str = tmp;                  // 指针指向新家
			_capacity = n;               // 更新容量
		}
	}

	// 尾部插入单个字符
	void string::push_back(char ch)
	{
		if (_size == _capacity) // 满了就扩容
		{
			// 如果一开始容量为0，先给4；否则容量翻倍
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}

		_str[_size] = ch; // 在原来的 '\0' 位置填上新字符
		++_size;
		_str[_size] = '\0'; // 别忘了在最后补上新的结束符 '\0'
	}

	string& string::operator+=(char ch)
	{
		push_back(ch); // 直接复用
		return *this;
	}

	// 尾部追加字符串
	void string::append(const char* str)
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			// 如果追加后超过原容量：
			// 如果追加很长（超过两倍），需要多少开多少；如果追加不长，按原容量的2倍扩，避免频繁扩容
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}

		strcpy(_str + _size, str); // 从原来 '\0' 的位置开始把 str 拷贝过去（自带 \0）
		_size += len;
	}

	string& string::operator+=(const char* str)
	{
		append(str); // 直接复用
		return *this;
	}

	// 指定位置插入单字符
	void string::insert(size_t pos, char ch)
	{
		assert(pos <= _size); // pos == _size 相当于尾插，也是合法的

		if (_size == _capacity) reserve(_capacity == 0 ? 4 : _capacity * 2);

		// 核心逻辑：从后往前挪动数据，腾出 pos 位置
		size_t end = _size + 1; // 把包含 '\0' 在内的字符整体往后挪1个位置
		while (end > pos)
		{
			_str[end] = _str[end - 1]; // 后一个位置 = 前一个位置
			--end;
		}

		_str[pos] = ch; // 填入新字符
		++_size;
	}

	// 指定位置插入字符串
	void string::insert(size_t pos, const char* s)
	{
		assert(pos <= _size);

		size_t len = strlen(s);
		if (_size + len > _capacity)
		{
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}

		// ★ 你之前抓出的重灾区！这里的逻辑已经修复正确了 ★
		size_t end = _size + len;
		// 条件写成 end > pos + len - 1，等价于 end >= pos + len 
		// 这样写是为了防止 pos=0, len=0 时 size_t 减出负数变成无穷大（下溢）
		while (end > pos + len - 1)
		{
			_str[end] = _str[end - len]; // 将前面的字符往后挪动 len 个位置
			--end;
		}

		// 把新字符串 s 的内容填充到腾出来的空位中
		for (size_t i = 0; i < len; i++)
		{
			_str[pos + i] = s[i];
		}

		_size += len;
	}

	// 删除指定位置的一段字符
	void string::erase(size_t pos, size_t len)
	{
		assert(pos < _size);

		// 情况1：从 pos 开始要删的长度比剩下的还长，或者没传 len (默认 npos)
		// 说明 pos 后面的全不要了
		if (len >= _size - pos)
		{
			_str[pos] = '\0'; // 直接把 pos 处截断作为结尾
			_size = pos;
		}
		else // 情况2：只是删掉中间的一部分
		{
			// 从后往前挪？错！删除要“从前往后挪”，用后面的数据覆盖前面的数据
			for (size_t i = pos + len; i <= _size; i++)
			{
				_str[i - len] = _str[i]; // 前面的位置 = 后面的位置（连同 \0 一起往前搬）
			}
			_size -= len;
		}
	}

	// 查找字符
	size_t string::find(char ch, size_t pos)
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; i++) // 朴素的线性遍历
		{
			if (_str[i] == ch) return i; // 找到就返回下标
		}
		return npos;
	}

	// 查找子串
	size_t string::find(const char* str, size_t pos)
	{
		assert(pos < _size);
		// 直接复用 C 库函数 strstr（字符串匹配函数）
		const char* ptr = strstr(_str + pos, str);
		if (ptr == nullptr)
		{
			return npos;
		}
		else
		{
			return ptr - _str; // 指针相减得到偏移量（即下标）
		}
	}

	// 截取子串
	string string::substr(size_t pos, size_t len)
	{
		assert(pos < _size);

		// 如果要截取的长度超出了剩余长度，就把剩余的全截了
		if (len > _size - pos)
		{
			len = _size - pos;
  		}

		string sub;
		sub.reserve(len); // 提前开好空间，避免循环里频繁扩容
		for (size_t i = 0; i < len; i++)
		{
			sub += _str[pos + i]; // 一个个字符追加
		}

		return sub; // 传值返回，会调用拷贝构造函数（这就是为什么一定要深拷贝）
	}

	// --- 大小比较操作符复用 ---
	// 直接利用 C 库的 strcmp，巧妙地只实现 < 和 ==，其余全部用逻辑取反推导出来！
	bool operator<(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}

	bool operator==(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}

	bool operator<=(const string& s1, const string& s2) { return s1 < s2 || s1 == s2; }
	bool operator>(const string& s1, const string& s2) { return !(s1 <= s2); }
	bool operator>=(const string& s1, const string& s2) { return !(s1 < s2); }
	bool operator!=(const string& s1, const string& s2) { return !(s1 == s2); }

	// 流插入：重载 <<
	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s) // 基于范围的 for 循环（底层会自动调用 s.begin() 和 s.end()）
		{
			out << ch;
		}
		return out;
	}

	// 流提取：重载 >>
	istream& operator>>(istream& in, string& s)
	{
		s.clear(); // 读入前先清空原字符串的内容

		// 神级优化：设立一个 256 字节的局部缓冲区 buff
		// 目的是：如果直接一个一个字符地 s += ch，一旦字符串很长，会导致底层疯狂触发 reserve 扩容，效率极低
		const int N = 256; 
		char buff[N];
		int i = 0;

		char ch = in.get(); // 用 get() 才能读取空格和换行（cin >> ch 默认会忽略空格换行）
		while (ch != ' ' && ch != '\n') // 遇到空格或换行停止读取
		{
			buff[i++] = ch;
			if (i == N - 1) // 缓冲区快满了（留一个给 \0）
			{
				buff[i] = '\0';
				s += buff;  // 一次性把这 255 个字符追加到 string 中，大幅减少扩容次数
				i = 0;      // 清空缓冲区，重新开始接
			}
			ch = in.get();
		}

		// 把最后一次没装满 255 的残余部分追加进去
		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}

		return in; // 支持 cin >> s1 >> s2;
	}
}