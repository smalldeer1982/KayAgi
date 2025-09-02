---
title: "Prefix and Suffix Array"
layout: "post"
diff: 入门
pid: CF1794A
tag: []
---

# Prefix and Suffix Array

## 题目描述

Marcos loves strings a lot, so he has a favorite string $ s $ consisting of lowercase English letters. For this string, he wrote down all its non-empty prefixes and suffixes (except for $ s $ ) on a piece of paper in arbitrary order. You see all these strings and wonder if Marcos' favorite string is a palindrome or not. So, your task is to decide whether $ s $ is a palindrome by just looking at the piece of paper.

A string $ a $ is a prefix of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the end.

A string $ a $ is a suffix of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning.

A palindrome is a string that reads the same backward as forward, for example, strings "gg", "ioi", "abba", "icpci" are palindromes, but strings "codeforces", "abcd", "alt" are not.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 120 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2\le n \le 20 $ ) — the length of the string $ s $ .

The second line of each test case contains $ 2n-2 $ strings $ a_1, a_2, \cdots, a_{2n-2} $ — all non-empty prefixes and suffixes of $ s $ , not including itself, in arbitrary order.

It is guaranteed that these strings are all the non-empty prefixes and suffixes of some string consisting of lowercase English letters.

## 输出格式

For each test case, output "YES" if $ s $ is a palindrome, and "NO" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, $ s $ is "abcd". Its prefixes are "a", "ab" and "abc", and its suffixes are "d", "cd" and "bcd". As the string "abcd" is not a palindrome, the answer is NO.

In the second test case, $ s $ is "ioi". Its prefixes are "i" and "io", and its suffixes are "i" and "oi". As the string "ioi" is a palindrome, the answer is YES.

In the third test case, $ s $ is "gg" which is a palindrome.

In the fourth test case, $ s $ is "alt" which is not a palindrome.

## 样例 #1

### 输入

```
5
4
bcd cd a d abc ab
3
i io i oi
2
g g
3
t al lt a
4
bba a ab a abb ba
```

### 输出

```
NO
YES
YES
NO
YES
```

