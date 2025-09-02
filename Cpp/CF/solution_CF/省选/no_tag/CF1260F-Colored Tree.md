# Colored Tree

## 题目描述

You're given a tree with $ n $ vertices. The color of the $ i $ -th vertex is $ h_{i} $ .

The value of the tree is defined as $ \sum\limits_{h_{i} = h_{j}, 1 \le i < j \le n}{dis(i,j)} $ , where $ dis(i,j) $ is the number of edges on the shortest path between $ i $ and $ j $ .

The color of each vertex is lost, you only remember that $ h_{i} $ can be any integer from $ [l_{i}, r_{i}] $ (inclusive). You want to calculate the sum of values of all trees meeting these conditions modulo $ 10^9 + 7 $ (the set of edges is fixed, but each color is unknown, so there are $ \prod\limits_{i = 1}^{n} (r_{i} - l_{i} + 1) $ different trees).

## 说明/提示

In the first example there are four different ways to color the tree (so, there are four different trees):

- a tree with vertices colored as follows: $ \lbrace 1,1,1,1 \rbrace $ . The value of this tree is $ dis(1,2)+dis(1,3)+dis(1,4)+dis(2,3)+dis(2,4)+dis(3,4) = 10 $ ;
- a tree with vertices colored as follows: $ \lbrace 1,2,1,1 \rbrace $ . The value of this tree is $ dis(1,3)+dis(1,4)+dis(3,4)=4 $ ;
- a tree with vertices colored as follows: $ \lbrace 1,1,1,2 \rbrace $ . The value of this tree is $ dis(1,2)+dis(1,3)+dis(2,3)=4 $ ;
- a tree with vertices colored as follows: $ \lbrace 1,2,1,2 \rbrace $ . The value of this tree is $ dis(1,3)+dis(2,4)=4 $ .

Overall the sum of all values is $ 10+4+4+4=22 $ .

## 样例 #1

### 输入

```
4
1 1
1 2
1 1
1 2
1 2
1 3
3 4
```

### 输出

```
22
```

# 题解

## 作者：xht (赞：15)

# 请到博客查看

首先设根为 $1$，设 $\text{dep}(x)$ 为 $x$ 的深度（$\text{dep}(1) = 0$），设 $\text{dis}(x,y), \text{lca}(x,y)$ 分别为 $x,y$ 的距离和最近公共祖先，显然有 $\text{dis}(x,y) = \text{dep}(x) + \text{dep}(y) - 2\text{dep}(\text{lca}(x,y))$。

再设 $v(x,c) = [l_x \le c \le r_x]$，$g(x) = r_x - l_x + 1$，$p = \prod_{i = 1} ^ n g(i)$。

对于两个点 $x,y$ 和一个颜色 $c$，其对答案的贡献为

$$
\begin{aligned}
ans &= [l_x \le  c \le r_x][l_y \le c \le r_y]\text{dis}(x,y)\prod_{z \ne x,y}(r_z - l_z + 1) \\
&= pv(x,c)v(y,c)(\text{dep}(x) + \text{dep}(y) - 2\text{dep}(\text{lca}(x,y)))\frac{1}{g(x)g(y)}
\end{aligned}
$$

首先考虑

$$
A = v(x,c)v(y,c)(\text{dep}(x) + \text{dep}(y))\frac{1}{g(x)g(y)}
$$

注意到，对于一个点 $x$ 和一个颜色 $c$，其对 $A$ 贡献为

$$
v(x,c)\text{dep}(x)(\sum_{v(y,c)}\frac{1}{g(x)g(y)} - \frac{1}{g^2(x)})
$$

则

$$
\begin{aligned}
A &= \sum_{v(x,c)}\text{dep}(x)(\sum_{v(y,c)}\frac{1}{g(x)g(y)} - \frac{1}{g^2(x)}) \\
&= \sum_{v(x,c)}\frac{\text{dep}(x)}{g(x)}\sum_{v(x,c)}\frac{1}{g(x)}-\sum_{v(x,c)}\frac{\text{dep}(x)}{g^2(x)}
\end{aligned}
$$

显然可以把 $c$ 从小到大扫一遍，同时维护

$$
\begin{aligned}
A_1 &= \sum_{v(x,c)}\frac{\text{dep}(x)}{g(x)} \\
A_2 &= \sum_{v(x,c)}\frac{1}{g(x)} \\
A_3 &= \sum_{v(x,c)}\frac{\text{dep}(x)}{g^2(x)}
\end{aligned}
$$

接下来考虑

$$
B = v(x,c)v(y,c)\text{dep}(\text{lca}(x,y))\frac{1}{g(x)g(y)}
$$

设 $s(x)$ 表示 $x$ 对 $B$ 的贡献，$S(x)$ 表示 $x$ 的所有祖先的 $s$ 之和。

注意到当我们加入一个点 $x$ 时，如果将 $x$ 的所有祖先的 $s$ 全都加上 $g(x)$，那么对于一个 $y$，其对 $B$ 的贡献 $= \frac{S(y) - s(1)}{g(y)}$。

树剖 + 树状数组即可。

总时间复杂度 $\mathcal O(n \log^2 n)$。

```cpp
const int N = 1e5 + 7;
int n, C, l[N], r[N], d[N], f[N], s[N], son[N], dfn[N], rnk[N], top[N], num;
modint g[N], vg[N], p, vp, now, A1, A2, A3, ans, c1[N], c2[N];
vi e[N], L[N], R[N];

void dfs(int x) {
	s[x] = 1;
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == f[x]) continue;
		d[y] = d[x] + 1;
		f[y] = x;
		dfs(y);
		s[x] += s[y];
		if (s[y] > s[son[x]]) son[x] = y; 
	}
}

void dfs(int x, int p) {
	top[x] = p;
	dfn[x] = ++num;
	rnk[num] = x;
	if (!son[x]) return;
	dfs(son[x], p);
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == f[x] || y == son[x]) continue;
		dfs(y, y);
	}
}

inline void add(modint *c, int x, modint k) {
	while (x <= n + 1) c[x] += k, x += x & -x;
}

inline modint ask(modint *c, int x) {
	modint ret = 0;
	while (x) ret += c[x], x -= x & -x;
	return ret;
}

inline void Add(int x, modint k) {
	while (x) {
		add(c1, dfn[top[x]], k);
		add(c1, dfn[x] + 1, -k);
		add(c2, dfn[top[x]], k * dfn[top[x]]);
		add(c2, dfn[x] + 1, -k * (dfn[x] + 1));
		x = f[top[x]];
	}
}

inline modint Ask(int x) {
	modint ret = -(ask(c1, 1) * 2 - ask(c2, 1));
	while (x) {
		ret += ask(c1, dfn[x]) * (dfn[x] + 1) - ask(c2, dfn[x]);
		ret -= ask(c1, dfn[top[x]] - 1) * dfn[top[x]] - ask(c2, dfn[top[x]] - 1);
		x = f[top[x]];
	}
	return ret;
}

int main() {
	rd(n), p = 1;
	for (int i = 1; i <= n; i++) {
		rd(l[i]), rd(r[i]);
		g[i] = r[i] - l[i] + 1;
		vg[i] = g[i] ^ -1;
		p *= g[i];
		C = max(C, r[i]);
		L[l[i]].pb(i), R[r[i]].pb(i);
	}
	for (int i = 1, x, y; i < n; i++)
		rd(x), rd(y), e[x].pb(y), e[y].pb(x);
	vp = p ^ -1;
	dfs(1);
	dfs(1, 1);
	for (int c = 1; c <= C; c++) {
		for (ui i = 0; i < L[c].size(); i++) {
			int x = L[c][i];
			A1 += d[x] * vg[x];
			A2 += vg[x];
			A3 += d[x] * vg[x] * vg[x];
			now += Ask(x) * vg[x];
			Add(x, vg[x]);
		}
		ans += A1 * A2 - A3 - 2 * now;
		for (ui i = 0; i < R[c].size(); i++) {
			int x = R[c][i];
			A1 -= d[x] * vg[x];
			A2 -= vg[x];
			A3 -= d[x] * vg[x] * vg[x];
			Add(x, -vg[x]);
			now -= Ask(x) * vg[x];
		}
	}
	print(ans * p);
	return 0;
}
```

---

## 作者：Dreamunk (赞：4)

（按照luogu的尿性，估计式子又会挂，可以到博客查看）

一千个人有一千零一种做法。

记 $len_i=r_i-l_i+1,p=\prod_i len_i$。

考虑对每种颜色算贡献。那么颜色 $h$ 的贡献为：

$\sum_{l_i\le h\le r_i}\sum_{l_j\le h\le r_j,j<i}dis(i,j)\frac{p}{len_ilen_j}$

把 ${dis}(i,j)$ 拆出来：

$\sum_{l_i\le h\le r_i}\sum_{l_j\le h\le r_j,j<i}[{dep}_i+{dep}_j-2{dep}_{{lca}(i,j)}]\frac{p}{len_ilen_j}$

把一些东西往前挪：

$\sum_{l_i\le h\le r_i}\frac{p}{len_i}\sum_{l_j\le h\le r_j,j<i}[{dep}_i+{dep}_j-2{dep}_{{lca}(i,j)}]\frac{1}{len_j}$

整理一下：

$\sum_{l_i\le h\le r_i}\frac{p}{len_i}[({dep}_i\sum_{l_j\le h\le r_j,j<i}\frac{1}{len_j})+(\sum_{l_j\le h\le r_j,j<i}\frac{{dep}_j}{len_j})-2(\sum_{l_j\le h\le r_j,j<i}\frac{{dep}_{{lca}(i,j)}}{len_j})]$

从 $1$ 到 $100\ 000$ 去枚举 $h$，一个点的贡献自然是在 加入时（$l$ 时刻）加上，然后在 删除时（$r$ 时刻）减掉。

于是我们要维护右边那三坨东西。前面两个随便维护，第三个采取 [这题](https://www.luogu.com.cn/problem/P4211) 的方法维护即可。

使用树剖就是 $O(n\log^2 n)$ 的，用 LCT 就是 $O(n\log n)$。

于是这题就做完了。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
const int N=1e5+3,M=1e9+7,K=18;
#define Md (L+R>>1)
struct segment_tree{
	int s[1<<K],lz[1<<K];
	inline void Down(int L,int R,int k){
		lz[k<<1]=(lz[k<<1]+lz[k])%M;
		lz[k<<1|1]=(lz[k<<1|1]+lz[k])%M;
		s[k<<1]=(s[k<<1]+(ll)lz[k]*(Md-L+1))%M;
		s[k<<1|1]=(s[k<<1|1]+(ll)lz[k]*(R-Md))%M;
		lz[k]=0;
	}
	int Sum(int l,int r,int L,int R,int k){
		if(l>r)return 0;
		if(l<=L&&R<=r)return s[k];
		Down(L,R,k);
		if(l>Md)return Sum(l,r,Md+1,R,k<<1|1);
		if(r<=Md)return Sum(l,r,L,Md,k<<1);
		return(Sum(l,r,L,Md,k<<1)+Sum(l,r,Md+1,R,k<<1|1))%M;
	}
	void Add(int l,int r,int a,int L,int R,int k){
		if(l>r)return;
		if(l<=L&&R<=r){
		  lz[k]=(lz[k]+a)%M;
		  s[k]=(s[k]+(ll)a*(R-L+1))%M;
		  return;
		}
		Down(L,R,k);
		if(l<=Md)Add(l,r,a,L,Md,k<<1);
		if(r>Md)Add(l,r,a,Md+1,R,k<<1|1);
		s[k]=(s[k<<1]+s[k<<1|1])%M;
	}
}t;
struct edge{int v,nxt;}g[N+N];
int n,head[N],k,dep[N],prod,invl[N],inv[N],s,s0,s1,ans,dfn[N],son[N],siz[N],top[N],fa[N];
inline void Insert(int u,int v){g[++k]=(edge){v,head[u]};head[u]=k;}
struct update{
	int x,u,f;
	bool operator<(const update&b)const{return x<b.x;}
}upd[N+N];
void Dfs(int u){
	int v;
	siz[u]=1;
	for(int i=head[u];i;i=g[i].nxt)if((v=g[i].v)!=fa[u])
	  dep[v]=dep[u]+1,fa[v]=u,Dfs(v),siz[u]+=siz[v],son[u]=siz[son[u]]>siz[v]?son[u]:v;
}
void Dfs1(int u){
	int v;
	dfn[u]=++k,top[u]=top[u]?top[u]:u;
	if(son[u])top[son[u]]=top[u],Dfs1(son[u]);
	for(int i=head[u];i;i=g[i].nxt)if((v=g[i].v)!=fa[u]&&v!=son[u])
	  Dfs1(v);
}
inline void Pathadd(int u,int a){
	for(;u;u=fa[top[u]])
	  t.Add(dfn[top[u]==1?son[1]:top[u]],dfn[u],a,1,n,1);
}
inline int Pathsum(int u){
	int s=0;
	for(;u;u=fa[top[u]])
	  s=(s+t.Sum(dfn[top[u]==1?son[1]:top[u]],dfn[u],1,n,1))%M;
	return s;
}
int main(){
	int u,v,l,r,f;
	scanf("%d",&n);
	inv[1]=1;for(int i=2;i<N;i++)inv[i]=(ll)inv[M%i]*(M-M/i)%M;
	prod=1;
	for(u=1;u<=n;u++){
	  scanf("%d%d",&l,&r);
	  invl[u]=inv[r-l+1];
	  prod=(ll)prod*(r-l+1)%M;
	  upd[u]=(update){l,u,1};
	  upd[u+n]=(update){r+1,u,M-1};
	}
	std::sort(upd+1,upd+1+n+n);
	for(int i=1;i<n;i++)scanf("%d%d",&u,&v),Insert(u,v),Insert(v,u);
	Dfs(1);
	k=0,Dfs1(1);
	for(int i=1,j=1;i<N;i++){
	  for(;upd[j].x==i;j++){
		u=upd[j].u,f=upd[j].f;
		s0=(s0+(ll)invl[u]*f)%M;
		s1=(s1+(ll)invl[u]*dep[u]%M*f)%M;
		Pathadd(u,(ll)invl[u]*f%M);
		s=(s+(ll)f*prod%M*invl[u]%M*(((ll)dep[u]*s0+s1-2*Pathsum(u)%M+M)%M))%M;
	  }
	  ans=(ans+s)%M;
	}printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Fuyuki (赞：4)

## Describtion

给定一棵树，每个节点有一个颜色$h$，$h_i$为$[L_i,R_i]$内的一个整数。

现在，对于所有$\prod (R_i-L_i+1)$种不同的染色方案，求出下列式子之和：

$$\sum_{h_i=h_j,1\leq i<j\leq n}dis(i,j)$$

$n\leq 10^5,1\leq L_i\leq R_i\leq 10^5$，答案对1e9+7取模。

## Solution

CER真是容易降智。

按惯例把$dis(i,j)$拆成$dep_i+dep_j-2dep_{lca(i,j)}$。

那么分别考虑一个点作为端点的贡献和作为lca的贡献。

作为端点的贡献就是和自己颜色相同的点的个数，这里每个颜色每个点分别贡献独立，做一个区间求和即可。

作为lca的贡献相当于跨子树之间在颜色上做点乘，这个用dsu on tree处理之后点乘的贡献之和也可以转化成区间求和。

用树状数组处理的话跑到了CF rank1。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define rnt re int
#define re register
#define I inline int
#define V inline void
#define isnum(ch) ('0'<=ch&&ch<='9')
#define FOR(i,a,b) for(rnt i=a;i<=b;i++)
#define REP(u) for(rnt _=h[u],v;v=e[_].t,_;_=e[_].n)if(v^pre[u])
#define gc (_op==_ed&&(_ed=(_op=_buf)+fread(_buf,1,100000,stdin),_op==_ed)?EOF:*_op++)
char _buf[100000],*_op(_buf),*_ed(_buf);
I getint(){
	rnt _s=0;re char _ch=gc;
	while(!isnum(_ch))_ch=gc;
	while(isnum(_ch))_s=_s*10+_ch-48,_ch=gc;
	return _s;
}
const int N=1e5+1,mod=1e9+7;
V check(int&x){x-=mod,x+=x>>31&mod;}
int n,ans,tot,sum,now,len[N],h[N],w[N];
int a[N],b[N],c[N],d[N],inv[N],pre[N],siz[N],wes[N],dep[N];
struct edge{int t,n;}e[N<<1];
V add_edge(rnt x,rnt y){
	e[++tot]=(edge){y,h[x]},h[x]=tot;
	e[++tot]=(edge){x,h[y]},h[y]=tot;
}
V input(){
	n=getint();rnt x,y;
	FOR(i,1,n)a[i]=getint(),b[i]=getint(),len[i]=b[i]-a[i]+1;
	FOR(i,2,n)x=getint(),y=getint(),add_edge(x,y);
}
V init(rnt u){
	siz[u]=1,dep[u]=dep[pre[u]]+1;
	REP(u){
		pre[v]=u,init(v),siz[u]+=siz[v];
		if(siz[v]>siz[wes[u]])wes[u]=v;
	}
}
I lowbit(const int&x){return x&-x;}
V add(rnt x,rnt y){
	for(rnt w=1ll*x*y%mod;x<N;x+=lowbit(x))
		check(c[x]+=w),check(d[x]+=y);
}
I ask(rnt x){
	rnt out=0,tmp=0;
	for(rnt i=x;i;i^=lowbit(i))
		check(tmp+=d[i]),check(out+=c[i]);
	check(out=1ll*(x+1)*tmp%mod+mod-out);
	return out;
}
V add(rnt l,rnt r,rnt x){add(l,x),add(r+1,mod-x);}
I ask(rnt l,rnt r){return (ask(r)-ask(l-1)+mod)%mod;}
V init(){
	inv[0]=1,inv[1]=1,sum=1,init(1);
	FOR(i,2,N-1)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	FOR(i,1,n)sum=1ll*sum*len[i]%mod;
	FOR(i,1,n)add(a[i],b[i],w[i]=1ll*sum*inv[len[i]]%mod);
	FOR(i,1,n)check(ans+=1ll*(mod+ask(a[i],b[i])-sum)*inv[len[i]]%mod*dep[i]%mod);
	FOR(i,1,N-1)c[i]=d[i]=0;
}
V once(rnt u){check(ans+=mod-2ll*now*ask(a[u],b[u])%mod*inv[len[u]]%mod);}
V clean(rnt u){add(a[u],b[u],mod-w[u]);REP(u)clean(v);}
V calc(rnt u){once(u);REP(u)calc(v);}
V add(rnt u){add(a[u],b[u],w[u]);REP(u)add(v);}
V dfs(rnt u){
	REP(u)if(v!=wes[u])dfs(v),clean(v);
	if(wes[u])dfs(wes[u]);
	now=dep[u],once(u),add(a[u],b[u],w[u]);
	REP(u)if(v!=wes[u])calc(v),add(v);
}
V work(){dfs(1),cout<<ans;}
int main(){
	input();
	init();
	work();
	return 0;
}
```


---

## 作者：Reunite (赞：3)

## 一
---

难得自己能独立切一题，说一个做法不大一样的实现。

首先这题的本质还是树上点对距离和，但由于贡献不同，不能直接把贡献拆到边上，但是我们可以点分治啊。注意到答案可以表示为：

$$\sum_{u<v} \{dis_{(u,v)}\cdot([l_u,r_u]\cap[l_v,r_v])\cdot \prod_{x \neq u,v}(r_x-l_x+1) \}$$

注意到后面那个连乘很无聊，预处理 $fn_u=\frac{\prod \limits_{i} (r_i-l_i+1)}{r_u-l_u+1}$。

对于点分中心 $U$，设当前分治层中 $u$ 到 $U$ 的距离为 $d_u$，按照 $l,r$ 的值域为下标开两棵线段树，分子树处理，则 $u$ 的贡献是：

$$ans= \sum_{v} \{ (d_u+d_v)\cdot([l_u,r_u]\cap[l_v,r_v])\cdot fn_v\cdot\frac{1}{r_u-l_u+1} \} $$

$$=(\frac{1}{r_u-l_u+1})(d_u\sum_{v} ([l_u,r_u]\cap[l_v,r_v])\cdot fn_v+\sum_{v} ([l_u,r_u]\cap[l_v,r_v])\cdot fn_v\cdot d_v)$$

于是发现这玩意只需要区间加，区间求和的数据结构就做完了。因为我们以 $l,r$ 的值域为下标，所以交集的贡献很容易处理。然后你发现超时了，换成 zkw 或者树状数组就行了。

复杂度两只 $\log$。

## 二
---

```cpp

#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ll long long
#define mod 1000000007
using namespace std;

int n,tot,root,tt,len=100000;
int l[100005];
int r[100005];
ll fn[100005];
ll inv[100005];
int sz[100005];
int msz[100005];
bool mp[100005];
int dep[100005];
int fa[21][100005];
vector <int> g[100005];
pair <int,int> a[100005];
ll ans;

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline int LCA(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	int t=dep[u]-dep[v];
	for(int i=0;i<=20;i++)
		if(t&(1<<i)) u=fa[i][u];
	if(u==v) return u;
	for(int i=20;i>=0;i--)
		if(fa[i][u]!=fa[i][v]) u=fa[i][u],v=fa[i][v];
	return fa[0][u];
}

inline int dis(int u,int v){return dep[u]+dep[v]-2*dep[LCA(u,v)];}

struct BIT{
	ll t[100005];
	inline void add(int x,ll k){while(x<=len) (t[x]+=k)%=mod,x+=x&-x;return ;}
	inline ll ask(int x){ll s=0;while(x) (s+=t[x])%=mod,x^=x&-x;return s;}
};

struct segmenttree{
	BIT t1,t2;
	inline void updata(int l,int r,ll x){
		t1.add(l,x);
		t1.add(r+1,-x);
		t2.add(l,x*(l-1)%mod);
		t2.add(r+1,-x*r%mod+mod);
		return ;
	}
	inline ll query(int l,int r){return (t1.ask(r)*r%mod-t1.ask(l-1)*(l-1)%mod-t2.ask(r)+t2.ask(l-1)+mod)%mod;}
}t1,t2;

inline void init(int u,int fath){
	fa[0][u]=fath;
	dep[u]=dep[fath]+1;
	for(int v:g[u]){
		if(v==fath) continue;
		init(v,u);
	}
	return ;
}

inline void getroot(int u,int fa){
	sz[u]=1,msz[u]=0;
	for(int v:g[u]){
		if(v==fa||mp[v]) continue;
		getroot(v,u);
		sz[u]+=sz[v];
		msz[u]=max(msz[u],sz[v]);
	}
	msz[u]=max(msz[u],tot-sz[u]);
	if(msz[u]<msz[root]) root=u;
	return ;
}

inline void getinformation(int u,int fa,int d){
	a[++tt]={u,d};
	for(int v:g[u]){
		if(v==fa||mp[v]) continue;
		getinformation(v,u,d+1);
	}
	return ;
}

inline void work(int u){
	tt=0;
	a[++tt]={u,0};
	t2.updata(l[u],r[u],fn[u]);
	for(int v:g[u]){
		if(mp[v]) continue;
		int lf=tt+1;
		getinformation(v,u,1);
		int rt=tt;
		for(int i=lf;i<=rt;i++){
			int uu=a[i].first;
			ans=(ans+t1.query(l[uu],r[uu])*inv[r[uu]-l[uu]+1]%mod)%mod;
			ans=(ans+a[i].second*t2.query(l[uu],r[uu])%mod*inv[r[uu]-l[uu]+1]%mod)%mod;
		}
		for(int i=lf;i<=rt;i++){
			int uu=a[i].first;
			t1.updata(l[uu],r[uu],a[i].second*fn[uu]%mod);
			t2.updata(l[uu],r[uu],fn[uu]);
		}
	}
	for(int i=1;i<=tt;i++){
		int uu=a[i].first;
		t1.updata(l[uu],r[uu],-a[i].second*fn[uu]%mod+mod);
		t2.updata(l[uu],r[uu],-fn[uu]+mod);
	}

	return ;
}

inline void solve(int u){
	mp[u]=1;
	work(u);
	for(int v:g[u]){
		if(mp[v]) continue;
		tot=sz[v],root=0;
		getroot(v,u);
		solve(root);
	}
	
	return ;
}

int main(){
	in(n);
	ll mul=1;
	for(int i=1;i<=n;i++) in(l[i]),in(r[i]),(mul*=(r[i]-l[i]+1))%=mod;
	inv[1]=1;
	for(int i=2;i<=100000;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=n;i++) fn[i]=mul*inv[r[i]-l[i]+1]%mod;
	for(int i=1;i<n;i++){
		int u,v;
		in(u),in(v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	init(1,0);
	for(int j=1;j<=20;j++)
		for(int i=1;i<=n;i++)
			fa[j][i]=fa[j-1][fa[j-1][i]];
	sz[0]=msz[0]=(tot=n)+1;
	getroot(1,0);
	solve(root);
	printf("%lld\n",ans);

	return 0;
} 
```

---

## 作者：FZzzz (赞：3)

先说几句闲话。

先膜一下楼上 xht，Fuyuki 等各位神仙，他们太强了。

这是道神题，然而我并不会数据结构，所以这篇题解**没有用到任何数据结构**。

~~但是不知道为什么还是跑得慢死，而且代码还比 Fuyuki 神仙长多了~~……所以继续膜 Fuyuki 神仙。

然而这个做法我认为还是这道题目前最好想最好写的做法。~~尽管我调了两天。~~

~~哦对我为什么要来做这题呢？其实是看错了某题单里某一题的题号啦（~~

------------
进入正题。

首先考虑套路点分。先求出当前子树内所有点 $i$ 到分治中心的距离 $dep_i$，然后计算所有点互相的贡献，再去容斥掉分治中心所有子树的贡献。

然后……就不会了。我们发现似乎单独考虑一个点没法计算所有点对他的贡献，然后也没什么好的办法去计算所有点对之间的贡献。

那我们不妨换个思路，去考虑每种颜色。

所以我们**对颜色做扫描线**。将所有点差分成出现和消失两个事件，然后排序，这样就可以单独计算每个颜色的贡献了。

这样的话，假设当前所有被考虑到的点的集合为 $S$，则贡献为
$$\sum\limits_{i,j\in S,i<j}(dep_i+dep_j)\prod\limits_{k=1}^n[k\ne i,j](r_k-l_k+1)$$
然后！是的我们就可以开始愉快地推式子了！

首先记 $len_i=r_i-l_i+1$，然后就把 $\prod\limits_{i=1}^nlen_i$ 提到一边去最后再算，这样的话就变成
$$\sum\limits_{i,j\in S,i<j}\frac{dep_i+dep_j}{len_ilen_j}$$
假装每个点可以与它自己造成贡献（反正也会在算子树的时候被容斥掉），这样就可以把每个 $dep$ 分开算贡献了，每个点 $i$ 的贡献就是
$$\sum\limits_{j\in S}\frac{dep_i}{len_ilen_j}=\frac{dep_i}{len_i}\sum\limits_{j\in S}\frac1{len_j}$$
那么总的贡献就是
$$\sum\limits_{i\in S}\frac{dep_i}{len_i}\sum\limits_{i\in S}\frac1{len_i}$$
所以我们对颜色做扫描线，维护 $\sum\limits_{i\in S}\frac{dep_i}{len_i}$ 和 $\sum\limits_{i\in S}\frac1{len_i}$。

复杂度 $O(n\log^2n)$。代码随手写的，码风比较丑，轻喷。
```cpp
#include<algorithm>
#include<vector>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=1e5+5;
int n,l[maxn],r[maxn];
vector<int> g[maxn];
typedef long long ll;
const ll mod=1e9+7;
ll inv[maxn];
bool vis[maxn];
int size[maxn];
void dfs1(int u,int fa){
	size[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa||vis[v]) continue;
		dfs1(v,u);
		size[u]+=size[v];
	}
}
int cen,res;
void dfs2(int u,int fa,int r){
	int maxs=size[r]-size[u];
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa||vis[v]) continue;
		dfs2(v,u,r);
		maxs=max(maxs,size[v]);
	}
	if(!cen||maxs<res){
		cen=u;
		res=maxs;
	}
}
int dep[maxn];
void dfs3(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa||vis[v]) continue;
		dfs3(v,u);
	}
}
typedef pair<int,int> pii;
void dfs4(int u,int fa,vector<pii>& res){
	res.push_back(pii(l[u],u));
	res.push_back(pii(r[u]+1,-u));
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa||vis[v]) continue;
		dfs4(v,u,res);
	}
}
ll calc(int u){
	vector<pii> res;
	dfs4(u,0,res);
	sort(res.begin(),res.end());
	ll ans=0,s1=0,s2=0;
	for(int i=0;i<res.size()-1;i++){
		int v=res[i].second;
		if(v>0){
			ll g=inv[r[v]-l[v]+1];
			s1=(s1+dep[v]*g%mod)%mod;
			s2=(s2+g)%mod;
		}
		else{
			v=-v;
			ll g=inv[r[v]-l[v]+1];
			s1=(s1+mod-dep[v]*g%mod)%mod;
			s2=(s2+mod-g)%mod;
		}
		ans=(ans+s1*s2%mod*(res[i+1].first-res[i].first)%mod)%mod;
	}
	return ans;
}
ll solve(int u){
	dfs3(u,0);
	ll ans=calc(u);
	vis[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(vis[v]) continue;
		ans=(ans+mod-calc(v))%mod;
	}
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(vis[v]) continue;
		dfs1(v,0);
		cen=0;
		dfs2(v,0,v);
		ans=(ans+solve(cen))%mod;
	}
	return ans;
}
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    for(int i=1;i<=n;i++){
    	l[i]=readint();
    	r[i]=readint();
	}
	for(int i=1;i<n;i++){
		int u,v;
		u=readint();
		v=readint();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	inv[1]=1;
	for(int i=2;i<maxn;i++)
		inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	dfs1(1,0);
	cen=0;
	dfs2(1,0,1);
	dep[0]=-1;
	ll ans=solve(cen);
	for(int i=1;i<=n;i++) ans=ans*(r[i]-l[i]+1)%mod;
	printf("%d\n",(int)ans);
    return 0;
}
```
这么好的题解，确定不点个赞再走吗？

---

## 作者：meiqwq (赞：3)

这题有点和LNOI 得 LCA那题类似

没人写LCT吗qwq

显然窝们是要求：

$\Pi_{i=1}^{n}(r_i-l_i+1) \sum\limits
_{i=1}^{n}\sum\limits_{j=i+1}^{n}|[max(l_i,l_j),min(r_i,r_j)]|dis(i,j)\frac{1}{(r_i-l_i+1)(r_j-l_j+1)}$

解释一下：就是枚举两个点$i$ 与$j$之间得贡献，当两个点去颜色相同时其它点任意取，再乘$dis(i,j)$

也就是说窝们要动态维护一个点集$S$，支持动态加入点与删除点

实时维护$\sum\limits_{i,j\in S}\frac{dis(i,j)}{(r_i-l_i+1)(r_j-l_j+1)}$

下面记$len_i=r_i-l_i+1$

考虑动态加入一个点$u$，介个点与点集中其他点产生的贡献如下

$\frac{1}{len_u}\sum_{i \in S}\frac{dep_i+dep_u-2dep_{lca(u,i)}}{len_i}$

$\sum_{i \in S}\frac{dep_i}{len_i}$与$dep_u\sum_{i \in S}\frac{1}{len_i}$都好维护

后面那部分读者阔以先做一下P4211

加入一个点时，窝们在这个点$i$到根得路径上得每个点都加$\frac{1}{len_i}$

最后查询一个点$u$的$\sum_{i \in S}\frac{dep_{lca(u,i)}}{len_i}$其实就是查询$u$到根所有点点权和

于是LCT维护之，都不用换根

LCT丑吗qwq

复杂度$O(nlogn)$
```cpp
#include <bits/stdc++.h>
#define rep(i,j,k) for(i=j;i<=k;++i)
#define dow(i,j,k) for(i=j;i>=k;--i)
#define LL long long
#define D_ double
#define sz(X) (int)(X.size())
#define itr iterator
#define mkp std::make_pair
#define pr std::pair
#define fi first
#define se second
const LL md=1e9+7;
inline LL fmul(LL x,LL y,const LL P){
    /*LL res=0;
    while(y){
        if(y&1)res+=x,res%=P;
        x+=x;x%=P;y>>=1;
    }
    return res;
    */
    //return (x*y-(LL)((long double)x/P*y)*P+P)%P;
    return (x*y)%P;
}
inline LL fpw(LL x,LL y,const LL modol){
    if(x==modol-1)return y&1 ? modol-1:1;
    LL res=1;while(y){if(y&1)res=fmul(res,x,modol);x=fmul(x,x,modol);y>>=1;}return res%modol;
}
LL exgcd(LL& x,LL& y,LL a,LL b){
    if(!b){x=1;y=0;return a;}
    LL res=exgcd(y,x,b,a%b);y-=x*(a/b);return res;
}
inline LL ad(LL x,LL y,const LL md){
    return x+y>=md ? x+y-md:x+y;
}
inline LL sub(LL x,LL y,const LL md){
    return x<y ? md+x-y:x-y;
}
inline LL inv(LL o,const LL modol){
    LL x,y;exgcd(x,y,o,modol);
    x=(x%modol+modol)%md;return x;
}
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
LL mmax(LL x,LL y){return x>y ? x:y;}
LL mmin(LL x,LL y){return x<y ? x:y;}
const int N=1e5+10;
int l[N],r[N],n;
struct edge{
	int nxt,to;
}e[N<<1];
int head[N],pos;
void add(int u,int v){e[++pos]=(edge){head[u],v};head[u]=pos;}
#define son(u,v) tr[u].ch[v]
#define fu(u) tr[u].f_
int stk[N],dep[N];
namespace lct{
	struct node{
		int ch[2],f_,siz;LL s,v,ts;
	}tr[N];
	void pushup(int u){
		tr[u].siz=tr[son(u,0)].siz+tr[son(u,1)].siz+1;
		tr[u].s=ad(ad(tr[son(u,0)].s,tr[son(u,1)].s,md),tr[u].v,md);
	}
	void fuck(int u,LL d){if(!u)return;
		tr[u].ts=ad(tr[u].ts,d,md);
		tr[u].v=ad(tr[u].v,d,md);
		tr[u].s=ad(tr[u].s,fmul(d,tr[u].siz,md),md);
	}
	void pushdown(int u){
		if(tr[u].ts){
			fuck(son(u,0),tr[u].ts);fuck(son(u,1),tr[u].ts);
			tr[u].ts=0;
		}
	}
	bool isrt(int u){return son(fu(u),0)!=u && son(fu(u),1)!=u;}
	int gt(int u){return son(fu(u),1)==u;}
	void rotate(int D){
		int B=fu(D),A=fu(B),w1=gt(D),w2=gt(B);
		if(!isrt(B))son(A,w2)=D;
		son(B,w1)=son(D,w1^1);fu(son(D,w1^1))=B;
		son(D,w1^1)=B;fu(B)=D;fu(D)=A;pushup(B);pushup(D);
	}
	void splay(int u){
		stk[0]=0;stk[++stk[0]]=u;
		for(int x=u;!isrt(x);x=fu(x))stk[++stk[0]]=fu(x);
		while(stk[0])pushdown(stk[stk[0]--]);
		for(int ft=fu(u);!isrt(u);rotate(u),ft=fu(u)){
			if(!isrt(ft))rotate(gt(ft)==gt(u) ? ft:u);
		}
		pushup(u);
	}
	void access(int u){
		for(int y=0;u;y=u,u=fu(u)){
			splay(u);son(u,1)=y;pushup(u);
		}
	}
}
void dfs(int u,int fa){
	int i;dep[u]=dep[fa]+1;
	for(i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		lct::fu(v)=u;dfs(v,u);
	}
}
std::vector<int>st[N],ed[N];
LL ans,pans,sd,sl;
void ad(int u){
	lct::access(u);lct::splay(u);
	LL sum=lct::tr[u].s;
	LL tmp=0;
	tmp=ad(sd,fmul(sl,dep[u],md),md);
	tmp=sub(tmp,fmul(2,sum,md),md);
	tmp=fmul(tmp,inv(r[u]-l[u]+1,md),md);
	pans=ad(pans,tmp,md);
	sd=ad(sd,fmul(dep[u],inv(r[u]-l[u]+1,md),md),md);
	sl=ad(sl,inv(r[u]-l[u]+1,md),md);
	tmp=inv(r[u]-l[u]+1,md);
	lct::fuck(u,tmp);
}
void del(int u){
	lct::access(u);lct::splay(u);
	sd=sub(sd,fmul(dep[u],inv(r[u]-l[u]+1,md),md),md);
	sl=sub(sl,inv(r[u]-l[u]+1,md),md);
	LL tmp=inv(r[u]-l[u]+1,md);
	lct::fuck(u,sub(0,tmp,md));
	tmp=0;
	LL sum=lct::tr[u].s;
	tmp=ad(sd,fmul(sl,dep[u],md),md);
	tmp=sub(tmp,fmul(2,sum,md),md);
	tmp=fmul(tmp,inv(r[u]-l[u]+1,md),md);
	pans=sub(pans,tmp,md);
}
int main(){//freopen("in.txt","r",stdin);
	int i;n=read();
	rep(i,1,n)l[i]=read(),r[i]=read();
	rep(i,2,n){
		int x,y;x=read();y=read();
		add(x,y);add(y,x);
	}
	dfs(1,0);
	rep(i,1,n)st[l[i]].push_back(i),ed[r[i]+1].push_back(i);
	std::vector<int>::itr it;
	rep(i,1,1e5){
		for(it=st[i].begin();it!=st[i].end();++it)ad(*it);
		for(it=ed[i].begin();it!=ed[i].end();++it)del(*it);
		ans=ad(ans,pans,md);
	}
	rep(i,1,n)ans=fmul(ans,r[i]-l[i]+1,md);
	std::cout<<ans;
}

```


---

## 作者：do_while_true (赞：2)

令 $len_i=r_i-l_i=1$，$all=\prod len_i$，如果一对点 $(x,y)$ 若都能染成颜色 $c$，则对答案贡献 $dis(x,y)\frac{all}{len_xlen_y}$．

对颜色编号维进行扫描线，现在问题就是每次将一个点染成黑色或者白色。求所有黑色点对 $(x,y)$ 的 $dis(x,y)\frac{all}{len_xlen_y}$ 之和。

上点分树，就把 $(dep_x+dep_y)\frac{all}{len_xlen_y}$ 拆成 $\frac{dep_xall}{len_x}\cdot \frac{1}{len_y}$ 和 $\frac{all}{len_x}\cdot \frac{dep_y}{len_y}$，对于每个分治中心统计其作为分治中心的连通块中黑点的 $\frac{1}{len_y}$ 和 $\frac{dep_y}{len_y}$ 的和即可。要去重所以还需要统计分治中心的各个子树内部的。

时间复杂度 $\mathcal{O}((n+r)\log n)$．

虽然是一只 log，但是常数好像特别大，也有可能是点分树写丑了。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<set>
#include<map>
#include<unordered_map>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=1000000007;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=100010;
int n;
int ans,sum;
int l[N],r[N],len[N],il[N],all=1,mxr;
int s1[N*3],s2[N*3],tot;
vi eg[N];
vpii vec[N];
int rt,rs,siz[N],mx[N],vis[N];
int fa[N];
unordered_map<int,int>dep[N],bl[N];
void getrt(int x,int fa){
	siz[x]=mx[x]=1;
	for(auto v:eg[x]){
		if(v==fa||vis[v])continue;
		getrt(v,x);
		siz[x]+=siz[v];
		cmax(mx[x],siz[v]);
	}
	cmax(mx[x],rs-siz[x]);
	if(mx[x]<mx[rt])rt=x;
}
void dfs1(int x,int fa,int t){
	dep[t][x]=dep[t][fa]+1;
	bl[t][x]=tot;
	for(auto v:eg[x])
		if(!vis[v]&&v!=fa)
			dfs1(v,x,t);
}
void dfz(int x){
	vis[x]=1;
	for(auto v:eg[x])if(!vis[v]){
		++tot;
		dfs1(v,x,x);
	}
	int tmp=rs;
	for(auto v:eg[x])if(!vis[v]){
		rs=siz[v]>siz[x]?tmp-siz[x]:siz[v];
		rt=0;
		getrt(v,x);
		fa[rt]=x;
		dfz(rt);
	}
}
void Ins(int x){
	int t=x;
	while(t){
		int p=bl[t][x];
		cadd(sum,1ll*dep[t][x]*il[x]%mod*all%mod*s1[t]%mod);
		cadd(sum,1ll*all*il[x]%mod*s2[t]%mod);
		//
		if(t!=x){
			cdel(sum,1ll*dep[t][x]*il[x]%mod*all%mod*s1[p]%mod);
			cdel(sum,1ll*all*il[x]%mod*s2[p]%mod);
		}
		//
		cadd(s1[t],il[x]);
		cadd(s2[t],1ll*dep[t][x]*il[x]%mod);
		if(t!=x){
			cadd(s1[p],il[x]);
			cadd(s2[p],1ll*dep[t][x]*il[x]%mod);
		}
		t=fa[t];
	}
}
void Del(int x){
	int t=x;
	while(t){
		int p=bl[t][x];
		cdel(s1[t],il[x]);
		cdel(s2[t],1ll*dep[t][x]*il[x]%mod);
		if(t!=x){
			cdel(s1[p],il[x]);
			cdel(s2[p],1ll*dep[t][x]*il[x]%mod);
		}
		//
		cdel(sum,1ll*dep[t][x]*il[x]%mod*all%mod*s1[t]%mod);
		cdel(sum,1ll*all*il[x]%mod*s2[t]%mod);
		//
		if(t!=x){
			cadd(sum,1ll*dep[t][x]*il[x]%mod*all%mod*s1[p]%mod);
			cadd(sum,1ll*all*il[x]%mod*s2[p]%mod);
		}
		t=fa[t];
	}
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n);
	for(int i=1;i<=n;i++){
		read(l[i],r[i]);cmax(mxr,r[i]);
		len[i]=r[i]-l[i]+1;
		all=1ll*all*len[i]%mod;
		il[i]=qpow(len[i],mod-2);
		vec[l[i]].pb(mp(i,1));
		vec[r[i]+1].pb(mp(i,-1));
	}
	for(int i=1,u,v;i<n;i++){
		read(u,v);
		eg[u].pb(v);eg[v].pb(u);
	}
	tot=n;
	mx[rt=0]=N;rs=n;
	getrt(1,0);
	dfz(rt);
	for(int o=1;o<=mxr;o++){
		for(auto i:vec[o])
			if(i.se==1)Ins(i.fi);
			else Del(i.fi);
		cadd(ans,sum);
	}
	cout << ans << '\n';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

[黄队](https://www.luogu.com.cn/user/443261#main)提出这道题可以使用线段树合并做到 $O(n \log n)$。而其实直接点分树就可以做到 $O(n \log n)$。

考虑答案实际上是

$$
\begin{aligned}
& \sum_{\text{all possible situations of } h_i} \sum_{i=1}^n \sum_{j=i+1}^n [h_i=h_j] \text{dis}(i,j) \\
=& \sum_{\text{all possible situations of } h_i} \sum_{i=1}^n \sum_{j=i+1}^n \sum_{H=1}^n [H=h_i][H=h_j] \text{dis}(i,j) \\
=& \sum_{H=1}^n \sum_{i=1}^n \sum_{j=i+1}^n \text{dis}(i,j) \sum_{\text{all possible situations of } h_i} [H=h_i][H=h_j] \\
=& \sum_{H=1}^n \sum_{i=1}^n \sum_{j=i+1}^n \text{dis}(i,j)\dfrac{[L_i \le H \le R_i][L_j \le H \le R_j] \prod_{k=1}^n (R_k-L_k+1)}{(R_i-L_i+1)(R_j-L_j+1)}
\end{aligned}
$$

这个式子看起来诡异，但实际上就是非常普通的拆贡献。

考虑扫描 $H$，动态维护 $S = \{u | L_u \le H \le R_u\}$。然后维护

$$
\sum_{u,v \in S,u<v} \frac{\text{dis}(u,v)}{(R_u-L_u+1)(R_v-L_v+1)}
$$

点分树随便维护一下就行。 /qq

复杂度 $O(n \log n)$，但是空间复杂度做不到线性。 /ll

话说我感觉这种做法用点分治反而不好维护。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MOD=1e9+7;
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int n,sum,L[MAXN],R[MAXN],mul=1,ans,sze[MAXN],mx[MAXN],cut[MAXN],val[MAXN],flg[MAXN];
vector<int> G[MAXN],ins[MAXN],del[MAXN];

int dis[MAXN][20],FA[MAXN],ddep[MAXN];
void dfs1(int u,int f) {
	sze[u]=1,mx[u]=0;
	for(auto v:G[u]) if(v!=f&&!flg[v]) dfs1(v,u),sze[u]+=sze[v],mx[u]=max(mx[u],sze[v]);
	return ;
}
int find_core(int u,int f,int al) {
	if(max(mx[u],al-sze[u])<=al/2) return u;
	for(auto v:G[u]) if(v!=f&&!flg[v]) {
		int ans=find_core(v,u,al);
		if(ans!=-1) return ans;	
	}
	return -1;
}
void dfs2(int u,int f,int dep) {
	if(f) dis[u][dep]=dis[f][dep]+1;
	for(auto v:G[u]) if(v!=f&&!flg[v]) dfs2(v,u,dep);
	return ;	
}
int solve(int u,int DEP) {
	dfs1(u,0),u=find_core(u,0,sze[u]),dfs2(u,0,DEP);
	ddep[u]=DEP,flg[u]=1;
	for(auto v:G[u]) if(!flg[v]) FA[solve(v,DEP+1)]=u;
	return u;
}
int s[MAXN][4];
void INS(int u) {
	int lst=0,ou=u;
	while(u) {
		sum=(sum+s[u][0]*val[ou])%MOD;
		sum=(sum+s[u][1]*val[ou]%MOD*dis[ou][ddep[u]])%MOD;
		if(lst) sum=(sum-s[lst][2]*val[ou])%MOD,sum=(sum-s[lst][3]*val[ou]%MOD*dis[ou][ddep[u]])%MOD;
		lst=u,u=FA[u];
	}
	lst=0,u=ou;
	while(u) {
		s[u][0]=(s[u][0]+dis[ou][ddep[u]]*val[ou])%MOD,s[u][1]=(s[u][1]+val[ou])%MOD;
		if(lst) s[lst][2]=(s[lst][2]+dis[ou][ddep[u]]*val[ou])%MOD,s[lst][3]=(s[lst][3]+val[ou])%MOD;
		lst=u,u=FA[u];
	}
	return ;
}
void DEL(int u) {
	int lst=0,ou=u;
	while(u) {
		s[u][0]=(s[u][0]-dis[ou][ddep[u]]*val[ou])%MOD,s[u][1]=(s[u][1]-val[ou])%MOD;
		if(lst) s[lst][2]=(s[lst][2]-dis[ou][ddep[u]]*val[ou])%MOD,s[lst][3]=(s[lst][3]-val[ou])%MOD;
		lst=u,u=FA[u];
	}
	lst=0,u=ou;
	while(u) {
		sum=(sum-s[u][0]*val[ou])%MOD;
		sum=(sum-s[u][1]*val[ou]%MOD*dis[ou][ddep[u]])%MOD;
		if(lst) sum=(sum+s[lst][2]*val[ou])%MOD,sum=(sum+s[lst][3]*val[ou]%MOD*dis[ou][ddep[u]])%MOD;
		lst=u,u=FA[u];
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>L[i]>>R[i],mul=mul*(R[i]-L[i]+1)%MOD,ins[L[i]].push_back(i),del[R[i]+1].push_back(i),val[i]=qpow(R[i]-L[i]+1,MOD-2);
	ffor(i,1,n-1) {
		int u,v;
		cin>>u>>v,G[u].push_back(v),G[v].push_back(u);	
	}
	solve(1,1);
	ffor(i,1,100000) {
		for(auto id:del[i]) DEL(id);
		for(auto id:ins[i]) INS(id);
		ans=(ans+sum)%MOD;	
	}
	cout<<(ans*mul%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Parsnip (赞：1)

提供另一种无脑点分的做法。

首先考虑一些简单的手法：

$$\sum_{ \large{ \forall t  \in [1,n]_{\mathbb N} ,c_t\in[l_t,r_t] } }\sum_{i=1}^n\sum_{j=i+1}^n \text{dis}(i,j)[c_i=c_j]$$
$$= \sum_{i=1}^n\sum_{j=i+1}^n\text{dis}(i,j)\sum_{ \large{ \forall t  \in [1,n]_{\mathbb N} ,c_t\in[l_t,r_t] } } [c_i=c_j]
$$

令$\mathbf I_i=[l_i,r_i]_{\mathbb N}$表示一个颜色区间，那么原式可以转化为：

$$
\sum_{i=1}^n\sum_{j=i+1}^n\text{dis}(i,j)\times  \frac{ \prod_{k=1}^n |\mathbf I_k| }{ |\mathbf{I}_i||\mathbf{I}_j| } \times \Bigg| \mathbf I_i\bigcap \mathbf I_j \Bigg|
$$
$$
= \left(\prod_{k=1}^n |\mathbf I_k|\right)\times  \sum_{i=1}^n\sum_{j=i+1}^n\text{dis}(i,j)\times  \frac{ \big| \mathbf I_i\bigcap \mathbf I_j \big| }{ |\mathbf{I}_i||\mathbf{I}_j| }
$$

考虑点分治，显然只需计算式子的后半部分，不妨设当前分治重心为$c$，那么后式即为：

$$
\Big (\mathrm{dis}(c,x)+\mathrm{dis}(c,y) \Big)\times  \frac{ \big| \mathbf I_x\bigcap \mathbf I_y \big| }{ |\mathbf{I}_x||\mathbf{I}_y| }
$$
$$
= \frac{1}{|\mathbf I_x|}\left (\mathrm{dis}(c,x)\times  \frac{ \big| \mathbf I_x\bigcap \mathbf I_y \big| }{ |\mathbf{I}_y| } +\mathrm{dis}(c,y)\times  \frac{ \big| \mathbf I_x\bigcap \mathbf I_y \big| }{ |\mathbf{I}_y| } \right)
$$

这时候可以把区间交$|\mathbf I_x\cap\mathbf I_y|$放到数据结构里面来处理，也就是说，我们只需考虑其他部分的贡献，这个系数就就让区间数据结构自动累加上。

具体地，维护两颗树状数组$T_1,T_2$，$T_1$**以区间为下标** 保存 已加入的子树 **中所有点$y$的$|\mathbf I_y|^{-1}$之和**，$T_2$**以区间为下标** 保存 已加入的子树 **中所有点$y$的$\mathrm{dis}(c,y)\times |\mathbf I_y|^{-1}$之和**。根据点分的思路，我们在加入一棵子树前 先计算子树内每一个点 与 前面子树点 的贡献，只需在树状数组内区间查询即可得到贡献。

主要代码如下：

```cpp
struct BinaryIndexedTree {
	modint c1[N], c2[N]; int n; BinaryIndexedTree(int _n = 0) { n = _n; }
	inline int Lowbit(int x) { return x & (-x); }
	inline void Modify(int p,modint v) { for (int i = p; i <= n; i += Lowbit(i)) c1[i] += v, c2[i] += modint(p) * v; }
	inline void Modify(int l,int r,modint v) { Modify( l, v ), Modify( r+1, modint( mod - v.x ) ); }
	inline modint Query(int p) { modint s(0); for (int i = p; i; i -= Lowbit(i)) s += modint(p+1) * c1[i] - c2[i]; return s; }
	inline modint Query(int l,int r) { return Query(r) - Query(l-1); }
} T1, T2;

int n, t, Head[N], l[N], r[N], Max; modint Ans, Inv[N];
int dep[N], flag[N], sz[N], g[N], rt, tot;

inline void Insert(int x,int y) { e[++t] = (Edge) { y, Head[x] }, Head[x] = t; }

inline void Findroot(int x,int Fa) { 
	sz[x] = 1, g[x] = 0;
	for (int i = Head[x], y; i; i = e[i].next)
		if ( !flag[ y = e[i].ver ] && y != Fa ) 
			Findroot(y,x), sz[x] += sz[y], g[x] = max( g[x], sz[y] );
	g[x] = max( g[x], tot - sz[x] ), ( g[x] >= g[rt] ?: rt = x );
}

inline void Modify(int x,int Fa,modint op) {
	modint _Inv = Inv[ r[x] - l[x] + 1 ];
	T1.Modify( l[x], r[x], _Inv * op );
	T2.Modify( l[x], r[x], _Inv * op * modint(dep[x]) );
	for (int i = Head[x], y; i; i = e[i].next)
		if ( !flag[ y = e[i].ver ] && y != Fa ) Modify(y,x,op);
}

inline void Calc(int x,int Fa) {
	modint val = T1.Query(l[x],r[x]) * modint(dep[x]) + T2.Query(l[x],r[x]);
	Ans = Ans + val * Inv[ r[x] - l[x] + 1 ];
	for (int i = Head[x], y; i; i = e[i].next)
		if ( !flag[ y = e[i].ver ] && y != Fa ) Calc(y,x);
}

inline int Inter(int l1,int r1,int l2,int r2) { return max( min(r1,r2) - max(l1,l2) + 1, 0 ); }

inline void Dfs(int x,int Fa,int rt) {
	dep[x] = dep[Fa] + 1;
	modint val = modint(Inter(l[x],r[x],l[rt],r[rt])) * modint(dep[x]);
	Ans += val * Inv[ r[x] - l[x] + 1 ] * Inv[ r[rt] - l[rt] + 1 ];
	for (int i = Head[x], y; i; i = e[i].next)
		if ( !flag[ y = e[i].ver ] && y != Fa ) Dfs(y,x,rt);
}

inline void Divide(int x) {
	flag[x] = true, dep[0] = -1, Dfs(x,0,x);
	for (int i = Head[x], y; i; i = e[i].next)
		if ( !flag[ y = e[i].ver ] ) Calc(y,x), Modify(y,x,modint(1));
	for (int i = Head[x], y; i; i = e[i].next)
		if ( !flag[ y = e[i].ver ] ) Modify(y,x,modint(mod-1));
	for (int i = Head[x], y; i; i = e[i].next)
		if ( !flag[ y = e[i].ver ] ) 
			tot = sz[y], rt = 0, Findroot(y,0), Divide(rt);
}

int main(void) {
	scanf( "%d", &n );
	for (int i = 1; i <= n; i++) 
		scanf( "%d%d", &l[i], &r[i] ), Max = max( Max, r[i] );
	Inv[1] = modint(1);
	for (int i = 2; i <= Max; i++) 
		Inv[i] = modint( mod - mod/i ) * Inv[mod%i];
	T1 = T2 = BinaryIndexedTree(Max);
	for (int i = 1, u, v; i < n; i++)
		scanf( "%d%d", &u, &v ), Insert(u,v), Insert(v,u);
	g[ rt = 0 ] = 1e9, tot = n, Findroot(1,0), Divide(rt);
	for (int i = 1; i <= n; i++) Ans = Ans * modint(r[i]-l[i]+1);
	return printf( "%d\n", Ans.x ) * 0; 
}
```



---

## 作者：cosf (赞：0)

由题意，我们可以枚举每一对点对 $i, j$ 的贡献。但由于每个 $i$ 都有不同的 $L_i, R_i$，所以直接枚举不太好做。因此我们可以枚举 $c = h_i$。

具体地，令 $S_c = \{i | c \in [L_i, R_i]\}$，$s_i = R_i - L_i + 1$，以及 $d_i$ 为 $i$ 在树上的深度，则答案可以表示为：

$$
\left(\prod s_i\right)\left(\sum_{c=1}^{10^5}\sum_{i, j \in S_c, i \lt j}\frac{\mathit{dis}(i, j)}{s_is_j}\right)
$$

我们从小到大枚举 $c$，并计算当前新加的和删去的 $i$ 对答案的贡献是什么。我们只需要计算最右边的 $\sum$ 的变化量即可。也就是在 $i$ 加入 $S_c$ 前：

$$
\begin{aligned}
\Delta &= \sum_{j \in S_c}\frac{\mathit{dis}(i, j)}{s_is_j}\\
&= \frac{1}{s_i}\sum_{j \in S_c}\frac{d_i + d_j - 2d_{\text{LCA}(i, j)}}{s_j}\\
s_i\Delta &= d_i\sum_{j \in S_c}\frac{1}{s_j} + \sum_{j \in S_c}\frac{d_j}{s_j} - 2\sum_{j \in S_c}\frac{d_{\text{LCA}(i, j)}}{s_j}
\end{aligned}
$$

前面两个 $\sum$ 和 $i$ 无关，可以直接计算。最后一个我们可以采用一个 trick。在加入 $j$ 时，我们可以给 $j$ 到根的路径上的点全部加上 $\frac{1}{s_j}$，然后我们查询 $i$ 到根路径的点权和，就是 $\sum_{j \in S_c}\frac{d_{\text{LCA}(i, j)}}{s_j}$ 了。

这个 trick 同时存在于[旧词](https://www.luogu.com.cn/problem/P5305)和 [LCA](https://www.luogu.com.cn/problem/P4211)。

删除点就反过来做一遍就可以了。

在实现中把所有 $s_i$ 取成其倒数更好写。

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100005
#define MOD 1000000007ll

using ll = long long;

ll pow(ll b, ll p, ll m)
{
    ll r = 1;
    while (p)
    {
        if (p & 1)
        {
            r = r * b % m;
        }
        b = b * b % m;
        p >>= 1;
    }
    return r;
}

int n;

vector<int> ad[MAXN], dl[MAXN];

ll s[MAXN];

vector<int> e[MAXN];

int sz[MAXN], son[MAXN], fa[MAXN], dep[MAXN];
int top[MAXN], dfn[MAXN], idx = 0;

void dfs1(int p, int f)
{
    sz[p] = 1;
    dep[p] = dep[f] + 1;
    fa[p] = f;
    for (int u : e[p])
    {
        if (u == f)
        {
            continue;
        }
        dfs1(u, p);
        sz[p] += sz[u];
        if (sz[u] > sz[son[p]])
        {
            son[p] = u;
        }
    }
}

void dfs2(int p, int t)
{
    top[p] = t;
    dfn[p] = ++idx;
    if (!son[p])
    {
        return;
    }
    dfs2(son[p], t);
    for (int u : e[p])
    {
        if (u == fa[p] || u == son[p])
        {
            continue;
        }
        dfs2(u, u);
    }
}

ll sd = 0, ss = 0, sr = 0;

struct Tree
{
    ll s, t;
} t[MAXN << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)

void pushup(int p)
{
    t[p].s = t[ls].s + t[rs].s;
}

void pushdown(int p, int l, int r)
{
    if (t[p].t)
    {
        int mid = (l + r) >> 1;
        (t[ls].s += t[p].t * (mid - l + 1)) %= MOD;
        (t[ls].t += t[p].t) %= MOD;
        (t[rs].s += t[p].t * (r - mid)) %= MOD;
        (t[rs].t += t[p].t) %= MOD;
        t[p].t = 0;
    }
}

void add(int p, int l, int r, int ql, int qr, ll v)
{
    if (ql <= l && r <= qr)
    {
        (t[p].s += (r - l + 1) * v) %= MOD;
        (t[p].t += v) %= MOD;
        return;
    }
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (mid >= ql)
    {
        add(ls, l, mid, ql, qr, v);
    }
    if (mid < qr)
    {
        add(rs, mid + 1, r, ql, qr, v);
    }
    pushup(p);
}

ll query(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
    {
        return t[p].s;
    }
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (mid >= ql)
    {
        (res += query(ls, l, mid, ql, qr)) %= MOD;
    }
    if (mid < qr)
    {
        (res += query(rs, mid + 1, r, ql, qr)) %= MOD;
    }
    return res;
}

void add(int u, ll v)
{
    while (true)
    {
        add(1, 1, n, dfn[top[u]], dfn[u], v);
        if (fa[top[u]] == top[u])
        {
            break;
        }
        u = fa[top[u]];
    }
}

ll query(int u)
{
    ll res = 0;
    while (true)
    {
        (res += query(1, 1, n, dfn[top[u]], dfn[u])) %= MOD;
        if (fa[top[u]] == top[u])
        {
            break;
        }
        u = fa[top[u]];
    }
    return res;
}

int main()
{
    cin >> n;
    ll mul = 1, res = 0;
    for (int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        (mul *= (r - l + 1)) %= MOD;
        s[i] = pow(r - l + 1, MOD - 2, MOD);
        ad[l].push_back(i);
        dl[r + 1].push_back(i);
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1, 1);
    dfs2(1, 1);
    for (int i = 1; i < MAXN; i++)
    {
        for (int u : dl[i])
        {
            (sd -= dep[u] * s[u] % MOD - MOD) %= MOD;
            (ss -= s[u] - MOD) %= MOD;
            add(u, MOD - s[u]);
            (sr -= s[u] * ((sd + dep[u] * ss % MOD - 2 * query(u) % MOD + MOD) % MOD) % MOD) % MOD;
            (sr += MOD) %= MOD;
        }
        for (int u : ad[i])
        {
            (sr += (sd + dep[u] * ss % MOD - 2 * query(u) % MOD + MOD) % MOD * s[u] % MOD) %= MOD;
            (sd += dep[u] * s[u] % MOD) %= MOD;
            (ss += s[u]) %= MOD;
            add(u, s[u]);
        }
        (res += sr) %= MOD;
    }
    cout << res * mul % MOD << endl;
    return 0;
}

```

---

## 作者：ifffer_2137 (赞：0)

### 题意
给定一棵 $n$ 个点的树，每个点可选的颜色区间为 $[l_i,r_i]$。对于所有染色方案，求出：
$$\sum_{1\le u<v\le n}[\text{col}_u\ne\text{col}_v]\text{dis}_{u,v}$$
的总和，对 $10^9+7$ 取模。
### 分析
这种题一般算贡献。

树上点对的贡献，先套个点分看看效果，发现效果很好。

于是推一下细节，设 $\text{dep}_i$ 表示 $i$ 到当前分治中心的距离，$\text{C}_i$ 表示 $i$ 的颜色集合，则对于点对 $u,v$，贡献为：
$$(\text{dep}_u+\text{dep}_v)\frac{\prod_{i=1}^n|\text{C}_i|}{|\text{C}_u||\text{C}_v|}|\text{C}_u\cap\text{C}_v|$$
把那个 $\prod$ 拿掉最后再一起乘，现在要处理的东西只跟 $u,v$ 有关。再拆一下柿子，把括号里乘出来，假设我们当前遍历到 $u$，所以只用看：
$$\text{dep}_u\frac{|\text{C}_u\cap\text{C}_v|}{|\text{C}_u||\text{C}_v|}$$
只跟 $u$ 有关的不用管，只要算其他所有子树里的 $v$ 的贡献和即可。

这个时候我们要维护带权线段交之和，可以上点 ds 了。
观察到值域很小，所以把线段拍到权值 sgt 上，每次插入一条线段给 $[l_i,r_i]$ 加上 $\frac{1}{r_i-l_i+1}$，这样算贡献的时候区间求和即可。由于常数原因这里选择使用强化版 BIT 维护区间加区间求和。

然后就做完了。点分时候算贡献可以先把所有子树加进去，然后遍历每棵子树，把自己的线段删掉，算完贡献再把自己的加回去。注意还要加上和分治中心产生的贡献。时间复杂度 $O(n\log n\log V)$。
### 代码
由于这题比较卡常所以代码会写的有点唐诗。关于 `#define int long long` 它似了。

```cpp
//From: ifffer_2137
#pragma GCC("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
constexpr int maxn=1e5+5;
constexpr int N=1e5;
constexpr int mod=1e9+7;
constexpr int inv2=5e8+4;
inline int pw(int a,int x){
	int s=1;
	while(x){
		if(x&1) s=1ll*s*a%mod;
		a=1ll*a*a%mod; x>>=1;
	}
	return s;
}
class Fenwick_Tree{
public:
	int c[2][maxn];
	inline int lowbit(int x){return x&(-x);}
	inline void update(int x,int k){
		int t=1ll*x*k%mod;
		while(x<=N){
			c[0][x]+=k;
			c[1][x]+=t;
			if(c[0][x]>=mod) c[0][x]-=mod;
			if(c[1][x]>=mod) c[1][x]-=mod;
			x+=lowbit(x);
		}
	}
	inline int query(int x){
		int s0=0,s1=0,t=x;
		while(x){
			s0+=c[0][x];if(s0>=mod) s0-=mod;
			s1+=c[1][x];if(s1>=mod) s1-=mod;
			x-=lowbit(x);
		}
		return (1ll*s0*(t+1)-s1+mod)%mod;
	}
	inline void add(int l,int r,int k){
		update(l,k),update(r+1,mod-k);
	}
	inline int getsum(int l,int r){
		int res=query(r)-query(l-1)+mod;
		if(res>=mod) res-=mod; return res;
	}
}tr;
int n;
ll M,ans;
pii c[maxn];
int inv[maxn];
inline int Cap(int x,int y){return max(0,min(c[x].sec,c[y].sec)-max(c[x].fir,c[y].fir)+1);}
vector<int> T[maxn];
int vis[maxn],siz[maxn],mx[maxn];
int cg,tot;
inline void getcg(int u,int f){
	siz[u]=1,mx[u]=0;
	for(int v:T[u]){
		if(v==f||vis[v]) continue;
		getcg(v,u);
		siz[u]+=siz[v];
		mx[u]=max(mx[u],siz[v]);
	}
	mx[u]=max(mx[u],tot-siz[u]);
	if(!cg||mx[u]<mx[cg]) cg=u;
}
inline void calc(int u,int f,int d){
	ans+=1ll*d*inv[u]%mod*inv[cg]%mod*Cap(u,cg)%mod;
	ans+=1ll*d*inv[u]%mod*tr.getsum(c[u].fir,c[u].sec)%mod;
	ans%=mod;
	for(int v:T[u]){
		if(v==f||vis[v]) continue;
		calc(v,u,d+1);
	}
}
inline void upt(int u,int f,int op){
	tr.add(c[u].fir,c[u].sec,(op?inv[u]:mod-inv[u]));
	for(int v:T[u]){
		if(v==f||vis[v]) continue;
		upt(v,u,op);
	}
}
inline void solve(int u,int m){
	tot=m,cg=0;
	getcg(u,0);
	vis[cg]=1;
	for(int v:T[cg]){
		if(vis[v]) continue;
		upt(v,cg,1);
	}
	for(int v:T[cg]){
		if(vis[v]) continue;
		upt(v,cg,0),calc(v,cg,1),upt(v,cg,1);
	}
	for(int v:T[cg]){
		if(vis[v]) continue;
		upt(v,cg,0);
	}
	for(int v:T[cg]){
		if(vis[v]) continue;
		solve(v,m-mx[v]);
	}
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read();M=1;
	for(int i=1;i<=n;i++){
		c[i].fir=read(),c[i].sec=read();
		M=1ll*M*(c[i].sec-c[i].fir+1)%mod;
		inv[i]=pw(c[i].sec-c[i].fir+1,mod-2);
	}
	for(int i=1,u,v;i<n;i++){
		u=read(),v=read();
		T[u].eb(v),T[v].eb(u);
	}
	solve(1,n);
	ans=1ll*ans*M%mod;
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：不知名用户 (赞：0)

题意：给定一棵树和每个点的颜色可取范围，求 所有涂色方案中两个相同颜色点距离之和 之和。模 $10^9+7$，树大小和颜色范围都是 $10^5$。

把贡献摊到每个颜色 $c$ 上，一对 $l_x\le c\le r_x,l_y\le c\le r_y,x<y$ 的 $(x,y)$ 对答案的贡献（在颜色 $c$ 下）是 $dep_x+dep_y-2dep_{LCA(x,y)}$？不对，还要考虑其它点选的颜色，所以要乘上 $\frac{\prod\limits_{i=1}^n(r_i-l_i+1)}{(r_x-l_x+1)(r_y-l_y+1)}$。为方便，以下令 $g_x=r_x-l_x+1,p=\prod\limits_{i=1}^ng_i$。

于是：

$$\frac{answer}{p}=\sum\limits_{c=1}^{maxR}\sum\limits_{l_x\le c\le r_x,l_y\le c\le r_y,x<y}\frac{dep_x+dep_y-2dep_{LCA(x,y)}}{g_xg_y}$$

摊到每个 $c$ 分别计算，令 $S$ 表示 $l_x\le c\le r_x$ 的所有 $x$ 的集合。我们要算的是这个式子（先不考虑 $LCA$ 部分，处理 $LCA$ 后面会写到）：

$$\sum\limits_{x\in S,y\in S,x<y}\frac{dep_x+dep_y}{g_xg_y}$$

根据乘法分配律，可以把两项拆开：

$$\sum\limits_{x\in S,y\in S,x<y}\frac{dep_x}{g_xg_y}+\sum\limits_{x\in S,y\in S,x<y}\frac{dep_y}{g_xg_y}$$

然后发现 $x,y$ 是对称的，我们可以把 $x<y$ 去掉，同时减去相等的：

$$\sum\limits_{x\in S,y\in S}\frac{dep_x}{g_xg_y}-\sum\limits_{x\in S}\frac{dep_x}{g_x^2}$$

发现减号左边的式子可以拆成只关于 $x$ 或 $y$ 的乘积：

$$\sum\limits_{x\in S}(\frac{dep_x}{g_x}\sum_{y\in S}\frac{1}{g_y})=(\sum\limits_{x\in S}\frac{dep_x}{g_x})(\sum_{y\in S}\frac{1}{g_y})$$

于是对于统计最终不计 $LCA$ 的只用维护 $a_1=\sum\limits_{x\in S}\frac{dep_x}{g_x},a_2=\sum\limits_{x\in S}\frac{1}{g_x},a_3=\sum\limits_{x\in S}\frac{dep_x}{g_x^2}$ 即可（`a1,a2,a3` 是我代码变量名，方便理解所以写在这里）。

对于 $LCA$ 的部分，还是摊到每个颜色 $c$，原式省去一些系数：

$$a_4=\sum\limits_{x\in S,y\in S,x<y}\frac{dep_{LCA(x,y)}}{g_xg_y}$$

处理 $dep$ 和 [[LNOI2014] LCA](https://www.luogu.com.cn/problem/P4211) 有点像。（我的代码里令 $dep_{root}=1$）每次插入 $x$ 时，把 $x$ 到根的路径**点**权加上 $\frac{1}{g_x}$，操作之前还需要把 $x$ 到根的路径点权和乘上 $\frac{1}{g_x}$ 累加到 $a_4$ 上。用树剖维护即可，具体见 [[LNOI2014] LCA](https://www.luogu.com.cn/problem/P4211)。

最后，对于每种颜色，我们已经知道了 $a_1,a_2,a_3,a_4$，把 $a_1a_2-a_3-2a_4$ 累加到 $answer$ 即可，注意最后 $answer$ 要乘上 $p$。[AC code。](https://codeforces.com/contest/1260/submission/247693701)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;

vector<int>gg[N],ad[N],de[N];
int g[N], dep[N], fa[N], sz[N], son[N], rk[N], id[N], cur, top[N];
int n, inv[N], a1, a2, a3, a4;
int c1[N], c2[N];
inline void add(int a, int b){
for(int i=a;i<=n;i+=(i&-i))c1[i]=(c1[i]+b)%mod,c2[i]=(c2[i]+b*a)%mod;}
inline void add(int a, int b, int c){add(a,c),add(b+1,-c);}
inline int ask(int a){int b=0;for(int i=a;i;i-=(i&-i))b=(b+c1[i]*(a+1)-c2[i])%mod;return b;}
inline int ask(int a, int b){return (ask(b)-ask(a-1))%mod;}

void dfs1(int x, int f)
{
	fa[x] = f, dep[x] = dep[f] + 1, sz[x] = 1;
	for(auto j:gg[x]) if(j!=f)
	{
		dfs1(j,x);
		sz[x] += sz[j];
		if(sz[j]>sz[son[x]]) son[x] = j;
	}
}
void dfs2(int x, int t)
{
	top[x] = t, rk[id[x]=++cur] = x;
	if(son[x]) dfs2(son[x],t);
	for(auto j:gg[x]) if(j!=fa[x]&&j!=son[x]) dfs2(j,j);
}

inline void Add(int a, int b){while(a) add(id[top[a]],id[a],b), a = fa[top[a]];}
inline int Ask(int a){int b=0;while(a) b=(b+ask(id[top[a]],id[a]))%mod, a = fa[top[a]];return b;}

void ins(int x)
{
	a1 = (a1 + dep[x] * inv[g[x]]) % mod;
	a2 = (a2 + inv[g[x]]) % mod;
	a3 = (a3 + dep[x] * inv[g[x]] % mod * inv[g[x]]) % mod;
	a4 = (a4 + Ask(x) * inv[g[x]]) % mod;
	Add(x,inv[g[x]]);
}
void del(int x)
{
	a1 = (a1 - dep[x] * inv[g[x]]) % mod;
	a2 = (a2 - inv[g[x]]) % mod;
	a3 = (a3 - dep[x] * inv[g[x]] % mod * inv[g[x]]) % mod;
	Add(x,-inv[g[x]]);
	a4 = (a4 - Ask(x) * inv[g[x]]) % mod;
}

signed main()
{
	int i, a, b, c, ans = 0, p = 1;
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a>>b, ad[a].emplace_back(i), de[b+1].emplace_back(i), g[i] = b - a + 1, p = p * g[i] % mod;
	for(i=1;i<n;i++) cin>>a>>b, gg[a].emplace_back(b), gg[b].emplace_back(a);
	inv[1] = 1;for(i=2;i<=N-10;i++) inv[i] = (mod - mod / i) * inv[mod%i] % mod;
	dfs1(1,0), dfs2(1,1);
	for(c=1;c<=N-10;c++)
	{
		for(auto i:de[c]) del(i);
		for(auto i:ad[c])
			ins(i);
		ans = (ans + a1 * a2 - a3 - a4 * 2 + mod) % mod;
	}
	cout<<(ans*p%mod+mod)%mod;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

首先为了方便我们求和转期望。令 $len_i=R_i-L_i+1$。

一个简单的想法是对于所有点对 $(i,j)$，求出他们的 $dis(i,j)$ 以及 $L_i,R_i$ 与 $L_j,R_j$ 重叠的长度，这个是可以 $O(n^2)$ 解决的。

考虑对于每种颜色分别计算 $(i,j)$ 的贡献，并让 $(i,j)$ 在 $lca$ 处被计算。假设目前考虑颜色 $k$，他们的距离就是 $dep_i+dep_j-2dep_{lca}$，如果 $i,j$ 的区间都包含 $k$ 的话他们给答案的贡献就是 $\frac{dep_i+dep_j-2dep_{lca}}{len_ilen_j}$。

考虑让 $i,j$ 依次加入时，如何计算。先枚举的需要在所有 $L_i\sim R_i$ 区间打下一个 $\frac{dep_i}{len_i}$ 的 $tag$ 才能让后者枚举 $h_j$ 时计算出 $\frac{dep_i}{len_ilen_j}$；需要在所有 $L_i\sim R_i$ 区间打下一个 $\frac{1}{len_i}$ 的 $tag$ 才能让后者枚举 $h_j$ 时计算出 $\frac{dep_j-2dep_{lca}}{len_ilen_j}$。

由于我们打 $tag$ 的区间是连续的，所以显然不用再去枚举每一个颜色，而是线段树上做即可。

如果对于每个 $lca$ 都暴力重新加入其子树内的所有点，复杂度是 $O(n^2\log n)$ 的，然而我们可以使用树上启发式合并优化，复杂度为 $O(n\log^2n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
struct sgt{
	int f[400005],lzt[400005];
	void add(int i,int l,int r,int val){
		(f[i]+=val*(r-l+1))%=mod;
		(lzt[i]+=val)%=mod;
	} 
	void pushdown(int i,int l,int r){
		add(i*2,l,mid,lzt[i]);
		add(i*2+1,mid+1,r,lzt[i]);
		lzt[i]=0;
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr) return add(i,l,r,cg),void();
		pushdown(i,l,r);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=(f[i*2]+f[i*2+1])%mod;
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		pushdown(i,l,r);
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return (qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr))%mod;
	}
}tree1,tree2;
vector<int> vc[100005];
int l[100005],r[100005],inv[100005],hson[100005],siz[100005],dep[100005],qdep,ans;
void dfs1(int now,int fa){
	siz[now]=1;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dep[v]=dep[now]+1;
		dfs1(v,now);
		hson[now]=(siz[v]>siz[hson[now]])?v:hson[now];
		siz[now]+=siz[v];
	} 
}
void dfs2(int now,int fa){
	(ans+=inv[now]*tree2.qry(1,1,100000,l[now],r[now])+mod-inv[now]*tree1.qry(1,1,100000,l[now],r[now])%mod*qdep%mod)%=mod;
	(ans+=inv[now]*tree1.qry(1,1,100000,l[now],r[now])%mod*(dep[now]-qdep))%=mod;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs2(v,now);
	}
}
void dfs3(int now,int fa){
	tree1.change(1,1,100000,l[now],r[now],inv[now]);
	tree2.change(1,1,100000,l[now],r[now],inv[now]*dep[now]%mod);
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs3(v,now);
	}
}
void dfs4(int now,int fa){
	tree1.change(1,1,100000,l[now],r[now],mod-inv[now]);
	tree2.change(1,1,100000,l[now],r[now],mod-inv[now]*dep[now]%mod);
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs4(v,now);
	}
}
void dfs5(int now,int fa,int kep){
	for(auto v:vc[now]) if(v!=fa&&v!=hson[now]) dfs5(v,now,0);
	if(hson[now]) dfs5(hson[now],now,1);
	qdep=dep[now];
	(ans+=inv[now]*tree2.qry(1,1,100000,l[now],r[now])+mod-inv[now]*tree1.qry(1,1,100000,l[now],r[now])%mod*qdep%mod)%=mod;
	tree1.change(1,1,100000,l[now],r[now],inv[now]);
	tree2.change(1,1,100000,l[now],r[now],inv[now]*dep[now]%mod);
	for(auto v:vc[now]) if(v!=fa&&v!=hson[now]) dfs2(v,now),dfs3(v,now);
	if(!kep) dfs4(now,fa);
}
signed main(){
	int n,tot=1; cin>>n;
	for(int i=1;i<=n;i++) cin>>l[i]>>r[i],inv[i]=qp(r[i]-l[i]+1,mod-2),(tot*=(r[i]-l[i]+1))%=mod;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	} 
	dfs1(1,0);
	dfs5(1,0,0);
	cout<<ans*tot%mod;
	return 0;
}

```

---

