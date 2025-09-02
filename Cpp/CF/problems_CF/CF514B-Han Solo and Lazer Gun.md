---
title: "Han Solo and Lazer Gun"
layout: "post"
diff: 普及/提高-
pid: CF514B
tag: []
---

# Han Solo and Lazer Gun

## 题目描述

There are $ n $ Imperial stormtroopers on the field. The battle field is a plane with Cartesian coordinate system. Each stormtrooper is associated with his coordinates $ (x,y) $ on this plane.

Han Solo has the newest duplex lazer gun to fight these stormtroopers. It is situated at the point $ (x_{0},y_{0}) $ . In one shot it can can destroy all the stormtroopers, situated on some line that crosses point $ (x_{0},y_{0}) $ .

Your task is to determine what minimum number of shots Han Solo needs to defeat all the stormtroopers.

The gun is the newest invention, it shoots very quickly and even after a very large number of shots the stormtroopers don't have enough time to realize what's happening and change their location.

## 输入格式

The first line contains three integers $ n $ , $ x_{0} $ и $ y_{0} $ ( $ 1<=n<=1000 $ , $ -10^{4}<=x_{0},y_{0}<=10^{4} $ ) — the number of stormtroopers on the battle field and the coordinates of your gun.

Next $ n $ lines contain two integers each $ x_{i} $ , $ y_{i} $ ( $ -10^{4}<=x_{i},y_{i}<=10^{4} $ ) — the coordinates of the stormtroopers on the battlefield. It is guaranteed that no stormtrooper stands at the same point with the gun. Multiple stormtroopers can stand at the same point.

## 输出格式

Print a single integer — the minimum number of shots Han Solo needs to destroy all the stormtroopers.

## 说明/提示

Explanation to the first and second samples from the statement, respectively:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514B/e0665254dc28c85d59225f8c53a8542938957367.png)

## 样例 #1

### 输入

```
4 0 0
1 1
2 2
2 0
-1 -1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 1 2
1 1
1 0

```

### 输出

```
1

```

