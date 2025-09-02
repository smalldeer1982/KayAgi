---
title: "Anton and Ira"
layout: "post"
diff: 提高+/省选-
pid: CF584E
tag: []
---

# Anton and Ira

## 题目描述

Anton loves transforming one permutation into another one by swapping elements for money, and Ira doesn't like paying for stupid games. Help them obtain the required permutation by paying as little money as possible.

More formally, we have two permutations, $ p $ and $ s $ of numbers from $ 1 $ to $ n $ . We can swap $ p_{i} $ and $ p_{j} $ , by paying $ |i-j| $ coins for it. Find and print the smallest number of coins required to obtain permutation $ s $ from permutation $ p $ . Also print the sequence of swap operations at which we obtain a solution.

## 输入格式

The first line contains a single number $ n $ ( $ 1<=n<=2000 $ ) — the length of the permutations.

The second line contains a sequence of $ n $ numbers from $ 1 $ to $ n $ — permutation $ p $ . Each number from $ 1 $ to $ n $ occurs exactly once in this line.

The third line contains a sequence of $ n $ numbers from $ 1 $ to $ n $ — permutation $ s $ . Each number from $ 1 $ to $ n $ occurs once in this line.

## 输出格式

In the first line print the minimum number of coins that you need to spend to transform permutation $ p $ into permutation $ s $ .

In the second line print number $ k $ ( $ 0<=k<=2·10^{6} $ ) — the number of operations needed to get the solution.

In the next $ k $ lines print the operations. Each line must contain two numbers $ i $ and $ j $ ( $ 1<=i,j<=n $ , $ i≠j $ ), which means that you need to swap $ p_{i} $ and $ p_{j} $ .

It is guaranteed that the solution exists.

## 说明/提示

In the first sample test we swap numbers on positions 3 and 4 and permutation $ p $ becomes 4 2 3 1. We pay $ |3-4|=1 $ coins for that. On second turn we swap numbers on positions 1 and 3 and get permutation $ 3241 $ equal to $ s $ . We pay $ |3-1|=2 $ coins for that. In total we pay three coins.

## 样例 #1

### 输入

```
4
4 2 1 3
3 2 4 1

```

### 输出

```
3
2
4 3
3 1

```

