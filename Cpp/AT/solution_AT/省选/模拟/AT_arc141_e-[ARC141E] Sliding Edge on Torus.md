# [ARC141E] Sliding Edge on Torus

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc141/tasks/arc141_e

$ N^2 $ 頂点からなる無向グラフがあります。はじめ、グラフは辺を持ちません。 $ 0\ \leq\ i,\ j\ <\ N $ を満たす整数の組 $ (i,\ j) $ それぞれについて、それに対応する頂点がひとつ存在し、その頂点を $ (i,\ j) $ と呼びます。

$ Q $ 個のクエリが与えられます。$ i $ 番目のクエリでは $ 4 $ つの整数 $ a_i,\ b_i,\ c_i,\ d_i $ が与えられるので以下のように順番に処理してください。

- 各 $ k\ (0\ \leq\ k\ <\ N) $ について、$ 2 $ 頂点 $ ((a_i+k)\ \bmod\ N,\ (b_i+k)\ \bmod\ N),\ ((c_i+k)\ \bmod\ N,\ (d_i+k)\ \bmod\ N) $ 間に辺を追加してください。その後、グラフの連結成分数を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ a_i,\ b_i,\ c_i,\ d_i\ <\ N $
- $ (a_i,\ b_i)\ \neq\ (c_i,\ d_i) $
- 入力される値はすべて整数

### Sample Explanation 1

$ 1 $ 番目のクエリでは頂点 $ (0,\ 0),\ (1,\ 2) $ 間、$ (1,\ 1),\ (2,\ 0) $ 間、$ (2,\ 2),\ (0,\ 1) $ 間に辺が追加されます。これにより連結成分数は $ 9 $ から $ 6 $ に変化します。

### Sample Explanation 2

クエリ処理の結果、グラフは単純グラフではなくなることがあります。

## 样例 #1

### 输入

```
3 3
0 0 1 2
2 0 0 0
1 1 2 2```

### 输出

```
6
4
4```

## 样例 #2

### 输入

```
4 3
0 0 2 2
2 3 1 2
1 1 3 3```

### 输出

```
14
11
11```

## 样例 #3

### 输入

```
6 5
0 0 1 1
1 2 3 4
1 1 5 3
2 0 1 5
5 0 3 3```

### 输出

```
31
27
21
21
19```

# 题解

## 作者：Singercoder (赞：4)

一个只用维护并查集的简单做法。

对于枚举 $k$ 所得到的格点 $(a_i+k,b_i+k)$，我们将它们归为一组染成同样颜色，$n=4$ 时候的染色长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/r54l8nwj.png)

把同样颜色的点取出来记成一组，根据横坐标从小到大排序，得到一个方便观察的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/g63o9u74.png)

不难发现对于一个格点 $(x,y)$，它的所在组号为 $(y-x) \mod n$，对应组内位置为第 $x$ 个。

然后考虑我们的每次操作，我们要操作的对象是 $(a,b)$ 和 $(c,d)$，首先给这些参数都减去 $a$ 是不影响操作的，于是得到操作对象 $(0,b-a)$ 和 $(c-a,d-a)$。

操作的第一个点是第 $b-a$ 组的第 $0$ 个点。

操作的第二个点是第 $d-c$ 组的第 $c-a$ 个点。

下面讨论我们要维护什么，我们要维护的是一个带权并查集，并查集中的点 $i$ 对应着第 $i$ 组的第 $0$ 个点，如果有一条边从 $u$ 指向 $v$ 权值为 $w$，表示的含义是第 $u$ 组的第 $0$ 个点与第 $v$ 组的第 $w$ 个点相连通。

所以对于上面的操作，如果 $b-a$ 和 $d-c$ 当前不在一个并查集里，就连一条从 $b-a$ 到 $d-c$ 的权值为 $c-a$ 的边，注意带权并查集意义下的连边不一定是直接相连，实际上我们是把它们各自所在森林的根连在了一起，那条边的权值用向量加减的思路计算即可。

但还没完，我们的操作有可能使某一个组内的两个点相连，我们记录并查集某颗森林根节点的 $f_u$ 表示第 $u$ 组中的第 $0$ 个点与第 $u$ 组中的第 $f_u$ 个点相连通。

一个组内的点可能会有多次联通操作，假设第一次操作使 $0$ 与 $p$ 联通，第二次操作使 $0$ 与 $q$ 联通，那么这等价于 $0$ 与 $\gcd(p,q)$ 联通。

如何根据 $f_u$ 求出第 $u$ 组内联通块的个数呢，计算 $\gcd(f_u,n)$ 即可。

对于这两个 $\gcd$ 可以用裴蜀定理来理解。

我的思路就是分好颜色以后，想一定要用带权并查集，然后各种设计都是往并查集上套的，所以意义上并不是很自然。

但是设计好了以后代码就很简洁了。

```c++
#include<bits/stdc++.h>

#define ll long long 

using namespace std;

const int N=2e5+10;

int gcd(int a,int b)
{
	return b ? gcd(b,a%b) : a;
}

int n,q;
int fa[N],w[N],f[N];
ll ans;
int get_fa(int u)
{
	if(u==fa[u])return u;
	else
	{
		int r=get_fa(fa[u]);
		if(fa[u]!=r)
		{
			w[u]=(w[u]+w[fa[u]])%n;
			fa[u]=r;
		}
		return r;
	}
}
void merge(int u,int v,int k)
{
	int fu=get_fa(u);
	int fv=get_fa(v);

	if(fu!=fv)
	{
		ans-=gcd(n,f[fu])+gcd(n,f[fv]);
		fa[fu]=fv;
		w[fu]=(k-w[u]+w[v]+n)%n;
		f[fv]=gcd(f[fu],f[fv]);
		ans+=gcd(n,f[fv]);
	}
	else
	{
		ans-=gcd(n,f[fu]);
		f[fu]=gcd(f[fu],(k-w[u]+w[v]+n)%n);
		ans+=gcd(n,f[fu]);
	}
}

int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);

	scanf("%d %d",&n,&q);
	for(int i=0;i<n;++i)fa[i]=i;
	ans=(ll)n*n;
	
	for(int i=1;i<=q;++i)
	{
		int a,b,c,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);

		b=(b-a+n)%n;
		c=(c-a+n)%n;
		d=(d-a+n)%n;
		a=0;

		int u=b;
		int v=(d-c+n)%n;
		merge(u,v,c);

		printf("%lld\n",ans);
	}

	return 0;
}
```



---

## 作者：tzc_wk (赞：2)

妙啊！

首先一维的问题是 trivial 的，直接用斐蜀定理转化为得到答案为所有 $k$ 的 $\gcd$。

对于二维的问题，我们首先将 $b,c,d$ 均减去 $a$，这样相当于对于所有 $x$，合并 $(x,(x+b)\bmod n)$ 与 $((x+c)\bmod n,(x+d)\bmod n)$。注意到我们对行列进行平移是不影响答案的，因此我们将第 $x$ 行向左平移 $x$ 位，即坐标 $(x,x+y)$ 变为 $(x,y)$，这样相当于合并 $(x,b)$ 与 $((x+c)\bmod n,(d-c)\bmod n)$。

我们先考虑两种特殊情况：

- $b=(d-c)\bmod n$，这样显然每一列都是独立的，对其做一维的问题即可。
- $c=0$，这样相当于并查集。

我们考虑将两者结合起来，即这样一个思想：我们先假设我们搞出了一个序列 $e$ 并将所有 $(x,y)$ 变换为 $(x+e_y,y)$（即，对每一列进行一定大小的轮换），我们希望，对于每次操作的 $b$ 与 $(d-c)\bmod n$，如果我们在每次操作都对这两个点进行并查集上的合并操作，且对于每次在合并前 $b$ 与 $(d-c)\bmod n$ 不在同一集合中的操作，都有进行坐标变换后的 $c=0$，那么这个问题就是可以解的了。因为如果在后面的合并中，我们合并的 $b$ 与 $(d-c)\bmod n$ 在同一集合中，我们就可以将其转化为一维的问题了。而这个 $e_x$ 的求法很简单——因为在每次有效合并的时，我们可以知道 $e_b$ 与 $e_{(d-c)\bmod n}$ 的差，建出图来 DFS 即可。

时间复杂度 $n\alpha(n)$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc141_e)

**题目大意**

> 给定 $n\times n$ 个点，标号 $(1,1)\sim (n,n)$，$q$ 次操作对于所有 $((a+k)\bmod n,(b+k)\bmod n)$ 与 $((c+k)\bmod n,(d+k)\bmod n)$ 连边（$0\le k<n$）。
>
> 每次操作后求图中连通块数。
>
> 数据范围：$n,q\le 2\times 10^5$。

**思路分析**

首先把 $(x,y)$ 用 $(x,(y-x)\bmod n)$ 表示，那么相当于 $(i,(b-a)\bmod n)$ 与 $((i-a+c)\bmod n,(d-c)\bmod n)$ 连边。

对于 $(b-a)\bmod n$ 和 $(d-c)\bmod n$，如果他们原先不在一个连通块里，那么连边相当于建立点之间的映射，如果此前他们已经联通，那么我们可以看成在 $(b-a)\bmod n$ 内部的连边，而边长（每条边跨越的长度）可以算出，那么每次连边后新的环数也可以维护（即所有边长的 $\gcd$）。

因此用带权并查集维护当前列中的点到连通块的根中的点的映射，以及每个连通块内所有边长的 $\gcd$ 即可，合并是简单的。

时间复杂度 $\mathcal O(q\alpha(n))$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
long long ans;
int n,q,fa[MAXN],w[MAXN],f[MAXN];
int find(int x) {
	if(x==fa[x]) return x;
	int c=find(fa[x]);
	w[x]=(w[x]+w[fa[x]])%n;
	return fa[x]=c;
}
int gcd(int x,int y) { return y?gcd(y,x%y):x; }
void merge(int u,int v,int k) {
	//a[u]=a[v]+k, a[u]=a[x]+w[u], a[v]=a[y]+w[v]
	int x=find(u),y=find(v);
	if(x!=y) {
		ans-=gcd(n,f[x])+gcd(n,f[y]);
		fa[x]=y,w[x]=(k+w[v]+n-w[u])%n,f[y]=gcd(f[x],f[y]);
		ans+=gcd(n,f[y]);
	} else {
		ans-=gcd(n,f[x]);
		f[x]=gcd(f[x],(w[v]+k+n-w[u])%n);
		ans+=gcd(n,f[x]);
	}
}
signed main() {
	scanf("%d%d",&n,&q),ans=1ll*n*n;
	iota(fa,fa+n,0);
	for(int a,b,c,d;q--;) {
		scanf("%d%d%d%d",&a,&b,&c,&d);
		merge((b+n-a)%n,(d+n-c)%n,(c+n-a)%n);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

