---
title: "Fibonacci Freeze"
layout: "post"
diff: 普及-
pid: UVA495
tag: []
---

# Fibonacci Freeze

## 题目描述

斐波那契数列（$0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...$）由以下递推关系定义：

$$
\begin{aligned}
& F _ 0 = 0
\\ & F _ 1 = 1
\\ & F _ i = F _ {i - 1} + F _ {i - 2} & i \ge 2
\end{aligned}
$$

编写一个程序来计算斐波那契数列。

## 输入格式

程序的输入是一系列不大于 $5000$ 的数字，每个数字占一行，指定要计算的斐波那契数。

## 输出格式

程序应输出每个输入值对应的斐波那契数，每个结果占一行。

---

Translated by User 735713.

## 样例 #1

### 输入

```
5
7
11
```

### 输出

```
The Fibonacci number for 5 is 5
The Fibonacci number for 7 is 13
The Fibonacci number for 11 is 89
```

