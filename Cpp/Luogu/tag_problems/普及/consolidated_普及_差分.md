---
title: "[USACO24JAN] Balancing Bacteria B"
layout: "post"
diff: 普及/提高-
pid: P10133
tag: ['USACO', '2024', '差分']
---
# [USACO24JAN] Balancing Bacteria B
## 题目描述

Farmer John 有 $N$（$1\le N\le 2\cdot 10^5$）块草地排成一行，其中草地 $i$ 的细菌水平与健康草的细菌水平相差 $a_i$（$−10^{15}\le a_i\le 10^{15}$）。例如，如果 $a_i=−3$，则草地 $i$ 的细菌水平比正常水平低 $3$，需要额外添加恰好 $3$ 个单位的细菌才能将其提高到被认为是健康的程度。

Farmer John 想要确保每一块草地都被修复至健康的细菌水平。方便的是，他有两种品牌的农药可以喷洒在他的田地里，一种可以添加细菌，另一种可以去除细菌。当 Farmer John 喷洒任一类型的农药时，他站在草地 $N$（最右边的草地）并为他的喷雾器选择功率等级 $L$（$1\le L\le N$）。

喷雾器对靠近 Farmer John 的草地效果最大，随着距离增加效果逐渐减弱。如果 Farmer John 选择添加细菌的农药，则 $L$ 单位的细菌将被添加至草地 $N$，$L−1$ 单位添加至草地 $N−1$，$L−2$ 单位添加至草地 $N−2$，以此类推。草地 $1\ldots N−L$ 不会得到任何细菌，因为喷雾器设置的功率不足以到达它们。类似地，如果 Farmer John 选择去除细菌的农药，则 $L$ 单位的细菌将被从草地 $N$ 去除，$L−1$ 单位被从草地 $N−1$ 去除，以此类推。同样，草地 $1\ldots N−L$ 将不受影响。

求 Farmer John 使用喷雾器的最少次数，使得每块草地都具有健康草的推荐细菌值。输入保证答案不超过 $10^9$。

**注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C/C++ 中的 "long long"）。**
## 输入格式

输入的第一行包含 $N$。

第二行包含 $N$ 个整数 $a_1\ldots a_N$，为每块草地的初始细菌水平。 
## 输出格式

输出一个整数，为使每块草地都具有健康草的推荐的细菌值所需使用喷雾器的最少次数。 
## 样例

### 样例输入 #1
```
2
-1 3
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
5
1 3 -2 -7 5
```
### 样例输出 #2
```
26
```
## 提示

### 样例解释 1

使用去除细菌的农药，功率等级为 $1$，使用五次。然后使用添加细菌的农药，功率等级为 $2$，使用一次。

### 测试点性质

- 测试点 $3-5$：$N\le 10^3$，答案不超过 $10^3$。
- 测试点 $6-10$：$N\le 10^3$。
- 测试点 $11-15$：没有额外限制。


---

---
title: "[NOIP 2012 提高组] 借教室"
layout: "post"
diff: 普及/提高-
pid: P1083
tag: ['2012', '二分', 'NOIP 提高组', '前缀和', '差分']
---
# [NOIP 2012 提高组] 借教室
## 题目描述

在大学期间，经常需要租借教室。大到院系举办活动，小到学习小组自习讨论，都需要向学校申请借教室。教室的大小功能不同，借教室人的身份不同，借教室的手续也不一样。

面对海量租借教室的信息，我们自然希望编程解决这个问题。

我们需要处理接下来 $n$ 天的借教室信息，其中第 $i$ 天学校有 $r_i$ 个教室可供租借。共有 $m$ 份订单，每份订单用三个正整数描述，分别为 $d_j,s_j,t_j$，表示某租借者需要从第 $s_j$ 天到第 $t_j$ 天租借教室（包括第 $s_j$ 天和第 $t_j$ 天），每天需要租借 $d_j$ 个教室。

我们假定，租借者对教室的大小、地点没有要求。即对于每份订单，我们只需要每天提供 $d_j$ 个教室，而它们具体是哪些教室，每天是否是相同的教室则不用考虑。

借教室的原则是先到先得，也就是说我们要按照订单的先后顺序依次为每份订单分配教室。如果在分配的过程中遇到一份订单无法完全满足，则需要停止教室的分配，通知当前申请人修改订单。这里的无法满足指从第 $s_j$ 天到第 $t_j$ 天中有至少一天剩余的教室数量不足 $d_j$ 个。

现在我们需要知道，是否会有订单无法完全满足。如果有，需要通知哪一个申请人修改订单。

## 输入格式

第一行包含两个正整数 $n,m$，表示天数和订单的数量。

第二行包含 $n$ 个正整数，其中第 $i$ 个数为 $r_i$，表示第 $i$ 天可用于租借的教室数量。

接下来有 $m$ 行，每行包含三个正整数 $d_j,s_j,t_j$，表示租借的数量，租借开始、结束分别在第几天。

每行相邻的两个数之间均用一个空格隔开。天数与订单均用从 $1$ 开始的整数编号。
## 输出格式

如果所有订单均可满足，则输出只有一行，包含一个整数 $0$。否则（订单无法完全满足）

输出两行，第一行输出一个负整数 $-1$，第二行输出需要修改订单的申请人编号。

## 样例

### 样例输入 #1
```
4 3 
2 5 4 3 
2 1 3 
3 2 4 
4 2 4
```
### 样例输出 #1
```
-1 
2
```
## 提示

【输入输出样例说明】

第 $1 $份订单满足后，$4 $天剩余的教室数分别为 $0,3,2,3$。第 $2$ 份订单要求第 $2 $天到第 $4$ 天每天提供 $3$ 个教室，而第 $3$ 天剩余的教室数为$ 2$，因此无法满足。分配停止，通知第 $2$ 个申请人修改订单。

【数据范围】

对于 $10\%$ 的数据，有 $1\le n,m\le 10$；

对于 $30\%$ 的数据，有 $1\le n,m\le 1000$；

对于 $70\%$ 的数据，有 $1 \le n,m \le 10^5$；

对于 $100\%$ 的数据，有 $1 \le n,m \le 10^6$，$0 \le r_i,d_j\le 10^9$，$1 \le s_j\le t_j\le n$。


NOIP 2012 提高组 第二天 第二题

2022.2.20 新增一组 hack 数据


---

---
title: "[蓝桥杯 2024 省 C] 商品库存管理"
layout: "post"
diff: 普及/提高-
pid: P10903
tag: ['2024', '差分', '蓝桥杯省赛']
---
# [蓝桥杯 2024 省 C] 商品库存管理
## 题目描述

在库存管理系统中，跟踪和调节商品库存量是关键任务之一。小蓝经营的仓库中存有多种商品，这些商品根据类别和规格被有序地分类并编号，编号范围从 $1$ 至 $n$。初始时，每种商品的库存量均为 $0$。

为了高效地监控和调整库存量，小蓝的管理团队设计了 $m$ 个操作，每个操作涉及到一个特定的商品区间，即一段连续的商品编号范围（例如区间 $[L, R]$）。执行这些操作时，区间内每种商品的库存量都将增加 $1$。然而，在某些情况下，管理团队可能会决定不执行某些操作，使得这些操作涉及的商品区间内的库存量不会发生改变，维持原有的状态。

现在，管理团队需要一个评估机制，来确定如果某个操作未被执行，那么最终会有多少种商品的库存量为 $0$。对此，请你为管理团队计算出，对于每个操作，如果不执行该操作而执行其它操作，库存量为 $0$ 的商品的种类数。
## 输入格式

输入的第一行包含两个整数 $n$ 和 $m$，分别表示商品的种类数和操作的个数。

接下来的 $m$ 行，每行包含两个整数 $L$ 和 $R$，表示一个操作涉及的商品区间。
## 输出格式

输出 $m$ 行，每行一个整数，第 $i$ 行的整数表示如果不执行第 $i$ 个操作，则最终库存量为 $0$ 的商品种类数。
## 样例

### 样例输入 #1
```
5 3
1 2
2 4
3 5
```
### 样例输出 #1
```
1
0
1
```
## 提示

**【样例说明】**

考虑不执行每个操作时，其余操作对商品库存的综合影响：

- **不执行操作 $1$**：剩余的操作是操作 $2$（影响区间 $[2, 4]$）和操作 $3$（影响区间 $[3, 5]$）。执行这两个操作后，商品库存序列变为 $[0, 1, 2, 2, 1]$。在这种情况下，只有编号为 $1$ 的商品的库存量为 $0$。因此，库存量为 $0$ 的商品种类数为 $1$。

- **不执行操作 $2$**：剩余的操作是操作 $1$（影响区间 $[1, 2]$）和操作 $3$（影响区间 $[3, 5]$）。执行这两个操作后，商品库存序列变为 $[1, 1, 1, 1, 1]$。在这种情况下，所有商品的库存量都不为 $0$。因此，库存量为 $0$ 的商品种类数为 $0$。

- **不执行操作 $3$**：剩余的操作是操作 $1$（影响区间 $[1, 2]$）和操作 $2$（影响区间 $[2, 4]$）。执行这两个操作后，商品库存序列变为 $[1, 2, 1, 1, 0]$。在这种情况下，只有编号为 $5$ 的商品的库存量为 $0$。因此，库存量为 $0$ 的商品种类数为 $1$。

**【评测用例规模与约定】**

对于 $20\%$ 的评测用例，$1 \le n,m \le 5 \times 10^3$，$1\le L \le R \le n$。  
对于所有评测用例，$1 \le n,m \le 3 \times 10^5$，$1 \le L \le R \le n$。


---

---
title: "「FSLOI Round I」迷雾"
layout: "post"
diff: 普及/提高-
pid: P11078
tag: ['线段树', '洛谷原创', 'O2优化', '差分', '洛谷月赛']
---
# 「FSLOI Round I」迷雾
## 题目背景

**[English statement.](https://www.luogu.com.cn/problem/T500989) You must submit your code at the Chinese version of the statement.**

小 F 来到了迷雾之森。
## 题目描述

整个迷雾之森可以由一个 $n \times m$ 的矩阵表示，`X` 代表有迷雾的地块，`.` 代表空地。从上到下给每行标号为 $1,2,\cdots,n$，从左到右给每列标号为 $1,2,\cdots,m$。除此之外，还会给定一个迷雾系数 $k$。

小 F 进行了 $q$ 次移动。第 $i$ 次移动由一个字符 $c_i$，两个数字 $a_i,b_i$ 描述，更具体地说：

- $c_i$ 为 `U` 时，向上走 $a_i$ 步。
- $c_i$ 为 `D` 时，向下走 $a_i$ 步。
- $c_i$ 为 `L` 时，向左走 $a_i$ 步。
- $c_i$ 为 `R` 时，向右走 $a_i$ 步。

当然，小 F 不可以走出这个 $ n \times m $ 的范围。换句话说，若走到边界处，立即结束此次移动。

若第 $i$ 次移动**结束**后小 F 停留在有迷雾的地块上，则小 F 会对从 $i+k$ 开始，之后每 $k$ 次移动的 $c$ 进行一次修改，一共修改 $b_i$ 个移动。也就是说，小 F 会对 $c_{i+k},c_{i+2\times k},\cdots,c_{i+b_i \times k}$ 进行一次**修改**（保证 $i+b_i\times k \leq q$）。若 $b_i=0$ 则相当于不做修改。**注意所有操作的 $k$ 是一样的**。

修改 $c_x$ 即为按照以下规则替换 $c_x$：

- 若 $c_x$ 为 `U`，则替换为 `D`。
- 若 $c_x$ 为 `D`，则替换为 `U`。
- 若 $c_x$ 为 `R`，则替换为 `L`。
- 若 $c_x$ 为 `L`，则替换为 `R`。

初始时小 F 在点 $(1,1)$ 处，请输出 $q$ 次移动后小 F 所在的位置 $(x,y)$。
## 输入格式

第一行四个整数 $n,m,q,k$。

接下来 $n$ 行，每行一个长度为 $m$，由 `.` 和 `X` 构成的字符串，描述整个迷雾之森。

接下来 $q$ 行，每行先是一个字符 $c_i$，然后依次是两个整数 $a_i,b_i$，描述每次移动。
## 输出格式

共一行。

两个整数 $x,y$，表示小 F 最终的位置。
## 样例

### 样例输入 #1
```
3 3 4 1
..X
.XX
XXX
D 1 2
R 1 2
D 2 0
L 1 0

```
### 样例输出 #1
```
1 3

```
### 样例输入 #2
```
10 10 8 2
XX.XX.X...
XXX..XXX.X
XXX.X.XXXX
XXXXXXX.X.
.XX...XX.X
.XXX.X.X.X
...XXX.XXX
XX...XX...
X..XX....X
XXXXX...XX
U 2 1
L 1 3
R 3 1
L 1 2
D 2 1
R 5 1
L 4 0
D 3 0

```
### 样例输出 #2
```
1 10

```
## 提示

**【样例 1 解释】**

小 F 的位置变化如下：

$(1,1) \rightarrow (2,1) \rightarrow (2,2)\rightarrow (1,2) \rightarrow (1,3)$

序列 $c$ 的变化如下：

$ \lbrace \texttt{D,R,D,L} \rbrace \rightarrow \lbrace \texttt{D,R,D,L} \rbrace \rightarrow \lbrace \texttt{D,R,U,R} \rbrace \rightarrow \lbrace \texttt{D,R,U,R} \rbrace \rightarrow \lbrace \texttt{D,R,U,R} \rbrace$

**【数据规模与约定】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，保证：
- $1 \leq n,m \leq 500$
- $1 \leq k \leq 20$
- $1\leq q \leq 2 \times 10^5$
- $1 \leq a_i,b_i \leq 10^6$
- $c_i$ 为 `L`，`R`，`U`，`D` 四个字符中的一个。

|子任务|分值|特殊性质|
|:-----:|:-----:|:-----:|
|$1$|$5$|$q=1$|
|$2$|$15$|$n,m,q\leq 100$|
|$3$|$20$|$k=1$|
|$4$|$30$|$n=1$|
|$5$|$30$|无|


---

---
title: "[NOISG 2018 Finals] Collecting Mushrooms"
layout: "post"
diff: 普及/提高-
pid: P11594
tag: ['2018', '前缀和', '差分', 'NOISG（新加坡）']
---
# [NOISG 2018 Finals] Collecting Mushrooms
## 题目背景

译自 [NOISG 2018 Finals A. Collecting Mushrooms](https://github.com/noisg/sg_noi_archive/tree/master/2018/tasks/collectmushrooms)。
## 题目描述

螃蟹 Lim Li 在她的花园里打造了一个蘑菇种植园。这个蘑菇种植园可以看成一个 $R$ 行 $C$ 列的网格，其中每一格要么是空的，要么有一朵蘑菇，要么有一个洒水器。

举个例子，一个 $R=5,C=5$ 的蘑菇种植园可能是长这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/qqn2ssqx.png)

一朵蘑菇和一个洒水器之间的距离被定义为它们的横坐标差的绝对值与纵坐标差的绝对值的较大值。换句话说，假设一朵蘑菇位于 $X_m$ 行 $Y_m$ 列，一个洒水器位于 $X_s$ 行 $Y_s$ 列，那么它们之间的距离为 $\max(|X_m-X_s|,|Y_m-Y_s|)$。

一个洒水器只能浇到距离自己不超过 $D$ 的蘑菇。下图展示了 $D=1$ 时洒水器可以浇到的区域：

![](https://cdn.luogu.com.cn/upload/image_hosting/sr5w3lov.png)

一朵蘑菇如果可以被至少 $K$ 个洒水器浇到，则我们称它是**好蘑菇**。你需要帮 Lim Li 计数在她的蘑菇种植园里有多少朵**好蘑菇**。
## 输入格式

第一行包含四个整数 $R,C,D,K$，含义如题意所述。

接下来 $R$ 行，每行 $C$ 个字符，描述一个蘑菇种植园。每个字符表示一个格子：

- `.` 表示一个空格子。
- `M` 表示一个有一朵蘑菇的格子。
- `S` 表示一个有一个洒水器的格子。
## 输出格式

一行一个整数，表示**好蘑菇**的数量。
## 样例

### 样例输入 #1
```
5 5 1 1
....M
.M...
..S..
.S...
...M.
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
4 4 4 1
....
.M..
..MM
...S
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
1 8 5 2
SM..MM.S
```
### 样例输出 #3
```
2
```
### 样例输入 #4
```
5 5 2 2
....M
.M...
..S..
.S...
...M.
```
### 样例输出 #4
```
2
```
## 提示

### 样例 #1 解释

所有洒水器可以浇到的距离范围都是 $1$，也就是每个洒水器都能且仅能洒到与自己八连通的格子。只有位于 $(2,2)$ 的蘑菇可以被浇到水。

这组样例满足子任务 $3,4,6$。

### 样例 #2 解释

唯一的洒水器可以浇到的距离范围是 $4$，所以可以浇到所有蘑菇。

这组样例满足子任务 $1,2,4,6$。

### 样例 #3 解释

所有蘑菇都需要被两头的洒水器浇到才能成为**好蘑菇**。因为洒水器可以浇到的距离范围都是 $5$，所以只有从左往右第二朵和第三朵蘑菇满足**好蘑菇**的要求。

这组样例满足子任务 $4,5,6$。

### 样例 #4 解释

因为洒水器可以浇到的距离范围都是 $2$，所以只有位于 $(2,2)$ 和 $(5,4)$ 的蘑菇可以同时被两个洒水器浇到。

这组样例满足子任务 $4,6$。

### 子任务

对于 $100\%$ 的数据，$2\le RC\le 5\times 10^5$，$1\le D\le \max(R,C)$，$1\le K\le RC$。保证种植园中至少有一朵蘑菇和一个洒水器。

| 子任务 | 得分 | 数据范围及特殊性质 |
| :----------: | :----------: | :----------: |
| $1$ | $9$ | $1\le R,C\le 100$，$D=\max(R,C)$，$K=1$ |
| $2$ | $10$ | $1\le R,C\le 100$，$D=\max(R,C)$ |
| $3$ | $18$ | $1\le R,C\le 100$，$D=1$，$K=1$ |
| $4$ | $23$ | $1\le R,C\le 500$，洒水器和蘑菇的数量均少于 $500$ |
| $5$ | $19$ | $R=1$ |
| $6$ | $21$ | 无特殊限制 |



---

---
title: "种树"
layout: "post"
diff: 普及/提高-
pid: P1250
tag: ['贪心', '排序', '差分约束']
---
# 种树
## 题目背景

一条街的一边有几座房子，因为环保原因居民想要在路边种些树。
## 题目描述

路边的地区被分割成块，并被编号成 $1, 2, \ldots,n$。每个部分为一个单位尺寸大小并最多可种一棵树。

每个居民都想在门前种些树，并指定了三个号码 $b$，$e$，$t$。这三个数表示该居民想在地区 $b$ 和 $e$ 之间（包括 $b$ 和 $e$）种至少 $t$ 棵树。

居民们想种树的各自区域可以交叉。你的任务是求出能满足所有要求的最少的树的数量。
## 输入格式

输入的第一行是一个整数，代表区域的个数 $n$。

输入的第二行是一个整数，代表房子个数 $h$。

第 $3$ 到第 $(h + 2)$ 行，每行三个整数，第 $(i + 2)$ 行的整数依次为 $b_i, e_i, t_i$，代表第 $i$ 个居民想在 $b_i$ 和 $e_i$ 之间种至少 $t_i$ 棵树。
## 输出格式

输出一行一个整数，代表最少的树木个数。
## 样例

### 样例输入 #1
```
9
4
1 4 2
4 6 2
8 9 2
3 5 2
```
### 样例输出 #1
```
5

```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证：

- $1 \leq n \leq 3 \times 10^4$，$1 \leq h \leq 5 \times 10^3$。
- $1 \leq b_i \leq e_i \leq n$，$1 \leq t_i \leq e_i - b_i + 1$。


---

---
title: "[GCJ 2019 #1B] Manhattan Crepe Cart"
layout: "post"
diff: 普及/提高-
pid: P13109
tag: ['2019', '差分', 'Google Code Jam']
---
# [GCJ 2019 #1B] Manhattan Crepe Cart
## 题目描述

There are a lot of great streetside food vendors in Manhattan, but without a doubt, the one with the tastiest food is the Code Jam Crepe Cart!

You want to find the cart, but you do not know where it is, except that it is at some street intersection. You believe that people from across Manhattan are currently walking toward that intersection, so you will try to identify the intersection toward which the most people are traveling.

For the purposes of this problem, Manhattan is a regular grid with its axes aligned to compass lines and bounded between 0 and $\mathbf{Q}$, inclusive, on each axis. There are west-east streets corresponding to gridlines $y = 0$, $y = 1$, $y = 2$, $\cdots$, $y = \mathbf{Q}$ and south-north streets corresponding to gridlines $x = 0$, $x = 1$, $x = 2$, $\cdots$, $x = \mathbf{Q}$, and people move only along these streets. The points where the lines meet — e.g., $(0, 0)$ and $(1, 2)$ — are intersections. The shortest distance between two intersections is measured via the Manhattan distance — that is, by the sum of the absolute horizontal difference and the absolute vertical difference between the two sets of coordinates.

You know the locations of $\mathbf{P}$ people, all of whom are standing at intersections, and the compass direction each person is headed: north (increasing $y$ direction), south (decreasing $y$ direction), east (increasing $x$ direction), or west (decreasing $x$ direction). A person is moving toward a street intersection if their current movement is on a shortest path to that street intersection within the Manhattan grid. For example, if a person located at $(x_0, y_0)$ is moving north, then they are moving toward all street intersections that have coordinates $(x, y)$ with $y > y_0$.

You think the crepe cart is at the intersection toward which the most people are traveling. Moreover, you believe that more southern and western parts of the island are most likely to have a crepe cart, so if there are multiple such intersections, you will choose the one with the smallest non-negative $x$ coordinate, and if there are multiple such intersections with that same $x$ coordinate, the one among those with the smallest non-negative $y$ coordinate. Which intersection will you choose?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with one line containing two integers $\mathbf{P}$ and $\mathbf{Q}$: the number of people, and the maximum possible value of an $x$ or $y$ coordinate in Manhattan, as described above. Then, there are $\mathbf{P}$ more lines. The $i$-th of those lines contains two integers $\mathbf{X}_i$ and $\mathbf{Y}_i$, the current location (street corner) of a person, and a character $\mathbf{D}_i$, the direction that person is headed. $\mathbf{D}_i$ is one of the uppercase letters N, S, E, or W, which stand for north, south, east, and west, respectively.
## 输出格式

For each test case, output one line containing `Case #t: x y`, where $t$ is the test case number (starting from 1) and $x$ and $y$ are the horizontal and vertical coordinates of the intersection where you believe the crepe cart is located.
## 样例

### 样例输入 #1
```
3
1 10
5 5 N
4 10
2 4 N
2 6 S
1 5 E
3 5 W
8 10
0 2 S
0 3 N
0 3 N
0 4 N
0 5 S
0 5 S
0 8 S
1 5 W
```
### 样例输出 #1
```
Case #1: 0 6
Case #2: 2 5
Case #3: 0 4
```
## 提示

**Sample Explanation**

In Sample Case #1, there is only one person, and they are moving north from $(5, 5)$. This means that all street corners with $y \geqslant 6$ are possible locations for the crepe cart. Of those possibilities, we choose the one with lowest $x \geqslant 0$ and then lowest $y \geqslant 6$.

In Sample Case #2, there are four people, all moving toward location $(2, 5)$. There is no other location that has as many people moving toward it.

In Sample Case #3, six of the eight people are moving toward location $(0, 4)$. There is no other location that has as many people moving toward it.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $1 \leqslant \mathbf{P} \leqslant 500$.
- $0 \leqslant \mathbf{X}_i \leqslant \mathbf{Q}$, for all $i$.
- $0 \leqslant \mathbf{Y}_i \leqslant \mathbf{Q}$, for all $i$.
- For all $i$, if $\mathbf{X}_i = 0$, $\mathbf{D}_i \neq \text{w}$.
- For all $i$, if $\mathbf{Y}_i = 0$, $\mathbf{D}_i \neq \text{s}$.
- For all $i$, if $\mathbf{X}_i = \mathbf{Q}$, $\mathbf{D}_i \neq \text{E}$.
- For all $i$, if $\mathbf{Y}_i = \mathbf{Q}$, $\mathbf{D}_i \neq \text{N}$.

**Test set 1 (9 Pts, Visible)**

- $\mathbf{Q} = 10$.

**Test set 2 (18 Pts, Hidden)**

- $\mathbf{Q} = 10^5$.


---

---
title: "[COCI 2012/2013 #4] RAZLIKA"
layout: "post"
diff: 普及/提高-
pid: P13416
tag: ['数学', '贪心', '2012', '单调队列', '排序', '差分', 'COCI（克罗地亚）']
---
# [COCI 2012/2013 #4] RAZLIKA
## 题目描述

Mirko's newest math homework assignment is a very difficult one! Given a sequence, $V$, of $N$ integers, remove exactly $K$ of them from the sequence. Let $M$ be the largest difference of any two remaining numbers in the sequence, and $m$ the smallest such difference. Select the $K$ integers to be removed from $V$ in such a way that the sum $M + m$ is the smallest possible. Mirko isn't very good at math, so he has asked you to help him!

## 输入格式

The first line of input contains two positive integers, $N$ ($3 \leq N \leq 1\,000\,000$) and $K$ ($1 \leq K \leq N - 2$).

The second line of input contains $N$ space-separated positive integers – the sequence $V$ ($-5\,000\,000 \leq V_i \leq 5\,000\,000$).
## 输出格式

The first and only line of output must contain the smallest possible sum $M + m$.
## 样例

### 样例输入 #1
```
5 2
-3 -2 3 8 6
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
6 2
-5 8 10 1 13 -1
```
### 样例输出 #2
```
13
```
### 样例输入 #3
```
6 3
10 2 8 17 2 17
```
### 样例输出 #3
```
6
```


---

---
title: "地毯 加强版"
layout: "post"
diff: 普及/提高-
pid: P13787
tag: ['前缀和', '差分']
---
# 地毯 加强版
## 题目描述

在 $n\times n$ 的格子上有 $m$ 个地毯。

给出这些地毯的信息，问每个点被多少个地毯覆盖。
## 输入格式

第一行，两个正整数 $n,m$。意义如题所述。

接下来 $m$ 行，每行两个坐标 $(x_1,y_1)$ 和 $(x_2,y_2)$，代表一块地毯，左上角是 $(x_1,y_1)$，右下角是 $(x_2,y_2)$。
## 输出格式

为了减少输出量，设 $F_{i,j}$ 表示 $(i,j)$ 这个格子被多少个地毯覆盖，你只需要输出 $\sum_{i=1}^n\sum_{j=1}^n (i+j)\oplus F_{i,j}$ 的值。注意这个值可能会超过 $2^{31}$。
## 样例

### 样例输入 #1
```
5 3
2 2 3 3
3 3 5 5
1 2 1 4
```
### 样例输出 #1
```
146
```
## 提示

对于 $50\%$ 的数据，有 $n,m\le 5000$。

对于 $100\%$ 的数据，有 $n\le 5000$，$m\le 2\times 10^5$。


---

---
title: "魔族密码"
layout: "post"
diff: 普及/提高-
pid: P1481
tag: ['树形 DP', '哈希 hashing', '字典树 Trie', '差分']
---
# 魔族密码
## 题目背景

风之子刚走进他的考场，就……

花花：当当当当~~偶是魅力女皇——花花！！^^（华丽出场，礼炮，鲜花）

风之子：我呕……（杀死人的眼神）快说题目！否则……-\_-###
## 题目描述



花花：……咦~~好冷~~我们现在要解决的是魔族的密码问题（自我陶醉：搞不好魔族里面还会有人用密码给我和菜虫写情书咧，哦活活，当然是给我的比较多拉\*^\_^\*）。

魔族现在使用一种新型的密码系统。每一个密码都是一个给定的仅包含小写字母的英文单词表，每个单词至少包含 $1$ 个字母，至多 $75$ 个字母。如果在一个由一个词或多个词组成的表中，除了最后一个以外，每个单词都被其后的一个单词所包含，即前一个单词是后一个单词的前缀，则称词表为一个词链。例如下面单词组成了一个词链：

- $\verb!i!$；
- $\verb!int!$；
- $\verb!integer!$。

但下面的单词不组成词链：

- $\verb!integer!$；
- $\verb!intern!$。

现在你要做的就是在一个给定的单词表中取出一些词，组成最长的词链，就是包含单词数最多的词链。将它的单词数统计出来，就得到密码了。

风之子：密码就是最长词链所包括的单词数阿……

## 输入格式

这些文件的格式是，第一行为单词表中的单词数 $N$（$1 \le N \le 2000$），下面每一行有一个单词，按字典顺序排列，中间也没有重复的单词。
## 输出格式

输出共一行，一个整数，表示密码。
## 样例

### 样例输入 #1
```
5
i
int
integer
intern
internet

```
### 样例输出 #1
```
4

```


---

---
title: "[USACO05FEB] Feed Accounting S"
layout: "post"
diff: 普及/提高-
pid: P1672
tag: ['2005', 'USACO', '差分']
---
# [USACO05FEB] Feed Accounting S
## 题目描述

约翰想知道上一船饲料是什么时候运到的。在饲料运到之前，他的牛正好把仓库里原来的饲料全吃光了。他收到运来的 $F1(1\le F1\le 10^6)$ 千克饲料。遗憾的是，他已经不记得这是哪一天的事情了。到第 $D(1\le D\le 2\times 10^3)$ 天为止，仓库里还剩下 $F2(1\le F2\le F1)$ 千克饲料。

约翰养了 $C(1\le C\le 100)$ 头牛，每头牛每天都吃掉恰好 $1$ 千克饲料。由于不同的原因，牛们从某一天开始在仓库吃饲料，又在某一天离开仓库，所以不同的两天可能会有差距很大的饲料消耗量。每头牛在来的那天和离开的那天都在仓库吃饲料。给出今天的日期 $D$，写一个程序，判断饲料**最近**一次运到是在什么时候。今天牛们已经吃过饲料了，并且饲料运到的那天牛们还没有吃过饲料。

**如果最终的答案有多个可能，请输出最大的（即，最近的）那一个。**
## 输入格式

第 $1$ 行：四个整数 $C$，$F1$，$F2$，$D$，用空格隔开。

第 $2$ 到 $C+1$ 行：每行是用空格隔开的两个数字，分别表示一头牛来仓库吃饲料的时间和离开的时间。
## 输出格式

一个正整数，即上一船饲料运到的时间。
## 样例

### 样例输入 #1
```
3 14 4 10
1 9
5 8
8 12
```
### 样例输出 #1
```
6
```
## 提示

### 样例解释

上一次运来了 $14$ 千克饲料，现在饲料还剩下 $4$ 千克。最近 $10$ 天里，有 $3$ 头牛来吃过饲料。

约翰在第 $6$ 天收到 $14$ 千克饲料，当天吃掉 $2$ 千克，第 $7$ 天吃掉 $2$ 千克，第 $8$ 天吃掉 $3$ 千克，第 $9$ 天吃掉 $2$ 千克，第 $10$ 天吃掉 $1$ 千克，正好还剩 $4$ 千克。

### 数据规模

$1\le F2\le F1\le 10^6$，$1\le D\le 2\times 10^3$，$1\le C\le 100$。


---

---
title: "[USACO13MAR] Poker Hands S"
layout: "post"
diff: 普及/提高-
pid: P3078
tag: ['贪心', '2013', 'USACO', '差分']
---
# [USACO13MAR] Poker Hands S
## 题目描述

Bessie and her friends are playing a unique version of poker involving a deck with N (1 <= N <= 100,000) different ranks, conveniently numbered 1..N (a normal deck has N = 13). In this game, there is only one type of hand the cows can play: one may choose a card labeled i and a card labeled j and play one card of every value from i to j.  This type of hand is called a "straight".

Bessie's hand currently holds a\_i cards of rank i (0 <= a\_i <= 100000). Help her find the minimum number of hands she must play to get rid of all her cards.

## 输入格式

\* Line 1: The integer N.

\* Lines 2..1+N: Line i+1 contains the value of a\_i.

## 输出格式

\* Line 1: The minimum number of straights Bessie must play to get rid of all her cards.

## 样例

### 样例输入 #1
```
5 
2 
4 
1 
2 
3 

```
### 样例输出 #1
```
6 

```
## 提示

Bessie can play a straight from 1 to 5, a straight from 1 to 2, a straight from 4 to 5, two straights from 2 to 2, and a straight from 5 to 5, for a total of 6 rounds necessary to get rid of all her cards.

## 题目翻译

Bessie 有 $n$ 堆牌，每堆牌有 $a_i$ 张。她一次可以将第 $i$ 堆到第 $j$ 堆里打一张出去，求打完 $n$ 堆牌最少的次数。

对于 $100\%$ 的数据，$1\le n\le10^5,0\le a_i\le10^5$。


---

---
title: "海底高铁"
layout: "post"
diff: 普及/提高-
pid: P3406
tag: ['前缀和', '差分']
---
# 海底高铁
## 题目描述

该铁路经过 $N$ 个城市，每个城市都有一个站。不过，由于各个城市之间不能协调好，于是乘车每经过两个相邻的城市之间（方向不限），必须单独购买这一小段的车票。第 $i$ 段铁路连接了城市 $i$ 和城市 $i+1(1\leq i<N)$。如果搭乘的比较远，需要购买多张车票。第 $i$ 段铁路购买纸质单程票需要 $A_i$ 博艾元。

虽然一些事情没有协调好，各段铁路公司也为了方便乘客，推出了 IC 卡。对于第 $i$ 段铁路，需要花 $C_i$ 博艾元的工本费购买一张 IC 卡，然后乘坐这段铁路一次就只要扣 $B_i(B_i<A_i)$ 元。IC 卡可以提前购买，有钱就可以从网上买得到，而不需要亲自去对应的城市购买。工本费不能退，也不能购买车票。每张卡都可以充值任意数额。对于第 $i$ 段铁路的 IC 卡，无法乘坐别的铁路的车。

Uim 现在需要出差，要去 $M$ 个城市，从城市 $P_1$ 出发分别按照 $P_1,P_2,P_3,\cdots,P_M$ 的顺序访问各个城市，可能会多次访问一个城市，且相邻访问的城市位置不一定相邻，而且不会是同一个城市。

现在他希望知道，出差结束后，至少会花掉多少的钱，包括购买纸质车票、买卡和充值的总费用。
## 输入格式

第一行两个整数，$N,M$。

接下来一行，$M$ 个数字，表示 $P_i$。

接下来 $N-1$ 行，表示第 $i$ 段铁路的 $A_i,B_i,C_i$。
## 输出格式

一个整数，表示最少花费
## 样例

### 样例输入 #1
```
9 10
3 1 4 1 5 9 2 6 5 3
200 100 50
300 299 100
500 200 500
345 234 123
100 50 100
600 100 1
450 400 80
2 1 10
```
### 样例输出 #1
```
6394
```
## 提示

$2$ 到 $3$ 以及 $8$ 到 $9$ 买票，其余买卡。

对于 $30\%$ 数据 $M=2$。

对于另外 $30\%$ 数据 $N\leq1000，M\leq1000$。

对于 $100\%$ 的数据 $M,N\leq 10^5，A_i,B_i,C_i\le10^5$。


---

---
title: "不成熟的梦想家 (未熟 DREAMER)"
layout: "post"
diff: 普及/提高-
pid: P3655
tag: ['递推', '差分', '洛谷月赛']
---
# 不成熟的梦想家 (未熟 DREAMER)
## 题目背景

**どんな未来かは 誰もまだ知らない**

**那是个任谁也不会知晓的未来**

**でも楽しくなるはずだよ**

**但应该会充满乐趣吧**

**みんなとなら乗りこえられる**

**只要大伙儿同在 就能跨越难关**

**これからなんだねお互いがんばろうよ**

**现在才正要开始 彼此互相加油吧**

**どんな未来かは 誰もまだ知らない**

**那是个任谁也不会知晓的未来**

**でも楽しくしたホントに**

**不过真心期望能够充满着乐趣**

**みんなとなら無理したくなる**

**只要大伙儿同在 就会想将顾虑抛诸脑后**

**成長したいなまだまだ未熟DREAMER**

**愿能有所成长 如今还只是尚未成熟的梦想家**

 ![](https://cdn.luogu.com.cn/upload/pic/4493.png) 

Aqours的成员终于到齐了。


今天，是我们全员在一起的第一场演唱会。


大家都好好练习过了，相信一定会表现得很出色的。


不过，每个人的唱功也要尽量地接近才可以呢，如果太突出或者太落后，也是会影响表现的样子。


所以我们从隔壁的学园都市借来了一个发明，可以改变我们成员的唱功呢。

## 题目描述

我们Aqours的成员共有N+1人，他们会列成一队。

他们的唱功以A[0]到A[N]表示，A[i]$(0\le i \le N)$均给出。

学园都市的机器可以改变队列中连续多个成员的唱功值，并将其加上一个数Z，当然当Z是负数的时候就变成减去了。

我打算一共使用这个机器Q次，每次把第X到第Y号（$1\le X,Y\le10^6$）的成员都加上Z点唱功值。

而我们队伍的魅力值B，是这么算的：

一开始B=0，然后从第1号到第N号成员，

- 当$A_{i-1}<A_i$：$B = B-S\cdot|A_{i-1} - A_i|$
- 当$A_{i-1}>A_i$：$B = B+T\cdot|A_{i-1} - A_i|$
其中S和T是LoveLive组委会给我们的常数。

果然，我是バカチカ（笨蛋千歌）呢，所以作为领导我永远排在队伍的开头，唱功永远是0，机器也不会改到我头上呢。

你能帮我们算算，我**每次**使用完这个机器之后，成员的魅力B是多少吗？

## 输入格式

第一行4个整数，N，Q，S，T，各个变量在描述中已经解释

接下来N+1行，每行一个数整数Ai，其中A0=0

接下来Q行，每行3个整数，X，Y，Z各个变量在描述中已经解释

## 输出格式

Q个整数，表示答案。

## 样例

### 样例输入 #1
```
4 3 2 3
0
5
2
4
6
1 2 1
3 4 -3
1 4 2

```
### 样例输出 #1
```
-9
-1
-5

```
## 提示

30% 的数据 $N,Q\le 2000$,

另外20% 的数据 $S=T$

100%的数据 $N,Q\le 200000$；$1\le S,T,A_i\le10^6$；$|Z|\le 10^6$
请注意可能需要使用int64，cin/cout可能超时。

样例解释：

第一次变化后，

A 0 6 3 4 6

B -12 -3 -5 -9


#### 以下是彩蛋

没有。

哪来的那么多彩蛋？



---

---
title: "数据结构"
layout: "post"
diff: 普及/提高-
pid: P3948
tag: ['线段树', '树状数组', '前缀和', '差分']
---
# 数据结构
## 题目背景

**引言**

数据结构学的好，未来工作没烦恼。

![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999\_10000&sec=1508946101936&di=0c08b703e466d2a3b2d20dd8008821fc&imgtype=0&src=http%3A%2F%2Fjoymepic.joyme.com%2Farticle%2Fuploads%2Fallimg%2F201511%2F1446516425349678.gif)


Edgration 是一个喜欢乱搞数据结构的蒟蒻（以下简称edt），有一天，他作死想去刁难一下dalao：

edt想求一种数据结构，使得可以实现区间加，求出某一区间大于k的元素的个数

dalao1：sb线段树

dalao2：sb分块

dalao3：sb平衡树

edt: 不行，那就加上取模，求区间取膜mod后大于MIN小于MAX的元素个数

dalao1：线段树&……￥#&……%……&\*&%￥

dalao2：sb分块 &%￥……%#￥#&……&\*

dalao3：\*&……%&￥LCT维护SBT水题 &……%&……%

edt：那不仅取模，每个数乘上数组下标再取模

dalao：￥%￥￥&\*（#￥% 叽里呱啦叽里呱啦

edt：不行，在把取模的值丢到一棵树上，维护一棵仙人掌乘积方差的最小极差

dalao：替罪羊树上用sb块状链表维护Toptree上的最小费用最大流和可持久化仙人掌，算出来在基尔霍夫矩阵中反演后跑一遍fft维护的插头DP就好了，给我三分钟轻松水过。。

edt：mmp

## 题目描述

蒟蒻Edt把这个问题交给了你 ———— 一个精通数据结构的大犇，由于是第一题，这个题没那么难。。


edt 现在对于题目进行了如下的简化：


最开始的数组每个元素都是0


给出$n$，$opt$，$mod$，$min$，$max$，$mod$在int范围内


操作$A$，$Q$


$A$: $L$,$R$,$X$ 表示把$[l,R]$这个区间加上$X$

**（数组的从L到R的每个元素都加上X）**


$Q$: $L$,$R$ 表示询问$[L,R]$这个区间中元素T满足  $min<=(T*i$%$ mod)<=max$  的 T这样的数的个数（i是数组下标）

**（元素的值\*数组下标%mod在min到max范围内）**


由于 edt 请来了一位非三次元的仓鼠，他帮你用延后了部分问题，将这些询问打入了混乱时空，你的询问操作不会超过1000次，不幸的是，对于延后的询问操作可能有很多次（小于1e7次），但是保证这些延后的询问操作之后不会再次有修改操作

（就是在最后会有很多次询问，但不会进行修改）

## 输入格式

给出n，opt，mod，min，max表示序列大小，操作次数，取膜，最小值，最大值


下面opt行，给出


$A$: $L$，$R$，$X$表示区间加，保证X在int范围内(<2147483647）


$Q$：$L$，$R$表示区间查询满足条件的个数


再给出一个$Final$值，表示后面有$Final$个询问


下面$Final$行，给出


$L$，$R$表示询问区间$[L,R]$表示询问$[L,R]$之间满足条件的个数

## 输出格式

每行对于每个$Q$操作输出$Q$个数表示每次询问的值，


下面$Final$行表示$Final$个询问的值

## 样例

### 样例输入 #1
```
3 2 4 0 2
A 1 3 5
Q 2 3 
5
1 3
2 3
1 1 
2 2 
3 3

```
### 样例输出 #1
```
1
2
1
1
1
0

```
### 样例输入 #2
```
17 25 4098 310 2622
A 10 16 657212040
A 4 15 229489140
A 1 2 -433239891
A 3 12 532385784
A 10 17 56266644
A 8 10 10038874
A 6 9 13084764
A 4 5 -9206340
Q 2 8
A 2 4 -43223955
A 6 9 31478706
A 2 4 189818310
A 2 8 179421180
A 2 8 40354938
Q 8 14
A 3 6 57229575
A 6 13 132795740
A 2 17 14558022
A 14 15 -552674185
A 5 11 -1104138
Q 2 12
Q 1 14
A 3 9 524902182
A 8 12 114291440
A 3 7 107531442
1
11 12

```
### 样例输出 #2
```
3
6
7
8
2

```
### 样例输入 #3
```
20 3 4317 1020 2232
A 8 15 -434078222
A 1 2 54988154
A 13 19 81757858
15
7 11
3 5
3 9
6 9
9 13
6 19
1 20
3 5
3 10
1 7
2 14
6 10
2 3
2 3
10 12

```
### 样例输出 #3
```
0
0
0
0
0
2
2
0
0
0
0
0
0
0
0

```
## 提示

## 样例说明

给出样例1的解释：

样例1中，$a$数组修改为$5$，$5$，$5$

每个$a[i]*i$%$4$ 的值为$1$,$2$,$3$

对于Final的询问

询问$[1$，$3]$中大于等于0小于等于2的个数为2个

剩下的询问类似

## 题目说明

**注意**：

### 1.关于负数取模问题，请以 c++ 的向0取整为标准，即如：

[ $ -7 $%$ 3 = -1 $ ]  [ $ 7 $%$ 3 = 1 $ ]

### 2.一共会有50个测试点，每个点分值为2分。

因为测试点数较多，请oier们自觉地不要故意多次提交来卡评测机，出题人 edt 在这里表示由衷的感谢

## 数据范围

如果你不能作对所有点，请尝试获得部分分，所有数据都是随机生成

![](https://cdn.luogu.com.cn/upload/image_hosting/whf39g4d.png)


---

---
title: "[USACO20FEB] Timeline G"
layout: "post"
diff: 普及/提高-
pid: P6145
tag: ['图论', '2020', 'USACO', '拓扑排序', '差分约束']
---
# [USACO20FEB] Timeline G
## 题目描述

Bessie 在过去的 $M$ 天内参加了 $N$ 次挤奶。但她已经忘了她每次挤奶是在哪个时候了。

对于第 $i$ 次挤奶，Bessie 记得它不早于第 $S_i$ 天进行。另外，她还有 $C$ 条记忆，每条记忆形如一个三元组 $(a,b,x)$，含义是第 $b$ 次挤奶在第 $a$ 次挤奶结束至少 $x$ 天后进行。

现在请你帮 Bessie 算出在满足所有条件的前提下，每次挤奶的最早日期。

保证 Bessie 的记忆没有错误，这意味着一定存在一种合法的方案，使得：

- 第 $i$ 次挤奶不早于第 $S_i$ 天进行，且不晚于第 $M$ 天进行；
- 所有的记忆都得到满足；
## 输入格式

第一行三个整数 $N,M,C$。保证 $1 \leq N,C \leq 10^5$，$2 \leq M \leq 10^9$。

接下来一行包含 $N$ 个整数 $S_1, S_2 , \ldots, S_n$，保证 $\forall 1 \leq i \leq n$，都满足 $1 \leq S_i \leq M$。

下面 $C$ 行每行三个整数 $a,b,x$，描述一条记忆。保证 $a \neq b$，且 $1 \leq x \leq M$。
## 输出格式

输出 $N$ 行，每行一个整数，第 $i$ 行的数表示第 $i$ 次挤奶的最早日期。
## 样例

### 样例输入 #1
```
4 10 3
1 2 3 4
1 2 5
2 4 2
3 4 4
```
### 样例输出 #1
```
1
6
3
8
```
## 提示

- 测试点 $2 \sim 4$ 满足 $N,C \leq 10^3$。
- 测试点 $5 \sim 10$ 没有特殊限制。


---

---
title: "[JOI 2021 Final] とてもたのしい家庭菜園 4 (Growing Vegetables is Fun 4)"
layout: "post"
diff: 普及/提高-
pid: P7404
tag: ['2021', 'O2优化', '差分', 'JOI（日本）']
---
# [JOI 2021 Final] とてもたのしい家庭菜園 4 (Growing Vegetables is Fun 4)
## 题目描述

给定一个长为 $N$ 的序列 $A_i$，你可以进行若干次操作：

- 选定一个区间 $[L,R]$，让这个区间里的数加 $1$。

设经过这若干次操作后的序列为 $B_i$，那么你需要让 $B_i$ 满足下面这个要求：

- 存在一个整数 $k \in [1,N]$，满足对于子序列 $A_1=\{B_1,B_2,\cdots,B_k\}$ 为严格递增序列，对于子序列 $A_2=\{B_k,B_{k+1},\cdots,B_N\}$ 为严格递减序列。

你想知道最少需要多少次操作才能满足上面这个要求。
## 输入格式

第一行一个整数 $N$ 代表序列长度。

第二行 $N$ 个整数 $A_i$ 代表序列。
## 输出格式

一行一个整数代表最小操作次数。
## 样例

### 样例输入 #1
```
5
3 2 2 3 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5
9 7 5 3 1
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
2
2021 2021
```
### 样例输出 #3
```
1
```
### 样例输入 #4
```
8
12 2 34 85 4 91 29 85
```
### 样例输出 #4
```
93
```
## 提示

#### 样例 1 解释

- 对 $[2,5]$ 进行操作，序列变为 $\{3,3,3,4,2\}$。
- 对 $[2,3]$ 进行操作，序列变为 $\{3,4,4,4,2\}$。
- 对 $[3,3]$ 进行操作，序列变为 $\{3,4,5,4,2\}$。

#### 样例 2 解释

序列已经满足要求，不需要操作。

#### 样例 3 解释

对区间 $[1,1]$ 或 $[2,2]$ 进行操作都可。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（40 pts）：$N \le 2000$。
- Subtask 2（60 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N \le 2 \times 10^5$，$1 \le A_i \le 10^9$。

#### 说明

翻译自 [The 20th Japanese Olympiad in Informatics Final Round A とてもたのしい家庭菜園 4 的英文翻译 Growing Vegetables is Fun 4](https://www.ioi-jp.org/joi/2020/2021-ho/2021-ho-t1-en.pdf)。


---

---
title: "[USACO21DEC]  Convoluted Intervals S"
layout: "post"
diff: 普及/提高-
pid: P7992
tag: ['数学', 'USACO', '2021', '前缀和', '差分']
---
# [USACO21DEC]  Convoluted Intervals S
## 题目描述

奶牛们正在努力尝试发明有趣的新游戏来玩。他们目前的工作之一与一组 $N$ 个区间（$1\le N\le 2\cdot 10^5$）有关，其中第 $i$ 个区间从数轴上的 $a_i$ 位置开始，并在位置 $b_i \geq a_i$ 结束。$a_i$ 和 $b_i$ 均为 $0 \ldots M$ 范围内的整数，其中 $1 \leq M \leq 5000$。

这个游戏的玩法是，Bessie 选择某个区间（假设是第 $i$ 个区间），而她的表妹 Elsie 选择某个区间（假设是第 $j$ 个区间，可能与 Bessie 所选的的区间相同）。给定某个值 $k$，如果 $a_i + a_j \leq k \leq b_i + b_j$，则她们获胜。

对范围 $0 \ldots 2M$ 内的每个值 $k$，请计算使得 Bessie 和 Elsie 可以赢得游戏的有序对 $(i,j)$ 的数量。
## 输入格式

输入的第一行包含 $N$ 和 $M$。以下 $N$ 行每行以整数 $a_i$ 和 $b_i$ 的形式描述一个区间。
## 输出格式

输出 $2M+1$ 行，依次包含范围 $0 \ldots 2M$ 中的每一个 $k$ 的答案。
## 样例

### 样例输入 #1
```
2 5
1 3
2 5
```
### 样例输出 #1
```
0
0
1
3
4
4
4
3
3
1
1

```
## 提示

【样例解释】

在这个例子中，对于 $k=3$，有三个有序对可以使得 Bessie 和 Elsie 获胜：$(1, 1)$，$(1, 2)$，和 $(2, 1)$。

【数据范围】

- 测试点 1-2 满足 $N\le 100, M\le 100$。
- 测试点 3-5 满足 $N\le 5000$。
- 测试点 6-20 没有额外限制。


---

---
title: "[蓝桥杯 2017 省 A] 油漆面积"
layout: "post"
diff: 普及/提高-
pid: P8648
tag: ['2017', '线段树', '扫描线', '差分', '蓝桥杯省赛']
---
# [蓝桥杯 2017 省 A] 油漆面积
## 题目描述

X 星球的一批考古机器人正在一片废墟上考古。

该区域的地面坚硬如石、平整如镜。

管理人员为方便，建立了标准的直角坐标系。

每个机器人都各有特长、身怀绝技。它们感兴趣的内容也不相同。

经过各种测量，每个机器人都会报告一个或多个矩形区域，作为优先考古的区域。

矩形的表示格式为 $(x_1,y_1,x_2,y_2)$，代表矩形的两个对角点坐标。

为了醒目，总部要求对所有机器人选中的矩形区域涂黄色油漆。

小明并不需要当油漆工，只是他需要计算一下，一共要耗费多少油漆。

其实这也不难，只要算出所有矩形覆盖的区域一共有多大面积就可以了。

注意，各个矩形间可能重叠。

本题的输入为若干矩形，要求输出其覆盖的总面积。

## 输入格式


第一行，一个整数 $n$，表示有多少个矩形 $(1 \le n<10000)$。

接下来的 $n$ 行，每行有 $4$ 个整数 $x_1$，$y_1$，$x_2$，$y_2$，空格分开，表示矩形的两个对角顶点坐标。

$(0 \le x_1,y_1,x_2,y_2 \le 10000)$。

## 输出格式

一行一个整数，表示矩形覆盖的总面积。
## 样例

### 样例输入 #1
```
3
1 5 10 10
3 1 20 20
2 7 15 17

```
### 样例输出 #1
```
340
```
### 样例输入 #2
```
3
5 2 10 6
2 7 12 10
8 1 15 15
```
### 样例输出 #2
```
128
```
## 提示

蓝桥杯 2022 省赛 A 组 J 题。


---

---
title: "「MXOI Round 1」涂色"
layout: "post"
diff: 普及/提高-
pid: P9583
tag: ['模拟', '洛谷原创', 'O2优化', '排序', '差分', '洛谷月赛']
---
# 「MXOI Round 1」涂色
## 题目描述

小 C 正在用彩铅给一张 $n$ 行 $m$ 列的方格纸涂色。初始时，所有方格都是空白的。

他一共要进行 $q$ 次涂色，每次涂色会选取一行或一列，给这一行或这一列的所有方格都添加 $1$ 层颜色。

小 C 喜欢浅色，所以他会在每次涂色结束后，把所有被涂上 $k$ 层颜色的方格的颜色都擦掉，让这些方格都变成空白的。

小 C 想知道，在最终共有多少方格被涂上了颜色。
## 输入格式

第一行四个整数 $n,m,q,k$。

接下来 $q$ 行，每行两个整数 $op,x$。

若 $op=1$，则表示给第 $x$ 行的所有方格都添加 $1$ 层颜色；  
若 $op=2$，则表示给第 $x$ 列的所有方格都添加 $1$ 层颜色。
## 输出格式

一个整数，表示在最终共有多少方格被涂上了颜色。
## 样例

### 样例输入 #1
```
3 4 5 3
1 3
2 4
1 2
1 3
2 2
```
### 样例输出 #1
```
8
```
## 提示

#### 【样例解释 #1】

第 $1$ 行第 $1$ 列的方格没有被涂上颜色，第 $1$ 行第 $2$ 列的方格被涂上了 $1$ 层颜色，第 $1$ 行第 $3$ 列的方格没有被涂上颜色，第 $1$ 行第 $4$ 列的方格被涂上了 $1$ 层颜色；

第 $2$ 行第 $1$ 列的方格被涂上了 $1$ 层颜色，第 $2$ 行第 $2$ 列的方格被涂上了 $2$ 层颜色，第 $2$ 行第 $3$ 列的方格被涂上了 $1$ 层颜色，第 $2$ 行第 $4$ 列的方格被涂上了 $2$ 层颜色；

第 $3$ 行第 $1$ 列的方格被涂上了 $2$ 层颜色，第 $3$ 行第 $2$ 列的方格的颜色被擦掉了，第 $3$ 行第 $3$ 列的方格被涂上了 $2$ 层颜色，第 $3$ 行第 $4$ 列的方格的颜色也被擦掉了；

最终，共有 $8$ 个方格被涂上了颜色。

#### 【样例 #2】

见附加文件中的 `paint/paint2.in` 与 `paint/paint2.ans`。

该样例满足测试点 $1$ 的限制。

#### 【样例 #3】

见附加文件中的 `paint/paint3.in` 与 `paint/paint3.ans`。

该样例满足测试点 $5$ 的限制。

#### 【样例 #4】

见附加文件中的 `paint/paint4.in` 与 `paint/paint4.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le n,m \le 2\times 10^5$，$1 \le k \le q \le 5 \times 10^5$，$op \in \{1,2\}$，保证当 $op=1$ 时 $1 \le x \le n$，当 $op=2$ 时 $1 \le x \le m$。

|测试点编号|$n,m \le$|$q \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1\sim4$|$3000$|$3000$|无|
|$5\sim9$|$3000$|$5\times10^5$|无|
|$10\sim12$|$2\times10^5$|$5\times10^5$|A|
|$13\sim16$|$2\times10^5$|$5\times10^5$|B|
|$17\sim20$|$2\times10^5$|$5\times10^5$|无|

特殊性质 A：保证 $op=1$。

特殊性质 B：保证 $k=2$。


---

