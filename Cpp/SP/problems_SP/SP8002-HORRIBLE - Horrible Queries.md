---
title: "HORRIBLE - Horrible Queries"
layout: "post"
diff: 普及+/提高
pid: SP8002
tag: []
---

# HORRIBLE - Horrible Queries

## 题目描述

World is getting more evil and it's getting tougher to get into the Evil League of Evil. Since the legendary Bad Horse has retired, now you have to correctly answer the evil questions of Dr. Horrible, who has a PhD in horribleness (but not in Computer Science). You are given an array of **N** elements, which are initially all 0. After that you will be given **C** commands. They are -

\* **0 p q v** - you have to add **v** to all numbers in the range of **p** to **q** (inclusive), where **p** and **q** are two indexes of the array.

\* **1 p q** - output a line containing a single integer which is the sum of all the array elements between **p** and **q** (inclusive)

## 输入格式

In the first line you'll be given **T**, number of test cases.

Each test case will start with **N** (**N** <= 100 000) and **C** (**C** <= 100 000). After that you'll be given **C** commands in the format as mentioned above. 1 <= **p**, **q** <= **N** and 1 <= **v** <= 10^7.

## 输出格式

Print the answers of the queries.

## 样例 #1

### 输入

```
\n1\n8 6\n0 2 4 26\n0 4 8 80\n0 4 5 20\n1 8 8 \n0 5 7 14\n1 4 8\n\n
```

### 输出

```
\n80\n508
```

