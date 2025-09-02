# Olya and Graph

## 题目描述

Olya has got a directed non-weighted graph, consisting of $ n $ vertexes and $ m $ edges. We will consider that the graph vertexes are indexed from 1 to $ n $ in some manner. Then for any graph edge that goes from vertex $ v $ to vertex $ u $ the following inequation holds: $ v&lt;u $ .

Now Olya wonders, how many ways there are to add an arbitrary (possibly zero) number of edges to the graph so as the following conditions were met:

1. You can reach vertexes number $ i+1,i+2,...,n $ from any vertex number $ i $ $ (i&lt;n) $ .
2. For any graph edge going from vertex $ v $ to vertex $ u $ the following inequation fulfills: $ v&lt;u $ .
3. There is at most one edge between any two vertexes.
4. The shortest distance between the pair of vertexes $ i,j $ $ (i&lt;j) $ , for which $ j-i<=k $ holds, equals $ j-i $ edges.
5. The shortest distance between the pair of vertexes $ i,j $ $ (i&lt;j) $ , for which $ j-i&gt;k $ holds, equals either $ j-i $ or $ j-i-k $ edges.

We will consider two ways distinct, if there is the pair of vertexes $ i,j $ $ (i&lt;j) $ , such that first resulting graph has an edge from $ i $ to $ j $ and the second one doesn't have it.

Help Olya. As the required number of ways can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample there are two ways: the first way is not to add anything, the second way is to add a single edge from vertex $ 2 $ to vertex $ 5 $ .

## 样例 #1

### 输入

```
7 8 2
1 2
2 3
3 4
3 6
4 5
4 7
5 6
6 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 0 2
```

### 输出

```
12
```

## 样例 #3

### 输入

```
7 2 1
1 3
3 5
```

### 输出

```
0
```

# 题解

## 作者：RainFestival (赞：0)

题意不再重复

codeforces 评分 $2200$

本文用 $(x,y)$ 表示 $x$ 向 $y$ 的一条**有向边** , $d(x,y)$ 表示 $x$ 到 $y$ 的距离

首先，显然，我们**必须**添加 $\forall x\in[1,n-1],(x,x+1)$

然后，我们考虑满足第二个条件

我们**可以**添加一些附加边 $(x,x')$ ，满足 $x+k+1=x'$

这样可以使得 $d(a,b),a\le x,b\ge x'$ 缩小到 $d(a,b)-k$

但是要注意一点

对于 $\forall (x,x'),(y,y')$ **必须**满足 $x'>y,y'>x$ ,即 $[x,x']\cap[y,y']\neq\varnothing$

如果不这样,从 $a$ 到 $b$ , $a\le \min(x,y),b\ge\max(x',y')$ 将经过 $\ge 2$ 条附加边， $d(a,b)$ 减少超过 $k$ ,我们称这种情况为冲突

现在我们考虑如何计数

记 $p,q$ 分别为预先加的附加边中起始点编号最小，最大的

我们枚举 $i$ ,其中 $i$ 为我们新加入的边中起始点编号最小的，当然预先加的附加边中没有 $(i,i')$

我们要先判断 $(i,i')$ 是否满足条件，容易知道只需与 $(p,p'),(q,q')$ 判断是否冲突

加入 $(i,i')$ 后，新的 $p,q$ 变成 $p_1,q_1$

记 $u$ 为能加入的起始点编号最大的边

当 $p_1+k>n$ 时 $u=n-(k+1)$ ,因为终到不能超过 $n$

当 $p_1+k\le n$ 时 $u=p+k$

我们可以通过简单地计数发现有 $2^{(u-i+1)-x-1}$ 种加边方案,

其中 $x$ 为起始点编号在 $[i,u]$ 中的已加好的边，因为这些边不能选择，必须存在，$-1$ 因为 $(i,i')$ 必须加入

对于起始状态没有附加边的图，进行特殊判断特殊处理，类似于上面的分类方法

当有一条预先加的边 $(x,y)$ 不满足 $y=x+1$ 或者 $y=x+k+1$ 时无解，此时应该输出 $0$

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#define mod 1000000007
int n,m,k,flag,ans,cnt,p,q,w[1000005],f[1000005],g[1000005],s[1000005];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	w[0]=1;for (int i=1;i<=n;i++) w[i]=w[i-1]*2%mod;
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (x>y) std::swap(x,y);
		if (x+1==y) f[x]=1;
		else if (x+k+1==y) g[x]=1,++cnt;
		else flag=1;
	}
	if (flag)
	{
		puts("0");
		return 0;
	}
   if (cnt==0)
	{
		for (int i=1;i<=n;i++)
	   {
		   if (i+k+1>n) continue;
			int up=(i+k+k+1>n?n-k-1:i+k);
			int can=up-i+1;
		   ans=(ans+w[can-1])%mod;
	   }
	   ++ans;
	   printf("%d\n",ans);
	   return 0;
	}
	for (int i=1;i<=n;i++) if (g[i]) q=i;
	for (int i=n;i>=1;i--) if (g[i]) p=i;
	if (p+k+1<=q)
	{
		puts("0");
		return 0;
	}
	for (int i=1;i<=n;i++) s[i]=s[i-1]+g[i];
	for (int i=1;i<=n;i++)
	{
		if (g[i]||i+k+1>n) continue;
		if (i>=p+k+1||i+k+1<=q) continue;
		int cp=p,cq=q;
		if (i<p) p=i;if (i>q) q=i;
		int up=(p+k+k+1>n?n-k-1:p+k);
		int can=up-i+1-(s[up]-s[i-1]);
		ans=(ans+w[can-1])%mod;
		q=cq,p=cp;
	}
	++ans;
	printf("%d\n",ans);
}
```
实测 $57$ 个测试点 $3.05s,18.82MB$

最大测试点 $122ms$

谢谢观看

---

