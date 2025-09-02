# Theft of Blueprints

## 题目描述

Insurgents accidentally got hold of the plan of a top secret research polygon created on a distant planet for the needs of the Galaxy Empire. The insurgents suppose that this polygon is developing new deadly weapon. The polygon consists of $ n $ missile silos connected by bidirectional underground passages. The passages are linked to laboratories where research is conducted. Naturally, the passages are guarded severely: the passage between silos $ i $ and $ j $ is patrolled by $ c_{i,j} $ war droids.

The insurgents studied the polygon plan and noticed its unusual structure. As it turned out, for any $ k $ -element set of silos $ S $ there is exactly one silo that is directly connected by a passage with each silo from $ S $ (we'll call this silo adjacent with $ S $ ). Having considered that, the insurgents decided to act as follows:

1. they choose a $ k $ -element set of silos $ S $ ;
2. a group of scouts lands from the air into each silo from $ S $ ;
3. each group moves along the corresponding passage to the silo, adjacent with $ S $ (as the scouts move, they check out the laboratories and watch for any signs of weapon blueprints);
4. in the silo, adjacent with $ S $ , the groups get on the ship and fly away.

The danger of the operation is the total number of droids that patrol the passages through which the scouts will go. The danger of the operation obviously only depends on the way to choose set $ S $ . The insurgents haven't yet decided on the exact silos to send the scouts to. However, they already want to start preparing the weapons for the scout groups. To do that, the insurgents need to know the mathematical average of the dangers of the operations that correspond to all possible ways to choose set $ S $ . Solve this problem to help the insurgents protect the ideals of the Republic!

## 说明/提示

In the first sample there are 6 one-element sets of silos. For sets $ {1} $ , $ {5} $ the operation danger will equal 8, for sets $ {3} $ , $ {6} $ — 3, for sets $ {2} $ , $ {4} $ — 5. The mathematical average equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF332D/6779180059bebd2b65884098cbd93497c7078b58.png).

In the second sample there are 3 two-elements sets of silos: $ {1,3} $ (danger equals 21), $ {1,2} $ (danger equals 11), $ {2,3} $ (danger equals 10). The average operation danger equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF332D/e461096176a32afa0b41586e7192e319cef72429.png).

## 样例 #1

### 输入

```
6 1
-1 -1 -1 8 -1
-1 5 -1 -1
-1 -1 3
-1 -1
-1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 2
10 0
11
```

### 输出

```
14
```

# 题解

## 作者：whiteqwq (赞：2)

[CF332D Theft of Blueprints](https://www.luogu.com.cn/problem/CF332D)解题报告

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1772966)

## 题意
- 给定一个$n$个点带边权的无向图，且满足对于任意大小为$k$的点集$S$都满足**有且仅有**一个点$p\notin S$（下文称之为**中间点**）与$S$中所有点存在一条边。
- 定义一个点集的权值为这个点集对应的点$p$与这个点集所有点的边权值之和。
- 求任意一个大小为$k$的点集的权值期望，答案向下取整。
- 数据范围$2\leqslant n\leqslant 2000,1\leqslant k\leqslant n-1$。

## 分析

比较好玩的一道题。

### $k=1$的情况

$k=1$时，只存在$n$个只包含一个单点的点集，我们直接枚举每个点，然后直接计算每个点连接的边的边权和，最后除以$n$就好了，时间复杂度：$O(n)$。

### $k=2$的情况

我们枚举每一个中间点$p$，并枚举这个中间点的每一条边$(p,x)$，那么不难发现这条边造成贡献当且仅当另一个点$y$与$x$成为点集，且$y$与$p$有一条边。设$p$的度数为$cnt$，这条边权值为$v$，则这条边造成的贡献为$(cnt-1)\times v$。

时间复杂度：$O(n^2)$。

### $k\geqslant 3$的情况

引理1：当$k\geqslant 3$时且满足上述条件时，原图任意两个结点都恰好有$k-1$个公共相邻结点。

证明：

设原图内两点公共相邻结点数量为$v$，那么有：

如果$v\geqslant k$，那么这两个结点的公共相邻结点可以形成一个大小为$k$的集合，且两个点都是中间点，不符合题意，故$v<k$。

如果$v<k-1$，那么这两个点与它们公共相邻顶点构成的点集$T$大小小于等于$k$，取任意一个大小为$k$的集合，满足$T$为该集合的子集，则可以得到一个新的点$d\notin T$，且$d$与这两个点均存在一条边，也就是说两个点存在了一个新的公共相邻结点，故$v\geqslant k-1$。

因此$v=k-1$，结论成立。

引理2：当$k\geqslant 3$时且满足上述条件时，原图包含一个$k+1$个点的完全图。

证明：我们取任意相连的两点$a_1,a_2$，不难找到一个包含$a_1,a_2$的集合，它的中间点为$a_3$，那么$a_1$与$a_3$，$a_2$与$a_3$均存在一条边，同理寻找一个包含$a_{1\cdots3}$的集合中间点为$a_4$，一直寻找到$a_{k+1}$，不难发现这$k+1$个点构成了一个$k+1$个点的完全图。

引理3：当$k\geqslant 3$且满足上述条件时，仅$k+1$个点的完全图满足条件。

证明：根据引理$2$可得原图包含一个$k+1$个点的完全图$a_{1\cdots k+1}$。根据引理$1$又可得完全图中两点的公共顶点恰好为完全图内的其他点。

设原图存在一个不在完全图中的点$w$，取一个包含完全图两点$a_1,a_2(a_1\ne a_2)$与$w$的点集，得到它的中间点为$x$，且$x$在完全图中。那么再取一个包含$a_1,x,w$的点集，可得另一个中间点为$y$，且$y$在完全图中，那么$x$与$y$存在公共顶点$w$，而因为完全图总两点的公共顶点为完全图内的其他点，因此$w$在完全图内，故不存在完全图外的点，即原图为一个$k+1$个点的完全图。

知道了该图为$k+1$个点的完全图，这道题就简单了。

我们考虑仅存在$n$个不同的子集，那么很显然对于每一个子集，该子集外的点便为这个子集的中间点，也就是说每个点都会作为中间点计算一次，我们直接算所有点连接的所有边边权之和除以$n$就好了。

时间复杂度：$O(n^2)$。


## 代码
```
#include<stdio.h>
#include<vector>
#define int long long
using namespace std;
const int maxn=2005;
int n,k,ans;
vector< pair<int,int> >v[maxn];
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			int x;
			scanf("%lld",&x);
			if(x==-1)
				continue;
			v[i].push_back(make_pair(j,x));
			v[j].push_back(make_pair(i,x));
		}
	if(k==1){
		for(int i=1;i<=n;i++)
			ans+=v[i][0].second;
		printf("%lld\n",ans/n);
		return 0;
	}
	if(k==2){
		for(int i=1;i<=n;i++){
			int cnt=0,sum=0;
			for(int j=0;j<v[i].size();j++)
				cnt++,sum+=v[i][j].second;
			ans+=(cnt-1)*sum;
		}
		printf("%lld\n",ans/(n*(n-1)/2));
		return 0;
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<v[i].size();j++)
			ans+=v[i][j].second;
	printf("%lld\n",ans/n);
	return 0;
}
```


---

