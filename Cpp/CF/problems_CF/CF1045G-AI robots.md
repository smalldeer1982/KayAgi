---
title: "AI robots"
layout: "post"
diff: 省选/NOI-
pid: CF1045G
tag: ['线段树', '树套树', '概率论']
---

# AI robots

## 题目描述

In the last mission, MDCS has successfully shipped $ N $ AI robots to Mars. Before they start exploring, system initialization is required so they are arranged in a line. Every robot can be described with three numbers: position ( $ x_i $ ), radius of sight ( $ r_i $ ) and IQ ( $ q_i $ ).

Since they are intelligent robots, some of them will talk if they see each other. Radius of sight is inclusive, so robot can see other all robots in range $ [x_i - r_i, x_i + r_i] $ . But they don't walk to talk with anybody, but only with robots who have similar IQ. By similar IQ we mean that their absolute difference isn't more than $ K $ .

 Help us and calculate how many pairs of robots are going to talk with each other, so we can timely update their software and avoid any potential quarrel.

## 输入格式

The first line contains two integers, numbers $ N (1 \leq N \leq 10^5)  $ and $ K (0 \leq K \leq 20) $ .

Next $ N $ lines contain three numbers each $ x_i, r_i, q_i (0 \leq x_i,r_i,q_i \leq 10^9) $ — position, radius of sight and IQ of every robot respectively.

## 输出格式

Output contains only one number — solution to the problem.

## 说明/提示

The first robot can see the second, but not vice versa. The first robot can't even see the third. The second and the third robot can see each other and their IQs don't differ more than 2 so only one conversation will happen.

## 样例 #1

### 输入

```
3 2
3 6 1
7 3 10
10 5 8

```

### 输出

```
1
```

