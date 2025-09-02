---
title: "Unnatural Conditions"
layout: "post"
diff: 普及+/提高
pid: CF1028B
tag: []
---

# Unnatural Conditions

## 题目描述

Let $ s(x) $ be sum of digits in decimal representation of positive integer $ x $ . Given two integers $ n $ and $ m $ , find some positive integers $ a $ and $ b $ such that

- $ s(a) \ge n $ ,
- $ s(b) \ge n $ ,
- $ s(a + b) \le m $ .

## 输入格式

The only line of input contain two integers $ n $ and $ m $ ( $ 1 \le n, m \le 1129 $ ).

## 输出格式

Print two lines, one for decimal representation of $ a $ and one for decimal representation of $ b $ . Both numbers must not contain leading zeros and must have length no more than $ 2230 $ .

## 说明/提示

In the first sample, we have $ n = 6 $ and $ m = 5 $ . One valid solution is $ a = 6 $ , $ b = 7 $ . Indeed, we have $ s(a) = 6 \ge n $ and $ s(b) = 7 \ge n $ , and also $ s(a + b) = s(13) = 4 \le m $ .

## 样例 #1

### 输入

```
6 5

```

### 输出

```
6 
7

```

## 样例 #2

### 输入

```
8 16

```

### 输出

```
35 
53

```

