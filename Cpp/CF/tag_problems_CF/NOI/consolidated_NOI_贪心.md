---
title: "378QAQ and Core"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1975H
tag: ['贪心']
---

# 378QAQ and Core

## 题目描述

378QAQ has a string $ s $ of length $ n $ . Define the core of a string as the substring $ ^\dagger $ with maximum lexicographic $ ^\ddagger $ order.

For example, the core of " $ \mathtt{bazoka} $ " is " $ \mathtt{zoka} $ ", and the core of " $ \mathtt{aaa} $ " is " $ \mathtt{aaa} $ ".

378QAQ wants to rearrange the string $ s $ so that the core is lexicographically minimum. Find the lexicographically minimum possible core over all rearrangements of $ s $ .

 $ ^\dagger $ A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, " $ \mathtt{defor} $ ", " $ \mathtt{code} $ " and " $ \mathtt{o} $ " are all substrings of " $ \mathtt{codeforces} $ " while " $ \mathtt{codes} $ " and " $ \mathtt{aaa} $ " are not.

 $ ^\ddagger $ A string $ p $ is lexicographically smaller than a string $ q $ if and only if one of the following holds:

- $ p $ is a prefix of $ q $ , but $ p \ne q $ ; or
- in the first position where $ p $ and $ q $ differ, the string $ p $ has a smaller element than the corresponding element in $ q $ (when compared by their ASCII code).

For example, " $ \mathtt{code} $ " and " $ \mathtt{coda} $ " are both lexicographically smaller than " $ \mathtt{codeforces} $ " while " $ \mathtt{codeforceston} $ " and " $ \mathtt{z} $ " are not.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 10^5 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\leq n\leq 10^6 $ ) — the length of string $ s $ .

The next line of each test case contains the string $ s $ of length $ n $ . The string $ s $ consists of lowercase English letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output the lexicographically minimum possible core over all rearrangements of $ s $ .

## 说明/提示

In the first test case, all possible rearrangements and their corresponding cores are as follows:

- " $ \mathtt{qaq} $ ", its core is " $ \mathtt{qaq} $ ".
- " $ \mathtt{aqq} $ ", its core is " $ \mathtt{qq} $ ".
- " $ \mathtt{qqa} $ ", its core is " $ \mathtt{qqa} $ ".

So the core with the minimum lexicographic order in all rearrangement plans is " $ \mathtt{qaq} $ ".

## 样例 #1

### 输入

```
6
3
qaq
4
cccc
6
bazoka
6
zazzzz
7
ababbbb
7
ccbabcc
```

### 输出

```
qaq
cccc
z
zzz
bbababb
cbcacbc
```



---

---
title: "Game in Tree (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2013F2
tag: ['贪心', '线段树', '根号分治']
---

# Game in Tree (Hard Version)

## 题目描述

这是问题的困难版本。在这一版本中，不要求 $u = v$。只有当两个版本的问题都成功解决后，你才能进行 hack。

Alice 和 Bob 在一棵树上玩一个有趣的游戏。这棵树有 $n$ 个顶点，编号从 $1$ 到 $n$。回顾一下，一棵有 $n$ 个顶点的树是一个有 $n - 1$ 条边的无向连通图。

游戏规则是 Alice 和 Bob 轮流移动，Alice 先行动，每位玩家在自己的回合中，必须从当前所在的顶点移动到一个尚未被访问过的相邻顶点。如果某个玩家无法移动，则他输掉比赛。

给定两个顶点 $u$ 和 $v$。从顶点 $u$ 到顶点 $v$ 的简单路径用数组表示为 $p_1, p_2, p_3, \ldots, p_m$，其中 $p_1 = u$，$p_m = v$，并且每对相邻的顶点 $p_i$ 和 $p_{i+1}$之间都有一条边（$1 \le i < m$）。

你的任务是，判断在 Alice 从顶点 $1$ 开始，而 Bob 从路径中的顶点 $p_j$（$1 \le j \le m$）开始的情况下，谁将获胜。

## 输入格式

输入包含多个测试用例。第一行为测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来每个测试用例进行描述。

每个测试用例的第一行是一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示树中顶点的个数。

接下来的 $n - 1$ 行，每行包含两个整数 $a$ 和 $b$（$1 \le a, b \le n$），表示顶点 $a$ 和 $b$ 之间连接着一条无向边。这些边保证组成一棵树。

测试用例的最后一行包含两个整数 $u$ 和 $v$（$2 \le u, v \le n$），保证从 $u$ 到 $v$ 的路径不通过顶点 $1$。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $m$ 行。

在第 $i$ 行输出结果，如果 Alice 从顶点 $1$ 开始而 Bob 从顶点 $p_i$ 开始时，游戏的赢家是谁。如果 Alice 赢，则输出“Alice”；否则输出“Bob”。

## 说明/提示

在第一个例子中，路径是（$2, 3$）。如果 Bob 开始时位于顶点 $2$，Alice 在第一回合就无法移动，只能输掉比赛。而如果 Bob 从顶点 $3$ 开始，Alice 会移动到顶点 $2$，此时 Bob 就没有顶点可动并会输掉比赛。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3
1 2
2 3
2 3
6
1 2
1 3
2 4
2 5
1 6
4 5
4
1 2
1 3
2 4
2 4
```

### 输出

```
Bob
Alice
Alice
Bob
Alice
Bob
Alice
```



---

---
title: "Complex Segments (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2018E1
tag: ['贪心', '根号分治']
---

# Complex Segments (Easy Version)

## 题目描述

这是这个问题的简单版本。在这个版本中， $n$ 的范围和时间限制都较低。

当一个区间的集合可以被分割成一些子集并满足以下条件时，这个集合是复杂的：

- 所有的子集的大小相同
- 当且仅当两个区间在同一子集内时，这两个区间相交。

$t$ 组数据，每组数据给你一个集合包含 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]$。求出最大的子集满足其为复杂的，输出这个集合的大小。

## 输入格式

第一行输入数据个数 $t(1 \le t \le 10^3)$。

每个数据的第一行包含一个整数 $n(1 \le n \le 2 \cdot 10^4)$，集合的区间个数。

每个数据的第二行包含 $n$ 个整数 $l_1, l_2, \ldots, l_n(1 \le l_i \le 2n)$，分别表示这 $n$ 个区间的左端点。

每个数据的第三行包含 $n$ 个整数 $r_1, r_2, \ldots, r_n(l_i \leq r_i \le 2n)$，分别表示这 $n$ 个区间的右端点。

保证所有数据 $n$ 的总和不超过 $2 \cdot 10^4$。

## 输出格式

对于每个数据输出一行表示最大的复杂的子集的大小。

## 样例 #1

### 输入

```
3
3
1 2 3
5 4 6
5
1 2 3 6 8
5 4 7 9 10
5
3 1 4 1 5
7 2 6 5 10
```

### 输出

```
3
4
4
```



---

---
title: "Complex Segments (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2018E2
tag: ['贪心', '分治']
---

# Complex Segments (Hard Version)

## 题目描述

这是这个问题的困难版本。在这个版本中， $n$ 的范围和时间限制都变高了。

当一个区间的集合可以被分割成一些子集并满足以下条件时，这个集合是复杂的：

- 所有的子集的大小相同
- 当且仅当两个区间在同一子集内时，这两个区间相交。

$t$ 组数据，每组数据给你一个集合包含 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]$。求出最大的子集满足其为复杂的，输出这个集合的大小。

## 输入格式

第一行输入数据个数 $t(1 \le t \le 10^3)$。

每个数据的第一行包含一个整数 $n(1 \le n \le 3 \cdot 10^5)$，集合的区间个数。

每个数据的第二行包含 $n$ 个整数 $l_1, l_2, \ldots, l_n(1 \le l_i \le 2n)$，分别表示这 $n$ 个区间的左端点。

每个数据的第三行包含 $n$ 个整数 $r_1, r_2, \ldots, r_n(l_i \leq r_i \le 2n)$，分别表示这 $n$ 个区间的右端点。

保证所有数据 $n$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个数据输出一行表示最大的复杂的子集的大小。

## 样例 #1

### 输入

```
3
3
1 2 3
5 4 6
5
1 2 3 6 8
5 4 7 9 10
5
3 1 4 1 5
7 2 6 5 10
```

### 输出

```
3
4
4
```



---

---
title: "Tree of Life"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2023E
tag: ['贪心']
---

# Tree of Life

## 题目描述

在一个古老王国的中心，生长着传奇的生命之树——这是独一无二的存在，也是整个世界魔法力量的源泉。该树由 $ n $ 个节点组成，树的每个节点都是一个魔法源，通过魔法通道（边）连接到其他这样的源。树中总共有 $ n-1 $ 条通道，第 $ i $ 条通道连接节点 $ v_i $ 和 $ u_i $。此外，树中任意两个节点之间存在一条唯一的简单路径。

然而，这些通道中流动的魔法能量必须保持平衡；否则，生命之树的力量可能扰乱自然秩序，造成灾难性的后果。王国的智者们发现，当两条魔法通道汇聚到一个节点时，会在它们之间产生一种危险的“魔法共振振动”。为了保护生命之树并维持其平衡，必须选择几条路径并沿着它们进行特殊的仪式。路径是一个由不同节点 $ v_1, v_2, \ldots, v_k $ 组成的序列，其中每一对相邻节点 $ v_i $ 和 $ v_{i+1} $ 由一条通道连接。当智者们沿着这样的路径进行仪式时，对于每个 $ 1 \leq i \leq k - 2 $，通道 $ (v_i, v_{i+1}) $ 和 $ (v_{i+1}, v_{i+2}) $ 之间的共振振动会被阻断。

智者们的任务是选择最少数量的路径，并沿着它们进行仪式，以阻止所有的共振振动。这意味着，对于从单个节点发出的每一对通道，必须至少存在一条选定的路径包含这两条通道。

帮助智者们找到最少数量的路径，以确保生命之树的魔法平衡得以保持，其力量继续滋养整个世界！

## 输入格式

每个测试由多个测试用例组成。第一行包含一个整数 $ t $（ $ 1 \leq t \leq 4 \cdot 10^4 $ ）——测试用例的数量。测试用例的描述如下。

每个测试用例的第一行包含一个整数 $ n $（ $ 2 \leq n \leq 5 \cdot 10^5 $ ）——生命之树中的节点数量。

接下来每个测试用例的 $ n - 1 $ 行中，第 $ i $ 行包含两个整数 $ v_i $ 和 $ u_i $（ $ 1 \leq v_i < u_i \leq n $ ）——连接节点 $ v_i $ 和 $ u_i $ 的通道。

保证在树中任意两节点之间存在一条唯一的简单路径。

保证所有测试用例中 $ n $ 的总和不超过 $ 5 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一个整数——智者们需要选择的最小路径数量，以防止灾难的发生。

## 说明/提示

在第一个测试用例中，有两个从单个节点发出的通道对：$ (1, 2) $ 和 $ (2, 3) ， (2, 3) $ 和 $ (3, 4) $。在路径 $ 1-2-3-4 $ 上进行仪式是足够的。因此，答案是 $ 1 $。

在第二个测试用例中，从单个节点发出的通道没有对，因此答案是 $ 0 $。

在第三个测试用例中，仪式可以沿着路径 $ 2-1-3 ， 2-1-4 $ 和 $ 3-1-4 $ 进行。

## 样例 #1

### 输入

```
5
4
1 2
2 3
3 4
2
1 2
4
1 2
1 3
1 4
8
3 7
2 4
1 2
2 5
3 6
1 3
3 8
6
2 3
1 2
3 6
1 5
1 4
```

### 输出

```
1
0
3
7
3
```



---

---
title: "Variance Challenge"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2029I
tag: ['贪心', '模拟费用流']
---

# Variance Challenge

## 题目描述

Kevin has recently learned the definition of variance. For an array $ a $ of length $ n $ , the variance of $ a $ is defined as follows:

- Let $ x=\dfrac{1}{n}\displaystyle\sum_{i=1}^n a_i $ , i.e., $ x $ is the mean of the array $ a $ ;
- Then, the variance of $ a $ is $ $$$ V(a)=\frac{1}{n}\sum_{i=1}^n(a_i-x)^2.  $ $  </li></ul><p>Now, Kevin gives you an array  $ a $  consisting of  $ n $  integers, as well as an integer  $ k $ . You can perform the following operation on  $ a $ :</p><ul> <li> Select an interval  $ \[l,r\] $  ( $ 1\\le l\\le r\\le n $ ), then for each  $ l\\le i\\le r $ , increase  $ a\_i $  by  $ k $ . </li></ul><p>For each  $ 1\\le p\\le m $ , you have to find the minimum possible variance of  $ a $  after exactly  $ p $  operations are performed, independently for each  $ p $ .</p><p>For simplicity, you only need to output the answers multiplied by  $ n^2$$$. It can be proven that the results are always integers.

## 输入格式

Each test contains multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1\le t\le 100 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 1\le n,m\le 5000 $ , $ \color{red}{n\cdot m\le 2\cdot 10^4} $ , $ 1\le k\le 10^5 $ ) — the length of the array $ a $ , the maximum number of operations, and the number you add to $ a_i $ each time, respectively.

The second line contains $ n $ integers $ a_1,a_2,\ldots, a_n $ ( $ 1\le a_i\le 10^5 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n\cdot m $ over all tests does not exceed $ 2\cdot 10^4 $ .

## 输出格式

For each test case, output $ m $ integers in a single line, the $ p $ -th integer denoting the minimum possible variance of $ a $ when exactly $ p $ operations are performed, multiplied by $ n^2 $ .

## 说明/提示

In the first test case:

- For $ p = 1 $ , you can perform the operation on $ [1, 1] $ , changing $ a $ from $ [1, 2, 2] $ to $ [2, 2, 2] $ . Since all of the elements are equal, the variance is equal to $ 0 $ .
- For $ p = 2 $ , you can perform the operation on $ [1, 3] $ and then $ [1, 1] $ , changing $ a $ from $ [1, 2, 2] $ to $ [2, 3, 3] $ to $ [3, 3, 3] $ . Since all of the elements are equal, the variance is equal to $ 0 $ .

In the second test case, some possible optimal choices are:

- $ p=1 $ : $ [\underline{1,}\,2,2]\to [3,2,2] $ ;
- $ p=2 $ : $ [1,\underline{2,2}] \to [\underline{1,}\,4,4] \to [3,4,4] $ .

In the third test case, some possible optimal choices are:

- $ p=1 $ : $ [10,\underline{1,1,1,1,10,1,1,1,1}]\to[10,2,2,2,2,11,2,2,2,2] $ ;
- $ p=2 $ : $ [10,1,1,1,1,10,\underline{1,1,1,1}] \to [10,\underline{1,1,1,1},10,2,2,2,2] \to [10,2,2,2,2,10,2,2,2,2] $ .

In the eighth test case, the optimal choice for all $ p $ is to perform the operation on the whole array $ p $ times.

## 样例 #1

### 输入

```
9
3 2 1
1 2 2
3 2 2
1 2 2
10 2 1
10 1 1 1 1 10 1 1 1 1
6 8 2
1 1 4 5 1 3
8 8 7
20 43 24 2 4 3 20 43
8 8 3
20 43 24 2 4 3 20 43
10 12 1
5 3 3 5 4 1 8 1 1 1
13 10 100000
1 2 3 4 5 6 7 8 9 10 11 5 4
10 5 10000
2308 9982 4435 3310 100000 9 7 8100 1919 100000
```

### 输出

```
0 0
2 2
1161 1024
53 21 21 5 5 5 5 5
10608 6912 4448 3104 1991 1312 535 304
13248 11184 9375 7815 6447 5319 4383 3687
385 316 269 224 181 156 124 101 80 56 41 29
1486 1486 1486 1486 1486 1486 1486 1486 1486 1486
134618047140 119919447140 107020847140 93922247140 82623647140
```



---

---
title: "Simurgh's Watch (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2034G1
tag: ['动态规划 DP', '贪心', '构造']
---

# Simurgh's Watch (Easy Version)

## 题目描述

传说中，神鸟 [Simurgh](https://www.eavartravel.com/blog/2023/11/3/140727/simurgh/) 需要监管大片土地，她召集了 $ n $ 名警惕的战士帮忙。每个战士在特定的时间段内保持警戒，这个时间段用 $ [l_i, r_i] $ 表示，其中 $ l_i $ 和 $ r_i $ 分别为开始和结束时间，都是包含在内的正整数。

![](https://espresso.codeforces.com/e448e919c3f03a9c212cd45c8dcd8e2bb0be579c.webp)然而，Simurgh 的顾问 [Zal](https://asia-archive.si.edu/learn/shahnama/zal-and-the-simurgh/) 担心，如果多个战士在同一时间值守且都穿着相同颜色的衣服，会造成混淆。因此，为了防止这种情况发生，在任何时刻（可以是非整数时间）的战士中，至少要有一种颜色是由恰好一个战士穿着的。

我们的任务是：确定需要的最少颜色数，并为每个战士的时间段 $ [l_i, r_i] $ 分配一种颜色 $ c_i $，使得无论在哪一个时间 $ t $（被某个时间段包含在内），至少有一种颜色只出现在一个战士上。

## 输入格式

第一行包含一个整数 $ t $ （$ 1 \leq t \leq 10^4 $）——表示测试用例的数目。

每个测试用例包含以下内容：

- 第一行是一个整数 $ n $ （$ 1 \leq n \leq 2 \cdot 10^5 $）——表示 Simurgh 派出的战士数量。
- 接下来的 $ n $ 行中，每行包含两个整数 $ l_i $ 和 $ r_i $ （$ 1 \leq l_i \leq r_i \leq 10^9 $）——分别表示第 $ i $ 个战士的值班开始和结束时间。

所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例：

- 首先输出要使用的最少的颜色数量 $ k $。
- 接下来输出一行 $ n $ 个整数 $ c_i $（$ 1 \leq c_i \leq k $），代表为第 $ i $ 位战士分配的颜色。

## 说明/提示

可以将每个战士的值班时间段视作 X 轴上的一个区间：

- 在测试用例 1 中，有两个彼此不重叠的区间，因此可用相同颜色。
- 在测试用例 2 中，时间点 2 是公共的，因此不能使用相同颜色。
- 在测试用例 3 中，区间可以按下图所示进行着色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/dd56c79752790418adde70ef7aa40c52b2f8834f.png)

- 在测试用例 4 中，区间的着色方式如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/7c7aad3a3ba91ddaff1d673e62791383c4f77dec.png)

- 在测试用例 5 中，区间着色如下图所示。右侧图是错误的着色示例；在时间点 $ 5.5 $ 时，没有唯一颜色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/b8f2a4852b6af3f78d2729a80e0ad7497e55682a.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
1 2
3 4
2
1 2
2 3
3
1 4
2 5
3 6
5
1 4
2 8
3 7
5 10
6 9
5
1 5
2 6
3 7
4 7
6 7
```

### 输出

```
1
1 1
2
1 2
2
1 2 1
3
2 3 1 2 1
3
2 1 3 1 1
```



---

---
title: "Simurgh's Watch (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2034G2
tag: ['动态规划 DP', '贪心', '构造']
---

# Simurgh's Watch (Hard Version)

## 题目描述

传说中的神鸟 Simurgh 负责守护一片辽阔的土地，她为此招募了 $n$ 名机敏的战士。每位战士都需要在特定的时间段 $[l_i, r_i]$ 内保持警戒，其中 $l_i$ 代表起始时间（包含），$r_i$ 代表结束时间（包含），两者均为正整数。

Simurgh 信任的顾问 Zal 担心，如果多个战士同时在岗且都穿着相同的颜色，那么他们之间可能会难以区分，从而导致混乱。为解决这一问题，在每个整数时刻 $t$，如果有多个战士在岗，必须确保至少有一种颜色仅被其中一个战士穿着。

任务是找出所需的最少颜色数量，并为每个战士的时间段 $[l_i, r_i]$ 分配一种颜色 $c_i$，使得对于包含在至少一个时间段内的每个整数时间点 $t$，总有一种颜色只被一个时间段在$t$时刻使用。

## 输入格式

第一行输入一个整数 $t$（$1 \leq t \leq 10^4$），表示测试用例的数量。

对于每个测试用例：

- 第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$），表示 Simurgh 招募的战士数量。
- 随后的 $n$ 行中，每行包含两个整数 $l_i$ 和 $r_i$（$1 \leq l_i \leq r_i \leq 10^9$），表示第 $i$ 位战士的警戒时间段。

所有测试用例中的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例：

- 输出所需的最少颜色数量 $k$。
- 接下来输出一行，包括 $n$ 个整数 $c_i$（$1 \leq c_i \leq k$），每个 $c_i$ 表示分配给第 $i$ 位战士的颜色。

## 说明/提示

我们可以将每位战士的警戒时间段看作 X 轴上的一个区间。

以下示例展示了如何为各个测试用例的区间着色（区域只有在某时间点，仅某种颜色出现时该区域才被染色）：

- 测试用例 1：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/a8ca04e863ed852cb4b11c3982c1d5442199b24b.png)

- 测试用例 2：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/36f2a5d9878f69668f835178da7df8642bec8342.png)

- 测试用例 3：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/75559577acf19732a5a59981d3806145e52c5ed5.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
5
1 4
2 8
3 7
5 10
6 9
5
1 5
2 6
3 7
4 7
6 7
5
4 9
8 17
2 15
12 19
6 13
```

### 输出

```
2
1 2 2 1 2
2
1 2 2 2 1
3
1 1 2 3 1
```



---

---
title: "Cheops and a Contest (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2046E2
tag: ['贪心', '构造']
---

# Cheops and a Contest (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, $ m $ is arbitrary. You can hack only if you solved all versions of this problem.

There is a problem-solving competition in Ancient Egypt with $ n $ participants, numbered from $ 1 $ to $ n $ . Each participant comes from a certain city; the cities are numbered from $ 1 $ to $ m $ . There is at least one participant from each city.

The $ i $ -th participant has strength $ a_i $ , specialization $ s_i $ , and wisdom $ b_i $ , so that $ b_i \ge a_i $ . Each problem in the competition will have a difficulty $ d $ and a unique topic $ t $ . The $ i $ -th participant will solve the problem if

- $ a_i \ge d $ , i.e., their strength is not less than the problem's difficulty, or
- $ s_i = t $ , and $ b_i \ge d $ , i.e., their specialization matches the problem's topic, and their wisdom is not less than the problem's difficulty.

Cheops wants to choose the problems in such a way that each participant from city $ i $ will solve strictly more problems than each participant from city $ j $ , for all $ i < j $ .

Please find a set of at most $ 5n $ problems, where the topics of all problems are distinct, so that Cheops' will is satisfied, or state that it is impossible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ T $ ( $ 1 \le T \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 2 \le m \le n \le 3 \cdot {10}^5 $ ) — the number of participants and the number of cities.

The following $ n $ lines describe the participants. The $ i $ -th line contains three integers — $ a_i $ , $ b_i $ , $ s_i $ ( $ 0 \le a_i, b_i, s_i \le {10}^9 $ , $ a_i \le b_i $ ) — strength, wisdom, and specialization of the $ i $ -th participant, respectively.

The next $ m $ lines describe the cities. In the $ i $ -th line, the first number is an integer $ k_i $ ( $ 1 \le k_i \le n $ ) — the number of participants from the $ i $ -th city. It is followed by $ k_i $ integers $ q_{i, 1}, q_{i, 2}, \ldots, q_{i, k_i} $ — ( $ 1 \le q_{i, j} \le n $ , $ 1 \le j \le k_i $ ) — the indices of the participants from this city. It is guaranteed that each participant is mentioned exactly once.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, if there exists a set of problems that satisfies Cheops' conditions, then in the first line output a single integer $ p $ ( $ 1 \le p \le 5n $ ) — the number of problems in your solution.

Then output $ p $ lines, each containing two integers $ d $ and $ t $ ( $ 0 \le d, t \le {10}^9 $ ) — the difficulty and topic of the respective problem. The topics must be distinct.

If there is no set of problems that meets Cheops' wishes, print $ -1 $ instead.

## 样例 #1

### 输入

```
2
5 2
5 7 1
6 7 2
3 9 2
5 10 3
4 4 1
2 1 2
3 3 4 5
2 2
1 2 1
1 2 1
1 2
1 1
```

### 输出

```
7
6 4
6 5
5 6
5 7
4 8
4 9
7 1
-1
```



---

---
title: "Yandex Cuneiform (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2046F1
tag: ['贪心', '树状数组']
---

# Yandex Cuneiform (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is that in this version, there are no question marks. You can hack only if you solved all versions of this problem.

For a long time, no one could decipher Sumerian cuneiform. However, it has finally succumbed to pressure! Today, you have the chance to decipher Yandex cuneiform.

Yandex cuneiform is defined by the following rules:

1. An empty string is a Yandex cuneiform.
2. If you insert exactly one copy of each of the three letters 'Y', 'D', and 'X' into a Yandex cuneiform in such a way that no two adjacent letters become equal after the operation, you obtain a Yandex cuneiform.
3. If a string can't be obtained using the above rules, it is not a Yandex cuneiform.

You are given a template. A template is a string consisting of the characters 'Y', 'D', 'X', and '?'.

You need to check whether there exists a way to replace each question mark with 'Y', 'D', or 'X' to obtain a Yandex cuneiform, and if it exists, output any of the matching options, as well as a sequence of insertion operations to obtain the resulting cuneiform.

In this version of the problem, there are no question marks in the template.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^4 $ ). The description of the test cases follows.

Each test case consists of a single line containing a template of length $ n $ ( $ 3 \leq n < 2 \cdot 10^5 $ , $ n \bmod 3 = 0 $ ), consisting only of characters 'Y', 'D', 'X'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing 'NO' if it is not possible to obtain a cuneiform from the given template.

Otherwise, output 'YES' on the first line, and on the second line, any obtainable cuneiform. After that, you need to output the sequence of operations that leads to the cuneiform you printed.

A sequence of operations is described by $ \frac{n}{3} $ triples of pairs. A pair has the form c p, where $ c $ is one of the letters 'Y', 'D', or 'X', and $ p $ is the position at which the letter $ c $ should be inserted. The insertion position is the number of letters to skip from the beginning of the string for the insertion. For example, after inserting the character 'D' into the string "YDX" with $ p=3 $ , the result is "YDXD", and with $ p=0 $ , it is "DYDX". Note that the index cannot exceed the current length of the string.

The operations are applied from top to bottom, left to right. After inserting each triple to the string, there should be no two adjacent identical characters.

## 说明/提示

In the second example, the string is transformed like this: $ "" \to \mathtt{YDX} \to \mathtt{YDXDYX} $ .

## 样例 #1

### 输入

```
4
YDX
YDXDYX
YDX
DYYDXYXYX
```

### 输出

```
YES
YDX
X 0 D 0 Y 0 
YES
YDXDYX
X 0 Y 0 D 1
X 2 D 3 Y 4
YES
YDX
Y 0 D 1 X 2
NO
```



---

---
title: "Naive String Splits"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2053G
tag: ['贪心', '哈希 hashing']
---

# Naive String Splits

## 题目描述

Cocoly 有一个长度为 $m$ 的字符串 $t$，全部由小写字母组成。他希望可以把这个字符串拆分成多个部分。若存在一个字符串序列 $a_1, a_2, \ldots, a_k$，满足：

- $t = a_1 + a_2 + \ldots + a_k$，其中 $+$ 表示字符串的连接。
- 对于每个 $1 \leq i \leq k$，至少满足 $a_i = x$ 或 $a_i = y$。

那么就称字符串对 $(x, y)$ 是美丽的。

Cocoly 还有一个长度为 $n$ 的字符串 $s$，同样由小写字母构成。现在，对于每一个位置 $1 \leq i < n$，Cocoly 需要你来判断字符串对 $(s_1s_2 \ldots s_i, \, s_{i+1}s_{i+2} \ldots s_n)$ 是否美丽。

注意：由于数据量较大，输入输出需要进行优化，例如在 C++ 中，可以在 `main` 函数的开头加入以下代码，以提高效率：

```cpp
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr);
}
```

## 输入格式

输入包含多个测试用例。第一行包含一个整数 $T$（$1 \leq T \leq 10^5$），表示测试用例的数量。接下来是每个测试用例的具体描述。

每个测试用例的第一行是两个整数 $n$ 和 $m$（$2 \leq n \leq m \leq 5 \times 10^6$），分别表示字符串 $s$ 和 $t$ 的长度。

接下来的两行中，第二行是长度为 $n$ 的字符串 $s$，第三行是长度为 $m$ 的字符串 $t$，这两个字符串均由小写字母组成。

保证所有测试用例中 $m$ 的总和不超过 $10^7$。

## 输出格式

对于每个测试用例，输出一个长度为 $n-1$ 的二进制字符串 $r$：每个 $1 \leq i < n$，如果第 $i$ 个字符串对是美丽的则 $r_i=\texttt{1}$，否则 $r_i=\texttt{0}$。输出时不要每两位之间加空格。

## 说明/提示

举例来说，第一个测试用例中，$s = \tt aba$，$t = \tt ababa$。

- 当 $i = 1$：Cocoly 可以将 $t$ 分割为 $\texttt{a} + \texttt{ba} + \texttt{ba}$，因此字符串对 $(\texttt{a}, \texttt{ba})$ 是美丽的。
- 当 $i = 2$：Cocoly 可以将 $t$ 分割为 $\texttt{ab} + \texttt{ab} + \texttt{a}$，因此字符串对 $(\texttt{ab}, \texttt{a})$ 也是美丽的。

在第二个测试用例中，$s = \tt czzz$，$t = \tt czzzzzczzz$。

- 当 $i = 1$：可以证明无法通过字符串 $\texttt{c}$ 和 $\texttt{zzz}$ 将 $t$ 进行美丽的分割。
- 当 $i = 2$：Cocoly 可以将 $t$ 分割为 $\texttt{cz} + \texttt{zz} + \texttt{zz} + \texttt{cz} + \texttt{zz}$。
- 当 $i = 3$：Cocoly 可以将 $t$ 分割为 $\texttt{czz} + \texttt{z} + \texttt{z} + \texttt{z} + \texttt{czz} + \texttt{z}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
3 5
aba
ababa
4 10
czzz
czzzzzczzz
5 14
dream
dredreamamamam
5 18
tcccc
tcctccccctccctcccc
7 11
abababc
abababababc
7 26
aaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaa
19 29
bbbbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbbbbbbbbbbbbbbbbb
```

### 输出

```
11
011
0010
0000
010100
111111
110010001100010011
```



---

---
title: "Coffee Break"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2057H
tag: ['贪心']
---

# Coffee Break

## 题目描述

T-Generation 的课程十分漫长。在一天中，必须安排时间来分析训练和专题比赛，讲解新内容，并在可能的情况下，举行一个小型研讨会。因此，课间休息时学生们会去喝咖啡或聊天。

走廊上总共有 $n+2$ 台咖啡机，依次排列。咖啡机编号从 $0$ 到 $n+1$，当休息开始时，第 $i$ 台咖啡机周围聚集了 $a_i$ 名学生。

由于学生们说话声太大，老师需要进行一个重要的通知。因此，他们希望将尽可能多的学生聚集到某一台咖啡机周围。不过，老师们懒得亲自去召集学生，想出了一种巧妙的方法：

- 随时可以选择房间 $i$（$1 \le i \le n$）并关闭那里的灯；
- 如果该房间有 $x$ 名学生，关灯后，$\lfloor \frac{1}{2} x \rfloor$ 名学生会去左边的房间 $(i-1)$，另外 $\lfloor \frac{1}{2} x \rfloor$ 名学生会去右边的房间 $(i+1)$；
- 如果 $x$ 是奇数，则有一名学生留在原位；
- 随后再次打开房间 $i$ 的灯。

老师们尚未决定最终要在何处聚集学生，因此需要计算，对于每个 $i$ 从 $1$ 到 $n$，在第 $i$ 台咖啡机周围最多能聚集多少名学生。

老师们可以任意顺序、任意次数选择关灯，可以在同一个房间多次操作。

需要注意的是，$a_0$ 和 $a_{n+1}$ 的值对结果没有影响，因此不需要考虑这两个值。

## 输入格式

第一行输入一个整数 $t$（$1 \le t \le 10\,000$），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10^6$）。

接下来一行是 $n$ 个整数 $a_1, \ldots, a_n$（$0 \le a_i \le 10^9$），表示学生在编号为 $1, 2, \ldots, n$ 的咖啡机周围的人数。

保证所有测试用例中的 $n$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数 $b_1, \ldots, b_n$，其中 $b_i$ 表示在编号为 $i$ 的咖啡机周围最多能聚集的学生人数。

## 说明/提示

举个例子，分析第一个测试用例：

- 为了让第 $1$ 台咖啡机周围的学生人数最大化，只需要保持现状。
- 为了让第 $2$ 台咖啡机周围的学生人数最大化，只需在第 $1$ 个房间关一次灯。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2
8 0
5
2 2 2 2 2
5
0 0 9 0 0
```

### 输出

```
8 4 
4 5 4 5 4 
4 6 9 6 4
```



---

