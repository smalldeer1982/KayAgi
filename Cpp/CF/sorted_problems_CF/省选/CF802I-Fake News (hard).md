---
title: "Fake News (hard)"
layout: "post"
diff: 省选/NOI-
pid: CF802I
tag: []
---

# Fake News (hard)

## 题目描述

Now that you have proposed a fake post for the HC $ ^{2} $ Facebook page, Heidi wants to measure the quality of the post before actually posting it. She recently came across a (possibly fake) article about the impact of fractal structure on multimedia messages and she is now trying to measure the self-similarity of the message, which is defined as

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802I/cdbfdfc02921b55d94f8e9715364be36292f81c3.png)where the sum is over all nonempty strings $ p $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802I/aea1d5f3b9f7520d94fcc0daea05a447b5429c82.png) is the number of occurences of $ p $ in $ s $ as a substring. (Note that the sum is infinite, but it only has a finite number of nonzero summands.)

Heidi refuses to do anything else until she knows how to calculate this self-similarity. Could you please help her? (If you would like to instead convince Heidi that a finite string cannot be a fractal anyway – do not bother, we have already tried.)

## 输入格式

The input starts with a line indicating the number of test cases $ T $ ( $ 1<=T<=10 $ ). After that, $ T $ test cases follow, each of which consists of one line containing a string $ s $ ( $ 1<=|s|<=100000 $ ) composed of lowercase letters (a-z).

## 输出格式

Output $ T $ lines, every line containing one number – the answer to the corresponding test case.

## 说明/提示

A string $ s $ contains another string $ p $ as a substring if $ p $ is a contiguous subsequence of $ s $ . For example, ab is a substring of cab but not of acb.

## 样例 #1

### 输入

```
4
aa
abcd
ccc
abcc

```

### 输出

```
5
10
14
12

```

