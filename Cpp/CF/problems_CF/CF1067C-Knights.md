---
title: "Knights"
layout: "post"
diff: 省选/NOI-
pid: CF1067C
tag: []
---

# Knights

## 题目描述

Ivan places knights on infinite chessboard. Initially there are $ n $ knights. If there is free cell which is under attack of at least $ 4 $ knights then he places new knight in this cell. Ivan repeats this until there are no such free cells. One can prove that this process is finite. One can also prove that position in the end does not depend on the order in which new knights are placed.

Ivan asked you to find initial placement of exactly $ n $ knights such that in the end there will be at least $ \lfloor \frac{n^{2}}{10} \rfloor $ knights.

## 输入格式

The only line of input contains one integer $ n $ ( $ 1 \le n \le 10^{3} $ ) — number of knights in the initial placement.

## 输出格式

Print $ n $ lines. Each line should contain $ 2 $ numbers $ x_{i} $ and $ y_{i} $ ( $ -10^{9} \le x_{i}, \,\, y_{i} \le 10^{9} $ ) — coordinates of $ i $ -th knight. For all $ i \ne j $ , $ (x_{i}, \,\, y_{i}) \ne (x_{j}, \,\, y_{j}) $ should hold. In other words, all knights should be in different cells.

It is guaranteed that the solution exists.

## 说明/提示

Let's look at second example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1067C/1b1831e33b9c7fd1ae942c44032d9f6c6e603132.png)

Green zeroes are initial knights. Cell $ (3, \,\, 3) $ is under attack of $ 4 $ knights in cells $ (1, \,\, 2) $ , $ (2, \,\, 1) $ , $ (4, \,\, 1) $ and $ (5, \,\, 2) $ , therefore Ivan will place a knight in this cell. Cell $ (4, \,\, 5) $ is initially attacked by only $ 3 $ knights in cells $ (2, \,\, 6) $ , $ (5, \,\, 7) $ and $ (6, \,\, 6) $ . But new knight in cell $ (3, \,\, 3) $ also attacks cell $ (4, \,\, 5) $ , now it is attacked by $ 4 $ knights and Ivan will place another knight in this cell. There are no more free cells which are attacked by $ 4 $ or more knights, so the process stops. There are $ 9 $ knights in the end, which is not less than $ \lfloor \frac{7^{2}}{10} \rfloor = 4 $ .

## 样例 #1

### 输入

```
4

```

### 输出

```
1 1
3 1
1 5
4 4

```

## 样例 #2

### 输入

```
7

```

### 输出

```
2 1
1 2
4 1
5 2
2 6
5 7
6 6

```

