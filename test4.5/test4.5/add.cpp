#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
#define lc p << 1
#define rc p << 1 | 1
typedef long long LL;
int n, m;
LL a[N];
ll c[N];
ll dp[N];
struct node
{
    int l, r;
    LL a1, a2;
} tr[N << 2]; // ¿Õ¼ä¿ª 4 ±¶

void pushup(int p)
{
    tr[p].a1 = max(tr[lc].a1, tr[rc].a1);
    tr[p].a2 = max(tr[lc].a2, tr[rc].a2);
}

void build(int p, int l, int r)
{
    tr[p] = { l, r, (LL)-1e18,(ll)-1e18 };
    if (l == r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(p);
}
void modify(int p, int x, ll a1, ll a2)
{
    if (tr[p].l == x && tr[p].r == x)
    {
        tr[p].a1 = max(tr[p].a1, a1);
        tr[p].a2 = max(tr[p].a2, a2);
        return;
    }
    int mid = (tr[p].l + tr[p].r) >> 1;
    if (x <= mid) modify(lc, x, a1, a2);
    else modify(rc, x, a1, a2);
    pushup(p);
}
node query(int p, int x, int y)
{
    if (x <= tr[p].l && tr[p].r <= y) return { 0, 0, tr[p].a1, tr[p].a2 };
    int mid = (tr[p].l + tr[p].r) >> 1;
    node sum = { 0, 0, (LL)-1e18, (ll)-1e18 };
    if (x <= mid) {
        node L = query(lc, x, y);
        sum.a1 = max(sum.a1, L.a1); sum.a2 = max(sum.a2, L.a2);
    }
    if (y > mid) {
        node R = query(rc, x, y);
        sum.a1 = max(sum.a1, R.a1); sum.a2 = max(sum.a2, R.a2);
    }
    return sum;
}
void cnm()
{
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    build(1, 1, n);
    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1];
        if (i > 1)
        {
            node t = query(1, 1, i - 1);
            ll max1;
            if (a[i] % 2)max1 = t.a1;
            else max1 = t.a2;
            if (max1 != -1e18)
            {
                dp[i] = max(dp[i], a[i] + max1);
            }
        }
        if (a[i] % 2)modify(1, i, dp[i - 1] + a[i], -1e18);
        else modify(1, i, -1e18, dp[i - 1] + a[i]);
    }

    cout << dp[n] << '\n';
}

int main()
{
    int t; cin >> t;
    while (t--)
    {
        cnm();
    }
    return 0;
}