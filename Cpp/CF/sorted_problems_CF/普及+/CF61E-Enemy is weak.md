---
title: "Enemy is weak"
layout: "post"
diff: 普及+/提高
pid: CF61E
tag: []
---

# Enemy is weak

## 题目描述

The Romans have attacked again. This time they are much more than the Persians but Shapur is ready to defeat them. He says: "A lion is never afraid of a hundred sheep".

Nevertheless Shapur has to find weaknesses in the Roman army to defeat them. So he gives the army a weakness number.

In Shapur's opinion the weakness of an army is equal to the number of triplets $ i,j,k $ such that $ i&lt;j&lt;k $ and $ a_{i}&gt;a_{j}&gt;a_{k} $ where $ a_{x} $ is the power of man standing at position $ x $ . The Roman army has one special trait — powers of all the people in it are distinct.

Help Shapur find out how weak the Romans are.

## 输入格式

The first line of input contains a single number $ n $ ( $ 3<=n<=10^{6} $ ) — the number of men in Roman army. Next line contains $ n $ different positive integers $ a_{i} $ ( $ 1<=i<=n,1<=a_{i}<=10^{9} $ ) — powers of men in the Roman army.

## 输出格式

A single integer number, the weakness of the Roman army.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cout (also you may use %I64d).

## 样例 #1

### 输入

```
3
3 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
2 3 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4
10 8 3 1

```

### 输出

```
4

```

## 样例 #4

### 输入

```
4
1 5 4 3

```

### 输出

```
1

```

