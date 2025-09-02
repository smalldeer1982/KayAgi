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
title: "Galactic Council"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2038H
tag: ['费用流']
---

# Galactic Council

## 题目描述

Monocarp 正在玩一个电脑游戏，他在游戏中掌控着一个太空帝国。这个帝国由 $n$ 个政党组成。起初，每个政党的政治影响力都是 $0$，并且没有执政党。

在接下来的 $m$ 个回合中，会发生如下事件：

1. 首先，Monocarp 要选择支持哪个政党。他可以支持任何一个政党，但不能是当前的执政党。每当他支持一个政党，该政党的政治影响力就增加 $1$。假如他在第 $j$ 回合支持第 $i$ 个政党，他会因此获得 $a_{i,j}$ 分的加分；
2. 接下来，进行选举，影响力最高的政党被选为新的执政党（如果有多个这样的政党，则选编号最小的）。前任执政党会被替换，除非它继续胜选；
3. 最后，一个事件会发生。在每个回合结束时，政党 $p_j$ 必须成为执政党，否则 Monocarp 将输掉游戏。

你的任务是帮助 Monocarp 确定在每个回合中支持哪个政党，以避免因为事件而输掉游戏，并且使他的得分达到最大。初始时，Monocarp 的得分为 $0$。

## 输入格式

第一行包含两个整数 $n$ 和 $m$，表示政党的数量和游戏的回合数（$2 \le n, m \le 50$）。

第二行包含 $m$ 个整数 $p_1, p_2, \dots, p_m$，这些数表示在第 $j$ 回合结束时必须成为执政党的政党编号（$1 \le p_j \le n$）。

接下来有 $n$ 行，第 $i$ 行包含 $m$ 个整数 $a_{i,1}, a_{i,2}, \dots, a_{i,m}$，表示如果 Monocarp 在第 $j$ 回合支持第 $i$ 个政党，他会获得的得分（$1 \le a_{i,j} \le 10^5$）。

## 输出格式

如果无论 Monocarp 怎样行动都会失败，输出 $-1$。

否则，输出 $m$ 个整数 $c_1, c_2, \dots, c_m$，每个整数表示 Monocarp 在第 $j$ 回合应该支持的政党编号（$1 \le c_j \le n$）。如果有多种方案，输出任意一个即可。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2 3
2 1 2
1 2 3
4 5 6
```

### 输出

```
2 1 2
```

## 样例 #2

### 输入

```
3 5
1 1 1 2 1
1 1 1 1 1
10 5 7 8 15
7 10 9 8 15
```

### 输出

```
1 3 2 2 1
```

## 样例 #3

### 输入

```
3 5
1 1 1 1 1
1 1 1 1 1
10 5 7 8 15
7 10 9 8 15
```

### 输出

```
-1
```



---

