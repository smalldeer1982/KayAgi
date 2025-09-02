---
title: "Continued Fractions"
layout: "post"
diff: 普及+/提高
pid: CF305B
tag: []
---

# Continued Fractions

## 题目描述

A continued fraction of height $ n $ is a fraction of form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/19ade84928d3d628a6e212b03adbbf8bc0856736.png). You are given two rational numbers, one is represented as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/ae456f9650d5b3ca46e54c303d07fec088f6ad5e.png) and the other one is represented as a finite fraction of height $ n $ . Check if they are equal.

## 输入格式

The first line contains two space-separated integers $ p,q $ $ (1<=q<=p<=10^{18}) $ — the numerator and the denominator of the first fraction.

The second line contains integer $ n $ $ (1<=n<=90) $ — the height of the second fraction. The third line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{18}) $ — the continued fraction.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 输出格式

Print "YES" if these fractions are equal and "NO" otherwise.

## 说明/提示

In the first sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/a7429bd0927ab226e00de904e1ba240c58b09318.png).

In the second sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/a01a984749367ddde5131c663127bc347e31f0a2.png).

In the third sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/4db9464841d1b99996f6c98f75df85058aee123f.png).

## 样例 #1

### 输入

```
9 4
2
2 4

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
9 4
3
2 3 1

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
9 4
3
1 2 4

```

### 输出

```
NO

```

