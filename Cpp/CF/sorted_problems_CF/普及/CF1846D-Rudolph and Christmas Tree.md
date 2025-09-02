---
title: "Rudolph and Christmas Tree"
layout: "post"
diff: 普及/提高-
pid: CF1846D
tag: []
---

# Rudolph and Christmas Tree

## 题目描述

Rudolph drew a beautiful Christmas tree and decided to print the picture. However, the ink in the cartridge often runs out at the most inconvenient moment. Therefore, Rudolph wants to calculate in advance how much green ink he will need.

The tree is a vertical trunk with identical triangular branches at different heights. The thickness of the trunk is negligible.

Each branch is an isosceles triangle with base $ d $ and height $ h $ , whose base is perpendicular to the trunk. The triangles are arranged upward at an angle, and the trunk passes exactly in the middle. The base of the $ i $ -th triangle is located at a height of $ y_i $ .

The figure below shows an example of a tree with $ d = 4, h = 2 $ and three branches with bases at heights $ [1, 4, 5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1846D/37fc4e66c82224ed8a6c688f81f74511a07dacd6.png)Help Rudolph calculate the total area of the tree branches.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Then follow the descriptions of the test cases.

The first line of each test case contains three integers $ n, d, h $ ( $ 1 \le n, d, h \le 2 \cdot 10^5 $ ) — the number of branches, the length of the base, and the height of the branches, respectively.

The second line of each test case contains $ n $ integers $ y_i $ $ (1 \le y_i \le 10^9, y_1 < y_2 < ... < y_n) $ — the heights of the bases of the branches.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single real number on a separate line — the total area of the tree branches. The answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
5
3 4 2
1 4 5
1 5 1
3
4 6 6
1 2 3 4
2 1 200000
1 200000
2 4 3
9 11
```

### 输出

```
11
2.5
34.5
199999.9999975
11.333333
```

