---
title: "PT07C - The GbAaY Kingdom"
layout: "post"
diff: 省选/NOI-
pid: SP1479
tag: ['最短路', '生成树', '树的直径']
---

# PT07C - The GbAaY Kingdom

## 题目描述

给定一个 $n$ 个点 $m$ 条边的带权无向图.

现求一生成树,使得任意两结点间最长距离(直径)最短.

## 输入格式

输入的第一行包含两个正整数 $n,m (1 \le n \le 200,n - 1 \le m \le 20000)$ ,代表点数和边数.

接下来 $m$ 行每行三个正整数 $u,v,w$,代表一条从 $u$ 连向 $v$ 边权为 $w$,保证 $u \ne v,1 \le w \le 10^5$

## 输出格式

输出第一行包含一个整数，表示生成树直径.

接下来输出 $n - 1$ 行,每行两个数代表生成树的一条边.

如果有多解,输出任意一个.

### 输入输出样例


#### 输入 #1

```
3 3
1 2 1
2 3 1
1 3 1
```

#### 输出 #1

```
2
1 2
1 3
```

## 样例 #1

### 输入

```
3 3

1 2 1

2 3 1

1 3 1
```

### 输出

```
2

1 2

1 3
```



---

---
title: "INGRED - Ingredients"
layout: "post"
diff: 省选/NOI-
pid: SP18187
tag: ['最短路', '进制', '队列']
---

# INGRED - Ingredients

## 题目描述

 You are given **n** cities with **m** bi-directional roads connecting them and the length of each road. There are two friends living in different cities who wish to collect some ingredients available at different stores to make cake. There are s such stores. They need not come back home after purchasing the ingredients. Petrol is expensive and they would hence like to travel minimum total distance (sum of distance distance traveled by both kids). Help them find out what this distance is.



---

