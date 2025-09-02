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
title: "Garden"
layout: "post"
diff: 入门
pid: CF915A
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# Garden

## 题目描述

Luba thinks about watering her garden. The garden can be represented as a segment of length $ k $ . Luba has got $ n $ buckets, the $ i $ -th bucket allows her to water some continuous subsegment of garden of length exactly $ a_{i} $ each hour. Luba can't water any parts of the garden that were already watered, also she can't water the ground outside the garden.

Luba has to choose one of the buckets in order to water the garden as fast as possible (as mentioned above, each hour she will water some continuous subsegment of length $ a_{i} $ if she chooses the $ i $ -th bucket). Help her to determine the minimum number of hours she has to spend watering the garden. It is guaranteed that Luba can always choose a bucket so it is possible water the garden.

See the examples for better understanding.

## 输入格式

The first line of input contains two integer numbers $ n $ and $ k $ ( $ 1<=n,k<=100 $ ) — the number of buckets and the length of the garden, respectively.

The second line of input contains $ n $ integer numbers $ a_{i} $ ( $ 1<=a_{i}<=100 $ ) — the length of the segment that can be watered by the $ i $ -th bucket in one hour.

It is guaranteed that there is at least one bucket such that it is possible to water the garden in integer number of hours using only this bucket.

## 输出格式

Print one integer number — the minimum number of hours required to water the garden.

## 说明/提示

In the first test the best option is to choose the bucket that allows to water the segment of length $ 3 $ . We can't choose the bucket that allows to water the segment of length $ 5 $ because then we can't water the whole garden.

In the second test we can choose only the bucket that allows us to water the segment of length $ 1 $ .

## 样例 #1

### 输入

```
3 6
2 3 5

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6 7
1 2 3 4 5 6

```

### 输出

```
7

```



---

---
title: "Olympiad"
layout: "post"
diff: 入门
pid: CF937A
tag: ['素数判断,质数,筛法', '概率论']
---

# Olympiad

## 题目描述

题意：

现在有n个人，每个人都有一些分数（0<=a[i]<=600）,你要做的是统计有多少种分数（0和重复的都不算）。

## 输入格式

第一行：一个n，接下来的一行里有n个数。

## 输出格式

输出分数的种类。

感谢 @（T_T）   提供的翻译。

## 样例 #1

### 输入

```
4
1 3 3 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 1 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4
42 0 0 42

```

### 输出

```
1

```



---

