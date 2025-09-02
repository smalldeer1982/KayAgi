---
title: "Match & Catch"
layout: "post"
diff: 省选/NOI-
pid: CF427D
tag: []
---

# Match & Catch

## 题目描述

Police headquarter is monitoring signal on different frequency levels. They have got two suspiciously encoded strings $ s_{1} $ and $ s_{2} $ from two different frequencies as signals. They are suspecting that these two strings are from two different criminals and they are planning to do some evil task.

Now they are trying to find a common substring of minimum length between these two strings. The substring must occur only once in the first string, and also it must occur only once in the second string.

Given two strings $ s_{1} $ and $ s_{2} $ consist of lowercase Latin letters, find the smallest (by length) common substring $ p $ of both $ s_{1} $ and $ s_{2} $ , where $ p $ is a unique substring in $ s_{1} $ and also in $ s_{2} $ . See notes for formal definition of substring and uniqueness.

## 输入格式

The first line of input contains $ s_{1} $ and the second line contains $ s_{2} $ $ (1<=|s_{1}|,|s_{2}|<=5000) $ . Both strings consist of lowercase Latin letters.

## 输出格式

Print the length of the smallest common unique substring of $ s_{1} $ and $ s_{2} $ . If there are no common unique substrings of $ s_{1} $ and $ s_{2} $ print -1.

## 说明/提示

Imagine we have string $ a=a_{1}a_{2}a_{3}...a_{|a|} $ , where $ |a| $ is the length of string $ a $ , and $ a_{i} $ is the $ i^{th} $ letter of the string.

We will call string $ a_{l}a_{l+1}a_{l+2}...a_{r} $ $ (1<=l<=r<=|a|) $ the substring $ [l,r] $ of the string $ a $ .

The substring $ [l,r] $ is unique in $ a $ if and only if there is no pair $ l_{1},r_{1} $ such that $ l_{1}≠l $ and the substring $ [l_{1},r_{1}] $ is equal to the substring $ [l,r] $ in $ a $ .

## 样例 #1

### 输入

```
apple
pepperoni

```

### 输出

```
2

```

## 样例 #2

### 输入

```
lover
driver

```

### 输出

```
1

```

## 样例 #3

### 输入

```
bidhan
roy

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
testsetses
teeptes

```

### 输出

```
3

```

