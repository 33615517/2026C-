#define _CRT_SECURE_NO_WARNINGS 1
#include"string.h"

namespace bit
{
	// size_t 是无符号整数，-1 会发生截断变成全 1，也就是该类型能表示的最大值喵~
	const size_t string::npos = -1;

	// 【预留空间/扩容机制】
	// 只会扩大容量，不会缩小。这是为了减少频繁分配内存的开销。
	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1]; // 多开 1 个字节给 '\0'
			strcpy(tmp, _str);           // 老数据搬家到新房子
			delete[] _str;               // 炸掉老房子（释放旧内存）
			_str = tmp;                  // 更新指针指向新房子
			_capacity = n;               // 更新容量记录
		}
	}

	// 【尾插字符】
	void string::push_back(char ch)
	{
		// 检查满没满，满了就扩容
		if (_size == _capacity)
		{
			// 如果一开始容量是 0，先给 4 个字节；否则按 2 倍扩容
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}

		_str[_size] = ch; // 在原来的 '\0' 位置放新字符
		++_size;
		_str[_size] = '\0'; // 在新末尾补上 '\0'
	}

	// 【尾插字符的语法糖 +=】
	string& string::operator+=(char ch)
	{
		push_back(ch); // 直接复用
		return *this;
	}

	// 【尾插字符串】
	void string::append(const char* str)
	{
		size_t len = strlen(str); // 算一下要插多长
		if (_size + len > _capacity)
		{
			// 扩容策略：如果需要的总长度超过了当前容量的 2 倍，就按需要的实际长度扩；否则按 2 倍扩。
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}

		// 把 str 拷贝到 _str + _size（即原字符串末尾 '\0' 的位置）
		strcpy(_str + _size, str);
		_size += len;
	}

	// 【尾插字符串的语法糖 +=】
	string& string::operator+=(const char* str)
	{
		append(str); // 直接复用
		return *this;
	}

	// 【在 pos 位置插入字符】
	void string::insert(size_t pos, char ch)
	{
		assert(pos <= _size); // 可以在末尾插入（相当于尾插），但不能越界

		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}

		// 挪动数据：从最后面的 '\0' 开始，把 pos 后面的字符统统往后挪一格
		size_t end = _size + 1; // end 初始指向 '\0' 后面的越界位置，等待接收 '\0'
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}

		_str[pos] = ch; // 腾出空位，放入新字符
		++_size;
	}

	// 【在 pos 位置插入字符串】
	void string::insert(size_t pos, const char* s)
	{
		assert(pos <= _size);

		size_t len = strlen(s);
		if (_size + len > _capacity)
		{
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}

		// 挪动数据：为新来的字符串腾出 len 长度的空间
		size_t end = _size + len;
		while (end > pos + len - 1)
		{
			_str[end] = _str[end - len]; // 把字符往后抛 len 个身位
			--end;
		}

		// 把新字符串的内容填入腾出的空位中（这里用 strncpy 也可以）
		for (size_t i = 0; i < len; i++)
		{
			_str[pos + i] = s[i];
		}

		_size += len;
	}

	// 【删除指定区间的字符】
	void string::erase(size_t pos, size_t len)
	{
		assert(pos < _size); // 删除位置必须有效

		// 情况 1：要删的长度 >= 从 pos 开始剩余的所有字符长度
		// 说明 pos 后面的字符全不要了，直接截断！
		if (len >= _size - pos)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			// 情况 2：只是删掉中间的一部分
			// 把 pos+len 后面的存活数据，整体往前挪动覆盖掉要删除的部分
			for (size_t i = pos + len; i <= _size; i++)
			{
				_str[i - len] = _str[i];
			}

			_size -= len;
		}
	}

	// 【查找字符】从 pos 位置开始找 ch
	size_t string::find(char ch, size_t pos)
	{
		assert(pos < _size);

		for (size_t i = pos; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i; // 找到了，返回下标
			}
		}

		return npos; // 找不到，返回最大值
	}

	// 【查找字符串】从 pos 位置开始找 str 子串
	size_t string::find(const char* str, size_t pos)
	{
		assert(pos < _size);

		// 调用 C 标准库的字符串匹配函数 strstr，底层通常是暴力匹配或 KMP
		const char* ptr = strstr(_str + pos, str);
		if (ptr == nullptr)
		{
			return npos;
		}
		else
		{
			// 指针相减得到偏移量，即下标位置
			return ptr - _str;
		}
	}

	// 【提取子串】从 pos 开始，提取长度为 len 的子串
	string string::substr(size_t pos, size_t len)
	{
		assert(pos < _size);

		// 如果要提取的长度超过了剩余的可用长度，说明只要提取到末尾就行，更新 len
		if (len > _size - pos)
		{
			len = _size - pos;
		}

		string sub;
		sub.reserve(len); // 提前开好空间，避免下面的循环拼接时疯狂扩容（性能优化）
		for (size_t i = 0; i < len; i++)
		{
			sub += _str[pos + i]; // 逐个塞进新字符串
		}

		return sub; // 返回一个新对象（这里会触发拷贝构造或移动构造）
	}

	// ==================== 运算符重载区 ====================
	// 都是调用 C 库的 strcmp 函数进行按字典序比较喵~

	bool operator<(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}

	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2; // 复用逻辑，极其优雅
	}

	bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);
	}

	bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}

	bool operator==(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}

	bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}

	// 【流插入运算符重载】（控制台输出）
	// 注意：不能用 cout << _str，因为如果 string 中间含有 '\0'（合法情况），
	// C 风格的输出会在遇到第一个 '\0' 时提前截断。必须基于 _size 逐个字符输出！
	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s) // 范围 for，底层调用我们之前写的 begin() 和 end()
		{
			out << ch;
		}

		return out;
	}

	// 【流提取运算符重载】（控制台输入）
	istream& operator>>(istream& in, string& s)
	{
		s.clear(); // 读入前先清空旧数据

		// 性能优化：使用一个定长 buffer，避免频繁地触发字符串的扩容机制
		const int N = 256;
		char buff[N];
		int i = 0;

		char ch;
		ch = in.get(); // 用 get() 才能读取到空格和换行符，正常的 in >> ch 会过滤掉空白字符！

		// 默认遇到空格或换行代表一个词输入结束
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == N - 1) // 缓冲区快满了
			{
				buff[i] = '\0'; // 封口
				s += buff;      // 批量把这批数据塞入字符串对象中（触发一次扩容）
				i = 0;          // 重置缓冲区指针，继续读剩下的
			}

			ch = in.get();
		}

		// 把缓冲区里最后剩下的一点碎数据也收尾塞进去
		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}

		return in;
	}
}