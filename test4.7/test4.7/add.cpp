#define _CRT_SECURE_NO_WARNINGS 1
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s; cin >> s;
	int num = 0, cur = 0, cur1 = 0;
	int flag = 0, flag1 = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
		{
			if (flag == 1)
			{
				cur = 0;
				cur1 = 0;
			}
			flag = 1;
			flag1 = 0;
	   }
		else if (s[i] == ')')
		{
			if (flag != 0)
			{
				cur += cur1;
				cur1 = 0;
				num = max(num, cur);
				flag = 0;
				cur = 0;
			}
		}
		else if (s[i] == '.')
		{
			cur += cur1;
			cur1 = 0;
			if (flag1 == 1)
			{
				flag1 = 3;
				cur = 0;
			}
			else
			{
				flag = 1;
			}
		}
		else if(s[i]>='0'&&s[i]<='9'&&flag == 1)
		{
			cur1 = cur1 * 10 + s[i] - '0';
			flag1 = 0;
		}
	}
	cout << num;
	return 0;
}
