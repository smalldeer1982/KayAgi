---
title: "CAKE - Birthday Cake"
layout: "post"
diff: 提高+/省选-
pid: SP1452
tag: []
---

# CAKE - Birthday Cake

## 题目描述

Adolf 想送一个蛋糕给 Blue Mary 庆祝她的生日。蛋糕看起来像一座有 $M$ 层的塔，每层都是一个圆柱体。从下到上计数的第 $i$ 个圆柱体具有高度 $h_i$ 和半径 $r_i$（$h_i,r_i\in Z_{+}$）。这些数字满足以下两个条件：

- $h_1>h_2>\cdots>h_M$
- $r_1>r_2>\cdots>r_M$

## 输入格式

本题有多组数据。

第一行一个整数 $T$，表示有 $T$ 组数据。

对于每一组数据：

第一行一个数 $N$（$N\leq10^4$），第二行一个数 $M$（$M\leq10$）

蛋糕必须由 $M$ 个圆柱体组成且体积为 $\pi\times N$，其中 $\pi=\operatorname{acos}(-1.0)$。

## 输出格式

对于每个测试点，输出一行一个整数 $S$ 表示蛋糕所需最小摆放面积为 $\pi\times S$。  
translate by @[\_\_Tonycyt\_\_](/user/667037)。

## 样例 #1

### 输入

```
1
100
2
```

### 输出

```
68
```

