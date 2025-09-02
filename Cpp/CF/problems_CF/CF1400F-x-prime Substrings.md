---
title: "x-prime Substrings"
layout: "post"
diff: 省选/NOI-
pid: CF1400F
tag: []
---

# x-prime Substrings

## 题目描述

You are given an integer value $ x $ and a string $ s $ consisting of digits from $ 1 $ to $ 9 $ inclusive.

A substring of a string is a contiguous subsequence of that string.

Let $ f(l, r) $ be the sum of digits of a substring $ s[l..r] $ .

Let's call substring $ s[l_1..r_1] $  $ x $ -prime if

- $ f(l_1, r_1) = x $ ;
- there are no values $ l_2, r_2 $ such that 
  - $ l_1             \le l_2 \le r_2 \le r_1 $ ;
  - $ f(l_2, r_2) \neq x $ ;
  - $ x $ is divisible by $ f(l_2, r_2) $ .

You are allowed to erase some characters from the string. If you erase a character, the two resulting parts of the string are concatenated without changing their order.

What is the minimum number of characters you should erase from the string so that there are no  $ x $ -prime substrings in it? If there are no  $ x $ -prime substrings in the given string $ s $ , then print $ 0 $ .

## 输入格式

The first line contains a string $ s $ ( $ 1 \le |s| \le       1000 $ ). $ s $ contains only digits from $ 1 $ to $ 9 $ inclusive.

The second line contains an integer $ x $ ( $ 1 \le x \le 20 $ ).

## 输出格式

Print a single integer — the minimum number of characters you should erase from the string so that there are no  $ x $ -prime substrings in it. If there are no  $ x $ -prime substrings in the given string $ s $ , then print $ 0 $ .

## 说明/提示

In the first example there are two $ 8 $ -prime substrings "8" and "53". You can erase these characters to get rid of both: "116285317". The resulting string "1162317" contains no $ 8 $ -prime substrings. Removing these characters is also a valid answer: "116285317".

In the second example you just have to erase both ones.

In the third example there are no $ 13 $ -prime substrings. There are no substrings with the sum of digits equal to $ 13 $ at all.

In the fourth example you can have neither "34", nor "43" in a string. Thus, you have to erase either all threes or all fours. There are $ 5 $ of each of them, so it doesn't matter which.

## 样例 #1

### 输入

```
116285317
8
```

### 输出

```
2
```

## 样例 #2

### 输入

```
314159265359
1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
13
13
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3434343434
7
```

### 输出

```
5
```

