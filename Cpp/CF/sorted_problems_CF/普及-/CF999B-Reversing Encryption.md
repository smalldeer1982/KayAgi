---
title: "Reversing Encryption"
layout: "post"
diff: 普及-
pid: CF999B
tag: ['字符串']
---

# Reversing Encryption

## 题目描述

A string $ s $ of length $ n $ can be encrypted by the following algorithm:

- iterate over all divisors of $ n $ in decreasing order (i.e. from $ n $ to $ 1 $ ),
- for each divisor $ d $ , reverse the substring $ s[1 \dots d] $ (i.e. the substring which starts at position $ 1 $ and ends at position $ d $ ).

For example, the above algorithm applied to the string $ s $ ="codeforces" leads to the following changes: "codeforces" $ \to $ "secrofedoc" $ \to $ "orcesfedoc" $ \to $ "rocesfedoc" $ \to $ "rocesfedoc" (obviously, the last reverse operation doesn't change the string because $ d=1 $ ).

You are given the encrypted string $ t $ . Your task is to decrypt this string, i.e., to find a string $ s $ such that the above algorithm results in string $ t $ . It can be proven that this string $ s $ always exists and is unique.

## 输入格式

The first line of input consists of a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the length of the string $ t $ . The second line of input consists of the string $ t $ . The length of $ t $ is $ n $ , and it consists only of lowercase Latin letters.

## 输出格式

Print a string $ s $ such that the above algorithm results in $ t $ .

## 说明/提示

The first example is described in the problem statement.

## 样例 #1

### 输入

```
10
rocesfedoc

```

### 输出

```
codeforces

```

## 样例 #2

### 输入

```
16
plmaetwoxesisiht

```

### 输出

```
thisisexampletwo

```

## 样例 #3

### 输入

```
1
z

```

### 输出

```
z

```

