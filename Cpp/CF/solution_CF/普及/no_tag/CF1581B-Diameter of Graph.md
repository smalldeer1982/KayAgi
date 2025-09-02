# Diameter of Graph

## 题目描述

CQXYM wants to create a connected undirected graph with $ n $ nodes and $ m $ edges, and the diameter of the graph must be strictly less than $ k-1 $ . Also, CQXYM doesn't want a graph that contains self-loops or multiple edges (i.e. each edge connects two different vertices and between each pair of vertices there is at most one edge).

The diameter of a graph is the maximum distance between any two nodes.

The distance between two nodes is the minimum number of the edges on the path which endpoints are the two nodes.

CQXYM wonders whether it is possible to create such a graph.

## 说明/提示

In the first test case, the graph's diameter equal to 0.

In the second test case, the graph's diameter can only be 2.

In the third test case, the graph's diameter can only be 1.

## 样例 #1

### 输入

```
5
1 0 3
4 5 3
4 6 3
5 4 1
2 1 1```

### 输出

```
YES
NO
YES
NO
NO```

# 题解

## 作者：Gokix (赞：9)

[CF1581B](https://www.luogu.com.cn/problem/CF1581B)

本来是巧妙构造题，但被出题人整的心态不好了。

------------

由于我们的构造出来的图得保证连通，所以容易得出一个思路：先构造一棵树，然后往上加边。

构造一棵什么样的树好呢？显然为了满足直径尽可能小，我们构造的树得“密集”一点，于是想到**菊花图**。

然后就会有一条美妙的性质：在菊花图上加边也不会使直径长度大于 $2$。菊花图直径长度就是 $2$，再加边肯定不会变大啊。

所以对于 $k-2 \ge 2$ 的情况直接判定为有解，现在就剩下 $k-2 \ge 1$ 的情况（若 $k-2=0$ 除了一个点必然无解）。

想想直径为 $1$ 说明了什么？图必须是个完全图，否则没有直接连边的两点之间最短路就会大于 $1$。

------------

看上去这题结束了？

不！出题人他要整你心态，让你 FST！

诶，他数据里就有连边都连不通的情况，还有连满了还剩下边的情况，还有 $k-2 < 0$ 的情况。以上统统无解。

还有 $n=1$ 的，它必须满足 $k-2 \ge 0$ 才有解，否则无解（注意这是唯一一种 $k=0$ 还有解的情况）。

咱也想不明白出题人干这些事为了啥。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath> 
#include<algorithm>
using namespace std;
inline long long read(){char ch=getchar();long long x=0,f=1;while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}while('0'<=ch && ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(long long x){if(x<0){putchar('-');x=-x;}if(x>9) write(x/10);putchar(x%10+'0');}

long long t,n,m,k;

int main(){
	long long i,j,u,v;
	t=read();
	while(t--){
		n=read();m=read();k=read();
		k-=2;
		if(m>n*(n-1)/2 || m<n-1 || k<0){
			cout<<"NO"<<endl;
			continue;
		}
		if(k==0){
			if(n==1){
				cout<<"YES"<<endl;
			}
			else{
				cout<<"NO"<<endl;
			}
		}
		if(k>=2){
			cout<<"YES"<<endl;
			continue;
		}
		else if(k==1){
			if(m==n*(n-1)/2){
				cout<<"YES"<<endl;
				continue;
			}
			else{
				cout<<"NO"<<endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：5)

## 题意简述

CQXYM 想让你构造一个 $n$ 个点，$m$ 条边的**连通图**，并且图中任意两点之间的距离小于 $k - 1$。两个点之间的距离是指两个点之间任意一条路径中**经过最少的边数的路径的边的数量**（有点绕）。

## 解题思路

- 既然要求两点之间距离小于选 $k - 1$，那么我们考虑贪心。经过尝试我们发现这样建图使得任何时候两点之间距离都是小于等于2的：

	1. 选取一个中心点 $x$，并且从 $x$ 向除了 $x$ 以外的点连一条边。这样此时任意两点间距离最大就是经过 $x$ 的时候，为2。
    2. 这时候我们发现整个图形如同一个 $n-1$ 边形，每个顶点连向中心。我们进一步连边，连上这个多边形的每一条边和每一条对角线。由于之前的最小值已经是2，此举不会影响最小值。
    3. 我们发现，完全图任意两点之间距离为1。
    
有点绕，~~良心~~放个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/c8a354aj.png)

以上为 $n = 7$ 的情况。1 号为选取的中心点，蓝色为第一次操作连的边，；绿色为第二次操作连的边。**由于对角线太乱了，会影响图原本的效果，所以没画，~~敬请您自行脑补~~。**

按照这样的策略，我们就可以在任意时刻两点之间距离小于 3 的情况下完成建图。

## 代码实现

显然是分类讨论啦。

1. $k < 2$：$k - 1 < 0$ 所以肯定不行，输出 ```No```。

2. $k = 2$：当 $n = 1$ 的时候，任意两点之间距离为 $0$，**符合题意（别落下！）。** 其他情况不符合题意。

3. $k = 3$：当这是一个完全图的时候符合题意。无需特判 1 的情况，因为它已经包含在内。

4. $k > 3$：一定可行，输出 ```Yes```。

最后注意一下能不能建成一个符合题意的图（也就是能不能联通，是不是必须有重边等。因为我看数据里有坑）：```if(m<n-1 || m>n*(n-1)/2) puts("No");```

然后这道题就解决了。（比赛的时候我不知道为啥没想到这个简单的分支结构，我太菜了）

### 代码

~~（敲黑板）快来看！代码大放送！~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long T,n,m,k;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&n,&m,&k);
		if(k<2 || m<n-1 || m>n*(n-1)/2){puts("nO");continue;}
		if(k==2)
		{
			if(n==1) puts("Yes");
			else puts("No");
			continue;
		}
		if(k==3)
		{
			if(m==n*(n-1)/2) puts("Yes");
			else puts("No");
			continue;
		}
		else puts("yEs");
	}
	return 0;
}
```

完结撒花！~~~

---

## 作者：ZolaWatle (赞：1)

### 题目大意

定义一张无向，边权为 $1$ 的连通图的**直径**为其中某两点间最短距离的最大值。

共 $T$ 组询问，每次给定三个数 $n,m,k$，问是否有一种构造图的方法，使得构造出的一张 $n$ 个点 $m$ 条边的无向连通图没有重边、自环，且这张图的直径**严格小于** $k-1$。

$1\leq T\leq 10^5, 1\leq n\leq 10^9, 0\leq m,k\leq 10^9$。

### 解题思路

我们知道，将 $n$ 个点全部连通，连成一棵树的情况是使用边最少的，需要 $n-1$ 条边。另外，一张 $n$ 个点的完全图的边数为 $\text{maxE}=\dfrac{n*(n-1)}{2}$，如果一张图的边数 $m>\text{maxE}$，则多余出来的边要么是自环，要么是重边。于是，我们知道，当 $m<n-1$ 或 $m>\dfrac{n*(n-1)}{2}$ 时，不符合题目要求。

接下来考虑一种生成图的方式使得直径尽可能小。我们考虑先用掉 $n-1$ 条边，建立一棵高度为 $2$ 的树。

![](https://cdn.luogu.com.cn/upload/image_hosting/8j4kiboe.png)

容易看出，这样一来，我们保证了这张图的直径**不超过** $2$ 。

考虑用掉剩下的边，我们将深度为 $2$ 的所有点间相互连边，可以保证某些点之间的最短距离为 $1$，但全局而言，依然存在一些点之间的距离为 $2$，直径不变。

我们发现，要使得这张无向连通图的直径为 $1$，有且仅有一种情况，即为它是**完全图**时。因为此时任意两点之间都通过一条边**直接相连**。

于是，我们分情况讨论：

- 当 $n\leq m<\text{maxE}$ 时：
  - 若 $k\geq 4$，存在合法方案。
  - 若 $k<4$，不存在合法方案。

- 当 $m=\text{maxE}$ 时：
  - 若 $k\geq 3$，存在合法方案。
  - 若 $k<3$，不存在合法方案。

此外，我们还需要特判孤点，即 $n=1$ 时的情况。显然，只需要 $m=0$ 且 $k\neq 0$，即存在合法方案。

考虑对于每一组 $n,m,k$ 分类讨论解决。时间复杂度 $\text{O}(T)$。

------------

感谢阅读！

---

## 作者：Eason_AC (赞：0)

## Content
$\textsf{C}\color{Red}\textsf{QXYM}$ 想要构造一个包含 $n$ 个点和 $m$ 条边的无向连通图，并且他希望这个图满足下列条件：

- 该图中不存在重边和自环。也就是说，一条边应该连接两个不同的顶点，且两个点之间最多只能连一条边。
- 该图的直径严格小于 $k-1$。

定义：

- 一个图中两个节点之间的距离是以这两个点为端点的路径经过的最小边数。
- 一个图的直径是任意两点之间距离的最大值。


$\textsf{C}\color{Red}\textsf{QXYM}$ 想知道他能不能够造出这样一个图。由于他还忙于其他事情，于是就把这个任务交给了你。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 10^5$，$1\leqslant n\leqslant 10^9$，$0\leqslant m,k\leqslant 10^9$。**
## Solution
非常牛的一道分类讨论题。

首先，任何一个图的直径最少是 $0$（当且仅当 $n=1$ 时成立），因此有 $k-1>0\Rightarrow k>1$。因此只要 $k\leqslant 1$，就一定不能构造出满足题目要求的图，排除掉这一类。

排除掉这一类，我们再来看 $n=1$ 时的情况，此时，由于图不存在重边和自环，因此必须要满足 $m=0$。所以当 $n=1$ 的时候只需要判断是否有 $m=0$ 成立。

然后就到了关键的 $n>1$ 这一部分了。众所周知，一个 $n$ 个点的图要变成联通的，最少需要 $n-1$ 条边（此时它是一棵树），而且要保证不存在重边和自环的话，由于每个点最多能向 $n-1$ 个点连边，但是不难发现，这样算的话每条边会重复计算 $2$ 次。因此，满足条件的 $n$ 个点的图最多边数为 $\frac {n(n-1)}2$。因此可以首先排除 $m$ 不在 $[n-1,\frac{n(n-1)}2]$ 这个区间内的情况，此时一定不能构造出满足题目要求的图。

然后我们再分成 $m\in[n-1,\frac{n(n-1)}2)$ 和 $m=\frac{n(n-1)}2$ 这两个部分来讨论。

首先，我们来看，这是 $m=n-1$ 的时候能够构造出来的直径最短的图的例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/2njcd59h.png)

这种一个点连向其他所有点的树，我们称之为**菊花图**。可以看到，菊花图的直径为 $2$，而非完全图不能做到一个点可以仅通过一条边到达其他点，因此，当 $m\in[n-1,\frac{n(n-1)}2)$ 时，直径最小是 $2$。对应可以算出 $2<k-1\Rightarrow k>3$。

而当 $m=\frac{n(n-1)}2$ 的时候，此时图变成了完全图，可以做到一个点仅通过一条边到达其他点，因此其直径为 $1$，对应可以算出 $1<k-1\Rightarrow k>2$。

对应情况分类讨论判断即可通过此题。
## Code
```cpp
namespace Solution {
	iv Main() {
		MT {
			ll n, m, k;
			read(n, m, k);
			if(n == 1) {
				if(!m && k >= 2) YES; //赛时由于这里没有写 k >= 2 惨遭暴毙
				else NO;
			}
			else if(m < n - 1) NO;
			else if(m >= n - 1 && m < n * (n - 1) / 2) {
				if(k <= 3) NO;
				else YES;
			} else if(m == n * (n - 1) / 2) {
				if(k <= 2) NO;
				else YES;
			} else NO;
		}
		return;
	}
}
```

---

## 作者：Meaninglessness (赞：0)

### B. Diameter of Graph

**题目大意：**
> 询问 $n$ 个点和 $m$ 条边，是否存在一个连通图，使得没有重边，没有自环，且图的直径小于 $k-1$。

> 这里图的直径定义为图上任意两点之间的最短路的最小值。

**解题思路：**

若 $m < n-1$，则构不成连通图，答案为 ```NO```。

若 $m > n*(n-1)/2$，则图中会有重边，答案为 ```NO```。

那么现在必然能够造出一个定义上合法的图，考虑若构造菊花图，则直径为 $2$，那么当 $k>3$ 时必然满足。

只有当图为完全图，即 $m=n*(n-1)/2$ 时，图的直径为 $1$，那么 $k=3$ 时也能满足。

注意若图中只有 $1$ 个点，那么图的直径为 $0$，$k=2$ 时也行。

（据说部分人都因为这个 fst 了）

---

## 作者：yangzd (赞：0)

# 题目大意

给定 $n,m,k$ ，是否能构造无向连通图，使得

+ 正好有 $n$ 个点， $m$ 条边，且没有重边和自环

+ 直径严格小于 $k-1$ ，直径指 $max{dis(i,j)}$ ($dis$ 指两点之间最短距离)，即最远点对的距离。

# 分析

先排除非联通、$k≤1$ ，边数过多的情况。

其次，$k-2$ 为 $0$ ，即直径为 $0$ ，只可能是一个点的平凡图。

$k-2$ 为 $1$ ，即直径至多为 $1$ ，必然是完全图 (考虑少一条 $i→j$ 的边，则 $i→j$ 的距离至少是 $2$ )。

$k-2$ 至少为 $2$ ，则构造直径为 $2$ 即可，可以构造菊花图 (一个点连通所有其他的点，则直径至多是 $2$ )

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	ios::sync_with_stdio(0);
	
	long long n,m,k;
	
	cin >> n >> m >> k;
	
	if(m<n-1 || k<=1 || m>n*(n-1)/2)
		cout << "NO" << endl;
		 
	if(m==0 && n==1)
		cout << "YES" << endl;
		
	if(k==2 || (k==3 && (n*(n-1)/2!=m))) 
		cout << "NO" << endl;
		
	else
		cout << "YES" << endl;
		
	return 0;
}
```

---

