---
title: "Hot Black Hot White"
layout: "post"
diff: 普及+/提高
pid: CF1725H
tag: []
---

# Hot Black Hot White

## 题目描述

#### 题目大意
Dr. Chanek 有 $n$ 块魔法石，编号为 $1$ 至 $n$。第 Dr. Chanek 有 $n$ 块魔法石，编号为 $1$ 至 $n$。第 $i$ 块魔法石拥有 $a_i$ 的力量。Dr. Chanek 需要将 $n$ 块魔法石中的 $\frac{n}{2}$ 块染成黑色，另外 $\frac{n}{2}$ 块染成白色。

当第 $i$ 块魔法石和第 $j$ 块魔法石同时满足以下两个条件时，它们就会发生反应：

1. $color_i \ne color_j$（即两块石头颜色不同）

2. $\text{concat}(a_i,a_j) \times \text{concat}(a_j,a_i) + a_i \times a_j \equiv Z \mod 3$（即 $(\text{concat}(a_i,a_j) \times \text{concat}(a_j,a_i) + a_i \times a_j) \mod 3 = Z \mod 3$）

其中 $\text{concat}(x,y)$ 表示将十进制下的 $x$ 接在十进制下的 $y$ 的左边形成的新十进制数。例如，$\text{concat}(10,24) = 1024$。

因为魔法石发生反应时会很热很危险，所以你需要确定 $Z$ 的值和魔法石的染色方案，使任意一对魔法石之间都不产生反应。

## 输入格式

第一行，一个正整数 $n(2 \leq n \leq 10^5)$。

第二行，$n$ 个正整数，第 $i$ 个数表示 $a_i$。

## 输出格式

如果不存在使魔法石不会发生反应的 $Z$ 和 染色方案，直接输出 $-1$。

否则，第一行，输出一个数 $Z$。

第二行，输出一个长度为 $n$ 的字符串 $s$。其中，$s_i = 0$ 表示第 $i$ 块魔法石染成黑色，$s_i = 1$ 表示第 $i$ 块魔法石染成白色。

（Translated by @[owo_ImposterAnYu_owo](https://www.luogu.com.cn/user/510555)）

## 样例 #1

### 输入

```
4
4 10 9 14
```

### 输出

```
0
1001
```

