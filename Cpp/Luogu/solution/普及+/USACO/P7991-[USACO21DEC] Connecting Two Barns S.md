# [USACO21DEC] Connecting Two Barns S

## 题目描述

Farmer John 的农场由 $N$ 块田地（$1 \leq N \leq 10^5$）组成，编号为 $1 \ldots N$。在这些田地之间有 $M$ 条双向道路（$0 \leq M \leq 10^5$），每条道路连接两块田地。

农场有两个牛棚，一个在田地 1 中，另一个在田地 $N$ 中。Farmer John 希望确保有一种方式可以沿着一组道路在两个牛棚之间行走。 他愿意建造至多两条新道路来实现这一目标。由于田地的位置因素，在田地 $i$ 和 $j$ 之间建造新道路的花费是 $(i-j)^2$。

请帮助 Farmer John 求出使得牛棚 $1$ 和 $N$ 可以相互到达所需要的最小花费。

## 说明/提示

【样例解释】

- 第一个子测试用例中，最优的方式是用一条道路连接田地 2 和 3，用一条道路连接田地 3 和 4。
- 第二个子测试用例中，最优的方式是用一条道路连接田地 3 和 4。不需要第二条道路。

【数据范围】

- 测试点 2 满足 $N \le 20$。
- 测试点 3-5 满足 $N \le 10^3$。
- 测试点 6-10 没有额外限制。

## 样例 #1

### 输入

```
2
5 2
1 2
4 5
5 3
1 2
2 3
4 5```

### 输出

```
2
1
```

# 题解

## 作者：望月Asta (赞：12)

### 题意

给出一个 $n$ 个点 $m$ 条边，编号从 $1$ 到 $n$ 的无向图，可以以 $(i - j)^2$ 的代价在任意的  $i,j$ 之间连一条边。

现在可以进行不超过两次连边操作，求使得 $1$ 和 $n$ 两点连通的最小代价。

### 解法

首先不超过两次连边一定是以下几种形式中的一种 : 

- $1,n$ 初始即连通，不需连边。

- 从 $1$ 和 $n$ 分别所在的连通分量中找出差值最小的两个点连边，共连一条边。

- 将 $1$ 和 $n$ 分别所在的连通分量和第三个连通分量相连，共连两条边。

可以发现都是把某个点所在的连通分量与 $1$ 或 $n$ 连通的过程。

令 $f_i$ 表示将点 $i$ 所在的连通分量与 $1$ 连接的最小代价，$g_i$ 表示将点 $i$ 所在的连通分量与 $n$ 连接的最小代价。

那么答案为 : $\min_{i = 1}^{n} \{f_i + g_i\}$。

然后考虑如何求出 $f$ 和 $g$。

首先可以求出初始与 $1,n$ 在同一连通分量的点的集合，记为 $F$ 与 $G$。

对于一个点 $u$，在 $F,G$ 中分别二分查找得到与其差值最小的点并尝试更新最小值。

时间复杂度 $\mathcal{O} (n \log n)$。

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long ll;
constexpr int N = 100005;

ll f[N],g[N];
int F[N],G[N],fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    int n,m;
    scanf("%d %d",&n,&m);
    memset(f,127,sizeof(f));
    memset(g,127,sizeof(g));
    for(int i = 1;i <= n;++i)
        fa[i] = i;
    for(int i = 1;i <= m;++i) {
        int u,v;
        scanf("%d %d",&u,&v);
        u = find(u),v = find(v);
        if(u == v) continue;
        fa[u] = v;
    }
    int r1 = find(1),rn = find(n);
    f[r1] = 0,g[rn] = 0;
    int cntF = 0,cntG = 0;
    for(int i = 1;i <= n;++i) {
        int u = find(i);
        if(u == r1) F[++cntF] = i;
        else if(u == rn) G[++cntG] = i;
    }
    for(int i = 1;i <= n;++i) {
        int u = find(i);
        if(u != r1) {
            int pre = std::upper_bound(F + 1,F + cntF + 1,i) - F - 1;
            f[u] = std::min(f[u],(ll)(i - F[pre]) * (i - F[pre]));
            if(pre < cntF) {
                ++pre;
                f[u] = std::min(f[u],(ll)(i - F[pre]) * (i - F[pre]));
            }
        }
        if(u != rn) {
            int nxt = std::upper_bound(G + 1,G + cntG + 1,i) - G;
            g[u] = std::min(g[u],(ll)(i - G[nxt]) * (i - G[nxt]));
            if(nxt > 1) {
                --nxt;
                g[u] = std::min(g[u],(ll)(i - G[nxt]) * (i - G[nxt]));
            }
        }
    }
    ll ans = (ll)(n - 1ll) * (n - 1ll);
    for(int i = 1;i <= n;++i) {
        int u = find(i);
        ans = std::min(ans,f[u] + g[u]);
    }
    printf("%lld\n",ans);
}

int main() {
    int T;
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}

```

---

## 作者：lyt_awa (赞：10)

## 简要题意
给出一个 $n$ 个点 $m$ 条边，编号为 $1…N$ 的无向图，可以以 $(i - j)^2$ 的代价在任意的 $i,j$ 之间连一条边。现在可以进行**不超过两次**连边操作，求使得 $1$ 和 $n$ 两点连通的最小代价。
## 思路
明显可以用**并查集**来记录每一个点分别在哪一个连通块里。

接下来用 $f_i$ 来表示 $i$ 所在的连通块的代表点。

然后对于 $1$ 和 $n$ 两点有两种情况：
1. 在同一个连通块里。
2. 在两个不同的连通块里。

### 情况 1
很明显不需要连任何一条边，所以代价就是 $0$。

### 情况 2
可以**直接在 $f_1$ 和 $f_n$ 中最近的两点连边**，或者**通过其他连通块来间接的连接 $f_1$ 和 $f_n$**。
### 怎么求出最小值？(对于情况2)
可以先处理出哪些点在 $f_1$ 中，哪些点在 $f_n$ 中，分别记录在 $S$ 数组和 $E$ 数组中。

对于每一个连通块 $f_i$ 计算出其与 $f_1$ 和 $f_n$ 通过连一条边连通的最小代价，分别记录在 $s[f_i]$ 和 $e[f_i]$ 中（这里的计算可以通过二分来实现）。

最后最小代价为 $\min_{1\le i\le n} s[f_i]+e[f_i]$。

AC代码奉上。
```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 1e5 + 5;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

int t, n, m, fa[maxn], S[maxn], E[maxn];
ll s[maxn], e[maxn];

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main() {
	t = read();
	while (t--) {
		memset(s, 0x3f, sizeof(s));
		memset(e, 0x3f, sizeof(e));
		n = read(); m = read();
		for (int i = 1; i <= n; ++i) fa[i] = i;
		for (int i = 1; i <= m; ++i) {
			int x = read(), y = read();
			x = find(x); y = find(y);
			fa[x] = y;
		}
		if (find(1) == find(n)) {
			printf("0\n");
			continue;
		}
		int rt1 = find(1), rtn = find(n), ct1 = 0, ctn = 0;
		s[rt1] = 0; e[rtn] = 0;
		for (int i = 1; i <= n; ++i) {
			int fi = find(i);
			if (rt1 == fi) S[++ct1] = i;
			if (rtn == fi) E[++ctn] = i;
		}
		ll ans = 0x3f3f3f3f3f3f3f3f;
		for(int i = 1; i <= n; ++i) {
			int fi = find(i);
			if(fi != rt1) {
				int ub1 = upper_bound(S + 1, S + ct1 + 1, i) - S - 1;
				s[fi] = min(s[fi], (ll)(i - S[ub1]) * (i - S[ub1]));
				if (ub1 < ct1) {
					++ub1;
					s[fi] = min(s[fi], (ll)(i - S[ub1]) * (i - S[ub1]));
				}
			}
			if (fi != rtn) {
				int ubn = upper_bound(E + 1, E + ctn + 1, i) - E;
				e[fi] = min(e[fi], (ll)(i - E[ubn]) * (i - E[ubn]));
				if(ubn > 1) {
					--ubn;
					e[fi] = min(e[fi], (ll)(i - E[ubn]) * (i - E[ubn]));
				}
			}
		}
		for(int i = 1; i <= n; ++i) {
			int fi = find(i);
//			printf("@%lld %lld\n", s[fi], e[fi]);
			ans = min(ans, s[fi] + e[fi]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Ginger_he (赞：6)

# 题解  
**并查集+二分查找**好题  
由于至多连两条边，所以只有三种情况。  
若不连边，则 $1$ 和 $n$ 连通；  
若连一条边，则在分别在 $1$ 和 $n$ 所在的连通块里找一个点连边；  
若连两条边，则找一个点分别与 $1$ 和 $n$ 所在的连通块里找一个点连边。  
这三种情况的最小值就是答案，时间复杂度 $\Theta(n\log n)$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int t,n,m,u,v,fa[maxn];
ll ans;
vector<int> g[maxn];
ll square(int x)
{
	return (ll)x*x;
}
int find(int x)
{
	if(x==fa[x])
		return x;
	return fa[x]=find(fa[x]);
} 
ll dis(int x,int y)
{
	ll res=1e18;
	int a,b;
	for(int i=0;i<g[x].size();i++)
	{
		a=g[x][i],b=lower_bound(g[y].begin(),g[y].end(),a)-g[y].begin();//二分
		if(b) res=min(res,square(a-g[y][b-1]));//比a小里最接近a的 
		if(b<g[y].size()) res=min(res,square(a-g[y][b]));//比a大里最接近a的 
	}
	return res;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			fa[i]=i;
			g[i].clear();
		}//初始化 
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&u,&v);
			fa[find(u)]=find(v);
		}
		for(int i=1;i<=n;i++)
			g[find(i)].push_back(i);
		u=fa[1],v=fa[n],ans=dis(u,v);//1与n直接相连 
		for(int i=1;i<=n;i++)
		{
			if(fa[i]==u||fa[i]==v||fa[i]!=i)
				continue;
			ans=min(ans,dis(i,u)+dis(i,v));//找到某个点与1和n相连 
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：3)

好题。

# 题目大意

给出一个 $n$ 个点 $m$ 条边，编号从 $1$ 到 $n$ 的无向图，可以以 $(i-j)^2$ 的代价在任意的 $i,j$ 之间连一条边。

现在可以进行不超过两次连边操作，求使得 $1$ 和 $n$ 两点连通的最小代价。

# 题目分析

因为最多只能连 $2$ 条，所以只会出现三种情况：

+ $1$ 和 $n$ 已在同一连通分量里；

+ $1$ 所在的连通分量和 $n$ 所在的连通分量通过连接一条边使得 $1$ 和 $n$ 在同一连通分量里。

+ $1$ 所在的连通分量和 $n$ 所在的连通分量通过分别向另一连通分量连接一条边使得 $1$ 和 $n$ 在同一连通分量里。

第一种情况显然代价为 $0$。

性质：最优策略中连边的两个顶点差值应尽量小。

其他情况我们通过并查集将所有边的两个顶点加在同一连通分量里，然后枚举点 $i$，更新答案，答案即为 $\min\limits_{i=1}^ndist(fa_1,i)+dist(i,fa_n)$。

怎么计算 $dist(i,j)$ 呢？可以用 $st_i$ 记录以点 $i$ 为祖先的子孙集合，然后枚举 $st_i$ 的所有元素（记其中一个子孙节点为 $k$），再在 $st_j$ 中二分查找大于 $k$ 的最近位置 $v$，枚举所有的边 $(k,v)$ 取最小价值即可。

# 代码

```cpp
//2022/2/19
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <algorithm>
#include <set>
#define int long long
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int INF = 0x3f3f3f3f3f3f3f3f;
const int ma = 1e5 + 5;
int fa[ma];
set<int>st[ma];
int T,n,m;
inline int getf(int x) {
	return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
inline void merge(int x,int y) {
	int f1 = getf(x),f2 = getf(y);
	if (f1 != f2) fa[f1] = f2;
}
inline int sq(int x) {
	return x * x;
}
inline int dist(int x,int y) {
	int ans = INF;
	for (set<int>::iterator it = st[x].begin();it != st[x].end(); ++ it) {
		set<int>::iterator tmp = st[y].upper_bound(*it);
		if (tmp != st[y].end()) {
			ans = min(ans,sq(*tmp - *it));
		}
		if (tmp != st[y].begin()) {
			ans = min(ans,sq(*(-- tmp) - *it));
		}
	}
	return ans;
}
inline void solve() {
	n = read(),m = read();
	for (register int i = 1;i <= n; ++ i) {
		fa[i] = i;
		st[i].clear();
	}
	for (register int i = 1;i <= m; ++ i) {
		int u = read(),v = read();
		merge(u,v);
	}
	for (register int i = 1;i <= n; ++ i) {
		st[getf(i)].insert(i);
	}
	if (getf(1) == getf(n)) {
		puts("0");
	} else {
		int ans = dist(getf(1),getf(n));
		for (register int i = 1;i <= n; ++ i) {
			if (getf(1) != getf(i) && getf(n) != getf(i)) {
				ans = min(ans,dist(i,getf(1)) + dist(i,getf(n)));
			}
		}
		printf("%lld\n",ans);
	}
}
signed main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	T = read();
	while (T --) {
		solve();
	}

	return 0;
}
```

---

## 作者：nydzsf_qwq (赞：3)

## P7991 题解

在连完所有的道路以后，这 $n$ 个点会被分成若干个连通块

由于只能建两条道路，所以新建的道路只可能是这种情况

$1$ 号点所在的连通块上的一点 $\rightarrow$ 连通块 $A$ 上的一点 和 连通块 $A$ 上的一点 $\rightarrow$ $n$ 号点所在的连通块上的一点

这里的连通块 $A$ 可以是 $1$ 号点或者 $n$ 号点所在的连通块，因为可以令建两端为同一点的道路的费用为 $0$ 

首先建一个并查集，每建一条边就做一次合并的操作

这样就可以将 $1$ 号点和 $n$ 号点所在的连通块内的所有点的编号**依次**列出来，分别开两个数组 $a$ 和 $b$ 保存

之后枚举 $1\sim n$ 中的所有点，分别在 $a$ 中二分这个点的编号，在算出数组 $a$ 中比这个点编号小的且编号最大的点和比这个点编号大且编号最小的点分别是多少后，算出这个点到 $a$ 中的点所需要花的最小费用，并记录到这个点所在的连通块中

这样对于每个连通块都可以计算出建一条连接这个连通块内的一点到 $1$ 号点所在连通块内的一点所需要的最小费用

对数组 $b$ 同理

最后进行统计即可

#### 友情提示：

1、最终答案要开 `long long`

2、下面的代码中有一些小错误，请勿抄袭题解

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,fa[100005],a[100005],b[100005],c[100005],d[100005],cnt1,cnt2;
long long ans;
int find(int x) {
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y) {
	x=find(x),y=find(y);
	fa[x]=y;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i) fa[i]=i;
		for(int i=1,u,v;i<=m;++i) scanf("%d%d",&u,&v),merge(u,v);	//并查集合并
		cnt1=cnt2=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;++i) {
			if(find(i)==find(1)) a[++cnt1]=i;
			if(find(i)==find(n)) b[++cnt2]=i;	//统计1号点和n所在连通块内的点
		}
		memset(c,0x3f3f3f3f,sizeof(c));
		memset(d,0x3f3f3f3f,sizeof(d));
		for(int i=1;i<=n;++i) {
			int t1=lower_bound(a+1,a+cnt1+1,i)-a;	//二分
			if(t1==1) c[find(i)]=min(c[find(i)],abs(a[1]-i));
			else c[find(i)]=min(c[find(i)],min(abs(a[t1]-i),abs(a[t1-1]-i)));	//更新最小费用
		}
		for(int i=1;i<=n;++i) {	//同上
			int t1=lower_bound(b+1,b+cnt2+1,i)-b;
			if(t1==1) d[find(i)]=min(d[find(i)],abs(b[1]-i));
			else d[find(i)]=min(d[find(i)],min(abs(b[t1]-i),abs(b[t1-1]-i)));
		}
		ans=1ll*d[find(1)]*d[find(1)];
		for(int i=2;i<=n;++i) {
			if(find(i)==i) ans=min(ans,1ll*c[find(i)]*c[find(i)]+1ll*d[find(i)]*d[find(i)]);	//统计答案
		}
		printf("%lld\n",&ans);
	}
}
```



---

## 作者：lsj2009 (赞：3)

[更好的阅读体验。](https://www.luogu.com.cn/blog/lvsiji/solution-p7991)
## 题意
给定 $n$ 个点，问用****至多 $2$ 条路径****连接点 $1$ 和 $N$ 最小代价。
## 思路
看见这题第一反应：****并查集****！

题中，提到
“****他愿意建造至多两条新道路来实现这一目标****”，那么，也就是说，对于这题，有****三种****可能解法：

- 连接 $0$ 条路，当且仅当田地 $1$ 和田地 $N$ 处于同一连通分量。
- 连接 $1$ 条路，直接连接田地 $1$ 和田地 $N$，使之处于同一连通分量。
- 连接 $2$ 条路，通过一联通分量 $mid$ 间接连接田地 $1$ 和田地 $N$，使之处于同一连通分量。

对于一联通分量，我们可以考虑用 ```vector``` 将其存起来。

每次考虑连通分量 $i$ 中 $x$ 点去连接连通分量 $j$ 中的哪个 $y$ 点时，我们可以通过****二分查找**** ```lower_bound``` 去搜索离 $x$ 的 $j$ 中最近点。

细节较多，详见代码。
```cpp
#include<bits/stdc++.h>
#define int long long //十年OI一场空，不开longlong见祖宗
#define pd push_back
using namespace std;
const int N=1e5+5;
int fa[N],n,T,m;
int GetRoot(int x) { //并查集路径压缩（可以加上按轶合并）
	if(x==fa[x])
		return x;
	return fa[x]=GetRoot(fa[x]);
}
void Union(int x,int y) { //合并两个连通分量
	fa[GetRoot(x)]=fa[GetRoot(y)];
}
signed main() {
	scanf("%lld",&T);
	while(T--) {
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++) fa[i]=i;
		while(m--) {
			int u,v;
			scanf("%lld%lld",&u,&v);
			Union(u,v);
		}
		for(int i=1;i<=n;i++) GetRoot(i); 注意有些孩子可能还没有找到祖宗
		vector<int> vec[N]; //vector存连通分量
		for(int i=1;i<=n;i++) {
			if(fa[1]==fa[i]) vec[0].pd(i);
			else if(fa[n]==fa[i]) vec[n].pd(i);
			else vec[fa[i]].pd(i);
		}
//		for(int i=1;i<=n;i++) {
//			if(vec[i].empty()) continue;
//			printf("fa=%lld's list=[",i);
//			for(int j=0;j<vec[i].size();j++)
//				printf(" %lld",vec[i][j]);
//			puts("]");
//		}
		if(fa[1]==fa[n]) { //无需连接
			puts("0"); continue;
		}
		int ans=1e10;
		for(int i=0;i<vec[0].size();i++) { //直接连接
			int x=lower_bound(vec[n].begin(),vec[n].end(),vec[0][i])-vec[n].begin();
			if(x!=vec[n].size()) ans=min(ans,(vec[n][x]-vec[0][i])*(vec[n][x]-vec[0][i]));
			if(x!=0) ans=min(ans,(vec[0][i]-vec[n][x-1])*(vec[0][i]-vec[n][x-1]));
		}
		for(int i=2;i<n;i++) { //间接连接
			int a=1e5,b=1e5;
			if(vec[i].empty()) continue;
			for(int j=0;j<vec[i].size();j++) {
				int x=lower_bound(vec[0].begin(),vec[0].end(),vec[i][j])-vec[0].begin();
				int y=lower_bound(vec[n].begin(),vec[n].end(),vec[i][j])-vec[n].begin();
				if(x!=vec[0].size()) a=min(a,vec[0][x]-vec[i][j]);
				if(y!=vec[n].size()) b=min(b,vec[n][y]-vec[i][j]);
				if(x!=0) a=min(a,vec[i][j]-vec[0][x-1]);
				if(y!=0) b=min(b,vec[i][j]-vec[n][y-1]);
			}
			if(a==1e5||b==1e5) continue;
			ans=min(ans,a*a+b*b);
		}
		printf("%lld\n",ans);
	}
	return 1;
}
```


---

## 作者：free_fall (赞：2)

# 题目大意

有 $n$ 个点 $m$ 条边，要求连通 $1$ 到 $n$ 的无向图，连接 $(i,j)$ 需花费 $(i-j)^2$ 的代价，最多不能超过两次操作。

# 思路

一共有两种情况，第一种是 $1$ 和 $n$ 之间已经连通，不需要进行操作。

第二种是需要进行连接来达到题目要求。

首先很容易就可以想到用并查集来判断 $1$ 和 $n$ 是否连通，尽量找到下标相近的点进行连通，因为 $i-j$ 越接近 $(i-j)^2$ 越小，最终的花费就越优。

那么我们就可以通过枚举中间的那一个点（因为这一个点包括起点和终点，所以相当于同时判断了只连一条边的情况），来计算连通 $1$ 到 $n$ 的价值。

但是这样时间会超，我们可以使用一个 ```set<int> st[100005]``` 来优化搜索时间，这样时间复杂度就可以减少到 $O(n \log n)$ 级别。

# 代码

代码实现如下：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int fa[100005],t,n,m;
set<int> st[100005];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int sqr(int x){
	return x*x;
}
int solve(int x,int y){
	int ans=1e18;
	for(set<int>::iterator it=st[x].begin();it!=st[x].end();it++){
		set<int>::iterator j=st[y].lower_bound(*it);
		if(j!=st[y].end())ans=min(ans,sqr((*j)-*it));
		if(j!=st[y].begin())ans=min(ans,sqr(*(--j)-*it));
	}
	return ans;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++){
			fa[i]=i;
			st[i].clear();
		}
		for(int i=1,a,b;i<=m;i++){
			scanf("%lld%lld",&a,&b);
			fa[find(a)]=find(b);
		}
		if(find(1)==find(n)){
			printf("0\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			st[find(i)].insert(i);
		}
		int ans=solve(find(1),find(n));
		for(int i=1;i<=n;i++){
			if(fa[i]==find(1)||fa[i]==find(n)||fa[i]!=i)continue;
			ans=min(ans,solve(i,find(1))+solve(i,find(n)));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：wshcl (赞：2)

本题我们可以分为这几种情况

情况一： $1$ 与 $n$​ 本身已经联通

情况二：从 $1$ 和 $n$​ 分别所在的连通分量中找出两个点连一条边

情况三：将 $1$ 和 $n$​ 分别所在的连通分量和另一个连通分量连两条边

对于情况一，直接输出 $0$ 即可

对于情况二，我们可以先预处理出每个点到 $1$ 和 $n$ 分别所在的连通分量的最小代价，枚举 $1$ 和 $n$​ 分别所在的连通分量中的点

对于情况三，我们同样像像情况二一样预处理，之后枚举

但是这会 **TLE**

我们需要引入两个新的数组 $minA$ 与 $minB$​

 $minA_i$ 表示 $i$ 所在的连通分量到 $1$ 所在的连通分量的最小代价

 $minB_i$ 表示 $i$ 所在的连通分量到 $n$ 所在的连通分量的最小代价

之后照旧，复杂度就会小很多（ $O(n)$​ ）

```c++
#include <cstdio>
#include <vector>
#include <algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
typedef long long ll;
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+7;
struct bcj {
	int fa[N];
	inline bcj() {
		clear();
	}
	inline void clear() {
		for(int i=0;i<N;++i)
			fa[i]=i;
	}
	inline int find(int x) {
	    while(x!=fa[x]) 
	    	fa[x]=fa[fa[x]],x=fa[x];
	    return x;
	}
	inline void merge(int x,int y) {
		fa[find(x)]=find(y);
	}
	inline bool check(int x,int y) {
		return find(x)==find(y);
	}
}f;

vector<int> a,b;

ll A[N],B[N];
ll minA[N],minB[N];
int father[N];

int T,n,m;
ll ans;

inline void resetA() {
	sort(a.begin(),a.end());
	if(a.size()==1) {
		for(int i=1;i<=n;++i)
			A[i]=i-1;
		return ;
	}
	for(int i=1,l,r;i<a.size();++i) {
		l=a[i-1],r=a[i];
		for(int j=l;j<=r;++j)
			A[j]=min(j-l,r-j);
	}
	for(int i=a[a.size()-1];i<=n;++i)
		A[i]=i-a[a.size()-1];
}

inline void resetB() {
	sort(b.begin(),b.end());
	if(b.size()==1) {
		for(int i=1;i<=n;++i)
			B[i]=n-i;
		return ;
	}
	for(int i=1;i<=b[0];++i)
		B[i]=b[0]-i;
	for(int i=1,l,r;i<b.size();++i) {
		l=b[i-1],r=b[i];
		for(int j=l;j<=r;++j)
			B[j]=min(j-l,r-j);
	}
	for(int i=b[b.size()-1];i<=n;++i)
		B[i]=i-b[b.size()-1];
}

inline void Clean() {
	f.clear();
	a.clear(),b.clear();
	for(int i=1;i<=n;++i)
		minA[i]=inf,minB[i]=inf;
}

signed main() {
	scanf("%d",&T);
	for(;T;--T) {
		scanf("%d%d",&n,&m);
		Clean();
		for(int i=1,u,v;i<=m;++i) {
			scanf("%d%d",&u,&v);
			f.merge(u,v);
		}
		if(f.check(1,n)) {
			puts("0");
			continue;
		} // 1与n本身已经联通
		for(int i=1;i<=n;++i)
			if(f.check(1,i))
				a.push_back(i),father[i]=1;
			else if(f.check(i,n))
				b.push_back(i),father[i]=n;
			else
				father[i]=f.find(i);// 预处理每个点所在的连通分量
		resetA(),resetB();
		for(int i=1;i<=n;++i) {
			minA[father[i]]=min(minA[father[i]],A[i]);
			minB[father[i]]=min(minB[father[i]],B[i]);
		}
		ans=minB[1]*minB[1];
		for(int i=1;i<=n;++i)
			if(father[i]!=1 && father[i]!=n)
			ans=min(ans,minA[father[i]]*minA[father[i]]+minB[father[i]]*minB[father[i]]);
		printf("%lld\n",ans);
	}
    return 0;
}
```



---

## 作者：Yun_Mengxi (赞：1)

[题目传送门](/problem/P7991)

## 题意

给定 $n$ 个点 $m$ 条边的无向图，可以连两条及以下条边，连接 $i$ 和 $j$ 的代价是 $(i-j)^2$，求使 $1$ 到 $n$ 联通的最小代价。

## 分析

因为要让 $1$ 到 $n$ 联通，稍微想一想，发现可以使用并查集来维护每个联通块。

最多连两条边，所以不难想到分三种情况讨论：

1. 不用连边，$1$ 和 $n$ 在一个联通块里。

2. 连一条边，找 $1$ 和 $m$ 所在集合里差值最小的两个点连边。

3. 连两条边，可以找一个第三方联通块，让 $1$ 所在的集合差值最小的点和 $n$ 所在的集合差值最小的店与它连边。

可以发现，每种情况都是将当前联通块与 $1$ 或 $n$ 所在的联通块的过程，所以可以开两个数组分别维护当前联通块与 $1$ 和 $n$ 联通的最小代价。

二分查找一下差值最小的点就行了。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int M = 100005;

int t;
int n, m;
int u, v;
int fa[M];
int d1s[M], dns[M];
int cnt1, cntn;
int s1[M], sn[M];

int find(int x) {
  return x == fa[x] ? x : (fa[x] = find(fa[x]));
}

void merge(int u, int v) {
  u = find(u);
  v = find(v);
  u != v && (fa[u] = v);
}

void mian() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    d1s[i] = dns[i] = 0x3f3f3f3f3f3f3f3fll;
  }
  for (int i = 1; i <= m && cin >> u >> v; i++, merge(u, v)) {
  }
  int f1 = find(1), fn = find(n);
  cnt1 = cntn = d1s[f1] = dns[fn] = 0;
  for (int i = 1; i <= n; i++) {
    int si = find(i);
    si == f1 && (s1[++cnt1] = i);
    si == fn && (sn[++cntn] = i);
  }
  for (int i = 1; i <= n; i++) {
    int u = find(i), p;
    if (u != f1) {
      p = upper_bound(s1 + 1, s1 + cnt1 + 1, i) - s1 - 1;
      d1s[u] = min(d1s[u], (i - s1[p]) * (i - s1[p]));
      p < cnt1 && p++;
      d1s[u] = min(d1s[u], (i - s1[p]) * (i - s1[p]));
    }
    if (u != fn) {
      p = upper_bound(sn + 1, sn + cntn + 1, i) - sn;
      dns[u] = min(dns[u], (i - sn[p]) * (i - sn[p]));
      p > 1 && p--;
      dns[u] = min(dns[u], (i - sn[p]) * (i - sn[p]));
    }
  }
  int ans = (n - 1) * (n - 1);
  for (int i = 1; i <= n; i++) {
    int u = find(i);
    ans = min(ans, d1s[u] + dns[u]);
  }
  cout << ans << '\n';
}

signed main() {
  cin >> t;
  while (t--) {
    mian();
  }
  return 0;
}
```

---

## 作者：_Imaginary_ (赞：1)

## Problem

有一张图（不一定联通），两个点 $i,j$ 之间的边权为 $0$ 或 $(i-j)^2$，求从 $1$ 号点走到 $n$ 号点，走至多两条不为 $0$ 边的最短路。

## Solution

显然，可以转化为两部分：

- 从起点走到一个点

- 从另一个点走到终点。

第一步，把所有联通块求出来。

接下来，我们可以用 $\Theta(n)$ 的复杂度分别求出每个点到起点和终点的距离。

最后，在每个联通块中进行处理。	

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=1000000007;
const int N=100005,M=200005;
int hd[N],nxt[M],to[M],tot;
int f[N];
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=hd[x];
	hd[x]=tot;
}
int find(int x){return f[x]==x?x:find(f[x]);}
int n,m,T;
bool AAGH;
char vis[N];
int d1[N],d2[N],c1,c2;
ll len1[N],len2[N];
ll mn1[N],mn2[N];
void dfs(int u)
{
	if(u==n) AAGH=1;
	vis[u]=1;
	d1[++c1]=u;
//	s1.insert(u);
//	printf("1 in %d\n",u);
	for(int i=hd[u];i;i=nxt[i])
		if(!vis[to[i]]) dfs(to[i]);
}
void dfs2(int u)
{
	vis[u]=2;
//	s2.insert(u);
	d2[++c2]=u;
//	printf("2 in %d\n",u);
	for(int i=hd[u];i;i=nxt[i])
		if(!vis[to[i]]) dfs2(to[i]);
}
int main()
{
	scanf("%d",&T);
	set<int>::iterator it;
	int ta,tb;
	ll tc,td,ans;
	while(T--)
	{
		tot=0;
		ans=0x3f3f3f3f3f3f3f3f;
		memset(hd,0,sizeof(hd));
		memset(vis,0,sizeof(vis));
		memset(mn1,0x3f,sizeof(mn1));
		memset(mn2,0x3f,sizeof(mn2));
		c1=c2=0;
		scanf("%d%d",&n,&m);
		AAGH=0;
		for(int i=1;i<=n;i++) f[i]=i;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&ta,&tb);
			add(ta,tb);
			add(tb,ta);
			f[find(ta)]=find(tb);
		}
		dfs(1);
		if(AAGH)
		{
			printf("0\n");
			continue;
		}
		dfs2(n);
		sort(d1+1,d1+c1+1);
		sort(d2+1,d2+c2+1);
		d1[c1+1]=0x3f3f3f3f;
		d2[0]=0x3f3f3f3f;
		int it=1;
		for(int i=1;i<=n;i++)
		{
			if(abs(d1[it+1]-i)<=abs(d1[it]-i)) it++;
			len1[i]=1ll*(i-d1[it])*(i-d1[it]);
			
		}
		it=c2;
		for(int i=n;i>=1;i--)
		{
			if(abs(d2[it-1]-i)<=abs(d2[it]-i)) it--;
			len2[i]=1ll*(i-d2[it])*(i-d2[it]);
			
		}
//		for(int i=1;i<=n;i++) printf("%lld ",len1[i]); printf("\n");
//		for(int i=1;i<=n;i++) printf("%lld ",len2[i]); printf("\n");
		for(int i=1;i<=n;i++)
		{
			mn1[find(i)]=min(mn1[find(i)],len1[i]);
			mn2[find(i)]=min(mn2[find(i)],len2[i]);
		}
		for(int i=1;i<=n;i++)
		{
			ans=min(ans,mn1[i]+mn2[i]);
		}
		printf("%lld\n",ans);
//		printf("%lld\n",min(ans,hh(n)));
	}
	return 0;
}
```

---

## 作者：CCX_CoolMint (赞：1)


### 简化题意：
有 $N$ 个点和 $M$ 条双向边，你可以至多加两条边，使得 $1$ 号点和 $N$ 号点联通，对于 $i$ 和 $j$ 两点，加边的代价为 $(i-j)^2$。

### 思路：
对于题目给出的 $N$ 个点和 $M$ 条边的无向图，我们可以将其视作若干个连通块，而目标是让点 $1$ 所处的联通块（即为 $1$ 号连通块）和点 $N$ 所处的连通块（即为 $N$ 号连通块）联通。

考虑以下情况：

 - 点 $1$ 和点 $N$ 已经联通
 
 	
	
 	- 那么此时无需考虑加边，答案为 $0$。

 
 - 点 $1$ 和点 $N$ 尚未联通

 		
 	1. 我们可以选择 $1$ 号连通块的一个点或 $N$ 号连通块的一个点进行加边，此时仅需加 $1$ 条边即可。
 	2. 我们选择 $2-N$ 中的一个连通块，将该联通块的头与 $1$ 号连通块的尾连接，将该连通块的尾与 $N$ 号联通块的头连接，此时需要加 $2$ 条边。

	
	小结：不难发现其实情况一是情况二的特例。
 
 综上所述，我们用两个数组 $f$ 和 $g$ 记录第 $i$ 个连通块与第一个连通块的最短距离和与第 $N$ 个连通块的最短距离，然后相加即可得到第 $i$ 个连通块联通第一个连通块和第 $N$ 个连通块的最短距离。

### 注意：

错误思路:

![Wrong](https://cdn.luogu.com.cn/upload/image_hosting/3a37lpq6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

正确思路：

![True](https://cdn.luogu.com.cn/upload/image_hosting/v1sg4vnx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


### 实现：
使用并查集与二分查找实现。

时间复杂度 $O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll t,n,m,u,v,fa[1001000],ans,a[1001000],b[1001000],x,y;
ll cnt1,cnt2,f[201000],g[201000],tmp1,tmp2,p1,p2;
ll find(ll x)
{
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
void uni(ll x,ll y)
{
    x=find(x),y=find(y);
    fa[x]=y;
}
ll dis(ll x,ll y)
{
    return (x-y)*(x-y);
}
int main()
{
	cin>>t;
    while(t--)
    {
        ans=LONG_LONG_MAX;
        cnt1=cnt2=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++) fa[i]=i,f[i]=g[i]=LONG_LONG_MAX;
        for(int i=1;i<=m;i++)
        {
            cin>>u>>v;
            uni(u,v);
        }
        x=find(1),y=find(n);
        if(x==y)
        {
            cout<<0<<endl;
        }
        else
        {
            for(int i=1;i<=n;i++)
            {
                if(find(i)==x) a[++cnt1]=i;
                if(find(i)==y) b[++cnt2]=i;
            }
            for(int i=1;i<=n;i++)
            {
                tmp1=LONG_LONG_MAX;
                p1=lower_bound(a+1,a+1+cnt1,i)-a;
                if(p1<=cnt1) tmp1=min(tmp1,dis(a[p1],i));
                if(p1>1) tmp1=min(tmp1,dis(a[p1-1],i));
                f[find(i)]=min(f[find(i)],tmp1);
            }
            for(int i=1;i<=n;i++)
            {
                tmp2=LONG_LONG_MAX;
                p2=lower_bound(b+1,b+1+cnt2,i)-b;
                if(p2<=cnt2) tmp2=min(tmp2,dis(b[p2],i));
                if(p2>1) tmp2=min(tmp2,dis(b[p2-1],i));
                g[find(i)]=min(g[find(i)],tmp2);
            }
            for(int i=1;i<=n;i++)
            {
                if(find(i)==i) ans=min(ans,f[i]+g[i]);
            }
            cout<<ans<<endl;
        }
    }
	return 0;
}
```

---

## 作者：xkcdjerry (赞：1)

显然在一个连通块里的点就不用互相连接了，所以找到连接 $1$ 和 $n$ 的方式实际上就是找到连通 $1$ 与 $n$ 所在连通块的方式。

可以先扫一遍确定所有连通块，特判如果 $1$ 和 $n$ 在同一个直接输出 $0$ ，否则分类讨论到底是连一条边还是两条边。（此处定义距离为题目中边权，即点编号差的平方；点到连通块的距离是点到连通块中所有点距离的最小值）

* 如果连一条边，那就遍历 $1$ 的连通块中所有点，找一下离 $n$ 连通块距离最小的就是答案。
* 如果连两条边，枚举所有连通块，对于每个连通块寻找点 $x$ 使得其与 $1$ 所在连通块距离最短，然后寻找点 $y$ 使得其与 $n$ 所在连通块距离最短，可连接 $1$ 和 $x$，$y$ 和 $n$。
* 最后两种方案取一个 $\min$ 即可。

注意如果每次寻找距离 $1$ 或 $n$ 连通块中点的最小距离都使用 `lower_bound`/`upper_bound` 会很容易超时，所以可以先对于这两个连通块中的点按点编号排序之后 $O(n)$ 预处理所有点到连通块中点距离的最小值，后面直接 $O(1)$ 取用即可。

代码如下：

```c++
#include <cstdio>
#include <vector>
#include <algorithm>
#define N 100010
#define ll long long
using std::vector;
using std::sort;
using std::lower_bound;
using std::upper_bound;
int fa[N];
vector<int> chunk[N];
inline int sq(int x) {return x*x;}
int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
int f1[N],f2[N];
void once()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	while(m--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		u=find(u),v=find(v);
		if(u!=v) fa[u]=v;
	}
	if(find(1)==find(n))
	{
		puts("0");
		return;
	}
	for(int i=1;i<=n;i++) if(fa[i]==i) chunk[i]=vector<int>();
	for(int i=1;i<=n;i++) chunk[find(i)].push_back(i);
	auto &c1=chunk[find(1)],&c2=chunk[find(n)];
	sort(c1.begin(),c1.end());
	sort(c2.begin(),c2.end());
	for(int i=0;i<c1.size()-1;i++)
	{
		int j;
		for(j=c1[i];2*j<c1[i]+c1[i+1];j++) f1[j]=j-c1[i];
		for(;j<c1[i+1];j++) f1[j]=c1[i+1]-j;
	}
	for(int i=c1[0]-1;i>=1;i--) f1[i]=c1[0]-i;
	for(int i=c1[c1.size()-1];i<=n;i++) f1[i]=i-c1[c1.size()-1];


	for(int i=0;i<c2.size()-1;i++)
	{
		int j;
		for(j=c2[i];2*j<c2[i]+c2[i+1];j++) f2[j]=j-c2[i];
		for(;j<c2[i+1];j++) f2[j]=c2[i+1]-j;
	}
	for(int i=c2[0]-1;i>=1;i--) f2[i]=c2[0]-i;
	for(int i=c2[c2.size()-1];i<=n;i++) f2[i]=i-c2[c2.size()-1];

	ll ans=0x3f3f3f3f3f3f3f3f;
	// 一条边
	for(auto i:c1)
	{
		int o=f2[i];
		if(1ll*o*o<ans) ans=1ll*o*o;
	}
	// 两条边
	for(int i=1;i<=n;i++)
	{
		if(fa[i]==i&&i!=find(1)&&i!=find(n))
		{
			int mn1=0x3f3f3f3f,mnn=0x3f3f3f3f;
			for(auto j:chunk[i])
			{
				if(f1[j]<mn1) mn1=f1[j];
				if(f2[j]<mnn) mnn=f2[j];
			}
			if(1ll*mn1*mn1+1ll*mnn*mnn<ans) ans=1ll*mn1*mn1+1ll*mnn*mnn;
		}
	}
	printf("%lld\n",ans);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--) once();
}
```

时间复杂度：预处理 $O(n\log n)$，枚举一条边的方案和枚举两条边的方案加起来最多访问 $n-1$ 个点复杂度 $O(n)$，总复杂度 $O(n \log n)$ 而且由于 $\log$ 是从 `sort` 来的所以跑得飞快。

---

## 作者：cyhyyds (赞：1)

## 思路：
可以分三种情况进行讨论：

$1.$ 不连边；

$2.$ 连一条边；

$3.$ 连二条边。

我们可以把第二种和第三种情况放在一起操作。

------------


第一种情况：

当 $1$ 和 $n$ 在同一集合时，花费为 $0$。



------------
第二&三种情况：

写一个求出任意两个集合的最短距离的函数，这样就可以求出第二种情况的代价。

对于第三种情况，我们枚举中转集合，计算最小代价。

如果直接遍历集合中所有元素的话，时间复杂度有点危险。

于是可以使用二分查找，找到与当前点花费最小的点，这样就可以过了。

```
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 7;
const ll inf = 1e18;

int fa[N];

set<int> s[N];

int find (int x) {
	return fa[x] == x ? x : fa[x] = find (fa[x]);
}

inline void unionn (int x, int y) {
	fa[find (x)] = find (y);
}

inline ll pf (ll x) {
	return x * x;
}

inline ll calc (int x, int y) {
	ll res = inf;
	
	for (set<int>::iterator i = s[x].begin (); i != s[x].end (); i ++) {
		set<int>::iterator j = s[y].upper_bound (*i);
		//寻找y集合中第一个最小的大于i的元素。 
		
		if (j != s[y].end ()) {
			res = min (res, pf ((*j) - (*i)));
			//直接计算答案。 
		} 
		
		if (j != s[y].begin ()) {
			res = min (res, pf ((*(-- j)) - *i));
			
			//计算小于i且最大的元素代价。 
		}  
		
		/*只要二分到不是中转集合中最小和最大的点，
     	有两种可能中的一种会使答案最优，可以想想为什么。
		*/ 
	}
	
	return res;
}

signed main () {
	int T;
	
	scanf ("%d", &T);
	
	while (T --) {
		int n, m;
		
		scanf ("%d%d", &n, &m);
		
		for (int i = 1; i <= n; i ++) {
			fa[i] = i;
		}
		
		for (int i = 1; i <= n; i ++) {
			s[i].clear ();
		}
		
		for (int i = 1; i <= m; i ++) {
			int x, y;
			
			scanf ("%d%d", &x, &y);
			
			unionn (x, y);	
		}
		
		for (int i = 1; i <= n; i ++) {
			int fi = find (i);
			
			s[fi].insert (i);
		}
		
		int f1 = find (1), fn = find (n);
		
		if (f1 == fn) {
			printf ("%lld\n", 0);//情况1。	
		}
		
		else {
			ll ans = calc (f1, fn);

			for (int i = 1; i <= n; i ++) {
				if (fa[i] == f1 || fa[i] == fn) {
					continue;
				}
				
				ans = min (ans, calc (i, f1) + calc (i, fn));
				//记录最小代价。 
			}
			
			printf ("%lld\n", ans);	
		}
	}
	
	return 0;
}
```


---

## 作者：taojinchen (赞：0)

# 思路
当我们建边时发现，只要每个联通块的节点不变，都是等价的，我们可以用并查集，后面判两点联通也方便。

在特殊情况下起点和终点一开始就联通，可以特判。然后，我们可以两个联通块中只建一条边或把这一条边拆成两条。还可以和中间的联通块联通，一条和包含起点的联通块相连，另一条和包含终点的联通块相连。

其中只建一条边或把这一条边拆成两条的情况，可以先记录每个与起点联通的点和哪一个与终点联通的点之间建边最优，再依次求出最小值。后面一种情况，可以二分查询离它最近的与起点联通的两个点，以及离它最近的与终点联通的两个点，每一个联通块都要取最小的两边，一条和包含起点的联通块相连，另一条和包含终点的联通块相连。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int kM=1e5+5;
long long i,j,k,mi,t[kM],f[kM],a[kM],b[kM],to[kM][3],e[kM][3],cnt,len,n,m,q,u,v;
long long find(long long x){//并查集
  return x==f[x]?x:f[x]=find(f[x]);
}
long long abc(long long x){//怕abs出问题
  if(x<0)return -x;
  return x;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>q;
  while(q--){
    cin>>n>>m;
    for(i=1;i<=n;i++)f[i]=i;//并查集初始化
    for(i=1;i<=m;i++){
      cin>>u>>v;
      u=find(u),v=find(v);//建边
      if(u!=v)f[u]=f[v];
    }
    if(find(1)==find(n)){//一开始就联通
      cout<<0<<"\n";
      continue;
    }
    t[0]=1e18;
    cnt=len=0;
    for(i=1;i<=n;i++){
      if(find(i)==find(1))a[++cnt]=i;//记录
      if(find(n)==find(i)){
        b[++len]=t[i]=i;
      }
      else t[i]=t[i-1];
    }
    t[n+1]=1e18;
    for(i=n;i;i--){
      if(find(n)==find(i))t[i]=i;
      else if(abc(t[i+1]-i)<abc(i-t[i-1]))t[i]=t[i+1];//更新
    }
    sort(a+1,a+1+cnt);//后面要二分查询
    sort(b+1,b+1+len);
    mi=1e18;
    for(i=1;i<=n;i++){
      if(find(1)!=find(i))continue;
      j=t[i];
      mi=min(mi,(j-i)*(j-i));//两个联通块中只建一条边
      long long mid=(i+j)/2;
      mi=min(mi,(j-mid)*(j-mid)+(i-mid)*(i-mid));//一条边拆成两条
    }
    for(i=1;i<=n;i++){
      e[i][0]=e[i][1]=1e18;//初始化
    }
    for(i=1;i<=n;i++){
      if(find(1)==find(i)||find(n)==find(i))continue;
      u=lower_bound(a+1,a+1+cnt,i)-a;//查询离它最近的两个点
      v=upper_bound(a+1,a+1+cnt,i)-a-1;
      if(u>cnt)u=cnt;//边界
      if(v>cnt)v=cnt;
      if(u==0)u=1;
      if(v==0)v=1;
      to[i][0]=min((a[u]-i)*(a[u]-i),(a[v]-i)*(a[v]-i));//计算
      u=lower_bound(b+1,b+1+len,i)-b;//查询离它最近的两个点
      v=upper_bound(b+1,b+1+len,i)-b-1;
      if(u>len)u=len;//边界
      if(v>len)v=len;
      if(u==0)u=1;
      if(v==0)v=1;
      to[i][1]=min((b[u]-i)*(b[u]-i),(b[v]-i)*(b[v]-i));//最近的
      j=find(i);
      e[j][0]=min(e[j][0],to[i][0]);//在原本的联通块中不用花钱修路
      e[j][1]=min(e[j][1],to[i][1]);
    }
    for(i=1;i<=n;i++){
      j=find(i);
      mi=min(mi,e[j][0]+e[j][1]);//统计答案
    }
    cout<<mi<<"\n";//输出
  }
  return 0;
}
```


---

## 作者：jimmy2021 (赞：0)

## 题意

给定一个 $n$ 个点 $m$ 条边的有向图 $G$，要求再加至多两条边，使得节点 $1$ 和节点 $n$ 在一个连通块内。

## 解法

首先，题目中的“加边”实际上只有三种形式：

- 节点 $1$ 和节点 $n$ 本来就在一个连通块内，不用加边。
- 将节点 $1$ 和节点 $n$ 分别所在的连通块中取两个点连边，共连一条边。
- 将节点 $1$ 和节点 $n$ 分别所在的连通块和第三个连通块相连，共连两条边。

而第二种加边形式启发我们定义 $f_i$ 为节点 $i$ 所在连通块中的一个点向节点 $1$ 连边的最小代价，定义 $g_i$ 为节点 $i$ 所在连通块中的一个点向节点 $n$ 所在连通块连边的最小代价。（实际上代码内只计算了所有作为并查集根节点的 $f$ 和 $g$ 值）

具体来讲，用两个数组 $s_1$ 和 $s_n$ 代表节点 $1$ 和节点 $n$ 所在的连通块中的节点，对于每个 $i \in [1, n]$ ，二分出与 $s_1$ 或 $s_n$ 中差值最小的一个节点，计算代价，更新根节点的 $f$ 或 $g$ 即可。

而如何维护图中的每个连通块呢？我们想到了并查集。

其他详情见（本蒟蒻丑陋的）代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits.h>
#include <cstring>
#include <vector>
//#include <time.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f, INF_BIT = 0x3f;

const int N = 1e5 + 10;

LL t;
LL n, m;
LL u, v;

LL fa[N];
LL find(LL x){
    if(fa[x] == x) return x;
    else return fa[x] = find(fa[x]);
}
void merge(LL x, LL y){
    LL fx = find(x), fy = find(y);
    if(fx != fy){
        fa[fx] = fy;
    }
}

//节点1和节点n对应的树中有那些节点
LL s1[N], sn[N];
LL ind1, indn;

LL f[N], g[N];  //见上（题解描述）

//求在a中选择一个数y，使得(x - y) ^ 2最小，那么(x - y) ^ 2为多少
//其实，(x - y) ^ 2，那么|x - y|也最小
LL getcost(LL x, LL a[], LL n){
    //找到两个在x附近的数
    LL ind1 = lower_bound(a + 1, a + n + 1, x) - a;
    LL ind2 = ind1 - 1;
    LL chsval;
    //比较那个差值最近，得到y（上文注释中的）
    if(ind2 < 1) chsval = a[ind1];
    else if(ind1 > n) chsval = a[ind2];
    else{
        LL dif1 = abs(x - a[ind1]);
        LL dif2 = abs(x - a[ind2]);
        if(dif1 < dif2){
            chsval = a[ind1];
        }else{
            chsval = a[ind2];
        }
    }
    return (x - chsval) * (x - chsval);
}

LL ans;

int main(){
    scanf("%lld", &t);
    while(t--){
        scanf("%lld%lld", &n, &m);
        
        for(LL i = 1;i <= n;i++){
            fa[i] = i;
        }
        
        for(LL i = 1;i <= m;i++){
            scanf("%lld%lld", &u, &v);
            
            merge(u, v);
        }
        
        //int st = clock();
        
        LL f1 = find(1), fn = find(n);
        ind1 = indn = 0;
        for(LL i = 1;i <= n;i++){
            LL fx = find(i);
            if(fx == f1) s1[++ind1] = i;
            if(fx == fn) sn[++indn] = i;
        }
        
        //用每个节点更新它对应树中根节点信息
        memset(f, INF_BIT, sizeof(f));
        memset(g, INF_BIT, sizeof(g));
        for(LL i = 1;i <= n;i++){
            LL fx = find(i);
            if(fx != f1){
                f[fx] = min(f[fx], getcost(i, s1, ind1));
            }else f[fx] = 0;  //特殊情况
            if(fx != fn){
                g[fx] = min(g[fx], getcost(i, sn, indn));
            }else g[fx] = 0;
        }
        
        ans = LLONG_MAX;
        for(LL i = 1;i <= n;i++){
            if(find(i) == i) ans = min(ans, f[i] + g[i]);
        }
        
        //cout << "time:" << clock() - st <<endl;
        
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：BreakPlus (赞：0)

好题一道。

由于只能连接两条边，考虑分以下两种情况。

1. 连接 $1$ 号点所在连通块中的一个点和 $n$ 号点所在连通块中的一个点。看似只用了一条边，不够优秀。如果我们想连接 $x,y$ 两个点（$x<y$），应该拆成 $x\to mid$ 和 $mid \to y$ 两条边，其中 $mid$ 根据小学数学可以得知应该取中间。

2. 连接 $1$ 号点所在连通块中的一个点和一个转折点，再连接转折点和 $n$ 号点所在连通块中的一个点。

额，如果要枚举连接哪俩点肯定是 $O(n^2)$ 不可取的。

考虑我们要在两个连通块中选取两个点连接，肯定要找编号差最小的。这里考虑使用启发式合并的思想。

```cpp
ll merge(ll X, ll Y){
	// 将 vec[X] 和 vec[Y] 这俩集合求出编号差最小
	// 事先 vec[X] 和 vec[Y] 均已排序
	ll ans=1e18;
	if(vec[X].size()>vec[Y].size()){
		ll t=Y; Y=X; X=t;
	}// 交换，保证 vec[X] 更小，这样就从 X 合并到 Y
	for(ll i: vec[X]){
		auto it=lower_bound(vec[Y].begin(),vec[Y].end(),i);
		if(it!=vec[Y].end()){
			if(abs(i-(*it))<ans){
				ans=abs(i-(*it));
			}
		}
		if(it!=vec[Y].begin()){
			it--;
			if(abs(i-(*it))<ans){
				ans=abs(i-(*it));
			}
		} // 只考虑在 vec[Y] 中值和它相邻的
	}
    return ans;
}
```

上面的时间复杂度是 $O(u \log v)$ 的，其中 $u$ 是 ``vec[X]`` 的大小，$v$ 是 ``vec[Y]`` 的大小。

总复杂度的事情呢，待会再说，看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,m,u,v,head[200005],sorted[200005],tot;
struct Edge{
    ll to,nxt;
}edge[200005];
void add(ll u,ll v){
	edge[++tot].to=v;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
vector<ll>vec[200005];
ll merge(ll X, ll Y){
    ll ans=1e18;
    if(vec[X].size()>vec[Y].size()){
    	ll t=Y; Y=X; X=t;
	}
    for(ll i: vec[X]){
        auto it=lower_bound(vec[Y].begin(),vec[Y].end(),i);
        if(it!=vec[Y].end()){
            if(abs(i-(*it))<ans){
                ans=abs(i-(*it));
            }
        }
        if(it!=vec[Y].begin()){
        	it--;
        	if(abs(i-(*it))<ans){
                ans=abs(i-(*it));
            }
		} 
    }
    return ans;
}// 求两个集合元素差最小
ll vis[1000005];
void dfs(ll x){
	for(ll i=head[x];i;i=edge[i].nxt){
		ll tmp=edge[i].to;
		if(!vis[tmp]){
			vis[tmp]=vis[x];
			dfs(tmp);
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		memset(head,0,sizeof head); tot=0;
		for(ll i=1;i<=m;i++){
			cin>>u>>v;
			add(u,v); add(v,u);
		}
		memset(vis,0,sizeof vis);
		for(ll i=1;i<=n;i++)
			if(!vis[i]) vis[i]=i,dfs(i);
		for(ll i=1;i<=n;i++) vec[i].clear();
		for(ll i=1;i<=n;i++) vec[vis[i]].push_back(i); // 以上预处理出连通块存入 vec，复杂度可以不计
		memset(sorted,0,sizeof sorted);
		for(ll i=1;i<=n;i++)
			if(!sorted[vis[i]]) sort(vec[vis[i]].begin(),vec[vis[i]].end()),sorted[vis[i]]=1; // 每个连通块元素排序，复杂度 O(n log n)
		ll temp=merge(vis[1],vis[n]); // 1 和 n 所在连通块找到最小差
		ll answer=(temp/2)*(temp/2)+(temp-temp/2)*(temp-temp/2); // 分开连接，这是一种方法
		memset(sorted,0,sizeof sorted); 
		for(ll i=1;i<=n;i++)
			if(vis[i]!=vis[1] && vis[i]!=vis[n] && !sorted[vis[i]]){ // 枚举转折连通块
				sorted[vis[i]]=1;
				ll temp1=merge(vis[1],vis[i]), temp2=merge(vis[n],vis[i]); // 分别合并
				if(temp1*temp1+temp2*temp2<answer)
					answer=temp1*temp1+temp2*temp2; // 更新答案
			}
		cout<<answer<<endl;
	}
	return 0;
}
```

我们来分析分析复杂度吧。我们首先合并 $1$ 和 $n$ 所在连通块，复杂度 $O(n \log n)$，然后枚举中转连通块，中转连通块大小之和可以看作 $n$，合并两个连通块时复杂度和小的连通块大小有关，总的合并复杂度不会超过 $O(n \log n)$。总的还是 $O(n \log n)$ 的。


~~这个常数巨大，做法很烦的题解终于结束了 /kk~~

---

