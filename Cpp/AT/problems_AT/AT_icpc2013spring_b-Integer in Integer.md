---
title: "Integer in Integer"
layout: "post"
diff: 难度0
pid: AT_icpc2013spring_b
tag: []
---

# Integer in Integer

## 题目描述

请统计某个给定范围 $\lbrack A,B \rbrack \lparen 0 \leq A \leq B \leq 10^{10000} \rparen$ 的所有整数中，数 $C \lparen 0 \leq C \leq 10^{500} \rparen$ 出现的次数，结果对 $10^{9} + 7$ 取模。

例如，在样例2中， $33$ 在 $333$ 中出现了 $2$ 次，在 $334$ 中出现了 $1$ 次。所以 $\lbrack 333,334 \rbrack$ 中 $33$ 出现了 $3$ 次。

## 输入格式

1行，3个整数，分别表示 $A,B,C$ 。

## 输出格式

1个整数，表示范围 $\lbrack A,B \rbrack$ 间所有整数中 $C$ 出现的次数，答案对 $10^{9} + 7$ 取模。

#  输入输出样例
输入 #1

`1 3 2`

输出 #1

`1`

输入 #2

`333 334 33`

输出 #2

`3`

输入 #3

`0 10 0`

输出 #3

`2`

