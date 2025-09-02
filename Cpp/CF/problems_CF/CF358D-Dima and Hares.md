---
title: "Dima and Hares"
layout: "post"
diff: 提高+/省选-
pid: CF358D
tag: []
---

# Dima and Hares

## 题目描述

Dima liked the present he got from Inna very much. He liked the present he got from Seryozha even more.

Dima felt so grateful to Inna about the present that he decided to buy her $ n $ hares. Inna was very happy. She lined up the hares in a row, numbered them from 1 to $ n $ from left to right and started feeding them with carrots. Inna was determined to feed each hare exactly once. But in what order should she feed them?

Inna noticed that each hare radiates joy when she feeds it. And the joy of the specific hare depends on whether Inna fed its adjacent hares before feeding it. Inna knows how much joy a hare radiates if it eats when either both of his adjacent hares are hungry, or one of the adjacent hares is full (that is, has been fed), or both of the adjacent hares are full. Please note that hares number 1 and $ n $ don't have a left and a right-adjacent hare correspondingly, so they can never have two full adjacent hares.

Help Inna maximize the total joy the hares radiate. :)

## 输入格式

The first line of the input contains integer $ n $ $ (1<=n<=3000) $ — the number of hares. Then three lines follow, each line has $ n $ integers. The first line contains integers $ a_{1} $ $ a_{2} $ $ ... $ $ a_{n} $ . The second line contains $ b_{1},b_{2},...,b_{n} $ . The third line contains $ c_{1},c_{2},...,c_{n} $ . The following limits are fulfilled: $ 0<=a_{i},b_{i},c_{i}<=10^{5} $ .

Number $ a_{i} $ in the first line shows the joy that hare number $ i $ gets if his adjacent hares are both hungry. Number $ b_{i} $ in the second line shows the joy that hare number $ i $ radiates if he has exactly one full adjacent hare. Number $ с_{i} $ in the third line shows the joy that hare number $ i $ radiates if both his adjacent hares are full.

## 输出格式

In a single line, print the maximum possible total joy of the hares Inna can get by feeding them.

## 样例 #1

### 输入

```
4
1 2 3 4
4 3 2 1
0 1 1 0

```

### 输出

```
13

```

## 样例 #2

### 输入

```
7
8 5 7 6 1 8 9
2 7 9 5 4 3 1
2 3 3 4 1 1 3

```

### 输出

```
44

```

## 样例 #3

### 输入

```
3
1 1 1
1 2 1
1 1 1

```

### 输出

```
4

```

