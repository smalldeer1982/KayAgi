---
title: "Bracket Insertion"
layout: "post"
diff: 省选/NOI-
pid: CF1781F
tag: ['动态规划 DP', '组合数学', '前缀和', '概率论']
---

# Bracket Insertion

## 题目描述

Vika likes playing with bracket sequences. Today she wants to create a new bracket sequence using the following algorithm. Initially, Vika's sequence is an empty string, and then she will repeat the following actions $ n $ times:

- Choose a place in the current bracket sequence to insert new brackets uniformly at random. If the length of the current sequence is $ k $ , then there are $ k+1 $ such places: before the first bracket, between the first and the second brackets, $ \ldots $ , after the $ k $ -th bracket. In particular, there is one such place in an empty bracket sequence.
- Choose string "()" with probability $ p $ or string ")(" with probability $ 1 - p $ and insert it into the chosen place. The length of the bracket sequence will increase by $ 2 $ .

A bracket sequence is called regular if it is possible to obtain a correct arithmetic expression by inserting characters '+' and '1' into it. For example, sequences "(())()", "()", and "(()(()))" are regular, while ")(", "(()", and "(()))(" are not.

Vika wants to know the probability that her bracket sequence will be a regular one at the end. Help her and find this probability modulo $ 998\,244\,353 $ (see Output section).

## 输入格式

The only line contains two integers $ n $ and $ q $ ( $ 1 \le n \le 500 $ ; $ 0 \le q \le 10^4 $ ). Here $ n $ is equal to the number of bracket insertion operations, and the probability that Vika chooses string "()" on every step of the algorithm is equal to $ p = q \cdot 10^{-4} $ .

## 输出格式

Print the probability that Vika's final bracket sequence will be regular, modulo $ 998\,244\,353 $ .

Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first example, Vika will get a regular bracket sequence () with probability $ p = \frac{3}{4} $ , and she will get an irregular bracket sequence )( with probability $ 1 - p = \frac{1}{4} $ . The sought probability is $ \frac{3}{4} $ , and $ 249\,561\,089 \cdot 4 \equiv 3 \pmod{998\,244\,353} $ .

In the second example, the sought probability is $ \frac{11}{25} $ .

## 样例 #1

### 输入

```
1 7500
```

### 输出

```
249561089
```

## 样例 #2

### 输入

```
2 6000
```

### 输出

```
519087064
```

## 样例 #3

### 输入

```
5 4000
```

### 输出

```
119387743
```

