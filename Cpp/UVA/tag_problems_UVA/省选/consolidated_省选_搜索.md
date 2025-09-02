---
title: "方块消除 Blocks"
layout: "post"
diff: 省选/NOI-
pid: UVA10559
tag: ['搜索', '记忆化搜索', '区间 DP']
---

# 方块消除 Blocks

## 题目描述

有 $n$ 个带有颜色的方块，没消除一段长度为x的连续的相同颜色的方块可以得到 $x^2$ 的分数，让你用一种最优的顺序消除所有方块使得得分最多。

## 输入格式

第一行包含测试的次数 $t(1≤t≤15)$ 。

每个案例包含两行。

第一行包含整数 $n(1≤n≤200)$，即框数。

第二行包含 $n$ 个数，代表每个盒子的颜色。数字的大小 $1\sim n$ 内。

## 输出格式

输出 $\texttt{Case x: }y$，其中 $\texttt{x}$ 表示当前是第几组数据，$y$ 表示答案。

## 样例 #1

### 输入

```
2
9
1 2 2 2 2 3 3 3 1
1
1
```

### 输出

```
Case 1: 29
Case 2: 1
```



---

---
title: "Sharing Chocolate"
layout: "post"
diff: 省选/NOI-
pid: UVA1099
tag: ['搜索', '记忆化搜索', '状态合并']
---

# Sharing Chocolate

## 题目描述

（摘自《算法竞赛入门经典训练指南》，刘汝佳 陈峰 著）

给出一块长为 $x$, 宽为 $y$ 的矩形巧克力，每次操作可以沿一条直线把一块巧克力切割成两块长宽均为整数的巧克力（一次不能同时切割多块巧克力）。 

问：是否可以经过若干次操作得到 $n$ 块面积分别为 $a_1, a_2, ..., a_n$ 的巧克力。

## 输入格式

输入包含若干组数据：

每组数据第一行为一个整数 $n(1 \leq n \leq 15)$;

第二行两个整数 $x,y(1 \leq x, y \leq 100)$;

第三行 $n$ 个整数 $a_1,a_2, ... ,a_n$。

输入结束标志为 $n = 0$。

## 输出格式

对于每组数据，如果切割成功，输出 `Yes`，否则输出 `No`

## 样例 #1

### 输入

```
4
3 4
6 3 2 1
2
2 3
1 5
0
```

### 输出

```
Case 1: Yes
Case 2: No
```



---

---
title: "编辑书稿 Editing a Book"
layout: "post"
diff: 省选/NOI-
pid: UVA11212
tag: ['搜索', '深度优先搜索 DFS', '剪枝']
---

# 编辑书稿 Editing a Book

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2153

[PDF](https://uva.onlinejudge.org/external/112/p11212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/cb36674ea3b096f313832bf9d1662a62d42ac8f2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/22e9d9ac532d783c01ab518c2e636f8cb7ea6eec.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/9f3b00f1af2070ad6d631ffe71eb64da0a7d7b6f.png)

## 样例 #1

### 输入

```
6
2 4 1 5 3 6
5
3 4 5 1 2
0
```

### 输出

```
Case 1: 2
Case 2: 1
```



---

---
title: "Gokigen Naname谜题 Gokigen Naname"
layout: "post"
diff: 省选/NOI-
pid: UVA11694
tag: ['搜索', '并查集', '深度优先搜索 DFS']
---

# Gokigen Naname谜题 Gokigen Naname

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2741

[PDF](https://uva.onlinejudge.org/external/116/p11694.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/2821a2ff4c94a298109d6239ae84f49273f2c058.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/9c24649ccdd7cee6a77e317317cbe288310a0ac8.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/c93452858027f71971ba0f8875eec90de1b0dfe0.png)

## 样例 #1

### 输入

```
3
1.1.
...0
.3..
..2.
5
.21...
..33.0
......
..33..
0..33.
....11
```

### 输出

```
\//
\\\
/\/
/\\//
//\\\
\\\//
\/\\/
///\\
```



---

---
title: "Race to 1"
layout: "post"
diff: 省选/NOI-
pid: UVA11762
tag: ['搜索', '素数判断,质数,筛法', '期望']
---

# Race to 1

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2862

[PDF](https://uva.onlinejudge.org/external/117/p11762.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/b1ef1b689a23762fedd48e6bac11ed55518ccb60.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/a9e8aa18a999254778b847f800ff15db6efad8e6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/2f64db9ff88189d3cfead67b6fe9a973785d0c8c.png)

## 样例 #1

### 输入

```
3
1
3
13
```

### 输出

```
Case 1: 0.0000000000
Case 2: 2.0000000000
Case 3: 6.0000000000
```



---

---
title: "Pushing Boxes"
layout: "post"
diff: 省选/NOI-
pid: UVA589
tag: ['广度优先搜索 BFS']
---

# Pushing Boxes

## 题目描述

### 题面翻译

想象你站在一个二维的迷宫里，迷宫由 $R$ 列 $C$ 行共 $R\times C$ 个方格组成，有些方格里是岩石（所以你与箱子不能走到这些格子上），而另外的则是空格子。你可以在一个空格子上向北（上）、南（下）、东（右）、西（左）移动到另外一个相邻的空格子上，这个操作叫做**步行**。

有一个空格子上放着一个箱子，你可以站在盒子旁边，向盒子的方向移动，使得你和箱子共同平移一格（当然平移到的地方不能有岩石）。我们把这样的操作叫做**推**。你只能用推的方式来移动箱子，这意味着，如果你把箱子推到了死角里，你就无法将它推出来了。

现在给定你的起始坐标、箱子的起始坐标和箱子要被推到的坐标，请你找出一个最优的推箱子的操作序列，或报告无解。具体地说：

1. 这个操作序列的**推**操作的次数是最少的。

2. 在满足 (1) 的条件下，若存在不止一个操作序列，则要求操作序列的**总操作次数**（包括**步行**操作和**推**操作）最少。

3. 若在满足 (1) (2) 的条件下，操作序列仍然不唯一，任意输出一个均可。

## 输入格式

**本题存在多组数据。**

对于每组数据，第一行是两个整数 $R,C$，描述迷宫的行数和列数。

接下来 $R$ 行，每行 $C$ 个字符，每个字符描述一个格子：

- `#` 表示有岩石的格子。
- `.` 表示空格子。
- `B` 表示箱子初始位置。**这是一个空格子。**
- `S` 表示你的初始位置。**这是一个空格子。**
- `T` 表示箱子目标位置。**这是一个空格子。**

每个测试点以 $R=C=0$ 结尾，无需处理该组数据。

## 输出格式

对于每组数据，第一行是一个字符串 `Maze #d`，其中 **$\boldsymbol{d}$ 表示这是第几组数据。**

如果无解，在第二行输出 `Impossible`.

否则输出一个符合题目要求的最优的（见上）的操作序列。具体地说：

用大写的 `N`（北）、`S`（南）、`E`（东）、`W`（西）表示**推**操作。

用小写的 `n`（北）、`s`（南）、`e`（东）、`w`（西）表示**步行**操作。

**请在两组测试数据之间输出额外的一行空行。**

## 说明/提示

$R,C \leq 20$。

## 样例 #1

### 输入

```
1 7
SB....T
1 7
SB..#.T
7 11
###########
#T##......#
#.#.#..####
#....B....#
#.######..#
#.....S...#
###########
8 4
....
.##.
.#..
.#..
.#.B
.##S
....
###T
0 0
```

### 输出

```
Maze #1
EEEEE

Maze #2
Impossible.

Maze #3
eennwwWWWWeeeeeesswwwwwwwnNN

Maze #4
swwwnnnnnneeesssSSS
```



---

