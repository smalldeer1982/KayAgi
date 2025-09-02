# [PA 2014] Fiolki

## 题目描述

化学家吉丽想要配置一种神奇的药水来拯救世界。

吉丽有 $n$ 种不同的液体物质，和 $n$ 个药瓶（均从 $1$ 到 $n$ 编号）。初始时，第 $i$ 个瓶内装着 $g_i$ 克的第 $i$ 种物质。

吉丽需要执行一定的步骤来配置药水，第 $i$ 个步骤是将第 $a_i$ 个瓶子内的所有液体倒入第 $b_i$ 个瓶子，此后第 $a_i$ 个瓶子不会再被用到。瓶子的容量可以视作是无限的。

吉丽知道某几对液体物质在一起时会发生反应产生沉淀，具体反应是 $1$ 克 $c_i$ 物质和 $1$ 克 $d_i$ 物质生成 $2$ 克沉淀，一直进行直到某一反应物耗尽。生成的沉淀不会和任何物质反应。

当有多于一对可以发生反应的物质在一起时，吉丽知道它们的反应顺序。每次倾倒完后，吉丽会等到反应结束后再执行下一步骤。

吉丽想知道配置过程中总共产生多少沉淀。

## 说明/提示

对于 $100\%$ 的数据，$0\le m<n\le 2\times 10^5$，$0\le k\le 5\times 10^5$，$1\le g_i\le 10^9$，$1\le a_i,b_i,c_i,d_i\le n$，$a_i\ne b_i$，$c_i\ne d_i$。

## 样例 #1

### 输入

```
3 2 1
2 3 4
1 2
3 2
2 3```

### 输出

```
6```

# 题解

## 作者：PineappleSummer (赞：16)

[题目传送门](https://www.luogu.com.cn/problem/P5578)

LCA 好题，细节挺多的，来写个题解吧。

首先分析样例，发现是这么一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/zi6q8ime.png)

嗯，这不是仅仅图，这是树。题目上说：
>第 $i$ 个步骤是将第 $a_i$ 个瓶子内的所有液体倒入第 $b_i$ 个瓶子，此后第 $a_i$ 个瓶子不会再被用到。

这不就是说一个儿子只能有一个父亲，而一个父亲可以有多个儿子吗？这不就是树？

建树。**注意：应该把两个反应物向生成物连一条边，把 $b$ 自己拆成反应物和生成物，这样就可能会形成森林（不一定联通）。** 此处感谢@[Starlight_Glimmer](https://www.luogu.com.cn/user/41165)题解的指导。

建树代码：
```cpp
for(int i=1;i<=m;i++)
{
	int u,v;
	cin>>u>>v;
	G[n+i].push_back(pos[u]);
	G[n+i].push_back(pos[v]);
	pos[v]=n+i;//pos[v]表示点v的生成物所在的点编号，初始化 pos[v]=v
}
```

我们进一步分析，发现对于可以进行反应的点对 $(u,v)$，如果 $(u,v)$ 有公共祖先（即有 LCA），他们就**可能**进行反应，反之则**不可能**进行反应。

预处理和倍增求 LCA 都是板子，这里就不放了，可以在最后的代码里查看。


```cpp
for(int i=n+m;i>=1;i--)
	if(!d[i]) bfs(i);//图不一定联通
for(int i=1;i<=k;i++)
{
	int u,v;
	cin>>u>>v;
	int LCA=lca(u,v);//求LCA
	if(!LCA) continue;//没有公共祖先
	e[++tot]=Edge{u,v,LCA,d[LCA],i};//如果有，存入e结构体数组
}
```

$e$ 是一个结构体数组，其存储着每一对会发生反应的点对 $(u,v)$，其定义如下：
```cpp
struct Edge
{
	int u,v,l,dep,id;//l为u,v的lca，dep为l的深度，id为反应的优先级
}e[K];
```

$e$ 数组是无序的，而反应是有序的，考虑对 $e$ 数组进行排序。先按照 $l$ 的深度从大到小排序，因为 $l$ 的深度越大，越早发生反应；$l$ 的深度相同的按照反应的优先级从大到小排序。

```cpp
bool cmp(Edge a,Edge b)
{
	return a.dep>b.dep||(a.dep==b.dep&&a.id<b.id);
}
```

遍历每一个可以进行反应的点对 $(u,v)$，沉淀即为 $\min(g_u,g_v)\times 2$，$\min(g_u,g_v)$ 记为 $s$，用 $g_u$ 和 $g_v$ 分别减去 $s$，再拿 $ans$ 加上新增加的沉淀即可。
```cpp
for(int i=1;i<=tot;i++)
{
	int s=min(g[e[i].u],g[e[i].v]);
	g[e[i].u]=max(0ll,g[e[i].u]-s),g[e[i].v]=max(0ll,g[e[i].v]-s);
	ans+=(s<<1);
}
```

最后输出 $ans$。

完整代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4e5+10,K=5e5+10,logg=21;
int n,m,k,d[N],t,f[N][logg],pos[N],tot;
vector<int>G[N];
ll ans=0,g[N];
void bfs(int s)
{
	queue<int>q;
	d[s]=1;
	q.push(s);
	while(q.size())
	{
		int x=q.front();
		q.pop();
		for(auto i:G[x])
		{
			if(d[i]) continue;
			d[i]=d[x]+1;
			f[i][0]=x;
			for(int j=1;j<=t;j++)
				f[i][j]=f[f[i][j-1]][j-1];
			q.push(i);
		}
	}
}
int lca(int x,int y)
{
	if(d[x]>d[y]) swap(x,y);
	for(int i=t;i>=0;i--)
		if(d[f[y][i]]>=d[x]) y=f[y][i];
	if(x==y) return x;
	for(int i=t;i>=0;i--)
	{
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i]; 
	}
	return f[x][0];
}
struct Edge
{
	int u,v,l,dep,id;
}e[K];
bool cmp(Edge a,Edge b)
{
	return a.dep>b.dep||(a.dep==b.dep&&a.id<b.id);
}
int main()
{
//    freopen("input.in","r",stdin);
//    freopen("output.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	t=log2(n+m)+1;
	for(int i=1;i<=n;i++) cin>>g[i],pos[i]=i;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		G[n+i].push_back(pos[u]);
		G[n+i].push_back(pos[v]);
		pos[v]=n+i;
	}
	for(int i=n+m;i>=1;i--)
		if(!d[i]) bfs(i);
	for(int i=1;i<=k;i++)
	{
		int u,v;
		cin>>u>>v;
		int LCA=lca(u,v);
		if(!LCA) continue;
		e[++tot]=Edge{u,v,LCA,d[LCA],i};
	}
	sort(e+1,e+tot+1,cmp);
	for(int i=1;i<=tot;i++)
	{
		int s=min(g[e[i].u],g[e[i].v]);
		g[e[i].u]=max(0ll,g[e[i].u]-s),g[e[i].v]=max(0ll,g[e[i].v]-s);
		ans+=(s<<1);
	}
	cout<<ans;
    return 0;
}
```

如果觉得这篇题解写得好，请不要忘记点赞，谢谢！

---

## 作者：huanyue (赞：12)

本蒟蒻第一次写题解,有不当之处,多多体谅

我们先考虑大模拟,直接进行模拟实验步骤有,同时在每一步反应中检测所有可生成的沉淀$O(mk)$,然后看数据范围,显然没有那么简单.

同样我们可以通过数据范围可以猜到这大概是$O(n log n)$,重新读题

 第$i$个步骤是将第$a_i$个瓶子内的所有液体倒入第$b_i$个瓶子，此后第$a_i$个瓶子**不会再被**用到。

然后我们可以画一张图来清晰的表示这个过程



![](https://cdn.luogu.com.cn/upload/image_hosting/k1pm4ivs.png)







这张图直接让我想起了政治老师在网课中说的: 窗外那绿油油的是什么,那不是树吗.

我们不难发现

1.这是二叉树构成的森林

2.所有叶子节点就是我们的化学试剂

3.沉淀就是两个试剂的**LCA**

同样,不难想到深度大,说明反应先发生,这样我们就只用按照反应顺序模拟就行了

反应产生的沉淀是两个试剂中量较小的两倍

答案是不是已经呼之欲出,看上去过程很~~简单~~,实际上实现有很多细节

那就放CODE了
```cpp
/*
 * @Author: Huanyue 
 * @Date: 2020-02-13 07:45:25 
 * @Last Modified by: Huanyue
 * @Last Modified time: 2020-02-13 08:41:08
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
#define rgi register
typedef long long ll;
using namespace std;

inline void write(rgi int x)
{
    if (x < 0)
    {
        putchar('-'), x = -x;
    }
    if (x >= 10)
    {
        write(x / 10);
    }
    putchar('0' + x % 10);
}

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = ((x << 3) + (x << 1) + (ch ^ 48));
        ch = getchar();
    }
    return x * f;
}

const int N = 2e5 + 10;
const int M = 2e5 + 10;
ll ans;
int n, m, k, head[N + M], cnt, pos[N];
int g[N], dep[N + M], f[N + M][20], tot;

struct Edge
{
    int next, to;
} e[(N + M) << 1]; //两倍开边
struct Q
{
    int x, y, sc, dep, id;
} q[500010];

bool cmp(const Q &a, const Q &b)
{
    return a.dep == b.dep ? a.id < b.id : a.dep > b.dep;//深度优先
}
void add_edge(int x, int y)
{
    e[++cnt] = (Edge){head[x], y};
    head[x] = cnt;
    e[++cnt] = (Edge){head[y], x};
    head[y] = cnt;
}
void dfs(int x)
{
    for (int i = 1; i <= 19; i++)
        f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = head[x]; i; i = e[i].next)
        if (e[i].to != f[x][0])
        {
            f[e[i].to][0] = x;
            dep[e[i].to] = dep[x] + 1;
            dfs(e[i].to);
        }
}
int lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    int d = dep[x] - dep[y];
    for (int i = 19; i >= 0; --i)
        if ((d >> i) & 1)
            x = f[x][i];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; --i)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
int main()
{
    n = read(), m = read(), k = read();

    for (rgi int i = 1; i <= n; i++)
    {
        pos[i] = i;
        g[i] = read();
    }

    for (rgi int i = 1; i <= m; i++)
    {
        int u = read(), v = read(), sc = n + i;
        add_edge(pos[u], sc); //都向生成物加边
        add_edge(pos[v], sc);
        pos[v] = sc;
    }
    for (rgi int i = n + m; i >= 1; --i) //注意是n+m,因为有m个反应物
        if (!f[i][0])
            dfs(i); //倍增LCA的预处理
    for (rgi int i = 1; i <= k; i++)
    {
        int c = read(), d = read(), sc;
        sc = lca(c, d);
        if (!sc)
            continue;                           //无法生成就过
        q[tot++] = (Q){c, d, sc, dep[sc], tot}; //加入模拟列表
    }
    sort(q, q + tot, cmp); //按照顺序反应
    for (int i = 0; i < tot; i++)
    {
        int x = q[i].x, y = q[i].y;
        int use = min(g[x], g[y]);
        g[x] -= use, g[y] -= use;
        ans += (use << 1);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：OIer_ACMer (赞：2)

# 题目解析：

本题，我在这给大家介绍一种不一样的写法，供大家参考。

根据题目要求，主人公在做实验时，每种反应只会发生一次，因为**一次反应至少会把其中一种物质反应完**，之后就不会再有这种物质出现，也就不会再发生这种反应了。根据这个条件，我们可以将所有能发生的反应选出来，但是其先后顺序已知，因此我们就需要求出这些反应是**在什么时候进行并按此排序，得到的就是反应出现的顺序**。然后我们遍历每种反应，找出每次反应的最小值进行贪心。

然而，一个一个遍历实在是耗费时间，我们便可以用带权并查集，将每两个点发生的反应时间赋值给两个点之间的边权 $tim$ 之上。不过要注意的是，这种并查集不能路径压缩，要按照秩合并，最终还要注意如果两种反应发生时间相同，要按照题目给的优先顺序排。

# 代码如下：

```

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005;
int n, m, k, g[N];
int father[N], siz[N], tim[N], dep[N];
int find(int x)
{
    if (x == father[x])
    {
        return x;
    }
    int fa = find(father[x]);
    dep[x] = dep[father[x]] + 1;
    return fa;
}
void un(int x, int y, int t)
{
    x = find(x);
    y = find(y);
    if (x == y)
    {
        return;
    }
    if (siz[x] < siz[y])
    {
        father[x] = y;
        siz[y] += siz[x];
        tim[x] = t;
    }
    else
    {
        father[y] = x;
        siz[x] += siz[y];
        tim[y] = t;
    }
}
int merge(int u, int v)
{
    if (find(u) != find(v))
    {
        return -1;
    }
    if (dep[u] < dep[v])
    {
        swap(u, v);
    }
    int ans = 0;
    while (dep[u] != dep[v])
    {
        if (tim[u] > ans)
        {
            ans = tim[u];
        }
        u = father[u];
    }
    while (u != v)
    {
        if (tim[u] > ans)
        {
            ans = tim[u];
        }
        if (tim[v] > ans)
        {
            ans = tim[v];
        }
        u = father[u];
        v = father[v];
    }
    return ans;
}
struct query
{
    int c, d, id, t;
} w[500005];
inline bool cmp(query x, query y)
{
    if (x.t != y.t)
    {
        return x.t < y.t;
    }
    return x.id < y.id;
}
signed main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
        siz[i] = 1;
        cin >> g[i];
    }
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        un(a, b, i);
    }
    int cnt = 0;
    for (int i = 1; i <= k; i++)
    {
        int c, d;
        cin >> c >> d;
        int t = merge(c, d);
        if (t == -1)
        {
            continue;
        }
        else
        {
            w[++cnt] = (query){c, d, i, t};
        }
    }
    sort(w + 1, w + cnt + 1, cmp);
    int ans = 0;
    for (int i = 1; i <= cnt; i++)
    {
        int val = min(g[w[i].c], g[w[i].d]);
        g[w[i].c] -= val;
        g[w[i].d] -= val;
        ans += val << 1;
    }
    cout << ans << endl;
    return 0;
}

```

---

## 作者：Starlight_Glimmer (赞：2)

[My Blog](https://www.cnblogs.com/lyttt/p/14044526.html)

[题目链接](https://www.luogu.com.cn/problem/P5578)

### 题目解析

~~神奇题目，洛谷评分居然是普及+，果然还是我太菜了吗$qwq$~~

题意我也看了好一会儿，我以为它是一个类似于化合反应的东西，把试剂$a$倒入试剂$b$之后，药水就全部变成试剂$b$了，而质量为两者的和（质量守恒定律）。

但实际上题目的意思只是把这两种药水混合在一起，是物理变化，只有生成的那个沉淀是化学变化。

首先可以想到一个$O(mk)$的大暴力，但是数据范围显然过不去。

考虑到重要的是这些沉淀们各自的顺序，因为顺序不同，发生反应时反应物的已消耗量可能不同，也就是反应物的量可能不同，产物的量可能不同。

所以重点在于判断各个沉淀的顺序。

神奇的做法来喏，就是其实把两个反应物向生成物连一条边（我刚开始想的是直接$a->b$连边了，没有想到把$b$自己拆成反应物和生成物，然后没有做出来），那么就形成了一个二叉树森林（不一定联通），叶子结点都是原来的试剂，如果两种试剂会反应，那么它们会在$lca$的位置相遇，然后反应生成沉淀，生成的沉淀质量为$2$倍较小质量数，然后各自减去这个转化量。

显然$lca$深度比较大沉淀先发生，于是我们就找出了这些沉淀的顺序。注意$lca$深度相同时，要按照给出顺序排，题目说了按照反应优先顺序给出这$k$对可以反应的物质。

用倍增求$lcs$，时间复杂度应该为$O(k\times log(n+m))$

------

### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define N 200005
#define M 200005
#define K 500005
#define INF 0x3f3f3f3f
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f*x;
}
int n,m,k;
int g[N];
vector<int>G[N+M];
int pos[N];//当前试剂i的结点编号 
int f[N+M][25],dep[N+M];
struct node{
	int a,b,cd,id;
}q[K];
int cnt;//有效沉淀反应个数 
LL ans;
void add(int u,int v)
{
	G[v].push_back(u);
}
bool cmp(node p,node q)
{
	if(p.cd==q.cd) return p.id<q.id;//注意k对试剂按照反应优先顺序给出
	//我刚开始以为同一层的顺序可以随便 实际上不行 因为试剂有量的多少 
	return p.cd>q.cd;
}
void dfs(int u)
{
	for(int i=1;i<=20;i++)
		f[u][i]=f[f[u][i-1]][i-1];
	for(int i=0;i<G[u].size();i++)
	{
		int v=G[u][i];
		if(v==f[u][0]) continue;
		f[v][0]=u;
		dep[v]=dep[u]+1;
		dfs(v);
	}
}
int LCA(int u,int v)
{
	int tmp;
	if(dep[u]<dep[v]) tmp=u,u=v,v=tmp;
	for(int j=20;j>=0;j--)
		if(dep[f[u][j]]>=dep[v])
			u=f[u][j];
	if(u==v) return u;
	for(int j=20;j>=0;j--)
		if(f[u][j]!=f[v][j])
			u=f[u][j],v=f[v][j];
	return f[u][0];
}
int main()
{
	n=rd(),m=rd(),k=rd();
	for(int i=1;i<=n;i++)
	{
		pos[i]=i;
		g[i]=rd();
	}
	for(int i=1;i<=m;i++)
	{
		int a=rd(),b=rd();
		add(pos[a],n+i);
		add(pos[b],n+i);
		pos[b]=n+i;
	}
	for(int i=n+m;i>=1;i--)
		if(f[i][0]==0)//可能不连通 即二叉树森林 
			dfs(i);
	for(int i=1;i<=k;i++)
	{
		int a=rd(),b=rd(),lca=LCA(a,b);
		if(!lca) continue;//这对沉淀不会出现
		node tmp; tmp.a=a,tmp.b=b,tmp.cd=dep[lca],tmp.id=i;
		q[++cnt]=tmp;
	}
	sort(q+1,q+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)
	{
		int del=min(g[q[i].a],g[q[i].b]);
		g[q[i].a]-=del,g[q[i].b]-=del;
		ans=ans+2ll*del;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Starmoon_dhw (赞：0)

# 前言
某外启发式合并的练习题，一看题解区，大佬们都用 LCA 为什么？于是有了此篇题解。

# 题目大意：
有 $n$ 种不同的药品，并且每种药品仅有一瓶，题目已知每瓶中药物的数量。有 $m$ 个操作，每次操作输入两个数 $a_i$ $b_i$ 表示将 $a_i$ 种的药物倒入 $b_i$。另外题目给出了 $k$ 个反应，按照反应顺序给出。

# 简要分析
其实直接用并查集表示来模拟药物合成的操作，并且将每次操作后的物质用动态数组存储即可。

我们可以将配方都存储起来：

```
s[x[i]].push_back(i);
s[y[i]].push_back(i);
```
然后再处理 $m$ 个操作的时候默认 $u_i$ 代表小的。具体的先将 $u_i$ 和 $v_i$ 合并到同一个集合，然后去便利上面存储配方的动态数组 $s$ 寻找符合这次操作的配方，找到之后将其存入另一个动态数组 $q$ 存储的原因是后续可能不止发生一个化学反应。

```
for(auto k:s[u[i]])
{
    if(find(x[k])==find(y[k]))
        q.push_back(k);
    else
        s[v[i]].push_back(k);
}
```

处理完这些之后，我们先按照反应的优先顺序排序 $q$ 这也是之前 $s$ 种存储编号的原因。排序完之后再按照各个操作减去消耗掉的物质即可，注意要两份并且按照化学反应规律要按照少的那份去算。

```
sort(q.begin(),q.end());
for(auto k:q)
{
	int t=min(g[x[k]],g[y[k]]);
	g[x[k]]-=t;
	g[y[k]]-=t;
  ans+=t*2;
}
```
# 完整代码

```cpp
#include<bits/stdc++.h>
//#define int long long 
using namespace std;
const int N=2e5+5;
const int M=5e5+5;
int fa[N],u[N],v[N],g[N],x[M],y[M],n,m,k,T;
long long ans;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * f;
}
vector<int>s[N];
int find(int x)
{
	if(x==fa[x])
		return fa[x];
	return fa[x]=find(fa[x]);
}
signed main()
{
	n=read(),m=read(),T=read();
	for(int i=1;i<=n;i++)
		g[i]=read(),fa[i]=i;
	for(int i=1;i<=m;i++)
		u[i]=read(),v[i]=read();
	for(int i=1;i<=T;i++)
	{
		x[i]=read(),y[i]=read();
		s[x[i]].push_back(i);
		s[y[i]].push_back(i);
	}
	for(int i=1;i<=m;i++)
	{
		if(s[u[i]].size()>s[v[i]].size())
			swap(s[u[i]],s[v[i]]);
		fa[find(u[i])]=find(v[i]);
		vector<int>q;
		for(auto k:s[u[i]])
		{
			if(find(x[k])==find(y[k]))
				q.push_back(k);
			else
				s[v[i]].push_back(k);
		}
		sort(q.begin(),q.end());
		for(auto k:q)
		{
			int t=min(g[x[k]],g[y[k]]);
			g[x[k]]-=t;
			g[y[k]]-=t;
			ans+=t*2;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：lw393 (赞：0)

给个启发式合并做法。

这个启发式合并主要是把反应给启发式合并掉。

我们处理的是这个集合中的试剂能跟什么试剂反应。这个可以用并查集快速处理。

例如当前的要合并两个集合 $S_1 = \{u,v,w\},S_2 = \{x,y,z\}$，假设有这样几种反应（按顺序） $(u,x),(u,y),(u,a),(v,y)$。那我们可以取出可以反应的 $(u,x),(u,y),(v,y)$ 并计算答案，然后合并其他的。这就是我们程序的流程。

然后至于优先级处理问题，我们存储反应的编号，再进行排序就可以解决。

然后时间复杂度就是启发式的复杂度 $O(n\log n)$。

```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;

struct dsu{
  int n; vector<int>father;
  void init(int n) { father.resize(n + 1); for(int i = 1; i <= n; i++) father[i] = i; }
  int find(int x) { return (father[x] == x ? x : father[x] = find(father[x])); }
  void bing(int a, int b) { int x = find(a), y = find(b); if(x == y) return; father[y] = x; }
  bool same(int a, int b) { return find(a) == find(b); }
  bool is_root(int x) { return father[x] == x; }
}d1;
int u[N], v[N], x[N], y[N], g[N];
vector<int>S[N];
#define pb push_back

void solve(){
  int n, m, k; cin >> n >> m >> k;
  d1.init(n);
  for(int i = 1; i <= n; i++) cin >> g[i];
  for(int i = 1; i <= m; i++) cin >> u[i] >> v[i];
  for(int i = 1; i <= k; i++) cin >> x[i] >> y[i];
  for(int i = 1; i <= k; i++) S[x[i]].pb(i), S[y[i]].pb(i);
  long long ans = 0;
  for(int i = 1; i <= m; i++) {
    u[i] = d1.find(u[i]), v[i] = d1.find(v[i]);
    if(S[u[i]].size() < S[v[i]].size()) swap(u[i], v[i]);
    vector<int>V;
    for(auto id : S[v[i]]) {
      if((d1.find(x[id]) == u[i] && d1.find(y[id]) == v[i]) || (d1.find(x[id]) == v[i] && d1.find(y[id]) == u[i])) V.push_back(id);
      else S[u[i]].push_back(id);
    }
    sort(V.begin(), V.end(), less<int>());
    for(auto id : V) {
      int t = min(g[x[id]], g[y[id]]); 
      g[x[id]] -= t, g[y[id]] -= t;
      ans += 2 * t;
    }
    d1.bing(u[i], v[i]);
  }
  cout << ans << '\n';
}

signed main(){
  ios::sync_with_stdio(false);
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
```

---

## 作者：yinianxingkong (赞：0)

# [P5578 [PA2014] Fiolki](https://www.luogu.com.cn/problem/P5578)

# 前言

还是调了有一会儿的，但总体来讲还是一道比较基础的绿题。

# 解法分析

对我这种语文不好的读题是一个难点，大意是有几种元素会沉淀，问按照操作顺序会沉淀多少。

首先题目告诉我们一个瓶子最多用一次，即点出度至多为 $1$。那么构成的一定是森林。这里不需要建虚点，直接建树即可（当然边的方向要反过来）。

再次观察反应这个东西，容易发现两个元素反应只会在 `LCA` 处发生。用并查集判断两个元素是否在同一树里，然后将这个反应挂在他们 `LCA` 处。接下来我们只需要遍历树求答案就可以了。

# 具体实现

一定注意这题的**顺序**：

1. 深度低的 `LCA` 处的反应发生在深度高的反应的前面。这一点显然，因为一个瓶子动过一次就不会再动了。

2. 先倒的瓶子在后倒的瓶子前面反应。这个可以给边赋权加入时间，挂询问的时候直接加权两点的合并时刻，处理的时候排序即可。加的权就是两点所属子树与 `LCA` 连边的最大值，倍增即可。

3. 先输入的反应较后输入的反应先反应。这个在给询问加权的时候加一个复权就可以了。

That's All.

# 代码

代码中上面未提到的部分就请自行理解了。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace TYX_YNXK{
	#define il inline
	#define bl bool
	#define ll long long
	#define vd void
	#define N 500005
	#define INF 0x3f3f3f3f
	#define pii pair<int,int>
	#define pb push_back
	#define MP make_pair
	#define fi first
	#define se second
	#define DEBUG cout<<"You are right,but you are wrong"<<'\n'
	#define END cout<<"You are right,but you are right now"<<'\n'
	int n,m,q,s[N],out[N],fath[N],fa[N][23],dep[N],dis[N];ll ans;
	vector<pii > G[N];
	int find(int x){return x==fath[x]?x:fath[x]=find(fath[x]);}
	vd dfs(int u){
		for(int i=1;i<=20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
		for(pii v:G[u]) if(v.fi!=fa[u][0]) fa[v.fi][0]=u,dep[v.fi]=dep[u]+1,dis[v.fi]=v.se,dfs(v.fi);
	}
	il int lca(int u,int v){
		if(dep[u]<dep[v]) swap(u,v);
		for(int i=20;i>=0;i--) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
		if(u==v) return u;
		for(int i=20;i>=0;i--) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
		return fa[u][0];
	}
	il int get(int u,int v){
		if(u==v) return 0;
		for(int i=20;i>=0;i--) if(dep[fa[u][i]]>dep[v]) u=fa[u][i];
		return dis[u];
	}
	vector<pair<pii,pii > > V[N];
	vd dfs1(int u){
		for(pii v:G[u]){
			if(v.fi==fa[u][0]) continue;
			dfs1(v.fi);
		}
		sort(V[u].begin(),V[u].end());
		for(pair<pii,pii > pos:V[u]){
			int tmp=min(s[pos.se.fi],s[pos.se.se]);
			ans+=tmp*2,s[pos.se.fi]-=tmp,s[pos.se.se]-=tmp;
		}
	}
	signed main(){
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++) cin>>s[i],fath[i]=i;
		for(int i=1,u,v;i<=m;i++) cin>>u>>v,G[v].pb(MP(u,i)),++out[u],fath[find(u)]=find(v);
		for(int i=1;i<=n;i++) if(!out[i]) dep[i]=1,dfs(i);
		for(int i=1;i<=q;i++){
			int u,v;cin>>u>>v;
			if(find(u)!=find(v)) continue;
			int d=lca(u,v);V[d].pb(MP(MP(max(get(u,d),get(v,d)),i),MP(u,v)));
		}
		for(int i=1;i<=n;i++){
			if(!out[i]) dfs1(i);
		}
		cout<<ans;
		return 0;
	}
}
signed main(){
	TYX_YNXK::main();
	return 0;
}
```

# 后记

欢迎 `hack`！

---

