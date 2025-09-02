---
title: "CTTC - Counting Child"
layout: "post"
diff: 普及-
pid: SP34009
tag: []
---

# CTTC - Counting Child

## 题目描述

 Little boy Arik is playing with tree. He is counting the number of children of each node.

 For this, he starts with root node 1. And traverse the full tree in DFS (Depth First Search) style. For simplicity, see the following figure.

For Tree - 1, his traversing sequence is 1 2 2 3 3 1. He starts with root node 1. Then he starts visiting first child 2, then finishes his traversing at 2. Then he starts visiting second child 3, then finishes his traversing at 3. And then finally finishes his traversing at 1.

For Tree - 2, his traversing sequence is 1 2 4 4 2 3 5 5 6 6 3 1.

## 输入格式

Input starts with an integer t (1 <= t <= 20), which denotes the case numbers.

For each case, you are given n (1 <= n <= 100) in first line. Next line contains 2n integers denoting his sequences of traversing. All nodes are between 1 to n. The root node is always node 1.

## 输出格式

 For each case print the case number in the first line. Following n lines print each node from 1 to n and number of child of the node. Print a blank line after each test cases. See the sample I/O section for more details about output format.

## 样例 #1

### 输入

```
2
3
1 2 2 3 3 1
6
1 2 4 4 2 3 5 5 6 6 3 1
```

### 输出

```
Case 1:
1 -> 2
2 -> 0
3 -> 0

Case 2:
1 -> 2
2 -> 1
3 -> 2
4 -> 0
5 -> 0
6 -> 0
```

