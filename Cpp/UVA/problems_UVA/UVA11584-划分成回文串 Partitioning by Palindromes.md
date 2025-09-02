---
title: "划分成回文串 Partitioning by Palindromes"
layout: "post"
diff: 普及+/提高
pid: UVA11584
tag: ['字符串', '动态规划 DP', '搜索']
---

# 划分成回文串 Partitioning by Palindromes

## 题目描述

回文子串(palind)

**问题描述：**

当一个字符串正序和反序是完全相同时，我们称之为“回文串”。例如“racecar”就是一个回文串，而“fastcar”就不是。现在给一个字符串s，把它分割成若干个互不相交的回文子串，求分割的回文子串的最少个数。

## 输入格式

第一行为正整数t(≤10)，表示数据组数；接下来t行，每行一个完全由小写字母组成的字符串，长度不超过1000。

## 输出格式

对于每组数据，输出最少回文子串数。

由 @C919 提供翻译

## 样例 #1

### 输入

```
3
racecar
fastcar
aaadbccb
```

### 输出

```
1
7
3
```

