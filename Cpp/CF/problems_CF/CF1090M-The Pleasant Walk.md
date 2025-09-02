---
title: "The Pleasant Walk"
layout: "post"
diff: 普及-
pid: CF1090M
tag: []
---

# The Pleasant Walk

## 题目描述

There are $ n $ houses along the road where Anya lives, each one is painted in one of $ k $ possible colors.

Anya likes walking along this road, but she doesn't like when two adjacent houses at the road have the same color. She wants to select a long segment of the road such that no two adjacent houses have the same color.

Help Anya find the longest segment with this property.

## 输入格式

The first line contains two integers $ n $ and $ k $ — the number of houses and the number of colors ( $ 1 \le n \le 100\,000 $ , $ 1 \le k \le 100\,000 $ ).

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ — the colors of the houses along the road ( $ 1 \le a_i \le k $ ).

## 输出格式

Output a single integer — the maximum number of houses on the road segment having no two adjacent houses of the same color.

## 说明/提示

In the example, the longest segment without neighboring houses of the same color is from the house 4 to the house 7. The colors of the houses are $ [3, 2, 1, 2] $ and its length is 4 houses.

## 样例 #1

### 输入

```
8 3
1 2 3 3 2 1 2 2

```

### 输出

```
4

```

