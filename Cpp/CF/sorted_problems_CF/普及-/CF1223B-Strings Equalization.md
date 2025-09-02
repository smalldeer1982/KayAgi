---
title: "Strings Equalization"
layout: "post"
diff: 普及-
pid: CF1223B
tag: ['字符串']
---

# Strings Equalization

## 题目描述

You are given two strings of equal length $ s $ and $ t $ consisting of lowercase Latin letters. You may perform any number (possibly, zero) operations on these strings.

During each operation you choose two adjacent characters in any string and assign the value of the first character to the value of the second or vice versa.

For example, if $ s $ is "acbc" you can get the following strings in one operation:

- "aabc" (if you perform $ s_2 = s_1 $ );
- "ccbc" (if you perform $ s_1 = s_2 $ );
- "accc" (if you perform $ s_3 = s_2 $ or $ s_3 = s_4 $ );
- "abbc" (if you perform $ s_2 = s_3 $ );
- "acbb" (if you perform $ s_4 = s_3 $ );

Note that you can also apply this operation to the string $ t $ .

Please determine whether it is possible to transform $ s $ into $ t $ , applying the operation above any number of times.

Note that you have to answer $ q $ independent queries.

## 输入格式

The first line contains one integer $ q $ ( $ 1 \le q \le 100 $ ) — the number of queries. Each query is represented by two consecutive lines.

The first line of each query contains the string $ s $ ( $ 1 \le |s| \le 100 $ ) consisting of lowercase Latin letters.

The second line of each query contains the string $ t $ ( $ 1 \le |t| \leq 100 $ , $ |t| = |s| $ ) consisting of lowercase Latin letters.

## 输出格式

For each query, print "YES" if it is possible to make $ s $ equal to $ t $ , and "NO" otherwise.

You may print every letter in any case you want (so, for example, the strings "yEs", "yes", "Yes", and "YES" will all be recognized as positive answer).

## 说明/提示

In the first query, you can perform two operations $ s_1 = s_2 $ (after it $ s $ turns into "aabb") and $ t_4 = t_3 $ (after it $ t $ turns into "aabb").

In the second query, the strings are equal initially, so the answer is "YES".

In the third query, you can not make strings $ s $ and $ t $ equal. Therefore, the answer is "NO".

## 样例 #1

### 输入

```
3
xabb
aabx
technocup
technocup
a
z

```

### 输出

```
YES
YES
NO

```

