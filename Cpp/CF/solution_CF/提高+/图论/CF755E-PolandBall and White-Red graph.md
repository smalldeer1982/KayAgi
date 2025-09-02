# PolandBall and White-Red graph

## 题目描述

PolandBall has an undirected simple graph consisting of $ n $ vertices. Unfortunately, it has no edges. The graph is very sad because of that. PolandBall wanted to make it happier, adding some red edges. Then, he will add white edges in every remaining place. Therefore, the final graph will be a clique in two colors: white and red.

Colorfulness of the graph is a value $ min(d_{r},d_{w}) $ , where $ d_{r} $ is the diameter of the red subgraph and $ d_{w} $ is the diameter of white subgraph. The diameter of a graph is a largest value $ d $ such that shortest path between some pair of vertices in it is equal to $ d $ . If the graph is not connected, we consider its diameter to be -1.

PolandBall wants the final graph to be as neat as possible. He wants the final colorfulness to be equal to $ k $ . Can you help him and find any graph which satisfies PolandBall's requests?

## 说明/提示

In the first sample case, no graph can fulfill PolandBall's requirements.

In the second sample case, red graph is a path from $ 1 $ to $ 5 $ . Its diameter is $ 4 $ . However, white graph has diameter $ 2 $ , because it consists of edges 1-3, 1-4, 1-5, 2-4, 2-5, 3-5.

## 样例 #1

### 输入

```
4 1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
5 2
```

### 输出

```
4
1 2
2 3
3 4
4 5
```

# 题解

## 作者：xkcdjerry (赞：2)

这种绝(ren)世(lei)好(zhi)题(hui)为什么洛谷没题解，CodeForces 的还只摆结论不证明，差评。这里我给出一个比 CodeForces 官方题解更加详细而且带证明的题解 ~~也是本题洛谷的第一篇题解~~：

以下推导中的 $G$ 与 $G'$ 均为连通图且 $G'$ 为 $G$ 的反图。

先放一个结论：$k>3$ 无解，即不存在一个图 $G$ 使得 $\min(d_G,d_{G'})>3$。

证明：  
定义 $d(x,y)$ 为图 $G$ 中 $x$ 和 $y$ 间最短路径包含的边数，$d'(x,y)$ 为 $G'$ 中 $x$ 和 $y$ 间最短路径包含的边数。  
不妨假设有图 $G$ 存在点 $u,v$ 使得 $d(u,v) \geqslant 4$，则命题等效于对于任何点对 $x,y$ 均有 $d'(x,y) \leqslant 2$。  

由于 $d(u,v) \geqslant 4$，所以 $u,v,x,y$ 一定不在同一个只由 $u,v,x,y$ 和其间的边构成的连通块（下称“限制连通块”）中，否则 $d(u,v) \leqslant 3$。  

令所有最大限制连通块中包含 $u$ 的连通块的为 $S_u$，包含 $y$ 的连通块为 $S_v$（由上可得 $S_u \neq S_v$）则：  

* 若存在 $S\in\{S_u,S_v\}$ 使得 $x \in S$ 且 $y \in S$（不妨令 $S=S_u$），则有：$(x,v) \notin G$，$(y,v) \notin G$。  
  那么有 $(x,v) \in G'$，$(y,v) \in  G'$，即 $d'(x,y) \leqslant d'(x,v)+d'(y,v)=2$
* 否则，$x,y$ 不在一个限制连通块中，由限制连通块的定义可得 $(x,y) \notin G$，即 $(x,y) \in G'$，所以 $d'(x,y)=1$

综上，若存在图 $G$ 和点对 $u,v$ 使得 $d(u,v) \geqslant 4$，则不存在一对点 $x,y$ 使得 $d'(x,y) > 2$。即 $\min(d_G,d_{G'}) \leqslant 3$。

---
引理：若有点 $u,v,x,y$ 使得 $d(u,v)=d'(x,y)=3$，则 $d_G=d_{G'}=3$。  

证明：  
因为 $d(u,v)=d'(x,y)=3$，所以 $d_G,d_{G'} \geqslant 3$。  
若 $d_G \geqslant 4$，则 $d_{G'} \leqslant 2$，矛盾，故 $d_G<4$，同理可得 $d_{G'}<4$。  
因此 $d_G=d_{G'}=3$。

---

所以只需要分析 $k=1,k=2,k=3$ 的情况：  

* $k=1$：随便画画就能发现显然无解
  
* $k=2$：$n \leqslant 3$ 时显然无解，否则构造 $G=\{(1,2),(2,3),...,(n-1,n)\}$，显然 $d_G=n-1$，且 $d'(1,2)=2$，$d'(x,y) \geqslant d'(x,z)+d'(z,y)=2 (x \neq z,y \neq z)$，即 $d_{G'}=2$。

* $k=3$：
$n \leqslant 3$ 时无解，否则：

构造 $G_n$ 为有 $n$ 个点且 $\min(d_G,d_{G'})=3$ 的图，$G_4=\{(1,2),(2,3),(3,4)\}$，$G_5=\{(1,2),(2,3),(3,4),(1,5),(3,5)\}$。  
显然对于两张图均有 $d(1,4)=d'(2,3)=3$，由引理可得 $d_G=d_{G'}=3$。  

令 $G_n=G_{n-1} \cup \{(1,n),(3,n),(5,n),(n-1,n)\} (n \geqslant 6)$：

定义“$n$ 不影响 $x$”表示 $G_n$ 中的 $x$ 与 $G_{n-1}$ 中的 $x$ 相同，则：  
若 $d(u,n)+d(n,v) \geqslant d(u,v)$，那么 $n$ 不影响 $d(u,v)$。  

由于 $n-1$ 不影响 $d(1,4)$，所以 $d(1,n-1)+d(n-1,4) \geqslant 3$，即 $d(n-1,4) \geqslant 2$。  
由于 $d(1,n)=1$，$d(n,4)=1+\min\{d(3,4),d(5,4),d(n-1,4)\}=2$，$d(1,n)+d(n,4)=3$，即 $n$ 不影响 $d(1,4)$。

同理，$d'(2,n-1)+d'(n-1,3)=1+d'(n-1,3) \geqslant 3$，即 $d'(n-1,3) \geqslant 2$，由此有 $d'(x,3) \geqslant 2 (5 \leqslant x < n)$，$d'(n,3) = 1+\min\{d'(2,3),d'(4,3),d'(x,3)\}(5 \leqslant x < n) = 2$，即 $d'(2,n)+d'(n,3)=3$，即 $n$ 不影响 $d'(2,3)$。

由上可知，若 $n-1$ 不影响 $d(1,4)$ 与 $d'(2,3)$，$n$ 就也不影响 $d(1,4)$ 与 $d'(2,3)$。又因为 $5$ 显然不影响，所以任意 $n \geqslant 6$ 也不影响 $d(1,4)$ 与 $d'(2,3)$。

综上，在图 $G_n$ 中，$d(1,4)=d'(2,3)=3$，由引理可得 $d_G=d_{G'}=3$。

---

至此，我们证明了 $k=1$ 与 $k>3$ 的不可行性，并为 $k=2$ 和 $k=3$ 给出了构造方案与证明。

代码：
```c++
#include <cstdio>
struct edge{int u,v;}a[1000010];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	if(k>3||k==1||n<k+1) return puts("-1"),0;
	if(k==2)
	{
		if(n<=4) return puts("-1"),0;
		printf("%d\n",n-1);
		for(int i=1;i<n;i++) printf("%d %d\n",i,i+1);
	}
	else if(k==3)
	{
		int top=0;
		a[top++]={1,2},a[top++]={2,3},a[top++]={3,4};
		for(int i=5;i<=n;i++)
		{
			a[top++]={1,i},a[top++]={3,i};
			if(i>5) a[top++]={5,i};
			if(i>6) a[top++]={i-1,i};
		}
		printf("%d\n",top);
		for(int i=0;i<top;i++) printf("%d %d\n",a[i].u,a[i].v);
	}
}
```

---

## 作者：良心WA题人 (赞：2)

若 $k\ge 4$ 则在某个图中存在一个大于等于 $4$ 的链使得链上任意两点没边，显然链上不会有两点在另一个图距离超过 $2$。在链外面一点到链上最多与某相邻或距离为 $2$ 的两个点有连线，则该点到链上任意一点的距离不会超过 $2$。两个不在链上的点一定可以通过链上某个二者都没连边的点中转，也不超过 $2$。所以 $k\ge 4$ 无解。

注意到 $k=1$ 和 $n\le 3$ 无解。

$k=2$ 直接构造一条链（此时 $n=4$ 无解，此情况包含于上述证明，所以得证。）

$k=3$ 构造一个菊花图缺一个点，将缺的那个点放到菊花图某个叶子上面。此时当前图显然距离为 $3$，另一个图从中心点到那个叶子的距离为 $3$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	if(k==1||k>=4||n<=3)
	{
		puts("-1");
		return 0;
	}
	if(k==2)
	{
		if(n==4)
		{
			puts("-1");
			return 0;
		}
		printf("%d\n",n-1);
		for(int i=1;i<n;i++)
			printf("%d %d\n",i,i+1);
	}
	else
	{
		printf("%d\n2 %d\n",n-1,n);
		for(int i=3;i<=n;i++)
			printf("1 %d\n",i);
	}
	return 0;
}
```

---

