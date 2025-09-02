---
title: "Dumb Bones"
layout: "post"
diff: 省选/NOI-
pid: UVA10529
tag: ['递推', '枚举', '期望']
---

# Dumb Bones

## 题目描述

你正在尝试用多米诺骨牌搭成一条直线，以便最后试验时推倒它们

（确实，搭建某些东西仅仅为了推倒看上去没啥意义，但你有一些奇怪的爱好）

然而你在搭建过程中可能会弄倒骨牌，这将波及到邻近的部分

现在需要你来求将骨牌搭建完成所需的期望步数

## 输入格式

若干组数据，以0结尾

一个整数n$(1 \leq n \leq 1000)$ 表示你需要搭的骨牌数量

两个整数$P_l,P_r$ 分别表示搭建某个骨牌时向左，向右倾倒的概率

## 输出格式

对于每组数据，输出一个实数，保留两位小数，为搭建完成的期望步数

翻译提供者：Captain_Paul

## 样例 #1

### 输入

```
10 0.25 0.25
10 0.1 0.4
10 0.0 0.5
0
```

### 输出

```
46.25
37.28
20.00
```



---

---
title: "Dijkstra, Dijkstra."
layout: "post"
diff: 省选/NOI-
pid: UVA10806
tag: ['枚举', '最短路']
---

# Dijkstra, Dijkstra.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1747

[PDF](https://uva.onlinejudge.org/external/108/p10806.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/e738bac0dde02ff0489078ea146317a0237c7c29.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/ee4a786c893868ed23aa2feb76f36addda229200.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/3114ba3008d7c18545f888edf30d40fc11724d13.png)

## 样例 #1

### 输入

```
2
1
1 2 999
3
3
1 3 10
2 1 20
3 2 50
9
12
1 2 10
1 3 10
1 4 10
2 5 10
3 5 10
4 5 10
5 7 10
6 7 10
7 8 10
6 9 10
7 9 10
8 9 10
0
```

### 输出

```
Back to jail
80
Back to jail
```



---

---
title: "Travel in Desert"
layout: "post"
diff: 省选/NOI-
pid: UVA10816
tag: ['枚举', '最短路', '生成树']
---

# Travel in Desert

## 题目描述

### 题目大意
沙漠中有$n$ 个绿洲（编号为$1-n$ ）和$e$ 条连接绿洲的双向道路。每条道路都有一个长度$d$ 和一个温度值$r$ 。给定起点绿洲编号$s$ 和终点绿洲编号$t$ ，求出一条$s$ 到$t$ 的路径，使得这条路径上经过的所有道路的最高温度尽量小，如果有多条路径，选择总长度最短的那一条。

## 输入格式

输入包含多组数据。

每组数据第一行为两个整数$n$ 和$e$ 。表示绿洲数量和连接绿洲的道路数量。

每组数据第二行为两个整数$s$ 和$t$ 。表示起点和终点的绿洲编号。

接下来$e$ 行，每行包含两个整数$x,y$ 以及两个实数$r,d$，表明在绿洲$x$ 和$y$ 之间有一条双向道路相连，长度为$d$ ，温度为$r$ 。

## 输出格式

对于输入的每组数据，应输出两行，第一行表示你找到的路线，第二行包含两个实数，为你找出的路线的总长度与途经的最高温度。

## 样例 #1

### 输入

```
6 9
1 6
1 2 37.1 10.2
2 3 40.5 20.7
3 4 42.8 19.0
3 1 38.3 15.8
4 5 39.7 11.1
6 3 36.0 22.5
5 6 43.9 10.2
2 6 44.2 15.2
4 6 34.2 17.4
```

### 输出

```
1 3 6
38.3 38.3
```



---

---
title: "Now or later"
layout: "post"
diff: 省选/NOI-
pid: UVA1146
tag: ['枚举', '2-SAT', '后缀数组 SA']
---

# Now or later

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3587

[PDF](https://uva.onlinejudge.org/external/11/p1146.pdf)



---

---
title: "The Super Powers"
layout: "post"
diff: 省选/NOI-
pid: UVA11752
tag: ['高精度', '枚举']
---

# The Super Powers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2852

[PDF](https://uva.onlinejudge.org/external/117/p11752.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/caccb369bd9149203faf09eaf595e5873b362929.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/3962a6191c1c4336a2bb19bfd7086e2d311306c0.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/ee20a6418dc90b6edefd09d6018cfe0bb329ffe4.png)

## 样例 #1

### 输入

```

```

### 输出

```
1
16
64
81
256
512
.
.
.
```



---

---
title: "That Nice Euler Circuit"
layout: "post"
diff: 省选/NOI-
pid: UVA1342
tag: ['数学', '计算几何', '枚举']
---

# That Nice Euler Circuit

## 题目描述

给出一个平面上$n-1$个点的回路，第$n$个顶点与第$1$个顶点相同，求它把整个平面分成了几个部分（包括内部围起来的部分和外面的无限大的区域）。

## 输入格式

本题包含多组数据$(\leqslant 25)$。

对于每组数据，第一行，一个整数$n$。

第二行，$2n$个整数，为$x_i,y_i$，表示这$n$个点的坐标，数据保证$x_n=x_1,y_n=y_1$.

$n=0$表示数据结束。

## 输出格式

对于每组数据，输出一行，以下列格式输出，其中$x$表示第$x$组数据，$w$是答案。

**Case** $x$**: There are **$w$** pieces.**

## 说明/提示

数据组数$\leqslant 25$

$4\leqslant n\leqslant 300$

$-300\leqslant x_i,y_i\leqslant 300$

感谢@AThousandMoon 提供的翻译



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
title: "Warfare And Logistics"
layout: "post"
diff: 省选/NOI-
pid: UVA1416
tag: ['枚举', '最短路', '概率论']
---

# Warfare And Logistics

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4162

[PDF](https://uva.onlinejudge.org/external/14/p1416.pdf)



---

---
title: "Picnic Planning"
layout: "post"
diff: 省选/NOI-
pid: UVA1537
tag: ['枚举', '生成树', '构造']
---

# Picnic Planning

## 题目描述

[PDF](https://onlinejudge.org/external/15/p1537.pdf)
# 题目背景
The Contortion Brothers是一组著名的马戏团小丑，以其令人难以置信的能力而闻名于世即使是最小的车辆，也能容纳无限的数量。在淡季期间，兄弟俩喜欢在当地公园聚在一起参加年度拳师大会。然而,兄弟俩不仅在狭小的空间里很紧张，而且在金钱上也很紧张，所以他们试图找到让每个人都参加聚会的方法，尽量**减少**每个人的汽车行驶里程（从而节省气体、磨损等）。为此，他们愿意在必要时把自己塞进少数几个车，尽量减少所有汽车的总里程。这经常导致许多兄弟开车去一个兄弟家，除了一辆车外，其他车都停在那里，然后挤进剩下的一个。然而，公园有一个限制：野餐地点的停车场可以只能容纳**有限数量**的汽车，因此必须将其纳入整体最小的计算中。同时，由于公园的入场费，一旦任何兄弟的车到达公园，它就会停在那里;他不会让乘客下车，然后去接其他兄弟。现在，对于你的普通马戏团来说，解决这个问题是一个挑战，所以留给你写一个程序来解决他们的最小化问题。

## 输入格式

第一行输入一个正整数 $ t $，**表示测试数据组数**

对于每一组测试样例:

**第一行**将包含一个整数 $ n ( n \leqslant 20) $，表示兄弟之间或兄弟与公园之间的公路连接数量。
空两行后接下来 $ n $ 行每行格式为“  $ name_1-name_2-dist $ ”  ，其中  $ name_1 $  和  $ name_2 $  要么是两个兄弟的名字。要么是“$ Park $ ”这个词和一个兄弟的姓名（**按任何顺序**），以及
$ dist $是它们之间的整数距离。这些道路都将是双向的。 

最后一行包含一个整数 $ s $ ，用于指定可以放在野餐地点停车场的汽车。你可以假设兄弟的房子都有一条路到公园，即每个问题都有解决方案。

**形式化地**:

给定一张 $ n $ 个点 $ n $ 条边的无向图，求出无向图的一棵最小生成树，满足一号节点的度数不超过给定的整数 $ s $.

## 输出格式

对于每个测试用例，输出必须遵循以下描述。连续两个案例的输出**将用空行分隔**。
对于每个测试用例，输出应该由以下组成:
```
Total miles driven: xxx
```
其中 `xxx` 是兄弟俩所有汽车的总行驶里程。
# 输入输出样例

### 输入 #1
```
2


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
3


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
1
```
### 输出 #1
```
Total miles driven: 183

Total miles driven: 255

```



---

---
title: "岛屿 Islands"
layout: "post"
diff: 省选/NOI-
pid: UVA1665
tag: ['并查集', '枚举', '排序']
---

# 岛屿 Islands

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4540

[PDF](https://uva.onlinejudge.org/external/16/p1665.pdf)



---

---
title: "Jury Compromise"
layout: "post"
diff: 省选/NOI-
pid: UVA323
tag: ['枚举', '背包 DP', '状态合并']
---

# Jury Compromise

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=259

[PDF](https://uva.onlinejudge.org/external/3/p323.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/c7b6c683e8d99d641e6ceda5403d2046b1543157.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/549f8f7966cff47368b778a0f8cc36bf7e06dada.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/3a147f526328df86970adad2cdf916382d1282db.png)

## 样例 #1

### 输入

```
4 2
1 2
2 3
4 1
6 2
0 0

```

### 输出

```
Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3

```



---

