---
title: "COPSEQH - Non Coprime Sequences(Hard)"
layout: "post"
diff: 难度0
pid: SP30961
tag: []
---

# COPSEQH - Non Coprime Sequences(Hard)

## 题目描述

Define **F(n,m)** to be the number of sequences of length **n** which satisfy:

- All elements of the sequence are positive divisors of **m**
- For any two adjacent elements, say p and q, there exists at least one prime which divides both of them.

You are given two integers, n and m. Find the values of **F(1,m), F(2,m), ... ,F(n,m)** modulo **10 $ ^{9} $ +7**

## 输入格式

The only line of input contains two integers, n and m.

   
#### Constraints

- 0 < n
- 0 < m

## 输出格式

Print the values of **F(1,m), F(2,m), ... , F(n,m)** modulo **10 $ ^{9} $ +7** in a single line separated by space.

## 样例 #1

### 输入

```
2 10
```

### 输出

```
4 7
```

