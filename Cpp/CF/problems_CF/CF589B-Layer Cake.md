---
title: "Layer Cake"
layout: "post"
diff: 难度0
pid: CF589B
tag: []
---

# Layer Cake

## 题目描述

Dasha decided to bake a big and tasty layer cake. In order to do that she went shopping and bought $ n $ rectangular cake layers. The length and the width of the $ i $ -th cake layer were $ a_{i} $ and $ b_{i} $ respectively, while the height of each cake layer was equal to one.

From a cooking book Dasha learned that a cake must have a form of a rectangular parallelepiped constructed from cake layers of the same sizes.

Dasha decided to bake the biggest possible cake from the bought cake layers (possibly, using only some of them). It means that she wants the volume of the cake to be as big as possible. To reach this goal, Dasha can cut rectangular pieces out of the bought cake layers. She always cuts cake layers in such a way that cutting lines are parallel to the edges of that cake layer. Dasha isn't very good at geometry, so after cutting out a piece from the original cake layer, she throws away the remaining part of it. Also she can rotate a cake layer in the horizontal plane (swap its width and length).

Dasha wants her cake to be constructed as a stack of cake layers of the same sizes. Each layer of the resulting cake should be made out of only one cake layer (the original one or cut out from the original cake layer).

Help Dasha to calculate the maximum possible volume of the cake she can bake using given cake layers.

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=4000) $ — the number of cake layers that Dasha can use.

Each of the following $ n $ lines contains two integer numbers $ a_{i} $ and $ b_{i} $ $ (1<=a_{i},b_{i}<=10^{6}) $ — the length and the width of $ i $ -th cake layer respectively.

## 输出格式

The first line of the output should contain the maximum volume of cake that can be baked using given layers.

The second line of the output should contain the length and the width of the resulting cake. If there are many solutions with maximum possible volume, print any of them.

## 说明/提示

In the first example Dasha doesn't use the second cake layer. She cuts $ 4×6 $ rectangle from the first cake layer and she uses other cake layers as is.

In the second example Dasha cuts off slightly from the both cake layers.

## 样例 #1

### 输入

```
5
5 12
1 1
4 6
6 4
4 6

```

### 输出

```
96
6 4

```

## 样例 #2

### 输入

```
2
100001 900000
900001 100000

```

### 输出

```
180000000000
900000 100000

```

