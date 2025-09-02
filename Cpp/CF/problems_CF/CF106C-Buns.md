---
title: "Buns"
layout: "post"
diff: 普及/提高-
pid: CF106C
tag: ['背包 DP']
---

# Buns

## 题目描述

Lavrenty, a baker, is going to make several buns with stuffings and sell them.

Lavrenty has $ n $ grams of dough as well as $ m $ different stuffing types. The stuffing types are numerated from 1 to $ m $ . Lavrenty knows that he has $ a_{i} $ grams left of the $ i $ -th stuffing. It takes exactly $ b_{i} $ grams of stuffing $ i $ and $ c_{i} $ grams of dough to cook a bun with the $ i $ -th stuffing. Such bun can be sold for $ d_{i} $ tugriks.

Also he can make buns without stuffings. Each of such buns requires $ c_{0} $ grams of dough and it can be sold for $ d_{0} $ tugriks. So Lavrenty can cook any number of buns with different stuffings or without it unless he runs out of dough and the stuffings. Lavrenty throws away all excess material left after baking.

Find the maximum number of tugriks Lavrenty can earn.

## 输入格式

The first line contains $ 4 $ integers $ n $ , $ m $ , $ c_{0} $ and $ d_{0} $ ( $ 1<=n<=1000 $ , $ 1<=m<=10 $ , $ 1<=c_{0},d_{0}<=100 $ ). Each of the following $ m $ lines contains $ 4 $ integers. The $ i $ -th line contains numbers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ and $ d_{i} $ ( $ 1<=a_{i},b_{i},c_{i},d_{i}<=100 $ ).

## 输出格式

Print the only number — the maximum number of tugriks Lavrenty can earn.

## 说明/提示

To get the maximum number of tugriks in the first sample, you need to cook 2 buns with stuffing 1, 4 buns with stuffing 2 and a bun without any stuffing.

In the second sample Lavrenty should cook 4 buns without stuffings.

## 样例 #1

### 输入

```
10 2 2 1
7 3 2 100
12 3 1 10

```

### 输出

```
241
```

## 样例 #2

### 输入

```
100 1 25 50
15 5 20 10

```

### 输出

```
200
```

