---
title: "Hexadecimal Digits of an Integral"
layout: "post"
diff: 难度0
pid: UVA11302
tag: []
---

# Hexadecimal Digits of an Integral

## 题目描述

求下面式子

$$\left(\int_0^136\left(\prod_{k=1}^{\infty}\frac{2}{\sqrt[2^k]{2}+1}\right)^2-48(x+1)^{-1}\sum_{k=0}^\infty\frac{(-1)^k}{k+1}x^{2k+2}\mathrm dx\right)^{1/2}$$

的十六进制表示法的的第 $k$ 位。例如，假若答案是 $(\overline{n_1.n_2n_3n_4\cdots n_k\cdots})_{\mathrm{HEX}}$，那么你需要给出 $n_k$。

## 输入格式

多组数据。至多 $50$ 组。每组数据包含一个整数 $k(k\le 10^6+1)$。

## 输出格式

对于每行输入，给出一个十六进制数位，即为答案。

## 样例 #1

### 输入

```
100
200
```

### 输出

```
A
4
```

