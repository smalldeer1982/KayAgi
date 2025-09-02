---
title: "XOR Tree"
layout: "post"
diff: 提高+/省选-
pid: CF1709E
tag: ['树上启发式合并', '最近公共祖先 LCA']
---

# XOR Tree

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

Recall that a simple path is a path that visits each vertex at most once. Let the weight of the path be the bitwise XOR of the values written on vertices it consists of. Let's say that a tree is good if no simple path has weight $ 0 $ .

You can apply the following operation any number of times (possibly, zero): select a vertex of the tree and replace the value written on it with an arbitrary positive integer. What is the minimum number of times you have to apply this operation in order to make the tree good?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of vertices.

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 1 \le a_i < 2^{30} $ ) — the numbers written on vertices.

Then $ n - 1 $ lines follow, each containing two integers $ x $ and $ y $ ( $ 1 \le x, y \le n; x \ne y $ ) denoting an edge connecting vertex $ x $ with vertex $ y $ . It is guaranteed that these edges form a tree.

## 输出格式

Print a single integer — the minimum number of times you have to apply the operation in order to make the tree good.

## 说明/提示

In the first example, it is enough to replace the value on the vertex $ 1 $ with $ 13 $ , and the value on the vertex $ 4 $ with $ 42 $ .

## 样例 #1

### 输入

```
6
3 2 1 3 2 1
4 5
3 4
1 4
2 1
6 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
2 1 1 1
1 2
1 3
1 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
2 2 2 2 2
1 2
2 3
3 4
4 5
```

### 输出

```
2
```



---

---
title: "Blood Cousins"
layout: "post"
diff: 提高+/省选-
pid: CF208E
tag: ['树上启发式合并']
---

# Blood Cousins

## 题目描述

### 题面描述

有一个家族关系森林，描述了 $n$（$1\leq n\leq 10 ^ 5$）人的家庭关系，成员编号为 $1$ 到 $n$ 。

如果 $a$ 是 $b$ 的父亲，那么称 $a$ 为 $b$ 的 $1$ 级祖先；如果 $b$ 有一个 $1$ 级祖先，$a$ 是 $b$ 的 $1$ 级祖先的 $k-1$ 级祖先，那么称 $a$ 为 $b$ 的 $k$ 级祖先。

家庭关系保证是一棵森林，树中的每个人都至多有一个父母，且自己不会是自己的祖先。

如果存在一个人 $z$ ，是两个人 $a$ 和 $b$ 共同的 $p$ 级祖先：那么称 $a$ 和 $b$ 为 $p$ 级表亲。

$m$（$1\leq m\leq 10 ^ 5$）次询问，每次询问给出一对整数 $v$ 和 $p$，求编号为 $v$ 的人有多少个 $p$ 级表亲。

## 输入格式

第一个正整数 $n$ 表示家族里共有 $n$ 个人。

接下来一行 $n$ 个数 $r_1, r_2, \ldots, r_n$，表示 $r_i$ 是 $i$ 的父亲；如果 $r_i$ 为 $0$，那么 $i$ 就是根节点。

第三行一个整数 $m$ 表示询问数量。

接下来 $m$ 行，每行两个整数 $v_i$ 和 $p_i$，数字间用空格间隔；表示一组询问，即询问编号为 $v$ 的人有多少个 $p$ 级表亲。

保证输入合法。

## 输出格式

输出一行 $m$ 个数。对于每次询问，输出其答案。数字间用空格间隔。

## 样例 #1

### 输入

```
6
0 1 1 0 4 4
7
1 1
1 2
2 1
2 2
4 1
5 1
6 1

```

### 输出

```
0 0 1 0 0 1 1 

```



---

