---
title: "Ebony and Ivory"
layout: "post"
diff: 入门
pid: CF633A
tag: ['枚举']
---

# Ebony and Ivory

## 题目描述

Dante is engaged in a fight with "The Savior". Before he can fight it with his sword, he needs to break its shields. He has two guns, Ebony and Ivory, each of them is able to perform any non-negative number of shots.

For every bullet that hits the shield, Ebony deals $ a $ units of damage while Ivory deals $ b $ units of damage. In order to break the shield Dante has to deal exactly $ c $ units of damage. Find out if this is possible.

## 输入格式

The first line of the input contains three integers $ a $ , $ b $ , $ c $ ( $ 1<=a,b<=100,1<=c<=10000 $ ) — the number of units of damage dealt by Ebony gun and Ivory gun, and the total number of damage required to break the shield, respectively.

## 输出格式

Print "Yes" (without quotes) if Dante can deal exactly $ c $ damage to the shield and "No" (without quotes) otherwise.

## 说明/提示

In the second sample, Dante can fire $ 1 $ bullet from Ebony and $ 2 $ from Ivory to deal exactly $ 1·3+2·2=7 $ damage. In the third sample, Dante can fire $ 1 $ bullet from ebony and no bullets from ivory to do $ 1·6+0·11=6 $ damage.

## 样例 #1

### 输入

```
4 6 15

```

### 输出

```
No

```

## 样例 #2

### 输入

```
3 2 7

```

### 输出

```
Yes

```

## 样例 #3

### 输入

```
6 11 6

```

### 输出

```
Yes

```

