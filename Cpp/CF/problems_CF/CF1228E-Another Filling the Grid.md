---
title: "Another Filling the Grid"
layout: "post"
diff: 提高+/省选-
pid: CF1228E
tag: []
---

# Another Filling the Grid

## 题目描述

You have $ n \times n $ square grid and an integer $ k $ . Put an integer in each cell while satisfying the conditions below.

- All numbers in the grid should be between $ 1 $ and $ k $ inclusive.
- Minimum number of the $ i $ -th row is $ 1 $ ( $ 1 \le i \le n $ ).
- Minimum number of the $ j $ -th column is $ 1 $ ( $ 1 \le j \le n $ ).

Find the number of ways to put integers in the grid. Since the answer can be very large, find the answer modulo $ (10^{9} + 7) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228E/461043b230da4734e02a378fa88336fd5a76ad41.png) These are the examples of valid and invalid grid when $ n=k=2 $ .

## 输入格式

The only line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 250 $ , $ 1 \le k \le 10^{9} $ ).

## 输出格式

Print the answer modulo $ (10^{9} + 7) $ .

## 说明/提示

In the first example, following $ 7 $ cases are possible.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228E/50e0a56b2ebcb373865c65f252219c6e6fb65791.png)In the second example, make sure you print the answer modulo $ (10^{9} + 7) $ .

## 样例 #1

### 输入

```
2 2

```

### 输出

```
7

```

## 样例 #2

### 输入

```
123 456789

```

### 输出

```
689974806

```

