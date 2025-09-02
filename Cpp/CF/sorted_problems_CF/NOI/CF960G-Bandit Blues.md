---
title: "Bandit Blues"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF960G
tag: []
---

# Bandit Blues

## 题目描述

Japate, while traveling through the forest of Mala, saw $ N $ bags of gold lying in a row. Each bag has some distinct weight of gold between $ 1 $ to $ N $ . Japate can carry only one bag of gold with him, so he uses the following strategy to choose a bag.

Initially, he starts with an empty bag (zero weight). He considers the bags in some order. If the current bag has a higher weight than the bag in his hand, he picks the current bag.

Japate put the bags in some order. Japate realizes that he will pick $ A $ bags, if he starts picking bags from the front, and will pick $ B $ bags, if he starts picking bags from the back. By picking we mean replacing the bag in his hand with the current one.

Now he wonders how many permutations of bags are possible, in which he picks $ A $ bags from the front and $ B $ bags from back using the above strategy.

Since the answer can be very large, output it modulo $ 998244353 $ .

## 输入格式

The only line of input contains three space separated integers $ N $ ( $ 1<=N<=10^{5} $ ), $ A $ and $ B $ ( $ 0<=A,B<=N $ ).

## 输出格式

Output a single integer — the number of valid permutations modulo $ 998244353 $ .

## 说明/提示

In sample case $ 1 $ , the only possible permutation is $ [1] $

In sample cases $ 2 $ and $ 3 $ , only two permutations of size $ 2 $ are possible: $ {[1,2],[2,1]} $ . The values of $ a $ and $ b $ for first permutation is $ 2 $ and $ 1 $ , and for the second permutation these values are $ 1 $ and $ 2 $ .

In sample case $ 4 $ , out of 120 permutations of $ [1,2,3,4,5] $ possible, only 22 satisfy the given constraints of $ a $ and $ b $ .

## 样例 #1

### 输入

```
1 1 1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 1 1

```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 2 1

```

### 输出

```
1
```

## 样例 #4

### 输入

```
5 2 2

```

### 输出

```
22
```

