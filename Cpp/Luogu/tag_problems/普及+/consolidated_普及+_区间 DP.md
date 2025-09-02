---
title: "[中山市赛 2023] 永别"
layout: "post"
diff: 普及+/提高
pid: B4336
tag: ['动态规划 DP', '2023', '广东', '区间 DP', '科创活动', '小学活动']
---
# [中山市赛 2023] 永别
## 题目描述

你做了一个梦，梦里有一个字符串，这个字符串无论正着读还是倒着读都是一样的，例如：$\tt abcba$ 就符合这个条件。

但是你醒来时不记得梦中的字符串是什么，只记得它是另一个字符串 $S$ 的子序列，你想知道梦中字符串最长是多少。

提示：字符串 $A$ 是字符串 $B$ 的子序列当且仅当从 $B$ 中删除若干个字符（可以不删）后可以变成 $A$。例如：$\tt acd$ 是 $\tt achda$ 的子序列，因为从 $\tt achda$ 中删去第 $3$ 个和第 $5$ 个字符后就是 $\tt acd$。 
## 输入格式

第一行一个正整数 $len$，表示字符串 $S$ 的长度。

第二行一个长度为 $len$ 的字符串，表示字符串 $S$。 
## 输出格式

第一行包含一个整数，表示梦中字符串最长的长度。 
## 样例

### 样例输入 #1
```
7
acbdcaa
```
### 样例输出 #1
```
5
```
## 提示

### 样例解释

从 $\tt acbdcaa$ 中删去第 $4$ 个和第 $7$ 个字符后变成 $\tt acbca$ 就满足正着读还是倒着读都是一样，不难发
现这是最长的。 

### 数据范围

对于 $15\%$ 的数据，$len \le 20$。

对于 $30\%$ 的数据，$len \le 200$。

对于 $45\%$ 的数据，$len \le 700$。

对于另外 $15\%$ 的数据，$len \le 800$，字符串中只会出现字母 $\tt a$ 和 $\tt b$。

对于 $100\%$ 的数据，$3 \le len \le 1000$，字符串中只会出现英文小写字母。


---

---
title: "[NOIP 2007 提高组] 矩阵取数游戏"
layout: "post"
diff: 普及+/提高
pid: P1005
tag: ['动态规划 DP', '高精度', '2007', 'NOIP 提高组', '区间 DP']
---
# [NOIP 2007 提高组] 矩阵取数游戏
## 题目描述

帅帅经常跟同学玩一个矩阵取数游戏：对于一个给定的 $n \times m$ 的矩阵，矩阵中的每个元素 $a_{i,j}$ 均为非负整数。游戏规则如下：

1. 每次取数时须从每行各取走一个元素，共 $n$ 个。经过 $m$ 次后取完矩阵内所有元素；
2. 每次取走的各个元素只能是该元素所在行的行首或行尾；
3. 每次取数都有一个得分值，为每行取数的得分之和，每行取数的得分 = 被取走的元素值 $\times 2^i$，其中 $i$ 表示第 $i$ 次取数（从 $1$ 开始编号）；
4. 游戏结束总得分为 $m$ 次取数得分之和。

帅帅想请你帮忙写一个程序，对于任意矩阵，可以求出取数后的最大得分。

## 输入格式

输入文件包括 $n+1$ 行：

第一行为两个用空格隔开的整数 $n$ 和 $m$。

第 $2\sim n+1$ 行为 $n \times m$ 矩阵，其中每行有 $m$ 个用单个空格隔开的非负整数。





## 输出格式

输出文件仅包含 $1$ 行，为一个整数，即输入矩阵取数后的最大得分。
## 样例

### 样例输入 #1
```
2 3
1 2 3
3 4 2

```
### 样例输出 #1
```
82
```
## 提示

**【数据范围】**

对于 $60\%$ 的数据，满足 $1\le n,m\le 30$，答案不超过 $10^{16}$。  
对于 $100\%$ 的数据，满足 $1\le n,m\le 80$，$0\le a_{i,j}\le1000$。

**【题目来源】**

NOIP 2007 提高第三题。






---

---
title: "[LMXOI Round 1] Placer"
layout: "post"
diff: 普及+/提高
pid: P10115
tag: ['动态规划 DP', '枚举', '区间 DP']
---
# [LMXOI Round 1] Placer
## 题目背景

LMX 最近迷上了括号序列，她尤其钟爱合法括号序列。

LMX 为了检验 HQZ 的真诚，于是她出一道题准备考验下 HQZ。

## 题目描述

LMX 给出了一个长度为 $n$ 括号序列 $S$，以及一个长度为 $n$ 的序列 $a_i$。

定义 $w(l,r)=
\begin{cases}
a_r-a_l, & S_{l..r} \text{为合法括号序列}\\
\ 0 & \text{otherwise}
\end{cases}$

你可以将序列分成若干非空子段，定义整个序列的美丽度为每段的 $w(l , r)$ 之和。

求美丽度最大为多少。
## 输入格式

第一行一个整数 $n$。

第二行一个字符串，代表括号序列。

第三行代表序列 $a$。
## 输出格式

第一行一个整数，表示最大的美丽度。
## 样例

### 样例输入 #1
```
5
()(()
1 3 2 3 5
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
10
()((())())
2 4 1 7 3 2 8 4 9 5
```
### 样例输出 #2
```
8
```
## 提示

**样例解释 #1**

原串可以划分成三个区间：$[1,2],[3,3],[4,5]$。贡献为 $(a_2-a_1)+0+(a_5-a_4)=(3-1)+0+(5-3)=4$

| 子任务编号 | $n$ | 特殊性质 | 分值 |
| :--------: | :--------: | :-------------: | :--: |
| Subtask #1 | $\le 5000$ | 无 | $30$ |
| Subtask #2 | $\le 10 ^ 5$ | 无 | $20$ |
| Subtask #3 | $\le 3 \times 10 ^ 6$ | 括号序列为 $()()\dots()$ | $15$ |
| Subtask #4 | $\le 3 \times 10 ^ 6$ | 无 | $35$ |

对于 $100\%$ 的数据，$1\le a_i \le 10^9$。


---

---
title: "[yLCPC2024] D. 排卡"
layout: "post"
diff: 普及+/提高
pid: P10236
tag: ['洛谷原创', '区间 DP', '洛谷月赛']
---
# [yLCPC2024] D. 排卡
## 题目背景

经过千辛万苦，扶苏终于到达了机厅。但是她很快发现机厅排起了大 b 队 ~~（不是省选的 B 队）~~。

舞萌玩家们在人多的时候经常采取排卡的方式决定谁下一个上机。因为人实在是太多了，他们在排卡的时候，便注意到了卡上的编号。

他们向扶苏提了一个问题，你能解决吗？
## 题目描述

扶苏有一个双端队列 $a$。这个队列与计算机科学中队列的概念类似，不同的是，这个队列既可以从队列头读取和弹出元素，也可以在队列尾部读取和弹出元素，因此被称为『双端队列』。

这个队列中有 $n$ 个数。扶苏将通过 $n$ 次操作构造一个长度为 $n$ 的序列 $b$，第 $i$（$1 \leq i \leq n$）次操作会可以进行如下两个过程之一：

1. 令 $b_i$ 为 $a$ 的队列头，并在 $a$ 的头部弹出一个元素。
2. 令 $b_i$ 为 $a$ 的队列尾，并在 $a$ 的尾部弹出一个元素。

我们定义一个数对 $(i, j)$ 的得分为：

$$\mathrm{score}(i,j) = i^j \bmod 998244353$$

即 $i$ 的 $j$ 次幂对 $998244353$ 取余数的结果。特别的，在本题中我们规定 $0^0 = 0$。

现在，扶苏想用最优的策略构造 $b$ 序列，最大化如下式子的值：

$$\sum_{i = 1}^{n - 1} \mathrm{score}(b_i, b_{i + 1})$$

即 $b$ 所有相邻两项按原顺序计算的得分之和。

注意，我们仅在计算一个数对的时候将得分对 $998,244,353$ 取模，在计算求和时不再将这个和取余。
## 输入格式

**本题单个测试点内有多组测试数据**。第一行是一个正整数，表示数据组数 $T$。对每组数据：

第一行是一个整数 $n$（$2 \leq n \leq 10^3$），表示序列的长度。  
第二行有 $n$ 个整数 $a_1, a_2, \dots a_n$（$0 \leq a_i < 998,244,353$），按从头到尾的顺序表示队列 $a$ 里每个数字的值。

数据保证单个测试点内 $n$ 的和不超过 $10^3$。
## 输出格式

对每组测试数据，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2
5
5 3 1 4 2
6
6 5 1 4 2 3
```
### 样例输出 #1
```
1168
15655
```


---

---
title: "[NOIP 2006 提高组] 能量项链"
layout: "post"
diff: 普及+/提高
pid: P1063
tag: ['动态规划 DP', '2006', '递归', 'NOIP 提高组', '枚举', '区间 DP']
---
# [NOIP 2006 提高组] 能量项链
## 题目描述

在 Mars 星球上，每个 Mars 人都随身佩带着一串能量项链。在项链上有 $N$ 颗能量珠。能量珠是一颗有头标记与尾标记的珠子，这些标记对应着某个正整数。并且，对于相邻的两颗珠子，前一颗珠子的尾标记一定等于后一颗珠子的头标记。因为只有这样，通过吸盘（吸盘是 Mars 人吸收能量的一种器官）的作用，这两颗珠子才能聚合成一颗珠子，同时释放出可以被吸盘吸收的能量。如果前一颗能量珠的头标记为 $m$，尾标记为 $r$，后一颗能量珠的头标记为 $r$，尾标记为 $n$，则聚合后释放的能量为 $m \times r \times n$（Mars 单位），新产生的珠子的头标记为 $m$，尾标记为 $n$。

需要时，Mars 人就用吸盘夹住相邻的两颗珠子，通过聚合得到能量，直到项链上只剩下一颗珠子为止。显然，不同的聚合顺序得到的总能量是不同的，请你设计一个聚合顺序，使一串项链释放出的总能量最大。

例如：设 $N=4$，$4$ 颗珠子的头标记与尾标记依次为 $(2,3)(3,5)(5,10)(10,2)$。我们用记号 $\oplus$ 表示两颗珠子的聚合操作，$(j \oplus k)$ 表示第 $j,k$ 两颗珠子聚合后所释放的能量。则第 $4$，$1$ 两颗珠子聚合后释放的能量为：

$(4 \oplus 1)=10 \times 2 \times 3=60$。

这一串项链可以得到最优值的一个聚合顺序所释放的总能量为：

$(((4 \oplus 1) \oplus 2) \oplus 3)=10 \times 2 \times 3+10 \times 3 \times 5+10 \times 5 \times 10=710$。
## 输入格式

第一行是一个正整数 $N$（$4 \le N \le 100$），表示项链上珠子的个数。第二行是 $N$ 个用空格隔开的正整数，所有的数均不超过 $1000$。第 $i$ 个数为第 $i$ 颗珠子的头标记（$1 \le i \le N$），当 $i<N$ 时，第 $i$ 颗珠子的尾标记应该等于第 $i+1$ 颗珠子的头标记。第 $N$ 颗珠子的尾标记应该等于第 $1$ 颗珠子的头标记。

至于珠子的顺序，你可以这样确定：将项链放到桌面上，不要出现交叉，随意指定第一颗珠子，然后按顺时针方向确定其他珠子的顺序。
## 输出格式

一个正整数 $E$（$E\le 2.1 \times 10^9$），为一个最优聚合顺序所释放的总能量。

## 样例

### 样例输入 #1
```
4
2 3 5 10

```
### 样例输出 #1
```
710
```
## 提示

NOIP 2006 提高组 第一题



---

---
title: "金字塔"
layout: "post"
diff: 普及+/提高
pid: P10956
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS', '区间 DP']
---
# 金字塔
## 题目描述

虽然探索金字塔是极其老套的剧情，但是有一队探险家还是到了某金字塔脚下。

经过多年的研究，科学家对这座金字塔的内部结构已经有所了解。

首先，金字塔由若干房间组成，房间之间连有通道。

如果把房间看作节点，通道看作边的话，整个金字塔呈现一个有根树结构，节点的子树之间有序，金字塔有唯一的一个入口通向树根。

并且，每个房间的墙壁都涂有若干种颜色的一种。

探险队员打算进一步了解金字塔的结构，为此，他们使用了一种特殊设计的机器人。

这种机器人会从入口进入金字塔，之后对金字塔进行深度优先遍历。

机器人每进入一个房间（无论是第一次进入还是返回），都会记录这个房间的颜色。

最后，机器人会从入口退出金字塔。

显然，机器人会访问每个房间至少一次，并且穿越每条通道恰好两次（两个方向各一次）， 然后，机器人会得到一个颜色序列。

但是，探险队员发现这个颜色序列并不能唯一确定金字塔的结构。

现在他们想请你帮助他们计算，对于一个给定的颜色序列，有多少种可能的结构会得到这个序列。

因为结果可能会非常大，你只需要输出答案对$10^9$ 取模之后的值。
## 输入格式

输入仅一行，包含一个字符串 $S$，长度不超过 $300$，表示机器人得到的颜色序列。

## 输出格式

输出一个整数表示答案。

## 样例

### 样例输入 #1
```
ABABABA

```
### 样例输出 #1
```
5
```


---

---
title: "[USACO25FEB] Printing Sequences B"
layout: "post"
diff: 普及+/提高
pid: P11838
tag: ['模拟', 'USACO', '递归', '2025', '区间 DP']
---
# [USACO25FEB] Printing Sequences B
## 题目描述

Bessie 正在学习使用一种简单的编程语言进行编程。她首先定义一个合法的程序，然后执行该程序以产生一些输出序列。

### 定义：

一个程序是一个非空的语句序列。

一个语句的形式或者是 "PRINT $c$"，其中 $c$ 是一个整数，或者是 "REP $o$"，随后是一个程序，随后是 "END"，其中 $o$ 是一个不小于 1 的整数。

### 执行：

执行一个程序将依次执行其语句。

执行语句 "PRINT $c$" 将使 $c$ 追加到输出序列中。

执行以 "REP $o$" 开始的语句将依次执行内部程序共 $o$ 次。

Bessie 知道如何编写的一个程序示例如下。

```plain
REP 3
    PRINT 1
    REP 2
        PRINT 2
    END
END
```

该程序输出序列 $[1,2,2,1,2,2,1,2,2]$。

Bessie 想要输出一个包含 $N$（$1 \le N \le 100$）个正整数的序列。Elsie 挑战她使用不超过 $K$（$1 \le K \le 3$）个 "PRINT" 语句。注意，Bessie 可以使用任意数量的 "REP" 语句。同时注意，序列中的每个正整数都不超过 $K$。

对于 $T$（$1 \le T \le 100$）个独立的测试用例中的每一个，求 Bessie 是否可以编写一个程序，使用至多 $K$ 个 "PRINT" 语句输出给定的序列。
## 输入格式

输入的第一行包含 $T$。

每一个测试用例的第一行包含空格分隔的两个整数 $N$ 和 $K$。

每一个测试用例的第二行包含一个由 $N$ 个空格分隔的正整数组成的序列，每个数都不超过 $K$，为 Bessie 想要产生的序列。
## 输出格式

对于每一个测试用例输出一行，包含 "YES" 或 "NO"（大小写敏感）。

## 样例

### 样例输入 #1
```
2
1 1
1
4 1
1 1 1 1
```
### 样例输出 #1
```
YES
YES
```
### 样例输入 #2
```
11
4 2
1 2 2 2
4 2
1 1 2 1
4 2
1 1 2 2
6 2
1 1 2 2 1 1
10 2
1 1 1 2 2 1 1 1 2 2
8 3
3 3 1 2 2 1 2 2
9 3
1 1 2 2 2 3 3 3 3
16 3
2 2 3 2 2 3 1 1 2 2 3 2 2 3 1 1
24 3
1 1 2 2 3 3 3 2 2 3 3 3 1 1 2 2 3 3 3 2 2 3 3 3
9 3
1 2 2 1 3 3 1 2 2
6 3
1 2 1 2 2 3
```
### 样例输出 #2
```
YES
NO
YES
NO
YES
YES
YES
YES
YES
NO
NO
```
## 提示

样例 1 解释：

对于第二个测试用例，以下代码使用了 $1$ 个 "PRINT" 语句输出了序列 $[1,1,1,1]$。

```plain
REP 4
    PRINT 1
END
```

样例 2 解释：

对于第一个测试用例，以下代码使用了 $2$ 个 "PRINT" 语句输出了序列 $[1,2,2,2]$。

```plain
PRINT 1
REP 3
    PRINT 2
END
```

对于第二个测试用例，答案是 "NO"，因为使用不超过 $2$ 个 "PRINT" 语句输出序列 $[1,1,2,1]$ 是不可能的。

对于第六个测试用例，以下代码使用了 $3$ 个 "PRINT" 语句输出了序列 $[3,3,1,2,2,1,2,2]$。

```plain
REP 2
    PRINT 3
END
REP 2
    PRINT 1
    REP 2
        PRINT 2
    END
END
```

- 测试点 $3$：$K=1$。
- 测试点 $4\sim 7$：$K \le 2$。
- 测试点 $8\sim 13$：没有额外限制。


---

---
title: "[GCJ 2009 #1C] Bribe the Prisoners"
layout: "post"
diff: 普及+/提高
pid: P13439
tag: ['动态规划 DP', '2009', '区间 DP', 'Google Code Jam']
---
# [GCJ 2009 #1C] Bribe the Prisoners
## 题目描述

In a kingdom there are prison cells (numbered $1$ to $P$) built to form a straight line segment. Cells number $i$ and $i+1$ are adjacent, and prisoners in adjacent cells are called "neighbours." A wall with a window separates adjacent cells, and neighbours can communicate through that window.

All prisoners live in peace until a prisoner is released. When that happens, the released prisoner's neighbours find out, and each communicates this to his other neighbour. That prisoner passes it on to his other neighbour, and so on until they reach a prisoner with no other neighbour (because he is in cell $1$, or in cell $P$, or the other adjacent cell is empty). A prisoner who discovers that another prisoner has been released will angrily break everything in his cell, unless he is bribed with a gold coin. So, after releasing a prisoner in cell $A$, all prisoners housed on either side of cell $A$ - until cell $1$, cell $P$ or an empty cell - need to be bribed.

Assume that each prison cell is initially occupied by exactly one prisoner, and that only one prisoner can be released per day. Given the list of $Q$ prisoners to be released in $Q$ days, find the minimum total number of gold coins needed as bribes if the prisoners may be released in any order.

Note that each bribe only has an effect for one day. If a prisoner who was bribed yesterday hears about another released prisoner today, then he needs to be bribed again.
## 输入格式

The first line of input gives the number of cases, $N$. $N$ test cases follow. Each case consists of 2 lines. The first line is formatted as

$P \ Q$

where $P$ is the number of prison cells and $Q$ is the number of prisoners to be released.

This will be followed by a line with $Q$ distinct cell numbers (of the prisoners to be released), space separated, sorted in ascending order.

## 输出格式

For each test case, output one line in the format

Case #$X$: $C$

where $X$ is the case number, starting from $1$, and $C$ is the minimum number of gold coins needed as bribes.
## 样例

### 样例输入 #1
```
2
8 1
3
20 3
3 6 14
```
### 样例输出 #1
```
Case #1: 7
Case #2: 35
```
## 提示

**Sample Explanation**

In the second sample case, you first release the person in cell 14, then cell 6, then cell 3. The number of gold coins needed is $19 + 12 + 4 = 35$. If you instead release the person in cell 6 first, the cost will be $19 + 4 + 13 = 36$.

**Limits**

- $1 \leq N \leq 100$
- $Q \leq P$
- Each cell number is between $1$ and $P$, inclusive.

**Small dataset**

- Time limit: ~~20~~ 2 seconds.
- $1 \leq P \leq 100$
- $1 \leq Q \leq 5$

**Large dataset**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq P \leq 10000$
- $1 \leq Q \leq 100$



---

---
title: "[NOI1995] 石子合并"
layout: "post"
diff: 普及+/提高
pid: P1880
tag: ['动态规划 DP', 'NOI', '区间 DP', '四边形不等式']
---
# [NOI1995] 石子合并
## 题目描述

在一个圆形操场的四周摆放 $N$ 堆石子，现要将石子有次序地合并成一堆，规定每次只能选相邻的 $2$ 堆合并成新的一堆，并将新的一堆的石子数，记为该次合并的得分。

试设计出一个算法,计算出将 $N$ 堆石子合并成 $1$ 堆的最小得分和最大得分。

## 输入格式

数据的第 $1$ 行是正整数 $N$，表示有 $N$ 堆石子。

第 $2$ 行有 $N$ 个整数，第 $i$ 个整数 $a_i$ 表示第 $i$ 堆石子的个数。

## 输出格式

输出共 $2$ 行，第 $1$ 行为最小得分，第 $2$ 行为最大得分。

## 样例

### 样例输入 #1
```
4
4 5 9 4
```
### 样例输出 #1
```
43
54
```
## 提示

$1\leq N\leq 100$，$0\leq a_i\leq 20$。


---

---
title: "[USACO16OPEN] 248 G"
layout: "post"
diff: 普及+/提高
pid: P3146
tag: ['动态规划 DP', '贪心', '2016', 'USACO', '区间 DP']
---
# [USACO16OPEN] 248 G
## 题目描述

Bessie likes downloading games to play on her cell phone, even though she  doesfind the small touch screen rather cumbersome to use with her large hooves.

She is particularly intrigued by the current game she is playing.The game starts with a sequence of $N$ positive integers ($2 \leq N\leq 248$), each in the range $1 \ldots 40$. In one move, Bessie cantake two adjacent numbers with equal values and replace them a singlenumber of value one greater (e.g., she might replace two adjacent 7s with an 8).  The goal is to maximize the value of the largest numberpresent in the sequence at the end of the game.  Please help Bessiescore as highly as possible!

## 输入格式

The first line of input contains $N$, and the next $N$ lines give the sequence of $N$ numbers at the start of the game.

## 输出格式

Please output the largest integer Bessie can generate.

## 样例

### 样例输入 #1
```
4
1
1
1
2
```
### 样例输出 #1
```
3
```
## 提示

In this example shown here, Bessie first merges the second and third 1s to obtain the sequence 1 2 2, and then she merges the 2s into a 3. Note that it is not optimal to join the first two 1s.

## 题目翻译

### 题目描述

贝西喜欢在手机上下载游戏来玩，尽管她确实觉得对于自己巨大的蹄子来说，小小的触摸屏用起来相当笨拙。

她对当前正在玩的这个游戏特别感兴趣。游戏开始时给定一个包含 $N$ 个正整数的序列（$2 \leq N \leq 248$），每个数的范围在 $1 \ldots 40$ 之间。在一次操作中，贝西可以选择两个相邻且相等的数，将它们替换为一个比原数大 1 的数（例如，她可以将两个相邻的 7 替换为一个 8）。游戏的目标是最大化最终序列中的最大数值。请帮助贝西获得尽可能高的分数！

### 输入格式

第一行输入包含 $N$，接下来的 $N$ 行给出游戏开始时序列的 $N$ 个数字。

### 输出格式

请输出贝西能生成的最大整数。

### 说明/提示

在示例中，贝西首先合并第二个和第三个 1，得到序列 1 2 2，然后将两个 2 合并为 3。注意，合并前两个 1 并不是最优策略。


---

---
title: "[HNOI2010] 合唱队"
layout: "post"
diff: 普及+/提高
pid: P3205
tag: ['动态规划 DP', '2010', '湖南', '区间 DP']
---
# [HNOI2010] 合唱队
## 题目描述

为了在即将到来的晚会上有更好的演出效果，作为 AAA 合唱队负责人的小 A 需要将合唱队的人根据他们的身高排出一个队形。假定合唱队一共 $n$ 个人，第 $i$ 个人的身高为 $h_i$ 米（$1000 \le h_i \le 2000$），并已知任何两个人的身高都不同。假定最终排出的队形是 $A$ 个人站成一排，为了简化问题，小 A 想出了如下排队的方式：他让所有的人先按任意顺序站成一个初始队形，然后从左到右按以下原则依次将每个人插入最终棑排出的队形中：

- 第一个人直接插入空的当前队形中。

- 对从第二个人开始的每个人，如果他比前面那个人高（$h$ 较大），那么将他插入当前队形的最右边。如果他比前面那个人矮（$h$ 较小），那么将他插入当前队形的最左边。

当 $n$ 个人全部插入当前队形后便获得最终排出的队形。

例如，有 $6$ 个人站成一个初始队形，身高依次为 $1850, 1900, 1700, 1650, 1800, 1750$，  
那么小 A 会按以下步骤获得最终排出的队形：

- $1850$。

- $1850, 1900$，因为 $1900 > 1850$。

- $1700, 1850, 1900$，因为 $1700 < 1900$。

- $1650, 1700, 1850, 1900$，因为 $1650 < 1700$。

- $1650, 1700, 1850, 1900, 1800$，因为 $1800 > 1650$。

- $1750, 1650, 1700, 1850, 1900, 1800$，因为 $1750 < 1800$。

因此，最终排出的队形是 $1750, 1650, 1700, 1850, 1900, 1800$。

小 A 心中有一个理想队形，他想知道多少种初始队形可以获得理想的队形。

请求出答案对 $19650827$ 取模的值。
## 输入格式

第一行一个整数 $n$。  
第二行 $n$ 个整数，表示小 A 心中的理想队形。
## 输出格式

输出一行一个整数，表示答案 $\bmod 19650827$ 的值。
## 样例

### 样例输入 #1
```
4
1701 1702 1703 1704
```
### 样例输出 #1
```
8
```
## 提示

对于 $30\%$ 的数据，$n \le 100$。  
对于 $100\%$ 的数据，$n \le 1000$，$1000 \le h_i \le 2000$。


---

---
title: "[HAOI2008] 玩具取名"
layout: "post"
diff: 普及+/提高
pid: P4290
tag: ['动态规划 DP', '2008', '河南', '各省省选', '枚举', '区间 DP']
---
# [HAOI2008] 玩具取名
## 题目描述

某人有一套玩具，并想法给玩具命名。首先他选择 `W, I, N, G` 四个字母中的任意一个字母作为玩具的基本名字。然后他会根据自己的喜好，将名字中任意一个字母用 `W, I, N, G` 中任意两个字母代替，使得自己的名字能够扩充得很长。

现在，他想请你猜猜某一个很长的名字，最初可能是由哪几个字母变形过来的。
## 输入格式

第一行四个整数 $W, I, N, G$。表示每一个字母能由几种两个字母所替代。

接下来 $W$ 行，每行两个字母,表示 `W` 可以用这两个字母替代。

接下来 $I$ 行，每行两个字母，表示 `I` 可以用这两个字母替代。

接下来 $N$ 行，每行两个字母，表示 `N` 可以用这两个字母替代。

接下来 $G$ 行，每行两个字母，表示 `G` 可以用这两个字母替代。

最后一行一个长度不超过 $L$ 的字符串。表示这个玩具的名字。
## 输出格式

一行字符串，该名字可能由哪些字母变形而得到。（按照 `W, I, N, G` 的顺序输出）

如果给的名字不能由任何一个字母变形而得到则输出 `The name is wrong!`。
## 样例

### 样例输入 #1
```
1 1 1 1
II
WW
WW
IG
IIII

```
### 样例输出 #1
```
IN

```
## 提示

### 数据规模与约定

- $30\%$ 数据满足 $L \leq 20$，$W, I, N, G \leq 6$；
- $100\%$ 数据满足 $L \leq 200$，$W, I, N, G \leq 16$。


---

---
title: "[IOI 1998] Polygon"
layout: "post"
diff: 普及+/提高
pid: P4342
tag: ['动态规划 DP', '1998', 'IOI', '区间 DP']
---
# [IOI 1998] Polygon
## 题目描述

Polygon is a game for one player that starts on a polygon with $N$ vertices, like the one in Figure 1, where $N=4$. Each vertex is labelled with an integer and each edge is labelled with either the symbol `+` (addition) or the symbol `*` (product). The edges are numbered from $1$ to $N$.

![](https://cdn.luogu.com.cn/upload/pic/16086.png)

On the first move, one of the edges is removed. Subsequent moves involve the following steps: 
- pick an edge $E$ and the two vertices $V_1$ and $V_2$ that are linked by $E$; and 
- replace them by a new vertex, labelled with the result of performing the operation indicated in $E$ on the labels of $V_1$ and $V_2$.

The game ends when there are no more edges, and its score is the label of the single vertex remaining. 

Consider the polygon of Figure 1. The player started by removing edge 3. After that, the player picked edge 1, then edge 4, and, finally, edge 2. The score is 0. 

![](https://cdn.luogu.com.cn/upload/pic/16088.png)

Write a program that, given a polygon, computes the highest possible score and lists all the edges that, if removed on the first move, can lead to a game with that score. 

## 输入格式

Your program is to read from standard input. The input describes a polygon with N vertices. It contains two lines. On the first line is the number N. The second line contains the labels of edges 1, ..., N, interleaved with the vertices' labels (first that of the vertex between edges 1 and 2, then that of the vertex between edges 2 and 3, and so on, until that of the vertex between edges N and 1), all separated by one space. An edge label is either the letter t (representing +) or the letter x (representing *). 

3 <= N <= 50 


For any sequence of moves, vertex labels are in the range [-32768,32767]. 

## 输出格式

Your program is to write to standard output. On the first line your program must write the highest score one can get for the input polygon. On the second line it must write the list of all edges that, if removed on the first move, can lead to a game with that score. Edges must be written in increasing order, separated by one space.

## 样例

### 样例输入 #1
```
4
t -7 t 4 x 2 x 5

```
### 样例输出 #1
```
33
1 2
```
## 题目翻译

# 题目可能有些许修改，但大意一致

多边形是一个玩家在一个有n个顶点的多边形上的游戏，如图所示，其中n＝4。每个顶点用整数标记，每个边用符号+（加）或符号*（乘积）标记。

![](https://cdn.luogu.org/upload/pic/16086.png)

第一步，删除其中一条边。随后每一步： 

选择一条边连接的两个顶点V1和V2，用边上的运算符计算V1和V2得到的结果来替换这两个顶点。 

游戏结束时，只有一个顶点，没有多余的边。

如图所示，玩家先移除编号为3的边。之后，玩家选择计算编号为1的边，然后计算编号为4的边，最后，计算编号为2的边。结果是0。

![](https://cdn.luogu.org/upload/pic/16088.png)

（翻译者友情提示：这里每条边的运算符旁边的数字为边的编号，不拿来计算）

编写一个程序，给定一个多边形，计算最高可能的分数。

## 输入格式

输入描述一个有n个顶点的多边形，它包含两行。第一行是数字n，为总边数。

第二行描述这个多边形，一共有2n个读入，每两个读入中第一个是字符，第二个是数字。

第一个字符为第一条边的计算符号(t代表相加，x代表相乘)，第二个代表顶点上的数字。首尾相连。 

3 < = n < = 50

对于任何一系列的操作，顶点数字都在[-32768,32767]的范围内。

## 输出格式

第一行，输出最高的分数。在第二行，它必须写出所有可能的被清除后的边仍能得到最高得分的列表，必须严格递增。

感谢@2016c01 提供的翻译


---

---
title: "[蓝桥杯 2018 国 B] 搭积木"
layout: "post"
diff: 普及+/提高
pid: P8675
tag: ['2018', '区间 DP', '前缀和', '蓝桥杯国赛']
---
# [蓝桥杯 2018 国 B] 搭积木
## 题目描述

小明对搭积木非常感兴趣。他的积木都是同样大小的正立方体。

在搭积木时，小明选取 $m$ 块积木作为地基，将他们在桌子上一字排开，中间不留空隙，并称其为第 $0$ 层。

随后，小明可以在上面摆放第 $1$ 层，第 $2$ 层，……，最多摆放至第 $n$ 层。摆放积木必须遵循三条规则：

规则 $1$：每块积木必须紧挨着放置在某一块积木的正上方，与其下一层的积木对齐；

规则 $2$：同一层中的积木必须连续摆放，中间不能留有空隙；

规则 $3$：小明不喜欢的位置不能放置积木。

其中，小明不喜欢的位置都被标在了图纸上。图纸共有 $n$ 行，从下至上的每一行分别对应积木的第 $1$ 层至第 $n$ 层。每一行都有 $m$ 个字符，字符可能是 `.` 或 `X`，其中 `X` 表示这个位置是小明不喜欢的。

现在，小明想要知道，共有多少种放置积木的方案。他找到了参加蓝桥杯的你来帮他计算这个答案。

由于这个答案可能很大，你只需要回答这个答案对 $1000000007(10^9+7)$ 取模后的结果。

注意：地基上什么都不放，也算作是方案之一种。
## 输入格式

输入数据的第一行有两个正整数 $n$ 和 $m$，表示图纸的大小。

随后 $n$ 行，每行有 $m$ 个字符，用来描述图纸。每个字符只可能是 `.` 或 `X`。
## 输出格式

输出一个整数，表示答案对 $10^9+7$ 取模后的结果。
## 样例

### 样例输入 #1
```
2 3
..X
.X.
```
### 样例输出 #1
```
4
```
## 提示

**【样例解释】**

成功的摆放有（其中O表示放置积木）：

```
 1       2       3       4
..X     ..X     O.X     ..X
.X.     OX.     OX.     .XO
```

**【数据约定】**

对于 $10\%$ 的数据，$n=1$，$m \le 30$；

对于 $40\%$ 的数据，$n \le 10$，$m \le 30$；

对于 $100\%$ 的数据，$n \le 100$，$m \le 100$。

时限 1 秒, 256M。蓝桥杯 2018 年第九届国赛


---

