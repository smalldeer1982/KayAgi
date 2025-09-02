---
title: "CHAMPS - Michel and the championship"
layout: "post"
diff: 难度0
pid: SP10730
tag: []
---

# CHAMPS - Michel and the championship

## 题目描述

Michel is participating in a championship where each participant have p $ _{i} $ (0<=i<=N-1) points. He knows for some pairs of participants an inequality between the points of each one, in the form p $ _{A} $ -p $ _{B} $ >= C. Now he wants to know if his data is correct, i.e., if its possible to assign points for each participant and satisfy all the inequalities.

## 输入格式

The input consists of several test cases (at most 150). The first line of each test case consists of two integers N and M (1<=N<=500, 0<=M<=5000). Then follow M lines of three integers A, B and C, indicating that p $ _{A} $ -p $ _{B} $ >= C (0<=A,B<=N-1, |C|<=20000).

## 输出格式

Print a single line for each test case with 'y' if the data is valid or 'n' if its not.

## 样例 #1

### 输入

```
2 2
0 1 2
1 0 2
4 4
0 1 1
1 2 1
2 3 -2
3 0 1
4 4
0 1 1
1 2 1
2 3 -3
3 0 1
```

### 输出

```
n
n
y
```

