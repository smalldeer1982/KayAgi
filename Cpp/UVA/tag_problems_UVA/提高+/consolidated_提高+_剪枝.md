---
title: "Raising the Roof"
layout: "post"
diff: 提高+/省选-
pid: UVA1065
tag: ['剪枝']
---

# Raising the Roof

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=245&page=show_problem&problem=3506

[PDF](https://uva.onlinejudge.org/external/10/p1065.pdf)



---

---
title: "旋转游戏 The Rotation Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1343
tag: ['剪枝', '启发式迭代加深搜索 IDA*', '构造']
---

# 旋转游戏 The Rotation Game

## 题目描述

　　如图 $1$ 所示，有一个 “#” 形的棋盘，上面有 $1,2,3$ 三种数字各 $8$ 个。给定 $8$ 种操作，分别为图中的 $\text{A}\sim \text{H}$。这些操作会按照图中字母与箭头所指明的方向，把一条长度为 $8$ 的序列循环移动 $1$ 个单位。例如下图最左边的 “#” 形棋盘执行操作 $\text{A}$ 时，会变为图中间的 “#” 形棋盘，再执行操作 $\text{C}$ 后会变为图中最右边的 “#” 形棋盘。
![](https://cdn.luogu.org/upload/pic/40731.png)
$$\text{图 1}$$
　　现给定一个初始状态，请使用最少的操作次数，使 “#” 形棋盘最中间的 $8$ 个格子里的数字相同。

## 输入格式

　　输入包括不超过 $30$ 组测试数据。每个测试数据只包括一行，包含 $24$ 个整数，每相邻两个整数之间用 $1$ 个空格隔开，表示这个 “#” 形棋盘的初始状态。（这些整数的排列顺序是从上至下，同一行的从左至右。例如 $\text{1 1 1 1 3 2 3 2 3 1 3 2 2 3 1 2 2 2 3 1 2 1 3 3}$ 表示图 $1$ 最左边的状态。）每两组测试数据之间没有换行符。输入文件以一行 $0$ 结束。

## 输出格式

　　对于每组测试数据，输出两行。第一行用字符 $\text{A}\sim \text{H}$ 输出操作的方法，**每两个操作字符之间没有空格分开**，如果不需要任何步数，输出 `No moves needed`。第二行输出最终状态中最中间的 $8$ 个格子里的数字。如果有多组解，输出操作次数最少的一组解；如果仍有多组解，输出字典序最小的一组。任意相邻两组测试数据的输出之间不需输出换行符。



---

---
title: "Sudoku Extension"
layout: "post"
diff: 提高+/省选-
pid: UVA1461
tag: ['模拟', '搜索', '剪枝']
---

# Sudoku Extension

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4207

[PDF](https://uva.onlinejudge.org/external/14/p1461.pdf)



---

---
title: "Addition Chains"
layout: "post"
diff: 提高+/省选-
pid: UVA529
tag: ['搜索', '枚举', '剪枝', '搜索']
---

# Addition Chains

## 题目描述

一个与 $n$ 有关的整数加成序列 $<a_0,a_1,a_2,...,a_m>$ 满足以下四个条件：  
 $1.a_0=1$   
 $2.a_m=n$   
 $3.a_0<a_1<a_2<...<a_{m-1}<a_m$   
 $4.$ 对于每一个 $k(1≤k≤m)$ 都存在有两个整数 $i$ 和 $j(0≤i,j≤k-1,i$ 和 $j$ 可以相等 $)$ ，使得 $a_k=a_i+a_j$   
你的任务是：给定一个整数 $n$ ,找出符合上述四个条件的长度最小的整数加成序列。如果有多个满足要求的答案，只需要输出任意一个解即可。  
举个例子，序列 $<1,2,3,5>$ 和 $<1,2,4,5>$ 均为 $n=5$ 时的解。

## 输入格式

输入包含多组数据。每组数据仅一行包含一个整数 $n(1≤n≤10000)$ 。在最后一组数据之后是一个 $0$ 。

## 输出格式

对于每组数据，输出一行所求的整数加成序列，每个整数之间以空格隔开。

感谢@Iowa_BattleShip 提供的翻译

## 样例 #1

### 输入

```
5
7
12
15
77
0
```

### 输出

```
1 2 4 5
1 2 4 6 7
1 2 4 8 12
1 2 4 5 10 15
1 2 4 8 9 17 34 68 77
```



---

