---
title: "Lazyland"
layout: "post"
diff: 普及/提高-
pid: CF1089L
tag: ['贪心']
---

# Lazyland

## 题目描述

The kingdom of Lazyland is the home to $ n $ idlers. These idlers are incredibly lazy and create many problems to their ruler, the mighty King of Lazyland.

Today $ k $ important jobs for the kingdom ( $ k \le n $ ) should be performed. Every job should be done by one person and every person can do at most one job. The King allowed every idler to choose one job they wanted to do and the $ i $ -th idler has chosen the job $ a_i $ .

Unfortunately, some jobs may not be chosen by anyone, so the King has to persuade some idlers to choose another job. The King knows that it takes $ b_i $ minutes to persuade the $ i $ -th idler. He asked his minister of labour to calculate the minimum total time he needs to spend persuading the idlers to get all the jobs done. Can you help him?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 10^5 $ ) — the number of idlers and the number of jobs.

The second line of the input contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le k $ ) — the jobs chosen by each idler.

The third line of the input contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 10^9 $ ) — the time the King needs to spend to persuade the $ i $ -th idler.

## 输出格式

The only line of the output should contain one number — the minimum total time the King needs to spend persuading the idlers to get all the jobs done.

## 说明/提示

In the first example the optimal plan is to persuade idlers 1, 6, and 8 to do jobs 2, 4, and 6.

In the second example each job was chosen by some idler, so there is no need to persuade anyone.

## 样例 #1

### 输入

```
8 7
1 1 3 1 5 3 7 1
5 7 4 8 1 3 5 2

```

### 输出

```
10

```

## 样例 #2

### 输入

```
3 3
3 1 2
5 3 4

```

### 输出

```
0

```

