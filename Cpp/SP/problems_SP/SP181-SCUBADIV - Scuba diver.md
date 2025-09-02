---
title: "SCUBADIV - Scuba diver"
layout: "post"
diff: 普及/提高-
pid: SP181
tag: ['动态规划 DP', '背包 DP']
---

# SCUBADIV - Scuba diver

## 题目描述

A scuba diver uses a special equipment for diving. He has a cylinder with two containers: one with oxygen and the other with nitrogen. Depending on the time he wants to stay under water and the depth of diving the scuba diver needs various amount of oxygen and nitrogen. The scuba diver has at his disposal a certain number of cylinders. Each cylinder can be described by its weight and the volume of gas it contains. In order to complete his task the scuba diver needs specific amount of oxygen and nitrogen. What is the minimal total weight of cylinders he has to take to complete the task?

## 输入格式

The number of test cases _c_ is in the first line of input, then _c_ test cases follow separated by an empty line.

In the first line of a test case there are two integers _t_, _a_ separated by a single space, 1 <= _t_ <= 21 and 1 <= _a_ <= 79. They denote volumes of oxygen and nitrogen respectively, needed to complete the task. The second line contains one integer _n_, 1 <= _n_ <= 1000, which is the number of accessible cylinders. The following _n_ lines contain descriptions of cylinders; _i_-th line contains three integers _t_ _$ _{i} $_ , _a_ _$ _{i} $_ , _w_ _$ _{i} $_  separated by single spaces, (1 <= _t_ _$ _{i} $_  <= 21, 1 <= _a_ _$ _{i} $_  <= 79, 1 <= _w_ _$ _{i} $_  <= 800). These are respectively: volume of oxygen and nitrogen in the _i_-th cylinder and the weight of this cylinder.

## 输出格式

For each test case your program should output one line with the minimal total weight of cylinders the scuba diver should take to complete the task.

## 样例 #1

### 输入

```
1
5 60
5
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119

```

### 输出

```
249

```

