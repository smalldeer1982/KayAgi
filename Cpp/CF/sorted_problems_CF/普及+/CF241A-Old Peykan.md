---
title: "Old Peykan"
layout: "post"
diff: 普及+/提高
pid: CF241A
tag: []
---

# Old Peykan

## 题目描述

There are $ n $ cities in the country where the Old Peykan lives. These cities are located on a straight line, we'll denote them from left to right as $ c_{1},c_{2},...,c_{n} $ . The Old Peykan wants to travel from city $ c_{1} $ to $ c_{n} $ using roads. There are $ (n-1) $ one way roads, the $ i $ -th road goes from city $ c_{i} $ to city $ c_{i+1} $ and is $ d_{i} $ kilometers long.

The Old Peykan travels 1 kilometer in 1 hour and consumes 1 liter of fuel during this time.

Each city $ c_{i} $ (except for the last city $ c_{n} $ ) has a supply of $ s_{i} $ liters of fuel which immediately transfers to the Old Peykan if it passes the city or stays in it. This supply refreshes instantly $ k $ hours after it transfers. The Old Peykan can stay in a city for a while and fill its fuel tank many times.

Initially (at time zero) the Old Peykan is at city $ c_{1} $ and $ s_{1} $ liters of fuel is transferred to it's empty tank from $ c_{1} $ 's supply. The Old Peykan's fuel tank capacity is unlimited. Old Peykan can not continue its travel if its tank is emptied strictly between two cities.

Find the minimum time the Old Peykan needs to reach city $ c_{n} $ .

## 输入格式

The first line of the input contains two space-separated integers $ m $ and $ k $ $ (1<=m,k<=1000) $ . The value $ m $ specifies the number of roads between cities which is equal to $ n-1 $ .

The next line contains $ m $ space-separated integers $ d_{1},d_{2},...,d_{m} $ $ (1<=d_{i}<=1000) $ and the following line contains $ m $ space-separated integers $ s_{1},s_{2},...,s_{m} $ $ (1<=s_{i}<=1000) $ .

## 输出格式

In the only line of the output print a single integer — the minimum time required for The Old Peykan to reach city $ c_{n} $ from city $ c_{1} $ .

## 说明/提示

In the second sample above, the Old Peykan stays in $ c_{1} $ for 3 hours.

## 样例 #1

### 输入

```
4 6
1 2 5 2
2 3 3 4

```

### 输出

```
10

```

## 样例 #2

### 输入

```
2 3
5 6
5 5

```

### 输出

```
14

```

