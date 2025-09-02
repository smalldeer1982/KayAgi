---
title: "买礼物"
layout: "post"
diff: 普及/提高-
pid: P1194
tag: ['图论', '生成树']
---
# 买礼物
## 题目描述

又到了一年一度的明明生日了，明明想要买 $B$ 样东西，巧的是，这 $B$ 样东西价格都是 $A$ 元。

但是，商店老板说最近有促销活动，也就是：

如果你买了第 $I$ 样东西，再买第 $J$ 样，那么就可以只花 $K_{I,J}$ 元，更巧的是，$K_{I,J}$ 竟然等于 $K_{J,I}$。

现在明明想知道，他最少要花多少钱。
## 输入格式

第一行两个整数，$A,B$。

接下来 $B$ 行，每行 $B$ 个数，第 $I$ 行第 $J$ 个为 $K_{I,J}$。

我们保证 $K_{I,J}=K_{J,I}$ 并且 $K_{I,I}=0$。

特别的，如果 $K_{I,J}=0$，那么表示这两样东西之间不会导致优惠。

注意 $K_{I,J}$ **可能大于** $A$。
## 输出格式

一个整数，为最小要花的钱数。

## 样例

### 样例输入 #1
```
1 1
0


```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3 3
0 2 4
2 0 2
4 2 0

```
### 样例输出 #2
```
7
```
## 提示

样例解释 $2$。

先买第 $2$ 样东西，花费 $3$ 元，接下来因为优惠，买 $1,3$ 样都只要 $2$ 元，共 $7$ 元。

（同时满足多个“优惠”的时候，聪明的明明当然不会选择用 $4$ 元买剩下那件，而选择用 $2$ 元。）

数据规模

对于 $30\%$ 的数据，$1\le B\le 10$。

对于 $100\%$ 的数据，$1\le B\le500,0\le A,K_{I,J}\le1000$。

2018.7.25新添数据一组


---

---
title: "口袋的天空"
layout: "post"
diff: 普及/提高-
pid: P1195
tag: ['图论', '并查集', '生成树']
---
# 口袋的天空
## 题目背景

小杉坐在教室里，透过口袋一样的窗户看口袋一样的天空。

有很多云飘在那里，看起来很漂亮，小杉想摘下那样美的几朵云，做成棉花糖。

## 题目描述

给你云朵的个数 $N$，再给你 $M$ 个关系，表示哪些云朵可以连在一起。

现在小杉要把所有云朵连成 $K$ 个棉花糖，一个棉花糖最少要用掉一朵云，小杉想知道他怎么连，花费的代价最小。

## 输入格式

第一行有三个数 $N,M,K$。

接下来 $M$ 行每行三个数 $X,Y,L$，表示 $X$ 云和 $Y$ 云可以通过 $L$ 的代价连在一起。



## 输出格式

对每组数据输出一行，仅有一个整数，表示最小的代价。

如果怎么连都连不出 $K$ 个棉花糖，请输出 `No Answer`。

## 样例

### 样例输入 #1
```
3 1 2
1 2 1

```
### 样例输出 #1
```
1
```
## 提示

对于 $30\%$ 的数据，$1 \le N \le 100$，$1\le M \le 10^3$；

对于 $100\%$ 的数据，$1 \le N \le 10^3$，$1 \le M \le 10^4$，$1 \le K \le 10$，$1 \le X,Y \le N$，$0 \le L<10^4$。



---

---
title: "[蓝桥杯 2025 省 Java B] 爆破"
layout: "post"
diff: 普及/提高-
pid: P12158
tag: ['2025', 'Special Judge', '生成树', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 Java B] 爆破
## 题目描述

小明正在参加一场爆破工作。人们在地面上放置了 $n$ 个爆炸魔法阵，第 $i$ 个魔法阵的圆心坐标为 $(x_i, y_i)$，半径为 $r_i$。如果两个魔法阵相交，则它们可以一起引爆；如果两个魔法阵不相交，则可以再使用一条魔法回路将它们的边缘连接起来。小明想知道最少需要布置总长度多长的魔法回路才能使得所有的魔法阵可以一起引爆？
## 输入格式

输入共 $n + 1$ 行。
- 第一行为一个正整数 $n$。
- 后面 $n$ 行，每行三个整数表示 $x_i, y_i, r_i$。
## 输出格式

输出共 $1$ 行，一个浮点数表示答案（四舍五入保留两位小数）。
## 样例

### 样例输入 #1
```
4
0 0 1
2 0 2
-3 0 1
4 4 1
```
### 样例输出 #1
```
2.47
```
## 提示

### 样例说明

- 使用魔法回路连接第 $1$、$3$ 个魔法阵，长度为 $1$。
- 使用魔法回路连接第 $2$、$4$ 个魔法阵，长度为 $2\sqrt{5} - 3 = 1.47$。

总长度 $2.47$。

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$n \leq 500$。
- 对于 $100\%$ 的评测用例，$1\leq n \leq 5000$，$|x_i|, |y_i| \leq 2000$，$0 < r_i \leq 20$。


---

---
title: "[蓝桥杯 2023 国 Java B] 电动车"
layout: "post"
diff: 普及/提高-
pid: P12222
tag: ['2023', '生成树', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Java B] 电动车
## 题目描述

作为一名繁忙的程序员，小蓝经常需要在 $N$ 座城市之间来回穿梭。他准备购买一辆电动车出行，但是担心电动车电量不足。

为了描述方便，我们把 $N$ 座城市编号 $1$ 至 $N$。城市之间一共有 $M$ 条双向高速公路相连。其中第 $i$ 条连接 $u_i$ 号城市和 $v_i$ 号城市，耗费 $w_i$ 个单位的电量。

假设小蓝可以在出发城市，以及任何中途经过的城市充满电。小蓝想知道，如果希望从任意城市开电动车到任意另一个城市，都可以找到一条由若干高速公路组成路径，使得不需要在任何高速公路内补充电量，那么这台电动车至少需要多少电量？
## 输入格式

第一行包含两个整数 $N$ 和 $M$。

以下 $M$ 行，每行包含 $3$ 个整数 $u_i$、$v_i$ 和 $w_i$。
## 输出格式

一个整数，代表答案。

如果存在两个城市不能通过高速公路相互到达，输出 $-1$。
## 样例

### 样例输入 #1
```
4 5
1 2 3
1 3 5
2 4 2
4 3 2
4 1 4
```
### 样例输出 #1
```
3
```
## 提示

### 样例说明

- 从 $1$ 到 $2$ 可以走：$1 \rightarrow 2$，需要电量 3。
- 从 $1$ 到 $3$ 可以走：$1 \rightarrow 2 \rightarrow 4 \rightarrow 3$，其中 $1 \rightarrow 2$ 需要电量 $3$，$2 \rightarrow 4$ 需要电量 $2$，$4 \rightarrow 3$ 需要电量 $2$，全程至少需要电量 $3$。
- 从 $1$ 到 $4$ 可以走：$1 \rightarrow 2 \rightarrow 4$，其中 $1 \rightarrow 2$ 需要电量 $3$，$2 \rightarrow 4$ 需要电量 $2$，全程至少需要电量 $3$。
- 从 $2$ 到 $3$ 可以走：$2 \rightarrow 4 \rightarrow 3$，其中 $2 \rightarrow 4$ 需要电量 $2$，$4 \rightarrow 3$ 需要电量 $2$，全程至少需要电量 $2$。
- 从 $2$ 到 $4$ 可以走：$2 \rightarrow 4$，需要电量 $2$。
- 从 $3$ 到 $4$ 可以走：$3 \rightarrow 4$，需要电量 $2$。

综上所述，电动车至少需要 $3$ 个单位的电量。

### 评测用例规模与约定

- 对于 $20\%$ 的数据，$1 \leq N, M \leq 100$，$0 \leq w_i \leq 100$。
- 对于 $100\%$ 的数据，$1 \leq N, M \leq 200000$，$0 \leq w_i \leq 10^9$。


---

---
title: "[COCI 2020/2021 #2] Odasiljaci"
layout: "post"
diff: 普及/提高-
pid: P13427
tag: ['2020', '二分', '并查集', 'Special Judge', '生成树', '连通块', 'COCI（克罗地亚）']
---
# [COCI 2020/2021 #2] Odasiljaci
## 题目描述

Sadly, this is the last time Sean will play James Bond.

His mission is to network $n$ antennas that are scattered across a vast desert, which can be represented as a 2D plane. He will set the transmission radius of each antenna to be the same non negative real number $r$. The range of an antenna is defined as the set of all points whose distance to the antenna is at most $r$. If ranges of two antennas have a common point, those antennas can directly communicate. Also, if antennas $A$ and $B$ can communicate, as well as antennas $B$ and $C$, then antennas $A$ and $C$ are also able to communicate, through antenna $B$.

Sean wants to network the antennas, i.e. make possible for every two antennas to communicate. Since $M$ has limited his spending for this mission, and larger radii require more money, Sean will choose the smallest possible radius $r$. Help him solve this problem!
## 输入格式

The first line contains an integer $n$ ($1 \leq n \leq 1000$), the number of antennas.

Each of the following $n$ lines contains integers $x_i$ and $y_i$ ($0 \leq x_i, y_i \leq 10^9$), coordinates of the $i$-th antenna.
## 输出格式

Output the minimal radius.

Your answer will be considered correct if its absolute or relative error doesn't exceed $10^{-6}$.
## 样例

### 样例输入 #1
```
2
1 1
2 2
```
### 样例输出 #1
```
0.7071068
```
### 样例输入 #2
```
7
2 3
3 4
4 5
0 1
3 1
4 2
1 5
```
### 样例输出 #2
```
1.4142135
```
### 样例输入 #3
```
4
2020 20
20 2020
2020 2020
20 20
```
### 样例输出 #3
```
1000.0000000
```
## 提示

Clarification of the second example:

![](https://cdn.luogu.com.cn/upload/image_hosting/dxxoyzwk.png)


---

---
title: "营救"
layout: "post"
diff: 普及/提高-
pid: P1396
tag: ['图论', '二分', '并查集', '福建省历届夏令营', '最短路', '生成树']
---
# 营救
## 题目背景

“咚咚咚……”“查水表！”原来是查水表来了，现在哪里找这么热心上门的查表员啊！小明感动得热泪盈眶，开起了门……
## 题目描述

妈妈下班回家，街坊邻居说小明被一群陌生人强行押上了警车！妈妈丰富的经验告诉她小明被带到了 $t$ 区，而自己在 $s$ 区。

该市有 $m$ 条大道连接 $n$ 个区，一条大道将两个区相连接，每个大道有一个拥挤度。小明的妈妈虽然很着急，但是不愿意拥挤的人潮冲乱了她优雅的步伐。所以请你帮她规划一条从 $s$ 至 $t$ 的路线，使得经过道路的拥挤度最大值最小。
## 输入格式

第一行有四个用空格隔开的 $n$，$m$，$s$，$t$，其含义见【题目描述】。

接下来 $m$ 行，每行三个整数 $u, v, w$，表示有一条大道连接区 $u$ 和区 $v$，且拥挤度为 $w$。

**两个区之间可能存在多条大道**。
## 输出格式

输出一行一个整数，代表最大的拥挤度。
## 样例

### 样例输入 #1
```
3 3 1 3
1 2 2
2 3 1
1 3 3
```
### 样例输出 #1
```
2

```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n\leq 10$。
- 对于 $60\%$ 的数据，保证 $n\leq 100$。
- 对于 $100\%$ 的数据，保证 $1 \leq n\leq 10^4$，$1 \leq m \leq 2 \times 10^4$，$w \leq 10^4$，$1 \leq s, t \leq n$。且从 $s$ 出发一定能到达 $t$ 区。

--- 

#### 样例输入输出 1 解释

小明的妈妈要从 $1$ 号点去 $3$ 号点，最优路线为 $1$->$2$->$3$。


---

---
title: "村村通"
layout: "post"
diff: 普及/提高-
pid: P1536
tag: ['并查集', '生成树']
---
# 村村通
## 题目描述

某市调查城镇交通状况，得到现有城镇道路统计表。表中列出了每条道路直接连通的城镇。市政府 "村村通工程" 的目标是使全市任何两个城镇间都可以实现交通（但不一定有直接的道路相连，只要相互之间可达即可）。请你计算出最少还需要建设多少条道路？
## 输入格式

输入包含若干组测试数据，每组测试数据的第一行给出两个用空格隔开的正整数，分别是城镇数目 $n$ 和道路数目 $m$ ；随后的 $m$ 行对应 $m$ 条道路，每行给出一对用空格隔开的正整数，分别是该条道路直接相连的两个城镇的编号。简单起见，城镇从 $1$ 到 $n$ 编号。

注意：两个城市间可以有多条道路相通。

**在输入数据的最后，为一行一个整数 $0$，代表测试数据的结尾。**
## 输出格式

对于每组数据，对应一行一个整数。表示最少还需要建设的道路数目。

## 样例

### 样例输入 #1
```
4 2
1 3
4 3
3 3
1 2
1 3
2 3
5 2
1 2
3 5
999 0
0

```
### 样例输出 #1
```
1
0
2
998

```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \le n < 1000$ 。


---

---
title: "[USACO3.1] 最短网络 Agri-Net"
layout: "post"
diff: 普及/提高-
pid: P1546
tag: ['图论', '贪心', 'USACO', '并查集', '生成树']
---
# [USACO3.1] 最短网络 Agri-Net
## 题目背景

Farmer John 被选为他们镇的镇长！他其中一个竞选承诺就是在镇上建立起互联网，并连接到所有的农场。当然，他需要你的帮助。

## 题目描述

FJ 已经给他的农场安排了一条高速的网络线路，他想把这条线路共享给其他农场。为了用最小的消费，他想铺设最短的光纤去连接所有的农场。

你将得到一份各农场之间连接费用的列表，你必须找出能连接所有农场并所用光纤最短的方案。每两个农场间的距离不会超过 $10^5$。
## 输入格式

第一行农场的个数 $N$（$3 \leq N \leq 100$）。

接下来是一个 $N \times N$ 的矩阵，表示每个农场之间的距离。理论上，他们是 $N$ 行，每行由 $N$ 个用空格分隔的数组成，实际上，由于每行 $80$ 个字符的限制，因此，某些行会紧接着另一些行。当然，对角线将会是 $0$，因为不会有线路从第 $i$ 个农场到它本身。
## 输出格式

只有一个输出，其中包含连接到每个农场的光纤的最小长度。

## 样例

### 样例输入 #1
```
4
0 4 9 21
4 0 8 17
9 8 0 16
21 17 16 0
```
### 样例输出 #1
```
28
```
## 提示

题目翻译来自NOCOW。

USACO Training Section 3.1



---

---
title: "[USACO05MAR] Out of Hay S"
layout: "post"
diff: 普及/提高-
pid: P1547
tag: ['图论', '贪心', '2005', 'USACO', '并查集', '生成树', '连通块']
---
# [USACO05MAR] Out of Hay S
## 题目描述

Bessie 计划调查 $N$（$2 \leq N \leq 2\,000$）个农场的干草情况，它从 $1$ 号农场出发。农场之间总共有 $M$（$1 \leq M \leq 10^4$）条双向道路，所有道路的总长度不超过 $10^9$。有些农场之间存在着多条道路，所有的农场之间都是连通的。

Bessie 希望计算出该图中最小生成树中的最长边的长度。

## 输入格式

第一行两个整数 $N,M$。

接下来 $M$ 行，每行三个用空格隔开的整数 $A_i,B_i,L_i$，表示 $A_i,B_i$ 之间有一条道路，长度为 $L_i$。
## 输出格式

一个整数，表示最小生成树中的最长边的长度。

## 样例

### 样例输入 #1
```
3 3
1 2 23
2 3 1000
1 3 43
```
### 样例输出 #1
```
43
```


---

---
title: "[USACO04DEC] Bad Cowtractors S"
layout: "post"
diff: 普及/提高-
pid: P1669
tag: ['2004', 'USACO', '生成树']
---
# [USACO04DEC] Bad Cowtractors S
## 题目描述

奶牛贝茜被雇去建设 $N(2\le N\le 10^3)$ 个牛棚间的互联网。她已经勘探出 $M(1\le M\le 2\times 10^4)$ 条可建的线路，每条线路连接两个牛棚，而且会花费 $C(1\le C\le 10^5)$。农夫约翰吝啬得很，他希望建设费用最少甚至他都不想给贝茜工钱。贝茜得知工钱要告吹，决定报复。她打算选择建一些线路，把所有牛棚连接在一起，让约翰花费最大。但是她不能造出环来，这样约翰就会发现。
## 输入格式

第 $1$ 行：$N$，$M$。

第 $2$ 到 $M+1$ 行：三个整数，表示一条可能线路的两个端点和费用。
## 输出格式

一行，表示最大的花费。如果不能建成合理的线路，就输出 $-1$。
## 样例

### 样例输入 #1
```
5 8
1 2 3
1 3 7
2 3 10
2 4 4
2 5 8
3 4 6
3 5 2
4 5 17
```
### 样例输出 #1
```
42
```
## 提示

$2\le N\le 10^3$，$1\le M\le 2\times 10^4$，$1\le C\le 10^5$。


---

---
title: "无线通讯网"
layout: "post"
diff: 普及/提高-
pid: P1991
tag: ['图论', '并查集', '生成树']
---
# 无线通讯网
## 题目描述

国防部计划用无线网络连接若干个边防哨所。2 种不同的通讯技术用来搭建无线网络；

每个边防哨所都要配备无线电收发器；有一些哨所还可以增配卫星电话。

任意两个配备了一条卫星电话线路的哨所（两边都有卫星电话）均可以通话，无论他们相距多远。而只通过无线电收发器通话的哨所之间的距离不能超过 $D$，这是受收发器的功率限制。收发器的功率越高，通话距离 $D$ 会更远，但同时价格也会更贵。

收发器需要统一购买和安装，所以全部哨所只能选择安装一种型号的收发器。换句话说，每一对哨所之间的通话距离都是同一个 $D$。你的任务是确定收发器必须的最小通话距离 $D$，使得每一对哨所之间至少有一条通话路径（直接的或者间接的）。

## 输入格式

第一行，$2$ 个整数 $S$ 和 $P$，$S$ 表示可安装的卫星电话的哨所数，$P$ 表示边防哨所的数量。

接下里 $P$ 行，每行两个整数 $x，y$ 描述一个哨所的平面坐标 $(x, y)$，以 km 为单位。

## 输出格式

第一行，$1$ 个实数 $D$，表示无线电收发器的最小传输距离，精确到小数点后两位。

## 样例

### 样例输入 #1
```
2 4
0 100
0 300
0 600
150 750

```
### 样例输出 #1
```
212.13

```
## 提示

### 数据范围及约定

- 对于 $20\%$ 的数据：$P = 2，S = 1$；
- 对于另外 $20\%$ 的数据：$P = 4，S = 2$；
- 对于 $100\%$ 的数据保证：$1 ≤ S ≤ 100$，$S < P ≤ 500$，$0 ≤ x,y ≤ 10000$。



---

---
title: "拆地毯"
layout: "post"
diff: 普及/提高-
pid: P2121
tag: ['图论', '生成树']
---
# 拆地毯
## 题目背景

还记得 NOIP 2011 提高组 Day1 中的铺地毯吗？时光飞逝，光阴荏苒，三年过去了。组织者精心准备的颁奖典礼早已结束，留下的则是被人们踩过的地毯。请你来解决类似于铺地毯的另一个问题。

## 题目描述

会场上有 $n$ 个关键区域，不同的关键区域由 $m$ 条无向地毯彼此连接。每条地毯可由三个整数 $u$、$v$、$w$ 表示，其中 $u$ 和 $v$ 为地毯连接的两个关键区域编号，$w$ 为这条地毯的美丽度。

由于颁奖典礼已经结束，铺过的地毯不得不拆除。为了贯彻勤俭节约的原则，组织者被要求只能保留至多 $K$ 条地毯，且保留的地毯构成的图中，任意可互相到达的两点间只能有一种方式互相到达。换言之，组织者要求新图中不能有环。现在组织者求助你，想请你帮忙算出这至多 $K$ 条地毯的美丽度之和最大为多少。

## 输入格式

第一行包含三个正整数 $n$、$m$、$K$。

接下来 $m$ 行中每行包含三个正整数 $u$、$v$、$w$。

## 输出格式

只包含一个正整数，表示这 $K$ 条地毯的美丽度之和的最大值。

## 样例

### 样例输入 #1
```
5 4 3
1 2 10
1 3 9
2 3 7
4 5 3
```
### 样例输出 #1
```
22
```
## 提示

选择第 $1$、$2$、$4$ 条地毯，美丽度之和为 $10 + 9 + 3 = 22$。

若选择第 $1$、$2$、$3$ 条地毯，虽然美丽度之和可以达到 $10 + 9 + 7 = 26$，但这将导致关键区域 $1$、$2$、$3$ 构成一个环，这是题目中不允许的。


$1\le n,m,k \le 10^5$。



---

---
title: "[USACO14MAR] Watering the Fields S"
layout: "post"
diff: 普及/提高-
pid: P2212
tag: ['2014', 'USACO', '生成树']
---
# [USACO14MAR] Watering the Fields S
## 题目描述

Due to a lack of rain, Farmer John wants to build an irrigation system to


send water between his N fields (1 <= N <= 2000).

Each field i is described by a distinct point (xi, yi) in the 2D plane,

with 0 <= xi, yi <= 1000.  The cost of building a water pipe between two

fields i and j is equal to the squared Euclidean distance between them:



(xi - xj)^2 + (yi - yj)^2

FJ would like to build a minimum-cost system of pipes so that all of his

fields are linked together -- so that water in any field can follow a

sequence of pipes to reach any other field.


Unfortunately, the contractor who is helping FJ install his irrigation

system refuses to install any pipe unless its cost (squared Euclidean


length) is at least C (1 <= C <= 1,000,000).  

Please help FJ compute the minimum amount he will need pay to connect all

his fields with a network of pipes.


给定 $n$ 个点，第 $i$ 个点的坐标为 $(x_i,y_i)$，如果想连通第 $i$ 个点与第 $j$ 个点，需要耗费的代价为两点的距离。第 $i$ 个点与第 $j$ 个点之间的距离使用欧几里得距离的平方进行计算，即：
$$(x_i-x_j)^2+(y_i-y_j)^2$$
我们规定耗费代价小于 $c$ 的两点无法连通，求使得每两点都能连通下的最小代价，如果无法连通输出 `-1`。
## 输入格式

\* Line 1: The integers N and C.


\* Lines 2..1+N: Line i+1 contains the integers xi and yi.

第一行两个整数 $n,c$ 代表点数与想要连通代价不能少于的一个数。   
接下来 $n$ 行每行两个整数 $x_i,y_i$ 描述第 $i$ 个点。
## 输出格式

\* Line 1: The minimum cost of a network of pipes connecting the

fields, or -1 if no such network can be built.

一行一个整数代表使得每两点都能连通下的最小代价，如果无法连通输出 `-1`。
## 样例

### 样例输入 #1
```
3 11
0 2
5 0
4 3
```
### 样例输出 #1
```
46
```
## 提示

INPUT DETAILS:


There are 3 fields, at locations (0,2), (5,0), and (4,3).  The contractor

will only install pipes of cost at least 11.

OUTPUT DETAILS:


FJ cannot build a pipe between the fields at (4,3) and (5,0), since its

cost would be only 10.  He therefore builds a pipe between (0,2) and (5,0)


at cost 29, and a pipe between (0,2) and (4,3) at cost 17.  

Source: USACO 2014 March Contest, Silver

### 数据规模与约定

对于 $100\%$ 的数据，$1 \le n \le 2000$，$0 \le x_i,y_i \le 1000$，$1 \le c \le 10^6$。

### 说明

Translated by 一只书虫仔。


---

---
title: "[USACO14MAR] The Lazy Cow S"
layout: "post"
diff: 普及/提高-
pid: P2213
tag: ['图论', '2014', 'USACO', '生成树', '前缀和']
---
# [USACO14MAR] The Lazy Cow S
## 题目描述

It's a hot summer day, and Bessie the cow is feeling quite lazy.  She wants

to locate herself at a position in her field so that she can reach as much

delicious grass as possible within only a short distance.


The field Bessie inhabits is described by an N by N grid of square cells

(1 <= N <= 400).  The cell in row r and column c (1 <= r,c <= N) contains

G(r,c) units of grass (0 <= G(r,c) <= 1000).  From her initial square in

the grid, Bessie is only willing to take up to K steps (0 <= K <= 2\*N).

Each step she takes moves her to a cell that is directly north, south,

east, or west of her current location.


For example, suppose the grid is as follows, where (B) describes Bessie's

```cpp
50    5     25*   6     17    
14    3*    2*    7*    21    
99*   10*   1*(B) 2*    80*    
8     7*    5*    23*   11   
10    0     78*   1     9        
```

initial position (here, in row 3, column 3):

If K=2, then Bessie can only reach the locations marked with \*s.

Please help Bessie determine the maximum amount of grass she can reach, if

she chooses the best possible initial location in the grid.

奶牛贝茜非常懒惰，她希望在她的地盘内找到一点最佳位置居住，以便在有限的步数内可以吃到尽量多的青草。

她的地盘是一个 $N \times N(1\le N \le 400)$ 的矩阵，第 $r$ 行 $c$ 列包含 $G(r,c)$ 单位的青草 $(0 \le G(r,c) \le 1000)$。从她的居住点，她最多愿意走 $K$ 步 $(0 \le K \le 2 \times N)$，每一步她可以走到上与她相邻的某个格子。
## 输入格式

\* Line 1: The integers N and K.


\* Lines 2..1+N: Line r+1 contains N integers describing row r of the

grid.
## 输出格式

\* Line 1: The maximum amount of grass Bessie can reach, if she chooses

the best possible initial location (the location from which

she can reach the most grass).

## 样例

### 样例输入 #1
```
5 2
50 5 25 6 17
14 3 2 7 21
99 10 1 2 80
8 7 5 23 11
10 0 78 1 9

```
### 样例输出 #1
```
342
```
## 提示

OUTPUT DETAILS:


In the example above, Bessie can reach 342 total units of grass if she

locates herself in the middle of the grid.


Source: USACO 2014 March Contest, Silver



---

---
title: "[SCOI2005] 繁忙的都市"
layout: "post"
diff: 普及/提高-
pid: P2330
tag: ['图论', '2005', '四川', '并查集', '各省省选', '生成树']
---
# [SCOI2005] 繁忙的都市
## 题目描述

城市 C 是一个非常繁忙的大都市，城市中的道路十分的拥挤，于是市长决定对其中的道路进行改造。城市 C 的道路是这样分布的：城市中有 $n$ 个交叉路口，有些交叉路口之间有道路相连，两个交叉路口之间最多有一条道路相连接。这些道路是双向的，且把所有的交叉路口直接或间接的连接起来了。每条道路都有一个分值，分值越小表示这个道路越繁忙，越需要进行改造。但是市政府的资金有限，市长希望进行改造的道路越少越好，于是他提出下面的要求：

1. 改造的那些道路能够把所有的交叉路口直接或间接的连通起来。
1. 在满足要求 1 的情况下，改造的道路尽量少。
1. 在满足要求 1、2 的情况下，改造的那些道路中分值最大的道路分值尽量小。

任务：作为市规划局的你，应当作出最佳的决策，选择哪些道路应当被修建。
## 输入格式

第一行有两个整数 $n,m$ 表示城市有 $n$ 个交叉路口，$m$ 条道路。

接下来 $m$ 行是对每条道路的描述，$u, v, c$ 表示交叉路口 $u$ 和 $v$ 之间有道路相连，分值为 $c$。
## 输出格式

两个整数 $s, \mathit{max}$，表示你选出了几条道路，分值最大的那条道路的分值是多少。
## 样例

### 样例输入 #1
```
4 5
1 2 3
1 4 5
2 4 7
2 3 6
3 4 8

```
### 样例输出 #1
```
3 6
```
## 提示

### 数据范围及约定

对于全部数据，满足 $1\le n\le 300$，$1\le c\le 10^4$，$1 \le m \le 8000$。


---

---
title: "[HAOI2006] 聪明的猴子"
layout: "post"
diff: 普及/提高-
pid: P2504
tag: ['图论', '2006', '河南', '各省省选', '生成树']
---
# [HAOI2006] 聪明的猴子
## 题目描述

在一个热带雨林中生存着一群猴子，它们以树上的果子为生。昨天下了一场大雨，现在雨过天晴，但整个雨林的地表还是被大水淹没着，部分植物的树冠露在水面上。猴子不会游泳，但跳跃能力比较强，它们仍然可以在露出水面的不同树冠上来回穿梭，以找到喜欢吃的果实。

现在，在这个地区露出水面的有 $N$ 棵树，假设每棵树本身的直径都很小，可以忽略不计。我们在这块区域上建立直角坐标系，则每一棵树的位置由其所对应的坐标表示(任意两棵树的坐标都不相同)。

在这个地区住着的猴子有 $M$ 个，下雨时，它们都躲到了茂密高大的树冠中，没有被大水冲走。由于各个猴子的年龄不同、身体素质不同，它们跳跃的能力不同。有的猴子跳跃的距离比较远(当然也可以跳到较近的树上)，而有些猴子跳跃的距离就比较近。这些猴子非常聪明，它们通过目测就可以准确地判断出自己能否跳到对面的树上。

现已知猴子的数量及每一个猴子的最大跳跃距离，还知道露出水面的每一棵树的坐标，你的任务是统计有多少个猴子可以在这个地区露出水面的所有树冠上觅食。

## 输入格式

输入包括：

第 $1$ 行为一个整数，表示猴子的个数 $M$ $(2 \le M \le 500)$；

第 $2$ 行为 $M$ 个整数，依次表示猴子的最大跳跃距离（每个整数值在 $1 \sim 1000$ 之间）；

第 $3$ 行为一个整数表示树的总棵数 $N$ $(2 \le N \le 1000)$ ；

第 $4$ 行至第 $N+3$ 行为 $N$ 棵树的坐标（横纵坐标均为整数，范围为：$-1000 \sim 1000$）。

（同一行的整数间用空格分开）

## 输出格式

输出包括一个整数，表示可以在这个地区的所有树冠上觅食的猴子数。
## 样例

### 样例输入 #1
```
4
 1 2 3 4
6
0 0
1 0
1 2
-1 -1
-2 0
2 2
```
### 样例输出 #1
```
3
```
## 提示

对于 $40\%$ 的数据，保证有 $2 \le N \le 100$，$1 \le M \le 100$

对于全部的数据，保证有 $2 \le N \le 1000$，$1 \le M \le500$

感谢 @charlie003 修正数据


---

---
title: "局域网"
layout: "post"
diff: 普及/提高-
pid: P2820
tag: ['图论', '并查集', '生成树']
---
# 局域网
## 题目背景

某个局域网内有 $n$ 台计算机，由于搭建局域网时工作人员的疏忽，现在局域网内的连接形成了回路，我们知道如果局域网形成回路那么数据将不停的在回路内传输，造成网络卡的现象。因为连接计算机的网线本身不同，所以有一些连线不是很畅通，我们用 $f(i,j)$ 表示 $i,j$ 之间连接的畅通程度，$f(i,j)$ 值越小表示 $i,j$ 之间连接越通畅，$f(i,j)$ 为 $0$ 表示 $i,j$ 之间无网线连接。
## 题目描述

现在需要解决回路问题，我们将除去一些连线，使得网络中没有回路，**不改变原图节点的连通性**，并且被除去网线的 $\sum f(i,j)$ 最大，请求出这个最大值。
## 输入格式

第一行两个正整数 $n,k$。

接下来的 $k$ 行每行三个正整数 $i,j,m$ 表示 $i,j$ 两台计算机之间有网线联通，通畅程度为 $m$。
## 输出格式

一个正整数， $\sum f(i,j)$ 的最大值。
## 样例

### 样例输入 #1
```
5 5
1 2 8
1 3 1
1 5 3
2 4 5
3 4 2

```
### 样例输出 #1
```
8
```
## 提示

对于全部数据，保证 $1\le n \le 100$，$1\le f(i,j)\le 1000$。



---

---
title: "[USACO07DEC] Building Roads S"
layout: "post"
diff: 普及/提高-
pid: P2872
tag: ['图论', '2007', 'USACO', '生成树']
---
# [USACO07DEC] Building Roads S
## 题目描述

Farmer John had just acquired several new farms! He wants to connect the farms with roads so that he can travel from any farm to any other farm via a sequence of roads; roads already connect some of the farms.

Each of the N (1 ≤ N ≤ 1,000) farms (conveniently numbered 1..N) is represented by a position (Xi, Yi) on the plane (0 ≤ Xi ≤ 1,000,000; 0 ≤ Yi ≤ 1,000,000). Given the preexisting M roads (1 ≤ M ≤ 1,000) as pairs of connected farms, help Farmer John determine the smallest length of additional roads he must build to connect all his farms.

给定 $n$ 个点的坐标，第 $i$ 个点的坐标为 $(x_i,y_i)$，这 $n$ 个点编号为 $1$ 到 $n$。给定 $m$ 条边，第 $i$ 条边连接第 $u_i$ 个点和第 $v_i$ 个点。现在要求你添加一些边，并且能使得任意一点都可以连通其他所有点。求添加的边的总长度的最小值。

## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..N+1: Two space-separated integers: Xi and Yi

\* Lines N+2..N+M+2: Two space-separated integers: i and j, indicating that there is already a road connecting the farm i and farm j.

第一行两个整数 $n,m$ 代表点数与边数。   
接下来 $n$ 行每行两个整数 $x_i,y_i$ 代表第 $i$ 个点的坐标。   
接下来 $m$ 行每行两个整数 $u_i,v_i$ 代表第 $i$ 条边连接第 $u_i$ 个点和第 $v_i$ 个点。

## 输出格式

\* Line 1: Smallest length of additional roads required to connect all farms, printed without rounding to two decimal places. Be sure to calculate distances as 64-bit floating point numbers.

一行一个实数代表添加的边的最小长度，要求保留两位小数，为了避免误差， 请用 $64$ 位实型变量进行计算。

## 样例

### 样例输入 #1
```
4 1
1 1
3 1
2 3
4 3
1 4
```
### 样例输出 #1
```
4.00
```
## 提示

### 数据规模与约定

对于 $100\%$ 的整数，$1 \le n,m \le 1000$，$1 \le x_i,y_i \le 10^6$，$1 \le u_i,v_i \le n$。

### 说明

Translated by 一只书虫仔。


---

---
title: "[USACO08NOV] Cheering up the Cow G"
layout: "post"
diff: 普及/提高-
pid: P2916
tag: ['2008', 'USACO', '生成树']
---
# [USACO08NOV] Cheering up the Cow G
## 题目描述

Farmer John has grown so lazy that he no longer wants to continue maintaining the cow paths that currently provide a way to visit each of his N (5 <= N <= 10,000) pastures (conveniently numbered 1..N). Each and every pasture is home to one cow. FJ plans to remove as many of the P (N-1 <= P <= 100,000) paths as possible while keeping the pastures connected. You must determine which N-1 paths to keep.

Bidirectional path j connects pastures S\_j and E\_j (1 <= S\_j <= N; 1 <= E\_j <= N; S\_j != E\_j) and requires L\_j (0 <= L\_j <= 1,000) time to traverse. No pair of pastures is directly connected by more than one path.

The cows are sad that their transportation system is being reduced. You must visit each cow at least once every day to cheer her up. Every time you visit pasture i (even if you're just traveling

through), you must talk to the cow for time C\_i (1 <= C\_i <= 1,000).

You will spend each night in the same pasture (which you will choose) until the cows have recovered from their sadness. You will end up talking to the cow in the sleeping pasture at least in the morning when you wake up and in the evening after you have returned to sleep.

Assuming that Farmer John follows your suggestions of which paths to keep and you pick the optimal pasture to sleep in, determine the minimal amount of time it will take you to visit each cow at least once in a day.

For your first 10 submissions, you will be provided with the results of running your program on a part of the actual test data.

POINTS: 300

约翰有N个牧场，编号依次为1到N。每个牧场里住着一头奶牛。连接这些牧场的有P条道路，每条道路都是双向的。第j条道路连接的是牧场Sj和Ej，通行需要Lj的时间。两牧场之间最多只有一条道路。约翰打算在保持各牧场连通的情况下去掉尽量多的道路。 

约翰知道，在道路被强拆后，奶牛会非常伤心，所以他计划拆除道路之后就去忽悠她们。约翰可以选择从任意一个牧场出发开始他维稳工作。当他走访完所有的奶牛之后，还要回到他的出发地。每次路过牧场i的时候，他必须花Ci的时间和奶牛交谈，即使之前已经做过工作了，也要留下来再谈一次。注意约翰在出发和回去的时候，都要和出发地的奶牛谈一次话。请你计算一下，约翰要拆除哪些道路，才能让忽悠奶牛的时间变得最少？

## 输入格式

\* Line 1: Two space-separated integers: N and P

\* Lines 2..N+1: Line i+1 contains a single integer: C\_i

\* Lines N+2..N+P+1: Line N+j+1 contains three space-separated

integers: S\_j, E\_j, and L\_j

## 输出格式

\* Line 1: A single integer, the total time it takes to visit all the cows (including the two visits to the cow in your

sleeping-pasture)

## 样例

### 样例输入 #1
```
5 7 
10 
10 
20 
6 
30 
1 2 5 
2 3 5 
2 4 12 
3 4 17 
2 5 15 
3 5 6 
4 5 12 

```
### 样例输出 #1
```
176 

```
## 提示

```cpp
   +-(15)-+ 
  /        \ 
 /          \ 
1-(5)-2-(5)-3-(6)--5 
   \   /(17)  / 
(12)\ /      /(12) 
     4------+ 

Keep these paths: 
1-(5)-2-(5)-3      5 
       \          / 
    (12)\        /(12) 
        *4------+ 
```
Wake up in pasture 4 and visit pastures in the order 4, 5, 4, 2, 3, 2, 1, 2, 4 yielding a total time of 176 before going back to sleep.



---

---
title: "【模板】最小生成树"
layout: "post"
diff: 普及/提高-
pid: P3366
tag: ['生成树']
---
# 【模板】最小生成树
## 题目描述

如题，给出一个无向图，求出最小生成树，如果该图不连通，则输出 `orz`。

## 输入格式

第一行包含两个整数 $N,M$，表示该图共有 $N$ 个结点和 $M$ 条无向边。

接下来 $M$ 行每行包含三个整数 $X_i,Y_i,Z_i$，表示有一条长度为 $Z_i$ 的无向边连接结点 $X_i,Y_i$。

## 输出格式

如果该图连通，则输出一个整数表示最小生成树的各边的长度之和。如果该图不连通则输出 `orz`。

## 样例

### 样例输入 #1
```
4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3
```
### 样例输出 #1
```
7
```
## 提示

数据规模：

对于 $20\%$ 的数据，$N\le 5$，$M\le 20$。

对于 $40\%$ 的数据，$N\le 50$，$M\le 2500$。

对于 $70\%$ 的数据，$N\le 500$，$M\le 10^4$。

对于 $100\%$ 的数据：$1\le N\le 5000$，$1\le M\le 2\times 10^5$，$1\le Z_i \le 10^4$。


样例解释：

 ![](https://cdn.luogu.com.cn/upload/pic/2259.png) 

所以最小生成树的总边权为 $2+2+3=7$。



---

---
title: "[USACO15FEB] Superbull S"
layout: "post"
diff: 普及/提高-
pid: P4826
tag: ['2015', 'USACO', '图论建模', '生成树']
---
# [USACO15FEB] Superbull S
## 题目描述

Bessie and her friends are playing hoofball in the annual Superbull championship, and Farmer John is in charge of making the tournament as exciting as possible. A total of $N$ $(1 <= N <= 2000)$ teams are playing in the Superbull. Each team is assigned a distinct integer team ID in the range 1...2^30-1 to distinguish it from the other teams. The Superbull is an elimination tournament -- after every game, Farmer John chooses which team to eliminate from the Superbull, and the eliminated team can no longer play in any more games. The Superbull ends when only one team remains.

Farmer John notices a very unusual property about the scores in matches! In any game, the combined score of the two teams always ends up being the bitwise exclusive OR (XOR) of the two team IDs. For example, if teams 12 and 20 were to play, then 24 points would be scored in that game, since 01100 XOR 10100 = 11000.

Farmer John believes that the more points are scored in a game, the more exciting the game is. Because of this, he wants to choose a series of games to be played such that the total number of points scored in the Superbull is maximized. Please help Farmer John organize the matches.
## 输入格式

The first line contains the single integer $N$. The following $N$ lines contain the N team IDs.
## 输出格式

Output the maximum possible number of points that can be scored in the Superbull.
## 样例

### 样例输入 #1
```
4
3
6
9
10
```
### 样例输出 #1
```
37
```
## 提示

OUTPUT DETAILS: One way to achieve 37 is as follows: FJ matches teams 3 and 9, and decides that 9 wins, so teams 6, 9, and 10 are left in the tournament. He then matches teams 6 and 9, and lets team 6 win. Teams 6 and 10 are then left in the tournament. Finally, teams 6 and 10 face off, and team 10 wins. The total number of points scored is (3 XOR 9) + (6 XOR 9) + (6 XOR 10) = 10 + 15 + 12 = 37.

NOTE: The bitwise exclusive OR operation, commonly denoted by the ^ symbol, is a bitwise operation that performs the logical exclusive OR operation on each position in two binary integers. The result in each position is 1 if only the first bit is 1 or only the second bit is 1, but is 0 if both bits are 0 or both are 1. For example: 10100 (decimal 20) XOR 01100 (decimal 12) = 11000 (decimal 24)

[Problem credits: Alex Yang, 2015] 
## 题目翻译

### 题目描述

Bessie 和她的朋友们正在一年一度的 Superbull 锦标赛中比赛，Farmer John 负责让比赛尽可能精彩。总共有 $N$ $(1 \leq N \leq 2000)$ 支队伍参加 Superbull。每支队伍都被分配了一个唯一的整数队伍 ID，范围在 $1 \ldots 2^{30}-1$ 之间，用于区分不同队伍。Superbull 是淘汰制比赛——每场比赛后，Farmer John 会选择淘汰其中一支队伍，被淘汰的队伍将不再参与后续比赛。当只剩一支队伍时，Superbull 结束。

Farmer John 发现比赛得分有一个特殊性质：任意一场比赛中，两支队伍的得分总和总是等于两队 ID 的按位异或（XOR）。例如，若队伍 12 和 20 比赛，则该场比赛总得分为 $24$，因为 $01100 \oplus 10100 = 11000$（即 $12 \oplus 20 = 24$）。

Farmer John 认为比赛总得分越高越精彩。因此，他希望安排一系列比赛，使得 Superbull 所有比赛的总得分最大化。请帮助他设计比赛方案。

### 输入格式

第一行包含整数 $N$。接下来的 $N$ 行每行包含一个队伍 ID。

### 输出格式

输出 Superbull 所有比赛可能获得的最大总得分。

### 说明/提示

**输出样例解释**：  
一种获得 37 分的方案如下：  
1. Farmer John 让队伍 3 和 9 比赛，选择淘汰 9，此时剩余队伍为 6、9、10  
2. 让队伍 6 和 9 比赛，选择淘汰 9，此时剩余队伍为 6 和 10  
3. 最后让队伍 6 和 10 比赛  
总得分为 $(3 \oplus 9) + (6 \oplus 9) + (6 \oplus 10) = 10 + 15 + 12 = 37$。

**关于按位异或**：  
按位异或运算（记作 $\oplus$）对两个二进制数的每一位进行逻辑异或操作。当且仅当某一位上两个数不同时，结果的该位为 1。例如：  
$10100$（十进制 20）$\oplus$ $01100$（十进制 12）$= 11000$（十进制 24）


---

---
title: "[ICPC 2021 Macao R] Link-Cut Tree"
layout: "post"
diff: 普及/提高-
pid: P9666
tag: ['2021', 'O2优化', '生成树', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] Link-Cut Tree
## 题目描述

BaoBao just learned how to use a data structure called link-cut tree to find cycles in a graph and decided to give it a try. BaoBao is given an undirected graph with $n$ vertices and $m$ edges, where the length of the $i$-th edge equals $2^i$. She needs to find a simple cycle with the smallest length.

A simple cycle is a subgraph of the original graph containing $k$ ($3 \le k \le n$) vertices $a_1, a_2, \cdots, a_k$ and $k$ edges such that for all $1 \le i \le k$ there is an edge connecting vertices $a_i$ and $a_{(i \mod k) + 1}$ in the subgraph. The length of a simple cycle is the total length of the edges in the cycle.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($3 \le n \le 10^5$, $1 \le m \le 10^5$) indicating the number of vertices and edges in the original graph.

For the following $m$ lines, the $i$-th line contains two integers $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$) indicating an edge connecting vertices $u_i$ and $v_i$ with length $2^i$. There are no self loops nor multiple edges. Note that the graph is not necessarily connected.

It's guaranteed that neither the sum of $n$ nor the sum of $m$ of all test cases will exceed $10^6$.
## 输出格式

For each test case output one line. If there are no simple cycles in the graph output ``-1`` (without quotes); Otherwise output $k$ integers separated by a space in increasing order indicating the indices of the edges in the simple cycle with the smallest length. It can be shown that there is at most one answer.

Please, DO NOT output extra spaces at the end of each line, or your solution may be considered incorrect!
## 样例

### 样例输入 #1
```
2
6 8
1 2
2 3
5 6
3 4
2 5
5 4
5 1
4 2
4 2
1 2
4 3
```
### 样例输出 #1
```
2 4 5 6
-1
```
## 提示

The first sample test case is shown below. The integers beside the edges are their indices (outside the parentheses) and lengths (inside the parentheses). The simple cycle with the smallest length consists of edges $2$, $4$, $5$ and $6$ with a length of $2^2 + 2^4 + 2^5 + 2^6 = 116$.
## 题目翻译


BaoBao刚学会如何用一种叫做 LCT 的数据结构去找图中的环，因此决定试一试。BaoBao 得到一个有 $n$ 个点，$m$    条边的无向图，其中第 $i$ 条边的权值为 $2^i$。她需要找到一个权值最小的环。

环是原图的子图，包含 $k$ ($3 \le k \le n$) 个点 $a_1, a_2, \cdots, a_k$ 和 $k$ 条边，使得对于所有的 $1 \le i \le k$ ，子图中存在边连接点 $a_i$ 和 $a_{(i \mod k) + 1}$ 。环的权值为环上所有边的权值之和。

每一个测试点有多组测试数据。 第一行有一个整数 $T$ 表示数据组数。

第二行有两个整数 $n$ 和 $m$ ($3 \le n \le 10^5$, $1 \le m \le 10^5$)，分别为点数和边数。

接下来 $m$ 行， 第 $i$ 行包括两个整数 $u_i$ 和 $v_i$ ($1 \le u_i, v_i \le n$) 表示有一条边连接 $u_i$ 和 $v_i$ ，权值为 $2^i$。 请注意，图 **不一定** 连通。

保证所有测试样例 $n$ 之和， $m$ 之和均不超过 $10^6$.

对每一组测试数据输出一行。如果图中没有环，输出 ``-1`` 。 否则 **升序** 输出边的编号，共 $k$ 个整数 ， 显然答案唯一。

第一个测试样例如图，图中标注出的为边的编号，环 $2$, $4$, $5$, $6$ 边权为 $2^2 + 2^4 + 2^5 + 2^6 = 116$，为最小环。

![](https://cdn.luogu.com.cn/upload/image_hosting/vqpea23u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


---

