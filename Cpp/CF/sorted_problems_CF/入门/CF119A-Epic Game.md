---
title: "Epic Game"
layout: "post"
diff: 入门
pid: CF119A
tag: ['模拟', '最大公约数 gcd']
---

# Epic Game

## 题目描述

Simon和Antisimon在玩石子游戏。

共有n颗石子，Simon先拿。

Simon能拿当前n和a的最大公约数，Antisimon能拿当前n和b的最大公约数。

当有一个人不能拿时（n=0）那个人就输了。

求谁赢了。

## 输入格式

一行，a，b，n（1<=a,b,n<=100）

## 输出格式

一行，如果Simon赢了，输出0；Antisimon赢了，输出1.

## 说明/提示

gcd(0,x)=gcd(x,0)=x;

对于样例1：

Simon拿gcd(3,9)=3颗

Antisimon拿gcd(5,6)=1颗

Simon拿gcd(3,5)=1颗

Antisimon拿gcd(5,4)=1颗

Simon拿gcd(3,3)=3颗

Antisimon输了

感谢@引领天下 提供的翻译

## 样例 #1

### 输入

```
3 5 9

```

### 输出

```
0
```

## 样例 #2

### 输入

```
1 1 100

```

### 输出

```
1
```

