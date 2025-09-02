---
title: "Split it!"
layout: "post"
diff: 入门
pid: CF1496A
tag: []
---

# Split it!

## 题目描述

给出一个长度为 $n$ 的字符串 $s$，再给定一个参数 $k$。

问是否存在字符串 $a_1,a_2,...,a_{k+1}$，使得：

$$s=a_1+a_2+...+a_k+a_{k+1}+R(a_k)+...+R(a_2)+R(a_1)$$

如果存在，输出 `YES`；否则输出 `NO`。

上式中 $+$ 为字符串拼接，$R(a_i)$ 为 $a_i$ 的反串。

**本题多测。**

## 输入格式

第一行 $t$ 表示数据组数。

对于每组数据：

第一行 $n,k$ 如题所述，第二行一个字符串 $s$。

## 输出格式

共 $t$ 行，第 $i$ 行为第 $i$ 组数据。

对于第 $i$ 组数据，如果 $s$ 满足题意条件，输出 `YES`；否则输出 `NO`。

## 说明/提示

$1 \leq n \leq 100,0 \leq k \leq \left\lfloor\dfrac{n}{2}\right\rfloor$

## 样例 #1

### 输入

```
7
5 1
qwqwq
2 1
ab
3 1
ioi
4 2
icpc
22 0
dokidokiliteratureclub
19 8
imteamshanghaialice
6 3
aaaaaa
```

### 输出

```
YES
NO
YES
NO
YES
NO
NO
```

