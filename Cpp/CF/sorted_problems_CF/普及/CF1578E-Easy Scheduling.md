---
title: "Easy Scheduling"
layout: "post"
diff: 普及/提高-
pid: CF1578E
tag: []
---

# Easy Scheduling

## 题目描述

Eonathan Eostar decided to learn the magic of multiprocessor systems. He has a full binary tree of tasks with height $ h $ . In the beginning, there is only one ready task in the tree — the task in the root. At each moment of time, $ p $ processes choose at most $ p $ ready tasks and perform them. After that, tasks whose parents were performed become ready for the next moment of time. Once the task becomes ready, it stays ready until it is performed.

You shall calculate the smallest number of time moments the system needs to perform all the tasks.

## 输入格式

The first line of the input contains the number of tests $ t $ ( $ 1 \leq t \leq 5\cdot 10^5 $ ). Each of the next $ t $ lines contains the description of a test. A test is described by two integers $ h $ ( $ 1 \leq h \leq 50 $ ) and $ p $ ( $ 1 \leq p \leq 10^4 $ ) — the height of the full binary tree and the number of processes. It is guaranteed that all the tests are different.

## 输出格式

For each test output one integer on a separate line — the smallest number of time moments the system needs to perform all the tasks.

## 说明/提示

Let us consider the second test from the sample input. There is a full binary tree of height $ 3 $ and there are two processes. At the first moment of time, there is only one ready task, $ 1 $ , and $ p_1 $ performs it. At the second moment of time, there are two ready tasks, $ 2 $ and $ 3 $ , and the processes perform them. At the third moment of time, there are four ready tasks, $ 4 $ , $ 5 $ , $ 6 $ , and $ 7 $ , and $ p_1 $ performs $ 6 $ and $ p_2 $ performs $ 5 $ . At the fourth moment of time, there are two ready tasks, $ 4 $ and $ 7 $ , and the processes perform them. Thus, the system spends $ 4 $ moments of time to perform all the tasks.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1578E/98a14360f938976e2072b80e9c0ef58237d08d77.png)

## 样例 #1

### 输入

```
3
3 1
3 2
10 6
```

### 输出

```
7
4
173
```

