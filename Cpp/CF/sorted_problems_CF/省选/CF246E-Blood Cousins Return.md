---
title: "Blood Cousins Return"
layout: "post"
diff: 省选/NOI-
pid: CF246E
tag: ['树上启发式合并']
---

# Blood Cousins Return

## 题目描述

Polycarpus got hold of a family tree. The found tree describes the family relations of $ n $ people, numbered from 1 to $ n $ . Every person in this tree has at most one direct ancestor. Also, each person in the tree has a name, the names are not necessarily unique.

We call the man with a number $ a $ a 1-ancestor of the man with a number $ b $ , if the man with a number $ a $ is a direct ancestor of the man with a number $ b $ .

We call the man with a number $ a $ a $ k $ -ancestor $ (k&gt;1) $ of the man with a number $ b $ , if the man with a number $ b $ has a 1-ancestor, and the man with a number $ a $ is a $ (k-1) $ -ancestor of the 1-ancestor of the man with a number $ b $ .

In the tree the family ties do not form cycles. In other words there isn't a person who is his own direct or indirect ancestor (that is, who is an $ x $ -ancestor of himself, for some $ x $ , $ x > 0 $ ).

We call a man with a number $ a $ the $ k $ -son of the man with a number $ b $ , if the man with a number $ b $ is a $ k $ -ancestor of the man with a number $ a $ .

Polycarpus is very much interested in how many sons and which sons each person has. He took a piece of paper and wrote $ m $ pairs of numbers $ v_{i} $ , $ k_{i} $ . Help him to learn for each pair $ v_{i} $ , $ k_{i} $ the number of distinct names among all names of the $ k_{i} $ -sons of the man with number $ v_{i} $ .

## 输入格式

The first line of the input contains a single integer $ n $ $ (1 \le n \le 10^{5}) $ — the number of people in the tree. Next $ n $ lines contain the description of people in the tree. The $ i $ -th line contains space-separated string $ s_{i} $ and integer $ r_{i} $ $ (0<=r_{i}<=n) $ , where $ s_{i} $ is the name of the man with a number $ i $ , and $ r_{i} $ is either the number of the direct ancestor of the man with a number $ i $ or 0, if the man with a number $ i $ has no direct ancestor.

The next line contains a single integer $ m $ $ (1 \le m \le 10^{5}) $ — the number of Polycarpus's records. Next $ m $ lines contain space-separated pairs of integers. The $ i $ -th line contains integers $ v_{i} $ , $ k_{i} $ $ (1 \le v_{i},k_{i} \le n) $ .

It is guaranteed that the family relationships do not form cycles. The names of all people are non-empty strings, consisting of no more than $20$ lowercase English letters.

## 输出格式

Print $ m $ whitespace-separated integers — the answers to Polycarpus's records. Print the answers to the records in the order, in which the records occur in the input.

## 样例 #1

### 输入

```
6
pasha 0
gerald 1
gerald 1
valera 2
igor 3
olesya 1
5
1 1
1 2
1 3
3 1
6 1

```

### 输出

```
2
2
0
1
0

```

## 样例 #2

### 输入

```
6
valera 0
valera 1
valera 1
gerald 0
valera 4
kolya 4
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
1
0
0
0
2
0
0

```

