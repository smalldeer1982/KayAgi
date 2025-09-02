---
title: "「FAOI-R2」A trip to Macao"
layout: "post"
diff: 提高+/省选-
pid: P10036
tag: ['动态规划 DP', '倍增', '2024', '洛谷原创', 'O2优化', '动态规划优化', '前缀和']
---
# 「FAOI-R2」A trip to Macao
## 题目背景

## 本题目背景仅供引出题意，无任何不良诱导。
## 出题人特别提醒：请勿在赌博非法地区模仿题目中的行为

这天，xhabc66 来到澳门旅游。一下飞机，他直奔赌场。

可是，今天的赌场格外热闹，不知发生了什么。

xhabc66 打开手机一看：啊，原来今天是 $12$ 月 $20$ 日！

因此，赌场在做活动！一年一度！机不可失！

xhabc66 径直走进了赌场。
## 题目描述

赌场贴出了如下规则（**你可以忽略没有加粗的内容**）：

1. 所有玩家在注册后方可进行游戏。
2. 活动期间，**新注册的玩家可从抽奖盒内拿走一枚筹码。抽奖盒内共 $m$ 种筹码，面值分别为 $a_1,a_2,\ldots,a_m$ 澳元（均为正整数）**，每种一个，保证公平。
3. 本赌场仅提供一种游戏：猜拳。游戏开始时，双方各下注相同数量（以 $1$ 澳元为单位）的筹码；若猜拳分出胜负，则胜者拿走所有下注。
4. 根据上一条可知，**玩家一次游戏中赢得的筹码（正整数）不得超过自身所携带的筹码**。
5. 公平游戏，严禁作弊，违者严惩。

xhabc66 注册后，**连赢数局（可以是 $0$ 局，但没有输过，也没有平局过）**，最终带着 $n$ 澳元走出了赌场。

出赌场后，xhabc66 突然好奇他是怎么赢到这么多钱的。然而，他不记得他每局下了多少注，不记得他一共玩了多少局，甚至不记得他开始时拿走的筹码是什么面值。

**他想知道：他有多少种不同的赢钱方法。**

**答案对 $10^9+7$ 取模。**

> 两种赢钱方法在满足以下任何一个条件时，xhabc66 都会认为它们不同：
>
> - 他某一局的下注金额不同；
> - 他玩的局数不同；
> - 他开始时拿走的筹码的面值不同。

### 形式化题意

求有多少个数列 $\{b_k\}$ 满足：

1. $\forall i \in [1,k],b_i \in \mathbb{N^*}$；
2. $\forall i \in [2,k],b_i \in [b_{i-1}+1,b_{i-1} \times 2]$；
3. $b_1 \in\{a_m\}$；
4. $b_k=n$。

数列的长度 $k$ 可以是任何**正整数**。

答案对 $10^9+7$ 取模。
## 输入格式

两行。

第一行，两个正整数，$n,m$。

第二行，$m$ 个**从小到大排列**的正整数，$a_1 \sim a_m$。
## 输出格式

一行一个正整数，表示答案。
## 样例

### 样例输入 #1
```
4 4
1 2 3 4
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
5 1
1
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
12345678 9
1 2 3 45 67 89 123 456 789
```
### 样例输出 #3
```
998899106
```
## 提示

样例 $1$ 解释：

```plain
1 2 3 4
1 2 4
2 3 4
2 4
3 4
4
```

样例 $2$ 解释：

```plain
1 2 3 4 5
1 2 3 5
1 2 4 5
```

----------

**本题采用捆绑测试。**

| Subtask 编号 | $m \le$ | $n \le$ | 分值 |
| :-: | :-: | :-: | :-: |
| $0$ | $3$ | $3$ | $20$ |
| $1$ | $10^5$ | $10^5$ | $40$ |
| $2$ | $10^6$ | $10^8$ | $40$ |

对于 $100\%$ 的数据，$1 \le m \le 10^6$，$1 \le a_1<a_2<\ldots<a_m \le n \le 10^8$，$m \le n$。

> **提示：** 请注意本题不同寻常的内存限制！


---

---
title: "[USACO24JAN] Walking in Manhattan G"
layout: "post"
diff: 提高+/省选-
pid: P10137
tag: ['倍增', 'USACO', '2024']
---
# [USACO24JAN] Walking in Manhattan G
## 题目描述

Farmer John 和他的 $Q$（$1\le Q\le 2\cdot 10^5$）头奶牛在曼哈顿度假，但奶牛们逃跑了，现在正在城市里自由走动！曼哈顿很大——大到它的 $N$（$1\le N\le 2\cdot 10^5$）条道路在 $x-y$ 平面上无限延伸，但简单的是，这些道路都完全水平或垂直。每条水平和垂直道路都可以用形式为 $y=c_i$ 或 $x=c_i$ 的方程表示，其中 $c_i$ 是 $0$ 到 $10^9$ 范围内的整数。

Farmer John 准确地知道每头奶牛从哪里开始行走，以及她们多久之前逃跑的。奶牛们很容易被预测，因此每头奶牛都是按照以下模式行走：

- 她们只会以每秒一个单位的速度向北（$+y$）或向东（$+x$    ）行走。
- 如果她们当前在一条道路上，她们会继续沿着道路的方向行走。
- 如果她们在两条道路的交叉口处，如果她们行走了偶数秒，则向北行走，否则向东行走。

给定曼哈顿的布局以及每头奶牛的信息，帮助 Farmer John 求出他的奶牛们现在在哪里！ 
## 输入格式

输入的第一行包含 $N$ 和 $Q$。

以下 $N$ 行描述道路。每条道路由方向（`H` 或 `V`）和坐标 $c_i$ 表示。输入保证道路各不相同。

以下 $Q$ 行描述奶牛。每头奶牛由三个整数 $(x_i,y_i,d_i)$ 表示，意味着她们在 $d_i$ 秒前从 $(x_i,y_i)$ 开始行走。输入保证 $(x_i,y_i)$ 位于某条道路上，且 $0\le x_i,y_i,d_i\le 10^9$。 
## 输出格式

输出 $Q$ 行，其中第 $i$ 行包含第 $i$ 头奶牛当前的位置。 
## 样例

### 样例输入 #1
```
4 5
V 7
H 4
H 5
V 6
6 3 10
6 4 10
6 5 10
6 6 10
100 4 10
```
### 样例输出 #1
```
14 5
7 13
6 15
6 16
110 4
```
## 提示

### 样例解释 1

前两头奶牛经过的路径如下：

$(6, 3) \to (6, 4) \to (7, 4) \to (7, 5) \to (8, 5) \to \ldots \to (14, 5)$  
$(6, 4) \to (6, 5) \to (7, 5) \to (7, 6) \to \ldots \to (7, 13)$

### 测试点性质

- 测试点 $2-4$：$N,Q,c_i,x_i,y_i,d_i\le 100$。
- 测试点 $5-9$：$N,Q\le 3000$。
- 测试点 $10-20$：没有额外限制。


---

---
title: "Genius Acm"
layout: "post"
diff: 提高+/省选-
pid: P10455
tag: ['贪心', '倍增']
---
# Genius Acm
## 题目描述

Advanced CPU Manufacturer (ACM) is one of the best CPU manufacturers in the world. 每天，该公司生产 $n$ 台 CPU 并销售到世界各地。

ACM 公司的质检部门会对生产出的 CPU 进行成组测试，对一组（若干个）CPU 进行测试的方法如下：

1. 随机从该组 CPU 中选取 $m$ 对（即 $2m$ 台），若总数不足 $2m$ 台，则选取尽量多对。

2. 对于每一对 CPU，测量它们之间的 Relative Performance Difference (RPD)，并把第 $i$ 对的 RPD 记为 $D_i$。RPD 的计算方法在后面给出。

3. 该组 CPU 的 Sqared Performance Difference (SPD） 由以下公式给出：

$SPD=\sum _i D^2_i$


4. 该组 CPU 通过质检，当且仅当 $SPD \le k,$ 其中 $k$ 是给定常数。

ACM 公司生产的 CPU 性能很好，而质检部门制定的标准更是过于严格。通常他们把 $n$ 台 CPU 作为一整组进行测试，这导致一些性能良好的 CPU 无法通过测试，生产部门对此颇有微词。作为质检部门的领导，小 S 在不更改质检测试流程的前提下，想出了这样一个主意：如果能够把 $n$ 台 CPU 恰当地分成连续的若干段，使得每段 CPU 都能够通过成组测试，就可以解决当下的问题。

现在，小 S 已经知道了 $n$ 台各自的性能表现 $P_1,\cdots ,P_n$，两台 CPU 的 RPD 被定义为它们性能表现的差的绝对值。请你帮忙计算一下，至少把这些 CPU 分成多少段，才能使得每一段都能通过成组测试。
## 输入格式

每个测试点包含多组数据，第一行整数 $T$ 给出数据组数。

对于每组数据，第一行三个整数 $n,m,k$，第二行 $n$ 个整数 $P_1,\cdots ,P_n$。
## 输出格式

对于每组数据，输出一个整表示答案。
## 样例

### 样例输入 #1
```
2
5 1 49
8 2 1 7 9
5 1 64
8 2 1 7 9
```
### 样例输出 #1
```
2
1
```
## 提示

对于 $20 \%$ 的数据，$1 \leq n \leq 10^2$ 。  
对于 $40 \%$ 的数据， $1 \leq n \leq 10^3$ 。  
对于另外 $10 \%$ 的数据，$k=0$ 。  
对于另外 $10 \%$ 的数据，$0 \leq k \leq 1$ 。  
对于另外 $10 \%$ 的数据， $m=1$ 。  
对于另外 $10 \%$ 的数据，$1 \leq m \leq 2$ 。  
对于 $90 \%$ 的数据，$0 \leq k \leq 10^{12}$ 。  
对于 $100 \%$ 的数据，$T \leq 12,1 \leq n, m \leq 5 \cdot 10^5, 0 \leq k \leq 10^{18}, 0 \leq P_i \leq 2^{20}$ 。  


---

---
title: "「CZOI-R1」三角形与树"
layout: "post"
diff: 提高+/省选-
pid: P10799
tag: ['数学', '倍增', '树状数组', 'O2优化', '最近公共祖先 LCA', '树链剖分']
---
# 「CZOI-R1」三角形与树
## 题目背景

CaiZi 讨厌三角形，但是他喜欢树。

2024.8.15 Update：增加了一组 hack 数据。
## 题目描述

给定一颗有 $n$ 个点的树，节点编号为 $1\sim n$，每个点有点权，开始时点 $i$ 的点权为 $a_i$。共有 $q$ 次操作。
1. 将点 $x$ 到点 $y$ 的简单路径上的点的点权**异或** $k$。
1. 判断能否在点 $x$ 到点 $y$ 的简单路径上选 $3$ 个**不同点**，并以这 $3$ 个点的点权为边长构成**三角形**。特别的，如果无法选出 $3$ 个点，也视为不能构成**三角形**。

点 $x$ 到点 $y$ 的简单路径：点 $x$ 到点 $y$ 不重复走过任何一条边的路径。其上的所有点为这条路径上所有的点，**包括**点 $x$ 和点 $y$。

**保证任何时刻不会有任何一个点的点权为 $0$。**
## 输入格式

第一行输入 $2$ 个整数 $n,q$，分别表示这棵树点的个数、操作的个数。

第二行输入 $n$ 个整数 $a_i$，表示开始时点 $i$ 的点权。

接下来 $n-1$ 行，每行输入 $2$ 个整数 $u,v$，表示这棵树的一条边。

接下来 $q$ 行，每行先输入 $1$ 个整数 $s$，表示操作类型。
- 若 $s=1$，则再输入 $3$ 个整数 $u,v,w$，表示一次修改操作。
- 若 $s=2$，则再输入 $2$ 个整数 $u,v$，表示一次询问操作。
## 输出格式

对于每次询问操作，若能满足条件输出 $1$，否则输出 $0$，无需空格或换行。
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 2
1 3
2 4
2 5
2 1 2
2 3 4
1 3 5 4
2 2 3
2 1 5
```
### 样例输出 #1
```
0110
```
## 提示

**【样例解释】**

第 $1$ 次操作时简单路径上的点权少于 $3$ 个。  
第 $2$ 次操作时简单路径上的点权分别为 $1,2,3,4$。  
第 $3$ 次操作后点 $1\sim n$ 的点权分别为 $5,6,7,4,1$。  
第 $4$ 次操作时简单路径上的点权分别为 $5,6,7$。  
第 $5$ 次操作时简单路径上的点权分别为 $1,5,6$。

**【数据范围】**

**本题采用捆绑测试**。
- Subtask #1（$8\text{ pts}$）：$n,q\le3\times10^3$。
- Subtask #2（$8\text{ pts}$）：保证这棵树是一朵菊花。
- Subtask #3（$20\text{ pts}$）：每次修改操作时 $x=y$。
- Subtask #4（$24\text{ pts}$）：保证这棵树是一条链。
- Subtask #5（$40\text{ pts}$）：无特殊性质。**依赖 Subtask #1 到 Subtask #4。**

对于 $100\%$ 的数据，$1\le u,v\le n\le10^5$，$1\le q\le10^5$，$s\in\{1,2\}$，$1\le a_i,w\le 2^{31}-1$。


---

---
title: "[NHSPC 2023] F. 恐怖的黑色魔物"
layout: "post"
diff: 提高+/省选-
pid: P11907
tag: ['倍增', '2023', 'Kruskal 重构树', 'O2优化', '台湾']
---
# [NHSPC 2023] F. 恐怖的黑色魔物
## 题目描述

G 公司最近用黑科技在某個神秘的地方建立了新的研發總部。這座研發總部的形狀是個長方體，內部共有 $F$ 層樓，每一層樓均有形狀大小相同且由 $M$ 列 $N$ 行組成的矩形房間。一個房間的位置以三個正整數 $(p, q, r)$ 表示，代表該房間位於研發總部 $p$ 樓的第 $q$ 列第 $r$ 行。

G 公司的員工均可以透過黑科技直接傳送至隔壁、樓下或樓上的房間。更明確地說，位於房間 $(p, q, r)$ 的 G 公司員工，

1. 當 $p > 1$ 時，可傳送至房間 $(p-1, q, r)$。
1. 當 $p < F$ 時，可傳送至房間 $(p+1, q, r)$。
1. 當 $q > 1$ 時，可傳送至房間 $(p, q-1, r)$。
1. 當 $q < M$ 時，可傳送至房間 $(p, q+1, r)$。
1. 當 $r > 1$ 時，可傳送至房間 $(p, q, r-1)$。
1. 當 $r < N$ 時，可傳送至房間 $(p, q, r+1)$。

G 公司為了節省員工的用餐休息時間，在其中的 $R$ 個房間開設了餐廳，方便員工在研發總部內直接用餐。但餐廳的食物會滋生一種恐怖的黑色魔物，有一部分的 G 公司員工非常害怕這種恐怖的黑色魔物，因此不敢在這些餐廳用餐。

你的上司 K 先生特別害怕這種恐怖的黑色魔物。他總認為這些恐怖的黑色魔物，也能透過黑科技，在研發總部裡自由穿梭。他定義了「黑色恐怖距離」：若一個房間至少須使用 $d$ 次黑科技傳送，才能抵達餐廳，則該房間的黑色恐怖距離就是 $d$。對 K 先生來說，黑色恐怖距離越小就越恐怖，因次他每次在研發總部內移動時，都會計算該如何使用黑科技，才能讓途中經過的房間，最小的黑色恐怖距離最大。作為 K 先生下屬的你，打算撰寫一個程式，幫助 K 先生快速算出在最不恐怖的路徑上，所經過的房間裡黑色恐怖距離的最小值。
## 输入格式

> $F$ $M$ $N$   
> $R$   
> $p_1$ $q_1$ $r_1$   
> $p_2$ $q_2$ $r_2$   
> $\vdots$   
> $p_R$ $q_R$ $r_R$   
> $Q$   
> $a_1$ $b_1$ $c_1$ $x_1$ $y_1$ $z_1$   
> $a_2$ $b_2$ $c_2$ $x_2$ $y_2$ $z_2$   
> $\vdots$   
> $a_Q$ $b_Q$ $c_Q$ $x_Q$ $y_Q$ $z_Q$

* $F$ 代表 G 公司研發總部的樓層數。
* $M$ 代表 G 公司研發總部的列數。
* $N$ 代表 G 公司研發總部的行數。
* $R$ 代表 G 公司研發總部的餐廳數。
* $(p_i, q_i, r_i)$ 代表 G 公司研發總部內第 $i$ 間餐廳的位置。
* $Q$ 代表 K 先生計畫移動的次數。
* $(a_i, b_i, c_i)$ 代表 K 先生計畫第 $i$ 次移動的起點。
* $(x_i, y_i, z_i)$ 代表 K 先生計畫第 $i$ 次移動的終點。
## 输出格式

> $d_1^*$   
> $d_2^*$   
> $\vdots$   
> $d_Q^*$

* $d_i^*$ 代表 K 先生第 $i$ 次移動時，所有可能的路徑中，最小黑色恐怖距離的最大值。
## 样例

### 样例输入 #1
```
3 3 3
3
1 1 1
2 2 2
3 3 3
4
1 3 3 3 1 1
1 2 2 3 2 2
1 2 3 1 2 3
1 1 1 3 3 3
```
### 样例输出 #1
```
2
1
2
0
```
### 样例输入 #2
```
1 1 3
1
1 1 2
1
1 1 1 1 1 3
```
### 样例输出 #2
```
0
```
## 提示

### 測資限制

* $1 \le F \le 2\times10^5$。
* $1 \le M \le 2\times10^5$。
* $1 \le N \le 2\times10^5$。
* $1 \le FMN \le 2\times10^5$。
* $1 \le R \le FMN$。
* $1 \le p_i \le F$。
* $1 \le q_i \le M$。
* $1 \le r_i \le N$。
* $1 \le Q \le 2\times10^5$。
* $1 \le a_i \le F$。
* $1 \le b_i \le M$。
* $1 \le c_i \le N$。
* $1 \le x_i \le F$。
* $1 \le y_i \le M$。
* $1 \le z_i \le N$。
* 對任意 $i, j \in \{1, 2, \ldots, R\}$，若 $i \ne j$，則 $(p_i, q_i, r_i) \ne (p_j, q_j, r_j)$。
* 輸入的數皆為整數。

### 評分說明

本題共有五組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | $6$ | $F = R = 1, MN \le 100, Q \le 100$ |
| 2 | $21$ | 對任意 $i \in \{1, 2, \ldots, Q\}$，均有 $(a_i, b_i, c_i) = (x_i, y_i, z_i)$ |
| 3 | $4$ | $FMN \le 3000$ |
| 4 | $25$ | $Q = 1$ |
| 5 | $44$ | 無額外限制 |


---

---
title: "【MX-X10-T4】[LSOT-4] Fragment of Memories"
layout: "post"
diff: 提高+/省选-
pid: P12008
tag: ['倍增', '双指针 two-pointer', '梦熊比赛']
---
# 【MX-X10-T4】[LSOT-4] Fragment of Memories
## 题目背景

甜与苦的一体两面。
## 题目描述

苏珊在昏迷前度过了 $m$ 天。从第一天起，苏珊会有一个基准记忆 $x$，第 $i$（$1\le i\le m$）天的记忆为 $x+i-1$。这 $m$ 天的记忆按顺序依次拼接，得到了一串长为 $m$ 的记忆。

在梦境中，这段记忆被按顺序重复了 $k$ 遍。在这之后，为了唤醒苏珊，露薇娅进入了梦境，记忆被插入了一些不属于苏珊的记忆，最终变为了一个长度为 $n$ 的序列 $a_1, \ldots, a_n$。

现在给你这个序列和 $k$。露薇娅不知道一开始的基准记忆 $x$ 是多少，所以他想知道对于所有的 $1\le x\le V$，$m$ 的值最大可能是多少。若对于一个 $x$ 不存在合法的记忆，输出 $0$。
## 输入格式

第一行，三个整数 $n,k,V$，意义如题面所示。

第二行，$n$ 个整数 $a_1, \ldots, a_n$，表示最终的序列。
## 输出格式

仅一行，$V$ 个整数，第 $i$ 个整数表示当 $x=i$ 时最大的可能的 $m$。
## 样例

### 样例输入 #1
```
9 2 5
2 1 3 4 5 2 3 2 4
```
### 样例输出 #1
```
0 3 2 1 0
```
### 样例输入 #2
```
30 3 8
3 4 5 5 1 2 8 4 5 3 6 4 5 7 5 6 6 7 6 8 7 1 8 2 3 2 7 3 7 8
```
### 样例输出 #2
```
0 2 1 2 1 2 2 1
```
## 提示

**【样例解释 #1】**

当 $x=2$、$m=3$ 时，苏珊的记忆是 `2 3 4`。重复了 $k=2$ 次变成了 `2 3 4 2 3 4`。在位置 $1$ 和位置 $2$ 中间、位置 $3$ 和位置 $4$ 中间、位置 $5$ 和位置 $6$ 中间分别插入了一个数后变成了原序列。

类似地，`2`、`3`、`4`、`2 3`、`3 4` 都是符合要求的记忆。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（13 分）：$n\le 100$。
- 子任务 2（21 分）：$n\le 3000$。
- 子任务 3（23 分）：$n\le 3\times10^4$。
- 子任务 4（25 分）：$n\le 5\times10^5$。
- 子任务 5（18 分）：无特殊性质。

对于全部的数据，$1\le k\le n\le 2\times 10^6$，$1\le a_i\le V\le n$。


---

---
title: "「RiOI-6」flos"
layout: "post"
diff: 提高+/省选-
pid: P12393
tag: ['倍增', '洛谷原创', 'O2优化', '可持久化线段树', '洛谷比赛']
---
# 「RiOI-6」flos
## 题目背景

![](bilibili:BV1Gi4y1g77Q)

即使是像萝卜这样不起眼的小木头，也有被人喜欢的日子呢！

帽子的表白真是突如其来，小萝卜拼尽全力才战胜了自己上扬的嘴角，没有在上课划水的时候笑出来。

今年的 2.14，终于！可以！两个人过了！
## 题目描述

帽子要摘一些小萝卜最喜欢的花装点礼物。

小萝卜最喜欢的花长在一棵根为 $1$ 的树上，其中每个节点都有一朵花。当帽子从点 $u$ 开始摘花时，花的芳香度 $w_v$ 定义为 $\operatorname{dis}(u,v)$，也即 $u$ 到 $v$ 的最短距离。帽子只能摘下一朵花。

帽子只有 $t$ 秒的时间。具体的，他从 $u$ 开始沿着边移动，当他向上爬一条边（即**远离根**）时消耗 $1$ 单位时间，向下滑一条边（即**接近根**）时不消耗时间，全过程中剩余时间不能少于 $0$。

小萝卜有 $q$ 个问题，每次形如：帽子从点 $x_i$ 出发，有 $t_i$ 时间，摘的花的最大芳香度是多少。各个询问相互独立。

特别的，有时候小萝卜会在帽子摘完花后才会问下一个问题，所以在一些测试点中你需要强制在线。
## 输入格式

第一行两个正整数 $n,q,d$，表示树的节点个数、询问个数、与是否强制在线。

接下来 $n-1$ 行，每行两个正整数 $u_i,v_i$，表示树上 $u_i,v_i$ 之间有一条边。

接下来 $q$ 行，每行两个非负整数 $x_i,t_i$，表示一组询问。特别的，若 $d=1$，设上一组询问的答案为 $ans$（第一组询问为 $0$），你需要将 $x_i,t_i$ 异或上 $ans$ 得到真实询问。
## 输出格式

$q$ 行每行一个非负整数，表示每个询问的答案。
## 样例

### 样例输入 #1
```
5 3 0
1 2
1 3
3 4
4 5
1 2
1 4
2 2

```
### 样例输出 #1
```
2
3
3

```
### 样例输入 #2
```
10 5 1
1 2
1 3
3 4
2 5
4 6
4 7
7 8
8 9
9 10
1 0
4 2
2 4
2 1
8 0

```
### 样例输出 #2
```
0
4
3
2
8

```
## 提示

#### 【样例解释】

对于样例 $1$，三个询问分别如下：

- 从 $1$ 出发，体力值为 $2$。此时能摘下的其中一朵芳香度最大的花是 $4$，芳香度为 $2$。帽子可以向上爬 $2$ 条边到达 $4$。
- 从 $1$ 出发，体力值为 $4$。此时能摘下的其中一朵芳香度最大的花是 $5$，芳香度为 $3$。帽子可以向上爬 $3$ 条边到达 $5$。
- 从 $2$ 出发，体力值为 $2$。此时能摘下的其中一朵芳香度最大的花是 $4$，芳香度为 $3$。帽子可以先向下滑一条边到 $1$，再向上爬 $2$ 条边到达 $4$。

对于样例 $2$，暂时不能给你一个明确的答复。

#### 【数据范围】

**本题开启捆绑测试。**

|子任务|分数|$n,q\le$|$d=$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$20$|$10^3$|$0$||
|$2$|$10$|$2\times10^5$|$0$|$\forall i,u_i+1=v_i$|
|$3$|$20$|$2\times10^5$|$0$|$\forall i,t_i=n$|
|$4$|$20$|$2\times10^5$|$0$||
|$5$|$30$|$2\times10^5$|$1$||

对于 $100\%$ 的数据，$1\le n,q\le 2\times10^5,d\in\{0,1\},1\le x_i\le n,0\le t_i\le n$。


---

---
title: "[UTS 2024] Matrix"
layout: "post"
diff: 提高+/省选-
pid: P12561
tag: ['递推', '倍增', '单调队列', '2024', 'UOI（乌克兰）']
---
# [UTS 2024] Matrix
## 题目描述

You are given a matrix of size $n \times m$ consisting of elements $a_{i,j}$. 

We call a **triangle** on the matrix of size $k$ starting at point $(x;y)$ a set of points that can be reached from $(x;y)$ in no more than $k$ steps going either up or right. 

You are asked to find for each $(x;y)$ $(k \le x \le n, 1 \le y \le m-k+1)$ the following values:

- The maximal value in the triangle of size $k$ starting at point $(x;y)$;
- The number of occurrences of the maximal value in that triangle.
## 输入格式

The first line contains three integers $n$, $m$, and $k$ $(1 \le n,m \le 2\,000, 1 \le k \le \min(n,m))$ --- dimensions of the matrix and the size of the triangle.

The following $n$ lines contain $m$ integers $a_{i,j}$ $(0 \le a_{i,j} \le 10^6)$ --- description of the matrix.
## 输出格式

Print two matrices of size $(n-k+1)\times(m-k+1)$. 

The first matrix in position $(i;j)$ should contain the maximal value of a triangle of size $k$ starting at $(i+k-1;j)$.

The second matrix in position $(i;j)$ should contain the number of occurrences of the maximal value in the triangle of size $k$ starting at $(i+k-1;j)$.
## 样例

### 样例输入 #1
```
4 4 2
1 2 6 14
12 3 13 5
11 4 7 8
10 16 9 15
```
### 样例输出 #1
```
12 13 13 
12 7 13 
16 16 15 
1 1 1 
1 1 1 
1 1 1 
```
## 提示

- ($5$ points) $n,m \le 20$;
- ($10$ points) $n,m \le 100$;
- ($30$ points) $a_{i,j} \le 1$;
- ($35$ points) $n,m \le 1\,000$;
- ($20$ points) no additional restrictions.


---

---
title: "[UOI 2023] An Array and Range Additions"
layout: "post"
diff: 提高+/省选-
pid: P12568
tag: ['倍增', '2023', 'UOI（乌克兰）']
---
# [UOI 2023] An Array and Range Additions
## 题目描述

Given an array of integers $a$ of length $n$.

You can modify the array using the **addition operation**. To apply the **addition operation**, you need to perform three sequential actions:

- Choose any integer $x$.
- Choose any subarray $[l;r]$ of the array.
- Add $x$ to each element of the chosen subarray (perform the assignment operation $a_i \leftarrow (a_i+x)$ for $l \le i\le r$).

Find the minimum number of **addition operations** required to make all elements of the array $a$ pairwise distinct.
## 输入格式

The first line contains a single integer $n$ ($1 \le n \le 2 \cdot 10^5$) --- the length of the array.

The second line contains $n$ integers $a_1,a_2,\ldots,a_n$ ($1 \le a_i \le 10^9$) --- the elements of the array.
## 输出格式

Output a single integer --- the minimum number of **addition operations** required to make all elements of the array $a$ pairwise distinct.
## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
5
2 3 2 3 2
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
9
2 3 1 1 3 2 1 3 3
```
### 样例输出 #3
```
2
```
## 提示

In the first example, all elements of the array $a$ are pairwise distinct.

In the second example, after applying two \textit{addition operations} with parameters $x=-3$, $l=1$, $r=2$ and $x=-1$, $l=1$, $r=3$, the array $a$ becomes equal to $[-2,-1,1,3,2]$.

In the third example, after applying two \textit{addition operations} with parameters $x=-3$, $l=4$, $r=8$ and $x=-10$, $l=7$, $r=9$, the array $a$ becomes equal to $[2,3,1,-2,0,-1,-12,-10,-7]$.

### Scoring

- ($9$ points): all elements of the array $a$ are equal to $1$.
- ($15$ points): $1 \le a_i \le 2$ for $1 \le i \le n$; $a_i \le a_{i+1}$ for $1 \le i < n$.
- ($14$ points): $n \le 8$.
- ($17$ points): $a_1 = a_n$.
- ($12$ points): $n \le 2000$.
- ($12$ points): $1 \le a_i \le 100$ for $1\le i\le n$.
- ($21$ points): no additional constraints.


---

---
title: "斐波那契公约数"
layout: "post"
diff: 提高+/省选-
pid: P1306
tag: ['数学', '倍增', '线性数据结构', '递归', '斐波那契数列']
---
# 斐波那契公约数
## 题目描述

对于 Fibonacci 数列：

$$ f_i = \begin{cases}
  [i = 1]               & i \leq 1 \\
  f_{i - 1} + f_{i - 2} & i \gt 1
\end{cases}$$

请求出 $f_n$ 与 $f_m$ 的最大公约数，即 $\gcd(f_n, f_m)$。
## 输入格式

一行两个正整数 $n$ 和 $m$ 。
## 输出格式

输出一行一个整数，代表 $f_n$ 和 $f_m$ 的最大公约数。答案请对 $10^8$ 取模。
## 样例

### 样例输入 #1
```
4 7
```
### 样例输出 #1
```
1
```
## 提示

#### 数据规模与约定

- 对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 10^9$。


---

---
title: "高级打字机"
layout: "post"
diff: 提高+/省选-
pid: P1383
tag: ['倍增', '福建省历届夏令营', '可持久化线段树', '可持久化']
---
# 高级打字机
## 题目描述

早苗入手了最新的高级打字机。最新款自然有着与以往不同的功能，那就是它具备撤销功能，厉害吧。

请为这种高级打字机设计一个程序，支持如下 $3$ 种操作：

1. `T x`：Type 操作，表示在文章末尾打下一个小写字母 $x$。
2. `U x`：Undo 操作，表示撤销最后的 $x$ 次修改操作。
3. `Q x`：Query 操作，表示询问当前文章中第 $x$ 个字母并输出。请注意 Query 操作并不算修改操作。

文章一开始可以视为空串。
## 输入格式

第 $1$ 行：一个整数 $n$，表示操作数量。

以下 $n$ 行，每行一个命令。保证输入的命令合法。
## 输出格式

每行输出一个字母，表示 Query 操作的答案。


## 样例

### 样例输入 #1
```
7
T a
T b
T c
Q 2
U 2
T c
Q 2

```
### 样例输出 #1
```
b
c

```
## 提示

对于前 $20\%$ 的数据，$n\le 200$。

对于前 $50\%$ 的数据，保证 Undo 操作不会撤销 Undo 操作。

对于 $100\%$ 的数据，$n\le 10^5$。


---

---
title: "跑路"
layout: "post"
diff: 提高+/省选-
pid: P1613
tag: ['动态规划 DP', '倍增', '最短路']
---
# 跑路
## 题目描述

小 A 的工作不仅繁琐，更有苛刻的规定，要求小 A 每天早上在 $6:00$ 之前到达公司，否则这个月工资清零。可是小 A 偏偏又有赖床的坏毛病。于是为了保住自己的工资，小 A 买了一个空间跑路器，每秒钟可以跑 $2^k$ 千米（$k$ 是任意自然数）。当然，这个机器是用 `longint` 存的，所以总跑路长度不能超过 `maxlongint` 千米。小 A 的家到公司的路可以看做一个有向图，小 A 家为点 $1$，公司为点 $n$，每条边长度均为一千米。小 A 想每天能醒地尽量晚，所以让你帮他算算，他最少需要几秒才能到公司。数据保证 $1$ 到 $n$ 至少有一条路径。
## 输入格式

第一行两个整数 $n,m$，表示点的个数和边的个数。

接下来 $m$ 行每行两个数字 $u,v$，表示一条 $u$ 到 $v$ 的边。
## 输出格式

一行一个数字，表示到公司的最少秒数。
## 样例

### 样例输入 #1
```
4 4
1 1
1 2
2 3
3 4

```
### 样例输出 #1
```
1
```
## 提示

**【样例解释】**

$1 \to 1 \to 2 \to 3 \to 4$，总路径长度为 $4$ 千米，直接使用一次跑路器即可。

**【数据范围】**

$50\%$ 的数据满足最优解路径长度 $\leq 1000$；

$100\%$ 的数据满足 $2\leq n \leq 50$，$m \leq 10 ^ 4$，最优解路径长度 $\leq$ `maxlongint`。


---

---
title: "刷题比赛"
layout: "post"
diff: 提高+/省选-
pid: P1707
tag: ['递推', '倍增', '矩阵运算', '洛谷原创', '矩阵乘法', '线性递推']
---
# 刷题比赛
## 题目背景

nodgd 是一个喜欢写程序的同学，前不久洛谷 OJ 横空出世，nodgd 同学当然第一时间来到洛谷 OJ 刷题。   
于是发生了一系列有趣的事情，他就打算用这些事情来出题恶心大家……

## 题目描述

洛谷OJ当然算是好地方，nodgd 同学打算和朋友分享一下。于是他就拉上了他的朋友 Ciocio 和 Nicole 两位同学一起刷题。喜欢比赛的他们当然不放过这样一次刷题比赛的机会！

在第 $1$ 天 nodgd,Coicoi,Nicole 都只做了 $1$ 道题。

在第 $2$ 天 nodgd,Coicoi,Nicole 都只做了 $3$ 道题。

他们都有着严格的刷题规则，并且会在每一天都很遵守规则的刷一定量的题。

1、nodgd 同学第 $k+2$ 天刷题数量    
$$a_{k+2}=pa_{k+1}+qa_k+b_{k+1}+c_{k+1}+rk^2+tk+1$$

2、Ciocio 同学第 $k+2$ 天刷题数量      
$$b_{k+2}=ub_{k+1}+vb_k+a_{k+1}+c_{k+1}+w^k$$

3、Nicole 同学第 $k+2$ 天刷题数量    
$$c_{k+2} = xc_{k+1}+yc_k + a_{k+1} + b_{k+1} + z^k+k+2$$

（以上的字母 $p,q,r,t,u,v,w,x,y,z$ 都是给定的常数，并保证是正整数）

于是他们开始了长时间的刷题比赛！一共进行了 $n$ 天

但是时间是可贵的，nodgd 想快速知道第 $n$ 天每个人的刷题数量。  
不过 nodgd 同学还有大量的数学竞赛题、物理竞赛题、英语竞赛题、美术竞赛题、体育竞赛题…… 要做，就拜托你来帮他算算了。

由于结果很大，输出结果 $\bmod \space m$ 的值即可。

## 输入格式

第一行两个正整数 $n,m$。

第二行四个正整数 $p,q,r,t$。

第三行三个正整数 $u,v,w$。

第四行三个正整数 $x,y,z$。

## 输出格式

共三行，每行一个名字 + 一个空格 + 一个整数。  
依次是 nodgd,Ciocio,Nicole 和他们在第 $n$ 天刷题数量 $\bmod \space m$ 的值。

## 样例

### 样例输入 #1
```
4 10007
2 1 1 1
2 2 3
1 1 2
```
### 样例输出 #1
```
nodgd 74
Ciocio 80
Nicole 59
```
## 提示

对于 $100\%$ 的数据，$4\le n \le 10^{16}$，$2\le m \le 10^{16}$，$1\le p,q,r,t,u,v,w,x,y,z \le 100$。


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
title: "Sam数"
layout: "post"
diff: 提高+/省选-
pid: P2106
tag: ['动态规划 DP', '数学', '倍增', '数位 DP', '矩阵加速']
---
# Sam数
## 题目描述

小 Z 最近发现了一种非常有趣的数，他将这种数称之为 Sam 数。Sam 数具有以下特征：相邻两位的数字之差不超过 $2$。小 Z 还将 Sam 数按位数进行了分类，他将一个 $k$ 位 Sam 数称之为 $k$ 阶 Sam 数。但不幸的是小 Z 发现他数不清第 $k$ 阶的 Sam 数一共有多少个，这个时候机智的他想到了向你求助。
## 输入格式

输入共一行一个整数 $k$，含义见题面。
## 输出格式

一行一个整数 $ans$，表示 $k$ 阶的 Sam 数的个数。

由于第 $k$ 阶 Sam 数非常多，你只需要输出 $ans\bmod 1000000007$。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
867
```
## 提示

**【数据规模和约定】**

对于 $30\%$ 的数据，$1\le k\le10^6$。

对于 $60\%$ 的数据，$1\le k\le 10^{12}$。

对于 $100\%$ 的数据，$1\le k\le10^{18}$。


---

---
title: "[POI 2010] ZAB-Frog"
layout: "post"
diff: 提高+/省选-
pid: P3509
tag: ['动态规划 DP', '2010', '倍增', 'POI（波兰）', '深度优先搜索 DFS']
---
# [POI 2010] ZAB-Frog
## 题目描述

On the bed of one particularly long and straight Byteotian brook there lie $n$ rocks jutting above the water level. Their distances from the brook's spring are $p_1 < p_2 < \cdots < p_n$ respectively. A small frog sitting on one of these is about to begin its leaping training. Each time the frog leaps to the rock that is the -th closest to the one it is sitting on. Specifically, if the frog is sitting on the rock at position $p_i$, then it will leap onto such $p_j$ that:
$$
|\{ p_a : |p _ a - p _ i| < |p_j - p_i| \}| \le k \text{ and } |\{ p_a : |p _ a - p _ i| \le |p_j - p_i| \}| > k
$$
If $p_j$ is not unique, then the frog chooses among them the rock that is closest to the spring. On which rock the frog will be sitting after $m$ leaps depending on the rock is started from?
## 输入格式

The first line of the standard input holds three integers, $n$, $k$ and $m$ ($1 \le k < n \le 1 \, 000 \, 000, 1 \le m \le 10^{18}$), separated by single spaces, that denote respectively: the number of rocks, the parameter $k$, and the number of intended leaps. The second line holds $n$ integers $p_j$ ($1 \le p_1 < p_2 < \cdots < p_n \le 10^{18}$), separated by single spaces, that denote the positions of successive rocks on the bed of the brook.
## 输出格式

Your program should print a single line on the standard output, with $n$ integers $r_1, r_2, \cdots, r_n$ from the interval $[1, n]$ in it, separated by single spaces. The number $r_i$ denotes the number of the rock that the frog ends on after making $m$ leaps starting from the rock no. $i$ (in the input order).
## 样例

### 样例输入 #1
```
5 2 4
1 2 4 7 10
```
### 样例输出 #1
```
1 1 3 1 1
```
## 提示

### 样例 #1 解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/yyilx2mp.png)

The figure presents where the frog leaps to (in a single leap) from each and every rock.
## 题目翻译

有 $n$ 个点，升序给出每个点到起点的距离。有编号为 $1 \sim n$ 的 $n$ 只青蛙分别在第 $1 \sim n$ 个点上，每次它们会跳到距离自己第 $k$ 近的点上。

如果有相同距离的点，就跳到下标更小的点上。

求跳 $m$ 次之后，第 $i$ 只的青蛙在哪个点上。

输入共一行三个整数：代表 $n, k, m$。

输出共一行 $n$ 个整数，代表每只青蛙最终所处在的点。


---

---
title: "[APIO2009] 会议中心"
layout: "post"
diff: 提高+/省选-
pid: P3626
tag: ['贪心', '2009', '线段树', '倍增', 'APIO', '排序', '前缀和']
---
# [APIO2009] 会议中心
## 题目描述

Siruseri 政府建造了一座新的会议中心。许多公司对租借会议中心的会堂很 感兴趣，他们希望能够在里面举行会议。

对于一个客户而言，仅当在开会时能够独自占用整个会堂，他才会租借会堂。 会议中心的销售主管认为：最好的策略应该是将会堂租借给尽可能多的客户。

显 然，有可能存在不止一种满足要求的策略。 例如下面的例子。总共有 4 个公司。他们对租借会堂发出了请求，并提出了 他们所需占用会堂的起止日期（如下表所示）。

```cpp
       开始日期 结束日期 
 公司1    4        9 
 公司2    9        11 
 公司3    13       19 
 公司4    10       17 
```
上例中，最多将会堂租借给两家公司。租借策略分别是租给公司 1 和公司 3， 或是公司 2 和公司 3，也可以是公司 1 和公司 4。注意会议中心一天最多租借给 一个公司，所以公司 1 和公司 2 不能同时租借会议中心，因为他们在第九天重合 了。

销售主管为了公平起见，决定按照如下的程序来确定选择何种租借策略：首 先，将租借给客户数量最多的策略作为候选，将所有的公司按照他们发出请求的 顺序编号。对于候选策略，将策略中的每家公司的编号按升序排列。最后，选出 其中字典序最小1的候选策略作为最终的策略。

例中，会堂最终将被租借给公司 1 和公司 3：3 个候选策略是 {(1,3),(2,3),(1,4)}。而在字典序中(1,3)<(1,4)<(2,3)。 你的任务是帮助销售主管确定应该将会堂租借给哪些公司。

## 输入格式

输入的第一行有一个整数 N，表示发出租借会堂申请的公司的个数。第 2 到 第 N+1 行每行有 2 个整数。第 i+1 行的整数表示第 i 家公司申请租借的起始和终 止日期。对于每个公司的申请，起始日期为不小于 1 的整数，终止日期为不大于 10^9 的整数。

## 输出格式

输出的第一行应有一个整数 M，表示最多可以租借给多少家公司。第二行应列出 M 个数，表示最终将会堂租借给哪些公司。

## 样例

### 样例输入 #1
```
4 
4 9
9 11 
13 19 
10 17
```
### 样例输出 #1
```
2
1 3
```
## 提示

对于 50%的输入，N≤3000。

在所有输入中，N≤200000。



---

---
title: "[SHOI2012] 魔法树"
layout: "post"
diff: 提高+/省选-
pid: P3833
tag: ['2012', '线段树', '倍增', '各省省选', '上海', '最近公共祖先 LCA', '树链剖分']
---
# [SHOI2012] 魔法树
## 题目背景

SHOI2012 D2T3

## 题目描述

Harry Potter 新学了一种魔法：可以改变树上的果子个数。满心欢喜的他找到了一个巨大的果树，来试验他的新法术。

这棵果树共有 $N$ 个节点，其中节点 $0$ 是根节点，每个节点 $u$ 的父亲记为 $fa[u]$，保证有 $fa[u] < u$ 。初始时，这棵果树上的果子都被 Dumbledore 用魔法清除掉了，所以这个果树的每个节点上都没有果子（即 $0$ 个果子）。

不幸的是，Harry 的法术学得不到位，只能对树上一段路径的节点上的果子个数统一增加一定的数量。也就是说，Harry 的魔法可以这样描述：`A u v d` 。表示将点 $u$ 和 $v$ 之间的路径上的所有节点的果子个数都加上 $d$。

接下来，为了方便检验 Harry 的魔法是否成功，你需要告诉他在释放魔法的过程中的一些有关果树的信息：`Q u`。表示当前果树中，以点 $u$ 为根的子树中，总共有多少个果子？

## 输入格式

第一行一个正整数 $N (1 \leq N \leq 100000)$，表示果树的节点总数，节点以 $0,1,\dots,N - 1$ 标号，$0$ 一定代表根节点。

接下来 $N - 1$ 行，每行两个整数 $a,b (0 \leq a < b < N)$，表示 $a$ 是 $b$ 的父亲。

接下来是一个正整数 $Q(1 \leq Q \leq 100000)$，表示共有 $Q$ 次操作。

后面跟着 $Q$ 行，每行是以下两种中的一种：

1. `A u v d`，表示将 $u$ 到 $v$ 的路径上的所有节点的果子数加上 $d$。保证 $0 \leq u,v < N,0 < d < 100000$

2. `Q u`，表示询问以 $u$ 为根的子树中的总果子数，注意是包括 $u$ 本身的。

## 输出格式

对于所有的 `Q` 操作，依次输出询问的答案，每行一个。答案可能会超过 $2^{32}$ ，但不会超过 $10^{15}$ 。

## 样例

### 样例输入 #1
```
4
0 1
1 2
2 3
4
A 1 3 1
Q 0
Q 1
Q 2
```
### 样例输出 #1
```
3
3
2
```


---

---
title: "[SCOI2015] 国旗计划"
layout: "post"
diff: 提高+/省选-
pid: P4155
tag: ['贪心', '2015', '四川', '倍增', '二分', '排序']
---
# [SCOI2015] 国旗计划
## 题目描述

A 国正在开展一项伟大的计划 —— 国旗计划。这项计划的内容是边防战士手举国旗环绕边境线奔袭一圈。这项计划需要多名边防战士以接力的形式共同完成，为此，国土安全局已经挑选了 $N$ 名优秀的边防战士作为这项计划的候选人。


A 国幅员辽阔，边境线上设有 $M$ 个边防站，顺时针编号 $1$ 至 $M$。每名边防战士常驻两个边防站，并且善于在这两个边防站之间长途奔袭，我们称这两个边防站之间的路程是这个边防战士的奔袭区间。$N$ 名边防战士都是精心挑选的，身体素质极佳，所以每名边防战士的奔袭区间都不会被其他边防战士的奔袭区间所包含。


现在，国土安全局局长希望知道，至少需要多少名边防战士，才能使得他们的奔袭区间覆盖全部的边境线，从而顺利地完成国旗计划。不仅如此，安全局局长还希望知道更详细的信息：对于每一名边防战士，在他必须参加国旗计划的前提下，至少需要多少名边防战士才能覆盖全部边境线，从而顺利地完成国旗计划。

## 输入格式

第一行，包含两个正整数 $N,M$，分别表示边防战士数量和边防站数量。


随后 $N$ 行，每行包含两个正整数。其中第 $i$ 行包含的两个正整数 $C_i$、$D_i$ 分别表示 $i$ 号边防战士常驻的两个边防站编号，$C_i$ 号边防站沿顺时针方向至 $D_i$ 号边防站力他的奔袭区间。数据保证整个边境线都是可被覆盖的。

## 输出格式

输出数据仅 $1$ 行，需要包含 $N$ 个正整数。其中，第 $j$ 个正整数表示 $j$ 号边防战士必须参加的前提下至少需要多少名边防战士才能顺利地完成国旗计划。

## 样例

### 样例输入 #1
```
4 8
2 5
4 7
6 1
7 3
```
### 样例输出 #1
```
3 3 4 3
```
## 提示

$N\leqslant 2×10^5,M<10^9,1\leqslant C_i,D_i\leqslant M$。



---

---
title: "旅行"
layout: "post"
diff: 提高+/省选-
pid: P5557
tag: ['倍增', 'O2优化']
---
# 旅行
## 题目背景

> 光阴似箭。如烟火，只许刹那芳华；似九月，夜幕昙花一闪而散。
> 辉煌已逝。步征夫，辗转行路之洼；立孤叶，夙夜漂泊四海之旅。
——《旅行》
## 题目描述

行走与尘世之间，charine 是一位旅行家。踏入城市的喧嚣，他开始了辗转于城市的旅行……

这是一个具有 $n$ 个城市的城市群，每两个点可以互相到达。现代交通技术飞速发展，大大缩短了航程，距离已显得不在那么重要：

城市群里，道路已经没有长长短短之说，**每一条道路由于时间的不断缩短都可视为等长**，把它们以一个单位计量，可以容易的视其为 $1$ zm。

正是由于城市群的庞大，未脱离于城市的 charine 亦有牵绊，这使他不可能无限遨游于这宽广的城市群里。这使 charine 极为郁闷，他决定选择尽可能短的时间走遍整个城市群。

具体而言，charine 不会因为在某个城市里而耽误他遨游天下的决心，他走访的每一个城市，都会在极短的时间里将其印在脑海里。

charine 的行走速度不会很快，这意味着他只能在一个单位时间内行走 $1$ zm。

这却使他更着急着找到足够旅行更多城市的方法……

为了去除他在每一个岔路口的犹豫时间，charine 亦是聪明的提前了他的旅行计划。对于走出城市 $i$ 的那几个路口，charine 给这个城市定义了一个通路 $a_i$，他相信自己的计划，就一定会踩着通路向前走。**走访完城市 $i$ 的他会给自己的下一个城市目标定为 $a_i$**。

处理完这些以后，他便是再也找不出继续缩短时间的办法了，于是他开始执行了自己的旅行计划。

charine 有 $m$ 个季度都有出行的机会，对于第 $i$ 个季度，charine 将会从 $S_i$ 出发，他告诉你，他会准备 $t$ 单位时间去旅行。

为了能及时的看到他的身影，你要知道，**$t$ 单位时间后 charine 会出现在哪个城市……**

**注意“道路”与“通路”的定义问题。**
## 输入格式

输入数据的第一行为一个正整数 $n$，表示城市数。

第二行 $n$ 个整数，第 $i$ 个整数表示 $a_i$。

接下来一个整数 $m$，表示 $m$ 个季度。

第 $4$ 到 $m+3$ 行，描述一次旅行，每行 $3$ 个整数，$S_i,t_1,t_2$，描述见题面，其中，$t=t_1^{t_2}$。
## 输出格式

对于每个季度输出一行，表示答案。
## 样例

### 样例输入 #1
```
6
2 3 4 5 6 1
3
1 2 2
2 7 1
6 1 1
```
### 样例输出 #1
```
5
3
1
```
## 提示

样例解析：

从 $1$ 开始走 $2^{2}$ 步到达 $5$（$1-2-3-4-5$）

从 $2$ 开始走 $7^{1}$ 步到达 $3$（$2-3-4-5-6-1-2-3$）

从 $6$ 开始走 $1^{1}$ 步到达 $1$（$6-1$）

对于 $10\%$ 的数据，$n\leq 100$，$m\leq 300$，$t_1\leq 100$。

对于 $50\%$ 的数据，$n\leq 3000$，$m\leq 3000$，$t_1\leq 3000$，$t_2=1$。

对于 $70\%$ 的数据，$n\leq 3000$，$m\leq 3000$。

对于 $100\%$ 的数据，$n\leq 400000$，$m\leq 300000$，$t_1\leq 10^{9}$，$t_2\leq 10^9$。


---

---
title: "[USACO16FEB] Load Balancing P"
layout: "post"
diff: 提高+/省选-
pid: P6172
tag: ['2016', '倍增', '二分', 'USACO', '树状数组']
---
# [USACO16FEB] Load Balancing P
## 题目背景

*本题与 [银组同名题目](/problem/P3138) 在题意上一致，唯一的差别是数据范围。*
## 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 10^5$）散布在整个农场上。整个农场是一个无限大的二维平面，第 $i$ 头奶牛的坐标是 $(x_i,y_i)$（保证 $x_i,y_i$ 均为正奇数，且 $x_i,y_i \leq 10^6$），且没有任意两头奶牛在同一位置上。

FJ 希望修建一条竖直方向的栅栏，它的方程是 $x=a$，他还希望修建一条水平方向的栅栏，它的方程是 $y=b$。为了防止栅栏经过奶牛，$a,b$ 均要求是偶数。容易发现，这两个栅栏会在 $(a,b)$ 处相交，将整个农场分割为四个区域。

FJ 希望这四个区域内的奶牛数量较为均衡，尽量避免一个区域奶牛多而另一个区域奶牛少的情况。令 $M$ 为四个区域里奶牛最多区域的奶牛数量，请帮 FJ 求出 $M$ 的最小值。
## 输入格式

第一行一个整数 $N$。

接下来 $N$ 行，每行两个整数 $x_i,y_i$，描述第 $i$ 头奶牛的位置。
## 输出格式

输出 $M$ 的最小值。
## 样例

### 样例输入 #1
```
7
7 3
5 5
7 13
3 1
11 7
5 3
9 1
```
### 样例输出 #1
```
2
```


---

---
title: "[NOI Online #3 提高组] 魔法值"
layout: "post"
diff: 提高+/省选-
pid: P6569
tag: ['2020', '倍增', '矩阵运算', 'NOI Online']
---
# [NOI Online #3 提高组] 魔法值
## 题目描述

H 国的交通由 $n$ 座城市与 $m$ 条道路构成，城市与道路都从 $1$ 开始编号，其中 $1$ 号城市是 H 国的首都。H 国中一条道路将把两个不同城市直接相连，且任意两个城市间至多有一条道路。

H 国是一个信奉魔法的国家，在第 $j$ 天，$i$ 号城市的魔法值为 $f_{i,j}$。H 国的魔法师已观测到第 0 天时所有城市的魔法值 $f_{i,0}$，且他们还发现，之后的每一天每个城市的魔法值，都将会变为所有与该城市直接相连的城市的前一天魔法值的异或值，即

$$
f_{x,j}=f_{v_1,j-1}\oplus f_{v_2,j-1}\oplus \cdots\oplus f_{v_k,j-1}
$$

其中 $j\ge 1$，$v_1,v_2,\cdots,v_k$ 是所有与 $x$ 号城市直接相连的城市，$\oplus$ 为异或运算。

现在 H 国的国王问了你 $q$ 个问题，对于第 $i$（$1\le i\le q$）个问题你需要回答：第 $a_i$ 天时首都的魔法值是多少。
## 输入格式

第一行三个用空格分隔的整数 $n,m,q$，表示城市数、道路数与问题数。

第二行 $n$ 个用空格分隔的整数，第 $i$ 个整数表示 $f_{i, 0}$。

接下来 $m$ 行，每行两个用空格分隔的正整数 $u,v$，表示一条连接 $u$ 号城市与 $v$ 号城市的道路。

接下来 $q$ 行每行一个整数，第 $i$ 行的整数表示 $a_i$。
## 输出格式

按顺序输出 $q$ 行每行一个整数，表示对应问题的答案。
## 样例

### 样例输入 #1
```
3 3 1
0 0 1
1 2
1 3
2 3
1

```
### 样例输出 #1
```
1
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，满足 $a_i \leq 100$。
- 对于 $40\%$ 的数据，满足 $n \leq 20$。
- 另有 $30\%$ 的数据，满足 $m=\frac{n(n-1)}{2}$。
- 对于 $100\%$ 的数据，满足 $1 \leq n,q \leq 100$，$1 \leq m \leq \frac{n(n-1)}{2}$，$1\leq a_i < 2^{32}$，$0\leq f_i < 2^{32}$。

#### 说明

data provider ：@一扶苏一，数据有锅请联系她。如果被朴素的快速幂水过去了也请联系她。


---

---
title: "[CCC 2019] Triangle: The Data Structure"
layout: "post"
diff: 提高+/省选-
pid: P6648
tag: ['动态规划 DP', '递推', '2019', '倍增', 'CCC（加拿大）', 'ST 表']
---
# [CCC 2019] Triangle: The Data Structure
## 题目背景

在 Shuchong 的平行宇宙里，计算机学中的最重要的数据结构就是三角形。   
注：因为原数据包太大，故这题缩减了一些数据，具体缩减的数据点如下：

- Subtask 1：1 ~ 10
- Subtask 2：1 ~ 10

所以此题拥有的测试点为：

- Subtask 1：11 ~ 26
- Subtask 2：11 ~ 24

若想测试本题没有的测试点请到 [此处](https://www.luogu.com.cn/problem/U120704) 测试。
## 题目描述

大小为 $m$ 的一个三角形由 $m$ 行组成，第 $i$ 行包含 $i$ 个元素。   
并且，这些行必须排为等边三角形的形状。  
比如说，以下是一个 $m=4$ 的三角形。   
![](https://cdn.luogu.com.cn/upload/image_hosting/fdut4hrs.png)    
每个三角形还包含子三角形。   
比如说上面这个三角形，包含：
- $10$ 个大小为 $1$ 的三角形。
- $6$ 个大小为 $2$ 的三角形。
- $3$ 个大小为 $3$ 的三角形。

注意，每个三角形都是自身的子三角形。   
现在给定一个大小为 $n$ 的三角形，求对于每个大小为 $k$ 的子三角形，子三角形内几个数的最大值的和。
## 输入格式

第一行两个整数 $n,k$ 代表三角形的大小和要求的子三角形的大小。   
接下来 $n$ 行第 $i$ 行有 $i$ 个整数代表这个三角形。
## 输出格式

一行一个整数代表对于每个大小为 $k$ 的子三角形，子三角形内几个数的最大值的和。
## 样例

### 样例输入 #1
```
4 2
3
1 2
4 2 1
6 1 4 2
```
### 样例输出 #1
```
23
```
## 提示

#### 数据规模与约定

- Subtask 1（25 pts）：$n \le 1000$。
- Subtask 2（75 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le k \le n \le 3000$，$0 \le $ 三角形内每个数 $\le 10^9$。

#### 说明

**翻译自 [CCC 2019](https://cemc.math.uwaterloo.ca/contests/computing/2019/index.html) Senior T5 [Triangle: The Data Structure](https://cemc.math.uwaterloo.ca/contests/computing/2019/stage%201/seniorEF.pdf)。**   
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。


---

---
title: "[ICPC 2014 WF] Surveillance"
layout: "post"
diff: 提高+/省选-
pid: P6902
tag: ['2014', '倍增', 'ICPC']
---
# [ICPC 2014 WF] Surveillance
## 题目描述

The International Corporation for Protection and Control (ICPC) develops efficient technology for, well, protection and control. Naturally, they are keen to have their own headquarters protected and controlled. Viewed from above, the headquarters building has the shape of a convex polygon. There are several suitable places around it where cameras can be installed to monitor the building. Each camera covers a certain range of the polygon sides (building walls), depending on its position. ICPC wants to minimize the number of cameras needed to cover the whole building.
## 输入格式

The input consists of a single test case. Its first line contains two integers $n$ and $k$ ($3 \le n \le 10^6$ and $1 \le k \le 10^6$), where $n$ is the number of walls and $k$ is the number of possible places for installing cameras. Each of the remaining $k$ lines contains two integers $a_ i$ and $b_ i$ ($1 \le a_ i, b_ i \le n$). These integers specify which walls a camera at the $i^{th}$ place would cover. If $a_ i \le b_ i$ then the camera covers each wall $j$ such that $a_ i \le j \le b_ i$. If $a_ i > b_ i$ then the camera covers each wall $j$ such that $a_ i \le j \le n$ or $1 \le j \le b_ i$.
## 输出格式

Display the minimal number of cameras that suffice to cover each wall of the building. The ranges covered by two cameras may overlap. If the building cannot be covered, display impossible instead.
## 样例

### 样例输入 #1
```
100 7
1 50
50 70
70 90
90 40
20 60
60 80
80 20

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
8 2
8 3
5 7

```
### 样例输出 #2
```
impossible

```
### 样例输入 #3
```
8 2
8 4
5 7

```
### 样例输出 #3
```
2

```
## 提示

Time limit: 4000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

### 题目描述
给定一个长度为 $n$ 的环，有 $k$ 个区域被覆盖，求最小的满足环被完全覆盖的区域数量。
### 输入格式
第一行两个整数 $n$，$k$。
接下来 $k$ 行，每行两个整数表示一个区域。
### 输出格式
若环不可能被完全覆盖，输出 `impossible`；否则输出一个整数，表示最少的区域数量。


---

---
title: "[NOIP2020] 字符串匹配"
layout: "post"
diff: 提高+/省选-
pid: P7114
tag: ['字符串', '2020', '倍增', 'NOIP 提高组', '哈希 hashing']
---
# [NOIP2020] 字符串匹配
## 题目描述

小 C 学习完了字符串匹配的相关内容，现在他正在做一道习题。

对于一个字符串 $S$，题目要求他找到 $S$ 的所有具有下列形式的拆分方案数：

$S = ABC$，$S = ABABC$，$S = ABAB \ldots ABC$，其中 $A$，$B$，$C$ 均是非空字符串，且 $A$ 中出现奇数次的字符数量不超过 $C$ 中出现奇数次的字符数量。

更具体地，我们可以定义 $AB$ 表示两个字符串 $A$，$B$ 相连接，例如 $A = \texttt{aab}$，$B = \texttt{ab}$，则 $AB = \texttt{aabab}$。

并递归地定义 $A^1=A$，$A^n = A^{n - 1} A$（$n \ge 2$ 且为正整数）。例如 $A = \texttt{abb}$，则 $A^3=\texttt{abbabbabb}$。

则小 C 的习题是求 $S = {(AB)}^iC$ 的方案数，其中 $F(A) \le F(C)$，$F(S)$ 表示字符串 $S$ 中出现奇数次的字符的数量。两种方案不同当且仅当拆分出的 $A$、$B$、$C$ 中有至少一个字符串不同。

小 C 并不会做这道题，只好向你求助，请你帮帮他。
## 输入格式

本题有多组数据，输入文件第一行一个正整数 $T$ 表示数据组数。

每组数据仅一行一个字符串 $S$，意义见题目描述。$S$ 仅由英文小写字母构成。
## 输出格式

对于每组数据输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
nnrnnr
zzzaab
mmlmmlo

```
### 样例输出 #1
```
8
9
16

```
### 样例输入 #2
```
5
kkkkkkkkkkkkkkkkkkkk
lllllllllllllrrlllrr
cccccccccccccxcxxxcc
ccccccccccccccaababa
ggggggggggggggbaabab

```
### 样例输出 #2
```
156
138
138
147
194

```
### 样例输入 #3
```
见附件中的 string/string3.in
```
### 样例输出 #3
```
见附件中的 string/string3.ans
```
### 样例输入 #4
```
见附件中的 string/string4.in
```
### 样例输出 #4
```
见附件中的 string/string4.ans
```
## 提示

**【样例 #1 解释】**

对于第一组数据，所有的方案为

1. $A=\texttt{n}$，$B=\texttt{nr}$，$C=\texttt{nnr}$。
2. $A=\texttt{n}$，$B=\texttt{nrn}$，$C=\texttt{nr}$。
3. $A=\texttt{n}$，$B=\texttt{nrnn}$，$C=\texttt{r}$。
4. $A=\texttt{nn}$，$B=\texttt{r}$，$C=\texttt{nnr}$。
5. $A=\texttt{nn}$，$B=\texttt{rn}$，$C=\texttt{nr}$。
6. $A=\texttt{nn}$，$B=\texttt{rnn}$，$C=\texttt{r}$。
7. $A=\texttt{nnr}$，$B=\texttt{n}$，$C=\texttt{nr}$。
8. $A=\texttt{nnr}$，$B=\texttt{nn}$，$C=\texttt{r}$。

**【数据范围】**

| 测试点编号 | $\lvert S \rvert \le$ | 特殊性质 |
|:-:|:-:|:-:|
| $1 \sim 4$ | $10$ | 无 |
| $5 \sim 8$ | $100$ | 无 |
| $9 \sim 12$ | $1000$ | 无 |
| $13 \sim 14$ | $2^{15}$ | $S$ 中只包含一种字符 |
| $15 \sim 17$ | $2^{16}$ | $S$ 中只包含两种字符 |
| $18 \sim 21$ | $2^{17}$ | 无 |
| $22 \sim 25$ | $2^{20}$ | 无 |

对于所有测试点，保证 $1 \le T \le 5$，$1 \le |S| \le 2^{20}$。 


---

---
title: "[eJOI 2020] Fountain (Day1)"
layout: "post"
diff: 提高+/省选-
pid: P7167
tag: ['2020', '倍增', 'eJOI（欧洲）', 'ST 表']
---
# [eJOI 2020] Fountain (Day1)
## 题目描述

大家都知道喷泉吧？现在有一个喷泉由 $N$ 个圆盘组成，从上到下以此编号为 $1 \sim N$，第 $i$ 个喷泉的直径为 $D_i$，容量为 $C_i$，当一个圆盘里的水大于了这个圆盘的容量，那么水就会溢出往下流，直到流入半径大于这个圆盘的圆盘里。如果下面没有满足要求的圆盘，水就会流到喷泉下的水池里。

现在给定 $Q$ 组询问，每一组询问这么描述：

- 向第 $R_i$ 个圆盘里倒入 $V_i$ 的水，求水最后会流到哪一个圆盘停止。

如果最终流入了水池里，那么输出 $0$。

**注意，每个询问互不影响。**
## 输入格式

第一行两个整数 $N,Q$ 代表圆盘数和询问数。      
接下来 $N$ 行每行两个整数 $D_i,C_i$ 代表一个圆盘。       
接下来 $Q$ 行每行两个整数 $R_i,V_i$ 代表一个询问。
## 输出格式

$Q$ 行每行一个整数代表询问的答案。
## 样例

### 样例输入 #1
```
6 5
4 10
6 8
3 5
4 14
10 9
4 20
1 25
6 30
5 8
3 13
2 8
```
### 样例输出 #1
```
5
0
5
4
2
```
## 提示

#### 样例 1 解释

前两个询问的解释如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/64e7acuq.png)

因为每个询问互不影响，对于第三个询问，第 $5$ 个圆盘里的水不会溢出。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（30 pts）：$N \le 1000$，$Q \le 2000$。
- Subtask 2（30 pts）：$D_i$ 为严格单调递增序列。
- Subtask 3（40 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $2 \le N \le 10^5$。
- $1 \le Q \le 2 \times 10^5$。
- $1 \le C_i \le 1000$。
- $1 \le D_i,V_i \le 10^9$。
- $ 1\le R_i \le N$。

#### 说明

翻译自 [eJOI 2020 Day1 A Fountain](https://ejoi2020.ge/static/assets/Day1/Problems/Fountain.pdf)。


---

---
title: "[JRKSJ R3] system"
layout: "post"
diff: 提高+/省选-
pid: P7981
tag: ['倍增', '2021', '洛谷原创', '基环树']
---
# [JRKSJ R3] system
## 题目描述

定义对序列 $a$ 的一次操作为令 $b_i\gets a_{a_i}$，再令 $a_i\gets b_i$，其中 $i\in[1,n]$。

给你一个长为 $n$ 的序列 $a$，询问对 $a$ 进行 $k$ 次操作后的序列。
## 输入格式

第一行两个整数 $n,k$。

第二行 $n$ 个整数表示序列 $a$。
## 输出格式

一行共 $n$ 个整数，表示 $k$ 次操作后的序列 $a$。
## 样例

### 样例输入 #1
```
5 2
2 5 4 3 1
```
### 样例输出 #1
```
2 5 3 4 1
```
### 样例输入 #2
```
20 233
1 1 5 6 8 15 10 11 18 14 4 16 16 11 3 5 1 15 4 5
```
### 样例输出 #2
```
1 1 4 5 6 8 4 15 5 6 3 11 11 15 11 4 1 8 3 4
```
## 提示

### 样例解释

对于第 $1$ 个样例，$a$ 的变化如下：

$$5,1,3,4,2$$
$$2,5,3,4,1$$

### 数据规模与约定

本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10^4$ | $\text A$ | $5$ |
| $2$ | $10^2$ | 无 | $15$ |
| $3$ | $10^4$ | $\text B$ | $10$ |
| $4$ | $5\times 10^5$ | $\text B$ | $20$ |
| $5$ | $5\times 10^5$ | $\text C$ | $20$ |
| $6$ | $5\times 10^5$ | 无 | $30$ |

性质 $\text A$：$0\le k\le 10^3$。\
性质 $\text B$：$a_i=i\bmod n+1$。\
性质 $\text C$：$a$ 是一个 $[1,n]$ 的排列。

对于 $100\%$ 的数据，$1\le n\le 5\times 10^5$，$0\le k\le 10^9$，$1\le a_i\le n$。


---

