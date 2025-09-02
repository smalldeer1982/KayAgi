---
title: "Mixing Invitations"
layout: "post"
diff: 普及+/提高
pid: UVA11282
tag: ['数学', '组合数学']
---

# Mixing Invitations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2257

[PDF](https://uva.onlinejudge.org/external/112/p11282.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/110870a90869e55e6ec3515fe755ec5b158955d7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/b4e7fdf072d0155249bf58edb79207686db0d3d3.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/47758b1841a784e0d76de0fe038a80510f818f87.png)

## 样例 #1

### 输入

```
3 2
4 1
4 4
```

### 输出

```
5
17
24
```



---

---
title: "Chess Queen"
layout: "post"
diff: 普及+/提高
pid: UVA11538
tag: ['数学', '枚举', '组合数学']
---

# Chess Queen

## 题目描述

你一定知道国际象棋是怎么玩的，以及皇后是怎么运作的吧。如果两个皇后在同一列，同一行或者同一对角线上，她们就会互相攻击。

例如，有两个皇后（一白一黑）放置在$2×2$的棋盘上，那么有$12$中放置方式可以使她们互相攻击。如下图所示。（见PDF版题面）

给出棋盘的大小，请你计算有多少种放置皇后的方式，可以使她们互相攻击。

## 输入格式

输入文件包含至多$5,000$行，每行包含两个非负整数$M,N(1< M,N \leq 10^6 )$，表示棋盘的规格为$M × N$。输入以$M=N=0$结束。

## 输出格式

对每组数据输出一行，表示可以使两个皇后互相攻击的放置方案数。

保证答案在$64$位有符号整数范围内。

Translation provided by @Zaoaa

## 样例 #1

### 输入

```
2 2
100 223
2300 1000
0 0
```

### 输出

```
12
10907100
11514134000
```



---

