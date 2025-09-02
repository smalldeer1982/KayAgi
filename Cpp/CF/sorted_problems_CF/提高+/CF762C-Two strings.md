---
title: "Two strings"
layout: "post"
diff: 提高+/省选-
pid: CF762C
tag: []
---

# Two strings

## 题目描述

You are given two strings $ a $ and $ b $ . You have to remove the minimum possible number of consecutive (standing one after another) characters from string $ b $ in such a way that it becomes a subsequence of string $ a $ . It can happen that you will not need to remove any characters at all, or maybe you will have to remove all of the characters from $ b $ and make it empty.

Subsequence of string $ s $ is any such string that can be obtained by erasing zero or more characters (not necessarily consecutive) from string $ s $ .

## 输入格式

The first line contains string $ a $ , and the second line — string $ b $ . Both of these strings are nonempty and consist of lowercase letters of English alphabet. The length of each string is no bigger than $ 10^{5} $ characters.

## 输出格式

On the first line output a subsequence of string $ a $ , obtained from $ b $ by erasing the minimum number of consecutive characters.

If the answer consists of zero characters, output «-» (a minus sign).

## 说明/提示

In the first example strings $ a $ and $ b $ don't share any symbols, so the longest string that you can get is empty.

In the second example ac is a subsequence of $ a $ , and at the same time you can obtain it by erasing consecutive symbols cepted from string $ b $ .

## 样例 #1

### 输入

```
hi
bob

```

### 输出

```
-

```

## 样例 #2

### 输入

```
abca
accepted

```

### 输出

```
ac

```

## 样例 #3

### 输入

```
abacaba
abcdcba

```

### 输出

```
abcba

```

