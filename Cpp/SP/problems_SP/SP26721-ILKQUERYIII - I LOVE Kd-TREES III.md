---
title: "ILKQUERYIII - I LOVE Kd-TREES III"
layout: "post"
diff: 难度0
pid: SP26721
tag: []
---

# ILKQUERYIII - I LOVE Kd-TREES III

## 题目描述

The "I-Love-Kd-trees'' annual con is receiving too many applicants so they decided to complicate a bit the task used to select participants. (They realized some people were using other data structures to solve their problems, so they designed this problem, almost only solvable with Kd-trees).  
  
You are given a list of **N** numbers and **Q** queries.  
  
Each query can be of two types.   
  
**Type-0** queries (marked with 0 in the input), consist of three integers: **i,** **l** and **k** ; let **d** be the **k-th** smallest element until the index **i** (i.e. if the first i +1 elements were sorted in non-descending way, **d** would be the element at index k - 1 ). Then, the answer to each query is the index of the **l-th** occurrence of **d** in the array. If there's no such index, the answer is -1.   
  
**Type-1** queries (marked with 1 in the input) are contiguous-swap update-queries, and consists of a single integer **i**. When a type-1 query is executed the elements at index i and i +1 in the list must be swapped.  
  
You have to consider that all indexes are counted starting with 0.

## 样例 #1

### 输入

```
10 6\n2 3 1 1 2 7 9 1 2 6\n0 2 3 2\n1 1 \n1 2 \n0 2 3 2 \n1 0 \n0 0 2 1\n
```

### 输出

```
8\n7\n2
```

