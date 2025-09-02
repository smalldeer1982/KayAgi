---
title: "Hamming Distance Sum"
layout: "post"
diff: 普及/提高-
pid: CF608B
tag: []
---

# Hamming Distance Sum

## 题目描述

吉诺斯需要你的帮助。他被要求完成塞塔玛出的如下编程问题：  
  
  字符串 s 的长度被表示为 $\left|s\right|$。两个等长字符串 s 和 t 之间的“Hamming”距离被定义为 $\sum\limits_{i=1}^{\left|s\right|}\left|s_i-t_i\right|$，其中，$s_i$ 是字符串 s 的第 i 个字符，$t_i$ 是字符串 t 的第 i 个字符。  
  
  比如说，字符串“0011”和字符串“0110”之间的“Hamming”距离为 $\left|0-0\right|+\left|0-1\right|+\left|1-1\right|+\left|1-0\right|=0+1+0+1=2$。
  
  给定两个字符串 a 和 b，找到字符串 a 和所有字符串 b 的长度为 $\left|a\right|$ 的子串之间的“Hamming”距离总和。

## 输入格式

第一行输入二进制字符串 a（$1\leqslant\left|a\right|\leqslant200000$）。  
  
  第二行输入二进制字符串 b（$\left|a\right|\leqslant\left|b\right|\leqslant200000$）。  
  
  两个字符串均只包含字符“0”和“1”。

## 输出格式

输出一个整数，即字符串 a 和所有字符串 b 的长度为 $\left|a\right|$ 的子串之间的“Hamming”距离总和。

## 样例 #1

### 输入

```
01
00111

```

### 输出

```
3

```

## 样例 #2

### 输入

```
0011
0110

```

### 输出

```
2

```

