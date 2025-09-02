---
title: "DYNACON1 - Dynamic Tree Connectivity"
layout: "post"
diff: 省选/NOI-
pid: SP9577
tag: []
---

# DYNACON1 - Dynamic Tree Connectivity

## 题目描述

给出一个森林，初始时有$N$个点，没有边。森林中的边是双向的。你需要支持以下操作：

**add A B**：连接$A\ B$两点，保证连接完成后仍是森林。

**rem A B**：断开连接在$A\ B$之间的边，保证边存在。

**conn A B**：询问$A\ B$之间是否存在路径。

## 输入格式

第一行两个正整数$N,M(1 \leq N , M \leq 10^5)$

接下来$M$行每行一个操作

## 输出格式

对于每一个**conn**操作输出一行，如果存在路径输出`YES`，否则输出`NO`

## 样例 #1

### 输入

```
5 11
conn 1 5
add 1 2
add 1 3
add 3 4
add 5 4
conn 1 5
rem 4 5
conn 1 5
rem 3 4
add 3 5
conn 1 5
```

### 输出

```
NO
YES
NO
YES
```

