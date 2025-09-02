---
title: "西湖有雅座"
layout: "post"
diff: 普及+/提高
pid: P11409
tag: ['二分图']
---
# 西湖有雅座
## 题目背景

>江湖路上走走停停，翻开年少漂泊的回忆。
如今走过这世间，万般留恋，风吹起了从前 。
## 题目描述

孙亦谐准备建西湖雅座来开饭馆。

他有 $n$ 个零件，零件的大小均为 $h\times w$。零件从 $1 \sim n$ 编号。

对于一个大小为 $h \times w$ 的零件，其可视为一个 $h$ 行 $w$ 列的矩阵 $w$。若用 $a_{i,j}$ 来表示这个矩阵中第 $i$ 行第 $j$ 列的元素。对于 $\forall a_{i,j}$，都有 $a_{i,j}\in \left \{  0,1\right \} $。

则编号为 $i$ 的零件的面积为： $S\left(i\right) = \sum_{i = 1}^{h}\sum_{j = 1}^{w}a_{i,j} $。

若编号为 $l$ 和 $r$ 的两个零件的分别表示为矩阵 $a$ 和 $b$，其在同一座楼的稳固程度可表示为： 

$$f\left(l,r\right) = \sum_{i = 1}^{h} \sum_{j = 1}^{w} \left [ (a_{i,j} = 1) \text{ and } (b_{i,j} = 1) \right ]$$

孙亦谐需要将这 $n$ 个零件先选取若干个按照任意顺序排列搭成大楼，然后把剩余的零件搭成小楼。若没有剩余零件，则可以不搭小楼。

设 $U$ 表示某座楼选取的零件编号的集合，则这座楼能成功搭建的条件是：

$$\forall i,j \in U,f\left (i,j\right) \ge \lceil \frac{ \min \left ( S\left(i \right),S\left(j\right) \right) }{2}\rceil$$

孙亦谐想知道在保证两座楼能成功搭建的条件下，让大楼使用的零件数尽量多。若无法成功搭建，则直接输出 `-1`。



## 输入格式

第一行输入包含三个正整数 $n,h,w$，分别表示零件的个数、零件的行数、零件的列数。

接下来输入 $n$ 个零件所表示的矩阵。

对于每个零件的矩阵 $a$，输入的格式如下：

共输入 $h$ 行，每行 $w$ 个元素。

第 $i$ 行第 $j$ 列的元素 $a_{i,j}$，表示这个矩阵中第 $i$ 行第 $j$ 列的元素。


## 输出格式

输出一个整数，表示在搭建成功的情况下，大楼最多能使用多少个零件。若无法成功搭建，则直接输出 `-1`。
## 样例

### 样例输入 #1
```
3 2 2
0 1 
1 1
1 0
0 0
0 1
0 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 2 2
0 1
1 0
0 0
0 1
1 0
0 0

```
### 样例输出 #2
```
-1
```
## 提示

**【样例1解释】**

可以证明最优方案是用第一个零件和第三个零件搭大楼，用第二个零件搭小楼。

**【数据范围】**

**本题采用捆绑测试**。

- Subtask 1（30 points）：$n \le 20$。
- Subtask 2（5 points）：$w = h = 1$。
- Subtask 3（65 points）：无特殊限制。

对于所有测试数据，$1 \le n \le 1000$，$1 \le w,h \le 6$。


---

---
title: "[NOIP 2010 提高组] 关押罪犯"
layout: "post"
diff: 普及+/提高
pid: P1525
tag: ['图论', '贪心', '2010', '并查集', 'NOIP 提高组', '排序', '二分图']
---
# [NOIP 2010 提高组] 关押罪犯
## 题目背景

NOIP2010 提高组 T3
## 题目描述

S 城现有两座监狱，一共关押着 $N$ 名罪犯，编号分别为 $1\sim N$。他们之间的关系自然也极不和谐。很多罪犯之间甚至积怨已久，如果客观条件具备则随时可能爆发冲突。我们用“怨气值”（一个正整数值）来表示某两名罪犯之间的仇恨程度，怨气值越大，则这两名罪犯之间的积怨越多。如果两名怨气值为 $c$ 的罪犯被关押在同一监狱，他们俩之间会发生摩擦，并造成影响力为 $c$ 的冲突事件。

每年年末，警察局会将本年内监狱中的所有冲突事件按影响力从大到小排成一个列表，然后上报到 S 城 Z 市长那里。公务繁忙的 Z 市长只会去看列表中的第一个事件的影响力，如果影响很坏，他就会考虑撤换警察局长。

在详细考察了 $N$ 名罪犯间的矛盾关系后，警察局长觉得压力巨大。他准备将罪犯们在两座监狱内重新分配，以求产生的冲突事件影响力都较小，从而保住自己的乌纱帽。假设只要处于同一监狱内的某两个罪犯间有仇恨，那么他们一定会在每年的某个时候发生摩擦。

那么，应如何分配罪犯，才能使 Z 市长看到的那个冲突事件的影响力最小？这个最小值是多少？

## 输入格式

每行中两个数之间用一个空格隔开。第一行为两个正整数 $N,M$，分别表示罪犯的数目以及存在仇恨的罪犯对数。接下来的 $M$ 行每行为三个正整数 $a_j,b_j,c_j$，表示 $a_j$ 号和 $b_j$ 号罪犯之间存在仇恨，其怨气值为 $c_j$。数据保证 $1<a_j< b_j\leq N, 0 < c_j\leq 10^9$，且每对罪犯组合只出现一次。

## 输出格式

共一行，为 Z 市长看到的那个冲突事件的影响力。如果本年内监狱中未发生任何冲突事件，请输出 `0`。

## 样例

### 样例输入 #1
```
4 6
1 4 2534
2 3 3512
1 2 28351
1 3 6618
2 4 1805
3 4 12884
```
### 样例输出 #1
```
3512
```
## 提示

**输入输出样例说明**

罪犯之间的怨气值如下面左图所示，右图所示为罪犯的分配方法，市长看到的冲突事件影响力是 $3512$（由 $2$ 号和 $3$ 号罪犯引发）。其他任何分法都不会比这个分法更优。

![](https://cdn.luogu.com.cn/upload/image_hosting/uia11zcq.png)

**数据范围**  

对于 $30\%$ 的数据有 $N\leq 15$。

对于 $70\%$ 的数据有 $N\leq 2000,M\leq 50000$。  

对于 $100\%$ 的数据有 $N\leq 20000,M\leq 100000$。



---

---
title: "[USACO4.2] 完美的牛栏The Perfect Stall"
layout: "post"
diff: 普及+/提高
pid: P1894
tag: ['USACO', '二分图']
---
# [USACO4.2] 完美的牛栏The Perfect Stall
## 题目描述

农夫约翰上个星期刚刚建好了他的新牛棚，他使用了最新的挤奶技术。

不幸的是，由于工程问题，每个牛栏都不一样。

第一个星期，农夫约翰随便地让奶牛们进入牛栏，但是问题很快地显露出来：每头奶牛都只愿意在她们喜欢的那些牛栏中产奶。

上个星期，农夫约翰刚刚收集到了奶牛们的爱好的信息（每头奶牛喜欢在哪些牛栏产奶）。

一个牛栏只能容纳一头奶牛，当然，一头奶牛只能在一个牛栏中产奶。

给出奶牛们的爱好的信息，计算最大分配方案。
## 输入格式

第一行为两个整数，$n$ 和 $m$。$n$ 是农夫约翰的奶牛数量，$m$ 是新牛棚的牛栏数量。

第二行到第 $n+1$ 行 一共 $n$ 行，每行对应若干个整数一只奶牛。第一个数字 $s_i$ 是这头奶牛愿意在其中产奶的牛栏的数目。后面的 $s_i$ 个数表示这些牛栏的编号。牛栏的编号限定在区间 $[1,m]$ 中，在同一行，一个牛栏不会被列出两次。

## 输出格式

只有一行，为一个整数，表示最多能分配到的牛栏的数量。
## 样例

### 样例输入 #1
```
5 5
2 2 5
3 2 3 4
2 1 5
3 1 2 5
1 2
```
### 样例输出 #1
```
4
```
## 提示

$0\le n,m\le 200$，$0\le s_i\le m$。


---

---
title: "飞行员配对方案问题"
layout: "post"
diff: 普及+/提高
pid: P2756
tag: ['网络流', 'Special Judge', 'O2优化', '二分图', '网络流与线性规划 24 题']
---
# 飞行员配对方案问题
## 题目背景

第二次世界大战期间，英国皇家空军从沦陷国征募了大量外籍飞行员。由皇家空军派出的每一架飞机都需要配备在航行技能和语言上能互相配合的两名飞行员，其中一名是英国飞行员，另一名是外籍飞行员。在众多的飞行员中，每一名外籍飞行员都可以与其他若干名英国飞行员很好地配合。
## 题目描述

一共有 $n$ 个飞行员，其中有 $m$ 个外籍飞行员和 $(n - m)$ 个英国飞行员，**外籍飞行员从 $1$ 到 $m$ 编号**，**英国飞行员从 $m + 1$ 到 $n$ 编号**。 对于给定的外籍飞行员与英国飞行员的配合情况，试设计一个算法找出最佳飞行员配对方案，使皇家空军一次能派出最多的飞机。
## 输入格式

输入的第一行是用空格隔开的两个正整数，分别代表外籍飞行员的个数 $m$ 和飞行员总数 $n$。  
从第二行起到倒数第二行，每行有两个整数 $u, v$，代表外籍飞行员 $u$ 可以和英国飞行员 $v$ 配合。  
输入的最后一行保证为 `-1 -1`，代表输入结束。
## 输出格式

**本题存在 Special Judge**。  
请输出能派出最多的飞机数量，并给出一种可行的方案。  
输出的第一行是一个整数，代表一次能派出的最多飞机数量，设这个整数是 $k$。  
第 $2$ 行到第 $k + 1$ 行，每行输出两个整数 $u, v$，代表在你给出的方案中，外籍飞行员 $u$ 和英国飞行员 $v$ 配合。这 $k$ 行的 $u$ 与 $v$ 应该互不相同。
## 样例

### 样例输入 #1
```
5 10
1 7
1 8
2 6
2 9
2 10
3 7
3 8
4 7
4 8
5 10
-1 -1

```
### 样例输出 #1
```
4
1 7
2 9
3 8
5 10

```
## 提示

**【数据范围与约定】**

- 对于 $100\%$ 的数据，保证 $1 \leq m \leq n < 100$，$1 \leq u \leq m < v \leq n$，同一组配对关系只会给出一次。

**【提示】**

- 请注意输入的第一行先读入 $m$，再读入 $n$。


---

---
title: "【模板】二分图最大匹配"
layout: "post"
diff: 普及+/提高
pid: P3386
tag: ['O2优化', '二分图']
---
# 【模板】二分图最大匹配
## 题目描述

给定一个二分图，其左部点的个数为 $n$，右部点的个数为 $m$，边数为 $e$，求其最大匹配的边数。

左部点从 $1$ 至 $n$ 编号，右部点从 $1$ 至 $m$ 编号。
## 输入格式

输入的第一行是三个整数，分别代表 $n$，$m$ 和 $e$。

接下来 $e$ 行，每行两个整数 $u, v$，表示存在一条连接左部点 $u$ 和右部点 $v$ 的边。
## 输出格式

输出一行一个整数，代表二分图最大匹配的边数。
## 样例

### 样例输入 #1
```
1 1 1
1 1

```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
4 2 7
3 1
1 2
3 2
1 1
4 2
4 1
1 1

```
### 样例输出 #2
```
2

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证：
- $1 \leq n, m \leq 500$。
- $1 \leq e \leq 5 \times 10^4$。
- $1 \leq u \leq n$，$1 \leq v \leq m$。

**不保证给出的图没有重边**。



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
title: "「MCOI-01」Village 村庄"
layout: "post"
diff: 普及+/提高
pid: P6722
tag: ['动态规划 DP', '搜索', '图论', '二分图', '树的直径']
---
# 「MCOI-01」Village 村庄
## 题目背景

今天，珂爱善良的0x3喵酱骑着一匹小马来到了一个村庄。

“诶，这个村庄的布局 ……”   
“好像之前我玩 Ciste 的地方啊 qwq”

0x3喵酱有一个地图，地图有着这个村庄的信息。

然后0x3喵酱要通过这张地图来判断 Ciste 有解无解啦 ~

注：Ciste 是《请问您今天要来点兔子吗》中的一种藏宝图游戏
## 题目描述

村庄被简化为一个 $n$ 个节点（编号为 $1$ 到 $n$）和 $n-1$ 条边构成的无向连通图。

0x3喵酱认为这个无向图里的信息跟满足以下条件的新图有关：

- 新图的点集与原图相同
- 在新图中 $u,v$ 之间有无向边 是 在原图中 $dis(u,v) \ge k$ 的**充分必要条件** （$k$ 为给定常量，$dis(u,v)$ 表示编号为 $u$ 的点到编号为 $v$ 的点最短路的长度）

0x3喵酱还认为这个"新图"如果为二分图，则 Ciste "有解"，如果"新图"不是二分图这个 Ciste "无解"。（如果您不知道二分图请翻到提示）

那么0x3喵酱想请您判断一下这个 Ciste 是否"有解"。
## 输入格式

第一行包含一个正整数 $ T $，表示有 $ T $ 组数据。  
对于每组数据第一行包含两个正整数 $ n,k $。接下来 $ n-1 $ 行，每行包含三个正整数 $ x,y,v $ 表示编号为 $ x $ 的点到编号为 $ y $ 的点有一条边权为 $ v $  的无向边。  
输入数据保证合法。

## 输出格式

对于每一组数据包含一行，如果“有解”输出 `Yes`，否则输出 `Baka Chino`。
## 样例

### 样例输入 #1
```
5
5 2
1 2 1
2 3 1
3 4 1
4 5 1
5 3
1 2 1
2 3 1
3 4 1
4 5 1
5 8
1 3 3
1 2 1
2 4 6
2 5 2
5 2
1 3 3
1 2 1
2 4 6
2 5 2
7 4
1 2 3
1 3 3
2 5 3
2 6 3
3 7 3
2 4 2
```
### 样例输出 #1
```
Baka Chino
Yes
Yes
Baka Chino
Baka Chino
```
## 提示

#### 样例解析

对于样例中的 **第一组** 数据：

原图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9f9zh4b2.png)
新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dg4es91e.png)

新图不为二分图，故输出 `Baka Chino`。

对于 **第三组** 数据：

原图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mku4v6uo.png)

新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/15o3x3zz.png)

新图为二分图，故输出 `Yes`。

#### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 1（16 pts）$\ $ ：$n \le 10$。
- Subtask 2（24 pts）$\ $ ：$n \le 100$。
- Subtask 3（8 pts）$\ $ ：$n \le 1000$。
- Subtask 4（28 pts）：图退化成一条链。
- Subtask 5（24 pts）：无特殊限制。

对于 $100\%$ 的数据，$n \le 10^5$，$T \le 10$，$v \le 1000$，$k \le 1000000$。

本题数据使用 [CYaRon](https://www.luogu.org/discuss/show?postid=11410) 生成。

#### 提示


**二分图** 又称作二部图，是图论中的一种特殊模型。设 $G=(V,E)$ 是一个无向图，如果顶点 $V$ 可分割为两个互不相交的子集 $(A,B)$，并且图中的每条边 $(i,j)$ 所关联的两个顶点 $i$ 和 $j$ 分别属于这两个不同的顶点集 $(i \in A,j \in B)$，则称图 $G$ 为一个二分图。（摘自[百度百科](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E5%9B%BE/9089095?fr=aladdin)）

#### 说明

Minecraft OI Round 1 A

- Idea：0x3喵酱
- Solution/Std：0x3喵酱
- Data：0x3喵酱
- Tester：tarjin


---

---
title: "[NOIP2023] 三值逻辑"
layout: "post"
diff: 普及+/提高
pid: P9869
tag: ['并查集', '2023', 'NOIP 提高组', 'O2优化', '二分图', '基环树']
---
# [NOIP2023] 三值逻辑
## 题目描述

小 L 今天学习了 Kleene 三值逻辑。

在三值逻辑中，一个变量的值可能为：真（$\mathit{True}$，简写作 $\mathit{T}$）、假（$\mathit{False}$，简写作 $\mathit{F}$）或未确定（$\mathit{Unknown}$，简写作 $\mathit{U}$）。

在三值逻辑上也可以定义逻辑运算。由于小 L 学习进度很慢，只掌握了逻辑非运算 $\lnot$，其运算法则为：
$$\lnot \mathit{T} = \mathit{F}, \lnot \mathit{F} = \mathit{T}, \lnot\mathit{U} = \mathit{U}.$$

现在小 L 有 $n$ 个三值逻辑变量 $x_1,\cdots, x_n$。小 L 想进行一些有趣的尝试，于是他写下了 $m$ 条语句。语句有以下三种类型，其中 $\leftarrow$ 表示赋值：

1. $x_i \leftarrow v$，其中 $v$ 为 $\mathit{T}, \mathit{F}, \mathit{U}$ 的一种；
2. $x_i \leftarrow x_j$；
3. $x_i \leftarrow \lnot x_j$。

一开始，小 L 会给这些变量赋初值，然后按顺序运行这 $m$ 条语句。

小 L 希望执行了所有语句后，所有变量的最终值与初值都相等。在此前提下，小 L 希望初值中 $\mathit{Unknown}$ 的变量尽可能少。

在本题中，你需要帮助小 L 找到 $\mathit{Unknown}$ 变量个数最少的赋初值方案，使得执行了所有语句后所有变量的最终值和初始值相等。小 L 保证，至少对于本题的所有测试用例，这样的赋初值方案都必然是存在的。
## 输入格式

**本题的测试点包含有多组测试数据。**

输入的第一行包含两个整数 $c$ 和 $t$，分别表示测试点编号和测试数据组数。对于样例，$c$ 表示该样例与测试点 $c$ 拥有相同的限制条件。

接下来，对于每组测试数据：

- 输入的第一行包含两个整数 $n$ 和 $m$，分别表示变量个数和语句条数。
- 接下来 $m$ 行，按运行顺序给出每条语句。
  - 输入的第一个字符 $v$ 描述这条语句的类型。保证 $v$ 为 `TFU+-` 的其中一种。
  - 若 $v$ 为 `TFU` 的某一种时，接下来给出一个整数 $i$，表示该语句为 $x_i \leftarrow v$；
  - 若 $v$ 为 `+`，接下来给出两个整数 $i,j$，表示该语句为 $x_i \leftarrow x_j$；
  - 若 $v$ 为 `-`，接下来给出两个整数 $i,j$，表示该语句为 $x_i \leftarrow \lnot x_j$。
## 输出格式

对于每组测试数据输出一行一个整数，表示所有符合条件的赋初值方案中，$\mathit{Unknown}$ 变量个数的最小值。
## 样例

### 样例输入 #1
```
1 3
3 3
- 2 1
- 3 2
+ 1 3
3 3
- 2 1
- 3 2
- 1 3
2 2
T 2
U 2

```
### 样例输出 #1
```
0
3
1

```
## 提示

**【样例解释 #1】**

第一组测试数据中，$m$ 行语句依次为

- $x_2 \leftarrow \lnot x_1$；
- $x_3 \leftarrow \lnot x_2$；
- $x_1 \leftarrow x_3$。

一组合法的赋初值方案为 $x_1 = \mathit{T}, x_2 = \mathit{F}, x_3 = \mathit{T}$，共有 $0$ 个$\mathit{Unknown}$ 变量。因为不存在赋初值方案中有小于 $0$ 个$\mathit{Unknown}$ 变量，故输出为 $0$。

第二组测试数据中，$m$ 行语句依次为

- $x_2 \leftarrow \lnot x_1$；
- $x_3 \leftarrow \lnot x_2$；
- $x_1 \leftarrow \lnot x_3$。

唯一的赋初值方案为 $x_1 = x_2 = x_3 = \mathit{U}$，共有 $3$ 个$\mathit{Unknown}$ 变量，故输出为 $3$。

第三组测试数据中，$m$ 行语句依次为

- $x_2 \leftarrow \mathit{T}$；
- $x_2 \leftarrow \mathit{U}$；

一个最小化 $\mathit{Unknown}$ 变量个数的赋初值方案为 $x_1 = \mathit{T}, x_2 = \mathit{U}$。$x_1 = x_2 = \mathit{U}$ 也是一个合法的方案，但它没有最小化 $\mathit{Unknown}$ 变量的个数。

**【样例解释 #2】**

该组样例满足测试点 $2$ 的条件。

**【样例解释 #3】**

该组样例满足测试点 $5$ 的条件。

**【样例解释 #4】**

该组样例满足测试点 $8$ 的条件。

**【数据范围】**

对于所有测试数据，保证：

- $1 \le t \le 6$，$1 \le n,m \le 10 ^ 5$；
- 对于每个操作，$v$ 为 `TFU+-` 中的某个字符，$1 \le i,j \le n$。

| 测试点编号 | $n,m\leq$ | $v$ 可能的取值 |
| :----------: | :----------: | :----------: |
| $1,2$ | $10$ | $\mathit{TFU+-}$ |
| $3$ | $10^3$ | $\mathit{TFU}$ |
| $4$ | $10^5$ | $\mathit{TFU}$ |
| $5$ | $10^3$ | $\mathit{U+}$ |
| $6$ | $10^5$ | $\mathit{U+}$ |
| $7$ | $10^3$ | $\mathit{+-}$ |
| $8$ | $10^5$ | $\mathit{+-}$ |
| $9$ | $10^3$ | $\mathit{TFU+-}$ |
| $10$ | $10^5$ | $\mathit{TFU+-}$ |


---

