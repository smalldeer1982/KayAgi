# Useful Edges

## 题目描述

先有一 $n$ 个顶点的加权无向图，以及 $q$ 个三元组 （$u,v,l$）。其中每个三元组中 $u$ 与 $v$ 是顶点，$l$ 是一个正整数。如果至少有一个具有以下属性的三元组 $u,v,l$ 和一条路径（不一定是最简路径），则边 $e$ 被称为有用的边：

- $u$ 和 $v$ 是此路径的端点；

- $e$ 是这条路径的边之一；

- 此路径上的所有边的权重之和不超过 $l$；

请输出此图中有用边的数量。

## 说明/提示

在第一个样例中，除了权重为 5 的边外，每条边都是有用边。

在第二个样例中，只有 1 和 2 之间的边是有用的，因为它属于路径 1-2 和 $10≤11$。3和4之间的边是没有用的。

在第三个样例中，两条边都是有用的，因为路径 $1-2-3-2$ 的长度正好为 5。 请注意，路径可能会多次通过一个顶点。

翻译者：[XiaoQuQu](https://www.luogu.com.cn/user/427623)

## 样例 #1

### 输入

```
4 6
1 2 1
2 3 1
3 4 1
1 3 3
2 4 3
1 4 5
1
1 4 4```

### 输出

```
5```

## 样例 #2

### 输入

```
4 2
1 2 10
3 4 10
6
1 2 11
1 3 11
1 4 11
2 3 11
2 4 11
3 4 9```

### 输出

```
1```

## 样例 #3

### 输入

```
3 2
1 2 1
2 3 2
1
1 2 5```

### 输出

```
2```

# 题解

## 作者：XiaoQuQu (赞：9)

本题翻译来交题解拉！

首先这个题目要求我们求：有用边的数量。我们根据题意可知，如果一条边 $x,y,c$ 与三元组 $(u,v,l)$ 合法，那么肯定要具备以下的性质：

$$dis_{u,x}+dis_{v,y}+c≤l$$

首先考虑暴力。暴力枚举边+三元组的时间复杂度为 $O(n^4)$ ，显然，就算 `wys` 都救不了这个的复杂度。（迫害

但我们真的有必要枚举四个吗？

于是我们换个思路。枚举对角线上的点。这样可以将枚举拆成两个不相干的部分。

这样，上面的这个不等式可以改为下面这个：$dis[v][y]+c≤l-dis[u][x]$。

想让这个式合法，而两边都不相关，所以可以直接找右边的最大值（枚举 $u$），然后枚举 $y$ 就可以判断这个式是否成立了，时间复杂度 $O(n^3)$

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream> //为了 max 与 min 函数。当然你可以自己写一个。
using namespace std;
#define int long long
const int MAXN = 605;
const int N = MAXN * MAXN;
const int inf = 1e18;
int read()
{
	int x = 0, f = 1; char c;
	while ((c = getchar()) < '0' || c > '9') { if (c == '-') f = -1; }
	while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
int n, m, q, ans, a[N], b[N], c[MAXN][MAXN], d[MAXN][MAXN], l[MAXN][MAXN], ok[MAXN][MAXN];
signed main()
{
	n = read(); m = read();
	memset(d, 0x3f, sizeof d);
	memset(c, 0x3f, sizeof c);
	//这里必须要是 0x3f
	for (int i = 1; i <= n; i++)
		d[i][i] = 0;
	for (int i = 1; i <= m; i++)
	{
		a[i] = read(); b[i] = read();
		c[a[i]][b[i]] = c[b[i]][a[i]] =
			d[a[i]][b[i]] = d[b[i]][a[i]] = read();
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	q = read();
	while (q--)
	{
		int u = read(), v = read(), c = read();
		l[u][v] = l[v][u] = c;
	}
	for (int v = 1; v <= n; v++)
		for (int x = 1; x <= n; x++)
		{
			int mr = 0;
			for (int u = 1; u <= n; u++)
				mr = max(mr, l[u][v] - d[u][x]);
			for (int y = 1; y <= n; y++)
				if (d[v][y] + c[x][y] <= mr)
					ok[x][y] = ok[y][x] = 1;
		}
	for (int i = 1; i <= m; i++)
		if (ok[a[i]][b[i]]) ans++;
	printf("%lld\n", ans);
}
```
码字+翻译不易 求审核通过~

Upd7.18:更新了说明

---

## 作者：Mihari (赞：5)

# 壹、题目描述 &para;

[传送门 to Luogu](https://www.luogu.com.cn/problem/CF1483D).

# 贰、题解 &para;

记 $\text{dis}(a,b)$ 表示图中由 $a$ 到 $b$ 的最短距离。

考虑一对三元组 $\lang u_i,v_i,l_i\rang$，对于一条边 $\lang a,b,w\rang$，如果它是 “有用的”，那么必须满足：
$$
\text{dis}(u_i,a)+w+\text{dis}(b,v_i)\le l_i
$$
显然，我们暴力去匹配一个三元组和一条边，复杂度达到了 $\mathcal O(n^4)$，这是不可接受的。

考虑枚举的重复点，似乎对于每一条边我们都重复访问了许多次，我们能否固定一个三元组的其中一个点，用这个点去匹配边？如果我们将三元组的 $u_i$ 固定，即我们选择枚举 $u$，那么我们的不等式变成了：
$$
\begin{aligned}
&\text{dis}(u,a)+w+\text{dis}(b,v_i)\le l_i \\
\Rightarrow &\text{dis}(u,a)+w\le l_i-\text{dis}(b,v_i)
\end{aligned}
$$
括号左边，就是我们枚举时的固定值，对于右边，我们发现它实际上和独立的 $b$ 有关，我们能否将 $l_i-\text{dis}(b,v_i)$ 预处理出来？

若
$$
\text{cei}(u,b)\overset\Delta=\min\{l-\text{dis}(b,v)\mid \lang u,v,l\rang\in T\}
$$
其中 $T$ 是三元组集合。

那么，我们的不等式就是
$$
\text{dis}(u,a)+w\le \text{cei}(u,b)
$$
考虑 $\text{cei}(u,b)$ 如何快速处理？只需要枚举每一个三元组，再枚举一个点即可。

预处理复杂度 $\mathcal O(n^3)$，跑 $\tt floyd$ 的复杂度是 $\mathcal O(n^3)$，计算答案的复杂度是 $\mathcal O(n^3)$，那么总复杂度就是 $\mathcal O(n^3)$ 了。

# 叁、参考代码 &para;

```cpp
#include<cstdio>
#include<vector>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

#define NDEBUG
#include<cassert>

#define Endl putchar('\n')
#define mp(a, b) make_pair(a, b)
#define rep(i, l, r) for(int i=(l), i##_end_=(r); i<=i##_end_; ++i)
#define fep(i, l, r) for(int i=(l), i##_end_=(r); i>=i##_end_; --i)
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;
template<class T>inline T fab(T x){ return x<0? -x: x; }
template<class T>inline T readin(T x){
	x=0; int f=0; char c;
	while((c=getchar())<'0' || '9'<c) if(c=='-') f=1;
	for(x=(c^48); '0'<=(c=getchar()) && c<='9'; x=(x<<1)+(x<<3)+(c^48));
	return f? -x: x;
}

const int maxn=600;
const int maxm=maxn*maxn;

struct edge{
    int u, v, w;
    edge(){}
    edge(int U, int V, int W): u(U), v(V), w(W){}
}e[maxm+5];

struct trituple{
    int u, v, l;
    trituple(){}
    trituple(int U, int V, int L): u(U), v(V), l(L){}
}tri[maxm+5];

ll f[maxn+5][maxn+5];
int n, m, q;

inline void input(){
    n=readin(1), m=readin(1);
    memset(f, 0x3f, sizeof f);
    int u, v, w;
    rep(i, 1, m){
        u=readin(1), v=readin(1), w=readin(1);
        f[u][v]=f[v][u]=w;
        e[i]=edge(u, v, w);
    }
}

inline void floyd(){
    rep(i, 1, n) f[i][i]=0;
    rep(k, 1, n) rep(i, 1, n) if(i!=k)
        rep(j, 1, n) if(j!=i && j!=k)
            f[i][j]=min(f[i][j], f[i][k]+f[k][j]);
}

inline void gettuple(){
    q=readin(1);
    int u, v, l;
    rep(i, 1, q){
        u=readin(1), v=readin(1), l=readin(1);
        tri[i]=trituple(u, v, l);
    }
}

ll cei[maxn+5][maxn+5];

inline void getminn(){
    memset(cei, -0x3f, sizeof cei);
    int u, v, l;
    rep(i, 1, q){
        u=tri[i].u, v=tri[i].v, l=tri[i].l;
        rep(i, 1, n){
            cei[u][i]=max(l-f[i][v], cei[u][i]);
            cei[v][i]=max(l-f[i][u], cei[v][i]);
        }
    }
}

int vis[maxm+5];
inline void getans(){
    int ans=0, a, b, w;
    rep(u, 1, n){
        rep(i, 1, m) if(!vis[i]){
            a=e[i].u, b=e[i].v, w=e[i].w;
            if(f[u][a]+w<=cei[u][b] || f[u][b]+w<=cei[u][a])
                vis[i]=1, ++ans;
        }
    }
    printf("%d\n", ans);
}

signed main(){
    input();
    floyd();
    gettuple();
    getminn();
    getans();
    return 0;
}
```

# 肆、用到 の Trick

当匹配太乱时，固定一个参数吧，他会让你的枚举变得有序，重复枚举的部分也会变少。

---

## 作者：Fairicle (赞：3)

首先发现暴力是 $O(m)$ 枚举边再枚举 $q$ 中的三元组判断该边可不可行。这样做是 $O(n^4)$ 的，考虑优化。

发现枚举边的过程不好优化，于是考虑优化枚举三元组的过程，将其简化到 $O(n)$。

假设枚举一条边 $(v,u)$，再枚举 $q$ 中一个端点 $i$，若这条边合法，则存在一个 $j$ 使得 $l_{(i,j)}\ge dis(i,v)+dis(v,u)+dis(u,j)$，将固定的值放在右边，有 $l_{(i,j)}-dis(u,j)\ge dis(i,v)+dis(v,u)$。

所以只要能预处理 $\max(l_{(i,j)}-dis(u,j))$ 就能 $O(m)$ 枚举边再 $O(n)$ 枚举一个端点去判断了，记其为  $pre[i][u]$。

这个预处理过程可以通过类似的 $O(q)$ 枚举所有三元组，$O(n)$ 枚举一个点来处理。

复杂度 $O(n^3)$.

code：

```cpp
#define ll long long
#define ri register int
#define pb push_back
#define mp make_pair
#define inf 1000000000000000000
#define N 605
int x,y,z,n,m,ok[N*N],q;
ll dis[N][N],pre[N][N];
vector<pair<int,int> > l[N*N];
inline void floyd(){
    for(ri k=1;k<=n;++k){
        for(ri i=1;i<=n;++i){
            if(i==k) continue;
            for(ri j=1;j<=n;++j){
                if(j==i||j==k) continue;
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
}
struct node{
    int from,to;
    ll val;
}star[(N*N)<<1];
int wl=0;
int main()
{
	n=rd(),m=rd();
	memset(dis,0x3f,sizeof(dis));
	for(ri i=1;i<=n;++i) dis[i][i]=0;
	for(ri i=1;i<=m;++i){
        x=rd(),y=rd(),z=rd();
        dis[x][y]=dis[y][x]=z;
        star[++wl].from=x,star[wl].to=y,star[wl].val=z;
        star[++wl].from=y,star[wl].to=x,star[wl].val=z;
    }
    q=rd();
    for(ri i=1;i<=q;++i){
        x=rd(),y=rd(),z=rd();
        l[x].pb(mp(y,z));
    }
    floyd();
    for(ri u=1;u<=n;++u){
        for(ri i=1;i<=n;++i){
            pre[i][u]=-inf;
            for(ri k=0;k<(int)l[i].size();++k){
                int j=l[i][k].first;
                ll len=l[i][k].second;
                pre[i][u]=max(pre[i][u],len-dis[u][j]);
            }
        }
    }
    for(ri e=1;e<=wl;++e){
        int v=star[e].from,u=star[e].to;
        ll val=star[e].val;
        for(ri i=1;i<=n;++i) if(pre[i][u]>=dis[i][v]+val) ok[(e+1)/2]=1;
    }
    int ans=0;
    for(ri i=1;i<=wl/2;++i) if(ok[i]) ans++;
    cout<<ans;
    return 0;
}

```


---

## 作者：lsj2009 (赞：1)

### Solution

简单题。

考虑 Floyd 计算出节点 $u\to v$ 的最短路径 $dis_{u,v}$。

则一条边 $(u,v)$ 是 Useful 的当且仅当存在一个三元组 $(s,t,l)$ 满足 $dis_{s,u}+w(u,v)+dis_{v,t}\le l$，我们考虑先枚举 $s,v$，发现 $dis_{s,u}+w(u,v)$ 与 $dis_{v,t}$ 的值是独立的。

我们考虑变换一下不等式得到 $dis_{s,u}+w(u,v)\le l-dis_{v,t}$，先枚举一下 $t$ 取 $l-dis_{v,t}$ 的最大值 $res$，然后再去枚举 $u$ 判断一下 $dis_{s,u}+w(u,v)\le res$ 即可。

复杂度 $\Theta(n^3)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=6e2+5,M=1e6+5;
int f[N][N],u[M],v[M],w[N][N],g[N][N];
bool ans[N][N];
signed main() {
    int n,m;
    scanf("%lld%lld",&n,&m);
    cl(f,0x3f); cl(w,0x3f);
    rep(i,1,n)
        f[i][i]=0;
    rep(i,1,m) {
        int val;
        scanf("%lld%lld%lld",&u[i],&v[i],&val);
        f[u[i]][v[i]]=w[u[i]][v[i]]=val;
        f[v[i]][u[i]]=w[v[i]][u[i]]=val;
    }
	rep(k,1,n) {
		rep(i,1,n) {
			rep(j,1,n)
				chkmin(f[i][j],f[i][k]+f[k][j]);
		}
	}	
    int q;
    scanf("%lld",&q);
    while(q--) {
        int u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        g[u][v]=g[v][u]=w;
    }
    rep(s,1,n) {
        rep(v,1,n) {
            int res=-INFLL;
            rep(t,1,n)
                chkmax(res,g[s][t]-f[v][t]);
            rep(u,1,n) {
                if(f[s][u]+w[u][v]<=res)
                    ans[u][v]=ans[v][u]=true;
            }
        }
    }
    int res=0;
    rep(i,1,m)
        res+=ans[u[i]][v[i]];
    printf("%lld\n",res);
    return 0;
}

```

---

## 作者：hyman00 (赞：0)

对于一个限制 $(u,v,l)$，可以枚举走第一条边是 $(u,u',l')$，可以转化为限制 $(u',v,l-l')$，即减去一条边之后的。最后一条边也是类似的，枚举边 $(v',v,l')$，转化为 $(u,v',l-l')$。

对于一条边 $(x,y,l)$，如果它满足条件，即存在路径 $u\to x\to y\to v$，那么一定可以从一个限制开始，删去开头和结尾的若干条边，转化为限制 $(x,y,l')$，只需判断是否有 $l'\ge l$。

相同的限制可以合并，取 max 即可，因此可以用最短路算法做到 $O(n^3\log n)$，cf 可以通过。

另外，可以先用 floyd 算法处理出节点间两两距离，这样对于一个限制，只要更新起点和终点各一次就可以找到答案，即 $(u,v)\to (u',v)\to (u',v')$，去掉一个 log，做到 $O(n^3)$。

---

