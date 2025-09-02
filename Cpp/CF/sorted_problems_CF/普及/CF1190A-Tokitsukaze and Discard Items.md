---
title: "Tokitsukaze and Discard Items"
layout: "post"
diff: 普及/提高-
pid: CF1190A
tag: []
---

# Tokitsukaze and Discard Items

## 题目描述

Recently, Tokitsukaze found an interesting game. Tokitsukaze had $ n $ items at the beginning of this game. However, she thought there were too many items, so now she wants to discard $ m $ ( $ 1 \le m \le n $ ) special items of them.

These $ n $ items are marked with indices from $ 1 $ to $ n $ . In the beginning, the item with index $ i $ is placed on the $ i $ -th position. Items are divided into several pages orderly, such that each page contains exactly $ k $ positions and the last positions on the last page may be left empty.

Tokitsukaze would do the following operation: focus on the first special page that contains at least one special item, and at one time, Tokitsukaze would discard all special items on this page. After an item is discarded or moved, its old position would be empty, and then the item below it, if exists, would move up to this empty position. The movement may bring many items forward and even into previous pages, so Tokitsukaze would keep waiting until all the items stop moving, and then do the operation (i.e. check the special page and discard the special items) repeatedly until there is no item need to be discarded.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1190A/a059bb92f5a4888ea9bb5a2b1a83486b43dcecf3.png)Consider the first example from the statement: $ n=10 $ , $ m=4 $ , $ k=5 $ , $ p=[3, 5, 7, 10] $ . The are two pages. Initially, the first page is special (since it is the first page containing a special item). So Tokitsukaze discards the special items with indices $ 3 $ and $ 5 $ . After, the first page remains to be special. It contains $ [1, 2, 4, 6, 7] $ , Tokitsukaze discards the special item with index $ 7 $ . After, the second page is special (since it is the first page containing a special item). It contains $ [9, 10] $ , Tokitsukaze discards the special item with index $ 10 $ .Tokitsukaze wants to know the number of operations she would do in total.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n \le 10^{18} $ , $ 1 \le m \le 10^5 $ , $ 1 \le m, k \le n $ ) — the number of items, the number of special items to be discarded and the number of positions in each page.

The second line contains $ m $ distinct integers $ p_1, p_2, \ldots, p_m $ ( $ 1 \le p_1 < p_2 < \ldots < p_m \le n $ ) — the indices of special items which should be discarded.

## 输出格式

Print a single integer — the number of operations that Tokitsukaze would do in total.

## 说明/提示

For the first example:

- In the first operation, Tokitsukaze would focus on the first page $ [1, 2, 3, 4, 5] $ and discard items with indices $ 3 $ and $ 5 $ ;
- In the second operation, Tokitsukaze would focus on the first page $ [1, 2, 4, 6, 7] $ and discard item with index $ 7 $ ;
- In the third operation, Tokitsukaze would focus on the second page $ [9, 10] $ and discard item with index $ 10 $ .

For the second example, Tokitsukaze would focus on the second page $ [6, 7, 8, 9, 10] $ and discard all special items at once.

## 样例 #1

### 输入

```
10 4 5
3 5 7 10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
13 4 5
7 8 9 10

```

### 输出

```
1

```

