---
title: "Matryoshkas"
layout: "post"
diff: 普及/提高-
pid: CF1790D
tag: []
---

# Matryoshkas

## 题目描述

Matryoshka is a wooden toy in the form of a painted doll, inside which you can put a similar doll of a smaller size.

A set of nesting dolls contains one or more nesting dolls, their sizes are consecutive positive integers. Thus, a set of nesting dolls is described by two numbers: $ s $ — the size of a smallest nesting doll in a set and $ m $ — the number of dolls in a set. In other words, the set contains sizes of $ s, s + 1, \dots, s + m - 1 $ for some integer $ s $ and $ m $ ( $ s,m > 0 $ ).

You had one or more sets of nesting dolls. Recently, you found that someone mixed all your sets in one and recorded a sequence of doll sizes — integers $ a_1, a_2, \dots, a_n $ .

You do not remember how many sets you had, so you want to find the minimum number of sets that you could initially have.

For example, if a given sequence is $ a=[2, 2, 3, 4, 3, 1] $ . Initially, there could be $ 2 $ sets:

- the first set consisting of $ 4 $ nesting dolls with sizes $ [1, 2, 3, 4] $ ;
- a second set consisting of $ 2 $ nesting dolls with sizes $ [2, 3] $ .

According to a given sequence of sizes of nesting dolls $ a_1, a_2, \dots, a_n $ , determine the minimum number of nesting dolls that can make this sequence.

Each set is completely used, so all its nesting dolls are used. Each element of a given sequence must correspond to exactly one doll from some set.

## 输入格式

The first line of input data contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the total number of matryoshkas that were in all sets.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the sizes of the matryoshkas.

It is guaranteed that the sum of values of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, print one integer $ k $ — the minimum possible number of matryoshkas sets.

## 说明/提示

The first test case is described in the problem statement.

In the second test case, all matryoshkas could be part of the same set with minimum size $ s=7 $ .

In the third test case, each matryoshka represents a separate set.

## 样例 #1

### 输入

```
10
6
2 2 3 4 3 1
5
11 8 7 10 9
6
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
8
1 1 4 4 2 3 2 3
6
1 2 3 2 3 4
7
10 11 11 12 12 13 13
7
8 8 9 9 10 10 11
8
4 14 5 15 6 16 7 17
8
5 15 6 14 8 12 9 11
5
4 2 2 3 4
```

### 输出

```
2
1
6
2
2
2
2
2
4
3
```

