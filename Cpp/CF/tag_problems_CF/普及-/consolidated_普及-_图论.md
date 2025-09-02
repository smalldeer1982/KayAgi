---
title: "Destroying Bridges"
layout: "post"
diff: 普及-
pid: CF1944A
tag: ['图论']
---

# Destroying Bridges

## 题目描述

There are $ n $ islands, numbered $ 1, 2, \ldots, n $ . Initially, every pair of islands is connected by a bridge. Hence, there are a total of $ \frac{n (n - 1)}{2} $ bridges.

Everule lives on island $ 1 $ and enjoys visiting the other islands using bridges. Dominater has the power to destroy at most $ k $ bridges to minimize the number of islands that Everule can reach using (possibly multiple) bridges.

Find the minimum number of islands (including island $ 1 $ ) that Everule can visit if Dominater destroys bridges optimally.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first and only line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 100 $ , $ 0 \le k \le \frac{n \cdot (n - 1)}{2} $ ).

## 输出格式

For each test case, output the minimum number of islands that Everule can visit if Dominater destroys bridges optimally.

## 说明/提示

In the first test case, since no bridges can be destroyed, all the islands will be reachable.

In the second test case, you can destroy the bridge between islands $ 1 $ and $ 2 $ . Everule will not be able to visit island $ 2 $ but can still visit island $ 1 $ . Therefore, the total number of islands that Everule can visit is $ 1 $ .

In the third test case, Everule always has a way of reaching all islands despite what Dominater does. For example, if Dominater destroyed the bridge between islands $ 1 $ and $ 2 $ , Everule can still visit island $ 2 $ by traveling by $ 1 \to 3 \to 2 $ as the bridges between $ 1 $ and $ 3 $ , and between $ 3 $ and $ 2 $ are not destroyed.

In the fourth test case, you can destroy all bridges since $ k = \frac{n \cdot (n - 1)}{2} $ . Everule will be only able to visit $ 1 $ island (island $ 1 $ ).

## 样例 #1

### 输入

```
6
2 0
2 1
4 1
5 10
5 3
4 4
```

### 输出

```
2
1
4
1
5
1
```



---

---
title: "The Way to Home"
layout: "post"
diff: 普及-
pid: CF910A
tag: ['图论', '最短路']
---

# The Way to Home

## 题目描述

一只青蛙现在在一个数轴上，它现在要从点 $1$ 跳到点 $n$ ，它每次可以向右跳不超过 $d$ 个单位。比如，它可以从点 $x$ 跳到点 $x+a$  $( 1<=a<=d )$ 。特别的，青蛙只能在有百合花的点上停留。保证点 $1$ 和点 $n$ 之间有一些点有百合花。请输出青蛙到达点 $n$ 的最小跳跃次数。

## 输入格式

输入的第一行包括两个正整数 $n$ 和 $d$  $( 2<=n<=100, 1<=d<=n-1 )$ 。
输入的第二行是一个长度为 $n$ 的无空格字符串，由`0`和`1`组成，表示哪些点上有百合花（`1`表示有）。保证点 $1$ 和点 $n$ 有百合花。

## 输出格式

输出青蛙的最小跳跃次数。如果它不可能到达，输出-1。

## 输入输出样例
略

## 说明/提示

在样例1中，青蛙可以从点 $1$ 跳3个单位到点 $4$ ，再从点 $4$ 跳4个单位到点 $8$ .
在样例2中，青蛙不能到达点 $n$ ，因为它至少需要跳3个单位，但它最多只能跳2个单位。

由 @星烁晶熠辉 提供翻译

## 样例 #1

### 输入

```
8 4
10010101

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 2
1001

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
8 4
11100101

```

### 输出

```
3

```

## 样例 #4

### 输入

```
12 3
101111100101

```

### 输出

```
4

```



---

