---
title: "The Great Julya Calendar"
layout: "post"
diff: 省选/NOI-
pid: CF331C2
tag: []
---

# The Great Julya Calendar

## 题目描述

## 题目大意

聪明的海狸得到了一个魔数 $n$，现在可以对其进行一种操作：

- 使 $n=n-k$  $(0\le k\le9)$，其中 $k$ 必须在$n$的某一位中出现。

海狸将不断进行这个操作，直至$n=0$。

选择不同的 $k$ 显然会使操作次数不同，海狸希望你能帮他算出他最少需要操作多少次才能使魔数变为$0$。

## 输入格式

单独一行，包含了一个整数，表示魔数$n$ $(0\le n\le 10^{12})$.

## 输出格式

输出一行，表示将魔数变为$0$所需的最少操作数。

## 说明/提示

对于输出样例，通过以下操作顺序可以得到最少操作次数：
 $$ 24 \rightarrow 20 \rightarrow 18 \rightarrow 10 \rightarrow 9 \rightarrow 0 $$

## 样例 #1

### 输入

```
24

```

### 输出

```
5
```

