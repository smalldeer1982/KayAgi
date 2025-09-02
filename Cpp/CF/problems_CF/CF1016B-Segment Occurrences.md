---
title: "Segment Occurrences"
layout: "post"
diff: 普及/提高-
pid: CF1016B
tag: ['前缀和']
---

# Segment Occurrences

## 题目描述

You are given two strings $ s $ and $ t $ , both consisting only of lowercase Latin letters.

The substring $ s[l..r] $ is the string which is obtained by taking characters $ s_l, s_{l + 1}, \dots, s_r $ without changing the order.

Each of the occurrences of string $ a $ in a string $ b $ is a position $ i $ ( $ 1 \le i \le |b| - |a| + 1 $ ) such that $ b[i..i + |a| - 1] = a $ ( $ |a| $ is the length of string $ a $ ).

You are asked $ q $ queries: for the $ i $ -th query you are required to calculate the number of occurrences of string $ t $ in a substring $ s[l_i..r_i] $ .

## 输入格式

The first line contains three integer numbers $ n $ , $ m $ and $ q $ ( $ 1 \le n, m \le 10^3 $ , $ 1 \le q \le 10^5 $ ) — the length of string $ s $ , the length of string $ t $ and the number of queries, respectively.

The second line is a string $ s $ ( $ |s| = n $ ), consisting only of lowercase Latin letters.

The third line is a string $ t $ ( $ |t| = m $ ), consisting only of lowercase Latin letters.

Each of the next $ q $ lines contains two integer numbers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — the arguments for the $ i $ -th query.

## 输出格式

Print $ q $ lines — the $ i $ -th line should contain the answer to the $ i $ -th query, that is the number of occurrences of string $ t $ in a substring $ s[l_i..r_i] $ .

## 说明/提示

In the first example the queries are substrings: "cod", "deforces", "fo" and "for", respectively.

## 样例 #1

### 输入

```
10 3 4
codeforces
for
1 3
3 10
5 6
5 7

```

### 输出

```
0
1
0
1

```

## 样例 #2

### 输入

```
15 2 3
abacabadabacaba
ba
1 15
3 4
2 14

```

### 输出

```
4
0
3

```

## 样例 #3

### 输入

```
3 5 2
aaa
baaab
1 3
1 1

```

### 输出

```
0
0

```

