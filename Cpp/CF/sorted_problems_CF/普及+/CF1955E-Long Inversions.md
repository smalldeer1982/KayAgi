---
title: "Long Inversions"
layout: "post"
diff: 普及+/提高
pid: CF1955E
tag: ['线段树']
---

# Long Inversions

## 题目描述

给定一个长度为$ n $的01字符串$ s $。01字符串是指只包含字符'1' 和'0'的字符串

可以选定一个整数$ k $ ( $ 1 \le k \le n $ )，将字符串中的连续k个字符进行替换，将0替换成1，1替换成0。

当 $ n=5 $ , $ s=00100 $时 , 你可以指定$ k=3 $ ，做如下操作：

- 翻转1-3的子串：$ s=\color{blue}{110}00 $ ;
- 反转3-5的子串：$ s=11\color{blue}{111} $ ;

经过不限次操作后，寻找能将01字符串中的所有字符转换成1的最大$ k $值。

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 5000 $ ) — the length of the string $ s $ .

The second line of each test case contains a string $ s $ of length $ n $ , consisting of the characters '1' and '0'.

It is guaranteed that the sum of the values $ n^2 $ over all test cases in the test does not exceed $ 25 \cdot 10^6 $ .

## 输出格式

For each test case, output the maximum integer $ k $ ( $ 1 \le k \le n $ ) for which it is possible to obtain a string $ s $ consisting only of the characters '1' using the described operations.

## 样例 #1

### 输入

```
5
5
00100
5
01000
7
1011101
3
000
2
10
```

### 输出

```
3
2
4
3
1
```

