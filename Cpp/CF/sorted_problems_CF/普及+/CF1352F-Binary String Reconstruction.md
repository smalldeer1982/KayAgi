---
title: "Binary String Reconstruction"
layout: "post"
diff: 普及+/提高
pid: CF1352F
tag: []
---

# Binary String Reconstruction

## 题目描述

For some binary string $ s $ (i.e. each character $ s_i $ is either '0' or '1'), all pairs of consecutive (adjacent) characters were written. In other words, all substrings of length $ 2 $ were written. For each pair (substring of length $ 2 $ ), the number of '1' (ones) in it was calculated.

You are given three numbers:

- $ n_0 $ — the number of such pairs of consecutive characters (substrings) where the number of ones equals $ 0 $ ;
- $ n_1 $ — the number of such pairs of consecutive characters (substrings) where the number of ones equals $ 1 $ ;
- $ n_2 $ — the number of such pairs of consecutive characters (substrings) where the number of ones equals $ 2 $ .

For example, for the string $ s= $ "1110011110", the following substrings would be written: "11", "11", "10", "00", "01", "11", "11", "11", "10". Thus, $ n_0=1 $ , $ n_1=3 $ , $ n_2=5 $ .

Your task is to restore any suitable binary string $ s $ from the given values $ n_0, n_1, n_2 $ . It is guaranteed that at least one of the numbers $ n_0, n_1, n_2 $ is greater than $ 0 $ . Also, it is guaranteed that a solution exists.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le       1000 $ ) — the number of test cases in the input. Then test cases follow.

Each test case consists of one line which contains three integers $ n_0, n_1, n_2 $ ( $ 0 \le n_0, n_1, n_2 \le 100 $ ; $ n_0 +       n_1 + n_2 > 0 $ ). It is guaranteed that the answer for given $ n_0, n_1, n_2 $ exists.

## 输出格式

Print $ t $ lines. Each of the lines should contain a binary string corresponding to a test case. If there are several possible solutions, print any of them.

## 样例 #1

### 输入

```
7
1 3 5
1 1 1
3 9 3
0 1 0
3 1 2
0 0 3
2 0 0
```

### 输出

```
1110011110
0011
0110001100101011
10
0000111
1111
000
```

