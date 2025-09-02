# Delivery Bears

## 题目描述

Niwel is a little golden bear. As everyone knows, bears live in forests, but Niwel got tired of seeing all the trees so he decided to move to the city.

In the city, Niwel took on a job managing bears to deliver goods. The city that he lives in can be represented as a directed graph with $ n $ nodes and $ m $ edges. Each edge has a weight capacity. A delivery consists of a bear carrying weights with their bear hands on a simple path from node $ 1 $ to node $ n $ . The total weight that travels across a particular edge must not exceed the weight capacity of that edge.

Niwel has exactly $ x $ bears. In the interest of fairness, no bear can rest, and the weight that each bear carries must be exactly the same. However, each bear may take different paths if they like.

Niwel would like to determine, what is the maximum amount of weight he can deliver (it's the sum of weights carried by bears). Find the maximum weight.

## 说明/提示

In the first sample, Niwel has three bears. Two bears can choose the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF653D/4b21426951c2d0e6a3a42095e6d1b45a7f4622f3.png), while one bear can choose the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF653D/68a85f5b867b3c9f9afa90e0eb0708e14f1376a4.png). Even though the bear that goes on the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF653D/68a85f5b867b3c9f9afa90e0eb0708e14f1376a4.png) can carry one unit of weight, in the interest of fairness, he is restricted to carry 0.5 units of weight. Thus, the total weight is 1.5 units overall. Note that even though Niwel can deliver more weight with just 2 bears, he must use exactly 3 bears on this day.

## 样例 #1

### 输入

```
4 4 3
1 2 2
2 4 1
1 3 1
3 4 2
```

### 输出

```
1.5000000000
```

## 样例 #2

### 输入

```
5 11 23
1 2 3
2 3 4
3 4 5
4 5 6
1 3 4
2 4 5
3 5 6
1 4 2
2 5 3
1 5 2
3 2 30
```

### 输出

```
10.2222222222
```

# 题解

## 作者：Reywmp (赞：1)

- ## CF653D Delivery Bears

比较特别的网络流题目。

~~就是无脑乱搞，相信自己就过了！~~


-----------

- ### Prelude

这个题上手就感觉太神必了，根本感觉不是网络流。~~该用网络流你不用，不用的你一个劲想。~~

因为众所周知题面告诉你一个算法的那这个题肯定不用这个算法（雾）。

为啥要说这个，因为这个题上手一看：每条边有容量，有流量，求最大流量，这不是网络流吗？

但是其实感觉很难做，因为要求的流量限制太多，很难直接做。于是我们需要转换思路了。

--------------

- ### Solution

这个题也没啥建模，直接讲吧。

就是说，我们考虑到对于一个要求的重量的限制只是边上的限制 $c_i$ 。如果我们知道货物的统一重量 $d$ ，那么我们就只需要考虑一条边上经过的熊的个数上限 $\displaystyle\lfloor \frac{c_i}{d}\rfloor$ 。这样有显然的好处：

- 我们可以把运算转换成 `int` 类型的。
- 这样方便判断每只熊是否能到达。

这样就可以直接判了，因为把每只熊看作 $1$ 的流量，那么每只熊 $1\rightarrow n$ 一路走下去如果不溢出必然有 $x$ 的流量。所以只需要判断能否有 $x$ 流量到达汇点 $n$ 就这个 $d$ 满足条件。

那么 $d$ 怎么确定呢，都说到这份上了，还不想想二分答案？

上面那个显然是 `check(mid)` 的思路，所以直接做二分答案，上界 `r` 最多也就 $1e6$ 。

一看 $n\leq 50$ ，显然可以过。

最后的答案是总重量，所以是 $x\times ans$ 。

-------------------------

- ### Code

实现判断直接用 $\texttt{Dinic}$ 跑最大流就可以了，超过 $x$ 即是合法的。

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<map>
#include<stack>
//#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define INL inline
#define Re register

//Tosaka Rin Suki~
using namespace std;

INL int read()
{
	 int x=0;int w=1;
	 char ch=getchar();
	 while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	 if(ch=='-')w=-1,ch=getchar();
	 while(ch>='0'&&ch<='9')
	 {x=(x<<1)+(x<<3)+ch-48,ch=getchar();}
	 return x*w;
}

INL int mx(int a,int b){return a>b?a:b;}
INL int mn(int a,int b){return a<b?a:b;}

const int INF=1<<30,N=1005,M=1000005;

int n,m,x,S,T;

struct Rey
{
	int nxt,to,c;
}e[M];
int head[N],cnt;
int dis[N],cur[N];
int a[N],b[N],c[N];

INL void add_edge(int u,int v,int w)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].c=w;
	head[u]=cnt;
}

INL void add_flow(int u,int v,int w)
{
	add_edge(u,v,w);
	add_edge(v,u,0);
}

INL bool bfs()
{
	queue <int> q;
	q.push(S);
	memset(dis,0,sizeof(dis));
	dis[S]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt)
		{
			int go=e[i].to;
			if(e[i].c>0&&!dis[go])
			{
				dis[go]=dis[u]+1;
				q.push(go);
				if(dis[T])return 1;
			}
		}
	}
	return dis[T]!=0;
}

INL int dfs(int x,int flow)
{
	if(x==T||!flow)return flow;
	int usd=0;
	for(int i=cur[x];i;i=e[i].nxt)
	{
        cur[x]=i;
		int go=e[i].to;
		if(e[i].c>0&&dis[go]==dis[x]+1)
		{
			int C=dfs(go,min(flow-usd,e[i].c));
			usd+=C;
			e[i].c-=C,e[i^1].c+=C;
			if(flow==0)return usd;
		}
	}
	if(!usd)dis[x]=0;
	return usd;
}

INL int Dinic()
{
	int fl=0;
	while(bfs())
	{
		memcpy(cur,head,sizeof(head));
		fl+=dfs(S,INF);
	}
	return fl;
}

INL bool check(double p)
{
	cnt=1;memset(head,0,sizeof(head));
	for(int i=1;i<=m;i++)
	{
        int x=min(c[i]/p,1e9);//p 有时候会莫名其妙的很小或者一些溢出问题，所以特判。
		add_flow(a[i],b[i],x);
	}
	return Dinic()>=x;
}

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read(),x=read();
	S=1,T=n;
	for(int i=1;i<=m;i++)
	{
		a[i]=read();b[i]=read(),c[i]=read();
	}
	double l=0,r=1e6;
	for(int i=0;i<80;i++)//因为是 double 所以直接暴力循环多次，在复杂度能承受范围以及误差范围内即可。
	{
		double mid=(l+r)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.12lf\n",(double)l*x);
	return 0;
}
```



---

## 作者：Priestess_SLG (赞：0)

CSP 2024 前最后一篇了！祝所有人 ++RP！

-------

典题。看到“最大运输量”可以快速的想到网络最大流。因此考虑二分答案 $d$，然后对于建出的新图跑网络最大流。合法的条件即为流量 $\ge x$。

网络流可以跑 Dinic。

```cpp
bool begmem;
#include <bits/stdc++.h>
#define int long long
using namespace std;
class FastIO {
public:
    int read() {
        int o = 1, x; char ch;
        while (!isdigit(ch = getchar())) {
            if (ch == '-') {
                o = -1;
            }
        }
        x = ch ^ 48;
        while (isdigit(ch = getchar())) {
            x = (x << 3) + (x << 1) + (ch ^ 48);
        }
        return o * x;
    }
} ; FastIO io;

void calcqwq();
const int N = 200100, inf = 1e18;
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
inline void swap(int &a, int &b) { a ^= b ^= a ^= b; }
namespace Flow {

struct edg {
    int e, f, o;
    edg(int a, int b) { e = a, f = b, o = 0; }
} ; vector<edg> z[N];
int dep[N], S, T;
void link(int s, int e, int f) {
    z[s].push_back({edg(e, f)}), z[e].push_back(edg(s, 0));
    int s1 = z[s].size() - 1, s2 = z[e].size() - 1;
    z[s][s1].o = s2, z[e][s2].o = s1;
}
bool bfs() {
    queue<int> q;
    memset(dep, 0, sizeof dep), dep[S] = 1, q.push(S);
    while (q.size()) {
        int p = q.front(); q.pop();
        for (auto &[r, f, _] : z[p]) if (f && !dep[r]) {
            dep[r] = dep[p] + 1, q.push(r);
            if (r == T) return true;
        }
    } return false;
}
int dfs(int p, int f) {
    if (p == T) return f;
    int s = 0;
    for (int i = 0; i < z[p].size(); ++i) {
        if (!f) break;
        int q = z[p][i].e, fx = z[p][i].f;
        if (fx && dep[p] + 1 == dep[q]) {
            int delta = dfs(q, min(f, fx));
            z[p][i].f -= delta, z[q][z[p][i].o].f += delta;
            f -= delta, s += delta;
        }
    }
    return s ? s : (dep[p] = 0);
}
int dinic() {
    int s = 0;
    while (bfs()) s += dfs(S, inf);
    return s;
}
}
struct qwq {
    int a, b, c;
} ed[N];
int n, m, x;
bool check(double p) {
    for (int i = 1; i <= n; ++i) {
        Flow::z[i].clear();
        Flow::dep[i] = 0;
    }
    Flow::S = 1, Flow::T = n;
    for (int i = 1; i <= m; ++i) {
        Flow::link(ed[i].a, ed[i].b, (int)(1. * ed[i].c / p));
    }
    return Flow::dinic() >= x;
}
signed main() {
    atexit(calcqwq);
    n = io.read(), m = io.read(), x = io.read();
    for (int i = 1; i <= m; ++i) {
        ed[i].a = io.read(), ed[i].b = io.read(), ed[i].c = io.read();
    }
    double l = 1e-7, r = 1e7, best;
    for (int i = 0; i < 100; ++i) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    printf("%.15lf\n", r * x);
    return 0;
}
bool endmem;
void calcqwq() {
    fprintf(stderr, "Memory = %.5lf\n", (&begmem - &endmem) / 1048576.);
}
```

---

