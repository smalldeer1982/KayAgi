---
title: "[蓝桥杯青少年组省赛 2023] 最大的矩形纸片"
layout: "post"
diff: 普及+/提高
pid: B4273
tag: ['2023', '单调栈', '蓝桥杯青少年组']
---
# [蓝桥杯青少年组省赛 2023] 最大的矩形纸片
## 题目描述

一张半边参差不齐的网格纸（网格边长均为 $1$），有一边是完整没有破损的。现要从中剪出一片面积最大的矩形纸片。

给定网格纸中完整边的长度 $N$（$1 \leq N \leq 1\,000\,000$），以及网格中每一列残存部分的高度（$1 \leq$ 高度 $\leq 10\,000$），输出能够剪出的最大矩形纸片面积。
## 输入格式

第一行输入一个正整数 $N$（$1 \leq N \leq 1\,000\,000$），表示纸片完整边的长度。  

第二行输入 $N$ 个正整数（$1 \leq$ 正整数 $\leq 10\,000$），表示每列格子残存部分的高度，两个正整数之间用一个空格隔开。  
## 输出格式

输出一个正整数，表示能够剪出的最大矩形纸片面积。
## 样例

### 样例输入 #1
```
6
3 2 1 4 5 2
```
### 样例输出 #1
```
8
```


---

---
title: "[USACO24OPEN] The 'Winning' Gene S"
layout: "post"
diff: 普及+/提高
pid: P10279
tag: ['USACO', '2024', '单调栈']
---
# [USACO24OPEN] The 'Winning' Gene S
## 题目背景

**注意：本题的内存限制为 512MB，通常限制的 2 倍。**
## 题目描述

在多年举办比赛并看着 Bessie 一次又一次地获得第一名后，Farmer John 意识到这绝非偶然。他得出结论，Bessie 一定将胜利写进了 DNA，于是他开始寻找这种「胜利」基因。

他设计了一个过程来识别这个「胜利」基因的可能候选。他获取了 Bessie 的基因组，为一个长为 $N$ 的字符串 $S$，其中 $1\le N\le 3000$。他选择某个数对 $(K,L)$，其中 $1\le L\le K\le N$，表示「胜利」基因候选的长度将为 $L$，并且将在一个较大的 $K$ 长度子串中进行寻找。为了识别这一基因，他从 $S$ 中取出所有 $K$ 长度的子串，我们将称这样的子串为一个 $K$-mer。对于一个给定的 $K$-mer，他取出其所有长度为 $L$ 的子串，将字典序最小的子串识别为胜利基因候选（如果存在并列则选择其中最左边的子串），然后将该字串在 $S$ 中的起始位置 $p_i$（从 $0$ 开始索引）写入一个集合 $P$。

由于他还没有选定 $K$ 和 $L$，他想知道每对 $(K,L)$ 将有多少个候选。

对于 $1\ldots N$ 中的每一个 $v$，帮助他求出满足 $|P|=v$ 的 $(K,L)$ 对的数量。 
## 输入格式

输入的第一行包含 $N$，为字符串的长度。第二行包含 $S$，为给定的字符串。输入保证所有字符均为大写字符，其中 $s_i\in \texttt A-\texttt Z$，因为奶牛遗传学远比我们的高级。
## 输出格式

对于 $1\ldots N$ 中的每一个 $v$，输出满足 $|P|=v$ 的 $(K,L)$ 对的数量，每行输出一个数。

## 样例

### 样例输入 #1
```
8
AGTCAACG
```
### 样例输出 #1
```
11
10
5
4
2
2
1
1
```
## 提示

### 样例解释 1

在这个测试用例中，输出的第三行为 $5$ 是因为我们发现恰好有 $5$ 对 $K$ 和 $L$ 存在三个「胜利」基因候选。这些候选为（其中 $p_i$ 从 $0$ 开始索引）：

```plain
(4,2) -> P = [0,3,4]
(5,3) -> P = [0,3,4]
(6,4) -> P = [0,3,4]
(6,5) -> P = [0,1,3]
(6,6) -> P = [0,1,2]
```

为了了解 $(4,2)$ 如何得到这些结果，我们取出所有的 $4$-mer

```plain
AGTC
GTCA
TCAA
CAAC
AACG
```

对于每一个 $4$-mer，我们识别出字典序最小的长度为 $2$ 的子串

```plain
AGTC -> AG
GTCA -> CA
TCAA -> AA
CAAC -> AA
AACG -> AA
```

我们取出所有这些子串在原字符串中的位置并将它们添加到集合 $P$ 中，得到 $P=[0,3,4]$。

另一方面，如果我们关注 $(4,1)$ 对，我们会发现这只会得到总共 $2$ 个「胜利」基因候选。如果我们取出所有的 $4$-mer 并识别字典序最小的长度为 $1$ 的子串（用 A，A' 和 A* 来区分不同的 A），我们得到

```plain
AGTC -> A
GTCA' -> A'
TCA'A* -> A'
CA'A*C -> A'
A'A*CG -> A'
```

尽管 A' 和 A* 在最后 3 种情况下字典序均为最小，但最左边的子串优先，因此仅有 A' 在所有这些情况中被视为候选。这意味着 $P=[0,4]$。

### 测试点性质

- 测试点 $2-4$：$N\le 100$。
- 测试点 $5-7$：$N\le 500$。
- 测试点 $8-16$：没有额外限制。


---

---
title: "[UESTCPC 2024] 饮料"
layout: "post"
diff: 普及+/提高
pid: P10334
tag: ['贪心', '2024', 'O2优化', '单调栈', '高校校赛']
---
# [UESTCPC 2024] 饮料
## 题目描述

有一个果汁机，每分钟可以制作一杯任意体积的果汁。

有 $n$ 个人排成一队。第 $i$ 个人将在第 $t_i$ 分钟走到果汁机前，并拿走当前已经制作的果汁中体积最大的一杯。第 $i$ 个人拿到体积大于等于 $a_i$ 的果汁就会满意。如果此时没有果汁，则第 $i$ 个人也会不满意。

问是否能够让所有人满意。如果是，输出让所有人满意所需的果汁体积之和的最小值。
## 输入格式

第一行一个整数 $n$ $(1\leq n\leq 2 \times 10^5)$，表示队伍中人的数量。

接下来一行 $n$ 个整数 $t_1,t_2,\ldots,t_n$ $(1\leq t_1\leq t_2\leq\ldots\leq t_n\leq 10^9)$，其中 $t_i$ 表示第 $i$ 个人到果汁机前的时间。如果两个人的到达时间相同，则按题目给出的顺序从左到右决定先后。

接下来一行 $n$ 个整数 $a_1,a_2,\ldots,a_n$ $(1\leq a_i\leq 10^9)$，其中 $a_i$ 表示第 $i$ 个人对果汁的体积要求。

## 输出格式

如果不能令所有人满意，输出 $-1$。

否则输出一行一个整数，表示所需的最小体积和。
## 样例

### 样例输入 #1
```
5
1 3 4 6 6
3 8 2 7 4
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
5
1 3 4 5 5
3 8 2 7 4
```
### 样例输出 #2
```
26
```
## 提示

样例一解释如下：

| 时间 | 制作 | 取走 |
| :----------: | :----------: | :----------: |
| $1$ | $3$ | $3$ |
| $2$ | $-$ | $-$ |
| $3$ | $8$ | $8$ |
| $4$ | $2$ | $2$ |
| $5$ | $4$ | $-$ |
| $6$ | $7$ | $7,4$ |

样例二解释如下：

| 时间 | 制作 | 取走 |
| :----------: | :----------: | :----------: |
| $1$ | $3$ | $3$ |
| $2$ | $4$ | $-$ |
| $3$ | $8$ | $8$ |
| $4$ | $4$ | $4$ |
| $5$ | $7$ | $7,4$ |
| $6$ | $-$ | $-$ |


---

---
title: "「CZOI-R1」消除威胁"
layout: "post"
diff: 普及+/提高
pid: P10798
tag: ['贪心', 'O2优化', 'ST 表', '单调栈']
---
# 「CZOI-R1」消除威胁
## 题目背景

**本题数据已修复。**
## 题目描述

给定一个序列 $\{A_n\}$。

我们称序列 $A$ 中的一个区间 $[l,r]$ 具有威胁，当且仅当 $1\le l<r\le n$ 且 $A_l=A_r$，且 $\forall i\in[l,r]$ 满足 $|A_i|\le|A_l|$。

你可以操作 $A$ 任意次，每次操作选择一个 $A_i$ 修改为 $-A_i$。请问最后序列 $A$ 中具有威胁的**不同**区间**最少**有多少个？



两个区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 不同，当且仅当 $l_1 \ne l_2$ 或 $r_1 \ne r_2$。


## 输入格式

第一行一个整数 $n$ ，表示 $A$ 的长度。

第二行 $n$ 个整数，表示 $\{A_n\}$。
## 输出格式

第一行一个正整数，表示**最少**的具有威胁的区间个数。
## 样例

### 样例输入 #1
```
8
3 2 1 2 3 -1 3 3
```
### 样例输出 #1
```
2
```
## 提示

**【数据范围】**

**本题采用捆绑测试**。
- Subtask #1（$10\text{ pts}$）：$n\le10$。
- Subtask #2（$10\text{ pts}$）：$n\le10^3$。
- Subtask #3（$10\text{ pts}$）：$|A_i|\le60$。
- Subtask #4（$10\text{ pts}$）：$|A_i|$ 均相等。
- Subtask #5（$20\text{ pts}$）：$n\le10^5$。
- Subtask #6（$40\text{ pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le n\le5\times10^5$，$|A_i|\le10^9$。


---

---
title: "「ROI 2025 Day1」奥林匹克楼梯"
layout: "post"
diff: 普及+/提高
pid: P12501
tag: ['2025', '单调栈', 'ROI（俄罗斯）']
---
# 「ROI 2025 Day1」奥林匹克楼梯
## 题目描述

**译自 [ROI 2025](https://neerc.ifmo.ru/school/archive/2024-2025.html) Day1 T1.** ***[Лестница для участников олимпиады](https://neerc.ifmo.ru/school/archive/2024-2025/ru-olymp-roi-2025-day1.pdf)***

在天狼星教育中心，学生们最喜欢聚集和交流的地方莫过于各式各样的楼梯。然而，信息学奥林匹克的参与者数量远远超过了其他任何教育项目的学生，现有的楼梯已无法满足需求。因此，装备部门决定利用一块特殊的模板，打造一座全新的楼梯。

这块模板是一个由 $h$ 行 $w$ 列组成的表格，行从上到下、列从左到右依次编号。表格的每个格子中记录了一个数字，要么是 `0`，要么是 `1`。而所谓的楼梯，只能由那些格子中填有 `1` 的格子构成。

楼梯是由若干连续行中填有 `1` 的格子集合组成的。在每一行中，被选中的格子必须形成一个连续的段。  
同时，满足以下条件：  
- 每下一行的选中格子数量不得少于紧邻其上的上一行；  
- 每行中最左边的选中格子必须位于同一列。

下图展示了一个楼梯的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/l57xqjcb.png)

你的任务是找出给定表格中，能够构成楼梯的最大格子数量。
## 输入格式

输入的第一行包含两个整数 $h$ 和 $w$ $(1 \le h, w \le 2 \cdot 10^5, h \cdot w \le 4 \cdot 10^6)$，分别表示表格的行数和列数。

接下来的 $h$ 行，每行包含 $w$ 个字符，每个字符为 `0` 或 `1`，表示表格中对应格子的数字。
## 输出格式

输出一个整数，表示能够构成楼梯的最大格子数量。
## 样例

### 样例输入 #1
```
6 4
0011
1101
0111
1110
0111
0100
```
### 样例输出 #1
```
8
```
## 提示

样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/prkfqb5m.png)

详细子任务附加限制及分值如下表所示。其中子任务 $0$ 是样例。

| 子任务 | 分值 | 附加限制 | 
| :-: | :-: | :-: |
| $1$        | $25$ | $h, w \le 50$ |
| $2$        | $25$ | $h, w \le 400$ |
| $3$        | $25$ | $h \cdot w \le 200\,000$ |
| $4$        | $25$ | 无附加限制 |


---

---
title: "[GCJ 2013 #1A] Manage your Energy"
layout: "post"
diff: 普及+/提高
pid: P13286
tag: ['贪心', '2013', '单调栈', 'Google Code Jam']
---
# [GCJ 2013 #1A] Manage your Energy
## 题目描述

You've got a very busy calendar today, full of important stuff to do. You worked hard to prepare and make sure all the activities don't overlap. Now it's morning, and you're worried that despite all of your enthusiasm, you won't have the energy to do all of this with full engagement.

You will have to manage your energy carefully. You start the day full of energy - $E$ joules of energy, to be precise. You know you can't go below zero joules, or you will drop from exhaustion. You can spend any non-negative, integer number of joules on each activity (you can spend zero, if you feel lazy), and after each activity you will regain $R$ joules of energy. No matter how lazy you are, however, you cannot have more than $E$ joules of energy at any time; any extra energy you would regain past that point is wasted.

Now, some things (like solving Code Jam problems) are more important than others. For the $i$th activity, you have a value $v_i$ that expresses how important this activity is to you. The gain you get from each activity is the value of the activity, multiplied by the amount of energy you spent on the activity (in joules). You want to manage your energy so that your total gain will be as large as possible.

Note that you cannot reorder the activities in your calendar. You just have to manage your energy as well as you can with the calendar you have.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case is described by two lines. The first contains three integers: $E$, the maximum (and initial) amount of energy, $R$, the amount you regain after each activity, and $N$, the number of activities planned for the day. The second line contains $N$ integers $v_i$, describing the values of the activities you have planned for today.

## 输出格式

For each test case, output one line containing "Case #x: $y$", where $x$ is the case number (starting from 1) and $y$ is the maximum gain you can achieve by managing your energy that day.
## 样例

### 样例输入 #1
```
3
5 2 2
2 1
5 2 2
1 2
3 3 4
4 1 3 5
```
### 样例输出 #1
```
Case #1: 12
Case #2: 12
Case #3: 39
```
## 提示

**Sample Explanation**

In the first case, we can spend all 5 joules of our energy on the first activity (for a gain of 10), regain 2 and spend them on the second activity. In the second case, we spend 2 joules on the first activity, regain them, and spend 5 on the second. In the third case, our regain rate is equal to the maximum energy, meaning we always recover all energy after each activity - so we can spend full 3 joules on each activity.

**Limits**

- $1 \leq T \leq 100 .$

**Small dataset (12 Pts, Test set 1 - Visible)**

- $1 \leq E \leq 5 .$
- $1 \leq R \leq 5 .$
- $1 \leq N \leq 10 .$
- $1 \leq v_{i} \leq 10 .$

**Large dataset (23 Pts, Test set 2 - Hidden)**

- $1 \leq E \leq 10^{7} .$
- $1 \leq R \leq 10^{7} .$
- $1 \leq N \leq 10^{4} .$
- $1 \leq v_{i} \leq 10^{7} .$


---

---
title: "玉蟾宫"
layout: "post"
diff: 普及+/提高
pid: P4147
tag: ['动态规划 DP', '枚举', '单调栈']
---
# 玉蟾宫
## 题目背景

有一天，小猫 rainbow 和 freda 来到了湘西张家界的天门山玉蟾宫，玉蟾宫宫主蓝兔盛情地款待了它们，并赐予它们一片土地。

## 题目描述

这片土地被分成 $N\times M$ 个格子，每个格子里写着 'R' 或者 'F'，R 代表这块土地被赐予了 rainbow，F 代表这块土地被赐予了 freda。

现在 freda 要在这里卖萌。。。它要找一块矩形土地，要求这片土地都标着 'F' 并且面积最大。

但是 rainbow 和 freda 的 OI 水平都弱爆了，找不出这块土地，而蓝兔也想看 freda 卖萌（她显然是不会编程的……），所以它们决定，如果你找到的土地面积为 $S$，它们每人给你 $S$ 两银子。

## 输入格式

第一行两个整数 $N$，$M$，表示矩形土地有 $N$ 行 $M$ 列。

接下来 $N$ 行，每行 $M$ 个用空格隔开的字符 'F' 或 'R'，描述了矩形土地。

## 输出格式

输出一个整数，表示你能得到多少银子，即 ($3\times \text{最大 'F' 矩形土地面积}$) 的值。

## 样例

### 样例输入 #1
```
5 6 
R F F F F F 
F F F F F F 
R R R F F F 
F F F F F F 
F F F F F F
```
### 样例输出 #1
```
45
```
## 提示

对于 $50\%$ 的数据，$1 \leq N, M \leq 200$。  
对于 $100\%$ 的数据，$1 \leq N, M \leq 1000$。


---

---
title: "「TAOI-1」Apollo"
layout: "post"
diff: 普及+/提高
pid: P9218
tag: ['O2优化', '深度优先搜索 DFS', '最近公共祖先 LCA', '进制', '字典树 Trie', '单调栈']
---
# 「TAOI-1」Apollo
## 题目背景

Execution.

这题原来叫 `std::cout << std::fixed << std::setprecision(1) << 6.5 << '\n';`。

[被当事人删掉的图片.jpg]

**【Upd 2023/04/15 21:42】添加了一组 Hack 数据位于 Subtask 2，#13。现在所有赛时的 $\bm{50}$ 分提交理论上均只能获得 $\bm{30}$ 分。**
## 题目描述

给出 $n$ 个十进制小数 $a_1 \dots a_n$。

对于一个 **数** $a$，定义其精度 $f(a)$ 表示最小的非负整数 $k$ 使得 $10^k\times a$ 为整数；对于整数 $a$，定义 $f(a) = 0$。对于两个十进制小数 $a, b$，定义 $g(a, b)$ 为对于所有 **数** $c \in [\min(a,b), \max(a,b)]$ 的 $f(c)$ 的最小值。

对于所有 $1 \leq i \leq n$，你需要求出 $\sum\limits_{j=1}^ng(a_i, a_j)$ 的值并输出。

定义十进制小数是一个含有整数部分和小数部分的数，其小数部分不为 $0$。之所以描述得这么愚蠢是因为保证输入的每个数都有小数点，但是好像无论什么写法都会有人提出不满，真是抱歉了。~~所以还是得看看被当事人删掉的图片。所以我在这里写闲话有人看得到吗。~~
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，每行一个十进制小数 $a_i$。
## 输出格式

$n$ 行，每行一个整数，分别表示 $i = 1 \dots n$ 对应的答案。
## 样例

### 样例输入 #1
```
5
11.4514
11.4778
11.1338
11.1236
11.4789
```
### 样例输出 #1
```
10
11
9
9
11
```
### 样例输入 #2
```
8
1.1145
1.114
1.1145
1.514
1.19198
1.1154
1.114
1.1145
```
### 样例输出 #2
```
24
21
24
10
18
22
21
24
```
## 提示

### 数据范围

**本题采用捆绑测试。**

令 $\sum\limits_{i=1}^n f(a_i) = t$。

- Subtask 1（15 points）：$a_i \leq 10$，$n \leq 5$，$t \leq 10$。
- Subtask 2（15 points）：$a_i \leq 10$，$n \leq 100$，$t \leq 1000$。
- Subtask 3（20 points）：$n \leq 1722$。
- Subtask 4（15 points）：$a_i \leq 1$。
- Subtask 5（35 points）：无特殊限制。

对于所有数据，$0 \lt a_i \lt 10^9$，$1 \leq n \leq 10^5$，$1 \leq t \leq 3 \times 10^6$，**保证 $\bm{a_i}$ 没有后导 [$\color{black}\bm 0$](https://cdn.luogu.com.cn/upload/image_hosting/pg66fm1z.png)，不保证 $\bm{a_i}$ 互不相同**。

### 样例解释

以 $i = 1$ 为例：

+ $j = 1$：取 $c = 11.4514$，$f(c) = 4$；
+ $j = 2$：取 $c = 11.46$，$f(c) = 2$；
+ $j = 3$：取 $c = 11.2$，$f(c) = 1$；
+ $j = 4$：取 $c = 11.3$，$f(c) = 1$；
+ $j = 5$：取 $c = 11.47$，$f(c) = 2$。

故 $\sum\limits_{j=1}^n g(a_1, a_j) = 4 + 2 + 1 + 1 + 2 = 10$。对于同一个 $j$，上文给出的所有 $c$，都可能有其它的不同的 $c$ 满足 $f(c)$ 同样最小。


---

---
title: "[ROI 2018]  Decryption"
layout: "post"
diff: 普及+/提高
pid: P9290
tag: ['2018', '单调栈', 'ROI（俄罗斯）']
---
# [ROI 2018]  Decryption
## 题目背景

译自 [ROI 2018 Day2](https://neerc.ifmo.ru/school/archive/2017-2018.html) T1. [Расшифровка](https://neerc.ifmo.ru/school/archive/2017-2018/ru-olymp-roi-2018-day2.pdf) ([Decryption](https://codeforces.com/gym/102154/problem/B))。 
## 题目描述

研究表明，汉字的顺序并不一定能影响阅读。科学家们对数列进行了类似的研究。

给一个正整数数列，若数列首项为数列中所有数的最小值，末项为数列中的最大值，则我们称这是个正确的数列。例如，序列 $[1, 3, 2, 4]$ 和 $[1, 2, 1, 2]$ 是正确的，但序列 
$[1, 3, 2]$ 不是。

给出长度为 n 的序列 $[a_1, a_2, \ldots, a_n]$。对于该序列的某个片段 $[a_l, a_{l+1}, \ldots, a_r]$, 若该片段的首项为该片段中的最小值，末项为该片段中的最大值，则我们称这是个正确的片段。

对于给定的序列，请求出该序列至少需要被分成多少段，才能使得每个片段均为正确的片段。序列 $[2, 3, 1, 1, 5, 1]$ 可以分为三个正确的段：$[2, 3]$ 和 $[1, 1, 5]$ 和 $[1]$。

需要编写一个程序，该程序按给定的顺序确定可以划分的最小正确段数。
## 输入格式

第一行一个整数 $n$。

接下来一行 $n$ 个数，分别为 $a_1,a_2,\ldots,a_n$。
## 输出格式

输出可以划分的最小正确段数。
## 样例

### 样例输入 #1
```
5
5 4 3 2 1
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
4
1 3 2 4
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
6
2 3 1 1 5 1
```
### 样例输出 #3
```
3
```
## 提示

对于 $30\%$ 的数据，$1 \leq n \leq 500$。

对于 $60\%$ 的数据，$1 \leq n \leq 5000$。

对于所有数据，$1 \leq n \leq3 \times 10^5$，$1\leq a_i \leq 10^9$。


---

