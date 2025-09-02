---
title: "Cycle Palindrome"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1656G
tag: []
---

# Cycle Palindrome

## 题目描述

### 【前置定义】

1. 回文数列：如果一个长度为 $n$ 的数列 $a_{1\cdots n}$ 满足 $\forall i \in [1,n], a_{i}=a_{n-i+1}$，则称 $a_{1 \cdots n}$ 是回文的。
2. 循环数列：如果一个长度为 $n$ 的数列 $b_{1 \cdots n}$ 满足 $\{ 1,b(1),b^{2}(1),b^3(1) \cdots b^{n-1}(1)\}$ 两两不同，则称 $b_{1 \cdots n}$ 是循环数列。其中 $b^{m}(1)=\underbrace{b(b(\cdots b}_{m \ \text{times}}(1)\cdots))$，如 $b^{2}(1)=b(b(1))$。
3. 排列：对于一个长度为 $n$ 的数列 $c_{1 \dots n}$，如果 $1,2,3,\cdots,n$ 中的每一个数字**都**在 $c_{1 \cdots n}$ **恰好**只出现 $1$ 次，则称 $c_{1 \cdots n}$ 是一个长度为 $n$ 的排列。


给定一个长度为 $n$ 的数列 $a_{1 \cdots n}$，你需要找到一个**循环数列** $b_{1 \cdots n}$ 使得数列 $\{ a_{b_{1}},a_{b_{2}},a_{b_{3}}, \cdots,a_{b_{n}} \}$ 是一个**回文数列**且 $b$ 是一个长度为 $n$ 的**排列**。

## 输入格式

**多组数据**。

第一行输入一个整数 $T$，表示测试点数目。

对于每个测试点：

- 第一行一个整数 $n$，表示数列长度。
- 第二行 $n$ 个整数，表示 $a_{1 \cdots n}$。

## 输出格式

对于每个测试点，如果存在这样的循环数列 $b_{1\cdots n}$，则输出两行：第一行输出一个 `YES`，第二行输出 $b_{1 \cdots n}$。如果有多个 $b_{1 \cdots n}$，输出任意一个即可。

如果不存在这样的 $b_{1 \cdots n}$，则只输出一行，输出 `NO`。

## 说明/提示

- $1 \leq T \leq 3 \times 10^{4}$。
- $1 \leq n \leq 2 \times 10^{5},1 \leq \sum n \leq 2 \times 10^{5}$。
- $\forall i \in [1,n], \quad 1 \leq a_{i} \leq n$。

Translated by @HPXXZYY

## 样例 #1

### 输入

```
3
4
1 2 2 1
3
1 2 1
7
1 3 3 3 1 2 2
```

### 输出

```
YES
3 1 4 2 
NO
YES
5 3 7 2 6 4 1
```

