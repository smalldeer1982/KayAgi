---
title: "Bash and a Tough Math Puzzle"
layout: "post"
diff: 普及+/提高
pid: CF914D
tag: ['线段树']
---

# Bash and a Tough Math Puzzle

## 题目描述

Bash likes playing with arrays. He has an array $ a_{1},a_{2},...\ a_{n} $ of $ n $ integers. He likes to guess the greatest common divisor (gcd) of different segments of the array. Of course, sometimes the guess is not correct. However, Bash will be satisfied if his guess is almost correct.

Suppose he guesses that the gcd of the elements in the range $ [l,r] $ of $ a $ is $ x $ . He considers the guess to be almost correct if he can change at most one element in the segment such that the gcd of the segment is $ x $ after making the change. Note that when he guesses, he doesn't actually change the array — he just wonders if the gcd of the segment can be made $ x $ . Apart from this, he also sometimes makes changes to the array itself.

Since he can't figure it out himself, Bash wants you to tell him which of his guesses are almost correct. Formally, you have to process $ q $ queries of one of the following forms:

- $ 1lrx $ — Bash guesses that the gcd of the range $ [l,r] $ is $ x $ . Report if this guess is almost correct.
- $ 2iy $ — Bash sets $ a_{i} $ to $ y $ .

Note: The array is $ 1 $ -indexed.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the size of the array.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the elements of the array.

The third line contains an integer $ q $ ( $ 1<=q<=4·10^{5} $ ) — the number of queries.

The next $ q $ lines describe the queries and may have one of the following forms:

- $ 1lrx $ ( $ 1<=l<=r<=n,1<=x<=10^{9} $ ).
- $ 2iy $ $ (1<=i<=n,1<=y<=10^{9}) $ .

Guaranteed, that there is at least one query of first type.

## 输出格式

For each query of first type, output "YES" (without quotes) if Bash's guess is almost correct and "NO" (without quotes) otherwise.

## 说明/提示

In the first sample, the array initially is $ {2,6,3} $ .

For query $ 1 $ , the first two numbers already have their gcd as $ 2 $ .

For query $ 2 $ , we can achieve a gcd of $ 3 $ by changing the first element of the array to $ 3 $ . Note that the changes made during queries of type $ 1 $ are temporary and do not get reflected in the array.

After query $ 3 $ , the array is now $ {9,6,3} $ .

 For query $ 4 $ , no matter which element you change, you cannot get the gcd of the range to be $ 2 $ .

## 样例 #1

### 输入

```
3
2 6 3
4
1 1 2 2
1 1 3 3
2 1 9
1 1 3 2

```

### 输出

```
YES
YES
NO

```

## 样例 #2

### 输入

```
5
1 2 3 4 5
6
1 1 4 2
2 3 6
1 1 4 2
1 1 5 2
2 5 10
1 1 5 2

```

### 输出

```
NO
YES
NO
YES

```

