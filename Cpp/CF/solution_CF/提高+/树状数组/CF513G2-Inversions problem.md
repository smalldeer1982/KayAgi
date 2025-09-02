# Inversions problem

## 题目描述

You are given a permutation of $ n $ numbers $ p_{1},p_{2},...,p_{n} $ . We perform $ k $ operations of the following type: choose uniformly at random two indices $ l $ and $ r $ ( $ l<=r $ ) and reverse the order of the elements $ p_{l},p_{l+1},...,p_{r} $ . Your task is to find the expected value of the number of inversions in the resulting permutation.

## 说明/提示

Consider the first sample test. We will randomly pick an interval of the permutation $ (1,2,3) $ (which has no inversions) and reverse the order of its elements. With probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513G2/6201067a97da7a97c457211e210f5a8e998bdde9.png), the interval will consist of a single element and the permutation will not be altered. With probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513G2/f7ba68e3a158029dadd77767404a7d3ca97f69d2.png) we will inverse the first two elements' order and obtain the permutation $ (2,1,3) $ which has one inversion. With the same probability we might pick the interval consisting of the last two elements which will lead to the permutation $ (1,3,2) $ with one inversion. Finally, with probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513G2/f7ba68e3a158029dadd77767404a7d3ca97f69d2.png) the randomly picked interval will contain all elements, leading to the permutation $ (3,2,1) $ with 3 inversions. Hence, the expected number of inversions is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513G2/35fd27aec725b8812c04480f588647c66aec3f9c.png).

## 样例 #1

### 输入

```
3 1
1 2 3
```

### 输出

```
0.833333333333333
```

## 样例 #2

### 输入

```
3 4
1 3 2
```

### 输出

```
1.458333333333334
```

# 题解

## 作者：Jerrywang09 (赞：0)

### 解析

定义 DP 状态：$f(t,i,j)$ 表示进行到第 $t$ 次操作，下标 $i,j$ 里的数构成逆序对的概率。根据期望的定义，所求答案（期望）就是 $\sum_{1\le i\le j\le n} f(k,i,j)$。

很容易想到一个非常暴力的 DP，枚举操作次数后，暴力枚举两个下标和反转的区间。时间复杂度是 $O(n^4k)$，无法通过。

考虑优化。设函数 $C(x)=\frac{x\cdot (x+1)}{2}$，含义是长度 $x$ 的区间内随机选取两个下标（可以相等）的方案数。这个方案数是 $\frac{x\cdot (x-1)}{2}+x$，化简为 $\frac{x\cdot (x+1)}{2}$。

选定了两个下标 $i,j$，一次翻转操作后会有什么影响？

1. 翻转操作完全与 $i,j$ 无关。

这个区间的选取一定严格在 $i$ 左或 $j$ 右，也可以严格在 $i,j$ 中间。方案数是 $C(i-1)+C(n-j)+C(j-i-1)$。方案数乘上每种下标对被选的概率，就是对下一个状态的贡献。

2. 翻转区间包含 $i$，但不包含 $j$。

可以枚举 $i$ 向右移动的距离 $k$。如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/k10cyary.png)

此处可以结合代码，`min(i, i+k)` 是 $i$ 与 $i+k$ 中较为靠左的下标。区间 $[i,i+k]$ 可以实现翻转，将 $i$ 翻转到 $i+k$，不难发现区间 $[i-1,i+k+1],[i-2,i+k+2]\cdots$ 都能实现同样功能。

这样的区间有多少个呢？$i,j$ 同步向左向右移动，其实区间个数就是两个移动距离的较小值，也就是 `min(min(i, i+k), j-max(i, i+k))`。

剩下两种情况，都和上述情况类似，请您画图并类比上述推导。

因为求的是期望，所以过大的 $k$ 无意义，可以将其与 $900$ 取 $\min$。同时，目前的复杂度还是悬，请使用快读和滚动数组。

### 代码

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, s, t) for(register int i=(s); i<=(t); ++i)
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define all(x) x.begin(), x.end()
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=105;
using namespace std;

inline int read()
{
	int x=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) {x=x*10+c-'0'; c=getchar();}
	return x;
}

int n=read(), m=min(read(), 900);
int a[N];
double f[N][N], g[N][N];									// 滚动数组卡常数

inline int C(int x) {return x*(x+1)/2;}

signed main()
{
	rep(i, 1, n) a[i]=read();
	rep(i, 1, n-1) rep(j, i+1, n)
		if(a[i]>a[j]) f[i][j]=1;							// 初始的逆序对
	double p=1./C(n);										// 选中一对数的概率
	rep(tt, 1, m)
	{
		memset(g, 0, sizeof g);
		rep(i, 1, n-1) rep(j, i+1, n)
		{
			g[i][j]+=f[i][j]*p*(C(i-1)+C(n-j)+C(j-i-1));	// i,j都不被翻转
			rep(k, 1-i, j-i-1)								// i被翻转，j不被翻转
				g[i+k][j]+=f[i][j]*p*min(min(i, i+k), j-max(i, i+k));
			rep(k, -(j-i-1), n-j)							// i不被翻转，j被翻转
				g[i][j+k]+=f[i][j]*p*min(n-max(j, j+k)+1, min(j, j+k)-i);
			rep(k, 1-i, n-j)								// i,j都被翻转，逆序对状态切换
				g[i+k][j+k]+=(1-f[i][j])*p*min(min(i, i+k), n-max(j, j+k)+1);
		}
		memcpy(f, g, sizeof f);
	}
	double ans=0;
	rep(i, 1, n-1) rep(j, i+1, n)
		ans+=f[i][j];
	printf("%.15lf", ans);
	
	return 0;
}
```

---

