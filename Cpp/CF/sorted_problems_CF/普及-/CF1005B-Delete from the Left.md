---
title: "Delete from the Left"
layout: "post"
diff: 普及-
pid: CF1005B
tag: ['字符串']
---

# Delete from the Left

## 题目描述

You are given two strings $ s $ and $ t $ . In a single move, you can choose any of two strings and delete the first (that is, the leftmost) character. After a move, the length of the string decreases by $ 1 $ . You can't choose a string if it is empty.

For example:

- by applying a move to the string "where", the result is the string "here",
- by applying a move to the string "a", the result is an empty string "".

You are required to make two given strings equal using the fewest number of moves. It is possible that, in the end, both strings will be equal to the empty string, and so, are equal to each other. In this case, the answer is obviously the sum of the lengths of the initial strings.

Write a program that finds the minimum number of moves to make two given strings $ s $ and $ t $ equal.

## 输入格式

The first line of the input contains $ s $ . In the second line of the input contains $ t $ . Both strings consist only of lowercase Latin letters. The number of letters in each string is between 1 and $ 2\cdot10^5 $ , inclusive.

## 输出格式

Output the fewest number of moves required. It is possible that, in the end, both strings will be equal to the empty string, and so, are equal to each other. In this case, the answer is obviously the sum of the lengths of the given strings.

## 说明/提示

In the first example, you should apply the move once to the first string and apply the move once to the second string. As a result, both strings will be equal to "est".

In the second example, the move should be applied to the string "codeforces" $ 8 $ times. As a result, the string becomes "codeforces" $ \to $ "es". The move should be applied to the string "yes" once. The result is the same string "yes" $ \to $ "es".

In the third example, you can make the strings equal only by completely deleting them. That is, in the end, both strings will be empty.

In the fourth example, the first character of the second string should be deleted.

## 样例 #1

### 输入

```
test
west

```

### 输出

```
2

```

## 样例 #2

### 输入

```
codeforces
yes

```

### 输出

```
9

```

## 样例 #3

### 输入

```
test
yes

```

### 输出

```
7

```

## 样例 #4

### 输入

```
b
ab

```

### 输出

```
1

```

