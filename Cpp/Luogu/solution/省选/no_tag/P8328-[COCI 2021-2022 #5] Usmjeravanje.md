# [COCI 2021/2022 #5] Usmjeravanje

## 题目描述

永无岛有两条河流。每条河流沿岸分布有若干个城市，其中城市数量分别为 $a,b$。

对于位于同一条河流沿岸的 $i,j$ 两个城市，如果 $i \lt j$，那么可以通过水路从城市 $i$ 到城市 $j$。

永无岛的居民们已经决定修建 $m$ 条连接第一条河流的城市 $x_i$ 和第二条河流的城市 $y_i$ 的单向航线，但方向有待商榷。

当两个城市之间可以通过水路或航线互相到达时，则称它们是连通的。在所有的城市中，存在若干个城市集合，使得集合中没有任何一对城市是连通的。请为每条航线选择一个方向，使得所有集合中包含元素最多的集合元素个数最少。

## 说明/提示

**【样例 1 解释】**

最优的方案可以使得每对城市都连通，因此答案为 $1$。

**【数据规模与约定】**

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$1 \le a,b,m \le 15$。
- Subtask 2（30 pts）：$1 \le a,b \le 1000$。
- Subtask 3（60 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le a,b,m \le 2 \times 10^5$，$1 \le x_i \le a$，$1 \le y_i \le b$。

**【说明】**

本题采用自行编写的 [Special Judge](https://www.luogu.com.cn/paste/uv2vgxxa)。如果对此有疑问或想要 hack，请[私信编写者](https://www.luogu.com.cn/chat?uid=137367)或发帖。

**【来源】[COCI 2021-2022#5](https://hsin.hr/coci/contest5_tasks.pdf) Task 5 Usmjeravanje。**

## 样例 #1

### 输入

```
5 3
4
1 2
2 3
3 1
5 3```

### 输出

```
1
1 1 0 0```

## 样例 #2

### 输入

```
6 6
4
1 2
3 2
4 3
5 6```

### 输出

```
9
1 0 1 1```

## 样例 #3

### 输入

```
8 7
7
1 3
2 1
3 4
5 6
6 5
6 7
8 7```

### 输出

```
5
1 0 1 1 0 1 0```

# 题解

## 作者：Thunder_S (赞：5)

## Solution

看到任意两点均不互连，想到与之类似的强连通分量，预示着这题将使用 $\text{Tarjan}$ 来完成。

先考虑把边的方向确定下来。

注意到有贡献的连法只有以下三种：

![](https://s1.ax1x.com/2022/07/02/j1I3X8.png) ![](https://s1.ax1x.com/2022/07/02/j1IJ0g.png) ![](https://s1.ax1x.com/2022/07/02/j1IGnS.png)

观察发现，这三种连法中右下的点一定是向左上连出的。

根据这个发现，我们有了以下思路：

1. 将边排序，第一关键字 x 从小到大（上河岸），第二关键字 y 从大到小（下河岸）。

2. 枚举每条边，如果当前边下河岸的点在目前所有边的最右端，那么说明这个点在某种连法中一定处在右下的位置，所以此边的类型为 1。

3. 其余边类型为 0。

现在已经确定了边的方向，剩下的就是模板题：有向图中求强连通分量的个数。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 400005
using namespace std;
int na,nb,n,m,tot,num,mx,cnt,ans,sum[N],sta[N*10],dfn[N<<1],low[N<<1];
bool bj[N<<1];
struct node {int x,y,id;} edg[N];
struct edge {int to,next,head;} a[N*3];
bool cmp(node x,node y)
{
    if (x.x<y.x) return true;
    if (x.x>y.x) return false;
    return x.y>y.y;
}
void add(int x,int y) {a[++tot].to=y;a[tot].next=a[x].head;a[x].head=tot;}
void dfs(int x)
{
    dfn[x]=low[x]=++cnt;
    sta[++num]=x;
    bj[x]=true;
    for (int i=a[x].head;i;i=a[i].next)
    {
        int y=a[i].to;
        if (!dfn[y]) dfs(y),low[x]=min(low[x],low[y]);
        else if (bj[y]) low[x]=min(low[x],dfn[y]);
    }
    if (dfn[x]==low[x])
    {
        ++ans;
        while (sta[num]!=x) bj[sta[num--]]=false;
        bj[sta[num--]]=false;
    }
}
int main()
{
    freopen("neverland.in","r",stdin);
    freopen("neverland.out","w",stdout);
    scanf("%d%d",&na,&nb);
    for (int i=1;i<na;++i)
        add(i,i+1);
    for (int i=1;i<nb;++i)
        add(i+na,i+na+1);
    scanf("%d",&m);
    for (int i=1;i<=m;++i)
        scanf("%d%d",&edg[i].x,&edg[i].y),edg[i].id=i;
    sort(edg+1,edg+m+1,cmp);
    for (int i=1;i<=m;++i)
    {
        if (edg[i].y>mx) mx=edg[i].y,add(edg[i].y+na,edg[i].x),sum[edg[i].id]=1;
        else add(edg[i].x,edg[i].y+na),sum[edg[i].id]=0;
    }
    n=na+nb;
    for (int i=1;i<=n;++i)
        if (!dfn[i]) dfs(i);
    printf("%d\n",ans);
    for (int i=1;i<=m;++i)
        printf("%d ",sum[i]);
    return 0;
}
```

---

## 作者：Rem_CandleFire (赞：2)

~~COCI 一堆 SPJ~~

### 题目大意与做法

本题的题目有理解难度，关键在于以下两点

- **图的形状**

- **对题目中集合的理解**

我们将从对这两点的分析中找出解题的线索（以样例一为例）。

对于**第一点**，读题之后可以得到这样一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5o5oiakb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图所示，两边箭头表示水路，中间的线表示航线（方向待定）。于是我们就对图有了一个清晰的认识：两侧的节点相当于顺次有道路单向连接，中间有单向航线需要确定方向

对于**第二点**，我们尝试给出集合稍微形式一点的定义：

设左河岸和右河岸分别有 $n$ 个与 $m$ 个城市。

设所有节点组成的全集 $U=\{1,2,3,\ldots,n+m-1,n+m\}$

我们记 $x,y$ 不互相可达为 $x\nleftrightarrow y$

那么题目要求的集合为：

$S=\{x\in U|\forall y \in S ,x \neq y,x\nleftrightarrow y \}$(不规范，能理解就行，轻喷)

人话就是：任意两个城市均不连通（即互相可达）。

现在来想想：**如何构造这样的集合？**

**由果溯因**：假设所有的航线已经确定了方向，那么图就成了一个有向图。于是就可以想到有向图中的著名概念：**强联通分量**

因为每个强联通分量中的任意两个节点均联通，所以 **$S$ 中的任意两个元素均不在同一个强联通分量中**。

于是我们就可以在每个强联通分量中任取一个节点加入 $S$ 中。

为了让元素最多的集合的元素尽可能小，我们必须尽可能让每一个强联通分量更大。

现在的目标很明确了：**构造环使强联通分量尽可能大（即其个数尽可能少）**

题目理解与初步思路到此结束。

---

### 具体做法

考虑到河流的作用，我们对边进行排序，使一条边的 $x$ 从小到大，两条边 $x$ 相等时 $y$ 从大到小。

然后让尽可能小的 $y$ 连到尽可能大的 $x$（类似贪心的思想），从而尽可能地构造回去的路线。

（其实我感觉这个过程想象一个工厂流水线中途把产品回收重新过流程会更好理解）

剩下的就是 tarjan 模版求 SCC 个数了。

### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int size=4e5+5;
int n,m,ecnt,tim,top,scc_cnt,dir[size];
int dfn[size],sta[size],low[size],ins[size];
vector<int> g[size];
struct edge{
	int x,y,id;
}e[size];
bool cmp(edge a,edge b)
	{ return a.x!=b.x?a.x<b.x:a.y>b.y; }//排序 
void tarjan(int u)
{
	sta[++top]=u; ins[u]=1;
	dfn[u]=low[u]=++tim;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(!dfn[v]) 
			tarjan(v) , low[u]=min(low[u],low[v]);
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		scc_cnt++;
		int v;
		do{
			v=sta[top]; top--;
			ins[v]=0;
		}while(v!=u);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
		g[i].push_back(i+1);
	for(int i=1;i<m;i++)
		g[i+n].push_back(i+n+1); //把右河岸的点并入 
	scanf("%d",&ecnt);
	int x,y;
	for(int i=1;i<=ecnt;i++)
		scanf("%d%d",&e[i].x,&e[i].y), e[i].id=i;
	sort(e+1,e+1+ecnt,cmp);
	int hy=0;
	for(int i=1;i<=ecnt;i++)
	{
		if(e[i].y>hy)
		{
			g[e[i].y+n].push_back(e[i].x);
			hy=e[i].y; dir[e[i].id]=1;
		} 
		else g[e[i].x].push_back(e[i].y+n);
	}
	n+=m;
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i);
	printf("%d\n",scc_cnt);
	for(int i=1;i<=ecnt;i++)
		printf("%d ",dir[i]);

	return 0;
}
```

---

