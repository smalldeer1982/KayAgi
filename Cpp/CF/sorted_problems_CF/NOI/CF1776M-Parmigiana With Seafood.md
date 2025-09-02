---
title: "Parmigiana With Seafood"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1776M
tag: []
---

# Parmigiana With Seafood

## 题目描述

The "Parmigiana di melanzane" is a typical Italian dish. Alessandro and Bianca have very different tastes when it comes to it: Alessandro loves to eat Parmigiana with seafood, but Bianca thinks it is an atrocity! To decide which ingredients to include in the dish they prepare, they play the following game.

There are $ n $ possible ingredients, labeled from $ 1 $ to $ n $ . The higher the label, the closer the ingredient is to being seafood. The ingredients are connected by $ n - 1 $ edges, in such a way as to form a tree. Alessandro and Bianca take turns, with Alessandro going first. They alternately choose a terminal ingredient $ x $ , that is an ingredient currently connected to at most one other ingredient, and remove it from the tree. If the terminal ingredient $ x $ was chosen by Alessandro, it goes in the recipe; if it was chosen by Bianca, it is discarded.

The taste of the Parmigiana is measured as the maximum label of an ingredient in the recipe. Alessandro wants to maximize the taste, while Bianca wants to minimize the taste. If both play optimally, what is the taste of the Parmigiana?

## 输入格式

The first line contains an integer $ n $ ( $ 2\le n \le 100\,000 $ ) — the number of ingredients.

Each of the following $ n-1 $ lines contain two integers $ u_i $ and $ v_i $ ( $ 1 \le u_i, v_i \le n $ , $ u_i \ne v_i $ ) — the ingredients that the $ i $ -th edge connects.

It is guaranteed that the edges form a tree (i.e., any pair of ingredients is connected by the edges, possibly indirectly).

## 输出格式

Print the value of the taste if both Alessandro and Bianca play optimally.

## 说明/提示

In the first sample, Alessandro can choose terminal ingredient $ 4 $ in the first turn. This ingredient is added to the recipe. Since $ 4 $ is the maximum label of an ingredient, the taste is $ 4 $ regardless of the choices that follow.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776M/96bad947ed4d3b8bf55db712a7b8f56e59f006f5.png)In the second sample, Bianca can make sure that neither ingredient $ 4 $ nor $ 5 $ are included in the recipe, in which case Alessandro can include $ 3 $ . Thus, the taste is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776M/3f6ff43288b8e77a8a4ea1312fff9cb34ab05654.png)

## 样例 #1

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 5
5 3
3 4
4 2
```

### 输出

```
3
```

