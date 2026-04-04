#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
ll a[N];
int main()
{
    a[1] = 1;
    a[2] = 2;
    a[3] = 4;
    a[4] = 6;
    a[5] = 9;
    a[6] = 13;
    a[7] = 17;
    for (int i = 8; i < N; i++)a[i] = (a[i - 4] * 2 + 10) % 998244353;
    int t; cin >> t;
    while (t--)
    {
        int n; cin >> n;
        cout << a[n] << '\n';
    }
    return 0;
}