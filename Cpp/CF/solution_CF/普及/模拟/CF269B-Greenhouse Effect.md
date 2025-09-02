# Greenhouse Effect

## 题目描述

Emuskald is an avid horticulturist and owns the world's longest greenhouse — it is effectively infinite in length.

Over the years Emuskald has cultivated $ n $ plants in his greenhouse, of $ m $ different plant species numbered from 1 to $ m $ . His greenhouse is very narrow and can be viewed as an infinite line, with each plant occupying a single point on that line.

Emuskald has discovered that each species thrives at a different temperature, so he wants to arrange $ m-1 $ borders that would divide the greenhouse into $ m $ sections numbered from 1 to $ m $ from left to right with each section housing a single species. He is free to place the borders, but in the end all of the $ i $ -th species plants must reside in $ i $ -th section from the left.

Of course, it is not always possible to place the borders in such way, so Emuskald needs to replant some of his plants. He can remove each plant from its position and place it anywhere in the greenhouse (at any real coordinate) with no plant already in it. Since replanting is a lot of stress for the plants, help Emuskald find the minimum number of plants he has to replant to be able to place the borders.

## 说明/提示

In the first test case, Emuskald can replant the first plant to the right of the last plant, so the answer is 1.

In the second test case, the species are already in the correct order, so no replanting is needed.

## 样例 #1

### 输入

```
3 2
2 1
1 2.0
1 3.100
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 5.0
2 5.5
3 6.0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 3
1 14.284235
2 17.921382
1 20.328172
3 20.842331
1 25.790145
1 27.204125
```

### 输出

```
2
```

# 题解

## 作者：ZolaWatle (赞：3)

## CF269B 题解

稍加思考，题目可以简化为：给到每一株植物的品种以及其原位置的序列，要我们求出需要对植物进行多少次移位，使得序列的 $ \text{LIS} $ 长度为 $ n $，即使序列满足**非严格单调递增**（对于 $ \forall x_1,x_2 \in [1,n] $ 且 $ x_1<x_2 $，总有 $ a[x_1] \leq a[x_2] $）。

我们注意到，每株植物是有一个位置的。根据题意，**这个位置在数轴上**。这就代表着，当进行移动时，只用考虑被移动的植物，而不用考虑其它植物给它让位子。

这样的结论很容易证明。在数轴上，可以找到任意实数所在的位置。**数轴是无限可分割的**。

举个例子，有三株植物 $ A,B,C $，它们所在的位置分别是 $ 1,2,3 $，现在要将 $ A $ 移到 $ BC $ 之间，使序列满足最优子结构性质。如果限定在 $ Z $ 中，我们当然要让植物 $ C $ 给植物 $ A $ 让位；但这题位置的范围是 $ R $，而 $ 2 $ 和 $ 3 $ 之间有无穷多个实数。

有了以上思考，我们完全可以**忽略每株植物的位置**。

我们可以先求出原序列中满足非严格单调递增的子序列的长度，记为 $ len $。容易想到用一个基本得不能再基本的 $ \text{DP} $ ——**最长不下降子序列**求解：

边界：$ dp[i]=1, i\in [1,n] $

转移：$ dp[i]=max\{dp[i],dp[j]+1\}, i\in [2,n], j\in [1,i), a[i]>a[j] $

目标：$ max\{dp[i]\}, i\in [1,n] $

那么剩下的植株在一开始并不满足题目的要求，数量是 $ n-len $。

考虑如何移动。

根据以上的推论，我们容易得到：

对于 $ \forall x$，总能在 $ \forall k_1, k_2, a[k_1]<a[x]<a[k_2] $ 之间找到一个位置，供 $ x $ 移动。因此，对于每一株起始时并不满足题目要求的植物，**仅需要移动一次**。

则答案为 $ n-len $。

### 完整代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN=5001;
int n,m,LIS,a[MAXN],dp[MAXN];
double tmp;

int main()
{
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++)
	{
		scanf("%d%lf",&a[i],&tmp);
		dp[i]=1;
	}
	
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++)
			if(a[i]>=a[j])
				dp[i]=max(dp[i],dp[j]+1);
	
	for(int i=1;i<=n;i++)
		LIS=max(LIS,dp[i]);
	
	printf("%d",n-LIS);
	return 0;
}
```


---

## 作者：lotus_grow (赞：3)

###  题目大意：
给出 $N$ 个植物，每个植物都属于一个品种，共计 $m$ 个品种，分落在不同的位置上（在一个数轴上，而且数轴是**无限长度**的），保证读入的位置是按照**升序**读入的。

现在我们可以进行一个操作：取任意一个位置上的植物，移动到任意一个没有植物的位子上去。

问我们最少进行多少次操作，能够使得从左到右，是按照**品种升序**排列的（$1$ ~ $m$）（**单调不降**），而且每种植物都相邻。

### 思路
注意到题意中数轴是**无限长度**的，所以位置没有意义。

那我们要令这些植物的品种单调不降，就可以用贪心的方法，先求出读入的数列的最长不降子序列，然后将剩余的植物移动到子序列中与它品种相同的位置即可。

所以答案就是 $n-$最长不降子序列的长度

### 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

int n,m,ans;
int f[5001];
double t;

int main()
{
	scanf("%d%d",&n,&m);
	memset(f,0x3f,sizeof(f));
	for(int i=1,x;i<=n;i++) 
	{
		scanf("%d%lf",&x,&t);
		*upper_bound(f+1,f+n+1,x)=x;
	}
	ans=n+1-(lower_bound(f+1,f+n+1,0x3f3f3f3f)-f);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：black_trees (赞：2)

水题。
---

题目内容不用解释了吧。

我们知道这题数轴无限长度。

所以我们其实可以在 $\pi ,\sqrt{114514}$ 等等地方放东西。

那么。聪明的你，告诉我。

序列总长度（也就是已经全部排好的序列的长度），减去序列的最长不下降子序列的长度。和我们要求的解有什么区别呢？

所以 $O\ (\ n\log n)$ 和 $O\ ( \ n ^ 2 \ ) $求一下即可。

（因为数据水所以都可以过）

代码略。

---

upd:修改了错误的复杂度 & ~~手滑~~打反的句子。



---

## 作者：Miracle_ZX (赞：1)

### Part 0 前言
希望管理员大大能通过这篇文章 ya~

### Part 1 题意 + 分析

给出 $n$ 个植物，每个植物都属于一个品种，一共 $m$ 个品种，分别在**无限**长度的数轴的不同位置上），保证位置是按照**升序读入**的。

我们可以做的事情：取任意一个位置上的植物，移动到任意一个没有植物的位子上去。

问：最少进行多少次操作，能够使得数列，是按照品种单调不下降排列（而且植物还要相邻）。

我们可以考虑到大方向应该是 LIS，并且如果我们注意到了那个玄乎的 “无限长度”，我们应该就可以知道，位置其实根本不重要，因为空位是肯定够的，所以每个未排好序的植物只需要移动一次就可以到达确定的地点。于是我们可以放心大胆地向 LIS 方向考虑。

因为它要求最终的序列是不下降的，然而只需要调整那些影响了整个序列不下降的数，即 $n$ - 最长公共子序列的长度即可。

不知道 LIS 各种写法的同学：[这里有介绍，可以研究一下](https://blog.csdn.net/lxt_Lucia/article/details/81206439)，这里由于是不下降，代码稍微改一改即可。

思路简述：$dp[i] = \max(dp[i], dp[j] + 1) (a[i] >= a[j])$

### Part 2 Code
```cpp
#include <iostream>
#include <algorithm>
// 原谅用 VS Code 的我
using namespace std;

int dp[10000010];
int a[10000010];
double x;
//x 用来应付我们的长度
int n, m, maxn = -10000010;
int main()
{
	cin >> n >> m;
    //dp 数组初始化为 1 
	for(int i = 1; i <= n; ++i)
    {
        cin >> a[i] >> x;
    }
    //距离虽然没有什么用，但还是要输入
	for(int i = 1; i <= n; ++i)
    {
        dp[i] = 1;
		for(int j = 1; j < i; ++j) 
        {
            if(a[i] <= a[j] ) dp[i] = max(dp[i], dp[j] + 1);
        }
        //详情见文中链接的详细讲解
	}
    for(int i = 1; i <= n; ++i)
    {
        maxn = max(maxn, dp[i]);
	}
	cout << n - maxn;
	return 0;
}


```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF269B)

## 思路

首先需要了解一个数学思想：两个不相等的浮点数之间有无限个浮点数。

举个例子：

$1.0$ 和 $2.0$ 之间有没有数？当然有，$1.1,1.2,\dots,1.9$。

$1.1$ 和 $1.2$ 之间有没有数？当然有，$1.11,1.12,\dots,1.19$。

$1.11$ 和 $1.12$ 之间有没有数？当然有，$1.111,1.112,\dots,1.119$。

$\vdots \qquad \vdots \qquad \vdots \qquad \vdots \qquad \vdots \qquad \vdots \qquad \vdots \qquad \vdots \qquad \vdots \qquad \vdots \qquad \vdots$

所以有无数个。

所以只需要让品种不降就行了。

如果本来就不降那就不需要移动了，所以求出 `LIS` 就行了。 

## 代码

```cpp
// J2023 | BLuemoon_
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 5e3 + 5;

int n, m, ans, a[kMaxN], dp[kMaxN];
double x;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> x;
    dp[i] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (a[i] >= a[j]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
    ans = max(ans, dp[i]);
  }
  cout << n - ans << '\n';
  return 0;
}
```

---

## 作者：gesong (赞：0)

题目传送门：[CF269B](https://www.luogu.com.cn/problem/CF269B)。
# 思路
我们知道由于，数轴是**无线长度**的，所以我我怎么移动植物，怎么改变顺序都可以，因此我们输入的第二个数 $x_i$ 其实没有用，我们只要考虑把第一个数 $s_i$ 排成单调不降的即可。

于是我们把这道题想成了一道最长不下降序列的问题，因为 $x_i$ 已经排好序了。

这样我们考虑 **dp**。

**状态表示**：

$f_i$ 表示以 $i$ 结尾的最长不下降序列的长度。

**初始化**：

$f_i=1$ 自己就可以是不下降序列的一种。

**状态转移**：

我们考虑枚举我们算过的 $j$，得到此范围为 $1\le j\le i-1$ 我们判断如果 $s_j$ 可以成为 $f_i$ 的不下降序列，即 $s_j\le s_i$，我们就可以把他算进 $f_i$ 中，最后去一个最大值即可。

综上所述方程为：在满足 $1\le j\le i-1$ 且  $s_j\le s_i$,可以得到方程 $f_i=\max(f_i,f_j+1)$。

所以最后的答案为 $n-\max(f_i)$ 要把所有情况都考虑一遍。
# 代码

注意：本程序中把题目中的 $s_i$ 写成了 $a_i$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1234567],f[1234567];
main(){
	int n,m;
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		double x;
		cin>>a[i]>>x;
		f[i]=1;
	}
	for (int i=1;i<=n;i++)
		for (int j=i-1;j>0;j--)
			if (a[j]<=a[i]) f[i]=max(f[i],f[j]+1);
	int ans=0;
	for (int i=1;i<=n;i++) ans=max(ans,f[i]);
	cout <<n-ans;
    return 0;
}
```



---

## 作者：__JiCanDuck__ (赞：0)

这是一道比较水的dp ~~(我还错了一次)~~ 。

# 思路

想要种类单调不降（先不考虑位置），答案就是总数 $-$ 不需要移动的数量 ，那么就变成了 LCS 的模板。考虑位置，因为位置是实数，所以在任意两数之间有无数个位置，这道题还友好的告诉我们，位置是上升的，所以这道题就变成了标准的 LCS。

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxn = 5005;
int s[kMaxn], n, m, dp[kMaxn], ans;
double x[kMaxn];
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> s[i] >> x[i]; //虽然位置不重要，但还是友好的读了进来。
  }
  for (int i = 1; i <= n; i++) {
    dp[i] = 1;
    for (int j = 1; j < i; j++) {
      if (s[i] >= s[j]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
    ans = max(ans, dp[i]);
  }
  cout << n - ans; 
  return 0;
}

```

---

## 作者：FstAutoMaton (赞：0)

一道特水黄题。

众所周知两个数之间是有无数个数的（小数点可以保留任意位）。那么我们可以把题目转换为：给定 $n$ 个数，移动最少的数让数列变为严格上升的。不难想到，已经为上升的数不需要再去移动，那我们就尽肯能让上升的序列更长。可以发现其实就是求 ```LIS``` ( 最长上升子序列 )，那么只要求一遍  ```LIS``` 再用 $n$ 减去就可以得到答案了。代码如下：
```
#include <bits/stdc++.h>
using namespace std;
const int pty = 5005;
int n, a[pty], f[pty], ans, m;
double x;
int main()
{
    cin >> n >> m;
    for( int i = 1; i <= n; i ++ )
    {
        f[i] = 1;
        cin >> a[i];
        cin >> x;
        for( int j = 1; j < i; j ++ )
        {
            if( a[i] >= a[j] )
            {
                f[i] = max( f[i], f[j] + 1 );
            }
        }
        ans = max( ans, f[i] );
    }
    cout << n - ans << endl;
}
```


---

## 作者：Lee666666 (赞：0)

假设你已经找出了需要移动的那些植物，那么接下来要做的就是将那些植物插入到原有的按品种编号升序排列的序列中。**因为这道题所有的植物坐标都是实数，所以任意两株植物之间都能插入第三株植物。** 既然插入没有任何问题，那剩下的问题就是要找一个 **尽可能长的按品种编号升序排列的序列**（很明显这个序列越长移动的植物就越少）。

这个问题，就是最长不下降子序列问题，因为数据规模只是 $n \leq 5000$，所以只需要用简单的 DP 解决即可。

代码：

```cpp
#include <cstdio>
using namespace std;

inline int max(int a, int b) {
    return a > b ? a : b;
}

int n, m, ans, a[5015], f[5015];

int main(void) {
    scanf("%d %d", &n, &m);
    double pos;
    for (register int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        scanf("%lf", &pos);
        for (register int j = 1; j < i; j++) {
            if (a[i] >= a[j] && f[i] < f[j]) {
                f[i] = f[j];
            }
        }
        ans = max(ans, ++f[i]);
    }
    ans = n - ans;
    printf("%d", ans);
    return 0;
}


```

时间复杂度 $O(n^2)$，空间复杂度 $O(n)$。

---

## 作者：_Dreamer_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF269B)

由题面得到 数轴是**无限长度**的  那位置就没有什么意义了

那么我们可以把移动操作看作删除或修改

题面变为 给定一个序列最少修改多少次 单调不降

那么我们每次把所有相同品种的植物 移动到他对应的单调不降植物后面

那么我们的答案就是  $n-$ 最长不降序列长度 

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,m;
int f[5001];
int main()
{
	scanf("%d%d",&n,&m);
	memset(f,0x3f,sizeof f);
	for(int i=1;i<=n;i++)
	{
		int x;double pos;
		scanf("%d%lf",&x,&pos);
		*upper_bound(f+1,f+1+n,x)=x;
	}
	printf("%d",n+1-(lower_bound(f+1,f+1+n,0x3f3f3f3f)-f));
	return 0;
}

```

---

## 作者：L7_56 (赞：0)

### 首先需要注意是在数轴上的实数范围
也就是说任意两盆花之间都可以插得下一盆花

所以一盆花到达最终的位置只需要一步

最后的情况是升序排列

可以想象从原列中抽出一部分已经排好的序列

再把剩下的插入到序列里面

需要用的步数就是总个数减去序列最开始的长度

总个数是不变的，所以只需要找 $LIS$ 就可以了

### 代码
---
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define Nmx 5010
using namespace std;

int dp[Nmx];
struct node{
	double x;
	int l;
}a[Nmx];

int n,m,mxl;

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;++i)
	 scanf("%d%lf", &a[i].l, &a[i].x);
	for(int i=1;i<=n;++i){
		for(int j=1;j<i;++j){
			if(a[i].l>=a[j].l) dp[i]=max(dp[i],dp[j]);
		}
		mxl=max(mxl,++dp[i]);
	}
	printf("%d", n-mxl);
	return 0;
}

```

---

## 作者：Tyyyyyy (赞：0)

# 一道很水的dp
题目描述得很清楚了，仔细看样例可以发现位置是无限多的，所以位置是没有用的。我们只需要将他们的种类用最少的次数排成单调不降的序列即可。

**已知位置是无限多的**，那么**任意一个**位置都是我们可以移动植物的。也就是说：

**要保证所有植物的种类单调不减，我们不需要移动原来已经排好的植物。**

由于空位是一定够的，只需要移动原来没有排好序的植物即可。

所以先找原来已经排好的植物：求一个最长不降子序列。$dp$方程非常简单：

$dp[i]=max(dp[i],dp[j]+1)(p[i]>=p[j])$

再想一想，空位一定足够，所以每个未排好序的植物**只需要移动一次**就可以到达确定的，可排好序的位置。

因此，最终答案就是序列总长度减去最长不降子序列的长度。

AC代码如下：
```cpp
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
int n,m,ans;
int p[5100];
double x[5100];
int dp[5100];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%lf",&p[i],&x[i]);
	dp[1]=1;
	for(int i=2;i<=n;i++)
	{
		dp[i]=1;
		for(int j=1;j<i;j++)if(p[i]>=p[j])dp[i]=max(dp[i],dp[j]+1);
	}
	for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
	printf("%d",n-ans);
	return 0;
}
```

---

