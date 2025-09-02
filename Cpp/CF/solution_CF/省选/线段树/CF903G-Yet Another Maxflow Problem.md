# Yet Another Maxflow Problem

## 题目描述

In this problem you will have to deal with a very special network.

The network consists of two parts: part $ A $ and part $ B $ . Each part consists of $ n $ vertices; $ i $ -th vertex of part $ A $ is denoted as $ A_{i} $ , and $ i $ -th vertex of part $ B $ is denoted as $ B_{i} $ .

For each index $ i $ ( $ 1<=i<n $ ) there is a directed edge from vertex $ A_{i} $ to vertex $ A_{i+1} $ , and from $ B_{i} $ to $ B_{i+1} $ , respectively. Capacities of these edges are given in the input. Also there might be several directed edges going from part $ A $ to part $ B $ (but never from $ B $ to $ A $ ).

You have to calculate the [maximum flow value](https://en.wikipedia.org/wiki/Maximum_flow_problem) from $ A_{1} $ to $ B_{n} $ in this network. Capacities of edges connecting $ A_{i} $ to $ A_{i+1} $ might sometimes change, and you also have to maintain the maximum flow value after these changes. Apart from that, the network is fixed (there are no changes in part $ B $ , no changes of edges going from $ A $ to $ B $ , and no edge insertions or deletions).

Take a look at the example and the notes to understand the structure of the network better.

## 说明/提示

This is the original network in the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF903G/dcc7a52e873b883e6fea740d5c4aff84e5c0da8d.png)

## 样例 #1

### 输入

```
4 3 2
1 2
3 4
5 6
2 2 7
1 4 8
4 3 9
1 100
2 100
```

### 输出

```
9
14
14
```

# 题解

## 作者：Soulist (赞：20)

非常妙的一道题

首先它给的图非常的有性质，$A_i$向$A_{i+1}$连了一条边，然后$B_i$向$B_{i+1}$连一条边，然后$A$向$B$内任意连边，存在边权

我们可以注意到按照最小割的性质，假设我们割了$A_i->A_{i+1}$这一条边，那么我们一定不会割去$A_u->A_{u+1}(u>i)$这一条边，这是因为$A_u$到$A_{u+1}$已经没法再连向$A_1$了

由于上述的结论，不妨假设割去$A_x->A_{x+1}$是最小割的一条割边，那么显然我们不会割去$A_{(i<x)}->A_{i+1}$这条边，否则我们割去那条边就不会再割去$A_x->A_{x+1}$这条边了，于是有我们会割且仅割去一条$A_{i}->A_{i+1}$的边

同理，我们也可以得到我们会割且仅割去一条$B_{i}->B_{i+1}$这样的一条边

我们令割去的$A_u->A_{u+1},B_v->B_{v+1}$为二元组$(u,v)$造成的贡献，令其边权为$a_u,b_v$，令连接$A,B$间的边边权为$c$

那么显然有

$$cost_{u,v}=a_u+b_v+\sum_{i\le u\&j>v}c_{i,j}$$

我们可以发现对于一个$u$，其最优的$v$是固定的

即使是修改也仅仅是单点改$a_i$，所以即使修改也不会对后面那一坨造成影响qwq

令对于一个$u$最优的后面那一坨的权值为$p_u$

于是修改就是改$a_u$求$(a_u+p_u)_{min}$

考虑求解$p_u$

对$b$开一颗线段树，考虑一次求解$u=1...n$时的$p_u$

那么每次$u$增大就只需要修改不同$b$的权值即可，线段树常规操作qwq

当然这道题有那么一点点弟弟在于，，，它可能不删掉任何一条$A$边/$B$边，这就导致其非常的$\rm naive$

所以我们还要两条边权为$0$的边来特判这两种情况...

因为实在是讲不清了~~懒癌晚期~~，所以还是看代码吧...

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define re register
#define ls(x) x * 2
#define rs(x) x * 2 + 1
#define inf 1e17
#define int long long
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 2e5 + 5 ; 
int n, m, q, A[N], B[N], C[N] ; 
int head[N], cnt ; 
struct E { int to, next, w ; } e[N * 2] ;
struct Tr { int mi, tag ; } tr[N * 4] ;
inline void add( int x, int y, int z ) {
	e[++ cnt] = (E){ y, head[x], z }, head[x] = cnt ; 
}
inline void build( int x, int l, int r ) {
	if( l == r ) { tr[x].mi = B[l] ; return ; }
	int mid = ( l + r ) >> 1 ; 
	build( ls(x), l, mid ), build( rs(x), mid + 1, r ) ;
	tr[x].mi = min( tr[ls(x)].mi, tr[rs(x)].mi ) ;
}
inline void pushmark( int x ) {
	if( tr[x].tag )
		tr[ls(x)].mi += tr[x].tag, tr[rs(x)].mi += tr[x].tag, 
		tr[ls(x)].tag += tr[x].tag, tr[rs(x)].tag += tr[x].tag, 
		tr[x].tag = 0 ;
}
inline void update( int x, int l, int r, int ql, int qr, int w ) {
	if( ql > r || qr < l ) return ; 
	if( ql <= l && r <= qr ) { tr[x].mi += w, tr[x].tag += w ; return ; }
	int mid = ( l + r ) >> 1 ; pushmark(x) ; 
	update( ls(x), l, mid, ql, qr, w ), update( rs(x), mid + 1, r, ql, qr, w ) ;
	tr[x].mi = min( tr[ls(x)].mi, tr[rs(x)].mi ) ; 
}
void Init() {
	build( 1, 1, n ) ; 
	rep( x, 1, n ) {
		Next( i, x ) update( 1, 1, n, 1, e[i].to, e[i].w ) ;
		C[x] = tr[1].mi ; 
	}
	memset( tr, 0, sizeof(tr) ) ;
	rep( i, 1, n ) B[i] = A[i] + C[i] ; 
	build( 1, 1, n ) ;
}
signed main()
{
	n = read(), m = read(), q = read() ; int x, y, z ; 
	rep( i, 2, n ) A[i - 1] = read(), B[i] = read() ; B[1] = 0 ;
	rep( i, 1, m ) {
		x = read(), y = read(), z = read(), add( x, y, z ) ;
	}
	Init() ; printf("%I64d\n", tr[1].mi );
	rep( i, 1, q ) {
		x = read(), z = read() ; 
		update( 1, 1, n, x, x, z - A[x] ), A[x] = z ; 
		printf("%I64d\n", tr[1].mi ) ; 
	}
	return 0 ;
}
```

---

## 作者：skylee (赞：5)

# [CF903G]Yet Another Maxflow Problem

### 题目大意：

有$A$类点和$B$类点各$n(n\le2\times10^5)$个，所有$A_i$到$A_{i+1}$有一条权值为$a_i$的有向边，所有$B_i$到$B_{i+1}$有一条权值为$b_i$的有向边，另有$m(m\le2\times10^5)$条从$A_x$到$B_y$的权值为有向边。连续$q(q\le2\times10^5)$次操作将$A_{v_i}$与$A_{v_i+1}$之间的边的权值改为$w_i$。问每次修改完毕后的从$A_1$到$B_n$的最大流。

### 思路：

根据最大流-最小割定理，题目所求相当于每次修改完毕后的最小割。定义$A$类点间的边为$A$类边，$B$类点间的边为$B$类边，$AB$类点间的边为$C$类边。假设两类边各$n-1$条之外还分别有一个边权为$0$的边，那么每次的最小割一定恰好包含一个$A$类边、一个$B$类边和若干$C$类边。由于$B$类边和$C$类边都不会被修改，则对于同一个$A$类边，对应的最优的$B$类边是固定的。方便起见，下文将$B_i$到$B_{i+1}$的边记作$b_{i+1}$，不同于题面描述。

考虑预处理每个$A$类边对应的最优$B$类边。不难发现，若我们选择了$a_i$和$b_j$两条边，要使得$A_1$与$B_n$不连通，则我们还需要割去所有连接$A_x,B_y(x\le i,y\ge j)$的$C$类边，而这也是选择$a_i$和$b_j$后的最小割。反过来说，连接$A_x,B_y$的$C$类边会对$a_i,b_j(x\le i,y\ge j)$的选择产生影响。因此我们可以$1\sim n$枚举每个$a_i$，用线段树维护对应每个$b_j$所需要的最小割的大小。首先将所有$b_j$加入到线段树中，对于当前枚举到的$a_i$，枚举从$A_i$出发的所有$C$类边，若对应的点为$B_j$，权值为$w$，将区间$[1,j]$加上$w$，表示对于$a_i$及$a_i$以后的$A$类边，若还要考虑$b_j$及$b_j$以前的$B$类边作为对应边，一定要割去这条$C$类边。而每次插入后线段树最小元素就是对应当前$a_i$，由一个$B$类边和若干$C$类边组成的、能与$a_i$构成割的边权和，记这一边权和为$sum$，则选择$a_i$时的最小割为$sum+a_i$，记作$c_i$。

考虑修改操作，由于$a_i$对应的$B$类边和$C$类边已经确定，每次修改时$a_i$的变化也就是$c_i$的变化。用一些数据结构维护所有$c_i$的最小值即可。时间复杂度$\mathcal O((m+q)\log n)$。

### 源代码：

```cpp
#include<cstdio>
#include<cctype>
#include<vector>
using int64=long long;
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
constexpr int N=2e5+1;
int64 a[N],b[N],c[N];
using Edge=std::pair<int,int>;
std::vector<Edge> e[N];
class SegmentTree {
	#define _left <<1
	#define _right <<1|1
	private:
		int64 val[N<<2],tag[N<<2];
		void push_up(const int &p) {
			val[p]=std::min(val[p _left],val[p _right]);
		}
		void push_down(const int &p) {
			if(!tag[p]) return;
			val[p _left]+=tag[p];
			val[p _right]+=tag[p];
			tag[p _left]+=tag[p];
			tag[p _right]+=tag[p];
			tag[p]=0;
		}
	public:
		void build(const int &p,const int &b,const int &e,const int64 arr[]) {
			tag[p]=0;
			if(b==e) {
				val[p]=arr[b];
				return;
			}
			const int mid=(b+e)>>1;
			build(p _left,b,mid,arr);
			build(p _right,mid+1,e,arr);
			push_up(p);
		}
		void modify(const int &p,const int &b,const int &e,const int &l,const int &r,const int64 &v) {
			if(b==l&&e==r) {
				val[p]+=v;
				tag[p]+=v;
				return;
			}
			push_down(p);
			const int mid=(b+e)>>1;
			if(l<=mid) modify(p _left,b,mid,l,std::min(mid,r),v);
			if(r>mid) modify(p _right,mid+1,e,std::max(mid+1,l),r,v);
			push_up(p);
		}
		int64 query() const {
			return val[1];
		}
	#undef _left
	#undef _right
};
SegmentTree t;
int main() {
	const int n=getint(),m=getint(),q=getint();
	for(register int i=1;i<n;i++) {
		a[i]=getint(),b[i+1]=getint();
	}
	t.build(1,1,n,b);
	for(register int i=0;i<m;i++) {
		const int u=getint(),v=getint(),w=getint();
		e[u].push_back({v,w});
	}
	for(register int x=1;x<=n;x++) {
		for(register auto &j:e[x]) {
			const int &y=j.first,&w=j.second;
			t.modify(1,1,n,1,y,w);
		}
		c[x]=t.query()+a[x];
	}
	t.build(1,1,n,c);
	printf("%lld\n",t.query());
	for(register int i=0;i<q;i++) {
		const int x=getint(),v=getint();
		t.modify(1,1,n,x,x,v-a[x]);
		a[x]=v;
		printf("%lld\n",t.query());
	}
	return 0;
}
```



---

## 作者：pidan (赞：3)

## Solution CF903G Yet Another Maxflow Problem
[题目链接](https://codeforces.com/problemset/problem/903/G)

题意描述
>给定一张图，左右各$n$个节点，$A_i\to A_{i+1}$连边，$B_i\to B_{i+1}$​连边，容量给出。
>有$m$对$A_i\to B_j$​有边，容量给出。
>你需要先求出原图从$A_1$到$B_n$的最大流，然后有$q$次操作，每次操作给出$i$，先修改$A_i\to A_{i+1}$的边的容量，然后询问从$A_1$到$B_n$的最大流。

Solution：

显然最大流先转最小割，则考虑割掉哪些边最优。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF903G/dcc7a52e873b883e6fea740d5c4aff84e5c0da8d.png)

可以发现，割边有四种选择：左部链上割or不割，右部链上割or不割，乘法原理得到四种选择。

我们不希望过多的分类讨论，因此可以在$A_1$上面增加一条边表示左部不割边，在$B_n$下面增加一条边表示右部不割边。那么问题就是在左部割若干条边，右部割若干条边，再割掉中间与$A_1,B_n$连通的边，求所有方案最小代价。

在左部或右部同时割掉多条边显然是不优的，因为只有断掉的与$A_1,B_n$最近的边产生了割的效果，于是问题可以抽象为一个式子：

$$Min\{A_x+B_y+\sum\limits_{u,v\in E,u<x,v\geq y}W(u,v)\}$$

此时回到题目：$q$次操作，每次操作给出$i$，先修改$A_i\to A_{i+1}$的边的容量，然后询问从$A_1$到$B_n$的最大流。

注意到修改仅在左部进行，因此对于割掉一条左部边$A_x\to A_{x+1}$，所对应的
$$B_y+\sum\limits_{u,v\in E,u<x,v\geq y}W(u,v)$$
是不变的。考虑使用线段树，将$B$放到线段树上，从$1$到$n$加入$A_x$，每到一个新点就枚举该点的边集$E(x,v)$，在线段树上对应区间$v\sim n$进行区间加，然后求全局最小值。求完后将
$$Min\{A_x+B_y+\sum\limits_{u,v\in E,u<x,v\geq y}W(u,v)\}$$
放入一棵新的线段树，之后的操作就是单点修改$+$全局最小值，直接维护即可。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
#define N 200005
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define pii pair<int,int>
#define il inline
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
il int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
struct Edge{
	int next,to,val;
}edge[N];
int n,m,q;
int head[N],num;
int A[N],B[N],res[N];
void add(int u,int v,int w){
	edge[++num].next=head[u];
	edge[num].to=v;
	edge[num].val=w;
	head[u]=num;
}
namespace SGT{
	int Min[N<<2],Tag[N<<2];
	void pushup(int k){Min[k]=min(Min[ls],Min[rs]);}
	void pushdown(int k){
		if(!Tag[k])return;
		Min[ls]+=Tag[k];Min[rs]+=Tag[k];
		Tag[ls]+=Tag[k];Tag[rs]+=Tag[k];
		Tag[k]=0;
	}
	void build(int k,int l,int r){
		Tag[k]=0;
		if(l==r){
			Min[k]=B[l];
			return;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(k);
	}
	void modify(int k,int l,int r,int x,int y,int val){
		if(l>=x&&r<=y){
			Min[k]+=val;
			Tag[k]+=val;
			return;
		}
		pushdown(k);
		if(x<=mid)modify(ls,l,mid,x,y,val);
		if(mid<y)modify(rs,mid+1,r,x,y,val);
		pushup(k);
	}
}
signed main(){
	n=read();m=read();q=read();
	for(int i=2;i<=n;i++)A[i-1]=read(),B[i]=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w);
	}
	SGT::build(1,1,n);
	for(int i=1;i<=n;i++){
		for(int j=head[i];j;j=edge[j].next){
			int v=edge[j].to,w=edge[j].val;
			SGT::modify(1,1,n,1,v,w);
		}
		res[i]=SGT::Min[1];
	}
	for(int i=1;i<=n;i++)B[i]=res[i]+A[i];
	SGT::build(1,1,n);
	printf("%lld\n",SGT::Min[1]);
	while(q--){
		int x=read(),val=read();
		SGT::modify(1,1,n,x,x,val-A[x]);
		A[x]=val;
		printf("%lld\n",SGT::Min[1]);
	}
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：2)

[CF903G Yet Another Maxflow Problem](https://www.luogu.com.cn/problem/CF903G)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/18079174)

神奇的模拟最小割。（？）[另一道类似的题](https://www.luogu.com.cn/problem/CF1861F)

暴力流显然跑不过。考虑最大流等于最小割，考虑割去那些边使得 $a_1,b_n$ 不连通。

一个重要的性质是 $A$ 链上和 $B$ 链上都最多只会删一条边。原因很显然，如果删了很多条边，可以只保留 $A$ 中最靠前的边和 $B$ 中最靠后的边。为了方便处理，设连接 $A_i,A_{i+1}$ 的边编号为 $i$，连接 $B_i,B_{i+1}$ 的边编号为 $i+1$，所以编号为 $an,b0$ 的边的边权为 $0$。

如果断了 $ai$ 和 $bj$ 条边，中间的边需要断掉的是 $x_i\leq ai\wedge y_i\geq b_j$ 的所有边。所以扫描线扫描断开 $A$ 的边的编号，同时维护 $f_i$ 表示假设此时断开 $bi$ 边的代价。

$f_i$ 的初值即为 $B_i$。当扫到一条边 $(x,y,z)$ 时，需要做的是 $[1,y]$ 前缀加 $z$，还需要求全局最小值，线段树维护即可，这样可以求出 $g_i$ 表示断 $ai$ 条边的最小代价为 $A_i+g_i$。

对于修改，就是单点修改，查询全局最大值。可以用堆维护，这里直接偷懒线段树废物再利用了/tx/tx。复杂度是 $\mathcal O((m+q)\log n)$。

```cpp
	int n,m,q,a[200010],b[200010],v[200010];
	vector<pii> ve[200010];
	namespace Segment
	{
		#define ls(x) (t[x].l+t[x].r)
		#define rs(x) ((t[x].l+t[x].r)^1)
		struct{int l,r,v,tg;}t[400010];
		inline void update(int x){t[x].v=min(t[ls(x)].v,t[rs(x)].v);}
		inline void down(int x,int y){t[x].tg+=y,t[x].v+=y;}
		inline void spread(int x){down(ls(x),t[x].tg),down(rs(x),t[x].tg),t[x].tg=0;}
		void build(int p,int l,int r)
		{
			t[p].l=l,t[p].r=r,t[p].tg=0;
			if(l==r)return t[p].v=v[l],void();
			int mid=l+((r-l)>>1);
			build(ls(p),l,mid),build(rs(p),mid+1,r),update(p);
		}
		void modify(int p,int l,int r,int x)
		{
			if(l<=t[p].l&&r>=t[p].r)return down(p,x);
			spread(p);
			if(l<=t[ls(p)].r)modify(ls(p),l,r,x);
			if(r>t[ls(p)].r)modify(rs(p),l,r,x);
			update(p);
		}
	}
	using namespace Segment;
	inline void mian()
	{
		read(n,m,q);int x,y,z;
		for(int i=1;i<n;++i)read(a[i],b[i]),v[i+1]=b[i];
		while(m--)read(x,y,z),ve[x].eb(mp(y,z));
		build(1,1,n);
		for(int i=1;i<=n;++i)
		{
			for(auto p:ve[i])modify(1,1,p.fi,p.se);
			v[i]=a[i]+t[1].v;
		}
		build(1,1,n),write(t[1].v,'\n');
		while(q--)read(x,y),modify(1,x,x,y-a[x]),a[x]=y,write(t[1].v,'\n');
	}
```

---

## 作者：Purslane (赞：1)

# Solution

考虑这些边的形态是不会发生改变的，改变的只有边的容量大小。而且这个图的形态很特殊，直接像一般图一样跑最大流比较浪费。

考虑把最大流问题转化为最小割问题。看一张图。

![](https://s11.ax1x.com/2023/12/28/piLmjE9.png)

两个蓝色分别指的是左部和右部（允许我这么叫，虽然我知道他不是二分图）离起点终点最近的断边。而只有如图浅紫色的部分的边才必须要断掉。

因此如果我们知道了左部要断那条边，中间浅紫色的边和右部的边最小割中的部分是确定的。这些可以使用数据结构预处理（扫描线）。

于是你就变成了单点修改区间最值问题。线段树可做。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,q,x[MAXN],y[MAXN],tag[MAXN<<2],mn[MAXN<<2],val[MAXN],u[MAXN],v[MAXN],w[MAXN];
vector<int> edge[MAXN];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void push_down(int k,int l,int r) {return tag[lson]+=tag[k],tag[rson]+=tag[k],mn[lson]+=tag[k],mn[rson]+=tag[k],tag[k]=0,void();}
void update(int k,int l,int r,int x,int y,int v) {
	if(x<=l&&r<=y) return tag[k]+=v,mn[k]+=v,void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,v);
	if(y>mid) update(rson,mid+1,r,x,y,v);
	mn[k]=min(mn[lson],mn[rson]);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	ffor(i,1,n-1) cin>>x[i]>>y[i];
	ffor(i,1,m) cin>>u[i]>>v[i]>>w[i],edge[u[i]].push_back(i);
	ffor(i,1,n) update(1,1,n,i,i,y[i-1]);
	ffor(i,1,n) {
		for(auto id:edge[i]) update(1,1,n,1,v[id],w[id]);
		val[i]=mn[1];
	}
	memset(tag,0,sizeof(tag));
	memset(mn,0,sizeof(mn));
	ffor(i,1,n) update(1,1,n,i,i,val[i]+x[i]);
	cout<<mn[1]<<'\n';
	ffor(i,1,q) {
		int pos,v;
		cin>>pos>>v;
		update(1,1,n,pos,pos,v-x[pos]);
		x[pos]=v;
		cout<<mn[1]<<'\n';	
	}
	return 0;	
}
```

---

## 作者：Tyyyyyy (赞：1)

## CF903G
### 题意简述
有一张图，结构为 $A,B$ 两条长度为 $n$ 的链，再由 $A$ 向 $B$ 连了 $m$ 条边。$q$ 次操作，每次修改 $A$ 链上一条边的权值，求 $A_1\to B_n$ 的最大流。

$n,m,q\leq 2\times 10^5$。

### 题目分析
最大流转成最小割后，显然 $A,B$ 中的边只会各割掉一条。设我们割掉 $A$ 中的第 $i$ 条边，$B$ 中的第 $j$ 条边，那么就还需要割掉 $A$ 中第 $i$ 条边前面的点连到 $B$ 中第 $j$ 条边后面的点的边。

我们把“割掉 $A$ 中的第 $i$ 条边，$B$ 中的第 $j$ 条边”看作二维平面上的一个点 $(i,j)$，则不难发现本题的本质是若干次矩形加和查询全局最小值。然而，若我们使用离线后 cdq 分治的方法，会因为拆差分/扫描线太多而超时；若使用树套树，则会超空间。我们考虑发掘本题中操作的性质。

我们发现，修改操作只修改 $A$ 链上的边权。也就是说，$B$ 链上和 $A\to B$ 的边权所带来的矩形操作是在询问之前就确定了的。而考虑我们的二维平面，修改 $A$ 中的第 $i$ 条边会影响到所有的 $(i,j)$，也就是一列。既然所有的修改都是在一列中整体进行的，那就说明每一列的 **最小值位置** 不会发生改变。因此，我们可以先处理原来的边权带来的矩形加，预处理出每一列的最小值，再用线段树维护这 $n$ 列即可。

Code：（删除了头文件和快读）
```cpp
const int N=2e5+10;
int n,m,q,wa[N];
ll w[N];
vector<pii>e[N];
struct SegmentTree
{
	ll mn[N<<2],tag[N<<2];
	void pushup(int p){mn[p]=min(mn[p<<1],mn[p<<1|1]);}
	void pushdown(int p)
	{
		if(!tag[p])return;
		mn[p<<1]+=tag[p],tag[p<<1]+=tag[p];
		mn[p<<1|1]+=tag[p],tag[p<<1|1]+=tag[p];
		tag[p]=0;
	}
	void upd(int p,int l,int r,int L,int R,ll d)
	{
		if(L<=l&&r<=R){mn[p]+=d,tag[p]+=d;return;}
		pushdown(p);int mid=(l+r)>>1;
		if(L<=mid)upd(p<<1,l,mid,L,R,d);
		if(R>mid)upd(p<<1|1,mid+1,r,L,R,d);
		pushup(p);
	}
}sgt;
int main()
{
	read(n),read(m),read(q);
	for(int i=1,x;i<n;i++)read(wa[i]),read(x),sgt.upd(1,1,n,i+1,i+1,x);
	for(int i=1,x,y,z;i<=m;i++)
	{
		read(x),read(y),read(z);
		e[x].push_back({y,z});
	}
	for(int i=1;i<=n;i++)
	{
		for(auto p:e[i])sgt.upd(1,1,n,1,p.fi,p.se);
		w[i]=wa[i]+sgt.mn[1];
	}
	memset(sgt.mn,0,sizeof(sgt.mn));
	memset(sgt.tag,0,sizeof(sgt.tag));
	for(int i=1;i<=n;i++)sgt.upd(1,1,n,i,i,w[i]);
	write(sgt.mn[1]);
	for(int i=1,x,y;i<=q;i++)
	{
		read(x),read(y);
		sgt.upd(1,1,n,x,x,y-wa[x]),wa[x]=y;
		write(sgt.mn[1]);
	}
	IO::pchar(0);
	return 0;
}
```

---

## 作者：Corzica (赞：0)

先把题目中要求的最大流转成最小割，再来考虑这个最小割的形式。

显然，一个最小割一定是在 $A$ 上割一条边，在 $B$ 上割一条边，再把所有的起点在 $A$ 上割边前方，终点在 $B$ 上割边后方的边全部割掉（也可以选择不在 $A,B$ 上割）。

因为我们只会修改 $A$ 上边的权值，所以我们预先处理出来每一条 $A$ 上割边的最优方案。

我们建立一棵线段树，把在 $A,B$ 之间的割边按在 $A$ 上的顺序轮流加进来，每一条边的影响是对 $B$ 上割边在其前方的方案的代价加上其的权值。

预处理所有方案之后，每一次询问只需要更改线段树，查找最小值即可。

时间复杂度 $(m+q) \log n$。

因为偷懒所以常数究极大的代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#pragma GCC optimize(2)
using namespace std;
struct XDS {
	struct node {
		int l, r, minn, tag;
	} b[900005];
	inline void update(int p) {
		b[p].minn = min(b[2 * p].minn, b[2 * p + 1].minn);
	}
	inline void push_down(int p) {
		if (b[p].tag) {
			b[2 * p].minn += b[p].tag, b[2 * p + 1].minn += b[p].tag;
			b[2 * p].tag += b[p].tag, b[2 * p + 1].tag += b[p].tag;
			b[p].tag = 0;
		}
	}
	inline void build(int p, int l, int r) {
		b[p].l = l, b[p].r = r;
		b[p].minn = b[p].tag = 0;
		if (l == r) return;
		build(2 * p, l, (l + r) >> 1);
		build(2 * p + 1, ((l + r) >> 1) + 1, r);
	}
	inline void change(int p, int l, int r, int w) {
		if (b[p].l >= l && b[p].r <= r) {
			b[p].tag += w, b[p].minn += w;
			return;
		}
		push_down(p);
		int mid = (b[p].l + b[p].r) >> 1;
		if (r <= mid) change(2 * p, l, r, w);
		else if (l > mid) change(2 * p + 1, l, r, w);
		else change(2 * p, l, mid, w), change(2 * p + 1, mid + 1, r, w);
		update(p);
	}
	inline int query(int p, int l, int r) {
		if (b[p].l >= l && b[p].r <= r) {
			return b[p].minn;
		}
		push_down(p);
		int mid = (b[p].l + b[p].r) >> 1;
		if (r <= mid) return query(2 * p, l, r);
		else if (l > mid) return query(2 * p + 1, l, r);
		else return min(query(2 * p, l, mid), query(2 * p + 1, mid + 1, r));
	}
} t, tt;
int n, m, k, a[200005], b[200005], val[200005];
struct edge {
	int l, r, val;
} c[200005];
bool cmp(edge p, edge q) {
	return p.l < q.l;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i < n; i++) {
		cin >> a[i] >> b[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> c[i].l >> c[i].r >> c[i].val;
	}
	sort(c + 1, c + m + 1, cmp);
	int r = 1;
	t.build(1, 0, n - 1);
	for (int i = 1; i < n; i++) t.change(1, i, i, b[i]);
	tt.build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		while (c[r].l <= i && r <= m) {
			t.change(1, 0, c[r].r - 1, c[r].val);
			r++;
		}
		tt.change(1, i, i, a[i] + t.query(1, 0, n));
	}
	cout << tt.b[1].minn << "\n";
	int p, q;
	for (int i = 1; i <= k; i++) {
		cin >> p >> q;
		tt.change(1, p, p, q - a[p]);
		a[p] = q;
		cout << tt.b[1].minn << "\n";
	}
}
```

---

## 作者：happybob (赞：0)

比较好想，但是细节比较多。

我们考虑到最大流 $=$ 最小割，于是我们直接刻画最小割即可。

由于图的特殊性质，左侧 $i \rightarrow i+1$ 和右侧 $i \rightarrow i+1$ 在最小割必然至多只会割一次。

我们假设左侧选的是割 $i \rightarrow i+1$ 的边，右侧是 $j \rightarrow j+1$ 的边，$a_i$ 是左侧这条边容量，$b_i$ 是右侧这条边容量。则 $(i,j)$ 的结果是 $a_i+b_j+\sum \limits_{(x,y)|(x,y)\in E \land x \leq i \land y>j} c_{x,y}$。

又注意到，我们修改的仅仅是左侧 $i \rightarrow i+1$ 的边权，与中间和右侧无关，所以我们可以对于每个 $i$ 求出相对应的最小的 $j$，这显然可以从前往后使用线段树维护区间加全局 $\min$。

修改时只需要修改 $a_i$ 并维护全局 $\min$ 即可。

注意上述讨论都基于两边都割一条边，但事实上可以选择不割两边只割中间，割一边不割另一边。讨论一下即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e5 + 5;
using ll = long long;

int n, m, q;
ll a[N], b[N];

ll res[N];
vector<pair<int, ll>> v[N], vv[N];

class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		ll minn, tag;
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].minn = min(tr[u << 1].minn, tr[u << 1 | 1].minn);
	}
	void pushtag(int u, ll t)
	{
		tr[u].tag += t;
		tr[u].minn += t;
	}
	void pushdown(int u)
	{
		if (tr[u].tag)
		{
			pushtag(u << 1, tr[u].tag);
			pushtag(u << 1 | 1, tr[u].tag);
			tr[u].tag = 0;
		}
	}
	void build(int u, int l, int r, ll *b)
	{
		tr[u] = { l, r, b[l], 0LL };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid, b);
		build(u << 1 | 1, mid + 1, r, b);
		pushup(u);
	}
	void update(int u, int l, int r, ll v)
	{
		if (tr[u].l >= l and tr[u].r <= r)
		{
			pushtag(u, v);
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update(u << 1, l, r, v);
		if (r > mid) update(u << 1 | 1, l, r, v);
		pushup(u);
	} 
}sgt, s2;

ll s[N];

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> q;
	for (int i = 2; i <= n; i++)
	{
		cin >> a[i] >> b[i]; 
	}
	bool f = 1;
	ll ss2 = 0;
	ll ss = 0;
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		ll z;
		cin >> x >> y >> z;
		if (y == n) ss += z; 
		else f = 0;
		ss2 += z;
		v[x].emplace_back(make_pair(y, z));
		vv[y].emplace_back(make_pair(x, z));
	}
	b[1] = (int)1e15;
	sgt.build(1, 1, n, b);
	for (int i = 2; i <= n; i++)
	{
		ll tot = 0; 
		for (auto &[j, v] : ::v[i - 1])
		{
			sgt.update(1, 1, j, v);
			tot += v;
		}
		res[i] = sgt.tr[1].minn;
		res[i] += a[i];
		s[i] = s[i - 1] + tot;
		res[i] = min(res[i], a[i] + s[i]);
	}
	res[1] = (int)1e15;
	s2.build(1, 1, n, res);
	ll ress = ss + (!f ? b[n] : 0LL);
	ll sus = 0;
	for (int i = n - 1; i >= 2; i--)
	{
		ll sp = ss + b[i];
		for (auto &[k, v] : vv[i]) sus += v; 
		ress = min(ress, sp + sus);
	}
	cout << min(s2.tr[1].minn, min(ress, ss2)) << "\n";
	while (q--)
	{
		int x, y;
		cin >> x >> y;
		x++;
		s2.update(1, x, x, -a[x]);
		a[x] = y;
		s2.update(1, x, x, a[x]);
		cout << min(s2.tr[1].minn, min(ress, ss2)) << "\n";	 
	}
	return 0;
}
```


---

## 作者：syzf2222 (赞：0)

这边是一个不用线段树的做法，我也不知道问题出在哪里了，很神奇。

首先必然是最大流转最小割。

容易发现 $A_i\to A_{i+1}$ 和 $B_i\to B_{i+1}$ 的边都只会断一条，而修改只会修改 $A$，于是如果固定 $A$ 中断的边，$B$ 中断的边也固定了。于是我们只需在一开始求出断每条 $A$ 边会断哪条 $B$ 边即可。易证这个是有单调性的。于是我们直接分治算出来就行。

复杂度 $O(n\log^2 n)$。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
#define ll long long
#define INF 1e18
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
vector<pii>E[maxn];
int n,m,q,A[maxn],B[maxn];ll Ans[maxn],tr[maxn];
inline void add(int x,int y){for(;x<=n;x+=x&(-x))tr[x]+=y;}
inline ll query(int x){ll res=0;for(;x;x-=x&(-x))res+=tr[x];return res;}
inline void solve(int l,int r,int L,int R){
	if(l>r)return;int mid=(l+r)>>1;
	for(int i=l;i<=mid;i++)
		for(auto x:E[i])add(n-x.fi+1,x.se);
	int pos=L;ll res=INF;
	for(int i=L;i<=R;i++){
		ll now=B[i]+query(n-i+1);
		if(now<res)pos=i,res=now;
	}Ans[mid]=res;
	for(int i=l;i<=mid;i++)
		for(auto x:E[i])add(n-x.fi+1,-x.se);
	solve(l,mid-1,L,pos);
	for(auto x:E[mid])add(n-x.fi+1,x.se);
	solve(mid+1,r,pos,R);
}
multiset<ll>S;
int main(){
	n=read(),m=read(),q=read();
	for(int i=1;i<n;i++)A[i]=read(),B[i+1]=read();
	for(int i=1,x,y,z;i<=m;i++)
		x=read(),y=read(),z=read(),E[x].pb(mkp(y,z));
	solve(1,n,1,n);
	for(int i=1;i<=n;i++)S.insert(A[i]+Ans[i]);
	printf("%lld\n",*S.begin());
	for(int i=1,x,y;i<=q;i++){
		x=read(),y=read();
		S.erase(S.find(A[x]+Ans[x]));
		A[x]=y;S.insert(y+Ans[x]);
		printf("%lld\n",*S.begin());
	}
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：rui_er (赞：0)

加边 $A_n\stackrel{0}{\to}A_{n+1}$，$B_0\stackrel{0}{\to}B_1$。称形如 $A_i\to A_{i+1}$ 的边为左部边，形如 $B_j\to B_{j+1}$ 的边为右部边，形如 $A_i\to B_j$ 的边为中间边。

根据最大流最小割定理，将最大流问题转化为最小割问题求解。显然，至少存在一组最小割，包含恰好一条左部边、恰好一条右部边和若干条中间边。

设割了左部边 $A_i\to A_{i+1}$、右部边 $B_j\to B_{j+1}$，则割掉的中间边一定是 $A_u\to B_v$，其中 $u\le i\land v > j$。设此时割掉的所有中间边的容量和为 $c_{i,j}$，则答案为 $\min\limits_i\left\{a_i+\min\limits_j\left\{b_j+c_{i,j}\right\}\right\}$。设 $p_i=\min\limits_j\left\{b_j+c_{i,j}\right\}$，答案即为 $\min\limits_i\left\{a_i+p_i\right\}$。

初始时 $p_i$ 可通过扫描线求出，由于修改操作是对 $a_i$ 的单点改，再使用线段树维护单点改、区间 $\min$ 即可。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(ll x = (y); x <= (z); ++x)
#define per(x, y, z) for(ll x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
    uniform_int_distribution<ll> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 2e5 + 5;

ll n, m, q, a[N], b[N], p[N];
vector<tuple<ll, ll>> e[N];

struct SegmentTree {
    ll val[N << 2], tag[N << 2];
    #define lc(u) (u << 1)
    #define rc(u) (u << 1 | 1)
    void pushup(ll u) {
        val[u] = min(val[lc(u)], val[rc(u)]);
    }
    void pushdown(ll u) {
        if(!tag[u]) return;
        tag[lc(u)] += tag[u];
        val[lc(u)] += tag[u];
        tag[rc(u)] += tag[u];
        val[rc(u)] += tag[u];
        tag[u] = 0;
    }
    void build(ll* a, ll u, ll l, ll r) {
        tag[u] = 0;
        if(l == r) {
            val[u] = a[l];
            return;
        }
        ll mid = (l + r) >> 1;
        build(a, lc(u), l, mid);
        build(a, rc(u), mid + 1, r);
        pushup(u);
    }
    void modify(ll u, ll l, ll r, ll ql, ll qr, ll k) {
        if(ql <= l && r <= qr) {
            tag[u] += k;
            val[u] += k;
            return;
        }
        pushdown(u);
        ll mid = (l + r) >> 1;
        if(ql <= mid) modify(lc(u), l, mid, ql, qr, k);
        if(qr > mid) modify(rc(u), mid + 1, r, ql, qr, k);
        pushup(u);
    }
    void clear(ll u, ll l, ll r) {
        tag[u] = val[u] = 0;
        if(l == r) return;
        ll mid = (l + r) >> 1;
        clear(lc(u), l, mid);
        clear(rc(u), mid + 1, r);
    }
    #undef lc
    #undef rc
}sgt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> q;
    rep(u, 1, n - 1) cin >> a[u] >> b[u + 1];
    rep(i, 1, m) {
        ll u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(v + 1, w);
    }
    sgt.build(b, 1, 1, n);
    rep(u, 1, n) {
        for(auto [v, w] : e[u]) {
            sgt.modify(1, 1, n, 1, v - 1, w);
        }
        p[u] = a[u] + sgt.val[1];
    }
    sgt.build(p, 1, 1, n);
    cout << sgt.val[1] << endl;
    while(q--) {
        ll u, w;
        cin >> u >> w;
        sgt.modify(1, 1, n, u, u, -a[u]);
        a[u] = w;
        sgt.modify(1, 1, n, u, u, +a[u]);
        cout << sgt.val[1] << endl;
    }
    return 0;
}
```

---

