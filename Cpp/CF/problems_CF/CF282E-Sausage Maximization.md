---
title: "Sausage Maximization"
layout: "post"
diff: 普及+/提高
pid: CF282E
tag: []
---

# Sausage Maximization

## 题目描述

The Bitlandians are quite weird people. They have their own problems and their own solutions. They have their own thoughts and their own beliefs, they have their own values and their own merits. They have their own dishes and their own sausages!

In Bitland a sausage is an array of integers! A sausage's deliciousness is equal to the bitwise excluding OR (the $ xor $ operation) of all integers in that sausage.

One day, when Mr. Bitkoch (the local cook) was going to close his BitRestaurant, BitHaval and BitAryo, the most famous citizens of Bitland, entered the restaurant and each ordered a sausage.

But Mr. Bitkoch had only one sausage left. So he decided to cut a prefix (several, may be zero, first array elements) of the sausage and give it to BitHaval and a postfix (several, may be zero, last array elements) of the sausage and give it to BitAryo. Note that one or both pieces of the sausage can be empty. Of course, the cut pieces mustn't intersect (no array element can occur in both pieces).

The pleasure of BitHaval and BitAryo is equal to the bitwise XOR of their sausages' deliciousness. An empty sausage's deliciousness equals zero.

Find a way to cut a piece of sausage for BitHaval and BitAryo that maximizes the pleasure of these worthy citizens.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{5} $ ).

The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (0<=a_{i}<=10^{12}) $ — Mr. Bitkoch's sausage.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 输出格式

Print a single integer — the maximum pleasure BitHaval and BitAryo can get from the dinner.

## 样例 #1

### 输入

```
2
1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 2 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
2
1000 1000

```

### 输出

```
1000

```

