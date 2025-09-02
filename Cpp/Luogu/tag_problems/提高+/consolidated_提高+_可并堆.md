---
title: "BZOJ3252 攻略"
layout: "post"
diff: 提高+/省选-
pid: P10641
tag: ['贪心', '线段树', 'O2优化', '可并堆', '树链剖分']
---
# BZOJ3252 攻略
## 题目背景

众所周知，桂木桂马是攻略之神，开启攻略之神模式后，他可以同时攻略 $k$ 部游戏。

今天他得到了一款新游戏《XX 半岛》，这款游戏有 $n$ 个场景，某些场景可以通过不同的选择支到达其他场景。所有场景和选择支构成树状结构：开始游戏时在根节点（共通线），叶子节点为结局。每个场景有一个价值，现在桂马开启攻略之神模式，同时攻略 $k$ 次该游戏，问他观赏到的场景的价值和最大是多少？（同一场景观看多次是不能重复得到价值的）

>“为什么你还没玩就知道每个场景的价值呢？”  
>“我已经看到结局了。”
## 题目描述

给定一个有 $n$ 个结点的树，树有点权且点权为正整数。现选取 $k$ 条从根结点出发到叶子结点的简单路径，求这些路径的并集上所有结点的点权之和的最大值。
## 输入格式

第一行两个正整数 $n,k$。

第二行输入 $n$ 个正整数 $w_i$，表示每个结点的点权。

第三行输入 $n-1$ 行，每行 $2$ 个正整数 $u,v$，表示结点 $u$ 是结点 $v$ 的父亲。
## 输出格式

输出一个正整数，表示答案。
## 样例

### 样例输入 #1
```
5 2
4 3 2 1 1
1 2
1 5
2 3
2 4
```
### 样例输出 #1
```
10
```
## 提示

对于所有数据，保证 $1\leq n\leq 2\times 10^5$，$1\leq w_i\leq 2^{31}-1$。


---

---
title: "【模板】可并堆 2"
layout: "post"
diff: 提高+/省选-
pid: P11266
tag: ['可并堆']
---
# 【模板】可并堆 2
## 题目背景

感谢 @[Spasmodic](https://www.luogu.com.cn/user/121027) 提供初版数据生成器。

[gen](https://www.luogu.com.cn/paste/4vk36jsp)。
## 题目描述

给定正整数 $n$ 和 $m$ 以及一个长为 $n$ 的整数序列 $a_{1,\dots,n}$。

你需要维护序列 $a_{1,\dots,n}$ 以及 $n$ 个集合 $S_{1,\dots,n}$，初始时 $S_i=\{i\}$。

接下来要进行以下四种操作共 $m$ 次，每次操作形如：

- `0 x y`：表示将元素 $y$ 从集合 $S_x$ 中删去。保证此时元素 $y$ 在集合 $S_x$ 中。
- `1 x`：表示询问 $\min_{i\in S_x} a_i$，保证此时集合 $S_x$ 非空。
- `2 x y`：将集合 $S_y$ 中并入 $S_x$ 并清空集合 $S_y$。保证此时集合 $S_x,S_y$ 均非空，且此次操作后不会再出现涉及集合 $S_y$ 的操作。
- `3 x y z`：表示将 $a_y$ 赋值为 $z$。保证此时元素 $y$ 在集合 $S_x$ 中，且 $z<a_y$。

不难发现这是一道堆的模板题，所以现在请你完成它。
## 输入格式

第一行两个正整数 $n$ 和 $m$。

第二行 $n$ 个正整数，第 $i$ 个正整数表示 $a_i$。

接下来 $m$ 行每行一个操作如题。
## 输出格式

对于每个 `1` 操作一行整数（注意不保证依然为正）表示答案。
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 4
2 4 5
3 4 5 3
1 4
0 4 5
1 4
```
### 样例输出 #1
```
3
4
```
## 提示

对于 $20\%$ 的数据，$n=m=10$；

对于 $80\%$ 的数据，$n=m=10^5$；

对于 $100\%$ 的数据，$1\le n,m\le10^6$，$1\le a_i\le2\times10^9$，保证任意时刻任意堆中元素绝对值不超过 $10^{15}$（人话：保证每次 `3` 操作最多单点减 $5\times10^8$）。

---

最后两个点出题人的手写堆和 pbds 的配对堆都跑到了几百毫秒，如果有被卡常的可私。


---

---
title: "Monkey King"
layout: "post"
diff: 提高+/省选-
pid: P1456
tag: ['可并堆']
---
# Monkey King
## 题目描述

Once in a forest, there lived N aggressive monkeys. At the beginning, they each does things in its own way and none of them knows each other. But monkeys can't avoid quarrelling, and it only happens between two monkeys who does not know each other. And when it happens, both the two monkeys will invite the strongest friend of them, and duel. Of course, after the duel, the two monkeys and all of their friends will know each other, and the quarrel above will no longer happen among these monkeys even if they have ever conflicted.


Assume that every money has a strongness value, which will be reduced to only half of the original after a duel(that is, 10 will be reduced to 5 and 5 will be reduced to 2).


And we also assume that every monkey knows himself. That is, when he is the strongest one in all of his friends, he himself will go to duel.
## 输入格式

There are several test cases, and each case consists of two parts.


First part: The first line contains an integer N(N<=100,000), which indicates the number of monkeys. And then N lines follows. There is one number on each line, indicating the strongness value of ith monkey(<=32768).


Second part: The first line contains an integer M(M<=100,000), which indicates there are M conflicts happened. And then M lines follows, each line of which contains two integers x and y, indicating that there is a conflict between the Xth monkey and Yth.
## 输出格式

For each of the conflict, output -1 if the two monkeys know each other, otherwise output the strength value of the strongest monkey among all of its friends after the duel.
## 样例

### 样例输入 #1
```
5
20
16
10
10
4
5
2 3
3 4
3 5
4 5
1 5

```
### 样例输出 #1
```
8
5
5
-1
10

```
## 提示

题目可能有多组数据

题目来源 ZOJ 3rd Anniversary Contest
## 题目翻译

#### 题目描述

曾经在一个森林中居住着 $N$ 只好斗的猴子。在最初他们我行我素，互不认识。但是猴子们不能避免争吵，且两只猴子只会在不认识对方时发生争吵，当争吵发生时，双方会邀请它们各自最强壮的朋友并发起决斗（决斗的为各自最强壮的朋友）。当然，在决斗之后两只猴子和他们各自的伙伴都认识对方了（成为朋友），虽然他们曾经有过冲突，但是他们之间绝不会再发生争吵了。

假设每只猴子有一个强壮值，强壮值将在一场决斗后减少为原先的一半（例如  $10$ 会减少到  $5$，而  $5$ 会减少到  $2$，即向下取整）。

我们也假设每只猴子都认识它自己（是自己的朋友）。即当他是他朋友中最强壮的，他自己就会去决斗。

#### 输入格式

有多组数据，每一组数据有两部分。

第一部分：第一行包含一个整数 $N$ 表示猴子的数量。后为 $N$ 行，每行一个数字为第 $i$ 只猴子的强壮值  $s_{i}$。

第二部分：第一行包含一个整数 $M$ 表示发生了 $M$ 次冲突。后为 $M$ 行，每行两个整数 $x$ 和 $y$，表示第 $x$ 只猴子和第 $y$ 只猴子之间发生了冲突。

#### 输出格式

对于每次冲突，如果两只猴子认识对方，输出 `-1`，否则输出决斗后他们朋友中最强壮的猴子的强壮值。

#### 说明/提示

$N,M\leq 100000$，$s_{i}\leq 32768$


---

---
title: "罗马游戏"
layout: "post"
diff: 提高+/省选-
pid: P2713
tag: ['可并堆']
---
# 罗马游戏
## 题目描述

罗马皇帝很喜欢玩杀人游戏。 他的军队里面有  $n$ 个士兵，每个士兵都是一个独立的团。最近举行了一次平面几何测试，每个士兵都得到了一个分数。 皇帝很喜欢平面几何，他对那些得分很低的士兵嗤之以鼻。

他决定玩这样一个游戏。 它可以发两种命令：

- `M i j` 把  $i$ 所在的团和  $j$ 所在的团合并成一个团。如果  $i,j$ 有一个士兵是死人，那么就忽略该命令。  
- `K i` 把   $i$ 所在的团里面得分最低的士兵杀死。如果  $i$ 这个士兵已经死了，这条命令就忽略。

皇帝希望他每发布一条 `K i` 命令，下面的将军就把被杀的士兵的分数报上来 
（如果这条命令被忽略，那么就报  $0$ 分）。 

保证**士兵的分数互不相同**。
## 输入格式

第一行一个整数  $n$，表示士兵数。  

第二行  $n$ 个整数   $a_1,a_2,\ldots a_n$，其中  $a_i$ 表示编号为   $i$ 的士兵的分数。

第三行一个整数  $m$。

第   $3+i$ 行描述第i条命令。命令为如下两种形式：`M i j` 或 `K i`。
## 输出格式

如果命令是 `K i`，对应的请输出被杀士兵的分数（如果这个人不存在，就输出  $0$）。
## 样例

### 样例输入 #1
```
5
100 90 66 99 10
7
M 1 5
K 1
K 1
M 2 3
M 3 4
K 5
K 4
```
### 样例输出 #1
```
10
100
0
66
```
## 提示

对于   $100\%$ 的数据，  $1\le n\le 10^6$，$1\le m\le 10^5$，$0\le a_i\le 10^7$，
**注意测试数据中 `M i j` 的 $i,j$ 可能在同一个团中。** 


---

---
title: "【模板】左偏树/可并堆"
layout: "post"
diff: 提高+/省选-
pid: P3377
tag: ['可并堆']
---
# 【模板】左偏树/可并堆
## 题目描述

如题，一开始有 $n$ 个小根堆，每个堆包含且仅包含一个数。接下来需要支持两种操作：

1. `1 x y`：将第 $x$ 个数和第 $y$ 个数所在的小根堆合并（若第 $x$ 或第 $y$ 个数已经被删除或第 $x$ 和第 $y$ 个数在同一个堆内，则无视此操作）。

2. `2 x`：输出第 $x$ 个数所在的堆最小数，并将这个最小数删除（若有多个最小数，优先删除先输入的；若第 $x$ 个数已经被删除，则输出 $-1$ 并无视删除操作）。
## 输入格式

第一行包含两个正整数 $n, m$，分别表示一开始小根堆的个数和接下来操作的个数。

第二行包含 $n$ 个正整数，其中第 $i$ 个正整数表示第 $i$ 个小根堆初始时包含且仅包含的数。

接下来 $m$ 行每行 $2$ 个或 $3$ 个正整数，表示一条操作，格式如下：

操作 $1$：`1 x y`

操作 $2$：`2 x`
## 输出格式

输出包含若干行整数，分别依次对应每一个操作 $2$ 所得的结果。
## 样例

### 样例输入 #1
```
5 5
1 5 4 2 3
1 1 5
1 2 5
2 2
1 4 2
2 2
```
### 样例输出 #1
```
1
2

```
## 提示

**【数据规模】**

对于 $30\%$ 的数据：$n\le 10$，$m\le 10$。  
对于 $70\%$ 的数据：$n\le 10^3$，$m\le 10^3$。  
对于 $100\%$ 的数据：$n\le 10^5$，$m\le 10^5$，初始时小根堆中的所有数都在 `int` 范围内。

**【样例解释】**

初始状态下，五个小根堆分别为：$\{1\}$、$\{5\}$、$\{4\}$、$\{2\}$、$\{3\}$。

第一次操作，将第 $1$ 个数所在的小根堆与第 $5$ 个数所在的小根堆合并，故变为四个小根堆：$\{1,3\}$、$\{5\}$、$\{4\}$、$\{2\}$。

第二次操作，将第 $2$ 个数所在的小根堆与第 $5$ 个数所在的小根堆合并，故变为三个小根堆：$\{1,3,5\}$、$\{4\}$、$\{2\}$。

第三次操作，将第 $2$ 个数所在的小根堆的最小值输出并删除，故输出 $1$，第一个数被删除，三个小根堆为：$\{3,5\}$、$\{4\}$、$\{2\}$。

第四次操作，将第 $4$ 个数所在的小根堆与第 $2$ 个数所在的小根堆合并，故变为两个小根堆：$\{2,3,5\}$、$\{4\}$。

第五次操作，将第 $2$ 个数所在的小根堆的最小值输出并删除，故输出 $2$，第四个数被删除，两个小根堆为：$\{3,5\}$、$\{4\}$。

故输出依次为 $1$、$2$。


---

