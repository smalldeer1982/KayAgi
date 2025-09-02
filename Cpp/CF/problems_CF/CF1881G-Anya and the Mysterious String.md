---
title: "Anya and the Mysterious String"
layout: "post"
diff: 普及+/提高
pid: CF1881G
tag: []
---

# Anya and the Mysterious String

## 题目描述

Anya received a string $ s $ of length $ n $ brought from Rome. The string $ s $ consists of lowercase Latin letters and at first glance does not raise any suspicions. An instruction was attached to the string.

Start of the instruction.

A palindrome is a string that reads the same from left to right and right to left. For example, the strings "anna", "aboba", "level" are palindromes, while the strings "gorilla", "banan", "off" are not.

A substring $ [l \ldots r] $ of string $ s $ is a string $ s_l s_{l+1} \ldots s_{r-1} s_r $ . For example, the substring $ [4 \ldots 6] $ of the string "generation" is the string "era".

A string is called beautiful if it does not contain a substring of length at least two that is a palindrome. For example, the strings "fox", "abcdef", and "yioy" are beautiful, while the strings "xyxx", "yikjkitrb" are not.

When an integer $ x $ is added to the character $ s_i $ , it is replaced $ x $ times with the next character in the alphabet, with "z" being replaced by "a".

When an integer $ x $ is added to the substring $ [l, r] $ of string $ s $ , it becomes the string $ s_1 s_2 \ldots s_{l-1} (s_l + x) (s_{l+1} + x) \ldots (s_{r-1} + x) (s_r + x) s_{r+1} \ldots s_n $ . For example, when the substring $ [2, 4] $ of the string "abazaba" is added with the number $ 6 $ , the resulting string is "ahgfaba".

End of the instruction.

After reading the instruction, Anya resigned herself to the fact that she has to answer $ m $ queries. The queries can be of two types:

1. Add the number $ x $ to the substring $ [l \ldots r] $ of string $ s $ .
2. Determine whether the substring $ [l \ldots r] $ of string $ s $ is beautiful.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) - the number of test cases.

The descriptions of the test cases follow.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 2 \cdot 10^5 $ ) - the length of the string $ s $ and the number of queries.

The second line of each test case contains the string $ s $ of length $ n $ , consisting of lowercase Latin letters.

The next $ m $ lines contain the queries:

- $ 1 $ $ l $ $ r $ $ x $ ( $ 1 \le l \le r \le n $ , $ 1 \le x \le 10^9 $ ) - description of a query of the first type;
- $ 2 $ $ l $ $ r $ ( $ 1 \le l \le r \le n $ ) - description of a query of the second type.

It is guaranteed that the sum of $ n $ and the sum of $ m $ over all test cases do not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query of the second type, output "YES" if the substring $ [l \ldots r] $ of string $ s $ is beautiful, otherwise output "NO".

You can output "YES" and "NO" in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive answers).

## 说明/提示

In the first test case of the first test, the following happens:

- tedubcyyxopz: the string edub is beautiful;
- tedubcyyxopz $ \to $ tedwdeaaxopz;
- tedwdeaaxopz: the string tedwdea is not beautiful as it contains the palindrome edwde;
- tedwdeaaxopz $ \to $ terkreaaxopz;
- terkreaaxopz $ \to $ terkreaaarsz;
- terkreaaarsz $ \to $ terkreaaaasz;
- terkreaaaasz: the string kreaaaa is not beautiful as it contains the palindrome aaaa;
- terkreaaaasz: the string asz is beautiful.

## 样例 #1

### 输入

```
5
12 8
tedubcyyxopz
2 2 5
1 4 8 2
2 1 7
1 3 5 40
1 9 11 3
1 10 10 9
2 4 10
2 10 12
10 4
ubnxwwgzjt
2 4 10
2 10 10
1 6 10 8
2 7 7
11 3
hntcxfxyhtu
1 4 6 1
2 4 10
1 4 10 21
13 2
yxhlmzfhqctir
1 5 9 3
1 8 13 15
2 3
bp
1 1 2 15
1 1 2 18
1 2 2 1000000000
```

### 输出

```
YES
NO
NO
YES
NO
YES
YES
YES
```

