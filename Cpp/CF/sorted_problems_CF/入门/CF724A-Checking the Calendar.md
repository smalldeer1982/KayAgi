---
title: "Checking the Calendar"
layout: "post"
diff: 入门
pid: CF724A
tag: []
---

# Checking the Calendar

## 题目描述

您将得到一周中某两天的英文名。
请判断是否有可能在某个非闰年期间，某个月的第一天为给出的第一天，下个月的第一天为给出的第二天。这两个月应属于同一年。
本题中，我们将使用公历，即一年有12个月，每个月的天数分别为： _31,28,31,30,31,30,31,31,30,31,30,31_ 。
给出的日期名称将以小写英文单词给出，即为: _"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"_ 。

## 输入格式

两行。

## 输出格式

如果可能，请输出 _"YES"_ （不加引号），否则输出 _"NO"_ （不加引号）。

## 样例 #1

### 输入

```
monday
tuesday

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
sunday
sunday

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
saturday
tuesday

```

### 输出

```
YES

```

