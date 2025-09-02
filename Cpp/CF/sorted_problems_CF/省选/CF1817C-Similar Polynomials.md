---
title: "Similar Polynomials"
layout: "post"
diff: 省选/NOI-
pid: CF1817C
tag: []
---

# Similar Polynomials

## 题目描述

A polynomial $ A(x) $ of degree $ d $ is an expression of the form $ A(x) = a_0 + a_1 x + a_2 x^2 + \dots + a_d x^d $ , where $ a_i $ are integers, and $ a_d \neq 0 $ . Two polynomials $ A(x) $ and $ B(x) $ are called similar if there is an integer $ s $ such that for any integer $ x $ it holds that

 $ $$$ B(x) \equiv A(x+s) \pmod{10^9+7}.  $ $ </p><p>For two similar polynomials  $ A(x) $  and  $ B(x) $  of degree  $ d $ , you're given their values in the points  $ x=0,1,\\dots, d $  modulo  $ 10^9+7 $ .</p><p>Find a value  $ s $  such that  $ B(x) \\equiv A(x+s) \\pmod{10^9+7} $  for all integers  $ x$$$.

## 输入格式

The first line contains a single integer $ d $ ( $ 1 \le d \le 2\,500\,000 $ ).

The second line contains $ d+1 $ integers $ A(0), A(1), \ldots, A(d) $ ( $ 0 \le A(i) < 10^9+7 $ ) — the values of the polynomial $ A(x) $ .

The third line contains $ d+1 $ integers $ B(0), B(1), \ldots, B(d) $ ( $ 0 \le B(i) < 10^9+7 $ ) — the values of the polynomial $ B(x) $ .

It is guaranteed that $ A(x) $ and $ B(x) $ are similar and that the leading coefficients (i.e., the coefficients in front of $ x^d $ ) of $ A(x) $ and $ B(x) $ are not divisible by $ 10^9+7 $ .

## 输出格式

Print a single integer $ s $ ( $ 0 \leq s < 10^9+7 $ ) such that $ B(x) \equiv A(x+s) \pmod{10^9+7} $ for all integers $ x $ .

If there are multiple solutions, print any.

## 说明/提示

In the first example, $ A(x) \equiv x-1 \pmod{10^9+7} $ and $ B(x)\equiv x+2 \pmod{10^9+7} $ . They're similar because $ $$$B(x) \equiv A(x+3) \pmod{10^9+7}. $ $ </p><p>In the second example,  $ A(x) \\equiv (x+1)^2 \\pmod{10^9+7} $  and  $ B(x) \\equiv (x+10)^2 \\pmod{10^9+7} $ , hence  $ $ B(x) \equiv A(x+9) \pmod{10^9+7}. $ $$$

## 样例 #1

### 输入

```
1
1000000006 0
2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
1 4 9
100 121 144
```

### 输出

```
9
```

