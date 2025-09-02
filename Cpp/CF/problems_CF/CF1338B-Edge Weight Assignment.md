---
title: "Edge Weight Assignment"
layout: "post"
diff: 普及+/提高
pid: CF1338B
tag: []
---

# Edge Weight Assignment

## 题目描述

You have unweighted tree of $ n $ vertices. You have to assign a positive weight to each edge so that the following condition would hold:

- For every two different leaves $ v_{1} $ and $ v_{2} $ of this tree, [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of weights of all edges on the simple path between $ v_{1} $ and $ v_{2} $ has to be equal to $ 0 $ .

Note that you can put very large positive integers (like $ 10^{(10^{10})} $ ).

It's guaranteed that such assignment always exists under given constraints. Now let's define $ f $ as the number of distinct weights in assignment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/eb47baeab358a9bf4d6536421055c2c258904b33.png) In this example, assignment is valid, because bitwise XOR of all edge weights between every pair of leaves is $ 0 $ . $ f $ value is $ 2 $ here, because there are $ 2 $ distinct edge weights( $ 4 $ and $ 5 $ ).![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/158a70d1382d5b7e8863700d0f77901af19c305f.png) In this example, assignment is invalid, because bitwise XOR of all edge weights between vertex $ 1 $ and vertex $ 6 $ ( $ 3, 4, 5, 4 $ ) is not $ 0 $ .

What are the minimum and the maximum possible values of $ f $ for the given tree? Find and print both.

## 输入格式

The first line contains integer $ n $ ( $ 3 \le n \le 10^{5} $ ) — the number of vertices in given tree.

The $ i $ -th of the next $ n-1 $ lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ 1 \le a_{i} \lt b_{i} \le n $ ) — it means there is an edge between $ a_{i} $ and $ b_{i} $ . It is guaranteed that given graph forms tree of $ n $ vertices.

## 输出格式

Print two integers — the minimum and maximum possible value of $ f $ can be made from valid assignment of given tree. Note that it's always possible to make an assignment under given constraints.

## 说明/提示

In the first example, possible assignments for each minimum and maximum are described in picture below. Of course, there are multiple possible assignments for each minimum and maximum.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/c4eae7135fc2816569401e9d249b68afcb80223d.png)In the second example, possible assignments for each minimum and maximum are described in picture below. The $ f $ value of valid assignment of this tree is always $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/baad69bf823b2a9aa4bb5b201a45aae8769d51f6.png)In the third example, possible assignments for each minimum and maximum are described in picture below. Of course, there are multiple possible assignments for each minimum and maximum.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/4ce205cbdc1e4310ee123b92671ae7a1941bacd7.png)

## 样例 #1

### 输入

```
6
1 3
2 3
3 4
4 5
5 6
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
6
1 3
2 3
3 4
4 5
4 6
```

### 输出

```
3 3
```

## 样例 #3

### 输入

```
7
1 2
2 7
3 4
4 7
5 6
6 7
```

### 输出

```
1 6
```

