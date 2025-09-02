---
title: "Pencils and Boxes"
layout: "post"
diff: 普及+/提高
pid: CF985E
tag: []
---

# Pencils and Boxes

## 题目描述

Mishka received a gift of multicolored pencils for his birthday! Unfortunately he lives in a monochrome world, where everything is of the same color and only saturation differs. This pack can be represented as a sequence $ a_{1},a_{2},...,a_{n} $ of $ n $ integer numbers — saturation of the color of each pencil. Now Mishka wants to put all the mess in the pack in order. He has an infinite number of empty boxes to do this. He would like to fill some boxes in such a way that:

- Each pencil belongs to exactly one box;
- Each non-empty box has at least $ k $ pencils in it;
- If pencils $ i $ and $ j $ belong to the same box, then $ |a_{i}-a_{j}|<=d $ , where $ |x| $ means absolute value of $ x $ . Note that the opposite is optional, there can be pencils $ i $ and $ j $ such that $ |a_{i}-a_{j}|<=d $ and they belong to different boxes.

Help Mishka to determine if it's possible to distribute all the pencils into boxes. Print "YES" if there exists such a distribution. Otherwise print "NO".

## 输入格式

The first line contains three integer numbers $ n $ , $ k $ and $ d $ ( $ 1<=k<=n<=5·10^{5} $ , $ 0<=d<=10^{9} $ ) — the number of pencils, minimal size of any non-empty box and maximal difference in saturation between any pair of pencils in the same box, respectively.

The second line contains $ n $ integer numbers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — saturation of color of each pencil.

## 输出格式

Print "YES" if it's possible to distribute all the pencils into boxes and satisfy all the conditions. Otherwise print "NO".

## 说明/提示

In the first example it is possible to distribute pencils into $ 2 $ boxes with $ 3 $ pencils in each with any distribution. And you also can put all the pencils into the same box, difference of any pair in it won't exceed $ 10 $ .

In the second example you can split pencils of saturations $ [4,5,3,4] $ into $ 2 $ boxes of size $ 2 $ and put the remaining ones into another box.

## 样例 #1

### 输入

```
6 3 10
7 2 7 7 4 2

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
6 2 3
4 5 3 13 4 10

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
3 2 5
10 16 22

```

### 输出

```
NO

```

