---
title: "Square Pool"
layout: "post"
diff: 难度0
pid: CF2120B
tag: []
---

# Square Pool

## 题目描述

Aryan and Harshith are playing pool in universe AX120 on a fixed square pool table of side $ s $ with pockets at its $ 4 $ corners. The corners are situated at $ (0,0) $ , $ (0,s) $ , $ (s,0) $ , and $ (s,s) $ . In this game variation, $ n $ identical balls are placed on the table with integral coordinates such that no ball lies on the edge or corner of the table. Then, they are all simultaneously shot at $ 10^{100} $ units/sec speed (only at $ 45 $ degrees with the axes).

In universe AX120, balls and pockets are almost point-sized, and the collisions are elastic, i.e., the ball, on hitting any surface, bounces off at the same angle and with the same speed.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120B/7f871ecbc7e2a7d12194afbb6ec8cea212feaef1.png)Harshith shot the balls, and he provided Aryan with the balls' positions and the angles at which he shot them. Help Aryan determine the number of balls potted into the pockets by Harshith.

It is guaranteed that multiple collisions do not occur at the same moment and position.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ s $ ( $ 1 \le n \le 10^3 $ , $ 2 \le s\le 10^9 $ ) — the number of balls placed on the table and the side length of the square pool table.

The $ i $ -th of the next $ n $ lines contains four integers $ d_x $ , $ d_y $ , $ x_i $ , and $ y_i $ ( $ d_x,d_y \in \{-1, 1\} $ , $ 0 \lt x_i, y_i \lt s $ ) — the direction vectors of the launch on the $ X $ -axis and $ Y $ -axis respectively, and the coordinates of the location where the $ i $ -th ball was placed. It is guaranteed that no two balls coincide at the initial moment.

It is also guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^3 $ .

## 输出格式

For each test case, print a single integer — the number of balls potted in that game.

## 说明/提示

In the first test case, there is a single ball and it's shot directly towards the pocket at $ (2, 2) $ , thus potted.

In the second test case, the state progresses as

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120B/7e7d284b38443a88b73723bd222602ca61a06036.png) $ \rightarrow $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120B/2e3d1f9bb535e0497fea850963fae4b6cec283cd.png)  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120B/67dddeac40338ec99879d48eedfc570ecdd1bdd7.png) $ \rightarrow $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120B/5f80a04942c25a01a70957ea82fe65f505baa91c.png)  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120B/1b9ab256c7839dc4ee83a93e0fb6b144e0fd12cf.png) $ \rightarrow $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120B/d850463cf22e6264fade9ef408e74183d1316c25.png)  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120B/a019759f2e9d4932e6857aa94117fba8d715b805.png) $ \rightarrow $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120B/2a6728aff68b062c6b9e2f48e6dbe5683dbe9f0d.png)

## 样例 #1

### 输入

```
2
1 2
1 1 1 1
5 4
1 -1 1 1
1 -1 2 2
-1 1 2 3
1 -1 1 3
-1 1 3 1
```

### 输出

```
1
3
```

