---
title: "XXXXXXXX - Sum of Distinct Numbers"
layout: "post"
diff: 难度0
pid: SP9066
tag: []
---

# XXXXXXXX - Sum of Distinct Numbers

## 题目描述

给你一个长度为 $N$ 的数组，你要完成两种操作：

- `U X Y`，将第 $X$ 个元素变成 $Y$；
- `Q X Y`，计算 $[X,Y]$ 中不同数字的总和，就比如集合 $\{1,2,3,2,7\}$ 的总和就是 $1+2+3+7=13$。


保证答案不超过 $32$ 位整型。

## 输入格式

第一行，一个正整数 $N(1\le n\le 5\times 10^4)$。

第二行，$N$ 个数字，表示数组元素。

第三行，一个正整数 $Q(1\le Q \le 10^5)$。

## 输出格式

对于每个操作 $2$ 给出你的回答。

## 样例 #1

### 输入

```
\n5\n1 2 4 2 3&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;\n3\nQ 2 4\nU 4 7\nQ 2 4\n\n
```

### 输出

```
\n6\n13\n\n
```

