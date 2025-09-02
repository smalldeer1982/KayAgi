---
title: "Bear and Colors"
layout: "post"
diff: 普及-
pid: CF643A
tag: []
---

# Bear and Colors

## 题目描述

Bear Limak has $ n $ colored balls, arranged in one long row. Balls are numbered $ 1 $ through $ n $ , from left to right. There are $ n $ possible colors, also numbered $ 1 $ through $ n $ . The $ i $ -th ball has color $ t_{i} $ .

For a fixed interval (set of consecutive elements) of balls we can define a dominant color. It's a color occurring the biggest number of times in the interval. In case of a tie between some colors, the one with the smallest number (index) is chosen as dominant.

There are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643A/e72cbeaa17cceea137ec85134680a8c41a08d995.png) non-empty intervals in total. For each color, your task is to count the number of intervals in which this color is dominant.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=5000 $ ) — the number of balls.

The second line contains $ n $ integers $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=n $ ) where $ t_{i} $ is the color of the $ i $ -th ball.

## 输出格式

Print $ n $ integers. The $ i $ -th of them should be equal to the number of intervals where $ i $ is a dominant color.

## 说明/提示

In the first sample, color $ 2 $ is dominant in three intervals:

- An interval $ [2,2] $ contains one ball. This ball's color is $ 2 $ so it's clearly a dominant color.
- An interval $ [4,4] $ contains one ball, with color $ 2 $ again.
- An interval $ [2,4] $ contains two balls of color $ 2 $ and one ball of color $ 1 $ .

There are $ 7 $ more intervals and color $ 1 $ is dominant in all of them.

## 样例 #1

### 输入

```
4
1 2 1 2

```

### 输出

```
7 3 0 0 

```

## 样例 #2

### 输入

```
3
1 1 1

```

### 输出

```
6 0 0 

```

