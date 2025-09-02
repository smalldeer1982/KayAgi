---
title: "[USACO24FEB] Milk Exchange B"
layout: "post"
diff: 普及+/提高
pid: P10188
tag: ['数学', 'USACO', '2024', 'O2优化', '图论建模']
---
# [USACO24FEB] Milk Exchange B
## 题目描述

Farmer John 的 $N$（$1\le N\le 2\cdot 10^5$）头奶牛排成一圈，使得对于 $1,2,\ldots,N−1$ 中的每个 $i$，奶牛 $i$ 右边的奶牛是奶牛 $i+1$，而奶牛 $N$ 右边的奶牛是奶牛 $1$。第 $i$ 头奶牛有一个容量为整数 $a_i$（$1\le a_i\le 10^9$）升的桶。所有桶初始时都是满的。

每一分钟，奶牛都会根据一个字符串 $s_1s_2\ldots s_N$
传递牛奶，该字符串仅由字符 `L` 和 `R` 组成。当第 $i$ 头奶牛至少有 $1$ 升牛奶时，如果 $s_i=\texttt{L}$，她会将 $1$ 升牛奶传递给她左边的奶牛，如果 $s_i=\texttt R$ 则传递给右边的奶牛。所有交换同时发生（即，如果一头奶牛的桶是满的，送出一升牛奶，但也收到一升，则她的牛奶量保持不变）。如果此时一头奶牛的牛奶量超过 $a_i$，则多余的牛奶会损失。

FJ 想要知道：经过 $M$ 分钟（$1\le M\le 10^9$）后，所有奶牛总共还余下多少牛奶？ 
## 输入格式

输入的第一行包含 $N$ 和 $M$。

第二行包含一个字符串 $s_1s_2\ldots s_N$，仅由字符 `L` 或 `R` 组成，表示每头奶牛传递牛奶的方向。

第三行包含整数 $a_1,a_2,\ldots,a_N$，为每个桶的容量。 
## 输出格式

输出一个整数，为 $M$ 分钟后所有奶牛总共余下的牛奶量。 

**注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C/C++ 中的 `long long`）。**
## 样例

### 样例输入 #1
```
3 1
RRL
1 1 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5 20
LLLLL
3 3 2 3 3
```
### 样例输出 #2
```
14
```
### 样例输入 #3
```
9 5
RRRLRRLLR
5 8 4 9 3 4 9 5 4
```
### 样例输出 #3
```
38
```
## 提示

### 样例解释 1

奶牛 $2$ 和 $3$ 互相传递一升牛奶，因此她们的牛奶得以保留。当奶牛 $1$ 将牛奶传递给奶牛 $2$ 时，奶牛 $2$ 的桶会溢出，从而一分钟后损失了一升牛奶。 

### 样例解释 2

 每头奶牛都将一升牛奶传递给左边的奶牛，并从右边的奶牛那里获得一升牛奶，因此无论经过多长时间所有牛奶都会被保留下来。 
 
### 样例解释 3

初始时，共有 $51$ 升牛奶。$5$ 分钟后，奶牛 $3$，$6$ 和 $7$ 将分别损失 $5$，$3$ 和 $5$ 升牛奶。因此，总共还剩下 $38$ 升牛奶。

### 测试点性质

- 测试点 $4-8$：$N,M\le 1000$。
- 测试点 $9-16$：没有额外限制。


---

---
title: "[USACO24OPEN] Bessie's Interview S"
layout: "post"
diff: 普及+/提高
pid: P10277
tag: ['USACO', '堆', '2024', '图论建模']
---
# [USACO24OPEN] Bessie's Interview S
## 题目描述

Bessie 正在寻找新工作！幸运的是，$K$ 名农夫目前正在招聘并举行面试。由于工作竞争激烈，农夫们决定按申请的顺序对奶牛进行编号和面试。有 $N$ 头奶牛在 Bessie 之前申请，因此她的编号为 $N+1$（$1\le K\le N\le 3\cdot 10^5$）。

面试过程如下。在时刻 $0$，对于每一个 $1\le i\le K$，农夫 $i$ 将开始面试奶牛 $i$。一旦一名农夫完成面试，他将立刻开始面试队列中的下一头奶牛。如果多名农夫同时完成，下一头奶牛可以根据自己的偏好选择接受任一此时空闲的农夫的面试。

对于每一个 $1\le i\le N$，Bessie 已经知道奶牛 $i$ 的面试将恰好花费 $t_i$ 分钟（$1\le t_i\le 10^9$）。然而，她不知道每头奶牛对农夫的偏好。

由于这份工作对 Bessie 来说非常重要，所以她想要认真准备面试。为此，她需要知道她会在何时接受面试，以及哪些农夫可能会面试她。帮助她求出这些信息！ 
## 输入格式

输入的第一行包含两个整数 $N$ 和 $K$。

第二行包含 $N$ 个整数 $t_1\ldots t_N$。 
## 输出格式

输出的第一行包含 Bessie 的面试将开始的时刻。

第二行包含一个长为 $K$ 的 `01` 字符串，其中如果农夫 $i$ 可能面试 Bessie 则第 $i$ 个字符为 `1`，否则为 `0`。 
## 样例

### 样例输入 #1
```
6 3
3 1 4159 2 6 5
```
### 样例输出 #1
```
8
110
```
## 提示

### 样例解释 1

除了 Bessie 之外有 $6$ 头奶牛，以及 $3$ 名农夫。面试过程将如下进行：

1. 于时刻 $t=0$，农夫 $1$ 面试奶牛 $1$，农夫 $2$ 面试奶牛 $2$，农夫 $3$ 面试奶牛 $3$。
2. 于时刻 $t=1$，农夫 $2$ 结束了对奶牛 $2$ 的面试并开始面试奶牛 $4$。
3. 于时刻 $t=3$，农夫 $1$ 和农夫 $2$ 都完成了面试，从而有两种可能：
    * 农夫 $1$ 面试奶牛 $5$，农夫 $2$ 面试奶牛 $6$。在这种情况下，农夫 $2$ 将于时刻 $t=8$ 完成面试并开始面试 Bessie。
    * 农夫 $1$ 面试奶牛 $6$，农夫 $2$ 面试奶牛 $5$。在这种情况下，农夫 $1$ 将于时刻 $t=8$ 完成面试并开始面试 Bessie。

从而，Bessie 的面试将于时刻 $t=8$ 开始，并且她可能会被农夫 $1$ 或农夫 $2$ 面试。

### 测试点性质

- 测试点 $2-3$：没有两名农夫同时完成面试。
- 测试点 $4-9$：$N\le 3\cdot 10^3$。
- 测试点 $10-21$：没有额外限制。


---

---
title: "[USACO25OPEN] Compatible Pairs S"
layout: "post"
diff: 普及+/提高
pid: P12026
tag: ['图论', '贪心', 'USACO', '2025', '图论建模', '拓扑排序']
---
# [USACO25OPEN] Compatible Pairs S
## 题目描述

在遥远的乡村，农夫约翰的奶牛并非普通的农场动物——它们隶属于一个秘密的奶牛情报网络。每头奶牛都有一个由精英密码学家精心分配的ID号码。但由于农夫约翰随意的标记系统，部分奶牛出现了重复ID的情况。

农夫约翰记录到共有 $N$（$1\le N\le 2\cdot 10^5$）个不同的ID号码，对于每个唯一ID $d_i$（$0\le d_i\le 10^9$），有 $n_i$（$1\le n_i\le 10^9$）头奶牛共享该ID。

奶牛们只能成对交流，它们的加密通信有一个严格规则：两头奶牛仅当不是同一头牛且它们的ID号码之和等于 $A$ 或 $B$（$0\le A\le B\le 2\cdot 10^9$）时才能交换信息。每头奶牛同一时间只能参与一次对话（即不能同时属于多对通信组合）。

农夫约翰希望最大化互不干扰的通信对数来确保最佳信息流通。你能计算出最多可以同时建立多少对通信吗？

## 输入格式

第一行包含 $N$、$A$、$B$。
接下来 $N$ 行每行包含 $n_i$ 和 $d_i$。所有 $d_i$ 均不相同。

## 输出格式

可同时建立的最大互不干扰通信对数。
注意：由于涉及大整数运算，可能需要使用 64 位整数类型（如C/C++中的 `long long`）。
## 样例

### 样例输入 #1
```
4 4 5
17 2
100 0
10 1
200 4
```
### 样例输出 #1
```
118
```
## 提示

解释：
ID为 $0$ 的奶牛可与 ID 为 $4$ 奶牛通信（ID 之和为 $4$）。由于共有 $100$ 头 ID $0$ 的奶牛和 $200$ 头 ID $4$ 的奶牛，最多可组成 $100$ 对通信组合。

ID 为 $4$ 的奶牛还可与 ID 为 $1$ 的奶牛通信（ID 之和为$5$）。此时剩余 $100$ 头 ID $4$ 的奶牛和 $10$ 头 ID $1$ 的奶牛可组成 $10$ 对通信组合。

最后，ID 为 $2$ 的奶牛可与其他同 ID 奶牛通信。$17$ 头 ID $2$ 的奶牛最多可组成 $8$ 对通信组合（$\lfloor17/2\rfloor=8$）。

总计 $100+10+8=118$ 对通信组合，可以证明这是最大可能值。

- 测试点 $3\sim4$：$A=B$。
- 测试点 $5\sim7$：$N\le 1000$。
- 测试点 $8\sim12$：无额外限制。


---

---
title: "[蓝桥杯 2024 国 Python B] 工厂"
layout: "post"
diff: 普及+/提高
pid: P12275
tag: ['贪心', '2024', 'Special Judge', '图论建模', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Python B] 工厂
## 题目描述

H 市是一座制造业十分发达的城市。在 H 市中，工厂可以生产 $n$ 种不同的物品，部分物品都可以以特定的价格 $a_i$ 在市场上售出而带来收益。生产方式分为两类，使用第一类生产方式每个工人可以在一天时间内生产若干件物品 $y$。使用第二类生产方式，每个工人可以在一天时间内使用若干件物品 $x$ 生产若干件物品 $y$，其中 $x \leq y$，即只能将编号较小的物品加工成编号较大的物品。

小蓝作为 H 市的市长自然希望能够最大化收益，由于 H 市的人口非常多，你只需要帮她计算出平均一天内每个工人能够获得的最大收益即可。
## 输入格式

输入的第一行包含两个正整数 $n, m$，用一个空格分隔，其中 $n$ 表示物品种数，$m$ 表示生产方式总数。

第二行包含 $n$ 个正整数 $a_i$，相邻整数之间使用一个空格分隔，表示物品的售价，若 $a_i = 0$ 则表示这种物品无法在市场上售出。

接下来 $m$ 行，每行包含四个非负整数 $x_i, y_i, k_i, w_i$，相邻整数之间使用一个空格分隔，表示一个工人可以在一天时间内使用 $k_i$ 件物品 $x_i$ 生产 $w_i$ 件物品 $y_i$。特殊地，如果 $k_i = 0$（此时 $x_i$ 不一定为 $0$，请忽略 $x_i$ 的值）则表示该种生产方式是第一类生产方式，不需要原材料。
## 输出格式

输出一行包含一个实数，四舍五入保留正好两位小数，表示平均每个工人在一天时间内能够获得的最大收益。
## 样例

### 样例输入 #1
```
3 3
1 0 2
1 1 0 6
1 2 5 10
2 3 6 10
```
### 样例输出 #1
```
9.52
```
## 提示

### 样例说明

$1$ 个工人可以在一天时间内生产 $6$ 份小麦，或者将 $5$ 份小麦加工成 $10$ 份面粉，或者将 $6$ 份面粉加工成 $10$ 份饼干。

那么最理想的情况是 $5$ 个工人生产小麦，$6$ 个工人将小麦加工成面粉，$10$ 个工人将面粉加工成饼干后在市场上以 $2$ 的价格出售。

此时需要 $21$ 个工人生产，共能获得 $200$ 的收益。平均每个工人一天时间内获得的收益约为 $9.52$。

### 评测用例规模与约定

- 对于 $50\%$ 的评测用例，$1 \leq n, m \leq 300$，$w_i = 1$，$0 \leq k_i \leq 1$；
- 另存在 $20\%$ 的评测用例，$x_i = y_i$；
- 对于所有评测用例，$1 \leq n, m \leq 300000$，$0 \leq a_i \leq 10^6$，$1 \leq w_i \leq 10$，$0 \leq k_i \leq 10$，$1 \leq x_i \leq y_i \leq n$。保证数据中至少存在一个 $k_i = 0$。


---

---
title: "[KOI 2024 Round 2] 收集彩球"
layout: "post"
diff: 普及+/提高
pid: P12649
tag: ['图论', '2024', '图论建模', 'KOI（韩国）']
---
# [KOI 2024 Round 2] 收集彩球
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

现在有 $2N$ 个彩球和 $N + 1$ 个盒子。彩球的颜色为 $1, 2, \dots, N$ 中的某一个。对于每种颜色，恰好有两个彩球被涂成该颜色。每个盒子最多可以容纳两个彩球。

最开始，第 $1$ 到第 $N$ 个盒子中每个盒子内都放有两个彩球，第 $N + 1$ 个盒子是空的。第 $i$ 个盒子中，最上面那个彩球的颜色为 $A_i$，下面那个彩球的颜色为 $B_i$。

你可以将一个盒子顶部的彩球取出，放入另一个盒子的顶部，完成一次移动操作。

你的目标是使得每种颜色的两个彩球都被放入同一个盒子中。每次移动操作必须满足下列两个条件之一：

- 被放入彩球的目标盒子是空的；
- 被放入彩球的目标盒子中恰好已有一个彩球，并且该彩球与被放入的彩球颜色相同。

请你编写程序，计算为了实现目标——使每种颜色的两个彩球在同一个盒子中，所需的最小移动次数。如果无法实现目标，请输出 $-1$。
## 输入格式

第一行输入一个整数 $N$。  
接下来的 $N$ 行中，第 $i$ 行输入两个整数 $A_i$ 和 $B_i$，以空格分隔，表示第 $i$ 个盒子中从上到下的两个彩球的颜色。
## 输出格式

如果存在解决方案，输出最小的移动次数；如果不存在解决方案，输出 $-1$。

## 样例

### 样例输入 #1
```
5
4 1
3 5
2 4
3 2
5 1
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
2
1 1
2 2
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
4
2 1
3 1
2 4
3 4
```
### 样例输出 #3
```
-1
```
## 提示

**样例 1 说明**

![](https://cdn.luogu.com.cn/upload/image_hosting/jm5qt4kg.png)

可以按照如下步骤完成：
1. 将第 4 号盒子中的颜色为 $3$ 的球移动到第 6 号盒子；
2. 将第 3 号盒子中的颜色为 $2$ 的球移动到第 4 号盒子；
3. 将第 1 号盒子中的颜色为 $4$ 的球移动到第 3 号盒子；
4. 将第 2 号盒子中的颜色为 $3$ 的球移动到第 6 号盒子；
5. 将第 5 号盒子中的颜色为 $5$ 的球移动到第 2 号盒子；
6. 将第 5 号盒子中的颜色为 $1$ 的球移动到第 1 号盒子。

**约束条件**

- 所有输入均为整数。
- $1 \leq N \leq 200\,000$
- $1 \leq A_i, B_i \leq N$
- 对于每个 $1 \leq i \leq N$，$A_1, A_2, \dots, A_N, B_1, B_2, \dots, B_N$ 中恰好有两个数等于 $i$。

**子问题**

1. （2 分）$N \leq 2$  
2. （23 分）$N \leq 20$  
3. （15 分）存在使所有同色彩球放入同一盒子的方法  
4. （15 分）$N \leq 2\,000$  
5. （45 分）无附加限制条件

翻译由 ChatGPT-4o 完成


---

---
title: "[NOI2025] 机器人"
layout: "post"
diff: 普及+/提高
pid: P13271
tag: ['图论', '2025', 'NOI', '图论建模', '最短路']
---
# [NOI2025] 机器人
## 题目描述

NOI2025 正在绍兴举办，小 Y 为闭幕式表演制作了一个机器人并打算操控它从仓库走到礼堂。

绍兴的道路系统可以简化为 $n$ 个路口以及连接这些路口的 $m$ 条 **单行道路**，且每条道路有一定的长度。为了方便将道路系统录入机器人的芯片，小 Y 对每一个路口连接的所有道路进行了编号。具体而言，若有 $d$ 条道路以路口 $x$ 为起点，则这 $d$ 条道路会被小 Y 按照某种顺序编号为 $1 \sim d$，分别称作以 $x$ 为起点的第 $1 \sim d$ 条道路。

小 Y 的机器人内部有一个参数 $p$。给定参数 $p$ 的上限 $k$ 与修改费用 $v_1, v_2, \ldots, v_{k-1}, w_2, w_3, \ldots, w_k$。小 Y 将按照如下规则设置与修改机器人的参数：

- 初始时，小 Y 将参数 $p$ 设置为 $1$。
- 在 **任意时刻**，小 Y 可以远程控制机器人修改参数：
  - 若 $p < k$，则小 Y 可以花费 $v_p$ 的费用将 $p$ 增加 $1$，即 $p \leftarrow p + 1$；
  - 若 $p > 1$，则小 Y 可以花费 $w_p$ 的费用将 $p$ 减少 $1$，即 $p \leftarrow p - 1$。

初始时，小 Y 的机器人位于机器人仓库，即路口 $1$。当机器人位于路口 $x$ 时，记以路口 $x$ 为起点的第 $p$ 条道路的终点为 $y$，道路长度为 $z$，则小 Y 可以花费 $z$ 的费用操控机器人从 $x$ 走到 $y$。特别地，若以路口 $x$ 为起点的道路不足 $p$ 条，则小 Y 无法操控机器人走动。

小 Y 并不知道闭幕式表演所在的礼堂位于哪个路口，因此他需要对每个路口都做好准备。请你帮助他求出将机器人从仓库移动到每个路口所需费用的最小值。
## 输入格式

输入的第一行包含一个非负整数 $c$，表示测试点编号。$c = 0$ 表示该测试点为样例。

输入的第二行包含三个正整数 $n, m, k$，分别表示路口数量、道路数量与参数 $p$ 的上限。

输入的第三行包含 $k - 1$ 个非负整数 $v_1, \ldots, v_{k-1}$，表示增加参数 $p$ 的费用。

输入的第四行包含 $k - 1$ 个非负整数 $w_2, \ldots, w_k$，表示减少参数 $p$ 的费用。

输入的第 $i + 4$（$1 \leq i \leq n$）行包含若干个正整数，其中第一个非负整数 $d_i$ 表示以路口 $i$ 为起点的道路数量，接下来 $2d_i$ 个正整数 $y_{i,1}, z_{i,1}, y_{i,2}, z_{i,2}, \ldots, y_{i,d_i}, z_{i,d_i}$，表示以路口 $i$ 为起点的道路，其中 $y_{i,j}, z_{i,j}$（$1 \leq j \leq d_i$）分别表示编号为 $j$ 的道路的终点与长度。
## 输出格式

输出一行 $n$ 个整数，其中第 $i$（$1 \leq i \leq n$）个数表示小 Y 将机器人从仓库移动到路口 $i$ 所需费用的最小值。特别地，若小 Y 无法将机器人从仓库移动到该路口，则输出 $-1$。
## 样例

### 样例输入 #1
```
0
5 6 3
2 4
1 1
3 2 5 3 1 4 2
1 3 2
2 1 2 4 1
0
0
```
### 样例输出 #1
```
0 5 3 4 -1
```
## 提示

### 样例 1 解释

小 Y 可以按照以下方案将机器人分别从仓库移动到路口 $1 \sim 4$：

- 对于路口 $1$：小 Y 的机器人初始时即位于路口 $1$，因此所需费用为 $0$。
- 对于路口 $2$：小 Y 操控机器人沿以路口 $1$ 为起点的第 $1$ 条道路走到路口 $2$，所需费用为 $5$。
- 对于路口 $3$：小 Y 将参数 $p$ 增加 $1$，然后操控机器人沿以路口 $1$ 为起点的第 $2$ 条道路走到路口 $3$，所需费用为 $2 + 1 = 3$。
- 对于路口 $4$：小 Y 将参数 $p$ 增加 $1$，然后操控机器人沿以路口 $1$ 为起点的第 $2$ 条道路走到路口 $3$，再操控机器人沿以路口 $3$ 为起点的第 $2$ 条道路走到路口 $4$，所需费用为 $2 + 1 + 1 = 4$。

可以证明，上述移动方案的所需费用均为最小值。

- 对于路口 $5$：由于小 Y 无法将机器人移动到路口 $5$，因此输出 $-1$。

### 样例 2

见选手目录下的 `robot/robot2.in` 与 `robot/robot2.ans`。

该样例满足测试点 $3 \sim 5$ 的约束条件。

### 样例 3

见选手目录下的 `robot/robot3.in` 与 `robot/robot3.ans`。

该样例满足测试点 $6 \sim 8$ 的约束条件。

### 样例 4

见选手目录下的 `robot/robot4.in` 与 `robot/robot4.ans`。

该样例满足测试点 $9, 10$ 的约束条件。

### 样例 5

见选手目录下的 `robot/robot5.in` 与 `robot/robot5.ans`。

该样例满足测试点 $16 \sim 18$ 的约束条件。

### 数据范围

对于所有测试数据，保证：

- $1 \leq n, m \leq 3 \times 10^5$，$1 \leq k \leq 2.5 \times 10^5$；
- 对于所有 $1 \leq i \leq k - 1$，均有 $0 \leq v_i \leq 10^9$；
- 对于所有 $2 \leq i \leq k$，均有 $0 \leq w_i \leq 10^9$；
- 对于所有 $1 \leq i \leq n$，均有 $0 \leq d_i \leq k$，且 $\sum_{i=1}^{n} d_i = m$；
- 对于所有 $1 \leq i \leq n$，$1 \leq j \leq d_i$，均有 $1 \leq y_{i,j} \leq n$，$1 \leq z_{i,j} \leq 10^9$。

| 测试点编号 | $n, m \leq$ | $k \leq$ | 特殊性质 |
| :-: | :-: | :-: | :-: |
| $1, 2$ | $6$ | $6$ | C |
| $3 \sim 5$ | $10^3$ | $10^3$ | C |
| $6 \sim 8$ | $5 \times 10^4$ | $10^2$ | 无 |
| $9, 10$ | $10^5$ | $10^5$ | AB |
| $11, 12$ | $10^5$ | $10^5$ | A |
| $13 \sim 15$ | $10^5$ | $10^5$ | C |
| $16 \sim 18$ | $10^5$ | $10^5$ | 无 |
| $19, 20$ | $3 \times 10^5$ | $2.5 \times 10^5$ | 无 |

- 特殊性质 A：保证 $v_1 = v_2 = \cdots = v_{k-1} = 0$ 且 $w_2 = w_3 = \cdots = w_k = 0$。
- 特殊性质 B：保证对于所有 $1 \leq i \leq n$，$1 \leq j \leq d_i$，均有 $z_{i,j} = 1$。
- 特殊性质 C：保证至多存在 10 个 $i$ 满足 $d_i \geq 10$。

附加文件来自于 [QOJ](https://qoj.ac/contest/2315/problem/13079)。


---

---
title: "[NOIP 2013 普及组] 车站分级"
layout: "post"
diff: 普及+/提高
pid: P1983
tag: ['图论', '贪心', '2013', 'NOIP 普及组', 'O2优化', '排序', '图论建模', '拓扑排序']
---
# [NOIP 2013 普及组] 车站分级
## 题目背景

NOIP2013 普及组 T4
## 题目描述

一条单向的铁路线上，依次有编号为 $1, 2, …, n$ 的 $n $ 个火车站。每个火车站都有一个级别，最低为 $1$ 级。现有若干趟车次在这条线路上行驶，每一趟都满足如下要求：如果这趟车次停靠了火车站 $x$，则始发站、终点站之间所有级别大于等于火车站 $x$ 的都必须停靠。  
注意：起始站和终点站自然也算作事先已知需要停靠的站点。

例如，下表是 $ 5 $ 趟车次的运行情况。其中，前 $ 4$ 趟车次均满足要求，而第 $5$ 趟车次由于停靠了 $3$ 号火车站（$2$ 级）却未停靠途经的 $6$ 号火车站（亦为 $2$ 级）而不满足要求。



 ![](https://cdn.luogu.com.cn/upload/pic/1238.png) 

现有 $m$ 趟车次的运行情况（全部满足要求），试推算这 $ n$ 个火车站至少分为几个不同的级别。

## 输入格式

第一行包含 $2$ 个正整数 $n, m$，用一个空格隔开。

第 $i + 1$ 行 $(1 ≤ i ≤ m)$ 中，首先是一个正整数 $s_i\ (2 ≤ s_i ≤ n)$，表示第 $ i$ 趟车次有 $s_i$ 个停靠站；接下来有 $ s_i$ 个正整数，表示所有停靠站的编号，从小到大排列。每两个数之间用一个空格隔开。输入保证所有的车次都满足要求。

## 输出格式

一个正整数，即 $n$ 个火车站最少划分的级别数。

## 样例

### 样例输入 #1
```
9 2 
4 1 3 5 6 
3 3 5 6 
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
9 3 
4 1 3 5 6 
3 3 5 6 
3 1 5 9 
```
### 样例输出 #2
```
3
```
## 提示

对于 $ 20\%$ 的数据，$1 ≤ n, m ≤ 10$；

对于 $50\%$ 的数据，$1 ≤ n, m ≤ 100$；

对于 $100\%$ 的数据，$1 ≤ n, m ≤ 1000$。



---

---
title: "[COCI 2006/2007 #1] Bond"
layout: "post"
diff: 普及+/提高
pid: P4329
tag: ['搜索', '2006', 'Special Judge', '图论建模', '二分图', '费用流', 'COCI（克罗地亚）', '状压 DP']
---
# [COCI 2006/2007 #1] Bond
## 题目描述

Everyone knows of the secret agent double-oh-seven, the popular Bond (James Bond). A lesser known fact is that he actually did not perform most of his missions by himself; they were instead done by his cousins, Jimmy Bonds. Bond (James Bond) has grown weary of having to distribute assign missions to Jimmy Bonds every time he gets new missions so he has asked you to help him out.
Every month Bond (James Bond) receives a list of missions. Using his detailed intelligence from past missions, for every mission and for every Jimmy Bond he calculates the probability of that particular mission being successfully completed by that particular Jimmy Bond. Your program should process that data and find the arrangement that will result in the greatest probability that all missions are completed successfully.
Note: the probability of all missions being completed successfully is equal to the product of the probabilities of the single missions being completed successfully.
## 输入格式

The first line will contain an integer N, the number of Jimmy Bonds and missions (1 ≤ N ≤ 20).
The following N lines will contain N integers between 0 and 100, inclusive. The j-th integer on the ith line is the probability that Jimmy Bond i would successfully complete mission j, given as a percentage.
## 输出格式

Output the maximum probability of Jimmy Bonds successfully completing all the missions, as a percentage.
## 样例

### 样例输入 #1
```
2
100 100
50 50
```
### 样例输出 #1
```
50.000000
```
### 样例输入 #2
```
2
0 50
50 0
```
### 样例输出 #2
```
25.00000
```
### 样例输入 #3
```
3
25 60 100
13 0 50
12 70 90
```
### 样例输出 #3
```
9.10000
```
## 提示

Clarification of the third example: If Jimmy bond 1 is assigned the 3rd mission, Jimmy Bond 2 the 1st mission and Jimmy Bond 3 the 2nd mission the probability is: 1.0 * 0.13 * 0.7 = 0.091 = 9.1%. All other arrangements give a smaller probability of success.
Note: Outputs within ±0.000001 of the official solution will be accepted.
## 题目翻译

有 $n$ 个人去执行 $n$ 个任务，每个人执行每个任务有不同的成功率，每个人只能执行一个任务，求所有任务都执行的总的成功率。

输入第一行，一个整数 $n$（$1\leq n\leq 20$），表示人数兼任务数。接下来 $n$ 行每行 $n$ 个数，第 $i$ 行第 $j$ 个数表示第 $i$ 个人去执行第 $j$ 个任务的成功率（这是一个百分数，在 $0$ 到 $100$ 间）。

输出最大的总成功率（这应也是一个百分数）


---

---
title: "[中山市选] 生成树"
layout: "post"
diff: 普及+/提高
pid: P4821
tag: ['枚举', '图论建模']
---
# [中山市选] 生成树
## 题目描述

有一种图形叫做五角形圈。一个五角形圈的中心有1个由n个顶点和n条边组成的圈。在中心的这个n边圈的每一条边同时也是某一个五角形的一条边，一共有n个不同的五角形。这些五角形只在五角形圈的中心的圈上有公共的顶点。如图0所示是一个4-五角形圈。

![https://cdn.luogu.com.cn/upload/pic/22665.png](https://cdn.luogu.com.cn/upload/pic/22665.png)

现在给定一个n五角形圈，你的任务就是求出n五角形圈的不同生成树的数目。还记得什么是图的生成树吗？一个图的生成树是保留原图的所有顶点以及顶点的数目减去一这么多条边,从而生成的一棵树。
注意：在给定的n五角形圈中所有顶点均视为不同的顶点。
## 输入格式

输入包含多组测试数据。第一行包含一个正整数T，表示测试数据数目。每组测试数据包含一个整数n( 2<=N<=100)，代表你需要求解的五角形圈中心的边数。
## 输出格式

对每一组测试数据，输出一行包含一个整数x，表示n五角形圈的生成树数目模2007之后的结果。
## 样例

### 样例输入 #1
```
1
2
```
### 样例输出 #1
```
40
```


---

---
title: "[USACO22FEB] Redistributing Gifts S"
layout: "post"
diff: 普及+/提高
pid: P8186
tag: ['图论', 'USACO', '2022', '图论建模', 'bitset', 'Floyd 算法']
---
# [USACO22FEB] Redistributing Gifts S
## 题目描述

Farmer John has $N$ gifts labeled $1\cdots N$ for his $N$ cows, also labeled $1\cdots N$ $(1\le N\le 500)$. Each cow has a wishlist, which is a permutation of all $N$ gifts such that the cow prefers gifts that appear earlier in the list over gifts that appear later in the list.

FJ was lazy and just assigned gift $i$ to cow $i$ for all $i$. Now, the cows have gathered amongst themselves and decided to reassign the gifts such that after reassignment, every cow ends up with the same gift as she did originally, or a gift that she prefers over the one she was originally assigned.

For each $i$ from $1$ to $N$, compute the most preferred gift cow $i$ could hope to receive after reassignment.
## 输入格式

The first line contains $N$. The next $N$ lines each contain the preference list of a cow. It is guaranteed that each line forms a permutation of $1\cdots N$.
## 输出格式

Please output $N$ lines, the $i$-th of which contains the most preferred gift cow $i$ could hope to receive after reassignment.
## 样例

### 样例输入 #1
```
4
1 2 3 4
1 3 2 4
1 2 3 4
1 2 3 4
```
### 样例输出 #1
```
1
3
2
4

```
## 提示

【样例解释】

In this example, there are two possible reassignments:

- The original assignment: cow 1 receives gift 1, cow 2 receives gift 2, cow 3 receives gift 3, and cow 4 receives gift 4.
- Cow 1 receives gift 1, cow 2 receives gift 3, cow 3 receives gift 2, and cow 4 receives gift 4.
Observe that both cows 1 and 4 cannot hope to receive better gifts than they were originally assigned. However, both cows 2 and 3 can.

【数据范围】

- Test cases 2-3 satisfy $N\le 8$.

- Test cases 4-11 satisfy no additional constraints.
## 题目翻译

# 题目描述
FJ 有 $N$ 个礼物给他的 $N$ 头奶牛，这 $N$ 个礼物和 $N$ 头奶牛都被标记为 $1 \dotsm N (1 \le N \le 500)$ 。 每头奶牛都有一个愿望单，记录着一个含有 $N$ 个礼物的排列。比起在愿望单中出现更晚的礼物，奶牛更喜欢先出现在愿望单中的礼物。

因为 FJ 太懒了，他直接把 $i$ 号礼物分配给了 $i$ 号奶牛。现在，奶牛们聚在了一起，决定重新分配礼物，以便在重新分配后，每头奶牛都能得到跟原来一样，或是它更喜欢的礼物。

对于每个 $i$ （$i$ 从 $1$ 到 $N$），计算出重新分配后， $i$ 号奶牛可能拿到的最好的礼物（这个奶牛经过重新分配后能拿到的最喜欢的礼物）。

# 输入格式
第一行输入 $N$ 。之后 $N$ 行每行包含一个奶牛的愿望单。保证这 $N$ 行都是 $1 \dotsm N$ 的排列

# 输出格式
输出 $N$ 行，第 $i$ 行输出重新分配后 $i$ 号奶牛可能得到的最好礼物。

# 样例解释
在这个例子中，有两种可能的分配方案
- 最初的方案：一号奶牛得到一号礼物，二号奶牛得到二号礼物，三号奶牛得到三号礼物，四号奶牛得到四号礼物
- 重新分配后的方案：一号奶牛得到一号礼物，二号奶牛得到三号礼物，三号奶牛得到二号礼物，四号奶牛得到四号礼物。可以发现一号和四号奶牛都拿不到比FJ分配的更好的礼物。不过二号和三号都可以。

# 数据范围
- $2 \sim 3$ 号测试点满足 $N \le 8$
- $4 \sim 11$ 号测试点没有别的限制

由 [tzyt](https://www.luogu.com.cn/user/394488) 翻译


---

---
title: "[蓝桥杯 2022 省 A] 推导部分和"
layout: "post"
diff: 普及+/提高
pid: P8779
tag: ['并查集', '2022', '图论建模', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 A] 推导部分和
## 题目描述

对于一个长度为 $N$ 的整数数列 $A_{1}, A_{2}, \cdots A_{N}$，小蓝想知道下标 $l$ 到 $r$ 的部分和 $\sum\limits_{i=l}^{r}A_i=A_{l}+A_{l+1}+\cdots+A_{r}$ 是多少?

然而，小蓝并不知道数列中每个数的值是多少，他只知道它的 $M$ 个部分和的值。其中第 $i$ 个部分和是下标 $l_{i}$ 到 $r_{i}$ 的部分和 $\sum_{j=l_{i}}^{r_{i}}=A_{l_{i}}+A_{l_{i}+1}+\cdots+A_{r_{i}}$, 值是 $S_{i}$ 。
## 输入格式

第一行包含 3 个整数 $N 、 M$ 和 $Q$。分别代表数组长度、已知的部分和数量 和询问的部分和数量。

接下来 $M$ 行，每行包含 $3$ 个整数 $l_{i}, r_{i}, S_{i}$。

接下来 $Q$ 行，每行包含 $2$ 个整数 $l$ 和 $r$，代表一个小蓝想知道的部分和。

## 输出格式

对于每个询问, 输出一行包含一个整数表示答案。如果答案无法确定, 输出 `UNKNOWN`。
## 样例

### 样例输入 #1
```
5 3 3
1 5 15
4 5 9
2 3 5
1 5
1 3
1 2
```
### 样例输出 #1
```
15
6
UNKNOWN
```
## 提示

对于 $10 \%$ 的评测用例, $1 \leq N, M, Q \leq 10,-100 \leq S_{i} \leq 100$ 。

对于 $20 \%$ 的评测用例, $1 \leq N, M, Q \leq 20,-1000 \leq S_{i} \leq 1000$ 。

对于 $30 \%$ 的评测用例, $1 \leq N, M, Q \leq 50,-10000 \leq S_{i} \leq 10000$ 。

对于 $40 \%$ 的评测用例, $1 \leq N, M, Q \leq 1000,-10^{6} \leq S_{i} \leq 10^{6}$ 。

对于 $60 \%$ 的评测用例, $1 \leq N, M, Q \leq 10000,-10^{9} \leq S_{i} \leq 10^{9}$ 。

对于所有评测用例, $1 \leq N, M, Q \leq 10^{5},-10^{12} \leq S_{i} \leq 10^{12}, 1 \leq l_{i} \leq r_{i} \leq N$, $1 \leq l \leq r \leq N$ 。数据保证没有矛盾。

蓝桥杯 2022 省赛 A 组 J 题。


---

---
title: "[DMOI-R1] Portal"
layout: "post"
diff: 普及+/提高
pid: P8886
tag: ['搜索', 'O2优化', '图论建模', '最短路']
---
# [DMOI-R1] Portal
## 题目背景

出题人正在玩一款叫 Portal 的游戏。但由于他太菜了，于是找来了你，让你帮他过几个他过不去的关卡。

什么？你说你不会玩？

玩家需要通过传送门枪到达出口。利用传送门枪射击可开出两种门，分别是橙色门和蓝色门，两面都可作入口及出口。在创造门的时候，另一道同样颜色的门会消失，即是说同时间不可能存在两道同色的门，最多只可同时存在一道蓝色及一道橙色的门。

两道传送门在三维空间之中的两个地点创造出视觉上及物理上的连系，传送门的立点只限于平面，玩家从门出来时会自动配合地心吸力调整身体水平。

出题人把所有希望都寄托于你身上了哟。哦，对了，因为出题人是个白嫖党，因此他拥有的是盗版 Portal。
## 题目描述

在一个 $n \times n$ 的二维平面图上，用 $(x,y)$ 表示地图第 $x$ 行第 $y$ 列。每个点都是墙、虚空和地面中的一种，分别用 `#`，`*`，`.` 表示。玩家只能站在地面上。**地图之外都是墙。**

你手里有一个传送门枪，可以发射蓝色和橙色的传送门，只能朝上下左右四个方向使用。

在选定一个方向和颜色后，将会在该方向上第一个碰到的墙的墙面上建造选定颜色的传送门，并摧毁之前建造的这种颜色的传送门。两种颜色的传送门不能被建立在同一墙面。

玩家可以朝上下左右四个方向的空地移动。玩家还可以在不同色传送门之间穿梭。假如玩家朝一堵墙移动并且墙面上有传送门，并且当前已经建立了两个传送门，那么会从另一个传送门出来（必须保证出来也站在陆地上）。

出来的时候，玩家会站在另一个门外的空地上，**四个方向都可以。**

一开始玩家站在 $(1,1)$，目的地是 $(n,n)$。求最少使用多少次传送门枪才能到达目的地。

**注意哦，这里的使用指的是穿过多少面传送门。**
## 输入格式

第一行一个正整数 $T$ 表示数据组数。

每组数据第一行一个正整数 $n$ 表示平面图的行数和列数。

接下来 $n$ 行每行 $n$ 个字符只包含 `#`，`*`，`.` 三种字符表示地图。
## 输出格式

对于每组数据输出一个数表示最少需要使用传送门枪的次数。无法到达输出 `-1`。如果起点或终点不为陆地，那么直接结束程序。
## 样例

### 样例输入 #1
```
2
5
..###
#.#.#
#..##
...#.
.###.
5
..#..
##..#
#.#..
..#..
.#...
```
### 样例输出 #1
```
2
2
```
### 样例输入 #2
```
4
5
...*.
*##*.
#..*.
#*###
.....
5
.#*..
.**.#
###.*
***.*
**...
5
.**..
***.#
###.*
***.*
*****
5
.**..
***.#
###..
***.*
***..
```
### 样例输出 #2
```
4
2

```
### 样例输入 #3
```
见下发文件portal1.in
```
### 样例输出 #3
```
见下发文件portal1.ans
```
### 样例输入 #4
```
见下发文件portal2.in
```
### 样例输出 #4
```
见下发文件portal2.ans
```
## 提示

### 样例1解释

我们用白色格子表示空地，黑色格子表示墙，蓝色格子表示蓝色传送门，橙色格子表示橙色传送门，可以画出第一局的如下地图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s16tq3vq.png)

走到橙色传送门处，从橙色传送门进入，蓝色传送门出即可。

而第二局地图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/v7q0izdk.png)


走到蓝色传送门处，从蓝色传送门进入，橙色传送门出即可。

### 数据范围

对于 $20\%$ 的数据，$n \le 10$。

对于 $60\%$ 的数据，$n \le 100$。

对于另外 $10\%$ 的数据，$T=1$ 且不存在虚空。

对于 $100\%$ 的数据，$2 \le n \le 500$，$1 \le T \le 10$。


---

---
title: "[USACO23JAN] Find and Replace S"
layout: "post"
diff: 普及+/提高
pid: P9013
tag: ['USACO', '2023', '图论建模', '基环树']
---
# [USACO23JAN] Find and Replace S
## 题目描述

Bessie is using the latest and greatest innovation in text-editing software, miV! She starts with an input string consisting solely of upper and lowercase English letters and wishes to transform it into some output string. With just one keystroke, miV allows her to replace all occurrences of one English letter $c_1$ in the string with another English letter $c_2$. For example, given the string `aAbBa`, if Bessie selects $c_1$ as `a` and $c_2$ as `B`, the given string transforms into `BAbBB`.

Bessie is a busy cow, so for each of $T
(1 \le T \le 10)$ independent test cases, output the minimum number of keystrokes required to transform her input string into her desired output string. 
## 输入格式

The first line contains $T$, the number of independent test cases.

The following $T$ pairs of lines contain an input and output string of equal length. All characters are upper or lowercase English letters (either `A` through `Z` or `a` through `z`). The sum of the lengths of all strings does not exceed $10^5$. 
## 输出格式

For each test case, output the minimum number of keystrokes required to change the input string into the output string, or $−1$ if it is impossible to do so. 
## 样例

### 样例输入 #1
```
4
abc
abc
BBC
ABC
abc
bbc
ABCD
BACD
```
### 样例输出 #1
```
0
-1
1
3
```
## 提示

### Explanation for Sample 1

The first input string is the same as its output string, so no keystrokes are required.

The second input string cannot be changed into its output string because Bessie cannot change one `B`' to `A` while keeping the other as `B`.

The third input string can be changed into its output string by changing `a` to `b`.

The last input string can be changed into its output string like so: $\texttt{ABCD} \rightarrow \texttt{EBCD} \rightarrow \texttt{EACD} \rightarrow \texttt{BACD}$.

### Scoring

 - Inputs $2-6$: Every string has a length at most $50$.
 - Inputs $7-9$: All strings consist only of lowercase letters `a` through `e`
 - Inputs $10-15$: No additional constraints.
## 题目翻译

### 题目描述

Bessie 正在使用世界上最先进最伟大的文本编辑器：miV！她想将一个仅由大写和小写英文字母组成的字符串转换为一个新的字符串。每一次操作，miV 可以将字符串中所有的字母  $c_1$ 替换成另一种字母 $c_2$。例：对于字符串`aAbBa`, 如果将其中的 `a` 替换成 `B`, 那么字符串会变为`BAbBB`。

Bessie 非常地忙碌, 所以对于给出的 $T
(1 \le T \le 10)$ 组测试数据, 请输出她至少需要多少次操作才能把原字符串转换为新字符串。

### 输入格式

第一行是一个整数 $T$, 表示测试数据的数量。

接下来有 $T$ 对长度相等的字符串。字符串中所有的字符都是大写或小写的字母。字符串的长度不会超过 $10^5$。

### 输出格式

对于每组测试数据，输出转换字符串需要的最小操作数。

如果这不可能做到，输出 $-1$。

### 样例 1 解释

第一组数据：两个字符串相等，所以不需要任何操作。

第二组数据：你不可能在把其中一个 `B` 转换为 `A`的同时保持剩下一个 `B` 不变。

第三组数据：你可以把字符串中所有的 `a` 转换为 `b`。

第四组数据：你可以按 $\texttt{ABCD} \rightarrow \texttt{EBCD} \rightarrow \texttt{EACD} \rightarrow \texttt{BACD}$ 的方式转换。

### 数据范围

 - 对于 $ 40 \% $ 的数据，字符串的长度不超过 $50$。
 - 对于另外 $ 20\% $ 的数据，所有的字符串仅包含从 `a` 到 `e` 的小写字母。
 - 对于 $ 100\% $ 的数据，字符串的长度不超过 $10^5$，$1 \le T \le 10$。


---

---
title: "[USACO23FEB] Moo Route II S"
layout: "post"
diff: 普及+/提高
pid: P9126
tag: ['图论', 'USACO', '2023', '图论建模', '最短路']
---
# [USACO23FEB] Moo Route II S
## 题目描述

**Note: The time limit for this problem is 4s, twice the default.**

Bessie is on vacation! Due to some recent technological advances, Bessie will travel via technologically sophisticated flights, which can even time travel. Furthermore, there are no issues if two "parallel" versions of Bessie ever meet.

In the country there are $N$ airports numbered $1,2,\cdots ,N$ and $M$ time-traveling flights $(1 \le N,M \le 200000)$. Flight $j$ leaves airport $c_j$ at time $r_j$, and arrives in airport $d_j$ at time $s_j (0 \le rj,sj \le 10^9$, $s_j<r_j$ is possible$)$. In addition, she must leave $a_i$ time for a layover at airport $i (1 \le a_i \le 10^9)$. (That is to say, if Bessie takes a flight arriving in airport $i$ at time $s$, she can then transfer to a flight leaving the airport at time $r$ if $r \ge s+a_i$. The layovers do not affect when Bessie arrives at an airport.)

Bessie starts at city $1$ at time $0$. For each airport from $1$ to $N$, what is the earliest time when Bessie can get to at it? 
## 输入格式

The first line of input contains $N$ and $M$.

The next $M$ lines describe flights. The $j$-th of these lines contains $c_j, r_j, d_j, s_j$ in that order. $(1 \le c_j,d_j \le N, 0 \le r_j,s_j \le 10^9)$

The next line describes airports. It contains $N$
space separated integers, $a_1, \cdots ,a_N$. 
## 输出格式

There are $N$ lines of output. Line $i$ contains the earliest time when Bessie can get to airport $i$, or $-1$ if it is not possible for Bessie to get to that airport. 
## 样例

### 样例输入 #1
```
3 3
1 0 2 10
2 11 2 0
2 1 3 20
10 1 10
```
### 样例输出 #1
```
0
0
20
```
### 样例输入 #2
```
3 3
1 0 2 10
2 10 2 0
2 1 3 20
10 1 10
```
### 样例输出 #2
```
0
10
-1
```
## 提示

### Explanation for Sample 1

Bessie can take the $3$ flights in the listed order, which allows her to arrive at airports $1$ and $2$ at time $0$, and airport $3$ at time $20$.

Note that this route passes through airport $2$ twice, first from time $10-11$ and then from time $0-1$.

### Explanation for Sample 2

In this case, Bessie can take flight $1$, arriving at airport $2$ at time $10$. However, she does not arrive in time to also take flight $2$, since the departure time is $10$ and she cannot make a $1$ time-unit layover. 

### SCORING

 - Inputs $3-5$: $r_j<s_j$ for all $j$, i.e. all flights arrive after they depart.
 - Inputs $6-10$: $N,M \le 5000$
 - Inputs $11-20$: No additional constraints.
## 题目翻译

### 题目描述

注意：本题的时间限制为 4 秒，是默认限制的两倍。

Bessie 正在度假！由于最近的技术进步，Bessie 可以通过先进的航班旅行，这些航班甚至可以进行时间旅行。此外，即使存在多个“平行”的 Bessie 同时出现也不会有任何问题。

在这个国家，有 $N$ 个机场，编号为 $1,2,\cdots,N$，以及 $M$ 条时间旅行航班（$1 \leq N,M \leq 200000$）。第 $j$ 条航班从机场 $c_j$ 在时间 $r_j$ 起飞，并在时间 $s_j$ 抵达机场 $d_j$（$0 \leq r_j,s_j \leq 10^9$，$s_j < r_j$ 是可能的）。此外，Bessie 在机场 $i$ 需要停留 $a_i$ 时间（$1 \leq a_i \leq 10^9$）。也就是说，如果 Bessie 乘坐一趟航班在时间 $s$ 抵达机场 $i$，她可以转乘一趟从该机场出发的航班，只要该航班的起飞时间 $r \geq s + a_i$。需要注意的是，停留时间不会影响 Bessie 抵达某机场的实际时间。

Bessie 从城市 $1$ 出发，起始时间为 $0$。对于从 $1$ 到 $N$ 的每个机场，求出 Bessie 最早可以到达该机场的时间。

### 输入格式

第一行输入包含两个整数 $N$ 和 $M$。

接下来的 $M$ 行描述航班信息。其中第 $j$ 行包含 $c_j, r_j, d_j, s_j$，依次表示航班的起飞机场、起飞时间、降落机场和降落时间。$(1 \leq c_j,d_j \leq N, 0 \leq r_j,s_j \leq 10^9)$

接下来的 $1$ 行描述每个机场的停留时间。该行包含 $N$ 个用空格分隔的整数，分别为 $a_1,\cdots,a_N$。

### 输出格式

输出共 $N$ 行。第 $i$ 行输出 Bessie 最早到达机场 $i$ 的时间；如果无法到达该机场，输出 $-1$。

### 样例 1 的解释

Bessie 可以按照给定的顺序乘坐第 $3$ 班航班，这使她可以在时间 $0$ 到达机场 $1$ 和机场 $2$，以及在时间 $20$ 到达机场 $3$。


注意，这条路线会两次经过机场 $2$，第一次是在时间 $10-11$，第二次是在时间 $0-1$。

### 样例 2 的解释

在这个例子中，Bessie 可以乘坐第 $1$ 班航班，在时间 $10$ 抵达机场 $2$。但是，她无法及时赶上第 $2$ 班航班，因为该航班的起飞时间为 $10$，而她需要至少 $1$ 个时间单位来完成停留。

### 评分标准

 - 测试点 $3-5$：对于每个 $j$，$r_j < s_j$，也就是说所有航班的到达时间晚于起飞时间。
 - 测试点 $6-10$：$N,M \leq 5000$
 - 测试点 $11-20$：无额外限制。


---

