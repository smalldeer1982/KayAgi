---
title: "[NOIP 2006 提高组] 2^k进制数"
layout: "post"
diff: 提高+/省选-
pid: P1066
tag: ['数学', '高精度', '2006', 'NOIP 提高组', '进制']
---
# [NOIP 2006 提高组] 2^k进制数
## 题目描述

设 $r$ 是个 $2^k$ 进制数，并满足以下条件：

- $r$ 至少是个 $2$ 位的 $2^k$ 进制数。

- 作为 $2^k$ 进制数，除最后一位外，$r$ 的每一位严格小于它右边相邻的那一位。

- 将 $r$ 转换为二进制数 $q$ 后，则 $q$ 的总位数不超过 $w$。

在这里，正整数 $k,w$ 是事先给定的。

问：满足上述条件的不同的 $r$ 共有多少个？

我们再从另一角度作些解释：设 $S$ 是长度为 $w$ 的 $01$ 字符串（即字符串 $S$ 由 $w$ 个 $0$ 或 $1$ 组成），$S$ 对应于上述条件三中的 $q$。将 $S$ 从右起划分为若干个长度为 $k$ 的段，每段对应一位 $2^k$ 进制的数，如果 $S$ 至少可分成 $2$ 段，则 $S$ 所对应的二进制数又可以转换为上述的 $2^k$ 进制数 $r$。

例：设 $k=3,w=7$。则 $r$ 是个八进制数（ $2^3=8$ ）。由于 $w=7$，长度为 $7$ 的 $01$ 字符串按 $3$ 位一段分，可分为 $3$ 段（即 $1,3,3$，左边第一段只有一个二进制位），则满足条件的八进制数有：

$2$ 位数：  
高位为 $1$：$6$ 个（即 $12,13,14,15,16,17$ ）,   
高位为 $2$：$5$ 个，  
…，  
高位为 $6$：$1$ 个（即 $67$ ）。  
共 $6+5+…+1=21$ 个。

$3$ 位数：  
高位只能是 $1$，  
第 $2$ 位为 $2$：$5$ 个（即 $123,124,125,126,127$ ），  
第 $2$ 位为 $3$：$4$ 个，  
…，    
第 $2$ 位为 $6$：$1$ 个（即 $167$ ）。  
共 $5+4+…+1=15$ 个。

所以，满足要求的 $r$ 共有 $36$ 个。

## 输入格式

一行两个正整数 $k,w$ 用一个空格隔开：

## 输出格式

一行一个个正整数，为所求的计算结果。  
即满足条件的不同的 $r$ 的个数（用十进制数表示），要求不得有前导零，各数字之间不得插入数字以外的其他字符（例如空格、换行符、逗号等）。

（提示：作为结果的正整数可能很大，但不会超过 $200$ 位）

## 样例

### 样例输入 #1
```
3 7
```
### 样例输出 #1
```
36
```
## 提示

【数据范围】  
$1\le k \le 9$    
$1\le w \le 3\times 10^4$

NOIP 2006 提高组 第四题



---

---
title: "[CSP-J2022 山东] 吟诗"
layout: "post"
diff: 提高+/省选-
pid: P11856
tag: ['2022', '山东', '枚举', '状态合并', '进制', 'CSP-J 入门级']
---
# [CSP-J2022 山东] 吟诗
## 题目背景

受疫情影响，山东省取消了 CSP-J 2022 认证活动，并于次年三月重新命题，在省内补办比赛。
## 题目描述

"文章本天成，妙手偶得之。"

吟诗是表达情怀的常用手段，战争落下了帷幕，常年的军旅生活使得小虾米喜欢上了豪放派的诗歌。

这一天，小虾米突然想吟诗了。著名的豪放派诗人苏轼有“老夫聊发少年狂，左牵黄，右擎苍。”的豪放，又有“十年生死两茫茫，不思量，自难忘。”的悲怆。小虾米心向往之，于是也想用《江城子》词牌名作诗。

小虾米想作出能流传千古的诗，根据经验，如果一首诗存在妙手就能流传千古。

具体来说，一首 N 个字的诗，每个字可以用 **$1$ 到 $10$** 之间的某个正整数来表示。同时存在三个正整数 $X,Y,Z\left(1\le X\le7,1\le Y\le5,1\le Z\le5\right)$，如果诗中出现了三个连续的片段使得第一个片段之和为 $X$，第二个片段之和为 $Y$，第三个片段之和为 $Z$，则小虾米认为这首诗出现了**妙手**。

即长度为 $n$ 的序列 $a_{1},a_{2},\dots a_{n} \left(1\le a_{i}\le10\right)$，如果存在 $i,j,k,l\left(1\le i<j<k<l\le n\right)$ 使得$a_{i}+a_{i+1}+\dots a_{j-1}=X$ 且 $a_{j}+a_{j+1}+\dots a_{k-1}=Y$ 且 $a_{k}+a_{k+1}+\dots a_{l-1}=Z$ 同时成立，则认为序列出现了妙手（注：第二个片段紧接第一个片段，第三个片段紧接第二个片段）。

举例来说，如果 $N=7$，$X=7$，$Y=3$，$Z=3$，则所有长度为 $7$ 的序列中，很显然共有 $10^{7}$ 种序列，其中一种序列 $\left[1,5,2,2,1,3,4\right]$ 出现了**妙手**，因为**存在**三个连续的区间 $\left[2,3\right]$、$\left[4,5\right]$、$\left[6,6\right]$ 满足它们的和分别为 $X=7$，$Y=3$，$Z=3$。

小虾米想知道在给定 $N,X,Y,Z$ 的前提下（共计 $10^{n}$ 种序列，即共 $10^{n}$ 种诗），计算有多少种存在妙手的诗，请你帮他计算出答案。

由于答案可能很大，请你将结果对 **$998244353$** 取模。
## 输入格式

一行，以空格隔开的 4 个正整数 $N,X,Y,Z$，分别表示序列长度和题目中 $X,Y,Z$ 的值。
## 输出格式

一行，一个整数，表示答案对 **$998244353$** 取模的结果。
## 样例

### 样例输入 #1
```
3 2 3 3
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
4 7 5 5
```
### 样例输出 #2
```
34
```
### 样例输入 #3
```
23 7 3 5
```
### 样例输出 #3
```
824896638
```
## 提示

### 样例一说明
在所有可能的序列中，只能构造出一种序列 $\left[2,3,3\right]$ 满足题意，因此答案为 $1$。
### 数据范围
对于 $30\%$ 的数据，$3\le N\le5$；

对于 $60\%$ 的数据，$3\le N\le20$；

对于 $100\%$ 的数据，$3\le N\le40,1\le X\le7,1\le Y\le5,1\le Z\le5$。


---

---
title: "[POI 2020/2021 R2] 棋盘 / Projekt planszy"
layout: "post"
diff: 提高+/省选-
pid: P12911
tag: ['POI（波兰）', '2021', 'Special Judge', '进制', '构造']
---
# [POI 2020/2021 R2] 棋盘 / Projekt planszy
## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/4828)。
## 题目描述

**题目译自 [XXVIII Olimpiada Informatyczna – II etap](https://sio2.mimuw.edu.pl/c/oi28-2/dashboard/) [Projekt planszy](https://szkopul.edu.pl/problemset/problem/tFYVKjavLmyczkxMH7WFewXe/statement/)**

棋盘由 $n \cdot n$ 个格子组成，分为 $n$ 行和 $n$ 列，格子编号从 $1$ 到 $n$。第 $i$ 行第 $j$ 列的格子坐标为 $(i, j)$。你需要从左上角的格子 $(1,1)$ 走到右下角的格子 $(n, n)$。棋盘上有些格子是被封锁的，你只能在未被封锁的格子上向右或向下移动，也就是说，从格子 $(i, j)$ 可以走到 $(i, j+1)$ 或 $(i+1, j)$，前提是目标格子没有被封锁。

有的棋盘只有一种走法，有的则有多种走法。给定一个数字 $K$，请你设计一个尺寸不超过 $100$ 的棋盘，使从起点到终点的不同走法数量恰好为 $K$。
## 输入格式

输入的第一行包含一个整数 $K$ $(0 \leq K)$。
## 输出格式

输出的第一行是一个整数 $n$ $(1 \leq n \leq 100)$，表示棋盘的大小。接下来 $n$ 行，每行输出一个长度为 $n$ 的字符串，由字符 `.`（表示未封锁的格子）和 `#`（表示被封锁的格子）组成。第 $i$ 行的第 $j$ 个字符描述了格子 $(i, j)$ 的状态。

在题目给定的限制条件下，答案总是存在的。如果有多种可能的答案，你的程序可以输出其中任意一种。
## 样例

### 样例输入 #1
```
6
```
### 样例输出 #1
```
4
...#
....
##..
###.
```
## 提示

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$ | $K \leq 50$ | $15$ |
| $2$ | $K \leq 2000$ | $15$ |
| $3$ | $K \leq 10^{9}$ | $40$ |
| $4$ | $K \leq 10^{18}$ | $30$ |


---

---
title: "[GCJ 2022 #1A] Equal Sum"
layout: "post"
diff: 提高+/省选-
pid: P12985
tag: ['数学', '贪心', '2022', '交互题', 'Special Judge', '进制', '构造', 'Google Code Jam']
---
# [GCJ 2022 #1A] Equal Sum
## 题目描述

You are given a set of distinct integers. You need to separate them into two non-empty subsets such that each element belongs to exactly one of them and the sum of all elements of each subset is the same.

An anonymous tip told us that the problem above was unlikely to be solved in polynomial time (or something like that), so we decided to change it. Now you get to decide what half of the integers are!

This is an interactive problem with three phases. In phase 1, you choose $\mathbf{N}$ distinct integers. In phase 2, you are given another $\mathbf{N}$ integers that are distinct from each other and from the ones you chose in phase 1. In phase 3, you have to partition those $2\mathbf{N}$ integers into two subsets, both of which sum to the same amount. All $2\mathbf{N}$ integers are to be between 1 and $10^9$, inclusive, and it is guaranteed that they sum up to an even number.

### Interactive Protocol

This is an interactive problem.

Initially, your program should read a single line containing an integer, $\mathbf{T}$, the number of test cases. Then, $\mathbf{T}$ test cases must be processed.

For each test case, your program must first read a line containing a single integer $\mathbf{N}$. Then, it must output a line containing $\mathbf{N}$ distinct integers $A_1, A_2, \ldots, A_{\mathbf{N}}$. Each of these integers must be between 1 and $10^9$, inclusive. After that, your program must read a line containing $\mathbf{N}$ additional integers $B_1, B_2, \ldots, B_{\mathbf{N}}$. Finally, your program must output a line containing between 1 and $2\mathbf{N}-1$ integers from among $A_1, A_2, \ldots, A_{\mathbf{N}}, B_1, B_2, \ldots, B_{\mathbf{N}}$: the ones chosen to be part of the first subset. The integers from $A$ and $B$ that you do not output are considered to be part of the other subset.

The next test case starts immediately if there is one. If this was the last test case, the judge will expect no more output and will send no further input to your program. In addition, all $\mathbf{T}$ test cases are always processed, regardless of whether the final output from your program is correct or not.

Note: It can be shown that given the limits for this problem, there exists a sequence $A_1, A_2, \ldots, A_{\mathbf{N}}$ such that any sequence $B_1, B_2, \ldots, B_{\mathbf{N}}$ results in a set of $2\mathbf{N}$ integers that can be separated into two subsets with equal sums.

If the judge receives an invalidly formatted or invalid line (like outputting an unexpected number of integers, or integers out of range, or repeated integers in a line) from your program at any moment, the judge will print a single number -1 and will not print any further output. If your program continues to wait for the judge after receiving a -1, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
2
3

10 4 9

3

10 8 12
```
### 样例输出 #1
```


5 1 3

1 10 5

5 2 3

12 8
```
## 提示

**Sample Explanation**

In the sample interaction above, the solution gets all cases right and would receive a correct verdict. Notice that the value for $\mathbf{N}$ does not conform to the limits for the Test Set and is used to simplify the example only. Notice that the judge could have given the solution the integers $\{2, 7, 100\}$ for the first case, making it impossible for the solution to find a valid partition into subsets of equal sum.

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our interactive runner for that.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

**Test Set 1 (Visible Verdict)**

- $1 \leq \mathbf{T} \leq 100$.
- $\mathbf{N} = 100$.
- $1 \leq \mathbf{B}_i \leq 10^9$, for all $i$.
- $\mathbf{B}_i \neq A_j$, for all $i, j$.
- $\mathbf{B}_i \neq \mathbf{B}_j$, for all $i \neq j$.
- For each test case, the judge will choose the $\mathbf{B}_i$s such that the sum of all $2\mathbf{N}$ integers is even.


---

---
title: "[USACO07MAR] Gold Balanced Lineup G"
layout: "post"
diff: 提高+/省选-
pid: P1360
tag: ['2007', 'USACO', '离散化', '进制', '前缀和', '队列']
---
# [USACO07MAR] Gold Balanced Lineup G
## 题目描述

神仙 $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 在许多方面都有着很强的能力。具体的说，他总共有 $m$ 种能力，并将这些能力编号为 $1 \sim m$。  

他的能力是一天一天地提升的，每天都会有一些能力得到一次提升，她对每天的能力提升都用一个数字表示，称之为能力提升数字，比如数字 $13$，转化为二进制为 $1101$，并且从右往左看，表示他的编号为 $1,3,4$ 的能力分别得到了一次提升。  

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 把每天表示能力提升的数字的记了下来，如果在连续的一段时间内，她的每项能力都提升了相同的次数，她就会称这段时间为一个均衡时期，比如在连续 $5$ 天内，她的每种能力都提升了 $4$ 次，那么这就是一个长度为 $5$ 的均衡时期。

于是，问题来了，给出 $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ $n$ 天的能力提升数字，请求出均衡时期的最大长度。

## 输入格式

第一行有两个整数 $n,m$，表示有 $n$ 天，$m$ 种能力。　　

接下来有 $n$ 行，每行有一个整数，分别表示第 $1\sim n$ 天的能力提升数字。  

能力提升数字转化为二进制后，从右到左的每一位表示对应的能力是否在当天得到了一次提升。



## 输出格式

输出只有一个整数，表示长度最大的均衡时期的长度。

## 样例

### 样例输入 #1
```
7 3
7
6
7
2
1
4
2

```
### 样例输出 #1
```
4


```
## 提示

【数据范围】    
对于 $50\%$ 的数据，$1\le n \le 1000$。  
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le m \le 30$。

【样例解释】

每天被提升的能力种类分别为：

| 天数 | 提升的能力 |
| :-----------: | :-----------: |
| $1$ | $1,2,3$ |
| $2$ | $2,3$ |
| $3$ | $1,2,3$ |
| $4$ | $2$ |
| $5$ | $1$ |
| $6$ | $3$ |
| $7$ | $2$ |

第三天到第六天为长度最长的均衡时期，因为这四天每种能力分别提升了 $2$ 次。



---

---
title: "[SCOI2005] 超级格雷码"
layout: "post"
diff: 提高+/省选-
pid: P2328
tag: ['2005', '四川', '各省省选', 'Special Judge', '枚举', '进制']
---
# [SCOI2005] 超级格雷码
## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1392.png)

## 输入格式

只有一行，为两个整数n和B。

## 输出格式

一共B^n个行，每行一个B进制数，表示你所求得的符合条件的排列。

## 样例

### 样例输入 #1
```
2  2
```
### 样例输出 #1
```
00
01
11
10

```
## 提示

感谢@Night_Aurora 提供SPJ


---

---
title: "[SDOI2006] 二进制方程"
layout: "post"
diff: 提高+/省选-
pid: P2456
tag: ['字符串', '高精度', '2006', '各省省选', '山东', '进制']
---
# [SDOI2006] 二进制方程
## 题目描述

一个形如：

X1X2…Xn=Y1Y2..Ym 

的等式称为二进制方程。

在二进制方程的两边：Xi和Yj （1<=i<=n；1<=j<=m）是二进制数字（0、1）或者一个变量（小写字母）。每个变量都是一个有固定长度的二进制代码，他可以在等式中取代变量的位置，称这个长度为变量的长度。为了解一个二进制方程，需要给其中的变量赋予适当的二进制代码，使得我们用他们替代等式中的相应的变量后（等式的两边都变成二进制代码），这个等式成立。

编程任务：

对于每一个给出的方程，计算一共有多少组解。已知变量最多有26个（26个英文小写字母），且等式的每一端的数字和变量的长度之和不超过10000。

## 输入格式

第一行：k（k<=26,变量的个数，规定使用小写英文字母中的前k个字母作为变量，如k=5，则变量a,b,c,d,e）。

第二行：k个正整数，中间用一个空格隔开，依次代表k个变量的长度。

第三行：等式左边的表达式。

第四行：等式右边的表达式。

## 输出格式

等式中出现的变量共有多少组解。

## 样例

### 样例输入 #1
```
2

4 2

1b1

a


```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5

4 2 4 4 2

1bad1

acbe


```
### 样例输出 #2
```
16
```
## 提示

样例一：4组解

1 、a=1001； b=00

2、 a=1011； b=01

3、 a=1101； b=10

4、 a=1111； b=11）

样例二：K=5，变量：a,b,c,d,e。长度分别为：4 2 4 4 2。等式是：1bad1= acbe

输出16，即变量a,b,c,d,e共有16组解。




---

---
title: "[NOI2001] 炮兵阵地"
layout: "post"
diff: 提高+/省选-
pid: P2704
tag: ['2001', 'NOI', '进制', '状压 DP']
---
# [NOI2001] 炮兵阵地
## 题目描述

司令部的将军们打算在 $N\times M$ 的网格地图上部署他们的炮兵部队。

一个 $N\times M$ 的地图由 $N$ 行 $M$ 列组成，地图的每一格可能是山地（用 $\texttt{H}$ 表示），也可能是平原（用 $\texttt{P}$ 表示），如下图。

在每一格平原地形上最多可以布置一支炮兵部队（山地上不能够部署炮兵部队）；一支炮兵部队在地图上的攻击范围如图中黑色区域所示：

 ![](https://cdn.luogu.com.cn/upload/pic/1881.png) 

如果在地图中的灰色所标识的平原上部署一支炮兵部队，则图中的黑色的网格表示它能够攻击到的区域：沿横向左右各两格，沿纵向上下各两格。

图上其它白色网格均攻击不到。从图上可见炮兵的攻击范围不受地形的影响。

现在，将军们规划如何部署炮兵部队，在防止误伤的前提下（保证任何两支炮兵部队之间不能互相攻击，即任何一支炮兵部队都不在其他支炮兵部队的攻击范围内），在整个地图区域内最多能够摆放多少我军的炮兵部队。


## 输入格式

第一行包含两个由空格分割开的正整数，分别表示 $N$ 和 $M$。

接下来的 $N$ 行，每一行含有连续的 $M$ 个字符，按顺序表示地图中每一行的数据。

## 输出格式

一行一个整数，表示最多能摆放的炮兵部队的数量。

## 样例

### 样例输入 #1
```
5 4
PHPP
PPHH
PPPP
PHPP
PHHP
```
### 样例输出 #1
```
6
```
## 提示

对于 $100\%$ 的数据，$1 \leq N\le 100$，$1 \leq M\le 10$，保证字符仅包含 `P` 与 `H`。


---

---
title: "A*B Problem"
layout: "post"
diff: 提高+/省选-
pid: P2841
tag: ['数学', '高精度', '递推', '进制']
---
# A*B Problem
## 题目描述

给出一个数 $A$ ，你需要给出一个最小的数 $B$ ，使得 $A\times B$ 的结果只含有 $0$ 和 $1$ 。
## 输入格式

一个正整数 $A$。
## 输出格式

正整数 $B$ 和 $A\times B$ 的结果，两数之间用一个空格隔开。
## 样例

### 样例输入 #1
```
6
```
### 样例输出 #1
```
185 1110

```
## 提示

样例说明：$6\times 185=1110$。

对于 $30\%$ 的数据，$0<A<20$。

对于 $50\%$ 的数据，$0<A<100$。

对于 $70\%$ 的数据，$0<A<1000$。

对于 $100\%$ 的数据，$0<A<10^4$。



---

---
title: "[USACO06DEC] The Fewest Coins G"
layout: "post"
diff: 提高+/省选-
pid: P2851
tag: ['动态规划 DP', '2006', 'USACO', '背包 DP', '进制']
---
# [USACO06DEC] The Fewest Coins G
## 题目描述

Farmer John has gone to town to buy some farm supplies. Being a very efficient man, he always pays for his goods in such a way that the smallest number of coins changes hands, i.e., the number of coins he uses to pay plus the number of coins he receives in change is minimized. Help him to determine what this minimum number is.

FJ wants to buy T (1 ≤ T ≤ 10,000) cents of supplies. The currency system has N (1 ≤ N ≤ 100) different coins, with values V1, V2, ..., VN (1 ≤ Vi ≤ 120). Farmer John is carrying C1 coins of value V1, C2 coins of value V2, ...., and CN coins of value VN (0 ≤ Ci ≤ 10,000). The shopkeeper has an unlimited supply of all the coins, and always makes change in the most efficient manner (although Farmer John must be sure to pay in a way that makes it possible to make the correct change).

农夫 John 想到镇上买些补给。为了高效地完成任务，他想使硬币的转手次数最少。即使他交付的硬 币数与找零得到的的硬币数最少。 


John 想要买价值为 $T$ 的东西。有 $N$（$1 \le N \le 100$）种货币参与流通，面值分别为 $V_1,V_2,\dots,V_N$（$1 \le V_i \le 120$）。John 有 $C_i$ 个面值为 $V_i$ 的硬币（$0 \le C_i \le 10 ^ 4$）。

我们假设店主有无限多的硬币， 并总按最优方案找零。**注意**无解输出 `-1`。

## 输入格式

Line 1: Two space-separated integers: N and T.


Line 2: N space-separated integers, respectively V1, V2, ..., VN coins (V1, ...VN)


Line 3: N space-separated integers, respectively C1, C2, ..., CN

## 输出格式

Line 1: A line containing a single integer, the minimum number of coins involved in a payment and change-making. If it is impossible for Farmer John to pay and receive exact change, output -1.

## 样例

### 样例输入 #1
```
3 70
5 25 50
5 2 1
```
### 样例输出 #1
```
3
```
## 提示

Farmer John pays 75 cents using a 50 cents and a 25 cents coin, and receives a 5 cents coin in change, for a total of 3 coins used in the transaction.



---

---
title: "萃香抱西瓜"
layout: "post"
diff: 提高+/省选-
pid: P3786
tag: ['洛谷原创', '最短路', '进制', '状压 DP']
---
# 萃香抱西瓜
## 题目背景

 ![](https://cdn.luogu.com.cn/upload/pic/5565.png) 

伊吹萃香 (Ibuki Suika) 正在魔法之森漫步，突然，许多西瓜 (Suika) 从四周飞来，划出了绚丽的轨迹。虽然阵势有点恐怖，但她还是决定抱走一些西瓜。

## 题目描述

萃香所处的环境被简化为一个长为 $h$，宽为 $w$ 的网格平面。$X$ 坐标范围为 $[1,w]$，$Y$ 坐标范围为 $[1,h]$。

她初始时（第 $1$ 个时刻）站在坐标为 $(sx,sy)$ 的方格。

西瓜可能在任意一个方格出现，在每个时间单位，它们可能向任何一个方向移动，也可能静止不动。西瓜的位置和移动的轨迹是已知的。西瓜的总数为 $n$ 个，但只有 $m$ 个西瓜可以被萃香抱走，因为其他都太大了，可能会砸伤她。

整个过程会持续 $T$ 个时刻。萃香希望可以抱走全部的 $m$ 个西瓜，并且在任何时候避免与任何一个过大的西瓜处在同一位置。抱走的方式为在某个时刻，与该西瓜处于同一位置。另外，由于萃香不愿耗费过多体力到处乱跑，她每个时刻可以选择静止不动，也可以选择移动到相邻的四个格子之一，只要不越出环境边界。如果选择移动到相邻格子，则算作移动了一次。第 $1$ 个时刻萃香刚站定，无法移动。

在每个时刻，如果萃香选择移动，可以认为萃香与西瓜同时从原来的位置移到了新的位置，没有先后顺序。

萃香想要知道，不被任何一个大西瓜砸中，并得到所有的m个小西瓜的情况下，最少需要移动多少次。

## 输入格式

第一行五个整数 $h,w,T,sx,sy$ ，含义见题目描述。

第二行两个整数 $n,m$，含义见题目描述。

接下来 $n$ 段数据，每一段描述了一个西瓜的出现位置，时间，移动方式，是否可以被抱走等内容，具体如下:

首先一行，两个整数 $t1,t2$，表示西瓜在 $t1$ 时刻出现，$t2$ 时刻消失。若 $t2=T+1$，表示西瓜在最后一个时刻也不消失。保证西瓜至少存在一个时刻。

接下来一行一个整数 $a$，只能为 $0$ 或 $1$，$0$ 表示这个西瓜需要避开，$1$ 表示这个西瓜需要抱走。数据保证需要抱走的西瓜恰好有 $m$ 个。

接下来 $t2-t1$ 行，每一行两个整数 $x,y$，顺序描述了从 $t1$ 时刻到 $t2-1$ 时刻，该西瓜的坐标。西瓜的移动不一定是连续的，并且是一瞬间完成的，所以无需考虑萃香是否站在了移动路径上。

## 输出格式

如果萃香在整个 $T$ 时刻内无法避免被大西瓜砸中或者无法收集到所有 $m$ 个小西瓜，输出 $-1$，否则输出一个整数，表示萃香需要移动的最少次数。

## 样例

### 样例输入 #1
```
5 5 10 3 3
1 1
1 11
1
3 4
5 2
3 5
1 1
5 4
3 4
2 1
1 1
1 1
5 5
```
### 样例输出 #1
```
1
```
## 提示


### 样例说明
第 $2 \sim 4$ 个时刻萃香站着不动，在第 $6$ 个时刻，西瓜出现在萃香旁边，萃香移动到 $(3,4)$ 位置即可抱走这个西瓜。

### 数据范围和提示

本题采用捆绑测试。

Subtask $1$：具有特殊性质 A 和 B；

Subtask $2 \sim 3$：仅具有特殊性质 A；

Subtask $4 \sim 5$：仅具有特殊性质 B；

Subtask $6 \sim 10$：不具有任何一个特殊性质。

特殊性质 A：对于所有西瓜，均满足 $t1=1,t2=T+1$。
所有西瓜全程都静止在原地，不会发生移动。

特殊性质 B：$m=0$。

对于全部子任务，满足：

$1 \le x \le w,1 \le y \le h$

$1\le n \le 20,
0 \le m \le 10,
m \le n$

$1 \le h,w \le 5,
1 \le T \le 100,
1 \le t1 \le T,
2 \le t2 \le T+1,
t1< t2$


保证一个位置不会同时出现两个或两个以上西瓜。


---

---
title: "签到题IV"
layout: "post"
diff: 提高+/省选-
pid: P3794
tag: ['线段树', '洛谷原创', 'O2优化', '枚举', '进制', '洛谷月赛']
---
# 签到题IV
## 题目背景

这场月赛好像其他题背景都很长，这题就不写背景了。 ![](https://cdn.luogu.com.cn/upload/pic/1436.png)

## 题目描述

给定一个长度为 $n$ 的序列 $[a_1,a_2\cdots a_n]$，其中每个数都是正整数。


你需要找出有多少对 $(i,j)$，$1 \leq i \leq j \leq n$ 且$\gcd(a_i,a_{i+1}...a_j) \operatorname{xor} (a_i \operatorname{or} a_{i+1} \operatorname{or} \cdots \operatorname{or} a_j)=k$，其中 $\operatorname{xor}$ 表示二进制异或，$\operatorname{or}$ 表示二进制或。

## 输入格式

第一行两个整数 $n,k$。

第二行 $n$ 个整数 $a_1,a_2\cdots a_n$。

## 输出格式

输出合法的 $(i,j)$ 的对数。

## 样例

### 样例输入 #1
```
5 6
2 4 3 4 2
```
### 样例输出 #1
```
8
```
## 提示

- 对于 $30\%$ 的数据，$n \leq 500$。
- 对于 $60\%$ 的数据，$n \leq 100000$。
- 对于 $100\%$ 的数据，$1 \leq n,a_i \leq 500000$。



---

---
title: "【模板】卢卡斯定理/Lucas 定理"
layout: "post"
diff: 提高+/省选-
pid: P3807
tag: ['递归', '素数判断,质数,筛法', '进制', '组合数学', '逆元', 'Lucas 定理']
---
# 【模板】卢卡斯定理/Lucas 定理
## 题目背景

这是一道模板题。

## 题目描述

给定整数 $n, m, p$ 的值，求出 $C_{n + m}^n \bmod p$ 的值。

输入数据保证 $p$ 为质数。

注: $C$ 表示组合数。
## 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示数据组数。

对于每组数据: 

一行，三个整数 $n, m, p$。
## 输出格式

对于每组数据，输出一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
2
1 2 5
2 1 5
```
### 样例输出 #1
```
3
3
```
## 提示

对于 $100\%$ 的数据，$1 \leq n, m, p \leq 10^5$，$1 \leq T \leq 10$。


---

---
title: "【模板】线性基"
layout: "post"
diff: 提高+/省选-
pid: P3812
tag: ['贪心', '进制', '线性基']
---
# 【模板】线性基
## 题目背景

这是一道模板题。

## 题目描述

给定 $n$ 个整数（数字可能重复），求在这些数中选取任意个，使得他们的异或和最大。

## 输入格式

第一行一个数 $n$，表示元素个数

接下来一行 $n$ 个数

## 输出格式

仅一行，表示答案。

## 样例

### 样例输入 #1
```
2
1 1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
4
1 5 9 4

```
### 样例输出 #2
```
13

```
## 提示

$ 1 \leq n \leq 50, 0 \leq S_i < 2 ^ {50} $



---

---
title: "[TJOI2008] 彩灯"
layout: "post"
diff: 提高+/省选-
pid: P3857
tag: ['2008', '各省省选', '进制', '线性基', '构造', '天津']
---
# [TJOI2008] 彩灯
## 题目描述

Peter 女朋友的生日快到了，他亲自设计了一组彩灯，想给女朋友一个惊喜。已知一组彩灯是由一排 $N$ 个独立的灯泡构成的，并且有 $M$ 个开关控制它们。从数学的角度看，这一排彩灯的任何一个彩灯只有亮与不亮两个状态，所以共有 $2^N$ 个样式。由于技术上的问题，Peter 设计的每个开关控制的彩灯没有什么规律，当一个开关被按下的时候，它会把所有它控制的彩灯改变状态（即亮变成不亮，不亮变成亮）。假如告诉你他设计的每个开关所控制的彩灯范围，你能否帮他计算出这些彩灯有多少种样式可以展示给他的女朋友？

注： 开始时所有彩灯都是不亮的状态。
## 输入格式

每组测试数据第一行为两个整数 $N$ 和 $M$，用空格隔开。紧接着是有 $M$ 行，每行都是一个长度为 $N$ 的字符串，表示一个开关控制彩灯的范围（$N$ 盏灯），如果第 $i$ 个字母是大写字母 `O`，则表示这个开关控制第 $i$ 盏灯，如果第 $i$ 个字母是大写字母 `X`，则表示这个开关不控制此灯。
## 输出格式

输出这些开关和彩灯可以变换出来的样式数目。由于这个值可能会很大，请求出它对于整数 $2008$ 的余数。
## 样例

### 样例输入 #1
```
2 3
OO
XO
OX

```
### 样例输出 #1
```
4
```
## 提示

可见样例中第一个开关控制了所有的彩灯，而后两个开关分别控制了第一个和第二个彩灯，这样我们可以只用后两个开关控制彩灯，可以变换出来所有的 $2^2$ 个状态。

对于 $30\%$ 的数据，$N$ 和 $M$ 不超过 $15$。

另外有 $40\%$ 的数据，$N$ 和 $M$ 有一个为 $50$。

对于 $100\%$ 的数据，$N$ 和 $M$ 不超过 $50$。


---

---
title: "[TJOI2010] 分金币"
layout: "post"
diff: 提高+/省选-
pid: P3878
tag: ['2010', '各省省选', 'O2优化', '模拟退火', '进制', '天津']
---
# [TJOI2010] 分金币
## 题目描述

现在有 $n$ 枚金币，它们可能会有不同的价值，第 $i$ 枚金币的价值为 $v_i$。

现在要把它们分成两部分，要求这两部分金币数目之差不超过 $1$，问这样分成的两部分金币的价值之差最小是多少？


## 输入格式

**本题单个测试点内有多组测试数据**。

输入的第一行是一个正整数 $T$，表示该测试点内数据组数。

对于每组测试数据的格式为：

每组测试数据占两行。

第一行是一个整数 $n$，表示金币的个数。

第二行有 $n$ 个整数，第 $i$ 个整数表示第 $i$ 个金币的价值 $v_i$。
## 输出格式

对于每组数据输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2
3
2 2 4
4
1 2 3 6

```
### 样例输出 #1
```
0
2

```
## 提示

#### 数据规模与约定

- 对 $30\%$ 的数据，保证 $1 \leq v_i \leq 1000$
- 对于 $100\%$ 的数据，保证 $1 \leq T \leq 20$，$1 \leq n \leq 30$，$1 \leq v_i \leq 2^{30}$。


---

---
title: "[GDOI2014] 拯救莫莉斯"
layout: "post"
diff: 提高+/省选-
pid: P3888
tag: ['2014', '各省省选', '广东', '枚举', '进制', '状压 DP']
---
# [GDOI2014] 拯救莫莉斯
## 题目描述

莫莉斯·乔是圣域里一个叱咤风云的人物，他凭借着自身超强的经济头脑，牢牢控制了圣域的石油市场。

圣域的地图可以看成是一个 $n\times m$ 的矩阵。每个整数坐标点 $(x, y)$ 表示一座城市（$1\le x\le n,1\le y\le m$）。两座城市间相邻的定义为：对于城市 $(A_x, A_y)$ 和城市 $(B_x, B_y)$，满足 $(A_x - B_x)^2 + (A_y - B_y)^2 = 1$。

由于圣域的石油贸易总量很大，莫莉斯意识到不能让每笔石油订购单都从同一个油库里发货。为了提高效率，莫莉斯·乔决定在其中一些城市里建造油库，最终使得每一个城市 $X$ 都满足下列条件之一：

1. 该城市 $X$ 内建有油库.
2. 某城市 $Y$ 内建有油库，且城市 $X$ 与城市 $Y$ 相邻。

与地球类似，圣域里不同城市间的地价可能也会有所不同，所以莫莉斯想让完成目标的总花费尽可能少。如果存在多组方案，为了方便管理，莫莉斯会选择建造较少的油库个数。

## 输入格式

第一行两个正整数 $n,m$（$n \times m \le 50$ 且 $m\le n$），表示矩阵的大小。

接下来一个 $n$ 行 $m$ 列的矩阵 $F$，$F_{i, j}$表示在城市 $(i,j)$ 建造油库的代价。

## 输出格式

输出两个数，建造方案的油库个数和方案的总代价。

## 样例

### 样例输入 #1
```
3 3
6 5 4
1 2 3
7 8 9
```
### 样例输出 #1
```
3 6
```
## 提示

对于 $30\%$ 数据满足 $n \times m \le 25$;   
对于 $100\%$ 数据满足 $n \times m \le 50,0 \le F_{i, j} \le 10 ^ 5$。



---

---
title: "SAC E#1 - 一道中档题 Factorial"
layout: "post"
diff: 提高+/省选-
pid: P3927
tag: ['洛谷原创', 'O2优化', '素数判断,质数,筛法', '进制', '洛谷月赛']
---
# SAC E#1 - 一道中档题 Factorial
## 题目背景

# 数据已修改

SOL君（炉石主播）和SOL菌（完美信息教室讲师）是好朋友。

## 题目描述

SOL君很喜欢阶乘。而SOL菌很喜欢研究进制。

这一天，SOL君跟SOL菌炫技，随口算出了n的阶乘。

SOL菌表示不服，立刻就要算这个数在k进制表示下末尾0的个数。

但是SOL菌太菜了于是请你帮忙。

## 输入格式

每组输入仅包含一行：两个整数n，k。

## 输出格式

输出一个整数：n!在k进制下后缀0的个数。

## 样例

### 样例输入 #1
```
10 40
```
### 样例输出 #1
```
2
```
## 提示

对于20%的数据，n <= 1000000， k = 10

对于另外20%的数据，n <= 20， k <= 36

对于100%的数据，n <= 10^12，k <= 10^12

## update

1.一组数据

2.K不会==1

3.现在std没有爆long long

4.对数据有问题联系icy （建议大家不要面向数据编程）



---

---
title: "SAC E#1 - 一道大水题 Knight"
layout: "post"
diff: 提高+/省选-
pid: P3930
tag: ['洛谷原创', 'O2优化', '广度优先搜索 BFS', '进制', '洛谷月赛', '状压 DP']
---
# SAC E#1 - 一道大水题 Knight
## 题目背景

毒奶色和F91是好朋友。

## 题目描述

他们经常在一起玩一个游戏，不，不是星际争霸，是国际象棋。

毒奶色觉得F91是一只鸡。他在一个n×n的棋盘上用黑色的城堡（车）、骑士（马）、主教（象）、皇后（副）、国王（帅）、士兵（卒）摆了一个阵。

然而F91觉得毒奶色是一只鸡。他发起了挑战：他要操纵一个白色骑士，不经过任何一个棋子的攻击范围（F91可以连续行动，而毒奶色的棋子不会动，除非白骑士进入了对方的攻击范围），并击杀毒奶色的国王（即进入黑国王所在的位置）。

请告诉F91他最少需要多少步骤来完成这一项壮举。


注意：

1.当F91的白骑士走到毒奶色的棋子所在的格子上的时候，会击杀（吃掉）该棋子。这个棋子也就不再对F91的白骑士有威胁了。

2.如果白骑士开场就在黑子的攻击范围内，则立刻被击杀、F91立刻失败。

3.即使白骑士在攻击王的瞬间进入了其他棋子攻击范围（即其他棋子“看护”着王所在的格子），依然算F91获胜。


攻击范围：


城堡：横、竖方向所有位置，直到被一个其他棋子阻拦。

```cpp
..#..
..#..
##C##
..#..
..#..
```

骑士：横2竖1或者横1竖2的所有位置（最多8个，类似日字）。

```cpp
.#.#.
#...#
..K..
#...#
.#.#.
```

主教：斜向（45°）所有位置，直到被一个其他棋子阻拦。

```cpp
#...#
.#.#.
..B..
.#.#.
#...#
```

皇后：城堡和主教的结合体（既能横/竖向攻击，也能45°角斜向攻击，直到被其他棋子阻挡）。

```cpp
#.#.#
.###.
##Q##
.###.
#.#.#
```

国王：身边8连通位置的8个格子。

```cpp
.....
.###.
.#X#.
.###.
.....
```

士兵：左下方/右下方（45°）的格子（最多2个）。

`````
.....
.....
..P..
.#.#.
.....
```

其中字母表示棋子类型，参考输入格式。

‘#’表示可攻击范围。

## 输入格式

输入包含多组数据。

每一组数据中，第一行一个整数n表示棋盘规模。

接下来n行，每行一个长度为n的字符串。描述棋盘的格局。

其中：

.表示空

O表示白骑士

C表示黑城堡

K表示黑骑士

B表示黑主教

Q表示黒皇后

X表示黑国王

P表示黑士兵

## 输出格式

对于每一个测试数据，每行输出一个整数，表示F91的最小步数。

如果无论F91如何行动也无法击杀黑国王，输出-1。

## 样例

### 样例输入 #1
```
8
...X....
........
........
........
........
........
........
......O.
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
8
......X.
........
.O......
...P.Q.C
.....B..
........
...K....
........
```
### 样例输出 #2
```
7
```
## 提示

**输入最多包含5组数据。**

对于20%的数据，毒奶色只有国王。n <= 8。

对于30%的数据，毒奶色只有国王、骑士。n <= 8。

对于60%的数据，毒奶色只有国王、骑士、王后。n <= 50。

对于100%的数据，毒奶色可以有全套16颗棋子（2城堡，2骑士，2主教，1后，1王，8兵）。n <= 50。


温馨提示：

时间限制可能比想象之中还要更紧一点，请注意实现细节以保证性能。



样例2解释：

一种可行的做法是：

```cpp
......X.
.3..6...
.O5.....
4.2P.Q.C
1....B..
........
...K....
........
```


---

---
title: "Changing"
layout: "post"
diff: 提高+/省选-
pid: P3937
tag: ['数学', '洛谷原创', '进制', '组合数学']
---
# Changing
## 题目描述

有 $n$ 盏灯环形排列，顺时针依次标号为 $1\cdots n$。初始时刻为 $0$，初始时刻第 $i$ 盏灯的亮灭 $a_i$ 给定，$0$ 表示灭，$1$ 表示亮。下一时刻每盏灯的亮灭取决于当前时刻这盏灯与顺时针方向下一盏灯的亮灭。若两盏灯状态相同，则下一时刻该灯灭，否则该灯亮。


试求时刻 $t$ 第 $k$ 盏灯的状态。

## 输入格式

第一行，三个整数，分别为 $n, t, k$。


第二行，共 $n$ 个整数，分别为 $0$ 或 $1$，代表 $a_i$。

## 输出格式

共一行，一个数，$0$ 或 $1$，代表时刻 $t$ 第 $k$ 盏灯的状态。

## 样例

### 样例输入 #1
```
4 2 1
1 0 1 0
```
### 样例输出 #1
```
0
```
## 提示

- 对于 $25\%$ 的数据，有$1\leq t, k\leq n\leq 1000$。 
- 对于 $60\%$ 的数据，有$1\leq t, k\leq n\leq 10^5$。 
- 对于 $100\%$ 的数据，有$1\leq t, k\leq n\leq 3\times 10^6$。



---

---
title: "[SHOI2013] 二重镇"
layout: "post"
diff: 提高+/省选-
pid: P3999
tag: ['2013', '各省省选', '上海', 'O2优化', '枚举', '进制', '状压 DP']
---
# [SHOI2013] 二重镇
## 题目描述

这是一个充满爱的村子，它的名字叫二重镇。在这个爱意浓浓的村子里，居民们的生活快乐又安宁。二重镇呈长条形状，可分为排成一行的 $N$ 个方格。每个格子可能是空地，也可能是小草、灌木、大树、房屋或城堡中的一种物品。每种物品都有一个等级，小草的等级是 $1$，灌木的等级是 $2$，依此类推。

你是这个村庄的建造者。你会陆续获得 $D$ 件物品，你要将它们合理地放置在村庄的空地上。你的目标是要让村子的总人气尽可能大。人气的获得规则在后面说明。关于放置的规则有以下几条：

* 第一，每件物品都必须放在一个地方，不可丢弃，如果没有空地了，游戏直接结束；

* 第二，物品可以放在一格空地上，或者临时放在仓库里。仓库同时最多只能放一件物品，它一开始是空的。只存在一个仓库；

* 第三，一旦物品放在某个空格上，只要符合条件，系统就会自动将一些物品合成一个大的物品，这是强制被动的，也是瞬间的。直到合成结束后，才能放置下一个物品。

* 第四，存放在仓库中的物品，随时可以取出放到空地上（但注意不能在合成的过程中放置），也可以一直留在仓库里。

* 第五，除非利用仓库，不然不能更改物品的放置顺序；

总结起来，这个游戏的流程就是获得一个新物品，决定是否将这个物品存入仓库，再决定将仓库中的物品或新物品放到哪个空地上，系统自动判定合成，获得人气，直到所有物品都被放置完毕，或空地用完为止。

最后是关于合成的规则。合成是自动完成的，也是强制性的。如果有连续两个或以上相邻的格子里有相同等级的物品，它们会自动合体成一个新的物品，新物品的等级比之前高一个级别。合体分三步：

* 第一步，确定有多少物品参与合成，这些物品的位置必须连在一起，等级相同。参与合体的物品会全部消失，对应的格子边成空地；

* 第二步，假设有 $A$ 个 $K$ 级物品参与合体，那么将获得$A\times 2^K$ 点人气。例如有一次五棵小草进行了合体，那么总人气就会增加 $5 \times 2^1=10$；

* 第三步，一个 $K+1$ 等级的物品会出现在一个格子里。如果 $K+1$ 大于 $5$，则跳过这步，但第二步中的人气仍然要算，第一步中的旧物品也会被清除。这个高等级的物品只会出现在参与合体的格子上。每个格子会记录最后一次被放置物品的时间，新的物品会出现在该时间最晚的那个格子里，形象地说，就是出现在最近被放置过东西的格子；

最后，请注意合成是会触发多次的，比如两个小草合成一个灌木，如果这棵灌木旁边还有其他灌木，合体将继续发生下去。

现在，给出 $N$ 和获得物品的顺序及等级，请你要合理地将这些物品放置在一个初始全是空地的村子里，使得村子最终的人气值尽可能高。当所有物品都被放置，或者某一刻村子里没空地了，你都会结束村子的建设，而此时村子里累计人气值就是你的最终成果。

## 输入格式

第一行给出两个整数 $N$ 和 $D$，用空格隔开。$N$ 表示村庄大小，$D$ 表示建设村庄的天数。

第二行为一个字符串，每个字符为 $1 \ldots 5$ 之间的一个字符，表示每天你可以放置的物品的等级。

## 输出格式

输出一个整数，表示你能得到的最大的人气值。

## 样例

### 样例输入 #1
```
4 10
1132411235
```
### 样例输出 #1
```
168
```
## 提示

对于 $30\%$ 的数据，$N=3$, $D\leq 10$。

对于 $60\%$ 的数据，$N\leq 4$, $D\leq 30$。

对于 $100\%$ 的数据，$N\leq 6$, $D\leq 100$。



---

---
title: "孤岛营救问题"
layout: "post"
diff: 提高+/省选-
pid: P4011
tag: ['O2优化', '广度优先搜索 BFS', '图论建模', '进制', '网络流与线性规划 24 题', '状压 DP']
---
# 孤岛营救问题
## 题目描述

$1944$ 年，特种兵麦克接到国防部的命令，要求立即赶赴太平洋上的一个孤岛，营救被敌军俘虏的大兵瑞恩。瑞恩被关押在一个迷宫里，迷宫地形复杂，但幸好麦克得到了迷宫的地形图。迷宫的外形是一个长方形，其南北方向被划分为 $N$ 行，东西方向被划分为 $M$ 列，于是整个迷宫被划分为 $N\times M$ 个单元。每一个单元的位置可用一个有序数对(单元的行号，单元的列号)来表示。南北或东西方向相邻的 $2$ 个单元之间可能互通，也可能有一扇锁着的门，或者是一堵不可逾越的墙。迷宫中有一些单元存放着钥匙，并且所有的门被分成$P$ 类，打开同一类的门的钥匙相同，不同类门的钥匙不同。


大兵瑞恩被关押在迷宫的东南角，即 $(N,M)$ 单元里，并已经昏迷。迷宫只有一个入口，在西北角。也就是说，麦克可以直接进入 $(1,1)$ 单元。另外，麦克从一个单元移动到另一个相邻单元的时间为 $1$，拿取所在单元的钥匙的时间以及用钥匙开门的时间可忽略不计。


试设计一个算法，帮助麦克以最快的方式到达瑞恩所在单元，营救大兵瑞恩。

## 输入格式

第 $1$ 行有 $3$ 个整数，分别表示 $N,M,P$ 的值。

第 $2$ 行是 $1$ 个整数 $K$，表示迷宫中门和墙的总数。

第 $I+2$ 行$(1\leq I\leq K)$，有 $5$ 个整数，依次为$X_{i1},Y_{i1},X_{i2},Y_{i2},G_i$：

- 当 $G_i \geq 1$ 时，表示 $(X_{i1},Y_{i1})$ 单元与 $(X_{i2},Y_{i2})$ 单元之间有一扇第 $G_i$ 类的门

- 当 $G_i=0$ 时，表示 $(X_{i1},Y_{i1})$ 单元与 $(X_{i2},Y_{i2})$ 单元之间有一堵不可逾越的墙（其中，$|X_{i1}-X_{i2}|+|Y_{i1}-Y_{i2}|=1$，$0\leq G_i\leq P$）。

第 $K+3$ 行是一个整数 $S$，表示迷宫中存放的钥匙总数。

第 $K+3+J$  行$(1\leq J\leq S)$，有 $3$ 个整数，依次为 $X_{i1},Y_{i1},Q_i$：表示第 $J$ 把钥匙存放在 $(X_{i1},Y_{i1})$单元里，并且第 $J$ 把钥匙是用来开启第 $Q_i$ 类门的。（其中$1\leq Q_i\leq P$）。

输入数据中同一行各相邻整数之间用一个空格分隔。

## 输出格式

将麦克营救到大兵瑞恩的最短时间的值输出。如果问题无解，则输出 $-1$。

## 样例

### 样例输入 #1
```
4 4 9
9
1 2 1 3 2
1 2 2 2 0
2 1 2 2 0
2 1 3 1 0
2 3 3 3 0
2 4 3 4 1
3 2 3 3 0
3 3 4 3 0
4 3 4 4 0
2
2 1 2
4 2 1
```
### 样例输出 #1
```
14
```
## 提示

$|X_{i1}-X_{i2}|+|Y_{i1}-Y_{i2}|=1,0\leq G_i\leq P$

$1\leq Q_i\leq P$


$N,M,P\leq10, K<150,S\leq 14$



---

---
title: "[HEOI2013] Eden 的新背包问题"
layout: "post"
diff: 提高+/省选-
pid: P4095
tag: ['2013', '各省省选', '河北', '枚举', '背包 DP', '进制']
---
# [HEOI2013] Eden 的新背包问题
## 题目背景

“ 寄 没 有 地 址 的 信 ，这 样 的 情 绪 有 种 距 离 ，你 放 着 谁 的 歌 曲 ，是 怎 样 的 心 情 。 能 不 能 说 给 我 听 。”
## 题目描述

失忆的 Eden 总想努力地回忆起过去，然而总是只能清晰地记得那种思念的感觉，却不能回忆起她的音容笑貌。

记忆中，她总是喜欢给 Eden 出谜题：在 valentine's day 的夜晚，两人在闹市中闲逛时，望着礼品店里精巧玲珑的各式玩偶，她突发奇想，问了 Eden 这样的一个问题：有 $n$ 个玩偶，每个玩偶有对应的价值、价钱，每个玩偶都可以被买有限次，在携带的价钱 $m$ 固定的情况下，如何选择买哪些玩偶以及每个玩偶买多少个，才能使得选择的玩偶总价钱不超过 $m$，且价值和最大。

众所周知的，这是一个很经典的多重背包问题，Eden 很快解决了，不过她似乎因为自己的问题被飞快解决感到了一丝不高兴，于是她希望把问题加难：多次询问，每次询问都将给出新的总价钱，并且会去掉某个玩偶（即这个玩偶不能被选择），再问此时的多重背包的答案（即前一段所叙述的问题）。

这下 Eden 犯难了，不过 Eden 不希望自己被难住，你能帮帮他么？
## 输入格式

第一行有一个整数，代表玩偶的个数 $n$，玩偶从 $0$ 开始编号。

第二行开始后面的 $n$ 行，每行三个整数，第 $(i + 2)$ 行的整数  $a_i, b_i, c_i$，分别表示买一个第 $i$ 个玩偶需要的价钱，获得的价值以及第 $i$ 个玩偶的限购次数。

接下来的一行有一个整数 $q$，表示询问次数。

接下来 $q$ 行，每行两个整数 $d_i, e_i$，表示每个询问去掉的是哪个玩偶（注意玩偶从 $0$ 开始编号）以及该询问对应的新的总价钱数。（去掉操作不保留，即不同询问互相独立）。
## 输出格式

输出 $q$ 行，第 $i$ 行输出对于第 $i$ 个询问的答案。
## 样例

### 样例输入 #1
```
5 
2 3 4 
1 2 1 
4 1 2 
2 1 1 
3 2 3 
5 
1 10 
2 7 
3 4 
4 8 
0 5
```
### 样例输出 #1
```
13 
11 
6 
12 
4 

```
## 提示

#### 样例解释

一共五种玩偶，分别的价钱价值和限购次数为 $(2,3,4)$， $(1,2,1)$， $(4,1,2)$， $(2,1,1)$， $(3,2,3)$。

五个询问，以第一个询问为例。

第一个询问表示的是去掉编号为 $1$ 的玩偶， 且拥有的钱数为 $10$ 时可以获得的最大价值，则此时剩余玩偶为 $(2,3,4$)，$(4,1,2)$， $(2,1,1)$，$(3,2,3)$，若把编号为 $0$ 的玩偶买 $4$ 个（即全买了），然后编号为 $3$ 的玩偶 买一个，则刚好把 $10$ 元全部花完，且总价值为 $13$。可以证明没有更优的方案了。

注意买某种玩偶不一定要买光。

---

#### 数据规模与约定

- 对于 $10\%$ 的数据，保证 $n \leq 10$。
- 另外存在 $20\%$ 的数据，保证  $n \leq 100$，$c_i = 1$，$q \leq 100$。
- 另外存在 $20\%$ 的数据，保证 $n \leq 100$，$q \leq 100$。
- 另外存在 $30\%$ 的数据，保证 $c_i = 1$。
- 对于 $100\%$ 的数据，保证  $1 \leq n \leq 1000$，$1 \leq q \leq 3\times 10^5$， $1 \leq a_i,b_i,c_i \leq 100$，$0 \leq d_i < n$，$0 \leq e_i \leq 1000$。




---

---
title: "扑克"
layout: "post"
diff: 提高+/省选-
pid: P4236
tag: ['进制']
---
# 扑克
## 题目背景

lsq邀请wzt去他家打扑克牌
## 题目描述

lsq的扑克没有大小王，共计有n张，由于wzt沉迷于幂运算无法自拔，wzt提出要每次抽a^2张牌（这里“^”是乘方的意思），lsq觉得这样抽真没意思，于是改成了每次抽a^k（k是一个自然数，由游戏者自由选择）张牌。**由lsq开始**，每个人轮流按上述规则摸牌，谁先摸到最后一张牌谁就赢。

由于时间充裕，lsq和wzt一共会玩q盘游戏，每一盘都有不同的a和n。wzt怒敲了一波代码，竟然可以算出当确定了a和n的值后，若能必胜如何下。lsq在见识过你的~~毒瘤~~操作后，希望你也帮他写出一个程序，能判断确定了a和n的值后他是否能赢，lsq当然知道怎么下最优，所以不需要你算出如何下 

**注意：此题中两方的打牌决策都是若有必胜决策则必用必胜决策**

此题中k是一个每次抽牌都可由抽牌者自己决定的一个非负整数，可以结合下面的样例加以理解
## 输入格式

第一行一个数q， 表示有q局游戏
接下来q行，每行两个整数a,n，意义如上
## 输出格式

输出共q行
若lsq能赢，输出“lsq Win”
若wzt能赢，输出“wzt Win”
## 样例

### 样例输入 #1
```
3
2 5
2 9
3 9
```
### 样例输出 #1
```
lsq Win
wzt Win
lsq Win
```
## 提示

对于30%的数据，满足q<=30，a<=30，n<=1e8

对于50%的数据，满足q<=50，a<=30，n<=1e12

对于100%的数据，满足q<=50000，a<=20000，n<=1e500

样例一解释：
询问1：lsq必胜，lsq先抽2^1=2，接下来无论wzt抽2^1=2或2^0=1，lsq只要把牌抽完；其他抽法同上（只是顺序不同）

询问2：wzt必胜，若lsq先抽2^0=1，则wzt抽2^3=8；若lsq先抽2^1=2，则wzt抽2^2=4，接下来无论lsq抽2^1=2或2^0=1，wzt只要把牌抽完；其他抽法同上（只是顺序不同）

询问3：lsq必胜，lsq只需拿走3^2=9即可

By [Broadway](https://www.luogu.org/space/show?uid=33509)


---

---
title: "[HAOI2008] 移动玩具"
layout: "post"
diff: 提高+/省选-
pid: P4289
tag: ['2008', '河南', '各省省选', '哈希 hashing', '进制', '队列']
---
# [HAOI2008] 移动玩具
## 题目描述

在一个4*4的方框内摆放了若干个相同的玩具，某人想将这些玩具重新摆放成为他心中理想的状态，规定移动时只能将玩具向上下左右四个方向移动，并且移动的位置不能有玩具，请你用最少的移动次数将初始的玩具状态移动到某人心中的目标状态。
## 输入格式

前4行表示玩具的初始状态，每行4个数字1或0，1表示方格中放置了玩具，0表示没有放置玩具。接着是一个空行。接下来4行表示玩具的目标状态，每行4个数字1或0，意义同上。
## 输出格式

一个整数，所需要的最少移动次数。
## 样例

### 样例输入 #1
```
1111
0000
1110
0010 

1010
0101
1010
0101
```
### 样例输出 #1
```
4
```


---

---
title: "花神的数论题"
layout: "post"
diff: 提高+/省选-
pid: P4317
tag: ['枚举', '数位 DP', '进制']
---
# 花神的数论题
## 题目背景

众所周知，花神多年来凭借无边的神力狂虐各大 OJ、OI、CF、TC …… 当然也包括 CH 啦。
## 题目描述

话说花神这天又来讲课了。课后照例有超级难的神题啦…… 我等蒟蒻又遭殃了。 花神的题目是这样的：设  $\text{sum}(i)$  表示  $i$  的二进制表示中  $1$  的个数。给出一个正整数  $N$  ，花神要问你  $\prod_{i=1}^{N}\text{sum}(i)$ ，也就是  $\text{sum}(1)\sim\text{sum}(N)$  的乘积。
## 输入格式

一个正整数 $N$。
## 输出格式

一个数，答案模 $10000007$ 的值。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
2
```
## 提示

对于 $100\%$ 的数据，$1\le N\le 10^{15}$。


---

---
title: "[Code+#4] 最短路"
layout: "post"
diff: 提高+/省选-
pid: P4366
tag: ['图论建模', '最短路', '进制', 'Code+']
---
# [Code+#4] 最短路
## 题目背景

在北纬 91° ，有一个神奇的国度，叫做企鹅国。这里的企鹅也有自己发达的文明，称为企鹅文明。因为企鹅只有黑白两种颜色，所以他们的数学也是以二进制为基础发展的。

比如早在 $11101001$ 年前，他们就有了异或这样一个数学概念。如果你不知道异或是什么，请出门过墙左转到[这里](https://zh.wikipedia.org/wiki/%E9%80%BB%E8%BE%91%E5%BC%82%E6%88%96)。

再比如早在 $1000010$ 年前，他们的大科学家 Penguin. Tu 就提出了[图](https://zh.wikipedia.org/wiki/%E5%9B%BE_%28%E6%95%B0%E5%AD%A6%29#%E6%9C%89/%E7%84%A1_%E5%90%91%E5%9B%BE)和[最短路径](https://zh.wikipedia.org/wiki/%E6%9C%80%E7%9F%AD%E8%B7%AF%E9%97%AE%E9%A2%98)这样一些概念。
## 题目描述

企鹅国中有 $N$ 座城市，编号从 $1$ 到 $N$ 。

对于任意的两座城市 $i$ 和 $j$ ，企鹅们可以花费 $(i~\mathrm{xor}~j) \times C$ 的时间从城市 $i$ 走到城市 $j$ ，这里 $C$ 为一个给定的常数。

当然除此之外还有 $M$ 条单向的快捷通道，第 $i$ 条快捷通道从第 $F_i$​​ 个城市通向第 $T_i$​​ 个城市，走这条通道需要消耗 $V_i$​​ 的时间。

现在来自 **P**enguin **K**ingdom **U**niversity 的企鹅豆豆正在考虑从城市 $A$ 前往城市 $B$ 最少需要多少时间？
## 输入格式

从标准输入读入数据。

输入第一行包含三个整数 $N,M,C$ ，表示企鹅国城市的个数、快捷通道的个数以及题面中提到的给定的常数$C$。

接下来的 $M$ 行，每行三个正整数 $F_i,T_i,V_i$​ ($1 \leq F_i \leq N$,$1 \leq T_i \leq N ,1\leq V_i \leq 100$)，分别表示对应通道的起点城市标号、终点城市标号和通过这条通道需要消耗的时间。

最后一行两个正整数 $A,B$ $(1 \leq C \leq 100)$，表示企鹅豆豆选择的起点城市标号和终点城市标号。

## 输出格式

输出到标准输出。

输出一行一个整数，表示从城市 $A$ 前往城市 $B$ 需要的最少时间。

## 样例

### 样例输入 #1
```
4 2 1
1 3 1
2 4 4
1 4
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
7 2 10
1 3 1
2 4 4
3 6
```
### 样例输出 #2
```
34
```
## 提示

**样例1解释**

直接从 $1$ 走到 $4$ 就好了。

**样例2解释**

先从 $3$ 走到 $2$ ，再从 $2$ 通过通道到达 $4$ ，再从 $4$ 走到 $6$。

![0](https://cdn.luogu.com.cn/upload/pic/16868.png)

活泼可爱的出题人给大家留下了下面这张图。

![1](https://i.loli.net/2018/04/02/5ac1bb2333c22.jpg)

Credit: https://www.luogu.org/discuss/show/38908


---

---
title: "[CQOI2018] 异或序列"
layout: "post"
diff: 提高+/省选-
pid: P4462
tag: ['2018', '重庆', '莫队', '各省省选', '进制', '前缀和']
---
# [CQOI2018] 异或序列
## 题目描述

已知一个长度为 $n$ 的整数数列 $a_1,a_2,\dots,a_n$，给定查询参数 $l,r$，问在 $a_l,a_{l+1},\dots,a_r$ 区间内，有多少子区间满足异或和等于 $k$。也就是说，对于所有的 $x,y (l \leq x \leq y \leq r)$，能够满足 $a_x \oplus a_{x+1} \oplus \dots \oplus a_y = k$ 的 $x,y$ 有多少组。

## 输入格式

输入文件第一行，为 $3$ 个整数 $n,m,k$。

第二行为空格分开的 $n$ 个整数，即 $a_1,a_2,..a_n$。

接下来 $m$ 行，每行两个整数 $l_j,r_j$，表示一次查询。
## 输出格式

输出文件共 $m$ 行，对应每个查询的计算结果。
## 样例

### 样例输入 #1
```
4 5 1
1 2 3 1
1 4
1 3
2 3
2 4
4 4
```
### 样例输出 #1
```
4
2
1
2
1
```
## 提示

对于 $30\%$ 的数据，$1 \leq n, m \leq 1000$。

对于 $100\%$ 的数据，$1 \leq n, m \leq 10^5$，$0 \leq k, a_i \leq 10^5$，$1 \leq l_j \leq r_j \leq n$。


---

---
title: "[USACO14FEB] Cow Decathlon G"
layout: "post"
diff: 提高+/省选-
pid: P4877
tag: ['贪心', '2014', 'USACO', '进制', '状压 DP']
---
# [USACO14FEB] Cow Decathlon G
## 题目描述

Farmer John's $N$ cows $(1 <= N <= 20)$, conveniently labeled $1...N$ as always, are preparing for a decathlon that has $N$ different events (so perhaps it would be better called an N-athlon instead of a decathlon, which traditionally has exactly 10 events).

Cow i has a skill level of $s_ij$ $(1 <= s_ij <= 1000)$ when competing in event j.  Each cow must compete in one and only one event, and each event must have some cow competing in it.

The total score for all cows is the sum of their skill levels for the events in which they are competing.  However, the event judges can also give out bonus points if they are particularly impressed.  There are $B$ bonuses $(1 <= B <= 20)$ that the judges can give out. Bonus i has three parts: if the cows obtain at least $P_i$ points $(1 <= P_i <= 40,000)$ for the first $K_i$ events (including other bonuses involving just those events), they will get an additional $A_i$ points $(1 <= A_i <= 1000)$.  

For example, let us consider $N = 3$ cows with the following skills:

```
      E V E N T
     | 1 | 2 | 3
   --+---+---+--
C  1 | 5 | 1 | 7
   --+---+---+--
O  2 | 2 | 2 | 4
   --+---+---+--
W  3 | 4 | 2 | 1
```
For example, cow 1 would earn the team 7 points if she participates in event 3.  

Suppose the judges offer a bonus (B = 1), such that if the if the cows score at least 7 points in the first two events, they will get an  additional 6 points.  Here, the optimal assignment would be to assign cow 1 to event 1, cow 2 to event 3 and cow 3 to event 2.  For the first two events, cow 1 will score 5 points and cow 3 will score 2 points giving them 7 points, which is enough to satisfy bonus 1.  Therefore, the total points that they score will be 5+2+4+6=17.

Please help decide which events the cows should attempt to maximize their total score.
## 输入格式

* Line 1: Two space-separated integers: $N, B$

* Lines 2..B+1: Line i+1 will contain the information for bonus i which is three space- separated integers: $K_i, P_i, A_i$.

* Lines B+2..B+N+1: Line B+1+j will contain the information on how cow j will perform at each  of her events. This will be given in $N$ space-separated integers: $s_j1...s_jN.$
## 输出格式

* Line 1: The maximum amount of points that the cows can receive, including bonuses.

## 样例

### 样例输入 #1
```
3 1
2 7 6
5 1 7
2 2 4
4 2 1
```
### 样例输出 #1
```
17
```
## 提示

Cow 1 will perform event 1, cow 3 will perform event 2, and cow 2 will  perform event 3.
## 题目翻译

题目大意
约翰有N头奶牛，组成了一直队伍参加全能比赛。比赛一共有N项，每头奶牛必须参加一项比赛，每项比赛也必须有一头奶牛参加。任何一头奶牛可以胜任任何一项比赛，但得分不一样。如果第i头奶牛参加第j项比赛，在比赛结束的时候，可以为团体总分增加Si,j。
比赛是按照顺序依次进行的。除了上述获得分数的方法之外，还有B种奖励分。获得奖励的方法是在前几项比赛里获得足够的分数。具体来说，第i项奖励会在第Ki项比赛结束的时候检查，如果 当时的总分大于或等于Pi，奶牛们就可以立即获得额外的Ai 分。如果有多项奖励在同一时刻检查，奶牛可以自由安排检查和加分的顺序。请问约翰应该如何安排奶牛参加比赛，才能让它们获得最高的分数？

输入输出格式
输入格式
第一行：两个整数N和B，1≤N≤20 , 1≤B≤20
第二行到第B+1行：第i+1行有三个整数Ki，Pi和Ai，1≤Ki≤N ,1≤Pi≤40000 , 1≤Ai≤1000
第B+2行到第B+N+1行：第i+B+1 行有N个整数，代表Si,1到Si,N，对每个1≤j≤N , 1≤Si,j≤1000。

输出格式
单个整数：表示奶牛们可以获得的最大得分

样例输入
3 1
2 7 6
5 1 7
2 2 4
4 2 1

样例输出
17

提示：
第一项比赛由第一头奶牛参加，第二项比赛由第三头奶牛参加，第三项比赛由第二头奶牛参加。

translator：2018_RNG丶妖夢


---

---
title: "小奔关闹钟"
layout: "post"
diff: 提高+/省选-
pid: P4906
tag: ['搜索', '进制', '状压 DP']
---
# 小奔关闹钟
## 题目背景

由于今天是星期一，闹钟准时响了，由于小奔太困了，所以他想关停闹钟。

## 题目描述

可是，他的闹钟电路太复杂了，有很多个开关，每个开关都连着其他开关，其他开关又连着更多的开关，当且仅当所有开关都关闭时，闹钟才会停止响铃，（初始时默认每个开关都开着的），她该如何是好呢？


请你帮小奔求出最少开关次数，如果无论如何都不能关闭闹钟，请输出‘Change an alarm clock，please!’
## 输入格式

共有N+1行

第一行一个数N（1≤N≤20），表示有N个开关，从第2行起的第i行表示第i个闹钟开关。

以后N行，每行第一个数为M（0≤M≤N-1），表示第i个闹钟开关的直接关联开关个数。（由直接关联开关所关联的直接关联开关，自然就是第i个闹钟间接关联开关啦，当打开第i个开关时，只有直接关联，间接关联以及第i个开关才会起作用。），之后M个数，表示第i个闹钟直接关联开关的标号。（如果M为0则表示没有任何关联）
## 输出格式

一个数ans，表示最少按开关次数，如果无法关闭，输出‘Change an alarm clock，please!’
## 样例

### 样例输入 #1
```
5
4 2 3 4 5
2 1 3
2 1 4
2 1 5
1 1
```
### 样例输出 #1
```
2
```
## 提示

样例1说明：


先关闭5，直接关联会关闭1。1间接关闭2、3、4，但会重新打开5。


此时共关闭开关一次，已关闭1，2，3，4


再打开2，直接关联会打开1和3。1间接关闭2、3、5，重新打开4。3间接关闭1、4。


此时共关闭开关2次，已关闭1，2，3，4，5，彻底关闭闹钟。


---

---
title: "[MtOI2018] 衣服？身外之物！"
layout: "post"
diff: 提高+/省选-
pid: P4928
tag: ['2018', '洛谷原创', 'O2优化', '枚举', '进制', '状压 DP']
---
# [MtOI2018] 衣服？身外之物！
## 题目背景

gcd 有许多件衣服，每件衣服有不同的颜色。
## 题目描述

gcd 共有 $n$ 件衣服，编号为 $A_1,A_2,\cdots A_n$。

每一件衣服分别拥有颜色值和清洗时间，他在每一件衣服穿完以后都会将其送去清洗，而这件衣服当天所拥有的舒适感取决于当天的天气与他的衣服颜色值的乘积，天气值存在负数。

现给出共 $m$ 天的天气情况，求最大舒适值。

如果**必定**有一天 gcd 没有衣服穿，输出 "gcd loves her clothes!"（不含引号）。      

## 输入格式

输出共 $4$ 行。

第 $1$ 行输入 $n,m$。

第 $2$ 行输入 $x_1,x_2\cdots x_n$表示衣服的颜色值。     
   
第 $3$ 行输入 $y_1,y_2\cdots y_n$表示衣服的清洗时间。 
  
第 $4$ 行输入 $z_1,z_2\cdots z_m$表示当天的天气值。  
## 输出格式

输出共 $1$ 行，输出 $m$ 天穿衣的最大舒适值或输出 "gcd loves her clothes!"。
## 样例

### 样例输入 #1
```
2 5
5 10
1 1
2 4 3 5 2
```
### 样例输出 #1
```
125
```
## 提示

#### 样例解释 $1$

$A_1:Day_1,Day_3,Day_5$

$A_2:Day_2,Day_4$

### 子任务

对于 $30\%$ 的数据，$n=2$，$m=100$。

对于 $50\%$ 的数据，$n\leq 3$，$m\leq 1000$。

对于 $100\% $的数据，$n\leq 4$，$n\neq 1$，$m\leq 2000$，$y_i\leq 6$，$Maxy<m$，$|z_i|\leq 10^8$。

### 题目来源

[MtOI2018 迷途の家の水题大赛](https://www.luogu.org/contest/11260) T3

出题人：b2019dy

78488


---

---
title: "咕咕咕"
layout: "post"
diff: 提高+/省选-
pid: P4996
tag: ['递推', '进制', '洛谷月赛', '状压 DP']
---
# 咕咕咕
## 题目描述

小 F 是一个能鸽善鹉的同学，他经常把事情拖到最后一天才去做，导致他的某些日子总是非常匆忙。

比如，时间回溯到了 2018 年 11 月 3 日。小 F 望着自己的任务清单：

1. 看 iG 夺冠；
2. 补月赛题的锅。

小 F 虽然经常咕咕咕，但他完成任务也是很厉害的，他一次性可以完成剩余任务的任一**非空子集**。比如，他现在可以选择以下几种中的一种：

1. 看 iG 夺冠；
2. 补月赛题的锅；
3. 一边看 iG 夺冠的直播，一边补锅。

当然，比赛实在是太精彩了，所以小 F 就去看比赛了。

不过，当金雨从天而降、IG 举起奖杯之时，小 F 突然心生愧疚——锅还没补呢！于是，小 F 的内心产生了一点歉意。

这时小 F 注意到，自己总是在某些情况下会产生歉意。每当他要检查自己的任务表来决定下一项任务的时候，如果当前他干了某些事情，但是没干另一些事情，那么他就会产生一定量的歉意——比如，无论他今天看没看比赛，只要没有补完月赛的锅，他都会在选择任务的时候产生 $1$ 点歉意。小 F 完成所有任务后，他这一天的歉意值等于他每次选择任务时的歉意之和。

过高的歉意值让小 F 感到不安。现在，小 F 告诉你他还有 $n$ 项任务，并告诉你在 $m$ 种情况中的一种 $\mathrm{state}_i$ 的情况下，小 F 会产生 $a_i$ 点歉意。请你帮忙计算一下，小 F 在那一天所有可能的完成所有任务方式的歉意值之和是多少。

由于答案可能很大，你只需要输出答案对 $998244353$ 取模即可。
## 输入格式

输入一行两个整数 $n, m$，表示有 $n$ 项任务，在 $m$ 种情况中下小 F 会产生歉意值。

输入接下来 $m$ 行，每行有一个长度为 $n$ 的 $0-1$ 串 $\mathrm{state}_i$ 和一个歉意值 $a_i$，$\mathrm{state}_{i, j}$ 为 $0/1$  表示第 $j$ 项任务此时没做 / 已经做了。

详情请参考样例和样例解释。
## 输出格式

输出一行一个整数，表示小 F 在那一天所有可能的完成任务方式的歉意值之和对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
2 2
00 1
10 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3 4
000 16
001 9
110 4
111 1
```
### 样例输出 #2
```
260
```
## 提示

#### 样例 1 解释：

$0-1$ 串中第一个数字表示小 F 看没看比赛，第二个数字表示小 F 补没补锅。

我们用 $\varnothing$ 表示小 F 什么都没干，$A$ 表示小 F 看了比赛，$B$ 表示小 F 补了锅，那么所有会产生愧疚的方式如下：

$\varnothing: 1$  
$\{A\}:1$

那么所有可能的选择如下：

$\varnothing\rightarrow\{A\}\rightarrow\{A,B\}:2$  
$\varnothing\rightarrow\{B\}\rightarrow\{A,B\}:1$  
$\varnothing\rightarrow\{A,B\}:1$

所以答案是 $2 + 1 + 1 = 4$。

#### 数据范围

保证出现的 $\mathrm{state}_i$ 互不相同。

对于所有数据，有 $1 \leq n \leq 20$, $1 \leq m \leq \min(2 ^ n, 10 ^ 5), 1 \leq a_i \leq 10 ^ 5$。

| Case | $n$ |
| :------:|:------: |
|1|$1$|
|2|$2$|
|3|$3$|
|4|$10$|
|5|$12$|
|6|$14$|
|7|$16$|
|8|$18$|
|9|$19$|
|10|$20$|



---

---
title: "中国象棋 - 摆上马"
layout: "post"
diff: 提高+/省选-
pid: P5005
tag: ['枚举', '进制', '状压 DP']
---
# 中国象棋 - 摆上马
## 题目背景

~~相信自己的做法 大喊一声 I won't MLE！您就会过这道题~~

Imakf 玩腻了国际象棋，决定玩一玩中国象棋。

他发现中国象棋的马和国际象棋的马有所不同，他意识到这又可以出一道简单的问题，于是他又准备摆一摆马了
## 题目描述

Imakf 有一个 $X$ 行 $Y$ 列的棋盘，还有很多**完全相同**的马（你可以认为有无数个）。现在在棋盘上摆上马（或者不摆），求任何马无法攻击另一匹马的方案总数。

中国象棋的马和国际象棋的马不同。

![](https://cdn.luogu.com.cn/upload/pic/40761.png)

注意：实际问题中是没有兵的。

当然由于方案可能过多，请输出对 $(10^9+7)$ 取模的值

## 输入格式

第一行两个正整数 $X,Y$。
## 输出格式

方案对 $(10^9+7)$ 取模的值。
## 样例

### 样例输入 #1
```
1 1 

```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 3 

```
### 样例输出 #2
```
145
```
## 提示

对于 100% 的数据，有 $1\le X\leq100$，$1\le Y\leq6$。

对于 20% 的数据，有 $X,Y\leq6$。

对于另外 20% 的数据，有 $X\leq20$。

对于样例 1，可以选择不摆或者摆。

对于样例 2，我有一个绝妙的解释可惜我写不下。



---

---
title: "[GDCPC 2023] X Equals Y"
layout: "post"
diff: 提高+/省选-
pid: P9699
tag: ['数学', '2023', '广东', 'Special Judge', 'O2优化', '进制', 'XCPC']
---
# [GDCPC 2023] X Equals Y
## 题目描述

For positive integers $X$ and $b \geq 2$, define $f(X,b)$ as a sequence which describes the base-$b$ representation of $X$, where the $i$-th element in the sequence is the $i$-th least significant digit in the base-$b$ representation of $X$. For example, $f(6, 2) = \{0, 1, 1\}$, while $f(233, 17) = \{12, 13\}$.

Given four positive integers $x$, $y$, $A$ and $B$, please find two positive integers $a$ and $b$ satisfying:

- $2 \leq a \leq A$
- $2 \leq b \leq B$
- $f(x, a) = f(y, b)$
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \leq T \leq 10^3$) indicating the number of test cases. For each test case:

The first line contains four integers $x$, $y$, $A$ and $B$ ($1 \leq x,y \leq 10^9$, $2 \leq A,B \leq 10^9$).

It's guaranteed that there are at most $50$ test cases satisfying $\max(x, y) > 10^6$.
## 输出格式

For each test case, if valid positive integers $a$ and $b$ do not exist, output $\texttt{NO}$ in one line.

Otherwise, first output $\texttt{YES}$ in one line. Then in the next line, output two integers $a$ and $b$ separated by a space. If there are multiple valid answers, you can output any of them.
## 样例

### 样例输入 #1
```
6
1 1 1000 1000
1 2 1000 1000
3 11 1000 1000
157 291 5 6
157 291 3 6
10126 114514 789 12345
```
### 样例输出 #1
```
YES
2 2
NO
YES
2 10
YES
4 5
NO
YES
779 9478
```
## 题目翻译

**【题目描述】**

对于正整数 $X$ 与 $b \geq 2$，定义 $f(X,b)$ 为一个描述了 $X$ 在 $b$ 进制表示下的序列，其中序列的第 $i$ 个元素表示 $X$ 在 $b$ 进制表示下从低到高第 $i$ 位的值。例如，$f(6, 2) = \{0, 1, 1\}$，而 $f(233, 17) = \{12, 13\}$。

给定的四个正整数 $x$，$y$，$A$ 和 $B$，请找到两个正整数 $a$ 和 $b$，同时满足：

- $2 \leq a \leq A$
- $2 \leq b \leq B$
- $f(x, a) = f(y, b)$

**【输入格式】**

有多组测试数据。第一行输入一个整数 $T$（$1 \leq T \leq 10^3$）表示测试数据组数。对于每组测试数据：

第一行输入四个整数 $x$，$y$，$A$ 和 $B$（$1 \leq x,y \leq 10^9$，$2 \leq A,B \leq 10^9$）。

保证至多只有 $50$ 组测试数据满足 $\max(x, y) > 10^6$。

**【输出格式】**

对于每组测试数据，如果不存在合法的正整数 $a$ 和 $b$，则输出一行一个字符串 $\texttt{NO}$。

否则，首先输出一行一个字符串 $\texttt{YES}$。下一行输出两个由单个空格分隔的整数 $a$ 和 $b$。如果有多种合法答案，您可以输出任意一种。


---

