# 【模板】最小割树（Gomory-Hu Tree）

## 题目背景

模板题。做本题之前请确保你会 Dinic 或 ISAP。如果你乱搞过了我请你抽烟。

根据惯例，网络流题不允许卡 Dinic/ISAP，但可以卡 EK，本题数据严格遵循上述条约。

## 题目描述

给定一个 $n+1$ 个点 $m$ 条边的无向连通图，编号 $0\sim n$，多次询问两点之间的最小割。

两点间的最小割是这样定义的：原图的每条边有一个割断它的代价，你需要用最小的代价使得这两个点不连通。

## 说明/提示

保证 $1\le n\leq 500$，$0\le m\leq 1500$，$0\le Q\leq 10^5$，$0\leq w\leq 10^4$，$u\neq v$。

## 样例 #1

### 输入

```
4 5
0 1 2
1 2 2
3 1 3
3 2 1
0 2 1
3
0 3
1 3
1 2```

### 输出

```
3
4
4```

# 题解

## 作者：_LHF_ (赞：41)

##### 终于AC这一题了，发个题解庆祝一下吧！！！
首先，大家要先用Dinic或ISAP做对[【模板】网络最大流](https://www.luogu.org/problem/P3376)（不会网络最大流的可以[点这里](https://www.luogu.org/blog/user48036/solution-p3376)），根据推断，网络最大流=网络最小割。

首先，我们要知道。按照正常暴力的算法，这一题会被T飞的。为了防止TLE事件~~不~~再发生。我们就要采取相应的优化措施。

怎么弄？其实也不难。我们可以建立一棵**最小割树**。
（最小割树？啥？）

最小割树=[分治](https://baike.baidu.com/item/%E5%88%86%E6%B2%BB/3029637?fr=aladdin)+[最小割（最大流）](https://www.luogu.org/blog/user48036/solution-p3376)

其实，我们可以这样做：

![](https://i.loli.net/2019/11/18/hczGRxQN1iTB2Z3.png)

先建立一个无向图，然后再把这个图的整体看做一个集合，然后任意选择两个点（设它们为1和5），在**原图上**跑一趟最小割。如图：

![](https://i.loli.net/2019/11/18/MaPNilbR4ZOp3y8.png)

然后，因为1和5已经无法连接了，所以我们可以把1和5再分成两个集合，中间由一条边连接，这条边的权值为两点之间的最小割。然后，我们再对每个集合进行这样的操作（注意，最小割要在原图上跑），再分下去，直到集合内只剩一个节点为止。如图：

![](https://i.loli.net/2019/11/18/oYBM6Ex5kmTySLR.png)

![](https://i.loli.net/2019/11/18/SBfi2JngopbCq5M.png)

![](https://i.loli.net/2019/11/26/If5UkNzqhvQX28E.png)

![](https://i.loli.net/2019/11/26/UzjNTY7iwCEvA8a.png)

最后，我们可以得到一棵最小割树。
##### 这里要注意，跑最小割（最大流）要在原图上跑！！！
大功告成(〃'▽'〃)，这棵树中任意两点的最小割等于原图上任意两点的最小割，因此，我们直接用BFS来查找就行了，查找一个的时间复杂度是O(n)，这样求Q个最小割只需要用O(Qn)的时间复杂度，查询代码如下：
```cpp
int findans()
{
	head=0,tail=1;
	d[head]=a;
	for(register int i=0;i<=n;i++) dis[i]=0;
	dis[a]=0x7ffffff;
	while(head<tail)
	{
		t=d[head];
		head++;
		for(register int i=trf[t];i;i=tr[i].next)
		{
			if(dis[trar]==0)
			{
				dis[trar]=min(dis[t],tr[i].flow+1);
				if(trar==b) return dis[b]-1;
				d[tail]=trar;
				tail++;
			}
		}
	}
	return dis[b]-1;
}
```
然后就是如何构建这一棵树。其实也不难，因为Dinic或ISAP跑dfs时图中有一些边的容量为0，其实就代表要割掉那一条边，所以我们只需要用搜索的方式来寻找两个集合中分别包含那些数，代码如下：
```cpp
void build(int l,int r)
{
	if(l>=r)return;
	//在原图上跑两点之间的最小割
	a=v[l];
	b=v[l+1];
	dinic();
	//给两个集合之间加一条无向边
	adtr(a,b,ans);
	adtr(b,a,ans);
	//寻找两个集合的元素
	int tl1=0,tl2=0;
	for(register int i=l;i<=r;i++)
	{
		if(dis[v[i]])
		{
			tl1++;
			t1[tl1]=v[i];
		}
		else
		{
			tl2++;
			t2[tl2]=v[i];
		}
	}
	for(register int i=1;i<=tl1;i++) v[i+l-1]=t1[i];
	for(register int i=1;i<=tl2;i++) v[l+tl1+i-1]=t2[i];
	//分治下去
	build(l,tl1+l-1);
	build(l+tl1,r);
}
```
好了，最后来一份完整代码:
```cpp
#pragma GCC optimize(3)
#include<cstdio>
#define N 100010
#define kar k[i].ar
#define trar tr[i].ar
#define min(a,b) (a<b?a:b)
using namespace std;
int a,b,t,n,m,f[N],ans,trl;
struct node {
	int next,ar,flow;
} k[N*20],tr[N*20];
int trf[N],ss;
int first[N],dis[N],len;
int x[N],y[N],v[N],e[N];
int t1[N],t2[N],tl1,tl2;
void add(int a,int b,int t) {
	len++;
	k[len].ar=b;
	k[len].next=first[a];
	first[a]=len;
	k[len].flow=t;
}
void adtr(int a,int b,int t) {
	trl++;
	tr[trl].ar=b;
	tr[trl].next=trf[a];
	trf[a]=trl;
	tr[trl].flow=t;
}
int head,tail,d[N];
bool bfs() {
	head=0,tail=1;
	d[0]=a;
	for(register int i=0; i<=n; i++) dis[i]=0;
	dis[a]=1;
	while(head<tail) {
		t=d[head];
		head++;
		for(register int i=first[t]; i; i=k[i].next) {
			if(dis[kar]==0&&k[i].flow>0) {
				dis[kar]=dis[t]+1;
				if(kar==b) return true;
				d[tail]=kar;
				tail++;
			}
		}
	}
	return false;
}
int dfs(int xx,int flow) {
	if(xx==b) return flow;
	if(flow==0) return 0;
	if(dis[xx]>=dis[b])return 0;
	int h,s=0;
	for(register int i=first[xx]; i>1; i=k[i].next) {
		if(flow==0) {
			dis[xx]=0;
			break;
		}
		if(dis[kar]==dis[xx]+1&&k[i].flow>0) {
			h=dfs(kar,min(flow,k[i].flow));
			s+=h;
			flow-=h;
			k[i].flow-=h;
			k[i^1].flow+=h;
			if(h==0) dis[kar]=0;
		}
	}
	return s;
}
void dinic() {
	for(register int i=0; i<=n; i++) {
		dis[i]=0;
		first[i]=0;
	}
	len=1,ans=0;
	for(register int i=1; i<=m; i++)
		add(x[i],y[i],f[i]),add(y[i],x[i],f[i]);
	while(bfs()) ans+=dfs(a,0x7ffffff);
}
void build(int l,int r) {
	if(l>=r)return;
	a=v[l];
	b=v[l+1];
	dinic();
	adtr(a,b,ans);
	adtr(b,a,ans);
	int tl1=0,tl2=0;
	for(register int i=l; i<=r; i++) {
		if(dis[v[i]]) tl1++,t1[tl1]=v[i];
		else tl2++,t2[tl2]=v[i];
	}
	for(register int i=1; i<=tl1; i++) v[i+l-1]=t1[i];
	for(register int i=1; i<=tl2; i++) v[l+tl1+i-1]=t2[i];
	build(l,tl1+l-1);
	build(l+tl1,r);
}
int findans() {
	head=0,tail=1;
	d[head]=a;
	for(register int i=0; i<=n; i++) dis[i]=0;
	dis[a]=0x7ffffff;
	while(head<tail) {
		t=d[head];
		head++;
		for(register int i=trf[t]; i; i=tr[i].next) {
			if(dis[trar]==0) {
				dis[trar]=min(dis[t],tr[i].flow+1);
				if(trar==b) return dis[b]-1;
				d[tail]=trar;
				tail++;
			}
		}
	}
	return dis[b]-1;
}
int main() {
	int T;
	len=1;
	scanf("%d%d",&n,&m);
	for(register int i=1; i<=m; i++) {
		scanf("%d%d%d",&a,&b,&t);
		x[i]=a,y[i]=b,f[i]=t;
	}
	for(register int i=0; i<=n; i++) v[i]=i;
	build(0,n);
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&a,&b);
		printf("%d\n",findans());
	}
	return 0;
}
```
好了，到此结束了（逃）。

---

## 作者：mydcwfy (赞：29)

### 看大家都是倍增，我换一个简单点的方法吧

~~一开始还以为是最小割的模板呢~~

## 1.题意

[题目传送门](http://luogu.org/problem/P4897)

1. 每次询问$u$到$v$的最小割。
1. 有$Q$个询问，点数、边数分别为$n$、$m$。
1. $Q \leq 10^5,n \leq 500,m \leq 1500$。

## 2.知识储备
网络流 + 最大流

最大流最小割定理

不会请移步
[我的博客](https://www.luogu.com.cn/blog/mydcwfy-342891/wang-lao-liu-chu-bu) 或者百度

## 3.最小割树
很明显，不可能每次求最小割（复杂度为 $O(Qn^2m)$）。

我们将一个网络流的图转化为一棵树，其中原图 $u$ 到 $v$ 的最小割即为转化到树上。

树的一个性质是：删除一条边，树变得不连通。

那么，我们可以任意选 2 个点 $s$ 与 $t$，跑最小割（即最大流），然后再连一条从 $s$ 到 $t$ 的边。

又 Dinic 算法最后一次 bfs 相当于求一个最小割，原图就被分为了两部分。

最后分治就可以了，复杂度为 $O(n^3m)$（Dinic 跑不满的，所以不会超时）。

按这样建出的树，就是一棵无根树。

我们可以发现一个有趣的性质：$u$ 到 $v$ 的最小割就是树上从 $u$ 到 $v$ 的所有路径长的最小值。

可以感性地理解一下（ ~~主要是太菜不会证~~ ）：最小割即为最小的路径长，把 $u$ 到 $v$ 的任意一条路径切断，都是割。

#### 注意：
每次跑 Dinic 时，都要对全图进行，否则就不是最大流
（$u$ 到 $v$ 的最大流就是针对全局的）。

Code：

```cpp
void work(int l,int r)
{//node存放要处理的节点，l与r分别是左右端点
	if (l==r) return ;
	S=node[l],T=node[l+1];
	int t=dinic();
	ans[T][S]=ans[S][T]=t;//or add(S,T,t),add(T,S,t)
	int cnt1=0,cnt2=0;
	for (int i=l;i<=r;++i)
		if (d[node[i]]) tmp1[++cnt1]=node[i];
		else tmp2[++cnt2]=node[i];
	for (int i=1;i<=cnt1;++i) node[i+l-1]=tmp1[i];
	for (int i=1;i<=cnt2;++i) node[cnt1+l+i-1]=tmp2[i];
	work(l,l+cnt1-1);
	work(l+cnt1,r);
   	return;
}
```

## 4.处理询问
由于询问数很多（ $Q \leq 10^5$ ），很多 dalao 选择了树上倍增的做法，复杂度为 $O(Q \log n)$。

鉴于本人对倍增不太熟练，我换了一种方式。

观察题目数据范围，发现 $n$ 较小，而 $Q$ 较大，所以使用预处理的方式，先将答案处理好。

复杂度为 $O(n^2)$。

我们甚至不用建树（心中有“树”即可），在每一个 work(l,r) 函数中直接统计从 $s$ 所在集合 $S$ 到 $t$ 所在集合 $T$ 的答案。

当前 $S$ 与 $T$ 集合的连接只有 $s$ 与 $t$（其他的都在集合内部）。

则 $\forall u \in S,v \in T$，都有： 
$$ans(u,v)=\min (ans(u,s),ans(s,t),ans(t,v))$$

同时，由于正向与反向都相同，所以不要忘记处理反向。

最后每个询问，输出答案即可。

代码实现时，注意以下几个细节：

1. 每一次最大流时，都要先恢复开始的网络流（即退流）。

1. 插入网络流的边时，要双向插入（题目没有指明哪个是起点）。
1. 下标从 0 开始到 $n$。
1. 每一次最大流时，先保存源点和汇点，防止被覆盖（如果 $s$ 与 $t$ 使用全局变量）（ ~~卡了一个多小时我才发现~~ ）。

其余细节看代码吧。

Code：
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int N=505,M=6005,INF=0x3f3f3f3f;
//M要开4倍，因为正反各要2条边

int h[N],e[M],ne[M],w[M],idx;
int cur[N],q[N],d[N],S,T,n,m;
int node[N],ans[N][N],tmp1[N],tmp2[N];

void add(int a,int b,int c)
{
	e[idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx++;
	e[idx]=a,ne[idx]=h[b],w[idx]=0,h[b]=idx++;
}

bool bfs()
{
	memset(d,0,sizeof d);
	int hh=1,tt=1;
	q[1]=S;cur[S]=h[S];d[S]=1;
	while (hh<=tt)
	{
		int x=q[hh++];
		for (int i=h[x];~i;i=ne[i])
			if (!d[e[i]]&&w[i])
			{
				d[e[i]]=d[x]+1;
				cur[e[i]]=h[e[i]];
				if (e[i]==T) return true;
				q[++tt]=e[i];
			}
	}
	return false;
}

int findflow(int x,int limit)
{
	if (x==T) return limit;
	int flow=0;
	for (int i=cur[x];~i&&flow<limit;i=ne[i])
	{
		cur[x]=i;
		if (d[e[i]]==d[x]+1&&w[i])
		{
			int t=findflow(e[i],min(w[i],limit-flow));
			if (!t) d[e[i]]=-1;
			w[i]-=t,w[i^1]+=t,flow+=t;
		}
	}
	return flow;
}

void init()
{
	for (int i=0;i<idx;i+=2)
		w[i]=(w[i]+w[i^1]),w[i^1]=0;
	return;
}//注意退流的方式

int dinic()
{
	init();
	int r=0,flow;
	while (bfs()) while (flow=findflow(S,INF)) r+=flow;
	return r;
}//Dinic模板

void work(int l,int r)
{
	if (l==r) return ;
	S=node[l],T=node[l+1];
	int t=dinic(),s=node[l],tt=node[l+1];//将源汇点存下来
	ans[T][S]=ans[S][T]=t;
	int cnt1=0,cnt2=0;
	for (int i=l;i<=r;++i)
		if (d[node[i]]) tmp1[++cnt1]=node[i];
		else tmp2[++cnt2]=node[i];
	for (int i=1;i<=cnt1;++i) node[i+l-1]=tmp1[i];
	for (int i=1;i<=cnt2;++i) node[cnt1+l+i-1]=tmp2[i];
	work(l,l+cnt1-1);
	work(l+cnt1,r);//分治
	for (int i=1;i<=cnt1;++i)
		for (int j=1;j<=cnt2;++j)
		{
			int ii=node[i+l-1],jj=node[j+cnt1+l-1];
			ans[jj][ii]=ans[ii][jj]=min(min(ans[ii][s],ans[s][tt]),ans[tt][jj]);
		}//每个点都要处理
	return;
}

int main()
{
	memset(h,-1,sizeof h);
	memset(ans,0x3f,sizeof ans);
	cin>>n>>m;
	int x,y,z;
	while (m--)
	{
		scanf("%d %d %d",&x,&y,&z);
		add(x,y,z);add(y,x,z);//双向边
	}
	for (int i=0;i<=n;++i) node[i]=i;
	work(0,n);//下标从0开始
	int que;cin>>que;
	while (que--)
	{
		scanf("%d %d",&x,&y);
		printf("%d\n",ans[x][y]);
	}
	return 0;
}
```

---

## 作者：Ebola (赞：22)

啊好的，其实这个不是什么很难的算法

首先有一个定理，就是一个$n$个点的图上，两点之间只有$n$中本质不同的最小割。因此一定存在一棵树，满足树上两点的最小割等于原图上两点的最小割。我们把这样的树称之为“最小割树”。建立最小割树的常用算法就是Gomory-Hu Tree

算法大致思路是分治。具体地，在所有点中任取两个作为源汇点，跑一遍Dinic/ISAP求出最小割，最小割将图分成了两个互不连通的割集。我们从源点出发做一遍dfs得到源点割集，dfs时不得越过满流边，因为那是割集分界线。然后在最小割树中，为我们选定的两个点之间连一条边，边权就是求出的最小割。然后递归对两个割集进行一样的操作

注意每次跑Dinic/ISAP时，都要把所有边恢复初始状态，并且不管在哪个分治环节，Dinic/ISAP都应该是针对整个图跑的，而不是当前要处理的这个割集

那么最终我们就连好了$n-1$条边，图上的最小割询问就可以转到树上了。树上两点之间的路径是唯一的，故最小割就是路径边权最小值，用一个简单的树上倍增就可以搞定询问了

不过看很多人也是用的Gomory-Hu Tree算法，但没把最小割树真正地建出来，也没做倍增，我表示比较好奇

由于我们每次最大流是对全图跑的，一共跑了$n$次，所以复杂度是$O(n^3m)$，因为网络流的复杂度几乎不可能卡满，所以能过

```cpp
#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

const int N=510,M=14010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],sum=0,n,m,now=0;
int pdx[N],tdx[N],col[N];
int fa[9][N],mn[9][N],dep[N];

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

namespace GHT
{
    struct Edge{int to,capa,flow,next;} e[M];
    int h[N],sum=-1,s,t;
    int d[N],cur[N];
    bool vis[N];

    void add_edge(int u,int v,int w)
    {
        e[++sum]={v,w,0,h[u]};h[u]=sum;
        e[++sum]={u,w,0,h[v]};h[v]=sum;
    }

    bool BFS()
    {
        queue<int> q;q.push(s);
        memset(vis,0,sizeof(vis));
        vis[s]=1;d[s]=0;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int t=h[u];~t;t=e[t].next)
            {
                int v=e[t].to;
                if(!vis[v]&&e[t].capa>e[t].flow)
                {
                    d[v]=d[u]+1;
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
        return vis[t];
    }

    int DFS(int u,int a)
    {
        if(u==t||a==0) return a;
        int res=0,flow;
        for(int &t=cur[u];~t;t=e[t].next)
        {
            int v=e[t].to;
            if(d[v]!=d[u]+1) continue;
            flow=DFS(v,min(a,e[t].capa-e[t].flow));
            if(!flow) continue;
            e[t].flow+=flow;
            e[t^1].flow-=flow;
            res+=flow;a-=flow;
            if(a==0) break;
        }
        return res;
    }

    int Dinic(int x,int y)
    {
        int flow=0;s=x;t=y;
        for(int i=0;i<=sum;i++) e[i].flow=0;
        while(BFS())
        {
            memcpy(cur,h,sizeof(h));
            flow+=DFS(s,INF);
        }
        return flow;
    }

    void dfs(int u)
    {
        col[u]=now;
        for(int t=h[u];~t;t=e[t].next)
            if(e[t].capa>e[t].flow&&col[e[t].to]!=now)
                dfs(e[t].to);
    }

    void build(int l,int r)
    {
        if(l>=r) return;
        int x=pdx[l],y=pdx[l+1];
        int cut=Dinic(x,y);
        now++;dfs(x);int p=l,q=r;
        for(int i=l;i<=r;i++)
            if(col[pdx[i]]==now) tdx[p++]=pdx[i];
            else tdx[q--]=pdx[i];
        for(int i=l;i<=r;i++) pdx[i]=tdx[i];
        ::add_edge(x,y,cut);
        ::add_edge(y,x,cut);
        build(l,p-1);build(q+1,r);
    }
}

void dfs(int u,int la)
{
    for(int i=1;i<=8;i++)
    {
        fa[i][u]=fa[i-1][fa[i-1][u]];
        mn[i][u]=min(mn[i-1][u],mn[i-1][fa[i-1][u]]);
    }
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la) continue;
        dep[v]=dep[u]+1;
        mn[0][v]=e[t].capa;
        fa[0][v]=u;dfs(v,u);
    }
}

int getcut(int x,int y)
{
    int res=INF;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=8;i>=0;i--)
        if(dep[fa[i][x]]>=dep[y])
        {
            res=min(res,mn[i][x]);
            x=fa[i][x];
        }
    if(x==y) return res;
    for(int i=8;i>=0;i--)
        if(fa[i][x]!=fa[i][y])
        {
            res=min(res,mn[i][x]);
            res=min(res,mn[i][y]);
            x=fa[i][x];y=fa[i][y];
        }
    res=min(res,min(mn[0][x],mn[0][y]));
    return res;
}

int main()
{
    int u,v,w,q;
    scanf("%d%d",&n,&m);
    memset(GHT::h,-1,sizeof(GHT::h));
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        GHT::add_edge(u,v,w);
    }
    for(int i=1;i<=n;i++) pdx[i]=i;
    GHT::build(1,n);
    dep[1]=1;dfs(1,0);
    for(scanf("%d",&q);q;q--)
    {
        scanf("%d%d",&u,&v);
        printf("%d\n",getcut(u,v));
    }
    return 0;
}
```

---

## 作者：Eznibuil (赞：21)

Upd on 2023.3.1：些许补充和修复。

Upd on 2023.5.2：为了方便检测 Gomory-Hu 算法的正确性，造了一道[板子](/problem/U278541)。

Upd on 2024.5.6：修正定理 1 的证明错误。

Upd on 2024.9.13：题解区 KaTeX 升级，进行小修复。

前言：很难相信 Gomory-Hu Tree 的板子题没人写 Gomory-Hu 算法的题解。~~不过话说回来这题也没必要用 Gomory-Hu Tree。~~

写个更易懂（也许？）的 Gomory-Hu 算法的粗略证明放这里。不太清晰（毕竟本人也不怎么懂），若需要好一点的请参见参考文献[2]。

最小割树（Gomory-Hu Tree），满足原图上的两点间的最小割大小和方案正好有一种是树上对应两点间的最小割大小和方案。

下面定义：图 $G=(V,E)$，$V$ 为点集，$E$ 为边集，$\lambda(x,y)$ 表示 $x,y$ 之间的最小割。
### Lemma 1
任取三点 $a,b,c$，有 $\lambda(a,b)\ge\min(\lambda(a,c),\lambda(c,b))$。
>证明：考虑 $a,b,c$ 之间的割：设切断 $a\leftrightarrow b$ 和 $a\leftrightarrow c$ 的最小的割权值是 $\alpha$，切断 $a\leftrightarrow b$ 和 $b\leftrightarrow c$ 的最小的割权值是 $\beta$，切断 $a\leftrightarrow c$ 和 $b\leftrightarrow c$ 的最小的割权值是 $\gamma$，则原式化为 $\min(\alpha,\beta)\ge\min(\min(\alpha,\gamma),\min(\beta,\gamma))$，得证。

由此可得 $\lambda(a,b),\lambda(a,c),\lambda(b,c)$ 三者中必有两者相等，且另一个大于等于相等的两者。

然后立即得出以下推论：
#### Corollary 1
对于任意互不相同的 $k$ 个点 $s_1,s_2,\cdots,s_k\in V$，有 $\lambda(s_1,s_k)\ge\min(\lambda(s_1,s_2),\lambda(s_2,s_3),\cdots,\lambda(s_{k-1},s_k))$。
### Theorem 1
若一棵树的每条边满足边权为最小割且割断此边分出的点集与最小割割出的点集相同，那么取任意两点 $u,v$，令 $s,t$ 为 $u,v$ 的路径上最小的边，则 $\lambda(u,v)=\lambda(s,t)$。
>证明：根据引理 1，$\lambda(u,v)\ge\lambda(s,t)$；另一方面，根据此树的定义，必然 $s,t$ 的最小割可以成为 $u,v$ 的割，有 $\lambda(u,v)\le\lambda(s,t)$。综上得证。
>
>注：此树即为 Gomory-Hu Tree。

定义一个割 $W$（一边的点的点集）的权函数 $\delta(W)$ 为所有满足一端点在 $W$ 而另一端点不在 $W$ 的边的边权和。
### Lemma 2.1
$\delta(W)$ 是对称函数，亦即，$\delta(W)=\delta(V-W)$。
>证明：显然割两侧点集的权相等。

### Lemma 2.2
$\delta(W)$ 满足 submodular，亦即，$\delta(A)+\delta(B)\ge\delta(A\cap B)+\delta(A\cup B)$。
>证明：画出 Venn 图易证。

### Lemma 2.3
$\delta(W)$ 满足 posi-modular，亦即，$\delta(A)+\delta(B)\ge\delta(A-B)+\delta(B-A)$。
>证明：根据引理 2.1 和引理 2.2：
>$$\begin{aligned}\delta(A)+\delta(B)&=\delta(V-A)+\delta(B)\\&\ge\delta((V-A)\cap B)+\delta((V-A)\cup B)\\&=\delta(B-A)+\delta(V-(A-B))\\&=\delta(B-A)+\delta(A-B)\end{aligned}$$

### Key Lemma
令 $W$ 为 $s,t$ 之间的一个最小割一侧的点集，则对于任意点对 $u,v\in W,u\ne v$，存在 $u,v$ 间的一个最小割一侧的点集 $X$ 使得 $X\subseteq W$。
>证明：假设 $s\in W,s\in X,u\in X$，且 $X$ 不是 $W$ 的子集。
>
>1. $t\notin X$。根据引理 2.2 的 submodular 性质，$\delta(X)+\delta(W)\ge\delta(X\cap W)+\delta(X\cup W)$。另一方面，$X\cap W$ 是一个 $u,v$ 间的割，所以 $\delta(X\cap W)\ge\delta(X)$；同理 $\delta(X\cup W)\ge\delta(W)$。由此可得以上均取等号，则 $X\cap W$ 同样是 $u,v$ 最小割且满足其为 $W$ 的子集。
>1. $t\in X$。根据引理 2.3 的 posi-modular 性质，$\delta(X)+\delta(W)\ge\delta(X-W)+\delta(W-X)$，同上可得 $W-X$ 是 $u,v$ 间的最小割且满足其为 $W$ 的子集。

由 Key Lemma 可以发现最小割可以互不交叉，这是 Gomory-Hu Tree 存在的基础。
### Gomory-Hu 算法
以下是参考文献[1]给出的实现：（传入的 $G$ 是图，$R$ 是点集，返回的 $T$ 是树，$C_r$ 是划分）
$$\begin{aligned}&\underline{\text{{\bf function} GomoryHuAlg(G,R)\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad}}\\&\textbf{if }|R|=1\textbf{ then}\\&\quad\textbf{return }T=(R,\varnothing),C_r=V\\&\textbf{else}\\&\quad\text{令 }r_1,r_2\in R,r_1\ne r_2,\text{且令 }W\text{ 为 }r_1,r_2\text{ 最小割一侧的点集},r_1\in W\\\\&\quad\langle\text{创建两个子问题}\rangle\\&\quad G_1=G\text{ 把 }V-W\text{ 缩成一个点 }v_1;R_1=R\cap W\\&\quad G_2=G\text{ 把 }W\text{ 缩成一个点 }v_2;R_2=R-W\\\\&\quad\langle\text{现在递归}\rangle\\&\quad T_1,(C^1_r|r\in R_1)=\operatorname{GomoryHuAlg}(G_1,R_1)\\&\quad T_2,(C^2_r|r\in R_2)=\operatorname{GomoryHuAlg}(G_2,R_2)\\\\&\quad\langle\text{注意 }r',r''\text{ {\bf不一定}是 }r_1,r_2\text{！}\rangle\\&\quad\text{令 }r'\text{ 为满足 }v_1\in C^1_{r'}\text{ 的点}\\&\quad\text{令 }r''\text{ 为满足 }v_2\in C^2_{r''}\text{ 的点}\\\\&\quad\langle\text{现在合并，并把 }v_1,v_2\text{ 从划分中去除}\rangle\\&\quad T=(R_1\cup R_2,E_{T_1}\cup E_{T_2}\cup\{r'-r''\})\qquad\text{注：此处的 }R_1\cup R_2\text{ 就是 }R\\&\quad\textbf{for }r\in R_1,r\ne r',C_r=C^1_r\\&\quad\textbf{for }r\in R_2,r\ne r'',C_r=C^2_r\\&\quad C_{r'}=C_{r'}-\{v_1\}\\&\quad C_{r''}=C_{r''}-\{v_2\}\\&\quad\textbf{return }T,C_r\\&\textbf{end if}\end{aligned}$$
### Theorem 2
上述算法对于一个输入的无向非负权图 $G=(V,E)$，一定可以返回一个原图的 Gomory-Hu Tree。
>证明：使用归纳法，首先当 $|V|=1$ 时树中只有唯一的一点，因此符合要求，接下来考虑 $|V|>1$ 的情况。
>
>首先划分然后递归，递归后返回了两个子图的 Gomory-Hu Tree，根据 Key Lemma，其他的不用管，因为不会影响，于是证明加上去的那条边合法即可，也就是 $\lambda(r_1,r_2)=\lambda(r',r'')$。
>
>可以发现 $r_1,r_2$ 之间的最小割一定是 $r',r''$ 之间的割，所以我们有 $\lambda(r_1,r_2)\ge\lambda(r',r'')$。分析缩了点的图，可以得到 $\lambda(r_1,r')\ge\lambda(r_1,r_2)$ 以及 $\lambda(r'',r_2)\ge\lambda(r_1,r_2)$。
>
>所以根据引理 1，$\lambda(r',r'')\ge\min(\lambda(r',r_1),\lambda(r_1,r_2),\lambda(r_2,r''))=\lambda(r_1,r_2)$，而前面已经得到 $\lambda(r_1,r_2)\ge\lambda(r',r'')$，综上证毕。

所以很快可以得出以下推论：
#### Corollary 2
对于一个输入的无向非负权图 $G=(V,E)$，Gomory-Hu 算法会正好执行 $|V|-1$ 次求最小割。

---
回到这道题，具体实现 Gomory-Hu 算法时，可以用一个全局的图和一个映射来模拟缩点，传入一个记录点集的 `std::vector<int>`，用全局 `bool[][]` 记录划分，用全局的 `std::vector<std::pair<std::pair<int,int>,int>>` 记录树边集。

可以发现其他题解的 Gusfield 算法和 Gomory-Hu 算法非常相似，除了连边时直接在求最小割的两个点之间连而且无需缩点。同样可以证明 Gusfield 算法给出了一个等价流树（equivalent flow tree），满足任意两点的最大流即为树上两点的最大流。

注 1：参考文献[2]给出了两种算法的非递归形式，可以去看一下。大意就是反正是拆分点集，可以用枚举每一个没有拆分完全的点集进行拆分。代码难度略低于递归形式。

注 2：显然 Gusfield 比 Gomory-Hu 好写而且这道题不要求方案。~~但这不是 Gomory-Hu 板子没人用 Gomory-Hu 写的理由。~~

下面是 Gomory-Hu 算法的基于 SAP 的实现，语言为 C++14，时间复杂度 $O(n^2+n\tau)$，其中 $\tau$ 是求一次最小割（最大流）的时间复杂度。

使用了很多 `std::vector::emplace_back()` 看似效率比较低，实际上因为缩点的缘故速度和 Gusfield 差不多快，甚至更快。
```cpp
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
const int N=2001,M=100001;
bool vis[N],C[N][N];
int f,s,t,len,las[N],nex[M],en[M],vol[M],he,ta,q[N],dis[N],cnt[N],maxfl,sh[N],fa[N],ans[N][N];
#define addedg(e,d,g) (nex[len]=las[e],las[e]=len,en[len]=d,vol[len++]=g)
#define addfl(e,d,g) (addedg(e,d,g),addedg(d,e,g))
std::vector<int>rs[N];
std::vector<std::pair<std::pair<int,int>,int>>T;
bool bfs()
{
	int x;
	for(int i=he=ta=0;i<f;i++)
		vis[sh[i]]=0,cnt[sh[i]]=dis[sh[i]]=0;
	vis[q[ta++]=sh[t]]=1,dis[sh[t]]=0;
	while(he<ta)
	{
		cnt[dis[x=q[he++]]]++;
		for(int _:rs[x])
			for(int i=las[_];~i;i=nex[i])
				if(!vis[sh[en[i]]])
					vis[sh[en[i]]]=1,dis[sh[en[i]]]=dis[x]+1,q[ta++]=sh[en[i]];
	}
	assert(sh[s]!=sh[t]);
	return vis[sh[s]];
}
int dfs(int x,int fl)
{
	if(x==sh[t])
		return maxfl+=fl,fl;
	int d=0;
	for(int _:rs[x])
		for(int i=las[_],j;~i;i=nex[i])
			if(vol[i]&&dis[sh[en[i]]]==dis[x]-1)
			{
				d+=j=dfs(sh[en[i]],vol[i]<fl-d?vol[i]:fl-d),vol[i]-=j,vol[i^1]+=j;
				if(d==fl)
					return d;
			}
	cnt[dis[x]]--;
	if(!cnt[dis[x]])
		dis[sh[s]]=f;
	return cnt[++dis[x]]++,d;
}
void tag(int x)
{
	vis[x]=1;
	for(int _:rs[x])
		for(int i=las[_];~i;i=nex[i])
			if(vol[i^1]&&!vis[sh[en[i]]])
				tag(sh[en[i]]);
	return;
}
int mf(int S,int T)
{
	s=S,t=T;
	for(int i=maxfl=0;i<len;i+=2)
		vol[i]=vol[i^1]=vol[i]+vol[i^1]>>1;
	if(bfs())
		while(dis[sh[s]]<f)
			dfs(sh[s],1000000000);
	for(int i=0;i<f;i++)
		vis[sh[i]]=0;
	return tag(sh[t]),maxfl;
}
void GomoryHu(const std::vector<int>&R)
{
	if(R.size()==1)
	{
		for(int i=0;i<f;i++)
			C[R[0]][sh[i]]=1;
		return;
	}
	std::vector<int>R1,R2;
	bool v[N];
	int r1=R[0],r2=R[1],d=mf(r1,r2),tmp[N],rp,rpp;
	for(int i=0;i<f;i++)
		tmp[i]=-1,v[i]=vis[i];
	for(int i:R)
		if(vis[sh[i]])
			R2.emplace_back(i);
		else
			R1.emplace_back(i);
	for(int i=0,k;i<f;i++)
		if(v[k=sh[i]]&&k!=r2)
			for(int j=rs[k].size()-1;~j;j--)
				tmp[rs[k][j]]=sh[rs[k][j]],sh[rs[k][j]]=r2;
	for(int i=0;i<f;i++)
		rs[i].clear();
	for(int i=0;i<f;i++)
		rs[sh[i]].emplace_back(i);
	GomoryHu(R1);
	for(int i=0;i<f;i++)
		if(~tmp[i])
			sh[i]=tmp[i],tmp[i]=-1;
	for(int i=0;i<f;i++)
		rs[i].clear();
	for(int i=0;i<f;i++)
		rs[sh[i]].emplace_back(i);
	for(int i=0,k;i<f;i++)
		if(!v[k=sh[i]]&&k!=r1)
			for(int j=rs[k].size()-1;~j;j--)
				tmp[rs[k][j]]=sh[rs[k][j]],sh[rs[k][j]]=r1;
	for(int i=0;i<f;i++)
		rs[i].clear();
	for(int i=0;i<f;i++)
		rs[sh[i]].emplace_back(i);
	GomoryHu(R2);
	for(int i=0;i<f;i++)
		if(~tmp[i])
			sh[i]=tmp[i];
	for(int i=0;i<f;i++)
		rs[i].clear();
	for(int i=0;i<f;i++)
		rs[sh[i]].emplace_back(i);
	for(int i:R1)
		if(C[i][r2])
		{
			rp=i,C[i][r2]=0;
			break;
		}
	for(int i:R2)
		if(C[i][r1])
		{
			rpp=i,C[i][r1]=0;
			break;
		}
	T.emplace_back(std::make_pair(rp,rpp),d);
	return;
}
void getans(int x,int y)
{
	for(int i=las[y];~i;i=nex[i])
		if(en[i]!=fa[y])
			fa[en[i]]=y,ans[x][en[i]]=(ans[x][y]<vol[i]?ans[x][y]:vol[i]),getans(x,en[i]);
	return;
}
int main()
{
	int n,m,q,u,v,w;
	std::vector<int>R;
	scanf("%d%d",&n,&m),f=n+1;
	for(int i=0;i<f;i++)
		las[i]=-1,R.emplace_back(i),sh[i]=i,rs[i].emplace_back(i);
	while(m--)
		scanf("%d%d%d",&u,&v,&w),addfl(u,v,w);
	GomoryHu(R);
	for(int i=len=0;i<f;i++)
		las[i]=-1;
	for(auto j:T)
		addfl(j.first.first,j.first.second,j.second);
	for(int i=0;i<f;i++)
		fa[i]=-1,ans[i][i]=1e9,getans(i,i);
	scanf("%d",&q);
	while(q--)
		scanf("%d%d",&u,&v),printf("%d\n",ans[u][v]);
	return 0;
}
```
### 参考文献
1. <https://courses.engr.illinois.edu/cs598csc/sp2010/Lectures/Lecture6.pdf>
1. 《浅谈无向图最小割问题的一些算法及应用》（绍兴一中王文涛，[2016 年国集论文](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf)）

---

## 作者：EnofTaiPeople (赞：15)

首先明确最小割树的定义：对于任意树上的边 $(u,v)$，删除图上的点 $u,v$，树上的边 $(u,v)$，之后，图会分成两部分，一部分在树上与 $u$ 连通，另一部分在树上与 $v$ 连通，树上边 $(u,v)$ 的边权为图上 $u,v$ 之间的最小割。

同时，图上任意两点的最小割是它们的树上路径边权最小值。

于是，只要将树建出来，就可以实现 $O(1)$ 查询最小割啦！

问题来了：怎么建树？

事实上，最小割树的性质告诉我们，其实只要不断加边就可以了，具体做法是：

1. 定义 $solve(l,r)$ 为将区间 $[l,r]$的节点建树；
2. 求出 $MinCut(a_l,a_r)$；
3. 判断 $[l,r]$ 中那些点与 $a_l$ 连通，那些点与 $a_r$ 连通，并将其划分为 $[l,lc],[rc,r]$，可以用最后一次广搜节点是否被搜到为标准判断；
4. 递归：$solve(l,lc),solve(rc,r)$；
5. $n$ 遍深搜求出树上任意两点路径上的最小边权。

然后查询就可以啦！

## $~~~~~~~~~~~~~~~~ code$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505,M=3005;
char buf[M+5],*p1,*p2,c;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	int an=0,f=1;while(!isdigit(c=gc))if(c=='-')f=-f;
	do an=an*10+(48^c);while(isdigit(c=gc));return an*f;
}
int a[N],b[N],d[N],n,m,s,t,Q,q[N],l,r;
vector<int>lk[N];
int w[M],ed[M],cnt,now[N];
struct Eg{int u,v,w;}g[N];
int ans[N][N],*add;
inline bool bfs(){
	int i,x,y;
	for(i=1;i<=n;++i)now[i]=d[i]=0;
	q[l=r=d[s]=1]=s;
	while(l<=r){
		x=q[l++];
		for(int i:lk[x])
			if(w[i]&&!d[y=ed[i]]){
				d[q[++r]=y]=d[x]+1;
				if(y==t)return 1;
			}
	}return 0;
}
int Dinic(int x,int flow){
	if(x==t)return flow;int i,y,k,rest=flow;
	for(int &g=now[x],sz=lk[x].size();g<sz;++g)
		if(w[i=lk[x][g]]&&d[y=ed[i]]==d[x]+1)
			if(k=Dinic(y,min(w[i],rest))){
				w[i]-=k,w[i^1]+=k;
				if(!(rest-=k))return flow;
			}
	d[x]=0;
	return flow-rest;
}
inline void solve(int l,int r){
	if(l>=r)return;int i,lc=l-1,rc=r+1;
	s=a[l],t=a[r],g[++cnt]={a[l],a[r]};
	while(bfs())g[cnt].w+=Dinic(s,INT_MAX);
	for(i=l;i<=r;++i)
		if(d[a[i]])b[++lc]=a[i];
		else b[--rc]=a[i];
	for(i=l;i<=r;++i)a[i]=b[i];
	for(i=1;i<=m;++i){
		w[i+i]+=(w[i+i+1]-w[i+i])>>1;
		w[i+i+1]=w[i+i];
	}solve(l,lc),solve(rc,r);
}
void dfs(int x,int ad,int pr){
	add[x]=ad;int y;
	for(int i:lk[x])
		if((y=ed[i])!=pr)
			dfs(y,min(ad,w[i]),x);
}
int main(){
	n=read()+1,m=read();int i,x,y;
	for(i=1;i<=m;++i){
		x=read()+1,y=read()+1;
		w[i+i]=w[i+i+1]=read();
		ed[i+i]=x,lk[y].push_back(i+i);
		ed[i+i+1]=y,lk[x].push_back(i+i+1);
	}
	for(i=1;i<=n;++i)a[i]=i;
	solve(1,n);
	for(i=1;i<=n;++i)lk[i].clear();
	for(i=1;i<=cnt;++i){
		w[i+i]=w[i+i+1]=g[i].w;
		ed[i+i]=g[i].v,lk[g[i].u].push_back(i+i);
		ed[i+i+1]=g[i].u,lk[g[i].v].push_back(i+i+1);
	}
	for(x=1;x<=n;++x)
		add=ans[x],dfs(x,INT_MAX,-1);
	Q=read();
	while(Q--)printf("%d\n",ans[read()+1][read()+1]);
	return 0;
}
```

---

## 作者：旋转卡壳 (赞：8)

找个题解抄了抄 分享下思路

前排提示 我写的是**ISPA+倍增** 开了O2 390ms ~~(当时还是rk1)~~

------------
关于第9个点WA 我当时找了大半天BUG 没找到... 后来把

```
for(register int i=1;i<=n;++i) cur[i]=head[i];

```
改成
```
for(register int i=0;i<=n;++i) cur[i]=head[i];

```
就AC了 所以说??? 黑人问号.jpg

------------
我们先看题目 知道它要我们求的是给定n个点m条边的无向图 问对于两个点(u,v)

删掉图中的一些带权边 求最小的能让两个点不连通的代价

可能一开始看有点懵 没有想法(个屁 题目都明示了)

我们先看简化版本

对于![1](https://cdn.luogu.com.cn/upload/pic/45210.png)

(用画图画的 将就着看吧) 

我们要求(1,4)的最小割 可以直接看出是5 对吧 就是断边(2,3)

那对于![2](https://cdn.luogu.com.cn/upload/pic/45213.png)

我们要求(1,8)的最小割 从图中看出是20+20+10=50 对吧 因为三条路径都要断掉才行

于是我们通过两个例子

可能就能看出**两个点的最小割就是两个点之间的最大流**了

(写到这里我才发现我在写废话)

那根据题意 我们是要求Q次两个点的最大流? 其实想一想感觉就爆炸了是不是

那我们继续看这个栗子 我们可以发现(神仙的灵光一闪)

**对于(2,8)的最小割 就等于(1,8)的最小割**

我们可以这样想 具体不会证明...

对于1-2-3-8 如果最小割的边为(1,2) 那1和2就不联通了

因为边(1,2)能通过的流量减去最小割后为0

而只要能联通 就说明它俩到同一点8的最小割相等

基于这种想法 我们可以把上图转化成

![3](https://cdn.luogu.com.cn/upload/pic/45216.png)

红框内的点到蓝框内的点的最小割都是50

那还有一种情况就是同颜色的框内的两个点的最小割

其实转换一下 我们只需要按照同样的方法**分治**做下来就可以了

比如6到8的最小割是30(注意在图上1和6是相连的 在上面的图里只是**省略**掉了)

然后两个点连一条边 一共就有**n-1**条边 用倍增维护一下最小值就行

为什么要用倍增维护最小值呢

比如求(2,8)的最小割 我们从上面的图看得出来是50 但我们实际查询的时候

**并不知道1,2是同一个联通块 而其他点是另一个联通块 且两个联通块的最小割为50**

**有可能1是一个联通块而其他点是一个联通块 那么最小值就不是(2,8)而是(1,2)了**

所以需要我们维护最小值

------------
那接下来讲一下具体代码的实现

首先我们正常存网络流的图 因为题目要求多次不同点间的最大流

所以每次求最大流每条边的流量容量都要**更新**

比如![4](https://cdn.luogu.com.cn/upload/pic/45218.png)

我们先求(1,3)的最小割 然后不重置 就会得到(1,2)的最小割为50 显然是错的

对于找联通块 我们直接**暴力dfs 打标记**即可

这里还用到了**类似归并排序的方法**(原来我不会这是啥)

比如数组a[1,3]里的点都是在一个联通块里的

我们求a[1],a[2]的最小割后得到a[1],a[3]在一个联通块

就用一个tmp数组把同一个联通块里的排在左边就行了 然后复制回a数组

具体看代码吧 我的语文太弱了

```
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn=6e2;
const int maxm=2e3;
const int inf=2047483647;

int n,m,q;

inline int read() {
    int a=0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') a=(a<<1)+(a<<3)+c-'0',c=getchar();
    return a;
}

//存生成出来的树 
int edgeNum,head[maxn],to[maxm<<1],next[maxm<<1],w[maxm<<1]; 
    
inline void add(int u,int v,int c) {
    next[++edgeNum]=head[u];head[u]=edgeNum;
    to[edgeNum]=v;w[edgeNum]=c;
}

int cnt,p[maxn],tmp[maxn],S[maxn];
//cnt代表现在是第几个联通块
//p[i]代表第i个点上的点的编号 
//tmp数组用于复制排序p数组
//S[u]表示u在的联通块编号 

struct GHT {
    int s,t,maxFlow,cur[maxn];
    
    int edgeNum=-1,head[maxn],to[maxm<<1],next[maxm<<1];
    int w[maxm<<1],f[maxm<<1];
	//w[i]表示第i条边可以通过的最大流量
	//f[i]表示第i条边目前可以通过的最大流量 
    
    GHT() {memset(head,-1,sizeof(head));}
    
    inline void add_edge(int u,int v,int c) {
        next[++edgeNum]=head[u];head[u]=edgeNum;
        to[edgeNum]=v;w[edgeNum]=c;
    }
    
    int dep[maxn],gap[maxn];
    
    inline void bfs() {
        memset(dep,0,sizeof(dep));memset(gap,0,sizeof(gap));
        dep[t]=gap[1]=1;queue<int> Q;Q.push(t);
        while(!Q.empty()) { int u=Q.front();Q.pop();
            for(int i=head[u];i!=-1;i=next[i]) if(!dep[to[i]])
                ++gap[dep[to[i]]=dep[u]+1],Q.push(to[i]);
        }
    }
    
    int dfs(int u,int lastFlow) {
        int used=0,minFlow=0;
        if(u==t) {maxFlow+=lastFlow;return lastFlow;}
        for(int &i=cur[u];i!=-1;i=next[i]) 
            if(f[i]&&dep[to[i]]+1==dep[u])
                if(minFlow=dfs(to[i],min(lastFlow-used,f[i])))
                {	f[i]-=minFlow;f[i^1]+=minFlow;
                    if((used+=minFlow)==lastFlow) return used;
                }
        if(!(--gap[dep[u]++])) dep[s]=n+1;
        ++gap[dep[u]];return used;
    }
    
    inline int ISAP(int x,int y) {
        for(register int i=0;i<=edgeNum;++i) f[i]=w[i];
        maxFlow=0;s=x;t=y;bfs();while(dep[s]<=n) { //每次ISAP都要初始化 
            for(register int i=0;i<=n;++i) cur[i]=head[i];
            dfs(s,inf);
        }return maxFlow;
    }
    
    void dfs(int u) { S[u]=cnt;
        for(int i=head[u];i!=-1;i=next[i])
            if(f[i]&&S[to[i]]!=cnt) dfs(to[i]);
            //可以联通到to[i]并且to[i]没有访问过 
    }
    
    void build(int l,int r) {
        if(l>=r) return ; //只有一个点就退出 
        int x=p[l],y=p[l+1],cut=ISAP(x,y),L=l,R=r;
        ++cnt;dfs(x);add(x,y,cut);add(y,x,cut);
        //找联通块与给要生成的树连边 
        for(register int i=l;i<=r;++i) tmp[S[p[i]]==cnt?L++:R--]=p[i];
        //在找到的联通块里的点从左放到右边 
        //不在联通块里的点从右放到左边
        for(register int i=l;i<=r;++i) p[i]=tmp[i]; //复制回来
        build(l,L-1);build(R+1,r);
        //边界看看就懂了 
    }
}T;

int dep[maxn],fa[maxn][9],Min[maxn][9];

void dfs(int u,int fat) {
    for(register int i=1;i<=8;++i)
        fa[u][i]=fa[fa[u][i-1]][i-1],
        Min[u][i]=min(Min[u][i-1],Min[fa[u][i-1]][i-1]);
    for(int i=head[u];i;i=next[i]) if(to[i]!=fat) {
        Min[to[i]][0]=w[i];fa[to[i]][0]=u;
        dep[to[i]]=dep[u]+1;dfs(to[i],u);
    }
}

inline int getCut(int x,int y) {
    int ans=inf;if(dep[x]<dep[y]) x^=y^=x^=y;
    for(register int i=8;i>=0;--i)
        if(dep[fa[x][i]]>=dep[y])
            ans=min(ans,Min[x][i]),x=fa[x][i];
    if(x!=y) {
        for(register int i=8;i>=0;--i)
            if(fa[x][i]!=fa[y][i])
                ans=min(ans,min(Min[x][i],Min[y][i])),
                x=fa[x][i],y=fa[y][i];
        ans=min(ans,min(Min[x][0],Min[y][0]));
    }return ans;
}

int main() {
    n=read();m=read();
    for(register int i=1;i<=n;++i) p[i]=i;
    for(register int i=1;i<=m;++i) {
        int u=read(),v=read(),c=read();
        T.add_edge(u,v,c);T.add_edge(v,u,c);
    }T.build(1,n);dep[1]=1;dfs(1,0);q=read();
    for(register int i=1;i<=q;++i) {
        int u=read(),v=read();
        printf("%d\n",getCut(u,v));
    }return 0;
}

```















---

## 作者：杨铠远 (赞：6)

有位神犇说过：啊好的，其实这个不是什么很难的算法

在图上每次拽两个点（源点，汇点）出来，跑一遍网络流

这时候流量已经跑满的边将整个图划分为两部分

在新图上将s和t连起来，边权为最小割

递归处理两部分图

查询时输出两点之间边权最小值

(至于证明，好吧这就是Gomory-Hu Tree算法）

维护两点之间边权最小值用倍增较好

## 但LCT也就一个log!

具体细节详见代码

```cpp
//Code by : Y-k-y
//这道题的一个坑点就是网络流每次跑之前要先退流（就是还原）
//因为是无向图，建边时正边反边都要有流量
//自认为dinic板子敲得还可以 。。。 
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <set>
#define ll long long
const int N=20010;
const int inf=1<<30;
using namespace std;
inline int rnd(){
	int res=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
inline void wr(int x){
	if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');
}
int tot=1,s,t,n,m,col,num;
struct pp{
	int v,nxt,w,up;
}edge[N];
int head[N],d[N],a[N],co[N],b[N];
int fa[N],ch[N][2],rev[N],sta[N],sum[N],val[N];
inline void add(int u,int v,int w){//记录流量 
	edge[++tot].nxt=head[u],head[u]=tot;
	edge[tot].v=u,edge[tot].up=w;
	edge[++tot].nxt=head[v],head[v]=tot;
	edge[tot].v=u,edge[tot].up=w;
}
struct L_C_T_{//lct部分：用拆点技巧  
	inline int get(int x){
		return x==ch[fa[x]][1]||x==ch[fa[x]][0];
	}
	inline int chk(int x){
		return x==ch[fa[x]][1];
	}
	inline void pushup(int x){
		sum[x]=min(min(sum[ch[x][0]],sum[ch[x][1]]),val[x]);
	}
	inline void filp(int x){
		swap(ch[x][0],ch[x][1]);rev[x]^=1;
	}
	inline void pushdown(int x){
		if(!rev[x])return;
		if(ch[x][0])filp(ch[x][0]);
		if(ch[x][1])filp(ch[x][1]);
		rev[x]=0;
	}
	inline void zhuan(int x){
		int y=fa[x],z=fa[y],k=chk(x),w=ch[x][k^1];
		if(get(y))ch[z][chk(y)]=x;ch[y][k]=w,ch[x][k^1]=y;
		if(w)fa[w]=y;fa[y]=x,fa[x]=z;
		pushup(y);pushup(x);
	}
	inline void splay(int x){
		int y=x,top=0;sta[++top]=y;
		while(get(y))sta[++top]=y=fa[y];
		while(top)pushdown(sta[top--]);
		while(get(x)){
			int y=fa[x];
			if(get(y))
				zhuan(chk(x)==chk(y)?y:x);
			zhuan(x);
		}
		pushup(x);
	}
	inline void Access(int x){
		for(int y=0;x;x=fa[y=x]){
			splay(x);ch[x][1]=y,pushup(x);
		}
	}
	inline void makeroot(int x){
		Access(x);splay(x);filp(x);
	}
	inline void split(int x,int y){
		makeroot(x);Access(y);splay(y);
	}
	inline int findroot(int x){
		Access(x);splay(x);
		while(ch[x][0])pushdown(x),x=ch[x][0];
		return x;
	}
	inline void link(int x,int y){
		makeroot(x);if(findroot(y)!=x)fa[x]=y;
	}
}LCT;//LCT一定要手敲，不要粘板子！（好吧，也可以，不要像我一样调试时将cout和正文一块删了就行
inline int bfs(){
	queue<int>q;q.push(s);
	memset(d,0,sizeof(d));
	d[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v;
			if((!d[v])&&edge[i].w){
				d[v]=d[u]+1;
				q.push(v);
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
inline int dinic(int u,int flow){
	if(u==t)return flow;
	int rest=flow,k;
	for(int i=head[u];i&&rest;i=edge[i].nxt){
		int v=edge[i].v;
		if(d[v]==d[u]+1&&edge[i].w){
		k=dinic(v,min(rest,edge[i].w));
		if(!k)d[v]=0;
		edge[i].w-=k;
		edge[i^1].w+=k;
		rest-=k;
		}
	}
	return flow-rest;
}
inline int work(int x,int y){
	s=x,t=y;//确定源点和汇点 
	for(int i=2;i<=tot;i++)edge[i].w=edge[i].up;//还原 
	int ans=0;
	while(bfs())ans+=dinic(s,inf);
	return ans;
}
inline void dfs(int u){
	co[u]=col;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(co[v]!=col&&edge[i].w){
			dfs(v);
		}
	}
}
inline void build(int l,int r){
	if(l>=r)return;
	int x=a[l],y=a[l+1];
	int Val=work(x,y);
	int New=++num;//拆点 num初始成n 
	sum[New]=val[New]=Val;//将边权变为点权 
	LCT.link(x,New);LCT.link(New,y);
	col++;dfs(x);//割边组成的割集将图分成两部分 将和s在同一部分的点染色 
	int num1=l,num2=r;
	for(int i=l;i<=r;i++){
		if(co[a[i]]==col){
			b[num1++]=a[i];
		}
		else{
			b[num2--]=a[i];
		}
	}
	for(int i=l;i<=r;i++){
		a[i]=b[i];
	}
	build(l,num1-1);build(num2+1,r);//递归建图 
}
int main(){
	n=rnd();m=rnd();int x,y,z;num=n;
	while(m--){
		x=rnd();y=rnd();z=rnd();
		add(x,y,z);add(y,x,z);
	}	
	for(int i=1;i<=n;i++){//build的辅助数组 
		a[i]=i;
	}
	memset(sum,0x3f,sizeof(sum));//LCT维护最小值一定要初始化 
	memset(val,0x3f,sizeof(val));
	build(1,n);
	m=rnd();
	while(m--){
		x=rnd();y=rnd();
		LCT.split(x,y);
		wr(sum[y]);puts("");
	}
	return 0;
}拜拜！
```


---

## 作者：wxzzzz (赞：5)

该文截自[最小割树](https://www.cnblogs.com/wangxuzhou-blog/p/17995020/high-order-graph-theory#%E6%9C%80%E5%B0%8F%E5%89%B2%E6%A0%91)。

最小割树可以以 $O(n^3m)$ 的时间预处理，以 $O(\log n)$ 的复杂度查询任意两点之间的最小割。

### 思路

令 $\operatorname{mincut}(u,v)$ 表示 $u\to v$ 的最小割。

考虑分治建最小割树。

1. 对于分治区间 $l,r$，其点集为 $p_l\sim p_r$。

1. 求出 $p_l\to p_r$ 的最小割，在最小割树上连边 $(p_l,p_r,\operatorname{mincut}(p_l,p_r))$。

1. 此时 $p_l\sim p_r$ 会被割成两个集合，对这两个集合继续分治建树。

对于 $x,y$，$\operatorname{mincut}(x,y)$ 为原图最小割树上 $x\to y$ 简单路径上的边权最小值，可以建出最小割树的 kruskal 重构树求解。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, s, t, cnt, idx, f[6005], w[6005], d[6005], p[6005], h[6005], v[6005], e[6005], ne[6005], st[6005],
    p1[6005], p2[6005], sz[6005], ft[6005], son[6005], top[6005];
struct edge {
    int x, y, z;
} g[6005], te[6005];
bool cmp(edge x, edge y) {
    return x.z > y.z;
}
void add1(int x, int y, int z) {
    v[++idx] = y, e[idx] = z, ne[idx] = h[x], h[x] = idx;
    v[++idx] = x, ne[idx] = h[y], h[y] = idx;
}
void add2(int x, int y) {
    v[++idx] = y, ne[idx] = h[x], h[x] = idx;
}
bool bfs() {
    for (int i = 0; i <= n; i++)
        d[i] = 0, st[i] = h[i];

    queue<int> q;
    d[s] = 1, q.push(s);

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int i = h[x]; ~i; i = ne[i]) {
            int y = v[i];

            if (!d[y] && e[i]) {
                d[y] = d[x] + 1;
                q.push(y);
            }
        }
    }

    return d[t];
}
int dfs(int x, int flow) {
    if (x == t || !flow)
        return flow;

    int ret = 0, tmp;

    for (int i = st[x]; ~i; i = ne[i]) {
        int y = v[i];
        st[x] = i;

        if (d[y] == d[x] + 1) {
            tmp = dfs(y, min(flow - ret, e[i]));
            ret += tmp;
            e[i] -= tmp;
            e[((i - 1) ^ 1) + 1] += tmp;
        }
    }

    return ret;
}
int dinic() {
    int ret = 0;

    while (bfs())
        ret += dfs(s, 1e9);

    return ret;
}
void clear() {
    for (int i = 0; i <= n; i++)
        h[i] = -1;

    for (int i = 1; i <= idx; i++)
        v[i] = e[i] = ne[i] = 0;

    idx = 0;
}
void build(int l, int r) {
    if (l >= r)
        return;

    clear();

    for (int i = 0; i <= m; i++) {
        add1(g[i].x, g[i].y, g[i].z);
        add1(g[i].y, g[i].x, g[i].z);
    }

    s = p[l], t = p[r];
    te[++cnt] = {p[l], p[r], dinic()};
    int cnt1 = 0, cnt2 = 0;

    for (int i = l; i <= r; i++) {
        if (d[p[i]])
            p1[++cnt1] = p[i];
        else
            p2[++cnt2] = p[i];
    }

    for (int i = l; i <= l + cnt1 - 1; i++)
        p[i] = p1[i - l + 1];

    for (int i = l + cnt1; i <= r; i++)
        p[i] = p2[i - l - cnt1 + 1];

    build(l, l + cnt1 - 1);
    build(l + cnt1, r);
}
int find(int x) {
    if (x == f[x])
        return x;

    return f[x] = find(f[x]);
}
void dfs1(int x) {
    sz[x] = 1;

    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y == ft[x])
            continue;

        ft[y] = x, d[y] = d[x] + 1;
        dfs1(y), sz[x] += sz[y];

        if (!son[x] || sz[y] > sz[son[x]])
            son[x] = y;
    }
}
void dfs2(int x, int tp) {
    top[x] = tp;

    if (son[x])
        dfs2(son[x], tp);

    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y != ft[x] && y != son[x])
            dfs2(y, y);
    }
}
int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (d[top[x]] >= d[top[y]])
            x = ft[top[x]];
        else
            y = ft[top[y]];
    }

    if (d[x] > d[y])
        swap(x, y);

    return x;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
        cin >> g[i].x >> g[i].y >> g[i].z;

    for (int i = 1; i <= n; i++)
        p[i] = i;

    build(0, n);
    sort(te + 1, te + cnt + 1, cmp);
    clear();

    for (int i = 1; i <= n + cnt; i++)
        f[i] = i;

    for (int i = 1, x, y; i <= cnt; i++) {
        x = find(te[i].x), y = find(te[i].y);
        w[++n] = te[i].z;
        add2(n, x), add2(x, n);
        add2(n, y), add2(y, n);
        f[x] = f[y] = n;
    }

    dfs1(n), dfs2(n, n);
    int q;
    cin >> q;

    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << w[LCA(x, y)] << '\n';
    }

    return 0;
}
```

---

## 作者：__FL__ (赞：4)

## 最小割树
我们先简单介绍一下最小割树的思想。

最小割树满足这样的一种性质：对于一张流量图的最小割树，**这张图上任意两点的最小割，等于最小割树上对应两点的最小割**。

这类题目一般伴有多组询问，如果我们已经得到了最小割树，就可以根据树的良好性质，$O(N^2)$ 进行预处理，然后 $O(1)$ 处理询问。

那么我们怎么得到最小割树呢？

过程是这样的：对于一张流量图，我们任取两个点 $s,t$，然后求 $s,t$ 之间的最小割 $c$。显然这时两个点不再连通，并且整个图被分为两部分，一部分与 $s$ 连通，另一部分不与 $s$ 连通。我们在树中（注意不是流量图）连一条 $(s,t)$ 的权为 $c$ 的双向边，然后将与 $s$ 连通的一部分点在 $s$ 那头递归建立最小割子树，另一部分点在 $t$ 那头建立最小割子树。这里运用的是分治思想。

尤其需要注意的是，每次求最小割时，都应在**流量图原图**上跑最大流。

于是我们得到了一棵最小割树。

这个思路的证明比较复杂，但是如果你将树的性质和“最小割要在原图上跑”这个问题联合起来想一想，应该能隐约想到它是正确的。至于其他可以自行查阅证明。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 505,M = 6005,inf = 1e15;
int n,m,x,y,z,s,t,Q,head[N],nxt[M],to[M],w[M],init_w[M],cnt=-1,d[N],a[N],temp[N],f[N][N];
vector<pair<int,int>>vec[N];
queue<int>q;
inline void add(int u,int v,int c) {nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = v; w[cnt] = c;}
inline void Add(int u,int v,int c) {add(u,v,c); add(v,u,0);}
inline void addvec(int u,int v,int c) {vec[u].push_back({v,c}); vec[v].push_back({u,c});}
bool bfs()
{
	while (!q.empty()) q.pop();
	memset(d,0,sizeof d);
	q.push(s);
	d[s] = 1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u]; ~i; i = nxt[i])
		{
			int v = to[i];
			if (w[i] && !d[v])
			{
				d[v] = d[u]+1;
				if (v == t) return 1;
				q.push(v);
			}
		}
	}
	return 0;
}
int dfs(int u,int limit)
{
	if (u == t) return limit;
	int flow = 0;
	for (int i = head[u]; ~i; i = nxt[i])
	{
		int v = to[i];
		if (d[v] == d[u]+1 && w[i])
		{
			int p = dfs(v,min(limit-flow,w[i]));
			if (!p) d[v] = 0;
			flow += p;
			w[i] -= p;
			w[i^1] += p;
			if (flow == limit) return flow;
		}
	}
	return flow;
}
int Dinic()
{
	int ans = 0;
	while (bfs())
		ans += dfs(s,inf);
	return ans;
}
void build(int l,int r)
{
	if (l >= r) return;
	s = a[l],t = a[r];
	for (int i = 0; i <= cnt; i++)
		init_w[i] = w[i];
	int ans = Dinic();
	for (int i = 0; i <= cnt; i++)
		w[i] = init_w[i];
	addvec(s,t,ans);
	int tl = l-1,tr = r+1;
	for (int i = l; i <= r; i++)
	{
		if (d[a[i]]) temp[++tl] = a[i];
		else temp[--tr] = a[i];
	}
	for (int i = l; i <= r; i++)
		a[i] = temp[i];
	build(l,tl);
	build(tr,r);
}
void dfs_init(int u,int fa,int root,int mmin)
{
	f[root][u] = mmin;
	for (pair<int,int>i: vec[u])
		if (i.first != fa)
			dfs_init(i.first,u,root,min(mmin,i.second));
}
signed main()
{
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	memset(head,-1,sizeof head);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> x >> y >> z;
		Add(x,y,z);
		Add(y,x,z);
	}
	for (int i = 0; i <= n; i++)
		a[i] = i;
	build(0,n);
	for (int i = 0; i <= n; i++)
		dfs_init(i,i,i,inf);
	cin >> Q;
	while (Q--)
	{
		cin >> x >> y;
		cout << f[x][y] << '\n';
	}
	return 0;
}
```
推荐练习最小割树：[P4214 [CERC2015] Juice Junctions](https://www.luogu.com.cn/problem/P4214)

---

## 作者：Acoipp (赞：4)

## 分析

最小割树用于处理任意割断代价总和最小的边使得任意两个点不连通的问题。

很显然，每次得到询问之后处理是不优秀的，时间复杂度为 $O(Qn^2m)$，那么我们就可以用 Gomory-Hu 算法优化到 $O(n^3m+Q)$。

具体来说，这个算法把这些点建立成了一棵树，然后使得其中任意两个点 $s,t$ 的最小割就是这两个点树上简单路径上的边权最小值。

为了建立出来这么一棵树，我们需要分治。

1. 在当前的点集中任意选取两个点 $s,t$，在原图上跑最小割，得到结果。
2. 把当前最小割划分出来的两个集合分别向下递归，得到两棵子树的根。
3. 连接这两个根，边权为当前最小割的值。
4. 如果 $s$ 这个集合包含了点集外的数，返回根为 $s$；如果 $t$ 这个集合包含了点集外的数，返回根为 $t$；否则当前点集一定是全集，特判一下即可。

这就是构建最小割树的过程，之后对于每个询问，我们可以预处理回答，也可以处理倍增后在线回答询问，一个是 $O(Q)$ 的，一个是 $(Q \log n)$ 的。

还有一种构造过程：

1. 随便选取两个点 $s,t$，$s$ 连向 $t$ 一条双向边，边权为源点为 $s$，汇点为 $t$ 的最小割。  
2. 得到两个集合，这两个集合往下递归即可。

第二种做法更加简单，推荐选择第二种做法。

这个做法的正确性在于，我们选取了两个点，假设最小割割成了两个集合 $S,T$，那么在分治的过程中，我们至少会有一次任取两个点一个取到了 $S$ 集合，一个取到了 $T$ 集合，这个显然可得。

于是任意询问两点最小割的问题就解决了。

## 代码
代码中的网络流使用 Dinic 实现。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 50005
using namespace std;
vector<ll> op[N],w[N];
ll n,m,i,x,y,z;
ll tot=1,cur[N],ne[N],la[N],to[N],val[N],vis[N],we[N],q[N],he,ta,dis[N],s,t,inf,tofa[N],id[N],idd[N],st[N][21],st2[N][21],dep[N];
inline void merge(ll x,ll y,ll z){
	tot++,ne[tot] = la[x],la[x] = tot,to[tot] = y,val[tot] = z,we[tot] = z;
	tot++,ne[tot] = la[y],la[y] = tot,to[tot] = x,val[tot] = 0,we[tot] = 0;
}
bool bfs(){
	for(ll i=1;i<=n;i++) dis[i]=-1;
	q[he=ta=1]=s,dis[s]=0;
	while(he<=ta){
		ll tmp = q[he++];
		for(ll i=la[tmp];i;i=ne[i]){
			if(val[i]>0&&dis[to[i]]==-1){
				dis[to[i]]=dis[tmp]+1;
				q[++ta]=to[i];
			}
		}
	}
	return dis[t]!=-1;
}
ll dfs(ll x,ll step){
	if(x==t||!step) return step;
	ll used = 0;
	for(ll i=cur[x];i;i=ne[i]){
		cur[x] = i;
		if(dis[to[i]]==dis[x]+1&&val[i]>0){
			ll temp = dfs(to[i],min(step-used,val[i]));
			used += temp,val[i] -= temp,val[i^1] += temp;
			if(used==step) return used;
		}
	}
	return used;
}
ll get_max(ll x,ll y){
	ll ans = 0;
	for(ll i=0;i<=tot;i++) val[i]=we[i];
	s=x,t=y;
	while(bfs()){
		for(ll i=1;i<=n;i++) cur[i]=la[i];
		ans += dfs(s,1e18);
	}
	return ans;
}
ll solve(ll l,ll r){
	if(l==r) return id[l];
	ll temp = get_max(id[l],id[l+1]);
	ll tot = l,pos = tot-1,root = 0;
	for(ll i=l;i<=r;i++) vis[id[i]]=1;
	for(ll i=l;i<=r;i++) if(dis[id[i]]!=-1) idd[tot++]=id[i];
	pos=tot-1;
	for(ll i=l;i<=r;i++) if(dis[id[i]]==-1) idd[tot++]=id[i];
	for(ll i=l;i<=r;i++) id[i]=idd[i];
	for(ll i=1;i<=n;i++){
		if(!vis[i]&&dis[i]==-1) root=-2;
		if(!vis[i]&&dis[i]!=-1) root=-1;
	}
	for(ll i=l;i<=r;i++) vis[id[i]]=0;
	ll ls = solve(l,pos),rs = solve(pos+1,r);
	op[ls].push_back(rs),w[ls].push_back(temp),op[rs].push_back(ls),w[rs].push_back(temp);
	if(root==-1) return ls;
	if(root==-2) return rs;
	return root;
}
void dfss(ll x,ll fa){
	for(ll i=1;i<=20;i++){
		st[x][i] = st[st[x][i-1]][i-1];
		st2[x][i] = min(st2[x][i-1],st2[st[x][i-1]][i-1]);
	}
	for(ll i=0;i<op[x].size();i++){
		if(op[x][i]==fa) continue;
		st[op[x][i]][0] = x,st2[op[x][i]][0] = w[x][i],dep[op[x][i]] = dep[x]+1;
		dfss(op[x][i],x);
	}
}
ll found(ll x,ll y){
	ll ans = LLONG_MAX;
	if(dep[x]>dep[y]) swap(x,y);
	for(ll i=20;i>=0;i--) if(dep[st[y][i]]>=dep[x]) ans=min(ans,st2[y][i]),y=st[y][i];
	if(x==y) return ans;
	for(ll i=20;i>=0;i--){
		if(st[x][i]!=st[y][i]){
			ans=min(ans,min(st2[x][i],st2[y][i]));
			x=st[x][i],y=st[y][i];
		}
	}
	return min(ans,min(st2[x][0],st2[y][0]));
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m,n++;
	while(m--){
		cin>>x>>y>>z,x++,y++;
		merge(x,y,z),merge(y,x,z);
	}
	for(i=1;i<=n;i++) id[i]=i;
	solve(1,n);
	dep[1]=1;
	dfss(1,-1);
	cin>>m;
	while(m--){
		cin>>x>>y;
		x++,y++;
		cout<<found(x,y)<<endl;
	}
	return 0;
}
/*
Input:
4 5
1 2 2
2 3 2
4 2 3
4 3 1
1 3 1
3
1 4
2 4
2 3

Output:
3
4
4
*/
```

第二种写法的代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 50005
using namespace std;
vector<ll> op[N],w[N];
ll n,m,i,x,y,z;
ll tot=1,cur[N],ne[N],la[N],to[N],val[N],vis[N],we[N],q[N],he,ta,dis[N],s,t,inf,tofa[N],id[N],idd[N],st[N][21],st2[N][21],dep[N];
inline void merge(ll x,ll y,ll z){
	tot++,ne[tot] = la[x],la[x] = tot,to[tot] = y,val[tot] = z,we[tot] = z;
	tot++,ne[tot] = la[y],la[y] = tot,to[tot] = x,val[tot] = 0,we[tot] = 0;
}
bool bfs(){
	for(ll i=1;i<=n;i++) dis[i]=-1;
	q[he=ta=1]=s,dis[s]=0;
	while(he<=ta){
		ll tmp = q[he++];
		for(ll i=la[tmp];i;i=ne[i]){
			if(val[i]>0&&dis[to[i]]==-1){
				dis[to[i]]=dis[tmp]+1;
				q[++ta]=to[i];
			}
		}
	}
	return dis[t]!=-1;
}
ll dfs(ll x,ll step){
	if(x==t||!step) return step;
	ll used = 0;
	for(ll i=cur[x];i;i=ne[i]){
		cur[x] = i;
		if(dis[to[i]]==dis[x]+1&&val[i]>0){
			ll temp = dfs(to[i],min(step-used,val[i]));
			used += temp,val[i] -= temp,val[i^1] += temp;
			if(used==step) return used;
		}
	}
	return used;
}
ll get_max(ll x,ll y){
	ll ans = 0;
	for(ll i=0;i<=tot;i++) val[i]=we[i];
	s=x,t=y;
	while(bfs()){
		for(ll i=1;i<=n;i++) cur[i]=la[i];
		ans += dfs(s,1e18);
	}
	return ans;
}
void solve(ll l,ll r){
	if(l==r) return ;
	ll temp = get_max(id[l],id[l+1]);
	ll tt1 = id[l],tt2 = id[l+1];
	ll tot = l,pos = tot-1;
	for(ll i=l;i<=r;i++) vis[id[i]]=1;
	for(ll i=l;i<=r;i++) if(dis[id[i]]!=-1) idd[tot++]=id[i];
	pos=tot-1;
	for(ll i=l;i<=r;i++) if(dis[id[i]]==-1) idd[tot++]=id[i];
	for(ll i=l;i<=r;i++) id[i]=idd[i];
	for(ll i=l;i<=r;i++) vis[id[i]]=0;
	solve(l,pos),solve(pos+1,r);
	op[tt1].push_back(tt2),w[tt1].push_back(temp);
	op[tt2].push_back(tt1),w[tt2].push_back(temp);
	return ;
}
void dfss(ll x,ll fa){
	for(ll i=1;i<=20;i++){
		st[x][i] = st[st[x][i-1]][i-1];
		st2[x][i] = min(st2[x][i-1],st2[st[x][i-1]][i-1]);
	}
	for(ll i=0;i<op[x].size();i++){
		if(op[x][i]==fa) continue;
		st[op[x][i]][0] = x,st2[op[x][i]][0] = w[x][i],dep[op[x][i]] = dep[x]+1;
		dfss(op[x][i],x);
	}
}
ll found(ll x,ll y){
	ll ans = LLONG_MAX;
	if(dep[x]>dep[y]) swap(x,y);
	for(ll i=20;i>=0;i--) if(dep[st[y][i]]>=dep[x]) ans=min(ans,st2[y][i]),y=st[y][i];
	if(x==y) return ans;
	for(ll i=20;i>=0;i--){
		if(st[x][i]!=st[y][i]){
			ans=min(ans,min(st2[x][i],st2[y][i]));
			x=st[x][i],y=st[y][i];
		}
	}
	return min(ans,min(st2[x][0],st2[y][0]));
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m,n++;
	while(m--){
		cin>>x>>y>>z,x++,y++;
		merge(x,y,z),merge(y,x,z);
	}
	for(i=1;i<=n;i++) id[i]=i;
	solve(1,n);
	dep[1]=1;
	dfss(1,-1);
	cin>>m;
	while(m--){
		cin>>x>>y;
		x++,y++;
		cout<<found(x,y)<<endl;
	}
	return 0;
}
/*
Input:
4 5
1 2 2
2 3 2
4 2 3
4 3 1
1 3 1
3
1 4
2 4
2 3

Output:
3
4
4
*/
```

---

## 作者：TernaryTree (赞：3)

无聊翻集训队论文学的 useless algorithm。

首先要做一个区分，我们所构造的树不是最小割树。

最小割树的定义是，任意两点，在树的路径上最小的边，这两个端点的最小割的方案与原始的两点相同。显然同时满足其最小割的权值相同。

最小割树构造是困难的，需要维护缩点等。

我们考虑弱化条件，把方案相同去掉。也就是说只要任意两点的最小割权值等于其树上路径最小边权即可。我们把这样的树叫做等价流树。

等价流树如何构造呢，我们有一个算法叫做 Gusfield 算法。算法流程如下：

1. 找到任意两点，在等价流树上连边，边权为这两点最小割；
2. 上面两点的割把图分成了两个点集，形成了两个子问题，就分治下去做。

容易知道我们要跑 $\Theta(n)$ 次 dinic 求最小割，复杂度 $\Theta(n^3 m)$。

---

接下来证明这样构造的正确性。可选择性跳过。

考虑归纳，不妨令一次分治两边构造的树都是满足条件的。这个时候我们需要证明新连上的这条边也合法，即在最小割一侧的任意一个点 $u$ 与另一侧的任意 $v$ 在等价流树上的路径满足性质。

---

一个定理：记 $f(u,v)$ 为 $u$ 与 $v$ 的最小割，则有

$$f(u,v)\ge \min(f(u,w),f(v,w))$$

证明如下：不妨设任意三个点中，两两最小割最小的为 $f(u,v)$。考虑另一个点 $w$，其与 $u,v$ 中与其异侧的点的最小割显然不超过 $f(u,v)$，而 $f(u,v)$ 最小，所以 $f(u,w),f(v,w)$ 中至少有一个与 $f(u,v)$ 相等，得证。

---

另一个定理：对于 $s,t$ 的一组最小割，令 $u,v$ 两点位于这个割的同一侧，则 $u,v$ 存在一个最小割使得这个最小割的边的端点仅在这一侧的点中。

证明略，可自行阅读论文理解。

---

回到等价流树正确性的归纳证明，我们设加入的边为 $(s,t)$，设 $u$ 是 $s$ 侧的一个点，$v$ 是 $t$ 侧的一个点，那么有

$$f(u,v)=\min(f(s,t),\min(u\to s\textrm{ \small 上最小边权},t\to v\textrm{ \small 上最小边权}))$$

根据定理，有 $f(u,v)\ge \min(f(s,t),\min(u\to s\textrm{ \small 上最小边权},t\to v\textrm{ \small 上最小边权}))$。

其次，我们有 $f(u,v)\le f(s,t)$，因为 $s,t$ 这一组割一定对 $u,v$ 合法。

然后我们考虑 $u\to s$ 的路径，$t\to v$ 可同理；根据定理， $u,s$ 的最小割一定不会碰到 $t$ 侧。而 $u,(s,t)$，$s,(u,t)$ 中必然有一个割，要么是 $u,v$ 的割要么是 $s,t$ 的割，所以显然不小于 $f(s,t)$，于是得到 $f(u,v)\le$ 后面那一坨。

证毕。

---

## 作者：zhenglier (赞：3)

## 题意：
求任意两点间的最小割（最大流）

## 题解：
本题要用到最小割树。

最小割树其实就是把所有的点分成多个部分然后分治，使只用跑很少次网络流就能解决两点之间的最小割。

举个例子：

这个图：

[![FNnJoT.png](https://s1.ax1x.com/2018/12/13/FNnJoT.png)](https://imgchr.com/i/FNnJoT)

开始先求1，4点间的最小割，易得为3。

跑完网络流之后的图是这样的。

[![FNnBO1.png](https://s1.ax1x.com/2018/12/13/FNnBO1.png)](https://imgchr.com/i/FNnBO1)

我们发现图变成了两部分，事实上，图肯定会变成两部分甚至更多，因为既然是一个割，就肯定会把两个点分到不同的区域。

然后易知两个区域之间的最小割至少为当前的最小割——3。

然后我们把图复原

[![FNnJoT.png](https://s1.ax1x.com/2018/12/13/FNnJoT.png)](https://imgchr.com/i/FNnJoT)

在刚才划分的区域里继续划分

但有(1)区间只剩一个点了，所以不继续划分，取（2，3，4）中的2，3两点做最小割(其实随便哪两个不同的点都可以)，易得最小割为4。

剩下的图为：

[![FNnOpQ.png](https://s1.ax1x.com/2018/12/13/FNnOpQ.png)](https://imgchr.com/i/FNnOpQ)

然后易知两个区域之间的最小割至少为当前的最小割——4。

然后更新答案，记住，就算不在当前区间内的数也必须更新。

继续复原，更新，然后得到最后的$ans$：

然后就可以根据询问输出了。

用这样的算法只用跑$n$遍网络流，因为每次必定分离两个点，乘上网络流复杂度$O(n^2m)$(其实跑不满)复杂度是$O(n^3m)$(也跑不满)。

至于为什么叫最小割树，大概是因为实际运算的时候每次都会把区间分为两部分，所以会分$n-1$次，然后每次会算出一个数（最小割），可以作为边权，然后就成了一棵树。

听说在这棵树上跑倍增找路径上的最小值也可以做这道题。

下面是常数极大的代码。

```cpp
#include<bits/stdc++.h>
#define re register 
using namespace std;
const int inf=1<<29,N=1010,M=20010;
int n,m,a[N];
int ans[N][N];
int head[N],nxt[M],bian[M],zhi[M],tot;
void init(){
    tot=1;
    memset(head,0,sizeof head);
}
inline void add(re int x,re int y,re int z){
    tot++;bian[tot]=y;zhi[tot]=z;nxt[tot]=head[x];head[x]=tot;
    tot++;bian[tot]=x;zhi[tot]=z;nxt[tot]=head[y];head[y]=tot;
}
inline void build(int m){
    for(re int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
    }
}
void rebuild(){
    for(re int i=1;i<=tot;i+=2){
        zhi[i]=zhi[i^1]=(zhi[i]+zhi[i^1])>>1;
    }
}
int v[N],d[N];
void cut(int x){
    v[x]=1;
    for(int i=head[x];i;i=nxt[i]){
        if(zhi[i]&&!v[bian[i]])cut(bian[i]);
    }
}
queue<int>q;
bool bfs(int b,int e){
    memset(d,0,sizeof(d));
    while(!q.empty())q.pop();
    q.push(b);d[b]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=head[x];i;i=nxt[i]){
            if(zhi[i] && !d[bian[i]]){
                q.push(bian[i]);
                d[bian[i]]=d[x]+1;
                if(bian[i]==e)return 1;
            }
        }
    }
    return 0;
}
int dinic(int b,int e,int x,int flow){
    if(x==e)return flow;
    int rest=flow,k;
    for(int i=head[x];i && rest;i=nxt[i]){
        if(zhi[i] && d[bian[i]]==d[x]+1){
            k=dinic(b,e,bian[i],min(rest,zhi[i]));
            if(!k)d[bian[i]]=0;
            zhi[i]-=k;
            zhi[i^1]+=k;
            rest-=k;
        }
    }
    return flow-rest;
}
inline int maxflow(int b,int e){
    int flow=0,maxflow=0;
    while(bfs(b,e)){
        while(flow=dinic(b,e,b,inf))maxflow+=flow;
    }
    return maxflow;
}
int b,e;
void solve(int l,int r){
    if(l==r)return;
    rebuild();
    b=a[l],e=a[r];
    re int mincut=maxflow(b,e);
    memset(v,0,sizeof v);
    cut(b);
    for(re int i=1;i<=n;++i){
        if(!v[i])continue;
        for(re int j=1;j<=n;++j){
            if(v[j])continue;
            ans[i][j]=ans[j][i]=min(ans[i][j],mincut);
        }
    }
    re int cnt=l-1;
    static int ls[N];
    for(re int i=l;i<=r;++i){
        if(v[a[i]]){
            ls[++cnt]=a[i];
        }
    }
    re int fj=cnt;
    for(re int i=l;i<=r;++i){
        if(!v[a[i]]){
            ls[++cnt]=a[i];
        }
    }
    for(re int i=l;i<=r;++i)a[i]=ls[i];
    solve(l,fj);
    solve(fj+1,r);
}
int main()
{
    int b,e,q;
    memset(ans,0x3f,sizeof ans);
    cin>>n>>m;
    init();
    build(m);
    for(int i=1;i<=n;++i){
    	a[i]=i;
    }
    solve(1,n);
    cin>>q;
    while(q--){
        scanf("%d%d",&b,&e);
        printf("%d\n",ans[b][e]);
    }
}
```

---

## 作者：AbsMatt (赞：2)

### [题目传送器](https://www.luogu.com.cn/problem/P4897)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/p4897-solution)

## 题意

给一个无向连通图，询问两点之间需要割掉多少边权能使两点不连通。

## 做法

因为连通性是可传递的，所以可以使用分治。

由于无向图两点间最小割 $=$ 最大流，所以使用网络最大流求最小割。

对于当前处理需要处理的点集 $s$，随意选两个点 $u$ 和 $v$ 跑一次网络最大流，设最大流为 $maxflow$，则在最小割树上建一条 $(u,v,maxflow)$ 边。设割掉满流的边后 $u$ 能遍历到的点集为 $s1$，剩下的点集 $s2=\complement_s s1$。往下递归处理 $s1$ 和 $s2$ 即可。求 $s1$ 可以找最后一次 dinic 的 bfs 遍历到的点。

现在已经建出了最小割树，考虑如何使用。当断掉一条边后，会花费当前边权的代价，将原树树断成两颗新树，这两棵新树上的点两两互相不连通。那对于求 $(u,v)$ 的最小割，只要断掉树上 $(u,lca(u,v))$ 和 $(lca(u,v),v)$ 这两条链中最小的一条边即可。可以使用倍增维护边权最小值。

## AC Code

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define piii pair<int,pii>
#define eb emplace_back
using namespace std;
const int maxn=1e5+10;
const int maxm=maxn*100;
int n,m;
struct Tree{
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
}Tr;
namespace Graph{
    piii g[maxn];
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void rebuild(){cnt=1;memset(head,0,sizeof(head));for(int i=1;i<=m;i++){add(g[i].first,g[i].second.first,g[i].second.second);add(g[i].second.first,g[i].first,g[i].second.second);}}
}
using namespace Graph;
int S,T;
namespace DINIC{
    const int inf=0x3f3f3f3f;
    int d[maxn],now[maxn];
    queue<int> q;
    inline bool bfs(){
        while(!q.empty())   q.pop();
        memset(d,0x3f,sizeof(d));
        memcpy(now,head,sizeof(head));
        d[S]=0;
        q.push(S);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=head[u];i;i=e[i].nxt){
                int t=e[i].to;
                if(d[t]!=inf||!e[i].w)  continue;
                d[t]=d[u]+1;
                q.push(t);
                if(t==T)    return true;
            }
        }
        return false;
    }
    int dfs(int u,int flw){
        if(u==T)    return flw;
        int res=0;
        for(int i=now[u];i&&flw;i=e[i].nxt){
            now[u]=i;
            int t=e[i].to;
            if(d[t]!=d[u]+1||!e[i].w)    continue;
            int k=dfs(t,min(e[i].w,flw));
            if(!k)  d[t]=inf;
            e[i].w-=k;e[i^1].w+=k;
            res+=k;flw-=k;
        }
        return res;
    }
    inline int dinic(){
        rebuild();
        int res=0;
        while(bfs())    res+=dfs(S,inf);
        return res;
    }
}
using namespace DINIC;
namespace DFS{
    int w[20][maxn],f[20][maxn],dep[maxn];
    void dfs(int u,int fa){
        dep[u]=dep[f[0][u]=fa]+1;w[0][u]=inf;
        for(int i=Tr.head[u];i;i=Tr.e[i].nxt){
            int t=Tr.e[i].to;
            if(t==fa)   continue;
            dfs(t,u);
            w[0][t]=Tr.e[i].w;
        }
    }
    inline void init_LCA(){for(int i=1;i<=19;i++)for(int j=1;j<=n;j++){w[i][j]=min(w[i-1][j],w[i-1][f[i-1][j]]);f[i][j]=f[i-1][f[i-1][j]];}}
    inline int LCA(int x,int y){  // O(nlogn) - O(logn) 倍增
        int res=inf;
        if(dep[x]<dep[y])   swap(x,y);
        for(int i=19;~i;i--){
            if(dep[f[i][x]]>=dep[y]){
                res=min(res,w[i][x]);
                x=f[i][x];
            }
        }
        if(x==y)    return res;
        for(int i=19;~i;i--){
            if(f[i][x]^f[i][y]){
                res=min(res,w[i][x]);res=min(res,w[i][y]);
                x=f[i][x];y=f[i][y];
            }
        }
        res=min(res,w[0][x]);res=min(res,w[0][y]);
        return res;
    }
}
vector<int> v,v1,v2;
void divide(int l,int r){
    v1.clear();v2.clear();
    if(l>=r)    return;
    S=v[l];T=v[l+1];
    int res=dinic();
    Tr.add(S,T,res);Tr.add(T,S,res);
    for(int i=l;i<=r;i++){
        if(d[v[i]]!=inf)   v1.eb(v[i]);
        else    v2.eb(v[i]);
    }
    for(int i=0;i<v1.size();i++)    v[i+l]=v1[i];
    for(int i=0;i<v2.size();i++)    v[i+l+v1.size()]=v2[i];
    int siz=v1.size();
    divide(l,l+siz-1);divide(l+siz,r);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d%d",&g[i].first,&g[i].second.first,&g[i].second.second);
    }
    for(int i=0;i<=n;i++)   v.eb(i);
    divide(0,n);
    DFS::dfs(1,0);
    DFS::init_LCA();
    int q;scanf("%d",&q);
    while(q--){
        int u,v;
        scanf("%d%d",&u,&v);
        printf("%d\n",DFS::LCA(u,v));
    }
}
```



## 总结 

时间复杂度为 $O(n \times D)$。$O(D)$ 是 dinic 的时间复杂度，理论是 $O(n^2\times m)$，但实际上小很多。

---

## 作者：yanwh1 (赞：2)

**前置芝士：[P3376 【模板】网络最大流](https://www.luogu.com.cn/problem/P3376)**

您是否经常因为要求多次最小割而烦恼？您是否因为多次求最小割而导致超时？它来啦，它来啦！最小割树，让您不再惧怕网络流，从此走上 OI 巅峰！

# 题意
给一张 $n$ 个点 $m$ 条边的无向图以及 $q$ 次询问，每次询问给出 $u$ 和 $v$，回答 $u$ 和 $v$ 的最小割。
# 原理
> 首先有一个定理，就是一个 $n$ 个点的图上，两点之间只有 $n$ 种本质不同的最小割。因此一定存在一棵树，满足树上两点的最小割等于原图上两点的最小割。我们把这样的树称之为“最小割树”。——Ebola

当然，~~我看不懂~~。
# 用途
最小割树常应用于多次求最小割的题目中，用它那看似超时的时间复杂度通过题目（主要是 dinic 太多玄学优化了）。
# 算法流程
最小割树算法主要分为两大类：建树以及查找。
## 建树
省流：最大流加分治。

首先我们需要在图上找出任意两点 $u,v$，然后对这两点找最大流，然后我们把这两个点连一条边（不要在原图连，这是为了建树）。

找完之后，可以发现图中的点可以分为两类：一类是能到 $u$ 的点，一类是能到 $v$ 的点（可以保证，查完后图中的点要么与 $u$ 相连，要么与 $v$ 相连）。

于是我们将这两个集合分治下去，重复以上操作，直到建成树（注意：每次找两点的最大流都是在全图找）。

建树的时间复杂度为 $O(n^3 \times m)$（~~真不知道这么大的时间复杂度怎么过的~~）。

贴下建树代码。

```cpp
inline void build(int l,int r){
	int m1=0,m2=0;
	if(l==r)return;
	int ans=dinic(rs[l],rs[l+1]);
	qwe[rs[l]].push_back({rs[l+1],ans});
	qwe[rs[l+1]].push_back({rs[l],ans});
	for(rint i=l;i<=r;i++){
		if(dis[rs[i]]!=inf)rs1[++m1]=rs[i];
		else rs2[++m2]=rs[i];
	}for(rint i=1;i<=m1;i++)rs[i+l-1]=rs1[i];
	for(rint i=1;i<=m2;i++)rs[i+l+m1-1]=rs2[i];
	build(l,l+m1-1),build(l+m1,r);
}
```

## 查询
剩下的查询就简单了：我们将在图上找最小割变成了在树上找最小割。于是如果我们要查找 $u$ $v$ 两点的最小割，就找它们路径上边的最小权值即可
省流：dfs。
，dfs 秒了。

这里太过于简单，就不贴代码了。
# 回归题目
理解了最小割树后，这道题就好做了。我们建好最小割树后，按上文所述 dfs 查询即可。
# 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void write(long long x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}const int N=505,M=1505,inf=INT_MAX;
int head[M],to[M<<1],nxt[M<<1],w[M<<1],cnt=1,n,m,s,t;
inline void add(int u,int v,int vl){nxt[++cnt]=head[u],to[cnt]=v,w[cnt]=vl,head[u]=cnt;}
int dis[N],now[N],rs[N],rs1[N],rs2[N];
queue<pair<int,int>>qe;
struct edge{int v,w;};
vector<edge>qwe[N];
inline int bfs(){
	for(rint i=1;i<=n;i++)dis[i]=inf;
	queue<int>q;q.push(s),dis[s]=0,now[s]=head[s];
	while(!q.empty()){
		int u=q.front();q.pop();
		for(rint i=head[u];i;i=nxt[i]){
			int v=to[i],vl=w[i];
			if(vl&&dis[v]==inf){
				q.push(v);
				dis[v]=dis[u]+1;
				now[v]=head[v];
				if(v==t)return 1;
			}
		}
	}return 0;
}inline int dfs(int u=s,int mn=inf){
	if(u==t||!mn)return mn;
	int k,res=0;
	for(rint i=now[u];i;i=nxt[i]){
		now[u]=i;int v=to[i],vl=w[i];
		if(vl&&dis[v]==dis[u]+1){
			k=dfs(v,min(vl,mn));
			if(!k)dis[v]=inf;
			w[i]-=k,w[i^1]+=k;
			qe.push(make_pair(i,k));
			res+=k,mn-=k;
			if(!mn)break;
		}
	}return res;
}inline int dinic(int u,int v){
	s=u,t=v;int ans=0;
	while(bfs())ans+=dfs();
	while(!qe.empty()){
		pair<int,int> res=qe.front();qe.pop();
		w[res.first]+=res.second;
		w[res.first^1]-=res.second;
	}return ans;
}inline void build(int l,int r){
	int m1=0,m2=0;
	if(l==r)return;
	int ans=dinic(rs[l],rs[l+1]);
	qwe[rs[l]].push_back({rs[l+1],ans});
	qwe[rs[l+1]].push_back({rs[l],ans});
	for(rint i=l;i<=r;i++){
		if(dis[rs[i]]!=inf)rs1[++m1]=rs[i];
		else rs2[++m2]=rs[i];
	}for(rint i=1;i<=m1;i++)rs[i+l-1]=rs1[i];
	for(rint i=1;i<=m2;i++)rs[i+l+m1-1]=rs2[i];
	build(l,l+m1-1),build(l+m1,r);
}inline int query(int u,int f,int wd){
	for(rint i=0;i<qwe[u].size();i++){
		int v=qwe[u][i].v,w=qwe[u][i].w;
		if(f==v)continue;
		if(v==wd)return w;
		int res=query(v,u,wd);
		if(res!=inf)return min(res,w);
	}return inf;
}
signed main(){
	n=read(),m=read();
	for(rint i=1;i<=n;i++)rs[i]=i;
	for(rint i=1;i<=m;i++){
		int u=read(),v=read(),e=read();
		add(u,v,e),add(v,u,e);
	}build(1,n);
	int q=read();
	while(q--){
		int u=read(),v=read();
		write(query(u,0,v)),puts("");
	}
	return 0;
}
```

# 算法进阶
有一些最小割树~~勾石~~豪题，要求你求出每个点对其它所有点的最小割，某些涉世未深的 OIer 们可能会一个一个去查，但是我们可以发现：每次 dfs 其实可以以搜索整张图为代价，算出该点与其它所有结点的最小割。于是时间复杂度查询操作从 $O(n^2 \times m)$ 变成 $O(n \times m)$。芜湖！

# 最小割树豪题
- [P4123 [CQOI2016] 不同的最小割](https://www.luogu.com.cn/problem/P4123)
- [P3329 [ZJOI2011] 最小割](https://www.luogu.com.cn/problem/P3329)
- [UVA11594 All Pairs Maximum Flow](https://www.luogu.com.cn/problem/UVA11594)
- [P4214 [CERC2015] Juice Junctions](https://www.luogu.com.cn/problem/P4214)
- [ CF343E Pumping Stations](https://www.luogu.com.cn/problem/CF343E)

---

## 作者：Charlie_ljk (赞：1)

- [更好的阅读体验](https://www.cnblogs.com/Charlieljk/p/18729786)。

# 最小割树

最小割树就是通过分治建出一棵树，树上两点的最小割就等于原图上的最小割，树上两点路径唯一，其最小割就等于路径上边权的最小值。

建树时，任意选择两点最为 $s,t$ 跑最小割，求得 $ans_{s,t}$，并将其分为两个集合 $S,T$，对于 $x\in S,y\in T$，有 $ans_{x,y}=ans_{y,x}=\min(ans_{s,t},ans_{x,s},ans_{t,y})$。

之后对于这两部分再分别跑最小割，重复上述步骤，就能在理论（网络流的复杂度跑不满） $O(n^3m)$ 的复杂度内建出一棵最小割树。

# 答案处理

## 建树

建树就是对于每一层分治将 $s,t$ 连上边权为 $ans_{s,t}$ 的边即可，$ans_{s,t}$ 为本次最小割跑出的答案。

因为原图两点的最小割就等于树上两点路径上边权的最小值，根据这点就可以有很多种处理方式了：

- $O(n)$ 预处理，之后 $ans_{x,y}=\min(ans_{x,lca(x,y)},ans_{lca(x,y),y})$，根据 lca 的实现，总体查询复杂度 $O(Q\log n)$ 或 $O(n\log n+Q)$。
- 树上倍增，查询复杂度也是 $O(Q\log n)$。
- 因为 $n$ 是很小的，所以直接以每个点为根遍历一遍树预处理出答案也是可以的，复杂度 $O(n^2)$。
- ……

## 不建树

根据上面的式子，对于 $x\in S,y\in T$，有 $ans_{x,y}=ans_{y,x}=\min(ans_{s,t},ans_{x,s},ans_{t,y})$。

根据这个式子，在分治的同时处理出答案即可，不需要把树建出来。

# 一些细节

- 每一次跑最小割前要将所有边恢复初始状态。
- 本题为无向图，要所以可以不用对于每一个边再建一条流量为 $0$ 的反边了，建双向边即可。
- 注意分治时每层的 $s,t$ 不同，根据需要保存本层的 $s,t$。
- 因为数据有误，给定图的真实点数应该是 $n+1$ 个，编号为 $0$ 到 $n$。

# 代码如下

使用的是不把树建出来的方法。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp make_pair
using namespace std;
const int N=510,M=3010,inf=0x3f3f3f3f;
#ifdef __linux__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc _getchar_nolock
#define pc _putchar_nolock
#endif
inline bool blank(const char x) {return !(x^32)||!(x^10)||!(x^13)||!(x^9);}
template<typename Tp> inline void read(Tp &x) {x=0; register bool z=true; register char a=gc(); for(;!isdigit(a);a=gc()) if(a=='-') z=false; for(;isdigit(a);a=gc()) x=(x<<1)+(x<<3)+(a^48); x=(z?x:~x+1);}
inline void read(double &x) {x=0.0; register bool z=true; register double y=0.1; register char a=gc(); for(;!isdigit(a);a=gc()) if(a=='-') z=false; for(;isdigit(a);a=gc()) x=x*10+(a^48); if(a!='.') return x=z?x:-x,void(); for(a=gc();isdigit(a);a=gc(),y/=10) x+=y*(a^48); x=(z?x:-x);}
inline void read(char &x) {for(x=gc();blank(x)&&(x^-1);x=gc());}
inline void read(char *x) {register char a=gc(); for(;blank(a)&&(a^-1);a=gc()); for(;!blank(a)&&(a^-1);a=gc()) *x++=a; *x=0;}
inline void read(string &x) {x=""; register char a=gc(); for(;blank(a)&&(a^-1);a=gc()); for(;!blank(a)&&(a^-1);a=gc()) x+=a;}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y) {read(x),read(y...);}
template<typename Tp> inline void write(Tp x) {if(!x) return pc(48),void(); if(x<0) pc('-'),x=~x+1; register int len=0; register char tmp[64]; for(;x;x/=10) tmp[++len]=x%10+48; while(len) pc(tmp[len--]);}
inline void write(const double x) {register int a=6; register double b=x,c=b; if(b<0) pc('-'),b=-b,c=-c; register double y=5*powl(10,-a-1); b+=y,c+=y; register int len=0; register char tmp[64]; if(b<1) pc(48); else for(;b>=1;b/=10) tmp[++len]=floor(b)-floor(b/10)*10+48; while(len) pc(tmp[len--]); pc('.'); for(c*=10;a;a--,c*=10) pc(floor(c)-floor(c/10)*10+48);}
inline void write(const pair<int,double>x) {register int a=x.first; if(a<7) {register double b=x.second,c=b; if(b<0) pc('-'),b=-b,c=-c; register double y=5*powl(10,-a-1); b+=y,c+=y; register int len=0; register char tmp[64]; if(b<1) pc(48); else for(;b>=1;b/=10) tmp[++len]=floor(b)-floor(b/10)*10+48; while(len) pc(tmp[len--]); a&&(pc('.')); for(c*=10;a;a--,c*=10) pc(floor(c)-floor(c/10)*10+48);} else cout<<fixed<<setprecision(a)<<x.second;}
inline void write(const char x) {pc(x);}
inline void write(const bool x) {pc(x?49:48);}
inline void write(char *x) {fputs(x,stdout);}
inline void write(const char *x) {fputs(x,stdout);}
inline void write(const string &x) {fputs(x.c_str(),stdout);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y) {write(x),write(y...);}
int n,m,s,t,cs[N],ct[N],dep[N],node[N],ans[N][N];
int tot=1,now[N],head[N],nxt[M],to[M],w[M];
inline void add(int x,int y,int z)
{
	nxt[++tot]=head[x],to[head[x]=tot]=y,w[tot]=z;
	nxt[++tot]=head[y],to[head[y]=tot]=x,w[tot]=z;
}
inline bool bfs()
{
	queue<int>q; memset(dep,0,sizeof(dep));
	for(memcpy(now,head,sizeof(now)),q.push(s),dep[s]=1;!q.empty();)
	{
		int x=q.front(); q.pop();
		for(int i=head[x],y;y=to[i];i=nxt[i]) if(w[i]&&!dep[y])
		{dep[y]=dep[x]+1,q.push(y); if(y==t) return true;}
	} return false;
}
inline int dfs(int x,int sum)
{
	if(x==t||!sum) return sum; int sur,res=0;
	for(int &i=now[x],y;y=to[i];i=nxt[i]) if(w[i]&&dep[y]==dep[x]+1)
	{
		if(!(sur=dfs(y,min(sum,w[i])))) {dep[y]=-1; continue;}
		w[i]-=sur,w[i^1]+=sur,res+=sur; if(!(sum-=sur)) break;
	} return res;
}
inline void build(int l,int r)
{
	if(l>=r) return ; s=node[l],t=node[r]; int res=0,ns=0,nt=0;
	for(int i=2;i<tot;i+=2) w[i]=w[i^1]=w[i]+w[i^1]>>1;
	while(bfs()) res+=dfs(s,inf); ans[s][t]=ans[t][s]=res;
	for(int i=l,x;i<=r;i++) dep[x=node[i]]?cs[++ns]=x:ct[++nt]=x;
	for(int i=1;i<=ns;i++) node[l+i-1]=cs[i];
	for(int i=1;i<=nt;i++) node[l+ns+i-1]=ct[i];
	int os=s,ot=t; build(l,l+ns-1),build(l+ns,r); 
	for(int i=1,j,x,y;i<=ns;i++) for(x=node[l+i-1],j=1;j<=nt;j++)
		y=node[l+ns+j-1],ans[x][y]=ans[y][x]=min({ans[x][os],ans[ot][y],res});
}
signed main()
{
	read(n,m),n++,memset(ans,0x3f,sizeof(ans));
	for(int x,y,z;m--;) read(x,y,z),add(x+1,y+1,z);
	for(int i=1;i<=n;i++) node[i]=i; build(1,n),read(m);
	for(int x,y;m--;) read(x,y),write(ans[x+1][y+1],'\n');
}
```

---

## 作者：JiaY19 (赞：1)

大概是年初学的算法了，现在联赛前复习一下。

### 思路

由于题目中需要多次求得两点最小割。

如果直接对于每一次询问都进行一次网络流求解，时间复杂度显然是错误的。

我们考虑进行优化，使用最小割树。

最小割树的大致算法流程：

1. 找到集合中的任意两点，初始的集合即为全图中的点。

2. 利用网络流求解答案。

3. 将两点连边，边有权值，权值为求解出的答案。

4. 将两个割集分开进行递归处理，返回 $1$。

然后对于最小割树，它有一个十分优美的性质。

树上任意两点的最小割为两点的简单路径上边权的最小值。

这样，就可以 $n^2$ 预处理进行求解了。

至于这个性质的证明，过程比较繁琐，本人也不是非常理解，可以看一眼网上的证明。

有一个感性理解，对于要求解最小割的两个点，他们简单路径上的任意一条边被割掉之后，都会使两个点被分成两个割集。

注意几点。

1. 最大流后记得清空。

2. 初始的边连双向边。

时间复杂度 $O(n^3\times m)$。

本人使用 ISAP。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 600;
const int M = 10100;
const int inf = 1e9 + 10;

int n , m , s , t , q , cnt = 1 , maxflow;
int id[N] , tmp[N] , vis[N] , dep[N] , gap[N] , head[N];

struct edge
{
    int to , nxt , val , sum;
}e[M];

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}

inline void add(int x , int y , int z)
{
    e[++cnt] = {y , head[x] , z , z} , head[x] = cnt;
}

inline void bfs()
{
    queue<int> q;
    memset(dep , 0 , sizeof dep);
    memset(gap , 0 , sizeof gap);
    q.push(t) , gap[dep[t] = 1] = 1;
    while(q.empty() == 0)
    {
        int x = q.front(); q.pop();
        for(int i = head[x];i;i = e[i].nxt)
        {
            if(!dep[e[i].to])
            {
                dep[e[i].to] = dep[x] + 1;
                gap[dep[e[i].to]]++;
                q.push(e[i].to);
            }
        }
    }
}

inline int dfs(int now , int flow)
{
    if(now == t)  return flow;
    int used = 0;
    for(int i = head[now];i;i = e[i].nxt)
    {
        int x = e[i].to;
        if(e[i].val && dep[x] + 1 == dep[now])
        {
            int y = dfs(e[i].to , min(flow - used , e[i].val));
            e[i].val -= y , e[i ^ 1].val += y , used += y;
            if(used == flow) return used;
        }
    }
    gap[dep[now]]--;
    if(gap[dep[now]] == 0) dep[s] = n + 1;  
    gap[++dep[now]]++;
    return used;
}

inline void init()
{
    for(int i = 0;i <= cnt;i++) e[i].val = e[i].sum;
}

inline int isap(int S , int T)
{
    s = S , t = T , maxflow = 0;
    init() , bfs();
    while(dep[s] <= n) maxflow += dfs(s , inf);
    return maxflow;
}

struct GHT
{
    edge tr[M];
    int tot , ans[N][N] , hed[N];
        
    inline void add_edge(int x , int y , int z)
    {
        tr[++tot] = {y , hed[x] , z} , hed[x] = tot;
        tr[++tot] = {x , hed[y] , z} , hed[y] = tot;
    }
        
    inline void find(int now)
    {
        vis[now] = 1;
        for(int i = head[now];i;i = e[i].nxt)
            if(!vis[e[i].to] && e[i].val) find(e[i].to);
    }
        
    inline void build(int l , int r)
    {
        if(l >= r) return;
        int x = id[l] , y = id[l + 1];
        int sum = isap(x , y) , ls = l , rs = r;
        add_edge(x , y , sum);
        add_edge(y , x , sum);
        memset(vis , 0 , sizeof vis) , find(x);
        for(int i = l;i <= r;i++) 
            tmp[(vis[id[i]] ? ls++ : rs--)] = id[i];
        for(int i = l;i <= r;i++) id[i] = tmp[i];
        build(l , ls - 1) , build(rs + 1 , r);
    }
        
    inline void get(int now , int fa , int gen , int dis)
    {
        ans[now][gen] = dis;
        for(int i = hed[now];i;i = tr[i].nxt)
            if(tr[i].to != fa) get(tr[i].to , now , gen , min(dis , tr[i].val));
    }
        
    inline int ask(int x , int y)
    {
        return ans[x][y];
    }
        
    inline void solve()
    {
        build(1 , n);
        for(int i = 1;i <= n;i++) get(i , 0 , i , inf);
    }
        
}tree;

int main()
{
    n = read() + 1 , m = read();
    for(int i = 1;i <= m;i++)
    {
        int x = read() + 1 , y = read() + 1 , z = read();
        add(x , y , z);
        add(y , x , 0);
        add(x , y , 0);
        add(y , x , z);
    }
    for(int i = 1;i <= n;i++) id[i] = i;
    tree.solve();
    q = read();
    for(int i = 1;i <= q;i++)
    {
        int x = read() + 1 , y = read() + 1;
        cout << tree.ask(x , y) << endl;
    }
    return 0;
}
```

---

## 作者：issue_is_fw (赞：1)



$首先最小割树是一颗树,有着这样一个性质$

$对于树中任意两点$s$和$t$,$s$和$t$在原图的最小割等于最小割树上$s$到$t$路径上的最小边$

构造完成之后,就可以树上倍增求两点间最小边权(就是lca的树上倍增)

考虑如何来构造

$Ⅰ.选择图中任意两点,求出最小割,在最小割树中连接这两点,边权为最小割$

$Ⅱ.这两点的最小割把图划分为两个集合,在两个集合中继续分治,重复步骤Ⅰ$

**这样分集合最后会分到集合中只有1个点,算法结束,最小割树构造完成**

$至于最小割树为什么有这样的定理,我只有自己的感性理解$

$所有读者感兴趣自行去了解吧,我比较菜,记住就好了。$

**附上有注释的模板,感觉我的代码挺易懂的**

```
#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
const int maxn=1e5+10;
struct edge{
	int to,nxt,flow;
}d[maxn]; int head[maxn],cnt=1;
void add(int u,int v,int flow){
	d[++cnt]=(edge){ v,head[u],flow },head[u]=cnt;
	d[++cnt]=(edge){ u,head[v],0 },head[v]=cnt;
}
int dis[maxn],n,m;
bool bfs(int s,int t)//普通的最大流找增广路 
{
	for(int i=0;i<=n+1;i++)	dis[i]=0;
	dis[s]=1;
	queue<int>q; q.push( s );
	while( !q.empty() )
	{
		int u=q.front(); q.pop();
		for(int i=head[u];i;i=d[i].nxt )
		{
			int v=d[i].to;
			if( dis[v]==0&&d[i].flow )
			{
				dis[v]=dis[u]+1;
				if( v==t )	return true;
				q.push( v );
			}
		}
	}
	return false;
}
int dinic(int u,int t,int flow )//普通的最大流 
{
	if( u==t )	return flow;
	int res=flow;
	for(int i=head[u];i;i=d[i].nxt )
	{
		int v=d[i].to;
		if( dis[v]==dis[u]+1&&d[i].flow )
		{
			int temp=dinic(v,t,min(res,d[i].flow) );
			res-=temp;
			if( temp==0 )	dis[v]=0;
			d[i].flow-=temp;
			d[i^1].flow+=temp;
		}
		if( res==0 )	break;
	}
	return flow-res;
}
void init()
{
	for(int i=2;i<=cnt;i+=2)//撤流操作,因为上一次跑最大流改变了图的流量,改回来 
		d[i].flow=( d[i].flow+d[i^1].flow ),d[i^1].flow=0;
}
int maxflow(int s,int t)
{
	init();//退流
	int ans=0;
	while( bfs(s,t) )	ans+=dinic(s,t,inf);
	return ans; 
}
class GHT
{
	public:
		edge d[maxn];
		int head[maxn],cnt;
		int temp1[maxn],temp2[maxn],node[maxn];
		void add(int u,int v,int flow){
			d[++cnt]=(edge){ v,head[u],flow },head[u]=cnt;
			d[++cnt]=(edge){ u,head[v],flow},head[v]=cnt;
		}
		void build(int l,int r)
		{
			if( l>=r )	return;
			int x=node[l],y=node[l+1];
			int cut = maxflow(x,y);
			add(x,y,cut );
			int top1=0,top2=0;
			//去掉x和y,分成集合temp1和temp2 
			for(int i=l;i<=r;i++)
			{
				//最后一次bfs后有深度,说明和x相连接,放在左集合temp1 
				if( dis[ node[i] ] )	temp1[++top1]=node[i];
				else	temp2[++top2]=node[i]; 
			}
			for(int i=l;i<=l+top1-1;i++)	node[i]=temp1[i-l+1];
			for(int i=l+top1;i<=r;i++)	node[i]=temp2[i-top1-l+1];
			build(l,l+top1-1); build(l+top1,r);//两个集合分别建图 
		}
		int deep[maxn],fa[maxn][23],ans[maxn][23],log2n;
		void dfs(int x,int father)
		{
			fa[x][0]=father;
			deep[x]=deep[father]+1;
			for(int i=1;i<=log2n;i++)
			{
				fa[x][i]=fa[ fa[x][i-1] ][i-1];
				ans[x][i]=min( ans[x][i-1],ans[ fa[x][i-1] ][i-1]);
			}
			for(int i=head[x];i;i=d[i].nxt )
			{
				int v=d[i].to;
				if( v!=father )
				{
					ans[v][0]=d[i].flow;
					dfs(v,x);
				} 
			}
		}
		int query(int x,int y)
		{
			int zhi=inf;
			if( deep[x]<deep[y] )	swap(x,y);
			for(int i=log2n;i>=0;i-- )
				if( deep[ fa[x][i] ]>=deep[y] )
				{
					zhi=min(zhi,ans[x][i] );
					x=fa[x][i];
				}
			if( x==y )	return zhi;
			for(int i=log2n;i>=0;i-- )
			{
				if( fa[x][i]!=fa[y][i] )
				{
					zhi=min( zhi,min( ans[x][i],ans[y][i] ) );
					x=fa[x][i],y=fa[y][i];
				}
			}
			zhi=min(zhi,min( ans[x][0],ans[y][0] ) );
			return zhi;
		}
}CUT;
void CUT_init()
{
	CUT.log2n=log2(n)+1;
	CUT.cnt=1;//是链式前向星的边编号 
	for(int i=1;i<=n;i++)	CUT.node[i]=i;//这是储存节点集合的信息 
	CUT.build(1,n);//建树 
	CUT.dfs(1,0);//倍增 
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int l,r,flow; scanf("%d%d%d",&l,&r,&flow);
		add( l,r,flow );	add(r,l,flow);//无向图网络流建边 
	}
	CUT_init();//初始化最小割树 
	int q; scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int s,t; scanf("%d%d",&s,&t);
		int _= CUT.query(s,t);
		if( _==inf )	_=-1;
		printf("%d\n",_);
	}
}
```

---

## 作者：__ycx2010__ (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P4897)

## 过程

暴力跑最小割显然会 TLE，于是引出了最小割树。

对于一个图，随机两个点 $u, v$，求从 $u$ 到 $v$ 的最小割，按照割边将图分成两部分，

删除所有割边，取而代之的是在最小割树上连接边 $(u, v)$，边权为最小割的容量，并分别对 $u,v$ 所在的连通图求最小割树。

最终以 $O(n^3m)$ 的复杂度求得了最小割树，任意两点的最小割即为树上简单路径边权最小值。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 510, M = 10010, inf = 0x3f3f3f3f;

int n, m, S, T;
int v[N], t[N];
int h[N], h2[N], e[M], c[M], ne[M], idx, pidx;
int q[N], dep[N], cur[N];

void add_edge(int u, int v, int w) {
    e[idx] = v, c[idx] = w, ne[idx] = h[u], h[u] = idx ++ ;
    e[idx] = u, c[idx] = 0, ne[idx] = h[v], h[v] = idx ++ ;
}

void add2(int u, int v, int w) {
	e[idx] = v, c[idx] = w, ne[idx] = h2[u], h2[u] = idx ++ ;
}

bool bfs() {
    memset(dep, -1, sizeof dep);
    int hh = 0, tt = 0;
    q[0] = S, dep[S] = 0;
    cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dep[j] == -1 && c[i]) {
                dep[j] = dep[t] + 1;
                cur[j] = h[j];
                if (j == T) return true;
                q[++ tt] = j;
            }
        }
    }
    return false;
}

int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        cur[u] = i;
        int j = e[i];
        if (dep[j] == dep[u] + 1 && c[i]) {
            int t = find(j, min(c[i], limit - flow));
            if (!t) dep[j] = -2;
            c[i] -= t, c[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic() {
	for (int i = 0; i < pidx; i += 2) c[i] += c[i ^ 1], c[i ^ 1] = 0;
    int res = 0, flow;
    while (bfs()) while (flow = find(S, inf)) res += flow;
    return res;
}

void build(int l, int r) {
	if (l >= r) return;
	S = v[l], T = v[l + 1];
	int ans = dinic();
	add2(S, T, ans);
	add2(T, S, ans);
	int t1 = l, t2 = r;
	for (int i = l; i <= r; i ++ )
		if (dep[v[i]] != -1) t[t1 ++ ] = v[i];
		else t[t2 -- ] = v[i];
	for (int i = l; i <= r; i ++ ) v[i] = t[i];
	build(l, t1 - 1), build(t1, r);
}

int dfs(int u, int fa, int v) {
	for (int i = h2[u]; ~i; i = ne[i]) {
		int ver = e[i];
		if (ver == fa) continue;
		if (ver == v) return c[i];
		int tmp = dfs(ver, u, v);
		if (tmp != -1) return min(tmp, c[i]);
	}
	return -1;
}

int main() {
	scanf("%d%d", &n, &m);
	n ++ ;
	memset(h, -1, sizeof h);
	memset(h2, -1, sizeof h2);
	for (int i = 1; i <= m; i ++ ) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u ++ , v ++ ;
		add_edge(u, v, w), add_edge(v, u, w);
	}
	pidx = idx;
	for (int i = 1; i <= n; i ++ ) v[i] = i;
	build(1, n);
	int Q;
	scanf("%d", &Q);
	while (Q -- ) {
		int u, v;
		scanf("%d%d", &u, &v);
		u ++ , v ++ ;
		printf("%d\n", dfs(u, -1, v));
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

试着写写最小割树的算法总结捏。

最小割树解决的问题是类似于给你一个图，要求快速查询任意两点之间的最小割（也就是以这两个点为源汇的最小割）。自然不可以每次都重新跑一遍 Dinic，要得出一个能快速查询的结构。这就是最小割树。

具体就是这样：点集初始为图中所有的点。

1.若点集内只剩下 $1$ 个点，直接终止。

2.否则从点集任意选择两个点作为源汇 $s, t$，跑一遍全局的最大流，求出 $s, t$ 之间的最小割 $w$，在树中连边 $(s, t, w)$。

3.现在的残量网络就会把点集内的点分为与 $s$ 相通和与 $t$ 相通的两个不相通点集，那么分别递归这两个点集即可。

这为啥对啊？因为你每次割，割掉的边肯定不会全部位于 $s$ 相通 / $t$ 相通的点集内，肯定会将原点集分离成两部分。

那建出来就会是一棵树，$u, v$ 之间的最小割就是树上 $u, v$ 路径上的最小边权。这很好理解，因为 $u, v$ 路径上的每一条边都代表着一种割开 $u, v$ 的方法，那么最小的边权肯定就是最小割了。

实现的话我是用 vector 传当前点集，可能慢但是好写。每次跑完网络流记得要退流，说白了就是把剩余容量恢复成原先的初始边权。

然后有几个小题题。你会发现网络流题的很多数据范围都极小，所以一些平常大数据范围下需要用一些 DS 之类的技巧维护的东西可能直接暴力就能求。

* 求不同的最小割数：把树上的所有边权放到 unique 一下即可。

* P3729：题意就是给你一个有点权无边权的无向连通图，每次给出一个 $x$，要求在你选出的点集权值和 $\ge x$ 的情况下，使得点集内的点对 $(u, v)$ 都满足 $u, v$ 之间存在至少 $k$ 条不交的路径，然后最大化这个 $k$。

  这咋做啊，首先 $u, v$ 之间在至少 $k$ 条不交的路径等价于以 $u, v$ 为源汇，所有边的容量都看作 $1$，$u, v$ 之间的最大流 $\ge k$。你发现这个 $(u, v)$ 不只一组啊，考虑转最大流为最小割。那么相当于 $u, v$ 之间最小割 $\ge k$，也就是最小割树上的 $u, v$ 之间最小边权 $\ge k$。

  考虑一个类似于 Kruskal 的过程，把最小割树上的边从大到小排序，然后依次加入。用并查集实时维护当前点权和最大的连通块的权值。因为你当前最小树边都是一个值，所以点权和最大的肯定更有竞争力。如果某个询问的 $x \le$ 目前最大点权和 $maxs$，那么用当前的最小树边 $w$ 去更新这个 $x$ 对应的答案。

* CF343E：shit。首先考虑一个类似于边分治的过程，每次选出最小割树上边权最小的边 $(u, v, w)$，考虑到无论如何总会有一组 $(a_i, a_{i + 1})$ 经过了它，所以它肯定会贡献一个 $w$ 当做最小割而被算入答案中。所以答案就是最小割树上所有边的边权和。现在考虑构造方案，通过手动分析最小割树与最小割的性质，发现先将 $u$ 所在连通块走了，再走 $(u, v)$，最后走 $v$ 所在连通块，答案最大。所以直接边分治，每次找出当前连通块内最小权边，然后往这条边两侧递归，如果连通块大小 为$1$ 就输出该点，之后退出。注意边分治最好用链式前向星，因为边分治的 $vis$ 是对边打，也方便得到反向边，然后最小割树的加边最好别和网络流的建边用同一个函数，因为这两者的反向边建法不同，然后别建树的时候把边加多了。

给一个板子代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define mr make_pair
#define fi first
#define se second 
using namespace std;
const int N = 505, M = 6005;
int n, m, q, tot = 1, to[M], nxt[M], head[M], limit[M], cut[N][N];
vector <pii> T[N];

void addedge(int u, int v, int w) {
    to[++tot] = v, limit[tot] = w, nxt[tot] = head[u], head[u] = tot;
    to[++tot] = u, limit[tot] = 0, nxt[tot] = head[v], head[v] = tot;
    return ;
}

namespace Dinic{
    int cur[M], s, t, dis[N];
    queue <int> q;
    void FlowBack() {
        for (int i = 2; i <= tot; i += 2) {
            limit[i] += limit[i ^ 1], limit[i ^ 1] = 0;
        }
        return ;
    }
    int Augmenting(int u, int rest) {
        if(u == t) return rest;
        int ret = 0;
        for (int i = cur[u]; i && rest; i = nxt[i]) {
            cur[u] = i;
            int v = to[i], c = min(rest, limit[i]);
            if(dis[v] == dis[u] + 1 && c) {
                int f = Augmenting(v, c);
                rest -= f, ret += f;
                limit[i] -= f, limit[i ^ 1] += f;
            }
        }
        if(!ret) dis[u] = -1;
        return ret;
    }
    int MaxFlow(int ss, int tt) {
        FlowBack();
        int maxflow = 0; s = ss, t = tt;
        while(1) {
            while(!q.empty()) q.pop();
            memset(dis, -1, sizeof(dis));
            memcpy(cur, head, sizeof(head));
            dis[s] = 0, q.emplace(s);
            bool bl = 0;
            while(!q.empty()) {
                if(bl) break;
                int u = q.front(); q.pop();
                for (int i = head[u]; i; i = nxt[i]) {
                    int v = to[i];
                    if(dis[v] == -1 && limit[i]) {
                        dis[v] = dis[u] + 1;
                        if(v == t) { bl = 1; break;}
                        q.emplace(v);
                    }
                }
            }
            if(dis[t] == -1) return maxflow;
            maxflow += Augmenting(s, 2e9);
        }
    }
    void Cut(vector <int> vec) {
        if(vec.size() == 1) return ;
        int ss = vec[0], tt = vec[1], w = MaxFlow(ss, tt);
        T[ss].emplace_back(tt, w), T[tt].emplace_back(ss, w);
        vector <int> vec1, vec2;
        for (int i : vec) {
            if(dis[i] != -1) vec1.emplace_back(i);
            else vec2.emplace_back(i);
        }
        Cut(vec1), Cut(vec2);
        return ;
    }
}

void dfs(int u, int ff, int s) {
    for (pii e : T[u]) {
        int v = e.fi, w = e.se;
        if(v == ff) continue;
        cut[s][v] = min(cut[s][u], w);
        dfs(v, u, s);
    }
    return ;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w;
        addedge(u, v, w), addedge(v, u, w);
    }
    vector <int> vec;
    for (int i = 1; i <= n; ++i) vec.emplace_back(i);
    Dinic::Cut(vec);   
    memset(cut, 0x3f, sizeof(cut));
    for (int i = 1; i <= n; ++i) dfs(i, 0, i);
    /*for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << i << ' ' << j << ' ' << cut[i][j] << "\n";
        }
    }*/
    cin >> q;
    for (int i = 1, u, v; i <= q; ++i) {
        cin >> u >> v; cout << cut[u][v] << "\n";
    }
    return 0;
}
```



---

