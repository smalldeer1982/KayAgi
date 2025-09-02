---
title: "Almost Prime"
layout: "post"
diff: 入门
pid: CF26A
tag: ['枚举', '剪枝', '素数判断,质数,筛法']
---

# Almost Prime

## 题目描述

一个数如果恰好有两个不同质因子，那它被叫做几乎是质数的数。例如：`6,18,24`就是几乎是质数的数，而`4,8,9,42`不是，请你找出 $1$ 到 $n$ 中几乎是质数的数有多少个。

## 输入格式

输入仅包含一个整数 $n$（$1\leq n\leq3000$）。

## 输出格式

输出 $1$ 到 $n$ 中几乎是质数的数的数量。

Translated by Khassar

## 样例 #1

### 输入

```
10

```

### 输出

```
2

```

## 样例 #2

### 输入

```
21

```

### 输出

```
8

```



---

---
title: "Search for Pretty Integers"
layout: "post"
diff: 入门
pid: CF870A
tag: ['模拟', '排序', '剪枝']
---

# Search for Pretty Integers

## 题目描述

You are given two lists of non-zero digits.

Let's call an integer pretty if its (base $ 10 $ ) representation has at least one digit from the first list and at least one digit from the second list. What is the smallest positive pretty integer?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=9 $ ) — the lengths of the first and the second lists, respectively.

The second line contains $ n $ distinct digits $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=9 $ ) — the elements of the first list.

The third line contains $ m $ distinct digits $ b_{1},b_{2},...,b_{m} $ ( $ 1<=b_{i}<=9 $ ) — the elements of the second list.

## 输出格式

Print the smallest pretty integer.

## 说明/提示

In the first example $ 25 $ , $ 46 $ , $ 24567 $ are pretty, as well as many other integers. The smallest among them is $ 25 $ . $ 42 $ and $ 24 $ are not pretty because they don't have digits from the second list.

In the second example all integers that have at least one digit different from $ 9 $ are pretty. It's obvious that the smallest among them is $ 1 $ , because it's the smallest positive integer.

## 样例 #1

### 输入

```
2 3
4 2
5 7 6

```

### 输出

```
25

```

## 样例 #2

### 输入

```
8 8
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1

```

### 输出

```
1

```



---

