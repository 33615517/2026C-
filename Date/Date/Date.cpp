#define _CRT_SECURE_NO_WARNINGS 1
#include"Date.h"
using namespace std;
Date::Date (int year, int month , int day)
	:_year(year),
	_month(month),
	_day(day)
{
	assert(year >= 1);
	assert(month >= 1 && month <= 12);
	assert(day >= 1 && day <= GetMonthDay(year, month));
}
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}
Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
		return *this;
	
}
int Date::GetMonthDay(int year, int month) const
{
	assert(month > 0 && month < 13);
	static int monthDayArray[13] = { -1, 31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		return 29;
	}

	return monthDayArray[month];
}
// 日期+=天数

Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= (-day);
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13)
		{
			_month = 1;
			++_year;
		}
	}
	return *this;
}
// 日期+天数

Date Date::operator+(int day) const
{
	Date tmp(*this);
	tmp += day;
	return tmp;
}



// 日期-天数

Date Date::operator-(int day) const
{
	Date tmp(*this);
	tmp -= day;
	return tmp;
}



// 日期-=天数

Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += (-day);
	}
	else
	{
		_day -= day;
		while (_day <= 0)
		{
			--_month;
			if (_month == 0)
			{
				_month = 12;
				--_year;
			}
			_day += GetMonthDay(_year, _month);
		}
	}
	return *this;
}



// 前置++

Date& Date::operator++()
{
	*this += 1;
	return *this;
}



// 后置++

Date Date::operator++(int)
{
	Date tmp(*this);
	*this += 1;
	return tmp;
}



// 后置--

Date Date::operator--(int)
{
	Date tmp(*this);
	*this -= 1;
	return tmp;
}



// 前置--

Date& Date::operator--()
{
	*this -= 1;
	return *this;
}



// >运算符重载

bool Date::operator>(const Date& d) const
{
	if (_year > d._year || (_year == d._year && _month > d._month) || (_year == d._year && _month == d._month && _day > d._day))return true;
	return false;
}



// ==运算符重载

bool Date::operator==(const Date& d) const
{
	if (_year == d._year && _month == d._month && _day == d._day)return true;
	return false;
}



// >=运算符重载

bool Date::operator >= (const Date& d)  const
{
	if (*this > d || *this == d)return true;
	return false;
}



// <运算符重载

bool Date::operator < (const Date& d)  const
{
	if (!(*this >= d))return true;
	return false;
}



// <=运算符重载

bool Date::operator <= (const Date& d) const
{
	if (!(*this > d))return true;
	return false;
}



// !=运算符重载

bool Date::operator != (const Date& d) const
{
	if (!(*this == d))return true;
	return false;
}



// 日期-日期 返回天数

int Date::operator-(const Date& d) const
{
	int flag = 1;
	Date max = *this;
	Date min = d;
	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	int n = 0;
	while (min != max)
	{
		++min;
		++n;
	}
	return n * flag;
}
ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "/" << d._month << "/" << d._day;
	return out; 
}
istream& operator>>(istream& in, Date& d)
{
	while (1)
	{
		cout << "请依次输入年月日:>";
		in >> d._year >> d._month >> d._day;

		if (d._month < 1 || d._month > 12 || d._day < 1 || d._day > d.GetMonthDay(d._year, d._month))
		{
			cout << "输入日期非法:";
			cout << d << endl;
			cout << "请重新输入!!!" << endl;
		}
		else
		{
			break;
		}
	}

	return in;
}