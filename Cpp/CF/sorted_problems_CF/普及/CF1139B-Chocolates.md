---
title: "Chocolates"
layout: "post"
diff: 普及/提高-
pid: CF1139B
tag: []
---

# Chocolates

## 题目描述

You went to the store, selling $ n $ types of chocolates. There are $ a_i $ chocolates of type $ i $ in stock.

You have unlimited amount of cash (so you are not restricted by any prices) and want to buy as many chocolates as possible. However if you buy $ x_i $ chocolates of type $ i $ (clearly, $ 0 \le x_i \le a_i $ ), then for all $ 1 \le j < i $ at least one of the following must hold:

- $ x_j = 0 $ (you bought zero chocolates of type $ j $ )
- $ x_j < x_i $ (you bought less chocolates of type $ j $ than of type $ i $ )

For example, the array $ x = [0, 0, 1, 2, 10] $ satisfies the requirement above (assuming that all $ a_i \ge x_i $ ), while arrays $ x = [0, 1, 0] $ , $ x = [5, 5] $ and $ x = [3, 2] $ don't.

Calculate the maximum number of chocolates you can buy.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ), denoting the number of types of chocolate.

The next line contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 10^9 $ ), denoting the number of chocolates of each type.

## 输出格式

Print the maximum number of chocolates you can buy.

## 说明/提示

In the first example, it is optimal to buy: $ 0 + 0 + 1 + 3 + 6 $ chocolates.

In the second example, it is optimal to buy: $ 1 + 2 + 3 + 4 + 10 $ chocolates.

In the third example, it is optimal to buy: $ 0 + 0 + 0 + 1 $ chocolates.

## 样例 #1

### 输入

```
5
1 2 1 3 6

```

### 输出

```
10
```

## 样例 #2

### 输入

```
5
3 2 5 4 10

```

### 输出

```
20
```

## 样例 #3

### 输入

```
4
1 1 1 1

```

### 输出

```
1
```

