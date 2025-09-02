---
title: "Replace"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1707E
tag: ['倍增']
---

# Replace

## 题目描述

给定一个长为 $n$ 的序列 $a_1,\ldots,a_n$，其中对于任意的 $i$ 满足 $1 \leq a_i \leq n$。

定义一个二元组函数如下：
$$f((l,r))=(\min\{a_l,\ldots,a_r\},\max\{a_l,\ldots,a_r\})(l \leq r)$$

你需要回答 $q$ 次询问，每次给定 $(l_i,r_i)$，问其最少经过多少次 $f$ 的调用（即 $(l,r) \rightarrow f((l,r))$）使得 $(l_i,r_i)$ 变成 $(1,n)$，若无解请输出 `-1`。

## 输入格式

第一行包含两个整数 $n,q(1 \leq n,q \leq 10^5)$，表示序列长度和询问次数。

第二行包含 $n$ 个整数 $a_i(1 \leq a_i \leq n)$，表示序列 $a$。

接下来 $q$ 行每行两个整数 $l_i,r_i(1 \leq l_i \leq r_i \leq n)$，表示每组询问。

## 输出格式

对每一个询问，输出其最小次数，或无解输出 `-1`。

### 样例解释

第一个样例中，$a=\{2,5,4,1,3\}$。

对于第一个询问，$(4,4) \rightarrow (1,1) \rightarrow (2,2) \rightarrow (5,5) \rightarrow (3,3) \rightarrow (4,4) \rightarrow \cdots$，故无解。

对于第二个询问，已经有 $(l_i,r_i)=(1,n)$，需要 $0$ 次。

对于第三个询问，$(1,4) \rightarrow (1,5)$，需要 $1$ 次。

对于第四个询问，$(3,5) \rightarrow (1,4) \rightarrow (1,5)$，需要 $2$ 次。

对于第五个询问，$(4,5) \rightarrow (1,3) \rightarrow (2,5) \rightarrow (1,5)$，需要 $3$ 次。

对于第六个询问，$(2,3) \rightarrow (4,5) \rightarrow (1,3) \rightarrow (2,5) \rightarrow (1,5)$，需要 $4$ 次。

## 样例 #1

### 输入

```
5 6
2 5 4 1 3
4 4
1 5
1 4
3 5
4 5
2 3
```

### 输出

```
-1
0
1
2
3
4
```

## 样例 #2

### 输入

```
6 3
2 3 4 6 1 2
5 6
2 5
2 3
```

### 输出

```
5
1
3
```

## 样例 #3

### 输入

```
5 3
3 2 2 4 1
2 5
1 3
1 5
```

### 输出

```
-1
-1
0
```

