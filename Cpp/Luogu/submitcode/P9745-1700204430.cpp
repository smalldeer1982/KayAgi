#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
using namespace std;
namespace Milkcat {
    typedef long long LL;
    typedef pair<LL, LL> pii;
    const int N = 1e6 + 5, mod = 998244353;
    LL n, u, v, a[N], f[N]; int g[N][64][2];
    vector<int> G[N];
    void dfs(int u, int fa) {
    	REP(i, 0, 63) g[u][i][a[u] >> i & 1] = 1;
    	for (int v : G[u]) {
    		if (v == fa) continue;
    		dfs(v, u);
    		REP(i, 0, 63) {
    			LL t0 = g[u][i][0], t1 = g[u][i][1];
    			g[u][i][0] = (t0 * (g[v][i][0] + f[v]) + t1 * g[v][i][1]) % mod;
    			g[u][i][1] = (t0 * g[v][i][1] + t1 * (g[v][i][0] + f[v])) % mod;
    		}
		}
		REP(i, 0, 63) f[u] = (f[u] + (1LL << i) % mod * g[u][i][1]) % mod;
	}
    int main() {
		cin >> n;
		REP(i, 1, n) cin >> a[i];
		REP(i, 2, n)
			cin >> u, G[u].push_back(i), G[i].push_back(u);
		dfs(1, 0);
		cout << f[1] << '\n';
        return 0;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T --) Milkcat::main();
    return 0;
}