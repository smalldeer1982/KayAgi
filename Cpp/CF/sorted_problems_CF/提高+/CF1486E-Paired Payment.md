---
title: "Paired Payment"
layout: "post"
diff: 提高+/省选-
pid: CF1486E
tag: []
---

# Paired Payment

## 题目描述

There are $ n $ cities and $ m $ bidirectional roads in the country. The roads in the country form an undirected weighted graph. The graph is not guaranteed to be connected. Each road has it's own parameter $ w $ . You can travel through the roads, but the government made a new law: you can only go through two roads at a time (go from city $ a $ to city $ b $ and then from city $ b $ to city $ c $ ) and you will have to pay $ (w_{ab} + w_{bc})^2 $ money to go through those roads. Find out whether it is possible to travel from city $ 1 $ to every other city $ t $ and what's the minimum amount of money you need to get from $ 1 $ to $ t $ .

## 输入格式

First line contains two integers $ n $ , $ m $ ( $ 2 \leq n \leq 10^5 $ , $ 1 \leq m \leq min(\frac{n \cdot (n - 1)}{2}, 2 \cdot 10^5) $ ).

Next $ m $ lines each contain three integers $ v_i $ , $ u_i $ , $ w_i $ ( $ 1 \leq v_i, u_i \leq n $ , $ 1 \leq w_i \leq 50 $ , $ u_i \neq v_i $ ). It's guaranteed that there are no multiple edges, i.e. for any edge $ (u_i, v_i) $ there are no other edges $ (u_i, v_i) $ or $ (v_i, u_i) $ .

## 输出格式

For every city $ t $ print one integer. If there is no correct path between $ 1 $ and $ t $ output $ -1 $ . Otherwise print out the minimum amount of money needed to travel from $ 1 $ to $ t $ .

## 说明/提示

The graph in the first example looks like this.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486E/d05a9b1774a0eade44485bb99ef938693d1a95f9.png)

In the second example the path from $ 1 $ to $ 3 $ goes through $ 2 $ , so the resulting payment is $ (1 + 2)^2 = 9 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486E/9c27ff1803f812784d9dc5ba8f09e905e17b3714.png)

## 样例 #1

### 输入

```
5 6
1 2 3
2 3 4
3 4 5
4 5 6
1 5 1
2 4 2
```

### 输出

```
0 98 49 25 114
```

## 样例 #2

### 输入

```
3 2
1 2 1
2 3 2
```

### 输出

```
0 -1 9
```

