---
title: "Bill Total Value"
layout: "post"
diff: 普及/提高-
pid: CF727B
tag: []
---

# Bill Total Value

## 题目描述

Vasily exited from a store and now he wants to recheck the total price of all purchases in his bill. The bill is a string in which the names of the purchases and their prices are printed in a row without any spaces. Check has the format " $ name_{1}price_{1}name_{2}price_{2}...name_{n}price_{n} $ ", where $ name_{i} $ (name of the $ i $ -th purchase) is a non-empty string of length not more than $ 10 $ , consisting of lowercase English letters, and $ price_{i} $ (the price of the $ i $ -th purchase) is a non-empty string, consisting of digits and dots (decimal points). It is possible that purchases with equal names have different prices.

The price of each purchase is written in the following format. If the price is an integer number of dollars then cents are not written.

Otherwise, after the number of dollars a dot (decimal point) is written followed by cents in a two-digit format (if number of cents is between $ 1 $ and $ 9 $ inclusively, there is a leading zero).

Also, every three digits (from less significant to the most) in dollars are separated by dot (decimal point). No extra leading zeroes are allowed. The price always starts with a digit and ends with a digit.

For example:

- "234", "1.544", "149.431.10", "0.99" and "123.05" are valid prices,
- ".333", "3.33.11", "12.00", ".33", "0.1234" and "1.2" are not valid.

Write a program that will find the total price of all purchases in the given bill.

## 输入格式

The only line of the input contains a non-empty string $ s $ with length not greater than $ 1000 $ — the content of the bill.

It is guaranteed that the bill meets the format described above. It is guaranteed that each price in the bill is not less than one cent and not greater than $ 10^{6} $ dollars.

## 输出格式

Print the total price exactly in the same format as prices given in the input.

## 样例 #1

### 输入

```
chipsy48.32televizor12.390

```

### 输出

```
12.438.32

```

## 样例 #2

### 输入

```
a1b2c3.38

```

### 输出

```
6.38

```

## 样例 #3

### 输入

```
aa0.01t0.03

```

### 输出

```
0.04

```

