---
title: "Erase Subsequences"
layout: "post"
diff: 提高+/省选-
pid: CF1303E
tag: ['有限状态自动机']
---

# Erase Subsequences

## 题目描述

You are given a string $ s $ . You can build new string $ p $ from $ s $ using the following operation no more than two times:

1. choose any subsequence $ s_{i_1}, s_{i_2}, \dots, s_{i_k} $ where $ 1 \le i_1 < i_2 < \dots < i_k \le |s| $ ;
2. erase the chosen subsequence from $ s $ ( $ s $ can become empty);
3. concatenate chosen subsequence to the right of the string $ p $ (in other words, $ p = p + s_{i_1}s_{i_2}\dots s_{i_k} $ ).

Of course, initially the string $ p $ is empty.

For example, let $ s = \text{ababcd} $ . At first, let's choose subsequence $ s_1 s_4 s_5 = \text{abc} $ — we will get $ s = \text{bad} $ and $ p = \text{abc} $ . At second, let's choose $ s_1 s_2 = \text{ba} $ — we will get $ s = \text{d} $ and $ p = \text{abcba} $ . So we can build $ \text{abcba} $ from $ \text{ababcd} $ .

Can you build a given string $ t $ using the algorithm above?

## 输入格式

The first line contains the single integer $ T $ ( $ 1 \le T \le 100 $ ) — the number of test cases.

Next $ 2T $ lines contain test cases — two per test case. The first line contains string $ s $ consisting of lowercase Latin letters ( $ 1 \le |s| \le 400 $ ) — the initial string.

The second line contains string $ t $ consisting of lowercase Latin letters ( $ 1 \le |t| \le |s| $ ) — the string you'd like to build.

It's guaranteed that the total length of strings $ s $ doesn't exceed $ 400 $ .

## 输出格式

Print $ T $ answers — one per test case. Print YES (case insensitive) if it's possible to build $ t $ and NO (case insensitive) otherwise.

## 样例 #1

### 输入

```
4
ababcd
abcba
a
b
defi
fed
xyz
x
```

### 输出

```
YES
NO
NO
YES
```

