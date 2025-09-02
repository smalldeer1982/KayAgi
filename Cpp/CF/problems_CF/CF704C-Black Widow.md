---
title: "Black Widow"
layout: "post"
diff: 省选/NOI-
pid: CF704C
tag: []
---

# Black Widow

## 题目描述

Natalia Romanova is trying to test something on the new gun S.H.I.E.L.D gave her. In order to determine the result of the test, she needs to find the number of answers to a certain equation. The equation is of form:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/1d8b978fb9a12b135427c0c260993d6889a8fc0c.png)

Where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/7fca95146e6c9642c62830d4709435706988c675.png) represents logical OR and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/4298d47c0191af3c0a3103f431751061bc7e2362.png) represents logical exclusive OR (XOR), and $ v_{i,j} $ are some boolean variables or their negations. Natalia calls the left side of the equation a XNF formula. Each statement in brackets is called a clause, and $ v_{i,j} $ are called literals.

In the equation Natalia has, the left side is actually a 2-XNF-2 containing variables $ x_{1},x_{2},...,x_{m} $ and their negations. An XNF formula is 2-XNF-2 if:

1. For each $ 1<=i<=n $ , $ k_{i}<=2 $ , i.e. the size of each clause doesn't exceed two.
2. Each variable occurs in the formula at most two times (with negation and without negation in total). Please note that it's possible that a variable occurs twice but its negation doesn't occur in any clause (or vice versa).

Natalia is given a formula of $ m $ variables, consisting of $ n $ clauses. Please, make sure to check the samples in order to properly understand how the formula looks like.

Natalia is more into fight than theory, so she asked you to tell her the number of answers to this equation. More precisely, you need to find the number of ways to set $ x_{1},...,x_{m} $ with $ true $ and $ false $ (out of total of $ 2^{m} $ ways) so that the equation is satisfied. Since this number can be extremely large, you need to print the answer modulo $ 10^{9}+7 $ .

Please, note that some variable may appear twice in one clause, or not appear in the equation at all (but still, setting it to $ false $ or $ true $ gives different ways to set variables).

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=100000 $ ) — the number of clauses and the number of variables respectively.

The next $ n $ lines contain the formula. The $ i $ -th of them starts with an integer $ k_{i} $ — the number of literals in the $ i $ -th clause. It is followed by $ k_{i} $ non-zero integers $ a_{i,1},...,a_{i,ki} $ . If $ a_{i,j}&gt;0 $ then $ v_{i,j} $ is $ x_{ai,j} $ otherwise it's negation of $ x_{-ai,j} $ ( $ 1<=k_{i}<=2 $ , $ -m<=a_{i,j}<=m $ , $ a_{i,j}≠0 $ ).

## 输出格式

Print the answer modulo $ 1000000007 $ ( $ 10^{9}+7 $ ) in one line.

## 说明/提示

The equation in the first sample is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/8a7d0715aca7a7756df4c64309d02f2f1b4790fe.png)The equation in the second sample is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/e73ae748289a1c91c6e0a8548db01f380614ddbc.png)The equation in the third sample is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/bdaba6b1526d3afbd73f7d5f247c3b948989c742.png)

## 样例 #1

### 输入

```
6 7
2 4 -2
2 6 3
2 -7 1
2 -5 1
2 3 6
2 -2 -5

```

### 输出

```
48

```

## 样例 #2

### 输入

```
8 10
1 -5
2 4 -6
2 -2 -6
2 -7 9
2 10 -1
2 3 -1
2 -8 9
2 5 8

```

### 输出

```
544

```

## 样例 #3

### 输入

```
2 3
2 1 1
2 -3 3

```

### 输出

```
4

```

