---
title: "[JRKSJ R8] C0mp0nents"
layout: "post"
diff: 省选/NOI-
pid: P10573
tag: ['图论', '2024', '洛谷原创', 'O2优化', '连通块', '洛谷月赛']
---
# [JRKSJ R8] C0mp0nents
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/m71eooc6.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/b626ra6r.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/it3ulcpz.png)
## 题目描述

小 I 有一张 $n$ 个点、$m$ 条边的无向图，保证图无重边、无自环。初始时第 $i$ 个点的点权 $a_i = i$。小 I 有一个额外的常量 $k$。

小 R 可以进行很多很多次操作。每次操作，她选择图上两个相邻的节点 $x, y$ 满足 $\lvert a_x - a_y \rvert = k$，随后小 I 会将 $a_x$ 设为 $a_y$。

对每个 $1 \leq s \leq n$，**如果在过程中不修改 $\bm{a_x = s}$ 的节点 $\bm x$ 的权值**，小 I 想知道：若干次操作后，图上最多有多少个点满足 $a_i = s$。
## 输入格式

第一行三个整数 $n, m, k$。

接下来 $m$ 行，每行两个整数 $u, v$，依次表示一条连接 $u, v$ 的边。
## 输出格式

一行 $n$ 个整数，第 $i$ 个整数表示 $s = i$ 时的答案。
## 样例

### 样例输入 #1
```
5 6 1
1 2
1 3
1 5
2 3
2 4
4 5
```
### 样例输出 #1
```
3 3 5 5 5

```
### 样例输入 #2
```
8 10 1
1 3
1 4
1 5
2 3
2 7
3 6
4 6
5 8
6 7
7 8

```
### 样例输出 #2
```
8 8 7 7 5 4 3 3

```
### 样例输入 #3
```
14 19 2
1 3
1 4
1 9
2 5
2 14
3 7
4 5
4 6
4 7
4 8
5 6
5 11
6 8
7 9
8 10
8 12
9 10
10 11
11 12

```
### 样例输出 #3
```
2 1 2 4 1 4 2 4 2 5 1 5 1 1

```
## 提示

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 0（0 pts）：样例；
- Subtask 1（5 pts）：$n \leq 200$，$m \leq 400$；
- Subtask 2（20 pts）：$n \leq 5000$，$m \leq 10^4$；
- Subtask 3（25 pts）：$n \leq 10^5$，$m \leq 3\times 10^5$；
- Subtask 4（50 pts）：无特殊限制。

对于所有数据，满足 $1 \leq k \leq n \leq 4\times 10^5$，$1 \leq u, v \leq n$，$0 \leq m \leq 10^6$，保证图无重边、无自环。


---

---
title: "[HEOI2016/TJOI2016] 游戏"
layout: "post"
diff: 省选/NOI-
pid: P2825
tag: ['2016', '各省省选', '网络流', '河北', '连通块', '二分图', '天津']
---
# [HEOI2016/TJOI2016] 游戏
## 题目描述

在 2016 年，佳媛姐姐喜欢上了一款游戏，叫做泡泡堂。

简单的说，这个游戏就是在一张地图上放上若干个炸弹，看是否能炸到对手，或者躲开对手的炸弹。在玩游戏的过程中，小 H 想到了这样一个问题：当给定一张地图，在这张地图上最多能放上多少个炸弹能使得任意两个炸弹之间不会互相炸到。炸弹能炸到的范围是该炸弹所在的一行和一列，炸弹的威力可以穿透软石头，但是不能穿透硬石头。

给定一张 $ n \times m $ 的网格地图:其中 ``*`` 代表空地，炸弹的威力可以穿透，可以在空地上放置一枚炸弹。 ``x`` 代表软石头，炸弹的威力可以穿透，不能在此放置炸弹。``#`` 代表硬石头，炸弹的威力是不能穿透的，不能在此放置炸弹。例如：给出 $ 1 \times 4 $ 的网格地图 `` *xx*``，这个地图上最多只能放置一个炸弹。给出另一个$ 1 \times 4 $ 的网格地图 ``*x#*``，这个地图最多能放置两个炸弹。

现在小 H 任意给出一张 $ n \times m $ 的网格地图，问你最多能放置多少炸弹。
## 输入格式

第一行输入两个正整数 $ n, m $，$ n $ 表示地图的行数，$ m $ 表示地图的列数。

接下来输入 $ n $ 行 $ m $ 列个字符，代表网格地图。``*``的个数不超过 $ n \times m $ 个。
## 输出格式

输出一个整数 $ a $，表示最多能放置炸弹的个数。
## 样例

### 样例输入 #1
```
4 4
#***
*#**
**#*
xxx#
```
### 样例输出 #1
```
5
```
## 提示

$1 \leq n,m \leq 50$


---

---
title: "[USACO12JAN] Cow Run G"
layout: "post"
diff: 省选/NOI-
pid: P3042
tag: ['贪心', '2012', 'USACO', '连通块', '队列']
---
# [USACO12JAN] Cow Run G
## 题目描述

Farmer John and Bessie have devised a new exercise game for the cows.  The cows are running on a circular track of length M (2 <= M <= 1,000,000,000) starting from the same position.  The game proceeds in N (1 <= N <= 14) rounds using a deck of 8N cards each with a number X\_i (0 <= X\_i < M) written on it.

Each round FJ moves the top 8 cards into a separate pile and selects either the top 4 or bottom 4 cards for Bessie to play with.  Bessie then chooses either the top 2 cards or bottom 2 cards of the 4 cards FJ selected.  After this FJ calls out the number on the top card, X\_top, and the cows run a distance of R \* X\_top, where R is the total distance the cows have run so far.  Bessie then calls out the number on the bottom card, X\_bottom, and the cows run a distance of X\_bottom.

FJ is concerned that after the exercise the cows will be too tired to get back to the beginning of the track if they end up too far away.  He believes if the cows end up more than a distance of K (0 <= K <= floor(M/2)) from their starting position they won't be able to get back home.

It is guaranteed that if FJ plays correctly, he will always be able to ensure the cows can come home, irrespective of the moves made by Bessie! For each round, your task is to determine which half of the cards FJ should choose such that no matter what Bessie does from that point on, FJ can always get the cows home.  Bessie will then make the move provided in the input and you can then continue onto the next round.  Note that even though Bessie's moves are provided to you in the input, you are to specify moves for FJ that would have worked no matter what Bessie chooses (so it is effectively as if FJ does not really know what Bessie will do during her moves).

## 输入格式

\* Line 1: Three space-separated integers N, M, K

\* Line 2: A string N characters.  If the ith character is 'T' it means Bessie will select the top 2 cards in the ith round.  Otherwise the ith character will be 'B' to indicate Bessie will select the bottom 2 cards in the ith round.

\* Lines 3..2+N: Each line contains eight integers representing the 8 cards to be used that round from top to bottom.

## 输出格式

\* Line 1: A string of N characters where the ith character is 'T' if FJ should choose the top 4 cards or 'B' if FJ should choose the bottom 4 cards in the ith round.  If there are multiple ways to get the cows home, choose the lexicographically first (that is, the string that is alphabetically smallest).

## 样例

### 样例输入 #1
```
2 2 0 
TT 
1 0 0 0 0 0 0 1 
0 1 1 1 0 0 1 0 

```
### 样例输出 #1
```
TB 

```
## 提示

The cows must end up exactly where they started to be able to come home. Note that FJ is not aware of what choices Bessie is going to make beforehand.  If FJ did know, he could have chosen the bottom half each time.

## 题目翻译

FJ 和贝茜为奶牛们设计了一个新的跑步游戏。跑道是环行的，长度为 $(2 \le M \le 1,000,000,000)$ 的环行，奶牛们在相同的起跑位置。这个游戏一共要进行 $N\ (1 \le N \le 14)$ 轮，通过一副 $8N$ 张的纸牌来控制每一轮的跑步距离，每张纸牌都有一个数字 $X_i\ (0 \le X_i<M)$。

每一轮，FJ 取出最上面的 $8$ 张纸牌，然后再取出这 $8$ 张的上面或者底下的 $4$ 张。接着，贝茜从这 $4$ 张牌中取出上面或者底下的 $2$ 张，上面一张的数字为 $X_{\mathrm{top}}$，下面一张的数字是 $X_{\mathrm{bottom}}$，则牛先跑 $R\times X_{\mathrm{top}}$ 的距离（$R$ 表示奶牛们已经跑过的距离），再跑 $X_{\mathrm{bottom}}$ 的距离。

FJ 担心奶牛们太累而回不到起点，游戏结束时，若奶牛们离开起点距离超过 $K\ (0 \le K \le \lfloor M/2\rfloor)$，则他们就回不了起点了。

问题保证，当 FJ 选择正确的取牌策略，不论贝西如何取牌，奶牛们都能够回到起点。对于每一轮，你的任务是决定取哪 $4$ 张纸牌。在输入数据中，贝西的每次选择都是已知的，但 FJ 的每次取牌时，贝西接着的选择应该被假定为是未知的，即不论贝西怎么选，FJ 的选择都是能保证奶牛们能够回到起点。


---

---
title: "[HNOI2011] 勾股定理"
layout: "post"
diff: 省选/NOI-
pid: P3213
tag: ['2011', '湖南', '枚举', '连通块', '最大公约数 gcd']
---
# [HNOI2011] 勾股定理
## 题目描述

沫沫最近在研究勾股定理。对于两个正整数 A 与 B，若存在正整数 C 使得 A2+B2=C2，且 A 与 B 互质，则称(A,B)为一个互质勾股数对。


有一天，沫沫得到了 N 根木棍，其长度都是正整数，她准备从中挑选出若干根木棍来玩拼图游戏，为了使拼出的图案有凌乱美，她希望挑选出的木棍中任意两根的长度均不是互质勾股数对。现在，沫沫想知道有多少种满足要求的挑选木棍的方案。由于答案可能很大，你只要输出答案对 $10^9+7$ 取模的结果。

## 输入格式

从文件input.txt中读入数据，输入文件第一行是一个正整数N，表示共有多少根木棍。

输入文件第二行是用空格隔开的N个正整数h1, h2, …, hN，其中对1≤i≤N，hi表示第i根木棍的长度。

输入的数据保证30%的数据满足对$1≤i≤N$有$1≤h_i≤3000$，

另外30%的数据满足对$1≤i≤N$有$1≤hi≤200000$，

剩下的40%的数据满足对$1≤i≤N$有$20000≤h_i≤1000000$，

100%的数据满足$N≤1000000$。

## 输出格式

输出文件 output.txt 仅包含一个非负整数，表示满足要求的挑选木棍的方案数对 109+7 取模的结果。

## 样例

### 样例输入 #1
```
4				
5 12 35 5	

```
### 样例输出 #1
```
8
```
## 提示

样例解释：（5,12）与（12,35）是互质勾股数对，故满足要求的挑选木棍的方案有8种，即：


{5}，{12}，{35}，{5}，{5,35}，{35,5}，{5,5}，{5,35,5}。



---

---
title: "[SCOI2011] 棘手的操作"
layout: "post"
diff: 省选/NOI-
pid: P3273
tag: ['2011', '四川', '线段树', '深度优先搜索 DFS', '连通块']
---
# [SCOI2011] 棘手的操作
## 题目描述

有 $N$ 个节点，标号从 $1$ 到 $N$，这 $N$ 个节点一开始相互不连通。第i个节点的初始权值为 $a_i$，接下来有如下一些操作：
- `U x y`: 加一条边，连接第 $x$ 个节点和第 $y$ 个节点；
- `A1 x v`: 将第 $x$ 个节点的权值增加 $v$；
- `A2 x v`: 将第 $x$ 个节点所在的连通块的所有节点的权值都增加 $v$；
- `A3 v`: 将所有节点的权值都增加 $v$；
- `F1 x`: 输出第 $x$ 个节点当前的权值；
- `F2 x`: 输出第 $x$ 个节点所在的连通块中，权值最大的节点的权值；
- `F3`: 输出所有节点中，权值最大的节点的权值。
## 输入格式

输入的第一行是一个整数 $N$，代表节点个数。接下来一行输入 $N$ 个整数，$a_1,a_2,\dots,a_N$，代表 $N$ 个节点的初始权值。

再下一行输入一个整数 $Q$，代表接下来的操作数。

最后输入 $Q$ 行，每行的格式如题目描述所示。
## 输出格式

对于操作 `F1 x`,`F2 x`,`F3`，输出对应的结果，每个结果占一行。
## 样例

### 样例输入 #1
```
3
0 0 0
8
A1 3 -20
A1 2 20
U 1 3
A2 1 10
F1 3
F2 3
A3 -10
F3
```
### 样例输出 #1
```
-10
10
10
```
## 提示

对于 $30\%$ 的数据，保证 $N\le 100，Q\le 10000$；

对于 $80\%$ 的数据，保证 $N\le 100000$，$Q\le 100000$；

对于 $100\%$ 的数据，保证 $N\le 300000$，$Q\le 300000$；

对于所有的数据，保证输入合法，并且 $-1000\le v,a_1,a_2,\dots,a_N \le 1000$。


---

---
title: "[SCOI2011] 飞镖"
layout: "post"
diff: 省选/NOI-
pid: P3277
tag: ['2011', '四川', '线段树', '并查集', '连通块']
---
# [SCOI2011] 飞镖
## 题目描述

飞镖是在欧洲颇为流行的一项运动。它的镖盘上分为20个扇形区域，分别标有1到20的分值，每个区域中有单倍、双倍和三倍的区域，打中对应的区域会得到分值乘以倍数所对应的分数。

例如打中18分里面的三倍区域，就会得到54分。

另外，在镖盘的中央，还有”小红心“和”大红心“，分别是25分和50分。

通常的飞镖规则还有一条，那就是在最后一镖的时候，必须以双倍结束战斗，才算获胜。也就是说，当还剩12分的时候，必须打中双倍的6才算赢，而打中单倍的12或者三倍的4则不算。

特别的，”大红心“也算双倍(双倍的25)。在这样的规则下，3镖能解决的最多分数是170分(两个三倍的20，最后用大红心结束)。

现在，lxhgww把原来的1到20分的分值变为了1到K分，同时把小红心的分数变为了M分(大红心是其双倍)，现在lxhgww想知道能否在3镖内（可以不一定用满3镖）解决X分。同样的，最后一镖必须是双倍（包括大红心）。

## 输入格式

输入的第一行是一个整数T，包括了T组数据。

第二行是5个整数，$A_1,B_1,C_1,D_1,K_1$，表示第一组数据的镖盘是从1到$K_1$分的，随后数据的镖盘由公式$K_i=(A_1K^2_{i-1}+B_1K_{i-1}+C_1)mod D_1 + 20$决定，其中第$i(1<i\le T)$组数据的镖盘是从1到$K_i$分的。

第三行是5个整数，$A_2,B_2,C_2,D_2,M_1$，表示第一组数据的小红心$M_1$分的，随后数据的镖盘由公式$M_i=(A_2M^2_{i-1}+B_2M_{i-1}+C_2)mod D_2 + 20$决定，其中第$i(1<i\le T)$组数据的小红心是$M_i$分。


第四行是5个整数，$A_3,B_3,C_3,D_3,X_1$，表示第一组数据需要解决的分数是$X_1$分的，随后数据的镖盘由公式$X_i=(A_3X^2_{i-1}+B_3X_{i-1}+C_3)mod D_3 + 20$决定，其中第$i(1<i\le T)$组数据需要解决的分数是$X_i$分。

## 输出格式

一行，包括一个数字，表示这T组数据中，能够被解决的数据数目。

## 样例

### 样例输入 #1
```
5
1 2 2 10 20
1 3 2 15 25
2 2 5 200 170
```
### 样例输出 #1
```
4
```
## 提示

对于30%的数据，保证$1\le T\le 20$,$20\le K1,M1,X1,D1,D2,D3\le 1000$

对于100%的数据，保证$1\le T\le 10^6$,$20\le K1,M1,X1,D1,D2,D3\le 10^9$

对于所有的数据，保证$0\le A1,B1,A2,B2,C2,A3,B3,C3 \le 10^9$



---

---
title: "[APIO2013] 道路费用"
layout: "post"
diff: 省选/NOI-
pid: P3639
tag: ['2013', 'APIO', '生成树', '连通块', '强连通分量']
---
# [APIO2013] 道路费用
## 题目描述

幸福国度可以用 N 个城镇（用 1 到 N 编号）构成的集合来描述，这些城镇 最开始由 M 条双向道路（用 1 到 M 编号）连接。城镇 1 是中央城镇。保证一个 人从城镇 1 出发，经过这些道路，可以到达其他的任何一个城市。这些道路都是 收费道路，道路 i 的使用者必须向道路的主人支付 ci分钱的费用。已知所有的这 些ci是互不相等的。最近有K条新道路建成，这些道路都属于亿万富豪Mr. Greedy。 Mr. Greedy 可以决定每条新道路的费用（费用可以相同），并且他必须在明天宣 布这些费用。

两周以后，幸福国度将举办一个盛况空前的嘉年华！大量的参与者将沿着这 些道路游行并前往中央城镇。共计 pj个参与者将从城镇 j 出发前往中央城镇。这 些人只会沿着一个选出的道路集合前行，并且这些选出的道路将在这件事的前一 天公布。根据一个古老的习俗，这些道路将由幸福国度中最有钱的人选出，也就 是 Mr. Greedy。同样根据这个习俗，Mr. Greedy 选出的这个道路集合必须使所有 选出道路的费用之和最小，并且仍要保证任何人可以从城镇 j 前往城镇 1（因此， 这些选出的道路来自将费用作为相应边边权的“最小生成树”）。如果有多个这样 的道路集合，Mr. Greedy 可以选其中的任何一个，只要满足费用和是最小的。

Mr. Greedy 很明确地知道，他从 K 条新道路中获得的收入不只是与费用有 关。一条道路的收入等于所有经过这条路的人的花费之和。更准确地讲，如果 p 个人经过道路 i，道路 i 产生的收入为 ci p 的积。注意 Mr. Greedy 只能从新道路 收取费用，因为原来的道路都不属于他。

Mr. Greedy 有一个阴谋。他计划通过操纵费用和道路的选择来最大化他的收 入。他希望指定每条新道路的费用（将在明天公布），并且选择嘉年华用的道路 （将在嘉年华的前一天公布），使得他在 K 条新道路的收入最大。注意 Mr. Greedy 仍然需要遵循选出花费之和最小的道路集合的习俗。

你是一个记者，你想揭露他的计划。为了做成这件事，你必须先写一个程序 来确定 Mr. Greedy 可以通过他的阴谋获取多少收入。

## 输入格式

你的程序必须从标准输入读入。第一行包含三个由空格隔开的整数 N，M 和 K。接下来的 M 行描述最开始的 M 条道路。这 M 行中的第 i 行包含由空格隔开 的整数 ai，bi和 ci，表示有一条在 ai 和 bi之间，费用为 ci 的双向道路。接下来的 K 行描述新建的 K 条道路。这 K 行中的第 i 行包含由空格隔开的整数 xi和 yi，表 示有一条连接城镇 xi 和 yi 新道路。最后一行包含 N 个由空格隔开的整数，其中 的第 j 个为 pj，表示从城镇 j 前往城镇 1 的人数。

输入也满足以下约束条件。 

1 ≤ N ≤ 100000； 

1 ≤ K ≤ 20； 

1 ≤ M ≤ 300000； 

对每个 i 和 j，1 ≤ ci, pj ≤ 10^6；


如果 i ≠ i'，则 ci ≠ ci'； 

在任意两个城市之间，最多只有一条道路（包括新建的道路）。

## 输出格式

你的程序必须输出恰好一个整数到标准输出，表示能获得的最大的收入。

## 样例

### 样例输入 #1
```
5 5 1 
3 5 2 
1 2 3 
2 3 5 
2 4 4 
4 3 6 
1 3 
10 20 30 40 50
```
### 样例输出 #1
```
400
```
## 提示

在样例中，Mr. Greedy 应该将新道路(1,3)的费用设置为 5 分钱。在这个费用 下，他可以选择道路(3,5)，(1,2)，(2,4)和(1,3)来最小化总费用，这个费用为 14。 从城镇 3 出发的 30 个人和从城镇 5 出发的 50 个人将经过新道路前往城镇 1，因 此他可以获得为(30+50)×5=400 分钱的最好收入。

如果我们这样做，将新道路(1,3)的费用设置为 10 分钱。根据传统的限制， Mr. Greedy 必须选择(3,5)，(1,2)，(2,4)和(2,3)，因为这是唯一费用最小的集合。 因此，在嘉年华的过程中道路(1,3)将没有任何收入。


我们将使用以下 5 类测例测试你的程序。

1. （国际 16 分，国内 15 分）N ≤ 10，M ≤ 20 且 K = 1；

2. （国际 18 分，国内 20 分）N ≤ 30，M ≤ 50 且 K ≤ 10；

3. （国际 22 分，国内 20 分）N ≤ 1,000，M ≤ 5,000 且 K ≤ 10；

4. （国际 22 分，国内 20 分）N ≤ 100,000，M ≤ 300,000 且 K ≤ 15；

5. （国际 22 分，国内 25 分）N ≤ 100,000，M ≤ 300,000 且 K ≤ 20。

**update: 2024/07/04 删除了两个测试点，并且改为捆绑。**



---

---
title: "琪露诺的冰雪小屋"
layout: "post"
diff: 省选/NOI-
pid: P3693
tag: ['模拟', '洛谷原创', '枚举', '广度优先搜索 BFS', '连通块']
---
# 琪露诺的冰雪小屋
## 题目背景

琪露诺有一片正方形的雪地，她想在上面盖一栋小冰屋。

## 题目描述

琪露诺偶然间得到了一片 $N\times N$ 大小的正方形的雪地，她想在上面盖一栋冰雪小屋。

但调皮的⑨才不会认真地收集冰块呢，她要在这片土地上使用冰雪弹幕来制造冰砖，然后一块一块地搭起一个房子。

琪露诺制造冰砖的方式是这样的：她会站在某个方格上，然后向上，下，左，右，左上，左下，右上，右下这八个方向之一发射强力的冰雪弹幕，弹幕能影响到该方向一条直线上一定的距离以内的所有方格。

地面的每个方格都有一个冷冻度，初始为 $0$。被冰雪弹幕影响一次，冷冻度 $+1$，冷冻度的上限为 $4$。

在发射弹幕的间隙中，琪露诺会来到所有冷冻度为 $4$ 的格子，把那里的雪堆到一起，制作一个冰砖（大小为 $1\times1\times1$ 方格），并且将冷冻度重新归零。

琪露诺会拿着这些冰砖来盖房子。这个房子的长度、宽度和坐落位置她在一开始就已经规划好了，但她并不愿意提早确定房子的高度。

琪露诺是这样计划的：这个房子外观上看起来是一个长方体。

她会先盖起这个房子的四面墙（厚度为 $1$ 个方格），并在贴近地面的位置（废话）留一个宽度和高度分别为 $1$ 和 $2$ 的空位不放冰砖，作为房门。（显然，门无法开在墙的拐角处，但可以紧贴拐角）。

在她喜欢的时候，她会结束四面墙的建造，并一次性在墙顶部盖上一个厚度为 $1$ 方格的屋顶，使房子成为一个空心有顶的长方体。

计划已经非常充分了，但琪露诺还是不放心，所以她想请你帮她写一个程序，来随时提醒着她别出什么差错。这个程序需要具备的功能将在下文详细介绍。

----------------------
雪地由 $N$ 行 $N$ 列，$N\times N$ 个方格组成。（下标从 $0$ 开始，也就是说，存在第 $0$ 行第 $0$ 列，但不存在第 $N$ 行第 $N$ 列）每个方格都有一个冷冻度,范围 $[0,4]$，初始为 $0$。注意，空间是三维的，而冷冻度只是地面的属性。

琪露诺想将房子的左上角放在第 $H_R$行，$H_C$ 列（外墙也是房子的一部分，因此左上角位置不应该是房子的内部,而是外墙,并且是墙的拐角）。

这个房子的长度（平行于每列）是 $H_X$，宽度（平行于每行）是 $H_Y$，包含墙。保证房子所占空间不会超出雪地的范围。

除了最后搭建屋顶，琪露诺只会在高度 $[0,H_M-1]$ 放置冰砖。

一开始，琪露诺一个冰砖也没有。
在以下的介绍中，我们用俯视图来作示意：
```plain
0000
0000
4x90
0x01
```
数字代表当前该格子的冷冻度。如果位置紧贴地面（高度为 $0$）的地方放上了冰砖，那么用字母 $x$ 表示。

如果紧贴地面的位置没有冰砖，但是位置正上方的高空存在冰砖，那么仍然用数字表示地面的冷冻度，但这个数字会增加 $5$。即如果在示意图中看到了一个数字 $t\ge5$，表示该位置地面是空的，但高处有冰砖，且地面的冷冻度为 $t-5$。

第一个操作：`ICE_BARRAGE R C D S`  
---------------
表示琪露诺站在第 $R$ 行 $C$ 列的位置，朝着方向 $D$ 发射了一个强度为 $S$ 的弹幕。  
$R,C,D,S\in\mathbf{Z},0\le D\le7,0\le R,C,S<N$。  
方向编号 $0$ 表示上 $(R-1,C)$，$1$ 表示左上 $(R-1,C-1)$，   
$2$ 表示左 $(R,C-1)$，$3$ 表示左下 $(R+1,C-1)$，  
$4$ 表示下 $(R+1,C)$，$5$ 表示右下 $(R+1,C+1)$，  
$6$ 表示右 $(R,C+1)$，$7$ 表示右上 $(R-1,C+1)$。  
强度为 $S$ 的弹幕，可以使“处在发射方向直线上，距离琪露诺不超过 $S$ 格的所有格子（包括她站的格子）”的冷冻度都 $+1$。有以下几种特殊情况：

1. 如果某个格子冷冻度为 $4$，那么该格子冷冻度不变。
2. 如果弹幕所经路途上，有一个位置的地面上（高度为 $0$）已经放了冰砖（就是弹幕撞上了琪露诺已经盖了一半的房子），那么弹幕将被阻挡，无法影响到冰砖所在的格子以及冰砖后面被挡住的格子。
3. 弹幕超出雪地的部分忽略不计。

对于这个操作，需要如下输出一行：`CIRNO FREEZED k BLOCK(S)`  
如果这个弹幕将某个方格的冷冻度成功增加了 $1$，那么认为这个弹幕冻住了该方格。

`k` 表示这个弹幕总共冻住了多少方格。

如图：发射弹幕前地图如下：
```plain
00000
00000
00000
000x0
00000
```
执行操作 `ICE_BARRAGE 1 1 5 4`，地图变为：
```plain
00000
01000
00100
000x0
00000
```
输出：`CIRNO FREEZED 2 BLOCK(S)`  
解释：琪露诺站在第一行第一列，面对右下角发射了一个强度为 $4$ 的弹幕，但弹幕被 `x` 所阻挡，只能影响到 `x` 之前的格子。

第二个操作：`MAKE_ICE_BLOCK`  
-------------------------
琪露诺走遍地图上所有冷冻度为 $4$ 的方格，每个方格可以收集一个冰砖，然后将它们的冷冻度归零。 

对于这个操作，你需要给出如下输出一行：`CIRNO MADE x ICE BLOCK(S),NOW SHE HAS y ICE BLOCK(S)`  
表示琪露诺制造了 $x$ 个冰砖，目前她有 $y$ 个冰砖。  
比如琪露诺一开始有 $0$ 个冰砖，并且状态如下：
```plain
0xxx
0x4x
0x9x
0400
```
执行操作 `MAKE_ICE_BLOCK` 后变为
```plain
0xxx
0x0x
0x5x
0000
```
输出：`CIRNO MADE 3 ICE BLOCK(S),NOW SHE HAS 3 ICE BLOCK(S)`  
在这个示例中，房子已经完成了一部分，`x` 表示墙，`9` 这个位置地面没有冰砖，但高处有（可以猜出是门）。房间内唯一一块空地、门的位置，以及房间外的一个位置的冷冻度都达到了 $4$，因此可以收集到 $3$ 块冰砖，收集后将三个位置冷冻度都归零。

第三个操作：`PUT_ICE_BLOCK R C H` 
-----------------
表示在第 $R$ 行，第 $C$ 列，高度为 $H$ 的地方放一个冰砖。$0\le R,C<N,0\le H<H_M$。

贴近地面的位置高度为 $0$。如果冰砖放置成功，那么琪露诺库存的冰砖数量将减 $1$。

如果放置的位置贴近地面，该位置冷冻度立即归 $0$。

有以下几种情况，序号越小优先级越高，并且只能满足一种情况。

如果满足 $1$ 的话就忽视后面的，不满足 $1$ 的前提下才可能满足 $2\cdots\cdots$ 以此类推。

1. 琪露诺目前没有任何冰砖，无法放置。这种情况下你需要输出：`CIRNO HAS NO ICE_BLOCK`
2. 冰砖将放在半空中，无法依附其他任何冰砖，或者目标位置已有冰砖了。  
这种情况下你需要输出一行：`BAKA CIRNO,CAN'T PUT HERE`，并无视此次操作，不做任何工作。
3. 冰砖放在了规划建造房子的区域之外，即
$R<H_R$ 或 $R>H_R+H_x-1$  
或 $C<H_C$ 或 $C>H_C+H_Y-1$。请输出一行：`CIRNO MISSED THE PLACE`  
尽管琪露诺放错了地方，但你并不能阻止她放置这个冰砖。  
4. 冰砖留在了房子的内部，本应留空的地方被占用了，即  
$H_R+1\le R\le H_R+H_X-2$ 且 $H_C+1\le C\le H_C+H_Y-2$  
在屋顶的高度固定下来前，我们将所有满足上式的情况都认为是放在了房屋内部。  
请输出一行：`CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE`  
尽管琪露诺放错了地方，但你并不能阻止她放置这个冰砖。
5. 冰砖放在了正确的位置（不必考虑是否堵住了留给门的地方）  
请输出一行：`CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS x ICE_BLOCK(S)`  
`x` 表示放过这块冰砖后琪露诺剩余的冰砖。

第四个操作：`REMOVE_ICE_BLOCK R C H` 
---------
表示取走第 $R$ 行，第 $C$ 列，高度为 $H$ 处的冰砖。  
有以下几种情况，序号越小优先级越高，并且只能满足一种情况。

如果满足 $1$ 的话就忽视后面的，不满足 $1$ 的前提下才可能满足 $2\cdots\cdots$ 以此类推。

1. 目标位置没有冰砖，输出一行：`BAKA CIRNO,THERE IS NO ICE_BLOCK`
2. 目标位置有冰砖，并且在这个冰砖被移走后，至少有一个冰砖形成了一个悬空的块。  
如下面的“侧视图”，`x` 表示冰砖，`0` 表示空位。
```plain
xxxx
x000
x000
x000
```
$\ \ $在移走左上角的冰砖后，第一行右边三个冰砖没有了依靠，形成了一个悬空的连通块，就属于这种情况。  
$\ \ $这个冰砖将成功移走，琪露诺的冰砖库存将会 $+1$。并且所有的悬空连通块都会掉下来摔碎并消失  
$\ \ $（既不会进入冰砖库存，也不会在地面上留有任何痕迹）。  
$\ \ $输出一行：`CIRNO REMOVED AN ICE_BLOCK,AND k BLOCK(S) ARE BROKEN`，`k` 表示摔碎的冰砖数量。  
3. 琪露诺挪走了冰砖，并且其他冰砖不受任何影响。    
$\ \ \ $琪露诺的冰砖库存 $+1$，输出一行：`CIRNO REMOVED AN ICE_BLOCK`
    
第五个操作：`MAKE_ROOF` 
--------
这个操作只会出现一次，并且只会作为最后一个操作。  
这个操作表明琪露诺已经完成了冰雪小屋的四墙，只剩屋顶了！  

一般情况下，琪露诺将放置最后的 $H_X\times H_Y$ 个冰砖，把它们放置在墙壁最高的高度 $+1$ 的那一层，  
形成一个屋顶。然后她移除所有多余的冰砖，接下来补好所有残缺的墙壁。

你需要按顺序来执行整个过程，一旦遇到某种用 $\bullet$ 标识的特殊情况，则执行完该情况后退出流程。

在特殊情况之间所描述的均为一般情况，只要之前没有因为满足某种特殊情况而退出流程，均认为满足了一般情况。

首先，琪露诺将会一次性放置最多 $H_X\times H_Y$ 个冰砖来建造屋顶。

为什么是最多呢？请注意一点：如果之前错误放置在房子内部的冰砖恰好充当了屋顶的一部分，那么就不用在这个位置再放冰砖了。并且，所有比屋顶高的冰砖在之后将视为错误放置在了房子外部。

注意，放屋顶的时候可能会触及到高度为 $H_M$ 的那个平面。

建造屋顶前后将会碰到两种特殊情况：
- 琪露诺剩余的冰砖不足以建造屋顶。输出一行：`SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO MAKE ROOF`
- 墙壁的最高高度小于 $2$ 个方格，或者内部有效空间小于两个方格。  
墙壁所在的一圈不算内部空间。计算内部有效空间时请忽视错误放置的冰砖，因为它们将来要被移除。  
输出一行：`SORRY CIRNO,HOUSE IS TOO SMALL`

（特殊情况结束）

此后，我们认为琪露诺已经造好了屋顶，接下来该移除所有多余冰砖了。在移除过程中，琪露诺会尽可能让更少的冰砖摔碎。如果墙壁上某个冰砖因为移走了多余的冰砖而将要摔碎，那么她会先拆掉墙壁上的那个冰砖，然后在填补墙壁残缺时重新补回来（显然，这种行为不会影响到墙壁有无残缺的定性，但可以少损失一个冰砖）。她不会故意拆掉一个处在墙壁上且不会摔碎的冰砖。  
输出两行：  
`K1 ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED`  
`K2 ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED`  
`K1`表示房子内部错误放置的冰砖数量，`K2`表示房子外部错误放置的冰砖数量。

将有可能遭遇一种特殊情况：
- 琪露诺移除了所有多余的冰砖，但在移除过程中，屋顶塌陷了。  
输出一行：`SORRY CIRNO,HOUSE IS BROKEN WHEN REMOVING BLOCKS`

（特殊情况结束）

此后，我们认为琪露诺已经移除了所有多余的冰砖，接下来该填补墙壁的残缺了。

墙壁有残缺的定义是：除了宽为 $1$，高为 $2$ 的门以外，
在房子内部看外面还能看到其他缺口。

如果某个空位将来要作为门的一部分，则不属于残缺。并且房子只能有一个门。

如果墙壁没有残缺，则不要填补，否则需要填补。你需要记下墙壁是否有残缺，之后会用到。

填补的策略是：使用尽可能少的冰砖，在正确的位置填补墙壁，使房屋的状态不满足墙壁有残缺的定义（即不能放置多余的冰砖，通过遮挡视线来达到目的）。在此定义下，**大多数**情况我们无需考虑四角的柱子是否完整，因为在房间里看不到。

将有可能遭遇一种特殊情况：
- 琪露诺剩余的冰砖不足以填补墙壁的残缺。  
输出一行：`SORRY CIRNO,NOT ENOUGH ICE_BLOCKS TO FIX THE WALL`

（特殊情况结束）

此后，我们认为房子被成功建成了，这时你需要输出几行内容来对房子进行评价。

首先输出这么一行来庆祝房子的建成：`GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE`  
1. 在贴近地面的位置找不到一个宽度为 $1$，高度为 $2$ 的位置留给门。  
	输出一行：`HOUSE HAS NO DOOR`，然后琪露诺会尽可能利用墙壁上的残缺来开一个门。  
    否则，输出一行：`DOOR IS OK`
2. 接下来输出一行表示填补之前墙壁的完整程度  
	2.1. 在之前的记录中，墙壁不完整而需要修补。输出：`WALL NEED TO BE FIXED`  
    2.2. 在之前的记录中，墙壁完整而无需修补。输出：`WALL IS OK`  
3. 接下来一行表示四角的完整程度。  
	如果四个角的柱子有不完整的地方，就输出：`CORNER NEED TO BE FIXED`  
    在这种情况下，如果琪露诺剩余的冰砖足够修复拐角的空缺，那么她直接会修复这个空缺。  
    如果不够的话，她会再多收集几个冰砖，数量恰好修复这个空缺，然后修复这个空缺。  
    否则，输出：`CORNER IS OK`
    
接下来，输出一行：`CIRNO FINALLY HAS k ICE_BLOCK(S)`  
`k` 表示琪露诺最后剩余的冰砖的数量。

最后，如果在之前的记录中，墙壁完整无缺，没有一个位置需要填补。房子内外都无任何多余的方块，没有一个位置需要移除。没有出现房子没门的情况，房子四角的柱子也在造屋顶前完全造好，而不是通过修补完善的。并且门恰好开在了某面墙的正中央（如果长度为偶数，中间的两个都算），输出一行：   
`CIRNO IS PERFECT!`
## 输入格式

第一行一个正整数 $N$，表示雪地的大小。

第二行一个正整数$H_M$，表示琪露诺放置方块的最大高度。

第三行四个正整数 $H_R,H_C,H_X,H_Y$，表示房子左上角位置的行列坐标，房子的长度以及宽度。

第四行一个正整数 $M$，表示操作的数量。

接下来 $M$ 行，每行表示一个操作，输入格式见题目描述。
## 输出格式

在题目描述中已经介绍。

## 样例

### 样例输入 #1
```
8
10
4 0 4 4
63
ICE_BARRAGE 2 1 1 3
ICE_BARRAGE 0 1 3 1
MAKE_ICE_BLOCK
PUT_ICE_BLOCK 3 2 0
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 2 0 6 7
ICE_BARRAGE 3 0 6 7
ICE_BARRAGE 4 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
PUT_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 4 0 0
PUT_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 3 0 1
REMOVE_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 4 2 0
PUT_ICE_BLOCK 6 1 0
PUT_ICE_BLOCK 4 3 0
PUT_ICE_BLOCK 5 3 0
PUT_ICE_BLOCK 6 3 0
PUT_ICE_BLOCK 7 3 0
ICE_BARRAGE 0 1 4 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
REMOVE_ICE_BLOCK 6 1 0
PUT_ICE_BLOCK 5 0 0
PUT_ICE_BLOCK 6 0 0
PUT_ICE_BLOCK 7 0 0
PUT_ICE_BLOCK 7 1 0
PUT_ICE_BLOCK 7 2 0
PUT_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 5 0 1
PUT_ICE_BLOCK 6 0 1
PUT_ICE_BLOCK 7 0 1
PUT_ICE_BLOCK 7 1 1
PUT_ICE_BLOCK 7 2 1
PUT_ICE_BLOCK 7 3 1
PUT_ICE_BLOCK 6 3 1
PUT_ICE_BLOCK 5 3 1
PUT_ICE_BLOCK 4 3 1
PUT_ICE_BLOCK 4 2 1
MAKE_ROOF

```
### 样例输出 #1
```
CIRNO FREEZED 2 BLOCK(S)
CIRNO FREEZED 2 BLOCK(S)
CIRNO MADE 0 ICE BLOCK(S),NOW SHE HAS 0 ICE BLOCK(S)
CIRNO HAS NO ICE_BLOCK
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 7 BLOCK(S)
CIRNO FREEZED 7 BLOCK(S)
CIRNO FREEZED 0 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 8 ICE BLOCK(S)
BAKA CIRNO,CAN'T PUT HERE
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 7 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 6 ICE_BLOCK(S)
CIRNO MISSED THE PLACE
CIRNO REMOVED AN ICE_BLOCK,AND 1 BLOCK(S) ARE BROKEN
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 5 ICE_BLOCK(S)
CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 3 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 2 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 1 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 0 ICE_BLOCK(S)
CIRNO FREEZED 6 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 7 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 8 ICE BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 16 ICE BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 24 ICE BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 32 ICE BLOCK(S)
CIRNO REMOVED AN ICE_BLOCK
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 32 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 31 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 30 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 29 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 28 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 27 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 26 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 25 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 24 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 23 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 22 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 21 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 20 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 19 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 18 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 17 ICE_BLOCK(S)
0 ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED
0 ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED
GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE
DOOR IS OK
WALL IS OK
CORNER IS OK
CIRNO FINALLY HAS 1 ICE_BLOCK(S)
CIRNO IS PERFECT!

```
## 提示

共分为 $6$ 个 **Subtask**，每个 **Subtask** 的数据都满足一定条件，并且同时满足序号更大的 **Subtask** 的条件。  
如 **Subtask #0** 同时满足 **Subtask #0~5** 的条件。  
每一个 **Subtask** 的得分取所有测试点的最低分。

**Subtask #0** $20\%$  
琪露诺只想玩玩冰雪弹幕，她不会放置任何冰砖，也不会盖房子(即只有操作一和操作二)。  


**Subtask #1** $10\%$  
琪露诺不会移除已经放置的冰砖。

**Subtask #2** $20\%$  
琪露诺很有信心，她将在没有 `MAKE_ROOF` 的情况下建造她的冰屋(这种情况下，放置方块的高度仍然会小于 $H_M$ 且没有 `MAKE_ROOF` 操作)。

**Subtask #3** $20\%$  
琪露诺在移除方块时会谨慎考虑,不会造成任何冰砖摔落。`MAKE_ROOF` 操作移除多余冰砖时，也不会造成屋顶塌陷。

**Subtask #4** $20\%$  
琪露诺不喜欢把门开到四角的柱子旁边(数据保证在所有可能作为门的墙壁空缺中，有一种可能使得门不紧贴四角的柱子)。 

**Subtask #5** $10\%$  
$4\le N\le 16$，$5\le H_M\le 20$，$10\le M\le 10^3$，保证不属于冰屋范围内的所有空地至多构成一个连通块。

注意：判断墙壁是否有残缺时，候选的开门位如果被方块堵住，在当时还未被清空。"能看到残缺"以当时的情况作为判断依据。


---

---
title: "[USACO18FEB] New Barns P"
layout: "post"
diff: 省选/NOI-
pid: P4271
tag: ['2018', 'USACO', '并查集', '连通块', '最近公共祖先 LCA', '树的直径', '动态树 LCT']
---
# [USACO18FEB] New Barns P
## 题目描述

给你一棵树，初始没有节点。你需要支持两种操作：  

- `B p` 表示新建一个节点，将它与 $p$  节点连接；若 $p=-1$，则表示不与其它节点相连  

- `Q k` 表示查询在 $k$ 节点所在的连通块中，距它最远的点的距离。这里距离的定义是两点间经过的边数。
## 输入格式

第一行一个正整数 $q$，表示操作个数。  
接下来 $q$ 行，每行表示一个操作。
## 输出格式

对于每个询问操作，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
7
B -1
Q 1
B 1
B 2
Q 3
B 2
Q 2
```
### 样例输出 #1
```
0
2
1

```
## 提示

【数据范围】  

对于 $100%$ 的数据，$1 \le q \le 10^5$。  
保证操作合法。

The example input corresponds to this network of barns:
```
  (1) 
    \   
     (2)---(4)
    /
  (3)
```
In query 1, we build barn number 1. In query 2, we ask for the distance of 1 to the farthest connected barn. Since barn 1 is connected to no other barns, the answer is 0. In query 3, we build barn number 2 and connect it to barn 1. In query 4, we build barn number 3 and connect it to barn 2. In query 5, we ask for the distance of 3 to the farthest connected barn. In this case, the farthest is barn 1, which is 2 units away. In query 6, we build barn number 4 and connect it to barn 2. In query 7, we ask for the distance of 2 to the farthest connected barn. All three barns 1, 3, 4 are the same distance away, which is 1, so this is our answer.

Problem credits: Anson Hu


---

---
title: "[SHOI2014] 概率充电器"
layout: "post"
diff: 省选/NOI-
pid: P4284
tag: ['2014', '各省省选', '上海', '连通块', '条件概率', '期望', '高斯消元']
---
# [SHOI2014] 概率充电器
## 题目描述

著名的电子产品品牌 SHOI 刚刚发布了引领世界潮流的下一代电子产品——概率充电器：

“采用全新纳米级加工技术，实现元件与导线能否通电完全由真随机数决定！SHOI 概率充电器，您生活不可或缺的必需品！能充上电吗？现在就试试看吧！”

SHOI 概率充电器由 $n-1$ 条导线连通了 $n$ 个充电元件。进行充电时，每条导线是否可以导电以概率决定，每一个充电元件自身是否直接进行充电也由概率决定。随后电能可以从直接充电的元件经过通电的导线使得其他充电元件进行间接充电。

作为 SHOI 公司的忠实客户，你无法抑制自己购买 SHOI 产品的冲动。在排了一个星期的长队之后终于入手了最新型号的 SHOI 概率充电器。你迫不及待地将 SHOI 概率充电器插入电源——这时你突然想知道，进入充电状态的元件个数的期望是多少呢？
## 输入格式

第一行一个整数 $n$。概率充电器的充电元件个数。充电元件由 $1 \sim n$ 编号。

之后的 $n-1$ 行每行三个整数 $a, b, p$，描述了一根导线连接了编号为 $a$ 和 $b$ 的充电元件，通电概率为 $p\%$。

第 $n+2$ 行 $n$ 个整数 $q_i$。表示 $i$ 号元件直接充电的概率为 $q_i\%$。
## 输出格式

输出一行一个实数，为能进入充电状态的元件个数的期望，四舍五入到小数点后 6 位小数。
## 样例

### 样例输入 #1
```
3
1 2 50
1 3 50
50 0 0
```
### 样例输出 #1
```
1.000000
```
### 样例输入 #2
```
5
1 2 90
1 3 80
1 4 70
1 5 60
100 10 20 30 40
```
### 样例输出 #2
```
4.300000
```
## 提示

对于 $30\%$ 的数据，$n \leq 5 \times 10^3$。

对于 $100\%$ 的数据，$n \leq 5 \times 10^5$，$0 \leq p,q_i \leq 100$。


---

---
title: "不围棋"
layout: "post"
diff: 省选/NOI-
pid: P4997
tag: ['模拟', '并查集', 'Special Judge', '连通块', '洛谷月赛']
---
# 不围棋
## 题目背景

「不围棋」是一种非常有趣的棋类游戏。

大家都知道，围棋的「气」是指一个棋子所在的联通块相邻的空格。两粒棋如果在棋盘上线段的两端就认为是相邻的，也就是在同一个连通块里。比如在图中，白子为四个独立的连通块，黑子构成一个连通块，绿色点是黑子连通块唯一的「气」：

![](https://cdn.luogu.com.cn/upload/pic/41011.png )

「提子」是指将没有「气」的棋子提出棋盘，在上图中，如果白方走绿点，那么就可以将黑子全部提走。

在围棋中，我们想尽量多地占领地盘、提走对方棋子。然而，不围棋恰恰相反——不围棋是一种非常和平的游戏，双方的走子不能产生任何提子，也就是说，**任何一次走子不能让棋盘上任何一个棋子所在的连通块没有气**。比如，白方在上图中不能走绿点。

在你的某一步棋后，对方无棋可走，那么你就赢了。
## 题目描述

小 F 对不围棋特别感兴趣，不过他经常输，所以他想做出一个 AI 来替他完成这局游戏。

不过造 AI 实在是太困难啦，小 F 千辛万苦写出来的 AI 被同学们的 AI 锤爆啦！

现在，他想请你帮他实现一个 AI 中一部分的功能——随机模拟，因为他相信你写的程序非常优秀，一定能优化他的 AI。

给你一个 $n \times n$ 的棋盘，上面或许已经有一些棋子了，但此时局面一定是合法的，即**不存在没有气的连通块**；此时轮到黑棋下棋，因此棋盘上**黑白棋子的数量一定是相等的**。

你的任务是，**依次**为黑棋和白棋**随意**指定一个可行的走子位置，直到某一步游戏无法进行，决出胜负为止。

在正式的不围棋比赛还存在一些禁手规则。不过由于小 F 玩的是一种棋盘大小可变的新型不围棋，我们只用考虑上面提到的气的规则就好。
## 输入格式

输入一行一个整数 $n$，表示棋盘大小。
输入接下来 $n$ 行，每行有一个长度为 $n$ 的字符串，表示第 $i$ 行的情况。

* `.` 表示空
* `X` 表示黑棋
* `O` 表示白棋

详细请参考样例。

输入保证，棋盘初始局面合法，`X` 与 `O` 数量相等。
## 输出格式

你需要输出至少一行，假设你输出了 $L$ 行，那么对于前 $L - 1$ 行，你应该输出两个用空格分隔的正整数表示下棋坐标 $x_i, y_i$，其中奇数行表示黑棋的行动，偶数行表示白棋的行动。$x$ 坐标为从上到下从 $1$ 到 $n$，$y$ 坐标为从左到右从 $1$ 到 $n$。

请在第 $L$ 行输出 `-1 -1`，表示此时第 $L$ 手执棋人已经无棋可走。

你的输出可能会很大，即使本题时限为 $3s$，也请你不要使用太慢的方法输出大量内容。

#### 评分方式：

本题启用 Special Judge，并且有部分分。我们将通过以下方式进行计分：

* 如果你输出格式错误，那么该测试点不得分。格式错误包括但不限于：输出了非数字内容；一行输出了超过或者少于两个正整数；输出的坐标在棋盘外；最后一行的输出不是 `-1 -1`。
* 如果你的输出格式正确，但是你的输出的第一行的答案就是不可接受的，那么该测试点不得分。例如：输出的坐标是黑棋不可以下的位置；黑棋有棋可走却输出了 `-1 -1`。
* 如果你的输出格式正确，并且你的前 $k(1 \leq k <L)$ 行输出是可以接受的，那么该测试点将至少得到 $s$ 分，其中 $s = \lfloor \lg k \rfloor + 1$，含义是 $k$ 在十进制表示下是一个 $s$ 位数。
* 如果你的输出完全正确，无论你输出了多少行，你都将得到 $10$ 分。

详情请参考样例解释。
## 样例

### 样例输入 #1
```
3
XXX
OOX
OO.
```
### 样例输出 #1
```
-1 -1
```
### 样例输入 #2
```
3
XOO
XO.
X..
```
### 样例输出 #2
```
2 3
-1 -1
```
## 提示

#### 样例 1 解释：

注意到将棋盘下满会让棋盘上所有连通块都没有气，所以黑棋是无棋可走的。

#### 样例 2 解释：

样例 2 还有两个正确的输出是这样的：
```
3 2
2 3
-1 -1
```
```
3 3
2 3
-1 -1
```
我们将棋盘表示出来：

![](https://cdn.luogu.com.cn/upload/pic/41216.png)

其中，黑棋是三个空格都可以走的。

* 如果黑棋走 $(2, 3)$，如图，此时白棋走任何位置都会提走相邻的黑棋，白棋无棋可走；
 ![](https://cdn.luogu.com.cn/upload/pic/41219.png)

* 如果黑棋走 $(3, 2)$，如图，此时白棋唯一可走的点是 $(2, 3)$，之后黑棋无棋可走；
 ![](https://cdn.luogu.com.cn/upload/pic/41218.png)

* 如果黑棋走 $(3, 3)$，如图，此时白棋唯一可走的点是 $(2, 3)$，之后黑棋无棋可走；
 ![](https://cdn.luogu.com.cn/upload/pic/41217.png)

这三种情况依次对应三个输出，输出任意一种可得到满分。

#### 评分规则解释：

为了解释评分规则，我们以样例 2 为例，对于以下几种输出：
```
I AK IOI
```
很不幸，因为您太强了，所以为了按住躁动的您，我们会给您 $0$ 分。

```
-1 -1
```
```
1 1
-1 -1
```
很不幸，你的第一行没有输出正确，得 $0$ 分。

```
3 3
-1 -1
```
你输出的前 $1$ 行是正确方案的一部分。由于 $1$ 是 $1$ 位数，恭喜你得到了整整 $1$ 分！

#### 数据范围：

![](https://cdn.luogu.com.cn/upload/pic/41855.png)


---

---
title: "随机生成树"
layout: "post"
diff: 省选/NOI-
pid: P5036
tag: ['模拟', '枚举', '连通块']
---
# 随机生成树
## 题目背景

@葛军 改编的水题


## 题目描述

rainheavy在纸上画了N个点（从1到N编号），每个点的颜色用一个整数描述。rainheavy决定用这N个点随机生成一棵树，生成的规则如下：

对于2号点到N号点，每个点随机指定连接一个点。i号点(2 <= i <= N)的连的点在i的约数中和i的倍数中不超过N的中随机挑选一个。（例如N=30时10号点的可以连接1号，2号，5号，20号，30号）

生成的树中不能有重边（不然就不叫树了）

树生成完之后，rainheavy可以计算出这个树有多少个联通块，一个联通块是一些点的集合，需要满足以下两个条件：

1、从集合中任取两个点都满足：两个点颜色相同，且这两个点之间存在一条树边组成的路径，路径上的所有点都和这两个点颜色相同

2、对于集合中的任意一个点和集合外的任意一个点：两点要么不同色，要么不存在一条树边组成的路径使得路径上所有点都和这两个点同色。

rainheavy希望计算出生成的树中联通块个数最多时，需要连接哪些边，但是rainheavy太强了，不屑于做这种辣鸡题目，~~更重要的是他要去AK IOI~~，于是就把题目扔给了你

注：边的顺序

1.首先，满足连通块个数最多的优先（即对于生成连通块有贡献的优先）

2.同样满足条件1时，连接的两个点编号之和较小的边优先（如满足条件1时，连接3号点和5号点的边比连接4号点和5号点的边优先）

3.同时满足条件2时，连接的两个点编号的之中较小的一个较小的边优先（如满足条件2时，连接2号点和6号点的边比连接3号点和5号点的边优先）
## 输入格式

第一行一个整数N代表点数

第二行N个整数，第i个整数$c_i$代表第i个点的颜色

## 输出格式

输出共n-1行，每行两个整数x,y表示需要一条边连接点x和点y（要求x<y，且输出的顺序满足题目描述中边的顺序）

Tip：由于输出较多，建议用快速输出（不会就算了顶多T掉嘛对不对）
## 样例

### 样例输入 #1
```
4
3 2 3 2
```
### 样例输出 #1
```
1 2
1 4
1 3
```
## 提示

对于样例的解释：因为2号、4号点会对生成联通块有贡献（3号你连了也没用），又因为1+2<1+4，所以1 2比1 4优先输出，最后再输出1 3


对于30%的数据, 2 <= N <= 10

对于60%的数据, 2 <= N <= 5000

对于80%的数据, 2 <= N <= 200000

对于100%的数据, 2 <= N <= 500000，1<=颜色<=1e9（反正多了也没用）


---

