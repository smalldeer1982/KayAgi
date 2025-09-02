---
title: "Stripes"
layout: "post"
diff: 普及-
pid: CF1742C
tag: []
---

# Stripes

## 题目描述

On an $ 8 \times 8 $ grid, some horizontal rows have been painted red, and some vertical columns have been painted blue, in some order. The stripes are drawn sequentially, one after the other. When the stripe is drawn, it repaints all the cells through which it passes.

Determine which color was used last.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1742C/6f423ce4b1dd07561098c185bf230d882c12b3e9.png)The red stripe was painted after the blue one, so the answer is R.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \leq t \leq 4000 $ ) — the number of test cases. The description of test cases follows. There is an empty line before each test case.

Each test case consists of $ 8 $ lines, each containing $ 8 $ characters. Each of these characters is either 'R', 'B', or '.', denoting a red square, a blue square, and an unpainted square, respectively.

It is guaranteed that the given field is obtained from a colorless one by drawing horizontal red rows and vertical blue columns.

At least one stripe is painted.

## 输出格式

For each test case, output 'R' if a red stripe was painted last, and 'B' if a blue stripe was painted last (without quotes).

## 说明/提示

The first test case is pictured in the statement.

In the second test case, the first blue column is painted first, then the first and last red rows, and finally the last blue column. Since a blue stripe is painted last, the answer is B.

## 样例 #1

### 输入

```
4


....B...
....B...
....B...
RRRRRRRR
....B...
....B...
....B...
....B...


RRRRRRRB
B......B
B......B
B......B
B......B
B......B
B......B
RRRRRRRB


RRRRRRBB
.B.B..BB
RRRRRRBB
.B.B..BB
.B.B..BB
RRRRRRBB
.B.B..BB
.B.B..BB


........
........
........
RRRRRRRR
........
........
........
........
```

### 输出

```
R
B
B
R
```

