---
title: "NORMA2 - Norma"
layout: "post"
diff: 省选/NOI-
pid: SP22343
tag: ['分治', '前缀和', '概率论']
---

# NORMA2 - Norma

## 题目描述

Mirko got an array of integers for his birthday from his grandmother Norma. As any other kid, he was hoping for some money, but got an array. Luckily, in his town there is a pawn shop that buys up arrays. The cost of an array of integers is **min** \* **max** \* **L** kunas, where **min** is the minimal integer in the array, **max** is the maximal and **L** is the array length. Mirko is going to sell a subsequence of consecutive numbers from his array. He calculated the average price of all such subsequences.

In order to check his result, he wants you to do the same. He will be pleased with only the last 9 digits of the sum of all prices, so you don’t need to bother with large and real numbers.

## 输入格式

The first line of input contains an integer N (1

Each of the following N lines contains a member of Mirko’s array. The members of the array will be integers from the interval \[1, 10 $ ^{8} $ \].

## 输出格式

The first and only line of output must contain an integer, the last 9 digits of the required sum from the task. **You don’t need to output** the leading zeroes of that 9-digit integer.

## 样例 #1

### 输入

```
2\n1\n3 
```

### 输出

```
16
```



---

---
title: "QTREE4 - Query on a tree IV"
layout: "post"
diff: 省选/NOI-
pid: SP2666
tag: ['递归', '分治', '动态树 LCT', '概率论']
---

# QTREE4 - Query on a tree IV

## 题目描述

You are given a tree (an acyclic undirected connected graph) with $N$ nodes, and nodes numbered $1,2,3\ldots,N$. Each edge has an integer value assigned to it (note that the value can be negative). Each node has a color, white or black. We define $dist(a, b)$ as the sum of the value of the edges on the path from node $a$ to node $b$.

All the nodes are white initially.

We will ask you to perfrom some instructions of the following form:

- `C a` : change the color of node $a$.(from black to white or from white to black)
- `A` : ask for the maximum $dist(a, b)$, both of node a and node $b$ must be white ($a$ can be equal to $b$). Obviously, as long as there is a white node, the result will alway be non negative.

## 输入格式

- In the first line there is an integer $N$. ($N \leq 100000$)
- In the next $N-1$ lines, the $i$-th line describes the $i$-th edge: a line with three integers $a,b,c$ denotes an edge between $a, b$ of value $c$. ($-10^3 \leq c \leq 10^3$)
- In the next line, there is an integer $Q$ denotes the number of instructions. ($Q \leq 100000$)
- In the next $Q$ lines, each line contains an instruction `C a` or `A`.

## 输出格式

For each `A` operation, write one integer representing its result. If there is no white node in the tree, you should write `They have disappeared.`.

## 样例 #1

### 输入

```
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A
```

### 输出

```
2
2
0
They have disappeared.
```



---

