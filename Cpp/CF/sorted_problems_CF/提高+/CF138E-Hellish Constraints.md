---
title: "Hellish Constraints"
layout: "post"
diff: 提高+/省选-
pid: CF138E
tag: []
---

# Hellish Constraints

## 题目描述

Katya recently started to invent programming tasks and prepare her own contests. What she does not like is boring and simple constraints. Katya is fed up with all those " $ N $ does not exceed a thousand" and "the sum of $ a_{i} $ does not exceed a million" and she decided to come up with something a little more complicated.

The last problem written by Katya deals with strings. The input is a string of small Latin letters. To make the statement longer and strike terror into the people who will solve the contest, Katya came up with the following set of $ k $ restrictions of the same type (characters in restrictions can be repeated and some restrictions may contradict each other):

- The number of characters $ c_{1} $ in a string is not less than $ l_{1} $ and not more than $ r_{1} $ .
- ...
- The number of characters $ c_{i} $ in a string is not less than $ l_{i} $ and not more than $ r_{i} $ .
- ...
- The number of characters $ c_{k} $ in a string is not less than $ l_{k} $ and not more than $ r_{k} $ .

However, having decided that it is too simple and obvious, Katya added the following condition: a string meets no less than $ L $ and not more than $ R $ constraints from the above given list.

Katya does not like to compose difficult and mean tests, so she just took a big string $ s $ and wants to add to the tests all its substrings that meet the constraints. However, Katya got lost in her conditions and asked you to count the number of substrings of the string $ s $ that meet the conditions (each occurrence of the substring is counted separately).

## 输入格式

The first line contains a non-empty string $ s $ , consisting of small Latin letters. The length of the string $ s $ does not exceed $ 10^{5} $ .

The second line contains three space-separated integers $ k $ , $ L $ and $ R $ ( $ 0<=L<=R<=k<=500 $ ).

Next $ k $ lines contain Katya's constrictions in the following form " $ c_{i} $ $ l_{i} $ $ r_{i} $ ". All letters $ c_{i} $ are small Latin letters, $ l_{i} $ and $ r_{i} $ are integers ( $ 0<=l_{i}<=r_{i}<=|s| $ , where $ |s| $ is the length of string $ s $ ). Letters $ c_{i} $ are not necessarily different.

## 输出格式

Print a single number — the number of substrings that meet the constrictions.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the cout stream or the %I64d specificator.

## 说明/提示

In the first test we should count the number of strings that do not contain characters "e" and "o". All such strings are as follows (in the order of occurrence in the initial string from the left to the right): "c", "d"', "f", "r", "rc", "c", "s".

In the second test we cannot achieve fulfilling exactly one of the two identical constrictions, so the answer is 0.

## 样例 #1

### 输入

```
codeforces
2 0 0
o 1 2
e 1 2

```

### 输出

```
7

```

## 样例 #2

### 输入

```
codeforces
2 1 1
o 1 2
o 1 2

```

### 输出

```
0

```

