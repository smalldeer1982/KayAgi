---
title: "Erase and Extend (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF1537E1
tag: []
---

# Erase and Extend (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is the constraints on $ n $ and $ k $ . You can make hacks only if all versions of the problem are solved.

You have a string $ s $ , and you can do two types of operations on it:

- Delete the last character of the string.
- Duplicate the string: $ s:=s+s $ , where $ + $ denotes concatenation.

You can use each operation any number of times (possibly none).

Your task is to find the lexicographically smallest string of length exactly $ k $ that can be obtained by doing these operations on string $ s $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a\ne b $ ;
- In the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The first line contains two integers $ n $ , $ k $ ( $ 1 \leq n, k \leq 5000 $ ) — the length of the original string $ s $ and the length of the desired string.

The second line contains the string $ s $ , consisting of $ n $ lowercase English letters.

## 输出格式

Print the lexicographically smallest string of length $ k $ that can be obtained by doing the operations on string $ s $ .

## 说明/提示

In the first test, it is optimal to make one duplication: "dbcadabc" $ \to $ "dbcadabcdbcadabc".

In the second test it is optimal to delete the last $ 3 $ characters, then duplicate the string $ 3 $ times, then delete the last $ 3 $ characters to make the string have length $ k $ .

"abcd" $ \to $ "abc" $ \to $ "ab" $ \to $ "a" $ \to $ "aa" $ \to $ "aaaa" $ \to $ "aaaaaaaa" $ \to $ "aaaaaaa" $ \to $ "aaaaaa" $ \to $ "aaaaa".

## 样例 #1

### 输入

```
8 16
dbcadabc
```

### 输出

```
dbcadabcdbcadabc
```

## 样例 #2

### 输入

```
4 5
abcd
```

### 输出

```
aaaaa
```

