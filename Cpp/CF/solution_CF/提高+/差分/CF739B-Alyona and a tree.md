# Alyona and a tree

## 题目描述

Alyona有一棵有 $n$ 个节点的树。这棵树的根节点是 $1$。在每个节点里，Alyona写了一个正整数，在节点 $i$ 她写了正整数 $a_i$ 。另外，她在这棵树上的每条边上写了一个正整数（不同边上可能有不同的数）。

让我们定义 $dist(v,u)$ 作为从 $v$ 到 $u$ 的简单路径上的边权和。

当且仅当 $u$ 在 $v$ 的子树中并且 $dist(v,u)\leq a_u$，顶点 $v$ 控制顶点 $u(v\neq u)$ 。

Alyona想在某些顶点定居。为了做到这件事，她想知道在每个节点 $v$ 能控制几个节点。

## 说明/提示

在样例中，节点 $1$ 控制了节点 $3$ ，节点 $3$ 控制节点 $5$ （注意，这并不代表节点 $1$ 控制了节点 $5$ ）

Translated by @lolte

## 样例 #1

### 输入

```
5
2 5 1 4 6
1 7
1 1
3 5
3 6
```

### 输出

```
1 0 1 0 0
```

## 样例 #2

### 输入

```
5
9 7 8 6 5
1 1
2 1
3 1
4 1
```

### 输出

```
4 3 2 1 0
```

# 题解

## 作者：くろねこ (赞：26)

有道是 
```cpp
算法就是优化的暴力
``` 
那么我们先从暴力开始说起(真的是最裸的暴力qwq).

首先这是棵树,很显然采用链式前向星建边.然后我们观察题面
![qwq](https://s2.ax1x.com/2019/02/10/kaS9xJ.png)
显然,我们需要知道dis[u][v]的值,那么,怎么求他们的路径呢?

学了图论的应该都知道Dijkstra的优秀,那我们就采用Dijkstra吧!

跑一遍最短路,由于Dijkstra求的是单源最短路,所以我们得到了从根节点1到每个子节点的距离.那么问题来了

**tm我们要的是dis[u][v] 你tm求个dis[1][k]有个屁用啊?!**
![qwq](https://s2.ax1x.com/2019/02/10/kaSlqI.png)

稍安勿躁,我们先看一棵简单的树
![qwq](https://s2.ax1x.com/2019/02/10/kaSEa6.png)
如果我们现在已知根节点到任意节点的单源最短路,想求任意子节点和父节点的距离怎么办?
就这么办!
![qwq](https://s2.ax1x.com/2019/02/10/kaSVIK.png)

红色的是根节点,绿色是父节点,蓝色是子节点.
不难发现,dis[blue][green] = dis[red][blue] - dis[red][green]!
那么我们的单源最短路有用了!
---接下来呢?
当然是找每个点控制的点啦!
---怎么找呢?
开个father数组把每个点的直接父亲记录下来,链式遍历求每个点控制的个数啊!
就像这样
```
inline void isFa(int now,int son)
{
    rg int f = fa[now];
    if (!f) return;
    if (dis[son] - dis[f] <= pos[son])
    {
        ++ans[f];
        isFa(f,son);
    }
}

```
是不是很简略啊qwq
那么把上述部分拼凑一下,我们的代码就出炉啦
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define rg register
#define LL long long
const int maxn = 233333;
template <typename qwq> inline void read(qwq & x)
{
    x = 0;
    rg int f = 1;
    rg char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    x *= f;
}
template <typename qaq> inline void print(qaq x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
struct edge
{
    int v,w,next;
}e[maxn];
int tot,head[maxn];
inline void add(int x,int y,int z)
{
    ++tot;
    e[tot].v = y;
    e[tot].w = z;
    e[tot].next = head[x];
    head[x] = tot;
}
int dis[maxn],ans[maxn],fa[maxn],pos[maxn];;
bool vis[maxn];
priority_queue <int,vector<int>,greater<int> > heap;
inline void dijkstra()
{
    memset(dis,0x3f,sizeof dis);
    dis[1] = 0;
//	vis[1] = 1;
    heap.push(1);
    while (!heap.empty())
    {
        rg int x = heap.top();
        heap.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (rg int i = head[x];i;i = e[i].next)
        {
            rg int v = e[i].v,w = e[i].w;
            if (dis[x] + e[i].w < dis[v])
            {
                dis[v] = dis[x] + e[i].w;
                heap.push(v);
            }
        }
    }
}
inline void isFa(int now,int son)
{
    rg int f = fa[now];
    if (!f) return;
    if (dis[son] - dis[f] <= pos[son])
    {
        ++ans[f];
        isFa(f,son);
    }
}
inline void dfs(int x,int fa)
{
    for (rg int i = head[x];i;i = e[i].next)
    {
        rg int v = e[i].v;
//		printf("Test x:%d,v:%d,fa:%d\n",x,v,fa);
//		system("pause");
        if (v == fa) continue;
        dfs(v,x); 
        if (dis[v] - dis[x] <= pos[v])
        {
            ++ans[x];
            isFa(x,v);
        }
    }
}
int n,m,x,y,z;
int main()
{
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
    read(n);
    for (rg int i = 1;i <= n;++i) read(pos[i]);
    for (rg int i = 2;i <= n;++i)
    {
        read(x),read(y);
        add(x,i,y);
        fa[i] = x;
    }
    fa[1] = 0;
    dijkstra();
    dfs(1,0);
    for (rg int i = 1;i <= n;++i)
    {
        print(ans[i]),putchar(' ');
    }
}
```
然后开心的submit
![qwq](https://s2.ax1x.com/2019/02/10/kaSirR.png)
![qwq](https://s2.ax1x.com/2019/02/10/kaSgWF.png)


怎么办一定是数据太强了

我们考虑优化一下吧...

首先!**根本不用Dijkstra!** 我们这是棵树,为什么不在dfs的时候把父亲节点的信息拿过来用呢?!

直接边跑dfs边求dis不就的了吗qwq

然后这个遍历求控制的节点数,万一我一棵树都能被根节点控制我岂不是要遍历1mol次这棵树?!

让我们思考一下,优化这种遍历次数一般用什么方法呢emm..

对了!二分和倍增嘛!

由于我们经常用二分,那么我们考虑一下二分算法.

首先从子节点出发,我们需要找到dis[1][son],然后除以二,这个点就是mid了,l是子节点,r是根节点(1).好的,到son的距离大约为dis[1][son] / 2的节点是...不慌我遍历一次不就知道了吗qwq.

等等,遍历.....

~~好的我们还是考虑倍增算法吧~~

倍增其实挺好实现,由于我们是始终只看当前点的father节点,所以找到最后肯定是根节点,那么这样遍历出来其实就是个长长的边而已(自己画图理解我懒得画了qwq)

从子节点出发,由p = 1(倍增倍数)开始倍增,找到一个点,若当前点可以实现,则更新当前节点并继续向上倍增,不行的话则缩小为p / 2,由更新后的节点继续倍增.时间复杂度类似于二分.

好了最后能优化的也就是一个一个加太慢了.那么有没有一款能实现区间修改的数据结构呢?

对,线段树!

我们考虑在原来的基础上套线段树并进行区间更新.

等等,我们这个树上的节点编号好像并不是连续的...

~~好的我们想一下其他办法吧~~

想想我们是不是学过差分数组了,对,我们就用树上差分实现吧!

本题所用的树上差分其实是简化版的,因为我们所有的节点都是在根节点(1)到son节点这条边上,不必再费心思求什么两点的LCA再进行差分.

举个栗子
![qwq](https://s2.ax1x.com/2019/02/10/kaSFq1.png)

比如我们原来所有节点都代表0,我们想在从blue到red的地方+ 1.

那么我们只用在blue这个点上+ 1,在green这个点- 1,从blue到red求一次前缀和,用前缀和代表每个节点的信息即可.

拿出草稿算一下,是不是刚好+ 1呀qwq

那么这里也解决了.

好了,上最终代码!
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define rg register
#define LL long long
#define __space putchar(' ')
#define __endl putchar('\n')
template <typename qwq> inline void read(qwq & x)
{
    x = 0;
    rg int f = 1;
    rg char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    x *= f;
}
template <typename qaq> inline void print(qaq x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
struct edge
{
    int v,w,next;
}e[233333 << 1];
int tot,head[233333 << 1],ans[233333],a[233333],bz[233333][19];
//=================================================================
inline void add(int x,int y,int z)
{
    ++tot;
    e[tot].v = y;
    e[tot].w = z;
    e[tot].next = head[x];
    head[x] = tot;
}
LL dep[233333];
inline void dfs(int x,int fa,int w)
{
    bz[x][0] = fa;
    dep[x] = dep[fa] + w;
    for (rg int i = 1;i <= 18;++i)
    {
        bz[x][i] = bz[bz[x][i - 1]][i - 1];
    }
    for (rg int i = head[x];i;i = e[i].next)
    {
        rg int v = e[i].v,ww = e[i].w;
        if (v == fa) continue;
        dfs(v,x,ww);
        rg int pp = pos[v];
        if (ww > pp) continue;
        //=================================================================
        rg int p = 1;
        while(p && v)
        {
            if (dep[v] - dep[bz[v][p]] <= pp)
            {
                pp -= dep[v] - dep[bz[v][p]];
                v = bz[v][p];
                p <<= 1;
            }
            else p >>= 1;
        }
        if (dep[v] - dep[bz[v][0]] <= pp) v = bz[v][0];
        --ans[bz[v][0]],++ans[bz[e[i].v][0]];
        //=================================================================
    }
    ans[fa] += ans[x];
}
//=================================================================
int n,m,x,y,z;
int main()
{
    read(n);
    for (rg int i = 1;i <= n;++i)
    {
    	read(a[i]);
	}
    for (rg int i = 2;i <= n;++i)
    {
        read(x),read(y);
        add(x,i,y);
        add(i,x,y);
    }
    dfs(1,0,0);
    for (rg int i = 1;i <= n;++i)
    {
        print(ans[i]),putchar(' ');
    }
}
```
Submit...

![qwq](https://s2.ax1x.com/2019/02/10/kaSAVx.png)

![qwq](https://s2.ax1x.com/2019/02/10/kaS5e1.png)
AC了qwq

---

## 作者：RedreamMer (赞：14)

### [CF739B](https://www.luogu.com.cn/problem/CF739B)

算法：树上差分+倍增

### Meaning

给你一棵树，即 $n-1$ 条边和边权和点权，问你对于每个 $u(1 \leq u \leq n)$ ，所有在 $u$ 的**子树**中的 $v$ ，距离它的距离不超过 $a_v$ 的节点有多少个？

### Solve

反过来思考，每个节点 $v$ 作用于所有它的祖宗节点，所以我们可以暴力 $O(N^2)$ 做这道题，即 dfs 遍历到每个节点，再从一个一个祖宗依次往上找，进行修改答案，但是对于 $2*10^5$ 的数据显然过不去。

那就用倍增，存储每个节点的 $2^p(0 \leq p \leq log_2(N) )$ 的祖宗，因为题目中有：

> 第 $i$ 行包含整数 $p_i,w_i$ $(1\leq p_i \leq n,1 \leq w \leq 10^9)$

我们注意到每条边的边权是正数，所以必然有：

$$dist(fathers[u],v)>dist(u,v)(u \neq root)$$

即每条从 $v$ 到 $v$ 的祖宗的路径的边权和一定是严格单调递增的，这样做就可以优化了往上找这个操作，因为只要找到第一个祖宗是不满足题目的条件，那上面的就一定更不满足了，下面的肯定都满足，时间复杂度 $O(N \log_2 N)$ ，可以过。

但是修改答案就没法一个一个修改了，于是我们又搬出新的存储方式————树上差分，思路很简单，和普通差分差不多，这里就不多解释。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long//可能会炸int
const int N=2e5+10;

int a,s1[N],head[N],top,fa[N][20],dis[N],x,y,z,ans[N];
struct node {
	int last,to,dis;
} s[N];

inline void add(int l1,int l2,int l3) {
	s[++top].last=head[l1];
	s[top].to=l2;
	s[top].dis=l3;
	head[l1]=top;
}
inline void dfs(int n) {
	for(int i=1; i<=19; i++) fa[n][i]=fa[fa[n][i-1]][i-1];//维护倍增数组
	int now=n;
//	cout<<n<<endl;
	for(int i=19; i>=0; i--) {
		if(fa[now][i]&&dis[n]-dis[fa[now][i]]<=s1[n]) now=fa[now][i];//寻找第一个不满足条件的祖宗
//		cout<<i<<' '<<now<<' '<<fa[now][i]<<' '<<dis[fa[now][i]]<<endl;
	}
//	cout<<n<<' '<<now<<endl;
	ans[fa[now][0]]--;//进行差分
	ans[fa[n][0]]++;
	for(int i=head[n]; i; i=s[i].last) {
		dis[s[i].to]=dis[n]+s[i].dis;
		dfs(s[i].to);
		ans[n]+=ans[s[i].to];//维护答案
	}
}
signed main() {
//	freopen("in1.in","r",stdin);
	scanf("%lld",&a);
	for(int i=1; i<=a; i++) scanf("%lld",&s1[i]);
	for(int i=2; i<=a; i++) {
		scanf("%lld%lld",&fa[i][0],&x);
		add(fa[i][0],i,x);
	}
//	for(int i=1;i<=a;i++) cout<<i<<' '<<fa[i][0]<<endl;
//	cout<<fa[2][0]<<endl;
	dfs(1);
	for(int i=1; i<=a; i++) printf("%lld ",ans[i]);
	return 0;
}

```

### [$\color{blue}\text{My Blog}$](https://www.luogu.com.cn/blog/184549/)

---

## 作者：GuuGuu (赞：5)

# Foreword

发一篇没人写的 cdq 分治的题解。

~~我也不知道为什么这个思路这么清奇，总之看到偏序关系就想到 cdq 分治了。~~

# Problem

题意也说得很清楚。

给定一棵树，点权为 $a_i$ ，边有边权，对每一个点求这个点子树中距离它不超过 $a_i$ 的点的个数。

# Solution

首先看到最后一句话可以直接抽象成满足： $dep_j-dep_i\le a_j$ ，其中 $dep$ 代表这个点的深度。

那么我们又发现其实第一个条件就等价于另外一个常见的柿子，学过树剖的同学应该能很快反应过来，就是如果我们给原树打上 dfs 序（记为 $dfn$），再处理出每个点的子树大小记为 $siz$ 。

那么这个条件可以表示成：$dfn_i<dfn_j\le dfn_i+siz_i$

稍微变形一下两个柿子：

$dep_j-a_j\le dep_i$ 

$dfn_i<dfn_j \& dfn_j\le dfn_i+siz_i$

第一个作为二维偏序的第一维，第二个可以转化为差分然后作为二维偏序的第二维，直接 sort 然后 cdq分治 即可解决。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
#define ll long long
const int N=2e5+5,INF=1e9+7;
struct Que{
	ll d1;int d2,id;
	Que(ll d1=0,int d2=0,int id=0):d1(d1),d2(d2),id(id){}
}Q[N*3],tmp[N*3];
int head[N],to[N<<1],nex[N<<1],idx;
int n,m,dfn[N],siz[N],cnt,DFN;
ll dep[N],Ans[N],a[N],val[N<<1];
void dfs(int x,int f){
	siz[x]=1;dfn[x]=++DFN;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==f) continue;
		dep[y]=dep[x]+val[i];
		dfs(y,x); 
		siz[x]+=siz[y];
	}
	Q[++cnt]=Que(dep[x]-a[x],dfn[x],0);
	Q[++cnt]=Que(dep[x],dfn[x],-x);
	Q[++cnt]=Que(dep[x],dfn[x]+siz[x]-1,x);
	return ;
} 

inline void add(int u,int v,ll w){nex[++idx]=head[u];to[idx]=v;head[u]=idx;val[idx]=w;}
inline bool cmp1(const Que &x,const Que &y){
	if(x.d1^y.d1) return x.d1<y.d1;
	if(x.d2^y.d2) return x.d2<y.d2;
	return x.id<y.id;
}
void CDQ_Divide(int l,int r){
	if(l==r) return ;
	int mid=l+r>>1,posl=l,posr=mid+1,pos=l,tot=0;
	CDQ_Divide(l,mid),CDQ_Divide(mid+1,r);
	while(posl<=mid&&posr<=r){
		if(Q[posl].d2<=Q[posr].d2){
			if(Q[posl].id==0) tot++;
			tmp[pos++]=Q[posl++];
		}
		else{
			if(Q[posr].id<0) Ans[-Q[posr].id]-=tot;
			else if(Q[posr].id>0) Ans[Q[posr].id]+=tot;
			tmp[pos++]=Q[posr++];
		}
	}
	while(posl<=mid) tmp[pos++]=Q[posl++]; 
	while(posr<=r){
		if(Q[posr].id<0) Ans[-Q[posr].id]-=tot;
		else if(Q[posr].id>0) Ans[Q[posr].id]+=tot;
		tmp[pos++]=Q[posr++];
	}
	for(int i=l;i<=r;i++) Q[i]=tmp[i];
	return ;
}

signed main(){
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=2,x,v;i<=n;i++) read(x),read(v),add(i,x,v),add(x,i,v);
	dfs(1,0);
	sort(Q+1,Q+cnt+1,cmp1);
	CDQ_Divide(1,cnt);
	for(int i=1;i<=n;i++) write(Ans[i]),putchar(' ');
	return 0;	
}
```









---

## 作者：mol茶蛋糕 (赞：5)

俗话说解每道题都是从暴力开始的嘛  
刚拿到这道题时，我的第一个想法是枚举每个起点，然后向上爬，爬到多高是多高，接着我过了样例，我本来以为只是TLE，结果直接WA掉。     
然而这道题的正解是：前缀和+倍增+dfs+差分  
拿着每个点，先dfs跑一下深度，顺便把TA的倍增数组预处理好，然后再倍增跑一下每一个点能被控制的最远祖先，并用差分数组处理一下，最后再用dfs跑一遍把下边的值收一下（其实就相当于前缀和），就bingo了！

~~~
#include<iostream>
using namespace std;
void read(int & x)
{
	x=0;int f=1;char c=getchar();
	while(c>'9'||c<'0') {if(c=='-') f=-1; c=getchar();}
	while(c<='9'&&c>='0')
	{x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x*=f;
}
void print(int x)
{
	if(x<0) {putchar('-');x=-x;}
	if(x>9) print(x/10);
	putchar(x%10+48);
}
int q[200005];
struct edge{
	int w,to,nxt;
}e[200005];
int head[200005],cnt;
void add(int x,int y,int z)
{
	cnt++;
	e[cnt].w=z;
	e[cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
long long dep[200005];
int doubly[21][200005],prefix[200005];
void dfs(int s)		//预处理一个倍增数组 
{
	for(int i=1;i<=20;i++)
		doubly[i][s]=doubly[i-1][doubly[i-1][s]];
	for(int i=head[s];i;i=e[i].nxt)
	{
		int to=e[i].to;
		doubly[0][to]=s;
		dep[to]=dep[s]+e[i].w;
		dfs(to);
	}
}
void find(int now)		//找到最远的祖先 
{
	int x=now;
	for(int i=20;i>=0;--i)
		if(doubly[i][x]&&dep[now]-dep[doubly[i][x]]<=q[now]) 
			x=doubly[i][x];
	if(x!=1) prefix[doubly[0][x]]--;
	if(now!=1) prefix[doubly[0][now]]++;
	
}
void DFS(int x)
{
	for(int i=head[x];i;i=e[i].nxt)
	{
		int to=e[i].to;
		DFS(to);
		prefix[x]+=prefix[to];
	}
}
int main()
{
	int n;
	read(n);
	for(int i=1;i<=n;i++)
		read(q[i]);
	for(int i=2;i<=n;i++)
	{
		int k,g;
		read(k),read(g);
		add(k,i,g);
	}
	dfs(1);
	for(int i=1;i<=n;i++)		//更改差分数组 
		find(i);
	DFS(1);		//dfs一遍求前缀和 
	for(int i=1;i<=n;i++)
		print(prefix[i]),putchar(' ');
	return 0;
}
~~~

---

## 作者：qianfujia (赞：5)

**树上差分 + DFS + 二分 + 树上前缀和**

搜索$O(n)$，对于每个点二分$O(log\ n)$祖先前缀和$O(n)$，差分$O(1)$修改路径

$$O(n\ log \ n)$$

Code
```cpp
#include<bits/stdc++.h>
#define LL long long
#define N 200010
using namespace std;
LL n;

struct EDGE{
	LL u, v;
	LL Next;
	LL Value;
}G[N];

LL tot = 0;
LL Head[N];

inline void Add(LL u, LL v, LL Val)
{
	++ tot;
	G[tot].u = u;
	G[tot].v = v;
	G[tot].Value = Val;
	G[tot].Next = Head[u];
	Head[u] = tot;
}

LL Ctrl[N];

LL Ans[N];
LL Stk[N], Size = 0;
LL F[N];
inline void DFS(LL u)
{
	Stk[++ Size] = u;
	LL Left = 1, Right = Size;
	while(Left < Right)
	{
		LL Mid = (Left + Right) >> 1;
		if(F[Stk[Mid]] >= F[u] - Ctrl[u])
			Right = Mid;
		else
			Left = Mid + 1;
	}
	++ Ans[Stk[Size - 1]];
	-- Ans[Stk[Left - 1]];
	for(LL i = Head[u]; i; i = G[i].Next)
	{
		LL v = G[i].v;
		F[v] = G[i].Value + F[u];
		DFS(v);
		Ans[u] += Ans[v];
	}
	-- Size;
}
int main()
{
	scanf("%lld", &n);
	for(LL i = 1; i <= n; ++ i)
		scanf("%lld", &Ctrl[i]);
	for(LL i = 1; i < n; ++ i)
	{
		LL u, Val;
		scanf("%lld%lld", &u, &Val);
		Add(u, i + 1, Val);
	}
	DFS(1);
	for(LL i = 1; i <= n; ++ i)
		printf("%lld ", Ans[i]);
	return 0;
}
```

---

## 作者：天命之路 (赞：4)

这题....就没有树状数组解法吗？还是有的。

注意到因为$u$在$v$的子树内，所以$dist(v,u)=dep[u]-dep[v]$,$dep$为深度，

所以$dep[u]-dep[v]\le a[u]$

$ dep[u]-a[u] \le dep[v]$

将 $dep[u]-a[u]$ 和 $dep[v]$ 离散化，然后作为树状数组的下标，设立三化的结果为 $b[u]$ 和 $bd[u]$。

所以结点 $x$ 的答案就是树状数组中在  $bd[x]$ 之前（包括本身）的数的个数

显然用 $dfs$ 求解

还有一点 ,在执行 $dfs(x)$ 之前，树状数组并不是空的，这怎么办？

这好办，我们在递归下放之前，先预先减去之前的影响即可。

上代码:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,Sz=N<<1,M=N<<1;
int fir[N],nxt[M],to[M],w[M],ect=0,n;
//dep[u]-dep[v]<=a[u]
//dep[u]-a[u]<=dep[v]
int a[N],dep[N],ans[N];

int tr[Sz];
#define lowbit(x) (x&(-x))
inline void add(int pos,int x){for(int p=pos;p<Sz;p+=lowbit(p)) tr[p]+=x;}
inline int sum(int pos){ int res=0;for(int p=pos;p;p^=lowbit(p)) res+=tr[p];return res;}  //四行树状数组
int bd[N],b[N];
inline void dfs(int x,int f)   //求dep
{
	for(int i=fir[x];i;i=nxt[i])
	if(f!=to[i]) 
	dep[to[i]]=dep[x]+w[i],
	dfs(to[i],x);
}
inline void solve(int x,int f)   //求答案
{
	ans[x]-=sum(bd[x]);   //预先减去影响
	for(int i=fir[x];i;i=nxt[i])
	if(to[i]!=f) solve(to[i],x);
	ans[x]+=sum(bd[x]);   //加上影响
	add(b[x],1);  //加标记
}
inline void addedge(int u1,int v1,int w1)
{
	nxt[++ect]=fir[u1];fir[u1]=ect;to[ect]=v1;w[ect]=w1;
}
int vals[Sz];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=2;i<=n;i++)
	{
		int f,w;
		scanf("%lld%lld",&f,&w);
		addedge(f,i,w);
	}
	dfs(1,0);
    
	for(int i=1;i<=n;i++) vals[i]=dep[i]-a[i],vals[i+n]=dep[i];
	sort(vals+1,vals+n*2+1);
	int tot=unique(vals+1,vals+n*2+1)-vals-1;
	for(int i=1;i<=n;i++)
	bd[i]=lower_bound(vals+1,vals+tot+1,dep[i])-vals,
	b[i]=lower_bound(vals+1,vals+tot+1,dep[i]-a[i])-vals;  //离散化
    
	solve(1,0);
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
}
```

---

## 作者：loctopus (赞：3)

## 简述题意
- 一棵有 $n$ 个节点的树，根节点为 $1$。

- 每个点有点权 $a_i$ ，每条边也有边权 $x_i$，权值均为正整数 。

- 定义 $\operatorname{dis}(u,v)$ 为从 $u$ 到 $v$ 的简单路径上的边权和。

- 当且仅当 $u$ 在 $v$ 的子树中并且 $\operatorname{dis}(u,v)\leqslant a_u$ ，**顶点 $v$ 控制顶点 $u$ $(v!=u)$**。

- 问：对于每个节点能控制几个节点。

## 思路

以下内容中均设 $u$ 的深度大于 $v$ 的深度。

首先思考如何求出 $\operatorname{dis}(u,v)$，一般情况下有：

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
$\operatorname{dis}(u,v)=\operatorname{dis}(1,u)+\operatorname{dis}(1,v)-2 \times \operatorname{dis}(1,\operatorname{lca}(u,v))$

但显然对于这题是杀鸡用牛刀了。

本题求距离时 $u$ 在 $v$ 的子树中，所以不需要用到 $\operatorname{lca}(u,v)$ 。

只需要 $dfs$ 一下就可求出距离，而且还可以发现一条性质：

- 从 $v$ 向下到 $u$ 的经过的每一条路径的边权和一定**严格单调递增**。

然后我们发现题目中对“控制”的定义与 $a_u$ 有关。

于是**从 $u$ 入手**，如果从 $v$ 入手就一点思路都没有了~~在暴力的路上一去不复返~~。

借助刚才的性质不难得出，只要从 $u$一直向上，

满足 $\operatorname{dis}(u,v)\leqslant a_u$ 的节点都可以控制 $u$。

所以只需要找出能控制到 $u$ 的深度最浅，也就是距离最远的 $v$。 

模仿倍增求 $\operatorname{lca}$ 即可。

```c++
//代码里的c[i]即为上文的点权a[i]
void dfs1(int x,int fa)
{
	f[x][0]=fa; int u=x;
	for(int i=0;i<=19;i++) f[x][i+1]=f[f[x][i]][i];
	for(int i=20;i>=0;i--)
		if(f[u][i]&&dis[x]-dis[f[u][i]]<=c[x])
			u=f[u][i];
}
```
找出目标点 $v$ 后，统计答案。

把从 $f[u][0]$ 到 $v$上的点的答案全部加 $1$ ，因为他们都可以控制 $u$ 。

注意是**从 $f[u][0]$ 开始**，**$u$ 不能控制它自己**。

树上连续一段增加相同的数？不就是树上差分吗，还比一般的更简单。

只需：

```c++
	//只需要两句是因为增加的区间并没有离开u所在的子树内
	dif[f[x][0]]++; dif[f[u][0]]--;
```

最后再 $dfs$ 一次统计答案即可，注意 $\operatorname{dis}(u,v)$ 可能会爆 $int$ 。

放一下完整 code 。

```c++
#include<cstdio>
#include<iostream>
#define N 200050
#define ll long long 
using namespace std;
ll n,m,a,b,c[N];
ll first[2*N],nxt[2*N],go[2*N],w[2*N],tot;
ll f[N][21],dis[N],dif[N],ans[N];
inline ll read()
{
	ll num=0;
	char c=getchar();
	while(c>'9'||c<'0') c=getchar();
	while(c>='0'&&c<='9'){num=num*10+c-'0'; c=getchar();}
	return num;
}
void add(int u,int v,ll cost)
{
	nxt[++tot]=first[u];first[u]=tot;go[tot]=v;w[tot]=cost;
}
void dfs1(int x,int fa)
{
	f[x][0]=fa; int u=x;
	for(int i=0;i<=19;i++) f[x][i+1]=f[f[x][i]][i];
	for(int i=20;i>=0;i--)
		if(f[u][i]&&dis[x]-dis[f[u][i]]<=c[x])
			u=f[u][i];
	dif[f[x][0]]++; dif[f[u][0]]--;
	for(int i=first[x];i;i=nxt[i])
		if(go[i]!=fa)
			dis[go[i]]=dis[x]+w[i],
			dfs1(go[i],x);
}
ll dfs2(int x,int fa)
{
	ans[x]=dif[x];
	for(int i=first[x];i;i=nxt[i])
		if(go[i]!=fa)
			ans[x]+=dfs2(go[i],x);
	return ans[x];
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) c[i]=read();
	for(int i=1;i<=n-1;i++)
	{
		a=read(); b=read();
		add(a,i+1,b); add(i+1,a,b);
	}
	dfs1(1,0); dfs2(1,0);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```

### 啰嗦几句：

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（关于为什么从 $u$ 出发考虑）

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;关键原因：“控制”的定义与 $u$ 的相关性更大。

- &nbsp;&nbsp;&nbsp;如果从 $v$ 出发考虑的话一定要落实到其子树内每一个节点上，

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;而且每个点的点权并没有规律，复杂度降不下来。

- &nbsp;&nbsp;&nbsp;而从 $u$ 出发，$a_u$就是确定的，而且$\operatorname{dis}(u,v)$ 有单调性，

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;此时倍增就可以快速求出最远的 $v$ ，然后用差分快速统计答案。



---

## 作者：aRenBigFather (赞：3)

## 主要算法

前缀边权和 + 树上差分 + 倍增

## 朴素算法

对于每一个点$P1$,向它上面的所有父亲节点$P_f$查询,看该父亲节点是否有能力控制点$P1$,如果能,就继续向上找,直到找到能控制该点的最高父节点$P_{ff}$，再将这条链上的所有节点答案+1（深度最浅）

容易证明,从$P1$到$P_{ff}$这条链上的每个节点都有能力控制点$P1$,相当于$P1$给这条链上每个节点都贡献了一个单位的答案

暴力做法就是枚举每个$P1$，$P_f$，然后分别找到每个$P1$的$P_{ff}$，再将这条链上的所有节点答案+1

显然时间复杂度为 $O(n^2)$ 会超时，考虑优化

## 快速求两点距离(在同一条链上)的优化

建图后，dfs预处理每一个节点$P_i$到根节点1的距离 $dis[i]$

对于在同一条链上的两个节点$u,v$,他们之间的距离就是$dis[v]-dis[u]$

其中v为较深的一个点,深度可以顺便在dfs预处理时维护

## 找最浅父亲$P_{ff}$的优化

由于我们肯定不能从$P1$起一个一个向上爬，因为这样实在是太慢了

所以想到倍增求LCA时用到的思想,维护$Parent[i][j]$为第i个节点的第$2^j$个祖先编号，这样我们可以每次不向上跳一步,而是跳$2^j$步，这样就加速了我们找父亲节点的速度

怎么确定这个j呢,我们可以从高到低枚举这个j(比如从20开始),然后判断跳$2^j$步的点能不能把$P1$控制到,如果能我们就移动到那个点,然后继续枚举j跳跃,容易发现,越跳到后面,每次跳跃的步数是会越小的(即j递减)，所以一个循环枚举j就能完成

找父亲节点复杂度 $O(log n)$

## 给链上节点添加答案优化-树上差分

我们现在要做的是给链上每一个节点的答案都加上1,显然如果暴力添加，前面的优化努力又白费了

所以现在要找到一个高效的算法来维护:给树上一条链的每一个点权值加上1,多次添加,最后询问每个节点的权值

运用一维数组差分的思想,我们可以在树上来进行差分,思路同理,非常简单,这里不再赘述

## AC代码(已加入防剽窃片段)


```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,s;
const int maxn = 200010;
struct edge{
    int v,nxt;
    ll w;
}E[maxn*2];
int p[maxn],eid;
void init(){
    memset(p,-1,sizeof p);
    eid = 0;
}
void insert(int u,int v,ll w){
    E[eid].v = v;
    E[eid].nxt = p[u];
    E[eid].w = w;
    p[u] = eid++;
}
void insert2(int u,int v,ll w){
    insert(u,v,w);
    insert(v,u,w);
}
ll pv[maxn],d[maxn],dis[maxn];
int parent[maxn][25];
void dfs1(int u,int fa){
	for(register int i=p[u];~i;i=E[i].nxt){
		int v = E[i].v,w = E[i].w;
		if(v == fa) continue;
		dis[v] = dis[u] + w;
		parent[v][0] = u;
		d[v] = d[u] + 1;
		dfs1(v,u);
	}
}
ll dt[maxn];
void addCtl(int u,int v){
	if(d[u] > d[v]) swap(u,v);
	//printf("addctl %d %d\n",u,v);
	int c = u;
	int fc = parent[c][0];
	dt[u]++;
    dt[v]++;
    dt[c]--;
    dt[fc]--;
}
void dfs2(int u,int fa){
	for(register int i=p[u];~i;i=E[i].nxt){
		int v = E[i].v;
		if(v == fa) continue;
		dfs2(v,u);
		dt[u] += dt[v];
	}
}
int main(){
    init();
    scanf("%lld",&n);
    for(register int i=1;i<=n;i++){
		scanf("%lld",pv+i);
	}
	for(register int i=1;i<=n;i++){
		ll p,w;
		scanf("%lld%lld",&p,&w);
		insert2(i+1,p,w);
	}
	d[1] = 1;
	dfs1(1,-1);
	for(register int lev=1;(1<<lev)<=n;lev++){
		for(register int i=1;i<=n;i++){
			parent[i][lev] = parent[parent[i][lev-1]][lev-1];
		}
	}
	for(register int i=1;i<=n;i++){
		ll aim = pv[i];
		ll now = 0,nowu = i,nowv = nowu;
		for(register int j=18;j>=0;j--){
			ll tmpnowv = parent[nowv][j];
			ll sumEdge = dis[nowu] - dis[tmpnowv];
			if(sumEdge <= aim){
				now += sumEdge;
				nowv = tmpnowv;
			}
		}
		if(nowv == 0) nowv = 1;
		//printf("%d can be ctled by %d\n",i,nowv);
		if(nowu != nowv) addCtl(parent[nowu][0],nowv);
	}
	
	dfs2(1,-1);
	for(register int i=1;i<n;i++){
		printf("%lld ",dt[i]);
	}
    return 0;
}
```


---

## 作者：chen_qian (赞：2)

看到题解里面都是倍增的做法。来一个 $\text{dfn}$ 序 + $\text{BIT}$ 的做法。 

- 题意：给定一棵带边权的树，每个点 $i$ 上有权值 $\text{a}_ i$。$u$ 能支配 $v$ 需要满足 $u$ 是 $v$ 的父亲，且 $\text{dis(u,v)} \le \text{a} _ v$。$\text{dis(u,v)}$ 定义为树上距离。

- 解法：最早的时候看错题了，看成 $\text{dis(u,v)} \le \text{a} _ u$ 。然后想了个做法，写完后才发现看错题，但是实际上差别不大。

 - 记 $ \text{dis}_ x$ 为点 $x$ 的深度，那么实际上对于$x$ 我们要统计的答案就是在 $x$ 的子树中，满足 $\text{dis} _ y-\text{dis}_ x \le \text{a}_ y$ 的 $y$ 的数量，将不等式相关的挪到一边就是 $\text{dis} _ y- \text{a}_ y \le \text{dis}_ x$。 用 $\text{dfn}$ 序压到序列上就是求区间 $[l,r]$ 里值小于一个给定值的个数，直接将询问拆开，就是问前缀里小于某个数的个数，直接用 $\text{BIT}$ 维护。
 
 ```cpp
#include<bits/stdc++.h>
#define N 300005
#define int long long
#define lb(x) x&-x 
using namespace std;
int n,m,a[N];
int head[N],idx;
struct edge{
	int v,w,next;
}e[N];
int tmp[N],Idx;
void add(int u,int v,int w){
	e[++idx].v=v;
	e[idx].next=head[u];
	head[u]=idx;
	e[idx].w=w;
}
int dfn[N],rev[N],size[N],num;
int dis[N];
int ans[N];
void dfs(int x){
	dfn[x]=++num;
	rev[num]=x;
	size[x]=1;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
	 	dis[y]=dis[x]+e[i].w;
	 	dfs(y);
	 	size[x]+=size[y];
	} 
}
int L[N],R[N];
struct node{
	int op,x,id,l,r,type;
}p[N<<1];
int cnt;
bool cmp(node x,node y){
	if(x.x!=y.x) return x.x<y.x;
	return x.op<y.op; 
}
int c[N<<2];
void add(int x,int v){
	for(;x<=m;x+=lb(x)) c[x]+=v;
} 
int ask(int x){
	int res=0;
	for(;x;x-=lb(x)) res+=c[x];
	return res;
}
int getid(int x){
	return lower_bound(tmp+1,tmp+m+1,x)-tmp;
} 
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=2;i<=n;i++){
		int f,w;
		scanf("%lld%lld",&f,&w);
		add(f,i,w);
	}
	dfs(1);
	for(int i=1;i<=n;i++){
		tmp[++Idx]=dis[i];
		tmp[++Idx]=dis[i]-a[i];
	}
	sort(tmp+1,tmp+Idx+1);
	m=unique(tmp+1,tmp+Idx+1)-tmp-1;
	for(int i=1;i<=n;i++){
		p[++cnt]=(node){2,dfn[i]-1,i,1,getid(dis[i]),-1};
		p[++cnt]=(node){2,dfn[i]+size[i]-1,i,1,getid(dis[i]),1};
		p[++cnt]=(node){1,dfn[i],getid(dis[i]-a[i]),0,0,0};
	}
	sort(p+1,p+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		if(p[i].op==2){
			ans[p[i].id]+=p[i].type*(ask(p[i].r)-ask(p[i].l-1));
		} 
		else add(p[i].id,1); 
	}
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]-1);
	return 0;
}
```


---

## 作者：JayTwenty (赞：2)

（前缀和+差分）
dfs遍历，当前点为v,过程中用二分或倍增找到最远的一个点x满足dist(v,x)<=point[v](即v的点权）将这两点之间所有的点都ans++。          
这里用差分来优化：将x的父亲节点ans--，将v的父亲节点ans++,然后在dfs的末尾往回传递ans值，就可以达到将v到x一条链上所有的点都ans++；    
最后依次输出答案即可。



~~~~#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=200008;
template<typename xxx>inline void read(xxx &x){
	x=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-'){f=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x*=f;
}
template<typename xxx>inline void print(xxx x){
	if(x<0){x=-x;putchar('-');}
	if(x>9){print(x/10);}
	putchar(x%10+48);
}
struct node{
	int v,w,nxt;
}e[maxn<<1];
int head[maxn];
int tot;
inline void add(int a,int b,int c){
	++tot;
	e[tot].v=b;
	e[tot].w=c;
	e[tot].nxt=head[a];
	head[a]=tot;
}
long long dep[maxn]; //注意dep数组必须用long long否则过不了。
int point[maxn]; 
int ans[maxn]; 
int f[maxn][20];
void dfs(int x,int fa,int val){
	f[x][0]=fa;
	dep[x]=dep[fa]+val;
	int v,w;
	for(int i=1;i<=18;i++){
		f[x][i]=f[f[x][i-1]][i-1];
	}
	for(int i=head[x];i;i=e[i].nxt){
		v=e[i].v;
		w=e[i].w;
		if(v==fa) continue;
		dfs(v,x,w);
		int vp=point[v];
		int p=1;
		int now=v;//倍增
		while(p&&now){
			if(dep[now]-dep[f[now][p]]<=vp){
				vp-=dep[now]-dep[f[now][p]];
				now=f[now][p];
				p<<=1;
			}
			else {
				p>>=1;
			}
		}
		if(dep[now]-dep[f[now][0]]<=vp){
			now=f[now][0];
		}
		ans[f[now][0]]--;
		ans[f[v][0]]++;
	}
	ans[fa]+=ans[x];
}
int n;
int aa,cc;
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(point[i]);
	}
	for(int i=2;i<=n;i++){
		read(aa),read(cc);
		add(aa,i,cc);
		add(i,aa,cc);
	}
	dfs(1,0,0);
	for(int i=1;i<=n;i++){
		print(ans[i]);
		putchar(' ');
	}
}
~~~~

---

## 作者：mrclr (赞：1)

前缀和+倍增+树上差分

假设$v$是$u$子树中的一个点，那么$u$能控制$v$的条件是受$v$的权值的限制，而并非$u$。因此我们就能想到计算每一个点的贡献，即$v$有多少个祖先能控制它。这样就能想到暴力的做法：枚举每一个点$i$，向上爬直到两点间距离大于$a_i$为止。然后树上差分（准确说是链上差分）即可。至于两点间距离，采用前缀和相减。

但这样的复杂度能达到$O(n^2)$，因此我们可以用倍增优化一步步向上跳，达到$O(nlogn)$。

总结一下，先$dfs$一遍求出每一个点到根节点的距离和倍增数组，复杂度$O(nlogn)$；然后对于每一个点倍增向上跳，并修改差分数组，复杂度也是$O(nlogn)$；最后$O(n)$ $dfs$一遍求查差分组的树上前缀和。
  
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define rg register
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 2e5 + 5;
inline ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) last = ch, ch = getchar();
  while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
  if(last == '-') ans = -ans;
  return ans;
}
inline void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}

int n;
ll a[maxn];
struct Edge
{
  int nxt, to, w;
}e[maxn];
int head[maxn], ecnt = -1;
void addEdge(int x, int y, int w)
{
  e[++ecnt] = (Edge){head[x], y, w};
  head[x] = ecnt;
}

int fa[21][maxn];
ll dis[maxn];
void dfs(int now)
{
  for(int i = 1; i <= 20; ++i)
    fa[i][now] = fa[i - 1][fa[i - 1][now]];
  for(int i = head[now], v; i != -1; i = e[i].nxt)
    {
      v = e[i].to;
      fa[0][v] = now;
      dis[v] = dis[now] + e[i].w;
      dfs(v);
    }
}

int dif[maxn];
void solve(int now)
{
  int x = now;
  for(int i = 20; i >= 0; --i)
      if(fa[i][x] && dis[now] - dis[fa[i][x]] <= a[now]) x = fa[i][x];
  if(x != 1) dif[fa[0][x]]--;
  if(now != 1) dif[fa[0][now]]++;
}

void dfs2(int now)
{
  for(int i = head[now], v; i != -1; i = e[i].nxt)
    {
      v = e[i].to;
      dfs2(v);
      dif[now] += dif[v];
    }
}

int main()
{
  Mem(head, -1);
  n = read();
  for(int i = 1; i <= n; ++i) a[i] = read();
  for(int i = 2; i <= n; ++i)
    {
      int x = read(), w = read();
      addEdge(x, i, w);
    }
  dfs(1);
  for(int i = 1; i <= n; ++i) solve(i);
  dfs2(1);
  for(int i = 1; i <= n; ++i) write(dif[i]), space; enter;
  return 0;
}
```

---

## 作者：pitiless0514 (赞：1)

首先整个图搜一遍预处理出每个点到根节点的距离。

然后发现暴力去判断每个点是否被控制是 $O(n^2)$ 的，显然不行。

由于是在树上的问题，考虑倍增优化，发现可行。

倍增预处理出往上跳 $2$ 的次幂会跳到哪一个节点。

容易发现我们其实就是要找到最远的能被支配的点 $g$。

然后这个点 $g$ 到当前点间的点很明显是都可以被控制的。

直接暴力去加还是会超时，这时可以上一个数据结构去维护。

但发现其实完全没有必要，可以用树上差分，最后整个图搜索一遍就完事了。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
template<typename T> inline void read(T &x){
	T f=1;x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x*=f;
}
const int N = 3e5;
int n,a[N],nex[N],first[N],v[N],w[N],num=1;
int dep[N],f[N][35],dis[N],ans[N];
void add(int from,int to,int val){
	nex[++num]=first[from];first[from]=num;v[num]=to;w[num]=val;
}
void dfs(int x,int fa){
	for(int i=first[x];i;i=nex[i]){
		int to=v[i];
		if(to==fa||dep[to]) continue;
		dep[to]=dep[x]+1;
		f[to][0]=x;
		dis[to]=dis[x]+w[i];
		dfs(to,x);
	}
}
void get(int x){
	int g=x;
	for(int i=32;i>=0;i--){
		if(f[g][i]&&dis[x]-dis[f[g][i]]<=a[x]){
			g=f[g][i];
		} 
	}
	ans[f[g][0]]--;
	ans[f[x][0]]++;
}
void dfs2(int x){
	for(int i=first[x];i;i=nex[i]){
		int to=v[i];
		dfs2(to);
		ans[x]+=ans[to];
	}
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=2;i<=n;i++){
		int p,w;read(p),read(w);
		add(p,i,w);
	}
	dfs(1,-1);
	for(int j=1;j<=32;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	for(int i=1;i<=n;i++){
		get(i);
	}
	dfs2(1);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：PrincessQi (赞：1)

题意：给定一棵有根树，求出对于每个点 $i$ ，它的子树里有多少个节点 $x$ 满足 $dis(i,x)\leq a_x$。

题解：先对这个树进行树上差分、求dfs序、求每个点的深度 $d_i$（到根节点的距离）。

然后，有一个小结论：设节点 $i$ 的子树大小为 $s_i$，则它的子树的dfs序区间为 $[i,i+s_i-1]$。（其实就是dfs序的定义）

所以，这道题转化成了：对于dfs序为 $i$ 的节点，有多少个dfs序为 $x$（$x\in [i+1,i+s_i-1]$）的节点满足 $d_x-a_x\leq d_i$，其实就是静态区间求排名。

然后就可以使用树套树/主席树/整体二分解决这个题了。

时间复杂度：$O(n\log^2 n)$。

其实还可以写分块，时间复杂度：$O(n\sqrt n \log\sqrt n)$。

由于 $n\leq 2\times 10^5$，上述做法均可通过此题。

---

## 作者：zhengrunzhe (赞：1)

非常裸的做法 提供一个数据结构合并

$dist(x,y)\leq a[y] \ \  \ y \in subtree_x$

开个前缀和(到根距离)数组$dis[]$ 转化成

$dis[y]-dis[x]\leq a[y]$

移项得

$dis[y]-a[y]\leq dis[x]$

然后对于每个点p 先查合并上来的数据结构(表示了p不包含的子树)里差有多少个$\leq dis[p]$的 然后把$dis[p]-a[p]$作为关键字扔到数据结构里

边权是$10^9$级别的 最大距离可能达到$2*10^{14}$

用线段树不太好搞 我就写了个$splay$启发式合并

对于每个点取子树最大的儿子作重儿子 把轻儿子合并到重儿子上就可以保证复杂度

```cpp
#include<cstdio>
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
typedef long long ll;
const int N(2e5+5);
struct tree
{
	ll key;
	int cnt,size;
	tree *fa,*son[2];
	static tree *null;
	void *operator new(size_t size);
	void operator delete(void *ptr);
	inline tree():key(0),cnt(0),size(0),fa(null){son[0]=son[1]=null;}
	inline tree(const ll &key,const int &cnt):key(key),cnt(cnt),size(cnt),fa(null){son[0]=son[1]=null;}
	inline const void pushup()
	{
		size=son[0]->size+cnt+son[1]->size;
	}
	inline const void set(tree *p,const bool &f)
	{
		if (p!=null)p->fa=this;
		if (this!=null)son[f]=p;
	}
	inline const bool id()
	{
		return fa->son[1]==this;
	}
	inline const void rotate()
	{
		tree *fa(this->fa);
		const bool f(id());
		fa->fa->set(this,fa->id());
		fa->set(son[!f],f);
		set(fa,!f);
		fa->pushup();pushup();
	}
	inline const void splay(tree *&root);
}*root[N],*tree::null;
#define null tree::null
char memory_pool[N*sizeof(tree)],*tail(memory_pool+sizeof(memory_pool));
void *recycle[N],**top(recycle);
inline void *tree::operator new(size_t size){return recycle!=top?*--top:tail-=size;}
inline void tree::operator delete(void *ptr){*top++=ptr;}
inline const void tree::splay(tree *&root)
{
	for (;fa!=null;rotate())
		if (fa->fa!=null)
			(fa->id()^id()?this:fa)->rotate();
	root=this;
}
inline const void insert(tree *&root,const ll &key,const int &cnt)
{
	if (root==null)return root=new tree(key,cnt),void();
	tree *now(root);
	while (1)
	{
		if (now->key==key)return now->cnt+=cnt,now->pushup(),now->splay(root);
		tree *fa(now);
		const bool f(now->key<key);
		now=fa->son[f];
		if (now==null)return fa->set(now=new tree(key,cnt),f),fa->pushup(),now->splay(root);
	}
}
inline const int query(tree *&root,const ll &key)
{
	int sum(0);
	tree *p(root);
	while (p!=null)
		if (key<p->key)p=p->son[0];
		else if (key==p->key)return sum+p->son[0]->size+p->cnt;
			else sum+=p->son[0]->size+p->cnt,p=p->son[1];
	return sum;
}
inline const void merge(tree *a,tree *&b)
{
	if (a==null)return;
	merge(a->son[0],b);
	merge(a->son[1],b);
	insert(b,a->key,a->cnt);
	delete a;
}
int head[N],a[N],edc,n,ans[N];
struct edge
{
	int to,w,next;
	inline edge(){}
	inline edge(const int &to,const int &w,const int &next):to(to),w(w),next(next){}
}e[N<<1];
inline const void addedge(const int &u,const int &v,const int &w)
{
	e[++edc]=edge(v,w,head[u]);head[u]=edc;
}
ll dis[N];
void check(tree *p)
{
	if (p==null)return;
	check(p->son[0]);
	printf(":%lld lson:%lld rson:%lld fa:%lld size:%d cnt:%d\n",p->key,p->son[0]->key,p->son[1]->key,p->fa->key,p->size,p->cnt);
	check(p->son[1]);
}
inline const void dfs(const int &p)
{
	root[p]=null;
	int wson(0),wsiz(0);
	for (int son,i(head[p]);i;i=e[i].next)
		if (dis[son=e[i].to]=dis[p]+e[i].w,dfs(son),root[son]->size>wsiz)
			wsiz=root[son]->size,wson=son;
	if (!wson)return insert(root[p],dis[p]-a[p],1);
	for (int i(head[p]);i;i=e[i].next)
		if (e[i].to^wson)
			merge(root[e[i].to],root[wson]);
	root[p]=root[wson];
	ans[p]=query(root[p],dis[p]);
	insert(root[p],dis[p]-a[p],1);
}
int main()
{
	null=new tree;null->fa=null->son[0]=null->son[1]=null;
	read(n);
	for (int i(1);i<=n;i++)read(a[i]);
	for (int i(2),fa,w;i<=n;i++)read(fa),read(w),addedge(fa,i,w);
	dfs(1);
	for (int i(1);i<=n;i++)printf("%d ",ans[i]);
	putchar('\n');
	return 0;
}
```

---

## 作者：Elma_ (赞：0)

考虑一个点 $v$ 对多少个点 $u$（$v$ 在 $u$ 的子树中） 有贡献。

因为一个点 $u$ 能否控制到点 $v$ 只和 $a_v$ 有关系，所以这个贡献可以从点 $v$ 用倍增求出来。注意这个贡献直接一个一个加时间复杂度是会爆炸的，我们注意到对于任意一个点 $v$，能控制它的节点的点集在树上一定是一条链的形式，所以我们树上差分打一个标记，最后前缀和统计一遍答案就行了。

总时间复杂度 $O(n\log n)$。

```cpp
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

inline ll read() {
	ll x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

struct node {
	int nxt, to, val;
}edge[maxn << 1];
int n, m, tot;
ll a[maxn], head[maxn], sum[maxn], dis[maxn], fa[maxn][35];

inline void addedge(int u, int v, int w) {
	edge[++tot].nxt = head[u];
	edge[tot].to = v;
	edge[tot].val = w;
	head[u] = tot;
}

inline void dfs(int u) {
	for (int i = 1;i <= 30;i++)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	int now = u;
	for (int i = 30;i >= 0;i--)
		if (fa[now][i] && dis[u] - dis[fa[now][i]] <= a[u]) 
			now = fa[now][i];
	sum[fa[now][0]]--, sum[fa[u][0]]++;
	for (int i = head[u];i;i = edge[i].nxt) {
		int v = edge[i].to; fa[v][0] = u;
		dis[v] = dis[u] + edge[i].val;
		dfs(v), sum[u] += sum[v];
	}
}

int main(void) {
	n = read();
	for (int i = 1;i <= n;i++) a[i] = read();
	for (int i = 2;i <= n;i++) {
		int u = read(), val = read();
		addedge(u, i, val);
	}
	dfs(1);
	for (int i = 1;i <= n;i++) printf("%lld%c", sum[i], " \n"[i == n]);
	return 0;
}
```


---

## 作者：极寒神冰 (赞：0)

做法：发现每一个点都是这个点到根上连续的一段且没有负权边。可以倍增找到最远的点并使用差分记录答案，


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int N=400040;
int head[N],cnt;
struct edge
{
	int nxt,to,dis;
}e[N];
int n;
int a[N];
int dp[N][21],sum[N][21],ans[N];//dp[i][j]表示i号点往上走2^j步的点，sum[i][j]则存从这些值的和
int Log[N];

inline void init_edge()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}

inline void add_edge(int u,int v,int d)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].dis=d;
	head[u]=cnt;
}

inline void dfs1(int u,int f,int dis)
{
	dp[u][0]=f;sum[u][0]=dis;//自己往上走2^0步就是自己的父亲，和为边权
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f)continue;
		dfs1(v,u,e[i].dis);
	}
}
inline void dfs2(int u,int f)//重新遍历一遍树，求值
{
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f)continue;
		dfs2(v,u);
		ans[u]+=ans[v];
	}
}
inline void init_st()//预处理st表
{
	Log[0]=-1;
	for(int i=1;i<=n;i++)
	{
		Log[i]=Log[i>>1]+1;//预处理log
	}
	for(int j=1;j<=Log[n];j++)
	{
		for(int i=1;i<=n;i++)
		{
			dp[i][j]=dp[dp[i][j-1]][j-1];//往上走2^j步
			sum[i][j]=sum[i][j-1]+sum[dp[i][j-1]][j-1];
		}
	}
}

inline void check(int qwq)
{
	int x=qwq，y=a[qwq];
	for(int i=Log[n];i>=0;i--)
	{
		if(sum[x][i]<=y)//枚举这个点最远能走到哪里
		{
			y-=sum[x][i];
			x=dp[x][i];
		}
	}
	ans[dp[x][0]]--;ans[dp[qwq][0]]++;//树上差分，显然这是条链（树上差分模版题CF191C
}

signed main()
{
	init_edge();
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	for(int i=2;i<=n;i++)
	{
		int v=read(),d=read();
		add_edge(i,v,d),add_edge(v,i,d);
	}
	dfs1(1,0,0);
	init_st();
	for(int i=1;i<=n;i++) check(i);
	dfs2(1,0);
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<" ";
	}
	return 0;
}
```


---

## 作者：qiyue7 (赞：0)

给出一个比倍增优雅得多的Dsu on tree的做法。

画图后注意到每一个点影响的节点都是自身到祖先的一条链，deep[u]-A[u]即确定了这个点所能影响的最早祖先深度，每个点的答案就是当前节点子树里最早祖先深度小于当前节点的深度的节点个数，这个可以用大根堆直接维护，pb_ds里的配对堆合并的复杂度为O(1),那么我们直接自底向上合并每个节点的信息的即可。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
#define int long long
vector<pair<int, int> > edge[210000];
array<int, 210000> arr, ans, size1, deep;
__gnu_pbds::priority_queue<pair<int, int>, less<pair<int, int> > > *calc[210000];
void dfs(int u, int fa)
{
	for (auto &k : edge[u])
	{
		int p = k.first;
		if (p != fa)
		{
			deep[p] = deep[u] + k.second;
			dfs(p, u);
			size1[u] += size1[p];
			calc[u]->join(*calc[p]);
		}
	}
	while (!calc[u]->empty() && (calc[u]->top()).first > deep[u])
		calc[u]->pop();
	ans[u] = (int)calc[u]->size();
	calc[u]->push({ deep[u] - arr[u],u });
}
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, u, v;
	size1.fill(1);
	ans.fill(0);
	deep[1] = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> arr[i];
		calc[i] = new __gnu_pbds::priority_queue<pair<int, int>, less<pair<int, int> > >();
	}
	for (int i = 2; i <= n; ++i)
	{
		cin >> u >> v;
		edge[u].push_back({ i,v });
		edge[i].push_back({ u,v });
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i)
		cout << ans[i] << ' ';
	return 0;
}
```


---

