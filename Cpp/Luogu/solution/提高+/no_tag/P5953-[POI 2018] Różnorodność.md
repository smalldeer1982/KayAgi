# [POI 2018] Różnorodność

## 题目描述

给定一个 $n$ 行 $m$ 列的矩阵，请对于每个长宽均为 $k$ 的连续子正方形，统计里面出现过的数值的种类数。

## 说明/提示

对于 $100\%$ 的数据，$n,m\le3000$，$k\le \min(n,m)$。

## 样例 #1

### 输入

```
3 5 2
1 5 3 3 3
4 1 3 3 4
4 2 4 4 3```

### 输出

```
4 20```

# 题解

## 作者：jiangly (赞：2)

#### 题意

给定一个 $n\times m$ 的矩阵 ($1\le n,m\le 3000$)，求所有 $k\times k$ 的子矩阵的不同元素个数，输出最大值以及和。

#### 题解

对每种元素分开算，要求的就是一些 $k\times k$ 的矩形的并，用平衡树维护连续段，差分计算贡献即可。

时间复杂度：$O(nm\log m)$。

#### 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
int n, m, k;
std::vector<std::vector<int>> a, d;
std::map<int, int> s;
std::vector<std::vector<int>> pos;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m >> k;
    a.assign(n, std::vector<int>(m));
    int maxA = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j];
            maxA = std::max(maxA, a[i][j]);
            --a[i][j];
        }
    }
    pos.resize(maxA);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            pos[a[i][j]].push_back(i * m + j);
    d.assign(n - k + 2, std::vector<int>(m - k + 2));
    for (int v = 0; v < maxA; ++v) {
        s.clear();
        s[0] = 0;
        s[m - k + 1] = -1;
        for (int p : pos[v]) {
            int x = p / m + 1, y = p % m + 1;
            int u = std::max(0, x - k), l = std::max(0, y - k);
            x = std::min(x, n - k + 1);
            y = std::min(y, m - k + 1);
            s[y] = std::prev(s.upper_bound(y)) -> second;
            auto it = std::prev(s.upper_bound(l));
            int up = std::max(it -> second, u), rt = std::next(it) -> first;
            ++d[up][l];
            --d[up][rt];
            --d[x][l];
            ++d[x][rt];
            ++it;
            s[l] = x;
            while (it -> first != y) {
                up = std::max(it -> second, u);
                int lf = it -> first;
                it = s.erase(it);
                rt = it -> first;
                ++d[up][lf];
                --d[up][rt];
                --d[x][lf];
                ++d[x][rt];
            }
        }
    }
    for (int i = 0; i <= n - k + 1; ++i)
        for (int j = 1; j <= m - k + 1; ++j)
            d[i][j] += d[i][j - 1];
    for (int i = 1; i <= n - k + 1; ++i)
        for (int j = 0; j <= m - k + 1; ++j)
            d[i][j] += d[i - 1][j];
    int max = 0;
    long long sum = 0;
    for (int i = 0; i < n - k + 1; ++i) {
        for (int j = 0; j < m - k + 1; ++j) {
            max = std::max(max, d[i][j]);
            sum += d[i][j];
        }
    }
    std::cout << max << " " << sum << "\n";
    return 0;
}

```



---

## 作者：Starrykiller (赞：1)

其他题解我都看不懂，网上的题解也只有 $\Theta(1)$ 篇，所以为了造福后人来写篇题解。

分别考虑每种颜色。令 $f(i,j)$ 为以 $(i,j)$ 为**右下**顶点的 $k\times k$ 正方形内的颜色数。每个 $(i,j)$ 会给一个矩形区域内的 $f(i,j)$ 造成 $+1$ 的贡献，我们的目标就是：利用 $\texttt{std::multiset}$ 来维护贡献的区域，利用差分来维护贡献。

如果不考虑其他同颜色的元素的话，$(i,j)$ 会对 $x\in [i,i+k)$，$y\in [j,j+k)$ 内的 $f(x,y)$ 有 $+1$ 的贡献。直接扫描线是容易的。

问题是，现在可能会有同颜色的元素，导致贡献区间缩小。我们利用 $\texttt{std::multiset}$ 来维护已经有贡献的区间，然后令 $[i,i+k)$ 与已经有贡献的区间的补集取交集即可。

时间复杂度 $\Theta(nm\log nm)$，在洛谷和 POI 的官方评测机上均能通过。我也不知道为什么在 QOJ 上过不了，可能是常数原因。

```cpp
int n, m, k;
int a[MAXN][MAXN], s[MAXN][MAXN];
int mx, sum, now; 
vector<pair<int,int>> v[N];
multiset<pair<int,int>> st;

void work(int x, int l, int r, int t) {
    if (x>n) return;
    if (t==1) st.insert({l,r});
    int L=0, R=m+1;
    auto it=st.lower_bound({l,r});
    if (it!=st.begin()) L=prev(it)->second;
    if (next(it)!=st.end()) R=next(it)->first;
    L++, R--;
    L=max(L,l); R=min(R,r);
    if (L<=R) s[x][L]+=t, s[x][R+1]-=t;
    if (t==-1) st.erase(it);
}

void work(vector<pair<int,int>>& v) {
    int i=0, j=0;
    while(i<size(v)&&j<size(v)) {
        auto x1=v[i].first, x2=v[j].first+k;
        if (x1<=x2) work(x1,v[i].second,v[i].second+k-1,1), i++;
        if (x2<=x1) work(x2,v[j].second,v[j].second+k-1,-1), j++;
    }
    while (j<size(v)) work(v[j].first+k,v[j].second,v[j].second+k-1,-1), j++;
    st.clear();
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>m>>k;
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) cin>>a[i][j], v[a[i][j]].push_back({i,j});
    for (int i=1; i<=1e5; ++i) if (v[i].size()) work(v[i]);
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j)
            s[i][j]+=s[i][j-1];
        for (int j=1; j<=m; ++j)
            s[i][j]+=s[i-1][j];
    }
    for (int i=k; i<=n; ++i) for (int j=k; j<=m; ++j) sum+=s[i][j], mx=max(mx,s[i][j]);
    cout<<mx<<' '<<sum<<'\n';
}
```

---

## 作者：Jayun (赞：1)

# [POI2018] Różnorodność

## 题目描述

给定一个 $n$ 行 $m$ 列的矩阵，请对于每个长宽均为 $k$ 的连续子正方形，统计里面出现过的数值的种类数。

$n,m\le3000$，$k\le \min(n,m)$。

## 题解

用一个 $n\times k$ 大窗口从左往右滑动，这样相当于把二维化成一维。这样一列增一列减地转移。

再考虑大窗口内的 $k\times k$ 小窗口。对于每个权值，它的贡献很像扫描线，用数据结构维护权值所在的行数，对于当前操作的某行，小窗口的下端刚好够到此行（或者如果在前面 $k$ 内有相同权值，就是小窗口的上端在前面的下一行）、小窗口将走（即上端在此行）的区间就是此行的贡献区间，用差分维护即可。

数据结构用 `bitset` 就行了，然后发现它虽然有 `_Find_next`，但没有 `_Find_last`……遂手打。

复杂度 $\mathcal{O}\left(\frac{nm^2}{\omega}\right)$。

## 代码

`bitset` 你让我好调哇！！**记得左移的 1 开 ull！！！**

```cpp
const int N = 3e3 + 5, M = 1e5 + 5;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

namespace Main {
	int n, m, k;
	int a[N][N];
	int ans1; ll ans2;
	bool Line[N][N];
	int ans[N], nxt[M], cnt[M];
	void update (int x) { ans1 = max(ans1, x), ans2 += x; }
	int c[N];
	void add (int l, int r, int val) {
		if (l > r) return;
		c[l] += val, c[r + 1] -= val;
	}
//	bitset<N> b[M];
	
	struct mybitset {
		unsigned ll arr[N / 64 + 5];
		int test (int p) { return (arr[p >> 6] >> (p & 63)) & 1;}
		void set(int p, int v = 1) {
			if (v) arr[p >> 6] |= (1ull << (p & 63));
			else arr[p >> 6] -= (1ull << (p & 63));
		}
		int _Find_next(int p) {
			int a = p >> 6, b = p & 63;
			for (int i = b + 1; i < 64; ++i) if (arr[a] & (1ull << i)) return p - b + i;
			for (int i = a + 1; i <= N / 64; ++i) 
				if (arr[i]) 
					for (int j = 0; j < 64; ++j) 
						if (arr[i] & (1ull << j)) return (i << 6) + j;
			return n + 1;
		}
		int _Find_last(int p) {
			int a = p >> 6, b = p & 63;
			for (int i = b - 1; i >= 0; --i) if (arr[a] & (1ull << i)) return p - b + i;
			for (int i = a - 1; i >= 0; --i) 
				if (arr[i]) 
					for (int j = 63; j >= 0; --j) 
						if (arr[i] & (1ull << j)) return (i << 6) + j;
			return 0;
		}
	}b[M];

	void get_first_window() {
		int tot = 0;
		for (int i = 1; i <= k; i++) 
			for (int j = 1; j <= k; j++) if ((cnt[a[i][j]]++) == 0) tot++;
		update (ans[1] = tot);
		for (int i = 1; i <= n - k; i++) {
			for (int j = 1; j <= k; j++) tot -= ((--cnt[a[i][j]]) == 0);
			for (int j = 1; j <= k; j++) if ((cnt[a[i + k][j]]++) == 0) tot++;
			update(ans[i + 1] = tot);
		}


		for (int i = 1; i <= M - 5; i++) b[i].set(0), b[i].set(n + 1);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= k; j++) {
				b[a[i][j]].set(i);
			}
	}

	int main () {
		n = Read(), m = Read(), k = Read();
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][j] = Read();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) nxt[a[i][j]] = m + k + k;
			for (int j = m; j; j--) Line[i][j] = (nxt[a[i][j]] - j <= k), nxt[a[i][j]] = j;
		}
		get_first_window();
		//for (int i = 1; i <= n; i++) printf ("%d ", ans[i]); putchar(10);
		for (int j = 1; j <= m - k; j++) {
			for (int i = 1; i <= n; i++)
				if (!Line[i][j]) {
					int l = b[a[i][j]]._Find_last(i) + 1, r = b[a[i][j]]._Find_next(i) - 1;
					//printf ("[1]%d %d\n", l, r);
					add (max(l, i - k + 1), min(i, r - k + 1), -1);
					b[a[i][j]].set(i, 0);
				}
			for (int i = 1; i <= n; i++)
				if (!b[a[i][j + k]].test(i)) {
					int l = b[a[i][j + k]]._Find_last(i) + 1, r = b[a[i][j + k]]._Find_next(i) - 1;
					//printf ("[2]%d %d\n", l, r);
					add (max(l, i - k + 1), min(i, r - k + 1), 1);
					b[a[i][j + k]].set(i);
				}
			for (int i = 1; i <= n; i++) update(ans[i] += (c[i] += c[i - 1]))/*, printf ("%d ", ans[i]);putchar(10)*/;
			for (int i = 1; i <= n; i++) c[i] = 0;
		}
		printf ("%d %lld\n", ans1, ans2);
		return 0;
	}
}

int main () {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	Main::main();
	return 0;
}
```

---

