#include <bits/stdc++.h>
#include <fstream>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
#define pd push_back
#define ALL(a) a.begin(),a.end() 
const ll N = 5e3 + 7, M = 998244353;
int p[N];
ll mp[2][N];
void solve() {
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) cin >> p[i];
	for (int i = 0; i <= n; ++i)
		mp[0][i] = mp[1][i] = 1e18;
	mp[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int t = 0; t < i; ++t) {
			mp[i & 1][t] = min(mp[i & 1][t], mp[i + 1 & 1][t] + abs(p[i] - p[i - 1]));
			mp[i & 1][i - 1] = min(mp[i & 1][i - 1], mp[i + 1 & 1][t] + abs(p[i] - p[t]));
		}
		memset(&mp[i + 1 & 1], 127, sizeof(ll) * (n + 1));
	}
	ll ans = 1e18;
	for (int i = 0; i <= n; ++i) ans = min(ans, mp[n & 1][i]);
	cout << ans << '\n';
}
int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	if (ifstream("Aaa.in")) freopen("Aaa.in", "r", stdin);

	int T = 1; cin >> T;
	while (T--) solve();
	return 0;
}