---
title: "Qingshan Loves Strings"
layout: "post"
diff: 普及-
pid: CF1890B
tag: []
---

# Qingshan Loves Strings

## 题目描述

Qingshan has a string $ s $ , while Daniel has a string $ t $ . Both strings only contain $ \texttt{0} $ and $ \texttt{1} $ .

A string $ a $ of length $ k $ is good if and only if

- $ a_i \ne a_{i+1} $ for all $ i=1,2,\ldots,k-1 $ .

For example, $ \texttt{1} $ , $ \texttt{101} $ , $ \texttt{0101} $ are good, while $ \texttt{11} $ , $ \texttt{1001} $ , $ \texttt{001100} $ are not good.

Qingshan wants to make $ s $ good. To do this, she can do the following operation any number of times (possibly, zero):

- insert $ t $ to any position of $ s $ (getting a new $ s $ ).

Please tell Qingshan if it is possible to make $ s $ good.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ T $ ( $ 1\le T\le 2000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n,m \le 50 $ ) — the length of the strings $ s $ and $ t $ , respectively.

The second line of each test case contains a string $ s $ of length $ n $ .

The third line of each test case contains a string $ t $ of length $ m $ .

It is guaranteed that $ s $ and $ t $ only contain $ \texttt{0} $ and $ \texttt{1} $ .

## 输出格式

For each test case, print "YES" (without quotes), if it is possible to make $ s $ good, and "NO" (without quotes) otherwise.

You can print letters in any case (upper or lower).

## 说明/提示

In the first test case, $ s $ is good initially, so you can get a good $ s $ by doing zero operations.

In the second test case, you can do the following two operations (the inserted string $ t $ is underlined):

1. $ \texttt{1}\underline{\texttt{010}}\texttt{11} $
2. $ \texttt{10101}\underline{\texttt{010}}\texttt{1} $

and get $ s = \texttt{101010101} $ , which is good.

In the third test case, there is no way to make $ s $ good after any number of operations.

## 样例 #1

### 输入

```
5
1 1
1
0
3 3
111
010
3 2
111
00
6 7
101100
1010101
10 2
1001001000
10
```

### 输出

```
Yes
Yes
No
No
No
```

