---
title: "Most Similar Words"
layout: "post"
diff: 普及-
pid: CF1676C
tag: ['模拟']
---

# Most Similar Words

## 题目描述

You are given $ n $ words of equal length $ m $ , consisting of lowercase Latin alphabet letters. The $ i $ -th word is denoted $ s_i $ .

In one move you can choose any position in any single word and change the letter at that position to the previous or next letter in alphabetical order. For example:

- you can change 'e' to 'd' or to 'f';
- 'a' can only be changed to 'b';
- 'z' can only be changed to 'y'.

The difference between two words is the minimum number of moves required to make them equal. For example, the difference between "best" and "cost" is $ 1 + 10 + 0 + 0 = 11 $ .

Find the minimum difference of $ s_i $ and $ s_j $ such that $ (i < j) $ . In other words, find the minimum difference over all possible pairs of the $ n $ words.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains $ 2 $ integers $ n $ and $ m $ ( $ 2 \leq n \leq 50 $ , $ 1 \leq m \leq 8 $ ) — the number of strings and their length respectively.

Then follows $ n $ lines, the $ i $ -th of which containing a single string $ s_i $ of length $ m $ , consisting of lowercase Latin letters.

## 输出格式

For each test case, print a single integer — the minimum difference over all possible pairs of the given strings.

## 说明/提示

For the second test case, one can show that the best pair is ("abb","bef"), which has difference equal to $ 8 $ , which can be obtained in the following way: change the first character of the first string to 'b' in one move, change the second character of the second string to 'b' in $ 3 $ moves and change the third character of the second string to 'b' in $ 4 $ moves, thus making in total $ 1 + 3 + 4 = 8 $ moves.

For the third test case, there is only one possible pair and it can be shown that the minimum amount of moves necessary to make the strings equal is $ 35 $ .

For the fourth test case, there is a pair of strings which is already equal, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
6
2 4
best
cost
6 3
abb
zba
bef
cdu
ooo
zzz
2 7
aaabbbc
bbaezfe
3 2
ab
ab
ab
2 8
aaaaaaaa
zzzzzzzz
3 1
a
u
y
```

### 输出

```
11
8
35
0
200
4
```

