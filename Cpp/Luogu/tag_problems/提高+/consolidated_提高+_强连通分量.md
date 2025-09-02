---
title: "[NOIP 2009 提高组] 最优贸易"
layout: "post"
diff: 提高+/省选-
pid: P1073
tag: ['动态规划 DP', '搜索', '图论', '2009', 'NOIP 提高组', '最短路', '强连通分量']
---
# [NOIP 2009 提高组] 最优贸易
## 题目背景

本题原题数据极弱，Subtask 0 中的测试点为原题测试点，Subtask 1 中的测试点为 Hack 数据。
## 题目描述

$C$ 国有 $n$ 个大城市和 $m$ 条道路，每条道路连接这 $n$ 个城市中的某两个城市。任意两个城市之间最多只有一条道路直接相连。这 $m$ 条道路中有一部分为单向通行的道路，一部分为双向通行的道路，双向通行的道路在统计条数时也计为 $1$ 条。

$C$ 国幅员辽阔，各地的资源分布情况各不相同，这就导致了同一种商品在不同城市的价格不一定相同。但是，同一种商品在同一个城市的买入价和卖出价始终是相同的。

商人阿龙来到 $C$ 国旅游。当他得知同一种商品在不同城市的价格可能会不同这一信息之后，便决定在旅游的同时，利用商品在不同城市中的差价赚回一点旅费。设 $C$ 国 $n$ 个城市的标号从 $1\sim n$，阿龙决定从 $1$ 号城市出发，并最终在 $n$ 号城市结束自己的旅行。在旅游的过程中，任何城市可以重复经过多次，但不要求经过所有 $n$ 个城市。阿龙通过这样的贸易方式赚取旅费：他会选择一个经过的城市买入他最喜欢的商品――水晶球，并在之后经过的另一个城市卖出这个水晶球，用赚取的差价当做旅费。由于阿龙主要是来 $C$ 国旅游，他决定这个贸易只进行最多一次，当然，在赚不到差价的情况下他就无需进行贸易。

假设 $C$ 国有 $5$ 个大城市，城市的编号和道路连接情况如下图，单向箭头表示这条道路为单向通行，双向箭头表示这条道路为双向通行。

![](https://cdn.luogu.com.cn/upload/image_hosting/flre534z.png)

假设 $1\sim n$ 号城市的水晶球价格分别为 $4,3,5,6,1$。

阿龙可以选择如下一条线路：$1\to2\to3\to5$，并在 $2$ 号城市以 $3$ 的价格买入水晶球，在 $3$ 号城市以 $5$ 的价格卖出水晶球，赚取的旅费数为 $2$。

阿龙也可以选择如下一条线路：$1\to4\to5\to4\to5$，并在第 $1$ 次到达 $5$ 号城市时以 $1$ 的价格买入水晶球，在第 $2$ 次到达 $4$ 号城市时以 $6$ 的价格卖出水晶球，赚取的旅费数为 $5$。

现在给出 $n$ 个城市的水晶球价格，$m$ 条道路的信息（每条道路所连接的两个城市的编号以及该条道路的通行情况）。请你告诉阿龙，他最多能赚取多少旅费。
## 输入格式

第一行包含 $2$ 个正整数 $n$ 和 $m$，中间用一个空格隔开，分别表示城市的数目和道路的数目。

第二行 $n$ 个正整数，每两个整数之间用一个空格隔开，按标号顺序分别表示这 $n$ 个城市的商品价格。

接下来 $m$ 行，每行有 $3$ 个正整数 $x,y,z$，每两个整数之间用一个空格隔开。如果 $z=1$，表示这条道路是城市 $x$ 到城市 $y$ 之间的单向道路；如果 $z=2$，表示这条道路为城市 $x$ 和城市 $y$ 之间的双向道路。


## 输出格式

一个整数，表示最多能赚取的旅费。如果没有进行贸易，则输出 $0$。
## 样例

### 样例输入 #1
```
5 5 
4 3 5 6 1 
1 2 1 
1 4 1 
2 3 2 
3 5 1 
4 5 2 
```
### 样例输出 #1
```
5
```
## 提示

【数据范围】

输入数据保证 $1$ 号城市可以到达 $n$ 号城市。

对于 $10\%$ 的数据，$1\leq n\leq 6$。

对于 $30\%$ 的数据，$1\leq n\leq 100$。

对于 $50\%$ 的数据，不存在一条旅游路线，可以从一个城市出发，再回到这个城市。

对于 $100\%$ 的数据，$1\leq n\leq 100000$，$1\leq m\leq 500000$，$1\leq  x,y\leq  n$，$1\leq  z\leq  2$，$1\leq $ 各城市的编号 $\leq  n$。

水晶球价格 $\leq 100$。

NOIP 2009 提高组 第三题


---

---
title: "[GCJ 2019 #2] Contransmutation"
layout: "post"
diff: 提高+/省选-
pid: P13118
tag: ['动态规划 DP', '图论', '2019', '拓扑排序', '强连通分量', 'Google Code Jam']
---
# [GCJ 2019 #2] Contransmutation
## 题目描述

Last year, we asked you to help us convert expensive metals into lead. (You do not need to know anything about the previous problem to solve this one.) But your country's leader is still greedy for more lead!

There are $\mathbf{M}$ metals known in the world; lead is metal number 1 on your periodic table. Your country's leader has asked you to use the metals in the treasury to make as much lead as possible.

For each metal (including lead), you know exactly one formula that lets you destroy one gram of that metal and create one gram each of two metals. (It is best not to think too much about the principle of mass conservation!) Note that it is possible that the formula for the i-th metal might produce the i-th metal as one of the products. The formulas do not work with partial grams. However, you can use each formula as often as you would like (or not at all), as long as you have a gram of the required ingredient.

If you make optimal choices, what is the largest number of grams of lead you can end up with, or is it unbounded? If it is not unbounded: since the output can be a really big number, we only ask you to output the remainder of dividing the result by the prime $10^9+7$ (that is, $1000000007$).
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each begins with one line with an integer $\mathbf{M}$: the number of metals known in the world. Then there are $\mathbf{M}$ more lines with two integers $\mathbf{R_{i1}}$ and $\mathbf{R_{i2}}$ each; the i-th of these lines, counting starting from 1, indicates that you can destroy one gram of metal i to create one gram of metal $\mathbf{R_{i1}}$ and one gram of metal $\mathbf{R_{i2}}$. Finally, there is one line with $\mathbf{M}$ integers $\mathbf{G_1}$, $\mathbf{G_2}$, ..., $\mathbf{G_M}$; $\mathbf{G_i}$ is the number of grams of metal i in the treasury. Lead is metal 1.

## 输出格式

For each test case, output one line containing `Case #x: y` where $x$ is the test case number (starting from 1). If there is no bound on the maximum amount of lead that can be produced, $y$ must be UNBOUNDED. Otherwise, $y$ must be the largest amount of lead, in grams, that you can end up with, modulo the prime $10^9+7$ (that is, $1000000007$).
## 样例

### 样例输入 #1
```
3
2
1 2
1 2
1 0
2
1 2
1 2
0 0
4
2 4
3 4
2 4
2 3
10 10 10 10
```
### 样例输出 #1
```
Case #1: UNBOUNDED
Case #2: 0
Case #3: 10
```
## 提示

**Sample Explanation**

In Sample Case #1, you have one formula that turns 1 gram of lead into 1 gram of lead and 1 gram of the second metal, and another formula that turns 1 gram of the second metal into 1 gram of lead and 1 gram of the second metal. You can alternate between these formulas to produce as much of both metals as you want.

Sample Case #2 has the same formulas as Sample Case #1, but you have no metals to start with!

In Sample Case #3, none of the formulas help you produce more lead, so you cannot end up with more lead than you started with.

**Limits**

- $1 \leq \mathbf{R_{i1}} < \mathbf{R_{i2}} \leq \mathbf{M}$, for all $i$.

**Test set 1 (7 Pts, Visible)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{M} \leq 10$.
- $0 \leq \mathbf{G_i} \leq 10$, for all $i$.

**Test set 2 (16 Pts, Hidden)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{M} \leq 100$.
- $0 \leq \mathbf{G_i} \leq 10^9$, for all $i$.

**Test set 3 (6 Pts, Hidden)**

- $1 \leq \mathbf{T} \leq 5$.
- $2 \leq \mathbf{M} \leq 10^5$.
- $0 \leq \mathbf{G_i} \leq 10^9$, for all $i$.


---

---
title: "[国家集训队] 稳定婚姻"
layout: "post"
diff: 提高+/省选-
pid: P1407
tag: ['强连通分量', 'Tarjan', '二分图']
---
# [国家集训队] 稳定婚姻
## 题目描述

我们已知 $n$ 对夫妻的婚姻状况，称第 $i$ 对夫妻的男方为 $B_i$，女方为 $G_i$。若某男 $B_i$ 与某女 $G_j$ 曾经交往过（无论是大学，高中，亦或是幼儿园阶段，$i \le j$），则当某方与其配偶（即 $B_i$ 与 $G_i$ 或 $B_j$ 与 $G_j$）感情出现问题时，他们有私奔的可能性。不妨设 $B_i$ 和其配偶 $G_i$ 感情不和，于是 $B_i$ 和 $G_j$ 旧情复燃，进而 $B_j$ 因被戴绿帽而感到不爽，联系上了他的初恋情人 $G_k$ ……一串串的离婚事件像多米诺骨牌一般接踵而至。若在 $B_i$ 和 $G_i$ 离婚的前提下，这 $2n$ 个人最终依然能够结合成 $n$ 对情侣，那么我们称婚姻 $i$ 为不安全的，否则婚姻 $i$ 就是安全的。

给定所需信息，你的任务是判断每对婚姻是否安全。
## 输入格式

第一行为一个正整数 $n$，表示夫妻的对数；

以下 $n$ 行，每行包含两个字符串，表示这 $n$ 对夫妻的姓名（先女后男），由一个空格隔开；

第 $n+2$ 行包含一个正整数 $m$，表示曾经相互喜欢过的情侣对数；

以下 $m$ 行，每行包含两个字符串，表示这 $m$ 对相互喜欢过的情侣姓名（先女后男），由一个空格隔开。
## 输出格式

输出文件共包含 $n$ 行，第 $i$ 行为 `Safe`（如果婚姻 $i$ 是安全的）或 `Unsafe`（如果婚姻 $i$ 是不安全的）。

## 样例

### 样例输入 #1
```
2
Melanie Ashley
Scarlett Charles
1
Scarlett Ashley
```
### 样例输出 #1
```
Safe
Safe
```
### 样例输入 #2
```
2
Melanie Ashley
Scarlett Charles
2
Scarlett Ashley
Melanie Charles
```
### 样例输出 #2
```
Unsafe
Unsafe
```
## 提示

对于 $20\%$ 的数据，$n \le 20$；

对于 $40\%$ 的数据，$n \le 100$，$m \le 400$；

对于 $100\%$ 的数据，所有姓名字符串中只包含英文大小写字母，大小写敏感，长度不大于 $8$，保证每对关系只在输入文件中出现一次，输入文件的最后 $m$ 行不会出现未在之前出现过的姓名，这 $2n$ 个人的姓名各不相同，$1 \le n \le 4000$，$0 \le m \le 20000$。


---

---
title: "[USACO04DEC] Cow Ski Area G"
layout: "post"
diff: 提高+/省选-
pid: P1653
tag: ['图论', '2004', 'USACO', '强连通分量', 'Tarjan']
---
# [USACO04DEC] Cow Ski Area G
## 题目描述

约翰的表哥罗恩生活在科罗拉多州。他近来打算教他的奶牛们滑雪，但是奶牛们非常害羞，不敢在游人组织的度假胜地滑雪。没办法，他只好自己建滑雪场了。罗恩的雪场可以划分为 $W$ 列 $L$ 行 $(1\le W\le 500, 1\le L\le 500)$，每个方格有一个特定的高度 $H(0\le H\le 9999)$。奶牛可以在相邻方格间滑雪，而且不能由低到高滑。

为了保证任意方格可以互通，罗恩打算造一些直达缆车。缆车很强大，可以连接任意两个方格，而且是双向的。而且同一个方格也可以造多台缆车。但是缆车的建造费用贵得吓人，所以他希望造尽量少的缆车。那最少需要造多少台呢？
## 输入格式

第 $1$ 行：$W$，$L$。

接下来输入宽 $W$ 高 $L$ 的矩阵地图。
## 输出格式

输出最小需要的缆车数。
## 样例

### 样例输入 #1
```
9 3
1 1 1 2 2 2 1 1 1
1 2 1 2 3 2 1 2 1
1 1 1 2 2 2 1 1 1
```
### 样例输出 #1
```
3
```
## 提示

$1\le W,L\le 500$，$0\le H\le 9999$。


---

---
title: "HXY烧情侣"
layout: "post"
diff: 提高+/省选-
pid: P2194
tag: ['图论', '强连通分量']
---
# HXY烧情侣
## 题目描述

众所周知，HXY 已经加入了 FFF 团。现在她要开始喜（sang）闻（xin）乐（bing）见（kuang）地烧情侣了。

这里有 $n$ 座电影院，$n$ 对情侣分别在每座电影院里，然后电影院里都有汽油，但是要使用它需要一定的费用。$m$ 条单向通道连接相邻的两对情侣所在电影院。

HXY 有个绝技，如果她能从一个点开始烧，最后回到这个点，那么烧这条回路上的情侣的费用只需要该点的汽油费即可。并且每对情侣只需烧一遍，电影院可以重复去。然后她想花尽可能少的费用烧掉所有的情侣。

问：最少需要多少费用，并且当费用最少时的方案数是多少？由于方案数可能过大，所以请输出方案数对 $10^9+7$ 取模的结果。

（注：这里 HXY 每次可以从任何一个点开始走回路。就是说一个回路走完了，下一个开始位置可以任选。所以说不存在烧不了所有情侣的情况，即使图不连通，HXY 自行选择顶点进行烧情侣行动。且走过的道路可以重复走。）
## 输入格式

第一行一个正整数 $n$。   
第二行 $n$ 个正整数，表示每个点的汽油费 $w_i$。  
第三行一个正整数 $m$。  
接下来 $m$ 行，每行两个正整数 $x_i,y_i$，表示一条 $x_i \to y_i$ 的单向道路。
## 输出格式

输出一行两个整数，分别表示最小花费，和花费最小时的方案数。
## 样例

### 样例输入 #1
```
3
1 2 3
3
1 2
2 3
3 2
```
### 样例输出 #1
```
3 1

```
### 样例输入 #2
```
3
10 20 10
4
1 2
1 3
3 1
2 1

```
### 样例输出 #2
```
10 2

```
## 提示

对于 $30\%$ 的数据，$1\le n,m \le 20$；  
对于另外 $10\%$ 的数据，保证不存在回路；  
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le m \le 3\times 10^5$，$0\le w_i \le 10^9$。


---

---
title: "[SDOI2010] 所驼门王的宝藏"
layout: "post"
diff: 提高+/省选-
pid: P2403
tag: ['2010', '各省省选', '山东', '拓扑排序', '强连通分量', 'Tarjan']
---
# [SDOI2010] 所驼门王的宝藏
## 题目描述

在宽广的非洲荒漠中，生活着一群勤劳勇敢的羊驼家族。被族人恭称为“先知”的 AlpacaL.Sotomon 是这个家族的领袖，外人也称其为“所驼门王”。所驼门王毕生致力于维护家族的安定与和谐，他曾亲自率军粉碎河蟹帝国主义的野蛮侵略，为族人立下赫赫战功。所驼门王一生财宝无数，但因其生性节俭低调，他将财宝埋藏在自己设计的地下宫殿里，这也是今天 Henry Curtis 故事的起点。Henry 是一个爱财如命的贪婪家伙，而又非常聪明，他费尽心机谋划了这次盗窃行动，破解重重机关后来到这座地下宫殿前。

整座宫殿呈矩阵状，由 $R \times C$ 间矩形宫室组成，其中有 $N$ 间宫室里埋藏着宝藏，称作藏宝宫室。宫殿里外、相邻宫室间都由坚硬的实体墙阻隔，由一间宫室到达另一间只能通过所驼门王独创的移动方式——传送门。所驼门王为这 $N$ 间藏宝宫室每间都架设了一扇传送门，没有宝藏的宫室不设传送门，所有的宫室传送门分为三种：

1. “横天门”：由该门可以传送到同行的任一宫室；
2. “纵寰门”：由该门可以传送到同列的任一宫室；
3. “任意门”：由该门可以传送到以该门所在宫室为中心周围 $8$ 格中任一宫室（如果目标宫室存在的话）。

深谋远虑的 Henry 当然事先就搞到了所驼门王当年的宫殿招标册，书册上详细记录了每扇传送门所属宫室及类型。而且，虽然宫殿内外相隔，但他自行准备了一种便携式传送门，可将自己传送到殿内任意一间宫室开始寻宝，并在任意一间宫室结束后传送出宫。整座宫殿只许进出一次，且便携门无法进行宫室之间的传送。不过好在宫室内传送门的使用没有次数限制，每间宫室也可以多次出入。

现在 Henry 已经打开了便携门，即将选择一间宫室进入。为得到尽多宝藏，他希望安排一条路线，使走过的不同藏宝宫室尽可能多。请你告诉 Henry 这条路线最多行经不同藏宝宫室的数目。
## 输入格式

第一行给出三个正整数 $N,R,C$。

以下 $N$ 行，每行给出一扇传送门的信息，包含三个正整数 $x_i,y_i,T_i$，表示该传送门设在位于第 $x_i$ 行第 $y_i$ 列的藏宝宫室，类型为 $T_i$。$T_i$ 是一个 $1 \sim 3$ 间的整数，$1$ 表示可以传送到第 $x_i$ 行任意一列的“横天门”，$2$ 表示可以传送到任意一行第 $y_i$ 列的“纵寰门”，$3$ 表示可以传送到周围 $8$ 格宫室的“任意门”。

保证 $1 \le x_i \le R$，$1 \le y_i \le C$，所有的传送门位置互不相同。
## 输出格式

输出只有一个正整数，表示你确定的路线所经过不同藏宝宫室的最大数目。

## 样例

### 样例输入 #1
```
10 7 7
2 2 1
2 4 2
1 7 2
2 7 3
4 2 2
4 4 1
6 7 3
7 7 1
7 5 2
5 2 1
```
### 样例输出 #1
```
9
```
## 提示

数据规模和约定：

![](https://cdn.luogu.com.cn/upload/pic/1594.png)



---

---
title: "[HAOI2010] 软件安装"
layout: "post"
diff: 提高+/省选-
pid: P2515
tag: ['动态规划 DP', '2010', '河南', '各省省选', '强连通分量', 'Tarjan']
---
# [HAOI2010] 软件安装
## 题目描述

现在我们的手头有 $N$ 个软件，对于一个软件 $i$，它要占用 $W_i$ 的磁盘空间，它的价值为 $V_i$。我们希望从中选择一些软件安装到一台磁盘容量为 $M$ 计算机上，使得这些软件的价值尽可能大（即 $V_i$ 的和最大）。

但是现在有个问题：软件之间存在依赖关系，即软件 $i$ 只有在安装了软件 $j$（包括软件 $j$ 的直接或间接依赖）的情况下才能正确工作（软件 $i$ 依赖软件 $j$)。幸运的是，一个软件最多依赖另外一个软件。如果一个软件不能正常工作，那么它能够发挥的作用为 $0$。


我们现在知道了软件之间的依赖关系：软件 $i$ 依赖软件 $D_i$。现在请你设计出一种方案，安装价值尽量大的软件。一个软件只能被安装一次，如果一个软件没有依赖则 $D_i=0$，这时只要这个软件安装了，它就能正常工作。
## 输入格式

第 1 行：$N,M(0\leq N\leq 100, 0\leq M\leq 500)$

第 2 行：$W_1,W_2, ... W_i, ..., W_n (0\leq W_i\leq M)$

第 3 行：$V_1, V_2, ..., V_i, ..., V_n  (0\leq V_i\leq 1000)$

第 4 行：$D_1, D_2, ..., D_i, ..., D_n (0\leq D_i\leq N, D_i≠i)$
## 输出格式

一个整数，代表最大价值。

## 样例

### 样例输入 #1
```
3 10
5 5 6
2 3 4
0 1 1
```
### 样例输出 #1
```
5
```


---

---
title: "有机化学之神偶尔会做作弊"
layout: "post"
diff: 提高+/省选-
pid: P2783
tag: ['图论', '强连通分量', '最近公共祖先 LCA']
---
# 有机化学之神偶尔会做作弊
## 题目背景

XS 中学化学竞赛组教练是一个酷爱炉石的人。

有一天他一边搓炉石一边监考，而你作为一个信息竞赛的大神也来凑热闹。

然而你的化竞基友却向你求助了。

“第 1354 题怎么做？”<--手语  他问道。
## 题目描述

你翻到那一题：给定一个烃，只含有单键（给初中生的一个理解性解释：就是一堆碳用横线连起来，横线都是单条的）。

然后炎魔之王拉格纳罗斯用他的火焰净化了一切环（？？？）。所有的环状碳都变成了一个碳，如图所示。

![环状碳变为一个碳](https://cdn.luogu.com.cn/upload/pic/2758.png)

然后指定多组碳，求出它们之间总共有多少碳，如图所示（和上图没有关系）。

![求出有多少碳](https://cdn.luogu.com.cn/upload/pic/2759.png)

但是因为在考试，所以你只能把这个答案用手语告诉你的基友。你决定用二进制来表示最后的答案，如图所示（不要在意，和题目没有什么没关系）。

![二进制手语](https://cdn.luogu.com.cn/upload/pic/2760.png)

### 题意简述

给你一个 $n$ 个点，$m$ 条边的无向图。把图中所有的环变为一个点，求变化后某两个点之间有多少个点。
## 输入格式

第一行两个整数 $n$，$m$。表示有 $n$ 个点，$m$ 根键。

接下来 $m$ 行每行两个整数 $u$，$v$ 表示 $u$ 号碳和 $v$ 号碳有一根键。

接下来一个整数 $tot$ 表示询问次数。

接下来 $tot$ 行每行两个整数，$a$，$b$ 表示询问的两个碳的编号。
## 输出格式

共 $tot$ 行，每行一个二进制数，表示答案。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
2
1 2
2 3

```
### 样例输出 #1
```
10
10
```
## 提示

两个碳不成环。

## 数据范围及约定

对于 $100\%$ 的数据，$1<n\le10 ^ 4$，$1<m\le5\times 10 ^ 4$。


---

---
title: "校园网络【[USACO]Network of Schools加强版】"
layout: "post"
diff: 提高+/省选-
pid: P2812
tag: ['图论', '强连通分量']
---
# 校园网络【[USACO]Network of Schools加强版】
## 题目背景

浙江省的几所 OI 强校的神犇发明了一种人工智能，可以 AC 任何题目，所以他们决定建立一个网络来共享这个软件。但是由于他们脑力劳动过多导致全身无力身体被♂掏♂空，他们来找你帮助他们。

## 题目描述

共有 $n$ 所学校 $(1 \leq n \leq 10000)$ 已知他们实现设计好的网络共 $m$ 条线路，为了保证高速，网络是单向的。现在请你告诉他们至少选几所学校作为共享软件的母机，能使每所学校都可以用上。再告诉他们至少要添加几条线路能使任意一所学校作为母机都可以使别的学校使用上软件。

## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行每行有若干个整数，用空格隔开。

第 $i+1$ 行，每行输入若干个非零整数 $x$，表示从 $i$ 到 $x$ 有一条线路。以 $0$ 作为结束标志。

## 输出格式

第一行一个整数，表示至少选几所学校作为共享软件的母机，能使每所学校都可以用上。

第二行一个整数，表示至少要添加几条线路能使任意一所学校作为母机都可以使别的学校使用上软件。
## 样例

### 样例输入 #1
```
5
2 0
4 0
5 0
1 0
0

```
### 样例输出 #1
```
2
2
```
## 提示

~~POJ 原题。数据扩大了 $100$ 倍。~~

~~$1 \leq $ 边数 $\leq 5000000$，$1 \leq n \leq 10000$ 。~~

实际上，$1 \leq n \leq 10000$，$1\le $ 边数 $\le 50000$。


---

---
title: "[USACO06JAN] Redundant Paths G"
layout: "post"
diff: 提高+/省选-
pid: P2860
tag: ['图论', '2006', 'USACO', '强连通分量', '位运算']
---
# [USACO06JAN] Redundant Paths G
## 题目描述

In order to get from one of the F (1 <= F <= 5,000) grazing fields (which are numbered 1..F) to another field, Bessie and the rest of the herd are forced to cross near the Tree of Rotten Apples.  The cows are now tired of often being forced to take a particular path and want to build some new paths so that they will always have a choice of at least two separate routes between any pair of fields. They currently have at least one route between each pair of fields and want to have at least two. Of course, they can only travel on Official Paths when they move from one field to another.


Given a description of the current set of R (F-1 <= R <= 10,000) paths that each connect exactly two different fields, determine the minimum number of new paths (each of which connects exactly two fields) that must be built so that there are at least two separate routes between any pair of fields. Routes are considered separate if they use none of the same paths, even if they visit the same intermediate field along the way.


There might already be more than one paths between the same pair of fields, and you may also build a new path that connects the same fields as some other path.

## 输入格式

Line 1: Two space-separated integers: F and R




Lines 2..R+1: Each line contains two space-separated integers which are the fields at the endpoints of some path.

## 输出格式

Line 1: A single integer that is the number of new paths that must be built.

## 样例

### 样例输入 #1
```
7 7
1 2
2 3
3 4
2 5
4 5
5 6
5 7
```
### 样例输出 #1
```
2
```
## 提示

Explanation of the sample:




One visualization of the paths is:

![](https://cdn.luogu.com.cn/upload/image_hosting/cubnel5k.png)

Building new paths from 1 to 6 and from 4 to 7 satisfies the conditions.

![](https://cdn.luogu.com.cn/upload/image_hosting/rgguiytp.png)

Check some of the routes:

- 1 – 2:  1 –> 2 and 1 –> 6 –> 5 –> 2
- 1 – 4:  1 –> 2 –> 3 –> 4 and 1 –> 6 –> 5 –> 4
- 3 – 7:  3 –> 4 –> 7 and 3 –> 2 –> 5 –> 7

Every pair of fields is, in fact, connected by two routes.

It's possible that adding some other path will also solve the problem (like one from 6 to 7). Adding two paths, however, is the minimum.

## 题目翻译

为了从 $F(1 \le F \le 5000)$ 个草场中的一个走到另一个，贝茜和她的同伴们有时不得不路过一些她们讨厌的可怕的树．奶牛们已经厌倦了被迫走某一条路，所以她们想建一些新路，使每一对草场之间都会至少有两条相互分离的路径，这样她们就有多一些选择。

每对草场之间已经有至少一条路径．给出所有 $R\ (F-1 \le R \le 10000)$ 条双向路的描述，每条路连接了两个不同的草场，请计算最少的新建道路的数量，路径由若干道路首尾相连而成．两条路径相互分离，是指两条路径没有一条重合的道路．但是，两条分离的路径上可以有一些相同的草场．对于同一对草场之间，可能已经有两条不同的道路，你也可以在它们之间再建一条道路，作为另一条不同的道路。


---

---
title: "[USACO15JAN] Grass Cownoisseur G"
layout: "post"
diff: 提高+/省选-
pid: P3119
tag: ['2015', 'USACO', '拓扑排序', '强连通分量', 'Tarjan']
---
# [USACO15JAN] Grass Cownoisseur G
## 题目描述

In an effort to better manage the grazing patterns of his cows, Farmer John has installed one-way cow paths all over his farm. The farm consists of N fields, conveniently numbered 1..N, with each one-way cow path connecting a pair of fields. For example, if a path connects from field X to field Y, then cows are allowed to travel from X to Y but not from Y to X.

Bessie the cow, as we all know, enjoys eating grass from as many fields as possible. She always starts in field 1 at the beginning of the day and visits a sequence of fields, returning to field 1 at the end of the day. She tries to maximize the number of distinct fields along her route, since she gets to eat the grass in each one (if she visits a field multiple times, she only eats the grass there once).

As one might imagine, Bessie is not particularly happy about the one-way restriction on FJ's paths, since this will likely reduce the number of distinct fields she can possibly visit along her daily route.  She wonders how much grass she will be able to eat if she breaks the rules and follows up to one path in the wrong direction. Please compute the maximum number of distinct fields she can visit along a route starting and ending at field 1, where she can follow up to one path along the route in the wrong direction.  Bessie can only travel backwards at most once in her journey.  In particular, she cannot even take the same path backwards twice.
## 输入格式

The first line of input contains N and M, giving the number of fields and the number of one-way paths (1 <= N, M <= 100,000). 

The following M lines each describe a one-way cow path.  Each line contains two distinct field numbers X and Y, corresponding to a cow path from X to Y.  The same cow path will never appear more than once.
## 输出格式

A single line indicating the maximum number of distinct fields Bessie can visit along a route starting and ending at field 1, given that she can follow at most one path along this route in the wrong direction.
## 样例

### 样例输入 #1
```
7 10 
1 2 
3 1 
2 5 
2 4 
3 7 
3 5 
3 6 
6 5 
7 2 
4 7 


```
### 样例输出 #1
```
6 

```
## 提示

SOLUTION NOTES:

Here is an ASCII drawing of the sample input:

```cpp
v---3-->6
7   | \ |
^\  v  \|
| \ 1   |
|   |   v
|   v   5
4<--2---^
```

Bessie can visit pastures 1, 2, 4, 7, 2, 5, 3, 1 by traveling backwards on the path between 5 and 3.  When she arrives at 3 she cannot reach 6 without following another backwards path.
## 题目翻译

### 题目描述

为了更好地管理牛群的放牧路线，Farmer John 在他的农场中安装了若干单向牛道。农场由 $N$ 块草场组成，编号为 $1$ 到 $N$，每条单向牛道连接一对草场。例如，若存在一条从草场 $X$ 到 $Y$ 的路径，则牛可以从 $X$ 前往 $Y$，但不能从 $Y$ 返回 $X$。

众所周知，Bessie 喜欢尽可能多地品尝不同草场的牧草。她每天从草场 $1$ 出发，访问一系列草场后返回草场 $1$。她试图最大化沿途经过的不同草场数量（重复访问的草场只算一次）。

由于单向路径的限制，Bessie 担心这会减少她每日路线中可以访问的草场数量。她想知道如果她违反规则，在路线中最多逆向通过某条道路一次，最多能品尝多少草场的牧草。请计算她从草场 $1$ 出发并返回的情况下，最多能访问的不同草场数量。注意 Bessie 在整个旅程中最多只能逆向通过一条道路，且同一条路径不能逆向两次。

### 输入格式

第一行包含两个整数 $N$ 和 $M$，表示草场数量和单向牛道数量（$1 \leq N, M \leq 100,000$）。

接下来 $M$ 行每行描述一条单向牛道，包含两个不同的整数 $X$ 和 $Y$，表示从 $X$ 到 $Y$ 的单向路径。保证每条路径不会重复出现。

### 输出格式

输出一行，表示 Bessie 在最多逆向通过一条道路的情况下，从草场 $1$ 出发并返回时能访问的最大不同草场数量。

### 说明/提示

**样例解析：**

以下是样例输入的 ASCII 图示：

```
v---3-->6
7   | \ |
^\  v  \|
| \ 1   |
|   |   v
|   v   5
4<--2---^
```

Bessie 可以通过逆向路径 $5\to 3$ 访问草场 $1, 2, 4, 7, 2, 5, 3, 1$。到达草场 $3$ 后，若不再次逆向其他路径则无法前往 $6$。


---

---
title: "[APIO2009] 抢掠计划"
layout: "post"
diff: 提高+/省选-
pid: P3627
tag: ['2009', 'APIO', '强连通分量', '栈']
---
# [APIO2009] 抢掠计划
## 题目描述

Siruseri 城中的道路都是单向的。不同的道路由路口连接。按照法律的规定，在每个路口都设立了一个 Siruseri 银行的 ATM 取款机。令人奇怪的是，Siruseri 的酒吧也都设在路口，虽然并不是每个路口都设有酒吧。  

Banditji 计划实施 Siruseri 有史以来最惊天动地的 ATM 抢劫。他将从市中心出发，沿着单向道路行驶，抢劫所有他途径的 ATM 机，最终他将在一个酒吧庆祝他的胜利。  

使用高超的黑客技术，他获知了每个 ATM 机中可以掠取的现金数额。他希望你帮助他计算从市中心出发最后到达某个酒吧时最多能抢劫的现金总数。他可以经过同一路口或道路任意多次。但只要他抢劫过某个 ATM 机后，该 ATM 机里面就不会再有钱了。 例如，假设该城中有 $6$ 个路口，道路的连接情况如下图所示：  

![](https://cdn.luogu.com.cn/upload/pic/4396.png)  

市中心在路口 $1$，由一个入口符号 → 来标识，那些有酒吧的路口用双圈来表示。每个 ATM 机中可取的钱数标在了路口的上方。在这个例子中，Banditji 能抢劫的现金总数为 $47$，实施的抢劫路线是：$1-2-4-1-2-3-5$。
## 输入格式

第一行包含两个整数 $N,M$。$N$ 表示路口的个数，$M$ 表示道路条数。  

接下来 $M$ 行，每行两个整数，这两个整数都在 $1$ 到 $N$ 之间，第 $i+1$ 行的两个整数表示第 $i$ 条道路的起点和终点的路口编号。  

接下来 $N$ 行，每行一个整数，按顺序表示每个路口处的 ATM 机中的钱数 $a_i$。  

接下来一行包含两个整数 $S,P$，$S$ 表示市中心的编号，也就是出发的路口。$P$ 表示酒吧数目。  

接下来的一行中有 $P$ 个整数，表示 $P$ 个有酒吧的路口的编号。
## 输出格式

输出一个整数，表示 Banditji 从市中心开始到某个酒吧结束所能抢劫的最多的现金总数。
## 样例

### 样例输入 #1
```
6 7 
1 2 
2 3 
3 5 
2 4 
4 1 
2 6 
6 5 
10 
12 
8 
16 
1 
5 
1 4 
4 3 5 6
```
### 样例输出 #1
```
47
```
## 提示

对于 $50\%$ 的数据，保证 $N, M \le 3000$。  

对于 $100\%$ 的数据，保证 $N, M \le 5\times 10^5$，$0 \le a_i \le 4000$。保证可以从市中心沿着 Siruseri 的单向的道路到达其中的至少一个酒吧。


---

---
title: "[JSOI2010] 连通数"
layout: "post"
diff: 提高+/省选-
pid: P4306
tag: ['2010', '各省省选', '江苏', '枚举', '图论建模', '连通块', '强连通分量']
---
# [JSOI2010] 连通数
## 题目背景

本题数据过水，可前往 https://www.luogu.com.cn/problem/U143178 提交

$\text{upd 2022.8.4}$：已作为 Hack 数据合并进来。
## 题目描述

度量一个有向图连通情况的一个指标是连通数，指图中可达顶点对个的个数。

如图

![](https://cdn.luogu.com.cn/upload/image_hosting/8jviim6w.png)

顶点 $1$ 可达 $1, 2, 3, 4, 5$

顶点 $2$ 可达 $2, 3, 4, 5$

顶点 $3$ 可达 $3, 4, 5$

顶点 $4, 5$ 都只能到达自身。

所以这张图的连通数为 $14$。

给定一张图，请你求出它的连通数
## 输入格式

输入数据第一行是图顶点的数量，一个正整数 $N$。  
接下来 $N$ 行，每行 $N$ 个字符。第 $i$ 行第 $j$ 列的 `1` 表示顶点 $i$ 到 $j$ 有边，`0` 则表示无边。
## 输出格式

输出一行一个整数，表示该图的连通数。
## 样例

### 样例输入 #1
```
3
010
001
100
```
### 样例输出 #1
```
9
```
## 提示

对于 $100 \%$ 的数据，$1 \le N \le 2000$。


---

---
title: "[Wind Festival] Running In The Sky"
layout: "post"
diff: 提高+/省选-
pid: P4742
tag: ['图论建模', '拓扑排序', '强连通分量']
---
# [Wind Festival] Running In The Sky
## 题目背景

$[Night - 20:02$ $P.M.]$

夜空真美啊……但是……快要结束了呢……
## 题目描述

一天的活动过后，所有学生都停下来欣赏夜空下点亮的风筝。$Curtis$ $Nishikino$想要以更近的视角感受一下，所以她跑到空中的风筝上去了(这对于一个妹子来说有点匪夷所思)! 每只风筝上的灯光都有一个亮度 $k_i$. 由于风的作用，一些风筝缠在了一起。但是这并不会破坏美妙的气氛，缠在一起的风筝会将灯光汇聚起来，形成更亮的光源！

$Curtis$ $Nishikino$已经知道了一些风筝间的关系，比如给出一对风筝$(a,b)$, 这意味着她可以从 $a$ 跑到 $b$ 上去，但是不能返回。

现在，请帮她找到一条路径(她可以到达一只风筝多次，但只在第一次到达时她会去感受上面的灯光), 使得她可以感受到最多的光亮。同时请告诉她这条路径上单只风筝的最大亮度，如果有多条符合条件的路径，输出能产生最大单只风筝亮度的答案。
## 输入格式

第一行两个整数 $n$ 和 $m$. $n$ 是风筝的数量, $m$ 是风筝间关系对的数量. 

接下来一行 $n$ 个整数 $k_i$.

接下来 $m$ 行, 每行两个整数 $a$ 和 $b$, 即$Curtis$可以从 $a$ 跑到 $b$.
## 输出格式

一行两个整数。$Curtis$在计算出的路径上感受到的亮度和，这条路径上的单只风筝最大亮度.
## 样例

### 样例输入 #1
```
5 5
8 9 11 6 7
1 2
2 3
2 4
4 5
5 2
```
### 样例输出 #1
```
41 11
```
## 提示

对于 $20\%$ 的数据, $0<n \le 5\times10^3, \ 0 < m \le 10^4$.

对于 $80\%$ 的数据, $0 < n \le 10^5, \ 0 < m \le 3\times10^5$.

对于 $100\%$ 的数据, $0<n\le2\times10^5,\ 0<m\le5\times10^5,\ 0<k\le200$.



---

---
title: "【模板】2-SAT"
layout: "post"
diff: 提高+/省选-
pid: P4782
tag: ['图论', 'Special Judge', 'O2优化', '2-SAT', '强连通分量']
---
# 【模板】2-SAT
## 题目描述

有 $n$ 个布尔变量 $x_1\sim x_n$，另有 $m$ 个需要满足的条件，每个条件的形式都是 「$x_i$ 为 `true` / `false` 或 $x_j$ 为 `true` / `false`」。比如 「$x_1$ 为真或 $x_3$ 为假」、「$x_7$ 为假或 $x_2$ 为假」。

2-SAT 问题的目标是给每个变量赋值使得所有条件得到满足。
## 输入格式

第一行两个整数 $n$ 和 $m$，意义如题面所述。

接下来 $m$ 行每行 $4$ 个整数 $i$, $a$, $j$, $b$，表示 「$x_i$ 为 $a$ 或 $x_j$ 为 $b$」($a, b\in \{0,1\}$)
## 输出格式

如无解，输出 `IMPOSSIBLE`；否则输出 `POSSIBLE`。

下一行 $n$ 个整数 $x_1\sim x_n$（$x_i\in\{0,1\}$），表示构造出的解。
## 样例

### 样例输入 #1
```
3 1
1 1 3 0
```
### 样例输出 #1
```
POSSIBLE
0 0 0
```
## 提示

$1\leq n, m\leq 10^6$ , 前 $3$ 个点卡小错误，后面 $5$ 个点卡效率。

由于数据随机生成，可能会含有（ 10 0 10 0）之类的坑，但按照最常规写法的写的标程没有出错，各个数据点卡什么的提示在标程里。


---

---
title: "「TAOI-1」椎名真昼"
layout: "post"
diff: 提高+/省选-
pid: P9220
tag: ['博弈论', 'O2优化', '拓扑排序', '强连通分量', 'Tarjan']
---
# 「TAOI-1」椎名真昼
## 题目背景

**请注意赛后题目添加了多测。因此请将您的赛时代码进行修改后再提交。**
## 题目描述

你正在看轻小说，突然你的家长走了进来，于是你假装在写 OI 题目。

Alice 和 Bob 正在玩一款游戏，给定一个有向图，每个点初始有一个颜色（黑或白）。

双方轮流进行操作，Alice 先手，每次操作选定一个节点，将所有从该点开始，能到达的点（包括自身）颜色翻转。如果某次操作后所有节点都变为白色，则进行该次操作的人胜利。

假如双方都采用最优策略使得自己胜利，或者如果自己无法胜利，使得对方无法胜利。

给你节点的初始状态，请你求出最终的胜者，亦或者，没有胜者。

---

定义点 $u$ 能到达点 $v$，当且仅当存在数列 $(a_1,a_2,a_3,\cdots,a_k)$，其中 $k \ge 1$，使得 $\forall i \in [1,k)$，存在有向边 $a_i \to a_{i+1}$，且 $a_1=u$，$a_k=v$。
## 输入格式

**本题有多组测试数据。**

第一行一个正整数 $T$，代表数据组数。

对于每组测试数据：

第一行两个整数 $n, m$，代表图的点数，边数。

第二行 $n$ 个整数，代表每个点开始时的颜色。$1$ 代表黑色，$0$ 代表白色。

接下来 $m$ 行，每行两个整数 $u, v$ 代表一条从 $u \to v$ 的边。
## 输出格式

对于每组测试数据：

如果最后 Alice 胜利，输出 `A`。

如果最后 Bob 胜利，输出 `B`。

如果双方（在对方的阻止下）都无法胜利，输出 `N`。

您无需输出空格或换行符。
## 样例

### 样例输入 #1
```
2
2 1
1 0
2 1
3 2
1 0 1
1 2
2 3
```
### 样例输出 #1
```
AN
```
## 提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 1（5 points）：$n \leq 2$，$m \leq 1$，$T=1$。
- Subtask 2（15 points）：$n \leq 5$，$m \leq 8$，$T=1$。
- Subtask 3（25 points）：保证所有点的初始颜色相同。
- Subtask 4（55 points）：无特殊限制。

对于所有测试数据，$1 \leq n \leq 10^5$，$1 \leq m \leq 2 \times 10^5$，$1 \le T \le 15$。

### 样例解释

在第一组数据中，Alice 可以先手对节点 $1$ 进行操作。操作后所有节点变为白色。

在第二组数据中，双方都没有必胜的方法，因此双方会互相拖延对方阻止对方获胜。

---

「据说如果无论如何都输出 `N` 的话，有 $45\%$ 的几率能够得到正确答案？」

「怎么可能，不会真的有人造出这么蠢的数据吧……」


---

