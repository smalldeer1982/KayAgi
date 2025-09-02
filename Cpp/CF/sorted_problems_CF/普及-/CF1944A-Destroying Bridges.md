---
title: "Destroying Bridges"
layout: "post"
diff: 普及-
pid: CF1944A
tag: ['图论']
---

# Destroying Bridges

## 题目描述

There are $ n $ islands, numbered $ 1, 2, \ldots, n $ . Initially, every pair of islands is connected by a bridge. Hence, there are a total of $ \frac{n (n - 1)}{2} $ bridges.

Everule lives on island $ 1 $ and enjoys visiting the other islands using bridges. Dominater has the power to destroy at most $ k $ bridges to minimize the number of islands that Everule can reach using (possibly multiple) bridges.

Find the minimum number of islands (including island $ 1 $ ) that Everule can visit if Dominater destroys bridges optimally.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first and only line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 100 $ , $ 0 \le k \le \frac{n \cdot (n - 1)}{2} $ ).

## 输出格式

For each test case, output the minimum number of islands that Everule can visit if Dominater destroys bridges optimally.

## 说明/提示

In the first test case, since no bridges can be destroyed, all the islands will be reachable.

In the second test case, you can destroy the bridge between islands $ 1 $ and $ 2 $ . Everule will not be able to visit island $ 2 $ but can still visit island $ 1 $ . Therefore, the total number of islands that Everule can visit is $ 1 $ .

In the third test case, Everule always has a way of reaching all islands despite what Dominater does. For example, if Dominater destroyed the bridge between islands $ 1 $ and $ 2 $ , Everule can still visit island $ 2 $ by traveling by $ 1 \to 3 \to 2 $ as the bridges between $ 1 $ and $ 3 $ , and between $ 3 $ and $ 2 $ are not destroyed.

In the fourth test case, you can destroy all bridges since $ k = \frac{n \cdot (n - 1)}{2} $ . Everule will be only able to visit $ 1 $ island (island $ 1 $ ).

## 样例 #1

### 输入

```
6
2 0
2 1
4 1
5 10
5 3
4 4
```

### 输出

```
2
1
4
1
5
1
```

