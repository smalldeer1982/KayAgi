---
title: "[GCJ 2014 #3] Willow"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13263
tag: ['动态规划 DP', '博弈论', '2014', '记忆化搜索', '树形 DP', 'Google Code Jam']
---
# [GCJ 2014 #3] Willow
## 题目描述

Hanaa and Sherine are playing Willow, a game that is played on a board containing $\mathbf{N}$ cities. The $\mathrm{i}^{\text {th }}$ city contains $\mathbf{C}_{\mathrm{i}}$ coins, and there are $\mathbf{N}-1$ bidirectional roads running between the cities. All cities are reachable from one another. The game is played as follows:

First Hanaa chooses one of the cities as her starting location, then Sherine chooses one of the cities (possibly the same one Hanaa chose) as her starting location. Afterwards, they take turns playing the game, with Hanaa going first.

On a player's turn, that player must take all the coins on the city where she currently is, if there are any; there might be none if the city starts with no coins, or if one of the players has already started a turn in that city. Then, if possible, the player must travel to an adjacent city on a road. It might not be possible, because each road can be used at most once. This means that after one player has used a road, neither player is allowed to use the same road later. The game ends when neither Hanaa nor Sherine can make a move.

After the game ends, each player's score is equal to the difference between the number of coins she has and the number of coins her opponent has. If her opponent has more coins, this means that her score will be negative. Both players are trying to maximize their scores. Assuming that they are both using the best possible strategy to maximize their scores, what is the highest score that Hanaa can obtain?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing one integer $\mathbf{N}$, the number of cities on the board. $\mathbf{N}$ lines then follow, with the $\mathrm{i}^{\text {th }}$ line containing an integer $\mathbf{C}_{\mathrm{i}}$, the number of coins in city $\mathrm{i}$.

Finally there will be another $\mathbf{N}-1$ lines, with the $\mathrm{i}^{\text {th }}$ line $(\mathrm{i}$ starts from 1$)$ containing a single integer $\mathrm{j}(\mathrm{i}<\mathrm{j} \leq \mathbf{N})$ indicating that there is a road between city $\mathrm{i}$ and city $\mathrm{j}$. All cities are guaranteed to be reachable from one another at the start of the game.

## 输出格式

For each test case, output one line containing "Case #x: $y$", where $\mathrm{x}$ is the case number (starting from 1) and $y$ is the highest score that Hanaa can obtain.
## 样例

### 样例输入 #1
```
3
3
1000
200
1000
2
3
8
8
0
8
0
0
0
0
10
2
5
4
5
6
7
8
10
150
200
0
5000
0
100
0
0
0
10000
10
3
8
5
8
7
8
9
10
```
### 样例输出 #1
```
Case #1: 200
Case #2: -2
Case #3: 5100
```
## 提示

**Limits**

- Memory limit: 1 GB.
- $1 \leq \mathbf{T} \leq 50 .$
- $0 \leq \mathbf{C}_{\mathrm{i}} \leq 10000 .$

**Small dataset(15 Pts)**

- Time limit: ~~60~~ 30 seconds.
- $2 \leq \mathbf{N} \leq 80 .$

**Large dataset(24 Pts)**

- Time limit: ~~120~~ 30 seconds.
- $2 \leq \mathbf{N} \leq 500 .$



---

---
title: "[CQOI2015] 标识设计"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3170
tag: ['动态规划 DP', '搜索', '2015', '重庆', '各省省选', '记忆化搜索']
---
# [CQOI2015] 标识设计
## 题目描述

一家名字缩写为 LLL 的公司正在设计 logo，他们的初步方案是在一张方格上放置 $3$ 个 L 形的图案以及一些额外的装饰性图形，例如：![](https://cdn.luogu.com.cn/upload/pic/15558.png)  （灰色区域表示装饰性图形）。

$3$ 个 L 图案和装饰性图形均放置在方格之中，且必须占满方格。L 的横竖笔画长短均可，但长度必须大于 $0$（即不能退化为一条线段）。另外，为了使 L 图案醒目且容易辨别，设计师规定 $3$ 个 L 形图案之间不能有重叠或交叉的部分。当然，L 形图案也不能穿过装饰图形或与之重叠。

现在设计师已经确定了所有装饰性图形的位置，希望你计算一下放置不同的 L 形图案总共可以设计出多少个 logo。

## 输入格式

第一行包含两个空格分开的正整数 $n$ 和 $m$，分别表示方格的行数和列数。

接下来 $n$ 行，每行 $m$ 个字符，第 $(i + 1)$ 行第 $j$ 个字符代表第 $i$ 行第 $j$ 列的图形，该字符只可能为 `.` 或 `#`。`#` 表示该方格为装饰性图形，`.` 表示可以放置 L 图案的空白区域。
## 输出格式

输出一个整数，为可能的logo总数。

## 样例

### 样例输入 #1
```
4 4
....
#...
....
..#.
```
### 样例输出 #1
```
4
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le n,m\leq 30$。


---

---
title: "辉夜姬的十道难题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3798
tag: ['模拟', '动态规划 DP', '搜索', '贪心', '洛谷原创', '提交答案', '剪枝', '记忆化搜索']
---
# 辉夜姬的十道难题
## 题目背景

妹红最近玩了一款叫 $2048$ 的小游戏。

![](https://cdn.luogu.com.cn/upload/pic/5857.png)

(图为个人无撤销最高纪录~ 纯手玩)。
## 题目描述

$2048$ 是一个非常简单的数字游戏，它在 $4\times 4$ 的棋盘上进行，通过移动来合并数字，达到 $2048$ 即算胜利。妹红最近沉迷上了这个游戏，事情传到辉夜那里后，辉夜决定用曾经无人破解的十道难题来考考妹红。

游戏规则：

1. 游戏在 $n\times m$ 的方格棋盘上进行。

2. 两个玩家，其中一个可以移动棋盘上的数字，记做 M，另外一个可以向棋盘上放数字，记做 C。

3. 移动数字的规则如下：可以向上/下/左/右四个方向的其中之一移动。选定好方向后，所有数字都会向该方向靠拢，相同的两个数字相撞时会合并成一个新数字，这个数字是它们的和。在一次移动中，每个数字最多只能合并一次，优先合并靠近移动方向棋盘边缘的数字。

以 $n=2,m=4$ 的情况举例如下（$0$ 表示该位置为空）：

```
2 2 2 2
2 2 0 2
```

向左移动后变为：

```
4 4 0 0
4 2 0 0
```

每次合并后，将会获得一定的分数，获得的分数等于所有合并后数字相加之和。若无任何合并发生，则不得分。在上例中，得分为 $12$。

移动前后，若棋盘上的所有数字大小和位置均没有变化，则不算做有效移动，否则即是有效移动。

4. 向棋盘放置数字的规则如下：只能选择棋盘上没有数字的位置放置一个数字，可以放置的数字和放置方法在每个子任务中会具体描述。

5. 游戏开始时棋盘为空，分数为 $0$。先由玩家 C 行动两步，接着玩家 M 和 C 轮流行动，中间的每一步都必须是有效的。当轮到玩家 M 时，若不能够进行有效移动，则游戏结束，此时的得分为最终得分。

本题目为提交答案题，共有 $10$ 个子任务需要你来完成。将你的答案写到 $10$ 个文件中，分别命名为 ```gamex.out```，$x$ 表示子任务的编号（$0\ldots 9$）。

子任务内无部分分，你可以得到该任务的分数当且仅当你的输出和标准答案完全相同。

十道难题如下:

0. $n=1,m=2$。玩家 C 行动时可以放置 $2$ 或 $4$。若用 $x$ 表示在一局游戏中玩家 M 最多可以行动 $x$ 次，那么这个 $x$ 的最值是多少？输出两行，第一行一个整数表示 $x$ 的最小值，第二行一个整数表示 $x$ 的最大值。

1. $n=10738029,m=921023$。玩家 C 行动时可以放置 $2$ 或 $4$。若用 $x$ 表示棋盘上所有数字之和，请问 $x$ 的最大值是多少。因为这个值可能过大，只需要输出它除以 $10^9+7$ 的余数即可。

2. $n=2,m=2$。玩家 C 行动时可以放置 $2,4$。用 $x$ 表示目标数字， $x$ 一定为 $2$ 的正整数幂。玩家 M 的目标是使盘面上出现大于等于数字 $x$ 的数，玩家 C 的目标是在盘面上出现数字 $x$ 之前使游戏结束。在两方均最优决策的情况下，求一个最大的 $x$，使得玩家 M 能达到自己的目标。

3. $n=4,m=4$。玩家 C 行动时可以放置 $2,4$。输出两行，每行一个数字。第一行的数字表示能达到的最大分数。第二行的数字表示当数字总和达到最大时，分数的最小值。

4. $n=7393,m=9133$。玩家 C 可以放置数字 $2$ 共 $6144$ 次。棋盘初始为空，初始分数为 $0$。首先由玩家 C 连续行动，直到用完所有放置机会或中途主动放弃。然后连续向上移动直到向上方向不能构成有效移动。输出一行一个整数，表示最大得分。

5. $n=7,m=233$。初始分数为 $0$,玩家 C 可以放置数字 $2$ 共 $233$ 次，数字 $4$ 共 $66$ 次。棋盘第一行一开始有若干数字，第 $i$ 列的数字为 $\text{lowbit}(i)\times 2$，$\text{lowbit}(i)$ 表示数字 $i$ 的二进制形式只取最后一个 $1$ 构成的数字。如 $\text{lowbit}(1\ldots 8)$ 为 $1,2,1,4,1,2,1,8$。棋盘的其他位置均为空。首先由玩家 C 连续行动，直到用完所有放置机会或中途主动放弃。然后连续向上移动直到向上方向不能构成有效移动。输出一行一个整数，表示最大得分。

6. $n=3,m=3$。玩家 C 行动时可以放置 $2,4$。用 $x$ 表示目标数字，$x$ 一定为 $2$ 的正整数幂。玩家 M 的目标是使盘面上出现数字 $x$，玩家 C 的目标是在盘面上出现数字 $x$ 之前使游戏结束。在两方均最优决策的情况下，输出一个最大的 $x$，使得玩家 M 能达到自己的目标。

7. $n=3,m=3$。玩家 C 行动时可以放置 $2,4$。玩家 M 的目标是让得分最大化，玩家 C 的目标是让得分最小化，在两方均最优决策的情况下，输出一个整数，表示最终的分数。

8. $n=3,m=3$。玩家 C 行动时，有 $90\%$ 的几率放置一个 $2$，$10\%$ 的几率放置一个 $4$，放置在各个空位的几率均等。用 $x$ 表示目标数字，玩家 M 的目标是使盘面上出现大于等于数字 $x$ 的数。在玩家 M 最优决策的情况下，输出一行，$9$ 个实数，四舍五入到小数点后 $2$ 位，用空格隔开，分别表示 $x=2,4,8,16,32,64,128,256,512$ 时，达成目标数字的概率。

9. $n=3,m=3$。玩家 C 行动时，有 $90\%$ 的几率放置一个 $2$，$10\%$ 的几率放置一个 $4$，放置在各个空位的几率均等。玩家 M 的目标是让分数最大化。在玩家 M 最优决策的情况下，输出一个实数，四舍五入保留整数，表示分数的期望值。

妹红虽然对 $2048$ 有一定了解，但她并不能解决全部的问题，于是就交给了学 OI 的你。
## 输入格式

见题目描述

## 输出格式

见题目描述

## 样例

### 样例输入 #1
```
样例任务（无需提交）:
 n=2,m=2。 玩家C行动时只可以放置2。请输出一个整数，表示棋盘上可能出现的最大数字。

```
### 样例输出 #1
```
16
```
## 提示

如果对移动规则有疑惑，可以到 $2048$ 网站进行尝试:

http://gabrielecirulli.github.io/2048/

by-orangebird



---

---
title: "[THUWC 2017] 随机二分图"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4547
tag: ['搜索', '2017', '记忆化搜索', 'THUWC', '状压 DP']
---
# [THUWC 2017] 随机二分图
## 题目背景

# 滥用本题评测将被封号
## 题目描述

某人在玩一个非常神奇的游戏。这个游戏中有一个左右各 $n$ 个点的二分图，图中的边会按照一定的规律随机出现。

为了描述这些规律，某人将这些边分到若干个组中。每条边或者不属于任何组 （这样的边一定不会出现），或者只属于一个组。

有且仅有以下三类边的分组：

0.  这类组每组只有一条边，该条边恰好有 $50\%$ 的概率出现。

1. 这类组每组恰好有两条边，这两条边有 $50\%$ 的概率同时出现，有 $50\%$ 的概率同时不出现。
2. 这类组每组恰好有两条边，这两条边恰好出现一条，各有 $50\%$ 的概率出现。

组和组之间边的出现都是完全独立的。

某人现在知道了边的分组和组的种类，想要知道完美匹配数量的期望是多少。你能帮助她解决这个问题吗？
## 输入格式

从标准输入读入数据。

第一行两个数 $n$ 和 $m$，表示图左右点数的数量和边的组的个数。我们用 $(a,b)$ （其中 $1 \le a,b \le n$）表示一条左端点为二分图左侧第 $a$ 个点，右端点为二分图右侧第 $b$ 个点的边。

接下来 $m$ 行，每行描述一个组。开头第一个数 $t$ 表示组的种类，$t=0$ 表示是一条边的组，$t=1$ 表示是两条边的组中的第一种，$t=2$ 表示是两条边的组中的第二种。如果 $t=0$， 接下来两个数 $a_1,b_1$ 表示组内的第一条边；否则，接下来四个数 $a_1,b_1,a_2,b_2$， 表示该组内的两条边分别为 $(a_1,b_1)$  和 $(a_2,b_2)$。保证每条边至多出现一次。
## 输出格式

输出到标准输出。

假设期望的完美匹配数量是$E$。输出一行表示
$$
(2^{n} E) \bmod (10^9 + 7)
$$
可以看出上式一定是一个整数。
## 样例

### 样例输入 #1
```
2 2
1 2 1 2 2
2 1 2 1 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 5
1 1 2 3 3
1 3 2 2 2
1 1 1 1 3
1 2 1 3 1
0 2 3
```
### 样例输出 #2
```
7
```
### 样例输入 #3
```
4 9
2 4 1 4 2
1 3 2 1 4
2 2 1 4 4
2 3 4 1 1
2 4 3 2 4
2 2 2 3 1
0 1 3
0 3 3
1 2 3 1 2
```
### 样例输出 #3
```
20
```
## 提示

## 【定义解释】

如果你对完美匹配和期望的定义很熟悉，那么你可以跳过本段。

对于一个左右各 $n$ 个点的二分图，它的一个完美匹配是指 $n$ 条没有公共点的边构成的匹配。

两个完美匹配不同，当且仅当它们至少含有一条不同的边。一个二分图完美匹配的数量定义为这张图能找到的两两不同的完美匹配的数量。

在题目的图中，边都是随机出现的，因此这个图中完美匹配的数量是一个随机变量。一个（离散型）随机变量 $X$ 的期望定义为以概率为权，$X$ 所有可能取值的加权平均数，即
$$
\sum_{x \in V(X)}P[X=x]\cdot x
$$
其中 $V(X)$ 表示 $X$ 所有可能的取值集合，$P[X=x]$ 表示 $X$ 取值为 $x$ 的概率。

## 【数据规模和约定】

对于 $5\%$ 的数据 $n \le 5$ 。  
对于另 $5\%$ 的数据 $n \le 8$ 。  
对于另 $10\%$ 的数据 $n \le 10$ 。  
对于另 $15\%$ 的数据，只有$t = 0$ 的情况。  
对于另 $5\%$ 的数据，只有$t = 0$ 的情况，且$m = n^2$，也就是该图为一个完全图。  
对于另 $20\%$ 的数据，只有 $t =0$ 或者 $t=1$ 的情况。
对于另 $20\%$ 的数据，只有 $t =0$ 或者 $t=2$ 的情况。
对于 $100\%$ 的数据，$n \le 15$。


---

