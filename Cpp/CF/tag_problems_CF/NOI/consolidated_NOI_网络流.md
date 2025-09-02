---
title: "Projectors"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1250K
tag: ['网络流']
---

# Projectors

## 题目描述

There are $ n $ lectures and $ m $ seminars to be conducted today at the Faculty of Approximate Sciences. The $ i $ -th lecture starts at $ a_i $ and ends at $ b_i $ (formally, time of the lecture spans an interval $ [a_i, b_i) $ , the right bound is exclusive). The $ j $ -th seminar starts at $ p_j $ and ends at $ q_j $ (similarly, time of the seminar spans an interval $ [p_j, q_j) $ , the right bound is exclusive).

There are $ x $ HD-projectors numbered from $ 1 $ to $ x $ and $ y $ ordinary projectors numbered from $ x + 1 $ to $ x + y $ available at the faculty. Projectors should be distributed in such a way that:

- an HD-projector is used in each lecture;
- some projector (ordinary or HD) is used in each seminar;
- a projector (ordinary or HD) can only be used in one event at the same moment of time;
- if a projector is selected for an event, it is used there for the whole duration of the event;
- a projector can be reused in some following event, if it starts not earlier than current event finishes.

You are to find such distribution of projectors, if it exists.

Again, note that the right bound of the event's time range is not inclusive: if some event starts exactly when another event finishes, the projector can be reused (suppose that it is instantly transported to the location of the event).

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 300 $ ) — the number of test cases.

Each test case starts with a line containing four integers $ n, m, x, y $ ( $ 0 \le n, m, x, y \le 300 $ ; $ n+m>0 $ , $ x + y > 0 $ ) — the number of lectures, the number of seminars, the number of HD projectors and the number of ordinary projectors, respectively.

The next $ n $ lines describe lectures. Each line contains two integers $ a_i $ , $ b_i $ ( $ 1 \le a_i < b_i \le 10^6 $ ) — the start time (inclusive) and finish time (exclusive) of the $ i $ -th lecture.

The next $ m $ lines describe seminars. Each line contains two integers $ p_j $ , $ q_j $ ( $ 1 \le p_j < q_j \le 10^6 $ ) — the start time (inclusive) and finish time (exclusive) of the $ j $ -th seminar.

## 输出格式

For each test case, print YES if it is possible to distribute projectors in order to meet all requirements, or NO otherwise.

In case of positive answer, output one additional line containing $ n + m $ integers. The first $ n $ integers should be not less than $ 1 $ and not greater than $ x $ , and the $ i $ -th of them should be the index of HD projector used in the $ i $ -th lecture. The last $ m $ integers should be not less than $ 1 $ and not greater than $ x + y $ , and the $ j $ -th of them should be the index of projector used in the $ j $ -th seminar. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
2
2 2 2 2
1 5
2 5
1 5
1 4
2 0 2 10
1 3
1 3

```

### 输出

```
YES
2 1 4 3 
YES
2 1 

```

## 样例 #2

### 输入

```
3
1 2 1 1
3 4
2 4
1 3
3 4 2 3
5 7
1 3
1 7
4 8
2 5
1 6
2 8
0 1 1 0
1 1000000

```

### 输出

```
YES
1 2 1 
NO
YES
1 

```



---

---
title: "Lost Luggage"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2097F
tag: ['网络流']
---

# Lost Luggage

## 题目描述

众所周知，航空公司"Trouble"经常丢失行李，为此关心的记者们决定计算可能无法归还给旅客的行李最大数量。

航空公司"Trouble"在编号从 $1$ 到 $n$ 的 $n$ 个机场间运营航班。记者们的实验将持续 $m$ 天。已知在实验第一天午夜前，第 $j$ 个机场有 $s_j$ 件遗失行李。在第 $i$ 天会发生以下事件：

- 早晨，同时起飞 $2n$ 个航班，包括 $n$ 个第一类航班和 $n$ 个第二类航班：
  - 第一类第 $j$ 个航班从机场 $j$ 飞往机场 $(((j-2) \bmod n )+ 1)$（前一个机场，第一个机场的前一个是最后一个），最多可运输 $a_{i,j}$ 件遗失行李；
  - 第二类第 $j$ 个航班从机场 $j$ 飞往机场 $((j \bmod n) + 1)$（后一个机场，最后一个机场的后一个是第一个），最多可运输 $c_{i,j}$ 件遗失行李；
- 下午，机场会进行遗失行李检查。如果当天航班起飞后，第 $j$ 个机场剩余 $x$ 件行李且 $x \ge b_{i, j}$，则至少会有 $x - b_{i, j}$ 件行李被找到，不再视为遗失；
- 晚上，当天所有 $2n$ 个航班结束，运输的遗失行李抵达对应机场。

对于每个 $k$ 从 $1$ 到 $m$，记者们想知道在前 $k$ 天的检查中可能未被找到的遗失行李最大数量。注意每个 $k$ 的计算都是独立的。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 100$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$3 \le n \le 12$，$1 \le m \le 2000$）——机场数量和实验天数。

每个测试用例的第二行包含 $n$ 个整数 $s_1, s_2, \ldots, s_n$（$0 \le s_i \le 10^8$）——每个机场初始的遗失行李数量。

接下来按顺序给出 $m$ 天的描述：

每个第 $i$ 天的描述中：
- 第一行包含 $n$ 个整数 $a_{i,1}, a_{i,2}, \ldots, a_{i,n}$（$0 \le a_{i, j} \le 10^8$）——每个机场可以运输到前一个机场的遗失行李最大数量；
- 第二行包含 $n$ 个整数 $b_{i,1}, \ldots, b_{i,n}$（$0 \le b_{i, j} \le 10^8$）——第 $i$ 天每个机场将被找到的遗失行李最小数量；
- 第三行包含 $n$ 个整数 $c_{i,1}, \ldots, c_{i,n}$（$0 \le c_{i, j} \le 10^8$）——每个机场可以运输到后一个机场的遗失行李最大数量。

保证所有测试用例的 $m$ 之和不超过 $2000$。

## 输出格式

对于每个测试用例，输出 $m$ 个整数——分别对应前 $1$ 天到前 $m$ 天可能未被找到的遗失行李最大数量。


## 说明/提示

在第一个测试用例中：
- 第一天，所有 $5$ 件行李都可能未被找到，因为可以从每个机场发送航班运输遗失行李；
- 第二天早晨，第 $2$ 个机场最多可能有 $3$ 件行李，第 $5$ 个机场最多 $2$ 件，其他机场可能没有行李。所有行李可能仍留在第 $5$ 个机场。在第 $2$ 个机场，最多 $2$ 件行李可以被发送到相邻机场。因此，至少有 $1$ 件行李会被找到；
- 到第三天结束时，遗失行李可能只在第 $1$ 和第 $2$ 个机场。每个机场最多有 $1$ 件，意味着最多总共 $2$ 件行李未被找到。

在第二个测试用例中，所有行李可能留在原机场，检查不会找到任何遗失行李。因此答案是 $10^8 + 5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 3
1 1 1 1 1
0 0 1 0 0
0 1 0 0 1
1 0 0 1 0
0 1 0 0 0
9 0 9 9 9
0 1 0 0 0
0 0 0 0 0
9 0 9 0 0
0 0 0 0 0
3 1
0 100000000 5
0 100000000 5
0 100000000 5
0 100000000 5
```

### 输出

```
5
4
2
100000005
```



---

---
title: "Tanya is 5!"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF737E
tag: ['网络流', '二分图']
---

# Tanya is 5!

## 题目描述

Tanya 五岁了！所以她所有的朋友都来给她庆祝生日。包括Tanya在内，一共有 $n$ 个孩子参加了庆典。

庆典就快要结束了，还有最后一项活动——玩游戏机没有完成。在大厅里放着 $m$ 台游戏机，它们的编号为 $1\!\sim\!m$ 。 每个孩子都有一个游戏机清单，上面有他想玩的游戏机编号和对应的时间。对于每一台游戏机，在同一时刻只能被一个孩子使用。

现在已经是傍晚了，大人们都想快点回家。为了加快这个活动的进程，对于每一台机器你都可以额外租用**一台**备用机器。对于编号为 $j$ 的机器的备用机，租金为 $p_j$ 。当你租用了一台备用机以后，它可以在任何时间被使用。备用机和游戏机一样，在同一时刻只能被一个孩子使用。

如果你有 $b$ 元预算来租用备用机，需要多长时间才能使所有孩子都完成他们的游戏机清单？每台游戏机只有一台备用机可租用，所以你不可能拥有三台编号相同的机器。

孩子们可以在任意时间停止或者继续游戏。在你租用了第 $j$ 台游戏机的备用机后，如果第 $i$ 个孩子想要玩第 $j$ 台游戏机，他可以花一部分时间玩第 $j$ 台游戏机，花另一部分时间玩第 $j$ 台游戏机的备用机（每一部分都可以为空）。停止和改变使用机器的行为都可以在任何整数时刻发生，并且认为是瞬间完成，不花费时间。当然，一个孩子不可能同时使用两台机器。

记住，这不是为了省钱（没有人会为了省钱而牺牲孩子的快乐！）, 这是为了尽量缩短孩子们完成清单所需的时间。

## 输入格式

第一行包含三个整数 $n$，$m$ 和 $b$ $(1\!\le\!n\!\le\!40 $，$1\!\le\!m\!\le\!10$，$0\!\le\!b\!\le\!10^6)$，分别表示孩子数量，游戏机数量和预算。

第二行包含 $m$ 个整数 $p_1$，$p_2$，$\dots$，$p_m(1\!\le\!p_j\!\le\!10^6)$，其中 $p_j$ 表示编号为 $j$ 的游戏机的备用机所需租金。

接下来有 $n$ 行，第 $i$ 行描述了第 $i$ 个孩子的游戏机清单。每一行开头有一个整数 $k_i(0\!\le\!k_i\!\le\!m)$ ，表示第 $i$ 个孩子想玩的游戏机的数量。之后有 $k_i$ 对数，第 $y$ 对是 $x_{iy},t_{iy}$ 。这表示第 $i$ 个孩子想在编号为 $x_{iy}$ 的游戏机上玩 $t_{iy}$ 分钟。在这 $n$ 行中，$x_{iy}$ 的值是不同的。$(1\!\le\!x_{iy}\!\le\!m$，$1\!\le\!t_{iy}\!\le\!2500)$

## 输出格式

在第一行输出所有孩子完成他们的游戏机清单的最小时间。

在第二行输出一个长度为 $m$ 的$01$字符串，如果租用了编号为 $j$ 的游戏机的备用机，那么第 $j$ 个字符为  $1$，否则为 $0$。

在第三行输出一个整数 $g(0\le\!g\!\le10^6)$，表示所有孩子连续玩游戏机的时间片段总数。
接下来 $g$ 行输出四个整数 $i$，$j$，$s$，$d$，表示第 $i$ 个孩子从 $s$ $(0\le\!s)$ 时刻开始玩了 $d\;(1\le\!d)$。你可以以任意顺序输出这些行。

如果有多个可能的答案，请输出其中任意一个。

## 样例 #1

### 输入

```
2 2 100
3 7
2 1 3 2 1
2 1 3 2 1

```

### 输出

```
4
10
8
1 1 0 1
2 2 0 1
1 1 1 1
2 1 1 1
2 1 2 1
1 1 2 1
1 2 3 1
2 1 3 1

```

## 样例 #2

### 输入

```
3 2 15
11 7
2 2 10 1 5
1 2 20
2 1 4 2 3

```

### 输出

```
20
01
17
2 2 0 4
2 2 4 1
1 1 5 2
2 2 5 2
1 2 7 5
2 2 7 5
2 2 12 1
1 2 12 1
3 1 13 4
2 2 13 4
1 2 13 4
1 1 17 2
3 2 17 2
2 2 17 2
1 1 19 1
2 2 19 1
3 2 19 1

```



---

---
title: "Maximum Flow"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF843E
tag: ['网络流', '上下界网络流']
---

# Maximum Flow

## 题目描述

You are given a directed graph, consisting of $ n $ vertices and $ m $ edges. The vertices $ s $ and $ t $ are marked as source and sink correspondingly. Additionally, there are no edges ending at $ s $ and there are no edges beginning in $ t $ .

The graph was constructed in a following way: initially each edge had capacity $ c_{i}&gt;0 $ . A maximum flow with source at $ s $ and sink at $ t $ was constructed in this flow network. Let's denote $ f_{i} $ as the value of flow passing through edge with index $ i $ . Next, all capacities $ c_{i} $ and flow value $ f_{i} $ were erased. Instead, indicators $ g_{i} $ were written on edges — if flow value passing through edge $ i $ was positive, i.e. $ 1 $ if $ f_{i}&gt;0 $ and $ 0 $ otherwise.

Using the graph and values $ g_{i} $ , find out what is the minimum possible number of edges in the initial flow network that could be saturated (the passing flow is equal to capacity, i.e. $ f_{i}=c_{i} $ ). Also construct the corresponding flow network with maximum flow in it.

A flow in directed graph is described by flow values $ f_{i} $ on each of the edges so that the following conditions are satisfied:

- for each vertex, except source and sink, total incoming flow and total outcoming flow are equal,
- for each edge $ 0<=f_{i}<=c_{i} $

A flow is maximum if the difference between the sum of flow values on edges from the source, and the sum of flow values on edges to the source (there are no such in this problem), is maximum possible.

## 输入格式

The first line of input data contains four positive integers $ n,m,s,t $ ( $ 2<=n<=100 $ , $ 1<=m<=1000 $ , $ 1<=s,t<=n $ , $ s≠t $ ) — the number of vertices, the number of edges, index of source vertex and index of sink vertex correspondingly.

Each of next $ m $ lines of input data contain non-negative integers $ u_{i} $ , $ v_{i} $ , $ g_{i} $ ( $ 1<=u_{i},v_{i}<=n $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843E/201335e9198f48d5febb70f0affd569974e4ae7f.png)) — the beginning of edge $ i $ , the end of edge $ i $ and indicator, which equals to $ 1 $ if flow value passing through edge $ i $ was positive and $ 0 $ if not.

It's guaranteed that no edge connects vertex with itself. Also it's guaranteed that there are no more than one edge between each ordered pair of vertices and that there exists at least one network flow that satisfies all the constrains from input data.

## 输出格式

In the first line print single non-negative integer $ k $ — minimum number of edges, which should be saturated in maximum flow.

In each of next $ m $ lines print two integers $ f_{i},c_{i} $ ( $ 1<=c_{i}<=10^{9} $ , $ 0<=f_{i}<=c_{i} $ ) — the flow value passing through edge $ i $ and capacity of edge $ i $ .

This data should form a correct maximum flow in flow network. Also there must be exactly $ k $ edges with statement $ f_{i}=c_{i} $ satisfied. Also statement $ f_{i}&gt;0 $ must be true if and only if $ g_{i}=1 $ .

If there are several possible answers, print any of them.

## 说明/提示

The illustration for second sample case. The saturated edges are marked dark, while edges with $ g_{i}=0 $ are marked with dotted line. The integer on edge is the index of this edge in input list. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843E/da38835a9ed43e4db05620dc1c76827cb3c4290c.png)

## 样例 #1

### 输入

```
5 6 1 5
1 2 1
2 3 1
3 5 1
1 4 1
4 3 0
4 5 1

```

### 输出

```
2
3 3
3 8
3 4
4 4
0 5
4 9

```



---

