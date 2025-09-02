---
title: "Group Projects"
layout: "post"
diff: 省选/NOI-
pid: CF626F
tag: ['动态规划 DP', '枚举']
---

# Group Projects

## 题目描述

There are $ n $ students in a class working on group projects. The students will divide into groups (some students may be in groups alone), work on their independent pieces, and then discuss the results together. It takes the $ i $ -th student $ a_{i} $ minutes to finish his/her independent piece.

If students work at different paces, it can be frustrating for the faster students and stressful for the slower ones. In particular, the imbalance of a group is defined as the maximum $ a_{i} $ in the group minus the minimum $ a_{i} $ in the group. Note that a group containing a single student has an imbalance of $ 0 $ . How many ways are there for the students to divide into groups so that the total imbalance of all groups is at most $ k $ ?

Two divisions are considered distinct if there exists a pair of students who work in the same group in one division but different groups in the other.

## 输入格式

The first line contains two space-separated integers $ n $ and $ k $ ( $ 1<=n<=200 $ , $ 0<=k<=1000 $ ) — the number of students and the maximum total imbalance allowed, respectively.

The second line contains $ n $ space-separated integers $ a_{i} $ ( $ 1<=a_{i}<=500 $ ) — the time it takes the $ i $ -th student to complete his/her independent piece of work.

## 输出格式

Print a single integer, the number of ways the students can form groups. As the answer may be large, print its value modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, we have three options:

- The first and second students form a group, and the third student forms a group. Total imbalance is $ 2+0=2 $ .
- The first student forms a group, and the second and third students form a group. Total imbalance is $ 0+1=1 $ .
- All three students form their own groups. Total imbalance is $ 0 $ .

In the third sample, the total imbalance must be $ 0 $ , so each student must work individually.

## 样例 #1

### 输入

```
3 2
2 4 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 3
7 8 9 10

```

### 输出

```
13

```

## 样例 #3

### 输入

```
4 0
5 10 20 21

```

### 输出

```
1

```

