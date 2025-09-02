# [JRKSJ R3] a question

## 题目背景

这是一个问题。

## 题目描述

现在有一棵 $n$ 个结点的树 $\text{T}$，边带权，结点的编号为 $[1,n]$ 的排列。

设 $\text{G}$ 为 $\text{T}$ 的补图。对于 $\text{G}$ 上的每一条边 $(x,y)$，该边的权值为 $\text{T}$ 上 $x\rightarrow y$ 的路径上的边权和。

设 $dis(x,y)$ 为 $\text{G}$ 上 $x,y$ 两点之间的最短路径的长度。若 $x,y$ 两点不连通，则令 $dis(x,y)=0$。

求 $\displaystyle\sum_{i=1}^{n-1} \sum_{j=i+1}^n dis(i,j)$。

## 说明/提示

$\text{T}$ 的补图 $\text{G}$ 的定义为：对于边 $(x,y)(1\le x,y\le n,x\ne y)$，若 $\text{T}$ 中不存在该边 ，则 $\text{G}$ 中存在该边；若 $\text{T}$ 中存在该边 ，则 $\text{G}$ 中不存在该边。$\text{G}$ 为无向图。

### 样例解释
对于样例 $2$，图 $\text{G}$ 如图所示：

![3](https://cdn.luogu.com.cn/upload/image_hosting/wjblfgx5.png?x-oss-process=image)

我们有：
| $dis(i,j)$ | $j=1$ | $j=2$ | $j=3$ | $j=4$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $i=1$ |  | $20$ | $8$ | $12$ |
| $i=2$ |  |  | $28$ | $8$ |
| $i=3$ |  |  |  | $20$ |

所以答案为 $96$。
### 数据规模

| $\text{Subtask}$ | $n\le$ | 特殊性质 | 分值 | 子任务依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $10^3$ | 无 | $10$ | 无 |
| $2$ | $10^4$ | 无 | $20$ | $1$ |
| $3$ | $2\times 10^6$ | 树为菊花 | $20$ | 无 |
| $4$ | $2\times 10^6$ | 树为链 | $20$ | 无 |
| $5$ | $2\times 10^6$ | 无 | $30$ | $1,2,3,4$ |

对于 $100\%$ 的数据，$2\le n \le 2\times 10^6$，$1\le x,y\le n$，$0\le v\le 10^9$。

**本题输入文件较大，请使用恰当的读入方式。**

## 样例 #1

### 输入

```
3
1 2 2
2 3 3```

### 输出

```
5```

## 样例 #2

### 输入

```
4
1 2 4
2 3 4
3 4 4```

### 输出

```
96```

# 题解

## 作者：cyffff (赞：3)

[$\text{Link}$](https://www.luogu.com.cn/problem/P7980)
### $\text{Subtask 1}$
$n\le 10^3$。

考虑直接建图再跑 $\text{Floyd}$，注意是答案需要取模，而不是取模后的最短路。时间复杂度 $O(n^3)$。
### $\text{Subtask 2}$
$n\le 10^4$。

考虑若 $\text T$ 中 $u,v$ 两点不相连，则 $\text G$ 中 $u,v$ 直接有边，距离可以 $\text {RMQ}-\text{LCA}$ $O(1)$ 求出。否则直接分类讨论，这个可以看后面的做法。这里可以直接搜两层，时间复杂度 $O(n^2)$。
### $\text{Subtask 3}$
$n\le 2\times 10^6$，树为菊花图。

根节点显然没有贡献，直接忽略。考虑两点 $u,v,(u,v\ne1)$，它们肯定相邻，距离为 $w_{1,u}+w_{1,v}$，考虑每条边会被计算几次，所以答案为 $\displaystyle(n-2)\sum w$，时间复杂度 $O(n)$。
### $\text{Subtask 4}$
$n\le 2\times 10^6$，树为链。

问题即为树上每次转移只得走 $\ge2$ 格，求路径最小和，考虑分类算贡献：

1. $(u,v)\notin E$，设 $dep_u>dep_v$，则此部分贡献为 $\displaystyle\sum w\times siz_u\times(n-siz_u)$
2. $(u,v)\in E$

![1](https://cdn.luogu.com.cn/upload/image_hosting/1p7kl7np.png?x-oss-process=image/resize,m_lfit,h_170,w_225)![2](https://cdn.luogu.com.cn/upload/image_hosting/ehvult75.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

考虑长这样，分类讨论：
- 向上走 $2$ 格再向下走 $3$ 格或者反过来，如图 $1$。
- 向下走 $2$ 格再向上走 $3$ 格再往下走 $2$ 格，如图 $2$。注意需要存向下走两格的最小值和次小值，方便算贡献。

取 $\min$ 即可，答案为两种贡献和再减掉多余的 $\displaystyle \sum w$ 的贡献，时间复杂度 $O(n)$。
### $\text{Subtask 5}$
$n\le 2\times 10^6$。

上一个 $\text{Subtask}$ 中第二种情况由于每个点至多两个儿子只需维护向下 $2$ 格的 $\min$ 和 $\text{secmin}$ 就能计算，但是最小 $2$ 个值可能都是第一步走 $u$，所以需要维护**以 $v$ 向下走两格，且第一格不是 $u$ 的最小权值**，这点可以给 $v$ 的儿子编号，算出**以 $v$ 向下走两格，且第一格是 $u$ 的最小权值**，维护前后缀 $\min$，就能计算了，时间复杂度 $O(n)$。

这题思路简单，但实现细节繁多，并且有些卡常。

给一下我的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=2e6+10,mod=1e9+7;
int n,cnt,head[N];
int son[N];
struct Edge{
	int to,nxt,w;
}a[N<<1],stc[N];
inline void add(int u,int v,int w){
	cnt++;
	a[cnt].to=v;
	a[cnt].nxt=head[u];
	a[cnt].w=w;
	head[u]=cnt;
	son[u]++;
}
int siz[N],dep[N],fa[N];
ll up[N],dw2[N],dw1[N],dw1s[N],dwp[N],go2[N],mdep[N];
inline void dfs1(int x,int f,int gf){
	siz[x]=1,dep[x]=dep[f]+1,mdep[x]=dep[x],fa[x]=f;
	dw1[x]=dw1s[x]=dw2[x]=go2[x]=2e16;
	dw2[gf]=min(dw2[gf],up[x]+up[f]);
	if(dw1[f]>up[x]){
		dw1s[f]=dw1[f];
		dwp[f]=x;
		dw1[f]=up[x];
	}else if(dw1s[f]>up[x]){
		dw1s[f]=up[x];
	}
	for(int i=head[x];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==f) continue;
		up[t]=a[i].w;
		dfs1(t,x,f);
		mdep[x]=max(mdep[x],mdep[t]);
		siz[x]+=siz[t];
	}
}
ll *dw2h[N],tmp[N],pre[N],suf[N],pool[N<<2],*now=pool;
inline void dfs2(int x,int f){
	int sz=son[x],cnt=0;
	dw2h[x]=now,now+=sz+1;
	pre[0]=2e16,suf[sz+1]=2e16;
	for(int i=head[x];i;i=a[i].nxt)
		stc[cnt++]=a[i];
	reverse(stc,stc+cnt);
	for(int i=0;i<cnt;i++)
		if(stc[i].to!=f)
			tmp[i+1]=stc[i].w+dw1[stc[i].to];
		else
			tmp[i+1]=2e16;
	for(int i=1;i<=sz;i++)
		pre[i]=min(pre[i-1],tmp[i]);
	for(int i=sz;i>=1;i--)
		suf[i]=min(suf[i+1],tmp[i]);
	for(int i=1;i<=sz;i++)
		dw2h[x][i]=min(pre[i-1],suf[i+1]);
	for(int i=head[x];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==f) continue;
		dfs2(t,x);
	}
	go2[x]=min(up[x]+up[f],dwp[f]==x?up[x]+dw1s[f]:up[x]+dw1[f]);
}
struct Tmp{
	int u,v,w,idu,idv;
}e[N];
ll ans1,ans2;
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
		e[i]={u,v,w,son[v],son[u]};
	}
	up[1]=up[0]=2e16;
	dfs1(1,0,0);
	dfs2(1,0);
	for(int i=1;i<n;i++){
		int u=e[i].u,v=e[i].v,w=e[i].w,iu=e[i].idu,iv=e[i].idv;
		if(dep[u]<dep[v]) swap(u,v),swap(iu,iv);
		ans1=(ans1+1ll*w*siz[u]%mod*(n-siz[u]))%mod;
		ll tmp=2e16;
		if(mdep[u]-dep[u]>=2)
			tmp=min(tmp,dw2[u]);
		tmp=min(tmp,go2[u]+dw1[u]);
		tmp=min(tmp,go2[v]);
		tmp=min(tmp,dw2h[v][iu]);
		if(tmp<2e16)
			ans2=(ans2+2*tmp)%mod;
		else
			ans1=(ans1+mod-w)%mod;
	}
	write((ans1+ans2)%mod);
	flush();
}
```
再见 qwq~

---

## 作者：Jsxts_ (赞：3)

分类讨论。

设当前要计算的两个点为 $i$ 和 $j$，并且默认的边都是树上的边。

1.当 $i$ 和 $j$ 没有直接父子关系：

此时显然 $dist(i,j)$ 为 $i$ 到 $j$ 的路径，这样的和就是树上所有链和减去每条边的权值，$\texttt{dfs}$ 求每条边的贡献即可。

2.当 $i$ 和 $j$ 是父子关系：

不妨设 $i$ 是 $j$ 的父亲。

我们猜想答案一定是从 $i$ 到一个其他的点，再从这个点到 $j$，显然这个点越近越好，于是就有以下几种情况考虑（设这个中转点为 $k$）：

- $k$ 为 $j$ 的一个孙子。
- $k$ 为 $i$ 的祖父。
- $k$ 为 $i$ 的父亲除 $i$ 外的儿子。
- $k$ 为 $i$ 除子树 $j$ 外的孙子。

可以自己画图理解一下。

$dist(i,j)=2mn+w(i,j)$，$mn$ 即为上面所有情况的最小值，可以用 $\texttt{dfs}$ 遍历树的时候求。

但是还有一种特殊情况，必须经过两个中转点，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8psdszof.png)

$i$ 是不能只通过一个点就到达 $j$ 的，必须按箭头方法到达 $j$，这时候要找两个中转点，一个是 $j$ 的一个儿子，另一个是 $i$ 的父亲或 $i$ 除 $j$ 外的儿子，求出最小值然后计算贡献就行了。

我这里计算求 $i$ 除 $j$ 外的儿子的最小值用的是前后缀 $\texttt{min}$，$i$ 除子树 $j$ 外的孙子等也可以这样做。

**Code：**

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO{
    char ibuf[4000010],*iS,*iT;
    #if ONLINE_JUDGE
    #define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,4000010,stdin),(iS==iT?EOF:*iS++):*iS++)
    #else
    #define gh() getchar()
    #endif
    #define reg register
    inline int read(){
        reg char ch=gh();
        reg int x=0;
        reg char t=0;
        while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
        while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
        return t?-x:x;
    }
    inline char getc(){
        char ch=gh();
        while(ch<'A'||ch>'Z') ch=gh();
        return ch;
    }
}using namespace IO;
typedef long long ll;
const int mod = 1e9 + 7;
const ll inf = 1e12;
int n,fa[2000010];
ll mn[2000010],mmn[2000010];
/*
mn[i]：i所有儿子的最小值 mmn[i]：i所有孙子的最小值 
f[i]：i父亲到i的距离 ff[i]：i祖父到i的距离
f2[i]：i的父亲除i之外的儿子到i的距离的最小值
*/
struct edge {
	int v;
	ll w;
	int nxt;
}ed[4000010];
int cnt,head[2000010];
void add(int u,int v,int w) {
	ed[++cnt] = {v,w,head[u]};
	head[u] = cnt;
}
long long ans = 0;
ll st[2000010],pmn[2000010],smn[2000010],ff[2000010];
ll st2[2000010],pmn2[2000010],smn2[2000010],f[2000010];
ll f2[2000010];
int sz[2000010];
void dfs1(int x,int f,ll d) {
	mn[x] = inf, ff[x] = inf, sz[x] = 1;
	for (int i = head[x];i;i = ed[i].nxt) {
		int v = ed[i].v;
		if (v == f) continue;
		fa[v] = x, mn[x] = min(mn[x],ed[i].w);
		dfs1(v,x,ed[i].w);
		ff[v] = ed[i].w + d;
		sz[x] += sz[v];
		ans = (ans + 1ll * sz[v] * (n - sz[v]) % mod * ed[i].w % mod) % mod;
		ans = (ans - ed[i].w + mod) % mod;
     		//对于这条边，下面sz[v]个点，上面n-sz[v]个点任意配对
	}
	int top = 0;
	for (int i = head[x];i;i = ed[i].nxt)
		if (ed[i].v != fa[x])
			st[++top] = ed[i].w, pmn[top] = min(pmn[top-1],st[top]);
	smn[top + 1] = inf;
	for (int i = top;i;i -- ) smn[i] = min(smn[i + 1],st[i]);
	for (int i = head[x],j = 1;i;i = ed[i].nxt, j ++ ) {
		int v = ed[i].v;
		if (v == fa[x]) continue;
		f2[v] = min(pmn[j-1],smn[j+1]) + ed[i].w;
	}
}
void dfs2(int x) {
	int top = 0;
	for (int i = head[x];i;i = ed[i].nxt) {
		int v = ed[i].v;
		if (v == fa[x]) continue;
		dfs2(v);
	}
	for (int i = head[x];i;i = ed[i].nxt)
		if (ed[i].v != fa[x])
			st[++top] = mn[ed[i].v] + ed[i].w, pmn[top] = min(pmn[top-1],st[top]),
			st2[top] = ed[i].w, pmn2[top] = min(pmn2[top-1],st2[top]);
	smn[top + 1] = smn2[top + 1] = inf;
	for (int i = top;i;i -- ) smn[i] = min(smn[i+1],st[i]), smn2[i] = min(smn2[i+1],st2[i]);
	for (int i = head[x],j = 1;i;i = ed[i].nxt, j ++ ) {
		int v = ed[i].v;
		if (v == fa[x]) continue;
		ll t1 = min(min(min(min(pmn[j-1],smn[j+1]),mmn[v]),ff[x]),f2[x]) * 2ll + ed[i].w;
		ll t2 = 3 * ed[i].w + 2 * (mn[v] + min(min(pmn2[j-1],smn2[j+1]),f[x]));
		if (t1 < inf || t2 < inf) ans = (ans + min(t1,t2)) % mod;
	}
}
int main() {
	n = read();
	for (int i = 1;i < n;i ++ ) {
		int u = read(),v = read(),w = read();
		add(u,v,w), add(v,u,w);
	}
	pmn[0] = pmn2[0] = inf;
	dfs1(1,0,inf);
	f[1] = f2[1] = inf;
	for (int i = 1;i <= n;i ++ ) {
		mmn[i] = inf;
		for (int j = head[i];j;j = ed[j].nxt)
			if (ed[j].v != fa[i]) mmn[i] = min(mmn[i],mn[ed[j].v]+ed[j].w), f[ed[j].v] = ed[j].w;
	}
//	for (int i = 1;i <= n;i ++ ) cout << mn[i] << ' ' << mmn[i] << ' ' << f[i] << endl; 
	dfs2(1);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：JackMerryYoung (赞：2)

# 前言

学校搜索作业的一道题目，没人写就我来写了。

注意：这是一道细节巨多的题目，调试的时候要有耐心。

# 正文

尝试对 $i, j$ 两点的关系进行分类讨论。

## 1. $i, j$ 没有直接关系

由题意得补图 $G$ 的边的权值为树 $T$ 上 $i, j$ 两点的简单路径权值和。

既然两点无关系，那么答案即为路径长度。

那么 DFS 求解路径长度即可。

## 2. $i, j$ 是父子关系

不妨令 $i$ 为 $j$ 的父亲。

既然补图 $G$ 没有一条直边使得两点相连，那么可以寻找另一个中转点 $k$ 求得最短路。

那么 $k$ 是哪些点呢？

它可以是与 $i, j$ 相连的其他点。

那么就分别去 DFS 求最小值，最后求得一个总的最小即为答案。

还有一种很奇特的情况，就是在链上的父子需要两个中转点，特判处理即可。

---

分类讨论结束。不过时间复杂度为 $\mathcal{O}(N^2)$, 竟然不可以通过？

上述做法还是过不了，于是我们思考瓶颈何在。

发现求除去一个点的最小值都需要重新计算，考虑优化。

实用优化小技巧：树上问题中，前后缀最小值求去除一个节点的最小值。

这样就能去掉一维，复杂度大大下降。

现在的做法复杂度仅为 $\mathcal{O}(N)$, 可以通过本题。

读入超时就用 `scanf`, 再不行就用快读。

# 代码

可变参数列表的 `my_min()` 是我找的板子。

您可以写 `min()` 嵌套，但是很丑。

带宏定义的代码就不放了，这里的仅供参考，不要抄袭。

``` cpp
llong N, fa[2000010];
llong sonmin[2000010], gsonmin[2000010];

struct Edge {
	llong to, dis, nxt;
} edge[4000010];

llong cnt, head[2000010];

void add(llong u, llong v, llong w)
{
    ++ cnt;
	edge[cnt].to  = v;
    edge[cnt].nxt = head[u];
    edge[cnt].dis = w;
    head[u] = cnt;
}

llong ans = 0;
llong start1[2000010], pfmin1[2000010], sfmin1[2000010], gfadis[2000010];
llong start2[2000010], pfmin2[2000010], sfmin2[2000010], fadis[2000010];
llong nsdmin[2000010];
llong tcnt[2000010];

template<typename T>
T my_min(T&& t)
{
    return std::forward<T>(t);
}

template<typename T0, typename T1, typename... Ts>
typename std::common_type<T0, T1, Ts...>::type my_min(T0&& val1, T1&& val2, Ts&& ... vs)
{
    if (val2 < val1)
        return my_min(val2, std::forward<Ts>(vs) ...);
    else
        return my_min(val1, std::forward<Ts>(vs) ...);
}

void dfs1(llong u, llong f, llong d) 
{
	sonmin[u] = gfadis[u] = my_inf;
	tcnt[u] = 1;
	for(llong i = head[u]; i; i = edge[i].nxt) 
    {
		llong v = edge[i].to;
		llong w = edge[i].dis;
		if(v == f) 
			continue;

		fa[v] = u;
		sonmin[u] = my_min(sonmin[u], w);
		dfs1(v, u, w);
		gfadis[v] = w + d;
		tcnt[u] += tcnt[v];
		ans = ((ans + tcnt[v] * (N - tcnt[v]) % MOD * w % MOD) % MOD - w + MOD) % MOD;
	}

	llong tot = 0;
	for(llong i = head[u]; i; i = edge[i].nxt)
    {
        llong v = edge[i].to;
		llong w = edge[i].dis;
        if(v == fa[u]) 
			continue;
			
        ++ tot;
        start1[tot] = w;
        pfmin1[tot] = my_min(pfmin1[tot - 1], start1[tot]);
    }
		

	sfmin1[tot + 1] = my_inf;
	for(llong i = tot; i; -- i) 
		sfmin1[i] = my_min(sfmin1[i + 1], start1[i]);

	for(llong i = head[u], j = 1; i; i = edge[i].nxt, ++ j)
    {
		llong v = edge[i].to;
		llong w = edge[i].dis;
		if(v == fa[u]) continue;
		nsdmin[v] = min(pfmin1[j - 1], sfmin1[j + 1]) + w;
	}
}

void dfs2(llong u) 
{
	llong tot = 0;
	for(llong i = head[u]; i; i = edge[i].nxt) 
	{
		llong v = edge[i].to;
		if(v == fa[u]) 
			continue;

		dfs2(v);
	}

	for(llong i = head[u]; i; i = edge[i].nxt)
	{
        llong v = edge[i].to;
		llong w = edge[i].dis;
		if(v == fa[u]) 
			continue;

        ++ tot;
        start1[tot] = sonmin[v] + w;
		pfmin1[tot] = min(pfmin1[tot - 1], start1[tot]);
		start2[tot] = w;
        pfmin2[tot] = min(pfmin2[tot - 1], start2[tot]);
	}

	sfmin1[tot + 1] = sfmin2[tot + 1] = my_inf;
	for(llong i = tot; i; -- i) 
	{
		sfmin1[i] = min(sfmin1[i + 1], start1[i]);
		sfmin2[i] = min(sfmin2[i + 1], start2[i]);
	}

	for(llong i = head[u], j = 1; i; i = edge[i].nxt, ++ j)
	{
		llong v = edge[i].to;
		llong w = edge[i].dis;
		if(v == fa[u]) 
			continue;

		llong tmp1 = my_min(pfmin1[j - 1], sfmin1[j + 1], gfadis[u], nsdmin[u], gsonmin[v]) * 2ll + w;
		llong tmp2 = 3 * w + 2 * (sonmin[v] + my_min(pfmin2[j - 1], sfmin2[j + 1], fadis[u]));
		if(tmp1 < my_inf || tmp2 < my_inf) 
			ans = (ans + min(tmp1, tmp2)) % MOD;
	}
}

signed main() 
{
	cin >> N;
	for(llong i = 1; i < N; ++ i) 
    {
		int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
        add(v, u, w);
	}

	pfmin1[0] = pfmin2[0] = my_inf;
	dfs1(1, 0, my_inf);
	fadis[1] = nsdmin[1] = my_inf;
	for(llong i = 1; i <= N; ++ i) 
	{
		gsonmin[i] = my_inf;
		for(llong j = head[i]; j; j = edge[j].nxt)
        {
            llong v = edge[j].to;
			llong w = edge[j].dis;
			if(v == fa[i]) 
                continue;

			gsonmin[i] = my_min(gsonmin[i], sonmin[v] + w);
			fadis[v] = w;		
        }
	}

	dfs2(1);
	cout << ans << endl;
	return 0;
}
```

# 后言

这题也够坑，调了我一天。

---

