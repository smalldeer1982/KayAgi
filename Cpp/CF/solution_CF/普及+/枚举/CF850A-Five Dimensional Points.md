# Five Dimensional Points

## 题目描述

You are given set of $ n $ points in 5-dimensional space. The points are labeled from $ 1 $ to $ n $ . No two points coincide.

We will call point $ a $ bad if there are different points $ b $ and $ c $ , not equal to $ a $ , from the given set such that angle between vectors ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/0653dbc57091409c95cbdb75a14170af617d0442.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/bde2e95036e34134c1ea6bd6b9709d7dd49d1b09.png) is acute (i.e. strictly less than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/fe3c8011bb9ee15abb5ac0ee9f2f980eef59656c.png)). Otherwise, the point is called good.

The angle between vectors ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/5a3a683029365387cf086e592ebfccb0e126e88a.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/2c10c8fe0b4dfc279c1514830bc9fce0b1aa6b49.png) in 5-dimensional space is defined as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/d27dbfc0849680d0f326c5cde0af47140b2f6df3.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/0fea22328d6b3b4c1d11529ba4c9764cafce84d3.png) is the scalar product and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/f06b81b731bd497af38154f7447638a84ce787f2.png) is length of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/5a3a683029365387cf086e592ebfccb0e126e88a.png).

Given the list of points, print the indices of the good points in ascending order.

## 说明/提示

In the first sample, the first point forms exactly a ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/fe3c8011bb9ee15abb5ac0ee9f2f980eef59656c.png) angle with all other pairs of points, so it is good.

In the second sample, along the cd plane, we can see the points look as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/dc25f4e169ea69409034b12812dd7f4f82002152.png)

We can see that all angles here are acute, so no points are good.

## 样例 #1

### 输入

```
6
0 0 0 0 0
1 0 0 0 0
0 1 0 0 0
0 0 1 0 0
0 0 0 1 0
0 0 0 0 1
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
3
0 0 1 2 0
0 0 9 2 0
0 0 5 9 0
```

### 输出

```
0
```

# 题解

## 作者：Dementor (赞：7)

## T4 CF850A 五维点

[CF850A](http://codeforces.com/problemset/problem/850/A)

### 题解

这题是 **抽屉原理**

**发现当他的 $n$ 大于  $34$ 的时候是没有“好点”的。**

为什么呢？

首先，二维坐标有 $2$ 条坐标轴，三维坐标有 $3$ 条坐标轴，那么我们可以猜想四维、五维坐标有多少条坐标轴。

发现五维坐标有 $5$ 条坐标轴，然后知道每个坐标轴分 $+ and -$ 所以我们任意将一个点作为坐标原点，这样知道当 $n > 34$ 时一共有 $33$ 个其余的点。

**根据抽屉原理，这样就至少有一个象限分到两个点。**

然后如果真的有的话，那么无论如何当前这个坐标原点所对的点不能成为“好点”。

根据抽屉原理，**知道当 $n > 34$ 时答案永远是 $0$**。

然后就做完了，复杂度 $O (n ^ 3) ……$

代码的话可以参考下边的题解，我提供思路，谢谢大家~。

~~第一次写题解，求洛谷各位伟大的管理员通过~~

---

## 作者：封禁用户 (赞：6)

题意：当三个点相连后夹角小于90°，则为坏点，不然就为好点

这道题题目的5维空间还是很吓人的，还有什么向量。。。我这种小学生怎么会懂呢？

但是看懂了就很简单，暴力枚举三个点，计算是否为好点

==============================我是华丽丽的分割线================================

```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;
int a[maxn][10], good[maxn], tot, n;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 5; j++)
            scanf("%d", &a[i][j]);
    /*以下暴力部分可能会引起不适，4重循环，还好CF机子快*/
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j != i) {
                for (int k = j + 1; k <= n; k++) //直接从1开始枚举也不会超时，同为31ms...
                    if (k != i) {
                        int ans = 0;
                        for (int l = 1; l <= 5; l++)
                            ans += (a[j][l] - a[i][l]) * (a[k][l] - a[i][l]);
                        if (ans > 0)
                            goto nxt;
                    }
            }
        }
        good[++tot] = i;
        nxt:;
    }
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++)
        printf("%d\n", good[i]);
}
```
### 壮哉我大暴力

文中的goto可参照[这篇文章](https://baike.baidu.com/item/goto%E8%AF%AD%E5%8F%A5/7603004?fr=aladdin) or [This](https://en.wikipedia.org/wiki/Goto)

---

## 作者：Provence_24 (赞：3)

# 本题和5维没多大关系
~~要仔细思考一下~~
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
struct node{
	int a;
	int b;
	int c;
	int d;
	int e;
}point[1100];//一个结构体数组
bool judge[1100];
int n;
int main()
{
	scanf("%d", &n);
	if (n > 11){
		cout << 0 << endl;
		return 0;
	}
	for (int i=1; i<=n; i++)
	{
		scanf("%d", &point[i].a);
		scanf("%d", &point[i].b);
		scanf("%d", &point[i].c);
		scanf("%d", &point[i].d);
		scanf("%d", &point[i].e);
	}
	memset (judge, 0, sizeof (judge)); 
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=n; j++)
		{
			if (j == i) continue;
			for (int k=1; k<=n; k++)
			{
				if (k == i || k == j) continue;//三位循环枚举每维的数据
				node x, y;
				x.a = point[j].a - point[i].a;
				y.a = point[k].a - point[i].a;
				x.b = point[j].b - point[i].b;
				y.b = point[k].b - point[i].b;
				x.c = point[j].c - point[i].c;
				y.c = point[k].c - point[i].c;
				x.d = point[j].d - point[i].d;
				y.d = point[k].d - point[i].d;
				x.e = point[j].e - point[i].e;
			    y.e = point[k].e - point[i].e;
			    //按题目要求处理
			    if (x.a * y.a + x.b * y.b + x.c * y.c + x.d * y.d + x.e * y.e > 0) {
				   judge[i] = 1;
				   break;
				}
			}
		}
	}
	int sum = 0;
	for (int i=1; i<=n; i++)
	{
		if (judge[i] == 0) sum ++;
	}
	cout << sum << endl;
	for (int i=1; i<=n; i++)
	{
		if (judge[i] == 0) cout << i << " ";/。判好坏
	}
	return 0;
}
```
### 思考了很久
# 加油！！！

---

