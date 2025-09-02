# Harmonious Graph

## 题目描述

You're given an undirected graph with $ n $ nodes and $ m $ edges. Nodes are numbered from $ 1 $ to $ n $ .

The graph is considered harmonious if and only if the following property holds:

- For every triple of integers $ (l, m, r) $ such that $ 1 \le l < m < r \le n $ , if there exists a path going from node $ l $ to node $ r $ , then there exists a path going from node $ l $ to node $ m $ .

In other words, in a harmonious graph, if from a node $ l $ we can reach a node $ r $ through edges ( $ l < r $ ), then we should able to reach nodes $ (l+1), (l+2), \ldots, (r-1) $ too.

What is the minimum number of edges we need to add to make the graph harmonious?

## 说明/提示

In the first example, the given graph is not harmonious (for instance, $ 1 < 6 < 7 $ , node $ 1 $ can reach node $ 7 $ through the path $ 1 \rightarrow 2 \rightarrow 7 $ , but node $ 1 $ can't reach node $ 6 $ ). However adding the edge $ (2, 4) $ is sufficient to make it harmonious.

In the second example, the given graph is already harmonious.

## 样例 #1

### 输入

```
14 8
1 2
2 7
3 4
6 3
5 7
3 8
6 8
11 12
```

### 输出

```
1
```

## 样例 #2

### 输入

```
200000 3
7 9
9 8
4 5
```

### 输出

```
0
```

# 题解

## 作者：灵茶山艾府 (赞：3)

对每个点，计算出其所在连通分量的最大的点。然后从小到大遍历每个点，同时维护当前能访问到的最大的点 $max$，若当前点所在连通分量的最大的点不等于 $max$，则需要从当前连通分量连一条边到最大的点所在的连通分量。

并查集可以完成上述操作，注意在合并的时候，总是把小的合并到大的上。


AC 代码（Golang）：

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, m, v, w, ans int
	Fscan(in, &n, &m)

	// 初始化并查集
	fa := make([]int, n+1)
	for i := range fa {
		fa[i] = i
	}
	var find func(int) int
	find = func(x int) int {
		if fa[x] != x {
			fa[x] = find(fa[x])
		}
		return fa[x]
	}
	merge := func(from, to int) int {
		// 把小的合并到大的上，并返回大的
		ff, ft := find(from), find(to)
		if ff > ft {
			ff, ft = ft, ff
		}
		fa[ff] = ft
		return ft
	}

	for ; m > 0; m-- {
		Fscan(in, &v, &w)
		merge(v, w)
	}
	max := -1
	for i := range fa {
		if i > max {
			max = find(i)
		} else if find(i) != max {
			max = merge(i, max)
			ans++
		}
	}
	Print(ans)
}
```


---

## 作者：fengxiaoyi (赞：2)

### 修改日志

$2022/12/16\text{ }\text{ }22:42$：修改了部分变量的名称。

### 思路

**暴力+并查集，加一点点的优化即可。**

这题的有点暴力的样子，对于每个节点 $i$，初始 $f_i=i$（常规的并查集初值）。唯一不同的是，每个代表元还要记两个变量 $X_i,Y_i$，其中 $X_i$ 表示以 $i$ 为代表元的连通块的节点编号的最大值，$Y_i$ 表示以 $i$ 为代表元的连通块的节点编号的最小值。

输入一条边就合并一次连通块

```
void H(int k1,int k2){//合并操作
	int x=Find(k1),y=Find(k2);
	fa[x]=y;
	mn[y]=min(mn[x],mn[y]);
	mx[y]=max(mx[x],mx[y]);
}
```

**接下来就是暴力+优化**

对于每个节点 $i$，查找他的代表元 $p$，暴力搜一遍 $Y_p\sim X_p$，查找其（指的是编号为 $Y_p\sim X_p$ 的节点）的代表元是不是 $p$，如果不是，合并这两个并查集。

这里有个小细节：就是合并的并查集的代表元必须是 $p$。

#### 就这么暴力？这题这么水？

其实并不是这样的，照这样暴力肯定会超时。

#### 优化？

查找到的代表元 $p$ 以后，看看之前有没有访问到这个简单 $p$，如果没有，标记为访问，去暴力搜。

#### 复杂度：

玄学复杂度，但是可以过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,num,si[200010],ans;
int fa[200010],mx[200010],mn[200010];
bool v[200010];
int Find(int k){
	if(fa[k]==k) return k;
	return fa[k]=Find(fa[k]);
}
void H(int k1,int k2){
	int x=Find(k1),y=Find(k2);
	fa[x]=y;
	mn[y]=min(mn[x],mn[y]);
	mx[y]=max(mx[x],mx[y]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=mx[i]=mn[i]=i;
	for(int i=1;i<=m;i++){
		int x1,x2;
		scanf("%d%d",&x1,&x2);
		H(x1,x2);
	}
	for(int i=1;i<=n;i++){
		int f=Find(i);
		if(v[f]) continue;
		v[f]=1;
		for(int j=mn[f]+1;j<mx[f];j++){
			int fj=Find(j);
			if(fj!=f) H(fj,f),ans++;
		}
	}
	return !printf("%d",ans);
}
```


---

## 作者：李伟业 (赞：2)

# 题目
#### n个点（编号1-n）

#### m条边

#### 无自环，无重边

#### 对于给出的图中，**任意**可达的两点（1<=u<=v<=n) 

#### 如果u也到{u+1，u+2，......，v-1}这些点

####  那么称这个图为 和谐图 。

#### 原图可能不是和谐图，求要使它变成和谐图最少要加入的边的条数。


# 思路
#### 通过把第一个样例画出来可以很看出，原图可以分成3个连通块。

#### 既然是联通块，那么是不是可以用并查集去做啊？

#### 每一个连通块中，如果最小值到最大值之间不连续，

#### 那么就需要新加入缺少的那个点（或者是另外一个连通块）。

#### 这么一想并查集还挺简单的对不对。

#### ~~先处理每个连通块的最大值，最小值，然后for(1,n)~~，

#### ~~判断i点所在的连通块是否和谐~~，

#### ~~不和谐的话，从块的最小值-最大值之间遍历找出应该加入的点（或者连通块）~~。

#### 开开心心的敲完，样例都过了，交，WA，自闭，改！

#### 问题出在每次新加入连通块时，

#### 当前连通块的最大值和最小值都可能会发生改变。

#### 另外，和谐了的连通块要标记，不要再找块中的点了，否则会T

```cpp
//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=2e5+5;
const int inf=0x7fffffff/2;
int n,m;
int fa[maxn];
int vis[maxn];
struct edge// point set
{
    int u;
    int v;
    int w;
}e[maxn];
struct ex// to record every collection's extreme
{
    int mi;
    int mx;
    int sum;
}ex[maxn];
int father(int x)//find the collection's boss
{
    if(x!=fa[x])
        fa[x]=father(fa[x]);
    return fa[x];
}
void join(int x,int y)//D ans S,join them.And update every collection's extreme
{
    ex[father(y)].mi=min(ex[father(y)].mi,ex[father(x)].mi);
    ex[father(y)].mx=max(ex[father(y)].mx,ex[father(x)].mx);
    ex[father(y)].sum+=ex[father(x)].sum;
    fa[father(x)]=father(y);
}
int judge_node(int x)
{
    x=father(x);
    int mi=ex[x].mi;
    int mx=ex[x].mx;
    int sum=ex[x].sum;
    if(mi==-inf)// the point of haven't form edge
        return 1;
    mi=((mi-1)*mi)/2;
    mx=((mx+1)*mx)/2;
    if((mx-mi)!=sum)
        return 1;
    else return 0;
}
void init(int u,int v)// to calculate max and min ,init it at first
{
    ex[u].sum=u;
    ex[v].sum=v;
    ex[u].mx=u;
    ex[u].mi=u;
    ex[v].mx=v;
    ex[v].mi=v;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;
        ex[i].mi=inf;
        ex[i].mx=-inf;
        ex[i].sum=0;
    }
    for(int i=1;i<=m;i++)
    {
        cin>>e[i].u>>e[i].v;
        init(e[i].u,e[i].v);
    }
    for(int i=1;i<=m;i++)
    {
        if(father(e[i].u)!=father(e[i].v))
        {
            join(e[i].u,e[i].v);
        }
    }
    int ans=0;
    int mxx=-inf,last;
    for(int i=1;i<=n;i++)
    {
        if(judge_node(i)&&vis[father(i)]==0)
        {
            int l=ex[father(i)].mi;
            int r=ex[father(i)].mx;
            for(int j=l;j<r;j++)
            {
                if(father(j)!=father(i))
                {
                    join(i,j);
                    ans++;
                    last=j;
                }
                l=ex[father(i)].mi;
                r=ex[father(i)].mx;
            }
            vis[father(last)]=1;
        }
    }
    cout<<ans<<endl;
    return 0;
}

```
//没有彩蛋


---

## 作者：ZLCT (赞：0)

# CF1253D Harmonious Graph
## 题目翻译
定义一张无向图合法，仅当若存在 $l,r$ 之间存在路径，那么必定有 $l$ 与 $[l+1,r-1]$ 中所有点都存在路径。问在一个给定的 $n$ 个点，$m$ 条边的图中至少添加几条边能使图合法。
## 传统艺能——转换题意
两个点之间存在路径，就是表示两个点连通，而 $l$ 与 $[l+1,r-1]$ 中所有点都存在路径，就表示 $[l,r]$ 全部连通。\
于是题目就变成了把 $[1,n]$ 分成若干子段，使得每个子段间都是连通的且封闭。\
那么我们有一个性质：如果能构造一组合法方案，那么我们一定不会把方案中两个不连通的连通块连接。\
这个性质是比较显然的，因为首先我们既然合法了，那再添一条边肯定不优了，并且或许还会使序列不合法。\
但是这个性质太弱了，我们需要继续挖掘一下。\
我们考虑 $1$ 号点最终形成的连通块，根据题意一定与 $max_{v\in{G_1}}$ 相连通。\
而对于 $i\in[1,max_{v\in{G_1}}]$ 的点，都至少与 $[i,max_{v\in{G_i}}]$ 相连通。\
根据连通的传递性（自己瞎取的名，理解就行），$1$ 所在连通块的右端点一定会如此递归下去，直到这个连通块没有向后的连边。\
根据我们第一个证明的性质，此时我们一定会新起一个连通块并继续操作。\
那么如何递归查找这个连通块的右端点呢？\
首先连通性这个问题我们可以想到用并查集解决。\
那么我们对于并查集可以维护 $maxx_i$ 表示 $i$ 所在连通块目前的右端点，每次连边（并查集合并）的时候更新一下就行。\
那如何去连边呢？我们考虑一种类似双指针的思路，我们枚举 $i$ 表示枚举到的左端点，并不断根据上面的递归思路枚举 $j$，若 $i,j$ 不连通，则连一条 $i,j$ 的边，由于 $[i,j-1]$ 是连通的，所以我们可以从 $j$ 走到 $i$，这样 $[i,j]$ 也全部连通了。\
但是单单这样枚举时间复杂度是 $O(n^2)$ 的，所以我们也向双指针一样每次更新完当前连通块直接跳到下一个连通块的起点，这样一共只需要枚举 $n$ 个点，加上并查集的 $\alpha$，复杂度一共为 $O(n\alpha(n))$。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+233;
int fa[N],rk[N];
int n,m,maxx[N],ans;
int find(int x){
    if(x==fa[x])return x;
    maxx[fa[x]]=max(maxx[fa[x]],maxx[x]);
    return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    x=find(x);y=find(y);
    if(x==y)return;
    if(rk[x]==rk[y]){
        rk[x]++;fa[y]=x;
        maxx[x]=max(maxx[x],maxx[y]);
    }else if(rk[x]>rk[y]){
        fa[y]=x;
        maxx[x]=max(maxx[x],maxx[y]);
    }else{
        fa[x]=y;
        maxx[y]=max(maxx[x],maxx[y]);
    }
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        fa[i]=i;maxx[i]=i;
    }
    for(int i=1;i<=m;++i){
        int u,v;cin>>u>>v;
        maxx[u]=max(maxx[u],v);
        maxx[v]=max(maxx[v],u);
        merge(u,v);
    }
    for(int i=1;i<=n;i=maxx[find(i)]+1){
        for(int j=i+1;j<=maxx[find(i)];++j){
            if(find(i)==find(j))continue;
            merge(i,j);
            ans++;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

