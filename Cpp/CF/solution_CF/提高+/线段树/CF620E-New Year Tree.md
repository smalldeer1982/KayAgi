# New Year Tree

## 题目描述

The New Year holidays are over, but Resha doesn't want to throw away the New Year tree. He invited his best friends Kerim and Gural to help him to redecorate the New Year tree.

The New Year tree is an undirected tree with $ n $ vertices and root in the vertex $ 1 $ .

You should process the queries of the two types:

1. Change the colours of all vertices in the subtree of the vertex $ v $ to the colour $ c $ .
2. Find the number of different colours in the subtree of the vertex $ v $ .

## 样例 #1

### 输入

```
7 10
1 1 1 1 1 1 1
1 2
1 3
1 4
3 5
3 6
3 7
1 3 2
2 1
1 4 3
2 1
1 2 5
2 1
1 6 4
2 1
2 2
2 3
```

### 输出

```
2
3
4
5
1
2
```

## 样例 #2

### 输入

```
23 30
1 2 2 6 5 3 2 1 1 1 2 4 5 3 4 4 3 3 3 3 3 4 6
1 2
1 3
1 4
2 5
2 6
3 7
3 8
4 9
4 10
4 11
6 12
6 13
7 14
7 15
7 16
8 17
8 18
10 19
10 20
10 21
11 22
11 23
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4
1 12 1
1 13 1
1 14 1
1 15 1
1 16 1
1 17 1
1 18 1
1 19 1
1 20 1
1 21 1
1 22 1
1 23 1
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4
```

### 输出

```
6
1
3
3
2
1
2
3
5
5
1
2
2
1
1
1
2
3
```

# 题解

## 作者：xixike (赞：13)

本题要不难想到要用线段树或树状数组之类的数据结构，但是题目要求在树上操作，我们该如何处理呢？

首先我们要用到一个叫dfs序的概念。其实并不难，刚接触的同学不要被它吓到，它本质上就是一棵树的先序遍历，所谓先序遍历就是先遍历根，然后遍历左子节点，最后遍历右子节点。**我们需要把dfs序存在pos数组中，并把每个节点第一次遍历到的时间点和第二次遍历到的时间点存到in和out数组中，这样就成功地把一棵树转换为了线性结构。对一棵子树进行操作时，只需对这棵子树的根节点两次遍历到的时间戳中间的部分进行操作即可**。

求dfs序的代码
```cpp
void dfs(ll x,ll fa){
	tim++;
	in[x]=tim;
	pos[tim]=x;
	for(ll i=head[x];i;i=edge[i].next){
		ll y=edge[i].v;
		if(y==fa) continue;
		dfs(y,x);
	}
	out[x]=tim;
}

```
然后我们就可以用dfs序，也就是pos数组对线段树进行操作了，不过需要用到状态压缩，要把颜色压缩成二进制数到线段树中，所以要开long long。接下来基本上都是线段树区间修改，区间查询的模板了。**需要注意的是，查询出来的值是一个经过状压后的数，我们需要把它分解。**这里可以借鉴树状数组的思想，即每次减去一个lowbit（一棵树上有数值的节点的最低位,不会的话可以先去学习一下树状数组，这里不再过多赘述）再让ans++，因为状压后只有0和1，有值的话一定是1。ans就是最后的答案。

附代码
```cpp
#include<iostream>
#include<cstdio>
#define N 400010
#define ll long long

using namespace std;

struct node{                      //用前向星找dfs序
	ll v,next;
}edge[N<<2];
ll head[N],tot,tim;
ll in[N],out[N],pos[N];

ll a[N];
ll ans[N<<2],lazy[N<<2];          //线段树开4倍空间


//-----------------------找dfs序
void dfs(ll x,ll fa){
	tim++;
	in[x]=tim;
	pos[tim]=x;
	for(ll i=head[x];i;i=edge[i].next){
		ll y=edge[i].v;
		if(y==fa) continue;
		dfs(y,x);
	}
	out[x]=tim;
}

void add(ll x,ll y){
	tot++;
	edge[tot].v=y;
	edge[tot].next=head[x];
	head[x]=tot;
}

//-----------------------状压线段树各种操作
void pushup(ll rt){
	ans[rt]=ans[rt<<1]|ans[rt<<1|1];   //状压，所以是或运算
}

void pushdown(ll rt){
	if(lazy[rt]!=0){
		lazy[rt<<1]=lazy[rt];
		lazy[rt<<1|1]=lazy[rt];
		ans[rt<<1]=lazy[rt];
		ans[rt<<1|1]=lazy[rt];
		lazy[rt]=0;
	}
}

void build(ll l,ll r,ll rt){
	if(l==r){
		ans[rt]=1ll<<(a[pos[l]]);
		return;
	}
	ll mid=(l+r)>>1;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	pushup(rt);
}

void update(ll L,ll R,ll x,ll l,ll r,ll rt){
	if(L<=l&&r<=R){
		ans[rt]=1ll<<x;     //存的是二进制数，左移x位代表颜色，刚开始接触的话如果不懂多做题就能慢慢理解了
		lazy[rt]=1ll<<x;    //1ll是强制类型转换成long long的意思，一定要有，当时我就在这里卡了好久
		return; 
	}
	pushdown(rt);
	ll mid=(l+r)>>1;
	if(L<=mid) update(L,R,x,l,mid,rt<<1);
	if(R>mid) update(L,R,x,mid+1,r,rt<<1|1);
	pushup(rt);
}

ll query(ll L,ll R,ll l,ll r,ll rt){
	if(L<=l&&r<=R)
		return ans[rt];
	pushdown(rt);
	ll mid=(l+r)>>1;
	ll res=0;
	if(L<=mid) res|=query(L,R,l,mid,rt<<1);
	if(R>mid) res|=query(L,R,mid+1,r,rt<<1|1);
	return res;
}

//-----------------------利用树状数组思路分解状压后的数，并求出答案
ll lowbit(ll k){
	return k&(-k);
}

ll getsum(ll x){
	ll ans=0;
	for(ll i=x;i>0;i-=lowbit(i))
		ans++;
	return ans;
}

int main(){
	ll n,m,p,v,c;
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(ll i=1;i<n;i++){
		ll x,y; 
		scanf("%lld%lld",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	build(1,n,1);
	for(ll i=1;i<=m;i++){
		scanf("%lld",&p);
		if(p==1){
			scanf("%lld%lld",&v,&c);
			update(in[v],out[v],c,1,n,1);
		}else{
			scanf("%lld",&v);
			ll num=query(in[v],out[v],1,n,1);
			printf("%lld\n",getsum(num));
		}
	}
	return 0;
}
```


---

## 作者：luyan (赞：8)

知识储备：线段树、图的存储与遍历、状态压缩
题意翻译

你有一棵以1为根的有根树，有n个点，每个节点初始有一个颜色c[i]。

有两种操作：

1 v c 将以v为根的子树中所有点颜色更改为c

2 v 查询以v为根的子树中的节点有多少种不同的颜色
题目链接：https://www.luogu.org/problem/CF620E
首先我们讲一下dfs序在这道题里面的应用

定义：一棵树从根节点开始进行深度优先搜索，用一个时间戳记录下来每一个点被访问的时间，得到的序列就叫dfs序。

注意：以不同方式存树会有不同的dfs序，但是对于同一个邻接表搜出来的dfs序永远一样


![在这里插入图片描述](https://img-blog.csdnimg.cn/20190803212440813.PNG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1eWFuMDQwOA==,size_16,color_FFFFFF,t_70)

这棵树的dfs序（不唯一）就是：1 4 6 3 7 10 5 8 2 9
这样的话我们就可以把一个点的dfs序代表这个点，这样不论树的形状是怎样的，dfs序都可以把它转化成线性结构

我们通过dfs把这颗树的dfs序存储在pos数组中

同时，我们还要记录一个点的入点时间戳与出点时间戳。因为题目要求我们支持更改一整个子树，如果我们把它转化成线性结构就可以用线段树维护它而不用dfs了，但是线段树要有左右端点，而这个左右端点就是用in与out数组实现。

dfs代码：
我是用邻接表存图，tot为时间，pos记录当前时间访问到的结点。

```cpp
void dfs(int x,int fa){//用dfs序将树形结构转为线性结构 
	tot++;
	in[x]=tot;
	pos[tot]=x;
	for(int i=head[x];i+1;i=e[i].next){
		int k=e[i].to;
		if(k==fa)continue;
		dfs(k,x);
	}
	out[x]=tot;//其实我们out记录的是该子树中dfs序最大结点的dfs序，所以tot不加一 
	return;
} 
```
这样的话，我们就可以用pos数组建树了！

```
struct tree{
	long long sum;
	long long tag;//记录要修改为哪个颜色 
	int l,r;
}t[1600040];
```

我们把颜色状态压缩到一个long long中，然后要建立一颗与运算的线段树：
首先是上传、下传以及建树：

```cpp
void pushup(int rt){
	t[rt].sum=t[rt<<1].sum|t[rt<<1|1].sum;
	return;
}
void pushdown(int rt){
	if(t[rt].tag!=0){//或运算不像区间和，这里0是影响答案的 
		t[rt<<1].sum=t[rt].tag;
		t[rt<<1].tag=t[rt].tag;
		t[rt<<1|1].sum=t[rt].tag;
		t[rt<<1|1].tag=t[rt].tag;
		t[rt].tag=0;
	}	
	return;
}
void build(int rt,int l,int r){
	t[rt].l=l;
	t[rt].r=r;
	if(l==r){
		t[rt].sum=(long long)1<<(c[pos[l]]);//
		t[rt].tag=0;
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
	return;
}
```
然后，我们分别来处理两种操作

首先使修改操作：
将以x结点为根的子树的颜色修改为p：

```cpp
void modify(int rt,int l,int r,int p){//将dfs序从l到r这一区间的颜色改为p  注意状压 
	if(t[rt].l>=l&&t[rt].r<=r){
		t[rt].sum=(long long)1<<p;//
		t[rt].tag=(long long)1<<p;//
		return ;
	}
	int mid=(t[rt].l+t[rt].r)>>1;
	pushdown(rt);
	if(l<=mid)modify(rt<<1,l,r,p);
	if(r>mid)modify(rt<<1|1,l,r,p);
	pushup(rt);
	return;
}
```
还记得我一开始的dfs过程吗？我们每访问一个点就记录它的入点时间戳，然后遍历它每一个儿子，然后记录出点时间戳，这样的话一个点的入、出点时间戳之间就包含了它的所有孩子。（这有点像笛卡尔树中序遍历就是一段区间）。

所以l和r就分别是in[x]和out[x]

然后是查询操作：

```cpp
long long query(int rt,int l,int r){//查询dfs序从l到r的颜色个数 
	if(t[rt].l>=l&&t[rt].r<=r){
		return t[rt].sum;
	}
	pushdown(rt);
	int mid=(t[rt].l+t[rt].r)>>1;
	long long rec=0;
	if(l<=mid)rec|=query(rt<<1,l,r);
	if(r>mid)rec|=query(rt<<1|1,l,r);
	pushup(rt);
	return rec;
}
```
但要注意的是，我们返回的是一个状压之后的数字，所以我们还要分解它，这里有两种写法：
第一种比较直观，但有一些慢

```cpp
while(res) {
                s += res&1;
                res >>= 1;
            }
```
实际思想就是按位与记录答案

还有一种是用lowbit，没学过树状数组的话可以先去看一下树状数组。
返回某一个数二进制下第一个1所代表的值，**注意**：是值，不是位置

```cpp
long long lowbit(long long x){
	return x&(-x);
}
```

```
	for(long long j=num;j>0;j-=lowbit(j))ans++;
```
然后接结束了！

下附AC代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int read(){
	char s;
	int x=0,f=1;
	s=getchar();
	while(s<'0'||s>'9'){
		if(s=='-')f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9'){
		x*=10;
		x+=s-'0';
		s=getchar();
	}
	return x*f;
}
struct tree{
	long long sum;
	long long tag;//记录要修改为哪个颜色 
	int l,r;
}t[1600040];
int c[400040];
int tot=0;
int pos[400040];//时间戳所对应的点
int in[400040];//入点时间戳 
int out[400040];//出点时间戳 
struct edge{
	int to,next;
}e[800080];
int eid=0;
int head[400040];
void insert(int u,int v){
	eid++;
	e[eid].to=v;
	e[eid].next=head[u];
	head[u]=eid;
}
void dfs(int x,int fa){//用dfs序将树形结构转为线性结构 
	tot++;
	in[x]=tot;
	pos[tot]=x;
	for(int i=head[x];i+1;i=e[i].next){
		int k=e[i].to;
		if(k==fa)continue;
		dfs(k,x);
	}
	out[x]=tot;//其实我们out记录的是该子树中dfs序最大结点的dfs序，所以tot不加一 
	return;
} 
void pushup(int rt){
	t[rt].sum=t[rt<<1].sum|t[rt<<1|1].sum;
	return;
}
void pushdown(int rt){
	if(t[rt].tag!=0){//或运算不像区间和，这里0是影响答案的 
		t[rt<<1].sum=t[rt].tag;
		t[rt<<1].tag=t[rt].tag;
		t[rt<<1|1].sum=t[rt].tag;
		t[rt<<1|1].tag=t[rt].tag;
		t[rt].tag=0;
	}	
	return;
}
void build(int rt,int l,int r){
	t[rt].l=l;
	t[rt].r=r;
	if(l==r){
		t[rt].sum=(long long)1<<(c[pos[l]]);//
		t[rt].tag=0;
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
	return;
}
void modify(int rt,int l,int r,int p){//将dfs序从l到r这一区间的颜色改为p  注意状压 
	if(t[rt].l>=l&&t[rt].r<=r){
		t[rt].sum=(long long)1<<p;//
		t[rt].tag=(long long)1<<p;//
		return ;
	}
	int mid=(t[rt].l+t[rt].r)>>1;
	pushdown(rt);
	if(l<=mid)modify(rt<<1,l,r,p);
	if(r>mid)modify(rt<<1|1,l,r,p);
	pushup(rt);
	return;
}
long long query(int rt,int l,int r){//查询dfs序从l到r的颜色个数 
	if(t[rt].l>=l&&t[rt].r<=r){
		return t[rt].sum;
	}
	pushdown(rt);
	int mid=(t[rt].l+t[rt].r)>>1;
	long long rec=0;
	if(l<=mid)rec|=query(rt<<1,l,r);
	if(r>mid)rec|=query(rt<<1|1,l,r);
	pushup(rt);
	return rec;
}
int n,m;
long long lowbit(long long x){
	return x&(-x);
}
int main(){
	memset(head,-1,sizeof(head));
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		c[i]=read();
	}
	for(int i=1;i<n;i++){
		int x,y;
		x=read();
		y=read();
		insert(x,y);
		insert(y,x);
	}
	dfs(1,0);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int a;
		a=read();
		if(a==1){
			int x,y;
			x=read();
			y=read();
			modify(1,in[x],out[x],y);
			//cout<<query(1,in[x],in[x])<<endl;
		}
		else{
			int x;
			x=read();
			long long num=query(1,in[x],out[x]);
			int ans=0;
			//cout<<num<<endl;
			for(long long j=num;j>0;j-=lowbit(j))ans++;
			cout<<ans<<endl;
		}
	}
	return 0;
}
```


---

## 作者：roger_yrj (赞：7)

# 珂学的力量是没有极限的！

一眼珂学题，用珂朵莉树完全是裸题，但需要加个优化：

当某次询问已经找到了 $60$ 种颜色，直接停止。

这应该是全谷第一个用珂朵莉树过掉这道题的。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define sit set<node>::iterator

struct node{
	int l,r;
	mutable int v;
	node(int l,int r=0,int v=0):l(l),r(r),v(v){}
};

bool operator<(node x,node y){
	return x.l<y.l;
}

const int N=4e5+10;
int n,m,a[N],b[N],L[N],R[N],id[N],tim,vis[65];
set<node>s;

sit split(int x){
	sit it=s.lower_bound(node(x));
	if(it!=s.end()&&it->l==x)return it;
	--it;
	if(it->r<x)return s.end();
	int l=it->l,r=it->r,v=it->v;
	s.erase(it);
	s.insert(node(l,x-1,v));
	return s.insert(node(x,r,v)).first;
}

void assign(int l,int r,int v){
	sit itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(node(l,r,v));
}

int query(int l,int r){
	sit itr=split(r+1),itl=split(l);
	memset(vis,0,sizeof(vis));
	int ret=0;
	for(sit it=itl;it!=itr;++it){
		if(!vis[it->v]){
			ret++;
			vis[it->v]=1;
			if(ret==60)return ret;
		}
	}
	return ret;
}

int fst[N],nxt[2*N],to[2*N],ecnt;

void adde(int u,int v){
	ecnt++;
	to[ecnt]=v;
	nxt[ecnt]=fst[u];
	fst[u]=ecnt;
}

void dfs(int u,int fa){
	L[u]=++tim;
	id[tim]=u;
	for(int i=fst[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		dfs(v,u);
	}
	R[u]=tim;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		adde(u,v);adde(v,u);
	} 
	dfs(1,0);
	for(int i=1;i<=n;i++)b[L[i]]=a[i];
	for(int i=1,lst;i<=n+1;i++){
		if(b[i]!=b[i-1]){
			if(i>1)s.insert(node(lst,i-1,b[i-1]));
			lst=i;	
		}
	}
	for(int i=1,op,x,y;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&x,&y);
			assign(L[x],R[x],y);
		}else{
			scanf("%d",&x);
			printf("%d\n",query(L[x],R[x]));
		}
	}
	return 0;
}
```

---

## 作者：MikeDuke (赞：3)

 ~~因为红色的MikeDuke变成了橙色的MikeDuke~~
 
 ~~所以我来水题解了。。~~
 
##  珂学的力量是有极限的！

这题一眼珂学题，然而被毒瘤出题人卡了。。

在放出正解之前，我提供一份丑陋不堪，常数巨大的珂学代码供各位神犇参考

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define M 1000005
 
 
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { (x *= 10) += ch - '0'; ch = getchar(); }
	return x * f;
}
 
int n, cnt, m, opt, t1, t2;
 
int col[M], dfn[M], siz[M], ver[M];
 
vector<int> G[M];
 
inline void add_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}
 
struct Node
{
	int l,r;
	mutable int v;
	Node(int L, int R=-1, int V=0):l(L), r(R), v(V) {}
	bool operator<(const Node& x) const
	{
		return l < x.l;
	}
};
 
set<Node> s;
 
typedef set<Node>::iterator IT;
 
inline IT split(int pos)
{
	IT it = --s.upper_bound(Node(pos));
	if (it->l == pos) return it;
	int ls = it->l, rs = it->r, val = it->v;
	s.erase(it); s.insert(Node(ls, pos - 1, val));
	return s.insert(Node(pos, rs, val)).first;
}
 
inline void assign(int l, int r, int v)
{
	IT itr = split(r + 1), itl = split(l);
	s.erase(itl, itr);
	s.insert(Node(l, r, v));
}
 
void dfs(int u, int c_fa)
{
	siz[u] = 1;
	dfn[u] = ++cnt;
	ver[cnt] = u;
	int sz = G[u].size();
	for (int i = 0; i < sz; i++)
	{
		int v = G[u][i];
		if (v == c_fa) continue;
		dfs(v, u);
		siz[u] += siz[v];
	}
}
 
inline int query(int u)
{
	IT itr = split(dfn[u] + siz[u]), itl = split(dfn[u]);
	int cnt[65] = {}, ans = 0;
	for (IT it = itl; it != itr; it++)
	{
		if (!cnt[it->v]) ans++;
		cnt[it->v]++;
	}
	return ans;
}
 
int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
	{
		col[i] = read();
	}
	
	for (int i = 1; i < n; i++)
	{
		add_edge(read(), read());
	}
	
 	dfs(1, 0);
 
 	for (int i = 1; i <= n; i++)
	{
		int p = ver[i];
		s.insert( Node(dfn[p], dfn[p], col[p]) );
	}
	
	for (int i = 1; i <= m; i++)
	{
		opt = read(), t1 = read();
		if (opt == 1)
		{
			t2 = read();
			assign(dfn[t1], dfn[t1] + siz[t1] - 1, t2);
		}
		if (opt == 2)
		{
			printf("%d\n", query(t1));
		}
	}
	
	return 0;
}
```
time limit exeeded on test 67..

~~如果能开O2我将绝杀，可惜开不得~~


------------


# 那我们来看正解

我在读题的时候偶然发现了
```
1 <= c[i] <= 60
```
我又恰巧想到了
```
1 << 60 ≈ long long上限
```
那么这说明可以使用**状态压缩**


------------


想必做这道题的神犇们都熟练掌握**树链剖分**

那么我们可以轻易知道对**以一个点为根的子树**进行奇♂怪的操作可以转化为在**dfn序**上，对一段**连续区间**进行奇♂怪的操作。

具体来说，对**以$u$为根的子树**进行操作等价在**dfn序**上对闭区间 $(dfn[u], dfn[u] + siz[u] - 1)$进行操作

dfn序列可以用**线段树**维护


------------
假设$dat$用来存储**一段区间上的颜色信息**

那么可以使用如下的方法

#### $dat$的第$i$位是$1$，则$dat$所表示的区间就有$i$这种颜色


------------
### 如何$pushup$

想必各位神犇熟练掌握位运算的各种技巧

那么就很容易得到以下式子

dat[pos] = dat[pos<<1] **|** dat[pos<<1|1]

左右子区间任何一个有了某种颜色，那么母区间一定也有这种颜色，所以使用位运算中的**或**


------------
### 如何$pushdown$

$mark[pos]$表示$pos$代表的区间的标记

那么

$mark[pos<<1] = mark[pos<<1|1] = mark[pos]$

$dat[pos<<1] = dat[pos<<1|1] = mark[pos]$

也很容易理解


------------
### 最后，完整代码
```cpp
#include <bits/stdc++.h>

using namespace std;

#define M 400005

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { (x *= 10) += ch - '0'; ch = getchar(); }
	return x * f;
}

int n, m, cnt, opt, t1, t2;
int l_[M<<2], r_[M<<2], siz[M], ver[M], dfn[M], col[M];
long long mark[M<<2], dat[M<<2];

vector<int> G[M];

inline void add_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

inline int count(long long val) // 一个状态中有多少个1，即不同的颜色数
{
	int res = 0;
	while (val)
	{
		if (val & 1) res++;
		val >>= 1;
	}
	return res;
}

inline void push_down(int pos)
{
	if (mark[pos] != 0)
	{
		mark[pos<<1] = mark[pos<<1|1] = mark[pos];
		dat[pos<<1] = dat[pos<<1|1] = mark[pos];
		mark[pos] = 0;
	}
}

void build(int pos, int l, int r)
{
	l_[pos] = l, r_[pos] = r;
	if (l == r)
	{
		dat[pos] = 1ll << col[ver[l]]; // 直接将状态中的第col位变成1，表示有这种颜色
		return;
	}
	int mid = (l + r) >> 1;
	build(pos<<1, l, mid);
	build(pos<<1|1, mid + 1, r);
	dat[pos] = dat[pos<<1] | dat[pos<<1|1];
}

void upd(int pos, int l, int r, int c)
{
	if (l_[pos] >= l && r_[pos] <= r)
	{
		mark[pos] = dat[pos] = 1ll << c;
		return;
	}
	push_down(pos);
	int mid = (l_[pos] + r_[pos]) >> 1;
	if (l <= mid) upd(pos<<1, l, r, c);
	if (r > mid) upd(pos<<1|1, l, r, c);
	dat[pos] = dat[pos<<1] | dat[pos<<1|1];
}

long long query(int pos, int l, int r)
{
	if (l_[pos] >= l && r_[pos] <= r)
	{
		return dat[pos];
	}
	long long ans = 0;
	push_down(pos);
	int mid = (l_[pos] + r_[pos]) >> 1;
	if (l <= mid) ans |= query(pos<<1, l, r);
	if (r > mid) ans |= query(pos<<1|1, l, r);
	dat[pos] = dat[pos<<1] | dat[pos<<1|1];
	return ans; // query返回的是压缩后的状态
}

void dfs(int u, int c_fa)
{
	siz[u] = 1, dfn[u] = ++cnt, ver[cnt] = u;
	int sz = G[u].size();
	for (int i = 0; i < sz; i++)
	{
		int v = G[u][i];
		if (v == c_fa) continue;
		dfs(v, u);
		siz[u] += siz[v];
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		col[i] = read();
    for (int i = 1; i < n; i++)
		add_edge(read(), read());

	dfs(1, 0);
	
	build(1, 1, n);

	for (int i = 1; i <= m; i++)
	{
		opt = read(), t1 = read();
		if (opt == 1)
		{
			t2 = read();
			upd(1, dfn[t1], dfn[t1] + siz[t1] - 1, t2);
		}
		else
		{
			printf("%d\n", count(query(1, dfn[t1], dfn[t1] + siz[t1] - 1)));
		}
	}
}
```


---

## 作者：傅思维666 (赞：3)


## 题解：

来水一发其他大佬都没提到过的题解：

#### bitset+半树链剖分

知识铺垫：

对$bitset$容器不太了解的小伙伴请戳这里：

[详解bitset容器](https://www.cnblogs.com/fusiwei/p/11720118.html)

对树链剖分不太了解的小伙伴请戳这里：

[树链剖分详解](https://www.cnblogs.com/fusiwei/p/11519470.html)

~~2019.10.29模拟赛T3 50分场~~

一开始觉得用树链剖分可做，想得很简单，后来代码实现的时候碰到一堆问题。冥思苦想很长时间之后，用搜索统计拿到了50分：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=8*1e5+10;
int n,m;
int a[maxn];
int tot,head[maxn],nxt[maxn<<1],to[maxn<<1],fa[maxn];
bool vis[70];
void add(int x,int y)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void update(int x,int k)
{
    a[x]=k;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(y==fa[x])
            continue;
        update(y,k);
    }
}
int query(int x)
{
    int ret=0;
    if(!vis[a[x]])
    {
        vis[a[x]]=1;
        ret++;
    }
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(y==fa[x])
            continue;
        ret+=query(y);
    }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
        fa[v]=u;
    }
    for(int i=1;i<=m;i++)
    {
        int opt;
        scanf("%d",&opt);
        int v,c;
        if(opt==1)
        {
            scanf("%d%d",&v,&c);
            update(v,c);
        }
        else
        {
            scanf("%d",&v);
            memset(vis,0,sizeof(vis));
            printf("%d\n",query(v));
        }
    }
    return 0;
}
```

后来看到正解是用状态压缩加DFS序转线段树过的。

我没有改变正解的思路，只是在实现方式上变了一下花样。

大家是用long long进行状压的。我使用了bitset容器。大家是用DFS记录了DFS序的两个时间戳进行查询/修改的。我使用的是树链剖分预处理操作中的size数组进行实现的。

思路：输入数据建立原始树，然后在进行两次DFS（一次当然可以，但因为我直接用的树链剖分的板子，就懒得改了）跑出size数组和id、idx数组，这两个数组构建了一个完整、可复的映射关系。然后以此建立线段树。其中**bitset容器的每位表示这种颜色有还是没有**，所以最后只需要统计bitset容器中1的个数就可以。省去了用lowbit运算进行数1的操作。

对于线段树的更新，我们采用了位运算中的**或运算**，根据bitset容器的性质，或运算是可以应用于bitset容器上的，就成功地把线段树的两个状态合并到一起。

对于线段树的查询/修改区间，很明显，它在区间上的范围就是$[id[x],id[x]+size[x]-1]$，如有不懂请参照上面的树链剖分博客补习。

完整AC代码：

```cpp
#include<cstdio>
#include<bitset>
#define lson pos<<1
#define rson pos<<1|1
using namespace std;
const int maxn=4*1e5+10;
char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
    int x=0;
    char ch=nc();
    while(ch>47)
        x=(((x<<2)+x)<<1)+ch-48,ch=nc();
    return x;
}
int n,m,a[maxn],cnt;
int tot,head[maxn],nxt[maxn<<1],to[maxn<<1];
int fa[maxn],id[maxn],idx[maxn],size[maxn];
int lazy[maxn<<2];
bitset<64> tree[maxn<<2];
void add(int x,int y)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void dfs1(int x,int f)
{
    fa[x]=f;
    size[x]=1;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(y==f)
            continue;
        dfs1(y,x);
        size[x]+=size[y];
    }
}
void dfs2(int x)
{
    id[x]=++cnt;
    idx[cnt]=x;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(y==fa[x])
            continue;
        dfs2(y);
    }
}
void build(int pos,int l,int r)
{
    int mid=(l+r)>>1;
    if(l==r)
    {
        tree[pos].set(a[idx[l]]);
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    tree[pos]=tree[lson]|tree[rson];
}
void mark(int pos,int l,int r,int k)
{
    lazy[pos]=k;
    tree[pos].reset();
    tree[pos].set(k);
}
void pushdown(int pos,int l,int r)
{
    int mid=(l+r)>>1; 
    if(!lazy[pos]) 
        return;
    mark(lson,l,mid,lazy[pos]);
    mark(rson,mid+1,r,lazy[pos]);
    lazy[pos]=0;
}
void update(int pos,int l,int r,int x,int y,int k)
{
    int mid=(l+r)>>1;
    if(x<=l && r<=y)
    {
        mark(pos,l,r,k);
        return;
    }
    pushdown(pos,l,r);
    if(x<=mid)
        update(lson,l,mid,x,y,k);
    if(y>mid)
        update(rson,mid+1,r,x,y,k);
    tree[pos]=tree[lson]|tree[rson];
}
bitset<64> query(int pos,int l,int r,int x,int y)
{
    int mid=(l+r)>>1;
    bitset<64> ret;
    if(x<=l && r<=y)
        return tree[pos];
    pushdown(pos,l,r);
    if(x<=mid)
        ret|=query(lson,l,mid,x,y);
    if(y>mid)
        ret|=query(rson,mid+1,r,x,y);
    return ret;
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    for(int i=1;i<n;i++)
    {
        int u,v;
        u=read(),v=read();
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    dfs2(1);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int opt,v,c;
        opt=read();
        if(opt==1)
        {
            v=read();c=read();
            update(1,1,n,id[v],id[v]+size[v]-1,c);
        }
        else 
        {
            v=read();
            printf("%d\n",query(1,1,n,id[v],id[v]+size[v]-1).count());
        }
    }
    return 0;
}
```



---

## 作者：Fuko_Ibuki (赞：3)

## **@Styx 首先我要更正一点,这个人才是大佬,我很菜.**  
具体的做法楼下都说过了,但我还有几点要说的.  
`首先状态压缩的时候线段树里一定要写1ll<<x,不能写1<<x,否则会爆int.`  
`不然你会WA在第13个点.这个错误我已经不止犯过一次了,而且每次都不知改悔.`  
`还有在求一个二进制数中1的个数的时候不能用c++自带的__builtin_popcount函数,要自己写一个.这个函数只对int有效.`  
最后用dfs序加上线段树就可以过了.
```cpp
#include<bits/stdc++.h> //Ithea Myse Valgulious
namespace chtholly{
typedef long long ll;
#define re0 register int
#define rec register char
#define rel register ll
#define gc getchar
#define pc putchar
#define p32 pc(' ')
#define pl puts("")
/*By Citrus*/
inline int read(){
  re0 x=0,f=1;rec c=gc();
  for (;!isdigit(c);c=gc()) f^=c=='-';
  for (;isdigit(c);c=gc()) x=(x<<3)+(x<<1)+(c^'0');
  return f?x:-x;
  }
inline void read(rel &x){
  x=0;re0 f=1;rec c=gc();
  for (;!isdigit(c);c=gc()) f^=c=='-';
  for (;isdigit(c);c=gc()) x=(x<<3)+(x<<1)+(c^'0');
  x=f?x:-x;
  }
template <typename mitsuha>
inline int write(mitsuha x){
  if (!x) return pc(48);
  if (x<0) x=-x,pc('-');
  re0 bit[20],i,p=0;
  for (;x;x/=10) bit[++p]=x%10;
  for (i=p;i;--i) pc(bit[i]+48);
  }
inline char fuhao(){
  rec c=gc();
  for (;isspace(c);c=gc());
  return c;
  }
}using namespace chtholly;
using namespace std;
const int yuzu=4e5;
typedef int fuko[yuzu|10];
vector<int> lj[yuzu|10];
int n,m,cnt;
fuko dfn,edf,ord,a;

void dfs(int u,int fa){
dfn[u]=++cnt,ord[cnt]=u;
for (int v:lj[u]) if (v^fa) dfs(v,u);
edf[u]=cnt;
}

typedef ll karen[yuzu<<2|13];
struct segtree{
#define le rt<<1
#define ri le|1
#define ls le,l,mid
#define rs ri,mid+1,r
karen val,lazy;
void build(int rt=1,int l=1,int r=n){
  lazy[rt]=-1;
  if (l==r) val[rt]=1ll<<a[ord[l]];
  else{
    int mid=l+r>>1;
    build(ls),build(rs);
    val[rt]=val[le]|val[ri];
    }
  }
void push_down(int rt){
  if (~lazy[rt]){
    lazy[le]=lazy[ri]=lazy[rt];
    val[le]=val[ri]=1ll<<lazy[rt];
    lazy[rt]=-1;
    }
  }
void update(int ql,int qr,int v,int rt=1,int l=1,int r=n){
  if (ql>r||qr<l) return;
  if (ql<=l&&qr>=r){
    val[rt]=1ll<<v-1;
    lazy[rt]=v-1;
    }else{
    int mid=l+r>>1;
    push_down(rt);
    update(ql,qr,v,ls),update(ql,qr,v,rs);
    val[rt]=val[le]|val[ri];
    }
  }
ll query(int ql,int qr,int rt=1,int l=1,int r=n){
  if (ql>r||qr<l) return 0;
  if (ql<=l&&qr>=r) return val[rt];
  int mid=l+r>>1;
  push_down(rt);
  return query(ql,qr,ls)|query(ql,qr,rs);
  }
}my_;

#define all(u) dfn[u],edf[u]
int _bp(ll x){//看得出吧,__builtin_popcount的简称.
int ans=0;
for (;x;x&=x-1) ++ans;
return ans;
}

int main(){
re0 i;
n=read(),m=read();
for (i=1;i<=n;++i) a[i]=read()-1;
for (i=1;i<n;++i){
  int u=read(),v=read();
  lj[u].push_back(v);
  lj[v].push_back(u);
  }
dfs(1,0),my_.build();
for (;m--;){
  int op=read(),u=read();
  if (op==1){ 
    my_.update(all(u),read());
    }
  else{
    write(_bp(my_.query(all(u)))),pl;
    }
  }
}
```

---

## 作者：Styx (赞：2)

## **@Fuko_Ibuki 大佬说此题非常水，然后我就来做了一下**

**这是一道非常dark的线段树，我们看到这道题的颜色最多只有60种，所以理所应当的想到突破口就是颜色，60的范围可以考虑状压，其实我们在乎的只是有或者没有该颜色，所以我们可以用或运算来合并两个块，这自然是线段树的思路，因为只有修改子树或者查询子树的操作，所以直接dfs序就可以啦~对dfs序维护一个线段树，支持区间修改区间或，统计区间或之后得到的数在二进制下1的个数，这即为答案**

**代码如下**

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson root<<1
#define rson root<<1|1
using namespace std;

struct node
{
	int l,r;
	long long sum,lazy;
} tr[1600010];

vector<int> g[400010];
int dfsn[400010],c[400010],w[400010],size[400010],tot;

int get_bit(long long x)
{
	int ans=0;
	while(x)
	{
		if(x&1)
		{
			ans++;
		}
		x>>=1;
	}
	return ans;
}

void push_up(int root)
{
	tr[root].sum=tr[lson].sum|tr[rson].sum;
}

void push_down(int root)
{
	tr[lson].sum=tr[root].lazy;
	tr[rson].sum=tr[root].lazy;
	tr[lson].lazy=tr[root].lazy;
	tr[rson].lazy=tr[root].lazy;
	tr[root].lazy=-1;
}

void build(int root,int l,int r)
{
	if(l==r)
	{
		tr[root].l=l;
		tr[root].r=r;
		tr[root].lazy=-1;
		tr[root].sum=1ll<<c[l];
		return ;
	}
	tr[root].l=l;
	tr[root].r=r;
	tr[root].lazy=-1;
	int mid=(l+r)>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
	push_up(root);
}

void update(int root,int l,int r,int val)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		tr[root].sum=1ll<<val;
		tr[root].lazy=1ll<<val;
		return ;
	}
	if(~tr[root].lazy)
	{
		push_down(root);
	}
	int mid=(tr[root].l+tr[root].r)>>1;
	if(l>mid)
	{
		update(rson,l,r,val);
	}
	else
	{
		if(r<=mid)
		{
			update(lson,l,r,val);
		}
		else
		{
			update(lson,l,mid,val);
			update(rson,mid+1,r,val);
		}
	}
	push_up(root);
}

long long query(int root,int l,int r)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		return tr[root].sum;
	}
	if(~tr[root].lazy)
	{
		push_down(root);
	}
	int mid=(tr[root].l+tr[root].r)>>1;
	if(l>mid)
	{
		return query(rson,l,r);
	}
	else
	{
		if(r<=mid)
		{
			return query(lson,l,r);
		}
		else
		{
			return query(lson,l,mid)|query(rson,mid+1,r);
		}
	}
}

void dfs(int now,int f)
{
	dfsn[now]=++tot;
	size[now]=1;
	c[tot]=w[now];
	for(int i=0;i<g[now].size();i++)
	{
		if(g[now][i]==f)
		{
			continue;
		}
		dfs(g[now][i],now);
		size[now]+=size[g[now][i]];
	}
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&w[i]);
	}
	for(int i=1;i<n;i++)
	{
		int from,to;
		scanf("%d%d",&from,&to);
		g[from].push_back(to);
		g[to].push_back(from);
	}
	
	dfs(1,0);
	build(1,1,n);
	
	for(int i=1;i<=m;i++)
	{
		int kd;
		scanf("%d",&kd);
		if(kd==1)
		{
			int v,val;
			scanf("%d%d",&v,&val);
			update(1,dfsn[v],dfsn[v]+size[v]-1,val);
		}
		if(kd==2)
		{
			int v;
			scanf("%d",&v);
			printf("%d\n",get_bit(query(1,dfsn[v],dfsn[v]+size[v]-1)));
		}
	}
}
```


---

## 作者：Zxsoul (赞：0)

# 位运算.dfs序.线段树
# 题面
- 给定一个树，树上有颜色，修改子树，求子树中颜色的数量
# Solution
- #### 子树修改，子树求和，dfs序的知识（类似区间修改区间求和）
- #### 考虑到颜色的个数问题，利用位运算进行表示。
- #### 最后答案用二进制表示，$\ 1\ $表示有该种颜色，$\ 0\ $表示没有，
- #### 因此还需考虑答案$\ 1\ $的数量。
- #### dfs序问题自然用到线段树进行维护。

## 具体介绍一下位运算，和一些小错误
- #### 方案总数不是两个节点维护的方案数的简单相加，而是“|”（或）
- #### 答案维护的是颜色的个数，但不是具体数值
- #### 关于答案$\ 1\ $的个数,可以利用快速幂
- #### 也可利用$\ lowbit\ $,作用是得到最后$\ 1\ $的位置上表示的数。
- #### 建树的时候特别记住需要$\ long \ long \ $的地方
![](https://cdn.luogu.com.cn/upload/image_hosting/52rrh7w8.png)

### [更加详细的内容](https://www.cnblogs.com/yrjns/p/11246163.html)
---
# Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define clr(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int manx=1e6+10;
const int mamx = 1e7 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
inline int read() {
  char c = getchar(); int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
struct nodee{
	int l,r;
	ll sum;
	ll add;
}e[manx<<2+2];
int clr[manx<<1];
struct node{
    int u;
    int v;
    int nxt;
    int w;
}ee[manx];
int head[manx],js,l[manx],r[manx],cnt,n,m,dfn[manx];
int add(int u,int v){
    ee[++cnt].u = u;
    ee[cnt].nxt = head[u];
    ee[cnt].v = v;
    //e[cnt].w = w;
    head[u] = cnt;
}
inline void init(){
    cnt=js=0;
    clr(head,-1);
}
//大法师 
void dfs(int u, int pre){ 
    js++;
    l[u] = js;
    dfn[js] = u;    
    for(int i = head[u];~i;i = ee[i].nxt){
        int v = ee[i].v;
        if( v == pre ) continue;
        dfs(v,u);
    }
    r[u] = js; //我们可以只记录他的入段，尾端那个不必重复 
	return ; 
}
//线段树 
void uploat(int s){//上传 
	e[s].sum = 0;
	if(e[s<<1].l) e[s].sum |=e[s<<1].sum ;
	if(e[s<<1|1].l ) e[s].sum |=e[s<<1|1].sum ;
}
void downloat(int i){
	if(e[i].add !=0){
		ll s = e[i].add ;//不要用int 用ll，作者就在这卡了一天 
		e[i<<1].sum = s;
		e[i<<1].add = s;
		e[i<<1|1].add = s;	
		e[i<<1|1].sum = s;
	 e[i].add = 0; 
	}
}
void build_up (int rt,int l,int r){
	e[rt].l = l;e[rt].r = r;
	if(l == r){
		e[rt].sum = (ll)1<<(clr[dfn[l]]);
		e[rt].add = 0;
		return;
	}
	int mid = (l+r) >> 1;
	build_up(rt<<1,l,mid);
	build_up(rt<<1|1,mid+1,r);
	e[rt].sum = e[rt<<1].sum | e[rt<<1|1].sum;
}
void updata(int i,int l,int r,int add){
	if(e[i].l >= l && e[i].r <= r)
	{
		e[i].sum = (ll)1<<add;
		e[i].add = (ll)1<<add;
		return;
	}
	int mid = (e[i].l  + e[i].r ) >> 1;
	downloat(i);
	if(mid >= r)updata(i<<1,l,r,add);
	else if(mid <l)updata(i<<1|1,l,r,add);
	else updata(i<<1,l,mid,add),updata(i<<1|1,mid+1,r,add);
	uploat(i);
 }
ll query(int i,int l,int r)
{
   if(e[i].l >= l && e[i].r <= r){
   	   return e[i].sum ;
   }
   downloat(i);
   int mid = (e[i].l +e[i].r ) >> 1;
	if(mid >= r)  
		return  query(i<<1,l,r);
	else 
		if(mid<l)
		return  query(i<<1|1,l,r);//熟悉的操作 
		return  query(i<<1,l,mid)|query(i<<1|1,mid+1,r);
}
ll lowbit(ll x){
	return x&-x;//lowbit函数 
}
int  ans;
int main(){
    n = read();
    m = read();
	init ();
    for(int i = 1;i <= n;i ++)
    	clr[i] = read();
    for(int i = 1;i <= n - 1;i ++)
    {
    	int x = read(),y = read();
    	add(x,y);add(y,x);
	} 
	dfs(1,0);
	build_up(1,1,n);//建树 
	for(int i = 1;i <= m; i++)
	{
		int x = read();
		int y;
		int z;
		if(x == 1){
			y = read();z = read();
		  updata(1,l[y],r[y],z);	
		}
		else{
			ans = 0;y = read();
			ll diet = query(1,l[y],r[y]);
			while(diet>0){
				diet-=lowbit(diet);
				ans++;//判断1的个数 
			}
			cout<<ans<<endl;//华丽收场 
		}
	}
	return 0;
}
```
---

# 感谢观看~~


---

## 作者：_CloudySky_ (赞：0)

#### 线段树+dfs序+状态压缩搞定这道题
我们把每种颜色k设为2^k，先dfs一遍把树变成区间，同时维护子树信息。（我用的是pair，当然也可以用两个数组）

同时，这道题的代码~~比较~~长，要注意细节呦。（比如说要开 long long ）

具体推导过程楼下已经写得很详细了，我就是来上份详细注释、可读性较高的代码。（那里偷来的自信）
```cpp
#include<iostream>
#include<cstdio>
#define int long long
typedef unsigned long long ull;
const int Maxn=400010;
using namespace std;

struct edge{
	int v,nxt;
}e[Maxn<<2];int head[Maxn],cnt;//用链式前向星存边

void adg(int u,int v){//加边操作
	e[++cnt].v=v,e[cnt].nxt=head[u],head[u]=cnt;
}

int pos[Maxn],t;//pos用来存放dfs序
pair<int,int>tim[Maxn];//用来维护子树信息 tim[i].second代表这棵子树的最后一个元素

void dfs(int x,int f){
	pos[++t]=x;//存储dfs序
	tim[x].first=t;//这棵子树的根
	for(int i=head[x];i;i=e[i].nxt){//遍历这个节点的边
		int tmp=e[i].v;//存放下个节点
		if(tmp==f)continue;//不能往回走
		dfs(tmp,x);
	}
	tim[x].second=t;//这棵子树的最后一个元素
}

#define ls p<<1//偷个懒，事先设定好
#define rs p<<1|1//和p*2+1一样
ull c[Maxn];//原序列

struct Stree{
	int l,r;ull dat,chg;
	#define l(x) St[x].l//同样，方便写代码，也方便理解（从哪里偷来的自信）
	#define r(x) St[x].r
	#define d(x) St[x].dat
	#define c(x) St[x].chg
}St[Maxn<<2];//因为最后一层有空节点，所以要开四倍
//进入最可爱的线段树部分
void build(int p,int l,int r){//建树
	l(p)=l,r(p)=r;//确定子树范围
	if(l==r){d(p)=1ll*c[pos[l]];return;}//如果区间长度为一，代表到了最底层，返回
	int mid=(l+r)>>1;
	build(ls,l,mid);//建立左子树
	build(rs,mid+1,r);//建立右子树
	d(p)=d(ls)|d(rs);//上传信息，由于要统计颜色个数，所以用不进位加法（或|），代表有这种颜色
}

void spread(int p){//下传标记，注意是直接修改，不是增加。
	if(c(p)){//如果有标记
		d(ls)=c(p),d(rs)=c(p);//直接修改子树值
		c(ls)=c(p),c(rs)=c(p);//把标记下传给字数
		c(p)=0ll;//取消标记
	}
}

void change(int p,int l,int r,int d){//区间修改操作
	if(l(p)>=l&&r(p)<=r){
		d(p)=d;c(p)=d;return;
	}//如果覆盖区间，直接打标记，降低复杂度
	spread(p);//否则先下传标记
	int mid=(l(p)+r(p))>>1;
	if(l<=mid)change(ls,l,r,d);//如果左子树有重叠，修改左子树
	if(r>mid) change(rs,l,r,d);//同理可证
	d(p)=d(ls)|d(rs);//上传信息，线段树每部操作都要顺便上传信息
}

ull ask(int p,int l,int r){//询问操作
	if(l(p)>=l&&r(p)<=r){
		return d(p);
	}//如果完全覆盖，就直接返回
	spread(p);//否则先下传标记
	int mid=(l(p)+r(p))>>1;
	ull val=0;//一开始没有任何颜色
	if(l<=mid)val|=ask(ls,l,r);//如果左子树有重叠，统计左子树
	if(r>mid) val|=ask(rs,l,r);//如果右子树有重叠，统计右子树
	d(p)=d(ls)|d(rs);//顺便上传信息
	return val;//返回颜色
}

signed main(){
	int n,m;
	scanf("%lld%lld",&n,&m);
	
	for(int i=1,tmp;i<=n;i++){
		scanf("%lld",&tmp);c[i]=(1ll<<tmp);
	}
	
	int x,y;
	for(int j=1;j<=n-1;j++){
		scanf("%lld%lld",&x,&y);
		adg(x,y),adg(y,x);
	}
	
	dfs(1,0);build(1,1,n);
	
	#define lowbit(x) x&-x
	int t,v,l,r;ull ch;
	for(int k=1,tmp;k<=m;k++){
		scanf("%lld",&t);
		if(t==2){
			scanf("%lld",&v);
			l=tim[v].first,r=tim[v].second;
			ull temp=ask(1,l,r);int ans=0;
			for(;temp;temp-=lowbit(temp))ans++;//统计答案，lowbit是最后一位唯一的数位
			printf("%lld\n",ans);
		}else{
			scanf("%lld%lld",&v,&tmp);
			l=tim[v].first,r=tim[v].second,ch=(1ll<<tmp);
			change(1,l,r,ch);
		}
	}
	return 0;
}

```


---

## 作者：HomuraCat (赞：0)

蛮好玩的一道题

首先dfs序变成序列操作就不说了

考虑到颜色数比较少，我们可以将颜色数状压，维护一个$sum$表示颜色集合，上传的时候或一下就好了

代码：

```cpp
#include<bits/stdc++.h>
#define fo(i, a, b) for (int i = (a); i <= (b); ++i)
#define fd(i, a, b) for (int i = (a); i >= (b); --i)
#define edge(i, u) for (int i = head[u], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
#define N 400005
#define pb push_back
#define F first
#define S second
#define ll long long
#define inf 1000000007
#define mp std::make_pair
#define lowbit(x) (x & -x)
#define ls (k << 1)
#define rs (k << 1 | 1)
int n, m, a[N], x, y, L[N], R[N], tim, ti[N], val, opt, tot;
struct edge{
    int nxt, v;
}e[N << 1];
int head[N];
struct node{
    ll sum;
    bool tag;
}t[N << 2];
inline void addedge (int u, int v)
{
    e[++tot] = (edge) {head[u], v};
    head[u] = tot;
}
inline int count (ll x)
{
    int ret = 0;
    while (x) x -= lowbit(x), ++ret;
    return ret;
}
inline void dfs (int u, int fa)
{
    L[u] = ++tim; ti[tim] = u;
    edge(i, u)
    {
        if (v == fa) continue;
        dfs(v, u);
    }
    R[u] = tim;
}
inline void pushdown (int k)
{
    if (t[k].tag)
    {
        t[k].tag = 0;
        t[ls].sum = t[rs].sum = t[k].sum;
        t[ls].tag = t[rs].tag = 1;
    }
}
inline void build (int k, int l, int r)
{
    if (l == r) {t[k].sum = 1ll << a[ti[l]]; return;}
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    t[k].sum = t[ls].sum | t[rs].sum;
}
inline void modify (int k, int l, int r, int x, int y)
{
    if (x <= l && r <= y) {t[k].sum = 1ll << val; t[k].tag = 1; return;}
    pushdown(k);
    int mid = l + r >> 1;
    if (x <= mid) modify(ls, l, mid, x, y);
    if (mid < y) modify(rs, mid + 1, r, x, y);
    t[k].sum = t[ls].sum | t[rs].sum;
}
inline ll query (int k, int l, int r, int x, int y)
{
    if (x <= l && r <= y) {return t[k].sum;}
    pushdown(k);
    int mid = l + r >> 1;
    if (y <= mid) return query(ls, l, mid, x, y);
    if (x > mid) return query(rs, mid + 1, r, x, y);
    return query(ls, l, mid, x, y) | query(rs, mid + 1, r, x, y);
}
int main ()
{
    scanf("%d %d", &n, &m);
    fo (i, 1, n)
        scanf("%d", &a[i]);
    fo (i, 2, n)
    {
        scanf("%d %d", &x, &y);
        addedge(x, y); addedge(y, x);
    }
    dfs(1, 0);
    build(1, 1, n);
    fo (I, 1, m)
    {
        scanf("%d", &opt);
        if (opt == 2)
        {
            scanf("%d", &x);
            ll ans = query(1, 1, n, L[x], R[x]);
         //   printf("%d \n", I);
            printf("%d\n", count(ans));
        }
        else
        {
            scanf("%d %d", &x, &val);
            modify(1, 1, n, L[x], R[x]);
        }
    }
    return 0;
}
```

---

