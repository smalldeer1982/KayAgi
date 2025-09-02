---
title: "[NOISG 2022 Qualification] Tree Cutting"
layout: "post"
diff: 提高+/省选-
pid: P11294
tag: ['树形数据结构', '2022', '深度优先搜索 DFS', '树形 DP', 'NOISG（新加坡）']
---
# [NOISG 2022 Qualification] Tree Cutting
## 题目背景

一个国家有 $N$ 个城市，编号为 $1$ 到 $N$，以及 $N-1$ 条双向公路。通过这些公路，可以从任意一个城市到达另一个城市。

城市 $x$ 和城市 $y$ 之间的距离定义为连接两城市所需经过的公路数。

州长决定拆除一条公路，并新建另一条公路，使得任意两城市之间的最远距离最大化。
## 题目描述

请计算新建公路后，任意两城市之间的最大距离。
## 输入格式

- 第一行包含一个整数 $N$，表示城市的数量。
- 接下来的 $N-1$ 行，每行包含两个整数 $u$ 和 $v$，表示城市 $u$ 和 $v$ 之间有一条双向公路。
## 输出格式

输出一个整数，表示新建公路后任意两城市之间的最大距离。
## 样例

### 样例输入 #1
```
4
1 2
1 3
3 4
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
6
1 2
2 3
2 5
4 5
5 6
```
### 样例输出 #2
```
5
```
## 提示

【样例解释】

对于样例 $1$，最远距离无法增加，仍然为 $3$。  

对于样例 $2$，可以拆除公路 $2-5$，新建公路 $3-4$，最远路径为 $1-2-3-4-5-6$，其长度为 $5$。

【数据范围】

- $2 \leq N \leq 300,000$
- $1 \leq u, v \leq N$

| 子任务编号 | 分值 | 额外限制条件                             |
| :--------: | :--: | :--------------------------------------: |
| $1$        | $5$  | $N \leq 10$                              |
| $2$        | $10$ | $N \leq 100$                             |
| $3$        | $15$ | $N \leq 3000$                            |
| $4$        | $15$ | $N \leq 300,000$，至多一个城市连接至少 $3$ 条公路 |
| $5$        | $55$ | 无额外限制                              |


---

---
title: "[Sloi 2024]D1T1 精卫"
layout: "post"
diff: 提高+/省选-
pid: P11417
tag: ['数论', '深度优先搜索 DFS', '素数判断,质数,筛法']
---
# [Sloi 2024]D1T1 精卫
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/p38htsuu.png)
## 题目描述

$f(x)$ 为积性函数，且满足 $f(p^k)=p^{2k}+k$（$p$ 为素数）。

令 $g(x)=\prod\limits_{d|x}f(d)\space \bmod\space (10^9+7)$ ，请计算 $g(i)\space (1\le i \le n)$ 的异或和。
## 输入格式

一行一个正整数 $n$。
## 输出格式

一行一个非负整数。
## 样例

### 样例输入 #1
```
5
```
### 样例输出 #1
```
78
```
### 样例输入 #2
```
142857
```
### 样例输出 #2
```
67850062
```
### 样例输入 #3
```
10000000
```
### 样例输出 #3
```
505679580
```
## 提示

**本题采用捆绑测试**

| Subtask | n | Score |
| :----------: | :----------: | :----------: |
| $1$ | $\le10^4$ | $10$ |
| $2$ | $\le 5\times 10^6$ | $30$ |
| $3$ | $\le 2\times 10^7$ | $30$ |
| $4$ | $\le 5\times10^7$ | $30$ |

对 $100\%$ 的数据，$1\le n \le 5\times10^{7} $。



---

---
title: "[NOI2013] 快餐店"
layout: "post"
diff: 提高+/省选-
pid: P1399
tag: ['递推', '2013', '线段树', 'NOI', '深度优先搜索 DFS', '基环树']
---
# [NOI2013] 快餐店
## 题目描述

小 T 打算在城市 C 开设一家外送快餐店。送餐到某一个地点的时间与外卖店到该地点之间最短路径长度是成正比的，小 T 希望快餐店的地址选在离最远的顾客距离最近的地方。

快餐店的顾客分布在城市 C 的 $N$ 个建筑中，这 $N$ 个建筑通过恰好 $N$ 条双向道路连接起来，不存在任何两条道路连接了相同的两个建筑。任意两个建筑之间至少存在一条由双向道路连接而成的路径。小 T 的快餐店可以开设在任一建筑中，也可以开设在任意一条道路的某个位置上（该位置与道路两端的建筑的距离不一定是整数）。

现给定城市 C 的地图（道路分布及其长度），请找出最佳的快餐店选址，输出其与最远的顾客之间的距离。
## 输入格式

第一行包含一个整数 $N$，表示城市 C 中的建筑和道路数目。

接下来 $N$ 行，每行 $3$ 个整数，$A_i,B_i,L_i$（$1\leq i\leq N$，$L_i>0$），表示一条道路连接了建筑 $A_i$ 与 $B_i$，其长度为 $L_i$。

## 输出格式

输出仅包含一个实数，四舍五入保留**恰好一位小数**，表示最佳快餐店选址距离最远用户的距离。

注意：你的结果必须恰好有一位小数，小数位数不正确不得分。
## 样例

### 样例输入 #1
```
4 
1 2 1 
1 4 2 
1 3 2 
2 4 1

```
### 样例输出 #1
```
2.0 
```
### 样例输入 #2
```
5
1 5 100
2 1 77
3 2 80
4 1 64
5 3 41
```
### 样例输出 #2
```
109.0
```
## 提示

### 样例解释 1

![](https://cdn.luogu.com.cn/upload/image_hosting/r0dmxcgy.png)

### 样例解释 2

![](https://cdn.luogu.com.cn/upload/image_hosting/pf8eaowl.png)

### 数据范围

- 对于 $10\%$ 的数据，$N\leq 80$，$L_i=1$；
- 对于 $30\%$ 的数据，$N\leq 600$，$L_i\leq 100$；
- 对于 $60\%$ 的数据，$N\leq 2000$，$L_i\leq 10^9$；
- 对于 $100\%$ 的数据，$1\leq N\leq 10^5$，$1\leq L_i \leq 10^9$。


---

---
title: "切蛋糕"
layout: "post"
diff: 提高+/省选-
pid: P1528
tag: ['搜索', '贪心', '深度优先搜索 DFS', '剪枝']
---
# 切蛋糕
## 题目描述

Facer今天买了 $n$ 块蛋糕，不料被信息组中球球等好吃懒做的家伙发现了，没办法，只好浪费一点来填他们的嘴巴。他答应给每个人留一口，然后量了量每个人口的大小。Facer 有把刀，可以切蛋糕，但他不能把两块蛋糕拼起来，但是他又不会给任何人两块蛋糕。现在问你，facer 怎样切蛋糕，才能满足最多的人。（facer 的刀很强，切的时候不会浪费蛋糕）。

 
 
## 输入格式

第一行 $n$，facer 有 $n$ 个蛋糕。接下来 $n$ 行，每行表示一个蛋糕的大小。再一行一个数 $m$，为信息组的人数，然后 $m$ 行，每行一个数，为一个人嘴的大小。$(1\le n\le 50$，$ 1\le m\le 1024)$


## 输出格式

一行，facer最多可以填多少张嘴巴。

## 样例

### 样例输入 #1
```
4

30

40

50

25

10

15

16

17

18

19

20

21

25

24

30



 


```
### 样例输出 #1
```
7


```


---

---
title: "贪吃虫"
layout: "post"
diff: 提高+/省选-
pid: P1751
tag: ['模拟', '搜索', '图论', '深度优先搜索 DFS']
---
# 贪吃虫
## 题目背景

我们都知道一个很著名的游戏——贪吃蛇。它的一大特点是当前一个食物被吃掉后，后一个食物才会出现。今天我们要做的另一个游戏——贪吃虫也很类似。

## 题目描述

贪吃虫有 $k$ 条，在一棵有 $n$ 个节点的树上，每只虫子都在不同的节点上。第一个食物到来时，所有的 $k$ 只虫会从它们当前的位置出发，前往食物的位置。它们的移动遵循如下规则：

- 这棵树上的任何两个节点之间有且仅有一条路，所有的贪吃虫沿着唯一的路径前往食物所在的位置；
- 如果有一只贪吃虫到达了食物所在的位置，食物马上就被吃掉了；
- 如果有另外一只贪吃虫在某一只贪吃虫通往食物的道路上，那么距离食物较远的那只虫子会停止移动，停留在当前的节点上；
- 如果有多只虫子尝试进入同一个节点，只有编号最小的虫子能够到达，其它的贪吃虫停留在它们当前的位置上；
- 吃掉食物的那只虫子会停留在食物的位置上；
- 食物被吃掉之后会出现在树上的另外一个节点上。这时所有的贪吃虫会重新出发，尝试再一次吃掉食物。为了简化过程，我们假设从一个节点移动到相邻的节点需要花费一个单位时间。

## 输入格式

第 $1$ 行一个整数 $n$，表示树上的节点个数。

第 $2$ 至 $N$ 行，第 $i+1$ 行包含了一个两个整数 $:A_i,B_i$，表示从节点 $A_i$ 到节点 $B_i$ 有一条边直接相连。

第 $N+1$ 行有一个整数 $k$，表示树上贪吃虫的个数。

第 $N+2$ 至 $N+1+k$ 行，第 $N+1+i$ 行有一个整数 $P_i$，表示第 $i$ 只贪吃虫开始时的位置，任何两只贪吃虫的初始位置不相同。

第 $N+2+k$ 行：有一个整数 $h$，表示食物一共在树上出现了多少次。

接下来的 $h$ 行，每行一个整数，表示食物依次出现的位置。
## 输出格式

输出一共包含 $k$ 行，第 $i$ 行有两个整数 $C_i$ 和 $D_i$。分别表示第 $i$ 只贪吃虫最终停留的位置和这只贪吃虫吃到食物的次数。
## 样例

### 样例输入 #1
```
4

1 2

1 3

2 4

2

1

2

2

2

4
```
### 样例输出 #1
```
1 0

4 2


```
## 提示


### 数据范围及约定

对于全部数据，$1 \le n \le 5000$，$1 \le k \le 1000$，$k \le n$，$1 \le h \le 500$。


---

---
title: "[SCOI2005] 互不侵犯"
layout: "post"
diff: 提高+/省选-
pid: P1896
tag: ['动态规划 DP', '2005', '四川', '各省省选', '深度优先搜索 DFS', '状压 DP']
---
# [SCOI2005] 互不侵犯
## 题目描述

在 $N \times N$ 的棋盘里面放 $K$ 个国王，使他们互不攻击，共有多少种摆放方案。国王能攻击到它上下左右，以及左上左下右上右下八个方向上附近的各一个格子，共 $8$ 个格子。
## 输入格式

只有一行，包含两个数 $N,K$。
## 输出格式

所得的方案数

## 样例

### 样例输入 #1
```
3 2

```
### 样例输出 #1
```
16

```
## 提示

### 数据范围及约定

对于全部数据，$1 \le N \le 9$，$0 \le K \le N\times N$。

---

$\text{upd 2018.4.25}$：数据有加强。


---

---
title: "[NOI2015] 软件包管理器"
layout: "post"
diff: 提高+/省选-
pid: P2146
tag: ['树形数据结构', '2015', '线段树', 'NOI', '深度优先搜索 DFS', '树链剖分']
---
# [NOI2015] 软件包管理器
## 题目背景

Linux 用户和 OSX 用户一定对软件包管理器不会陌生。通过软件包管理器，你可以通过一行命令安装某一个软件包，然后软件包管理器会帮助你从软件源下载软件包，同时自动解决所有的依赖（即下载安装这个软件包的安装所依赖的其它软件包），完成所有的配置。Debian/Ubuntu 使用的 apt-get，Fedora/CentOS 使用的 yum，以及 OSX 下可用的 homebrew 都是优秀的软件包管理器。  

## 题目描述

你决定设计你自己的软件包管理器。不可避免地，你要解决软件包之间的依赖问题。如果软件包 $a$ 依赖软件包 $b$，那么安装软件包 $a$ 以前，必须先安装软件包 $b$。同时，如果想要卸载软件包 $b$，则必须卸载软件包 $a$。

现在你已经获得了所有的软件包之间的依赖关系。而且，由于你之前的工作，除 $0$ 号软件包以外，在你的管理器当中的软件包都会依赖一个且仅一个软件包，而 $0$ 号软件包不依赖任何一个软件包。且依赖关系不存在环（即不会存在 $m$ 个软件包 $a_1,a_2, \dots , a_m$，对于 $i<m$，$a_i$ 依赖 $a_{i+1}$，而 $a_m$ 依赖 $a_1$ 的情况）。

现在你要为你的软件包管理器写一个依赖解决程序。根据反馈，用户希望在安装和卸载某个软件包时，快速地知道这个操作实际上会改变多少个软件包的安装状态（即安装操作会安装多少个未安装的软件包，或卸载操作会卸载多少个已安装的软件包），你的任务就是实现这个部分。

注意，安装一个已安装的软件包，或卸载一个未安装的软件包，都不会改变任何软件包的安装状态，即在此情况下，改变安装状态的软件包数为 $0$。

## 输入格式

第一行一个正整数 $n$，表示软件包个数，从 $0$ 开始编号。  
第二行有 $n-1$ 个整数，第 $i$ 个表示 $i$ 号软件包依赖的软件包编号。  
然后一行一个正整数 $q$，表示操作个数，格式如下：  

- `install x` 表示安装 $x$ 号软件包
- `uninstall x` 表示卸载 $x$ 号软件包

一开始所有软件包都是未安装的。  

对于每个操作，你需要输出这步操作会改变多少个软件包的安装状态，随后应用这个操作（即改变你维护的安装状态）。
## 输出格式

输出 $q$ 行，每行一个整数，表示每次询问的答案。
## 样例

### 样例输入 #1
```
7
0 0 0 1 1 5
5
install 5
install 6
uninstall 1
install 4
uninstall 0
```
### 样例输出 #1
```
3
1
3
2
3
```
### 样例输入 #2
```
10
0 1 2 1 3 0 0 3 2
10
install 0
install 3
uninstall 2
install 7
install 5
install 9
uninstall 9
install 4
install 1
install 9
```
### 样例输出 #2
```
1
3
2
1
3
1
1
1
0
1
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/1504.png)  
一开始所有软件包都处于未安装状态。

安装 $5$ 号软件包，需要安装 $0,1,5$ 三个软件包。

之后安装 $6$ 号软件包，只需要安装 $6$ 号软件包。此时安装了 $0,1,5,6$ 四个软件包。

卸载 $1$ 号软件包需要卸载 $1,5,6$ 三个软件包。此时只有 $0$ 号软件包还处于安装状态。

之后安装 $4$ 号软件包，需要安装 $1,4$ 两个软件包。此时 $0,1,4$ 处在安装状态。最后，卸载 $0$ 号软件包会卸载所有的软件包。

【数据范围】  
![](https://cdn.luogu.com.cn/upload/pic/1505.png)


---

---
title: "[HNOI2002] 彩票"
layout: "post"
diff: 提高+/省选-
pid: P2236
tag: ['2002', '各省省选', '湖南', '深度优先搜索 DFS']
---
# [HNOI2002] 彩票
## 题目描述

某地发行一套彩票。彩票上写有 $1$ 到 $M$ 这 $M$ 个自然数。彩民可以在这 $M$ 个数中任意选取 $N$ 个不同的数打圈。每个彩民只能买一张彩票，不同的彩民的彩票上的选择不同。

每次抽奖将抽出两个自然数 $X$ 和 $Y$。如果某人拿到的彩票上，所选 $N$ 个自然数的倒数和，恰好等于 $\dfrac{X}{Y}$，则他将获得一个纪念品。

已知抽奖结果 $X$ 和 $Y$。现在的问题是，必须准备多少纪念品，才能保证支付所有获奖者的奖品。
## 输入格式

输入文件有且仅有一行，就是用空格分开的四个整数 $N$，$M$，$X$，$Y$。

## 输出格式

输出文件有且仅有一行，即所需准备的纪念品数量。

## 样例

### 样例输入 #1
```
2 4 3 4
```
### 样例输出 #1
```
1
```
## 提示

$1 \leq X, Y \leq 100$，$1 \leq N \leq 10$，$1 \leq M \leq 50$。

输入数据保证输出结果不超过 $10^5$。


---

---
title: "[HNOI2003] 消防局的设立"
layout: "post"
diff: 提高+/省选-
pid: P2279
tag: ['贪心', '2003', '各省省选', '湖南', '深度优先搜索 DFS', '树形 DP']
---
# [HNOI2003] 消防局的设立
## 题目描述

2020 年，人类在火星上建立了一个庞大的基地群，总共有 $n$ 个基地。起初为了节约材料，人类只修建了 $n-1$ 条道路来连接这些基地，并且每两个基地都能够通过道路到达，所以所有的基地形成了一个巨大的树状结构。如果基地 $A$ 到基地 $B$ 至少要经过 $d$ 条道路的话，我们称基地A到基地B的距离为 $d$。

由于火星上非常干燥，经常引发火灾，人类决定在火星上修建若干个消防局。消防局只能修建在基地里，每个消防局有能力扑灭与它距离不超过 $2$ 的基地的火灾。

你的任务是计算至少要修建多少个消防局才能够确保火星上所有的基地在发生火灾时，消防队有能力及时扑灭火灾。
## 输入格式

输入文件的第一行为 $n$（$1 \leq n \leq 1000$），表示火星上基地的数目。接下来的 $n-1$ 行每行有一个正整数，其中文件第 $i$ 行的正整数为 $a_i$，表示从编号为 $i$ 的基地到编号为 $a_i$ 的基地之间有一条道路，为了更加简洁的描述树状结构的基地群，有 $a_i\lt i$。
## 输出格式

仅有一个正整数，表示至少要设立多少个消防局才有能力及时扑灭任何基地发生的火灾。
## 样例

### 样例输入 #1
```
6
1
2
3
4
5

```
### 样例输出 #1
```
2
```


---

---
title: "[SCOI2005] 王室联邦"
layout: "post"
diff: 提高+/省选-
pid: P2325
tag: ['搜索', '2005', '四川', '各省省选', 'Special Judge', '深度优先搜索 DFS', '栈']
---
# [SCOI2005] 王室联邦
## 题目描述

“余”人国的国王想重新编制他的国家。他想把他的国家划分成若干个省，每个省都由他们王室联邦的一个成员来管理。

他的国家有 $N$ 个城市，编号为 $1\ldots N$。

一些城市之间有道路相连，任意两个不同的城市之间有且仅有一条直接或间接的道路。

为了防止管理太过分散，每个省至少要有 $B$ 个城市。

为了能有效的管理，每个省最多只有 $3\times B$ 个城市。

每个省必须有一个省会，这个省会可以位于省内，也可以在该省外。

但是该省的任意一个城市到达省会所经过的道路上的城市（除了最后一个城市，即该省省会）都必须属于该省。

一个城市可以作为多个省的省会。

聪明的你快帮帮这个国王吧！
## 输入格式

第一行包含两个数 $N,B$。

接下来 $N－1$ 行，每行描述一条边，包含两个数，即这条边连接的两个城市的编号。
## 输出格式

如果无法满足国王的要求，输出 $0$。

否则第一行输出数 $K$，表示你给出的划分方案中省的个数。

第二行输出 $N$ 个数，第 $I$ 个数表示编号为 $I$ 的城市属于的省的编号。要求城市编号在 $[1,K]$ 范围内。

第三行输出 $K$ 个数，表示这 $K$ 个省的省会的城市编号。

如果有多种方案，你可以输出任意一种。
## 样例

### 样例输入 #1
```
8 2 
1 2 
2 3 
1 8 
8 7 
8 6 
4 6 
6 5 

```
### 样例输出 #1
```
3 
2 1 1 3 3 3 3 2 
2 1 8 

```
## 提示

对于 $100\%$ 的数据，$1\le B\leq N\le 10^3$。

感谢 @[FlierKing](/user/9433) 提供 spj。


---

---
title: "[SCOI2010] 幸运数字"
layout: "post"
diff: 提高+/省选-
pid: P2567
tag: ['2010', '四川', '各省省选', '深度优先搜索 DFS', '剪枝', '容斥原理']
---
# [SCOI2010] 幸运数字
## 题目背景

四川 NOI 省选 2010。

## 题目描述

在中国，很多人都把 $6$ 和 $8$ 视为是幸运数字！lxhgww 也这样认为，于是他定义自己的“幸运号码”是十进制表示中只包含数字 $6$ 和 $8$ 的那些号码，比如 $68$，$666$，$888$ 都是“幸运号码”！但是这种“幸运号码”总是太少了，比如在 $[1,100]$ 的区间内就只有 $6$ 个（$6$，$8$，$66$，$68$，$86$，$88$），于是他又定义了一种“近似幸运号码”。lxhgww 规定，凡是“幸运号码”的倍数都是“近似幸运号码”，当然，任何的“幸运号码”也都是“近似幸运号码”，比如 $12$，$16$，$666$ 都是“近似幸运号码”。

现在 lxhgww 想知道在一段闭区间 $[a, b]$ 内，“近似幸运号码”的个数。
## 输入格式

输入数据是一行，包括 $2$ 个数字 $a$ 和 $b$。
## 输出格式

输出数据是一行，包括 $1$ 个数字，表示在闭区间 $[a, b]$ 内“近似幸运号码”的个数。
## 样例

### 样例输入 #1
```
1 10
```
### 样例输出 #1
```
2
```
## 提示

对于 $30\%$ 的数据，保证 $1\le a\le b\le10^6$。

对于 $100\%$ 的数据，保证 $1\le a\le b\le10^{10}$。



---

---
title: "[NOIP 2015 提高组] 斗地主"
layout: "post"
diff: 提高+/省选-
pid: P2668
tag: ['搜索', '贪心', '2015', 'NOIP 提高组', '深度优先搜索 DFS']
---
# [NOIP 2015 提高组] 斗地主
## 题目背景

NOIP2015 Day1T3
## 题目描述

牛牛最近迷上了一种叫斗地主的扑克游戏。斗地主是一种使用黑桃、红心、梅花、方片的 $A$ 到 $K$ 加上大小王的共 $54$ 张牌来进行的扑克牌游戏。在斗地主中，牌的大小关系根据牌的数码表示如下：$3<4<5<6<7<8<9<10<J<Q<K<A<2<\text{小王}<\text{大王}$，而花色并不对牌的大小产生影响。每一局游戏中，一副手牌由 $n$ 张牌组成。游戏者每次可以根据规定的牌型进行出牌，首先打光自己的手牌一方取得游戏的胜利。

现在，牛牛只想知道，对于自己的若干组手牌，分别最少需要多少次出牌可以将它们打光。请你帮他解决这个问题。

需要注意的是，本题中游戏者每次可以出手的牌型与一般的斗地主相似而略有不同。具体规则如下：

 ![](https://cdn.luogu.com.cn/upload/pic/1827.png) 

**本题数据随机，不支持hack，要hack或强力数据请点击[这里](https://www.luogu.org/problem/P2540)**。

## 输入格式

第一行包含用空格隔开的 $2$ 个正整数 $T,n$，表示手牌的组数以及每组手牌的张数。

接下来 $T$ 组数据，每组数据 $n$ 行，每行一个非负整数对 $a_i,b_i$，表示一张牌，其中 $a_i$ 表示牌的数码，$b_i$ 表示牌的花色，中间用空格隔开。特别的，我们用 $1$ 来表示数码 $A$，$11$ 表示数码 $J$，$12$ 表示数码 $Q$，$13$ 表示数码 $K$；黑桃、红心、梅花、方片分别用 $1-4$ 来表示；小王的表示方法为 `0 1`，大王的表示方法为 `0 2`。
## 输出格式

共 $T$ 行，每行一个整数，表示打光第 $i$ 组手牌的最少次数。
## 样例

### 样例输入 #1
```
1 8
7 4
8 4
9 1
10 4
11 1
5 1
1 4
1 1
```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
1 17
12 3
4 3
2 3
5 4
10 2
3 3
12 2
0 1
1 3
10 1
6 2
12 1
11 3
5 2
12 4
2 2
7 2

```
### 样例输出 #2
```
6

```
## 提示

**样例 1 说明**

共有 $1$ 组手牌，包含 $8$ 张牌：方片 $7$，方片 $8$，黑桃 $9$，方片 $10$，黑桃 $J$，黑桃 $5$，方片 $A$ 以及黑桃 $A$。可以通过打单顺子（方片 $7$，方片 $8$，黑桃 $9$，方片 $10$，黑桃 $J$），单张牌（黑桃 $5$）以及对子牌（黑桃 $A$以及方片 $A$）在 $3$ 次内打光。

对于不同的测试点， 我们约定手牌组数 $T$ 与张数 $n$ 的规模如下：

| 测试点编号 | $T=$ | $n=$ |
| :------: | :----: | :----: |
|  1       |  $100$   |  $2$  |
|  2       |  $100$   |  $2$  |
|  3       |  $100$   |  $3$  |
|  4       |  $100$   |  $3$  |
|  5       |  $100$   |  $4$  |
|  6       |  $100$   |  $4$  |
|  7       |  $100$   |  $10$  |
|  8       |  $100$   |  $11$  |
|  9       |  $100$   |  $12$  |
|  10       |  $100$   |  $13$  |
|  11       |  $100$   |  $14$  |
|  12       |  $100$   |  $15$  |
|  13       |  $10$   |  $16$  |
|  14       |  $10$   |  $17$  |
|  15       |  $10$   |  $18$  |
|  16       |  $10$   |  $19$  |
|  17       |  $10$   |  $20$  |
|  18       |  $10$   |  $21$  |
|  19       |  $10$   |  $22$  |
|  20       |  $10$   |  $23$  |

数据保证：所有的手牌都是随机生成的。



---

---
title: "[USACO5.3] 量取牛奶Milk Measuring"
layout: "post"
diff: 提高+/省选-
pid: P2744
tag: ['动态规划 DP', '搜索', 'USACO', '深度优先搜索 DFS']
---
# [USACO5.3] 量取牛奶Milk Measuring
## 题目描述

农夫约翰要量取 $Q$（$1 \le Q \le 20,000$）夸脱（译注：即 quarts，容积单位）他的最好的牛奶，并把它装入一个大瓶子中卖出。消费者要多少，他就给多少，从不有任何误差。

农夫约翰总是很节约。他现在在奶牛五金商店购买一些桶，用来从他的巨大的牛奶池中量出 $Q$ 夸脱的牛奶。每个桶的价格一样。你的任务是计算出一个农夫约翰可以购买的最少的桶的集合，使得能够刚好用这些桶量出 $Q$ 夸脱的牛奶。另外，由于农夫约翰必须把这些桶搬回家，对于给出的两个极小桶集合，他会选择“更小的”一个，即：把这两个集合按升序排序，比较第一个桶，选择第一个桶容积较小的一个。如果第一个桶相同，比较第二个桶，也按上面的方法选择。否则继续这样的工作，直到相比较的两个桶不一致为止。例如，集合 $\{3,5,7,100\}$ 比集合 $\{3,6,7,8\}$ 要好。

为了量出牛奶，农夫约翰可以从牛奶池把桶装满，然后倒进瓶子。他决不把瓶子里的牛奶倒出来或者把桶里的牛奶倒到别处。用一个容积为 $1$ 夸脱的桶，农夫约翰可以只用这个桶量出所有可能的夸脱数。其它的桶的组合没有这么方便。

计算需要购买的最佳桶集，保证所有的测试数据都至少有一个解。
## 输入格式

第一行一个整数 $Q$。

第二行一个整数 $P\ (1 \le  P \le 100)$，表示商店里桶的数量。

第 $3$ 至第 $P+2$ 行，每行一个整数 $h_i$ 表示第 $i$ 个桶的容积。$(1\le h_i\le 10^4)$。

## 输出格式

输出文件只有一行，由空格分开的整数组成：

为了量出想要的夸脱数，需要购买的最少的桶的数量，接着是：

一个排好序的列表（从小到大），表示需要购买的每个桶的容积

## 样例

### 样例输入 #1
```
16

3

3

5

7
```
### 样例输出 #1
```
2 3 5
```
## 提示

题目翻译来自NOCOW。

USACO Training Section 5.3



---

---
title: "[USACO07MAR] Cow Traffic S"
layout: "post"
diff: 提高+/省选-
pid: P2883
tag: ['动态规划 DP', '递推', '2007', 'USACO', '深度优先搜索 DFS']
---
# [USACO07MAR] Cow Traffic S
## 题目描述

The bovine population boom down on the farm has caused serious congestion on the cow trails leading to the barn. Farmer John has decided to conduct a study to find the bottlenecks in order to relieve the 'traffic jams' at milking time.

The pasture contains a network of M (1 ≤ M ≤ 50,000) one-way trails, each of which connects exactly two different intersections from the set of N (1 ≤ N ≤ 5,000) intersections conveniently numbered 1..N; the barn is at intersection number N. Each trail connects one intersection point to another intersection point with a higher number. As a result, there are no cycles and, as they say on the farm, all trails lead to the barn. A pair of intersection points might be connected by more than one trail.

During milking time rush hour, the cows start from their respective grazing locations and head to the barn. The grazing locations are exactly those intersection points with no trails connecting into them. Each cow traverses a 'path', which is defined as a sequence of trails from a grazing location to the barn.

Help FJ finding the busiest trail(s) by computing the largest number of possible paths that contain any one trail. The answer is guaranteed to fit in a signed 32-bit integer.

随着牛的数量增加，农场的道路的拥挤现象十分严重，特别是在每天晚上的挤奶时间。为了解决这个问题，FJ决定研究这个问题，以能找到导致拥堵现象的瓶颈所在。


牧场共有M条单向道路，每条道路连接着两个不同的交叉路口，为了方便研究，FJ将这些交叉路口编号为1..N,而牛圈位于交叉路口N。任意一条单向道路的方向一定是是从编号低的路口到编号高的路口，因此农场中不会有环型路径。同时，可能存在某两个交叉路口不止一条单向道路径连接的情况。


在挤奶时间到来的时候，奶牛们开始从各自的放牧地点回到牛圈。放牧地点是指那些没有道路连接进来的路口（入度为0的顶点）。


现在请你帮助fj通过计算从放牧点到达牛圈的路径数目来找到最繁忙的道路，即求出所有可行路径中通过某条道路的最大值（答案保证是不超过32位整数）。

## 输入格式

Line 1: Two space-separated integers: N and M.


Lines 2..M+1: Two space-separated intersection points.

## 输出格式

Line 1: The maximum number of paths passing through any one trail.

## 样例

### 样例输入 #1
```
7 7
1 3
3 4
3 5
4 6
2 3
5 6
6 7
```
### 样例输出 #1
```
4
```
## 提示

Here are the four possible paths that lead to the barn:


1 3 4 6 7


1 3 5 6 7


2 3 4 6 7


2 3 5 6 7



---

---
title: "[USACO09NOV] Lights G"
layout: "post"
diff: 提高+/省选-
pid: P2962
tag: ['搜索', '2009', 'USACO', 'O2优化', '深度优先搜索 DFS', '高斯消元']
---
# [USACO09NOV] Lights G
## 题目背景

[English Edition](/paste/410oq6t5)
## 题目描述

给出一张 $n$ 个点 $m$ 条边的无向图，每个点的初始状态都为 $0$。  

你可以操作任意一个点，操作结束后该点以及所有与该点相邻的点的状态都会改变，由 $0$ 变成 $1$ 或由 $1$ 变成 $0$。  

你需要求出最少的操作次数，使得在所有操作完成之后所有 $n$ 个点的状态都是 $1$。
## 输入格式

第一行两个整数 $n, m$。

之后 $m$ 行，每行两个整数 $a, b$，表示在点 $a, b$ 之间有一条边。
## 输出格式

一行一个整数，表示最少需要的操作次数。

本题保证有解。
## 样例

### 样例输入 #1
```
5 6 
1 2 
1 3 
4 2 
3 4 
2 5 
5 3 

```
### 样例输出 #1
```
3 

```
## 提示

对于 $100\%$ 的数据，$1\le n\le35,1\le m\le595, 1\le a,b\le n$。保证没有重边和自环。


---

---
title: "[USACO10FEB] Slowing down G"
layout: "post"
diff: 提高+/省选-
pid: P2982
tag: ['2010', '线段树', 'USACO', '树状数组', '深度优先搜索 DFS']
---
# [USACO10FEB] Slowing down G
## 题目描述

Every day each of Farmer John's N $(1 \le N \le 100,000)$ cows conveniently numbered $1..N$ move from the barn to her private pasture. The pastures are organized as a tree, with the barn being on pasture $1$. Exactly $N-1$ cow unidirectional paths connect the pastures; directly connected pastures have exactly one path. Path $i$ connects pastures $A_i$ and $B_i$ $(1 \le A_i \le N,1 \le B_i \le N)$.

Cow $i$ has a private pasture $P_i(1 \le P_i \le N)$. The barn's small door lets only one cow exit at a time; and the patient cows wait until their predecessor arrives at her private pasture. First cow $1$ exits and moves to pasture $P_1$. Then cow $2$ exits and goes to pasture $P_2$, and so on.

While cow $i$ walks to $P_i$ she might or might not pass through a pasture that already contains an eating cow. When a cow is present in a pasture, cow $i$ walks slower than usual to prevent annoying her friend.

```cpp
Consider the following pasture network, where the number between
parentheses indicates the pastures' owner.

        1 (3)        
       / \
  (1) 4   3 (5)
     / \   
(2) 2   5 (4)

First, cow 1 walks to her pasture:

        1 (3)        
       / \
  [1] 4*  3 (5)
     / \   
(2) 2   5 (4)

When cow 2 moves to her pasture, she first passes into the barn's
pasture, pasture 1. Then she sneaks around cow 1 in pasture 4 before
arriving at her own pasture.

        1 (3)
       / \
  [1] 4*  3 (5)
     / \   
[2] 2*  5 (4)

Cow 3 doesn't get far at all -- she lounges in the barn's pasture, #1.

        1* [3]
       / \
  [1] 4*  3 (5)
     / \   
[2] 2*  5 (4)

Cow 4 must slow for pasture 1 and 4 on her way to pasture 5:

        1* [3]
       / \
  [1] 4*  3 (5)
     / \   
[2] 2*  5* [4]

Cow 5 slows for cow 3 in pasture 1 and then enters her own private pasture:

        1* [3]
       / \
  [1] 4*  3*[5]
     / \   
[2] 2*  5* [4]
```

FJ would like to know how many times each cow has to slow down.

每天 Farmer John 的 $N$ 头奶牛，编号 $1 \ldots N$，从粮仓走向他的自己的牧场。牧场构成了一棵树，粮仓在 $1$ 号牧场。恰好有 $N-1$ 条道路直接连接着牧场，使得牧场之间都恰好有一条路径相连。第 $i$ 条路连接着 $A_i$ 和 $B_i$。奶牛们每人有一个私人牧场 $P_i$。粮仓的门每次只能让一只奶牛离开。耐心的奶牛们会等到他们的前面的朋友们到达了自己的私人牧场后才离开。首先奶牛 $1$ 离开，前往 $P_1$；然后是奶牛 $2$，以此类推。

当奶牛 $i$ 走向牧场 $P_i$ 的时候，他可能会经过正在吃草的同伴旁。当路过已经有奶牛的牧场时，奶牛 $i$ 会放慢自己的速度，防止打扰他的朋友。

FJ 想要知道奶牛们总共要放慢多少次速度。
## 输入格式


\* Line $1$: Line $1$ contains a single integer: $N$

\* Lines $2..N$: Line $i+1$ contains two space-separated integers: $A_i$ and $B_i$

\* Lines $N+1..N+N$: line $N+i$ contains a single integer: $P_i$

第一行：有一个整数 $N$。

第 $2 \sim N$ 行：第 $i+1$ 行有两个以空格隔开的整数 $A_i$ 和 $B_i$。

第 $N+1 \sim N+N$ 行：第 $N+i$ 行有一个整数 $P_i$。
## 输出格式

\* Lines $1 \sim N$：Line $i$ contains the number of times cow $i$ has to slow down.

第 $1 \sim N$ 行：第 $i$ 行包括奶牛 $i$ 需要放慢速度的次数。
## 样例

### 样例输入 #1
```
5 
1 4 
5 4 
1 3 
2 4 
4 
2 
1 
5 
3 

```
### 样例输出 #1
```
0 
1 
0 
2 
1 

```
## 提示

数据范围：$1 \leq A_i,B_i,P_i\leq N \leq 10^5$。


---

---
title: "[USACO11FEB] The Lost Cows G"
layout: "post"
diff: 提高+/省选-
pid: P3013
tag: ['模拟', '字符串', '2011', 'USACO', 'Special Judge', '深度优先搜索 DFS']
---
# [USACO11FEB] The Lost Cows G
## 题目描述

One sunny day farmer John was kidnapped by evil farmer Marcus's cows. FJ wasn't too concerned about his forced holiday but wanted to make sure that his cows got home safely together.

The cows are spread out in every one of FJ's N (3 <= N <= 200) pastures conveniently numbered 1..N. The barn is located at pasture 1. The farm has an interesting navigation system: at every pasture i there are M (1 <= M <= 200) signs S\_ij (1 <= S\_ij <= N) which one could reference as S\_i1..S\_iM; each sign points the way to a pasture. Sometimes a sign points to a path that leads back to the same

pasture.

Farmer Marcus's cows allow FJ to write a single message to all of his cows. FJ's plan is to write a list of sign numbers such that any cow who follows those instructions will all arrive at the barn when each cow has completed all the instructions.

When a cow starts at a given pasture then she will first follow the path indicated by the first sign number on FJ's list. When she arrives at the second pasture, she looks at the second sign of FJ's list and follows the path marked by that sign. She continues until she exhausts the instruction list, at which point she should be at the barn.

Find a list of instructions containing no more than 5,000,000 sign numbers that will guide every cow, from every pasture, to the barn after all instructions are followed.  It is guaranteed that such a list exists.

Consider a set of three signs in four pastures that direct the cows like these do:

```cpp
** Pasture# ** 
1    2    3    4 
Sign 1   4    4    1    3 
Sign 2   1    3    2    4 
Sign 3   4    2    3    1 
```
The set of instructions below will direct cows to the barn from any of the four pastures:

```cpp
Instruction#   Sign#            Instruction#   Sign# 
1           1                   5           3 
2           2                   6           1 
3           1                   7           3 
4           2 
```
The cow in pasture 1 will read sign #1 at time 1 and be directed to pasture 4.  At time 2, she is in pasture 4 and (per FJ's

instructions) read sign #2 and then be directed to pasture 4. Below is a table that shows the cow's travels:

```cpp
* * * *  Cow in pasture  1  * * * * 
Time    CurrentPasture#    WhichSign     Sign->Nextpasture 
1            1               1                4 
2            4               2                4 (same pasture!) 
3            4               1                3 
4            3               2                2 
5            2               3                2 (same pasture)
6            2               1                4 
7            4               3                1 Barn! 
```
Similarly: Pasture 2's cow visits pastures [2]-4-4-3-2-2-4-1. Pasture 3's cow visits pastures [3]-1-1-4-4-1-4-1.

Pasture 4's cow visits pastures [4]-3-2-4-4-1-4-1.


Given a set of signs, create a set of instructions. 

## 输入格式

\* Line 1: Two space separated integers: N and M

\* Lines 2..M+1: Line i+1 describes the contents of each pasture's N signs with N integers: S\_1i..S\_Ni

## 输出格式

\* Lines 1..?: The sign numbers the cows should follow, one per line.

## 样例

### 样例输入 #1
```
4 3 
4 4 1 3 
1 3 2 4 
4 2 3 1 

```
### 样例输出 #1
```
1 
2 
1 
2 
3 
1 
3 

```
## 题目翻译

### 题目描述

给定一张 $n(3\leq n\leq 200)$ 个点的图，每个点都恰好有 $m(1\leq m\leq 200)$ 条出边，第 $i$ 个点的第 $j$ 条出边指向 $a_{i,j}$。

现在这张图上每个点都有一头牛。每次你可以报出一个数 $x(1\leq x\leq m)$，这会使得每一头牛沿着当前所在的点的第 $x$ 条边走一步（即当前在点 $u$ 的牛移动到点 $a_{u,x}$）。

你需要发出不超过 $5\times 10^6$ 条指令，使得在所有的指令执行完后，所有的牛都在编号为 $1$ 的点上。

### 输入格式

第一行两个整数 $n,m$。

接下来 $m$ 行每行 $n$ 个整数，第 $i$ 行的第 $j$ 个整数是 $a_{j,i}$。

### 输出格式

在第 $i$ 行输出你发出的第 $i$ 条指令。


---

---
title: "[USACO13FEB] Perimeter S"
layout: "post"
diff: 提高+/省选-
pid: P3072
tag: ['2013', '线段树', 'USACO', '深度优先搜索 DFS']
---
# [USACO13FEB] Perimeter S
## 题目背景

征求翻译。如果你能提供翻译或者题意简述，请直接发讨论，感谢你的贡献。

## 题目描述

Farmer John has arranged N hay bales (1 <= N <= 50,000) in the middle of one of his fields.  If we think of the field as a 1,000,000 x 1,000,000 grid of 1 x 1 square cells, each hay bale occupies exactly one of these cells (no two hay bales occupy the same cell, of course).

FJ notices that his hay bales all form one large connected region, meaning that starting from any bale, one can reach any other bale by taking a series of steps either north, south, east, or west onto directly adjacent bales.  The connected region of hay bales may however contain "holes" -- empty regions that are completely surrounded by hay bales.

Please help FJ determine the perimeter of the region formed by his hay bales.  Note that holes do not contribute to the perimeter.

## 输入格式

\* Line 1: The number of hay bales, N.

\* Lines 2..1+N: Each line contains the (x,y) location of a single hay bale, where x and y are integers both in the range

1..1,000,000. Position (1,1) is the lower-left cell in FJ's field, and position (1000000,1000000) is the upper-right cell.

## 输出格式

\* Line 1: The perimeter of the connected region of hay bales.

## 样例

### 样例输入 #1
```
8 
10005 200003 
10005 200004 
10008 200004 
10005 200005 
10006 200003 
10007 200003 
10007 200004 
10006 200005 

```
### 样例输出 #1
```
14 

```
## 提示

The connected region consisting of hay bales looks like this:

XX
X XX
XXX

The length of the perimeter of the connected region is 14 (for example, the left side of the region contributes a length of 3 to this total).  Observe that the hole in the middle does not contribute to this number.

## 题目翻译

农夫约翰已经在他的一片田地中间放置了n（1<=n<=50000）个干草堆。我们可以认为这片田地是由1000000*1000000 个小方格组成的矩阵，每个干草堆占据一个小方格（当然，没有两堆干草占据同一个格子）

FJ 注意到他的干草堆组成了一个大的连通块，这就意味着从任何一个草堆走起，可以通过相邻草堆走若干步到达其他任意的草堆。这个连通块的内部可能包含若干个“洞”——被干草堆完全包围的空白格子。

请帮助FJ计算整个连通块的周长。计算周长时请不要考虑“洞”。

##   输入格式

第一行：干草堆的数量 n

第2~n+1行：每行两个数，表示干草堆的坐标（x，y），满足1<=x,y<=1000000 

## 输出格式
连通块的周长p
 


---

---
title: "[HAOI2015] 树上操作"
layout: "post"
diff: 提高+/省选-
pid: P3178
tag: ['2015', '河南', '线段树', '深度优先搜索 DFS', '树链剖分']
---
# [HAOI2015] 树上操作
## 题目描述

有一棵点数为 $N$ 的树，以点 $1$ 为根，且树有点权。然后有 $M$ 个操作，分为三种：
- 操作 $1$：把某个节点 $x$ 的点权增加 $a$。
- 操作 $2$：把某个节点 $x$ 为根的子树中所有点的点权都增加 $a$。
- 操作 $3$：询问某个节点 $x$ 到根的路径中所有点的点权和。

## 输入格式

第一行包含两个整数 $N,M$。表示点数和操作数。  
接下来一行 $N$ 个整数，表示树中节点的初始权值。  
接下来 $N-1$ 行每行两个正整数 $\mathit{from},\mathit{to}$， 表示该树中存在一条边 $(\mathit{from},\mathit{to})$。  
再接下来 $M$ 行，每行分别表示一次操作。其中第一个数表示该操作的种类，之后接这个操作的参数。

## 输出格式

对于每个询问操作，输出该询问的答案。答案之间用换行隔开。

## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 2
1 4
2 3
2 5
3 3
1 2 1
3 5
2 1 2
3 3
```
### 样例输出 #1
```
6
9
13
```
## 提示

对于 $100\%$ 的数据，$1\le N,M\le10^5$，且所有输入数据的绝对值都不会超过 $10^6$。



---

---
title: "[HNOI2012] 矿场搭建"
layout: "post"
diff: 提高+/省选-
pid: P3225
tag: ['2012', '湖南', '深度优先搜索 DFS', 'Tarjan', '双连通分量']
---
# [HNOI2012] 矿场搭建
## 题目描述

煤矿工地可以看成是由隧道连接挖煤点组成的无向图。为安全起见，希望在工地发生事故时所有挖煤点的工人都能有一条出路逃到救援出口处。于是矿主决定在某些挖煤点设立救援出口，使得无论哪一个挖煤点坍塌之后，其他挖煤点的工人都有一条道路通向救援出口。

请写一个程序，用来计算至少需要设置几个救援出口，以及不同最少救援出口的设置方案总数。

## 输入格式

输入文件有若干组数据。

每组数据的第一行是一个正整数 $N\ (N \le 500)$，表示工地的隧道数。

接下来的 $N$ 行每行是用空格隔开的两个整数 $S$ 和 $T$，表示挖煤点 $S$ 与挖煤点 $T$ 由隧道直接连接。

输入数据以 $0$ 结尾。
## 输出格式

对于每组数据，输出一行。

第 $i$ 行组数据以 $\verb!Case i: !$ 开始（注意大小写，$\verb!Case!$ 与 $\verb!i!$ 之间有空格，$\verb!i!$ 与 $\verb!:!$ 之间无空格，$\verb!:!$ 之后有空格）。

其后是用空格隔开的两个正整数，第一个正整数表示对于第 $i$ 组输入数据至少需要设置几个救援出口，第二个正整数表示对于第 $i$ 组输入数据不同最少救援出口的设置方案总数。

输入数据保证答案小于 $2^{64}$。输出格式参照以下输入输出样例。

## 样例

### 样例输入 #1
```
9
1 3
4 1
3 5
1 2
2 6
1 5
6 3
1 6
3 2
6
1 2
1 3
2 4
2 5
3 6
3 7
0
```
### 样例输出 #1
```
Case 1: 2 4
Case 2: 4 1
```
## 提示

### 样例解释

- Case 1 的四组解分别是 $(2,4)$，$(3,4)$，$(4,5)$，$(4,6)$；
- Case 2 的一组解为 $(4,5,6,7)$。

### 数据范围及约定

对于每组数据，设 $m$ 为各组 $S, T$ 中最大值，则有：

- $1 \le m \le 10^3$；
- 各组 $S, T$ 构成的集合 $V = [1, m] \cap \mathbb Z$。
- $V$ 中任意两点连通。


---

---
title: "[HNOI2013] 比赛"
layout: "post"
diff: 提高+/省选-
pid: P3230
tag: ['搜索', '2013', '湖南', '深度优先搜索 DFS', '哈希 hashing']
---
# [HNOI2013] 比赛
## 题目描述

沫沫非常喜欢看足球赛，但因为沉迷于射箭游戏，错过了最近的一次足球联赛。此次联赛共 $N$ 支球队参加，比赛规则如下：

1. 每两支球队之间踢一场比赛；

2. 若平局，两支球队各得 $1$ 分；

3. 否则胜利的球队得 $3$ 分，败者不得分。 尽管非常遗憾没有观赏到精彩的比赛，但沫沫通过新闻知道了每只球队的最后总得分， 然后聪明的她想计算出有多少种可能的比赛过程。

譬如有 $3$ 支球队，每支球队最后均积 $3$ 分，那么有两种可能的情况：

可能性 $1$ and 可能性 $2$

| 球队 | $A$ | $B$ | $C$ | 得分 | 球队 | $A$ | $B$ | $C$ | 得分 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $A$ | - | $3$ | $0$ | $3$ | $A$ | - | $0$ | $3$ | $3$ |
| $B$ | $0$ | - | $3$ | $3$ | $B$ | $3$ | - | $0$ | $3$ |
| $C$ | $3$ | $0$ | - | $3$ | $C$ | $0$ | $3$ | - | $3$ |

但沫沫发现当球队较多时，计算工作量将非常大，所以这个任务就交给你了。请你计算出可能的比赛过程的数目，由于答案可能很大，你只需要输出答案对 $10^9+7$ 取模的结果。
## 输入格式

第一行是一个正整数 $N$，表示一共有 $N$ 支球队。 接下来一行 $N$ 个非负整数，依次表示各队的最后总得分。 输入保证 $20\%$ 的数据满足 $N\leq4$，$40\%$ 的数据满足 $N\leq6$，$60\%$ 的数据满足 $N\leq8$，$100\%$ 的数据满足 $3\leq N\leq10$ 且至少存在一组解。

## 输出格式

仅包含一个整数，表示答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
4
4 3 6 4
```
### 样例输出 #1
```
3
```
## 提示

$20\%$ 的数据满足 $N≤4$;

$40\%$ 的数据满足 $N≤6$;

$60\%$ 的数据满足 $N≤8$;

$100\%$ 的数据满足 $3≤N≤10$ 且至少存在一组解。


---

---
title: "[SDOI2015] 排序"
layout: "post"
diff: 提高+/省选-
pid: P3322
tag: ['搜索', '2015', '山东', '排序', '深度优先搜索 DFS']
---
# [SDOI2015] 排序
## 题目描述

小 A 有一个 $1\sim 2^N$ 的排列 $A_1\sim A_{2^N}$，他希望将 $A$ 数组从小到大排序,小 $A$ 可以执行的操作有 $N$ 种，每种操作最多可以执行一次，对于所有的 $i(1\le i\le N)$，第 $i$ 种操作为将序列从左到右划分为 $2^{N-i+1}$ 段，每段恰好包括 $2^{i-1}$ 个数,然后整体交换其中两段。

小 A 想知道可以将数组 $A$ 从小到大排序的不同的操作序列有多少个。小 A 认为两个操作序列不同，当且仅当操作个数不同，或者至少一个操作不同（种类不同或者操作位置不同）。

下面是一个操作事例: $N=3,A=[3,6,1,2,7,8,5,4]$。
- 第一次操作，执行第 $3$ 种操作，交换 $A[1..4]$ 和 $A[5..8]$，交换后的 $A$ 为$[7,8,5,4,3,6,1,2]$。
- 第二次操作，执行第 $1$ 种操作，交换 $A[3]$ 和 $A[5]$，交换后的 $A$ 为$[7,8,3,4,5,6,1,2]$。
- 第三次操作，执行第 $2$ 种操作，交换 $A[1..2]$ 和 $A[7..8]$，交换后的 $A[1..8]$ 为$[1,2,3,4,5,6,7,8]$。
## 输入格式

第一行，一个整数 $N$。

第二行，$2^N$ 个整数，$A_1\sim A_{2^N}$。
## 输出格式

一个整数表示答案。

## 样例

### 样例输入 #1
```
3
7 8 5 6 1 2 4 3
```
### 样例输出 #1
```
6
```
## 提示

$100\%$ 的数据, $1\le N\le 12$。



---

---
title: "[POI 2007] BIU-Offices"
layout: "post"
diff: 提高+/省选-
pid: P3452
tag: ['2007', '线性数据结构', 'POI（波兰）', '深度优先搜索 DFS']
---
# [POI 2007] BIU-Offices
## 题目描述

Bytel is a mobile telephony potentate. Each employee has been issued a company phone, the memory ofwhich holds the numbers of some of his co-workers (all of them have his number in their phones as well).

Due to dynamic growth of their operations the board of directors intends to move company headquaters tonew office buildings. It has been decided - in order to boost work efficiency - that every pair of employeesworking in different buildings should know (reciprocally) each others phone number i.e. the memory of theircompany phone ought to hold necessary phone numbers.

Simultaneously, the board have decided to rent as many office buildings as possible to ensure good workingconditions. Help the board of Bytel to plan the number of office buildings and their size in accordancewith the aforementioned requirements.

## Task

Write a programme which:

reads the description of employees' phone number lists from the standard input        calculates the maximal number of office buildings and their sizes, satisfying board's conditions        writes the outcome to the standard output.
## 输入格式

The first line of the standard input consists of two integers: $n$ and $m$ ($2 \le n \le 100\ 000$, $1 \le m \le 2\ 000\ 000$),separated by single spaces, denoting the number of Bytel employees and the number of pairs of employeeswho have their numbers in company phones, respectively. The employees are numbered from $1$ to $n$.

Each of the following $m$ lines contains a single pair of integers $a_i$ and $b_i$ ($1 \le a_i < b_i \le n$ for $1 \le i \le m$), separated by a single space, denoting that employees $a_i$ and $b_i$ have their numbers (reciprocally) in company phones' memory. Each pair of integers denoting a pair of employees shall occur once at the most in the standard input.

## 输出格式

The first line of the standard output should contain a single integer: the maximal number of office buildingsthat Bytel should rent. The second should contain a non-decreasing sequence of positive integers, separatedby singe spaces, denoting the sizes of the office buildings (i.e. the numbers of employees working there).

Should there exist more than one correct answer - write out any one of them.

## 样例

### 样例输入 #1
```
7 16
1 3
1 4
1 5
2 3
3 4
4 5
4 7
4 6
5 6
6 7
2 4
2 7
2 5
3 5
3 7
1 7
```
### 样例输出 #1
```
3
1 2 4
```
## 题目翻译

## 题目描述

Bytel 是一家移动通信公司。该公司的每位员工都收到了一部公司生产的电话，电话的通讯录中存储着一些同事的电话号码（每部手机中也都有该手机本身的电话号码）。

由于业务扩张，公司总部需要迁移至新的办公区。为了提高工作效率，董事会决定在不同栋楼工作的每一对员工需要**相互**知道对方的电话号码。即如果 $u$ 和 $v$ 在不同的楼工作，则 $u$ 的通讯录里需要存储 $v$ 的电话号，$v$ 的通讯录里也要存储 $u$ 的电话号码。

同时，董事会决定租用尽可能多的楼，以确保良好的工作条件。现在你需要帮助 Bytel 公司计算出他们需要租用多少栋楼。

## 输入格式

输入第一行包含两个整数 $n,m$，分别代表公司的员工数和通讯录的信息数，员工从 $1$ 到 $n$ 编号。

接下来 $m$ 行，每行两个整数 $a_i,b_i$，表示 $a_i$ 和 $b_i$ **相互**知道对方的电话号码，保证任意两条信息不重复。

## 输出格式

输出第一行包含一个整数 $t$：董事会需要租用多少栋办公楼。

第二行包含 $t$ 个整数，第 $i$ 个整数 $c_i$ 表示在第 $i$ 栋建筑工作的员工数量。你的输出需要保证 $c_i$ 是单调不下降的。

如果有多种合法方案，你可以输出任意一种。

## 数据范围

$2 \leq n \leq 10^5$，$1 \leq m \leq 2 \times 10^6$，$1 \leq a_i \lt b_i \leq n$。


---

---
title: "[POI 2007] MEG-Megalopolis"
layout: "post"
diff: 提高+/省选-
pid: P3459
tag: ['2007', '线段树', '树状数组', 'POI（波兰）', '深度优先搜索 DFS', '栈']
---
# [POI 2007] MEG-Megalopolis
## 题目描述

Byteotia has been eventually touched by globalisation, and so has Byteasar the Postman, who once roamedthe country lanes amidst sleepy hamlets and who now dashes down the motorways. But it is those strolls inthe days of yore that he reminisces about with a touch of tenderness.

In the olden days $n$ Byteotian villages (numbered from $1$ to $n$) were connected by bidirectional dirt roadsin such a way, that one could reach the village number $1$ (called Bitburg) from any other village in exactlyone way. This unique route passed only through villages with number less or equal to that of the startingvillage. Furthermore, each road connected exactly two distinct villages without passing through any othervillage. The roads did not intersect outside the villages, but tunnels and viaducts were not unheard of.

Time passing by, successive roads were being transformed into motorways. Byteasar remembers distinctly,  when each of the country roads so disappeared. Nowadays, there is not a single country lane left  in Byteotia - all of them have been replaced with motorways, which connect the villages into Byteotian  Megalopolis.

Byteasar recalls his trips with post to those villages. Each time he was beginning his journey with letters  to some distinct village in Bitburg. He asks you to calculate, for each such journey (which took place in a      specific moment of time and led from Bitburg to a specified village), how many country roads it led through.

TaskWrite a programme which:

reads from the standard input:

descriptions of roads that once connected Byteotian villages,    sequence of events: Byteasar's trips and the moments when respective roads were transformed    into motorways,            for each trip, calculates how many country roads Byteasar has had to walk,        writes the outcome to the standard output.


有一棵节点数为 $n$ 的树，给定 $m + n - 1$ 组询问，每组询问有两种操作。

1. `A x y`，将 $x$ 节点和 $y$ 节点间的边权改为 $0$，每条边会被修改恰好一次。

2. `W x`，求 $1$ 号点到 $x$ 号点路径上的边权和。

初始所有边权值都为 $1$。
## 输入格式

In the first line of the standard input there is a single integer $n$ ($1\le n\le 250\ 000$),denoting the number of villages in Byteotia. The following $n-1$ lines contain descriptions of the roads, in the form of two integers $a$,$b$ ($1\le a<b\le n$)separated by a single space, denoting the numbers of villages connected with a road. Inthe next line there is a single integer $m$($1\le m\le 250\ 000$),denoting the number of trips Byteasar has made.

The following $n+m-1$ lines contain descriptions of the events, in chronological order:

A description of the form "A $a$ $b$"(for $a<b$) denotes a country road between villages $a$ and $b$ beingtransformed into a motorway in that particular moment.

A description of the from "W $a$" denotes Byteasar's trip from Bitburg to village $a$.

## 输出格式

Your programme should write out exactly $m$ integers to the standard output, one a line, denoting the numberof country roads Byteasar has travelled during his successive trips.

## 样例

### 样例输入 #1
```
5
1 2
1 3
1 4
4 5
4
W 5
A 1 4
W 5
A 4 5
W 5
W 2
A 1 2
A 1 3
```
### 样例输出 #1
```
2
1
0
1
```


---

---
title: "[POI 2008] POD-Subdivision of Kingdom"
layout: "post"
diff: 提高+/省选-
pid: P3475
tag: ['2008', 'POI（波兰）', 'Special Judge', '深度优先搜索 DFS', '状压 DP']
---
# [POI 2008] POD-Subdivision of Kingdom
## 题目背景

[English Edition](/paste/eu7u3hqg)
## 题目描述

给出一张有 $n$ 个点 $m$ 条边的无向图，你需要求出一组合法的方案，使得图被划分为点数均为 $\frac n2$ 的两个集合，且两个端点在不同集合中的边数最少。
## 输入格式

第一行两个整数 $n,m$。

之后 $m$ 行，每行两个整数 $a, b$，表示在 $a$ 与 $b$ 之间有一条边。
## 输出格式

一行 $\frac n2$ 个整数，表示在你求出的方案中的一个集合的所有点，由编号从小到大排序。
## 样例

### 样例输入 #1
```
6 8
1 2
1 6
2 3
2 5
2 6
3 4
4 5
5 6

```
### 样例输出 #1
```
1 2 6

```
## 提示

对于 $100\%$ 的数据，$1\le n\le 26$，$1\le a,b\le n$，且 $n$ 为偶数。保证没有重边。


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
title: "[USACO17JAN] Promotion Counting P"
layout: "post"
diff: 提高+/省选-
pid: P3605
tag: ['2017', '线段树', 'USACO', '树状数组', '离散化', '深度优先搜索 DFS']
---
# [USACO17JAN] Promotion Counting P
## 题目描述

奶牛们又一次试图创建一家创业公司，还是没有从过去的经验中吸取教训——牛是可怕的管理者！

为了方便，把奶牛从 $1\sim n$ 编号，把公司组织成一棵树，1 号奶牛作为总裁（这棵树的根节点）。除了总裁以外的每头奶牛都有一个单独的上司（它在树上的 “双亲结点”）。  

所有的第 $i$ 头牛都有一个不同的能力指数 $p_i$，描述了她对其工作的擅长程度。如果奶牛 $i$ 是奶牛 $j$ 的祖先节点，那么我们我们把奶牛 $j$ 叫做 $i$ 的下属。

不幸地是，奶牛们发现经常发生一个上司比她的一些下属能力低的情况，在这种情况下，上司应当考虑晋升她的一些下属。你的任务是帮助奶牛弄清楚这是什么时候发生的。简而言之，对于公司的中的每一头奶牛 $i$，请计算其下属 $j$ 的数量满足 $p_j > p_i$。

## 输入格式

输入的第一行包括一个整数 $n$。

接下来的 $n$ 行包括奶牛们的能力指数 $p_1,p_2 \dots p_n$。保证所有数互不相同。

接下来的 $n-1$ 行描述了奶牛 $2 \sim n$ 的上司的编号。再次提醒，1 号奶牛作为总裁，没有上司。

## 输出格式

输出包括 $n$ 行。输出的第 $i$ 行应当给出有多少奶牛 $i$ 的下属比奶牛 $i$ 能力高。

## 样例

### 样例输入 #1
```
5
804289384
846930887
681692778
714636916
957747794
1
1
2
3
```
### 样例输出 #1
```
2
0
1
0
0
```
## 提示

 对于 $100\%$ 的数据，$1\le n \le 10^5$，$1 \le p_i \le 10^9$。


---

---
title: "[USACO17FEB] Why Did the Cow Cross the Road I G"
layout: "post"
diff: 提高+/省选-
pid: P3659
tag: ['2017', 'USACO', '广度优先搜索 BFS', '深度优先搜索 DFS', '最短路']
---
# [USACO17FEB] Why Did the Cow Cross the Road I G
## 题目描述

Why did the cow cross the road? Well, one reason is that Farmer John's farm simply has a lot of roads, making it impossible for his cows to travel around without crossing many of them.

FJ's farm is arranged as an $N \times N$ square grid of fields ($3 \leq N \leq 100$), with a set of $N-1$ north-south roads and $N-1$ east-west roads running through the interior of the farm serving as dividers between the fields. A tall fence runs around the external perimeter, preventing cows from leaving the farm. Bessie the cow can move freely from any field to any other adjacent field (north, east, south, or west), as long as she carefully looks both ways before crossing the road separating the two fields. It takes her $T$ units of time to cross a road ($0 \leq T \leq 1,000,000$).

One day, FJ invites Bessie to visit his house for a friendly game of chess. Bessie starts out in the north-west corner field and FJ's house is in the south-east corner field, so Bessie has quite a walk ahead of her. Since she gets hungry along the way, she stops at every third field she visits to eat grass (not including her starting field, but including possibly the final field in which FJ's house resides). Some fields are grassier than others, so the amount of time required for stopping to eat depends on the field in which she stops.

Please help Bessie determine the minimum amount of time it will take to reach FJ's house.
## 输入格式

The first line of input contains $N$ and $T$. The next $N$ lines each contain $N$ positive integers (each at most 100,000) describing the amount of time required to eat grass in each field. The first number of the first line is the north-west corner.

## 输出格式

Print the minimum amount of time required for Bessie to travel to FJ's house.
## 样例

### 样例输入 #1
```
4 2
30 92 36 10
38 85 60 16
41 13 5 68
20 97 13 80
```
### 样例输出 #1
```
31
```
## 提示

The optimal solution for this example involves moving east 3 squares (eating the "10"), then moving south twice and west once (eating the "5"), and finally moving south and east to the goal.
## 题目翻译

### 题目描述

奶牛为什么要过马路？其中一个原因是 Farmer John 的农场有很多道路，使得他的奶牛在四处走动时不可避免地要穿过许多道路。

FJ 的农场被安排成一个 $N \times N$ 的方形网格田地（$3 \leq N \leq 100$），其中有 $N-1$ 条南北向的道路和 $N-1$ 条东西向的道路穿过农场内部，作为田地之间的分隔。农场外部有一圈高高的围栏，防止奶牛离开农场。奶牛 Bessie 可以自由地从任何田地移动到相邻的田地（北、东、南或西），只要她在穿过分隔两块田地的道路时小心地左右看看。她穿过一条道路需要花费 $T$ 单位时间（$0 \leq T \leq 1,000,000$）。

有一天，FJ 邀请 Bessie 去他家进行一场友好的国际象棋比赛。Bessie 从西北角的田地出发，而 FJ 的家在东南角的田地，因此 Bessie 需要走很长一段路。由于她在路上会感到饥饿，她会在每经过第三个田地时停下来吃草（不包括她的起始田地，但可能包括最终到达的 FJ 家的田地）。有些田地的草比其他田地更茂盛，因此停下来吃草所需的时间取决于她停下的田地。

请帮助 Bessie 确定她到达 FJ 家所需的最少时间。

### 输入格式

输入的第一行包含 $N$ 和 $T$。接下来的 $N$ 行每行包含 $N$ 个正整数（每个数不超过 100,000），描述了每个田地中吃草所需的时间。第一行的第一个数是西北角的田地。

### 输出格式

输出 Bessie 到达 FJ 家所需的最少时间。

### 说明/提示

这个例子的最优解是向东移动 3 个方格（吃“10”），然后向南移动两次，向西移动一次（吃“5”），最后向南和向东移动到目的地。


---

---
title: "【模板】点分治 1"
layout: "post"
diff: 提高+/省选-
pid: P3806
tag: ['点分治', 'O2优化', '分治', '深度优先搜索 DFS']
---
# 【模板】点分治 1
## 题目背景

感谢 hzwer 的点分治互测。



## 题目描述

给定一棵有 $n$ 个点的树，询问树上距离为 $k$ 的点对是否存在。
## 输入格式

第一行两个数 $n,m$。

第 $2$ 到第 $n$ 行，每行三个整数 $u, v, w$，代表树上存在一条连接 $u$ 和 $v$ 边权为 $w$ 的路径。

接下来 $m$ 行，每行一个整数 $k$，代表一次询问。
## 输出格式

对于每次询问输出一行一个字符串代表答案，存在输出 `AYE`，否则输出 `NAY`。
## 样例

### 样例输入 #1
```
2 1
1 2 2
2
```
### 样例输出 #1
```
AYE
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n\leq 100$。
- 对于 $60\%$ 的数据，保证 $n\leq 1000$，$m\leq 50$ 。
- 对于 $100\%$ 的数据，保证 $1 \leq n\leq 10^4$，$1 \leq m\leq 100$，$1 \leq k \leq 10^7$，$1 \leq u, v \leq n$，$1 \leq w \leq 10^4$。

#### 提示

- **本题不卡常**。
- 如果您 #7 一直 RE/TLE，不妨看看 [这个帖子](https://www.luogu.com.cn/discuss/show/188596)。


---

---
title: "染色计数"
layout: "post"
diff: 提高+/省选-
pid: P3914
tag: ['动态规划 DP', '数学', '枚举', '深度优先搜索 DFS']
---
# 染色计数
## 题目描述

有一颗$N$个节点的树，节点用$1,2,\cdots,N$编号。你要给它染色，使得相邻节点的颜色不同。有$M$种颜色，用$1,2,\cdots,M$编号。每个节点可以染$M$种颜色中的若干种，求不同染色方案的数量除以($10^9 + 7$)的余数。

## 输入格式

第1 行，2 个整数$N,M$。

接下来$N$行，第$i$行表示节点$i$可以染的颜色。第1个整数$k_i$，表示可以染的颜色数量。接下来$k_i$个整数，表示可以染的颜色编号。

最后$N - 1$行，每行2个整数$A_i,B_i$，表示边$(A_i,B_i)$。

## 输出格式

1 个整数，表示所有的数。

## 样例

### 样例输入 #1
```
2 2
1 1
2 1 2
1 2
```
### 样例输出 #1
```
1
```
## 提示

• 对于30% 的数据，$1 \le N \le 10; 1 \le M \le 4$；

• 对于60% 的数据，$1 \le N \le 200; 1 \le M \le 200$；

• 对于100% 的数据，$1 \le N \le 5000; 1 \le M \le 5000$。



---

---
title: "分配问题"
layout: "post"
diff: 提高+/省选-
pid: P4014
tag: ['深度优先搜索 DFS', '二分图', '费用流', '网络流与线性规划 24 题']
---
# 分配问题
## 题目描述

有 $n$ 件工作要分配给 $n$ 个人做。第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{ij}$ 。试设计一个将 $n$ 件工作分配给 $n$ 个人做的分配方案，使产生的总效益最小或最大。

## 输入格式

文件的第一行有 $1$ 个正整数 $n$，表示有 $n$ 件工作要分配给 $n$ 个人做。

接下来的 $n$ 行中，每行有 $n$ 个整数 $c_{i,j}$，表示第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{i,j}$。

## 输出格式

两行分别输出最小总效益和最大总效益。

## 样例

### 样例输入 #1
```
5
2 2 2 1 2
2 3 1 2 4
2 0 1 1 1
2 3 4 3 3
3 2 1 2 1
```
### 样例输出 #1
```
5
14
```
## 提示

$1 \leq n \leq 50, 0 \le c _ {i, j} \le 100$。

一个人只能修一个工件。


---

---
title: "[SCOI2009] 生日快乐"
layout: "post"
diff: 提高+/省选-
pid: P4160
tag: ['动态规划 DP', '搜索', '2009', '四川', '各省省选', '深度优先搜索 DFS', '最大公约数 gcd']
---
# [SCOI2009] 生日快乐
## 题目描述

windy 的生日到了，为了庆祝生日，他的朋友们帮他买了一个边长分别为 $X$ 和 $Y$ 的矩形蛋糕。

现在包括 windy，一共有 $N$ 个人来分这块大蛋糕，要求每个人必须获得相同面积的蛋糕。

windy 主刀，每一切只能平行于一块蛋糕的一边（任意一边），并且必须把这块蛋糕切成两块。

这样，要切成 $N$ 块蛋糕，windy 必须切 $N-1$ 次。

为了使得每块蛋糕看起来漂亮，我们要求 $N$ 块蛋糕的长边与短边的比值的最大值最小。

你能帮助 windy 求出这个比值么？

## 输入格式

一行三个整数 $X,Y,N$。

## 输出格式

一行一个浮点数，保留 $6$ 位小数。

## 样例

### 样例输入 #1
```
5 5 5
```
### 样例输出 #1
```
1.800000
```
## 提示

对于 $100\%$ 的数据，满足 $1 \le X,Y \le 10^4$，$1\le N\le 10$。



---

---
title: "[USACO18JAN] Cow at Large G"
layout: "post"
diff: 提高+/省选-
pid: P4186
tag: ['2018', 'USACO', '深度优先搜索 DFS']
---
# [USACO18JAN] Cow at Large G
## 题目描述

Cornered at last, Bessie has gone to ground in a remote farm. The farm consists of $N$ barns ($2 \leq N \leq 10^5$) and $N-1$ bidirectional tunnels between barns, so that there is a unique path between every pair of barns. Every barn which has only one tunnel is an exit. When morning comes, Bessie will surface at some barn and attempt to reach an exit.

But the moment Bessie surfaces, the law will be able to pinpoint her location. Some farmers will then start at various exit barns, and attempt to catch Bessie. The farmers move at the same speed as Bessie (so in each time step, each farmer can move from one barn to an adjacent barn). The farmers know where Bessie is at all times, and Bessie knows where the farmers are at all times. The farmers catch Bessie if at any instant a farmer is in the same barn as Bessie, or crossing the same tunnel as Bessie. Conversely, Bessie escapes if she reaches an exit barn before any farms catch her.


Bessie is unsure about her chances of success, which depends on the number of farmers that the law is able to deploy. Given that Bessie surfaces at barn $K$, help Bessie determine the minimum number of farmers who would be needed to catch Bessie, assuming that the farmers distribute themselves optimally among the exit barns.

## 输入格式

The first line of the input contains $N$ and $K$. Each of the following $N-1$ lines specify two integers, each in the range $1 \ldots N$, describing a tunnel between two barns.

## 输出格式

Please output the minimum number of farmers needed to ensure catching Bessie.

## 样例

### 样例输入 #1
```
7 1
1 2
1 3
3 4
3 5
4 6
5 7
```
### 样例输出 #1
```
3
```
## 题目翻译

### 题目描述
最后，Bessie 被迫去了一个远方的农场。这个农场包含 $N$ 个谷仓（$2 \le N \le 10^5$）和 $N-1$ 条连接两个谷仓的双向隧道，所以每两个谷仓之间都有唯一的路径。每个只与一条隧道相连的谷仓都是农场的出口。当早晨来临的时候，Bessie 将在某个谷仓露面，然后试图到达一个出口。

但当 Bessie 露面的时候，她的位置就会暴露。一些农民在那时将从不同的出口谷仓出发尝试抓住 Bessie。农民和 Bessie 的移动速度相同（在每个单位时间内，每个农民都可以从一个谷仓移动到相邻的一个谷仓，同时 Bessie 也可以这么做）。农民们和 Bessie 总是知道对方在哪里。如果在任意时刻，某个农民和 Bessie 处于同一个谷仓或在穿过同一个隧道，农民就可以抓住 Bessie。反过来，如果 Bessie 在农民们抓住她之前到达一个出口谷仓，Bessie 就可以逃走。

Bessie 不确定她成功的机会，这取决于被雇佣的农民的数量。给定 Bessie 露面的谷仓K，帮助 Bessie 确定为了抓住她所需要的农民的最小数量。假定农民们会自己选择最佳的方案来安排他们出发的出口谷仓。

### 输入格式

输入的第一行包含 $N$ 和 $K$。接下来的 $N - 1$ 行，每行有两个整数（在 $1\sim N$ 范围内）描述连接两个谷仓的一条隧道。

### 输出格式

输出为了确保抓住 Bessie 所需的农民的最小数量。

由 @Marser 提供翻译


---

---
title: "[NOI2005] 聪聪与可可"
layout: "post"
diff: 提高+/省选-
pid: P4206
tag: ['搜索', '2005', 'NOI', '广度优先搜索 BFS', '深度优先搜索 DFS', '记忆化搜索', '期望']
---
# [NOI2005] 聪聪与可可
## 题目描述

在一个魔法森林里，住着一只聪明的小猫聪聪和一只可爱的小老鼠可可。虽然灰姑娘非常喜欢她们俩，但是，聪聪终究是一只猫，而可可终究是一只老鼠，同样不变的是，聪聪成天想着要吃掉可可。

一天，聪聪意外得到了一台非常有用的机器，据说是叫 GPS，对可可能准确的定位。有了这台机器，聪聪要吃可可就易如反掌了。于是，聪聪准备马上出发，去找可可。而可怜的可可还不知道大难即将临头，仍在森林里无忧无虑的玩耍。小兔子乖乖听到这件事，马上向灰姑娘报告。灰姑娘决定尽快阻止聪聪，拯救可可，可她不知道还有没有足够的时间。

整个森林可以认为是一个无向图，图中有 $N$ 个美丽的景点，景点从 $1$ 至 $N$ 编号。小动物们都只在景点休息、玩耍。在景点之间有一些路连接。

当聪聪得到 GPS 时，可可正在景点 $M$（$M \le N$）处。以后的每个时间单位，可可都会选择去相邻的景点（可能有多个）中的一个或停留在原景点不动。而去这些地方所发生的概率是相等的。假设有 $P$ 个景点与景点 $M$ 相邻，它们分别是景点 $R$、景点 $S$、……、景点 $Q$，在时刻 $T$ 可可处在景点 $M$，则在 $(T+1)$ 时刻，可可有 $1/(1 +P)$ 的可能在景点 $R$，有 $1/(1 +P)$ 的可能在景点 $S$，……，有 $1/(1 +P)$ 的可能在景点 $Q$，还有$1/(1 +P)$的可能停在景点 $M$。

我们知道，聪聪是很聪明的，所以，当她在景点 $C$ 时，她会选一个更靠近可可的景点，如果这样的景点有多个，她会选一个标号最小的景点。由于聪聪太想吃掉可可了，如果走完第一步以后仍然没吃到可可，她还可以在本段时间内再向可可走近一步。

在每个时间单位，假设聪聪先走，可可后走。在某一时刻，若聪聪和可可位于同一个景点，则可怜的可可就被吃掉了。

灰姑娘想知道，平均情况下，聪聪几步就可能吃到可可。而你需要帮助灰姑娘尽快的找到答案。
## 输入格式

数据的第 1 行为两个整数 $N$ 和 $E$，以空格分隔，分别表示森林中的景点数和连接相邻景点的路的条数。

第 2 行包含两个整数 $C$ 和 $M$，以空格分隔，分别表示初始时聪聪和可可所在的景点的编号。

接下来 E 行，每行两个整数，第 $i+2$ 行的两个整数 $A_i$ 和 $B_i$ 表示景点 $A_i$ 和景点 $B_i$ 之间有一条路。所有的路都是无向的，即：如果能从 A 走到 B，就可以从 B 走到 A。

输入保证任何两个景点之间不会有多于一条路直接相连，且聪聪和可可之间必有路直接或间接的相连。
## 输出格式

输出 1 个实数，四舍五入保留三位小数，表示平均多少个时间单位后聪聪会把可可吃掉。
## 样例

### 样例输入 #1
```
4 3 
1 4 
1 2 
2 3 
3 4
```
### 样例输出 #1
```
1.500 

```
### 样例输入 #2
```
9 9 
9 3 
1 2 
2 3 
3 4 
4 5 
3 6 
4 6 
4 7 
7 8 
8 9
```
### 样例输出 #2
```
2.167
```
## 提示

【样例说明 1】 

开始时，聪聪和可可分别在景点 1 和景点 4。 

第一个时刻，聪聪先走，她向更靠近可可(景点 4)的景点走动，走到景点 2， 然后走到景点 3；假定忽略走路所花时间。 

可可后走，有两种可能： 第一种是走到景点 3，这样聪聪和可可到达同一个景点，可可被吃掉，步数为 $1$，概率为$0.5$。
 
第二种是停在景点 4，不被吃掉。概率为 $0.5$。

到第二个时刻，聪聪向更靠近可可(景点 4)的景点走动，只需要走一步即和 可可在同一景点。因此这种情况下聪聪会在两步吃掉可可。 所以平均的步数是 $1\times 1/2 + 2\times 1/2 =1.5$ 步。

【样例说明 2】

森林如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/8uiq0ltc.png)

对于 50%的数据，$1≤N≤50$。  
对于所有的数据，$1≤N,E≤1000$。 


---

---
title: "[JLOI2014] 聪明的燕姿"
layout: "post"
diff: 提高+/省选-
pid: P4397
tag: ['2014', '各省省选', '吉林', '枚举', '深度优先搜索 DFS', '素数判断,质数,筛法']
---
# [JLOI2014] 聪明的燕姿
## 题目背景

> 阴天傍晚车窗外
>
> 未来有一个人在等待
>
> 向左向右向前看
>
> 爱要拐几个弯才来
>
> 我遇见谁会有怎样的对白
>
> 我等的人他在多远的未来
>
> 我听见风来自地铁和人海
>
> 我排着队拿着爱的号码牌
## 题目描述

城市中人们总是拿着号码牌，不停寻找，不断匹配，可是谁也不知道自己等的那个人是谁。

可是燕姿不一样，燕姿知道自己等的人是谁，因为燕姿数学学得好！燕姿发现了一个神奇的算法：假设自己的号码牌上写着数字 $S$，那么自己等的人手上的号码牌数字的所有正约数之和必定等于 $S$。

所以燕姿总是拿着号码牌在地铁和人海找数字（喂！这样真的靠谱吗）可是她忙着唱《绿光》，想拜托你写一个程序能够快速地找到所有自己等的人。
## 输入格式

输入包含 $k$ 组数据。

对于每组数据，输入包含一个号码牌 $S$。
## 输出格式

对于每组数据，输出有两行，第一行包含一个整数 $m$，表示有 $m$ 个等的人。

第二行包含相应的 $m$ 个数，表示所有等的人的号码牌。

特别地，当某组数据出现 $m=0$，即不存在满足题意的号码牌时，该组数据不应输出第二行（只应输出第一行的 $0$）。

注意：你输出的号码牌必须按照升序排列。
## 样例

### 样例输入 #1
```
42
```
### 样例输出 #1
```
3
20 26 41
```
## 提示

对于 $100\%$ 的数据，$k\leqslant100$，$S\leqslant2\times10^9$。


---

---
title: "[CQOI2013] 新数独"
layout: "post"
diff: 提高+/省选-
pid: P4573
tag: ['搜索', '2013', '重庆', '各省省选', '枚举', '深度优先搜索 DFS']
---
# [CQOI2013] 新数独
## 题目描述

下面是一个没有数字，只有大小关系（没错，那些尖角都是“大于符号”）！的数独：

![](https://cdn.luogu.com.cn/upload/image_hosting/wm5lvhj6.png)

除了大小关系外（注意相邻格子不能相同），还需要满足通常的数独规则：

 * 每个格子都是 $1\sim 9$ 的数字；
 * 每行都是 $1 \sim 9$ 的排列；
 * 每列都是 $1 \sim 9$ 的排列；
 * 每个 $3\times 3$ 的子矩阵（上图中用粗线隔开，一共有 $3\times 3$ 个这样的子矩阵）都是 $1\sim 9$ 的排列。
 
 如下图所示，是上述提到的数独的唯一一种填法：
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/73a6a29i.png)
 
 为了美观，每个 $3\times 3$ 子矩阵的**所有 $12$ 对**相邻格子的大小关系都将给出。
## 输入格式

一共 $15$ 行，包含一个新数独的实例。第 $1,3,5,6,8,10,11,13,15$ 行包含左右方向的符号（< 和 >），其余行包含上下方向的符号（^ 和 v）
## 输出格式

包含 $9$ 行，每行 $9$ 个 $1\sim 9$ 的数字，以空格隔开。输入保证唯一解。
## 样例

### 样例输入 #1
```
> < < < > <
v ^ v v ^ v ^ ^ v
< < < > < <
v ^ v ^ v v ^ ^ v
< < < < > >
< > > > < >
v v ^ ^ v ^ ^ v v
< > > < > >
^ v v v ^ v v ^ v
> < < > > >
< > > > > <
v v v v ^ ^ ^ ^ ^
> < < < < <
^ ^ ^ ^ ^ v v v ^
> > < > < <
```
### 样例输出 #1
```
5 3 9 4 6 8 2 1 7
2 4 8 1 9 7 3 5 6
1 6 7 2 3 5 9 8 4
6 8 1 7 4 2 5 9 3
3 7 5 9 1 6 8 4 2
9 2 4 5 8 3 7 6 1
7 9 6 8 2 1 4 3 5
4 1 2 3 5 9 6 7 8
8 5 3 6 7 4 1 2 9
```
### 样例输入 #2
```
< > > < > <
v v ^ ^ v v ^ ^ ^
< < > < > <
^ ^ ^ v ^ ^ ^ v v
< < < < > > 
> < > > > >
v ^ ^ ^ ^ v v v ^
> > > > < >
v v ^ v ^ v ^ v ^
> < < > > > 
< < < < > <
v ^ v v v v ^ ^ v
< > > < < >
^ v v v ^ v ^ v v
< > < > < >
```
### 样例输出 #2
```
4 9 1 7 3 6 5 2 8
2 3 7 8 1 5 6 4 9
5 6 8 2 4 9 7 3 1
9 1 3 6 5 4 8 7 2
8 5 4 9 7 2 1 6 3
7 2 6 3 8 1 9 5 4
3 4 9 5 6 8 2 1 7
1 8 5 4 2 7 3 9 6
6 7 2 1 9 3 4 8 5
```


---

---
title: "[IOI 2008] Type Printer"
layout: "post"
diff: 提高+/省选-
pid: P4683
tag: ['字符串', '2008', 'IOI', 'Special Judge', '深度优先搜索 DFS', '字典树 Trie']
---
# [IOI 2008] Type Printer
## 题目描述

你需要利用一台可移动的打印机打印出 $n$ 个单词。这种可移动式打印机是一种老式打印机，它需要你将一些小的金属块（每个包含一个字母）放到打印机上以组成单词。然后将这些小金属块压在一张纸上以打印出这个词。这种打印机允许你进行下列操作： 

- 在打印机当前词的末端（尾部）添加一个字母； 
- 在打印机当前词的尾部删去一个字母（将打印机当前词的最后一个字母删去）。仅当打印机当前至少有一个字母时才允许进行该操作；
- 将打印机上的当前词打印出来。 

初始时打印机为空，或者说它不含任何带字母的金属块。打印结束时，允许有部分字母留在打印机内。同时也允许你按照任意的次序打印单词。

由于每一个操作都需要一定时间，所以需要你尽可能减少所需操作的总数目（将操作的总数最小化）。

你需要编写一个程序，给定所要打印的 $n$ 个单词，找出以任意次序打印所有单词所需操作的最小数目，并输出一种这样的操作序列。
## 输入格式

- 第 $1$ 行包含一个整数 $n$, 表示你需要打印的单词数。 	
- 随后的 $n$ 行中，每一行都包含一个单词。每个词仅由小写字母组成，而且单词的长度为 $1$ 到 $20$ 个字母（包含 $1$ 和 $20$ 在内）。所有单词都不相同。
## 输出格式

第一行包含一个整数 $m$，表示打印这 $n$ 个单词所需操作的最小数目。

接下来的 $m$ 行，每行一个字符，表示你的操作序列，序列的描述方法如下：
- 添加一个字母，用这个小写字母的自身来表示。
- 删去一个字母，用 `-` 表示。
- 打印单词，用 `P` 表示。
## 样例

### 样例输入 #1
```
3
print
the
poem
```
### 样例输出 #1
```
20
t
h
e
P
-
-
-
p
o
e
m
P
-
-
-
r
i
n
t
P
```
## 提示

对于 $40\%$ 的数据，$n\leq18$；

对于 $100\%$ 的数据，$1\leq n\leq25000$。


---

---
title: "[NOIP 2018 普及组] 摆渡车"
layout: "post"
diff: 提高+/省选-
pid: P5017
tag: ['动态规划 DP', '2018', 'NOIP 普及组', '枚举', '深度优先搜索 DFS', '斜率优化']
---
# [NOIP 2018 普及组] 摆渡车
## 题目背景

NOIP2018 普及组 T3
## 题目描述

有 $n$ 名同学要乘坐摆渡车从人大附中前往人民大学，第 $i$ 位同学在第 $t_i$ 分钟去 等车。只有一辆摆渡车在工作，但摆渡车容量可以视为无限大。摆渡车从人大附中出发、 把车上的同学送到人民大学、再回到人大附中（去接其他同学），这样往返一趟总共花费 $m$ 分钟（同学上下车时间忽略不计）。摆渡车要将所有同学都送到人民大学。  

凯凯很好奇，如果他能任意安排摆渡车出发的时间，那么这些同学的等车时间之和最小为多少呢？    

注意：摆渡车回到人大附中后可以即刻出发。
## 输入格式

第一行包含两个正整数 $n, m$，以一个空格分开，分别代表等车人数和摆渡车往返一趟的时间。    
第二行包含 $n$ 个正整数，相邻两数之间以一个空格分隔，第 $i$ 个非负整数 $t_i$ 代表第 $i$ 个同学到达车站的时刻。 
## 输出格式

输出一行，一个整数，表示所有同学等车时间之和的最小值（单位：分钟）。 
## 样例

### 样例输入 #1
```
5 1 
3 4 4 3 5 
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
5 5 
11 13 1 5 5 
```
### 样例输出 #2
```
4
```
## 提示

**样例 1 说明**    

同学 $1$ 和同学 $4$ 在第 $3$ 分钟开始等车，等待 $0$ 分钟，在第 $3$ 分钟乘坐摆渡车出发。摆渡车在第 $4$ 分钟回到人大附中。   
同学 $2$ 和同学 $3$ 在第 $4$ 分钟开始等车，等待 $0$ 分钟，在第 $4$ 分钟乘坐摆渡车 出发。摆渡车在第 $5$ 分钟回到人大附中。   
同学 $5$ 在第 $5$ 分钟开始等车，等待 $0$ 分钟，在第 $5$ 分钟乘坐摆渡车出发。自此 所有同学都被送到人民大学。总等待时间为 $0$。

**样例 2 说明**  

同学 $3$ 在第 $1$ 分钟开始等车，等待 $0$ 分钟，在第 $1$ 分钟乘坐摆渡车出发。摆渡 车在第 $6$ 分钟回到人大附中。   
同学 $4$ 和同学 $5$ 在第 $5$ 分钟开始等车，等待 $1$ 分钟，在第 $6$ 分钟乘坐摆渡车 出发。摆渡车在第 $11$ 分钟回到人大附中。   
同学 $1$ 在第 $11$ 分钟开始等车，等待 $2$ 分钟；同学 $2$ 在第 $13$ 分钟开始等车， 等待 $0$ 分钟。他/她们在第 $13$ 分钟乘坐摆渡车出发。自此所有同学都被送到人民大学。 总等待时间为 $4$。  
可以证明，没有总等待时间小于 $4$ 的方案。 

**数据规模与约定**

对于 $10\%$ 的数据，$n ≤ 10$，$m = 1$，$0 ≤ t_i ≤ 100$。   
对于 $30\%$ 的数据，$n ≤ 20$，$m ≤ 2$，$0 ≤ t_i ≤ 100$。  
对于 $50\%$ 的数据，$n ≤ 500$，$m ≤ 100$，$0 ≤ t_i ≤ 10^4$。  
另有 $20\%$ 的数据，$n ≤ 500$，$m ≤ 10$，$0 ≤ t_i ≤ 4 \times  10^6$。  
对于 $100\%$ 的数据，$n ≤ 500$，$m ≤ 100$，$0 ≤ t_i ≤ 4 \times 10^6$。


---

---
title: "[NOIP 2018 提高组] 旅行"
layout: "post"
diff: 提高+/省选-
pid: P5022
tag: ['搜索', '贪心', '2018', 'NOIP 提高组', '深度优先搜索 DFS', '基环树']
---
# [NOIP 2018 提高组] 旅行
## 题目背景

NOIP2018 提高组 D2T1
## 题目描述

小 Y 是一个爱好旅行的 OIer。她来到 X 国，打算将各个城市都玩一遍。 
  
小 Y 了解到，X 国的 $n$ 个城市之间有 $m$ 条双向道路。每条双向道路连接两个城市。 不存在两条连接同一对城市的道路，也不存在一条连接一个城市和它本身的道路。并且， 从任意一个城市出发，通过这些道路都可以到达任意一个其他城市。小 Y 只能通过这些 道路从一个城市前往另一个城市。   

小 Y 的旅行方案是这样的：任意选定一个城市作为起点，然后从起点开始，每次可 以选择一条与当前城市相连的道路，走向一个没有去过的城市，或者沿着第一次访问该 城市时经过的道路后退到上一个城市。当小 Y 回到起点时，她可以选择结束这次旅行或 继续旅行。需要注意的是，小 Y 要求在旅行方案中，每个城市都被访问到。   

为了让自己的旅行更有意义，小 Y 决定在每到达一个新的城市（包括起点）时，将 它的编号记录下来。她知道这样会形成一个长度为 $n$ 的序列。她希望这个序列的字典序 最小，你能帮帮她吗？  对于两个长度均为 $n$ 的序列 $A$ 和 $B$，当且仅当存在一个正整数 $x$，满足以下条件时， 我们说序列 $A$ 的字典序小于 $B$。 
  
- 对于任意正整数 $1 ≤ i < x$，序列 $A$ 的第 $i$ 个元素 $A_i$ 和序列 $B$ 的第 $i$ 个元素 $B_i$ 相同。   
- 序列 $A$ 的第 $x$ 个元素的值小于序列 $B$ 的第 $x$ 个元素的值。 
## 输入格式

输入文件共 $m + 1$ 行。第一行包含两个整数 $n,m(m ≤ n)$，中间用一个空格分隔。
 
接下来 m 行，每行包含两个整数 $u,v (1 ≤ u,v ≤ n)$ ，表示编号为 $u$ 和 $v$ 的城市之 间有一条道路，两个整数之间用一个空格分隔。 
## 输出格式

输出文件包含一行，$n$ 个整数，表示字典序最小的序列。相邻两个整数之间用一个 空格分隔。 
## 样例

### 样例输入 #1
```
6 5 
1 3 
2 3 
2 5 
3 4 
4 6
```
### 样例输出 #1
```
1 3 2 5 4 6
```
### 样例输入 #2
```
6 6 
1 3 
2 3 
2 5 
3 4 
4 5 
4 6
```
### 样例输出 #2
```
1 3 2 4 5 6
```
## 提示

【数据规模与约定】   

对于 $100\%$ 的数据和所有样例， $1 \le n \le 5000 $ 且 $m = n − 1$ 或 $m = n$ 。

对于不同的测试点， 我们约定数据的规模如下：

![](https://cdn.luogu.com.cn/upload/pic/43271.png)


---

---
title: "[yLOI2019] 梅深不见冬"
layout: "post"
diff: 提高+/省选-
pid: P5521
tag: ['贪心', '2019', 'O2优化', '排序', '深度优先搜索 DFS']
---
# [yLOI2019] 梅深不见冬
## 题目背景

> 风，吹起梅岭的深冬；霜，如惊涛一样汹涌；  
> 雪，飘落后把所有烧成空，像这场，捕捉不到的梦。   
> 醒来时已是多年之久，宫门铜环才长了铁锈，也开始生出离愁。

——银临《梅深不见冬》
## 题目描述

扶苏从深冬的梅岭走出，来到了一棵有 $n$ 个节点的有根树上。

如果你不知道什么是树，可以认为树是一个边数恰好比节点个数少一的简单无向连通图。

如果我们规定 $x$ 是树 $T$ 的根，那么定义任意一个节点 $y$ 到根的路径就是从 $y$ 出发不重复经过节点到达 $x$ 所经过的所经过的点构成的点集。可以证明这样的点集有且仅有一个。

定义一个节点 $u$ 是节点 $v$ 的孩子，当且仅当 $u$ 与 $v$ 相连且 $u$ 不在 $v$ 到根的路径中。如果 $u$ 是 $v$ 的孩子，那么定义 $v$ 是 $u$ 的家长节点。

如果我是 @[\_rqy](https://www.luogu.org/space/show?uid=7868) 那种~~毒瘤~~神仙的话，可能会问你每个节点的孩子数不超过 $k$ 的 $n$ 个节点的带标号无根树一共有多少个，可惜这个问题我也不会，所以我不会问你这么毒瘤的问题。

扶苏从这棵 $n$ 个节点的树的 $1$ 号节点出发，沿着树上的边行走。当然我们规定 $1$ 号节点是这棵树的根。他所行走的规定是：当扶苏在节点 $u$ 时，扶苏要么在 $u$ 的孩子中选择一个**没有到达过**的节点 $v$ 并行走到 $v$，要么选择回到 $u$ 的家长节点。

现在给每个节点一个权值 $w$，其中 $i$ 号节点的权值为 $w_i$。他想给这棵树的某个节点放上从梅岭带出的梅花。我们规定扶苏能在节点 $u$ 放上梅花当且仅当满足如下条件：

> 扶苏当前在节点 $u$。
>
> 对于 $u$ 的所有孩子 $v$，节点 $v$ 被放上了 $w_v$ 朵梅花。

同时，扶苏可以在**任意时刻**收回**任意节点**上的梅花，在收回梅花时不需要走到对应节点。

现在扶苏想问问你，对于每个节点，如果他想在 $i$ 号节点上放 $w_i$ 朵梅花，那么他最少要从梅岭带出多少朵梅花。
## 输入格式

每个输入文件中都有且仅有一组测试数据。

数据的第一行是一个整数 $n$ 代表树的节点个数。

第二行有 $n-1$ 个用空格隔开的整数，第 $i$ 个整数 $p_i$ 代表第 $i+1$ 号节点的家长节点编号。

第三行有 $n$ 个用空格隔开的整数，第 $i$ 个整数代表 $w_i$。
## 输出格式

输出一行 $n$ 个用空格隔开的整数，第 $i$ 个整数代表想在 $i$ 号节点上放 $w_i$ 朵梅花需要准备的梅花个数。
## 样例

### 样例输入 #1
```
3 
1 2 
1 1 1
```
### 样例输出 #1
```
2 2 1
```
### 样例输入 #2
```
3
1 1
1 1 1
```
### 样例输出 #2
```
3 1 1
```
### 样例输入 #3
```
6
1 1 2 3 4
3 14 1 5 12 15
```
### 样例输出 #3
```
21 20 13 20 12 15
```
## 提示

#### 输入输出样例 1 解释

![qwq](https://cdn.luogu.com.cn/upload/pic/72286.png)

样例 1 的输入如上图，每个节点都需要放 $1$ 一朵梅花。

如果在 1 号节点放梅花，则从一号点运动到 2 号点，然后运动到 3 号点，在 3 号点上放一朵梅花，返回 2 号点，在 2 号点上放一朵梅花，同时收回三号点的梅花，然后返回 1 号点，将从 3 号点收回的梅花放到 1 号点即可。一共需要两朵梅花。

在 2、3 号节点放梅花的方案类似。

#### 输入输出样例 3 解释

![qwq](https://cdn.luogu.com.cn/upload/pic/72287.png)

样例 3 的输入如左图。

先从 1 号节点运动至 3 号节点，再运动至 5 号节点，在 5 号节点上放置 $12$ 朵梅花，然后返回 3 号节点，在 3 号节点上放置 $1$ 朵梅花，收回五号节点的 $12$ 朵梅花，返回 1 号节点。

然后运动到 2 号节点，通过 4 号节点运动到 6 号节点，放下 $15$ 朵梅花，返回 4 号节点放下 $5$ 朵梅花，此时树上有的梅花数为 $5 + 15 + 1 = 21$，分别在 4 号、6 号和 3 号节点上。然后收回 6 号节点的梅花，返回 2 号节点，放下 $14$ 朵梅花，收回 4 号节点的，返回 1 号节点，在 1 号节点上放置 $3$ 朵梅花，即可达到在 1 号节点上放梅花的目的。

可以验证最大花费为 $21$。其他节点的答案同理。

请注意，其他节点的答案不一定是按照该节点的运动路径行走得到的。

---

#### 数据规模与约定

| 测试点编号 |  $n = $  | 测试点编号 |  $n = $  |
| :--------: | :------: | :--------: | :------: |
|     1      |   $1$    |     11     | $100003$ |
|     2      |   $8$    |     12     | $100003$ |
|     3      |   $8$    |     13     | $100003$ |
|     4      |   $8$    |     14     | $100003$ |
|     5      |   $8$    |     15     | $100004$ |
|     6      | $100000$ |     16     | $100004$ |
|     7      | $100000$ |     17     | $100004$ |
|     8      | $100002$ |     18     | $100004$ |
|     9      | $100002$ |     19     | $100004$ |
|     10     | $100002$ |     20     | $100004$ |

- 对于测试点 5、6，满足特殊性质：每个节点的孩子结点个数不超过 $2$。
- 对于测试点 8 到测试点 10，满足特殊性质：每个节点的孩子节点个数不超过 $5$。
- 对于测试点 11 到测试点 14，满足特殊性质：任意一个节点到根的路径上的点数不超过 $3$，也即树高不超过 $3$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5 + 4,~1 \leq p_i \leq i,~1 \leq w_i \leq 1000$。

---

#### 提示

- $n$ 的末位数字可以帮助你快速的判断测试点所具有的的特殊性质。


---

---
title: "[BalticOI 2017] Cat in a tree"
layout: "post"
diff: 提高+/省选-
pid: P6574
tag: ['贪心', '2017', '深度优先搜索 DFS', 'BalticOI（波罗的海）']
---
# [BalticOI 2017] Cat in a tree
## 题目描述

小猫在一棵有 $n$ 个节点的树上，它通过标记节点来划分领地。  
它标记的节点满足彼此距离不小于 $d$。  
两节点之间的距离指的是两点间路径上节点的个数（包括端点）。   
求小猫最多能标记多少个节点。
## 输入格式

第一行两个整数代表节点数 $n$ 和标记的节点不超过的距离 $d$。  
第 $0$ 个节点就是根节点，节点的编号为从 $0$ 到 $n - 1$。  
接下来 $n-1$ 行，第 $i$ 行代表第 $i$ 个节点与哪个节点相连，一个数 $x_i$ 代表编号为 $i$ 的节点与编号为 $x_i$ 的节点相连。
## 输出格式

一行一个整数代表猫最多能标记多少个节点。
## 样例

### 样例输入 #1
```
4 3
0
0
1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 1000
0
0
```
### 样例输出 #2
```
1
```
## 提示

#### 数据范围与约定

**本题采用捆绑测试。**

- Subtask 1（11 pts）：$n \le 18$。
- Subtask 2（40 pts）：$n \le 1500$。
- Subtask 3（49 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,d \le 2 \times 10^5$，$0 \le x_i < i$。

#### 说明

**翻译自 [BOI 2017 D2](https://boi.cses.fi/files/boi2017_day2.pdf) T1 Cat in a tree。**  
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。


---

---
title: "[YsOI2020] 换寝室"
layout: "post"
diff: 提高+/省选-
pid: P6594
tag: ['二分', 'O2优化', '深度优先搜索 DFS', '树形 DP', '最近公共祖先 LCA', '差分']
---
# [YsOI2020] 换寝室
## 题目背景

马上要开学了，Ysuperman 正在为给孩子们分配寝室忙得不可开交......
## 题目描述

幼儿园里面有 $n$ 个房间，这些房间由 $n-1$ 条双向道路连接着，第 $i$ 条道路连接着房间 $u_i$ 和 $v_i$ ，每条道路 Ysuperman 都可以选择开启或者是关闭，每个房间**在所有道路开启的前提下**都可以到达其他任意一个房间。

每个房间有一个差异值，其中，第 $i$ 个房间的差异值为 $h_i$ 。

在选择完关闭哪些道路后，整个寝室会被分成许多连通块，一个联通块内的小朋友的不满意值定义为连通块内差异值的**最大值减去最小值**，小朋友们的总不满意值定义为**所有联通块不满意值的最大值**。

寝室里有 $m$ 个寝室老师，每个老师晚上都要查寝，第 $i$ 个老师会从第 $x_i$ 个房间走到第 $y_i$ 个房间，如果老师在查寝时经过了某条被关闭的道路，TA就会很生气，一个老师的不满意值定义为**从 $x_i$ 走到 $y_i$ 经过的被关闭的道路数量**，老师的总不满意值定义为**所有老师的不满意值之和**。

Ysuperman 能承受的老师的总不满意值最大为 $k$ ，现在TA想知道小朋友们的总不满意值最小可以达到多少。
## 输入格式

输入共 $n+m+1$ 行。

第一行三个整数 $n,m,k$，表示房间个数，寝室老师个数和Ysuperman 能承受的老师的总不满意值。

接下来一行，共 $n$ 个整数，第 $i$ 个整数是 $h_i$，表示第 $i$ 个房间的差异值。

接下来 $n-1$ 行，每行两个整数，第 $i+2$ 行是 $u_i$ 和 $v_i$，表示寝室 $u_i,v_i$ 之间有直接道路。

接下来 $m$ 行，每行两个整数，第 $i+n+1$ 行是 $x_i$ 和 $y_i$，表示第 $i$ 个老师的查寝路线。
## 输出格式

一行一个整数，即答案。
## 样例

### 样例输入 #1
```
5 2 0
1 3 1 4 0
1 2
1 3
1 4
1 5
2 3
1 4
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5 2 1
1 3 1 4 0
1 2
1 3
1 4
1 5
2 3
1 4
```
### 样例输出 #2
```
2
```
## 提示

### 样例说明

#### 样例说明 $1$

![](https://cdn.luogu.com.cn/upload/image_hosting/mf6j6hz3.png)

Ysuperman选择关闭连接着 $1$ 和 $5$ 的道路，老师的总不满意值为 $0$，寝室被分为 $2$ 个连通块，小朋友们的总不满意值为 $3$。

#### 样例说明 $2$

图同样例一。

Ysuperman选择关闭连接着 $1$ 和 $5$ 的道路以及连接着 $1$ 和 $4$ 的道路，老师的总不满意值为 $1$，寝室被分为 $3$ 个连通块，小朋友们的总不满意值为 $2$。

------
### 数据范围

**本题采用捆绑测试。**

| Subtask | $n$ | $m$ | $k$ | 特殊性质 | 分数 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| 1 | $\le 20$ | $\le 10$ | $\le 80$ | 无 | 8 |
| 2 | $\le 150$ | $\le 10^3$ | $\le 8 \times 10^4$ | 无 | 13 |
| 3 | $\le 800$ | $\le 10^5$ | $\le 8 \times 10^7$ | 树为一条链 | 13 |
| 4 | $\le 800$ | $\le 10^5$ | $\le 8 \times 10^7$ | 树为一朵盛开的菊花 | 13 |
| 5 | $\le 800$ | $\le 10^5$ | $= 0$ | 无 | 13 |
| 6 | $\le 800$ | $\le 10^5$ | $\le 8 \times 10^7$ | 无 | 40 |

【一条链】定义为：所有点的度数 $\le2$。

【一朵盛开的菊花】定义为：存在一个点的度数为 $n-1$。

对于 $100\%$ 的数据，满足 $1\le h_i\le 10^9，0\le k \le 8\cdot 10^7,u_i\ne v_i$ 。


---

---
title: "[BalticOI 2014] Senior Postmen (Day2)"
layout: "post"
diff: 提高+/省选-
pid: P6743
tag: ['搜索', '2014', 'Special Judge', '深度优先搜索 DFS', 'BalticOI（波罗的海）']
---
# [BalticOI 2014] Senior Postmen (Day2)
## 题目背景

# 滥用本题评测将被封号
## 题目描述

给定一张 $N$ 点 $M$ 边的无向图，求从中找出若干个环，使得：

- 这些环没有重复的边。
- 这些环覆盖了所有的点和边。
## 输入格式

第一行两个整数 $N,M$ 代表点数和边数。       
接下来 $M$ 行每行两个整数 $u,v$ 代表一条边。
## 输出格式

若干行每行若干个整数代表一个环。
## 样例

### 样例输入 #1
```
10 15
1 3
5 1
2 3
9 2
3 4
6 3
4 5
7 4
4 8
5 7
8 5
6 7
7 8
8 10
10 9
```
### 样例输出 #1
```
2 3 4 5 8 10 9
7 8 4
1 5 7 6 3
```
## 提示

#### 样例说明

对于样例 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/z5q8d4du.png)

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（38 pts）：$N \le 2000$，$M \le 10^5$。
- Subtask 2（17 pts）：$N,M \le 10^5$。
- Subtask 3（45 pts）：无特殊限制。

对于 $100\%$ 的数据，$3 \le N,M \le 5 \times 10^5$。

**本题使用 Special Judge。**

感谢 spj 提供者 @[tiger2005](https://www.luogu.com.cn/user/60864)。

#### 说明

翻译自 [BalticOI 2014 Day2 C Senior Postmen](https://boi.cses.fi/files/boi2014_day2.pdf)。


---

---
title: "[IOI 2020] 连接擎天树"
layout: "post"
diff: 提高+/省选-
pid: P6830
tag: ['2020', 'IOI', '交互题', 'Special Judge', '深度优先搜索 DFS']
---
# [IOI 2020] 连接擎天树
## 题目背景

**这是一道交互题。**

本题仅支持 C++ 系列语言，提交时**不需要**包含 `supertrees.h` 头文件，但**需要**在程序开头包含 `vector` 头文件以及声明函数 `void build(std::vector<std::vector<int> > b);`
## 题目描述

滨海湾花园是新加坡的一个大型自然公园。公园内有 $n$ 个塔，称之为“擎天树”。这些塔的编号为 $0$ 到 $n-1$。我们希望建立一个桥的集合（桥的数目大于等于 $0$）。每⼀座桥连接两个不同的塔，而且可以双向通行。没有两座桥连接相同的一对塔。

一条从塔 $x$ 到塔 $y$ 的路径是一个满足以下条件的塔序列（塔的数目大于等于 $1$）：

- 序列的第一个元素是 $x$，
- 序列的最后一个元素是 $y$，
- 序列中所有元素互不相同，

序列中每两个相邻元素（塔）都是被某一座桥连接起来的。

注意根据定义，一个塔到它自己有且仅有一条路径，并且从塔 $i$ 到塔 $j$ 的不同路径的数目和从塔 $j$ 到塔 $i$ 的不同路径的数目是一样的。

负责该项设计的首席设计师希望待建造的桥梁要符合：任意给定 $0 \le i,j \le n-1$，恰好有 $p[i][j]$ 条从塔 $i$ 到塔 $j$ 的不同路径，其中 $0 \le p[i][j] \le 3$。

请构造一个桥的集合来满足设计师的要求，或判定这样的桥梁集合不可能存在。

#### 实现细节

你需要实现下面的这个函数：

```cpp
int construct(std::vector<std::vector<int> > p)
```

- $p$：⼀个表示设计师要求的 $n \times n$ 数组。
- 如果这个建设方案是存在的，该函数应该恰好调用一次 `build`（见下文）来给出建设方案，然后应返回 $1$。
- 否则，该函数应该返回 $0$，并且不要调用 `build`。
- 该函数将被调用恰好一次。

函数 `build` 定义如下：

```cpp
void build(std::vector<std::vector<int> > b)
```
  
- $b$：一个 $n \times n$ 的数组，$b[i][j]=1$ 表示有一座桥连接塔 $i$ 和塔 $j$，否则 $b[i][j]=0$。
- 注意该数组必须满足：对所有 $0 \le i,j \le n-1$，$b[i][j]=b[j][i]$；并且对所有 $0 \le i \le n-1$，$b[i][i]=0$。
## 提示

#### 样例说明

#### 例 1

考虑以下调用：

```cpp
construct([[1, 1, 2, 2], [1, 1, 2, 2], [2, 2, 1, 2], [2, 2, 2, 1]])
```
  
这表明从塔 $0$ 到塔 $1$ 恰好有一条路径。对于所有其他的塔对 $(x,y)(0 \le x<y \le 3)$, 恰好有两条不同的路径连接塔 $x$ 和塔 $y$。这可以通过建设 $4$ 座桥来实现：连接塔对 $(0, 1), (1, 2), (1, 3)$ 和 $(2,3)$。

为了给出这个解决方案，函数 `construct` 应该做以下调用：

```cpp
build([[0, 1, 0, 0], [1, 0, 1, 1], [0, 1, 0, 1], [0, 1, 1, 0]])
  ```

![](https://cdn.luogu.com.cn/upload/image_hosting/lf8q5wrk.png)

函数应该返回 $1$。

对于这个例子，存在多种不同的建设方案来满足要求，所有这些方案都被认为是正确的。

#### 例 2

考虑以下调用：

```cpp
construct([[1, 0], [0, 1]])
```
  
  这表明无法在两个塔之间进行旅行。这只能通过不建设桥梁来满足。

因此，函数 `construct` 应该做以下调用：
```cpp
build([[0, 0], [0, 0]])
```
  然后，函数 `construct` 应该返回 $1$。
  
  #### 例 3
  
考虑以下调用：

```cpp
construct([[1, 3], [3, 1]])
```

这表明从塔 $0$ 到塔 $1$ 恰好有 $3$ 条路径。这些要求无法满足。因此，函数 `construct` 应该返回 $0$ 并且不要调用 `build`。

#### 约束条件

- $1\le n\le 1000$
- $p[i][i]=1$（对所有 $0 \le i \le n-1$）
- $p[i][j]=p[j][i]$（对所有 $0 \le i,j \le n-1$）
- $0 \le p[i][j] \le 3$（对所有 $0 \le i,j \le n-1$）

#### 子任务

1. （11 分）$p[i][j]=1$（对所有 $0 \le i,j \le n-1$）
2. （10 分）$p[i][j] \in \{0,1\}$（对所有 $0 \le i,j \le n-1$）
1. （19 分）$p[i][j] \in \{0,2\}$（对所有 $i \ne j,0 \le i,j \le n-1$）
1. （35 分）$0 \le p[i][j]\le 2$（对所有 $0 \le i,j \le n-1$）并且至少有一种建设方案满足要求
1. （21 分）$0 \le p[i][j] \le 2$（对所有 $0 \le i,j \le n-1$）
1. （4 分）没有额外约束条件

#### 评测程序示例

评测程序示例以如下格式读取输入数据：

第 $1$ 行：$n$       
第 $2+i$ 行（$0 \le i \le n+1$）：$p[i][0]\ p[i][1]\ \ldots\ p[i][n]$

评测程序示例的输出格式如下：

第 $1$ 行: `construct` 的返回值。

如果 `construct` 的返回值为 $1$，评测程序示例会额外打印：

第 $2+i$ 行（$0 \le i \le n+1$）：$b[i][0]\ b[i][1]\ \ldots\ b[i][n]$


---

---
title: "[BalticOI 2015] File Paths"
layout: "post"
diff: 提高+/省选-
pid: P6843
tag: ['图论', '2015', '深度优先搜索 DFS', 'BalticOI（波罗的海）']
---
# [BalticOI 2015] File Paths
## 题目描述

一个文件 $\tt file$ 都需要在一个包含很多文件 $\tt dir1,dir2,\cdots,dirj$ 的目录中，这个文件的 absolute file path 为 $\tt/dir1/dir2/\cdots/dirj/file$，根目录用 $\tt /$ 表示，每一个放在根目录下的文件的 absolute file path 的形式为 $\tt /file$。

符号链接指向一个已被命名的目录，可以看作一个快捷方式，他可以放置在任意目录下，注意，符号链接不能指向文件。比如，我们在 $\tt /$ 下放一个指向 $\tt /$ 的符号链接 $\tt hello$，那么，$\tt /dir/file$，$\tt /hello/dir/file$，$\tt /hello/hello/dir/dile$ 都指向同一个文件 $\tt file$。另比如，我们在 $\tt /dir$ 下放一个指向 $\tt /$ 的符号链接 $\tt hi$，那么，$\tt /dir/file$，$\tt /dir/hi/dir/file$，$\tt /dir/hi/dir/hi/dir/file$ 都指向同一个文件 $\tt file$。符号链接指向上一层，下一层，甚至同层都可以，但是不允许 $\tt ./$，$\tt ../$，$\tt //$ 之类的操作。

现在想问，是否能通过引入一个长为 $s$ 的符号链接使得找到一个文件的 absolute file path 长度恰好为 $k$？
## 输入格式

第一行三个整数 $n,m,k$ 代表除根目录之外的目录数，文件数和要求等于的路径长度。        
第二行一个整数 $s$ 代表符号链接长。       
接下来 $n$ 行每行两个整数 $p_i,l_i$ 描述一个目录，这个目录编号为 $l_i$，父目录编号为 $p_i$。        
接下来 $m$ 行每行两个整数 $p_j,l_j$，描述一个文件，这个文件的长度为 $l_j$，父目录编号为 $p_j$。
## 输出格式

$m$ 行每行一个字符串代表是否能通过引入一个长为 $s$ 的符号链接使得找到编号为 $j$ 的文件的 absolute file path 长度恰好为 $k$，如果是的话输出 $\tt YES$，否则输出 $\tt NO$。
## 样例

### 样例输入 #1
```
2 4 22
2
0 1
1 5
2 13
2 10
1 4
0 7
```
### 样例输出 #1
```
YES
YES
YES
NO
```
## 提示

#### 样例 1 解释

假设符号链接名字为 $\tt LL$，目录名字为 $\tt a$，$\tt bbbbb$，文件名字为 $\tt ccccccccccccc$，$\tt dddddddddd$，$\tt eee$，$\tt fffffff$，根目录下包含目录 $\tt a$ 和文件 $\tt fffffff$，目录 $\tt a$ 下包含目录 $\tt bbbbb$ 和文件 $\tt eee$，目录 $\tt bbbbb$ 包含文件 $\tt ccccccccccccc$ 和 $\tt dddddddddd$。下面是形象化的表述：

```plain
/
|-- a
| |-- bbbbb
| | |-- ccccccccccccc
| | +-- dddddddddd
| +-- eeee
+-- fffffff
```

- 对于第 $1$ 个文件，满足条件的路径为 $\tt /a/bbbbb/ccccccccccccc$。
- 对于第 $2$ 个文件，满足条件的路径为 $\tt /a/LL/bbbbb/dddddddddd$。
- 对于第 $3$ 个文件，满足条件的路径为 $\tt /a/LL/a/LL/a/LL/a/eeee$。
- 对于第 $4$ 个文件，无满足条件的路径。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（33 pts）：$n,m \le 500$。
- Subtask 2（33 pts）：$n,m \le 3 \times 10^3$，符号链接最多被调用一次。
- Subtask 3（34 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le k,s \le 10^6$，$1\le m,n\le 3\times 10^3$。

#### 说明

翻译自 [BalticOI 2015 Day2 A File Paths](https://boi.cses.fi/files/boi2015_day2.pdf)。


---

---
title: "「EZEC-10」序列"
layout: "post"
diff: 提高+/省选-
pid: P7717
tag: ['动态规划 DP', '2021', 'O2优化', '深度优先搜索 DFS', '数位 DP', '图论建模', '字典树 Trie', '位运算']
---
# 「EZEC-10」序列
## 题目背景

> 精准的解析刻画，是应该首先尝试的突破口。

——command_block 《考前小贴士》
## 题目描述

请问有多少个不同的序列 $a$，满足：
1. $a$ 的长度为 $n$。
2. $a$ 中的元素均为不大于 $k$ 的非负整数。
3. 满足 $m$ 组形如 $(x_i,y_i,z_i)$ 且 $x_i<y_i$ 的限制，每组限制的意义为 $a_{x_i} \oplus a_{y_i} = z_i$ （$\oplus$ 表示按位异或运算）。

两个序列相同，当且仅当它们所有元素均相同。

请输出答案对 $10^9+7$ []($114514\times(114\times5\times14+((1+145)\times(1+4)+(1\times14+5-1+4)))+(114\times514+(11\times(451+4)+(-1+145+14)))$)取模的结果。
## 输入格式

输入共 $m+1$ 行：
- 第一行三个数，$n,m,k$。
- 接下来 $m$ 行，每行 $3$ 个数，$x_i,y_i,z_i$。
## 输出格式

输出仅一行，表示答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
3 1 2
1 2 1
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
5 1 12
1 2 3

```
### 样例输出 #2
```
26364
```
## 提示

【样例 $1$ 说明】

共有 $6$ 种序列：$\{0,1,0\},\{0,1,1\},\{0,1,2\},\{1,0,0\},\{1,0,1\},\{1,0,2\}$。

【数据规模与约定】

**本题采用捆绑测试。**

- Subtask 1（1 point）：$n=1$。
- Subtask 2（5 points）：$m=0$。
- Subtask 3（15 points）：$n,m,k\le 5$。
- Subtask 4（10 points）：$z_i=0$。
- Subtask 5（20 points）：$k\le 16$。
- Subtask 6（2 points）：数据随机。
- Subtask 7（47 points）：无特殊限制。

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^5$，$0 \le m \le 5 \times 10^5$，$0 \le z_i<2^{30}$，$1 \leq k< 2^{30}$，$1\le x_i,y_i\le n$。

【提示】

如果你不知道什么是异或，请点击[这里](https://baike.baidu.com/item/%E5%BC%82%E6%88%96#:~:text=%E5%BC%82%E6%88%96%E4%B9%9F%E5%8F%AB%E5%8D%8A,%E8%AE%A4%E4%BD%9C%E4%B8%8D%E8%BF%9B%E4%BD%8D%E5%8A%A0%E6%B3%95%E3%80%82&text=%E7%A8%8B%E5%BA%8F%E4%B8%AD%E6%9C%89%E4%B8%89%E7%A7%8D%E6%BC%94%E7%AE%97%E5%AD%90%EF%BC%9AXOR%E3%80%81eor%E3%80%81%E2%8A%95%E3%80%82)。


---

---
title: "「EVOI-RD1」摘叶子"
layout: "post"
diff: 提高+/省选-
pid: P7864
tag: ['博弈论', '深度优先搜索 DFS']
---
# 「EVOI-RD1」摘叶子
## 题目描述

某日，小 A 和小 B 在一起开心地玩着游戏。

他们找了一棵以 $1$ 节点为根节点的树，很显然，作为一棵树，总有一个或好多个叶子节点。小 A 和小 B 玩的是回合制游戏。

每次小 A 或小 B 可以选择**任意数量**的叶子节点，将其从树中摘下（每次只能摘叶子节点，每次摘的数量不限制，但**不能不摘**，更不能摘的数量超过本来叶子节点的数量）。

很显然，把一些叶子摘下后，他们的父亲节点有可能会成为新的叶子节点，这时，这些新成为叶子节点的原父亲节点也变得可以被摘取了。

现在，小 A 先摘，小 B 再摘，往复循环。把 $1$ 号节点摘下的人获胜。我们知道，小 A 和小 B 总会按最优方式进行游戏，问谁会取得胜利。
## 输入格式

**本题有多组测试数据。**

第一行一个正整数 $T$，表示一共有 $T$ 组数据。

每组数据的第二行一个正整数 $n$，表示这棵树有 $n$ 个节点。

每组数据的第三行，$n-1$ 个整数，代表从 $2$ 号节点到 $n$ 号节点的父亲节点编号。
## 输出格式

共 $T$ 行，每行一个整数 $1$ 或 $0$。

$1$ 代表小 A 会取得胜利，$0$ 代表小 B 会取得胜利。
## 样例

### 样例输入 #1
```
2
3
1 1
4
1 2 3

```
### 样例输出 #1
```
1
0

```
## 提示

本题数据随机，只要简单分析一下性质，就很好骗分，因此本题采用**捆绑测试**。

对于 $40\%$ 的数据：$1 \leq n \leq 100$。

对于 $100\%$ 的数据：$1 \leq n \leq 10^6$，$1 \leq T \leq 10$。

本题时空限制（尤其是空间）均非常宽松，不卡常，不毒瘤，请放心食用。


---

---
title: "[FOI2021] 幸运区间"
layout: "post"
diff: 提高+/省选-
pid: P8317
tag: ['搜索', '2021', '福建', '枚举', '分治', '深度优先搜索 DFS', '剪枝']
---
# [FOI2021] 幸运区间
## 题目背景

2021 年福建省青少年信息学编程水平认证 第四题。
## 题目描述

一个抽奖活动正在进行。每个参加活动的人拿到了 $n$ 个序列，每个序列包含了 $d$ 个正整数，以及一个数字 $k$，代表这些正整数中，存在 $k$ 个幸运数字。

每个拿到序列的人，会从自己手中的序列中选出连续的若干个序列形成一个区间，称之为待选区间。如果待选区间中的每一个序列都包含至少一个幸运数字，则称该区间为幸运区间。当然幸运区间可能不止一个。游戏规定，其中包含的序列最多的即总长度最长的那个幸运区间称为超级幸运区间。

例如：$d=2,k=3$ 时，序列如下：

- 序列 $0$：``115 120``。
- 序列 $1$：``50 80``。
- 序列 $2$：``199 30``。
- 序列 $3$：``40 40``。
- 序列 $4$：``30 30``。
- 序列 $5$：``25 40``。

从序列 $0$ 到序列 $2$ 的区间是幸运区间，因为从 $0$ 到 $2$ 中的每个序列都包含了 $120,50$ 或 $30$，共 $3$ 个幸运数字。从序列 $1$ 到序列 $5$ 的区间也是幸运区间，因为 $1$ 到 $5$ 的所有序列都包含 $80,30$ 或 $40$，并且包含了 $5$ 个序列，是总长度最大的超级幸运区间。

每个有序列的人都想知道自己的超级幸运区间是怎样的。编程任务就是对于每个拿到序列的人，输出总长度最大的超级幸运区间的第一个元素的下标和最后一个元素的下标。如果有多个长度一样的，输出第一个元素下标最小的。请注意下标从 $0$ 开始。
## 输入格式

第一行包含一个整数 $T$，表示拿到序列的人的数量。

接下来 $T$ 组数字，每组描述的是每个人的序列信息。

每组数据的第一行是三个正整数 $n,d,k$，描述如上。接下来一行，包含 $n\times d$ 个整数，前 $d$ 个整数表示第 $0$ 个序列，接下来 $d$ 个表示第 $1$ 个序列，以此类推。
## 输出格式

对于每个人，输出一行，``Case #x: y z``，$x$ 表示 $\text{case}$ 标号（从 $1$ 开始），$y$ 和 $z$ 是答案区间的第一个和最后一个元素的下标。

（``Case`` 与 ``#`` 之间有一个空格，``#`` 与 ``x`` 之间没有空格，``:`` 后面 ``y`` 之前有一个空格，``y`` 与 ``z`` 之间有一个空格）
## 样例

### 样例输入 #1
```
4
8 1 2
1 2 3 2 4 5 4 6
4 3 2
1 2 3 4 5 6 7 8 9 10 11 12
6 2 3
10 20 50 60 70 30 40 40 30 30 20 40
10 1 3
2 4 3 1 4 5 3 1 1 2
```
### 样例输出 #1
```
Case #1: 1 3
Case #2: 0 1
Case #3: 1 5
Case #4: 1 4
```
## 提示

#### 数据范围

对于 $45\%$ 的数据，$n\le1000$。

对于 $50\%$ 的数据，$k=2$。

前两部分数据共计 $70\%$。

对于 $100\%$ 的数据，$2\le k\le 3$。

输入文件在 $\text{4.8M}$ 以内，$T=10,1\le d\le 4,1\le$ 每个序列中的数字 $\le10^5$。

对于最多 $6$ 个 $\text{case}$，$1\le n\le 10^5$，对于其他所有的 $\text{case}$，$1\le n\le 10^3$。


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

