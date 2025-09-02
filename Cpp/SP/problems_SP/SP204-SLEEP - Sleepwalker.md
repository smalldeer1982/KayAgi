---
title: "SLEEP - Sleepwalker"
layout: "post"
diff: 难度0
pid: SP204
tag: []
---

# SLEEP - Sleepwalker

## 题目描述

在一个建筑物的屋顶上，铺设着一个大小为 $3^k \times 3^k$ 的正方形平面，这个平面的边缘与南北和东西方向平行。屋顶上覆盖着许多 $1 \times 1$ 的正方形瓦片，其中有一块瓦片被移除，形成了一个洞，可以让人掉下去。瓦片按照矩形网格排列，因此可以用坐标来表示位置。最西南角的瓦片坐标是 $(1,1)$，坐标的第一位沿东向增加，第二位沿北向增加。

一个梦游者在屋顶上游荡，他每一步可以从当前瓦片移动到东(E)、西(W)、南(S)或北(N)方向的相邻瓦片。梦游者从西南角的瓦片开始移动。他移动路径的描述是一个由字母 N、S、E、W 组成的字符串 $d_k$，分别表示向北、南、东和西移动。例如，当 $k = 1$ 时，路径描述为：

$$ d_1 = \text{EENNWSWN} $$

当 $k = 2$ 时，路径描述是：

$$ d_2 = \text{NNEESWSEENNEESWSEEEENNWSWNNEENNWSWNNEENNWSWNWWWSSENESSSSWWNENWWSSWNENWNEENNWSWN} $$

（可以参考示意图，了解梦游者在 $3 \times 3$ 或 $9 \times 9$ 大小的屋顶上如何行走）。通常情况下，如果 $k \geq 1$，描述梦游者在 $3^{k+1} \times 3^{k+1}$ 大小屋顶上的路径的字符串为：

$$ d_{k+1} = a(d_k) \text{E} a(d_k) \text{E} d_k \text{N} d_k \text{N} d_k \text{W} c(d_k) \text{S} b(d_k) \text{W} b(d_k) \text{N} d_k $$

函数 **a**、**b** 和 **c** 对应以下方向的字母置换：
```
a: E->N W->S N->E S->W 
b: E->S W->N N->W S->E 
c: E->W W->E N->S S->N 
```
例如，$a(\text{SEN})=\text{WNE}$，$b(\text{SEN})=\text{ESW}$，$c(\text{SEN})=\text{NWS}$。

我们在梦游者站在坐标 $(u_1, u_2)$ 的瓦片上时开始观察。梦游者需要经过多少步才能掉到坐标为 $(v_1, v_2)$ 的洞里？

## 输入格式

第一行为测试用例的数量 $t$，接下来是 $t$ 个测试用例，每个测试用例之间用空行分隔。每个测试用例的第一行为一个整数 $k$，表示屋顶的大小 ($3^k \times 3^k$)，满足 $1 \leq k \leq 60$。接下来两行，每行包含两个用空格分隔的自然数 $x, y$，坐标范围为 $1 \leq x \leq 3^k$ 和 $1 \leq y \leq 3^k$。第二行是梦游者当前站立的瓦片的坐标，第三行是洞的坐标。所有输入数据确保梦游者最终会走入洞中。

## 输出格式

对于每个测试用例，输出一行，表示梦游者到达洞口所需的步数。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
The number of test cases t is in the first line of input, then t test cases follow separated by an empty line.
In the first line of each test case one integer k,

1
```

### 输出

```
The only line of output for each test case should contain the number of steps on
the sleepwalker's path to the hole.


Example

Sample input:
1
2
3 2
7 2

Sample output
20
```

## 样例 #2

### 输入

```
1
2
3 2
7 2
```

### 输出

```
None
```

