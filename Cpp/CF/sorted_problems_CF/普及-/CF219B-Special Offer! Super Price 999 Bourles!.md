---
title: "Special Offer! Super Price 999 Bourles!"
layout: "post"
diff: 普及-
pid: CF219B
tag: []
---

# Special Offer! Super Price 999 Bourles!

## 题目描述

Polycarpus is an amateur businessman. Recently he was surprised to find out that the market for paper scissors is completely free! Without further ado, Polycarpus decided to start producing and selling such scissors.

Polycaprus calculated that the optimal celling price for such scissors would be $ p $ bourles. However, he read somewhere that customers are attracted by prices that say something like "Special Offer! Super price 999 bourles!". So Polycarpus decided to lower the price a little if it leads to the desired effect.

Polycarpus agrees to lower the price by no more than $ d $ bourles so that the number of nines at the end of the resulting price is maximum. If there are several ways to do it, he chooses the maximum possible price.

Note, Polycarpus counts only the trailing nines in a price.

## 输入格式

The first line contains two integers $ p $ and $ d $ ( $ 1<=p<=10^{18} $ ; $ 0<=d&lt;p $ ) — the initial price of scissors and the maximum possible price reduction.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I64d specifier.

## 输出格式

Print the required price — the maximum price that ends with the largest number of nines and that is less than $ p $ by no more than $ d $ .

The required number shouldn't have leading zeroes.

## 样例 #1

### 输入

```
1029 102

```

### 输出

```
999

```

## 样例 #2

### 输入

```
27191 17

```

### 输出

```
27189

```

