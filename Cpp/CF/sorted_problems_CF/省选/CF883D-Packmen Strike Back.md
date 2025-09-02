---
title: "Packmen Strike Back"
layout: "post"
diff: 省选/NOI-
pid: CF883D
tag: []
---

# Packmen Strike Back

## 题目描述

Game field is represented by a line of $ n $ square cells. In some cells there are packmen, in some cells there are asterisks and the rest of the cells are empty. Packmen eat asterisks.

Before the game starts you can choose a movement direction, left or right, for each packman. Once the game begins all the packmen simultaneously start moving according their directions. A packman can't change the given direction.

Once a packman enters a cell containing an asterisk, packman immediately eats the asterisk. Once the packman leaves the cell it becomes empty. Each packman moves at speed 1 cell per second. If a packman enters a border cell, the packman stops. Packmen do not interfere with the movement of other packmen; in one cell there can be any number of packmen moving in any directions.

Your task is to assign a direction to each packman so that they eat the maximal number of asterisks. If there are multiple ways to assign directions to eat the maximal number of asterisks, you should choose the way which minimizes the time to do that.

## 输入格式

The first line contains integer number $ n $ ( $ 2<=n<=1000000 $ ) — the number of cells in the game field.

The second line contains $ n $ characters. If the $ i $ -th character is '.', the $ i $ -th cell is empty. If the $ i $ -th character is '\*', the $ i $ -th cell contains an asterisk. If the $ i $ -th character is 'P', the $ i $ -th cell contains a packman.

The field contains at least one asterisk and at least one packman.

## 输出格式

Print two integer numbers — the maximal number of asterisks packmen can eat and the minimal time to do it.

## 说明/提示

In the first example the leftmost packman should move to the right, the rightmost packman should move to the left. All the asterisks will be eaten, the last asterisk will be eaten after 4 seconds.

## 样例 #1

### 输入

```
6
*.P*P*

```

### 输出

```
3 4

```

## 样例 #2

### 输入

```
8
*...P..*

```

### 输出

```
1 3

```

