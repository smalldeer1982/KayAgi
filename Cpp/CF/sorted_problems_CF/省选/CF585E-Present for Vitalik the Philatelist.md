---
title: "Present for Vitalik the Philatelist"
layout: "post"
diff: 省选/NOI-
pid: CF585E
tag: []
---

# Present for Vitalik the Philatelist

## 题目描述

Vitalik the philatelist has a birthday today!

As he is a regular customer in a stamp store called 'Robin Bobin', the store management decided to make him a gift.

Vitalik wants to buy one stamp and the store will give him a non-empty set of the remaining stamps, such that the greatest common divisor (GCD) of the price of the stamps they give to him is more than one. If the GCD of prices of the purchased stamp and prices of present stamps set will be equal to $ 1 $ , then Vitalik will leave the store completely happy.

The store management asks you to count the number of different situations in which Vitalik will leave the store completely happy. Since the required number of situations can be very large, you need to find the remainder of this number modulo $ 10^{9}+7 $ . The situations are different if the stamps purchased by Vitalik are different, or if one of the present sets contains a stamp that the other present does not contain.

## 输入格式

The first line of the input contains integer $ n $ ( $ 2<=n<=5·10^{5} $ ) — the number of distinct stamps, available for sale in the 'Robin Bobin' store.

The second line contains a sequence of integers $ a_{1},a_{2},...,a_{n} $ ( $ 2<=a_{i}<=10^{7} $ ), where $ a_{i} $ is the price of the $ i $ -th stamp.

## 输出格式

Print a single integer — the remainder of the sought number of situations modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample the following situations are possible:

- Vitalik buys the 1-st stamp, the store gives him the 2-nd stamp as a present;
- Vitalik buys the 3-rd stamp, the store gives him the 2-nd stamp as a present;
- Vitalik buys the 2-nd stamp, the store gives him the 1-st stamp as a present;
- Vitalik buys the 2-nd stamp, the store gives him the 3-rd stamp as a present;
- Vitalik buys the 2-nd stamp, the store gives him the 1-st and 3-rd stamps as a present.

## 样例 #1

### 输入

```
3
2 3 2

```

### 输出

```
5

```

## 样例 #2

### 输入

```
2
9 6

```

### 输出

```
0

```

