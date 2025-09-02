---
title: "Guard Duty (medium)"
layout: "post"
diff: 省选/NOI-
pid: CF958E2
tag: []
---

# Guard Duty (medium)

## 题目描述

Princess Heidi decided to give orders to all her $ K $ Rebel ship commanders in person. Unfortunately, she is currently travelling through hyperspace, and will leave it only at $ N $ specific moments $ t_{1},t_{2},...,t_{N} $ . The meetings with commanders must therefore start and stop at those times. Namely, each commander will board her ship at some time $ t_{i} $ and disembark at some later time $ t_{j} $ . Of course, Heidi needs to meet with all commanders, and no two meetings can be held during the same time. Two commanders cannot even meet at the beginnings/endings of the hyperspace jumps, because too many ships in one position could give out their coordinates to the enemy.

Your task is to find minimum time that Princess Heidi has to spend on meetings, with her schedule satisfying the conditions above.

## 输入格式

The first line contains two integers $ K $ , $ N $ ( $ 2<=2K<=N<=500000 $ , $ K<=5000 $ ). The second line contains $ N $ distinct integers $ t_{1},t_{2},...,t_{N} $ ( $ 1<=t_{i}<=10^{9} $ ) representing the times when Heidi leaves hyperspace.

## 输出格式

Output only one integer: the minimum time spent on meetings.

## 说明/提示

In the first example, there are five valid schedules: $ [1,4],[6,7] $ with total time 4, $ [1,4],[6,12] $ with total time 9, $ [1,4],[7,12] $ with total time 8, $ [1,6],[7,12] $ with total time 10, and $ [4,6],[7,12] $ with total time 7. So the answer is 4.

In the second example, there is only 1 valid schedule: $ [1,2],[3,4],[5,6] $ .

For the third example, one possible schedule with total time 6 is: $ [1,3],[4,5],[14,15],[23,25] $ .

## 样例 #1

### 输入

```
2 5
1 4 6 7 12

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3 6
6 3 4 2 5 1

```

### 输出

```
3

```

## 样例 #3

### 输入

```
4 12
15 7 4 19 3 30 14 1 5 23 17 25

```

### 输出

```
6

```

