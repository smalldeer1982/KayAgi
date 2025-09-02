---
title: "Apples in Boxes"
layout: "post"
diff: 普及-
pid: CF2107B
tag: ['贪心', '博弈论']
---

# Apples in Boxes

## 题目描述

Tom 和 Jerry 在地下室中找到了一些苹果，他们决定通过玩一个游戏拿取苹果。

地下室有 $n$ 个箱子，第 $i$ 个箱子里装有 $a_i$ 个苹果，Tom 和 Jerry 轮流拿取苹果，从 Tom 开始。当轮到一个人拿取苹果时，他需要：
- 选择一个盒子 $i$，满足 $a_i>0$，从中拿取一个苹果。这会使得 $a_i$ 减小 $1$。
- 如果没有满足此条件的盒子，当前拿取苹果的玩家输掉。
- 如果在拿取苹果后，$\max(a_1,a_2,\cdots,a_n)-\min(a_1,a_2,\cdots,a_n)>k$，那么刚刚拿取苹果的玩家输掉。

Tom 和 Jerry 都是理智的，请你推测游戏的结果——谁会获胜？

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据：

第一行两个整数 $n,k(1\le n\le 10^5,1\le k\le  10^9)$。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le 10^9)$。

保证一个测试点中 $\sum n\le 10^5$。

## 输出格式

对于每组数据，输出一行，如果 Tom 会赢则输出 `Tom`，如果 Jerry 会赢则输出 `Jerry`。

## 说明/提示

请注意：以下样例解释中 Tom 和 Jerry 不一定采用了最优策略，以下解释只是在使理解游戏过程变得更方便。

对于第一组数据，一种可能的游戏进行流程如下：

- Tom 选择 $i=1$，拿取苹果后 $a=(1,1,2)$。此时 $\max(1,1,2)-\min(1,1,2)=1\le k$，所以 Tom 没有输掉。
- Jerry 选择 $i=1$，拿取苹果后 $a=(0,1,2)$。此时 $\max(0,1,2)-\min(0,1,2)=2> k$，Jerry 输掉了。

By chenxi2009

## 样例 #1

### 输入

```
3
3 1
2 1 2
3 1
1 1 3
2 1
1 4
```

### 输出

```
Tom
Tom
Jerry
```



---

---
title: "箱中苹果"
layout: "post"
diff: 普及-
pid: CF2107B
tag: ['贪心', '博弈论']
---

# 箱中苹果

## 题目描述

Tom 和 Jerry 在地下室中找到了一些苹果，他们决定通过玩一个游戏拿取苹果。

地下室有 $n$ 个箱子，第 $i$ 个箱子里装有 $a_i$ 个苹果，Tom 和 Jerry 轮流拿取苹果，从 Tom 开始。当轮到一个人拿取苹果时，他需要：
- 选择一个盒子 $i$，满足 $a_i>0$，从中拿取一个苹果。这会使得 $a_i$ 减小 $1$。
- 如果没有满足此条件的盒子，当前拿取苹果的玩家输掉。
- 如果在拿取苹果后，$\max(a_1,a_2,\cdots,a_n)-\min(a_1,a_2,\cdots,a_n)>k$，那么刚刚拿取苹果的玩家输掉。

Tom 和 Jerry 都是理智的，请你推测游戏的结果——谁会获胜？

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据：

第一行两个整数 $n,k(1\le n\le 10^5,1\le k\le  10^9)$。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le 10^9)$。

保证一个测试点中 $\sum n\le 10^5$。

## 输出格式

对于每组数据，输出一行，如果 Tom 会赢则输出 `Tom`，如果 Jerry 会赢则输出 `Jerry`。

## 说明/提示

请注意：以下样例解释中 Tom 和 Jerry 不一定采用了最优策略，以下解释只是在使理解游戏过程变得更方便。

对于第一组数据，一种可能的游戏进行流程如下：

- Tom 选择 $i=1$，拿取苹果后 $a=(1,1,2)$。此时 $\max(1,1,2)-\min(1,1,2)=1\le k$，所以 Tom 没有输掉。
- Jerry 选择 $i=1$，拿取苹果后 $a=(0,1,2)$。此时 $\max(0,1,2)-\min(0,1,2)=2> k$，Jerry 输掉了。

By chenxi2009

## 样例 #1

### 输入

```
3
3 1
2 1 2
3 1
1 1 3
2 1
1 4
```

### 输出

```
Tom
Tom
Jerry
```



---

---
title: "Little Xor"
layout: "post"
diff: 普及-
pid: CF252A
tag: ['博弈论', '枚举', '前缀和']
---

# Little Xor

## 题目描述

Little Petya likes arrays that consist of non-negative integers a lot. Recently his mom has presented him one such array consisting of $ n $ elements. Petya immediately decided to find there a segment of consecutive elements, such that the $ xor $ of all numbers from this segment was maximal possible. Help him with that.

The $ xor $ operation is the bitwise exclusive "OR", that is denoted as "xor" in Pascal and "^" in C/C++/Java.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the number of elements in the array. The second line contains the space-separated integers from the array. All numbers are non-negative integers strictly less than $ 2^{30} $ .

## 输出格式

Print a single integer — the required maximal $ xor $ of a segment of consecutive elements.

## 说明/提示

In the first sample one of the optimal segments is the segment that consists of the first and the second array elements, if we consider the array elements indexed starting from one.

The second sample contains only one optimal segment, which contains exactly one array element (element with index three).

## 样例 #1

### 输入

```
5
1 2 1 1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 2 7

```

### 输出

```
7

```

## 样例 #3

### 输入

```
4
4 2 4 8

```

### 输出

```
14

```



---

