---
title: "Alphabet Permutations"
layout: "post"
diff: 提高+/省选-
pid: CF610E
tag: []
---

# Alphabet Permutations

## 题目描述

You are given a string $ s $ of length $ n $ , consisting of first $ k $ lowercase English letters.

We define a  $ c $ -repeat of some string $ q $ as a string, consisting of $ c $ copies of the string $ q $ . For example, string "acbacbacbacb" is a $ 4 $ -repeat of the string "acb".

Let's say that string $ a $ contains string $ b $ as a subsequence, if string $ b $ can be obtained from $ a $ by erasing some symbols.

Let $ p $ be a string that represents some permutation of the first $ k $ lowercase English letters. We define function $ d(p) $ as the smallest integer such that a $ d(p) $ -repeat of the string $ p $ contains string $ s $ as a subsequence.

There are $ m $ operations of one of two types that can be applied to string $ s $ :

1. Replace all characters at positions from $ l_{i} $ to $ r_{i} $ by a character $ c_{i} $ .
2. For the given $ p $ , that is a permutation of first $ k $ lowercase English letters, find the value of function $ d(p) $ .

All operations are performed sequentially, in the order they appear in the input. Your task is to determine the values of function $ d(p) $ for all operations of the second type.

## 输入格式

The first line contains three positive integers $ n $ , $ m $ and $ k $ ( $ 1<=n<=200000,1<=m<=20000,1<=k<=10 $ ) — the length of the string $ s $ , the number of operations and the size of the alphabet respectively. The second line contains the string $ s $ itself.

Each of the following lines $ m $ contains a description of some operation:

1. Operation of the first type starts with $ 1 $ followed by a triple $ l_{i} $ , $ r_{i} $ and $ c_{i} $ , that denotes replacement of all characters at positions from $ l_{i} $ to $ r_{i} $ by character $ c_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ , $ c_{i} $ is one of the first $ k $ lowercase English letters).
2. Operation of the second type starts with $ 2 $ followed by a permutation of the first $ k $ lowercase English letters.

## 输出格式

For each query of the second type the value of function $ d(p) $ .

## 说明/提示

After the first operation the string $ s $ will be abbbbba.

In the second operation the answer is $ 6 $ -repeat of abc: ABcaBcaBcaBcaBcAbc.

After the third operation the string $ s $ will be abbcbba.

In the fourth operation the answer is $ 5 $ -repeat of cba: cbAcBacBaCBacBA.

Uppercase letters means the occurrences of symbols from the string $ s $ .

## 样例 #1

### 输入

```
7 4 3
abacaba
1 3 5 b
2 abc
1 4 4 c
2 cba

```

### 输出

```
6
5

```

