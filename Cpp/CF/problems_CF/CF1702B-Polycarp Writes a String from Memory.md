---
title: "Polycarp Writes a String from Memory"
layout: "post"
diff: 普及-
pid: CF1702B
tag: []
---

# Polycarp Writes a String from Memory

## 题目描述

Polycarp has a poor memory. Each day he can remember no more than $ 3 $ of different letters.

Polycarp wants to write a non-empty string of $ s $ consisting of lowercase Latin letters, taking minimum number of days. In how many days will he be able to do it?

Polycarp initially has an empty string and can only add characters to the end of that string.

For example, if Polycarp wants to write the string lollipops, he will do it in $ 2 $ days:

- on the first day Polycarp will memorize the letters l, o, i and write lolli;
- On the second day Polycarp will remember the letters p, o, s, add pops to the resulting line and get the line lollipops.

If Polycarp wants to write the string stringology, he will do it in $ 4 $ days:

- in the first day will be written part str;
- on day two will be written part ing;
- on the third day, part of olog will be written;
- on the fourth day, part of y will be written.

For a given string $ s $ , print the minimum number of days it will take Polycarp to write it.

## 输入格式

The first line of input data contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of a non-empty string $ s $ consisting of lowercase Latin letters (the length of the string $ s $ does not exceed $ 2 \cdot 10^5 $ ) — the string Polycarp wants to construct.

It is guaranteed that the sum of string lengths $ s $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single number — minimum number of days it will take Polycarp to write the string $ s $ from memory.

## 样例 #1

### 输入

```
6
lollipops
stringology
abracadabra
codeforces
test
f
```

### 输出

```
2
4
3
4
1
1
```

