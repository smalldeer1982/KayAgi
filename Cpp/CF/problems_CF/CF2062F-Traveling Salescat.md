---
title: "Traveling Salescat"
layout: "post"
diff: 省选/NOI-
pid: CF2062F
tag: []
---

# Traveling Salescat

## 题目描述

You are a cat selling fun algorithm problems. Today, you want to recommend your fun algorithm problems to $ k $ cities.

There are a total of $ n $ cities, each with two parameters $ a_i $ and $ b_i $ . Between any two cities $ i,j $ ( $ i\ne j $ ), there is a bidirectional road with a length of $ \max(a_i + b_j , b_i + a_j) $ . The cost of a path is defined as the total length of roads between every two adjacent cities along the path.

For $ k=2,3,\ldots,n $ , find the minimum cost among all simple paths containing exactly $ k $ distinct cities.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 1500 $ ) — the number of test cases.

For each test case, the first line contains a single integer $ n $ ( $ 2 \leq n \leq 3\cdot 10^3 $ ) — the number of cities.

Then $ n $ lines follow, the $ i $ -th line contains two integers $ a_i,b_i $ ( $ 0 \leq a_i,b_i \leq 10^9 $ ) — the parameters of city $ i $ .

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 9\cdot 10^6 $ .

## 输出格式

For each test case, print $ n-1 $ integers in one line. The $ i $ -th integer represents the minimum cost when $ k=i+1 $ .

## 说明/提示

In the first test case:

- For $ k=2 $ , the optimal path is $ 1\to 2 $ with a cost of $ \max(0+1,2+2)=4 $ .
- For $ k=3 $ , the optimal path is $ 2\to 1\to 3 $ with a cost of $ \max(0+1,2+2)+\max(0+3,3+2)=4+5=9 $ .

In the second test case:

- For $ k=2 $ , the optimal path is $ 1\to 4 $ .
- For $ k=3 $ , the optimal path is $ 2\to 3\to 5 $ .
- For $ k=4 $ , the optimal path is $ 4\to 1\to 3\to 5 $ .
- For $ k=5 $ , the optimal path is $ 5\to 2\to 3\to 1\to 4 $ .

## 样例 #1

### 输入

```
3
3
0 2
2 1
3 3
5
2 7
7 5
6 3
1 8
7 5
8
899167687 609615846
851467150 45726720
931502759 23784096
918190644 196992738
142090421 475722765
409556751 726971942
513558832 998277529
294328304 434714258
```

### 输出

```
4 9 
10 22 34 46 
770051069 1655330585 2931719265 3918741472 5033924854 6425541981 7934325514
```

