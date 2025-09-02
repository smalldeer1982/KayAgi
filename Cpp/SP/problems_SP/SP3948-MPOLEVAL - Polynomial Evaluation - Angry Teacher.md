---
title: "MPOLEVAL - Polynomial Evaluation - Angry Teacher"
layout: "post"
diff: 难度0
pid: SP3948
tag: []
---

# MPOLEVAL - Polynomial Evaluation - Angry Teacher

## 题目描述

O'Cruel 先生正在教授九年级的数学课程。学生们天生懒散，不喜欢做作业；与此同时，O'Cruel 先生又对懒学生深恶痛绝。最近，Andrew 再次没完成作业，因此被布置了一个特别任务。若不完成，他将被学校开除。乍看之下，这个任务似乎很简单，但其技术性很强，十分耗时。具体来说，Andrew 被给了一个多项式 $p(x) = a_n x^n + a_{n-1} x^{n-1} + \ldots + a_1 x + a_0$，其中系数都是整数。

他需要计算从 $l$ 开始的连续 $k$ 个整数的多项式值。显然，用纸记录所有这些数字将会很麻烦。为了证明他完成了任务，Andrew 需要为从 $l$ 到 $l+k-1$ 的每个整数 $x$，计算 $p(x)$ 在十进制下最后 $m$ 位数字的平方和。由于 Andrew 懒得自己动手，他决定请求你来编写一个程序以进行计算。

## 输入格式

输入的第一行包含四个整数 $n, l, k, m$（$0 \le n \le 10, 0 \le l \le 10^{1000}, 1 \le k \le 1000, 1 \le m \le 1000$）。接下来的 $n+1$ 行给出多项式的各项系数：$a_n, a_{n-1}, \ldots, a_1, a_0$（$0 \le a_i \le 10^{1000}$）。

```
SAMPLE INPUT
3 0 10 2
1
0
2
1
```

## 输出格式

输出 $k$ 行结果——对于从 $l$ 到 $l+k-1$ 的每个整数 $x$，输出 $p(x)$ 在十进制表示下最后 $m$ 位数字的平方和。

```
SAMPLE OUTPUT
1
16
10
25
58
45
85
89
85
80
```

## 说明/提示

- $0 \le n \le 10$
- $0 \le l \le 10^{1000}$
- $1 \le k \le 1000$
- $1 \le m \le 1000$
- $0 \le a_i \le 10^{1000}$

 **本翻译由 AI 自动生成**

