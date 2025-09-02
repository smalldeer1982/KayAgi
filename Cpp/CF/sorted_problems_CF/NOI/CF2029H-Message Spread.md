---
title: "Message Spread"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2029H
tag: ['快速沃尔什变换 FWT', '快速沃尔什变换 FWT']
---

# Message Spread

## 题目描述

Given is an undirected graph with $ n $ vertices and $ m $ edges. Each edge connects two vertices $ (u, v) $ and has a probability of $ \frac{p}{q} $ of appearing each day.

Initially, vertex $ 1 $ has a message. At the end of the day, a vertex has a message if and only if itself or at least one of the vertices adjacent to it had the message the day before. Note that each day, each edge chooses its appearance independently.

Calculate the expected number of days before all the vertices have the message, modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1\leq n\leq 21 $ , $ n-1\leq m\leq\frac{n(n-1)}{2} $ ).

Then $ m $ lines follow, each containing four integers $ u $ , $ v $ , $ p $ , and $ q $ ( $ 1\leq u\neq v\leq n $ , $ 1\leq p<q<998\,244\,353 $ , $ \gcd(p,q)=1 $ ) — there is an undirected edge between $ u $ and $ v $ , and it has a probability of appearance of $ \frac{p}{q} $ each day.

It is guaranteed that there are no self-loops or multiple-edges in the graph and that the graph is connected if all of the edges appear.

Additional constraint in the input: Let $ g_{i,j} $ be the probability of appearance of the edge between $ i $ and $ j $ ( $ g_{i,j}=0 $ if there is no edge between $ i $ and $ j $ ). It is guaranteed that for any $ S\subseteq\{1,2,\ldots,n\} $ ( $ |S|\ge 1 $ ), $ $$$ \prod_{i\in S}\left(\prod_{j\in\{1,2,\ldots,n\}\setminus S}(1-g_{i,j})\right)\not\equiv1\pmod{998\,244\,353}.  $ $$$

## 输出格式

Print a single integer in the only line of the output — the expected number of days, modulo $ 998\,244\,353 $ .

Formally, let $ M = 998\,244\,353 $ . It can be shown that the exact answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test, the answer is equal to the expected number of days before the only edge in the graph first appears, and that is $ \frac{1}{0.1}=10 $ .

In the second test, the answer is equal to $ \frac{20}{9} $ before it is taken modulo $ 998\,244\,353 $ .

In the third test, the only vertex already has the message, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
2 1
1 2 1 10
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 3
1 2 1 2
1 3 1 2
2 3 1 2
```

### 输出

```
887328316
```

## 样例 #3

### 输入

```
1 0
```

### 输出

```
0
```

## 样例 #4

### 输入

```
5 8
1 2 1 11
1 3 2 11
1 4 3 11
1 5 4 11
2 4 5 11
2 5 6 11
3 4 7 11
4 5 8 11
```

### 输出

```
469993557
```

## 样例 #5

### 输入

```
21 22
1 2 3 4
2 3 4 5
3 4 5 6
5 6 7 8
6 7 8 9
7 8 9 10
8 9 2 3
9 10 3 4
10 11 4 5
11 12 5 6
12 13 6 7
13 14 7 8
14 15 8 9
15 16 9 10
16 17 2 3
17 18 3 4
18 19 4 5
19 20 5 6
20 21 6 7
1 10 100 1001
15 4 147 220
4 11 1 998244352
```

### 输出

```
299529765
```

