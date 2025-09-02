---
title: "Fox and Box Accumulation"
layout: "post"
diff: 普及/提高-
pid: CF388A
tag: []
---

# Fox and Box Accumulation

## 题目描述

Fox Ciel has $ n $ boxes in her room. They have the same size and weight, but they might have different strength. The $ i $ -th box can hold at most $ x_{i} $ boxes on its top (we'll call $ x_{i} $ the strength of the box).

Since all the boxes have the same size, Ciel cannot put more than one box directly on the top of some box. For example, imagine Ciel has three boxes: the first has strength 2, the second has strength 1 and the third has strength 1. She cannot put the second and the third box simultaneously directly on the top of the first one. But she can put the second box directly on the top of the first one, and then the third box directly on the top of the second one. We will call such a construction of boxes a pile.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF388A/6d2633af40be72721ab147bac34f10adae362d79.png)Fox Ciel wants to construct piles from all the boxes. Each pile will contain some boxes from top to bottom, and there cannot be more than $ x_{i} $ boxes on the top of $ i $ -th box. What is the minimal number of piles she needs to construct?

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ). The next line contains $ n $ integers $ x_{1},x_{2},...,x_{n} $ ( $ 0<=x_{i}<=100 $ ).

## 输出格式

Output a single integer — the minimal possible number of piles.

## 说明/提示

In example 1, one optimal way is to build 2 piles: the first pile contains boxes 1 and 3 (from top to bottom), the second pile contains only box 2.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF388A/8da8ac854632528901b4b6d1d556d9ee8e51a35b.png)In example 2, we can build only 1 pile that contains boxes 1, 2, 3, 4, 5 (from top to bottom).

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF388A/c58e3e4af77310d72ce6f918487297f03a91630c.png)

## 样例 #1

### 输入

```
3
0 0 10

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
0 1 2 3 4

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4
0 0 0 0

```

### 输出

```
4

```

## 样例 #4

### 输入

```
9
0 1 0 2 0 1 1 2 10

```

### 输出

```
3

```

