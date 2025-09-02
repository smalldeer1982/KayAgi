---
title: "Nezzar and Chocolate Bars"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1477F
tag: []
---

# Nezzar and Chocolate Bars

## 题目描述

Nezzar buys his favorite snack — $ n $ chocolate bars with lengths $ l_1,l_2,\ldots,l_n $ . However, chocolate bars might be too long to store them properly!

In order to solve this problem, Nezzar designs an interesting process to divide them into small pieces. Firstly, Nezzar puts all his chocolate bars into a black box. Then, he will perform the following operation repeatedly until the maximum length over all chocolate bars does not exceed $ k $ .

- Nezzar picks a chocolate bar from the box with probability proportional to its length $ x $ .
- After step $ 1 $ , Nezzar uniformly picks a real number $ r \in (0,x) $ and divides the chosen chocolate bar into two chocolate bars with lengths $ r $ and $ x-r $ .
- Lastly, he puts those two new chocolate bars into the black box.

Nezzar now wonders, what is the expected number of operations he will perform to divide his chocolate bars into small pieces.

It can be shown that the answer can be represented as $ \frac{P}{Q} $ , where $ P $ and $ Q $ are coprime integers and $ Q \not \equiv 0 $ ( $ \bmod 998\,244\,353 $ ). Print the value of $ P\cdot Q^{-1} \mod 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 50, 1 \le k \le 2000 $ ).

The second line contains $ n $ integers $ l_1, l_2, \ldots, l_n $ ( $ 1 \le l_i $ , $ \sum_{i=1}^{n} l_i \le 2000 $ ).

## 输出格式

Print a single integer — the expected number of operations Nezzar will perform to divide his chocolate bars into small pieces modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
1 1
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
1 1
1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
1 5
1234
```

### 输出

```
15630811
```

## 样例 #4

### 输入

```
2 1
2 3
```

### 输出

```
476014684
```

## 样例 #5

### 输入

```
10 33
10 20 30 40 50 60 70 80 90 100
```

### 输出

```
675105648
```

