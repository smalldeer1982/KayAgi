# Tourist Guide

## 题目描述

It is not that easy to create a tourist guide as one might expect. A good tourist guide should properly distribute flow of tourists across the country and maximize the revenue stream from the tourism. This is why there is a number of conditions to be met before a guide may be declared as an official tourist guide and approved by Ministry of Tourism.

Ministry of Tourism has created a list of $ k $ remarkable cities out of $ n $ cities in the country. Basically, it means that in order to conform to strict regulations and to be approved by the ministry a tourist guide should be represented as a set of routes between remarkable cities so that the following conditions are met:

- the first and the last city of every route are distinct remarkable cities,
- each remarkable city can be an endpoint of at most one route,
- there is no pair of routes which share a road.

Please note that a route may pass through a remarkable city. Revenue stream from the tourism highly depends on a number of routes included in a tourist guide so the task is to find out a set of routes conforming the rules of a tourist guide with a maximum number of routes included.

## 样例 #1

### 输入

```
6 4 4
1 2
2 3
4 5
5 6
1 3 4 6
```

### 输出

```
2
2 1 2 3
2 4 5 6
```

## 样例 #2

### 输入

```
4 3 4
1 2
1 3
1 4
1 2 3 4
```

### 输出

```
2
1 1 2
2 3 1 4
```

# 题解

## 作者：xuan_gong_dong (赞：5)

昨晚码敲完了没保存，导致还原卡直接把我码肘没了。。。

气死了只能重新敲了一遍。

## 题面
[Tourist Guide](https://www.luogu.com.cn/problem/CF589H)
## 分析
考虑每一个联通块分开处理。

先将每一个联通块变为生成树，任意生成方式皆可。

对于每一个联通块，一定可以构造一种组合方法，使得该联通块中最多只有一个关键点无法被选择。

并且每一个组合之间一定不会有重复的路径。因为如果有重复边，那么选择组合的时候就不会这么选了，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/y5htfby3.png)

假设 $x_1$ 与 $y_1$ 是一对组合。

同时 $x_2$ 与 $y_2$ 组合与该组合有重复的部分。

那么选择的时候就会选择 $x_1$ 与 $x_2$ 作为一对组合， $y_1$ 与 $y_2$ 作为一对组合,即可避免这种重复的情况，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/h1mbj3oq.png)

找出所有组合之后，暴力求生成树上两点的距离就好了，可惜作者是个小呆呆，写了树剖，还没用上。。。

时间复杂度 $O(n)$。

谷还是交不了 codeforce 的题，好不容易切了一道黑题，白切了。
## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int nxt,to;
}edge[100010];
int head[100010],tot;
void add(int x,int y)
{
	edge[++tot].nxt=head[x];
	edge[tot].to=y;
	head[x]=tot;
}
int n,m,k;
int book[100010];//k 
int vis[100010];
int vis2[100010];
int dep[100010];
int size[100010];
int son[100010];
int top[100010];
int fa[100010];
pair<int,int>t[100010];
int cnt;
int dfs(int id,int f=0)
{
	int hys=book[id]?id:0;
//	cout<<id<<' '<<hys<<endl;
	fa[id]=f;
	dep[id]=dep[f]+1;
	vis[id]=1;
	size[id]=1;
	for(int i=head[id];i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(vis[to])continue;
		int xgd=dfs(to,id);
		size[id]+=size[to];
		if(xgd)
		{
			if(hys)
			{
				t[++cnt]=make_pair(xgd,hys);
				hys=0;
			}
			else hys=xgd;
		}
		if(son[id]==0||size[son[id]]<size[to])
		{
			son[id]=to;
		}
	}
	return hys;
}
void dfs2(int id,int topid)
{
	vis2[id]=1;
	top[id]=topid;
	if(son[id])
	{
		dfs2(son[id],topid);
	}
	for(int i=head[id];i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(!vis2[to]&&to!=son[id])
		{
			dfs2(to,to);
		}
	}
}
int ans[100010],ans2[1000010];
int l1,l2;
void lca(int x,int y)
{
//	cout<<x<<y<<endl;
	l1=0,l2=0;
	while(top[x]!=top[y])
	{
//		cout<<x<<y<<endl;
		if(dep[top[x]]>=dep[top[y]])
		{
			int e=fa[top[x]];
			for(;x!=e;x=fa[x])ans[++l1]=x;
		}
		else if(dep[top[x]]<dep[top[y]])
		{
			int e=fa[top[y]];
			for(;y!=e;y=fa[y])ans2[++l2]=y;	
		}
	}
	if(dep[x]>dep[y])
	{
		for(;x!=y;x=fa[x])ans[++l1]=x;		
	}
	else
	{
		for(;y!=x;y=fa[y])ans2[++l2]=y;		
	}
	ans[++l1]=x;
	printf("%lld ",l1+l2-1);
	for(int i=1;i<=l1;i++)
	{
		printf("%lld ",ans[i]);
	}
	for(int i=l2;i>=1;i--)
	{
		printf("%lld ",ans2[i]);
	}	
	putchar(10);
}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%lld%lld",&u,&v);
//			cout<<"QWQ";
		add(u,v);
//			cout<<"QWQ";
		add(v,u);
//		cout<<"QWQ";
	}
	for(int i=1;i<=k;i++)
	{
		int id;
		scanf("%lld",&id);
		book[id]=1;
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			int qwq=dfs(i);
			dfs2(i,i);
		}
//		cout<<dep[i];
	}
	printf("%lld\n",cnt);
	for(int i=1;i<=cnt;i++)
	{
		int x=t[i].first,y=t[i].second;
		if(x>y)swap(x,y);
		lca(x,y);
//		cout<<x<<y<<endl;
	}
	return 0;
}
```

---

## 作者：ezoixx130 (赞：3)

### 题意：
有一个n个点m条边的图，指定k个点为关键点。

每次你可以选择两个未被选择过的在图上联通的关键点，选择它们之间的一条简单路径，将这条路径上的所有边删除。

你需要输出最多能选多少对点，并且输出每对点你删除路径长度和这条路径经过的点。

### 题解：
思维题。

对于这个图每一个联通块我们分开考虑，若一个联通块中有$x$个关键点， 那么显然最多只能选择$\lfloor \frac{x}{2} \rfloor$对关键点。
下面证明一定能选择$\lfloor \frac{x}{2} \rfloor$对关键点：
如果存在两对关键点的路径有重合，那么我们可以选择这段重合的路径一侧的两个关键点作为一对，另一侧的两个关键点作为一对，这样就不会重合。
于是我们就一定能找到一种方案，使得选择的所有关键点对的路径不会重合。

考虑如何构造方案，我们在原图的每个联通块的生成树上跑一遍dfs，这个dfs返回值为这棵子树内还未匹配的关键点的编号（如果全匹配完了就是-1）。
那么如何实现这个dfs呢？对于一个儿子，如果它的dfs返回值为-1，那么就不用考虑了。否则选择另一个dfs返回值不为-1的儿子，将这两棵子树内未匹配的关键点设为匹配。很显然这样最终只会剩下0会1个关键点没有匹配，那么就返回-1或者相对应的关键点编号即可。

这样一定会有$\lfloor \frac{x}{2} \rfloor$对关键点被设为匹配，并且很显然，这些路径不会重合。输出时就暴力找lca输出路径即可。

代码：
```cpp
#include <bits/stdc++.h>
using std::vector;

#define MAXN 50010

int n,m,k,tot,dep[MAXN],fa[MAXN],matched[MAXN],left[MAXN],right[MAXN],lcnt,rcnt;
bool visit[MAXN],tag[MAXN];
vector<int> edge[MAXN];

int dfs(int u,int father)
{
	int match;
	if(tag[u])match=u;else match=-1;
	visit[u]=true;
	fa[u]=father;
	for(auto v:edge[u])
	{
		if(visit[v])continue;
		dep[v]=dep[u]+1;
		int tomatch=dfs(v,u);
		if(~tomatch)
			if(~match)
			{
				matched[tomatch]=match;
				matched[match]=tomatch;
				match=-1;
				++tot;
			}
			else match=tomatch;
	}
	return match;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	for(int i=1;i<=k;++i)
	{
		int u;
		scanf("%d",&u);
		tag[u]=1;
	}
	for(int i=1;i<=n;++i)
		if(!visit[i])dfs(i,0);
	printf("%d\n",tot);
	for(int i=1;i<=n;++i)
	{
		if(!matched[i])continue;
		int u=i,v=matched[i];
		matched[u]=matched[v]=false;
		left[lcnt=1]=u;
		right[rcnt=1]=v;
		while(u^v)if(dep[u]<dep[v])right[++rcnt]=v=fa[v];else left[++lcnt]=u=fa[u];
		printf("%d ",lcnt+rcnt-2);
		for(int i=1;i<lcnt;++i)printf("%d ",left[i]);
		for(int i=rcnt;i>=1;--i)printf("%d ",right[i]);
		puts("");
	}
}
```


---

## 作者：Ebola (赞：1)

# 【CF589H】Tourist Guide

先考虑一棵树的情况。容易发现，只要关键点数量为偶数个，那一定存在某种匹配方式，能将它们两两匹配成功。树已如此，图就更应该如此了。

所以我们可以轻易算出匹配对数。令size\[p\]表示第p个联通块中关键点的数量，则答案为Σ(size\[p\] / 2)

考虑到图上方案很难输出，树上相对容易一些，而把图变成树并不影响两两匹配成功的事实，于是我们可以把图的生成树造出来，随便生成一棵树即可

然后直接搜索即可。记fuck\[x\]表示节点x及其下方第一个未匹配的点，然后在子树中遇到一个可匹配的点就匹配上去。如果子树中仍然存在未匹配的点，就将fuck\[x\]传给它的父亲

路径的输出直接暴力跳到LCA即可，沿途记录经过的点

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<20)+5;
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline int read()
    {
        int x=0;char c=Get();
        while(!isdigit(c)) c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x;
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
}

using IO::read;
using IO::print;
using IO::putc;
const int N=50010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n,m,tot;
int dep[N],fa[N],fuck[N];
int ffa[N],sz[N];
bool spd[N];

int find(int x){return ffa[x]==x?x:ffa[x]=find(ffa[x]);}

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void getpath(int x,int y)
{
    static int path1[N],path2[N];
    int tot1=0,tot2=0;
    while(x!=y)
    {
        if(dep[x]>dep[y]) path1[++tot1]=x,x=fa[x];
        else path2[++tot2]=y,y=fa[y];
    }
    path1[++tot1]=x;
    print(tot1+tot2-1);putc(' ');
    for(int i=1;i<=tot1;i++) print(path1[i]),putc(' ');
    for(int i=tot2;i>=1;i--) print(path2[i]),putc(' ');
    putc('\n');
}

void dfs(int u,int la)
{
    fuck[u]=spd[u]?u:0;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs(v,u);
        if(!fuck[v]) continue;
        if(!fuck[u]) fuck[u]=fuck[v];
        else getpath(fuck[u],fuck[v]),fuck[u]=0;
    }
}

int main()
{
    n=read();m=read();tot=read();
    for(int i=1;i<=n;i++) ffa[i]=i;
    for(int i=1,u,v;i<=m;i++)
    {
        u=read();v=read();
        if(find(u)==find(v)) continue;
        ffa[find(u)]=find(v);
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int i=1,x;i<=tot;i++)
        x=read(),spd[x]=1,sz[find(x)]++;
    int ans=0;
    for(int i=1;i<=n;i++)
        if(ffa[i]==i) ans+=sz[i]/2;
    print(ans);putc('\n');
    for(int i=1;i<=n;i++)
        if(ffa[i]==i) dfs(i,0);
    IO::flush();
    return 0;
}
```



---

