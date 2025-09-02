---
title: "Prison Break"
layout: "post"
diff: 入门
pid: CF1484A
tag: []
---

# Prison Break

## 题目描述

Michael is accused of violating the social distancing rules and creating a risk of spreading coronavirus. He is now sent to prison. Luckily, Michael knows exactly what the prison looks like from the inside, especially since it's very simple.

The prison can be represented as a rectangle $ a\times b $ which is divided into $ ab $ cells, each representing a prison cell, common sides being the walls between cells, and sides on the perimeter being the walls leading to freedom. Before sentencing, Michael can ask his friends among the prison employees to make (very well hidden) holes in some of the walls (including walls between cells and the outermost walls). Michael wants to be able to get out of the prison after this, no matter which cell he is placed in. However, he also wants to break as few walls as possible.

Your task is to find out the smallest number of walls to be broken so that there is a path to the outside from every cell after this.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\leq t\leq 100 $ ) — the number of test cases.

Each of the following $ t $ lines contains two integers $ a $ and $ b $ ( $ 1\leq a, b\leq 100 $ ), representing a corresponding test case.

## 输出格式

For each test case print the single integer on a separate line — the answer to the problem.

## 说明/提示

Some possible escape plans for the example test cases are shown below. Broken walls are shown in gray, not broken walls are shown in black.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1484A/a4659585fb5a010bae617b961924fcd595e6f78a.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1484A/4c54b6f42b6a89eb061e6459fc4f87678206d125.png)

## 样例 #1

### 输入

```
2
2 2
1 3
```

### 输出

```
4
3
```

