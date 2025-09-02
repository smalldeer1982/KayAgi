---
title: "378QAQ and Core"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1975H
tag: ['贪心']
---

# 378QAQ and Core

## 题目描述

378QAQ has a string $ s $ of length $ n $ . Define the core of a string as the substring $ ^\dagger $ with maximum lexicographic $ ^\ddagger $ order.

For example, the core of " $ \mathtt{bazoka} $ " is " $ \mathtt{zoka} $ ", and the core of " $ \mathtt{aaa} $ " is " $ \mathtt{aaa} $ ".

378QAQ wants to rearrange the string $ s $ so that the core is lexicographically minimum. Find the lexicographically minimum possible core over all rearrangements of $ s $ .

 $ ^\dagger $ A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, " $ \mathtt{defor} $ ", " $ \mathtt{code} $ " and " $ \mathtt{o} $ " are all substrings of " $ \mathtt{codeforces} $ " while " $ \mathtt{codes} $ " and " $ \mathtt{aaa} $ " are not.

 $ ^\ddagger $ A string $ p $ is lexicographically smaller than a string $ q $ if and only if one of the following holds:

- $ p $ is a prefix of $ q $ , but $ p \ne q $ ; or
- in the first position where $ p $ and $ q $ differ, the string $ p $ has a smaller element than the corresponding element in $ q $ (when compared by their ASCII code).

For example, " $ \mathtt{code} $ " and " $ \mathtt{coda} $ " are both lexicographically smaller than " $ \mathtt{codeforces} $ " while " $ \mathtt{codeforceston} $ " and " $ \mathtt{z} $ " are not.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 10^5 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\leq n\leq 10^6 $ ) — the length of string $ s $ .

The next line of each test case contains the string $ s $ of length $ n $ . The string $ s $ consists of lowercase English letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output the lexicographically minimum possible core over all rearrangements of $ s $ .

## 说明/提示

In the first test case, all possible rearrangements and their corresponding cores are as follows:

- " $ \mathtt{qaq} $ ", its core is " $ \mathtt{qaq} $ ".
- " $ \mathtt{aqq} $ ", its core is " $ \mathtt{qq} $ ".
- " $ \mathtt{qqa} $ ", its core is " $ \mathtt{qqa} $ ".

So the core with the minimum lexicographic order in all rearrangement plans is " $ \mathtt{qaq} $ ".

## 样例 #1

### 输入

```
6
3
qaq
4
cccc
6
bazoka
6
zazzzz
7
ababbbb
7
ccbabcc
```

### 输出

```
qaq
cccc
z
zzz
bbababb
cbcacbc
```

