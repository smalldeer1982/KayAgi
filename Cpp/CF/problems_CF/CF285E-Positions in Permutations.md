---
title: "Positions in Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF285E
tag: ['动态规划 DP', '容斥原理']
---

# Positions in Permutations

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

We'll call position $ i $ ( $ 1<=i<=n $ ) in permutation $ p_{1},p_{2},...,p_{n} $ good, if $ |p[i]-i|=1 $ . Count the number of permutations of size $ n $ with exactly $ k $ good positions. Print the answer modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The single line contains two space-separated integers $ n $ and $ k $ ( $ 1<=n<=1000,0<=k<=n $ ).

## 输出格式

Print the number of permutations of length $ n $ with exactly $ k $ good positions modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The only permutation of size 1 has 0 good positions.

Permutation $ (1,2) $ has 0 good positions, and permutation $ (2,1) $ has 2 positions.

Permutations of size 3:

1. $ (1,2,3) $ — 0 positions
2. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/0be2e55cf7a19e2daea8429a422511a827d2e236.png) — 2 positions
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/581bad7452cc25f3e2dca31dac99a205bf6361ef.png) — 2 positions
4. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/aad15ec07c7621cca60c3be370547e4457323e38.png) — 2 positions
5. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/b2a9b87daae026f62e110bd34347625817635c68.png) — 2 positions
6. $ (3,2,1) $ — 0 positions

## 样例 #1

### 输入

```
1 0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 2

```

### 输出

```
4

```

## 样例 #4

### 输入

```
4 1

```

### 输出

```
6

```

## 样例 #5

### 输入

```
7 4

```

### 输出

```
328

```

