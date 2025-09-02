# 指定区间和

## 题目描述

给你一个整数 $N$ 和 $M$ 个整数三元组 $(L_i,R_i,S_i)$。

判断是否存在一个长度为 $N$ 的**正整数**数列 $A$，满足对于所有的三元组限制 $(L_i,R_i,S_i)$，满足 $\sum\limits_{j=L_i}^{R_i}A_j=S_i$。如果存在，找出合法的 $A$ 的最小元素和。

## 说明/提示

**样例 1 解释**

$A=(1,3,2,1,5)$ 是一种符合条件的情况。\
此情况下 $A$ 的和是 $12$，可以证明这是可能的最小值。

**样例 2 解释**

此时无解。

By chenxi2009

## 样例 #1

### 输入

```
5 3
1 2 4
2 3 5
5 5 5```

### 输出

```
12```

## 样例 #2

### 输入

```
1 2
1 1 1
1 1 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
9 6
8 9 8
3 6 18
2 4 19
5 6 8
3 5 14
1 3 26```

### 输出

```
44```

# 题解

## 作者：XXh0919 (赞：4)

来纪念一下第二次做出 G 题（第一次是 [ABC293G](https://atcoder.jp/contests/abc293/submissions/61765477)，当时作为的学情考察题）。

### 题意

给你三个长度为 $M$ 的序列 $L=(L_1,L_2,L_3,...,L_M)$，$R=(R_1,R_2,R_3,...,R_M)$，$S=(S_1,S_2,S_3,...,S_M)$，要求构造一个长度为 $N$ 的**正整数序列** $A$，使其满足下面的式子：

$$\sum_{j=L_i}^{R_i}A_j=S_i$$

如果能构造出来，输出找到的所有可能的 $A$ 中总和最小的那个，否则输出 $-1$。

### 解法

首先注意到这个式子，不妨用前缀和将其代替。令 $s_i=\sum_{j=1}^{i}A_j$，则原式变为

$$s_{R_i}-s_{L_i-1}=S_i$$

这看着咋感觉有点熟悉？我们将这个式子再变个形：

$$s_{R_i}-s_{L_i-1}\le S_i$$
$$s_{L_i-1}-s_{R_i}\le -S_i$$

这不就是差分约束吗！那么我们继续来看，因为我们要构造的是正整数序列，所以一定有 $A_i>0$，即 $A_i\ge1$，所以所一定也有 $s_i-s_{i-1}\ge1$，即 $s_{i-1}-s_i\le-1$，那么这样我们就把图建出来了，然后再跑一遍 SPFA 找负环，找到就输出 $-1$，否则正常输出答案就行了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 15, inf = 1e18;

int n, m;
int head[N], to[N], nxt[N], val[N], idx;//链式前向星
int cnt[N];
bool vis[N];
int dis[N];

void add (int u, int v, int w) {
	to[idx] = v;
	val[idx] = w;
	nxt[idx] = head[u];
	head[u] = idx ++;
}

void spfa () {
    queue<int> q;
    memset (dis, inf, sizeof dis);
    memset (vis, false, sizeof vis);
    memset (cnt, 0, sizeof cnt);
    dis[0] = 0;
    q.push (0);
    vis[0] = true;
    //从 0 号开始：因为前缀和数组默认从 0 号开始累加
    while (!q.empty ()) {
        int u = q.front();
        q.pop ();
        vis[u] = false;
        cnt[u] ++;
        if (cnt[u] > n + 1) {
            puts ("-1");
            return ;
        }
        for (int i = head[u]; i != -1; i = nxt[i]) {
        	int v = to[i], w = val[i];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    cout << -dis[n] << endl;
    //因为建边的时候是从 i-1 到 i 建了一条权为 -1 的边，这与我们本来的约束方向是相反的，所以输出 -dis[n]
}

signed main () {
	memset (head, -1, sizeof head);
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
    	add (i - 1, i, -1);
    }
    for (int i = 1; i <= m; ++ i) {
        int l, r, s;
        cin >> l >> r >> s;
        add (r, l - 1, s);
        add (l - 1, r, -s);
    }
    spfa ();
    return 0;
}
```
求个赞，不过分吧？

---

## 作者：Walrus (赞：2)

差分约束板子。

做这道题前保证你会 P5960。

哦对了主题库里有道叫「糖果」的差分约束题你也理应会做。

## Solution

定义 $sum_i=\sum\limits_{j=1}^i a_j$。

考虑对于每条约束 $(L,R,S)$：

$$\sum\limits_{i=L}^Ra_i=S$$

也即 $sum_r-sum_{l-1}=S$。

这是差分约束的经典形式的变形，将此条件转化为：

$$sum_r-sum_{l-1}\leq S \And sum_r-sum_{l-1}\geq S$$

就变为了约束的一般形式。

并且注意到题目中说 $a_i\in N^*$，则有条件 $sum_i-sum_{i-1}\geq 1$。

按上述条件建边，答案即为 $sum_n$ 的最小值，考虑建反图跑最长路即可。

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr)
#define rep(i, j, k) for (int i = j; i <= k; ++i)
#define pre(i, j, k) for (int i = j; i >= k; --i)
#define PII pair<int, int>
#define fi first
#define se second
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define inf 0x3fffffff
#define iv inline void
#define il inline int
#define ic inline char
#define int long long

//#define getchar getchar_unlocked
//#define putchar putchar_unlocked

using LL = long long;
using i64 = __int128;
using namespace std;

const int N = 4e3 + 5;
const int mod = 998244353;

#define cmax(a, b) (a = a > b ? a : b)
#define cmin(a, b) (a = a < b ? a : b)
#define cadd(a, b) (a = ((a + b) % mod + mod) % mod)
#define cdel(a, b) (a = ((a - b) % mod + mod) % mod)

int n, m, l, r, s, ans, vis[N], dis[N], cnt[N];
vector<PII> e[N];

void spfa(int s) {
	queue<int> q;
	memset(dis, 0xcf, sizeof dis);
    dis[s] = 0, q.push(s);
    while (q.size()) {
        int x = q.front();
        q.pop();
        vis[x] = 0, ++cnt[x];
        if (cnt[x] > n + 1) cout << -1, exit(0);
        for (auto ed : e[x]) {
        	int y = ed.fi, z = ed.se;
        	if (dis[y] < dis[x] + z) {
                dis[y] = dis[x] + z;
                if (!vis[y]) q.push(y), vis[y] = 1;
            }
		}
    }
}

signed main() {
    FASTIO;
    cin >> n >> m;
    rep(i, 1, m) cin >> l >> r >> s, e[l - 1].pb({r, s}), e[r].pb({l - 1, -s});
    rep(i, 1, n) e[i - 1].push_back({i, 1});
    spfa(0);
    cout << dis[n];
    return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 思路

题目要求一些区间里所有数的和相同。

可以考虑把原数组变成前缀和数组。令前缀和数组为 $s$，那么，可以找到 $s_{L_i-1}$ 和 $s_{R_i}$ 间的差为 $S_i$。

有多个关系，考虑直接用差分约束来处理。

我们把 $s_{R_i}-s_{L_i-1}=S_i$ 转换为：

$$s_{R_i}-s_{L_i-1} \ge S_i$$

$$s_{R_i}-s_{L_i-1} \le S_i$$

注意到第二个式子并不好差分约束，我们给他两边乘上一个负数让小于等于变成大于等于：

$$s_{L_i-1}-s_{R_i} \ge -S_i$$

当然，为了让原数组的每个数是正数，我们还得到一个式子：

$$s_{i-1}-s_{i} \ge -1$$

接下来就直接按照这两个不等式关系建图，然后跑一次最短路检查有没有负环即可，最后得到的显然是负数，乘上 $-1$ 就可以了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 1000010,M = 3000010;
long long h[N], e[M], w[M], ne[M], idx;
long long dist[N];
bool st[N];
long long n,m;
void add(long long a, long long b, long long c){
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}
long long cnt[N];
bool spfa(){
	queue<long long>q;
	memset(dist,0x3f,sizeof dist);
	dist[0] = 0;
	st[0] = 1;
	q.push(0);
	while (!q.empty()){
		long long t = q.front();
		q.pop();
		st[t] = 0;
		if (cnt[t] >= n){
			return 0;
		}
		cnt[t] ++ ;
		for (long long i = h[t]; ~i; i = ne[i]){
			long long j = e[i];
			if (dist[j] > dist[t] + w[i]){
				dist[j] = dist[t] + w[i];
				if (!st[j]){
					q.push(j);
					st[j] = 1;
				}
			}
		}
	}
	return 1;
}
int main(){
	cin >> n >> m;
	memset(h, -1, sizeof h);
	while (m -- ){
		long long a,b,c;
		cin >> a >> b >> c;
		//s_b-s_{a-1}=c
		//s_b-s_{a-1}>=c
		//s_{a-1}-s_b>=-c
		add(a - 1,b,-c);
		add(b,a - 1,c);
	}
	for (long long i = 1; i <= n; i ++ ){
		add(i - 1,i,-1);
	}
	if (spfa()){
		cout << -dist[n];
	}
	else{
		cout << -1;
	}
	return 0;
}
```

---

## 作者：Clover_Lin (赞：1)

## 前言
点击[这里](https://blog.csdn.net/ArmeriaLeap/article/details/147687946)查看我的博客！

赛时想到了差分约束，随手写了个 SPFA 结果挂的很惨……还是太菜了，赛后 Bellman-Ford 又调了半天。
## 题目大意
给定整数 $N,M$ 和长度为 $M$ 的三个整数序列 $L=(L_1,L_2,\dots,L_M),R=(R_1,R_2,\dots,R_M),S=(S_1,S_2,\dots,S_M)$。请判断是否存在一个长度为 $N$ 的**正整数**序列 $A$ 满足 $\forall 1\le i\le M,\sum_{j=L_i}^{R_i}A_j=S_i$。如果存在输出序列所有元素之和的最小值，否则输出 `-1`。
## 思路
我们不妨令 $s_i$ 表示 $\sum_{j=1}^i A_i$，所以 $\forall 1\le i\le M,s_{R_i}-s_{L_i-1}=S_i$。很自然地想到差分约束（例题：[洛谷 P1993 小 K 的农场](https://www.luogu.com.cn/problem/P1993)），即利用最长路中**如果 $x$ 向 $y$ 连一条边权为 $w$ 的边，那么满足 $y\ge x+w$** 的性质解不等式。

关于差分约束的详细内容本文不再过多讲解，请自行搜索学习。

本题显然要跑最长路。我们来想一想，都需要连哪些边：
- $L_i-1\to R_i$，边权为 $S_i$。
- $R_i\to L_i-1$，边权为 $-S_i$。
- $i-1\to i$，边权为 $1$。

所以，我们建了这样一张图，以 $0$ 为源点跑 **Bellman-Ford** 最长路即可。（注：作者赛时使用 SPFA 挂的很惨，如果您知道为什么这道题只能使用 Bellman-Ford 或者 SPFA 需要注意什么，可以在评论区中回复！）

那么答案就是 $s_n$，即 $0$ 到 $n$ 的最长路。

现在分析无解情况：
- 该图中存在负环情况。
- $S_i<R_i-L_i+1$ 的时候也不满足条件。
- $s_n$ 为负无穷。
## 代码
提交记录：[这里](https://atcoder.jp/contests/abc404/submissions/65479660)。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n, m;
long long dis[5010];
int vis[5010];
int sum[5010];

struct edge
{
	int x, y, w;
} ;

vector<edge> e;

void add(int x, int y, int w)
{
	e.push_back((edge){x, y, w});
}

bool bellman_ford(int s)
{
	memset(dis, -0x3f, sizeof(dis));
	dis[s] = 0;
	for (int i = 0; i <= n; i++)
	{
		bool flag = false;
		for (int j = 0; j < e.size(); j++)
		{
			int x = e[j].x;
			int y = e[j].y;
			int w = e[j].w;
			if (dis[x] >= -1e17 && dis[y] < dis[x] + w)
			{
				dis[y] = dis[x] + w;
				flag = true;
			}
		}
		if (!flag) return false;
	}
	return true;
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		if (w < v - u + 1)
		{
			cout << "-1" << endl;
			return 0;
		}
		int t = w - (v - u + 1);
		add(v, u - 1, -w);
		add(u - 1, v, w);
//		cout << u - 1 << " " << v << endl;
	}
	for (int i = 1; i <= n; i++)
		add(i - 1, i, 1);
	if (bellman_ford(0) || dis[n] <= -1e17)
		cout << "-1" << endl;
	else
	{
//		for (int i = 0; i <= n; i++)
//			cout << dis[i] << " ";
//		cout << endl; 
		long long minn = 0;
		for (int i = 1; i <= n; i++)
			minn = min(minn, dis[i]);
		cout << dis[n] << endl;
	}
	return 0;
}
```
## 总结
这次的 G 很水，难度顶多 $\color{green}普及+/提高$，思维难度和代码实现难度都不是很高。
## 求助
作者赛时使用 SPFA 挂的很惨，如果您知道为什么这道题只能使用 Bellman-Ford 或者 SPFA 需要注意什么，可以在评论区中回复！

---

## 作者：LostKeyToReach (赞：1)

我们令 $A$ 序列 $1 \sim i$ 的和为 $P_i$，那么要让 $P_{R_i} - P_{L_i - 1} = S_i$，这个条件等价于 $P_{R_i} - P_{L_i - 1} \le S_i$ 且 $ P_{L_i - 1} - P_{R_i} \le - S_i$，同时为了保证 $A$ 序列为正整数序列，我们还要求 $P_{i} - P_{i + 1} \le -1$，那么就是一个差分约束问题，直接建完图跑 SPFA 就行了，时间复杂度 $\mathcal{O}(nm)$。

---

## 作者：Exscallop64_ (赞：1)

# AtCoder abc404_g

## 题目简述

给定 $m$ 个三元组限制条件，第 $i$ 组条件形如 $(L_i,R_i,S_i)$，同时给定一个正整数 $n$。

判断是否存在一个长度为 $n$ 的正整数序列 $a_1,a_2,\dots,a_n$ 满足以下条件。若存在，输出序列 $a$ 的最小总和。

+ 对于所有的 $i$（$1 \le i \le m$）满足 $\sum_{j=L_i}^{R_i} a_j = S_i$。

## 思路

我们不妨先转换题意。

令 $X_i = \sum_{j=1}^{i} a_j$（$1 \le i \le n$）。

则题目变为：

你需要判断是否存在正整数序列 $X_0,X_1,\dots,X_n$ 满足以下三个条件，如果存在，则需最小化 $X_n$。

1. 对于所有的 $i$（$1 \le i \le m$）满足 $X_{R_i} - X_{L_i - 1} = S_i$。

2. $X_j - X_{j-1} \ge 1$（$1 \le j \le n$）。

3. $X_0 = 0$。

注意，因为题目要求构造出的序列是**正整数序列**，因此需要满足$X_j - X_{j-1} \ge 1$（$1 \le j \le n$）。因为 $X$ 序列为 $a$ 序列的前缀和序列，因此需要**强制要求** $X_0 = 0$。 

前两个条件显然可以用[差分约束](https://oi-wiki.org//graph/diff-constraints/)求解，以下是使用差分约束的过程。

### 建图

首先需要建出差分约束系统的图。

我们将 $X_{R_i} - X_{L_i-1} = S_i$ 转换为以下不等式组：

$$
\begin{cases}
X_{R_i} - X_{L_i-1} \le S_i\\
X_{R_i} - X_{L_i-1} \ge S_i
\end{cases}
$$

即

$$
\begin{cases}
X_{R_i} \le X_{L_i - 1} + S_i\\
X_{L_i-1} \le X_{R_i} - S_i
\end{cases}
$$

因此我们可以连一条 $L_i-1 \to R_i$ 边权为 $S_i$ 的单向边，以及一条 $R_i \to L_i-1$ 边权为 $-S_i$ 的单向边。

$X_j - X_{j-1} \ge 1$ 也同理，可以连一条 $j \to j-1$ 边权为 $-1$ 的单向边。

到此，差分约束系统已经建立完毕。

### 找到源点

通常，我们可以使用 Bellman-Ford 求解差分约束。

但可以发现，对于一个点 $u$ 若无法到达一个其他点，显然该点不能作为 Bellman-Ford 的源点。

也就是说，我们需要找到一个源点使得该点能到达所有点，若没有，我们不妨建出一个超级源点（虚拟点）并向所有其他点建边。

但此题显然没必要建出超级源点。观察 $X_j - X_{j-1} \ge 1$ 建出的边，是 $j \to j-1$，因此对于点 $n$ 可以到达 $n-1$，$n-1$ 可以到达 $n-2$……所以点 $n$ 可到达所有点（即 $n$ 可以到达 $0 \sim n$）。

所以我们已经确定了源点，是 $n$。

### 求解

现在，我们可以从 $n$ 跑一遍 Bellman-Ford，若存在负环，则无解。

否则，我们已经求出了一组解 $X_0,X_1,\dots,X_n$。

注意，我们还有 $3$ 条件，不能保证求出的解中 $X_0 = 0$。

但是，差分约束有一个性质，即若已有一组解 $p_1.p_2,\dots,p_n$，则对于任意的偏移量 $d$，有 $p_1+d,p_2+d,\dots,p_n+d$ 也为一组解。

因此，我们不妨对于当前的解 $X_0,X_1,\dots,X_n$ 全部同时减去 $X_0$ 变为 $X'_0,X'_1,\dots,X'_n$，减去后，此时 $X'_0 = 0$，$X'_n$ 即为答案。

可能有人感到疑惑，为何 $X'_n$ 即为答案？

我们不妨假设存在另一组解 $Y_0,Y_1,\dots,Y_n$，满足 $Y_0 < X'_0,Y_1 < X'_1,\dots,Y_n < X'_n$，且 $X'_0-Y_0=X'_1-Y_1=\dots=X'_n-Y_n$，此时 $Y_n$ 更优。

不过因为 $Y_0 < X'_0 = 0$，所以 $Y_0 < 0$，即 $Y_0 \ne 0$，此时不满足 $3$ 条件，不合法。

综上，建图后从源点 $n$ 进行一遍 Bellman-Ford 后，$X_n - X_0$ 即为答案。

代码中使用 $dis$ 数组代替了 $X$ 数组。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 4e3 + 5;
const ll INF = 1e18;

int n, m;
ll dis[MAXN];

struct Edge{
  int u, v, w;
};
vector<Edge> e;

bool Find_Neg_Cycle(){//判断负环
  fill(dis, dis + 1 + n, INF);
  dis[n] = 0;
  for(int i = 1; i <= n + 1; i++){//注意，点是0 ~ n，有 n + 1 个点，需要 n + 1 轮迭代才能找出负环
    bool flag = 0;
    for(const auto [u, v, w] : e){
      if(dis[u] == INF) continue;
      if(dis[v] > dis[u] + w){//松弛
        dis[v] = max(dis[u] + w, -INF);//此处取max并无作用，仅仅是防止炸long long
        flag = 1;
      }
    }
    if(!flag) return 0;
  }
  return 1;
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(int i = 1, u, v, w; i <= m; i++){
    cin >> u >> v >> w; u--;
    e.push_back({v, u, -w});
    e.push_back({u, v, w});//建边
  }
  for(int i = 1; i <= n; i++){
    e.push_back({i, i - 1, -1});//建边
  }
  cout << (Find_Neg_Cycle() ? -1 : dis[n] - dis[0]);
  return 0;
}
``````

关于为何不使用 SPFA，因为~它四了~ SPFA 最坏时间复杂度也是 $O(nm)$，没必要，毕竟题目一定是可以把 SPFA 卡成 Bellman-Ford 的。

如有错误，烦请巨佬指出。

---

## 作者：Jerry20231029 (赞：1)

这次的 G 竟比 F 简单~~但赛时仍然切不出来~~。

## 思路

题目的条件可以转化为若干个不等式，然后就可以用差分约束做了。

看到区间和，于是就想到了前缀和。

不妨求出 $A$ 的前缀和 $B$，那么题目的条件 $\displaystyle\sum_{i=L_i}^{R_i} A_j = S_i$ 就可以转化为 $B_r-B_{l-1}=S_i$。

我们可以把它再转化一下，变成了：

$$
\begin{cases}
  B_r-B_{l-1} \le S_i \\
  B_r-B_{l-1} \ge S_i
\end{cases}
$$

而且题目要求 $A_i > 0$ 所以还有一个约束条件：$B_i-B_{i-1} \ge 1$。

然后就可以愉快的跑差分约束模版啦！

最后如果最长路出现正环或最短路出现负环就无解，输出 `-1`，否则输出 $dis_N$。

## 代码

[AC 记录](https://atcoder.jp/contests/abc404/submissions/65574236)

```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

typedef long long lld;

struct Edge{
	int v;
	lld w;
};
vector<Edge> E[4100];
lld d[4100],f[4100],c[4100],n;

bool SPFA(int s){
	memset(d,-0x3f,sizeof d);
	queue<int> q;
	q.push(s);
	f[s] = c[s] = 1;
	d[s] = 0;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		f[u] = 0;
		for(auto [v,w] : E[u]){
			if(d[v] < d[u]+w){
				d[v] = d[u]+w;
				if(f[v]){
					continue;
				}
				f[v] = 1;
				c[v]++;
				q.push(v);
				if(c[v] > n+1){
					return 1;
				}
			}
		}
	}
	return 0;
}

int main(){
	int m,l,r,s;
	cin>>n>>m;
	for(int i = 1; i <= n; i++){
		E[i-1].push_back({i,1});
	}
	for(int i = 1; i <= m; i++){
		cin>>l>>r>>s;
		E[l-1].push_back({r,s});
		E[r].push_back({l-1,-s});
	}
	if(SPFA(0)){
		cout<<-1;
	}else{
		cout<<d[n];
	}
	return 0;
}
```

---

## 作者：sodalyghat (赞：0)

### 分析
题目给的约束条件是区间和等于某个数的形式。直接做没什么思路，试着转成对于前缀和的约束条件。这个时候条件变成了两个数的差等于某一个值。这种形式我们可以用差分约束系统来处理。在每一个约束条件之间的两个数建一条边，然后跑一次最长路，最后 $n$ 号点也就是所有点的前缀和就是答案。注意由于还要保证每一个数都是正数，所以还有一个隐藏的条件就是相邻两个前缀和的差要大于等于一。关于具体的建边，假设我们得到的一个条件形式是 $s_r-s_{l-1}=k$，首先需要把它拆成两个条件，分别是 $s_{l-1}\geq s_r-k$ 和 $s_r\geq k+s_{l-1}$。由于我们是跑最长路，因此从 $l-1$ 连一条向 $r$ 的边，边权是 $k$，再从 $r$ 连一条向 $l-1$ 的边，边权是 $-k$ 即可。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 4005;
	const long long inf = 0x7ffffffffffffff / 2;
	int head[MAXN], CNT;
	struct edge{
		int next, to, val;
	}ed[MAXN << 2];
	void add_edge(int u, int v, int w){
		ed[++CNT] = (edge){head[u], v, w};
		head[u] = CNT;
	}
	int q[MAXN * MAXN], l, r, tim[MAXN];
	long long dis[MAXN];
	int vis[MAXN];
	int main(){
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 1, l, r, s;i <= m;i++){
			scanf("%d%d%d", &l, &r, &s);
			add_edge(l - 1, r, s);
			add_edge(r, l - 1, -s);
		} 
		for(int i = 1;i <= n;i++){
			dis[i] = -inf;
			add_edge(i - 1, i, 1);
		}
		q[++r] = 0;
		while(l < r){
			int u = q[++l];
			vis[u] = 0;
			tim[u]++;
			if(tim[u] >= n + 5){
				printf("-1");
				return 0;
			}
			for(int i = head[u];i;i = ed[i].next){
				int v = ed[i].to;
				if(dis[v] < dis[u] + ed[i].val){
					dis[v] = dis[u] + ed[i].val;
					if(!vis[v]){
						vis[v] = 1;
						q[++r] = v;
					}
				}
			}
		}
		printf("%lld", dis[n]);
		return 0;
	}
}
signed main(){
	return Luo_ty::main();
}//International Milan is the best team.
```

---

## 作者：fish_love_cat (赞：0)

[七倍经验](https://www.luogu.com.cn/discuss/1078777)。

其实不算原，但是差分约束板子还是有点难绷了。

然后我调不出来 SPFA 痛失场 G /fad

---

先做前缀和，然后原本的区间可以看作两个点间的关系。

由于是恰好等于所以还要建反边。

于是差分约束就可以求出最小的情况。

出现负环无解，正常 SPFA 就可以。不要写挂了。

机房打不开 AT，代码不放了。

---

这题最多绿吧，怎么能放到 G 的。

---

## 作者：Crazyouth (赞：0)

## 分析

由于题目规定 $a_i\ge 1$，所以可以得到对于每个整数 $i\in [1,n)$，都有 $sum_i-sum_{i-1}\ge 1$，即 $sum_{i-1}-sum_i\le -1$，其中 $sum$ 为 $a$ 的前缀和序列。又因为有若干个 $sum_r-sum_{l-1}=s$，所以可以直接建立差分约束模型，这样一来就能求出 $sum_n-sum_1$，我们只需要要求 $sum_1$ 是正整数，所以最终答案可以得到。

---

## 作者：Dtw_ (赞：0)

为啥这么板我都不会。
## 题意
给你 $n$ 个未知数 $A_1,A_2,\cdots,A_n$ 满足 ：

$$\displaystyle \sum_{j=L_i}^{R_i} A_j = S_i$$ 对于 $i\in[1,n]$。

求 $\sum A_i$ 的最小值。
## Solution
我们记 $c_i$ 为前缀和数组，那么这题分为 $3$ 步：

* $\displaystyle \sum_{j=L_i}^{R_i} A_j = S_i \to c_{R_i} - c_{L_i - 1} = S_i$

* $c_r - c_{l-1} = S_i \to c_r - c_{l-1} \leq S \ \&  \ c_r - c_{l-1}\ge S$

* 由于每个数都得是正整数，所以 $c_i - c_{i-1} \ge 0$。

然后差分约束做完了。答案就是 $c_n$。
## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 1e5 + 10, inf = 0x3f3f3f3f;

int n, m, c[N];
ll d[N];
bool vis[N];
vector<pair<int, int>> e[N];

bool spfa(int s)
{
    queue<int> q; q.push(s);
    memset(d, inf, sizeof d);
    d[s] = 0; vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (auto t : e[u]) {
            int v = t.first, w = t.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                c[v] = c[u] + 1;
                if (c[v] > n) return false;
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
    return true;
}

int main()
{
    fst
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w; u--;
        e[u].emplace_back(v, -w);
        e[v].emplace_back(u, w);
    }
    for (int i = 1; i <= n; i++) {
        e[i - 1].emplace_back(i, -1);
    }
    for (int i = 1; i <= n; i++) e[0].emplace_back(i, 0);
    if (spfa(0)) cout << -d[n];
    else cout << -1;
    return 0;
}
```

---

## 作者：Inv_day_in_R (赞：0)

比赛结束前六分钟意识到这是个差分约束，结束前二十秒交了第一发，A 了 82 个点，WA 了 6 个点，TLE 了 6 个点（话说我差分约束模板里的 spfa 怎么是个栈版本的，气死了）。

首先不难想到，用前缀和的方法，把区间和 $\displaystyle\sum_{j=L_i}^{R_i} A_j=S_i$ 变成两数之差 $sum_{R_i}-sum_{L_i-1}=S_i$。而这个前缀和除了这个还满足什么条件呢？观察到这个 $A$ 数组里全是**正**整数，那么自然满足关系：$sum_i+1\le sum_{i+1}$。这时学过差分约束的一定一眼秒了，只打过差分约束[模板题](https://www.luogu.com.cn/problem/P5960)怎么办？其实可以把 $sum_{R_i}-sum_{L_i-1}=S_i$ 的条件转化为：

$$ \begin{cases} sum_{R_i}-sum_{L_i-1}\le S_i \\sum_{R_i}-sum_{L_i-1}\ge S_i \end{cases}$$

代码实现：（我用的是跑最长路的做法）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int dis[100010],cnt[100010];
bool st[100010];
vector<array<int,2>>g[100010];
bool spfa(){
    memset(dis,-0x3f,sizeof dis);
    queue<int>s;
    s.push(0);
    st[0]=0;
    dis[0]=0;
    while(s.size()){
        int u=s.front();
        s.pop();
        st[u]=0;
        for(auto[v,w]:g[u]){
            if(dis[v]<dis[u]+w){//最长路
                dis[v]=dis[u]+w;
                cnt[v]=cnt[u]+1;
                if(cnt[v]>=n+1)return 1;
                if(!st[v]){
                    st[v]=1;
                    s.push(v);
                }
            }
        }
    }
    return 0;
}
void add(int u,int v,int w){
    g[u].push_back({v,w});
}
main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>k;
    for(int i=0;i<k;i++){
		int l,r,s;
		cin>>l>>r>>s;
		l--;
		add(l,r,s);
		add(r,l,-s);
    }
    for(int i=1;i<=n;i++){
		add(i-1,i,1);
	}
    if(spfa())cout<<-1;
    else{
		cout<<dis[n]-dis[0]<<"\n";
    }
}
```

---

