---
title: "Kitahara Haruki's Gift"
layout: "post"
diff: 入门
pid: CF433A
tag: []
---

# Kitahara Haruki's Gift

## 题目描述

Kitahara Haruki has bought $ n $ apples for Touma Kazusa and Ogiso Setsuna. Now he wants to divide all the apples between the friends.

Each apple weights 100 grams or 200 grams. Of course Kitahara Haruki doesn't want to offend any of his friend. Therefore the total weight of the apples given to Touma Kazusa must be equal to the total weight of the apples given to Ogiso Setsuna.

But unfortunately Kitahara Haruki doesn't have a knife right now, so he cannot split any apple into some parts. Please, tell him: is it possible to divide all the apples in a fair way between his friends?

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=100) $ — the number of apples. The second line contains $ n $ integers $ w_{1},w_{2},...,w_{n} $ ( $ w_{i}=100 $ or $ w_{i}=200 $ ), where $ w_{i} $ is the weight of the $ i $ -th apple.

## 输出格式

In a single line print "YES" (without the quotes) if it is possible to divide all the apples between his friends. Otherwise print "NO" (without the quotes).

## 说明/提示

In the first test sample Kitahara Haruki can give the first and the last apple to Ogiso Setsuna and the middle apple to Touma Kazusa.

## 样例 #1

### 输入

```
3
100 200 100

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4
100 100 100 200

```

### 输出

```
NO

```

