---
title: "Three Threadlets"
layout: "post"
diff: 普及-
pid: CF1881B
tag: []
---

# Three Threadlets

## 题目描述

Once upon a time, bartender Decim found three threadlets and a pair of scissors.

In one operation, Decim chooses any threadlet and cuts it into two threadlets, whose lengths are positive integers and their sum is equal to the length of the threadlet being cut.

For example, he can cut a threadlet of length $ 5 $ into threadlets of lengths $ 2 $ and $ 3 $ , but he cannot cut it into threadlets of lengths $ 2.5 $ and $ 2.5 $ , or lengths $ 0 $ and $ 5 $ , or lengths $ 3 $ and $ 4 $ .

Decim can perform at most three operations. He is allowed to cut the threadlets obtained from previous cuts. Will he be able to make all the threadlets of equal length?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follows the description of each test case.

In a single line of each test case, there are three integers $ a $ , $ b $ , $ c $ ( $ 1 \le a, b, c \le 10^9 $ ) — the lengths of the threadlets.

## 输出格式

For each test case, output "YES" if it is possible to make all the threadlets of equal length by performing at most three operations, otherwise output "NO".

You can output "YES" and "NO" in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

Let's consider some testcases of the first test.

In the first testcase, you can apply following operations:

 $ 1, 3, 2 \to 1, 2, 1, 2 \to 1, 1, 1, 1, 2 \to 1, 1, 1, 1, 1, 1 $ .

In the second testcase, you can do nothing, the threadlets are already of equal length.

In the third testcase, it isn't possible to make threadlets of equal length.

## 样例 #1

### 输入

```
15
1 3 2
5 5 5
6 36 12
7 8 7
6 3 3
4 4 12
12 6 8
1000000000 1000000000 1000000000
3 7 1
9 9 1
9 3 6
2 8 2
5 3 10
8 4 8
2 8 4
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
YES
NO
NO
YES
YES
NO
YES
NO
```

