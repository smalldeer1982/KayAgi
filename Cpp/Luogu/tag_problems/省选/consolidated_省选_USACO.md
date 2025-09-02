---
title: "[USACO24JAN] Merging Cells P"
layout: "post"
diff: 省选/NOI-
pid: P10141
tag: ['动态规划 DP', 'USACO', '2024', '概率论']
---
# [USACO24JAN] Merging Cells P
## 题目背景

**注意：本题的内存限制为 512MB，通常限制的两倍。**
## 题目描述

Bessie 正在玩一个著名的在线游戏，游戏中有许多不同编号和大小的细胞。细胞会被其他细胞吞噬，直到只剩下一个胜利者。

有 $N$（$2\le N\le 5000$）个细胞从左到右排成一行，编号为 $1\ldots N$，初始大小为 $s_1,s_2,\ldots,s_N$（$1\le s_i\le 10^5$）。当存在多个细胞时，均匀地随机选择一对相邻细胞，并根据以下规则合并为一个新的细胞：

如果编号为 $a$ 且当前大小为 $c_a$ 的细胞与编号为 $b$ 且当前大小为 $c_b$ 的细胞合并，则合并成的细胞的大小为 $c_a+c_b$，且编号等于较大细胞的编号，并列时则为编号较大的细胞的编号。形式化地说，合并成的细胞的编号为 $\begin{cases}a & c_a>c_b\\b & c_a<c_b\\ \max(a,b) & c_a=c_b \end{cases}$。

对于 $1\ldots N$ 范围内的每个编号 $i$，最终的细胞具有编号 $i$ 的概率可以以 $\frac{a_i}{b_i}$ 的形式表示，其中 $b_i\not \equiv 0 \pmod {10^9+7}$。输出 $a_ib_i^{-1}\pmod {10^9+7}$。 
## 输入格式

输入的第一行包含 $N$。

第二行包含 $s_1,s_2,\ldots,s_N$。 
## 输出格式

对于 $1\ldots N$ 内的每个 $i$ 输出一行，为输出最终的细胞具有编号 $i$ 的概率模 $10^9+7$ 的余数。 
## 样例

### 样例输入 #1
```
3
1 1 1
```
### 样例输出 #1
```
0
500000004
500000004
```
### 样例输入 #2
```
4
3 1 1 1
```
### 样例输出 #2
```
666666672
0
166666668
166666668
```
## 提示

### 样例解释 1

存在两种可能性，其中 $(a,b)\to c$ 表示编号为 $a$ 和 $b$ 的细胞合并成了一个编号为 $c$ 的新的细胞。

$(1, 2) \to 2, (2, 3) \to 2$  
$(2, 3) \to 3, (1, 3) \to 3$

所以有各 $\frac{1}{2}$ 的概率最终的细胞具有编号 $2$ 或 $3$。


### 样例解释 2

六种可能性如下：

$(1, 2) \to 1, (1, 3) \to 1, (1, 4) \to 1$  
$(1, 2) \to 1, (3, 4) \to 4, (1, 4) \to 1$  
$(2, 3) \to 3, (1, 3) \to 1, (1, 4) \to 1$  
$(2, 3) \to 3, (3, 4) \to 3, (1, 3) \to 3$  
$(3, 4) \to 4, (2, 4) \to 4, (1, 4) \to 4$  
$(3, 4) \to 4, (1, 2) \to 1, (1, 4) \to 1$

所以有 $\frac{2}{3}$ 的概率最终的细胞具有编号 $1$，各 $\frac{1}{6}$ 的概率最终的细胞具有编号 $3$ 或 $4$。

### 测试点性质

- 测试点 3：$N\le 8$。
- 测试点 $4-8$：$N\le 100$。
- 测试点 $9-14$：$N\le 500$。
- 测试点 $15-22$：没有额外限制。


---

---
title: "[USACO24JAN] Mooball Teams III P"
layout: "post"
diff: 省选/NOI-
pid: P10142
tag: ['线段树', 'USACO', '2024', '容斥原理']
---
# [USACO24JAN] Mooball Teams III P
## 题目描述

Farmer John 在他的农场上有 $N$ 头牛（$2\le N\le 2\cdot 10^5$），编号为 $1\ldots N$。奶牛 $i$ 位于整数坐标 $(x_i,y_i)$（$1\le x_i,y_i\le N$）。Farmer John 想要挑选两支队伍来玩哞球游戏！

其中一支队伍将是「红队」；另一队将是「蓝队」。对组队只有很少的要求。两队都不能为空，并且 $N$ 头奶牛中的每一头至多只能在一个队中（可以两队都不在）。唯一的其他要求是基于哞球独特的特点：一个无限长的网，必须将其放置为平面中非整数坐标的水平或垂直直线，例如 $x=0.5$。FJ 挑选队伍必须使得可以用网将两队分开。奶牛们不愿意为此进行移动。

帮帮农夫吧！为 Farmer John 计算选择满足上述要求的红队和蓝队的方法数，对 $10^9+7$ 取模。
## 输入格式

输入的第一行包含一个整数 $N$。

以下 $N$ 行每行包含两个空格分隔的整数 $x_i$ 和 $y_i$。输入保证 $x_i$ 组成 $1\ldots N$ 的一个排列，$y_i$ 类似。
## 输出格式

输出一个整数，为选择满足上述要求的红队和蓝队的方法数，对 $10^9+7$ 取模。
## 样例

### 样例输入 #1
```
2
1 2
2 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3
1 1
2 2
3 3
```
### 样例输出 #2
```
10
```
### 样例输入 #3
```
3
1 1
2 3
3 2
```
### 样例输出 #3
```
12
```
### 样例输入 #4
```
40
1 1
2 2
3 3
4 4
5 5
6 6
7 7
8 8
9 9
10 10
11 11
12 12
13 13
14 14
15 15
16 16
17 17
18 18
19 19
20 20
21 21
22 22
23 23
24 24
25 25
26 26
27 27
28 28
29 29
30 30
31 31
32 32
33 33
34 34
35 35
36 36
37 37
38 38
39 39
40 40
```
### 样例输出 #4
```
441563023
```
## 提示

### 样例解释 1

我们可以选择红队为牛 1，蓝队为牛 2，或者相反。无论哪种情况，我们都可以用一个网将两支球队分开（例如，$x=1.5$）。

### 样例解释 2

以下是所有的十种可能的将奶牛分队的方法；第 $i$ 个字符表示第 $i$ 头奶牛的队伍，`R` 表示红队，`B` 表示蓝队，或 `.` 表示第 $i$ 头奶牛不在一个队伍中。 

```plain
RRB
R.B
RB.
RBB
.RB
.BR
BRR
BR.
B.R
BBR
```

### 样例解释 3

以下是所有的十二种可能的将奶牛分队的方法：

```plain
RRB
R.B
RBR
RB.
RBB
.RB
.BR
BRR
BR.
BRB
B.R
BBR
```

### 样例解释 4

确保输出答案对 $10^9+7$ 取模。

### 测试点性质

- 测试点 $5$：$N\le 10$。
- 测试点 $6-9$：$N\le 200$。
- 测试点 $10-13$：$N\le 3000$。
- 测试点 $14-24$：没有额外限制。


---

---
title: "[USACO24FEB] Lazy Cow P"
layout: "post"
diff: 省选/NOI-
pid: P10196
tag: ['线段树', '二分', 'USACO', '2024', 'O2优化', '凸包']
---
# [USACO24FEB] Lazy Cow P
## 题目描述

Bessie 正在努力为美国件算机奥林匹克二月的竞赛准备测试用例。每一分钟，她可以选择不准备测试用例，不花费能量；或者对于某个正整数 $a$，花费 $3^{a−1}$ 能量准备 $a$ 个测试用例。

Farmer John 有 $D$（$1\le D\le 2\cdot 10^5$）个需求。对于第 $i$ 个需求，他告诉 Bessie，在前 $m_i$ 分钟内她总共需要准备至少 $b_i$ 个测试用例（$1\le m_i\le 10^6,1\le b_i\le 10^{12}$）。

令 $e_i$ 为满足前 $i$ 个需求 Bessie 最小需要花费的能量。输出 $e_1,\ldots,e_D$ 模 $10^9+7$ 的余数。 
## 输入格式

输入的第一行包含 $D$。以下 $D$ 行，第 $i$ 行包含两个空格分隔的整数 $m_i$ 和 $b_i$。
## 输出格式

输出 $D$ 行，第 $i$ 行包含 $e_i \bmod 10^9+7$。 
## 样例

### 样例输入 #1
```
4
5 11
6 10
10 15
10 30
```
### 样例输出 #1
```
21
21
25
90
```
### 样例输入 #2
```
2
100 5
100 1000000000000
```
### 样例输出 #2
```
5
627323485
```
### 样例输入 #3
```
20
303590 482848034083
180190 112716918480
312298 258438719980
671877 605558355401
662137 440411075067
257593 261569032231
766172 268433874550
8114 905639446594
209577 11155741818
227183 874665904430
896141 55422874585
728247 456681845046
193800 632739601224
443005 623200306681
330325 955479269245
377303 177279745225
880246 22559233849
58084 155169139314
813702 758370488574
929760 785245728062
```
### 样例输出 #3
```
108753959
108753959
108753959
148189797
148189797
148189797
148189797
32884410
32884410
32884410
32884410
32884410
32884410
32884410
3883759
3883759
3883759
3883759
3883759
3883759
```
## 提示

### 样例解释 1

对于第一个测试用例，

- $i=1$：如果 Bessie 在前 $5$ 天分别制作 $[2,3,2,2,2]$ 个测试用例，她将花费 $3^1+3^2+3^1+3^1+3^1=21$ 单位能量，并在第 $5$ 天结束时制作了 $11$ 个测试用例。
- $i=2$：Bessie 可以遵循上面的策略，确保在第 $5$ 天结束时制作了 $11$ 个测试用例，而这将自动满足第二个需求。
- $i=3$：如果 Bessie 在前 $10$ 天分别制作 $[2,3,2,2,2,0,1,1,1,1]$ 个测试用例，她将花费 $25$ 单位能量并满足所有需求。可以证明她无法花费更少的能量。
- $i=4$：如果 Bessie 在前 $10$ 天每一天制作 $3$ 个测试用例，她将花费 $3^2\cdot 10=90$ 单位能量并满足所有需求。

对于每一个 $i$，可以证明 Bessie 无法花费更少的能量满足前 $i$ 个需求。

### 测试点性质

- 测试点 $4-5$：$D\le 100$，且对于所有 $i$，$m_i\le 100$。
- 测试点 $6-8$：$D\le 3000$。
- 测试点 $9-20$：没有额外限制。


---

---
title: "[USACO24OPEN] Grass Segments G"
layout: "post"
diff: 省选/NOI-
pid: P10281
tag: ['USACO', '2024', 'cdq 分治']
---
# [USACO24OPEN] Grass Segments G
## 题目描述

Bessie 正在数轴的正半轴上种一些草。她有 $N$（$2\le N\le 2\cdot 10^5$）个不同的栽培品种，并将把第 $i$ 个品种种植在区间 $[l_i,r_i]$（$0<l_i<r_i\le 10^9$）内。

此外，品种 $i$ 会在存在某个品种 $j$（$j\neq i$）使得品种 $j$ 与品种 $i$ 重叠至少 $k_i$（$0<k_i\le r_i-l_i$）长度时生长得更好。Bessie 想要评估她所有的品种。对于每一个 $i$，计算 $j\neq i$ 的数量，使得 $j$ 与 $i$ 重叠至少 $k_i$ 长度。 
## 输入格式

输入的第一行包含 $N$。

以下 $N$ 行每行包含三个空格分隔的整数 $l_i$，$r_i$ 和 $k_i$。 
## 输出格式

输出所有品种的答案，每种一行。
## 样例

### 样例输入 #1
```
2
3 6 3
4 7 2
```
### 样例输出 #1
```
0
1
```
### 样例输入 #2
```
4
3 6 1
2 5 1
4 10 1
1 4 1
```
### 样例输出 #2
```
3
3
2
2
```
### 样例输入 #3
```
5
8 10 2
4 9 2
3 7 4
5 7 1
2 7 1
```
### 样例输出 #3
```
0
3
1
3
3
```
## 提示

### 样例解释 1

两品种的重叠部分为 $[4,6]$，长度为 $2$，不小于 $2$ 但并非不小于 $3$。

### 测试点性质

- 测试点 $4-5$：$N\le 5000$。
- 测试点 $6-11$：$k$ 对于所有的区间均相同。
- 测试点 $12-20$：没有额外限制。

此外，对于测试点 $5$，$7$，……，$19$，对于所有 $i$ 有 $r_i\le 2N$。 


---

---
title: "[USACO24OPEN] Identity Theft P"
layout: "post"
diff: 省选/NOI-
pid: P10283
tag: ['贪心', 'USACO', '2024', '字典树 Trie']
---
# [USACO24OPEN] Identity Theft P
## 题目背景

**注意：本题的时间限制和内存限制为 3 秒 和 512MB，分别为通常限制的 1.5 倍和 2 倍。**
## 题目描述

Farmer John 的 $N$（$1\le N\le 10^5$）头奶牛每头都有一个二进制字符串（由字符 `0` 和 `1` 组成的字符串）形式的农场证号。Bessie，最年长的奶牛，记住了所有奶牛的农场证号，还喜欢到处询问奶牛她们的农场证号。

当一头奶牛被询问她的农场证号时，她们会开始报正确的二进制字符串，但有可能会感到困惑并在报完之前停下来。当 Bessie 听到该二进制字符串时，如果它不等于农场上任何一头奶牛的农场证号，她就会耸耸肩走开。然而，如果它等于不同于她所询问的奶牛的另一头奶牛的农场证号，那么她就会认为发生了身份盗用并封锁整个农场。注意，这种情况即使当奶牛报出完整的农场证号时也可能发生。

Farmer John 希望防止这种情况发生，并愿意以添加更多二进制位的方式改变奶牛的农场证号。他可以在一秒钟内在任意一头牛的农场证号末尾添加一个二进制位。求出他所需要的最小时间以防止封锁发生。 
## 输入格式

输入的第一行包含 $N$，为 Farmer John 的农场上的奶牛数量。

以下 $N$ 行，第 $k$ 行包含表示 Farmer John 的农场上第 $k$ 头奶牛的农场证号的二进制字符串。

所有奶牛的农场证号均不为空，且所有农场证号的总长度不超过 $10^6$。 
## 输出格式

输出 Farmer John 需要花费的最小秒数以确保封锁不会发生。 
## 样例

### 样例输入 #1
```
3
1
1
1
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
3
1
11
111
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
3
1
1
11
```
### 样例输出 #3
```
4
```
### 样例输入 #4
```
5
0
01
0011
010
01
```
### 样例输出 #4
```
6
```
### 样例输入 #5
```
14
0
1
1
0
1
0
1
1
1
1
1
0
0
1
```
### 样例输出 #5
```
41
```
## 提示

### 样例解释 1

这一样例满足第一个子任务的性质。

我们可以花费 5 秒使得封锁不可能发生，通过对第一个农场证号添加 `0`，对第二个农场证号添加 `10`，对第三个农场证号添加 `11`，使农场证号变为 `10`，`110` 和 `111`。

你可以证明这不可能在 4 秒或更少的时间内完成。例如，如果你保持所有农场证号不变，则所有 3 头奶牛都具有相同的农场证号 `1`，因此当 Bessie 听到它时，它将始终等于另一头奶牛的农场证号。

作为另一个例子，如果你仅花费 2 秒对第二个农场证号添加 `0`，对第三个农场证号添加 `1`，则农场证号变为 `1`，`10` 和 `11`，因此第二头和第三头奶牛在报她们的农场证号时，可能会停在中间只报出 `1`，而这将等于第一头奶牛的农场证号。

### 样例解释 2

我们可以在 2 秒内使得封锁不可能发生，通过对前两个农场证号添加 `0`，像之前一样使农场证号变为 `10`，`110` 和 `111`。你可以证明这不可能在 1 秒内完成。

### 样例解释 3

我们可以在 4 秒内使得封锁不可能发生，通过对第一个农场证号添加 `00`，对第二个农场证号添加 `01`。你可以证明这不可能在 3 秒或更少的时间内完成。

### 样例解释 5

这一样例满足第一个子任务的性质。

### 测试点性质

- 测试点 $6-7$：所有农场证号的长度均恰好为 $1$。
- 测试点 $8-15$：$N\le 10^2$，且所有农场证号的总长度不超过 $10^3$。
- 测试点 $16-25$：没有额外限制。


---

---
title: "[USACO24OPEN] Splitting Haybales P"
layout: "post"
diff: 省选/NOI-
pid: P10284
tag: ['USACO', '平衡树', '2024', '均摊分析']
---
# [USACO24OPEN] Splitting Haybales P
## 题目描述

Farmer John 想要将干草堆公平地分配给他最喜欢的两头奶牛 Bessie 和 Elsie。他有 $N$（$1\le N\le 2\cdot 10^5$）个降序排序的干草堆，其中第 $i$ 个干草堆有 $a_i$ 单位干草（$2\cdot 10^5\ge a_1\ge a_2\ge \cdots \ge a_N\ge 1$）。

Farmer John 正在考虑将一个连续区间的干草堆 $a_l,\ldots,a_r$ 分配给 Bessie 和 Elsie。他决定按从 $l$ 到 $r$ 的顺序处理干草堆，当处理第 $i$ 个干草堆时他会将其交给当前干草较少的奶牛（如果并列，他会将其交给 Bessie）。

给定 $Q$（$1\le Q\le 2\cdot 10^5$）个询问，每个询问包含三个整数 $l,r,x$（$1\le l\le r\le N$，$|x|\le 10^9$）。对于每个询问，输出如果 Bessie 初始时比 Elsie 多 $x$ 单位干草，在处理干草堆 $l$ 到 $r$ 后 Bessie 将比 Elsie 多多少单位的干草。注意如果 Elsie 最终获得的干草多于 Bessie 则该值为负。
## 输入格式

输入的第一行包含 $N$。

第二行包含 $a_1\ldots a_N$。

第三行包含 $Q$。

以下 $Q$ 行包含 $l,r,x$。 
## 输出格式

输出 $Q$ 行，包含每个询问的答案。
## 样例

### 样例输入 #1
```
2
3 1
15
1 1 -2
1 1 -1
1 1 0
1 1 1
1 1 2
1 2 -2
1 2 -1
1 2 0
1 2 1
1 2 2
2 2 -2
2 2 -1
2 2 0
2 2 1
2 2 2
```
### 样例输出 #1
```
1
2
3
-2
-1
0
1
2
-1
0
-1
0
1
0
1
```
### 样例输入 #2
```
5
4 4 3 1 1
7
1 1 20
1 2 20
1 5 20
1 1 0
1 5 0
1 4 0
3 5 2
```
### 样例输出 #2
```
16
12
7
4
1
2
1
```
## 提示

### 样例解释 1

对于第 1 个询问，Elsie 初始时比 Bessie 多 2 单位干草。然后，在处理干草堆 1 后，Bessie 将收到 3 单位干草，从而 Bessie 将比 Elsie 多 1 单位干草。

对于第 3 个询问，Elsie 和 Bessie 初始时有相同的干草数量。在处理干草堆 1 后，Bessie 将收到 3 单位干草，从而 Bessie 将比 Elsie 多 3 
单位干草。

对于第 9 个询问，Bessie 初始时比 Elsie 多 1 单位干草，然后在处理第 1 个干草堆后，比 Elsie 少 2 单位干草，处理第 2 个干草堆后，比 Elsie 少 1 单位干草。

### 样例解释 2

对于第 5 个询问，有 5 个干草堆需要处理。Bessie 收到 4 单位干草，然后 Elsie 收到 4 单位干草，然后 Bessie 收到 3 单位干草，然后 Elsie 收到 1 单位干草，然后 Elsie 收到 1 单位干草。

### 测试点性质

- 测试点 $3$：$Q\le 100$。
- 测试点 $4-6$：至多存在 $100$ 个不同的 $a_i$。
- 测试点 $7-22$：没有额外限制。


---

---
title: "[USACO24OPEN] Activating Robots P"
layout: "post"
diff: 省选/NOI-
pid: P10285
tag: ['二分', 'USACO', '2024', '状压 DP']
---
# [USACO24OPEN] Activating Robots P
## 题目描述

你和一个机器人初始时位于周长为 $L$（$1\le L\le 10^9$）的圆上的点 $0$ 处。你可以以每秒 $1$ 
单位的速度沿圆周顺时针或逆时针移动。本题中的所有移动都是连续的。

你的目标是放置恰好 $R-1$ 个机器人，使得最终每两个相邻的机器人彼此相距 $L/R$（$2\le R\le 20$，$R$ 整除 $L$）。有 $N$（$1\le N\le 10^5$）个激活点，其中第 $i$ 个激活点位于距点 $0$ 逆时针方向 $a_i$ 距离处（$0\le a_i<L$）处。如果你当前位于一个激活点，你可以立刻在该点放置一个机器人。所有机器人（包括初始的）均以每 $K$ 秒 $1$ 单位的速度逆时针移动（$1\le K\le 10^6$）。

计算达到目标所需要的最小时间。 
## 输入格式

输入的第一行包含 $L$，$R$，$N$ 和 $K$。

第二行包含 $N$ 个空格分隔的整数 $a_1,a_2,\ldots,a_N$。 
## 输出格式

 输出达到目标所需要的最小时间。
## 样例

### 样例输入 #1
```
10 2 1 2
6
```
### 样例输出 #1
```
22
```
### 样例输入 #2
```
10 2 1 2
7
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
32 4 5 2
0 23 12 5 11
```
### 样例输出 #3
```
48
```
### 样例输入 #4
```
24 3 1 2
16
```
### 样例输出 #4
```
48
```
## 提示

### 样例解释 1

我们可以通过顺时针移动在 $4$ 秒内到达点 $6$ 的激活点。此时，初始的机器人将位于点 $2$。再等待 $18$ 秒直到初始机器人位于点 $1$。现在我们可以放置一个机器人以立即获胜。 

### 样例解释 2

我们可以通过顺时针移动在 $3$ 秒内到达点 $7$ 的激活点。此时，初始的机器人将位于点 $1.5$。再等待一秒直到初始机器人位于点 $2$。现在我们可以放置一个机器人以立即获胜。 

### 测试点性质

- 测试点 $5-6$：$R=2$。
- 测试点 $7-12$：$R\le 10,N\le 80$。
- 测试点 $13-20$：$R\le 16$。
- 测试点 $21-24$：没有额外限制。


---

---
title: "[USACO24DEC] All Pairs Similarity P"
layout: "post"
diff: 省选/NOI-
pid: P11458
tag: ['USACO', '2024', '容斥原理', '快速沃尔什变换 FWT', '状压 DP']
---
# [USACO24DEC] All Pairs Similarity P
## 题目描述

**注意：本题的内存限制为 512MB，通常限制的 2 倍。**

Farmer John 的 $N$（$1\le N\le 5\cdot 10^5$）头奶牛都被分配了一个长度为 $K$ 的非全零位串（$1\le K\le 20$）。不同的奶牛可能被分配到相同的位串。

两个位串的 Jaccard 相似度定义为它们的按位与的结果中 $\texttt{1}$ 的数量除以它们的按位或的结果中 $\texttt{1}$ 的数量。例如，位串 $\texttt{11001}$ 和 $\texttt{11010}$ 的 Jaccard 相似度为 $2/4$。

对于每头奶牛，输出她的位串与每头奶牛（包括她自己）的位串的 Jaccard 相似度之和，对 $10^9+7$ 取模。具体地说，如果总和等于一个有理数 $a/b$，其中 $a$ 和 $b$ 是互质的整数，则输出范围 $[0,10^9+7)$ 内的唯一整数 $x$，使得 $bx-a$ 被 $10^9+7$ 整除。
## 输入格式

输入的第一行包含 $N$ 和 $K$。

以下 $N$ 行每行包含一个整数 $i\in (0,2^K)$，表示一头奶牛分配到了 $i$ 的 $K$ 位二进制表示。
## 输出格式

对于每头奶牛输出一行，包含所求的总和，对 $10^9+7$ 取模。

## 样例

### 样例输入 #1
```
4 2
1
1
2
3
```
### 样例输出 #1
```
500000006
500000006
500000005
500000006
```
## 提示

奶牛们分配到了以下的位串：$[\texttt{01}, \texttt{01}, \texttt{10}, \texttt{11}]$。

对于第一头奶牛，总和为 $\text{sim}(1,1)+\text{sim}(1,1)+\text{sim}(1,2)+\text{sim}(1,3)=1+1+0+1/2\equiv 500000006\pmod{10^9+7}$。

第二头奶牛的位串与第一头奶牛相同，所以她的总和也与第一头奶牛相同。

对于第三头奶牛，总和为 $\text{sim}(2,1)+\text{sim}(2,1)+\text{sim}(2,2)+\text{sim}(2,3)=0+0+1+1/2\equiv 500000005\pmod{10^9+7}$。

- 测试点 $2\sim 15$：对于每一个 $K\in \{10,15,16,17,18,19,20\}$ 有两个测试点。


---

---
title: "[USACO24DEC] It's Mooin' Time P"
layout: "post"
diff: 省选/NOI-
pid: P11459
tag: ['动态规划 DP', 'USACO', '2024', '动态规划优化', '凸包']
---
# [USACO24DEC] It's Mooin' Time P
## 题目描述

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。**

Bessie 有一个长度为 $N$（$1\le N\le 3\cdot 10^5$）的字符串，仅由字符 M 和 O 组成。对于字符串中的每个位置 $i$，需要花费 $c_i$ 来将该位置上的字符修改为另一种字符（$1\le c_i\le 10^8$）。

Bessie 认为，如果字符串包含更多长度为 $L$（$1\le L\le \min(N, 3)$）的哞叫会看起来更好。一个长度为 $L$ 的哞叫指的是一个 M 后面跟着 $L-1$ 个 O。

对于从 $1$ 到 $\lfloor N/L\rfloor$ 的每一个正整数 $k$，计算将字符串修改至包含至少 $k$ 个等于长度为 $L$ 的哞叫的子串的最小花费。
## 输入格式

输入的第一行包含 $L$ 和 $N$。

下一行包含 Bessie 的长为 $N$ 的字符串，仅由字符 M 和 O 组成。

下一行包含空格分隔的整数 $c_1\dots c_N$。
## 输出格式

输出 $\lfloor N/L\rfloor$ 行，依次包含每一个 $k$ 的答案。

## 样例

### 样例输入 #1
```
1 4
MOOO
10 20 30 40
```
### 样例输出 #1
```
0
20
50
90
```
### 样例输入 #2
```
3 4
OOOO
50 40 30 20
```
### 样例输出 #2
```
40
```
### 样例输入 #3
```
2 20
OOOMOMOOOMOOOMMMOMOO
44743602 39649528 94028117 50811780 97338107 30426846 94909807 22669835 78498782 18004278 16633124 24711234 90542888 88490759 12851185 74589289 54413775 21184626 97688928 10497142
```
### 样例输出 #3
```
0
0
0
0
0
12851185
35521020
60232254
99881782
952304708
```
### 样例输入 #4
```
3 20
OOOMOMOOOMOOOMMMOMOO
44743602 39649528 94028117 50811780 97338107 30426846 94909807 22669835 78498782 18004278 16633124 24711234 90542888 88490759 12851185 74589289 54413775 21184626 97688928 10497142
```
### 样例输出 #4
```
0
0
0
44743602
119332891
207066974
```
## 提示

- 测试点 $5$：$L=3, N\le 5000$。
- 测试点 $6$：$L=1$。
- 测试点 $7\sim 10$：$L=2$。
- 测试点 $11\sim 18$：$L=3$。


---

---
title: "[USACO25JAN] Photo Op G"
layout: "post"
diff: 省选/NOI-
pid: P11675
tag: ['USACO', '2025']
---
# [USACO25JAN] Photo Op G
## 题目描述

Farmer John 的农场充满了茂盛的植被，每头奶牛都想拥有一张这里的自然美景的照片。不幸的是，Bessie 还有其他地方要去，但她不想打扰任何摄影活动。

Bessie 目前站在 xy 平面上 $(X,0)$ 处，她想要前往 $(0,Y)$（$1\le X,Y\le 10^6$）。不幸的是，$N$（$1 \leq N \leq 3 \cdot 10^5$）头其他奶牛决定在 $x$ 轴上摆姿势。更具体地说，奶牛 $i$ 将位于 $(x_i,0)$，她的摄影师位于 $(0,y_i)$（$1 \leq x_i,y_i \leq 10^6$），准备拍摄她的照片。他们将在时刻 $s_i$（$1 \leq s_i < T$）开始摆姿势，并且他们会保持姿势很长时间（他们必须拍出完美的照片）。这里，$1\le T\le N+1$。

Bessie 知道每头奶牛的摄影安排，她将选择最短欧几里得距离到达目的地，而不穿越任何摄影师与其对应的奶牛之间的视线（她的路径将由一条或多条线段组成）。

如果 Bessie 在时刻 $t$ 出发，她将避开所有在时刻 $s_i \le t$ 开始摆姿势的摄影师-奶牛对的视线，此外令她到达最终目的地的距离为 $d_t$。求从 $0$ 到 $T-1$ 的每一个整数 $t$ 的 $\lfloor d_t\rfloor$ 的值。
## 输入格式

输入的第一行包含 $N$ 和 $T$，为在 $x$ 轴上摆姿势的奶牛数量及 Bessie 可以出发的时刻数量。

第二行包含 $X$ 和 $Y$，分别表示 Bessie 起始点的 $x$ 坐标以及目的地的 $y$ 坐标。

以下 $N$ 行包含 $s_i$，$x_i$ 和 $y_i$。输入保证所有的 $x_i$ 各不相同且与 $X$ 不同，所有的 $y_i$ 各不相同且与 $Y$ 不同。所有 $s_i$ 将按升序给出，即 $s_i \leq s_{i+1}$。
## 输出格式

输出 $T$ 行，第 $t$ 行（从 0 开始索引）包含 $\lfloor d_t\rfloor$。

## 样例

### 样例输入 #1
```
4 5
6 7
1 7 5
2 4 4
3 1 6
4 2 9
```
### 样例输出 #1
```
9
9
9
10
12
```
### 样例输入 #2
```
2 3
10 7
1 2 10
1 9 1
```
### 样例输出 #2
```
12
16
16
```
### 样例输入 #3
```
5 6
8 9
1 3 5
1 4 1
3 10 7
4 9 2
5 6 6
```
### 样例输出 #3
```
12
12
12
12
14
14
```
## 提示

样例 2 解释：

对于 $t=0$ 答案为 $\lfloor \sqrt{149} \rfloor=12$。

对于 $t=1$ 答案为 $\lfloor 14+\sqrt 5\rfloor=16$。

样例 3 解释：

对于 $t=5$ 答案为 $\lfloor 1+\sqrt{9^2+7^2}+2\rfloor=14$。路径：$(8,0)\to (9,0)\to (0,7)\to (0,9)$。

- 测试点 $4\sim 6$：$N\le 100$。
- 测试点 $7\sim 9$：$N\le 3000$。
- 测试点 $10\sim 12$：$T\le 10$。
- 测试点 $13\sim 18$：没有额外限制。


---

---
title: "[USACO25FEB] Friendship Editing G"
layout: "post"
diff: 省选/NOI-
pid: P11844
tag: ['USACO', '2025', '状压 DP']
---
# [USACO25FEB] Friendship Editing G
## 题目描述

Farmer John 的 $N$ 头奶牛编号为 $1$ 到 $N$（$2\le N\le 16$）。奶牛之间的朋友关系可以建模为一个有 $M$（$0\le M\le N(N-1)/2$）条边的无向图。两头奶牛为朋友当且仅当图中她们之间存在一条边。

在一次操作中，你可以添加或删除图中的一条边。计算确保以下性质成立所需的最小操作次数：如果奶牛 $a$ 和 $b$ 是朋友，则对于每头其他奶牛 $c$，$a$ 和 $b$ 中至少之一与 $c$ 是朋友。
## 输入格式

输入的第一行包含 $N$ 和 $M$。

以下 $M$ 行，每行包含一对朋友 $a$ 和 $b$（$1\le a<b\le N$）。每对朋友出现至多一次。
## 输出格式

输出你需要增加或删除的边的数量。

## 样例

### 样例输入 #1
```
3 1
1 2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3 2
1 2
2 3
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
4 4
1 2
1 3
1 4
2 3
```
### 样例输出 #3
```
1
```
## 提示

样例 1 解释：

该网络不符合性质。我们可以添加边 $(2,3)$ 或 $(1,3)$，或删除边 $(1,2)$ 进行修复。

样例 2 解释：

不需要进行任何修改。

- 测试点 $4\sim 13$：对于每一个 $N\in [6, 15]$ 依次有一个测试点。
- 测试点 $14\sim 18$：$N=16$。


---

---
title: "[USACO25FEB] Min Max Subarrays P"
layout: "post"
diff: 省选/NOI-
pid: P11845
tag: ['二分', 'USACO', '2025', '分类讨论', '单调栈']
---
# [USACO25FEB] Min Max Subarrays P
## 题目描述

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。**

给定一个长为 $N$ 的整数数组 $a_1,a_2,\dots,a_N$（$2\le N \le 10^6$，$1\le a_i\le N$)。输出所有 $N(N+1)/2$ 个 $a$ 的连续子数组的以下子问题的答案之和。

给定一个非空整数列表，交替执行以下操作（从第一个操作开始）直到列表大小恰好为一。

1. 将列表内的两个相邻整数替换为它们的较小值。
1. 将列表内的两个相邻整数替换为它们的较大值。

求最终余下的整数的最大可能值。

例如，

$[4, 10, 3] \to [4, 3] \to [4]$

$[3, 4, 10] \to [3, 10] \to [10]$

在第一个数组中，$(10, 3)$ 被替换为 $\min(10, 3)=3$，随后 $(4, 3)$ 被替换为 $\max(4, 3)=4$。

## 输入格式

输入的第一行包含 $N$。

第二行包含 $a_1,a_2,\dots,a_N$。
## 输出格式

输出所有连续子数组的子问题的答案之和。

## 样例

### 样例输入 #1
```
2
2 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3
3 1 3
```
### 样例输出 #2
```
12
```
### 样例输入 #3
```
4
2 4 1 3
```
### 样例输出 #3
```
22
```
## 提示

样例 1 解释：

对于 $[2]$ 答案为 $2$，对于 $[1]$ 答案为 $1$，对于 $[2, 1]$ 答案为 $1$。

因此，我们的输出应当为 $2+1+1 = 4$。

样例 3 解释：

考虑子数组 $[2, 4, 1, 3]$。


1. 在 $(1, 3)$ 上应用第一次操作，我们的新数组是 $[2, 4, 1]$。
1. 在 $(4, 1)$ 上应用第二次操作，我们的新数组是 $[2, 4]$。
1. 在 $(2, 4)$ 上应用第三次操作，我们最终的数是 $2$。

可以证明 $2$ 是最终的数的最大可能值。

- 测试点 $4\sim 5$：$N\le 100$。
- 测试点 $6\sim 7$：$N\le 5000$。
- 测试点 $8\sim 9$：$\max(a)\le 10$。
- 测试点 $10\sim 13$：没有额外限制。


---

---
title: "[USACO25FEB] True or False Test P"
layout: "post"
diff: 省选/NOI-
pid: P11847
tag: ['动态规划 DP', 'USACO', '2025', '决策单调性']
---
# [USACO25FEB] True or False Test P
## 题目描述

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。本题的内存限制为 512MB，通常限制的 2 倍。**

Bessie 正在参加一场 $N$ 道判断题的考试（$1\le N\le 2\cdot 10^5$）。对于第 $i$ 道题目，如果她答对了将获得 $a_i$ 分，如果答错了将失去 $b_i$ 分，如果不回答则分数不变（$0<a_i,b_i\le 10^9$）。

因为 Bessie 是一头聪明的牛，她知道所有的答案，但她担心 Elsie（主考官）会在测试后追溯性地更改至多 $k$ 道题目，使得 Bessie 无法答对这些题目。

给定 $Q$（$1\le Q\le N+1$）个 $k$ 的候选值（$0\le k\le N$），求对于每一个 $k$，Bessie 在回答至少 $k$ 道题目的前提下可以保证的分数。
## 输入格式

输入的第一行包含 $N$ 和 $Q$。

以下 $N$ 行每行包含 $a_i$ 和 $b_i$。

以下 $Q$ 行每行包含一个 $k$ 的值。每个 $k$ 的值出现至多一次。
## 输出格式

对于每一个 $k$ 输出一行，包含对于该值的答案。

## 样例

### 样例输入 #1
```
2 3
3 1
4 2
2
1
0
```
### 样例输出 #1
```
-3
1
7
```
## 提示

样例 1 解释：

对于每一个 $k$ 的值，Bessie 的最优策略都是回答所有的题目。

- 测试点 $2\sim 4$：$N\le 100$。
- 测试点 $5\sim 7$：$Q\le 10$，$N\le 2\cdot 10^5$。
- 测试点 $7\sim 20$：没有额外限制。


---

---
title: "[USACO25OPEN] OohMoo Milk G"
layout: "post"
diff: 省选/NOI-
pid: P12030
tag: ['USACO', '2025']
---
# [USACO25OPEN] OohMoo Milk G
## 题目描述

农夫约翰正在生产他世界闻名的 OohMoo 牛奶以获取利润。他有 $N$ 个（$1 \leq N \leq 10^5$）瓶子需要装牛奶，每个瓶子初始含有 $m_i$（$0 \leq m_i \leq 10^9$）单位的牛奶。每天，他会选择 $A$ 个（$1 \leq A \leq N$）瓶子，每个被选中的瓶子增加 $1$ 单位牛奶。

不幸的是，他的竞争对手农夫 Nhoj 知道这个生产过程并计划破坏。每天在农夫约翰添加牛奶后，农夫 Nhoj 会偷偷从 $B$ 个（$0 \leq B < A$）不同的非空瓶子中各偷走 $1$ 单位牛奶。为了不被发现，农夫 Nhoj 确保 $B$ 严格小于 $A$。

经过 $D$ 天（$1 \leq D \leq 10^9$）后，农夫约翰将出售他的牛奶。如果一个瓶子含有 $M$ 单位牛奶，它将卖出 $M^2$ moonies 的价钱。

设 $P$ 为唯一确定的利润值，使得无论农夫 Nhoj 如何操作，农夫约翰都能保证至少获得 $P$ 利润；同时无论农夫约翰如何操作，农夫 Nhoj 都能确保农夫约翰最多获得 $P$ 利润。请输出 $P$ 对 $10^9+7$ 取模的结果。

## 输入格式

第一行包含 $N$ 和 $D$，分别表示瓶子数量和天数。

第二行包含 $A$ 和 $B$，表示农夫约翰每天添加的牛奶瓶数和农夫 Nhoj 每天偷取的瓶数。

第三行包含 $N$ 个整数 $m_i$，表示每个瓶子的初始牛奶量。

## 输出格式

输出 $P$ 对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
5 4
4 2
4 10 8 10 10
```
### 样例输出 #1
```
546
```
### 样例输入 #2
```
10 5
5 1
1 2 3 4 5 6 7 8 9 10
```
### 样例输出 #2
```
777

```
### 样例输入 #3
```
5 1000000000
3 1
0 1 2 3 4
```
### 样例输出 #3
```
10
```
## 提示

样例一解释：经过 $4$ 天后，可能的牛奶量为 $[4,11,11,12,12]$，总利润为 $4^2+11^2+11^2+12^2+12^2=546$。

- 测试点 $4\sim6$：$N,D \leq 1000$。
- 测试点 $7\sim10$：$D \leq 10^6$。
- 测试点 $11\sim20$：无额外限制。


---

---
title: "[USACO25OPEN] Lazy Sort P"
layout: "post"
diff: 省选/NOI-
pid: P12032
tag: ['USACO', '2025']
---
# [USACO25OPEN] Lazy Sort P
## 题目描述

Farmer John has $N$ cows ($2 \le N \le 5 \cdot 10^6$) and is attempting to get them to sort a non-negative integer array $A$ of length $N$ by relying on their laziness. He has a lot of heavy boxes so he lines the cows up one behind another, where cow $i+1$ is behind cow $i$, and gives $a_i$ boxes to cow $i$ ($0 \le a_i$).

Cows are inherently lazy so they always look to pass their work off to someone else. From cow 1 to $N-1$ in order, each cow looks to the cow behind them. If cow $i$ has strictly more boxes than cow $i+1$, cow $i$ thinks this is "unfair" and gives one of its boxes to cow $i+1$. This process repeats until every cow is satisfied.

Farmer John will then note the number of boxes $b_i$ that each cow $i$ is holding and create an array $B$ out of these values. If $B = \text{sorted}(A)$, then Farmer John will be happy. Unfortunately, Farmer John forgot all but $Q$ values ($2 \le Q \le \min(N, 100)$) in $A$. Luckily, those values include the number of boxes he was going to give to the first and last cow. Each value that FJ remembers is given in the form $c_i\; v_i$ representing that $a_{c_i} = v_i$ ($1 \le c_i \le N$, $1 \le v_i \le 10^9$). Determine the number of different ways the missing values can be filled in so that he will be happy mod $10^9 + 7$.
## 输入格式

The first line contains two space-separated integers $N$ and $Q$ representing the number of cows and queries respectively.

The next $Q$ lines contain two space separated integers $c_i\; v_i$ representing that cow $c_i$ initially holds $v_i$ boxes. It is guaranteed that $c_1 = 1$, $c_Q = N$, and $c_i < c_{i+1}$ (the order of the cows is strictly increasing).
## 输出格式

Print the number of different ways modulo $10^9 + 7$ that values $a_i$ can be assigned such that Farmer John will be happy after the cows perform the lazy sort. It is guaranteed that there will be at least one valid assignment.
## 样例

### 样例输入 #1
```
3 2
1 3
3 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 3
1 1
3 3
6 5
```
### 样例输出 #2
```
89
```
## 提示

### Sample 1 Explanation

In this example, FJ remembers the values at the ends of the array. The arrays $[3, 2, 2]$ and $[3, 3, 2]$ are the valid arrays that will make FJ happy at the end of the lazy sorting.

### SCORING:
- Inputs 3-4: $N,v_i\leq 100$
- Inputs 5-6: $N\leq 100$ and $v_i\leq 10^6$
- Inputs 7-9: $N\leq 2\times 10^5$ and $v_i\leq 10^6$
- Inputs 10-12: $N\leq 2\times 10^5$
- Inputs 13-15: No additional constraints.


---

---
title: "[USACO4.4] 追查坏牛奶 Pollutant Control"
layout: "post"
diff: 省选/NOI-
pid: P1344
tag: ['图论', 'USACO']
---
# [USACO4.4] 追查坏牛奶 Pollutant Control
## 题目描述

你第一天接手三鹿牛奶公司就发生了一件倒霉的事情：公司不小心发送了一批有三聚氰胺的牛奶。

很不幸，你发现这件事的时候，有三聚氰胺的牛奶已经进入了送货网。这个送货网很大，而且关系复杂。你知道这批牛奶要发给哪个零售商，但是要把这批牛奶送到他手中有许多种途径。

送货网由一些仓库和运输卡车组成，每辆卡车都在各自固定的两个仓库之间单向运输牛奶。在追查这些有三聚氰胺的牛奶的时候，有必要保证它不被送到零售商手里，所以必须使某些运输卡车停止运输，但是停止每辆卡车都会有一定的经济损失。

你的任务是，在保证坏牛奶不送到零售商的前提下，制定出停止卡车运输的方案，使损失最小。

## 输入格式

第 $1$ 行两个整数 $N$、$M$，$N$ 表示仓库的数目，$M$ 表示运输卡车的数量。仓库 $1$ 代表发货工厂，仓库 $N$ 代表有三聚氰胺的牛奶要发往的零售商。

第 $2\sim M+1$ 行，每行 $3$ 个整数 $S_i$、$E_i$ 和 $C_i$。其中 $S_i$、$E_i$ 分别表示这辆卡车的出发仓库和目的仓库。$C_i$ 表示让这辆卡车停止运输的损失。

## 输出格式

两个整数 $C$ 和 $T$，$C$ 表示最小的损失，$T$ 表示在损失最小的前提下，最少要停止的卡车数。
## 样例

### 样例输入 #1
```
4 5

1 3 100

3 2 50

2 4 60

1 2 40

2 3 80


```
### 样例输出 #1
```
60 1


```
## 提示

对于 $100 \%$ 的数据，满足 $2 \le N \le 32$，$0 \le M \le 10^3$，$1 \le S_i \le N$，$1 \le E_i \le N$，$0 \le C_i \le 2 \times 10^6$。

题目翻译来自 NOCOW。

USACO Training Section 4.4


---

---
title: "【模板】旋转卡壳 | [USACO03FALL] Beauty Contest G"
layout: "post"
diff: 省选/NOI-
pid: P1452
tag: ['计算几何', '2003', 'USACO', '枚举', '凸包', '旋转卡壳']
---
# 【模板】旋转卡壳 | [USACO03FALL] Beauty Contest G
## 题目描述

给定平面上 $n$ 个点，求凸包直径。

## 输入格式

第一行一个正整数 $n$。   
接下来 $n$ 行，每行两个整数 $x,y$，表示一个点的坐标。保证所有点的坐标两两不同。
## 输出格式

输出一行一个整数，表示答案的平方。
## 样例

### 样例输入 #1
```
4
0 0
0 1
1 1
1 0

```
### 样例输出 #1
```
2
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$2\le n \le 50000$，$|x|,|y| \le 10^4$。

---

$\text{upd 2022.7.22}$：新增加四组 Hack 数据。


---

---
title: "[USACO12JAN] Mountain Climbing S"
layout: "post"
diff: 省选/NOI-
pid: P1561
tag: ['贪心', '2012', 'USACO']
---
# [USACO12JAN] Mountain Climbing S
## 题目描述

Farmer John has discovered that his cows produce higher quality milk when they are subject to strenuous exercise.  He therefore decides to send his N cows (1 <= N <= 25,000) to climb up and then back down a nearby mountain!

Cow i takes U(i) time to climb up the mountain and then D(i) time to climb down the mountain.  Being domesticated cows, each cow needs the help of a farmer for each leg of the climb, but due to the poor economy, there are only two farmers available, Farmer John and his cousin Farmer Don.  FJ plans to guide cows for the upward climb, and FD will then guide the cows for the downward climb.  Since every cow needs a guide, and there is only one farmer for each part of the voyage, at most one cow may be climbing upward at any point in time (assisted by FJ), and at most one cow may be climbing down at any point in time (assisted by FD).  A group of cows may temporarily accumulate at the top of the mountain if they climb up and then need to wait for FD's assistance before climbing down.  Cows may climb down in a different order than they climbed up.

Please determine the least possible amount of time for all N cows to make the entire journey.

## 输入格式

第一行，一个整数 $N$。

第 $2$ 到第 $N+1$ 行，每行两个用空格隔开的整数 $U(i)$ 和 $D(i)$。

$(1 \le U(i),D(i) \le 50,000)$。
## 输出格式

一行一个整数，表示所有 $N$ 头牛完成旅程的最短时间。
## 样例

### 样例输入 #1
```
3
6 4
8 1
2 3
```
### 样例输出 #1
```
17
```
## 题目翻译

农场主约翰发现他的奶牛剧烈运动后产奶的质量更高，所以他决定让 $N$ 头 $(1 \le N \le 25,000)$ 奶牛去附近爬山再返回来。

第 $i$ 头奶牛用时 $U(i)$ 爬上山，用时 $D(i)$ 下山。作为家畜，奶牛们每段路都要有农夫的帮助，可是由于经济疲软，农场里只有两个农夫 John 和 Don。John 计划引导奶牛爬山，Don 引导奶牛下山。虽然每个奶牛都需要向导，但每段旅途只有一名农夫。所有任何时刻只有一头奶牛爬山也只能有一头奶牛下山，奶牛爬上山后，可以暂时停留在山顶上等待 Don 的帮助。奶牛上山的顺序和下山的顺序不一定要相同。

请计算出所有 $N$ 头牛完成旅程的最短时间。


---

---
title: "[USACO07FEB] Lilypad Pond G"
layout: "post"
diff: 省选/NOI-
pid: P1606
tag: ['图论', '2007', 'USACO', '广度优先搜索 BFS', '最短路']
---
# [USACO07FEB] Lilypad Pond G
## 题目描述

FJ has installed a beautiful pond for his cows' aesthetic enjoyment and exercise.

The rectangular pond has been partitioned into square cells of M rows and N columns (1 ≤ M ≤ 30; 1 ≤ N ≤ 30). Some of the cells have astonishingly sturdy lilypads; others have rocks; the remainder are just beautiful, cool, blue water.

Bessie is practicing her ballet moves by jumping from one lilypad to another and is currently located at one of the lilypads. She wants to travel to another lilypad in the pond by jumping from one lilypad to another.

Surprising only to the uninitiated, Bessie's jumps between lilypads always appear as a chess-knight's move: one move in one direction and then two more in the orthogonal direction (or perhaps two in one direction and then one in the orthogonal direction).

Farmer John is observing Bessie's ballet drill and realizes that sometimes she might not be able to jump to her destination lilypad because intermediary lilypads are missing.

Ever thrifty, he wants to place additional lilypads so she can complete her quest (perhaps quickly, perhaps by using a large number of intermediate lilypads). Of course, lilypads cannot be placed where rocks already intrude on a cell.

Help Farmer John determine the minimum number of additional lilypads he has to place, and in how many ways he can place that minimum number.

## 输入格式

第一行两个用空格分开的整数 $M$ 和 $N$。

第二行到 $M+1$ 行，第 $i+1$ 行有 $N$ 个用空格分开的整数，描述了池塘第 $i$ 行的状态：

- $0$ 为水，$1$ 为莲花，$2$ 为岩石，$3$ 为贝西所在的起点，$4$ 为贝西想去的终点。
## 输出格式

第一行一个整数，需要增加的最少莲花数；如果无解，输出 $-1$。

第二行输出放置这些莲花的方案数量，保证这个数字可用一个 $64$ 位的有符号整数，表示。

特别地，如果第一行是 $-1$，不要输出第二行。
## 样例

### 样例输入 #1
```
4 5
1 0 0 0 0
3 0 0 0 0
0 0 2 0 0
0 0 0 4 0

```
### 样例输出 #1
```
2
3

```
## 提示

### 样例解释

池塘分成四行五列，贝西的起点在第二行第一列，想去的终点在第四行第四列，池塘里一共有三朵莲花和一块石头。

最少需要两朵莲花，有三种方式可以放置，

如下 $\verb!X!$ 所示：

$$\begin{bmatrix}
\verb!10000! \\
\verb!30X00! \\
\verb!00200! \\
\verb!0X040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!30000! \\
\verb!0X200! \\
\verb!00040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!3000X! \\
\verb!00200! \\
\verb!00040! \\
\end{bmatrix}
$$
## 题目翻译

为了让奶牛们娱乐和锻炼，农夫约翰建造了一个美丽的池塘。这个长方形的池子被分成了 $M$ 行 $N$ 列个方格（$1 \le M,N \le 30$）。一些格子是坚固得令人惊讶的莲花，还有一些格子是岩石，其余的只是美丽、纯净、湛蓝的水。

贝西正在练习芭蕾舞，她站在一朵莲花上，想跳到另一朵莲花上去，她只能从一朵莲花跳到另一朵莲花上，既不能跳到水里，也不能跳到岩石上。

贝西的舞步很像象棋中的马步：每次总是先横向移动一格，再纵向移动两格，或先纵向移动两格，再横向移动一格。最多时，贝西会有八个移动方向可供选择。

约翰一直在观看贝西的芭蕾练习，发现她有时候不能跳到终点，因为中间缺了一些荷叶。于是他想要添加几朵莲花来帮助贝西完成任务。一贯节俭的约翰只想添加最少数量的莲花。当然，莲花不能放在石头上。

请帮助约翰确定必须要添加的莲花的最少数量，以及有多少种放置这些莲花的方法。


---

---
title: "[USACO05FEB] Secret Milking Machine G"
layout: "post"
diff: 省选/NOI-
pid: P1674
tag: ['2005', '二分', 'USACO', '网络流']
---
# [USACO05FEB] Secret Milking Machine G
## 题目描述

约翰正在制造一台新型的挤奶机，但他不希望别人知道。他希望尽可能久地隐藏这个秘密。他把挤奶机藏在他的农场里，使它不被发现。在挤奶机制造的过程中，他需要去挤奶机所在的地方 $T$ 次。他的农场里有秘密的地道，但约翰只在返回的时候用它。农场被划分成 $N$ 块区域，用 $1$ 到 $200$ 标号。这些区域被 $P$ 条道路连接，每条路有一个小于 $10^6$ 的长度 $L$。两块区域之间可能有多条道路连接。为了减少被发现的可能，约翰不会两次经过农场上的任何一条道路。当然了，他希望走最短的路。请帮助约翰寻找这 $T$ 次从仓库走到挤奶机所在地的路线。仓库是区域 $1$，挤奶机所在地是区域 $N$。我们现在要求的是约翰经过的这些道路中最长的路的长度最小是多少，当然他不能重复走某一条路。请注意，我们要求的不是最短的总路程长度，而是所经过的直接连接两个区域的道路中最长的道路的最小长度。数据保证约翰可以找到 $T$ 条没有重复的从仓库到挤奶机所在区域的路。
## 输入格式

第 $1$ 行是 $3$ 个整数 $N$、$P$ 和 $T$，用空格隔开。

第 $2$ 到 $P+1$ 行，每行包括 $3$ 个整数，$A_i$，$B_i$，$L_i$。表示区域 $A_i$、$B_i$ 之间有一条长度为 $L_i$ 的道路。
## 输出格式

输出只有一行，包含一个整数，即约翰经过的这些道路中最长的路的最小长度。
## 样例

### 样例输入 #1
```
7 9 2
1 2 2
2 3 5
3 7 5
1 4 1
4 3 1
4 5 7
5 7 1
1 6 3
6 7 3
```
### 样例输出 #1
```
5
```
## 提示

选择 $1-2-3-7$ 和 $1-6-7$ 两条路线．这些路线中最长路的最小长度是 $5$。

对于 $100\%$ 的数据满足：$2\le N\le 200$，$1\le P\le 4\times 10^4$，$1\le T\le 200$，每条路的长度 $\le 10^6$。


---

---
title: "[USACO16DEC] Lots of Triangles P"
layout: "post"
diff: 省选/NOI-
pid: P1715
tag: ['计算几何', '2016', 'USACO', '容斥原理', '分类讨论']
---
# [USACO16DEC] Lots of Triangles P
## 题目描述

Farmer John is thinking of selling some of his land to earn a bit of extra income. His property contains $N$ trees ($3 \leq N \leq 300$), each described by a point in the 2D plane, no three of which are collinear. FJ is thinking about selling triangular lots of land defined by having trees at their vertices; there are of course $L = \binom{N}{3}$ such lots he can consider, based on all possible triples of trees on his property.

A triangular lot has value $v$ if it contains exactly $v$ trees in its interior (the trees on the corners do not count, and note that there are no trees on the boundaries since no three trees are collinear). For every $v = 0 \ldots N-3$, please help FJ determine how many of his $L$ potential lots have value $v$.
## 输入格式

The first line of input contains $N$.

The following $N$ lines contain the $x$ and $y$ coordinates of a single tree; these are both integers in the range $0 \ldots 1,000,000$.
## 输出格式

Output $N-2$ lines, where output line $i$ contains a count of the number of lots having value $i-1$.
## 样例

### 样例输入 #1
```
7
3 6
17 15
13 15
6 12
9 1
2 7
10 19
```
### 样例输出 #1
```
28
6
1
0
0
```
## 题目翻译

### 题目描述

Farmer John 正在考虑出售他的一部分土地以赚取一些额外收入。他的财产包含 $N$ 棵树（$3 \leq N \leq 300$），每棵树由二维平面中的一个点描述，且任意三棵树不共线。FJ 正在考虑出售由三棵树作为顶点定义的三角形地块；显然，他可以考虑的此类地块数量为 $L = \binom{N}{3}$，基于他财产中所有可能的三棵树组合。

一个三角形地块的价值为 $v$，如果它的内部恰好包含 $v$ 棵树（顶点上的树不计入，且由于没有三棵树共线，边界上也没有树）。对于每个 $v = 0 \ldots N-3$，请帮助 FJ 确定他的 $L$ 个潜在地块中有多少个地块的价值为 $v$。

### 输入格式

输入的第一行包含 $N$。

接下来的 $N$ 行每行包含一棵树的 $x$ 和 $y$ 坐标；这些坐标都是 $0 \ldots 1,000,000$ 范围内的整数。

### 输出格式

输出 $N-2$ 行，其中第 $i$ 行输出价值为 $i-1$ 的地块数量。


---

---
title: "[USACO12OPEN] Bookshelf G"
layout: "post"
diff: 省选/NOI-
pid: P1848
tag: ['2012', '线段树', '二分', 'USACO', '平衡树']
---
# [USACO12OPEN] Bookshelf G
## 题目描述

When Farmer John isn't milking cows, stacking haybales, lining up his cows, or building fences, he enjoys sitting down with a good book.  Over the years, he has collected N books (1 <= N <= 100,000), and he wants to build a new set of bookshelves to hold them all.

Each book i has a width W(i) and height H(i).  The books need to be added to a set of shelves in order; for example, the first shelf should contain books 1...k for some k, the second shelf should start with book k+1, and so on.  Each shelf can have a total width of at most L (1 <= L <= 1,000,000,000).  The height of a shelf is equal to the height of the tallest book on that shelf, and the height of the entire set of bookshelves is the sum of the heights of all the individual shelves, since they are all stacked vertically.

Please help FJ compute the minimum possible height for the entire set of bookshelves.
## 输入格式

第一行：两个数 $N$ 和 $L$ 。

接下来 $N$ 行每行两个数 $H_i$ 和 $W_i$ 。
## 输出格式

一个数，书架高度的最小值。
## 样例

### 样例输入 #1
```
5 10
5 7
9 2
8 5
13 2
3 8
```
### 样例输出 #1
```
21
```
## 题目翻译

当农夫约翰闲的没事干的时候，他喜欢坐下来看书。多年过去，他已经收集了 $N$ 本书 $(1 \le N \le 100,000)$ ， 他想造一个新的书架来装所有书。

每本书 $i$ 都有宽度 $W_i$ 和高度 $H_i$ 。书需要按顺序添加到一组书架上；比如说，第一层架子应该包含书籍 $1  ... k$ ，第二层架子应该以第 $k + 1$ 本书开始，以下如此。每层架子的总宽度最大为 $L(1 \le L \le 1,000,000,000)$ 。每层的高度等于该层上最高的书的高度，并且整个书架的高度是所有层的高度的总和，因为它们都垂直堆叠。

请帮助农夫约翰计算整个书架的最小可能高度。

有 $N(1 \le N \le 100,000)$ 本书，每本书有一个宽度 $W_i$ ，高度 $H_i$ ，$(1 \le H_i \le 1,000,000; 1 \le W_i \le L)$ 。

现在有足够多的书架，书架宽度最多是 $L (1 \le L \le 1,000,000,000)$ ，把书按顺序 $($先放 $1$ ，再放 $2.....)$ 放入书架。某个书架的高度是该书架中所放的最高的书的高度。

将所有书放入书架后，求所有书架的高度和的最小值。


---

---
title: "[USACO16DEC] Robotic Cow Herd P"
layout: "post"
diff: 省选/NOI-
pid: P2541
tag: ['2016', 'USACO', 'Ad-hoc']
---
# [USACO16DEC] Robotic Cow Herd P
## 题目描述

Bessie is hoping to fool Farmer John by building a herd of $K$ realistic robotic cows ($1 \leq K \leq 100,000$).

It turns out that building a robotic cow is somewhat complicated. There are $N$ ($1 \leq n \leq 100,000$) individual locations on the robot into which microcontrollers must be connected (so a single microcontroller must be connected at each location). For each of these locations, Bessie can select from a number of different models of microcontroller, each varying in cost.

For the herd of robotic cows to look convincing to Farmer John, no two robots should behave identically. Therefore, no two robots should have exactly the same set of microcontrollers. For any pair of robots, there should be at least one location at which the two robots use a different microcontroller model. It is guaranteed that there will always be enough different microcontroller models to satisfy this constraint.

Bessie wants to make her robotic herd as cheaply as possible. Help her determine the minimum possible cost to do this!
## 输入格式

The first line of input contains $N$ and $K$ separated by a space.

The following $N$ lines contain a description of the different microcontroller models available for each location. The $i$th such line starts with $M_i$ ($1 \leq M_i \leq 10$), giving the number of models available for location $i$. This is followed by $M_i$ space separated integers $P_{i,j}$ giving the costs of these different models ($1 \le P_{i,j} \le 100,000,000$).
## 输出格式

Output a single line, giving the minimum cost to construct $K$ robots.
## 样例

### 样例输入 #1
```
3 10
4 1 5 3 10
3 2 3 3
5 1 3 4 6 6
```
### 样例输出 #1
```
61
```
## 题目翻译

### 题目描述

Bessie 希望通过建造 $K$ 头逼真的机器人奶牛（$1 \leq K \leq 100,000$）来愚弄 Farmer John。

事实证明，建造一头机器人奶牛有些复杂。机器人上有 $N$ 个（$1 \leq N \leq 100,000$）独立的位置需要连接微控制器（因此每个位置必须连接一个微控制器）。对于每个位置，Bessie 可以从多个不同的微控制器模型中选择，每个模型的成本各不相同。

为了让机器人牛群对 Farmer John 看起来逼真，任何两头机器人的行为都不应完全相同。因此，任何两头机器人都不应使用完全相同的微控制器集合。对于任意一对机器人，至少应有一个位置上的微控制器模型不同。保证始终有足够的不同微控制器模型来满足此约束。

Bessie 希望以尽可能低的成本建造她的机器人牛群。请帮助她确定实现这一目标的最小可能成本！

### 输入格式

输入的第一行包含用空格分隔的 $N$ 和 $K$。

接下来的 $N$ 行描述了每个位置可用的不同微控制器模型。第 $i$ 行以 $M_i$（$1 \leq M_i \leq 10$）开头，表示位置 $i$ 可用的模型数量。随后是 $M_i$ 个用空格分隔的整数 $P_{i,j}$，表示这些不同模型的成本（$1 \le P_{i,j} \le 100,000,000$）。

### 输出格式

输出一行，表示建造 $K$ 头机器人的最小成本。


---

---
title: "[USACO5.5] 贰五语言Two Five"
layout: "post"
diff: 省选/NOI-
pid: P2750
tag: ['动态规划 DP', '2001', 'USACO', 'IOI', '深度优先搜索 DFS']
---
# [USACO5.5] 贰五语言Two Five
## 题目描述

有一种奇怪的语言叫做“贰五语言”。它的每个单词都由A～Y这25个字母各一个组成。但是，并不是任何一种排列都是一个合法的贰五语言单词。贰五语言的单词必须满足这样一个条件：把它的25个字母排成一个5\*5的矩阵，它的每一行和每一列都必须是递增的。比如单词ACEPTBDHQUFJMRWGKNSXILOVY，它排成的矩阵如下所示：

A C E P T

B D H Q U

F J M R W

G K N S X

I L O V Y

因为它的每行每列都是递增的，所以它是一个合法的单词。而单词YXWVUTSRQPONMLKJIHGFEDCBA则显然不合法。 由于单词太长存储不便，需要给每一个单词编一个码。编码方法如下：从左到右，再从上到下，可以由一个矩阵的得到一个单词，再把单词按照字典顺序排序。比如，单词ABCDEFGHIJKLMNOPQRSTUVWXY的编码为1，而单词ABCDEFGHIJKLMNOPQRSUTVWXY的编码为2。

现在，你需要编一个程序，完成单词与编码间的转换。

## 输入格式

第一行为一个字母N或W。N表示把编码转换为单词，W表示把单词转换为编码。

若第一行为N，则第二行为一个整数，表示单词的编码。若第一行为W，则第二行为一个合法的单词。

## 输出格式

每行一个整数或单词。

## 样例

### 样例输入 #1
```
N
2
```
### 样例输出 #1
```
ABCDEFGHIJKLMNOPQRSUTVWXY
```
### 样例输入 #2
```
W 
ABCDEFGHIJKLMNOPQRSUTVWXY
```
### 样例输出 #2
```
2
```
## 提示

题目翻译来自NOCOW。

USACO Training Section 5.5



---

---
title: "[USACO06FEB] Steady Cow Assignment G"
layout: "post"
diff: 省选/NOI-
pid: P2857
tag: ['贪心', '2006', '二分', 'USACO', '网络流', '枚举', '双指针 two-pointer']
---
# [USACO06FEB] Steady Cow Assignment G
## 题目描述

Farmer John's N (1 <= N <= 1000) cows each reside in one of B (1 <= B <= 20) barns which, of course, have limited capacity. Some cows really like their current barn, and some are not so happy.

FJ would like to rearrange the cows such that the cows are as equally happy as possible, even if that means all the cows hate their assigned barn.


Each cow gives FJ the order in which she prefers the barns.  A cow's happiness with a particular assignment is her ranking of her barn. Your job is to find an assignment of cows to barns such that no barn's capacity is exceeded and the size of the range (i.e., one more than the positive difference between the the highest-ranked barn chosen and that lowest-ranked barn chosen) of barn rankings the cows give their assigned barns is as small as possible.

## 输入格式

Line 1: Two space-separated integers, N and B


Lines 2..N+1: Each line contains B space-separated integers which are exactly 1..B sorted into some order. The first integer on line i+1 is the number of the cow i's top-choice barn, the second integer on that line is the number of the i'th cow's second-choice barn, and so on.


Line N+2: B space-separated integers, respectively the capacity of the first barn, then the capacity of the second, and so on. The sum of these numbers is guaranteed to be at least N.

## 输出格式

Line 1: One integer, the size of the minumum range of barn rankings the cows give their assigned barns, including the endpoints.

## 样例

### 样例输入 #1
```
6 4
1 2 3 4
2 3 1 4
4 2 3 1
3 1 2 4
1 3 4 2
1 4 2 3
2 1 3 2
```
### 样例输出 #1
```
2
```
## 提示

Explanation of the sample:




Each cow can be assigned to her first or second choice: barn 1 gets cows 1 and 5, barn 2 gets cow 2, barn 3 gets cow 4, and barn 4 gets cows 3 and 6.

## 题目翻译

有 $N$ 头牛，$B$ 个牛棚。告诉你每头牛心里牛棚的座次，即哪个牛棚他最喜欢，哪个第 $2$ 喜欢，哪个第 $3$ 喜欢，等等。但牛棚容量一定，所以每头牛分配到的牛棚在该牛心中的座次有高有低。现在求一种最公平的方法分配牛到牛棚，使所有牛中，所居牛棚的座次最高与最低的跨度最小。


---

---
title: "[USACO07DEC] Sightseeing Cows G"
layout: "post"
diff: 省选/NOI-
pid: P2868
tag: ['搜索', '2007', '二分', 'USACO', '最短路', '分数规划']
---
# [USACO07DEC] Sightseeing Cows G
## 题目描述

Farmer John has decided to reward his cows for their hard work by taking them on a tour of the big city! The cows must decide how best to spend their free time.

Fortunately, they have a detailed city map showing the L (2 ≤ L ≤ 1000) major landmarks (conveniently numbered 1.. L) and the P (2 ≤ P ≤ 5000) unidirectional cow paths that join them. Farmer John will drive the cows to a starting landmark of their choice, from which they will walk along the cow paths to a series of other landmarks, ending back at their starting landmark where Farmer John will pick them up and take them back to the farm. Because space in the city is at a premium, the cow paths are very narrow and so travel along each cow path is only allowed in one fixed direction.

While the cows may spend as much time as they like in the city, they do tend to get bored easily. Visiting each new landmark is fun, but walking between them takes time. The cows know the exact fun values Fi (1 ≤ Fi ≤ 1000) for each landmark i.

The cows also know about the cowpaths. Cowpath i connects landmark L1i to L2i (in the direction L1i -> L2i ) and requires time Ti (1 ≤ Ti ≤ 1000) to traverse.

In order to have the best possible day off, the cows want to maximize the average fun value per unit time of their trip. Of course, the landmarks are only fun the first time they are visited; the cows may pass through the landmark more than once, but they do not perceive its fun value again. Furthermore, Farmer John is making the cows visit at least two landmarks, so that they get some exercise during their day off.

Help the cows find the maximum fun value per unit time that they can achieve.

## 输入格式

\* Line 1: Two space-separated integers: L and P

\* Lines 2..L+1: Line i+1 contains a single one integer: Fi

\* Lines L+2..L+P+1: Line L+i+1 describes cow path i with three space-separated integers: L1i , L2i , and Ti

## 输出格式

\* Line 1: A single number given to two decimal places (do not perform explicit rounding), the maximum possible average fun per unit time, or 0 if the cows cannot plan any trip at all in accordance with the above rules.

## 样例

### 样例输入 #1
```
5 7
30
10
10
5
10
1 2 3
2 3 2
3 4 5
3 5 2
4 5 5
5 1 3
5 2 2
```
### 样例输出 #1
```
6.00
```
## 题目翻译

给你一张 $n$ 点 $m$ 边的有向图，第 $i$ 个点点权为 $F_i$，第 $i$ 条边边权为 $T_i$。

找一个环，设环上的点组成的集合为 $S$，环的边组成的集合为 $E$，最大化 $\dfrac{\sum_{u\in S}F_u}{\sum_{e\in E}T_e}$。

数据范围：$1\leq n,F_i,T_i\leq 10^3$，$1\leq m\leq 5\times10^3$。


---

---
title: "[USACO07JAN] Cow School G"
layout: "post"
diff: 省选/NOI-
pid: P2877
tag: ['贪心', '2007', 'USACO']
---
# [USACO07JAN] Cow School G
## 题目描述

Bessy is going to school and doing well. She has taken N (1 ≤ N ≤ 5000 -- except one case where 1 ≤ N ≤ 50,000) tests and recorded the scores (Ti points out of Pi points for test i; 0 ≤ Ti ≤ Pi < 40,000; 0 < Pi) as this task's input.

Her teacher will drop the D tests with the lowest percentage (Ti⁄Pi) before calculating Bessie's final grade (which is the sum of the remaining test score points over the sum of the remaining total test points). Bessy is good at math and quickly realizes that this does not benefit her as much as it might.

To prove her point, Bessy wants to find all values of D for which she could have ended up with a higher grade by choosing to drop different tests than the teacher would have. Help her by finding and printing all values of D for which this is possible.

Bessy has noted that, amazingly, she has never scored the same percentage on two different tests.

一个人参加了 $N$ 场考试，第 $i$ 场满分为 $P_i$，其得分为 $T_i$。现在要删去其中 $D$ 次考试的成绩，用剩下的总得分除以剩下的满分之和，作为其最终成绩。问对于哪些 $D$ 而言，删除得分比（即 $\dfrac{T_i}{P_i}$）最小的 $D$ 场得到的最终成绩不是最优的（用其他方法可以得到更高的最终成绩）。
## 输入格式

Line 1: A single integer, N


Lines 2..N+1: Line i+1 contains two space-separated integers: Ti and Pi

## 输出格式

Line 1: A single integer K (0 ≤ K ≤ N) that is the number of values of D for which Bessy could have ended up with a higher grade by dropping a different set of D tests than the teacher.


Lines 2..K+1: The values of D for which this is true, in ascending numerical order.

## 样例

### 样例输入 #1
```
5
1 2
5 9
3 8
4 10
1 3
```
### 样例输出 #1
```
2
1
2
```


---

---
title: "[USACO07OPEN] Dining G"
layout: "post"
diff: 省选/NOI-
pid: P2891
tag: ['动态规划 DP', '递推', '2007', 'USACO', '网络流']
---
# [USACO07OPEN] Dining G
## 题目描述

Cows are such finicky eaters. Each cow has a preference for certain foods and drinks, and she will consume no others.

Farmer John has cooked fabulous meals for his cows, but he forgot to check his menu against their preferences. Although he might not be able to stuff everybody, he wants to give a complete meal of both food and drink to as many cows as possible.

Farmer John has cooked F (1 ≤ F ≤ 100) types of foods and prepared D (1 ≤ D ≤ 100) types of drinks. Each of his N (1 ≤ N ≤ 100) cows has decided whether she is willing to eat a particular food or drink a particular drink. Farmer John must assign a food type and a drink type to each cow to maximize the number of cows who get both.

Each dish or drink can only be consumed by one cow (i.e., once food type 2 is assigned to a cow, no other cow can be assigned food type 2).

## 输入格式

Line 1: Three space-separated integers: N, F, and D


Lines 2..N+1: Each line i starts with a two integers Fi and Di, the number of dishes that cow i likes and the number of drinks that cow i likes. The next Fi integers  denote the dishes that cow i will eat, and the Di integers following that denote the drinks that cow i will drink.

## 输出格式

Line 1: A single integer that is the maximum number of cows that can be fed both food and drink that conform to their wishes

## 样例

### 样例输入 #1
```
4 3 3
2 2 1 2 3 1
2 2 2 3 1 2
2 2 1 3 1 2
2 1 1 3 3
```
### 样例输出 #1
```
3
```
## 提示

One way to satisfy three cows is:


Cow 1: no meal


Cow 2: Food #2, Drink #2


Cow 3: Food #1, Drink #1


Cow 4: Food #3, Drink #3


The pigeon-hole principle tells us we can do no better since there are only three kinds of food or drink. Other test data sets are more challenging, of course.

## 题目翻译

有 $F$ 种食物和 $D$ 种饮料，每种食物或饮料只能供一头牛享用，且每头牛只享用一种食物和一种饮料。现在有 $n$ 头牛，每头牛都有自己喜欢的食物种类列表和饮料种类列表，问最多能使几头牛同时享用到自己喜欢的食物和饮料。

对于全部数据，$1 \le f \le 100$，$1 \le d \le 100$，$1 \le n \le 100$。


---

---
title: "[USACO08MAR] Land Acquisition G"
layout: "post"
diff: 省选/NOI-
pid: P2900
tag: ['动态规划 DP', '2008', 'USACO', '斜率优化']
---
# [USACO08MAR] Land Acquisition G
## 题目描述

Farmer John 准备扩大他的农场，眼前他正在考虑购买 $N$ 块长方形的土地。

如果 FJ 单买一块土地，价格就是土地的面积。但他可以选择并购一组土地，并购的价格为这些土地中最大的长乘以最大的宽。比如 FJ 并购一块 $3 \times 5$ 和一块 $5 \times 3$ 的土地，他只需要支付 $5 \times 5=25$ 元， 比单买合算。

FJ 希望买下所有的土地。他发现，将这些土地分成不同的小组来并购可以节省经费。 给定每份土地的尺寸，请你帮助他计算购买所有土地所需的最小费用。
## 输入格式

第一行一个整数 $N$（$1 \leq N \leq 5 \times 10^4$）。

接下来 $N$ 行，每行两个整数 $w_i$ 和 $l_i$，代表第 $i$ 块土地的长和宽。保证土地的长和宽不超过 $10^6$。
## 输出格式

输出买下所有土地的最小费用。
## 样例

### 样例输入 #1
```
4 
100 1 
15 15 
20 5 
1 100 

```
### 样例输出 #1
```
500 

```
## 提示

将所有土地分为三组：

- 第一块土地为第一组，花费 $100 \times 1=100$；
- 第二，三块土地为第二组，花费 $20 \times 15=300$；
- 第四块土地为第三组，花费 $1 \times 100=100$；

总花费为 $500$，可以证明不存在更优的方案。


---

---
title: "[USACO08OPEN] Cow Neighborhoods G"
layout: "post"
diff: 省选/NOI-
pid: P2906
tag: ['2008', 'USACO', '并查集', '平衡树', '生成树']
---
# [USACO08OPEN] Cow Neighborhoods G
## 题目描述

了解奶牛的人都知道奶牛是如何组成「奶牛社区」的。他们观察了 Farmer John 的 $N$ 头奶牛（编号为 $1 \sim N$），它们在 $X$ 和 $Y$ 坐标范围为 $1$ 的牧场上放牧，每头奶牛都在自己唯一的整数直线坐标上。

如果满足以下两个标准中的至少一个，则两头奶牛是邻居：

1. 两只奶牛的曼哈顿距离不超过 $C$，即 $|X_i - x_i| + |Y_i - y_i| \leq C$；
2. 两只奶牛有共同的邻居。即存在一只奶牛 $k$，使 $i$ 与 $k$，$j$ 与 $k$ 均同属一个群。

给定奶牛的位置和距离 $C$，确定「奶牛社区」的数量和最大的「奶牛社区」中的奶牛数量。

例如，考虑下面的牧场。 当 $C = 4$ 时，这个牧场有四个社区：左边的一个大社区，两个大小为 1 的社区，右边有一个巨大的社区，里面有 $60$ 头不同的奶牛。

```text
.....................................*.................
....*...*..*.......................***.................
......*...........................****.................
..*....*..*.......................*...*.******.*.*.....
........................*.............***...***...*....
*..*..*...*..........................*..*...*..*...*...
.....................................*..*...*..*.......
.....................................*..*...*..*.......
...*................*..................................
.*..*............................*.*.*.*.*.*.*.*.*.*.*.
.*.....*..........................*.*.*.*.*.*.*.*.*.*.*
....*..................................................
```
## 输入格式

第 $1$ 行包含两个用空格分隔的整数 $N, C$。

第 $2$ 到第 $N + 1$ 行每行包含两个用空格分隔的整数 $X_i, Y_i$，表示一头牛的坐标。

## 输出格式


共一行，为两个用空格分隔的整数，为「奶牛社区」的数量和最大的「奶牛社区」内牛的数量。
## 样例

### 样例输入 #1
```
4 2 
1 1 
3 3 
2 2 
10 10 

```
### 样例输出 #1
```
2 3 

```
## 提示

### 样例说明 #1

样例中有 $2$ 个社区，一个由前三头奶牛组成，另一个是最后一头奶牛。因此，最大的社区大小为 $3$。

### 数据范围与约定

对于 $100\%$ 的数据，$1 \leq N \leq 10^5$，$1 \leq C \leq 10^9$，$1 \leq X_i, Y_i \leq 10^9$，$X_i, Y_i$ 均为整数。


---

---
title: "[USACO08NOV] Toys G"
layout: "post"
diff: 省选/NOI-
pid: P2917
tag: ['贪心', '2008', 'USACO', '生成树', '状压 DP']
---
# [USACO08NOV] Toys G
## 题目描述

Bessie's birthday is coming up, and she wishes to celebrate for the next D (1 <= D <= 100,000; 70% of testdata has 1 <= D <= 500) days. Cows have short attention spans so Bessie wants to provide toys to entertain them. She has calculated that she will require T\_i (1 <= T\_i <= 50) toys on day i.

Bessie's kindergarten provides many services to its aspiring bovine programmers, including a toy shop which sells toys for Tc (1 <= Tc <= 60) dollars. Bessie wishes to save money by reusing toys, but Farmer John is worried about transmitting diseases and requires toys to be disinfected before use. (The toy shop disinfects the toys when it sells them.)

The two disinfectant services near the farm provide handy complete services. The first one charges C1 dollars and requires N1 nights to complete; the second charges C2 dollars and requires N2 nights to complete (1 <= N1 <= D; 1 <= N2 <= D; 1 <= C1 <= 60; 1 <= C2 <= 60). Bessie takes the toys to the disinfecters after the party and can pay and pick them back up the next morning if one night service is rendered, or on later mornings if more nights are required for disinfecting.

Being an educated cow, Bessie has already learned the value of saving her money. Help her find the cheapest way she can provide toys for her party.

POINTS: 400

## 输入格式

\* Line 1: Six space-separated integers: D, N1, N2, C1, C2, Tc

\* Lines 2..D+1: Line i+1 contains a single integer: T\_i

## 输出格式

\* Line 1: The minimum cost to provide safe and sanitary toys for Bessie's birthday parties.

## 样例

### 样例输入 #1
```
4 1 2 2 1 3 
8 
2 
1 
6 

```
### 样例输出 #1
```
35 

```
## 提示

Bessie wishes to party for 4 days, and requires 8 toys the first day, 2 toys the second, 1 toy the third, and 6 toys on the fourth day. The first disinfectant service takes 1 day and charges $2, and the second takes 2 days and charges $1. Buying a new toy costs $3.


Day 1   Purchase 8 toys in the morning for $24; party in the

afternoon. Take 2 toys to the fast cleaner (overnight) and 

the other 6 toys to the slow cleaner (two nights). 

Day 2   Pick up the two toys at the fast cleaner; pay $4. Party in the afternoon. Take 1 toy to the slow cleaner. 

Day 3   Pick up 6 toys from the slow cleaner and pay $6. Party in the afternoon.

Day 4   Pick up the final remaining toy from the slow cleaner

(bringing the number of toys onsite back to 6); pay $1. Party hearty with the realization that a minimum amount of money was spent.

## 题目翻译

Bessie 的生日快到了，她希望用 $D$（$1 \le D \le 100000$）天来庆祝。奶牛们的注意力不会太集中，因此 Bessie 想通过提供玩具的方式来使它们高兴。她已经计算出了第 $i$ 天需要的玩具数 $T_i$（$1 \le T_i \le 50$）。

Bessie 的幼儿园给它们的奶牛程序员们提供了许多服务，包括一个每天以 $T_c\ (1 \le T_c \le 60)$ 美元卖出商品的玩具店。Bessie 想尽可能地节省钱。但是 FarmerJohn 担心没有经过消毒的玩具会带来传染病。（玩具店卖出的玩具是经过消毒的）

有两种消毒的方式。

- 第 $1$ 种方式需要收费 $C_1$ 美元，需要 $N_1$ 个晚上的时间；
- 第 $2$ 种方式需要收费 $C_2$ 美元，需要 $N_2$ 个晚上的时间（$1 \le N_1,N_2 \le D$，$1 \le C_1,C_2 \le 60$）。

Bessie 在派对结束之后把她的玩具带去消毒。如果消毒只需要一天，那么第二天就可以拿到；如果还需要一天，那么第三天才可以拿到。

作为一个受过教育的奶牛，Bessie 已经了解到节约的意义。帮助她找到提供玩具的最便宜的方法。


---

---
title: "[USACO08DEC] Largest Fence G"
layout: "post"
diff: 省选/NOI-
pid: P2924
tag: ['数学', '2008', 'USACO', '素数判断,质数,筛法', '凸包']
---
# [USACO08DEC] Largest Fence G
## 题目描述

Farmer John has purchased N (5 <= N <= 250) fence posts in order to build a very nice-looking fence. Everyone knows the best fences are convex polygons where fence posts form vertices of a polygon. The pasture is represented as a rectilinear grid; fencepost i is at integer coordinates (x\_i, y\_i) (1 <= x\_i <= 1,000; 1 <= y\_i <= 1000).

Given the locations of N fence posts (which, intriguingly, feature no set of three points which are collinear), what is the largest number of fence posts FJ can use to create a fence that is convex?

For test cases worth 45% of the points for this problem, N <= 65.

Time limit: 1.2 seconds

POINTS: 400

Farmer John的农场里有N（5<=N<=250）个篱笆桩，每个都有独一无二的坐标(xi,yi)（1<=xi,yi<=1000）。他想选择尽量多的篱笆桩来构建他的围栏。这个围栏要美观，所以必须是凸多边形的。那他最多能选多少个呢？

所有的篱笆桩中不存在三点共线。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 describes fence post i's location with two space-separated integers: x\_i and y\_i

## 输出格式

\* Line 1: A single integer, the maximum possible number of fence posts that form a convex polygon.

## 样例

### 样例输入 #1
```
6 
5 5 
2 3 
3 2 
1 5 
5 1 
1 1 

```
### 样例输出 #1
```
5 

```
## 提示

A square with two points inside.


The largest convex polygon is the pentagon (2,3), (3,2), (5,1), (5,5), (1,5).



---

---
title: "[USACO09HOL] Cattle Bruisers G"
layout: "post"
diff: 省选/NOI-
pid: P2928
tag: ['2009', 'USACO']
---
# [USACO09HOL] Cattle Bruisers G
## 题目描述

Canmuu is out for revenge after being utterly defeated by Bessie in paintball and has challenged Bessie to a video game.

In this game, Bessie starts out at point (BX, BY) in the coordinate grid (-1,000 <= BX <= 1,000; -1000 <= BY <= 1,000), and tries to escape, starting at time 0. She moves continuously at a velocity of (BVX, BVY) units/second (-100 <= BVX <= 100; -100 <= BVY <= 100). Thus, at time 1 she will be at point (BX + BVX, BY + BVY); at time 1.5 she will be at (BX + 1.5\*BVX, BY + 1.5\*BVY).

Unfortunately, Canmuu has sent N (1 <= N <= 50,000) cattle bruisers to pursue Bessie.  At time t=0, cattle bruiser i is at position (X\_i, Y\_i) (-1,000 <= X\_i <= 1,000; -1,000 <= Y\_i <= 1,000) with velocity (VX\_i, VY\_i) units/second (-1,000 <= VX\_i <= 1,000; -1,000 <= VY\_i <= 1,000).

Each cattle bruiser carries a 'proximity' weapon to fire at Bessie; the weapon can hurt Bessie when the cattle bruiser is no further than R (1 <= R <= 2,500) units from her.

Bessie has a shield to protect herself from these attacks. However, she does not want to waste any of her shield's power, so she would like to know the maximum number of cattle bruisers within firing range for any (potentially non-integer) time t >= 0.

In order to avoid precision errors with real numbers, it is guaranteed that the answer produced will be the same whether the attack range is decreased to R-0.0001 or increased to R+0.0001.

FEEDBACK: Your first 50  submissions for this problem will be run on some of the official test data, and you will receive a summary of the results.

自从卡门在弹珠游戏中被贝茜彻底击败，他一直在想找机会复仇.这会儿，他邀贝茜去玩一 个电脑游戏.

游戏中，贝茜在（BX,BY）处开始行动，这时时刻为0.她要试图 逃离.她的速度为(BVX，BVY)每秒.

不幸的是，卡门为了复仇，放出N(l<=N< =50000)个杀手追击贝茜.在t = 0时，杀手i的位置 是Xi, Yi他的速度是Vxi,Vyi每秒.

由于每个杀手配备了手枪，手枪的射程是R，也就是说贝茜要与这个杀手的距 离保持超过R，否则有性命之虞.

然而，贝茜还有一件秘密武器，盾.但是，她不想过多地消耗盾的能量.所以，她想知道在 逃脱过程中，某一个时刻她在最多为多少个杀手的射程内.当然这个时刻不一定是整数.

为了防止出现精度误差，数据保证在R 土 0.0001时也能得出正确结果.

## 输入格式

\* Line 1: Six space-separated integers: N, R, BX, BY, BVX, and BVY

\* Lines 2..N+1: Line i+1 contains four space-separated integers: X\_i, Y\_i, VX\_i, and VY\_i

## 输出格式

\* Line 1: Print a single integer denoting the maximum number of cattle bruisers within attack range at any point in time.

## 样例

### 样例输入 #1
```
3 1 0 0 0 2 
0 -3 0 4 
1 2 -1 1 
1 -2 2 -1 

```
### 样例输出 #1
```
2 

```
## 提示

Bessie starts at point (0, 0) and is moving at 2 units per second in the (positive) y-direction. There are 3 cattle bruisers, the first of which starts at point (0, -3) and travels 4 units per second in the y-direction. The maximum distance for a cattle bruiser to be in range of Bessie is 1 unit.


At time 1.5, Bessie is at point (0, 3), and the three bruisers are at points (0, 3), (-0.5, 3.5), and (4, -3.5). The first two cattle bruisers are within 1 unit of Bessie, while the third will never be within 1 unit of Bessie, so 2 is the most achievable.



---

---
title: "[USACO09HOL] Holiday Painting G"
layout: "post"
diff: 省选/NOI-
pid: P2930
tag: ['2009', 'USACO']
---
# [USACO09HOL] Holiday Painting G
## 题目描述

To show their spirit for the holidays, the cows would like to paint a picture! Their picture will be represented as an R x C (1 <= R <= 50,000; 1 <= C <= 15) grid of unit squares, each of which is either 0 or 1. The grid rows are conveniently numbered 1..R; the columns are numbered 1..C.

Being pressed for time, the cows have asked their neighbors north of the border for help. Under the very helpful supervision of Canmuu the moose, they constructed a machine to throw paint at the picture in entire buckets! Beginning with all 0's in the picture grid, the machine splashes a certain paint color (either 0 or 1) over a

rectangle in the grid. In particular, Canmuu suggested that they perform Q (1 <= Q <= 10,000) operations; operation i consists of five integers R1\_i, R2\_i, C1\_i, C2\_i, and X\_i (1 <= R1\_i <= R2\_i <= R; 1 <= C1\_i <= C2\_i <= C; 0 <= X\_i <= 1), meaning that the cows will paint each unit square with a row index between R1\_i and R2\_i, inclusive, and a column index between C1\_i and C2\_i, inclusive, with color X\_i.

However, painting a picture like this is quite prone to mistakes. So Canmuu has enlisted you to determine, after each operation, the number of unit squares in the grid which are the correct color.

MEMORY LIMIT: 64 MB

TIME LIMIT: 1.5 seconds

为了表达假日的激情，奶牛们要画一幅巨大的画。

画布可以分成$R\times C$个方格，从上到下编为 $1$ 到 $R$ 行，从左到右编为 $1$ 到 $C$ 列。作画的颜色有两种，白色（用 $0$ 表示）或者黑色（用 $1$ 表示）。

由于时间紧迫，奶牛们不得不请教北面的邻居，卡门。卡门送给它们一台机器，一次操作只输入5个参数 $R1_i,R2_i,C1_i,C2_i,X_i$ $(1 \le R1_i \le R2_i \le R;1 \le C1_i \le C2_i \le C;0 \le X_i \le 1)$，把 $R1_i$ 行到 $R2_i$ 行，$C1_i$ 列到 $C2_i$ 列的一个大长方形涂成 $X_i$ 色。在所有操作还未进行的时候，画布是白色的。

奶牛们一共要进行 $Q$ 次操作。

因为这样的画法总要出些差错，所以奶牛们想请你算算，每一次操作过后，一共有多少个方格与它们的目标画里对应的方格是同色的。
## 输入格式

\* Line 1: Three space-separated integers: R, C, and Q

\* Lines 2..R+1: Line i+1 contains C characters, each '0' or '1', denoting the i-th row of the grid in the obvious way.

\* Lines R+2..R+Q+1: Line R+i+1 contains five space-separated integers representing a paint operation: R1\_i, R2\_i, C1\_i, C2\_i, and X\_i

## 输出格式

\* Lines 1..Q: On line i+1, print a single integer representing the number of matching unit squares after the i-th operation.

## 样例

### 样例输入 #1
```
17 15 10 
111111101111111 
111111000111111 
111110000011111 
111100000001111 
111000000000111 
111100000001111 
111000000000111 
110000000000011 
111000000000111 
110000000000011 
100000000000001 
110000000000011 
100000000000001 
000000000000000 
111111000111111 
111111000111111 
111111000111111 
5 8 2 14 1 
8 17 3 7 1 
4 5 10 15 0 
7 16 12 14 1 
2 17 13 14 0 
2 6 2 3 1 
13 14 4 8 1 
3 6 6 7 1 
1 16 10 11 0 
7 16 10 10 0 

```
### 样例输出 #1
```
113 
94 
95 
91 
87 
93 
91 
87 
93 
93 

```
## 提示

The cows want to paint a picture of a holiday tree


After the first operation, the picture grid looks as follows:

000000000000000

000000000000000

000000000000000

000000000000000

011111111111110

011111111111110

011111111111110

011111111111110

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

There are 113 unit squares which match the corresponding square in the tree image; they are denoted below by an 'x' (the other bits are shown as they appear after the first paint splash):

0000000x0000000

000000xxx000000

00000xxxxx00000

0000xxxxxxx0000

0xx111111111xx0

0xxx1111111xxx0

0xx111111111xx0

0x11111111111x0

000xxxxxxxxx000

00xxxxxxxxxxx00

0xxxxxxxxxxxxx0

00xxxxxxxxxxx00

0xxxxxxxxxxxxx0

xxxxxxxxxxxxxxx

000000xxx000000

000000xxx000000

000000xxx000000



---

---
title: "[USACO09JAN] Safe Travel G"
layout: "post"
diff: 省选/NOI-
pid: P2934
tag: ['2009', 'USACO', '并查集', '最短路', '最近公共祖先 LCA']
---
# [USACO09JAN] Safe Travel G
## 题目描述

Gremlins have infested the farm. These nasty, ugly fairy-like

creatures thwart the cows as each one walks from the barn (conveniently located at pasture\_1) to the other fields, with cow\_i traveling to from pasture\_1 to pasture\_i. Each gremlin is personalized and knows the quickest path that cow\_i normally takes to pasture\_i. Gremlin\_i waits for cow\_i in the middle of the final cowpath of the quickest route to pasture\_i, hoping to harass cow\_i.

Each of the cows, of course, wishes not to be harassed and thus chooses an at least slightly  different route from pasture\_1 (the barn) to pasture\_i.

Compute the best time to traverse each of these new not-quite-quickest routes that enable each cow\_i that avoid gremlin\_i who is located on the final cowpath of the quickest route from pasture\_1 to

pasture\_i.

As usual, the M (2 <= M <= 200,000) cowpaths conveniently numbered 1..M are bidirectional and enable travel to all N (3 <= N <= 100,000) pastures conveniently numbered 1..N. Cowpath i connects pastures a\_i (1 <= a\_i <= N) and b\_i (1 <= b\_i <= N) and requires t\_i (1 <= t\_i <= 1,000) time to traverse. No two cowpaths connect the same two pastures, and no path connects a pasture to itself (a\_i != b\_i). Best of all, the shortest path regularly taken by cow\_i from pasture\_1 to pasture\_i is unique in all the test data supplied to your program.

By way of example, consider these pastures, cowpaths, and [times]:

```cpp
1--[2]--2-------+ 
|       |       | 
[2]     [1]     [3] 
|       |       | 
+-------3--[4]--4
```
``` 
TRAVEL     BEST ROUTE   BEST TIME   LAST PATH 
p_1 to p_2       1->2          2         1->2 
p_1 to p_3       1->3          2         1->3 
p_1 to p_4      1->2->4        5         2->4 
```
When gremlins are present:

```cpp
TRAVEL     BEST ROUTE   BEST TIME    AVOID 
p_1 to p_2     1->3->2         3         1->2 
p_1 to p_3     1->2->3         3         1->3 
p_1 to p_4     1->3->4         6         2->4 
```
For 20% of the test data, N <= 200. 

For 50% of the test data, N <= 3000. 

TIME LIMIT: 3 Seconds

MEMORY LIMIT: 64 MB
## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..M+1: Three space-separated integers: a\_i, b\_i, and t\_i

## 输出格式

\* Lines 1..N-1: Line i contains the smallest time required to travel from pasture\_1 to pasture\_i+1 while avoiding the final cowpath of the shortest path from pasture\_1 to pasture\_i+1. If no such path exists from pasture\_1 to pasture\_i+1, output -1 alone on the line.

## 样例

### 样例输入 #1
```
4 5 
1 2 2 
1 3 2 
3 4 4 
3 2 1 
2 4 3 

```
### 样例输出 #1
```
3 
3 
6 

```
## 题目翻译

**【题目描述】**

给定一张有 $n$ 个节点，$m$ 条边的无向图，对于任意的 $i$（$2\le i\le n$），请求出在不经过原来 $1$ 节点到 $i$ 节点最短路上最后一条边的前提下，$1$ 节点到 $i$ 节点的最短路。

特别地，保证 $1$ 到任何一个点 $i$ 的最短路都是唯一的。

保证图中没有重边和自环。

**【输入格式】**

第一行，两个整数 $n,m$。

之后 $m$ 行，每行三个整数 $a_i,b_i,t_i$ 表示有一条 $a_i$ 到 $b_i$，边权为 $t_i$ 的无向边。

**【输出格式】**

共 $n-1$ 行，第 $i$ 行表示 $1$ 到 $i+1$ 在不经过原来 $1$ 节点到 $i+1$ 节点最短路上最后一条边的前提下的最短路。如果最短路不存在，则在对应行输出 `-1`。

翻译贡献者：@[cryozwq](/user/282751)。


---

---
title: "[USACO09MAR] Earthquake Damage 2 G"
layout: "post"
diff: 省选/NOI-
pid: P2944
tag: ['2009', 'USACO', '网络流', '图论建模', '最小割']
---
# [USACO09MAR] Earthquake Damage 2 G
## 题目描述

Wisconsin has had an earthquake that has struck Farmer John's farm! The earthquake has damaged some of the pastures so that they are unpassable. Remarkably, none of the cowpaths was damaged.

As usual, the farm is modeled as a set of P (1 <= P <= 3,000) pastures conveniently numbered 1..P which are connected by a set of C (1 <= C <= 20,000) non-directional cowpaths conveniently numbered 1..C. Cowpath i connects pastures a\_i and b\_i (1 <= a\_i <= P; 1 <= b\_i <= P). Cowpaths might connect a\_i to itself or perhaps might connect two pastures more than once.  The barn is located in pasture 1.

A total of N (1 <= N <= P) cows (in different pastures) sequentially contacts Farmer John via moobile phone with an integer message report\_j (2 <= report\_j <= P) that indicates that pasture report\_j is undamaged but that the calling cow is unable to return to the barn from pasture report\_j because she could not find a path that does not go through damaged pastures.

After all the cows report in, determine the minimum number of pastures that are damaged.

地震袭击了威斯康星州，一些牧场被摧毁了。

一共有 $P$ 个牧场。由 $C$ 条双向路连接。两个牧场间可能有多条路。一条路也可能连接相同的牧场。牛棚坐落在牧场 $1$。

$N\ (1 \le N \le P)$ 只奶牛打来了求救电话，说她们的农场没有被摧毁，但是已经无法到达牛棚。求出最少可能有多少牧场被摧毁。

## 输入格式

\* Line 1: Three space-separated integers: P, C, and N

\* Lines 2..C+1: Line i+1 describes cowpath i with two integers: a\_i and b\_i

\* Lines C+2..C+N+1: Line C+1+j contains a single integer: report\_j

## 输出格式

\* Line 1: One number, the minimum number of damaged pastures.

## 样例

### 样例输入 #1
```
5 5 2 
1 2 
2 3 
3 5 
2 4 
4 5 
4 
5 

```
### 样例输出 #1
```
1 

```
## 提示

Only pasture 2 being damaged gives such a scenario.



---

---
title: "[USACO09NOV] Who Brings the Cookies? G"
layout: "post"
diff: 省选/NOI-
pid: P2961
tag: ['2009', 'USACO', 'Special Judge']
---
# [USACO09NOV] Who Brings the Cookies? G
## 题目描述

Farmer John's N (1 <= N <= 1,000) cows conveniently numbered 1..N decided to form M (1 <= M <= 100) study groups. A total of S\_i (1 <= S\_i <= 19) cows study in group G\_i (namely cows G\_i1, G\_i2, ...). A cow might study in more than one study group.

For each study group, one cow in the group must be chosen to bring cookies to the meeting. Cookies are costly and require time to acquire, so the cows want to divide the work of bringing cookies as fairly as possible.

They decided that if a cow attends meetings with size c\_1, c\_2, ..., c\_K, she is only willing to bring cookies to at most ceil(1/c\_1 + 1/c\_2 + ... + 1/c\_K) meetings.

Figure out which cow brings cookies to each meeting. If this isn't possible, just output '-1'. Choose any solution if more than one is possible.


## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..M+1: Line i+1 contains many space-separated integers: S\_i, G\_i1, G\_i2, ...

## 输出格式

\* Lines 1..M: If a mapping is possible, line i contains the number of the cow who brings cookies to study group i. Otherwise, line 1 contains just the integer -1.

## 样例

### 样例输入 #1
```
5 6 
3 2 4 5 
2 1 3 
3 1 2 3 
1 1 
2 2 5 
3 2 3 4 

```
### 样例输出 #1
```
5 
1 
3 
1 
2 
4 

```
## 提示

Cow1 can bring cookies to at most 2 meetings, cow2 can bring 2, cow3 can bring 2, cow4 can bring 1, and cow5 can bring 1.

## 题目翻译

农夫约翰的 $N(1 \le N \le 1000)$ 只奶牛（编号为 $1$ 到 $N$）决定成立 $M(1 \le M \le 100)$ 个学习小组。在学习小组 $G_i$ 中有 $S_i$ 只牛，分别为牛$G_{i1},G_{i2},\cdots$，一头牛可能会参加多个小组。

对于每个学习小组，有一只牛必须在每次聚会的时候带饼乾饮料请大家吃（衰～）。因为买这些零食会消耗牛们那为数不多的零花钱，还会花费牛们宝贵的时间，所以牛们希望尽可能公平地分摊带零食的责任。 牛们决定。如果一只牛参加了 $K$ 个学习小组，$K$ 个学习小组的大小分别为 $c_1,c_2, \cdots c_K$，那麽她最多负责为 $\lceil \frac{1}{c_1} + \frac {1}{c_2} + \cdots + \frac{1}{c_K} \rceil$ 个学习小组的聚会带零食。其中 $\lceil \rceil$为上取整函数。 请计算出一个方案，决定每个学习小组的聚会由哪一头牛负责带零食。如果没有一种方案可行，输出 `-1`。



---

---
title: "[USACO10HOL] Cow Politics G"
layout: "post"
diff: 省选/NOI-
pid: P2971
tag: ['2010', 'USACO']
---
# [USACO10HOL] Cow Politics G
## 题目描述

Farmer John's cows are living on N (2 <= N <= 200,000) different pastures conveniently numbered 1..N. Exactly N-1 bidirectional cow paths (of unit length) connect these pastures in various ways, and each pasture is reachable from any other cow pasture by traversing one or more of these paths (thus, the pastures and paths form a graph called a tree).

The input for a particular set of pastures will specify the parent node P\_i (0 <= P\_i <= N) for each pasture. The root node will specify parent P\_i == 0, which means it has no parent.

The cows have organized K (1 <= K <= N/2) different political parties conveniently numbered 1..K. Each cow identifies with a single

political party; cow i identifies with political party A\_i (1 <= A\_i <= K). Each political party includes at least two cows.

The political parties are feuding and would like to know how much 'range' each party covers. The range of a party is the largest distance between any two cows within that party (over cow paths).

For example, suppose political party 1 consists of cows 1, 3, and 6, political party 2 consists of cows 2, 4, and 5, and the pastures are connected as follows (party 1 members are marked as -n-):

-3-
|
-1-
/ | \
2  4  5

|
-6-
The greatest distance between any two pastures of political party 1 is 3 (between cows 3 and 6), and the greatest distance for political party 2 is 2 (between cows 2 and 4, between cows 4 and 5, and between cows 5 and 2).

Help the cows determine party ranges.

TIME LIMIT: 2 seconds

MEMORY LIMIT: 64MB

农夫约翰的奶牛住在N (2 <= N <= 200,000)片不同的草地上，标号为1到N。恰好有N-1条单位长度的双向道路，用各种各样的方法连接这些草地。而且从每片草地出发都可以抵达其他所有草地。也就是说，这些草地和道路构成了一种叫做树的图。输入包含一个详细的草地的集合，详细说明了每个草地的父节点P\_i (0 <= P\_i <= N)。根节点的P\_i == 0, 表示它没有父节点。因为奶牛建立了1到K一共K (1 <= K <= N/2)个政党。每只奶牛都要加入某一个政党，其中， 第i只奶牛属于第A\_i (1 <= A\_i <= K)个政党。而且每个政党至少有两只奶牛。 这些政党互相吵闹争。每个政党都想知道自己的“范围”有多大。其中，定义一个政党的范围是这个政党离得最远的两只奶牛（沿着双向道路行走）的距离。

## 输入格式

\* Line 1: Two space-separated integers: N and K

\* Lines 2..N+1: Line i+1 contains two space-separated integers: A\_i and P\_i

## 输出格式

\* Lines 1..K: Line i contains a single integer that is the range of party i.

## 样例

### 样例输入 #1
```
6 2 
1 3 
2 1 
1 0 
2 1 
2 1 
1 5 

```
### 样例输出 #1
```
3 
2 

```
## 题目翻译

农夫约翰的奶牛住在 $n$ 片不同的草地上，标号为 $1$ 到 $n$。

恰好有 $n-1$ 条单位长度的双向道路，用各种各样的方法连接这些草地。而且从每片草地出发都可以抵达其他所有草地。也就是说，这些草地和道路构成了一种叫做树的图。输入包含一个详细的草地的集合，详细说明了每个草地的父节点 $p_i$（$0 \le p_i \le n$）。根节点的 $p_i = 0$，表示它没有父节点。

因为奶牛建立了 $1$ 到 $k$ 一共 $k$ 个政党。每只奶牛都要加入某一个政党，其中，第 $i$ 只奶牛属于第 $a_i$（$1 \le a_i \le k$）个政党。而且每个政党至少有两只奶牛。每个政党都想知道自己的“范围”有多大。其中，定义一个政党的范围是这个政党离得最远的两只奶牛（沿着双向道路行走）的距离。

数据范围：$2 \le n \le 200000$，$1 \le k \le \dfrac n2$


---

---
title: "[USACO10HOL] Driving Out the Piggies G"
layout: "post"
diff: 省选/NOI-
pid: P2973
tag: ['2010', 'USACO', 'Special Judge', 'O2优化', '高斯消元']
---
# [USACO10HOL] Driving Out the Piggies G
## 题目描述

The Cows have constructed a randomized stink bomb for the purpose of driving away the Piggies. The Piggy civilization consists of N (2 <= N <= 300) Piggy cities conveniently numbered 1..N connected by M (1 <= M <= 44,850) bidirectional roads specified by their distinct endpoints A\_j and B\_j (1 <= A\_j <= N; 1 <= B\_j <= N). Piggy city 1 is always connected to at least one other city.

The stink bomb is deployed in Piggy city 1. Each hour (including the first one), it has a P/Q (1 <= P <= 1,000,000; 1 <= Q <=

1,000,000; P <= Q) chance of polluting the city it occupies. If it does not go off, it chooses a random road out of the city and follows it until it reaches a new city.  All roads out of a city are equally likely to be chosen.

Because of the random nature of the stink bomb, the Cows are wondering which cities are most likely to be polluted. Given a map of the Piggy civilization and the probability that the stink bomb detonates in a given hour, compute for each city the probability that it will be polluted.

For example, suppose that the Piggie civilization consists of two cities connected together and that the stink bomb, which starts in city 1, has a probability of 1/2 of detonating each time it enters a city:

1--2
We have the following possible paths for the stink bomb (where the last entry is the ending city):

1: 1
2: 1-2
3: 1-2-1

4: 1-2-1-2

5: 1-2-1-2-1

etc.
To find the probability that the stink bomb ends at city 1, we can add up the probabilities of taking the 1st, 3rd, 5th, ... paths above (specifically, every odd-numbered path in the above list). The probability of taking path number k is exactly (1/2)^k - the bomb must not remain in its city for k - 1 turns (each time with a probability of 1 - 1/2 = 1/2) and then land in the last city

(probability 1/2). 

So our probability of ending in city 1 is represented by the sum 1/2 + (1/2)^3 + (1/2)^5 + ... . When we sum these terms infinitely, we will end up with exactly 2/3 as our probability, approximately 0.666666667. This means the probability of landing in city 2 is 1/3, approximately 0.333333333. 

Partial feedback will be provided for your first 50 submissions. 
## 输入格式

\* Line 1: Four space separated integers: N, M, P, and Q

\* Lines 2..M+1: Line i+1 describes a road with two space separated integers: A\_j and B\_j

## 输出格式

\* Lines 1..N: On line i, print the probability that city i will be destroyed as a floating point number. An answer with an absolute error of at most 10^-6 will be accepted (note that you should output at least 6 decimal places for this to take effect).

## 样例

### 样例输入 #1
```
2 1 1 2 
1 2 

```
### 样例输出 #1
```
0.666666667 
0.333333333 

```
## 提示

感谢 @[Alpha](https://www.luogu.com.cn/user/87058) 贡献 Special Judge。
## 题目翻译

奶牛们已经制造了一种随机的臭弹，目的是驱赶小猪们。小猪文明由 $N$（$2 \leq N \leq 300$）个小猪城市构成，这些城市通过 $M$（$1 \leq M \leq 44,850$）条双向道路连接，具体的端点为 $A_j$ 和 $B_j$（$1 \leq A_j \leq N; 1 \leq B_j \leq N$）。小猪城市 1 总是与至少一个其他城市相连。

臭弹在小猪城市 1 部署。每个小时（包括第一个小时），它有 $P/Q$（$1 \leq P \leq 1,000,000; 1 \leq Q \leq 1,000,000; P \leq Q$）的概率污染它所处的城市。如果它没有爆炸，它会随机选择一条离开该城市的道路并沿着这条道路行进，直到到达一个新城市。所有离开一个城市的道路被选择的概率是相等的。

由于臭弹的随机特性，奶牛们想知道哪些城市最有可能被污染。给定小猪文明的地图和臭弹在某一小时内引爆的概率，计算每个城市被污染的概率。

例如，假设小猪文明由两个城市相连，并且臭弹在进入每个城市时都有 $1/2$ 的引爆概率：

$$
1--2
$$

我们有以下臭弹的可能路径（最后一项为结束城市）：

1: 1  
2: 1-2  
3: 1-2-1  
4: 1-2-1-2  
5: 1-2-1-2-1  
等。

要找出臭弹最终在城市 1 的概率，我们可以将上述第 1、3、5... 条路径的概率相加（具体来说，是上面列表中的每条奇数编号路径）。路径编号为 $k$ 的概率恰好为 $(1/2)^k$ —— 弹药在城市中必须停留 $k-1$ 回合（每次概率为 $1 - 1/2 = 1/2$），然后到达最后一个城市（概率为 $1/2$）。

因此我们在城市 1 的概率表示为和：

$$
\frac{1}{2} + \left(\frac{1}{2}\right)^3 + \left(\frac{1}{2}\right)^5 + \ldots
$$

当我们无限地求和这些项时，最终得到的概率正好是 $\frac{2}{3}$，约为 $0.666666667$。这意味着在城市 2 的概率是 $\frac{1}{3}$，约为 $0.333333333$。


---

---
title: "[USACO10HOL] Cow War G"
layout: "post"
diff: 省选/NOI-
pid: P2974
tag: ['2010', 'USACO', 'Special Judge', '费用流']
---
# [USACO10HOL] Cow War G
## 题目描述

Farmer John has long had a dispute with neighbor Farmer Tom over a group of V (1 <= V <= 1,000) pastures conveniently numbered 1..V. Both farmers currently graze their cows on the pastures; each pasture might be empty or might have a single cow which is owned by either Farmer John or Farmer Tom.

Farmer John's patience is at an end, and he wishes to settle the dispute with Farmer Tom by tipping over Tom's cows. Of course, he wants to strike first and to tip as many of Farmer Tom's cows as possible.

A total of E (1 <= E <= 5,000) bidirectional cowpaths connect pairs of pastures. No two pastures are connected by more than one cowpath; each path connects exactly two distinct pastures. Paths are described by their endpoints P1\_i and P2\_i (1 <= P1\_i <= V; 1 <= P2\_i <= V).

During his offense, each of Farmer John's cows can traverse a single cowpath if she wishes. Whether or not she chooses to traverse a cowpath, she can then (if she wishes) launch a cow tipping attack to a pasture connected to her pasture by a single cowpath, thus tipping the enemy cow on that pasture. Note that a cow can move and then attack -- but she is not able to attack and then move.

Each pasture can hold exactly one cow at a time; no cow can move to a pasture occupied by another cow, especially if it has been tipped. Of course, if a pasture is vacated, another cow can later move in to take its place. A tipped cow cannot be tipped again.

Farmer John wants to know two things:

\* How many of Farmer Tom's cows he can tip in the first salvo

of the war

\* How to command his cows to move and attack so as to tip

that maximal number of Farmer Tom's cows in that first salvo

Find the maximum number of cows that can be tipped and construct a sequence of move and attack commands to his cows that then obey the rules and tip that number of cows. Any such sequence is acceptable, as long as it tips the maximum number of Farmer Tom's cows.

Consider, for instance, a group of 5 pastures arranged in a line, with each pasture connected (via '--'; see diagram below) to its left and right neighbors (if they exist). In other words, there is a cowpath from Pasture 1 to Pasture 2, Pasture 2 to Pasture 3, etc. Farmer Tom ('T') has 2 cows, standing on pastures 1 and 4, while Farmer John ('J') has 2 cows standing on pastures 3 and 5 ('E' means empty):

1    2    3    4    5

T -- E -- J -- T -- J

In this case, Farmer John can tip both of Farmer Tom's cows by first moving his cow on Pasture 3 to Pasture 2, so that the pastures in order are now TJETJ. Farmer John can then have both of his cows attack to the left.  Note that although the cow in Pasture 3 could have attacked to the right without moving, the rightmost cow would then be unable to attack. The only valid solutions thus have the same move and attacks, although the order in which Farmer John commands his cows can vary slightly.

If you compute the correct maximum number but do not provide a sequence (or your sequence is wrong), you will get 50% of the points for that test case. A program will grade your output.

Partial feedback will be provided for your first 50 submissions.
## 输入格式

\* Line 1: Two space separated integers: V and E

\* Line 2: A string of V characters (no spaces); character #i indicates whether pasture #i is empty ('E') or has a cow owned by Farmer John ('J') or Farmer Tom ('T')

\* Lines 3..E+2: Line i+2 contains two space separated integers: P1\_i and P2\_i

## 输出格式

\* Line 1: A single integer, the maximum number of enemy cows Farmer John can have tipped

\* Lines 2.....: One of Farmer John's instructions to his cows (to be executed in the order given):

MOVE A B

or
ATTACK A B

where A is the vertex the cow occupies before taking the action and B is the vertex it is moving to or attacking, respectively. Note that when instructing a cow that has already moved to attack, the instruction specifies the location the cow is currently standing, not where it was originally.

## 样例

### 样例输入 #1
```
5 4 
TEJTJ 
1 2 
2 3 
3 4 
4 5 

```
### 样例输出 #1
```
2 
MOVE 3 2 
ATTACK 2 1 
ATTACK 5 4 

```
## 提示

The other valid outputs are:

2
MOVE 3 2

ATTACK 5 4

ATTACK 2 1

and
2
ATTACK 5 4

MOVE 3 2

ATTACK 2 1

which are just reorderings of the output shown.  This might not be true on other testdata.

## 题目翻译

### 题目描述

给定 $V$ 个点，$E$ 条边的无向图。
一开始每个点上有 `T` 牛，`J` 牛，或者没有（`E`）。
`J` 牛可以 `MOVE` 到一个相邻的点，也可以 `ATTACK` 相邻点上的一个 `T` 牛。不过操作有限制，只能按照 `MOVE`,`ATTACK` 或者 `MOVE` 然后 `ATTACK` 三种方式操作。
一个 `T` 牛仅能被 `ATTACK` 一次，被 `ATTACK` 后它会留在原地。
需要保证任意时刻，每个点上有且仅有一头牛。
求所有 `T` 牛被 `ATTACK` 的最大次数，并给出一个可行的操作方案。

### 输入格式

第一行两个整数 $V,E$，表示无向图的点数和边数。
接下来一行 $V$ 个字符，第 $i$ 个字符表示第 $i$ 个点的初始状态。
接下来 $E$ 行每行两个整数 $u,v$，表示存在一条连接 $u,v$ 的无向边。

### 输出格式

第一行一个整数，表示所有 `T` 牛被 `ATTACK` 的最大次数。
接下来若干行，每行以 `MOVE u v` 或 `ATTACK u v` 的形式给出，表示你的操作方案。

### 说明/提示

对于测试点 $1\sim5$，$1\leq V\leq 30,1\leq E\leq 50$。
对于测试点 $6\sim 10$，$1\leq V\leq 500,1\leq E\leq 2\times 10^3$。
对于测试点 $11\sim 15$，$1\leq V\leq 10^3,1\leq E\leq 5\times 10^3$。
注意：一个操作需要描述现在的位置，例如：点 $3$ 上的牛先 `MOVE` 到点 $2$，再 `ATTACK` 点 $4$，应该写为：

\```
MOVE 3 2
ATTACK 2 4
\```



---

---
title: "[USACO10JAN] Shipping Around an Island G"
layout: "post"
diff: 省选/NOI-
pid: P2976
tag: ['2010', 'USACO']
---
# [USACO10JAN] Shipping Around an Island G
## 题目描述

Farmer John decided to start his own cruise ship line! He has but one ship, but is hoping for big growth. He recently acquired a map of the area of ocean where his cruise ship will operate. It looks something like the diagram below, with height H (3 <= H <= 1000) and width W (3 <= W <= 1000).

```cpp
................... 
................... 
.....A............. 
.....A..x.......... 
..x..A.....AAAA.... 
.....A.....A..A.... 
.....AAAAAAAA.A.... 
........A.....A.... 
.xx...AAA...x.A.... 
......A............ 
...AAAAAAAAAAAAA... 
................... 
```
In this map, '.' denotes water; 'A' is an element of the main island; and 'x' are other islands.

Farmer John has decided his cruise ship will loop around the main island. However, due to trade restrictions, the path his ship takes is NOT allowed to go around any OTHER islands. For instance, the following path of length 50 is not allowed because it encloses the island denoted by 'x'.

```cpp
................... 
....+--+........... 
....|A.|........... 
....|A.|x.+-----+.. 
..x.|A.+--+AAAA.|.. 
....|A.....A..A.|.. 
....|AAAAAAAA.A.|.. 
....|...A.....A.|.. 
.xx.|.AAA...x.A.|..    <--- route circumnavigates 'x' -- illegal! ..+-+.A.........|.. 
..|AAAAAAAAAAAAA|.. 
..+-------------+.. 
```
Given a map, help Farmer John determine the shortest path his cruise ship can take to go around the main island without going around any other islands.

Two cells are considered connected if they lie vertically or

horizontally across from one another (not diagonally). It is

guaranteed that the main island is connected and that a solution exists.

Note that FJ's path may visit the same square more than once, for instance there are three squares that are visited more than once in FJ's optimal path (of length 62) for the example:

```cpp
................... 
....+--+........... 
....|A.|........... 
....|A.|x.+----+... 
..x.|A.+--+AAAA|... 
....|A.....A..A|... 
....|AAAAAAAA.A|... 
....|...A..+-+A|... 
.xx.|.AAA..|x|A|... 
..+-+.A....+-+-++.. 
..|AAAAAAAAAAAAA|.. 
..+-------------+.. 
```
The above diagram is somewhat unclear because of the path overlapping itself.  Drawn in two stages, FJ's optimal path is:

```cpp
...................            ................... 
...................            ....+--+........... 
.....A.............            ....|A.|........... 
.....A..x..........            ....|A.|x.+----+... 
..x..A.....AAAA....            ..x.|A.+--+AAAA|... 
.....A.....A..A....  and then  ....|A.....A..A|... 
.....AAAAAAAA.A....            ....|AAAAAAAA.A|... 
....V...A..+>.A....            ....V...A...>+A|... 
.xx.|.AAA..|x.A....            .xx...AAA...x|A|... 
..+-+.A....+----+..            .....A.......+-+... 
..|AAAAAAAAAAAAA|..            ...AAAAAAAAAAAAA... 
..+-------------+..            ................... 
```

John 得到一份地图，长 $H$（$3 \leq H\leq 1000$）宽 $W$（$3 \leq W\leq 1000$），地图中 ``.`` 表示水，`A` 表示大陆，`x` 表示其他小岛。他决定驾驶他的船绕大陆一圈，但并不想环绕其他小岛。John 可以再任意有水的格子出发，求绕一周最小路径长度（一个格子可以经过任意多次）。

输入格式：

第一行两个空格隔开正整数 $H$ 和 $W$（$3 \leq H,W\leq 1000$），接下来有 $H$ 行，每行 $W$ 个字符表示地图。
## 输入格式

\* Line 1: Two space-separated integers: H and W

\* Lines 2..H+1: Line i+1 contains contains W characters that are the elements of map row i (all '.' or 'x' or 'A')

## 输出格式

\* Line 1: The minimum length of a path that Farmer John's cruise ship can take

## 样例

### 样例输入 #1
```
12 19 
................... 
................... 
.....A............. 
.....A..x.......... 
..x..A.....AAAA.... 
.....A.....A..A.... 
.....AAAAAAAA.A.... 
........A.....A.... 
.xx...AAA...x.A.... 
......A............ 
...AAAAAAAAAAAAA... 
................... 

```
### 样例输出 #1
```
62 

```


---

---
title: "[USACO10MAR] StarCowraft G"
layout: "post"
diff: 省选/NOI-
pid: P2987
tag: ['2010', 'USACO']
---
# [USACO10MAR] StarCowraft G
## 题目描述

The beta version of StarCowraft II is ready! Farmer John and Bessie are testing it, trying different strategies in one-on-one battles against each other's armies. The goal in StarCowraft II is to defeat your opponent's army in a battle.

Each player's army fights in a battle. An army comprises as many as three different types of 'units' with respective strengths denoted by constant positive real numbers unknown to the players: cattlebruisers with strength S1, cow templars with strength S2, and ultracows with strength S3. The only given bounding information is that no unit is more than 100 times as strong as any another unit.

An army's total strength is the sum of the individual strengths of each of its units. An army that has, among others units, 23

cattlebruisers would gain 23\*S1 strength just from the cattlebruisers.

When two opposing armies fight in a battle, the army with a higher total strength value wins.  If the armies have exactly equal strength values, one of the players randomly wins.

Farmer John and Bessie played N (0 <= N <= 300) 'test battles'. In the i-th test battle, FJ's army had J1\_i cattlebruisers, J2\_i cow templars, and J3\_i ultracows (0 <= J1\_i + J2\_i + J3\_i <= 1,000). Similarly, Bessie's army had B1\_i cattlebruisers, B2\_i cow templars, and B3\_i ultracows (0 <= B1\_i + B2\_i + B3\_i <= 1,000). After their armies fought against each other, FJ and Bessie recorded the winner as a single 'victory letter' V\_i: 'J' if Farm John won the battle; 'B' if Bessie won.

Although these victory results are the only information that they have, they hope to predict some of the results of additional battles if they are given the unit compositions of two opposing armies. For some battles, though, they know it might not be possible to determine the winner with certainty.

Given the results of the N test battles that Farmer John and Bessie already played, write a program that decides the winner (if possible) for M (1 <= M <= 2,000) new battles.

The results reported for the test battles are correct; there exists at least one set of strength values which are consistent with the results.

For purposes of demonstrating the army strength evaluation functions, consider these test battles fought in a game where we (but neither FJ nor Bessie) know that S1=9.0, S2=7.0, and S3=4.0:

```cpp
---- Farmer John ----    ------- Bessie ------    Battle 
J1  J2  J3 J_Strength    B1  B2  B3 B_Strength   Outcome 
6   5   4    105         5   4   7    101          J 
5   4   2     81         3   5   5     82          B 
9   0  10    121         8   2   7    114          J 
```
These results connote the following deduced results for the reasons shown:

---- Farmer John ----    ------- Bessie ------    Battle

J1  J2  J3 J\_Strength    B1  B2  B3 B\_Strength   Outcome

6   6   4    112         5   4   7    101          J

FJ's army is even stronger than in test battle 1 9   0  10    121         8   2   6    110          J

Bessie's army is even weaker than in test battle 3

《星际争霸2》全面公测啦！Farmer John和Bessie正在测试中——在1v1的战役中使用一些不同的策略来对抗对方的部队。《星际争霸2》的游戏目标就是在战役中打败你对手的军队。

每个选手的军队都在战役中拼杀。一支军队由若干3种不同类型的单位所组成，不同单位有着不同的由正实数表示的，且不被选手所知道的力量值：cattlebruisers 的力量是S1，cow templars 的力量是S2，ultracows的力量是S3。唯一提供的信息是，没有一个单位的力量值超过另一个单位力量值的100倍。

一支军队的总力量值，是其中各自单独的单位的力量值的总和。比如一支军队除了其他单位有23个cattlebruisers，那么这支军队单独从cattlebruisers就能获得23\*S1的力量值。

当两支对立的军队在战役中厮杀，有着更高力量值的军队将获得胜利。如果两支军队的力量值恰好相同，那么将随机产生一个获胜方。

Farmer John 和 Bessie 进行了 N (0 <= N <= 300) 局的“测试战役”。在第 i 局测试战役中，Farmer John 有 J1\_i 个 cattlebruisers，J2\_i 个 cow templars 以及 J3\_i 个 ultracows(0 <= J1\_i + J2\_i + J3\_i <= 1,000)。相似的，Bessie的军队有 B1\_i 个 cattlebruisers，B2\_i 个 cow templars 以及 B3\_i 个 ultracows (0 <= B1\_i + B2\_i + B3\_i <= 1,000)。当他们的军队战斗结束后，FJ 和 Bessie 将胜者以一个单独的“胜利字母” V\_i 记录下来："J"表示 Farmer John 赢得了战役；"B" 表示 Bessie 获胜了。

虽然这些结果是他们唯一所拥有的信息，但是他们希望预测一些额外的战役的结果——如果告知他们两支对立军队的组成。尽管，可能对于一些比赛他们是无法确定到底哪一方一定能获胜的。

给出已经结束的 N 场测试战役的结果，写一个程序来确定(如果可能的话)M (1 <=M <=2,000)场额外战役的获胜方。

所有给出的测试战役的结果都是正确的。至少存在一种合法的力量值的取值符合这些结果。

## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..N+1: Line i+1 describes a test battle with seven

space-separated items -- a victory letter and six

space-separated integer unit counts: V\_i, J1\_i, J2\_i, J3\_i, B1\_i, B2\_i, and B3\_i

\* Lines N+2..N+M+1: Line i+N+1 describes a 'new battle' using six space-separated integers: J1\_i, J2\_i, J3\_i, B1\_i, B2\_i, and B3\_i

## 输出格式

\* Lines 1..M: Line i contains the outcome of the i-th new battle: 'J' if Farmer John definitely wins, 'B' if Bessie definitely wins, and 'U' (undecidable) if it is impossible to decide the winner with the given information.

## 样例

### 样例输入 #1
```
3 3 
J 6 5 4 5 4 7 
B 5 4 2 3 5 5 
J 9 0 10 8 2 7 
6 6 4 5 4 7 
9 0 10 8 2 6 
3 4 8 4 4 6 

```
### 样例输出 #1
```
J 
J 
U 

```
## 提示

First two games correspond to the examples in the description. The result of the last game cannot be determined with only the information that Farmer John and Bessie currently have. Specifically, both S\_1=9.0, S\_2=7.0, S\_3=4.0 and S\_1=12.0, S\_2=20.0, S\_3=10.0 are consistent with the &quot;test battles,&quot; but they give different results when plugged in the third &quot;new battle.&quot;



---

---
title: "[USACO10OPEN] Triangle Counting G"
layout: "post"
diff: 省选/NOI-
pid: P2992
tag: ['计算几何', '2010', 'USACO', '排序', '容斥原理']
---
# [USACO10OPEN] Triangle Counting G
## 题目描述

Bessie is standing guard duty after

the big bad wolf was spotted stalking

```cpp
cows over at Farmer Don's spread. 
Looking down from her guard tower in 
utter boredom, she's decided to 
perform intellectual exercises in 
```
order to keep awake.
After imagining the field as an X,Y

grid, she recorded the coordinates of

the N (1 <= N <= 100,000) 

conveniently numbered 1..N cows as

```cpp
X_i,Y_i (-100,000 <= X_i <= 100,000; 
-100,000 <= Y_i <= 100,000; 1 <= i <= 
N). She then mentally formed all possible triangles that could be made from subsets of the entire set of cow coordinates. She counts a triangle as 'golden' if it wholly contains the origin (0,0). The origin does not fall on the line between any pair of cows. Additionally, no cow is standing exactly on the origin. 
Given the list of cow locations, calculate the number of 'golden' triangles that contain the origin so Bessie will know if she's doing a good job. 
```
By way of example, consider 5 cows at these locations:
-5,0   0,2   11,2   -11,-6   11,-5

Below is a schematic layout of the field from Betsy's point of view:

```cpp
............|............ 
............*..........*. 
............|............ 
-------*----+------------ 
............|............ 
............|............ 
............|............ 
............|............ 
............|..........*. 
.*..........|............ 
............|............ 
```
All ten triangles below can be formed from the five points above:

By inspection, 5 of them contain the origin and hence are 'golden'.

在一只大灰狼偷偷潜入Farmer Don的牛群被群牛发现后，贝西现在不得不履行着她站岗的职责。从她的守卫塔向下瞭望简直就是一件烦透了的事情。她决定做一些开发智力的小练习，防止她睡着了。



想象牧场是一个X，Y平面的网格。她将N只奶牛标记为1…N (1 <= N <= 100,000)，每只奶牛的坐标为X\_i,Y\_i (-100,000 <= X\_i <= 100,000;-100,000 <= Y\_i <= 100,000; 1 <= i <=N)。然后她脑海里想象着所有可能由奶牛构成的三角形。如果一个三角形完全包含了原点(0,0)，那么她称这个三角形为“黄金三角形”。原点不会落在任何一对奶牛的连线上。另外，不会有奶牛在原点。

给出奶牛的坐标，计算出有多少个“黄金三角形”。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Each line contains two integers, the coordinates of a single cow: X\_i and Y\_i

## 输出格式

\* Line 1: A single line with a single integer that is the count of the number of times a triangle formed by the cow locations contains the origin

## 样例

### 样例输入 #1
```
5 
-5 0 
0 2 
11 2 
-11 -6 
11 -5 

```
### 样例输出 #1
```
5 

```


---

---
title: "[USACO10DEC] Threatening Letter G"
layout: "post"
diff: 省选/NOI-
pid: P3002
tag: ['贪心', '2010', 'USACO', '排序']
---
# [USACO10DEC] Threatening Letter G
## 题目描述

FJ has had a terrible fight with his neighbor and wants to send him a nasty letter, but wants to remain anonymous. As so many before him have done, he plans to cut out printed letters and paste them onto a sheet of paper. He has an infinite number of the most recent issue of the Moo York Times that has N (1 <= N <= 50,000) uppercase letters laid out in a long string (though read in as a series of shorter strings). Likewise, he has a message he'd like to compose that is a single long string of letters but that is read in as a set of shorter strings.

Being lazy, he wants to make the smallest possible number of cuts. FJ has a really great set of scissors that enables him to remove any single-line snippet from the Moo York Times with one cut. He notices that he can cut entire words or phrases with a single cut, thus reducing his total number of cuts.

What is the minimum amount of cuts he has to make to construct his letter of M (1 <= M <= 50,000) letters?

It is guaranteed that it is possible for FJ to complete his task.

Consider a 38 letter Moo York Times:

```cpp
THEQUICKBROWNFOXDO 
GJUMPSOVERTHELAZYDOG 
from which FJ wants to construct a 9 letter message: 
FOXDOG 
DOG 
```
These input lines represent a pair of strings:
THEQUICKBROWNFOXDOGJUMPSOVERTHELAZYDOG 

FOXDOGDOG 

Since 'FOXDOG' exists in the newspaper, FJ can cut this piece out and then get the last 'DOG' by cutting out either instance of the word 'DOG'. 

Thus, he requires but two cuts.

FJ 刚刚和邻居发生了一场可怕的争吵，他咽不下这口气，于是决定佚名发给他的邻居一封脏话连篇的信。他有无限张完全相同的已经打印好的纸张，都包含 $N$ 个字母。他有一把举世无双的剪刀，可以从某张纸中通过一刀剪出连续的一段（也可以通过一刀获得整个字符串）。他想知道获得这封 $M$ 个字母的长信最少需要剪多少刀。保证这总是可能的。
## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..?: N letters laid out on several input lines; this is the text of the one copy of the Moo York Times. Each line will have no more than 80 characters.

\* Lines ?..?: M letters that are the text of FJ's letter. Each line will have no more than 80 characters.

## 输出格式

\* Line 1: The minimum number of cuts FJ has to make to create his message

## 样例

### 样例输入 #1
```
38 9 
THEQUICKBROWNFOXDO 
GJUMPSOVERTHELAZYDOG 
FOXDOG 
DOG 

```
### 样例输出 #1
```
2 

```


---

---
title: "[USACO11JAN] Bottleneck G"
layout: "post"
diff: 省选/NOI-
pid: P3006
tag: ['2011', '线段树', 'USACO', '最短路', '树链剖分']
---
# [USACO11JAN] Bottleneck G
## 题目描述

Farmer John is gathering the cows. His farm contains a network of N (1 <= N <= 100,000) fields conveniently numbered 1..N and connected by N-1 unidirectional paths that eventually lead to field 1. The fields and paths form a tree.

Each field i > 1 has a single one-way, exiting path to field P\_i, and currently contains C\_i cows (1 <= C\_i <= 1,000,000,000). In each time unit, no more than M\_i (0 <= M\_i <= 1,000,000,000) cows can travel from field i to field P\_i (1 <= P\_i <= N) (i.e., only M\_i cows can traverse the path).

Farmer John wants all the cows to congregate in field 1 (which has no limit on the number of cows it may have). Rules are as follows:

\* Time is considered in discrete units.

\* Any given cow might traverse multiple paths in the same time unit. However, no more than M\_i total cows can leave field i (i.e., traverse its exit path) in the same time unit.

\* Cows never move \*away\* from field #1.

In other words, every time step, each cow has the choice either to

a) stay in its current field

b) move through one or more fields toward field #1, as long as the bottleneck constraints for each path are not violated

Farmer John wants to know how many cows can arrive in field 1 by certain times. In particular, he has a list of K (1 <= K <= 10,000) times T\_i (1 <= T\_i <= 1,000,000,000), and he wants to know, for each T\_i in the list, the maximum number of cows that can arrive at field 1 by T\_i if scheduled to optimize this quantity.

Consider an example where the tree is a straight line, and the T\_i list contains only T\_1=5, and cows are distibuted as shown:

```cpp
Locn:      1---2---3---4      <-- Pasture ID numbers 
C_i:       0   1   12  12     <-- Current number of cows 
M_i:           5   8   3      <-- Limits on path traversal; field 1 has no limit since it has no exit 
The solution is as follows; the goal is to move cows to field 1: 
```
Tree:      1---2---3---4
```cpp
t=0        0   1   12  12     <-- Initial state 
t=1        5   4   7   9      <-- field 1 has cows from field 2 and 3 t=2        10  7   2   6 
t=3        15  7   0   3 
t=4        20  5   0   0 
t=5        25  0   0   0 
Thus, the answer is 25: all 25 cows can arrive at field 1 by time t=5. 

## 输入格式

\* Line 1: Two space-separated integers: N and K

\* Lines 2..N: Line i (not i+1) describes field i with three 

space-separated integers: P\_i, C\_i, and M\_i

\* Lines N+1..N+K: Line N+i contains a single integer: T\_i

## 输出格式

\* Lines 1..K: Line i contains a single integer that is the maximum number of cows that can arrive at field 1 by time T\_i.

## 样例

### 样例输入 #1
```
4 1 
1 1 5 
2 12 7 
3 12 3 
5 

```
### 样例输出 #1
```
25 

```
## 题目翻译

WC正在召集奶牛,他的农场有一个包含 ***N*** 块农田的网络，编号为 **1 -- N** ，每个农场里有 $C_i$ 头牛。农场被 **N-1**  条 **单向** 边链接,（每个农场有通向$P_i$的路） 保证从任何点可以到达1号点。WC想让所有奶牛集中到1号农场。 

**时间是离散的** 奶牛可以在1单位时间里走过任意多条道路，但是每条路有一个容纳上限 *$M_i$*  并且奶牛不会离开1号农场(农场没有容量上限) 

### 每一个单位时间，奶牛可以选择如下几种行动 
1. 留在当前的农场
2. 经过几条道路，向1号农场移动（需要满足$M_i$）

WC想要知道有多少牛可以在某个特定的时刻到达1号农场，
他有一张列着 ***K*** 个时间（分别为$T_i$)的单子
，他想知道在每个$T_i$, 采用最优策略在$T_i$结束最多能有多少牛到1号农场

### 数据范围如下：
$1 \le N \le  10^5$

$1 \le C_i \le  10^9$

$0 \le M_i \le 10^9$

$1 \le P_i \le N$

$1 \le K \le 10^4$

$1 \le T_i \le 10^9$


## **输入输出格式**
* 输入格式
 
    *第一行：两个整数 N 和 K
    
    *第2—N行，第i行描述一块农场及它的路 $P_i \;C_i\;M_i$

    *第N+1 - N+K行， 第N+i 一个整数 $T_i$
* 输出格式
    
    *每行一个答案对应$T_i$

感谢@ToBiChi 提供翻译


---

---
title: "[USACO11JAN] Traffic Lights S"
layout: "post"
diff: 省选/NOI-
pid: P3011
tag: ['2011', 'USACO']
---
# [USACO11JAN] Traffic Lights S
## 题目背景

征求翻译。如果你能提供翻译或者题意简述，请直接发讨论，感谢你的贡献。

## 题目描述

Kenosha, the city nearest Farmer John, has M (1 <= M <= 14,000) roads conveniently numbered 1..M that connect N (2 <= N <= 300) junctions which are conveniently numbered 1..N. No two roads connect the same pair of junctions. No road connects a junction to itself. The integer travel time T\_ij (1 <= T\_ij <= 100) between junctions i and j is the same for both directions (i.e., T\_ij = T\_ji).

Each junction has a single traffic light with two colors: blue or purple. The color of each light alternates periodically: blue for certain duration and then purple for another duration.  Traffic is permitted to commence travel down the road between any two junctions, if and only if the lights at both junctions are the same color at the moment of departing from one junction for the other.  The lights do not necessarily have to be the same on the whole trip down the road.

If a vehicle arrives at a junction just at the moment the lights switch it must consider the new colors of lights. Vehicles are allowed to wait at the junctions. You are given the city map which shows:

```cpp
                                    Init  Remg  Blue   Purple
       4       76         Junction  Color Time  Cycle  Cycle
>>[1B]===[2P]======          1        B    2     16      99
    |   /          \         2        P    6     32      13
  40|  /75          \        3        P    2     87       4
    | /              \       4        P   38     96      49
  [3P]===============[4P]>>
           77
```
```cpp
* The travel times T_ij for all roads 
* The durations of the two colors at junction i. (DB_i (1 <= DB_i <= 100) for the blue light and DP_i (1 <= DP_i <= 100) for the purple light) 
* The initial color C_i of the light at junction i (a letter 'B' or 'P' with the obvious meaning) and the remaining time R_i (1 <= R_i <= 100) for this color to change 
Find the minimum time one needs to get from a given source S (1 <= S <= N) to a given destination D (1 <= D <= N; D != S). 
Consider the map below with four junctions and five roads. FJ wants to travel from junction 1 to junction 4. The first light is blue; the rest are purple. 
```
The minimum time is 127 utilizing the path 1-2-4.
Initially, the light at junction 1 is blue. Since the light at junction 2 is purple, vehicle waits at junction 1 for 2 seconds then travels 4 seconds to junction 2.

At time 6, the light at junction 2 switches to blue whereas the light at junction 4 has 32 more seconds to switch to blue. However, after 32 seconds, the light at junction 2 switches to purple and the light at junction 4 switches to blue at the same time. So the vehicle needs to wait 13 seconds more for junction 2 to switch to blue then the lights have the same color and vehicle travels 76 seconds to the destination junction 4.

The total time is 2+4+32+13+76=127 seconds. 

Below is a more graphical presentation of this travel plan:

```cpp
                                                                                                      1    1    1    1    1    1
             1    1    2    2    3    3    4    4    5    5    6    6    7    7    8    8    9    9    0    0    1    1    2    2
   0....5....0....5....0....5....0....5....0....5....0....5....0....5....0....5....0....5....0....5....0....5....0....5....0....5..
   --------------------------------------------------------------------------------------------------------------------------------
J1 BBBPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPBBBBBBBBBBBBBBBBPPPPPPPPPP
J2 PPPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBPPPPPPPPPPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBPPPPPPPPPPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
J3 PPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
J4 PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
FJ 1..>>>2............................................>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>4
```
## 输入格式

\* Line 1: Two space-separated integers: S and D

\* Line 2: Two space-separated integers: N and M

\* Lines 3..N+2: Line i+2 line describes junction i with a character and three integers (all separated by a single space): C\_i, R\_i, DB\_i, and DP\_i

\* Lines N+3..N+M+2: Line N+2+k describes road k with three integers: i, j, and T\_ij

## 输出格式

\* Line 1: One integer: the time taken by a minimum-time path from the source junction to the destination junction. If there is no path, output 0.

## 样例

### 样例输入 #1
```
1 4 
4 5 
B 2 16 99 
P 6 32 13 
P 2 87 4 
P 38 96 49 
1 2 4 
1 3 40 
2 3 75 
2 4 76 
3 4 77 

```
### 样例输出 #1
```
127 

```
## 题目翻译

## **题目描述**

和FJ靠的最近的城市Kenosha市有 $M$条道路。(编号为$1-M$) 连接着$N$个路口 (编号为$1-N$) 。保证没有重边和自环。 

从点$i$到点$j$需要的时间是$T_{ij}$， 且保证$T_{ij}$ = $T_{ji}$

每个路口有一个交通灯，有两种颜色：蓝色和紫色。两个颜色周期性的交替。蓝色持续一定时间，然后紫色持续一定时间。
想要从$i$到$j$只有在$i$和$j$的信号灯颜色相同的时候才可以走(从T1离开i走向j，只需T1时刻i与j的颜色相同即可，无其他任何约束。)

如果在变幻灯的那一秒到$j$，考虑的是变幻后的颜色。
给你所有第$i$个路口的蓝色灯持续时间$DB_i$和紫色灯持续时间$DP_i$
和每个路口刚开始灯的颜色$C_i$,剩余持续时间$R_i$
求一个给定的原点$S$到给定目标点$D$的最小时间。

## 输入输出格式
###   输入格式
 * 第一行两个整数 S和D
 * 第二行两个整数 N和M
 * 第三至N+2行。第i+2行描述点i的信号灯情况 $C_i$,   $R_i$,  $DB_i$,   $DP_i$
 * 第三道N+M+2行：第N+2+k行描述第k条道路 : $i$, $j$, $T_{ij}$
###   输出格式
 * 一个整数代表从S到D最少消耗的时间， 如果S、D不连通，输出0

感谢@ToBiChi 提供翻译


---

---
title: "[USACO11OPEN] Soldering G"
layout: "post"
diff: 省选/NOI-
pid: P3023
tag: ['动态规划 DP', '动态规划 DP', '2011', 'USACO', '斜率优化', '斜率优化', '树形 DP', '树形 DP']
---
# [USACO11OPEN] Soldering G
## 题目描述

The cows are playing with wires! They have learned a technique called soldering, in which they connect two pieces of wire together by attaching the endpoint of one wire to a location along the length of the other. (Soldering endpoint to endpoint is not allowed.) There can be multiple solder junctions at the same point.

The cows have a plan for an Amazing Structure they would like to build. It is in the form of a graph with N (1 <= N <= 50,000) nodes and N-1 edges of unit length so that each pair of nodes is connected. Each edge is described by a pair of integers, A and B (1 <= A <= N; 1 <= B <= N; A != B).

The cows are able to buy wire from a local store; however longer wire is more expensive. In particular the cows can buy a wire of length L with cost L\*L, but they cannot cut wires or join wires together.

Given the plan, the cows would like solder wires together to build their Amazing Structure. Please help them find the minimum possible cost!

Test data worth at least 50% of the points will have N <= 2,000.

Partial feedback will be provided on your first 50 submissions to this problem.

TIME LIMIT: 2 seconds

MEMORY LIMIT: 64 MB

奶牛决定用电线焊接出一个特殊图形，这个图形是连通的，由N个点，N -1条边组成， 每条边的长度都是1。焊接所用的电线要从当地的商店里买。越长的电线越贵，一条长度为 L的电线售价为L^2 。 奶牛们已经学会了基本的焊接方法， 她们会把某条电线的一个端点焊接到另一条电线的 中间某个位置， 但她们没有学会如何把两条电线的端点直接焊接起来， 也没有学会怎么把电 线剪断。 告诉你奶牛准备焊接的图形，请告诉奶牛怎么焊接才能最节约材料费用。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N: Two space-separated integers describing an edge: A and B

## 输出格式

\* Line 1: A single integer, the cost of soldering the tree together. Note that this number may not always fit in a 32-bit integer.

## 样例

### 样例输入 #1
```
6 
1 2 
1 3 
1 4 
1 5 
1 6 

```
### 样例输出 #1
```
7 

```
## 提示

Since all nodes in the structure are connected to node 1, we only need to buy one wire of length 2 and three of length 1, for a total cost of 2 \* 2 + 1 \* 1 + 1 \* 1 + 1 \* 1 = 7.



---

---
title: "[USACO11DEC] Simplifying the Farm G"
layout: "post"
diff: 省选/NOI-
pid: P3037
tag: ['2011', 'USACO']
---
# [USACO11DEC] Simplifying the Farm G
## 题目描述

Farmer John has been taking an evening algorithms course at his local university, and he has just learned about minimum spanning trees.  However, Farmer John now realizes that the design of his farm is not as efficient as it could be, and he wants to simplify the layout of his farm.

The farm is currently arranged like a graph, with vertices representing fields and edges representing pathways between these fields, each having an associated length.  Farmer John notes that for each distinct length, at most three pathways on his farm share this length.  FJ would like to remove some of the pathways on his farm so that it becomes a tree -- that is, so that there is one unique route between any pair of fields.  Moreover, Farmer John would like this to be a minimum spanning tree -- a tree having the smallest possible sum of edge lengths.

Help Farmer John compute not only the sum of edge lengths in a minimum spanning tree derived from his farm graph, but also the number of different possible minimum spanning trees he can create.

农夫约翰在一所夜校学习算法课程，他刚刚学会了最小生成树。现在约翰意识到他的农场设计得不够高效，他想简化农场的布局。


约翰的农场可以看做一个图，农田代表图中顶点，田间小路代表图中的边，每条边有一定的长度。约翰注意到，农场中最多有三条小路有着相同的长度。约翰想删除一些小路使得农场成为一棵树，使得两块农田间只有一条路径。但是约翰想把农场设计成最小生成树，也就是农场道路的总长度最短。


请帮助约翰找出最小生成树的总长度，同时请计算出总共有多少种最小生成树？

## 输入格式

\* Line 1: Two integers N and M (1 <= N <= 40,000; 1 <= M <= 100,000), representing  the number of vertices and edges in the farm graph, respectively.  Vertices are numbered as 1..N.

\* Lines 2..M+1: Three integers a\_i, b\_i and n\_i (1 <= a\_i, b\_i <= N; 1 <= n\_i <= 1,000,000)  representing an edge from vertex a\_i to b\_i with length n\_i.  No edge length n\_i will occur more than three times.

## 输出格式

\* Line 1: Two integers representing the length of the minimal spanning tree and the number of minimal spanning trees (mod

1,000,000,007).

## 样例

### 样例输入 #1
```
4 5 
1 2 1 
3 4 1 
1 3 2 
1 4 2 
2 3 2 

```
### 样例输出 #1
```
4 3 

```
## 提示

Picking both edges with length 1 and any edge with length 2 yields a minimum spanning tree of length 4.




---

---
title: "[USACO12JAN] Delivery Route S"
layout: "post"
diff: 省选/NOI-
pid: P3039
tag: ['2012', 'USACO']
---
# [USACO12JAN] Delivery Route S
## 题目描述

After several years of record milk production, Farmer John now operates an entire network of N farms (1 <= N <= 100).  Farm i is located at position (x\_i, y\_i) in the 2D plane, distinct from all other farms, with both x\_i and y\_i being integers.

FJ needs your help planning his daily delivery route to bring supplies to the N farms.  Starting from farm 1, he plans to visit the farms sequentially (farm 1, then farm 2, then farm 3, etc.), finally returning to farm 1 after visiting farm N.  It tames FJ one minute to make a single step either north, south, east, or west.  Furthermore, FJ wants to visit each farm exactly once during his entire journey (except farm 1, which he visits twice of course).

Please help FJ determine the minimum amount of time it will take him to complete his entire delivery route.


FJ有N (1 <= N <= 100)个农场，每个农场具有独立的整数坐标(x\_i, y\_i)。他需要一个物资配送路线，从第1个农场出发，依次经过农场1，农场2，农场3…，最后从农场N回到农场1.


FJ每次只能朝东南西北四个方向行走，每行走一个单位长度需要1分钟，除了农场1，其他农场能且仅能到达一次。


请计算FJ的最小时间花费。

## 输入格式

\* Line 1: The number of farms, N.

\* Lines 2..1+N: Line i+1 contains two space-separated integers, x\_i and y\_i  (1 <= x\_i, y\_i <= 1,000,000).

## 输出格式

\* Line 1: The minimum number of minutes FJ needs to complete his delivery route, or -1 if it is impossible to find a feasible delivery route that visits every farm exactly once (except farm 1).

## 样例

### 样例输入 #1
```
4 
2 2 
2 4 
2 1 
1 3 

```
### 样例输出 #1
```
12 

```
## 提示

FJ can complete his delivery route in 12 minutes: 2 minutes to go from farm 1 to farm 2, 5 minutes to go from farm 2 to farm 3 (circumventing farm 1), 3 minutes to go from farm 3 to farm 4, and then 2 minutes to return to farm 1.



---

---
title: "[USACO12JAN] Video Game G"
layout: "post"
diff: 省选/NOI-
pid: P3041
tag: ['动态规划 DP', '2012', 'USACO', 'O2优化', 'AC 自动机']
---
# [USACO12JAN] Video Game G
## 题目描述

Bessie 在玩一款游戏，该游戏只有三个技能键 `A`，`B`，`C` 可用，但这些键可用形成 $n$ 种特定的组合技。第 $i$ 个组合技用一个字符串 $s_i$ 表示。

Bessie 会输入一个长度为 $k$ 的字符串 $t$，而一个组合技每在 $t$ 中出现一次，Bessie 就会获得一分。$s_i$ 在 $t$ 中出现一次指的是 $s_i$ 是 $t$ 从某个位置起的连续子串。如果 $s_i$ 从 $t$ 的多个位置起都是连续子串，那么算作 $s_i$ 出现了多次。

若 Bessie 输入了恰好 $k$ 个字符，则她最多能获得多少分？
## 输入格式

输入的第一行是两个整数，分别表示组合技个数 $n$ 和 Bessie 输入的字符数 $k$。

接下来 $n$ 行，每行一个字符串 $s_i$，表示一种组合技。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3 7 
ABA 
CB 
ABACB 

```
### 样例输出 #1
```
4 

```
## 提示

#### 样例 1 解释

Bessie 如果输入 `ABACBCB`，则 `ABA` 出现了一次，`ABACB` 出现了一次，`CB` 出现了两次，共得到 $4$ 分。可以证明这是最优的输入。

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 20$，$1 \leq k \leq 10^3$。
- $1 \leq |s_i| \leq 15$。其中 $|s_i|$ 表示字符串 $s_i$ 的长度。
- $s$ 中只含大写字母 `A`，`B`，`C`。


---

---
title: "[USACO12JAN] Cow Run G"
layout: "post"
diff: 省选/NOI-
pid: P3042
tag: ['贪心', '2012', 'USACO', '连通块', '队列']
---
# [USACO12JAN] Cow Run G
## 题目描述

Farmer John and Bessie have devised a new exercise game for the cows.  The cows are running on a circular track of length M (2 <= M <= 1,000,000,000) starting from the same position.  The game proceeds in N (1 <= N <= 14) rounds using a deck of 8N cards each with a number X\_i (0 <= X\_i < M) written on it.

Each round FJ moves the top 8 cards into a separate pile and selects either the top 4 or bottom 4 cards for Bessie to play with.  Bessie then chooses either the top 2 cards or bottom 2 cards of the 4 cards FJ selected.  After this FJ calls out the number on the top card, X\_top, and the cows run a distance of R \* X\_top, where R is the total distance the cows have run so far.  Bessie then calls out the number on the bottom card, X\_bottom, and the cows run a distance of X\_bottom.

FJ is concerned that after the exercise the cows will be too tired to get back to the beginning of the track if they end up too far away.  He believes if the cows end up more than a distance of K (0 <= K <= floor(M/2)) from their starting position they won't be able to get back home.

It is guaranteed that if FJ plays correctly, he will always be able to ensure the cows can come home, irrespective of the moves made by Bessie! For each round, your task is to determine which half of the cards FJ should choose such that no matter what Bessie does from that point on, FJ can always get the cows home.  Bessie will then make the move provided in the input and you can then continue onto the next round.  Note that even though Bessie's moves are provided to you in the input, you are to specify moves for FJ that would have worked no matter what Bessie chooses (so it is effectively as if FJ does not really know what Bessie will do during her moves).

## 输入格式

\* Line 1: Three space-separated integers N, M, K

\* Line 2: A string N characters.  If the ith character is 'T' it means Bessie will select the top 2 cards in the ith round.  Otherwise the ith character will be 'B' to indicate Bessie will select the bottom 2 cards in the ith round.

\* Lines 3..2+N: Each line contains eight integers representing the 8 cards to be used that round from top to bottom.

## 输出格式

\* Line 1: A string of N characters where the ith character is 'T' if FJ should choose the top 4 cards or 'B' if FJ should choose the bottom 4 cards in the ith round.  If there are multiple ways to get the cows home, choose the lexicographically first (that is, the string that is alphabetically smallest).

## 样例

### 样例输入 #1
```
2 2 0 
TT 
1 0 0 0 0 0 0 1 
0 1 1 1 0 0 1 0 

```
### 样例输出 #1
```
TB 

```
## 提示

The cows must end up exactly where they started to be able to come home. Note that FJ is not aware of what choices Bessie is going to make beforehand.  If FJ did know, he could have chosen the bottom half each time.

## 题目翻译

FJ 和贝茜为奶牛们设计了一个新的跑步游戏。跑道是环行的，长度为 $(2 \le M \le 1,000,000,000)$ 的环行，奶牛们在相同的起跑位置。这个游戏一共要进行 $N\ (1 \le N \le 14)$ 轮，通过一副 $8N$ 张的纸牌来控制每一轮的跑步距离，每张纸牌都有一个数字 $X_i\ (0 \le X_i<M)$。

每一轮，FJ 取出最上面的 $8$ 张纸牌，然后再取出这 $8$ 张的上面或者底下的 $4$ 张。接着，贝茜从这 $4$ 张牌中取出上面或者底下的 $2$ 张，上面一张的数字为 $X_{\mathrm{top}}$，下面一张的数字是 $X_{\mathrm{bottom}}$，则牛先跑 $R\times X_{\mathrm{top}}$ 的距离（$R$ 表示奶牛们已经跑过的距离），再跑 $X_{\mathrm{bottom}}$ 的距离。

FJ 担心奶牛们太累而回不到起点，游戏结束时，若奶牛们离开起点距离超过 $K\ (0 \le K \le \lfloor M/2\rfloor)$，则他们就回不了起点了。

问题保证，当 FJ 选择正确的取牌策略，不论贝西如何取牌，奶牛们都能够回到起点。对于每一轮，你的任务是决定取哪 $4$ 张纸牌。在输入数据中，贝西的每次选择都是已知的，但 FJ 的每次取牌时，贝西接着的选择应该被假定为是未知的，即不论贝西怎么选，FJ 的选择都是能保证奶牛们能够回到起点。


---

---
title: "[USACO12MAR] Large Banner G"
layout: "post"
diff: 省选/NOI-
pid: P3050
tag: ['2012', 'USACO']
---
# [USACO12MAR] Large Banner G
## 题目描述

Bessie is returning from a long trip abroad to the Isle of Guernsey, and Farmer John wants to mount a nice "Welcome Home" banner for her arrival. Farmer John's field has integer dimensions M x N (1 <= M, N <= 100,000), and he has installed a post at every possible point in the field with integer coordinates (if we assign a coordinate system to the field so that (0,0) is in the lower-left corner and (M,N) is in the upper-right corner). Of these (M+1) \* (N+1) points, Farmer John must pick two as the endpoints of the banner.

 
Farmer John, being the perfectionist that he is, insists that the banner must be completely straight.  This means that, for the two posts he chooses, there cannot be any other post on the line segment that the banner will form between them.  Additionally, Farmer John wants the banner to have length at least L and at most H (1 <= L <= H <= 150,000).  Farmer John needs your help to figure out how many possible ways he can hang the banner. The banner is reversible, so switching the two endpoints of the banner counts as the same way to hang the banner. As this number may be very large, Farmer John simply wants to know what it is modulo B (1 <= B <= 1,000,000,000).

Consider the example below, with M = 2 and N = 2: 

\* \* \*
\* \* \*
\* \* \*
Farmer John wants the length of the banner to be between 1 and 3 inclusive. Any choice of posts satisfies this length requirement, but note that eight pairs cannot be picked:

(0, 0) and (2, 0): (1, 0) is on the line segment between them

(0, 1) and (2, 1): (1, 1) is on the line segment between them

(0, 2) and (2, 2): (1, 2) is on the line segment between them

(0, 0) and (2, 2): (1, 1) is on the line segment between them

(0, 0) and (0, 2): (0, 1) is on the line segment between them

(1, 0) and (1, 2): (1, 1) is on the line segment between them

(2, 0) and (2, 2): (2, 1) is on the line segment between them

(0, 2) and (2, 0): (1, 1) is on the line segment between them

Therefore, there are a total of (9 choose 2) - 8 = 28 possible locations.

给出n,m,l,h，问有多少点A(ax,ay),B(bx,by)满足：ax,bx∈[0,n], ay,by∈[0,m]，l<=AB<=h，且线段AB上除A,B外无整点。

## 输入格式

\* Line 1: Five space-separated integers: M, N, L, H and B.

## 输出格式

\* Line 1: One integer denoting the number of possible banners (modulo B).

## 样例

### 样例输入 #1
```
2 2 1 3 100 

```
### 样例输出 #1
```
28 

```


---

---
title: "[USACO12NOV] Concurrently Balanced Strings G"
layout: "post"
diff: 省选/NOI-
pid: P3059
tag: ['2012', 'USACO']
---
# [USACO12NOV] Concurrently Balanced Strings G
## 题目描述

Farmer John's cows are all of a very peculiar breed known for its distinctive appearance -- each cow is marked with a giant spot on its hide in the shape of a parenthesis (depending on the direction the cow is facing, this could look like either a left or a right parenthesis).

One morning, Farmer John arranges his cows into K lines each of N cows (1 <= K <= 10, 1 <= N <= 50,000).  The cows are facing rather arbitrary directions, so this lineup can be described by K length-N strings of parentheses S\_1,..., S\_k.  Farmer John notes with great excitement that some ranges of his cows are "concurrently balanced", where a range i...j of cows is concurrently balanced only if each of the strings S\_1,..., S\_k is balanced in that range (we define what it means for a single string of parentheses to be balanced below). For instance, if K = 3, and we have

S\_1 = )()((())))(()) 

S\_2 = ()(()()()((()) 

S\_3 = )))(()()))(()) 

1111
01234567890123

Then the range [3...8] is concurrently balanced because S\_1[3...8] = ((())), S\_2[3...8] = ()()(), and S\_3[3...8] = (()()). The ranges [10...13] and [11...12] are also concurrently balanced.

Given K length-N strings of parentheses, help Farmer John count the number of pairs (i,j) such that the range i...j is concurrently balanced.

There are several ways to define what it means for a single string of parentheses to be "balanced".  Perhaps the simplest definition is that there must be the same total number of ('s and )'s, and for any prefix of the string, there must be at least as many ('s as )'s.  For example, the following strings are all balanced:

() 
(()) 
()(()()) 

while these are not:

)( 
())( 
((()))) 

给出k个长度为n的括号序列，问有多少个区间在k个序列中对应的子串均平衡。

## 输入格式

\* Line 1: Two integers, K and N.

\* Lines 2..K+1: Each line contains a length-N string of parentheses.

## 输出格式

\* Line 1: A single integer, the number of concurrently balanced ranges.

## 样例

### 样例输入 #1
```
3 14 
)()((())))(()) 
()(()()()((()) 
)))(()()))(()) 

```
### 样例输出 #1
```
3 

```


---

---
title: "[USACO12NOV] Balanced Trees G"
layout: "post"
diff: 省选/NOI-
pid: P3060
tag: ['2012', 'USACO', '点分治']
---
# [USACO12NOV] Balanced Trees G
## 题目描述

Fascinated by his experience with balanced parentheses so far, Farmer John is curious if you can help him solve one final problem.  As it turns out, FJ's farm is in the shape of a giant tree of N pastures (1 <= N <= 40,000), each of which he has labeled with either ( or ).  For example:

'('--'('--')'--'('--')' 

|         |

')'       ')'--'('--'(' 

|              |

')'            '('--')'--')'--')'--'(' 

Recall that since his farm is a tree, this means that certain pairs of pastures are connected by corridors so that there is one unique path between any given pair of pastures.  FJ believes that some of these paths represent balanced strings of parentheses.  In particular, he would like to know, among all such balanced strings represented by paths through the tree, what is the maximum nesting depth one can find.  The nesting depth of a balanced string of parentheses is the maximum, over all prefixes of the string, of the excess number of ('s within the prefix.  For example, the string ()()() has nesting depth 1, but the string ((()))() has nesting depth 3, as we can see clearly if we count excess ('s for every prefix of the string: 

((()))() 

12321010

For the example farm above, the deepest string is ((())) with a depth of 3, and can be obtained by taking the path from A to B below:

```cpp
'('--'('--')'--'('--')' 
|         | 
')'       ')'--'('--'(' < A 
|              | 
')'            '('--')'--')'--')'--'(' 
^C                            ^B 
```
Note that this is different than the longest balanced string; for instance (())(()), starting at A and ending at C, has length 8.

Your task is to output the nesting depth of the deepest balanced path in the tree.

给出一棵树，每个结点上有一个括号。问在所有括号平衡的路径中，最大嵌套层数为多少。

## 输入格式

\* Line 1: A single integer N, the number of nodes in the tree.

\* Lines 2..N: Line i+1: A single integer p\_(i+1) (1 <= p\_(i+1) <= i), denoting an edge between nodes i+1 and p\_{i+1} in the tree.

\* Lines N+1..2N: Line N+i: Either ( or ), the label of node i.

## 输出格式

\* Line 1: A single integer, giving the maximum nesting depth of a balanced path.

## 样例

### 样例输入 #1
```
15 
1 
2 
1 
4 
4 
6 
7 
5 
9 
9 
11 
12 
13 
14 
( 
) 
) 
( 
) 
) 
( 
) 
( 
( 
( 
) 
) 
) 
( 

```
### 样例输出 #1
```
3 

```
## 提示

This is the example from the problem description, with the following node labels:

1'('--4'('--6')'--7'('--8')' 

|     |

2')'  5')'--9'('--10'(' 

|           |

3')'       11'('--12')'--13')'--14')'--15'(' 




---

---
title: "[USACO12DEC] Crazy Fences S"
layout: "post"
diff: 省选/NOI-
pid: P3061
tag: ['计算几何', '2012', 'USACO']
---
# [USACO12DEC] Crazy Fences S
## 题目描述

After visiting a modern art museum, Farmer John decides to re-design his farm by moving all of the N (1 <= N <= 1000) fences between his pastures! Each fence is describe by a line segment in the 2D plane.  If two fences meet, they do so only at their endpoints.  Each fence touches exactly two other fences, one at both endpoints.

FJ has C cows (1 <= C <= 1000) on his farm.  Each cow resides at a point in the 2D plane that is not on any fence, and no two cows reside at the same point.  Two cows are said to be in the same community if one could walk to the other without touching any fences.  Please help FJ determine the size of the largest community.

 
在访问了一个现代美术馆后，约翰农夫决定移动n个在他的牧场之间的栅栏来


重新设计他的农场。每个栅栏用一个2D平面的线段来描述。两个栅栏只有在他们的端点才会相遇。每个栅栏在两个端点接触其他的两个栅栏。


约翰农夫有c头牛在他的农场。每头牛住在2D平面的不在任何栅栏的一个点，并且没有两头牛在同一个点。如果两头牛可以不接触任何栅栏地走到一起，他们就是在同一个社区。请确定最大的社区的牛的数量。

## 输入格式

\* Line 1: Two space-separated integers N and C.

\* Lines 2..1+N: Each line contains four integers: x1, y1, x2, y2, indicating a fence from point (x1,y1) to point (x2,y2).  All coordinates are integers in the range 0..1,000,000.

\* Lines 2+N..1+N+C: Each line contains two integers x and y describing the location of a cow.  All coordinates are integers in the range 0..1,000,000.

## 输出格式

\* Line 1: The number of cows in the largest community.

## 样例

### 样例输入 #1
```
10 4 
0 0 10 0 
10 0 10 10 
0 0 0 10 
10 10 0 10 
8 8 9 8 
9 8 8 9 
8 9 8 8 
2 7 3 2 
3 2 7 5 
7 5 2 7 
15 3 
1 4 
4 5 
7 1 

```
### 样例输出 #1
```
2 

```
## 提示

There are 10 fences and 4 cows.  The fences form a square containing two triangles.


Cows #2 and #4 belong to the same community.  Cows #1 and #3 are each members of a community of size 1.


感谢@kczno1 提供翻译



---

---
title: "[USACO13JAN] Seating G"
layout: "post"
diff: 省选/NOI-
pid: P3071
tag: ['2013', 'USACO', '单调队列', '离散化', '队列']
---
# [USACO13JAN] Seating G
## 题目描述

To earn some extra money, the cows have opened a restaurant in their barn specializing in milkshakes.  The restaurant has N seats (1 <= N <= 500,000) in a row. Initially, they are all empty.

Throughout the day, there are M different events that happen in sequence at the restaurant (1 <= M <= 300,000).  The two types of events that can happen are:

1. A party of size p arrives (1 <= p <= N). Bessie wants to seat the party in a contiguous block of p empty seats. If this is possible, she does so in the lowest position possible in the list of seats.  If it is impossible, the party is turned away.

2. A range [a,b] is given (1 <= a <= b <= N), and everybody in that range of seats leaves.

Please help Bessie count the total number of parties that are turned away over the course of the day.

有一排n个座位，m次操作。A操作：将a名客人安置到最左的连续a个空位中，没有则不操作。L操作：[a,b]的客人离开。

求A操作的失败次数。

## 输入格式

\* Line 1: Two space-separated integers, N and M.

\* Lines 2..M+1: Each line describes a single event.  It is either a line of the form "A p" (meaning a party of size p arrives) or "L a b" (meaning that all cows in the range [a, b] leave).

## 输出格式

\* Line 1: The number of parties that are turned away.

## 样例

### 样例输入 #1
```
10 4 
A 6 
L 2 4 
A 5 
A 2 

```
### 样例输出 #1
```
1 

```
## 提示

There are 10 seats, and 4 events.  First, a party of 6 cows arrives.  Then all cows in seats 2..4 depart.  Next, a party of 5 arrives, followed by a party of 2.


Party #3 is turned away.  All other parties are seated.



---

---
title: "[USACO13OPEN] Photo G"
layout: "post"
diff: 省选/NOI-
pid: P3084
tag: ['2013', '线段树', 'USACO', '单调队列', '差分约束', '队列']
---
# [USACO13OPEN] Photo G
## 题目描述

Farmer John has decided to assemble a panoramic photo of a lineup of his N cows (1 <= N <= 200,000), which, as always, are conveniently numbered from 1..N.  Accordingly, he snapped M (1 <= M <= 100,000) photos, each covering a contiguous range of cows: photo i contains cows a\_i through b\_i inclusive.  The photos collectively may not necessarily cover every single cow.

After taking his photos, FJ notices a very interesting phenomenon: each photo he took contains exactly one cow with spots!  FJ was aware that he had some number of spotted cows in his herd, but he had never actually counted them.  Based on his photos, please determine the maximum possible number of spotted cows that could exist in his herd.  Output -1 if there is no possible assignment of spots to cows consistent with FJ's photographic results.

农夫约翰决定给站在一条线上的N(1 <= N <= 200,000)头奶牛制作一张全家福照片，N头奶牛编号1到N。


于是约翰拍摄了M(1 <= M <= 100,000)张照片，每张照片都覆盖了连续一段奶牛：第i张照片中包含了编号a\_i 到 b\_i的奶牛。但是这些照片不一定把每一只奶牛都拍了进去。


在拍完照片后，约翰发现了一个有趣的事情：每张照片中都**有且仅有**一只身上带有斑点的奶牛。约翰意识到他的牛群中有一些斑点奶牛，但他从来没有统计过它们的数量。 根据照片，请你帮约翰估算在他的牛群中最多可能有多少只斑点奶牛。如果无解，输出“-1”。


Input
## 输入格式

\* Line 1: Two integers N and M.

\* Lines 2..M+1: Line i+1 contains a\_i and b\_i.

## 输出格式

\* Line 1: The maximum possible number of spotted cows on FJ's farm, or -1 if there is no possible solution.

## 样例

### 样例输入 #1
```
5 3 
1 4 
2 5 
3 4 

```
### 样例输出 #1
```
1 

```
## 提示

There are 5 cows and 3 photos.  The first photo contains cows 1 through 4, etc.


From the last photo, we know that either cow 3 or cow 4 must be spotted. By choosing either of these, we satisfy the first two photos as well.



---

---
title: "[USACO13OPEN] Yin and Yang G"
layout: "post"
diff: 省选/NOI-
pid: P3085
tag: ['模拟', '2013', 'USACO', '分治']
---
# [USACO13OPEN] Yin and Yang G
## 题目描述

Farmer John is planning his morning walk on the farm. The farm is structured like a tree: it has N barns (1 <= N <= 100,000) which are connected by N-1 edges such that he can reach any barn from any other. Farmer John wants to choose a path which starts and ends at two different barns, such that he does not traverse any edge twice. He worries that his path might be a little long, so he also wants to choose another "rest stop" barn located on this path (which is distinct from the start or the end).

Along each edge is a herd of cows, either of the Charcolais (white hair) or the Angus (black hair) variety. Being the wise man that he is, Farmer John wants to balance the forces of yin and yang that weigh upon his walk. To do so, he wishes to choose a path such that he will pass by an equal number of Charcolais herds and Angus herds-- both on the way from the start to his rest stop, and on the way from the rest stop to the end.

Farmer John is curious how many different paths he can choose that are "balanced" as described above.  Two paths are different only if they consist of different sets of edges; a path should be counted only once even if there are multiple valid "rest stop" locations along the path that make it balanced.

Please help determine the number of paths Farmer John can choose!

给出一棵n个点的树，每条边为黑色或白色。问满足以下条件的路径条数：路径上存在一个不是端点的点，使得两端点到该点的路径上两种颜色的边数都相等。

## 输入格式

\* Line 1: The integer N.

\* Lines 2..N: Three integers a\_i, b\_i and t\_i, representing the two barns that edge i connects. t\_i is 0 if the herd along that edge is Charcolais, and 1 if the  herd is Angus.

## 输出格式

\* Line 1: One integer, representing the number of possible paths Farmer John can choose from.

## 样例

### 样例输入 #1
```
7 
1 2 0 
3 1 1 
2 4 0 
5 2 0 
6 3 1 
5 7 1 

```
### 样例输出 #1
```
1 

```
## 提示

There are 7 barns and 6 edges. The edges from 1 to 2, 2 to 4 and 2 to 5 have Charcolais herds along them.


No path of length 2 can have a suitable rest stop on it, so we can only consider paths of length 4. The only path that has a suitable rest stop is 3-1-2-5-7, with a rest stop at 2.



---

---
title: "[USACO13OPEN] Figure Eight G"
layout: "post"
diff: 省选/NOI-
pid: P3086
tag: ['2013', 'USACO', '枚举']
---
# [USACO13OPEN] Figure Eight G
## 题目描述

Farmer John's cows recently received a large piece of marble, which, unfortunately, has a number of imperfections.  To describe these, we can represent the piece of marble by an N by N square grid (5 <= N <= 300), where the character '\*' represents an imperfection and '.' represents a flawless section of the marble.

The cows want to carve a number "8" in this piece of marble (cows are quite fond of the number "8" since they have cloven hooves on each of their four feet, so they can effectively count up to 8 using their "toes"). However, the cows need your help to determine the optimally placed figure eight in the piece of marble.  Here are a few properties that define a valid figure eight:

\* A figure eight consists of two rectangles, a top and a bottom. \* Both the top and bottom have at least one cell in their interior. \* The bottom edge of the top rectangle is a (not necessarily proper) subset of the top edge of the bottom rectangle.

\* The figure eight can only be carved from flawless regions of the piece of marble.

The aesthetic score of a figure eight is equal to the product of the areas enclosed by its two rectangles.  The cows wish to maximize this score.

```cpp
............... 
............... 
...*******..... 
.*....*.......* 
.*......*....*. 
....*.......... 
...*...****.... 
............... 
..**.*..*..*... 
...*...**.*.... 
*..*...*....... 
............... 
.....*..*...... 
.........*..... 
............... 
```
For example, given this piece of marble 

the optimally placed eight is:

```cpp
..88888888888.. 
..8.........8.. 
..8*******..8.. 
.*8...*.....8.* 
.*8.....*...8*. 
..8.*.......8.. 
..8*...****.8.. 
.88888888888888 
.8**.*..*..*..8 
.8.*...**.*...8 
*8.*...*......8 
.8............8 
.8...*..*.....8 
.8.......*....8 
.88888888888888 
```
The top rectangle has area 6x9=54, and the bottom rectangle has area 12x6=72.  Thus, its aesthetic score is 54x72=3888.

农民约翰的奶牛最近收到了一大块大理石，不幸的是，它有许多缺陷.。为了描述这些，我们可以用n个正方形网格来表示一块大理石（5 < n = n = 300），其中字符“\*”表示一个不完美和“。


母牛想雕刻一个号码“8”在这一块大理石（牛很喜欢数字“8”，因为他们对他们的每一个四英尺，有偶蹄有效地数到8，用“脚”）。然而，奶牛需要你的帮助，以确定最佳放置在图八块大理石。这里有一些属性定义一个有效的数字八：


图八包括两个矩形，一个顶部和一个底部。顶部和底部至少有一个单元在其内部。顶部矩形的底部边缘是底部矩形顶部边缘的一个（不一定是适当的）子集.。


图八只能刻在大理石的无瑕疵区域。


图八的美学得分等于其两个矩形所包围的区域的乘积.。奶牛希望最大限度地提高这一成绩。

## 输入格式

\* Line 1: A single integer N, indicating the side length of the marble.

\* Lines 2..N+1: Each line describes a row of the marble, and contains N characters which are each either '\*' (an imperfection) or '.' (a flawless section).

第1行：一个整数n，表示大理石的边长。


行2 N + 1：每行描述了一排大理石，并包含n个字符，每个都是“\*”（缺陷）或'.' (完整)。

## 输出格式

\* Line 1: The highest aesthetic score of any figure eight which doesn't use any imperfect squares of the marble.  If no figure eight is attainable, then output -1.

## 样例

### 样例输入 #1
```
15 
............... 
............... 
...*******..... 
.*....*.......* 
.*......*....*. 
....*.......... 
...*...****.... 
............... 
..**.*..*..*... 
...*...**.*.... 
*..*...*....... 
............... 
.....*..*...... 
.........*..... 
............... 

```
### 样例输出 #1
```
3888 

```
## 提示

顶部的矩形面积6X9 = 54，和底部矩形面积12x6 = 72。因此，它的审美评分54x72 = 3888。


给出一个n×n的区域，其中有一些位置有瑕疵。现在要在没有瑕疵的位置中雕一个8”出来。


“8”字的定义为两个矩形框，框内面积均大于0，且一个矩形框的底边是是另一个矩形框的顶边的子集。


最大化两矩形框内面积的积。


感谢 @3505515693qq 提供翻译



---

---
title: "[USACO13NOV] Line of Sight G"
layout: "post"
diff: 省选/NOI-
pid: P3091
tag: ['2013', 'USACO']
---
# [USACO13NOV] Line of Sight G
## 题目描述

Farmer John's N cows (1 <= N <= 50,000) are located at distinct points in his two-dimensional pasture.  In the middle of the pasture is a large circular grain silo.  Cows on opposite sides of the silo cannot see each-other, since the silo blocks their view.  Please determine the number of pairs of cows that can see each-other via a direct line of sight.

The grain silo is centered at the origin (0,0) and has radius R.  No cow is located on or inside the circle corresponding to the silo, and no two cows lie on a tangent line to the silo.  The value of R is in the range 1..1,000,000, and each cow lives at a point with integer coordinates in the range -1,000,000..+1,000,000.

给定平面上的 $N$ 个点，求有多少点对能互相看见而不被以原点为圆心，$R$ 为半径的圆挡住。

题目保证不存在圆上或圆内的点，也不存在连接两点的线段为圆的切线。

$1\le N\le50000$

$1\le R\le10^6$ 

$|x|,|y|\le10^6$
## 输入格式

\* Line 1: Two integers: N and R.

\* Lines 2..1+N: Each line contains two integers specifying the (x,y) coordinates of a cow.

## 输出格式

\* Line 1: The number of pairs of cows who can see each-other.

## 样例

### 样例输入 #1
```
4 5 
0 10 
0 -10 
10 0 
-10 0 

```
### 样例输出 #1
```
4 

```
## 提示

There are 4 cows at positions (0,10), (0,-10), (10,0), and (-10,0).  The silo is centered at (0,0) and has radius 5.


All 6 pairs of cows can see each-other, except for the pairs situated on opposite sides of the silo: the cows at (-10,0) and (10,0) cannot see each-other, and the cows at (0,-10) and (0,10) cannot see each-other.



---

---
title: "[USACO13DEC] The Bessie Shuffle G"
layout: "post"
diff: 省选/NOI-
pid: P3098
tag: ['2013', 'USACO', '并查集', '广度优先搜索 BFS', '图论建模']
---
# [USACO13DEC] The Bessie Shuffle G
## 题目描述

Bessie is practicing her card tricks.  She has already mastered the Bessie- shuffle -- a shuffle on M (2 <= M <= 100,000) cards that reorganizes the cards so the i-th card from the top is now the P[i]-th card from the top.

Now Bessie is practicing shuffles on larger decks.  She has a deck of N cards (M <= N <= 1,000,000,000) conveniently labeled 1 to N.  She shuffles this deck by taking the first M cards and performing the Bessie-shuffle on them, placing the shuffled cards back on top of the deck.  She then removes the top card from the deck and places it face down.  She repeats this process, placing the top cards successively on top of each other, until she is out of cards.  When Bessie has less than M cards left, she no longer performs the Bessie-shuffle, but continues to place the top card on top of the others.

Bessie knows that the deck initially started in sorted order, with 1 on top, 2 next, and N on the bottom.  Given the description of the Bessie-shuffle, help Bessie compute which cards end up located at Q different specified positions (1 <= Q <= N, Q <= 5,000) in the deck.

50% of test cases will have N <= 100,000. 

贝西有一种独门的洗牌方法，称为 A 类洗牌法；

A 类洗牌法的具体过程：将一堆共 $M$（$2 \le M \le 10 ^ 5$）张从上到下编号 $1, 2, \cdots, M$ 的纸牌，从上到下第 $i$ 张牌洗到位置 $p _ i$。

例如，$M=3，p = \{3, 1, 2\}$，则执行一次 A 类洗牌法后，从上到下将变为 $2, 3, 1$，即牌 $1$ 放到位置 $3$，牌 $2$ 放到位置 $1$，牌 $3$ 放到位置 $2$。


贝西现在要练习另外一种洗牌方法，称为 B 类洗牌法。


B 类洗牌法的具体过程： 

有一堆 $N$（$M \le N \le 10 ^ 9$）张编号为 $1, 2, \cdots, N$ 的牌，并按从上到下 $1$ 到 $N$ 的顺序堆放。另有一个牌堆用来辅助洗牌，称为临时堆，开始时为空。

1. 将最上面 $M$ 张牌进行一次 A 类洗牌法；
2. 将最上面的一张牌放到临时堆的最上方；
3. 重复前两个操作，直到原先的堆没有牌为止。


以上过程中，当原先堆的牌不足 $M$ 张的时候，将不进行 A 类洗牌法，而是将最上面的牌依次放到临时堆上。


给定 $N, M$ 和排列 $p$。现在有 $Q$（$1 \le Q \le \min(N, 5000)$）个询问，请求出对其做一次 B 类洗牌法后临时堆中 $q _ i$ 位置上的牌的编号。

$50\%$ 的数据中，$N \le 10 ^ 5$。

## 输入格式

\* Line 1: A single line containing N, M and Q separated by a space.

\* Lines 2..1+M: Line i+1 indicates the position from the top, P[i], of the i-th card in the Bessie-shuffle (1 <= P[i] <= M).

\* Lines 2+M..1+M+Q: Line i+1+M contains a single integer q\_i

describing the i-th query.  You are to compute the label on the card located in position q\_i from the top (1 <= q\_i <= N).

## 输出格式

\* Lines 1..Q: On the i-th line, print a single integer indicating the card at position q\_i from the top.

## 样例

### 样例输入 #1
```
5 3 5 
3 
1 
2 
1 
2 
3 
4 
5 

```
### 样例输出 #1
```
4 
5 
3 
1 
2 

```
## 提示

Bessie has a deck of 5 cards initially ordered as [1, 2, 3, 4, 5].  Her shuffle is on 3 cards and has the effect of moving the top card to the bottom.  There are 5 queries querying each position in the deck.


The shuffle proceeds as:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (put 2 face down) 
[3, 1, 4, 5] -> [1, 4, 3, 5] (put 1 face down) 
[4, 3, 5] -> [3, 5, 4] (put 3 face down) 
[5, 4] (put 5 face down) 
[4] (put 4 face down) 
```
This produces the final order of [4, 5, 3, 1, 2]

贝西的五张牌刚开始顺序为 [1, 2, 3, 4, 5]。她一次洗三张牌，效果是将第一张牌放到底部。以上五个问题询问了每一张牌的位置。


洗牌的顺序是:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (将2正面向下放置)
[3, 1, 4, 5] -> [1, 4, 3, 5] (将1正面向下放置) 
[4, 3, 5] -> [3, 5, 4] (将3正面向下放置) 
[5, 4] (将5正面向下放置) 
[4] (将4正面向下放置) 
```
这就形成了最终的顺序：[4, 5, 3, 1, 2]



---

---
title: "[USACO14FEB] Airplane Boarding G"
layout: "post"
diff: 省选/NOI-
pid: P3103
tag: ['2014', 'USACO', '平衡树']
---
# [USACO14FEB] Airplane Boarding G
## 题目描述

FJ's cows have decided to take a vacation, and have miraculously managed to find an airline willing to sell them tickets.  When they arrive at the airport and start boarding their plane, they face an interesting problem, however.

The airplane has N seats, which we model as the points x=1 through x=N on the number line.  All N cows (1 <= N <= 200,000) are standing in line waiting to get to their seats.  Cow N is at position x=0, Cow N-1 is at position x=-1, and so on.  Cow i has been assigned to Seat S\_i, where S\_1,...,S\_N is a permutation of 1,...,N.

At each time step, each cow takes a step to the right if she can. When cow i reaches her seat S\_i, she will stop to put her baggage in the overhead bin, which takes T\_i seconds, and then sit down. For those T\_i steps, the cow behind her (if there is one) is blocked from moving forward.  If there is a line of cows behind her, the line is effectively blocked as well.

How long will it take for all the cows to sit down? 

The sum of T\_i for all cows will be less than 1,000,000,000. 

想象一下飞机有N个座位，N个座位相当于数轴上的1至N共N个整点，第1个座位在整点1处，第2个座位在整点2处，……第N个座位在整点N处。


有N个奶牛排好队，要登陆坐飞机，第N头奶牛在数轴的整点0处，第N−1头奶牛在数轴的整点−1处，……第1头奶牛在数轴的整点−N+1处。第i头奶牛的座位号是Si。注意：每头奶牛都有唯一的一个座位，不会出现多头奶牛有相同的座位号。


在每一秒钟，奶牛会向右移动一步到达下一个整点，前提是没有奶牛挡住它。 当第i头奶牛到达它的座位Si时，它需要花费Ti秒去把行李放到头顶的行李架上，然后坐到自己的位置上，在此过程中，由于飞机通道很窄，所以在第i头奶牛坐到自己座位之前，在它左边的所有奶牛都不能动，要等奶牛i放好行李坐好后才能动。


现在的问题是，至少要多少秒之后，所有的奶牛都能做到自己的座位上？

## 输入格式

\* Line 1: A single integer, N.

\* Lines 2..N+1: Two space-separated integers, S\_i and T\_i.

## 输出格式

\* Line 1: A single line indicating the amount of time it takes to seat all cows.

## 样例

### 样例输入 #1
```
3 
2 5 
3 10 
1 5 

```
### 样例输出 #1
```
19 

```
## 提示

Initially, the cows are situated like this:

cows -> 123

123 <- seats 

with cow 1 trying to get to seat 2, cow 2 trying to get to seat 3, and cow 3 trying to get to seat 1.


After one step, they will all move 1 to the right and cow 3 will reach her seat:

123
123
Cow 3 takes 5 seconds to sit down, at which point she effectively disappears.

12
123
It takes 3 more seconds for cows 1 and 2 to reach their desired seats:

12
123
It takes 5 seconds for cow 1 to sit down and 10 seconds for cow 2 to sit down, so that's 10 seconds total.

In total this took 1 + 5 + 3 + 10 = 19 seconds. 




---

---
title: "[USACO14OPEN] Cow Optics G"
layout: "post"
diff: 省选/NOI-
pid: P3108
tag: ['贪心', '2014', '线段树', 'USACO', '前缀和']
---
# [USACO14OPEN] Cow Optics G
## 题目背景

征求翻译。如果你能提供翻译或者题意简述，请直接发讨论，感谢你的贡献。

## 题目描述

Farmer John's cows would like to host a dance party in their barn, complete with a laser light show.  Unfortunately, the only working laser they have found is located far away from the barn and too heavy to move, so they plan to re-direct the laser light to the barn using a series of mirrors.

The layout of the farm has the laser at position (0,0) pointing north (in the positive y direction), and the barn at (Bx, By); we can think of both the laser and the barn as points in the 2D plane.  There are already N cows (1 <= N <= 100,000) scattered throughout the farm holding mirrors that are aligned at angles of 45 degrees to the axes.  For example, a mirror aligned like \ will take a beam of light entering from below and reflect it to the left.  We can also think of the mirrors as being located at points in the 2D plane.

Just before pressing the big red button to activate the laser, Bessie noticed a major flaw in the plan: the laser cannot hit the barn with the mirrors in their current configuration!  As a result, she plans to run out onto the field, and hold up one more mirror (placed once again at a 45 degree angle) in order to redirect the laser onto the barn. Please count the number of locations in the field where Bessie can stand to accomplish this goal.

All coordinates are integers between -1,000,000,000 and 1,000,000,000. It is guaranteed that any mirrors to be placed will be in this range as well. The cows running the laser insist that the beam should never come back to (0,0) after leaving this location (and with the mirrors in their initial configuration, it is guaranteed that this will not happen).  No two cows occupy the same point in space, and Bessie cannot locate herself at the same position as an existing cow.

农场主约翰的牛想在谷仓里面举办舞会，用激光灯来表演。但不幸的是唯一的激光灯离谷仓太远，并且搬不动，所以牛们想用镜子来反射激光，使得激光照到谷仓。


激光的位置在（0,0），指向为北方（即y轴正方向），谷仓在位置（Bx，By）。已经有N头奶牛拿着镜子分散在农场的各个位置（1 <= N <= 100,000），镜子与原点之间的夹角为45度。例如一个这样（“\“）的镜子可以把从下方射来的光线反射成向左的光线。


Bessie在启动激光的前一刻意识到计划有缺陷，所以她自己又拿着一面镜子出去了，恰好使得激光照到谷仓。


请计算Bessie可能站在的位置的总数。


坐标范围：-1,000,000,000 到 1,000,000,000，数据保证初始时激光光束不会反射回（0,0）位置。同一点上不可能有多头牛，Bessie不能站在其他牛的位置。

## 输入格式

\* Line 1: The integers N, Bx, and By.

\* Lines 2..N + 1: Line i+1 describes the ith mirror with 3 elements: its (x,y) location, and its orientation (either '\' or '/').

第一行：三个整数：N，Bx，By。


第2~N+1行：每行两个整数表示牛的位置，一个字符（”/“或"\"）表示镜子怎么放置的。

## 输出格式

where Bessie can stand to redirect the laser to the barn.

Bessie所有可能站在的位置总数。

## 样例

### 样例输入 #1
```
4 1 2 
-2 1 \ 
2 1 / 
2 2 \ 
-2 2 / 

```
### 样例输出 #1
```
2 

```
## 提示

A mirror at (0,1) or (0,2) placed in either direction would do the trick.

样例中Bessie可能站在（0,1）或者（0,2）。

感谢@SystemLLH  提供翻译



---

---
title: "[USACO15FEB] Censoring G"
layout: "post"
diff: 省选/NOI-
pid: P3121
tag: ['2015', 'USACO', '哈希 hashing', '栈', 'AC 自动机']
---
# [USACO15FEB] Censoring G
## 题目描述

FJ 把杂志上所有的文章摘抄了下来并把它变成了一个长度不超过 $10^5$ 的字符串 $s$。他有一个包含 $n$ 个单词的列表，列表里的 $n$ 个单词记为 $t_1 \cdots t_n$。他希望从 $s$ 中删除这些单词。

FJ 每次在 $s$ 中找到最早出现的列表中的单词（最早出现指该单词的开始位置最小），然后从 $s$ 中删除这个单词。他重复这个操作直到 $s$ 中没有列表里的单词为止。注意删除一个单词后可能会导致 $s$ 中出现另一个列表中的单词。

FJ 注意到列表中的单词不会出现一个单词是另一个单词子串的情况，这意味着每个列表中的单词在 $s$ 中出现的开始位置是互不相同的。

请帮助 FJ 完成这些操作并输出最后的 $s$。
## 输入格式

第一行是一个字符串，表示文章 $s$。

第二行有一个整数，表示单词列表的单词个数 $n$。

第 $3$ 到第 $(n + 2)$ 行，每行一个字符串，第 $(i + 2)$ 行的字符串 $t_i$ 表示第 $i$ 个单词。
## 输出格式

输出一行一个字符串，表示操作结束后的 $s$。
## 样例

### 样例输入 #1
```
begintheescapexecutionatthebreakofdawn 
2 
escape 
execution 

```
### 样例输出 #1
```
beginthatthebreakofdawn 

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq |s|, \sum\limits_{i = 1}^n |t_i|, n \leq 10^5$。
- 字符串均只含小写字母。
- 操作结束后 $s$ 不会被删成空串。
- 对于所有的 $i \neq j$，$t_i$ 不是 $t_j$ 的子串。

其中对于一个字符串 $x$，约定 $|x|$ 表示 $x$ 的长度。

---

#### 提示

操作过程中 $s$ 有可能某一个前缀子串被完全删除，请格外注意这一点。



---

---
title: "[USACO15FEB] Fencing the Herd G"
layout: "post"
diff: 省选/NOI-
pid: P3122
tag: ['计算几何', '2015', 'USACO', 'cdq 分治', '凸包']
---
# [USACO15FEB] Fencing the Herd G
## 题目描述

Farmer John 需要你帮助他决定在哪里建造形状是一条无限长的直线的栅栏来限制他的牛的活动。他选出了几个可能的建造栅栏的位置，你需要帮助他判断哪些栅栏是有用的。一个栅栏是有用的当且仅当所有奶牛都在栅栏的同一侧。（如果有牛群在栅栏所在的直线上，那么栅栏是没用的），Farmer John 将会多次询问你一个栅栏是否有用，如果这个栅栏是有用的，需要输出 `YES`，反之输出 `NO`。

另外，Farmer John 也可能会带来一些新的奶牛加入这个牛群。一头牛加入之后，以后的所有询问中，这头牛也需要与其它的牛在栅栏的同一侧。

## 输入格式


第一行，两个正整数 $n,q$，表示初始时牛群的数量与询问个数；

后 $n$ 行，每行两个整数 $x,y$，表示一个牛群的初始位置；

后 $q$ 行，每行多个整数，表示一次询问，询问的格式如下：

- 1 $x$ $y$：表示一个新的牛群加入了牧场，驻留在 $(x,y)$ 上；
- 2 $A$ $B$ $C$：表示 Farmer John 询问栅栏 $Ax+By=C$ 是否有用。
## 输出格式

对于每个 $2$ 类型的询问，如果栅栏有用，输出 `YES`，否则输出 `NO`。

## 样例

### 样例输入 #1
```
3 4 
0 0 
0 1 
1 0 
2 2 2 3 
1 1 1 
2 2 2 3 
2 0 1 1 

```
### 样例输出 #1
```
YES 
NO 
NO 


```
## 提示

直线 $2x+2y=3$ 使得初始的三个牛群都在同侧；然而在该栅栏另一侧的牛群 $(1,1)$ 的加入使得它没有用了。

直线 $y=1$ 没用因为牛群 $(0,1)$，$(1,1)$ 恰好在它上面。

---

对于 $100\%$ 的数据，保证 $1\leq n\leq 10^5$，$1\leq q\leq 10^5$，所有牛群的坐标都各不相同且满足 $-10^9\leq x,y\leq 10^9$，$-10^9\leq A,B\leq 10^9$，$-10^{18}\leq C\leq 10^{18}$。

数据保证不存在栅栏满足 $A=B=0$。


---

---
title: "[USACO17JAN] Subsequence Reversal P"
layout: "post"
diff: 省选/NOI-
pid: P3607
tag: ['动态规划 DP', '2017', 'USACO', '枚举']
---
# [USACO17JAN] Subsequence Reversal P
## 题目描述

Farmer John is arranging his $N$ cows in a line to take a photo ($1 \leq N \leq 50$). The height of the $i$th cow in sequence is $a(i)$, and Farmer John thinks it would make for an aesthetically pleasing photo if the cow lineup has a large increasing subsequence of cows by height.

To recall, a subsequence is a subset $a(i_1), a(i_2), \ldots, a(i_k)$ of elements from the cow sequence, found at some series of indices $i_1 < i_2 < \ldots < i_k$. We say the subsequence is increasing if $a(i_1) \leq a(i_2) \leq \ldots \leq a(i_k)$.

FJ would like there to be a long increasing subsequence within his ordering of the cows. In order to ensure this, he allows himself initially to choose any subsequence and reverse its elements.

For example, if we had the list

```
1 6 2 3 4 3 5 3 4
```

We can reverse the chosen elements

```
1 6 2 3 4 3 5 3 4
  ^         ^ ^ ^
```
to get

```
1 4 2 3 4 3 3 5 6
  ^         ^ ^ ^
```
Observe how the subsequence being reversed ends up using the same indices as it initially occupied, leaving the other elements unchanged.

Please find the maximum possible length of an increasing subsequence, given that you can choose to reverse an arbitrary subsequence once.
## 输入格式

The first line of input contains $N$. The remaining $N$ lines contain $a(1) \ldots a(N)$, each an integer in the range $1 \ldots 50$.
## 输出格式

Output the number of elements that can possibly form a longest increasing subsequence after reversing the contents of at most one subsequence.
## 样例

### 样例输入 #1
```
9
1
2
3
9
5
6
8
7
4
```
### 样例输出 #1
```
9

```
## 题目翻译

### 题目描述

Farmer John 正在将他的 $N$ 头奶牛排成一列拍照（$1 \leq N \leq 50$）。序列中第 $i$ 头奶牛的高度为 $a(i)$，Farmer John 认为如果奶牛队列中存在一个较长的按高度递增的子序列，那么这张照片会更具美感。

回顾一下，子序列是指从奶牛序列中选出的一组元素 $a(i_1), a(i_2), \ldots, a(i_k)$，这些元素位于一系列索引 $i_1 < i_2 < \ldots < i_k$ 处。如果满足 $a(i_1) \leq a(i_2) \leq \ldots \leq a(i_k)$，则称该子序列是递增的。

FJ 希望在他的奶牛排列中存在一个较长的递增子序列。为了确保这一点，他允许自己最初选择任意一个子序列并将其元素反转。

例如，如果我们有以下序列：

```
1 6 2 3 4 3 5 3 4
```

我们可以反转选中的元素：

```
1 6 2 3 4 3 5 3 4
  ^         ^ ^ ^
```

得到：

```
1 4 2 3 4 3 3 5 6
  ^         ^ ^ ^
```

注意被反转的子序列最终仍然使用最初占据的索引，而其他元素保持不变。

请找出在最多反转一个子序列的情况下，可能的最长递增子序列的长度。

### 输入格式

输入的第一行包含 $N$。接下来的 $N$ 行包含 $a(1) \ldots a(N)$，每个数均为 $1$ 到 $50$ 之间的整数。

### 输出格式

输出在最多反转一个子序列后，可能形成的最长递增子序列的元素个数。


---

---
title: "[USACO17FEB] Why Did the Cow Cross the Road II P"
layout: "post"
diff: 省选/NOI-
pid: P3657
tag: ['2017', 'USACO', '树状数组', '离散化', '枚举']
---
# [USACO17FEB] Why Did the Cow Cross the Road II P
## 题目背景

*本题与 [金组同名题目](/problem/P6119) 在题意上一致，唯一的差别是数据范围。*
## 题目描述

Farmer John 饲养了 $N$ 种奶牛，编号从 $1$ 到 $N$。一些品种的奶牛和其他奶牛间相处良好，事实证明，如果两个品种的奶牛编号分别为 $a,b$，当 $|a-b| \leq 4$ 时，这两个品种的奶牛能友好相处，否则不能友好相处。

一条长长的道路贯穿整个农场，道路的左侧有 $N$ 个牧场（每个品种的奶牛恰好占据一个牧场），道路的右侧也有 $N$ 个牧场（每个品种的奶牛恰好占据一个牧场）。为了让奶牛们安全穿过马路，Farmer John 希望能在马路上画出一些人行道（牛行道？），要求这些人行道满足如下条件：

1. 人行道从左侧的某个牧场出发，连接到右侧的某个牧场；
2. 人行道连接的两个牧场的奶牛要能友好相处；
3. 人行道不能在道路中间相交；
4. 每个牧场只能与一条人行道相连。

你需要帮 FJ 求出最多能有多少条人行道。
## 输入格式

输入第一行一个整数 $N$（$1 \leq N \leq 10^5$）。

接下来 $N$ 行，每行一个整数 $a_i$，代表道路左侧第 $i$ 个牧场的奶牛品种编号。

接下来 $N$ 行，每行一个整数 $b_i$，代表道路右侧第 $i$ 个牧场的奶牛品种编号。
## 输出格式

输出最多能画多少条人行道。
## 样例

### 样例输入 #1
```
6
1
2
3
4
5
6
6
5
4
3
2
1
```
### 样例输出 #1
```
5

```


---

---
title: "[USACO17FEB] Why Did the Cow Cross the Road III P"
layout: "post"
diff: 省选/NOI-
pid: P3658
tag: ['2017', 'USACO', '树状数组', 'cdq 分治']
---
# [USACO17FEB] Why Did the Cow Cross the Road III P
## 题目描述

Farmer John is continuing to ponder the issue of cows crossing the road through his farm, introduced in the preceding two problems. He realizes now that the threshold for friendliness is a bit more subtle than he previously considered -- breeds $a$ and $b$ are now friendly if $|a - b| \leq K$, and unfriendly otherwise.
Given the orderings of fields on either side of the road through FJ's farm, please count the number of unfriendly crossing pairs of breeds, where a crossing pair of breeds is defined as in the preceding problems.


## 输入格式

The first line of input contains $N$ ($1 \leq N \leq 100,000$) and $K$ ($0 \leq K < N$). The next $N$ lines describe the order, by breed ID, of fields on one side of the road; each breed ID is an integer in the range $1 \ldots N$. The last $N$ lines describe the order, by breed ID, of the fields on the other side of the road. Each breed ID appears exactly once in each ordering.

## 输出格式

Please output the number of unfriendly crossing pairs of breeds.


## 样例

### 样例输入 #1
```
4 1
4
3
2
1
1
4
2
3
```
### 样例输出 #1
```
2
```
## 提示

In this example, breeds 1 and 4 are unfriendly and crossing, as are breeds 1 and 3.


## 题目翻译

### 题目描述

Farmer John 继续思考奶牛穿过他农场道路的问题，这个问题在前两个问题中已经介绍过。他现在意识到，友好度的阈值比他之前考虑的要微妙一些——现在，品种 $a$ 和 $b$ 是友好的当且仅当 $|a - b| \leq K$，否则就是不友好的。给定 FJ 农场道路两侧田地的品种顺序，请计算不友好的交叉品种对的数量，其中交叉品种对的定义与前两个问题相同。

### 输入格式

输入的第一行包含 $N$ ($1 \leq N \leq 100,000$) 和 $K$ ($0 \leq K < N$)。接下来的 $N$ 行描述了道路一侧田地的品种顺序；每个品种 ID 是一个在 $1 \ldots N$ 范围内的整数。最后的 $N$ 行描述了道路另一侧田地的品种顺序。每个品种 ID 在每个顺序中恰好出现一次。

### 输出格式

请输出不友好的交叉品种对的数量。

### 说明/提示

在这个例子中，品种 1 和 4 是不友好的且交叉的，品种 1 和 3 也是不友好的且交叉的。


---

---
title: "[USACO17OPEN] Switch Grass P"
layout: "post"
diff: 省选/NOI-
pid: P3665
tag: ['2017', '线段树', 'USACO', 'Kruskal 重构树', '生成树']
---
# [USACO17OPEN] Switch Grass P
## 题目描述

Farmer John has recently been experimenting with cultivating different types of grass on his farm, realizing that different types of cows like different types of grass. However, he must be careful to ensure that different types of grass are planted sufficiently far away from each-other, in order to prevent them from being inextricably mixed.


FJ's farm consists of $N$ fields ($1 \leq N \leq 200,000$), where $M$ pairs of  fields are connected by bi-directional pathways ($1 \leq M \leq 200,000$).  Using these pathways, it is possible to walk from any field to any other field. Each pathway has an integer length in the range $1 \ldots 1,000,000$. Any pair of fields will be linked by at most one direct pathway.


In each field, FJ initially plants one of $K$ types of grass ($1 \leq K \leq N$). Over time, however, he might decide to switch the grass in some field to a different type. He calls this an "update"  peration. He might perform several updates over the course of time, which are all cumulative in nature.


After each update, FJ would like to know the length of the shortest path between two fields having different grass types. That is, among all pairs of fields having different grass types, he wants to know which two are closest. Ideally,

this number is large, so he can prevent grass of one type from mixing with grass of another type. It is guaranteed that the farm will always have at least two fields with different grass types.


In 30 percent of the input cases, each field will be directly connected to at most 10 pathways.



## 输入格式

The first line of input contains four integers, $N$, $M$, $K$, and $Q$, where $Q$ is the number of updates ($1 \leq Q \leq 200,000$).

The next $M$ lines describe the paths; each one contains three integers $A$, $B$, and $L$, indicating a path from field $A$ to field $B$ (both integers in the range $1 \ldots N$) of length $L$.

The next line indicates the initial type of grass growing in each field ($N$ integers in the range $1 \ldots K$).

Finally, the last $Q$ lines each describe an update, specified by two integers $A$ and $B$, where the grass in field $A$ is to be updated to type $B$.

## 输出格式

For each update, print the length of the shortest path between two fields with different types of grass, after the update is applied.

## 样例

### 样例输入 #1
```
3 2 3 4
1 2 3
2 3 1
1 1 2
3 3
2 3
1 2
2 2
```
### 样例输出 #1
```
1
3
3
1
```
## 题目翻译

### 题目描述

Farmer John 最近在他的农场尝试种植不同类型的草，发现不同类型的奶牛喜欢不同类型的草。然而，他必须小心确保不同类型的草种植得足够远，以防止它们不可分割地混合在一起。

FJ 的农场由 $N$ 块田地组成（$1 \leq N \leq 200,000$），其中 $M$ 对田地通过双向路径连接（$1 \leq M \leq 200,000$）。使用这些路径，可以从任何田地走到任何其他田地。每条路径的长度是一个在 $1 \ldots 1,000,000$ 范围内的整数。任何一对田地之间最多只有一条直接路径。

在每块田地中，FJ 最初种植了 $K$ 种草中的一种（$1 \leq K \leq N$）。然而，随着时间的推移，他可能会决定将某块田地的草更换为另一种类型。他称这种操作为“更新”操作。他可能会在一段时间内执行多次更新，这些更新都是累积性质的。

每次更新后，FJ 想知道种植不同草类型的两块田地之间的最短路径长度。也就是说，在所有种植不同草类型的田地对中，他希望知道哪两块田地最接近。理想情况下，这个数字应该较大，以便他可以防止一种类型的草与另一种类型的草混合。保证农场中始终至少有两块田地种植不同的草类型。

在 30% 的输入案例中，每块田地最多直接连接 10 条路径。

### 输入格式

输入的第一行包含四个整数 $N$、$M$、$K$ 和 $Q$，其中 $Q$ 是更新的次数（$1 \leq Q \leq 200,000$）。

接下来的 $M$ 行描述路径；每行包含三个整数 $A$、$B$ 和 $L$，表示从田地 $A$ 到田地 $B$（两者都是 $1 \ldots N$ 范围内的整数）的长度为 $L$ 的路径。

接下来的一行表示每块田地最初种植的草类型（$N$ 个 $1 \ldots K$ 范围内的整数）。

最后，最后的 $Q$ 行每行描述一个更新，由两个整数 $A$ 和 $B$ 指定，表示将田地 $A$ 的草更新为类型 $B$。

### 输出格式

对于每次更新，输出更新后种植不同草类型的两块田地之间的最短路径长度。


---

---
title: "[USACO17OPEN] COWBASIC P"
layout: "post"
diff: 省选/NOI-
pid: P3666
tag: ['模拟', '2017', 'USACO', '矩阵乘法', '栈', '构造']
---
# [USACO17OPEN] COWBASIC P
## 题目描述

Bessie has invented a new programming language, but since there is no compiler yet, she needs your help to actually run her programs.


COWBASIC is a simple, elegant language. It has two key features: addition and MOO loops. Bessie has devised a clever solution to overflow: all addition is done modulo $10^9+7$. But Bessie's real achievement is the MOO loop, which runs a block of code a fixed number of times. MOO loops and addition can, of course, be nested.


Given a COWBASIC program, please help Bessie determine what number it returns.

## 输入格式

You are given a COWBASIC program at most 100 lines long, with each line being at most 350 characters long. A COWBASIC program is a list of statements.

There are three types of statements:

```cpp
<variable> = <expression>

<literal> MOO {
<list of statements>
}

RETURN <variable>
```

There are three types of expressions:

```cpp
<literal>

<variable>

( <expression> ) + ( <expression> )
```

A literal is a positive integer at most 100,000.

A variable is a string of at most 10 lowercase English letters.

It is guaranteed that no variable will be used or RETURNed before it is defined. It is guaranteed that RETURN will happen exactly once, on the last line of the program.
## 输出格式

Output a single positive integer, giving the value of the RETURNed variable.

## 样例

### 样例输入 #1
```
x = 1
10 MOO {
x = ( x ) + ( x )
}
RETURN x
```
### 样例输出 #1
```
1024
```
### 样例输入 #2
```
n = 1
nsq = 1
100000 MOO {
100000 MOO {
nsq = ( nsq ) + ( ( n ) + ( ( n ) + ( 1 ) ) )
n = ( n ) + ( 1 )
}
}
RETURN nsq
```
### 样例输出 #2
```
4761
```
## 提示

Scoring

In 20 percent of all test cases - MOO loops are not nested.

In another 20 percent of all test cases - The program only has 1 variable. MOO loops can be nested.

In the remaining test cases, there are no further restrictions.
## 题目翻译

### 题目描述

Bessie 发明了一种新的编程语言，但由于还没有编译器，她需要你的帮助来实际运行她的程序。

COWBASIC 是一种简单而优雅的语言。它有两个关键特性：加法和 MOO 循环。Bessie 设计了一个巧妙的解决方案来处理溢出：所有的加法都是在模 $10^9+7$ 下进行的。但 Bessie 的真正成就是 MOO 循环，它可以固定次数地运行一段代码。当然，MOO 循环和加法可以嵌套。

给定一个 COWBASIC 程序，请帮助 Bessie 确定它返回的数字。

### 输入格式

你将获得一个最多 100 行的 COWBASIC 程序，每行最多 350 个字符。一个 COWBASIC 程序是一个语句列表。

有三种类型的语句：

```cpp
<variable> = <expression>

<literal> MOO {
<list of statements>
}

RETURN <variable>
```

有三种类型的表达式：

```cpp
<literal>

<variable>

( <expression> ) + ( <expression> )
```

字面量是一个最多为 100,000 的正整数。

变量是一个最多由 10 个小写英文字母组成的字符串。

保证在定义之前不会使用或 RETURN 任何变量。保证 RETURN 恰好发生一次，并且在程序的最后一行。

### 输出格式

输出一个正整数，表示 RETURN 的变量的值。

### 说明/提示

评分

在 20% 的测试用例中，MOO 循环不会嵌套。

在另外 20% 的测试用例中，程序只有一个变量。MOO 循环可以嵌套。

在剩余的测试用例中，没有进一步的限制。


---

---
title: "[USACO17DEC] Standing Out from the Herd P"
layout: "post"
diff: 省选/NOI-
pid: P4081
tag: ['字符串', '2017', 'USACO', '后缀自动机 SAM', '后缀数组 SA']
---
# [USACO17DEC] Standing Out from the Herd P
## 题目描述

Just like humans, cows often appreciate feeling they are unique in some way. Since Farmer John's cows all come from the same breed and look quite similar, they want to measure uniqueness in their names.

Each cow's name has some number of substrings. For example, "amy" has substrings {a, m, y, am, my, amy}, and "tommy" would have the following substrings: {t, o, m, y, to, om, mm, my, tom, omm, mmy, tomm, ommy, tommy}.

A cow name has a "uniqueness factor" which is the number of substrings of that name not shared with any other cow. For example, If amy was in a herd by herself, her uniqueness factor would be 6. If tommy was in a herd by himself, his uniqueness factor would be 14. If they were in a herd together, however, amy's uniqueness factor would be 3 and tommy's would be 11.

Given a herd of cows, please determine each cow's uniqueness factor.
## 输入格式

The first line of input will contain $N$ ($1 \le N \le 10^5$). The following $N$ lines will each contain the name of a cow in the herd. Each name will contain only lowercase characters a-z. The total length of all names will not exceed $10^5$.

## 输出格式

Output $N$ numbers, one per line, describing the uniqueness factor of each cow.

## 样例

### 样例输入 #1
```
3
amy
tommy
bessie
```
### 样例输出 #1
```
3
11
19
```
## 题目翻译

### 题目描述

就像人类一样，奶牛也常常希望在某些方面感到自己与众不同。由于 Farmer John 的奶牛都来自同一品种且外观非常相似，它们希望通过名字来衡量独特性。

每头奶牛的名字都有一些子字符串。例如，"amy" 的子字符串为 {a, m, y, am, my, amy}，而 "tommy" 的子字符串为 {t, o, m, y, to, om, mm, my, tom, omm, mmy, tomm, ommy, tommy}。

一头奶牛的名字有一个“独特性因子”，即该名字中不与任何其他奶牛共享的子字符串的数量。例如，如果 amy 独自在一个牛群中，她的独特性因子为 6。如果 tommy 独自在一个牛群中，他的独特性因子为 14。然而，如果它们在一个牛群中，amy 的独特性因子为 3，而 tommy 的独特性因子为 11。

给定一个牛群，请计算每头奶牛的独特性因子。

### 输入格式

输入的第一行包含 $N$（$1 \le N \le 10^5$）。接下来的 $N$ 行每行包含牛群中一头奶牛的名字。每个名字仅包含小写字母 a-z。所有名字的总长度不超过 $10^5$。

### 输出格式

输出 $N$ 个数字，每行一个，表示每头奶牛的独特性因子。


---

---
title: "[USACO17DEC] A Pie for a Pie G"
layout: "post"
diff: 省选/NOI-
pid: P4083
tag: ['2017', '二分', 'USACO', '并查集', '图论建模', '最短路']
---
# [USACO17DEC] A Pie for a Pie G
## 题目描述

Bessie and Elsie have each baked $N$ pies ($1 \leq N \leq 10^5$). Each of the $2N$ pies has a tastiness value according to Bessie and a (possibly different) tastiness value according to Elsie.

Bessie is thinking about giving one of her pies to Elsie. If Elsie receives a pie from Bessie, she will feel obligated to give one of her pies to Bessie. So as to not appear stingy nor flamboyant, Elsie will try to pick a pie that is at least as tasty (in Elsie's eyes) as the pie she received, but no more than $D$ units tastier ($0 \leq D \leq 10^9$). Such a pie may not exist, in which case Elsie will adopt a pseudonym and exile herself to Japan.


But if Elsie does give Bessie a pie in return, Bessie will similarly try to give Elsie a pie which is at least as tasty but no more than $D$ units tastier (in Bessie's eyes) as the pie Elsie just gave her. Should this be impossible, Bessie too will exile herself. Otherwise she will give her chosen pie to Elsie. This cycle will continue until one of the cows is exiled, an unhappy outcome, or one of the cows receives a pie which she accords a tastiness value of $0$, in which case the gift exchange will end and both cows will be happy.


Note that a pie may not be gifted twice, nor can either cow return a pie gifted to her.


For each of the $N$ pies Bessie could select as her initial gift to Elsie, determine the minimum number of pies that could possibly be gifted in the resulting exchange before the cows are happy.

## 输入格式

The first line contains the two integers $N$ and $D$.

The next $2N$ lines contain two space-separated integers each, respectively denoting the value of a particular pie according to Bessie, and the value of that pie according to Elsie.


The first $N$ lines refer to Bessie's pies, and the remaining $N$ lines refer to Elsie's pies.


It is guaranteed that all tastiness values are in the range $[0,10^9]$.

## 输出格式

There should be $N$ lines in the output. Line $i$ should contain a single integer: the minimum number of pies that could be gifted in a happy gift exchange started with Bessie's pie $i$. If no gift exchange starting with pie $i$ is happy, then line $i$ should contain the single integer $-1$ instead.

## 样例

### 样例输入 #1
```
2 1
1 1
5 0
4 2
1 4
```
### 样例输出 #1
```
3
1

```
## 题目翻译

### 题目描述

Bessie 和 Elsie 各自烤了 $N$ 个派（$1 \leq N \leq 10^5$）。这 $2N$ 个派中的每一个都有一个由 Bessie 评定的美味值和一个（可能不同的）由 Elsie 评定的美味值。

Bessie 正在考虑将她的一只派送给 Elsie。如果 Elsie 收到了 Bessie 的派，她会觉得有义务回赠 Bessie 一只派。为了既不显得吝啬也不显得炫耀，Elsie 会尝试选择一只在她看来至少与收到的派一样美味，但不超过 $D$ 单位更美味的派（$0 \leq D \leq 10^9$）。如果这样的派不存在，Elsie 将采用一个化名并自我流放到日本。

但如果 Elsie 确实回赠了 Bessie 一只派，Bessie 也会类似地尝试送给 Elsie 一只在她看来至少与 Elsie 刚送给她的派一样美味，但不超过 $D$ 单位更美味的派。如果这不可能，Bessie 也会自我流放。否则，她会将她选择的派送给 Elsie。这个循环将继续，直到其中一头奶牛被流放（一个不愉快的结果），或者其中一头奶牛收到一只她评定美味值为 $0$ 的派，在这种情况下，礼物交换将结束，两头奶牛都会感到高兴。

请注意，一只派不能被赠送两次，任何一头奶牛也不能回赠她收到的派。

对于 Bessie 可以选择作为初始礼物送给 Elsie 的每一只派，确定在奶牛们感到高兴之前，可能被赠送的派的最小数量。

### 输入格式

第一行包含两个整数 $N$ 和 $D$。

接下来的 $2N$ 行每行包含两个用空格分隔的整数，分别表示某只派由 Bessie 评定的美味值和由 Elsie 评定的美味值。

前 $N$ 行描述 Bessie 的派，剩下的 $N$ 行描述 Elsie 的派。

保证所有美味值都在 $[0,10^9]$ 范围内。

### 输出格式

输出应包含 $N$ 行。第 $i$ 行应包含一个整数：如果以 Bessie 的第 $i$ 只派开始的礼物交换是高兴的，则输出可能被赠送的派的最小数量；否则输出 $-1$。


---

---
title: "[USACO18FEB] Slingshot P"
layout: "post"
diff: 省选/NOI-
pid: P4088
tag: ['2018', '线段树', 'USACO', '枚举', '树套树']
---
# [USACO18FEB] Slingshot P
## 题目描述

One of the farming chores Farmer John dislikes the most is hauling around lots of cow manure. In order to streamline this process, he comes up with an intriguing idea: instead of hauling manure between two points in a cart behind his tractor, why not shoot it through the air with a giant manure slingshot? (indeed, what could possibly go wrong...)
Farmer John's farm is built along a single long straight road, so any location on his farm can be described simply using its position along this road (effectively a point on the number line). FJ builds $N$ slingshots ($1 \leq N \leq 10^5$), where the $i$th slingshot is described by three integers $x_i$, $y_i$, and $t_i$, specifying that this slingshot can shoot manure from position $x_i$ to position $y_i$ in only $t_i$ total units of time.

FJ has $M$ piles of manure to transport ($1 \leq M \leq 10^5$). The $j$th such pile needs to be moved from position $a_j$ to position $b_j$. Hauling manure with the tractor for a distance of $d$ takes $d$ units of time. FJ is hoping to reduce this by allowing up to one use of any slingshot for transporting each pile of manure. Time FJ spends moving his tractor without manure in it does not count.

For each of the $M$ manure piles, please help FJ determine the minimum possible transportation time, given that FJ can use up to one slingshot during the process.
## 输入格式

The first line of input contains $N$ and $M$. The next $N$ lines each describe a single slingshot in terms of integers $x_i$, $y_i$, and $t_i$ ($0 \leq x_i, y_i, t_i \leq 10^9$). The final $M$ lines describe piles of manure that need to be moved, in terms of integers $a_j$ and $b_j$.
## 输出格式

Print $M$ lines of output, one for each manure pile, indicating the minimum time needed to transport it.
## 样例

### 样例输入 #1
```
2 3
0 10 1
13 8 2
1 12
5 2
20 7
```
### 样例输出 #1
```
4
3
10
```
## 提示

Here, the first pile of manure needs to move from position 1 to position 12. Without using an slingshot, this would take 11 units of time. However, using the first slingshot, it takes 1 unit of time to move to position 0 (the slingshot source), 1 unit of time to fling the manure through the air to land at position 10 (the slingshot destination), and then 2 units of time to move the manure to position 12. The second pile of manure is best moved without any slingshot, and the third pile of manure should be moved using the second slingshot.

Problem credits: Brian Dean
## 题目翻译

### 题目描述

Farmer John 最不喜欢的农活之一就是到处搬运牛粪。为了简化这一过程，他想出了一个有趣的主意：与其用拖拉机后面的拖车搬运牛粪，为什么不通过一个巨大的牛粪弹弓将其射到空中呢？（确实，可能会出什么问题呢……）

Farmer John 的农场建在一条笔直的长路上，因此农场上的任何位置都可以简单地用其在这条路上的位置来描述（实际上就是数轴上的一个点）。FJ 建造了 $N$ 个弹弓（$1 \leq N \leq 10^5$），其中第 $i$ 个弹弓由三个整数 $x_i$、$y_i$ 和 $t_i$ 描述，表示这个弹弓可以将牛粪从位置 $x_i$ 射到位置 $y_i$，仅需 $t_i$ 个单位时间。

FJ 有 $M$ 堆牛粪需要搬运（$1 \leq M \leq 10^5$）。第 $j$ 堆牛粪需要从位置 $a_j$ 搬运到位置 $b_j$。用拖拉机搬运牛粪，每移动距离 $d$ 需要 $d$ 个单位时间。FJ 希望通过允许每堆牛粪最多使用一次弹弓来减少搬运时间。FJ 在没有牛粪的情况下移动拖拉机的时间不计入搬运时间。

对于每堆牛粪，请帮助 FJ 确定在最多使用一次弹弓的情况下，搬运所需的最少时间。

### 输入格式

输入的第一行包含 $N$ 和 $M$。接下来的 $N$ 行每行描述一个弹弓，包含三个整数 $x_i$、$y_i$ 和 $t_i$（$0 \leq x_i, y_i, t_i \leq 10^9$）。最后的 $M$ 行描述需要搬运的牛粪堆，每行包含两个整数 $a_j$ 和 $b_j$。

### 输出格式

输出 $M$ 行，每行对应一堆牛粪，表示搬运所需的最少时间。

### 提示

在这里，第一堆牛粪需要从位置 $1$ 搬运到位置 $12$。如果不使用弹弓，这将花费 $11$ 个单位时间。然而，使用第一个弹弓，花费 $1$ 个单位时间将牛粪移动到位置 $0$（弹弓的起点），$1$ 个单位时间将牛粪射到位置 $10$（弹弓的终点），然后花费 $2$ 个单位时间将牛粪移动到位置 $12$。第二堆牛粪最好不使用弹弓搬运，而第三堆牛粪应使用第二个弹弓搬运。

题目来源：Brian Dean


---

---
title: "[USACO18JAN] Lifeguards P"
layout: "post"
diff: 省选/NOI-
pid: P4182
tag: ['动态规划 DP', '2018', 'USACO', '单调队列', '枚举', '队列']
---
# [USACO18JAN] Lifeguards P
## 题目描述

Farmer John has opened a swimming pool for his cows, figuring it will help them relax and produce more milk.

To ensure safety, he hires $N$ cows as lifeguards, each of which has a shift that covers some contiguous interval of time during the day. For simplicity, the pool is open from time $0$ until time $10^9$ on a daily basis, so each shift can be described by two integers, giving the time at which a cow starts and ends her shift. For example, a lifeguard starting at time $t = 4$ and ending at time $t = 7$ covers three units of time (note that the endpoints are "points" in time).


Unfortunately, Farmer John hired $K$ more lifeguards than he has the funds to support. Given that he must fire exactly $K$ lifeguards, what is the maximum amount of time that can still be covered by the shifts of the remaining lifeguards? An interval of time is covered if at least one lifeguard is present.

## 输入格式

The first line of input contains $N$ and $K$ ($K \leq N \leq 100,000, 1 \leq K \leq 100$). Each of the next $N$ lines describes a lifeguard in terms of two integers in the range $0 \ldots 10^9$, giving the starting and ending point of a lifeguard's shift. All such endpoints are distinct. Shifts of different lifeguards might overlap.

## 输出格式

Please write a single number, giving the maximum amount of time that can still be covered if Farmer John fires $K$ lifeguards.

## 样例

### 样例输入 #1
```
3 2
1 8
7 15
2 14
```
### 样例输出 #1
```
12

```
## 提示

In this example, FJ should fire the lifeguards covering $1 \ldots 8$ and $7 \ldots 15$.


## 题目翻译

### 题目描述

Farmer John 为他的奶牛们开设了一个游泳池，认为这将帮助它们放松并产更多的奶。

为了确保安全，他雇佣了 $N$ 头奶牛作为救生员，每头奶牛的班次覆盖一天中的某个连续时间段。为简单起见，游泳池每天从时间 $0$ 开放到时间 $10^9$，因此每个班次可以用两个整数描述，分别表示奶牛开始和结束其班次的时间。例如，一头救生员从时间 $t = 4$ 开始到时间 $t = 7$ 结束，覆盖了 $3$ 个单位的时间（注意端点表示时间点）。

不幸的是，Farmer John 多雇佣了 $K$ 名救生员，超出了他的资金支持范围。鉴于他必须解雇恰好 $K$ 名救生员，剩下的救生员的班次能够覆盖的最长时间是多少？如果至少有一名救生员在场，则某个时间段被视为被覆盖。

### 输入格式

输入的第一行包含 $N$ 和 $K$（$K \leq N \leq 100,000$，$1 \leq K \leq 100$）。接下来的 $N$ 行每行描述一名救生员，用两个范围在 $0 \ldots 10^9$ 的整数表示该救生员班次的开始和结束时间。所有端点都是唯一的。不同救生员的班次可能会重叠。

### 输出格式

请输出一个数字，表示如果 Farmer John 解雇 $K$ 名救生员后，剩下的救生员的班次能够覆盖的最长时间。

### 提示

在这个例子中，Farmer John 应该解雇覆盖 $1 \ldots 8$ 和 $7 \ldots 15$ 的救生员。


---

---
title: "[USACO18JAN] Cow at Large P"
layout: "post"
diff: 省选/NOI-
pid: P4183
tag: ['2018', 'USACO', '点分治', '分治']
---
# [USACO18JAN] Cow at Large P
## 题目描述

Cornered at last, Bessie has gone to ground in a remote farm. The farm consists of $N$ barns ($2 \leq N \leq 7 \cdot 10^4$) and $N-1$ bidirectional tunnels between barns, so that there is a unique path between every pair of barns. Every barn which has only one tunnel is an exit. When morning comes, Bessie will surface at some barn and attempt to reach an exit.

But the moment Bessie surfaces at some barn, the law will be able to pinpoint her location. Some farmers will then start at various exit barns, and attempt to catch Bessie. The farmers move at the same speed as Bessie (so in each time step, each farmer can move from one barn to an adjacent barn). The farmers know where Bessie is at all times, and Bessie knows where the farmers are at all times. The farmers catch Bessie if at any instant a farmer is in the same barn as Bessie, or crossing the same tunnel as Bessie. Conversely, Bessie escapes if she reaches an exit barn strictly before any farmers catch her.


Bessie is unsure at which barn she should surface. For each of the $N$ barns, help Bessie determine the minimum number of farmers who would be needed to catch Bessie if she surfaced there, assuming that the farmers distribute themselves optimally among the exit barns.


Note that the time limit for this problem is slightly larger than the default: 4 seconds for C/C++/Pascal, and 8 seconds for Java/Python.

## 输入格式

The first line of the input contains $N$. Each of the following $N-1$ lines specify two integers, each in the range $1 \ldots N$, describing a tunnel between two barns.

## 输出格式

Please output $N$ lines, where the $i$th line of output tells the minimum number of farmers necessary to catch Bessie if she surfaced at the $i$th barn.

## 样例

### 样例输入 #1
```
7
1 2
1 3
3 4
3 5
4 6
5 7
```
### 样例输出 #1
```
3
1
3
3
3
1
1
```
## 题目翻译

### 题目描述

Bessie 被逼到了绝境，躲进了一个偏远的农场。这个农场由 $N$ 个谷仓（$2 \leq N \leq 7 \cdot 10^4$）和 $N-1$ 条双向隧道组成，因此每对谷仓之间都有一条唯一的路径。每个只有一个隧道的谷仓都是一个出口。当早晨来临时，Bessie 会从某个谷仓出现，并试图到达一个出口。

但是，当 Bessie 从某个谷仓出现时，执法人员会立即定位到她的位置。一些农民会从各个出口谷仓出发，试图抓住 Bessie。农民和 Bessie 的移动速度相同（因此在每个时间步中，每个农民可以从一个谷仓移动到相邻的谷仓）。农民们始终知道 Bessie 的位置，而 Bessie 也始终知道农民们的位置。如果农民和 Bessie 在同一谷仓或同时穿过同一条隧道，农民就会抓住 Bessie。相反，如果 Bessie 在农民抓住她之前严格地到达一个出口谷仓，她就能逃脱。

Bessie 不确定她应该从哪个谷仓出现。对于每个谷仓，请帮助 Bessie 确定如果她从该谷仓出现，假设农民们最优地分布在出口谷仓中，抓住她所需的最少农民数量。

请注意，本题的时间限制略高于默认值：C/C++/Pascal 为 4 秒，Java/Python 为 8 秒。

### 输入格式

输入的第一行包含 $N$。接下来的 $N-1$ 行每行包含两个整数，范围在 $1 \ldots N$ 之间，描述一条连接两个谷仓的隧道。

### 输出格式

请输出 $N$ 行，其中第 $i$ 行表示如果 Bessie 从第 $i$ 个谷仓出现，抓住她所需的最少农民数量。


---

---
title: "[USACO18JAN] Sprinklers P"
layout: "post"
diff: 省选/NOI-
pid: P4184
tag: ['2018', '线段树', 'USACO', '前缀和']
---
# [USACO18JAN] Sprinklers P
## 题目描述

Farmer John has a large field, and he is thinking of planting sweet corn in some part of it. After surveying his field, FJ found that it forms an $(N-1) \times (N-1)$ square. The southwest corner is at coordinates $(0,0)$, and the northeast corner is at $(N-1,N-1)$.

At some integer coordinates there are double-headed sprinklers, each one sprinkling both water and fertilizer. A double-heading sprinkler at coordinates $(i,j)$ sprinkles water on the part of the field north and east of it, and sprinkles fertilizer on the part of the field south and west of it. Formally, it waters all real coordinates $(x,y)$ for which $N \geq x \geq i$ and $N \geq y \geq j$, and it fertilizes all real coordinates $(x,y)$ for which $0 \leq x \leq i$ and $0 \leq y \leq j$.


Farmer John wants to plant sweet corn in some axis-aligned rectangle in his field with integer-valued corner coordinates. However, for the sweet corn to grow, all points in the rectangle must be both watered and fertilized by the double-headed sprinklers. And of course the rectangle must have positive area, or Farmer John wouldn't be able to grow any corn in it!


Help Farmer John determine the number of rectangles of positive area in which he could grow sweet corn. Since this number may be large, output the remainder of this number modulo $10^9 + 7$.

## 输入格式

The first line of the input consists of a single integer $N$, the size of the field ($1 \leq N \leq 10^5$).

The next $N$ lines each contain two space-separated integers. If these integers are $i$ and $j$, where $0 \leq i,j \leq N-1$, they denote a sprinkler located at $(i,j)$.


It is guaranteed that there is exactly one sprinkler in each column and exactly one sprinkler in each row. That is, no two sprinklers have the same $x$-coordinate, and no two sprinklers have the same $y$-coordinate.

## 输出格式

The output should consist of a single integer: the number of rectangles of positive area which are fully watered and fully fertilized, modulo $10^9 + 7$.

## 样例

### 样例输入 #1
```
5
0 4
1 1
2 2
3 0
4 3
```
### 样例输出 #1
```
21
```
## 题目翻译

### 题目描述

农夫约翰有块田，这块田可视为一个 $N×N$  的正方形网格。西南角为 $(0,0)$ ，东北角为 $(N-1, N-1)$ 。  
在某些格子中有双头喷头，每一个都能够同时喷洒水和肥料。一个位于 $(i,j)$  的双头喷头会
* 将水洒在所有满足 $N≥x≥i,$  $N≥y≥j$  的格子 $(x,y)$  上；
* 将肥料洒在所有满足 $0≤x≤i$  和 $0≤y≤j$  的格子 $(x,y)$  上。

农民约翰想在这块田里切割出一个矩形种甜玉米。矩形的边不能把格子切开。矩形内的所有格子都必须能由双头喷头灌溉和施肥。  
求切割矩形的方案数。由于这个数字可能很大，所以输出对 $10^9+7$  取模。

### 输入格式

第一行包含一个整数 $N$ ，表示农场的大小。  
接下来的 $N$  行，每行有两个由空格分隔的整数 $i, j$ 。这表示有一个双头喷头位于 $(i, j)$ 。  
保证每列都有一台喷头，每排正好有一台喷头。换句话说，没有两个喷头有相同的横坐标或纵坐标。

### 输出格式

输出包含一行，表示方案数，对 $10^9+7$  取模。


---

---
title: "[USACO18JAN] Stamp Painting G"
layout: "post"
diff: 省选/NOI-
pid: P4187
tag: ['动态规划 DP', '数学', '2018', 'USACO', '排列组合']
---
# [USACO18JAN] Stamp Painting G
## 题目描述

Bessie has found herself in possession of an $N$-unit long strip of canvas ($1 \leq N \leq 10^6$), and she intends to paint it. However, she has been unable to acquire paint brushes. In their place she has $M$ rubber stamps of different colors ($1 \leq M \leq 10^6$), each stamp $K$ units wide ($1 \leq K \leq 10^6$). Astounded by the possibilities that lie before her, she wishes to know exactly how many different paintings she could conceivably create, by stamping her stamps in some order on the canvas.

To use a stamp, it must first be aligned with exactly $K$ neighboring units on the canvas. The stamp cannot extend beyond the ends of the canvas, nor can it cover fractions of units. Once placed, the stamp paints the $K$ covered units with its color. Any given stamp may be used multiple times, once, or even never at all. But by the time Bessie is finished, every unit of canvas must have been painted at least once.


Help Bessie find the number of different paintings that she could paint, modulo $10^9 + 7$. Two paintings that look identical but were painted by different sequences of stamping operations are counted as the same.


For at least 75% of the input cases, $N,K \leq 10^3$.

## 输入格式

The first and only line of input has three integers, $N$, $M$, and $K$. It is guaranteed that $K \leq N$.

## 输出格式

A single integer: the number of possible paintings, modulo $10^9 + 7$.

## 样例

### 样例输入 #1
```
3 2 2
```
### 样例输出 #1
```
6

```
## 提示

If the two stamps have colors A and B, the possible paintings are AAA, AAB, ABB, BAA, BBA, and BBB.

## 题目翻译

Bessie想拿$M$  种颜色的长为$K$  的图章涂一个长为$N$  的迷之画布。假设他选择涂一段区间，则这段区间长度必须为$K$  ，且涂完后该区间颜色全变成图章颜色。他可以随便涂，但是最后必须把画布画满。问能有多少种最终状态，$N\leq 10^6,M\leq 10^6,K\leq 10^6$ 

对于$75\%$  的数据，$N,K\leq 10^3$ 

输入输出格式

输入格式：

一行3个整数$N,M,K$ 

输出格式：

一个整数表示答案（模$10^9+7$  ）

输入输出样例

说明

如果两个图章叫A,B，合法方案如下:AAB,ABB,BAA,BBA,AAA,BBB

Translated by @ComeIntoPower 


---

---
title: "[USACO18FEB] Cow Gymnasts P"
layout: "post"
diff: 省选/NOI-
pid: P4270
tag: ['2018', 'USACO', '数论', '欧拉函数']
---
# [USACO18FEB] Cow Gymnasts P
## 题目描述

Bored of farm life, the cows have sold all their earthly possessions and joined the crew of a traveling circus. So far, the cows had been given easy acts: juggling torches, walking tightropes, riding unicycles -- nothing a handy-hoofed cow couldn't handle. However, the ringmaster wants to create a much more dramatic act for their next show.
The stage layout for the new act involves $N$ platforms arranged in a circle. On each platform, between $1$ and $N$ cows must form a stack, cow upon cow upon cow. When the ringmaster gives the signal, all stacks must simultaneously fall clockwise, so that the bottom cow in a stack doesn't move, the cow above her moves one platform clockwise, the next cow moves two platforms clockwise, and so forth. Being accomplished gymnasts, the cows know they will have no trouble with the technical aspect of this act. The various stacks of cows will not "interfere" with each other as they fall, so every cow will land on the intended platform. All of the cows landing on a platform form a new stack, which does not fall over.

The ringmaster thinks the act will be particularly dramatic if after the stacks fall, the new stack on each platform contains the same number of cows as the original stack on that platform. We call a configuration of stack sizes "magical" if it satisfies this condition. Please help the cows by computing the number of magical configurations. Since this number may be very large, compute its remainder modulo $10^9 + 7$.

Two configurations are considered distinct if there is any platform for which the configurations assign a different number of cows.
## 输入格式

The input is a single integer, $N$ ($1 \leq N \leq 10^{12}$).
## 输出格式

A single integer giving the number of magical configurations modulo $10^9 + 7$.
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
6
```
## 提示

For $N = 4$, the valid configurations are $(1,1,1,1)$, $(2,2,2,2)$, $(3,3,3,3)$, $(4,4,4,4)$, $(2,3,2,3)$, and $(3,2,3,2)$.

Problem credits: Dhruv Rohatgi
## 题目翻译

### 题目描述

厌倦了农场生活的奶牛们卖掉了所有的财产，加入了一个巡回马戏团。到目前为止，奶牛们被分配了一些简单的表演：杂耍火炬、走钢丝、骑独轮车——没有什么是一头灵巧的奶牛无法应付的。然而，马戏团团长希望为他们的下一场演出创造一个更加戏剧性的表演。

新表演的舞台布局包括 $N$ 个平台，排列成一个圆圈。在每个平台上，必须有 $1$ 到 $N$ 头奶牛堆叠成一摞，奶牛一头叠在另一头上面。当团长发出信号时，所有的堆叠必须同时顺时针倒下，使得堆叠底部的奶牛不动，她上面的奶牛移动一个平台顺时针，再上面的奶牛移动两个平台顺时针，依此类推。作为技艺高超的体操运动员，奶牛们知道她们在技术方面不会有任何问题。各个奶牛堆叠在倒下时不会相互“干扰”，因此每头奶牛都会落在目标平台上。所有落在平台上的奶牛会形成一个新的堆叠，这个堆叠不会倒下。

团长认为，如果堆叠倒下后，每个平台上的新堆叠包含的奶牛数量与原始堆叠相同，那么这个表演将特别戏剧化。我们称满足这一条件的堆叠大小为“魔法”配置。请帮助奶牛们计算魔法配置的数量。由于这个数字可能非常大，请计算其对 $10^9 + 7$ 取模的结果。

如果两个配置在任何平台上分配的奶牛数量不同，则认为它们是不同的配置。

### 输入格式

输入是一个整数 $N$（$1 \leq N \leq 10^{12}$）。

### 输出格式

输出一个整数，表示魔法配置的数量对 $10^9 + 7$ 取模的结果。

### 提示

对于 $N = 4$，有效的配置是 $(1,1,1,1)$、$(2,2,2,2)$、$(3,3,3,3)$、$(4,4,4,4)$、$(2,3,2,3)$ 和 $(3,2,3,2)$。

题目来源：Dhruv Rohatgi


---

---
title: "[USACO18FEB] New Barns P"
layout: "post"
diff: 省选/NOI-
pid: P4271
tag: ['2018', 'USACO', '并查集', '连通块', '最近公共祖先 LCA', '树的直径', '动态树 LCT']
---
# [USACO18FEB] New Barns P
## 题目描述

给你一棵树，初始没有节点。你需要支持两种操作：  

- `B p` 表示新建一个节点，将它与 $p$  节点连接；若 $p=-1$，则表示不与其它节点相连  

- `Q k` 表示查询在 $k$ 节点所在的连通块中，距它最远的点的距离。这里距离的定义是两点间经过的边数。
## 输入格式

第一行一个正整数 $q$，表示操作个数。  
接下来 $q$ 行，每行表示一个操作。
## 输出格式

对于每个询问操作，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
7
B -1
Q 1
B 1
B 2
Q 3
B 2
Q 2
```
### 样例输出 #1
```
0
2
1

```
## 提示

【数据范围】  

对于 $100%$ 的数据，$1 \le q \le 10^5$。  
保证操作合法。

The example input corresponds to this network of barns:
```
  (1) 
    \   
     (2)---(4)
    /
  (3)
```
In query 1, we build barn number 1. In query 2, we ask for the distance of 1 to the farthest connected barn. Since barn 1 is connected to no other barns, the answer is 0. In query 3, we build barn number 2 and connect it to barn 1. In query 4, we build barn number 3 and connect it to barn 2. In query 5, we ask for the distance of 3 to the farthest connected barn. In this case, the farthest is barn 1, which is 2 units away. In query 6, we build barn number 4 and connect it to barn 2. In query 7, we ask for the distance of 2 to the farthest connected barn. All three barns 1, 3, 4 are the same distance away, which is 1, so this is our answer.

Problem credits: Anson Hu


---

---
title: "[USACO18OPEN] Out of Sorts P"
layout: "post"
diff: 省选/NOI-
pid: P4372
tag: ['2018', 'USACO', '排序', 'Ad-hoc']
---
# [USACO18OPEN] Out of Sorts P
## 题目描述

留意着农场之外的长期职业生涯的可能性，奶牛 Bessie 开始在不同的在线编程网站上学习算法。她最喜欢的两个算法是“冒泡排序”和“快速排序”，但不幸的是，Bessie 轻易地把它们搞混了，最后实现了一个奇怪的混合算法！

如果数组 $A$ 中 $A[0 \ldots i]$ 的最大值不大于 $A[i+1 \ldots N-1]$ 的最小值，我们就称元素 $i$ 和 $i+1$ 之间的位置为一个“分隔点”。Bessie 还记得快速排序包含对数组的重排，产生一个分隔点，然后递归对两侧的 $A[0 \ldots i]$ 和 $A[i+1 \ldots N-1]$ 排序。然而，尽管她正确地记下了数组中所有的分隔点都可以在线性时间内求出，她却忘记了快速排序应该如何重排来快速构造一个分隔点！在这个可能是排序算法历史上最糟糕的失误之下，她做出了一个不幸的决定：使用冒泡排序来完成这个任务。

以下是 Bessie 最初对数组 $A$ 进行排序的实现的概要。她首先写了一个简单的函数，执行冒泡排序的一轮：

```
bubble_sort_pass(A) {
   for i = 0 to length(A)-2
      if A[i] > A[i+1], swap A[i] and A[i+1]
}
```

她的快速排序（相当快）函数的递归代码如下：

```
quickish_sort(A) {
   if length(A) == 1, return
   do { // Main loop
      work_counter = work_counter + length(A)
      bubble_sort_pass(A)
   } while (no partition points exist in A)
   divide A at all partition points; recursively quickish_sort each piece
}
```

Bessie 好奇于她的代码能够运行得多快。简单起见，她计算出主循环的每一轮都消耗线性时间，因此她通过增加一个全局变量 `work_counter` 的值来跟踪整个算法完成的总工作量。

给定一个输入数组，请预测 `quickish_sort` 函数接收这个数组后，变量 `work_counter` 的最终值。
## 输入格式

输入的第一行包含 $N$（$1 \leq N \leq 100,000$）。接下来的 $N$ 行描述了 $A[0] \ldots A[N-1]$，每个数都是一个范围在 $0 \ldots 10^9$ 的整数。输入数据不保证各不相同。
## 输出格式

输出 `work_counter` 的最终值。
## 样例

### 样例输入 #1
```
7
20
2
3
4
9
8
7
```
### 样例输出 #1
```
12

```
## 提示

在这个例子中，数组初始为 `20 2 3 4 9 8 7`。在一轮冒泡排序之后（增加 $7$ 的工作量），我们得到 `2 | 3 | 4 | 9 8 7 | 20`，其中 `|` 表示一个分隔点。于是问题被分成了递归的子问题，包括对 `2`、`3`、`4`、`20` 排序（每个消耗 $0$ 单元的工作量）和对 `9 8 7` 排序。对于 `9 8 7` 这个子问题，主循环的一轮（$3$ 单元工作量）得到 `8 7 | 9`，在此之后最后一轮处理 `8 7`（$2$ 单元工作量）就有效地完成了排序。

题目来源：Brian Dean


---

---
title: "[USACO14MAR] The Lazy Cow G"
layout: "post"
diff: 省选/NOI-
pid: P4876
tag: ['2014', 'USACO']
---
# [USACO14MAR] The Lazy Cow G
## 题目描述

It's a hot summer day, and Bessie the cow is feeling quite lazy. She wants to locate herself at a position in her field so that she can reach as much delicious grass as possible within only a short distance.

There are $N$ patches of grass $(1 <= N <= 100,000)$ in Bessie's field. The $ith$ such patch contains $g_i$ units of grass $(1 <= g_i <= 10,000)$ and is located at a distinct point $(x_i, y_i)$ in the field $(0 <= x_i,$ $y_i <= $ $1,000,000)$.  Bessie would like to choose a point in the field as her initial location (possibly the same point as a patch of grass, and possibly even a point with non-integer coordinates) so that a maximum amount of grass is within a distance of $K$ steps from this location $(1 <= K <= 2,000,000)$.

When Bessie takes a step, she moves 1 unit north, south, east, or west of her current position.  For example, to move from $(0,0)$ to $(3,2)$, this requires 5 total steps.  Bessie does not need to take integer-sized steps -- for example, 1 total step could be divided up as half a unit north and half a unit east.

Please help Bessie determine the maximum amount of grass she can reach, if she chooses the best possible initial location.

## 输入格式

* Line 1: The integers $N$ and $K$.

* Lines 2..1+N: Line $i+1$ describes the $ith$ patch of grass using 3 integers: $g_i, x_i, y_i.$

## 输出格式

* Line 1: The maximum amount of grass Bessie can reach within $K$ steps, if she locates herself at the best possible initial position.
## 样例

### 样例输入 #1
```
4 3
7 8 6
3 0 0
4 6 0
1 4 2
```
### 样例输出 #1
```
8
```
## 提示

INPUT DETAILS:

Bessie is willing to take at most 3 steps from her initial position.  There
are 4 patches of grass.  The first contains 7 units of grass and is located
at position $(8,6)$, and so on.

OUTPUT DETAILS:

By locating herself at $(3,0)$, the grass at positions $(0,0)$, $(6,0)$, and
$(4,2)$ is all within $K$ units of distance.
## 题目翻译

```
  Bessie的田里有N(1<=N<=100,000)块草地，每块草地的坐标是 (xi, yi) (0<=xi,yi<=1,000,000),上面长着gi(1<=gi<=10,000)个单位的牧草。 
  Bessie可以向东南西北方向走，一次走一步（一个单位长度）。如她从（0,0）走到（3,2）需要5步。她最多可以一次走k (1<=k<=2,000,000) 步。
  现在她想找一个位置，使她从该位置出发可以得到最多单位的牧草(她可以走多次，但每次都从该位置出发)。 
  输入格式： 
  第1行：两个整数N和K 
  第2~N+1行：三个整数gi，xi，yi 
  输出格式： 
  第1行：Bessie所能获得的最多单位牧草数
```


---

---
title: "[USACO02FEB] Cow Cycling"
layout: "post"
diff: 省选/NOI-
pid: P4953
tag: ['2002', 'USACO']
---
# [USACO02FEB] Cow Cycling
## 题目描述

奶牛自行车队由 $N$ 名队员组成，他们正准备参加一个比赛，这场比赛的路程共有 $D$ 圈。车队在比赛时会排成一条直线，由于存在空气阻力，当骑车速度达到每分钟 $x$ 圈时，领头的奶牛每分钟消耗的体力为 $x^2$，其它奶牛每分钟消耗的体力为 $x$。每头奶牛的初始体力值都是相同的，记作 $E$。如果有些奶牛在比赛过程中的体力不支，就会掉队，掉队的奶牛不能继续参加比赛。每支队伍最后只要有一头奶牛能到终点就可以了。

比赛规定，最小的计时单位是分钟，在每分钟开始的时候，车队要哪头奶牛负责领头，领头奶牛不能在这分数中内掉队，每分钟骑过的圈数也必须是整数。

请帮忙计划一下，采用什么样的策略才能让车队以最快的时间到达终点？
## 输入格式

第一行：三个正整数：$N, E, D$。$1 \leq N \leq 20$，$1 \leq E \leq 100$，$1 \leq D \leq 100$。
## 输出格式

第一行：单独一个整数，表示最早达到终点的时间，如果无法到达终点，输出 $0$。
## 样例

### 样例输入 #1
```
3 30 20
```
### 样例输出 #1
```
7
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/spwg7uf6.png)


---

---
title: "[USACO09OPEN] Tower of Hay G"
layout: "post"
diff: 省选/NOI-
pid: P4954
tag: ['2009', 'USACO']
---
# [USACO09OPEN] Tower of Hay G
## 题目背景

为了调整电灯亮度，贝西要用干草包堆出一座塔，然后爬到牛棚顶去把灯泡换掉。干草包会从传送带上运来，共会出现 $n$ 包干草，第 $i$ 包干草的宽度是 $W_i$，高度和长度统一为 $1$。干草塔要从底层开始铺建。贝西会选择最先送来的若干包干草，堆在地上作为第一层，然后再把紧接着送来的几包干草包放在第二层， 再铺建第三层……重复这个过程，一直到所有的干草全部用完。每层的干草包必须紧靠在一起，不出现缝隙，而且为了建筑稳定，上层干草的宽度不能超过下层的宽度。 按顺序运来的干草包一定要都用上，不能将其中几个干草包弃置不用。贝西的目标是建一座最高的塔，请你来帮助她完成这个任务吧。
## 输入格式

第一行：一个整数 $n,\ (1 ≤ n ≤ 100000)$

第二行到 $n + 1$ 行：第 $i + 1$ 行有一个整数 $W_i,\ (1 ≤ W_i ≤ 10000)$。
## 输出格式

第一行：单个整数，表示可以建立的最高高度。
## 样例

### 样例输入 #1
```
3
1
2
3
```
### 样例输出 #1
```
2
```
## 提示

### 样例解释

将 $1$ 和 $2$ 放在第一层，将 $3$ 放在第二层。


---

---
title: "[USACO18DEC] Balance Beam P"
layout: "post"
diff: 省选/NOI-
pid: P5155
tag: ['数学', '2018', 'USACO', '期望', '凸包']
---
# [USACO18DEC] Balance Beam P
## 题目描述

Bessie为了存钱给她的牛棚新建一间隔间，开始在当地的马戏团里表演，通过在平衡木上小心地来回走动来展示她卓越的平衡能力。

Bessie能够通过表演赚到的钱取决于她最终成功跳下平衡木的位置。平衡木上从左向右的位置记为 $ 0,1,\ldots,N+1 $ 。如果Bessie到达了位置 $ 0 $ 或是 $ N+1 $ ，她就会从平衡木的一端掉下去，遗憾地得不到报酬。

如果Bessie处在一个给定的位置 $ k $ ，她可以进行下面两项中的任意一项：

1. 投掷一枚硬币。如果背面朝上，她前往位置 $ k-1 $ ，如果正面朝上，她前往位置 $ k+1 $ （也就是说，每种可能性 $ 1/2 $ 的概率）。

2. 跳下平衡木，获得 $ f(k) $ 的报酬（ $ 0 \leq f(k) \leq 10^9 $ ）。

Bessie意识到她并不能保证结果能够得到某一特定数量的报酬，这是由于她的移动是由随机的掷硬币结果控制。然而，基于她的起始位置，她想要求出当她进行一系列最优的决定之后，她能够得到的期望报酬（“最优”指的是这些决定能够带来最高可能的期望报酬）。

例如，如果她的策略能够使她以 $ 1/2 $ 的概率获得 $ 10 $ 的报酬，$ 1/4 $ 的概率获得 $ 8 $ 的报酬，$ 1/4 $ 的概率获得 $ 0 $ 的报酬，那么她的期望报酬为加权平均值 $ 10 \times (1/2)+8 \times (1/4)+0 \times (1/4)=7 $ 。
## 输入格式

输入的第一行包含 $ N $ （ $ 2 \leq N \leq 10^5 $ ）。以下 $ N $ 行包含 $ f(1) \ldots f(N) $ 。
## 输出格式

输出 $ N $ 行。第 $ i $ 行输出 $ 10^5 $ 乘以Bessie从位置 $ i $ 开始使用最优策略能够获得的报酬的期望值，向下取整。
## 样例

### 样例输入 #1
```
2
1
3
```
### 样例输出 #1
```
150000
300000

```


---

---
title: "[USACO18DEC] Sort It Out P"
layout: "post"
diff: 省选/NOI-
pid: P5156
tag: ['2018', 'USACO', '树状数组']
---
# [USACO18DEC] Sort It Out P
## 题目描述

FJ 有 $N$（$1 \leq N \leq 10^5$）头奶牛（分别用 $1 \ldots N$ 编号）排成一行。FJ 喜欢他的奶牛以升序排列，不幸的是现在她们的顺序被打乱了。在过去，FJ 曾经使用一些诸如“冒泡排序”的开创性算法来使他的奶牛排好序，但今天他想偷个懒。取而代之，他会每次对着一头奶牛叫道“按顺序排好”。当一头奶牛被叫到的时候，她会确保自己在队伍中的顺序是正确的（从她的角度看来）。当有一头紧接在她右边的奶牛的编号比她小，她们就交换位置。然后，当有一头紧接在她左边的奶牛的编号比她大，她们就交换位置。这样这头奶牛就完成了“按顺序排好”，在这头奶牛看来左边的奶牛编号比她小，右边的奶牛编号比她大。

FJ 想要选出这些奶牛的一个子集，然后遍历这个子集，依次对着每一头奶牛发号施令（按编号递增的顺序），重复这样直到所有 $N$ 头奶牛排好顺序。例如，如果他选出了编号为 $\{2,4,5\}$ 的奶牛的子集，那么他会喊叫奶牛 $2$，然后是奶牛 $4$，然后是奶牛 $5$。如果 $N$ 头奶牛此时仍未排好顺序，他会再次对着这几头奶牛喊叫，如果有必要的话继续重复。

由于 FJ 不确定哪些奶牛比较专心，他想要使得这个子集最小。此外，他认为 $K$ 是个幸运数字。请帮他求出满足重复喊叫可以使得所有奶牛排好顺序的最小子集之中字典序第 $K$ 小的子集。

我们称 $\{1, \ldots ,N\}$ 的一个子集 $S$ 在字典序下小于子集 $T$，当 $S$ 的所有元素组成的序列（按升序排列）在字典序下小于 $T$ 的所有元素组成的序列（按升序排列）。例如，$\{1,3,6\}$ 在字典序下小于 $\{1,4,5\}$。
## 输入格式

输入的第一行包含一个整数 $ N $ 。第二行包含一个整数 $ K $ （ $ 1 \leq K \leq 10^{18} $ ）。第三行包含 $ N $ 个空格分隔的整数，表示从左到右奶牛的编号。

保证存在至少 $ K $ 个符合要求的子集。
## 输出格式

第一行输出最小子集的大小。接下来输出字典序第 $ K $ 小的最小子集中奶牛的编号，每行一个数，升序排列。
## 样例

### 样例输入 #1
```
4 1
4 2 1 3

```
### 样例输出 #1
```
2
1
4

```
## 提示

开始的时候序列为 $ \mathtt{\:4\:\; 2\:\; 1\:\; 3\:} $ 。在FJ喊叫编号为 $ 1 $ 的奶牛之后，序列变为 $ \mathtt{\:1\:\; 4\:\; 2\:\; 3\:} $ 。在FJ喊叫编号为 $ 4 $ 的奶牛之后，序列变为 $ \mathtt{\:1\:\; 2\:\; 3\:\; 4\:} $ 。在这个时候，序列已经完成了排序。

## 子任务

对于占总分 $ 3/16 $ 的测试数据， $ N \leq 6 $ ，并且 $ K=1 $ 。

对于另外的占总分 $ 5/16 $ 的测试数据， $ K=1 $ 。

对于另外的占总分 $ 8/16 $ 的测试数据，没有其他限制。


---

---
title: "[USACO18DEC] The Cow Gathering P"
layout: "post"
diff: 省选/NOI-
pid: P5157
tag: ['图论', '2018', 'USACO', '图论建模', '拓扑排序']
---
# [USACO18DEC] The Cow Gathering P
## 题目描述

奶牛们从世界各地聚集起来参加一场大型聚会。总共有 $ N $ 头奶牛， $ N-1 $ 对奶牛互为朋友。每头奶牛都可以通过一些朋友关系认识其他每头奶牛。

她们玩得很开心，但是现在到了她们应当离开的时间了，她们会一个接一个地离开。她们想要以某种顺序离开，使得只要至少还有两头奶牛尚未离开，所有尚未离开的奶牛都还有没有离开的朋友。此外，由于行李寄存的因素，有 $ M $ 对奶牛 $ (a_i,b_i) $ 必须满足奶牛 $ a_i $ 要比奶牛 $ b_i $ 先离开。注意奶牛 $ a_i $ 和奶牛 $ b_i $ 可能是朋友，也可能不是朋友。

帮助奶牛们求出，对于每一头奶牛，她是否可以成为最后一头离开的奶牛。可能会发生不存在满足上述要求的奶牛离开顺序的情况。
## 输入格式

输入的第 $ 1 $ 行包含两个空格分隔的整数 $ N $ 和 $ M $ 。

输入的第 $ 2 \leq i \leq N $ 行，每行包含两个整数 $ x_i $ 和 $ y_i $ ，满足 $ 1 \leq x_i $ ， $ y_i \leq N,xi \neq yi $ ，表示奶牛 $ x_i $ 和奶牛 $ y_i $ 是朋友关系。

输入的第 $ N+1 \leq i \leq N+M $ 行，每行包含两个整数 $ a_i $ 和 $ b_i $ ，满足 $ 1 \leq a_i,b_i \leq N $ ， $ a_i \neq b_i $ ，表示奶牛 $ a_i $ 必须比奶牛 $ b_i $ 先离开聚会。

输入保证 $ 1 \leq N,M \leq 10^5 $ 。对于占总分 $ 20\% $ 的测试数据，保证 $ N,M \leq 3000 $ 。
## 输出格式

输出 $ N $ 行，每行包含一个整数 $ d_i $ ，如果奶牛 $ i $ 可以成为最后一头离开的奶牛，则 $ d_i=1 $ ，否则 $ d_i=0 $ 。
## 样例

### 样例输入 #1
```
5 1
1 2
2 3
3 4
4 5
2 4

```
### 样例输出 #1
```
0
0
1
1
1

```


---

---
title: "[USACO19JAN] Exercise Route P"
layout: "post"
diff: 省选/NOI-
pid: P5203
tag: ['2019', 'USACO', '最近公共祖先 LCA', '容斥原理']
---
# [USACO19JAN] Exercise Route P
## 题目背景

USACO 19 年一月月赛铂金组第二题。
## 题目描述

奶牛 Bessie 意识到为了保持好的体形她需要更多地进行锻炼。她需要你帮助她选择在农场里每天用来晨跑的路线。 农场由 $n$ 块草地组成，方便起见编号为 $1\sim n$，由 $m$ 条双向的小路连接。作为一种遵循规律的生物，奶牛们倾向于使用其中特定的 $n−1$ 条小路作为她们日常在草地之间移动的路线——她们管这些叫“常规的”小路。从每块草地出发都可以仅通过常规的小路到达所有其他草地。

为了使她的晨跑更加有趣，Bessie 觉得她应该选择一条包含一些非常规的小路的路线。然而，使用常规的小路能够使她感到舒适，所以她不是很想在她的路线中使用过多非常规的小路。经过一些思考，她认为一条好的路线应当形成一个简单环（能够不经过任何草地超过一次的情况下回到起点），其中包含恰好两条非常规的小路。

请帮助 Bessie 计算她可以使用的好的路线的数量。两条路线被认为是相同的，如果它们包含的小路的集合相等。
## 输入格式

输入的第一行包含 $n$ 和 $m$。以下 $m$ 行每行包含两个整数 $a_i$ 和 $b_i$，描述了一条小路的两端。其中前 $(n−1)$ 条是常规的小路。
## 输出格式

输出一行一个整数表示 Bessie 可以选择的路线的总数。
## 样例

### 样例输入 #1
```
5 8
1 2
1 3
1 4
1 5
2 3
3 4
4 5
5 2
```
### 样例输出 #1
```
4
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 2 \times 10^5$，$1 \leq m \leq 2 \times 10^5$，$m \geq n - 1$，$1 \leq a_i, b_i \leq n$。


---

---
title: "[USACO19JAN] Train Tracking 2 P"
layout: "post"
diff: 省选/NOI-
pid: P5204
tag: ['动态规划 DP', '2019', 'USACO']
---
# [USACO19JAN] Train Tracking 2 P
## 题目背景

USACO 2019 一月月赛铂金组第三题
## 题目描述

每天特快列车都会经过农场。列车有 $N$ 节车厢（$1 \le N \le 10^5$），每节车厢上有一个 $1$ 到 $10^9$ 之间的正整数编号；不同的车厢可能会有相同的编号。
平时，Bessie 会观察驶过的列车，记录车厢的编号。但是今天雾实在太浓了，Bessie 一个编号也看不见！幸运的是，她从城市里某个可靠的信息源获知了列车编号序列的所有滑动窗口中的最小值。具体地说，她得到了一个正整数 $K$ ，以及 $N-K+1$ 个正整数 $c_1,…,c_{N+1-K}$ ，其中 $c_i$ 是车厢 $i,i+1,…,i+K-1$ 之中编号的最小值。

帮助 Bessie 求出满足所有滑动窗口最小值的对每节车厢进行编号的方法数量。由于这个数字可能非常大，只要你求出这个数字对 $10^9+7$ 取余的结果 Bessie 就满意了。

Bessie 的消息是完全可靠的；也就是说，保证存在至少一种符合要求的编号方式。

## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $K$ 。余下的行包含所有的滑动窗口最小值 $c_1,…,c_{N+1-K}$ ，每行一个数。

## 输出格式

输出一个整数：对每节车厢给予一个不超过 $10^9$ 的正整数编号的方法数量对 $10^9+7$ 取余的结果，满足车厢 $i,i+1,…,i+K-1$ 之中编号的最小值等于 $c_i$，对于 $1 \le i \le N - K+1$ 均成立。

## 样例

### 样例输入 #1
```
4 2
999999998
999999999
999999998
```
### 样例输出 #1
```
3
```


---

---
title: "[USACO19FEB] Cow Dating P"
layout: "post"
diff: 省选/NOI-
pid: P5242
tag: ['2019', 'USACO', '三分', '斜率优化']
---
# [USACO19FEB] Cow Dating P
## 题目描述

由于目前可供奶牛们使用的约会网站并没有给 Farmer John 留下深刻印象，他决定推出一个基于新匹配算法的奶牛交友网站，该算法可基于公牛和母牛间的共同兴趣对公牛和母牛进行匹配。

Bessie 在寻找情人节 Barn Dance 的合作伙伴时，决定试用这个网站。在注册账户之后，FJ 的算法为他给出了一个长度为 $ N $（$1 \leq N \leq 10^6$） 的匹配列表，列表上每头公牛接受她舞蹈邀请的概率为 $ p $（$0 < p < 1$）。

Bessie 决定向列表中的一个连续区间内的奶牛发送邀请，但Bessie希望**恰好只有一个奶牛**接受邀请。请帮助 Bessie 求出**恰好只有一个奶牛**接受邀请的最大概率是多少。
## 输入格式

第一行输入一个整数 $ N $ 。

接下来 $ N $ 行，每行包含一个整数，它的含义是 $ p_i $ 乘以 $ 10^6 $ 后的结果。
## 输出格式

请输出**恰好只有一个奶牛**接受邀请的最大概率乘以 $ 10^6 $ 后向下取整后的结果。
## 样例

### 样例输入 #1
```
3
300000
400000
350000

```
### 样例输出 #1
```
470000
```
## 提示

样例的最优方案是向第二和第三只奶牛发送邀请。

子任务：对于 $ 25\% $ 的数据， $ N \leq 4000 $ 。


---

---
title: "[USACO19FEB] Moorio Kart P"
layout: "post"
diff: 省选/NOI-
pid: P5243
tag: ['动态规划 DP', '2019', 'USACO']
---
# [USACO19FEB] Moorio Kart P
## 题目描述

Bessie 和 Farmer John 喜欢山羊卡丁车比赛。这个比赛非常类似于其他人喜欢的卡丁车比赛，除了卡丁车是由山羊拉动，以及赛道是由农田组成。农田由 $ N $ 个草地和 $ M $ 条道路组成，每条道路都连接着两个草地。

定义农场是两个或更多草地的一个集合，同一农场中的每个草地都可以沿着一系列**唯一**的道路到达农场中其他任意一个草地。

整个农田可能由多个农场组成，假设图中有 $ K $ 个农场。Bessie 希望通过添加长度为 $ X $ 的 $ K $ 条道路，连接所有 $ K $ 个农场来制作山羊卡丁车赛道。每个农场只应访问一次，并且每个农场内必须至少穿过一条道路。

为了让选手们对赛道更有兴趣，赛道的长度至少应该为 $ Y $ 。Bessie 希望知道所有这些有趣赛道的赛道长度总和。如果一个赛道中有两个农场直接相连，但另外一个赛道中这两个农场没有直接相连的话，这两个赛道就是不同的。

---

形式化题意：

给定 $K$ 个连通块的森林，边有边权。你需要加入 $K$ 条长为 $X$ 的边使得整张图变成一棵基环树。原来的每个连通块在环上至少有一条边，所有新加入的边都应该在环上。

求所有环长 $\ge Y$ 的合法方案的环长之和。
## 输入格式

第一行包括四个整数 $ N,M,X,Y $（$1 \leq N \leq 1500,1 \leq M \leq N-1,0 \leq X, Y \leq 2500$）。

接下来 $ M $ 行，每行包含三个整数： $ A_i,B_i,D_i $（$1 \leq A_i, B_i \leq N,0 \leq D_i \leq 2500$），代表 $ A_i $ 号草地和 $ B_i $ 号草地间有一条长度为 $ D_i $ 的道路。保证两个草地间最多只有一条道路直接相连，且不存在自环。
## 输出格式

输出有趣赛道的赛道长度总和 $\pmod {10^9+7}$ 后的结果。
## 样例

### 样例输入 #1
```
5 3 1 12
1 2 3
2 3 4
4 5 6

```
### 样例输出 #1
```
54
```
## 提示

有 6 个合法的赛道方案：

- 1 --> 2 --> 4 --> 5 --> 1 (长度 11)
- 1 --> 2 --> 5 --> 4 --> 1 (长度 11)
- 2 --> 3 --> 4 --> 5 --> 2 (长度 12)
- 2 --> 3 --> 5 --> 4 --> 2 (长度 12)
- 1 --> 2 --> 3 --> 4 --> 5 --> 1 (长度 15)
- 1 --> 2 --> 3 --> 5 --> 4 --> 1 (长度 15)

其中后 4 条赛道满足了赛道总长不低于 12 的条件，这几条赛道的长度总和为 54。

子任务：对于 $ 70\% $ 的数据， $ N,Y \leq 1000 $ 。


---

---
title: "[USACO19DEC] Tree Depth P"
layout: "post"
diff: 省选/NOI-
pid: P5853
tag: ['数学', '2019', 'USACO', '组合数学', '生成函数']
---
# [USACO19DEC] Tree Depth P
## 题目背景

For the new year, Farmer John decided to give his cows a festive binary search tree
(BST)! 

To generate the BST, FJ starts with a permutation $a=\{a_1,a_2,\ldots,a_N\}$
of the integers $1\ldots N$, where $N\le 300$.  He then runs the following
pseudocode with arguments $1$ and $N.$

```
generate(l,r):
  if l > r, return empty subtree;
  x = argmin_{l <= i <= r} a_i; // index of min a_i in {a_l,...,a_r}
  return a BST with x as the root, 
    generate(l,x-1) as the left subtree,
    generate(x+1,r) as the right subtree;
```
For example, the permutation $\{3,2,5,1,4\}$ generates the following BST:

```
    4
   / \
  2   5
 / \ 
1   3
```
Let $d_i(a)$ denote the depth of node $i$ in the tree corresponding to $a,$ 
meaning the number of nodes on the path from $a_i$ to the root. In the above
example, $d_4(a)=1, d_2(a)=d_5(a)=2,$ and $d_1(a)=d_3(a)=3.$

The number of inversions of $a$ is equal to the number of pairs of integers
$(i,j)$ such that $1\le i<j\le N$ and $a_i>a_j.$ The cows know that the $a$ that
FJ will use to generate the BST has exactly $K$ inversions
$(0\le K\le \frac{N(N-1)}{2})$.  Over all $a$ satisfying this condition, compute
the remainder when $\sum_ad_i(a)$ is divided by $M$ for each $1\le i\le N.$
## 题目描述

为了迎接新年，Farmer John 决定给他的奶牛们一个节日二叉搜索树！

为了生成这个二叉搜索树，Farmer John 从一个 $1 \dots N$ 的排列 $a= \{1,2, \dots ,N\}$ 开始，然后以参数 $l$ 和 $r$ 开始运行如下的伪代码：
```
generate(l,r):
  if l > r, return empty subtree;
  x = argmin_{l <= i <= r} a_i; // index of min a_i in {a_l,...,a_r}
  return a BST with x as the root, 
    generate(l,x-1) as the left subtree,
    generate(x+1,r) as the right subtree;
```
例如，排列 $\{ 3,2,5,1,4 \}$ 将产生如下的二叉搜索树：

![](https://cdn.luogu.com.cn/upload/image_hosting/gw6ursc0.png)

令 $d_i(a)$ 表示节点 $i$ 在用排列 $a$ 生成的二叉搜索树中的深度。深度定义为这个节点到根节点的路径上的点数。在上述例子中，$d_4(a)=1,d_2(a)=d_5(a)=2,d_1(a)=d_3(a)=3$。

$a$ 中的逆序对数等于满足 $1 \le i<j \le N$ 且 $a_i>a_j$ 的数对 $(i,j)$ 的个数。奶牛们知道 Farmer John 用来生成二叉搜索树的排列 $a$ 中恰好有 $K$ 个逆序对。对于所有满足条件的 $a$，请计算对于每个 $1 \le i \le N$，$\sum_a d_i(a)$ 对 $M$ 取模后的结果。
## 输入格式

输入只有一行，包含三个整数 $N,K,M$。
## 输出格式

输出一行 $N$ 个整数，第 $i$ 个整数表示 $\sum_a d_i(a) \bmod M$。两个整数之间用一个空格隔开。
## 样例

### 样例输入 #1
```
3 0 192603497

```
### 样例输出 #1
```
1 2 3

```
### 样例输入 #2
```
3 1 144408983

```
### 样例输出 #2
```
3 4 4

```
## 提示

#### 样例解释 1

对于这个样例，唯一满足条件的排列为 $a=\{1,2,3\}$。

#### 样例解释 2

对于这个样例，满足条件的两个排列分别为 $a=\{1,3,2\}$ 和 $a=\{2,1,3\}$。

#### 数据范围

对于全部数据，$1\le N\le 300$，$0\le K\le \frac{N(N-1)}{2}$，保证 $M$ 是一个 $\left[ 10^8,10^9+9 \right]$ 范围中的质数。

对于测试点 $3,4$，满足 $N \le 8$；

对于测试点 $5-7$，满足 $N \le 20$；

对于测试点 $8-10$，满足 $N \le 50$。

USACO 2019 December 铂金组T3


---

---
title: "[USACO20JAN] Springboards G"
layout: "post"
diff: 省选/NOI-
pid: P6007
tag: ['动态规划 DP', '2020', 'USACO', '树状数组', '动态规划优化']
---
# [USACO20JAN] Springboards G
## 题目描述

Bessie 在一个仅允许沿平行于坐标轴方向移动的二维方阵中。她从点 $(0,0)$ 出发，想要到达 $(N,N)$（$1 \leq N \leq 10^9$）。为了帮助她达到目的，在方阵中有 $P$（$1 \leq P \leq 10^5$）个跳板。每个跳板都有其固定的位置 $(x_1,y_1)$，如果 Bessie 使用它，会落到点 $(x_2,y_2)$。

Bessie 是一个过程导向的奶牛，所以她仅允许她自己向上或向右行走，从不向左或向下。类似地，每个跳板也设置为不向左或向下。Bessie 需要行走的距离至少是多少？
## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $P$。

以下 $P$ 行每行包含四个整数 $x_1,y_1,x_2,y_2$，其中 $x_1 \leq x_2$ 且 $y_1 \leq y_2$。

所有跳板的位置和目标位置均不相同。
## 输出格式

输出一个整数，为 Bessie 到达点 $(N,N)$ 需要行走的最小距离。
## 样例

### 样例输入 #1
```
3 2
0 1 0 2
1 2 2 3
```
### 样例输出 #1
```
3
```
## 提示

### 样例解释

Bessie 的最佳路线为：

- Bessie 从 (0,0) 走到 (0,1)（1 单位距离）。
- Bessie 跳到 (0,2)。
- Bessie 从 (0,2) 走到 (1,2)（1 单位距离）。
- Bessie 跳到 (2,3)。
- Bessie 从 (2,3) 走到 (3,3)（1 单位距离）。

Bessie 总共走过的路程为 3 单位距离。

### 子任务

- 测试点 $2 \sim 5$ 满足 $P \leq 1000$。
- 测试点 $6 \sim 15$ 没有额外限制。


---

---
title: "[USACO20JAN] Non-Decreasing Subsequences P"
layout: "post"
diff: 省选/NOI-
pid: P6009
tag: ['动态规划 DP', '2020', 'USACO', '矩阵运算', '分治']
---
# [USACO20JAN] Non-Decreasing Subsequences P
## 题目描述

Bessie 最近参加了一场 USACO 竞赛，遇到了以下问题。当然 Bessie 知道怎么做。那你呢？

考虑一个仅由范围在 $1 \ldots K$（$1 \leq K \leq 20$）之间的整数组成的长为 $N$ 的序列 $A_1,A_2, \ldots ,A_N$（$1 \leq N \leq 5 \times 10^4$）。给定 $Q$（ $1 \leq Q \leq 2 \times 10^5$ ）个形式为 $[L_i,R_i]$（$1 \leq L_i \leq R_i \leq N$）的询问。对于每个询问，计算 $A_{L_i},A_{L_i+1}, \ldots ,A_{R_i}$ 中不下降子序列的数量模 $10^9+7$ 的余数。

$A_L,\ldots ,A_R$ 的一个不下降子序列是一组索引 （$j_1,j_2, \ldots ,j_x$），满足 $L\le j_1<j_2<\ldots<j_x\le R$ 以及 $A_{j_1}\le A_{j_2}\le \ldots \le A_{j_x}$。确保你考虑了空子序列！
## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $K$。

第二行包含 $N$ 个空格分隔的整数 $A_1,A_2, \ldots ,A_N$。

第三行包含一个整数 $Q$。

以下 $Q$ 行每行包含两个空格分隔的整数 $L_i$ 和 $R_i$。
## 输出格式

对于每个询问 $[L_i,R_i]$，你应当在新的一行内输出 $A_{L_i},A_{L_i+1},\ldots, A_{R_i}$ 的不下降子序列的数量模 $10^9+7$ 的余数。
## 样例

### 样例输入 #1
```
5 2
1 2 1 1 2
3
2 3
4 5
1 5
```
### 样例输出 #1
```
3
4
20
```
## 提示

### 样例解释

对于第一个询问，不下降子序列为 $()$、$(2)$ 和 $(3)$。$(2,3)$ 不是一个不下降子序列，因为 $A_2\not \le A_3$。

对于第二个询问，不下降子序列为 $()$、$(4)$、$(5)$ 和 $(4,5)$。

### 子任务

- 测试点 $2 \sim 3$ 满足 $N \leq 1000$。
- 测试点 $4 \sim 6$ 满足 $K \leq 5$。
- 测试点 $7 \sim 9$ 满足 $Q \leq 10^5$。
- 测试点 $10 \sim 12$ 没有额外限制。


---

---
title: "[USACO20JAN] Falling Portals P"
layout: "post"
diff: 省选/NOI-
pid: P6010
tag: ['贪心', '2020', '倍增', '二分', 'USACO', '凸包']
---
# [USACO20JAN] Falling Portals P
## 题目描述

有 $N$（$2 \leq N \leq 2 \times 10^5$）个世界，每个世界有一个传送门。初始时，世界 $i$（对于 $1 \leq i \leq N$）位于 $x$ 坐标 $i$，$y$ 坐标 $A_i$（$1 \leq A_i \leq 10^9$）。每个世界里还有一头奶牛。在时刻 $0$，所有的 $y$ 坐标各不相同，然后这些世界开始坠落：世界 $i$ 沿着 $y$ 轴负方向以 $i$ 单位每秒的速度移动。

在任意时刻，如果两个世界在某一时刻 $y$ 坐标相同（可能是非整数时刻），传送门之间就会“同步”，使得其中一个世界的奶牛可以选择瞬间传送到另一个世界。

对于每一个 $i$，在世界 $i$ 的奶牛想要去往世界 $Q_i$（$Q_i \neq i$）。帮助每头奶牛求出如果她以最优方案移动需要多少时间。

每个询问的输出是一个分数 $a/b$，其中 $a$ 和 $b$ 为互质的正整数，或者 $-1$，如果不可能到达。
## 输入格式

输入的第一行包含一个整数 $N$。

下一行包含 $N$ 个空格分隔的整数 $A_1,A_2,\ldots,A_N$。

下一行包含 $N$ 个空格分隔的整数 $Q_1,Q_2,\ldots,Q_N$。
## 输出格式

输出 $N$ 行，第 $i$ 行包含奶牛 $i$ 的旅程的时间。
## 样例

### 样例输入 #1
```
4
3 5 10 2
3 3 2 1
```
### 样例输出 #1
```
7/2
7/2
5/1
-1
```
## 提示

### 样例解释

考虑原先在世界 $2$ 的奶牛的答案。在时刻 $2$ 世界 $1$ 和世界 $2$ 同步，所以奶牛可以前往世界 $1$。在时刻 $\frac{7}{2}$ 世界 $1$ 和世界 $3$ 同步，所以奶牛可以前往世界 $3$。

### 子任务

- 测试点 $2 \sim 3$ 满足 $N \leq 100$。
- 测试点 $4 \sim 5$ 满足 $N \leq 2000$。
- 测试点 $6 \sim 14$ 没有额外限制。


---

---
title: "[USACO05JAN] Muddy Fields G"
layout: "post"
diff: 省选/NOI-
pid: P6062
tag: ['2005', 'USACO']
---
# [USACO05JAN] Muddy Fields G
## 题目描述

大雨侵袭了奶牛们的牧场。

牧场是一个 $R \times C$ 的矩形，其中 $1 \leq R,C \leq 50$。大雨将没有长草的土地弄得泥泞不堪，可是小心的奶牛们不想在吃草的时候弄脏她们的蹄子。为了防止她们的蹄子被弄脏，约翰决定在泥泞的牧场里放置一些木板。每一块木板的宽度为 $1$ 个单位，长度任意，每一个板必须放置在平行于牧场的泥地里。 

约翰想使用最少的木板覆盖所有的泥地．一个木板可以重叠在另一个木板上，但是不能放在草地上。
## 输入格式

第一行两个整数 $R,C$。

接下来 $R$ 行，每行 $C$ 个字符，描述牧场，其中 `*` 为泥地，`.` 为草地。
## 输出格式

输出一个整数，最少需要多少木板。
## 样例

### 样例输入 #1
```
4 4
*.*.
.***
***.
..*.
```
### 样例输出 #1
```
4
```


---

---
title: "[USACO05DEC] Cow Patterns G"
layout: "post"
diff: 省选/NOI-
pid: P6080
tag: ['2005', 'USACO']
---
# [USACO05DEC] Cow Patterns G
## 题目描述

Farmer John 的 $N$（$1 \leq N \leq 10^5$）头奶牛中出现了 $K$（$1 \leq K \leq 25000$）只坏蛋！这些坏蛋在奶牛排队的时候总站在一起。现在你需要帮助 FJ 找出他们。

为了区分，FJ 给每头奶牛发了号牌，上面写着一个 $1 \ldots S$ 之间的数字（$1 \leq S \leq 25$），虽然这不是个完美的方法，但也有一定作用。现在 FJ 记不得坏蛋们的具体号码，但他给出了一个模式串。原坏蛋的号码相同，模式串中的号码依旧相同，模式串中坏蛋号码的大小关系也和原号码相同。

例如模式串：$1,4,4,3,2,1$，原来的 $6$ 只坏蛋，最前面和最后面的号码相等且最小（不一定是 $1$），位置 $2,3$ 的坏蛋号码相同且最大（不一定是 $4$）。

现在有这样一个队列：$5, 6, 2, 10, 10, 7, 3, 2, 9$，它的子串 $2, 10, 10, 7, 3, 2$ 匹配模式串的相等关系和大小关系，这就可能是一个坏蛋团伙。

请找出所有团伙的可能情况。 
## 输入格式

第一行三个整数 $N,K,S$。

接下来 $N$ 行，每行一个整数，代表第 $i$ 奶牛的编号。

接下来 $K$ 行，每行一个整数，表示模式串中第 $i$ 个位置的号码。
## 输出格式

第一行输出一个整数 $B$。

接下来 $B$ 行，每行一个整数，为一种可能的坏蛋团伙的起始位置。

所有位置按升序输出。
## 样例

### 样例输入 #1
```
9 6 10
5
6
2
10
10
7
3
2
9
1
4
4
3
2
1
```
### 样例输出 #1
```
1
3
```


---

---
title: "[USACO20FEB] Help Yourself P"
layout: "post"
diff: 省选/NOI-
pid: P6144
tag: ['动态规划 DP', '2020', '线段树', 'USACO', 'Stirling 数']
---
# [USACO20FEB] Help Yourself P
## 题目描述

在一个数轴上有 $N$ 条线段，第 $i$ 条线段覆盖了从 $l_i$ 到 $r_i$ 的所有实数（包含 $l_i$ 和 $r_i$）。

定义若干条线段的**并**为一个包含了所有被至少一个线段覆盖的点的集合。

定义若干条线段的**复杂度**为这些线段的并形成的连通块的数目的 $K$ 次方。

现在 Bessie 想要求出给定 $N$ 条线段的所有子集（共有 $2^N$ 个）的复杂度之和对 $10^9+7$ 取模的结果。

你也许猜到了，你需要帮 Bessie 解决这个问题。但不幸的是，你猜错了！在这道题中你就是 Bessie，而且没有人来帮助你。一切就靠你自己了！
## 输入格式

第一行两个整数 $N$，$K$（$1 \leq N \leq 10^5$。$2 \leq K \leq 10$）。

接下来 $N$ 行，每行两个整数 $l_i,r_i$，描述一条线段。保证 $1 \leq l_i \lt r_i \leq 2N$，且任意两个端点都不在同一位置上。
## 输出格式

输出所求答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
3 2
1 6
2 3
4 5
```
### 样例输出 #1
```
10
```
## 提示

### 样例解释

所有非空子集的复杂度如下所示（显然空集的复杂度为零）：

$$
\{[1,6]\} \implies 1, \{[2,3]\} \implies 1, \{[4,5]\} \implies 1
$$

$$
\{[1,6],[2,3]\} \implies 1, \{[1,6],[4,5]\} \implies 1, \{[2,3],[4,5]\} \implies 4
$$

$$
\{[1,6],[2,3],[4,5]\} \implies 1
$$

故答案为 $1+1+1+1+1+4+1=10$。

### 子任务

- 测试点 $2$ 满足 $N \leq 16$；
- 测试点 $3 \sim 5$ 满足 $N \leq 10^3$，且 $K=2$；
- 测试点 $6 \sim 8$ 满足 $N \leq 10^3$；
- 对于测试点 $T$（$T \in [9,16]$），满足 $K=3+(T-9)$。


---

---
title: "[USACO16FEB] Circular Barn P"
layout: "post"
diff: 省选/NOI-
pid: P6173
tag: ['动态规划 DP', '2016', 'USACO', '分治', '动态规划优化', '斜率优化', '四边形不等式']
---
# [USACO16FEB] Circular Barn P
## 题目描述

作为当代建筑的爱好者，Farmer John 建造了一个圆形新谷仓，谷仓内部 $n$ 个房间排成环形（$3 \leq n \leq 1000$），按顺时针顺序编号为 $1\ldots n$，每个房间都有通往与其相邻的左右房间的门，还有一扇门通往外面。

FJ 准备让第 $i$ 个房间里恰好有 $r_i$ 头奶牛（$1 \le r_i \le {10}^6$）。为了有序地让奶牛进入谷仓，他打算解锁 $k$ 个从外界进入谷仓的门（$1 \le k \le 7$）。然后，每头奶牛**顺时针**走动，直到到达目的地。FJ 的目标是让所有奶牛走动的距离和最小（奶牛从哪个门进入可以随意安排，这里走动的距离只包含进入谷仓后走动的距离），现在请你求出这个最小距离。
## 输入格式

第一行两个整数 $n,k$。

接下来 $n$ 行，第 $i$ 行一个整数 $r_i$。
## 输出格式

输出所有奶牛最小走动距离和。
## 样例

### 样例输入 #1
```
6 2
2
5
4
2
6
2
```
### 样例输出 #1
```
14
```
## 提示

FJ 打开 $2,5$ 两个门。$11$ 头奶牛从 $2$ 号门进入，前往 $2,3,4$ 号房间，总距离 $8$。$10$ 头奶牛从 $5$ 号门进入，前往 $5,6,1$ 号房间，总距离 $6$。


---

---
title: "[USACO16JAN] Lights Out P"
layout: "post"
diff: 省选/NOI-
pid: P6176
tag: ['动态规划 DP', '2016', 'USACO']
---
# [USACO16JAN] Lights Out P
## 题目描述

Farmer John has installed a fancy new milking machine in his barn, but it draws so much power that it occasionally causes the power to go out! This happens so often that Bessie has memorized a map of the barn, making it easier for her to find the exit of the barn in the dark. She is curious though about the impact of power loss on her ability to exit the barn quickly. For example, she wonders how much farther she might need to walk find the exit in the dark.

The barn is described by a simple (non self-intersecting) polygon with integer vertices $(x_1,y_1)\ldots(x_n,y_n)$ listed in clockwise order. Its edges alternate between horizontal (parallel to the x-axis) and vertical (parallel to the y-axis); the first edge can be of either type. The exit is located at $(x_1,y_1)$. Bessie starts inside the barn located at some vertex $(x_i,y_i)$ for $i \gt 1$. She can walk only around the perimeter of the barn, either clockwise or counterclockwise, potentially changing direction any time she reaches a vertex. Her goal is to travel a minimum distance to reach the exit. This is relatively easy to do with the lights on, of course, since she will travel either clockwise or counterclockwise from her current location to the exit -- whichever direction is shorter.

One day, the lights go out, causing Bessie to panic and forget which vertex she is standing at. Fortunately, she still remembers the exact map of the barn, so she can possibly figure out her position by walking around and using her sense of touch. Whenever she is standing at a vertex (including at her initial vertex), she can feel whether it is a left turn or a right turn, and she can tell if that vertex is the exit. When she walks along an edge of the barn, she can determine the exact length of the edge after walking along the entire edge. In general, Bessie will strategically feel her way around her starting vertex until she knows enough information to determine where she is, at which point she can easily figure out how to get to the exit by traveling a minimum amount of remaining distance.

Please help Bessie determine the smallest possible amount by which her travel distance will increase in the worst case (over all possibilities for her starting vertex) for travel in the dark versus in a lit barn, assuming she moves according to an optimal strategy in each case. An "optimal" strategy for the unlit case is one that minimizes this extra worst-case amount.
## 输入格式

The first line of the input contains $N$ ($4 \leq N \leq 200$). Each of the next $N$ lines contains two integers, describing the points $(x_i,y_i)$ in clockwise order around the barn. These integers are in the range $-100,000 \ldots 100,000$.
## 输出格式

Please output the smallest possible worst-case amount by which Bessie's optimal distance in the dark is longer than her optimal distance in a lit barn, where the worst case is taken over all possible vertices at which Bessie can start.
## 样例

### 样例输入 #1
```
4
0 0
0 10
1 10
1 0
```
### 样例输出 #1
```
2
```
## 提示

In this example, Bessie can feel that she is initially standing at an inward bend, however since in this example all corners are inward bends this tells her little information.

One optimal strategy is to just travel clockwise. This is optimal is she starts at vertex 3 or 4 and only adds 2 units of distance if she starts at vertex 2.
## 题目翻译

### 题目描述

农夫约翰在他的谷仓里安装了一台新的挤奶机，但它耗电量太大，偶尔会导致停电！这种情况发生得如此频繁，以至于贝茜已经记住了谷仓的地图，这帮助她在黑暗中更容易找到出口。但她好奇停电会对她快速离开谷仓的能力产生多大影响。例如，她想知道在黑暗中寻找出口可能需要多走多少路。

谷仓由一个简单（无自交）多边形描述，其顶点按顺时针顺序排列为 $(x_1,y_1)\ldots(x_n,y_n)$。多边形的边在水平（平行于 $x$ 轴）和垂直（平行于 $y$ 轴）之间交替；第一条边可以是任意类型。出口位于 $(x_1,y_1)$。贝茜从某个顶点 $(x_i,y_i)$（$i > 1$）开始位于谷仓内部。她只能沿着谷仓的周边行走，可以顺时针或逆时针方向移动，并可在到达顶点时随时改变方向。她的目标是以最短距离到达出口。在有灯光的情况下这很容易，因为她只需从当前位置沿顺时针或逆时针中选择较短的方向行进即可。

某天停电时，贝茜因恐慌而忘记了自己所在的起始顶点。幸运的是，她仍清楚记得谷仓的地图，因此她可能通过行走并利用触觉来确定自己的位置。每当她站在一个顶点时（包括初始顶点），她可以感知该顶点是左转还是右转，并能判断该顶点是否是出口。当她沿着谷仓的边行走时，她可以在走完整条边后确定该边的精确长度。贝茜将策略性地探索周围环境，直到获得足够信息来确定自己的位置，之后她就能轻松计算出剩余的最短路径。

请帮助贝茜计算：在最优策略下，黑暗中最坏情况（考虑所有可能的起始顶点）下她的行走距离相比有灯光时可能增加的最小额外距离。这里的“最优策略”指能最小化这种最坏情况额外距离的策略。

### 输入格式

输入第一行包含 $N$（$4 \leq N \leq 200$）。接下来 $N$ 行每行包含两个整数，按顺时针顺序描述多边形顶点 $(x_i,y_i)$。这些整数的范围在 $-100,000$ 到 $100,000$ 之间。

### 输出格式

请输出在最优策略下，贝茜在黑暗中最坏情况（考虑所有可能的起始顶点）下的行走距离相比有灯光时可能增加的最小额外距离。

### 说明/提示

在此示例中，贝茜可以感知到自己初始位于一个内角处，但由于所有角都是内角，这提供的信息有限。

一种最优策略是始终顺时针行走。如果她从顶点 3 或 4 出发，这是最优选择；如果从顶点 2 出发，则只会增加 2 单位距离。


---

---
title: "[USACO06OPEN] The Milk Queue G"
layout: "post"
diff: 省选/NOI-
pid: P6243
tag: ['2006', 'USACO']
---
# [USACO06OPEN] The Milk Queue G
## 题目背景

题目是经过简写保证不改变原有题意的题目。
## 题目描述

每早，FJ 的 $N$ 头奶牛都排成一列挤奶．一个个进到仓库，为提高速率，FJ 把整个挤奶过程划分成两道工序，FJ负责实行第一道，第二道由 Rob 完成。

如果某头牛先于另一头牛开始进行第一道工序，那么她同样先开始第二道工序。

FJ 发现，如果奶牛们按某种顺序排队进行挤奶，那么可能会在排队等待上多花很多的时间。比如，如果 FJ 要花很长时间才能完成某头奶牛的第一道工序，那么 Rob 就会浪费一段时间。反之如果 FJ 的工作完成得太快，Rob 面前会有很多奶牛排起长队。

请你计算按最优方式排队后最少需要多少时间才能挤完奶。对于每头奶牛，数据提供第一道工序的时间 $A_i$ 和第二道工序的时间 $B_i$。
## 输入格式

第一行一个整数 $N$。

接下来 $N$ 行，每行两个整数表示第 $i$ 头牛的 $A_i$，$B_i$ 值。
## 输出格式

输出按最优方案排队后挤奶所需的最短时间。
## 样例

### 样例输入 #1
```
3
2 2
7 4
3 5
```
### 样例输出 #1
```
16
```
## 提示

#### 样例说明

把奶牛们按照 3，1，2  的顺序排队，这样挤奶总共花费 16 个单位时间．

$1\le N\le 25000$

$1\le A_i,B_i\le 2\times 10^4$


---

---
title: "[USACO20DEC] Bovine Genetics G"
layout: "post"
diff: 省选/NOI-
pid: P7152
tag: ['动态规划 DP', '2020', 'USACO', 'O2优化']
---
# [USACO20DEC] Bovine Genetics G
## 题目描述

Farmer John 在对他的奶牛进行基因组测序之后，他现在要进行基因组编辑了！我们知道，基因组可以用一个由 A、C、G、T 组成的字符串来表示。Farmer John 考虑的基因组的最大长度为 $10^5$。

Farmer John 从一个基因组开始，通过下列步骤对其进行编辑：

 1. 在所有连续相同字符之间的位置将当前基因组切开。
 2. 反转所有得到的子串。
 3. 按原先的顺序将反转的子串进行联结。

例如，如果 FJ 从基因组 AGGCTTT 开始，他会执行下列步骤：

 1. 在连续的 G 和 T 之间切开，得到 AG | GCT | T | T。
 2. 反转每一子串，得到 GA | TCG | T | T。
 3. 将这些子串联结起来，得到 GATCGTT。

不幸的是，在对基因组进行编辑之后，Farmer John 的计算机崩溃了，他丢失了他开始时的基因组序列。此外，编辑后的基因组的部分位置遭到了破坏，这些位置用问号代替。

给定编辑后的基因组序列，请帮助 FJ 求出可能的开始时的基因组序列的数量，对 $10^9+7$ 取模。 
## 输入格式

一个非空字符串，其中每个字符为 A、G、C、T 和 ? 之一。 
## 输出格式

输出可能的开始时的基因组序列的数量模 $10^9+7$ 的结果。
## 样例

### 样例输入 #1
```
?
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
GAT?GTT
```
### 样例输出 #2
```
3
```
## 提示

### 样例 2 解释：

除了在之前说明过的 AGGCTTT 之外，还有两种可能的开始时的基因组。

`AGGATTT -> AG | GAT | T | T -> GA | TAG | T | T -> GATAGTT`

`TAGGTTT -> TAG | GT | T | T -> GAT | TG | T | T -> GATTGTT`

### 测试点性质：


 - 测试点 1-4 中，基因组的长度不超过 $10$。
 - 测试点 5-11 中，基因组的长度不超过 $10^2$。
 - 测试点 12-20 没有额外限制。

供题：Benjamin Qi 


---

---
title: "[USACO20DEC] Square Pasture G"
layout: "post"
diff: 省选/NOI-
pid: P7153
tag: ['数学', '2020', 'USACO', 'O2优化', '排序', '双指针 two-pointer']
---
# [USACO20DEC] Square Pasture G
## 题目描述

Farmer John 最大的牧草地可以被看作是一个由方格组成的巨大的二维方阵（想象一个巨大的棋盘）。现在，有 $N$ 头奶牛正占据某些方格（$1≤N≤200$）。

Farmer John 想要建造一个可以包围一块正方形区域的栅栏；这个正方形必须四边与 $x$ 轴和 $y$ 轴平行，最少包含一个方格。请帮助他求出他可以包围在这样的区域内的不同的奶牛子集的数量。注意空集应当被计算为答案之一。 
## 输入格式

输入的第一行包含一个整数 $N$。以下 $N$ 行每行包含两个空格分隔的整数，表示一头奶牛所在方格的坐标 $(x,y)$。所有 $x$ 坐标各不相同，所有 $y$ 坐标各不相同。所有 $x$ 与 $y$ 的值均在 $0…10^9$ 范围内。

注意尽管所有奶牛所在的方格坐标均非负，但围成的正方形区域可以包含坐标为负的方格。
## 输出格式

输出 FJ 可以包围的奶牛的子集数量。可以证明这个数量可以用 32 位有符号整数型存储。 
## 样例

### 样例输入 #1
```
4
0 2
2 3
3 1
1 0

```
### 样例输出 #1
```
14
```
### 样例输入 #2
```
16
17 4
16 13
0 15
1 19
7 11
3 17
6 16
18 9
15 6
11 7
10 8
2 1
12 0
5 18
14 5
13 2
```
### 样例输出 #2
```
420
```
## 提示

 - 测试点 1-5 中，所有奶牛所在的方格的坐标均小于 20 。
 - 测试点 6-10 中，$N≤20$。
 - 测试点 11-20 没有额外限制。

供题：Benjamin Qi 



---

---
title: "[USACO20DEC] Sleeping Cows P"
layout: "post"
diff: 省选/NOI-
pid: P7154
tag: ['动态规划 DP', '2020', 'USACO', 'O2优化', '组合数学']
---
# [USACO20DEC] Sleeping Cows P
## 题目描述


Farmer John 有 $N$（$1≤N≤3000$）头各种大小的奶牛。他原本为每头奶牛量身定制了牛棚，但现在某些奶牛长大了，使得原先的牛棚大小不够用。具体地说，FJ 原来建造了 $N$ 个牛棚的大小为 $t_1,t_2,…,t_N$，现在奶牛的大小为 $s_1,s_2,…,s_N$（$1≤s_i,t_i≤10^9$）。

每天晚上，奶牛们都会按照某种方式寻找睡觉的牛棚。奶牛 $i$ 可以睡在牛棚 $j$ 中当且仅当她的大小可以进入牛棚（$s_i≤t_j$）。每个牛棚中至多可以睡一头奶牛。

我们称奶牛与牛棚的一个匹配是极大的，当且仅当每头奶牛可以进入分配给她的牛棚，且对于每头未被分配牛棚的奶牛无法进入任何未分配的空牛棚。

计算极大的匹配的数量模 $10^9+7$ 的结果。 
## 输入格式

输入的第一行包含 $N$。

第二行包含 $N$ 个空格分隔的整数 $s_1,s_2,…,s_N$。

第三行包含 $N$ 个空格分隔的整数 $t_1,t_2,…,t_N$。 
## 输出格式

输出极大的匹配的数量模 $10^9+7$ 的结果。 
## 样例

### 样例输入 #1
```
4
1 2 3 4
1 2 2 3
```
### 样例输出 #1
```
9
```
## 提示

以下是全部九种极大的匹配。有序对 $(i,j)$ 表示奶牛 $i$ 被分配到了牛棚 $j$。

```
(1, 1), (2, 2), (3, 4)
(1, 1), (2, 3), (3, 4)
(1, 1), (2, 4)
(1, 2), (2, 3), (3, 4)
(1, 2), (2, 4)
(1, 3), (2, 2), (3, 4)
(1, 3), (2, 4)
(1, 4), (2, 2)
(1, 4), (2, 3)
```

 - 测试点 2-3 中，$N≤8$。
 - 测试点 4-12 中，$N≤50$。
 - 测试点 13-20 没有额外限制。

供题：Nick Wu 


---

---
title: "[USACO21FEB] Modern Art 3 G"
layout: "post"
diff: 省选/NOI-
pid: P7414
tag: ['USACO', '2021', 'O2优化']
---
# [USACO21FEB] Modern Art 3 G
## 题目描述

厌倦了常规的二维画作（同时也由于作品被他人抄袭而感到失落），伟大的奶牛艺术家牛加索决定转变为更为极简主义的一维风格。她的最新画作可以用一个长为 $N$（$1 \leq N \leq 300$）的一维数组来描述，其中每种颜色用 $1\ldots N$ 中的一个整数表示。

令牛加索感到沮丧的是，尽管这样，她的竞争对手哞奈似乎已经发现了如何抄袭她的这些一维画作！哞奈会用一种颜色涂在一个区间上，等待颜料干了再涂另一个区间，以此类推。哞奈可以使用 $N$ 中颜色中的每一种任意多次（也可以不用）。

请计算哞奈抄袭牛加索的最新一维画作所需要的涂色的次数。
## 输入格式

输入的第一行包含 $N$。

下一行包含 $N$ 个范围在 $1 \ldots N$ 之内的整数，表示牛加索的最新一维画作每个方格上的颜色。
## 输出格式

输出抄袭这一画作所需要的最小涂色次数。
## 样例

### 样例输入 #1
```
10
1 2 3 4 1 4 3 2 1 6
```
### 样例输出 #1
```
6
```
## 提示

#### 样例 1 解释：


在这个样例中，哞奈可以按下列方式进行涂色。我们用 $0$ 表示一个未涂色的方格。

 - 初始时，整个数组均未被涂色：`0 0 0 0 0 0 0 0 0 0`
 - 哞奈将前九个方格涂上颜色 $1$：`1 1 1 1 1 1 1 1 1 0`
 - 哞奈在一个区间上涂上颜色 $2$：`1 2 2 2 2 2 2 2 1 0`
 - 哞奈在一个区间上涂上颜色 $3$：`1 2 3 3 3 3 3 2 1 0`
 - 哞奈在一个区间上涂上颜色 $4$：`1 2 3 4 4 4 3 2 1 0`
 - 哞奈在一个方格上涂上颜色 $1$：`1 2 3 4 1 4 3 2 1 0`
 - 哞奈在最后一个方格上涂上颜色 $6$：`1 2 3 4 1 4 3 2 1 6 `

注意在第一次涂色时，哞奈可以同时在前九个方格之外将第十个方格也同时涂上颜色 $1$，这并不会影响最后的结果。

#### 测试点性质：

 - 对于另外 $15\%$ 的数据，画作中仅出现颜色 $1$ 和 $2$。
 - 对于另外 $30\%$ 的数据，对于每一个 $1\le i\le N$，第 $i$ 个方格的颜色在范围 $\left[12\left\lfloor\frac{i-1}{12}\right\rfloor+1,12\left\lfloor\frac{i-1}{12}\right\rfloor+12\right]$ 之内。
 - 对于另外 $50\%$ 的数据，没有额外限制。

供题：Brian Dean，Benjamin Qi


---

---
title: "[USACO21OPEN] Permutation G"
layout: "post"
diff: 省选/NOI-
pid: P7529
tag: ['动态规划 DP', 'USACO', '2021']
---
# [USACO21OPEN] Permutation G
## 题目描述

Bessie 在二维平面上有 $N$ 个最爱的不同的点，其中任意三点均不共线。对于每一个 $1\le i\le N$，第 $i$ 个点可以用两个整数 $x_i$ 和 $y_i$ 表示。

Bessie 按如下方式在这些点之间画一些线段：

- 1. 她选择这 $N$ 个点的某个排列 $p_1,p_2,\dots,p_N$ 。
- 2. 她在点 $p_1$ 和 $p_2$ 、$p_2$ 和 $p_3$、$p_3$ 和 $p_1$ 之间画上线段。
- 3. 然后依次对于从 $4$ 到 $N$ 的每个整数 $i$，对于所有 $j<i$，她从 $p_i$ 到 $p_j$ 画上一条线段，只要这条线段不与任何已经画上的线段相交（端点位置相交除外）。

Bessie 注意到对于每一个 $i$ ，她都画上了恰好三条新的线段。计算 Bessie 在第 $1$ 步可以选择的满足上述性质的排列的数量，结果对 $10^9+7$ 取模。 
## 输入格式

输入的第一行包含 $N$。

以下 $N$ 行，每行包含两个空格分隔的整数 $x_i$ 和 $y_i$。 
## 输出格式

输出一行一个整数表示方案数对 $10^9+7$ 取模后的结果。
## 样例

### 样例输入 #1
```
4
0 0
0 4
1 1
1 2
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
4
0 0
0 4
4 0
1 1
```
### 样例输出 #2
```
24
```
### 样例输入 #3
```
5
0 0
0 4
4 0
1 1
1 2
```
### 样例输出 #3
```
96
```
## 提示

#### 样例一解释

没有排列满足该性质

#### 样例二解释

所有排列均满足该性质

#### 样例解释三

一个满足该性质的排列为 $(0,0),(0,4),(4,0),(1,2),(1,1)$ 。对于这个排列，

- 首先，她在 $(0,0),(0,4)$ 和 $(4,0)$ 两两之间画上线段。
- 然后她从 $(1,2)$ 向 $(0,0)$ ，$(0,4)$ 和 $(4,0)$ 画上线段。
- 最后，她从 $(1,1)$ 向 $(1,2)$ ，$(4,0)$ 和 $(0,0)$ 画上线段。 

![](http://usaco.org/current/data/fig_permutation_gold_open21.png)

### 数据范围与约定

$3\le N \le 40$，$0\le x_i,y_i \le 10^4$


---

---
title: "[USACO21OPEN] United Cows of Farmer John P"
layout: "post"
diff: 省选/NOI-
pid: P7530
tag: ['线段树', 'USACO', '2021', '扫描线']
---
# [USACO21OPEN] United Cows of Farmer John P
## 题目描述

农夫约翰合牛国（The United Cows of Farmer John，UCFJ）将要选派一个代表队参加国际牛学奥林匹克（International bOvine olympIad，IOI）。

有 $N$ 头奶牛参加了代表队选拔。她们站成一行，奶牛 $i$ 的品种为 $b_i$。

代表队将会由包含至少三头奶牛的连续区间组成——也就是说，对于满足 $1\le l<r\le N$ 且 $r−l\ge 2$ 的奶牛 
$l\dots r$。选定区间内的三头奶牛将会被指定为领队。出于法律原因，最边上的两头奶牛必须是领队。此外，为了避免种内冲突，每一名领队都必须与代表队的其他成员（包括领队）品种不同。

请帮助 UCFJ 求出（由于纳税原因）他们可以选派参加 IOI 的代表队的方法数。如果两个代表队拥有不同的成员或不同的领队，则被认为是不同的。 
## 输入格式

输入的第一行包含 $N$。

第二行包含 $N$ 个整数 $b_1,b_2,\dots,b_N$，均在范围 $[1,N]$ 之间。
## 输出格式

输出一行一个整数表示可能的代表队的数量。
## 样例

### 样例输入 #1
```
7
1 2 3 4 3 2 5
```
### 样例输出 #1
```
9
```
## 提示

#### 样例解释

每一代表队对应以下的一组领队：

$$(1,2,3),(1,2,4),(1,3,4),(1,4,7),(2,3,4),(4,5,6),(4,5,7),(4,6,7),(5,6,7).$$

#### 数据范围与约定

$1\le N\le 2\times 10^5$


---

---
title: "[USACO21OPEN] Balanced Subsets  P"
layout: "post"
diff: 省选/NOI-
pid: P7532
tag: ['动态规划 DP', 'USACO', '2021', '前缀和']
---
# [USACO21OPEN] Balanced Subsets  P
## 题目描述

Farmer John 的草地可以被看作是由正方形方格组成的巨大的二维方阵（想象一个巨大的棋盘），对于每一个 $1≤i≤N$、$1≤j≤N$，方格可以用有序对 $(i,j)$ 表示。某些方格中含有草。

方格的一个非空子集被称为是「平衡的」，如果以下条件成立：

- 1. 所有子集中的方格均含有草。
- 2. 子集是四连通的。换句话说，从子集中的任一方格到另一方格均存在一条路径使得路径中的相邻方格均水平或竖直方向上相邻。
- 3. 如果方格 $(x_1,y)$ 和 $(x_2,y)$（$x_1≤x_2$）存在于子集中，那么所有满足 $x_1≤x≤x_2$ 的方格 $(x,y)$ 也存在于子集中。
- 4. 如果方格 $(x,y_1)$ 和 $(x,y_2)$（$y_1≤y_2$）存在于子集中，那么所有满足 $y_1≤y≤y_2$ 的方格 $(x,y)$ 也存在于子集中。

计算平衡的子集数量模 $10^9+7$ 的结果。
## 输入格式

输入的第一行包含 $N$。

以下 $N$ 行每行包含一个长为 $N$ 的字符串。如果方格 $(i,j)$ 中有草，则第 $i$ 行的第 $j$ 个字符为 $\texttt{G}$，否则为$\texttt{.}$。 
## 输出格式

输出平衡的子集数量模 $10^9+7$ 的结果。 
## 样例

### 样例输入 #1
```
2
GG
GG
```
### 样例输出 #1
```
13
```
### 样例输入 #2
```
4
GGGG
GGGG
GG.G
GGGG
```
### 样例输出 #2
```
642
```
## 提示

#### 样例一解释

对于这个测试用例，所有的四连通子集均是平衡的。

```
G.  .G  ..  ..  GG  .G  ..  G.  GG  .G  G.  GG  GG
.., .., G., .G, .., .G, GG, G., G., GG, GG, .G, GG
```

#### 样例二解释

以下是一个符合第二个条件（四连通）但不符合第三个条件的子集的例子： 

```
GG..
.G..
GG..
....
```

#### 数据范围与约定

$1\le N \le 150$ 。


---

---
title: "[USACO21DEC]  Tickets P"
layout: "post"
diff: 省选/NOI-
pid: P7984
tag: ['动态规划 DP', '线段树', 'USACO', '2021', '图论建模', '最短路']
---
# [USACO21DEC]  Tickets P
## 题目描述

Bessie 正在参加远足旅行！她当前正在旅行的路线由编号为 $1\ldots N$（$1\le N\le 10^5$）的 $N$ 个检查点组成。

有 $K$（$1\le K\le 10^5$）张票可供购买。第 $i$ 张票可以在检查站 $c_i$（$1\le c_i\le N$）以 $p_i$（$1\le p_i\le 10^9$）的价格购得，并且可以用其进入所有检查站 $[a_i,b_i]$（$1\le a_i\le b_i\le N$）。在进入任何检查站之前，Bessie 必须已购买一张允许其进入该检查站的票。一旦 Bessie 可以前往某一检查站，她就可以在未来的任何时候回到该检查站。

对于每一个 $i\in [1,N]$，如果 Bessie 最初只能进入检查点 $i$，输出使得可以进入检查点 $1$ 和 $N$ 所需的最低总价。如果无法这样做，输出 $-1$。

## 输入格式

输入的第一行包含 $N$ 和 $K$。

以下 $K$ 行，对于每一个 $1\le i\le K$，第 $i$ 行包含四个整数 $c_i$，$p_i$，$a_i$ 和 $b_i$。
## 输出格式

输出 $N$ 行，每行输出一个检查点的答案。
## 样例

### 样例输入 #1
```
7 6
4 1 2 3
4 10 5 6
2 100 7 7
6 1000 1 1
5 10000 1 4
6 100000 5 6
```
### 样例输出 #1
```
-1
-1
-1
1111
10100
110100
-1
```
## 提示

【样例解释】

如果 Bessie 从检查点 $i=4$ 开始，那么一种购得进入检查点 $1$ 和 $N$ 的方法如下：

在检查点 $4$ 购买第一张票，使 Bessie 可以进入检查点 $2$ 和 $3$。

在检查点 $2$ 购买第三张票，使 Bessie 可以进入检查点 $7$。

回到检查点 $4$ 购买第二张票，使 Bessie 可以进入检查点 $5$ 和 $6$。

在检查点 $6$ 购买第四张票，使 Bessie 可以进入检查点 $1$。

【数据范围】

- 测试点 1-7 满足 $N,K\le 1000$。
- 测试点 8-19 没有额外限制。



---

---
title: "[USACO21DEC] Paired Up P"
layout: "post"
diff: 省选/NOI-
pid: P7985
tag: ['动态规划 DP', 'USACO', '2021', '动态规划优化']
---
# [USACO21DEC] Paired Up P
## 题目描述

数轴上总计有 $N$（$1\le N\le 5000$）头奶牛，每一头奶牛都是荷斯坦牛（Holstein）或更赛牛（Guernsey）之一。第 $i$ 头奶牛的品种为 $b_i\in \{H,G\}$，第 $i$ 头奶牛的位置为 $x_i$（$0 \leq x_i \leq 10^9$），而第 $i$ 头奶牛的重量为 $y_i$（$1 \leq y_i \leq 10^5$）。

根据 Farmer John 的信号，某些奶牛会组成对，使得

- 每一对包含位置相差不超过 $K$ 的一头荷斯坦牛 $h$ 和一头更赛牛 $g$（$1\le K\le 10^9$）；也就是说，$|x_h-x_g|\le K$。

- 每一头奶牛要么包含在恰好一对中，要么不属于任何一对。
- 配对是**极大的**；也就是说，没有两头未配对的奶牛可以组成对。

你需要求出未配对的奶牛的重量之和的可能的范围。具体地说，

- 如果 $T=1$，计算未配对的奶牛的最小重量和。

- 如果 $T=2$，计算未配对的奶牛的最大重量和。
## 输入格式

输入的第一行包含 $T$，$N$ 和 $K$。

以下 $N$ 行，第 $i$ 行包含 $b_i,x_i,y_i$。输入保证 $0\le x_1<x_2<\cdots<x_{N}\le 10^9$。
## 输出格式

输出未配对的奶牛的最小或最大重量和。
## 样例

### 样例输入 #1
```
2 5 4
G 1 1
H 3 4
G 4 2
H 6 6
H 8 9
```
### 样例输出 #1
```
16
```
### 样例输入 #2
```
1 5 4
G 1 1
H 3 4
G 4 2
H 6 6
H 8 9
```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
2 10 76
H 1 18
H 18 465
H 25 278
H 30 291
H 36 202
G 45 96
G 60 375
G 93 941
G 96 870
G 98 540
```
### 样例输出 #3
```
1893
```
## 提示

【样例解释1】

奶牛 $2$ 和 $3$ 可以配对，因为她们的距离为 $1$，不超过 $K = 4$。这个配对方案是极大的，因为奶牛 $1$，唯一余下的更赛牛，和奶牛 $4$ 的距离为 $5$，和奶牛 $5$ 的距离为 $7$，均大于 $K = 4$。未配对的奶牛的重量和为 $1 + 6 + 9 = 16$。

【样例解释2】

奶牛 $1$ 和 $2$ 可以配对，因为她们的距离为 $2 \leq K = 4$，同时奶牛 $3$ 和 $5$ 可以配对，因为她们的距离为 $4 \leq K = 4$。这个配对方案是极大的，因为只剩下了奶牛 $4$。未配对的奶牛的重量和即为唯一未配对的奶牛的重量，即为 $6$。

【样例解释3】

这个例子的答案为 $18+465+870+540=1893$。

【数据范围】

- 测试点 4-7 满足 $T=1$；
- 测试点 8-14 满足 $T=2$ 且 $N\le 300$；
- 测试点 15-22 满足 $T=2$。

**注意：本题的内存限制为 $\text{512MB}$，是通常限制的两倍。**



---

---
title: "[USACO21DEC] HILO P"
layout: "post"
diff: 省选/NOI-
pid: P7986
tag: ['动态规划 DP', '数学', 'USACO', '2021', '期望']
---
# [USACO21DEC] HILO P
## 题目描述

Bessie 有一个数 $x+0.5$，其中 $x$ 是某个 $0$ 到 $N$ 之间的整数（$1\le N\le 5000$）。

Elsie 正试着猜这个数。她可以以如下形式对于某个 $1$ 到 $N$ 之间的整数提问：「$i$ 是大了还是小了？」如果 $i$ 大于 $x+0.5$，Bessie 会回答 "HI!"，如果 $i$ 小于 $x+0.5$ 则回答 "LO!"。

Elsie 想到了以下猜测 Bessie 的数的策略。在进行任何猜测之前，她创建了一个包含 $N$ 个整数的序列，其中从 $1$ 到 $N$ 的每个数均恰好出现一次（换句话说，这个序列是长为 $N$ 的一个排列）。然后她遍历这一列表，按列表中的数的顺序依次猜数。然而，Elsie 会跳过所有不必要的猜测。也就是说，如果 Elsie 将要猜某个数 $i$，而 Elsie 之前已经猜过了某个 $j < i$ 并且 Bessie 回答 "HI!"，Elsie 不会再猜 $i$，而是继续猜序列中的下一个数。类似地，如果她将要猜某个数 $i$，而她之前已经猜过了某个 $j > i$ 并且 Bessie 回答 "LO!"，Elsie 不会再猜 $i$，而是继续猜序列中的下一个数。可以证明，使用这一策略，对于 Elsie 创建的任意序列，她都可以唯一确定 $x$。

如果我们将所有 Bessie 回答的 "HI" 或 "LO" 拼接成一个字符串 $S$，那么 Bessie 说 "HILO" 的次数为 $S$ 等于 "HILO" 的长为 $4$ 的子串数量。

Bessie 知道 Elsie 将要使用这一策略，并且已经选定了值 $x$，但她不知道 Elsie 会使用什么排列。你的目标是对于所有 Elsie 可能选用的排列，计算 Bessie 说 "HILO" 的次数之和，对 $10^9+7$ 取模。
## 输入格式

输入一行，包含 $N$ 和 $x$。
## 输出格式

输出 HILO 的总数，对 $10^9+7$ 取模。
## 样例

### 样例输入 #1
```
4 2
```
### 样例输出 #1
```
17
```
### 样例输入 #2
```
60 10
```
### 样例输出 #2
```
508859913
```
## 提示

【样例解释1】

在这个测试用例中，Bessie 的数是 $2.5$。

例如，如果 Elsie 的排列是 $(4,1,3,2)$，那么 Bessie 会说 ""HILOHILO"，总计两次 "HILO"。又例如，如果 Elsie 的排列是 $(3,1,2,4)$，那么 Bessie 会说 "HILOLO"，总计一次 "HILO"。

【样例解释2】

确保输出总和对 $10^9+7$ 取模的结果。

【数据范围】

- 测试点 3-10 满足 $N\le 50$；
- 测试点 11-18 满足 $N\le 500$；
- 测试点 19-26 没有额外限制。


---

---
title: "[USACO22JAN] Tests for Haybales G"
layout: "post"
diff: 省选/NOI-
pid: P8098
tag: ['数学', 'USACO', '2022', 'Special Judge', '构造']
---
# [USACO22JAN] Tests for Haybales G
## 题目描述

Farmer John 的奶牛们决定为 Farmer Nhoj 农场的奶牛们举办一场编程竞赛。为了使问题尽可能有趣，他们花费了大量时间来构造具有挑战性的测试用例。特别是对于一个问题，「Haybales」，奶牛们需要你的帮助来设计具有挑战性的测试用例。这有关解决以下这个有些奇妙的问题：

有一个有序整数数组 $x_1 \leq x_2 \leq \dotsb \leq x_N$（$1 \leq N \leq 10^5$），和一个整数 $K$。你不知道这个数组以及 $K$，但你知道对于每个索引 $i$ 使得 $x_{j_i} \leq x_i + K$ 的最大索引 $j_i$。保证有 $i\le j_i$ 以及 $j_1\le j_2\le \cdots \le j_N\le N$。

给定这些信息，Farmer John 的奶牛需要构造任意一个数组以及整数 $K$ 与该信息一致。构造需要满足对于所有 $i$ 有 $0 \leq x_i \leq 10^{18}$，并且 $1 \leq K \leq 10^{18}$。

可以证明这一定是可行的。请帮助 Farmer John 的奶牛们解决这一问题！
## 输入格式

输入的第一行包含 $N$。第二行包含 $j_1,j_2,\ldots,j_N$。
## 输出格式

输出 $K$，然后在下一行输出 $x_1,\ldots,x_N$。任何合法的输出均正确。
## 样例

### 样例输入 #1
```
6
2 2 4 5 6 6
```
### 样例输出 #1
```
6
1
6
17
22
27
32
```
## 提示

【样例解释】

输出样例为数组 $a=[1,6,17,22,27,32]$ 以及 $K=6$。 $j_1=2$ 被满足是由于 $a_2=6 \le 1+6=a_1+K$ 而 $a_3=17>1+6=a_1+K$，从而 $a_2$ 是最大的不超过 $a_1+K$ 的元素。类似地：

- $j_2=2$ 被满足是由于 $a_2=6 \le 6+6$ 而 $a_3=17>6+6$；
- $j_3=4$ 被满足是由于 $a_4=22 \le 17+6$ 而 $a_5=27>17+6$；
- $j_4=5$ 被满足是由于 $a_5=27 \le 22+6$ 而 $a_5=32>22+6$；
- $j_5=6$ 被满足是由于 $a_6=32 \le 27+6$ 且 $a_6$ 是数组的最后一个元素；
- $j_6=6$ 被满足是由于 $a_6=32 \le 32+6$ 且 $a_6$ 是数组的最后一个元素。

对于输入样例，这并不是唯一正确的输出。例如，你也可以输出数组 $[1,2,4,5,6,7]$ 和 $K=1$。

【数据范围】

- 所有测试点的 $50\%$ 满足 $N \le 5000$。
- 其余测试点没有额外限制。

【说明】

本题采用自行编写的 [Special Judge](https://www.luogu.com.cn/paste/kzgvkesl)。如果对此有疑问或想要 hack，请[私信编写者](https://www.luogu.com.cn/chat?uid=137367)或[发帖](https://www.luogu.com.cn/discuss/lists?forumname=P8098)。


---

---
title: "[USACO22JAN] Counting Haybales P"
layout: "post"
diff: 省选/NOI-
pid: P8100
tag: ['动态规划 DP', 'USACO', '2022']
---
# [USACO22JAN] Counting Haybales P
## 题目描述

如同往常一样，奶牛 Bessie 正在 Farmer John 的牛棚里制造麻烦。FJ 有 $N$（$1 \le N \le 5000$）堆草堆。对于每个 $i \in [1,N]$，第 $i$ 堆草堆有 $h_i$（$1 \le h_i \le 10^9$）的草。Bessie 不想让任何的草倒下来，所以她唯一可以执行的操作为：

如果两个相邻的草堆的高度相差恰好为 $1$，她可以将较高的草堆中最上方的草移到较低的草堆之上。

执行有限多次上述操作后，可以得到多少种不同的高度序列，对 $10^9+7$ 取模？两个高度序列被认为是相同的，如果对于所有 $i$，第 $i$ 堆草堆在两者中具有相同数量的草。
## 输入格式

输入的第一行包含 $T$，为独立的子测试用例的数量，必须全部回答正确才能通过整个测试用例。

每个子测试用例包含 $N$，以及一个 $N$ 个高度的序列。输入保证所有子测试用例的 $N$ 之和不超过 $5000$。
## 输出格式

输出 $T$ 行，每行输出一个子测试用例的答案。
## 样例

### 样例输入 #1
```
7
4
2 2 2 3
4
3 3 1 2
4
5 3 4 2
6
3 3 1 1 2 2
6
1 3 3 4 1 2
6
4 1 2 3 5 4
10
1 5 6 6 6 4 2 3 2 5
```
### 样例输出 #1
```
4
4
5
15
9
8
19
```
## 提示

【样例解释】

对于第一个子测试用例，四个可能的高度序列为：

$(2,2,2,3),(2,2,3,2),(2,3,2,2),(3,2,2,2)$

对于第二个子测试用例，四个可能的高度序列为：

$(2,3,3,1),(3,2,3,1),(3,3,2,1),(3,3,1,2)$

【数据范围】

- 测试点 1-3 满足 $N \le 10$。
- 测试点 4 满足对于所有 $i$，有 $1 \le h_i \le 3$。
- 测试点 5-7 满足对于所有 $i$，有 $|h_i-i| \le 1$。
- 测试点 8-10 满足对于所有 $i$，有 $1 \le h_i \le 4$，且 $N \le 100$。
- 测试点 11-13 满足 $N \le 100$。
- 测试点 14-17 满足 $N \le 1000$。
- 测试点 18-21 没有额外限制。

供题：Daniel Zhang


---

---
title: "[USACO22JAN] Multiple Choice Test P"
layout: "post"
diff: 省选/NOI-
pid: P8101
tag: ['USACO', '2022', '凸包', '极角排序']
---
# [USACO22JAN] Multiple Choice Test P
## 题目描述

奶牛们正在参加一个选择题测试。在通常的测试中，对每个问题你的选项会被单独评分然后累加，而在此测试中，你的选项在累加之后再评分。

具体地说，你被给定二维平面上的 $N$（$2 \le N \le 10^5$）组整数向量，其中每个向量用一个有序对 $(x,y)$ 表示。从每组中选择一个向量，使向量的总和尽可能远离原点。

输入保证向量的总数不超过 $2 \times 10^5$。每组至少包含 $2$ 个向量，并且一组内所有向量各不相同。输入同时保证每个 $x$ 和 $y$ 坐标的绝对值不超过 $\dfrac{10^9}{N}$。
## 输入格式

输入的第一行包含 $N$，为向量的组数。

每一组的第一行包含 $G$，为组中的向量数。以下 $G$ 行包含组中的向量。相邻组之间用空行分隔。
## 输出格式

输出最大可能的欧几里得距离的平方。
## 样例

### 样例输入 #1
```
3

2
-2 0
1 0

2
0 -2
0 1

3
-5 -5
5 1
10 10
```
### 样例输出 #1
```
242
```
## 提示

【样例解释】

最优方案是从第一组选择 $(1,0)$，从第二组中选择 $(0,1)$，从第三组选择 $(10,10)$。这些向量之和等于 $(11,11)$，与原点的距离平方等于 $11^2+11^2=242$。

【数据范围】

- 测试点 1-5 中，向量的总数不超过 $10^3$。
- 测试点 6-9 中，每一组恰好包含 $2$ 个向量。
- 测试点 10-17 没有额外限制。

供题：Benjamin Qi


---

---
title: "[USACO22FEB] Redistributing Gifts G"
layout: "post"
diff: 省选/NOI-
pid: P8189
tag: ['USACO', '2022', '组合数学', '状压 DP']
---
# [USACO22FEB] Redistributing Gifts G
## 题目描述

Farmer John has $N$ gifts labeled $1…N$ for his $N$ cows, also labeled $1…N$ $(1≤N≤18)$. Each cow has a wishlist, which is a permutation of all $N$ gifts such that the cow prefers gifts that appear earlier in the list over gifts that appear later in the list.

FJ was lazy and just assigned gift $i$ to cow $i$ for all $i$. Now, the cows have gathered amongst themselves and decided to reassign the gifts such that after reassignment, every cow ends up with the same gift as she did originally, or a gift that she prefers over the one she was originally assigned.

There is also an additional constraint: a gift may only be reassigned to a cow if it was originally assigned to a cow of the same type (each cow is either a Holstein or a Guernsey). Given $Q$ $(1≤Q≤min(10^5,2^N))$ length-$N$ breed strings, for each one count the number of reassignments that are consistent with it.
## 输入格式

The first line contains $N$.
The next $N$ lines each contain the preference list of a cow. It is guaranteed that each line forms a permutation of $1…N$.

The next line contains $Q$.

The final $Q$ lines each contain a breed string, each $N$ characters long and consisting only of the characters G and H. No breed string occurs more than once.
## 输出格式

For each breed string, print the number of reassignments that are consistent with it on a new line.
## 样例

### 样例输入 #1
```
4
1 2 3 4
1 3 2 4
1 2 3 4
1 2 3 4
5
HHHH
HHGG
GHGH
HGGG
GHHG
```
### 样例输出 #1
```
2
1
1
2
2
```
## 提示

【样例解释】

In this example, for the first breed string, there are two possible reassignments:

- The original assignment: cow $1$ receives gift $1$, cow $2$ receives gift $2$, cow $3$ receives gift $3$, and cow $4$ receives gift $4$.
- Cow $1$ receives gift $1$, cow $2$ receives gift $3$, cow $3$ receives gift
$2$, and cow $4$ receives gift $4$.

【数据范围】

- For $T=2,\cdots ,13$, test case T satisfies $N=T+4$.
- Test cases 14-18 satisfy $N=18$.
## 题目翻译

### 题目描述

Farmer John 有 $N$ 个礼物，编号为 $1 \ldots N$，准备分给他的 $N$ 头奶牛，奶牛也编号为 $1 \ldots N$（$1 \leq N \leq 18$）。每头奶牛有一个愿望清单，清单是 $N$ 个礼物的一个排列，奶牛更喜欢清单中靠前的礼物。

FJ 很懒，直接将礼物 $i$ 分配给了奶牛 $i$。现在，奶牛们聚集在一起，决定重新分配礼物，使得重新分配后，每头奶牛最终得到的礼物要么与原来相同，要么是她更喜欢的礼物。

还有一个额外的限制：一个礼物只能重新分配给与它原主人同类型的奶牛（每头奶牛要么是荷斯坦牛，要么是根西牛）。给定 $Q$（$1 \leq Q \leq \min(10^5, 2^N)$）个长度为 $N$ 的品种字符串，对于每个字符串，计算符合该字符串的重新分配方案的数量。

### 输入格式

第一行包含 $N$。  
接下来的 $N$ 行，每行包含一头奶牛的愿望清单。保证每行是 $1 \ldots N$ 的一个排列。  
接下来一行包含 $Q$。  
最后的 $Q$ 行，每行包含一个品种字符串，长度为 $N$，仅由字符 `G` 和 `H` 组成。每个品种字符串只出现一次。

### 输出格式

对于每个品种字符串，输出一行，表示符合该字符串的重新分配方案的数量。

### 样例解释

在这个例子中，对于第一个品种字符串，有两种可能的重新分配方案：

1. 原始分配：奶牛 $1$ 得到礼物 $1$，奶牛 $2$ 得到礼物 $2$，奶牛 $3$ 得到礼物 $3$，奶牛 $4$ 得到礼物 $4$。
2. 奶牛 $1$ 得到礼物 $1$，奶牛 $2$ 得到礼物 $3$，奶牛 $3$ 得到礼物 $2$，奶牛 $4$ 得到礼物 $4$。

### 数据范围

- 对于 $T = 2, \cdots ,13$，测试用例 $T$ 满足 $N = T + 4$。
- 测试用例 14-18 满足 $N = 18$。


---

---
title: "[USACO22FEB] Sleeping in Class P"
layout: "post"
diff: 省选/NOI-
pid: P8193
tag: ['贪心', 'USACO', '2022', '数论', '素数判断,质数,筛法', '前缀和']
---
# [USACO22FEB] Sleeping in Class P
## 题目描述

最近终于线下授课了，奶牛 Bessie 十分兴奋！不幸的是，Farmer John 是一个非常无聊的讲师，因此她经常课堂上睡觉。

Farmer John 注意到了 Bessie 上课走神。他要求班上的另一个学生 Elsie 跟踪记录给定课上 Bessie 睡觉的次数。一共有 $N$ 堂课，Elsie 记录下了 Bessie 在第 $i$ 堂课睡了 $a_i$ 次。所有课上 Bessie 一共睡觉的次数最多为 $10^{18}$。

Elsie 认为自己是 Bessie 的竞争对手，所以她想让 FJ 觉得在每堂课上 Bessie 都一直睡了同样多次——让 FJ 觉得这个问题显然完全是 Bessie 的错，而不是 FJ 有时上课很无聊的问题。

Elsie 修改记录只有以下两种方式：把两堂课的记录合起来，或者把一堂课的记录分成两堂课。例如，如果 $a=[1,2,3,4,5]$，那么如果 Elsie 将第二堂和第三堂课的记录合起来，记录就会变为 $[1,5,4,5]$。如果 Elsie 继续选择让第三堂课的记录分为两堂，记录就可能变为 $[1,5,0,4,5],[1,5,1,3,5],[1,5,2,2,5],[1,5,3,1,5]$ 或 $[1,5,4,0,5]$。

给定 $Q$ 个候选的 Bessie 最不喜欢的数字 $q_1,\ldots,q_Q$，对于每个数字，请帮助 Elsie 计算她至少要操作多少次，才能让记录里的所有数字都变成这个数字。
## 输入格式

第一行一个整数 $N$（$2\le N\le 10^5$）。

第二行 $N$ 个整数 $a_1,a_2,\ldots, a_N$（$1\le a_i\le 10^{18}$）。

第三行一个整数 $Q$（$1\le Q\le 10^5$）。

接下来 $Q$ 行，每行一个整数 $q_i$（$1\le q_i\le 10^{18}$），表示 Bessie 最不喜欢的数字。
## 输出格式

对于每个 $q_i$，计算 Elsie 把记录里的每个数都变成 $q_i$ 所需要的最小操作次数。如果不能把所有数都变成 $q_i$，输出 $-1$。
## 样例

### 样例输入 #1
```
6
1 2 3 1 1 4
7
1
2
3
4
5
6
12
```
### 样例输出 #1
```
6
6
4
5
-1
4
5
```
## 提示

**【样例解释】**

Elsie 需要至少 $4$ 次修改才能让记录里的所有数都变成 $3$。

$$
\begin{aligned}
&\ 1\ 2\ 3\ 1\ 1\ 4\\
\rightarrow&\ 3\ 3\ 1\ 1\ 4\\
\rightarrow&\ 3\ 3\ 1\ 5\\
\rightarrow&\ 3\ 3\ 6\\
\rightarrow&\ 3\ 3\ 3\ 3\\
\end{aligned}
$$

Elsie 不可能把记录中的所有数都变成 $5$，因此输出 $-1$。这是正确的。

**【数据范围】**

- 对于第 $2\sim 4$ 组数据，$N,Q\le 5000$。
- 对于第 $5\sim 7$ 组数据，所有 $a_i$ 最多为 $10^9$。
- 对于第 $8\sim 26$ 组数据，无附加限制。


---

---
title: "[USACO22OPEN] Hoof and Brain P"
layout: "post"
diff: 省选/NOI-
pid: P8276
tag: ['USACO', '2022', '拓扑排序', '启发式合并']
---
# [USACO22OPEN] Hoof and Brain P
## 题目描述

给定一个包含 $N$ 个结点和 $M$ 条边的有向图（$2 \leq N \leq 10^5$, $1 \leq M \leq 2 \cdot 10^5$），Farmer John 的奶牛们喜欢玩以下的双人游戏。

在图中的不同结点上放置两个指示物（可以用一些与奶牛相关的物品代替指示物）。每一回合，一名玩家，脑，选择一个需要沿某一条出边移动的指示物。另一名玩家，蹄，选择沿着哪条出边移动该指示物。两个指示物在任何时刻不允许处于同一个结点上。如果在某些时刻蹄不能做出合法的行动，则脑获胜。如果游戏可以无限进行下去，则蹄获胜。

给定 $Q$ 个询问（$1 \leq Q \leq 10^5$），包含两个指示物所在的初始结点。对于每个询问，输出哪名玩家获胜。
## 输入格式

输入的第一行包含 $N$ 和 $M$。

以下 $M$ 行每行包含两个整数 $a$ 和 $b$，表示一条从 $a$ 连向 $b$ 的边。

图中不包含自环或重边。

下一行包含 $Q$。

最后 $Q$ 行每行包含两个整数 $x$ 和 $y$，满足 $1\le x,y\le N$ 以及 $x\neq y$，表示指示物所在的初始结点。

## 输出格式

输出一个长为 $Q$ 的字符串，其中字符 B 表示脑获胜，H 表示蹄获胜。

**注意：本题的时间限制为 4 秒，通常限制的两倍。**
## 样例

### 样例输入 #1
```
9 10
1 2
2 3
3 4
4 7
3 5
1 6
6 8
8 9
9 6
7 2
4
1 5
1 2
1 6
2 4
```
### 样例输出 #1
```
BHHB
```
## 提示

【数据范围】

脑可以通过选择结点 $5$ 赢得第一局游戏；此时蹄将没有合法的行动。

脑可以通过选择结点 $4$ 然后选择结点 $7$ 赢得最后一局游戏；此时蹄没有合法的行动。

蹄赢得其他局游戏。

【测试点性质】

- 测试点 2-3 满足 $N\le 100$，$M\le 200$。
- 测试点 4-9 满足 $N\le 5000$。
- 测试点 10-21 没有额外限制。


---

---
title: "[USACO22OPEN] Up Down Subsequence P"
layout: "post"
diff: 省选/NOI-
pid: P8277
tag: ['动态规划 DP', 'USACO', '树状数组', '2022', '动态规划优化']
---
# [USACO22OPEN] Up Down Subsequence P
## 题目描述

Farmer John 的 $N$ 头奶牛（$2 \leq N \leq 3\cdot 10^5$），编号为 $1 \ldots N$，排列成 $1\ldots N$ 的一个排列 $p_1,p_2,\ldots,p_N$。另外给定一个长为 $N-1$ 的字符串，由字母 U 和 D 组成。请求出最大的 $K\le N-1$，使得存在 $p$ 的一个子序列 $a_0,a_1,\ldots,a_{K}$，满足对于所有 $1\le j\le K$，当字符串中第 $j$ 个字母是 U 时 $a_{j - 1} < a_j$，当字符串中的第 $j$ 个字母是 D 时 $a_{j - 1} > a_j$。

## 输入格式

输入的第一行包含 $N$。

第二行包含 $p_1,p_2,\ldots,p_N$。

最后一行包含给定的字符串。
## 输出格式

输出 $K$ 的最大可能值。
## 样例

### 样例输入 #1
```
5
1 5 3 4 2
UDUD
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5
1 5 3 4 2
UUDD
```
### 样例输出 #2
```
3
```
## 提示

【样例解释 1】

我们可以选择 $[a_0,a_1,a_2,a_3,a_4]=[p_1,p_2,p_3,p_4,p_5]$；整个排列与给定的字符串相一致。

【样例解释 2】

我们可以选择 $[a_0,a_1,a_2,a_3]=[p_1,p_3,p_4,p_5]$。

【测试点性质】

- 测试点 3-4 满足 $N\le 500$。
- 测试点 5-8 满足 $N\le 5000$。
- 测试点 9-12 中，字符串中的 U 均在 D 之前。
- 测试点 13-22 没有额外限制。



---

---
title: "[USACO22DEC] Breakdown P"
layout: "post"
diff: 省选/NOI-
pid: P8906
tag: ['USACO', '2022', '最短路', '均摊分析', '折半搜索 meet in the middle']
---
# [USACO22DEC] Breakdown P
## 题目描述

Farmer John 的农场可以用一个带权有向图表示，道路（边）连接不同的结点，每条边的权值是通过道路所需的时间。每天，Bessie 喜欢从牛棚（位于结点 $1$）经过恰好 $K$ 条道路前往草地（位于结点 $N$），并希望在此限制下尽快到达草地。然而，在某些时候，道路停止维护，一条一条地开始破损，变得无法通行。帮助 Bessie 求出每一时刻从牛棚到草地的最短路径！

形式化地说，我们从一个 $N$ 个结点（$1 \le N \le 300$）和 $N^2$ 条边的带权有向完全图开始：对于 $1 \le i,j \le N$ 的每一对 $(i,j)$ 存在一条边（注意存在 $N$ 个自环）。每次移除一条边后，输出从 $1$ 到 $N$ 的所有路径中经过恰好 $K$ 条边（不一定各不相同）的路径的最小权值（$2 \le K \le 8$）。注意在第 $i$ 次移除后，该图还剩下 $N^2-i$ 条边。

路径的权值定义为路径上所有边的权值之和。注意一条路径可以包含同一条边多次或同一个结点多次，包括结点 $1$
和 $N$。
## 输入格式

输入的第一行包含 $N$ 和 $K$。

以下 $N$ 行每行包含 $N$ 个整数。第 $i$ 行的第 $j$ 个整数为 $w_{ij}(1 \le w_{ij} \le 10^8)$。

以下 $N^2$ 行，每行包含两个整数 $i$ 和 $j$（$1 \le i,j \le N$）。每对整数出现恰好一次。 
## 输出格式

输出 $N^2$ 行，为每一次移除后经过 $K$ 条边的路径的最小权值。如果不存在经过 $K$ 条边的路径则输出 $-1$。 
## 样例

### 样例输入 #1
```
3 4
10 4 4
9 5 3
2 1 6
3 1
2 3
2 1
3 2
2 2
1 3
3 3
1 1
1 2
```
### 样例输出 #1
```
11
18
22
22
22
-1
-1
-1
-1
```
## 提示

### 样例 1 解释

第一次移除后，最短的经过 $4$ 条边的路径为：

$$1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 3$$

第二次移除后，最短的经过 $4$ 条边的路径为：

$$1 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 3$$

第三次移除后，最短的经过 $4$ 条边的路径为：

$$1 \rightarrow 3 \rightarrow 3 \rightarrow 3 \rightarrow 3$$

六次移除后，不再存在经过 $4$ 条边的路径。 

### 测试点性质

 - 对于 $2 \le T \le 14$，测试点 $T$ 满足 $K=\lfloor \dfrac{T+3}{2} \rfloor$。 


---

---
title: "[USACO22DEC] Palindromes P"
layout: "post"
diff: 省选/NOI-
pid: P8908
tag: ['数学', 'USACO', '树状数组', '2022', '均摊分析']
---
# [USACO22DEC] Palindromes P
## 题目描述

农夫约翰合牛国（The United Cows of Farmer John，UCFJ）正在参加一年一度的蹄球锦标赛！UCFJ 队的 $N(1 \le N \le 7500)$ 头奶牛以微弱优势击败了 Farmer Nhoj 的队伍，赢得了蹄球比赛的金牌。

奶牛们已经为颁奖典礼排好了队。她们希望 FJ 拍摄 $\dfrac{N(N+1)}{2}$ 张合影，为队伍的每个连续子段拍摄一张。

然而，FJ，作为球队的主帅，对于奶牛们应该如何列队十分讲究。具体地说，他拒绝为一个子段拍照，除非它形成一个**回文串**，即对于所有不超过子段长度的正整数 $i$，从子段左端开始的第 $i$ 头奶牛的品种必须与从子段右端开始的第 $i$ 
头奶牛的品种相同。每头奶牛的品种是更赛牛（Guernsey）或荷斯坦牛（Holstein）之一。

对于队伍的 $\dfrac{N(N+1)}{2}$ 个连续子段的每一个，计算将该子段重新排列成回文串所需的最小换位次数（如果不可能这样做则为 $−1$）。单次换位是在子序列中取两头相邻的奶牛并交换。输出所有这些次数之和。

注意对每个连续子段所需的换位次数是独立计算的（奶牛们会在照片拍摄之间返回她们的起始位置）。 
## 输入格式

输入队伍，用一个长为 $N$ 的字符 $\texttt{G}$ 和 $\texttt{H}$ 组成的字符串表示。 
## 输出格式

输出队伍的所有 $\dfrac{N(N+1)}{2}$ 个连续子段的前述数量之和。 
## 样例

### 样例输入 #1
```
GHHGGHHGH
```
### 样例输出 #1
```
12
```
## 提示

### 样例 1 解释

前四个连续子段是 $\texttt{G}$，$\texttt{GH}$，$\texttt{GHH}$ 和 $\texttt{GHHG}$。$\texttt{G}$ 和 $\texttt{GHHG}$ 都已经是回文串，因此它们对总和的贡献为 $0$。$\texttt{GHH}$ 可以使用一次换位重新排列成回文串，因此它对总和的贡献为 $1$。$\texttt{GH}$ 不能使用任意次数的换位重新排列成回文串，因此它对总和的贡献为 $−1$。

$\texttt{HHGG}$ 是另一个对总和有贡献的连续子段。这个子段可以使用两次换位重新排列成回文串。 

### 测试点性质

除样例外有十五个测试点，满足 $N \in \{ 100,200,500,1000,2000,5000,5000,5000,5000,5000,7500,7500,7500,7500,7500\}$ 各一。


---

---
title: "[USACO23JAN] Tractor Paths P"
layout: "post"
diff: 省选/NOI-
pid: P9019
tag: ['贪心', '倍增', 'USACO', '2023', '最短路']
---
# [USACO23JAN] Tractor Paths P
## 题目描述

**Note: The time limit for this problem is 4s, twice the default. The memory limit for this problem is 512MB, twice the default.**

Farmer John has $N
(2 \le N \le 2 \cdot 10^5)$ tractors, where the $i$-th tractor can only be used within the inclusive interval $[l_i,r_i]$. The tractor intervals have left endpoints $l_1<l_2<\cdots <l_N$ and right endpoints $r_1<r_2< \cdots <r_N$. Some of the tractors are special.

Two tractors $i$ and $j$ are said to be adjacent if $[l_i,r_i]$ and $[l_j,r_j]$ intersect. Farmer John can transfer from one tractor to any adjacent tractor. A path between two tractors $a$ and $b$ consists of a sequence of transfers such that the first tractor in the sequence is $a$, the last tractor in the sequence is $b$, and every two consecutive tractors in the sequence are adjacent. It is guaranteed that there is a path between tractor $1$ and tractor $N$. The length of a path is the number of transfers (or equivalently, the number of tractors within it minus one). 

You are given $Q (1 \le Q \le 2 \cdot 10^5)$ queries, each specifying a pair of tractors $a$ and $b (1 \le a<b \le N)$. For each query, output two integers: 

 - The length of any shortest path between tractor $a$ to tractor $b$.
 - The number of special tractors such that there exists at least one shortest path from tractor $a$ to tractor $b$ containing it. 
## 输入格式

The first line contains $N$ and $Q$.

The next line contains a string of length $2N$ consisting of Ls and Rs, representing the left and right endpoints in sorted order. It is guaranteed that for each proper prefix of this string, the number of Ls exceeds the number of Rs.

The next line contains a bit string of length $N$, representing for each tractor whether it is special or not.

The next $Q$ lines each contain two integers $a$ and $b$, specifying a query. 
## 输出格式

 For each query, the two quantities separated by spaces. 
## 样例

### 样例输入 #1
```
8 10
LLLLRLLLLRRRRRRR
11011010
1 2
1 3
1 4
1 5
1 6
1 7
1 8
2 3
2 4
2 5
```
### 样例输出 #1
```
1 2
1 1
1 2
2 4
2 3
2 4
2 3
1 1
1 2
1 2
```
## 提示

### Explanation for Sample 1

The $8$ tractor intervals, in order, are $[1,5],[2,10],[3,11],[4,12],[6,13],[7,14],[8,15],[9,16]$.

For the 4th query, there are three shortest paths between the 1st and 5th tractor: $1$ to $2$ to $5$, $1$ to $3$ to $5$, and $1$ to $4$ to $5$. These shortest paths all have length $2$.

Additionally, every tractor $1,2,3,4,5$
is part of one of the three shortest paths mentioned earlier, and since $1,2,4,5$ are special, there are $4$ special tractors such that there exists at least one shortest path from tractor $1$ to $5$ containing it. 

### Scoring

 - Inputs $2-3$: $N,Q \le 5000$
 - Inputs $4-7$: There are at most $10$ special tractors.
 - Inputs $8-16$: No additional constraints.
## 题目翻译

### 题目描述

**注意：这个问题的时间限制是4秒，内存限制是512MB，是默认值的两倍。**

农民约翰有 $N
(2 \le N \le 2 \cdot 10^5)$ 台拖拉机, 其中第 $i$ 台拖拉机只能在序列 $[l_i,r_i]$ 内使用。拖拉机有左端点 $l_1<l_2<\cdots <l_N$ 和右端点 $r_1<r_2< \cdots <r_N$. 有一些拖拉机是特别的。

如果 $[l_i,r_i]$ 和 $[l_j,r_j]$ 相交，则两台拖拉机 $i$ 和 $j$ 是相邻的。 约翰可以从一辆拖拉机转移到任何相邻的拖拉机上。两台拖拉机 $a$ 和 $b$ 之间的路径由一个传输序列组成，这样序列中的第一个拖拉机是 $a$，序列中的最后一个拖拉机是 $b$，并且序列中的每两个连续的拖拉机相邻。 保证拖拉机 $1$ 和 拖拉机 $N$ 之间有一条路径。路径的长度是转移的数量 (或等价地，其中拖拉机的数量减去 $1$)。

给定 $Q (1 \le Q \le 2 \cdot 10^5)$ 组询问，每次给定 $a$ 和 $b (1 \le a<b \le N)$。 对于每组询问，你需要回答两个问题：

 - $a$ 到 $b$ 的最短路径。
 - 在保证传送次数的最少的情况下，有多少个特殊拖拉机的区间可能被某条最短路经过。

### 输入格式

第一行输入两个整数 $N$ 和 $Q$，表示有 $N$ 台拖拉机和 $Q$ 次询问。

第二行输入一个长度为 $2N$ 的字符串，由大写字母 `L` 和 `R` 组成，保证这个字符串的每个前缀中 `L` 的数量大于 `R` 的数量。

第三行输入一个长度为 $N$ 的字符串, 表示每个拖拉机是否特殊。

接下来 $Q$ 行输入两个整数 $a$ 和 $b$, 表示一次查询。

### 输出格式

对于每一组数据，一行两个数，表示答案。

### 提示

### 样例 $1$ 解释

$8$ 个拖拉机的时间间隔，按顺序，是 $[1,5],[2,10],[3,11],[4,12],[6,13],[7,14],[8,15],[9,16]$。

对于第四个查询, 第 $1$ 台和第 $5$ 台拖拉机之间有三条最短路径: $1 \rightarrow 2 \rightarrow 5$, $1 \rightarrow 3 \rightarrow 5$, 和 $1 \rightarrow 4 \rightarrow 5$。这些最短路径的长度都为 $2$。

另外, 拖拉机 $1,2,3,4,5$
都是前面提到的三条最短路径之一的一部分, 由于 $1,2,4,5$ 是特殊的，因此有 $4$ 台特殊拖拉机，这样存在至少一条包含拖拉机 $1$ 到 $5$ 的最短路径。

### 数据范围

 - 数据点 $2-3$： $N,Q \le 5000$
 - 数据点 $4-7$： 最多 $10$ 台特别的拖拉机。
 - 数据点 $8-16$： 没有额外的约束。
 
 翻译提供者：[shuqiang](https://www.luogu.com.cn/user/685964)


---

---
title: "[USACO23JAN] Mana Collection P"
layout: "post"
diff: 省选/NOI-
pid: P9020
tag: ['USACO', '2023', '凸包', '李超线段树', '状压 DP']
---
# [USACO23JAN] Mana Collection P
## 题目描述

**Note: The time limit for this problem is 5s, 2.5 times the default. The memory limit for this problem is 512MB, twice the default.**

Bessie has recently taken an interest in magic and needs to collect mana for a very important spell. Bessie has $N(1 \le N \le 18)$ mana pools, the ith of which accumulates $m_i$ mana per second $(1 \le m_i \le 10^8)$. The pools are linked by a collection of $M (0 \le M \le N(N−1))$ directed edges $(a_i,b_i,t_i)$, meaning that she can travel from $a_i$ to $b_i$ in $t_i$ seconds $(1 \le a_i,b_i \le N, a_i \neq b_i, 1 \le t_i \le 10^9)$. Whenever Bessie is present at a pool, she can collect all the mana stored at that location, emptying it. At time $0$, all mana pools are empty, and Bessie can select any pool to start at.

Answer $Q(1 \le Q \le 2 \cdot 10^5)$ queries, each specified by two integers $s$ and $e (1 \le s \le 10^9, 1 \le e \le N)$. For each query, determine the maximum amount of mana Bessie can collect in s seconds if she must be at mana pool $e$ at the end of the $s$-th second. 
## 输入格式

First line contains $N$ and $M$.

Next line contains $m_1,m2, \cdots ,m_N$.

Next $M$ lines contain $a_i,b_i,t_i$. No ordered pair $(a_i,b_i)$ appears more than once in the input.

Next line contains $Q$.

Next $Q$ lines contain two integers $s$ and $e$. 
## 输出格式

$Q$ lines, one for each query. 
## 样例

### 样例输入 #1
```
2 1
1 10
1 2 10
4
5 1
5 2
100 1
100 2
```
### 样例输出 #1
```
5
50
100
1090
```
### 样例输入 #2
```
4 8
50000000 100000000 20000000 70000000
1 2 20
2 1 50
2 3 90
1 3 40
3 1 10
4 1 25
1 4 5
4 3 70
3
8 3
1000000000 1
500000 4
```
### 样例输出 #2
```
160000000
239999988050000000
119992550000000
```
## 提示

### Explanation for Sample 1

First query: Bessie takes $5$ mana from pool $1$ after $5$ seconds.

Second query: Bessie takes $50$ mana from pool $2$ after $5$ seconds.

Third query: Bessie takes $100$ mana from pool $1$ after $100$ seconds.

Fourth query: Bessie takes $90$ mana from pool $1$ after $90$ seconds and $1000$ mana from pool $2$ after $100$ seconds. 

### Explanation for Sample 2

An example where Bessie is able to collect much larger amounts of mana. 

### Scoring

 - Inputs $3-4$: $N \le 10$,$Q \le 100$
 - Inputs $5-9$: $N \le 10$
 - Inputs $10-14$: $Q \le 100$
 - Inputs $15-17$: $N=16$
 - Inputs $18-20$: $N=17$
 - Inputs $21-24$: No additional constraints.
## 题目翻译

## 题目背景

**注意：这个问题的时间限制是5秒，是默认的2.5倍。这个问题的内存限制是512MB，是默认值的两倍。**

## 题目描述

贝西需要为一个非常重要的法术收集法力。贝西有 $N$  $(1\le N\le 18)$ 个法力池，其中第 $i$ 个法力池每秒可积累 $m_i$ 法力 $(1\le m_i\le 10^8)$ 。这些池子由 $M$ $(0\le M\le N \cdot (N-1))$  条有向边 $(a_i,b_i,t_i)$ 连接，这意味着她可以在 $t_i$ 秒内从 $a_i$ 移动到 $b_i$ $(1\le a_i, b_i\le N$, $a_i\neq b_i$, $1\le t_i\le 10^9)$ 。每当贝西出现在一个池子里，她就可以收集储存在那个地方的所有法力，把它清空。在 $0$ 的时候，所有的法力池都是空的，贝西可以选择任何一个池子来开始收集。

回答 $Q$ $(1\le Q\le 2\cdot 10^5)$ 个查询，每个查询由两个整数 $s$ 和 $e$ 指定 $(1\le s\le 10^9$，$1\le e\le N)$ 。对于每个查询，如果贝西在第 $s$ 秒结束时必须在法力池 $e$ 处，请确定她在 $s$ 秒内能收集的最大法力值。

## 输入格式

第一行包含 $N$ 和 $M$ 。

下一行包含 $m_1,m_2,\dots, m_N$ 。

接下来的 $M$ 行每行包含 $a_i,b_i,t_i$ 。在输入中没有一对有序的 $(a_i,b_i)$ 出现超过一次。

下一行包含 $Q$ 。

接下来的 $Q$ 行每行包含两个整数 $s$ 和 $e$ 。

## 输出格式

输出 $Q$ 行，每个查询所对应的答案。

## 提示

对于第一个样例：

第一次询问。贝西在 $5$ 秒后从水池 $1$ 中取出 $5$ 个法力值。

第二次查询。 $5$ 秒后，贝西从水池 $2$ 中获取 $50$ 点法力。

第三次查询。 $100$ 秒后，贝西从水池 $1$ 中获取 $100$ 法力值。

第四次查询。 $90$ 秒后贝西从水池 $1$ 中获得 $90$ 法力， $100$ 秒后从水池 $2$ 中获得 $1000$ 法力。

测试点 $3-4$: $N\le 10, Q\le 100$ 。

测试点 $5-9$: $N\le 10$ 。

测试点 $10-14$: $Q\le 100$ 。

测试点 $15-17$: $N = 16$ 。

测试点 $18-20$: $N = 17$ 。

测试点 $21-24$：没有其他约束条件 。


---

---
title: "[USACO23JAN] Subtree Activation P"
layout: "post"
diff: 省选/NOI-
pid: P9021
tag: ['USACO', '2023', '树形 DP']
---
# [USACO23JAN] Subtree Activation P
## 题目描述

For the New Year celebration, Bessie and her friends have constructed a giant tree with many glowing ornaments. Bessie has the ability to turn the ornaments on and off through remote control. Before the sun rises, she wants to toggle some of the ornaments in some order (possibly toggling an ornament more than once) such that the tree starts and ends with no ornaments on. Bessie thinks the tree looks cool if the set of activated ornaments is exactly a subtree rooted at some vertex. She wants the order of ornaments she toggles to satisfy the property that, for every subtree, at some point in time it was exactly the set of all turned on ornaments. Additionally, it takes energy to switch on and off ornaments, and Bessie does not want to waste energy, so she wants to find the minimum number of toggles she can perform. 

Formally, you have a tree with vertices labeled $1 \cdots N (2 \le N \le 2 \cdot 10^5)$ rooted at $1$. Each vertex is initially inactive. In one operation, you can toggle the state of a single vertex from inactive to active or vice versa. Output the minimum possible length of a sequence of operations satisfying both of the following conditions: 

 - Define the subtree rooted at a vertex $r$ to consist of all vertices $v$ such that $r$ lies on the path from $1$ to $v$ inclusive. For every one of the $N$ subtrees of the tree, there is a moment in time when the set of active vertices is precisely those in that subtree. 
 - Every vertex is inactive after the entire sequence of operations.
## 输入格式

The first line contains $N$.

The second line contains $p_2 \cdots p_N
(1 \le p_i<i)$, where $p_i$ denotes the parent of vertex $i$ in the tree. 
## 输出格式

Output the minimum possible length. 
## 样例

### 样例输入 #1
```
3
1 1
```
### 样例输出 #1
```
6
```
## 提示

### Explanation for Sample 1

There are three subtrees, corresponding to $\{1,2,3\}$, $\{2\}$, and $\{3\}$. Here is one sequence of operations of the minimum possible length:

activate 2  
(activated vertices form the subtree rooted at 2)  
activate 1  
activate 3  
(activated vertices form the subtree rooted at 1)  
deactivate 1  
deactivate 2  
(activated vertices form the subtree rooted at 3)  
deactivate 3

### Scoring

 - Inputs $2-3$: $N \le 8$
 - Inputs $4-9$: $N \le 40$
 - Inputs $10-15$: $N \le 5000$
 - Inputs $16-21$: No additional constraints.

## 题目翻译

## 题目描述

你有一棵根为 $1$ 的树，顶点标记为 $1 \dots N$ $(2 \le N \le 2 \cdot 10^5)$ 。每个顶点最初都是关闭的。在一次操作中，你可以将一个顶点的状态从关闭状态切换到开启状态，反之亦然。输出一个满足以下两个条件的操作序列的最小可能长度。

- 定义以顶点 $r$ 为根的子树由所有满足 $r$ 位于从 $1$ 到 $v$ 的路径上 $($包括 $v)$ , 的顶点 $v$ 组成。每一个顶点的子树，都有一个时刻，开启状态顶点的集合恰好是该子树中的顶点。
- 在整个操作序列之后，每个顶点都是关闭的。

## 输入格式

第一行包含 $N$ 。

第二行包含 $p_2 \dots p_N$ ， $p_i$ 是结点 $i$ 的父亲 $(1\le p_i < i)$ 。

## 输出格式

输出可能的最小长度。

## 提示

有三个子树，分别对应 $\{1,2,3\}、\{2\}、\{3\}$ 。下面是最小可能长度的一个操作序列。

- 开启 $2$ (激活的顶点形成以 $2$ 为根的子树) 。
- 开启 $1$ 。
- 开启 $3$ (激活的顶点形成以 $1$ 为根的子树) 。
- 关闭 $1$ 。
- 关闭 $2$ (激活的顶点形成以 $3$ 为根的子树) 。
- 关闭 $3$ 。

子任务：
- 测试点 $2-3$ : $N \le 8$
- 测试点 $4-9$ : $N \le 40$
- 测试点 $10-15$ : $N \le 5000$
- 测试点 $16-21$ ：没有额外的限制。


---

---
title: "[USACO23FEB] Fertilizing Pastures G"
layout: "post"
diff: 省选/NOI-
pid: P9128
tag: ['数学', '贪心', 'USACO', '2023', '排序']
---
# [USACO23FEB] Fertilizing Pastures G
## 题目描述

There are $N$ pastures $(2 \le N \le 2 \cdot 10^5)$, connected by $N−1$ roads, such that they form a tree. Every road takes $1$ second to cross. Each pasture starts out with $0$ grass, and the ith pasture's grass grows at a rate of $a_i (1 \le a_i \le 10^8)$ units per second. Farmer John is in pasture $1$ at the start, and needs to drive around and fertilize the grass in every pasture. If he visits a pasture with $x$ units of grass, it will need $x$ amount of fertilizer. A pasture only needs to be fertilized the first time it is visited, and fertilizing a pasture takes $0$ time.

The input contains an additional parameter $T \in \{0,1\}$.

 - If $T=0$, Farmer John must end at pasture $1$.
 - If $T=1$, Farmer John may end at any pasture.

Compute the minimum amount of time it will take to fertilize every pasture and the minimum amount of fertilizer needed to finish in that amount of time. 
## 输入格式

The first line contains $N$ and $T$.

Then for each $i$ from $2$ to $N$, there is a line containing $p_i$ and $a_i$, meaning that there is a road connecting pastures $p_i$ and $i$. It is guaranteed that $1 \le p_i<i$. 
## 输出格式

 The minimum amount of time and the minimum amount of fertilizer, separated by spaces. 
## 样例

### 样例输入 #1
```
5 0
1 1
1 2
3 1
3 4
```
### 样例输出 #1
```
8 21
```
### 样例输入 #2
```
5 1
1 1
1 2
3 1
3 4
```
### 样例输出 #2
```
6 29
```
## 提示

### Explanation for Sample 1

The optimal route for Farmer John is as follows: 

 - At time $1$, move to node $3$, which now has $1 \cdot 2=2$ grass and so needs $2$ fertilizer.
 - At time $2$, move to node $5$, which now has $2 \cdot 4=8$ grass and so needs $8$ fertilizer.
 - At time $3$, move back to node $3$, which we already fertilized and so don't need to fertilize again.
 - At time $4$, move to node $4$, which now has $4 \cdot 1=4$ grass and so needs $4$ fertilizer.
 - At time $5$, move back to node $3$, which we already fertilized.
 - At time $6$, move back to node $1$.
 - At time $7$, move to node $2$, which now has $7 \cdot 1=7$ grass and so needs $7$ fertilizer.
 - At time $8$, return to node $1$. 

This route takes $8$ time and uses $2+8+4+7=21$ fertilizer. It can be shown that $8$ is the least possible amount of time for any route that returns to node $1$ at the end and $21$ is the least possible fertilizer used for any route that returns to node $1$ and takes $8$ time.

### Explanation for Sample 2

The optimal route for Farmer John is as follows:

 - At time $1$, move to node $2$, which now has $1 \cdot 1=1$ grass and so needs $1$ fertilizer.
 - At time $2$, move back to node $1$.
 - At time $3$, move to node $3$, which now has $3 \cdot 2=6$ grass and so needs $6$ fertilizer.
 - At time $4$, move to node $5$, which now has $4 \cdot 4=16$ grass and so needs $16$ fertilizer.
 - At time $5$, move back to node $3$, which we already fertilized and so don't need to fertilize again.
 - At time $6$, move to node $4$, which now has $6 \cdot 1=6$ grass and so needs $6$ fertilizer.

This route takes $6$ time and uses $1+6+16+6=29$ fertilizer. It can be shown that $6$ is the least possible amount of time for any route and $29$ is the least possible fertilizer used for any route that takes $6$ time.

### SCORING

 - Inputs $3-10$: $T=0$
 - Inputs $11-22$: $T=1$
 - Inputs $3-6$ and $11-14$: No pasture is adjacent to more than three roads.
## 题目翻译

### 题目描述

有 $N$ 个顶点的树，经过节点之间的每一条边都需要 $1s$。每个顶点一开始的权值均为 $0$，第 $i$ 个点的权值的增长速率为 $a_i/s$。FJ 从 $1$ 号顶点出发遍历整棵树。当 FJ 走到某个节点时，若该节点的权值为 $x$，则需要支出大小为 $x$ 的费用。（当然，只需在第一次经过该节点时需要支出。）

给出一个参数 $T$:

+ **若 $T=0$，FJ 必须回到 $1$ 号节点**。

+ **若 $T=1$，FJ 可以在任意节点结束他的遍历**。

求遍历所有节点的最小时间和此时需要付出的最小的费用。

### 输入格式

第一行包括 $N$ 和 $T$。

第 $2$ 行到第 $N$ 行，包含两个整数 $p_i$ 和 $a_i$,$a_i$ 的含义见上文。$p_i$ 则表示节点 $i$ 和 $p_i$ 之间有一条边相连。

### 输出格式
两个整数：遍历所有节点的最小时间和此时需要付出的最小的费用。

$2 \le N \le 2 \times 10^5,T \in \{0,1\},1 \le a_i \le 10^8, 1 \le p_i < i$。


---

---
title: "[USACO23FEB] Piling Papers G"
layout: "post"
diff: 省选/NOI-
pid: P9129
tag: ['USACO', '2023', '数位 DP', '区间 DP']
---
# [USACO23FEB] Piling Papers G
## 题目描述

Farmer John wrote down $N (1 \le N \le 300)$ digits on pieces of paper. For each $i \in [1,N]$, the ith piece of paper contains digit $a_i (1 \le a_i \le 9)$.

The cows have two favorite integers $A$ and $B(1 \le A \le B<10^{18})$, and would like you to answer $Q (1 \le Q \le 5⋅10^4)$ queries. For the $i$-th query, the cows will move left to right across papers $l_i \cdots r_i (1 \le l_i \le r_i \le N)$, maintaining an initially empty pile of papers. For each paper, they will either add it to the top of the pile, to the bottom of the pile, or neither. In the end, they will read the papers in the pile from top to bottom, forming an integer. Over all $3 ^ {r_i−l_i+1}$ ways for the cows to make choices during this process, count the number of ways that result in the cows reading an integer in $[A,B]$ inclusive, and output this number modulo $10^9+7$. 
## 输入格式

The first line contains three space-separated integers $N, A$, and $B$.

The second line contains $N$ space-separated digits $a_1,a_2, \cdots ,a_N$.

The third line contains an integer $Q$, the number of queries.

The next $Q$ lines each contain two space-separated integers $l_i$ and $r_i$. 
## 输出格式

For each query, a single line containing the answer. 
## 样例

### 样例输入 #1
```
5 13 327
1 2 3 4 5
3
1 2
1 3
2 5
```
### 样例输出 #1
```
2
18
34
```
## 提示

### Explanation for Sample 1

For the first query, there are nine ways Bessie can stack papers when reading the interval $[1,2]$:

 - Bessie can ignore $1$ then ignore $2$, getting $0$.
 - Bessie can ignore $1$ then add $2$ to the top of the stack, getting $2$.
 - Bessie can ignore $1$ then add $2$ to the bottom of the stack, getting $2$.
 - Bessie can add $1$ to the top of the stack then ignore $2$, getting $1$.
 - Bessie can add $1$ to the top of the stack then add $2$ to the top of the stack, getting $21$.
 - Bessie can add $1$ to the top of the stack then add $2$ to the bottom of the stack, getting $12$.
 - Bessie can add $1$ to the bottom of the stack then ignore $2$, getting $1$.
 - Bessie can add $1$ to the bottom of the stack then add $2$ to the top of the stack, getting $21$.
 - Bessie can add $1$ to the bottom of the stack then add $2$ to the bottom of the stack, getting $12$. 

Only the $2$ ways that give $21$ yield a number between $13$ and $327$, so the answer is $2$.

### SCORING

 - Inputs $2-3$: $B<100$
 - Inputs $4-5$: $A=B$
 - Inputs $6-13$: No additional constraints.
## 题目翻译

给定长度为 $n(1\leq n\leq 300)$ 的整数序列 $a(1\leq a_i\leq 9)$，和整数区间 $[A,B](1\leq A\leq B\leq 10^{18})$，有 $q$ 次询问，每次询问给出 $l,r$。每次询问开始，你有一个空串 $x$，你可以正序对 $a_{l\sim r}$ 进行操作，操作有三种：$x\rightarrow\overline{x+a_i}$，$x\rightarrow\overline{a_i+x}$，或者什么也不做，求 $\overline{x}$ 的取值在 $[A,B]$ 的不同的操作方案数，对 $10^9+7$ 取模。


---

---
title: "[USACO23FEB] Hungry Cow P"
layout: "post"
diff: 省选/NOI-
pid: P9130
tag: ['线段树', 'USACO', '2023', '分治']
---
# [USACO23FEB] Hungry Cow P
## 题目描述

**Note: The time limit for this problem is 6s, three times the default. The memory limit for this problem is 512MB, twice the default.** 

Bessie is a hungry cow. Each day, for dinner, if there is a haybale in the barn, she will eat one haybale. Farmer John does not want Bessie to starve, so some days he sends a delivery of haybales, which arrive in the morning (before dinner). In particular, on day $d_i$, Farmer John sends a delivery of $b_i$ haybales $(1 \le d_i \le 10^{14}, 0 \le b_i \le 10^9)$.

Process $U(1 \le U \le 10^5)$ updates as follows: Given a pair $(d,b)$, update the number of haybales arriving on day $d$ to $b$. After each update, output the sum of all days on which Bessie eats haybales modulo $10^9+7$. 
## 输入格式

$U$, followed by $U$ lines containing the updates. 
## 输出格式

The sum after each update modulo $10^9+7$. 
## 样例

### 样例输入 #1
```
3
4 3
1 5
1 2
```
### 样例输出 #1
```
15
36
18
```
### 样例输入 #2
```
9
1 89
30 7
101 26
1 24
5 1
60 4
5 10
101 0
1 200
```
### 样例输出 #2
```
4005
4656
7607
3482
3507
3753
4058
1107
24531
```
## 提示

### Explanation for Sample 1

Answers after each update:

$4+5+6=15$  
$1+2+3+4+5+6+7+8=36$  
$1+2+4+5+6=18$

### SCORING

 - Input $3$: $U \le 5000$
 - Inputs $4-10$: Updates only increase the number of haybales arriving on day $d$.
 - Inputs 11-22: No additional constraints.
## 题目翻译

Bessie 很饿，每天晚饭如果有干草就会吃 $1$ 份，没有就不吃，初始没有干草。

每天早上 Farmer John 会给它送若干干草，设第 $k$ 天送 $a_k$ 份干草，初始时 $a_k=0$，表示该天不送干草。

$q$ 次操作，每次给出 $x,y$，表示将 $a_x$ 改成 $y$，请将在此时 Bessie 有干草吃的**日期编号**求和并输出。对 $10^9+7$ 取模。

操作间互不独立。

$1\le q\le10^5$，$1\le x\le10^{14}$，$0\le y\le10^9$。


---

---
title: "[USACO23FEB] Problem Setting P"
layout: "post"
diff: 省选/NOI-
pid: P9131
tag: ['USACO', '2023', '快速沃尔什变换 FWT', '状压 DP']
---
# [USACO23FEB] Problem Setting P
## 题目描述

**Note: The memory limit for this problem is 512MB, twice the default.**

Farmer John created $N(1 \le N \le 10^5)$ problems. He then recruited $M (1 \le M \le 20)$ test-solvers, each of which rated every problem as "easy" or "hard."

His goal is now to create a problemset arranged in increasing order of difficulty, consisting of some subset of his $N$ problems arranged in some order. There must exist no pair of problems such that some test-solver thinks the problem later in the order is easy but the problem earlier in the order is hard.

Count the number of distinct nonempty problemsets he can form, modulo $10^9+7$. 
## 输入格式

The first line contains $N$ and $M$.

The next $M$ lines each contain a string of length $N$. The $i$-th character of this string is `E` if the test-solver thinks the ith problem is easy, or `H` otherwise. 
## 输出格式

The number of distinct problemsets FJ can form, modulo $10^9+7$. 
## 样例

### 样例输入 #1
```
3 1
EHE
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
10 6
EHEEEHHEEH
EHHHEEHHHE
EHEHEHEEHH
HEHEEEHEEE
HHEEHEEEHE
EHHEEEEEHE
```
### 样例输出 #2
```
33
```
## 提示

### Explanation for Sample 1

The nine possible problemsets are as follows:

$[1]$  
$[1,2]$  
$[1,3]$  
$[1,3,2]$  
$[2]$  
$[3]$  
$[3,1]$  
$[3,2]$  
$[3,1,2]$  

Note that the order of the problems within the problemset matters. 

### SCORING

 - Inputs $3-4$: $M=1$
 - Inputs $5-14$: $M \le 16$
 - Inputs $15-22$: No additional constraints.
## 题目翻译

Farmer John 出了 $n$ 道题，聘了 $m$ 个验题人来品鉴难度。

难度只有简单（`E`）和困难（`H`）两种。

Farmer John 将从中选出若干道（**至少一道**），并以一定顺序排列，使得前一道题目中任意一个觉得此题困难的验题人也觉得后面一道题目困难。

回答有多少种选出来并排列的方案，对 $10^9+7$ 取模。

$1\le n\le10^5$，$1\le m\le20$。


---

---
title: "[USACO23FEB] Watching Cowflix P"
layout: "post"
diff: 省选/NOI-
pid: P9132
tag: ['USACO', '2023', '树形 DP', '根号分治']
---
# [USACO23FEB] Watching Cowflix P
## 题目描述

**Note: The time limit for this problem is 3s, 1.5x the default.**

Bessie likes to watch shows on Cowflix, and she watches them in different places. Farmer John's farm can be represented as a tree with $N(2 \le N \le 2 \cdot 10^5)$ nodes, and for each node, either Bessie watches Cowflix there or she doesn't. It is guaranteed that Bessie watches Cowflix in at least one node.

Unfortunately, Cowflix is introducing a new subscription model to combat password sharing. In their new model, you can choose a connected component of size $d$ in the farm, and then you need to pay $d+k$ moonies for an account that you can use in that connected component. Formally, you need to choose a set of disjoint connected components $c_1,c_2, \cdots ,c_C$ so that every node where Bessie watches Cowflix must be contained within some $c_i$. The cost of the set of components is $\sum\limits^{C}_{i=1}(|c_i|+k)$, where $|c_i|$ is the number of nodes in component $c_i$. Nodes where Bessie does not watch Cowflix do not have to be in any $c_i$.

Bessie is worried that the new subscription model may be too expensive for her given all the places she visits and is thinking of switching to Mooloo. To aid her decision-making, calculate the minimum amount she would need to pay to Cowflix to maintain her viewing habits. Because Cowflix has not announced the value of $k$, calculate it for all integer values of $k$ from $1$ to $N$. 
## 输入格式

The first line contains $N$.

The second line contains a bit string $s_1s_2s_3\cdots s_N$ where $s_i=1$ if Bessie watches Cowflix at node $i$.

Then $N - 1$ lines follow, each containing two integers $a$ and $b (1 \le a,b \le N)$, which denotes an edge between $a$ and $b$ in the tree.
## 输出格式

The answers for each $k$ from $1$ to $N$ on separate lines. 
## 样例

### 样例输入 #1
```
5
10001
1 2
2 3
3 4
4 5
```
### 样例输出 #1
```
4
6
8
9
10
```
### 样例输入 #2
```
7
0001010
7 4
5 6
7 2
5 1
6 3
2 5
```
### 样例输出 #2
```
4
6
8
9
10
11
12
```
## 提示

### Explanation for Sample 1

For $k \le 3$, it's optimal to have two accounts: $c_1=\{1\},c_2=\{5\}$. For $k \ge 3$, it's optimal to have one account: $c_1=\{1,2,3,4,5\}$.

### SCORING

 - Inputs $3-5$: $N \le 5000$
 - Inputs $6-8$: $i$ is connected to $i+1$ for all $i \in [1,N)$.
 - Inputs $9-19$: $N \le 10^5$
 - Inputs $20-24$: No additional constraints.
## 题目翻译

Bessie 喜欢在 Cowflix 上看节目，并且喜欢在农场里的不同地方看。

Farmer John 的农场可以被描述成一颗 $n$ 个节点的树，并且 Bessie 只可能在树上的一些指定的节点处看节目。每个节点是否要看节目将在初始时给定；保证至少在一个节点处会看节目。

不幸的是，Cowflix 为了避免奶牛们使用公用账号，采取了一个新的会员策略：
* Bessie 将多次付款，每次选择树上任意一个大小为 $d$ 的**连通块**，为其支付 $d+k$ 的代价，才能够在这些位置看节目。

换言之，Bessie 将选取若干**连通块** $c_1,c_2,\dots,c_C$，支付 $\sum_{i=1}^C(|c_i|+k)$ 的代价，才可以在这些连通块的各个节点处看节目；即，**被指定的节点必须被某个连通块包含，不被指定的节点不必被包含**。

Bessie 觉得这个策略的代价太昂贵了，考虑是否要改在 Mooloo 上看节目。为了帮助其决策，你应当告诉之 $k$ 取遍 $1\sim n$ 时看节目的最小总代价。

$1\le n\le2\times10^5$。


---

---
title: "[USACO23OPEN] Pareidolia P"
layout: "post"
diff: 省选/NOI-
pid: P9192
tag: ['动态规划 DP', '线段树', 'USACO', '2023', '矩阵加速']
---
# [USACO23OPEN] Pareidolia P
## 题目描述

Pareidolia is the phenomenon where your eyes tend to see familiar patterns in images where none really exist -- for example seeing a face in a cloud. As you might imagine, with Farmer John's constant proximity to cows, he often sees cow-related patterns in everyday objects. For example, if he looks at the string `bqessiyexbesszieb`, Farmer John's eyes ignore some of the letters and all he sees is `bessiebessie`.

Given a string $s$, let $B(s)$ represent the maximum number of repeated copies of `bessie` one can form by deleting zero or more of the characters from $s$. In the example above, $B(bqessiyexbesszieb)=2$. Furthermore, given a string $t$, let $A(t)$ represent the sum of $B(s)$ over all contiguous substrings $s$ of $t$.

Farmer John has a string t of length at most $2\times10^5$ consisting only of characters a-z. Please compute A(t), and how A(t) would change after $U (1\le U\le2\times10^5)$ updates, each changing a character of t. Updates are cumulative.
## 输入格式

The first line of input contains $t$.

The next line contains $U$, followed by $U$ lines each containing a position $p$ $(1\le p\le N)$ and a character $c$ in the range a-z, meaning that the pth character of $t$ is changed to $c$.
## 输出格式

Output $U+1$ lines, the total number of bessies that can be made across all substrings of $t$ before any updates and after each update.
## 样例

### 样例输入 #1
```
bessiebessie
3
3 l
7 s
3 s
```
### 样例输出 #1
```
14
7
1
7
```
## 提示

Before any updates, twelve substrings contain exactly $1$ `bessie` and $1$ string contains exactly $2$ `bessie`s, so the total number of bessies is $12⋅1+1⋅2=14$.

After one update, $t$ is `belsiebessie`. Seven substrings contain exactly one `bessie`.

After two updates, $t$ is `belsiesessie`. Only the entire string contains `bessie`.


Input $2$: $|t|,U\le300$;

Inputs $3-5$: $U\le10$;

Inputs $6-13$: $|t|,U\le10^5$;

Inputs $14-21$: No additional constraints.
## 题目翻译

### 题目描述

Pareidolia 是一种现象，指的是人们倾向于在并不真正存在的地方看到熟悉的图案——例如在云中看到一张脸。可以想象，由于农夫 John 经常与奶牛接触，他常常在日常物品中看到与奶牛相关的图案。例如，如果他看到字符串 `bqessiyexbesszieb`，农夫 John 的眼睛会忽略其中的一些字母，而他看到的只是 `bessiebessie`。

给定一个字符串 $s$，令 $B(s)$ 表示通过删除 $s$ 中的零个或多个字符后，能够形成的 `bessie` 的最大重复次数。在上面的例子中，$B(bqessiyexbesszieb)=2$。此外，给定一个字符串 $t$，令 $A(t)$ 表示所有连续子串 $s$ 的 $B(s)$ 之和。

农夫 John 有一个长度不超过 $2 \times 10^5$ 的字符串 $t$，且仅由字符 a-z 组成。请计算 $A(t)$，以及在 $U (1 \le U \le 2 \times 10^5)$ 次更新后 $A(t)$ 的变化情况，每次更新会修改 $t$ 中的一个字符。更新是累积的。

### 输入格式

第一行输入包含 $t$。

接下来的一行包含 $U$，随后是 $U$ 行，每行包含一个位置 $p$ $(1 \le p \le N)$ 和一个字符 $c$（范围为 a-z），表示将 $t$ 的第 $p$ 个字符修改为 $c$。

### 输出格式

输出 $U+1$ 行，分别表示在没有任何更新之前以及每次更新后，$t$ 的所有子串中能够形成的 `bessie` 的总数。

### 提示

在没有任何更新之前，有 12 个子串恰好包含 $1$ 个 `bessie`，有 $1$ 个子串恰好包含 $2$ 个 `bessie`，因此 `bessie` 的总数为 $12 \cdot 1 + 1 \cdot 2 = 14$。

第一次更新后，$t$ 变为 `belsiebessie`。有 7 个子串恰好包含一个 `bessie`。

第二次更新后，$t$ 变为 `belsiesessie`。只有整个字符串包含 `bessie`。

输入 $2$：$|t|, U \le 300$；

输入 $3-5$：$U \le 10$；

输入 $6-13$：$|t|, U \le 10^5$；

输入 $14-21$：没有额外限制。


---

---
title: "[USACO23OPEN] Good Bitstrings P"
layout: "post"
diff: 省选/NOI-
pid: P9193
tag: ['递推', 'USACO', '2023', 'O2优化', '向量']
---
# [USACO23OPEN] Good Bitstrings P
## 题目描述

For any two positive integers $a$ and $b$, define the function `gen_string(a,b)` by the following Python code:

```
def gen_string(a: int, b: int):
	res = ""
	ia, ib = 0, 0
	while ia + ib < a + b:
		if ia * b <= ib * a:
			res += '0'
			ia += 1
		else:
			res += '1'
			ib += 1
	return res
```

Equivalent C++ code:

```
string gen_string(int64_t a, int64_t b) {
	string res;
	int ia = 0, ib = 0;
	while (ia + ib < a + b) {
		if ((__int128)ia * b <= (__int128)ib * a) {
			res += '0';
			ia++;
		} else {
			res += '1';
			ib++;
		}
	}
	return res;
}
```

$ia$ will equal $a$ and $ib$ will equal $b$ when the loop terminates, so this function returns a bitstring of length $a+b$ with exactly $a$ zeroes and $b$ ones. For example, `gen_string(4,10)=01110110111011`.

Call $a$ bitstring $s$ **good** if there exist positive integers $x$ and $y$ such that s=`gen_string(x,y)`. Given two positive integers $A$ and $B$ $(1\le A,B\le10^{18})$, your job is to compute the number of good prefixes of `gen_string(A,B)`. For example, there are $6$ good prefixes of `gen_string(4,10)`:

```
x = 1 | y = 1 | gen_string(x, y) = 01
x = 1 | y = 2 | gen_string(x, y) = 011
x = 1 | y = 3 | gen_string(x, y) = 0111
x = 2 | y = 5 | gen_string(x, y) = 0111011
x = 3 | y = 7 | gen_string(x, y) = 0111011011
x = 4 | y = 10 | gen_string(x, y) = 01110110111011
```
## 输入格式

The first line contains $T$ $(1\le T\le10)$, the number of independent test cases.

Each of the next $T$ lines contains two integers $A$ and $B$.
## 输出格式

The answer for each test case on a new line.
## 样例

### 样例输入 #1
```
6
1 1
3 5
4 7
8 20
4 10
27 21

```
### 样例输出 #1
```
1
5
7
10
6
13
```
## 提示

Input $2$: $A,B\le100$;\
Input $3$: $A,B\le1000$;\
Inputs $4-7$: $A,B\le10^6$;\
Inputs $8-13$: All answers are at most $10^5$.\
Inputs $14-21$: No additional constraints.
## 题目翻译

### 题目描述

对于任意两个正整数 $a$ 和 $b$，定义函数 `gen_string(a,b)` 如下 Python 代码所示：

```python
def gen_string(a: int, b: int):
	res = ""
	ia, ib = 0, 0
	while ia + ib < a + b:
		if ia * b <= ib * a:
			res += '0'
			ia += 1
		else:
			res += '1'
			ib += 1
	return res
```

等效的 C++ 代码如下：

```cpp
string gen_string(int64_t a, int64_t b) {
	string res;
	int ia = 0, ib = 0;
	while (ia + ib < a + b) {
		if ((__int128)ia * b <= (__int128)ib * a) {
			res += '0';
			ia++;
		} else {
			res += '1';
			ib++;
		}
	}
	return res;
}
```

当循环结束时，$ia$ 将等于 $a$，$ib$ 将等于 $b$，因此该函数返回一个长度为 $a+b$ 的比特串，其中恰好包含 $a$ 个零和 $b$ 个一。例如，`gen_string(4,10)=01110110111011`。

称一个 $0/1$ 串 $s$ 是**好的**，如果存在正整数 $x$ 和 $y$，使得 $s = \text{gen\_string}(x,y)$。给定两个正整数 $A$ 和 $B$ $(1 \le A, B \le 10^{18})$，你的任务是计算 `gen_string(A,B)` 的所有好前缀的数量。例如，`gen_string(4,10)` 有 $6$ 个好前缀：

```
x = 1 | y = 1 | gen_string(x, y) = 01
x = 1 | y = 2 | gen_string(x, y) = 011
x = 1 | y = 3 | gen_string(x, y) = 0111
x = 2 | y = 5 | gen_string(x, y) = 0111011
x = 3 | y = 7 | gen_string(x, y) = 0111011011
x = 4 | y = 10 | gen_string(x, y) = 01110110111011
```

### 输入格式

第一行包含 $T$ $(1 \le T \le 10)$，表示独立测试用例的数量。

接下来的 $T$ 行，每行包含两个整数 $A$ 和 $B$。

### 输出格式

每个测试用例的答案单独占一行。

### 提示

输入 $2$：$A, B \le 100$；\
输入 $3$：$A, B \le 1000$；\
输入 $4-7$：$A, B \le 10^6$；\
输入 $8-13$：所有答案不超过 $10^5$；\
输入 $14-21$：没有额外限制。


---

---
title: "[USACO23DEC] A Graph Problem P"
layout: "post"
diff: 省选/NOI-
pid: P9984
tag: ['线段树', 'USACO', '并查集', '2023', 'Kruskal 重构树', 'O2优化', '哈希 hashing', '启发式合并']
---
# [USACO23DEC] A Graph Problem P
## 题目描述

为了丰富自己的数学知识，Bessie 选修了一门图论课程，她发现她被下面的问题困住了，请帮帮她！

给出一张连通的无向图，包含编号为 $1\dots N$ 的节点和编号为 $1\dots M$（$2 \le N \le 2\cdot 10^5$，$N - 1 \le M \le 4 \cdot 10^5$）的边，下边的操作将被实施：

1. 假设集合 $S=\{v\}$，变量 $h=0$。
2. 当 $|S|<N$，重复执行：
	1. 仅有一个顶点在集合 $S$ 中的边中，找到编号最小的那条，编号记为 $e$。
    2. 将 $e$ 不在 $S$ 中的那个顶点加入集合 $S$。
    3. 将 $h$ 修改为 $10h+e$。
3. 返回 $h$ 对 $10^9+7$ 取模的值。

输出这个过程的全部返回值。
## 输入格式

第一行包含 $N$ 和 $M$。接下来 $M$ 行，每行包含第 $e$ 条边的顶点 $(a_e,b_e)$，保证图连通，没有重边。
## 输出格式

输出 $N$ 行，第 $i$ 行包含在节点 $i$ 开始过程的返回值。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
```
### 样例输出 #1
```
12
12
21
```
### 样例输入 #2
```
5 6
1 2
3 4
2 4
2 3
2 5
1 5
```
### 样例输出 #2
```
1325
1325
2315
2315
5132
```
### 样例输入 #3
```
15 14
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
```
### 样例输出 #3
```
678925929
678925929
678862929
678787329
678709839
678632097
178554320
218476543
321398766
431520989
542453212
653475435
764507558
875540761
986574081
```
## 提示

### 样例解释 2

考虑在 $i=3$ 开始执行。首先，选择 $2$ 号边，$S=\{3,4\}$，$h=2$。然后，选择 $3$ 号边，$S=\{2,3,4\}$，$h=23$。接着，选择 $1$ 号边，$S=\{1,2,3,4\}$，$h=231$。最后，选择 $5$ 号边，$S=\{1,2,3,4,5\}$，$h=2315$。因此，$i=3$ 的答案是 $2315$。

### 样例解释 3

确保答案对 $10^9+7$ 取模。

### 测试点性质

- 测试点 $4$ 满足 $N,M \le 2000$。
- 测试点 $5-6$ 满足 $N \le 2000$。
- 测试点 $7-10$ 满足 $N \le 10000$。
- 测试点 $11-14$ 满足对于所有边，有 $a_e+1=b_e$。
- 测试点 $15-23$ 没有额外限制。


---

---
title: "[USACO23DEC] Train Scheduling P"
layout: "post"
diff: 省选/NOI-
pid: P9985
tag: ['动态规划 DP', 'USACO', '2023', 'O2优化', '动态规划优化']
---
# [USACO23DEC] Train Scheduling P
## 题目背景

**Note: The memory limit for this problem is 512MB, twice the default.**
## 题目描述

Bessie 找到了一份行车调度的新工作。现在有两座火车站 $A$ 和 $B$，由于预算限制，只有一条单线铁道连接起车站 $A$ 和 $B$。如果一列列车在 $t$ 时刻离开其中一座火车站，它将在 $t+T$（$1 \le T \le 10^{12}$）时刻到达另一座火车站。

现在有 $N$（$1 \le N \le 5000$）列火车的出发时间需要安排。第 $i$ 列火车必须在 $t_i$ 时刻后从车站 $s_i$ 出发（$s_i\in \{A,B\}$，$0 \le t_i \le 10^{12}$）。在同一时刻不允许铁道上有相反方向的列车，否则它们会相撞。但是，假设火车有可以忽略的尺寸，在同一时刻，铁道上可以有许多相同方向的列车。

帮助 Bessie 安排每辆列车的出发时间，在不会相撞的前提下最小化总延误时间。假设第 $i$ 辆列车被安排在 $a_i$ 时刻出发，总延误为 $\sum\limits_{i=1}^n{a_i-t_i}$。
## 输入格式

第一行包含 $N$ 和 $T$。

接下来 $N$ 行，第 $i$ 行包含用于描述第 $i$ 辆列车的 $s_i,t_i$。
## 输出格式

输出合法安排中最小总延误时间。
## 样例

### 样例输入 #1
```
1 95
B 63
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
4 1
B 3
B 2
A 1
A 3
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
4 10
A 1
B 2
A 3
A 21
```
### 样例输出 #3
```
13
```
### 样例输入 #4
```
8 125000000000
B 17108575619
B 57117098303
A 42515717584
B 26473500855
A 108514697534
B 110763448122
B 117731666682
A 29117227954
```
### 样例输出 #4
```
548047356974
```
## 提示

### 样例解释 1

唯一的一辆列车准点出发。

### 样例解释 2

有两种最佳方案。第一种是让列车 $2,3,4$ 准点出发，列车 $1$ 延误一分钟后出发。第二种是让列车 $1,2,3$ 准点出发，列车 $4$ 延误一分钟后出发。

### 样例解释 3

最佳方案是让列车 $1,3$ 准点出发，列车 $2$ 在时刻 $13$ 出发，列车 $4$ 在时刻 $23$ 出发。总延误为 $0+11+0+2=13$。

### 测试点性质

- 测试点 $5-6$ 满足 $N \le 15$。
- 测试点 $7-10$ 满足 $N \le 100$。
- 测试点 $11-14$ 满足 $N \le 500$。
- 测试点 $15-18$ 满足 $N \le 2000$。
- 测试点 $19-24$ 没有额外限制。


---

