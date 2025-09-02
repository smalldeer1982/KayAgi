# Book of Evil

## 题目描述

Paladin Manao caught the trail of the ancient Book of Evil in a swampy area. This area contains $ n $ settlements numbered from 1 to $ n $ . Moving through the swamp is very difficult, so people tramped exactly $ n-1 $ paths. Each of these paths connects some pair of settlements and is bidirectional. Moreover, it is possible to reach any settlement from any other one by traversing one or several paths.

The distance between two settlements is the minimum number of paths that have to be crossed to get from one settlement to the other one. Manao knows that the Book of Evil has got a damage range $ d $ . This means that if the Book of Evil is located in some settlement, its damage (for example, emergence of ghosts and werewolves) affects other settlements at distance $ d $ or less from the settlement where the Book resides.

Manao has heard of $ m $ settlements affected by the Book of Evil. Their numbers are $ p_{1},p_{2},...,p_{m} $ . Note that the Book may be affecting other settlements as well, but this has not been detected yet. Manao wants to determine which settlements may contain the Book. Help him with this difficult task.

## 说明/提示

Sample 1. The damage range of the Book of Evil equals 3 and its effects have been noticed in settlements 1 and 2. Thus, it can be in settlements 3, 4 or 5.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337D/bb5982168a46056c0b6c7bf34dd6accd73b10df3.png)

## 样例 #1

### 输入

```
6 2 3
1 2
1 5
2 3
3 4
4 5
5 6
```

### 输出

```
3
```

# 题解

## 作者：Elma_ (赞：32)

## Description

[题目链接](https://codeforces.ml/problemset/problem/337/D)

有 $n$ 个点，$(n-1)$ 条边，$m$ 个鬼，求存在多少个点使得这个点到每个鬼的距离都不超过 $d$？

## Solution

这里提供一种 $3$ 次 dfs 的做法，个人感觉比树DP好写而且比较好理解。

找出在这颗树上距离最远的两只鬼，将它们的位置设为 $A,B$。类似于树的直径，这颗树上的其余点具有这样的性质：

- 如果某一个点到 $A$ 和 $B$ 的距离都不超过 $d$，那么该点到其余鬼所在点的距离也不会超过 $d$。

否则，如果存在某一个鬼和该点的距离超过 $d$，那么这个鬼所在的位置离 $A,B$ 两点中某一点的距离大于 $A,B$ 两点间的距离。

考虑证明这一个性质。设该点为 $P$，分点 $P$ 在 $A,B$ 两点的路径上和 $P$ 点在 $A,B$ 两点路径之外两种情况讨论。记 $dis(x,y)$ 表示 $x,y$ 两点之间的距离。

- 设点 $P$ 在 $A,B$ 路径上，设另有一只鬼在点 $C$。

反证法。假设 $dis(P,C) > d$，而根据前面性质的定义有 $dis(B,P) \leq d$，于是有 $dis(P,C) > dis(B,P)$。两边同时加上 $dis(A,P)$ 得到:

$$dis(P,C) + dis(A,P) > dis(B,P) + dis(A,P) \to dis(A,C) > dis(A,B)$$

与 $A,B$ 为距离最远的两只鬼矛盾。在这种情况下，该命题得证。

- 设点 $P$ 在 $A,B$ 路径之外，设另有一只鬼在点 $C$。

这种情况中还包含着两种小情况，同样使用反证法。

1. 若 $P,C$ 两点间的路径和 $A,B$ 两点间的路径没有交点：

设有两点 $U,V$，$U,V$ 之间有边连接且 $U$ 在 $A,B$ 路径上，$V$ 在 $P,C$ 路径上。

假设 $dis(P,C) > d$，而 $dis(B,P) \leq d$，于是有 $dis(P,C) > dis(B,P)$。两边同时减 $dis(V,P)$ 得到:

$$dis(V,C) > dis(B,V)$$

两边同时加上$dis(A,V)$，得到:

$$dis(A,C) > dis(A,B) + 2 \times dis(U,V)$$

与 $A,B$ 为距离最远的两只鬼矛盾。

2. 若 $P,C$ 两点间的路径和 $A,B$ 两点间的路径有交点，设交点为 $X$ :

假设 $dis(P,C) > d$，而 $dis(B,P) \leq d$，于是有 $dis(P,C) > dis(B,P)$。两边同时减 $dis(X,P)$ 得到:

$$dis(X,C) > dis(X,B)$$

两边同时加上$dis(A,X)$得到:

$$dis(A,C) > dis(A,B)$$

与 $A,B$ 为距离最远的两只鬼矛盾。该性质得证。

考虑如何找到最远的两只鬼 $A,B$。和树的直径相同，我们可以很自然的想到两次 dfs 的方法，第一次从任意一点出发找到离该点最远的一只鬼 $A$，第二次从 $A$ 点出发找到离鬼 $A$ 最远的一只鬼 $B$。

于是这个问题可以转化为找到 $dis(i,A) \leq d$ 且 $dis(i, B) \leq d$ 的点的个数。所以只需要求出每个点离点 $A$ 和点 $B$ 的距离。和点$A$的距离在前两次 dfs 中已经求出，所以只需要再加一次 dfs 求出每个点到点 $B$ 的距离即可。

总共三次 dfs，最后扫一遍所有点统计答案。总时间复杂度为 $O(n)$。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define maxn 1000005
using namespace std;

inline int read()
{
    int x = 0, w = 1;char ch = getchar();
    while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
    while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
    return x * w;
}

struct node
{
	int to, nxt;
}edge[maxn << 1];
int n, m, d, tot, tmp, ans;
int evil[maxn], dis1[maxn], dis2[maxn], head[maxn];

inline void add(int u, int v) { edge[++tot].nxt = head[u];edge[tot].to = v;head[u] = tot; }
inline void addedge(int u, int v) { add(u, v), add(v, u); }

void dfs1(int u, int fath, int dep)
{
	dis1[u] = dep;
	for (int i = head[u];i;i = edge[i].nxt)
	{
		int v = edge[i].to;
		if (v != fath) 
			dfs1(v, u, dep + 1);
	}
}

void dfs2(int u, int fath, int dep)
{
	dis2[u] = dep;
	for (int i = head[u];i;i = edge[i].nxt)
	{
		int v = edge[i].to;
		if (v != fath)
			dfs2(v, u, dep + 1);
	}
}

int main(void)
{
	n = read(), m = read(), d = read();
	for (int i = 1;i <= m;i++)
		evil[i] = read();
	for (int i = 1;i < n;i++)
	{
		int u = read(), v = read();
		addedge(u, v);
	}
	dfs1(1, 0, 0);
	for (int i = 1;i <= m;i++)
		if (dis1[evil[i]] > dis1[tmp]) tmp = evil[i];
	dfs1(tmp, 0, 0);tmp = 0;
	for (int i = 1;i <= m;i++)
		if (dis1[evil[i]] > dis1[tmp]) tmp = evil[i];
    dfs2(tmp, 0, 0);
	for (int i = 1;i <= n;i++)
		if (dis1[i] <= d && dis2[i] <= d) ans++;
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：Wen_kr (赞：31)

树形dp
设 $dp[i][1]$ 表示 $i$ 到其子树内有怪物的点的最大距离

$dp[i][2]$ 表示 $i$ 到其子树内有怪物的点的次大距离

$dis[i]$ 表示 $i$ 到其子树**以外**的节点的最大距离

$dp[i][1],dp[i][2]$可以在一次dfs内计算完毕，伪代码如下：

假设当前递归到 u 子树：
```
for v in son[u]:
	work(v)
    if dp[v][1] + 1 > dp[u][1]
    {
    	dp[u][2] = dp[u][1];
        dp[u][1] = dp[v][1] + 1;
	}
    else dp[u][2] = max(dp[u][2],dp[v][1] + 1)
```

第二次 $dfs$ 我们使用父亲节点的信息计算儿子节点的 $dis$ 值

伪代码如下：($u$的定义同上)
```
for v in son[u]:
	if dp[v][1] + 1 = dp[u][1]
    	dis[v] = max(dis[u] + 1,dp[u][2] + 1)
    else
    	dis[v] = max(dis[u] + 1,dp[u][1] + 1)
```
道理很好解释：

若 $dp[u][1]$ 是由 $dp[v][1]$ 转移过去的，$dis[v]$ 有两种情况：

1.位于距离 $u$ 次大的那棵子树上（其他子树是没有意义的因为无论如何距离都不会大于次大子树的距离）

2.位于 $u$ 的父亲节点或以上

最后

若 $dp[i][1] <= d$并且$dis[i] <= d$那么$ans$增加1

最后输出就可以啦~

```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int dist[100050][3],dis[100050];

struct edge
{
	int v,nxt;
}e[200050];

int ecnt,head[100050];

void adde(int u,int v)
{
	e[++ecnt].v = v;
	e[ecnt].nxt = head[u];
	head[u] = ecnt;
}

bool evil[100050];

void dfs(int u,int lst)
{if(evil[u])
		dist[u][1] = dist[u][2] = 0;
	for(int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].v;
		if(v == lst) continue;
			dfs(v,u);
		if(dist[v][1] + 1 > dist[u][1])
		{
			dist[u][2] = dist[u][1];
			dist[u][1] = dist[v][1] + 1;
		}
		else dist[u][2] = max(dist[v][1] + 1,dist[u][2]);
	}
	
	return ;
}

void dfs2(int u,int lst)
{
	for(int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].v;
		if(v == lst)
			continue;
		if(dist[u][1] == dist[v][1] + 1)
			dis[v] = max(dis[u] + 1,dist[u][2] + 1);
		else
			dis[v] = max(dis[u] + 1,dist[u][1] + 1);
		dfs2(v,u);
	}
	return ;
}

int d;

int main()
{
	memset(dist,128,sizeof(dist));
	memset(dis,128,sizeof(dis));
	int n,m;
	scanf("%d%d%d",&n,&m,&d);
	for(int i = 1;i <= m; ++ i)
	{
		int p;
		scanf("%d",&p);
		evil[p] = 1;
	}
	for(int i = 1;i < n;++ i)
	{
		int fr,t;
		scanf("%d%d",&fr,&t);
		adde(fr,t);
		adde(t,fr);
	}
	dfs(1,0);
	dfs2(1,0);
	int ans=  0;
	for(int i = 1;i <= n; ++ i)
	{
		if(i == 1)
		{
			if(dist[i][1] <= d && dist[i][2] <= d) ans++;
		}
		else if(dis[i] <= d && dist[i][1] <= d)
			ans ++;
	}
	printf("%d\n",ans);
}
```

---

## 作者：KemononeRou (赞：10)

可以发现相当于要求出有多少个点到给定的 $m$ 个关键点距离的最大值 $\leq d$。

考虑在 dfs 的过程中，维护当前位置到每个点的距离。

发现从一个点走向它的儿子 $x$，当前位置到 $x$ 子树内的点的距离会减少 $1$，到 $x$ 子树外的点的距离会增加 $1$。

把树拍到 dfs 序上，再用线段树区间修改维护最大值即可。

[Code](luogu.com.cn/paste/srjy4c7l)

---

## 作者：RainAir (赞：9)

感觉比楼上的 dp 好理解一点 Orz
### 题目描述
指定在树上的一些点，求有多少个点到指定的点的距离不超过 $d$
### 解题报告
朴素的思想是对于每一个点限制次数的 `bfs` 并且统计答案。这样显然不能过。

我们考虑优化这个做法。

这个算法的瓶颈主要在于做了太多无用的 `bfs`，我们考虑哪些 `bfs` 是必要的。

不难发现，我们可以找出指定的点中距离最短的一对点（可以用两遍 `bfs` 来解决），然后到指定点距离不超过 $d$ 的点就是到这两个点的距离不超过 $d$ 的点。

于是 $3$ 遍 `bfs` 就可以解决问题。时间复杂度 $O(n)$

详细的说，第一遍 `bfs` 处理以 $1$ 号节点为根的其余节点的深度，并找出距离 $ 1 $ 号节点最远的节点 $u$ ，第二遍 `bfs` 类比第一遍找出 $u$ 的最远点 $v$ 。第三遍 `bfs` 处理以$v$为根的每个节点的深度。最后扫一遍所有点，找出满足条件 $ d1_i \leq k $ 且 $d2_i \leq k$ 的点即可。
### 参考代码
```c++
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;

const int MAXN = 100000 + 5;

struct Node{
    struct Edge *firstEdge;
    int depth[4];
    bool vis[4];
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN*2],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

void bfs(int s,int turn){
    node[s].depth[turn] = 0;
    node[s].vis[turn] = true;
    std::queue<Node *> q;
    q.push(&node[s]);
    while(!q.empty()){
        Node *v = q.front();q.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->vis[turn]) continue;
            e->t->vis[turn] = true;
            e->t->depth[turn] = v->depth[turn] + 1;
            q.push(e->t);
        }
    }
}

int N,M,D;
int a[MAXN];

inline int getmax(int turn){
    int ret = a[1];
    FOR(i,2,M)
        if(node[a[i]].depth[turn] > node[ret].depth[turn])
            ret = a[i];
    return ret;
}

int main(){
    read(N);read(M);read(D);
    FOR(i,1,M) read(a[i]);
    FOR(i,1,N-1){
        int u,v;read(u);read(v);
        add(u,v);
    }
    bfs(1,1);
    bfs(getmax(1),2);
    bfs(getmax(2),3);
    int ans = 0;
    FOR(i,1,N){
        if(node[i].depth[2] <= D && node[i].depth[3] <= D) ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：critnos (赞：7)

啪的一下就秒了啊，很快啊~

枚举每个点 $i$，然后求是否所有的出现怪物的点都在 $i$ 的 $d$ 范围内，即求点 $i$ 距离 $d$ 的出现怪物的点的数量是否等于 $m$。

这不就是点分树模板吗？

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;
struct node
{
	int x,nxt;
}a[200005];
int head[100005];
bool t[100005];
int cnt,m,w;
int size[100005],f[100005],d[100005],son[100005];
int top[100005];
int sum[100005];
int xfa[100005];
int allcnt;
int bitt[10000005];
int v[100005];
struct bit
{
	int l;
	int n;
	void build(int n_)
	{
		n=n_+2,l=++allcnt,allcnt+=n+1;
	}
	void add(int x,int v)
	{
		for(x++;x<=n;x+=lowbit(x))
			bitt[x+l]+=v;
	}
	int ask(int x)
	{
		x=min(x+1,n);
		int s=0;
		for(;x;x-=lowbit(x))
			s+=bitt[x+l];
		return s;
	}
}p[100005],fa[100005];
//pi：点i为分治重心的子树信息
//fai：以fatheri为根到i的子树信息 
void addedge(int x,int y)
{
	a[++cnt]=node({y,head[x]});
	head[x]=cnt;
}
void dfs1(int x,int deep,int fa,int s)
{
	size[x]=1;
	f[x]=fa;
	d[x]=deep;
	sum[x]=s;
	int i,y;
	for(i=head[x];i;i=a[i].nxt)
	{
		y=a[i].x;
		if(y==fa) continue;
		dfs1(y,deep+1,x,s+1);
		size[x]+=size[y];
		if(size[son[x]]<=size[y])
			son[x]=y;
	}
}
void dfs2(int x,int t)
{
	top[x]=t;
	if(!son[x]) return;
	dfs2(son[x],t);
	int i,y;
	for(i=head[x];i;i=a[i].nxt)
	{
		y=a[i].x;
		if(y==f[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}
int asklca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(d[top[x]]>=d[top[y]])
			x=f[top[x]];
		else
			y=f[top[y]];
	}
	return d[x]<d[y]?x:y;
}
int asksum(int x,int y)
{
	return sum[x]+sum[y]-sum[asklca(x,y)]*2;
}
pair<int,int> findroot(int w,int fa,int pre)
{
	size[w]=1;
	int i,mx=0;
	pair<int,int> ans=make_pair(1e9,0);
	for(i=head[w];i;i=a[i].nxt)
	{
		if(t[a[i].x]||a[i].x==fa) continue;
		ans=min(ans,findroot(a[i].x,w,pre));
		size[w]+=size[a[i].x];
		mx=max(mx,size[a[i].x]);
	}
	ans=min(ans,make_pair(max(mx,pre-size[w]),w));
	return ans;
}
void build(int d,int pre,int fat)
{
	int rt=findroot(d,0,pre).second,i,ret=size[d];
	p[rt].build(ret),fa[rt].build(ret);
	t[rt]=1;
	xfa[rt]=fat;
	for(i=head[rt];i;i=a[i].nxt)
		if(!t[a[i].x])
			build(a[i].x,ret,rt);	
}
//pi：点i为分治重心的子树信息
//fai：以fatheri为根到i的子树信息 
int ask(int x,int k)
{
	int s=p[x].ask(k),i,f,d;
	for(i=x;xfa[i];i=f)
	{
		f=xfa[i];
		d=asksum(f,x);
		if(k>=d)s+=p[f].ask(k-d)-fa[i].ask(k-d);
	}
	return s;
}
void add(int x,int y)
{
	int i,d,f;
	p[x].add(0,y);
	for(i=x;xfa[i];i=f)
	{
		f=xfa[i],d=asksum(x,f);
		p[f].add(d,y);
		fa[i].add(d,y);
	}
}
int main()
{
	int n,m,d,i,opt,x,y,sum=0;
	scanf("%d%d%d",&n,&m,&d);
	for(i=0;i<m;i++)
		scanf("%d",&v[i]);
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		addedge(x,y),addedge(y,x);
	}
	dfs1(1,1,0,0);
	dfs2(1,1);
	memset(size,0,sizeof(size));
	build(1,n,0);
	for(i=0;i<m;i++)
		add(v[i],1);
	for(i=1;i<=n;i++)
		if(ask(i,d)==m)
			sum++;
	cout<<sum;
}
```


---

## 作者：览遍千秋 (赞：6)

## 题目大意

给出一棵有 $n$ 个结点的树，其中 $m$ 个结点 $p_1,p_2,\cdots,p_m$ 作特殊标记，令 $dis(x,y)$ 代表结点 $x$ 到 $y$ 简单路径上边数，求有多少个点 $x$ ，满足 $\forall i \in [1,m] ,\max\{dis(x,p_i)\} \le d$

---

## 题解

不妨令 $1$ 为根。

考虑结点 $x$ 的最远标记点，可以在 $x$ 的子树 $T(x)$ 内，也可以在 $x$ 的子树外。

对这两种情况分别讨论。

### $\texttt{Part I}$

在 $x$ 的子树内情况比较简单，可以通过一次 dfs 求出。

记 $dp(x)$ 为 $T(x)$ 内最远标记点到 $x$ 的距离，如果 $T(x)$ 内没有标记点，则 $dp(x) = +\infty$

但在这个 dfs 过程中，还要维护$T(x)$ 内第二远标记点到 $x$ 的距离 $dp2(x)$，原因将在 $\texttt{Part II}$ 解释。

### $\texttt{Part II}$

在 $x$ 的子树外情况比较复杂，但可以自然地想到是一个换根 DP：根 $1$ 号点不存在子树外情况，已经可以求解。

假设 $y$ 是 $x$ 的任一儿子，此时对 $y$ 有两种情况：

 - $dp(x) = dp(y) + 1$ ，即 $dp(x)$ 由 $dp(y)$ 转移而来
 - $dp(x) \neq dp(y) + 1$ ，即 $dp(x)$ 不是由 $dp(y)$ 转移而来。

以题目样例为例

![](https://cdn.luogu.com.cn/upload/image_hosting/lem2dp1d.png)

其中 $1$ 号点只有一个儿子 $5$ 号点，那么 $5$ 号点符合上述的第一种情况，也就是说，$1$ 号点的最远点就在孩子 $5$ 号子树内。

此时，如果从 $1$ 号点向 $5$ 号点换根，如果使用 $dp(1)$，则 $5$ 号点子树外的情况并未得到考虑，所以还需要记录 $\texttt{Part I}$ 中所述的 $dp2(x)$ ，并在换根过程中分类讨论。

其他细节请见代码。

---

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

template < typename Tp >
void read(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}

const int maxn = 100000 + 7;
const int maxm = 200000 + 7;
const int INF = 0x3f3f3f3f;

int n, m, d, dp[maxn], dp2[maxn];
bool mark[maxn];

int Head[maxn], Next[maxm], to[maxm], tot;
void addedge(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void add(int x, int y){
	addedge(x, y); addedge(y, x);
}

void Init(void) {
	read(n); read(m); read(d);
	for(int i = 1, x; i <= m; i++) {
		read(x); mark[x] = true;
	}
	for(int i = 1, x, y; i < n; i++) {
		read(x); read(y);
		add(x, y);
	}
}

void dfs(int x, int fa) {
	dp[x] = dp2[x] = INF;
	for(int i = Head[x] ;i ; i = Next[i]) {
		int y = to[i];
		if(y == fa) continue;
		dfs(y, x);
		if(dp[y] != INF) {
			if(dp[x] == INF) dp[x] = dp[y] + 1;
			else {
				if(dp[y] + 1 > dp[x]) {
					dp2[x] = dp[x];
					dp[x] = dp[y] + 1;
				}
				else if(dp2[x] == INF) dp2[x] = dp[y] + 1;
				else dp2[x] = max(dp2[x], dp[y] + 1);
			}
		}
	}
	if(dp[x] == INF) if(mark[x]) dp[x] = 0;
}

int ans;

void dfs2(int x, int fa, int mov) {
	if(mov == INF && mark[fa]) mov = 1;
//	printf("id = %d, fa = %d, mov = %d, dp[x] = %d\n", x, fa, mov, dp[x]);
	if((dp[x] <= d || dp[x] == INF) && (mov <= d || mov == INF)) {
		++ans;
	}
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == fa) continue;
		if(dp[x] == dp[y] + 1) {
			if(mov == INF && dp2[x] != INF) dfs2(y, x, dp2[x] + 1);
			else if(mov != INF && dp2[x] == INF) dfs2(y, x, mov + 1);
			else if(mov == INF && dp2[x] == INF) dfs2(y, x, INF);
			else dfs2(y, x, max(dp2[x], mov) + 1);
		}
		else {
			if(mov == INF && dp[x] != INF) dfs2(y, x, dp[x] + 1);
			else if(mov != INF && dp[x] == INF) dfs2(y, x, mov + 1);
			else if(mov == INF && dp[x] == INF) dfs2(y, x, INF);
			else dfs2(y, x, max(dp[x], mov) + 1);
		}
	}
}

void Work(void) {
	dfs(1, 0);
//	for(int i = 1; i <= n; i++) {
//		printf("%d : %d\n", i, dp[i]);
//	}
	dfs2(1, 0, INF);
	printf("%d\n", ans);
}

int main(void) {
	Init();
	Work();
	return 0;
}
```

---

## 作者：LlLlCc (赞：4)

## 题目大E：
给定一棵$n$个节点的树，其中$m$个点为特殊点，求有多少个点到所有特殊点的距离最大值小于$d$

------------
比较套路的树形$dp$，对每个点考虑由子树转移来的最远距离和由父节点转移来的最远距离，设：

$\large f_i:$节点$i$所有子树中的最远的特殊点距离

$\large g_i:$节点$i$所有非子树中的最远的特殊点距离

$\large f$数组很容易求，对于每个$i$，找所有子节点中最大的$f_{son}$，即：

$\Large f_i=\max f_{son}+1$

$\large g$数组也很好求，因为每一个$i$只有可能由父节点或者兄弟节点转移过来，即$\large g_{fa}$和父节点所有子节点中最大的$\large f_{fa_{son}}$，所以：

$\Large g_i=\max(g_{fa}+1,\max f_{fa_{son}}+2)$

但因为父亲的最大$f$子节点可能就是$i$，所以我们还要记一下次大值

统计答案也比较方便，只有找有几个$i$满足$\large g_i\leq d$并且$\large f_i\leq d$即可

即： $\Large \sum\limits_{i=1}^n[max(g_i,f_i)\leq a]$

## code
```
#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
int n,m,ans,f[maxn],d,g[maxn],Mx[maxn][2],mx[maxn][2],lnk[maxn],nxt[maxn],son[maxn],tot;
bool vis[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void dfs(int x,int fa){
	if (vis[x]) f[x]=0;
	for (int i=lnk[x];i;i=nxt[i]) if (son[i]!=fa){
		dfs(son[i],x);if (f[son[i]]!=-1) f[x]=max(f[x],f[son[i]]+1);
		if (f[son[i]]!=-1&&f[son[i]]>=Mx[x][0]) Mx[x][1]=Mx[x][0],mx[x][1]=mx[x][0],Mx[x][0]=f[son[i]],mx[x][0]=son[i];
		else if (f[son[i]]!=-1&&f[son[i]]>=Mx[x][1]) Mx[x][1]=f[son[i]],mx[x][1]=son[i];
	}
}
inline void dfs2(int x,int fa){
	if (vis[x]) g[x]=0;
	if (mx[fa][0]&&x!=mx[fa][0]) g[x]=max(g[x],Mx[fa][0]+2);
	else if (mx[fa][1]) g[x]=max(g[x],Mx[fa][1]+2);
	if (g[fa]!=-1) g[x]=max(g[x],g[fa]+1);
	for (int i=lnk[x];i;i=nxt[i]) if (son[i]!=fa) dfs2(son[i],x);
}
int main(){
	n=read(),m=read(),d=read();memset(f,-1,sizeof f);memset(g,-1,sizeof g);
	for (int i=1;i<=m;i++) vis[read()]=1;
	for (int i=1,x,y;i<n;i++) x=read(),y=read(),add(x,y),add(y,x);
	dfs(1,0);dfs2(1,0);
	for (int i=1;i<=n;i++) if (max(g[i],f[i])<=d) ans++;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：空の軌跡 (赞：4)

跟那篇题解类似，但是还是有点区别。

# 思路

题目要求找到所有与指定点距离 $<=d$ 的点，这里我们理所应当就是想到树上最远的两个指定的点对，我们将其分别当做 $A,B$ 。

对于树上除 $A,B$ 外任意一点 $X$，我们将其连接的所有边分为三种：

- 向 $A$ 走的边，有且仅有一条。

- 向 $B$ 走的边，有且仅有一条。

- 剩余的边，可能有多条，也可能没有。

对于这个点，如果它放置魔法书在范围内能够覆盖 $A,B$ 点，那么：

- 对于 $A$ 类边的子树中的指定点，我们可以保证任意一个点到 $X$ 的距离不超过 $A$ 到当前点的距离，否则它可以作为与 $B$ 匹配的更远点，与 $A$ 作为最远点对的事实冲突。

- 对于 $B$ 类边的子树中的指定点，同理。

- 对于其余类边的子树中的指定点，其距离也绝不超过  $ min(dis(X,A),dis(X,B))$ 。 同理 ，否则其可以取代 $A$ 或 $B$ 成为与另一点匹配的最远点。

综上所述，只要我们覆盖了 $A,B$ ，那么其余指定点一定也会被覆盖。

所以再分别以 $A,B$ 为根处理其余所有点的深度。

于是我们只要 $ O(n) $计算某一点 $X$ 的 $max(dis(A,X),dis(B,X))$ 并判断即可。

上述做法已经很优秀，达到 $O(N)$ 的复杂度 。

但是我最后的处理方法还略有区别。

我是将 $A$ 作为根后处理出其余所有点的深度，然后从 $B$ 向上跳，对于你跳到的每个点 $X$ ，你都计算其 $d-max(dis(A,X),dis(B,X))$ ，这意味着你可以向 其余类边 所移动的距离，每向 其余类边 移动，你都可以到达的点统计入答案。控制好距离，你就可以保证不会有不合法的统计了。

可能这个没有上面的做法简单，但是实际的运行速度应该会更快。


# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>
#include<stack>
#include<queue>
#include<iomanip>
#include<map>
#include<ctime>
#include<cstdlib>
using namespace std;
inline void read(int &x)
{
	int w=1;x=0;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	x*=w;
}
vector<int>side[100010];
bool ye[100010];
int maxdis,id;
int dep[100010],fa[100010];
void dfs(int x,int fr,int dis)
{
	dep[x]=dis;fa[x]=fr;
	if(ye[x]&&maxdis<dis)
	{
		maxdis=dis;
		id=x;
	}
	for(int i=0;i<side[x].size();i++)
	{
		int to=side[x][i];
		if(to==fr)continue;
		dfs(to,x,dis+1);
	}
}
int tot=0;
bool used[100010];
void solve(int x,int dis)
{
	++tot;
	if(dis==0)return;
	for(int i=0;i<side[x].size();i++)
	{
		int to=side[x][i];
		if(to==fa[x]||used[to])continue;
		solve(to,dis-1);
	}
}
int main()
{
	int n,m,k,a,b,c;cin>>n>>m>>k;
	if(m==0)
	{
		cout<<n;
		return 0;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>c;
		ye[c]=1;
	}
	for(int i=1;i<n;i++)
	{
		cin>>a>>b;
		side[a].push_back(b);
		side[b].push_back(a);
	}
	dfs(c,c,1);
	int A=id;
	maxdis=0;
	dfs(id,id,1);
	int B=id;
	while(1)
	{
		used[id]=1;
		int ok=min(k-dep[id]+dep[A],k-dep[B]+dep[id]);
		if(ok>-1)solve(id,ok);
		if(id==A)break;
		id=fa[id];
	}
	cout<<tot;
}
```

---

## 作者：MeowScore (赞：4)

题面：给出一棵有 $n$ 个节点的树，树上有 $m$ 个关键点，求有多少个点满足所有关键点距离它都不超过 $d$。

我们可以把问题转化为“有多少个点满足距离它不超过 $d$ 的点中包含 $m$ 个关键点”。我们把关键点的权值设为 $1$，其余为 $0$，然后枚举所有点，如果距离它不超过 $d$ 的点的权值和是等于 $m$，则答案加一。

这个一看就是点分树啦。

我太懒了，随便花两分钟改了改点分树模板水过去了。

```
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
inline int read(){
	int ss=0,ww=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			ww=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ss=ss*10+ch-'0';
		ch=getchar();
	}
	return ss*ww;
}
inline int max(int x,int y){
	return x>y?x:y;
}
struct ST{
	struct nd{
		int ls;
		int rs;
		int sum;
	}st[N*100];
	int rt[N];
	int ncnt=0;
	void change(int &root,int l,int r,int x,int k){
		if(!root){
			ncnt++;
			root=ncnt;
		}
		if(l==r){
			st[root].sum+=k;
			return;
		}
		int mid=(l+r)/2;
		if(mid>=x)
			change(st[root].ls,l,mid,x,k);
		else
			change(st[root].rs,mid+1,r,x,k);
		st[root].sum=st[st[root].ls].sum+st[st[root].rs].sum;
	}
	int ask(int root,int l,int r,int x,int y){
		if(!root)
			return 0;
		if(l>=x&&r<=y)
			return st[root].sum;
		int ans=0;
		int mid=(l+r)/2;
		if(mid>=x)
			ans+=ask(st[root].ls,l,mid,x,y);
		if(mid+1<=y)
			ans+=ask(st[root].rs,mid+1,r,x,y);
		return ans;
	}
}st1,st2;
int ans;
int n,m;
int head[N],to[N*2],nex[N*2],cnt;
inline void add(int x,int y){
	cnt++;
	to[cnt]=y;
	nex[cnt]=head[x];
	head[x]=cnt;
}
int dfa[N];
int d[N];
int fa[N],tp[N],son[N],sz[N];
bool del[N];
int maxp[N];
int D;
void getsz(int x,int F){
	sz[x]=1;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==F||del[y])
			continue;
		getsz(y,x);
		sz[x]+=sz[y];
	}
}
void getrt(int x,int F,int &nw,int tot){
	maxp[x]=0;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==F||del[y])
			continue;
		getrt(y,x,nw,tot);
		maxp[x]=max(maxp[x],sz[y]);
	}
	maxp[x]=max(maxp[x],tot-sz[x]);
	if(maxp[x]<maxp[nw])
		nw=x;
}
void solve(int x,int F){
	getsz(x,F);
	int rt=0;
	maxp[0]=n;
	getrt(x,F,rt,sz[x]);
	dfa[rt]=F;
	del[rt]=1;
	x=rt;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(del[y])
			continue;
		solve(y,x);
	}
}
void dfs1(int x,int F){
	fa[x]=F;
	sz[x]=1;
	d[x]=d[F]+1;
	int maxn=0;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==F)
			continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[y]>maxn){
			maxn=sz[y];
			son[x]=y;
		}
	}
}
void dfs2(int x,int top){
	tp[x]=top;
	if(son[x])
		dfs2(son[x],top);
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa[x]||y==son[x])
			continue;
		dfs2(y,y);
	}
}
int lca(int x,int y){
	while(tp[x]!=tp[y]){
		if(d[tp[x]]<d[tp[y]])
			swap(x,y);
		x=fa[tp[x]];
	}
	if(d[x]>d[y])
		swap(x,y);
	return x;
}
inline int dis(int x,int y){
	return d[x]+d[y]-2*d[lca(x,y)];
}
int calc(int x,int k){
	int nw=x;
	int pre=0;
	int ans=0;
	while(nw){
		if(dis(nw,x)>k){
			pre=nw;
			nw=dfa[nw];
			continue;
		}
		int qwq=k-dis(nw,x);
		if(qwq>=0)
			ans+=st1.ask(st1.rt[nw],0,n-1,0,min(qwq,n-1));
		if(pre&&qwq>=0)
			ans-=st2.ask(st2.rt[pre],0,n-1,0,min(qwq,n-1));
		pre=nw;
		nw=dfa[nw];
	}
	return ans;
}
void cg(int x,int k){
	int nw=x;
	while(nw){
		st1.change(st1.rt[nw],0,n-1,dis(nw,x),k);
		if(dfa[nw])
			st2.change(st2.rt[nw],0,n-1,dis(dfa[nw],x),k);
		nw=dfa[nw];
	}
}
int p[N];
int main(){
	n=read();
	m=read();
	D=read();
	for(int i=1;i<=m;i++)
		p[read()]=1;
	for(int i=1;i<n;i++){
		int x,y;
		x=read();
		y=read();
		add(x,y);
		add(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	del[1]=1;
	for(int i=head[1];i;i=nex[i])
		solve(to[i],1);
	for(int i=1;i<=n;i++)
		if(p[i])
			cg(i,1);
	for(int i=1;i<=n;i++)
		if(calc(i,D)==m)
			ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：Arghariza (赞：2)

upd 2022/7/22：勘误，更正了 $dis$ 转移的错误。

以下有怪物的点记为关键点。

记录 $u$ 子树内关键点离 $u$ 最远和次远距离（两个关键点不在 $u$ 的同一个儿子的子树内），记为 $dp_{u,0/1}$。

考虑从叶子向根转移，显然有：

- $dp_{u,1}\gets dp_{u,0},dp_{u,0}\gets dp_{v,0}+1\ \ \ (dp_{v,0}+1>dp_{u,0})$
- $dp_{u,1}=\max\{dp_{u,1},dp_{v,0}+1\}\ \ \ \ \ \ \ (\text{otherwise})$

然后令 $dis_u$ 为 $u$ 的**子树外**关键点距离 $u$ 的最远距离，考虑从根到叶子转移：

- 如果 $dp_{u,0}$ 由 $dp_{v,0}$ 转移而来，说明 $u$ 子树内离 $u$ 最远的关键点在子树 $v$ 内，于是我们需要找次远的那个点，因为根据 $dp$ 的定义，次远点和最远点不在 $u$ 的同一个儿子的子树内，所以 $dis_v\gets \max\{dis_u+1,dp_{u,1}+1\}$。
- 如果 $dp_{u,0}$ 不由 $dp_{v,0}$ 转移而来，那么还是在 $u$ 子树内，$v$ 的最远距离就是它距离 $u$ 最远点的距离，$dis_v\gets \max\{dis_u+1,dp_{u,0}+1\}$。

然后最后遍历每一个节点，如果当前节点为根节点，只需要满足 $dp_{u,0}\le d$ 即可对答案贡献；如果当前节点不为根节点，需要满足 $dp_{u,0},dis_u\le d$。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxn = 1e5 + 100;
const int inf = 0x3f3f3f3f;
struct edge { int to, nxt; } e[maxn << 1];
int n, m, d, res, tot, dp[maxn][2], dis[maxn], head[maxn], vs[maxn];

void add_edge(int u, int v) {
    e[++tot] = (edge) { v, head[u] };
    head[u] = tot;
}

void dfs1(int u, int fa) {
    if (vs[u]) dp[u][0] = dp[u][1] = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        if (dp[v][0] + 1 > dp[u][0]) dp[u][1] = dp[u][0], dp[u][0] = dp[v][0] + 1;
        else dp[u][1] = max(dp[u][1], dp[v][0] + 1);
    }
}

void dfs2(int u, int fa) {
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        if (dp[u][0] == dp[v][0] + 1) dis[v] = max(dis[u] + 1, dp[u][1] + 1);
        else dis[v] = max(dis[u] + 1, dp[u][0] + 1);
        dfs2(v, u);
    }
}

int main() {
    memset(dp, -inf, sizeof dp);
    memset(dis, -inf, sizeof dis);
    n = read(), m = read(), d = read();
    for (int i = 1; i <= m; i++) vs[read()] = 1;
    for (int i = 1, u, v; i <= n - 1; i++) {
        u = read(), v = read();
        add_edge(u, v), add_edge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        if (i == 1 && dp[i][0] <= d) res++;
        else if (dp[i][0] <= d && dis[i] <= d) res++; 
    }
    write(res);
    return 0;
}
```

---

## 作者：Strelitzia (赞：2)

[]()

---

水？

想法比较简单，对于一个节点 $u$ 如果这个位置可能有邪恶之书，那么，

所有怪物离她的距离都在 $\operatorname d$ 以内。

也就是说，她子树内和子树外的的怪物的距离至少为 $d$。

我们定义 $dp_{u,0/1}$ 分别表示，在 $u$ 的子树内的离有怪物的最长路和次长路。

$dis$ 是子树以外的。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &u) {
	T f = 1;u = 0;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {u = u * 10 + s - '0';s = getchar();}
	u *= f;
}
template<typename T>void print(T u) {
	if(u < 0) putchar('-'),u = -u;
	if(u > 9) print(u / 10);
	putchar(u % 10 + '0');
}

const int maxn = 100005;

int nxt[maxn << 1],ver[maxn << 1],head[maxn],tot;
void addEdge(int u,int y) {
    nxt[++ tot] = head[u];ver[tot] = y;head[u] = tot;
}

int n,m,d,dp[maxn][2],pos[maxn],dis[maxn];

void dfs(int u,int fa) {
	for (int e = head[u] ; e ; e = nxt[e]) {
		int v = ver[e];
		if (v == fa) continue;
		dfs(v,u);
		if (dp[v][0] + 1 >= dp[u][0]) {
			dp[u][1] = dp[u][0];
			dp[u][0] = dp[v][0] + 1;
			pos[u] = v;
		}
		else if (dp[v][0] + 1 > dp[u][1]) dp[u][1] = dp[v][0] + 1;
	}
}

void dfs2(int u,int fa) {
	for (int e = head[u] ; e ; e = nxt[e]) {
		int v = ver[e];
		if (v == fa) continue;
		if (pos[u] == v) {
			dis[v] = max(dis[u] + 1,dp[u][1] + 1);
		}
		else dis[v] = max(dp[u][0] + 1,dis[u] + 1);
		dfs2(v,u);
	}
}

int main () {
	read(n);read(m);read(d);
	memset(dp,0xef,sizeof dp);
	memset(dis,0xef,sizeof dis);
	int u,v;
	for (int i = 1 ; i <= m ; ++ i) {
		read(u);
		dp[u][0] = dp[u][1] = 0;
	}
	for (int i = 1 ; i < n ; ++ i) {
		read(u);read(v);
		addEdge(u,v);addEdge(v,u);
	}
	dfs(1,0);
	dfs2(1,0);
	int ans = 0;
	for (int i = 1 ; i <= n ; ++ i) {
		if (i == 1) {
			if (dp[i][0] <= d) ans ++;
		}
		else if (dp[i][0] <= d && dis[i] <= d) {
			ans ++;
		}
	}
	print(ans);
	return 0;
}
```

---

## 作者：qfpjm (赞：1)

# 前置知识

- 树的直径。

# 题解

## 先给出结论：

- 与**距离最远的两只鬼**的距离小于 $d$ 的节点都有可能是魔法书所在的点。

## 证明：

- 使用反证法证明。

- 假设有一个节点 $W$，与**距离最远的两只鬼** $X,Y$ 的距离小于 $d$。

- 假设有另外一只鬼 $Z$，使得 **$W$ 距离它的距离大于 $d$** 且 **$Z$ 离 $X$ 更近一些**。

- 那么 **$W$ 到 $Z$ 的距离**是大于 **$Z$ 到 $X$ 的距离**的。

- 分两种大情况考虑：

### 1. $W$ 在 $X$ 到 $Y$ 的路径上：

- 因为 **$W$ 到 $Y$ 的距离不变**，所以 **$Z$ 和 $Y$ 才是距离最远的两只鬼**。

- 显然，与**距离最远的两只鬼**是 $X,Y$ 矛盾。

### 2. $W$ 不在 $X$ 到 $Y$ 的路径上：

- 分两种小情况：

#### 1. $W,Z$ 的路径与 $A,B$ 的路径有交点：

- 假设两条路径中有一个交点 $K$。

- 因为 **$W$ 到 $Z$ 的距离**大于 **$Z$ 到 $X$ 的距离**，所以 **$K$ 到 $Z$ 的距离**是大于 **$K$ 到 $X$ 的距离**的。

- 又因为 **$K$ 到 $Y$ 的距离**不变，所以 **$Z$ 和 $Y$ 才是距离最远的两只鬼**。

- 显然，与**距离最远的两只鬼**是 $X,Y$ 矛盾。

#### 2. $W,Z$ 的路径与 $A,B$ 的路径没有交点：

- 假设有 $U,V$ **分别**连接着 $X,Y$ 和 $W,Y$ 的路径。

- 因为 **$W$ 到 $Z$ 的距离**大于 **$Z$ 到 $X$ 的距离**，所以 **$V$ 到 $Y$ 的距离**是大于 **$V$ 到 $X$ 的距离**的。

- 又因为 **$V$ 到 $Y$ 的距离**不变，所以 **$X$ 和 $Z$ 才是距离最远的两只鬼**。

- 显然，与**距离最远的两只鬼**是 $X,Y$ 矛盾。
 
## 实现过程

- 首先，找到距离最远的两只鬼，再一一枚举每一个点，判断距离即可。

- 找最远的两只鬼做法与树的直径相同。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, d, evil[100005];
int tot, head[100005], to[200005], nxt[200005];
int dis1[100005], dis2[100005];

void add(int x, int y)
{
	nxt[++ tot] = head[x];
	head[x] = tot;
	to[tot] = y;
}

void dfs1(int u, int fa, int dep)
{
	dis1[u] = dep;
	for (int i = head[u] ; i ; i = nxt[i])
	{
		int v = to[i];
		if (v != fa)
		{
			dfs1(v, u, dep + 1);
		}
	}
}

void dfs2(int u, int fa, int dep)
{
	dis2[u] = dep;
	for (int i = head[u] ; i ; i = nxt[i])
	{
		int v = to[i];
		if (v != fa)
		{
			dfs2(v, u, dep + 1);
		}
	}
}

int main()
{
	cin >> n >> m >> d;
	for (int i = 1 ; i <= m ; i ++)
	{
		cin >> evil[i];
	}
	for (int i = 1 ; i < n ; i ++)
	{
		int x, y;
		cin >> x >> y;
		add(x, y);
		add(y, x);
	}
	dfs1(1, 0, 0);
	int tmp = 0;
	for (int i = 1 ; i <= m ; i ++)
	{
		if (dis1[evil[i]] > dis1[tmp])
		{
			tmp = evil[i];
		}
	}
	dfs1(tmp, 0, 0);
	tmp = 0;
	for (int i = 1 ; i <= m ; i ++)
	{
		if (dis1[evil[i]] > dis1[tmp])
		{
			tmp = evil[i];
		}
	}
	dfs2(tmp, 0, 0);
	int ans = 0;
	for (int i = 1 ; i <= n ; i ++)
	{
		if (dis1[i] <= d && dis2[i] <= d)
		{
			ans ++;
		}
	}
	cout << ans;
}
```


---

## 作者：出言不逊王子 (赞：0)

你管这叫 `*2000` 啊。我做的时候以为得 `*2500` 呢。

既然魔法书的要求是**到所有妖魔鬼怪的距离都满足 $\le d$ 这一条件**，那么我们可以转换成到妖魔鬼怪的距离**最大值满足 $\le d$ 这一条件**。

考虑树形 DP。设 $f_i$ 表示 $i$ 到其子树内鬼的距离最大值，同时设 $g_i$ 表示 $i$ 到其子树外鬼的距离最大值。那么当 $f_i\le d$ 且 $g_i\le d$ 时，这个点就是一个合规的点。

我们以 $1$ 为根向下搜索，可以在一遍 `dfs` 内算出 $f$ 数组。

然后求完了 $f$ 数组，用换根的方式求出 $g$ 数组。

对于一个点我们现在有了它的父亲的 $f$，我们思考怎么利用这个来转移 $g$。

那么在转移 $g$ 时，如果当前父亲的 $f$ **不是**由儿子的 $f$ 转移而来——也就是说，距离父亲最远的鬼在**另一个**儿子的子树里——那好办，儿子的 $g$ 就是父亲到这个鬼的距离，也就是 $f$ 再加上 $1$，作为儿子和父亲的通勤成本。

我们发现，如果当前父亲的 $f$ 是由儿子的 $f$ 转移而来——也就是说，距离父亲最远的鬼在儿子的子树里，那我们就把儿子的 $g$ 设为父亲的 $g$ 与距离父亲**第二远**的鬼的最大值——再加上 $1$。

可是如果距离父亲**最远和第二远**的点都在当前子树呢？

那么在更新到第二远节点时，距“第二远节点”最远的点是“最远节点”，所以当更新到这个子树时“最远节点”就一马当先把“第二远节点”的贡献给覆盖了。

所以我们在求 $f$ 的时候还得顺便把每个点在子树内**第二远**的鬼的距离给求出来。

具体实现看代码。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=200001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
struct edge{
	int v,nx;
}e[N<<1];
int n,hd[N],totm,m,d,b[N],dis0[N][2],dis1[N];//dis0表示子树内最/次，dis1表示子树外
void add(int u,int v){
	e[++totm].v=v;e[totm].nx=hd[u];
	hd[u]=totm;
}
void dfs(int now,int fa){
	if(b[now]) dis0[now][0]=dis0[now][1]=0;
	for(int i=hd[now];i;i=e[i].nx){
		int v=e[i].v;if(v==fa) continue;
		dfs(v,now);
		if(dis0[v][0]+1>dis0[now][0]) dis0[now][1]=dis0[now][0],dis0[now][0]=dis0[v][0]+1;//观察这里，如果这时候遍历到那个次大点，那么对于此时的次大点而言，仅仅会更新最大值，因为此时的次大值来自于其他子树（如果有的话，没的话就是负无穷）
      //到了上边，因为第一个儿子的dis0[0]很大，所以父亲还是会这么更新，等于说它里边这个就——没用啦
      //也对哈，如果比你更远的那个鬼都没用了，那你这个鬼还有啥用 
		else dis0[now][1]=max(dis0[v][0]+1,dis0[now][1]);
	}
}
void dfs2(int now,int fa){
	for(int i=hd[now];i;i=e[i].nx){
		int v=e[i].v;if(v==fa) continue;
		if(dis0[now][0]==dis0[v][0]+1) dis1[v]=max(dis1[now]+1,dis0[now][1]+1);//最大值在V子树内
		else dis1[v]=max(dis1[now]+1,dis0[now][0]+1); 
		//那么次大值就是：要么在U那里，要么就是次大值，因为次大值不在子树内
		//那如果次大值也在V子树内呢
		//那么这说明一点，还有第三大的值？反正要捞出来一个
		//那如果都没有呢……都在V子树内？
		//思考V与U的关系，最大值在V的那棵子树上，对吧
		//如果真这样，那么遍历到那个点的时候就会被更新掉了啊 
		dfs2(v,now);
	}
}
int main(){
	ms(dis0,0x80);//初始是负无穷
	ms(dis1,0x80); 
	n=read(),m=read(),d=read();fs(i,1,m,1) b[read()]=1;
	fs(i,1,n-1,1){
		int u=read(),v=read();
		add(u,v);add(v,u); 
	}
	dfs(1,0);
	dfs2(1,0); 
//	fs(i,1,n,1) cout<<dis0[i][0]<<' '<<dis1[i]<<'\n'; 
	int res=0;
	fs(i,1,n,1) if(dis1[i]<=d&&dis0[i][0]<=d) res++;
	cout<<res;
	return 0;
}
```

---

## 作者：hgzxwzf (赞：0)

## 解题思路：
有意思的换根树形 DP。

显然，对于一个点，我们只需要考虑它离怪物最远的距离是否小于等于 $d$。

那就定义 $dp_i$ 为 $i$ 离怪物的距离。

换根 DP 第一步，以 $1$ 号点为根，求出每个点离它的子树上的怪物的最远距离。

转移方程：$dp_i=\max(dp_i,dp_j+1)$，其中 $j$ 为 $i$ 的儿子。

换根 DP 第二步，考虑一个点子树之外的怪物：

转移方程：$dp_j=max(dp_j,dp_i+1)$，其中 $j$ 为 $i$ 的儿子。

还没完，（~~毕竟是 CodeForces 2000~~）第二个转移方程是有问题的，因为如果第一步中 $dp_j$ 转移到了 $dp_i$，第二步中 $dp_i$ 反过来转移到了 $dp_j$，那么不就变成了 $dp_j=dp_j+2$，肯定是不可以的。

所以第二步转移时要保证不出现上述的情况，所以我们还要记录一个次大值，如果最大值不能转移了，那肯定让次大值顶替它。

所以 $dp_{i,0}$ 和 $dp_{i,1}$ 分别表示 $i$ 离怪物的最远距离和次远距离。

第一步转移变为：

$\begin{cases}dp_{i,1}=dp_{i,0},dp_{i,0}=dp_{j,0}+1&dp_{j,0}+1>=dp_{i,0}\\dp_{i,1}=dp_{j,0}+1&dp_{i,0}>dp_{j,0}+1>dp_{i,1}\end{cases}$

第二步状态转移方程变为：

$\begin{cases}dp_{j,1}=dp_{j,0},dp_{j,0}=dp_{i,0}+1&dp_{i,0}\not=dp_{j,0}+1,dp_{i,0}+1>=dp_{j,0}\\dp_{j,1}=dp_{i,0}+1&dp_{i,0}\not=dp_{j,0}+1,dp_{j,0}>dp_{i,0}+1>dp_{j,1}\\dp_{j,1}=dp_{j,0},dp_{j,0}=dp_{i,1}+1&dp_{i,0}=dp_{j,0}+1,dp_{i,1}+1>=dp_{j,0}\\dp_{j,1}=dp_{i,1}+1&dp_{i,0}=dp_{j,0}+1,dp_{j,0}>dp_{i,1}+1>dp_{j,1}\end{cases}$。

因为次大并非严格次大，所以如果一个点有两个最大，那么就会有一个记录在次大中，转移时就相当于用了最大。

最后把满足离怪物的最大距离小于等于 $d$ 的点的个数求出来就可以了。

## 代码：
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define tree(x) for(auto nt:e[x])
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x++)
using namespace std;
const int N=100005;
vector<int>e[N];
bool has_mon[N];
int n,m,d;
int dp[N][2];

inline void update(int cur,int t)
{
	if(t>=dp[cur][0])
	{
		dp[cur][1]=dp[cur][0];
		dp[cur][0]=t;
	}
	else if(t>dp[cur][1]) dp[cur][1]=t;
}

void dfs(int cur,int fa)
{
	if(has_mon[cur]) dp[cur][0]=0;
	tree(cur)
	{
		if(nt==fa) continue;
		dfs(nt,cur);
		update(cur,dp[nt][0]+1);
//		update(cur,dp[nt][1]+1);
	}
}

void dfs2(int cur,int fa)
{
	tree(cur)
	{
		if(nt==fa) continue;
		if(dp[nt][0]+1!=dp[cur][0]) update(nt,dp[cur][0]+1);
		else update(nt,dp[cur][1]+1);
		dfs2(nt,cur);
	}
}

int main()
{
	memset(dp,0xcf,sizeof(dp));
	scanf("%d%d%d",&n,&m,&d);
	rep(i,1,m)
	{
		int pos;
		scanf("%d",&pos);
		has_mon[pos]=1;
	}
	rep(i,1,n-1)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,1);
	dfs2(1,1);
	int ans=0;
	rep(i,1,n) if(dp[i][0]<=d) ans++;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16014465.html)

目前相同思路的题解定义都有点问题。

# 题目大意

有一棵树有 $n$ 个节点，其中有 $m$ 个节点发现了怪物。已知树上有一本魔法书，魔法书可以让到其距离小于等于 $d$ 的点出现怪物，求魔法书所在点有几种可能。

输入第一行为 $3$ 个正整数 $n,m,d$。

第二行 $m$ 个整数，以空格间隔，表明这些点出现了怪物。

接下来 $n−1$行，每行两个整数，描述树上的一条边。

输出一行一个整数，魔法书可能在的位置的方案数。

# 题目分析

令 $dp_{i,1}$ 表示 $i$ 与以 $i$ 为根的子树内有怪物的点的最大距离，$dp_{i,2}$ 表示 $i$ 与以 $i$ 为根的子树内有怪物的点的次大距离，**且这个次远节点与最远节点不在同一分支**，$dis_i$ 表示 $i$ 到其子树外的最远怪兽的距离。

首先我们需要求出 $dp_{i,1}$ 和 $dp_{i,2}$。这一步非常显然，互相迭代更新即可，若最大值更新了，当前最大值变为次大值，当前最大值变为更大值。

重点在于求出 $dis_i$，这里比较难理解。
首先当 $dp_{v,1}+1=dp_{i,1}(v\in son\{i\})$ 时，$v$ 和距离点 $i$ 最远的那个怪兽节点在一条链上，$dis_{v}=\max\{dis_i+1,dp_{i,2}+1\}$，因为儿子节点 $v$ 距离子树外面最大距离为父亲节点距离子树外面最大距离 $+1$ 或距离父亲节点次远的节点所在的子树中（可能是祖先节点或是父亲节点的其他子树中），为什么不是 $dp_{i,1}+1$ 呢，因为此时距离点 $i$ 最远的那个怪兽节点已经是点 $v$ 的子孙了，不再满足定义了。而如果最远怪兽节点和次远怪兽节点都是 $v$ 的子孙呢？这与定义相悖。很多题解都疏忽了这一点，但大概是说明的问题。

否则不难推，跟上面是一模一样的。

# 代码


代码中有关键字放不上来，请前往博客园观看。

---

## 作者：_Diu_ (赞：0)

[Luogu 传送门](https://www.luogu.com.cn/problem/CF337D)

[CF 传送门](https://codeforces.com/contest/337/problem/D)

## 题目大意

一棵树，有 $m$ 个特殊点，求树上有多少个点满足这个点到任意特殊点的距离 $\le d$。

## 思路

我们容易想到，如果我们确定一个根节点，那么对于树上某一个节点 $u$，特殊点（怪兽）有可能在子树 $u$ 内，也有可能在子树 $u$ 外。（~~这不废话~~）

而在子树 $u$ 内的特殊点距离最大值很好求（深搜），主要是如何求子树 $u$ 之外的。

我们发现子树 $u$ 之外的特殊点到子树 $u$ 内，一定要经过 $u$ 的父亲 $fa$，我们可以考虑再进行一次 `dfs`。

我们假设 $f_u$ 表示子树 $u$ 内特殊点到点 $u$ 的距离最大值， $s_u$ 表示次大值（如果有两个相同距离做最大值，那么这个值同时也是次大值）。

这样，我们可以轻松通过一遍深搜求出每个点的 $f_u$ 和 $s_u$。

```cpp
void dfs(int u,int fa){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		dfs(v,u);
		int mv=fmx[v]?fmx[v]+1:mst[v];
		if(mst[v])mv=max(mv,1);
		if(fmx[u]<mv)smx[u]=fmx[u],fmx[u]=mv;
		else if(smx[u]<mv)smx[u]=mv;
	}
//	printf("Dfs1:%d %d %d\n",u,fmx[u],smx[u]);
}
```

（`mst` 表示是否是特殊点）

然后我们假设已经知道 $u$ 子树外的特殊点到点 $u$ 的最大距离 $mx$，考虑如何求到 $u$ 的儿子 $v$。

我们发现原来的特殊点距离会增加 $1$，然后会把 $v$ 的兄弟姐妹们的子树内的特殊点给算上。

如果 $f_u$ 是由子树 $v$ 转移过来，那么从 $s_u$ 下传到 $v$。

否则的话从 $f_u$ 更新过来。

```cpp
void dfs2(int u,int fa,int mx){
//	printf("Dfs2:%d %d %d\n",u,fa,mx);
	if(max(mx,fmx[u])<=d)++ans;
	mx=mx?mx+1:mst[u];
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		int mv=fmx[v]?fmx[v]+1:mst[v];
		if(mv==fmx[u])dfs2(v,u,max(mx,smx[u]?smx[u]+1:mst[u]));
		else dfs2(v,u,max(mx,fmx[u]?fmx[u]+1:mst[u]));
	}
}
```

注意要特判如果一个子树内（外）没有特殊点的情况

## code

~~不~~完整的代码：

~~答案的输出被我喂狗了。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,d,mst[N],fmx[N],smx[N],ans;
vector<int> g[N];
void dfs(int u,int fa){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		dfs(v,u);
		int mv=fmx[v]?fmx[v]+1:mst[v];
		if(mst[v])mv=max(mv,1);
		if(fmx[u]<mv)smx[u]=fmx[u],fmx[u]=mv;
		else if(smx[u]<mv)smx[u]=mv;
	}
//	printf("Dfs1:%d %d %d\n",u,fmx[u],smx[u]);
}
void dfs2(int u,int fa,int mx){
//	printf("Dfs2:%d %d %d\n",u,fa,mx);
	if(max(mx,fmx[u])<=d)++ans;
	mx=mx?mx+1:mst[u];
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		int mv=fmx[v]?fmx[v]+1:mst[v];
		if(mv==fmx[u])dfs2(v,u,max(mx,smx[u]?smx[u]+1:mst[u]));
		else dfs2(v,u,max(mx,fmx[u]?fmx[u]+1:mst[u]));
	}
}
signed main(){
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1,x;i<=m;i++)scanf("%d",&x),mst[x]=1;
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	dfs2(1,0,0);
}
```

完结撒花

---

## 作者：Yukinoshita_Yukino (赞：0)

题意:树上有 $m$ 个怪物，求最远怪物不大于 $d$ 的节点数。

树上问题分情况讨论，某个节点最远的怪物有可能在它的子树外或者子树内。

子树内的最远怪物可以通过一次 dfs 求出，但是子树外的最远怪物怎么求呢？

其实也可以分情况讨论，一种情况是这个节点子树外的最远怪物是它父亲子树外的最远怪物，一种情况是它父亲子树内的最远怪物，一种情况是它父亲子树内的次远怪物。

是不是很乱 qwq ，不如画张图感受一下。

我们设现在要计算 5 号节点的最远怪物的距离，红色节点代表这个节点有怪物,以下是三种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/exlk30so.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/k5dqa5p4.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/7jms9k3w.png)

于是在第一次 dfs 中顺便求一下子树内次远怪物，在第二次 dfs 中讨论一下这三种情况就能求出每个节点的子树外最远的怪物了。

统计答案时只需保证答案节点子树外和子树内最大的怪物距离均不大于 $d$ 就行了 qwq 。

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=300010;
int n,m,d,cnt=0,first[maxn],have[maxn];
struct edge{
	int to;
	int next;
}e[maxn];
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].next=first[u];
	first[u]=cnt;
}
int dp[maxn][3],dis[maxn];
void dfs(int fa,int x)
{
	if(have[x]==1) dp[x][0]=dp[x][1]=0;
	for(int i=first[x];i;i=e[i].next)
	{
		if(e[i].to==fa) continue ;
		dfs(x,e[i].to);
		if(dp[e[i].to][0]+1>dp[x][0])
		{
			dp[x][1]=dp[x][0];
			dp[x][0]=dp[e[i].to][0]+1;
		}
		else dp[x][1]=max(dp[x][1],dp[e[i].to][0]+1);
	}
	return ;
}
void check(int fa,int x)
{
	for(int i=first[x];i;i=e[i].next)
	{
		if(e[i].to==fa) continue ;
		if(dp[e[i].to][0]==dp[x][0]-1) dis[e[i].to]=max(dis[x],dp[x][1])+1;
		else dis[e[i].to]=max(dis[x],dp[x][0])+1;
		check(x,e[i].to);
	}
	return ;
}
int main()
{
	memset(dp,128,sizeof dp);
	memset(dis,128,sizeof dis);
	cin>>n>>m>>d;
	for(int i=1;i<=m;i++)
	{
		int qwq;
		cin>>qwq;
		have[qwq]=1;
	}
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	dfs(0,1);
	check(0,1);
	int ans=0;
	if(dp[1][0]<=d&&dp[1][1]<=d) ans++;
	for(int i=2;i<=n;i++)
	{
		if(dp[i][0]<=d&&dis[i]<=d) ans++;
	}
	cout<<ans;
	return 0;
 } 

```



---

