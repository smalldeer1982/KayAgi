---
title: "QTREE2 - Query on a tree II"
layout: "post"
diff: 提高+/省选-
pid: SP913
tag: ['倍增', '深度优先搜索 DFS', '最近公共祖先 LCA']
---

# QTREE2 - Query on a tree II

## 题目描述

 You are given a tree (an undirected acyclic connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1. Each edge has an integer value assigned to it, representing its length.

 We will ask you to perfrom some instructions of the following form:

- **DIST a b** : ask for the distance between node **a** and node **b**  
   or
- **KTH a b k** : ask for the **k**-th node on the path from node **a** to node **b**

 **Example:**  
**N** = 6   
 1 2 1 // edge connects node 1 and node 2 has cost 1   
 2 4 1   
 2 5 2   
 1 3 1   
 3 6 2   
  
 Path from node 4 to node 6 is 4 -> 2 -> 1 -> 3 -> 6   
**DIST 4 6** : answer is 5 (1 + 1 + 1 + 2 = 5)   
**KTH 4 6 4** : answer is 3 (the 4-th node on the path from node 4 to node 6 is 3)

## 输入格式

 The first line of input contains an integer **t**, the number of test cases (**t** <= 25). **t** test cases follow.

For each test case:

- In the first line there is an integer **N** (**N** <= 10000)
- In the next **N**-1 lines, the i-th line describes the i-th edge: a line with three integers **a b c** denotes an edge between **a**, **b** of cost **c** (**c** <= 100000)
- The next lines contain instructions **"DIST a b"** or **"KTH a b k"**
- The end of each test case is signified by the string "**DONE**".

There is one blank line between successive tests.

## 输出格式

For each **"DIST"** or **"KTH"** operation, write one integer representing its result.

Print one blank line after each test.

## 样例 #1

### 输入

```
1

6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
DIST 4 6
KTH 4 6 4
DONE
```

### 输出

```
5
3
```



---

