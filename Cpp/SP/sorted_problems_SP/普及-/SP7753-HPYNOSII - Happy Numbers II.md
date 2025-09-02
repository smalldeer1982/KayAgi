---
title: "HPYNOSII - Happy Numbers II"
layout: "post"
diff: 普及-
pid: SP7753
tag: []
---

# HPYNOSII - Happy Numbers II

## 题目描述

The process of “**breaking**” an integer is defined as summing the squares of its digits. For example, the result of breaking the integer **125** is (**1 $ ^{2} $**  + **2 $ ^{2} $** + **5 $ ^{2} $** ) = **30**. An integer **N** is **happy** if after “**breaking**” it repeatedly the result reaches 1. If the result never reaches 1 no matter how many times the “**breaking**” is repeated, then N is not a happy number.

   
### TASK

Write a program that given an integer **T** (number of test cases) and **T** integers, determines for each number whether it is a happy number or not.

## 输入格式

The first line contains an integer **T**.

Next 1...T lines contain an integer **N** for detemining whether it is happy or not.

## 输出格式

T lines containing a single integer **N** which is the number of times the process had to be done to determine that N is happy, or **-1** if **N** is not happy.

## 样例 #1

### 输入

```
\n2\n19\n204\n\n
```

### 输出

```
\n4\n-1
```

