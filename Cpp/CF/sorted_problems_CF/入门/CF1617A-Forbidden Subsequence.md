---
title: "Forbidden Subsequence"
layout: "post"
diff: 入门
pid: CF1617A
tag: ['字符串', '贪心']
---

# Forbidden Subsequence

## 题目描述

You are given strings $ S $ and $ T $ , consisting of lowercase English letters. It is guaranteed that $ T $ is a permutation of the string abc.

Find string $ S' $ , the lexicographically smallest permutation of $ S $ such that $ T $ is not a subsequence of $ S' $ .

String $ a $ is a permutation of string $ b $ if the number of occurrences of each distinct character is the same in both strings.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements.

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains a string $ S $ ( $ 1 \le |S| \le 100 $ ), consisting of lowercase English letters.

The second line of each test case contains a string $ T $ that is a permutation of the string abc. (Hence, $ |T| = 3 $ ).

Note that there is no limit on the sum of $ |S| $ across all test cases.

## 输出格式

For each test case, output a single string $ S' $ , the lexicographically smallest permutation of $ S $ such that $ T $ is not a subsequence of $ S' $ .

## 说明/提示

In the first test case, both aaaabbc and aaaabcb are lexicographically smaller than aaaacbb, but they contain abc as a subsequence.

In the second test case, abccc is the smallest permutation of cccba and does not contain acb as a subsequence.

In the third test case, bcdis is the smallest permutation of dbsic and does not contain bac as a subsequence.

## 样例 #1

### 输入

```
7
abacaba
abc
cccba
acb
dbsic
bac
abracadabra
abc
dddddddddddd
cba
bbc
abc
ac
abc
```

### 输出

```
aaaacbb
abccc
bcdis
aaaaacbbdrr
dddddddddddd
bbc
ac
```

