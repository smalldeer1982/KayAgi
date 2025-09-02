---
title: "Convex Dombination"
layout: "post"
diff: 难度0
pid: AT1202Contest_i
tag: []
---

# Convex Dombination

## 题目描述

给定平面上的 $ N $ 个不同的格点 $ (X_i,\ Y_i)\ (i\ =\ 1,\ 2,\ \dots,\ N) $。每个格点 $ (X_i,\ Y_i) $ 都有一个整数得分 $ P_i $。从这些格点中选择任意数量的格点，使得满足以下条件。求选取的格点得分的最大可能总和。

**条件**： 选取的格点被凸组合所支配。也就是说，对于每个 $ k\ =\ 1,\ 2,\ \dots,\ N $，存在 $ N $ 个非负实数 $ (\lambda_1,\ \lambda_2,\ \dots,\ \lambda_N) $，满足以下条件，格点 $ (X_k,\ Y_k) $ 被选取。
- $ \lambda_i\ >\ 0\ \implies\ {} $格点 $ (X_i,\ Y_i) $ 被选取。
- $ \sum_{i=1}^N\ \lambda_i\ =\ 1 $
- $ \sum_{i=1}^N\ \lambda_i\ X_i\ \geq\ X_k $
- $ \sum_{i=1}^N\ \lambda_i\ Y_i\ \geq\ Y_k $

## 输入格式

输入以以下格式从标准输入中给出。
> $ N $ $ X_1\ Y_1\ P_1 $ $ X_2\ Y_2\ P_2 $ $ \vdots $ $ X_N\ Y_N\ P_N $

## 输出格式

输出满足条件的选取格点的得分的最大可能总和。
### 约束
- $ 1\ \leq\ N\ \leq\ 200 $
- $ 1\ \leq\ X_i\ \leq\ 10^9\ (1\ \leq\ i\ \leq\ N) $
- $ 1\ \leq\ Y_i\ \leq\ 10^9\ (1\ \leq\ i\ \leq\ N) $
- $ (X_i,\ Y_i)\ \neq\ (X_j,\ Y_j)\ (i\ \neq\ j) $
- $ |P_i|\ \leq\ 10^7\ (1\ \leq\ i\ \leq\ N) $

Translate by [@XYQ_102](https://www.luogu.com.cn/user/712337)

## 样例 #1

### 输入

```
3
1 4 2
4 1 3
2 2 -4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 4 2
4 1 3
2 2 -1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
1 4 2
4 1 3
1 1 -6
```

### 输出

```
0
```

