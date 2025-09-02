# Yunli's Subarray Queries (hard version)

## 题目描述

这是问题的困难版本。在此版本中，保证所有查询的 $r\geq l+k-1$。

对于任意数组 $b$，Yunli 可以执行以下操作任意次数：

- 选择一个索引 $i$。设置 $b_i=x$，其中 $x$ 是她想要的任何整数（$x$ 不限于区间 $[1,n]$）。

将 $f(b)$ 表示为她需要执行的最小操作数，直到 $b$ 中存在长度至少为 $k$ 的连续子数组$^{\text{*}}$。

Yunli 收到一个大小为 $n$ 的数组 $a$，并询问 $q$ 次。在每次查询中，你需要计算 $\sum_{j=l+k-1}^{r}f([a_l,a_{l+1},\ldots,a_j])$。

$^{\text{*}}$ 如果存在一个长度为 $k$ 的连续子数组，从索引 $i$ 开始（$1\leq i\leq |b|-k+1$），那么对于所有 $i<j\leq i+k-1$，$b_j=b_{j-1}+1$。

## 说明/提示

在第一组测试用例的第二次查询中，我们计算了以下函数值：

- $f([2,3,2,1,2])=3$，因为 Yunli 可以设置 $b_3=4$、$b_4=5$ 和 $b_5=6$，从而在 $3$ 次操作中形成一个大小为 $5$ 的连续子阵列。
- $f([2,3,2,1,2,3])=2$，因为我们可以设置 $b_3=0$ 和 $b_2=-1$，在 $2$ 次操作中中（从位置 $2$ 开始）形成一个大小为$5$的连续子阵列。

这个查询的答案是 $3+2=5$。

翻译 @Cure_Wing。

## 样例 #1

### 输入

```
3
7 5 3
1 2 3 2 1 2 3
1 7
2 7
3 7
8 4 2
4 3 1 1 2 4 3 2
3 6
1 5
5 4 2
4 5 1 2 3
1 4
1 5```

### 输出

```
6
5
2
2
5
2
3```

# 题解

## 作者：Super_Cube (赞：6)

# Solution

设 $b_i=f([a_i,a_{i+1},\ldots,a_{i+k-1}])$，那么答案为 $\displaystyle\sum_{i=l}^{r-k+1}\min_{j=l}^ib_j$。

对 $a$ 中所有数执行 $a_i\gets a_i-i$，那么原问题（修改最少的数使得区间变为公差为 $1$ 的递增数列）变为了新问题：修改最少的数使得区间所有数相等。肯定把非区间众数改为区间众数是最优的，所以 $b_i$ 即为 $k$ 减区间 $[i,i+k-1]$ 中众数的出现次数。

由于 $k$ 为定值，可利用类似滑动窗口的模式预处理出 $b_i$。

对于询问，先使 $r\gets r-k+1$，答案即为 $\displaystyle\sum_{j=l}^r\min_{i=l}^jb_i$。

如何计算？找到 $x\in[l,r]$ 使得 $b_x=\displaystyle\min_{i=l}^rb_i$，那么对于 $j\ge x$ 的贡献为 $b_x(r-x+1)$。关于 $j<x$ 的部分？设 $f_{l,r}$ 表示左端点为 $l$，右端点在 $[l,r]$ 的贡献，所以 $i<x$ 部分即为 $f_{l,x-1}$。

现在的需求是快速算任意 $f_{l,r}$。利用单调栈找到 $suf_i$ 为从 $i$ 开始往后第一个小于 $b_i$ 的位置，对于 $[l,suf_l)$ 的最小值都为 $b_l$，于是 $f_{l,r}=b_l(suf_l-l)+f_{suf_l,r}$。发现转移与 $r$ 无关，直接去掉：$f_l=b_l(suf_l-l)+f_{suf_l}$。现在的 $f_l-f_r$ 就是原来的 $f_{l,r-1}$。

所以答案为 $b_x(r-x+1)+f_l-f_x$。

---

## 作者：冷却心 (赞：3)

> 对于一个满足条件的数组 $\{a\}$，我们对每个数加上 $n-i$ 那么就可以得到一个新数组 $\{b\}$，其中 $b_i=a_i+n-i$，因为 $a_i+1=a_{i+1}$，那么：
>
> $$\begin{aligned}b_i&=a_i+n-i,\\b_{i+1}=a_{i+1}+n-(i+1)&=a_i+1+n-i-1=a_i+n-i,\\ b_i=b_{i+1}\end{aligned}$$
>
> 也就是 $b$ 数组完全相同。所以对于一个并不满足条件的长度为 $l$ 的数组，如果对它进行以上的变换之后，众数的个数是 $k$，则把它合法化的最少操作次数就是 $l-k$。
 
首先我们发现这道题是静态的。我们记 $g_i$ 表示把子数组 $a_i,a_{i+1},\cdots,a_{i+k-1}$ 这一段合法化的最小操作次数。这比较类似一个滑动窗口，根据上面引用内的性质，我们可以用一个 `map` 或者权值线段树 $O(n\log n)$ 求出所有的 $g_i$。所以题目定义的函数就是：

$$f([a_l,a_{l+1},\cdots,a_r])=\min_{i=l}^{r-k+1} g_i.$$

即取这么多子区间中最小的一个答案。所以对于一次询问 $l, r$，要求的和式就是：

$$\text{Answer}=\sum_{i=l+k-1}^{r}\min_{j=l}^{i-k+1} g_j=\sum_{i=l}^{r-k+1}\min_{j=l}^i g_j.$$

即一个从 $l$ 开始的前缀最小值连续和。我们发现这个并不好维护。我们考虑一个答案 $g_i$ 能影响到的区间。首先我们发现，对于某一个 $g_i$，它能影响到的区间最远可以到达下一个比他小的 $g_j$ 之前（或者数组结尾）。那么我们处理一个 $\{p\}$ 数组，$p_i$ 表示下一个小于 $g_i$ 的数的位置（如果没有则为 $n+1$），这个可以单调栈 $O(n)$ 求出。然后思考如何求答案。

设当前询问左右端点分别为 $x,y$，而前缀求值的右端点是 $y-k+1$，我们不妨把 $y$ 赋值为它。我们使用一个变量 $t$，表示当前位置，一开始为 $x$。那么前缀最小值为它的区间就是从 $t$ 到 $p_t-1$ 的区间，对答案的贡献是 $g_t\times (p_t-t)$，然后把 $t:= p_t$ 向后跳。直到跳到右端点 $y$。然后贡献直接累加后输出即可。

暴力跳是 $O(n)$ 的，可以使用倍增变成预处理 $O(n\log n)$，查询 $O(\log n)$。

总时间复杂度是 $O(n\log n)$。


```cpp
#include <bits/stdc++.h>
#define LL long long
#define int long long
using namespace std;
const int N = 5e5 + 10;
int n, K, Q, A[N], ret[N];
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
int tree[N << 2];
void pushup(int p) { tree[p] = max(tree[ls(p)], tree[rs(p)]); }
void build(int p, int l, int r) {
	tree[p] = -1e9; if (l == r) return ;
	int mid = (l + r) >> 1; build(ls(p), l, mid); build(rs(p), mid + 1, r);
	return ;
}
void update(int p, int l, int r, int x, int k) {
	if (x > r || x < l) return ;
	if (l == r) { 
		if (tree[p] == -1e9) tree[p] = 0; 
		tree[p] += k; 
		if (tree[p] == 0) tree[p] = -1e9;
		return ;
	}
	int mid = (l + r) >> 1; update(ls(p), l, mid, x, k); update(rs(p), mid + 1, r, x, k);
	pushup(p); return ;
}
int stk[N], tp = 0, fa[N][20]; LL sum[N][20];
signed main() {
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	while (_ --) {
		cin >> n >> K >> Q;
		for (int i = 1; i <= n; A[i] += n - i, i ++) cin >> A[i];
		build(1, 1, n * 2);
		for (int i = 1; i < K; i ++) update(1, 1, n * 2, A[i], 1);
		for (int i = 1; i <= n - K + 1; i ++) {
			update(1, 1, n * 2, A[i + K - 1], 1); ret[i] = K - tree[1]; update(1, 1, n * 2, A[i], -1);
		} tp = 0; ret[n - K + 2] = -1;
		for (int i = 1; i <= n - K + 2; i ++) {
			while (tp && ret[stk[tp]] >= ret[i]) {
				fa[stk[tp]][0] = i; sum[stk[tp]][0] = 1ll * (i - stk[tp]) * ret[stk[tp]]; tp --;
			} stk[++ tp] = i;
		}fa[n - K + 2][0] = n - K + 2; sum[n - K + 2][0] = 0;
		for (int k = 1; k <= 19; k ++) for (int i = 1; i <= n - K + 2; i ++)
			fa[i][k] = fa[fa[i][k - 1]][k - 1], sum[i][k] = sum[i][k - 1] + sum[fa[i][k - 1]][k - 1];
		int x, y;
		while (Q --) {
			cin >> x >> y;
			LL Ans = 0; int cur = x; y = y - K + 1;
			for (int i = 19; i >= 0; i --) if (fa[cur][i] <= y)
				Ans += sum[cur][i], cur = fa[cur][i];
			Ans += (y - cur + 1) * ret[cur]; cout << Ans << "\n";
		}
	}
	return 0;
}
```

---

## 作者：PNNNN (赞：3)

### G1

题目要求，对于一个子区间 $a_{l\sim l+k-1}$，最少要进行多少次单点修改，才能使 $\forall \  l < i \leq l+k-1,a_i=a_{i-1}+1$，其中 $k$ 是固定的。

对于这种问题，我们通常有一个 trick：将 $a_i$ 变为 $a_i-i$。这样的话，我们要求的答案就变为了 $k$ 减去变化后的 $a_{l\sim l+k-1}$ 中众数的出现次数。这个可以用线段树或者莫队做。

以下是线段树的代码，为了避免出现 $a_i < 0$，这里将 $a_i$ 变为了 $a_i-i+n$。

[代码](https://codeforces.com/contest/2009/submission/284650406)

时间复杂度为 $O(n\times\log n)$。

### G2
我们先用 G1 的方法求出 $f(\{a_i,a_{i+1},\dots, a_{i+k-1}\})$，并设其为 $w_i$。

与 G1 不同，G2 要求的的是 $\sum \limits_{i=l}^{r-k+1} \min \limits_{j=l}^{i} w_j$，其中 $r \geq l+k-1$。

看到对一段前缀取最小值，我们考虑如何模拟出这一过程。设 $p_0=l$，每次往后找到离 $p_0$ 最近的满足 $w_{p_0} > w_p$ 的 $p$，此时 $\min \limits_{j=l}^{i} w_j=w_{p_0}(p_0\le i\le p - 1)$，这段对答案的贡献为 $(p-p_0)\times w_{p_0}$ ，再将 $p_0$ 设为 $p$。不断这样做下去，直到 $p_0$ 后已经没有 $w_{p_0}>w_p$ 或者 $p_0>r-k+1$。

我们不可能每次询问都这样暴力做一次，考虑如何优化。显然，对于每个 $p_0$，其后最近的满足 $w_{p_0} > w_p$ 的 $p$ 都是不变的。考虑提前将每个 $p_0$ 的 $p$ 求出来，这个可以用单调栈求。然后我们需要用到另一个 trick：将 $p$ 向 $p_0$ 连一条长度为 $(p-p_0)\times w_{p_0}$ 的边，这样连出来一定是棵树。（我也不太清楚这个 trick 的名字，可能跟 AC 自动机的优化差不多。）

这样我们可以在树上二分出最后一个不大于 $r-k+1$ 的 $p_0$。具体实现：先一遍 dfs 将 $dep_i$ 和 $dis_i$ 求出，其中 $dep_i$ 表示 $i$ 的深度，$dis_i$ 表示 $i$ 到根节点（为了方便设为 $n-m+2$）的距离。接着将二分的左起始点设为 $1$，右起始点设为 $dep_l$，判断 $l$ 在树上的 $dep_l-mid$ 级祖先是否小于等于 $r-k+1$，移动 $l$ 和 $r$ 进行二分，设二分出来的答案为 $res$。这时答案就为 $dis_l-dis_{res}+(r-k-res+2)\times w_{res}$。

[代码](https://codeforces.com/contest/2009/submission/279915573)

我的树上 k 级祖先是用重链剖分求的，因此时间复杂度为 $O(n\times \log^2 n)$。可以将重链剖分换成长链剖分之类的，时间复杂度可以降到 $O(n\times\log n)$。或许可以直接上历史和线段树?

### G3
G3要求的东西变为了 $\sum \limits_{i=l}^{r-k+1} \sum \limits_{j=i}^{r-k+1} \min \limits_{g=i}^{j} w_g$。类似这种式子套上[P3246 [HNOI2016] 序列](https://www.luogu.com.cn/problem/P3246)的方法就行了。不知道能否将G2的方法继续扩展到G3，我还没想出来，如果可以的话还请告诉我！

这里仅仅贴一份用莫队实现的代码，具体思路还请参考 [P3246 [HNOI2016] 序列](https://www.luogu.com.cn/problem/P3246) 的题解：

[代码](https://codeforces.com/contest/2009/submission/280066658)

---

## 作者：rainygame (赞：2)

\*2200 的题不知道场上能不能做出来……

首先考虑 $f$ 函数的本质是什么。考虑设 $b_i=a_i-i$，那么 $f([a_i,a_{i+1},\dots,a_{i+k-1}])$ 的值即为 $k$ 减去 $b_{i\sim i-k+1}$ 的众数出现次数。

设 $c_i$ 表示 $f([a_i,a_{i+1},\dots,a_{i+k-1}])$（这可以使用 `map` 和 `multiset` $O(n \log n)$ 求出）。可以发现询问的答案即为 $\sum\limits_{i=l}^{r-k+1}\min\limits_{j=l}^ic_j$。

令 $r\leftarrow r-k+1$。对于前缀最小值一类的问题，假设现在已经计算了 $[l,i)$ 部分的答案，那么可以找到最小的 $j$ 使得 $j > i$ 且 $c_i<c_j$。然后计算出 $[i,j)$ 的贡献（本题为 $(j-i)\times c_i$），并令 $i \leftarrow j$。一直做直到 $j > r$ 为止。

注意到每个数的下一个比它小的数的位置是固定的。使用倍增优化即可。时间复杂度 $O((n+q) \log n)$。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200005
#define MAXK 18

int t, n, k, q;
int a[MAXN], c[MAXN];
int f[MAXN][MAXK], s[MAXN][MAXK];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	for (cin >> t; t; --t){
		cin >> n >> k >> q; for (int i(1); i<=n; ++i) cin >> a[i], a[i] -= i; map<int, int> mp; multiset<int, greater<int>> mst;
		for (int i(1); i<=k; ++i) ++mp[a[i]]; for (auto i: mp) mst.insert(i.second); c[1] = k-*mst.begin(); n = n-k+1;
		for (int i(2); i<=n; ++i){
			if (mst.find(mp[a[i-1]]) != mst.end()) mst.erase(mst.find(mp[a[i-1]])); if (--mp[a[i-1]]) mst.insert(mp[a[i-1]]);
			if (mst.find(mp[a[i+k-1]]) != mst.end()) mst.erase(mst.find(mp[a[i+k-1]])); mst.insert(++mp[a[i+k-1]]); c[i] = k-*mst.begin();
		}
		stack<int, vector<int>> st;
		for (int i(n); i; --i){
			while (st.size() && c[st.top()] >= c[i]) st.pop();
			f[i][0] = st.size() ? st.top() : n+1; s[i][0] = (f[i][0]-i)*c[i]; st.push(i);
		}
		for (int i(0); i<MAXK; ++i) f[n+1][i] = n+1;
		for (int j(1); j<MAXK; ++j) for (int i(1); i<=n; ++i){
			f[i][j] = f[f[i][j-1]][j-1]; s[i][j] = s[i][j-1]+s[f[i][j-1]][j-1];
		}
		for (int l, r; q; --q){
			cin >> l >> r; r = r-k+1; int res(0);
			for (int i(MAXK-1); ~i; --i) if (f[l][i] <= r) res += s[l][i], l = f[l][i];
			cout << res+(r-l+1)*c[l] << '\n';
		}
	}
	
	return 0;
}

```

---

