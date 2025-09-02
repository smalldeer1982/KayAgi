---
title: "Modular Stability"
layout: "post"
diff: 提高+/省选-
pid: CF1359E
tag: []
---

# Modular Stability

## 题目描述

求有多少个长度为 $k$ 的序列 $a$，满足以下条件：

- $\forall 1 \le i < k,a_i < a_{i+1}$
- $\forall 1 \le i \le k,1 \le a_i \le n$
- 对于任意一个 $1$ 至 $k$ 的排列 $p$，满足 $( (((x \bmod a_1)\bmod a_2)\bmod a_3)\bmod \cdots \bmod a_k) = ((((x \bmod a_{p_1})\bmod a_{p_2})\bmod a_{p_3} \bmod \cdots \bmod a_{p_k}$。其中 $x$ 为任意非负整数。

结果对 $998,244,353$ 取模。

## 输出格式

输出一个整数表示答案。

## 说明/提示

$1 \le n,k \le 5 \times 10^5$。

## 样例 #1

### 输入

```
7 3
```

### 输出

```
16
```

## 样例 #2

### 输入

```
3 7
```

### 输出

```
0
```

## 样例 #3

### 输入

```
1337 42
```

### 输出

```
95147305
```

## 样例 #4

### 输入

```
1 1
```

### 输出

```
1
```

## 样例 #5

### 输入

```
500000 1
```

### 输出

```
500000
```

