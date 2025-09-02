---
title: "Non-equal Neighbours"
layout: "post"
diff: 提高+/省选-
pid: CF1585F
tag: ['动态规划 DP', '单调队列', '容斥原理']
---

# Non-equal Neighbours

## 题目描述

You are given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ . Your task is to calculate the number of arrays of $ n $ positive integers $ b_1, b_2, \ldots, b_n $ such that:

- $ 1 \le b_i \le a_i $ for every $ i $ ( $ 1 \le i \le n $ ), and
- $ b_i \neq b_{i+1} $ for every $ i $ ( $ 1 \le i \le n - 1 $ ).

The number of such arrays can be very large, so print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

Print the answer modulo $ 998\,244\,353 $ in a single line.

## 说明/提示

In the first test case possible arrays are $ [1, 2, 1] $ and $ [2, 1, 2] $ .

In the second test case possible arrays are $ [1, 2] $ , $ [1, 3] $ , $ [2, 1] $ and $ [2, 3] $ .

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
2 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
0
```



---

---
title: "Graph Cost"
layout: "post"
diff: 提高+/省选-
pid: CF1731E
tag: ['贪心', '容斥原理']
---

# Graph Cost

## 题目描述

You are given an initially empty undirected graph with $ n $ nodes, numbered from $ 1 $ to $ n $ (i. e. $ n $ nodes and $ 0 $ edges). You want to add $ m $ edges to the graph, so the graph won't contain any self-loop or multiple edges.

If an edge connecting two nodes $ u $ and $ v $ is added, its weight must be equal to the greatest common divisor of $ u $ and $ v $ , i. e. $ \gcd(u, v) $ .

In order to add edges to the graph, you can repeat the following process any number of times (possibly zero):

- choose an integer $ k \ge 1 $ ;
- add exactly $ k $ edges to the graph, each having a weight equal to $ k + 1 $ . Adding these $ k $ edges costs $ k + 1 $ in total.

 Note that you can't create self-loops or multiple edges. Also, if you can't add $ k $ edges of weight $ k + 1 $ , you can't choose such $ k $ .For example, if you can add $ 5 $ more edges to the graph of weight $ 6 $ , you may add them, and it will cost $ 6 $ for the whole pack of $ 5 $ edges. But if you can only add $ 4 $ edges of weight $ 6 $ to the graph, you can't perform this operation for $ k = 5 $ .

Given two integers $ n $ and $ m $ , find the minimum total cost to form a graph of $ n $ vertices and exactly $ m $ edges using the operation above. If such a graph can't be constructed, output $ -1 $ .

Note that the final graph may consist of several connected components.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 10^6 $ ; $ 1 \leq m \leq \frac{n(n-1)}{2} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print the minimum cost to build the graph, or $ -1 $ if you can't build such a graph.

## 说明/提示

In the first test case, we can add an edge between the vertices $ 2 $ and $ 4 $ with $ \gcd = 2 $ . This is the only possible way to add $ 1 $ edge that will cost $ 2 $ .

In the second test case, there is no way to add $ 10 $ edges, so the answer is $ -1 $ .

In the third test case, we can add the following edges:

- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 2 $ and $ 4 $ ( $ \gcd(2, 4) = 2 $ ). Cost: $ 2 $ ;
- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 4 $ and $ 6 $ ( $ \gcd(4, 6) = 2 $ ). Cost: $ 2 $ ;
- $ k = 2 $ : edges of weight $ 3 $ : $ (3, 6) $ and $ (3, 9) $ ( $ \gcd(3, 6) = \gcd(3, 9) = 3 $ ). Cost: $ 3 $ .

 As a result, we added $ 1 + 1 + 2 = 4 $ edges with total cost $ 2 + 2 + 3 = 7 $ , which is the minimal possible cost.

## 样例 #1

### 输入

```
4
4 1
6 10
9 4
10 11
```

### 输出

```
2
-1
7
21
```



---

---
title: "Khayyam's Royal Decree (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2034F1
tag: ['动态规划 DP', '容斥原理']
---

# Khayyam's Royal Decree (Easy Version)

## 题目描述

这是本题的简单版本。两个版本的唯一区别在于 $k$ 和 $\sum k$ 的限制。

Khayyam 有一个**宝箱**，**宝箱**里初始有 $n$ 个红宝石和 $m$ 个蓝宝石。一个红宝石的价值为 $2$，一个蓝宝石的价值为 $1$。他还有一个**背包**，初始为空。另外，他还有 $k$ 张卷轴，第 $i$ 张卷轴上有数对 $(r_i,b_i)$。

Khayyam 将进行一个游戏，游戏共 $n+m$ 轮，每轮流程如下：

1. Khayyam 从**宝箱**中等概率随机拿出一个宝石。
2. 他将这个宝石放入**背包**中。
3. 若存在一张卷轴 $i$，使得**宝箱**中恰有 $r_i$ 个红宝石和 $b_i$ 个蓝宝石，将所有**背包**里的宝石的价值翻倍。

一个宝石的价值可以被多次翻倍。

求游戏结束时 Khayyam **背包**里宝石的价值总和的期望值，对 $998244353$ 取模。

## 输入格式

多测，第一行一个整数 $T$ 表示数据组数。

每组数据的第一行三个整数 $n,m,k$。

接下来 $k$ 行，每行两个整数 $r_i,b_i$。

保证 $1\le T\le 500$，$1\le n,m,\sum n,\sum m\le 2\times 10^5$，$1\le k,\sum k\le 500$。

保证 $0\le r_i\le n$，$0\le b_i\le m$，$1\le r_i+b_i\le n+m-1$，且 $(r_i,b_i)$ 两两不同。

## 输出格式

一行一个整数，表示答案对 $998244353$ 取模的值。

### 样例解释

对于第一组数据，最终背包里总会有 $3$ 个红宝石和 $4$ 个蓝宝石，不会有卷轴被触发。因此背包里宝石的总价值总是 $2\times 3+1\times 4=10$。

对于第二组数据：

+ 有 $\dfrac{1}{2}$ 概率，Khayyam 先拿出红宝石再拿出蓝宝石，不会有卷轴被触发，总价值为 $3$；
+ 有 $\dfrac{1}{2}$ 概率，Khayyam 先拿出蓝宝石再拿出红宝石，卷轴 $1$ 会被触发，蓝宝石的价值翻倍，总价值为 $4$。

因此总价值的期望是 $\dfrac{1}{2}\times 3+\dfrac{1}{2}\times 4=\dfrac{7}{2}\equiv 499122180\pmod {998244353}$。

## 样例 #1

### 输入

```
5
3 4 0
1 1 1
1 0
3 3 2
1 1
2 2
3 3 2
2 1
1 2
10 4 5
1 0
8 0
6 4
0 2
7 4
```

### 输出

```
10
499122180
798595498
149736666
414854846
```



---

---
title: "Yaroslav and Two Strings"
layout: "post"
diff: 提高+/省选-
pid: CF296B
tag: ['动态规划 DP', '容斥原理']
---

# Yaroslav and Two Strings

## 题目描述

Yaroslav thinks that two strings $ s $ and $ w $ , consisting of digits and having length $ n $ are non-comparable if there are two numbers, $ i $ and $ j $ $ (1<=i,j<=n) $ , such that $ s_{i}&gt;w_{i} $ and $ s_{j}&lt;w_{j} $ . Here sign $ s_{i} $ represents the $ i $ -th digit of string $ s $ , similarly, $ w_{j} $ represents the $ j $ -th digit of string $ w $ .

A string's template is a string that consists of digits and question marks ("?").

Yaroslav has two string templates, each of them has length $ n $ . Yaroslav wants to count the number of ways to replace all question marks by some integers in both templates, so as to make the resulting strings incomparable. Note that the obtained strings can contain leading zeroes and that distinct question marks can be replaced by distinct or the same integers.

Help Yaroslav, calculate the remainder after dividing the described number of ways by $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ — the length of both templates. The second line contains the first template — a string that consists of digits and characters "?". The string's length equals $ n $ . The third line contains the second template in the same format.

## 输出格式

In a single line print the remainder after dividing the answer to the problem by number $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

The first test contains no question marks and both strings are incomparable, so the answer is $ 1 $ .

The second test has no question marks, but the given strings are comparable, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
2
90
09

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
11
55

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5
?????
?????

```

### 输出

```
993531194

```



---

---
title: "Iahub and Permutations"
layout: "post"
diff: 提高+/省选-
pid: CF340E
tag: ['动态规划 DP', '容斥原理', '逆元']
---

# Iahub and Permutations

## 题目描述

Iahub is so happy about inventing bubble sort graphs that he's staying all day long at the office and writing permutations. Iahubina is angry that she is no more important for Iahub. When Iahub goes away, Iahubina comes to his office and sabotage his research work.

The girl finds an important permutation for the research. The permutation contains $ n $ distinct integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ $ (1<=a_{i}<=n) $ . She replaces some of permutation elements with -1 value as a revenge.

When Iahub finds out his important permutation is broken, he tries to recover it. The only thing he remembers about the permutation is it didn't have any fixed point. A fixed point for a permutation is an element $ a_{k} $ which has value equal to $ k $ $ (a_{k}=k) $ . Your job is to proof to Iahub that trying to recover it is not a good idea. Output the number of permutations which could be originally Iahub's important permutation, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=2000 $ ). On the second line, there are $ n $ integers, representing Iahub's important permutation after Iahubina replaces some values with -1.

It's guaranteed that there are no fixed points in the given permutation. Also, the given sequence contains at least two numbers -1 and each positive number occurs in the sequence at most once. It's guaranteed that there is at least one suitable permutation.

## 输出格式

Output a single integer, the number of ways Iahub could recover his permutation, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

For the first test example there are two permutations with no fixed points are \[2, 5, 4, 3, 1\] and \[5, 1, 4, 3, 2\]. Any other permutation would have at least one fixed point.

## 样例 #1

### 输入

```
5
-1 -1 4 3 -1

```

### 输出

```
2

```



---

---
title: "Jzzhu and Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF449D
tag: ['枚举', '状态合并', '容斥原理']
---

# Jzzhu and Numbers

## 题目描述

Jzzhu have $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ . We will call a sequence of indexes $ i_{1},i_{2},...,i_{k} $ $ (1<=i_{1}<i_{2}<...<i_{k}<=n) $ a group of size $ k $ .

Jzzhu wonders, how many groups exists such that $ a_{i1} $ & $ a_{i2} $ & ... & $ a_{ik}=0 $ $ (1<=k<=n) $ ? Help him and print this number modulo $ 1000000007 $ $ (10^{9}+7) $ . Operation $ x $ & $ y $ denotes bitwise AND operation of two numbers.

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{6}) $ . The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (0<=a_{i}<=10^{6}) $ .

## 输出格式

Output a single integer representing the number of required groups modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
3
2 3 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
4
0 1 2 3

```

### 输出

```
10

```

## 样例 #3

### 输入

```
6
5 2 0 5 2 1

```

### 输出

```
53

```



---

---
title: "Lengthening Sticks"
layout: "post"
diff: 提高+/省选-
pid: CF571A
tag: ['枚举', '容斥原理']
---

# Lengthening Sticks

## 题目描述

You are given three sticks with positive integer lengths of $ a,b $ , and $ c $ centimeters. You can increase length of some of them by some positive integer number of centimeters (different sticks can be increased by a different length), but in total by at most $ l $ centimeters. In particular, it is allowed not to increase the length of any stick.

Determine the number of ways to increase the lengths of some sticks so that you can form from them a non-degenerate (that is, having a positive area) triangle. Two ways are considered different, if the length of some stick is increased by different number of centimeters in them.

## 输入格式

The single line contains $ 4 $ integers $ a,b,c,l $ ( $ 1<=a,b,c<=3·10^{5} $ , $ 0<=l<=3·10^{5} $ ).

## 输出格式

Print a single integer — the number of ways to increase the sizes of the sticks by the total of at most $ l $ centimeters, so that you can make a non-degenerate triangle from it.

## 说明/提示

In the first sample test you can either not increase any stick or increase any two sticks by $ 1 $ centimeter.

In the second sample test you can increase either the first or the second stick by one centimeter. Note that the triangle made from the initial sticks is degenerate and thus, doesn't meet the conditions.

## 样例 #1

### 输入

```
1 1 1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
1 2 3 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
10 2 1 7

```

### 输出

```
0

```



---

---
title: "Unusual Sequences"
layout: "post"
diff: 提高+/省选-
pid: CF900D
tag: ['数论', '莫比乌斯反演', '组合数学', '容斥原理']
---

# Unusual Sequences

## 题目描述

Count the number of distinct sequences $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i} $ ) consisting of positive integers such that $ gcd(a_{1},a_{2},...,a_{n})=x $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF900D/b6b0405f12ef386aeb195f818cd0534bcf4623e0.png). As this number could be large, print the answer modulo $ 10^{9}+7 $ .

 $ gcd $ here means the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor).

## 输入格式

The only line contains two positive integers $ x $ and $ y $ ( $ 1<=x,y<=10^{9} $ ).

## 输出格式

Print the number of such sequences modulo $ 10^{9}+7 $ .

## 说明/提示

There are three suitable sequences in the first test: $ (3,3,3) $ , $ (3,6) $ , $ (6,3) $ .

There are no suitable sequences in the second test.

## 样例 #1

### 输入

```
3 9

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 8

```

### 输出

```
0

```



---

