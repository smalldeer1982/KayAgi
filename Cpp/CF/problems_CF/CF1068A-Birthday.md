---
title: "Birthday"
layout: "post"
diff: 普及+/提高
pid: CF1068A
tag: []
---

# Birthday

## 题目描述

Ivan is collecting coins. There are only $ N $ different collectible coins, Ivan has $ K $ of them. He will be celebrating his birthday soon, so all his $ M $ freinds decided to gift him coins. They all agreed to three terms:

- Everyone must gift as many coins as others.
- All coins given to Ivan must be different.
- Not less than $ L $ coins from gifts altogether, must be new in Ivan's collection.

But his friends don't know which coins have Ivan already got in his collection. They don't want to spend money so they want to buy minimum quantity of coins, that satisfy all terms, irrespective of the Ivan's collection. Help them to find this minimum number of coins or define it's not possible to meet all the terms.

## 输入格式

The only line of input contains 4 integers $ N $ , $ M $ , $ K $ , $ L $ ( $ 1 \le K \le N \le 10^{18} $ ; $ 1 \le M, \,\, L \le 10^{18} $ ) — quantity of different coins, number of Ivan's friends, size of Ivan's collection and quantity of coins, that must be new in Ivan's collection.

## 输出格式

Print one number — minimal number of coins one friend can gift to satisfy all the conditions. If it is impossible to satisfy all three conditions print "-1" (without quotes).

## 说明/提示

In the first test, one coin from each friend is enough, as he will be presented with 15 different coins and 13 of them will definitely be new.

In the second test, Ivan has 11 friends, but there are only 10 different coins. So all friends can't present him different coins.

## 样例 #1

### 输入

```
20 15 2 3

```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 11 2 4

```

### 输出

```
-1
```

