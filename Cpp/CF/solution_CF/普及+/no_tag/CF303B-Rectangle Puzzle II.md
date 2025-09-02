# Rectangle Puzzle II

## 题目描述

You are given a rectangle grid. That grid's size is $ n×m $ . Let's denote the coordinate system on the grid. So, each point on the grid will have coordinates — a pair of integers $ (x,y) $ $ (0<=x<=n,0<=y<=m) $ .

Your task is to find a maximum sub-rectangle on the grid $ (x_{1},y_{1},x_{2},y_{2}) $ so that it contains the given point $ (x,y) $ , and its length-width ratio is exactly $ (a,b) $ . In other words the following conditions must hold: $ 0<=x_{1}<=x<=x_{2}<=n $ , $ 0<=y_{1}<=y<=y_{2}<=m $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303B/d25d5fd31cdc2b2671d5f1dca98aadab16b15a21.png).

The sides of this sub-rectangle should be parallel to the axes. And values $ x_{1},y_{1},x_{2},y_{2} $ should be integers.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303B/4f1aa1906686be0387a09dbeae2bf3128e4fc307.png)If there are multiple solutions, find the rectangle which is closest to $ (x,y) $ . Here "closest" means the Euclid distance between $ (x,y) $ and the center of the rectangle is as small as possible. If there are still multiple solutions, find the lexicographically minimum one. Here "lexicographically minimum" means that we should consider the sub-rectangle as sequence of integers $ (x_{1},y_{1},x_{2},y_{2}) $ , so we can choose the lexicographically minimum one.

## 样例 #1

### 输入

```
9 9 5 5 2 1
```

### 输出

```
1 3 9 7
```

## 样例 #2

### 输入

```
100 100 52 50 46 56
```

### 输出

```
17 8 86 92
```

