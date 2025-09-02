---
title: "城市里的间谍 A Spy in the Metro"
layout: "post"
diff: 提高+/省选-
pid: UVA1025
tag: ['动态规划 DP', '枚举']
---

# 城市里的间谍 A Spy in the Metro

## 题目描述

#### 题目大意

某城市地铁是一条直线，有 $n$（$2\leq	 n\leq	 50$）个车站，从左到右编号 $1\ldots n$。有 $M_1$ 辆列车从第 $1$ 站开始往右开，还有 $M_2$ 辆列车从第 $n$ 站开始往左开。列车在相邻站台间所需的运行时间是固定的，因为所有列车的运行速度是相同的。在时刻 $0$，Mario 从第 $1$ 站出发，目的在时刻 $T$（$0\leq T\leq 200$）会见车站 $n$ 的一个间谍。在车站等车时容易被抓，所以她决定尽量躲在开动的火车上，让在车站等待的时间尽量短。列车靠站停车时间忽略不计，且 Mario 身手敏捷，即使两辆方向不同的列车在同一时间靠站，Mario 也能完成换乘。

## 输入格式

输入文件包含多组数据。

每一组数据包含以下 $7$ 行：

第一行是一个正整数 $n$，表示有 $n$ 个车站。

第二行是为 $T$，表示 Mario 在时刻 $T$ 会见车站 $n$ 的间谍。

第三行有 $n-1$ 个整数 $t_1,t_2,\ldots,t_{n-1}$，其中 $t_i$ 表示地铁从车站 $i$ 到 $i+1$ 的行驶时间。


第四行为 $M_1$，及从第一站出发向右开的列车数目。

第五行包含 $M_1$ 个正整数 $a_1,a_2,\ldots,a_{M_1}$，即每个列车出发的时间。

第六行为 $M_2$ ，即从第 $n$ 站出发向左开的列车数目。

第七行包含 $M_2$ 个正整数 $b_1,b_2,\ldots,b_{M_2}$，即每个列车出发的时间。

输入文件以一行 $0$ 结尾。

## 输出格式

有若干行，每行先输出 ```Case Number XXX : ```（XXX为情况编号，从 $1$ 开始），再输出最少等待时间或 ```impossible```（无解）。

## 样例 #1

### 输入

```
4
55
5 10 15
4
0 5 10 20
4
0 5 10 15
4
18
1 2 3
5
0 3 6 10 12
6
0 3 5 7 12 15
2
30
20
1
20
7
1 3 5 7 11 13 17
0

```

### 输出

```
Case Number 1: 5
Case Number 2: 0
Case Number 3: impossible

```



---

---
title: "Optimal Binary Search Tree"
layout: "post"
diff: 提高+/省选-
pid: UVA10304
tag: ['动态规划 DP', '区间 DP']
---

# Optimal Binary Search Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1245

[PDF](https://uva.onlinejudge.org/external/103/p10304.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10304/8240dddbc7a394a9919bfe12ea1df0e5a38b12ed.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10304/5b63358ad156699ebafb2a0a0b6d27baf4fd1d2b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10304/79b21d984f95af03e88a2fb005e341d755d171c2.png)

## 样例 #1

### 输入

```
1 5
3 10 10 10
3 5 10 20
```

### 输出

```
0
20
20
```



---

---
title: "Ferry Loading II"
layout: "post"
diff: 提高+/省选-
pid: UVA10440
tag: ['动态规划 DP', '贪心']
---

# Ferry Loading II

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1381

[PDF](https://uva.onlinejudge.org/external/104/p10440.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/62f4e72b9730523fdb77b04f21f28f29a3eff81d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/0bb9d3b2914964e55e2370002ec531eaa0ab40b4.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/4a97c3e41ba3630f0efc866c67bde50939a5e9db.png)

## 样例 #1

### 输入

```
2
2 10 10
0
10
20
30
40
50
60
70
80
90
2 10 3
10
30
40
```

### 输出

```
100 5
50 2
```



---

---
title: "Multi-peg Towers of Hanoi"
layout: "post"
diff: 提高+/省选-
pid: UVA10444
tag: ['动态规划 DP', '高精度', '递推']
---

# Multi-peg Towers of Hanoi

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1385

[PDF](https://uva.onlinejudge.org/external/104/p10444.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/b08ae043c16349a4e020bb344c82bd8559661c15.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/9918d07219dee733e043308fe7408963612853cc.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/28c5f29618658abb670593f72b8636cd5eadedfe.png)

## 样例 #1

### 输入

```
3 4
4 4
10 4
10 5
0 0
```

### 输出

```
Case 1: 5
Case 2: 9
Case 3: 49
Case 4: 31
```



---

---
title: "校长的烦恼 Headmaster's Headache"
layout: "post"
diff: 提高+/省选-
pid: UVA10817
tag: ['动态规划 DP', '状态合并', '进制']
---

# 校长的烦恼 Headmaster's Headache

## 题目描述

斯普林菲尔德（春之田野？？？）学院的校长正在考虑为某些科目招聘新老师 现在有一批申请岗位的老师 每个老师能教一个或多个科目 校长想要选择一些申请者以保证每个科目都至少有两名老师能教 同时总共花的钱要最小

## 输入格式

输入由多组测试组成，它们的格式如下： 第一行包含三个给定的整数S，M和N， S (<=8)是科目的总数 M(<=20)是在职教师数，N(<=100)是应聘者的数量

接下来M行每行描述一个在职教师 首先给出雇佣他的花费C (10000<=C<=50000) ,接下来是他能教的科目列表 科目用1—S的整数表示 你必须保证继续聘用他们

之后N行，以同样格式给出应聘者的信息

输入以一个空测试S=0结束，你不应当处理它 （这句有些别扭，不过懂意思就好）

## 输出格式

对于每组测试，输出符合条件的最小花费
翻译贡献者UID：60885

## 样例 #1

### 输入

```
2 2 2
10000 1
20000 2
30000 1 2
40000 1 2
0 0 0
```

### 输出

```
60000
```



---

---
title: "放置街灯 Placing Lampposts"
layout: "post"
diff: 提高+/省选-
pid: UVA10859
tag: ['动态规划 DP']
---

# 放置街灯 Placing Lampposts

## 题目描述

# 题面描述

给定一个 $n$ 个点 $m$ 条边的无向无环图，在尽量少的节点上放灯，使得所有边都与灯相邻（被灯照亮）。

在灯的总数最小的前提下，被两盏灯同时照亮的边数应该尽可能大。

## 输入格式

第一行输入 $T$ ,为数据组数。

每组数据第一行输入 $n,m$，分别为该组数据中图的点数和边数。

以下 $m$ 行，输入各边的两端点 $u,v$。

## 输出格式

输出共 $T$ 行。

对每组数据，一行输出三个数，最小灯数、被两盏灯同时照亮的边数、只被一盏灯照亮的边数。

## 样例 #1

### 输入

```
2
4 3
0 1
1 2
2 3
5 4
0 1
0 2
0 3
0 4
```

### 输出

```
2 1 2
1 0 4
```



---

---
title: "Game of Sum"
layout: "post"
diff: 提高+/省选-
pid: UVA10891
tag: ['动态规划 DP']
---

# Game of Sum

## 题目描述

有一个长度为 $n$ 的整数序列，两个游戏者 $A$ 和 $B$ 轮流取数，$A$ 先取。每次玩家只能从左端或者右端取任意数量的数，但不能两边都取。所有数都被取走视为游戏结束，然后统计每个人取走的数之和，作为各自的得分。两个人采取的策略都是让自己得分尽可能高，并且两个人都很机智，求 $A$ 得分 - $B$ 得分后的结果。

## 输入格式

输入包含多组数据，每组数据第一行为正整数 $n(1\leq n\leq 100)$ ，第二行为给定的整数序列，输入结束标志是 $n=0$ 。

## 输出格式

对于每组数据，输出 $A$ 和 $B$ 都采取最优策略下，$A$ 的得分$-B$ 的得分。


感谢 @额冻豆腐  提供的翻译

## 样例 #1

### 输入

```
4
4 -10 -20 7
4
1 2 3 4
0
```

### 输出

```
7
10
```



---

---
title: "Tiling Dominoes"
layout: "post"
diff: 提高+/省选-
pid: UVA11270
tag: ['动态规划 DP', '进制', '插头 DP']
---

# Tiling Dominoes

## 题目描述

题目大意

给定一个m×n的矩形网格，用1×2多米诺骨牌完全平铺。 请注意，即使一个平铺的旋转与另一个平铺相匹配，它们仍算作不同的平铺。 下面显示了一个平铺示例。

## 输入格式

输入包括多组数据。每组数据占一行，包含两个整数m，n（n×m≤100）。输入结束标志为文件结束符（EOF）。

## 输出格式

对于每组数据输出一行，输出总数。

## 样例 #1

### 输入

```
2 10
4 10
8 8
```

### 输出

```
89
18061
12988816
```



---

---
title: "完美的服务 Perfect Service"
layout: "post"
diff: 提高+/省选-
pid: UVA1218
tag: ['动态规划 DP', '递归', '枚举']
---

# 完美的服务 Perfect Service

## 题目描述

一个网络中有 $N$ 个节点，由 $N-1$ 条边连通，每个节点是服务器或者客户端。如果节点 $u$ 是客户端，就意味着 $u$ 所连接的所有点中有且仅有一台服务器。求最少要多少台服务器才能满足要求。

## 输入格式

输入包含多组测试数据。对于每组数据，第一行是一个整数 $N(\le10000)$。

接下来 $N-1$ 行，每行两个整数 $a_i,b_i$，表示 $a_i,b_i$ 有一条双向连通的边。

除最后一组输入以外，每组数据以 $0$ 结尾，最后一组数据以 $-1$ 结尾。

## 输出格式

对于每组输入，仅输出一行，表示所需要的最小服务器台数。

翻译贡献者：An_Account.



---

---
title: "20个问题 Twenty Questions"
layout: "post"
diff: 提高+/省选-
pid: UVA1252
tag: ['动态规划 DP', '标签464']
---

# 20个问题 Twenty Questions

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3693

[PDF](https://uva.onlinejudge.org/external/12/p1252.pdf)



---

---
title: "Dance Dance Revolution"
layout: "post"
diff: 提高+/省选-
pid: UVA1291
tag: ['动态规划 DP']
---

# Dance Dance Revolution

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=4037

[PDF](https://uva.onlinejudge.org/external/12/p1291.pdf)



---

---
title: "Jump"
layout: "post"
diff: 提高+/省选-
pid: UVA1452
tag: ['动态规划 DP']
---

# Jump

## 题目背景

扩展约瑟夫环问题。

## 题目描述

[problemUrl]: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4198

编号为 $1,2,...n$ 的人围坐在圆桌周围。从 $1$ 号开始报数，报到 $k$ 的人出列，他的下一个人又重新从 $1$ 开始报数，数到 $k$ 的人又出列；依次下去，直到圆桌上所有人都出列。给定 $n$ 与 $k$，求最后出列的三个人的编号。

例如 $n=10,k=2$，出列顺序为 `2，4，6，8，10，3，7，1，9，5`。那么答案为 `1 9 5`。

## 输入格式

第一行为数据组数 $T$。接下来 $T$ 行，每行包含两个数字 $n,k$ 。



## 输出格式

对每一组数据，输出一行，分别是倒数第三，倒数第二，倒数第一的序号，每个序号用空格隔开。

## 说明/提示

$5≤n≤5\times 10^5,2≤k≤5\times 10^5$ 。

## 样例 #1

### 输入

```
1
10 2
```

### 输出

```
1 9 5
```



---

---
title: "切蛋糕 Cake slicing"
layout: "post"
diff: 提高+/省选-
pid: UVA1629
tag: ['动态规划 DP', '枚举', '前缀和']
---

# 切蛋糕 Cake slicing

## 题目描述

翻译：有一个n行m列(1<=n,m<=20)的网络蛋糕上有k个樱桃。每次可以用一刀沿着网络线把蛋糕切成两块，并且只能够直切不能拐弯。要求最后每一块蛋糕上恰好有一个樱桃，且切割线总长度最小。

## 输出格式

输入输出样例
输入样例:
3 4 3
1 2
2 3
3 2
输出样例:
Case 1: 5



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

