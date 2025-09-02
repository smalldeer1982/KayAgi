# [USACO23FEB] Moo Route II S

## 题目描述

注意：本题的时间限制为 4 秒，是默认限制的两倍。

Bessie 正在度假！由于最近的技术进步，Bessie 可以通过先进的航班旅行，这些航班甚至可以进行时间旅行。此外，即使存在多个“平行”的 Bessie 同时出现也不会有任何问题。

在这个国家，有 $N$ 个机场，编号为 $1,2,\cdots,N$，以及 $M$ 条时间旅行航班（$1 \leq N,M \leq 200000$）。第 $j$ 条航班从机场 $c_j$ 在时间 $r_j$ 起飞，并在时间 $s_j$ 抵达机场 $d_j$（$0 \leq r_j,s_j \leq 10^9$，$s_j < r_j$ 是可能的）。此外，Bessie 在机场 $i$ 需要停留 $a_i$ 时间（$1 \leq a_i \leq 10^9$）。也就是说，如果 Bessie 乘坐一趟航班在时间 $s$ 抵达机场 $i$，她可以转乘一趟从该机场出发的航班，只要该航班的起飞时间 $r \geq s + a_i$。需要注意的是，停留时间不会影响 Bessie 抵达某机场的实际时间。

Bessie 从城市 $1$ 出发，起始时间为 $0$。对于从 $1$ 到 $N$ 的每个机场，求出 Bessie 最早可以到达该机场的时间。

## 样例 #1

### 输入

```
3 3
1 0 2 10
2 11 2 0
2 1 3 20
10 1 10```

### 输出

```
0
0
20```

## 样例 #2

### 输入

```
3 3
1 0 2 10
2 10 2 0
2 1 3 20
10 1 10```

### 输出

```
0
10
-1```

# 题解

## 作者：H_Kaguya (赞：8)

赛时想了想感觉没啥思路，结果最后写了一个麻烦的做法。  

首先把下飞机之后的等待时间算到边权上，这就是一个普通的最短路了。  
发现负边权最短路本身没啥好性质，所以考虑出发和到达时间固定这一点。  

套路拆点。对于每个点，可能的到达 / 出发时间是有限的，我们就拆出来若干个点。  
显然，可以在一个机场里等着，所以一个机场拆出来的点按时间顺序连一个链。  
至于航班，就在相应的时间点之间连边。  
这样，我们就把最短路问题转化成了连通性问题。跑一遍 BFS 即可。  

由于边数是 $O(n)$ 级别的，所以最后出来的总点数也是 $O(n)$ 的。  
由于需要按时间排序，所以总复杂度 $O(n\log n)$。  
当然，可以把所有点放在一起基数排序，并且用单调指针代替二分查找来做到线性。~~实现就算了。~~  

放上蒟蒻的赛时代码。  

```cpp
#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;
#define sz 200005
struct site
{
	int st, stim, ed, etim;
};
site dld[sz];
int n, m, top;
int wei[sz];
bool vis[sz << 1 | 1];
vector<int> tim[sz], ber[sz], fsl[sz << 1 | 1];
int read();
int haf(int, int);
void dfs(int);
int main()
{
	int x, y;
	n = read(); m = read();
	for (int i = 1; i <= m; ++i)
	{
		dld[i].st = read();
		dld[i].stim = read();
		dld[i].ed = read();
		dld[i].etim = read();
	}
	for (int i = 1; i <= n; ++i)
		wei[i] = read();
	for (int i = 1; i <= m; ++i)
	{
		tim[dld[i].st].emplace_back(dld[i].stim);
		tim[dld[i].ed].emplace_back(dld[i].etim + wei[dld[i].ed]);
	}
	for (int i = 1; i <= n; ++i)
		if (tim[i].size())
		{
			sort(tim[i].begin(), tim[i].end());
			x = 0;
			for (int j = 1; j < tim[i].size(); ++j)
				if (tim[i][j] != tim[i][x])
					tim[i][++x] = tim[i][j];
			tim[i].resize(x + 1);
			for (int j = 0; j <= x; ++j)
				ber[i].emplace_back(++top);
			for (int j = 1; j <= x; ++j)
				fsl[ber[i][j - 1]].emplace_back(ber[i][j]);
		}
	for (int i = 1; i <= m; ++i)
	{
		x = haf(dld[i].st, dld[i].stim);
		y = haf(dld[i].ed, dld[i].etim + wei[dld[i].ed]);
		fsl[x].emplace_back(y);
	}
	if (ber[1].size())
		dfs(1);
	puts("0");
	for (int i = 2; i <= n; ++i)
	{
		x = 1;
		for (int j = 0; j < ber[i].size(); ++j)
			if (vis[ber[i][j]])
			{
				printf ("%d\n", tim[i][j] - wei[i]);
				x = 0; break;
			}
		if (x)
			puts("-1");
	}
	return 0;
}

int read()
{
	int x = 0;
	char c = getchar();
	while (c < '0') c = getchar();
	do {
		x = x * 10 + (c & 15);
		c = getchar();
	}while (c >= '0');
	return x;
}

int haf(int a, int b)
{
	int lf = 0, rt = tim[a].size(), mid;
	while (rt > lf + 1)
	{
		mid = lf + rt >> 1;
		if (tim[a][mid] <= b)
			lf = mid;
		else
			rt = mid;
	}
	return ber[a][lf];
}

void dfs(int a)
{
	vis[a] = true;
	for (int i : fsl[a])
		if (!vis[i])
			dfs(i);
}

```


---

## 作者：Usada_Pekora (赞：5)

注意到航班只有 $m$ 个，也就是说最多出现 $m$ 种不同的到达时间，所以出现一个更新了的距离就把它塞回去更新其它点（spfa） 是 $O(m^2)$ 的。

不难发现，由于不管以什么时间经过一条边，出来的时间都是一样的，所以走过的边就没必要再走一次，考虑对每个点的出边按照 $r$ 降序排序，然后就可以很方便跳过走过的边了，因为既然距离大的时候能过去，小的时候也能过去。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int N = 2e5 + 5, inf = 2e9 + 7;
struct edge {
    int v, in, out;
    edge(int _v = 0, int _in = 0, int _out = 0) {
        v = _v, in = _in, out = _out;
    }
    bool operator < (const edge &o) const {
        return (in ^ o.in) ? (in > o.in) : (out < o.out);
    }
};
vector<edge> g[N];
int n, m, a[N], dis[N], cur[N];
bool inq[N];
inline void spfa() { // optimized bellman ford
    for (int i = 1; i <= n; i++)
        dis[i] = inf;
    dis[1] = 0, inq[1] = true;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        inq[u] = false;
        q.pop();
        for (int _ = cur[u]; _ < g[u].size(); _++) {
            int v = g[u][_].v, in = g[u][_].in, out = g[u][_].out;
            cur[u] = _;
            if (in < dis[u] + a[u])
                break;
            if (out < dis[v]) {
                dis[v] = out;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int c, r, d, s;
        cin >> c >> r >> d >> s;
        g[c].emplace_back(edge(d, r, s));
    }
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    a[1] = 0;
    for (int i = 1; i <= n; i++)
        sort(g[i].begin(), g[i].end());
    spfa();
    for (int i = 1; i <= n; i++)
        if (dis[i] != inf)
            cout << dis[i] << '\n';
        else
            cout << "-1\n";
    return 0;
}
```

---

## 作者：zac2010 (赞：4)

### 思路
首先，这道题目是一个比较明显的图论最短路，但是由于时间可以从后往前，想直接跑最短路而不用玄学方法的话——迪杰斯特拉怕只有怔怔地望着的份了。当然，是否有玄学方法我就不得而知了。

#### SPFA 的 LLL 优化

“燕子去了，有再来的时候；杨柳枯了，有再青的时候；桃花谢了，有再开的时候。”聪明的，你告诉我，SPFA 死了就没有再活的时候吗？

非然也。

我们直接按照题目的边作为图上的边，跑 SPFA 算法。注意一开始我们对一个点连出去的所有边排序，那么这样对于 SPFA 中枚举边的时候发现边被分为两类，刚好是两段——一段是起始时间太早导致无法乘坐的，位于其后面的一段是能去拓展其它点的边。

那么我们每次维护分隔点的位置即可。

~~“我掩面叹息，但是新来的日子的影儿又开始在叹息里闪过了”~~

我掩面叹息，但是强大的 SPFA 早已在叹息里跑过了。

此做法的代码是通过了，但是我就不给了。

#### 记忆化 SPFA

这只能应对有特殊性质的题目。

这个做法时间复杂度有保证，代码又异常短。

首先还是对边排序，还是跑 SPFA 最短路。改动的只是我们把每次拓展出去过的边都删掉。毕竟每条边只可能在第一次遍历到时更新其它点，从第二次开始必定不会更新成功。


```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(register int i = a; i <= b; i++)
#define R(i, a, b) for(register int i = a; i >= b; i--)
using namespace std;
const int N = 2e5 + 10;
struct Edge{
	int v, s, t;
	friend bool operator < (Edge a, Edge b){
		return a.s == b.s? a.v < b.v : a.s < b.s;
	}
};
int n, m, a[N], dis[N], vis[N], id[N];
queue<int> q; vector<Edge> g[N];
void Spfa(){
	L(i, 2, n) dis[i] = 2e9;
	vis[1] = 1, q.push(1);
	while(!q.empty()){
		int u = q.front(); q.pop();
		int tm = (u == 1? 0 : dis[u] + a[u]);
		while(id[u] && g[u][id[u] - 1].s >= tm) id[u]--;
		vis[u] = 0;
		L(i, id[u], (int)g[u].size() - 1){
			int v = g[u][i].v, t = g[u][i].t;
			if(t < dis[v]){
				dis[v] = t;
				if(!vis[v]) vis[v] = 1, q.push(v);
			}
		}
		while(g[u].size() > id[u]) g[u].pop_back(); id[u] = g[u].size();
	}
}
int main(){
	scanf("%d%d", &n, &m);
	L(i, 1, m){
		int u, v, s, t;
		scanf("%d%d%d%d", &u, &s, &v, &t);
		g[u].push_back({v, s, t});
	}
	L(i, 1, n){
		scanf("%d", &a[i]);
		sort(g[i].begin(), g[i].end()), id[i] = g[i].size();
	}
	Spfa();
	L(i, 1, n){
		if(dis[i] == 2e9) printf("-1\n");
		else printf("%d\n", dis[i]);
	}
	return 0;
}
```

---

## 作者：rhn7 (赞：2)

上课老师讲了这道题，顺便给了 hack 数据：
```cpp
#include<iostream>
using namespace std;
int main(){
    int n=2,m=200000;
    printf("%d %d\n",n,m);
    for(int i=1;i<=m;i++){
    	if(i%2) printf("1 1 2 0\n");
    	else printf("2 1 1 0\n");
	}
	printf("1 1\n");
	return 0;
}
```

面对这组数据，三篇题解都 TLE 了，我随机找了几位谷友，也有好多人挂了。本题解讲一下这三篇题解为什么错以及怎么改。

以 Xy_top 大佬的代码为例：

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int n, m, c;
int e[200005], f[200005], dis[200005];
struct Plane {int r, d, s;} t;
bool cmp (Plane p1, Plane p2) {return p1.r < p2.r;}
vector <Plane> v[200005];
void dfs (int x, int ti) {
	for (int i = f[x]; i >= 0; i --) {
		t = v[x][i];
		if (ti > t.r) break;
		else if (i == 0) f[x] = -1;
		dis[t.d] = min (dis[t.d], t.s);
		f[x] = i - 1;
		dfs (t.d, t.s + e[t.d]);
	}
}
int main () {
	for (int i = 1; i <= 200000; i ++) dis[i] = 1000000001;
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= m; i ++) {
		scanf ("%d%d%d%d", &c, &t.r, &t.d, &t.s);
		v[c].push_back (t);
	}
	for (int i = 1; i <= n; i ++) {
		scanf ("%d", &e[i]);
		f[i] = v[i].size () - 1;
		sort (v[i].begin (), v[i].end (), cmp);
	}
	dis[1] = 0;
	dfs (1, 0);
	for (int i = 1; i <= n; i ++) {
		if (dis[i] >= 1000000001) cout << -1 << "\n";
		else cout << dis[i] << "\n";
	}
	return 0;
}
```
主要思路就是一个点可能走多次，但一条边只能走一次（因为到达时间都是相同的，走一次就够了），对于每个点的所有出边，按 $r$ 从小到大排序（这样越靠后的出边越能走，越靠前的出边越不能走），$f_x$ 表示 `dfs` 时 $>f_x$ 的出边都走过了，遍历出边时从 $f_x$ 开始倒着循环，如果第 $i$ 条出边能走，那么 $f_x=i-1$。

思路和代码看上去都没有问题，但是如果图中有环，`dfs (t.d, t.s + e[t.d]);` 就有可能走到 $x$，遍历 $x$ 的出边，更新 $f_x$，由于是倒着循环，`for (int i = f[x]; i >= 0; i --)` 重复的遍历了区间 $[f_x,i-1]$ 的出边，所以才会 TLE。

解决方法也很简单，将 $i =f_x+1$ （回到 `for` 循环会 `i--`，所以要加上一）就可以通过 [数据加强版](https://www.luogu.com.cn/problem/U414043)。

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int n, m, c;
int e[200005], f[200005], dis[200005];
struct Plane {int r, d, s;} t;
bool cmp (Plane p1, Plane p2) {return p1.r < p2.r;}
vector <Plane> v[200005];
void dfs (int x, int ti) {
	for (int i = f[x]; i >= 0; i --) {
		t = v[x][i];
		if (ti > t.r) break;
		else if (i == 0) f[x] = -1;
		dis[t.d] = min (dis[t.d], t.s);
		f[x] = i - 1;
		dfs (t.d, t.s + e[t.d]);
		i = f[x] + 1;//加上这句话就可以 AC 
	}
}
int main () {
	for (int i = 1; i <= 200000; i ++) dis[i] = 1000000001;
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= m; i ++) {
		scanf ("%d%d%d%d", &c, &t.r, &t.d, &t.s);
		v[c].push_back (t);
	}
	for (int i = 1; i <= n; i ++) {
		scanf ("%d", &e[i]);
		f[i] = v[i].size () - 1;
		sort (v[i].begin (), v[i].end (), cmp);
	}
	dis[1] = 0;
	dfs (1, 0);
	for (int i = 1; i <= n; i ++) {
		if (dis[i] >= 1000000001) cout << -1 << "\n";
		else cout << dis[i] << "\n";
	}
	return 0;
}
```

---

## 作者：muyangli (赞：1)

# P9126 [USACO23FEB] Moo Route II S

## 题目描述

题目有一定的误导性。题目给你一些点和一些 $r_i$ 时刻出发 $s_i$ 时刻到达的线路，每个点在**经过线路**到达后还要至少停留 $a_i$ 时间（注意：无论你什么时候到达下一步想要走的线路的起始点，只要你到达的时间加上停留时间小于等于出发时间，你就都是出发时间 $r_i$ 出发，$s_i$ 到达）。求从一号点出发想要到达每个点的最短时间。

## 题目分析

求最短时间，可以想到最短路。又 $s_i$ 可能小于 $r_i$，可能出现负权边，所以使用某个著名已死 SPFA （也许是 Bellman-Ford？） 算法来解决。我们使用深搜实现方便进行优化。每次找可以走的边，记录已经走过。这里我们发现每条边做一次就可以了，因为无论什么时候到达起始点，都是 $s_i$ 到达，没必要重算。

65分代码：

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <cstdio>
#define int __int128
#define rd() read128()
#define pr(a) print128(a)
#define pc(b) putchar(b)
#define pel(c) pr(c), pc('\n')
#define psp(d) pr(d), pc(' ')
using namespace std;
int read128()
{
	int ttpttp = 0, flgflg = 1;
	char chrchr = getchar();
	if(chrchr == '-') flgflg = -1;
	while((chrchr < '0' || chrchr > '9') && chrchr != '-') chrchr = getchar();
	if(chrchr == '-') flgflg = -1, chrchr = getchar();
	while(chrchr >= '0' && chrchr <= '9') ttpttp = ttpttp * 10 + chrchr - '0', chrchr = getchar();
	return ttpttp * flgflg;
}
void print128(int ttpttp)
{
	char char_inserted_list[38];
	if(ttpttp < 0) putchar('-'), ttpttp *= -1;
	int iiiiii = 0;
	while(ttpttp > 0)
	{
		char_inserted_list[++iiiiii] = (char)(ttpttp % 10 + '0');
		ttpttp /= 10;
	}
    if(iiiiii == 0) putchar('0');
    else
    {
    	for(int i = iiiiii; i >= 1; i--) putchar(char_inserted_list[i]);
	}
}
struct E
{
	int u, v, st, et, nxt;
	bool used;
}e[200010];
int h[200010], tot, dis[200010], a[200010];
bool vis[200010];
void addedge(int u, int st, int v, int et)
{
	e[++tot].u = u;
	e[tot].v = v;
	e[tot].st = st;
	e[tot].et = et;
	e[tot].nxt = h[u];
	h[u] = tot;
}
void spfa(int pos)// 重点部分
{
	for(int i = h[pos]; i; i = e[i].nxt)
	{
		if(!e[i].used && dis[pos] <= e[i].st && dis[e[i].v] > e[i].et + a[e[i].v])
		{
            // 这里判断这条边有没有走过
            // 时间有没有超限
            // dis 可不可以更新
			dis[e[i].v] = e[i].et + a[e[i].v];
			e[i].used = 1;
			spfa(e[i].v);// 搜
		}
	}
}
signed main()
{
	int n = rd(), m = rd();
	for(int i = 1; i <= m; i++)
	{
		int u = rd(), st = rd(), v = rd(), et = rd();
		addedge(u, st, v, et);
	}
	for(int i = 1; i <= n; i++) a[i] = rd();
	for(int i = 1; i <= 200000; i++) dis[i] = 1e18;
	dis[1] = 0;
	spfa(1);
	dis[1] = a[1];
	for(int i = 1; i <= n; i++)
	{
		if(dis[i] < 1e17) pel(dis[i] - a[i]);
		else pel(-1);
	}
	return 0;
}
```

获得了65分的好成绩后，我们尝试优化。

发现我们很多时候在判断无用的边，于是我们将邻接表里的边按照起始点倒序排序，这样一旦找到一个T掉的边就可以直接 `break` 没有必要继续做下去。

## 满分实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
#define rd() read128()
#define pr(a) print128(a)
#define pc(b) putchar(b)
#define pel(c) pr(c), pc('\n')
#define psp(d) pr(d), pc(' ')
using namespace std;
int read128()
{
	int ttpttp = 0, flgflg = 1;
	char chrchr = getchar();
	if(chrchr == '-') flgflg = -1;
	while((chrchr < '0' || chrchr > '9') && chrchr != '-') chrchr = getchar();
	if(chrchr == '-') flgflg = -1, chrchr = getchar();
	while(chrchr >= '0' && chrchr <= '9') ttpttp = ttpttp * 10 + chrchr - '0', chrchr = getchar();
	return ttpttp * flgflg;
}
void print128(int ttpttp)
{
	char char_inserted_list[38];
	if(ttpttp < 0) putchar('-'), ttpttp *= -1;
	int iiiiii = 0;
	while(ttpttp > 0)
	{
		char_inserted_list[++iiiiii] = (char)(ttpttp % 10 + '0');
		ttpttp /= 10;
	}
    if(iiiiii == 0) putchar('0');
    else
    {
    	for(int i = iiiiii; i >= 1; i--) putchar(char_inserted_list[i]);
	}
}
struct E
{
	int v, st, et;
	bool used;
};
vector<E> e[200010];
int dis[200010], a[200010];
bool vis[200010];
void spfa(int pos, int tim)
{
	for(int i = 0; i < e[pos].size(); i++)
	{
		if(tim > e[pos][i].st) break;
		if(!e[pos][i].used && tim <= e[pos][i].st && dis[e[pos][i].v] > e[pos][i].et)
		{
			dis[e[pos][i].v] = e[pos][i].et;
			e[pos][i].used = 1;
			spfa(e[pos][i].v, dis[e[pos][i].v] + a[e[pos][i].v]);
		}
	}
}
bool cmp(E x, E y)
{
	return x.st > y.st;
}
signed main()
{
	int n = rd(), m = rd();
	for(int i = 1; i <= m; i++)
	{
		int u = rd(), st = rd(), v = rd(), et = rd();
		e[u].push_back({v, st, et, 0});
	}
	for(int i = 1; i <= n; i++) sort(e[i].begin(), e[i].end(), cmp);
	for(int i = 1; i <= n; i++) a[i] = rd();
	for(int i = 1; i <= n; i++) dis[i] = 1e18;
	dis[1] = 0;
	spfa(1, 0);
	for(int i = 1; i <= n; i++)
	{
		if(dis[i] < 1e17) pel(dis[i]);
		else pel(-1);
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

首先，坐一个相同的航班两次是没有意义的，他们的达到时间都一样。

考虑进行 dfs 搜索答案：如果当前航班可以乘坐，那么就坐，并更新答案。

这样明显是 $O(NM)$ 的，过不去。

考虑优化，因为每一个航班只坐一次，所以如果图有环的话，可能会对于一些边多走，于是考虑记录一个 $k_u$ 表示从 $u$ 出发的航班已经遍历到了第 $k_u$ 条，这样不会重复走航班。

还有一个优化，对于每一个点出发的航班的出发时间**降序**排序，如果当前这个航班都不合法，那么后面的航班也不合法，可以直接退出。

这样时间复杂度为 $O(N \log M+M)$。

**注意去重。**

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
struct Node{
	ll c,r,d,s;
	bool operator<(const Node&rhs)const{
		return r>rhs.r;
	}
	bool operator==(const Node&rhs)const{
		return c==rhs.c&&r==rhs.r&&d==rhs.d&&s==rhs.s;
	}
}a[N];
bool cmp(const Node&x,const Node&y){
	if(x.c!=y.c)
	  return x.c<y.c;
	if(x.r!=y.r)
	  return x.r<y.r;
	if(x.d!=y.d)
	  return x.d<y.d;
	return x.s<y.s;
}
ll n,m;
ll w[N],k[N],dis[N];
bool f[N];
vector<pair<Node,ll>> E[N];
void dfs(ll u,ll t){
	for(ll i=k[u];i<(ll)E[u].size();i++){
		ll id=E[u][i].second;
		Node v=E[u][i].first;
		if(v.r<t) 
		  break;
		if(f[id])
		  continue;
		f[id]=1;
		dis[v.d]=min(dis[v.d],v.s);
		k[u]++;
		dfs(v.d,v.s+w[v.d]);
	}
	return;
}
int main(){
//	freopen("A.in","r",stdin); 
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	  a[i]={read(),read(),read(),read()};
	sort(a+1,a+m+1,cmp);
	m=unique(a+1,a+m+1)-(a+1);
	for(int i=1;i<=m;i++)
	  E[a[i].c].push_back({a[i],i});
	for(int i=1;i<=n;i++){
		w[i]=read();
		dis[i]=INF;
		sort(E[i].begin(),E[i].end());
	}
	dis[1]=0;
	dfs(1,0);
	for(int i=1;i<=n;i++){
		write(dis[i]==INF?-1:dis[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：__xsy2013__ (赞：0)

有一个显然可以得到的结论，任意一个航班不可能坐两次，因为它的到达时间都是相同的。

所以这题可以一遍 DFS 解决。

具体过程：

首先 DFS 需要记录当前的时间以及在哪个机场里。

标记当前飞机已经坐过了，再坐就没有任何意义了，然后更新一下答案。

遍历所有它能够坐的飞机，如果这个飞机还没有被坐过，那就坐它。

别忘了 `dis` 数组的初始化。

另外，还有一个地方需要优化。假如每次遍历它能坐到的飞机，前面的都是坐过的了，就会浪费很多时间复杂度导致 TLE。

我是用 `vector` 存储的，把每个点出发的飞机按照时间排序。这样，每次能坐的飞机就一定是连续一块。

然后我记录下 $n$ 个数字，分别代表从 $i$ 号点出发的飞机第一个没做过的是几号，这样就可以愉快的通过了。

代码就不给了吧。

---

## 作者：tder (赞：0)

你说的对，但是我输入顺序看错了调了好久。

考虑类似最短路处理，用 $D_i$ 表示 $1\rightsquigarrow i$ 的最短路长度估计。

首先有结论，每条边只会松弛一次。下面给出证明：

- 对于一条边 $(u,v)$，若可以松弛则 $D_v>d$，而由于题目的特殊之处，松弛后 $D_v\leftarrow d$，与 $D_u$ 无关，而 $D_u$ 仅会不断变小，因此可以不断松弛，但效果不变，因此只松弛一次即可。

接下来，类似已死的 SPFA，我们用队列维护更新。对于 $k$ 的出边，若可以更新 $(k,d)$，则显然有出发时间不早于最短路长度与停泊时间之和，即 $r>D_k+a_k$，此时松弛入队后删边即可。另外注意特判 $k=1$ 时无需等待停泊时间。

时间复杂度 $O(n\log n+m)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5, INF = 1e18;
int n, m, d[N], a[N];
struct Edge {
    int s, e, v;
};
bool operator<(Edge x, Edge y) {
    return x.s < y.s;
}
vector<Edge> g[N];
void search(int s) {
    for(int i = 1; i <= n; i++) d[i] = INF;
    d[1] = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
        int k = q.front(); q.pop();
        // cout<<"k = "<<k<<endl;
        while(!g[k].empty() && (g[k].back().s >= d[k] + a[k] || k == 1)) {
            auto i = g[k].back();
            g[k].pop_back();
            // cout<<"s = "<<i.s<<", v = "<<i.v<<", e = "<<i.e<<", d = "<<d[i.v]<<endl;
            if(d[i.v] > i.e) {
                d[i.v] = i.e;
                q.push(i.v);
            }
        }
    }
}
signed main() {
    cin>>n>>m;
    for(int i = 1; i <= m; i++) {
        int c, r, d, s; cin>>c>>r>>d>>s;
        g[c].push_back({r, s, d});
    }
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());
    search(1);
    for(int i = 1; i <= n; i++) 
        if(d[i] != INF) cout<<d[i]<<endl;
        else cout<<-1<<endl;
}
```

---

