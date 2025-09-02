---
title: "Smaller"
layout: "post"
diff: 普及/提高-
pid: CF1742F
tag: []
---

# Smaller

## 题目描述

Alperen has two strings, $ s $ and $ t $ which are both initially equal to "a".

He will perform $ q $ operations of two types on the given strings:

- $ 1 \;\; k \;\; x $ — Append the string $ x $ exactly $ k $ times at the end of string $ s $ . In other words, $ s := s + \underbrace{x + \dots + x}_{k \text{ times}} $ .
- $ 2 \;\; k \;\; x $ — Append the string $ x $ exactly $ k $ times at the end of string $ t $ . In other words, $ t := t + \underbrace{x + \dots + x}_{k \text{ times}} $ .

After each operation, determine if it is possible to rearrange the characters of $ s $ and $ t $ such that $ s $ is lexicographically smaller $ ^{\dagger} $ than $ t $ .

Note that the strings change after performing each operation and don't go back to their initial states.

 $ ^{\dagger} $ Simply speaking, the lexicographical order is the order in which words are listed in a dictionary. A formal definition is as follows: string $ p $ is lexicographically smaller than string $ q $ if there exists a position $ i $ such that $ p_i < q_i $ , and for all $ j < i $ , $ p_j = q_j $ . If no such $ i $ exists, then $ p $ is lexicographically smaller than $ q $ if the length of $ p $ is less than the length of $ q $ . For example, $ \texttt{abdc} < \texttt{abe} $ and $ \texttt{abc} < \texttt{abcd} $ , where we write $ p < q $ if $ p $ is lexicographically smaller than $ q $ .

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ q $ $ (1 \leq q \leq 10^5) $ — the number of operations Alperen will perform.

Then $ q $ lines follow, each containing two positive integers $ d $ and $ k $ ( $ 1 \leq d \leq 2 $ ; $ 1 \leq k \leq 10^5 $ ) and a non-empty string $ x $ consisting of lowercase English letters — the type of the operation, the number of times we will append string $ x $ and the string we need to append respectively.

It is guaranteed that the sum of $ q $ over all test cases doesn't exceed $ 10^5 $ and that the sum of lengths of all strings $ x $ in the input doesn't exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each operation, output "YES", if it is possible to arrange the elements in both strings in such a way that $ s $ is lexicographically smaller than $ t $ and "NO" otherwise.

## 说明/提示

In the first test case, the strings are initially $ s =  $ "a" and $ t =  $ "a".

After the first operation the string $ t $ becomes "aaa". Since "a" is already lexicographically smaller than "aaa", the answer for this operation should be "YES".

After the second operation string $ s $ becomes "aaa", and since $ t $ is also equal to "aaa", we can't arrange $ s $ in any way such that it is lexicographically smaller than $ t $ , so the answer is "NO".

After the third operation string $ t $ becomes "aaaaaa" and $ s $ is already lexicographically smaller than it so the answer is "YES".

After the fourth operation $ s $ becomes "aaabb" and there is no way to make it lexicographically smaller than "aaaaaa" so the answer is "NO".

After the fifth operation the string $ t $ becomes "aaaaaaabcaabcaabca", and we can rearrange the strings to: "bbaaa" and "caaaaaabcaabcaabaa" so that $ s $ is lexicographically smaller than $ t $ , so we should answer "YES".

## 样例 #1

### 输入

```
3
5
2 1 aa
1 2 a
2 3 a
1 2 b
2 3 abca
2
1 5 mihai
2 2 buiucani
3
1 5 b
2 3 a
2 4 paiu
```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
NO
NO
YES
```

