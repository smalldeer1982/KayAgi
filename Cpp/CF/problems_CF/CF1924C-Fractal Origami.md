---
title: "Fractal Origami"
layout: "post"
diff: 提高+/省选-
pid: CF1924C
tag: ['数学']
---

# Fractal Origami

## 题目描述

You have a square piece of paper with a side length equal to $ 1 $ unit. In one operation, you fold each corner of the square to the center of the paper, thus forming another square with a side length equal to $ \dfrac{1}{\sqrt{2}} $ units. By taking this square as a new square, you do the operation again and repeat this process a total of $ N $ times.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1924C/de3bbf1154da54ac557ac761cc9644c6d1e0f30d.png) Performing operations for $ N = 2 $ .After performing the set of operations, you open the paper with the same side up you started with and see some crease lines on it. Every crease line is one of two types: a mountain or a valley. A mountain is when the paper folds outward, and a valley is when the paper folds inward.

You calculate the sum of the length of all mountain crease lines on the paper and call it $ M $ . Similarly, you calculate for valley crease lines and call it $ V $ . You want to find the value of $ \dfrac{M}{V} $ .

It can be proved that this value can be represented in the form of $ A + B\sqrt{2} $ , where $ A $ and $ B $ are rational numbers. Let this $ B $ be represented as an irreducible fraction $ \dfrac{p}{q} $ , your task is to print $ p*inv(q) $ modulo $ 999\,999\,893 $ (note the unusual modulo), where $ inv(q) $ is the [modular inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse) of $ q $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). Description of the test cases follows.

The only line of each test case contains an integer $ N $ ( $ 1 \leq N \leq 10^9 $ ), the number of operations you perform on the square paper.

## 输出格式

For each test case, print on a new line the required answer.

## 说明/提示

The blue lines in the given figures represent mountain crease lines, and the green lines represent valley crease lines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1924C/656ef1e31fbec994532b6ed88e854868aee0bb9e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1924C/4d56d193615060ea6202f89c8971139a2bc8d811.png)Crease lines after $ 1 $ operation $ (\dfrac{M}{V} = 0) $ .Crease lines after $ 2 $ operations $ (\dfrac{M}{V} = \sqrt{2} - 1) $ .

## 样例 #1

### 输入

```
3
1
2
3
```

### 输出

```
0
1
714285638
```

