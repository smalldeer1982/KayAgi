---
title: "Drinks"
layout: "post"
diff: 普及-
pid: CF200B
tag: []
---

# Drinks

## 题目描述

Little Vasya loves orange juice very much. That's why any food and drink in his kitchen necessarily contains orange juice. There are $ n $ drinks in his fridge, the volume fraction of orange juice in the $ i $ -th drink equals $ p_{i} $ percent.

One day Vasya decided to make himself an orange cocktail. He took equal proportions of each of the $ n $ drinks and mixed them. Then he wondered, how much orange juice the cocktail has.

Find the volume fraction of orange juice in the final drink.

## 输入格式

The first input line contains a single integer $ n $ ( $ 1<=n<=100 $ ) — the number of orange-containing drinks in Vasya's fridge. The second line contains $ n $ integers $ p_{i} $ ( $ 0<=p_{i}<=100 $ ) — the volume fraction of orange juice in the $ i $ -th drink, in percent. The numbers are separated by a space.

## 输出格式

Print the volume fraction in percent of orange juice in Vasya's cocktail. The answer will be considered correct if the absolute or relative error does not exceed $ 10^{-4} $ .

## 说明/提示

Note to the first sample: let's assume that Vasya takes $ x $ milliliters of each drink from the fridge. Then the volume of pure juice in the cocktail will equal ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF200B/7c2a6a8bbcdbfef1f9a32c2eb1f7549c3c17c619.png) milliliters. The total cocktail's volume equals $ 3·x $ milliliters, so the volume fraction of the juice in the cocktail equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF200B/cc3d21395b67607dff0b7baa3b0b870221e3352d.png), that is, $ 66.(6) $ percent.

## 样例 #1

### 输入

```
3
50 50 100

```

### 输出

```
66.666666666667

```

## 样例 #2

### 输入

```
4
0 25 50 75

```

### 输出

```
37.500000000000

```

