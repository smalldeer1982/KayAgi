---
title: "Working routine"
layout: "post"
diff: 省选/NOI-
pid: CF706E
tag: []
---

# Working routine

## 题目描述

Vasiliy finally got to work, where there is a huge amount of tasks waiting for him. Vasiliy is given a matrix consisting of $ n $ rows and $ m $ columns and $ q $ tasks. Each task is to swap two submatrices of the given matrix.

For each task Vasiliy knows six integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ , $ d_{i} $ , $ h_{i} $ , $ w_{i} $ , where $ a_{i} $ is the index of the row where the top-left corner of the first rectangle is located, $ b_{i} $ is the index of its column, $ c_{i} $ is the index of the row of the top-left corner of the second rectangle, $ d_{i} $ is the index of its column, $ h_{i} $ is the height of the rectangle and $ w_{i} $ is its width.

It's guaranteed that two rectangles in one query do not overlap and do not touch, that is, no cell belongs to both rectangles, and no two cells belonging to different rectangles share a side. However, rectangles are allowed to share an angle.

Vasiliy wants to know how the matrix will look like after all tasks are performed.

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ q $ ( $ 2<=n,m<=1000 $ , $ 1<=q<=10000 $ ) — the number of rows and columns in matrix, and the number of tasks Vasiliy has to perform.

Then follow $ n $ lines containing $ m $ integers $ v_{i,j} $ ( $ 1<=v_{i,j}<=10^{9} $ ) each — initial values of the cells of the matrix.

Each of the following $ q $ lines contains six integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ , $ d_{i} $ , $ h_{i} $ , $ w_{i} $ ( $ 1<=a_{i},c_{i},h_{i}<=n $ , $ 1<=b_{i},d_{i},w_{i}<=m $ ).

## 输出格式

Print $ n $ lines containing $ m $ integers each — the resulting matrix.

## 样例 #1

### 输入

```
4 4 2
1 1 2 2
1 1 2 2
3 3 4 4
3 3 4 4
1 1 3 3 2 2
3 1 1 3 2 2

```

### 输出

```
4 4 3 3
4 4 3 3
2 2 1 1
2 2 1 1

```

## 样例 #2

### 输入

```
4 2 1
1 1
1 1
2 2
2 2
1 1 4 1 1 2

```

### 输出

```
2 2
1 1
2 2
1 1

```

