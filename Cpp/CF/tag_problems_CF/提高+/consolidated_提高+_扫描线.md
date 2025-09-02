---
title: "Microwavable Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF2045I
tag: ['树状数组', '扫描线']
---

# Microwavable Subsequence

## 题目描述

给定一个整数数组 $[A_1, A_2, \dots, A_N]$，数组长度为 $N$。

从数组中移除零个或多个元素，并保持剩余元素的顺序不变，就可以得到一个子序列。例如，$[2, 1, 2]$、$[3, 3]$、$[1]$ 和 $[3, 2, 1, 3, 2]$ 都是数组 $[3, 2, 1, 3, 2]$ 的子序列，而 $[1, 2, 3]$ 不是。

如果某个子序列最多只包含两种不同的数，并且相邻元素不相同，则称为“微波炉”子序列。例如，$[2, 1, 2]$、$[3, 2, 3, 2]$ 以及 $[1]$ 是微波炉子序列，而 $[3, 3]$ 和 $[3, 2, 1, 3, 2]$ 则不是。

函数 $f(x, y)$ 表示数组 $A$ 中元素仅为 $x$ 或 $y$ 的最长微波炉子序列的长度。请计算所有满足 $1 \leq x < y \leq M$ 的 $f(x, y)$ 之和。

## 输入格式

第一行输入两个整数 $N$ 和 $M$，满足 $1 \leq N, M \leq 300,000$。

第二行包含 $N$ 个整数 $A_i$，其中 $1 \leq A_i \leq M$。

## 输出格式

输出一个整数，即所有满足 $1 \leq x < y \leq M$ 的 $f(x, y)$ 的总和。

## 说明/提示

### 样例解释 1

$f(1, 2)$ 的值为 $3$，可以从序列中去掉 $A_1$ 和 $A_4$，得到子序列 $[2, 1, 2]$。$f(1, 3)$ 的值为 $3$，通过去除 $A_2$ 和 $A_5$，得到子序列 $[3, 1, 3]$。$f(2, 3)$ 的值为 $4$，从序列中去除 $A_3$，得到子序列 $[3, 2, 3, 2]$。而 $f(1, 4)$、$f(2, 4)$ 和 $f(3, 4)$ 的值均为 $1$。

### 样例解释 2

$f(1, 2)$ 和 $f(1, 3)$ 的值均为 $1$，而 $f(2, 3)$ 的值是 $0$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5 4
3 2 1 3 2
```

### 输出

```
13
```

## 样例 #2

### 输入

```
3 3
1 1 1
```

### 输出

```
2
```



---

---
title: "Adventurers"
layout: "post"
diff: 提高+/省选-
pid: CF2046C
tag: ['线段树', '二分', '树状数组', '扫描线']
---

# Adventurers

## 题目描述

Once, four Roman merchants met in a Roman mansion to discuss their trading plans. They faced the following problem: they traded the same type of goods, and if they traded in the same city, they would inevitably incur losses. They decided to divide up the cities between them where they would trade.

The map of Rome can be represented in this problem as a plane with certain points marked — the cities of the Roman Empire.

The merchants decided to choose a certain dividing point $ (x_0, y_0) $ . Then, in a city with coordinates $ (x_i, y_i) $ ,

- the first merchant sells goods if $ x_0 \le x_i $ and $ y_0 \le y_i $ ;
- the second merchant sells goods if $ x_0 > x_i $ and $ y_0 \le y_i $ ;
- the third merchant sells goods if $ x_0 \le x_i $ and $ y_0 > y_i $ ;
- the fourth merchant sells goods if $ x_0 > x_i $ and $ y_0 > y_i $ .

The merchants want to choose $ (x_0, y_0) $ in such a way as to maximize the smallest number of cities that any of them gets (i. e., as fair as possible). Please find such a point for them.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 4 \le n \le 10^5 $ ) — the number of cities on the map.

Each of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ -10^9 \le x_i, y_i \le 10^9 $ ) — the coordinates of the cities.

Note that some points may coincide. This is because some cities may be so close that they cannot be distinguished on the map at the given scale.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, in the first line, print a single integer $ k $ ( $ 0 \le k \le \frac{n}{4} $ ) — the maximum possible number of cities that each merchant can get at a minimum.

In the second line, print two integers $ x_0 $ and $ y_0 $ ( $ |x_0|, |y_0| \le 10^9 $ ) — the coordinates of the dividing point. If there are multiple suitable points, print any of them.

## 样例 #1

### 输入

```
4
4
1 1
1 2
2 1
2 2
4
0 0
0 0
0 0
0 0
8
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
-2 1
-1 2
7
1 1
1 2
1 3
1 4
2 1
3 1
4 1
```

### 输出

```
1
2 2
0
0 0
2
1 0
0
0 0
```



---

---
title: "Mani and Segments"
layout: "post"
diff: 提高+/省选-
pid: CF2101D
tag: ['线段树', '枚举', '扫描线']
---

# Mani and Segments

## 题目描述

一个长度为 $|b|$ 的数组 $b$ 被称为"可爱的"，当且仅当其最长递增子序列（LIS）的长度与最长递减子序列（LDS）的长度 $^{\text{∗}}$ 之和恰好比数组长度大 1。更正式地说，数组 $b$ 是可爱的当且仅当 $\operatorname{LIS}(b) + \operatorname{LDS}(b) = |b| + 1$。

给定一个长度为 $n$ 的排列 $a$ $^{\text{†}}$。你的任务是统计排列 $a$ 中所有非空子数组 $^{\text{‡}}$ 中满足可爱条件的数量。

$^{\text{∗}}$ 序列 $x$ 是序列 $y$ 的子序列，如果可以通过从 $y$ 中删除任意位置（可能为零或全部）的元素得到 $x$。

数组的最长递增（递减）子序列是指元素按严格递增（递减）顺序排列的最长子序列。

$^{\text{†}}$ 长度为 $n$ 的排列是由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中出现了 $4$）。

$^{\text{‡}}$ 数组 $x$ 是数组 $y$ 的子数组，如果可以通过从 $y$ 的开头和结尾删除若干（可能为零或全部）元素得到 $x$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——排列 $a$ 的长度。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le n$）——排列 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出排列 $a$ 中满足可爱条件的非空子数组数量。

## 说明/提示

在第一个测试用例中，所有 6 个非空子数组都是可爱的：
- $[3]$：$\operatorname{LIS}([3]) + \operatorname{LDS}([3]) = 1 + 1 = 2$
- $[1]$：$\operatorname{LIS}([1]) + \operatorname{LDS}([1]) = 1 + 1 = 2$
- $[2]$：$\operatorname{LIS}([2]) + \operatorname{LDS}([2]) = 1 + 1 = 2$
- $[3, 1]$：$\operatorname{LIS}([3, 1]) + \operatorname{LDS}([3, 1]) = 1 + 2 = 3$
- $[1, 2]$：$\operatorname{LIS}([1, 2]) + \operatorname{LDS}([1, 2]) = 2 + 1 = 3$
- $[3, 1, 2]$：$\operatorname{LIS}([3, 1, 2]) + \operatorname{LDS}([3, 1, 2]) = 2 + 2 = 4$

在第二个测试用例中，一个可爱的子数组是 $[2, 3, 4, 5, 1]$，因为 $\operatorname{LIS}([2, 3, 4, 5, 1]) = 4$ 且 $\operatorname{LDS}([2, 3, 4, 5, 1]) = 2$，满足 $4 + 2 = 5 + 1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
3 1 2
5
2 3 4 5 1
4
3 4 1 2
7
1 2 3 4 5 6 7
10
7 8 2 4 5 10 1 3 6 9
```

### 输出

```
6
15
9
28
36
```



---

---
title: "Incessant Rain"
layout: "post"
diff: 提高+/省选-
pid: CF2117H
tag: ['线段树', '扫描线']
---

# Incessant Rain

## 题目描述

**注意本题的内存限制与通常不同。**

银狼给了你一个长度为 $n$ 的数组 $a$ 和 $q$ 个查询。在每个查询中，她替换数组中的一个元素。在每个查询后，她将询问你 $k$ 的最大值，使得存在一个整数 $x$ 和 $a$ 的一个子数组 $^*$，其中 $x$ 是该子数组的 $k$-多数。

若 $y$ 在数组 $b$ 中出现了至少 $\left\lfloor\frac{|b|+1}{2}\right\rfloor+k$ 次（其中 $|b|$ 表示 $b$ 的长度），则称 $y$ 是数组 $b$ 的 $k$-多数。注意 $b$ 可能不存在一个 $k$-多数。

$^*$ 若数组 $a$ 在删除开头和结尾的若干（可能为零或者全部）元素后可以得到数组 $b$，则称 $b$ 是 $a$ 的一个子数组。

## 输入格式

输入数据包含多个测试用例。输入数据的第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的个数。

对于每个测试用例：

- 第一行包含两个整数 $n$ 和 $q$（$1 \le n, q \le 3 \cdot 10^5$），表示 $a$ 的长度和查询的数量。
- 第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le n$）。
- 接下来的 $q$ 行中每行包含两个整数 $i$ 和 $x$，表示当前查询将 $a_i$ 替换为 $x$（$1 \le i,x \le n$）。

输入数据保证所有测试用例的 $n$ 和 $q$ 之和均不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，在一行中输出每个查询的回答，并以空格分隔。

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
3 4
1 4
2 4
4 3
2 3
7 8
3 2 3 3 2 2 3
2 3
5 3
6 3
3 4
4 4
7 4
6 4
2 4
```

### 输出

```
1 1 2 1 0 
2 2 3 2 1 1 1 2
```



---

