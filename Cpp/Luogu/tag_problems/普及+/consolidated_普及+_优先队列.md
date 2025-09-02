---
title: "【MX-S6-T1】「KDOI-11」打印"
layout: "post"
diff: 普及+/提高
pid: P11289
tag: ['贪心', 'O2优化', '排序', '优先队列', '梦熊比赛']
---
# 【MX-S6-T1】「KDOI-11」打印
## 题目背景

原题链接：<https://oier.team/problems/S6A>。
## 题目描述

巡的家有 $m$ 台打印机，编号从 $1$ 到 $m$。她有 $n$ 个文件想要打印。其中第 $i$ 个文件会在第 $t_i$ 时刻下发打印命令，打印这个文件需要 $s_i$ 的时间。

每次发送一个文件打印会选择等待时间最短的打印机，如有多个，选择编号最小的。

你需要告诉巡每台打印机打印了哪些文件。

**保证同一时刻不会下发多个打印命令。**
## 输入格式

第一行，两个正整数 $n,m$，表示文件的数量和打印机的数量。

接下来 $n$ 行，每行两个正整数 $s_i,t_i$，表示第 $i$ 个文件需要的打印时间以及下发命令的时刻。保证所有 $t_i$ 互不相同。
## 输出格式

$m$ 行，第 $i$ 行 $k_i + 1$ 个整数：
- 第一个非负整数 $k_i$，表示第 $i$ 台打印机打印的文件数量；
- 接下来 $k_i$ 个正整数，从小到大排序，表示其打印的文件编号。
## 样例

### 样例输入 #1
```
3 3
2 3
2 1
5 2
```
### 样例输出 #1
```
2 1 2
1 3
0
```
## 提示

**【样例解释 #1】**

共有 $3$ 台打印机。按时间顺序，打印命令如下：
- 文件 $2$ 在第 $1$ 秒被下发。此时所有打印机等待时间都是 $0$。因此选择编号最小的 $1$ 号打印机。
- 文件 $3$ 在第 $2$ 秒被下发。此时 $1$ 号打印机正在打印文件 $2$，其余打印机等待时间都是 $0$。因此选择编号最小的 $2$ 号打印机。
- 文件 $1$ 在第 $3$ 秒被下发。此时 $1$ 号打印机已经完成文件 $2$ 的打印，等待时间为 $0$。因此选择 $1$ 号打印机。

故三台打印机分别打印了编号为 $[1,2],[3],[]$ 的文件。

**【样例 #2】**

见附件中的 `print/print2.in` 与 `print/print2.ans`。

该组样例满足测试点 $1\sim 3$ 的约束条件。

**【样例 #3】**

见附件中的 `print/print3.in` 与 `print/print3.ans`。

该组样例满足测试点 $4\sim 9$ 的约束条件。

**【样例 #4】**

见附件中的 `print/print4.in` 与 `print/print4.ans`。

该组样例满足测试点 $18\sim 20$ 的约束条件。

**【数据范围】**

对于所有测试数据，保证：$1\leq n,m\leq 2\times 10^5$，$1\leq s_i,t_i\leq 10^9$，所有 $t_i$ 互不相同。

| 测试点编号  |   $n,m\leq$    | $s_i\leq $ |   $t_i\leq $   |
| :---------: | :------------: | :--------: | :------------: |
|  $1\sim 3$  |      $10$      |   $10^9$   |     $10^9$     |
|  $4\sim 9$  |     $5000$     |   $10^9$   |     $10^9$     |
| $10\sim 13$ | $2\times 10^5$ |    $1$     |     $2\times 10^5$     |
| $14\sim 17$ | $2\times 10^5$ |   $10^9$   | $2\times 10^5$ |
| $18\sim 20$ | $2\times 10^5$ |   $10^9$   |     $10^9$     |




---

---
title: "琪露诺"
layout: "post"
diff: 普及+/提高
pid: P1725
tag: ['动态规划 DP', '单调队列', '优先队列']
---
# 琪露诺
## 题目描述

在幻想乡，琪露诺是以笨蛋闻名的冰之妖精。

某一天，琪露诺又在玩速冻青蛙，就是用冰把青蛙瞬间冻起来。但是这只青蛙比以往的要聪明许多，在琪露诺来之前就已经跑到了河的对岸。于是琪露诺决定到河岸去追青蛙。

小河可以看作一列格子依次编号为 $0$ 到 $N$，琪露诺只能从编号小的格子移动到编号大的格子。而且琪露诺按照一种特殊的方式进行移动，当她在格子 $i$ 时，她只移动到区间 $[i+L,i+R]$ 中的任意一格。你问为什么她这么移动，这还不简单，因为她是笨蛋啊。

每一个格子都有一个冰冻指数 $A_i$，编号为 $0$ 的格子冰冻指数为 $0$。当琪露诺停留在那一格时就可以得到那一格的冰冻指数 $A_i$。琪露诺希望能够在到达对岸时，获取最大的冰冻指数，这样她才能狠狠地教训那只青蛙。

但是由于她实在是太笨了，所以她决定拜托你帮它决定怎样前进。

开始时，琪露诺在编号 $0$ 的格子上，只要她下一步的位置编号大于 $N$ 就算到达对岸。

## 输入格式

第一行三个正整数 $N, L, R$。

第二行共 $N+1$ 个整数，第 $i$ 个数表示编号为 $i-1$ 的格子的冰冻指数 $A_{i-1}$。

## 输出格式

一个整数，表示最大冰冻指数。

## 样例

### 样例输入 #1
```
5 2 3
0 12 3 11 7 -2

```
### 样例输出 #1
```
11


```
## 提示

对于 $60\%$ 的数据，$N \le 10^4$。

对于 $100\%$ 的数据，$N \le 2\times 10^5$，$-10^3 \le  A_i\le 10^3 $，$1 \le L \le R \le N $。数据保证最终答案不超过 $2^{31}-1$。



---

---
title: "[NOI2015] 荷马史诗"
layout: "post"
diff: 普及+/提高
pid: P2168
tag: ['贪心', '2015', '堆', 'NOI', '优先队列', '霍夫曼树']
---
# [NOI2015] 荷马史诗
## 题目背景

> 追逐影子的人，自己就是影子 —— 荷马
## 题目描述

Allison 最近迷上了文学。她喜欢在一个慵懒的午后，细细地品上一杯卡布奇诺，静静地阅读她爱不释手的《荷马史诗》。但是由《奥德赛》和《伊利亚特》 组成的鸿篇巨制《荷马史诗》实在是太长了，Allison 想通过一种编码方式使得它变得短一些。

一部《荷马史诗》中有 $n$ 种不同的单词，从 $1$ 到 $n$ 进行编号。其中第 $i$ 种单词出现的总次数为 $w_i$。Allison 想要用 $k$ 进制串 $s_i$ 来替换第 $i$ 种单词，使得其满足如下要求：

对于任意的 $1\leq i, j\leq n$ ，$i\ne j$ ，都有：$s_i$ 不是 $s_j$ 的前缀。

现在 Allison 想要知道，如何选择 $s_i$，才能使替换以后得到的新的《荷马史诗》长度最小。在确保总长度最小的情况下，Allison 还想知道最长的 $s_i$ 的最短长度是多少？

一个字符串被称为 $k$ 进制字符串，当且仅当它的每个字符是 $0$ 到 $k-1$ 之间（包括 $0$ 和 $k-1$ ）的整数。

字符串 $str1$ 被称为字符串 $str2$ 的前缀，当且仅当：存在 $1 \leq t\leq m$ ，使得 $str1 = str2[1..t]$。其中，$m$ 是字符串 $str2$ 的长度，$str2[1..t]$ 表示 $str2$ 的前 $t$ 个字符组成的字符串。
## 输入格式

输入的第 $1$ 行包含 $2$ 个正整数 $n, k$ ，中间用单个空格隔开，表示共有 $n$ 种单词，需要使用 $k$ 进制字符串进行替换。

接下来 $n$ 行，第 $i + 1$ 行包含 $1$ 个非负整数 $w_i$，表示第 $i$ 种单词的出现次数。
## 输出格式

输出包括 $2$ 行。

第 $1$ 行输出 $1$ 个整数，为《荷马史诗》经过重新编码以后的最短长度。

第 $2$ 行输出 $1$ 个整数，为保证最短总长度的情况下，最长字符串 $s_i$ 的最短长度。
## 样例

### 样例输入 #1
```
4 2
1
1
2
2

```
### 样例输出 #1
```
12
2
```
### 样例输入 #2
```
6 3
1
1
3
3
9
9

```
### 样例输出 #2
```
36
3

```
## 提示

#### 【样例解释】

#### 样例 1 解释

用 $X(k)$ 表示 $X$ 是以 $k$ 进制表示的字符串。

一种最优方案：令 $00(2)$ 替换第 $1$ 种单词， $01(2)$ 替换第 2 种单词， $10(2)$ 替换第 $3$ 种单词，$11(2)$ 替换第 $4$ 种单词。在这种方案下，编码以后的最短长度为：

$1 × 2 + 1 × 2 + 2 × 2 + 2 × 2 = 12$

最长字符串 $s_i$ 的长度为 $2$ 。

一种非最优方案：令 $000(2)$ 替换第 $1$ 种单词，$001(2)$ 替换第 $2$ 种单词，$01(2)$ 替换第 $3$ 种单词，$1(2)$ 替换第 $4$ 种单词。在这种方案下，编码以后的最短长度为：

$1 × 3 + 1 × 3 + 2 × 2 + 2 × 1 = 12$

最长字符串 $s_i$ 的长度为 $3$ 。与最优方案相比，文章的长度相同，但是最长字符串的长度更长一些。

#### 样例 2 解释

一种最优方案：令 $000(3)$ 替换第 $1$ 种单词，$001(3)$ 替换第 $2$ 种单词，$01(3)$ 替换第 $3$ 种单词， $02(3)$ 替换第 $4$ 种单词， $1(3)$ 替换第 5 种单词， $2(3)$ 替换第 $6$ 种单词。

#### 【数据规模与约定】

所有测试数据的范围和特点如下表所示（所有数据均满足 $0 < w_i \leq 10^{11}$）：

| 测试点编号 |  $n$ 的规模  | $k$ 的规模 |            备注            |
| :--------: | :----------: | :--------: | :------------------------: |
|    $1$     |    $n=3$     |   $k=2$    |                            |
|    $2$     |    $n=5$     |   $k=2$    |                            |
|    $3$     |    $n=16$    |   $k=2$    |     所有 $w_i$ 均相等      |
|    $4$     |  $n=1\,000$  |   $k=2$    | $w_i$ 在取值范围内均匀随机 |
|    $5$     |  $n=1\,000$  |   $k=2$    |                            |
|    $6$     | $n=100\,000$ |   $k=2$    |                            |
|    $7$     | $n=100\,000$ |   $k=2$    |     所有 $w_i$ 均相等      |
|    $8$     | $n=100\,000$ |   $k=2$    |                            |
|    $9$     |    $n=7$     |   $k=3$    |                            |
|    $10$    |    $n=16$    |   $k=3$    |     所有 $w_i$ 均相等      |
|    $11$    |  $n=1\,001$  |   $k=3$    |     所有 $w_i$ 均相等      |
|    $12$    | $n=99\,999$  |   $k=4$    |     所有 $w_i$ 均相等      |
|    $13$    | $n=100\,000$ |   $k=4$    |                            |
|    $14$    | $n=100\,000$ |   $k=4$    |                            |
|    $15$    |  $n=1\,000$  |   $k=5$    |                            |
|    $16$    | $n=100\,000$ |   $k=7$    | $w_i$ 在取值范围内均匀随机 |
|    $17$    | $n=100\,000$ |   $k=7$    |                            |
|    $18$    | $n=100\,000$ |   $k=8$    | $w_i$ 在取值范围内均匀随机 |
|    $19$    | $n=100\,000$ |   $k=9$    |                            |
|    $20$    | $n=100\,000$ |   $k=9$    |                            |

#### 【提示】

选手请注意使用 64 位整数进行输入输出、存储和计算。

#### 【评分方式】

对于每个测试点：

- 若输出文件的第 $1$ 行正确，得到该测试点 $40\%$ 的分数；
- 若输出文件完全正确，得到该测试点 $100\%$ 的分数。


---

---
title: "[USACO09OPEN] Work Scheduling G"
layout: "post"
diff: 普及+/提高
pid: P2949
tag: ['贪心', '递推', '2009', 'USACO', '优先队列']
---
# [USACO09OPEN] Work Scheduling G
## 题目描述

Farmer John has so very many jobs to do! In order to run the farm efficiently, he must make money on the jobs he does, each one of which takes just one time unit.

His work day starts at time 0 and has 1,000,000,000 time units (!).  He currently can choose from any of N (1 <= N <= 100,000) jobs

conveniently numbered 1..N for work to do. It is possible but

extremely unlikely that he has time for all N jobs since he can only work on one job during any time unit and the deadlines tend to fall so that he can not perform all the tasks.

Job i has deadline D\_i (1 <= D\_i <= 1,000,000,000). If he finishes job i by then, he makes a profit of P\_i (1 <= P\_i <= 1,000,000,000).

What is the maximum total profit that FJ can earn from a given list of jobs and deadlines?  The answer might not fit into a 32-bit integer.



## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 contains two space-separated integers: D\_i and P\_i

## 输出格式

\* Line 1: A single number on a line by itself that is the maximum possible profit FJ can earn.

## 样例

### 样例输入 #1
```
3 
2 10 
1 5 
1 7 

```
### 样例输出 #1
```
17 

```
## 提示

Complete job 3 (1,7) at time 1 and complete job 1 (2,10) at time 2 to maximize the earnings (7 + 10 -> 17).

## 题目翻译

约翰有太多的工作要做。为了让农场高效运转，他必须靠他的工作赚钱，每项工作花一个单位时间。 他的工作日从 $0$ 时刻开始，有 $10^9$ 个单位时间。在任一时刻，他都可以选择编号 $1$ 到 $N$ 的 $N(1 \leq N \leq 10^5)$ 项工作中的任意一项工作来完成。 因为他在每个单位时间里只能做一个工作，而每项工作又有一个截止日期，所以他很难有时间完成所有N个工作，虽然还是有可能。 对于第 $i$ 个工作，有一个截止时间 $D_i(1 \leq D_i \leq 10^9)$，如果他可以完成这个工作，那么他可以获利 $P_i( 1\leq P_i\leq 10^9 )$. 在给定的工作利润和截止时间下，约翰能够获得的利润最大为多少.


---

---
title: "[USACO17JAN] Cow Dance Show S"
layout: "post"
diff: 普及+/提高
pid: P3611
tag: ['模拟', '2017', '线段树', '二分', 'USACO', '优先队列', '队列']
---
# [USACO17JAN] Cow Dance Show S
## 题目描述

After several months of rehearsal, the cows are just about ready to put on their annual dance performance; this year they are performing the famous bovine ballet "Cowpelia".

The only aspect of the show that remains to be determined is the size of the stage. A stage of size $K$ can support $K$ cows dancing simultaneously. The $N$ cows in the herd ($1 \leq N \leq 10,000$) are conveniently numbered $1 \ldots N$ in the order in which they must appear in the dance. Each cow $i$ plans to dance for a specific duration of time $d(i)$. Initially, cows $1 \ldots K$ appear on stage and start dancing. When the first of these cows completes her part, she leaves the stage and cow $K+1$ immediately starts dancing, and so on, so there are always $K$ cows dancing (until the end of the show, when we start to run out of cows). The show ends when the last cow completes her dancing part, at time $T$.

Clearly, the larger the value of $K$, the smaller the value of $T$. Since the show cannot last too long, you are given as input an upper bound $T_{max}$ specifying the largest possible value of $T$. Subject to this constraint, please determine the smallest possible value of $K$.


## 输入格式

The first line of input contains $N$ and $T_{max}$, where $T_{max}$ is an integer of value at most 1 million.

The next $N$ lines give the durations $d(1) \ldots d(N)$ of the dancing parts for cows $1 \ldots N$. Each $d(i)$ value is an integer in the range $1 \ldots 100,000$.

It is guaranteed that if $K=N$, the show will finish in time.


## 输出格式

Print out the smallest possible value of $K$ such that the dance performance will take no more than $T_{max}$ units of time.


## 样例

### 样例输入 #1
```
5 8
4
7
8
6
4
```
### 样例输出 #1
```
4

```
## 题目翻译

### 题目描述

经过几个月的排练，奶牛们基本准备好展出她们的年度舞蹈表演。今年她们要表演的是著名的奶牛芭蕾——“cowpelia”。

表演唯一有待决定的是舞台的尺寸。一个大小为 $K$ 的舞台可以支持 $K$ 头牛同时在舞台上跳舞。在牛群中的 $N$ 头牛按照她们必须出现在舞蹈中的顺序方便地编号为 $1,2,\dots,N$。第 $i$ 头牛计划跳 $d_i$ 的特定持续时间。
一开始，第 $1,2,\dots,K$ 头牛出现在舞台上并开始跳舞。当这些牛中的某一头牛首先完成了她的部分，她会马上离开舞台并且第 $K+1$ 头牛会出现在舞台上并开始跳舞。所以，舞台上总有 $K$ 头奶牛在跳舞（直到表演的尾声，奶牛不够的时候）。当最后一头奶牛完成了她的舞蹈部分，表演结束，共花了 $T$ 个单位时间。

显然，$K$ 的值越大，$T$ 就越小。由于表演不能拖太长，你得知了指定 $T$ 的最大可能值的上限 $T_{max}$。请根据这个约束，确定 $K$ 的最小值。

### 输入格式

第一行包括 $N$ 和 $T_{max}$ 两个整数。

接下来的 $N$ 行，第 $i$ 行给出了第 $i$ 头牛跳舞的持续时间 $d_i$。第 $i$ 行包括一个整数 $d_i$。

保证 $K=N$ 时表演会按时完成。

### 输出格式

输出在表演时间不大于 $T_{max}$ 时的 $K$ 的最小可能值。

### 提示说明

对于 $100\%$ 的数据，$1 \le N \le 10^4$，$T_{max} \le 10^6$，$1 \le d_i \le 10^5$。


---

---
title: "[JSOI2007] 建筑抢修"
layout: "post"
diff: 普及+/提高
pid: P4053
tag: ['贪心', '2007', '各省省选', '江苏', '优先队列']
---
# [JSOI2007] 建筑抢修
## 题目描述

小刚在玩 JSOI 提供的一个称之为“建筑抢修”的电脑游戏：经过了一场激烈的战斗，T 部落消灭了所有 Z 部落的入侵者。但是 T 部落的基地里已经有 $N$ 个建筑设施受到了严重的损伤，如果不尽快修复的话，这些建筑设施将会完全毁坏。现在的情况是：T 部落基地里只有一个修理工人，虽然他能瞬间到达任何一个建筑，但是修复每个建筑都需要一定的时间。同时，修理工人修理完一个建筑才能修理下一个建筑，不能同时修理多个建筑。如果某个建筑在一段时间之内没有完全修理完毕，这个建筑就报废了。你的任务是帮小刚合理的制订一个修理顺序，以抢修尽可能多的建筑。

## 输入格式

第一行，一个整数 $N$。

接下来 $N$ 行，每行两个整数 $T_1,T_2$ 描述一个建筑：修理这个建筑需要 $T_1$ 秒，如果在 $T_2$ 秒之内还没有修理完成，这个建筑就报废了。

## 输出格式

输出一个整数 $S$，表示最多可以抢修 $S$ 个建筑。

## 样例

### 样例输入 #1
```
4
100 200
200 1300
1000 1250
2000 3200
```
### 样例输出 #1
```
3
```
## 提示

对于 $100 \%$ 的数据，$1 \le N < 150000$，$1 \le T_1 < T_2 < 2^{31}$。


---

---
title: "[BalticOI 2011] Switch the Lamp On 电路维修 (Day1)"
layout: "post"
diff: 普及+/提高
pid: P4667
tag: ['2011', '线段树', '优先队列', '最短路', 'BalticOI（波罗的海）']
---
# [BalticOI 2011] Switch the Lamp On 电路维修 (Day1)
## 题目描述

Casper is designing an electronic circuit on a $N \times M$ rectangular grid plate. There are $N \times M$ square tiles that are aligned to the grid on the plate. Two (out of four) opposite corners of each tile are connected by a wire.

A power source is connected to the top left corner of the plate. A lamp is connected to the bottom right corner of the plate. The lamp is on only if there is a path of wires connecting power source to lamp. In order to switch the lamp on, any number of tiles can be turned by 90° (in both directions).

![0](http://ruanx.pw/bzojch/file/2346_0.jpg)

In the picture above the lamp is off. If any one of the tiles in the second column from the right is turned by 90° , power source and lamp get connected, and the lamp is on.

Write a program to find out the minimal number of tiles that have to be turned by 90° to switch the lamp on.
## 输入格式

The first line of input contains two integer numbers $N$ and $M$, the dimensions of the plate. In each of the following $N$ lines there are $M$ symbols – either \ or / – which indicate the direction of the wire connecting the opposite vertices of the corresponding tile.
## 输出格式

There must be exactly one line of output. If it is possible to switch the lamp on, this line must contain only one integer number: the minimal number of tiles that have to be turned to switch on the lamp. If it is not possible, output the string: ``NO SOLUTION``
## 样例

### 样例输入 #1
```
3 5
\\/\\
\\///
/\\\\
```
### 样例输出 #1
```
1
```
## 提示

对于 $40\%$ 的数据，$1 \le N \le 4$，$1 \le M \le 5$。

对于所有数据，$1 \le N,M \le 500$。
## 题目翻译

### 题目描述
Casper 正在设计电路。有一种正方形的电路元件，在它的两组相对顶点中，有一组会用导线连接起来，另一组则不会。有 $N\times M$ 个这样的元件，你想将其排列成 $N$ 行，每行 $M$ 个。 电源连接到板的左上角。灯连接到板的右下角。只有在电源和灯之间有一条电线连接的情况下，灯才会亮着。为了打开灯，任何数量的电路元件都可以转动 90°（两个方向）。

![](https://cdn.luogu.com.cn/upload/pic/1286.png)

![](https://cdn.luogu.com.cn/upload/pic/1285.png)

在上面的图片中，灯是关着的。如果右边的第二列的任何一个电路元件被旋转 90°，电源和灯都会连接，灯被打开。现在请你编写一个程序，求出最小需要多少旋转多少电路元件。

### 输入输出格式

#### 输入格式
输入的第一行包含两个整数 $N$ 和 $M$，表示盘子的尺寸。 在以下 $N$ 行中，每一行有 $M$ 个符号 `\` 或 `/`，表示连接对应电路元件对角线的导线的方向。
#### 输出格式：
如果可以打开灯，那么输出只包含一个整数，表示最少转动电路元件的数量。

如果不可能打开灯，输出 `NO SOLUTION`。


---

---
title: "[USACO19JAN] Redistricting P"
layout: "post"
diff: 普及+/提高
pid: P5202
tag: ['动态规划 DP', '2019', 'USACO', '优先队列']
---
# [USACO19JAN] Redistricting P
## 题目背景

USACO 19 年一月月赛铂金组第一题。
## 题目描述

奶牛们的特大城市，牛都，要进行重新分区了！——这总是一个在居住在这里的两大主要种族（荷斯坦牛和更赛牛）之间富有争议的政治事件，因为两大种族都想要在牛都政府中保持足够的影响力。

牛都的大都市圈由一列 $n$ 块牧草地组成，每块里有一头奶牛，均为荷斯坦牛 (Holstein) 和更赛牛 (Guernsey) 之一。

牛都政府想要将大都市圈划分为若干个连续的区，使得每个区至少包含一块牧草地且至多包含 $k$ 块牧草地，并且每块牧草地恰好属于一个区。由于政府当前由荷斯坦牛控制，她们想要找到一种分区方式能够最小化更赛牛较多或者均势的区的数量（如果更赛牛的数量与荷斯坦牛的数量相等那么这个区就是均势的）。

有一个关心政治的更赛牛团体想要知道政府的分区计划可能会对她们造成多少损害。帮助她们求出最坏情况，也就是更赛牛较多或是均势的区的最小可能的数量。
## 输入格式

输入的第一行是用空格隔开的两个整数，分别代表牧草地的个数 $n$ 和每个区包含草地的上限 $k$。

输入的第二行是一个长度为 $n$ 的字符串 $s$，$s$ 中只含字符 `H` 和 `G`。若 $s$ 的第 $i$ 个字符是 `H`，则代表第 $i$ 块草地上的奶牛是荷斯坦牛，否则是更赛牛。
## 输出格式

输出一行一个整数，代表更赛牛较多或者优势区的最小可能数量。
## 样例

### 样例输入 #1
```
7 2
HGHGGHG
```
### 样例输出 #1
```
3
```
## 提示

### 样例解释

一种可能的划分方式是 $[1],~[2, 3],~[4, 5],~[6, 7]$。第二、四个区是均势的区，第三个区是更赛牛优势的区。

### 数据范围

对于 $100\%$ 的数据，保证 $1 \leq k \leq n \leq 3 \times 10^5$，$s$ 的长度为 $n$，且只含字符 `H` 和 `G`。


---

---
title: "「DPOI-1」道路规划"
layout: "post"
diff: 普及+/提高
pid: P8896
tag: ['贪心', '2022', '洛谷原创', 'O2优化', '优先队列', '构造']
---
# 「DPOI-1」道路规划
## 题目背景

不可以，总司令。
## 题目描述

战场上有 $n$ 个据点，从 $1\sim n$ 编号。**每两个据点**之间**都**有一条双向道路。

一天，总司令来战区巡视，走着走着迷路了，于是愤怒地下达命令，让你把每一条双向道路变成单向的，使得这些道路**不包含环**（否则总司令会迷路）。但由于每个据点的规模互不相同，总司令从第 $i$ 个据点出发沿着单向道路能**直接到达**的据点数量需要在 $[l_i,r_i]$ 之间。换言之，第 $i$ 个点的出度需要在 $[l_i,r_i]$ 之间。你需要告诉总司令有没有可能满足他的需求。
## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

第一行，一个整数 $n$，表示据点数量；

第二行，$n$ 个整数 $l_1, l_2, \dots, l_n$；

第三行，$n$ 个整数 $r_1, r_2, \dots, r_n$。
## 输出格式

对于每组数据：

一行，一个字符串。若可以满足总司令的需求，一行 `YES`；否则，一行 `NO`。
## 样例

### 样例输入 #1
```
2
5
0 1 4 0 0
3 4 4 1 3
3
1 2 2
2 2 2
```
### 样例输出 #1
```
YES
NO
```
### 样例输入 #2
```
见下发文件 road2.in
```
### 样例输出 #2
```
见下发文件 road2.out
```
## 提示

#### 样例 #1 解释
下面是第 $1$ 组数据中一种可行的方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/2uvwlydw.png)

#### 样例 #2 解释
该样例满足测试点 $3 \sim 6$ 的限制。
#### 数据范围
**本题测试点分数不等分。**

|  测试点编号  | $n \le$ | 特殊条件 |每个测试点分数|
| :----------: | :-----------: | :------: | :----: |
|     $1\sim 2$      |     $10$     |   无   |$5$|
|     $3\sim 6$      |     $1000$     |    无     |$5$|
|     $7\sim 8$      |     $10^5$     |    所有 $l_i = i-1$ 或所有 $l_i \geq \min (i, n - 1)$    |$5$|
| $9 \sim 10$  | $10^5$ | $l_i=0$ 或 $r_i=n-1$ |$5$|
| $11 \sim 15$ | $10^5$ | 无 |$10$|

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq l_i \leq r_i < n$，$1 \leq T \leq 10$。


---

---
title: "「MXOI Round 2」队列"
layout: "post"
diff: 普及+/提高
pid: P9588
tag: ['线段树', '倍增', '二分', '平衡树', '树状数组', '单调队列', '洛谷原创', 'O2优化', '优先队列', '前缀和', '队列', '洛谷月赛']
---
# 「MXOI Round 2」队列
## 题目描述

小 C 有一个队列，他要对这个队列进行 $q$ 次操作。操作共四种，参数分别如下：

$1\ x$：这是第一种操作，表示从队尾依次插入 $1,2,3,\cdots,x$；

$2\ y$：这是第二种操作，表示弹出队头的前 $y$ 个元素；

$3\ z$：这是第三种操作，表示查询队列中的第 $z$ 个元素；

$4$：这是第四种操作，表示查询队列中所有元素的最大值。

你需要帮助他维护这个队列，并对于每个第三种操作和第四种操作，输出查询的答案。
## 输入格式

第一行两个整数 $c,q$，其中 $c$ 表示测试点编号。$c=0$ 表示该测试点为样例。

接下来 $q$ 行，每行 $1 \sim 2$ 个整数，表示一个操作，格式见【**题目描述**】。
## 输出格式

对于每个第三种操作和第四种操作，输出一行一个整数，表示查询的答案。
## 样例

### 样例输入 #1
```
0 9
1 5
1 3
2 2
1 4
3 6
3 8
2 4
4
3 3
```
### 样例输出 #1
```
3
2
4
1
```
## 提示

#### 【样例解释 #1】

在进行第四次操作后，队列中的元素依次为 $3,4,5,1,2,3,1,2,3,4$。

在进行第七次操作后，队列中的元素依次为 $2,3,1,2,3,4$。

#### 【样例 #2】

见附加文件中的 `queue/queue2.in` 与 `queue/queue2.ans`。

该样例满足测试点 $1$ 的限制。

#### 【样例 #3】

见附加文件中的 `queue/queue3.in` 与 `queue/queue3.ans`。

该样例满足测试点 $4$ 的限制。

#### 【样例 #4】

见附加文件中的 `queue/queue4.in` 与 `queue/queue4.ans`。

该样例满足测试点 $11$ 的限制。

#### 【样例 #5】

见附加文件中的 `queue/queue5.in` 与 `queue/queue5.ans`。

该样例满足测试点 $15$ 的限制。

#### 【样例 #6】

见附加文件中的 `queue/queue6.in` 与 `queue/queue6.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

设 $\sum x$ 表示单个测试点内 $x$ 之和。

对于 $100\%$ 的数据，$1 \le q \le 2\times 10^5$，$1 \le x,y,z \le 10^9$，$0 \le \sum x \le 2\times10^{14}$，保证在进行第二种操作前队列内元素个数不小于 $y$，在进行第三种操作前队列内元素个数不小于 $z$，在进行第四种操作前队列内元素个数大于 $0$。

|测试点编号|$q \le$|$x \le$|$\sum x \le$|特殊性质|
|:---:|:---:|:---:|:---:|:---:|
|$1\sim3$|$500$|$500$|$2\times10^5$|C|
|$4\sim8$|$5000$|$5000$|$2\times10^7$|无|
|$9\sim10$|$2\times10^5$|$10^9$|$2\times10^{14}$|AB|
|$11\sim12$|$2\times10^5$|$10^9$|$2\times10^{14}$|B|
|$13\sim14$|$2\times10^5$|$10^9$|$2\times10^9$|AC|
|$15\sim16$|$2\times10^5$|$10^9$|$2\times10^9$|C|
|$17\sim18$|$2\times10^5$|$500$|$2\times10^7$|无|
|$19$|$2\times10^5$|$10^9$|$2\times10^9$|无|
|$20$|$2\times10^5$|$10^9$|$2\times10^{14}$|无|

特殊性质 A：没有第二种操作。

特殊性质 B：没有第三种操作。

特殊性质 C：没有第四种操作。


---

