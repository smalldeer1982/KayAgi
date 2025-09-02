# ADAAPPLE - Ada and Apple

## 题目描述

Ada the Ladybug is currently on a trip on apple [tree](https://en.wikipedia.org/wiki/Tree_(data_structure)). There are many apples on the tree connected with branches. Each apple is inhabited by either Psylloideas or by Woolly Apple Aphids. Psylloideas and Aphids doesn't like each other, so it is strictly prohibited to walk from apple of Psylloideas to apple of aphids (and vice versa). Ada has some questions, whether it is possible to go from node **I** to node **J**.

Anyway note, that as Aphids and Psyllodeas doesn't like each other, they sometime conquer an apple of the others. Also note, that it is a real apple tree (not some bush) so no apple is connected with more than 50 other apples.

# 题解

## 作者：CaoSheng_zzz (赞：2)

第一眼树上节点权值操作，很容易想到树链剖分。

想到树链剖分之后本题就很板了。

对于节点编号从 $0$ 开始我们直接将所有节点编号 $+1$。

对于操作 $0$，由于是单点修改所以直接定位到点，当然也可以把点当成一个区间，定义 $lazy$ 为当前这段区间是否有异或操作，有的话当前区间权值为区间大小减去当前权值，然后其他就是板子。

对于操作 $1$，我们查询这条链上的权值之和然后去判断权值是否为 $0$ 或链上的总点数。

Code：
```cpp
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <map>
#include <set>
#define prt printf
#define ll long long
#define spc putchar(' ')
#define ent putchar('\n')
#define pr_ prt("---")
#define prx prt("***")
#define prtn (putchar('N') , putchar('o'))
#define prty (putchar('Y') , putchar('e') , putchar('s'))

inline ll read() {
	bool f = 1 ; ll k = 0;
	char c = getchar() ;
	while(c < '0' || c > '9') {
		f = c == '-' ? 0 : 1 ;
		c = getchar() ;
	}
	while(c >= '0' && c <= '9') {
		k = (k << 3) + (k << 1) + (c ^ 48);
		c = getchar() ;
	}
	return (f == 1 ? k : -k);
}

void output(ll now) {
	if(now < 0){
		putchar('-');
		output(- now);
	}
	else{
		if(now > 9) output(now / 10);
		putchar((now % 10) ^ 48);
	}
}

inline ll max(ll a , ll b) { return a > b ? a : b ;}
inline ll min(ll a , ll b) { return a < b ? a : b ;}

#define ls k << 1 
#define rs k << 1 | 1 
const int maxn = 3e5 + 1 ;
struct SegTree {
	int l , r ;
	int val ;
	bool lazy ;
} tree[maxn << 2] ;
int a[maxn] ;
int n , q ;
struct edge {
	int next , to ;
} e[maxn << 1];
int h[maxn] , cnt ;
int anc[maxn] , deep[maxn] , size[maxn] , son[maxn] ;
int b[maxn] , f[maxn] , top[maxn] , idx ;
int rt , mod ;

void push_up(int k) { tree[k].val = tree[ls].val + tree[rs].val ;}
void push_down(int k) {
	if(! tree[k].lazy) return ;
	tree[ls].lazy ^= true ;
	tree[rs].lazy ^= true ;
	tree[ls].val = tree[ls].r - tree[ls].l + 1 - tree[ls].val ;
	tree[rs].val = tree[rs].r - tree[rs].l + 1 - tree[rs].val ;
	tree[k].lazy = false ;
}

void build(int k , int l , int r) {
	tree[k].l = l , tree[k].r = r ;
	if(l == r) {
		tree[k].val = a[f[l]] ;
		return ;
	}
	int mid = (l + r) >> 1 ;
	build(ls , l , mid) , build(rs , mid + 1 , r) ;
	push_up(k) ;
}

void Change(int k , int l , int r) {
	if(tree[k].l > r || tree[k].r < l) return ;
	if(l <= tree[k].l && tree[k].r <= r) {
		tree[k].val = tree[k].r - tree[k].l + 1 - tree[k].val ;
		tree[k].lazy ^= true ;
		return ;
	}
	push_down(k) ;
	Change(ls , l , r) , Change(rs , l , r) ;
	push_up(k) ;
}

int Ask(int k , int l , int r) {
	if(tree[k].l > r || tree[k].r < l) return 0 ;
	if(l <= tree[k].l && tree[k].r <= r) return tree[k].val ;
	push_down(k) ;
	return Ask(ls , l , r) + Ask(rs , l , r) ;
}

void Add(int u , int v) { e[++ cnt] = {h[u] , v} ; h[u] = cnt ;}

void dfs(int u , int fa){
	anc[u] = fa , deep[u] = deep[fa] + 1 , size[u] = 1 ;
	for(int i=h[u] ; i ; i=e[i].next) {
		int v = e[i].to ;
		if(v == fa) continue; ;
		dfs(v , u) ;
		size[u] += size[v] ;
		if(size[v] > size[son[u]]) son[u] = v ;
	}
}

void dfs_2(int u , int t) {
	b[u] = ++ idx , f[idx] = u , top[u] = t ;
	if(! son[u]) return ;
	dfs_2(son[u] , t) ;
	for(int i=h[u] ; i ; i=e[i].next) {
		int v = e[i].to ;
		if(v == anc[u] || v == son[u]) continue; ;
		dfs_2(v , v) ;
	}
}

//void change(int u , int v) {
//	while(top[u] != top[v]) {
//		if(deep[top[u]] < deep[top[v]]) std::swap(u , v) ;
//		Change(1 , b[top[u]] , b[u]) ;
//		u = anc[top[u]] ;
//	}
//	if(deep[u] > deep[v]) std::swap(u , v) ;
//	Change(1 , b[u] , b[v]) ;
//}

bool get(int u , int v) {
	int res = 0 , ret = 0 ;
	while(top[u] != top[v]) {
		if(deep[top[u]] < deep[top[v]]) std::swap(u , v) ;
		res += Ask(1 , b[top[u]] , b[u]) ;
		ret += b[u] - b[top[u]] + 1 ;
		u = anc[top[u]] ;
	}
	if(deep[u] > deep[v]) std::swap(u , v) ;
	res += Ask(1 , b[u] , b[v]) ;
	ret += b[v] - b[u] + 1;
//	output(res) , spc , output(ret) , ent ;
	return ! res || res == ret ;
}

signed main() {
	n = read() , q = read() ;
	for(int i=1 ; i<=n ; i++) {
		char cap = getchar() ;
		while(cap == ' ' || cap == '\n') cap = getchar() ;
		a[i] = cap ^ 48 ;
	}
	for(int i=1 ; i<n ; i++) {
		int u = read() + 1 , v = read() + 1 ;
//		output(u) , spc , output(v) , ent ;
		Add(u , v) , Add(v , u) ;
	}
	dfs(1 , 1) , dfs_2(1 , 1) ;
	build(1 , 1 , n) ;
	while(q --) {
		int opt = read() ;
		if(opt == 0) {
			int u = read() + 1 ;
			Change(1 , b[u] , b[u]) ;
		}
		else {
			int u = read() , v = read() ;
			puts(get(u + 1 , v + 1) ? "YES" : "NO") ;
		}
	}
	return 0 ;
}
```

---

## 作者：lunjiahao (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/SP30785)

[博客园](https://www.cnblogs.com/lunjiahao/p/18521575)**可能**食用更佳
### 题目大意：

给定一棵权值为 $0$ 或 $1$ 的树，$n$ 个点，$q$ 次操作：

- `0 i` 把结点 $i$ 的权值取反；

- `1 i j` 询问点 $i$ 到点 $j$ 的最短路径上权值是否全为 $0$ 或全为 $1$。

### 题目分析：

树上操作，看了下操作发现是树剖板子题。

开一棵线段树，操作一单点取反，考虑维护懒标记 $tag$ 记录结点的取反状态即可，操作二求一下路径上权值总和，再与最短路径长度比较一下即可。

时间复杂度：$\mathcal O(q \log n)$。

### Code：

```cpp
#include<bits/stdc++.h>
#define ls u<<1
#define rs u<<1|1
#define il inline
#define pb push_back
using namespace std;
il int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48),ch=getchar();}return x*f;}
il char getc(){char ch=getchar();while(ch=='\n'||ch=='\r'||ch==' ')ch=getchar();return ch;}
const int N=3e5+5;
int n,q,a[N];
vector<int> g[N];
int fa[N],dep[N],siz[N],hs[N];
void dfs1(int u,int fath)
{
	fa[u]=fath,dep[u]=dep[fath]+1;
	siz[u]=1,hs[u]=-1;
	for(auto v:g[u])
	{
		if(v==fath) continue;
		dfs1(v,u),siz[u]+=siz[v];
		if(hs[u]==-1||siz[v]>siz[hs[u]]) hs[u]=v;
	}
}
int cnt,top[N],w[N],pos[N];
void dfs2(int u,int t)
{
	top[u]=t,pos[w[u]=++cnt]=u;
	if(~hs[u]) dfs2(hs[u],t);
	for(auto v:g[u])
		if(v^hs[u]&&fa[u]^v) dfs2(v,v);
}
int t[N<<2],tag[N<<2];
void push_up(int u) {t[u]=t[ls]+t[rs];}
void build(int u,int l,int r)
{
	if(l==r) return t[u]=a[pos[l]],void();
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	push_up(u);
}
void push_down(int u,int l,int r)
{
	if(!tag[u]) return;
	tag[ls]^=1,tag[rs]^=1;
	int mid=(l+r)>>1;
	t[ls]=mid-l+1-t[ls],t[rs]=r-mid-t[rs];
	tag[u]=0;
}
void update(int u,int l,int r,int x,int y)
{
	if(y<l||r<x) return;
	if(x<=l&&r<=y) return tag[u]^=1,t[u]=r-l+1-t[u],void();
	push_down(u,l,r);
	int mid=(l+r)>>1;
	if(x<=mid) update(ls,l,mid,x,y);
	if(y>mid) update(rs,mid+1,r,x,y);
	push_up(u);
}
int query(int u,int l,int r,int x,int y)
{
	if(y<l||r<x) return 0;
	if(x<=l&&r<=y) return t[u];
	push_down(u,l,r);
	int mid=(l+r)>>1,res=0;
	if(x<=mid) res+=query(ls,l,mid,x,y);
	if(y>mid) res+=query(rs,mid+1,r,x,y);
	return res;
}
bool range_query(int u,int v)
{
	int ans=0,sum=0;
	while(top[u]^top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans+=query(1,1,n,w[top[u]],w[u]);
		sum+=w[u]-w[top[u]]+1;
		u=fa[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	ans+=query(1,1,n,w[v],w[u]);
	sum+=w[u]-w[v]+1;
	return !ans||ans==sum;
}
int main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=getc()^48;
	for(int i=1;i<n;i++)
	{
		int u=read()+1,v=read()+1;
		g[u].pb(v),g[v].pb(u);
	}
	dfs1(1,0),dfs2(1,1),build(1,1,n);
	while(q--)
	{
		int opt=read(),x=read()+1,y;
		if(opt&1) y=read()+1,puts(range_query(x,y)?"YES":"NO");
		else update(1,1,n,w[x],w[x]);
	}
	return 0;
}
```

---

## 作者：AC_love (赞：1)

树链剖分模板题。

每个点点权为 $0$ 或 $1$，每次操作对一个点的点权取反或询问一条路径上所有点的点权是否相等。

单点修改，区间查询。

查询的时候可以查一条路径上 $0$ 和 $1$ 的数量，然后 `return` 这俩里面有任何一个等于 $0$ 即可。

代码实现如下：

```cpp
#include <bits/stdc++.h>
#define tpl t[p].l
#define tpr t[p].r
#define tpn1 t[p].n1
#define tpn0 t[p].n0
#define t2pl t[p*2].l
#define t2pr t[p*2].r
#define t2pn1 t[p*2].n1
#define t2pn0 t[p*2].n0
#define t2p1l t[p*2+1].l
#define t2p1r t[p*2+1].r
#define t2p1n1 t[p*2+1].n1
#define t2p1n0 t[p*2+1].n0
using namespace std;

const int N = 3e5 + 3e4;
int n, q;

vector <int> e[N];
char val[N];

struct Node
{
	int top;
	int fa;
	int dep;
	int size;
	int son;
	int id;
	int w;
};

Node d[N];

void dfs1(int st, int fa, int dep)
{
	d[st].fa = fa;
	d[st].dep = dep;
	d[st].size = 1;
	for(int i = 0; i < e[st].size(); i = i + 1)
	{
		int ed = e[st][i];
		if(ed == fa) 
			continue;
		dfs1(ed, st, dep + 1);
		d[st].size += d[ed].size;
		if(d[ed].size > d[d[st].son].size)
			d[st].son = ed; 
	}
}

int cnt;
int nw[N];
void dfs2(int st, int top)
{
	cnt ++;
	nw[cnt] = d[st].w;
	d[st].id = cnt;
	d[st].top = top;
	if(!d[st].son)
		return;
	dfs2(d[st].son, top);
	for(int i = 0; i < e[st].size(); i = i + 1)
	{
		int ed = e[st][i];
		if(ed == d[st].fa || ed == d[st].son)
			continue;
		dfs2(ed, ed);
	}
}

struct tree
{
	int l;
	int r;
	int n0;
	int n1;
};

tree t[N * 4];

void pushup(int p)
{
	tpn0 = t2pn0 + t2p1n0;
	tpn1 = t2pn1 + t2p1n1;
}

void build(int p, int l, int r)
{
	tpl = l;
	tpr = r;
	if(l == r)
	{
		tpn0 = (nw[l] == 0);
		tpn1 = (nw[l] == 1);
		return;
	}
	int mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	pushup(p);
//	cout << p << " " << tpl << " " << tpr << " " << tpn0 << " " << tpn1 << "\n";
}

void change(int p, int w)
{
	if(tpl == tpr)
	{
		swap(tpn0, tpn1);
		return;
	}
	int mid = (tpl + tpr) / 2;
	if(mid >= w)
		change(p * 2, w);
	else
		change(p * 2 + 1, w);
	pushup(p);
}

tree ask(int p, int l, int r)
{
	if(l <= tpl && tpr <= r)
	{
//		cout << p << " " << tpn0 << " " << tpn1 << "\n";
		return t[p];
	}
	int mid = (tpl + tpr) / 2;
	tree ret;
	ret.n0 = 0, ret.n1 = 0;
	if(mid >= l)
	{
		tree tmp = ask(p * 2, l, r);
		ret.n0 += tmp.n0;
		ret.n1 += tmp.n1;
	}
	if(mid < r)
	{
		tree tmp = ask(p * 2 + 1, l, r);
		ret.n0 += tmp.n0;
		ret.n1 += tmp.n1;
	}
//	cout << ret.n0 << " " << ret.n1 << "???\n";
	return ret;
}

void changedot(int x)
{
	change(1, d[x].id);
}

bool askpath(int x, int y)
{
	tree ret;
	ret.n0 = 0;
	ret.n1 = 0;
	while(d[x].top != d[y].top)
	{
		if(d[d[x].top].dep < d[d[y].top].dep)
			swap(x, y);
		tree tmp = ask(1, d[d[x].top].id, d[x].id);
		ret.n0 += tmp.n0;
		ret.n1 += tmp.n1;
		x = d[d[x].top].fa;
//		cout << "   " << ret.n0 << " " << ret.n1 << "\n";
	}
	if(d[x].dep < d[y].dep)
		swap(x, y);
	tree tmp = ask(1, d[y].id, d[x].id);
	ret.n0 += tmp.n0;
	ret.n1 += tmp.n1;
//	cout << "   " << ret.n0 << " " << ret.n1 << "\n";
	return ((!ret.n0) || (!ret.n1));
}

signed main()
{
	cin >> n >> q;
	for(int i = 1; i <= n; i = i + 1)
	{
		while(val[i] != '1' && val[i] != '0')
			val[i] = getchar();
		d[i].w = val[i] - '0';
	}
	for(int i = 1; i <= n - 1; i = i + 1)
	{
		int st, ed;
		cin >> st >> ed;
		st += 1;
		ed += 1;
		e[st].push_back(ed);
		e[ed].push_back(st);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	while(q --)
	{
		int op;
		cin >> op;
		if(!op)
		{
			int w;
			cin >> w;
			w += 1;
			changedot(w);
		}
		else
		{
			int x, y;
			cin >> x >> y;
			x += 1;
			y += 1;
			bool flag = askpath(x, y);
			string s = flag ? "YES" : "NO";
			cout << s << "\n";
		}
	}
	return 0;
}
```

---

## 作者：National_Studying (赞：1)

正常树剖，用一棵支持区间查询，单点修改的线段树维护操作 $1$ 直接维护到点。

查询的时候可以查一条路径上 $0$ 和 $1$ 的数量，然后 `return` 任何一个等于 $0$ 即可。

---

## 作者：CaoSheng (赞：0)

考虑树链剖分。

维护线段树的时候对于操作 $1$ 直接维护到点，其余操作为板子。

需要注意节点编号从 $0$ 开始，使用前向星不想初始化的可以直接将所有节点编号 $+1$。

---

## 作者：Shxt_Plus (赞：0)

树剖板子题。

维护 $0$ 的个数，建一颗支持区间查询，单点修改的线段树，查询时判断 $0$ 的个数是不是 $r-l+1$ 或 $0$ 就行。

---

## 作者：ttq012 (赞：0)

首先上树剖，维护树上每一条链的最小值和最大值。

询问的时候就是询问当前询问的链上，最小值和最大值是不是相等即可。

这样做时间复杂度为 $O(n\log^2n)$，可以通过。

---

## 作者：Jerry_heng (赞：0)

（一）

树链剖分板子题。

支持单点取反，区间查询。

在线段树的每一个节点上分别记录全为 $1$ 或 全为 $0$。

代码挺好理解的。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxn=3e5+10;
int n,q,head[mxn],cnt,id[mxn],cntt,fa[mxn],cnt1,son[mxn],siz[mxn],a[mxn],tree[mxn<<2][2],top[mxn],dfn[mxn],dep[mxn];
struct node{
	int to,nxt;
}edge[mxn<<1];
void add(int u,int v){
	edge[++cnt]=(node){v,head[u]};
	head[u]=cnt;
}
void dfs1(int u,int f){
	fa[u]=f,dep[u]=dep[f]+1;
	siz[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==f)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp,dfn[u]=++cnt1;
	id[cnt1]=u;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==son[u]||v==fa[u])continue;
		dfs2(v,v);
	}
}
void pushup(int o){
	tree[o][0]=tree[o*2][0]&&tree[o*2+1][0];
	tree[o][1]=tree[o*2][1]&&tree[o*2+1][1];
}
void build(int o,int l,int r){
	if(l==r){
		tree[o][1]=a[id[l]];
		tree[o][0]=a[id[l]]^1;
		return;
	}
	int mid=(l+r)>>1;
	build(o*2,l,mid);
	build(o*2+1,mid+1,r);
	pushup(o);
}
void update(int o,int l,int r,int pos){
	if(l==r){
		tree[o][0]^=1;
		tree[o][1]^=1;
		return;	
	}
	int mid=(l+r)>>1;
	if(pos<=mid)update(o*2,l,mid,pos);
	else update(o*2+1,mid+1,r,pos);
	pushup(o);
}
bool query1(int o,int l,int r,int L,int R){
	if(L<=l&&r<=R)return tree[o][1];
	int mid=(l+r)>>1;bool ans=1;
	if(L<=mid)ans&=query1(o*2,l,mid,L,R);
	if(R>mid)ans&=query1(o*2+1,mid+1,r,L,R);
	return ans;
}
bool query0(int o,int l,int r,int L,int R){
	if(L<=l&&r<=R)return tree[o][0];
	int mid=(l+r)>>1;bool ans=1;
	if(L<=mid)ans&=query0(o*2,l,mid,L,R);
	if(R>mid)ans&=query0(o*2+1,mid+1,r,L,R);
	return ans;
}
bool query(int u,int v){
	bool ans1=1,ans0=1;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ans1&=query1(1,1,n,dfn[top[u]],dfn[u]);
		ans0&=query0(1,1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	ans1&=query1(1,1,n,dfn[u],dfn[v]);
	ans0&=query0(1,1,n,dfn[u],dfn[v]);
	return ans1||ans0;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%1d",&a[i]);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		u++,v++;
		add(u,v),add(v,u);
	}
	dfs1(1,0),dfs2(1,1);
	build(1,1,n);
	while(q--){
		int op,u,v;
		scanf("%d%d",&op,&u);
		u++;
		if(!op)update(1,1,n,dfn[u]);
		else{
			scanf("%d",&v);
			v++;
			if(query(u,v))puts("YES");
			else puts("NO");
		}
	}
	return 0;
} 
```

---

## 作者：da32s1da (赞：0)

**树剖**

0操作是单点修改，1操作是两点之间求和。

板子

另外注意点的编号
```
#include<cstdio>
const int N=3e5+50;
int n,m,x,y;
char s[N];
int to[N<<1],las[N<<1],fir[N],cnt;
inline void add_edge(int u,int v){
	to[++cnt]=v;las[cnt]=fir[u];fir[u]=cnt;
	to[++cnt]=u;las[cnt]=fir[v];fir[v]=cnt;
}
inline int swap(int &u,int &v){int G=u;u=v;v=G;}
int dep[N],son[N],siz[N],fa[N];
void dfs1(int u,int v){
	fa[u]=v;siz[u]=1;dep[u]=dep[v]+1;
	for(int i=fir[u];i;i=las[i])
	if(to[i]!=v){
		dfs1(to[i],u);siz[u]+=siz[to[i]];
		if(siz[son[u]]<siz[to[i]])son[u]=to[i];
	}
}
int bh[N],rnk[N],top[N],BH;
void dfs2(int u,int v){
	top[u]=v;bh[u]=++BH;rnk[BH]=u;
	if(son[u])dfs2(son[u],v);
	for(int i=fir[u];i;i=las[i])
	if(to[i]!=son[u]&&to[i]!=fa[u])
	dfs2(to[i],to[i]);
}
int tre[N<<3];
void mktree(int now,int ls,int rs){
	if(ls==rs){tre[now]=s[rnk[ls]]-'0';return;}
	int noww=now<<1,nrs=ls+rs>>1;
	mktree(noww,ls,nrs);
	mktree(noww|1,nrs+1,rs);
	tre[now]=tre[noww]+tre[noww|1];
}
void change(int now,int ls,int rs,int mb){
	if(ls>mb||rs<mb)return;
	if(ls==rs){tre[now]^=1;return;}
	int noww=now<<1,nrs=ls+rs>>1;
	change(noww,ls,nrs,mb);
	change(noww|1,nrs+1,rs,mb);
	tre[now]=tre[noww]+tre[noww|1];
}
int sum(int now,int ls,int rs,int zuo,int you){
	if(ls>you||rs<zuo)return 0;
	if(ls>=zuo&&rs<=you)return tre[now];
	int noww=now<<1,nrs=ls+rs>>1;
	return sum(noww,ls,nrs,zuo,you)+sum(noww|1,nrs+1,rs,zuo,you);
}
bool gans(int u,int v=0){
	scanf("%d",&v);++v;
	int ret=0,res=dep[u]+dep[v];
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ret+=sum(1,1,n,bh[top[u]],bh[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	ret+=sum(1,1,n,bh[u],bh[v]);
	res+=-dep[u]-dep[fa[u]];
	return ret==res||ret==0;
}
int main(){
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add_edge(x+1,y+1);
	}
	dfs1(1,0);
	dfs2(1,0);
	mktree(1,1,n);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&y,&x);++x;
		if(y)puts(gans(x)?"YES":"NO");
		else change(1,1,n,bh[x]);
	}
}
```

---

