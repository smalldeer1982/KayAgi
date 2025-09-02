---
title: "Census"
layout: "post"
diff: 省选/NOI-
pid: UVA11297
tag: ['线段树', '未知标签231']
---

# Census

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2272

[PDF](https://uva.onlinejudge.org/external/112/p11297.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11297/dcd5caafdceb17224df6ccc10085a992416eab82.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11297/cee81df1c08070576dd90be67eb8b5af4a2692c0.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11297/70670c305ce57048872cff5dbe6fe7d179bc2897.png)

## 样例 #1

### 输入

```
5
1 2 3 4 5
0 9 2 1 3
0 2 3 4 1
0 1 2 4 5
8 5 3 1 4
4
q 1 1 2 3
c 2 3 10
q 1 1 5 5
q 1 2 2 2
```

### 输出

```
9 0
10 0
9 2
```



---

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

