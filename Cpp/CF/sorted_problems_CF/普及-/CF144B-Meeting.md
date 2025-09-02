---
title: "Meeting"
layout: "post"
diff: 普及-
pid: CF144B
tag: []
---

# Meeting

## 题目描述

The Super Duper Secret Meeting of the Super Duper Secret Military Squad takes place in a Super Duper Secret Place. The place is an infinite plane with introduced Cartesian coordinate system. The meeting table is represented as a rectangle whose sides are parallel to the coordinate axes and whose vertexes are located at the integer points of the plane. At each integer point which belongs to the table perimeter there is a chair in which a general sits.

Some points on the plane contain radiators for the generals not to freeze in winter. Each radiator is characterized by the number $ r_{i} $ — the radius of the area this radiator can heat. That is, if the distance between some general and the given radiator is less than or equal to $ r_{i} $ , than the general feels comfortable and warm. Here distance is defined as Euclidean distance, so the distance between points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF144B/db1ba0d5909a3b47109b2e5f65fe13400ae1bd9a.png)

Each general who is located outside the radiators' heating area can get sick. Thus, you should bring him a warm blanket. Your task is to count the number of warm blankets you should bring to the Super Duper Secret Place.

The generals who are already comfortable do not need a blanket. Also the generals never overheat, ever if they are located in the heating area of several radiators. The radiators can be located at any integer points on the plane, even inside the rectangle (under the table) or on the perimeter (directly under some general). Even in this case their radius does not change.

## 输入格式

The first input line contains coordinates of two opposite table corners $ x_{a} $ , $ y_{a} $ , $ x_{b} $ , $ y_{b} $ ( $ x_{a}≠x_{b},y_{a}≠y_{b}) $ . The second line contains integer $ n $ — the number of radiators ( $ 1<=n<=10^{3} $ ). Then $ n $ lines contain the heaters' coordinates as " $ x_{i} $ $ y_{i} $ $ r_{i} $ ", the numbers are separated by spaces. All input data numbers are integers. The absolute value of all coordinates does not exceed $ 1000 $ , $ 1<=r_{i}<=1000 $ . Several radiators can be located at the same point.

## 输出格式

Print the only number — the number of blankets you should bring.

## 说明/提示

In the first sample the generals are sitting at points: $ (2,2) $ , $ (2,3) $ , $ (2,4) $ , $ (2,5) $ , $ (3,2) $ , $ (3,5) $ , $ (4,2) $ , $ (4,3) $ , $ (4,4) $ , $ (4,5) $ . Among them, 4 generals are located outside the heating range. They are the generals at points: $ (2,5) $ , $ (3,5) $ , $ (4,4) $ , $ (4,5) $ .

In the second sample the generals are sitting at points: $ (5,2) $ , $ (5,3) $ , $ (6,2) $ , $ (6,3) $ . All of them are located inside the heating range.

## 样例 #1

### 输入

```
2 5 4 2
3
3 1 2
5 3 1
1 3 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 2 6 3
2
6 2 2
6 5 3

```

### 输出

```
0

```

