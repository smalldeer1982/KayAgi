---
title: "Jeopardy of Dropped Balls"
layout: "post"
diff: 普及/提高-
pid: CF1575J
tag: []
---

# Jeopardy of Dropped Balls

## 题目描述

Mr. Chanek has a new game called Dropping Balls. Initially, Mr. Chanek has a grid $ a $ of size $ n \times m $

Each cell $ (x,y) $ contains an integer $ a_{x,y} $ denoting the direction of how the ball will move.

- $ a_{x,y}=1 $ — the ball will move to the right (the next cell is $ (x, y + 1) $ );
- $ a_{x,y}=2 $ — the ball will move to the bottom (the next cell is $ (x + 1, y) $ );
- $ a_{x,y}=3 $ — the ball will move to the left (the next cell is $ (x, y - 1) $ ).

Every time a ball leaves a cell $ (x,y) $ , the integer $ a_{x,y} $ will change to $ 2 $ . Mr. Chanek will drop $ k $ balls sequentially, each starting from the first row, and on the $ c_1, c_2, \dots, c_k $ -th ( $ 1 \leq c_i \leq m $ ) columns.

Determine in which column each ball will end up in (position of the ball after leaving the grid).

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ k $ ( $ 1 \leq n, m \leq 1000 $ , $ 1 \leq k \leq 10^5 $ ) — the size of the grid and the number of balls dropped by Mr. Chanek.

The $ i $ -th of the next $ n $ lines contains $ m $ integers $ a_{i,1},a_{i,2},\ldots,a_{i,m} $ ( $ 1 \leq a_{i,j} \leq 3 $ ). It will satisfy $ a_{i, 1} \ne 3 $ and $ a_{i, m} \ne 1 $ .

The next line contains $ k $ integers $ c_1, c_2, \ldots, c_k $ ( $ 1 \leq c_i \leq m $ ) — the balls' column positions dropped by Mr. Chanek sequentially.

## 输出格式

Output $ k $ integers — the $ i $ -th integer denoting the column where the $ i $ -th ball will end.

## 说明/提示

In the first example, the first ball will drop as follows. Note that the cell $ (1, 1) $ will change direction to the bottom direction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575J/fa2adb81fdf96ce1b92e46629bbcb5cf70e88c62.png)The second and third balls will drop as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575J/7c28f503603add2e57bd518e7c027aa1a32b9f99.png)All balls will be dropped from the first row and on the $ c_1, c_2, \dots, c_k $ -th columns respectively. A ball will stop dropping once it leaves the grid.

## 样例 #1

### 输入

```
5 5 3
1 2 3 3 3
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
1 2 1
```

### 输出

```
2 2 1
```

## 样例 #2

### 输入

```
1 2 2
1 3
1 2
```

### 输出

```
1 2
```

