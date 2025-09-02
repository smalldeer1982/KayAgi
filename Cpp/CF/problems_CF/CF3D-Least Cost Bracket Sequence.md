---
title: "Least Cost Bracket Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF3D
tag: ['字符串', '优先队列', '队列']
---

# Least Cost Bracket Sequence

## 题目描述

This is yet another problem on regular bracket sequences.

A bracket sequence is called regular, if by inserting "+" and "1" into it we get a correct mathematical expression. For example, sequences "(())()", "()" and "(()(()))" are regular, while ")(", "(()" and "(()))(" are not. You have a pattern of a bracket sequence that consists of characters "(", ")" and "?". You have to replace each character "?" with a bracket so, that you get a regular bracket sequence.

For each character "?" the cost of its replacement with "(" and ")" is given. Among all the possible variants your should choose the cheapest.

## 输入格式

The first line contains a non-empty pattern of even length, consisting of characters "(", ")" and "?". Its length doesn't exceed $ 5·10^{4} $ . Then there follow $ m $ lines, where $ m $ is the number of characters "?" in the pattern. Each line contains two integer numbers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=10^{6} $ ), where $ a_{i} $ is the cost of replacing the $ i $ -th character "?" with an opening bracket, and $ b_{i} $ — with a closing one.

## 输出格式

Print the cost of the optimal regular bracket sequence in the first line, and the required sequence in the second.

Print -1, if there is no answer. If the answer is not unique, print any of them.

## 样例 #1

### 输入

```
(??)
1 2
2 8

```

### 输出

```
4
()()

```

