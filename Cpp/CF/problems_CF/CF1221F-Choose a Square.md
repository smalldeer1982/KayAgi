---
title: "Choose a Square"
layout: "post"
diff: 省选/NOI-
pid: CF1221F
tag: []
---

# Choose a Square

## 题目描述

Petya recently found a game "Choose a Square". In this game, there are $ n $ points numbered from $ 1 $ to $ n $ on an infinite field. The $ i $ -th point has coordinates $ (x_i, y_i) $ and cost $ c_i $ .

You have to choose a square such that its sides are parallel to coordinate axes, the lower left and upper right corners belong to the line $ y = x $ , and all corners have integer coordinates.

The score you get is the sum of costs of the points covered by the selected square minus the length of the side of the square. Note that the length of the side can be zero.

Petya asks you to calculate the maximum possible score in the game that can be achieved by placing exactly one square.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ) — the number of points on the field.

Each of the following $ n $ lines contains three integers $ x_i, y_i, c_i $ ( $ 0 \le x_i, y_i \le 10^9, -10^6 \le c_i \le 10^6 $ ) — coordinates of the $ i $ -th point and its cost, respectively.

## 输出格式

In the first line print the maximum score Petya can achieve.

In the second line print four integers $ x_1, y_1, x_2, y_2 $ ( $ 0 \le x_1, y_1, x_2, y_2 \le 2 \cdot 10^9, x_1 = y_1, x_2 = y_2, x_1 \le x_2 $ ) separated by spaces — the coordinates of the lower left and upper right corners of the square which Petya has to select in order to achieve the maximum score.

## 说明/提示

The field corresponding to the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1221F/e9d6acfe5801db49535c73c7e3aac9d122102fde.png)

## 样例 #1

### 输入

```
6
0 0 2
1 0 -5
1 1 3
2 3 4
1 4 -4
3 1 -1

```

### 输出

```
4
1 1 3 3

```

## 样例 #2

### 输入

```
5
3 3 0
3 3 -3
0 2 -1
3 1 3
0 0 -2

```

### 输出

```
0
1 1 1 1

```

