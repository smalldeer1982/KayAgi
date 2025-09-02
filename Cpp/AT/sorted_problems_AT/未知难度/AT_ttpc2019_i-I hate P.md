---
title: "I hate P"
layout: "post"
diff: 难度0
pid: AT_ttpc2019_i
tag: []
---

# I hate P

## 题目描述

已知 $f(x)=\left\{\begin{matrix}
  f\left(\dfrac{x}{P}\right)&\text{if}\ x\equiv 0\pmod{P}  \\
  x&\text{otherwise}
\end{matrix}\right.$。求 $\text{ans}=\left(\prod\limits_{i=L}^{R}{f(i)}\right)\pmod{Q}$，$P,Q,L,R$ 给定。

## 输入格式

```
P Q
L R
```

## 输出格式

```
ans
```

## 样例 #1

### 输入

```
2 5
6 9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 3
57 61
```

### 输出

```
1
```

## 样例 #3

### 输入

```
65536 2
7 9
```

### 输出

```
0
```

## 样例 #4

### 输入

```
7878 78787
1234 56789
```

### 输出

```
14334
```

## 样例 #5

### 输入

```
2 4
1 81357343004
```

### 输出

```
1
```

