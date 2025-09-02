---
title: "[CCO 2022] Alternating Heights"
layout: "post"
diff: 普及/提高-
pid: P10050
tag: ['二分', '2022', 'CCO（加拿大）', '深度优先搜索 DFS', '图论建模', '双指针 two-pointer']
---
# [CCO 2022] Alternating Heights
## 题目描述

Troy 计划给 CCO 的学生拍一张合影，他向你寻求帮助。

有 $K$ 个学生，编号从 $1$ 到 $K$。Troy 忘记了学生的身高，但他记得没有两个学生的身高相同。

Troy 有一个序列 $A_{1}, A_{2}, \ldots, A_{N}$，表示合影中从左到右的学生顺序。一个学生可能在 $A$ 中出现多次。你不确定这张合影会怎么拍，但你不愿意认为 Troy 犯了错误。

Troy 会给你 $Q$ 个形式为 $x,y$ 的询问，每个询问为「给定学生序列 $A_{x}, A_{x+1}, \ldots, A_{y}$，他们的身高能否形成一个交替序列？」更具体地说，我们用 $h_i$ 表示第 $i$ 个学生的身高。如果存在一种身高分配$ h_1, h_2, \ldots, h_K$，使得 $h_{A_{x}}>h_{A_{x+1}}<h_{A_{x+2}}>h_{A_{x+3}}<\ldots h_{A_{y}}$，回答 `YES`；否则回答 `NO`。

注意，每个查询都是独立的：也就是说，询问 $i$ 的身高分配与询问 $j$ 的身高分配无关 $(i\neq j)$。
## 输入格式

第一行包含三个用空格分隔的整数 $N, K$ 和 $Q$。

第二行包含 $N$ 个整数，表示 $A_{1}, A_{2}, \ldots, A_{N}\left(1 \leq A_{i} \leq K\right)$。

接下来的 $Q$ 行，每行包含两个用空格分隔的整数 $x$ 和 $y (1 \leq x<y \leq N)$，表示一组查询。
## 输出格式

输出 $Q$ 行。第 $i$ 行，输出 `YES` 或者 `NO`，表示 Troy 的第 $i$ 个查询的答案。
## 样例

### 样例输入 #1
```
6 3 3
1 1 2 3 1 2
1 2
2 5
2 6
```
### 样例输出 #1
```
NO
YES
NO
```
## 提示

## 样例说明

对于第一个询问，不可能有 $h_1>h_1$，所以答案是 `NO`。

对于第二个询问，$h_1>h_2<h_3>h_1$ 的一种方案是 $h_1=160 \mathrm{~cm}, h_2=140 \mathrm{~cm}, h_3=180 \mathrm{~cm}$。另一种方案是 $h_1=1.55 \mathrm{~m}, h_2=1.473 \mathrm{~m}, h_3=1.81 \mathrm{~m}$。

对于第三个询问，不可能同时有 $h_1>h_2$ 和 $h_1<h_2$。

## 数据范围

对于所有的数据，有 $2 \leq N \leq 3000$，$2 \leq K \leq N$，$1 \leq Q \leq 10^{6}$。

子任务编号|	分值|	$N$|	$K$|	$Q$
:-:|:-:|:-:|:-:|:-:
$1$|	$16$|	$2 \leq N \leq 3000$|	$K=2$|	$1 \leq Q \leq 10^{6}$
$2$|	$24$|	$2 \leq N \leq 500$|	$2 \leq K \leq \min (N, 5)$|$1 \leq Q \leq 10^{6}$
$3$	|$28$|	$2 \leq N \leq 3000$	|$2 \leq K \leq N$	|$1 \leq Q \leq 2000$
$4$|	$32$| $2 \leq N \leq 3000$	|$2 \leq K \leq N$	|	$1 \leq Q \leq 10^{6}$


---

---
title: "[GESP202403 七级] 交流问题"
layout: "post"
diff: 普及/提高-
pid: P10378
tag: ['图论', '2024', '图论建模', '二分图', 'GESP']
---
# [GESP202403 七级] 交流问题
## 题目描述

来自两所学校 $A$、$B$ 的 $n$ 名同学聚在一起相互交流。为了方便起见，我们把这些同学从 $1$ 至 $n$ 编号。他们共进行了 $m$ 次交流，第 $i$ 次交流中，编号为 $u_i, v_i$ 的同学相互探讨了他们感兴趣的话题，并结交成为了新的朋友。

由于这次交流会的目的是促进两校友谊，因此只有不同学校的同学之间会交流。同校同学并不会互相交流。

作为 $A$ 校顾问，你对 $B$ 校的规模非常感兴趣，你希望求出 $B$ 校至少有几名同学、至多有几名同学。
## 输入格式

第一行两个正整数，表示同学的人数 $n$、交流的次数 $m$。  
接下来 $m$ 行，每行两个整数 $u_i, v_i$，表示一次交流。  
## 输出格式

输出一行两个整数，用单个空格隔开，分别表示 $B$ 校至少有几名同学、至多有几名同学。
## 样例

### 样例输入 #1
```
4 3
1 2
2 3
4 2

```
### 样例输出 #1
```
1 3
```
### 样例输入 #2
```
7 5
1 2
2 3
4 2
5 6
6 7

```
### 样例输出 #2
```
2 5
```
## 提示

### 数据规模与约定

- 对 $30\%$ 的数据，保证 $n \leq 17$，$m \leq 50$。
- 对 $60\%$ 的数据，保证 $n \leq 500$，$m \leq 2000$。
- 对全部的测试数据，保证 $1 \leq u_i, v_i \leq n \leq 10^5$，$1 \leq m \leq 2\times 10^5$，输入是合法的，即交流一定是跨校开展的。


---

---
title: "[GESP202412 八级] 排队"
layout: "post"
diff: 普及/提高-
pid: P11380
tag: ['图论', '2024', '数论', '图论建模', '组合数学', '排列组合', 'GESP']
---
# [GESP202412 八级] 排队
## 题目描述

小杨所在班级共有 $n$ 位同学，依次以 $1,2,\dots,n$ 标号。这 $n$ 位同学想排成一行队伍，其中有些同学之间关系非常好，在队伍里需要排在相邻的位置。具体来说，有 $m$ 对这样的关系（$m$ 是一个非负整数）。当 $m\geq 1$ 时，第 $i$ 对关系（$1\leq i\leq m$）给出 $a_i,b_i$，表示排队时编号为 $a_i$ 的同学需要排在编号为 $b_i$ 的同学前面，并且两人在队伍中相邻。

现在小杨想知道总共有多少种排队方式。由于答案可能很大，你只需要求出答案对 $10^9+7$ 取模的结果。
## 输入格式

第一行，两个整数 $n,m$，分别表示同学们的数量与关系数量。

接下来 $m$ 行，每行两个整数 $a_i,b_i$，表示一对关系。
## 输出格式

一行，一个整数，表示答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
4 2
1 3
2 4
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 0
```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
3 2
1 2
2 1
```
### 样例输出 #3
```
0
```
## 提示

对于 $20\%$ 的测试数据点，保证 $1\leq n\leq 8$，$0\leq m\leq 10$。

对于另外 $20\%$ 的测试数据点，保证 $1\leq n\leq 10^3$，$0\leq m\leq 1$。

对于所有测试数据点，保证 $1\leq n\leq 2\times 10^5$，$0\leq m\leq 2\times 10^5$。


---

---
title: "[KOI 2023 Round 2] 湖边的蚁穴"
layout: "post"
diff: 普及/提高-
pid: P12663
tag: ['贪心', '2023', '图论建模', 'KOI（韩国）']
---
# [KOI 2023 Round 2] 湖边的蚁穴
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

KOI 湖畔有一个蚂蚁们聚居的蚁穴。这个蚁穴沿着圆形湖泊的边缘，环形地依次排列着从 $1$ 到 $N$ 编号的 $N$ 个房间。对于所有满足 $1 \leq i \leq N - 1$ 的 $i$，第 $i$ 个房间与第 $i + 1$ 个房间之间，以及第 $N$ 个房间与第 $1$ 个房间之间都通过通道直接连接。

但由于各种原因，从某些房间开始分出了若干个小房间。现在，对于所有满足 $1 \leq i \leq N$ 的 $i$，蚁穴中的第 $i$ 个房间通过通道直接连接着 $C_i$ 个小房间。与第 $i$ 个房间连接的小房间不会与其他任何房间相连。

例如，若 $N = 7$ 且 $C = [3, 0, 0, 1, 0, 2, 0]$，蚁穴的结构如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/57hzt6bh.png)

蚁穴中的每个房间与小房间最多只能住一只蚂蚁。如果通道直接连接的两个位置（房间或小房间）中都住着蚂蚁，那么这两只蚂蚁会感到不舒服。为了避免这种不适，当前蚁穴的每条通道最多只能连接一只住着蚂蚁的位置。

蚂蚁们非常聪明，因此在上述条件允许的情况下，它们总是设法使蚁穴中居住的蚂蚁数量最大。现在给出蚁穴的结构，请编写一个程序，计算最多有多少只蚂蚁可以住在蚁穴中。
## 输入格式

第一行输入一个整数 $N$。  
第二行输入 $C_1, C_2, \dots, C_N$，表示每个房间连接的小房间数量，整数之间以空格分隔。
## 输出格式

输出一个整数，表示最多可以居住在蚁穴中的蚂蚁数量。

## 样例

### 样例输入 #1
```
4
1 0 1 0
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
4
1 1 1 1
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
2
0 0
```
### 样例输出 #3
```
1
```
### 样例输入 #4
```
7
3 0 0 1 0 2 0
```
### 样例输出 #4
```
9
```
## 提示

**限制条件**

- 所有给定的数均为整数。
- $2 \leq N \leq 250\,000$
- $0 \leq C_i \leq 10^{12} \quad (1 \leq i \leq N)$

**子任务**

1. （4 分）$N = 2$  
2. （8 分）$N \leq 1\,000$ 且 $C_i = 0 \quad (1 \leq i \leq N)$  
3. （14 分）$N \leq 1\,000$ 且 $C_i \leq 1 \quad (1 \leq i \leq N)$  
4. （15 分）$N \leq 1\,000$  
5. （20 分）$C_i \leq 1 \quad (1 \leq i \leq N)$  
6. （13 分）$C_i \leq 1\,000 \quad (1 \leq i \leq N)$  
7. （9 分）$C_i \geq 1 \quad (1 \leq i \leq N)$  
8. （17 分）无附加限制

翻译由 ChatGPT-4o 完成


---

---
title: "图的遍历"
layout: "post"
diff: 普及/提高-
pid: P3916
tag: ['搜索', '图论', '图论建模', '强连通分量']
---
# 图的遍历
## 题目描述

给出 $N$ 个点，$M$ 条边的有向图，对于每个点 $v$，求 $A(v)$ 表示从点 $v$ 出发，能到达的编号最大的点。
## 输入格式

第 $1$ 行 $2$ 个整数 $N,M$，表示点数和边数。

接下来 $M$ 行，每行 $2$ 个整数 $U_i,V_i$，表示边 $(U_i,V_i)$。点用 $1,2,\dots,N$ 编号。
## 输出格式

一行 $N$ 个整数 $A(1),A(2),\dots,A(N)$。
## 样例

### 样例输入 #1
```
4 3
1 2
2 4
4 3
```
### 样例输出 #1
```
4 4 3 4
```
## 提示

- 对于 $60\%$ 的数据，$1 \leq N,M \leq 10^3$。
- 对于 $100\%$ 的数据，$1 \leq N,M \leq 10^5$。


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
title: "[蓝桥杯 2018 国 C] 迷宫与陷阱"
layout: "post"
diff: 普及/提高-
pid: P8673
tag: ['2018', '广度优先搜索 BFS', '图论建模', '蓝桥杯国赛']
---
# [蓝桥杯 2018 国 C] 迷宫与陷阱
## 题目描述

小明在玩一款迷宫游戏，在游戏中他要控制自己的角色离开一间由 $N \times N$ 个格子组成的二维迷宫。

小明的起始位置在左上角，他需要到达右下角的格子才能离开迷宫。

每一步，他可以移动到上下左右相邻的格子中（前提是目标格子可以经过）。

迷宫中有些格子小明可以经过，我们用 `.` 表示；

有些格子是墙壁，小明不能经过，我们用 `#` 表示。

此外，有些格子上有陷阱，我们用 `X` 表示。除非小明处于无敌状态，否则不能经过。

有些格子上有无敌道具，我们用 `%` 表示。

当小明第一次到达该格子时，自动获得无敌状态，无敌状态会持续 $K$ 步。

之后如果再次到达该格子不会获得无敌状态了。

处于无敌状态时，可以经过有陷阱的格子，但是不会拆除 / 毁坏陷阱，即陷阱仍会阻止没有无敌状态的角色经过。

给定迷宫，请你计算小明最少经过几步可以离开迷宫。
## 输入格式

第一行包含两个整数 $N$ 和 $K$。$(1 \le N \le 1000，1 \le K \le 10)$。

以下 $N$ 行包含一个 $N\times N$ 的矩阵。

矩阵保证左上角和右下角是 `.`。
## 输出格式

一个整数表示答案。如果小明不能离开迷宫，输出 $-1$。
## 样例

### 样例输入 #1
```
5 3
...XX
##%#.
...#.
.###.
.....
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
5 1
...XX
##%#.
...#.
.###.
.....
```
### 样例输出 #2
```
12
```
## 提示

时限 3 秒, 256M。蓝桥杯 2018 年第九届国赛


---

