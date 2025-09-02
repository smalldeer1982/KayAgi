---
title: "Check the string"
layout: "post"
diff: 普及/提高-
pid: CF960A
tag: []
---

# Check the string

## 题目描述

A has a string consisting of some number of lowercase English letters 'a'. He gives it to his friend B who appends some number of letters 'b' to the end of this string. Since both A and B like the characters 'a' and 'b', they have made sure that at this point, at least one 'a' and one 'b' exist in the string.

B now gives this string to C and he appends some number of letters 'c' to the end of the string. However, since C is a good friend of A and B, the number of letters 'c' he appends is equal to the number of 'a' or to the number of 'b' in the string. It is also possible that the number of letters 'c' equals both to the number of letters 'a' and to the number of letters 'b' at the same time.

You have a string in your hands, and you want to check if it is possible to obtain the string in this way or not. If it is possible to obtain the string, print "YES", otherwise print "NO" (without the quotes).

## 输入格式

The first and only line consists of a string $ S $ ( $  1 \le |S| \le 5\,000  $ ). It is guaranteed that the string will only consist of the lowercase English letters 'a', 'b', 'c'.

## 输出格式

Print "YES" or "NO", according to the condition.

## 说明/提示

Consider first example: the number of 'c' is equal to the number of 'a'.

Consider second example: although the number of 'c' is equal to the number of the 'b', the order is not correct.

Consider third example: the number of 'c' is equal to the number of 'b'.

## 样例 #1

### 输入

```
aaabccc

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
bbacc

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
aabc

```

### 输出

```
YES

```

