#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int>PII;
typedef long long ll;
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> m >> n;
    while (m--)
    {
        vector<int>a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        bool max1 = true, min1 = true;
        for (int i = 0; i < n / 2; i++)
        {
            int l = 2 * i + 1;
            int r = i * 2 + 2;
            if (a[i] < a[l])max1 = false;
            if (a[i] > a[l])min1 = false;
            if (r < n)
            {
                if (a[i] < a[r])max1 = false;
                if (a[i] > a[r])min1 = false;
            }
        }
        if (max1)cout << "Max Heap\n";
        else if (min1)cout << "Min Heap\n";
        else cout << "Not Heap\n";
        vector<int>edges;
        cm(0, a, edges);
        for (int i = 0; i < edges.size()-1; i++)
            cout << edges[i] << " ";
            cout << edges[edges.size()-1];
    }
  

    return 0;
}