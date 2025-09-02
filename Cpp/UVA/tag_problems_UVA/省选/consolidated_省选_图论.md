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
title: "Manhattan Wiring"
layout: "post"
diff: 省选/NOI-
pid: UVA1214
tag: ['动态规划 DP', '图论', '进制']
---

# Manhattan Wiring

## 题目描述

题目大意

n×m网格里有空格和障碍，还有两个2和两个3.要求把这两个2和两个3各用一条折线连起来，使得总长度尽量小（线必须穿过格子中心，每个单位正方形的边长为1）。

限制条件如下：障碍格里不能有线，而每个空格里最多只能有一条线。由此可知，两条折线不能相交，每条折线不能自交。

如图所示，折线总长度为18（2、2、3、3格子中各有一条长度0.5的线）。

## 输入格式

输入包含多组数据。每组数据的第一行为正整数n、m（1≤n，m≤9），以下n行每行为m个整数，描述该网格。0表示空格，1表示障碍，2表示写有“2”的格子，3表示写有“3”的格子。

## 输出格式

对于每组数据输出一行，输出两条折线最小总长度，如果无解，输出0。



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
title: "UNIX插头 A Plug for UNIX"
layout: "post"
diff: 省选/NOI-
pid: UVA753
tag: ['图论建模']
---

# UNIX插头 A Plug for UNIX

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=694

[PDF](https://uva.onlinejudge.org/external/7/p753.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA753/bd8d54abcc7626a52e03f403121ef0c4cca175ba.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA753/85bc1d905b0ad29df832c8d7397d8a7fd9dca5b1.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA753/bde1b0921a746e5875af277006a66198bd24ffbb.png)

## 样例 #1

### 输入

```
1
4
A
B
C
D
5
laptop B
phone C
pager B
clock B
comb X
3
B X
X A
X D
```

### 输出

```
1
```



---

