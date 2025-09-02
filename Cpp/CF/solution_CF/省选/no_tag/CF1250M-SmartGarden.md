# SmartGarden

## 题目描述

Berland Gardeners United Inc. hired you for the project called "SmartGarden". The main feature of this project is automatic garden watering.

Formally the garden can be represented as a square of $ n \times n $ cells with rows numbered $ 1 $ to $ n $ from top to bottom and columns numbered $ 1 $ to $ n $ from left to right. Each cell of the garden contains either a plant or a slab.

It's known that slabs are located on the main diagonal of the matrix representing the garden, and in the cells that are below the main diagonal and share a side with at least one cell of the main diagonal. All the remaining cells of the garden are filled with plants.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1250M/920cff7b857d3b33730690cd330ac3e3f7380869.png)Example of the garden for $ n=5 $ .During implementation of the project you created a smart robot that takes a list of commands as an input, which are processed one by one. Each command contains:

- a list of horizontal lines (rows in the matrix representing the garden);
- a list of vertical lines (columns in the matrix representing the garden).

While executing each command robot waters only cells in the intersection of specified rows and specified columns. So, if you specify $ r $ rows and $ c $ columns, then exactly $ r \cdot c $ cells will be watered.

In the demo for the customer you have tuned robot in such a way that it waters all the garden. To do that you prepared a single command containing all $ n $ rows and all $ n $ columns.

Unfortunately, 5 hours before the demo for your customer it turned out that the CEO of Berland Gardeners United Inc. was going to take part in it. Moreover, most probably he will be standing on a garden slab during the demo!

Now you need to create a list of commands for the robot so that it waters all the plants and doesn't water any cell containing a slab. Since it's only a beta version of "SmartGarden", the total number of commands shouldn't exceed $ 50 $ .

Create a program that, for a given size of the garden, will find a list of no more than $ 50 $ commands that allow the robot to water all the plants in the garden without watering the slabs. It is allowed to water a plant several times.

## 样例 #1

### 输入

```
2```

### 输出

```
2
1 1
1 2
1 1
1 2
```

## 样例 #2

### 输入

```
4```

### 输出

```
4
2 1 4
1 2
2 1 2
2 3 4
1 3
2 1 4
1 4
1 1
```

# 题解

## 作者：NaOH_Frog (赞：2)

每次操作我们能选的坐标集合需要满足不存在一对 $x,y$ 使得 $0\le x-y\le 1$。

我们发现，钦定一个数 $p\ge 3$ 和一个 $0\le i\le p$ 那么我们一次可以选所有满足 $x\equiv i\pmod p$ 的 $x$ 和所有满足 $y\not\equiv i\pmod p,y\not\equiv i+1\pmod p$ 的 $y$。

那么，我们考虑钦定几个两两互质的 $p$，并且将所有可能的 $i$ 全部用一遍，会发现漏网之鱼非常少，只有模 $p$ 意义下不满足题目条件的点对不会被浇到。那么多取几个 $p$ 之后这些点应该会被筛的差不多。

自己写 checker 并且尝试（或者直接多次提交尝试）后，发现 $p$ 取 $\{5,7,8,9,19 \}$ 时可以通过本题。

---

## 作者：namelessgugugu (赞：1)

#### 题意

有一个 $n \times n$ 的 01 矩阵 $a$，初始时全为 $0$。

可以进行不超过 $50$ 次操作，每次操作选定集合 $S, T$，对于所有 $x \in S, y \in T$，将 $a_{x, y}$ 赋值为 $1$。

要求最后矩阵 $a$ 满足 $a_{x, y} = 1 - [y \leq x \leq y + 1]$。即矩阵中只有 $x = y$ 和 $x = y + 1$ 两条斜线上的位置为 $0$，其余地方都为 $1$。

$1 \leq n \leq 5000$。

#### 题解

$50$ 大概是 $k \log n$ 级别的数，可以考虑二进制分组。

考虑如果只要求斜线 $x = y$ 上的值为空（即限制等价于 $S \cap T = \emptyset$）的情况。

第 $k$ 次操作令 $S$ 为所有二进制下第 $k$ 位为 $0$ 的数，$T$ 为第 $k$ 位为 $1$ 的数。然后再把 $S, T$ 交换操作一次。这样需要 $2 \lceil \log_2 n \rceil$ 次操作。

再考虑斜线 $x = y + 1$ 上的也要为 $0$ 的情况。

类似之前的做法，跑 $\log n$ 轮操作。为了方便，要求对于数对 $(x, y)$，如果 $x, y$ 二进制下从高到低第一位不同是在第 $k$ 位，要求这个点一定要在第 $k$ 轮操作中被染成 $1$。

在第 $k$ 轮操作中，可以进行如下四次操作：

1. 仅考虑第 $k + 1$ 位是 $0$ 的数，把所有第 $k$ 位是 $0$ 的放进 $S$，是 $1$ 的放进 $T$；
2. 仅考虑第 $k + 1$ 位是 $1$ 的数，然后操作同上一步；
3. 把所有第 $k$ 位是 $1$ 的放进 $S$，其余的放进 $T$，但是删去所有 $T$ 中前 $k - 1$ 位都是 $1$ 的数；
4. 前半部分同上一步，删去的东西改为所有 $S$ 中前 $k - 1$ 位都是 $0$ 的数。

这四次操作中，前半解决了 $x < y$ 的情况，后半解决了 $x > y$ 的情况。如果不好理解可以把每一步的 $S$ 和 $T$ 写出来。

同时后半有一种等价写法：第三次先把第 $k$ 位是 $1$ 的放进 $S$，然后把所有剩下的，且加进去不会导致操作非法的放进 $T$，第四次类似。这是我代码中的写法。

看上去需要 $4\lceil \log_2 n \rceil = 52$ 次，但是 $k = 0$ 和 $k = 13$ 时其实可以各少两次，所以只需要 $48$ 次。

#### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <array>
const int N = 5005;
int n;
std::vector<std::array<std::vector<int>, 2>> res;
inline int dit(int x, int d)
{
	return (x >> d) & 1;
}
int main(void)
{
	scanf("%d", &n);
	for(int k = 0;(n >> k);++k)
		for(int o = 0;o < (1 << (k + 2));o += (1 << (k + 1)))
		{
			std::vector<int> vec[2];
			for(int i = o;i < n;i += (1 << (k + 2)))
			{
				for(int j = 0;j < (1 << k);++j)
				{
					if(i + j < n)
						vec[0].push_back(i + j);
					if(i + j + (1 << k) < n)
						vec[1].push_back(i + j + (1 << k));
				}
			}
			if(vec[0].size() && vec[1].size())
				res.push_back({vec[0], vec[1]});
		} 
	for(int k = 1;(n >> k);++k)
	{
		{
			std::vector<int> vec[2];
			for(int i = 0;i < n;++i)
				if(dit(i, k) == 1)
					vec[0].push_back(i);
			for(int i = 0;i < n;++i)
				if(dit(i, k) != 1 && dit(i + 1, k) != 1)
					vec[1].push_back(i);
			if(vec[0].size() && vec[1].size())
				res.push_back({vec[0], vec[1]}); 
		}
		{
			std::vector<int> vec[2];
			for(int i = 0;i < n;++i)
				if(dit(i, k) != 1)
					vec[1].push_back(i);
			for(int i = 0;i < n;++i)
				if(dit(i, k) == 1 && (i == 0 || dit(i - 1, k) == 1))
					vec[0].push_back(i);
			if(vec[0].size() && vec[1].size())
				res.push_back({vec[0], vec[1]}); 
		}
	}
	printf("%d\n", (int)res.size());
	for(auto opt : res)
		for(auto vec : opt)
		{
			printf("%d ", (int)vec.size());
			for(int x : vec)
				printf("%d ", x + 1);
			putchar('\n');
		}
	return 0;
}

```

---

