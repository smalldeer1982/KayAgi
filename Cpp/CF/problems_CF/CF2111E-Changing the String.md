---
title: "Changing the String"
layout: "post"
diff: 普及+/提高
pid: CF2111E
tag: []
---

# Changing the String

## 题目描述

Given a string $ s $ that consists only of the first three letters of the Latin alphabet, meaning each character of the string is either a, b, or c.

Also given are $ q $ operations that need to be performed on the string. In each operation, two letters $ x $ and $ y $ from the set of the first three letters of the Latin alphabet are provided, and for each operation, one of the following two actions must be taken:

- change any (one) occurrence of the letter $ x $ in the string $ s $ to the letter $ y $ (if at least one occurrence of the letter $ x $ exists);
- do nothing.

The goal is to perform all operations in the given order in such a way that the string $ s $ becomes lexicographically minimal.

Recall that a string $ a $ is lexicographically less than a string $ b $ if and only if one of the following conditions holds:

- $ a $ is a prefix of $ b $ , but $ a \neq b $ ;
- at the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that comes earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^{3} $ ) — the number of test cases. The description of the test cases follows.

In the first line of each test case, there are two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^{5} $ ) — the length of the string $ s $ and the number of operations.

In the second line of each test case, the string $ s $ is given — a string of exactly $ n $ characters, each of which is a, b, or c.

The next $ q $ lines of each test case contain the description of the operations. Each line contains two characters $ x $ and $ y $ , each of which is a, b, or c.

Additional constraints on the input:

- the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^{5} $ ;
- the sum of $ q $ across all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, output the lexicographically minimal string that can be obtained from $ s $ using the given operations.

## 说明/提示

In the first test case, both operations need to be applied to the first letter:

1. after the first operation, $ s =  $ "bb"
2. after the second operation, $ s =  $ "ab"

In the second test case, the string could change as follows:

1. "bbbbabbbbb" (changed the $ 5 $ -th letter)
2. "cbbbabbbbb" (changed the $ 1 $ -st letter)
3. "cbbbabbbbb" (did nothing)
4. "cbbaabbbbb" (changed the $ 4 $ -th letter)
5. "abbaabbbbb" (changed the $ 1 $ -st letter)
6. "abcaabbbbb" (changed the $ 3 $ -rd letter)
7. "abcaabbbbb" (did nothing)
8. "aacaabbbbb" (changed the $ 2 $ -nd letter)
9. "aacaabbbbb" (did nothing)
10. "aaaaabbbbb" (changed the $ 3 $ -rd letter)

## 样例 #1

### 输入

```
3
2 2
cb
c b
b a
10 10
bbbbbbbbbb
b a
b c
c b
b a
c a
b c
b c
b a
a b
c a
30 20
abcaababcbbcabcbbcabcbabbbbabc
b c
b c
c a
b c
b c
b a
b c
b c
b a
b a
b a
b a
c a
b c
c a
b c
c a
c a
b c
c b
```

### 输出

```
ab
aaaaabbbbb
aaaaaaaaaaaaaaabbbabcbabbbbabc
```

