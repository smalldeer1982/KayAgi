---
title: "Array Craft"
layout: "post"
diff: 普及-
pid: CF1990B
tag: []
---

# Array Craft

## 题目描述

For an array $ b $ of size $ m $ , we define:

- the maximum prefix position of $ b $ is the smallest index $ i $ that satisfies $ b_1+\ldots+b_i=\max_{j=1}^{m}(b_1+\ldots+b_j) $ ;
- the maximum suffix position of $ b $ is the largest index $ i $ that satisfies $ b_i+\ldots+b_m=\max_{j=1}^{m}(b_j+\ldots+b_m) $ .

You are given three integers $ n $ , $ x $ , and $ y $ ( $ x > y $ ). Construct an array $ a $ of size $ n $ satisfying:

- $ a_i $ is either $ 1 $ or $ -1 $ for all $ 1 \le i \le n $ ;
- the maximum prefix position of $ a $ is $ x $ ;
- the maximum suffix position of $ a $ is $ y $ .

If there are multiple arrays that meet the conditions, print any. It can be proven that such an array always exists under the given conditions.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

For each test case:

- The only line contains three integers $ n $ , $ x $ , and $ y $ ( $ 2 \leq n \leq 10^5, 1 \le y \lt x \le n) $ .

It is guaranteed that the sum of $ n $ over all test cases will not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ n $ space-separated integers $ a_1, a_2, \ldots, a_n $ in a new line.

## 说明/提示

In the second test case,

- $ i=x=4 $ is the smallest index that satisfies $ a_1+\ldots +a_i=\max_{j=1}^{n}(a_1+\ldots+a_j)=2 $ ;
- $ i=y=3 $ is the greatest index that satisfies $ a_i+\ldots +a_n=\max_{j=1}^{n}(a_j+\ldots+a_n)=2 $ .

Thus, the array $ a=[1,-1,1,1] $ is considered correct.

## 样例 #1

### 输入

```
3
2 2 1
4 4 3
6 5 1
```

### 输出

```
1 1
1 -1 1 1
1 1 -1 1 1 -1
```

