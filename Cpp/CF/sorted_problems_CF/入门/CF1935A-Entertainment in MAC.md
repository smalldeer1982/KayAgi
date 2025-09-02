---
title: "Entertainment in MAC"
layout: "post"
diff: 入门
pid: CF1935A
tag: []
---

# Entertainment in MAC

## 题目描述

Congratulations, you have been accepted to the Master's Assistance Center! However, you were extremely bored in class and got tired of doing nothing, so you came up with a game for yourself.

You are given a string $ s $ and an even integer $ n $ . There are two types of operations that you can apply to it:

1. Add the reversed string $ s $ to the end of the string $ s $ (for example, if $ s =  $ cpm, then after applying the operation $ s =  $ cpmmpc).
2. Reverse the current string $ s $ (for example, if $ s =  $ cpm, then after applying the operation $ s =  $ mpc).

It is required to determine the lexicographically smallest $ ^{\dagger} $ string that can be obtained after applying exactly $ n $ operations. Note that you can apply operations of different types in any order, but you must apply exactly $ n $ operations in total.

 $ ^{\dagger} $ A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single even integer $ n $ ( $ 2 \leq n \leq 10^9 $ ) — the number of operations applied to the string $ s $ .

The second line of each test case contains a single string $ s $ ( $ 1 \leq |s| \leq 100 $ ), consisting of lowercase English letters, — the string to which the operations are applied.

## 输出格式

For each test case, output a single line — the lexicographically smallest string that can be obtained after applying exactly $ n $ operations.

## 说明/提示

In the first test case, you can apply the operation of the second type (i.e., reverse the string $ s $ ) $ 4 $ times. Then the string $ s $ will remain equal to cpm.

In the second test case, you can do the following:

- Apply the operation of the second type, after which $ s $ will become equal to birg.
- Apply operation of the first type (i.e., add the reversed string $ s $ to the end of the string $ s $ ), after which $ s $ will become equal to birggrib.

## 样例 #1

### 输入

```
5
4
cpm
2
grib
10
kupitimilablodarbuz
1000000000
capybara
6
abacaba
```

### 输出

```
cpm
birggrib
kupitimilablodarbuz
arabypaccapybara
abacaba
```

