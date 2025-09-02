# Reachable Towns

## 题目描述

[problemUrl]: https://atcoder.jp/contests/acl1/tasks/acl1_a

$ 2 $ 次元平面上に $ N $ 個の街があります。$ i $ 個目の街の座標は $ (x_i,\ y_i) $ です。ここで、$ (x_1,\ x_2,\ \dots,\ x_N) $ と $ (y_1,\ y_2,\ \dots,\ y_N) $ は、ともに $ (1,\ 2,\ \dots,\ N) $ の順列となっています。

各 $ k\ =\ 1,2,\dots,N $ について、以下の問題の答えを求めてください。

rngさんが街 $ k $ にいる。 rngさんは、今いる街よりも「$ x,\ y $ 座標がともに小さい街」か「$ x,\ y $ 座標がともに大きい街」に移動することを好きな回数繰り返すことができる。 rngさんが到達可能な街は、(街 $ k $ を含めて) 何種類あるか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200,000 $
- $ (x_1,\ x_2,\ \dots,\ x_N) $ は $ (1,\ 2,\ \dots,\ N) $ の並び替え
- $ (y_1,\ y_2,\ \dots,\ y_N) $ は $ (1,\ 2,\ \dots,\ N) $ の並び替え
- 入力される数は全て整数である．

### Sample Explanation 1

街 $ 3 $ からは街 $ 4 $ に、また逆に街 $ 4 $ からは街 $ 3 $ へ移動できます。

## 样例 #1

### 输入

```
4
1 4
2 3
3 1
4 2```

### 输出

```
1
1
2
2```

## 样例 #2

### 输入

```
7
6 4
4 3
3 5
7 1
2 7
5 2
1 6```

### 输出

```
3
3
1
1
2
3
2```

# 题解

## 作者：Accelessar (赞：4)

考虑先按 $x$ 排序，那么问题可转化成这样：
- 对于 $i\lt j$，若 $y_i\lt y_j$ 则在 $i,j$ 间连一条无向边。求每个点所属连通块大小。

发现这个形式几乎和 [ARC187B](https://atcoder.jp/contests/arc187/tasks/arc187_b) 一致，有以下结论：
- 每个连通块都是一个区间。  
  证明：假设存在一个连通块不包含 $i$，但在 $i$ 左侧和右侧都有点。则必然存在 $u,v$ 使得 $u\lt i\lt v\land y_u\lt y_v$。简单讨论 $y_i$ 的取值，发现无论取何值都至少和 $u,v$ 中的一者有连边，故假设不成立。
- $i,i+1$ 不连通，当且仅当 $\min_{j\le i}y_j\ge\max_{j\gt i}y_j$。  
  证明：显然 $i,i+1$ 不连通意味着 $i$ 所属连通区间的最小值大于等于 $i+1$ 所属联通区间的最大值。从而可以推广得到联通区间的值域是递减的，所以 $i$ 为分割点的充要条件可以弱化为前缀最小值大于等于后缀最大值。

那么可以 $O(n)$ 求出所有分割点，也即求出了所有连通块。

[submission](https://atcoder.jp/contests/acl1/submissions/62822392).

---

## 作者：StayAlone (赞：3)

## 思路

一些定理：

1. 若点 $a$ 能一步走到 $b$，那么 $b$ 一定能一步走到 $a$。

2. 若点 $a$ 能一步走到 $b$，$b$ 能一步走到 $c$，则 $a,b,c$ 都能互相走到。

进而，若 $a$ 能一步走到 $b$，可以在 $a,b$ 间连一条无向边。那么每个点的答案就是它所在连通块的大小。

**考虑先将坐标按 $x$ 排序**。画出样例 2 的图，如下。~~懒得 graph editor 了。~~


![](https://s1.ax1x.com/2023/02/13/pSoVFRP.png)

经过一些观察，可以发现，对于每一个 $i$，找到 $t_i = \min\limits_{j\in [1,i]\land y_j\leq y_i} j$，那么 $[t_i,i]$ 中的这些点在同一个连通块中。

-------

证明：

设 $t_i$ 的坐标为 $(x_1,y_1)$，$i$ 的坐标为 $(x_3,y_3)$，有 $x_1<x_3,y_1<y_3$。显然 $t_i$ 可以走到 $i$。


设 $k\in(t_i,i)$ 的坐标为 $(x_2,y_2)$，有 $x_1<x_2<x_3$。然后分类讨论：

1. 若 $y_1<y_2<y_3$，则 $k$ 可以走到 $i$，也能走到 $t_i$。
2. 若 $y_2<y_1$，由 $y_1<y_3$ 得 $y_2<y_3$，则 $k$ 可以走到 $i$。
3. 若 $y_2>y_3$，由 $y_1<y_3$ 得 $y_2>y_1$，则 $k$ 可以走到 $t_i$。

证明部分感谢 @[L\_h\_](https://www.luogu.com.cn/user/413129) 的提示。

-----------

记 $p_i$ 表示 $y$ 为 $i$ 的点的下标，即 $p_{y_i} = i$。做 $p$ 数组的前缀最小值 $mi_i$，那么 $t_i=mi_{y_i}$。

于是得到了 $n$ 个区间 $[t_i,i]$，可能相交。所以合并相交区间之后，对于每一段区间 $[l,r]$，这些点的答案都是 $r-l+1$。

时间复杂度为 $\mathcal O(n\log n)$，瓶颈在于排序。既然给的点都是排列，那么简单地改成桶排就能做到 $\mathcal O(n)$。

[AC record](https://www.luogu.com.cn/record/102080684)

```
int n, ans[MAXN], p[MAXN], mi[MAXN];
pii seg[MAXN]; pair <pii, int> a[MAXN];

int main() {
	read(n);
	rep1(i, 1, n) read(a[i].fst), a[i].snd = i;
	sort(a + 1, a + 1 + n); mi[0] = INF;
	rep1(i, 1, n) p[a[i].fst.snd] = i;
	rep1(i, 1, n) mi[i] = min(mi[i - 1], p[i]);
	rep1(i, 1, n) seg[i] = mp(mi[a[i].fst.snd], i);
	// 以下是合并区间 
	sort(seg + 1, seg + 1 + n);
	int l = seg[1].fst, r = seg[1].snd;
	rep1(i, 1, n) {
		if (r >= seg[i].fst) r = max(r, seg[i].snd);
		else {
			rep1(j, l, r) ans[a[j].snd] = r - l + 1;
			tie(l, r) = seg[i];
		}
	}
	rep1(i, l, r) ans[a[i].snd] = r - l + 1;
	rep1(i, 1, n) printf("%d\n", ans[i]);
	rout;
}

```

---

## 作者：良心WA题人 (赞：2)

## 前言

学校组织 VP 有人前后连 $20$ 条边过了，感觉很炫酷。不过正解也并不难。

## 题意

每个点可以走到自己左下角和右上角的点，问每个点能够到达的点的数量是多少。

## 思路

不难发现，如果连边，则同一个连通块内的边到达的个数是相同的，为连通块大小。

所以，考虑求出这个连通块大小。不难发现，最终每个连通块一定是形似下图的样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/0jcf1o75.png)

形如下图的图形若左下角有一个东西则会合并相对于该点在右上角的所有矩形。所以我们可以先按 $x$ 从小到大排序，然后去扫。如果扫到某个 $y$ 在前面某些矩形的左下角则合并，就做完了。这个可以用并查集 + 单调栈维护。时间复杂度 $O(n(\log_2n+\alpha(n)))$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=200004;
struct node
{
	int x,y,id;
	bool operator<(const node&it)const
	{
		return x>it.x;
	}
}a[NN];
int r[NN],siz[NN],fa[NN],ans[NN];
int find(int u)
{
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		fa[i]=i,siz[i]=1;
		a[i].id=i;
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
		r[i]=a[i].y;
	stack<int>sta;
	for(int i=1;i<=n;i++)
	{
		int last=i;
		while(sta.size()&&r[find(sta.top())]>a[i].y)
		{
			int fu=find(last),fv=find(sta.top());
			fa[fu]=fv;
			siz[fv]+=siz[fu];
			r[fv]=max(r[fv],r[fu]);
			last=sta.top();
			sta.pop();
		}
		sta.push(find(i));
	}
	for(int i=1;i<=n;i++)
		ans[a[i].id]=siz[find(i)];
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Bobi2014 (赞：0)

这是一道~~可爱~~的思维题。

### 前置知识

- [前缀和](https://blog.csdn.net/m0_69323023/article/details/135789840)
- [快速排序](https://zhuanlan.zhihu.com/p/123416868)
- [桶排序](https://zhuanlan.zhihu.com/p/125737294)

### 思路

已经被众多大佬写的十分详细了，本题解主要介绍代码写法以及时间复杂度分析。

### 代码写法

- 以关键字 $x$ 升序排序，记得结构体中要存储他原来的编号 $id$，时间复杂度 $O(n \log n)$。
- 记两个数组 $minn$ 与 $maxx$，一个存前缀最小值，另一个存后缀最大值，`minn[0]` 记得给初始值 `INT_MAX`，时间复杂度 $O(n)$。
- 记 $tot$ 为连通块数量，$cnt$ 为连通块的点数，$scc$ 为每个点属于哪个连通块。
- 根据思路，枚举 $1$ 到 $n$，如果 `minn[i - 1] > maxx[i]`，则 `tot ++`，不管加不加，都要让 `cnt[tot] ++`，`scc[i] = tot`，时间复杂度 $O(n)$。
- 记 $rnk$ 为输入时每个点对应排序完后的点，枚举 $1$ 到 $n$，`rnk[nodes[i].id] = i`，时间复杂度 $O(n)$。
- 输出时枚举 $1$ 到 $n$，输出 `cnt[scc[rnk[i]]]`，时间复杂度 $O(n)$。

### 最终时间复杂度

最终时间复杂度为 $O(n \log n)$，观察写法，发现本做法在时间复杂度有大量来自排序，我们观察数据范围，发现 $x < 2 \times 10^6 + 1$，可以桶排序，所以优化后时间复杂度 $O(n)$。

---

