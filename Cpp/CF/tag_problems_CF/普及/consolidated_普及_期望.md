---
title: "New Year Ratings Change"
layout: "post"
diff: 普及/提高-
pid: CF379C
tag: ['递推', '排序', '期望']
---

# New Year Ratings Change

## 题目描述

One very well-known internet resource site (let's call it X) has come up with a New Year adventure. Specifically, they decided to give ratings to all visitors.

There are $ n $ users on the site, for each user we know the rating value he wants to get as a New Year Present. We know that user $ i $ wants to get at least $ a_{i} $ rating units as a present.

The X site is administered by very creative and thrifty people. On the one hand, they want to give distinct ratings and on the other hand, the total sum of the ratings in the present must be as small as possible.

Help site X cope with the challenging task of rating distribution. Find the optimal distribution.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=3·10^{5}) $ — the number of users on the site. The next line contains integer sequence $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a sequence of integers $ b_{1},b_{2},...,b_{n} $ . Number $ b_{i} $ means that user $ i $ gets $ b_{i} $ of rating as a present. The printed sequence must meet the problem conditions.

If there are multiple optimal solutions, print any of them.

## 样例 #1

### 输入

```
3
5 1 1

```

### 输出

```
5 1 2

```

## 样例 #2

### 输入

```
1
1000000000

```

### 输出

```
1000000000

```



---

---
title: "Little Pony and Expected Maximum"
layout: "post"
diff: 普及/提高-
pid: CF453A
tag: ['动态规划 DP', '期望']
---

# Little Pony and Expected Maximum

## 题目描述

暮暮刚刚在和她的朋友——AJ（苹果杰克）、FS（小蝶）、RD（云宝黛西）玩Ludo游戏。但是她马品没攒够总是输。回到城堡过后，她对游戏用的骰子产生了兴趣。


这个骰子有M面：骰子的第一面有一个点，第二面有两个点，以此类推，第m面含有M点。暮暮确信的是，当掷骰子时，每一面都有1/m的可能性出现，并且每次投掷的概率都是都是独立的。请你帮助她计算掷N次骰子后每次得到的点数中最大值的期望。

## 输入格式

一行两个整数 m 和 n (1 ≤ m, n ≤ 10^5).

## 输出格式

输出一行一个实数，与答案误差不大于10^-4

## 样例 #1

### 输入

```
6 1

```

### 输出

```
3.500000000000

```

## 样例 #2

### 输入

```
6 3

```

### 输出

```
4.958333333333

```

## 样例 #3

### 输入

```
2 2

```

### 输出

```
1.750000000000

```



---

---
title: "Journey"
layout: "post"
diff: 普及/提高-
pid: CF839C
tag: ['数学', '概率论', '期望']
---

# Journey

## 题目描述

## 问题描述

在七大王国里有 $n$ 个城市和 $n-1$ 条道路，每条道路连接两个城市，并且通过这些道路我们可以从任何一个城市到达任何一个城市。

席恩和阿莎在第一个城市骑上马，他们要通过这些路开始一次旅行。但是有雾，所以他们看不见他们的马带他们去了哪里。当马抵达一个城市的时候（包括第一个城市），它会去跟当前这个城市相连的城市。但是这是一匹奇怪的马，它只去他们以前没有去过的城市。在每个城市，马以相同的概率移动去上述符合要求的城市，并且当没有这样的城市（可走）时，马就停下了。

每条路的长度都是 $1$，旅行从城市 $1$ 开始，问这次旅行的期望长度（旅行长度的期望值）是多少？你可以通过[这个链接](https://en.wikipedia.org/wiki/Expected\_value)来阅读一些关于期望（平均）值的文字。

## 输入格式

第一行包含一个整数 $n$（$1 \leq n \leq 100000$）——城市的数量。

下来是 $n-1$ 行，这些行中的第 $i$ 行包含两个整数 $u_i$ 和 $v_i$（$1 \leq u_i, v_i \leq n$，$u_i \not = v_i$）——第 $i$ 条边连接的城市。

保证通过这些道路可以从任何一个城市到达任何一个城市。

## 输出格式

输出一个数——这次旅行长度的期望值。旅行从城市 $1$ 开始。

当你的答案的绝对或相对误差不超过 $10^{-6}$ 时你的答案将会被接受。

换句话说，假定你的答案是 $a$，标准答案是 $b$，当 $\frac{|a-b|}{max(1,b)} \leq 10^{-6}$ 时你的答案将会被接受。

## 说明/提示

在第一个例子中，他们的旅行可能以同等的概率停止于城市 $3$ 或城市 $4$。去城市 $3$ 的距离是 $1$，去城市 $4$ 的距离是 $2$，所以期望是 $1.5$。

在第二个例子中，他们的旅行可能停止于城市 $4$ 或城市 $5$。去这些城市的距离都是 $2$，所以期望是 $2$。

## 样例 #1

### 输入

```
4
1 2
1 3
2 4

```

### 输出

```
1.500000000000000

```

## 样例 #2

### 输入

```
5
1 2
1 3
3 4
2 5

```

### 输出

```
2.000000000000000

```



---

