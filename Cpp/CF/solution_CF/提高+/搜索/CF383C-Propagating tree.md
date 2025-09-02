# Propagating tree

## 题目描述

很久以前，有一棵神橡树(oak)，上面有$n$个节点，从$1$~$n$编号，由$n-1$条边相连。它的根是$1$号节点。  

这棵橡树每个点都有一个权值，你需要完成这两种操作：
$1$ $u$ $val$ 表示给$u$节点的权值增加$val$  
$2$ $u$ 表示查询$u$节点的权值   

但是这不是普通的橡树，它是神橡树。  
所以它还有个神奇的性质：当某个节点的权值增加$val$时，它的子节点权值都增加$-val$，它子节点的子节点权值增加$-(-val)$...... 如此一直进行到树的底部。

## 说明/提示

$1\le n,m \le 2\times 10^5$  
$1\le a_i,val \le 1000$  
$1\le u,v \le n$

## 样例 #1

### 输入

```
5 5
1 2 1 1 2
1 2
1 3
2 4
2 5
1 2 3
1 1 2
2 1
2 2
2 4
```

### 输出

```
3
3
0
```

# 题解

## 作者：lzjsy (赞：27)

#### 本蒟蒻的第一篇题解 ~~~瑟瑟发抖~~~
首先来看题目，一棵神橡树，嗯，在树上进行的区间操作，且每一次的操作都是针对以一个节点为根节点的子树来进行的操作，很明显~~很裸~~的dfs序了。
```cpp
void dfs(int u,int fa)
{
	L[u]=++cnt;//记录每个点第一次访问时的编号
    for(int i=head[u];i!=-1;i=e[i].next)
    { 
        int v=e[i].v;
        if(v==fa)continue;
        dep[v]=dep[u]+1;
        dfs(v,u);
    }
    R[u]=cnt;//记录每个点第二次访问时的编号
}
```

绝大多数的dfs序都是可以用线段树解决的，但是毕竟代码太长，常数也比较大，此题细节又很多。。。

仔细一看询问，单点查询！！！喜出望外，

于是就自然的选择了 **树状数组** 这种神奇的方法。

但是有一个问题，这题是区间修改，单点查询，需要用到差分（这是一个很有用的算法）

```cpp
int lowbit(int x)
{
	return x&(-x);
}//返回二进制最低位的1
inline void add(int x,int z)
{
	while(x<=n) 
	tr[x]+=z，x+=x&(-x);
}//修改点权
int query(int l)
{
	int ans=0;
	while(l) ans+=tr[l],l^=lowbit(l);
	return ans;
}//查询从1到某个点的权值之和
```
继续接着往下看题
当某个节点的权值增加val，它的子节点权值都增加-val，它子节点的子节点权值增加-(-val)，这就有点不太好处理了

看有的题解是用两个树状数组来做的，就在想怎么用一个树状数组来解决

于是又想到了一个十分巧妙的做法

因为这个点进行修改操作的时候，只会与其深度的奇偶性有关，只需判断一下深度，决定修改的值的正负就好，但初值不受影响，故还需用一个数组来存储初值

此题数据范围有点坑，注意是200005而不是100005

上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define N 200005
using namespace std;
inline int read()
{
	int e=0,m=1;char z=getchar();
	while(z<48||z>57){ if(z=='-') m=-1; z=getchar(); }
	while(z>=48&&z<=57) { e=e*10+z-'0',z=getchar(); }
	return e*m;
}
struct qwe
{
    int v,w,next;
}e[2*N];
int tot,cnt=0,L[N],R[N],tr[N];
int n,m,p,head[N],dep[N];
void adde(int x,int y) 
{
    e[++tot].v=y;
    e[tot].next=head[x];
    head[x]=tot;
}
void dfs(int u,int fa)
{
	L[u]=++cnt;
    for(int i=head[u];i!=-1;i=e[i].next)
    { 
        int v=e[i].v;
        if(v==fa) continue;
        dep[v]=dep[u]+1;
        dfs(v,u);
    }
    R[u]=cnt;
}
int lowbit(int x)
{
	return x&(-x);
}
inline void add(int x,int z)
{
    while(x<=n) 
	{
	tr[x]+=z;x+=x&(-x);
	}
}
int query(int l)
{
int ans=0;
while(l) ans+=tr[l],l^=lowbit(l);
return ans;
}
int u,v,b;
int val[N];
int main()
{
	n=read(),m=read();
	memset(head,-1,sizeof(head));
	for(register int q1=1;q1<=n;q1++) val[q1]=read();
	for(register int q1=1;q1<n;q1++)
	{
		u=read(),v=read();
		adde(u,v),adde(v,u);
	}//加边
	dfs(1,0);
	for(register int q1=1;q1<=m;q1++)
	{
	u=read(),v=read();
	if(u==1)
		{
		b=read();
		if(dep[v]&1) add(L[v],b),add(R[v]+1,-b);
		else add(L[v],-b),add(R[v]+1,b);
	}//修改时要住意R[v]+1
	else
	{
		int z1=query(L[v]);
		if (dep[v]&1) printf("%d\n",val[v]+z1);
		else printf("%d\n",val[v]-z1);
	}//最后查询时还需按深度判断一下
	}
	return 0;
}
```


---

## 作者：K2sen (赞：14)

### 思路
第一眼看这个题我们很容易想到树剖加线段树，然后我们思考如何区间修改。

最朴素的想法就是让修改的子树的根结点深度奇偶性相同的加 val，不同的减去 val。我们发现这种方法我们的懒标记不能合并，所以复杂度就只能是 $\operatorname {O}(n^2 \log n)$。

我们考虑让深度为奇数的根的子树修改的时候直接加 val，偶数的直接减去 val。这样我们就消除了所加的子树根结点深度不同的问题，所以我们的懒标记就可以合并了。

因为先前我们对深度不同的结点做出的调整，所以最后我们只需要在访问到每个点的时候判断一下深度的奇偶性，对应的加减就行了。复杂度就为 $\operatorname O(n \log n)$。 

### code
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
#define N 200010
#define M 1010

using namespace std;
int n, m, sy;
int dep[N], top[N], siz[N], dfn[N], fath[N], son[N], w[N], pre[N];

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

namespace Seg {
	#define lson rt << 1
	#define rson rt << 1 | 1
	struct node {
		int sum, lazy, len, dep;
	}tree[N << 2];
	void build(int rt, int l, int r) {
		tree[rt].len = r - l + 1, tree[rt].dep = tree[rt].lazy = 0;
		if (l == r) {
			tree[rt].sum = w[pre[l]];
			tree[rt].dep = dep[pre[l]];
			return;
		}
		int mid = (l + r) >> 1;
		build(lson, l, mid);
		build(rson, mid + 1, r);
	}
	void push_down(int rt) {
		if (!tree[rt].lazy) return;
		if (tree[lson].dep != 0)
			if (tree[lson].dep % 2 == 1) tree[lson].sum += tree[rt].lazy;
			else tree[lson].sum -= tree[rt].lazy;
		if (tree[rson].dep != 0)
			if (tree[rson].dep % 2 == 1) tree[rson].sum += tree[rt].lazy;
			else tree[rson].sum -= tree[rt].lazy;
		tree[lson].lazy += tree[rt].lazy;
		tree[rson].lazy += tree[rt].lazy;
		tree[rt].lazy = 0;
	}
	void update(int rt, int c, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			tree[rt].lazy += c;
			if (tree[rt].dep)
				if (tree[rt].dep % 2 == 1) tree[rt].sum += c;
				else tree[rt].sum -=c;
			return;
		}
		push_down(rt);
		int mid = (l + r) >> 1;
		if (L <= mid) update(lson, c, l, mid, L, R);
		if (R > mid) update(rson, c, mid + 1, r, L, R);
	}
	int query(int rt, int l, int r, int pos) {
		if (l == r) return tree[rt].sum;
		push_down(rt);
		int mid = (l + r) >> 1;
		if (pos <= mid) return query(lson, l, mid, pos);
		else return query(rson, mid + 1, r, pos);
	}
}

namespace Cut {
	int cnt, add_edge, head[N << 1];
	struct node {
		int next, to;
	}edge[N << 1];
	void add(int from, int to) {
		edge[++add_edge].next = head[from];
		edge[add_edge].to = to;
		head[from] = add_edge;
	}
	void dfs(int x, int fa) {
		siz[x] = 1, fath[x] = fa, dep[x] = dep[fa] + 1;
		for (int i = head[x]; i; i = edge[i].next) {
			int to = edge[i].to;
			if (to == fa) continue;
			dfs(to, x), siz[x] += siz[to];
			if (siz[son[x]] < siz[to]) son[x] = to;
		}
	}
	void dfs2(int x, int tp) {
		dfn[x] = ++cnt, pre[cnt] = x, top[x] = tp;
		if (son[x]) dfs2(son[x], tp);
		for (int i = head[x]; i; i = edge[i].next) {
			int to = edge[i].to;
			if (to == fath[x] || to == son[x]) continue;
			dfs2(to, to);
		}
	}
}

int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) w[i] = read();
	for (int i = 1, x, y; i < n; i++) {
		x = read(), y = read();
		Cut::add(x, y), Cut::add(y, x);
	}
	Cut::dfs(1, 0), Cut::dfs2(1, 1), Seg::build(1, 1, n);
	for (int i = 1, opt, x, y; i <= m; i++) {
		opt = read();
		if (opt == 1) {
			x = read(), y = read();
			if (dep[x] % 2 == 1) Seg::update(1, y, 1, n, dfn[x], dfn[x] + siz[x] - 1);
			else Seg::update(1, -y, 1, n, dfn[x], dfn[x] + siz[x] - 1);
		}
		if (opt == 2) {
			x = read();
			printf("%d\n", Seg::query(1, 1, n, dfn[x]));
		}
	}
	return 0;
}
```

---

## 作者：cirnovsky (赞：6)

## 题意简述

给你一颗树，让你支持两种操作，一种子树修改，按深度分正负。一种单点查询节点。

## 题解

首先考虑把整棵树的DFS序整出来。然后我们可以每次递归结束后再记录一个当前的DFS序的值。

即处理出一棵树的子树中的DFS序的最大值和最小值，由于一颗子树里的DFS序一定是连续的，所以我们把这棵树用DFS序拍平到了序列上。

考虑修改操作没有限制，就是直接更新子树，那么我们可以用线段树或者树状数组来实现区间更新。

由于这个修改操作有限制，要根据修改的节点的深度分类为加或者减。所以我们可以维护两颗线段树/树状数组，一颗加，一颗减。

查询的时候我们就可以直接先查询维护加的线段树/树状数组然后减。

线段树太长，由于查询是单点操作，我们可以把序列差分，用树状数组两次单点修改，查询就两次前缀和即可。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int Maxn = 2e5 + 5;
int n, m, tot, val [ Maxn ], fwt [ 2 ][ Maxn * 2 + 5 ], dfn [ Maxn ], fywf [ Maxn ], Lp [ Maxn ], Rp [ Maxn ];
vector < int > Graph [ Maxn ];

void dfs ( int x, int fa, int k )
{
	Lp [ x ] = ++ tot;
	fywf [ x ] = k;
	for ( unsigned i = 0; i < Graph [ x ].size ( ); ++ i )
	{
		int y = Graph [ x ][ i ];
		if ( y == fa )	continue;
		dfs ( y, x, k ^ 1 );
	}
	Rp [ x ] = tot;
}

void Modify ( int x, int v, int p )
{
	for ( ; x <= n * 2; x += x & -x )
		fwt [ p ][ x ] += v;
}

int Query ( int x, int p )
{
	int res = 0;
	for ( ; x; x -= x & -x )
		res += fwt [ p ][ x ];
	return res;
}

signed main()
{
	scanf ( "%d %d", &n, &m );
	for ( int i = 1; i <= n; ++ i )	scanf ( "%d", &val [ i ] );
	for (int i = 1, x, y; i < n; ++ i) {
		scanf ( "%d %d", &x, &y );
		Graph [ x ].push_back ( y );
		Graph [ y ].push_back ( x );
	}
	dfs ( 1, 0, 0 );
	for ( int i = 0, t, x, v; i < m; ++ i )
	{
		scanf ( "%d %d", &t, &x );
		if ( t == 1 )
		{
			scanf ( "%d", &v );
			Modify ( Lp [ x ], v, fywf [ x ] );
			Modify ( Rp [ x ] + 1, -v, fywf [ x ] );
		}
		else
		{
			printf ( "%d\n", val [ x ] + Query ( Lp [ x ], fywf [ x ] ) - Query ( Lp [ x ], fywf [ x ] ^ 1 ) );
		}
	}
	return 0;
}
```

---

## 作者：SSerxhs (赞：5)

为什么要用线段树这种大常数的呢...没有区间询问，树状数组就好了啊

考虑维护一个数组$f[n]$，表示第n号节点的修改情况，其中如果$dep[n]$是奇数则记录增加量，否则记录减少量。则题中修改就等同于在dfs序上修改一段区间（因为这时候增减已经不影响了），差分树状数组即可。

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N=2e5+2,M=4e5+2;
int a[N],lj[M],nxt[M],fir[N],f[N],dfn[N],siz[N],v[N],dep[N];
int n,m,i,j,x,y,c,bs,z;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
void dfs(int x)
{
	siz[x]=1;dfn[x]=++bs;
	for (int i=fir[x];i;i=nxt[i]) if (lj[i]!=f[x])
	{
		dep[lj[i]]=dep[f[lj[i]]=x]+1;dfs(lj[i]);siz[x]+=siz[lj[i]];
	}
}
inline void add(register int x,register int y,register int z)
{
	while (x<=n) {a[x]+=z;x+=x&(-x);}++y;
	while (y<=n) {a[y]-=z;y+=y&(-y);}
}
inline int sum(register int x)
{
	register int r=0;
	while (x) {r+=a[x];x^=x&(-x);}
	return r;
}
int main()
{
	read(n);read(m);
	for (i=1;i<=n;i++) read(v[i]);
	for (i=1;i<n;i++)
	{
		read(x);read(y);
		lj[++bs]=y;
		nxt[bs]=fir[x];
		fir[x]=bs;
		lj[++bs]=x;
		nxt[bs]=fir[y];
		fir[y]=bs;
	}bs=0;
	dfs(1);
	while (m--)
	{
		read(y);read(x);
		if (y==1)
		{
			read(z);
			if (dep[x]&1) add(dfn[x],dfn[x]+siz[x]-1,z); else add(dfn[x],dfn[x]+siz[x]-1,-z);
		}
		else {z=sum(dfn[x]);if (dep[x]&1) printf("%d\n",v[x]+z); else printf("%d\n",v[x]-z);}
	}
}
```


---

## 作者：Cylete (赞：4)

其实没有那么麻烦

显然先跑dfs得出树上的序列转换为线段树

嗯，然后怎么维护呢

这道题我们不需要跑树上的路径，所以复杂度应该是$O(nlog_2n)$的

对于2操作，我们线段树$O(log_2n)$查询即可

对于1操作，我们直接在$x$子树这一段的线段树标记上，为了方便维护我们分情况标记

如果当前$x$节点深度为奇数，我们就加上$val$，为偶数就加上$-val$，对于查询的节点就是深度为奇数的加上懒惰标记，深度为偶数的减去懒惰标记

当$tree[o]$维护的是$[l, r]$且$l == r$时，那么这个$tree[o]$就是一个具体点的权值，其他的$tree[o]$就相当于懒惰标记，向下推即可。

```cpp
#define mid ((l+r)>>1)
#define lson (o<<1)
#define rson (o<<1|1)
#define R register

#define size abcdefg
const int N = 2e5 + 10;

int n, m, a[N];

int cut, head[N], ver[N << 1], next[N << 1];
inline void add(int x, int y)
{
	ver[++cut] = y; next[cut] = head[x]; head[x] = cut;
}

int deep[N], f[N], size[N], son[N], id[N], tot, dede[N];
inline void dfs1(int x, int fa)
{
	deep[x] = deep[fa] + 1;
	f[x] = fa;
	size[x] = 1;
	for(R int i = head[x]; i; i = next[i])
	{
		int y = ver[i];
		if(y == fa) continue;
		dfs1(y, x);
		size[x] += size[y];
		if(size[y] > size[son[x]]) son[x] = y;
	}
}

inline void dfs2(int x, int top)
{
	id[x] = ++tot;
	dede[tot] = x;
	if(!son[x]) return;
	dfs2(son[x], top);
	for(R int i = head[x]; i; i = next[i])
	{
		int y = ver[i];
		if(y == f[x] || y == son[x]) continue;
		dfs2(y, y);
	}
}

int tree[N << 2];
inline void build(int o, int l, int r)
{
	if(l == r)
	{
		tree[o] = a[dede[l]];
		return;
	}
	build(lson, l, mid);
	build(rson, mid + 1, r);
}

inline void pushdown(int o, int l1, int r1, int l2, int r2)
{
	if(!tree[o]) return;
	if(l1 == r1) tree[lson] += ((deep[dede[l1]] & 1) ? 1 : -1) * tree[o];
	else tree[lson] += tree[o];
	if(l2 == r2) tree[rson] += ((deep[dede[l2]] & 1) ? 1 : -1) * tree[o];
	else tree[rson] += tree[o];
	tree[o] = 0;
}

inline void update(int o, int l, int r, int ql, int qr, int val)
{
	if(ql <= l && r <= qr)
	{
		if(l == r) tree[o] += ((deep[dede[l]] & 1) ? 1 : -1) * val;
		else tree[o] += val;
		return;
	}
	pushdown(o, l, mid, mid + 1, r);
	if(ql <= mid) update(lson, l, mid, ql, qr, val);
	if(qr > mid) update(rson, mid + 1, r, ql, qr, val);
}

inline int query(int o, int l, int r, int pos)
{
	if(l == r) return tree[o];
	pushdown(o, l, mid, mid + 1, r);
	if(pos <= mid) return query(lson, l, mid, pos);
	else return query(rson, mid + 1, r, pos);
}

signed main()
{
	read(n); read(m);
	for(R int i = 1; i <= n; i++) read(a[i]);
	for(R int i = 1, x, y; i < n; i++) read(x), read(y), add(x, y), add(y, x);
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	while(m--)
	{
		int opt, x, y;
		read(opt);
		if(opt == 1)
		{
			read(x); read(y);
			if(deep[x] & 1) update(1, 1, n, id[x], id[x] + size[x] - 1, y);
			else update(1, 1, n, id[x], id[x] + size[x] - 1, -y);
		}
		else
		{
			read(x);
			writeln(query(1, 1, n, id[x]));
		}
	}
	return 0;
}
```

---

## 作者：Limit (赞：4)

这应该属于一个比较麻烦的数据结构处理树上问题.

# 题目大意

给出一颗根节点编号为 $1$ 的树,对于一个节点修改时在它的子树中对于深度奇偶性相同的节点加上这个权值,不同则减去这个值,单点查询.

# 分析

先给出这个问题的弱化版:

给出一颗根节点编号为 $1$ 的树,对于一个节点修改时在它的子树中节点也加上这个权值,单点查询.

对于上面这个问题就好处理很多了,[DFS序](https://www.baidu.com/s?wd=DFS序&ie=UTF-8)有一个性质,又称[括号定理](https://baike.baidu.com/item/括号定理/8985762?fr=aladdin),在树中这个就会体现在再DFS序中以 $a$ 为根节点的子树中的所有节点都在 $a$ 的后面,且连续,于是对于一棵树的修改在DFS序中的就变成了区间修改,那么久可以拿出一些数据结构来维护这个东西.(例如[线段树](https://baike.baidu.com/item/线段树/10983506?fr=aladdin),[树状数组](https://baike.baidu.com/item/树状数组/313739?fr=aladdin),[平衡树](https://baike.baidu.com/item/平衡树/7641279?fr=aladdin)...)

下面回到这个问题,可以发现对于深度不同的点的修改可能是不同的,只有两种修改($+val$ 和 $-val$)而且这两个修改于这个点奇偶性有关,那就有一个鼻尖暴力的想法,既然和奇偶性有关,那么久维护两颗线段树,分别维护深度为奇数的点和深度为偶数的点的值,那就变会了第一个问题.

# 细节处理
0. 记得清空 $Lazy$ 标记和下传 $Lazy$ 标记.
1. 在连边的时候需要连双向边,并且需要注意边的数组需要开两倍(这应该算是常识吧).
2. 需要处理出每个点为根节点的树中深度为奇数的点的个数和深度为偶数的点的个数,需要用来计算修改的区间的开始和结束位置.
3. 可以发现每次修改在两颗树都需要修改,对于加上 $val$ 的部分很好计算,但是对于和它深度的奇偶性不同的节点的修改就比较麻烦了,所以在DFS的时候最好记录一下每个节点的第一个子节点是谁,即谁是在DFS序(不按奇偶分开)中的下一个节点,在修改的时候只要在另一颗线段树中以它为左端点,长度为这整颗子树中的所有深度的奇偶性与根节点不同的节点个数来修改.
4. 记得需要特判一下这颗树只有一个节点的情况,这样会有一颗线段树中的大小为 $0$,但是如果在建树的时候左端点从 $1$ 开始,右端点为 $0$,会无限递归,然后MLE.(亲身经历)

# 代码实现

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int maxN=3e5+7;
int N,M;
int val[maxN];
//链式前向星,基础知识,不解释
struct Edge
{
	int to,next;
}edge[maxN*2];
int edge_head[maxN];
int edge_cnt=0;
#define FOR(now) for(int i_edge=edge_head[now];i_edge;i_edge=edge[i_edge].next)
#define TO edge[i_edge].to
void AddEdge(int form,int to)//加边
{
	edge[++edge_cnt].to=to;
	edge[edge_cnt].next=edge_head[form];
	edge_head[form]=edge_cnt;
}
//下文中0表示偶数,1表示奇数,根节点为的深度为1
int deep[maxN];//每个节点的深度
int first_son[maxN];//记录每个节点的第一个子节点
int place[maxN];//记录每格节点在按奇偶分开后的位置,因为之后存在奇偶中的一个,所以只要不需要分别
int dfs[2][maxN];//记录奇偶的两个DFS序
int dfs_cnt[2]={0,0};//记录DFS序长度
int size[2][maxN];//记录每个节点为根节点的子树中深度为奇数的节点个数和深度为偶数的节点个数
bool visit[maxN];//判断这个点是否被访问过
#define TEAM (deep[now]&1)//方便使用
void DFS(int now=1)
{
	visit[now]=1;//记录访问过这个节点
	dfs[TEAM][++dfs_cnt[TEAM]]=now;//将这个点放入它改进入的DFS序中
	place[now]=dfs_cnt[TEAM];//记录出现的位置
	size[TEAM][now]=1;//自己和自己的深度的奇偶性自然相同
	FOR(now)
	{
		if(!visit[TO])//如果没有访问过才访问
		{
			if(!first_son[now])//如果这个是他的第一个子节点
			{
				first_son[now]=TO;
			}
			deep[TO]=deep[now]+1;//子节点的深度为父节点的深度+1
			DFS(TO);//继续DFS
			//一下为记录以当前节点为根节点的子树中深度为奇和偶的节点各自的出现次数
			size[TEAM^1][now]+=size[TEAM^1][TO];
			size[TEAM][now]+=size[TEAM][TO];
		}
	}
}
#undef TEAM
#undef FOR
#undef TO
struct LazyTag//Lazy标记
{
	int add;
	void CleanLazyTag()//清空标记
	{
		add=0;
	}
}ForMake;
LazyTag MakeLazyTag(int add)//制作一个标记
{
	ForMake.add=add;
	return ForMake;
}
//线段树不是本文终于内容,不细讲
struct SegmentTree//线段树
{
	int num;
	LazyTag tag;
}sgt[2][maxN*4];//奇偶两颗线段树
#define LSON (now<<1)
#define RSON (now<<1|1)
#define MIDDLE ((left+right)>>1)
#define LEFT LSON,left,MIDDLE
#define RIGHT RSON,MIDDLE+1,right
#define NOW team,now_left,now_right,add
//想每个函数中的第一个参数team表示修改的是哪一颗线段树
void Build(int team,int now,int left,int right)//建树
{
	if(left==right)
	{
		sgt[team][now].num=val[dfs[team][left]];
		return;
	}
	Build(team,LEFT);
	Build(team,RIGHT);
}
void Down(int team,LazyTag tag,int now,int left,int right)//修改部分
{
	sgt[team][now].tag.add+=tag.add;
	if(left==right)//只有叶节点需要修改值
	{
		sgt[team][now].num+=tag.add;
	}
}
void PushDown(int team,int now,int left,int right)//下传懒标记
{
	if(sgt[team][now].tag.add)
	{
		Down(team,sgt[team][now].tag,LEFT);
		Down(team,sgt[team][now].tag,RIGHT);
		sgt[team][now].tag.CleanLazyTag();
	}
}
void Updata(int team,int now_left,int now_right,int add,int now,int left,int right)//修改部分
{
	if(now_right<left||right<now_left)
	{
		return;
	}
	if(now_left<=left&&right<=now_right)
	{
		Down(team,MakeLazyTag(add),now,left,right);
		return;
	}
	PushDown(team,now,left,right);
	Updata(NOW,LEFT);
	Updata(NOW,RIGHT);
}
int Query(int team,int place,int now,int left,int right)//查询
{
	if(right<place||place<left)
	{
		return 0;
	}
	if(left==right)
	{
		return sgt[team][now].num;
	}
	PushDown(team,now,left,right);
	return Query(team,place,LEFT)+Query(team,place,RIGHT);
}
#undef LSON
#undef RSON
#undef MIDDLE
#undef LEFT
#undef RIGHT
#undef NOW
#define TEAM (deep[u]&1)
int main()
{
	scanf("%d%d",&N,&M);
	REP(i,1,N)
	{
		scanf("%d",&val[i]);
	}
	int father,son;
	REP(i,1,N-1)
	{
		scanf("%d%d",&father,&son);
		AddEdge(father,son);//连边
		AddEdge(son,father);
	}
	deep[1]=1;
	DFS();//BFS
	//注意建树前需要判断树中是否有节点
	if(dfs_cnt[0])
	{
		Build(0,1,1,dfs_cnt[0]);
	}
	if(dfs_cnt[1])
	{
		Build(1,1,1,dfs_cnt[1]);
	}
	int opt,u,add_val;
	REP(i,1,M)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d",&u,&add_val);
			Updata(TEAM,place[u],place[u]+size[TEAM][u]-1,add_val,1,1,dfs_cnt[TEAM]);//修改奇偶性和这个点一样的部分
			if(first_son[u])
			{
				Updata(TEAM^1,place[first_son[u]/*记录第一个子节点的左右*/],place[first_son[u]]+size[TEAM^1][u]-1,-add_val,1,1,dfs_cnt[TEAM^1]);//奇偶性不同的部分
			}
		}
		if(opt==2)//查询和普通线段树差不多
		{
			scanf("%d",&u);
			printf("%d\n",Query(TEAM,place[u],1,1,dfs_cnt[TEAM]));
		}
	}
	return 0;
}
#undef TEAM
```

---

## 作者：Erusel (赞：3)

首先用 $\text{DFS}$ 序把这个问题搞到序列上

其次我们发现，每次在奇数层上 ```add val```, 每次就在偶数层上 ```add -val```

每次在偶数层上 ```add val```, 每次就在奇数层上 ```add -val```

我们只要维护两棵线段树，一棵维护奇数层，一棵维护偶数层

在建树的时候，我们记录一下当前节点是奇数层还是偶数层即可

每次在修改的时候，下传一下一个 ```flag``` , 代表当前是奇数层 ```add val```，还是 ```add -val```

在查询的时候，只要判断一下当前节点是奇数层还是偶数层，确认返回哪棵线段树的值即可

---

## 作者：ダ月 (赞：1)

提供一种不一样的做法。

我们考虑将所有询问，修改离线下来。对于每个点，我们记录两个二元集合 $val$ 和 $Q$，其中 $val$ 集合每个元素表示修改的点的点权和操作编号（指题目中第 $i$ 次操作。），$Q$ 集合每个元素表示操作编号和第 $cnt$ 次询问（注意题目中的操作分为修改和询问）。

我们首先预处理深度 $dep$。考虑 dfs，我们每次进入到一个点 $x$，我们不断访问 $val_x$ 集合，记当前访问的二元组为 $(w,id)$，我们维护一个序列 $A_i$，在 $A_{id}$ 这个位置加上 $(-1)^{dep}w$，然后访问枚举每个询问，记当前的询问的二元组为 $(id,q)$，显然对 $q$ 这次询问的贡献为 $(-1)^{dep}\sum\limits_{i=1}^{id}A_i+v_i$，$v_i$ 表示初始点权。这个显然可以树状数组来维护。然后我们在离开这个结点的时候，我们在此访问 $val_x$ 这个二元集合，在 $A_{id}$ 这个位置减去 $(-1)^{dep}w$ 来消除贡献。

其实这个做法类似扫描线加二维数点。

时间复杂度：$O(q\log n)$。

代码如下：

```
struct FwT{
	int tr[N];
	void add(int x,int y){
		for(;x<=M;x+=(x&-x))tr[x]+=y;
	}
	int query(int x){
		int ans=0;
		for(;x;x^=(x&-x))
			ans+=tr[x];
		return ans;
	}
}Tr;
void solve(){
	//don't forget to open long long
	int n,m;
	IO::cin>>n>>m;
	std::vector<int>val(n);IO::cin>>val;
	mpre(val);
	std::vector<std::vector<int>>v(n+1);
	for(int i=1;i<n;i++){
		int x,y;IO::cin>>x>>y;
		v[x].pd(y);v[y].pd(x);
	}
	std::vector<int>dep(n+1);
	auto dfs=[&](int x,int F,auto self)->void{
		dep[x]=dep[F]+1;
		for(auto y:v[x])
			if(y^F)self(y,x,self);
	};
	dfs(1,0,dfs);
	std::vector<std::vector<std::array<int,2>>>Q(n+1);
	std::vector<std::vector<std::array<int,2>>>C(n+1);
	int cnt=0;
	for(int i=1;i<=m;i++){
		int opt,x;IO::cin>>opt>>x;
		if(opt==1){
			int y;IO::cin>>y;
			C[x].pd({y,i});
		}else Q[x].pd({i,cnt++});
	}
	std::vector<int>ans(cnt);
	auto solve=[&](int x,int F,auto self)->void{
		for(auto &p:C[x])
			Tr.add(p[1],(dep[x]&1?1:-1)*p[0]);
		for(auto &p:Q[x])
			ans[p[1]]=val[x]+(dep[x]&1?1:-1)*Tr.query(p[0]);
		for(auto y:v[x])
			if(y^F)self(y,x,self);
		for(auto &p:C[x])
			Tr.add(p[1],-(dep[x]&1?1:-1)*p[0]);
	};
	solve(1,0,solve);
	IO::cout<<ans; 
}
```


---

## 作者：Terac (赞：1)

[$\texttt{Link}$](https://www.luogu.com.cn/problem/CF383C)  

提供一种不同的 dfs 序做法。  

看到题面是在树上维护各节点的值，$n\le2\times10^5$，时间复杂度大概是 $O(n\log n)$，考虑用线段树或树状数组完成这个维护。  

类似树剖处理子树修改的方式，把修改相同值的节点放到同一个区间，本题是按节点深度奇偶决定修改的值。对于节点 $u$，用 $dfn_u$ 存 dfs 序，记录 $son_u$，表示 $dfn$ 值最小的子节点，再存 $siz_{0,u}$ 和 $siz_{1,u}$，表示深度分别为奇数与偶数的子节点总数。  

在标记 dfs 序时，分两次搜索，一次标记当 $1$ 为根时，深度是奇数的节点，另一次标记当 $1$ 为根时，深度是偶数的节点，这样便保证了深度奇偶相同的节点在一个连续区间内。  

若修改以 $u$ 为根的所有子树，对于与 $u$ 深度奇偶相同的修改，即为修改区间 $\left[dfn_u,dfn_u+siz_{0,u}-1\right]$；对于与 $u$ 深度奇偶不同的修改，因为 $son_u$ 必定是 $u$ 的直系子节点，与 $u$ 深度奇偶一定不同，所以修改区间 $\left[dfn_{son_u},dfn_{son_u}+siz_{1,u}-1\right]$ 即可。  

查询就是单点查询。  

因为本题是区间修改单点查询，直接上常数小还好写的树状数组差分维护就好。  

时间复杂度 $O(n\log n)$。  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m;
int a[N];
struct edge {
	int to, nxt;
} e[N << 1];
int head[N], cnt;
void addedge(int u, int v) {
	e[++cnt] = (edge){v, head[u]};
	head[u] = cnt;
}
int dfn[N], son[N], siz[2][N], dep[N], id[N], tot;//id[i]表示dfn值为i的节点
void dfs1(int u, int f) {
	dep[u] = dep[f] + 1;
	if(dep[u] & 1) {
		dfn[u] = ++tot; id[tot] = u; siz[0][u] = 1;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(v == f) continue;
			dfs1(v, u);
			siz[0][u] += siz[1][v];
		}
	}
	else
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(v == f) continue;
			dfs1(v, u);
			if(!son[u]) son[u] = v;
			siz[1][u] += siz[0][v];
		}
}
void dfs2(int u, int f) {
	dep[u] = dep[f] + 1;
	if(!(dep[u] & 1)) {
		dfn[u] = ++tot; id[tot] = u; siz[0][u] = 1;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(v == f) continue;
			dfs2(v, u);
			siz[0][u] += siz[1][v];
		}
	}
	else
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(v == f) continue;
			dfs2(v, u);
			if(!son[u]) son[u] = v;
			siz[1][u] += siz[0][v];
		}
}
int t[N];
void add(int x, int v) {
	for(int i = x; i <= n; i += i & -i) t[i] += v;
}
int query(int x) {
	int res = 0;
	for(int i = x; i; i -= i & -i) res += t[i];
	return res;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		addedge(u, v), addedge(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	for(int i = 1; i <= n; i++) add(dfn[i], a[i] - a[id[dfn[i] - 1]]);//注意dfn与id的双射
	int op, x, y;
	while(m--) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d%d", &x, &y);
			add(dfn[x], y), add(dfn[x] + siz[0][x], -y);
			if(son[x]) add(dfn[son[x]], -y), add(dfn[son[x]] + siz[1][x], y);
		}
		else {
			scanf("%d", &x);
			printf("%d\n", query(dfn[x]));
		}
	}
	return 0;
}
```


---

## 作者：Saber_Master (赞：1)

[CF383C Propagating tree](https://www.luogu.com.cn/problem/CF383C)

这题弄清题意，明确思路，其实很简单.

此题需支持两种操作$:$区间修改和单点查询，其中区间修改的权值按深度奇偶性交替变换.

首先套路性地跑出$dfs$序和每个点的$siz$值.由于此题只需单点查询，所以给了我们很大的发挥空间.又因为区间修改的权值按深度奇偶变换，所以我们可以考虑使用线段树打上$lazy$，对于深度为奇数的点查询的时候加上$lazy$,深度为偶数的点减去$lazy$，然后就可以求出答案.注意每次查询的时候加上初始值$v$.

修改操作以查询操作为基础，对于一组修改$(u, val)$，若其深度为奇数，则直接在对应的$dfs$序$[dfn[x], dfn[x]+siz[x]-1]$上加上$val$,否则就把$val$取反进行同样的操作.

这里我用了永久化标记，很好写，代码也很短，线段树只有一个数组$lazy$.

线段树单次操作复杂度$O(\log n)$,总复杂度$O(m\log n)$

```cpp
const ll N=2e5+5;

ll head[N], to[N<<1], next[N<<1], tot;
inline void add(ll x, ll y){
	to[++tot]=y; next[tot]=head[x]; head[x]=tot;
}
inline void Link(ll x, ll y){
	add(x, y); add(y, x);
}

ll n, m, v[N];
ll dfn[N], siz[N], dep[N], cnt;

inline void dfs(ll x, ll fa){
	dep[x]=dep[fa]+1; siz[x]=1;
	dfn[x]=++cnt;
	for (R ll i=head[x], ver; i; i=next[i]){
		ver=to[i];
		if (ver==fa) continue;
		dfs(ver, x);
		siz[x]+=siz[ver];
	}
}

namespace seg{
	ll lazy[N<<2];
	
	inline void update(ll p, ll l, ll r, ll u, ll v, ll val){
		if (u<=l && r<=v) return (void)(lazy[p]+=val);
		ll mid=l+r>>1;
		if (u<=mid) update(p<<1, l, mid, u, v, val);
		if (v>mid) update(p<<1|1, mid+1, r, u, v, val);
	}
	
	inline ll ask(ll p, ll l, ll r, ll k, ll type){
		if (l==r) return lazy[p]*type;
		ll mid=l+r>>1;
		if (k<=mid) return lazy[p]*type+ask(p<<1, l, mid, k, type);
		else return lazy[p]*type+ask(p<<1|1, mid+1, r, k, type);
	}
}

int main(){
	read(n); read(m);
	for (R ll i=1; i<=n; i++) read(v[i]);
	for (R ll i=1, x, y; i<n; i++){
		read(x); read(y); Link(x, y);
	}
	dfs(1, 0);
	ll op, u, val, type;
	while(m--){
		read(op); read(u);
		if (op==1){
			read(val);
			if (!(dep[u]&1)) val=-val;
			seg::update(1, 1, n, dfn[u], dfn[u]+siz[u]-1, val);
		}else{
			if (!(dep[u]&1)) type=-1;
			else type=1;
			writeln(v[u]+seg::ask(1, 1, n, dfn[u], type));
		}
	}
}
```


---

## 作者：Seanq (赞：1)

**文章总数80祭+CF383C Propagating tree**        
题意：给出一棵n个结点的树，每个结点有一个权值，有m个操作，一个是给x结点加上val，并且给x的子节点加上-val（这里有传递性，子节点还要给其子节点加上-(-val)）。另一个操作是查询某个结点的值。      
还有，根是1       
????       
DFS序      
把树拍扁拍成一个链     
然后在上面用线段树维护      
维护啥？    
LZT(Lazy Tag)      
啥？没错，~~这题就是这么水~~，只用维护LZT即可    
单点查询+区间修改。     
单点查询so easy，但是区间修改......     
定义两个LZT，LZT1和LZT2     
记录链上每个点的深度的奇偶性     
LZT1[i]表示第i个状态的给深度为奇数的点要加的值     
LZT2[i]也同理    
然后就好写了     
std:    
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
int n,m;
int col[N];
int hed[N*2],tal[N*2],nxt[N*2],cnt=0;
int k[N];
int c[N];
int ll[N];
int rr[N];
int opt=0;
int t[N*10];
int dis[N];
int LZT1[N*10]={0};//LZT=0:不加不减 LZT>0 加 LZT<0 减  
int LZT2[N*10]={0};
int sec[N*10]={0};//sec=0:偶数层的  sec=1：奇数层的 sec=2:即有奇数层的也有偶数层的
//root=1
void push_up(int num){
    t[num]=t[num<<1]+t[num<<1|1];
}
void push_down(int l,int r,int num){
    LZT1[num<<1]+=LZT1[num];
    LZT1[num<<1|1]+=LZT1[num];
    LZT1[num]=0;
    LZT2[num<<1]+=LZT2[num];
    LZT2[num<<1|1]+=LZT2[num];
    LZT2[num]=0;
}
void addege(int x,int y){
    cnt++;
    tal[cnt]=y;
    nxt[cnt]=hed[x];
    hed[x]=cnt;
}
void dfs(int x,int father,int deep){
    k[++opt]=x;
    c[opt]=col[x];
    ll[x]=opt;
    dis[opt]=deep;
    for(int i=hed[x];i;i=nxt[i]){
        int v=tal[i];
        if(v==father) continue;
        dfs(v,x,deep+1);
    }
    k[++opt]=x;
    c[opt]=col[x];
    rr[x]=opt;
    dis[opt]=deep;
}
void build(int l,int r,int num){
    if(l==r){
        LZT1[num]=0;
        LZT2[num]=0;
        t[num]=c[l];
        sec[num]=dis[l]%2; 
        if(sec[num]==0) LZT2[num]=c[l];
        else LZT1[num]=c[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,num<<1);
    build(mid+1,r,num<<1|1);
    t[num]=t[num<<1]+t[num<<1|1];
    if(sec[num<<1]==sec[num<<1|1]) sec[num]=sec[num<<1];
    else sec[num]=2;
    LZT1[num]=0;
    LZT2[num]=0;
}
void add(int l,int r,int num,int L,int R,int v,int u){
    if(l>R||r<L) return;
    if(l>=L&&r<=R){
        if(u==1) LZT1[num]+=v,LZT2[num]-=v;
        else LZT1[num]-=v,LZT2[num]+=v;
        return;
    }
    int mid=(l+r)>>1;
    push_down(l,r,num);
    add(l,mid,num<<1,L,R,v,u);
    add(mid+1,r,num<<1|1,L,R,v,u);
} 
int ask(int l,int r,int num,int X){
// printf("** (%d-%d):%d %d**\n",l,r,num,X);
    if(l>X||r<X) return 0;
    if(l==r&&r==X){
    // for(int i=1;i<=50;i++) printf("%d %d **\n",LZT1[i],LZT2[i]);
        if(dis[X]%2==0) return LZT2[num];
        else return LZT1[num];
    }
    push_down(l,r,num);
    int mid=(l+r)>>1;
    if(mid>=X) return ask(l,mid,num<<1,X);
    else return ask(mid+1,r,num<<1|1,X);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&col[i]);
    }
    for(int i=1;i<n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        addege(a,b);
        addege(b,a);
    } 
    dfs(1,0,1);
    build(1,2*n,1);
    for(int i=1;i<=m;i++){
        int opt,a,b;
        scanf("%d",&opt);
        if(opt==1){
            scanf("%d%d",&a,&b);
            int L=ll[a],R=rr[a];
            add(1,2*n,1,L,R,b,dis[L]%2);
        }
        else{
            //for(int i=1;i<=50;i++) printf("%d %d\n",LZT1[i],LZT2[i]);
            scanf("%d",&a);
            int X=ll[a];
            printf("%d\n",ask(1,2*n,1,X));
        }
    }
    return 0;
}
```  



---

## 作者：Allons—y (赞：0)

~~~	
   这道题显然要用线段树做。
   首先线段树只能对一个区间进行操作，对于一棵树是无能为力的，所以我们要根据这棵树的DFS序建树。每个修改操作是对根为x的子树进行修改，它在DFS序中的位置可以在DFS时记录下来，左端点的位置即x的位置，右端点的位置等于它最靠右的子树的右端点的位置，回溯即可。
   注意到，要是一个节点与x的深度模2同余，修改这个节点时要加上val，否则要减去val。这样我们可以用线段树维护一段区间内的[深度模2余1-深度模2余0]的节点个数。这样对于每一次修改，一个区间的改变量就是[深度模2余1-深度模2余0]的节点个数×val(如果x的深度模2余0，应是[深度模2余0-深度模2余1]的节点个数×val，这时将val取相反数即可)。
~~~
~~~
#include<iostream>
#include<cstdio>
#include<vector>
#define S 200005
#define LL long long
using namespace std;
struct node{
    LL l,r,mid,v1,cnt,det;
}tree[4*S+5];
LL n,m,typ,x,y,u,v,val,f,len,ans,b[S+5],k[S+5],p[S+5],d[S+5],o[S+5];
vector<LL> adj[S];
inline void dfs(int cur)
{
    if(cur==1){
        d[cur]=1;//节点1深度为1
    }
    b[cur]=++len;//节点cur在d数组中下标为len
    if(!adj[cur].size()){
        p[cur]=cur;//以cur为根节点的子树(叶子节点)在d数组中右端点即cur
        return;
    }
    for(int i=0;i<adj[cur].size();i++)
    {
        d[adj[cur][i]]=d[cur]+1;//节点cur的子节点深度等于节点cur的深度+1
        dfs(adj[cur][i]);
    }
    p[cur]=p[adj[cur][adj[cur].size()-1]];//以cur为根节点的子树在d数组中右端点等于它的最右子树在的数组中的右端点
}
inline void build_segtree(LL left,LL right,LL pos)
{
    tree[pos].l=left;
    tree[pos].r=right;
    tree[pos].mid=(left+right)/2;
    if(tree[pos].l==tree[pos].r){
        if(d[o[tree[pos].l]]%2){
            tree[pos].cnt=1;//如果深度模2余1则加1
        }
        else{
            tree[pos].cnt=-1;//如果深度模2余0则减1
        }
        return;
    }
    build_segtree(tree[pos].l,tree[pos].mid,pos*2);
    build_segtree(tree[pos].mid+1,tree[pos].r,pos*2+1);
    tree[pos].cnt=tree[pos*2].cnt+tree[pos*2+1].cnt;//回溯
}
inline void push_down(LL pos)
{
	
    tree[pos*2].v1+=tree[pos].det*tree[pos*2].cnt;
    tree[pos*2+1].v1+=tree[pos].det*tree[pos*2+1].cnt;//加上det*[深度模2余1-深度模2余0]的节点个数
    tree[pos*2].det+=tree[pos].det;
    tree[pos*2+1].det+=tree[pos].det;//加上det
    tree[pos].det=0;//清零
}
inline void ask_section(LL pos)
{
    if(x<=tree[pos].l&&tree[pos].r<=y){
        ans=tree[pos].v1;
        return;
    }
    if(tree[pos].det){
        push_down(pos);//下发懒标记
    }
    if(x<=tree[pos].mid){
        ask_section(pos*2);
    }
    if(tree[pos].mid+1<=y){
        ask_section(pos*2+1);
    }
}
inline void add_section(LL pos)
{
    if(x<=tree[pos].l&&tree[pos].r<=y){
        tree[pos].v1+=val*tree[pos].cnt;//加上val*[深度模2余1-深度模2余0]的节点个数
        tree[pos].det+=val;
        return;
    }
    if(tree[pos].det){
        push_down(pos);//下发懒标记
    }
    if(x<=tree[pos].mid){
        add_section(pos*2);
    }
    if(tree[pos].mid+1<=y){
        add_section(pos*2+1);
    }
    tree[pos].v1=tree[pos*2].v1+tree[pos*2+1].v1;//回溯
}
int main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&k[i]);//输入节点初值
    }
    for(int i=1;i<=n-1;i++)
    {
        scanf("%lld%lld",&u,&v);
        adj[u].push_back(v);//连边
    }
    dfs(1);//DFS得到每棵子树在d数组中的左，右端点位置
	for(int i=1;i<=n;i++)
    {
        o[b[i]]=i;//将d数组中下标与节点编号对应 
    }
    build_segtree(1,n,1);
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld",&typ,&f);
        if(typ==1){
            x=b[f];//以f为根节点的子树的左端点位置
            y=b[p[f]];//以f为根节点的子树的右端点位置
            scanf("%lld",&val);
            val*=(d[f]%2*2-1);//判断根节点深度模2结果，改变val正负
            add_section(1);//修改子树
        }
        else{
            ans=0;
            x=b[f];//节点f的左端点位置
            y=b[f];//节点f的右端点位置
            ask_section(1);//区间查询和(懒得写单点查询)
            ans+=k[f];//ans加上该节点初值
            printf("%lld\n",ans);//输出
        }
    }
    return 0;
}
~~~

---

