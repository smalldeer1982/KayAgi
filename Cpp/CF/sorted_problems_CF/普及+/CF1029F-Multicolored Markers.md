---
title: "Multicolored Markers"
layout: "post"
diff: 普及+/提高
pid: CF1029F
tag: ['数学', '枚举']
---

# Multicolored Markers

## 题目描述

There is an infinite board of square tiles. Initially all tiles are white.

Vova has a red marker and a blue marker. Red marker can color $ a $ tiles. Blue marker can color $ b $ tiles. If some tile isn't white then you can't use marker of any color on it. Each marker must be drained completely, so at the end there should be exactly $ a $ red tiles and exactly $ b $ blue tiles across the board.

Vova wants to color such a set of tiles that:

- they would form a rectangle, consisting of exactly $ a+b $ colored tiles;
- all tiles of at least one color would also form a rectangle.

Here are some examples of correct colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)Here are some examples of incorrect colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)Among all correct colorings Vova wants to choose the one with the minimal perimeter. What is the minimal perimeter Vova can obtain?

It is guaranteed that there exists at least one correct coloring.

## 输入格式

A single line contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le 10^{14} $ ) — the number of tiles red marker should color and the number of tiles blue marker should color, respectively.

## 输出格式

Print a single integer — the minimal perimeter of a colored rectangle Vova can obtain by coloring exactly $ a $ tiles red and exactly $ b $ tiles blue.

It is guaranteed that there exists at least one correct coloring.

## 说明/提示

The first four examples correspond to the first picture of the statement.

Note that for there exist multiple correct colorings for all of the examples.

In the first example you can also make a rectangle with sides $ 1 $ and $ 8 $ , though its perimeter will be $ 18 $ which is greater than $ 8 $ .

In the second example you can make the same resulting rectangle with sides $ 3 $ and $ 4 $ , but red tiles will form the rectangle with sides $ 1 $ and $ 3 $ and blue tiles will form the rectangle with sides $ 3 $ and $ 3 $ .

## 样例 #1

### 输入

```
4 4

```

### 输出

```
12

```

## 样例 #2

### 输入

```
3 9

```

### 输出

```
14

```

## 样例 #3

### 输入

```
9 3

```

### 输出

```
14

```

## 样例 #4

### 输入

```
3 6

```

### 输出

```
12

```

## 样例 #5

### 输入

```
506 2708

```

### 输出

```
3218

```

