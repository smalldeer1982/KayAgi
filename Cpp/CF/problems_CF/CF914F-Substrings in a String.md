---
title: "Substrings in a String"
layout: "post"
diff: 省选/NOI-
pid: CF914F
tag: ['进制', 'KMP 算法']
---

# Substrings in a String

## 题目描述

Given a string $ s $ , process $ q $ queries, each having one of the following forms:

- $ 1ic $ — Change the $ i $ -th character in the string to $ c $ .
- $ 2lry $ — Consider the substring of $ s $ starting at position $ l $ and ending at position $ r $ . Output the number of times $ y $ occurs as a substring in it.

## 输入格式

The first line of the input contains the string $ s $ ( $ 1<=|s|<=10^{5} $ ) of lowercase English letters.

The second line contains an integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of queries to process.

The next $ q $ lines describe the queries and may have one of the following forms:

- $ 1ic $ ( $ 1<=i<=|s| $ )
- $ 2lry $ ( $ 1<=l<=r<=|s| $ )

 $ c $ is a lowercase English letter and $ y $ is a non-empty string consisting of only lowercase English letters.

The sum of $ |y| $ over all queries of second type is at most $ 10^{5} $ .

It is guaranteed that there is at least one query of second type.

All strings are $ 1 $ -indexed.

 $ |s| $ is the length of the string $ s $ .

## 输出格式

For each query of type $ 2 $ , output the required answer in a separate line.

## 说明/提示

Consider the first sample case. Initially, the string aba occurs $ 3 $ times in the range $ [1,7] $ . Note that two occurrences may overlap.

After the update, the string becomes ababcbaba and now aba occurs only once in the range $ [1,7] $ .

## 样例 #1

### 输入

```
ababababa
3
2 1 7 aba
1 5 c
2 1 7 aba

```

### 输出

```
3
1

```

## 样例 #2

### 输入

```
abcdcbc
5
2 1 7 bc
1 4 b
2 4 7 bc
1 2 a
2 1 4 aa

```

### 输出

```
2
2
1

```

