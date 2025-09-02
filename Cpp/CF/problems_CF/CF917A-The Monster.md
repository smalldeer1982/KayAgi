---
title: "The Monster"
layout: "post"
diff: 普及/提高-
pid: CF917A
tag: ['枚举']
---

# The Monster

## 题目描述

As Will is stuck in the Upside Down, he can still communicate with his mom, Joyce, through the Christmas lights (he can turn them on and off with his mind). He can't directly tell his mom where he is, because the monster that took him to the Upside Down will know and relocate him.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917A/4c119b489e29bab2fd3dc778221019b04c8209ba.png)Thus, he came up with a puzzle to tell his mom his coordinates. His coordinates are the answer to the following problem.

A string consisting only of parentheses ('(' and ')') is called a bracket sequence. Some bracket sequence are called correct bracket sequences. More formally:

- Empty string is a correct bracket sequence.
- if $ s $ is a correct bracket sequence, then $ (s) $ is also a correct bracket sequence.
- if $ s $ and $ t $ are correct bracket sequences, then $ st $ (concatenation of $ s $ and $ t $ ) is also a correct bracket sequence.

A string consisting of parentheses and question marks ('?') is called pretty if and only if there's a way to replace each question mark with either '(' or ')' such that the resulting string is a non-empty correct bracket sequence.

Will gave his mom a string $ s $ consisting of parentheses and question marks (using Morse code through the lights) and his coordinates are the number of pairs of integers $ (l,r) $ such that $ 1<=l<=r<=|s| $ and the string $ s_{l}s_{l+1}...\ s_{r} $ is pretty, where $ s_{i} $ is $ i $ -th character of $ s $ .

Joyce doesn't know anything about bracket sequences, so she asked for your help.

## 输入格式

The first and only line of input contains string $ s $ , consisting only of characters '(', ')' and '?' ( $ 2<=|s|<=5000 $ ).

## 输出格式

Print the answer to Will's puzzle in the first and only line of output.

## 说明/提示

For the first sample testcase, the pretty substrings of $ s $ are:

1. "(?" which can be transformed to "()".
2. "?)" which can be transformed to "()".
3. "((?)" which can be transformed to "(())".
4. "(?))" which can be transformed to "(())".

For the second sample testcase, the pretty substrings of $ s $ are:

1. "??" which can be transformed to "()".
2. "()".
3. "??()" which can be transformed to "()()".
4. "?()?" which can be transformed to "(())".
5. "??" which can be transformed to "()".
6. "()??" which can be transformed to "()()".
7. "??()??" which can be transformed to "()()()".

## 样例 #1

### 输入

```
((?))

```

### 输出

```
4

```

## 样例 #2

### 输入

```
??()??

```

### 输出

```
7

```

