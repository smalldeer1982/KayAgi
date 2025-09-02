---
title: "Difference Row"
layout: "post"
diff: 普及/提高-
pid: CF347A
tag: []
---

# Difference Row

## 题目描述

You want to arrange $ n $ integers $ a_{1},a_{2},...,a_{n} $ in some order in a row. Let's define the value of an arrangement as the sum of differences between all pairs of adjacent integers.

More formally, let's denote some arrangement as a sequence of integers $ x_{1},x_{2},...,x_{n} $ , where sequence $ x $ is a permutation of sequence $ a $ . The value of such an arrangement is $ (x_{1}-x_{2})+(x_{2}-x_{3})+...+(x_{n-1}-x_{n}) $ .

Find the largest possible value of an arrangement. Then, output the lexicographically smallest sequence $ x $ that corresponds to an arrangement of the largest possible value.

## 输入格式

The first line of the input contains integer $ n $ ( $ 2<=n<=100 $ ). The second line contains $ n $ space-separated integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ ( $ |a_{i}|<=1000 $ ).

## 输出格式

Print the required sequence $ x_{1},x_{2},...,x_{n} $ . Sequence $ x $ should be the lexicographically smallest permutation of $ a $ that corresponds to an arrangement of the largest possible value.

## 说明/提示

In the sample test case, the value of the output arrangement is $ (100-(-50))+((-50)-0)+(0-50)+(50-(-100))=200 $ . No other arrangement has a larger value, and among all arrangements with the value of $ 200 $ , the output arrangement is the lexicographically smallest one.

Sequence $ x_{1},x_{2},...\ ,x_{p} $ is lexicographically smaller than sequence $ y_{1},y_{2},...\ ,y_{p} $ if there exists an integer $ r $ $ (0<=r&lt;p) $ such that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&lt;y_{r+1} $ .

## 样例 #1

### 输入

```
5
100 -100 50 0 -50

```

### 输出

```
100 -50 0 50 -100 

```

