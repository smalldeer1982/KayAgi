---
title: "Phone numbers"
layout: "post"
diff: 入门
pid: CF25B
tag: ['模拟', '字符串']
---

# Phone numbers

## 题目描述

Phone number in Berland is a sequence of $ n $ digits. Often, to make it easier to memorize the number, it is divided into groups of two or three digits. For example, the phone number 1198733 is easier to remember as 11-987-33. Your task is to find for a given phone number any of its divisions into groups of two or three digits.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=100 $ ) — amount of digits in the phone number. The second line contains $ n $ digits — the phone number to divide into groups.

## 输出格式

Output any of divisions of the given phone number into groups of two or three digits. Separate groups by single character -. If the answer is not unique, output any.

## 样例 #1

### 输入

```
6
549871

```

### 输出

```
54-98-71
```

## 样例 #2

### 输入

```
7
1198733

```

### 输出

```
11-987-33

```

