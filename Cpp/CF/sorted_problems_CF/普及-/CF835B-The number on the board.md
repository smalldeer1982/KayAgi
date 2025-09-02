---
title: "The number on the board"
layout: "post"
diff: 普及-
pid: CF835B
tag: ['字符串', '贪心', '排序']
---

# The number on the board

## 题目描述

Some natural number was written on the board. Its sum of digits was not less than $ k $ . But you were distracted a bit, and someone changed this number to $ n $ , replacing some digits with others. It's known that the length of the number didn't change.

You have to find the minimum number of digits in which these two numbers can differ.

## 输入格式

The first line contains integer $ k $ ( $ 1<=k<=10^{9} $ ).

The second line contains integer $ n $ ( $ 1<=n&lt;10^{100000} $ ).

There are no leading zeros in $ n $ . It's guaranteed that this situation is possible.

## 输出格式

Print the minimum number of digits in which the initial number and $ n $ can differ.

## 说明/提示

In the first example, the initial number could be $ 12 $ .

In the second example the sum of the digits of $ n $ is not less than $ k $ . The initial number could be equal to $ n $ .

## 样例 #1

### 输入

```
3
11

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
99

```

### 输出

```
0

```

