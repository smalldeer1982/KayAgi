---
title: "Matching Numbers"
layout: "post"
diff: 普及/提高-
pid: CF1788C
tag: []
---

# Matching Numbers

## 题目描述

You are given an integer $ n $ . Pair the integers $ 1 $ to $ 2n $ (i.e. each integer should be in exactly one pair) so that each sum of matched pairs is consecutive and distinct.

Formally, let $ (a_i, b_i) $ be the pairs that you matched. $ \{a_1, b_1, a_2, b_2, \ldots, a_n, b_n\} $ should be a permutation of $ \{1, 2, \ldots, 2n\} $ . Let the sorted list of $ \{a_1+b_1, a_2+b_2, \ldots, a_n+b_n\} $ be $ s_1 < s_2 < \ldots < s_n $ . We must have $ s_{i+1}-s_i = 1 $ for $ 1 \le i \le n - 1 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of the test cases follows.

For each test case, a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) is given.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each test case, if it is impossible to make such a pairing, print "No".

Otherwise, print "Yes" followed by $ n $ lines.

At each line, print two integers that are paired.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

If there are multiple solutions, print any.

## 说明/提示

For the third test case, each integer from $ 1 $ to $ 6 $ appears once. The sums of matched pairs are $ 4+2=6 $ , $ 1+6=7 $ , and $ 3+5=8 $ , which are consecutive and distinct.

## 样例 #1

### 输入

```
4
1
2
3
4
```

### 输出

```
Yes
1 2
No
Yes
1 6
3 5
4 2
No
```

