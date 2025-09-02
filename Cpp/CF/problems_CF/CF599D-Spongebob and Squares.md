---
title: "Spongebob and Squares"
layout: "post"
diff: 普及+/提高
pid: CF599D
tag: []
---

# Spongebob and Squares

## 题目描述

Spongebob is already tired trying to reason his weird actions and calculations, so he simply asked you to find all pairs of n and m, such that there are exactly $ x $ distinct squares in the table consisting of $ n $ rows and $ m $ columns. For example, in a $ 3×5 $ table there are $ 15 $ squares with side one, $ 8 $ squares with side two and $ 3 $ squares with side three. The total number of distinct squares in a $ 3×5 $ table is $ 15+8+3=26 $ .

## 输入格式

The first line of the input contains a single integer $ x $ ( $ 1<=x<=10^{18} $ ) — the number of squares inside the tables Spongebob is interested in.

## 输出格式

First print a single integer $ k $ — the number of tables with exactly $ x $ distinct squares inside.

Then print $ k $ pairs of integers describing the tables. Print the pairs in the order of increasing $ n $ , and in case of equality — in the order of increasing $ m $ .

## 说明/提示

In a $ 1×2 $ table there are $ 2 $ $ 1×1 $ squares. So, $ 2 $ distinct squares in total.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599D/9dab69eaea2bb36c546e77be3f4ad4f8dd6c533d.png)In a $ 2×3 $ table there are $ 6 $ $ 1×1 $ squares and $ 2 $ $ 2×2 $ squares. That is equal to $ 8 $ squares in total.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599D/35201b8105ae1bfeef67a0a4652f36b51fa0b01f.png)

## 样例 #1

### 输入

```
26

```

### 输出

```
6
1 26
2 9
3 5
5 3
9 2
26 1

```

## 样例 #2

### 输入

```
2

```

### 输出

```
2
1 2
2 1

```

## 样例 #3

### 输入

```
8

```

### 输出

```
4
1 8
2 3
3 2
8 1

```

