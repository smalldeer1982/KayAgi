---
title: "Cyclical Quest"
layout: "post"
diff: 省选/NOI-
pid: CF235C
tag: []
---

# Cyclical Quest

## 题目描述

Some days ago, WJMZBMR learned how to answer the query "how many times does a string $ x $ occur in a string $ s $ " quickly by preprocessing the string $ s $ . But now he wants to make it harder.

So he wants to ask "how many consecutive substrings of $ s $ are cyclical isomorphic to a given string $ x $ ". You are given string $ s $ and $ n $ strings $ x_{i} $ , for each string $ x_{i} $ find, how many consecutive substrings of $ s $ are cyclical isomorphic to $ x_{i} $ .

Two strings are called cyclical isomorphic if one can rotate one string to get the other one. 'Rotate' here means 'to take some consecutive chars (maybe none) from the beginning of a string and put them back at the end of the string in the same order'. For example, string "abcde" can be rotated to string "deabc". We can take characters "abc" from the beginning and put them at the end of "de".

## 输入格式

The first line contains a non-empty string $ s $ . The length of string $ s $ is not greater than $ 10^{6} $ characters.

The second line contains an integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of queries. Then $ n $ lines follow: the $ i $ -th line contains the string $ x_{i} $ — the string for the $ i $ -th query. The total length of $ x_{i} $ is less than or equal to $ 10^{6} $ characters.

In this problem, strings only consist of lowercase English letters.

## 输出格式

For each query $ x_{i} $ print a single integer that shows how many consecutive substrings of $ s $ are cyclical isomorphic to $ x_{i} $ . Print the answers to the queries in the order they are given in the input.

## 样例 #1

### 输入

```
baabaabaaa
5
a
ba
baa
aabaa
aaba

```

### 输出

```
7
5
7
3
5

```

## 样例 #2

### 输入

```
aabbaa
3
aa
aabb
abba

```

### 输出

```
2
3
3

```

