---
title: "Load Balancing"
layout: "post"
diff: 普及/提高-
pid: CF609C
tag: []
---

# Load Balancing

## 题目描述

In the school computer room there are $ n $ servers which are responsible for processing several computing tasks. You know the number of scheduled tasks for each server: there are $ m_{i} $ tasks assigned to the $ i $ -th server.

In order to balance the load for each server, you want to reassign some tasks to make the difference between the most loaded server and the least loaded server as small as possible. In other words you want to minimize expression $ m_{a}-m_{b} $ , where $ a $ is the most loaded server and $ b $ is the least loaded one.

In one second you can reassign a single task. Thus in one second you can choose any pair of servers and move a single task from one server to another.

Write a program to find the minimum number of seconds needed to balance the load of servers.

## 输入格式

The first line contains positive number $ n $ ( $ 1<=n<=10^{5} $ ) — the number of the servers.

The second line contains the sequence of non-negative integers $ m_{1},m_{2},...,m_{n} $ ( $ 0<=m_{i}<=2·10^{4} $ ), where $ m_{i} $ is the number of tasks assigned to the $ i $ -th server.

## 输出格式

Print the minimum number of seconds required to balance the load.

## 说明/提示

In the first example two seconds are needed. In each second, a single task from server #2 should be moved to server #1. After two seconds there should be 3 tasks on server #1 and 4 tasks on server #2.

In the second example the load is already balanced.

A possible sequence of task movements for the third example is:

1. move a task from server #4 to server #1 (the sequence $ m $ becomes: 2 2 3 3 5);
2. then move task from server #5 to server #1 (the sequence $ m $ becomes: 3 2 3 3 4);
3. then move task from server #5 to server #2 (the sequence $ m $ becomes: 3 3 3 3 3).

The above sequence is one of several possible ways to balance the load of servers in three seconds.

## 样例 #1

### 输入

```
2
1 6

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7
10 11 10 11 10 11 11

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5
1 2 3 4 5

```

### 输出

```
3

```

