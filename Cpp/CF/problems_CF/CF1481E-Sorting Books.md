---
title: "Sorting Books"
layout: "post"
diff: 省选/NOI-
pid: CF1481E
tag: []
---

# Sorting Books

## 题目描述

One day you wanted to read something, so you went to your bookshelf to grab some book. But when you saw how messy the bookshelf was you decided to clean it up first.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481E/eb717b77908d0758f813f3cb2f376ac8a23aad06.png)There are $ n $ books standing in a row on the shelf, the $ i $ -th book has color $ a_i $ .

You'd like to rearrange the books to make the shelf look beautiful. The shelf is considered beautiful if all books of the same color are next to each other.

In one operation you can take one book from any position on the shelf and move it to the right end of the shelf.

What is the minimum number of operations you need to make the shelf beautiful?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ) — the number of books.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — the book colors.

## 输出格式

Output the minimum number of operations to make the shelf beautiful.

## 说明/提示

In the first example, we have the bookshelf $ [1, 2, 2, 1, 3] $ and can, for example:

1. take a book on position $ 4 $ and move to the right end: we'll get $ [1, 2, 2, 3, 1] $ ;
2. take a book on position $ 1 $ and move to the right end: we'll get $ [2, 2, 3, 1, 1] $ .

In the second example, we can move the first book to the end of the bookshelf and get $ [2,2,1,1,1] $ .

## 样例 #1

### 输入

```
5
1 2 2 1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
1 2 2 1 1
```

### 输出

```
1
```

