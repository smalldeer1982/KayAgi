---
title: "[COTS 2019] 排名 Vezuv"
layout: "post"
diff: 提高+/省选-
pid: P11226
tag: ['2019', 'Special Judge', '字典树 Trie', 'COCI（克罗地亚）']
---
# [COTS 2019] 排名 Vezuv
## 题目背景


译自 [Izborne Pripreme 2019 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2019/) D2T3。$\texttt{1.5s,0.5G}$。
## 题目描述



在某场 ICPC Regional 中，组委会决定用队伍名的字典序来决定排名。不幸的是，对于队名以字母 $\texttt{z}$ 开头的队伍，这是相当不公平的。

经过讨论，组委会决定：随机抽取一个 $26$ 个字母的排列，用字母的排列对应的字典序来决定排名。

有 $N$ 支队伍参加了这场比赛，队伍名都为小写英文字母。

Etna 写了一个程序枚举了 $26!$ 个排列，以期找到能使每个队伍夺冠的排列。但是这个程序至今都没有跑出结果。

所以她找来了你，为每个队伍构造一个排列，使得这支队伍夺冠。

## 输入格式


第一行，一个正整数 $N$；

接下来 $N$ 行，第 $i$ 行一个字符串，表示第 $i$ 支队伍的队伍名。

保证队伍名两两不同。
## 输出格式


输出 $N$ 行：
- 如果可能使得这支队伍获胜，输出一个 $26$ 个字母的排列；
- 否则，输出 `nemoguce`（克罗地亚语「不可能」）。
## 样例

### 样例输入 #1
```
3
war
zag
wro
```
### 样例输出 #1
```
agorwzbcdefhijklmnpqstuvxy
agorzwbcdefhijklmnpqstuvxy
gorawzbcdefhijklmnpqstuvxy
```
### 样例输入 #2
```
3
b
ab
aa
```
### 样例输出 #2
```
bacdefghijklmnopqrstuvwxyz
nemoguce
abcdefghijklmnopqrstuvwxyz
```
### 样例输入 #3
```
7
bcada
dbaab
bbabc
ababb
aacdf
bcdff
baddb
```
### 样例输出 #3
```
cbadfeghijklmnopqrstuvwxyz
cdabfeghijklmnopqrstuvwxyz
bacdfeghijklmnopqrstuvwxyz
nemoguce
abcdfeghijklmnopqrstuvwxyz
cbdafeghijklmnopqrstuvwxyz
nemoguce
```
## 提示


令 $L$ 为字符串总长度，$|\Sigma|$ 为字符串字符集大小。

对于 $100\%$ 的数据，保证：

- $1\le N\le 25\, 000$；
- $1\le L\le 10^6$；
- 队伍名两两不同；
- $1\le |\Sigma|\le 26$。


| 子任务编号 | $N\le $ | $L\le $ | $\vert\Sigma\vert\le$    | 得分 |  
| :--: | :--: |:--: |  :--: | :--: | 
| $ 1 $    | $ 100 $ |   $ 10^4 $   |  $6$ | $13$ |
| $ 2 $    | $ 350 $ |  $ 10^4 $   |  $26 $ | $32$ |
| $ 3 $    | $ 25\, 000 $ | $ 10^6 $   |  $26$ |  $55$ |


---

---
title: "【MX-X9-T3】『GROI-R3』Powerless"
layout: "post"
diff: 提高+/省选-
pid: P11799
tag: ['O2优化', '数位 DP', '字典树 Trie', '梦熊比赛']
---
# 【MX-X9-T3】『GROI-R3』Powerless
## 题目背景

> 你能走到这里很了不起......
## 题目描述

白给了你一个长度为 $n$ 的整数序列 $a_1,\ldots, a_n$ 和一个整数 $m$，她请你求出以下式子的值：

$$ \sum_{i=1}^n \sum_{j=1}^n \sum_{k=0}^m \min(a_i \oplus k, a_j \oplus k)$$

其中，$\oplus$ 表示二进制下按位异或。

由于答案可能很大，所以你仅需要输出答案对 $998244353$ 取模后的值。
## 输入格式

第一行，两个非负整数 $n, m$。

第二行，$n$ 个非负整数 $a_1, \ldots, a_n$。
## 输出格式

仅一行，一个整数，表示答案对 $998244353$ 取模后的值。
## 样例

### 样例输入 #1
```
2 3
1 5

```
### 样例输出 #1
```
40

```
### 样例输入 #2
```
5 7
1 2 3 4 5

```
### 样例输出 #2
```
460

```
### 样例输入 #3
```
10 197
1 5 102 289 445 326 117 64 100 266

```
### 样例输出 #3
```
2788560

```
### 样例输入 #4
```
10 0
3701780 6015893 9822195 8016360 992671 8828219 5674666 4815987 1784800 995151

```
### 样例输出 #4
```
333221210

```
### 样例输入 #5
```
8 33554432
2117455 10849252 28912108 3049487 10134324 20812345 26061978 24220183

```
### 样例输出 #5
```
42695030

```
### 样例输入 #6
```
8 51937970
93102591 5826965 25429632 51808294 13143740 21293750 85706705 22127009

```
### 样例输出 #6
```
345700571

```
### 样例输入 #7
```
13 189320127
90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115

```
### 样例输出 #7
```
425145733

```
### 样例输入 #8
```
10 1000000000
530093637 530093637 530093637 540208320 451233002 540208320 540208320 895132935 619514612 895132935

```
### 样例输出 #8
```
644847220

```
## 提示

**【样例解释 #1】**

当 $i = j = 1$ 时，$\sum\limits_{k=0}^m \min(x_i \oplus k, x_j \oplus k) = (1 \oplus 0) + (1 \oplus 1) + (1 \oplus 2) + (1 \oplus 3) = 1 + 0 + 3 + 2 = 6$；

当 $i = j = 2$ 时，$\sum\limits_{k=0}^m \min(x_i \oplus k, x_j \oplus k) = (5 \oplus 0) + (5 \oplus 1) + (5 \oplus 2) + (5 \oplus 3) = 5 + 4 + 7 + 6 = 22$；

当 $i = 1, j = 2$ 或 $i = 2, j = 1$ 时，$\sum\limits_{k=0}^m \min(x_i \oplus k, x_j \oplus k) = \min(1, 5) + \min(0, 4) + \min(3, 7) + \min(2, 6) = 6$。

因此，答案为 $6 + 22 + 6 \times 2 = 40$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n\le$ | $m\le$ | $a_i\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $100$ | $100$ | $100$ |  | $1$ |
| 2 | $2\times 10^5$ | $0$ | $10^9$ |  | $8$ |
| 3| $3000$ | $10^6$ | $10^6$ |  | $21$ |
| 4 | $2\times 10^5$ | $10^6$ | $10^9$ |  | $16$ |
| 5 | $2\times 10^5$ | $10^9$ | $10^9$ | A | $9$ |
| 6 | $2\times 10^5$ | $10^9$ | $10^9$ | B | $24$ |
| 7 | $2\times 10^5$ | $10^9$ | $10^9$ |  |  $21$ |

- 特殊性质 A：保证 $a_1 = a_2 = \cdots = a_n$。
- 特殊性质 B：保证存在非负整数 $k$ 使得 $m = 2^k - 1$。

对于 $100\%$ 的数据，保证 $1 \leq n \leq 2\times 10^5$，$0 \leq m \leq 10^9$，$0 \leq a_i \leq 10^9$。


---

---
title: "[蓝桥杯 2023 国 Java A] 单词分类"
layout: "post"
diff: 提高+/省选-
pid: P12238
tag: ['动态规划 DP', '2023', '树形 DP', '字典树 Trie', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Java A] 单词分类
## 题目描述

在遥远的 LQ 国，只存在三种字符：$\tt{l}$、$\tt{q}$ 和 $\tt{b}$（ASCII 码分别为 $108$、$113$、$98$），所有的单词都由这三种字符组合而来。小蓝为了更加快速的记忆单词，决定将词典上所有的单词按照单词前缀将其分为 $K$ 类，具体的要求是:

1. 选出 $K$ 个不同的单词前缀作为 $K$ 类；
2. 对于字典上的每个单词，只能属于 $K$ 类中的某一个类，不能同时属于多个类；
3. 对于 $K$ 类中的每个类，至少包含有一个单词。

现在已知字典上一共有 $N$ 个单词，小蓝想要知道将这 $N$ 个单词按照上述要求分为 $K$ 类，一共有多少种不同的方案。两个方案不同指的是两个方案各自选出的 $K$ 个单词前缀不完全相同。答案可能过大，所以你需要将答案对 $1\,000\,000\,007$（即 $10^9 + 7$）取模后输出。
## 输入格式

输入的第一行包含两个整数 $N$ 和 $K$；

接下来 $N$ 行，每行包含一个单词，由 $\tt{l}$、$\tt{q}$、$\tt{b}$ 三种字符组成。
## 输出格式

输出一个整数表示答案。答案可能很大，请输出答案对 $1\,000\,000\,007$ 取模的值。
## 样例

### 样例输入 #1
```
4 2
lqb
lql
qqq
qql
```
### 样例输出 #1
```
4
```
## 提示

### 样例说明

- 方案 1：$\tt{l}=\tt{lqb}, \tt{lql}$、$\tt{q}=\tt{qqq}, \tt{qql}$；
- 方案 2：$\tt{lq}=\tt{lqb}, \tt{lql}$、$\tt{q}=\tt{qqq}, \tt{qql}$；
- 方案 3：$\tt{l}=\tt{lqb}, \tt{lql}$、$\tt{qq}=\tt{qqq}, \tt{qql}$；
- 方案 4：$\tt{lq}=\tt{lqb}, \tt{lql}$、$\tt{qq}=\tt{qqq}, \tt{qql}$。

以方案 $1$ 为例，他表示选出的两类对应的前缀分别是 $\tt l$ 和 $\tt q$，属于前缀 $\tt l$ 的单词有 $\tt {lqb}$、$\tt{lql}$，属于前缀 $\tt q$ 的单词有 $\tt{qqq}$、$\tt{qql}$，方案 $1$ 将四个单词按照前缀分成了两类，且每类至少包含一个单词，每个单词仅属于一类，所以方案 $1$ 满足题意。

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$1 \leq N \leq 10$，$1 \leq K \leq 5$；
- 对于 $50\%$ 的评测用例，$1 \leq N \leq 50$，$1 \leq K \leq 10$；
- 对于所有评测用例，$1 \leq N \leq 200$，$1 \leq K \leq 100$，$1 \leq$ 单词长度 $\leq 10$。


---

---
title: "[USACO12DEC] First! G"
layout: "post"
diff: 提高+/省选-
pid: P3065
tag: ['字符串', '2012', 'USACO', '哈希 hashing', '字典树 Trie']
---
# [USACO12DEC] First! G
## 题目描述

Bessie has been playing with strings again. She found that by

changing the order of the alphabet she could make some strings come before all the others lexicographically (dictionary ordering).

For instance Bessie found that for the strings "omm", "moo", "mom", and "ommnom" she could make "mom" appear first using the standard alphabet and that she could make "omm" appear first using the alphabet

"abcdefghijklonmpqrstuvwxyz".  However, Bessie couldn't figure out any way to make "moo" or "ommnom" appear first.

Help Bessie by computing which strings in the input could be

lexicographically first by rearranging the order of the alphabet.  To compute if string X is lexicographically before string Y find the index of the first character in which they differ, j.  If no such index exists then X is lexicographically before Y if X is shorter than Y.  Otherwise X is lexicographically before Y if X[j] occurs earlier in the alphabet than Y[j].

Bessie 一直在研究字符串。她发现，通过改变字母表的顺序，她可以按改变后的字母表来排列字符串（字典序大小排列）。

例如，Bessie 发现，对于字符串 $\texttt{omm},\texttt{moo},\texttt{mom}$ 和 $\texttt{ommnom}$，她可以使用标准字母表使 $\texttt{mom}$ 排在第一个（即字典序最小），她也可以使用字母表 $\texttt{abcdefghijklonmpqrstuvwxyz}$ 使得 $\texttt{omm}$ 排在第一个。然而，Bessie 想不出任何方法（改变字母表顺序）使得 $\texttt{moo}$ 或 $\texttt{ommnom}$ 排在第一个。

接下来让我们通过重新排列字母表的顺序来计算输入中有哪些字符串可以排在第一个（即字典序最小），从而帮助 Bessie。

要计算字符串 $X$ 和字符串 $Y$ 按照重新排列过的字母表顺序来排列的顺序，先找到它们第一个不同的字母 $X_i$ 与 $Y_i$，按重排后的字母表顺序比较，若 $X_i$ 比 $Y_i$ 先，则 $X$ 的字典序比 $Y$ 小，即 $X$ 排在 $Y$ 前；若没有不同的字母，则比较 $X$ 与 $Y$ 长度，若 $X$ 比 $Y$ 短，则 $X$ 的字典序比 $Y$ 小，即 $X$ 排在 $Y$ 前。

## 输入格式

\* Line 1: A single line containing N (1 <= N <= 30,000), the number of strings Bessie is playing with.

\* Lines 2..1+N: Each line contains a non-empty string.  The total number of characters in all strings will be no more than 300,000.  All characters in input will be lowercase characters 'a' through 'z'.  Input will contain no duplicate strings.

第 $1$ 行：一个数字 $N$（$1\le N \le 30,000$），表示 Bessie 正在研究字符串的数量。

第 $2\sim N+1$ 行：每行包含一个非空字符串。所有字符串包含的字符总数不会超过 $300,000$。输入中的所有字符都是小写字母，即 $a\sim z$。输入不包含重复的字符串。


## 输出格式

\* Line 1: A single line containing K, the number of strings that could be lexicographically first.

\* Lines 2..1+K: The (1+i)th line should contain the ith string that could be lexicographically first.  Strings should be output in the same order they were given in the input.

\* Line 1: A single line containing K, the number of strings that could be lexicographically first.

\* Lines 2..1+K: The (1+i)th line should contain the ith string that could be lexicographically first.  Strings should be output in the same order they were given in the input.

第 $1$ 行：一个数字 $K$，表示按重排的字母表顺序排列后可以排在第一个的字符串数量。

第 $2\sim K+1$ 行：第 $i+1$ 行包含第 $i$ 个按重排的字母表顺序排列后可以排在第一个的字符串。字符串应该按照它们在输入中的顺序来输出。

## 样例

### 样例输入 #1
```
4
omm
moo
mom
ommnom

```
### 样例输出 #1
```
2
omm
mom

```
## 提示

The example from the problem statement.


Only "omm" and "mom" can be ordered first.

样例即题目描述中给出的例子，只有 $\texttt{omm}$ 和 $\texttt{mom}$ 在各自特定的字典序下可以被排列在第一个。


---

---
title: "AC 自动机（简单版 II）"
layout: "post"
diff: 提高+/省选-
pid: P3796
tag: ['字符串', '字典树 Trie', 'AC 自动机']
---
# AC 自动机（简单版 II）
## 题目描述

有 $N$ 个由小写字母组成的模式串以及一个文本串 $T$。每个模式串可能会在文本串中出现多次。你需要找出**哪些**模式串在文本串 $T$ 中出现的次数最多。

## 输入格式

输入含多组数据。保证输入数据不超过 $50$ 组。

每组数据的第一行为一个正整数 $N$，表示共有 $N$ 个模式串，$1 \leq N \leq 150$。

接下去 $N$ 行，每行一个长度小于等于 $70$ 的模式串。下一行是一个长度小于等于 $10^6$ 的文本串 $T$。保证不存在两个相同的模式串。

输入结束标志为 $N=0$。
## 输出格式

对于每组数据，第一行输出模式串最多出现的次数，接下去若干行每行输出一个出现次数最多的模式串，按输入顺序排列。

## 样例

### 样例输入 #1
```
2
aba
bab
ababababac
6
beta
alpha
haha
delta
dede
tata
dedeltalphahahahototatalpha
0
```
### 样例输出 #1
```
4
aba
2
alpha
haha
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
title: "【AFOI-19】区间与除法"
layout: "post"
diff: 提高+/省选-
pid: P5629
tag: ['线段树', 'ST 表', '字典树 Trie']
---
# 【AFOI-19】区间与除法
## 题目背景

SY 好不容易才解出QM给她的数学题，在恰午饭的时候，QM 向她的脑洞里塞了个幻想的泡泡……SY 戳开一看，又是长长的一串数字!

SY 实在是不想思考了，她决定用小学的除法消灭她脑洞里的数字.
## 题目描述

定义 $op$ 操作意义为将当前数除以 $d$ 并向下取整.

SY 现在有 $m$ 个“原数”，若一个数经过若干次 $op$ 操作(包括 $0$ 次)后能变为这个“原数”，那么这个数是可以被这个“原数”所消灭的。注意，“原数”是不会被消耗的.

现在 SY 想问你,对于一个区间 $[l,r]$，在消灭最多个数的前提下最少需要多少个“原数”？
## 输入格式

第一行 $4$ 个数,分别是 $n,m,d,q$,分别表示数列 $\{a\}$ 元素个数，SY 拥有的 “原数” 个数，$op$ 操作参数，询问个数。

第二行为 $\{a\}$ 数列，即需要被消灭的数列。

第三行为 $m$ 个“原数”。

接下来 $q$ 行，每行两个数 $l$ 和 $r$，表示询问区间为 $[l,r]$。
## 输出格式

按照询问顺序，每一行输出一个整数表示答案.
## 样例

### 样例输入 #1
```
2 3 3 3
0 20
6 6 6
1 1
2 2
1 2

```
### 样例输出 #1
```
0
1
1

```
### 样例输入 #2
```
6 3 3 3
6 5 10 15 19 7
2 5 10
1 6
1 4
4 6

```
### 样例输出 #2
```
3
3
2

```
## 提示

#### 样例解释：

**#样例1** ： $20$ 经过一次 $op$ 操作（除以 $3$ 向下取整）可以变成 $6$，而 $0$ 不能经过若干次 $op$ 操作变成 $6$ 。

所以区间 $[1,1]$ 最多消灭 $0$ 个数，消灭最多数前提下最少需要 $0$ 个 "原数"，区间 $[1,2],[2,2]$ 最多消灭 $1$ 个数，消灭最多数前提下最少需要 $1$ 个 "原数" 。

**#样例2** ： $2$ 能消灭 $\{6,19,7\}$ ， $5$ 能消灭 $\{5,15\}$ ， $10$ 能消灭 $\{10\}$ ， 所以区间 $[1,6],[1,4]$ 最少能用所有 "原数" 全部消灭，区间 $[4,6]$ 能用 $2,5$ 全部消灭。

#### 数据范围：

对于 $30\%$ 的数据：$n\le100,m\leq10, d=2, q\le 10$

对于 $100\%$ 的数据：$n\le5\times 10^{5},m\leq60,2\leq d\leq10,q\le10^{6},0\le a_i,b_i\le 2^{63}$

![](https://cdn.luogu.com.cn/upload/image_hosting/t7pn0p1n.png)

特殊性质：数据经过构造。


---

---
title: "[JSOI2015] 字符串树"
layout: "post"
diff: 提高+/省选-
pid: P6088
tag: ['2015', '各省省选', '江苏', '字典树 Trie']
---
# [JSOI2015] 字符串树
## 题目背景

萌萌买了一颗字符串树的种子，春天种下去以后夏天就能长出一棵很大的字符串树。字符串树很奇特，树枝上都密密麻麻写满了字符串，看上去很复杂的样
子。
## 题目描述

字符串树本质上还是一棵树，即 $N$ 个节点 $N-1$ 条边的连通无向无环图，节点从 $1$ 到 $N$ 编号。与普通的树不同的是，树上的每条边都对应了一个字符串。萌萌和 JYY 在树下玩的时候，萌萌决定考一考 JYY。每次萌萌都写出一个字符串 $S$ 和两个节点 $U,V$，JYY 需要立即回答 $U$ 和 $V$ 之间的最短路径（即 $U,V$ 之间边数最少的路径，由于给定的是一棵树，这样的路径是唯一的）上有多少个字符串以 $S$ 为前缀。

JYY 虽然精通编程，但对字符串处理却不在行。所以他请你帮他解决萌萌的难题。
## 输入格式

输入第一行包含一个整数 $N$，代表字符串树的节点数量。

接下来 $N-1$ 行，每行先是两个数 $U,V$，然后是一个字符串 $S$，表示节点 $U$ 和节点 $V$ 之间有一条直接相连的边，这条边上的字符串是 $S$。输入数据保证给出的是一棵合法的树。

接下来一行包含一个整数 $Q$，表示萌萌的问题数。

接下来 $Q$ 行，每行先是两个数 $U,V$，然后是一个字符串 $S$，表示萌萌的一个问题是节点 $U$ 和节点 $V$ 之间的最短路径上有多少字符串以 $S$ 为前缀。
## 输出格式

输出 $Q$ 行，每行对应萌萌的一个问题的答案。
## 样例

### 样例输入 #1
```
4
1 2 ab
2 4 ac
1 3 bc
3
1 4 a
3 4 b
3 2 ab
```
### 样例输出 #1
```
2
1
1
```
## 提示

对于 $100\%$ 的数据，$1\leq N,Q\leq 10^5$，输入所有字符串长度不超过 $10$ 且只包含 `a~z` 的小写字母。


---

---
title: "[COCI 2016/2017 #1] Cezar"
layout: "post"
diff: 提高+/省选-
pid: P6286
tag: ['字符串', '2016', 'Special Judge', '拓扑排序', '字典树 Trie', 'COCI（克罗地亚）']
---
# [COCI 2016/2017 #1] Cezar
## 题目描述

Mirko 想对 $n$ 个单词进行加密。加密过程是这样的：

1.  选择一个英文字母表的排列作为密钥。
2.  将单词中的 `a` 替换为密钥中的第一个字母，`b` 替换为密钥中的第二个字母……以此类推。

例如，以 `qwertyuiopasdfghjklzxcvbnm` 作为密钥对 `cezar` 加密后，将得到 `etmqk`。

他希望，将所有单词加密并按字典序升序排列后，最初的第 $a_i$ 个单词位于第 $i$ 位。请你判断，这能否实现。如果能，请给出任意一种可行的密钥。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，每行一个字符串，表示待加密的单词。

最后一行 $n$ 个整数，表示 $a_i$。
## 输出格式

**本题使用 Special Judge**。

如果 Mirko 的要求不能实现，输出 `NE`。

否则，输出 `DA`。接下来一行输出任意一种可行的密钥。
## 样例

### 样例输入 #1
```
2
ab
bc
2 1 
```
### 样例输出 #1
```
DA
bacdefghijklmnopqrstuvwxyz 
```
### 样例输入 #2
```
3
abc
bcd
add
1 2 3 
```
### 样例输出 #2
```
NE 
```
### 样例输入 #3
```
3
bbb
ccc
ddd
2 3 1 
```
### 样例输出 #3
```
DA
adbcefghijklmnopqrstuvwxyz 
```
## 提示

#### 【样例解释】

**样例 1 解释**

以 `bacdefghijklmnopqrstuvwxyz` 为密钥加密后，得到：

- `ba`
- `ac`

字典序升序排列后，得到：

- `ac`
- `ba`

原先的第一个单词在第二位，第二个单词在第一位。符合要求。

**样例 3 解释**

以 `adbcefghijklmnopqrstuvwxyz`  为密钥加密后，得到：

- `ddd`
- `bbb`
- `ccc`

字典序升序排列后，得到：

- `bbb`
- `ddd`
- `ccc`

原先的第一个单词在第二位，第二个单词在第三位，第三个单词在第一位。符合要求。

---

#### 数据规模与约定

对于 $100\%$ 的数据，$2\le n\le 100$，$1 \leq a_i \leq n$。

所有单词的长度不超过 $100$，且只包含小写字母。

------------

#### 说明

**题目译自 [COCI2016-2017](https://hsin.hr/coci/archive/2016_2017/) [CONTEST #1](https://hsin.hr/coci/archive/2016_2017/contest1_tasks.pdf) _T3 Cezar_**。


---

---
title: "超超的序列 加强"
layout: "post"
diff: 提高+/省选-
pid: P6587
tag: ['线段树', '字典树 Trie']
---
# 超超的序列 加强
## 题目背景

孙1超总是喜欢疯言疯语，有一天，他随口说出了一串序列，又想对某几个特定位置的值进行修改和求和。由于孙1超十分菜，所以他来找你帮助。

## 请不要抄题解。
## 题目描述

给定序列 $a$，并且给出两种操作：
- `1 x y v`：将所有 $a_i$ 的值加上 $v$，其中 $i\equiv y\pmod {2^x}$。
- `2 x y`：询问所有 $a_i$ 的和，其中 $i\equiv y\pmod {2^ x}$。

**本题强制在线。**



## 输入格式

第一行 $n,m$ 两个整数。

第二行 $n$ 个整数，第 $i$ 个表示 $a_i$。

接下来若干行，每行给出若干个整数：

当 $op=1$ 时，$op'$ 的后三个整数依次为该操作的 $x,y,v$；

当 $op=2$ 时，$op'$ 的后两个个整数依次为该操作的 $x,y$。

其中保证没有多余的数输入。

每次操作的 $op=(\operatorname{lastans}+op')\bmod 2+1$。

其中 $\rm lastans$ 表示上一个输出的答案，若之前没有询问，则 $\rm lastans=0$。
## 输出格式

输出每次询问的结果。
## 样例

### 样例输入 #1
```
5 3
1 2 3 4 6
1 2 1
1 1 1 3
2 0 0
```
### 样例输出 #1
```
7
25
```
## 提示

#### 样例解释
对于样例 1：

- 第一个操作 $op=2$，需要计算贡献的 $i$ 为 $1,5$，答案为 $7$。
- 第二个操作 $op=1$， 需要加上 $3$ 的 $i$ 为 $1,3,5$，将 $a_1,a_3,a_5$ 加上 $3$。
- 第三个操作 $op=2$， 需要计算贡献的 $i$ 为 $1,2,3,4,5$，答案为 $25$。

#### 数据范围
- 对于 $10\%$ 的数据，$1\le n,m \leq 10^3$。
- 对于 $70\%$ 的数据，每一个操作后面有一个换行。 
- 对于 $100\%$ 的数据，$1\le n,m \leq 2\times10^5$，$0 \leq a_i,y,v,op'<10^7$。
- 对于操作 1 和 2，$0\leq x \leq 20$ 且 $0 \le y < 2^x$。



---

---
title: "[COCI 2016/2017 #4] Rima"
layout: "post"
diff: 提高+/省选-
pid: P7537
tag: ['2016', '树形 DP', '字典树 Trie', 'COCI（克罗地亚）']
---
# [COCI 2016/2017 #4] Rima
## 题目描述

规定字符串 $A,B$ 的最长公共后缀的长度为 $\text{LCS}(A,B)$。

当 $\text{LCS}(A,B) \ge \max(|A|,|B|)-1$ 时，我们认为 $A,B$ 两个字符串押韵。

给定 $N$ 个字符串，要求从中组合出一个长度最长的字符串序列（序列长度为该序列所包含字符串的数量），使得序列中相邻两个字符串押韵。
## 输入格式

第一行，一个整数 $N$。

接下来的 $N$ 行，每行一个字符串。保证所有字符串互不相同，且总长度不超过 $3 \times 10^6$。
## 输出格式

输出字符串序列长度的最大值。
## 样例

### 样例输入 #1
```
4
honi
toni
oni
ovi
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5
ask
psk
krafna
sk
k
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
5
pas
kompas
stas
s
nemarime
```
### 样例输出 #3
```
1
```
## 提示

**【样例 2 解释】**

字符串序列 $\texttt{ask-psk-sk-k}$ 长度最大，为 $4$。

**【样例 3 解释】**

没有任何两个字符串押韵，因此任何一个字符串都可以单独组成一个序列，答案为 $1$。

**【数据规模与约定】**

对于 $30\%$ 的数据，$N \le 18$。

对于 $100\%$ 的数据，$1 \le N \le 5 \times 10^5$。

**【提示与说明】**

**题目译自 [COCI 2016-2017](https://hsin.hr/coci/archive/2016_2017/) [CONTEST #4](https://hsin.hr/coci/archive/2016_2017/contest4_tasks.pdf) _T5 Rima_。**

**本题分值按 COCI 原题设置，满分 $140$。**


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
title: "[JOI Open 2016] 销售基因链"
layout: "post"
diff: 提高+/省选-
pid: P9196
tag: ['2016', '字典树 Trie', 'JOI（日本）']
---
# [JOI Open 2016] 销售基因链
## 题目背景

**译自 [JOI Open 2016](https://contests.ioi-jp.org/open-2016/index.html) T2 「RNA 鎖の販売 / Selling RNA Strands」**

本题由于测试数据过多，仅在此提供部分测试数据，剩余数据请[于此测试](https://www.luogu.com.cn/problem/U288877)。
## 题目描述

基因库中有 $N$ 个字符串，这些字符串仅由 `A`，`G`，`U`，`C` 组成（保证每个字符串都包含四种字母）。

有 $M$ 组查询，每组查询包含两个字符串 $P,Q$，试求：基因库中有多少个字符串同时存在前缀 $P$ 和后缀 $Q$。

举个例子，`GAC` 存在前缀 `G`、`GA`、`GAC`，存在后缀 `C`、`AC`、`GAC`，那么我们可以说：`GAC` 同时存在前缀 `GA` 和后缀 `AC`。
## 输入格式

输入共 $N + M + 1$ 行。

第一行有两个整数 $N, M$。  
在接下来的 $N$ 行中，每行一个字符串 $S_i$，表示基因库中的一个字符串。  
在接下来的 $M$ 行中，每行有两个用空格分隔的字符串，表示一组查询。
## 输出格式

输出共 $M$ 行，每行一个整数，表示符合查询条件的字符串的数量。
## 样例

### 样例输入 #1
```
2 3
AUGC
AGC
G C
AU C
A C
```
### 样例输出 #1
```
0
1
2
```
### 样例输入 #2
```
3 3
AA
AA
AGA
AA AA
AG GA
AG GA
```
### 样例输出 #2
```
2
1
1
```
### 样例输入 #3
```
8 7
GCGCUACCCCAACACAAGGCAAGAUAUA
G
GGAC
GCGG
U
GCGCUACCCCAACACAAGGCAAGAUGGUC
GCCG
GCGCUGA
GCGCUACCC A
GCGCUACCCC AC
GCG C
GCGC A
G G
G C
G GGA
```
### 样例输出 #3
```
1
0
1
2
3
2
0
```
## 提示

### 样例 1 解释

第一组查询：无法找到；  
第二组查询：`AUGC` 满足条件；  
第三组查询：`AUGC` 和 `AGC` 满足条件。

### 样例 2 解释

注意基因库中的字符串可以重复。

### 数据规模与约定

**本题采用捆绑测试**。

对于所有数据，$1\le N, M \leq 10 ^ 5$，$1 \leq |S_i|, |P_j|, |Q_j| \le 10^5$，$1\le\sum |S_i|, \sum |P_j|, \sum |Q_j| \le 2\times 10^6$。

- Subtask 1（10 points）：$N, M, |S_i|, |P_j|, |Q_j| \le 100$。
- Subtask 2（25 points）：$N, M\le 5000$。
- Subtask 3（25 points）：$\sum |S_i|, \sum|P_j|, \sum |Q_j| \le 10^5$。
- Subtask 4（40 points）：没有额外限制。


---

---
title: "[GDCPC 2023] New but Nostalgic Problem"
layout: "post"
diff: 提高+/省选-
pid: P9694
tag: ['2023', '广东', 'O2优化', '字典树 Trie', 'XCPC']
---
# [GDCPC 2023] New but Nostalgic Problem
## 题目描述

Given $n$ strings $w_1, w_2, \cdots, w_n$, please select $k$ strings among them, so that the lexicographic order of string $v$ is minimized, and output the optimal string $v$. String $v$ satisfies the following constraint: $v$ is the longest common prefix of two selected strings with different indices. Also, $v$ is the lexicographically largest string among all strings satisfying the constraint.

More formally, let $\mathbb{S}$ be a set of size $k$, where all the elements in the set are integers between $1$ and $n$ (both inclusive) and there are no duplicated elements. Let $\text{lcp}(w_i, w_j)$ be the longest common prefix of string $w_i$ and $w_j$, please find a set $\mathbb{S}$ to minimize the lexicographic order of the following string $v$ and output the optimal string $v$.

$$
v = \max\limits_{i \in \mathbb{S}, j \in \mathbb{S}, i \ne j} \text{lcp}(w_i, w_j)
$$

In the above expression, $\max$ is calculated by comparing the lexicographic order of strings.

Recall that:
- String $p$ is a prefix of string $s$, if we can append some number of characters (including zero characters) at the end of $p$ so that it changes to $s$. Specifically, empty string is a prefix of any string.
- The longest common prefix of string $s$ and string $t$ is the longest string $p$ such that $p$ is a prefix of both $s$ and $t$. For example, the longest common prefix of ``abcde`` and ``abcef`` is ``abc``, while the longest common prefix of ``abcde`` and ``bcdef`` is an empty string.
- String $s$ is lexicographically smaller than string $t$ ($s \ne t$), if
  - $s$ is a prefix of $t$, or
  - $s_{|p| + 1} < t_{|p| + 1}$, where $p$ is the longest common prefix of $s$ and $t$, $|p|$ is the length of $p$, $s_i$ is the $i$-th character of string $s$, and $t_i$ is the $i$-th character of string $t$.
- Specifically, empty string is the string with the smallest lexicographic order.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $k$ ($2\leq n\leq 10^6$, $2\leq k\leq n$) indicating the total number of strings and the number of strings to be selected.

For the following $n$ lines, the $i$-th line contains a string $w_i$ ($1\leq |w_i|\leq 10^6$) consisting of lower-cased English letters.

It's guaranteed that the total length of all strings of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing one string indicating the answer. Specifically, if the answer is an empty string, print $\texttt{EMPTY}$.
## 样例

### 样例输入 #1
```
2
5 3
gdcpc
gdcpcpcp
suasua
suas
sususua
3 3
a
b
c
```
### 样例输出 #1
```
gdcpc
EMPTY
```
## 题目翻译

**【题目描述】**

给定 $n$ 个字符串 $w_1, w_2, \cdots, w_n$，请选出恰好 $k$ 个字符串，最小化字符串 $v$ 的字典序，并输出这个最优的字符串 $v$。其中 $v$ 满足以下条件：$v$ 是被选出的字符串中，某两个编号不同的字符串的最长公共前缀。而且，$v$ 是所有满足条件的字符串中，字典序最大的字符串。

更正式地，令 $\mathbb{S}$ 表示一个大小为 $k$ 的集合，集合中的元素均为从 $1$ 到 $n$ 的整数（含两端），且没有重复的元素。令 $\text{lcp}(w_i, w_j)$ 表示字符串 $w_i$ 和 $w_j$ 的最长公共前缀，您需要找到一个集合 $\mathbb{S}$ 以最小化下述字符串 $v$ 的字典序，并输出这个最优的字符串 $v$。

$$
v = \max\limits_{i \in \mathbb{S}, j \in \mathbb{S}, i \ne j} \text{lcp}(w_i, w_j)
$$

上式中的 $\max$ 通过字典序比较两个字符串。

请回忆：
- 称字符串 $p$ 是字符串 $s$ 的前缀，若可以在 $p$ 的末尾添加若干个字符（包括零个字符）将它变成 $s$。特别地，空字符串是任意字符串的前缀。
- 字符串 $s$ 和 $t$ 的最长公共前缀是一个最长的字符串 $p$，满足 $p$ 既是 $s$ 的前缀，又是 $t$ 的前缀。例如，``abcde`` 与``abcef`` 的最长公共前缀为 ``abc``，而 ``abcde`` 与 ``bcdef`` 的最长公共前缀为空字符串。
- 称字符串 $s$ 的字典序小于字符串 $t$（$s \ne t$），若
  - $s$ 是 $t$ 的前缀，或
  - $s_{|p| + 1} < t_{|p| + 1}$，其中 $p$ 为 $s$ 和 $t$ 的最长公共前缀，$|p|$ 为 $p$ 的长度，$s_i$ 表示字符串 $s$ 的第 $i$ 个字符，$t_i$ 表示字符串 $t$ 的第 $i$ 个字符。
- 特别地，空字符串是字典序最小的字符串。

**【输入格式】**

有多组测试数据。第一行输入一个整数 $T$ 表示测试数据组数。对于每组测试数据：

第一行输入两个整数 $n$ 和 $k$（$2\leq n\leq 10^6$，$2\leq k\leq n$），表示字符串的总数和需要选择的字符串的数量。

对于接下来 $n$ 行，第 $i$ 行输入一个由小写字母构成的字符串 $w_i$（$1\leq |w_i|\leq 10^6$）。

保证所有数据中字符串长度之和不超过 $10^6$。

**【输出格式】**

每组数据输出一行一个字符串表示答案。特别地，若答案为空字符串，输出 $\texttt{EMPTY}$。


---

---
title: "[NFLSPC #6] 绝不能忘记的事……"
layout: "post"
diff: 提高+/省选-
pid: P9934
tag: ['字符串', 'O2优化', '哈希 hashing', '字典树 Trie']
---
# [NFLSPC #6] 绝不能忘记的事……
## 题目背景

> 那件事…… 绝对不能忘记！
## 题目描述

你在电脑内记录了一条绝对不能忘记的事。但是，因为 1064 病毒的入侵，它被电脑忘记了。更可怕的是，1064 病毒似乎拥有某种跨物种传播的能力，导致你也忘记了这件事。

万幸，在 1064 病毒让你和你的电脑忘记这件事之前，你及时将这件事的记录复制了 $n$ 份。但是，由于你和你的电脑在执行这件艰巨的任务的过程中受到 1064 病毒的影响忘记了很多可以忘记的事，所以你进行的操作有点奇怪。

- 首先，这件事的记录是一个长度未知（因为你已经忘记了它的长度）的字符串，称作 **记录串**。对于一份复制，你将记录串切成了三段非空的字符串 **片段**。**不同复制的场合，切割的方案不一定相同**。你暂且将这三份 **片段** 依次称作 **前面**，**中间** 和 **后面**。
- 因为电脑忘记了很多可以忘记的事，所以某些复制中的某些片段可能被忘记了。具体而言，前面有可能被替换为 `QIANMIANWANGLE`，中间有可能被替换为 `ZHONGJIANWANGLE`，后面有可能被替换为 `HOUMIANWANGLE`；在发生替换的场合，表示电脑 **完全忘记** 了这一段片段；否则，表示电脑 **完全记得** 该片段。
- 你终于想起了一件绝不能忘记的事：那就是那绝不能忘记的记录串中，**恰出现了一次** `NFLSPC#6QIDONG` 作为连续子串。除此之外，记录串中的所有其它字符都是 **小写英文字符**。并且，因为你和你的电脑始终记得这件事有多么重要，所以你在划分的时候，无意中让某一个片段恰好为 `NFLSPC#6QIDONG`；你的电脑也在每一份记录中忠实地记得这一段片段。
- 于是，你的电脑最终还记得的东西，就是：$n$ 份复制，每份复制由三段非空字符串构成，依次表示这份复制的三份片段；其中恰有一段为 `NFLSPC#6QIDONG`，另外两段要么是一串仅由小写英文字母构成的非空串，要么是对应的前面/中间/后面忘了。
- 邪恶的 1064 病毒不肯罢休，它篡改了你电脑中的信息，使得你的 $n$ 份复制不一定是自洽的。

你确信 1064 病毒没有能力篡改过多的信息，并且它绝对敌不过你和你的电脑对彼此牢牢记住的 `NFLSPC#6QIDONG` 的信念。因此，你的复制仍然满足上文中所述的性质（恰有一段是 `NFLSPC#6QIDONG`，另外两段要么忘了要么是小写字母非空串）。

你的目标是，寻找到初始的那绝不能忘记的记录串。这个记录串需要满足的条件是，恰出现一次 `NFLSPC#6QIDONG`，其余字符均是小写英文字符，且其匹配尽量多的复制串。

- 记录串与复制串匹配的要求是，记录串存在一种划分，使得三段划分与复制串的三段分别相同，或者复制串中这段划分忘了（此时本段划分中，记录串为任何非空英文字符串均合法）。

你希望求出该记录串能匹配的最多复制串数目。至于记录串本身，你更希望将它深深地埋藏于心底，因此你不需要求出它。

> 那忘记的事只会使你的心灵更加轻盈 / 那未曾忘记的事则会让你的心灵更加坚硬 /
## 输入格式

**为了避免输入量过大，输入进行了一定程度的压缩。请务必认真阅读输入格式**。

第一行一个正整数 $n$，表示记录数目。

接下来 $n$ 行，每行三个非空字符串，其中第一段要么是非空小写字符串，要么是 `Q`（表示 `QIANMIANWANGLE`），要么是 `N`（表示 `NFLSPC#6QIDONG`），不存在其它可能；第二段则是非空小写字符串、`Z`（表示 `ZHONGJIANWANGLE`）、`N` 三者之一；最后一段是非空小写字符串、`H`（表示 `HOUMIANWANGLE`）、`N` 三者之一。保证三段中恰有一段为 `N`。
## 输出格式

一行一个整数，表示所有记录串中，能匹配的最多的复制的数目。
## 样例

### 样例输入 #1
```
3
N Z H
Q N H
Q Z N

```
### 样例输出 #1
```
1

```
## 提示

对于所有数据，保证输入的所有字符串长度之和不超过 $10 ^ 6$。

- 子任务 1（$20$ 分）：保证复制中除了 `NFLSPC#6QIDONG` 恰出现一次以外，其它部分全部忘记。也即，输入的复制串仅可能为 `N Z H`，`Q N H`，`Q Z N` 三者之一。
- 子任务 2（$30$ 分）：保证所有复制串的 “后面” 段都是 `NFLSPC#6QIDONG`。也即，输入的复制串必然形如 `* * N`，其中 `*` 指代任意符合格式的输入。
- 子任务 3（$50$ 分）：无特殊限制。

Source：NFLSPC #6 J by Troverld


---

