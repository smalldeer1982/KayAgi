---
title: "Row of Models"
layout: "post"
diff: 提高+/省选-
pid: CF887F
tag: []
---

# Row of Models

## 题目描述

During the final part of fashion show all models come to the stage and stay in one row and fashion designer stays to right to model on the right. During the rehearsal, Izabella noticed, that row isn't nice, but she can't figure out how to fix it.

Like many other creative people, Izabella has a specific sense of beauty. Evaluating beauty of row of models Izabella looks at heights of models. She thinks that row is nice if for each model distance to nearest model with less height (model or fashion designer) to the right of her doesn't exceed $ k $ (distance between adjacent people equals 1, the distance between people with exactly one man between them equals 2, etc).

She wants to make row nice, but fashion designer has his own sense of beauty, so she can at most one time select two models from the row and swap their positions if the left model from this pair is higher than the right model from this pair.

Fashion designer (man to the right of rightmost model) has less height than all models and can't be selected for exchange.

You should tell if it's possible to make at most one exchange in such a way that row becomes nice for Izabella.

## 输入格式

In first line there are two integers $ n $ and $ k $ ( $ 1<=n<=5·10^{5} $ , $ 1<=k<=n $ ) — number of models and required distance.

Second line contains $ n $ space-separated integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — height of each model. Pay attention that height of fashion designer is not given and can be less than 1.

## 输出格式

Print «YES» (without quotes) if it's possible to make row nice using at most one exchange, and «NO» (without quotes) otherwise.

## 样例 #1

### 输入

```
5 4
2 3 5 2 5

```

### 输出

```
NO
```

## 样例 #2

### 输入

```
5 2
3 6 2 2 1

```

### 输出

```
YES
```

## 样例 #3

### 输入

```
5 2
5 3 6 5 2

```

### 输出

```
YES
```

