---
title: "Indecisive Taxi Fee"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1163F
tag: []
---

# Indecisive Taxi Fee

## 题目描述

In the city of Capypaland where Kuro and Shiro resides, there are $ n $ towns numbered from $ 1 $ to $ n $ and there are $ m $ bidirectional roads numbered from $ 1 $ to $ m $ connecting them. The $ i $ -th road connects towns $ u_i $ and $ v_i $ . Since traveling between the towns is quite difficult, the taxi industry is really popular here. To survive the harsh competition, each taxi company has to find a distinctive trait for their customers.

Kuro is the owner of a taxi company. He has decided to introduce a new fee model for his taxi brand, where the fee for each ride is not calculated based on the trip length, but on the sum of the prices of the roads traveled. The price for each of the $ m $ roads has been decided by Kuro himself.

As of now, the price for the road $ i $ is $ w_i $ and hence the fee for a taxi ride traveling through roads $ e_1, e_2, \ldots, e_k $ is $ \sum_{i=1}^k w_{e_i} $ .

However, Kuro himself is an indecisive person, so he has drafted $ q $ plans to change the road price. Each of the plans will be based on the original prices $ w_i $ , except for a single road $ t_j $ , the price of which is changed to $ x_j $ . Note, that the plans are independent of each other.

Shiro is a regular customer of the Kuro's taxi brand since she uses the taxi to travel from town $ 1 $ to town $ n $ every day. Since she's so a regular customer, Kuro decided to show her all his $ q $ plans before publishing them to the public. Now, Shiro wants to know the lowest fee she must pay to travel from the town $ 1 $ to the town $ n $ for each Kuro's plan.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ q $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le m, q \le 2 \cdot 10^5 $ ) — the number of towns, the number of roads, and the number of plans that Kuro has drafted respectively.

The $ i $ -th of the next $ m $ contains three integers $ u_i $ , $ v_i $ and $ w_i $ ( $ 1 \le u_i, v_i \le n $ , $ 1 \le w_i \le 10^9 $ , $ u_i \ne v_i $ ) — two endpoints and the original price of the $ i $ -th road.

It is guaranteed, that there is at least one way to travel from town $ 1 $ to town $ n $ using these $ m $ bidirectional roads.

Each of the next $ q $ lines contains two integers $ t_j $ and $ x_j $ ( $ 1 \leq t_j \leq m, 1 \leq x_j \leq 10^9 $ ) — the index of the road Kuro has planned to change and its new price respectively.

## 输出格式

Print $ q $ integers — the lowest fee Shiro must pay to get from town $ 1 $ to town $ n $ in each of those $ q $ plans.

## 说明/提示

In the first example, the original overview of Capypaland looks like this, where the number next to each road denotes the original prices of the roads,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163F/81d49c21b335c803aaed8b824c14712b78fe2d95.png)The overview of the first plan,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163F/06e604fe6cd3984de48ea91aaf7f60745f686fd0.png)The lowest fee Shiro must pay in this plan is $ 4 $ , which corresponds to the path $ 1 \rightarrow 4 $ .

The overview of the second plan,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163F/f16801fbc67919040dd394a0ecb93d766c247668.png)The lowest fee Shiro must pay in this plan is $ 2 $ , which corresponds to the path $ 1 \rightarrow 3 \rightarrow 4 $ .

The overview of the third plan,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163F/ccf55bd466d5967a1bb919d0ba5c59eea16e261e.png)The lowest fee Shiro must pay in this plan is $ 5 $ , which corresponds to the path $ 1 \rightarrow 2 \rightarrow 4 $ .

## 样例 #1

### 输入

```
4 5 6
1 2 2
2 4 3
1 4 7
1 3 1
3 4 5
3 4
5 1
3 8
1 4
2 1
3 1

```

### 输出

```
4
2
5
6
3
1

```

## 样例 #2

### 输入

```
2 4 4
1 2 2
1 2 3
1 2 4
1 2 5
2 1
3 2
4 3
1 5

```

### 输出

```
1
2
2
3

```

## 样例 #3

### 输入

```
2 1 1
1 2 1
1 3

```

### 输出

```
3

```

