---
title: "Singer House"
layout: "post"
diff: 省选/NOI-
pid: CF830D
tag: []
---

# Singer House

## 题目描述

It is known that passages in Singer house are complex and intertwined. Let's define a Singer $ k $ -house as a graph built by the following process: take complete binary tree of height $ k $ and add edges from each vertex to all its successors, if they are not yet present.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF830D/786f947e45e17a01a870bc159efd0eac65e5d884.png)Singer $ 4 $ -houseCount the number of non-empty paths in Singer $ k $ -house which do not pass the same vertex twice. Two paths are distinct if the sets or the orders of visited vertices are different. Since the answer can be large, output it modulo $ 10^{9}+7 $ .

## 输入格式

The only line contains single integer $ k $ ( $ 1<=k<=400 $ ).

## 输出格式

Print single integer — the answer for the task modulo $ 10^{9}+7 $ .

## 说明/提示

There are $ 9 $ paths in the first example (the vertices are numbered on the picture below): 1, 2, 3, 1-2, 2-1, 1-3, 3-1, 2-1-3, 3-1-2.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF830D/ae28806f7f5a770594827dbb3352d89115c44dfa.png)Singer $ 2 $ -house

## 样例 #1

### 输入

```
2

```

### 输出

```
9

```

## 样例 #2

### 输入

```
3

```

### 输出

```
245

```

## 样例 #3

### 输入

```
20

```

### 输出

```
550384565

```

