---
title: "TIP3 - Totient in permutation (hard)"
layout: "post"
diff: 难度0
pid: SP13167
tag: []
---

# TIP3 - Totient in permutation (hard)

## 题目描述

In number theory, Euler's totient (or PHI function), is an arithmetic function that counts the number of positive integers less than or equal to a positive integer N that are relatively prime to this number N.

 That is, if N is a positive integer, then PHI(N) is the number of integers K for which GCD(N, K) = 1 and 1

 Interestingly, PHI(87109)=79180, and it can be seen that 87109 is a permutation of 79180.

## 输入格式

There is only one number M.

## 输出格式

For the given M, you have to print on a single line the value of N, for which 1 < N < M, PHI(N) is a permutation of N and the ratio N/PHI(N) produces a minimum. If there's several answers output the greatest, or if need, "No solution." without quotes. Leading zeros are not allowed for integers greater than 0.

## 样例 #1

### 输入

```
22
```

### 输出

```
21


Input:
222

Output:
63


Input:
2222

Output:
291
```

