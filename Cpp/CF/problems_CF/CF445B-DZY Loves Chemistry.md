---
title: "DZY Loves Chemistry"
layout: "post"
diff: 普及/提高-
pid: CF445B
tag: []
---

# DZY Loves Chemistry

## 题目描述

DZY loves chemistry, and he enjoys mixing chemicals.

DZY has $ n $ chemicals, and $ m $ pairs of them will react. He wants to pour these chemicals into a test tube, and he needs to pour them in one by one, in any order.

Let's consider the danger of a test tube. Danger of an empty test tube is $ 1 $ . And every time when DZY pours a chemical, if there are already one or more chemicals in the test tube that can react with it, the danger of the test tube will be multiplied by $ 2 $ . Otherwise the danger remains as it is.

Find the maximum possible danger after pouring all the chemicals one by one in optimal order.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF445B/04c5ea027a40d7547891712e7f413f407f9053ef.png).

Each of the next $ m $ lines contains two space-separated integers $ x_{i} $ and $ y_{i} $ $ (1<=x_{i}<y_{i}<=n) $ . These integers mean that the chemical $ x_{i} $ will react with the chemical $ y_{i} $ . Each pair of chemicals will appear at most once in the input.

Consider all the chemicals numbered from $ 1 $ to $ n $ in some order.

## 输出格式

Print a single integer — the maximum possible danger.

## 说明/提示

In the first sample, there's only one way to pour, and the danger won't increase.

In the second sample, no matter we pour the $ 1 $ st chemical first, or pour the $ 2 $ nd chemical first, the answer is always $ 2 $ .

In the third sample, there are four ways to achieve the maximum possible danger: 2-1-3, 2-3-1, 1-2-3 and 3-2-1 (that is the numbers of the chemicals in order of pouring).

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
1 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 2
1 2
2 3

```

### 输出

```
4

```

