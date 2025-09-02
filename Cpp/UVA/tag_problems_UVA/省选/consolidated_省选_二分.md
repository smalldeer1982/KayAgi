---
title: "矩阵解压 Matrix Decompressing"
layout: "post"
diff: 省选/NOI-
pid: UVA11082
tag: ['网络流', '二分图']
---

# 矩阵解压 Matrix Decompressing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2023

[PDF](https://uva.onlinejudge.org/external/110/p11082.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11082/4bfbadba5826e7df25fe35bb6c563f54e80f8b54.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11082/1c9470803fa67b39a07afe5716e1afb7f904286c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11082/d5eaf050b2d4f97e173703f6c0ab39199cfec3a6.png)

## 样例 #1

### 输入

```
2
3 4
10 31 58
10 20 37 58
3 4
10 31 58
10 20 37 58
```

### 输出

```
Matrix 1
1 6 1 2
1 2 2 16
8 2 14 3
Matrix 2
1 1 1 7
1 1 7 12
8 8 9 2
```



---

---
title: "Halum"
layout: "post"
diff: 省选/NOI-
pid: UVA11478
tag: ['二分', '图论建模', '差分约束']
---

# Halum

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2473

[PDF](https://uva.onlinejudge.org/external/114/p11478.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/fe7bd946fb4e049b4a2acc693bd285a050d606f4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/d8a053537747d36f9bda3b53b2e300f24860c7fb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/59cf14738847dcbac078a3ffdf4966090114e0f4.png)

## 样例 #1

### 输入

```
2 1
1 2 10
2 1
1 2 -10
3 3
1 2 4
2 3 2
3 1 5
4 5
2 3 4
4 2 5
3 4 2
3 1 0
1 2 -1
```

### 输出

```
Infinite
Infinite
3
1
```



---

---
title: "Air Raid"
layout: "post"
diff: 省选/NOI-
pid: UVA1184
tag: ['网络流', '二分图']
---

# Air Raid

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3625

[PDF](https://uva.onlinejudge.org/external/11/p1184.pdf)

## 样例 #1

### 输入

```
2
4
3
3 4
1 3
2 3
3
3
1 3
1 2
2 3

```

### 输出

```
2
1

```



---

---
title: "Knights of the Round Table"
layout: "post"
diff: 省选/NOI-
pid: UVA1364
tag: ['双连通分量', '二分图']
---

# Knights of the Round Table

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4110

[PDF](https://uva.onlinejudge.org/external/13/p1364.pdf)



---

---
title: "Ants"
layout: "post"
diff: 省选/NOI-
pid: UVA1411
tag: ['网络流', '图论建模', '二分图', '费用流']
---

# Ants

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4157

[PDF](https://uva.onlinejudge.org/external/14/p1411.pdf)

给定平面上的 $N$ 个黑点和 $N$ 个白点（共 $2N$ 个点），请找到一种方案，对于每一个黑点，找到一个白点，用线段把黑点和白点连接，保证最后**任意两条线段无公共点（不相交）**。

## 输入格式

**可能有多组数据。**

对于每组输入数据，第一行一个整数 $N$，描述黑点和白点的数量；

接下来 $N$ 行，每行两个整数 $x,y$，描述**黑点**的坐标；

再接下来 $N$ 行，每行两个整数 $x,y$，描述**白点**的坐标；

## 输出格式

对于每组数据，输出 $N$ 行，每行一个整数，第 $i$ 行的整数 $j$ 表示第 $i$ 个黑点与第 $j$ （$1\leq j \leq N$）个白点相连。

**请在每组数据之间输出一个空行。**

若有多解，任意输出一个均可。

## 说明/提示

## 数据范围与提示

$1\leq N\leq 100, |x|, |y|\leq 10^4$。

保证无三点共线。数据保证有解。

$\small{\text{Statement fixed by @Starrykiller.}}$

## 样例 #1

### 输入

```
5
-42 58
44 86
7 28
99 34
-13 -59
-47 -44
86 74
68 -75
-68 60
99 -6
```

### 输出

```
4
2
1
5
3
```



---

---
title: "Jungle Outpost"
layout: "post"
diff: 省选/NOI-
pid: UVA1475
tag: ['二分', '半平面交']
---

# Jungle Outpost

## 题目描述

在丛林里有n个瞭望塔，瞭望塔的保护范围就是一个凸n多边形，敌人进攻会炸毁一些瞭望塔，使总部暴露在剩下的瞭望塔围成的凸多边形之外，请你选择一个点作为总部，使得敌人要炸毁的瞭望塔尽量多。

## 输入格式

多组数据，每组第一行一个数字n，接下来n行每行两个整数代表一个瞭望塔的坐标。结束标志为EOF。

## 输出格式

对于每组数据，输出当总部位置最优时，敌人需要炸毁的瞭望塔的数目。


感谢@TimeTraveller 提供的翻译

## 样例 #1

### 输入

```
3
0 0
50 50
60 10
5
0 0
0 10
10 20
20 10
25 0
```

### 输出

```
1
2
```



---

---
title: "团队分组 Team them up!"
layout: "post"
diff: 省选/NOI-
pid: UVA1627
tag: ['背包 DP', '二分图']
---

# 团队分组 Team them up!

## 题目描述

你的任务是按照以下要求将一些人员划分到两个队伍中。

1. 每个人都属于其中的一个队伍。

2. 每个队伍至少包含一个人。

3. 每个人都认识几个人，而同一个队伍中的人必须两两认识。

4. 两个队伍的人数尽可能的接近。

这个任务可能有多组解或无解，你只需要输出其中的任意一种或者宣布无解。

## 输入格式

第一行一个整数 t 表示共有 t 组测试数据

接下来 t 组数据，对于每组数据

第一行一个整数 n 表示一共有 n 个人且每个人的编号分别为1-n。

对于接下来 n 行，输入若干个整数，以输入'0'结束，第 i 行表示编号为 i 的人认识的人。

## 输出格式

对于每组数据以一个空行为间隔。

如果无解则输出'No solution'(不包括引号)。否则输出两行，分别表示两个队伍中的人员编号(编号之间以空格隔开)。你可以以任意的顺序输出方案。



---

