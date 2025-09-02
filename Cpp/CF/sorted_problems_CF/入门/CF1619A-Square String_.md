---
title: "Square String?"
layout: "post"
diff: 入门
pid: CF1619A
tag: []
---

# Square String?

## 题目描述

A string is called square if it is some string written twice in a row. For example, the strings "aa", "abcabc", "abab" and "baabaa" are square. But the strings "aaa", "abaaab" and "abcdabc" are not square.

For a given string $ s $ determine if it is square.

## 输入格式

The first line of input data contains an integer $ t $ ( $ 1 \le t \le 100 $ ) —the number of test cases.

This is followed by $ t $ lines, each containing a description of one test case. The given strings consist only of lowercase Latin letters and have lengths between $ 1 $ and $ 100 $ inclusive.

## 输出格式

For each test case, output on a separate line:

- YES if the string in the corresponding test case is square,
- NO otherwise.

You can output YES and NO in any case (for example, strings yEs, yes, Yes and YES will be recognized as a positive response).

## 样例 #1

### 输入

```
10
a
aa
aaa
aaaa
abab
abcabc
abacaba
xxyy
xyyx
xyxy
```

### 输出

```
NO
YES
NO
YES
YES
YES
NO
NO
NO
YES
```

