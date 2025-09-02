# Tree Queries

## 题目描述

You are given a tree consisting of $ n $ vertices (numbered from $ 1 $ to $ n $ ). Initially all vertices are white. You have to process $ q $ queries of two different types:

1. $ 1 $ $ x $ — change the color of vertex $ x $ to black. It is guaranteed that the first query will be of this type.
2. $ 2 $ $ x $ — for the vertex $ x $ , find the minimum index $ y $ such that the vertex with index $ y $ belongs to the simple path from $ x $ to some black vertex (a simple path never visits any vertex more than once).

For each query of type $ 2 $ print the answer to it.

Note that the queries are given in modified way.

## 样例 #1

### 输入

```
4 6
1 2
2 3
3 4
1 2
1 2
2 2
1 3
2 2
2 2
```

### 输出

```
3
2
1
```

# 题解

## 作者：decoqwq (赞：11)

首先将第一次修改的黑点抓出来，作为树根，然后我们 $\text{dfs}$ 一遍这棵树，记 $a[i]$ 代表第 $i$ 个点到根节点路径上最小的编号

之后对于每一次修改，显然对于修改点的子树里的点的答案是不会有变化的，如果不在子树内，那么第 $j$ 个点的答案就要与修改点到根路径的最小编号取 $\min$，所以在每次修改后记录一个所有黑点最小的到根路径上的最小编号，对于每次查询只需要将这个值与本身这个点到根路径上最小值取 $\min$ 即可

同时说一下正确性

对于不在根的同一棵子树内的两点 $(x,y)$ ，若 $y$ 是黑点，则这条路径上最小值显然是根到 $x$ 最小值与根到 $y$ 最小值中的最小值，多个取并即可，如果在同一棵子树内，那答案的并就是 $x,y$ 中较深的那一个到根的路径上最小值，同样是两个最小值中的最小值，所以查询就转化为了很多条到根的链最小值的最小值，每次取 $\min$ 就是答案

---

## 作者：Yuby (赞：10)

[题面](https://www.luogu.com.cn/problem/CF825G)

点数：2500

## 题意

给定一颗有 $n\leq 10^6$ 个节点的树，初始所有节点为白色，有 $q\leq 10^6$ 个操作，分为两种。第一种操作为输入 $x$，表示将节点 $x$ 改为黑色。第二种操作输入 $x$，查询 $x$ 到任何黑色节点的简单路径上的节点的编号最小值。保证第一次操作是第一种操作。

## 分析

个人感觉思路很清新。

不妨将第一个被染黑的节点设为根节点，记录 $a_i$ 表示 $i$ 到根的路径上的节点的编号最小值，$col_i$ 表示节点 $i$ 的颜色，$col_i=1$ 表示为黑色，另一种为白色。记录当前 $ans=\min\limits_{col_u=1} a_u$。如当前查询点 $x$，答案即为 $\min(ans,a_x)$。

### 证明

不妨设 $v$ 为某个黑色节点，$x$ 为当前查询的节点。答案对所有可能的 $v$ 取最小即可。

1.如果 $x$ 到 $v$ 的路径要经过根节点，那么可以将路径拆分为 $x$ 到根，$v$ 到根，答案即为 $\min(a_x,a_v)$。

2.如果 $x$ 到 $v$ 的路径上不经过根节点，那么必有一个黑色节点 $u$ 使得 $x$ 到 $u$ 的路径要经过根节点，转为第一种情况。因为根节点是黑色的，所以取 $u$ 到根即可。若 $v$ 在 $x$ 的子树内，$v$ 到 $x$ 的路径可以表示为 $v$ 到根去掉 $x$ 到根，但前面已经证明 $x$ 到根必然要计入，所以答案仍然可以为 $\min(a_x,a_v)$。若 $x$ 在 $v$ 的子树内，$x$ 到 $v$ 的路径变为 $x$ 到根去掉 $v$ 到根，但 $x$ 到根必然可以取，所以答案也是 $\min(a_x,a_v)$。

证毕。

第一次输入黑色节点的时候，以他为根，进行一次 dfs 处理出所有的 $a_i$，每次修改更新 $ans$ 即可。

复杂度：$O(n+q)$。

核心代码：

```cpp
const ll MAXN=1e6+7;
ll n,q,a[MAXN];
vector<ll>tree[MAXN];
void dfs(ll u,ll fa)
{
	for(ll i=0;i<tree[u].size();i++)
	{
		ll v=tree[u][i];
		if(v==fa)continue;
		a[v]=min(a[u],v);
		dfs(v,u);
	}
}
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read(),q=read();
    for(ll i=1;i<n;i++)
    {
    	ll u=read(),v=read();
    	tree[u].push_back(v);
    	tree[v].push_back(u);
	}
    bool f=0;
    ll ans=INF,las=0;
    while(q--)
    {
    	ll op=read(),x=(read()+las)%n+1;
    	if(op==1)
    	{
    		if(!f)a[x]=x,dfs(x,0);
    		f=1;
    		ans=min(ans,a[x]);
		}
		else
		{
			las=min(ans,a[x]);
			write(las),pc(10);
		}
	}
	return 0;
}
```



---

## 作者：do_while_true (赞：4)

点权转边权，把边权设为两个端点的 $\min$，然后发现询问 $x$ 的答案，就是询问 $x$ 与所有黑点的虚树，边权的 $\min$ 是多少。假设要判定答案是否 $\geq k$，那么就是询问 $x$ 只经过 $\geq k$ 是否能到达所有黑点，于是想到建立 Kruskal 重构树，那么 $x$ 与所有黑点的 LCA 的权值即为答案。时间复杂度为 $\mathcal{O}(n+q\log n)$．

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
#define DE(fmt,...) fprintf(stderr, "Line %d : " fmt "\n",__LINE__,##__VA_ARGS__)
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
typedef vector<pll>vpll;
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
const int N=2000010;
int n,m;
struct Edge{
	int x,y,w;
}e[N];
vi eg[N];
int tot,val[N],fa[N];
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
int dep[N],top[N],pa[N],son[N],siz[N];
void dfs1(int x){
	siz[x]=1;
	for(auto v:eg[x]){
		dep[v]=dep[x]+1;pa[v]=x;
		dfs1(v);siz[x]+=siz[v];
		if(siz[v]>siz[son[x]])son[x]=v;
	}
}
void dfs2(int x,int t){
	top[x]=t;
	if(son[x])dfs2(son[x],t);
	for(auto v:eg[x])if(v!=son[x])dfs2(v,v);
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=pa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n,m);
	for(int i=1;i<n;i++)read(e[i].x,e[i].y),e[i].w=min(e[i].x,e[i].y);
	sort(e+1,e+n,[&](const Edge &x,const Edge &y){return x.w>y.w;});
	tot=n;
	for(int i=1;i<=n;i++)fa[i]=val[i]=i;
	for(int i=1;i<n;i++){
		int x=e[i].x,y=e[i].y,w=e[i].w;
		x=getfa(x);y=getfa(y);
		++tot;val[tot]=w;
		eg[tot].pb(x);eg[tot].pb(y);
		fa[x]=fa[y]=fa[tot]=tot;
	}
	dfs1(tot);
	dfs2(tot,tot);
	int las=0,t=0;
	while(m--){
		int op,x;read(op,x);
		x=(las+x)%n+1;
		if(op==1){
			if(!t)t=x;
			else t=LCA(t,x);
		}
		else{
			las=val[LCA(t,x)];
			cout<<las<<'\n';
		}
	}
    #ifdef do_while_true
//		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：UperFicial (赞：3)

很妙的一道题。

第一次修改后，钦定修改点 $x$ 为根，并令 $a_i$ 表示 $i$ 到修改点 $x$ 路径上编号最小点。

显然，之后若对节点 $y$ 进行修改，不会影响 $y$ 子树内节点的答案，而对于不在子树内的点 $u$，不论它位于哪里，贡献形成两条路径，$u\to x$ 和 $u\to y$，这时，$u$ 的位置对于化简式子就很关键，我们分情况讨论：

- 若 $u$ 位于 $x\to y$ 的路径上，$u\to x$ 和 $u\to y$ 两条路径可以合并为 $x\to y$ 这一条路径，答案为 $a_y$。

- 其他情况，$u\to y$ 这一条路径可以分成 $u\to x$ 和 $x\to y$ 两条路径，答案为 $\min\{a_x,a_y\}$。

但这样有些麻烦，因为我们需要记录哪些点位于根和黑点路径上，哪些又不是，然后分别用两种做法。

但是注意，最小值是可重复贡献问题，第一种做法我们再算一遍 $u\to x$ 的贡献，那么答案变为 $\min\{a_x,a_y\}$。

这样做法就清晰明了了，我们记录对于所有修改的点 $y$ 中 $a_y$ 的最小值，然后每询问一个点 $x$，将 $a_x$ 与 $a_y$ 的结果取 $\min$，就做完了。

时间复杂度 $\Theta(n)$。

代码：

```cpp
inline void dfs(int u,int fa)
{
	a[u]=Min(a[fa],u);
	gra(i,u)
	{
		int v=edge[i].to;
		if(v!=fa) dfs(v,u);
	}
	return;
}

int main()
{
	n=read(),q=read();
	rep(i,2,n)
	{
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}
	rep(i,1,q)
	{
		int opt=read(),x=(lstans+read())%n+1;
		if(opt==1)
		{
			if(i==1) a[0]=INF,dfs(x,0);
			minn=Min(minn,a[x]);
		}
		else printf("%d\n",lstans=Min(minn,a[x]));
	}
	
	return 0;
}
```



---

## 作者：Kreado (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF825G)。

## 思路

我们不妨钦定第一次修改操作的点为根节点，一次 DFS 跑出所有节点 $u$ 到根节点路径上的节点最小编号值 $a_u$。

对于之后的每一次修改操作（假设操作节点为 $x$），本次修改对 $x$ 子树内的答案没有影响，因为 $x$ 子树的点到达根节点的路径上已经包含了节点 $x$。

考虑在 $x$ 子树外的节点 $y$，$y$ 的子树不包括节点 $x$，对于 $y$ 唯一更新的就是 $x\to y$ 路径上的节点最小编号值，之前我们已经求出了每个 $a_i$，因此 $x\to y$ 路径上最小值编号就是 $\min(a_x,a_y)$。

接下来只有一种情况，$y$ 的子节点包括 $x$，这个很好解决，就是 $a_x$，你当然可以写成 $\min(a_x,a_y)$。

当然这还不够，我们还需维护当前全局黑点路径的最小编号值 $mn$，每次修改操作对 $a_x$ 取 $\min$。

对于每个询问，$\min(mn,a_x)$ 就是答案。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

namespace IO{
	template<typename T>
	inline void qread(T &x){
		x=0;char ch;bool f=0;
		while((ch=getchar())&&(ch<'0'||ch>'9')) if(ch=='-') f=1;x=(ch^48);
		while((ch=getchar())&&(ch>='0'&&ch<='9')) x=(x<<1)+(x<<3)+(ch^48);
		x=f?-x:x;
	} 
	template<typename T>
	inline void write(T x){
		if(x<0) x=-x,putchar('-');
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
}
using namespace IO;

const int Maxn=1e6+7;
int a[Maxn]; 
int n,Q,mn,lst;
vector<int>e[Maxn];

void DFS(int u,int ft){
	a[u]=u;
	if(ft) a[u]=min(a[u],a[ft]);
	for(auto v:e[u]) if(v!=ft) DFS(v,u);
}

int main(){
	qread(n),qread(Q);
	for(int i=1,u,v;i<n;i++)
		qread(u),qread(v),
		e[u].push_back(v),
		e[v].push_back(u);
	int opt,x;
	Q--;scanf("%d%d",&opt,&x);x=(x+lst)%n+1;
	DFS(x,0);mn=x;
	while(Q--){
		scanf("%d%d",&opt,&x);x=(x+lst)%n+1;
		if(opt==1) mn=min(mn,a[x]);
		else lst=min(a[x],mn),printf("%d\n",lst);
	}
	return 0;
}
```

时间复杂度 $O(n+q)$。

由于这道题时限很宽松，所以你倍增这棵树也是能过的。

---

## 作者：Acc_Robin (赞：1)

## CF825G Tree Queries 题解

[传送门](http://codeforces.com/problemset/problem/825/G)

[更高更妙的阅读体验](https://accrobin.github.io/2021/08/15/solver/CF825G/)

### 题意

一颗 $n$ 个节点的树，初始所有节点均为白色，你需要处理两种操作：

1. 修改：把某个节点 $x$ 涂黑
2. 询问：查询节点 $x$ 到树上所有黑色节点的路径上最小的节点编号。

强制在线，$n,q\le 10^6$。

### 题解 

我们以第一个染黑的节点为根（假设是下图的节点 $1$）

![](https://accrobin.github.io/images/CF825G/1.png)

假设当前已经染黑了节点 $1,3,6$，需要查询节点 $2$，那么我们发现可以将所有黑色节点分成两部分：和 $2$​ 都在根的一颗子树内的（$3$号）、和 $2$​ 不在根的一颗子树内的（$6$ 号）。

- 对于不在根的一颗子树内的，我们需要查询的就是路径 $2\to 1$​​​ 和路径 $1\to 6$​​​​​ 上的最小值。维护一个 $f_i$​​ 表示节点 $i$​​ 到根的路径上的最小值，那么询问点 $x$​​ 时的答案就是 
  $$
  \min(f_x,\min\limits_{y\text{与}x\text{不在同一颗子树},y\text{是黑点}}f_y)
  $$

- 对于在同一颗子树内的，我们要查询的是路径 $2\to 3$​ 上的最小值，这个并不好表示，但是注意我们也要统计 $2\to\text{根}$ 路径上的最小值，不妨并在一起，得到
  $$
  \min(f_x,\min\limits_{y\text{与}x\text{在同一颗子树},y\text{是黑点}}f_y)
  $$

上下两式再取 $\min$，发现就是
$$
\min(f_x,\min_{y\text{是黑点}}f_y)
$$
那么我们只需要在加入一个新点 $x$ 时维护一下上面的最小值，记作 $r$。在查询 $x$ 时，让 $r$ 和 $f_x$ 取个 $\min$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	const int N=1e6+9;
	basic_string<int>G[N];
	int f[N];
	void dfs(int u){for(int v:G[u])if(!f[v])f[v]=min(f[u],v),dfs(v);}
	void work(){
		int n,m,i,las=0,x,y,res=1e9;
        //ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
		for(cin>>n>>m,i=1;i<n;++i)cin>>x>>y,G[x]+=y,G[y]+=x;
		cin>>y>>x,x=x%n+1,dfs(f[x]=x);
		while(--m)if(cin>>i>>x,x=(x+las)%n+1,i==1)res=min(res,f[x]);else cout<<(las=min(res,f[x]))<<'\n';
	}
}
int main(){return Acc::work(),0;}
```

### 小细节

这题好像 `cin` 不流优化过不去……

---

## 作者：small_john (赞：1)

## 思路

把问题拆成两部分，一部分是已染色的点之间的最小点权，另一部分是询问的点 $x$ 到已染色的点的最小点权。

考虑加进来一个点对答案的贡献。有下面几种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/de335ydq.png)

图中，$1,2$ 号点为原来的点，$3$ 号点为新加入的点。可以发现，新加入的点到任何一个点的最短路径上的点肯定可以更新答案。

第一种操作就是把点真的加进来，第二种操作就不是真的加入点集。即：设操作前的答案为 $ans$，操作后为 $tmp$，如果是第一种操作，就更新答案 $ans$ 为 $tmp$，否则输出 $tmp$，不进行更新。

这个东西可以直接用倍增解决，只需要注意空间，~~反正我一直超空间~~。但还有一种更巧妙的方法。

注意到新加入的点可以和任何一个点进行答案统计，直接钦定这个点为第一个被染色的点，然后以这个点为根节点建树。统计一个数组 $mn$，其中 $mn_i$ 表示 $i$ 到根节点的最小点权。这样，每加入一个点 $x$，就可以直接以 $mn_x$ 为贡献了。

时间复杂度 $O(n)$，空间复杂度 $O(n)$，可轻松通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> inline void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x<=9) return putchar(x+48),void();
    write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    puts("");
}
const int N = 1e6+5;
int n,q,cnt,fir,mn[N],ans = 2e9,las;
vector<int> g[N];
inline void dfs(int u,int fa)
{
    mn[u] = min(u,mn[fa]);
	for(auto v:g[u])
	{
		if(v==fa) continue;
		dfs(v,u);
	}
}
signed main()
{
    read(n),read(q);
	for(int i = 1,u,v;i<n;i++)
		read(u),read(v),g[u].push_back(v),g[v].push_back(u);
	while(q--)
	{
	    int op,x;
        read(op),read(x);
		x = (x+las)%n+1;
		if(op==1)
		{
			if(!fir) fir = x,mn[0] = 2e9,dfs(x,0);
			else ans = min(ans,mn[x]);
		}
		else writen(las = min(ans,mn[x]));
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑 $\min_{i=1}^m\min(x\to y_i)$，其中 $y_i$ 表示黑色节点，$\min(i\to j)$ 表示 $i$ 到 $j$ 路径上最小的点。

容易发现上式等于 $\min(\min_{i=2}^m\min(y_1\to y_i),\min(x\to y_1))$。

左边容易维护，右边倍增查询即可。

复杂度 $O((n+q)\log n)$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define double long double
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[1000005];
int f[1000005][17],minv[1000005][17],dep[1000005];
void dfs(int now,int fa){
	dep[now]=dep[fa]+1;
	f[now][0]=fa,minv[now][0]=min(now,fa);
	for(int i=1;i<=16;i++) f[now][i]=f[f[now][i-1]][i-1],minv[now][i]=min(minv[now][i-1],minv[f[now][i-1]][i-1]);
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
	}
}
int qmin(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	int ans=1e9;
	for(int i=16;i>=0;i--) while(dep[f[u][i]]>=dep[v]) ans=min(ans,minv[u][i]),u=f[u][i];
	if(u==v) return min(ans,u);
	for(int i=16;i>=0;i--) while(f[u][i]!=f[v][i]) ans=min(ans,minv[u][i]),ans=min(ans,minv[v][i]),u=f[u][i],v=f[v][i];
	return min(ans,min(minv[u][0],minv[v][0]));
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n,q,tag=0,lst=0,ans=1e9; cin>>n>>q;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u); 
	}
	dfs(1,0);
	while(q--){
		int opt,x; cin>>opt>>x; x=(lst+x)%n+1;
		if(opt==1){
			if(!tag) tag=x,ans=x;
			else ans=min(ans,qmin(tag,x));
		}
		else{
			cout<<(lst=min(ans,qmin(tag,x)))<<"\n";
		}
//		cout<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

对于一个初始没有节点被染色的树维护两种操作：将一个点染色，或查询一个点到其他所有被染色点的最短路径上的编号的最小值。强制在线。

## 题目分析

查询可以当成树上被染色的点和给定点的极小联通块。考虑加入一个点对于这个联通块的影响。结论：加入一个点，只需要在已染色的点中随便选择一个点，将它们之间的最短路径加入即可。

证明：考虑反证。假设加入后，还存在点没有加入，且在加入点和另一个点的最短路径上。这相当于两条路径的不重叠部分，这一部分肯定在这两个染色点的最短路径上，而这就已经存在于联通块里了，存在矛盾。所以不会出现这种情况，结论得证。

所以直接树剖线段树维护就行了，复杂度 $O(n\log^2 n)$。时限有三秒，可以通过。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =1e6+5,M=1e5+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=998244353,bas=131;
const ui base=13331;
using namespace std;
int n,m,h[N],to[N<<1],nxt[N<<1],cnt,f[N],dep[N],siz[N],son[N],dfn[N],Time,top[N],ansn,Id[N];
int sml;
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
} 
inline void dfs(int x,int fa){
	f[x]=fa,dep[x]=dep[fa]+1,siz[x]=1;
	e(x)if(y^fa)dfs(y,x),siz[x]+=siz[y],son[x]=siz[y]>siz[son[x]]?y:son[x];
}
inline void Dfs(int x,int low){
	top[x]=low,dfn[x]=++Time,Id[Time]=x;
	if(son[x])Dfs(son[x],low);
	e(x)if(y^f[x]&&y^son[x])Dfs(y,y);
}
struct seg{
	bool f,laz;
	int w;
}xd[N<<2];
inline void getup(int x){
	xd[x].f=xd[L].f|xd[R].f;
	xd[x].w=min(xd[L].w,xd[R].w); 
}
inline void pushdown(int x){
	if(xd[x].laz)xd[x].laz=0,xd[L].f=xd[R].f=xd[L].laz=xd[R].laz=1;
}
inline void build(int x,int l,int r){
	if(l==r)return xd[x].w=Id[l],void();
	build(lc),build(rc),getup(x);
}
inline void modify(int x,int l,int r,int Ll,int Rr){
	if(OK)return xd[x].f=xd[x].laz=1,void();
	pushdown(x);
	if(Ll<=mid&&Rr>=l)modify(lc,Ll,Rr);
	if(Ll<=r&&Rr>mid)modify(rc,Ll,Rr);
	getup(x);
}
inline int query(int x,int l,int r,int Ll,int Rr){
	if(OK)return xd[x].w;
	if(Rr<=mid)return query(lc,Ll,Rr);
	if(Ll>mid)return query(rc,Ll,Rr);
	return min(query(lc,Ll,Rr),query(rc,Ll,Rr));
}
inline bool got(int x,int l,int r,int Ll,int Rr){
	if(OK)return xd[x].f;
	pushdown(x);
	if(Rr<=mid)return got(lc,Ll,Rr);
	if(Ll>mid)return got(rc,Ll,Rr);
	return got(lc,Ll,Rr)|got(rc,Ll,Rr);
}
inline void lca(int x,int y){
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ansn=min(ansn,query(Root,dfn[top[x]],dfn[x]));
		modify(Root,dfn[top[x]],dfn[x]);
		x=f[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ansn=min(ansn,query(Root,dfn[x],dfn[y])),modify(Root,dfn[x],dfn[y]);
}
inline int Lca(int x,int y){
	int ans=ansn;
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=min(ans,query(Root,dfn[top[x]],dfn[x]));
		x=f[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans=min(ans,query(Root,dfn[x],dfn[y]));
	return ans;
}
inline void solve(int x){
	if(!sml)return sml=x,modify(Root,dfn[x],dfn[x]),ansn=x,void();
	if(got(Root,dfn[x],dfn[x]))return;
	lca(x,sml);
}
inline int getans(int x){
	if(got(Root,dfn[x],dfn[x]))return ansn;
	return Lca(x,sml);
}
int lastans;
int main(){
	ansn=n=read(),m=read();
	for(int i=1,x,y;i^n;i++)x=read(),y=read(),add(x,y),add(y,x);
	dfs(1,0),Dfs(1,1),build(Root);
	rep(i,1,m){
		int opt=read(),x=(lastans+read())%n+1;
		if(opt==1)solve(x);
		else lastans=getans(x),pf(lastans),putchar('\n');
	}
	return 0;
}
```


---

## 作者：shinkuu (赞：0)

场切力。

暴力一点也无妨，不用把第一个设为根其实也可以。

考虑维护当前点集内所有点的 lca 记为 $l$ 和联通所有点的最小子图内点权最小值记为 $mn$。设加入点 $x$，则让 $x$ 和 $l$ 都跳到 $\operatorname{lca}(x,l)$ 处，并对于路径上的所有点 $i$ 做一次 $mn\leftarrow\min(mn,i)$。这一部分可以简单倍增维护。

对于查询操作，可以做一遍和上文类似的操作，并令 $mn$ 的修改不影响后面操作即可。写起来没什么细节，`*2500` 高了。

code：

```cpp
int n,m,dep[N],fa[N][23],c[N][23];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
inline void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void dfs(int u,int f){
	fa[u][0]=c[u][0]=f;
	dep[u]=dep[f]+1;
	rep(i,1,20){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		c[u][i]=min(c[u][i-1],c[fa[u][i-1]][i-1]);
	}
	go(i,u){
		int v=e[i].to;
		if(v==f)
			continue;
		dfs(v,u);
	}
}
int get_lca(int u,int v){
	if(dep[u]<dep[v])
		swap(u,v);
	drep(i,20,0){
		if(dep[fa[u][i]]>=dep[v])
			u=fa[u][i];
	}
	if(u==v)
		return u;
	drep(i,20,0){
		if(fa[u][i]!=fa[v][i])
			u=fa[u][i],v=fa[v][i];
	}
	return fa[u][0];
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,n-1){
		int u,v;
		u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	int nl=0,mn=inf,lst=0;
	rep(i,1,m){
		int op=read(),x=read();
		x=(x+lst)%n+1;
		if(op==1){
			if(!nl){
				nl=mn=x;
				continue;
			}
			int y=get_lca(x,nl);
			mn=min(mn,x);
			drep(j,20,0){
				if(dep[fa[nl][j]]>=dep[y]){
					mn=min(mn,c[nl][j]);
					nl=fa[nl][j];
				}
			}
			drep(j,20,0){
				if(dep[fa[x][j]]>=dep[y]){
					mn=min(mn,c[x][j]);
					x=fa[x][j];
				}
			}
		}else{
			int y=get_lca(x,nl),z=nl,res=x;
			drep(j,20,0){
				if(dep[fa[z][j]]>=dep[y]){
					res=min(res,c[z][j]);
					z=fa[z][j];
				}
			}
			drep(j,20,0){
				if(dep[fa[x][j]]>=dep[y]){
					res=min(res,c[x][j]);
					x=fa[x][j];
				}
			}
			printf("%d\n",lst=min(res,mn));
		}
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：EuphoricStar (赞：0)

模拟赛赛时做法。

看到查询路径点权最小值，想到建重构树，满足重构树上 $\operatorname{LCA}(x, y)$ 为原树上 $x \to y$ 路径的点权最小值。建树方法可以参考 [CF1797F Li Hua and Path](https://www.luogu.com.cn/problem/CF1797F)。

于是问题变成了，维护一个点集，支持加点，查询给定点 $x$ 到点集中所有点的 $\operatorname{LCA}$ 中最浅的那个。

有个结论是点集中只有 dfn 序最小和最大的点有用。因为子树的 dfn 序是连续的，我们想让 $\operatorname{LCA}$ 尽量浅，就要让以 $\operatorname{LCA}$ 为根的子树尽量大。

于是我们维护点集中 dfn 序最小和最大的点即可，这样点集的大小不超过 $2$。

时间复杂度 $O((n + q) \log n)$。

[code](https://codeforces.com/problemset/submission/825/220474920)

---

## 作者：Federico2903 (赞：0)

## 思路

好题。模拟赛的时候不会 ST 表打了两只 $\log$ 的树剖，改成 ST 表过后这一题就过了。

假设我们已经求得了之前所有黑点的答案，记这些黑点的答案为 $minn$，这些黑点的最近公共祖先为 $lca$。

当加入一个新的黑点时，我们重新计算新的最近公共祖先（实际上只需要计算新点和 $lca$ 的最近公共祖先即可），而新的贡献一定产生在原来的 $lca$ 和新的 $lca$ 和 新的黑点到新的 $lca$ 之间。

考虑树链剖分，得到新的 $DFN$ 序列之后使用 ST 表处理出区间最小值即可。

时间复杂度 $O(q\log n)$。

## AC 代码

```cpp
const int MAXN = 1e6 + 5;
int iw[MAXN], w[MAXN];
int Min[MAXN][21];

int wSon[MAXN], hSon[MAXN], siz[MAXN], fa[MAXN], dfn[MAXN], dep[MAXN];
int top[MAXN], cnt;
vector <int> G[MAXN];
int n, q, minnTop = INT_MAX, lca;

void build() {
	rep (i, 1, n) Min[i][0] = w[i];
	rep (j, 1, 21)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
}

int query(int l, int r) {
	int k = log2(r - l + 1);
	return min(Min[l][k], Min[r - (1 << k) + 1][k]);
}

void getSize(int step, int u, int fa) {
	::fa[u] = fa, dep[u] = step, siz[u] = 1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		getSize(step + 1, v, u);
		siz[u] += siz[v];
		if (siz[v] > siz[hSon[u]]) hSon[u] = v;
	}
}

void getDFN(int u, int h) {
	top[u] = h, dfn[u] = ++cnt, w[dfn[u]] = iw[u];
	if (!hSon[u]) return;
	getDFN(hSon[u], h);
	for (auto v : G[u]) {
		if (v == fa[u] || v == hSon[u]) continue;
		getDFN(v, v);
	}
}

int LCA(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	return x;
}

int calcChain(int x, int y) {
	int res = INT_MAX;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		res = min(res, query(dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	res = min(res, query(dfn[x], dfn[y]));
	return res;
}

void JC(int x) {
	if (!lca) return (void) (lca = x, minnTop = iw[x]);
	int oldLCA = lca;
	lca = LCA(lca, x);
	minnTop = min(calcChain(oldLCA, lca), minnTop);
	minnTop = min(calcChain(x, lca), minnTop);
}

int Query(int x) {
	int ans = INT_MAX;
	ans = min(ans, min(calcChain(x, lca), minnTop));
	return ans;
}

int lstans = 0;

int main() {
	read(n), read(q);
	rep (i, 1, n - 1) {
		int u, v;
		read(u), read(v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	rep (i, 1, n) iw[i] = i;
	getSize(1, 1, 1);
	getDFN(1, 1); build();
	while (q --> 0) {
		int op, x; read(op), read(x);
		x = (lstans + x) % n + 1;
		if (op == 1) JC(x);
		else print(lstans = Query(x)), putchar(10);
	}
	return 0; 
}
```

---

