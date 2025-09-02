---
title: "Bicycle Chain"
layout: "post"
diff: 普及-
pid: CF215A
tag: []
---

# Bicycle Chain

## 题目描述

Vasya's bicycle chain drive consists of two parts: $ n $ stars are attached to the pedal axle, $ m $ stars are attached to the rear wheel axle. The chain helps to rotate the rear wheel by transmitting the pedal rotation.

We know that the $ i $ -th star on the pedal axle has $ a_{i} $ $ (0&lt;a_{1}&lt;a_{2}&lt;...&lt;a_{n}) $ teeth, and the $ j $ -th star on the rear wheel axle has $ b_{j} $ $ (0&lt;b_{1}&lt;b_{2}&lt;...&lt;b_{m}) $ teeth. Any pair $ (i,j) $ $ (1<=i<=n $ ; $ 1<=j<=m) $ is called a gear and sets the indexes of stars to which the chain is currently attached. Gear $ (i,j) $ has a gear ratio, equal to the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF215A/552855b6cae5503b6d59fc360af0683e021f4625.png).

Since Vasya likes integers, he wants to find such gears $ (i,j) $ , that their ratios are integers. On the other hand, Vasya likes fast driving, so among all "integer" gears $ (i,j) $ he wants to choose a gear with the maximum ratio. Help him to find the number of such gears.

In the problem, fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF215A/552855b6cae5503b6d59fc360af0683e021f4625.png) denotes division in real numbers, that is, no rounding is performed.

## 输入格式

The first input line contains integer $ n $ $ (1<=n<=50) $ — the number of stars on the bicycle's pedal axle. The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{4}) $ in the order of strict increasing.

The third input line contains integer $ m $ $ (1<=m<=50) $ — the number of stars on the rear wheel axle. The fourth line contains $ m $ integers $ b_{1},b_{2},...,b_{m} $ $ (1<=b_{i}<=10^{4}) $ in the order of strict increasing.

It is guaranteed that there exists at least one gear ( $ i,j $ ), that its gear ratio is an integer. The numbers on the lines are separated by spaces.

## 输出格式

Print the number of "integer" gears with the maximum ratio among all "integer" gears.

## 说明/提示

In the first sample the maximum "integer" gear ratio equals 3. There are two gears that have such gear ratio. For one of them $ a_{1}=4,b_{1}=12 $ , and for the other $ a_{2}=5,b_{3}=15 $ .

## 样例 #1

### 输入

```
2
4 5
3
12 13 15

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
1 2 3 4
5
10 11 12 13 14

```

### 输出

```
1

```

