# Distance to the Path

## 题目描述

You are given a tree consisting of $ n $ vertices. Initially, each vertex has a value $ 0 $ .

You need to perform $ m $ queries of two types:

1. You are given a vertex index $ v $ . Print the value of the vertex $ v $ .
2. You are given two vertex indices $ u $ and $ v $ and values $ k $ and $ d $ ( $ d \le 20 $ ). You need to add $ k $ to the value of each vertex such that the distance from that vertex to the path from $ u $ to $ v $ is less than or equal to $ d $ .

The distance between two vertices $ x $ and $ y $ is equal to the number of edges on the path from $ x $ to $ y $ . For example, the distance from $ x $ to $ x $ itself is equal to $ 0 $ .

The distance from the vertex $ v $ to some path from $ x $ to $ y $ is equal to the minimum among distances from $ v $ to any vertex on the path from $ x $ to $ y $ .

## 说明/提示

The tree from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1749F/179925eae4a3c002395e013ece768b1e51c00ae1.png) Some query explanations: - " $ 2 $ $ 4 $ $ 5 $ $ 10 $ $ 2 $ ": affected vertices are $ \{4, 2, 5, 1, 3\} $ ;
- " $ 2 $ $ 1 $ $ 1 $ $ 10 $ $ 20 $ " and " $ 2 $ $ 6 $ $ 6 $ $ 10 $ $ 20 $ ": all vertices are affected, since distance to $ 1 $ ( $ 6 $ ) is less that $ 20 $ for any vertex;
- " $ 2 $ $ 3 $ $ 2 $ $ 10 $ $ 0 $ ": affected vertices are $ \{3, 1, 2\} $ ;
- " $ 2 $ $ 5 $ $ 2 $ $ 10 $ $ 1 $ ": affected vertices are $ \{5, 2, 4, 1\} $ .

## 样例 #1

### 输入

```
6
1 2
1 3
4 2
5 2
3 6
14
2 4 5 10 2
1 3
1 6
2 1 1 10 20
2 6 6 10 20
1 3
2 3 2 10 0
2 5 2 10 1
1 1
1 2
1 3
1 4
1 5
1 6```

### 输出

```
10
0
30
50
50
40
40
40
20```

# 题解

## 作者：Alex_Wei (赞：12)

这道题太 OI 啦！

观察发现 $d$ 很小，我们要利用这一点。

以 $1$ 为根，维护 $f_{d, i}$ 表示 $i$ 子树内距离 $i$ 为 $d$ 的所有节点被加上的值，则查询 $v$ 时，对 $v$ 的 $k$ 级祖先 $u$ 求 $\sum f_{k, u}$。

设 $A(u, d)$ 表示 $u$ 子树内距离 $u$ 不大于 $d$ 的点集。

考虑一次修改 $(u, v, k, d)$，设 $x = \operatorname{lca}(u, v)$。则 $A(u, d)$ 会受到贡献，但 $A(fa_u, d)$ 同样会受到贡献，这样 $A(u, d - 1)$ 就会受到重复贡献。因此，对于 $u$，我们让 $A(u, d) \backslash A(u, d - 1)$ 受到贡献，相当于令 $f_{d, u}$ 加上 $k$。

我们对 $u, v$ 路径上所有节点都执行这样的操作后，发现还有 $A(x, d - 1)$ 和 $x$ 子树外距离 $x$ 不大于 $d$ 的节点没有受到贡献。这部分是平凡的，容易转化为 $\mathcal{O}(d)$ 次对 $f$ 的单点加。

接下来考虑实现。查询为 $\mathcal{O}(d)$ 次 $f$ 的单点查，修改为 $\mathcal{O}(1)$ 次 $f_d$ 的链加和 $\mathcal{O}(d)$ 次 $f$ 的单点加。链加单点查拆成两条竖直链，每条直链再差分变成两条到根的链，据此转化为子树加单点求和，用树状数组维护。单点加对单点查的贡献容易统计。

综上，时间复杂度 $\mathcal{O}((n + qd)\log n)$。[代码](https://codeforces.com/contest/1749/submission/183672400)。

---

## 作者：Spouter_27 (赞：7)

### 写在前面

前几天打了 CFeduR137，用一些奇怪的方法做出来了 F，幸运地上了紫。由于知道自己实力不太匹配，害怕掉分，所以 R138 就没有打。当天晚上朋友问我比赛打吗，我拒绝了，没有报名。后来想着帮朋友看一看 D 题，发现十分可做，于是感到有点后悔。不过过了 4 题在 div2 的排名是 200 多，不是特别靠前，所以没当回事。等到离比赛结束还有 10 分钟的时候我打开了 F ，也就是这题。然后我惊讶地发现，这题的套路不是跟 tyy 前几天刚讲过的题差不多吗？怎么全场就只有 26 个人过了？？于是我赛后用了 25min 写了一发，然后就过了。      
当晚直接就陷入了无尽的后悔。本来可以直接上橙的！不知道下一次这样的机会是在什么时候了。所以说不要害怕下分，勇敢打比赛吧！

不扯了，说回正题。

### 前置芝士：

- 线段树或树状数组。
- 树链剖分。

没错，就这些。虽然赛时过的人很少，但是这题做法很简单且很巧妙。保证你看完题解后会理解。

### 题意：

给你一棵树，点有点权，两种操作：    
- 询问点权。
- 将树上所有到从 $u$ 到 $v$ 的路径的距离不超过 $d$ 的点的点权增加 $k$。  
- 数据范围：$n,q\le 2\times 10^5,d\le 20.$

### 分析：

直接做貌似不太可做，我们先来看简化版的题目。   
[~~【魔怔题面】~~](https://www.luogu.com.cn/problem/U251477)

简要题意：

一棵树，初始所有点权为 $1$，两种操作：
- 询问点权。
- 将树上所有与 $u$ 距离不超过 $d$ 的点的点权乘 $k$，并对一个固定常数 $L$ 取模。
- 数据范围：$n,q\le 10^6,d\le 40$。

这个修改操作有点魔怔，不好直接拿数据结构维护。可能有什么淀粉质（点分治）的做法，但是那样代码又长又难写又难调~~还不一定对~~，这里介绍一种更为简单的做法。

对于每个节点 $i$，记 $f_{i,j}$ 表示以 $i$ 为根的子树的第 $j$ 代儿子要乘多少。初始值全为 $1$.   

这样询问操作就很好做了，由于 $d\le 40$，暴力向上跳即可。考虑怎么修改。

我们给定这样一棵树，现在假设我们要对所有距编号为 $4$ 的节点距离不超过 $2$ 的值乘 $k$：

![初始形态](https://cdn.luogu.com.cn/upload/image_hosting/tmuj4d6y.png)

从 $4$ 号点开始，按照下方图示的方法处理（红框内就是每次被处理的节点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/2zhvz2q2.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/nuzl7dxm.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/v3hvf7r5.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/mm75nznt.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/uwffk9ap.png)

不难发现通过遵循这样“算两步，跳一步”的方法，经过若干次（不超过 $(2d+1)$ 次）处理，所有与 $4$ 号节点距离不超过 $2$ 的点都被处理到了。   
这种方法可以扩展到距离为 $d$。需要特殊处理当前已经跳到根节点的情况，即不再往上跳，直接更新完所有的节点（这里不好描述，建议读者自己画图理解）。

复杂度为 $O(qd)$,可以通过该题。

### 解析：

回到本题，题目由单点修改变成了区间修改，暴力重复上面的过程复杂度为  $O(qnd)$，显然不能通过，怎么办呢？

！我会树链剖分！

正解就是造 $21$ 棵线段树，第 $i$ 棵线段树维护 $f_{x,i}$ 的值。先树剖，每次修改的时候，先修改链上所有的点 $i$ 的 $f_{i,d}$ 的值，然后从 $lca$ 处开始，重复上面的“算两步，跳一步”的做法，就可以了。   
我们发现需要维护的是一个支持区间修改，单点查询的数据结构，可以改用差分树状数组。这样时间常数较线段树更小，而空间占用也少了 $3/4$，显然是更优的。（虽然直接写支持区间修改区间查询的线段树也能过，但是你会像我一样喜提 $3744ms$ 最劣解）

复杂度为 $O(q\log^2n+dq\log n)$。由于 $d$ 与 $\log n$ 同阶，$q$ 与 $n$ 同阶，所以复杂度为 $O(n\log^2 n)$。

### 代码：

[不建议点进去的代码链接](https://codeforc.es/contest/1749/submission/177217388)

代码很丑，因为是直接贺的树剖板子，不具有什么参考价值。而且如果你能理解上面的解析，那代码也没有什么必要了。实在需要的话，你可以去看看其他大佬的代码，都是比我强的。

### 写在最后：

CSP-S2022 rp++。   
要积极参加比赛。

---

## 作者：SUNCHAOYI (赞：3)

部分参考了 [这篇](https://www.luogu.com.cn/blog/xianggl-ak-ioi/cf1749f-ti-xie) [xianggl](https://www.luogu.com.cn/user/201278)巨佬的博客。

由于 $d \le 20$，考虑将不等关系的信息存放在数组中，转换为最大距离 $d$ 时的信息。考虑单独处理每一个点时，直接暴力修改与某一点 $x$ 距离为 $[0,d]$ 的点，此时不难分析出时间复杂度为 $O(qnd)$。

由于是区间更新，需要同时更新 $x \to y$ 这条链上的点，也就是提示要用数据结构去维护。将单点数据的处理分为子树内与子树外两种情况进行分类讨论。

对于在子树内的点，倘若是一段连续的区间，则可以利用数据结构一次更新完毕。不难想到利用树链剖分维护 $\texttt{dfs}$ 序，这样子树内的 $\texttt{dfs}$ 序便是连续的。利用常数较小的树状数组，设 $c_{i,j}$ 存的是最大距离为 $i$ 时每一个点产生的贡献。则在一次处理时直接更新 $x,y,\rm{LCA(x,y)}$ 三点即可，也就是 `modify (c[d],x,k);modify (c[d],y,k);modify (c[d],LCA(x,y),-2 * k)`，其中 `modify` 函数即为树状数组的操作。用 `in[x]` 和 `out[x]` 分别表示第一次和最后一次经过 $x$ 点时的 $\texttt{dfs}$ 序，因此在查询答案时子树内的贡献即用差分的思想进行树状数组维护操作。

对于在子树外的点，显然都可以归结到 $z = \rm LCA(x,y)$ 这一点产生的贡献。由于是单点，直接进行暴力修改。设 $dp_{i,j}$ 表示以 $i$ 为根距离为 $j$ 时的贡献的权值。从 $z$ 开始向上走，$z$ 对上面距离不超过 $j$ 的节点产生影响，然后发现，$z$ 的父亲会对距离不超过 $j - 2$ 的节点产生的影响被重复计算，直接进行容斥即可（需要减去的条件是距离超过 $j - 2$ 且 $z$ 上方还存在节点）。

综上分析，子树内修改为 $O(q\log n)$，查询为 $O(qd \log n)$；子树外修改为 $O(qd)$，查询为 $(qd)$，由于 $n,q$ 同阶，$d,\log n$ 大小相近，所以最后的时间复杂度为 $O(n \log^2 n)$。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define lowbit(x) x & (-x)
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,m,cnt,in[MAX],out[MAX],top[MAX],sz[MAX],hson[MAX],f[MAX],dep[MAX],dp[MAX][25],c[25][MAX]; 
vector <int> ve[MAX];
void dfs1 (int u,int fa);
void dfs2 (int u,int fa);
int lca (int u,int v);
void modify (int tr[],int x,int v);
int query (int tr[],int x);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();
	for (int i = 1;i < n;++i)
	{
		int x = read (),y = read ();
		ve[x].push_back (y);ve[y].push_back (x);
	}
	dfs1 (1,0);
	in[1] = ++cnt,top[1] = 1;
	dfs2 (1,0);
	//for (int i = 1;i <= n;++i) cout<<in[i]<<" "<<out[i]<<endl;
	m = read ();
	for (int i = 1;i <= m;++i)
	{
		int ty = read ();
		if (ty == 1)
		{
			int x = read (),ans = 0,p = 0;
			for (int i = 0;i <= 20;++i)
			{
				ans += query (c[i],out[x]) - query (c[i],in[x] - 1);//差分思想
				for (int j = p;j <= 20;++j) ans += dp[x][j];//每向上走一次，距离至少为 p
				++p;x = f[x];
				if (!x) break;//向上面已经没有节点就停止
			}
			printf ("%d\n",ans);
		}
		else
		{
			int u = read (),v = read (),k = read (),d = read ();
			int z = lca (u,v);
			modify (c[d],in[u],k);modify (c[d],in[v],k);modify (c[d],in[z],-2 * k);//重复部分的去除
			for (int i = d;~i;--i)
			{	
				dp[z][i] += k;
				if (i - 2 >= 0 && f[z]) dp[z][i - 2] -= k;//容斥 距离 >= i - 2 且 z 上还有节点 
				z = f[z];
				if (!z) break;
			}
		}
	} 
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
void dfs1 (int u,int fa)//树链剖分
{
	dep[u] = dep[fa] + 1;
	f[u] = fa;sz[u] = 1;
	for (auto v : ve[u])
	{
		if (v == fa) continue;
		dfs1 (v,u);
		sz[u] += sz[v];
		if (sz[v] > sz[hson[u]]) hson[u] = v;
	}
}
void dfs2 (int u,int fa)
{
	if (hson[u])
	{
		in[hson[u]] = ++cnt;//dfs 序
		top[hson[u]] = top[u];
		dfs2 (hson[u],u);
	}
	for (auto v : ve[u])
	{
		if (top[v]) continue;
		in[v] = ++cnt;
		top[v] = v;
		dfs2 (v,v);
	}
	out[u] = cnt;//dfs 序
}
int lca (int u,int v)//树链剖分求 LCA
{
	int fx = top[u],fy = top[v];
	while (fx != fy)
	{
		if (dep[fx] < dep[fy]) swap (fx,fy),swap (u,v);
		u = f[fx],fx = top[u]; 
	}
	if (dep[u] > dep[v]) swap (u,v);
	return u;
}
void modify (int tr[],int x,int v) {for (int i = x;i <= n;i += lowbit (i)) tr[i] += v;}
int query (int tr[],int x) {int sum = 0;for (int i = x;i;i -= lowbit (i)) sum += tr[i];return sum;}//树状数组基本操作
```


---

## 作者：stntn (赞：2)

## 简要题意

给你一棵树，初始点权为 $0$，两种操作：

1. 查询一个点的点权。
2. 将一条链及到该链距离 $\le d$ 的所有点点权加 $k$。

## 树剖

令 $d_0=\max \left \{ d_i \right \}$，该题解复杂度 $O(d_0(n\log n + q \log ^2 n))$，**略微**卡常。

首先我们树剖，建线段树维护每个点的 $d_0$ 个属性，分别为该点对**其本身及其下方**到该点距离 $\le i$ 的所有节点权值的贡献，令 $(d,k)$ 表示第 $d$ 个属性大小为 $k$ 的值。.

如果我们能很好地维护这棵线段树，查询的时候只需要暴力向上跳 $d_0$ 个节点， 依次加贡献可，单次查询复杂度 $O(d \log^2 n)$。

现在我们来看怎么维护。

如果最简单粗暴地修改，对所有链上的点加上一个 $(d,k)$，然后对链中深度最低的点（即 lca）暴力向上跳祖先修改，其深度差为 $i$ 的祖先加上一个 $(d-i,k)$。

可以发现这样是错误的，因为链上的节点如果它的某个儿子也在链上（暴力跳祖先的过程同理）那么贡献就会算重（画图理解）。

解决办法也很简单，对于一个在链上的节点，其父亲也在链上且贡献增量为 $(d,k)$，该节点就算重了 $(d-1,k)$，减去即可，单次修改复杂度 $O(d\log^2n)$。

具体细节看代码。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 300010
#define LL long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define tep(u) for(auto v:e[u])
#define INF 0x3f3f3f3f
const int End=1e6; char buf[End],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,End,stdin),p1==p2)?EOF:*p1++)
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int n,m,dep[N],fa[N][21],siz[N],son[N],top[N],newid[N],idcc;
vector<int> e[N];
inline void dfs1(int u)//树剖 
{
	siz[u]=1;
	tep(u) if(v^fa[u][0])
	{
		dep[v]=dep[u]+1;fa[v][0]=u;
		rep(j,1,20) fa[v][j]=fa[fa[v][j-1]][j-1];
		dfs1(v);siz[u]+=siz[v];
		if(!son[u]||siz[son[u]]<siz[v]) son[u]=v;
	}
}
inline void dfs2(int u,int topf)
{
	newid[u]=++idcc;top[u]=topf;
	if(son[u]) dfs2(son[u],topf);
	tep(u) if(v^fa[u][0]&&v^son[u]) dfs2(v,v);
}
inline int get_lca(int u,int v)
{
	while(top[u]^top[v]) dep[top[u]]<dep[top[v]] ? v=fa[top[v]][0] : u=fa[top[u]][0];
	return dep[u]<dep[v] ? u:v;
}
struct SGT
{
	#define mid ((l+r)>>1)
	#define lc rt<<1
	#define rc rt<<1|1
	int sum[N<<2][21],add[N<<2][21],len[N<<2];//20个属性 
	inline void pushdown(int rt,int k)//只pushdown当前需要的属性，卡常 
	{
		add[lc][k]+=add[rt][k];
		add[rc][k]+=add[rt][k];
		sum[lc][k]+=add[rt][k]*len[lc];
		sum[rc][k]+=add[rt][k]*len[rc];
		add[rt][k]=0;
	}
	inline void build(int rt,int l,int r)
	{
		rep(i,0,20) sum[rt][i]=add[rt][i]=0;
		if(l==r){len[rt]=1;return;}
		build(lc,l,mid);build(rc,mid+1,r);
		len[rt]=len[lc]+len[rc];
	}
	inline void update(int rt,int l,int r,int L,int R,int val,int k)//区间修改和单点修改分开写 
	{
		if(L<=l&&r<=R){add[rt][k]+=val;sum[rt][k]+=val;return;}
		pushdown(rt,k);
		if(L<=mid) update(lc,l,mid,L,R,val,k);
		if(mid<R) update(rc,mid+1,r,L,R,val,k);
	}
	inline void update_pos(int rt,int l,int r,int p,int val,int k)
	{
		if(l==r){sum[rt][k]+=val;return;}
		pushdown(rt,k);
		if(p<=mid) update_pos(lc,l,mid,p,val,k);
		else update_pos(rc,mid+1,r,p,val,k);
	}
	inline int query(int rt,int l,int r,int p,int d)//节点p深度差d
	{
		if(l==r)
		{
			int res=0;
			rep(i,d,20) res+=sum[rt][i];//>=d均做贡献 
			return res;
		}
		rep(i,d,20) pushdown(rt,i);
		if(p<=mid) return query(lc,l,mid,p,d);
		else return query(rc,mid+1,r,p,d);
	}
	#undef mid
	#undef lc
	#undef rc
}t;
inline void updrange(int u,int v,int val,int k)
{
	while(top[u]^top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		t.update(1,1,n,newid[top[u]],newid[u],val,k);u=fa[top[u]][0];
	}
	if(dep[u]>dep[v]) swap(u,v);
	t.update(1,1,n,newid[u],newid[v],val,k);
}
inline int qrange(int u,int d){return t.query(1,1,n,newid[u],d);}
signed main()
{
	read(n);
	rep(i,2,n)
	{
		int u,v;read(u,v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1);dfs2(1,1);
	t.build(1,1,n);
	read(m);
	while(m--)
	{
		int opt,u,v,k,d;
		read(opt);
		if(opt==1)
		{
			read(u);int res=0;
			for(int now=u;now&&dep[u]-dep[now]<=20;now=fa[now][0]) res+=qrange(now,dep[u]-dep[now]);//暴力向上跳 
			printf("%d\n",res);
		}
		else
		{
			read(u,v,k,d);int lca=get_lca(u,v);
			if(!k) continue;
			if(u==v)//特判u=v 
			{
				t.update_pos(1,1,n,newid[u],k,d);
				for(int now=fa[u][0],lst=u;now&&dep[u]-dep[now]<=d;lst=now,now=fa[now][0])
				{
					t.update_pos(1,1,n,newid[now],k,d-(dep[u]-dep[now]));
					if(d-(dep[lca]-dep[now])) t.update_pos(1,1,n,newid[lst],-k,d-(dep[u]-dep[now])-1);
				}
			}
			else if(lca==u||lca==v)//两种链分讨一下，分别为lca是否是端点 
			{
				if(v==lca) swap(u,v);
				int pson=v;
				per(i,20,0) if(dep[fa[pson][i]]>dep[u]) pson=fa[pson][i];
				updrange(u,v,k,d);
				if(d) updrange(pson,v,-k,d-1);//去重 
				for(int now=fa[u][0],lst=u;now&&dep[u]-dep[now]<=d;lst=now,now=fa[now][0])//暴力修改 
				{
					t.update_pos(1,1,n,newid[now],k,d-(dep[u]-dep[now]));
					if(d-(dep[lca]-dep[now])) t.update_pos(1,1,n,newid[lst],-k,d-(dep[u]-dep[now])-1);//去重 
				}
			}
			else//以下同理 
			{
				int lson=u,rson=v;
				per(i,20,0)
				{
					if(dep[fa[lson][i]]>dep[lca]) lson=fa[lson][i];
					if(dep[fa[rson][i]]>dep[lca]) rson=fa[rson][i];
				}
				updrange(u,v,k,d);
				if(d)
				{
					updrange(u,lson,-k,d-1);
					updrange(v,rson,-k,d-1);
				}
				for(int now=fa[lca][0],lst=lca;now&&dep[lca]-dep[now]<=d;lst=now,now=fa[now][0])
				{
					t.update_pos(1,1,n,newid[now],k,d-(dep[lca]-dep[now]));
					if(d-(dep[lca]-dep[now])) t.update_pos(1,1,n,newid[lst],-k,d-(dep[lca]-dep[now])-1);
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：xianggl (赞：1)

题意：

给定义一棵 $n$ 个点的树，有两种操作。

1、查询 $x$ 的权值。

2、给距离 $(x, y)$ 这条链距离不超过 $d$ 的点权加 $k$。

题解：

考虑一个点距离不超过 $d$。

那么它必然是子树内不超过 $d$ 的，再加上子树外不超过 $d$ 的。

注意到，若 $x$ 不是链的 lca， 那么 $fa[x]$ 必然也可以覆盖 $x$ 子树外的部分。

所以说对于链上所有点 $x$，我们先只考虑其子树内距离为 $d$ 的覆盖，可以用树状数组 + dfs 序完成。

那么再考虑从 lca 往上 $d$ 步的这条链，相当于开始考虑 lca 其子树外的覆盖。

用 $f[x][i]$ 表示 $x$ 对子树内距离为 $i$ 加的值，注意到，$x$ 覆盖了距离不超过 $d$ 的部分，那么 $fa[x]$ 会将距离 $x$ 为 $d - 2$ 的部分多覆盖一次。

所以说容斥一下就好了。

时间复杂度 $O(n \times (\log_2 n \times d + d \times d))$。

代码：

```
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
const int Maxn=2e5;
vector<int>adj[Maxn+5];
int f[Maxn+5][21];
int son[Maxn+5],size[Maxn+5],father[Maxn+5],top[Maxn+5],in[Maxn+5],out[Maxn+5],dep[Maxn+5],timer;
int n,m;
struct Fenwick {
	int c[Maxn+5];
	inline int lowbit(int x) {return x&(-x);}
	inline void add(int x,int d) {
		for(;x<=n;x+=lowbit(x))c[x]+=d;
	}
	inline int query(int x) {
		int res=0;
		for(;x>=1;x-=lowbit(x))res+=c[x];
		return res;
	}
	inline int rangequery(int l,int r) {
		return query(r)-query(l-1);
	}
}fen[21];
void dfs1(int u,int fa) {
	size[u]=1,father[u]=fa,dep[u]=dep[fa]+1;	
	int mx=0;
	for(ri v:adj[u]) 
		if(v!=fa) {
			dfs1(v,u);
			if(size[v]>mx)son[u]=v,mx=size[v];
			size[u]+=size[v];
		}
}
void dfs2(int u,int fa,int now) {
	top[u]=now,in[u]=++timer;
	if(son[u])dfs2(son[u],u,now);
	for(ri v:adj[u])
		if(v!=son[u]&&v!=fa)dfs2(v,u,v);
	out[u]=timer;
}
inline int lca(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=father[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
inline void modify(int x,int y,int k,int d) {
	int z=lca(x,y);
	fen[k].add(in[x],d);
	fen[k].add(in[y],d);
	fen[k].add(in[z],-2*d);
	for(ri i=0;i<=k&&z;i++) {
		f[z][k-i]+=d;
		if(k-i-2>=0&&z!=1)f[z][k-i-2]-=d;
		z=father[z];
	}
}
inline int query(int x) {
	int res=0,dis=0;
	for(ri i=0;i<=20&&x;i++) {
		res+=fen[i].rangequery(in[x],out[x]);
		for(ri j=dis;j<=20;j++)res+=f[x][j];
		++dis,x=father[x];
	}
	return res;
}
int main() {
	scanf("%d",&n);
	for(ri i=1;i<n;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs1(1,0),dfs2(1,0,1);
	scanf("%d",&m);
	while(m--) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int x;
			scanf("%d",&x);
			printf("%d\n",query(x));
		}
		else {
			int x,y,k,d;
			scanf("%d%d%d%d",&x,&y,&d,&k);
			modify(x,y,k,d);
		}
	}
	return 0;
}
```


---

## 作者：MiniLong (赞：0)

考虑到 $d$ 很小，不妨将所有更改挂到对应节点上，然后枚举查询节点的不高于 $d$ 级祖先。

更改时，先考虑 $\operatorname{lca}(u,v)$ 子树内的贡献。可以开 $20$ 棵线段树维护每个距离的标记。对于链 $(u,v)$，可以在这条路径上每个点在 $[1,d]$ 这些线段树上加上 $k$，但是这样会算重，具体地，对于一个点 $x$，若它还有儿子 $y$ 被更改，那么 $y$ 子树中距离 $y$ 不超过 $d-1$ 的点会被多加 $k$。所以对于链 $(u,v)$ 上除了 $\operatorname{lca}(u,v)$ 的点之外所有点都在 $[1,d-1]$ 这些线段树上减 $k$。查询的时候枚举 $u$ 的 $20$ 个祖先然后单点查询。这样复杂度是 $\Theta(nd\log^2 n+nd\log n)$，不平衡。注意到只是单点查，那么树上差分一下变成子树查询即可，复杂度 $\Theta(nd \log n)$。然后是 $\operatorname{lca}(u,v)$ 子树以外的贡献，那么考虑直接枚举 $\operatorname{lca}(u,v)$ 的不超过 $d$ 级祖先，在每个这样的点 $x$ 开 $20$ 个标记，表示 $x$ 子树到 $x$ 距离等于 $i$ 的标记。类似地，每次把 $tag_{x,0}$ 到 $tag_{x,d-dis(u,\operatorname{lca}(u,v))}$ 加上 $k$，设 $x$ 在 $\operatorname{lca}(u,v)$ 方向儿子为 $y$，把 $tag_{y,0}$ 到 $tag_{y,d-dis(u,\operatorname{lca}(u,v))}$ 全部减去 $k$ 即可。复杂度 $\Theta(nd^2)$（当然可以做到 $\Theta(nd\log d)$）。

查询直接枚举 $u$ 的 $20$ 个祖先，然后子树求和就行，再加上标记，复杂度 $\Theta(n(d\log n+d))$。

所以总复杂度为 $\Theta(nd(\log n + d))$。

---

