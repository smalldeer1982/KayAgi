---
title: "Crossing Streets"
layout: "post"
diff: 提高+/省选-
pid: UVA1043
tag: ['搜索', '离散化']
---

# Crossing Streets

## 题目描述

Peter 要从家到学校，他想要规划穿过马路条数最少的路线。

给定 $n$ 条马路的起始点与终点坐标（马路一定与坐标轴平行），以及 Peter 家和大学所在位置坐标。求 Peter 从家到大学的任意路径下最少穿过多少条马路。特别地，Peter 不能穿过马路之间的交点。

## 输入格式

题目含有多组数据。

对于每组数据：

第一行，输入一个整数 $n$，代表马路条数。

接下来 $n$ 行，每行四个数 $x_1,y_1,x_2,y_2$，代表一条马路起点与终点坐标。

接下来一行四个数，$x_h,y_h,x_u,y_u$，代表 Peter 家的坐标与大学的坐标。

当输入的 $n$ 为 $0$ 时，结束程序。

## 输出格式

对于每组数据，输出 $2$ 行，格式如下：
```
City [i]
Peter has to cross [x] streets
```
其中 `i` 代表是第几组数据，`x` 代表答案（不包含 `[]`）。

## 说明/提示

$1\le n\le 500$，所有输入的坐标绝对值不大于 $2\times 10^9$。

Translated by HYdroKomide.

## 样例 #1

### 输入

```
8
6 0 24 0
24 0 24 4
24 4 6 4
6 4 6 0
12 1 26 1
26 1 26 6
26 6 12 6
12 6 12 1
0 1 17 3
1
10 10 20 10
1 1 30 30
0
```

### 输出

```
City 1
Peter has to cross 2 streets
City 2
Peter has to cross 0 streets
```



---

---
title: "Treblecross"
layout: "post"
diff: 提高+/省选-
pid: UVA10561
tag: ['字符串', '搜索']
---

# Treblecross

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1502

[PDF](https://uva.onlinejudge.org/external/105/p10561.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/31bc60cd2679d5a858bab6338b6a91a761cb246d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/f3a035fa62c3266f7235864450f9f70c79fb3298.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/9aa18e2eb8be86e1d3e3cb2e789c20ffbc1a2cbf.png)

## 样例 #1

### 输入

```
4
.....
X.....X..X.............X....X..X
.X.X...X
...............................................
```

### 输出

```
WINNING
3
LOSING
WINNING
3
WINNING
1 12 15 17 20 24 28 31 33 36 47
```



---

---
title: "The Largest Clique"
layout: "post"
diff: 提高+/省选-
pid: UVA11324
tag: ['搜索', '记忆化搜索', '强连通分量']
---

# The Largest Clique

## 题目描述

给你一张有向图 $G$，求一个结点数最大的结点集，使得该结点集中的任意两个结点 $u$ 和 $v$ 满足：要么 $u$ 可以达 $v$，要么 $v$ 可以达 $u$ （$u,v$ 相互可达也行）。

## 输入格式

第一行，输入一个整数，代表测试数据组数 $T$，每组数据的格式如下。

第一行为结点数 $n$ 和边数 $m$，结点编号 $1 \sim n$。

以下 $m$ 行每行两个整数 $u$ 和 $v$ ，表示一条有向边 $u \to v$。

## 输出格式

对于每组数据，输出最大结点集的结点数。

## 样例 #1

### 输入

```
1
5 5
1 2
2 3
3 1
4 1
5 2
```

### 输出

```
4
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
title: "Jurassic Remains"
layout: "post"
diff: 提高+/省选-
pid: UVA1326
tag: ['字符串', '搜索', '枚举']
---

# Jurassic Remains

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4072

[PDF](https://uva.onlinejudge.org/external/13/p1326.pdf)



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
title: "Falling Leaves"
layout: "post"
diff: 提高+/省选-
pid: UVA1525
tag: ['字符串', '搜索', '平衡树', '图论建模']
---

# Falling Leaves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4300

[PDF](https://uva.onlinejudge.org/external/15/p1525.pdf)



---

---
title: "理想路径 Ideal Path"
layout: "post"
diff: 提高+/省选-
pid: UVA1599
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# 理想路径 Ideal Path

## 题目描述

## 本题有多组数据


# 理想路径（Ideal Path, NEERC 2010, UVa1599）

给定一个$n$个点$m$条边的无向图，每条边上都涂有1种颜色。求点$1$到点$n$的一条路径，**使得经过的边数最少**，在此前提下，经过边的颜色序列最小。可能有自环与重边。输入保证至少存在一条连接$1$和$n$的道路。

## 输入格式

输入共$m+1$行：

第一行$2$个空格整数：$n$和$m$。

以后$m$行，每行空格隔开的$3$个整数$a_i,b_i,c_i$，表示在$a_i,b_i$之间有一条颜色为$c_i$的道路。

## 输出格式

输出共两行：

第一行$1$个正整数$k$，表示$1$到$n$至少需要经过$k$条边。

第二行包含$k$个空格隔开的正整数，表示从$1$到$n$依次经过的边的**颜色**。

## 输入输出样例：
### 输入样例：
```
4 6
1 2 1
1 3 2
3 4 3
2 3 1
2 4 4
3 1 1
```
### 输出样例：
```
2
1 3
```
### 输入输出样例解释：
路径依次如下：

$1\rightarrow3$，颜色为$1$（最后输入的那条）；

$3\rightarrow4$，颜色为$3$。

## 说明/提示

$2\leq n \leq 10^5, 1 \leq m \leq 2 \times 10^5,1\leq c_i \leq 10^9$。

对于任意$i \in [1,m]$有$1 \leq a_i,b_i \leq n$。

注：对于两个长度为$k$的序列$a,b$，当存在$i \in [1,k]$使$a_i < b_i$，且对于任意$j \in [1,i)$都有$a_j = b_j$时，$a<b$。

原文：A sequence (a1, a2, . . . , ak) is lexicographically smaller than a sequence (b1, b2, . . . , bk) if there
exists i such that ai < bi
, and aj = bj for all j < i.

感谢@Sparky_14145 提供的翻译



---

---
title: "纸牌游戏 Double Patience"
layout: "post"
diff: 提高+/省选-
pid: UVA1637
tag: ['动态规划 DP', '搜索', '概率论']
---

# 纸牌游戏 Double Patience

## 题目描述

Double  Patience是一种单人游戏，使用标准的36张牌组。这些牌在洗牌后放在一张桌子上，叠成9叠，每叠4张，面朝上。



牌放下后，玩家转身。每一次，他可以从任意两个牌堆中取出同一等级的顶级牌，然后将它们移除。如果有几种可能性，玩家可以选择任何一种。如果所有的牌都从桌上移除，玩家将赢得游戏，如果一些牌仍然在桌上，并且没有有效的移动，玩家将失败。



乔治喜欢这种游戏。但当有几种可能时，他不知道要选择哪一张。乔治不想多想，所以在这种情况下，他只需从可能的情况中选择一对随机的，并删除它。乔治选择每种情况的可能性相同。



例如，如果最上面的牌是Ks、Kh、Kd、9h、8s、8d、7c、7d和6h，他会删除任何一对在(KS, KH)、(KS, KD)、(KH, KD)、 (8S, 8D)和 (7C, 7D)中的任何一对。删除（Ks,Kh）、（Ks,Kd）、（Kh,Kd）、（8s,8d）和（7c,7d）的概率都为1/5。



请算出在游戏开始时，根据桌上的牌，找出如果乔治按照描述行事，他赢得游戏的可能性是多少。

## 输入格式

输入文件包含几个测试用例，每个测试用例由九行组成。每行包含四张牌的描述，它们在游戏开始时形成一堆，从下一张牌到上一张牌。



每张卡片有两个字符：一个用于等级，一个用于花色。等级用“6”表示6，“7”表示7，“8”表示8，“9”表示9，“T”表示10，“J”表示杰克，“Q”表示女王，“K”表示国王，“A”表示王牌。花色用“S”代表黑桃，C代表梅花，D代表钻石，H代表红桃。例如，“KS”表示黑桃王。



每个卡片描述之间用一个空格隔开。

## 输出格式

对于每个测试用例，输出一行实数-如果乔治随机玩游戏，他赢得游戏的概率。您的答案必须精确到小数点后6位

## 样例输入，输出略



---

---
title: "Solitaire"
layout: "post"
diff: 提高+/省选-
pid: UVA1724
tag: ['搜索', '广度优先搜索 BFS', '折半搜索 meet in the middle']
---

# Solitaire

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=859&page=show_problem&problem=4862

[PDF](https://uva.onlinejudge.org/external/17/p1724.pdf)

## 样例 #1

### 输入

```
4 4 4 5 5 4 6 5
2 4 3 3 3 6 4 6
```

### 输出

```
YES
```



---

---
title: "Optimal Array Multiplication Sequence"
layout: "post"
diff: 提高+/省选-
pid: UVA348
tag: ['搜索', '记忆化搜索']
---

# Optimal Array Multiplication Sequence

## 题目描述

对于三个矩阵$A,B,C$，若$C=AB$，则C的计算方式为$C_{i,j}=\sum_k A_{i,k} \times B_{k,j}$。



可见若要计算两个大小分别为$a \times b$和$b \times c$的矩阵的乘积，需要$a \times b \times c$次计算；

对于两个矩阵$A,B$，不满足$A \times B = B \times A$；对于三个矩阵$A,B,C$，满足$(A \times B) \times C = A \times (B \times C)$。



给定$n$个矩阵$A1,A2, \dots ,An$的行列数，现在要算出这些矩阵的积，问如何安排运算顺序可使运算次数最少。



本题包含多组数据。

## 输入格式

对于每组数据，首先输入一个正整数$n(0 \le n \le 10)$，然后每行输入两个正整数，表示每个矩阵的行数和列数。

## 输出格式

首先输出“$Case\ k:\ $”，其中$k$为当前数据的组别编号。然后输出最优计算顺序，其中乘号用“x”代表，且前后都要输出一个空格。每一次乘法的外面都要套一对小括号。



例如第一组数据的最优解为先计算$A2 \times A3$，再计算$A1 \times (A2 \times A3)$，则要输出“(A1 x (A2 x A3))”。

## 样例 #1

### 输入

```
3
1 5
5 20
20 1
3
5 10
10 20
20 35
6
30 35
35 15
15 5
5 10
10 20
20 25
0
```

### 输出

```
Case 1: (A1 x (A2 x A3))
Case 2: ((A1 x A2) x A3)
Case 3: ((A1 x (A2 x A3)) x ((A4 x A5) x A6))
```



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

---
title: "Triangle War"
layout: "post"
diff: 提高+/省选-
pid: UVA751
tag: ['搜索', '状态合并', '博弈树']
---

# Triangle War

## 题目描述

## 题面翻译

给出10个点，共有18条边，每次A,B两个人轮流加入一条边。A先加。

如果形成一个三角形，则三角形归他所有，**而且还必须再走一步**。最后三角形多的人胜。

现在已经给出一部分已经完成的步数，由于两位玩家都是**最聪明的**，他们都会走**为自己带来最大优势**的步数。你需要判断谁会赢得游戏。

## 输入格式

每个测试点包含多组数据。输入的第一行包括一个整数  $t$  ，表示数据组数。

对于每一组数据：
第一行为一个正整数  $m$  ，表示已经完成的步数。 （6 <=  $m$  <= 18)

接下来的  $m$  行描述了按顺序 A , B 两人完成的步数，按照  $i$   $j$  的形式，表示i，j 已经被填上。

## 输出格式

对于每一组测试数据输出一行，先输出游戏的序号 `Game x`: ，如果 A 获胜，输出 `A wins.` ，否则输出 `B wins.` 。

## 输入输出样例
略

感谢@Kato_Megumi  提供的翻译

## 样例 #1

### 输入

```
4
6
2 4
4 5
5 9
3 6
2 5
3 5
7
2 4
4 5
5 9
3 6
2 5
3 5
7 8
6
1 2
2 3
1 3
2 4
2 5
4 5
10
1 2
2 5
3 6
5 8
4 7
6 10
2 4
4 5
4 8
7 8
```

### 输出

```
Game 1: B wins.
Game 2: A wins.
Game 3: A wins.
Game 4: B wins.
```



---

---
title: "Abbott的复仇 Abbott's Revenge"
layout: "post"
diff: 提高+/省选-
pid: UVA816
tag: ['广度优先搜索 BFS', '图论建模', '最短路']
---

# Abbott的复仇 Abbott's Revenge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=757

[PDF](https://uva.onlinejudge.org/external/8/p816.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/815d09b7103ad071de9d9f7869315aa2585ea85b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/4939e773b1884a681cdc9dbd1fe1251df58b072b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/9ff2bb3a862e6ca3e356ecb98a558f994c9d7f5d.png)

## 样例 #1

### 输入

```
SAMPLE
3 1 N 3 3
1 1 WL NR *
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0
NOSOLUTION
3 1 N 3 2
1 1 WL NR *
1 2 NL ER *
2 1 SL WR NFR *
2 2 SR EL *
0
END
Figure 1: An Example Walk-Through
Arrow Maz
```

### 输出

```
SAMPLE
(3,1) (2,1) (1,1) (1,2) (2,2) (2,3) (1,3) (1,2) (1,1) (2,1)
(2,2) (1,2) (1,3) (2,3) (3,3)
NOSOLUTION
No Solution Possible
```



---

