---
title: "Intellectual Inquiry"
layout: "post"
diff: 省选/NOI-
pid: CF645E
tag: []
---

# Intellectual Inquiry

## 题目描述

After getting kicked out of her reporting job for not knowing the alphabet, Bessie has decided to attend school at the Fillet and Eggs Eater Academy. She has been making good progress with her studies and now knows the first $ k $ English letters.

Each morning, Bessie travels to school along a sidewalk consisting of $ m+n $ tiles. In order to help Bessie review, Mr. Moozing has labeled each of the first $ m $ sidewalk tiles with one of the first $ k $ lowercase English letters, spelling out a string $ t $ . Mr. Moozing, impressed by Bessie's extensive knowledge of farm animals, plans to let her finish labeling the last $ n $ tiles of the sidewalk by herself.

Consider the resulting string $ s $ ( $ |s|=m+n $ ) consisting of letters labeled on tiles in order from home to school. For any sequence of indices $ p_{1}<p_{2}<...<p_{q} $ we can define subsequence of the string $ s $ as string $ s_{p1}s_{p2}...\ s_{pq} $ . Two subsequences are considered to be distinct if they differ as strings. Bessie wants to label the remaining part of the sidewalk such that the number of distinct subsequences of tiles is maximum possible. However, since Bessie hasn't even finished learning the alphabet, she needs your help!

Note that empty subsequence also counts.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 0<=n<=1000000 $ , $ 1<=k<=26 $ ).

The second line contains a string $ t $ ( $ |t|=m,1<=m<=1000000 $ ) consisting of only first $ k $ lowercase English letters.

## 输出格式

Determine the maximum number of distinct subsequences Bessie can form after labeling the last $ n $ sidewalk tiles each with one of the first $ k $ lowercase English letters. Since this number can be rather large, you should print it modulo $ 10^{9}+7 $ .

Please note, that you are not asked to maximize the remainder modulo $ 10^{9}+7 $ ! The goal is to maximize the initial value and then print the remainder.

## 说明/提示

In the first sample, the optimal labeling gives $ 8 $ different subsequences: "" (the empty string), "a", "c", "b", "ac", "ab", "cb", and "acb".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF645E/9a7e922a3340c3ac5614145c3650ab330142ea1a.png)In the second sample, the entire sidewalk is already labeled. The are $ 10 $ possible different subsequences: "" (the empty string), "a", "b", "aa", "ab", "ba", "aaa", "aab", "aba", and "aaba". Note that some strings, including "aa", can be obtained with multiple sequences of tiles, but are only counted once.

## 样例 #1

### 输入

```
1 3
ac

```

### 输出

```
8

```

## 样例 #2

### 输入

```
0 2
aaba

```

### 输出

```
10

```

