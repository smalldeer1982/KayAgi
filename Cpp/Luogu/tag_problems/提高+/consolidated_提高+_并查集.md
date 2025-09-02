---
title: "「SFMOI Round I」Strange Train Game"
layout: "post"
diff: 提高+/省选-
pid: P11146
tag: ['贪心', '并查集', '洛谷原创', 'O2优化', '图论建模', '线性基', '随机化', '洛谷月赛']
---
# 「SFMOI Round I」Strange Train Game
## 题目背景

[English statement](https://www.luogu.com.cn/problem/T512993). **You must submit your code at the Chinese version of the statement.**

SFM 团队又断网了，于是玩起了 Mini Metro，结果发现游戏更新了，列车要自己组装，于是有了这题。


## 题目描述

**提示**：我们在题目描述的最后提供了一份简要的、形式化描述的题面。

SFM 号列车由 $n$ 节车厢组成，编号为 $1\sim n$。每节车厢有一个舒适度 $a_i\in \{0,1\}$，$0$ 代表不舒适，$1$ 代表舒适。管理组想要让舒适的车厢的编号尽量小，也就是说，让 $a$ 的字典序最大。

为此，管理组运来了一辆 $n$ 节车厢的备用车，舒适度表示为 $b_i\in \{0,1\}$。共有 $m$ 个可进行的操作，第 $i$ 个操作的操作参数为 $l_i,r_i$，表示 $\forall l_i\le k\le r_i$，交换 $a_k,b_k$。

可以**从小到大依次**决定是否执行每个操作，但是一共有 $2^m$ 种方案，于是，管理组找来了你，帮忙选出一种最优的方案，最大化 $a$ 的字典序。只需要输出最终得到的 $a$ 即可。

**形式化地**：给定长度为 $n$ 的 $01$ 串 $a,b$，给定 $2m$ 个正整数 $l_i,r_i$。对于 $i=1,2,\cdots,m$，**依次**执行以下操作：
- 选择是否执行第 $i$ 次操作。
    - 如果执行，则对于 $k=l_i,l_{i}+1,\cdots,r_i$，交换 $a_k,b_k$。

最大化 $a$ 的字典序并输出最终的结果。

## 输入格式

第一行，两个正整数 $n,m$，表示字符串的长度和操作次数。

第二行，一个长度为 $n$ 的 $01$ 串 $a$。

第三行，一个长度为 $n$ 的 $01$ 串 $b$。

接下来 $m$ 行，每行两个正整数 $l_i,r_i$，描述第 $i$ 个操作。

## 输出格式

输出一行长度为 $n$ 的 $01$ 串，表示最优操作后的 $a$。

## 样例

### 样例输入 #1
```
10 5
0101011001
0101001110
5 10
2 6
1 10
6 6
3 4
```
### 样例输出 #1
```
0101011110
```
## 提示

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$1\le n,m\le 20$；
- Subtask 2（30 pts）：$l_i$ 互不相同，$a_i \ne b_i$；
- Subtask 3（30 pts）：$1 \le n ,m \le 10^3$；
- Subtask 4（20 pts）：无限制；

对于 $100\%$ 的数据，保证：
- $1\le n,m\le 2\times 10^5$；
- $1\le l_i\le r_i\le n$。


---

---
title: "[JOI 2025 Final] 缆车 / Mi Teleférico"
layout: "post"
diff: 提高+/省选-
pid: P11664
tag: ['并查集', '树状数组', '2025', '生成树', '扫描线', 'JOI（日本）']
---
# [JOI 2025 Final] 缆车 / Mi Teleférico
## 题目背景


译自 [第24回日本情報オリンピック 本選](https://contests.ioi-jp.org/joi-ho-2025/index.html) T3。

Mi Teleférico 指的是连接玻利维亚拉巴斯市（La Paz）及埃尔阿尔托市（El Alto）的缆车系统。

## 题目描述


给定一张 $N$ 个点 $M$ 条边的有向无环图。这张有向图的边是由 $P$ 个公司（编号 $1\sim N$）修建的，每条边恰好被一个公司修建。

节点标号 $1\sim N$，第 $i$（$1\le i\le M$）条边由节点 $A_i$ 指向节点 $B_i$，且是公司 $C_i$ 修建的。这里，保证 $A_i\lt B_i$。

有 $Q$ 个询问，每个询问给定区间 $[L,R]$（$1\le L\le R\le P$）和钱数 $X$。目标是从 $1$ 号点只经过编号 $\in [L,R]$ 的公司修建的边，可以到达其他任意一个节点。

为此，可以选择一个新的区间 $[l',r']$（$1\le l'\le r'\le P$），将 $[L,R]$ 变为 $[l',r']$。这会花费 $|L'-l'|+|R-r'|$ 的代价，这个操作**至多只能执行一次**。操作的代价必须不大于钱数 $X$。

对于每个询问，判断是否能够达成目标。
## 输入格式


如下所示：


> $N$ $M$ $P$\
> $A_1$ $B_1$ $C_1$\
> $A_2$ $B_2$ $C_2$\
> $\vdots$\
> $A_M$ $B_M$ $C_M$\
> $Q$\
> $L_1$ $R_1$ $X_1$\
> $L_2$ $R_2$ $X_2$\
> $\vdots$\
> $L_Q$ $R_Q$ $X_Q$
## 输出格式


对于第 $i$ 个询问，如果可以达成，输出一行一个 $\texttt{Yes}$；否则输出一行一个 $\texttt{No}$。

## 样例

### 样例输入 #1
```
4 6 10
1 2 3
2 4 7
1 2 6
2 3 5
3 4 2
3 4 8
4
3 7 0
5 6 0
3 4 0
1 9 0
```
### 样例输出 #1
```
Yes
No
No
Yes
```
### 样例输入 #2
```
4 6 10
1 2 3
2 4 7
1 2 6
2 3 5
3 4 2
3 4 8
3
5 6 10
3 4 1
7 8 3
```
### 样例输出 #2
```
Yes
No
Yes
```
### 样例输入 #3
```
3 1 1000000000
1 2 6
1
1 1000000000 1000000000
```
### 样例输出 #3
```
No
```
### 样例输入 #4
```
5 9 2000
2 3 1814
2 3 457
1 2 1226
3 4 1354
1 5 1050
1 2 1725
2 3 1383
1 5 1626
1 4 1795
5
850 1872 128
82 428 1217
487 924 573
1639 1926 202
202 420 25
```
### 样例输出 #4
```
Yes
Yes
Yes
Yes
No
```
## 提示


### 样例解释

#### 样例 $1$ 解释

第 $1$ 个询问中，$[3,7]$ 已经可以满足条件，无需进行操作。

第 $2$ 个询问中，$[5,6]$ 不满足条件，然后无法进行任何操作，所以无法达成目标。


该样例满足所有子任务的限制。


#### 样例 $2$ 解释

第 $1$ 个询问中，选择 $l'=1,r'=5$，花费 $5$ 的代价可以达成目标。

该样例满足子任务 $2,3,5\sim 7$ 的限制。


#### 样例 $3$ 解释
该样例满足子任务 $6,7$ 的限制。



#### 样例 $4$ 解释

该样例满足子任务 $5\sim 7$ 的限制。



### 数据范围

- $2\le N\le 3\times 10^5$。
- $1\le M\le 3\times 10^5$。
- $1\le P\le 10^9$。
- $1\le A_i\lt B_i\le N$（$1\le i\le M$）。
- $1\le C_i\le P$（$1\le i\le M$）。
- $1\le Q\le 4\times 10^5$。
- $1\le L_i\le R_i\le P$（$1\le i\le Q$）。
- $0\le X_i\le 10^9$（$1\le i\le Q$）。
- 输入的都是整数。

### 子任务

1. （7pts）$N,M,Q\le 50$，$X_i=0$（$1\le i\le Q$）。
2. （8pts）$P\le 10$。
3. （11pts）$P\le 100$。
4. （23pts）$P\le 3\times 10^5$，$X_i=0$（$1\le i\le Q$）。
5. （9pts）$P\le 3\times 10^5$。
6. （22pts）$N,M\le 8,000$。
7. （20pts）无额外限制。


---

---
title: "【MX-X10-T5】[LSOT-4] Masuko or Haru？"
layout: "post"
diff: 提高+/省选-
pid: P12009
tag: ['并查集', '哈希 hashing', '梦熊比赛']
---
# 【MX-X10-T5】[LSOT-4] Masuko or Haru？
## 题目背景

Shion 作为社团活动后的作业，给 Yotsuba 出了一道数据结构题。

Yotsuba 本来是想用水路查资料的，但是查着查着就去和 Haru 聊天了……

但是还有 1 秒就要到下午 5 点了！Yotsuba 只能去询问 Masuko 这道题怎么做了。

Masuko 当然可以在 1 秒之内解决这道题，她现在想考考你看你能不能 1 秒内解决这道题！
## 题目描述

给你 $n$ 个长度为 $m$ 的 01 串。

区间二元组的定义为满足 $1\le l\le r\le m$ 的二元组 $(l,r)$。

区间集合的定义为区间二元组组成的集合。

定义 01 串 $a$ 关于区间集合 $S$ 的一次变化为任选一个区间二元组 $(l,r)\in S$，$\forall i\in[l,r],a_i\gets a_i\oplus 1$（$\oplus$ 代表二进制按位异或）。

定义 01 串 $a$ 和 $b$ 在区间集合 $S$ 下等价为 $a$ 可以在经过任意次关于 $S$ 的变化后变为 $b$。

刚开始时 $S=\emptyset$。

一共有 $q$ 次操作，每次操作都为插入操作或询问操作。

插入操作为给定一个区间二元组 $(l,r)$，$S\gets S\cup \{(l,r)\}$。

询问操作为给定 $x,y$，你需要判断第 $x$ 个 01 串和第 $y$ 个 01 串是否关于区间集合 $S$ 等价。



## 输入格式

第一行，三个整数 $n,m,q$。

第二行，一个长为 $n\times m$ 的 01 串，每 $m$ 个字符代表一个给定的 01 串，即第 $(i-1)\times m+1$ 个字符到第 $i\times m$ 个字符表示第 $i$ 个 01 串。

接下来 $q$ 行，每行三个正整数，第一个正整数为 $op$。

- 如果 $op=1$ 代表为插入操作，接下来两个正整数为 $l,r$。
- 如果 $op=2$ 代表为询问操作，接下来两个正整数为 $x,y$。
## 输出格式

对于每个询问操作，输出一行，一个字符串，如果等价则输出 `Masuko`，否则输出 `Haru`。
## 样例

### 样例输入 #1
```
2 5 5
1001111001
2 1 2
1 2 3
2 1 2
1 3 4
2 1 2
```
### 样例输出 #1
```
Haru
Haru
Masuko
```
### 样例输入 #2
```
10 10 20
1110001000101011110100110000110111001111111110111101001111011111011101000000000111110100010000100110
2 2 1
2 9 6
2 6 10
2 1 1
2 3 2
1 7 9
2 10 10
2 10 4
1 1 7
1 8 8
1 2 3
1 2 7
2 1 9
2 6 1
1 1 3
2 10 7
1 2 4
2 9 1
1 3 7
1 1 5
```
### 样例输出 #2
```
Haru
Haru
Haru
Masuko
Haru
Masuko
Haru
Haru
Haru
Haru
Haru

```
## 提示

**【样例解释 #1】**

每个 01 串初始形如：

`10011`，  
`11001`。

- 第一次询问：此时集合 $S$ 为空。两个 01 串显然不同。
- 第二次询问：此时集合 $S$ 为 $\{(2,3)\}$，则第一个串只能变成 `10011` 或 `11111`，无法变得相同，故不等价。
- 第三次询问：此时集合 $S$ 为 $\{(2,3),(3,4)\}$，依次进行 $(2,3)$ 变换和 $(3,4)$ 变换即可变为第二个串。故等价。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（17 分）：$n,m\le 10$，$q\le 20$。
- 子任务 2（14 分）：$l=r$。
- 子任务 3（16 分）：$l=r-1$。
- 子任务 4（13 分）：插入操作不超过 $5000$ 次。
- 子任务 5（21 分）：所有的插入操作在所有的询问操作之前。
- 子任务 6（19 分）：无特殊性质。

对于全部的数据，$1\le q,n,m\le 5\times 10^6$，$n\times m\le 10^7$，$1\le l\le r\le m$，$1\le x,y\le n$，$op\in\{1,2\}$。


---

---
title: "[蓝桥杯 2025 国 B] 涂格子"
layout: "post"
diff: 提高+/省选-
pid: P12839
tag: ['并查集', '2025', '组合数学', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 B] 涂格子
## 题目描述

小蓝正在玩一个涂格子的游戏。他有一个大小为 $n \times m$ 的矩阵，他要给这个矩阵中的每个格子都涂上黑色或白色。小蓝希望最终涂完的格子像国际象棋棋盘一样整齐。具体来说，他希望每一个同色连通块都是矩形，且与上下左右四个异色的矩形相邻（如果存在的话）。下图中第一行的两个涂色方案是合法的，第二行的两个涂色方案是不合法的。

![](https://cdn.luogu.com.cn/upload/image_hosting/ewqwlkxf.png)

同时小蓝希望 $k$ 个格子具有特定的颜色。其中第 $i$ 个格子位置是 $(x_i, y_i)$，具有特定的颜色 $c_i$。你需要帮助他求出符合要求的合法涂色方案有多少种。因为方案数可能很大，请对 $998244353$ 取模后输出。
## 输入格式

输入第一行包含三个正整数 $n, m, k$，含义如问题描述所述。

接下来 $k$ 行，每行三个正整数 $x_i, y_i, c_i$，表示格子 $(x_i, y_i)$ 必须被涂成颜色 $c_i$。**注意 $x_i, y_i$ 可能重复出现。**

## 输出格式

输出共一个整数，表示答案。
## 样例

### 样例输入 #1
```
2 2 4
1 1 0
1 2 0
2 1 0
2 2 1
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
3 3 2
1 1 0
2 2 1
```
### 样例输出 #2
```
8
```
## 提示

**【评测用例规模与约定】**

对于 $20\%$ 的评测用例，$n \times m \leq 20$。

对于 $50\%$ 的评测用例，$n, m, k \leq 5000$。

另存在 $30\%$ 的评测用例，$c_i = 0$。

另存在 $10\%$ 的评测用例，$k = 0$。

对于 $100\%$ 的评测用例，$1 \leq n, m \leq 10^9$，$1 \leq k \leq 3 \times 10^5$，$1 \leq x_i \leq n$，$1 \leq y_i \leq m$，$c_i \in \{0, 1\}$。



---

---
title: "[SCOI2010] 连续攻击游戏"
layout: "post"
diff: 提高+/省选-
pid: P1640
tag: ['2010', '四川', '并查集', '各省省选', '二分图']
---
# [SCOI2010] 连续攻击游戏
## 题目描述

lxhgww 最近迷上了一款游戏，在游戏里，他拥有很多的装备，每种装备都有 $2$ 个属性，这些属性的值用 $[1,10000]$ 之间的数表示。当他使用某种装备时，他只能使用该装备的某一个属性。并且每种装备最多只能使用一次。游戏进行到最后，lxhgww 遇到了终极 boss，这个终极 boss 很奇怪，攻击他的装备所使用的属性值必须从 $1$ 开始连续递增地攻击，才能对 boss 产生伤害。也就是说一开始的时候，lxhgww 只能使用某个属性值为 $1$ 的装备攻击 boss，然后只能使用某个属性值为 $2$ 的装备攻击 boss，然后只能使用某个属性值为 $3$ 的装备攻击 boss……以此类推。现在 lxhgww 想知道他最多能连续攻击 boss 多少次？
## 输入格式

输入的第一行是一个整数 $N$，表示 lxhgww 拥有 $N$ 种装备接下来 $N$ 行，是对这 $N$ 种装备的描述，每行 $2$ 个数字，表示第 $i$ 种装备的 $2$ 个属性值。
## 输出格式

输出一行，包括 $1$ 个数字，表示 lxhgww 最多能连续攻击的次数。
## 样例

### 样例输入 #1
```
3
1 2
3 2
4 5

```
### 样例输出 #1
```
2
```
## 提示

对于 $30\%$ 的数据，保证 $N \le 10^3$。

对于 $100\%$ 的数据，保证 $N \le 10^6$。


---

---
title: "海滩防御"
layout: "post"
diff: 提高+/省选-
pid: P1783
tag: ['图论', '二分', '并查集', '最短路']
---
# 海滩防御
## 题目描述

WLP 同学最近迷上了一款网络联机对战游戏（终于知道为毛 JOHNKRAM 每天刷洛谷效率那么低了），但是他却为了这个游戏很苦恼，因为他在海边的造船厂和仓库总是被敌方派人偷袭。于是，WLP 动用了他那丰满且充实的大脑（或许更偏向前者），想出了一个好主意，他把海滩分成垂直于海岸线的若干列，在其中的几列上放置几个信号塔，试图来监视整个海滩。然而，WLP 是一个非常心急的人，他把信号塔建好后才发现还需给信号塔供能，它们才能投入使用（这不是废话么），它们都有一个工作半径，一个圆形区域里的所有敌人都逃不过它们的监视，不过，WLP 发现，敌人们非常狡猾，除非他将道路完全封死，否则 WLP 的敌人可以走过一条任意弯曲的路（不一定走整点，但是不会出第 $0$ 列和第 $N$ 列构成的边界）来偷他的东西。

于是，WLP 就思考了：到底需要给每个信号塔多大的工作半径，才能将从海滩到内地的路径完全封死呢？他再次动用了他那丰满且充实的大脑，想了一堂数学课，终于，还是没想出来。于是，他向 LZZ 神犇求助（额…… CSUNSHINE 的身份是不是暴露了）。

终于，在 WLP：“ %^!\*@#!\*(\*^!\*#@\$^&（此处省略无数卖萌场景）”的哀求下，LZZ 神犇写了一个程序，在一秒内就解决了问题。但是，邪恶的 LZZ 神犇决定要将这个难题共享给无数无辜的 OIer，所以，现在轮到你了。
## 输入格式

第一行两个整数 $N$ 和 $M$，表示海滩被 WLP 分成的列数 $0,1,2,\cdots,N$ 和信号塔个数。

第 $2$ 至第 $M+1$ 行，每行两个数 $X_i$，$Y_i$ 表示 $1,2,3,\cdots,M$ 号信号塔所在的列数和离开海滩的距离。
## 输出格式

一行一个实数，表示最小的工作半径，保留两位小数。

## 样例

### 样例输入 #1
```
5 5
1 5
3 5
5 5
4 30
2 15
```
### 样例输出 #1
```
1.00
```
### 样例输入 #2
```
100 2
30 50
90 100
```
### 样例输出 #2
```
39.05
```
## 提示

### 数据范围及约定

- 对于 $10\%$ 的数据：$1 \le M \le 10$，$1 \le Y_i \le 100$；
- 对于 $30\%$ 的数据：$1 \le M \le 50$，$1 \le Y_i \le 1,000$；
- 对于 $80\%$ 的数据：$1 \le M \le 500$，$1 \le Y_i \le 1,000$；
- 对于 $100\%$ 的数据：$1 \le M \le 800$，$1 \le N \le 1000$，$1 \le X_i \le N$，$1 \le Y_i \le 100,000$。

### 提示

注意，封锁海滩是指，敌人的深入程度是有限制的，若敌人绕过了所有的信号塔，并且可以长驱直入，那么就说明道路没有完全封锁。


---

---
title: "[NOIP 2013 提高组] 货车运输"
layout: "post"
diff: 提高+/省选-
pid: P1967
tag: ['图论', '贪心', '2013', '倍增', '并查集', 'NOIP 提高组', '生成树', '最近公共祖先 LCA']
---
# [NOIP 2013 提高组] 货车运输
## 题目背景

NOIP2013 提高组 D1T3
## 题目描述

A 国有 $n$ 座城市，编号从 $1$ 到 $n$，城市之间有 $m$ 条双向道路。每一条道路对车辆都有重量限制，简称限重。  

现在有 $q$ 辆货车在运输货物， 司机们想知道每辆车在不超过车辆限重的情况下，最多能运多重的货物。

## 输入格式

第一行有两个用一个空格隔开的整数 $ n,m$，表示 A 国有 $ n$ 座城市和 $m$ 条道路。  

接下来 $m$ 行每行三个整数 $x, y, z$，每两个整数之间用一个空格隔开，表示从 $x $ 号城市到 $ y $ 号城市有一条限重为 $z$ 的道路。    
注意： $x \neq y$，两座城市之间可能有多条道路 。

接下来一行有一个整数 $q$，表示有 $q$ 辆货车需要运货。

接下来 $q$ 行，每行两个整数 $x,y$，之间用一个空格隔开，表示一辆货车需要从 $x$ 城市运输货物到 $y$ 城市，保证 $x \neq y$

## 输出格式

共有 $q$ 行，每行一个整数，表示对于每一辆货车，它的最大载重是多少。  
如果货车不能到达目的地，输出 $-1$。

## 样例

### 样例输入 #1
```
4 3
1 2 4
2 3 3
3 1 1
3
1 3
1 4
1 3
```
### 样例输出 #1
```
3
-1
3
```
## 提示

对于 $30\%$ 的数据，$1 \le n < 1000$，$1 \le m < 10,000$，$1\le q< 1000$；

对于 $60\%$ 的数据，$1 \le n < 1000$，$1 \le m < 5\times 10^4$，$1 \le q< 1000$；

对于 $100\%$ 的数据，$1 \le n < 10^4$，$1 \le m < 5\times 10^4$，$1 \le q< 3\times 10^4 $，$0 \le z \le 10^5$。



---

---
title: "白雪皑皑"
layout: "post"
diff: 提高+/省选-
pid: P2391
tag: ['模拟', '并查集', '福建省历届夏令营']
---
# 白雪皑皑
## 题目背景

“柴门闻犬吠，风雪夜归人”，冬天，不期而至。千里冰封，万里雪飘。空中刮起了鸭毛大雪。雪花纷纷，降落人间。 美能量星球（pty 在 spore 上的一个殖民地）上的人们被这美景所震撼。但是 pty 却不高兴，他不喜欢白色的世界，他觉得这样太单调了。所以他想对雪花进行染色，让世界变得多彩些。

## 题目描述

现在有 $n$ 片雪花排成一列。 pty 要对雪花进行 $m$ 次染色操作，第 $i$ 次染色操作中，把第 $((i\times p+q)\bmod n)+1$ 片雪花和第 $((i\times q+p)\bmod n)+1$ 片雪花之间的雪花（包括端点）染成颜色 $i$。其中 $p,q$ 是给定的两个正整数。他想知道最后 $n$ 片雪花被染成了什么颜色。没有被染色输出 $0$。
## 输入格式

输入共四行，每行一个整数，分别为 $n,m,p,q$，意义如题中所述。
## 输出格式

输出共 $n$ 行，每行一个整数，第 $i$ 行表示第 $i$ 片雪花的颜色。
## 样例

### 样例输入 #1
```
4
3
2
4
```
### 样例输出 #1
```
2
2
3
0
```
## 提示

- 对于 $20\%$ 的数据满足：$n,m\leq 1000$。
- 对于 $40\%$ 的数据满足：$n\leq 8000$，$m\leq 10^6$。
- 对于 $80\%$ 的数据满足：$n\leq 5\times 10^5$，$m\leq 10^7$。
- 对于 $100\%$ 的数据满足：$1\leq n\leq 10^6$，$1\leq m\leq 10^7$。

保证 $1\leq m\times p+q,m\times q+p\leq 2\times 10^9$。


---

---
title: "[HAOI2006] 旅行"
layout: "post"
diff: 提高+/省选-
pid: P2502
tag: ['2006', '河南', '并查集', '各省省选', '枚举', '排序']
---
# [HAOI2006] 旅行
## 题目描述

Z 小镇是一个景色宜人的地方，吸引来自各地的观光客来此旅游观光。Z 小镇附近共有 $n$ 个景点（编号为 $1,2,3,\ldots,n$），这些景点被 $m$ 条道路连接着，所有道路都是双向的，两个景点之间可能有多条道路。

也许是为了保护该地的旅游资源，Z 小镇有个奇怪的规定，就是对于一条给定的公路 $r_i$，任何在该公路上行驶的车辆速度必须为 $v_i$。

速度变化太快使得游客们很不舒服，因此从一个景点前往另一个景点的时候，大家都希望选择行驶过程中最大速度和最小速度的比尽可能小的路线，也就是所谓最舒适的路线。
## 输入格式

第一行包含两个正整数 $n,m$。

接下来的 $m$ 行每行包含三个正整数 $x,y,v$。表示景点 $x$ 到景点 $y$ 之间有一条双向公路，车辆必须以速度 $v$ 在该公路上行驶。

最后一行包含两个正整数 $s,t$，表示想知道从景点 $s$ 到景点 $t$ 最大最小速度比最小的路径。$s$ 和 $t$ 不可能相同。
## 输出格式

如果景点 $s$ 到景点 $t$ 没有路径，输出` IMPOSSIBLE`。否则输出一个数，表示最小的速度比。如果需要，输出一个既约分数。

## 样例

### 样例输入 #1
```
4 2
1 2 1
3 4 2
1 4
```
### 样例输出 #1
```
IMPOSSIBLE
```
### 样例输入 #2
```
3 3
1 2 10
1 2 5
2 3 8
1 3
```
### 样例输出 #2
```
5/4
```
### 样例输入 #3
```
3 2
1 2 2
2 3 4
1 3
```
### 样例输出 #3
```
2
```
## 提示

对于 $100\%$ 的数据，$1 \le x,y \le n \le 500$，$1 \le v < 3 \times 10^4$，$1 \le m \le 5 \times 10^3$，$x \ne y$。


---

---
title: "[USACO08JAN] Haybale Guessing G"
layout: "post"
diff: 提高+/省选-
pid: P2898
tag: ['2008', '线段树', '二分', 'USACO', '并查集']
---
# [USACO08JAN] Haybale Guessing G
## 题目描述

The cows, who always have an inferiority complex about their intelligence, have a new guessing game to sharpen their brains.

A designated 'Hay Cow' hides behind the barn and creates N (1 ≤ N ≤ 1,000,000) uniquely-sized stacks (conveniently numbered 1..N) of hay bales, each with 1..1,000,000,000 bales of hay.

The other cows then ask the Hay Cow a series of Q (1 ≤ Q ≤ 25,000) questions about the the stacks, all having the same form:

What is the smallest number of bales of any stack in the range of stack numbers Ql..Qh (1 ≤ Ql ≤ N; Ql ≤ Qh ≤ N)?The Hay Cow answers each of these queries with a single integer A whose truthfulness is not guaranteed.

Help the other cows determine if the answers given by the Hay Cow are self-consistent or if certain answers contradict others.


## 输入格式

\* Line 1: Two space-separated integers: N and Q

\* Lines 2..Q+1: Each line contains three space-separated integers that represent a single query and its reply: Ql, Qh, and A

## 输出格式

\* Line 1: Print the single integer 0 if there are no inconsistencies among the replies (i.e., if there exists a valid realization of the hay stacks that agrees with all Q queries). Otherwise, print the index from 1..Q of the earliest query whose answer is inconsistent with the answers to the queries before it.

## 样例

### 样例输入 #1
```
20 4
1 10 7
5 19 7
3 12 8
11 15 12

```
### 样例输出 #1
```
3

```
## 题目翻译

给一个长度为 $n$ 的数组 $q$ 个条件，数组中的数字互不相同，每个条件格式形如  $l_i,r_i,x_i$ 表示这个数组的区间 $[l_i,r_i]$ 内的最小值为  $x_i$，输出最早与前面的条件有矛盾的条件的编号，如果所有条件都不发生矛盾，输出 $0$。

### 输入格式

第一行两个整数，分别是  $n$ 和  $q$。

第二行至第 $q+1$ 行，每行三个整 $l_i,r_i,x_i$ 描述一个条件。

### 输出格式

仅一个整数，表示最早发生矛盾的条件的编号。如果所有条件都没有发生矛盾，输出 $0$。


---

---
title: "[USACO09FEB] Surround the Islands S"
layout: "post"
diff: 提高+/省选-
pid: P2941
tag: ['2009', 'USACO', '并查集', '枚举', 'Tarjan']
---
# [USACO09FEB] Surround the Islands S
## 题目描述

Farmer John has bought property in the Caribbean and is going to try to raise dairy cows on a big farm composed of islands. Set in his ways, he wants to surround all the islands with fence.

Each island in the farm has the shape of a polygon. He fences the islands one side at a time (between a consecutive pair of vertices) and proceeds clockwise around a given island with his fencing

operations. Since he wants to fence all the islands, he must at some point travel to any other islands using a boat.

He can start fencing at any vertex and, at any vertex he encounters, travel to some vertex on another island, fence all the way around it, and then IMMEDIATELY return back to the same vertex on the original island using the same path he traveled before. Each boat trip has a cost defined by a supplied matrix.

The islands are described by a set of N (3 <= N <= 500) pairs of vertices V1,V2 (1 <= V1 <= N; 1 <= V2 <= N) although you must figure out how to assemble them into islands. The vertices are conveniently numbered 1..N.

The cost of traveling by boat between each pair of vertices is given by a symmetric cost matrix whose elements fall in the range 0..1000.

What is the minimum cost of surrounding the islands with the fence?
## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Each line describes an island's border with two space-separated integers: V1 and V2

\* Lines N+2..2\*N+1: Line i-N-1 contains N integers that describe row i of the cost matrix: Row\_i

## 输出格式

\* Line 1: A single integer that specifies the minimum cost of building the fence

## 样例

### 样例输入 #1
```
12 
1 7 
7 3 
3 6 
6 10 
10 1 
2 12 
2 9 
8 9 
8 12 
11 5 
5 4 
11 4 
0 15 9 20 25 8 10 13 17 8 8 7 
15 0 12 12 10 10 8 15 15 8 8 9 
9 12 0 25 20 18 16 14 13 7 12 12 
20 12 25 0 8 13 14 15 15 10 10 10 
25 10 20 8 0 16 20 18 17 18 9 11 
8 10 18 13 16 0 10 9 11 10 8 12 
10 8 16 14 20 10 0 18 20 6 16 15 
13 15 14 15 18 9 18 0 5 12 12 13 
17 15 13 15 17 11 20 5 0 22 8 10 
8 8 7 10 18 10 6 12 22 0 11 12 
8 8 12 10 9 8 16 12 8 11 0 9 
7 9 12 10 11 12 15 13 10 12 9 0 

```
### 样例输出 #1
```
30 

```
## 提示

1        10            4

xxxxxxx              x

xxxxxxxxx            xxxx

7 xxxxxxxxxxx 6        xxxxxxx

xxxxxxxxxxx       11 xxxxxxxxxx 5

xxxxxxx

xxx
3         12 xxxxxxx 2

xxxxxxxx

xxxxxxxx

xxxxxxxxx

xxxxxxxxx

xxxxxxxxxx

xxxxxxxxxx

8 xxxxxxxxxx 9

The example describes three islands: {1,7,3,6,10}, {4,5,11} and {2,9,8,12}. The travel costs are provided as a matrix. For example, the travel cost from vertex 1 to 2 is 15.


There is more than one solution. One is: FJ starts from vertex 3 then 7 and stops at 1, travels to 11 followed by 4,5,11. He then returns back to 1, and travels to 12 followed by 2,9,8,12. Finally, he returns back to 1 and continues with 10,6,3,7. The costs are 8 \* 2 = 16 for traveling from 1 to 11 and returning back, and 7 \* 2 = 14 for traveling from 1 to 12 and back -- a total cost of 30.

## 题目翻译

**【题目描述】**

Farmer John 在加勒比海购置了一片地产，准备在由一系列岛屿组成的农场上养奶牛。 出于他的意愿，他要把所有的岛屿都用篱笆围上。  
每个岛都是多边形的。每一次，FJ 会给多边形的一个边（即相邻的两个顶点之间）装上篱笆。对于整个岛屿，他会按照顺时针顺序装上篱笆。由于他想要给所有的岛屿都装上篱笆，某些时候，他必须从一个岛屿坐船到另一个岛屿去。  
FJ 可以从任何一个顶点开始装篱笆，也可以从任何一个顶点坐船到另一个岛的某个顶点上，从这个顶点开始把该岛屿的篱笆全都装好，然后**马上**坐船原路返回。保证任意两个顶点间都有航线。在任意两个顶点之间坐船的费用会在一个矩阵中给出。  
所有的岛屿由给定的 $N$ 对顶点 $V_1$，$V_2$ 描述（即：给定顶点 $V_1$ 与 $V_2$ 相邻）。每个顶点具体属于哪个岛屿**不会**在输入中给出。所有顶点由 $1$ 到 $N$ 标号。  
在顶点间坐船旅行的费用由一个 $N \times N$ 的矩阵给出。保证两个岛屿间两个方向的旅行费用相等且不会超过 $1000$。   
请求出 FJ 把篱笆装完所需要的最小花费。

**【输入格式】**

第 $1$ 行：包含一个整数 $N$，含义见题目描述。  
第 $2$ 至第 $N+1$ 行：每行包含两个整数 $V_1$ 和 $V_2$，表示这两个顶点在同一个岛屿上且相邻。  
第 $N+2$ 行至第 $2N+1$ 行：每行包含 $N$ 个整数，第 $i-N-1$ 行的第 $j$ 个整数表示从 $i$ 号顶点坐船到第 $j$ 号顶点的花费。

**【输出格式】**

一行一个整数，表示 FJ 把篱笆装完所需要的最小花费。

**【说明/提示】**

对于所有数据，保证：

+ $3 \leq n \leq 500$
+ $1 \leq V_1,V_2 \leq N$
+ 任意两个顶点之间的旅行花费 $\leq 1000$


---

---
title: "[USACO14JAN] Ski Course Rating G"
layout: "post"
diff: 提高+/省选-
pid: P3101
tag: ['2014', '二分', 'USACO', '并查集']
---
# [USACO14JAN] Ski Course Rating G
## 题目描述

The cross-country skiing course at the winter Moolympics is described by an M x N grid of elevations (1 <= M,N <= 500), each elevation being in the range 0 .. 1,000,000,000.

Some of the cells in this grid are designated as starting points for the course.  The organizers of the Moolympics want to assign a difficulty rating to each starting point.  The difficulty level of a starting point P should be the minimum possible value of D such that a cow can successfully reach at least T total cells of the grid (1 <= T <= MN), if she starts at P and can only move from cell to adjacent cell if the absolute difference in elevation between the cells is at most D.  Two cells are adjacent if one is directly north, south, east, or west of the other.

Please help the organizers compute the difficulty rating for each starting point.

滑雪场用一个M\*N(1 <= M,N <= 500)的数字矩阵表示海拔高度，每个数字表示一个范围在0 .. 1,000,000,000的高度。有些格子被指定为起点，组织者想对这些起点做难度评级。


如果起点P点是一个难度级别为D的起点，则D必须是满足以下条件的一个最小值：


（1）从一个格子只能滑到相邻的格子；


（2）这两个格子的海拔差不超过D；


（3）至少能够到达T（1 <= T <= M\*N）个格子（包括起点本身）。

## 输入格式

\* Line 1: The integers M, N, and T.

\* Lines 2..1+M: Each of these M lines contains N integer elevations.

\* Lines 2+M..1+2M: Each of these M lines contains N values that are either 0 or 1, with 1 indicating a cell that is a starting point.

## 输出格式

\* Line 1: The sum of difficulty ratings of all starting points (note that this may not fit into a 32-bit integer, even though individual difficulty ratings will).

## 样例

### 样例输入 #1
```
3 5 10 
20 21 18 99 5 
19 22 20 16 17 
18 17 40 60 80 
1 0 0 0 0 
0 0 0 0 0 
0 0 0 0 1 

```
### 样例输出 #1
```
24 

```
## 提示

The ski course is described by a 3 x 5 grid of elevations.  The upper-left and lower-right cells are designated as starting points.  From each starting point, we must be able to reach at least 10 cells.


The difficulty rating of the upper-left starting point is 4, and for the lower-right it is 20.



---

---
title: "[USACO15OPEN] Trapped in the Haybales G"
layout: "post"
diff: 提高+/省选-
pid: P3127
tag: ['2015', 'USACO', '并查集', '离散化', '枚举']
---
# [USACO15OPEN] Trapped in the Haybales G
## 题目描述

Farmer John has received a shipment of N large hay bales ($1 \le N \le 100,000$), and placed them at various locations along the road leading to his barn. Unfortunately, he completely forgets that Bessie the cow is out grazing along the road, and she may now be trapped within the bales! Each bale $j$ has a size $S_j$ and a position $P_j$ giving its location along the one-dimensional road.  Bessie the cow can move around freely along the road, even up to the position at which a bale is located, but she cannot cross through this position.  As an exception, if she runs in the same direction for $D$ units of distance, she builds up enough speed to break through and permanently eliminate any hay bale of size strictly less than $D$.  Of course, after doing this, she might open up more space to allow her to make a run at other hay bales, eliminating them as well.

Bessie can escape to freedom if she can eventually break through either the  leftmost or rightmost hay bale.  Please compute the total area of the road consisting of real-valued starting positions from which Bessie cannot escape.


## 输入格式

The first line of input contains $N$.  Each of the next $N$ lines describes a bale, and contains two integers giving its size and position, each in the range $1\ldots 10^9$. All positions are distinct.

## 输出格式

Print a single integer, giving the area of the road from which Bessie cannot escape.
## 样例

### 样例输入 #1
```
5
8 1
1 4
8 8
7 15
4 20
```
### 样例输出 #1
```
14
```
## 题目翻译

### 题目描述

Farmer John 收到了一批 $N$ 个大型干草捆（$1 \le N \le 100,000$），并将它们放置在他通往谷仓的道路上的不同位置。不幸的是，他完全忘记了奶牛 Bessie 正在这条路上吃草，她现在可能被困在这些干草捆之间了！每个干草捆 $j$ 有一个大小 $S_j$ 和一个位置 $P_j$，表示它在这条一维道路上的位置。Bessie 可以在道路上自由移动，甚至可以移动到干草捆所在的位置，但她无法穿过这个位置。唯一的例外是，如果她朝同一方向连续移动 $D$ 单位的距离，她将获得足够的速度，能够突破并永久消除任何大小严格小于 $D$ 的干草捆。当然，在突破之后，她可能会打开更多的空间，从而有机会突破其他干草捆，并继续消除它们。

如果 Bessie 最终能够突破最左侧或最右侧的干草捆，她就可以成功逃脱。请计算道路中所有无法逃脱的实数起始位置的总面积。

### 输入格式

输入的第一行包含 $N$。接下来的 $N$ 行描述每个干草捆，每行包含两个整数，分别表示干草捆的大小和位置，范围均为 $1 \ldots 10^9$。所有位置均不相同。

### 输出格式

输出一个整数，表示 Bessie 无法逃脱的道路总面积。


---

---
title: "[HNOI2010] 物品调度"
layout: "post"
diff: 提高+/省选-
pid: P3207
tag: ['2010', '并查集', '湖南', '置换']
---
# [HNOI2010] 物品调度
## 题目描述

现在找工作不容易，Lostmonkey 费了好大劲才得到 fsk 公司基层流水线操作员的职位。流水线上有 $n$ 个位置，从 $0$ 到 $n - 1$ 依次编号，一开始 $0$ 号位置是空的，其它的位置 $i$ 上有编号为 $i$ 的盒子。Lostmonkey 要按照以下规则重新排列这些盒子。

规则由五个数描述，$q, p, m, d, s$，$s$ 表示空位的最终位置。

首先生成一个序列 $c$，$c_0=0$，$c_{i+1}=(c_i\times q+p)\bmod m$。

接下来从第一个盒子开始依次生成每个盒子的最终位置 $pos_i$，$pos_i=(c_i+d\times x_i+y_i)\bmod n$，$x_i,y_i$ 是为了让第 $i$ 个盒子不与之前的盒子位置相同的由你设定的非负整数，且 $pos_i$ 还不能为 $s$。

如果有多个序列 $x,y$ 满足要求，你需要选择 $y$ 的字典序最小的，当 $y$ 相同时选择 $x$ 字典序最小的。这样你得到了所有盒子的最终位置，现在你每次可以把某个盒子移动到空位上，移动后原盒子所在的位置成为空位。

问把所有的盒子移动到最终位置所需的最少步数。
## 输入格式

第一行包含一个整数 $t$，表示数据组数。

接下来 $t$ 行，每行六个数，$n, s, q, p, m, d$ 意义如上所述。
## 输出格式

对于每组数据输出一个数占一行，表示最少移动步数。

## 样例

### 样例输入 #1
```
1
8 3 5 2 7 4
```
### 样例输出 #1
```
6
```
## 提示

**【样例解释】**

第 $1$ 个到第 $7$ 个盒子的最终位置依次是：$[2, 5, 6, 4, 1, 0, 7]$。

**【数据范围】**

对于 $30 \%$ 的数据，$n \le 100$，  
对于 $100 \%$ 的数据，$1 \le t \le 20$，$1 \le n \le 100000$，$0 \le s < n$。

其余所有数字均为不超过 $100000$ 的正整数。

**【提示】**

计算过程可能超过整型范围。


---

---
title: "[POI 2008] CLO-Toll"
layout: "post"
diff: 提高+/省选-
pid: P3465
tag: ['2008', '并查集', 'POI（波兰）', 'Special Judge']
---
# [POI 2008] CLO-Toll
## 题目描述

King Byteasar has yielded under pressure of Byteotian merchants and  hence decided to settle the issue of toll paid by them.

Byteotia consists of $n$ towns connected with $m$ bidirectional roads.

Each road connects directly two different towns and no two towns are  connected by more than one direct road.

Note that the roads may lead through tunnels or flyovers.

Until now each town in Byteotia imposed duty on everyone who  either entered or left the town.

The merchants, discontented with such situation, lodged a protest  against multiple taxation.

King Byteasar ruled that the town privileges are now restricted.

According to the new royal edict, each town can only charge toll on  merchants travelling by exact one road leading into the town,  regardless of the direction they are travelling in.

Furthermore, for each road, those who travel it cannot be made to pay  the duty to both towns the road connects.

It remains to determine which town should collect toll from which road.

Solving this problem His Highness has commissioned to you.

## Task

Write a programme that:

- reads the Byteotian road system's description from the standard input,

- for each town determines on which road it should impose toll, or claims it is impossible,

- writes out the result to the standard output.

## 输入格式

There are two integers in the first line of the standard input: $n$ and $m$ ($1 \le n \le 100\ 000$, $1 \le n \le 200\ 000$), denoting the number of towns and roads in Byteotia, respectively. The towns are numbered from $1$ to $n$. In next $m$ lines descriptions of the roads follow. In line No. $i$ there are two integers $a_i$ and $b_i$ () meaning that towns $a_i$ and $b_i$ are directly connected by a road.

## 输出格式

If collecting the toll in accordance with the royal edict is impossible, your programme should write the word NIE ('no' in Polish) in the first and only line of the standard output. Otherwise, it should write the word TAK ('yes' in Polish) in the first line, while in the following $n$ lines should tell which city collects toll from which road. Line no. $(i+1)$ should tell on which road the town no. $i$ imposes toll. Since town no. $i$ is obviously one endpoint of this road, it is enough to tell what is the other endpoint. Thus if the town no. $i$ imposes toll on the road connecting it with the town no.$j$ , the line no. $(i+1)$ should contain the number $j$. If more than one solution exists, write out one chosen arbitrarily.

## 样例

### 样例输入 #1
```
4 5
1 2
2 3
1 3
3 4
1 4
```
### 样例输出 #1
```
TAK
3
3
4
1
```
### 样例输入 #2
```
4 3
1 3
3 4
2 3
```
### 样例输出 #2
```
NIE
```
## 提示

样例1：


 ![](https://cdn.luogu.com.cn/upload/pic/6984.png) 

样例2：

![](https://cdn.luogu.com.cn/upload/pic/6985.png)

## 题目翻译

### 题目描述

给你 $n$ 个点和 $m$ 条双向边，问能否将其中的一些边改成有向边，使得只考虑有向边的情况下每个点的入度都为 $1$ 。

### 输入格式

第一行输入 $n,m(1≤n≤100000,1≤m≤200000)$ ，接下来 $m$ 行每行两个数 $a,b$ 表示点 $a$ 和点 $b$ 之间有一条双向边。输入保证没有重边与自环。

### 输出格式

若没有合法方案，输出 $\verb!NIE!$，否则先在第一行输出 $\verb!TAK!$，然后在第 $i+1$ 行输出点 $i$ 的入度是由哪个点出发的边所得到的。

感谢@hdxrie 提供的翻译。


---

---
title: "小D的地下温泉"
layout: "post"
diff: 提高+/省选-
pid: P3820
tag: ['并查集', '洛谷原创', '广度优先搜索 BFS', '连通块', '洛谷月赛']
---
# 小D的地下温泉
## 题目背景

小D最喜欢泡温泉了。小D找某奸商租下了一块$N$行$M$列的地，左上角为$(1,1)$，右下角为$(N,M)$。小D本以为这块地里全是温泉，结果这块地极不稳定，曾经发生过一些地形变动，所以其中一些地方全是土。

## 题目描述

一开始他会告诉你当前这块地的情况，但是小D有一些假操作，希望你操作给他看：

1. 由小D指定$w$个位置，他希望知道其中哪个位置下水泡温泉的范围最大。泡温泉的范围定义为指定位置通过向上下左右四个方向能到达的位置的个数。若询问的位置为土，则范围为0。如果如果有多个位置均为最大，输出给出顺序较前的那个。位置编号为$1,2,...,w$。

2. 由小D指定$w$个位置，他会使用膜法按顺序翻转这$w$个地方的地形。即若原位置是土，则该位置变为温泉；若原位置是温泉，则该位置变为土。因为小D不希望活动范围减少得太快，所以他在将温泉变为土时不会将一个区域分割。

## 输入格式

第一行输入两个整数，$N,M$，为土地大小。

接下来的$N$行每行输入$M$个字符，为'.'（代表温泉）或'\*'（代表土）（不包括引号）

第$N+2$行输入一个整数，$Q$，为操作数量。

接下来的$Q$行，每行先读入两个整数$opt$和$w$，表示操作类型和指定点的数量，在同一行还有$2\times w$个数$x_{1},y_{1},x_{2},y_{2},...,x_{w},y_{w}$，分别表示$w$个操作的位置为$(x_{1},y_{1}),(x_{2},y_{2}),...,(x_{w},y_{w})$。

## 输出格式

对于每个操作1，输出询问的答案并换行

## 样例

### 样例输入 #1
```
5 5
.*...
.****
*....
*****
.....
3
1 2 1 1 1 3
2 1 3 1
1 2 1 1 1 3
```
### 样例输出 #1
```
2
1

```
## 提示

对于30%的数据，$N,M\le 100,\sum w\le 100$

对于70%的数据，$N,M\le 1000$

对于100%的数据，$1\le N\times M,Q\le 10^{6},\sum w\le 10^{6},w\geq 1$

数据在windows下制作



---

---
title: "[SDOI2016] 齿轮"
layout: "post"
diff: 提高+/省选-
pid: P4079
tag: ['搜索', '2016', '并查集', '各省省选', '山东', '逆元']
---
# [SDOI2016] 齿轮
## 题目描述

现有一个传动系统，包含了N个组合齿轮和M个链条。每一个链条连接了两个组合齿轮u和v，并提供了一个传动比x: y。即如果只考虑这两个组合齿轮，编号为u的齿轮转动x圈，编号为v的齿轮会转动y圈。传动比为正表示若编号为u的齿轮顺时针转动，则编号为v的齿轮也顺时针转动。传动比为负表示若编号为u的齿轮顺时针转动，则编号为v的齿轮会逆时针转动。若不同链条的传动比不相容，则有些齿轮无法转动。我们希望知道，系统中的这Ｎ个组合齿轮能否同时转动。

## 输入格式

有多组数据。

第一行给定整数Ｔ，表示总的数据组数，之后依次给出Ｔ组数据。

每一组数据的第一行给定整数Ｎ和Ｍ，表示齿轮总数和链条总数。

之后有Ｍ行，依次描述了每一个链条，其中每一行给定四个整数u，v，x和y，表示只考虑这一组联动关系的情况下，编号为u的齿轮转动x圈，编号为v的齿轮会转动y圈。请注意，x为正整数，而y为非零整数，但是y有可能为负数。

## 输出格式

输出T行，对应每一组数据。首先应该输出标识这是第几组数据，参见样例输出。之后输出判定结果，如果N个组合齿轮可以同时正常运行，则输出Yes，否则输出No。

## 样例

### 样例输入 #1
```
2
3 3
1 2 3 5
2 3 5 -7
1 3 3 -7
3 3
1 2 3 5
2 3 5 -7
1 3 3 7
```
### 样例输出 #1
```
Case #1: Yes
Case #2: No
```
## 提示

对于所有数据，T<=32，N<=1000，M<=10000且x与y的绝对值均不超过100。



---

---
title: "[HEOI2016/TJOI2016] 树"
layout: "post"
diff: 提高+/省选-
pid: P4092
tag: ['搜索', '2016', '线段树', '并查集', '各省省选', '河北', '树链剖分', '天津']
---
# [HEOI2016/TJOI2016] 树
## 题目描述

在 2016 年，佳媛姐姐刚刚学习了树，非常开心。现在他想解决这样一个问题：给定一颗有根树，根为 $1$ ，有以下两种操作：

1. 标记操作：对某个结点打上标记。（在最开始，只有结点 $1$ 有标记，其他结点均无标记，而且对于某个结点，可以打多次标记。）

2. 询问操作：询问某个结点最近的一个打了标记的祖先。（这个结点本身也算自己的祖先）

你能帮帮她吗?

## 输入格式

第一行两个正整数 $N$ 和 $Q$ 分别表示节点个数和操作次数。

接下来 $N-1$ 行，每行两个正整数 $u,v \,\, (1 \leqslant u,v \leqslant n)$ 表示 $u$ 到 $v$ 有一条有向边。

接下来 $Q$ 行，形如 `oper num` ，`oper`  为 `C` 时表示这是一个标记操作, `oper` 为 `Q` 时表示这是一个询问操作。
## 输出格式

输出一个正整数，表示结果

## 样例

### 样例输入 #1
```
5 5 
1 2 
1 3 
2 4 
2 5 
Q 2 
C 2 
Q 2 
Q 5 
Q 3
```
### 样例输出 #1
```
1
2
2
1
```
## 提示

$30\%$ 的数据，$1 \leqslant N, Q \leqslant 1000$ ；

$70\%$ 的数据，$1 \leqslant N, Q \leqslant 10000$ ；

$100\%$ 的数据，$1 \leqslant N, Q \leqslant 100000$ 。


---

---
title: "上帝造题的七分钟 2 / 花神游历各国"
layout: "post"
diff: 提高+/省选-
pid: P4145
tag: ['线段树', '并查集', '枚举', '分块']
---
# 上帝造题的七分钟 2 / 花神游历各国
## 题目背景

XLk 觉得《上帝造题的七分钟》不太过瘾，于是有了第二部。

## 题目描述

"第一分钟，X 说，要有数列，于是便给定了一个正整数数列。

第二分钟，L 说，要能修改，于是便有了对一段数中每个数都开平方(下取整)的操作。

第三分钟，k 说，要能查询，于是便有了求一段数的和的操作。

第四分钟，彩虹喵说，要是 noip 难度，于是便有了数据范围。

第五分钟，诗人说，要有韵律，于是便有了时间限制和内存限制。

第六分钟，和雪说，要省点事，于是便有了保证运算过程中及最终结果均不超过 $64$ 位有符号整数类型的表示范围的限制。

第七分钟，这道题终于造完了，然而，造题的神牛们再也不想写这道题的程序了。"

——《上帝造题的七分钟·第二部》

所以这个神圣的任务就交给你了。

## 输入格式

第一行一个整数 $n$，代表数列中数的个数。

第二行 $n$ 个正整数，表示初始状态下数列中的数。

第三行一个整数 $m$，表示有 $m$ 次操作。

接下来 $m$ 行每行三个整数 `k l r`。

- $k=0$ 表示给 $[l,r]$ 中的每个数开平方（下取整）。

- $k=1$ 表示询问 $[l,r]$ 中各个数的和。

**数据中有可能 $l>r$，所以遇到这种情况请交换 $l$ 和 $r$。**
## 输出格式

对于询问操作，每行输出一个回答。

## 样例

### 样例输入 #1
```
10
1 2 3 4 5 6 7 8 9 10
5
0 1 10
1 1 10
1 1 5
0 5 8
1 4 8
```
### 样例输出 #1
```
19
7
6
```
## 提示

对于 $30\%$ 的数据，$1\le n,m\le 10^3$，数列中的数不超过 $32767$。

对于 $100\%$ 的数据，$1\le n,m\le 10^5$，$1\le l,r\le n$，数列中的数大于 $0$，且不超过 $10^{12}$。


---

---
title: "[USACO18JAN] MooTube G"
layout: "post"
diff: 提高+/省选-
pid: P4185
tag: ['2018', 'USACO', '并查集', '连通块']
---
# [USACO18JAN] MooTube G
## 题目背景

*本题与 [银组同名题目](/problem/P6111) 在题意上一致，唯一的差别是数据范围。*
## 题目描述

在业余时间，Farmer John 创建了一个新的视频共享服务，他将其命名为 MooTube。在 MooTube 上，Farmer John 的奶牛可以录制，分享和发现许多有趣的视频。他的奶牛已经发布了 $N$ 个视频（$1 \leq N \leq 10^5$），为了方便将其编号为  $1 \ldots N$ 。然而，FJ 无法弄清楚如何帮助他的奶牛找到他们可能喜欢的新视频。

FJ 希望为每个 MooTube 视频创建一个“推荐视频”列表。这样，奶牛将被推荐与他们已经观看过的视频最相关的视频。

FJ 设计了一个“相关性”度量标准，顾名思义，它确定了两个视频相互之间的相关性。他选择 $N-1$ 对视频并手动计算其之间的相关性。然后，FJ 将他的视频建成一棵树，其中每个视频是节点，并且他手动将 $N-1$ 对视频连接。为了方便，FJ 选择了 $N-1$ 对，这样任意视频都可以通过一条连通路径到达任意其他视频。 FJ 决定将任意一对视频的相关性定义为沿此路径的任何连接的最小相关性。

Farmer John 想要选择一个 $K$ 值，以便在任何给定的 MooTube 视频旁边，推荐所有其他与该视频至少有 $K$ 相关的视频。然而，FJ 担心会向他的奶牛推荐太多的视频，这可能会分散他们对产奶的注意力！因此，他想设定适当的 $K$ 值。 Farmer John希望得到您的帮助，回答有关 $K$ 值的推荐视频的一些问题。
## 输入格式

第一行输入包含 $N$ 和 $Q$（$1 \leq Q \leq 10^5$）。

接下来的 $N-1$ 行描述了 FJ 手动比较的一对视频。 每行包括三个整数  $p_i$，$q_i$ 和 $r_i$（$1 \leq p_i, q_i \leq N$，$1 \leq r_i \leq 10^9$），表示视频 $p_i$ 和 $q_i$ 已连接并且相关性为 $r_i$。

接下来的 $Q$ 行描述了 Farmer John 的 $Q$ 个问题。每行包含两个整数，$k_i$ 和 $v_i$（$1 \leq k_i \leq 10^9$，$1 \leq v_i \leq N$），表示 FJ 的第 $i$ 个问题询问中当 $K = k_i$ 时，第 $v_i$ 个视频推荐列表中将推荐的视频数。
## 输出格式

输出 $Q$ 行。在第 $i$ 行，输出 FJ 的第 $i$ 个问题的答案。
## 样例

### 样例输入 #1
```
4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1
```
### 样例输出 #1
```
3
0
2

```


---

---
title: "公主の#18文明游戏"
layout: "post"
diff: 提高+/省选-
pid: P4255
tag: ['并查集', 'O2优化', '素数判断,质数,筛法', '逆元']
---
# 公主の#18文明游戏
## 题目背景

公主发现了一个游戏，998，于是我就花钱给她买下来了（捂脸）

## 题目描述

这个游戏叫做《文♂明》（滑稽），但是跟平常意义上的不一样。

这个游戏里有n个城市，标号1~n，有m条双向道路相连，编号1~m。

游戏里会系统会添加Ni个人到一个城市Xi，并给定这些人的信仰Ci

系统还会切断一条道路，并给定道路编号Xi

系统还会给定一个城市Xi，询问从Xi出发可以到达的所有城市中选择Ni个人，

使得他们信仰都为Ci的概率为多少，对19260817取模。

输入数据不保证没有重边和自环。

输入数据不保证同一条边不会被切断两次以上。

因为是公主的游戏，所以本题输入量较大，请注意输入的优化

## 输入格式

第一行三个正整数n,m,q

接下来n行，每行两个正整数Ni,Ci，分别代表第i个城市初始人数和信仰

接下来m行，每行两个正整数Xi,Yi，分别代表这条道路的起点和终点

接下来q行，每行第一个正整数opt（1<=opt<=3）

当opt=1时，表示系统添加人类，输入三个整数Xi,Ni,Ci

当opt=2时，表示系统切断道路，输入一个整数Xi

当opt=3时，表示系统询问概率，输入三个整数Xi,Ni,Ci

## 输出格式

对于每一个opt=3的操作，输出一行一个整数。

## 样例

### 样例输入 #1
```
5 5 5
5 1
9 2
8 1
8 1
6 2
5 2
1 2
2 2
1 1
5 3
1 1 3 2
2 1
3 3 4 1
3 2 3 1
3 1 2 1

```
### 样例输出 #1
```
9293681
15578602
849742

```
## 提示

吐槽某人居然没告诉我 我没放样例

补发样例（其实我本来有样例来着）

在这里跟大家道歉

对于30%的数据，1<=n,m,q<=100

对于60%的数据，1<=n,m,q<=50000

对于100%的数据，1<=n,m,q<=400000

对于100%的数据，保证所有信仰在C++的int，Pascal的long int范围内

对于100%的数据，保证每次添加的人数和初始人数都不超过10

对于100%的数据，保证数据随机生成

题目 @玫葵之蝶


---

---
title: "[USACO18FEB] Snow Boots G"
layout: "post"
diff: 提高+/省选-
pid: P4269
tag: ['2018', '线段树', 'USACO', '并查集', '单调队列']
---
# [USACO18FEB] Snow Boots G
## 题目描述

It's winter on the farm, and that means snow! There are $N$ tiles on the path from the farmhouse to the barn, conveniently numbered $1 \dots N$, and tile $i$ is covered in $f_i$ feet of snow.
In his farmhouse cellar, Farmer John has $B$ pairs of boots, numbered $1 \dots B$. Some pairs are more heavy-duty than others, and some pairs are more agile than others. In particular, pair $i$ lets FJ step in snow at most $s_i$ feet deep, and lets FJ move at most $d_i$ forward in each step.

Farmer John starts off on tile $1$ and must reach tile $N$ to wake up the cows. Tile $1$ is sheltered by the farmhouse roof, and tile $N$ is sheltered by the barn roof, so neither of these tiles has any snow. Help Farmer John determine which pairs of snow boots will allow him to make the trek.
## 输入格式

The first line contains two space-separated integers $N$ and $B$ ($1 \leq N,B \leq 10^5$).
The second line contains $N$ space-separated integers; the $i$th integer is $f_i$, the depth of snow on tile $i$ ($0 \leq f_i \leq 10^9$). It's guaranteed that $f_1 = f_N = 0$.

The next $B$ lines contain two space-separated integers each. The first integer on line $i+2$ is $s_i$, the maximum depth of snow in which pair $i$ can step. The second integer on line $i+2$ is $d_i$, the maximum step size for pair $i$. It's guaranteed that $0 \leq s_i \leq 10^9$ and $1 \leq d_i \leq N-1$.
## 输出格式

The output should consist of $B$ lines. Line $i$ should contain a single integer: $1$ if Farmer John can trek from tile $1$ to tile $N$ wearing the $i$th pair of boots, and $0$ otherwise.
## 样例

### 样例输入 #1
```
8 7
0 3 8 5 6 9 0 0
0 5
0 6
6 2
8 1
10 1
5 3
150 7
```
### 样例输出 #1
```
0
1
1
0
1
1
1

```
## 提示

Problem credits: Dhruv Rohatgi
## 题目翻译

到冬天了，这意味着下雪了！从农舍到牛棚的路上有 $N$ 块地砖，方便起见编号为 $1 \dots N$，第 $i$ 块地砖上积了 $f_i$ 英尺的雪。
在 Farmer John 的农舍的地窖中，总共有 $B$ 双靴子，编号为 $1 \dots B$。其中某些比另一些结实，某些比另一些轻便。具体地说，第 $i$ 双靴子能够让 FJ 在至多 $s_i$ 英尺深的积雪中行走，能够让 FJ 每步至多前进 $d_i$。

Farmer John 从 $1$ 号地砖出发，他必须到达 $N$ 号地砖才能叫醒奶牛们。$1$ 号地砖在农舍的屋檐下，$N$ 号地砖在牛棚的屋檐下，所以这两块地砖都没有积雪。帮助 Farmer John 求出哪些靴子可以帮助他走完这段艰辛的路程。

**【输入格式】**

第一行包含两个空格分隔的整数 $N$ 和 $B$（$1 \leq N,B \leq 10^5$）。  
第二行包含$N$个空格分隔的整数；第 $i$ 个整数为 $f_i$，即 $i$ 号地砖的积雪深度（$0 \leq f_i \leq 10^9$）。输入保证 $f_1 = f_N = 0$。

下面 $B$ 行，每行包含两个空格分隔的整数。第 $i+2$ 行的第一个数为 $s_i$，表示第 $i$ 双靴子能够承受的最大积雪深度。第 $i+2$ 行的第二个数为 $d_i$，表示第 $i$ 双靴子的最大步长。输入保证 $0 \leq s_i \leq 10^9$ 以及 $1 \leq d_i \leq N-1$。

**【输出格式】**

输出包含 $B$ 行。第 $i$ 行包含一个整数：如果 Farmer John 能够穿着第 $i$ 双靴子从 $1$ 号地砖走到 $N$ 号地砖，为 $1$，否则为 $0$。



---

---
title: "[USACO18OPEN] Multiplayer Moo S"
layout: "post"
diff: 提高+/省选-
pid: P4380
tag: ['2018', 'USACO', '并查集', '枚举', '随机化']
---
# [USACO18OPEN] Multiplayer Moo S
## 题目描述

奶牛们提出了一款创新性的新游戏，令人惊讶的是她们给这款游戏取了个最没创意的名字：“Moo”。  
Moo 游戏在一个由 $N \times N$ 个正方形格子组成的棋盘上进行。一头奶牛可以通过大叫一声“哞！”然后把她的数字编号写在这个格子里来占有这个格子。

在游戏结束时，每个格子中都包含一个数。此时，如果一头奶牛创建了一个由连通的格子组成的领域，且该领域的大小不小于其他所有领域，那么这头奶牛就获胜。一个“领域”被定义为一些具有相同数字编号的格子，其中每个格子都直接与另一个同一领域中的格子通过上、下、左或右相邻（对角线不计）。

由于以单牛形式进行游戏有点无聊，奶牛们也对双牛组队进行游戏感兴趣。同一队的两头奶牛可以创建一个领域，但现在领域中的格子可以属于队伍中的任一头奶牛。

给定游戏棋盘的最终状态，请帮助奶牛们计算：  
1. 任何单头奶牛占有的最大领域包含的格子数量。  
2. 任何两头奶牛组成的队伍占有的最大领域包含的格子数量。  

注意，两头奶牛占有的领域必须同时包含队伍中两头奶牛的编号，不能仅仅包含一头。
## 输入格式

输入的第一行包含 $N$（$1 \leq N \leq 250$）。接下来的 $N$ 行，每行包含 $N$ 个整数（每个整数在 $0 \ldots 10^6$ 之间），描述棋盘的最终状态。棋盘中至少出现两种不同的数字。
## 输出格式

输出的第一行描述任何单头奶牛占有的最大领域大小，第二行描述任何两头奶牛的队伍占有的最大领域大小。
## 样例

### 样例输入 #1
```
4
2 3 9 3
4 9 9 1
9 9 1 7
2 1 1 9
```
### 样例输出 #1
```
5
10

```
## 提示

在这个例子中，单头奶牛占有的最大领域是由五个 $9$ 组成的。如果编号为 $1$ 和 $9$ 的奶牛组队，她们可以形成一个大小为 $10$ 的领域。

供题：Brian Dean


---

---
title: "[COCI 2017/2018 #5] Pictionary"
layout: "post"
diff: 提高+/省选-
pid: P4616
tag: ['2017', '并查集', 'COCI（克罗地亚）']
---
# [COCI 2017/2018 #5] Pictionary
## 题目描述

There is a planet, in a yet undiscovered part of the universe, with a country inhabited solely
by mathematicians. In this country, there are a total of ​N mathematicians, and the interesting
fact is that each mathematician lives in their own city. Is it also interesting that no two cities
are connected with a road, because mathematicians can communicate online or by
reviewing academic papers. Naturally, the cities are labeled with numbers from 1 to ​N.

Life was perfect until one mathematician decided to write an academic paper on their
smartphone. The smartphone auto-corrected the word “self-evident” to “Pictionary” and the
paper was published as such. Soon after, the entire country discovered pictionary and
wanted to meet up and play, so construction work on roads between cities began shortly.
.
The road construction will last a total of ​M days, according to the following schedule: on the
first day, construction is done on roads between all pairs of cities that have ​M as their
greatest common divisor. On the second day, construction is done on roads between all
pairs of cities that have ​M-1 as their greatest common divisor, and so on until the ​$M^{th}$ day
when construction is done on roads between all pairs of cities that are co-prime. More
formally, on the $i^{th}$ day, construction is done on roads between cities ​a and ​b if ​gcd(a, b) = $M-i+1$.

Since the mathematicians are busy with construction work, they’ve asked you to help them
determine the minimal number of days before a given pair of mathematicians can play
pictionary together.
## 输入格式

The first line of input contains three positive integers ​N, M
and ​Q
(1 ≤ ​N
, ​Q ≤ 100 000, 1 ≤ ​M
≤ ​N
), the number of cities, the number of days it takes to build the roads, and the number of
queries.

Each of the following ​Q lines contains two distinct positive integers ​A and ​B
(1 ≤ ​A
, ​B ≤ ​N
)
that denote the cities of the mathematicians who want to find out the minimal number of days
before they can play pictionary together.
## 输出格式

The $i^{th}$ line must contain the minimal number of days before the mathematicians from the $i^{th}$ query can play pictionary together.
## 样例

### 样例输入 #1
```
8 3 3
2 5
3 6
4 8
```
### 样例输出 #1
```
3
1
2
```
### 样例输入 #2
```
25 6 1
20 9
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
9999 2222 2
1025 2405
3154 8949
```
### 样例输出 #3
```
1980
2160
```
## 提示

In test cases worth 40% of total points, it will hold ​N
≤ 1000, ​Q
≤ 100 000.

**Clarification of the first test case:**

On the first day, road (3, 6) is built. Therefore the answer to the second query is 1.

On the second day, roads (2, 4), (2, 6), (2, 8), (4, 6) and (6, 8) are built. Cities 4 and 8 are now
connected (it is possible to get from the first to the second using city 6).

On the third day, roads between relatively prime cities are built, so cities 2 and 5 are connected.

**Clarification of the second test case:**

On the second day, road (20, 15) is built, whereas on the fourth day, road (15, 9) is built. After the
fourth day, cities 20 and 9 are connected via city 15.
## 题目翻译

## 题目描述
在宇宙一个不为人知的地方，有一个星球，上面有一个国家，只有数学家居住。
在这个国家有$n$个数学家，有趣的是，每个数学家都住在自己的城市，且城市间无道路相连，因为他们可以在线交流。当然，城市有从$1$到$n$的编号。

一位数学家决定用手机发论文，而手机将“不言而喻”自动更正成了“猜谜游戏”。
不久之后，这个国家就发现了猜谜游戏。他们想要见面一起玩，于是这个国家就开始了修路工程。
道路修建会持续$m$天。对于第$i$天，若$\gcd(a,b)=m-i+1$，则$a$和$b$城市间会修一条路。

由于数学家们忙于建筑工作，请你来确定一对数学家最早什么时候能凑到一起玩。  

## 输入输出格式
### 输入格式
第一行有三个正整数$n,m,q$，表示城市数量、修路持续天数、询问数量。
接下来$q$行，每行有两个正整数$a,b$，表示询问$a$和$b$两个城市的数学家最早什么时候能在一起玩。

### 输出格式
输出$q$行，第$i$行有一个正整数，表示第$i$次询问的结果

## 说明  
**数据范围：**  
对于$40\%$的数据：
$n≤4000,q≤10^5$  
对于全部数据：  
$1≤n,q≤10^5$  
$1≤m≤n$

样例1解释：
在第一天，$(3,6)$之间修了一条路，因此第二次询问输出`1`  
在第二天，$(2,4),(2,6),(2,8),(4,6),(6,8)$之间都修了一条路，此时$4$和$8$号城市连通，第三次询问输出`2`  
在第三天，所有编号互质的城市之间都修了路，$2$和$5$号城市在此时连通，第一次询问输出`1`

样例2解释：
在第二天，$(20,15)$之间修了一条路  
第四天，$(15,9)$之间修了一条路  
所以$20$和$9$号城市在第四天连通，输出`4`


---

---
title: "[USACO14DEC] Cow Jog G"
layout: "post"
diff: 提高+/省选-
pid: P4873
tag: ['2014', 'USACO', '并查集', '树状数组', '离散化']
---
# [USACO14DEC] Cow Jog G
## 题目描述

Farmer John's $N$ cows $(1 <= N <= 100,000)$ are out exercising their
hooves again, jogging along an infinite track.  Each cow starts at a
distinct position on the track, and some cows run at different speeds.

The track is divided into lanes so that cows may move past each other.
No two cows in the same lane may ever occupy the same position.
Farmer John doesn't want any cow to have to change lanes or adjust
speed, and he wonders how many lanes he will need to accomplish this
if the cows are going to run for $T$ minutes $(1 <= T <= 1,000,000,000).$

## 输入格式

The first line of input contains $N$ and $T$.

The following $N$ lines each contain the initial position and speed of a
single cow.  Position is a nonnegative integer and speed is a positive
integer; both numbers are at most 1 billion.  All cows start at
distinct positions, and these will be given in increasing order in the
input.
## 输出格式

A single integer indicating the minimum number of lanes necessary so
that no two cows in the same lane ever occupy the same location
(including at time $T$).

## 样例

### 样例输入 #1
```
5 3
0 1
1 2
2 3
3 2
6 1
```
### 样例输出 #1
```
3
```
## 题目翻译

Farmer John 的 $ N $ 头奶牛 $ ( 1 ≤ N ≤ 10^5 ) $ 正在一条长度无限的跑道上慢跑，每头奶牛都有一个不同的开始位置，以及不同的跑步速度。

为了方便奶牛们互相超越，整个跑道被分成了若干条赛道。在同一时刻，不可能有在同一条赛道上的两头奶牛占据相同的位置。

现在奶牛们要跑 $ T $ 分钟，在跑步过程中，他们不会改变自己所在的赛道和自己跑步的速度。FJ想要知道，为了奶牛间不会发生冲突，他需要至少准备多少条赛道。

输入格式：第一行包括两个整数 $ N $ 和 $ T $ 。接下来 $ N $ 行，每行两个整数 $ p_i $ 和 $ v_i $ $ ( p_i , v_i ≤ 10^9 ) $，分别代表奶牛的初始位置和速度。保证了初始位置不相同且为升序排列。

输出格式：一个整数，代表最少需要的跑道数目。




---

---
title: "[BalticOI 2004] ships 船"
layout: "post"
diff: 提高+/省选-
pid: P5962
tag: ['2004', '并查集', 'BalticOI（波罗的海）']
---
# [BalticOI 2004] ships 船
## 题目描述

有一个由 $n\times n$ 的正方形组成的“船”的游戏棋盘。每个单元格可能属于某艘船(黑色)或为空。如果两个边相邻的单元格都是黑色，那么这两个单元格属于同一艘船。不同船之间没有公共边。船的吨位是这些相邻的单元格数。

下边样例，棋盘中(黑色)的单元格属于船，共有一艘 $29$ 吨的船，三艘 $7$ 吨的船，二艘 $4$ 吨的船，三艘 $1$ 吨的船。

![样例](https://cdn.luogu.com.cn/upload/image_hosting/uk57lz80.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

请写一个程序，对给定的游戏棋盘计算出每艘船的吨位和数量。
## 输入格式

第一行包含一个整数 $n$ 表示游戏棋盘的大小。

以下 $n$ 行，第 $i+1$ 行描述第 $i$ 行的列（船）的信息，中间用一个逗号分隔：    
如果是单独一个数，那么这一列属于船，这列的左、右单元格是空的；    
如果是```-```连接的两个数，表示这两列之间的所有格子（包含这两列）都属于船，则左侧和右侧是空的。    
数据之间用逗号分隔，每行结尾的分号。行中没有空格。如果某行只有一个分号，则这行没有船的信息。
## 输出格式

你的程序必须输出船的信息。每行是一个空格分隔的两个整数。第一个数是船的吨位，第二个数是这个吨位的船只数量。必须以递减顺序输出船的吨位，并且至少有一艘船有此吨位。
## 样例

### 样例输入 #1
```
12
2-4,7,9;
1,4,11-12;
1,4,10,12;
1,4-8,10-12;
1,8;
1,3-6,8,10-12;
1,3,5-6,8,11;
1,8,10-12;
1-8;
;
2;
2-4,7-10,12;
```
### 样例输出 #1
```
29 1
7 3
4 2
1 3
```
## 提示

对于所有的数据，$1\le n\le 3\times 10^4$，船舶总数和船舶吨位都不超过 $10^3$。


---

---
title: "[USACO20JAN] Cave Paintings P"
layout: "post"
diff: 提高+/省选-
pid: P6008
tag: ['动态规划 DP', '2020', 'USACO', '并查集']
---
# [USACO20JAN] Cave Paintings P
## 题目描述

Bessie 成为了一名艺术家，正在创作壁画！她现在正在创作的作品是一个高为 $N$ 的方阵，方阵的每行都由 $M$ 个方格组成（$1\le N,M\le 1000$）。每个方格是空的，画了石头，或者画了水。Bessie 已经画上了包含石头的方格，包括整幅画作的边界。她现在想要将某些空的方格画上水，使得如果这幅画是真实的，其中应当不存在水的净移动。定义从上到下第 $i$ 行的方格的高度为 $N+1-i$。Bessie 想要她的画作满足以下限制：

假设方格 $a$ 画的是水。那么如果存在一条从 $a$ 到方格 $b$ 的路径，由高度不超过 $a$ 的空的方格或是有水的方格组成，路径中每相邻两个方格都有一条公共边，那么 $b$ 画的也是水。

求 Bessie 可以创作的不同作品的数量模 $10^9+7$ 的余数。Bessie 可以将任意数量的空格画上水，包括不画以及全画。
## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $M$。

以下 $N$ 行每行包含 $M$ 个字符。每个字符均为 `.` 或 `#`，分别表示一个空的方格和一个画有石头的方格。第一行和最后一行、第一列和最后一列仅包含 `#`。
## 输出格式

输出一个整数，为满足限制的作品的数量模 $10^9+7$ 的余数。
## 样例

### 样例输入 #1
```
4 9
#########
#...#...#
#.#...#.#
#########
```
### 样例输出 #1
```
9
```
## 提示

### 样例解释

如果第二行中的任意一个方格被画上水，那么所有空的方格必须都被画上水。否则，假设没有这样的方格画有水。那么 Bessie 可以选择画上第三行的空格组成的三个连续区域的任意子集。所以，画作的总数等于 $1+2^3=9$。

### 子任务

- 测试点 $1 \sim 5$ 满足 $N,M \leq 10$。
- 测试点 $ 6 \sim 15$ 没有额外限制。


---

---
title: "[NOI Online #1 提高组] 序列"
layout: "post"
diff: 提高+/省选-
pid: P6185
tag: ['2020', '并查集', '二分图', 'NOI Online']
---
# [NOI Online #1 提高组] 序列
## 题目背景

## 由于本题数据较难构造，所以无法保证卡掉所有错误做法。


## 题目描述

小 D 有一个长度为 $n$ 的整数序列 $a_{1 \dots n}$，她想通过若干次操作把它变成序列 $b_i$。

小 D 有 $m$ 种可选的操作，第 $i$ 种操作可使用三元组 $(t_i,u_i,v_i)$ 描述：若 $t_i=1$，则她可以使 $a_{u_i}$ 与 $a_{v_i}$ 都加一或都减一；若 $t_i=2$，则她可以使 $a_{u_i}$ 减一、$a_{v_i}$ 加一，或是 $a_{u_i}$ 加一、$a_{v_i}$ 减一，因此当 $u_i=v_i$ 时，这种操作相当于没有操作。

小 D 可以以任意顺序执行操作，且每种操作都可进行无限次。现在给定序列与所有操作，请你帮她判断是否存在一种方案能将 $a_i$ 变为 $b_i$。题目保证两个序列长度都为 $n$。若方案存在请输出 `YES`，否则输出 `NO`。
## 输入格式

本题输入文件包含多组数据。

第一行一个正整数 $T$ 表示数据组数。对于每组数据：

第一行两个整数 $n,m$，表示序列长度与操作种数。

第二行 $n$ 个整数表示序列 $a_i$。

第三行 $n$ 个整数表示序列 $b_i$。

接下来 $m$ 行每行三个整数 $t_i,u_i,v_i$，第 $i$ 行描述操作 $i$。

注意：同一个三元组 $(t_i,u_i,v_i)$ 可能在输入中出现多次。
## 输出格式

对于每组数据输出一行一个字符串 `YES` 或 `NO` 表示答案。
## 样例

### 样例输入 #1
```
3
1 1
1
3
1 1 1
2 3
1 2
4 5
1 1 2
2 1 2
1 1 2
3 3
1 2 3
5 5 4
1 1 2
1 1 3
2 2 3
```
### 样例输出 #1
```
YES
YES
YES
```
## 提示

#### 样例 1 解释

第一组数据：使用一次操作 $1$。  
第二组数据：使用三次操作 $1$。  
第三组数据：使用三次操作 $1$，令 $a_1,a_2$ 都增加 $3$，再使用一次操作 $2$，令 $a_1,a_3$ 都增加 $1$。

---

#### 数据范围与提示

对于测试点 $1 \sim 5$：$n=2$，$m=1$，$a_i,b_i \le 99$，$u_1 \ne v_1$，$t_1=1$。  
对于测试点 $6 \sim 10$：$n=2$，$m=1$，$a_i,b_i \le 99$，$u_1 \ne v_1$，$t_1=2$。  
对于测试点 $11 \sim 12$：$n=2$，$a_i,b_i \le 99$，$u_i \ne v_i$。  
对于测试点 $13 \sim 16$：$t_i=2$。  
对于测试点 $17$：$n,m \le 20$。  
对于测试点 $18$：$n,m \le 10^3$。  
对于所有测试点：$1 \le T \le 10$，$1 \le n,m \le 10^5$，$1 \le a_i,b_i \le 10^9$，$t_i \in \{1,2\}$，$1\le u_i,v_i \le n$。


---

---
title: "[USACO20OPEN] Favorite Colors G"
layout: "post"
diff: 提高+/省选-
pid: P6279
tag: ['2020', 'USACO', '并查集', '启发式合并']
---
# [USACO20OPEN] Favorite Colors G
## 题目描述

Farmer John 的 $N$ 头奶牛每头都有一种最喜欢的颜色。奶牛们的编号为 $1\ldots N$，每种颜色也可以用 $1\ldots N$ 中的一个整数表示。  
存在 $M$ 对奶牛 $(a,b)$，奶牛 $b$ 仰慕奶牛 $a$。有可能 $a=b$，此时一头奶牛仰慕她自己。对于任意颜色 $c$，如果奶牛 $x$ 和 $y$ 都仰慕一头喜欢颜色 $c$ 的奶牛，那么 $x$ 和 $y$ 喜欢的颜色相同。

给定这些信息，求一种奶牛喜欢颜色的分配方案，使得每头奶牛最喜欢的颜色中不同颜色的数量最大。由于存在多种符合这一性质的分配方案，输出字典序最小的（这意味着你应当依次最小化分配给奶牛 $1 \ldots N$ 的颜色）。
## 输入格式

输入的第一行包含 $N$ 和 $M$。  
以下 $M$ 行每行包含两个空格分隔的整数 $a$ 和 $b$（$1\le a,b\le N$），表示奶牛 $b$ 仰慕奶牛 $a$。同一对奶牛可能会在输入中多次出现。
## 输出格式

对于 $1\ldots N$ 中的每一个 $i$，用一行输出分配给奶牛 $i$ 的颜色。
## 样例

### 样例输入 #1
```
9 12
1 2
4 2
5 8
4 6
6 9
2 9
8 7
8 3
7 1
9 4
3 5
3 4
```
### 样例输出 #1
```
1
2
3
1
1
2
3
2
3
```
## 提示

#### 样例解释：

在下图中，用粗边框圆表示的是最喜欢颜色 $1$ 的奶牛。

![](https://cdn.luogu.com.cn/upload/image_hosting/iratxzf8.png)

-----

对于 $100\%$ 的数据，$1\le N,M\le 2\times 10^5$。

共 $10$ 个测试点，其中 $1$ 为样例，其余性质如下：
 
测试点 $2\sim 3$ 满足 $N,M\le 10^3$。  
测试点 $4\sim 10$ 没有额外限制。

-----

出题人：William Lin，Benjamin Qi


---

---
title: "[USACO20OPEN] The Moo Particle S"
layout: "post"
diff: 提高+/省选-
pid: P6283
tag: ['2020', 'USACO', '并查集', '排序']
---
# [USACO20OPEN] The Moo Particle S
## 题目描述

FJ 的奶牛们最近很无聊，她们想到了一种全新的方式缓解无聊：研究高等物理！事实上，她们甚至成功发现了一种新的亚原子粒子，她们将其命名为“哞粒子”。

奶牛们正在进行一项有关 $N$ 个哞粒子的实验（$1\le N\le 10^5$）。粒子 $i$ 的“自旋”可以用范围在 $−10^9\ldots 10^9$ 之间的两个整数 $x_i$ 和 $y_i$ 来描述。有时两个哞粒子会发生相互作用。自旋为 ($x_i,y_i$) 和 ($x_j,y_j$) 的两个粒子之间仅当 $x_i\le x_j$ 并且 $y_i\le y_j$ 时会发生相互作用。在这些条件下，有可能这两个粒子中的一个会消失（另一个粒子不会发生任何变化）。在任意给定的时刻，至多只有一次相互作用会发生。

奶牛们想要知道在经过一些任意的相互作用之后剩余的哞粒子的最小数量。
## 输入格式

输入的第一行包含一个整数 $N$，为哞粒子的初始数量。以下 $N$ 行每行包含两个空格分隔的整数，为一个粒子的自旋。每个粒子的自旋各不相同。
## 输出格式

输出一个整数，为经过一些任意的相互作用之后剩余的哞粒子的最小数量。
## 样例

### 样例输入 #1
```
4
1 0
0 1
-1 0
0 -1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3
0 0
1 1
-1 3
```
### 样例输出 #2
```
2
```
## 提示

### 样例输入输出 1 解释

一个可能的相互作用顺序：

- 粒子 $1$ 和 $4$ 相互作用，粒子 $1$ 消失。
- 粒子 $2$ 和 $4$ 相互作用，粒子 $4$ 消失。
- 粒子 $2$ 和 $3$ 相互作用，粒子 $3$ 消失。
仅留下粒子 $2$。

### 样例输入输出 2 解释

粒子 $3$ 不能与任何其他两个粒子相互作用，所以它必然会留下。粒子 $1$ 和 $2$ 中必然留下至少一个。

### 子任务
- 测试点 $3$-$6$ 满足 $N\le 10^3$。
- 测试点 $7$-$12$ 没有额外限制。


---

---
title: "「Wdsr-3」令人感伤的红雨"
layout: "post"
diff: 提高+/省选-
pid: P8010
tag: ['并查集', 'O2优化']
---
# 「Wdsr-3」令人感伤的红雨
## 题目背景



秋静叶是在秋季掌管落叶的神明。在秋季即将迎来落幕之时，因她的力量使然，山里会变得火红一片。同时，将红叶变为落叶也是她工作的一环。

秋穰子是在秋季掌管丰收的神明。与秋静叶的职责相反，她掌管着秋天果实的成熟、秋粮的收获。

交织着快乐与忧愁的秋天，怎能让人不有感而发呢？
## 题目描述

秋穰子和秋静叶是掌管秋天的神灵，因而控制着田地的收成。具体而言，有 $n$ 块田依次排列，第 $i$ 块田的丰收程度为 $a_i$。秋之姐妹会据此得出一年的年成。

在综合考察了各方面因素后，秋之姐妹得出了收获第 $l$ 块至第 $r$ 块田地可以获得的作物总量 $\Omega(l,r)$。具体定义如下：

$$
\begin{aligned}
\Alpha(l,r)&=\max_{i=l}^r\{i\times[a_i=\max_{j=l}^r\{a_j\}]\}\cr
\Beta(l,r)&=\max_{i=l}^r\{\min_{j=1}^i\{\Alpha(j,i)\}\}-\min_{i=l}^r\{\max_{j=1}^i\{\Alpha(j,i)\}\}\cr
\Omega(l,r)&=\min_{i=l}^r\{\min_{j=i}^r\{|\Beta(i,j)|\}\}
\end{aligned}$$

在**提示说明**部分有相关符号的解释。

---

由于相关因素的影响，田地的丰收程度会发生变化。因此秋之姐妹会对 $a$ 进行 $q$ 次操作：

1. 形如 $\colorbox{f0f0f0}{\verb!1 x y!}$，表示让 $a_1,a_{2},a_{3},\cdots ,a_x$ **分别加上** $y$。
2. 形如 $\colorbox{f0f0f0}{\verb!2 l r!}$，表示询问 $\Omega(l,r)$ 的值。
## 输入格式

- 第一行有两个正整数 $n,q$，分别表示田地总数、操作次数。  
- 接下来一行有 $n$ 个整数，表示每块田地的丰收程度。  
- 接下来 $q$ 行，第一个数字 $op$ 表示该操作的种类。  
  - 如果 $op=1$，那么接下来会有两个整数 $x,y$，含义如题意所示。  
  - 如果 $op=2$，那么接下来会有两个正整数 $l,r$，含义如题意所示。
## 输出格式

- 输出若干行。对于每一个操作 $2$，输出对应的结果。
## 样例

### 样例输入 #1
```
6 3
1 1 4 5 1 4
2 3 5
1 2 5
2 3 5
```
### 样例输出 #1
```
0
1
```
### 样例输入 #2
```
10 6
1 3 5 7 8 12 14 15 17 18
2 5 9
1 3 10
2 4 5
1 1 10
2 4 6
2 1 10
```
### 样例输出 #2
```
0
1
3
0
```
## 提示

样例 $3$ 见下发的附件 $\textbf{\textit{sequence3.in}}/\textbf{\textit{sequence3.ans}}$。

#### 数据范围及约定

$$
\def{\arraystretch}{1.5}
\begin{array}{|c|c|c|c|}\hline
\textbf{Subtask} & \bm{n,q\le} & \textbf{特殊性质} & \textbf{分值}\cr\hline
1 & 100 & - & 10\cr\hline
2 & 5\times 10^3 & - &15\cr\hline
3 & 10^5 & \text{A} &10\cr\hline
4 & 10^5 & \text{B} &5\cr\hline
5 & 10^5 & - &30\cr\hline
6 & 6\times 10^6 & - & 30\cr\hline
\end{array}
$$

**特殊性质** $\textbf{A}$：保证对于任意的 $i\in[1,n-1]$，都有 $a_i<a_{i+1}$。  
**特殊性质** $\textbf{B}$：保证没有操作 $1$。

对于全部数据，保证 $1 \leq n,q \leq 6\times10^6$，$a_i,y_i\in[0,10^9]$，$1\le x_i\le n$，$1\le l_i\le r_i \le n$。

#### 符号解释

- $[P]$ 是艾弗森括号，其中 $P$ 是一个条件。如果 $P$ 为真，则该式子的值为 $1$；否则为 $0$。也就是说，  
$$[P]=\begin{cases}1 & \text{$P$ 为真}\cr 0 & \text{$P$ 为假}\end{cases}$$  
- $\min\limits_{i=l}^r\{P\}$ 表示当 $i$ 取 $l,l+1,l+2,\cdots,r$ 时，表达式 $P$ 的取值的最小值；同理定义了 $\max\limits_{i=l}^r\{P\}$。

#### 提示

本题输入输出量较大，请注意常数因子的影响。


---

---
title: "泪光 | Tears"
layout: "post"
diff: 提高+/省选-
pid: P8149
tag: ['并查集', '2022', 'O2优化']
---
# 泪光 | Tears
## 题目背景

「为什么哭呢？」

“因为自己的期许和现实相去甚远。”

「哭能改变什么呢？」

“什么都不能。正如同既成事实的过去一样。”

「那么为何不抹去泪水向前迈进呢？」

“… 我在等我的灵魂追上时间。”

> After night
>
> 长夜之后
>
> In boundless light
>
> 无垠光中
>
> He calls my name
>
> 他呼唤着我
>
> I do the same
>
> 我望向彼方，回应
## 题目描述

「不想回忆的事，就别再去想了吧。为了分散你的注意力，正好我有一道与人的感情相关的题目，你看看怎么样？」

“… 真是令人想吐槽呢。怎么，又是那个人在支配吗？”

「什么嘛，令人不快… 你以前对这种事不是有很大的热情吗？」

“… 说不准。”

「咳咳… 那么听好了。现在共有 $n$ 个人，每个人都有一个情绪值：用 **实数** $v_i$ 表示。现在由于一些特殊的变化，使得这些人的情感发生了纠缠…」

“嗯哼？”

「第一种纠缠有四个参数 $a,b,c,d$，表示：现在已知存在无穷个 $f:\R\rightarrow\R$，使得 $\frac{f(v_a)}{f(v_b)}=\frac{v_c}{v_d}$。」

“等等等等一下！这数学公式是怎么说出来的啊？！还有什么 $f:\R\rightarrow\R$ 是什么意思啊！”

「你瞧，你不也说出来了吗？」

“… 可恶，果然是你吗，那个人…”

「简单来说，$f:\R\rightarrow\R$ 就是代表一个定义域和值域都是实数的函数。如果这都不能理解的话，我要开始怀疑你作为高中生的身份了哦…」

“好吧… 继续吧。”

「第二种纠缠有两个参数 $a,b$，表示：现在已知存在有穷个 $f:\R\rightarrow\R$，使得 $f(v_a)\ne f(v_b)$。」

“什么叫‘有穷个’？”

「就是有一个确切的数目啦… 只要有一个自然数 $k$ 能表示这样函数的数目，那么就叫‘存在有穷个函数’哦？」

“嗯…”

「接下来，在纠缠不断增加的过程中，你也需要回答一些问题。第一种是，给出 $a,b$，你需要判断 $v_a$ 是否总是等于 $v_b$；第二种是，给出 $a$，你需要计算有多少个 $b$（$1\le b\le n$，$b$ 可以等于 $a$）使得 $v_a=v_b$ 恒成立。」

“… 题目我明白了，但是这跟人的情感有什么关系吗？”

「哈哈… 就是想逗你开心嘛，别那么严肃。」

“… 无聊。”

### 简要题意

有 $n$ 个 **正实数** 变量 $v_1,\dots,v_n$。你需要根据当前已知的条件作出判断。每次给出两种条件之一：

- 给出常数 $a,b,c,d$：表示现在已知存在无穷个 $f:\R\rightarrow\R$，使得 $\frac{f(v_a)}{f(v_b)}=\frac{v_c}{v_d}$。

- 给出常数 $a,b$：表示现在已知存在有穷个 $f:\R\rightarrow\R$，使得 $f(v_a)\ne f(v_b)$。

或者两种询问之一：

- 给出常数 $a,b$：询问 $v_a=v_b$ 是否恒成立。

- 给出常数 $a$：询问有多少个 $b$（$1\le b\le n$，$b$ 可以等于 $a$）使得 $v_a=v_b$ 恒成立。
## 输入格式

第一行两个正整数 $n,m$，分别表示变量的数量和操作的次数。

接下来 $m$ 行，每行表示一次操作，有四种可能：

- `1 a b c d`：表示现在已知存在无穷个 $f:\R\rightarrow\R$，使得 $\frac{f(v_a)}{f(v_b)}=\frac{v_c}{v_d}$。

- `2 a b`：表示现在已知存在有穷个 $f:\R\rightarrow\R$，使得 $f(v_a)\ne f(v_b)$。

- `3 a b`：询问 $v_a=v_b$ 是否恒成立。

- `4 a`：询问有多少个 $b$（$1\le b\le n$，$b$ 可以等于 $a$）使得 $v_a=v_b$ 恒成立。
## 输出格式

对于每次操作三，输出一行字符串 `entangled` 表示 $v_a=v_b$ 恒成立；反之输出一行字符串 `separate`。

对于每次操作四，输出一行一个整数表示符合条件的 $b$ 的数目。
## 样例

### 样例输入 #1
```
2 2
2 1 2
3 1 2
```
### 样例输出 #1
```
entangled
```
### 样例输入 #2
```
5 7
1 1 2 3 4
3 1 2
2 1 2
3 1 2
3 3 4
4 1
4 2
```
### 样例输出 #2
```
separate
entangled
entangled
2
2
```
### 样例输入 #3
```
7 6
1 1 2 3 4
1 3 5 6 7
2 4 5
3 6 7
2 1 2
3 6 7
```
### 样例输出 #3
```
separate
entangled
```
## 提示

对于全部数据，有 $1\le n,m\le 6\times 10^5$。保证操作一中 $a\ne b,c\ne d$，操作二中 $a\ne b$，操作三中 $a\ne b$。

Subtask 1（5 pts）：保证不出现操作一和操作二。

Subtask 2（10 pts）：保证不出现操作一。

Subtask 3（35 pts）：保证 $n\le 5000$。

Subtask 4（50 pts）：无特殊限制。


---

---
title: "[USACO22DEC] Strongest Friendship Group G"
layout: "post"
diff: 提高+/省选-
pid: P8905
tag: ['USACO', '并查集', '2022', '枚举', '连通块']
---
# [USACO22DEC] Strongest Friendship Group G
## 题目描述

Farmer John 有 $N$ 头奶牛（$2 \le N \le 10^5$），编号为 $1\cdots N$。这些奶牛中有 $M(1 \le M \le 2\times 10^5)$ 对朋友。

一组奶牛被称为是「小团体」，如果该组中的每头奶牛都可以从该组中的每头其他奶牛出发通过完全位于该组内的一系列朋友关系到达（连接到组外奶牛的朋友关系无效）。小团体的「强度」是组内奶牛的最小组内朋友数乘以组内奶牛的数量（同样，注意连接到组外奶牛的朋友关系不计入此定义）。

求所有小团体的最大强度。 
## 输入格式

输入的第一行包含 $N$ 和 $M$。

以下 $M$ 行每行包含两个整数 $u_i$ 和 $v_i$，表示奶牛 $u_i$ 和 $v_i$ 是朋友（$1 \le u_i,v_i \le N,u_i\neq v_i$）。每个奶牛无序对至多出现一次。 
## 输出格式

 输出一行，包含所有小团体的最大强度。 
## 样例

### 样例输入 #1
```
8 10
1 2
1 3
1 4
2 3
2 4
3 4
1 5
2 6
3 7
4 8
```
### 样例输出 #1
```
12
```
## 提示

### 样例 1 解释

可以观察到最大强度来自编号为 $1,2,3,4$ 的奶牛组。该组内奶牛的最小朋友数为 $3$，故答案为 $4 \times 3=12$。

### 测试点性质

 - 对于 $1 \le T \le 3$，测试点 $T$ 满足 $N \le 16$。
 - 对于 $4 \le T \le 9$，测试点 $T$ 满足 $N \le 1000$。
- 对于 $10 \le T \le 20$，测试点 $T$ 没有额外限制。 


---

---
title: "「VUSC」Math Game"
layout: "post"
diff: 提高+/省选-
pid: P8954
tag: ['数学', '并查集', '深度优先搜索 DFS']
---
# 「VUSC」Math Game
## 题目背景

**upd 2023.1.22**：新增一组 Hack 数据 by @[MCRS_lizi](https://www.luogu.com.cn/user/585805)。

远在哞利坚的 Bessie 也要在新春之际走亲访友！为了打发时间，她常和 Farmer John 玩一个有趣的数字游戏。
## 题目描述

Farmer John 有一个集合 $S$，集合初始为 $\{2,3,4,...,N\}$。

对于两个**在集合 $S$ 内的**正整数 $p,q$，我们称它们为「一对好数」当且仅当 $p^k=q(k\ge 2\land k\in\N)$。

我们将每个 $S$ 中的数看成一张**无向图**中的节点，对于每一对「好数」，我们在这两个数间连一条无向边。

Farmer John 会进行 $Q$ 次操作，操作有以下两种：

1. 给出 $x$，询问结点 $x$ 所在的连通块大小。
2. 给出 $x$，从 $S$ 中移除 $x$。**与此同时，无向图中的结点 $x$ 也被移除。**

由于 Bessie 的速度太慢了，她想要你来帮忙。
## 输入格式

第 $1$ 行 $2$ 个正整数，$N,Q$。

接下来 $Q$ 行，每行一个正整数，$op_i,x_i$。
其中，$op_i$ 表示操作的序号。

**数据保证 $x_i$ 在集合 $S$ 中**。
## 输出格式

对于操作 $1$，每行输出一个正整数，表示询问的答案。
## 样例

### 样例输入 #1
```
30 6
1 6
1 4
2 9
1 3
2 2
1 16
```
### 样例输出 #1
```
1
4
2
2
```
## 提示

#### 【样例解释】

这是原始无向图（上面一排都是孤点）：
![](https://cdn.luogu.com.cn/upload/image_hosting/utsz04dt.png)

这是进行第一次操作 $2$ 后的无向图（删除了结点 $9$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/wmexc9ks.png)

这是进行第二次操作 $2$ 后的无向图（删除了结点 $2$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/9mi0l18p.png)

---

#### 【数据范围】

全部数据满足：
- $2\le N \le 10^{18}$
- $1\le Q \le 10^6$
- $x_i\in S$
- $op_i \in \{1,2\}$

测试点 $1\sim2$ 另外满足 $2\le N \le 10^5$，$1\le Q \le 10^4$。

测试点 $3\sim4$ 另外满足所有 $x_i=m^{p_i}$，其中 $m$ 为一满足 $m\ge 2 \land m\in \N$ 的**常数**。

测试点 $5\sim10$ 没有额外限制。



---

---
title: "[蓝桥杯 2023 省 A] 网络稳定性"
layout: "post"
diff: 提高+/省选-
pid: P9235
tag: ['图论', '贪心', '并查集', '2023', '生成树', '最近公共祖先 LCA', '蓝桥杯省赛']
---
# [蓝桥杯 2023 省 A] 网络稳定性
## 题目描述

有一个局域网，由 $n$ 个设备和 $m$ 条物理连接组成，第 $i$ 条连接的稳定性为 $w_i$。

对于从设备 $A$ 到设备 $B$ 的一条经过了若干个物理连接的路径，我们记这条路径的稳定性为其经过所有连接中稳定性最低的那个。

我们记设备 $A$ 到设备 $B$ 之间通信的稳定性为 $A$ 至 $B$ 的所有可行路径的稳定性中最高的那一条。

给定局域网中的设备的物理连接情况，求出若干组设备 $x_i$ 和 $y_i$ 之间的通信稳定性。如果两台设备之间不存在任何路径，请输出 $-1$。
## 输入格式

输入的第一行包含三个整数 $n,m,q$，分别表示设备数、物理连接数和询问数。

接下来 $m$ 行，每行包含三个整数 $u_i,v_i,w_i$，分别表示 $u_i$ 和 $v_i$ 之间有一条稳定性为 $w_i$ 的物理连接。

接下来 $q$ 行，每行包含两个整数 $x_i,y_i$，表示查询 $x_i$ 和 $y_i$ 之间的通信稳定性。
## 输出格式

输出 $q$ 行，每行包含一个整数依次表示每个询问的答案。
## 样例

### 样例输入 #1
```
5 4 3
1 2 5
2 3 6
3 4 1
1 4 3
1 5
2 4
1 3
```
### 样例输出 #1
```
-1
3
5
```
## 提示

【评测用例规模与约定】

对于 $30 \%$ 的评测用例，$n,q \leq 500$，$m \leq 1000$；

对于 $60 \%$ 的评测用例，$n,q \leq 5000$，$m \leq 10000$；

对于所有评测用例，$2 \leq n,q \leq 10^5$，$1 \leq m \leq 3 \times 10^5$，$1 \leq u_i,v_i,x_i,y_i \leq n$，$
1 \leq w_i \leq 10^6$，$u_i \neq v_i$，$x_i \neq y_i$。


---

---
title: "[JOI 2023 Final] Cat Exercise"
layout: "post"
diff: 提高+/省选-
pid: P9352
tag: ['并查集', '2023', 'JOI（日本）']
---
# [JOI 2023 Final] Cat Exercise
## 题目描述

There are $N$ cat towers, numbered from $1$ to $N$. The height of Tower $i$ ($1 \le i \le N$) is $P_i$. The heights of the towers are distinct integers between $1$ and $N$, inclusive. There are $N - 1$ adjacent pairs of towers. For each $j$ ($1 \le j \le N - 1$), Tower $A_j$ and Tower $B_j$ are adjacent to each other. In the beginning, it is possible to travel from a tower to any other tower by repeating moves from towers to adjacent towers.

In the beginning, a cat stays in a tower of height $N$.

Then we perform **cat exercises**. In cat exercises, we repeatedly choose a tower and put an obstacle on it. However, we cannot put an obstacle on a tower where we already put an obstacle on it. During the process, the following will happen.

- If the cat does not stay in the chosen tower, nothing will happen.
- If the cat stays in the chosen tower and there is an obstacle on every tower which is adjacent to the chosen tower, the cat exercises will finish.
- Otherwise, among the towers where the cat can arrive by repeating moves from towers to adjacent towers without obstacles, the cat will move to the highest tower except for the current tower by repeating moves from towers to adjacent towers. In this process, the cat takes the route where the number of moves from towers to adjacent towers becomes minimum.

Given information of the heights of the towers and pairs of adjacent towers, write a program which calculates the maximum possible sum of the number of moves of the cat from towers to adjacent towers if we put obstacles suitably.
## 输入格式

Read the following data from the standard input.

> $N$  
> $P_1$ $P_2$ $\cdots$ $P_N$  
> $A_1$ $B_1$  
> $A_2$ $B_2$  
> $\vdots$    
> $A_N$ $B_N$
## 输出格式

Write one line to the standard output. The output should contain the maximum possible sum of the number of moves of the cat from towers to adjacent towers.
## 样例

### 样例输入 #1
```
4
3 4 1 2
1 2
2 3
3 4

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
7
3 2 7 1 5 4 6
1 2
1 3
2 4
2 5
3 6
3 7

```
### 样例输出 #2
```
7

```
## 提示

## Samples

### Sample 1

If we perform the cat exercises in the following way, the cat moves 3 times in total.

- We put an obstacle on Tower 1. The cat does not move.
- We put an obstacle on Tower 2. The cat moves from Tower 2 to Tower 3. Then, the cat moves from Tower 3 to Tower 4.
- We put an obstacle on Tower 4. The cat moves from Tower 4 to Tower 3.
- We put an obstacle on Tower 3. Then the cat exercises finish.

Since there is no way to perform cat exercises where the cat moves more than or equal to 4 times from towers to adjacent towers, output 3.

This sample input satisfies the constraints of Subtasks 1, 2, 3, 4, 5, 7.

### Sample 2

This sample input satisfies the constraints of Subtasks 4, 6, 7.

## Constraints

- $2 \le N \le 2\times 10^5$.
- $1 \le P_i \le N$ ($1 \le i \le N$).
- $P_i \neq P_j$ ($1 \le i < j \le N$).
- $1 \le A_j < B_j \le N$ ($1 \le j \le N - 1$).
- In the beginning, it is possible to travel from a tower to any other tower by repeating moves from towers to adjacent towers.
- Given values are all integers.

## Subtasks

1. (7 points) $A_i = i, B_i = i + 1$ ($1 \le i \le N - 1$), $N \le 16$．
2. (7 points) $A_i = i, B_i = i + 1$ ($1 \le i \le N - 1$), $N \le 300$．
3. (7 points) $A_i = i, B_i = i + 1$ ($1 \le i \le N - 1$), $N \le 5 000$．
4. (10 points) $N \le 5 000$．
5. (20 points) $A_i = i, B_i = i + 1$ ($1 \le i \le N - 1$)．
6. (23 points) $A_i =\left\lfloor\frac{i+1}2\right\rfloor, B_i = i + 1$ ($1 \le i \le N - 1$). Here $\lfloor x \rfloor$ is the largest integer which is smaller than or equal to $x$.
7. (26 points) No additional constraints.
## 题目翻译

有 $N$ 个猫爬架，编号从 $1$ 到 $N$。第 $i$（$1 \le i \le N$）个架子的高度是 $P_i$。架子的高度是 $1$ 和 $N$ 之间的不同整数，包括 $1$ 和 $N$。有 $N - 1$ 对架子彼此相邻。对于每个 $j$（$1 \le j \le N-1$），第 $A_j$ 个架子和第 $B_j$ 个架子彼此相邻。从任意一个架子开始，总能通过不断移动到相邻的架子来到达所有其它架子。

一开始，一只猫待在高度为 $N$ 的那个架子中。

接下来对这只猫进行锻炼。在锻炼中，我们每次选择一个架子并在其上放置障碍物。但是，我们不能在已经放置障碍物的架子上再放置障碍物。在此过程中，会发生以下情况。

- 如果猫不待在选定的架子中，则什么也不会发生。
- 如果猫待在选定的架子中，并且与选定架子相邻的每个架子上都有障碍物，则锻炼结束。
- 否则，猫将沿最短路径前往，仅通过移动到相邻的架子且不经过放置过障碍物的架子，能到达的所有架子中，高度最高的那个。

给定每个架子的高度和架子彼此相邻的方式，编写一个程序，计算如果我们适当放置障碍物，猫最多需要移动多少次。从一个架子移动到相邻的架子被称为一次移动。


---

---
title: "「yyOI R1」youyou 的军训"
layout: "post"
diff: 提高+/省选-
pid: P9638
tag: ['并查集', 'Kruskal 重构树', 'O2优化', '生成树']
---
# 「yyOI R1」youyou 的军训
## 题目背景

在 youyou 的班上，身高可能是一个敏感的话题。
## 题目描述

youyou 的班上一共有 $n$ 位同学，$m$ 对朋友，第 $i$ 对朋友关系对于身高有一个敏感值 $k_i$，敏感值可能会改变。

我们定义两位同学如果互为**朋友**，那么必然存在某对关系，将两位同学**直接**相连。

我们定义两位同学如果互为**好友**，那么必然存在直接或间接的关系，将两位同学相连。

例如存在关系 $(1,2)$ 和 $(2,3)$，那么，$1$ 与 $2$ 是朋友，但 $1$ 与 $3$ 就是好友。

现在，马上就要军训了，同学们要去领军训的服装，如果一位同学领到了尺码为 $p$ 的服装，所有同学会与朋友关系敏感值小于 $p$ 的朋友断交。即对于所有的朋友关系，若其敏感值小于 $p$，那么该朋友关系就会断开。不过在下一位同学领到服装时，所有**之前**的断开的朋友关系会恢复。

由于军训领服装是一个复杂的过程，而 youyou 对此十分感兴趣，所以给出 $q$ 次操作，且一共有三种操作:

- 操作 $1$，形如 `1 x`，表示有一位同学领到尺码为 $x$ 的服装。

- 操作 $2$，形如 `2 x`，表示询问第 $x$ 位同学还有多少位好友（包括自己）。

- 操作 $3$，形如 `3 x y`，表示第 $x$ 对朋友的敏感值变为 $y$，特别地，**敏感值的相对大小不会变化$^*$**（详情见下方），同时原来已经断开的关系不会恢复。

**注意：好友跟朋友是两个概念，朋友一定是好友，但好友不一定是朋友。**

$^*$：相对大小不会变化，指对于当前所有的敏感值而言，修改后的敏感值与原来的敏感值**排名相同**。

例如，若原来所有对朋友之间敏感值是 $\{1,2,3,5,6\}$，$3$ 的排名为 $3$，因此 $3$ 只能修改为 $3,4$ 中的一个，这样才能保证排名不变，即相对大小位置不会变换。
## 输入格式

第一行，输入三个正整数 $n,m,q$。

后面 $m$ 行，给定 $m$ 对朋友关系，对于第 $i$ 行给定三个正整数 $x_i,y_i,k_i$。

最后 $q$ 行，给定 $q$ 次操作。对于每次操作，给定一个正整数为 $op$，即操作类型。

当 $op=1$ 时，再给定一个正整数 $x$，表示有一位同学领到尺码为 $x$ 的服装；

当 $op=2$ 时，再给定一个正整数 $x$，表示一次询问；

当 $op=3$ 时，再给定两个正整数 $x,y$，表示一次修改。
## 输出格式

对于每次询问操作，输出一个 $x$ 表示询问的同学还有几位**好友**（**包括自己**）。保证对于每一个测试点，都会有一个询问操作。
## 样例

### 样例输入 #1
```
4 3 3
1 2 156
1 4 42
2 3 0
1 26963
3 3 40
2 4
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
7 6 7
1 2 292
1 3 274
1 4 221
1 5 156
3 4 42
3 6 40
1 30
3 4 50
2 6
3 3 250
3 1 298
1 280
2 1
```
### 样例输出 #2
```
6
2
```
## 提示


## 样例解释 #1

如图所示，这是初始的关系图。

![](https://cdn.luogu.com.cn/upload/image_hosting/68hzm5mr.png)

第一次操作为：有一位同学领到尺码为 $26963$ 的服装，这样，图中所有的边都会断开。

下一次操作：第三对朋友即边 $(2,3)$ 的权变为 $40$。

下一次操作：询问同学 $4$ 的好友数量，因为没有任何存在的边，因此答案为 $1$。
 
## 数据范围
| 测试点编号 | $n$ | $q$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1,2$ | $\le 10$ | $\le 4 \times 10^5$ | 无 |
| $3$ | $\le 10^3$ | $\le 10^3$ | 无 |
| $4$ | $\le 10^5$ | $\le 4 \times 10^5$ | 没有操作 $3$ |
| $5,6$ | $\le 10^5$ | $\le 10^3$ | 无 |
| $7$ | $\le 10^5$ | $\le 4 \times 10^5$ | 没有操作 $1$ |
| $8,9,10$ | $\le 4 \times 10^5$ | $\le 4 \times 10^5$ | 无 |

用 $c_i$ 表示询问中同学领到服装尺码的大小，$e_i$ 表示修改后敏感值的大小。

对于 $100\%$ 的数据，$1 \le n,m,q,x_i,y_i \le 4  \times  10^5$，$1 \le k_i,c_i,e_i \le 1 \times 10^9$，$m\le \min\{\frac{n(n-1)}{2},4 \times 10^5\}$。

同时数据保证在任何时刻，所有对朋友关系之间的敏感值**互不相同**。

**请注意常数因子对时间和空间产生的影响。**


---

