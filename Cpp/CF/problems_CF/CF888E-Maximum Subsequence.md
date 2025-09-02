---
title: "Maximum Subsequence"
layout: "post"
diff: 普及+/提高
pid: CF888E
tag: ['搜索', '贪心', '枚举']
---

# Maximum Subsequence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and additionally an integer $ m $ . You have to choose some sequence of indices $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{1}&lt;b_{2}&lt;...&lt;b_{k}<=n $ ) in such a way that the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png) is maximized. Chosen sequence can be empty.

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=35 $ , $ 1<=m<=10^{9} $ ).

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 说明/提示

In the first example you can choose a sequence $ b={1,2} $ , so the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/08d6750b1b23699a8b513ddd01c316f10e6a789c.png) is equal to $ 7 $ (and that's $ 3 $ after taking it modulo $ 4 $ ).

In the second example you can choose a sequence $ b={3} $ .

## 样例 #1

### 输入

```
4 4
5 2 4 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 20
199 41 299

```

### 输出

```
19

```

