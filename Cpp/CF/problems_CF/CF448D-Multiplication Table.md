---
title: "Multiplication Table"
layout: "post"
diff: 普及/提高-
pid: CF448D
tag: ['模拟', '二分', '枚举']
---

# Multiplication Table

## 题目描述

Bizon the Champion isn't just charming, he also is very smart.

While some of us were learning the multiplication table, Bizon the Champion had fun in his own manner. Bizon the Champion painted an $ n×m $ multiplication table, where the element on the intersection of the $ i $ -th row and $ j $ -th column equals $ i·j $ (the rows and columns of the table are numbered starting from 1). Then he was asked: what number in the table is the $ k $ -th largest number? Bizon the Champion always answered correctly and immediately. Can you repeat his success?

Consider the given multiplication table. If you write out all $ n·m $ numbers from the table in the non-decreasing order, then the $ k $ -th number you write out is called the $ k $ -th largest number.

## 输入格式

The single line contains integers $ n $ , $ m $ and $ k $ $ (1<=n,m<=5·10^{5}; 1<=k<=n·m) $ .

## 输出格式

Print the $ k $ -th largest number in a $ n×m $ multiplication table.

## 说明/提示

A $ 2×3 $ multiplication table looks like this:

`<br></br>1 2 3<br></br>2 4 6<br></br><br></br>`

## 样例 #1

### 输入

```
2 2 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 3 4

```

### 输出

```
3

```

## 样例 #3

### 输入

```
1 10 5

```

### 输出

```
5

```

