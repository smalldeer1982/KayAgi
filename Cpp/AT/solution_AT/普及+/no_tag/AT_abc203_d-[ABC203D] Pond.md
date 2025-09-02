# [ABC203D] Pond

## 题目描述

### 题目大意

给定一个 $n\times n$ 的矩阵 $A$，再给定一个数 $k$，求矩阵中所有大小为 $k\times k$ 的子矩阵的中位数的最小值。

一个 $k\times k$ 的矩阵的中位数被定义为将矩阵中的所有数从大到小排序后的第 $\lfloor\frac{k^2}{2}\rfloor+1$ 个数。

## 说明/提示

$1\le k\le n\le 800,0\le A_{i,j}\le 10^9$。

Translated by \_Ponder_

## 样例 #1

### 输入

```
3 2
1 7 0
5 8 11
10 4 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3
1 2 3
4 5 6
7 8 9```

### 输出

```
5```

# 题解

## 作者：_RainCappuccino_ (赞：10)

# AT_abc203_D

## 题意

给出一个 $N \times N$ 的矩阵，然后依次枚举 $k \times k$ 的子矩阵。

对于 $k \times k$ 的子矩阵，一共有个 $k^2$ 元素，找出其中的中位数。这里的中位数是子矩阵中元素从大到小排列的第 $\left \lfloor \frac{k^2}{2}  \right \rfloor $ 个元素。问对于所有子矩阵的中位数中，最小的那个中位数是多少。

## 思路

### 1. 暴力枚举

暴力枚举右下端点，将 $k\times k$ 矩阵中的元素取出，然后排序。时间复杂度为 $O(n^2k^2\log k)$，绝对超时。

### 2. 二分答案+二维前缀和

我们不妨转变思路，从枚举矩阵到二分中位数。判断一个值能否成为一个 $k\times k$ 矩阵的中位数。

#### 如何判断是否为中位数？

假设一个数 $x$ ，如果 $a_{i,j} > x$，那么另一个二维矩阵中的 $b_{i,j}$ 便设为 $1$，否则设为 $0$。这样便将矩阵 $a$ 转变成了一个零一矩阵 $b$。对其求前缀和，这样就可以求得 $b$ 中任意一个 $k\times k$ 矩阵中 $1$ 的个数。如果其中 $1$ 的个数小于等于 $\left \lfloor \frac{k^2}{2}  \right \rfloor $ 那么将上界调为 $x$，否则将下界调整为 $x+1$。时间复杂度为 $O(n^2\log n)$。 

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 800 + 5;
int n, k, l, r, kpow, lim;
int a[MAXN][MAXN], b[MAXN][MAXN];
bool check(int x) {
	int z;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			b[i][j] = a[i][j] > x;//转化为01矩阵
			b[i][j] = b[i][j - 1] + b[i - 1][j] - b[i - 1][j - 1] + b[i][j];//求二维前缀和
		}
	}
	bool flag = 0;
	for (int i = 1; i <= n - k + 1; i++) {
		for (int j = 1; j <= n - k + 1; j++) {
			z = b[i + k - 1][j + k - 1] - b[i - 1][j + k - 1] - b[i + k - 1][j - 1] + b[i - 1][j - 1];//一的个数
			if (z <= kpow) {
				flag = 1;//如果找到了一个可能的值就退出
				break;
			}
		}
		if (flag) break;
	}
	return flag;
}
signed main() {
	scanf("%d%d", &n, &k);
	kpow = k * k / 2;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &a[i][j]);
			r = max(a[i][j], r);
		}
	}
	while (l < r) {//二分
		int mid = (l + r) >> 1;
		if (check(mid)) {//可行，找更小的
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	printf("%d", r);
	return 0;
}
```







---

## 作者：刘辰雨 (赞：3)

题意：求 $N\times N$ 的矩阵中的所有 $K\times K$ 的小矩阵的中位数的**最小值**。

此处，题目定义“中位数”为小矩阵中所有 $K^2$ 个数的第 $\lfloor \frac{K^2}{2}\rfloor+1$ 大的数。譬如，对于矩阵 $\begin{array}{c} 8 & 11 \\ 4 & 2 \end{array}$，其中位数为 $4$。

正解：**二分答案**后用**二维前缀和**判断每个小矩阵内大于答案的数有几个；另一篇题解不会（$\text{Ta}$ 糊了个暴力），但是我会。

看到这里请先去手打一遍，然后你会在二分统计答案和确定区间的时候遇到问题，然后你再来看我的方法。

---

二分的时候，我们统计的是**每个矩阵内大于答案的数有多少个**，$\text{Thus}$：

- 如果这个答案合法，那么应该至少有一个矩阵内，这个数字是 $\lfloor\frac{K^2}{2}\rfloor$，这时统计答案。
- 如果对于所有矩阵，这个数字都大于 $\lfloor\frac{K^2}{2}\rfloor$，那么答案太小了，再小一些不会有解。
- 否则，就有一些矩阵中，这个数字小于 $\lfloor\frac{K^2}{2}\rfloor$，那么答案还有更小的可能。

就这样去统计答案并确定区间。

Code:

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int k, n;
int mp[801][801];
int pre[801][801];
int minv = 1e9, maxv;

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1 ; i<= n ; i++) {
		for(int j = 1 ; j<= n ; j++) {
			scanf("%d", &mp[i][j]);
			minv = min(mp[i][j], minv);
			maxv = max(mp[i][j], maxv);
		}
	}
	int l = minv, r = maxv, ans = maxv;
	while(l <= r) {
		int mid = (l+r) >> 1;
		for(int i = 1 ; i <= n ; i++) {
			for(int j = 1 ; j<= n ; j++) {
				pre[i][j] = 0;
				if(mp[i][j] > mid) pre[i][j] = 1;
				pre[i][j] = pre[i][j]+pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
			}
		}
		maxv = 0, minv = 1e9;
		bool F = false;
		for(int i = 1 ; i+k-1 <= n ; i++) {
			for(int j = 1 ; j+k-1 <= n ; j++) {
				int o = i+k-1;
				int p = j+k-1;
				int num = pre[o][p]-pre[o][j-1]-pre[i-1][p]+pre[i-1][j-1];
				if(num == k*k/2) F = true;
				maxv = max(maxv, num);
				minv = min(minv, num);
			}
		}
		if(F) ans = mid, r = mid-1;
		else if(minv > k*k/2) l = mid+1;
		else r = mid-1;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：loser_seele (赞：3)

题意：给定 $ N,K $，求 $ N \times N $ 的矩阵内所有 $ K \times K $ 的子矩阵的中位数的最小值。

正解是二分答案之后二维前缀和判断矩阵内大于答案的数有几个，但是我不会，于是参考 [这题](https://www.luogu.com.cn/problem/P1527) 的思路，暴力算出所有矩阵内的答案之后取最小值即可。

实际上这是区间第 $ K $ 大的二维情况，套用类似的整体二分思路，考虑对每个询问二分答案，统计比一个询问的数大的数的数量，如果较小则递归右区间，否则递归左区间。现在问题是如何统计这个数，可以动态维护二维前缀和，这个可以用朴素二维树状数组实现。至于具体的实现过程和更详细的讲解可以翻那题题解。理论上这题的数据范围较大是过不去的，但是树状数组常数较小可以通过。

时间复杂度 $ \mathcal{O}(N^2\log{N}^3) $，卡了好几发才压线过，喜提最劣解。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int N = 815;
int n, Q;
int a[N][N];
long long tr[N][N];
int ans[2000101];
struct group 
{
	int x, y, value;
}g[N * N]; 
int siz = 0;
struct queries
 {
	int id, _X1, _Y1, _X2, _Y2, k;
}q[N * N], tmp[N * N];
int le = 0;
int lowbit(int x) 
{
	return x & (-x);
}
int query(int x, int y) 
{
	int s = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		for(int j = y; j > 0; j -= lowbit(j))
			s += tr[i][j];
	return s;
}
void update(int x, int y, int v) 
{
	for(int i = x; i < N; i += lowbit(i))
		for(int j = y; j < N; j += lowbit(j))
			tr[i][j] += v;
	return;
}
int range(queries A) 
{
	return query(A._X2, A._Y2) - query(A._X1 - 1, A._Y2) - query(A._X2, A._Y1 - 1) + query(A._X1 - 1, A._Y1 - 1);
}
void work(int left, int right, int L, int R) 
{ 
	if(L > R)
		return;
	if(L == R) 
    {
		for(int i = left; i <= right; i++)
			ans[q[i].id] = g[L].value;
		return;
	}
	int mid = (L + R) >> 1;
	if(le < mid) 
    {
		for(int i = le + 1; i <= mid; i++)
			update(g[i].x, g[i].y, 1);
	}
	else if(le > mid) 
    {
		for(int i = le; i > mid; i--)
			update(g[i].x, g[i].y, -1);
	}
	le = mid;
	int l = left, r = right;
	for(int i = left; i <= right; i++) 
    {
		if(range(q[i]) >= q[i].k) 
        {
			tmp[l++] = q[i];
		}
		else 
        {
			tmp[r--] = q[i];
		}
	}
	l--;
	for(int i = left; i <= right; i++)
		q[i] = tmp[i];
	work(left, l, L, mid);
	work(l + 1, right, mid + 1, R);
}
bool cmp(group a, group b) 
{
	return a.value < b.value;
}
int main() 
{
	scanf("%d", &n);
    int kk;
    cin>>kk;
	for(int i = 1; i <= n; i++) 
    {
		for(int j = 1; j <= n; j++) 
        {
			scanf("%d", &a[i][j]);
			g[++siz].value = a[i][j], g[siz].x = i, g[siz].y = j;
		}
	}
	stable_sort(g + 1, g + siz + 1, cmp);
    int now=0;
    int BLOCK=kk*kk-kk*kk/2;
	for(int i = 1; i+kk-1<=n; i++)
    for(int j=1;j+kk-1<=n;j++)
    Q++,q[Q]._X1=i, q[Q]._Y1=j, q[Q]._X2=i+kk-1, q[Q]._Y2=j+kk-1, q[Q].k=BLOCK,q[Q].id = Q;
	work(1, Q, 1, siz);
    int minn=2e9;
	for(int i = 1; i <= Q; i++)
	minn=min(minn,ans[i]);
    cout<<minn;
}
```


---

