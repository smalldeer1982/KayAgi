---
title: "Paranoid String"
layout: "post"
diff: 普及-
pid: CF1694B
tag: []
---

# Paranoid String

## 题目描述

Let's call a binary string $ T $ of length $ m $ indexed from $ 1 $ to $ m $ paranoid if we can obtain a string of length $ 1 $ by performing the following two kinds of operations $ m-1 $ times in any order :

- Select any substring of $ T $ that is equal to 01, and then replace it with 1.
- Select any substring of $ T $ that is equal to 10, and then replace it with 0.For example, if $ T =  $ 001, we can select the substring $ [T_2T_3] $ and perform the first operation. So we obtain $ T =  $ 01.

You are given a binary string $ S $ of length $ n $ indexed from $ 1 $ to $ n $ . Find the number of pairs of integers $ (l, r) $ $ 1 \le l \le r \le n $ such that $ S[l \ldots r] $ (the substring of $ S $ from $ l $ to $ r $ ) is a paranoid string.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the size of $ S $ .

The second line of each test case contains a binary string $ S $ of $ n $ characters $ S_1S_2 \ldots S_n $ . ( $ S_i =  $ 0 or $ S_i =  $ 1 for each $ 1 \le i \le n $ )

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the number of pairs of integers $ (l, r) $ $ 1 \le l \le r \le n $ such that $ S[l \ldots r] $ (the substring of $ S $ from $ l $ to $ r $ ) is a paranoid string.

## 说明/提示

In the first sample, $ S $ already has length $ 1 $ and doesn't need any operations.

In the second sample, all substrings of $ S $ are paranoid. For the entire string, it's enough to perform the first operation.

In the third sample, all substrings of $ S $ are paranoid except $ [S_2S_3] $ , because we can't perform any operations on it, and $ [S_1S_2S_3] $ (the entire string).

## 样例 #1

### 输入

```
5
1
1
2
01
3
100
4
1001
5
11111
```

### 输出

```
1
3
4
8
5
```

