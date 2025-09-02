---
title: "Valiant's New Map"
layout: "post"
diff: 普及+/提高
pid: CF1731D
tag: ['二分', '前缀和']
---

# Valiant's New Map

## 题目描述

Game studio "DbZ Games" wants to introduce another map in their popular game "Valiant". This time, the map named "Panvel" will be based on the city of Mumbai.

Mumbai can be represented as $ n \times m $ cellular grid. Each cell $ (i, j) $ ( $ 1 \le i \le n $ ; $ 1 \le j \le m $ ) of the grid is occupied by a cuboid building of height $ a_{i,j} $ .

This time, DbZ Games want to make a map that has perfect vertical gameplay. That's why they want to choose an $ l \times l $ square inside Mumbai, such that each building inside the square has a height of at least $ l $ .

Can you help DbZ Games find such a square of the maximum possible size $ l $ ?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 1000 $ ). Description of the test cases follows.

The first line of each test case contains two positive integers $ n $ and $ m $ ( $ 1 \le n \le m $ ; $ 1 \leq n \cdot m \leq 10^6 $ ).

The $ i $ -th of next $ n $ lines contains $ m $ integers $ a_{i,1}, a_{i,2}, \dots, a_{i,m} $ ( $ 1 \leq a_{i,j} \leq 10^6 $ ) — heights of buildings on the $ i $ -th row.

It's guaranteed that the sum of $ n \cdot m $ over all test cases doesn't exceed $ 10^6 $ .

## 输出格式

For each test case, print the maximum side length $ l $ of the square DbZ Games can choose.

## 说明/提示

In the first test case, we can choose the square of side $ l = 2 $ (i. e. the whole grid) since the heights of all buildings are greater than or equal to $ 2 $ .

In the second test case, we can only choose the side as $ 1 $ , so the answer is $ 1 $ .

In the third test case, there are no squares of size $ 2 $ that have all buildings of height at least $ 2 $ , so the answer is $ 1 $ .

## 样例 #1

### 输入

```
4
2 2
2 3
4 5
1 3
1 2 3
2 3
4 4 3
2 1 4
5 6
1 9 4 6 5 8
10 9 5 8 11 6
24 42 32 8 11 1
23 1 9 69 13 3
13 22 60 12 14 17
```

### 输出

```
2
1
1
3
```

