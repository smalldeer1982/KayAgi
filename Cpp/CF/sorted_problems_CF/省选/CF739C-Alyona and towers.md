---
title: "Alyona and towers"
layout: "post"
diff: 省选/NOI-
pid: CF739C
tag: []
---

# Alyona and towers

## 题目描述

Alyona has built $ n $ towers by putting small cubes some on the top of others. Each cube has size $ 1×1×1 $ . A tower is a non-zero amount of cubes standing on the top of each other. The towers are next to each other, forming a row.

Sometimes Alyona chooses some segment towers, and put on the top of each tower several cubes. Formally, Alyouna chooses some segment of towers from $ l_{i} $ to $ r_{i} $ and adds $ d_{i} $ cubes on the top of them.

Let the sequence $ a_{1},a_{2},...,a_{n} $ be the heights of the towers from left to right. Let's call as a segment of towers $ a_{l},a_{l+1},...,a_{r} $ a hill if the following condition holds: there is integer $ k $ ( $ l<=k<=r $ ) such that $ a_{l}&lt;a_{l+1}&lt;a_{l+2}&lt;...&lt;a_{k}&gt;a_{k+1}&gt;a_{k+2}&gt;...&gt;a_{r} $ .

After each addition of $ d_{i} $ cubes on the top of the towers from $ l_{i} $ to $ r_{i} $ , Alyona wants to know the maximum width among all hills. The width of a hill is the number of towers in it.

## 输入格式

The first line contain single integer $ n $ ( $ 1<=n<=3·10^{5} $ ) — the number of towers.

The second line contain $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the number of cubes in each tower.

The third line contain single integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of additions.

The next $ m $ lines contain $ 3 $ integers each. The $ i $ -th of these lines contains integers $ l_{i} $ , $ r_{i} $ and $ d_{i} $ ( $ 1<=l<=r<=n $ , $ 1<=d_{i}<=10^{9} $ ), that mean that Alyona puts $ d_{i} $ cubes on the tio of each of the towers from $ l_{i} $ to $ r_{i} $ .

## 输出格式

Print $ m $ lines. In $ i $ -th line print the maximum width of the hills after the $ i $ -th addition.

## 说明/提示

The first sample is as follows:

After addition of $ 2 $ cubes on the top of each towers from the first to the third, the number of cubes in the towers become equal to $ [7,7,7,5,5] $ . The hill with maximum width is $ [7,5] $ , thus the maximum width is $ 2 $ .

After addition of $ 1 $ cube on the second tower, the number of cubes in the towers become equal to $ [7,8,7,5,5] $ . The hill with maximum width is now $ [7,8,7,5] $ , thus the maximum width is $ 4 $ .

After addition of $ 1 $ cube on the fourth tower, the number of cubes in the towers become equal to $ [7,8,7,6,5] $ . The hill with maximum width is now $ [7,8,7,6,5] $ , thus the maximum width is $ 5 $ .

## 样例 #1

### 输入

```
5
5 5 5 5 5
3
1 3 2
2 2 1
4 4 1

```

### 输出

```
2
4
5

```

