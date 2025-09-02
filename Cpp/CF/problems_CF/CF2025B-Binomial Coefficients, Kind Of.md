---
title: "Binomial Coefficients, Kind Of"
layout: "post"
diff: 普及/提高-
pid: CF2025B
tag: ['数学']
---

# Binomial Coefficients, Kind Of

## 题目描述

Recently, akshiM met a task that needed binomial coefficients to solve. He wrote a code he usually does that looked like this:

```
<pre class="verbatim">    for (int n = 0; n < N; n++) { // loop over n from 0 to N-1 (inclusive)<br></br>        C[n][0] = 1;<br></br>        C[n][n] = 1;<br></br>        for (int k = 1; k < n; k++) // loop over k from 1 to n-1 (inclusive)<br></br>            C[n][k] = C[n][k - 1] + C[n - 1][k - 1];<br></br>    }<br></br>
```

Unfortunately, he made an error, since the right formula is the following:

```
<pre class="verbatim">            C[n][k] = C[n - 1][k] + C[n - 1][k - 1]<br></br>
```

But his team member keblidA is interested in values that were produced using the wrong formula. Please help him to calculate these coefficients for $ t $ various pairs $ (n_i, k_i) $ . Note that they should be calculated according to the first (wrong) formula.

Since values $ C[n_i][k_i] $ may be too large, print them modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of pairs. Next, $ t $ pairs are written in two lines.

The second line contains $ t $ integers $ n_1, n_2, \dots, n_t $ ( $ 2 \le n_i \le 10^5 $ ).

The third line contains $ t $ integers $ k_1, k_2, \dots, k_t $ ( $ 1 \le k_i < n_i $ ).

## 输出格式

Print $ t $ integers $ C[n_i][k_i] $ modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
7
2 5 5 100000 100000 100000 100000
1 2 3 1 33333 66666 99999
```

### 输出

```
2
4
8
2
326186014
984426998
303861760
```

