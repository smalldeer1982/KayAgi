---
title: "Minimal String Xoration"
layout: "post"
diff: 省选/NOI-
pid: CF1654F
tag: []
---

# Minimal String Xoration

## 题目描述

You are given an integer $ n $ and a string $ s $ consisting of $ 2^n $ lowercase letters of the English alphabet. The characters of the string $ s $ are $ s_0s_1s_2\cdots s_{2^n-1} $ .

A string $ t $ of length $ 2^n $ (whose characters are denoted by $ t_0t_1t_2\cdots t_{2^n-1} $ ) is a xoration of $ s $ if there exists an integer $ j $ ( $ 0\le j \leq 2^n-1 $ ) such that, for each $ 0 \leq i \leq 2^n-1 $ , $ t_i = s_{i \oplus j} $ (where $ \oplus $ denotes the operation [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

Find the lexicographically minimal xoration of $ s $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 18 $ ).

The second line contains a string $ s $ consisting of $ 2^n $ lowercase letters of the English alphabet.

## 输出格式

Print a single line containing the lexicographically minimal xoration of $ s $ .

## 说明/提示

In the first test, the lexicographically minimal xoration $ t $ of $ s = $ "acba" is "abca". It's a xoration because, for $ j = 3 $ ,

- $ t_0 = s_{0 \oplus j} = s_3 = $ "a";
- $ t_1 = s_{1 \oplus j} = s_2 = $ "b";
- $ t_2 = s_{2 \oplus j} = s_1 = $ "c";
- $ t_3 = s_{3 \oplus j} = s_0 = $ "a".

 There isn't any xoration of $ s $ lexicographically smaller than "abca".In the second test, the minimal string xoration corresponds to choosing $ j = 4 $ in the definition of xoration.

In the third test, the minimal string xoration corresponds to choosing $ j = 11 $ in the definition of xoration.

In the fourth test, the minimal string xoration corresponds to choosing $ j = 10 $ in the definition of xoration.

In the fifth test, the minimal string xoration corresponds to choosing either $ j = 0 $ or $ j = 1 $ in the definition of xoration.

## 样例 #1

### 输入

```
2
acba
```

### 输出

```
abca
```

## 样例 #2

### 输入

```
3
bcbaaabb
```

### 输出

```
aabbbcba
```

## 样例 #3

### 输入

```
4
bdbcbccdbdbaaccd
```

### 输出

```
abdbdccacbdbdccb
```

## 样例 #4

### 输入

```
5
ccfcffccccccffcfcfccfffffcccccff
```

### 输出

```
cccccffffcccccffccfcffcccccfffff
```

## 样例 #5

### 输入

```
1
zz
```

### 输出

```
zz
```

