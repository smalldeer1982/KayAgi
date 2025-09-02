---
title: "Obtaining the String"
layout: "post"
diff: 普及-
pid: CF1015B
tag: ['字符串', '贪心']
---

# Obtaining the String

## 题目描述

You are given two strings $ s $ and $ t $ . Both strings have length $ n $ and consist of lowercase Latin letters. The characters in the strings are numbered from $ 1 $ to $ n $ .

You can successively perform the following move any number of times (possibly, zero):

- swap any two adjacent (neighboring) characters of $ s $ (i.e. for any $ i = \{1, 2, \dots, n - 1\} $ you can swap $ s_i $ and $ s_{i + 1}) $ .

You can't apply a move to the string $ t $ . The moves are applied to the string $ s $ one after another.

Your task is to obtain the string $ t $ from the string $ s $ . Find any way to do it with at most $ 10^4 $ such moves.

You do not have to minimize the number of moves, just find any sequence of moves of length $ 10^4 $ or less to transform $ s $ into $ t $ .

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 50 $ ) — the length of strings $ s $ and $ t $ .

The second line of the input contains the string $ s $ consisting of $ n $ lowercase Latin letters.

The third line of the input contains the string $ t $ consisting of $ n $ lowercase Latin letters.

## 输出格式

If it is impossible to obtain the string $ t $ using moves, print "-1".

Otherwise in the first line print one integer $ k $ — the number of moves to transform $ s $ to $ t $ . Note that $ k $ must be an integer number between $ 0 $ and $ 10^4 $ inclusive.

In the second line print $ k $ integers $ c_j $ ( $ 1 \le c_j < n $ ), where $ c_j $ means that on the $ j $ -th move you swap characters $ s_{c_j} $ and $ s_{c_j + 1} $ .

If you do not need to apply any moves, print a single integer $ 0 $ in the first line and either leave the second line empty or do not print it at all.

## 说明/提示

In the first example the string $ s $ changes as follows: "abcdef" $ \rightarrow $ "abdcef" $ \rightarrow $ "abdcfe" $ \rightarrow $ "abdfce" $ \rightarrow $ "abdfec".

In the second example there is no way to transform the string $ s $ into the string $ t $ through any allowed moves.

## 样例 #1

### 输入

```
6
abcdef
abdfec

```

### 输出

```
4
3 5 4 5 

```

## 样例 #2

### 输入

```
4
abcd
accd

```

### 输出

```
-1

```

