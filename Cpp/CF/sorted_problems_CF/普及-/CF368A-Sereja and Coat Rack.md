---
title: "Sereja and Coat Rack"
layout: "post"
diff: 普及-
pid: CF368A
tag: []
---

# Sereja and Coat Rack

## 题目描述

Sereja owns a restaurant for $ n $ people. The restaurant hall has a coat rack with $ n $ hooks. Each restaurant visitor can use a hook to hang his clothes on it. Using the $ i $ -th hook costs $ a_{i} $ rubles. Only one person can hang clothes on one hook.

Tonight Sereja expects $ m $ guests in the restaurant. Naturally, each guest wants to hang his clothes on an available hook with minimum price (if there are multiple such hooks, he chooses any of them). However if the moment a guest arrives the rack has no available hooks, Sereja must pay a $ d $ ruble fine to the guest.

Help Sereja find out the profit in rubles (possibly negative) that he will get tonight. You can assume that before the guests arrive, all hooks on the rack are available, all guests come at different time, nobody besides the $ m $ guests is visiting Sereja's restaurant tonight.

## 输入格式

The first line contains two integers $ n $ and $ d $ $ (1<=n,d<=100) $ . The next line contains integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ $ (1<=a_{i}<=100) $ . The third line contains integer $ m $ $ (1<=m<=100) $ .

## 输出格式

In a single line print a single integer — the answer to the problem.

## 说明/提示

In the first test both hooks will be used, so Sereja gets $ 1+2=3 $ rubles.

In the second test both hooks will be used but Sereja pays a fine $ 8 $ times, so the answer is $ 3-8=-5 $ .

## 样例 #1

### 输入

```
2 1
2 1
2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2 1
2 1
10

```

### 输出

```
-5

```

