---
title: "Clock Conversion"
layout: "post"
diff: 入门
pid: CF1950C
tag: ['模拟']
---

# Clock Conversion

## 题目描述

Given the time in 24-hour format, output the equivalent time in 12-hour format.

- [24-hour format](https://en.wikipedia.org/wiki/24-hour_clock#Description) divides the day into 24 hours from $ 00 $ to $ 23 $ , each of which has 60 minutes from $ 00 $ to $ 59 $ .
- [12-hour format](https://en.wikipedia.org/wiki/12-hour_clock#Description) divides the day into two halves: the first half is $ \mathrm{AM} $ , and the second half is $ \mathrm{PM} $ . In each half, the hours are numbered in the order $ 12, 01, 02, 03, \dots, 11 $ . Each hour has 60 minutes numbered from $ 00 $ to $ 59 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1440 $ ) — the number of test cases.

The only line of each test case contains a string $ s $ of length $ 5 $ with format hh:mm representing a valid time in the 24-hour format. hh represents the hour from $ 00 $ to $ 23 $ , and mm represents the minute from $ 00 $ to $ 59 $ .

The input will always be a valid time in 24-hour format.

## 输出格式

For each test case, output two strings separated by a space ("hh:mm AM" or "hh:mm PM"), which are the 12-hour equivalent to the time provided in the test case (without quotes).

You should output the time exactly as indicated; in particular, you should not remove leading zeroes.

## 样例 #1

### 输入

```
11
09:41
18:06
12:14
00:59
00:00
14:34
01:01
19:07
11:59
12:00
21:37
```

### 输出

```
09:41 AM
06:06 PM
12:14 PM
12:59 AM
12:00 AM
02:34 PM
01:01 AM
07:07 PM
11:59 AM
12:00 PM
09:37 PM
```

