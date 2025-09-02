---
title: "Hopscotch"
layout: "post"
diff: 普及-
pid: CF141B
tag: []
---

# Hopscotch

## 题目描述

So nearly half of the winter is over and Maria is dreaming about summer. She's fed up with skates and sleds, she was dreaming about Hopscotch all night long. It's a very popular children's game. The game field, the court, looks as is shown in the figure (all blocks are square and are numbered from bottom to top, blocks in the same row are numbered from left to right). Let us describe the hopscotch with numbers that denote the number of squares in the row, staring from the lowest one: 1-1-2-1-2-1-2-(1-2)..., where then the period is repeated (1-2).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF141B/3cab0cfd180f2a7ceceec93813314c6b7ddd8ea0.png)The coordinate system is defined as shown in the figure. Side of all the squares are equal and have length $ a $ .

Maria is a very smart and clever girl, and she is concerned with quite serious issues: if she throws a stone into a point with coordinates $ (x,y) $ , then will she hit some square? If the answer is positive, you are also required to determine the number of the square.

It is believed that the stone has fallen into the square if it is located strictly inside it. In other words a stone that has fallen on the square border is not considered a to hit a square.

## 输入格式

The only input line contains three integers: $ a $ , $ x $ , $ y $ , where $ a $ ( $ 1<=a<=100 $ ) is the side of the square, $ x $ and $ y $ ( $ -10^{6}<=x<=10^{6},0<=y<=10^{6} $ ) are coordinates of the stone.

## 输出格式

Print the number of the square, inside which the stone fell. If the stone is on a border of some stone or outside the court, print "-1" without the quotes.

## 样例 #1

### 输入

```
1 0 0

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
3 1 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 0 10

```

### 输出

```
5

```

## 样例 #4

### 输入

```
3 0 7

```

### 输出

```
-1

```

## 样例 #5

### 输入

```
3 4 0

```

### 输出

```
-1

```

