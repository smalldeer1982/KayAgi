---
title: "Mathematician Takeover"
layout: "post"
diff: 难度0
pid: CF1952G
tag: []
---

# Mathematician Takeover

## 题目描述

A mathematician grabbed my computer as I was preparing this problem, deleted the statement, and changed the samples to fit his liking. The model solution and input/output format are still correct, but the samples are wrong.

I've partially fixed the problem so that when you submit, it will be tested against the correct version of the problem. However, I can't fix the samples below. As a computer scientist, can you solve the correct problem?

## 输入格式

The only line of input contains a real number $ x $ ( $ 1 \leq x \leq 100 $ ), given to exactly three decimal places.

## 输出格式

Output one real number — the answer. Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-4} $ . Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is accepted if and only if $ \frac{|a-b|}{\max(1,|b|)} \le 10^{-4} $ .

## 样例 #1

### 输入

```
1.234
```

### 输出

```
0.21026
```

## 样例 #2

### 输入

```
4.113
```

### 输出

```
1.41415
```

## 样例 #3

### 输入

```
99.000
```

### 输出

```
4.59512
```

