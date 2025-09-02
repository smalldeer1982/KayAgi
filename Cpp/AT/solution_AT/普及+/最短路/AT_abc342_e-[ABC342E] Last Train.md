# [ABC342E] Last Train

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc342/tasks/abc342_e

AtCoder 国には駅 $ 1, $ 駅 $ 2,\ldots, $ 駅 $ N $ の $ N $ 個の駅があります。

AtCoder 国に存在する電車の情報が $ M $ 個与えられます。 $ i $ 番目 $ (1\leq\ i\leq\ M) $ の情報は正整数の $ 6 $ つ組 $ (l\ _\ i,d\ _\ i,k\ _\ i,c\ _\ i,A\ _\ i,B\ _\ i) $ で表され、次のような情報に対応しています。

- $ t=l\ _\ i,l\ _\ i+d\ _\ i,l\ _\ i+2d\ _\ i,\ldots,l\ _\ i+(k\ _\ i-1)d\ _\ i $ それぞれについて、次のような電車が存在する。
  - 時刻 $ t $ に 駅 $ A\ _\ i $ を出発し、時刻 $ t+c\ _\ i $ に駅 $ B\ _\ i $ に到着する。

これらの情報にあてはまらない電車は存在せず、電車以外の方法である駅から異なる駅へ移動することはできません。  
また、乗り換えにかかる時間は無視できるとします。

駅 $ S $ から駅 $ N $ に到着できる最終時刻を $ f(S) $ とします。  
より厳密には、整数の $ 4 $ つ組の列 $ \big((t\ _\ i,c\ _\ i,A\ _\ i,B\ _\ i)\big)\ _\ {i=1,2,\ldots,k} $ であって、次のすべての条件を満たすものが存在するような $ t $ の最大値を $ f(S) $ とします。

- $ t\leq\ t\ _\ 1 $
- $ A\ _\ 1=S,B\ _\ k=N $
- すべての $ 1\leq\ i\lt\ k $ について、$ B\ _\ i=A\ _\ {i+1} $
- すべての $ 1\leq\ i\leq\ k $ について、時刻 $ t\ _\ i $ に駅 $ A\ _\ i $ を出発して時刻 $ t\ _\ i+c\ _\ i $ に駅 $ B\ _\ i $ に到着する電車が存在する。
- すべての $ 1\leq\ i\lt\ k $ について、$ t\ _\ i+c\ _\ i\leq\ t\ _\ {i+1} $

ただし、そのような $ t $ が存在しないとき $ f(S)=-\infty $ とします。

$ f(1),f(2),\ldots,f(N-1) $ を求めてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq2\times10\ ^\ 5 $
- $ 1\leq\ M\leq2\times10\ ^\ 5 $
- $ 1\leq\ l\ _\ i,d\ _\ i,k\ _\ i,c\ _\ i\leq10\ ^\ 9\ (1\leq\ i\leq\ M) $
- $ 1\leq\ A\ _\ i,B\ _\ i\leq\ N\ (1\leq\ i\leq\ M) $
- $ A\ _\ i\neq\ B\ _\ i\ (1\leq\ i\leq\ M) $
- 入力はすべて整数

### Sample Explanation 1

AtCoder 国に走っている電車は以下の図のようになります（発着時間の情報は図には含まれていません）。 !\[\](https://img.atcoder.jp/abc342/c3007f6fd6e6bffff5483312395e51f6.png) 駅 $ 2 $ から駅 $ 6 $ に到着できる最終時刻について考えます。 次の図のように、駅 $ 2 $ を時刻 $ 56 $ に出発して駅 $ 2\rightarrow $ 駅 $ 3\rightarrow $ 駅 $ 4\rightarrow $ 駅 $ 6 $ のように移動することで駅 $ 6 $ に到着することができます。 !\[\](https://img.atcoder.jp/abc342/bf9e3c0a042ef63f63e45fd5b94a23af.png) 駅 $ 2 $ を時刻 $ 56 $ より遅く出発して駅 $ 6 $ に到着することはできないため、$ f(2)=56 $ です。

### Sample Explanation 2

駅 $ 1 $ を時刻 $ 10\ ^\ {18} $ に出発して駅 $ 5 $ に時刻 $ 10\ ^\ {18}+10\ ^\ 9 $ に到着するような電車が存在します。それ以降に駅 $ 1 $ を出発する電車はないため、$ f(1)=10\ ^\ {18} $ です。 このように、答えが $ 32\operatorname{bit} $ 整数におさまらない場合もあります。 また、時刻 $ 14 $ に駅 $ 2 $ を出発して時刻 $ 20 $ に駅 $ 3 $ に到着するような電車は $ 2 $ 番目の情報と $ 3 $ 番目の情報の両方で存在が保証されています。 このように、複数の情報に重複している電車もあります。

## 样例 #1

### 输入

```
6 7
10 5 10 3 1 3
13 5 10 2 3 4
15 5 10 7 4 6
3 10 2 4 2 5
7 10 2 3 5 6
5 3 18 2 2 3
6 3 20 4 2 1```

### 输出

```
55
56
58
60
17```

## 样例 #2

### 输入

```
5 5
1000000000 1000000000 1000000000 1000000000 1 5
5 9 2 6 2 3
10 4 1 6 2 3
1 1 1 1 3 5
3 1 4 1 5 1```

### 输出

```
1000000000000000000
Unreachable
1
Unreachable```

## 样例 #3

### 输入

```
16 20
4018 9698 2850 3026 8 11
2310 7571 7732 1862 13 14
2440 2121 20 1849 11 16
2560 5115 190 3655 5 16
1936 6664 39 8822 4 16
7597 8325 20 7576 12 5
5396 1088 540 7765 15 1
3226 88 6988 2504 13 5
1838 7490 63 4098 8 3
1456 5042 4 2815 14 7
3762 6803 5054 6994 10 9
9526 6001 61 8025 7 8
5176 6747 107 3403 1 5
2014 5533 2031 8127 8 11
8102 5878 58 9548 9 10
3788 174 3088 5950 3 13
7778 5389 100 9003 10 15
556 9425 9458 109 3 11
5725 7937 10 3282 2 9
6951 7211 8590 1994 15 12```

### 输出

```
720358
77158
540926
255168
969295
Unreachable
369586
466218
343148
541289
42739
165772
618082
16582
591828```

# 题解

## 作者：Genius_Star (赞：9)

~~题意一大坨，懒得提了……~~

### 思路：

这题可以进行反向考虑，即建一个反图，求 $n$ 号点到其它每一个点的最长路径，则考虑 dijkstra 算法。

对于与 $n$ 相连的点 $v$，其的最短出发时间肯定是 $v_l+(v_k-1) \times v_d$。

否则对于点 $(v,u)$，有 $v \to u$ 的路径，那么我们找到一个尽量靠后的 $v_d$ 的倍数。

考虑记 $w=dis_u-c_v-c_l$，即中间 $v_d$ 最多可以花的时间，则 $dis_v$ 可以更新为 $\min(\lfloor \frac{w}{v_d} \rfloor \times v_d+v_l,v_l+(v_k-1) \times v_d)$。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200,INF=1e17;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Edge{
	ll v;
	ll l,d,k,c;
};
ll n,m;
ll dis[N];
bool f[N];
vector<Edge> E[N];
priority_queue<pair<ll,ll>> Q;
void add(ll l,ll d,ll k,ll c,ll u,ll v){
	E[u].push_back({v,l,d,k,c});
}
void dijkstra(ll s){
	Q.push({INF,n});
	while(!Q.empty()){
		ll u=Q.top().second;
		Q.pop();
		if(f[u])
		  continue;
		f[u]=1;
		for(auto t:E[u]){
			ll v=t.v;
			if(u==n){
				if(dis[v]<t.l+(t.k-1)*t.d)
				  dis[v]=t.l+(t.k-1)*t.d; 
			}
			else{
				if(dis[u]-t.c-t.l<0)
				  continue;
				ll w=min(((dis[u]-t.c-t.l)/t.d)*t.d+t.l,t.l+(t.k-1)*t.d);
				if(dis[v]<w)
				  dis[v]=w;
			}
			Q.push({dis[v],v});
		}
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  dis[i]=-INF;
	for(int a,b,c,d,e,f,i=1;i<=m;i++){
		a=read(),b=read(),c=read(),d=read(),e=read(),f=read();
		add(a,b,c,d,f,e);
	}
	dijkstra(n);
	for(int i=1;i<n;i++){
		if(dis[i]==-INF)
		  puts("Unreachable");
		else{
			write(dis[i]);
			putchar('\n');
		}
	}
	return 0;
}
```


---

## 作者：Otue (赞：6)

要求出所有 $i$ 到 $n$ 的最短路，显然思路是从 $n$ 开始跑反图。可以搭配 dijkstra 算法。

但是遇到了一个问题，初始 $n$ 的时间设置为多少？$0$ 吗？事实上，我们可以将此设置为正无穷。

对于当前点 $u$，存在反图上的边 $u\to v$，找到可以从 $v$ 出发可以到达 $u$ 最晚的一班火车。首先，如果这趟车 $l+c>f_u$，那么这趟车是上不去的。否则，我们找到的车次 $t$ 就是 $\min\{\lfloor \dfrac{f_u-l-c}{d}\rfloor,k-1\}$。更新 $f_v=l+t\times d$。

```c++
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define int long long
const int N = 3e5 + 5;

int n, m, dist[N], st[N];

struct node {
	int v, l, d, k, c; 
};
vector<node> G[N];

void dijstra() {
	fill(dist + 1, dist + n + 1, -2e18);
	dist[n] = 2e18;
	priority_queue<PII> q;
	q.push({dist[n], n});
	while (q.size()) {
		auto t = q.top(); q.pop();
		int u = t.second;
		for (auto e : G[u]) {
			int v = e.v, l = e.l, d = e.d, k = e.k, c = e.c;
			if (l + c > dist[u]) continue;
			int D = l + min((dist[u] - l - c) / d, k - 1) * d;
			if (dist[v] < D) {
				dist[v] = D;
				q.push({dist[v], v});
			}
		}
	}
}

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int l, d, k, c, u, v;
		cin >> l >> d >> k >> c >> u >> v;
		G[v].push_back({u, l, d, k, c});
	}
	dijstra();
	for (int i = 1; i < n; i++) {
		if (dist[i] == -2e18) puts("Unreachable");
		else cout << dist[i] << endl;
	}
}
```

祝大家学习愉快！

---

## 作者：梦应归于何处 (赞：4)

### 思路

我们考虑建立反向图，求解从 $N$ 开始往其他点跑最长路。

我们考虑 dijkstra。

我们设 $dis_u$ 表示 $u$ 号点的最晚出发时间。

我们设 $u$ 点通往的点为 $v$。

那么我们需要满足：

$$ dis_v+w\le dis_u $$
$$  l\le dis_v \le l+(d-1)\times k$$
$$ \frac{dis_u-w-l}{d} \le k-1 $$

$ \frac{dis_u-w-l}{d} \le k-1 $ 这个表示我要赶第几班车。

### 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp make_pair
#define pll pair<ll,ll>
using namespace std;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			f = -1;
		}
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
ll n, m;
vector<array<ll, 5> > g[1000005];
vector<ll> dij(ll s) {
	priority_queue<pll> q;
	vector<ll> vis(2 * n + 10, 0);
	vector<ll> dis(2 * n + 10, 0);
	dis[s] = 2e18;
	q.push(mkp(dis[s], s));
	while (!q.empty()) {
		ll u = q.top().second;
		q.pop();
		if (vis[u]) {
			continue;
		}
		vis[u] = 1;
		for (auto [v, w, l, d, k] : g[u]) {
			if (dis[u] - w < l) {
				continue;
			}
			ll x = min((dis[u] - w - l) / d, k - 1) * d + l;
			if (x > dis[v]) {
				dis[v] = x;
				q.push(mkp(x, v));
			}
		}
	}
	return dis;
}
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		ll l = read(), d = read(), k = read(), c = read(), a = read(), b = read();
		g[b].push_back({a, c, l, d, k});
	}
	auto ans = dij(n);
	for (int i = 1; i < n; i++) {
		if (!ans[i]) {
			cout << "Unreachable\n";
		} else {
			cout << ans[i] << endl;
		}
	}
	return 0;
}
~~~

---

## 作者：lml0928 (赞：1)

### Part 0. 题目大意

题目似乎说了很多，其实就是给你 $m$ 条周期性的线路，让你求出每个点最晚什么时候出发能到达 $n$ 号点。 题目中的 $\operatorname{f}$ 函数就是这个意思。

### Part 1. 题目思路

这个 $\operatorname{f}$ 函数显然符合最优子结构性质，因为 $\operatorname{f}$ 越大，能坐的车就越多。

假设当前时间为 $x$，节点为 $p$，我们想走边 $(l,d,k,c,u,p)$。

如果 $x-c < l$，那么无论如何我们也做不了这趟车，直接跳过。

否则，我们可以坐第 $\min(\lfloor\dfrac{x-c-l}{d}\rfloor,k-1)$ 次车（从 $0$ 开始计算），也即在 $l + \min(\lfloor\dfrac{x-c-l}{d}\rfloor,k-1) \times d$ 的时间到达。

注意到时间显然是单调下降的，所以 **当前到达时间最大的点** 一定不会被更新。这样，我们可以用 Dijkstra 算法来维护，每次用优先队列取出当前到达时间最大的点即可。

### Part 2. 题目代码

~~献上代码供众人批判~~

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct edge
{
	int to;
	ll we, fst, del, cnt;
};
struct node
{
	int p;
	ll dis;
	bool operator < (const node& cmp) const
	{
		return dis < cmp.dis;
	}
};
priority_queue<node> q;
vector<edge> g[200010];
long long d[200010];
bool vis[200010];
const ll INF = 0x3f3f3f3f3f3f3f3f;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
	{
		ll l, d, k, c;
		int a, b;
		cin >> l >> d >> k >> c >> a >> b;
		g[b].push_back({a, c, l, d, k});
	}
	memset(d, 0xc0, sizeof d);
	d[n] = INF;
	q.push({n, INF});
	while(!q.empty())
	{
		int f = q.top().p;
		q.pop();
		if(vis[f]) continue;
		vis[f] = true;
		for(auto i : g[f])
		{
			ll now = d[f] - i.we;
			if(now < i.fst) continue;
			ll tmp = (now - i.fst) / i.del;
			tmp = min(tmp, i.cnt - 1);
			if(i.fst + tmp * i.del > d[i.to])
			{
				d[i.to] = i.fst + tmp * i.del;
				q.push({i.to, d[i.to]});
			}
		}
	}
	for(int i = 1; i < n; i++)
	{
		if(d[i] <= -INF) cout << "Unreachable\n";
		else cout << d[i] << '\n';
	}
	return 0;
}
```

### Part 3. 后记
赛内想出来，并且写完了，结果代码第 $50$ 行除法不知道为啥脑抽，写成向上取整了，导致整整少 $450$ 分。

~~什么？你在问 spfa？它死了？好吧，它竟然没死！！！它又复活了！~~

---

## 作者：chenzhaoxu2027 (赞：1)

# 前言

本次比赛难度较高，大家打的都不是很好，但是这道题我认为比第四题简单。

# 题目大意（deepl）

AtCoder 国家有 $N$ 个站点：站点 $1$ 至站点 $N$。

你得到了该国有关火车的 $M$ 条信息。其中第 $i$ 条信息 $1 \le i \le M$ 由六个正整数 $l_i,d_i,k_i,c_i,A_i,B_i$ 组成的元组表示，表示时刻 $t=l_i,l_i+d_i, \cdots ,l_i+(k_i-1) \times d_i$ 有一列火车从站点 $A_i$ 出发，并在时刻 $t+c_i$ 抵达站点 $B_i$。

$f(s)$ 的定义是 $t$ 的最大值并且存在一个元素是四个整数组成的元组的长度为 $X$ 的序列 $(t_i,c_i,A_i,B_i)$ 满足以下所有条件：

1. $t \le t_1$

2. $B_X=N,A_1=S$

3. $A_i=B_{i-1}(2 \le i \le X)$

4. $t_{i+1} \ge t_i+c_i$

5. 有一列火车在 $t_i$ 时刻从站点 $A_i$ 出发，在 $t_{i+1}$ 时刻抵达站点 $B_i$

如果不存在这样的 $t$，则设 $f(S)=\text{Unreachable}$。

求 $f(1),f(2), \cdots ,f(N-1)$。

# 分析

这道题题目很长，具有极大的震慑作用。不过没关系，我们来看样例解释中的图理解一下：

![](https://img.atcoder.jp/abc342/b6667844f8166458430c27bd93838a76.png)

显然看出，我们尽可能想乘坐末班车去往下一站，能拖就拖。

那么，如何求出最晚时间呢？

BFS，启动！

用 BFS 求出从这个点最晚什么时候出发可以抵达站点 $N$。

显然要建反图。

对于每个点 $u$，考虑在反图上能去的一点 $v$。此时点 $u$ 已被更新，由于是在反图上转移，变一下就是在原图上逆流，从 $u$ 的最晚出发时间已被确定，所以计算出从 $v$ 最晚坐哪一班车可以尽量晚而不超过时间限制即可。

细节问题：有时候一个点会被重复转移，我的办法十分粗暴，如果答案更优秀则转移，否则不转移。有时候会发现你算出来的最晚车次比原来的更晚，此时需要与它原本的最晚车次取 $\min$ 值。

最后就是初始值，这里我们需要求出一个本不存在的 $f(N)$，选取的是来到站点 $N$ 的所有车次中最晚的车次到达时间。

# 代码

贴代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

struct edge {
	int to;
	int l, d, k;
	int c;
};
vector<edge> g[200005];
int n, m;
int v[200005];

signed main() {
	cin >> n >> m;
	int mx = -1, id1, id2;
	for (int i = 1; i <= m; i++) {
		int x, y, l, d, k, c;
		cin >> l >> d >> k >> c >> x >> y;
		g[y].push_back({x, l, d, k, c});//注意建反图
		if (y == n) {
			mx = max(mx, l + (k - 1) * d + c);//求初始值
			id1 = x;
			id2 = y;
		}
	}
	//bfs过程
	memset(v, 0xff, sizeof(v));//建议初始为-1方便等会的判断
	v[n] = mx;
	queue<int> q;
	q.push(n);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < g[u].size(); i++) {
			edge e = g[u][i];
			int tm = (v[u] - e.c - e.l) / e.d;//计算最晚时间
			if (tm >= e.k) {
				tm = e.k - 1;
			}
			tm = tm * e.d + e.l;
			if (v[e.to] > tm) {
				continue;
			}
			v[e.to] = tm;
			q.push(e.to);
		}
	}
	for (int i = 1; i < n; i++) {
		if (v[i] == -1) {
			cout << "Unreachable\n";
			continue;
		}
		cout << v[i] << "\n";
	}
	return 0;
}
```

---

## 作者：MrPython (赞：0)

注意：本题解的点编号从 $0$ 开始。

---

作为一个最短路题还是很有意思的。

这道题难点在于**让时光倒流**，考虑从 $N-1$ 出发往各个点走。反向建图，之后就可以用 dijkstra 算法做。

具体一些，先将 $f$ 初始化为 $-\infty$，再将 $f(N-1)$ 初始化为 $+\infty$ （显然从自己到自己无论多晚走都可以）。

再考虑假设目前到达了点 $p$，从当前点可到 $N-1$ 的最晚出发时间为 $f(p)$，如何计算与之相邻节点的 $f$ 值？火车从 $l_i$ 时刻开始，每隔 $d_i$ 发一次车，车程为 $c_i$。因此，火车会从 $l_i+c_i$ 开始，每隔 $c_i$ 到达一次。显然如果首班车到达时间要早于 $f(p)$ 就不可能乘坐那班车，可以之间跳过。接着，我们可以计算**这班车最晚要坐哪一辆才能赶在 $f(p)$ 前到达 $p$**（具体计算车次即 $t=\left \lfloor \dfrac{f(p)-(l_i+c_i)}{d_i} \right \rfloor $）。注意，一共只有 $k_i$ 班车，因此若 $t\ge k_i$，你必须乘坐末班车（即 $k_i-1$）。有了车次信息，就能计算这趟车的出发时间（$l_i+td_i$），就可以愉快的套进 dijkstra 模板了。

可以发现，本题到达时间晚的点更优，因此堆应当使用大根堆。

```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
struct train{
    ui l,d,k,c;size_t a,b;
};
vector<uli> dij(vector<vector<train>> const& mp){
    priority_queue<pair<uli,size_t>> q;
    q.emplace(numeric_limits<uli>::max(),mp.size()-1);
    vector<uli> dis(mp.size(),numeric_limits<uli>::min());
    dis.back()=numeric_limits<uli>::max();
    vector<bool> vis(mp.size());
    while (!q.empty()){
        size_t p=q.top().second;q.pop();
        if (vis[p]) continue;
        vis[p]=true;
        for (train const& i:mp[p]){
            if (i.l+i.c>dis[p]) continue;
            size_t t=(dis[p]-(i.l+i.c))/i.d;
            if (t>=i.k) t=i.k-1;
            if (i.l+t*i.d>dis[i.a]) q.emplace(dis[i.a]=i.l+t*i.d,i.a);
        }
    }
    return dis;
}
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n,m;cin>>n>>m;
    vector<vector<train>> mp(n);
    for (size_t i=0;i<m;++i){
        train t;cin>>t.l>>t.d>>t.k>>t.c>>t.a>>t.b;--t.a,--t.b;
        mp[t.b].push_back(t);
    }
    vector<uli> ans=dij(mp);
    for_each(ans.begin(),prev(ans.end()),[](uli x)
        {(x>numeric_limits<uli>::min()?cout<<x:cout<<"Unreachable")<<'\n';});
    return 0;
}
```

---

## 作者：FBW2010 (赞：0)

# 题意简述

[传送门](https://www.luogu.com.cn/problem/AT_abc342_e)

有 $n$ 个车站，由一些单向火车轨道相互连接。每条轨道连接两个站点，并有如下参数：第一辆火车发车时间 $l$，火车总共辆数 $k$，每辆火车发车间隔时间 $d$，以及从起点到终点要花的时间 $c$。求最晚什么时候到 $1$ 至 $n-1$ 号站点才能到 $n$ 号站点。

# 思路

我们可以转换一下思路，从 $n$ 开始倒推，问题就转化为了从 $n$ 到其他节点要花的最短时间，这就是一道单源最短路的题了。使用 dijkstra 算法即可做到 $O(n \log n)$ 的复杂度。

对于时间的转移，我们设到 $i$ 号节点最晚时间为 $t$，那么到达下一个节点便有三种情况：

>1. $t<l+c$ 时，无法通过这条轨道。
>2. $l+c \le t \le l+(k-1)\times d+c$ 时，到达下一个节点最晚时间就是比 $t-c$ 早一点的火车发车时间。
>3. $t>l+(k-1)\times d+c$ 时，就是 $l+(k-1)\times d$。

# 代码

代码整体就是 dijkstra 的模版，但也需要注意一些地方：

+ 由于是求的最晚时间，应使用大根堆。

+ $n$ 站点的时间应设为正无穷，其余的初始化为负无穷。

+ 不开 long long 见祖宗。

~~下面就献上我又臭又长的代码吧。~~

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<vector> 
using namespace std;
const int N=2e5+5;
int n,m,cnt,h[N],vis[N];
long long dis[N];
priority_queue<pair<long long,int> > q;
struct node{
	int next,to,k;
	long long l,d,c;
}a[N];
void add(int x,int y,int c,int l,int d,int k){
	a[++cnt].next=h[x];
	a[cnt].to=y;
	a[cnt].c=c;
	a[cnt].l=l;
	a[cnt].d=d;
	a[cnt].k=k;
	h[x]=cnt;
}
void dij(int k){
	for(int i=1;i<=n;i++){
		dis[i]=-2e18;
	}
	dis[k]=2e18;
	q.push({2e18,n});
	while(!q.empty()){
		long long x=q.top().first;
		int y=q.top().second;
		q.pop();
		if(vis[y])continue;
		vis[y]=1;
		for(int i=h[y];i;i=a[i].next){
			if(x<a[i].l+a[i].c)continue;
			long long t;
			if(x>a[i].l+a[i].d*(a[i].k-1)+a[i].c)t=a[i].l+a[i].d*(a[i].k-1);
			else t=(x-a[i].c-a[i].l)/a[i].d*a[i].d+a[i].l; 
			if(vis[a[i].to]==0&&t>dis[a[i].to]){
				dis[a[i].to]=t;
				q.push({t,a[i].to});
			}
		}
	}
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int l,d,k,c,x,y;
		scanf("%d %d %d %d %d %d",&l,&d,&k,&c,&x,&y);
		add(y,x,c,l,d,k);
	}
	dij(n);
	for(int i=1;i<n;i++){
		if(dis[i]==-2e18)printf("Unreachable\n");
		else printf("%lld\n",dis[i]);
	}
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# AT_abc342_e 题解

## 题目分析

这道题可以用广搜来写！

题目要求的是从每个点出发能够到达 $N$ 的最晚出发时间，可以通过建反图，从 $N$ 开始跑一遍广搜。

那需要维护什么信息呢？

记 $maxs_i$ 为从 $i$ 出发能够到达 $N$ 的最晚时间，初始值为 $-1$。

先来看看如何存图吧！

链式前向星存图，将每一条线路转化成一条边，$e_i$ 表示第 $i$ 条边的终点，$w_i$ 表示第 $i$ 条边的权值，也就是通行所需的时间，$ne_i$ 表示下一条边，$h_i$ 表示第一条边。

但存图时仅保留这些信息还是不够的，还需要存其他的有关信息。$L_i$ 表示这条线路的第一班车的时刻，$D_i$ 表示这条线路每隔多长时间就有一班车，$K_i$ 表示这条线路一共会发出多少班车。

所以加边函数可以这样写：

```cpp
void add(int a,int b,int c,int l,int d,int k) {
    e[tot]=b,w[tot]=c,L[tot]=l,D[tot]=d,K[tot]=k,ne[tot]=h[a],h[a]=tot++;
}
```

接下来看看如何广搜！

对于一个队列中的点 $u$，将其取出后，枚举从它出发的每一条边，记 $maxx$ 为这条边的最晚的车的发车时间。$maxx$ 为 $L_i+(K_i-1) \times D_i$ 与 $maxs_u-w_i$ 的最小值。

但是，我们并不能用现在的 $maxx$ 去更新下一个节点的信息，为什么呢？

一条线路的每一班车，都是间隔一段时间才有，而不是每时每刻都有，所以，$maxx$ 还应该转化为这条线路有发出车辆的时刻，也就是寻找比当前 $maxx$ 小的发车时刻的最大值，因此，对于一条边 $edge$ 以及一个时间点 $k$，我们可以写这样一个函数：

```cpp
int go_lower(int edge,int k) {
    int s=L[edge];
    int st=D[edge];
    k-=s;
    k/=st;
    return s+st*k;
}
```

建完图，跑一次广搜，然后最后枚举每个点（$N$ 除外）并输出结果即可，若 $maxs_i = 1$，则输出 `Unreachable`。

## 代码

```cpp
#include <bits/stdc++.h>

#define inf 9000000000000000000LL
#define int long long

using namespace std;

const int N=200005;
const int M=200005;

int n,m;
int e[M],ne[M],h[N],w[M],L[M],D[M],K[M],tot;
int maxs[N];

// 加边函数
void add(int a,int b,int c,int l,int d,int k) {
    e[tot]=b,w[tot]=c,L[tot]=l,D[tot]=d,K[tot]=k,ne[tot]=h[a],h[a]=tot++;
}

// 寻找有车可以坐的时刻，小于 k 的最大值
int go_lower(int edge,int k) {
    int s=L[edge];
    int st=D[edge];
    k-=s;
    k/=st;
    return s+st*k;
}

// 广搜
void bfs() {
    queue<int> q;
    q.push(n);
    maxs[n]=inf;
    while (!q.empty()) {
        int u=q.front(); q.pop();
        for (int i=h[u];~i;i=ne[i]) {
            int maxx=L[i]+(K[i]-1)*D[i];
            maxx=min(maxx,maxs[u]-w[i]);
            maxx=go_lower(i,maxx);
            if (maxx>maxs[e[i]]) { // 若能够更新答案，则入队
                maxs[e[i]]=max(maxx,maxs[e[i]]);
                q.push(e[i]);
            }
        }
    }
}

signed main() {
    memset(h,-1,sizeof(h));
    scanf("%lld %lld",&n,&m);
    for (int i=1;i<=n;++i) maxs[i]=-1;
    while (m--) {
        int l,d,k,c,a,b;
        scanf("%lld %lld %lld %lld %lld %lld",&l,&d,&k,&c,&a,&b);
        add(b,a,c,l,d,k);
    }
    bfs();
    for (int i=1;i<=n-1;++i) {
        if (maxs[i]==-1) puts("Unreachable");
        else printf("%lld\n",maxs[i]);
    }
    return 0;
}
```

## 注意事项

题目的结果可能很大，除了开 `long long` 以外，无穷大最好开到 $9 \times 10^{18}$。

---

## 作者：_smart_stupid_ (赞：0)

## [题目](https://atcoder.jp/contests/abc342/tasks/abc342_e)

要算每一个点到终点的时间，可不可以把所有边逆转方向，再从终点跑一遍最短路？

我们得到在时间限制下每一条路线最后一班车的时间，再跑一遍迪杰斯特拉算法，终点的时间为无穷大，然后让每一个点到达的时间尽量大，去找下一条边时，要乘坐时间不能超过当前时间的列车。如果第一班车都比当前时间晚，就不能乘坐。如果没有跑到一个点，就说明这个点不能到达终点。

注意：要开长整形，由于精度问题，建议全开长整形。

## AC Code:

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
long long n, m;
struct edge{
	long long u, v, w, l, d, k, nxt;
	long long get(long long t) {
		if (t < l + w) return -1;
		return l + min(k - 1, (t - l - w) / d) * d;
	}
};
edge ed[400100];
long long edcnt, head[200100];
void addedge(long long l, long long d, long long k, long long u, long long v, long long w){
	edcnt++;
	ed[edcnt].u = u;
	ed[edcnt].v = v;
	ed[edcnt].w = w;
	ed[edcnt].l = l;
	ed[edcnt].d = d;
	ed[edcnt].k = k;
	ed[edcnt].nxt = head[u];
	head[u] = edcnt;
}
struct node {
	int x;
	long long dis;
	node(int x_, long long dis_) {
		x = x_;
		dis = dis_;
	}
};
bool operator <(node a, node b) {
	return a.dis < b.dis;
}

long long dis[514114];
long long ans[200100];
void dijkstra() {
	priority_queue<node> pq;
	pq.push(node(n, 0x7f7f7f7f7f7f7f7f));
	while (!pq.empty()) {
		node now = pq.top();
		pq.pop();
		if (ans[now.x] > now.dis) continue;
		for (int i = head[now.x]; i; i = ed[i].nxt) {
			int v = ed[i].v;
			long long t = ed[i].get(now.dis);
			if (t != -1 && ans[v] < t) {
				ans[v] = t;
				pq.push(node(v, t));
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		long long l, d, k, c, a, b;
		cin >> l >> d >> k >> c >> a >> b;
		addedge(l, d, k, b, a, c);
	}
	for (long long i = 1; i <= n; i++) {
		ans[i] = -1;
	}
	ans[n] = 0x7f7f7f7f7f7f7f7f;
	dijkstra();
	for (int i = 1; i < n; i++) {
		if (ans[i] != -1) cout << ans[i] << '\n';
		else cout << "Unreachable\n";
	}
	return 0;
}
```

---

## 作者：Down_syndrome (赞：0)

## 题意
给出一张 $n$ 个点 $m$ 条边的有向图，第 $i$ 条边有六个信息 $l_i,d_i,k_i,c_i,A_i,B_i$，表示在时间为 $l_i,l_i+d_i,…l_i+(k_i-1)d_i$ 时有一趟从 $A_i$ 到 $B_i$ 花费 $c_i$ 时间的火车。问从第 $i(1\le i<n)$ 个点乘坐火车能够到达点 $n$ 的最晚出发时间。

## 思路
看到普通图上的最值问题，可以联想到最短路。令 $dis_i$ 表示第 $i$ 个点的最晚出发时间，再按照题意反向建图，这样就只要求从点 $n$ 出发到达每个点的特殊最短路就行了。考虑最短路的转移。对于第 $i$ 条边，如果 $dis_u-c_i<l_i$，那么无法从 $u$ 转移到 $v$，因为都赶不上这条边的火车。否则的话，因为每个点的最晚出发时间肯定是某趟火车的发车时间，所以可以用第一个小于等于 $dis_u-c_i$ 的 $l_i,l_i+d_i…l_i+(k_i-1)d_i$ 来更新答案。那么怎么求这个东西呢？我们知道，对于求小于等于 $x$ 的第一个 $y$ 的倍数可以用 $x-x\bmod y$ 算出。那么，我们就可以把上述式子转换为小于等于 $\min(dis_u-c_i-l_i,(k_i-1)d_i)$ 的第一个 $d_i$ 的倍数加上 $l_i$。加上 $\min$ 是为了不超过末班车的时间。综上所述，最短路的转移就为以下式子。
$$x=\min(dis_u-c_i-l_i,(k_i-1)d_i)$$
$$dis_v=\min(dis_v,x-x\bmod d_i+l_i)$$
这道题其实可以写 dijkstra 防被卡，但是我还是写了 spfa。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int M=2e5+5;
int n,m,a,b,e,f,u,v,cnt,l[M],d[M],k[M],c[M],to[M],nxt[M],h[N],dis[N];
bool vis[N];
queue<int> q;
void save(int a,int b,int e,int f,int u,int v){
	to[++cnt]=v;
	l[cnt]=a;
	d[cnt]=b;
	k[cnt]=e;
	c[cnt]=f;
	nxt[cnt]=h[u];
	h[u]=cnt;
}
int tmp(int x,int y){
	return x-x%y;
}
void spfa(){
	memset(dis,0xcf,sizeof(dis));
	dis[n]=2e18;
	q.push(n);
	vis[n]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=h[u];i;i=nxt[i]){
			if(dis[u]-c[i]<l[i]) continue;
			if(tmp(min(dis[u]-c[i]-l[i],(k[i]-1)*d[i]),d[i])+l[i]>dis[to[i]]){
				dis[to[i]]=tmp(min(dis[u]-c[i]-l[i],(k[i]-1)*d[i]),d[i])+l[i];
				if(!vis[to[i]]){
					q.push(to[i]);
					vis[to[i]]=1;
				}
			}
		}
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld%lld%lld%lld",&a,&b,&e,&f,&u,&v);
		save(a,b,e,f,v,u);
	}
	spfa();
	for(int i=1;i<n;i++){
		if(dis[i]>=0) printf("%lld\n",dis[i]);
		else printf("Unreachable\n");
	}
	return 0;
}
```


---

## 作者：happybob (赞：0)

考虑反向建图，然后设 $f_u$ 表示 $u$ 点的答案，$f_n = + \infty$。然后 Dijkstra 维护，每次拓展到一个新的点，相当于考虑一些同余相关的问题。容易发现这个东西可以 $O(1)$ 求出，就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 5e5 + 5, MOD = 1e9 + 7, HSMOD = 1610612741, HSMOD2 = 998244353; // Remember to change

int n, m, q, t, a[N];
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

long long qpow(long long a, long long b)
{
	long long res = 1ll, base = a;
	while (b)
	{
		if (b & 1ll) res = res * base % MOD;
		base = base * base % MOD;
		b >>= 1ll;
	}
	return res;
}

bool isprime(int x)
{
	if (x == 1) return 0;
	for (int i = 2; 1ll * i * i <= x; i++) if (x % i == 0) return 0;
	return 1;
}

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

template<typename T>
class Bit
{
public:
	T lowbit(T x)
	{
		return x & -x;
	}
	T tr[N];
	void add(T x, T y)
	{
		while (x < N)
		{
			tr[x] += y;
			x += lowbit(x);
		}
	}
	T query(T x)
	{
		T sum = 0;
		while (x)
		{
			sum += tr[x];
			x -= lowbit(x);
		}
		return sum;
	}
};

struct Edge
{
	int to, l, k, d, c;
	Edge() = default;
	Edge(int to, int l, int k, int d, int c): to(to),l(l), k(k), d(d), c(c){}
};

vector<Edge> G[N];
int dis[N];

struct Node
{
	int u,d;
	Node(int u,int d):u(u),d(d){}
	Node()=default;
	bool operator<(const Node& g) const
	{
		return d<g.d;
	}
};
bool vis[N];

signed main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	memset(dis,-1,sizeof dis);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int l,k,d,c,a,b;
		cin>>l>>d>>k>>c>>a>>b;
		G[b].emplace_back(Edge(a,l,k,d,c));
	}
	dis[n]=(int)4e18;
	priority_queue<Node> q;
	q.push(Node(n,dis[n]));
	while(q.size())
	{
		auto [u,ds]=q.top();
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto&[j,l,k,d,c]:G[u])
		{
			// ds-c
			if(ds<c) continue;
			int gg=ds-c;
			// gg mod d=l mod d
			int p=l%d;
			int kk=gg%d;
			if(kk>=p) gg-=kk-p;
			else
			{
				gg-=kk;
				gg-=(d-p);
			}
			if(gg>=1)
			{
				int mm=(gg-l)/d;
				if(mm>k-1)
				{
					gg=(k-1)*d+l;
				}
				if(gg>=1)
				{
					if(dis[j]<gg)
					{
						dis[j]=gg;
						q.push(Node(j,dis[j]));
					}
				}
			}
		}
	}
	for(int i=1;i<n;i++) 
	{
		if(dis[i]==-1) cout<<"Unreachable\n";
		else cout<<dis[i]<<"\n";
	}
	return 0;
}



```

---

## 作者：xixisuper (赞：0)

# [ABC342E] Last Train 题解

一道好题。

本题的关键在于要看出来反向建图。

## 思路

对于每一个未更新且与已更新的点有直连边的点，找到到达 $n$ 号店出发时间最晚的点，然后更新该点，并把与其直连的点加入优先队列。

注意，由于我们要找出发的最晚时间，所以优先队列应为大根堆。

假设点 $u$ 到点 $v$ 有一条直连边且 $f(u)$ 已知，则 $f(v) = \min(\lfloor \frac{f(u)-c}{d} \rfloor , k) \times d$，然后在这个图上跑堆优化的 dijikstra 就行了，时间复杂度 $O(m \log n)$。

## 代码

```cpp
#include <iostream>
#include <queue>
#define ll long long
using namespace std;
const ll NEGINF=-2147483647;
const ll N=2e5+10;
ll tim[N],rear[N],n,m,tot;
bool vis[N];
struct node{
	ll lft_tim,jiange,tang,shijian,from,to,nxt;
}lines[N];
struct nnode{
	ll stat,lfttim;
	friend bool operator <(const nnode a,const nnode b){
		return a.lfttim < b.lfttim;
	}
};
priority_queue<nnode,vector<nnode>,less<nnode> > q;
void add_lines(ll l,ll d,ll k,ll c,ll A,ll B){
	lines[++tot].lft_tim = l;
	lines[tot].jiange = d;
	lines[tot].tang = k;
	lines[tot].shijian = c;
	lines[tot].from = A;
	lines[tot].to = B;
	lines[tot].nxt = rear[B];
	rear[B]=tot;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(ll i=1;i<=m;i++){
		ll a,b,c,d,e,f;
		cin>>a>>b>>c>>d>>e>>f;
		add_lines(a,b,c,d,e,f);
	}
	for(ll i=1;i<=n;i++) tim[i]=NEGINF;
	vis[n]=1;
	for(ll i=rear[n];i;i=lines[i].nxt){
		nnode x;
		x.stat = lines[i].from;x.lfttim=lines[i].lft_tim+lines[i].jiange*(lines[i].tang-1);
		q.push(x);
	}
	while(!q.empty()){
		nnode nw=q.top();
		q.pop();
		if(vis[nw.stat]) continue;
		ll now=nw.stat;
		vis[nw.stat]=1;
		tim[now]=nw.lfttim;
		for(ll i=rear[now];i;i=lines[i].nxt){
			if(vis[lines[i].from]) continue;
			if(tim[now]-lines[i].shijian>=lines[i].lft_tim){
				ll ks=min(((tim[now]-lines[i].shijian)-lines[i].lft_tim)/lines[i].jiange,lines[i].tang-1);
				if(lines[i].lft_tim+ks*lines[i].jiange>tim[lines[i].from]){
					nnode x;
					x.lfttim=lines[i].lft_tim+ks*lines[i].jiange;
					x.stat = lines[i].from;
					q.push(x);
				}
			}
		}
	}
	for(ll i=1;i<n;i++){
		if(tim[i]==NEGINF) cout<<"Unreachable\n";
		else cout<<tim[i]<<"\n";
	}
	return 0;
} 
```


---

