---
title: "Kalila and Dimna in the Logging Industry"
layout: "post"
diff: 提高+/省选-
pid: CF319C
tag: []
---

# Kalila and Dimna in the Logging Industry

## 题目描述

Kalila and Dimna are two jackals living in a huge jungle. One day they decided to join a logging factory in order to make money.

The manager of logging factory wants them to go to the jungle and cut $ n $ trees with heights $ a_{1},a_{2},...,a_{n} $ . They bought a chain saw from a shop. Each time they use the chain saw on the tree number $ i $ , they can decrease the height of this tree by one unit. Each time that Kalila and Dimna use the chain saw, they need to recharge it. Cost of charging depends on the id of the trees which have been cut completely (a tree is cut completely if its height equal to 0). If the maximum id of a tree which has been cut completely is $ i $ (the tree that have height $ a_{i} $ in the beginning), then the cost of charging the chain saw would be $ b_{i} $ . If no tree is cut completely, Kalila and Dimna cannot charge the chain saw. The chainsaw is charged in the beginning. We know that for each $ i $ < $ j $ , $ a_{i}&lt;a_{j} $ and $ b_{i}&gt;b_{j} $ and also $ b_{n}=0 $ and $ a_{1}=1 $ . Kalila and Dimna want to cut all the trees completely, with minimum cost.

They want you to help them! Will you?

## 输入格式

The first line of input contains an integer $ n $ ( $ 1<=n<=10^{5} $ ). The second line of input contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ). The third line of input contains $ n $ integers $ b_{1},b_{2},...,b_{n} $ ( $ 0<=b_{i}<=10^{9} $ ).

It's guaranteed that $ a_{1}=1 $ , $ b_{n}=0 $ , $ a_{1}&lt;a_{2}&lt;...&lt;a_{n} $ and $ b_{1}&gt;b_{2}&gt;...&gt;b_{n} $ .

## 输出格式

The only line of output must contain the minimum cost of cutting all the trees completely.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
5
1 2 3 4 5
5 4 3 2 0

```

### 输出

```
25

```

## 样例 #2

### 输入

```
6
1 2 3 10 20 30
6 5 4 3 2 0

```

### 输出

```
138

```

