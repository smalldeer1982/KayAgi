---
title: "Math Show"
layout: "post"
diff: 普及/提高-
pid: CF846B
tag: []
---

# Math Show

## 题目描述

Polycarp takes part in a math show. He is given $ n $ tasks, each consists of $ k $ subtasks, numbered $ 1 $ through $ k $ . It takes him $ t_{j} $ minutes to solve the $ j $ -th subtask of any task. Thus, time required to solve a subtask depends only on its index, but not on the task itself. Polycarp can solve subtasks in any order.

By solving subtask of arbitrary problem he earns one point. Thus, the number of points for task is equal to the number of solved subtasks in it. Moreover, if Polycarp completely solves the task (solves all $ k $ of its subtasks), he recieves one extra point. Thus, total number of points he recieves for the complete solution of the task is $ k+1 $ .

Polycarp has $ M $ minutes of time. What is the maximum number of points he can earn?

## 输入格式

The first line contains three integer numbers $ n $ , $ k $ and $ M $ ( $ 1<=n<=45 $ , $ 1<=k<=45 $ , $ 0<=M<=2·10^{9} $ ).

The second line contains $ k $ integer numbers, values $ t_{j} $ ( $ 1<=t_{j}<=1000000 $ ), where $ t_{j} $ is the time in minutes required to solve $ j $ -th subtask of any task.

## 输出格式

Print the maximum amount of points Polycarp can earn in $ M $ minutes.

## 说明/提示

In the first example Polycarp can complete the first task and spend $ 1+2+3+4=10 $ minutes. He also has the time to solve one subtask of the second task in one minute.

In the second example Polycarp can solve the first subtask of all five tasks and spend $ 5·1=5 $ minutes. Also he can solve the second subtasks of two tasks and spend $ 2·2=4 $ minutes. Thus, he earns $ 5+2=7 $ points in total.

## 样例 #1

### 输入

```
3 4 11
1 2 3 4

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5 5 10
1 2 4 8 16

```

### 输出

```
7

```

