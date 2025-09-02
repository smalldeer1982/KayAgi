---
title: "MAXCHILDSUM - Maximum Child Sum"
layout: "post"
diff: 省选/NOI-
pid: SP28079
tag: []
---

# MAXCHILDSUM - Maximum Child Sum

## 题目描述

EntropyIncreaser 种树  


$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 想要种树。  

最初这个树只有 $1$ 个权值为 $0$ 的节点，也就是根。

但是 $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 是魔法少女，她可以让 $u$ 节点上长出来一个权值为 $x$ 的子节点，其编号为 树中总节点数$+1$。  

她对这棵树的权值很感兴趣，她想知道对于一个节点 $u$，其所有儿子的子树 的最大权值是多少。  

因为她还要用魔法，没有心思再计算了。于是你就要帮她解决这个问题。

## 输入格式

第一行一个正整数 $q$，表示操作个数。  
接下来 $q$ 行，每行为如下格式，表示一次操作：  

- $1$ $u$ $x$，表示给 $u$ 添加一个权值为 $x$ 的子节点  
- $2$ $u$，表示查询 $u$ 节点所有儿子的子树中最大权值

## 输出格式

对于每个 $2$ 操作，输出一行一个整数，表示答案。

## 说明/提示

样例有锅。  

实际输入样例为：  
```cpp
7
1 1 3
2 1
2 2
1 2 5
2 1
1 1 4
2 1
```  
输出样例为：  
```cpp
3
0
8
8
```  

$1\le q \le 2\times10^5$  
$1\le x \le 10^9$

## 样例 #1

### 输入

```
7\n1 1 3\n2 1\n2 2\n1 2 5\n2 1\n1 1 4\n2 1
```

### 输出

```
3\n0\n8\n8
```

