---
title: "Pudding Monsters"
layout: "post"
diff: 省选/NOI-
pid: CF526F
tag: []
---

# Pudding Monsters

## 题目描述

In this problem you will meet the simplified model of game Pudding Monsters.

An important process in developing any game is creating levels. A game field in Pudding Monsters is an $ n×n $ rectangular grid, $ n $ of its cells contain monsters and some other cells contain game objects. The gameplay is about moving the monsters around the field. When two monsters are touching each other, they glue together into a single big one (as they are from pudding, remember?).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526F/20aa5815ee72cc21be376a3c3bc47e609a6b5dc1.png)Statistics showed that the most interesting maps appear if initially each row and each column contains exactly one monster and the rest of map specifics is set up by the correct positioning of the other game objects.

A technique that's widely used to make the development process more efficient is reusing the available resources. For example, if there is a large $ n×n $ map, you can choose in it a smaller $ k×k $ square part, containing exactly $ k $ monsters and suggest it as a simplified version of the original map.

You wonder how many ways there are to choose in the initial map a $ k×k $ ( $ 1<=k<=n $ ) square fragment, containing exactly $ k $ pudding monsters. Calculate this number.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=3×10^{5} $ ) — the size of the initial field.

Next $ n $ lines contain the coordinates of the cells initially containing monsters. The $ i $ -th of the next lines contains two numbers $ r_{i},c_{i} $ ( $ 1<=r_{i},c_{i}<=n $ ) — the row number and the column number of the cell that initially contains the $ i $ -th monster.

It is guaranteed that all $ r_{i} $ are distinct numbers and all $ c_{i} $ are distinct numbers.

## 输出格式

Print the number of distinct square fragments of the original field that can form a new map.

## 样例 #1

### 输入

```
5
1 1
4 3
3 2
2 4
5 5

```

### 输出

```
10

```

