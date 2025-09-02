---
title: "Sumsets"
layout: "post"
diff: 提高+/省选-
pid: UVA10125
tag: ['二分', '枚举', '排序']
---

# Sumsets

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1066

[PDF](https://uva.onlinejudge.org/external/101/p10125.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/29d92f1d32bdaefa1d311d7a2aa7e97895e4a322.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/ce194eb546afa406872932e0bd6f9dd4ca894f2d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/bf773b60567946315edebe60d7e76099b6dc0d8e.png)

## 样例 #1

### 输入

```
5
2
3
5
7
12
5
2
16
64
256
1024
0
```

### 输出

```
12
no solution
```



---

---
title: "Piotr's Ants"
layout: "post"
diff: 提高+/省选-
pid: UVA10881
tag: ['排序']
---

# Piotr's Ants

## 题目描述

一根长度为$L$厘米的木棍上有$n$只蚂蚁，每只蚂蚁要么向左爬，要么向右爬，速度为$1$厘米/秒。当两只蚂蚁相遇时，它们同时掉头（时间忽略不计）。给出每只蚂蚁的初始位置和朝向，请计算$T$秒后每只蚂蚁的位置。

　

## 输入格式

输入第一行为测试数据组数$N$，接下来一共$N$组数据，每组数据的第一行为$3$个整数$L,T,n(0<=n<=10000)$,以下$n$行每行描述了一只蚂蚁的初始位置。其中，整数$x$为它距离木棍左端的距离(单位：厘米).字母表示初始朝向($L$表示朝左，$R$表示向右)

  　

## 输出格式

对于每组数据，输出$n$行，按输入顺序给出每只蚂蚁的位置和朝向($Turning$ 表示正在碰撞)，在第$T$秒之前已经掉下的蚂蚁(正好爬到木棍边缘的不算)输出Fell off.

Translated by @洛谷万岁

## 样例 #1

### 输入

```
2
10 1 4
1 R
5 R
3 L
10 R
10 2 3
4 R
5 L
8 R
```

### 输出

```
Case #1:
2 Turning
6 R
2 Turning
Fell off

Case #2:
3 L
6 R
10 R
```



---

---
title: "Spreading the Wealth"
layout: "post"
diff: 提高+/省选-
pid: UVA11300
tag: ['递推', '排序', '前缀和']
---

# Spreading the Wealth

## 题目描述

圆桌旁边坐着$n$个人，每个人有一定数量的金币，金币的总数能被$n$整除。每个人可以给他左右相邻的人一些金币，最终使得每个人的金币数量相等。您的任务是求出被转手的金币的数量的最小值。

　

## 输入格式

输入包含多组数据。每组数据第一行为一个整数$n(n<=1000000)$,以下n行每行为一个整数，按逆时针顺序给出每个人拥有的金币数。输入结束标志为文件结束符($EOF$).

　

## 输出格式

对于每组数据，输出被转手的金币的数量的最小值。输入保证这个值在$64$位无符号整数的范围之内。

Translated by @洛谷万岁

## 样例 #1

### 输入

```
3
100
100
100
4
1
2
5
4
```

### 输出

```
0
4
```



---

---
title: "照明系统设计 Lighting System Design"
layout: "post"
diff: 提高+/省选-
pid: UVA11400
tag: ['枚举', '排序', '前缀和']
---

# 照明系统设计 Lighting System Design

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2395

[PDF](https://uva.onlinejudge.org/external/114/p11400.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11400/c3748d15cb3e3882e349c0c2e200acb240ab8b00.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11400/8c7751c33d777f27b23c671b600389469282fc9b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11400/115c28d58e6ba75439c2c7bd1d61178f8efff609.png)

## 样例 #1

### 输入

```
3
100 500 10 20
120 600 8 16
220 400 7 18
0
```

### 输出

```
778
```



---

---
title: "Following Orders"
layout: "post"
diff: 提高+/省选-
pid: UVA124
tag: ['搜索', '深度优先搜索 DFS', '拓扑排序']
---

# Following Orders

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=60

[PDF](https://uva.onlinejudge.org/external/1/p124.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/a4a2f6fd96f29dbbab122912895a18a100222b62.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/54c2361014489729658ffc3ced224b7aa260b8c2.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/d3b6edfcc40cb2874efe9a2a99da24fc2905e6df.png)

## 样例 #1

### 输入

```
a b f g
a b b f
v w x y z
v y x v z v w v
```

### 输出

```
abfg
abgf
agbf
gabf
wxzvy
wzxvy
xwzvy
xzwvy
zwxvy
zxwvy
```



---

---
title: "Wall"
layout: "post"
diff: 提高+/省选-
pid: UVA1303
tag: ['排序', '概率论', '凸包']
---

# Wall

## 题目描述

给定一些点，求出最短的包围所有点的轮廓且满足任意点到轮廓的距离不小于给定的$L$。

## 输入格式

第一行一个正整数$T$，代表数据组数。



接下来$T$组数据，对于每组数据，第一行为两个整数$n,L,(3\le n\le 1000,1\le L\le 1000)$，分别代表点的个数和点距离轮廓的最小距离。接下来$n$行，每行两个整数$X_i,Y_i(-10000\le X_i,Y_i\le 10000)$，表示点的坐标。

## 输出格式

输出共$2T$行，对于每组数据，**四舍五入至整数位**输出答案，并空一行。同时，最后一组数据后仅有一个空行。



例如：这是当$T=2$时，两组数据均为样例的答案，`----`表空行。

```

1628

----

1628

----

```



---

---
title: "苗条的生成树 Slim Span"
layout: "post"
diff: 提高+/省选-
pid: UVA1395
tag: ['并查集', '排序', '生成树']
---

# 苗条的生成树 Slim Span

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4141

[PDF](https://uva.onlinejudge.org/external/13/p1395.pdf)



---

---
title: "Guess"
layout: "post"
diff: 提高+/省选-
pid: UVA1423
tag: ['排序', '拓扑排序', '前缀和']
---

# Guess

## 题目描述

给定一个数组： $a_1,a_2,a_3,\dots ,a_n$ 。

我们定义一个符号矩阵 $S_{i,j},i\le j$ ，代表 $a_i+a_{i+1}+\dots +a_j$ 的符号为 $+,-,0$ 三个中的一种。

你需要写一个程序，输入这个 $n\times n$ 的半矩阵，输出原来的数列。如果有多解，输出一组即可。

数据总共有T组。

## 输入格式

第一行输入 $T$ ，代表数据的组数。

接下来共 $T$ 组数据。

对于每一组数据，第一行输入数列的长度 $n$ ，第二行是一个长度为 $\frac{n(n+1)}{2}$ 的字符串，代表这个半矩阵。

## 输出格式

对于每一组数据，输出原来的数列。如果有多解，输出一组即可。

## 说明/提示

$1\le n \le 10$ 

 $-10\le a_i \le 10$ 

Translated by @dblark



---

---
title: "巴比伦塔 The Tower of Babylon"
layout: "post"
diff: 提高+/省选-
pid: UVA437
tag: ['动态规划 DP', '搜索', '递推', '排序']
---

# 巴比伦塔 The Tower of Babylon

## 题目描述

你可能已经听说过巴比伦塔的传说。现在这个传说的许多细节已经被遗忘。所以本着本场比赛的教育性质，我们现在会告诉你整个传说：

巴比伦人有 $n$ 种长方形方块，每种有无限个，第 $i$ 种方块的三边边长是 $xi,yi,zi$。对于每一个方块，你可以任意选择一面作为底，这样高就随着确定了。举个例子，同一种方块，可能其中一个是竖着放的，一个是侧着放的，一个是横着放的。

他们想要用堆方块的方式建尽可能高的塔。问题是，只有一个方块的底的两条边严格小于另一个方块的底的两条边，这个方块才能堆在另一个上面。这意味着，一个方块甚至不能堆在一个底的尺寸与它一样的方块的上面。

你的任务是编写一个程序，计算出这个塔可以建出的最高的高度。

## 输入格式

输入会包含至少一组数据，每组数据的第一行是一个整数 $n(n\le30)$，表示方块的种类数。 这组数据接下来的 $n$ 行，每行有三个整数，表示 $xi,yi,zi$。输入数据会以 $0$ 结束。

## 输出格式

对于每组数据，输出一行，其中包含组号（从 $1$ 开始）和塔最高的高度。按以下格式：``Case i: maximum height = __``。

## 样例 #1

### 输入

```
1
10 20 30
2
6 8 10
5 5 5
7
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
5
31 41 59
26 53 58
97 93 23
84 62 64
33 83 27
0
```

### 输出

```
Case 1: maximum height = 40
Case 2: maximum height = 21
Case 3: maximum height = 28
Case 4: maximum height = 342
```



---

