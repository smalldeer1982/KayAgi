# Crosses

## 题目描述

There is a board with a grid consisting of $ n $ rows and $ m $ columns, the rows are numbered from $ 1 $ from top to bottom and the columns are numbered from $ 1 $ from left to right. In this grid we will denote the cell that lies on row number $ i $ and column number $ j $ as $ (i,j) $ .

A group of six numbers $ (a,b,c,d,x_{0},y_{0}) $ , where $ 0<=a,b,c,d $ , is a cross, and there is a set of cells that are assigned to it. Cell $ (x,y) $ belongs to this set if at least one of two conditions are fulfilled:

- $ |x_{0}-x|<=a $ and $ |y_{0}-y|<=b $
- $ |x_{0}-x|<=c $ and $ |y_{0}-y|<=d $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF215C/dd0bbfd77b0898ccae3538243b533d554266bc68.png) The picture shows the cross $ (0,1,1,0,2,3) $ on the grid $ 3×4 $ . Your task is to find the number of different groups of six numbers, $ (a,b,c,d,x_{0},y_{0}) $ that determine the crosses of an area equal to $ s $ , which are placed entirely on the grid. The cross is placed entirely on the grid, if any of its cells is in the range of the grid (that is for each cell $ (x,y) $ of the cross $ 1<=x<=n; 1<=y<=m $ holds). The area of the cross is the number of cells it has.

Note that two crosses are considered distinct if the ordered groups of six numbers that denote them are distinct, even if these crosses coincide as sets of points.

## 说明/提示

In the first sample the sought groups of six numbers are: $ (0,0,0,0,1,1) $ , $ (0,0,0,0,1,2) $ , $ (0,0,0,0,2,1) $ , $ (0,0,0,0,2,2) $ .

In the second sample the sought groups of six numbers are: $ (0,1,1,0,2,2) $ , $ (0,1,1,0,2,3) $ , $ (1,0,0,1,2,2) $ , $ (1,0,0,1,2,3) $ .

## 样例 #1

### 输入

```
2 2 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4 5
```

### 输出

```
4
```

# 题解

## 作者：minecraft_herobrine (赞：3)

### 翻译

有一个 $n\times m$ 的矩阵

我们用一个六元组 $(a,b,c,d,x0,y0)$ 表示一个十字形：

若一个方格 $(x,y)$ 满足下面两个条件之一，则这个方格属于这个六元组表示的十字形

- $|x-x0|\le a$ 且 $|y-y0|\le b$
- $|x-x0|\le c$ 且 $|y-y0|\le d$

已知一个十字形的面积是 $s$，问有多少个六元组满足要求

### 题解

翻译题目中的两个条件：

$x$ 到 $x0$ 的距离不超过 $a$ 且 $y$ 到 $y0$ 的距离不超过 $b$

或

$x$ 到 $x0$ 的距离不超过 $c$ 且 $y$ 到 $y0$ 的距离不超过 $d$

而这两个条件其实是分别表示了一个矩形再将这两个矩形取并集而形成的十字型。

![](https://cdn.luogu.com.cn/upload/image_hosting/77pcfl1u.png)

这是一个由 $(2,1,0,2,5,5)$ 表示的十字形，其中 $2,1$ 两个数生成了红色的矩形，$0,2$ 生成了蓝色矩形，紫色是重叠部分，黑色是十字的“中心点”。

定义条件中的 $|x-x0|$ 和 $|y-y0|$ 叫做 $xy$ 坐标的“偏移值”，设某一个“偏移值”为 $k$，则显然发现 $x(y)$ 坐标的取值范围是 $x0-k\le x(y)\le x0+k$ 这个范围显然有 $2k+1$ 个整数，所以，任何单个的条件表示的矩形长宽一定都是奇数。

对了，一个矩形也可以是一个十字形，比如六元组 $(1,1,0,0,4,4)$ 就表示一个以 $(4,4)$ 为中心点，大小为 $3\times 3$ 的矩形，而且十字形不能有任何一个格子在矩阵外边

注意到 $n,m$ 最多只有 $500$ ，所以我们可以暴力枚举矩形的长宽 $i,j$，看一下这个矩阵的面积是否恰好等于 $s$，分类讨论：

- 等于 $s$

那就直接看一下整个大矩阵里有多少个 $i\times j$ 的小矩阵并累加进答案。这可以用一个函数计算：

```cpp
ll F(ll x,ll y)
{
	return (n-x+1)*(m-y+1);
}
```


- 不等于 $s$

看一下需要在这个矩形左右两侧**或**上下两侧“补”多少格子

能否补，必须看剩下的面积是否是偶数，因为十字形是轴对称的，如果你左右或上下两侧不对称的话就不是十字形了。


再枚举一个 $k$，要求 $k$ 必须能整除剩下的面积，并且补的部分不能超出矩形的边界。

综上，由于只要六元组中表示中心点的参数(x0,y0)不相同，算作多种方案，所以第二种情况也需要乘以 $F(i,j)$

### code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
ll F(ll x,ll y)
{
	return (n-x+1)*(m-y+1);
}
int main()
{
	ll s,i,j,k,res=0;
	scanf("%lld %lld %lld",&n,&m,&s);
	for(i=1;i<=n;i+=2)
	{
		for(j=1;j<=m;j+=2)
		{
			ll s0=i*j;
			if(s0==s) res+=(((i-1)/2+1)*((j-1)/2+1)*2-1)*F(i,j);
			else if(s0<s)
			{
				s0=s-s0;
				for(k=1;k<j;k+=2)
					if(!(s0&1) && s0%k==0 && i+s0/k<=n) res+=2*F(i+s0/k,j);
			}
		}
	}
	printf("%lld",res);
	return 0;
}
```


---

## 作者：ShwStone (赞：0)

## 题面描述

题中所给的“十字”的定义不太好懂，翻译一下，一个十字其实是两个矩形的叠加。第一个矩形长宽分别为 $2a+1,2b+1$，第二个矩形长宽分别为 $2c+1,2d+1$，且这两个矩形的中心点都在 $(x0,y0)$。另外，题中有一点说的不清楚，就是“十字”不能超过矩阵的限制，整个“十字”都应该在 $n \times m$ 的矩阵范围内。

求的是有多少“十字”大小正好为 $s$。

## 解题思路

由上面的题面描述，我们可以知道：“十字”的大小只和 $a,b,c,d$ 有关。如果设大小为 $size$，具体的计算公式为：

$$
size=(2a+1)(2b+1)+(2c+1)(2d+1)-\min(2a+1,2c+1)\times \min(2b+1,2d+1)
$$

首先想到的是枚举。枚举什么呢？如果枚举 $(x0,y0)$ ，剩下的 $a,b,c,d$ 不好枚，并且难以判断是否等于 $s$。

所以我们枚举 $a,b,c,d$，并保证这个形状的十字大小为 $s$，再计算这样的十字能放在多少个不同的地方。

但是如果枚举四个变量一定会超时，所以我们可以枚举前三个，然后计算出能使十字大小为 $s$ 的那个 $d$。

具体怎么计算呢？

显然，当 $a,b,c$ 都确定时，随着 $d$ 的增大，十字的大小是单调递增的。考虑到这个单调性，我们就可以二分找到符合条件的 $d$。

对应的代码如下：

```cpp
for (int a = 0; a <= ((n - 1) >> 1); a++) {
    for (int b = 0; b <= ((m - 1) >> 1); b++) {
        for (int c = 0; c <= ((n - 1) >> 1); c++) {
            int l = 0, r = ((m - 1) >> 1), mid;
            while (l < r) {
                mid = (l + r) >> 1;
                if (calc(a, b, c, mid) < s) l = mid + 1;
                else r = mid;
            }
            if (calc(a, b, c, l) == s) { // calc是上文提到的计算方法
                int ta = (max(a, c) << 1) + 1, tb = (max(b, l) << 1) + 1;
                ans += (n - ta + 1) * (m - tb + 1);
            }
        }
    }
}
```

但是这一段代码是有漏洞的：当 $c,d$ 对应的矩阵被 $a,b$ 对应的矩阵完全包含的时候，其实是有多个 $d$ 符合题意的（因为较小的矩阵被覆盖了，不管是什么形状，最终只看大矩阵的大小）。所以要做一个修改：当 $c\le a$ 时，$d$ 应该有 $\max(d,b)-d+1$ 种取法。且这些取法最终看上去都是一样的，所以对答案的贡献都是相同的。

修改后的计算贡献如下：

```cpp
ans += (n - ta + 1) * (m - tb + 1) * (c <= a ? (max(b, l) - l + 1) : 1);
```

完整的代码几乎都出来了，所以就不放了。

---

