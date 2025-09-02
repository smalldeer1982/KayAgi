# Qtree3

## 题目描述

给出 $N$ 个点的一棵树（$N-1$ 条边），节点有白有黑，初始全为白。

有两种操作：

`0 i`：改变某点的颜色（原来是黑的变白，原来是白的变黑）。

`1 v`：询问 $1$ 到 $v$ 的路径上的第一个黑点，若无，输出 $-1$。

## 说明/提示

对于 $1/3$ 的数据有 $N=5000,Q=400000$。

对于 $1/3$ 的数据有 $N=10000,Q=300000$。

对于 $1/3$ 的数据有 $N=100000, Q=100000$。

此外，有$1 \le i,v \le N$。

## 样例 #1

### 输入

```
9 8
1 2
1 3
2 4
2 9
5 9
7 9
8 9
6 8
1 3
0 8
1 6
1 7
0 2
1 9
0 2
1 9 ```

### 输出

```
-1
8
-1
2
-1```

# 题解

## 作者：Zcus (赞：44)

####  终于来到了Qtree3， 其实这是Qtree系列中最简单的一道题，并不需要线段树， 只要树链剖分的一点思想就吼了。

对于树链剖分剖出来的每一根重链，在重链上维护一个Set就好了， 每一个Set里存的都是重链中的黑点， 深度就是关键字。

考虑每一种操作

------------------------------
### 0 ： 改变颜色
	    在他所在的重链上插入一个黑点或者earse掉
### 1 :  查询
		就像树链剖分一样， 一直往上跳重链头然后更新答案即可
       
--------------------
代码较短

```cpp
#include <bits/stdc++.h>
#define maxn 101000
#define maxm 303000
using namespace std;

template<class T>
inline void read(T &a){
	T s = 0, w = 1;
	char c = getchar();
	while(c < '0' || c  > '9') {if(c == '-') w = -1; c = getchar();}
	while(c >= '0' && c <= '9') {s = (s << 1) + (s << 3) + (c ^ 48); c = getchar();}
	a = s*w;
}

static int n,q;
static int head[maxn], net[maxm], to[maxm],tot;

inline void add(int x, int y){
	net[++tot] = head[x], head[x] = tot, to[tot] = y;
}

static int dfn[maxn],tid[maxn], fat[maxn], size[maxn], son[maxn], deep[maxn];
static int top[maxn], cnt;

set<int> Ans[maxn];

void dfs1(int x, int fa){
	size[x] = 1;
	son[x] = 0; size[0] = 0;
	fat[x] = fa;
//	printf("%d\n", x);
	for (int i = head[x]; i; i = net[i]){
		int v = to[i];
		if(v == fa) continue;
		deep[v] = deep[x] + 1;
		dfs1(v, x);
		size[x] += size[v];
		if(size[v] > size[son[x]]) son[x] = v;
	}
}
void dfs2(int x, int fa, int t){
	dfn[++cnt] = x;
	//printf("%d %d %d\n", cnt, x, t);
	tid[x] = cnt;
	top[x] = t;
	if(!son[x]) return;
	dfs2(son[x], x, t);
	for (int i = head[x]; i; i = net[i]){
		int v = to[i];
		if(v == fa || v == son[x]) continue;
		dfs2(v, x, v);
	}
}


int col[maxn];
int main(){
	#ifndef ONLINE_JUDGE
		freopen("p4116.in","r", stdin);
		freopen("p4116.out","w", stdout);
	#endif
	read(n); read(q);
//	printf("%d\n", n); return 0;
	for (int i = 1; i < n; i++){
		int x, y;
		read(x); read(y);
		add(x, y); add(y, x);
	}
	dfs1(1, 0);
	dfs2(1, 0, 1); 
	for (int i = 1; i <= q; i++){
		int opt, x;
		read(opt); read(x);
		if(opt == 0){
			col[x] ^= 1;
			if(col[x] == 1) Ans[top[x]].insert(tid[x]);
			 else Ans[top[x]].erase(tid[x]);
		}
		else{
			int ans = 0x3f3f3f3f;
			while(x){
				int k = *Ans[top[x]].begin();
				if(Ans[top[x]].size())
					if(deep[dfn[k]] <= deep[x]) ans = dfn[k];
				x = fat[top[x]];
			}
			printf("%d\n", ans == 0x3f3f3f3f ? -1: ans);
		}
	}
	return 0;
}
```

---

## 作者：Treaker (赞：25)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 树链剖分
看见题解里有用set的，本人表示不是很会STL；

于是还是用是树剖+线段树过了这道题。。

我们发现一个事情就是，从1到v这条路径上的点的dfs序是越来越大，因为他的深度越来越大，所以我们可以通过这个性质来维护。。

我们对于黑点，让它的值等于它的dfs序，白点的话，直接赋inf，那么我查询的时候，只需要查询dfs序的最小值，再把它转化成编号即可。。

完整~~指针~~代码如下：
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 100005 , inf = 1e9;
inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
int n , Q , cnt;
int dfn[N] , size[N] , top[N] , fa[N] , dep[N] , hs[N] , id[N];
struct Tree_Div
{
	struct Edge
	{
		int to; Edge *nxt;
		Edge(int to,Edge *nxt) : to(to) , nxt(nxt) {}
	}*head[N];
	inline void add(int u,int v) {head[u] = new Edge(v,head[u]);}
	void get_tree(int x)
	{
		size[x] = 1;
		for(Edge *i = head[x];i;i = i -> nxt)
		{
			int to = i -> to;
			if(dep[to]) continue;
			dep[to] = dep[x] + 1;
			fa[to] = x;
			get_tree(to);
			size[x] += size[to];
			if(size[to] > size[hs[x]]) hs[x] = to;
		}
	}
	void dfs(int x,int topfa)
	{
		dfn[x] = ++cnt;
		id[cnt] = x;
		top[x] = topfa;
		if(hs[x]) dfs(hs[x],topfa);
		for(Edge *i = head[x];i;i = i -> nxt)
		{
			int to = i -> to;
			if(to == hs[x] || to == fa[x]) continue;
			dfs(to,to);
		}
	}
	#define mid ((p -> l + p -> r) >> 1)
	struct node
	{
		node *ls , *rs;
		int l , r , minn;
		node(int l,int r) : l(l) , r(r) {ls = rs = NULL; minn = inf;}
		inline void up() {minn = min(ls -> minn,rs -> minn);}
	}*root;
	void build(node *&p,int l,int r)
	{
		p = new node(l,r);
		if(l == r) return ;
		build(p -> ls,l,mid); build(p -> rs,mid+1,r); p -> up();
	}
	void chenge(node *p,int x)
	{
		if(p -> l == p -> r) return (void)(p -> minn == inf ? p -> minn = x : p -> minn = inf);
		x <= mid ? chenge(p -> ls,x) : chenge(p -> rs,x);
		p -> up();
	}
	int query(node *p,int x,int y)
	{
		if(x <= p -> l && p -> r <= y) return p -> minn;
		return min(x <= mid ? query(p -> ls,x,y) : inf,y > mid ? query(p -> rs,x,y) : inf);
	}
	inline int sec_query(int x)
	{
		int res = inf;
		while(top[x] != 1)
		{
			res = min(res,query(root,dfn[top[x]],dfn[x]));
			x = fa[top[x]];
		}
		res = min(res,query(root,dfn[1],dfn[x]));
		return res == inf ? -1 : id[res];
	}
	inline void LOL()
	{
		n = read(); Q = read();
		for(int i = 1 , u , v;i < n;i ++)
		{
			u = read(); v = read();
			add(u,v); add(v,u);
		} dep[1] = 1;
		get_tree(1);
		dfs(1,1);
		build(root,1,n);
		for(int i = 1 , opt , x;i <= Q;i ++)
		{
			opt = read(); x = read();
			if(opt & 1) printf("%d\n",sec_query(x));
			else chenge(root,dfn[x]);
		}
	}
}CF;
int main()
{
	CF.LOL();
	return 0;
}
```


---

## 作者：yu__xuan (赞：9)

### 题目
[P4116 Qtree3](https://www.luogu.com.cn/problem/P4116)

### 思路
树链剖分。$1$ 到 $v$ 的路径上的第一个黑点就是 $1$ 到 $v$ 路径上 $dfs$ 序最小的黑点。我们只需要把黑点的权值赋成该点的 $dfs$ 序，白点的权值赋成无穷大，就把查询 $1$ 到 $v$ 的路径上的第一个黑点转化成了查询$1$ 到 $v$ 的路径上的最小值的问题了。如果最小值等于无穷大那么输出 $-1$，否则输出最小值（$dfs$ 序）对应的点的编号。

### Code

```cpp
#include<cstdio>
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#define MAXN 100001
#define inf 2147483647

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

int n,q,dfn[MAXN],pre[MAXN],size[MAXN];

int min(int a,int b) {return a<b?a:b;}

namespace Seg {
	#define lson now<<1
	#define rson now<<1|1
	struct Node {
		int l,r,w;
	}tree[MAXN<<2];
	void build(int l,int r,int now) {
		tree[now].l=l,tree[now].r=r;
		if(tree[now].l==tree[now].r) {
			tree[now].w=inf;return;
		}
		int mid=(tree[now].l+tree[now].r)>>1;
		build(l,mid,lson),build(mid+1,r,rson);
		tree[now].w=min(tree[lson].w,tree[rson].w);
	}
	void update(int x,int now) {
		if(tree[now].l==tree[now].r) {
			if(tree[now].w!=inf) tree[now].w=inf;
			else tree[now].w=tree[now].l;
			return;
		}
		int mid=(tree[now].l+tree[now].r)>>1;
		if(x<=mid) update(x,lson);
		else update(x,rson);
		tree[now].w=min(tree[lson].w,tree[rson].w);
	}
	int query(int x,int y,int now) {
		if(tree[now].l>=x&&tree[now].r<=y) return tree[now].w;
		int mid=(tree[now].l+tree[now].r)>>1,ans=inf;
		if(x<=mid) ans=min(ans,query(x,y,lson));
		if(y>mid) ans=min(ans,query(x,y,rson));
		return ans;
	}
}

namespace Cut {
	int cnt,pthn,head[MAXN],dep[MAXN];
	int fa[MAXN],son[MAXN],top[MAXN];
	struct Edge {
		int next,to;
	}pth[MAXN<<1];
	void add(int from,int to) {
		pth[++pthn].to=to,pth[pthn].next=head[from];
		head[from]=pthn;
	}
	void dfs1(int u,int father) {
		fa[u]=father,dep[u]=dep[father]+1,size[u]=1;
		for(int i=head[u];i;i=pth[i].next) {
			int x=pth[i].to;
			if(x!=father) {
				dfs1(x,u),size[u]+=size[x];
				if(size[son[u]]<size[x]) son[u]=x;
			}
		}
	}
	void dfs2(int u,int tp) {
		top[u]=tp,dfn[u]=++cnt,pre[cnt]=u;
		if(son[u]) dfs2(son[u],tp);
		for(int i=head[u];i;i=pth[i].next) {
			int x=pth[i].to;
			if(x!=fa[u]&&x!=son[u]) dfs2(x,x);
		}
	}
	int ask(int x,int y) {
		int ans=inf;
		while(top[x]!=top[y]) {
			if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
			ans=min(ans,Seg::query(dfn[top[x]],dfn[x],1));
			x=fa[top[x]];
		}
		if(dep[x]>dep[y]) std::swap(x,y);
		ans=min(ans,Seg::query(dfn[x],dfn[y],1));
		if(ans==inf) return -1;
		return ans;
	}
}

int main() {
	read(n),read(q);
	for(int i=1,u,v;i<n;++i) {
		read(u),read(v);
		Cut::add(u,v),Cut::add(v,u);
	}
	Cut::dfs1(1,1),Cut::dfs2(1,1),Seg::build(1,n,1);
	for(int i=1,opt,x;i<=q;++i) {
		read(opt),read(x);
		if(opt==0) Seg::update(dfn[x],1);
		else {
			int ccc=Cut::ask(1,x);
			if(ccc==-1) puts("-1");
			else printf("%d\n",pre[ccc]);
		}
	}
	return 0;
}
```

---

## 作者：wrpwrp (赞：8)

我寻思这题为什么LCT题解这么少啊...   
这个题目连换根都不要的话LCT岂不是不用维护翻转操作了嘛？
然后pushdown,makeroot等等函数都不要写了  
然后50行就完事了？？？
```cpp
#include <cstdio>
#define R register
const int MAXN=1e5+10;
int ch[MAXN][2],fa[MAXN],id[MAXN],co[MAXN];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
inline int nroot(int x) { return ls(fa[x])==x||rs(fa[x])==x; }
inline int get(int x) { return x==rs(fa[x]); }
inline void update(int x) {
	id[x]=id[ls(x)]?id[ls(x)]:(co[x]?x:(id[rs(x)]?id[rs(x)]:0));
}
inline void rotate(int x) {
	int y=fa[x],z=fa[y],k=get(x),w=ch[x][!k];
	if(nroot(y)) ch[z][get(y)]=x;ch[x][!k]=y;ch[y][k]=w;
	if(w) fa[w]=y;fa[y]=x;fa[x]=z;update(x);update(y);
}
inline void splay(int x) {
	for(;nroot(x);rotate(x))
		if(nroot(fa[x])) rotate(get(x)^get(fa[x])?x:fa[x]);
}
inline void access(int x) {
	for(R int y=0;x;x=fa[y=x]) splay(x),rs(x)=y,update(x);
}
int n,q;
struct edge{ int y,next; }e[MAXN*2];
int cnt,head[MAXN];
inline void add(int x,int y) {
	e[++cnt].y=y;e[cnt].next=head[x];head[x]=cnt;
}
inline void dfs(int x,int fx) {
	fa[x]=fx;
	for(R int i=head[x];i;i=e[i].next) {
		if(e[i].y==fx)continue; dfs(e[i].y,x);
	}
}
int main(){
	scanf("%d%d",&n,&q);
	for(R int i=1;i<n;i++) {
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	while(q--) {
		int x,y;
		scanf("%d%d",&x,&y);
		if(x==0) { splay(y);co[y]^=1;update(y); }
		else {
			access(y);splay(y);
			printf("%d\n",id[y]==0?-1:id[y]);
		}
	}
	return 0;
}
```
还挺快的，快读都不加就3s了

---

## 作者：what_can_I_do (赞：5)

[传送门](https://www.luogu.com.cn/problem/P4116)

一个很暴力的算法。

首先打出基础的树链剖分，线段树直接维护一段 dfs 序区间内黑点的个数，如果个数大于 $0$ 就说明这一段有黑点。

在进行查询的时候，要对查询进行一定的更改。首先要找到第一个黑点可以转化成找到 dfs 序最小的黑点，那么这个点所在的链的链底一定是所有黑点所在的链的链底中 dfs 序最小的。于是在查询 $1$ 到 $x$ 的路径上第一个黑点的时候，就用 $s$ 把其中的含有黑点的链中 dfs 序最小的链底存起来，如果没有找到黑点函数返回 $-1$。

接下来直接暴力跑 $s$ 所在的链找黑点肯定是不行的，于是这里用 $l$ 记录 $s$ 这条链的链顶的 dfs 序，用 $r$ 记录 $s$ 的 dfs 序。记 $block=\sqrt n$，然后循环每次查询 $l$ 到 $l+block-1$ 这段 dfs 序中是否有黑点，如果有就暴力遍历 $l$ 到 $l+block-1$ 这段 dfs 序查找第一个黑点，否则 $l$ 变为 $l+block$，若 $l+block-1>r$ 则退出循环，并暴力遍历 $l$ 到 $r$ 找第一个黑点。

# CODE:
```cpp
#include<bits/stdc++.h>
#define lc k<<1
#define rc k<<1|1
#define ll long long
using namespace std;
int n,q;
vector<int> g[100010];
int tot=0,dy[100010];
struct tree
{
	int fa,son,dfn,top,size,h;
}tr[100010];
int xds[400010];
int a[100010];
inline void dfs1(int k)
{
	tr[k].size=1;
	for(register int i=0;i<g[k].size();i++)
	{
		int x=g[k][i];
		if(x==tr[k].fa) continue;
		tr[x].fa=k,tr[x].h=tr[k].h+1,dfs1(x),tr[k].size+=tr[x].size;
		if(!tr[k].son) tr[k].son=x;
		else if(tr[tr[k].son].size<tr[x].size) tr[k].son=x;
	}
}
inline void dfs2(int k,int tp)
{
	tr[k].top=tp,tot++,tr[k].dfn=tot,dy[tot]=k;
	if(!tr[k].son) return;
	dfs2(tr[k].son,tp);
	for(register int i=0;i<g[k].size();i++)
	{
		int x=g[k][i];
		if(x==tr[k].fa) continue;
		if(x!=tr[k].son) dfs2(x,x);
	}
}
inline void change(int l,int r,int pos,int k)
{
	if(l==r)
	{
		xds[k]^=1;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) change(l,mid,pos,lc);
	else change(mid+1,r,pos,rc);
	xds[k]=xds[lc]+xds[rc];
}
inline int query(int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr) return xds[k];
	int sum=0,mid=(l+r)>>1;
	if(ql<=mid) sum+=query(l,mid,ql,qr,lc);
	if(mid<qr) sum+=query(mid+1,r,ql,qr,rc);
	return sum;
}
inline int qulca(int x)
{
	int sum=n+1;
	while(1)
	{
		int tx=tr[x].top;
		if(tx==1) break;
		if(query(1,n,tr[tx].dfn,tr[x].dfn,1)) sum=min(sum,tr[x].dfn);
		x=tr[tx].fa;
	}
	if(query(1,n,1,tr[x].dfn,1)) sum=min(sum,tr[x].dfn);
	if(sum==n+1) return -1;
	sum=dy[sum];
	int block=sqrt(n);
	int l=tr[tr[sum].top].dfn,r=tr[sum].dfn;
	if(l+block-1>=r)
		for(register int i=l;i<=r;i++)
			if(a[dy[i]])
				return dy[i];
	while(l+block-1<r)
	{
		if(query(1,n,l,l+block-1,1))
			for(register int i=l;i<=l+block-1;i++)
				if(a[dy[i]])
					return dy[i];
		l+=block;
	}
	for(register int i=l;i<=r;i++)
		if(a[dy[i]])
			return dy[i];
	return -1;
}
int main()
{
	scanf("%d%d",&n,&q);
	for(register int i=1;i<=n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v),g[v].push_back(u);
	}
	dfs1(1),dfs2(1,1);
	while(q--)
	{
		int op,x;
		scanf("%d%d",&op,&x);
		if(!op) change(1,n,tr[x].dfn,1),a[x]^=1;
		if(op) printf("%d\n",qulca(x));
	}
	return 0;
}
```

---

## 作者：81179332_ (赞：5)

update:我跟其他题解的做法不一样啊，其他题解都维护了 dfs 序，我的没有维护 dfs 序。

重链剖分，对于每一条重链，采用 `set` 维护这条重链上深度最小的点是什么。

对于 0 操作：若改成黑色，我们在这条重链的 `set` 中插入这个点；若改成白色，我们删除这个点。

对于 1 操作：不断地跳 `top`，更新答案。注意 `v` 所在重链的 `set` 中深度最小的黑点可能比 `v` 的深度大，而该重链深度最小的黑点深度都比 `v` 大，显然这条重链对答案没有贡献。

另外，由于查询的是 `1` 到 `v`，因此不必维护 dfs 序。

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<set>

using namespace std;

#define INF 1000000000
#define pprint(x) print(x),putchar(' ')
#define fprint(x) print(x),putchar('\n')

//#define getchar() (SS == TT && (TT = (SS = BB) + fread(BB,1,1 << 15,stdin),TT == SS) ? EOF : *SS++)
char BB[1 << 15],*SS = BB,*TT = BB;
inline long long read()
{
	long long x = 0;int f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-')
			f = -1;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	return x * f;
}
void print(long long x)
{
	if(x < 0)
		putchar('-'),x = -x;
	if(x > 9)
		print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 100010;

int dep[N];
struct Tree_Partition
{
	struct edge
	{
		int nxt,to;
	}e[N << 1];
	int head[N],cnt;
	void add(int u,int v)
	{
		e[++cnt].to = v,e[cnt].nxt = head[u];
		head[u] = cnt;
	}
	void add_edge(int u,int v)
	{
		add(u,v),add(v,u);
	}
	int col[N],f[N],siz[N],son[N],top[N];
	struct cmp{bool operator()(const int &a,const int &b){ return dep[a] < dep[b]; }};
	set<int,cmp> s[N];
	void dfs1(int u,int fa)
	{
		f[u] = fa,dep[u] = dep[fa] + 1,siz[u] = 1;
		son[u] = 0;
		for(int i = head[u];i;i = e[i].nxt)
		{
			int v = e[i].to;
			if(v == fa)
				continue;
			dfs1(v,u);
			siz[u] += siz[v];
			if(siz[v] > siz[son[u]])
				son[u] = v;
		}
	}
	void dfs2(int u,int t)
	{
		top[u] = t;
		if(!son[u])
			return;
		dfs2(son[u],t);
		for(int i = head[u];i;i = e[i].nxt)
		{
			int v = e[i].to;
			if(v == f[u] || v == son[u])
				continue;
			dfs2(v,v);
		}
	}
	void change(int u)
	{
		if(col[u] ^= 1)
			s[top[u]].insert(u);
		else
			s[top[u]].erase(u);
	}
	int solve(int u)
	{
		int ans = -1;
		while(u)
		{
			int k = *s[top[u]].begin();
			if(s[top[u]].size())
				if(dep[k] <= dep[u])
					ans = k;
			u = f[top[u]];
		}
		return ans;
	}
	void init()
	{
		dfs1(1,0);
		dfs2(1,1);
	}
}T;

int main()
{
	int n = read(),m = read();
	for(int i = 1;i < n;i++)
		T.add_edge(read(),read());
	T.init();
	while(m--)
	{
		int op = read();
		if(!op)
			T.change(read());
		else
			fprint(T.solve(read()));
	}
	return 0;
}
```

---

## 作者：kririae (赞：5)

# Qtree3题解

下午想颓废颓废打一波树剖  
发现线段树维护麻烦  
于是果断分块  
分块真男人  
然后发现分块速度这么快   
就卡了一波常   
分块大法吼啊！！！   
luogu的O2是反优化   

由于是处理一条链上的信息，所以尽力寻找dfs序最小的一个就好啦
每个块维护一个`MIN`表示最“左”的一个点的dfn，每次查询分块套路，分三段处理，每次修改的也是比较套路的...如果特判`col == 1`的话会快一点。有少量注释
QwQ

```cpp
// by kririae
#include <bits/stdc++.h>

using namespace std;

const int maxn = 100005;

namespace IO
{
inline char gc()
{
  static char buf[1 << 18], *fs, *ft;
  return (fs == ft && (ft = (fs = buf) + fread(buf, 1, 1 << 18, stdin)), fs == ft) ? EOF : *fs++;
}
inline int read()
{
  register int k = 0, f = 1;
  register char c = gc();
  for (; !isdigit(c); c = gc()) if (c == '-') f = -1;
  for (; isdigit(c); c = gc()) k = (k << 3) + (k << 1) + (c - '0');
  return k * f;
}
}

namespace Qtree3
{
int head[maxn], ver[maxn << 1], next[maxn << 1], tot;
int siz[maxn], son[maxn], fa[maxn], dep[maxn], id[maxn], top[maxn], col[maxn], rev[maxn], cnt;
int bs, sc, L[maxn], R[maxn], MIN[maxn], belong[maxn]; // block_size, size_count
int n, q, op, val;

inline void addedge(register int from, register int to)
{
  ver[++tot] = to, next[tot] = head[from], head[from] = tot;
}
inline void dfs1(int k)
{
  siz[k] = 1, son[k] = 0;
  for (register int i = head[k]; i; i = next[i])
  {
    int to = ver[i];
    if(to == fa[k]) continue;
    fa[to] = k, dep[to] = dep[k] + 1;
    dfs1(to);
    if(siz[to] > siz[son[k]]) son[k] = to;
    siz[k] += siz[to];
  }
}
inline void dfs2(int k, int topf)
{
  id[k] = ++cnt, rev[cnt] = k, col[cnt] = 0, top[k] = topf;
  if(!son[k]) return;
  dfs2(son[k], topf);
  for (register int i = head[k]; i; i = next[i])
  {
    int to = ver[i];
    if(to == fa[k] || to == son[k]) continue;
    dfs2(to, to);
  }
}
inline void init()
{
  dfs1(1), dfs2(1, 1);
  bs = sqrt(n);
  sc = n % bs == 0 ? n / bs : n / bs + 1;
  for (register int i = 1; i <= sc; ++i)
    L[i] = R[i - 1] + 1, R[i] = L[i] + bs - 1, MIN[i] = 1e9;
  R[sc] = n;
  for (register int i = 1; i <= sc; ++i)
    for (register int j = L[i]; j <= R[i]; ++j)
      belong[j] = i;
}
inline void modify(register int pos)
{
  // 将id[pos]转化为相反的颜色，然后重置当前块的信息
  int bl = belong[pos];
  col[pos] = 1 - col[pos];
  if(col[pos] == 1) return MIN[bl] = min(MIN[bl], pos), void();
  else { 
    for (register int i = L[bl]; i <= R[bl]; ++i)
      if(col[i] == 1) return MIN[bl] = i, void(); // 求出最浅的块
  }
}
inline int query(register int l, register int r)
{
  // 分成三部分处理...
  if(l > r) swap(l, r);
  if(belong[l] == belong[r]) 
  {
    for (int i = l; i <= r; ++i) if(col[i]) return i;
    return 1e9;
  }
  for (register int i = l; i < L[belong[l] + 1]; ++i) if(col[i]) return i;
  for (register int i = belong[l] + 1; i <= belong[r] - 1; ++i) if(MIN[i] != 1e9) return MIN[i];
  for (register int i = L[belong[r]]; i <= r; ++i) if(col[i]) return i;
  return 1e9;
  // 已经尽力返回最小的了啊QAQ
}
inline int qtree(int x)
{
  int ans = 1e9;
  while(top[x] != top[1])
  {
    ans = min(ans, query(id[top[x]], id[x]));
    x = fa[top[x]];
  }
  ans = min(ans, query(id[1], id[x]));
  return ans >= 1e9 ? -1 : rev[ans];
}
inline void mtree(int pos)
{
  modify(id[pos]);
}
inline void solve()
{
  using namespace IO;
  n = read(), q = read();
  register int x, y;
  for (register int i = 1; i < n; ++i)
    x = read(), y = read(), addedge(x, y), addedge(y, x);
  init();
  while(q--)
  {
    op = read();
    switch(op)
    {
      case 0: x = read(), mtree(x); break;
      case 1: x = read(), printf("%d\n", qtree(x)); break;
    }
  }
}
}

int main()
{
  return Qtree3::solve(), 0;
}
```

---

## 作者：子谦。 (赞：5)

**Qtree系列第三题**

读完题大概不难判断是一道树剖的题

不会树剖一不小心点进这题的可以参考一下我有关树剖的讲解 [树链剖分](https://www.cnblogs.com/hanruyun/p/9577500.html)

这道题的关键是记录两种状态，以及黑点的序号（不是编号）

线段树啊当然

定义两个变量v,f，v表示距离根节点最近的黑点，默认-1，f则表示区间内是否含有黑点，有为1，无为0

那么，怎么才能取当前路径距离根节点最近的黑点的呢？线段树更新时，优先取左子区间的黑点，后取右子区间，更新答案时，优先取后出现的答案

那么直接看程序吧

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define ll long long
#define gc() getchar()
#define maxn 100005
using namespace std;

inline ll read(){
    ll a=0;int f=0;char p=gc();
    while(!isdigit(p)){f|=p=='-';p=gc();}
    while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
    return f?-a:a;
}
void write(ll a){
    if(a>9)write(a/10);
    putchar(a%10+'0');
}
int n,m;

struct ahaha1{     //前向星存边
    int to,next;
}e[maxn<<1];int head[maxn],tot;
inline void add(int u,int v){
    e[tot].to=v;e[tot].next=head[u];head[u]=tot++;
}

int sz[maxn],dep[maxn],f[maxn],son[maxn];
void dfs(int u,int fa){
    sz[u]=1;int maxa=0;
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;if(v==fa)continue;
        f[v]=u;dep[v]=dep[u]+1;
        dfs(v,u);sz[u]+=sz[v];
        if(maxa<sz[v]){maxa=sz[v];son[u]=v;}
    }
}
int top[maxn],in[maxn],b[maxn];
void dfs(int u,int fa,int topf){
    in[u]=++tot;top[u]=topf;b[tot]=u;
    if(!son[u])return;
    dfs(son[u],u,topf);
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;if(v==fa||v==son[u])continue;
        dfs(v,u,v);
    }
}

#define lc p<<1
#define rc p<<1|1
struct ahaha2{
    int v;bool f;
    ahaha2(){v=-1;}   //v的初始值为-1
}t[maxn<<2];
inline void pushup(int p){
    t[p].f=t[lc].f|t[rc].f;   //若左右子区间中含有黑点，则当前区间含有黑点
    t[p].v=t[lc].f?t[lc].v:(t[rc].f?t[rc].v:-1);    //优先取左子区间的黑点，使距离根节点尽可能近
}
void update(int p,int l,int r,int L){
    if(l==r){t[p].f^=1;t[p].v=t[p].f?b[l]:-1;return;}    //若改变后为黑点，则赋值为节点序号，否则重置
    int m=l+r>>1;
    if(L<=m)update(lc,l,m,L);
    else update(rc,m+1,r,L);
    pushup(p);
}
int query(int p,int l,int r,int L,int R){
    if(l>R||r<L)return -1;
    if(L<=l&&r<=R)return t[p].v;
    int m=l+r>>1,l1=query(lc,l,m,L,R),r1=query(rc,m+1,r,L,R);    //优先取左子区间
    return l1==-1?r1:l1;
}

inline void solve_1(){
    int x=read();
    update(1,1,n,in[x]);
}
inline void solve_2(){
    int x=read(),ans=-1,p;     //ans优先取后出现的的答案
    while(top[x]!=1){
    	p=query(1,1,n,in[top[x]],in[x]);
    	ans=(p==-1?ans:p);
    	x=f[top[x]];
    }
    p=query(1,1,n,1,in[x]);
    ans=(p==-1?ans:p);
    if(ans<0)putchar('-'),ans=-ans;
    write(ans);putchar('\n');
}

int main(){memset(head,-1,sizeof head);
    n=read();m=read();
    for(int i=1;i<n;++i){
        int x=read(),y=read();
        add(x,y);add(y,x);
    }
    tot=0;dfs(1,-1);dfs(1,-1,1);
    for(int i=1;i<=m;++i){
        int z=read();
        switch(z){
            case 0:solve_1();break;
            case 1:solve_2();break;
        }
    }
    return 0;
}
```


---

## 作者：Katsura_Hinagiku (赞：4)

和各位大佬一样，同样考虑用树链剖分+线段树。

稍有不同的是，我在tree数组中直接记录储存的点的编号，如果当前点为白色，编号为n+1，否则就是它本身的编号。

因为在1~v的路径上查询，每一种深度最多只对应一个点，而且深度越浅的点在越上方，所以将$dep[n+1]$赋值为极大值后，pushup时只需比较对应的两个点的深度即可。

详见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int head[100005],pnt[200005],nxt[200005],f[100005],E=0;
int son[100005],fa[100005],dep[100005],sz[100005];
int top[100005],id[100005],cnt=0,mp[100005];
int tree[400005],lazy[400005];
const int INF=1000000000;
int n,q;
void add_edge(int a,int b)
{
	pnt[E]=b;
	nxt[E]=head[a];
	head[a]=E++;
}
void dfs1(int u,int dpth)
{
	int maxson=0;
	dep[u]=dpth;
	sz[u]=1;
	for(int i=head[u];i!=-1;i=nxt[i])
	{
		int v=pnt[i];
		if(v==fa[u])continue;
		fa[v]=u;
		dfs1(v,dpth+1);
		sz[u]+=sz[v];
		if(sz[v]>maxson)
		{
			son[u]=v;
			maxson=sz[v];
		}
	}
}
void dfs2(int u,int tops)
{
	id[u]=++cnt;
	mp[cnt]=u;
	top[u]=tops;
	if(!son[u])return;
	dfs2(son[u],tops);
	for(int i=head[u];i!=-1;i=nxt[i])
	{
		int v=pnt[i];
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
void pushup(int k)
{
	if(dep[tree[k<<1]]<dep[tree[k<<1|1]])tree[k]=tree[k<<1];else tree[k]=tree[k<<1|1];//比较两点的深度
}
void build(int l,int r,int k)
{
	if(l==r)
	{
		tree[k]=n+1;//保证路径上有黑色的点时，白色的点不会被取到
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,k+k);
	build(mid+1,r,k+k+1);
	pushup(k);
}
void modify(int l,int r,int k,int pos)
{
	if(l==r)
	{
		if(tree[k]==n+1)
		{
			//cout<<tree[k]<<endl;
			tree[k]=mp[pos];
			//cout<<tree[k]<<endl<<endl;
		}
		else
		{
			//cout<<tree[k]<<endl;
			tree[k]=n+1;
			//cout<<tree[k]<<endl<<endl;
		}
		return;
	}
	int m=(l+r)>>1;
	if(pos<=m)modify(l,m,k<<1,pos);
	else modify(m+1,r,k<<1|1,pos);
	pushup(k);
}
int query(int L,int R,int l,int r,int k)
{
	if(L<=l&&r<=R)
	{
		return tree[k];
	}
	int m=(l+r)>>1,tmp1=n+1,tmp2=n+1;
	if(L<=m)tmp1=query(L,R,l,m,k<<1);
	if(R>m)tmp2=query(L,R,m+1,r,k<<1|1);
	if(dep[tmp1]<dep[tmp2])return tmp1;
	return tmp2;
}
int querychain(int x,int y)
{
	int ans=n+1;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		//cout<<top[x]<<' '<<x<<' '<<query(id[top[x]],id[x],1,cnt,1)<<endl;
		int tmp=query(id[top[x]],id[x],1,cnt,1);
		if(dep[ans]>dep[tmp])ans=tmp;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	int tmp=query(id[x],id[y],1,cnt,1);
	if(dep[ans]>dep[tmp])ans=tmp;
	return ans;
}
int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&q);
	dep[n+1]=INF;
	for(int i=1;i<n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	dfs1(1,1);
	dfs2(1,1);
	build(1,cnt,1);
	for(int i=1;i<=q;++i)
	{
		int opt,x;
		scanf("%d%d",&opt,&x);
		if(opt==0)
		{
			modify(1,cnt,1,id[x]);
		}
		else
		{
			int tmp=querychain(1,x);
			if(tmp==n+1)
			{
				printf("-1\n");//路径上没有黑点
			}
			else
			{
				printf("%d\n",tmp);
			}
		}
	}
	return 0;
}
```

---

## 作者：Vanyun (赞：3)

## 题意

有一棵$n$个点$n-1$条边的树。

树上的每个点可以为黑色也可以是白色。

开始所有的点为白色。

现在需要$2$种操作：

$0~~i$ 表示改变$i$号点的颜色（与的颜色原来相反）。

$1~~v$ 表示询问$1$到$v$的路径上的第$1$个黑点，若路径上无黑点，输出$-1$。

## 思路

初始时所有点为白点，那我们对所有点赋极大值。

在修改操作时，这个点若变成黑点，我们对这点的值赋为该点的dfs序。

若变成白点则赋值为与初始极大值相同的极大值。

首先一条路径上的dfs序肯定是递增的。

那么查询操作时我们查询到的该条路径的最小值一定是第一个黑点的dfs序。此时输出dfs序对应的点的编号。

如果为极大值则输出$-1$即可。

此时已经很显然了。

那么维护以上操作直接用我们喜闻乐见的树剖+线段树就可以啦qwq。

~~还是很简单的~~。


## 代码
```c++
#include <bits/stdc++.h>
using namespace std;
#define ls (now << 1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)

template<typename temp>
temp read(temp& x){
	x = 0; temp f = 1; char ch;
	while(!isdigit(ch = getchar())) (ch == '-') and (f = -1);
	for(x = ch^48; isdigit(ch = getchar()); x = (x<<3)+(x<<1)+(ch^48));
	return x *= f;
}
template <typename temp, typename ...Args>
void read(temp& a, Args& ...args){read(a), read(args...);}

const int maxn = 1e5+10, inf = 1e9+10;

int n, q, a[maxn];

vector<int> v[maxn];

struct trees{
protected:
	struct nods{
		int l, r, minnum;
	}node[maxn<<2];
	int cnt, dfn[maxn], id[maxn], top[maxn], dep[maxn], fa[maxn], size[maxn], height_son[maxn];
	void build(int now){
		size[now] = 1;
		for(unsigned int i = 0; i < v[now].size(); i ++){
			int to = v[now][i];
			if(dep[to]) continue;
			dep[to] = dep[now] + 1, fa[to] = now;
			build(to);
			size[now] += size[to];
			if(size[to] > size[height_son[now]]) height_son[now] = to;
		}
		return;
	}
	void dfs(int now, int topfa){
		top[now] = topfa;
		dfn[now] = ++cnt, id[cnt] = now;
		if(height_son[now]) dfs(height_son[now], topfa);
		for(unsigned int i = 0; i < v[now].size(); i ++){
			int to = v[now][i];
			if(height_son[now] == to or to == fa[now]) continue;
			dfs(to,to);
		}
		return;
	}
	void up(int now){return (void)(node[now].minnum = min(node[ls].minnum, node[rs].minnum));}
	void build(int l, int r, int now){
		node[now].l = l, node[now].r = r;
		if(l == r) return (void)(node[now].minnum = inf);
		build(l, mid, ls), build(mid+1, r, rs);
		return up(now);
	}
	void quary(int l, int r, int now, int& ans){
		if(r < node[now].l or node[now].r < l) return;
		if(l <= node[now].l and node[now].r <= r) return(void)(ans = min(ans, node[now].minnum));
		quary(l, r, ls, ans), quary(l, r, rs, ans);
		return up(now);
	}
	void chenge(int l, int r, int now, int val){
		if(r < node[now].l or node[now].r < l) return;
		if(l <= node[now].l and node[now].r <= r){
			if(node[now].minnum == inf) node[now].minnum = val;
			else node[now].minnum = inf;
			return;
		}
		chenge(l, r, ls, val), chenge(l, r, rs, val);
		return up(now);
	}
public:
	int quary(int x){
		int ans = inf;
		while(top[x] != 1){
			quary(dfn[top[x]], dfn[x], 1, ans);
			x = fa[top[x]];
		}
		quary(dfn[1], dfn[x], 1, ans);
		return ans == inf ? -1 : id[ans];
	}
	void chenge(int x){return chenge(dfn[x], dfn[x], 1, dfn[x]);}
	void build(){return build(dep[1]=1), dfs(1,1), build(1,n,1);}
}tree;

signed main(){
	read(n, q);
	for(int i = 1, x, y; i < n; i ++){
		read(x, y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	tree.build();
	for(int opt, x; q; q --){
		read(opt, x);
		if(opt&1) printf("%d\n", tree.quary(x));
		else tree.chenge(x);
	}
	return 0;
}
```

---

## 作者：亚由亚由 (赞：3)

显然的一道树剖题;

听说可以用set维护,但是这种维护线段树也肯定是可以做的.

改变颜色显然是异或(黑为1,白为0),直接用线段树维护区间内的最大值(0或1),如果为1,则再维护区间内最左边为1的端点,没有的话记为0就好.

查找时直接按树剖模版进行区间查询取最后一次的答案就好了.
~~(正确性显然)~~

因为树剖中每一次查找都在同一条重链上,线段树维护的是DFS序,同一重链中DFS序小的深度也一定小,所以维护线段树每个区间最左端的黑点即可.

code:
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long n,m,h[1000005],cnt,d[1000005],tot,rk[1000005];
struct ll
{
	long long nx;
	long long to;
}a[2000005];
struct sp
{
	long long size;
	long long son;
	long long tid;
	long long de;
	long long top;
	long long f;
}t[1000005];
struct xds
{
	long long l;
	long long r;
	long long s;
	long long m;//维护最左端黑点
}xd[4000005];
void ad(long long x,long long y)
{
	a[++cnt].nx=h[x];
	a[cnt].to=y;
	h[x]=cnt;
}
void dfs(long long x,long long fa)
{
	long long i,j;
	for(i=h[x];i;i=a[i].nx)
	{
		j=a[i].to;
		if(j==fa)
		continue;
		t[j].de=t[x].de+1;
		t[j].f=x;
		t[j].size=1;
		dfs(j,x);
		t[x].size+=t[j].size;
		if(!t[x].son||t[j].size>t[t[x].son].size)
		t[x].son=j;
	}
}
void dfs1(long long x,long long tp)
{
	long long i,j;
	t[x].top=tp;
	t[x].tid=++tot;
	rk[tot]=x;
	if(t[x].son)
	dfs1(t[x].son,tp);
	for(i=h[x];i;i=a[i].nx)
	{
		j=a[i].to;
		if(j==t[x].f||j==t[x].son)
		continue;
		dfs1(j,j);
	}
}
void up(long long v)
{
	xd[v].s=xd[v<<1].s|xd[v<<1|1].s;
	if(xd[v<<1].m)//先判左边
	xd[v].m=xd[v<<1].m;
	else if(xd[v<<1|1].m)xd[v].m=xd[v<<1|1].m;
	else xd[v].m=0;
}
void bd(long long v,long long l,long long r)
{
	long long mid;
	xd[v].l=l;
	xd[v].r=r;
	if(l==r)return ;
	mid=l+r>>1;
	bd(v<<1,l,mid);
	bd(v<<1|1,mid+1,r);
	up(v);
}
void xg(long long v,long long x)
{
	if(x>xd[v].r||x<xd[v].l)
	return ;
	if(xd[v].l==xd[v].r)
	{
		xd[v].s^=1;
		if(xd[v].s)
		xd[v].m=xd[v].l;
		else xd[v].m=0;
		return ;
	}
	xg(v<<1,x);
	xg(v<<1|1,x);
	up(v);
}
long long ask(long long v,long long l,long long r)
{
	int ls,rs;
	if(l>xd[v].r||r<xd[v].l)
	return 0;
	if(l<=xd[v].l&&r>=xd[v].r)
	return xd[v].m;
	ls=ask(v<<1,l,r);
	rs=ask(v<<1|1,l,r);
	if(ls)
	return ls;
	return rs;
}
long long ASK(long long x)
{
	long long i,j,fx,an=0;
	fx=t[x].top;
	while(fx)
	{
		if(i=ask(1,t[fx].tid,t[x].tid))
		an=i;//如果不为0就取最后一次答案
		x=t[fx].f;
		fx=t[x].top;
	}
	if(i=ask(1,1,t[x].tid))
	an=i;
	if(!an&&!i)
	return -1;
	return rk[an];
}
int main()
{
	long long i,j,x,y,z;
	char c;
	cin>>n>>m;
	for(i=1;i<n;i++)
	{
		cin>>x>>y;
		ad(x,y);
		ad(y,x);
	}
	dfs(1,0);
	dfs1(1,1);
	bd(1,1,n);
	for(i=1;i<=m;i++)
	{
		cin>>x>>y;
		if(x)
		cout<<ASK(y)<<'\n';
		else xg(1,t[y].tid);
	}
	return 0;
}
```

线段树跑起来肯定会慢一点,但思维难度不高,
~~写得熟练的话写起来也是很快的~~

---

## 作者：wxgwxg (赞：3)

讲一下线段树维护的方法，维护dfs序区间中为黑点的最小的dfn值，白点赋值为inf，查询直接从下往上跳的时候查一下最小值就行了。

这样为什么是对的？

因为每次查询都是在一条链上，dfn最小就代表深度最小，也就是离1最近的点了。复杂度 $qlogn$.

效率也是相当不错的。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
inline  int read()
{
    int k=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) k=k*10+c-'0';return f*k;
}
const int N=100055,inf=0x3f3f3f3f;
int n,m,tot,cnt,to[N<<1],nextt[N<<1],head[N],co[N],fa[N],dep[N],top[N],dfn[N],tr[N],mn[N<<2],size[N],son[N];
// tr[i]是dfn值为i的节点编号
void add(int a,int b)
{
    to[++tot]=b;
    nextt[tot]=head[a];
    head[a]=tot;
}
void dfs(int u,int f,int d)
{
    fa[u]=f;dep[u]=d;size[u]=1;
    for(int i=head[u];i;i=nextt[i])
    {
        if(to[i]==f) continue;
        dfs(to[i],u,d+1);size[u]+=size[to[i]];
        if(size[to[i]]>size[son[u]]) son[u]=to[i];
    }
} 
void dfs2(int u,int num)
{
    top[u]=num;dfn[u]=++cnt;tr[cnt]=u;
    if(!son[u]) return;
    dfs2(son[u],num);
    for(int i=head[u];i;i=nextt[i])
    {
        if(to[i]==fa[u]||to[i]==son[u]) continue;
        dfs2(to[i],to[i]);
    }
}
#define lson k<<1,l,mid
#define rson k<<1|1,mid+1,r
void pu(int k) {mn[k]=min(mn[k<<1],mn[k<<1|1]);}
void build(int k,int l,int r)
{
    if(l==r) {mn[k]=inf;return;}
    int mid=l+r>>1;
    build(lson);build(rson);
    pu(k);
}
void ch(int k,int l,int r,int x,int opt)
{
    if(l==r) {if(opt==1) mn[k]=l;else mn[k]=inf;return;}
    int mid=l+r>>1;
    if(x<=mid) ch(lson,x,opt);else ch(rson,x,opt);
    pu(k);
}
int query(int k,int l,int r,int a,int b)
{
    if(a<=l&&b>=r) return mn[k];
    int mid=l+r>>1,ans=inf;
    if(a<=mid) ans=min(ans,query(lson,a,b));
    if(b>mid ) ans=min(ans,query(rson,a,b));return ans; 
}
int query2(int x)
{
    int ans=inf;
    while(top[x]!=1)
    {
        ans=min(ans,query(1,1,n,dfn[top[x]],dfn[x]));x=fa[top[x]];
    }
    ans=min(ans,query(1,1,n,1,dfn[x]));return ans;
}
int main()
{
    int a,b;
    n=read();m=read();
    for(int i=1;i<n;i++)
    a=read(),b=read(),add(a,b),add(b,a);
    dfs(1,1,1);dfs2(1,1);build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        a=read();b=read();
        if(a==0) 
        {
            co[b]^=1;ch(1,1,n,dfn[b],co[b]);
        }
        else 
        {
            int k=query2(b);
            if(k==inf) puts("-1");
            else printf("%d\n",tr[k]);
        }
    }
    return 0;
}
```

---

## 作者：SammyChu (赞：2)

发现题解区里的各位佬的思路和我都不太一样，于是我就来~~献一波丑~~发表一下自己的思路。

注意到这道题的询问是每个点到树上一个固定节点的路径的相关信息，因此可以指定该固定节点为根，然后用树链剖分去维护每条链上的信息。如果不会树链剖分……请自行上网学习。
（~~逃~~）

于是问题就转化成维护序列的操作。注意到树链剖分在对节点进行标号的时候，**任意一个节点的编号一定小于于其任意一个子孙的编号**，而我们要查询的就是距离根结点最近的满足某种要求的点，所以可以维护**最小值**（最小点权）。

只剩下一个问题了：黑白点怎么处理？考虑到维护的是最小值，所以可以想办法把不符合要求的点的值设为INF，即：每次改变颜色时，如果是白变黑就把该点的权值单点修改为该节点的编号值，若为黑变白就把该点的权值修改为INF。查询时只需要通过查询**从该点到根结点的路径所经过的最小点权**即可找到离根结点最近的黑点。于是本题就可以用一个比较模板的树剖解决了。

所以整体思路为：

1. 预处理，得到树剖的基本信息，如节点编号，深度，子树大小等。

1. 构建线段树，每一个区间的初始值设为INF（刚开始全为白点）

1. 读入修改操作，按照上面的构思进行单点修改，每次查询路径上的点的最小值。

于是就可以AC了。代码如下：
```cpp
#include<bits/stdc++.h>//万能头文件 
#define INF 0x7fffffff//设置最大值 
using namespace std;
inline void read(int &x)//读入优化 
{
	int w=x=0;
	char ch=0;
	while(ch<'0'||'9'<ch)
		w|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')
		x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
	x=w?-x:x;
}
const int N=1e5;
int n,q,a,b,c;//a,b,c是与题意无关的变量，让敲代码时更轻松 
struct segtree//线段树 
{
	int l,r,val;//分别为左端点，右端点，区间最小值 
}tr[N<<2];
#define ls tr[id].l
#define rs tr[id].r
#define lid id<<1
#define rid id<<1|1 //一手宏定义简化代码 
int E[N<<1],last,fst[N|1],nxt[N<<1];//邻接表存树 
int fa[N|1],dep[N|1],size[N|1];//记录每个点的父亲，深度以及子树大小 
int top[N|1],son[N|1],vis[N|1];//记录每个点所在的重链的最高点，重儿子编号
//vis表示当前是黑点还是白点（1：黑；0：白） 
int cnt,name[N|1],node[N|1];//记录点的编号，编号所对应的结点 
void add(int x,int y)//加边 
{
	E[++last]=y,nxt[last]=fst[x],fst[x]=last;
}
void pre(int x)//树链剖分第一次dfs 
{
	dep[x]=dep[fa[x]]+1,size[x]=1;
	for(int i=fst[x];i;i=nxt[i])
		if(E[i]^fa[x])//相当于E[i]!=fa[x] 
		{
			fa[E[i]]=x,pre(E[i]),size[x]+=size[E[i]];
			if(size[son[x]]<size[E[i]])
				son[x]=E[i];
		}
}
void dfs(int x,int up)//树链剖分第二次dfs 
{
	top[x]=up,name[x]=++cnt,node[cnt]=x;//记录 
	if(son[x])
		dfs(son[x],up);
	for(int i=fst[x];i;i=nxt[i])
		if(E[i]^fa[x]&&E[i]^son[x])
			dfs(E[i],E[i]);
}
void build(int x,int y,int id)//建立线段树 
{
	ls=x,rs=y,tr[id].val=INF;	
	if(x==y)
		return;
	int mid=(x+y)>>1;
	build(x,mid,lid),build(mid+1,y,rid);
}
void modify(int x,int y,int id)//单点修改 
{
	if(ls==rs)
	{
		tr[id].val=y;
		return;
	}
	int mid=(ls+rs)>>1;
	if(x<=mid)
		modify(x,y,lid);
	else
		modify(x,y,rid);
	tr[id].val=min(tr[lid].val,tr[rid].val);
}
int query(int x,int y,int id)//区间查询最小值 
{
	if(x<=ls&&rs<=y)
		return tr[id].val;
	int mid=(ls+rs)>>1,res=INF;
	if(x<=mid)
		res=min(res,query(x,y,lid));
	if(y>mid)
		res=min(res,query(x,y,rid));
	return res;
}
int ask(int x,int y)//树链剖分查询链上最小值 
{
	int res=INF;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		res=min(res,query(name[top[x]],name[x],1));
		x=fa[top[x]];
	}
	if(name[x]>name[y])
		swap(x,y);
	return min(res,query(name[x],name[y],1));
}
int main()
{
	read(n),read(q);
	for(int i=1;i<n;++i)
		read(a),read(b),add(a,b),add(b,a);
	pre(1),dfs(1,1),build(1,n,1);
	for(int i=1;i<=q;++i)
	{
		read(a),read(b);
		if(a)
		{
			c=ask(1,b);//先把最小值记录下来 
			if(c==INF)//说明没有黑点 
				printf("-1\n");
			else//一定是输出node（别问我为什么要强调这一点） 
				printf("%d\n",node[c]);
		}
		else
		{
			b=name[b];//先变成结点编号 
			if(!vis[b])//本来是白点，改为节点编号 
				modify(b,b,1),vis[b]=1;
			else//本来是黑点，改为INF 
				modify(b,INF,1),vis[b]=0;
		}
	}
	return 0;
}
```
于是就AC了。谢谢读者能看到最后！

---

## 作者：Ameyax (赞：2)

楼下的大佬们太强辣。

蒟蒻来一发lct。

首先暴力的做法是每次询问都往上跳，一直跳到根。

那么优化这个跳的过程，显然可以用平衡树来维护这条链，那就是一个lct的模板题了。

只需要在splay里维护子树里的黑点数目即可。

复杂度：$O(qlogn)$~~大常数64~~

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 110000;
struct LinkCutTree
{
    int sta[MAX], top;
    struct Node
    {
        int fa, son[2], sum, rev, val;
    } T[MAX];
    bool isroot(int x)
    {
        return T[T[x].fa].son[0] != x && T[T[x].fa].son[1] != x;
    }
    void pushup(int x)
    {
        T[x].sum = T[T[x].son[0]].sum + T[T[x].son[1]].sum + T[x].val;
    }
    void pushdown(int x)
    {
        if (T[x].rev)
        {
            T[x].rev ^= 1;
            T[T[x].son[0]].rev ^= 1;
            T[T[x].son[1]].rev ^= 1;
            swap(T[x].son[0], T[x].son[1]);
        }
    }
    void rotate(int x)
    {
        int y = T[x].fa, z = T[y].fa;
        int op = T[y].son[1] == x;
        T[x].fa = z;
        if (!isroot(y)) T[z].son[T[z].son[1] == y] = x;
        T[y].son[op] = T[x].son[!op];
        T[T[y].son[op]].fa = y;
        T[x].son[!op] = y;
        T[y].fa = x;
        pushup(y);
    }
    void splay(int x)
    {
        top = 1; sta[top] = x;
        for (int i = x; !isroot(i); i = T[i].fa) sta[++top] = T[i].fa;
        for (int i = top; i; i--) pushdown(sta[i]);
        while (!isroot(x))
        {
            int y = T[x].fa, z = T[y].fa;
            if (!isroot(y))
                if ((T[z].son[0] == y) ^ (T[y].son[0] == x)) rotate(x);
                else rotate(y);
            rotate(x);
        }
        pushup(x);
    }
    void access(int x)
    {
        for (int t = 0; x; t = x, x = T[x].fa)
            splay(x), T[x].son[1] = t, pushup(x);
    }
    void makeroot(int x)
    {
        access(x), splay(x); T[x].rev ^= 1;
    }
    int findroot(int x)
    {
        access(x), splay(x);
        while (T[x].son[0]) x = T[x].son[0];
        return x;
    }
    void link(int x, int y)
    {
        makeroot(x); T[x].fa = y;
    }
    void split(int x, int y)
    {
        makeroot(x), access(y), splay(y);
    }
    void cut(int x, int y)
    {
        split(x, y);
        T[x].fa = T[y].son[0] = 0;
        pushup(y);
    }
    void change(int x)
    {
        splay(x);
        T[x].val ^= 1;
        pushup(x);
    }
    int query(int x)
    {
        makeroot(1);
        access(x), splay(x);
        if (T[x].sum == 0) return -1;
        while (x)
        {
            if (T[T[x].son[0]].sum == 0 && T[x].val)
                return x;
            else if (T[T[x].son[0]].sum) x = T[x].son[0];
            else x = T[x].son[1];
        }
    }
} lct;
int n, q;
int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}
int main()
{
    n = read(), q = read();
    for (int i = 1; i < n; i++)
    {
        int u = read(), v = read();
        lct.link(u, v);
    }
    while (q--)
    {
        int opt = read(), x = read();
        if (opt == 0) lct.change(x);
        else printf("%d\n", lct.query(x));
    }
    return 0;
}
```

---

## 作者：Drifterming (赞：2)

```
//记录每个点下面那段区间的黑色的深度最浅的点是谁
//修改到叶子节点，直接修改，pushup的时候在左右儿子里取个最优的

//两天没做有些生疏了
//update的时候位置直接传的v，应该是node[v].s，
//因为找的是v这个点在线段树中的位置
//还要传一下v等于几
//node[v].s是在线段树中的位置，v是要改的节点的标号 

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int N=1e5+5;

int n,m;
int head[N],num_edge;
struct Edge
{
	int v,nxt;
}edge[N<<1];
struct NODE
{
	int fa,son;
	int size,dep;
	int top;
	int s,t;
}node[N];
struct TREE
{
	TREE *lson,*rson;
	int l,r,mid;
	int num,col;
}tree[N<<2];

typedef TREE* Tree;
Tree Root,now_node=tree;

inline int read()
{
	char c=getchar();int num=0;
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())
		num=num*10+c-'0';
	return num;
}

inline void add_edge(int u,int v)
{
	edge[++num_edge].v=v;
	edge[num_edge].nxt=head[u];
	head[u]=num_edge;
}

void dfs1(int u)
{
	node[u].size=1;
	for(int i=head[u],v;i;i=edge[i].nxt)
	{
		v=edge[i].v;
		if(v==node[u].fa)
			continue;
		node[v].fa=u;
		node[v].dep=node[u].dep+1;
		dfs1(v);
		node[u].size+=node[v].size;
		if(node[v].size>node[node[u].son].size)
			node[u].son=v;
	}
}

int bound;
void dfs2(int u,int top)
{
	node[u].s=++bound;
	node[u].top=top;
	if(node[u].son)
	{
		dfs2(node[u].son,top);
		for(int i=head[u],v;i;i=edge[i].nxt)
		{
			v=edge[i].v;
			if(v==node[u].son||v==node[u].fa)
				continue;
			dfs2(v,v);
		}
	}
	node[u].t=bound;
}

void build(Tree &root,int l,int r)
{
	root=++now_node;
	root->l=l,root->r=r,root->mid=l+r>>1;
	if(l==r)
		return;
	build(root->lson,l,root->mid);
	build(root->rson,root->mid+1,r);
}

void better(Tree root)
{
	if(node[root->lson->num].dep>node[root->rson->num].dep)
		root->num=root->rson->num;
	else
		root->num=root->lson->num;
}

void update(const Tree &root,int pos,int num)
{
	if(root->l==root->r)
	{
		root->col^=1;
		if(root->col)
			root->num=num;
		else
			root->num=0;
		return;
	}
	if(pos<=root->mid)
		update(root->lson,pos,num);
	else
		update(root->rson,pos,num);
	better(root);
}

int query(const Tree &root,int l,int r)
{
	if(root->l==l&&root->r==r)
		return root->num;
	if(r<=root->mid)
		return query(root->lson,l,r);
	else if(l>root->mid)
		return query(root->rson,l,r);
	else
	{
		int a=query(root->lson,l,root->mid),b=query(root->rson,root->mid+1,r);
		return node[a].dep>node[b].dep?b:a;
	}
}

inline int Query(int x,int y)
{
	int fx=node[x].top,fy=node[y].top;
	int ans=0,tmp,dep=599518803;
	while(fx!=fy)
	{
		if(node[fx].dep>node[fy].dep)
		{
			tmp=query(Root,node[fx].s,node[x].s);
			if(dep>node[tmp].dep)
				ans=tmp,dep=node[tmp].dep;
			x=node[fx].fa;
			fx=node[x].top;
		}
		else
		{
			tmp=query(Root,node[fy].s,node[y].s);
			if(dep>node[tmp].dep)
				ans=tmp,dep=node[tmp].dep;
			y=node[fy].fa;
			fy=node[y].top;
		}
	}
	if(node[x].dep>node[y].dep)
	{
		tmp=query(Root,node[y].s,node[x].s);
		if(dep>node[tmp].dep)
			ans=tmp;
	}
	else
	{
		tmp=query(Root,node[x].s,node[y].s);
		if(dep>node[tmp].dep)
			ans=tmp;
	}
	return ans?ans:-1;
}

int u,v;
int main()
{
	node[0].dep=0x7fffffff;
	n=read(),m=read();
	for(int i=1;i<n;++i)
	{
		u=read(),v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1);
	dfs2(1,1);
	build(Root,1,n);
	int opt,v;
	for(int i=1;i<=m;++i)
	{
		opt=read(),v=read();
		if(opt==0)
			update(Root,node[v].s,v);
		else
		{
			printf("%d\n",Query(1,v));
		}
	}
	return 0;
}
```

---

## 作者：Great_Influence (赞：2)

树链剖分。（然而没打等号连WA一版也是够）

直接用最暴力的思想跑。树链剖分完后直接对每一条链用set维护链上黑色点的dfn。因为dfn唯一对应，所以不会有重复。查询就一路跳链，在经过的链上查询dfn最小的点。注意如果这个点的dep小于目前跳到的点的dep，那么不计入答案。


代码：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define Chkmax(a,b) a=a>b?a:b;
#define Chkmin(a,b) a=a<b?a:b;
using namespace std;
template<typename T>inline void read(T &x)
{
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&(k^'-'))k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
void file()
{
    #ifndef ONLINE_JUDGE
        freopen("water.in","r",stdin);
        freopen("water.out","w",stdout);
    #endif
}
const int MAXN=200010;
static struct edge
{
    int v,next;
}p[MAXN<<1];
static int n,e,quer,head[MAXN],fa[MAXN],dep[MAXN];
static int sta[MAXN];
inline void add(int u,int v){p[++e].v=v;p[e].next=head[u];head[u]=e;}
static int dfn[MAXN],ri[MAXN],top[MAXN],sz[MAXN],son[MAXN];
static int t,link[MAXN];
void dfs1(int u)
{
    dep[u]=dep[fa[u]]+1;sz[u]=1;
    for(register int v=head[u];v;v=p[v].next)if(p[v].v^fa[u])
    {
        fa[p[v].v]=u;dfs1(p[v].v);sz[u]+=sz[p[v].v];
        if(!son[u]||sz[p[v].v]>sz[son[u]])son[u]=p[v].v;
    }
}
void dfs2(int u,int tp)
{
    dfn[u]=++e;ri[e]=u;top[u]=tp;
    if(u^tp)link[u]=link[tp];
    else link[u]=++t;
    if(son[u])dfs2(son[u],tp);else return;
    for(register int v=head[u];v;v=p[v].next)
        if(p[v].v!=fa[u]&&p[v].v!=son[u])
            dfs2(p[v].v,p[v].v);
}
inline void init()
{
    scanf("%d%d",&n,&quer);
    static int u,v;
    Rep(i,1,n-1)scanf("%d%d",&u,&v),add(u,v),add(v,u);
    e=0;dfs1(1);dfs2(1,1);
}
static set<int>G[100011];
inline void modify(int x)
{
    if(sta[x])G[link[x]].erase(dfn[x]);
    else G[link[x]].insert(dfn[x]);
    sta[x]^=1;
}
inline int query(int x)
{
    int ans=-1,pos=0;
    if(sta[x])ans=x;
    while(x)
    {
        if(!G[link[x]].empty()&&dep[pos=ri[*G[link[x]].begin()]]<=dep[x])//这个等号wa了我半天
            ans=pos;
        x=fa[top[x]];
    }
    return ans;
}
void solve()
{
    static int opt,x;
    Rep(i,1,quer)
    {
        scanf("%d%d",&opt,&x);
        if(opt)printf("%d\n",query(x));
        else modify(x);
    }
}
int main()
{
    file();
    init();
    solve();
    return 0;
}
```

---

## 作者：zjp_shadow (赞：2)

> 外话：最近洛谷加了好多好题啊...[原题入口](https://www.luogu.org/problemnew/show/P4116) 这题好像是SPOJ的题，挺不错的。看没有题解还是来一篇...

- 题意：


很明显吧。。

    
- 题解：

    
我的做法十分的暴力：树链剖分（伪）+线段树+$set$...

    
首先，我们可以考虑每次修改一个点的颜色的影响。

易知，翻转一个点颜色，只会对于他的子树产生影响，对于别的点就毫无意义了。

    
然后，只要学过一点树链剖分的就知道，我们可以将整棵树按它的$dfs$序进行标号，

每个点的序号就是$dfn$，

然后记下它的子树大小$size$，然后对于每个点$u$所在的子树区间就是$[dfn[u], dfn[u]+size[u]-1]$。

所以每次操作的时候，只要对于那一段区间进行修改就行了。


然后我们要修改和查询什么呢？不就是查询包含这个点，且深度最小的黑点吗？（需要把$1$作为根）

    
所以，我们每次记下一个区间中，包含这个点的所有黑色标号以及他们的深度，用$pair$记录一下（因为这个可以

自动按照第一关键字排序），再用$set$维护一下区间最值就行了。

    
每次更新的时候只要在$set$里面$insert$和$erase$。

查询就是从根节点一直向下跑，不断取一个深度更小的$ans$。

    
具体有些实现在程序中会体现的……

    
总时间复杂度$O(q \ log \ n)$ 空间复杂度也是$O(q \ log \ n)$。（所以说很暴力嘛……）


- 代码：

```cpp
#include <bits/stdc++.h>
#define For(i, l, r) for(int i = (l), _end_ = (int)(r); i <= _end_; ++i)
#define Fordown(i, r, l) for(int i = (r), _end_ = (int)(l); i >= _end_; --i)
#define Set(a, v) memset(a, v, sizeof(a))
using namespace std;

bool chkmin(int &a, int b) {return b < a ? a = b, 1 : 0;}
bool chkmax(int &a, int b) {return b > a ? a = b, 1 : 0;}

inline int read() {
    int x = 0, fh = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar() ) if (ch == '-') fh = -1;
    for (; isdigit(ch); ch = getchar() ) x = (x<<1) + (x<<3) + (ch ^ '0');
    return x * fh;
}

void File() {
#ifdef zjp_shadow
    freopen ("P4116.in", "r", stdin);
    freopen ("P4116.out", "w", stdout);
#endif
}

const int N = 1e5 + 1e3, M = N << 1;
int n, q;
int sz[N], dfn[N], dep[N];

int to[M], Next[M], Head[N], e = 0;

void add(int u, int v) {
    to[++e] = v;
    Next[e] = Head[u];
    Head[u] = e;
}

void Dfs(int u, int fa) {
    static int clk = 0;
    sz[u] = 1;
    dfn[u] = ++ clk;
    dep[u] = dep[fa] + 1;
    for (register int i = Head[u]; i; i = Next[i]) {
        register int v = to[i];
        if (v == fa) continue ;
        Dfs(v, u); sz[u] += sz[v];
    }
}//就是树链剖分的第一个dfs,求出size,dep,dfn 

typedef pair<int, int> PII;
#define mp make_pair
#define lson o << 1, l, mid
#define rson o << 1 | 1, mid + 1, r
set<PII> S[N << 2];

bool col[N];//因为不知道是变啥颜色,所以要记一下原来的颜色 
bool uopt; int ul, ur; PII uv;
void Update(int o, int l, int r) {
    if (ul <= l && r <= ur) {
        if (uopt) S[o].erase(uv);
        else S[o].insert(uv);
        //erase可以直接调用那个值. 
        return ;
    }
    int mid = (l + r) >> 1;
    if (ul <= mid) Update(lson);
    if (ur > mid) Update(rson);
}

PII ans; int up;
void Query(int o, int l, int r) {
    if ((bool)S[o].size() )
        ans = min(ans, *S[o].begin() );
    //begin就是这个set中最小的那一个,即这里面深度最小的那个点 
    if (l == r) return ;
    int mid = (l + r) >> 1;
    if (up <= mid) Query(lson);
    else Query(rson);
}

const int inf = 0x3f3f3f3f;

int main () {
    n = read(); q = read();
    For (i, 1, n - 1) {
        int u, v;
        scanf ("%d%d", &u, &v);
        //int u = read(), v = read();
        add(u, v); add(v, u);
    }
    Dfs(1, 0);
    
    For (i, 1, q) {
        int opt, pos;
        scanf ("%d%d", &opt, &pos);
        //int opt = read(), pos = read();
        if (opt == 0) {
            uopt = col[pos];
            col[pos] ^= true;
            ul = dfn[pos];
            ur = dfn[pos] + sz[pos] - 1;
            uv = mp(dep[pos], pos);
            Update(1, 1, n);
        } else {
            ans = mp(inf, inf);
            up = dfn[pos];
            Query(1, 1, n);
            printf ("%d\n", ans.second == inf ? -1 : ans.second);
        }
    }
    //cerr << clock() << endl;
    return 0;
}
```

> 后记：看到很多dalao都是用啥 主席树，倍增，和不用$set$的线段树做过去的。跑得都比我快，希望后面有人能讲一讲QAQ。

---

## 作者：Adove (赞：1)

为什么不试试维护重链上一个点到链顶的黑点个数呢QAQ

可以用标记永久化的方式减小常数

树链剖分第二个DFS不仅可以预处理链顶，还可以预处理链底

在最后一条有黑点的重链上二分答案

这样一个修改操作是$\Theta(\log n)$的

一个询问操作是$\Theta(\log ^2 n)$的

总复杂度$\Theta(q \log^2 n)$

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1<<17;

int n,m,np;
int h[MAXN],sn[MAXN],f[MAXN],siz[MAXN],deg[MAXN];
int top[MAXN],id[MAXN],dep[MAXN],rid[MAXN];
bool clr[MAXN];
int tag[MAXN<<1];
struct rpg{
	int li,nx;
}a[MAXN<<1];

inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||'9'<ch) ch=getchar();
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}

void add(int ls,int nx)
{
	a[++np]=(rpg){h[ls],nx};h[ls]=np;
	a[++np]=(rpg){h[nx],ls};h[nx]=np;
}

void dfs1(int x,int fa,int tp)
{
	f[x]=fa;siz[x]=1;dep[x]=tp;
	for(int i=h[x];i;i=a[i].li){
		if(a[i].nx==fa) continue;
		dfs1(a[i].nx,x,tp+1);
		siz[x]+=siz[a[i].nx];
		if(siz[a[i].nx]>siz[sn[x]]) sn[x]=a[i].nx;
	}return;
}

void dfs2(int x,int tpx)
{
	top[x]=tpx;id[x]=++id[0];rid[id[x]]=x;deg[tpx]=x;
	if(!sn[x]) return;
	dfs2(sn[x],tpx);
	for(int i=h[x];i;i=a[i].li){
		if(a[i].nx==f[x]||a[i].nx==sn[x]) continue;
		dfs2(a[i].nx,a[i].nx);
	}return;
}

void cchg(int k,int l,int r,int le,int ri,int v)
{
	if(le<=l&&r<=ri){tag[k]+=v;return;}
	int i=k<<1,mid=l+r>>1;
	if(le<=mid) cchg(i,l,mid,le,ri,v);
	if(mid<ri) cchg(i|1,mid+1,r,le,ri,v);
	return;
}

int cask(int k,int l,int r,int v)
{
	if(l==r) return tag[k];
	int i=k<<1,mid=l+r>>1;
	if(v<=mid) return cask(i,l,mid,v)+tag[k];
	return cask(i|1,mid+1,r,v)+tag[k];
}

int csk(int x)
{
	int sx=0;
	while(top[x]!=1){
		if(cask(1,1,n,id[x])) sx=x;
		x=f[top[x]];
	}if(cask(1,1,n,id[x])) sx=x;
	if(!sx) return -1;
	int l=id[top[sx]],r=id[sx];
	while(l<r){
		int mid=l+r>>1;
		if(cask(1,1,n,mid)) r=mid;
		else l=mid+1;
	}return rid[l];
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;++i){int x=read(),y=read();add(x,y);}
	dfs1(1,1,1);dfs2(1,1);
	while(m--){
		int p=read(),x=read();
		if(!p) cchg(1,1,n,id[x],id[deg[top[x]]],clr[x]?-1:1),clr[x]^=1;
		else printf("%d\n",csk(x));
	}return 0;
}

```

---

## 作者：arfa (赞：1)

![](https://i.loli.net/2018/08/07/5b69203423c82.png)

由于刚刚学树剖所以来刷刷水题。不会树剖的同学可以果断右转 : [$blog$](https://www.cnblogs.com/FibonacciHeap/articles/9797374.html)。

这道题的思路就是一直从点 $x$ 往上跳,一直到 $root$ (也就是 $1$)。在其中每一次都查询一遍 $x$ 到 $top[x]$ 的最高的黑点。

先随便画一个图 : 

![](https://cdn.luogu.com.cn/upload/pic/38569.png)

其中我们把 $white$ 定义为 $val$ 的 $0$,$black$ 为 $1$。

![](https://cdn.luogu.com.cn/upload/pic/38570.png)

假设我们从 $10$ 号节点开始跳。先跳到 $10$ 的链顶的父亲。

![](https://cdn.luogu.com.cn/upload/pic/38571.png)

我们会发现 $min\ dfn=10$ 但是 $dfn$ 为 $10$ 的节点还是 $white$,所以 $ans=inf$。

从 $4$ 往上跳。

![](https://cdn.luogu.com.cn/upload/pic/38572.png)

$4$ 是 $black$,现在是 $ans=8$ (因为是 $dfn$)。最后跳到 $1$ 发现 $1$ 是 $black$,结束。

关于线段树的维护,我们要维护的是区间最小值。且所有叶子节点只保留 $inf$ 或者是 叶子节点的位置 代表 $white$ 或者 $black$。(线段树维护错了让我错了半个板子)

然后有一个优化,如果 $root$ 是 $black$,直接输出。(虽然没有数据是这样子的)

```pascal
Uses math;

var
    recf,cnt,size,dfn,dep,top,father,son:array[-1..210000] of longint;
    next,reach:array[-1..450000] of longint;
    left,right:array[-1..450000] of longint;
    tree:array[-1..450000] of int64;
    i,n,m,l,r,dfnum,tot,root,order,ans,root_place:longint;

procedure add(l,r:longint);
begin
    inc(tot);
    reach[tot]:=r;
    next[tot]:=cnt[l];
    cnt[l]:=tot;
end;

procedure Dfs_1(x:longint);
var i:longint;
begin
    size[x]:=1; i:=cnt[x]; size[0]:=-maxlongint div 843;
    while i<>-1 do
    begin
        if dep[reach[i]]=0 then
        begin
            dep[reach[i]]:=dep[x]+1;
            father[reach[i]]:=x;
            Dfs_1(reach[i]); inc(size[x],size[reach[i]]);
            if size[reach[i]]>size[son[x]] then son[x]:=reach[i];
        end;
        i:=next[i];
    end;
end;

procedure Dfs_2(x,centre:longint);
var i:longint;
begin
    inc(dfnum); dfn[x]:=dfnum; recf[dfnum]:=x; top[x]:=centre;
    if son[x]=0 then exit; Dfs_2(son[x],centre);
    i:=cnt[x];
    while i<>-1 do
    begin
        if (reach[i]<>father[x])and(reach[i]<>son[x]) then Dfs_2(reach[i],reach[i]);
        i:=next[i];
    end;
end;

procedure Build(k,l,r:longint);
var mid:longint;
begin
    left[k]:=l; right[k]:=r;
    if (l=r) then begin if l=1 then root_place:=k; tree[k]:=maxlongint; exit; end;
    mid:=(l+r) >> 1;
    Build(k << 1,l,mid); Build(k << 1+1,mid+1,r);
    tree[k]:=maxlongint;
end;

procedure Change(k,x:longint);
var mid:longint;
begin
    if left[k]=right[k] then
    begin
        if tree[k]=maxlongint then tree[k]:=left[k] else tree[k]:=maxlongint;
        exit;
    end;
    mid:=(left[k]+right[k]) >> 1;
    if x<=mid then Change(k << 1,x) else Change(k << 1+1,x);
    tree[k]:=min(tree[k << 1],tree[k << 1+1]);
end;

function Query(k,x,y:longint):longint;
var mid:longint;
begin
    Query:=maxlongint div 84;
    if (x<=left[k])and(right[k]<=y) then exit(tree[k]);
    mid:=(left[k]+right[k]) >> 1;
    if (x<=mid) then Query:=min(Query,Query(k << 1,x,y));
    if (y>mid) then Query:=min(Query,Query(k << 1+1,x,y));
end;

procedure Refer(x:longint);
begin
    if tree[root_place]<>maxlongint then begin ans:=1; exit; end;
    while top[x]<>root do
    begin
        ans:=min(ans,Query(1,dfn[top[x]],dfn[x]));
        x:=father[top[x]];
    end;
    ans:=min(ans,Query(1,dfn[root],dfn[x]));
    if ans>maxlongint div 85 then ans:=-1;
end;

begin
    filldword(cnt,sizeof(cnt) div 4,maxlongint*2+1);
    read(n,m); root:=1; recf[-1]:=-1;
    for i:=1 to n-1 do begin read(l,r); add(l,r); add(r,l); end;
    dep[root]:=1; father[root]:=1;
    Dfs_1(root); Dfs_2(root,root); Build(1,1,n);
    for i:=1 to m do
    begin
        read(order); ans:=maxlongint div 84;
        if order=0 then begin read(l); Change(1,dfn[l]); end;
        if order=1 then begin  read(l); Refer(l); writeln(recf[ans]); end;
    end;
end.
```

---

## 作者：Tweetuzki (赞：1)

树链剖分 + 树状数组 + 倍增。

考虑将找到 $1 \rightarrow u$ 的第一个黑色点 $v$ 这个问题转化一下，可以变成求 $1 \rightarrow u$ 这条路径上，找到一个深度最浅的点 $v$，满足 $1 \rightarrow v$ 这条路径上有黑色节点。

这时可以将黑色节点的值赋为 $1$，白色节点的值赋为 $0$。那么现在要做的，就是找到一个深度最浅的点 $v$，满足 $1 \rightarrow v$ 这条路径之和大于 $0$。查和可以用树剖 + 树状数组实现，而寻找时可以倍增实现。

这样对于每次查询，倍增需要花费 $\log N$，在倍增基础上套个树剖，又来个 $\log N$，再套个树状数组…… 最坏时间复杂度是 $O(Q \log^3 N)$ 的…… 但是这种做法的常数极小，对于本题最大的一个点，可以在 $115 \text{ms}$ 内跑出结果。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MaxN = 100000 + 5;
const int MaxQ = 400000 + 5;
const int MaxM = 200000 + 5;
const int MaxLog = 20;

int N, Q;
int cntv, cnte;
int Opt[MaxQ], X[MaxQ];
int Head[MaxN], To[MaxM], Next[MaxM];
int fa[MaxLog + 1][MaxN], size[MaxN], depth[MaxN];
int dfn[MaxN], id[MaxN], wson[MaxN], top[MaxN];
int Bit[MaxN];

inline void add_edge( int from, int to ) {
    cnte++; To[cnte] = to;
    Next[cnte] = Head[from]; Head[from] = cnte;
}

void init() {
    scanf( "%d %d", &N, &Q );
    for ( int i = 1; i < N; ++i ) {
        int u, v;
        scanf( "%d %d", &u, &v );
        add_edge( u, v ); add_edge( v, u );
    }
    for ( int i = 1; i <= Q; ++i )
        scanf( "%d %d", &Opt[i], &X[i] );
}

void dfs1( int u ) {
    size[u] = 1;
    for ( int i = Head[u]; i; i = Next[i] ) {
        int v = To[i];
        if ( v == fa[0][u] ) continue;

        depth[v] = depth[u] + 1;
        fa[0][v] = u;
        for ( int j = 1; ( 1 << j ) <= depth[v]; ++j )
            fa[j][v] = fa[ j - 1 ][ fa[ j - 1 ][v] ];

        dfs1( v );
        size[u] += size[v];

        if ( size[v] > size[ wson[u] ] ) wson[u] = v;
    }
}

void dfs2( int u, int chain ) {
    dfn[++cntv] = u;
    id[u] = cntv;
    top[u] = chain;

    if ( wson[u] != 0 ) dfs2( wson[u], chain );
    for ( int i = Head[u]; i; i = Next[i] ) {
        int v = To[i];
        if ( v == fa[0][u] || v == wson[u] ) continue;
        dfs2( v, v );
    }
}

inline int lowbit( int x ) {
    return x & -x;
}

inline void update( int x, int v ) {
    for ( int i = x; i <= N; i += lowbit( i ) )
        Bit[i] += v;
}

inline int query( int x ) {
    int res = 0;
    for ( int i = x; i > 0; i -= lowbit( i ) )
        res += Bit[i];
    return res;
}

inline int RSQ( int l, int r ) {
    return query( r ) - query( l - 1 );
}

inline int Query_path( int u, int v ) {
    int sum = 0;
    while ( top[u] != top[v] ) {
        if ( depth[ top[u] ] < depth[ top[v] ] ) swap( u, v );
        sum += RSQ( id[ top[u] ], id[u] );
        u = fa[0][ top[u] ];
    }

    if ( depth[u] < depth[v] ) swap( u, v );
    sum += RSQ( id[v], id[u] );
    return sum;
}

void solve() {
    dfs1( 1 );
    dfs2( 1, 1 );

    for ( int q = 1; q <= Q; ++q ) {
        int opt = Opt[q], u = X[q];
        if ( opt == 0 ) {
            int col = RSQ( id[u], id[u] );
            if ( col == 0 ) update( id[u], 1 );
            else update( id[u], -1 );
        } else {
            if ( Query_path( 1, u ) == 0 ) {
                printf( "-1\n" );
                continue;
            }

            for ( int i = MaxLog; i >= 0; --i ) {
                int v = fa[i][u];
                if ( v == 0 ) continue;
                if ( Query_path( 1, v ) >= 1 ) u = v;
            }
            printf( "%d\n", u );
        }
    }
}

int main() {
    init();
    solve();
    return 0;
}
```

---

## 作者：devout (赞：0)

这道题其实可以不用维护那么多乱七八糟的东西

维护$\min$就可以了

因为白点我们不需要知道他在哪，所以我们把白点设成inf

对于黑点，我们可以把他当成一个权值为dfn[x]的点，其中dfn[x]表示原来编号为x的点重新标号之后的编号

因为答案问的是1到v的路径，从根节点到一个点的路径上dfn一定是递增的，所以我们树剖维护路径上的最小值就可以了

答案再取一个redf就可以了，redf[x]表示dfn为x的点原来的标号是多少

~~好久没有写过这么短的树剖了~~

```cpp
# include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)
# define debug puts("QAQ");

typedef long long ll;
const int N=1e5+5;
const int mod=1e9+7;
const double eps=1e-7;

template <typename T> void read(T &x){
	x=0;int f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
	x*=f;
}

int n,q;
int head[N],cnt;
int faz[N],son[N],dep[N],siz[N],top[N],dfn[N],redf[N],tot;
bool col[N];

struct Edge{
	int to,next;
}e[N<<1];

void add(int x,int y){
	e[++cnt]=(Edge){y,head[x]},head[x]=cnt;	
}

# define lc (u<<1)
# define rc (u<<1|1)

struct segment_tree{
	int l,r,_min;
}seg[N<<2];

void build(int u,int l,int r){
	seg[u].l=l,seg[u].r=r;
	seg[u]._min=1e9;
	if(l==r)return;
	int mid=l+r>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);	
}

void update(int u,int x,int k){
	if(seg[u].l==seg[u].r){
		seg[u]._min=k;
		return;
	}
	int mid=seg[u].l+seg[u].r>>1;
	if(x<=mid)update(lc,x,k);
	else update(rc,x,k);
	seg[u]._min=min(seg[lc]._min,seg[rc]._min);
}

int query(int u,int l,int r){
	if(seg[u].l>=l&&seg[u].r<=r)return seg[u]._min;
	int mid=seg[u].l+seg[u].r>>1;
	if(r<=mid)return query(lc,l,r);
	if(l>mid)return query(rc,l,r);
	return min(query(lc,l,r),query(rc,l,r));	
}

int RouteQueryMin(int x,int y){
	int res=1e9;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res=min(res,query(1,dfn[top[x]],dfn[x]));
		x=faz[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	res=min(res,query(1,dfn[x],dfn[y]));
	return res<1e9?redf[res]:-1;
}

void dfs1(int u,int fa){
	faz[u]=fa;
	siz[u]=1;
	dep[u]=dep[fa]+1;
	RepG(i,u){
		int v=e[i].to;
		if(v==fa)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}

void dfs2(int u,int _top){
	top[u]=_top;
	dfn[u]=++tot;
	redf[tot]=u;
	if(!son[u])return;
	dfs2(son[u],_top);
	RepG(i,u){
		int v=e[i].to;
		if(v==faz[u]||v==son[u])continue;
		dfs2(v,v);
	}
}

int main()
{	memset(head,-1,sizeof(head));
	read(n),read(q);
	Rep(i,1,n-1){
		int x,y;
		read(x),read(y);
		add(x,y),add(y,x); 
	}
	dfs1(1,0),dfs2(1,1);
	build(1,1,n);
	while(q--){
		int opt,x;
		read(opt),read(x);
		if(!opt)update(1,dfn[x],col[x]?1e9:dfn[x]),col[x]^=1;
		else printf("%d\n",RouteQueryMin(1,x));	
	}
	return 0;
}

```


---

## 作者：LevenKoko (赞：0)

首先双倍经验：有一道稍微改一下就可以A掉的：
P4092 [HEOI2016/TJOI2016]树 

依然是在重链上二分的大暴力做法...

貌似很多大佬是set、priority_queue的做法

那种里就来一发线段树的做法

像一般的树剖一样线段树维护重链上的信息

这里需要维护区间和，并支持单点更改

1代表黑，0代表白

显然对于树上某一段链，如果其中sum>0,说明其中有黑色的点，然后显然要选深度最小的黑，我们只需要二分即可，如果在mid上面有黑点（sum>0）那就在上面一段查找，否则在下面一段查找...

需要注意的是这里要求1~v的黑点，也就是离1最近的点...刚开始去求离v最近的黑点了...WA0分了好多次

总体时间复杂度$O(nlog^{2}n)$

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define writeln(x)  write(x),puts("")
using namespace std;
inline int read(){
	int ans=0,f=1;char chr=getchar();
	while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
	while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
	return ans*f;
}void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}const int M=100005;char opt[2];
int head[M<<1],ver[M<<1],x,y,nxt[M<<1],tot,n,m,dep[M],fa[M],tp[M],sz[M],son[M],idx[M],s[M<<2],rk[M];
inline void add(int x,int y){ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;}
void dfs1(int x,int f){
	sz[x]=1;dep[x]=dep[f]+1,fa[x]=f;
	for(register int i=head[x];i;i=nxt[i]){
		if(!dep[ver[i]]){
			dfs1(ver[i],x),sz[x]+=sz[ver[i]];
			if(sz[son[x]]<sz[ver[i]]) son[x]=ver[i];
		}
	}
}int t;
void dfs2(int x,int topf){
	idx[x]=++t;tp[x]=topf;rk[t]=x;
	if(!son[x]) return;
	dfs2(son[x],topf);
	for(int i=head[x];i;i=nxt[i])
		if(!idx[ver[i]]) dfs2(ver[i],ver[i]);
}
#define ls (i<<1)
#define rs (i<<1|1)
#define mid (l+r>>1)
inline void Push_Up(int i){s[i]=s[ls]+s[rs];}
void Update(int i,int l,int r,int pos,int x){
	if(l==r){s[i]^=1;return;}
	if(pos<=mid) Update(ls,l,mid,pos,x);
	else Update(rs,mid+1,r,pos,x);
	Push_Up(i);
}
int Query(int i,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return s[i];int ans=0;
	if(ql<=mid) ans+=Query(ls,l,mid,ql,qr);
	if(qr>mid)  ans+=Query(rs,mid+1,r,ql,qr);
	return Push_Up(i),ans;
}int a[M],L[M],R[M];
inline void Ask(int x){
	int tt=0;
	while(x){
		a[++tt]=Query(1,1,n,idx[tp[x]],idx[x]);
		L[tt]=idx[tp[x]];
		R[tt]=idx[x];//L,R记录区间左右端点 
		x=fa[tp[x]];
	}reverse(a+1,a+tt+1);
	 reverse(L+1,L+tt+1);
	 reverse(R+1,R+tt+1);//因为要求离1最近的黑点，所以要翻转过来 
	a[tt+1]=1;int pos=tt+1;
	for(int i=1;i<=tt+1;i++) if(a[i]) {tt=i;break;}//找到离1最近的黑点所在区间 
	if(tt==pos) return (void)(puts("-1"));//不存在黑点 
	int ll=L[tt],rr=R[tt],midd,ans;
	while(ll<=rr){//二分
		midd=ll+rr>>1;
		if(Query(1,1,n,ll,midd)) rr=midd-1,ans=midd;
		else ll=midd+1;
	}writeln(rk[ans]);//对应回来 
}
int main(){
	n=read(),m=read();
	for(register int i=1;i<n;++i)x=read(),y=read(),add(x,y),add(y,x);
	dfs1(1,0),dfs2(1,1);
	while(m--){
		int opt=read(),x=read();
		if(opt==1)	Ask(x);
		else Update(1,1,n,idx[x],1);
	}
	return 0;
}
```

---

## 作者：Jμdge (赞：0)

这题好像还是挺简单的


# noteskey

我们考虑树剖处理 top 

## update

然后每次一个点更新了就去 push 或者 erase 它的 top 节点

然后 top 节点里面维护的所有节点按 dep 升序排序（可以用 **大根堆 + pair + dep** 取反 实现）


## query

每次询问我们从询问点 x 出发，爆跳 top ，然后沿路维护答案（注意 top 节点里面维护的节点不一定来自 x 所在的子树，所以我们需要判断 top 节点堆顶的 dep 是否小于 x 的 dep ）


# 关于带删除 priority_queue

安利博客： [支持删除任意元素以及一些其他基本操作的堆](https://www.cnblogs.com/Judge/p/10557516.html)

我们发现用了这个实现简单然鹅功能神奇的数据结构后这道题会变的非常好做

（你可能会说用 set 更方便但是我觉得用堆可能会快些？）

# code

```
//by Judge
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define P pair<int,int>
#define fp(i,a,b) for(int i=(a),I=(b)+1;i<I;++i)
#define go(G,u) for(int i=G.head[u],v=G.e[i].to;i;v=G.e[i=G.e[i].nxt].to)
using namespace std;
const int M=1e5+3;
typedef int arr[M];
inline int read(){ int x=0,f=1; char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} inline int cread(){ char c=getchar();
    while(c!='K'&&c!='I'&&c!='O') c=getchar();
	return c=='I'?1:c=='K'?2:3;
} char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x,char chr='\n'){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]=chr;
} int n,m,tim; arr state,siz,dep,fa,son,top;
struct Heap{ priority_queue<P> q1,q2;
	inline void push(int x){q1.push(P(-dep[x],x));}
	inline void erase(int x){q2.push(P(-dep[x],x));}
	inline int size(){return q1.size()-q2.size();}
	inline void pop(){for(;q2.size()&&q2.top()==q1.top();q1.pop(),q2.pop());q1.pop();}
	inline int top(){for(;q2.size()&&q2.top()==q1.top();q1.pop(),q2.pop());return q1.top().second;}
}q[M];
struct Gr{ int pat,head[M];
    struct Edge{ int to,nxt; }e[M<<1];
    inline void clear(){ memset(head,0,sizeof head),pat=0; }
    inline void add(int u,int v){
        e[++pat]={v,head[u]},head[u]=pat;
        e[++pat]={u,head[v]},head[v]=pat;
    }
}G;
void dfs(int u,int f){ siz[u]=1,dep[u]=dep[f]+1;
    go(G,u) if(v^f){ fa[v]=u,dfs(v,u);
		siz[u]+=siz[v]; if(siz[v]>siz[son[u]]) son[u]=v; }
}
void dfs(int u){ if(!top[u]) top[u]=u;
    if(son[u]) top[son[u]]=top[u],dfs(son[u]);
    go(G,u) if(v^fa[u]&&v^son[u]) dfs(v);
}
inline int query(int x){ int ans=-1;
	for(;x;x=fa[top[x]]) if(q[top[x]].size())
		if(dep[q[top[x]].top()]<=dep[x])
			ans=q[top[x]].top(); return ans;
}
int main(){ n=read(),m=read(); int op,x,y,z;
	fp(i,1,n-1) x=read(),y=read(),G.add(x,y);
	for(dfs(1,0),dfs(1);m;--m){ op=read(),x=read();
		if(op) print(query(x));
		else{ state[x]^=1;
			if(state[x]) q[top[x]].push(x);
			else q[top[x]].erase(x);
		} 
	}return Ot(),0;
}
```

---

## 作者：Kelin (赞：0)

题意:问$1->v$路径上第一个黑点

考虑$1->v$的的一条链,我们只要维护这条链上深度最小的黑点就$ok$了

然后这条链又可以树链剖分分成很多条重链

所以我们每条重链维护一个可支持删除的堆

每次询问问堆里深度最小的点,注意特判深度最小的点的深度是否大于当前点深度 

复杂度$o(nlog^2n)$,但是常数极小

注意$1->v$的路径,不是$v->1$的路径,一开始以为是$v->1$还以为自己$set$挂了 

---

## 作者：yqw2486 (赞：0)

第一次把题目看错，，，，，
题目要求的是第一个黑点的编号，直接看了一下样例数据~~以为是求编号最小的黑点~~；

------------------------------------------------
树上更新和查询，所以想到树链剖分；

从1到v第一个黑点的编号，则以1为根对树进行第二遍dfs的时候重新编号，同一条重链上编号越小必然越靠近根；因此线段树中定义一个最小值minv保存新的编号即id[x]；不难发现光保存minv还不行，因为有可能不存在黑点，因此再定义一个has标记在区间中是否含有黑点。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005,inf=1e9;
int fir[N],to[N*2],nxt[N*2],cnt;
int fa[N],depth[N],top[N],size[N],son[N],inG[N],id[N];
struct node{
	int l,r,mid,minv,has;
	node(int a=0,int b=0):l(a),r(b){mid=(a+b)>>1;has=0;minv=inf;}
}tree[N*4];
void addEdge(int f,int t){
	to[++cnt]=t;nxt[cnt]=fir[f];fir[f]=cnt;
}
void build(int rt,int l,int r){
	tree[rt]=node(l,r);
	if(l==r)return;
	int mid=(l+r)>>1,ls=rt<<1,rs=ls+1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void dfs(int u,int fu){
	depth[u]=depth[fu]+1;fa[u]=fu;size[u]=1;
	for(int i=fir[u];i;i=nxt[i])
		if(to[i]!=fu){
			dfs(to[i],u);
			size[u]+=size[to[i]];
			if(size[to[i]]>size[son[u]])
				son[u]=to[i];
		}
}
void dfs1(int u,int k){
	top[u]=k;id[u]=++cnt;inG[cnt]=u;
	if(son[u])dfs1(son[u],k);
	for(int i=fir[u];i;i=nxt[i])
		if(to[i]!=fa[u]&&to[i]!=son[u])
			dfs1(to[i],to[i]);
}
void update(int rt,int x){
	if(tree[rt].l==tree[rt].r){
		tree[rt].has^=1; //更新一次就和1异或一次 
		if(tree[rt].has)tree[rt].minv=x;//有黑点则minv更新为x即新的编号，因为编号越小则越靠前
		else tree[rt].minv=inf;//没有黑点就更新为无穷大 
		return;
	}
	int mid=tree[rt].mid,ls=rt<<1,rs=ls+1;
	if(x<=mid)update(ls,x);
	else update(rs,x);
	tree[rt].minv=min(tree[ls].minv,tree[rs].minv);
	tree[rt].has=tree[ls].has|tree[rs].has;
}
int query(int rt,int l,int r){
	if(tree[rt].l==l&&tree[rt].r==r)return tree[rt].minv;
	if(!tree[rt].has) return inf;//提高不存在的情况的查询 
	int mid=tree[rt].mid,ls=rt<<1,rs=ls+1;
	if(l>mid)return query(rs,l,r);
	if(r<=mid)return query(ls,l,r);
	return min(query(ls,l,mid),query(rs,mid+1,r));
}
int getMin(int x,int y){
	int ans=inf;
	while(top[x]!=top[y]){
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		ans=min(ans,query(1,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(depth[x]>depth[y])swap(x,y);
	ans=min(ans,query(1,id[x],id[y]));
	if(ans==inf)ans=-1;
	else ans=inG[ans];
	return ans;
}
int main(){
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		addEdge(x,y);
		addEdge(y,x);
	}
	dfs(1,0);
	cnt=0;
	dfs1(1,1);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		if(x)printf("%d\n",getMin(1,y));
		else update(1,id[y]);
	}
	return 0;
} 
```




---

## 作者：zhengzhi726 (赞：0)

其实这个题比较基本但是本蒟蒻一个小地方却改了三四次……（uv混了）

顺便说一下对树剖的理解

本蒟蒻表达能力惊人（吓人）欢迎纠正病句

在noip里其实树剖是个有用而能解决很多问题的东西

树剖解决的是树的区间问题

对于数组的遍历一般是on的循环 而对于树就是dfs 针对问的问题dfsn次一般是一个有用的暴力做法

但是如果题目要求100000呢？显然nlogn的复杂度是首选
可是除了lca这样可以幻化为区间rmq的问题 nlogn太小了 因为logn次代表每次删除树的一半（就像点分治）这样本身只能解决与距离有关的问题

数据结构上树是一个好的思想 一些高效的数据结构比如单调队列单调栈是on的但是树的询问一般有可合并性 这种数据结构只能解决链上问题（还是要把链领出来）

同时我们发现领出来大链会对树的整体构型造成难以平复的弥天大过 拆开了树

树链剖分和更加具有可合并性的线段树--树剖

实链剖分和更具有拆分合并功能的splay产生了-lct

树剖维护的就是区间的合并性问题

区间可以做的 当然放到树上也可以做

区间的线段树本来就很难了 放到树上其实难度还是线段树维护的那个问题、

还有一种情况 就是利用树剖性质 每次更新答案

对于本题 现在的解法我都莫名觉得难了

这个东西只需要运用另外那种情况 黑节点存id 白点inf

每次区间min如果这次的min不是inf替换原来的即可
………………
………………
代码
………………
………………



```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define ll long long
#define inf 1000000000
#define lson (node<<1)
#define rson (lson+1)
struct edge{
    ll from,to;
};vector<int>g[maxn];vector<edge>edges;
ll n,m,k=0,a,b,c,depth[maxn],sz[maxn],wson[maxn],idx[maxn],id[maxn],visit[maxn],ans=0,num=0,val[maxn],top[maxn],fa[maxn];
ll tree[maxn*4];
void add_edge(int f,int t){
    g[f].push_back(k);edges.push_back({f,t});g[t].push_back(k+1);edges.push_back({t,f});k+=2;
}void build(int node,int l,int r){
    if(l==r){tree[node]=inf;return ;}
    int mid=(l+r)>>1;
    build(lson,l,mid);build(rson,mid+1,r);
    tree[node]=inf;
}void add(int node,int l,int r,int x){
    if(l==x&&x==r){if(val[idx[l]]==1)tree[node]=l;else tree[node]=inf;return ;
	}int mid=(l+r)>>1;
    if(x<=mid)add(lson,l,mid,x);
    else add(rson,mid+1,r,x);
    tree[node]=min(tree[lson],tree[rson]);
}ll query(int node,int l,int r,int x,int y){
    if(x>y)return 0;
    if(l==x&&y==r){return tree[node];}
    int mid=(l+r)>>1;
    if(y<=mid)return query(lson,l,mid,x,y);
    else if(x>=mid+1) return query(rson,mid+1,r,x,y);
    else return min(query(lson,l,mid,x,mid),query(rson,mid+1,r,mid+1,y));
}void dfs1(int u){visit[u]=sz[u]=depth[1]=1;
    for(int i=0;i<g[u].size();i++){
        edge &e=edges[g[u][i]];if(visit[e.to])continue;
        depth[e.to]=depth[u]+1;fa[e.to]=u;
        dfs1(e.to);
        sz[u]+=sz[e.to];if(sz[wson[u]]<sz[e.to])wson[u]=e.to;
    }
}void dfs2(int u){
    top[1]=1;id[u]=++num,idx[num]=u;visit[u]=1;
    if(wson[u]!=0){
        top[wson[u]]=top[u];dfs2(wson[u]);
    }
    for(int i=0;i<g[u].size();i++){
        edge &e=edges[g[u][i]];if(visit[e.to]||wson[u]==e.to)continue;
        top[e.to]=e.to;dfs2(e.to);
    }
}ll querymin(int u,int v){ll ans=inf,now=inf;
    while(top[v]!=1){
        now=query(1,1,n,id[top[v]],id[v]);
        if(now!=inf)ans=now;
        v=fa[top[v]];
    }
    now=query(1,1,n,1,id[v]);
    if(now!=inf)ans=now;
    return ans;
}int main(){
    cin>>n>>m;
    for(int i=1;i<n;i++)cin>>a>>b,add_edge(a,b);
    dfs1(1);memset(visit,0,sizeof(visit));dfs2(1);
    build(1,1,n);
    for(int i=1;i<=m;i++){
    	cin>>a>>b;
    	if(a==0){val[b]=1-val[b];
    		add(1,1,n,id[b]);
		}
		else{
			int mx=querymin(1,b);if(mx==inf)cout<<"-1"<<endl;
			else
			cout<<idx[mx]<<endl;
		} 
	}
}
```


---

