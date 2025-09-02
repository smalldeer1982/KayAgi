# Power Transmission (Easy Edition)

## 题目描述

This problem is same as the next one, but has smaller constraints.

It was a Sunday morning when the three friends Selena, Shiro and Katie decided to have a trip to the nearby power station (do not try this at home). After arriving at the power station, the cats got impressed with a large power transmission system consisting of many chimneys, electric poles, and wires. Since they are cats, they found those things gigantic.

At the entrance of the station, there is a map describing the complicated wiring system. Selena is the best at math among three friends. He decided to draw the map on the Cartesian plane. Each pole is now a point at some coordinates $ (x_i, y_i) $ . Since every pole is different, all of the points representing these poles are distinct. Also, every two poles are connected with each other by wires. A wire is a straight line on the plane infinite in both directions. If there are more than two poles lying on the same line, they are connected by a single common wire.

Selena thinks, that whenever two different electric wires intersect, they may interfere with each other and cause damage. So he wonders, how many pairs are intersecting? Could you help him with this problem?

## 说明/提示

In the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/2317b27306c4c65175012212cdceb02039be0972.png)In the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/0792ee139dbdc603551bd0c872a1bea92551eac5.png)Note that the three poles $ (0, 0) $ , $ (0, 2) $ and $ (0, 4) $ are connected by a single wire.

In the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/9e20f52f47cf7b9d491a8675d81506c0f862a971.png)

## 样例 #1

### 输入

```
4
0 0
1 1
0 3
1 2
```

### 输出

```
14
```

## 样例 #2

### 输入

```
4
0 0
0 2
0 4
2 0
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3
-1 -1
1 0
3 1
```

### 输出

```
0
```

# 题解

## 作者：FFTotoro (赞：2)

## 前言

再没见过这么水的 $*1900$ 了……

附：做完这题可以去做一下 [[ABC248E] K-colinear Line](https://www.luogu.com.cn/problem/AT_abc248_e)。

## 解法

首先，两条直线如果能相交，那么它们的斜率必然不相等。

所以，我们只需要枚举每两个点，然后将经过它们的直线的斜率存进一个 `std::vector`，最后直线两两再枚举判断斜率是否相等即可。

但是，本题需要处理三点共线。

我们首先需要一个判断三点共线的函数；利用相似三角形的原理即可。

```cpp
bool pd(int a,int b,int c){
    return (ay[b]-ay[a])*(ax[c]-ax[a])==(ax[b]-ax[a])*(ay[c]-ay[a]);
}
```

每次枚举两个点的时候，就把其他所有点都扫一遍，每遇到一个新的点，如果它与原始的两个点贡献，那么将它装入数组 $v$。最后给 $v$ 中的数两两打上标记，下次再枚举到就可以直接跳过。

放代码：

```cpp
#include<bits/stdc++.h>
#define st first
#define nd second
using namespace std;
typedef pair<int,int> pii;
bool pd(pii a,pii b,pii c){
  return (b.nd-a.nd)*(c.st-a.st)==(b.st-a.st)*(c.nd-a.nd);
} // 判断函数
int main(){
  ios::sync_with_stdio(false);
  int n,c=0; cin>>n;
  vector<pii> a(n),d;
  vector<vector<bool> > b(n,vector<bool>(n));
  for(auto &[x,y]:a)cin>>x>>y;
  for(int i=0;i<n-1;i++)
    for(int j=i+1;j<n;j++){
      if(b[i][j])continue;
      vector<int> v={i,j};
      for(int k=j+1;k<n;k++)
        if(pd(a[i],a[j],a[k]))v.emplace_back(k); // 统计三点共线
      for(auto &i:v)for(auto &j:v)b[i][j]=true; // 打标记
      d.emplace_back(a[i].st-a[j].st,a[i].nd-a[j].nd);
    }
  for(auto &i:d)for(auto &j:d)
    c+=(i.st*j.nd!=i.nd*j.st); // 枚举斜率不相同的直线有多少对
  cout<<(c>>1)<<endl; // 每两个点统计了两遍，最终答案需要除以二
  return 0;
}
```

---

## 作者：Rosmarinus (赞：0)

[更好的阅读体验](https://www.cnblogs.com/XJ21/p/14666509.html)

## 题意描述

平面上有 $n$ 个点，每两个点之间有一条**直线**，求有多少对直线相交。

注意：

- 若有多条直线完全重合，则他们都算是同一条一条直线；
- 求的是有多少对直线相交，而不是有多少个交点。

## 思路分析

一条直线可以表现为：$y=kx+b$。

由初中知识可得：

- 两条直线不是相交就是平行；
- 平行 $\Leftrightarrow$ $k$ 相等。

因此，题目就可以转化为：有多少对直线的 $k$ 不相等。

## 方法解析

### 如何求 $k$

由初中知识得：

- $k$ 即为斜率；
- 斜率 $=$ 纵坐标之差 $\div$ 横坐标之差。

具体地，若有两个点 $a,b$，则 $k=(x_a-x_b)\div(y_a-y_b)$。

另外，由于 $(x_a-x_b)\div(y_a-y_b)=(x_b-x_a)\div(y_b-y_a)$，因此 $k$ 与 $a,b$ 两点的相对位置无关，即**无需考虑 $a,b$ 之间的位置关系，直接算就好**。

接下来考虑一个问题：$k$ 不一定是整数，而此题要求比较两个 $k$ 是否严格相等，使用 `double` 大概率会碰上精度的问题—— 比如$\frac{1}{9999}$ 与 $\frac{1}{10000}$，因此我们考虑以下算法：

定义两个变量 $k\_son$ 与 $k\_mom$，分别表示 $k$ 的分子与分母，那么 $k$ 便可以表示为 $\frac{k\_son}{k\_mom}$，我们只要把 $k$ 约分，那么便可以通过 $k\_son$ 与 $k\_mom$ 精准表示每一个 $k$。

----------

**注意点：**

- 由于我们直接计算 $k$，可能会出现 $k=\frac{-1}{2}$ 与 $k=\frac{1}{-2}$ 的情况，它们两个是同一个 $k$ 但是 $k\_son$ 与 $k\_mom$ 并不相等。因此我们应该维护 $k\_mom$ 恒大于 $0$，这样子就不会在比较时出现问题；
- 当直线平行于 $y$ 轴时，我们可以令 $k\_son=1,k\_mom=0$，与其他直线区分开来；
- 当直线平行于 $x$ 轴时，我们应当令 $k\_son=k\_mom=0$，防止出现类似于 $\frac{0}{1}\neq\frac{0}{2}$的问题。

---------------

### 关于 $b$

$b$ 能用来干什么？$b$ 能用来判重合的直线。

由于我们能通过 $y=kx+b$ 精准表示每一条直线，因此只要两条直线的 $k,b$ 都相等，它们就是同一条直线。

$b=y-kx$，由于 $k$ 被我们用分数表示，我们可通过先通分，再约分的流程求出 $b$。

**但是！由于本人太菜了在写题解的时候才想到了这个方法，因此我们再说说另一个办法！**

-------------
### 如何判重

显然我们可以用 $k,b$ 判重，但是我们现在来考虑另一种做法。

我们回到初中数学，如下图：

[![cWayqK.png](https://z3.ax1x.com/2021/04/16/cWayqK.png)](https://imgtu.com/i/cWayqK)

如何判断三点共线？

$\because AB//BC$

$\therefore A,B,C$ 共线

相信你的数学老师是不会给你错的！

如果用人话讲就是：若两条平行线段有公共端点，那么它们共线。

带入到题目中，由于题目每两个点直接都连一条直线的性质，若是我们把直线变为线段，那么一条线段一定和另一条与它共线的线段有公共端点（如果有的话）。

我们定义 $x_i, y_i$ 表示 $i$ 号直线的两个原端点，如果有两条直线有一个原端点重合并且这两条直线平行，那么它们共线。

我们可以用`dfs`来解决此问题。

## AC代码

说了这么多，上代码！

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;

const int N = 51;
struct Node
{
    int k_mom, k_son, x, y;
}line[1000000];

struct Spot
{
    int x, y;
}a[1000000];

bool z[1000000];
int len;

int gcd(int a, int b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}

void dfs(int u)//dfs判重
{
	z[u] = true;
	for(int i = 1; i <= len; i ++)
	{
		if(!z[i] && (line[i].x == line[u].x || line[i].x == line[u].y || line[i].y == line[u].y || line[i].y == line[u].x) && line[i].k_son == line[u].k_son && line[i].k_mom == line[u].k_mom)
		{
			dfs(i);
		}
	}
}

int main()
{
    int n, x, y, x1, y1, ans = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d %d", &a[i].x, &a[i].y);
    }

    for(int i = 1; i <= n; i ++)//生成直线
    {
        if(z[i]) continue;
        for(int p = 1; p < i; p ++)
        {
            if(z[p] || (a[i].x == a[p].x && a[i].y == a[p].y)) continue;

            if(a[i].x == a[p].x)
            {
                line[++ len].k_son = 0;
                line[len].k_mom = 0;
                line[len].x = i, line[len].y = p;
            }
            else if(a[i].y == a[p].y)
            {
                line[++ len].k_son = 1;
                line[len].k_mom = 0;
                line[len].x = i, line[len].y = p;
            }
            else
            {
                x = a[i].x - a[p].x, y = a[i].y - a[p].y;
                line[ ++ len].k_son = x / gcd(abs(x), abs(y));
                line[len].k_mom = y / gcd(abs(x), abs(y));
                line[len].x = i, line[len].y = p;

				if(line[len].k_mom < 0)//维护k_mom恒大于0
				{
					line[len].k_mom *= -1;
					line[len].k_son *= -1;
				}
            }
        }
    }

    for(int i = 1; i <= len; i ++)//判重
    {
    	if(!z[i])
		{
			dfs(i);
			z[i] = false;
		}
	}
	
    for(int i = 1; i <= len; i ++)//计算答案
    {
    	if(z[i]) continue;
        for(int p = 1; p < i; p ++)
        {
        	if(z[p]) continue;
            if(line[i].k_mom != line[p].k_mom || line[i].k_son != line[p].k_son)
            {
                ans ++;
            }
        }
    }
	
    cout << ans << endl;

    return 0;
}
```

---

