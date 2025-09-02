---
title: "[GESP202312 七级] 商品交易"
layout: "post"
diff: 普及/提高-
pid: P10110
tag: ['2023', '最短路', 'GESP']
---
# [GESP202312 七级] 商品交易
## 题目描述

市场上共有 $N$ 种商品，编号从 $0$ 至 $N-1$ ，其中，第 $i$ 种商品价值 $v_i$ 元。

现在共有 $M$ 个商人，编号从 $0$ 至 $M-1$ 。在第 $j$ 个商人这，你可以使用你手上的第 $x_j$ 种商品交换商人手上的第 $y_j$ 种商品。每个商人都会按照商品价值进行交易，具体来说，如果 $v_{x_j}>v_{y_j}$，他将会付给你 $v_{x_j}-v_{y_j}$元钱；否则，那么你需要付给商人 $v_{x_j}-v_{y_j}$ 元钱。除此之外，每次交易商人还会收取 $1$ 元作为手续费，不论交易商品的价值孰高孰低。

你现在拥有商品 $a$ ，并希望通过一些交换来获得商品 $b$ 。请问你至少要花费多少钱？（当然，这个最小花费也可能是负数，这表示你可以在完成目标的同时赚取一些钱。）
## 输入格式

第一行四个整数 $N , M , a , b$，分别表示商品的数量、商人的数量、你持有的商品以及你希望获得的商品。保证 $0 \le a,b < N$ ，保证 $a \ne b$。

第二行 $N$ 个用单个空格隔开的正整数 $v_0,v_1,…,v_{N-1}$ ，依次表示每种商品的价值。保证 $1≤v_i≤10^9$。

接下来 $M$ 行，每行两个整数 $x_j,y_j$ ，表示在第 $j$ 个商人这，你可以使用第 $x_j$ 种商品交换第 $y_j$ 种商品。保证 $0≤x_j,y_j<N$，保证 $x_j≠y_j$ 。
## 输出格式

输出一行一个整数，表示最少的花费。特别地，如果无法通过交换换取商品 $b$ ，请输出 `No solution`。
## 样例

### 样例输入 #1
```
3 5 0 2
1 2 4
1 0
2 0
0 1
2 1
1 2
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
3 3 0 2
100 2 4
0 1
1 2
0 2
```
### 样例输出 #2
```
-95
```
### 样例输入 #3
```
4 4 3 0
1 2 3 4
1 0
0 1
3 2
2 3
```
### 样例输出 #3
```
No solution
```
## 提示

**数据范围**

对于30%的测试点，保证 $N ≤ 10$ ，$M ≤ 20$。

对于70%的测试点，保证 $N ≤10^3$ ，$M≤10^4$。

对于100%的测试点，保证 $N≤10^5$，$M≤2×10^5$。


---

---
title: "[Opoi 2024] 数据转换"
layout: "post"
diff: 普及/提高-
pid: P10535
tag: ['O2优化', '最短路']
---
# [Opoi 2024] 数据转换
## 题目背景

![](data:image/jpeg;base64,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)

![](https://tse2-mm.cn.bing.net/th/id/OIP-C.ojcWO_62WQhtFFaZSdmbgAHaEo?w=244&h=180&c=7&r=0&o=5&pid=1.7)

Arrda 家里面有很多五花八门的用电器和数据线，而且很多用电器的插头种类都不一样，这导致每次 Arrda 想要共享两个用电器的数据时都要一半天用来买到合适的数据线，而且有的时候数据线很贵！

于是 Arrda 想让你求出花钱最少的数据转换方案。
## 题目描述

Arrda 家中有 $n$ 类，$2n$ 种数据线接头，每一类插头有 $2$ 种不同接头，种类分别为 $i$ 和 $n+i$，**有且只有同一类的不同接头可以互相连接（你可以理解为 $i$ 是凸出的接头，$n + i$ 是凹的接头，可以连接可以理解为插上）**。

商城里售卖着 $m$ 种双向数据线，每根双向数据线两端各有一个接头，种类分别为为 $u_i,v_i$。同时，第 $i$ 种双向数据线有一个购买价格 $w_i$，每种数据线可以购买无限条。

Arrda 想要交换两个用电器的数据，其中两个用电器的接头种类编号为 $S,T$，求能使这两个用电器能直接或由若干条数据线相连的最小总价格（毕竟买数据线需要钱），如果无解，输出 `I have no idea how to solve it.`，注意，**两个用电器的接口不能直接连接数据线，因为它们在用电器上，而非数据线两端！**
## 输入格式

第一行两个整数 $n,m$，意义见题面。

接下来 $m$ 行，每行三个整数 $u_i,v_i,w_i$。

接下来一行两个整数 $S,T$。
## 输出格式

一个非负整数表示能使这两个用电器能直接或由若干条数据线相连的最小总价格。

若无解，请输出 `I have no idea how to solve it.`。
## 样例

### 样例输入 #1
```
4 4
5 8 10
7 8 2
2 3 1
5 6 5
1 4
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
4 1
2 3 1
1 8
```
### 样例输出 #2
```
I have no idea how to solve it.
```
### 样例输入 #3
```
4 1
2 3 1
1 5
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
5 10
1 2 603124134
2 3 373980902
2 4 6578324
3 5 936364479
4 6 182080546
4 7 340293479
6 8 753053273
1 9 274129271
3 10 616764767
4 6 255802600
1 2
```
### 样例输出 #4
```
3673658542
```
## 提示

### 样例 1 解释：

![picture](https://cdn.luogu.com.cn/upload/image_hosting/4j95t4xl.png)

```
1=5->6=2->3=7->8=4
```

可以证明，没有总代价更小的方案。

### 样例 4 解释

![222](https://cdn.luogu.com.cn/upload/image_hosting/k88cjz1t.png)

```
1=6->8=3->5=10->3=8->6=1->9=4->7=2
```
`4->6` 有两种数据线，我们选择代价为 $182080546$ 的那一根，因为其代价更小。

可以证明，没有总代价更小的方案。

### 数据范围

对于 $100\%$ 的数据，$1\le n,m \le 10^5$，$1\le u_i,v_i,s,t \le 2 \times n$，$1\le w_i \le 10^9$。


---

---
title: "[HBCPC2024] LCMs"
layout: "post"
diff: 普及/提高-
pid: P10869
tag: ['数学', '2024', 'O2优化', '最短路', 'XCPC', '湖北']
---
# [HBCPC2024] LCMs
## 题目描述

Walk Alone has a number axis with only positive integers on it. The cost of walking from point on integer $a$ to point on integer $b$ is ${\rm lcm}(a, b)$, where ${\rm lcm}(a, b)$ means the least common multiple of integers $a$ and $b$. Due to the hatred of the integer $1$, Walk Alone forbids anyone from moving to points on integers $\textbf{smaller than or equal to}$ $1$.

Given two integers $a$ and $b$, you need to calculate the minimal cost of walking from point on integer $a$ to $b$.
## 输入格式

There are $T$ ($1 \le T \le 1000$) test cases.

In each test case, there is only one line containing two integers $a$ and $b$ ($2 \le a \le b \le 10^7$), denoting the start and end point.
## 输出格式

For each test case, output a single integer denoting the minimal cost.
## 样例

### 样例输入 #1
```
3
3 4
10 15
2 4
```
### 样例输出 #1
```
10
25
4
```
## 提示

In the first test case, you can walk such a path: $3 \to 2 \to 4$, where the total cost is ${\rm lcm}(3, 2) + {\rm lcm}(2, 4) = 6 + 4 = 10$, which can be proved to be the minimum.


---

---
title: "[GESP202503 八级] 上学"
layout: "post"
diff: 普及/提高-
pid: P11966
tag: ['2025', '最短路', 'GESP']
---
# [GESP202503 八级] 上学
## 题目描述

C 城可以视为由 $n$ 个结点与 $m$ 条边组成的无向图。 这些结点依次以 $1, 2, \ldots, n$ 标号，边依次以 $1 \leq i \leq m$ 连接边号为 $u_i$ 与 $v_i$ 的结点，长度为 $l_i$ 米。

小 A 的学校坐落在 C 城的编号为 $s$ 的结点。小 A 的同学们共有 $q$ 位，他们想在保证不迟到的前提下，每天尽可能晚地出门上学。但同学们并不会计算从家需要多久才能到学校，于是找到了聪明的小 A。第 $i$ 位同学 ($1 \leq i \leq q$) 告诉小 A，他的家位置于编号为 $h_i$ 的结点，并且他每秒钟能行走 1 米。请你帮小 A 计算，每位同学从家出发需要多少秒才能到达学校呢？
## 输入格式

第一行，四个正整数 $n, m, s, q$，分别表示 C 城的结点数与边数，学校所在的结点编号，以及小 A 同学们的数量。

接下来 $m$ 行，每行三个正整数 $u_i, v_i, l_i$，表示 C 城中的一条无向边。

接下来 $q$ 行，每行一个正整数 $h_i$，表示一位同学的情况。
## 输出格式

共 $q$ 行，对于每位同学，输出一个整数，表示从家出发到学校的最短时间。
## 样例

### 样例输入 #1
```
5 5 3 3
1 2 3
2 3 2
3 4 1
4 5 3
1 4 2
5
1
4
```
### 样例输出 #1
```
4
3
1
```
## 提示

**本题采用捆绑测试。**

对于 $20\%$ 的测试点，保证 $q = 1$。

对于另外 $20\%$ 的测试点，保证 $1 \leq n \leq 500$，$1 \leq m \leq 500$。

对于所有测试点，保证 $1 \leq n \leq 2 \times 10^5$，$1 \leq m \leq 2 \times 10^5$，$1 \leq q \leq 2 \times 10^5$，$1 \leq u_i, v_i, s, h_i \leq n$，$1 \leq l_i \leq 10^6$。


---

---
title: "[USACO09OCT] Heat Wave G"
layout: "post"
diff: 普及/提高-
pid: P1339
tag: ['图论', '2009', 'USACO', '福建省历届夏令营', '最短路']
---
# [USACO09OCT] Heat Wave G
## 题目描述

有一个 $n$ 个点 $m$ 条边的无向图，请求出从 $s$ 到 $t$ 的最短路长度。
## 输入格式

第一行四个正整数 $n,m,s,t$。
接下来 $m$ 行，每行三个正整数 $u,v,w$，表示一条连接 $u,v$，长为 $w$ 的边。

## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
7 11 5 4
2 4 2
1 4 3
7 2 2
3 4 3
5 7 5
7 3 3
6 1 1
6 3 4
2 4 3
5 6 3
7 2 1
```
### 样例输出 #1
```
7
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 2500$，$1\le m \le 6200$，$1\le w \le 1000$。

【样例说明】   
$5 \to 6 \to 1 \to 4$ 为最短路，长度为 $3+1+3 = 7$。




---

---
title: "请柬"
layout: "post"
diff: 普及/提高-
pid: P1342
tag: ['图论', '福建省历届夏令营', '最短路']
---
# 请柬
## 题目背景

在电视时代，没有多少人观看戏剧表演。 Malidinesia 古董喜剧演员意识到这一事实，他们想宣传剧院,尤其是古色古香的喜剧片。
## 题目描述

他们已经打印了请帖和所有必要的信息和计划。许多学生被雇来分发这些请柬。每个学生志愿者被指定一个确切的公共汽车站，他或她将留在那里一整天,邀请人们参与。

这里的公交系统是非常特殊的：共有 $n$ 个站点和 $m$ 个线路，所有的线路都是单向的，连接两个站点。公共汽车离开起始点，到达目的地之后又空车返回起始点。

学生每天早上从总部所在的 $1$ 号站点出发，乘公交车到一个预定的站点邀请乘客。每个站点都被安排了一名学生。在一天结束的时候，所有的学生都回到总部。现在需要知道的是，学生所需的公交费用的总和最小是多少。
## 输入格式

输入的第一行是两个整数，代表站点个数 $n$ 和线路条数 $m$。

第 $2$ 到第 $(m + 1)$ 行，每行三个整数 $u, v, w$，代表存在一条从 $u$ 出发到达 $v$ 的线路，费用为 $w$。
## 输出格式

输出一行一个整数，表示最小费用。



## 样例

### 样例输入 #1
```
4 6
1 2 10
2 1 60
1 3 20
3 4 10
2 4 5
4 1 50
```
### 样例输出 #1
```
210 
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证：

- $1 \leq n, m \leq 10^6$。
- $1 \leq u, v \leq n$，$1 \leq w \leq 10^9$。
- 从 $1$ 出发可以到达所有的站点。


---

---
title: "医院设置"
layout: "post"
diff: 普及/提高-
pid: P1364
tag: ['动态规划 DP', '树形数据结构', '广度优先搜索 BFS', '最短路']
---
# 医院设置
## 题目描述

设有一棵二叉树，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kawht13x.png)

其中，圈中的数字表示结点中居民的人口。圈边上数字表示结点编号，现在要求在某个结点上建立一个医院，使所有居民所走的路程之和为最小，同时约定，相邻接点之间的距离为 $1$。如上图中，若医院建在 $1$ 处，则距离和 $=4+12+2\times20+2\times40=136$；若医院建在 $3$ 处，则距离和 $=4\times2+13+20+40=81$。
## 输入格式

第一行一个整数 $n$，表示树的结点数。

接下来的 $n$ 行每行描述了一个结点的状况，包含三个整数 $w, u, v$，其中 $w$ 为居民人口数，$u$ 为左链接（为 $0$ 表示无链接），$v$ 为右链接（为 $0$ 表示无链接）。
## 输出格式

一个整数，表示最小距离和。

## 样例

### 样例输入 #1
```
5						
13 2 3
4 0 0
12 4 5
20 0 0
40 0 0

```
### 样例输出 #1
```
81
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 100$，$0 \leq u, v \leq n$，$1 \leq w \leq 10^5$。


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
title: "[USACO2.4] 回家 Bessie Come Home"
layout: "post"
diff: 普及/提高-
pid: P1529
tag: ['图论', 'USACO', '最短路']
---
# [USACO2.4] 回家 Bessie Come Home
## 题目描述

现在是晚餐时间，而母牛们在外面分散的牧场中。 

Farmer John 按响了电铃，所以她们开始向谷仓走去。 你的工作是要指出哪只母牛会最先到达谷仓（在给出的测试数据中，总会**有且只有**一只最快的母牛）。在挤奶的时候（晚餐前），每只母牛都在她自己的牧场上，一些牧场上可能没有母牛。

每个牧场由一条条道路和一个或多个牧场连接（可能包括自己）。有时，两个牧场（可能是字母相同的）之间会有超过一条道路相连。至少有一个牧场和谷仓之间有道路连接。因此，所有的母牛最后都能到达谷仓，并且母牛总是走最短的路径。当然，母牛能向着任意一方向前进，并且她们以相同的速度前进。牧场被标记为 $\texttt{a} \ldots \texttt{z}$ 和 $\texttt{A} \ldots \texttt{Y}$，在用大写字母表示的牧场中有一只母牛，小写字母中则没有。 谷仓的标记是 $\texttt{Z}$，注意没有母牛在谷仓中。

**注意 $\texttt{m}$ 和 $\texttt{M}$ 不是同一个牧场**。
## 输入格式

第一行一个整数 $P$（$1\leq P \leq 10^4$），表示连接牧场（谷仓）的道路的数目。

接下来 $P$ 行，每行用空格分开的两个字母和一个正整数：被道路连接牧场的标号和道路的长度（道路长度均不超过 $10^3$）。

## 输出格式

单独的一行包含二个项目：最先到达谷仓的母牛所在的牧场的标号，和这只母牛走过的路径的长度。
## 样例

### 样例输入 #1
```
5
A d 6
B d 3
C e 9
d Z 8
e Z 3
```
### 样例输出 #1
```
B 11

```
## 提示

翻译来自 NOCOW

USACO 2.4



---

---
title: "最小花费"
layout: "post"
diff: 普及/提高-
pid: P1576
tag: ['图论', '最短路']
---
# 最小花费
## 题目描述

在 $n$ 个人中，某些人的银行账号之间可以互相转账。这些人之间转账的手续费各不相同。给定这些人之间转账时需要从转账金额里扣除百分之几的手续费，请问 $A$ 最少需要多少钱使得转账后 $B$ 收到 $100$ 元。
## 输入格式


第一行输入两个正整数 $n,m$，分别表示总人数和可以互相转账的人的对数。

以下 $m$ 行每行输入三个正整数 $x,y,z$，表示标号为 $x$ 的人和标号为 $y$ 的人之间互相转账需要扣除 $z\%$ 的手续费 $(z<100)$。

最后一行输入两个正整数 $A,B$。数据保证 $A$ 与 $B$ 之间可以直接或间接地转账。
## 输出格式

输出 $A$ 使得 $B$ 到账 $100$ 元最少需要的总费用。精确到小数点后 $8$ 位。
## 样例

### 样例输入 #1
```
3 3                                     
1 2 1
2 3 2
1 3 3
1 3

```
### 样例输出 #1
```
103.07153164
```
## 提示

$1\le n \le 2000,m\le 100000$。


---

---
title: "邮递员送信"
layout: "post"
diff: 普及/提高-
pid: P1629
tag: ['图论', '优先队列', '最短路', '队列']
---
# 邮递员送信
## 题目描述

有一个邮递员要送东西，邮局在节点 $1$。他总共要送 $n-1$ 样东西，其目的地分别是节点 $2$ 到节点 $n$。由于这个城市的交通比较繁忙，因此所有的道路都是单行的，共有 $m$ 条道路。这个邮递员每次只能带一样东西，并且**运送每件物品过后必须返回邮局**。求送完这 $n-1$ 样东西并且**最终回到邮局**最少需要的时间。
## 输入格式

第一行包括两个整数，$n$ 和 $m$，表示城市的节点数量和道路数量。

第二行到第 $(m+1)$ 行，每行三个整数，$u,v,w$，表示从 $u$ 到 $v$ 有一条通过时间为 $w$ 的道路。
## 输出格式

输出仅一行，包含一个整数，为最少需要的时间。
## 样例

### 样例输入 #1
```
5 10
2 3 5
1 5 5
3 5 6
1 2 8
1 3 8
5 3 4
4 1 8
4 5 3
3 5 6
5 4 2
```
### 样例输出 #1
```
83
```
## 提示

对于 $30\%$ 的数据，$1 \leq n \leq 200$。

对于 $100\%$ 的数据，$1 \leq n \leq 10^3$，$1 \leq m \leq 10^5$，$1\leq u,v \leq n$，$1 \leq w \leq 10^4$，输入保证任意两点都能互相到达。


---

---
title: "炸铁路"
layout: "post"
diff: 普及/提高-
pid: P1656
tag: ['模拟', '搜索', '图论', '并查集', '洛谷原创', '最短路', 'Tarjan']
---
# 炸铁路
## 题目描述

A 国派出将军 uim，对 B 国进行战略性措施，以解救涂炭的生灵。

B 国有 $n$ 个城市，这些城市以铁路相连。任意两个城市都可以通过铁路直接或者间接到达。

uim 发现有些铁路被毁坏之后，某两个城市无法互相通过铁路到达。这样的铁路就被称为 key road。

uim 为了尽快使该国的物流系统瘫痪，希望炸毁铁路，以达到存在某两个城市无法互相通过铁路到达的效果。

然而，只有一发炮弹（A 国国会不给钱了）。所以，他能轰炸哪一条铁路呢？

## 输入格式

第一行 $n,m\ (1 \leq n\leq 150$，$1 \leq m \leq 5000)$，分别表示有 $n$ 个城市，总共 $m$ 条铁路。

以下 $m$ 行，每行两个整数 $a, b$，表示城市 $a$ 和城市 $b$ 之间有铁路直接连接。

## 输出格式

输出有若干行。

每行包含两个数字 $a,b$，其中 $a<b$，表示 $\lang a,b\rang$ 是 key road。

请注意：输出时，所有的数对 $\lang a,b\rang$ 必须按照 $a$ 从小到大排序输出；如果$a$ 相同，则根据 $b$ 从小到大排序。

## 样例

### 样例输入 #1
```
6 6
1 2
2 3
2 4
3 5
4 5
5 6
```
### 样例输出 #1
```
1 2
5 6
```


---

---
title: "[USACO05FEB] Part Acquisition S"
layout: "post"
diff: 普及/提高-
pid: P1673
tag: ['2005', 'USACO', '最短路']
---
# [USACO05FEB] Part Acquisition S
## 题目描述

奶牛们接到了寻找一种新型挤奶机的任务，为此它们准备依次经过 $N(1\le N\le 5\times 10^4)$ 颗行星，在行星上进行交易。为了方便，奶牛们已经给可能出现的 $K(1\le K\le 10^3)$ 种货物进行了由 $1$ 到 $K$ 的标号。由于这些行星都不是十分发达。没有流通的货币，所以在每个市场里都只能用固定的一种货物去换取另一种货物。奶牛们带着一种上好的饲料从地球出发，希望在使用的物品的种类数量最少的情况下，最终得到所需要的机器。饲料的标号为 $1$，所需要的机器的标号为 $K$。如果任务无法完成，输出 $-1$。
## 输入格式

第 $1$ 行是两个数字 $N$ 和 $K$。

第 $2$ 到 $N+1$ 行，每行是两个数字 $A_i$ 和 $B_i$，表示第 $i$ 颗行星为得到 $A_i$ 愿意提供 $B_i$。
## 输出格式

输出最少经手物品数。
## 样例

### 样例输入 #1
```
6 5
1 3
3 2
2 3
3 1
2 5
5 4
```
### 样例输出 #1
```
4
```
## 提示

奶牛们至少需要 $4$ 种不同标号的物品，先用 $1$ 去交换 $3$，再用 $3$ 去交换 $2$，最后用 $2$ 交换得到 $5$。

$1\le N\le 5\times 10^4$，$1\le K\le 10^3$。


---

---
title: "贪婪的Copy"
layout: "post"
diff: 普及/提高-
pid: P1690
tag: ['搜索', '枚举', '最短路']
---
# 贪婪的Copy
## 题目描述

Copy 从卢牛那里听说在一片叫 yz 的神的领域埋藏着不少宝藏，于是 Copy 来到了这个被划分为 $n$ 个区域的神地。卢牛告诉了Copy这里共有 $n$ 个宝藏，分别放在第 $P_i$ 个 $(1\le P_i\le N)$ 区域。Copy还得知了每个区域之间的距离。现在 Copy 从 $1$ 号区域出发，要获得所有的宝藏并到 $n$ 号区域离开。Copy 很懒，只好来找你为他寻找一条合适的线路，使得他走过的距离最短。

## 输入格式

第一行一个正整数 $N(1\le N\le 100)$

接下来一个 $N\times N$ 的矩阵，第 $i+1$ 行第 $j$ 列的数字表示区域 $i,j$ 之间的距离。每个距离用空格隔开，距离保证 $i\to j\le 1000$。请注意的 $i \to j$ 距离并不一定等于 $j \to i$ 的距离。

第 $N+2$ 行一个整数 $P(0\le P\le 10)$。

第 $N+3$ 行共 $P$ 个用空格隔开的整数，表示有宝藏的区域编号。

## 输出格式

一个整数，为 Copy 获得全部宝藏需要的最短距离。数据保证答案小于等于 maxlongint。

## 样例

### 样例输入 #1
```
2
0 4
5 0
2
1 2

```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
3
0 2 6
1 0 4
7 10 0
1
2

```
### 样例输出 #2
```
6

```
## 提示

- 对 $30\%$ 的数据，$1\le n\le 15$，其余如题所述。
- 对 $100\%$ 的数据，全部数据范围如题所述。



---

---
title: "采购特价商品"
layout: "post"
diff: 普及/提高-
pid: P1744
tag: ['图论', '最短路', '队列']
---
# 采购特价商品
## 题目背景

《爱与愁的故事第三弹·shopping》第一章。
## 题目描述

中山路店山店海，成了购物狂爱与愁大神的“不归之路”。中山路上有 $n$（$n \leq 100$）家店，每家店的坐标均在 $-10000$ 至 $10000$ 之间。其中的 $m$ 家店之间有通路。若有通路，则表示可以从一家店走到另一家店，通路的距离为两点间的直线距离。现在爱与愁大神要找出从一家店到另一家店之间的最短距离。你能帮爱与愁大神算出吗？
## 输入格式

共 $n+m+3$ 行：

第一行：整数 $n$。 

接下来 $n$ 行：每行两个整数 $x$ 和 $y$，描述了一家店的坐标。 

接下来一行：整数 $m$。 

接下来 $m$ 行：每行描述一条通路，由两个整数 $i$ 和 $j$ 组成，表示第 $i$ 家店和第 $j$ 家店之间有通路。

接下来一行：两个整数 $s$ 和 $t$，分别表示原点和目标店。 
## 输出格式

仅一行：一个实数（保留两位小数），表示从 $s$ 到 $t$ 的最短路径长度。
## 样例

### 样例输入 #1
```
5

0 0

2 0

2 2

0 2

3 1

5

1 2

1 3

1 4

2 5

3 5

1 5
```
### 样例输出 #1
```
3.41
```
## 提示

对于 $100 \%$ 的数据：$2 \le n \leq 100$，$1 \le i, j, s, t \le n$，$1 \le m \leq 1000$。 


---

---
title: "[USACO07FEB] Cow Party S"
layout: "post"
diff: 普及/提高-
pid: P1821
tag: ['图论', '2007', 'USACO', 'O2优化', '最短路']
---
# [USACO07FEB] Cow Party S
## 题目描述

寒假到了，$n$ 头牛都要去参加一场在编号为 $x$ 的牛的农场举行的派对，农场之间有 $m$ 条有向路，每条路都有一定的长度。

每头牛参加完派对后都必须回家，无论是去参加派对还是回家，每头牛都会选择最短路径，求这 $n$ 头牛的最短路径（一个来回）中最长的一条路径长度。

## 输入格式

第一行有三个整数，分别表示牛的数量 $n$，道路数 $m$ 和派对农场编号 $x$。  
接下来 $m$ 行，每行三个整数 $u, v, w$，表示存在一条由 $u$ 通向 $v$ 的长度为 $w$ 的道路。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3

```
### 样例输出 #1
```
10
```
## 提示

### 样例 1 解释
![](https://cdn.luogu.com.cn/upload/image_hosting/rl3com2y.png)

### 数据规模与约定

对于全部的测试点，保证 $1 \leq x \leq n \leq 10^3$，$1 \leq m \leq 10^5$，$1 \leq u,v \leq n$，$1 \leq w \leq 10^2$，保证从任何一个结点出发都能到达 $x$ 号结点，且从 $x$ 出发可以到达其他所有节点。


---

---
title: "[USACO11OPEN] Corn Maze S"
layout: "post"
diff: 普及/提高-
pid: P1825
tag: ['模拟', '搜索', '2011', 'USACO', '广度优先搜索 BFS', '最短路']
---
# [USACO11OPEN] Corn Maze S
## 题目描述

This past fall, Farmer John took the cows to visit a corn maze. But this wasn't just any corn maze: it featured several gravity-powered teleporter slides, which cause cows to teleport instantly from one point in the maze to another. The slides work in both directions: a cow can slide from the slide's start to the end instantly, or from the end to the start. If a cow steps on a space that hosts either end of a slide, she must use the slide.

The outside of the corn maze is entirely corn except for a single exit.

The maze can be represented by an N x M (2 <= N <= 300; 2 <= M <= 300) grid. Each grid element contains one of these items:

\* Corn (corn grid elements are impassable) 

\* Grass (easy to pass through!) 

\* A slide endpoint (which will transport a cow to the other endpoint) 

\* The exit

A cow can only move from one space to the next if they are adjacent and neither contains corn. Each grassy space has four potential neighbors to which a cow can travel. It takes 1 unit of time to move from a grassy space to an adjacent space; it takes 0 units of time to move from one slide endpoint to the other.

Corn-filled spaces are denoted with an octothorpe (#). Grassy spaces are denoted with a period (.). Pairs of slide endpoints are denoted with the same uppercase letter (A-Z), and no two different slides have endpoints denoted with the same letter. The exit is denoted with the equals sign (=).

Bessie got lost. She knows where she is on the grid, and marked her current grassy space with the 'at' symbol (@). What is the minimum time she needs to move to the exit space?

## 输入格式

第一行：两个用空格隔开的整数 $N$ 和 $M$。

第 $2\sim N+1$ 行：第 $i+1$ 行描述了迷宫中的第 $i$ 行的情况（共有$M$个字符，每个字符中间没有空格）。
## 输出格式

一个整数，表示起点到出口所需的最短时间。
## 样例

### 样例输入 #1
```
5 6
###=##
#.W.##
#.####
#.@W##
######

```
### 样例输出 #1
```
3
```
## 提示

例如以下矩阵，$N=5,M=6$。

```plain
###=##
#.W.##
#.####
#.@W##
######
```

唯一的一个装置的结点用大写字母 $\tt{W}$ 表示。

最优方案为：先向右走到装置的结点，花费一个单位时间，再到装置的另一个结点上，花费 $0$ 个单位时间，然后再向右走一个，再向上走一个，到达出口处，总共花费了 $3$ 个单位时间。
## 题目翻译

奶牛们去一个 $N\times M$ 玉米迷宫，$2 \leq N \leq 300,2 \leq M \leq300$。

迷宫里有一些传送装置，可以将奶牛从一点到另一点进行瞬间转移。这些装置可以双向使用。

如果一头奶牛处在这个装置的起点或者终点，这头奶牛就必须使用这个装置，奶牛在传送过后不会立刻进行第二次传送，即不会卡在传送装置的起点和终点之间来回传送。

玉米迷宫除了唯一的一个出口都被玉米包围。

迷宫中的每个元素都由以下项目中的一项组成：

1. 玉米，`#` 表示，这些格子是不可以通过的。
1. 草地，`.` 表示，可以简单的通过。
1. 传送装置，每一对大写字母 $\tt{A}$ 到 $\tt{Z}$ 表示。
1. 出口，`=` 表示。
1. 起点， `@` 表示

奶牛能在一格草地上可能存在的四个相邻的格子移动，花费 $1$ 个单位时间。从装置的一个结点到另一个结点不花时间。


---

---
title: "[USACO09NOV] Job Hunt S"
layout: "post"
diff: 普及/提高-
pid: P1938
tag: ['图论', '2009', 'USACO', '最短路']
---
# [USACO09NOV] Job Hunt S
## 题目描述

Bessie is running out of money and is searching for jobs. Farmer John knows this and wants the cows to travel around so he has imposed a rule that his cows can only make D (1 <= D <= 1,000) dollars in a city before they must work in another city. Bessie can, however, return to a city after working elsewhere for a while and again earn the D dollars maximum in that city. There is no limit on the number of times Bessie can do this.

Bessie's world comprises P (1 <= P <= 150) one-way paths connecting C (2 <= C <= 220) cities conveniently numbered 1..C. Bessie is currently in city S (1 <= S <= C). Path i runs one-way from city A\_i to city B\_i (1 <= A\_i <= C; 1 <= B\_i <= C) and costs nothing to traverse.

To help Bessie, Farmer John will give her access to his private jet service. This service features F (1 <= F <= 350) routes, each of which is a one way flight from one city J\_i to a another K\_i (1 <= J\_i <= C; 1 <= K\_i <= C) and which costs T\_i (1 <= T\_i <= 50,000) dollars. Bessie can pay for the tickets from future earnings if she doesn't have the cash on hand.

Bessie can opt to retire whenever and wherever she wants. Given an unlimited amount of time, what is the most money that Bessie can make presuming she can make the full D dollars in each city she can travel to?  Print -1 if there is no limit to this amount.

奶牛们正在找工作。农场主约翰知道后，鼓励奶牛们四处碰碰运气。而且他还加了一条要求：一头牛在一个城市最多只能赚D（1≤D≤1000）美元，然后它必须到另一座城市工作。当然，它可以在别处工作一阵子后又回到原来的城市再最多赚D美元。而且这样的往返次数没有限制。

城市间有P（1≤P≤150）条单向路径连接，共有C（2≤C≤220）座城市，编号从1到C。奶牛贝茜当前处在城市S（1≤S≤C）。路径i从城市A\_i到城市B\_i（1≤A\_i≤C，1≤B\_i≤C），在路径上行走不用任何花费。

为了帮助贝茜，约翰让它使用他的私人飞机服务。这项服务有F条（1≤F≤350）单向航线，每条航线是从城市J\_i飞到另一座城市K\_i（1≤J\_i≤C，1≤K\_i≤C），费用是T\_i（1≤T\_i≤50000）美元。如果贝茜手中没有现钱，可以用以后赚的钱来付机票钱。

贝茜可以选择在任何时候，在任何城市退休。如果在工作时间上不做限制，贝茜总共可以赚多少钱呢？如果赚的钱也不会出现限制，就输出-1。

## 输入格式

第一行：5个用空格分开的整数D，P，C，F，S。

第2到第P+1行：第i+1行包含2个用空格分开的整数，表示一条从城市A\_i到城市B\_i的单向路径。

接下来F行，每行3个用空格分开的整数，表示一条从城市J\_i到城市K\_i的单向航线，费用是T\_i。

## 输出格式

一个整数，在上述规则下最多可以赚到的钱数。

## 样例

### 样例输入 #1
```
100 3 5 2 1
1 5
2 3
1 4
5 2 150
2 5 120

```
### 样例输出 #1
```
250
```
## 提示

This world has five cities, three paths and two jet routes. Bessie starts out in city 1, and she can only make 100 dollars in each city before moving on.


Bessie can travel from city 1 to city 5 to city 2 to city 3, and make a total of 4\*100 - 150 = 250 dollars.


Source: USACO 2009 November Silver

这个世界上有五个城市，三条单向路径和两条单向航线。贝茜从一号城市开始她的旅行，她在离开一个城市前最多只能在这个城市赚100美元。


贝茜可以通过从一号城市-->五号城市-->二号城市-->三号城市的旅行赚到4\*100-150=250美元。


(注:在四个城市各赚100美元,从五号城市飞到二号城市花掉150美元)


来源:USACO 2009 十一月银组



---

---
title: "[HNOI2004] 打鼹鼠"
layout: "post"
diff: 普及/提高-
pid: P2285
tag: ['动态规划 DP', '递推', '2004', '各省省选', '湖南', '最短路']
---
# [HNOI2004] 打鼹鼠
## 题目描述

鼹鼠是一种很喜欢挖洞的动物，但每过一定的时间，它还是喜欢把头探出到地面上来透透气的。根据这个特点阿牛编写了一个打鼹鼠的游戏：在一个 $n \times n$ 的网格中，在某些时刻鼹鼠会在某一个网格探出头来透透气。你可以控制一个机器人来打鼹鼠，如果 $i$ 时刻鼹鼠在某个网格中出现，而机器人也处于同一网格的话，那么这个鼹鼠就会被机器人打死。而机器人每一时刻只能够移动一格或停留在原地不动。机器人的移动是指从当前所处的网格移向相邻的网格，即从坐标为 $(i, j)$ 的网格移向 $(i-1, j), (i+1, j), (i, j-1), (i, j+1)$ 四个网格，机器人不能走出整个 $n \times n$ 的网格。游戏开始时，你可以自由选定机器人的初始位置。

现在知道在一段时间内，鼹鼠出现的时间和地点，请编写一个程序使机器人在这一段时间内打死尽可能多的鼹鼠。

## 输入格式

第一行为 $n, m$（$n \le 1000$，$m \le {10}^4$），其中 $m$ 表示在这一段时间内出现的鼹鼠的个数，接下来的 $m$ 行中每行有三个数据 $\mathit{time}, x, y$ 表示在游戏开始后 $\mathit{time}$ 个时刻，在第 $x$ 行第 $y$ 个网格里出现了一只鼹鼠。$\mathit{time}$ 按递增的顺序给出。注意同一时刻可能出现多只鼹鼠，但同一时刻同一地点只可能出现一只鼹鼠。
## 输出格式

仅包含一个正整数，表示被打死鼹鼠的最大数目。
## 样例

### 样例输入 #1
```
2 2	         

1 1 1		

2 2 2


```
### 样例输出 #1
```
1

```


---

---
title: "Mzc和体委的争夺战"
layout: "post"
diff: 普及/提高-
pid: P2299
tag: ['图论', '贪心', '最短路']
---
# Mzc和体委的争夺战
## 题目背景

mzc 与 djn 第四弹。

## 题目描述

mzc 家很有钱（开玩笑），他家有 $n$ 个男家丁（做过前三弹的都知道）。但如此之多的男家丁吸引来了我们的体委（矮胖小伙），他要来与 mzc 争夺男家丁。

mzc 很生气，决定与其决斗，但 cat 的体力确实有些不稳定，所以他需要你来帮他计算一下最短需要的时间。

## 输入格式

第一行有两个数 $n,m.n$ 表示有 $n$ 个停留站，m表示共有m条路。

之后 $m$ 行，每行三个数 $a_i,b_i,c_i$，表示第 $a_i$ 个停留站到第 $b_i$ 个停留站需要 $c_i$ 的时间。注意，这是双向的。也就是说，从 $b_i$ 个停留站到第 $a_i$ 个停留站也需要 $c_i$ 的时间。

## 输出格式

一行，输出 $1$ 到 $n$ 最短时间。

## 样例

### 样例输入 #1
```
5 8
1 2 3
2 3 4
3 4 5
4 5 6
1 3 4
2 4 7
2 5 8
1 5 100

```
### 样例输出 #1
```
11
```
## 提示

$1\le n \leq 2500$，$1\le m \leq 2\times10^5$，$1\le c_i\le 10^6$。

由于 mzc 大大十分着急，所以他只能等待 1s。



---

---
title: "关灯问题II"
layout: "post"
diff: 普及/提高-
pid: P2622
tag: ['最短路', '状压 DP']
---
# 关灯问题II
## 题目描述

现有 $n$ 盏灯，以及 $m$ 个按钮。每个按钮可以同时控制这 $n$ 盏灯——按下了第 $i$ 个按钮，对于所有的灯都有一个效果。按下 $i$ 按钮对于第 $j$ 盏灯，是下面 $3$ 中效果之一：如果 $a_{i,j}$ 为 $1$，那么当这盏灯开了的时候，把它关上，否则不管；如果为 $-1$ 的话，如果这盏灯是关的，那么把它打开，否则也不管；如果是 $0$，无论这灯是否开，都不管。

现在这些灯都是开的，给出所有开关对所有灯的控制效果，求问最少要按几下按钮才能全部关掉。
## 输入格式

前两行两个数，$n, m$。

接下来 $m$ 行，每行 $n$ 个数 $,a_{i, j}$ 表示第 $i$ 个开关对第 $j$ 个灯的效果。
## 输出格式

一个整数，表示最少按按钮次数。如果没有任何办法使其全部关闭，输出 $-1$。
## 样例

### 样例输入 #1
```
3
2
1 0 1
-1 1 0
```
### 样例输出 #1
```
2
```
## 提示

### 数据范围及约定

- 对于 $20\%$ 数据，输出无解可以得分。
- 对于 $20\%$ 数据，$n \le 5$。
- 对于 $20\%$ 数据，$m \le 20$。

上面的数据点可能会重叠。

对于 $100\%$ 数据 $n \le 10,m \le 100$。


---

---
title: "[USACO07NOV] Cow Hurdles S"
layout: "post"
diff: 普及/提高-
pid: P2888
tag: ['2007', 'USACO', '最短路']
---
# [USACO07NOV] Cow Hurdles S
## 题目描述

Farmer John wants the cows to prepare for the county jumping competition, so Bessie and the gang are practicing jumping over hurdles. They are getting tired, though, so they want to be able to use as little energy as possible to jump over the hurdles.

Obviously, it is not very difficult for a cow to jump over several very short hurdles, but one tall hurdle can be very stressful. Thus, the cows are only concerned about the height of the tallest hurdle they have to jump over.

The cows' practice room has $N$ stations, conveniently labeled $1,\dots,N$. A set of $M$ one-way paths connects pairs of stations; the paths are also conveniently labeled $1,\dots,M$. Path $i$ travels from station $S_i$ to station $E_i$ and contains exactly one hurdle of height $H_i$. Cows must jump hurdles in any path they traverse.

The cows have $T$ tasks to complete. Task $i$ comprises two distinct numbers, $A_i$ and $B_i$, which connote that a cow has to travel from station $A_i$ to station $B_i$ (by traversing over one or more paths over some route). The cows want to take a path the minimizes the height of the tallest hurdle they jump over when traveling from $A_i$ to $B_i$ . Your job is to write a program that determines the path whose tallest hurdle is smallest and report that height.


Farmer John 想让她的奶牛准备郡级跳跃比赛，Bessie 和她的伙伴们正在练习跨栏。她们很累，所以她们想消耗最少的能量来跨栏。 显然，对于一头奶牛跳过几个矮栏是很容易的，但是高栏却很难。于是，奶牛们总是关心路径上最高的栏的高度。 

奶牛的训练场中有 $N$ 个站台，分别标记为 $1,\dots,N$。所有站台之间有 $M$ 条单向路径，第 $i$ 条路经是从站台 $S_i$ 开始，到站台 $E_i$，其中最高的栏的高度为 $H_i$。无论如何跑，奶牛们都要跨栏。 

奶牛们有 $T$ 个训练任务要完成。第 $i$ 个任务包含两个数字 $A_i$ 和 $B_i$，表示奶牛必须从站台 $A_i$ 跑到站台 $B_i$，可以路过别的站台。奶牛们想找一条路径从站台 $A_i$ 到站台 $B_i$，使路径上最高的栏的高度最小。 你的任务就是写一个程序，计算出路径上最高的栏的高度的最小值。

## 输入格式

\* Line $1$: Three space-separated integers: $N$, $M$, and $T$

\* Lines $2,\dots,M+1$: Line $i+1$ contains three space-separated integers: $S_i$ , $E_i$ , and $H_i$

\* Lines $M+2,\dots,M+T+1$: Line $i+M+1$ contains two space-separated integers that describe task $i$: $A_i$ and $B_i$


第一行：三个空格隔开的整数 $N, M, T$。

接下来 $M$ 行：第 $i$ 行包含三个空格隔开的整数 $S_i, E_i, H_i$。

接下来 $T$ 行：第 $i$ 行包含两个空格隔开的整数，表示任务 $i$ 的起始站台和目标站台 $A_i, B_i$。

## 输出格式

\* Lines $1,\dots,T$: Line $i$ contains the result for task $i$ and tells the smallest possible maximum height necessary to travel between the stations. Output `-1` if it is impossible to travel between the two stations.

$T$ 行：第 $i$ 行为一个整数，表示任务 $i$ 路径上最高的栏的高度的最小值。如果无法到达，输出 `-1`。
## 样例

### 样例输入 #1
```
5 6 3
1 2 12
3 2 8
1 3 5
2 5 3
3 4 4
2 4 8
3 4
1 2
5 1

```
### 样例输出 #1
```
4
8
-1

```
## 提示

对于 $100\%$ 的数据，$1 \le N \le 300$，$1 \le M \le 2.5 \times 10^4$，$1 \le H_i \le 1 \times 10^6$，$1 \le T \le 4 \times 10^4$，$1 \le A_i,B_i \le N$。

感谢 @gaozhiyong @_Cppsteve_ 提供翻译



---

---
title: "[USACO08OPEN] Clear And Present Danger S"
layout: "post"
diff: 普及/提高-
pid: P2910
tag: ['2008', 'USACO', '最短路']
---
# [USACO08OPEN] Clear And Present Danger S
## 题目描述

Farmer John is on a boat seeking fabled treasure on one of the N (1 <= N <= 100) islands conveniently labeled 1..N in the Cowribbean Sea.

The treasure map tells him that he must travel through a certain sequence A\_1, A\_2, ..., A\_M of M (2 <= M <= 10,000) islands, starting on island 1 and ending on island N before the treasure will appear to him. He can visit these and other islands out of order and even more than once, but his trip must include the A\_i sequence in the order specified by the map.

FJ wants to avoid pirates and knows the pirate-danger rating (0 <= danger <= 100,000) between each pair of islands. The total danger rating of his mission is the sum of the danger ratings of all the paths he traverses.

Help Farmer John find the least dangerous route to the treasure that satisfies the treasure map's requirement.

## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..M+1: Line i+1 describes the i\_th island FJ must visit with a single integer: A\_i

\* Lines M+2..N+M+1: Line i+M+1 contains N space-separated integers that are the respective danger rating of the path between island i and islands 1, 2, ..., and N, respectively. The ith integer is always zero.

## 输出格式

\* Line 1: The minimum danger that Farmer John can encounter while obtaining the treasure.

## 样例

### 样例输入 #1
```
3 4 
1 
2 
1 
3 
0 5 1 
5 0 2 
1 2 0 

```
### 样例输出 #1
```
7 

```
## 提示

There are 3 islands and the treasure map requires Farmer John to visit a sequence of 4 islands in order: island 1, island 2, island 1 again, and finally island 3. The danger ratings of the paths are given: the paths (1, 2); (2, 3); (3, 1) and the reverse paths have danger ratings of 5, 2, and 1, respectively.


He can get the treasure with a total danger of 7 by traveling in the sequence of islands 1, 3, 2, 3, 1, and 3. The cow map's requirement (1, 2, 1, and 3) is satisfied by this route. We avoid the path between islands 1 and 2 because it has a large danger rating.

输入输出格式


输入格式：


第一行：两个用空格隔开的正整数N和M


第二到第M+1行：第i+1行用一个整数Ai表示FJ必须经过的第i个岛屿


第M+2到第N+M+1行：第i+M+1行包含N个用空格隔开的非负整数分别表示i号小岛到第1...N号小岛的航线各自的危险指数。保证第i个数是0。

输出格式


第一行：FJ在找到宝藏的前提下经过的航线的危险指数之和的最小值。

说明

这组数据中有三个岛屿，藏宝图要求FJ按顺序经过四个岛屿：1号岛屿、2号岛屿、回到1号岛屿、最后到3号岛屿。每条航线的危险指数也给出了：航路(1，2)、(2，3)、(3，1)和它们的反向路径的危险指数分别是5、2、1。


FJ可以通过依次经过1、3、2、3、1、3号岛屿以7的最小总危险指数获得宝藏。这条道路满足了奶牛地图的要求（1，2，1，3）。我们避开了1号和2号岛屿之间的航线，因为它的危险指数太大了。


注意：测试数据中a到b的危险指数不一定等于b到a的危险指数！

## 题目翻译

农夫约翰正驾驶一条小艇在牛勒比海上航行．

海上有 $N(1\leq N\leq 100)$ 个岛屿，用 $1$ 到 $N$ 编号．约翰从 $1$ 号小岛出发，最后到达 $N$ 号小岛．

一张藏宝图上说，如果他的路程上经过的小岛依次出现了  $A_1,A_2,\dots ,A_M(2\leq M\leq 10000)$ 这样的序列（不一定相邻），那他最终就能找到古老的宝藏． 但是，由于牛勒比海有海盗出没．约翰知道任意两个岛屿之间的航线上海盗出没的概率，他用一个危险指数 $D_{i,j}(0\leq D_{i,j}\leq 100000)$ 来描述．他希望他的寻宝活动经过的航线危险指数之和最小．那么，在找到宝藏的前提下，这个最小的危险指数是多少呢？

输入输出格式

输入格式：

第一行：两个用空格隔开的正整数 $N$ 和 $M$。

第二到第 $M+1$ 行：第 $i+1$ 行用一个整数 $A_i$ 表示 FJ 必须经过的第 $i$ 个岛屿

第 $M+2$ 到第 $N+M+1$ 行：第 $i+M+1$ 行包含 $N$ 个用空格隔开的非负整数分别表示 $i$ 号小岛到第 $1\dots N$ 号小岛的航线各自的危险指数。保证第 $i$ 个数是 $0$。

输出格式
第一行：FJ 在找到宝藏的前提下经过的航线的危险指数之和的最小值。

说明
这组数据中有三个岛屿，藏宝图要求 FJ 按顺序经过四个岛屿：$1$ 号岛屿、$2$ 号岛屿、回到 $1$ 号岛屿、最后到 $3$ 号岛屿。每条航线的危险指数也给出了：航路$(1,2),(2,3),(3,1)$ 和它们的反向路径的危险指数分别是 $5,2,1$。

FJ 可以通过依次经过 $1,3,2,3,1,3$ 号岛屿以 $7$ 的最小总危险指数获得宝藏。这条道路满足了奶牛地图的要求 $(1,2,1,3)$。我们避开了 $1$ 号和 $2$ 号岛屿之间的航线，因为它的危险指数太大了。

注意：测试数据中 $a$ 到 $b$ 的危险指数不一定等于 $b$ 到 $a$ 的危险指数！

Translated by @LJC00125 


---

---
title: "[USACO09JAN] Best Spot S"
layout: "post"
diff: 普及/提高-
pid: P2935
tag: ['2009', 'USACO', '枚举', '最短路']
---
# [USACO09JAN] Best Spot S
## 题目描述

Bessie, always wishing to optimize her life, has realized that she really enjoys visiting F (1 <= F <= P) favorite pastures F\_i of the P (1 <= P <= 500; 1 <= F\_i <= P) total pastures (conveniently

numbered 1..P) that compose Farmer John's holdings.

Bessie knows that she can navigate the C (1 <= C <= 8,000) bidirectional cowpaths (conveniently numbered 1..C) that connect various pastures to travel to any pasture on the entire farm. Associated with each path P\_i is a time T\_i (1 <= T\_i <= 892) to traverse that path (in either direction) and two path endpoints a\_i and b\_i (1 <= a\_i <= P; 1 <= b\_i <= P).

Bessie wants to find the number of the best pasture to sleep in so that when she awakes, the average time to travel to any of her F favorite pastures is minimized.

By way of example, consider a farm laid out as the map below shows, where \*'d pasture numbers are favorites. The bracketed numbers are times to traverse the cowpaths.

```cpp

            1*--[4]--2--[2]--3
                     |       |
                    [3]     [4]
                     |       |
                     4--[3]--5--[1]---6---[6]---7--[7]--8*
                     |       |        |         |
                    [3]     [2]      [1]       [3]
                     |       |        |         |
                    13*      9--[3]--10*--[1]--11*--[3]--12*
```
The following table shows distances for potential 'best place' of pastures 4, 5, 6, 7, 9, 10, 11, and 12:

```cpp
      * * * * * * Favorites * * * * * *
 Potential      Pasture Pasture Pasture Pasture Pasture Pasture     Average
Best Pasture       1       8      10      11      12      13        Distance
------------      --      --      --      --      --      --      -----------
    4              7      16       5       6       9       3      46/6 = 7.67
    5             10      13       2       3       6       6      40/6 = 6.67
    6             11      12       1       2       5       7      38/6 = 6.33
    7             16       7       4       3       6      12      48/6 = 8.00
    9             12      14       3       4       7       8      48/6 = 8.00
   10             12      11       0       1       4       8      36/6 = 6.00 ** BEST
   11             13      10       1       0       3       9      36/6 = 6.00
   12             16      13       4       3       0      12      48/6 = 8.00

```
Thus, presuming these choices were the best ones (a program would have to check all of them somehow), the best place to sleep is pasture 10.

约翰拥有 $P(1 \leq P \leq 500)$ 个牧场，贝茜特别喜欢其中的 $F$ 个。所有的牧场由 $C(1 < C \leq 8000)$条双向路连接，第 $i$ 条路连接着 $a_i,b_i$，需要 $T_i(1 \leq T_i < 892)$ 个单位时间来通过。

作为一只总想优化自己生活方式的奶牛，贝茜喜欢自己某一天醒来，到达所有那 $F$ 个她喜欢的牧场的平均需时最小。那她前一天应该睡在哪个牧场呢？请帮助贝茜找到这个最佳牧场。

由样例解释可见，在样例环境下，牧场 $10$ 到所有贝茜喜欢的牧场的平均距离最小，为最佳牧场。

## 输入格式

\* Line 1: Three space-separated integers: P, F, and C

\* Lines 2..F+1: Line i+2 contains a single integer: F\_i

\* Lines F+2..C+F+1: Line i+F+1 describes cowpath i with three

space-separated integers: a\_i, b\_i, and T\_i

## 输出格式

\* Line 1: A single line with a single integer that is the best pasture in which to sleep. If more than one pasture is best, choose the smallest one.

## 样例

### 样例输入 #1
```
13 6 15 
11 
13 
10 
12 
8 
1 
2 4 3 
7 11 3 
10 11 1 
4 13 3 
9 10 3 
2 3 2 
3 5 4 
5 9 2 
6 7 6 
5 6 1 
1 2 4 
4 5 3 
11 12 3 
6 10 1 
7 8 7 

```
### 样例输出 #1
```
10 

```
## 提示

As the problem statement


As the problem statement.



---

---
title: "[USACO09OPEN] Hide and Seek S"
layout: "post"
diff: 普及/提高-
pid: P2951
tag: ['2009', 'USACO', '最短路']
---
# [USACO09OPEN] Hide and Seek S
## 题目描述

Bessie is playing hide and seek (a game in which a number of players hide and a single player (the seeker) attempts to find them after which various penalties and rewards are assessed; much fun usually ensues).

She is trying to figure out in which of N (2 <= N <= 20,000) barns conveniently numbered 1..N she should hide. She knows that FJ (the seeker) starts out in barn 1. All the barns are connected by M (1 <= M <= 50,000) bidirectional paths with endpoints A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i); it is possible to reach any barn from any other through the paths.

Bessie decides that it will be safest to hide in the barn that has the greatest distance from barn 1 (the distance between two barns is the smallest number of paths that one must traverse to get from one to the other). Help Bessie figure out the best barn in which to hide.

奶牛贝西和农夫约翰（FJ）玩捉迷藏，现在有N个谷仓，FJ开始在第一个谷仓，贝西为了不让FJ找到她，当然要藏在距离第一个谷仓最远的那个谷仓了。现在告诉你N个谷仓，和M个两两谷仓间的“无向边”。每两个仓谷间当然会有最短路径，现在要求距离第一个谷仓（FJ那里）最远的谷仓是哪个（所谓最远就是距离第一个谷仓最大的最短路径）？如有多个则输出编号最小的。以及求这最远距离是多少，和有几个这样的谷仓距离第一个谷仓那么远。

## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..M+1: Line i+1 contains the endpoints for path i: A\_i and B\_i

第一行：两个整数N,M；


第2-M+1行：每行两个整数，表示端点A\_i 和 B\_i 间有一条无向边。

## 输出格式

\* Line 1: On a single line, print three space-separated integers: the index of the barn farthest from barn 1 (if there are multiple such barns, print the smallest such index), the smallest number of paths needed to reach this barn from barn 1, and the number of barns with this number of paths.

仅一行，三个整数，两两中间空格隔开。表示：距离第一个谷仓最远的谷仓编号（如有多个则输出编号最小的。），以及最远的距离，和有几个谷仓距离第一个谷仓那么远。

## 样例

### 样例输入 #1
```
6 7 
3 6 
4 3 
3 2 
1 3 
1 2 
2 4 
5 2 

```
### 样例输出 #1
```
4 2 3 

```
## 提示

The farm layout is as follows:

 ![](https://cdn.luogu.com.cn/upload/pic/2815.png) 

Barns 4, 5, and 6 are all a distance of 2 from barn 1. We choose barn 4 because it has the smallest index.



这里谷仓4，5，6距离1号谷仓都是2，但是4编号最小所以输出4.因此最远距离是2且有3个谷仓，依次输出：2和3。 

感谢 wjcwinmt 的贡献翻译



---

---
title: "[USACO10FEB] Chocolate Giving S"
layout: "post"
diff: 普及/提高-
pid: P2984
tag: ['贪心', '2010', 'USACO', '最短路']
---
# [USACO10FEB] Chocolate Giving S
## 题目描述

Farmer John is distributing chocolates at the barn for Valentine's day, and B (1 <= B <= 25,000) of his bulls have a special cow in mind to receive a chocolate gift.

Each of the bulls and cows is grazing alone in one of the farm's N (2\*B <= N <= 50,000) pastures conveniently numbered 1..N and connected by M (N-1 <= M <= 100,000) bidirectional cowpaths of various lengths. Some pastures might be directly connected by more than one cowpath. Cowpath i connects pastures R\_i and S\_i (1 <= R\_i <= N; 1 <= S\_i <= N) and has length L\_i (1 <= L\_i <= 2,000).

Bull i resides in pasture P\_i (1 <= P\_i <= N) and wishes to give a chocolate to the cow in pasture Q\_i (1 <= Q\_i <= N).

Help the bulls find the shortest path from their current pasture to the barn (which is located at pasture 1) and then onward to the pasture where their special cow is grazing. The barn connects, one way or another (potentially via other cowpaths and pastures) to every pasture.

As an example, consider a farm with 6 pastures, 6 paths, and 3 bulls (in pastures 2, 3, and 5) who wish to bestow chocolates on their love-objects:

```cpp

                      *1  <-- Bull wants chocolates for pasture 1 cow
             [4]--3--[5]  <-- [5] is the pasture ID
            /  |
           /   |
          4    2          <-- 2 is the cowpath length
         /     |               between [3] and [4]
      [1]--1--[3]*6
     /   \    /
    9     3  2
   /       \/
 [6]      [2]*4
```
\* The Bull in pasture 2 can travel distance 3 (two different ways) to get to the barn then travel distance 2+1 to pastures [3] and [4] to gift his chocolate. That's 6 altogether.

\* The Bull in pasture 5 can travel to pasture 4 (distance 3), then pastures 3 and 1 (total: 3 + 2 + 1 = 6) to bestow his chocolate offer.

\* The Bull in pasture 3 can travel distance 1 to pasture 1 and then take his chocolate 9 more to pasture 6, a total distance of 10.
## 输入格式

\* Line 1: Three space separated integers: N, M, and B

\* Lines 2..M+1: Line i+1 describes cowpath i with three

space-separated integers: R\_i, S\_i, and L\_i

\* Lines M+2..M+B+1: Line M+i+1 contains two space separated integers: P\_i and Q\_i

## 输出格式

\* Lines 1..B: Line i should contain a single integer, the smallest distance that the bull in pasture P\_i must travel to get chocolates from the barn and then award them to the cow of his dreams in pasture Q\_i

## 样例

### 样例输入 #1
```
6 7 3 
1 2 3 
5 4 3 
3 1 1 
6 1 9 
3 4 2 
1 4 4 
3 2 2 
2 4 
5 1 
3 6 

```
### 样例输出 #1
```
6 
6 
10 

```
## 题目翻译

### 题目描述

FJ 有 $B$ 头奶牛 $(1\le B\le 25000)$，有 $N(2\times B\le N\le 50000)$ 个农场，编号 $1$ 到 $N$，有 $M(N-1\le M\le 100000)$ 条双向边，第 $i$ 条边连接农场 $R_i$ 和 $S_i(1\le R_i\le N, 1\le S_i\le N)$，该边的长度是 $L_i(1\le L_i\le 2000)$。居住在农场 $P_i$ 的奶牛 A $(1\le P_i\le N)$，想送一份新年礼物给居住在农场 $Q_i(1\le Q_i\le N)$ 的奶牛 B，但是奶牛 A 必须先到 FJ（居住在编号 $1$ 的农场）那里取礼物，然后再送给奶牛 B。你的任务是：奶牛 A 至少需要走多远的路程？

### 输入格式
* 第一行三个整数 $N,M,B$。
* 第 $2$ 至 $M+1$ 行，每行 $3$ 个整数 $R_i,S_i,L_i$。

* 第 $M+2$ 至 $M+B+1$ 行，进行 $B$ 次询问，每行 $2$ 个整数 $P_i ,Q_i$。

### 输出格式
每次询问输出一个整数，即答案。



---

---
title: "[USACO10DEC] Apple Delivery S"
layout: "post"
diff: 普及/提高-
pid: P3003
tag: ['2010', 'USACO', '最短路']
---
# [USACO10DEC] Apple Delivery S
## 题目描述

Bessie has two crisp red apples to deliver to two of her friends in the herd. Of course, she travels the C (1 <= C <= 200,000)

cowpaths which are arranged as the usual graph which connects P (1 <= P <= 100,000) pastures conveniently numbered from 1..P: no cowpath leads from a pasture to itself, cowpaths are bidirectional, each cowpath has an associated distance, and, best of all, it is always possible to get from any pasture to any other pasture. Each cowpath connects two differing pastures P1\_i (1 <= P1\_i <= P) and P2\_i (1 <= P2\_i <= P) with a distance between them of D\_i. The sum of all the distances D\_i does not exceed 2,000,000,000.

What is the minimum total distance Bessie must travel to deliver both apples by starting at pasture PB (1 <= PB <= P) and visiting pastures PA1 (1 <= PA1 <= P) and PA2 (1 <= PA2 <= P) in any order. All three of these pastures are distinct, of course.

Consider this map of bracketed pasture numbers and cowpaths with distances:

```cpp
               3        2       2
           [1]-----[2]------[3]-----[4]
             \     / \              /
             7\   /4  \3           /2
               \ /     \          /
               [5]-----[6]------[7]
                    1       2
```
If Bessie starts at pasture [5] and delivers apples to pastures [1] and [4], her best path is:

5 -> 6-> 7 -> 4\* -> 3 -> 2 -> 1\*

with a total distance of 12.
## 输入格式

\* Line 1: Line 1 contains five space-separated integers: C, P, PB, PA1, and PA2

\* Lines 2..C+1: Line i+1 describes cowpath i by naming two pastures it connects and the distance between them: P1\_i, P2\_i, D\_i

## 输出格式

\* Line 1: The shortest distance Bessie must travel to deliver both apples

## 样例

### 样例输入 #1
```
9 7 5 1 4 
5 1 7 
6 7 2 
4 7 2 
5 6 1 
5 2 4 
4 3 2 
1 2 3 
3 2 2 
2 6 3 

```
### 样例输出 #1
```
12 

```
## 题目翻译

贝西有两个又香又脆的红苹果要送给她的两个朋友。当然她可以走的 $C(1 \le C \le 200000)$ 条“牛路”都被包含在一种常用的图中。这张图同时包含了$P(1 \le P \le 100000)$ 个牧场，分别被标为 $1 \cdots P$。没有“牛路”会从一个牧场又走回它自己。“牛路”是双向的，每条牛路都会被标上一个距离。最重要的是，每个牧场都可以通向另一个牧场。每条牛路都连接着两个不同的牧场 $P1\_i$和$P2\_i$（$1 \le P1\_i,P2\_i \le P$)，距离为$D\_i$。所有“牛路”的距离之和不大于 $2000000000$。

现在，贝西要从牧场 $PB$ 开始给 $PA\_1$ 和 $PA\_2$ 牧场各送一个苹果（$PA\_1$ 和 $PA\_2$ 顺序可以调换），那么最短的距离是多少呢？当然，$PB$、$PA\_1$ 和 $PA\_2$ 各不相同。



---

---
title: "[USACO11MAR] Package Delivery S"
layout: "post"
diff: 普及/提高-
pid: P3020
tag: ['2011', 'USACO', '最短路']
---
# [USACO11MAR] Package Delivery S
## 题目描述

Farmer John must deliver a package to Farmer Dan, and is preparing to make his journey. To keep the peace, he gives a tasty treat to every cow that he meets along his way and, of course, FJ is so frugal that he would like to encounter as few cows as possible.

农夫约翰必须送一个包裹给农夫丹，并准备去旅行。为了保持和平，他必须给每一头遇到的奶牛一些吃的，当然，FJ很节俭，他想可能遇到尽可能少的奶牛。

FJ has plotted a map of N (1 <= N <= 50,000) barns, connected by M (1 <= M <= 50,000) bi-directional cow paths, each with C\_i (0 <= C\_i <= 1,000) cows ambling along it. A cow path connects two distinct barns, A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i). Two barns may be directly connected by more than one path. He is currently located at barn 1, and Farmer Dan is located at barn N.

FJ 已经绘制了 $N(1 \le N \le 50000)$ 个谷仓的地图，通过 $M(1 \le M \le 50000)$ 条双向牛道，每条双向牛道上有 $c[i](0 \le c[i] \le 1000)$ 奶牛漫步。双向牛道连接两个不同的谷仓，$a[i]$ 和 $b[i](1 \le a[i] \le N,1 \le b[i] \le N, a[i] \neq b[i])$。两个谷仓可以由一条以上的小路直接连接。他目前在 $1$ 号谷仓，农夫丹位于 $N$ 号谷仓。

Consider the following map:

```cpp
           [2]---
          / |    \
         /1 |     \ 6
        /   |      \
     [1]   0|    --[3]
        \   |   /     \2
        4\  |  /4      [6]
          \ | /       /1
           [4]-----[5] 
                3  
```
The best path for Farmer John to take is to go from 1 -> 2 -> 4 -> 5 -> 6, because it will cost him 1 + 0 + 3 + 1 = 5 treats.

Given FJ's map, what is the minimal number of treats that he should bring with him, given that he will feed each distinct cow he meets exactly one treat? He does not care about the length of his journey.

## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..M+1: Three space-separated integers: A\_i, B\_i, and C\_i

## 输出格式

\* Line 1: The minimum number of treats that FJ must bring

## 样例

### 样例输入 #1
```
6 8 
4 5 3 
2 4 0 
4 1 4 
2 1 1 
5 6 1 
3 6 2 
3 2 6 
3 4 4 

```
### 样例输出 #1
```
5 

```


---

---
title: "【模板】单源最短路径（弱化版）"
layout: "post"
diff: 普及/提高-
pid: P3371
tag: ['图论', 'O2优化', '最短路']
---
# 【模板】单源最短路径（弱化版）
## 题目背景

本题测试数据为随机数据，在考试中可能会出现构造数据让SPFA不通过，如有需要请移步 [P4779](https://www.luogu.org/problemnew/show/P4779)。
## 题目描述

如题，给出一个有向图，请输出从某一点出发到所有点的最短路径长度。

## 输入格式

第一行包含三个整数 $n,m,s$，分别表示点的个数、有向边的个数、出发点的编号。

接下来 $m$ 行每行包含三个整数 $u,v,w$，表示一条 $u \to v$ 的，长度为 $w$ 的边。
## 输出格式

输出一行 $n$ 个整数，第 $i$ 个表示 $s$ 到第 $i$ 个点的最短路径，若不能到达则输出 $2^{31}-1$。
## 样例

### 样例输入 #1
```
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4
```
### 样例输出 #1
```
0 2 4 3
```
## 提示

【数据范围】    
对于 $20\%$ 的数据：$1\le n \le 5$，$1\le m \le 15$；  
对于 $40\%$ 的数据：$1\le n \le 100$，$1\le m \le 10^4$；   
对于 $70\%$ 的数据：$1\le n \le 1000$，$1\le m \le 10^5$；   
对于 $100\%$ 的数据：$1 \le n \le 10^4$，$1\le m \le 5\times 10^5$，$1\le u,v\le n$，$w\ge 0$，$\sum w< 2^{31}$，保证数据随机。

**Update 2022/07/29：两个点之间可能有多条边，敬请注意。**

对于真正 $100\%$ 的数据，请移步 [P4779](https://www.luogu.org/problemnew/show/P4779)。请注意，该题与本题数据范围略有不同。


样例说明：

![](https://cdn.luogu.com.cn/upload/pic/7641.png)

图片1到3和1到4的文字位置调换



---

---
title: "[TJOI2007] 线段"
layout: "post"
diff: 普及/提高-
pid: P3842
tag: ['动态规划 DP', '2007', '各省省选', '最短路', '天津']
---
# [TJOI2007] 线段
## 题目描述

在一个 $n \times n$ 的平面上，在每一行中有一条线段，第 $i$ 行的线段的左端点是$(i, L_{i})$，右端点是$(i, R_{i})$。

你从 $(1,1)$ 点出发，要求沿途走过所有的线段，最终到达 $(n,n)$ 点，且所走的路程长度要尽量短。

更具体一些说，你在任何时候只能选择向下走一步（行数增加 $1$）、向左走一步（列数减少 $1$）或是向右走一步（列数增加 $1$）。当然，由于你不能向上行走，因此在从任何一行向下走到另一行的时候，你必须保证已经走完本行的那条线段。
## 输入格式

第一行有一个整数 $n$。

以下 $n$ 行，在第 $i$ 行（总第 $(i+1)$ 行）的两个整数表示 $L_i$ 和 $R_i$。

## 输出格式

仅包含一个整数，你选择的最短路程的长度。
## 样例

### 样例输入 #1
```
6
2 6
3 4
1 3
1 2
3 6
4 5
```
### 样例输出 #1
```
24
```
## 提示

我们选择的路线是

```
 (1, 1) (1, 6)
 (2, 6) (2, 3)
 (3, 3) (3, 1)
 (4, 1) (4, 2)
 (5, 2) (5, 6)
 (6, 6) (6, 4) (6, 6)
```
不难计算得到，路程的总长度是 $24$。 

对于 $100\%$ 的数据中，$n \le 2 \times 10^4$，$1 \le L_i \le R_i \le n$。


---

---
title: "道路重建"
layout: "post"
diff: 普及/提高-
pid: P3905
tag: ['图论', '最短路', '队列']
---
# 道路重建
## 题目描述

从前，在一个王国中，在 $n$ 个城市间有 $m$ 条道路连接，而且任意两个城市之间至多有一条道路直接相连。在经过一次严重的战争之后，有 $d$ 条道路被破坏了。国王想要修复国家的道路系统，现在有两个重要城市 $A$ 和 $B$ 之间的交通中断，国王希望尽快的恢复两个城市之间的连接。你的任务就是修复一些道路使 $A$ 与 $B$ 之间的连接恢复，并要求修复的道路长度最小。
## 输入格式

输入文件第一行为一个整数 $n\ (2<n\le 100)$，表示城市的个数。这些城市编号从 $1$ 到 $n$。

第二行为一个整数 $m\ (n-1\le m\le \dfrac{1}{2}n(n-1))$，表示道路的数目。

接下来的 $m$ 行，每行 $3$ 个整数 $i,j,k\ (1 \le i,j \le n,i\neq j,0<k \le 100)$，表示城市 $i$ 与 $j$ 之间有一条长为 $k$ 的道路相连。

接下来一行为一个整数 $d\ (1\le d\le m)$，表示战后被破坏的道路的数目。在接下来的 $d$ 行中，每行两个整数 $i$ 和 $j$，表示城市 $i$ 与 $j$ 之间直接相连的道路被破坏。

最后一行为两个整数 $A$ 和 $B$，代表需要恢复交通的两个重要城市。
## 输出格式

输出文件仅一个整数，表示恢复 $A$ 与 $B$ 间的交通需要修复的道路总长度的最小值。

## 样例

### 样例输入 #1
```
3
2
1 2 1
2 3 2
1
1 2
1 3
```
### 样例输出 #1
```
1
```


---

---
title: "Geodetic集合"
layout: "post"
diff: 普及/提高-
pid: P3906
tag: ['图论', '枚举', '排序', '最短路']
---
# Geodetic集合
## 题目描述

图 $\text G$ 是一个无向连通图，没有自环，并且两点之间至多只有一条边。我们定义顶点 $v,u$ 的最短路径就是从 $v$ 到 $u$ 经过边最少的路径。所有包含在 $v-u$ 的最短路径上的顶点被称为 $v-u$ 的 Geodetic 顶点，这些顶点的集合记作 $I(v,u)$。

我们称集合 $I(v,u)$ 为一个 Geodetic 集合。

例如下图中，$I(2,5)=\{2,3,4,5\}$，$I(1,5)=\{1,3,5\}$，$I(2,4)=\{2,4\}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/26c7a19d.png)

给定一个图 $\text G$ 和若干点对 $v,u$，请你分别求出 $I(v,u)$。
## 输入格式

第一行为两个整数 $n,m$，分别表示图 $\text G$ 的顶点数和边数（顶点编号为 $1\sim n$）。  
接下来 $m$ 行，每行两个整数 $a,b$，表示 顶点 $a$ 和 $b$ 之间有一条无向边。  
第 $m+2$ 行有一个整数 $k$，表示给定的点对数。  
接下来 $k$ 行，每行两个整数 $v,u$，表示每个点对的起点和终点。 
## 输出格式

共 $k$ 行，对于输入文件中每一个点对 $v,u$，按顶点顺序一行输出 $I(v,u)$ 里面的所有点的编号。
## 样例

### 样例输入 #1
```
5 6
1 2
1 3
2 3
2 4
3 5
4 5
3
2 5
5 1
2 4
```
### 样例输出 #1
```
2 3 4 5
1 3 5
2 4
```
## 提示

对于所有数据，满足 $1\leqslant n\leqslant 40$，$1\leqslant m\leqslant \frac{n(n-1)}2$。


---

---
title: "【模板】单源最短路径（标准版）"
layout: "post"
diff: 普及/提高-
pid: P4779
tag: ['图论', '优先队列', '最短路']
---
# 【模板】单源最短路径（标准版）
## 题目背景

2018 年 7 月 19 日，某位同学在 [NOI Day 1 T1 归程](https://www.luogu.org/problemnew/show/P4768) 一题里非常熟练地使用了一个广为人知的算法求最短路。

然后呢？

$100 \rightarrow 60$；

$\text{Ag} \rightarrow \text{Cu}$；

最终，他因此没能与理想的大学达成契约。

小 F 衷心祝愿大家不再重蹈覆辙。
## 题目描述

给定一个 $n$ 个点，$m$ 条有向边的带非负权图，请你计算从 $s$ 出发，到每个点的距离。

数据保证你能从 $s$ 出发到任意点。
## 输入格式

第一行为三个正整数 $n, m, s$。
第二行起 $m$ 行，每行三个非负整数 $u_i, v_i, w_i$，表示从 $u_i$ 到 $v_i$ 有一条权值为 $w_i$ 的有向边。
## 输出格式

输出一行 $n$ 个空格分隔的非负整数，表示 $s$ 到每个点的距离。
## 样例

### 样例输入 #1
```
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4
```
### 样例输出 #1
```
0 2 4 3
```
## 提示

样例解释请参考 [数据随机的模板题](https://www.luogu.org/problemnew/show/P3371)。

$1 \leq n \leq 10^5$；

$1 \leq m \leq 2\times 10^5$；

$s = 1$；

$1 \leq u_i, v_i\leq n$；

$0 \leq w_i \leq 10 ^ 9$,

$0 \leq \sum w_i \leq 10 ^ 9$。

本题数据可能会持续更新，但不会重测，望周知。

2018.09.04 数据更新 from @zzq


---

---
title: "基础最短路练习题"
layout: "post"
diff: 普及/提高-
pid: P5651
tag: ['O2优化', '最短路', '洛谷月赛']
---
# 基础最短路练习题
## 题目背景

YSGH 牛逼
## 题目描述

给定 $n$ 个点 $m$ 条边的简单无向连通图 $G$，边有边权。保证没有重边和自环。

定义一条简单路径的权值为路径上所有边边权的异或和。

保证 $G$ 中不存在简单环使得边权异或和不为 $0$。

$Q$ 次询问 $x$ 到 $y$ 的最短简单路径。
## 输入格式

第一行三个正整数 $n, m, Q$。

接下来 $m$ 行，一行三个非负整数 $x, y, v$（$1 \le x, y \le n$），表示一条连接 $x, y$，权值为 $v$ 的无向边。保证没有重边和自环。

接下来 $Q$ 行，一行两个正整数 $x, y$（$1 \le x, y \le n$），表示一次询问。
## 输出格式

$Q$ 行，一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3 2 1
1 2 2
2 3 3
1 3
```
### 样例输出 #1
```
1
```
## 提示

| 数据点编号 | $n, Q \le$ | 特殊性质 |
| :--: | :--: | :--: |
| $1,2$ | $10$ | 无 |
| $3,4$ | $20$ | 无 |
| $5,6$ | ${10}^5$ | $m = n - 1$ |
| $7,8$ | ${10}^5$ | $v \le 1$ |
| $9,10$ | ${10}^5$ | 无 |

对于 $100\%$ 的数据，满足 $1 \le n \le {10}^5$，$1 \le m \le 2n$，$0 \le v < 2^{30}$。


---

---
title: "[USACO05MAR] Checking an Alibi 不在场的证明"
layout: "post"
diff: 普及/提高-
pid: P6770
tag: ['2005', 'USACO', '最短路']
---
# [USACO05MAR] Checking an Alibi 不在场的证明
## 题目描述

农场有 $F$ 个点，已知 $P$ 条边以及每条边的起点终点和通过时间，给出 $C$ 个有牛的点，求在规定时间 $M$ 内能从起点到达牛当前位置的牛的数量，并按升序输出牛的编号。

谷仓里发现谷物被盗！FJ 正试图从 $C$ 只奶牛里找出那个偷谷物的罪犯。幸运的是，一个恰好路过的卫星拍下谷物被盗前 $M$ 秒的农场的图片。这样约翰就能通过牛们的位置来判断谁有足够的时间来盗窃谷物。

约翰农场有 $F$ 草地，标号 $1$ 到 $F$，还有 $P$ 条双向路连接着它们。通过这些路需要的时间在 $1$ 到 $70000$ 秒的范围内。田地 $1$ 上建有那个被盗的谷仓。给出农场地图，以及卫星照片里每只牛所在的位置，请判断哪些牛有可能犯罪。

请注意：数据里可能存在重边（起点和终点相同的边）。
## 输入格式

第 $1$ 行：四个以空格分隔的整数：$F,P,C$ 和 $M$。\
第 $2$ 行至 $P+1$ 行：三个空间分隔的整数，描述一个路径。连接 $F1$ 和 $F2$ 的路径需要 $T$ 秒。\
第 $P+2$ 行至 $P+C+1$ 行：每行一个整数，是一头牛的位置。
## 输出格式

第 $1$ 行输出嫌疑犯的数目，接下来每一行输出一只嫌疑犯的编号。
## 样例

### 样例输入 #1
```
7 6 5 8
1 4 2
1 2 1
2 3 6
3 5 5
5 4 6
1 7 9
1
4
5
3
7
```
### 样例输出 #1
```
4
1
2
3
4
```
## 提示

#### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/ik4552lc.png)

#### 数据约定

对于 $100\%$ 的数据：$1 \le M \le 70000$，$1 \le C \le 100$，$1 \le P \le 1000$，$1 \le F \le 500$。


---

---
title: "[Cnoi2020] 雷雨"
layout: "post"
diff: 普及/提高-
pid: P6833
tag: ['图论', '2020', 'O2优化', '最短路', '洛谷月赛']
---
# [Cnoi2020] 雷雨
## 题目背景

> 令人不安的云开始笼罩天空。  
巨大的建筑在强风中轧轧作响。  
幻想乡中响彻着不和协音。  
——「东方辉针城 ～ Double Dealing Character」

一个雷雨交加的夜晚，一束闪电击中了雾之湖畔的红魔馆和迷途竹林。

似乎有什么大事要发生，Cirno 在小屋静静地中思考着。
## 题目描述

幻想乡的纵切面可以抽象成一个 $n\times m$ 的矩形。

其中每一个 $1\times 1$ 的单元格 $(i,j)$ 都有一个**电阻计量值**(虚构的概念) $R_{i,j}$。

闪电从**雷雨云**上的 $\texttt{O}(n,a)$ 发出，击中了**地面**上的*红魔馆* $\texttt{A}(1,b)$ 与*迷途竹林* $\texttt{B}(1,c)$。

雷电是自然的造物，所以覆盖的位置电阻计量值总和最小，即从 $\texttt{O}$ 到 $\texttt{A}$ 与 $\texttt{B}$ 的**两条路径的并集**的电阻计量值的和最小。

所以在所有位置电阻计量已知的情况下，Cirno 想知道雷电的经过的路径的最小电阻计量值的和。
## 输入格式

第一行，五个整数 $n,m,a,b,c$。$(0<a,b,c\le m)$

以下 $n$ 行，每行 $m$ 个整数，表示电阻计量 $R_{i,j}$，其中第一行表示雷雨云，最后一行表示地面。
## 输出格式

一行，一个整数，表示答案。
## 样例

### 样例输入 #1
```
5 5 1 2 4
1 8 1 6 6
1 1 1 2 4
8 3 1 2 2
1 2 1 9 1
1 0 9 1 1
```
### 样例输出 #1
```
15
```
## 提示

## 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/7ozs40i3.png)

如图黄色线为闪电的路径。

## 数据范围与约定

对于 $100\%$ 的数据保证：$0<n,m \le 1000$，$0 \le R_{i,j}\le 10^9$，$0< a,b,c \le m$。

#### 子任务「本题采用捆绑测试」

 - Subtask1（$10\%$）: $R_{i,j}\in\{1\}$。
 - Subtask2（$10\%$）: $R_{i,j}\in\{0,1\}$。
 - Subtask3（$10\%$）: $a=b=c$。
 - Subtask4（$10\%$）: $n,m \le 5$。
 - Subtask5（$60\%$）: 无特殊限制。
 


---

---
title: "[蓝桥杯 2015 国 AC] 穿越雷区"
layout: "post"
diff: 普及/提高-
pid: P8628
tag: ['2015', '最短路', '蓝桥杯国赛']
---
# [蓝桥杯 2015 国 AC] 穿越雷区
## 题目描述

$X$ 星的坦克战车很奇怪，它必须交替地穿越正能量辐射区和负能量辐射区才能保持正常运转，否则将报废。

某坦克需要从 $A$ 区到 $B$ 区去（$A$，$B$ 区本身是安全区，没有正能量或负能量特征），怎样走才能路径最短？

已知的地图是一个方阵，上面用字母标出了 $A$，$B$ 区，其它区都标了正号或负号分别表示正负能量辐射区。

例如：

```
A + - + -
- + - - +
- + + + -
+ - + - +
B + - + -
```

坦克车只能水平或垂直方向上移动到相邻的区。

## 输入格式

输入第一行是一个整数 $n$，表示方阵的大小，$4 \le n<100$。

接下来是 $n$ 行，每行有 $n$ 个数据，可能是 `A`，`B`，`+`，`-` 中的某一个，中间用空格分开。
## 输出格式

要求输出一个整数，表示坦克从 $A$ 区到 $B$ 区的最少移动步数。

如果没有方案，则输出 $-1$。
## 样例

### 样例输入 #1
```
5
A + - + -
- + - - +
- + + + -
+ - + - +
B + - + -
```
### 样例输出 #1
```
10
```
## 提示

时限 1 秒, 512M。蓝桥杯 2015 年第六届国赛


---

---
title: "[蓝桥杯 2018 国 B] 调手表"
layout: "post"
diff: 普及/提高-
pid: P8674
tag: ['2018', '最短路', '蓝桥杯国赛']
---
# [蓝桥杯 2018 国 B] 调手表
## 题目描述

小明买了块高端大气上档次的电子手表，他正准备调时间呢。

在 M78 星云，时间的计量单位和地球上不同，M78 星云的一个小时有 $n$ 分钟。

大家都知道，手表只有一个按钮可以把当前的数加一。在调分钟的时候，如果当前显示的数是 $0$，那么按一下按钮就会变成 $1$，再按一次变成 $2$。如果当前的数是 $n-1$，按一次后会变成 $0$。

作为强迫症患者，小明一定要把手表的时间调对。如果手表上的时间比当前时间多 $1$，则要按 $n-1$ 次加一按钮才能调回正确时间。

小明想，如果手表可以再添加一个按钮，表示把当前的数加 $k$ 该多好啊……

他想知道，如果有了这个 $+k$ 按钮，按照最优策略按键，从任意一个分钟数调到另外任意一个分钟数最多要按多少次。

注意，按 $+k$ 按钮时，如果加 $k$ 后数字超过 $n-1,$ 则会对 $n$ 取模。

比如，$n=10,k=6$ 的时候，假设当前时间是 $0$，连按 $2$ 次 $+k$ 按钮，则调为 $2$。

## 输入格式

一行两个整数 $n,k$，意义如题。
## 输出格式

一行一个整数。表示：按照最优策略按键，从一个时间调到另一个时间最多要按多少次。
## 样例

### 样例输入 #1
```
5 3
```
### 样例输出 #1
```
2
```
## 提示

**【样例解释】**

如果时间正确则按 $0$ 次。否则要按的次数和操作系列之间的关系如下：
1. +1
2. +1, +1
3. +3
4. +3, +1

**【数据约定】**

对于 $30\%$ 的数据 $0<k<n \le 5$。

对于 $60\%$ 的数据 $0<k<n \le 100$。

对于 $100\%$ 的数据 $0<k<n \le 10^5$。

时限 3 秒, 256M。蓝桥杯 2018 年第九届国赛


---

---
title: "[蓝桥杯 2022 国 A] 环境治理"
layout: "post"
diff: 普及/提高-
pid: P8794
tag: ['二分', '2022', '最短路', '蓝桥杯国赛']
---
# [蓝桥杯 2022 国 A] 环境治理
## 题目描述

LQ 国拥有 $n$ 个城市，从 $0$ 到 $n - 1$ 编号，这 $n$ 个城市两两之间都有且仅有一条双向道路连接，这意味着任意两个城市之间都是可达的。每条道路都有一个属性 $D$，表示这条道路的灰尘度。当从一个城市 A 前往另一个城市 B 时，可能存在多条路线，每条路线的灰尘度定义为这条路线所经过的所有道路的灰尘度之和，LQ 国的人都很讨厌灰尘，所以他们总会优先选择灰尘度最小的路线。

LQ 国很看重居民的出行环境，他们用一个指标 $P$ 来衡量 LQ 国的出行环境，$P$ 定义为：

$$P=\sum \limits_{i=0}^{n-1} \sum \limits_{j=0}^{n-1} d(i,j)$$

其中 $d(i,j)$ 表示城市 $i$ 到城市 $j$ 之间灰尘度最小的路线对应的灰尘度的值。

为了改善出行环境，每个城市都要有所作为，当某个城市进行道路改善时，会将与这个城市直接相连的所有道路的灰尘度都减少 $1$，但每条道路都有一个灰尘度的下限值 $L$，当灰尘度达到道路的下限值时，无论再怎么改善，道路的灰尘度也不会再减小了。

具体的计划是这样的：

- 第 $1$ 天，$0$ 号城市对与其直接相连的道路环境进行改善；
- 第 $2$ 天，$1$ 号城市对与其直接相连的道路环境进行改善；

……
- 第 $n$ 天，$n - 1$ 号城市对与其直接相连的道路环境进行改善；
- 第 $n + 1$ 天，$0$ 号城市对与其直接相连的道路环境进行改善；
- 第 $n + 2$ 天，$1$ 号城市对与其直接相连的道路环境进行改善；

……

LQ 国想要使得 $P$ 指标满足 $P \leq Q$。请问最少要经过多少天之后，$P$ 指标可以满足 $P \leq Q$。如果在初始时就已经满足条件，则输出 $0$；如果永远不可能满足，则输出 $-1$。
## 输入格式

输入的第一行包含两个整数 $n, Q$，用一个空格分隔，分别表示城市个数和期望达到的 $P$ 指标。

接下来 $n$ 行，每行包含 $n$ 个整数，相邻两个整数之间用一个空格分隔，其中第 $i$ 行第 $j$ 列的值 $D_{i,j} (D_{i,j}=D_{j,i},D_{i,i} = 0)$ 表示城市 $i$ 与城市 $j$ 之间直接相连的那条道路的灰尘度。

接下来 $n$ 行，每行包含 $n$ 个整数，相邻两个整数之间用一个空格分隔，其中第 $i$ 行第 $j$ 列的值 $L_{i,j} (L_{i,j} = L_{j,i}, L_{i,i} = 0)$ 表示城市 $i$ 与城市 $j$ 之间直接相连的那条道路的灰尘度的下限值。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
3 10
0 2 4
2 0 1
4 1 0
0 2 2
2 0 0
2 0 0
```
### 样例输出 #1
```
2

```
## 提示

**【样例说明】**

初始时的图如下所示，每条边上的数字表示这条道路的灰尘度：

![](https://cdn.luogu.com.cn/upload/image_hosting/5lz6auke.png)

此时每对顶点之间的灰尘度最小的路线对应的灰尘度为：

- $d(0, 0) = 0, d(0, 1) = 2, d(0, 2) = 3$；
- $d(1, 0) = 2, d(1, 1) = 0, d(1, 2) = 1$；
- $d(2, 0) = 3, d(2, 1) = 1, d(2, 2) = 0$。

初始时的 $P$ 指标为 $(2 + 3 + 1) \times 2 = 12$，不满足 $P \leq Q = 10$;

第一天，$0$ 号城市进行道路改善，改善后的图示如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/mrhf5wx6.png)

注意到边 $(0, 2)$ 的值减小了 $1$，但 $(0, 1)$ 并没有减小，因为 $L_{0,1} = 2$ ，所以 $(0, 1)$ 的值不可以再减小了。此时每对顶点之间的灰尘度最小的路线对应的灰尘度为：

- $d(0, 0) = 0, d(0, 1) = 2, d(0, 2) = 3$，
- $d(1, 0) = 2, d(1, 1) = 0, d(1, 2) = 1$，
- $d(2, 0) = 3, d(2, 1) = 1, d(2, 2) = 0$。

此时 $P$ 仍为 $12$。

第二天，1 号城市进行道路改善，改善后的图示如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/tjxis3yb.png)

此时每对顶点之间的灰尘度最小的路线对应的灰尘度为：

- $d(0, 0) = 0, d(0, 1) = 2, d(0, 2) = 2$，
- $d(1, 0) = 2, d(1, 1) = 0, d(1, 2) = 0$，
- $d(2, 0) = 2, d(2, 1) = 0, d(2, 2) = 0$。

此时的 $P$ 指标为 $(2 + 2) \times 2 = 8 < Q$，此时已经满足条件。

所以答案是 $2$。

**【评测用例规模与约定】**

- 对于 $30\%$ 的评测用例，$1 \leq n \leq 10$，$0 \leq L_{i,j} \leq D_{i,j} \leq 10$；
- 对于 $60\%$ 的评测用例，$1 \leq n \leq 50$，$0 \leq L_{i,j} \leq D_{i,j} \leq 10^5$；
- 对于所有评测用例，$1 \leq n \leq 100$，$0 \leq L_{i,j} \leq D_{i,j} \leq 10^5$，$0 \leq Q \leq 2^{31} - 1$。

蓝桥杯 2022 国赛 A 组 F 题。


---

---
title: "[蓝桥杯 2022 国 B] 出差"
layout: "post"
diff: 普及/提高-
pid: P8802
tag: ['2022', '最短路', '蓝桥杯国赛']
---
# [蓝桥杯 2022 国 B] 出差
## 题目描述

$\mathrm{A}$ 国有 $N$ 个城市，编号为 $1 \ldots N$ 小明是编号为 $1$ 的城市中一家公司的员工，今天突然接到了上级通知需要去编号为 $N$ 的城市出差。

由于疫情原因，很多直达的交通方式暂时关闭，小明无法乘坐飞机直接从城市 $1$ 到达城市 $N$，需要通过其他城市进行陆路交通中转。小明通过交通信息网，查询到了 $M$ 条城市之间仍然还开通的路线信息以及每一条路线需要花费的时间。

同样由于疫情原因，小明到达一个城市后需要隔离观察一段时间才能离开该城市前往其他城市。通过网络，小明也查询到了各个城市的隔离信息。（由于小明之前在城市 $1$，因此可以直接离开城市 $1$，不需要隔离）

由于上级要求，小明希望能够尽快赶到城市 $\mathrm{N}$, 因此他求助于你，希望你能帮他规划一条路线，能够在最短时间内到达城市 $N$ 。

## 输入格式

第 $1$ 行：两个正整数 $N, M$ 表示 A 国的城市数量, $M$ 表示末关闭的路线数量。

第 $2$ 行: $N$ 个正整数，第 $i$ 个整数 $C_{i}$ 表示到达编号为 $\mathrm{i}$ 的城市后需要隔离的时间。

第 $3 \ldots M+2$ 行: 每行 $3$ 个正整数, $u, v, c$, 表示有一条城市 $u$ 到城市 $v$ 的双向路线仍然开通着，通过该路线的时间为 $c$。
## 输出格式

第 $1$ 行：$1$ 个正整数，表示小明从城市 $1$ 出发到达城市 $N$ 的最短时间。（到达城市 $N$，不需要计算城市 $N$ 的隔离时间）
## 样例

### 样例输入 #1
```
4 4
5 7 3 4
1 2 4
1 3 5
2 4 3
3 4 5
```
### 样例输出 #1
```
13
```
## 提示

**【样例说明】**

![](https://cdn.mathpix.com/cropped/2022_09_29_8ee8d95d6d0319bca20dg-09.jpg?height=464&width=478&top_left_y=1249&top_left_x=309)

**【评测用例规模与约定】**

对于 $100 \%$ 的数据, $1 \leq N \leq 1000,1 \leq M \leq 10000,1 \leq C_{i} \leq 200,1 \leq u, v \leq$ $N, 1 \leq c \leq 1000$ 


蓝桥杯 2022 国赛 B 组 E 题。


---

---
title: "Deception Point"
layout: "post"
diff: 普及/提高-
pid: P8943
tag: ['2023', '洛谷原创', 'O2优化', '最短路', '基环树']
---
# Deception Point
## 题目背景

“防空火网已启用。”三角洲二号喊道，他坐在“基奥瓦”武装直升机舱门边的武器控制椅里，竖起了大拇指，“火力网
、调制噪声、掩护脉冲全都激活并锁定。”

三角洲一号心领神会，驾驶着飞机猛地向右一个侧弯飞机又驶上了一条前往“戈雅”的直线路径。这一招能躲过“戈雅”的雷达监控。

“锡箔包确定！”三角洲二号喊道。

> 绝对的孤立，

三角洲一号想。

> 他们毫无抵抗力。

他们的目标幸运且狡猾地从米尔恩冰架上逃脱了，但这回他们不会再得逞了。雷切尔 · 塞克斯顿和迈克尔 · 托兰选择弃岸上船，真是糟糕的选择。不过，这将是他们所做的最后一个坏决定了。
## 题目描述

雷切尔与迈克尔被困在了“戈雅”号上，而三角洲二号正在顺着雷达追杀二人。幸运的是，雷切尔也有一副雷达，因此双方都能知道对方的位置。

船舱内部共有 $n$ 个舱室，其中有 $n$ 条走廊连接这些舱室。$n$ 个舱室是互相连通的。由于船上空间拥挤，船舱内不会出现小于等于四条走廊组成的环。每过一分钟，雷切尔与三角洲二号都会同时从一个舱室跑到另一个舱室。

如果雷切尔在舱室内或者过道上碰到了三角洲，那么就意味着大限将至。雷切尔总共有 $q$ 个问题：当她在舱室 $x$，且三角洲二号在舱室 $y$ 时，她是否可以存活下来？

---

#### **【形式化题意】**

给定一张 $n$ 个点 $n$ 条边的无向连通图，图内不存在四元（及以下）环。$q$ 次询问 $x,y$，分别在图上 $x,y$ 点上放上棋子 $\rm A, B$。

每次两人同时操作棋子沿图边移动一步，若两棋子同时走到了同一个点上或者同时走过了相同的边，则 $\rm B$ 胜利。如果在 $10^{10^{9961}}$ 次操作后 $\rm B$ 还未胜利，则 $\rm A$ 胜利。

$\rm A,B$ 都是绝顶聪明的，他们不会做出对自己不利的决策。请你求出每次游戏的游戏结果。若 $\rm A$ 获胜，输出 `Survive`；否则输出 `Deception`。

**若对题意有疑问，请移步样例解释与数据范围部分。**
## 输入格式

第一行两个整数 $n,q$。  
接下来 $n$ 行，每行两个整数 $u_i,v_i$，表示舱室 $u_i$ 与 $v_i$ 之间有一条过道。
之后 $q$ 行，每行两个整数 $x_i,y_i$，表示一次询问。
## 输出格式

共 $q$ 行。对于每个询问，如果雷切尔可以存活，那么输出 `Survive`，否则输出 `Deception`。
## 样例

### 样例输入 #1
```
8 3
2 1
3 1 
4 2 
5 3
6 2
7 5
8 4
5 6
7 8
8 6
3 6
```
### 样例输出 #1
```
Survive
Deception
Survive

```
## 提示

#### 【样例解释】

船舱结构图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/tlsqnsia.png)

在第二组询问中，三角洲可以先走一步到达结点 $2$，此时雷切尔到达结点 $4$。随后可以证明，不存在一种方案使得雷切尔不碰到三角洲。

#### 【数据范围】

**本题开启捆绑测试。**

| $\text{Subtask}$ | 分值 | $n\le$ | $q\le$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $5$ | $2\times10^5$ | $1$ | 无 |
| $1$ | $5$ | $10$ | $2\times10^5$ | 无 |
| $2$ | $5$ | $2\times 10^5$ | $2\times10^5$ | $\forall 1\le i\le n, u_i=i,v_i=(i\bmod n) + 1$ |
| $3$ | $15$ | $200$ | $2\times 10^5$ | 无 |
| $4$ | $20$ | $2\times 10^3$ | $2\times 10^5$ | 无 |
| $5$ | $50$ | $2\times 10^5$ | $2\times 10^5$ | 无 |

对于 $100\%$ 的数据，$3\le n\le 2\times10^5$，$1\le q\le2\times10^5$，$u_i\neq v_i$，$x_i\neq y_i$。不存在四（及以下）元环。


---

