---
title: "The Sum of Good Numbers"
layout: "post"
diff: 省选/NOI-
pid: CF1598G
tag: []
---

# The Sum of Good Numbers

## 题目描述

Let's call a positive integer good if there is no digit 0 in its decimal representation.

For an array of a good numbers $ a $ , one found out that the sum of some two neighboring elements is equal to $ x $ (i.e. $ x = a_i + a_{i + 1} $ for some $ i $ ). $ x $ had turned out to be a good number as well.

Then the elements of the array $ a $ were written out one after another without separators into one string $ s $ . For example, if $ a = [12, 5, 6, 133] $ , then $ s = 1256133 $ .

You are given a string $ s $ and a number $ x $ . Your task is to determine the positions in the string that correspond to the adjacent elements of the array that have sum $ x $ . If there are several possible answers, you can print any of them.

## 输入格式

The first line contains the string $ s $ ( $ 2 \le |s| \le 5 \cdot 10^5 $ ).

The second line contains an integer $ x $ ( $ 2 \le x < 10^{200000} $ ).

An additional constraint on the input: the answer always exists, i.e you can always select two adjacent substrings of the string $ s $ so that if you convert these substrings to integers, their sum is equal to $ x $ .

## 输出格式

In the first line, print two integers $ l_1 $ , $ r_1 $ , meaning that the first term of the sum ( $ a_i $ ) is in the string $ s $ from position $ l_1 $ to position $ r_1 $ .

In the second line, print two integers $ l_2 $ , $ r_2 $ , meaning that the second term of the sum ( $ a_{i + 1} $ ) is in the string $ s $ from position $ l_2 $ to position $ r_2 $ .

## 说明/提示

In the first example $ s[1;2] = 12 $ and $ s[3;3] = 5 $ , $ 12+5=17 $ .

In the second example $ s[2;3] = 54 $ and $ s[4;6] = 471 $ , $ 54+471=525 $ .

In the third example $ s[1;1] = 2 $ and $ s[2;2] = 3 $ , $ 2+3=5 $ .

In the fourth example $ s[2;7] = 218633 $ and $ s[8;13] = 757639 $ , $ 218633+757639=976272 $ .

## 样例 #1

### 输入

```
1256133
17
```

### 输出

```
1 2
3 3
```

## 样例 #2

### 输入

```
9544715561
525
```

### 输出

```
2 3
4 6
```

## 样例 #3

### 输入

```
239923
5
```

### 输出

```
1 1
2 2
```

## 样例 #4

### 输入

```
1218633757639
976272
```

### 输出

```
2 7
8 13
```

