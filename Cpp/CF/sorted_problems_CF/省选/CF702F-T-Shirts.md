---
title: "T-Shirts"
layout: "post"
diff: 省选/NOI-
pid: CF702F
tag: ['平衡树']
---

# T-Shirts

## 题目描述

The big consignment of t-shirts goes on sale in the shop before the beginning of the spring. In all $ n $ types of t-shirts go on sale. The t-shirt of the $ i $ -th type has two integer parameters — $ c_{i} $ and $ q_{i} $ , where $ c_{i} $ — is the price of the $ i $ -th type t-shirt, $ q_{i} $ — is the quality of the $ i $ -th type t-shirt. It should be assumed that the unlimited number of t-shirts of each type goes on sale in the shop, but in general the quality is not concerned with the price.

As predicted, $ k $ customers will come to the shop within the next month, the $ j $ -th customer will get ready to spend up to $ b_{j} $ on buying t-shirts.

All customers have the same strategy. First of all, the customer wants to buy the maximum possible number of the highest quality t-shirts, then to buy the maximum possible number of the highest quality t-shirts from residuary t-shirts and so on. At the same time among several same quality t-shirts the customer will buy one that is cheaper. The customers don't like the same t-shirts, so each customer will not buy more than one t-shirt of one type.

Determine the number of t-shirts which each customer will buy, if they use the described strategy. All customers act independently from each other, and the purchase of one does not affect the purchase of another.

## 输入格式

The first line contains the positive integer $ n $ ( $ 1<=n<=2·10^{5} $ ) — the number of t-shirt types.

Each of the following $ n $ lines contains two integers $ c_{i} $ and $ q_{i} $ ( $ 1<=c_{i},q_{i}<=10^{9} $ ) — the price and the quality of the $ i $ -th type t-shirt.

The next line contains the positive integer $ k $ ( $ 1<=k<=2·10^{5} $ ) — the number of the customers.

The next line contains $ k $ positive integers $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{j}<=10^{9} $ ), where the $ j $ -th number is equal to the sum, which the $ j $ -th customer gets ready to spend on t-shirts.

## 输出格式

The first line of the input data should contain the sequence of $ k $ integers, where the $ i $ -th number should be equal to the number of t-shirts, which the $ i $ -th customer will buy.

## 说明/提示

In the first example the first customer will buy the t-shirt of the second type, then the t-shirt of the first type. He will spend 10 and will not be able to buy the t-shirt of the third type because it costs 4, and the customer will owe only 3. The second customer will buy all three t-shirts (at first, the t-shirt of the second type, then the t-shirt of the first type, and then the t-shirt of the third type). He will spend all money on it.

## 样例 #1

### 输入

```
3
7 5
3 5
4 3
2
13 14

```

### 输出

```
2 3 

```

## 样例 #2

### 输入

```
2
100 500
50 499
4
50 200 150 100

```

### 输出

```
1 2 2 1 

```

