# Good Graph

## 题目描述

You have an undirected graph consisting of $ n $ vertices with weighted edges.

A simple cycle is a cycle of the graph without repeated vertices. Let the weight of the cycle be the [XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of weights of edges it consists of.

Let's say the graph is good if all its simple cycles have weight $ 1 $ . A graph is bad if it's not good.

Initially, the graph is empty. Then $ q $ queries follow. Each query has the next type:

- $ u $ $ v $ $ x $ — add edge between vertices $ u $ and $ v $ of weight $ x $ if it doesn't make the graph bad.

For each query print, was the edge added or not.

## 样例 #1

### 输入

```
9 12
6 1 0
1 3 1
3 6 0
6 2 0
6 4 1
3 4 1
2 4 0
2 5 0
4 5 0
7 8 1
8 9 1
9 7 0```

### 输出

```
YES
YES
YES
YES
YES
NO
YES
YES
NO
YES
YES
NO```

# 题解

## 作者：一叶知秋。 (赞：8)

场上莫名其妙 $\text{A}$ 写了一年，然后 $\text{D}$ 看错了，就没时间写 $\text{F}$ 了。

我们首先把能改变连通性（就是能连接两个之前未连接的连通块）的边称作树边，树边显然一定能够加入

可以发现一条非树边能加入要满足两个条件：

1、它跟树边组成的环满足异或和为 $1$ 

2、它与树边组成的环不跟任何一个之前的环边相交，因为这样两个异或一下大环就为 $0$ 了

也就是要保证图是仙人掌，但当然貌似做起来并不需要用到这个性质，我们发现每次加入非树边其实就是查询 $u->lca$ 和 $v->lca$ 的边集中是否有边被覆盖了，没有就能加入，加入后就将这些边全部覆盖，也就是要做动态链覆盖和链查询

$\text{LCT}$ 显然可以做，但是已经被踢出考纲的东西也尽量别用（

显然非树边加入肯定跟它有关的树边已经全被加入了，其他的也并不影响，我们考虑离线处理，先把树边全部加入，然后就可以随便做了，同时我们可以发现一条边只会被覆盖一次，可以直接用树状数组暴力修改，查询一下前缀和就可以了，不需要写树剖

code ：

```cpp
#include<cstdio>
#include<cctype>
#include<vector>

#define maxn 505505

template<class T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

template<class T>

inline void swap(T &a,T &b){
	T c=a;
	a=b;
	b=c;
}

struct E{
	int v,w,nxt;
	E() {}
	E(int v,int w,int nxt):v(v),w(w),nxt(nxt) {}
}e[maxn<<1];

int n,m,s_e,head[maxn],f[maxn],size[maxn];

int s_dfn,fa[maxn],val[maxn],dfn[maxn],LCA[maxn];

bool used[maxn];

std::vector<int> to[maxn];

inline void a_e(int u,int v,int w){
	e[++s_e]=E(v,w,head[u]);
	head[u]=s_e;
}

int find(int x){
	return x^f[x]?f[x]=find(f[x]):x;
}

int U[maxn],V[maxn],W[maxn];

void dfs(int u){
	size[u]=1;
	dfn[u]=++s_dfn;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v,w=e[i].w;
		if(dfn[v])continue;
		val[v]=val[u]^w;
		fa[v]=u,dfs(v);
		size[u]+=size[v];
		f[v]=u;
	}
	for(int i=0;i<(int)to[u].size();i++){
		int num=to[u][i];
		int v=U[num]^V[num]^u;
		if(dfn[v])LCA[num]=find(v);
	}
}

namespace BIT{

#define lowbit(k) (k&(-k))

	int c[maxn];

	inline void add(int k,int x){
		for(;k<=n;k+=lowbit(k))c[k]+=x;
	}

	inline int sum(int k){
		int Sum=0;
		for(;k;k-=lowbit(k))Sum+=c[k];
		return Sum;
	}

#undef lowbit

}

int main(){
	n=read<int>();
	m=read<int>();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int u=read<int>();
		int v=read<int>();
		int w=read<int>();
		int fu=find(u),fv=find(v);
		if(fu^fv){
			a_e(u,v,w);
			a_e(v,u,w);
			f[fu]=fv;
			used[i]=1;
		}
		else {
			to[u].push_back(i);
			to[v].push_back(i);
		}
		U[i]=u,V[i]=v,W[i]=w;
	}
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++)
		if(!dfn[i])dfs(i);//离线建树
	for(int i=1;i<=m;i++){
		if(used[i]){
			puts("YES");
			continue;
		}
		int u=U[i],v=V[i],w=W[i],lca=LCA[i];
		if((val[u]^val[v]^w)&&BIT::sum(dfn[u])==BIT::sum(dfn[lca])&&BIT::sum(dfn[v])==BIT::sum(dfn[lca])){
			puts("YES");//暴力修改
			while(u^lca){
				BIT::add(dfn[u],1);
				BIT::add(dfn[u]+size[u],-1);
				u=fa[u];
			}
			while(v^lca){
				BIT::add(dfn[v],1);
				BIT::add(dfn[v]+size[v],-1);
				v=fa[v];
			}
		}
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：RedLycoris (赞：5)

晚上有点累就没打Edu，感觉亏大本了![](http://啧.tk/tuu)

---

首先，我们需要一个性质：

合法的图中不存在两个有着公共边的环

证明：

设环 $a$ 中不与环 $b$ 公用的部分的异或值为 $x$，环 $b$ 中不与环 $a$ 公用的部分的异或值为 $y$，环 $a$ 与 $b$ 公共部分的异或值为 $z$

那么，有:

+ $x \oplus z = 1$

+ $y \oplus z = 1$

+ $x \oplus y = 1$

(对应了环 $a$，环 $b$ 和新构成的环 $c$，其中 $\oplus$ 表示异或)

将这三个式子一起异或起来，就可以得到 $0 = 1$，显然不成立，故不会有两个有着公共边的环。

所以说，每次询问，就相当于询问，加上这条边后，会不会生成一个新环，且这个环与已经存在的环有着公共边。

还有一个性质：

如果我们把所有边离线下来，按照顺序加边，如果当前这条边不会生成一个环，那么它一定是可以加入的。

证明：

因为只有加上这条边后，会生成一个新环，且这个环与已经存在的环有着公共边，才会不能加，故在不生成环的情况下，是可以随便加边的。（也可以感性理解下）

所以我们就可以先按照第二个性质建出一棵树来，然后对于非树边一个一个判断。

于是，我们对于每一条可以加入的非树边，就对 $u_i$ 到 $v_i$ 的简单路径上的所有边权加一。在询问的时候，看 $u_i$ 到 $v_i$ 的简单路径上所有边的边权和是否为 0 即可。

看到是对树上的路径操作就很容易的想到了树剖。

至于题目要求是对边权进行加，我们可以把边权转换到点上：点 $i$ 的权值为连接 $i$ 与 $i$ 父亲的边的权值。

然后就可以码码码了![](http://啧.tk/cy)

我想练练手，所以代码里判断异或和就单独写了个倍增，没有再在树剖里搞，导致巨大多常数，1497ms

Code: 5130 Byte

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
const int mxn=5e5+5;
int n,q,root;
int val[mxn];
int bg[mxn],ed[mxn],top[mxn],sz[mxn],dep[mxn],dfsc;
int pa[mxn],ord[mxn],P[mxn][22],xo[mxn][22];
vector<int>g[mxn];
int par_val[mxn];
inline int dfs1(int x,int par=0,int deep=1){   //树剖基操
	dep[x]=deep;
	sz[x]=1;pa[x]=par;
	P[x][0]=par;
	for(int i=0;i<g[x].size();++i){
		int y=g[x][i];
		if(y==par)continue;
		sz[x]+=dfs1(y,x,deep+1);
	}
	return sz[x];
}
inline void dfs(int x,int tpf=root,int par=0){
	bg[x]=++dfsc;
	top[x]=tpf;
	ord[dfsc]=x;
	int mx=-1,pos;
	for(int i=0;i<g[x].size();++i){
		int y=g[x][i];
		if(y==par)continue;
		if(sz[y]>mx){
			mx=sz[y];
			pos=y;
		}
	}
	if(mx==-1){
		ed[x]=dfsc;
		return;
	}
	dfs(pos,tpf,x);
	for(int i=0;i<g[x].size();++i){
		int y=g[x][i];
		if(y==par or y==pos)continue;
		dfs(y,y,x);
	}
	ed[x]=dfsc;
}
struct segt{                         //线段树维护树点权
	int sum[mxn<<3];
	int laz[mxn<<3];
	int siz[mxn<<3];
	inline void init(){
		memset(siz,0,sizeof(siz));
		memset(laz,0,sizeof(laz));
		memset(sum,0,sizeof(sum));
	}
	inline void pushup(int x){sum[x]=sum[x<<1]+sum[x<<1|1];}
	inline void pushdown(int x){
		if(laz[x]){
			sum[x]+=1ll*laz[x]*siz[x];
			laz[x<<1]+=laz[x];
			laz[x<<1|1]+=laz[x];
			laz[x]=0;
		}
	}
	inline void build(int x,int l,int r){
		siz[x]=r-l+1;
		if(l==r){
			sum[x]=val[ord[l]];
			return;
		}
		int md=l+r>>1;
		build(x<<1,l,md);
		build(x<<1|1,md+1,r);
		pushup(x);
	}
	inline void add(int x,int l,int r,int a,int b,int d){
		pushdown(x);
		if(a<=l and r<=b){
			laz[x]+=d;
			pushdown(x);
			return;
		}
		if(r<a or b<l)return;
		int md=l+r>>1;
		add(x<<1,l,md,a,b,d);
		add(x<<1|1,md+1,r,a,b,d);
		pushup(x);
	}
	inline int ask(int x,int l,int r,int a,int b){
		pushdown(x);
		if(a<=l and r<=b)return sum[x];
		if(r<a or b<l)return 0;
		int md=l+r>>1;
		return ask(x<<1,l,md,a,b)+ask(x<<1|1,md+1,r,a,b);
	}
}seg;
inline void updRange(int x,int y,int d){   //路径修改
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])swap(x,y);
		seg.add(1,1,n,bg[top[y]],bg[y],d);
		y=top[y];
		y=pa[y];
	}
	if(dep[x]>dep[y])swap(x,y);
	seg.add(1,1,n,bg[x],bg[y],d);
}
inline int qryRange(int x,int y){       //路径查询
	int ans=0;
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])swap(x,y);
		ans+=seg.ask(1,1,n,bg[top[y]],bg[y]);
		y=top[y];
		y=pa[y];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans+=seg.ask(1,1,n,bg[x],bg[y]);
	return ans;
}
inline void addSub(int x,int d){     //闲着无聊把子树和也写了下，但没用
	seg.add(1,1,n,bg[x],ed[x],d);
}
inline int qrySub(int x){return seg.ask(1,1,n,bg[x],ed[x]);}
struct dsu{                   //并查集，用来离线后把所有树边提前加上
	int fa[mxn];
	inline void init(){for(int i=1;i<mxn;++i)fa[i]=i;}
	inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
	inline int merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return 0;
		fa[x]=y;
		return 1;
	}
}d;
int u[mxn],v[mxn],w[mxn];
int ans[mxn];
int roots[mxn];
inline void dfs_xor(int x,int P=0){          //写的倍增处理异或
	xo[x][0]=par_val[x];
	for(int i=0;i<g[x].size();++i){
		int y=g[x][i];
		if(y==P)continue;
		dfs_xor(y,x);
	}
}
inline void init_xor(){
	for(int j=1;j<=20;++j){
		for(int i=1;i<=n;++i){
			P[i][j]=P[P[i][j-1]][j-1];
			xo[i][j]=xo[i][j-1]^xo[P[i][j-1]][j-1];
		}
	}
}
inline int qryXor(int x,int y){
	int rt=0;
	if(dep[x]>dep[y])swap(x,y);
	for(int i=20;~i;--i)if(dep[P[y][i]]>=dep[x])rt^=xo[y][i],y=P[y][i];
	for(int i=20;~i;--i)if(P[x][i]!=P[y][i])rt^=xo[x][i],rt^=xo[y][i],x=P[x][i],y=P[y][i];
	if(x!=y){
		rt^=xo[x][0],rt^=xo[y][0];
		x=P[x][0],y=P[y][0];
	}
	return rt;
}
inline int lca(int x,int y){              //又用倍增写了个LCA
	if(dep[x]>dep[y])swap(x,y);
	for(int i=20;~i;--i)if(dep[P[y][i]]>=dep[x])y=P[y][i];
	for(int i=20;~i;--i)if(P[x][i]!=P[y][i])x=P[x][i],y=P[y][i];
	if(x!=y)x=P[x][0],y=P[y][0];
	return x;
}
inline void solve(){
	cin>>n>>q;
	d.init();
	for(int i=1;i<=q;++i){               //处理树边
		cin>>u[i]>>v[i]>>w[i];
		ans[i]=d.merge(u[i],v[i]);
		if(ans[i])g[u[i]].push_back(v[i]),g[v[i]].push_back(u[i]);
	}
	for(int i=1;i<=n;++i)if(!top[i]){       //可能会有多个边
		roots[i]=1;
		dfs1(i);
		dfs(i,i);
	}
	for(int i=1;i<=q;++i){ 
		if(!ans[i])continue;
		if(u[i]==pa[v[i]])par_val[v[i]]=w[i];
		else par_val[u[i]]=w[i];
	}
	for(int i=1;i<=n;++i)
		if(roots[i])
			dfs_xor(i);
	init_xor();
	seg.build(1,1,n);
	for(int i=1;i<=q;++i){                //边权转点权
		if(ans[i]){ 
			if(u[i]==pa[v[i]])val[v[i]]=w[i];
			else val[u[i]]=w[i];
		}
	}
	for(int i=1;i<=q;++i){
		if(ans[i])continue;
		int X=qryXor(u[i],v[i])^w[i];
		if(X==0)continue;
		int LCA=lca(u[i],v[i]);
//		cerr<<u[i]<<' '<<v[i]<<' '<<w[i]<<'\n';
//		for(int i=1;i<=n;++i)cerr<<qryRange(i,i)<<' ';cerr<<'\n';
		int t=qryRange(u[i],v[i])-qryRange(LCA,LCA);   //一定要减掉LCA处的点权 因为它对应的是LCA到LCA的父亲这条边的边权，不在路径上
//		cerr<<"??? "<<qryRange(u[i],v[i])<<' '<<qryRange(u[i],u[i])<<' '<<qryRange(v[i],v[i])<<' '<<qryRange(LCA,LCA)<<'\n';
		if(t!=0);
		else{
			ans[i]=1;
			updRange(u[i],v[i],1);    //同理
			updRange(LCA,LCA,-1); 
		}
	}
	for(int i=1;i<=q;++i){
		if(ans[i])cout<<"YES\n";
		else cout<<"NO\n";
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;T=1;
//	cin>>T;
	for(;T--;)solve();
	return 0;
}
```

---

## 作者：iMya_nlgau (赞：2)

因为图中每个环的权值异或和为 $1$，所以由两个环拼成的环的异或和就是 $0$，不合法。因此，合法的图中每条边一定至多属于一个环。

怎么维护这个东西呢？我们只维护一颗树就好了，加入的一条边如果和树上的一条路径形成环，我们就把这条路经上的边都打上标记，在这之前要进行判断，如果边两端之间的路径上已经存在标记或形成的环的异或和不为 $1$，则不合法。如果新加入的边两端点本来不连通，直接加入即可。

于是无脑的 LCT 维护就行了，只需要对链上的边打标记，查询链上是否有标记，查询链异或和，以及 link 操作。

复杂度 $O(m\log n)$。我比赛时候时间不够没码完，差这一道题没 AK。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
using namespace std; 
inline int read(){
	int x=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+(c^'0'),c=getchar();
	return x;
}
typedef long long ll;
const int maxn=3e5+10;
const int maxq=5e5+10;
struct Node{
	int s[2],p,siz,v1,sum,v2,_s,tag1,tag2;
}tr[maxn*2];
int n,q,tot,stk[maxn*2];
inline void pushup(int x){
	tr[x].siz=tr[tr[x].s[0]].siz+tr[tr[x].s[1]].siz+(x>n);
	tr[x].sum=tr[tr[x].s[0]].sum^tr[tr[x].s[1]].sum^tr[x].v1;
	tr[x]._s=tr[tr[x].s[0]]._s|tr[tr[x].s[1]]._s|(x>n&&tr[x].v2>0);
}
inline void pushrev(int x){
	swap(tr[x].s[0],tr[x].s[1]);
	tr[x].tag1^=1;
} 
inline void pushadd(int x){
	tr[x]._s=tr[x].siz;
	if(x>n) tr[x].v2=1;
	tr[x].tag2=1;
}
inline void pushdown(int x){
	if(tr[x].tag1){
		pushrev(tr[x].s[0]),pushrev(tr[x].s[1]);
		tr[x].tag1=0;
	}
	if(tr[x].tag2){
		pushadd(tr[x].s[0]),pushadd(tr[x].s[1]);
		tr[x].tag2=0;
	}
}
inline bool isroot(int x){
	return tr[tr[x].p].s[0]!=x&&tr[tr[x].p].s[1]!=x;
}
inline void rotate(int x){
	int y=tr[x].p,z=tr[y].p,k=tr[y].s[1]==x;
	if(!isroot(y)) tr[z].s[tr[z].s[1]==y]=x;
	tr[x].p=z;
	tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].p=y;
	tr[x].s[k^1]=y,tr[y].p=x;
	pushup(y),pushup(x);
}
void splay(int x){
	int top=0,r=x;
	stk[++top]=r;
	while(!isroot(r)) stk[++top]=r=tr[r].p;
	while(top) pushdown(stk[top--]);
	while(!isroot(x)){
		int y=tr[x].p,z=tr[y].p;
		if(!isroot(y)) rotate(tr[y].s[1]==x^tr[z].s[1]==y?x:y);
		rotate(x);
	}
}
void access(int x){
	int z=x;
	for(int y=0;x;y=x,x=tr[x].p){
		splay(x);
		tr[x].s[1]=y,pushup(x);
	}
	splay(z);
}
void makeroot(int x){
	access(x),pushrev(x);
}
int findroot(int x){
	access(x);
	while(tr[x].s[0]) pushdown(x),x=tr[x].s[0];
	splay(x);
	return x;
}
void split(int x,int y){
	makeroot(x),access(y);
}
void link(int x,int y){
	makeroot(x);
	if(findroot(y)!=x) tr[x].p=y;
}
int main(){
	n=read(),q=read(); tot=n;
	for(int i=1;i<=n;i++) tr[i].siz=1;
	for(int i=1;i<=q;i++){
		int u=read(),v=read(),w=read();
		makeroot(u);
		if(findroot(v)!=u){
			tot++,tr[tot].v1=tr[tot].sum=w,tr[tot].siz=1;
			link(u,tot),link(tot,v);
			puts("YES");
		}else{
			split(u,v);
			if(tr[v]._s>0||(tr[v].sum^w)!=1) puts("NO");
			else{
				pushadd(v);
				puts("YES");
			} 
		}
	}
	return 0;
}
```

---

## 作者：dead_X (赞：2)

## 前言
顶 风 作 案

甲 级 战 犯
## 思路
不难发现，如果当前的图合法，图一定是一棵**边仙人掌**。

证明：如果有两个权值为 $1$ 的简单环经过同一条边，它们的并一定是一个权值为 $0$ 的简单环。

~~因此，你可以用动态仙人掌解决问题。~~

于是，如果我们已经有一棵树，判断能不能加入一条连接树上节点的边就可以转化成两个操作：

* 求两个点路径异或和。
* 判断链是否全为 $0$，即判断这些边是否在环上。
* 将一条链全部修改为 $1$，即标记这些边在环上。

这个操作可以使用树链剖分在 $O(m\log^2n)$ 的时间内完成。

但是加边的过程是动态的 nya，怎么树剖呀？

* 我会 LCT！

嗯，但是笔者不会 LCT，所以请右转其他题解。

* 我会离线！

注意到连接两个连通块的边显然是合法的，而剩下的边即使合法，两个点的路径异或和也不会改变，因此正确性仍然能保证。

于是我们用一个并查集维护，将所有连接两个连通块的边先保留，这样就可以维护森林了，然后直接对于森林的每棵树树剖即可。

时间复杂度 $O(m\log^2n)$，只能说树剖常数实在是太小啦！
## 代码
我口胡了，代码贺的 Epsilon_Cube 的。

```cpp
//Efite gaaa c,lve iin ndt tdinlidhnhr.
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int u[500003],v[500003],w[500003],Fa[300003];
int find(int x)
{
	if(x==Fa[x]) return Fa[x];
	return Fa[x]=find(Fa[x]);
}
int ans[500003];
#define mp make_pair
vector<pair<int,int> > e[300003];
int sz[300003],fa[300003],dep[300003],son[300003],top[300003];
int dfn[300003],inv[300003],lst[300003],tot;
int V[300003];
inline void dfs1(int x)
{
    sz[x]=1;
    for(auto xx:e[x]) {int y=xx.first;if(y!=fa[x])
    {
        if(y==fa[x])continue;
        fa[y]=x,dep[y]=dep[x]+1,V[y]=V[x]^xx.second,dfs1(y),sz[x]+=sz[y];
        (sz[y]>sz[son[x]])&&(son[x]=y);
    }}
}
inline void dfs2(int x,int tp)
{
    top[x]=tp,dfn[x]=++tot,inv[tot]=x;
    if(son[x]) dfs2(son[x],tp);
    for(auto xx:e[x]) {int y=xx.first;
        if(y!=son[x]&&y!=fa[x])dfs2(y,y);}
    lst[x]=tot;
}
int sum[4000003];
inline void upd1(int nl,int nr,int l,int r,int i)
{
	if(r<nl||nr<l||sum[i]==2) return ;
	if(l<=nl&&nr<=r) return (void)(sum[i]=2);
	int mid=(nl+nr)>>1;
	upd1(nl,mid,l,r,i<<1),upd1(mid+1,nr,l,r,(i<<1)+1),
	sum[i]=1+(sum[i<<1]==2&&sum[(i<<1)+1]==2);
	return ;
}
inline int query(int nl,int nr,int l,int r,int i)
{
	if(r<nl||nr<l) return 0;
	if(!sum[i]) return 0;
	if(sum[i]==2) return 1;
	if(l<=nl&&nr<=r) return sum[i];
	int mid=(nl+nr)>>1;
	return query(nl,mid,l,r,i<<1)+query(mid+1,nr,l,r,(i<<1)+1);
}
signed main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) Fa[i]=i;
	for(int i=1; i<=m; ++i)
		u[i]=read(),v[i]=read(),w[i]=read();
	for(int i=1; i<=m; ++i)
	{
		int A=find(u[i]),B=find(v[i]);
		if(A!=B) 
		{e[u[i]].push_back(mp(v[i],w[i])),
		e[v[i]].push_back(mp(u[i],w[i]));
		Fa[A]=B;
		ans[i]=2;}
	}
	for(int i=1; i<=n; ++i) if(!dfn[i]) dfs1(i),dfs2(i,i);
	for(int i=1; i<=m; ++i) if(!ans[i])
	{
		int x=u[i],y=v[i];
		bool flg=1;
		if(!(V[x]^V[y]^w[i])) continue;
		ans[i]=-1;
		while(top[x]!=top[y])
		{
			if(dep[top[y]]>dep[top[x]]) swap(x,y);
			if(query(1,n,dfn[top[x]],dfn[x],1)){flg=0;break;}
			x=fa[top[x]];
		}
		if(flg) 
		if(x==y||query(1,n,min(dfn[x],dfn[y])+1,max(dfn[x],dfn[y]),1)==0)
		{
			int x=u[i],y=v[i];
			while(top[x]!=top[y])
			{
				if(dep[top[y]]>dep[top[x]]) swap(x,y);
				upd1(1,n,dfn[top[x]],dfn[x],1);
				assert(query(1,n,dfn[top[x]],dfn[x],1)>0);
				x=fa[top[x]];
			}
			if(x!=y)
			upd1(1,n,min(dfn[x],dfn[y])+1,max(dfn[x],dfn[y]),1);
			ans[i]=1;
		}
	}
	for(int i=1; i<=m; ++i) if(ans[i]>0) puts("YES");
	else puts("NO");
	return 0;
}
```

---

## 作者：kouylan (赞：1)

我们先考虑什么样子的边是可以加进来的。第一类是连接两个连通块的，称为 “树边”。第二类就是连接一个连通块内的两个点，满足路径上每条边在这之前不在环上（限制 $1$），并且路径异或和为 $1$（限制 $2$），这一类称为 “非树边”。

我们可以离线处理，先摘出所有树边并连边，这个图就构成了一个森林。这一步可以用并查集实现。

然后再考虑非树边。先处理限制 $1$，我们可以把在环上的边赋值为 $1$，不在环上的边赋值为 $0$，然后合法条件就是树的路径上所有边权值都是 $0$（和是 $0$ / 最大值是 $0$），这树剖就可以实现。然后处理限制 $2$，一个树上前缀异或和即可。

下面是 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define lson o<<1
#define rson o<<1|1
#define mid (l+r>>1)

int n,m,xx[500005],yy[500005],zz[500005];
int dsu[500005],tr[500005],sum[500005];
int ee,h[300005],nex[300005<<1],to[300005<<1],val[300005<<1];
int dep[300005],dfn[300005],fa[300005],siz[300005],top[300005],son[300005];
struct segtree{
	int v,laz;
}t[300005<<2];

int find_(int x)
{
	return dsu[x]==x ? x : dsu[x] = find_(dsu[x]);
}

void addedge(int x,int y,int z)
{
	nex[++ee] = h[x], to[ee] = y, val[ee] = z, h[x] = ee;
}

void dfs1(int x,int pre)
{
	dep[x] = dep[pre]+1, fa[x] = pre, siz[x] = 1;
	for(int i=h[x];i;i=nex[i])
		if(to[i]!=pre)
		{
			sum[to[i]] = sum[x]^val[i];
			dfs1(to[i],x);
			siz[x] += siz[to[i]];
			if(siz[to[i]]>siz[son[x]])
				son[x] = to[i];
		}
}

void dfs2(int x,int tp)
{
	top[x] = tp, dfn[x] = ++dfn[0];
	if(!son[x]) return;
	dfs2(son[x],tp);
	for(int i=h[x];i;i=nex[i])
		if(to[i]!=fa[x] && to[i]!=son[x])
			dfs2(to[i],to[i]);
}

void pushdown(int o)
{
	if(t[o].laz)
	{
		t[lson].v = t[lson].laz = t[o].laz;
		t[rson].v = t[rson].laz = t[o].laz;
	}
	t[o].laz = 0;
}

void modify(int o,int l,int r,int ql,int qr,int v)
{
	if(ql>qr)
		return;
	if(l>=ql && r<=qr)
	{
		t[o].v = t[o].laz = v;
		return;
	}
	pushdown(o);
	if(ql<=mid)
		modify(lson,l,mid,ql,qr,v);
	if(qr>mid)
		modify(rson,mid+1,r,ql,qr,v);
	t[o].v = max(t[lson].v,t[rson].v);
}

void modify_(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		modify(1,1,n,dfn[top[x]],dfn[x],1);
		x = fa[top[x]];
	}
	if(dep[x]<dep[y])
		swap(x,y);
	modify(1,1,n,dfn[y]+1,dfn[x],1);
}

int query(int o,int l,int r,int ql,int qr)
{
	if(ql>qr)
		return 0;
	if(l>=ql && r<=qr)
		return t[o].v;
	pushdown(o);
	int res=0;
	if(ql<=mid)
		res = max(res,query(lson,l,mid,ql,qr));
	if(qr>mid)
		res = max(res,query(rson,mid+1,r,ql,qr));
	return res;
}

int query_(int x,int y)
{
	int res=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		res = max(res,query(1,1,n,dfn[top[x]],dfn[x]));
		x = fa[top[x]];
	}
	if(dep[x]<dep[y])
		swap(x,y);
	res = max(res,query(1,1,n,dfn[y]+1,dfn[x]));
	return res;
}

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		dsu[i] = i;
	for(int i=1;i<=m&&scanf("%lld%lld%lld",xx+i,yy+i,zz+i);i++)
	{
		int fx=find_(xx[i]),fy=find_(yy[i]);
		if(fx!=fy)
		{
			dsu[fy] = fx;
			addedge(xx[i],yy[i],zz[i]), addedge(yy[i],xx[i],zz[i]);
			tr[i] = 1;
		}
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs1(i,0), dfs2(i,i);
	for(int i=1;i<=m;i++)
	{
		if(tr[i])
		{
			puts("YES");
			continue;
		}
		if((sum[xx[i]]^sum[yy[i]]^zz[i])==1 && query_(xx[i],yy[i])==0)
		{
			puts("YES");
			modify_(xx[i],yy[i]);
		}
		else
			puts("NO");
	}
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：_LPF_ (赞：1)

> 给定 $n$ 个点，一开始没有连边，然后给定 $m$ 个询问尝试不断加边，边权只能是 $0/1$。
>
> 若加边之后，图中所有简单环（没有重复顶点的环）的异或和为 $1$​ 即可加入，否则不能加入。
>
> 对于每个询问输出 `YES/NO` 表示能否加边。

比较有思维难度。

针对环相关的问题，有一种套路：离线下来，首先得到一颗生成树，这样可以很方便的考虑环的问题。

求出生成树，那么首先树上的边是一定可行的，因为这条边加入时不与任何边成简单环。

然后考虑非树边，显然只要这条非树边构成的环不与任何其它环相交即可。

若相交则一定出现 $0$ 环，这个环是两个相交的环分别去掉相交部分，然后重新构成的环。

判断方法很多，可以考虑转化成 树上区间加 & 区间最大值，直接树剖维护即可，复杂度 $O(m\log^2 n)$。 

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 3e5 + 10, M = 5e5 + 10;
int n, m, cnt, st[N], val[N], head[N];
bool vis[M];
struct edge{int u, v, w;} G[M];
struct Edge{int nxt, to, val;} ed[N << 1];

int read(){
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? -1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

int Get(int x){
	if(x == st[x]) return x;
	return st[x] = Get(st[x]);
}

void add(int u, int v, int w){
	ed[++ cnt] = (Edge){head[u], v, w}; head[u] = cnt;
	ed[++ cnt] = (Edge){head[v], u, w}; head[v] = cnt; 
}

int tot, fa[N], id[N], son[N], sz[N], top[N], dep[N];

void dfs1(int u, int Fa){
	fa[u] = Fa, dep[u] = dep[Fa] + 1, sz[u] = 1;
	for(int i = head[u], v; i; i = ed[i].nxt)
		if((v = ed[i].to) != Fa){
			val[v] = val[u] ^ ed[i].val;
			dfs1(v, u);
			sz[u] += sz[v];
			if(!son[u] || sz[v] > sz[son[u]]) son[u] = v;
		}
}

void dfs2(int u, int Top){
	top[u] = Top, id[u] = ++ tot;
	if(!son[u]) return;
	dfs2(son[u], Top);
	for(int i = head[u], v; i; i = ed[i].nxt)
		if((v = ed[i].to) != fa[u] && v != son[u]) dfs2(v, v);
}

int dat[N << 2], cov[N << 2];

void Push_Down(int p){
	if(!cov[p]) return;
	int l = p << 1, r = p << 1 | 1;
	dat[l] = cov[l] = cov[p];
	dat[r] = cov[r] = cov[p];
	cov[p] = 0;
}

int Query(int p, int l, int r, int L, int R){
	if(L <= l && r <= R) return dat[p];
	Push_Down(p);
	int mid = (l + r) >> 1;
	if(L <= mid && Query(p << 1, l, mid, L, R)) return 1;
	if(R  > mid && Query(p << 1 | 1, mid + 1, r, L, R)) return 1;
	return 0; 
}

void Update(int p, int l, int r, int L, int R, int v){
	if(L <= l && r <= R) {dat[p] = cov[p] = v; return;}
	Push_Down(p);
	int mid = (l + r) >> 1;
	if(L <= mid) Update(p << 1, l, mid, L, R, v);
	if(R >  mid) Update(p << 1 | 1, mid + 1, r, L, R, v);
	dat[p] = max(dat[p << 1], dat[p << 1 | 1]);
}

bool Ask(int x, int y){
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		if(Query(1, 1, n + 1, id[top[x]], id[x])) return true;
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	if(id[x] + 1 <= id[y] && Query(1, 1, n + 1, id[x] + 1, id[y])) return true;
	return false;
}

void Modify(int x, int y){
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		Update(1, 1, n + 1, id[top[x]], id[x], 1);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	if(id[x] + 1 <= id[y]) Update(1, 1, n + 1, id[x] + 1, id[y], 1);
}

int main(){
	n = read(), m = read();
	for(int i = 1; i <= n; i ++) st[i] = i;
	for(int i = 1; i <= m; i ++){
		int u = read(), v = read(), w = read();
		G[i] = (edge){u, v, w};
		int fu = Get(u), fv = Get(v);
		if(fu != fv)
			vis[i] = true, add(u, v, w), st[fu] = fv;
	}
	for(int i = 1; i <= n; i ++)
		if(!dep[i]) dfs1(i, 0), dfs2(i, i);
	
	for(int i = 1; i <= m; i ++){
		if(vis[i]) {puts("YES"); continue;}
		int u = G[i].u, v = G[i].v;
		int w = val[u] ^ val[v] ^ G[i].w;
		if(!w) {puts("NO"); continue;}

		if(Ask(u, v))
			puts("NO");
		else
			Modify(u, v), puts("YES");
	}
	return 0;
}
```



---

## 作者：cirnovsky (赞：1)

来一个不用 HLD / LCT 的做法。~~其实没有什么本质上的差别~~

首先容易想到离线，并且满足条件的图一定是边仙人掌，我们把离线后得到的图缩点，形成一片森林，并且标记树边。树边显然必选，主要来看非树边。

维护 $pre(x)$ 表示从根到 $x$ 的边权异或和，设当前我们考虑的非树边是 $(x,y)$，那么如果 $x,y$ 已经处于同一个环里或者 $pre(x)\oplus pre(y)\oplus w(x,y)\neq1$ 是不行的，否则就可以加进去。

然后怎么实现查找是否在同一个环里之类的就用 time-stamp & BIT 解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300100,M=500100;
int n,m,ix[M],iy[M],iw[M],sjc,fa[20][N],indfn[N],outdfn[N],tag[M],dep[N],pre[N];
vector<pair<int,int>> G[N];
void dfs(int x,int las)
{
	fa[0][x]=las;
	indfn[x]=++sjc;
	dep[x]=dep[las]+1;
	for(int i=1; i<20; ++i) fa[i][x]=fa[i-1][fa[i-1][x]];
	for(auto [y,w]:G[x])	if(y!=las)	pre[y]=pre[x]^w,dfs(y,x);
	outdfn[x]=sjc;
}
int fwk[N];
void ins(int x,int y) { for(; x<=n; x+=x&-x)	fwk[x]+=y; }
int find(int x)
{
	int res=0;
	for(; x; x-=x&-x)  res+=fwk[x];
	return res;
}
int lh[N];
int dsuFind(int x)
{
	while(x!=lh[x])	x=lh[x]=lh[lh[x]];
	return x;
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y])	swap(x,y);
	for(int i=19; ~i; --i)	if(dep[fa[i][x]]>=dep[y])	x=fa[i][x];
	if(x==y)	return x;
	for(int i=19; ~i; --i)	if(fa[i][x]!=fa[i][y])	x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	iota(lh+1,lh+n+1,1);
	for(int i=1; i<=m; ++i)
	{
		cin>>ix[i]>>iy[i]>>iw[i];
		int x=dsuFind(ix[i]),y=dsuFind(iy[i]);
		if(x!=y)
		{
			G[ix[i]].emplace_back(iy[i],iw[i]);
			G[iy[i]].emplace_back(ix[i],iw[i]);
			tag[i]=1,lh[x]=y;
		}
	}
	for(int i=1; i<=n; ++i)	if(!dep[i])	dfs(i,0);
	for(int i=1; i<=m; ++i)
	{
		if(tag[i])	cout<<"YES\n";
		else
		{
			int x=ix[i],y=iy[i];
			if(find(indfn[x])+find(indfn[y])-find(indfn[LCA(x,y)])*2>0||(pre[x]^pre[y]^iw[i])!=1)	cout<<"NO\n";
			else
			{
				cout<<"YES\n";
				while(x!=y)	(dep[x]<dep[y])&&(x^=y^=x^=y),ins(indfn[x],1),ins(outdfn[x]+1,-1),x=fa[0][x];
			}
		}
	}
	return 0;
}
```

---

## 作者：摸鱼酱 (赞：0)

大致题意：初始有一张 $n$ 个点，没有边的无向图。$m$ 次询问加入一条 $u_i,v_i$ 之间权值为 $w_i\in\{0,1\}$ 的边，若加入之后图上不存在路径权值异或和是 $0$ 的简单环，则成功加入，否则不加入。求每次是否成功加入了给定的边。

$3\leq n\leq 3\times 10^5$，$1\leq m\leq 5\times 10^5$。

提供一种两只 $\log$ 的树剖做法。

先 **离线**，顺次遍历每条边，若它连接了两个连通块，则这条边 **必定** 会加入，于是把这些边拉出来加入，得到一个森林。

考虑剩余的边能够成功加入的条件。

- 加入后直接构成的简单环异或和为 $1$；
- 加入后直接构成的简单环不与已经存在的简单环有共边，即不能形成"环套环"。

第一条很显然，可以画图理解第二条。

![](https://cdn.jsdelivr.net/gh/moyujiang/piccdn@a3c16d4c31b16ec09657461c754a7600831eb7cc/2021/07/31/e1afd7a74f49af52a4ebff646e33ed03.png)

可以把这里的边看作一条路径。

假设构成了一个这样的环套环，并且 $1-2-3,2-3-4$ 两个环都满足路径权值异或和为 $1$，那么考查大环 $1-2-4-3$ 的权值：

- $2-3$ 路径权值异或和为 $1$，则 $1-2,1-3$ 与 $2-4,3-4$ 的异或和都是 $0$，大环的异或和为 $0$；
- $2-3$ 路径权值异或和为 $0$，则 $1-2,1-3$ 与 $2-4,3-4$ 的异或和都是 $1$，大环的异或和为 $0$。

于是无论如何，都会使得大环的异或和为 $0$，不满足题意。

所以现在需要判断的东西变为了，求树上一条路径是否完全没有被覆盖，以及覆盖一条树上路径。

这个树剖一下，线段树维护区间加，区间求和就好了，时间复杂度 $O(m\log ^2n)$。

代码为了好写，直接写成比较习惯的区间赋值了，其它实现也比较不精细，反正 cf 不卡常，将就着看一下就好（

[code](https://www.luogu.com.cn/paste/f6y4h9fr)

---

## 作者：LTb_ (赞：0)

称权值异或和为 $1$ 的简单环为合法的环。

假设两个合法的环有至少一条公共边，那么考虑它们组成的大环的权值：每条公共边上的权值相同可以抵消，其他边上的权值异或和相同，也抵消，则大环的权值为 $0$——显然这两个环组成的大环不是合法的，所以原图一定是一个仙人掌状物。

然后考虑仙人掌是个什么样的东西：对它建出 DFS 树，每条非树边连接的两个点 在树上所形成的链 互不相交。那么把询问离线，用并查集维护，先建出这棵 DFS 树，然后对于每条非树边判断是否合法。具体来说，判断：

1. 链上是否有边已经被另一条非树边覆盖
2. 这条非树边所形成的环是否合法

可以用树剖 + 树状数组 / 线段树，需要实现链修改链查询。于是我们得到了一个 $\mathcal O(n \log ^2 n)$ 的做法。

$\mathcal O(n \log ^2 n)$ 实现得不太好的话会被卡常，所以讲个好写的 $\mathcal O(n \log n)$ 做法。

注意到每条边最多会被覆盖一次，所以修改链的时候可以暴力单点修改，于是问题变成了单点修改链查询。链查询还是得写树剖，所以树上差分一下变成子树修改单点查询，跑一遍 DFS 序，树状数组维护就行了。

值得注意的是这个图不一定连通，原图可能是一堆仙人掌。这个东西实际并不难处理，预处理 LCA 和 DFS 序的时候，对于每个连通块都跑一遍 DFS 就行了。

```c++
// 2021.07.31 - 09:09
// Code by LTb
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ll long long
#define debug printf("Passing Line %d in function [%s].\n",__LINE__,__FUNCTION__)
#define fi first
#define se second
inline int read(){
    int x=0,f=1;
    char ch='.';
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
inline void chmax(int &x,int y){x=max(x,y);}
inline void chmin(int &x,int y){x=min(x,y);}

const int MOD = 998244353;
inline int add(int x,int y){return(x+y>=MOD)?(x+y-MOD):((x+y<0)?(x+y+MOD):(x+y));}

const int MAXN = 300005, MAXM = 500005;

// data
int n, q;
int fr[MAXM], to[MAXM], val[MAXM];
vector<int> G[MAXN], H[MAXN];
bool ans[MAXM];
bool vis[MAXN];

// lca
int dep[MAXN];
int fa[23][MAXN];

void dfs1(int p, int par) {
	fa[0][p] = par;
	for (int i = 1; i <= 20; i++)
		fa[i][p] = fa[i - 1][fa[i - 1][p]];

	for (int i : G[p]) {
		if (i != par) {
			dep[i] = dep[p] + 1;
			dfs1(i, p);
		}
	}
}

int lca(int x, int y) {
	if (dep[x] < dep[y])
		swap(x, y);

	for (int i = 20; i >= 0; i--)
		if (dep[fa[i][x]] >= dep[y]) x = fa[i][x];
	if (x == y) return x;

	for (int i = 20; i >= 0; i--)
		if (fa[i][x] != fa[i][y])
			x = fa[i][x], y = fa[i][y];

	return fa[0][x];
}

// dsu
int dsu_fa[MAXN];
inline int find(int x) {
	if (dsu_fa[x] == x) return x;
	return dsu_fa[x] = find(dsu_fa[x]);
}

// dfs_rank
int dfn[MAXN], id[MAXN], siz[MAXN];
int s[MAXN], a[MAXN];
int ind;
void dfs2(int p, int f) {
	siz[p] = 1;
	dfn[p] = ++ind;
	id[ind] = p;

	for (int j = 0; j < G[p].size(); j++) {
		int i = G[p][j], w = H[p][j];
		if (i == f) continue;

		s[i] = s[p] + w;
		dfs2(i, p);
		siz[p] += siz[i];
	}
}

// bit
struct BIT {
	int tree[MAXN];
	int max_value;

	inline int lowbit(int x) {
		return x & (-x);
	}

	inline void add(int x, int c) {
		while (x <= max_value + 1) {
			tree[x] += c;
			x += lowbit(x);
		}
	}

	inline int qry(int x) {
		int ans = 0;
		while (x > 0) {
			ans += tree[x];
			x -= lowbit(x);
		}
		return ans;
	}

	inline int qry2(int l, int r) {
		return qry(r) - qry(l - 1);
	}

	inline void add2(int l, int r, int c) {
		add(l, c);
		add(r + 1, -c);
	}
}t1;

inline void upd(int x, int y, int l) {
	while (x != l) {
		t1.add2(dfn[x], dfn[x] + siz[x] - 1, 1);
		x = fa[0][x];
	}

	while (y != l) {
		t1.add2(dfn[y], dfn[y] + siz[y] - 1, 1);
		y = fa[0][y];
	}
}

signed main()

{
	n = read(), q = read();
	for (int i = 1; i <= n; i++)
		dsu_fa[i] = i;

	for (int i = 1; i <= q; i++) {
		fr[i] = read(), to[i] = read(), val[i] = read();
		int x = find(fr[i]), y = find(to[i]);
		if (x != y) {
			ans[i] = true;
			dsu_fa[x] = y;
			G[fr[i]].push_back(to[i]), H[fr[i]].push_back(val[i]);
			G[to[i]].push_back(fr[i]), H[to[i]].push_back(val[i]);
		}
	}

	for (int i = 1; i <= n; i++) {
		if (!vis[find(i)]) {
			vis[find(i)] = true;
			dfs1(i, i);
			dfs2(i, i);
		}
	}

	t1.max_value = n;
	for (int i = 1; i <= q; i++) {
		if (ans[i]) continue;
		int x = fr[i], y = to[i];

		int l = lca(x, y);
		int v1 = s[x] + s[y] - 2 * s[l] + val[i];
		int v2 = t1.qry(dfn[x]) + t1.qry(dfn[y]) - 2 * t1.qry(dfn[l]);
		if (v2 == 0 && v1 % 2 == 1) {
			ans[i] = true;
			upd(x, y, l);
		}
	}

	for (int i = 1; i <= q; i++) {
		if (ans[i]) puts("YES");
		else puts("NO");
	}
	return 0;
}
```



---

