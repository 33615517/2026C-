#define _CRT_SECURE_NO_WARNINGS 1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3 + 10;
ll a[N];
int n;
ll b[N];
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = b[i - 1] + a[i];
    }
    ll min1 = 1e18;
    for (int l1 = 1; l1 <= n; l1++)
    {
        for (int r1 = l1; r1 <= n; r1++)
        {
            for (int l2 = r1 + 1; l2 <= n; l2++)
            {
                for (int r2 = l2; r2 <= n; r2++)
                {
                    min1 = min(min1, abs((b[r1] - b[l1 - 1]) - (b[r2]-b[l2 - 1])));
                    if (min1 == 0)break;
                }
            }
        }
    }
    cout << min1;
    return 0;
}