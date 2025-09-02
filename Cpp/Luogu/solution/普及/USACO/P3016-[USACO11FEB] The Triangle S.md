# [USACO11FEB] The Triangle S

## 题目描述

For her spectacular milk output for the previous month, Farmer John has awarded Bessie a prize -- with a twist.  He has given her a triangular grid with N (1 <= N <= 700) rows (whose lengths vary from 1 through N, of course). Row i of the the grid has i values labeled v\_ij (-1,000,000,000 <= v\_ij <= 1,000,000,000) where j is in the range 1..i.

Bessie chooses a sub-triangle whose side length is at least K (1 <= K <= 20; 1 <= K <= N) within the triangular grid. The sub-triangle is another triangular grid which might be oriented the same as the original triangle or might be 'upside down' with its shorter rows on the bottom instead of the top.

After she chooses her sub-triangle, Farmer John will take the average of all the numbers in the sub-triangle, discarding the digits to the right of the decimal point, and give her that many gold coins (or take that many gold coins from her if the number is negative). Naturally, Bessie would like to maximize her prize (or minimize her loss). Help her solve this problem.

By way of example, Bessie is given this triangular grid with N = 3 rows and must choose a sub-triangle with a side length of at least K = 2. A graphical representation of the triangle is shown below:

```cpp
    / \
   / 5 \
  /-8  4\
 /2 -3  6\
 ---------
```
She could choose any of five valid sub-triangles (one of which is the entire original triangle):

```cpp
                                                   /\
    / \         / \        / \         / \        /5 \       
   / 5 \       / \5\      / 5 \       / 5/\      /----\    
  /-8  4\     /-8 \4\    /-8  4\     /-8/ 4\    /\-8 4/\ 
 /2 -3  6\   / 2 -3\6\  /-------\   / 2/-3 6\  / 2\-3/6 \ 
 ---------   ---------  -2  -3  6   ---------  ----------  
  entire      lower        top          lower     upside
 triangle     left                      right      down
```
The one that is lined below is the one with the highest average:

```cpp
    / \
   / 5/\
  /-8/ 4\
 / 2/-3 6\
 ---------
```
The average of this sub-triangle is (4+6-3)/3, which is about

2.3333...; without the fraction, the answer is 2. 

Help Bessie calculate the maximum amount of coins which she could receive.

TIME LIMIT: 2 seconds

MEMORY LIMIT: 32 MB

有一个n(1<=n<=700)行的等腰三角形，里面有很多数(-1,000,000,000 <= 数 <= 1,000,000,000)，现在可以选择边长至少为k(1<=k<=20,1<=k<=n)，至多为2k的相似等腰三角形，并且可以倒着选，比如样例可以有这些选择方法：


样例：

```cpp
                                                   /\
    / \         / \        / \         / \        /5 \       
   / 5 \       / \5\      / 5 \       / 5/\      /----\    
  /-8  4\     /-8 \4\    /-8  4\     /-8/ 4\    /\-8 4/\ 
 /2 -3  6\   / 2 -3\6\  /-------\   / 2/-3 6\  / 2\-3/6 \ 
 ---------   ---------  -2  -3  6   ---------  ----------  
  entire      lower        top          lower     upside
 triangle     left                      right      down
```
最后问你可以得到的最大平均值为多少（平均值：选出的三角形的累加和div选出个数）


## 说明/提示

感谢 zzkksunboy 提供翻译。


## 样例 #1

### 输入

```
3 2 
5 
-8 4 
2 -3 6 
```

### 输出

```
2 
```

# 题解

## 作者：Log_x (赞：8)

## Solution 
- 一道比较裸的**模拟**……

- 首先我们考虑枚举子三角形的顶点（当然顶点既可能在子三角形的最上方，也可能在最下方），然后枚举子三角形的边长，计算子三角形中每一层数的和。

- 这里每一层数的和可以预处理其前缀和，然后在枚举中 $O(1)$ 得到，那么总的时间复杂度大概也就是 $O(n^2k)$。而且实际上我们一旦发现枚举的子三角形超出了大三角形的边界就可以直接结束枚举边长的循环，这样也能快很多。

- 不过题目中对三角边边长不能超过 $2k$ 的要求是没有必要的（这好像是译者自己加进去的……），因为这是可以通过其它条件推出来的，具体为什么也可以看看我的[博客](http://blog.csdn.net/bzjr_log_x/article/details/76849952)，这里就不多论述了。

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 705;
ll Ans = -1e15, a[N][N];
int n, d;

inline void CkMax(ll &x, const ll &y) {if (x < y) x = y;}

inline int get()
{
    char ch; int res = 0; bool f = false;
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');
    if (ch == '-') f = true;
     else res = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9')
     res = (res << 3) + (res << 1) + ch - '0';
    return f ? -res : res;
}

inline void put(ll x)
{
    if (x < 0) 
     x = -x, putchar('-');
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}

int main()
{
    n = get(); d = get();
    for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= i; ++j)
      a[i][j] = a[i][j - 1] + get();
    ll res, num;
    for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= i; ++j)
     {
         res = num = 0ll;
         for (int k = 1; k <= (d << 1); ++k)
         {
             int tx = i + k - 1, ty = j + k - 1;
             if (tx > n || ty > tx) break;
             res += a[tx][ty] - a[tx][j - 1]; num += k;
            if (k >= d) CkMax(Ans, res / num);
        }
        res = num = 0ll;
        for (int k = 1; k <= (d << 1); ++k)
        {
            int tx = i - k + 1, ty = j - k + 1;
            if (tx < 1 || ty < 1 || j > tx) break;
            res += a[tx][j] - a[tx][ty - 1]; num += k;
            if (k >= d) CkMax(Ans, res / num);
        }
     }
    return put(Ans), 0;
}
```

---

## 作者：lailai0916 (赞：2)

## 原题链接

- [洛谷 P3016 [USACO11FEB] The Triangle S](https://www.luogu.com.cn/problem/P3016)

## 解题思路

枚举所有的等边三角形，利用前缀和优化求和。

将正的三角形和倒的三角形分开计算。

枚举三角形的顶点 $(i,j)$，边长为 $k$ 的等边三角形。（$j\le i$）

对于每个边长为 $k$ 的三角形：

1. 总和可以由边长为 $k-1$ 的三角形的总和加上第 $k$ 行，而第 $k$ 行可以用前缀和计算。
2. 数字个数为 $\frac{k(k+1)}{2}$。
3. 如果 $K\le k\le 2K$，计算平均值，并维护最大值。

时间复杂度 $O(n^2k)$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const ll inf=0x3f3f3f3f3f3f3f3f;
const int N=705;
ll a[N][N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,K;
	cin>>n>>K;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			cin>>a[i][j];
			a[i][j]+=a[i][j-1];
		}
	}
	ll ans=-inf;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			ll sum=0;
			for(int k=1;k<=n-i+1;k++)
			{
				sum+=a[i+k-1][j+k-1]-a[i+k-1][j-1];
				if(k<K)continue;
				if(k>K*2)break;
				ans=max(ans,sum/(k*(k+1)/2));
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			ll sum=0;
			for(int k=1;k<=j&&k<=i-j+1;k++)
			{
				sum+=a[i-k+1][j]-a[i-k+1][j-k];
				if(k<K)continue;
				if(k>K*2)break;
				ans=max(ans,sum/(k*(k+1)/2));
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：furina_yyds (赞：0)

## 思路

一道模拟题。

先考虑枚举三角形的顶点，然后枚举三角形的边长，计算三角形中每一层数的和。直接模拟会 T 掉，怎么办呢？

这里每一层数的和可以预处理其前缀和，在后续枚举中 $O(1)$ 得到。总的时间复杂度也就是 $O(n^2k)$，一旦发现枚举的三角形超出了三角形的边界就可以直接结束枚举边长的循环，这样也能干掉不少不满足题意的。

~~这题真的是黄题吗？~~

## 代码

```cpp
#include <iostream>
#include <vector>

// 定义一个函数来比较并更新最大值
template<typename T>
void updateMax(T& maxVal, const T& newVal) {
    if (newVal > maxVal) {
        maxVal = newVal;
    }
}

int main() {
    int n, d;
    std::cin >> n >> d;

    // 使用 vector 存储二维数组，避免固定大小的数组
    std::vector<std::vector<long long>> a(n + 1, std::vector<long long>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            std::cin >> a[i][j];
        }
    }

    long long ans = -1e15;

    // 遍历二维数组
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            long long res = 0;
            long long num = 0;

            // 向右下方向计算
            for (int k = 1; k <= (2 * d); ++k) {
                int tx = i + k - 1;
                int ty = j + k - 1;
                if (tx > n || ty > tx) break;
                // 计算当前子区域的元素和
                for (int m = j; m <= ty; ++m) {
                    res += a[tx][m];
                    num++;
                }
                if (k >= d) {
                    updateMax(ans, res / num);
                }
            }

            res = 0;
            num = 0;

            // 向左上方向计算
            for (int k = 1; k <= (2 * d); ++k) {
                int tx = i - k + 1;
                int ty = j - k + 1;
                if (tx < 1 || ty < 1 || j > tx) break;
                // 计算当前子区域的元素和
                for (int m = ty; m <= j; ++m) {
                    res += a[tx][m];
                    num++;
                }
                if (k >= d) {
                    updateMax(ans, res / num);
                }
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
```

---

