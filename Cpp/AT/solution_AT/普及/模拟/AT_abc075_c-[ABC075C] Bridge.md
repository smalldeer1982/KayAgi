# [ABC075C] Bridge

## 题目描述

给你一个$N$个点$M$条边无重边无自环的无向图。

求有几个桥（自行百度）。

## 说明/提示

$1 \leq N \leq 50$

$N-1 \leq M \leq N(N-1)/2$

## 样例 #1

### 输入

```
7 7
1 3
2 7
3 4
4 5
4 6
5 6
6 7```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3
1 2
1 3
2 3```

### 输出

```
0```

## 样例 #3

### 输入

```
6 5
1 2
2 3
3 4
4 5
5 6```

### 输出

```
5```

# 题解

## 作者：Diamiko (赞：5)

## 核心算法：Tarjan求割边（桥）

### 1.什么是割边

>假设有连通图G，e是其中一条边，如果G-e是不连通的，则边e是图G的一条割边。此情形下，G-e必包含两个连通分支。

以上内容摘自度娘百科。

用人话来说，就是图如果去掉这条边，整个图就不连通了，那么就是个割边。
![](https://bkimg.cdn.bcebos.com/pic/7aec54e736d12f2e30ff62944fc2d56284356848?x-bce-process=image/watermark,g_7,image_d2F0ZXIvYmFpa2U4MA==,xp_5,yp_5)

图中的$v_3,v_4$和$v_4,v_5$这两条边就是割边


------------

### 2.常用算法

**Tarjan**


------------

### 3.怎么求割边

1. 前置知识：关于Tarjan算法

在Tarjan算法中，每个点有两个十分重要的量，dfn，low

dfn：表示dfs遍历到该节点的序号，也就是顺序值

low：表示当前顶点不通过父亲节点能访问到的祖先节点（父亲节点上面的节点）中的最小顺序值

2. 求法

用u来表示当前深搜的点，v表示与u有连边的点

如果`low[v]==dfn[u]`，表示还可以回到父亲。

而`low[v]>dfn[u]`则表示连父亲都回不到了。

倘若顶点v不能回到祖先，也没有另外一条路能回到父亲，那么u-v就是割边。

儿子节点不经过这条边就可以访问到祖先节点，那么就要满足：`low[v] > dfn[u]`。

如果`low[v] == dfn[u]`，节点v还可以通过其他路径可以回到u。

但是只包含条件`low[x] > dfn[u]`时，说明没有任何一条路可以出了u-v边外，由u到达v，此时说明，u-v之间的边为一条割边。

这里没有Tarjan算法基础的可能听不大懂，可以参考博客

[Tarjan算法求割点和割边](https://blog.csdn.net/li1615882553/article/details/84678722)

[图的割点算法vs图的割边算法
](https://blog.csdn.net/wtyvhreal/article/details/43530613)


------------

### 4.代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
struct Node
{
    int head,low,dfn;
}node[55];
struct Edge
{
    int next,to;
}edge[5005];
int n,m,cnt,root,deep;
//n,m为点数，边数
//cnt为链式前向星建图中的边数变量
//root为Tarjan时的根节点
//deep为搜索深度
int ans;
//记录割边数量，答案
void addEdge(int u,int v)
{
    edge[++cnt].next=node[u].head;
    node[u].head=cnt;
    edge[cnt].to=v;
}
void Tarjan(int u,int father)
{
    node[u].dfn=node[u].low=++deep;
    //更新
    for(int e=node[u].head;e;e=edge[e].next)
    {
        int v=edge[e].to;
        if(!node[v].dfn)
        {
            //v还没被搜索过，就进行搜索
            Tarjan(v,u);
            node[u].low=min(node[u].low,node[v].low);
            //更新low值
            if(node[u].dfn<node[v].low)ans++;
            //符合这个条件，证明e是割边，答案加一
        }
        else if(v!=father)
        {
            node[u].low=min(node[u].low,node[v].dfn);
            //更新low值
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        addEdge(a,b);
        addEdge(b,a);
        //切记双向边
    }
    for(int i=1;i<=n;i++)
    {
        if(!node[i].dfn)
        {
            root=i;
            Tarjan(i,root);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：small_john (赞：3)

## 前言

题解里竟然没有并查集。

## 思路

简单的并查集。

一条一条边试。不要这条边的情况下，如果做一次并查集后这条边连接的两个点不是联通的，即最大祖宗不同，那么答案加一。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100;
int n,m,ans,x[N],y[N],f[N];
int find(int x)
{
	if(f[x]==x) return x;
	return f[x] = find(f[x]);
}
signed main()
{
	cin>>n>>m;
	for(int i = 1;i<=n;i++)
		f[i] = i;
	for(int i = 1;i<=m;i++)
		cin>>x[i]>>y[i];
	for(int i = 1;i<=m;i++)
	{
		for(int j = 1;j<=n;j++)
			f[j] = j;
		for(int j = 1;j<=m;j++)
			if(j!=i)
				f[find(x[j])] = find(y[j]);
		if(find(x[i])!=find(y[i])) ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：CarroT1212 (赞：3)

### 题目大意

给定一张 $n$ 个点 $m$ 条边的无向连通图，保证图无自环无重边，问这张图中有几个桥。

+ 什么是桥？

如果删去图中的一条边后，这个图中的连通块数量会增加，则这条边就是桥。

数据范围：$2 \le N \le 50$，$N-1 \le M \le \min\{\frac{N(N+1)}{2},50\}$。

------------

### 解法分析

不会 Tarjan 的看过来。

上面桥的定义换句话说其实就是：

如果删去图中的一条边后，这条边的两个端点不连通，则这条边就是桥。因为题目给的是连通图。

又看到这个怎么乱搞都能过的数据范围 $M \le 50$，我们就可以快乐地使用并查集了。

我们每次枚举一条边删掉，然后跑一遍并查集，看看这条边两端的点是否连通（在同一个集合里），如果不在就说明这条边是桥，答案加一。

如果你不会并查集，搜索也是个不错的选择。

但是考虑到这种解法的效率问题，各位有时间还是尽早学了 Tarjan 再把这题切一遍吧……

------------

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
const int N=57;
int n,m,ans,a[N][2],f[N];
int find(int x) { return f[x]==x?x:f[x]=find(f[x]); }
int main() {
	cin>>n>>m;
	for (int i=1;i<=m;i++) cin>>a[i][0]>>a[i][1];
	for (int i=1;i<=m;i++) {
		for (int j=1;j<=n;j++) f[j]=j; //并查集初始化
		for (int j=1;j<=m;j++) if (i!=j) f[find(a[j][0])]=find(a[j][1]); //加边，并跳过正在枚举的边
		if (find(a[i][0])!=find(a[i][1])) ans++; //不连通
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：VinstaG173 (赞：3)

这是一道裸的Tarjan求桥啊……如果还不知道桥是什么，可以上cnblogs或者博客园搜一下dalao的博客。本蒟蒻至今没有写过与桥有关的博客。

Tarjan，是一个玩DFS玩到成果让人怀疑人生的巨佬，其中割点和桥（割边）是最基础的（还有BCC，EBC和SCC，感兴趣的同学可以不知怎么转转到洛谷日报去参观学习一下）。

用Tarjan算法求割边，首先要跑一遍DFS（连DFS都不知道的同学可以左转试炼场去找些搜索题练练手），其中记录两个数dfn和low，dfn[u]=i表示u是第i个被访问到的结点，low[u]=j表示只途经DFS到u的时候没有访问过的结点可以到达的dfn值最小的结点dfn值为j。

简单来说，有一个式子：
$low[u]=min\{min\{low[v]\},dfn[u]\}$，其中v是u被访问时没有访问过且与u连通的结点。

那么有了两个数组，怎么求桥呢？

如果对于u，有一个v使得$low[v]>dfn[u]$，那么边(u,v)就是桥。因为到了v以后无论怎么走，不经过(u,v)打死也到不了u。

双倍经验&更多咨询：[P3388](https://www.luogu.org/problemnew/show/P3388)与[其题解区](https://www.luogu.org/problemnew/solution/P3388)

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
int n,m,cnt,idx;
int dfn[100001];
vector<int> G[100001];
inline int Tjcv(int u,int fa)
{
	int child=0,lowu;
	lowu=dfn[u]=++idx;
	for(int i=0,v;i<G[u].size();i++)
	{
		v=G[u][i];
		if(v!=fa)
		{
			if(!dfn[v])
			{
				++child;
				int lowv=Tjcv(v,u);
				lowu=min(lowu,lowv);
				if(lowv>dfn[u])
				{
					++cnt;
				}
			}
			else
			{
				lowu=min(lowu,dfn[v]);
			}
		}
	}
	return lowu;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0,u,v;i<m;i++) 
	{
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++) 
	{
		if(!dfn[i])
		{
			Tjcv(i,-1);
		}
	}
	printf("%d\n",cnt);
	return 0;
}
```

---

## 作者：yazzkl (赞：2)

# 图论好题

给一个图，桥就是指图中这样的边，删除它以后整个图不连通。【就看1能不能到达其他所有的点就可以了】

本题就是求删去多少条边后不联通的裸题。（貌似在哪里见过）

(题意还是好理解的，操作可能就有~~一点问题~~)

对于操作，推荐用**tarjan**

dfn[u]指在dfs中搜索到u节点的次序值，low[u]指dfs栈中u能追溯到的最早栈中节点从次序号。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=500;
vector<int> G[maxn];
int dfn[maxn],low[maxn];
int n,m,u,v,dep,ans;

void init()
{
    dep=ans=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    for(int i=0;i<=n;i++) G[i].clear();
}

void Tarjan(int u,int fa)
{
    dfn[u]=low[u]=++dep;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!dfn[v]){
            Tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]) ans++;
        }else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main()
{
    while(cin>>n>>m)
    {
        init();
        for(int i=0;i<m;i++){
            cin>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        Tarjan(1,-1);
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

~~打表出奇迹，爆搜过样例~~
# 一定是恶意评分！
# 一定是恶意评分！
# 一定是恶意评分！
# 裸的DFS
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x[15005],y[15005];
bool vis[15005];
vector<int> g[15005];
long long ans;
void dfs(int x)
{
    if(vis[x])
        return;
    vis[x]=1;
    for(int i=0;i<g[x].size();i++)
        dfs(g[x][i]);//枚举所有边
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        cin>>x[i]>>y[i];
    for(int i=1;i<=m;i++)
    {
        memset(vis,0,sizeof(vis));
        for(int j=1;j<=n;j++)
            g[j].clear();
        for(int j=1;j<=m;j++)
            if(j!=i)
            {
                g[x[j]].push_back(y[j]);
                g[y[j]].push_back(x[j]);//构图
            }
        int cnt=0;
        for(int j=1;j<=n;j++)
            if(!vis[j])
            {
                dfs(j);
                cnt++;
            }
        if(cnt>1)
            ans++;//边数的个数（CNT）
    }
    cout<<ans;
    return 0;
}
```


---

