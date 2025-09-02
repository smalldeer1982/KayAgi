---
title: "HS10RMSY - Check Ramsey"
layout: "post"
diff: 难度0
pid: SP7946
tag: []
---

# HS10RMSY - Check Ramsey

## 题目描述

### 题目背景

Ramsey定理。

$R(k,l)$ 表示Ramsey数，$K(n)$ 表示 $n$ 阶完全图。

（以上不知道无所谓，纯属背景）


给你一张染成红蓝两色的完全图，染成红色或蓝色的概率都接近 $\dfrac{1}{2}$   ，所以你可以认为图中将近有       $\dfrac{n\cdot(n-1)}{4}$   条红边和蓝边。

请你分别求出：

- 顶点个数为 $k$ 的子图的个数，对于每一个子图满足：

	- 这个子图是一个完全图
    
   - 这个子图上所有边都被染成红色。

- 顶点个数为 $l$ 的子图的个数，对于每一个子图满足：

	- 这个子图是一个完全图
    
	- 这个子图上所有边都被染成蓝色。

## 输入格式

第一行给定一个  $T$  表示数据组数。（ $T \le 100$ ）

对于每一组数据，由一个空行开始。

然后输入四个整数 $n,k,l,e$ ，分别表示整张完全图的顶点数、 $k$ 、 $l$ 、染成红色边的数量。（ $3 \le k \le l \le n < 100$ ）

接下来 $e$ 行，每一行表示一条红色的边。（所以完全图剩下的边就是蓝色的）。

注意顶点**下标从0开始**。

## 输出格式

详见样例。

### 样例修复

#### 输入 #1：
```
3

5 3 3 5
0 1
1 2
2 3
3 4
4 0

6 3 3 6
0 1
1 2
2 3
3 4
4 5
5 0

8 3 4 7
0 1
0 2
0 3
0 4
1 2
1 3
2 3
```
#### 输出 #1：
```
Case #1:
The number of blue K(3) is 0 and the number of red K(3) is 0.
Case #2:
The number of blue K(3) is 2 and the number of red K(3) is 0.
Case #3:
The number of blue K(3) is 25 and the number of red K(4) is 1.
```

## 样例 #1

### 输入

```
\n3\n\n5 3 3 5\n0 1\n1 2\n2 3\n3 4\n4 0\n\n6 3 3 6\n0 1\n1 2\n2 3\n3 4\n4 5\n5 0\n\n8 3 4 7\n0 1\n0 2\n0 3\n0 4\n1 2\n1 3\n2 3\n\n
```

### 输出

```
\nCase #1:\nThe number of blue K(3) is 0 and the number of red K(3) is 0.\nCase #2:\nThe number of blue K(3) is 2 and the number of red K(3) is 0.\nCase #3:\nThe number of blue K(3) is 25 and the number of red K(4) is 1.
```

