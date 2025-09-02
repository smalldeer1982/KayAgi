---
title: "Cardboard Box"
layout: "post"
diff: 省选/NOI-
pid: CF436E
tag: []
---

# Cardboard Box

## 题目描述

Everyone who has played Cut the Rope knows full well how the gameplay is organized. All levels in the game are divided into boxes. Initially only one box with some levels is available. Player should complete levels to earn stars, collecting stars opens new box with levels.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF436E/17b1896a1f51431c95d9715d9bee7717c44e7cec.png)Imagine that you are playing Cut the Rope for the first time. Currently you have only the levels of the first box (by the way, it is called "Cardboard Box"). Each level is characterized by two integers: $ a_{i} $ — how long it takes to complete the level for one star, $ b_{i} $ — how long it takes to complete the level for two stars $ (a_{i}&lt;b_{i}) $ .

You want to open the next box as quickly as possible. So, you need to earn at least $ w $ stars. How do make it happen? Note that the level can be passed only once: either for one star or for two. You do not necessarily need to pass all the levels.

## 输入格式

The first line contains two integers $ n $ and $ w $ $ (1<=n<=3·10^{5}; 1<=w<=2n) $ — the number of levels in the first box and the number of stars you need to open another box. Each of the following $ n $ lines contains two integers $ a_{i} $ and $ b_{i} $ $ (1<=a_{i}&lt;b_{i}<=10^{9}) $ — the attributes of the $ i $ -th level.

## 输出格式

In the first line print integer $ t $ — the minimum time you need to open the next box.

In the next line, print $ n $ digits without spaces — the description of the optimal scenario:

- if you need to pass the $ i $ -th level for one star, the $ i $ -th digit should equal 1;
- if you need to pass the $ i $ -th level for two stars, the $ i $ -th digit should equal 2;
- if you do not need to pass the $ i $ -th level at all, the $ i $ -th digit should equal 0.

## 说明/提示

In the first test sample, answer 21 is also assumed correct.

## 样例 #1

### 输入

```
2 3
1 2
1 2

```

### 输出

```
3
12

```

## 样例 #2

### 输入

```
5 3
10 20
5 10
10 20
6 9
25 30

```

### 输出

```
14
01020

```

