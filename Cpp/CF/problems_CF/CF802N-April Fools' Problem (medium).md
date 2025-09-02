---
title: "April Fools' Problem (medium)"
layout: "post"
diff: 省选/NOI-
pid: CF802N
tag: []
---

# April Fools' Problem (medium)

## 题目描述

The marmots need to prepare $ k $ problems for HC $ ^{2} $ over $ n $ days. Each problem, once prepared, also has to be printed.

The preparation of a problem on day $ i $ (at most one per day) costs $ a_{i} $ CHF, and the printing of a problem on day $ i $ (also at most one per day) costs $ b_{i} $ CHF. Of course, a problem cannot be printed before it has been prepared (but doing both on the same day is fine).

What is the minimum cost of preparation and printing?

## 输入格式

The first line of input contains two space-separated integers $ n $ and $ k $ ( $ 1<=k<=n<=2200 $ ). The second line contains $ n $ space-separated integers $ a_{1},...,a_{n} $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802N/e4754a7339522010b5528b1716cf92621f902f03.png)) — the preparation costs. The third line contains $ n $ space-separated integers $ b_{1},...,b_{n} $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802N/a8ea7f0bb23797e6537e2f5e7c007f9d7fcd2a0d.png)) — the printing costs.

## 输出格式

Output the minimum cost of preparation and printing $ k $ problems — that is, the minimum possible sum $ a_{i1}+a_{i2}+...+a_{ik}+b_{j1}+b_{j2}+...+b_{jk} $ , where $ 1<=i_{1}&lt;i_{2}&lt;...&lt;i_{k}<=n $ , $ 1<=j_{1}&lt;j_{2}&lt;...&lt;j_{k}<=n $ and $ i_{1}<=j_{1} $ , $ i_{2}<=j_{2} $ , ..., $ i_{k}<=j_{k} $ .

## 说明/提示

In the sample testcase, one optimum solution is to prepare the first problem on day $ 1 $ and print it on day $ 1 $ , prepare the second problem on day $ 2 $ and print it on day $ 4 $ , prepare the third problem on day $ 3 $ and print it on day $ 5 $ , and prepare the fourth problem on day $ 6 $ and print it on day $ 8 $ .

## 样例 #1

### 输入

```
8 4
3 8 7 9 9 4 6 8
2 5 9 4 3 8 9 1

```

### 输出

```
32
```

