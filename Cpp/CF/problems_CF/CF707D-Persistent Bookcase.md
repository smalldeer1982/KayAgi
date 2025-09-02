---
title: "Persistent Bookcase"
layout: "post"
diff: 提高+/省选-
pid: CF707D
tag: []
---

# Persistent Bookcase

## 题目描述

Recently in school Alina has learned what are the persistent data structures: they are data structures that always preserves the previous version of itself and access to it when it is modified.

After reaching home Alina decided to invent her own persistent data structure. Inventing didn't take long: there is a bookcase right behind her bed. Alina thinks that the bookcase is a good choice for a persistent data structure. Initially the bookcase is empty, thus there is no book at any position at any shelf.

The bookcase consists of $ n $ shelves, and each shelf has exactly $ m $ positions for books at it. Alina enumerates shelves by integers from $ 1 $ to $ n $ and positions at shelves — from $ 1 $ to $ m $ . Initially the bookcase is empty, thus there is no book at any position at any shelf in it.

Alina wrote down $ q $ operations, which will be consecutively applied to the bookcase. Each of the operations has one of four types:

- $ 1 $ $ i $ $ j $ — Place a book at position $ j $ at shelf $ i $ if there is no book at it.
- $ 2 $ $ i $ $ j $ — Remove the book from position $ j $ at shelf $ i $ if there is a book at it.
- $ 3 $ $ i $ — Invert book placing at shelf $ i $ . This means that from every position at shelf $ i $ which has a book at it, the book should be removed, and at every position at shelf $ i $ which has not book at it, a book should be placed.
- $ 4 $ $ k $ — Return the books in the bookcase in a state they were after applying $ k $ -th operation. In particular, $ k=0 $ means that the bookcase should be in initial state, thus every book in the bookcase should be removed from its position.

After applying each of operation Alina is interested in the number of books in the bookcase. Alina got 'A' in the school and had no problem finding this values. Will you do so?

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n,m<=10^{3} $ , $ 1<=q<=10^{5} $ ) — the bookcase dimensions and the number of operations respectively.

The next $ q $ lines describes operations in chronological order — $ i $ -th of them describes $ i $ -th operation in one of the four formats described in the statement.

It is guaranteed that shelf indices and position indices are correct, and in each of fourth-type operation the number $ k $ corresponds to some operation before it or equals to $ 0 $ .

## 输出格式

For each operation, print the number of books in the bookcase after applying it in a separate line. The answers should be printed in chronological order.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF707D/43cb8952ee4fc8994bedde8168b22c25f3bba0de.png)This image illustrates the second sample case.

## 样例 #1

### 输入

```
2 3 3
1 1 1
3 2
4 0

```

### 输出

```
1
4
0

```

## 样例 #2

### 输入

```
4 2 6
3 2
2 2 2
3 3
3 2
2 2 2
3 2

```

### 输出

```
2
1
3
3
2
4

```

## 样例 #3

### 输入

```
2 2 2
3 2
2 2 1

```

### 输出

```
2
1

```

