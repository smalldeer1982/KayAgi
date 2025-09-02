---
title: "The Ultimate Square"
layout: "post"
diff: 入门
pid: CF1748A
tag: []
---

# The Ultimate Square

## 题目描述

You have $ n $ rectangular wooden blocks, which are numbered from $ 1 $ to $ n $ . The $ i $ -th block is $ 1 $ unit high and $ \lceil \frac{i}{2} \rceil $ units long.

Here, $ \lceil \frac{x}{2} \rceil $ denotes the result of division of $ x $ by $ 2 $ , rounded up. For example, $ \lceil \frac{4}{2} \rceil = 2 $ and $ \lceil \frac{5}{2} \rceil = \lceil 2.5 \rceil = 3 $ .

For example, if $ n=5 $ , then the blocks have the following sizes: $ 1 \times 1 $ , $ 1 \times 1 $ , $ 1 \times 2 $ , $ 1 \times 2 $ , $ 1 \times 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1748A/19d3138a2c88b0952d5d3d3158c75a2a14071bba.png) The available blocks for $ n=5 $ Find the maximum possible side length of a square you can create using these blocks, without rotating any of them. Note that you don't have to use all of the blocks.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1748A/241be5d182fd6bff2bfe8df8e72795f57d91cb34.png) One of the ways to create $ 3 \times 3 $ square using blocks $ 1 $ through $ 5 $

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^9 $ ) — the number of blocks.

## 输出格式

For each test case, print one integer — the maximum possible side length of a square you can create.

## 说明/提示

In the first test case, you can create a $ 1 \times 1 $ square using only one of the blocks.

In the second test case, one of the possible ways to create a $ 3 \times 3 $ square is shown in the statement. It is impossible to create a $ 4 \times 4 $ or larger square, so the answer is $ 3 $ .

## 样例 #1

### 输入

```
3
2
5
197654321
```

### 输出

```
1
3
98827161
```

