---
title: "Vanya and Treasure"
layout: "post"
diff: 提高+/省选-
pid: CF677D
tag: []
---

# Vanya and Treasure

## 题目描述

Vanya is in the palace that can be represented as a grid $ n×m $ . Each room contains a single chest, an the room located in the $ i $ -th row and $ j $ -th columns contains the chest of type $ a_{ij} $ . Each chest of type $ x<=p-1 $ contains a key that can open any chest of type $ x+1 $ , and all chests of type $ 1 $ are not locked. There is exactly one chest of type $ p $ and it contains a treasure.

Vanya starts in cell $ (1,1) $ (top left corner). What is the minimum total distance Vanya has to walk in order to get the treasure? Consider the distance between cell $ (r_{1},c_{1}) $ (the cell in the row $ r_{1} $ and column $ c_{1} $ ) and $ (r_{2},c_{2}) $ is equal to $ |r_{1}-r_{2}|+|c_{1}-c_{2}| $ .

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ p $ ( $ 1<=n,m<=300,1<=p<=n·m $ ) — the number of rows and columns in the table representing the palace and the number of different types of the chests, respectively.

Each of the following $ n $ lines contains $ m $ integers $ a_{ij} $ ( $ 1<=a_{ij}<=p $ ) — the types of the chests in corresponding rooms. It's guaranteed that for each $ x $ from $ 1 $ to $ p $ there is at least one chest of this type (that is, there exists a pair of $ r $ and $ c $ , such that $ a_{rc}=x $ ). Also, it's guaranteed that there is exactly one chest of type $ p $ .

## 输出格式

Print one integer — the minimum possible total distance Vanya has to walk in order to get the treasure from the chest of type $ p $ .

## 样例 #1

### 输入

```
3 4 3
2 1 1 1
1 1 1 1
2 1 1 3

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 3 9
1 3 5
8 9 7
4 6 2

```

### 输出

```
22

```

## 样例 #3

### 输入

```
3 4 12
1 2 3 4
8 7 6 5
9 10 11 12

```

### 输出

```
11

```

