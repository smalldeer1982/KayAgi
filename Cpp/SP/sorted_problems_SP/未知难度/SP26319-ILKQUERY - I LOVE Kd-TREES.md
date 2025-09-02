---
title: "ILKQUERY - I LOVE Kd-TREES"
layout: "post"
diff: 难度0
pid: SP26319
tag: []
---

# ILKQUERY - I LOVE Kd-TREES

## 题目描述

You've been invited to the "I-Love-Kd-trees'' annual con, but first, you have to show them that you really know about great data structures, so they give you an easy task!   
  
You are given a list of **N** numbers and **Q** queries, each query consist of three integers: _**k**,_ **_i_** and **_l_** ;let **d** be the **k-th** smallest element until the index **i** (i.e. if the first i+1 elements were sorted in non-descending way, **d** would be the element at index **k - 1** ). Then, the answer to each query is the index of the **l-th** occurrence of **d** in the array. If there's no such index, the answer is **-1.** You have to consider that all indexes are counted starting with 0.

## 输入格式

Input consists of one test case.

The first line contains two integers, **N** ( 1 Q (1

The next line contains **N** possibly distinct integers **a $ _{i} $**  ( -10 $ ^{9} $

  
Then **Q** lines follow, each of those contains three integers _**k**_, _**i**_ and _**l**_. (0 < k

## 输出格式

  
For each query (in the same order as the input) output a single line with the answer to that query.

## 样例 #1

### 输入

```
\n\n10 6\n2 6 7 1 8 1 2 3 2 6\n2 4 2\n2 6 3\n1 4 1\n1 4 2\n3 4 2\n3 3 2\n
```

### 输出

```
\n6\n-1\n3\n5\n9\n9\n\nExplanation of the first query: \n\nThe elements until index 4 are [2,6,7,1,8] so the 2nd smallest element is 2, and your asked for the index of it's 2nd ocurrency, so the answer is 6.
```

