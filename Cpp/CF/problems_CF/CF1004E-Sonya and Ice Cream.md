---
title: "Sonya and Ice Cream"
layout: "post"
diff: 省选/NOI-
pid: CF1004E
tag: []
---

# Sonya and Ice Cream

## 题目描述

Sonya likes ice cream very much. She eats it even during programming competitions. That is why the girl decided that she wants to open her own ice cream shops.

Sonya lives in a city with $ n $ junctions and $ n-1 $ streets between them. All streets are two-way and connect two junctions. It is possible to travel from any junction to any other using one or more streets. City Hall allows opening shops only on junctions. The girl cannot open shops in the middle of streets.

Sonya has exactly $ k $ friends whom she can trust. If she opens a shop, one of her friends has to work there and not to allow anybody to eat an ice cream not paying for it. Since Sonya does not want to skip an important competition, she will not work in shops personally.

Sonya wants all her ice cream shops to form a simple path of the length $ r $ ( $ 1 \le r \le k $ ), i.e. to be located in different junctions $ f_1, f_2, \dots, f_r $ and there is street between $ f_i $ and $ f_{i+1} $ for each $ i $ from $ 1 $ to $ r-1 $ .

The girl takes care of potential buyers, so she also wants to minimize the maximum distance between the junctions to the nearest ice cream shop. The distance between two junctions $ a $ and $ b $ is equal to the sum of all the street lengths that you need to pass to get from the junction $ a $ to the junction $ b $ . So Sonya wants to minimize

 $ $$$\max_{a} \min_{1 \le i \le r} d_{a,f_i} $ $ </p><p>where  $ a $  takes a value of all possible  $ n $  junctions,  $ f\_i $  — the junction where the  $ i $ -th Sonya's shop is located, and  $ d\_{x,y} $  — the distance between the junctions  $ x $  and  $ y $ .</p><p>Sonya is not sure that she can find the optimal shops locations, that is why she is asking you to help her to open not more than  $ k$$$ shops that will form a simple path and the maximum distance between any junction and the nearest shop would be minimal.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1\leq k\leq n\leq 10^5 $ ) — the number of junctions and friends respectively.

Each of the next $ n-1 $ lines contains three integers $ u_i $ , $ v_i $ , and $ d_i $ ( $ 1\leq u_i, v_i\leq n $ , $ v_i\neq u_i $ , $ 1\leq d\leq 10^4 $ ) — junctions that are connected by a street and the length of this street. It is guaranteed that each pair of junctions is connected by at most one street. It is guaranteed that you can get from any junctions to any other.

## 输出格式

Print one number — the minimal possible maximum distance that you need to pass to get from any junction to the nearest ice cream shop. Sonya's shops must form a simple path and the number of shops must be at most $ k $ .

## 说明/提示

In the first example, you can choose the path 2-4, so the answer will be 4.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1004E/8c2f15a4fd52f01b9e20de5f6f72a725ba32bbc7.png)The first example.In the second example, you can choose the path 4-1-2, so the answer will be 7.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1004E/473187d2fc5546701ca91ad8cfaa45bd65002a47.png)The second example.

## 样例 #1

### 输入

```
6 2
1 2 3
2 3 4
4 5 2
4 6 3
2 4 6

```

### 输出

```
4

```

## 样例 #2

### 输入

```
10 3
1 2 5
5 7 2
3 2 6
10 6 3
3 8 1
6 4 2
4 1 6
6 9 4
5 2 5

```

### 输出

```
7

```

