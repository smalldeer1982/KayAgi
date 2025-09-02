---
title: "Maximum Crossings (Easy Version)"
layout: "post"
diff: 普及-
pid: CF1676H1
tag: ['模拟']
---

# Maximum Crossings (Easy Version)

## 题目描述

The only difference between the two versions is that in this version $ n \leq 1000 $ and the sum of $ n $ over all test cases does not exceed $ 1000 $ .

A terminal is a row of $ n $ equal segments numbered $ 1 $ to $ n $ in order. There are two terminals, one above the other.

You are given an array $ a $ of length $ n $ . For all $ i = 1, 2, \dots, n $ , there should be a straight wire from some point on segment $ i $ of the top terminal to some point on segment $ a_i $ of the bottom terminal. For example, the following pictures show two possible wirings if $ n=7 $ and $ a=[4,1,4,6,7,7,5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H1/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)A crossing occurs when two wires share a point in common. In the picture above, crossings are circled in red.

What is the maximum number of crossings there can be if you place the wires optimally?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 1000 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of the array.

The sum of $ n $ across all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case, output a single integer — the maximum number of crossings there can be if you place the wires optimally.

## 说明/提示

The first test case is shown in the second picture in the statement.

In the second test case, the only wiring possible has the two wires cross, so the answer is $ 1 $ .

In the third test case, the only wiring possible has one wire, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2
```

### 输出

```
6
1
0
3
```

