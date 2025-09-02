# 13th Labour of Heracles

## 题目描述

You've probably heard about the twelve labors of Heracles, but do you have any idea about the thirteenth? It is commonly assumed it took him a dozen years to complete the twelve feats, so on average, a year to accomplish every one of them. As time flows faster these days, you have minutes rather than months to solve this task. But will you manage?

In this problem, you are given a tree with $ n $ weighted vertices. A tree is a connected graph with $ n - 1 $ edges.

Let us define its $ k $ -coloring as an assignment of $ k $ colors to the edges so that each edge has exactly one color assigned to it. Note that you don't have to use all $ k $ colors.

A subgraph of color $ x $ consists of these edges from the original tree, which are assigned color $ x $ , and only those vertices that are adjacent to at least one such edge. So there are no vertices of degree $ 0 $ in such a subgraph.

The value of a connected component is the sum of weights of its vertices. Let us define the value of a subgraph as a maximum of values of its connected components. We will assume that the value of an empty subgraph equals $ 0 $ .

There is also a value of a $ k $ -coloring, which equals the sum of values of subgraphs of all $ k $ colors. Given a tree, for each $ k $ from $ 1 $ to $ n - 1 $ calculate the maximal value of a $ k $ -coloring.

## 说明/提示

The optimal $ k $ -colorings from the first test case are the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1466D/d2af7a338e536cf5cb74dc12f223baf263c91efb.png)In the $ 1 $ -coloring all edges are given the same color. The subgraph of color $ 1 $ contains all the edges and vertices from the original graph. Hence, its value equals $ 3 + 5 + 4 + 6 = 18 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1466D/4196e1299ca3444421f255a73f95765dbb2837c9.png)In an optimal $ 2 $ -coloring edges $ (2, 1) $ and $ (3,1) $ are assigned color $ 1 $ . Edge $ (4, 3) $ is of color $ 2 $ . Hence the subgraph of color $ 1 $ consists of a single connected component (vertices $ 1, 2, 3 $ ) and its value equals $ 3 + 5 + 4 = 12 $ . The subgraph of color $ 2 $ contains two vertices and one edge. Its value equals $ 4 + 6 = 10 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1466D/5febb146f8282f40f79782da3d6b349a0e6be93a.png)In an optimal $ 3 $ -coloring all edges are assigned distinct colors. Hence subgraphs of each color consist of a single edge. They values are as follows: $ 3 + 4 = 7 $ , $ 4 + 6 = 10 $ , $ 3 + 5 = 8 $ .

## 样例 #1

### 输入

```
4
4
3 5 4 6
2 1
3 1
4 3
2
21 32
2 1
6
20 13 17 13 13 11
2 1
3 1
4 1
5 1
6 1
4
10 6 6 6
1 2
2 3
4 1```

### 输出

```
18 22 25
53
87 107 127 147 167
28 38 44```

# 题解

## 作者：SSerxhs (赞：4)

结论：同色边必连通

证明：若存在同色边形成连通块 $A$ 和 $B$ 且 $A$ 权值更大，则可以把 $B$ 的颜色改为与它旁边任何一个颜色。由于 $B$ 不对答案贡献显然答案不劣，由于每次修改至少减少一个连通块所以总能调整到不能再调整为止，即同色边均连通的状态。

于是题意转化为划分为 $k$ 个连通块使得每个连通块点权和最大，我们可以直接考虑每个点的贡献，显然每个点周围若有 $x$ 种颜色则贡献了 $x$ 次。

考虑树形 $dp$ 设 $f_{u,x}$ 表示考虑第 $u$ 个点及其连父边用了 $x$ 种颜色的答案，列出方程可以发现这和 $x$ 的唯一关系就是当 $x\leftarrow x+k$ 时 $ans\leftarrow ans+k*v_u$ 

所以完全不需要做一个显式的树形 dp，直接按照 $val$ 降序做贡献就可以了。由于 $k\le d_u$，所以每个点可以做的贡献次数是度数次。 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e6+2;
struct Q
{
	int w,rd;
	bool operator<(const Q &o) const {return w>o.w;}
};
Q q[N];
ll ans;
int n,c,i,t,m,x,y,j,k,la,s,p;
inline void read(register int &x)
{
	register int c=getchar(),fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int main()
{
	read(t);
	while (t--)
	{
		read(n);
		ans=0;
		for (i=1;i<=n;i++) read(q[i].w),q[i].rd=-1,ans+=q[i].w;
		for (i=1;i<n;i++) read(x),read(y),++q[x].rd,++q[y].rd;
		sort(q+1,q+n+1);i=1;printf("%lld",ans);
		while (i<=n)
		{
			if (q[i].rd) --q[i].rd,ans+=q[i].w,printf(" %lld",ans); else ++i;
		}puts("");
	}
}
```

---

## 作者：Soulist (赞：2)


首先条件有多余的，因为同色只会有一个连通块。

考虑在这个连通块的最高点上打一个标记，可以转换为给定一棵树，打 $k-1$ 个标记（注意根必然有标记）情况下的贡献和。

如果 $i$ 处打标记，则额外贡献的为其父亲的权值。

每个父亲最多贡献 $\deg (i)-1$ 次。

第 $i$ 个点复制 $\deg(i)-1$ 次，排个序，前 $k$ 项之和加上基础贡献即为答案，复杂度 $\mathcal O(n\log n)$

---

## 作者：georgehe (赞：2)

# 题意简介
有一颗 $n$ 个节点，$n - 1$ 条边的树。树上每个点都有一个非负点权。现在要给这棵树进行 $n - 1$ 次染色，每次分别用 1，2...$n - 1$ 种颜色给这棵树进行染色。每种颜色所形成的联通块可以得到它所连接的所有节点的点权。如果一种颜色会形成多个联通快，每种颜色只会得到自己所有联通块中获得最多分数联通快的分数。请计算并输出在对树进行 1，2...$n - 1$ 次染色后分别所能得到的最大分数。

## 核心思路
这是一道结论题。

首先我们能够想到如果用一种颜色进行染色，那么得分一定是树上所有节点的点权之和，因为每个点权的值一定大于等于 0。这时候我们可以考虑两种颜色进行染色的最大的分。看样例可以得知两次染色的最优方案仍然可以覆盖整棵树，但是最大节点的值可以被计算两次，如果最大节点有两条边的话。

通过感性思考我们可以得知，每添加一种颜色实际上可以增加一个节点的值因为可以把新添加的颜色的一个终点放在一个点权较大的节点上。

结论：一种颜色是树上点权之和，每添加一种颜色可以添加一个节点的点权。需要注意每个节点有多少条边就能被多少种不同的颜色染色，但是一个节点被计算的次数不能超过他的入度和出度之和。

## 上代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 200010
int t,n;
long long ans;
struct node{
  long long cnt,val;
}edge[maxn*2];

bool cmp(struct node a,struct node b)
{
  return a.val>b.val;
}

int main()
{
  cin>>t;
  while(t--)
  {
    cin>>n;
    ans=0;
    for(int i=1;i<=n;i++)
    {
      cin>>edge[i].val;
      edge[i].cnt=0;
      ans+=edge[i].val;
    }
    for(int i=1;i<=n-1;i++)
    {
      long long from,to;
      cin>>from>>to;
      edge[from].cnt++;
      edge[to].cnt++;
    }
    sort(edge+1,edge+n+1,cmp);
    int now=1;
    cout<<ans<<" ";
    for(int i=2;i<=n-1;i++)
    {
      while(edge[now].cnt==1)
        now++;
      ans+=edge[now].val;
      edge[now].cnt--;
      cout<<ans<<" ";
    }
    cout<<endl;
  }
  return 0;
}

```


---

## 作者：liuzhongrui (赞：0)

## 思路

首先，对于每个测试用例，我们需要读入树的顶点权重以及边的信息。然后利用一个数组 $d$ 来记录每个顶点的度数（度数：相邻边的数量），另一个数组 $a$ 存储顶点的权重，数组 $b$ 用来存储非叶子节点的权重。

接下来，我们计算出树的所有顶点权重总和，并初始化一个变量 $ans$ 用来记录染色方案的总值。然后遍历每个顶点，更新 $d$ 数组中的度数信息。

接下来，我们将非叶子节点的权重按照从大到小的顺序排序，然后递减地加入到总值 $ans$ 中，并输出当前的染色方案的最大值。

整体思路就是根据题目给出的染色方案的定义，通过逐步将非叶子节点的权重加入到总值中，找到最优的染色方案，然后输出即可。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int d[100010]; ll a[100010],b[200010];
int main() {
	int T,n,i,u,v,cnt;
	cin>>T;
	while (T--) {
		cin>>n;
		cnt=0;
		ll ans=0;
		for (i=1; i<=n; i++) {
			cin>>a[i];
			ans+=a[i];
		}
		for (i=1; i<n; i++) {
			cin>>u>>v;
			d[u]++;
			d[v]++;
		}
		for (i=1; i<=n; i++) {
			d[i]--;
			while (d[i]) b[++cnt]=a[i],d[i]--;
		}
		sort(b+1,b+cnt+1);
		cout<<ans<<' ';
		for (i=cnt; i>=1; i--)
			ans+=b[i],cout<<ans<<' ';
		puts("");
	}
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：0)

## CF1466D 【13th Labour of Heracles】

### 题意

+ $n$ 个点的树，每条边有一个颜色，每个点有一个点权 $a$；
+ 连通块的权值为子块上所有点的权值和；
+ 颜色为 $i$ 的同色子图为所有颜色为 $i$ 的边和与这些边相连的点组成的子图，权值为该同色子图的所有连通块中最大的权值；
+ 树的权值定义为所有同色子图的权值和；
+ 对于任意 $x\in[1,n)$，求当有 $x$ 种不同的颜色时，树可能的最大权值；
+ 多组数据，$n\le10^5,a_i\le10^9$。

### 做法

因为同色子图的权值仅仅和权值最大的连通块有关，所以容易想到同色子图一定要连通。否则，对于每个同色子图，一定可以把权值不是最高的连通块内的边改成已经存在的颜色，结果一定不会更劣。

现在每个点的贡献为与它相连的边的颜色种数乘该点的权值，最大的贡献为它的度数乘该点的权值。每多一个颜色，有且只有一个点的贡献再加上一次它的权值。

贪心地，选权值更大的点增加贡献一定不会更劣，当然前提是该点贡献未达到最大的贡献。

---

