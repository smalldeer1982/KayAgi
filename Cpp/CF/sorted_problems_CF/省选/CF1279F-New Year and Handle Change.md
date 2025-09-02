---
title: "New Year and Handle Change"
layout: "post"
diff: 省选/NOI-
pid: CF1279F
tag: []
---

# New Year and Handle Change

## 题目描述

New Year is getting near. So it's time to change handles on codeforces. Mishka wants to change his handle but in such a way that people would not forget who he is.

To make it work, he only allowed to change letters case. More formally, during one handle change he can choose any segment of his handle $ [i; i + l - 1] $ and apply tolower or toupper to all letters of his handle on this segment (more fomally, replace all uppercase letters with corresponding lowercase or vice versa). The length $ l $ is fixed for all changes.

Because it is not allowed to change codeforces handle too often, Mishka can perform at most $ k $ such operations. What is the minimum value of $ min(lower, upper) $ (where $ lower $ is the number of lowercase letters, and $ upper $ is the number of uppercase letters) can be obtained after optimal sequence of changes?

## 输入格式

The first line of the input contains three integers $ n, k $ and $ l $ ( $ 1 \le n, k, l \le 10^6, l \le n) $ — the length of Mishka's handle, the number of changes and the length of the segment.

The second line of the input contains one string $ s $ , consisting of $ n $ lowercase and uppercase Latin letters — Mishka's handle.

## 输出格式

Print one integer — the minimum value of $ min(lower, upper) $ after that Mishka change his handle at most $ k $ times in a way described in the problem statement.

## 样例 #1

### 输入

```
7 1 4
PikMike

```

### 输出

```
0

```

## 样例 #2

### 输入

```
15 2 2
AaAaAAaaAAAAaaA

```

### 输出

```
2

```

## 样例 #3

### 输入

```
14 2 6
aBcdEFGHIJklMn

```

### 输出

```
0

```

## 样例 #4

### 输入

```
9 2 2
aAaAAAaaA

```

### 输出

```
1

```

