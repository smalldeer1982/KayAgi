---
title: "Half-sum"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1817E
tag: []
---

# Half-sum

## 题目描述

You're given a multiset of non-negative integers $ \{a_1, a_2, \dots, a_n\} $ .

In one step you take two elements $ x $ and $ y $ of the multiset, remove them and insert their mean value $ \frac{x + y}{2} $ back into the multiset.

You repeat the step described above until you are left with only two numbers $ A $ and $ B $ . What is the maximum possible value of their absolute difference $ |A-B| $ ?

Since the answer is not an integer number, output it modulo $ 10^9+7 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 100 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^6 $ ) — the size of the multiset.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the elements of the multiset.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer, the answer to the problem modulo $ 10^9+7 $ .

Formally, let $ M = 10^9+7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output an integer $ x $ such that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first case, you can't do any operations, so the answer is $ |7-3|=4 $ .

In the second case, one of the optimal sequence of operations:

1. Substitute $ 1 $ and $ 2 $ with $ 1.5 $ ;
2. Substitute $ 10 $ and $ 11 $ with $ 10.5 $ ;
3. The difference between $ 1.5 $ and $ 10.5 $ is $ 9 $ .

In the third case, the exact answer is $ \frac{3}{2} $ , and $ 500\,000\,005 \cdot 2 \equiv 3 \pmod{10^9+7} $ .

## 样例 #1

### 输入

```
5
2
7 3
4
1 2 10 11
3
1 2 3
6
64 32 64 16 64 0
4
1 1 1 1
```

### 输出

```
4
9
500000005
59
0
```

