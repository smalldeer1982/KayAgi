---
title: "Rat Kwesh and Cheese"
layout: "post"
diff: 提高+/省选-
pid: CF621D
tag: []
---

# Rat Kwesh and Cheese

## 题目描述

Wet Shark asked Rat Kwesh to generate three positive real numbers $ x $ , $ y $ and $ z $ , from $ 0.1 $ to $ 200.0 $ , inclusive. Wet Krash wants to impress Wet Shark, so all generated numbers will have exactly one digit after the decimal point.

Wet Shark knows Rat Kwesh will want a lot of cheese. So he will give the Rat an opportunity to earn a lot of cheese. He will hand the three numbers $ x $ , $ y $ and $ z $ to Rat Kwesh, and Rat Kwesh will pick one of the these twelve options:

1. $a_1=x^{y^z}$；
2. $a_2=x^{z^y}$；
3. $a_3=(x^y)^z$；
4. $a_4=(x^z)^y$；
5. $a_5=y^{x^z}$；
6. $a_6=y^{z^x}$；
7. $a_7=(y^x)^z$；
8. $a_8=(y^z)^x$；
9. $a_9=z^{x^y}$；
10. $a_{10}=z^{y^x}$；
11. $a_{11}=(z^x)^y$；
12. $a_{12}=(z^y)^x$。

Let $ m $ be the maximum of all the $ a_{i} $ , and $ c $ be the smallest index (from $ 1 $ to $ 12 $ ) such that $ a_{c}=m $ . Rat's goal is to find that $ c $ , and he asks you to help him. Rat Kwesh wants to see how much cheese he gets, so he you will have to print the expression corresponding to that $ a_{c} $ .

## 输入格式

The only line of the input contains three space-separated real numbers $ x $ , $ y $ and $ z $ ( $ 0.1<=x,y,z<=200.0 $ ). Each of $ x $ , $ y $ and $ z $ is given with exactly one digit after the decimal point.

## 输出格式

Find the maximum value of expression among $ x^{y^z} $ , $ x^{z^y} $ , $ (x^{y})^{z} $ , $ (x^{z})^{y} $ , $ y^{x^z} $ , $ y^{z^x} $ , $ (y^{x})^{z} $ , $ (y^{z})^{x} $ , $ z^{x^y} $ , $ z^{y^x} $ , $ (z^{x})^{y} $ , $ (z^{y})^{x} $ and print the corresponding expression. If there are many maximums, print the one that comes first in the list.

 $ x^{y^z} $ should be outputted as x^y^z (without brackets), and $ (x^{y})^{z} $ should be outputted as (x^y)^z (quotes for clarity).

## 样例 #1

### 输入

```
1.1 3.4 2.5

```

### 输出

```
z^y^x

```

## 样例 #2

### 输入

```
2.0 2.0 2.0

```

### 输出

```
x^y^z

```

## 样例 #3

### 输入

```
1.9 1.8 1.7

```

### 输出

```
(x^y)^z

```

