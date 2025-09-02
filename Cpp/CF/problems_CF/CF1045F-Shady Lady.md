---
title: "Shady Lady"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1045F
tag: []
---

# Shady Lady

## 题目描述

Ani and Borna are playing a short game on a two-variable polynomial. It's a special kind of a polynomial: the monomials are fixed, but all of its coefficients are fill-in-the-blanks dashes, e.g. $ $$$ \_ xy + \_ x^4 y^7 + \_ x^8 y^3 + \ldots  $ $ </p><p>Borna will fill in the blanks with positive integers. He wants the polynomial to be <span class="tex-font-style-underline">bounded from below</span>, i.e. his goal is to make sure there exists a real number  $ M $  such that the value of the polynomial at any point is greater than  $ M$$$.

 Ani is mischievous, and wants the polynomial to be unbounded. Along with stealing Borna's heart, she can also steal parts of polynomials. Ani is only a petty kind of thief, though: she can only steal at most one monomial from the polynomial before Borna fills in the blanks.

If Ani and Borna play their only moves optimally, who wins?

## 输入格式

The first line contains a positive integer $ N $ $ (2 \leq N \leq 200\, 000) $ , denoting the number of the terms in the starting special polynomial.

Each of the following $ N $ lines contains a description of a monomial: the $ k $ -th line contains two \*\*space\*\*-separated integers $ a_k $ and $ b_k $ $ (0 \leq a_k, b_k \leq 10^9 $ ) which mean the starting polynomial has the term $ \_ x^{a_k} y^{b_k} $ . It is guaranteed that for $ k \neq l $ , either $ a_k \neq a_l $ or $ b_k \neq b_l $ .

## 输出格式

If Borna can always choose the coefficients such that the resulting polynomial is bounded from below, regardless of what monomial Ani steals, output "Borna". Else, output "Ani".

You shouldn't output the quotation marks.

## 说明/提示

In the first sample, the initial polynomial is $ \_xy+ \_x^2 + \_y^2 $ . If Ani steals the $ \_y^2 $ term, Borna is left with $ \_xy+\_x^2 $ . Whatever positive integers are written on the blanks, $ y \rightarrow -\infty $ and $ x := 1 $ makes the whole expression go to negative infinity.

In the second sample, the initial polynomial is $ \_1 + \_x + \_x^2 + \_x^8 $ . One can check that no matter what term Ani steals, Borna can always win.

## 样例 #1

### 输入

```
3
1 1
2 0
0 2

```

### 输出

```
Ani

```

## 样例 #2

### 输入

```
4
0 0
0 1
0 2
0 8

```

### 输出

```
Borna

```

