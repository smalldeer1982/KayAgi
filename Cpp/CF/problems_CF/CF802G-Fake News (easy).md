---
title: "Fake News (easy)"
layout: "post"
diff: 入门
pid: CF802G
tag: ['模拟', '字符串', '枚举', '队列']
---

# Fake News (easy)

## 题目描述

As it's the first of April, Heidi is suspecting that the news she reads today are fake, and she does not want to look silly in front of all the contestants. She knows that a newspiece is fake if it contains heidi as a subsequence. Help Heidi assess whether the given piece is true, but please be discreet about it...

## 输入格式

The first and only line of input contains a single nonempty string $ s $ of length at most $ 1000 $ composed of lowercase letters (a-z).

## 输出格式

Output YES if the string $ s $ contains heidi as a subsequence and NO otherwise.

## 说明/提示

A string $ s $ contains another string $ p $ as a subsequence if it is possible to delete some characters from $ s $ and obtain $ p $ .

## 样例 #1

### 输入

```
abcheaibcdi

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
hiedi

```

### 输出

```
NO
```

