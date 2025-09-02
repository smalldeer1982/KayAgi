# Sereja and the Arrangement of Numbers

## 题目描述

Let's call an array consisting of $ n $ integer numbers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ , beautiful if it has the following property:

- consider all pairs of numbers $ x,y $ $ (x≠y) $ , such that number $ x $ occurs in the array $ a $ and number $ y $ occurs in the array $ a $ ;
- for each pair $ x,y $ must exist some position $ j $ $ (1<=j&lt;n) $ , such that at least one of the two conditions are met, either $ a_{j}=x,a_{j+1}=y $ , or $ a_{j}=y,a_{j+1}=x $ .

Sereja wants to build a beautiful array $ a $ , consisting of $ n $ integers. But not everything is so easy, Sereja's friend Dima has $ m $ coupons, each contains two integers $ q_{i},w_{i} $ . Coupon $ i $ costs $ w_{i} $ and allows you to use as many numbers $ q_{i} $ as you want when constructing the array $ a $ . Values $ q_{i} $ are distinct. Sereja has no coupons, so Dima and Sereja have made the following deal. Dima builds some beautiful array $ a $ of $ n $ elements. After that he takes $ w_{i} $ rubles from Sereja for each $ q_{i} $ , which occurs in the array $ a $ . Sereja believed his friend and agreed to the contract, and now he is wondering, what is the maximum amount of money he can pay.

Help Sereja, find the maximum amount of money he can pay to Dima.

## 说明/提示

In the first sample Sereja can pay $ 5 $ rubles, for example, if Dima constructs the following array: $ [1,2,1,2,2] $ . There are another optimal arrays for this test.

In the third sample Sereja can pay $ 100 $ rubles, if Dima constructs the following array: $ [2] $ .

## 样例 #1

### 输入

```
5 2
1 2
2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
100 3
1 2
2 1
3 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1 2
1 1
2 100
```

### 输出

```
100
```

# 题解

## 作者：_cyle_King (赞：4)

# CF367C 题解

## 题意

$m$ 个数 $q_i$ 互不相同，每一个的价值为 $w_i$，构造一个序列 $b$，要求：

1. 对于任意 $i$ 满足 $i\in\left[1,n\right]$，存在 $j\in\left[1,m\right]$，使得 $b_i=q_j$。
2. 对于 $b$ 中任意两个不同的元素 $x,y$，至少存在一个 $i(1\leq i\leq n)$，满足 $b_i=x\ \And b_{i+1}=y\lor b_i=y\ \And b_{i+1}=x$。

设 $S=\{i\in\left[1,m\right]|\exists\ j\in\left[1,n\right],q_i=b_j\}$，求 $\max\{\sum_{i\in S}w_i\}$。

#### 数据范围

$1\leq n\leq 2 \times10^6,1\leq m,q_i,w_i\leq 10^5$，保证 $\forall\ i\not=j,q_i\not=q_j$。

## 分析

不用考虑具体的构造方法，$q_i$ 真的一点用处也没有。采用贪心的思想，将 $w$ 从大到小排序，尽可能多的选大的 $w_i$ 就可以了。问题变为最大化选的不同的数的数量。

#### 转化问题

> 以下所说的选的数默认是选的不同数的数量，不考虑每一个数被选几次。

不如换一个角度思考：不考虑 $b$ 的长度为 $n$ 的限制，已知当前选的数的数量 $x$，求 $b$ 的最小长度，记作 $y$，题目转变为找到最大的 $x$，满足 $y\leq m$。可以直接暴力边判断边统计答案。

来考虑如何已知 $x$ 求 $y$。

#### 二度转化

观察第二个要求。对于每一对选出的 $a,b$，在 $a,b$ 之间连上一条无向边，表示这两个数相邻。那么问题就变成了找到一条最短的路径（可与自己相交），将 $m$ 条边覆盖。路径长度加 $1$ 就是 $y$。

显然连成的图是一个完全图，每一个点的度数为 $x-1$，分两种情况讨论。

- 当 $x$ 是奇数时，$x-1$ 是偶数，$x>1$ 时图是一个欧拉图，直接走欧拉回路就行了，$y=\dfrac{x(x-1)}{2}+1$，$x=1$ 时 $y=1$。

- 当 $x$ 是偶数时，$x-1$ 是奇数，除非 $x=2$（此时 $y=2$），否则图中不存在欧拉路径。

  这时，每一个顶点先留 $1$ 条边不跑，去除这些边后剩下的子图是一个欧拉图，采用贪心的方法，跑一遍欧拉回路。

  

  再来考虑剩下的没有跑的边组成的子图，由于每一个顶点只有一条边与之相连，因此每一个节点通过一条边与其余的节点构成一个孤立的节点对（如图），节点对的数量为 $\dfrac{x}{2}$。

  ![图片已被删除](https://cdn.luogu.com.cn/upload/image_hosting/qwefee9b.png)

  

  经过最少的边将这些节点对覆盖，显然可以将这些节点对首尾连接起来，形成一条链的形状（如图）。

  ![图片已被删除](https://cdn.luogu.com.cn/upload/image_hosting/i0kv806n.png)

  这一定是最优的方案，证明不难。

  

  由于只在将节点对连接成链时经过了重复的边（这个答案为 $\dfrac{x}{2}-1$），其余时候没有，因此 $y=1+\dfrac{x(x-1)}{2}+\dfrac{x}{2}-1=\dfrac{x^2}{2}$



剩下的就不难了，直接从小到大枚举 $x$ 判断是否有 $y\leq n$ 就可以了。当出现 $y>n$ 的情况时直接退出循环。

### Code

```cpp
#include<bits/stdc++.h>

#define rep(i,x,y) for(int i=(x), _=(y); i<=_; i++)
#define per(i,x,y) for(int i=(x), _=(y); i>=_; i--)

using namespace std;
template <class T1, class T2> inline bool cmax(T1 &a, T2 b) {return a < b ? a = b, 1 : 0;}
template <class T1, class T2> inline bool cmin(T1 &a, T2 b) {return b < a ? a = b, 1 : 0;}
typedef pair<int, int> pii;
typedef pair<int, long long> pil;
typedef pair<long long, int> pli;
typedef pair<long long, long long> pll;
typedef long long LL;

const int N = 1e6 + 10;

int 
main() {
	int n, m;
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	vector<int> a;
	a.reserve(m + 1);
	rep(i, 1, m) {
		int x, y; cin >> x >> y; a.emplace_back(y);
	}
	sort(a.begin(), a.end(), greater<int> ());
	LL ans = 0;
	rep(i, 0, m - 1) {//下标从0开始，奇偶性是相反的
		LL now;
		if(i & 1) now = 1ll * (i + 1) * (i + 1) / 2;//注意到 x = 2 时公式依然适用
		else now = 1 + 1ll * i * (i + 1) / 2;
		if(now > n) break;
		else ans += a[i];
	}
	cout << ans << endl;
	return 0;
}

```



# End













---

