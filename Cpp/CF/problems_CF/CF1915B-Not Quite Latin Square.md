---
title: "Not Quite Latin Square"
layout: "post"
diff: 入门
pid: CF1915B
tag: ['模拟']
---

# Not Quite Latin Square

## 题目描述

A Latin square is a $ 3 \times 3 $ grid made up of the letters $ \texttt{A} $ , $ \texttt{B} $ , and $ \texttt{C} $ such that:

- in each row, the letters $ \texttt{A} $ , $ \texttt{B} $ , and $ \texttt{C} $ each appear once, and
- in each column, the letters $ \texttt{A} $ , $ \texttt{B} $ , and $ \texttt{C} $ each appear once.

 For example, one possible Latin square is shown below. $ $$$\begin{bmatrix} \texttt{A} & \texttt{B} & \texttt{C} \\ \texttt{C} & \texttt{A} & \texttt{B} \\ \texttt{B} & \texttt{C} & \texttt{A} \\ \end{bmatrix} $ $ <p>You are given a Latin square, but one of the letters was replaced with a question mark  $ \texttt{?}$$$. Find the letter that was replaced.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \leq t \leq 108 $ ) — the number of testcases.

Each test case contains three lines, each consisting of three characters, representing the Latin square. Each character is one of $ \texttt{A} $ , $ \texttt{B} $ , $ \texttt{C} $ , or $ \texttt{?} $ .

Each test case is a Latin square with exactly one of the letters replaced with a question mark $ \texttt{?} $ .

## 输出格式

For each test case, output the letter that was replaced.

## 说明/提示

The correct Latin squares for the three test cases are shown below:

 $ $$$\begin{bmatrix} \texttt{A} & \texttt{B} & \texttt{C} \\ \texttt{C} & \color{red}{\texttt{A}} & \texttt{B} \\ \texttt{B} & \texttt{C} & \texttt{A} \\ \end{bmatrix} \quad \begin{bmatrix} \texttt{B} & \texttt{C} & \texttt{A} \\ \texttt{C} & \texttt{A} & \color{red}{\texttt{B}} \\ \texttt{A} & \texttt{B} & \texttt{C} \\ \end{bmatrix} \quad \begin{bmatrix} \color{red}{\texttt{C}} & \texttt{A} & \texttt{B} \\ \texttt{B} & \texttt{C} & \texttt{A} \\ \texttt{A} & \texttt{B} & \texttt{C} \\ \end{bmatrix} $ $$$

## 样例 #1

### 输入

```
3
ABC
C?B
BCA
BCA
CA?
ABC
?AB
BCA
ABC
```

### 输出

```
A
B
C
```

