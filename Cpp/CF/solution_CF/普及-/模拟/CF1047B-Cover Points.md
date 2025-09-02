# Cover Points

## 题目描述

现在有 $n$ 个点在飞机上，分别是 $(x_{1},y_{1}),(x_{2},y_{2}),\ldots,(x_{n},y_{n})$。

你需要在坐标轴上放置一个等腰三角形，以覆盖所有的点（一个点在三角形内或三角形的边上被覆盖），然后计算三角形较短边的最小长度。

## 样例 #1

### 输入

```
3
1 1
1 2
2 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
4
1 1
1 2
2 1
2 2
```

### 输出

```
4```

# 题解

## 作者：STLGirlfriend (赞：3)

可转换为求函数 $y = -x + b$ 使该函数图像可以覆盖所有点的 $b$ 值。

移项可得 $b = x + y$，所以求 $\max\{x_i + y_i\}$ 即为答案。

```c++
#include <cstdio>
#include <algorithm>

const int MaxN = 1e5;

int main() {
    int n;
    scanf("%d", &n);

    int res = -1e9;
    for (int i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        res = std::max(res, x + y);
    }

    printf("%d\n", res);
}
```

---

## 作者：E1_de5truct0r (赞：1)

- [题面传送门](https://www.luogu.com.cn/problem/CF1047B)

- [博客内查看](https://www.luogu.com.cn/blog/195198/solution-cf1047b)

## 思路

因为是在坐标轴上取等腰，所以只有 $x[i] = y[i]$ 的时候才可以。

那么这个时候就是一个等腰直角三角形。这个斜边是平行于 $y = -x$ 这条直线的，即 $y = -x + b$ 。如果想让这个点在三角形内部，我们至少要让这一个点在这条直线上。所以我们需要满足这里的 $y[i] = -x[i] + b[i]$ 。因为已知 $y[i], x[i]$ 所以我们得到 $b[i] = x[i] + y[i]$ 。

因为 $b[i]$ 是截距，而这个三角形又是要求是最小的等腰三角形。众所周知，斜边大于直角边。所以最小的边的长度就是直角边的长度，所以它的边长至少为 $b[i]$ 。

#### 具体来讲，就是这样：

---

$\because$ 在坐标轴上找等腰

$\therefore$ 必定有一个等腰直角三角形，其斜边为 $y = -x + b$ 。使得这个点在其内部。

$\because y[i] = -x[i] + b[i]$

$\therefore b[i] = x[i] + y[i]$

又 $\because$ 题目中要求 **最小至少**，最小为 $b[i]$

$\therefore \operatorname{maxn} = \max(b[i])$ （$\operatorname{maxn}$ 即至少）

---

实现起来很简单，用一个 ```maxn``` 每次对 $b[i]$（即 $x[i] + y[i]$） 取 $\max$ 即可。最后输出 ```maxn``` 。

时间复杂度 $O(n)$ 。$n \leq 10^5$，足以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int x,y,maxn=0,n;
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
		scanf("%d%d",&x,&y),maxn=max(x+y,maxn);
	printf("%d",maxn);
	return 0;
}
```

注：本人太弱，可能讲解会不太通顺和好理解，望读者谅解。

---

## 作者：zsc2003 (赞：1)

2018.9.21

codeforces CF1047B 【Cover Points】

题目大意：

给定n个点的左边，你需要求出一个腰长最短的等腰直角三角形(顶点为坐标轴原点)，是的所有点都在这个等腰直角三角形的内部或者边上。

思路：只需求出每个点的横纵坐标之和取一下max即可

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()//读入优化
{
	int r=0,s,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
int n,x,y,ans;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		x=read(),y=read();
		ans=max(ans,x+y);
	}//取max
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：xgwpp6710 (赞：0)

首先，我们发现所有的坐标都是正整数，因此都在第一象限。

因为在坐标轴上构造等腰三角形，而两条坐标轴是垂直的，那么它一定是等腰直角三角形？（位于第一象限）。

因此它的斜边解析式为 $x+y=l$ ， $l$ 为直角边长。

因为它要覆盖所有点，那么说明所有点的坐标 $(x,y)$ 都满足 $x+y≤l$ 。

然后就很好做了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,x[100009],y[100009],maxn=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
		maxn=max(maxn,x[i]+y[i]);
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：HoshizoraZ (赞：0)

题目翻译：

在坐标系中有 $n$ 个在第一象限的格点，第 $i$ 个点坐标为 $(x_i,y_i)$

如果有一条直线满足：

- 与 $x$ 轴、$y$ 轴围成了一个等腰三角形
- 所有点在该三角形内部或在该三角形上

求这条直线与两条坐标轴围成的等腰三角形腰长的最小值

-----------------------

这道题答案都知道，就在这里说一下为什么结果是最大的横纵坐标之和

设这条直线解析式为 $y=kx+b$

首先，这是个直角三角形，所以腰就是直角边，即在坐标轴上

所以我们可以推出该直线必定经过 $(0,b)$ 和 $(-\frac{b}{k},0)$ 两点

由于它们与原点距离相等，所以 $b=-\frac{b}{k}$（都在坐标正半轴，不需要绝对值），解得 $k=-1$

所以，直线解析式为 $y=-x+b$，那么三角形的腰长就是该直线与 $x$ 轴的截距，所以要求的答案等于 $b$

通过移项，可以得到 $b=x+y$

所以答案就是 $x+y$

当然，我们要求能包含所有点的结果的最小值，所以答案就是 $n$ 个点中最大的一组 $x+y$

---

