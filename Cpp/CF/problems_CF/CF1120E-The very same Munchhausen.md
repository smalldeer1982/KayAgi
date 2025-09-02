---
title: "The very same Munchhausen"
layout: "post"
diff: 省选/NOI-
pid: CF1120E
tag: []
---

# The very same Munchhausen

## 题目描述

A positive integer $ a $ is given. Baron Munchausen claims that he knows such a positive integer $ n $ that if one multiplies $ n $ by $ a $ , the sum of its digits decreases $ a $ times. In other words, $ S(an) = S(n)/a $ , where $ S(x) $ denotes the sum of digits of the number $ x $ .

Find out if what Baron told can be true.

## 输入格式

The only line contains a single integer $ a $ ( $ 2 \le a \le 10^3 $ ).

## 输出格式

If there is no such number $ n $ , print $ -1 $ .

Otherwise print any appropriate positive integer $ n $ . Your number must not consist of more than $ 5\cdot10^5 $ digits. We can show that under given constraints either there is no answer, or there is an answer no longer than $ 5\cdot10^5 $ digits.

## 样例 #1

### 输入

```
2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3

```

### 输出

```
6669

```

## 样例 #3

### 输入

```
10

```

### 输出

```
-1

```

