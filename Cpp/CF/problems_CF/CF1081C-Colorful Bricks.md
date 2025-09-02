---
title: "Colorful Bricks"
layout: "post"
diff: 普及/提高-
pid: CF1081C
tag: []
---

# Colorful Bricks

## 题目描述

On his free time, Chouti likes doing some housework. He has got one new task, paint some bricks in the yard.

There are $ n $ bricks lined in a row on the ground. Chouti has got $ m $ paint buckets of different colors at hand, so he painted each brick in one of those $ m $ colors.

Having finished painting all bricks, Chouti was satisfied. He stood back and decided to find something fun with these bricks. After some counting, he found there are $ k $ bricks with a color different from the color of the brick on its left (the first brick is not counted, for sure).

So as usual, he needs your help in counting how many ways could he paint the bricks. Two ways of painting bricks are different if there is at least one brick painted in different colors in these two ways. Because the answer might be quite big, you only need to output the number of ways modulo $ 998\,244\,353 $ .

## 输入格式

The first and only line contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \leq n,m \leq 2000, 0 \leq k \leq n-1 $ ) — the number of bricks, the number of colors, and the number of bricks, such that its color differs from the color of brick to the left of it.

## 输出格式

Print one integer — the number of ways to color bricks modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, since $ k=0 $ , the color of every brick should be the same, so there will be exactly $ m=3 $ ways to color the bricks.

In the second example, suppose the two colors in the buckets are yellow and lime, the following image shows all $ 4 $ possible colorings.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1081C/4fa7a2f23ff4f46a8191eb0b20c44295510018b7.png)

## 样例 #1

### 输入

```
3 3 0

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 2 1

```

### 输出

```
4

```

