---
title: "COCONUTS - Coconuts"
layout: "post"
diff: 提高+/省选-
pid: SP1693
tag: []
---

# COCONUTS - Coconuts

## 题目描述

A group of n castle guards are voting to determine whether African swallows can carry coconuts. While each guard has his own personal opinion on the matter, a guard will often vote contrary to his beliefs in order to avoid disagreeing with the votes of his friends.  
 You are given a list of guards who either do or do not believe in the coconut-carrying capacity of African swallows, and a list of all pairs of guards who are friends. Your task is to determine how each guard must vote in order to minimize the sum of the total number of disagreements between friends and the total number of guards who must vote against their own beliefs.

## 输入格式

The input to this problem will contain multiple test cases. Each test case begins with a single line containing an integer n (where 2 <= n <= 300), the number of guards, and an integer m (where 1 <= m <= n(n-1)/2), the number of pairs of guards who are friends. The second line of the test case contains n integers, where the ith integer is 1 if the ith guard believes in the ability of African swallows to carry coconuts, and 0 otherwise. Finally, the next m lines of the test case each contain two distinct integers i and j (where 1 <= i, j <= n), indicating that guards i and j are friends. Guards within each pair of friends may be listed in any order, but no pair of guards will be repeated. The input is terminated by an invalid test case with n = m = 0, which should not be processed.

## 输出格式

For each input test case, print a single line containing the minimum possible sum of the total number of disagreements between all friends plus the total number of guards who must vote against their own beliefs.

## 样例 #1

### 输入

```
3 3
1 0 0
1 2
1 3
3 2
6 6
1 1 1 0 0 0
1 2
2 3
4 2
3 5
4 5
5 6
0 0
```

### 输出

```
1
2
```

