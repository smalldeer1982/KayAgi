---
title: "Vanya and Exams"
layout: "post"
diff: 普及+/提高
pid: CF492C
tag: []
---

# Vanya and Exams

## 题目描述

Vanya wants to pass $ n $ exams and get the academic scholarship. He will get the scholarship if the average grade mark for all the exams is at least $ avg $ . The exam grade cannot exceed $ r $ . Vanya has passed the exams and got grade $ a_{i} $ for the $ i $ -th exam. To increase the grade for the $ i $ -th exam by 1 point, Vanya must write $ b_{i} $ essays. He can raise the exam grade multiple times.

What is the minimum number of essays that Vanya needs to write to get scholarship?

## 输入格式

The first line contains three integers n, r, avg (1 ≤ n ≤ 105, 1 ≤ r ≤ 109, 1 ≤ avg ≤ min(r, 106)) — the number of exams, the maximum grade and the required grade point average, respectively.

Each of the following n lines contains space-separated integers ai and bi (1 ≤ ai ≤ r, 1 ≤ bi ≤ 106).

## 输出格式

In the first line print the minimum number of essays.

## 说明/提示

In the first sample Vanya can write 2 essays for the 3rd exam to raise his grade by 2 points and 2 essays for the 4th exam to raise his grade by 1 point.

In the second sample, Vanya doesn't need to write any essays as his general point average already is above average.

## 样例 #1

### 输入

```
5 5 4
5 2
4 7
3 1
3 2
2 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2 5 4
5 2
5 2

```

### 输出

```
0

```

