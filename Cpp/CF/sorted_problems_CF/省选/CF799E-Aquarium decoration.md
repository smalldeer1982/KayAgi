---
title: "Aquarium decoration"
layout: "post"
diff: 省选/NOI-
pid: CF799E
tag: []
---

# Aquarium decoration

## 题目描述

Arkady and Masha want to choose decorations for thier aquarium in Fishdom game. They have $ n $ decorations to choose from, each of them has some cost. To complete a task Arkady and Masha need to choose exactly $ m $ decorations from given, and they want to spend as little money as possible.

There is one difficulty: Masha likes some $ a $ of the given decorations, Arkady likes some $ b $ of the given decorations. Some decorations may be liked by both Arkady and Masha, or not be liked by both. The friends want to choose such decorations so that each of them likes at least $ k $ decorations among the chosen. Help Masha and Arkady find the minimum sum of money they need to spend.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 1<=n<=200000 $ , $ 1<=m<=n $ , $ 1<=k<=n $ ) — the number of decorations, how many decorations the friends should choose, how many decorations each of them should like among the chosen.

The second line contains $ n $ integers $ c_{1},c_{2},...,c_{n} $ ( $ 1<=c_{i}<=10^{9} $ ) — decorations costs.

The third line contains single integer $ a $ ( $ 1<=a<=n $ ) — the number of decorations liked by Masha. The fourth line contains $ a $ distinct integers $ x_{1},x_{2},...,x_{a} $ ( $ 1<=x_{i}<=n $ ) — the ids of decorations liked by Masha.

The next two lines describe decorations liked by Arkady in the same format.

## 输出格式

Print single integer: the minimum sum of money the friends should spend to fulfill all constraints. If it is not possible, print -1.

## 说明/提示

In the first example the only possible variant to choose $ 3 $ decorations having all conditions satisfied is to choose decorations $ 1 $ , $ 2 $ , $ 3 $ .

In the second example friends can choose decoration $ 4 $ instead of decoration $ 3 $ , because this one is one coin cheaper.

In the third example it's not possible to choose $ 2 $ decorations in a way that both are liked by both Masha and Arkady.

## 样例 #1

### 输入

```
4 3 2
3 2 2 1
2
1 2
2
1 3

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4 3 2
3 2 2 1
2
1 2
3
4 1 3

```

### 输出

```
6

```

## 样例 #3

### 输入

```
4 2 2
3 2 2 1
2
1 2
3
4 1 3

```

### 输出

```
-1

```

