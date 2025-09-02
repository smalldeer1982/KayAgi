---
title: "Towers"
layout: "post"
diff: 提高+/省选-
pid: CF1637F
tag: ['贪心', '构造']
---

# Towers

## 题目描述

You are given a tree with $ n $ vertices numbered from $ 1 $ to $ n $ . The height of the $ i $ -th vertex is $ h_i $ . You can place any number of towers into vertices, for each tower you can choose which vertex to put it in, as well as choose its efficiency. Setting up a tower with efficiency $ e $ costs $ e $ coins, where $ e > 0 $ .

It is considered that a vertex $ x $ gets a signal if for some pair of towers at the vertices $ u $ and $ v $ ( $ u \neq v $ , but it is allowed that $ x = u $ or $ x = v $ ) with efficiencies $ e_u $ and $ e_v $ , respectively, it is satisfied that $ \min(e_u, e_v) \geq h_x $ and $ x $ lies on the path between $ u $ and $ v $ .

Find the minimum number of coins required to set up towers so that you can get a signal at all vertices.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \le n \le 200\,000 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ h_i $ ( $ 1 \le h_i \le 10^9 $ ) — the heights of the vertices.

Each of the next $ n - 1 $ lines contain a pair of numbers $ v_i, u_i $ ( $ 1 \le v_i, u_i \le n $ ) — an edge of the tree. It is guaranteed that the given edges form a tree.

## 输出格式

Print one integer — the minimum required number of coins.

## 说明/提示

In the first test case it's optimal to install two towers with efficiencies $ 2 $ at vertices $ 1 $ and $ 3 $ .

In the second test case it's optimal to install a tower with efficiency $ 1 $ at vertex $ 1 $ and two towers with efficiencies $ 3 $ at vertices $ 2 $ and $ 5 $ .

In the third test case it's optimal to install two towers with efficiencies $ 6 $ at vertices $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
3
1 2 1
1 2
2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 3 3 1 3
1 3
5 4
4 3
2 3
```

### 输出

```
7
```

## 样例 #3

### 输入

```
2
6 1
1 2
```

### 输出

```
12
```

