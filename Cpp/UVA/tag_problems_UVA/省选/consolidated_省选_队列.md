---
title: "Robotruck"
layout: "post"
diff: 省选/NOI-
pid: UVA1169
tag: ['线段树', '单调队列', '队列']
---

# Robotruck

## 题目描述

有n个垃圾，第i个垃圾的坐标为(xi,yi)，重量为wi。有一个机器人，要按照编号从小到大的顺序捡起所有垃圾并扔进垃圾桶（垃圾桶在原点(0,0)）。机器人可以捡起几个垃圾以后一起扔掉，但任何时候其手中的垃圾总重量不能超过最大载重C。两点间的行走距离为曼哈顿距离（即横坐标之差的绝对值加上纵坐标之差的绝对值）。求出机器人行走的最短总路程（一开始，机器人在(0,0)处）。

## 输入格式

输入的第一行为数据组数。每组数据的第一行为最大承重C(1<=C<=100)；第二行为正整数n(1<=n<=100000)，即垃圾的数量；以下n行每行为两个非负整数x,y和一个正整数w，即坐标和重量（重量保证不超过C）。

## 输出格式

对于每组数据，输出总路径的最短长度。

输出每行一个解



---

---
title: "DNA Regions"
layout: "post"
diff: 省选/NOI-
pid: UVA1392
tag: ['单调队列', '枚举', '排序']
---

# DNA Regions

## 题目描述

## 题面
给定两个长度为 $n$ 的字符串 $A$ 和 $B$，满足 $A$ 和 $B$ 都只由大写字母 A、C、G、T 组成。

求一个长度最长的闭区间 $[L,R]$，满足对于 $i \in [L,R]$，有不超过 $p \%$ 的 $i$ 满足 $A_i \neq B_i$。

## 输入格式

包含多组数据。

对于每组数据，第一行为两个整数 $n$ 和 $q$。
接下来两行分别是 $A$ 和 $B$。

结束的标志是 $n=0$。

## 输出格式

对于每组数据，若有解，输出满足条件的区间长度的最大值，若无解，输出`No solution.`。

## 输入输出样例
### 输入
```
14 25
ACCGGTAACGTGAA
ACTGGATACGTAAA
14 24
ACCGGTAACGTGAA
ACTGGATACGTAAA
8 1
AAAAAAAA
CCCCCCCC
8 33
AAACAAAA
CCCCCCCC
0 0

```
### 输出
```
8
7
No solution.
1
```

## 说明/提示

$1 \le n \le 1.5 \times 10^5$，$1 \le p \le 99$。



---

---
title: "Parade"
layout: "post"
diff: 省选/NOI-
pid: UVA1427
tag: ['单调队列', '前缀和', '队列']
---

# Parade

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4173

[PDF](https://uva.onlinejudge.org/external/14/p1427.pdf)



---

