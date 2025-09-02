---
title: "Spy Syndrome 2"
layout: "post"
diff: 普及+/提高
pid: CF633C
tag: []
---

# Spy Syndrome 2

## 题目描述

After observing the results of Spy Syndrome, Yash realised the errors of his ways. He now believes that a super spy such as Siddhant can't use a cipher as basic and ancient as Caesar cipher. After many weeks of observation of Siddhant’s sentences, Yash determined a new cipher technique.

For a given sentence, the cipher is processed as:

1. Convert all letters of the sentence to lowercase.
2. Reverse each of the words of the sentence individually.
3. Remove all the spaces in the sentence.

For example, when this cipher is applied to the sentence

Kira is childish and he hates losing

the resulting string is

ariksihsidlihcdnaehsetahgnisol

Now Yash is given some ciphered string and a list of words. Help him to find out any original sentence composed using only words from the list. Note, that any of the given words could be used in the sentence multiple times.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=10000 $ ) — the length of the ciphered text. The second line consists of $ n $ lowercase English letters — the ciphered text $ t $ .

The third line contains a single integer $ m $ ( $ 1<=m<=100000 $ ) — the number of words which will be considered while deciphering the text. Each of the next $ m $ lines contains a non-empty word $ w_{i} $ ( $ |w_{i}|<=1000 $ ) consisting of uppercase and lowercase English letters only. It's guaranteed that the total length of all words doesn't exceed $ 1000000 $ .

## 输出格式

Print one line — the original sentence. It is guaranteed that at least one solution exists. If there are multiple solutions, you may output any of those.

## 说明/提示

In sample case 2 there may be multiple accepted outputs, "HI there HeLLo" and "HI there hello" you may output any of them.

## 样例 #1

### 输入

```
30
ariksihsidlihcdnaehsetahgnisol
10
Kira
hates
is
he
losing
death
childish
L
and
Note

```

### 输出

```
Kira is childish and he hates losing 

```

## 样例 #2

### 输入

```
12
iherehtolleh
5
HI
Ho
there
HeLLo
hello

```

### 输出

```
HI there HeLLo 

```

