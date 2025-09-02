---
title: "Lucky Tickets"
layout: "post"
diff: 省选/NOI-
pid: CF1096G
tag: ['组合数学', '快速数论变换 NTT']
---

# Lucky Tickets

## 题目描述

All bus tickets in Berland have their numbers. A number consists of $ n $ digits ( $ n $ is even). Only $ k $ decimal digits $ d_1, d_2, \dots, d_k $ can be used to form ticket numbers. If $ 0 $ is among these digits, then numbers may have leading zeroes. For example, if $ n = 4 $ and only digits $ 0 $ and $ 4 $ can be used, then $ 0000 $ , $ 4004 $ , $ 4440 $ are valid ticket numbers, and $ 0002 $ , $ 00 $ , $ 44443 $ are not.

A ticket is lucky if the sum of first $ n / 2 $ digits is equal to the sum of remaining $ n / 2 $ digits.

Calculate the number of different lucky tickets in Berland. Since the answer may be big, print it modulo $ 998244353 $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (2 \le n \le 2 \cdot 10^5, 1 \le k \le 10) $ — the number of digits in each ticket number, and the number of different decimal digits that may be used. $ n $ is even.

The second line contains a sequence of pairwise distinct integers $ d_1, d_2, \dots, d_k $ $ (0 \le d_i \le 9) $ — the digits that may be used in ticket numbers. The digits are given in arbitrary order.

## 输出格式

Print the number of lucky ticket numbers, taken modulo $ 998244353 $ .

## 说明/提示

In the first example there are $ 6 $ lucky ticket numbers: $ 1111 $ , $ 1818 $ , $ 1881 $ , $ 8118 $ , $ 8181 $ and $ 8888 $ .

There is only one ticket number in the second example, it consists of $ 20 $ digits $ 6 $ . This ticket number is lucky, so the answer is $ 1 $ .

## 样例 #1

### 输入

```
4 2
1 8

```

### 输出

```
6

```

## 样例 #2

### 输入

```
20 1
6

```

### 输出

```
1

```

## 样例 #3

### 输入

```
10 5
6 1 4 0 3

```

### 输出

```
569725

```

## 样例 #4

### 输入

```
1000 7
5 4 0 1 8 3 2

```

### 输出

```
460571165

```



---

---
title: "Emotional Fishermen"
layout: "post"
diff: 省选/NOI-
pid: CF1437F
tag: ['动态规划 DP', '组合数学']
---

# Emotional Fishermen

## 题目描述

$ n $ fishermen have just returned from a fishing vacation. The $ i $ -th fisherman has caught a fish of weight $ a_i $ .

Fishermen are going to show off the fish they caught to each other. To do so, they firstly choose an order in which they show their fish (each fisherman shows his fish exactly once, so, formally, the order of showing fish is a permutation of integers from $ 1 $ to $ n $ ). Then they show the fish they caught according to the chosen order. When a fisherman shows his fish, he might either become happy, become sad, or stay content.

Suppose a fisherman shows a fish of weight $ x $ , and the maximum weight of a previously shown fish is $ y $ ( $ y = 0 $ if that fisherman is the first to show his fish). Then:

- if $ x \ge 2y $ , the fisherman becomes happy;
- if $ 2x \le y $ , the fisherman becomes sad;
- if none of these two conditions is met, the fisherman stays content.

Let's call an order in which the fishermen show their fish emotional if, after all fishermen show their fish according to this order, each fisherman becomes either happy or sad. Calculate the number of emotional orders modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 5000 $ ).

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

Print one integer — the number of emotional orders, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 4 9
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4
4 3 2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
4 2 1
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
42 1337 13 37 420 666 616 97
```

### 输出

```
19200
```



---

---
title: "Top-Notch Insertions"
layout: "post"
diff: 省选/NOI-
pid: CF1558D
tag: ['线段树', '二分', '平衡树', '组合数学']
---

# Top-Notch Insertions

## 题目描述

Consider the insertion sort algorithm used to sort an integer sequence $ [a_1, a_2, \ldots, a_n] $ of length $ n $ in non-decreasing order.

For each $ i $ in order from $ 2 $ to $ n $ , do the following. If $ a_i \ge a_{i-1} $ , do nothing and move on to the next value of $ i $ . Otherwise, find the smallest $ j $ such that $ a_i < a_j $ , shift the elements on positions from $ j $ to $ i-1 $ by one position to the right, and write down the initial value of $ a_i $ to position $ j $ . In this case we'll say that we performed an insertion of an element from position $ i $ to position $ j $ .

It can be noticed that after processing any $ i $ , the prefix of the sequence $ [a_1, a_2, \ldots, a_i] $ is sorted in non-decreasing order, therefore, the algorithm indeed sorts any sequence.

For example, sorting $ [4, 5, 3, 1, 3] $ proceeds as follows:

- $ i = 2 $ : $ a_2 \ge a_1 $ , do nothing;
- $ i = 3 $ : $ j = 1 $ , insert from position $ 3 $ to position $ 1 $ : $ [3, 4, 5, 1, 3] $ ;
- $ i = 4 $ : $ j = 1 $ , insert from position $ 4 $ to position $ 1 $ : $ [1, 3, 4, 5, 3] $ ;
- $ i = 5 $ : $ j = 3 $ , insert from position $ 5 $ to position $ 3 $ : $ [1, 3, 3, 4, 5] $ .

You are given an integer $ n $ and a list of $ m $ integer pairs $ (x_i, y_i) $ . We are interested in sequences such that if you sort them using the above algorithm, exactly $ m $ insertions will be performed: first from position $ x_1 $ to position $ y_1 $ , then from position $ x_2 $ to position $ y_2 $ , ..., finally, from position $ x_m $ to position $ y_m $ .

How many sequences of length $ n $ consisting of (not necessarily distinct) integers between $ 1 $ and $ n $ , inclusive, satisfy the above condition? Print this number modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ 0 \le m < n $ ) — the length of the sequence and the number of insertions.

The $ i $ -th of the following $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 2 \le x_1 < x_2 < \ldots < x_m \le n $ ; $ 1 \le y_i < x_i $ ). These lines describe the sequence of insertions in chronological order.

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Note that there is no constraint on the sum of $ n $ of the same kind.

## 输出格式

For each test case, print the number of sequences of length $ n $ consisting of integers from $ 1 $ to $ n $ such that sorting them with the described algorithm produces the given sequence of insertions, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the algorithm performs no insertions — therefore, the initial sequence is already sorted in non-decreasing order. There are $ 10 $ such sequences: $ [1, 1, 1], [1, 1, 2], [1, 1, 3], [1, 2, 2], [1, 2, 3], [1, 3, 3], [2, 2, 2], [2, 2, 3], [2, 3, 3], [3, 3, 3] $ .

In the second test case, the only sequence satisfying the conditions is $ [3, 2, 1] $ .

In the third test case, $ [4, 5, 3, 1, 3] $ is one of the sought sequences.

## 样例 #1

### 输入

```
3
3 0
3 2
2 1
3 1
5 3
3 1
4 1
5 3
```

### 输出

```
10
1
21
```



---

---
title: "A Random Code Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1626F
tag: ['动态规划 DP', '状态合并', '组合数学']
---

# A Random Code Problem

## 题目描述

给你一个数组 $a$ 和一个整数 $k$ ，执行下面的代码：
```cpp
long long ans = 0; //定义一个初始值为 0 的长整型变量
for(int i = 1; i <= k; i++) {
	int idx = rnd.next(0, n - 1); //生成一个介于0到n-1的随机数（含 0 和 n-1）
  								 //每个数被选中的概率是相同的
	ans += a[idx];
	a[idx] -= (a[idx] % i);
}
```
您需要在执行此代码后计算变量 $ans$ 的期望。

数组 $a$ 是输入时根据特殊规则生成的。

## 输入格式

仅一行，六个整数 $n$ , $a_0$ , $x$ , $y$ , $k$ 和 $M$ 。

数组 $a$ 由以下规则生成：

* $a_0$ 由输入给出
* 对于 $a_1$ 至 $a_{n-1}$，$a_i=(a_{i-1}\times x+y)\bmod M$。

## 输出格式

令 $E$ 为 $ans$ 的期望，输出 $E\times n^k$，对 $998244353$ 取模。

## 说明/提示

$1\le n\le10^7$

$1\le a_0,x,y<M\le998244353$

$1\le k\le17$

## 样例 #1

### 输入

```
3 10 3 5 13 88
```

### 输出

```
382842030
```

## 样例 #2

### 输入

```
2 15363 270880 34698 17 2357023
```

### 输出

```
319392398
```



---

---
title: "Coloring"
layout: "post"
diff: 省选/NOI-
pid: CF1697E
tag: ['动态规划 DP', '图论', '组合数学']
---

# Coloring

## 题目描述

You are given $ n $ points on the plane, the coordinates of the $ i $ -th point are $ (x_i, y_i) $ . No two points have the same coordinates.

The distance between points $ i $ and $ j $ is defined as $ d(i,j) = |x_i - x_j| + |y_i - y_j| $ .

For each point, you have to choose a color, represented by an integer from $ 1 $ to $ n $ . For every ordered triple of different points $ (a,b,c) $ , the following constraints should be met:

- if $ a $ , $ b $ and $ c $ have the same color, then $ d(a,b) = d(a,c) = d(b,c) $ ;
- if $ a $ and $ b $ have the same color, and the color of $ c $ is different from the color of $ a $ , then $ d(a,b) < d(a,c) $ and $ d(a,b) < d(b,c) $ .

Calculate the number of different ways to choose the colors that meet these constraints.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ) — the number of points.

Then $ n $ lines follow. The $ i $ -th of them contains two integers $ x_i $ and $ y_i $ ( $ 0 \le x_i, y_i \le 10^8 $ ).

No two points have the same coordinates (i. e. if $ i \ne j $ , then either $ x_i \ne x_j $ or $ y_i \ne y_j $ ).

## 输出格式

Print one integer — the number of ways to choose the colors for the points. Since it can be large, print it modulo $ 998244353 $ .

## 说明/提示

In the first test, the following ways to choose the colors are suitable:

- $ [1, 1, 1] $ ;
- $ [2, 2, 2] $ ;
- $ [3, 3, 3] $ ;
- $ [1, 2, 3] $ ;
- $ [1, 3, 2] $ ;
- $ [2, 1, 3] $ ;
- $ [2, 3, 1] $ ;
- $ [3, 1, 2] $ ;
- $ [3, 2, 1] $ .

## 样例 #1

### 输入

```
3
1 0
3 0
2 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
1 2
2 4
3 4
4 4
1 3
```

### 输出

```
240
```

## 样例 #3

### 输入

```
4
1 0
3 0
2 1
2 0
```

### 输出

```
24
```



---

---
title: "Game of AI (easy version)"
layout: "post"
diff: 省选/NOI-
pid: CF1704H1
tag: ['组合数学']
---

# Game of AI (easy version)

## 题目描述

这是本题的简单版本。简单版本与困难版本的区别在于对 $k$ 的约束和时间限制。此外，在本版本中，你只需要计算 $n=k$ 时的答案。只有当两个版本均被解决时，你才能进行 hack。

Cirno 正在玩一款战争模拟游戏，其中有 $n$ 座塔（编号为 $1$ 至 $n$）和 $n$ 个机器人（编号为 $1$ 至 $n$）。初始时，第 $i$ 座塔被第 $i$ 个机器人占据（$1 \le i \le n$）。

在游戏开始前，Cirno 首先选择一个长度为 $n$ 的排列 $p = [p_1, p_2, \ldots, p_n]$（一个长度为 $n$ 的排列是指每个 $1$ 到 $n$ 的整数恰好出现一次的数组）。接着，她选择一个序列 $a = [a_1, a_2, \ldots, a_n]$（满足 $1 \le a_i \le n$ 且 $a_i \ne i$ 对所有 $1 \le i \le n$ 成立）。

游戏包含 $n$ 轮攻击。在第 $i$ 轮中，如果第 $p_i$ 个机器人仍在游戏中，它将发起攻击，导致第 $a_{p_i}$ 座塔被第 $p_i$ 个机器人占据；原本占据第 $a_{p_i}$ 座塔的机器人将失去该塔。如果第 $p_i$ 个机器人已不在游戏中，此轮不会发生任何事。

每轮结束后，如果一个机器人未占据任何塔，它将被淘汰并退出游戏。注意一座塔不能同时被多个机器人占据，但一个机器人可以在游戏中占据多座塔。

游戏结束时，Cirno 将记录结果序列 $b = [b_1, b_2, \ldots, b_n]$，其中 $b_i$ 表示结束时占据第 $i$ 座塔的机器人编号。

然而，作为数学大师，她希望你解决以下计数问题而非亲自游戏：

计算所有可能的序列 $a$ 和排列 $p$ 能生成的不同序列对 $(a, b)$ 的数量。

由于结果可能很大，请输出其对 $M$ 取模后的值。

## 输入格式

仅一行包含两个正整数 $k$ 和 $M$（$1 \le k \le 5000$，$2 \le M \le 10^9$）。保证 $2^{18}$ 是 $M-1$ 的因数且 $M$ 是质数。

你需要计算当 $n=k$ 时的答案。

## 输出格式

输出一个整数——当 $n=k$ 时不同序列对的数量对 $M$ 取模后的结果。

## 说明/提示

当 $n=1$ 时，不存在合法的序列 $a$，因此答案为 $0$。

当 $n=2$ 时，唯一可能的数组 $a$ 是 $[2, 1]$：
- 当 $a$ 为 $[2, 1]$ 且 $p$ 为 $[1, 2]$ 时，最终序列 $b$ 为 $[1, 1]$。具体过程：
  - 第一轮，第一个机器人发起攻击并占领第 $2$ 座塔。此轮结束后，第二个机器人因失去所有塔而被淘汰。
  - 第二轮，第二个机器人已不在游戏中。
- 当 $a$ 为 $[2, 1]$ 且 $p$ 为 $[2, 1]$ 时，最终序列 $b$ 为 $[2, 2]$。具体过程：
  - 第一轮，第二个机器人发起攻击并占领第 $1$ 座塔。此轮结束后，第一个机器人被淘汰。
  - 第二轮，第一个机器人已不在游戏中。

因此当 $n=2$ 时，不同的序列对 $(a, b)$ 的数量为 $2$（即 $([2, 1], [1, 1])$ 和 $([2, 1], [2, 2])$）。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
1 998244353
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 998244353
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 998244353
```

### 输出

```
24
```

## 样例 #4

### 输入

```
8 998244353
```

### 输出

```
123391016
```



---

---
title: "Bags with Balls"
layout: "post"
diff: 省选/NOI-
pid: CF1716F
tag: ['组合数学', 'Stirling 数']
---

# Bags with Balls

## 题目描述

# Bags with Balls 袋中之球


这里有 $ n $ 个袋子，每个袋子里面有 $ m $ 个带有从 $ 1 $ - $ m $ 标记的球。对于每一个 $ 1 $ ≤ $ i $ ≤ $ m $  来说，每个袋子中都一定存在一个带有 $ i $ 标记的球。

你需要在每个袋子中取出一个球 ( 所有的袋子都是不同的，比如在 $ 1 $ 号袋子取 $ 2 $ 号球 并且从 $ 2 $ 号袋子里取 $ 1 $ 号球 与 从 $ 1 $ 号袋子取 $ 1 $ 号球并且从 $ 2 $ 号袋子取 $ 2 $ 号球是不同的两种方案 ) 然后计算出你取出的标号是奇数的球的数量，记这个数量为 $ F $ 。

你的任务是计算所有可能的取球方案的 $ F^k $ 之和。

## 输入格式

第一行包含一个整数 $ t $ ( $ 1 \le t \le 5000 $ ) — 测试组数的数量

每组第一行输入三个整数 $ n $ , $ m $ 和 $ k $ ( $ 1 \le n, m \le 998244352 $ ; $ 1 \le k \le 2000 $ ).

## 输出格式

每组测试输出一个整数 —  $ F^k $ ( 意义见题面 ). 由于它可能会很大，请将它模 $ 998244353 $ 后输出.

## 样例 #1

### 输入

```
5
2 3 8
1 1 1
1 5 10
3 7 2000
1337666 42424242 2000
```

### 输出

```
1028
1
3
729229716
652219904
```



---

---
title: "Illumination"
layout: "post"
diff: 省选/NOI-
pid: CF1728G
tag: ['动态规划 DP', '状态合并', '组合数学', '容斥原理', '快速沃尔什变换 FWT']
---

# Illumination

## 题目描述

Consider a segment $ [0, d] $ of the coordinate line. There are $ n $ lanterns and $ m $ points of interest in this segment.

For each lantern, you can choose its power — an integer between $ 0 $ and $ d $ (inclusive). A lantern with coordinate $ x $ illuminates the point of interest with coordinate $ y $ if $ |x - y| $ is less than or equal to the power of the lantern.

A way to choose the power values for all lanterns is considered valid if every point of interest is illuminated by at least one lantern.

You have to process $ q $ queries. Each query is represented by one integer $ f_i $ . To answer the $ i $ -th query, you have to:

- add a lantern on coordinate $ f_i $ ;
- calculate the number of valid ways to assign power values to all lanterns, and print it modulo $ 998244353 $ ;
- remove the lantern you just added.

## 输入格式

The first line contains three integers $ d $ , $ n $ and $ m $ ( $ 4 \le d \le 3 \cdot 10^5 $ ; $ 1 \le n \le 2 \cdot 10^5 $ ; $ 1 \le m \le 16 $ ) — the size of the segment, the number of lanterns and the number of points of interest, respectively.

The second line contains $ n $ integers $ l_1, l_2, \dots, l_n $ ( $ 1 \le l_i \le d - 1 $ ), where $ l_i $ is the coordinate of the $ i $ -th lantern.

The third line contains $ m $ integers $ p_1, p_2, \dots, p_m $ ( $ 1 \le p_i \le d - 1 $ ), where $ p_i $ is the coordinate of the $ i $ -th point of interest.

The fourth line contains one integer $ q $ ( $ 1 \le q \le 5 \cdot 10^5 $ ) — the number of queries.

The fifth line contains $ q $ integers $ f_1, f_2, \dots, f_q $ ( $ 1 \le f_i \le d - 1 $ ), where $ f_i $ is the integer representing the $ i $ -th query.

Additional constraint on the input: during the processing of each query, no coordinate contains more than one object (i. e. there cannot be two or more lanterns with the same coordinate, two or more points of interest with the same coordinate, or a lantern and a point of interest with the same coordinate).

## 输出格式

For each query, print one integer — the answer to it, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
6 1 1
4
3
3
2 1 5
```

### 输出

```
48
47
47
```

## 样例 #2

### 输入

```
6 1 2
4
2 5
2
1 3
```

### 输出

```
44
46
```

## 样例 #3

### 输入

```
20 1 2
11
15 7
1
8
```

### 输出

```
413
```

## 样例 #4

### 输入

```
20 3 5
5 7 18
1 6 3 10 19
5
4 17 15 8 9
```

### 输出

```
190431
187503
188085
189903
189708
```



---

---
title: "Function Sum"
layout: "post"
diff: 省选/NOI-
pid: CF1731F
tag: ['组合数学']
---

# Function Sum

## 题目描述

Suppose you have an integer array $ a_1, a_2, \dots, a_n $ .

Let $ \operatorname{lsl}(i) $ be the number of indices $ j $ ( $ 1 \le j < i $ ) such that $ a_j < a_i $ .

Analogically, let $ \operatorname{grr}(i) $ be the number of indices $ j $ ( $ i < j \le n $ ) such that $ a_j > a_i $ .

Let's name position $ i $ good in the array $ a $ if $ \operatorname{lsl}(i) < \operatorname{grr}(i) $ .

Finally, let's define a function $ f $ on array $ a $ $ f(a) $ as the sum of all $ a_i $ such that $ i $ is good in $ a $ .

Given two integers $ n $ and $ k $ , find the sum of $ f(a) $ over all arrays $ a $ of size $ n $ such that $ 1 \leq a_i \leq k $ for all $ 1 \leq i \leq n $ modulo $ 998\,244\,353 $ .

## 输入格式

The first and only line contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 50 $ ; $ 2 \leq k < 998\,244\,353 $ ).

## 输出格式

Output a single integer — the sum of $ f $ over all arrays $ a $ of size $ n $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

  $ f([1,1,1]) = 0 $  $ f([2,2,3]) = 2 + 2 = 4 $  $ f([1,1,2]) = 1 + 1 = 2 $  $ f([2,3,1]) = 2 $  $ f([1,1,3]) = 1 + 1 = 2 $  $ f([2,3,2]) = 2 $  $ f([1,2,1]) = 1 $  $ f([2,3,3]) = 2 $  $ f([1,2,2]) = 1 $  $ f([3,1,1]) = 0 $  $ f([1,2,3]) = 1 $  $ f([3,1,2]) = 1 $  $ f([1,3,1]) = 1 $  $ f([3,1,3]) = 1 $  $ f([1,3,2]) = 1 $  $ f([3,2,1]) = 0 $  $ f([1,3,3]) = 1 $  $ f([3,2,2]) = 0 $  $ f([2,1,1]) = 0 $  $ f([3,2,3]) = 2 $  $ f([2,1,2]) = 1 $  $ f([3,3,1]) = 0 $  $ f([2,1,3]) = 2 + 1 = 3 $  $ f([3,3,2]) = 0 $  $ f([2,2,1]) = 0 $  $ f([3,3,3]) = 0 $  $ f([2,2,2]) = 0 $ Adding up all of these values, we get $ 28 $ as the answer.

## 样例 #1

### 输入

```
3 3
```

### 输出

```
28
```

## 样例 #2

### 输入

```
5 6
```

### 输出

```
34475
```

## 样例 #3

### 输入

```
12 30
```

### 输出

```
920711694
```



---

---
title: "List Generation"
layout: "post"
diff: 省选/NOI-
pid: CF1747E
tag: ['递推', '组合数学', '容斥原理']
---

# List Generation

## 题目描述

For given integers $ n $ and $ m $ , let's call a pair of arrays $ a $ and $ b $ of integers good, if they satisfy the following conditions:

- $ a $ and $ b $ have the same length, let their length be $ k $ .
- $ k \ge 2 $ and $ a_1 = 0, a_k = n, b_1 = 0, b_k = m $ .
- For each $ 1 < i \le k $ the following holds: $ a_i \geq a_{i - 1} $ , $ b_i \geq b_{i - 1} $ , and $ a_i + b_i \neq a_{i - 1} + b_{i - 1} $ .

Find the sum of $ |a| $ over all good pairs of arrays $ (a,b) $ . Since the answer can be very large, output it modulo $ 10^9 + 7 $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t (1 \leq t \leq 10^4) $ — the number of test cases. The description of the test cases follows.

The only line of each test case contains two integers $ n $ and $ m $ $ (1 \leq n, m \leq 5 \cdot 10^6) $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^6 $ and the sum of $ m $ over all test cases does not exceed $ 5 \cdot 10^6 $ .

## 输出格式

For each test case, output a single integer — the sum of $ |a| $ over all good pairs of arrays $ (a,b) $ modulo $ 10^9 + 7 $ .

## 说明/提示

In the first testcase, the good pairs of arrays are

- $ ([0, 1], [0, 1]) $ , length = $ 2 $ .
- $ ([0, 1, 1], [0, 0, 1]) $ , length = $ 3 $ .
- $ ([0, 0, 1], [0, 1, 1]) $ , length = $ 3 $ .

Hence the sum of the lengths would be $ {2 + 3 + 3} = 8 $ .

## 样例 #1

### 输入

```
4
1 1
1 2
2 2
100 100
```

### 输出

```
8
26
101
886336572
```



---

---
title: "Laboratory on Pluto"
layout: "post"
diff: 省选/NOI-
pid: CF1775F
tag: ['动态规划 DP', '组合数学', '构造']
---

# Laboratory on Pluto

## 题目描述

As you know, Martian scientists are actively engaged in space research. One of the highest priorities is Pluto. In order to study this planet in more detail, it was decided to build a laboratory on Pluto.

It is known that the lab will be built of $ n $ square blocks of equal size. For convenience, we will assume that Pluto's surface is a plane divided by vertical and horizontal lines into unit squares. Each square is either occupied by a lab block or not, and only $ n $ squares are occupied.

Since each block is square, it has four walls. If a wall is adjacent to another block, it is considered inside, otherwise — outside.

Pluto is famous for its extremely cold temperatures, so the outside walls of the lab must be insulated. One unit of insulation per exterior wall would be required. Thus, the greater the total length of the outside walls of the lab (i. e., its perimeter), the more insulation will be needed.

Consider the lab layout in the figure below. It shows that the lab consists of $ n = 33 $ blocks, and all the blocks have a total of $ 24 $ outside walls, i. e. $ 24 $ units of insulation will be needed.

You should build the lab optimally, i. e., minimize the amount of insulation. On the other hand, there may be many optimal options, so scientists may be interested in the number of ways to build the lab using the minimum amount of insulation, modulo a prime number $ m $ .

Two ways are considered the same if they are the same when overlapping without turning. Thus, if a lab plan is rotated by $ 90^{\circ} $ , such a new plan can be considered a separate way.

To help scientists explore Pluto, you need to write a program that solves these difficult problems.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/19a2731aaaa55a0f9a8048f01dd79ff768ce23d2.png)

## 输入格式

The first line contains two integers $ t $ and $ u $ ( $ 1 \le t \le 2\cdot 10^5 $ , $ 1 \le u \le 2 $ ) — the number of test cases and the test type. If $ u=1 $ , you need to find any way to build the lab in an optimal way, and if $ u=2 $ , you need to calculate the number of ways to do it.

If $ u=2 $ , then in the following line of input there is a prime integer $ m $ ( $ 10^8 \le m \le 10^9 + 9 $ ), modulo which you need to calculate the number of ways.

Each of the following $ t $ lines of input contains a description of a test case consisting of one integer $ n $ ( $ 1 \le n \le 4\cdot 10^5 $ ) — the number of blocks the lab should consist of.

It is guaranteed that if $ u=1 $ , then the sum of $ n $ on all test cases does not exceed $ 8\cdot10^5 $ .

## 输出格式

For each test case, output the answers in the format below, separating them with a newline. The output format depends on $ u $ in the input data.

If $ u=1 $ , in the first line you need to print two integers $ h $ and $ w $ —the height and width of the area in which the lab should be built. Then, in each of the following $ h $ lines, you must output a line $ s_i $ consisting of $ w $ characters "\#" and ".". If the $ j $ -th character of the row $ s_i $ is "\#", then the corresponding square must contain a block of laboratory, otherwise, it is considered empty. Thus, we get a matrix of symbols. The condition must also be met that the first and last rows of the matrix, as well as the first and last columns, must have at least one character "\#", otherwise we could output the same lab layout, but with smaller $ h $ and $ w $ . If there are many options to build an optimal lab, you can print any of them.

If $ u=2 $ , you need to print two integers $ p $ and $ c $ — the number of outside walls in an optimal lab, and the remainder of the number of ways by prime modulo $ m $ .

## 说明/提示

Consider the second example.

If $ n=1 $ , the only way to build a lab is to place a single block. In this case, the perimeter will be equal to four.

When $ n=2 $ , you must place two blocks side by side. This can be done either vertically or horizontally, so there are two ways. It is easy to see that the lab has six outside walls in this case.

For $ n=7 $ , all the $ 22 $ optimal plans are shown in the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/2d61b154960a5ef9890728641d5e6f811e5f6274.png)

## 样例 #1

### 输入

```
3 1
1
2
7
```

### 输出

```
1 1
#
1 2
##
2 4
.###
####
```

## 样例 #2

### 输入

```
3 2
1000000007
1
2
7
```

### 输出

```
4 1
6 2
12 22
```



---

---
title: "Bracket Insertion"
layout: "post"
diff: 省选/NOI-
pid: CF1781F
tag: ['动态规划 DP', '组合数学', '前缀和', '概率论']
---

# Bracket Insertion

## 题目描述

Vika likes playing with bracket sequences. Today she wants to create a new bracket sequence using the following algorithm. Initially, Vika's sequence is an empty string, and then she will repeat the following actions $ n $ times:

- Choose a place in the current bracket sequence to insert new brackets uniformly at random. If the length of the current sequence is $ k $ , then there are $ k+1 $ such places: before the first bracket, between the first and the second brackets, $ \ldots $ , after the $ k $ -th bracket. In particular, there is one such place in an empty bracket sequence.
- Choose string "()" with probability $ p $ or string ")(" with probability $ 1 - p $ and insert it into the chosen place. The length of the bracket sequence will increase by $ 2 $ .

A bracket sequence is called regular if it is possible to obtain a correct arithmetic expression by inserting characters '+' and '1' into it. For example, sequences "(())()", "()", and "(()(()))" are regular, while ")(", "(()", and "(()))(" are not.

Vika wants to know the probability that her bracket sequence will be a regular one at the end. Help her and find this probability modulo $ 998\,244\,353 $ (see Output section).

## 输入格式

The only line contains two integers $ n $ and $ q $ ( $ 1 \le n \le 500 $ ; $ 0 \le q \le 10^4 $ ). Here $ n $ is equal to the number of bracket insertion operations, and the probability that Vika chooses string "()" on every step of the algorithm is equal to $ p = q \cdot 10^{-4} $ .

## 输出格式

Print the probability that Vika's final bracket sequence will be regular, modulo $ 998\,244\,353 $ .

Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first example, Vika will get a regular bracket sequence () with probability $ p = \frac{3}{4} $ , and she will get an irregular bracket sequence )( with probability $ 1 - p = \frac{1}{4} $ . The sought probability is $ \frac{3}{4} $ , and $ 249\,561\,089 \cdot 4 \equiv 3 \pmod{998\,244\,353} $ .

In the second example, the sought probability is $ \frac{11}{25} $ .

## 样例 #1

### 输入

```
1 7500
```

### 输出

```
249561089
```

## 样例 #2

### 输入

```
2 6000
```

### 输出

```
519087064
```

## 样例 #3

### 输入

```
5 4000
```

### 输出

```
119387743
```



---

---
title: "Wooden Spoon"
layout: "post"
diff: 省选/NOI-
pid: CF1784D
tag: ['数学', '组合数学', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---

# Wooden Spoon

## 题目描述

$ 2^n $ people, numbered with distinct integers from $ 1 $ to $ 2^n $ , are playing in a single elimination tournament. The bracket of the tournament is a full binary tree of height $ n $ with $ 2^n $ leaves.

When two players meet each other in a match, a player with the smaller number always wins. The winner of the tournament is the player who wins all $ n $ their matches.

A virtual consolation prize "Wooden Spoon" is awarded to a player who satisfies the following $ n $ conditions:

- they lost their first match;
- the player who beat them lost their second match;
- the player who beat that player lost their third match;
- $ \ldots $ ;
- the player who beat the player from the previous condition lost the final match of the tournament.

It can be shown that there is always exactly one player who satisfies these conditions.

Consider all possible $ (2^n)! $ arrangements of players into the tournament bracket. For each player, find the number of these arrangements in which they will be awarded the "Wooden Spoon", and print these numbers modulo $ 998\,244\,353 $ .

## 输入格式

The only line contains a single integer $ n $ ( $ 1 \le n \le 20 $ ) — the size of the tournament.

There are $ 20 $ tests in the problem: in the first test, $ n = 1 $ ; in the second test, $ n = 2 $ ; $ \ldots $ ; in the $ 20 $ -th test, $ n = 20 $ .

## 输出格式

Print $ 2^n $ integers — the number of arrangements in which the "Wooden Spoon" is awarded to players $ 1, 2, \ldots, 2^n $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the "Wooden Spoon" is always awarded to player $ 2 $ .

In the second example, there are $ 8 $ arrangements where players $ 1 $ and $ 4 $ meet each other in the first match, and in these cases, the "Wooden Spoon" is awarded to player $ 3 $ . In the remaining $ 16 $ arrangements, the "Wooden Spoon" is awarded to player $ 4 $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
0
2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
0
0
8
16
```

## 样例 #3

### 输入

```
3
```

### 输出

```
0
0
0
1536
4224
7680
11520
15360
```



---

---
title: "Graph Coloring (easy version)"
layout: "post"
diff: 省选/NOI-
pid: CF1792F1
tag: ['动态规划 DP', '图论', '组合数学']
---

# Graph Coloring (easy version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 输入格式

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^3 $ ).

## 输出格式

Print one integer — the number of ways to paint the graph, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
50
```

## 样例 #3

### 输入

```
100
```

### 输出

```
878752271
```

## 样例 #4

### 输入

```
1337
```

### 输出

```
520628749
```



---

---
title: "Count Voting"
layout: "post"
diff: 省选/NOI-
pid: CF1799G
tag: ['动态规划 DP', '组合数学', '容斥原理']
---

# Count Voting

## 题目描述

There are $ n $ people that will participate in voting. Each person has exactly one vote.

 $ i $ -th person has a team $ t_i $ ( $ 1 \leq t_i \leq n $ ) where $ t_i = t_j $ means $ i $ , $ j $ are in the same team. By the rules each person should vote for the person from the different team. Note that it automatically means that each person can't vote for himself.

Each person knows the number of votes $ c_i $ he wants to get. How many possible votings exists, such that each person will get the desired number of votes? Due to this number can be big, find it by modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 200 $ ) — the number of people.

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 0 \leq c_i \leq n $ ) — desired number of votes. It is guaranteed, that $ \sum\limits_{i=1}^{n} c_i = n $ .

The third line contains $ n $ integers $ t_1, t_2, \ldots, t_n $ ( $ 1 \leq t_i \leq n $ ) — team numbers.

## 输出格式

Print a single integer — the number of possible votings by modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test there are two possible votings: $ (2, 3, 1) $ , $ (3, 1, 2) $ .

In the third test there are five possible votings: $ (3, 3, 2, 2, 1) $ , $ (2, 3, 2, 3, 1) $ , $ (3, 3, 1, 2, 2) $ , $ (3, 1, 2, 3, 2) $ , $ (2, 3, 1, 3, 2) $ .

## 样例 #1

### 输入

```
3
1 1 1
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 0 1 0 2
1 2 3 4 5
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5
1 2 2 0 0
3 5 4 3 4
```

### 输出

```
5
```



---

---
title: "Balanced Subsequences"
layout: "post"
diff: 省选/NOI-
pid: CF1924D
tag: ['组合数学', 'Catalan 数']
---

# Balanced Subsequences

## 题目描述

A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters '+' and '1'. For example, sequences '(())()', '()', and '(()(()))' are balanced, while ')(', '(()', and '(()))(' are not.

A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

You are given three integers $ n $ , $ m $ and $ k $ . Find the number of sequences consisting of $ n $ '(' and $ m $ ')', such that the longest balanced subsequence is of length $ 2 \cdot k $ . Since the answer can be large calculate it modulo $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 3 \cdot 10^3 $ ). Description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n, m, k \le 2 \cdot 10^3 $ )

## 输出格式

For each test case, print one integer — the answer to the problem.

## 说明/提示

For the first test case "()()", "(())" are the $ 2 $ sequences

For the second test case no sequence is possible.

For the third test case ")((()", ")(()(", ")()((", "())((" are the $ 4 $ sequences.

## 样例 #1

### 输入

```
3
2 2 2
3 2 3
3 2 1
```

### 输出

```
2
0
4
```



---

---
title: "2..3...4.... Wonderful! Wonderful!"
layout: "post"
diff: 省选/NOI-
pid: CF1930E
tag: ['组合数学', '排列组合']
---

# 2..3...4.... Wonderful! Wonderful!

## 题目描述

Stack has an array $ a $ of length $ n $ such that $ a_i = i $ for all $ i $ ( $ 1 \leq i \leq n $ ). He will select a positive integer $ k $ ( $ 1 \leq k \leq \lfloor \frac{n-1}{2} \rfloor $ ) and do the following operation on $ a $ any number (possibly $ 0 $ ) of times.

- Select a subsequence $ ^\dagger $ $ s $ of length $ 2 \cdot k + 1 $ from $ a $ . Now, he will delete the first $ k $ elements of $ s $ from $ a $ . To keep things perfectly balanced (as all things should be), he will also delete the last $ k $ elements of $ s $ from $ a $ .

Stack wonders how many arrays $ a $ can he end up with for each $ k $ ( $ 1 \leq k \leq \lfloor \frac{n-1}{2} \rfloor $ ). As Stack is weak at counting problems, he needs your help.

Since the number of arrays might be too large, please print it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deleting several (possibly, zero or all) elements. For example, $ [1, 3] $ , $ [1, 2, 3] $ and $ [2, 3] $ are subsequences of $ [1, 2, 3] $ . On the other hand, $ [3, 1] $ and $ [2, 1, 3] $ are not subsequences of $ [1, 2, 3] $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 10^6 $ ) — the length of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test, on a new line, print $ \lfloor \frac{n-1}{2} \rfloor $ space-separated integers — the $ i $ -th integer representing the number of arrays modulo $ 998\,244\,353 $ that Stack can get if he selects $ k=i $ .

## 说明/提示

In the first test case, two $ a $ are possible for $ k=1 $ :

- $ [1,2,3] $ ;
- $ [2] $ .

In the second test case, four $ a $ are possible for $ k=1 $ :

- $ [1,2,3,4] $ ;
- $ [1,3] $ ;
- $ [2,3] $ ;
- $ [2,4] $ .

In the third test case, two $ a $ are possible for $ k=2 $ :

- $ [1,2,3,4,5] $ ;
- $ [3] $ .

## 样例 #1

### 输入

```
4
3
4
5
10
```

### 输出

```
2 
4 
10 2 
487 162 85 10
```



---

---
title: "Carousel of Combinations"
layout: "post"
diff: 省选/NOI-
pid: CF1957E
tag: ['数论', '组合数学']
---

# Carousel of Combinations

## 题目描述

You are given an integer $ n $ . The function $ C(i,k) $ represents the number of distinct ways you can select $ k $ distinct numbers from the set { $ 1, 2, \ldots, i $ } and arrange them in a circle $ ^\dagger $ .

Find the value of 
$$
\sum\limits_{i=1}^n \sum\limits_{j=1}^i \left( C(i,j) \bmod j \right)
$$
Here, the operation  $ x \\bmod y $  denotes the remainder from dividing  $ x $  by  $ y $ .</p><p>Since this value can be very large, find it modulo  $ 10^9+7 $ .</p><p> $ ^\\dagger $  In a circular arrangement, sequences are considered identical if one can be rotated to match the other. For instance,  $ \[1, 2, 3\] $  and  $ \[2, 3, 1\]$$$ are equivalent in a circle.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ).

## 输出格式

For each test case, output a single integer on a new line — the value of the expression to be calculated modulo $ 10^9+7 $ .

## 说明/提示

In the first test case, $ C(1,1) \bmod 1 = 0 $ .

In the second test case:

- $ C(1,1)=1 $ (the arrangements are: $ [1] $ );
- $ C(2,1)=2 $ (the arrangements are: $ [1] $ , $ [2] $ );
- $ C(2,2)=1 $ (the arrangements are: $ [1, 2] $ );
- $ C(3,1)=3 $ (the arrangements are: $ [1] $ , $ [2] $ , $ [3] $ );
- $ C(3,2)=3 $ (the arrangements are: $ [1, 2] $ , $ [2, 3] $ , $ [3, 1] $ );
- $ C(3,3)=2 $ (the arrangements are: $ [1, 2, 3] $ , $ [1, 3, 2] $ ).

 In total, $ \left(C(1,1) \bmod 1\right) + \left(C(2,1) \bmod 1\right) + \left(C(2,2) \bmod 2\right) + \left(C(3,1) \bmod 1\right) + \left(C(3,2) \bmod 2\right) + \left(C(3,3) \bmod 3\right) = 4 $ .

## 样例 #1

### 输入

```
4
1
3
6
314159
```

### 输出

```
0
4
24
78926217
```



---

---
title: "The Destruction of the Universe (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2030G1
tag: ['组合数学', '排列组合']
---

# The Destruction of the Universe (Easy Version)

## 题目描述

这是问题的简单版本，满足 $ n \leq 5000 $。如果两个版本的问题都被解决，才可以进行挑战。

猩猩是强大的生物，它们只需要 $1$ 个单位时间就能摧毁宇宙中每一个脆弱的星球！

宇宙中有 $n$ 个星球。每个星球在一个区间 $[l, r]$ 内是脆弱的，期间随时可能被猩猩摧毁。猩猩可以把任意一个星球的脆弱区间扩展 $1$ 个单位。

具体来说，如果对某个星球 $p$ 的脆弱区间 $[l_p, r_p]$ 进行扩展，结果可以是 $[l_p - 1, r_p]$ 或 $[l_p, r_p + 1]$ 中的任一个。

给定一组星球，如果它们的所有脆弱区间中至少有一个共同点，那么这组星球就能被摧毁。我们把这样一组星球的“得分”定义为实现摧毁所需的最小扩展次数。

猩猩关注的是宇宙中所有非空星球子集的得分之和。由于可能结果非常大，请输出答案对 $998\,244\,353$ 取模后的结果。

## 输入格式

第一行是一个整数 $t$（$1 \leq t \leq 1000$）——测试用例的数量。

每个测试用例的第一行有一个整数 $n$（$1 \leq n \leq 5000$）——星球的数量。

接下来的 $n$ 行中，每行包含两个整数 $l_i$ 和 $r_i$（$1 \leq l_i \leq r_i \leq n$），表示第 $i$ 个星球的初始脆弱区间。

保证所有测试用例中，星球数量的总和不超过 $5000$。

## 输出格式

对于每个测试用例，输出一个整数——所有非空星球子集的得分之和，对 $998\,244\,353$ 取模。

## 说明/提示

以第一个测试用例为例，需考虑以下七个非空子集：

- 对于子集 $\{[1,1]\}, \{[2,3]\}, \{[3,3]\}$，得分为 $0$。
- 对于子集 $\{[2,3], [3,3]\}$，得分为 $0$，因为点 $3$ 已经位于这两个星球的脆弱区间之内。
- 对于子集 $\{[1,1], [2,3]\}$，得分为 $1$。通过一次操作，将第二个星球的脆弱区间改为 $[1,3]$，这样两个星球的脆弱区间都包含点 $1$。
- 对于子集 $\{[1,1], [3,3]\}$，得分为 $2$。通过两次操作，将第一个星球的脆弱区间改为 $[1,3]$，使得两个星球的区间都包含点 $3$。
- 对于子集 $\{[1,1], [2,3], [3,3]\}$，得分为 $2$。通过一次操作把第一个星球的区间改为 $[1,2]$，再用一次操作把第三个星球的区间改为 $[2,3]$，这样三个星球都包含点 $2$。

所以，第一个测试用例中，所有非空子集的得分之和为 $0 \times 4 + 1 \times 1 + 2 \times 2 = 5$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5
```

### 输出

```
5
6
24
```



---

---
title: "The Destruction of the Universe (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2030G2
tag: ['组合数学', '排列组合', '前缀和']
---

# The Destruction of the Universe (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, $ n \leq 10^6 $ . You can only make hacks if both versions of the problem are solved.

Orangutans are powerful beings—so powerful that they only need $ 1 $ unit of time to destroy every vulnerable planet in the universe!

There are $ n $ planets in the universe. Each planet has an interval of vulnerability $ [l, r] $ , during which it will be exposed to destruction by orangutans. Orangutans can also expand the interval of vulnerability of any planet by $ 1 $ unit.

Specifically, suppose the expansion is performed on planet $ p $ with interval of vulnerability $ [l_p, r_p] $ . Then, the resulting interval of vulnerability may be either $ [l_p - 1, r_p] $ or $ [l_p, r_p + 1] $ .

Given a set of planets, orangutans can destroy all planets if the intervals of vulnerability of all planets in the set intersect at least one common point. Let the score of such a set denote the minimum number of expansions that must be performed.

Orangutans are interested in the sum of scores of all non-empty subsets of the planets in the universe. As the answer can be large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 10^6 $ ) — the number of planets in the universe.

The following $ n $ lines contain two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i \leq r_i \leq n $ ) — the initial interval of vulnerability of the $ i $ -th planet.

It is guaranteed that the sum of $ n $ does not exceed $ 10^6 $ over all test cases.

## 输出格式

For each test case, output an integer — the sum of scores to destroy all non-empty subsets of the planets in the universe, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, there are seven non-empty subsets of planets we must consider:

- For each of the subsets $ \{[1,1]\}, \{[2,3]\}, \{[3,3]\} $ , the score is $ 0 $ .
- For the subset $ \{[2,3], [3,3]\} $ , the score is $ 0 $ , because the point $ 3 $ is already contained in both planets' interval of vulnerability.
- For the subset $ \{[1,1], [2,3]\} $ , the score is $ 1 $ . By using one operation on changing the interval of vulnerability of the second planet to be $ [1,3] $ , the two planets now both have the point $ 1 $ in their interval.
- For the subset $ \{[1,1], [3,3]\} $ , the score is $ 2 $ . By using two operations on changing the interval of vulnerability of the first planet to be $ [1,3] $ , the two planets now both have the point $ 3 $ in their interval.
- For the subset $ \{[1,1], [2,3], [3,3]\} $ , the score is $ 2 $ . By using one operation on changing the interval of vulnerability of the first planet to be $ [1,2] $ and one operation on changing the interval of vulnerability of the third planet to $ [2,3] $ , all three planets will have the point $ 2 $ in their interval.

The sum of scores of all non-empty subsets of the first testcase is $ 0 \cdot 4 + 1 \cdot 1 + 2\cdot2 = 5 $ .

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5
```

### 输出

```
5
6
24
```



---

---
title: "Club of Young Aircraft Builders (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF2066D2
tag: ['动态规划 DP', '组合数学']
---

# Club of Young Aircraft Builders (hard version)

## 题目描述

这是该问题的困难版本。各版本间的区别在于此版本中不要求所有 $a_i = 0$。只有当您解决了该问题的所有版本时才能进行 hack。

有一栋 $n$ 层的建筑物，楼层从下到上编号为 $1$ 至 $n$。每层恰好住着一位居民。

今天全体居民有一个重要目标：共同发射至少 $c$ 架纸飞机。居民们将依次发射飞机。当第 $i$ 层的居民发射一架飞机时，从第 $1$ 层到第 $i$ 层的所有居民都能看到它降落到地面的过程。如果从第 $i$ 层居民的视角看，已有至少 $c$ 架飞机被发射，则该居民自己不会再发射更多飞机。已知到当天结束时，从每位居民的视角看至少发射了 $c$ 架飞机，且总共发射了 $m$ 架飞机。

您仔细记录了这次快闪活动，记录了每架飞机的发射者所在楼层。遗憾的是，关于部分飞机的具体发射者信息已经丢失。请找出填补空缺信息使其可信的方案数。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

也可能您的记录存在错误，导致无法恢复任何有效信息。此时答案视为 $0$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。随后为各测试用例的描述。

每个测试用例的第一行包含三个整数 $n, c, m$（$1 \le n \le 100$，$1 \le c \le 100$，$c \le m \le n \cdot c$）——建筑物的层数、所需最小飞机数、实际发射的飞机数。

每个测试用例的第二行包含 $m$ 个整数 $a_1, a_2, \ldots, a_m$（$0 \le a_i \le n$）——$a_i$ 表示发射第 $i$ 架飞机的居民所在楼层；$a_i = 0$ 表示空缺。

保证所有测试用例的 $m$ 值之和不超过 $10^4$。

## 输出格式

对于每个测试用例，输出用 $1$ 至 $n$ 填补空缺信息使其可信的方案数对 $10^9 + 7$ 取模后的结果。

## 说明/提示

第一个测试样例中，所有六种可能的填补方案如下：
1. $[1, 1, 3, 3]$
2. $[1, 2, 3, 3]$
3. $[1, 3, 2, 3]$
4. $[2, 1, 3, 3]$
5. $[2, 2, 3, 3]$
6. $[3, 1, 2, 3]$

注意数组 $[2, 3, 1, 3]$ 不是有效方案，因为第三架飞机不可能由第 $1$ 层的居民发射——从他们的视角看，当时已有 $c = 2$ 架飞机被发射。

同样地，数组 $[1, 1, 2, 3]$ 也不是有效方案，因为从第 $3$ 层居民的视角看，仅发射了 $1$ 架飞机，而 $c = 2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
3 2 4
0 0 0 0
5 5 7
0 0 0 0 0 0 0
6 1 3
2 0 0
2 3 5
0 0 1 0 2
3 3 4
3 3 3 0
2 1 2
0 1
2 1 2
0 2
5 3 12
0 0 1 0 2 4 0 0 0 5 0 5
```

### 输出

```
6
190
3
2
0
0
1
14
```



---

---
title: "XOR Matrix"
layout: "post"
diff: 省选/NOI-
pid: CF2075E
tag: ['数位 DP', '组合数学', '位运算']
---

# XOR Matrix

## 题目描述

对于两个数组 $a = [a_1, a_2, \dots, a_n]$ 和 $b = [b_1, b_2, \dots, b_m]$，我们定义大小为 $n \times m$ 的异或矩阵 $X$，其中对于每对 $(i,j)$（$1 \le i \le n$；$1 \le j \le m$），有 $X_{i,j} = a_i \oplus b_j$。符号 $\oplus$ 表示按位异或运算。

给定四个整数 $n, m, A, B$。请计算满足以下条件的数组对 $(a, b)$ 的数量：
- 数组 $a$ 包含 $n$ 个整数，每个整数的取值范围是 $0$ 到 $A$；
- 数组 $b$ 包含 $m$ 个整数，每个整数的取值范围是 $0$ 到 $B$；
- 由这些数组生成的异或矩阵中，不同值的数量不超过两个。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例由一行组成，包含四个整数 $n, m, A, B$（$2 \le n, m, A, B \le 2^{29} - 1$）。

## 输出格式

对于每个测试用例，输出一个整数——满足所有三个条件的数组对 $(a, b)$ 的数量。由于该数值可能非常大，请输出其对 $998244353$ 取模的结果。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
2 2 2 2
2 3 4 5
5 7 4 3
1337 42 1337 42
4 2 13 37
536870902 536370902 536390912 466128231
```

### 输出

```
57
864
50360
439988899
112000
732195491
```



---

---
title: "Different Subsets For All Tuples"
layout: "post"
diff: 省选/NOI-
pid: CF660E
tag: ['组合数学']
---

# Different Subsets For All Tuples

## 题目描述

For a sequence $ a $ of $ n $ integers between $ 1 $ and $ m $ , inclusive, denote $ f(a) $ as the number of distinct subsequences of $ a $ (including the empty subsequence).

You are given two positive integers $ n $ and $ m $ . Let $ S $ be the set of all sequences of length $ n $ consisting of numbers from $ 1 $ to $ m $ . Compute the sum $ f(a) $ over all $ a $ in $ S $ modulo $ 10^{9}+7 $ .

## 输入格式

The only line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{6} $ ) — the number of elements in arrays and the upper bound for elements.

## 输出格式

Print the only integer $ c $ — the desired sum modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
1 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
2 2

```

### 输出

```
14

```

## 样例 #3

### 输入

```
3 3

```

### 输出

```
174

```



---

---
title: "Anton and School - 2"
layout: "post"
diff: 省选/NOI-
pid: CF785D
tag: ['组合数学']
---

# Anton and School - 2

## 题目描述

As you probably know, Anton goes to school. One of the school subjects that Anton studies is Bracketology. On the Bracketology lessons students usually learn different sequences that consist of round brackets (characters "(" and ")" (without quotes)).

On the last lesson Anton learned about the regular simple bracket sequences (RSBS). A bracket sequence $ s $ of length $ n $ is an RSBS if the following conditions are met:

- It is not empty (that is $ n≠0 $ ).
- The length of the sequence is even.
- First ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to "(".
- Last ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to ")".

For example, the sequence "((()))" is an RSBS but the sequences "((())" and "(()())" are not RSBS.

Elena Ivanovna, Anton's teacher, gave him the following task as a homework. Given a bracket sequence $ s $ . Find the number of its distinct subsequences such that they are RSBS. Note that a subsequence of $ s $ is a string that can be obtained from $ s $ by deleting some of its elements. Two subsequences are considered distinct if distinct sets of positions are deleted.

Because the answer can be very big and Anton's teacher doesn't like big numbers, she asks Anton to find the answer modulo $ 10^{9}+7 $ .

Anton thought of this task for a very long time, but he still doesn't know how to solve it. Help Anton to solve this task and write a program that finds the answer for it!

## 输入格式

The only line of the input contains a string $ s $ — the bracket sequence given in Anton's homework. The string consists only of characters "(" and ")" (without quotes). It's guaranteed that the string is not empty and its length doesn't exceed $ 200000 $ .

## 输出格式

Output one number — the answer for the task modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample the following subsequences are possible:

- If we delete characters at the positions $ 1 $ and $ 5 $ (numbering starts with one), we will get the subsequence "(())".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".

The rest of the subsequnces are not RSBS. So we got $ 6 $ distinct subsequences that are RSBS, so the answer is $ 6 $ .

## 样例 #1

### 输入

```
)(()()

```

### 输出

```
6

```

## 样例 #2

### 输入

```
()()()

```

### 输出

```
7

```

## 样例 #3

### 输入

```
)))

```

### 输出

```
0

```



---

