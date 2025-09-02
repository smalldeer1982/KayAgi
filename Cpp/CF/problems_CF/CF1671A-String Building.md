---
title: "String Building"
layout: "post"
diff: 入门
pid: CF1671A
tag: []
---

# String Building

## 题目描述

You are given a string $ s $ . You have to determine whether it is possible to build the string $ s $ out of strings aa, aaa, bb and/or bbb by concatenating them. You can use the strings aa, aaa, bb and/or bbb any number of times and in any order.

For example:

- aaaabbb can be built as aa $ + $ aa $ + $ bbb;
- bbaaaaabbb can be built as bb $ + $ aaa $ + $ aa $ + $ bbb;
- aaaaaa can be built as aa $ + $ aa $ + $ aa;
- abab cannot be built from aa, aaa, bb and/or bbb.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of one line containing the string $ s $ ( $ 1 \le |s| \le 50 $ ), consisting of characters a and/or b.

## 输出格式

For each test case, print YES if it is possible to build the string $ s $ . Otherwise, print NO.

You may print each letter in any case (for example, YES, yes, Yes will all be recognized as positive answer, NO, no and nO will all be recognized as negative answer).

## 说明/提示

The first four test cases of the example are described in the statement.

## 样例 #1

### 输入

```
8
aaaabbb
bbaaaaabbb
aaaaaa
abab
a
b
aaaab
bbaaa
```

### 输出

```
YES
YES
YES
NO
NO
NO
NO
YES
```

