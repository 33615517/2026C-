#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
#define ALL(a) a.begin(),a.end() 
const ll N = 2e3 + 10, M = 998244353;
const int NN = 1e5 + 10;
int n, a[N];
ll fac[NN], inv[NN];
double ln_fac[NN];
ll qpow(ll a, ll b, ll p)
{
    ll ret = 1;
    while (b)
    {
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ret;
}

void init()
{
    fac[0] = 1;
    ln_fac[0] = 0;
    for (int i = 1; i < NN; i++) {
        fac[i] = fac[i - 1] * i % M;
        ln_fac[i] = ln_fac[i - 1] + log(i);
    }
    inv[NN - 1] = qpow(fac[NN - 1], M - 2, M);
    for (int i = NN - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % M;
}
ll C(int n, int m)
{
    if (m < 0 || m > n) return 0;
    return fac[n] * inv[m] % M * inv[n - m] % M;
}
double get_log_C(int n, int m)
{
    if (m < 0 || m > n) return -1.0;
    return ln_fac[n] - ln_fac[m] - ln_fac[n - m];
}

struct Edge
{
    int u, v;
    ll w;
    double real_w; 
    bool operator<(const Edge& t) const
    {
        return real_w < t.real_w;
    }
};

int fa[N];
int find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        fa[i] = i;
    }
    vector<Edge> edges;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            ll w = C(max(a[i], a[j]), min(a[i], a[j]));
            double real_w = get_log_C(max(a[i], a[j]), min(a[i], a[j]));
            edges.push_back({ i, j, w, real_w });
        }
    }
    sort(edges.begin(), edges.end());
    ll ret = 0;
    int cnt = 0;
    for (auto& e : edges)
    {
        int fx = find(e.u), fy = find(e.v);
        if (fx != fy)
        {
            fa[fx] = fy;
            ret = (ret + e.w) % M; 
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    cout << ret % M << '\n';
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    init();
    int T;
    if (!(cin >> T)) T = 1;
    while (T--) solve();
    return 0;
}