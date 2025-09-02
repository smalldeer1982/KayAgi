---
title: "Flower City Fence"
layout: "post"
diff: 普及-
pid: CF1862C
tag: []
---

# Flower City Fence

## 题目描述

Anya lives in the Flower City. By order of the city mayor, she has to build a fence for herself.

The fence consists of $ n $ planks, each with a height of $ a_i $ meters. According to the order, the heights of the planks must not increase. In other words, it is true that $ a_i \ge a_j $ for all $ i < j $ .

Anya became curious whether her fence is symmetrical with respect to the diagonal. In other words, will she get the same fence if she lays all the planks horizontally in the same order.

For example, for $ n = 5 $ , $ a = [5, 4, 3, 2, 1] $ , the fence is symmetrical. Because if all the planks are laid horizontally, the fence will be $ [5, 4, 3, 2, 1] $ , as shown in the diagram.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/bee85e28c2f6c75c9cfffe7860d8e27020ca6057.png) On the left is the fence $ [5, 4, 3, 2, 1] $ , on the right is the same fence laid horizontally

But for $ n = 3 $ , $ a = [4, 2, 1] $ , the fence is not symmetrical. Because if all the planks are laid horizontally, the fence will be $ [3, 2, 1, 1] $ , as shown in the diagram.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1862C/61240a948afb884e3b78ad7f150c3256a48031f7.png) On the left is the fence $ [4, 2, 1] $ , on the right is the same fence laid horizontally

Help Anya and determine whether her fence is symmetrical.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The description of the test cases follows.

The first line of a test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the fence.

The second line of a test case contains $ n $ integers $ a_1 \ge a_2 \ge a_3 \ge \dots \ge a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the heights of the planks.

The sum of the values of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if the fence is symmetrical, otherwise output "NO".

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes" and "YES" will be accepted as a positive answer.

## 说明/提示

In the first and second test cases of the example, the fence is symmetrical.

In the third test case of the example, the fence is not symmetrical. If the planks are laid horizontally, the fence will be $ [3, 2, 1, 1] $ .

In the fourth test case of the example, the fence is not symmetrical. If the planks are laid horizontally, the fence will be $ [1, 1] $ .

In the fifth and sixth test cases of the example, the fence is symmetrical.

In the seventh test case of the example, the fence is not symmetrical. If the planks are laid horizontally, the fence will be $ [2, 1, 1, 1, 1, 1] $ .

## 样例 #1

### 输入

```
7
5
5 4 3 2 1
3
3 1 1
3
4 2 1
1
2
5
5 3 3 1 1
5
5 5 5 3 3
2
6 1
```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
```

