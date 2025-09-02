---
title: "Tourist Problem"
layout: "post"
diff: 普及/提高-
pid: CF340C
tag: []
---

# Tourist Problem

## 题目描述

Iahub is a big fan of tourists. He wants to become a tourist himself, so he planned a trip. There are $ n $ destinations on a straight road that Iahub wants to visit. Iahub starts the excursion from kilometer 0. The $ n $ destinations are described by a non-negative integers sequence $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . The number $ a_{k} $ represents that the $ k $ th destination is at distance $ a_{k} $ kilometers from the starting point. No two destinations are located in the same place.

Iahub wants to visit each destination only once. Note that, crossing through a destination is not considered visiting, unless Iahub explicitly wants to visit it at that point. Also, after Iahub visits his last destination, he doesn't come back to kilometer 0, as he stops his trip at the last destination.

The distance between destination located at kilometer $ x $ and next destination, located at kilometer $ y $ , is $ |x-y| $ kilometers. We call a "route" an order of visiting the destinations. Iahub can visit destinations in any order he wants, as long as he visits all $ n $ destinations and he doesn't visit a destination more than once.

Iahub starts writing out on a paper all possible routes and for each of them, he notes the total distance he would walk. He's interested in the average number of kilometers he would walk by choosing a route. As he got bored of writing out all the routes, he asks you to help him.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=10^{5} $ ). Next line contains $ n $ distinct integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{7} $ ).

## 输出格式

Output two integers — the numerator and denominator of a fraction which is equal to the wanted average number. The fraction must be irreducible.

## 说明/提示

Consider 6 possible routes:

- \[2, 3, 5\]: total distance traveled: |2 – 0| + |3 – 2| + |5 – 3| = 5;
- \[2, 5, 3\]: |2 – 0| + |5 – 2| + |3 – 5| = 7;
- \[3, 2, 5\]: |3 – 0| + |2 – 3| + |5 – 2| = 7;
- \[3, 5, 2\]: |3 – 0| + |5 – 3| + |2 – 5| = 8;
- \[5, 2, 3\]: |5 – 0| + |2 – 5| + |3 – 2| = 9;
- \[5, 3, 2\]: |5 – 0| + |3 – 5| + |2 – 3| = 8.

The average travel distance is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF340C/46abd0367bb1ab89fd9e16a66d93ae130f1cb4b6.png) = ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF340C/3ee5b4e2d0bb159e64987b0886cc8a870c2084a7.png) = ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF340C/1d6a962c150afd1c2b26fd73c34a41806e6a93af.png).

## 样例 #1

### 输入

```
3
2 3 5

```

### 输出

```
22 3
```

