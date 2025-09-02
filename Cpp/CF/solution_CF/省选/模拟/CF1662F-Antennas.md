# Antennas

## 题目描述

# Antennas


$ n $ 架间距相等的天线站成一排，从左到右以 $ 1 $ 到 $ n $ 作为编号。每架天线有一个额定发射功率，编号为 $ i $ 的天线发射功率为 $ p_i $。    

当且仅当满足 $ |i-j| \leq \min(p_i, p_j) $ ，编号为 $ i $ 和 $ j $ 的天线可以直接传递信息。两架天线传递一条信息需要 $ 1 $ 秒种。  

现在需要从 $ a $ 天线向 $ b $ 天线发射一条信息，可以用其他天线作为中继，请问最短需要多长时间发送出这条信息？

## 说明/提示

在第一组数据中，我们要从 $ 2 $ 号天线到 $ 9 $ 号天线发射一条信息，可以证明最短耗时是 $ 4 $ 分钟：  

- 由  $ 2 $  号发射到 $ 1 $ 号 花费 $ 1 $ 秒。 $ |2-1|\le \min(1, 4) = \min(p_2, p_1) $.  
- 由  $ 1 $  号发射到 $ 5 $ 号 花费 $ 1 $ 秒。 $ |1-5|\le \min(4, 5) = \min(p_1, p_5) $.  
- 由  $ 5 $  号发射到 $ 10 $ 号 花费 $ 1 $ 秒。 $ |5-10|\le \min(5, 5) = \min(p_5, p_{10}) $.  
- 由 $ 10 $ 号发射到 $ 9 $ 号 花费 $ 1 $ 秒。$ |10-9|\le \min(5, 1) = \min(p_{10}, p_9) $ .

## 样例 #1

### 输入

```
3
10 2 9
4 1 1 1 5 1 1 1 1 5
1 1 1
1
3 1 3
3 3 1```

### 输出

```
4
0
2```

# 题解

## 作者：EuphoricStar (赞：6)

## 思路

边权为 $1$ 的最短路问题，可使用 BFS 求解。当目前搜到点 $u$ 时，瓶颈在于找出所有边 $u \to v$，若 $v$ 没被访问过就入队。

下面的部分和 [[JOISC2020] 治療計画](https://www.luogu.com.cn/problem/P7214) 有点像。考虑先拆限制中的绝对值。

- 若 $u < v$ ，则 $v - u \le p_u$ 且 $v - u \le p_v$。此时就是在 $[u+1,u+p_u]$ 中找出所有满足 $v - p_v \le u$ 的 $v$ 并入队。线段树上维护 $i \in [1,n]$，$i - p_i$ 的最小值，找点就直接在线段树上二分，如果当前区间的 $\min > u$ 说明区间内不可能有符合条件的点了，立即退出。

- 若 $u > v$ ，则 $u - v \le p_u$ 且 $u - v \le p_v$。此时就是在 $[u-p_u,u-1]$ 中找出所有满足 $v - p_v \ge u$ 的 $v$ 并入队。线段树上维护 $i \in [1,n]$，$i + p_i$ 的最大值，找点也直接在线段树上二分，如果当前区间的 $\max < u$ 说明区间内不可能有符合条件的点了，立即退出。

- 当一个点入队时，将 $v + p_v$ 设为 $-\infty$，$v - p_v$ 设为 $\infty$。

由于每个点只会入队一次，所以时间复杂度有保证，为 $O(n \log n)$。

## 代码

[code](https://codeforces.com/contest/1662/submission/164084528)

---

## 作者：Richard_Whr (赞：3)

# CF1662F Antennas题解

首先，最短路线，要么是 dp，要么是最短路。（在没有环的情况下好像差不多）

不过观察到这里的边权全为 $1$，因此果断考虑 bfs。

观察两个点之间存在边的条件：

- $| i - j | \le min ( p_i , p_j ) $

遇到绝对值有两种思路：
- 拆绝对值转真实值限制；

- 分类讨论；

这里拆为真实值限制没有太好的效果，因为右侧还是个 $min$ 函数，还需要拆，不能用偏序直接做。

所以考虑 **分类讨论** 

- 当 $i < j$ 时：

	- $j-i \ge p_i$
   - $j-i \ge p_j$
   
  将三个条件整理并合并得：
  
	- $i < j \le i+p_i$
   - $j - p_j \le i$
  
 - 当 $i > j$ 时：同理可以推出相应结论，这里留给读者自行推导。
 
	给出结论：
   
   - $i-p_i \le j < i$
   - $j+p_j \ge i$
 
观察这样的限制，可以发现是**区间内寻找符合条件的所有位置**，想到了线段树等数据结构。
  
不过这样的话会有问题，**每次都会走到叶子节点**，这样对于线段树来说**没法整体处理就失去了他的意义**。
  
我们想到一个问题，就是一个点**加入队列后，就再也不会入队了**，因此这个点以后**永远不应该被查到**。
  
也就是说，即使这个点满足限制，但是他之前**已经被查到了**，我们也就**无需**再找到他了。

因此，我们考虑给每个线段树节点**标记** $tag$，如果说这个节点所包含的区间没有我们需要的了，那我们就**拒绝继续分裂他**。

这个 $tag$ 是啥呢，再次观察限制条件。如果说一个节点中 **所有** $j - p_j$ 的最小值，**都**比 $i$ 要大， 那么实际上是不需要继续访问的。

那么怎么将刚刚所阐述的只会被查到一次的这个条件加入呢？

其实也是比较简单的，我们将他的 $i-p_j$ 设为 $+∞$，将他的 $i+p_j$ 设为 $-∞$，这个点就永远不会被查到了！

所以对于每个节点，$tag$ 就是节点所包含的所有 $i-p_i$ 的**最小值**和 $i+p_i$ 的**最大值**。

## 总结做法：

bfs 求最短路，转移的时候查询两个区间。（见上述两种限制）

查询的时候，如果 $tag$ 已经不符合要求了，直接 pass；如果有符合要求的，暴力递归到叶子节点，将其加入队列并修改其 $tag$，不要忘了 pushup。

最后，多测记得清空。

**放上我丑陋的 Code:**

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int,int> PII;
const int N=2e5+10,inf=1e9;
PII a[N];
struct node
{
	int l,r;
	int minv,maxv;
}tr[N*4];
int d[N];
int n,S,T;
int q[N];
bool st[N];
int hh,tt;

void init()
{
	hh=0,tt=-1;
}

void pushup(node &root,node &left,node &right)
{
	root.minv=min(left.minv,right.minv);
	root.maxv=max(left.maxv,right.maxv);
}

void pushup(int u)
{
	pushup(tr[u],tr[u*2],tr[u*2+1]);
}

void build(int u,int l,int r)
{
	if(l==r) 
	{
		tr[u]={l,r,a[l].x,a[l].y};
		if(l==S) tr[u].minv=inf,tr[u].maxv=-inf;
	}
	else
	{
		tr[u].l=l,tr[u].r=r;
		int mid=l+r>>1;
		build(u*2,l,mid),build(u*2+1,mid+1,r);
		pushup(u);
	}
}

void querymin(int u,int l,int r,int s,int dist)
{
	if(tr[u].minv>s) return;
	
	if(tr[u].l==tr[u].r)
	{
		q[++tt]=tr[u].l;
		d[tr[u].l]=dist+1;
		tr[u].minv=inf,tr[u].maxv=-inf;
	}
	else
	{
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) querymin(u*2,l,r,s,dist);
		if(r>mid) querymin(u*2+1,l,r,s,dist);
		pushup(u);  
	}
	
	
}

void querymax(int u,int l,int r,int s,int dist)
{
	if(tr[u].maxv<s) return;
	
	if(tr[u].l==tr[u].r) 
	{
		q[++tt]=tr[u].l;
		d[tr[u].l]=dist+1;
		tr[u].maxv=-inf,tr[u].minv=inf;
	}
	else
	{
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) querymax(u*2,l,r,s,dist);
		if(r>mid) querymax(u*2+1,l,r,s,dist);
		pushup(u);
	}
}

void bfs()
{
	memset(d,0x3f,sizeof d);
	d[S]=0,q[++tt]=S;
	
	while(hh<=tt)
	{
		int t=q[hh++];
		//printf("%d: %d\n",t,d[t]);
		//printf("minq:%d %d %d\n",t+1,a[t].y,t);
		//printf("maxq:%d %d %d\n",a[t].x,t-1,t);
		if(t==T) break;
		if(t+1<=n) querymin(1,t+1,min(a[t].y,n),t,d[t]);
		if(t-1>=1) querymax(1,max(a[t].x,1),t-1,t,d[t]);
	}
	
	printf("%d\n",d[T]);
}
int cases;
int main()
{
	scanf("%d",&cases);
	while(cases--)
	{
		init();
		scanf("%d%d%d",&n,&S,&T);
		for(int i=1;i<=n;i++)
		{
			int p;
			scanf("%d",&p);
			a[i]={i-p,i+p};
		}
		
		build(1,1,n);
		
		bfs();
	}
	return 0;	
}
```


---

