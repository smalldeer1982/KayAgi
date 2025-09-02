---
title: "Zookeeper and The Infinite Zoo"
layout: "post"
diff: 普及+/提高
pid: CF1491D
tag: []
---

# Zookeeper and The Infinite Zoo

## 题目描述

有一个无限图，其中有无数个节点，从 $1$ 开始标号。有一条从 $u$ 到 $u+v$ 的单向边，当且仅当 $u \&  v = v$ (这里的 $\&$ 指 [按位与](https://zh.wikipedia.org/wiki/位操作#按位与（AND）) 。除此以外没有其它边。

有 $q$ 个询问，询问是否存在一条从 $u$ 到 $v$ 的路径。

## 输入格式

第一行一个整数 $q$ （$1\le q\le10^5 $） —— 询问的个数

接下来 $q$ 行中，每行有两个整数 $u,v$ ($1 \leq u,v < 2^{30}$)，意义如上

## 输出格式

对于每个询问，输出一行 `YES` 来表示存在从 $u$ 到 $v$ 的一条路径，或输出一行 `NO` 表示不存在这样一条路径。(你可以以任意大小写形式来输出 `YES` 或 `NO`)

## 样例 #1

### 输入

```
5
1 4
3 6
1 6
6 2
5 5
```

### 输出

```
YES
YES
NO
NO
YES
```

