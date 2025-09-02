---
title: "The Good Array"
layout: "post"
diff: 入门
pid: CF1839A
tag: []
---

# The Good Array

## 题目描述

对于一个由 $0$ 和 $1$ 构成的数组 $a_1,a_2,\dots,a_n$，如果对于从 $1$ 到 $n$ 中所有的整数 $i$ 都满足以下两个条件，我们称这个数组为『好的数组』：
- **前** $i$ 个元素中有至少 $\left\lceil\frac{i}{k}\right\rceil$ 个元素为 $1$；
- **后** $i$ 个元素中有至少 $\left\lceil\frac{i}{k}\right\rceil$ 个元素为 $1$。

其中，$\left\lceil\frac{i}{k}\right\rceil$ 表示 $i$ 除以 $k$ 向上取整。

构造一个长度为 $n$ 的『好的数组』，使其中 $1$ 的数量尽可能的少。

## 输入格式

本题多测。第一行为一个整数 $t\left(1\le t\le10^4\right)$，表示有 $t$ 组数据。

## 输出格式

每组样例输出一行一个整数，表示你构造的『好的数组』中 $1$ 的数量。

## 样例 #1

### 输入

```
7
3 2
5 2
9 3
7 1
10 4
9 5
8 8
```

### 输出

```
2
3
4
7
4
3
2
```

