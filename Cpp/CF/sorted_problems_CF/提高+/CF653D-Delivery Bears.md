---
title: "Delivery Bears"
layout: "post"
diff: 提高+/省选-
pid: CF653D
tag: []
---

# Delivery Bears

## 题目描述

Niwel is a little golden bear. As everyone knows, bears live in forests, but Niwel got tired of seeing all the trees so he decided to move to the city.

In the city, Niwel took on a job managing bears to deliver goods. The city that he lives in can be represented as a directed graph with $ n $ nodes and $ m $ edges. Each edge has a weight capacity. A delivery consists of a bear carrying weights with their bear hands on a simple path from node $ 1 $ to node $ n $ . The total weight that travels across a particular edge must not exceed the weight capacity of that edge.

Niwel has exactly $ x $ bears. In the interest of fairness, no bear can rest, and the weight that each bear carries must be exactly the same. However, each bear may take different paths if they like.

Niwel would like to determine, what is the maximum amount of weight he can deliver (it's the sum of weights carried by bears). Find the maximum weight.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ x $ ( $ 2<=n<=50 $ , $ 1<=m<=500 $ , $ 1<=x<=100000 $ ) — the number of nodes, the number of directed edges and the number of bears, respectively.

Each of the following $ m $ lines contains three integers $ a_{i} $ , $ b_{i} $ and $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ , $ 1<=c_{i}<=1000000 $ ). This represents a directed edge from node $ a_{i} $ to $ b_{i} $ with weight capacity $ c_{i} $ . There are no self loops and no multiple edges from one city to the other city. More formally, for each $ i $ and $ j $ that $ i≠j $ it's guaranteed that $ a_{i}≠a_{j} $ or $ b_{i}≠b_{j} $ . It is also guaranteed that there is at least one path from node 1 to node $ n $ .

## 输出格式

Print one real value on a single line — the maximum amount of weight Niwel can deliver if he uses exactly $ x $ bears. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF653D/c5d4f85807f95b08a3db7aae534822038a5bf1df.png).

## 说明/提示

In the first sample, Niwel has three bears. Two bears can choose the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF653D/4b21426951c2d0e6a3a42095e6d1b45a7f4622f3.png), while one bear can choose the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF653D/68a85f5b867b3c9f9afa90e0eb0708e14f1376a4.png). Even though the bear that goes on the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF653D/68a85f5b867b3c9f9afa90e0eb0708e14f1376a4.png) can carry one unit of weight, in the interest of fairness, he is restricted to carry 0.5 units of weight. Thus, the total weight is 1.5 units overall. Note that even though Niwel can deliver more weight with just 2 bears, he must use exactly 3 bears on this day.

## 样例 #1

### 输入

```
4 4 3
1 2 2
2 4 1
1 3 1
3 4 2

```

### 输出

```
1.5000000000

```

## 样例 #2

### 输入

```
5 11 23
1 2 3
2 3 4
3 4 5
4 5 6
1 3 4
2 4 5
3 5 6
1 4 2
2 5 3
1 5 2
3 2 30

```

### 输出

```
10.2222222222

```

