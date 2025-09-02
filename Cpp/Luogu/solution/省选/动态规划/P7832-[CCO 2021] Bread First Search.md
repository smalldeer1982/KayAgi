# [CCO 2021] Bread First Search

## 题目描述

这个国家有 $n$ 个城市和 $m$ 条双向道路。

有一个人要游览这个国家，但他很讲究。他要求游览线路必须是一个 BFS（Bread First Search，面包优先搜索）序，必须访问每个城市各一次，且满足以下条件：

- 首个城市可以任选；
- 除了首个城市外，每个城市被访问前至少有一个相邻城市已经被访问过；
- 每个城市与首个城市的距离单调不降。其中两个城市的距离定义为它们路径边数的最小值。

这个人还有强迫症，一定要按照编号 $1 \sim n$ 的顺序将每个城市访问一次。为了使这条游览线路符合上述所有要求，政府需要新修若干条道路。请问最少需要新修多少条道路？

## 说明/提示

#### 样例 #2 解释
一种符合要求的方式是，在城市 $1, 2$ 之间修一条路，在城市 $1, 4$ 之间修一条路。此时城市 $1$ 与城市 $1 \sim 6$ 的距离分别是 $0, 1, 1, 1, 2, 2$。
#### 数据范围
对于 $\frac{11}{32}$ 的数据，$1 \leq n \leq 200$；

对于 $\frac{5}{8}$ 的数据，$1 \leq n \leq 5 \times 10^3$；

对于 $100\%$ 的数据，$1 \leq n \leq 2 \times 10^5$，$0 \leq m \leq \min(2 \times 10^5, \frac{n(n - 1)}{2})$，$1 \leq a, b \leq n$，**保证没有重边和自环**。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D2T2

## 样例 #1

### 输入

```
2 0```

### 输出

```
1```

## 样例 #2

### 输入

```
6 3
1 3
2 6
4 5```

### 输出

```
2```

# 题解

## 作者：Rainbow_qwq (赞：11)

bfs 序会把图分成若干层，考虑 DP 不停的加一层，有一个限制：原有的边不能有从第 $i-2$ 层到第 $i$ 层的；代价则是第 $i$ 层中没有向第 $i-1$ 层有边的。

可以设 $f(i,j)$ 表示分 $[i,j]$ 为一层，转移枚举 $f(k,i-1)\to f(i,j)$，可以得到 $O(n^3)$ 做法。

但是最终二维的做法还是不太行，需要再挖掘一下转移的性质。

设 $f(i)$ 表示前 $i$ 个分成若干段的代价最小值，考虑从 $i\to j(i<j)$，发现如下的 $j$ 是不能转移的：

![](https://cdn.luogu.com.cn/upload/image_hosting/xy8ywawq.png)

于是我们发现能转移的 $j$ 是一段后缀。设 $mx_i$ 为 $(1\sim i)\to v$ 中 $v$ 的最大值，$j$ 需要 $\ge mx_i$。并且在 $\ge mx_i$ 的部分，$j$ 每增大 1 代价就增大 1，代价是一段连续的数。

于是推一下就可以简单 $O(n)$ DP 了，可以只向 $j$ 能到的最小地方转移，后面 $f(i)+1\to f(i+1)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
//#define int long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 200005
#define inf 0x3f3f3f3f

bool vis[maxn];
int n,m,f[maxn],sum,mn[maxn],mx[maxn],g[maxn];
vi e[maxn];
void addin(int x){sum+=(!vis[x]),vis[x]=1;}

signed main()
{
	n=read(),m=read();
	For(i,1,n)mn[i]=n+1;
	For(i,1,m){
		int u=read(),v=read();
		mn[u]=min(mn[u],v);
		mn[v]=min(mn[v],u);
		mx[u]=max(mx[u],v);
		mx[v]=max(mx[v],u);
		e[min(u,v)].pb(max(u,v));
	}
	For(i,1,n)mx[i]=max(mx[i],mx[i-1]);
	memset(f,63,sizeof f);
//	For(j,2,n){
//		int sum=0,p=j-1;
//		For(i,max(j,mx[j-1]),n){
//			while(p<i) ++p,sum+=(mn[p]>j-1);
//			f[i]=min(f[i],f[j-1]+sum);
//		}
//	}
	For(j,1,n-1){
		f[j]=min(f[j],f[j-1]+1);
		int nowf=(j==1?0:f[j]);
		addin(j);
		for(auto v:e[j])addin(v);
		// mx[j]
		int to=max(mx[j],j+1);
		f[to]=min(f[to],nowf+to-sum);
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：Mars_Dingdang (赞：2)

从假贪心做法自然想到的 DP。

### 题目大意
给定一张 $n$ 个点 $m$ 条边的无向图（不一定联通），求最少添加几条边使得图连通并且 $1\sim n$ 是一个合法的 bfs 序。

$n,m\le 2\times 10^5$。

### 大体思路
我们先考虑什么情况下可以闭着眼睛连边。

比如 $1$ 往 $n$ 连了一条边，那么 $2\sim n-1$ 都得往 $1$ 连边了。

也就是说，如果 $i$ 向 $j$ 连了一条边（$i<j$），那么区间 $(i,j)$ 中的点要么在之前就有边连向他，要么他就得向 $i$ 增添一条边。也就是说，考虑到 $i$ 为止的情况，其对到 $j$ 为止的情况的贡献就是本身的代价加上要连的边数 $cnt(i,j)$ 表示 $(i,j)$ 中没有入边的点的数量。这里区间是开区间还是闭区间不重要，因为后文 DP 转移时会发现 $i,j$ 处一定有入边。

当没有跨过去的边时，容易发现没有贪心策略可以帮助我们直接把当前点挂在之前某个点下面，因此我们考虑 DP。

记 $f_i$ 表示 $1\sim i$ 划分成若干层的代价。考虑 $i$ 可以转移到哪些 $j$。容易发现如果存在一条边 $e=(u,v)$ 满足 $u\le i$ 且 $v\ge j$，则说明 $i$ 处划分一层之后一直到 $v$ 都是下一层，不能在 $j$ 处划分。

也就是说 $i$ 能贡献到的最小的 $j$ 是前 $i$ 个点往后连到的编号最大的点的编号 $mx_i$，即 $f_i+cnt(i,j)\to f_j|j\ge mx_i$。

看似好像有好多 $j$ 会被贡献到，但实际上这样的 $j$ 是一段后缀，并且由于 $j\ge mx_i$，除了 $mx_i$ 后面所有的 $j$ 一定没有入边，进而会使得 $cnt$ 增加一，即 $cnt(i,j+1)=cnt(i,j)+1$，因此 $f_{j+1}=f_j+1$。所以我们把贡献打在 $j=mx_i$ 处，然后处理到每一个 $i$ 时让 $f_i$ 与 $f_{i-1}+1$ 取 $\min$ 即可。

需要特别注意的是，没有位置会这样贡献 $f_1$，因此 $f_2$ 不能和 $f_1+1$ 取 $\min$。

时间复杂度 $\mathcal O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 2e5 + 5, inf = 0x3f3f3f3f;
template <typename T>
inline void chkmax(T &x, T y) {x = (x > y ? x : y);}
template <typename T>
inline void chkmin(T &x, T y) {x = (x < y ? x : y);}
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int n, m, mx[maxn], f[maxn], res;
vector <int> e[maxn];
bool vis[maxn];
inline void add(int u) {res += (!vis[u]), vis[u] = 1;}
int main () {
//	memset(d, inf, sizeof d);
	read(n); read(m);
	rep(i, 1, m) {
		int u, v;
		read(u), read(v);
		chkmax(mx[u], v);
		chkmax(mx[v], u);
		e[min(u, v)].push_back(max(u, v));
	}
	rep(u, 2, n) chkmax(mx[u], mx[u - 1]);
	memset(f, 0x3f, sizeof f);
	f[1] = 0;
	rep(u, 1, n - 1) {
		chkmin(f[u], f[u - 1] + 1);
		add(u); for(auto v : e[u]) add(v);
		int v = max(mx[u], u + 1);
		chkmin(f[v], f[u] + v - res);
		if(u == 1) f[u] = inf;
	}
	chkmin(f[n], f[n - 1] + 1);
	writeln(f[n]);
	return 0;
}
```

---

## 作者：naught (赞：0)

# [CCO2021] Bread First Search

## 题意

给一个无向图，求要再加多少条边使得 $1 \sim n$ 是合法的 `bfs` 序。

## Solution

首先考虑一个特殊情况：$1$ 与 $n$ 连了一条边。

那么 $1$ 和其他所有点都要连一条边。

把这个放到一般情况便有：

>推论：若 $i$ 与 $j$（$i < j$）连了一条边，那么对于区间 $\left ( i, j\right )$ 的每个点，要么 $i$ 与其有一条直接连接的边，要么要加一条直接连接的边。

这样的话所有点会被分层，并且每一层的点是连续的同时相邻层的点编号也连续，不难想到定义 $f_{i,j}$ 为 $i$ 和 $j$ 在同一层时要加的最少边数，时间复杂度为 $O(n^3)$。

由推论，对于一个锚定的点 $i$，所有在一层的 $j$ 是连续的，可以用后缀进行维护，可以优化至 $O(n)$。

## Code

```cpp
//written by Naught
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define Maxn 200005
#define Inf 0x3f3f3f3f
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define fr(i, r, l) for (int i = l; i >= r; --i)
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}

struct Edge
{
    int to, nxt;
}e[Maxn<<1];
int h[Maxn], cnt;

void add(int u, int v)
{
    e[++cnt] = {v, h[u]};
    h[u] = cnt;
}

int n, m, g[Maxn], f[Maxn], sum;
bool vis[Maxn];

void reach(int u) {sum += (vis[u]? 0 : 1), vis[u] = true;}

int main()
{
    n = read(), m = read();
    fo(i, 1, m)
    {
        int u = read(), v = read();
        g[u] = max(g[u], v), g[v] = max(g[v], u);
        add(u, v), add(v, u);
    }

    memset(f, Inf, sizeof(f));
    fo(i, 1, n) g[i] = max(g[i], g[i-1]);

    fo(i, 1, n-1)
    {
        f[i] = min(f[i], f[i-1]+1);
        reach(i);
        for(int j = h[i]; j; j = e[j].nxt)
        {
            int v = e[j].to;
            reach(v);
        }
        int lst = max(g[i], i+1);
        f[lst] = min(f[lst], (i == 1 ? 0 : f[i]) + lst - sum);
    }

    printf("%d", f[n]);

    return 0;
}
```

---

## 作者：7KByte (赞：0)

题意：给定一个图，求最少需要加入多少条边使得图的 $BFS$ 顺序可能为 $1\sim N$。

神仙题，首先得发现这是个线性 DP，并写出状态和方程，做到这里这题就完成了一半。

状态，我们定义 $f_i$ 表示节点 $1\sim i$​ 的子图的答案。

直接转移可以做到 $\mathcal{O}(N^3)$，考虑前缀和优化可以做到 $\mathcal{O}(N^2)$。

由于前缀和是二维的，考虑优化，观察一下发现 $s_i$ 是在 $s_{i - 1}$ 的基础上改动几个，所以直接可持久化线段树。

手算一下并打表验证不难发现这题具有决策单调性，直接队列优化即可。

更详细的题解见[**我的博客**](https://www.cnblogs.com/SharpnessV/p/15187502.html)。

时间复杂度 $\mathcal{O}(N\log ^2 N)$，空间 $\mathcal{O}(N\log N)$。

---

