---
title: "Complete the Word"
layout: "post"
diff: 普及/提高-
pid: CF716B
tag: []
---

# Complete the Word

## 题目描述

ZS the Coder loves to read the dictionary. He thinks that a word is nice if there exists a substring (contiguous segment of letters) of it of length $ 26 $ where each letter of English alphabet appears exactly once. In particular, if the string has length strictly less than $ 26 $ , no such substring exists and thus it is not nice.

Now, ZS the Coder tells you a word, where some of its letters are missing as he forgot them. He wants to determine if it is possible to fill in the missing letters so that the resulting word is nice. If it is possible, he needs you to find an example of such a word as well. Can you help him?

## 输入格式

The first and only line of the input contains a single string $ s $ ( $ 1<=|s|<=50000 $ ), the word that ZS the Coder remembers. Each character of the string is the uppercase letter of English alphabet ('A'-'Z') or is a question mark ('?'), where the question marks denotes the letters that ZS the Coder can't remember.

## 输出格式

If there is no way to replace all the question marks with uppercase letters such that the resulting word is nice, then print $ -1 $ in the only line.

Otherwise, print a string which denotes a possible nice word that ZS the Coder learned. This string should match the string from the input, except for the question marks replaced with uppercase English letters.

If there are multiple solutions, you may print any of them.

## 说明/提示

In the first sample case, ABCDEFGHIJKLMNOPQRZTUVWXYS is a valid answer beacuse it contains a substring of length $ 26 $ (the whole string in this case) which contains all the letters of the English alphabet exactly once. Note that there are many possible solutions, such as ABCDEFGHIJKLMNOPQRSTUVWXYZ or ABCEDFGHIJKLMNOPQRZTUVWXYS.

In the second sample case, there are no missing letters. In addition, the given string does not have a substring of length $ 26 $ that contains all the letters of the alphabet, so the answer is $ -1 $ .

In the third sample case, any string of length $ 26 $ that contains all letters of the English alphabet fits as an answer.

## 样例 #1

### 输入

```
ABC??FGHIJK???OPQR?TUVWXY?

```

### 输出

```
ABCDEFGHIJKLMNOPQRZTUVWXYS
```

## 样例 #2

### 输入

```
WELCOMETOCODEFORCESROUNDTHREEHUNDREDANDSEVENTYTWO

```

### 输出

```
-1
```

## 样例 #3

### 输入

```
??????????????????????????

```

### 输出

```
MNBVCXZLKJHGFDSAQPWOEIRUYT
```

## 样例 #4

### 输入

```
AABCDEFGHIJKLMNOPQRSTUVW??M

```

### 输出

```
-1
```

