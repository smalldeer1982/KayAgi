---
title: "Wilbur and Trees"
layout: "post"
diff: 省选/NOI-
pid: CF596D
tag: []
---

# Wilbur and Trees

## 题目描述

Wilbur the pig really wants to be a beaver, so he decided today to pretend he is a beaver and bite at trees to cut them down.

There are $ n $ trees located at various positions on a line. Tree $ i $ is located at position $ x_{i} $ . All the given positions of the trees are distinct.

The trees are equal, i.e. each tree has height $ h $ . Due to the wind, when a tree is cut down, it either falls left with probability $ p $ , or falls right with probability $ 1-p $ . If a tree hits another tree while falling, that tree will fall in the same direction as the tree that hit it. A tree can hit another tree only if the distance between them is strictly less than $ h $ .

For example, imagine there are $ 4 $ trees located at positions $ 1 $ , $ 3 $ , $ 5 $ and $ 8 $ , while $ h=3 $ and the tree at position $ 1 $ falls right. It hits the tree at position $ 3 $ and it starts to fall too. In it's turn it hits the tree at position $ 5 $ and it also starts to fall. The distance between $ 8 $ and $ 5 $ is exactly $ 3 $ , so the tree at position $ 8 $ will not fall.

As long as there are still trees standing, Wilbur will select either the leftmost standing tree with probability $ 0.5 $ or the rightmost standing tree with probability $ 0.5 $ . Selected tree is then cut down. If there is only one tree remaining, Wilbur always selects it. As the ground is covered with grass, Wilbur wants to know the expected total length of the ground covered with fallen trees after he cuts them all down because he is concerned about his grass-eating cow friends. Please help Wilbur.

## 输入格式

The first line of the input contains two integers, $ n $ $ (1<=n<=2000) $ and $ h $ $ (1<=h<=10^{8}) $ and a real number $ p $ ( $ 0<=p<=1 $ ), given with no more than six decimal places.

The second line of the input contains $ n $ integers, $ x_{1},x_{2},...,x_{n} $ $ (-10^{8}<=x_{i}<=10^{8}) $ in no particular order.

## 输出格式

Print a single real number — the expected total length of the ground covered by trees when they have all fallen down. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

Consider the first example, we have 2 trees with height 2.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/7ea79c02ec83af888c806be42da0defa4e428746.png) There are 3 scenarios:  1. Both trees falls left. This can either happen with the right tree falling left first, which has ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/b116fbdd63568e4121015b312e3b382ba11897c2.png) probability (also knocking down the left tree), or the left tree can fall left and then the right tree can fall left, which has ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/949810d863b968a5ba3d8d376258384cb22f342a.png) probability. Total probability is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/99d81ce87528a9d733790866f22c7ea59a9a6aba.png).

 2. Both trees fall right. This is analogous to (1), so the probability of this happening is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/9c584154315cc26f3f6d096139c60a6d963a78db.png).

 3. The left tree fall left and the right tree falls right. This is the only remaining scenario so it must have ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/7600097d7e8dbe4c0d431b4b3222d04bc7df2acc.png) probability.

 Cases 1 and 2 lead to a total of 3 units of ground covered, while case 3 leads to a total of 4 units of ground covered. Thus, the expected value is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/6b415b0ca26814ba41988ac3a2c4b91c5d01c6e4.png).

## 样例 #1

### 输入

```
2 2 0.500000
1 2

```

### 输出

```
3.250000000

```

## 样例 #2

### 输入

```
4 3 0.4
4 3 1 2

```

### 输出

```
6.631200000

```

