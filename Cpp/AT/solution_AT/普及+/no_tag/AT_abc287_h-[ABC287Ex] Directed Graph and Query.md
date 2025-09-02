# [ABC287Ex] Directed Graph and Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc287/tasks/abc287_h

$ N $ 頂点 $ M $ 辺の有向グラフがあります。頂点には $ 1 $ から $ N $ までの番号が付いており、$ i $ 番目の有向辺は頂点 $ a_i $ から頂点 $ b_i $ へと結ばれています。

また、このグラフ上の経路について、コストを次のように定めます。

- 経路上の頂点(始点・終点を含む)の番号の最大値
 
$ x=1,2,\ldots,Q $ に対して次の問題を解いてください。

- 頂点 $ s_x $ から頂点 $ t_x $ への経路のコストの最小値を求めよ。ただし、そのような経路が一つも存在しない場合は代わりに `-1` と出力せよ。
 
なお、入力の量が多くなる場合があるので、高速な方法で入出力を行うことを推奨します。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2000 $
- $ 0\ \leq\ M\ \leq\ N(N-1) $
- $ 1\ \leq\ a_i,b_i\ \leq\ N $
- $ a_i\ \neq\ b_i $
- $ i\ \neq\ j $ ならば $ (a_i,b_i)\ \neq\ (a_j,b_j) $
- $ 1\ \leq\ Q\ \leq\ 10^4 $
- $ 1\ \leq\ s_i,t_i\ \leq\ N $
- $ s_i\ \neq\ t_i $
- 入力はすべて整数
 
### Sample Explanation 1

$ x=1 $ に対しては、$ 1 $ 番目の辺を通って頂点 $ 1 $ から頂点 $ 2 $ へ行く経路のコストが $ 2 $ であり、これが最小です。 $ x=2 $ に対しては、$ 2 $ 番目の辺を通って頂点 $ 2 $ から頂点 $ 3 $ へ、そして $ 3 $ 番目の辺を通って頂点 $ 3 $ から頂点 $ 1 $ へ行く経路のコストが $ 3 $ であり、これが最小です。 $ x=3 $ に対しては、頂点 $ 1 $ から頂点 $ 4 $ への経路が存在しないため `-1` と出力します。

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 1
4 3
3
1 2
2 1
1 4```

### 输出

```
2
3
-1```

# 题解

## 作者：rui_er (赞：4)

心情不好，来刷点普及题放松放松。

考虑 Floyd 算法，常规实现中最外层循环枚举的 $k$ 就是路径上经过的点的最大编号（不包括两个端点）。问题等价于：对于每组询问 $(s_i,t_i)$，在 $k$ 取哪个值之后首次连通。

不难想到离线，对于每一个 $k$ 值，在更新完传递闭包之后枚举每个询问，如果符合条件就更新答案即可。另外由于是传递闭包问题，可以使用 bitset 进行优化。

复杂度 $\mathcal O(\frac{n^3}{\omega})$。

```cpp
// Problem: Ex - Directed Graph and Query
// Contest: AtCoder - UNIQUE VISION Programming Contest 2023 New Year (AtCoder Beginner Contest 287)
// URL: https://atcoder.jp/contests/abc287/tasks/abc287_h
// Memory Limit: 1024 MB
// Time Limit: 4500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
	uniform_int_distribution<int> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 2e3+5, M = 1e4+5;

int n, m, q, s[M], t[M], ans[M];
bitset<N> e[N];

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].set(v);
	}
	scanf("%d", &q);
	rep(i, 1, q) scanf("%d%d", &s[i], &t[i]);
	memset(ans, -1, sizeof(ans));
	rep(k, 1, n) {
		rep(i, 1, n) if(e[i].test(k)) e[i] |= e[k];
		rep(i, 1, q) if(ans[i] == -1 && e[s[i]].test(t[i])) ans[i] = max({s[i], t[i], k});
	}
	rep(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：CmsMartin (赞：2)

## 前言

这道题就是水爆了，哪有什么绿题蓝题紫题难度。

## 题解

考虑 **传递闭包**，使用 `std::bitset` 优化。

我们要找最小的点，所以可以外层枚举 $k = 1 \sim n$。然后将询问离线下来，考虑对于第 $i$ 个询问使得 $s_i,t_i$ 第一个联通的 $k_i$，那么答案就为 $\max\{s_i, t_i, k_i\}$。

然后就没了。

复杂度是 $\mathcal{O}(\frac{n^3}{w} + nq)$。能过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int N, M, Q;
bitset<2010> G[2010];
int S[10010], T[10010];
int Ans[10010];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		static int u, v;
		cin >> u >> v;
		G[u][v] = true;
	} 
	cin >> Q;
	for (int i = 1; i <= Q; i++) {
		cin >> S[i] >> T[i];
	}
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			if (G[i][k]) {
				G[i] |= G[k];
			}
		}
		for (int i = 1; i <= Q; i++) {
			if (G[S[i]][T[i]] && Ans[i] == 0) {
				Ans[i] = max({S[i], T[i], k});
			}
		}
	}
	for (int i = 1; i <= Q; i++) {
		cout << (Ans[i] == 0 ? -1 : Ans[i]) << endl;
	}
	return 0;
} 
```

---

## 作者：yhylivedream (赞：1)

我们注意到 floyd 处理传递闭包时的状态为 $f_{k,i,j}$ 表示只使用 $1\sim k$ 的点 $i$ 到 $j$ 是否联通，所以我们对于每个询问，找到最小的 $k$ 使得 $f_{k,s_x,t_x}$ 为 $1$ 即可。

但 $n\le 2000$，$O(n^3)$ 过不了，考虑用 bitset 处理即可。

空间有可能会爆，可以离线。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2005, kMaxM = 1e5 + 5;

int n, m, q, s[kMaxM], t[kMaxM], ans[kMaxM];
bitset<kMaxN> f[kMaxN];

signed main() {
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    f[x].set(y);
  }
  cin >> q;
  for (int i = 1; i <= q; i++) {
    cin >> s[i] >> t[i], ans[i] = -1;
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      if (f[i][k]) {
        f[i] |= f[k];
      }
    }
    for (int i = 1; i <= q; i++) {
      if (!~ans[i] && f[s[i]][t[i]]) {
        ans[i] = max({s[i], t[i], k});
      }
    }
  }
  for (int i = 1; i <= q; i++) {
    cout << ans[i] << '\n';
  }
}
```

---

## 作者：small_john (赞：1)

## 思路

假设对于两个点 $s_i,t_i$，在不考虑路径起点终点的情况下，最小的成本为 $x$，那么只经过编号 $1\sim x$ 的点一定能使 $s_i,t_i$ 联通。所以问题就变成了求满足上述条件的最小的 $x$。

有向图的连通性问题，很容易想到传递闭包。不会的[出门左转](https://www.luogu.com.cn/problem/B3611)。

考虑传递闭包的过程，第一步就是枚举中转点。而如果我们从小到大枚举，刚好枚举了一个前缀，与上面的条件对应。

具体的做法也很简单，先离线。在做传递闭包的过程中，如果枚举中转点 $k$ 之后 $s_i,t_i$ **第一次**联通，那么这个询问的答案就是 $\max(s_i,t_i,k)$。

传递闭包采用 bitset 优化，时间复杂度 $O(\frac {n^3}{\omega}+nq)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 2e3+5,M = 1e4+5;
int n,m,s[M],t[M],ans[M],q;
bitset<N> e[N];
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m);
	for(int i = 1,u,v;i<=m;i++)
		read(u),read(v),e[u][v] = 1;
	read(q);
	for(int i = 1;i<=q;i++)
		read(s[i]),read(t[i]),ans[i] = -1;
	for(int k = 1;k<=n;k++)
	{
		for(int i = 1;i<=n;i++)
			if(e[i][k]) e[i]|=e[k];
		for(int i = 1;i<=q;i++)
			if(e[s[i]][t[i]]&&ans[i]==-1) ans[i] = max({s[i],t[i],k});
	}
	for(int i = 1;i<=q;i++)
		writen(ans[i]);
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：1)

Ex < G < F（确信。

考虑 Floyd。

注意到 Floyd 的最外层循环 $k = 1\dots n$ 是枚举用到 $1\sim k$ 个点。

因此我们直接跑一遍 Floyd，每次跑完一次外层循环就扫一遍询问更新答案。

但你发现这个会超时，用 `bitset` 优化即可。

代码：[提交记录](https://atcoder.jp/contests/abc287/submissions/38437676)。

---

## 作者：dingyyds11111 (赞：0)

### 前置知识：

`Floyd` 传递闭包。

[点击传送 oi-wiki](https://oi.wiki/graph/shortest-path/#floyd-%E7%AE%97%E6%B3%95)

### 思路

因为要求从点 $s_x$ 到 $t_x$ 最小的点，多次询问，所以每个答案具有传递性，使用传递闭包 + `bitset` 优化。

第一层枚举最大点 $k$，如果点 $i$ 与 $k$ 相通，则更新。对于第一个联通的 $k$，$Ans_i = \max (s_i, t_i, k)$。复杂度为 $\Theta(\frac{n ^ 3}{\omega})$，时限 $4.5$ 秒，可以通过。

### 实现代码

```cpp
#include <bits/stdc++.h>
#define db double
#define all(x) (x).begin(), (x).end()

using namespace std;
bitset<2005> g[2005];
int a[10005], b[10005], ans[20005];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		g[x][y] = 1;
	}
	int q;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		cin >> a[i] >> b[i];
	}
	for (int k = 1; k <= n; k ++) {
		for (int i = 1; i <= n; i++) {
			if (g[i][k]) {
				g[i] |= g[k];
			}

		}
		for (int i = 1; i <= q; i++) {
			if (g[a[i]][b[i]] && ans[i] == 0) {
				ans[i] = max(max(k, a[i]), b[i]);
			}
		}
	}
	for (int i = 1; i <= q; i++) {
		if (ans[i] == 0) {
			cout << "-1" << endl;
		}
		else {
			cout << ans[i] << endl;
		}
	}
	return 0;
}

```

---

## 作者：xrtbclx (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/AT_abc287_h)

### 题目描述：
给点一个 $N$ 个点，$M$ 条边的有向图，求从 $s_x$ 到 $t_x$ 的最短路。

### 思路：
由于 $s_x$ 不一定都相等，所以应采用全源最短路（如 Floyd）。由于~~作者只会 Floyd~~，所以本题解着重介绍 Floyd。

### 关于 Floyd:
Floyd 是一种 **$O(n^3)$、不可处理负环的全源最短路算法**。其核心思想就是动态规划，枚举起点、终点和“途经点”，来计算出最短路。
#### Floyd核心代码：

```cpp
for (int k = 1; k <= n; k++)
{
	for (int x = 1; x <= n; x++)
	{
		for (int y = 1; y <= n; y++)
		{
			dis[x][y] = min(dis[x][y], dis[x][k] + dis[k][y]);
		}
	}
}
 
```

---

