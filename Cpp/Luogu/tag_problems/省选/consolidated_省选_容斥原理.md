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
title: "BZOJ4361 isn"
layout: "post"
diff: 省选/NOI-
pid: P10592
tag: ['动态规划 DP', '树状数组', 'O2优化', '容斥原理']
---
# BZOJ4361 isn
## 题目背景

题目来自原 BZOJ，我们承认题面及原数据的版权均属于原 BZOJ 或将题目授权给 BZOJ 使用的出题人。如果您是版权所有者且认为我们侵犯了您的权益，可联系我们。
## 题目描述

给出一个长度为 $n$ 的序列 $a_1,a_2,\dots a_n$。如果序列 $a$ 不是非降的，你必须从中删去一个数。

这一操作将被不断执行，直到 $A$ 非降为止。求有多少种不同的操作方案。操作方案不同当且仅当删除的顺序或次数不同。答案对 $10^9+7$ 取模。
## 输入格式

第一行输入一个正整数 $n$，表示序列长度。

第二行输入 $n$ 个正整数 $a_i$，表示序列。
## 输出格式

一行一个整数，表示答案对 $10^9+7$ 取模的值。
## 样例

### 样例输入 #1
```
4
1 7 5 3
```
### 样例输出 #1
```
18
```
## 提示

对于 $100\%$ 的数据，$1\leq n\leq 2\times 10^3$，$0\leq a_i \leq 2^{31}-1$。


---

---
title: "BZOJ2162 男生女生"
layout: "post"
diff: 省选/NOI-
pid: P10598
tag: ['O2优化', '二分图', '容斥原理']
---
# BZOJ2162 男生女生
## 题目背景

题目来自原 BZOJ，我们承认题面及原数据的版权均属于原 BZOJ 或将题目授权给 BZOJ 使用的出题人。如果您是版权所有者且认为我们侵犯了您的权益，可联系我们。

---

雨荨的班主任安远老师是一个非常严厉的老师。到了大学，男生和女生之间难免会出现一些暧昧关系，但这样显然是影响学习的。所以作为艾利斯顿的一块招牌，安远老师当然要拒绝这种现象的出现以及繁衍。

所以每当安远老师发现一个男生和一个女生放学走在一起或者男女生之间互相传纸条等，他就会立马制止并且通知家长。他也要求所有男女生晚上八点之后必须关手机，并且不定期打电话检查。于是安远老师的学生都感慨：这货不是大学，不是大学。
## 题目描述

安远老师的学生里，一共有 $n$ 个男生和 $n$ 个女生，编号都以 $1\sim n$ 编号。有 $m$ 对男女生之间有暧昧关系。现在安远老师想找出这样一个男女生群体，每个男生都和每个女生之间有暧昧关系，并且男女生总数最大。注意，男生数目或者女生数目可以为 $0$。

如果有多个这样的群体，安远老师会选择男生最多的那个群体，因为他觉得男生会很不安分。如果这样的群体依然不唯一，他会选择任意一个。

接下来，安远老师从选出的这个群体的所有暧昧关系中，选出 $k$ 个进行调查，使得这个群体的所有男生和女生，都至少和其中的一对暧昧关系有关系（即是这个暧昧关系的男/女主人公）。安远老师想让你告诉他总方案数除以 $19921228$ 的余数是多少。
## 输入格式

输入的第一行包含两个正整数 $n$ 和 $k$，分别代表男生女生的个数，以及安远老师要选择的暧昧关系个数。

第二行为一个正整数 $m$，代表暧昧关系总个数。接下来 $m$ 行，每行两个整数，代表一对有暧昧关系的男女生编号。
## 输出格式

第一行有两个空格隔开的整数，代表选择的团体内男生和女生的个数。第二行有一个整数，代表选法除以 $19921228$ 的余数。
## 样例

### 样例输入 #1
```
3 2 
4
1 1
1 2
2 1
2 2
```
### 样例输出 #1
```
2 2
2
```
## 提示

对于所有数据，$1\leq n \leq 50$，$1\leq m,k \leq 2500$。同一对暧昧关系不会在输入中出现多次。


---

---
title: "BZOJ4833 最小公倍佩尔数"
layout: "post"
diff: 省选/NOI-
pid: P10663
tag: ['数论', 'O2优化', '莫比乌斯反演', '容斥原理']
---
# BZOJ4833 最小公倍佩尔数
## 题目背景

题目来自 BZOJ 2017 年 4 月月赛。
## 题目描述

令 $(1+\sqrt{2})^n=e(n)+\sqrt{2}f(n)$，其中 $e(n),f(n)$ 都是整数，显然有 $(1-\sqrt{2})^n=e(n)-\sqrt{2}f(n)$。令 $g(n)=\operatorname{lcm}(f(1),f(2),\dots,f(n))$。

给定两个正整数 $n,p$，其中 $p$ 是质数，并且保证 $f(1),f(2),\dots,f(n)$ 在模 $p$ 意义下均不为 $0$，请计算 $\sum \limits_{i=1}^n i\times g(i)$ 模 $p$ 的值。
## 输入格式

第一行包含一个正整数 $T$，表示有 $T$ 组数据。

接下来是测试数据。每组测试数据只占一行，包含两个正整数 $n$ 和 $p$。
## 输出格式

对于每组测试数据，输出一行一个非负整数，表示这组数据的答案。
## 样例

### 样例输入 #1
```
5
1 233
2 233
3 233
4 233
5 233
```
### 样例输出 #1
```
1
5
35
42
121
```
## 提示

对于 $100\%$ 的数据，$1\leq T\leq 210$，$1\leq n\leq 10^6$，$2\leq p\leq 10^9+7$，$\sum n\leq 3\times 10^6$。


---

---
title: "【MX-X2-T4】「Cfz Round 4」Gcd with Xor"
layout: "post"
diff: 省选/NOI-
pid: P10855
tag: ['数学', '数论', 'O2优化', '莫比乌斯反演', '容斥原理', '字典树 Trie', '梦熊比赛']
---
# 【MX-X2-T4】「Cfz Round 4」Gcd with Xor
## 题目背景

原题链接：<https://oier.team/problems/X2D>。

---

ねえ もしも全て投げ捨てられたら  
呐 若然能将一切舍弃的话

笑って生きることが楽になるの  
笑着活下去这样的事就会变的轻松吗
## 题目描述

给定两个正整数 $n,k$。

定义 $\displaystyle f(x)=\sum_{i=1}^x \gcd(i,i\oplus x)^k$。计算 $\displaystyle \sum_{i=1}^n f(i)$。其中 $\gcd(a,b)$ 表示 $a$ 和 $b$ 的最大公因数，$\oplus$ 表示**按位异或**，即 C++ 中的 `^`。

由于答案可能很大，所以你只需要输出答案对 $10^9+7$ 取模的结果。
## 输入格式

**本题有多组测试数据。**

输入的第一行包含一个整数 $T$，表示测试数据组数。

接下来依次输入每组测试数据。对于每组测试数据，输入一行两个正整数 $n,k$。
## 输出格式

对于每组测试数据，输出一行一个整数，表示答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
5
3 2
10 1
261 261
2333 2333
124218 998244353
```
### 样例输出 #1
```
17
134
28873779
470507314
428587718

```
## 提示

**【样例解释】**

对于第 $1$ 组测试数据：

$f(1)=\gcd(1,0)^2=1$。

$f(2)=\gcd(1,3)^2+\gcd(2,0)^2=5$。

$f(3)=\gcd(1,2)^2+\gcd(2,1)^2+\gcd(3,0)^2=11$。

$f(1)+f(2)+f(3)=17$。

**【数据范围】**

对于所有测试数据，$1\le T\le 1000$，$1\le n\le 2\times 10^5$，$\sum n\le 2\times 10^5$，$1\le k\le 10^9$。

**本题采用捆绑测试。**

设 $\sum n$ 表示单个测试点中 $n$ 的和。

- Subtask 1（10 points）：$\sum n\le 2000$。
- Subtask 2（12 points）：$\sum n\le 10^4$。
- Subtask 3（15 points）：$k=1$。
- Subtask 4（45 points）：$\sum n\le 10^5$。
- Subtask 5（18 points）：无特殊限制。


---

---
title: "「KDOI-07」对树链剖分的爱"
layout: "post"
diff: 省选/NOI-
pid: P10879
tag: ['动态规划 DP', '数学', '图论', '2024', '洛谷原创', 'O2优化', '动态规划优化', '组合数学', '容斥原理', '期望']
---
# 「KDOI-07」对树链剖分的爱
## 题目背景

楼下说得对，但是 sszcdjr 在 NOI 2024 D2T2 用巧妙做法把我的暴力树剖爆掉了。

楼上说得对，但是树链剖分把我送上 10√ 了，所以我出了这道题以表示我对树链剖分的爱喵。
## 题目描述

给出一棵 $n$ 个节点以 $1$ 为根的有根树。对于第 $2\leq i\leq n$ 个节点，其父亲 $f_i$ 在 $[l_i,r_i]$ 中均匀随机。每个树的边有边权，初始为 $0$。

现在有 $m$ 次操作，第 $i$ 次操作表示将 $(u_i,v_i)$ 的路径上所有的边的权值统一加上 $w_i$。$m$ 次操作结束后，对于所有 $i=2\sim n$，求 $(i,f_i)$ 边上权值的期望，对 $998244353$ 取模。
## 输入格式

第一行一个正整数表示 $n$。

接下来 $n-1$ 行，其中第 $i$ 行两个正整数表示 $l_{i+1},r_{i+1}$。

接下来一行一个正整数表示 $m$。

接下来 $m$ 行，第 $i$ 行三个正整数表示 $u_i,v_i,w_i$。
## 输出格式

一行 $n-1$ 个正整数，其中第 $i$ 个表示边 $(i+1,f_{i+1})$ 边权的期望，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3
1 1
1 2
1
1 3 2
```
### 样例输出 #1
```
1 2
```
### 样例输入 #2
```
5
1 1
1 2
3 3
2 4
9
2 5 497855355
1 5 840823564
3 1 295265328
2 3 457999227
4 4 235621825
2 1 86836399
5 2 800390742
5 3 869167938
2 4 269250165
```
### 样例输出 #2
```
405260353 409046983 606499796 13504540
```
## 提示

### 样例解释 1

所有节点的父亲共有 $2$ 种可能的情况：

- $f_2=1,f_3=1$，此时 $(f_2,2),(f_3,3)$ 边上的权值分别是 $0,2$。

- $f_2=1,f_3=2$，此时 $(f_2,2),(f_3,3)$ 边上的权值分别是 $2,2$。

于是边 $(f_2,2)$ 边权的期望为 $\dfrac{0+2}{2}=1$，边 $(f_3,3)$ 边权的期望为 $\dfrac{2+2}{2}=2$。


---
### 数据规模与约定
**本题采用捆绑测试。**

| $\text{Subtask}$ | $n\leq$ | $m\leq$ | 分数 |
| :-----------: | :-----------: |  :-----------: | :-----------: |
| $1$ | $10$ | $10$ | $20$ |
| $2$ | $50$ | $50$ | $20$ |
| $3$ | $500$ | $500$ | $20$ |
| $4$ | $5000$ | $1$ | $20$ |
| $5$ | $5000$ | $5000$ | $20$|


对于所有数据，保证 $1\leq n,m\leq5000$，$1\leq l_i\leq r_i<i$，$1\leq u_i,v_i\leq n$，$1\leq w_i\leq 10^9$。


---

---
title: "【MX-S6-T4】「KDOI-11」彩灯晚会"
layout: "post"
diff: 省选/NOI-
pid: P11292
tag: ['动态规划 DP', 'O2优化', '动态规划优化', '拓扑排序', '组合数学', '容斥原理', '梦熊比赛']
---
# 【MX-S6-T4】「KDOI-11」彩灯晚会
## 题目背景

原题链接：<https://oier.team/problems/S6D>。
## 题目描述

小 K 家的房子还蛮大的，所以他举办了彩灯晚会。

彩灯晚会显然有彩灯。于是小 K 找来了 $n$ 盏彩灯。

小 K 不希望彩灯散在地上，于是他用 $m$ 条**有向边**连接了这些彩灯，使得他们连在一起。也就是说，在将有向边看成无向边的情况下，这些彩灯是连通的。保证该图为**有向无环图**。

小 K 的彩灯很厉害，每个都可以独立地发出 $k$ 种颜色中的任意一种。小 K 作为世界顶尖 Light Glowing Master（简称 LGM），决定将所有方案（共 $k^n$ 种）都尝试一下。

小 K 不喜欢很多的颜色，于是他给定了一个正整数 $l$，并定义一个方案的美丽度为每种颜色长度为 $l$ 的链数量的平方之和。形式化地讲，设第 $i$ 种颜色的长度为 $l$ 的链的数量为 $cnt_i$，则一个方案的美丽度为 $\sum_{i=1}^kcnt_i^2$。

现在小 K 想知道所有 $k^n$ 种方案的美丽度之和，对 $998244353$ 取模。

两种方案是不同的当且仅当存在某个彩灯在两种方案中发出不同的颜色。

一条长度为 $l$ 的链是一个 $2l-1$ 元组 $(v_1,e_1,v_2,e_2,\dots,e_{l-1},v_l)$，使得对于任意 $1\leq i<l$，第 $e_i$ 条有向边是由 $v_i$ 连向 $v_{i+1}$ 的。两条长度为 $l$ 的链 $(v_1,e_1,v_2,e_2,\dots,e_{l-1},v_l)$ 和 $(v'_1,e'_1,v'_2,e'_2,\dots,e'_{l-1},v'_l)$ 不同当且仅当存在 $1\leq i<l$ 满足 $e_i\neq e'_i$ 或存在 $1\leq i\leq l$ 满足 $v_i\neq v'_i$。

一种颜色 $x$ 的长度为 $l$ 的链是一条长度为 $l$ 的链 $(v_1,e_1,v_2,e_2,\dots,e_{l-1},v_l)$ 使得对于任意 $1\leq i\leq l$，$v_i$ 编号的彩灯发出颜色为 $x$。
## 输入格式

第一行，五个非负整数 $id,n,k,l,M$，其中 $id$ 表示测试点编号（所有样例满足 $id=0$），$n$ 表示彩灯数量，$k$ 表示颜色数量，$l$ 表示链的长度，$M$ 的意义如后文所示。

接下来 $M$ 行，第 $i$ 行三个正整数 $u_i,v_i,c_i$，表示有 $c_i$ 条 $u_i\to v_i$ 的有向边。也就是说，第 $\bigl(\sum_{j=1}^{i-1}c_j\bigr)+1$ 至第 $\bigl(\sum_{j=1}^ic_j\bigr)$ 条有向边由 $u_i$ 连向 $v_i$。

题面中 $m$ 满足 $m=\sum_{i=1}^Mc_i$。保证：$(u,v)$ 互不相同，给定图为有向无环图，在将有向边看成无向边的情况下，彩灯是连通的。
## 输出格式

仅一行，一个非负整数，表示所有 $k^n$ 种方案的美丽度之和，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
0 3 2 2 2
1 3 1
3 2 1
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
0 5 4 3 7
1 4 4
1 5 2
4 3 1
5 3 2
3 2 3
4 5 1
5 2 2
```
### 样例输出 #2
```
16096
```
## 提示

**【样例解释 #1】**

共有 $2^3=8$ 种不同的彩灯显示颜色的方案，如下表所示（不妨假设颜色为黑和白）：

| 编号 | $1$ 号彩灯颜色 | $2$ 号彩灯颜色 | $3$ 号彩灯颜色 | 美丽度 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | 黑 | 黑 | 黑 | $4$ |
| $2$ | 黑 | 黑 | 白 | $0$ |
| $3$ | 黑 | 白 | 黑 | $1$ |
| $4$ | 黑 | 白 | 白 | $1$ |
| $5$ | 白 | 黑 | 黑 | $1$ |
| $6$ | 白 | 黑 | 白 | $1$ |
| $7$ | 白 | 白 | 黑 | $0$ |
| $8$ | 白 | 白 | 白 | $4$ |

美丽度之和为 $4+0+1+1+1+1+0+4=12$。

**【样例 #3】**

见附件中的 `party/party3.in` 与 `party/party3.ans`。

该组样例满足测试点 $1$ 的约束条件。

**【样例 #4】**

见附件中的 `party/party4.in` 与 `party/party4.ans`。

该组样例满足测试点 $2\sim3$ 的约束条件。

**【样例 #5】**

见附件中的 `party/party5.in` 与 `party/party5.ans`。

该组样例满足测试点 $4\sim5$ 的约束条件。

**【样例 #6】**

见附件中的 `party/party6.in` 与 `party/party6.ans`。

该组样例满足测试点 $6\sim9$ 的约束条件。

**【样例 #7】**

见附件中的 `party/party7.in` 与 `party/party7.ans`。

该组样例满足测试点 $10\sim12$ 的约束条件。

**【样例 #8】**

见附件中的 `party/party8.in` 与 `party/party8.ans`。

该组样例满足测试点 $13\sim15$ 的约束条件。

**【样例 #9】**

见附件中的 `party/party9.in` 与 `party/party9.ans`。

该组样例满足测试点 $20\sim21$ 的约束条件。

**【数据范围】**

记 $P=998244353$，对于所有测试数据，保证：$1\leq n\leq300$，$1\leq M\leq\frac{n(n-1)}{2}$，$1\leq k<P$，$1\leq l\leq 20$，$1\leq c_i<P$，$(u_i,v_i)$ 互不相同，给定图为有向无环图，在将有向边看成无向边的情况下，彩灯是连通的。

| 测试点编号 | $n\leq$ | $k\leq$ | $l\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | $6$ | $6$ | $6$ | $m\leq10$，$c_i=1$ |
| $2\sim3$ | $300$ | $P-1$ | $1$ | 无 |
| $4\sim5$ | $300$ | $P-1$ | $2$ | 无 |
| $6\sim9$ | $300$ | $P-1$ | $3$ | 无 |
| $10\sim12$ | $300$ | $P-1$ | $20$ | $M=n-1$ 且有且仅有一个点入度为 $0$ |
| $13\sim15$ | $30$ | $P-1$ | $10$ | 无 |
| $16$ | $150$ | $P-1$ | $7$ | 无 |
| $17$ | $150$ | $P-1$ | $10$ | 无 |
| $18\sim19$ | $150$ | $P-1$ | $13$ | 无 |
| $20\sim21$ | $300$ | $P-1$ | $9$ | 无 |
| $22$ | $300$ | $P-1$ | $13$ | 无 |
| $23$ | $300$ | $P-1$ | $16$ | 无 |
| $24\sim25$ | $300$ | $P-1$ | $20$ | 无 |


---

---
title: "[COCI 2024/2025 #1] 教师 / Učiteljica"
layout: "post"
diff: 省选/NOI-
pid: P11390
tag: ['线段树', '2024', '容斥原理', 'COCI（克罗地亚）']
---
# [COCI 2024/2025 #1] 教师 / Učiteljica
## 题目背景

译自 [COCI 2024/2025 #1](https://hsin.hr/coci/) T4。$\texttt{5s,0.5G}$。满分为 $120$。
## 题目描述

给定长度为 $n$ 的正整数序列 $a_1,a_2,\cdots,a_n$。给定常数 $k$。

求出满足以下条件的二元组 $(l,r)$ 的数量：

- $1\le l\le r\le n$；
- 对于任意 $1\le i\le k$，都存在一个数 $x$，使得 $x$ 在 $a_l,a_{l+1},\ldots,a_r$ 间出现**恰好** $i$ 次。
## 输入格式


第一行，两个正整数 $n,k$。

第二行，$n$ 个正整数 $a_1,a_2,\cdots,a_n$。
## 输出格式


输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3 1
1 2 1
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
6 3
6 5 6 4 5 5
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
6 2
5 4 5 2 6 5
```
### 样例输出 #3
```
5
```
## 提示


对于 $100\%$ 的数据，保证：

- $1\le n\le 10^5$；    
- $1\le k\le 4$；
- $1\le a_i\le n$。


| 子任务编号 | $n\le$ |  特殊性质 | 得分 |  
| :--: | :--: | :--: |:--: | 
| $ 1 $    | $10^3$ |  |   $ 20 $   |  
| $ 2 $    | $10^5$ | A  |  $ 15 $   |  
| $ 3 $    | $10^5$ | B  |  $ 35 $   |  
| $ 4 $    | $10^5$ |  |  $ 50 $   |  

- 特殊性质 A：$1\le a_i\le k$。
- 特殊性质 B：$k=1$。




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
title: "调的啥啊"
layout: "post"
diff: 省选/NOI-
pid: P11771
tag: ['线段树', '洛谷原创', 'O2优化', '容斥原理', '洛谷月赛']
---
# 调的啥啊
## 题目背景

**为避免卡常，本题时限为比赛时的 2 倍。**

你试过用笔记本的触摸板操作扒谱吗？

阿绫正在玩天依——最新的 X Studio 声库，由于触控板和鼠标神秘失踪，她每调整一个音符都极其费力……

## 题目描述

在阿绫正在调的序列中一共有 $n$ 个音符，从左至右第 $i$ 个音符的音高为 $s_i$。阿绫发现其中三个音符 $s_i,s_j,s_k~(1\le i<j<k\le n)$ 产生的听感不佳，她决定将它们调整为 $s_i',s_j',s_k'$，使得 $s_i'\le s_k'$ 且 $s_j'\le s_k'$。扒拉触摸板真的很难受：

- 调节 $s_i$ 到 $s_i'$ 需要耗费阿绫 $a\times|s_i-s_i'|$ 的精力；
- 调节 $s_j$ 到 $s_j'$ 需要耗费阿绫 $b\times|s_j-s_j'|$ 的精力；
- 调节 $s_k$ 到 $s_k'$ 需要耗费阿绫 $c\times|s_k-s_k'|$ 的精力。

于是，调节完这三个音符，阿绫耗费的精力为：
$$
z=a\cdot|s_i-s_i'|+b\cdot|s_j-s_j'|+c\cdot|s_k-s_k'|.
$$

阿绫自然会找到使得 $z$ 值最小的 $(s_i',s_j',s_k')$，记此时的 $z$ 值为 $f(i,j,k)$。现在阿绫想知道，对于所有满足 $i<j<k$ 的 $(i,j,k)$，$f(i,j,k)$ 之和是多少呢？你只需要回答她这一答案对 $2^{32}$ 取模的结果。
## 输入格式

第一行一个整数 $n$ 表示音符序列的长度。

第二行三个整数 $a$，$b$，$c$。

第三行 $n$ 个整数表示 $s$ 序列，也就是每个音符的音高。
## 输出格式

一行一个整数即答案。
## 样例

### 样例输入 #1
```
4
3 4 5
2 4 3 1
```
### 样例输出 #1
```
39
```
## 提示

### 样例解释

$f(1,2,3)=4$，其中一组最优的 $(s_i',s_j',s_k')$ 为 $(2,3,3)$。

$f(1,2,4)=13$，其中一组最优的 $(s_i',s_j',s_k')$ 为 $(2,2,2)$。

$f(1,3,4)=9$，其中一组最优的 $(s_i',s_j',s_k')$ 为 $(2,2,2)$。

$f(2,3,4)=13$，其中一组最优的 $(s_i',s_j',s_k')$ 为 $(3,3,3)$。

$f(i,j,k)$ 的总和为 $4+13+9+13=39$。

### 数据规模与约定

**本题采用捆绑测试。** 仅当你通过了该子任务的全部测试数据才能获得该子任务的分值。

对于 $100\%$ 的数据，$3\le n\le5\times10^5$，$1\le s_i,a,b,c\le 10^9$。

对于不同的子任务，作如下约定：

| 子任务编号	| $n$ | 特殊性质 | 子任务分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $=3$ | 无 | $5$ |
| $2$ | $\le300$ | 无 | $5$ |
| $3$ | $\le1000$ | 无 | $10$ |
| $4$ | $\le5\times10^3$ | 无 | $20$ |
| $5$ | $\le5\times10^4$ | 无 | $20$ |
| $6$ | $\le5\times10^5$ | 有 | $20$ |
| $7$ | $\le5\times10^5$ | 无 | $20$ |

特殊性质：出现的不同音高不超过 $10$ 种。


---

---
title: "[PA 2019 Final] 数图 / Grafy"
layout: "post"
diff: 省选/NOI-
pid: P11817
tag: ['递推', '2019', '组合数学', '容斥原理', '生成函数', '高斯消元', 'PA（波兰）']
---
# [PA 2019 Final] 数图 / Grafy
## 题目背景

译自 PA 2019 Final。$\texttt{5s,256M}$。


本题数据为自造。

std: joke3579，validator & generator: Starrykiller。

加强版：P11821。**请勿提交 OEIS 题解。**
## 题目描述

求出 $n$ 个节点的满足以下条件的**有标号有向简单图**的数量：

- $\forall 1\le i\le n$，$\operatorname{deg_{out}}(i)=\operatorname{deg_{in}}(i)=2$。

这里，$\operatorname{deg_{out}}(u)$ 指节点 $u$ 的出度，$\operatorname{deg_{in}}(u)$ 指节点 $u$ 的入度。

你只需要输出答案对给定大素数 $p$ 取模后的结果。


注意我们是对**有标号**的「有向简单图」计数。也就是说，这张图中无重边自环。注意 $u\to v$ 和 $v\to u$ 同时出现是允许的。



## 输入格式

一行两个正整数 $n,p$。
## 输出格式

一行一个非负整数，表示答案。
## 样例

### 样例输入 #1
```
4 1000000007
```
### 样例输出 #1
```
9
```
## 提示

- $3\le n\le 500$；
- $10^8+7\le p\le 10^9+7$，$p$ 为素数。




---

---
title: "「Stoi2025」爱的飞行日记"
layout: "post"
diff: 省选/NOI-
pid: P11888
tag: ['2025', '数论', 'O2优化', '莫比乌斯反演', '容斥原理', '逆元', '洛谷比赛', '整除分块', 'Dirichlet 卷积', '筛法']
---
# 「Stoi2025」爱的飞行日记
## 题目背景

![](bilibili:BV1fx411N7bU?page=125)
## 题目描述

$t$ 组询问，每次询问给定正整数 $n,m$，计算

$$\prod_{a_1=1}^{m}\prod_{a_2=1}^{m}\cdots\prod_{a_n=1}^{m}\operatorname{lcm}(f_{a_1},f_{a_2},\dots,f_{a_n})\bmod{37426667}$$

的值。其中 $f_i$ 是斐波那契数，满足 $f_1=f_2=1$，且 $f_i=f_{i-1}+f_{i-2},\forall n\ge3$。
## 输入格式

第一行输入一个正整数 $t$ 表示询问组数。

接下来 $t$ 行，每行两个正整数 $n,m$ 表示一次询问。
## 输出格式

每次询问输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2
1 3
2 3

```
### 样例输出 #1
```
2
32

```
## 提示

#### 样例解释

对于第一组询问，有答案为 $f_1f_2f_3=1\times1\times2=2$。

对于第二组询问，当 $a_1,a_2\in\{1,2\}$ 时 $\operatorname{lcm}(f_{a_1},f_{a_2})=1$，否则 $\operatorname{lcm}(f_{a_1},f_{a_2})=2$。故答案为 $2^5=32$。

#### 数据范围与限制

**本题采用捆绑测试，各 Subtask 的限制与分值如下。**

| Subtask No. | $t\le$ | $n\le$ | $m\le$ | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $1$ | $2$ | $2 \times 10^3$ | $13$ |
| $2$ | $5$ | $2 \times 10^5$ | $2 \times 10^5$ | $24$ |
| $3$ | $5$ | $2 \times 10^7$ | $2 \times 10^7$ | $36$ |
| $4$ | $300$ | $2 \times 10^{17}$ | $2 \times 10^7$ | $27$ |

对于所有数据，满足 $1 \le t \le 300, 1 \le n \le 2 \times 10^{17}, 1 \le m \le 2 \times 10^7$。


---

---
title: "[蓝桥杯 2024 国研究生组] 深度优先搜索"
layout: "post"
diff: 省选/NOI-
pid: P12320
tag: ['2024', '组合数学', '容斥原理', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国研究生组] 深度优先搜索
## 题目描述

小蓝正在学习深度优先搜索。给出一段小蓝写的代码

```cpp
void dfs(int rt, int deep, int fa) {
    a[++cnt] = deep;
    for (int i = head[rt]; i; i = e[i].next)
        if (e[i].to != fa) dfs(e[i].to, deep + 1, rt);
}
```

对一个有根树执行 `dfs(root, 0, 0)` 可以生成一个长度为树中结点个数的序列，依次表示对遍历的所有结点的深度，小蓝认为假如一个序列能够通过对一个有根树执行 `dfs` 得到，这个序列就是合法的。现在小蓝有一个只包含 $-1$ 和非负整数的序列，小蓝想要知道，有多少种把 $-1$ 替换成任意非负整数的方案，使得该序列合法。
## 输入格式

输入的第一行包含一个正整数 $n$ 表示序列长度。

第二行包含 $n$ 个非负整数或 $-1$，相邻整数之间使用一个空格分隔，表示序列中的数 $a_i$。
## 输出格式

输出一行包含一个整数，表示答案除以 $10^9 + 7$ 的余数。
## 样例

### 样例输入 #1
```
2
1 -1
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
4
0 1 -1 1
```
### 样例输出 #2
```
2
```
## 提示

### 样例说明

对于样例 $2$，两个合法的序列是 $\{0, 1, 1, 1\}$ 和 $\{0, 1, 2, 1\}$。

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，保证序列中不会出现两个连续的 $-1$，即若 $a_i = -1$，则 $a_{i+1} \neq -1$。
- 对于 $50\%$ 的评测用例，$n \leq 300$；
- 对于所有评测用例，$1 \leq n \leq 1000000$，$-1 \leq a_i \leq n$。


---

---
title: "[UOI 2020] Topological Sorting of a Tree"
layout: "post"
diff: 省选/NOI-
pid: P12639
tag: ['动态规划 DP', '2020', '树形 DP', '拓扑排序', '组合数学', '前缀和', '容斥原理', 'UOI（乌克兰）']
---
# [UOI 2020] Topological Sorting of a Tree
## 题目描述

You are given a tree with $n$ vertices, numbered from $1$ to $n$. The root of the tree is the vertex with number $1$. For each $v$ from $2$ to $n$, let's define $p_v$ as the number of the vertex adjacent to $v$ that lies on the simple path between vertex $v$ and the root. Each edge $(p_v, v)$ is labeled with the symbol $\tt{<}$ or $\tt{>}$.

Find the number of ways to place the numbers from $1$ to $n$ in the vertices of the tree, such that each number is used exactly once and all the relationships indicated on the edges are satisfied. That is, for all edges with the symbol $\tt{<}$, $a[p_v] < a[v]$ should hold, and for all edges with the symbol $\tt{>}$, $a[p_v] > a[v]$ should hold.

Since the answer can be very large, output it modulo $10^9 + 7$.
## 输入格式

The first line contains a single integer $n$ ($1 \leq n \leq 3\,000$) - the number of vertices in the tree.

Each of the next $n-1$ lines contains a single integer $p_i$ ($1 \leq p_i < i$) and a character $c_i$ ($c_i \in \{\tt{<}, \tt{>}\}$), indicating that the edge between vertices with indices $p_i$ and $i$ is labeled with the symbol $c_i$. Note that the indexing starts from $2$.
## 输出格式

Output a single integer - the number of ways to arrange all numbers from $1$ to $n$ in the vertices of the tree such that all the relationships indicated on the edges are satisfied. Note that you should output the remainder of the division by $10^9 + 7$, not the actual answer.
## 样例

### 样例输入 #1
```
4
1 <
2 <
3 >
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4
1 <
1 <
1 <
```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
5
1 <
1 <
3 >
3 >
```
### 样例输出 #3
```
18
```
## 提示

- ($8$ points) $n \leq 10$;
- ($6$ points) $n \leq 18$;
- ($10$ points) $c_i = \tt{<}$;
- ($4$ points) $p_i = 1$;
- ($13$ points) $p_i = i - 1, 1 \leq n \leq 200$;
- ($19$ points) $p_i = i - 1$;
- ($24$ points) $n \leq 200$;
- ($16$ points) no additional constraints.


---

---
title: "回报"
layout: "post"
diff: 省选/NOI-
pid: P12735
tag: ['2025', '洛谷原创', '组合数学', '容斥原理', '快速数论变换 NTT', '洛谷月赛']
---
# 回报
## 题目背景

> 在我看来，得到太多的人明明是我，反倒是我该思考怎么回报才对。\
——浅村悠太
## 题目描述

悠太需要帮沙季找到合适的学习用音乐。

他找到了一个包含 $n$ 首音乐的专辑，其中的音乐编号为从 $1$ 至 $n$，播放每首音乐均需要 $1$ 分钟。沙季有 A 和 B 两门需要学的课程，每次学习 A 和 B 分别需要花 $a,b$ 分钟。为了更好地帮助她，悠太打算将音乐的播放顺序重新排列。具体地，他要选择一个长为 $n$ 的排列 $p_1,\dots,p_n$，使得其中存在两个长度分别为 $a,b$ 的循环 $A,B$，且 $A$ 中的任意一个元素小于 $B$ 中的任意一个元素。

排列中的一个长为 $k$ 的循环 $C$ 是一个由不同整数组成的序列 $c_1,\dots,c_k$，满足 $1\le c_1\le n$，$c_{i+1}=p_{c_i},i=1,\dots,k-1$，且 $p_{c_k}=c_1$。

悠太想要求出有多少满足要求的排列 $p$。由于答案可能很大，你只需要告诉他答案对 $998244353$ 取模的结果。
## 输入格式

输入一行三个整数表示序列长度 $n$ 与 $a,b$。
## 输出格式

输出一行一个整数，表示满足要求的排列的数量取模 $998244353$ 的结果。
## 样例

### 样例输入 #1
```
4 2 1

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
678 12 34

```
### 样例输出 #2
```
951781526

```
### 样例输入 #3
```
1987 654 321

```
### 样例输出 #3
```
27905503

```
### 样例输入 #4
```
1000000 13 20

```
### 样例输出 #4
```
912829543

```
## 提示

#### 样例 1 解释

满足要求的排列有 $(2,1,3,4),(3,2,1,4),(1,3,2,4)$，共 $3$ 个。

#### 数据范围与限制

**本题采用捆绑测试，各 Subtask 的限制与分值如下。**

| Subtask No. | $n\le$ | 特殊性质 | 分值 | 依赖子任务 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $10$ | 有 | $7$ |  |
| $2$ | $700$ | 有 | $10$ | $1$ |
| $3$ | $700$ | 无 | $20$ | $1,2$ |
| $4$ | $2000$ | 有 | $10$ | $1,2$ |
| $5$ | $2000$ | 无 | $30$ | $1,2,3,4$ |
| $6$ | $10^6$ | 有 | $20$ | $1,2,4$ |
| $7$ | $10^6$ | 无 | $3$ | $1,2,3,4,5,6$ |

特殊性质：$\min(a,b)=1$。

对于所有数据，$1\le n\le10^6$，$1\le a,b<a+b\le n$。


---

---
title: "【MX-X13-T6】「KDOI-12」能做到的也只不过是静等缘分耗尽的那一天。"
layout: "post"
diff: 省选/NOI-
pid: P13011
tag: ['动态规划 DP', '数学', 'O2优化', '组合数学', '容斥原理', '梦熊比赛']
---
# 【MX-X13-T6】「KDOI-12」能做到的也只不过是静等缘分耗尽的那一天。
## 题目背景

待到缘分耗尽，关系断裂，我们还会在一起吗？
## 题目描述

对于一个排列 $p_{1\sim n}$，建出其大根[笛卡尔树](https://www.luogu.com.cn/problem/P5854)，并断开每个点与其右儿子（如果存在）的连边，记最后所成的森林为 $T(p)$。

例如 $p_{1\sim 5} = [1, 3, 2, 5, 4]$，其大根笛卡尔树与 $T(p)$ 分别如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6mikhar1.png)![](https://cdn.luogu.com.cn/upload/image_hosting/otv9hnhe.png)

在给定 $n, x, y$ 的情况下，你需要回答，在 $n!$ 种 $1\sim n$ 的排列 $p_{1\sim n}$ 中，有多少种 $p$ 使得节点 $x$ 与节点 $y$ 在 $T(p)$ 中属于同一棵树。**节点指的是编号而非在 $p$ 中的权值。**

由于答案可能很大，输出的答案需要对一个质数 $P$ 取模。
## 输入格式

**本题有多组测试数据。**

第一行，两个正整数 $T, P$，表示测试数据组数与模数。**保证 $\bm P$ 为质数**。对于每组测试数据：

* 仅一行，三个正整数 $n, x, y$。
## 输出格式

对于每组测试数据，一行，一个非负整数，表示满足题目条件的排列数量，对 $P$ 取模。
## 样例

### 样例输入 #1
```
10 1000000007
4 1 4
4 2 2
4 3 2
5 4 2
7 3 5
8 2 7
10 3 8
100 99 6
1000 234 789
5000 1234 4321
```
### 样例输出 #1
```
6
24
8
25
882
3840
270000
220955222
251832899
768412458

```
## 提示

**【样例解释】**

对于样例的第一组测试数据：有 $[1, 2, 3, 4], [1, 3, 2, 4], [2, 1, 3, 4], [2, 3, 1, 4], [3, 1, 2, 4], [3, 2, 1, 4]$ 共 $6$ 种排列满足条件。

对于样例的第二组测试数据：任意 $1\sim 4$ 的排列均满足条件。

**【数据范围】**

**本题使用捆绑测试。**

| 子任务编号 | 分值 | $n\leq$ | $T\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | $5$ | $8$ | $10^6$ | 无 |
| $2$ | $15$ | $2000$ | $2000$ | 无 |
| $3$ | $15$ | $2000$ | $10^6$ | 无 |
| $4$ | $25$ | $5\times10^6$ | $20$ | 无 |
| $5$ | $15$ | $10^5$ | $10^6$ | A |
| $6$ | $25$ | $5\times10^6$ | $10^6$ | 无 |

* 特殊性质 A：$P=998244353$。

对于所有数据：$1\leq T\leq10^6$，$1\le x, y\le n\le 5\times 10^6$，$10^8\le P\le 10^9 + 7$ 且 $P$ 为质数。

**【提示】**

请使用较快的读入方式。


---

---
title: "Mivik 写书"
layout: "post"
diff: 省选/NOI-
pid: P1316
tag: ['字符串', '枚举', '容斥原理', '快速数论变换 NTT']
---
# Mivik 写书
## 题目背景

Mivik 想当大作家。
## 题目描述

Mivik 的键盘上有 $m$ 个不同的按键，对应着 $m$ 个不同的字符。由于 Mivik 不会写文章，所以他只好**等概率**随机乱按了 $n$ 个键，打出了一篇文章。

Mivik 定义一篇文章的复杂度是这篇文章所有**非空**本质不同子串的数目。我们认为两个字符串本质不同当且仅当它们的长度不同或者它们有任意一位上的字符不同。例如，文章 `abaa` 的复杂度是 8，因为它一共有 `a`、`b`、`ab`、`ba`、`aa`、`aba`、`baa`、`abaa` 这 8 个非空的本质不同子串。

Mivik 现在想知道，这篇文章期望的复杂度是多少。由于 Mivik 不喜欢奇形怪状的小数，你只需要输出期望的复杂度对 $10^9+7$ 取模后的值。
## 输入格式

一行两个整数 $n$ 和 $m$，意义见题目描述。
## 输出格式

一行一个整数，代表答案对 $10^9+7$ 取模后的值。
## 样例

### 样例输入 #1
```
2 2
```
### 样例输出 #1
```
500000006
```
### 样例输入 #2
```
3 3
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
3 4
```
### 样例输出 #3
```
250000007
```
## 提示

### 样例解释

样例一：假设键盘上的字符分别为 `a` 和 `b`，那么可能打出来的文章一共有 `aa`、`ab`、`ba`、`bb` 四种，它们的复杂度分别为 2、3、3、2，因此答案为 $\frac{2+3+3+2}{4}=\frac{5}{2}$，对 $10^9+7$ 取模后得到 500000006。

### 数据范围

对于全部数据，有 $1\le n\le 20$，$1\le m\le 5\cdot 10^6$。

Subtask 1 (10 pts)：满足 $1\le n, m\le 7$。

Subtask 2 (20 pts)：满足 $1\le n\le 5$。

Subtask 3 (20 pts)：满足 $1\le n\le 10$。

Subtask 4 (50 pts)：无特殊限制。


---

---
title: "[GCJ 2016 Finals] Gallery of Pillars"
layout: "post"
diff: 省选/NOI-
pid: P13208
tag: ['2016', '数论', '莫比乌斯反演', '容斥原理', 'Google Code Jam']
---
# [GCJ 2016 Finals] Gallery of Pillars
## 题目描述

Your friend Cody-Jamal is working on his new artistic installment called "Gallery of Pillars". The installment is to be exhibited in a square gallery of $\mathbf{N}$ by $\mathbf{N}$ meters. The gallery is divided into $\mathbf{N}^{2}$ squares of 1 by 1 meter, forming an $\mathbf{N}$ by $\mathbf{N}$ matrix. The exact center of the southwest corner cell is called the viewpoint; a person viewing the artwork is supposed to stand there. Each other cell contains a cylindrical pillar. All pillars have two circular bases of radius $\mathbf{R}$: one resting on the floor, in the center of its corresponding cell, and the other touching the gallery's ceiling. The observer will stand in the viewpoint, observe the $\mathbf{N}^{2} - 1$ pillars, and marvel.

Cody-Jamal is currently scouting venues trying to see how large he can make the value of $\mathbf{N}$. Also, he has not decided which material the pillars will be made of; it could be concrete, or carbon nanotubes, so the radius $\mathbf{R}$ of the base of each pillar could vary from 1 micrometer to almost half a meter. Notice that a radius of half a meter would make neighboring pillars touch.

You, as a trained mathematician, quickly observe that there could be pillars impossible to see from the viewpoint. Cody-Jamal asks your help in determining, for different combinations of $\mathbf{N}$ and $\mathbf{R}$, the number of visible pillars. Formally, a pillar is visible if and only if there is a straight line segment that runs from the center of the southwest corner cell (the viewpoint) to any point on the pillar's boundary, and does not touch or intersect any other pillar.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ lines follow. Each line describes a different test case with two integers $\mathbf{N}$ and $\mathbf{R}$. $\mathbf{N}$ is the number of 1 meter square cells along either dimension of the gallery, and $\mathbf{R}$ is the radius of each pillar, in micrometers. Thus, $\mathbf{R} / 10^{6}$ is the radius of each pillar in meters.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the number of pillars in the installment that are visible from the viewpoint.
## 样例

### 样例输入 #1
```
4
4 100000
4 300000
3 300000
100 499999
```
### 样例输出 #1
```
Case #1: 9
Case #2: 7
Case #3: 5
Case #4: 3
```
## 提示

**Sample Explanation**

The pictures below illustrate the first two samples (not to scale). In the center of the black circle is the observer. The other circles are pillars, with the visible ones in gray and the not visible ones in red. The blue dotted lines represent some of the unblocked lines of sight; the red dotted lines represent blocked lines of sight (that turn gray at the point at which they are first blocked).

![](https://cdn.luogu.com.cn/upload/image_hosting/kz9mmqav.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/zbn7wv7d.png)

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $1 \leqslant \mathbf{R} < 10^{6} / 2$.

**Small dataset (10 Pts, Test Set 1 - Visible)**

- $2 \leqslant \mathbf{N} \leqslant 300$.

**Large dataset (30 Pts, Test Set 2 - Hidden)**

- $2 \leqslant \mathbf{N} \leqslant 10^{9}$.


---

---
title: "[GDCPC 2024] 腊肠披萨"
layout: "post"
diff: 省选/NOI-
pid: P13352
tag: ['2024', '广东', '容斥原理', 'AC 自动机', 'KMP 算法', 'XCPC']
---
# [GDCPC 2024] 腊肠披萨
## 题目背景

数据、标程、题解等资源的获取：<https://gitlink.org.cn/thusaa/gdcpc2024>
## 题目描述

宇宙北大街上新开了一家披萨店。这家披萨店主打使用腊肠的披萨，被顾客亲切地称为“腊肠披萨店”。这种中西合璧的做法听上去很离经叛道，但是品尝过腊肠披萨的顾客都对其称赞有加，吸引了众多食客蜂拥而至。

除了配料极具特色，腊肠披萨店的 Wi-Fi 密码也是它的流量密码。菜单上写着：“本店的 Wi-Fi 密码是

$$
\sum_{i=1}^L \sum_{j=1}^L C^{\left|LCPS\left(s_i, s_j\right)\right|} \bmod{P},
$$

其中 $LCPS\left(s_i, s_j\right)$ 表示 $s_i$ 和 $s_j$ 的最长公共前后缀，即最长的同时是 $s_i$ 前缀和 $s_j$ 后缀的字符串（可能为空，也可能为整个串）；每天的 $s_1,\cdots,s_L$ 都不一样，服务员会在点餐后提供用于当天的 Wi-Fi 密码的字符串。每天将会从前 100 名连上 Wi-Fi 的顾客中随机抽取一位免单。”

你计划下周和朋友一起来这家店聚餐，因此你想设计一个算法，快速求出这家店的 Wi-Fi 密码。
## 输入格式

输入的第一行包含三个正整数 $L, C, P$，表示字符串的数量、底数及模数。保证 $1\le L\le 3\times 10^6$，$2\le C<P<2^{30}$。

接下来 $L$ 行，每行输入一个仅由小写字符构成的字符串 $s_i$。保证 $1\le \left|s_i\right| \le 3\times 10^6$，$\sum_{i=1}^L \left|s_i\right| \le 3\times 10^6$。

## 输出格式

输出一个非负整数，表示腊肠披萨店的 Wi-Fi 密码。
## 样例

### 样例输入 #1
```
4 2 378323747
shop
pizza
piazza
pizzala
```
### 样例输出 #1
```
286
```
### 样例输入 #2
```
9 99 998244353
asap
peace
piece
pizza
sapiens
dazzling
andromeda
sakurasaku
kokorosaku
```
### 样例输出 #2
```
161369438
```
## 提示

### 样例 1 解释

对于 $1\le i,j\le 4, i\ne j$，

- $LCPS($ `pizza` $,$ `shop` $ )=LCPS($ `piazza` $,$ `shop` $)=LCPS($ `pizzala` $,$ `shop` $)=$ `p`；
- $LCPS($ `pizzala` $,$ `pizza` $)=$ `pizza`；
- 其余的 $LCPS\left(s_i, s_j\right)=\varepsilon$。

因此对应的 Wi-Fi 密码为

$$
2^4 + 2^0 + 2^0 + 2^0 + 2^1 + 2^5 + 2^0 + 2^0 + 2^1 + 2^0 + 2^6 + 2^0 + 2^1 + 2^5 + 2^0 + 2^7 = 286.
$$

腊肠披萨店在制作披萨时使用了绝密配方。在没有专业人士指导的情况下，请不要轻易模仿。


---

---
title: "[GCJ 2009 Finals] Doubly-sorted Grid"
layout: "post"
diff: 省选/NOI-
pid: P13450
tag: ['动态规划 DP', '2009', '容斥原理', '状压 DP', 'Google Code Jam']
---
# [GCJ 2009 Finals] Doubly-sorted Grid
## 题目描述

A rectangular grid with lower case English letters in each cell is called doubly sorted if in each row the letters are non-decreasing from the left to the right, and in each column the letters are non-decreasing from the top to the bottom. In the following examples, the first two grids are doubly sorted, while the other two are not:

```
abc    ace    aceg    base
def    ade    cdef    base
ghi    bdg    xxyy    base
```

You are given a partially-filled grid, where some of the cells are filled with letters. Your task is to compute the number of ways you can fill the rest of the cells so that the resulting grid is doubly sorted. The answer might be a big number; you need to output the number of ways modulo $10007$.
## 输入格式

The first line of input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing two integers $R$ and $C$, the number of rows and the number of columns respectively. This is followed by $R$ lines, each containing a string of length $C$, giving the partially-filled grid. Each character in the grid is either a lower-case English letter, or '.', indicating that the cell is not filled yet.

## 输出格式

For each test case, output one line. That line should contain "Case #$X$: $y$", where $X$ is the case number starting with 1, and $y$ is the number of possible doubly-sorted grids, modulo $10007$.
## 样例

### 样例输入 #1
```
3
2 2
ad
c.
3 3
.a.
a.z
.z.
4 4
....
.g..
.cj.
....
```
### 样例输出 #1
```
Case #1: 23
Case #2: 7569
Case #3: 0
```
## 提示

**Limits**

- $1 \leq T \leq 40$
- Each character in the partially-filled grid is either '.' or a lower-case English letter.

**Small dataset(10 Pts)**

- Time limit: ~~60~~ 5 seconds.
- $1 \leq R, C \leq 4$

**Large dataset(20 Pts)**

- Time limit: ~~120~~ 10 seconds.
- $1 \leq R, C \leq 10$


---

---
title: "[CCPC 2024 重庆站] 乘积，欧拉函数，求和"
layout: "post"
diff: 省选/NOI-
pid: P13568
tag: ['重庆', '2024', '数论', '容斥原理', 'XCPC', '欧拉函数']
---
# [CCPC 2024 重庆站] 乘积，欧拉函数，求和
## 题目背景

本题目来自仓库 https://github.com/Disposrestfully/CCPC-CQ-2024/tree/main
## 题目描述

给定 $n$ 个数 $a_1,a_2,\cdots,a_n$，你需要求以下式子的值：

$$\sum_{S \subseteq \{1,2,\cdots,n\}} \varphi \left(\prod_{i \in S} a_i\right).$$

其中 $\varphi$ 为欧拉函数，$\varphi(x)$ 表示在 $[1,x]$ 内与 $x$ 互质的整数数量，例如

- $\varphi(6) = 2$，因为在 $[1,6]$ 内有 $1$ 和 $5$ 与 $6$ 互质。
- $\varphi(1) = 1$，因为在 $[1,1]$ 内有 $1$ 与 $1$ 互质。

另外，我们定义 $\prod_{i \in \varnothing} a_i = 1$。

答案可能很大，你需要求出其对质数 $998244353$ 取模的结果。

## 输入格式

输入的第一行为一个整数 $n \ (1 \le n \le 2000)$ 表示数的数量，接下来一行 $n$ 个整数 $a_1,a_2,\cdots, a_n \ (1 \le a_i \le 3000)$。
## 输出格式

输出一行一个整数表示答案，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
12
```
## 提示

共有八种 $S$ 的选择，所有选择得到的 $\prod_{i \in S} a_i$ 分别为 $1,1,2,2,3,3,6,6$。可以计算得到 $\varphi(1) = \varphi(2) = 1, \varphi(3) = \varphi(6) = 2$，因此答案为 $1 \times 4 + 2 \times 4 = 12$。


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
title: "四元组统计"
layout: "post"
diff: 省选/NOI-
pid: P2714
tag: ['数学', '容斥原理']
---
# 四元组统计
## 题目描述

有 $n$ 个正整数 $a _ i$，你要统计有多少个四元组满足 $\gcd(a _ i, a _ j, a _ k, a _ l) = 1$。

## 输入格式

输入包含多组数据。  
对于每组数据：第一行一个正整数 $n$，接下来一行 $n$ 个正整数 $a _ i$。

## 输出格式

若干行，每行对应一个输入数据，表示满足要求的四元组的个数。

## 样例

### 样例输入 #1
```
4
2 3 4 5
4
2 4 6 8
7
2 3 4 5 7 6 8  
```
### 样例输出 #1
```
1
0
34

```
## 提示

对于 $30\%$ 的数据，$4 ≤ n ≤ 10$，且数据组数不超过 $10$；

对于 $100\%$ 的数据，$4 ≤ n ≤ 10000$，$1 ≤ a _ i≤ 10000$，且数据组数不超过 $100$。



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
title: "[CQOI2011] 放棋子"
layout: "post"
diff: 省选/NOI-
pid: P3158
tag: ['动态规划 DP', '2011', '重庆', '各省省选', '容斥原理', '构造']
---
# [CQOI2011] 放棋子
## 题目描述

在一个 $m$ 行 $n$ 列的棋盘里放一些彩色的棋子，使得每个格子最多放一个棋子，且不同颜色的棋子不能在同一行或者同一列，有多少种方法？

例如，$n=m=3$，有两个白棋子和一个灰棋子，下面左边两种方法都是合法的，但右边两种都是非法的。

![](https://cdn.luogu.com.cn/upload/pic/28150.png)
## 输入格式

输入第一行为两个整数 $n,m,c$，即行数、列数和棋子的颜色数。

第二行包含 $c$ 个正整数，即每个颜色的棋子数。
## 输出格式

输出仅一行，即方案总数除以 $10^9+9$ 的余数。
## 样例

### 样例输入 #1
```
4 2 2
3 1
```
### 样例输出 #1
```
8
```
## 提示

$1\le n,m\le 30$，$1\le c\le 10$，总棋子数 $\le \max (250,n\times m)$。


---

---
title: "[CQOI2012] 局部极小值"
layout: "post"
diff: 省选/NOI-
pid: P3160
tag: ['2012', '重庆', '各省省选', '容斥原理', '状压 DP']
---
# [CQOI2012] 局部极小值
## 题目描述

有一个 $n$ 行 $m$ 列的整数矩阵，其中 $1$ 到 $n\times m$ 之间的每个整数恰好出现一次。

如果一个格子比所有相邻格子（相邻是指有公共边或公共顶点）都小，我们说这个格子是局部极小值。给出所有局部极小值的位置，你的任务是判断有多少个可能的矩阵。

答案对 $12{,}345{,}678$ 取模。
## 输入格式

输入第一行包含两个整数 $n$ 和 $m$，即行数和列数。

以下 $n$ 行每行 $m$ 个字符，第 $(i + 1)$ 行的第 $j$ 个字符代表第 $i$ 列的第 $j$ 个格子是否是局部极小值，该字符只可能是 `X` 或 `.`，其中 `X` 表示局部极小值，`.` 表示非局部极小值。
## 输出格式

输出仅一行，为可能的矩阵总数除以 $12345678$ 的余数。
## 样例

### 样例输入 #1
```
3 2
X.
..
.X
```
### 样例输出 #1
```
60
```
## 提示

#### 数据规模与约定

- 对于 $100\%$ 的数据，保证 $1\le n\le4$，$1\le m\le7$。


---

---
title: "[HAOI2015] 按位或"
layout: "post"
diff: 省选/NOI-
pid: P3175
tag: ['2015', '河南', 'Special Judge', '容斥原理', '快速沃尔什变换 FWT']
---
# [HAOI2015] 按位或
## 题目描述

刚开始你有一个数字 $0$，每一秒钟你会随机选择一个 $[0,2^n-1]$ 的数字，与你手上的数字进行或（C++,C 的 `|`，pascal 的 `or`）操作。选择数字 $i$ 的概率是 $p_i$。保证 $0\leq p_i \leq 1$，$\sum p_i=1$ 。问期望多少秒后，你手上的数字变成 $2^n-1$。

## 输入格式

第一行输入 $n$ 表示 $n$ 个元素，第二行输入 $2^n$ 个数，第 $i$ 个数表示选到 $i-1$ 的概率。

## 输出格式

仅输出一个数表示答案，绝对误差或相对误差不超过 $10^{-6}$ 即可算通过。如果无解则要输出 `INF`。
## 样例

### 样例输入 #1
```
2
0.25 0.25 0.25 0.25
```
### 样例输出 #1
```
2.6666666667
```
## 提示

对于 $100\%$ 的数据，$n\leq 20$。

以下为 spj 源代码。

```cpp
//liuchenrui 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#define AC {fclose(fstd),fclose(fuser);return 0;}
#define WA {fclose(fstd),fclose(fuser);return 1;}
#define PE {fclose(fstd),fclose(fuser);return 5;}
#define eps 1e-6
int main(int const argc, char*const argv[]){
    FILE *fstd,*fuser;
    fstd=fopen(argv[2],"r");
    fuser=fopen(argv[3],"r");
    //fstd=fopen("x1.in","r");
    //fuser=fopen("x2.in","r");
    char s[30],t[30];
    if(fscanf(fuser,"%s",s+1)==-1)WA;
    fscanf(fstd,"%s",t+1);
    if(s[1]=='I' && t[1]=='I')AC;
    if(s[1]=='I' || t[1]=='I')WA;
    double p,q;
    sscanf(s+1,"%lf",&p);
    sscanf(t+1,"%lf",&q);
    if(fabs(p-q)<eps)AC
    else{
        if(fabs(p-q)/q<eps)AC;
        if(fabs(q-p)/q<eps)AC;
        if(fabs(p-q)/p<eps)AC;
        if(fabs(q-p)/p<eps)AC;
    }
    WA;
}

```


---

---
title: "[JLOI2016] 成绩比较"
layout: "post"
diff: 省选/NOI-
pid: P3270
tag: ['递推', '2016', '各省省选', '吉林', '容斥原理']
---
# [JLOI2016] 成绩比较
## 题目描述

G 系共有 $N$ 位同学，$M$ 门必修课。这 $N$ 位同学的编号为 $0$ 到 $N-1$ 的整数，其中 B 神的编号为 $0$ 号。这 $M$ 门必修课编号为 $0$ 到 $M-1$ 的整数。一位同学在必修课上可以获得的分数是 $1$ 到 $U_i$ 中的一个整数。

如果在每门课上 A 获得的成绩均小于等于 B 获得的成绩，则称 A 被 B 碾压。在 B 神的说法中，G 系共有 $K$ 位同学被他碾压（不包括他自己），而其他 $N-K-1$ 位同学则没有被他碾压。D 神查到了 B 神每门必修课的排名。

这里的排名是指：如果 B 神某门课的排名为 $R$，则表示有且仅有 $R-1$ 位同学这门课的分数大于 B 神的分数，有且仅有 $N-R$ 位同学这门课的分数小于等于 B 神（不包括他自己）。

我们需要求出全系所有同学每门必修课得分的情况数，使其既能满足 B 神的说法，也能符合 D 神查到的排名。这里两种情况不同当且仅当有任意一位同学在任意一门课上获得的分数不同。

你不需要像 D 神那么厉害，你只需要计算出情况数模 $10^9+7$ 的余数就可以了。
## 输入格式

第一行包含三个正整数 $N,M,K$，分别表示 G 系的同学数量（包括 B 神），必修课的数量和被 B 神碾压的同学数量。

第二行包含 $M$ 个正整数，依次表示每门课的最高分 $U_i$。

第三行包含 $M$ 个正整数，依次表示 B 神在每门课上的排名 $R_i$。

数据保证至少有 $1$ 种情况使得 B 神说的话成立。
## 输出格式

仅一行一个正整数，表示满足条件的情况数模 $10^9+7$ 的余数。
## 样例

### 样例输入 #1
```
3 2 1
2 2
1 2
```
### 样例输出 #1
```
10
```
## 提示

$1\leq N\leq 100$，$1\leq M\leq 100$，$1\leq U_i\leq 10^9$，$1\leq R_i\leq N$。


---

---
title: "[JLOI2016] 方"
layout: "post"
diff: 省选/NOI-
pid: P3271
tag: ['2016', '吉林', '枚举', '容斥原理']
---
# [JLOI2016] 方
## 题目描述

上帝说，不要圆，要方，于是便有了这道题。

由于我们应该方，而且最好能够尽量方，所以上帝派我们来找正方形上帝把我们派到了一个有 $N$ 行 $M$ 列的方格图上，图上一共有 $(N+1)\times(M+1)$ 个格点，我们需要做的就是找出这些格点形成了多少个正方形（换句话说，正方形的四个顶点都是格点）。

但是这个问题对于我们来说太难了，因为点数太多了，所以上帝删掉了这 $(N+1)\times(M+1)$ 中的 $K$ 个点。既然点变少了，问题也就变简单了，那么这个时候这些格点组成了多少个正方形呢？

## 输入格式

第一行三个整数 $N, M, K$，代表棋盘的行数、 列数和不能选取的顶点个数。保证 $N, M \ge 1$， $K \le (N + 1) \times(M + 1)$。

约定每行的格点从上到下依次用整数 $0$ 到 $N$ 编号，每列的格点依次用 $0$ 到 $M$ 编号。

接下来 $K$ 行，每行两个整数 $x,y$ 代表第 $x$ 行第 $y$ 列的格点被删掉了。

保证 $0 \le x \le N \le 10^6$，$0 \le y \le M \le 10^6$，$K \le 2000$ 且不会出现重复的格点。
## 输出格式

仅一行一个正整数，代表正方形个数对 $100000007 ( 10^8 + 7)$ 取模之后的值。
## 样例

### 样例输入 #1
```
2 2 4
1 0
1 2
0 1
2 1
```
### 样例输出 #1
```
1
```


---

---
title: "[SCOI2013] 火柴棍数字"
layout: "post"
diff: 省选/NOI-
pid: P3283
tag: ['2013', '四川', '深度优先搜索 DFS', '容斥原理']
---
# [SCOI2013] 火柴棍数字
## 题目描述

Fish是一条生活在海里的鱼，有一天他很无聊，于是他去捡了人类扔进海里的垃圾，打算用这些来玩些什么。

他从捡回来的垃圾堆里找到了不少火柴棍，便把这些火柴棍拼成了一个长度为n 的十进制数，每个数字的拼法如下图所示

注意：每个数字占据的宽度和摆放方式是固定的，故以下情况均不合法。 ![](https://cdn.luogu.com.cn/upload/pic/4633.png)

 ![](https://cdn.luogu.com.cn/upload/pic/4634.png) 

拼完之后他好累，感觉再也不会拼了。他对拼出来的数大小不满意，希望通过移动一些火柴棍的位置来把这个数变得尽量大。

由于太累，他只能最多移动k 根火柴棍。而且由于数字的最低位放在墙边，他不能在该数的低位后面添加数字，但他可以在该数的前面添加数字。

你能帮他算出他移动火柴棍之后的数最大能是多大吗？

注意：火柴棍对于Fish 来说是很贵重的物品，所以不允许折断或丢弃火柴棍。

注意：火柴头的方向不影响数字的辨识，例如下面几种情况都是数字1

![](https://cdn.luogu.com.cn/upload/pic/4635.png)

## 输入格式

输入仅含一行，分别是长度为n 的十进制数x 和最多移动火柴棍的数量k。x 没有前导零。

## 输出格式

输出仅一行，表示移动火柴棍之后的最大数。

## 样例

### 样例输入 #1
```
3 2

```
### 样例输出 #1
```
17
```
### 样例输入 #2
```
3 3
```
### 样例输出 #2
```
71
```
## 提示

对于30% 的数据，1 <= n <= 10，0 <= k <= 10。

对于100% 的数据，1 <= n <= 500，0 <=k <=3500。



---

---
title: "[SDOI2013] 泉"
layout: "post"
diff: 省选/NOI-
pid: P3298
tag: ['2013', '山东', '哈希 hashing', '容斥原理']
---
# [SDOI2013] 泉
## 题目描述

作为光荣的济南泉历史研究小组中的一员，铭铭收集了历史上x个不同年份时不同泉区的水流指数，这个指数是一个小于. 2^30的非负整数。第i个年份时六个泉区的泉水流量指数分别为 A(i,l)，A(i,2)，A(i,3)，A(i,4)， A(i,5)与 A(i,6)。

现在铭铭希望知道有多少对不同的年份：i和j,满足这两年恰好有K个泉区的泉水流S指数对应相同。

## 输入格式

第一行有2个整数，分别是N和K

之后N行，每行有6个整数。第i行的第j个数字A(i，j)表示第i个年份中第j个泉区的泉水流量指数。

## 输出格式

一个整数表示有多少对不同的年份满足恰有K个区的泉水流量指数对应相同。

## 样例

### 样例输入 #1
```
3 3
1 2 3 4 5 6
1 2 3 0 0 0
0 0 0 4 5 6
```
### 样例输出 #1
```
2
```
## 提示

对于 100%的数据, 0<=K <=6, 且所有数据中K是等概率出现的, 即对于任意的 0<=x都有大约 1/7 的数据中 K=x.
N<=100000


---

---
title: "[SDOI2013] 方程"
layout: "post"
diff: 省选/NOI-
pid: P3301
tag: ['2013', '山东', '中国剩余定理 CRT', '组合数学', '容斥原理']
---
# [SDOI2013] 方程
## 题目描述

给定方程
$x_1+x_2+\dots +x_{n}=m$。

我们对第 $1 \sim n_1$ 个变量进行一些限制： $x_{1} \le a_{1},x_{2} \le a_{2},\dots, x_{n_1} \le a_{n_1}$。

我们对第 $n_1+1\sim n_1+n_2$ 个变量进行一些限制： $x_{n_1+1} \ge a_{n_1+1},x_{n_1+2} \ge a_{n_1+2},\dots,x_{n1+n2} \ge a_{n_1+n_2}$。

求：在满足这些限制的前提下，该方程正整数解的个数。答案可能很大，请输出对 $p$ 取模后的答案。
## 输入格式

输入含有多组数据。 

第一行两个正整数 $T,p$。$T$  表示这个测试点内的数据组数，$p$ 的含义见题目描述。

对于每组数据，第一行四个非负整数 $n,n_1,n_2,m$。 

第二行 $n_1+n_2$ 个正整数，表示 $a_{1},a_2,\dots, a_{n_1+n_2}$。请注意，如果 $n_1+n_2$ 等于 $0$，那么这一行会成为一个空行。
## 输出格式

共 $T$ 行，每行一个正整数表示取模后的答案。
## 样例

### 样例输入 #1
```
3 10007
3 1 1 6
3 3
3 0 0 5

3 1 1 3
3 3

```
### 样例输出 #1
```
3
6
0

```
## 提示

**【样例解释】**

对于第一组数据，三组解为 $(1,3,2)，(1,4,1),(2,3,1) $。  
对于第二组数据，六组解为 $(1,1,3),(1,2,2),(1,3,1),(2,1,2),(2,2,1),(3,1,1)$。

![](https://cdn.luogu.com.cn/upload/pic/17621.png)

对于 $100\%$ 的数据，$1\le T \le 5$，$1\le m, n \le 10^9$，$1 \le a_i \le m$，$0 \le n_1,n_2 \le \min(8, m)$ 且 $n_1 + n_2 \le n$，$1\le p \le 437367875$。


---

---
title: "[ZJOI2016] 小星星"
layout: "post"
diff: 省选/NOI-
pid: P3349
tag: ['动态规划 DP', '2016', '浙江', '枚举', '容斥原理']
---
# [ZJOI2016] 小星星
## 题目描述

小 Y 是一个心灵手巧的女孩子，她喜欢手工制作一些小饰品。她有 $n$ 颗小星星，用 $m$ 条彩色的细线串了起来，每条细线连着两颗小星星。

有一天她发现，她的饰品被破坏了，很多细线都被拆掉了。这个饰品只剩下了 $n-1$ 条细线，但通过这些细线，这颗小星星还是被串在一起，也就是这些小星星通过这些细线形成了树。小 Y 找到了这个饰品的设计图纸，她想知道现在饰品中的小星星对应着原来图纸上的哪些小星星。如果现在饰品中两颗小星星有细线相连，那么要求对应的小星星原来的图纸上也有细线相连。小 Y 想知道有多少种可能的对应方式。

只有你告诉了她正确的答案，她才会把小饰品做为礼物送给你呢。

## 输入格式

第一行包含 $2$ 个正整数 $n,m$，表示原来的饰品中小星星的个数和细线的条数。

接下来 $m$ 行，每行包含 $2$ 个正整数 $u,v$，表示原来的饰品中小星星 $u$ 和 $v$ 通过细线连了起来。这里的小星星从 $1$ 开始标号。保证 $u\neq v$，且每对小星星之间最多只有一条细线相连。

接下来 $n-1$ 行，每行包含 $2$ 个正整数 $u,v$，表示现在的饰品中小星星 $u$ 和 $v$ 通过细线连了起来。保证这些小星星通过细线可以串在一起。
## 输出格式

输出共 $1$ 行，包含一个整数表示可能的对应方式的数量。

如果不存在可行的对应方式则输出 `0`。
## 样例

### 样例输入 #1
```
4 3
1 2
1 3
1 4
4 1
4 2
4 3
```
### 样例输出 #1
```
6
```
## 提示

对于 $100\%$ 的数据，$n\leq 17$，$m\leq \frac 12n(n-1)$。


---

---
title: "[FJOI2017] 矩阵填数"
layout: "post"
diff: 省选/NOI-
pid: P3813
tag: ['2017', '各省省选', '离散化', '福建', '枚举', '容斥原理']
---
# [FJOI2017] 矩阵填数
## 题目描述

给定一个 $h \times w$ 的矩阵，矩阵的行编号从上到下依次为 $1 \sim h$，列编号从左到右依次 $1 \sim w$。

在这个矩阵中你需要在每个格子中填入 $1 \sim m$ 中的某个数。

给这个矩阵填数的时候有一些限制，给定 $n$ 个该矩阵的子矩阵，以及该子矩阵的最大值 $v$，要求你所填的方案满足该子矩阵的最大值为 $v$。

现在，你的任务是求出有多少种填数的方案满足 $n$ 个限制。

两种方案是不一样的当且仅当两个方案至少存在一个格子上有不同的数。由于答案可能很大，你只需要输出答案对 $10 ^ 9 + 7$ 取模后的结果。
## 输入格式

输入数据的第一行为一个数 $T$，表示数据组数。

对于每组数据，第一行为四个数 $h,w,m,n$。

接下来 $n$ 行，每一行描述一个子矩阵的最大值 v。每行为五个整数 $x1,y1,x2,y2,v$，表示一个左上角为$(x1,y1)$,右下角为$(x2,y2)$的子矩阵的最大值为 $v$。 $1 \le x1 \le x2 \le h$, $1 \le y1 \le y2 \le w$

## 输出格式

对于每组数据输出一行，表示填数方案 mod $1,000,000,007$ 后的值。

## 样例

### 样例输入 #1
```
2
3 3 2 2
1 1 2 2 2
2 2 3 3 1
4 4 4 4
1 1 2 3 3
2 3 4 4 2
2 1 4 3 2
1 2 3 4 4
```
### 样例输出 #1
```
28
76475
```
## 提示

对于 $20\%$ 的数据，$n \le 2$。

另有 $20\%$ 的数据，$1 \le h, w \le 50$。

对于 $100\%$ 的数据，$T \le 5$，$1 \le h, w, m \le 10 ^ 4$，$1 \le n \le 10$，$1 \le v \le m$。


---

---
title: "完全平方数"
layout: "post"
diff: 省选/NOI-
pid: P4318
tag: ['素数判断,质数,筛法', '容斥原理', '分块']
---
# 完全平方数
## 题目描述

小 X 自幼就很喜欢数。但奇怪的是，他十分讨厌完全平方数。他觉得这些数看起来很令人难受。由此，他也讨厌所有是完全平方数的正整数倍的数。然而这丝毫不影响他对其他数的热爱。

这天是小X的生日，小 W 想送一个数给他作为生日礼物。当然他不能送一个小X讨厌的数。他列出了所有小X不讨厌的数，然后选取了第 K个数送给了小X。小X很开心地收下了。

然而现在小 W 却记不起送给小X的是哪个数了。你能帮他一下吗？
## 输入格式

包含多组测试数据。文件第一行有一个整数 $T$，表示测试数据的组数。
第$2$ 至第$T+1$ 行每行有一个整数$K_i$，描述一组数据，含义如题目中所描述。
## 输出格式

含T 行，分别对每组数据作出回答。第 $i$ 行输出相应的第$K_i$ 个不是完全平方数的正整数倍的数。
## 样例

### 样例输入 #1
```
4 
1 
13 
100 
1234567
```
### 样例输出 #1
```
1 
19 
163 
2030745
```
## 提示

对于 50%的数据有 $1 ≤ K_i ≤ 10^5$,
对于 100%的数据有 $1 ≤ K_i ≤ 10^9, T ≤ 50$


---

---
title: "[SHOI2016] 黑暗前的幻想乡"
layout: "post"
diff: 省选/NOI-
pid: P4336
tag: ['2016', '各省省选', '矩阵树定理', '上海', '生成树', '容斥原理']
---
# [SHOI2016] 黑暗前的幻想乡
## 题目背景

四年一度的幻想乡大选开始了，最近幻想乡最大的问题是很多来历不明的妖怪涌入了幻想乡，扰乱了幻想乡昔日的秩序。但是幻想乡的建制派妖怪（人类）博丽灵梦和八云紫等人整日高谈所有妖怪平等，幻想乡多元化等等，对于幻想乡目前面临的种种大问题却给不出合理的解决方案。

风见幽香是幻想乡里少有的意识到了问题严重性的大妖怪。她这次勇敢地站了出来参加幻想乡大选，提出包括在幻想乡边境建墙（并让人类出钱），大力开展基础设施建设挽回失业率等一系列方案，成为了大选年出人意料的黑马并顺利地当上了幻想乡的大统领。
## 题目描述

幽香上台以后，第一项措施就是要修建幻想乡的公路。幻想乡一共有 $n$ 个城市，之前原来没有任何路。幽香向选民承诺要减税，所以她打算只修 $n-1$ 条公路将这些城市连接起来。但是幻想乡有正好 $n-1$ 个建筑公司，每个建筑公司都想在修路的过程中获得一些好处。虽然这些建筑公司在选举前没有给幽香钱，幽香还是打算和他们搞好关系，因为她还指望他们帮她建墙。所以她打算让每个建筑公司都负责一条路来修。

每个建筑公司都告诉了幽香自己有能力负责修建的路是哪些城市之间的。所以幽香打算 $n - 1$ 条能够连接幻想乡所有城市的边，然后每条边都交给一个能够负责该边的建筑公司修建，并且每个建筑公司都恰好修建一条边。

幽香现在想要知道一共有多少种可能的方案呢？两个方案不同当且仅当它们要么修的边的集合不同，要么边的分配方式不同。
## 输入格式

第一行包含一个整数 $n$，表示城市个数。

第 $2$ 到第 $n$ 行，第 $(i + 1)$ 行表示 第 $i$ 个建筑公司可以修建的路的列表：以一个非负整数 $m_i$ 开头，表示其可以修建条路的条数；接下来有 $m_i$ 对整数 $u, v$，每对数表示一条边的两个端点。其中不会出现重复的边，也不会出现自环。
## 输出格式

输出一行一个整数，表示所有可能的方案数对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
4
2 3 2 4 2
5 2 1 3 1 3 2 4 1 4 3
4 2 1 3 2 4 1 4 2
```
### 样例输出 #1
```
17
```
## 提示

#### 数据规模与约定

+ 对于 $20\%$ 的测试点，$n \le 5$。
+ 对于 $50\%$ 的测试点，$n \le 8$。
+ 对于 $60\%$ 的测试点，$n \le 10$。
+ 对于 $100\%$ 的测试点，$2 \leq n \le 17$，$0 \leq m_i \leq \frac{n(n - 1)}{2}$，$1 \leq u, v \leq n$。


---

---
title: "[AHOI2018初中组] 球球的排列"
layout: "post"
diff: 省选/NOI-
pid: P4448
tag: ['动态规划 DP', '2018', '安徽', '容斥原理']
---
# [AHOI2018初中组] 球球的排列
## 题目描述

小可可是一个有着特殊爱好的人。他特别喜欢收集各种各样的球球，至今已经收集了$n$ 个球球。

小可可又是一个有着特殊想法的人。他将他的所有球球从 1 到$n$ 编号，并每天都把球球排成一个全新的排列。

小可可又是一个有着特殊情怀的人。他将每个球球的特点用$a[i]$来表示（注意这里不同的球$a[i]$可能相同）。

小可可又是一个爱恨分明的人。他十分讨厌平方数，所以他规定：一个排列$p$，对于所有的$1 ≤ i < n$，$a[p_i]\times a[p_{i+1}]$ 不是一个平方数，这样的排列$p$ 才是合法的。

小可可一直坚持每天排一个全新的合法的排列。有一天，他心血来潮，想知道所有合法排列的个数。小可可十分强，他当然知道怎么算。不过，他想用这个题来考考身在考场的你。这个数可能太大了，所以你只需要告诉小可可合法排列个数对$10^9+7$ 取模的结果就可以了。

你能正确回答小可可的问题吗？如果能的话，他说不定会送个球球给你呢……
## 输入格式

输入有两行：

第一行一个正整数$n$，表示小可可拥有的球球个数。  
第二行有$n$ 个整数，第$i$ 个整数$a[i]$表示编号为$i$ 的球球的特点。
## 输出格式

输出一行，包括一个正整数，表示合法排列个数对$10^9+7$（即1000000007）取模的结果。
## 样例

### 样例输入 #1
```
4
2 2 3 4
```
### 样例输出 #1
```
12

```
### 样例输入 #2
```
9
2 4 8 9 12 4 3 6 11
```
### 样例输出 #2
```
99360
```
## 提示

【样例1 解释】
12 种合法的排列分别为：
```
1,3,2,4
2,3,1,4
3,1,4,2
3,2,4,1
1,3,4,2
2,3,4,1
1,4,2,3
2,4,1,3
4,1,3,2
4,2,3,1
1,4,3,2
2,4,3,1
```

【数据范围】

对于100%的数据满足：$1≤n≤300$，$1≤a[i]≤10^9$。

本题共10 个测试点，编号为1~10，每个测试点额外保证如下：

测试点编号| n的范围|a[i]的范围
-|-|-
1~2|$n≤10$|$a[i]≤10^9$
3~5|$n≤300$|$1≤a[i]≤2$
6~8|-|$a[i]≤10^9$且都是质数
9~10|-|$a[i]≤10^9$


---

---
title: "[HAOI2018] 染色"
layout: "post"
diff: 省选/NOI-
pid: P4491
tag: ['2018', '河南', '各省省选', 'O2优化', '容斥原理', '生成函数', '快速数论变换 NTT']
---
# [HAOI2018] 染色
## 题目背景

HAOI2018 Round2 第二题
## 题目描述

为了报答小 C 的苹果，小 G 打算送给热爱美术的小 C 一块画布，这块画布可以抽象为一个长度为 $N$ 的序列，每个位置都可以被染成 $M$ 种颜色中的某一种。

然而小 C 只关心序列的 $N$ 个位置中出现次数恰好为 $S$ 的颜色种数，如果恰好出现了 $S$ 次的颜色有 $K$ 种，则小 C 会产生 $W_k$ 的愉悦度。

小 C 希望知道对于所有可能的染色方案，他能获得的愉悦度的和对 $1004535809$
取模的结果是多少。
## 输入格式

从标准输入读入数据。第一行三个整数 $N, M, S$。

接下来一行 $M + 1$ 个整数，第 $i$ 个数表示 $W_{i-1}$。
## 输出格式

输出到标准输出中。输出一个整数表示答案。
## 样例

### 样例输入 #1
```
8 8 3
3999 8477 9694 8454 3308 8961 3018 2255 4910
```
### 样例输出 #1
```
524070430
```
### 样例输入 #2
```
见 sample.zip/data2.in
```
### 样例输出 #2
```
见 sample.zip/data2.ans
```
## 提示

特殊性质: $\forall 1 \le i \le m, W_i = 0$。

对于 $100\%$ 的数据，满足 $1 \le N \le 10 ^ 7$，$1 \le M \le 10 ^ 5$，$1 \le S \le 150$，$0 \le W_i < 1004535809$。

![Data](https://cdn.luogu.com.cn/upload/pic/18057.png)



---

---
title: "[COCI 2009/2010 #6] XOR"
layout: "post"
diff: 省选/NOI-
pid: P4515
tag: ['计算几何', '2009', '容斥原理', 'COCI（克罗地亚）']
---
# [COCI 2009/2010 #6] XOR
## 题目描述

坐标系下有若干个等腰直角三角形，且每个等腰直角三角形的直角顶点都在左下方，两腰与坐标轴平行。被奇数个三角形覆盖的面积部分为灰色，被偶数个三角形覆盖的面积部分为白色，如下图所示。
![](https://cdn.luogu.com.cn/upload/pic/18669.png)
已知 $N$个等腰直角三角形的顶点坐标及腰长，求灰色部分面积。

Mirko and Slavko have built their own LED display. The display is initially
white. During each of the $N$ parts of the testing phase, Mirko attached three
electrodes to the display in such way that they formed a right isosceles
triangle. He noticed that, after attaching the electrodes, all pixels in the
enclosing triangle are inverted (white pixels become black, and black pixels
become white).

Watching Mirko play with the electrodes, Slavko observed interesting shapes
emerging on the screen. Mathematically inclined as he is, first thing that
crossed his mind was how to calculate total area covered by black pixels. Help
him by writing a program to do just that!
## 输入格式

输入第一行包含一个整数 $N$，表示等腰直角三角形数量。

接下来 $N$行，每行三个整数 $X, Y, R$，分别表示等腰直角三角形的顶点坐标 $(X, Y)$与腰长 $R$。

First line of input contains an integer $N(1 \leq N \leq 10)$, number of triangles
formed by Mirko's fiddling with electrodes. Each of the following $N$ lines
contains three integers $X, Y$ and $R (1 \leq X, Y, R \leq 10^6
)$, describing a triangle. $(X, Y)$ are the coordinates of the lower left corner of the triangle, while $R$ represents the length of the two sides of the triangle.
## 输出格式

输出包含一个实数，表示灰色部分面积。保留1位小数。

The first and only line of output should contain the area covered by black
pixels, rounded to one decimal place.
## 样例

### 样例输入 #1
```
3
1 1 2
7 1 6
5 3 4
```
### 样例输出 #1
```
24.0
```
### 样例输入 #2
```
5
5 5 99
5 5 99
5 5 99
5 5 99
5 5 99
```
### 样例输出 #2
```
4900.5
```
### 样例输入 #3
```
4
5 5 99
5 5 99
5 5 99
5 5 99
```
### 样例输出 #3
```
0.0
```
## 提示

$1 \leq N \leq 10, 1 \leq X, Y, R \leq 10^6$


---

---
title: "[Ynoi Easy Round 2016] 谁的梦"
layout: "post"
diff: 省选/NOI-
pid: P4692
tag: ['2016', 'O2优化', '容斥原理', 'Ynoi']
---
# [Ynoi Easy Round 2016] 谁的梦
## 题目背景

6.373 

世界是独立于我的意志的。 

6.374 

就算我们所期望的全部的事情都发生了 

这果然也只能说是命运的恩惠吧。 

要问为什么，那是因为意志和世界之间 

能够保证这件事的逻辑性的关联并不存在 

Ludwig Josef Johann Wittgenstein [逻辑哲学论] 

自从双胞胎的哥哥过世起，已经过了多久了呢… 

从那时起，我一直保存着那个布偶。 

在那以后的我只是个影子…而这个布偶才是我… 

这样也并没有什么不好。 

我觉得只要现在的我消失掉就行了… 

那两个人却救了这样的我。 

一个是由歧姐… 

她又来到了我的身边… 

带着皆守哥…回到了我们的身边… 

水上由岐姐姐…温柔的姐姐 

曾经非常喜欢皆守哥的人……

![](https://cdn.luogu.com.cn/upload/pic/21195.png)

回去的路上…

平时不会经过的坡道…

在登上那个坡道的途中…

我看到了夜晚的太阳。

明明就在附近，却一直不知道的巨大的向日葵。

夜露使它的绒毛泛出了白光。

碧蓝的月光和黄色的向日葵…

就好像太阳和月亮的立场反过来一样…

原本是那么耀眼的的太阳在地上，只能在其背后下发光的月亮在天上…

黄色的向日葵被染成了碧蓝色。

那副样子虽然很美丽…

努力绽放的向日葵，看起来反而是柔弱的存在。

在夜里向天空伸展的向日葵…

我在车内一直追寻着它的身影…

被夜晚的月光映照着的太阳。

被染成碧蓝色的太阳…

它的身影…我一直追寻着……

![](https://cdn.luogu.com.cn/upload/pic/21196.png)

被月光照亮的天台上…

一个人影…

明明只是一个人影…却好像…在和什么东西对峙着一样…

皆守哥…

月下的立像，一个人影。

胸口在风中闪烁。

放在胸前的手里的是…那时的小刀。

和七年前同样的姿势。

唯一不同的是，那里的人影只有一个。

那把小刀，好像是被他自己刺入体内。

![](https://cdn.luogu.com.cn/upload/pic/21197.png)

是诅咒…

这是理所当然的事…

那并不是什么精神病…

那是诅咒…

下在幸存的我们身上的…诅咒…

说不定，不仅仅是卓司哥…连由岐姐也在诅咒我们…

所以变成这种结果…

哥哥刺向了自己的胸口…

破坏了我的半身…

然后…还要把很多人送回到天空…

回归天空的日子。

交还灵魂的日子。

那一天，卓司哥对我做的事情。

杀了由岐姐的…那个行为…

他想要再一次实行…

这次…和很多人一起…

![](https://cdn.luogu.com.cn/upload/pic/21198.png)

不是…

那是…我啊…

是那个…坡道的事情啊…

两个人一起看到向日葵的…那个坡道…

…我说要爬上那个坡道…要去寻找爸爸的灵魂…

我想，如果到了那个坡道的前方，就能取回爸爸的灵魂…爸爸就会复生的…

如果越过向日葵之路…向着向日葵所朝向的天空延伸的…那个大大的坡道的话…
大概，就会有爸爸的灵魂…

爸爸的故乡的…大大的坡道…

![](https://cdn.luogu.com.cn/upload/pic/21199.png)

哥哥的身体浮在空中…

我无言地跳了出去。

啊啊…是这样啊…

由岐姐也是这种心情啊…

并没有什么道理可言…

只是因为喜欢的人向着天空跳下去了…

我想要抓住那个身体…

我——
## 题目描述

您正在打 galgame，突然断电了，于是您跑去物管处问，结果发现是由于一个光头踢了变压器一脚导致的，可能还要修很久，于是您决定想一个之前见过的数据结构题：

定义一个序列的权值为不同数字的个数，例如 $[1,2,3,3]$  权值为 $3$。

现在有 $n$ 个序列，我们在每个序列里面选一个连续非空子串，拼接起来，求所有选法得到的序列的权值之和。

如果一个序列能通过多种方法被选择出来，那么计算多次。

本题带修改操作，格式请参考输入格式。

由于结果可能过大，请输出答案 $\bmod 19260817$ 的结果。
## 输入格式

第一行两个整数 $n,m$，表示有 $n$ 个序列，$m$ 次修改。

第二行 $n$ 个整数，第 $i$ 个数是 $len_i$，表示第 $i$ 个序列的长度。

之后 $n$ 行，每行 $len_i$ 个整数，表示第 $i$ 个序列。

之后 $m$ 行，每行三个整数 $x,y,z$ 表示将第 $x$ 个序列的第 $y$ 个元素改为 $z$。
## 输出格式

输出 $m + 1$ 行，每行一个整数，依次表示初始局面以及每次修改后的答案。
## 样例

### 样例输入 #1
```
2 5
6 6
1 3 1 1 3 2 
2 3 3 2 1 1 
1 1 1
1 1 2
1 1 2
1 1 1
1 1 1
```
### 样例输出 #1
```
1158
1158
1168
1168
1158
1158
```
## 提示

Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477( partially uploaded )

$1 \leq n,m,len_i \leq 10^5$，序列中的元素均为 $32$ 位整型数，$\sum len_i \leq 10^5$。

共 $50$ 组数据。


---

---
title: "[COCI 2009/2010 #4] PALACINKE"
layout: "post"
diff: 省选/NOI-
pid: P5188
tag: ['2009', '矩阵加速', '容斥原理', 'COCI（克罗地亚）']
---
# [COCI 2009/2010 #4] PALACINKE
## 题目描述

 **译自 [COCI 2010.02](http://hsin.hr/coci/archive/2009_2010/) T6「[PALACINKE](http://hsin.hr/coci/archive/2009_2010/contest4_tasks.pdf)」**

安娜有几个同学过来吃可丽饼，然而安娜忘了这事。当安娜发现时，留给她烤可丽饼的时间只剩下 $T$ 分钟了。她马上跑出去采购四样原材料：面粉 `B`，鸡蛋 `J`，牛奶 `M` 和果酱 `P`。

安娜周边有 $N$ 个路口，编号为 $1\ldots N$，还有 $M$ 条单向道路连接它们。已知每条路上的商店会卖哪些材料，保证每条路上的商店至少会卖（上述四种材料中）的一种。


![](https://cdn.luogu.com.cn/upload/image_hosting/dy9d4iw5.png)

安娜穿过一条道路时，如果她进入了这条路上的商店买东西，则她通过这条路耗时  $2$ 分钟，否则耗时  $1$ 分钟。即使她买完了所有原材料仍可以进店买东西。

安娜需要从 $1$ 开始，最终回到 $1$。

安娜需要在 $T$ 分钟内采购到四种原材料。请问她有多少种「采购方式」，答案对 $5557$ 取模。采购方式包含了她经过的结点的次序，以及她在每条路上买不买材料，但不计她在哪个商店买了什么。例如，当 $T=7$ 时，在上图中有 $5$ 种采购方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/ug3bvehg.png)
## 输入格式

第一行：$N,M$。  
接下来 $M$ 行，每行两个整数 $u,v$ 和一个仅可能包含 `BJMP` 四种字符的字符串 $s$，$u,v$ 表示一条单向道路，$s$ 表示这条道路上的商店会卖哪些材料。保证没有两条单向道路相同（但可能有两条连接的结点相同，而方向相反的道路）。  
第 $N+2$ 行：$T$。
## 输出格式

一行，一个答案，表示安娜有多少种采购方式。
## 样例

### 样例输入 #1
```
3 3
1 2 BMJ
2 3 MJP
3 1 JPB
5
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 4
1 2 B
2 1 P
1 3 J
3 1 M
8
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
5 7
1 2 B
2 4 M
1 3 J
3 4 MB
4 1 JP
4 5 J
5 1 P
7
```
### 样例输出 #3
```
5
```
## 提示

$1\le N\le 25,$ $1\le M\le 500,$ $1\le T\le 10^9$.  
保证没有两条单向道路相同（但可能有两条连接的结点相同，而方向相反的道路）。


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
title: "[THUPC 2019] 过河卒二"
layout: "post"
diff: 省选/NOI-
pid: P5376
tag: ['2019', '组合数学', '排列组合', '容斥原理', 'Lucas 定理', 'THUPC']
---
# [THUPC 2019] 过河卒二
## 题目描述

> 首先我们回忆一下经典难题过河卒问题：
>
> 棋盘上 $A$ 点有一个过河卒，需要走到目标 $B$ 点。卒行走的规则：可以向上、或者向右。同时在棋盘上 $C$ 点有一个对方的马，该马所在的点和所有跳跃一步可达的点称为对方马的控制点，因此称之为「马拦过河卒」。
>
> 棋盘用坐标表示，$A$ 点 $(1,1)$ 、$B$ 点 $(N,M)$ ，同样马的位置坐标是需要给出的。
>
> 现在要求你计算出卒从 $A$ 点能够到达 $B$ 点的路径的条数，假设马的位置是固定不动的，并不是卒走一步马走一步。
>
> **请注意，上述背景内容与本题无关！**

Kiana 喜欢玩象棋，尤其是喜欢用象棋玩过河卒的游戏。在传统的过河卒问题中，Kiana 需要控制一个卒从起点走到终点，在路中避开一个对方的马的攻击，然后假装不会算并询问你从起点到终点的路径总数。

在今天的过河卒二游戏中，Kiana 还是控制一个卒在一个 $N\times M$ 的棋盘上移动，初始时卒位于左下方坐标为 $(1,1)$ 位置，但为了增加难度，Kiana 对游戏规则做出了一些修改。传统的过河卒每步只能向上或向右移动 $1$ 格，Kiana 规定自己的过河卒二还可以在一步中向右上方移动 $1$ 格，即如果当前卒位于坐标 $(x,y)$ 处，则下一步可以走到 $(x+1,y)$ 、$(x,y+1)$ 或 $(x+1,y+1)$ 中的任意一格里面去，同时 Kiana 认为，如果两种移动方案在某一步时卒移动的方向（右、上或右上）不同，则两种方案就是不同的，例如从 $(1,1)$ 先走到 $(1,2)$ 再走到 $(2,2)$ 、从 $(1,1)$ 先走到 $(2,1)$ 再走到 $(2,2)$ 和从 $(1,1)$ 直接走到 $(2,2)$ 是三种不同的移动方案。

其次，过河卒二的终点不再是一个特定的位置，Kiana 规定卒可以从棋盘的上方或右方走出棋盘，此时就视为游戏成功。注意在走出棋盘时仍然有方向选择的不同，例如若过河卒位于 $(1,M)$ 处，则下一步它可以向右或者向右上用两种方式走出棋盘，若过河卒位于 $(N,M)$ 处，则下一步它可以向上、向右或者向右上用三种方式走出棋盘，以不同的方式走出棋盘仍然被算作是不同的移动方案。

此外，对方马的攻击范围不再是有规律的几个位置，而是 Kiana 规定好的 $K$ 个特定坐标，并要求过河卒在移动的过程中不能走到这 $K$ 个坐标的任何一个上，在除这些坐标以外的位置上过河卒都可以按规则自由移动。

现在 Kiana 想知道，过河卒二有多少种不同的移动方案可以走出棋盘，这个答案可能非常大，她只想知道方案数对 $59393$ 取模后的结果。由于她不会算，所以希望由你来告诉她。


## 输入格式

第一行包含三个整数 $N$ 、$M$ 和 $K$ ，分别表示棋盘的坐标范围与对方马的攻击格子数（即 Kiana 规定的不能经过的坐标数）。

接下来 $K$ 行，第 $i$ 行包含两个正整数 $X_i$ 和 $Y_i$ ，表示对方马的第 $i$ 个攻击坐标为 $(X_i,Y_i)$ 。

对于所有数据，保证 $1\leq N\leq 10^9,1\leq M\leq 10^5,0\leq K\leq 20,1\leq X_i\leq N,1\leq Y_i\leq M$，$(1,1)$ 一定不会被对方马攻击，且被攻击的格子中不存在两个坐标相同的格子。
## 输出格式

输出一行一个整数，表示过河卒走出棋盘的方案数对 $59393$ 取模后的结果。


## 样例

### 样例输入 #1
```
3 3 1
2 2
```
### 样例输出 #1
```
24
```
## 提示

### 样例解释

用 $\uparrow$ 表示过河卒向上移动了一格，用 $\rightarrow$ 表示过河卒向右移动了一格，用 $\nearrow$ 表示过河卒向右上移动了一格，由此可以简化样例解释的表述。

$24$ 种移动方案如下：

$(\uparrow\uparrow\uparrow)$、$(\uparrow\uparrow\nearrow)$、$(\uparrow\uparrow\rightarrow\uparrow)$、$(\uparrow\uparrow\rightarrow\nearrow)$、

$(\uparrow\uparrow\rightarrow\rightarrow\uparrow)$、$(\uparrow\uparrow\rightarrow\rightarrow\nearrow)$、$(\uparrow\uparrow\rightarrow\rightarrow\rightarrow)$、$(\uparrow\nearrow\uparrow)$、

$(\uparrow\nearrow\nearrow)$、$(\uparrow\nearrow\rightarrow\uparrow)$、$(\uparrow\nearrow\rightarrow\nearrow)$、$(\uparrow\nearrow\rightarrow\rightarrow)$、

$(\rightarrow\rightarrow\rightarrow)$、$(\rightarrow\rightarrow\nearrow)$、$(\rightarrow\rightarrow\uparrow\rightarrow)$、$(\rightarrow\rightarrow\uparrow\nearrow)$、

$(\rightarrow\rightarrow\uparrow\uparrow\rightarrow)$、$(\rightarrow\rightarrow\uparrow\uparrow\nearrow)$、$(\rightarrow\rightarrow\uparrow\uparrow\uparrow)$、$(\rightarrow\nearrow\rightarrow)$、

$(\rightarrow\nearrow\nearrow)$、$(\rightarrow\nearrow\uparrow\rightarrow)$、$(\rightarrow\nearrow\uparrow\nearrow)$、$(\rightarrow\nearrow\uparrow\uparrow)$。

### 版权信息

来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2019。

题解等资源可在 <https://github.com/wangyurzee7/THUPC2019> 查看。


---

---
title: "[YsOI2020] 计划"
layout: "post"
diff: 省选/NOI-
pid: P6595
tag: ['数学', 'Special Judge', 'O2优化', '容斥原理', '期望']
---
# [YsOI2020] 计划
## 题目背景

相信大家已经知道了这样几个事实：  
- Ysuperman 是很有钱。

- Ysuperman 一直都很善于制定计划。

- Ysuperman 管理着一个幼儿园。

- Ysuperman 收藏了一些零食。

- 每一天，TA 可能会心血来潮地想要有计划地吃掉 TA 的零食。

## 题目描述

Ysuperman 现在有 $n$ 份零食，对**每份**零食而言，TA 每一天有 $P$ 的概率对 TA 的这份零食做出计划，TA 每做出一份计划后的 $T$ 天后，TA 将会将这一份零食给吃掉。需要特殊说明的是，如果在Ysuperman制定计划前已经对该份零食做出计划，则实际会按照**第一份计划的时间**将零食吃掉。

不幸的是，幼儿园内贪吃的小朋友会破坏这一计划。  幼儿园内有 $m$ 个小朋友，TA 们觊觎着 Ysuperman 的零食。对于**每份**零食，每天会有 $p_i$ 的概率被第 $i$ 个小朋友偷吃。如果这份零食在某位小朋友偷吃之前被吃掉了，那么相应地，这位小朋友就偷吃不了。**如果有一份零食在计划完成前被偷吃，那么，相关计划就无法实现了。**

现在 Ysuperman 要对 TA 的计划进行风险评估，TA 悬赏了 $114514pts$ ，这个项目在经过层层转包后来到了您的手上，现在已经算出了各概率在模意义下的值。经过各方协商，您如果解决了这个问题，您可以获得 $ 100pts $ 。您需要告诉 TA **Ysuperman 能期望吃掉多少份零食，以及 Ysuperman 的零食期望在多少天后被吃完** 。

**如果一份零食被某位小朋友吃掉了，那么这份零食就不属于Ysuperman了。**

需要注意的是，Ysuperman每天制定计划的时间在小朋友偷吃糖果**之前**。

Ysuperman 认为浮点数的精度误差太大，所以你只需要输出答案**对 $998244353$ 取模**的结果。
## 输入格式

第一行包括三个正整数 $n,m,T$ ，含义如题目所述。 

第二行包括一个正整数 $ P $ ，表示 $P$ 对 $998244353$ 取模后的结果。  

第三行包括 $m$ 个正整数 $p_1,p_2,\cdots,p_m$ ，分别表示 $p_i$ 对 $998244353$ 取模后的结果。
## 输出格式

一行，两个自然数。 分别表示 Ysuperman 能期望吃掉多少份零食，以及 Ysuperman 的零食期望在多少天后被吃完，您需要输出答案对 $998244353$ 取模后的结果。


## 样例

### 样例输入 #1
```
5 8 11
13482572 
299473306 598946612 898419918 199648871 499122177 798595483 99824436 1
```
### 样例输出 #1
```
0 1
```
### 样例输入 #2
```
3 5 0
1
1 1 1 1 1
```
### 样例输出 #2
```
3 1
```
### 样例输入 #3
```
2 2 0
499122177
499122177 499122177
```
### 样例输出 #3
```
855638018 507044752
```
### 样例输入 #4
```
11 4 514
1919810
1919810 1919810 1919810 1919810
```
### 样例输出 #4
```
550831570 75142974
```
### 样例输入 #5
```
100000 20 227
2020
2000 2001 2002 2003 2004 2005 2006 2007 2008 2009 2010 2011 2012 2013 2014 2015 2016 2017 2018 2019
```
### 样例输出 #5
```
808786679 861511854
```
## 提示

### 样例说明

#### 样例说明 $1$:

在取模前的其中一种可能情况为：
```cpp
5 8 11  
0.1  
0.1 0.2 0.3 0.4 0.5 0.6 0.7 1
```
该情况下，小朋友会在第一天中偷吃完所有的零食。

#### 样例说明 $2$:

在取模前的一种可能情况为：
```cpp
3 5 0  
1  
1 1 1 1 1
```

该情况下，Ysuperman 会在第一天计划并吃完所有的零食。

#### 样例说明 $3$:

在取模前的一种可能的情况为：

```cpp
2 2 0  
0.5  
0.5 0.5
```
在此情况下，答案为 $\dfrac{8}{7}$ 和 $\dfrac{80}{63}$。

由于解答过程较为复杂，所以请聪明的读者自行思考。


------------
### 数据范围

**如果您只答对了某个测试点两问中的任意一问，您可以获得这个测试点 $ 25\% $ 的分数。**

以下是致敬 $\text{NOI}$ 的部分分表格：
| 测试点编号 | $n$ | $m$ | $T$ | $P$ | 特殊性质 |
| :-----------: | -----------: | -----------: | -----------: | -----------: | :-----------: |
| 1 | $=1$ | $=1$ | $=0$ | 无其它约束 | 无 |
| 2 | $=1$ | $=10$ | $=1$ | $=1$ | $1$ |
| 3 | $=1$ | $\le100$ | $=227$ | $=1$ | $2$ |
| 4 | $\le 20$ | $\le 1000$ | $=4$ | 无其它约束 | 无 |
| 5 | $\le 100$ | $\le 1000$ | $=4$ | 无其它约束 | 无 |
| 6 | $\le 1000$ | $\le 1000$ | $=227$ | $=0$ | $1$ |
| 7 | $\le 100000$ | $\le 100000$ | $=233$ | $=1$ | $2$ |
| 8 | $\le1919820$ | $=114514$ | $=2333$ | $=0$ | $2$ |
| 9 | $\le1919820$ | $=114514$ | $=2333$ | $=0$ | $2$ |
| 10 | $=100000$ | $=100000$ | $=3$ | 无其它约束 | $2$ |
| 11 | $=114514$ | $=114514$ | $=3$ | 无其它约束 | 无 |
| 12 | $\le1919820$ | $=114514$ | $=0$ | 无其它约束 | $2$ |
| 13 | $\le 1919820$ | $=1$ | $\le 227$ | 无其它约束 | 无 |
| 14 | $\le 1919820$ | $\le114514$ | $\le 227$ | 无其它约束 | $2$ |
| 15 | $\le 1919820$ | $=1$ | $\le 500$ | $=1$ | 无 |
| 16 | $\le 1919820$ | $\le 114514$ | $\le 500$ | $=1$ | 无 |
| 17 | $\le 1919820$ | $\le 114514$ | $\le 500$ | $=1$ | 无 |
| 18 | $\le 1919820$ | $\le 114514$ | $=0$ | 无其它约束 | 无 |
| 19 | $\le 1919820$ | $\le 114514$ | $=0$ | 无其它约束 | 无 |
| 20 | $\le 100000$ | $\le 100000$ | $\le 500$ | 无其它约束 | $2$ |
| 21 | $\le 100000$ | $\le 100000$ | $\le 500$ | 无其它约束 | 无 |
| 22 | $\le 100000$ | $\le 100000$ | $\le 500$ | 无其它约束 | 无 |
| 23 | $\le 1919820$ | $\le 114514$ | $\le 2333$ | 无其它约束 | 无 |
| 24 | $\le 1919820$ | $\le 114514$ | $\le 2333$ | 无其它约束 | 无 |
| 25 | $\le 1919820$ | $\le 114514$ | $\le 2333$ | 无其它约束 | $2$ |

对于 $100\%$ 的数据，满足 $ 1\le n\le 1919820,1\le m \le 114514,0\le T \le 2333,0\le P< 998244353,1\le p_i<998244353$


特殊性质 $1$：存在一个 $i$ 使得$p_i=1$。

特殊性质 $2$：所有的 $p_i$ 都相等。


---

---
title: "【模板】LGV 引理"
layout: "post"
diff: 省选/NOI-
pid: P6657
tag: ['LGV 引理', '容斥原理', '高斯消元']
---
# 【模板】LGV 引理
## 题目描述

这是一道模板题。

有一个 $n\times n$ 的棋盘，左下角为 $(1,1)$，右上角为 $(n,n)$，若一个棋子在点 $(x,y)$，那么走一步只能走到 $(x+1,y)$ 或 $(x,y+1)$。

现在有 $m$ 个棋子，第 $i$ 个棋子一开始放在 $(a_i,1)$，最终要走到 $(b_i,n)$。问有多少种方案，使得每个棋子都能从起点走到终点，且对于所有棋子，走过路径上的点互不相交。输出方案数 $\bmod\ 998244353$ 的值。

两种方案不同当且仅当存在至少一个棋子所经过的点不同。
## 输入格式

**本题有多组数据**

第一行一个整数 $T$，表示该测试点的数据组数。

对于每组数据：

第一行两个整数 $n,m$，分别表示棋盘的大小和起点终点的数量。

接下来 $m$ 行，每行 $2$ 个整数 $a_i,b_i$，其意义已在题目描述中说明。
## 输出格式

对于每一组数据，输出一行一个整数表示方案数 $\bmod\ 998244353$ 的值。
## 样例

### 样例输入 #1
```
3
3 2
1 2
2 3
5 2
1 3
3 5
10 5
3 5
4 7
5 8
7 9
9 10
```
### 样例输出 #1
```
3
155
2047320
```
## 提示

- 对于 $30\%$ 的数据，$n\leq 100$，$m\leq 8$。 

- 对于 $100\%$ 的数据，$T\leq5$，$2\leq n\leq10^6$，$1\leq m\leq100$，$1\leq a_1\leq a_2\leq \dots\leq a_m\leq n$，$1\leq b_1\leq b_2\leq \dots\leq b_m\leq n$。


---

---
title: "[POI 2019] Przedszkole / 幼儿园"
layout: "post"
diff: 省选/NOI-
pid: P6662
tag: ['2019', 'POI（波兰）', '容斥原理']
---
# [POI 2019] Przedszkole / 幼儿园
## 题目背景

幼儿园的早上，老师们要给小孩子发玩具。
## 题目描述

有些小孩子玩玩具是自己一个人玩，有些小孩子是成对玩耍。

现在有 $n$ 个小孩子，这 $n$ 个小孩子可以分为 $m$ 对。

有 $k$ 种玩具，要发放给这些小孩子，必须保证在一对内的小孩子拿到的玩具不同。

求一共有多少种发放方案。

因为要发放的天数很多，所以给定 $z$ 组询问，这 $z$ 组询问中 $n,m$ 和对应的对是不变的，变的是 $k$。
## 输入格式

第一行三个整数 $n,m,z$ 代表小孩子数，成对数和询问数。   
这 $n$ 个小朋友编号为 $1$ 到 $n$。   
接下来 $m$ 行每行两个整数代表一对小朋友。   
接下来 $z$ 行每行一个整数 $k$ 代表一组询问。
## 输出格式

$z$ 行每行一个整数代表发放方案数。        
答案对 $10^9+7$ 取模。
## 样例

### 样例输入 #1
```
4 4 1
1 2
2 3
1 3
3 4
3
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
5 10 2
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
5
6
```
### 样例输出 #2
```
120
720
```
### 样例输入 #3
```
11 40 1
8 1
4 1
3 8
2 6
9 8
11 5
2 5
2 1
11 4
10 6
11 10
9 7
10 4
6 9
9 10
2 11
6 7
8 2
10 8
3 6
11 9
1 10
4 3
6 11
3 11
4 5
8 7
10 3
11 7
9 2
8 6
2 3
3 7
8 4
9 5
4 9
7 2
5 10
10 2
6 4
15
```
### 样例输出 #3
```
142679253
```
## 提示

#### 样例说明

两个附加样例请见附加文件中的 sample 1/2.in 和 sample 1/2.out。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（8 pts）：$n,k \le 8$，$z \le 50$。
- Subtask 2（26 pts）：$n \le 15$。
- Subtask 3（33 pts）：$m \le 24$。
- Subtask 4（33 pts）：一个小朋友恰好在两对小朋友。

对于 $100\%$ 的数据，$1 \le n \le 10^5$，$0 \le m \le \min(10^5,\dfrac{n^2-n}{2})$，$1 \le z \le 1000$，$1 \le k \le 10^9$。

对于其中 $50\%$ 的数据，$z=1$。

#### 说明

翻译自 [POI 2019](https://sio2.mimuw.edu.pl/c/oi27-1/dashboard/) D [Przedszkole](https://sio2.mimuw.edu.pl/c/oi27-1/p/prz/)。


---

---
title: "「JZOI-1」红包"
layout: "post"
diff: 省选/NOI-
pid: P7360
tag: ['素数判断,质数,筛法', '最大公约数 gcd', '莫比乌斯反演', '二项式定理', '容斥原理']
---
# 「JZOI-1」红包
## 题目背景

新年到了，小僖收到了叔叔寄给他的红包，这个红包里面有很多很多的钱。
## 题目描述

小僖收到的红包总额是这样的：

所有 $K$ 元组满足每个元素都是正整数且 $\le N$，总额就是这些 $K$ 元组的最小公倍数的乘积。

但由于叔叔并没有那么多的钱，所以结果还要对 $998244353$ 取模。

小僖花了 $10^{-16}$ 秒就算了出来，但他想验证一下是否正确，于是找上了你（别问我为什么他不直接拆开红包看）。

换句话讲，题目只需要你求：
$$\prod_{i_1=1}^N\prod_{i_2=1}^N...\prod_{i_K=1}^N{\rm lcm}(i_1,i_2...i_K)\mod 998244353$$
保证 $K>1$，其中，${\rm lcm}(i_1,i_2...i_K)$，表示 $i_1,i_2...i_K$ 的最小公倍数。
## 输入格式

**本题有多组数据**。

第一行一个数：$T$，表示数据组数。

接下来 $T$ 行，每行两个数，$N,K$，表示每组询问。
## 输出格式

$T$ 行，每行一个数，表示答案，记得对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
2
2 2
3 2
```
### 样例输出 #1
```
8
7776
```
## 提示

对于样例的第一组数据，题目要求求出 ${\rm lcm}(1,1)\times {\rm lcm}(1,2)\times {\rm lcm}(2,1)\times {\rm lcm}(2,2)$。

显然，除了 ${\rm lcm}(1,1)=1$ 以外其它的结果都为 $2$，所以答案为 $1\times2\times2\times2=8$。

| 数据编号 | $N\le$ | $K\leq$ | $T=$ |
| :-----------: | ----------- | ----------- | ----------- |
| **0** |$10$|$5$|$10$|
| **1** | $10^6$ |$2$|$10^3$|
| **2** | $10^6$ |$3$|$10^3$|
| **3** | $100$ |$10^{18}$|$100$|
| **4** | $10^5$ |$100$|$10^3$|
| **5** | $10^5$ |$3\times10^8$|$1$|
| **6** | $10^5$ |$10^{100}$| $10$ |
| **7** |$10^6$|$10^{18}$|$10^3$|
| **8** |$10^6$|$10^{100}$|$10^3$|
| **9** |$10^6$|$10^{100}$|$10^3$|

**出题人：你真以为有这么多钱，哈哈，里面装的全是津巴布韦币哦！**


---

---
title: "50 年后的我们"
layout: "post"
diff: 省选/NOI-
pid: P7483
tag: ['动态规划 DP', 'O2优化', '动态规划优化', '组合数学', '二项式定理', '容斥原理']
---
# 50 年后的我们
## 题目背景

YSGHYYDS
## 题目描述

YSGH 给一场比赛出了 $n$ 道题，第 $i$ 道题的难度为 $d_i$，价值为 $c_i$。

有 $m$ 个可能参赛的选手。第 $i$ 个选手有 $p_i$ 的概率会参加比赛。若第 $i$ 个选手参加比赛，则该选手会恰好通过难度在 $l_i$ 到 $r_i$ 之间（包括 $l_i$ 和 $r_i$）的所有题目。

比赛组委会最终给 YSGH 的奖金为所有题中，有选手通过的题的价值之和的 $k$ 次幂。特别地，我们定义 $0$ 的 $0$ 次幂等于 $1$。

YSGH 想让你帮他求出奖金的期望。

令 $P=998244353$，设一个有理数 $x$ 表示成最简分数的形式为 $\frac{a}{b}$，若 $\gcd(b,P)=1$，则存在唯一的整数 $c$（$0 \le c < P$）满足 $b c \equiv a \pmod{P}$，我们称 $x$ 在模 $P$ 意义下的值为 $c$。

可以证明，在仅给出 $p_i$ 模 $P$ 意义下的值时，答案仍然在模 $P$ 意义下唯一存在。
## 输入格式

第一行，三个整数 $n,m,k$，表示题目数量，可能参赛的人数，以及计算奖金需要的参数。

接下来 $n$ 行，第 $i$ 行两个整数 $d_i, c_i$，分别表示第 $i$ 道题的难度和价值。

接下来 $m$ 行，第 $i$ 行三个整数 $l_i, r_i, p_i$，分别表示第 $i$ 个选手通过的题的难度区间，以及来参加比赛的概率在模 $P$ 意义下的值。
## 输出格式

一行，一个整数，表示奖金的期望在模 $P$ 意义下的值。
## 样例

### 样例输入 #1
```
5 2 1
346 412
464 685
895 544
976 322
612 121
346 712 2
850 932 3

```
### 样例输出 #1
```
4068

```
### 样例输入 #2
```
5 2 2
346 412
464 685
895 544
976 322
612 121
233 749 798465123
698 985 151455772

```
### 样例输出 #2
```
105133973
```
## 提示

**【样例解释 \#1】**

该样例满足特殊性质 A。

第一个人若参赛，可以通过第 $1,2,5$ 题。

第二个人若参赛，可以通过第 $3$ 题。

所以 YSGH 的奖金期望为 $(412+685+121)\times 2\times (1-3)+544\times (1-2)\times 3+(412+685+121+544)\times 2\times 3\equiv 4068\pmod{P}$。

---

**【数据范围】**

**本题采用捆绑测试。**

对于 $100\%$ 的数据，$1\le n\le 400$，$0\le k\le 400$，$1\le m\le 10^5$，$1\le d_i\le 10^9$，$1\le l_i\le r_i\le 10^9$，$0\le c_i,p_i < 998244353$。

各 Subtask 的特殊限制与分值如下：

| 测试包编号 | $n\le $ | $k\le $ | 其他限制 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $400$ | $1$ | 特殊性质 A | $5$ |
| $2$ | $400$ | $1$ | 无 | $6$ |
| $3$ | $400$ | $2$ | 特殊性质 A | $7$ |
| $4$ | $400$ | $2$ | 无 | $8$ |
| $6$ | $18$ | $100$ | 特殊性质 A | $3$ |
| $5$ | $18$ | $100$ | 无 | $15$ |
| $7$ | $100$ | $100$ | 特殊性质 A | $9$ |
| $8$ | $100$ | $100$ | 无 | $16$ |
| $9$ | $400$ | $400$ | 特殊性质 A | $10$ |
| $10$ | $400$ | $400$ | 无 | $21$ |

特殊性质 A：对于任意 $1\le i < j\le M$，都有 $[l_i,r_i]\cap [l_j,r_j]=\varnothing$。


---

---
title: "[传智杯 #4 决赛] [yLOI2021] 染色"
layout: "post"
diff: 省选/NOI-
pid: P8202
tag: ['O2优化', '树形 DP', '容斥原理', '传智杯']
---
# [传智杯 #4 决赛] [yLOI2021] 染色
## 题目背景

传智杯 2021 决赛 G 题。
## 题目描述

传智专修学院的老师给小智布置了一项任务。

老师给了小智一张纸，上面画着一棵有 $n$ 个节点的树（如果你不知道什么是树，可以参考上一题对此的解释）。老师还给了小智 $m$ 支彩色笔，每支笔的颜色都是不同的。老师想要让小智用这 $m$ 种颜色给树的节点涂色，使得这棵树满足如下约束：

1. 每个节点都被涂上了这 $m$ 个颜色之一的**一种**颜色。
2. 相邻两个节点（若存在一条边直接连接 $u$ 和 $v$，则我们称 $u,v$ 相邻）的颜色是不同的。
3. 任何一种颜色被使用的次数都不能超过 $\lfloor\frac{n}{3}\rfloor + 1$。

需要指出的是，虽然每个节点都必须被涂上一种颜色，但是每个颜色并不必须被使用。

如此简单的任务难不倒小智，所以小智提出了一个更困难的问题：他想知道一共有多少种染色的方案满足老师的要求。小智不会解答这个问题，所以来求助你，请你帮他解决他的问题。

因为方案数可能非常大，你只需要输出这个方案数除以 $998,244,353$ 的余数。两种染色方案不同当且仅当存在一个节点 $u$，使得 $u$ 在两种方案种被染上的颜色不同。
## 输入格式

第一行是两个整数，依次表示树的节点数 $n$ 和颜色的个数 $m$。  
接下来 $(n - 1)$ 行，每行两个整数 $u, v$，表示树上有一条连接 $u, v$ 的边。
## 输出格式

输出一行一个整数，表示方案数除以 $998,244,353$ 的余数。
## 样例

### 样例输入 #1
```
4 4
1 2
1 3
3 4

```
### 样例输出 #1
```
108
```
### 样例输入 #2
```
3 3
1 2
1 3

```
### 样例输出 #2
```
12
```
### 样例输入 #3
```
5 5
1 2
1 3
2 4
3 5

```
### 样例输出 #3
```
1200
```
### 样例输入 #4
```
5 5
1 2
1 3
2 4
2 5
```
### 样例输出 #4
```
1140
```
### 样例输入 #5
```
7 8
1 2
1 3
2 4
2 5
3 6
3 7

```
### 样例输出 #5
```
929376
```
### 样例输入 #6
```
6 6
1 2
1 3
3 4
4 5
3 6
```
### 样例输出 #6
```
18750
```
### 样例输入 #7
```
10 20
1 2
1 3
2 4
2 5
2 6
2 7
3 8
5 9
9 10

```
### 样例输出 #7
```
688946281
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $1 \leq u, v \leq n\leq 100$，$n \leq m \leq 10^6$，保证给出的是一棵树。

### 提示

**请注意常数因子对程序效率造成的影响**。


---

---
title: "[省选联考 2022] 卡牌"
layout: "post"
diff: 省选/NOI-
pid: P8292
tag: ['各省省选', '2022', 'O2优化', '容斥原理', '快速沃尔什变换 FWT']
---
# [省选联考 2022] 卡牌
## 题目描述

小 A 有 $n$ 张卡牌，编号为 $1, 2, \ldots, n$。每张卡牌上写着一个正整数，第 $i$ 张卡牌上的正整数为 $s_i$。

现在有 $m$ 轮游戏，第 $i$ 轮游戏会给出 $c_i$ 个质数，小 A 需要选择任意多张卡牌，使得这些卡牌上面的正整数的乘积能被该轮游戏给出的每个质数整除。

这当然难不倒小 A，于是他开始思考一个更难的问题，对于每一轮游戏，他有多少种卡牌的选法。

这给小 A 整不会了，于是他只能来求助你，你只需要告诉他答案模 $998244353$ 的值即可。两种选法 A 和 B 互不相同当且仅当存在一张卡牌在 A 中被选择但在 B 中未被选择或者存在一张卡牌在 B 中被选择但在 A 中未被选择。注意：牌面上的数字相同但编号不相同的两张卡牌被视为不同的卡牌。
## 输入格式

第一行一个正整数 $n$，表示卡牌数量。

第二行 $n$ 个正整数 $s_i$，表示每张卡牌上写的数字。

第三行一个正整数 $m$，表示游戏轮数。

接下来 $m$ 行，每行第一个正整数 $c_i$，表示该轮游戏给出的质数个数，接下来 $c_i$ 个质数 $p_{i, j}$，表示该轮游戏给出的所有质数。数据保证 $\sum_i c_i \le 18000$，即所有 $c_i$ 之和不超过 $18000$。
## 输出格式

输出 $m$ 行，每行一个整数，第 $i$ 行表示第 $i$ 轮游戏的方案数模 $998244353$ 的值。
## 样例

### 样例输入 #1
```
5
10 2 10 5 46
4
2 2 5
2 2 23
1 3
1 23
```
### 样例输出 #1
```
27
16
0
16
```
### 样例输入 #2
```
见附件中的 card/card2.in
```
### 样例输出 #2
```
见附件中的 card/card2.ans
```
## 提示

**【样例解释 #1】**

第一轮游戏：除了以下 $5$ 种方案外其它方案都可行：什么都不选、选 $2$、选 $5$、选 $46$、选 $2$ 和 $46$。所以答案为 $2^5 - 5 = 27$。

第二轮游戏：只要选了 $46$，其它卡牌选不选均可，所以答案为 $2^4 = 16$。

**【数据范围】**

对于 $100 \%$ 的数据，$1 \le n \le {10}^6$，$1 \le s_i \le 2000$，$1 \le m \le 1500$，$1 \le c_i, \sum_i c_i \le 18000$，$2 \le p_{i, j} \le 2000$。

| 测试点 | $n \le$ | $m \le$ | $\sum_i c_i \le$ | 其他限制 |
|:-:|:-:|:-:|:-:|:-:|
| $1 \sim 2$ | $10$ | $10$ | $20$ | $s_i \le 30$ |
| $3 \sim 5$ | $10$ | $20$ | $50$ | 无 |
| $6 \sim 8$ | ${10}^6$ | $1500$ | $10000$ | $s_i \le 30$ |
| $9 \sim 11$ | $10000$ | $1000$ | $5000$ | $s_i \le 500$ |
| $12 \sim 13$ | $1000$ | $100$ | $1000$ | 无 |
| $14 \sim 17$ | $5000$ | $600$ | $7000$ | 无 |
| $18 \sim 20$ | ${10}^6$ | $1500$ | $18000$ | 无 |


---

---
title: "[NOIP2022] 建造军营"
layout: "post"
diff: 省选/NOI-
pid: P8867
tag: ['2022', 'NOIP 提高组', 'O2优化', '树形 DP', '强连通分量', 'Tarjan', '容斥原理']
---
# [NOIP2022] 建造军营
## 题目描述

A 国与 B 国正在激烈交战中，A 国打算在自己的国土上建造一些军营。

A 国的国土由 $n$ 座城市组成，$m$ 条双向道路连接这些城市，使得**任意两座城市均可通过道路直接或间接到达**。A 国打算选择一座或多座城市（**至少一座**），并在这些城市上各建造一座军营。

众所周知，军营之间的联络是十分重要的。然而此时 A 国接到情报，B 国将会于不久后袭击 A 国的一条道路，但具体的袭击目标却无从得知。如果 B 国袭击成功，这条道路将被切断，可能会造成 A 国某两个军营无法互相到达，这是 A 国极力避免的。因此 A 国决定派兵看守若干条道路（**可以是一条或多条，也可以一条也不看守**)，A 国有信心保证被派兵看守的道路能够抵御 B 国的袭击而不被切断。

A 国希望制定一个建造军营和看守道路的方案，使得 B 国袭击的无论是 A 国的哪条道路，都不会造成某两座军营无法互相到达。现在，请你帮 A 国计算一下可能的建造军营和看守道路的方案数共有多少。由于方案数可能会很多，你只需要输出其对 $1,000,000,007\left(10^{9}+7\right)$ 取模的值即可。两个方案被认为是不同的，当且仅当存在至少一 座城市在一个方案中建造了军营而在另一个方案中没有，或者存在至少一条道路在一个 方案中被派兵看守而在另一个方案中没有。

## 输入格式

第一行包含两个正整数 $n,m$，分别表示城市的个数和双向道路的数量。

接下来 $m$ 行，每行包含两个正整数 $u_{i},v_{i}$，描述一条连接 $u_{i}$ 和 $v_{i}$ 的双向道路。保证没有重边和自环。
## 输出格式

输出一行包含一个整数，表示建造军营和看守道路的方案数对 $1,000,000,007\left(10^{9}+ 7\right)$ 取模的结果。
## 样例

### 样例输入 #1
```
2 1
1 2
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
4 4
1 2
2 3
3 1
1 4
```
### 样例输出 #2
```
184
```
### 样例输入 #3
```
见附加文件里的 barrack/barrack3.in
```
### 样例输出 #3
```
见附加文件里的 barrack/barrack3.ans
```
### 样例输入 #4
```
见附加文件里的 barrack/barrack4.in
```
### 样例输出 #4
```
见附加文件里的 barrack/barrack4.ans
```
## 提示

### 样例 1 解释

A 国有两座城市，一条道路连接他们。所有可能的方案如下：

- 在城市 $1$ 建军营, 不看守这条道路;
- 在城市 $1$ 建军营, 看守这条道路;
- 在城市 $2$ 建军营, 不看守这条道路;
- 在城市 $2$ 建军营, 看守这条道路;
- 在城市 $1,2$ 建军营, 看守这条道路。

### 数据规模与约定

对所有数据，保证 $1 \leq n \leq 5 \times 10^5$，$n - 1 \leq m \leq 10^6$，$1 \leq u_i, v_i \leq n$，$u_i \neq v_i$。

各测试点的信息如下

|测试点编号 | $n \leq $ | $m \leq $| 特殊条件 |
| :-: | :-: | :-: | :-: |
| $1 \sim 3$ | $8$ | $10$ | 无 |
| $4 \sim 7$ | $16$ | $25$ | 无 |
| $8 \sim 9$ | $3000$ | $5000$ | 无 |
| $10 \sim 11$ | $5 \times 10^5$ | $10^6$ | 特殊性质 $\mathrm{A}$ |
| $12 \sim 14$ | $5 \times 10^5$ | $10^6$ | $m = n - 1$ |
| $15 \sim 16$ |  $5 \times 10^5$ | $10^6$ | $m = n$ |
| $17 \sim 20$ | $5 \times 10^5$ | $10^6$ | 无 |

特殊性质 $\mathrm{A}$：保证 $m=n-1$ 且第 $i$ 条道路连接城市 $i$ 与 $i+1$。 


---

---
title: "[DMOI-R2] 回到过去"
layout: "post"
diff: 省选/NOI-
pid: P8915
tag: ['O2优化', '组合数学', '容斥原理']
---
# [DMOI-R2] 回到过去
## 题目背景

 > 想回到过去\
试着抱你在怀里\
羞怯的脸带有一点稚气\
想看你看的世界\
想在你梦的画面\
只要靠在一起就能感觉甜蜜\
想回到过去\
试着让故事继续\
至少不再让你离我而去\
分散时间的注意\
这次会抱得更紧\
这样挽留不知还来不来得及\
想回到过去\
沉默支撑跃过陌生\
静静看着凌晨黄昏\
你的身影 失去平衡\
慢慢下沉\
想回到过去\
—— 周杰伦《[回到过去](https://www.bilibili.com/video/BV1fx411N7bU?p=32&vd_source=2f4592e5507d6452d7d44dc098844d6b)》
>

什么阻碍着两颗心的碰面？什么阻碍着两个人的相见？

或许是令人捉摸不透的时间吧。
## 题目描述

给出 $n,m,t$ 以及 $t$ 个障碍物坐标，求在 $n$ 行 $m$ 列的矩阵中的非障碍位置上放置 $k$ 个两两之间没有公共边的方格的方案有多少种，答案对 $10^9+7$ 取模。
## 输入格式

**本题有多组数据。**

第一行一个整数 $T$，表示测试点数量。

接下来 $T$ 个测试点，每个测试点的第一行四个整数 $n,m,k,t$。接下来 $t$ 行，每行两个整数 $x_i,y_i$，表示第 $i$ 个障碍物的坐标（保证不重叠）。
## 输出格式

共 $T$ 行，每行一个整数表示当前询问的答案。
## 样例

### 样例输入 #1
```
5
4 3 2 0
5 7 3 0
2 2 3 0
1 8 2 0
19 13 3 0
```
### 样例输出 #1
```
49
4773
0
21
2369219
```
### 样例输入 #2
```
10
4329 12935 3 0
125891 5949823 2 0
95023489 15327384 3 0
28592394 32891538 2 0
5894392 52374853 2 0
58963495 32591238 3 0
438291538 42819324 3 0
58493683 234728 2 0
284952 823499 3 0
528394298 25892948 3 0
```
### 样例输出 #2
```
468372138
510295355
536959469
56564283
462091483
842203294
778629925
806214146
91259493
793676806
```
### 样例输入 #3
```
10
55888076 506356561 3 3
48940088 192152177
33004718 365781091
45088097 31400730
65004621 206038505 2 3
50919157 24882066
50919158 24882064
50919156 24882067
249418509 7616530 2 1
205309921 4639136
164784593 419325145 3 4
105814446 200482317
105814449 200482315
105814443 200482315
79723922 206425705
477366546 180501076 3 4
39819749 14485585
39819746 14485582
39819743 14485588
39819748 14485585
84215455 29656489 3 0
524291275 23244413 3 4
8149961 10903189
8149958 10903192
8149958 10903193
8149961 10903191
584987873 823324694 3 1
540008401 27919189
25681672 419244427 2 4
4753299 108169462
4753301 108169463
4753298 108169462
4753298 108169464
313195991 98402123 3 3
7016773 83186671
7016770 83186674
7016767 83186675
```
### 样例输出 #3
```
580170965
521412840
890711205
353426094
41995284
193113183
352219667
748854206
767819374
351309432
```
### 样例输入 #4
```
10
2 4 2 4
1 1
1 3
2 1
2 4
2 4 3 3
1 2
2 3
1 4
1 1 3 0
3 4 2 0
3 2 2 1
1 2
4 2 3 0
2 3 2 0
5 4 3 3
2 4
1 3
1 1
4 5 2 2
1 4
2 1
3 1 2 0
```
### 样例输出 #4
```
4
5
0
49
5
12
8
385
128
1
```
## 提示

#### 【样例解释 #4】

对于测试点 1，可以画出如下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9ld7rcxr.png)

其中用黑色格子表示障碍物，可发现只有 $\{(1,2)(1,4)\}\{(1,2)(2,3)\}\{(2,2)(1,4)\}\{(2,3)(1,4)\}$ 四种方案满足题意。

对于测试点 2，可以画出如下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/74rbxvs6.png)

可发现只有 $\{(1,1)(1,3)(2,2)\}\{(1,1)(1,3)(2,4)\}\{(1,1)(2,2)(2,4)\}\{(1,3)(2,1)(2,4)\}\{(1,3)(2,2)(2,4)\}$ 五种情况符合题意。

### 数据点约定

|  数据点编号  |    $n$     |    $m$     |       $k$       |         $t$         |
| :----------: | :--------: | :--------: | :-------------: | :-----------------: |
|     $1$      |    $=1$    | $\le 10^9$ |      $=2$       |        $=0$         |
|     $2$      |    $=1$    | $\le 10^9$ |      $=3$       |        $=0$         |
|     $3$      |  $\le 20$  |  $\le 20$  |      $=2$       |        $=0$         |
|     $4$      |  $\le 20$  |  $\le 20$  |      $=3$       |        $=0$         |
|     $5$      |  $\le 20$  |  $\le 20$  |      $=2$       |      $\le 400$      |
|     $6$      |  $\le 20$  |  $\le 20$  |      $=3$       |      $\le 400$      |
|    $7,8$     | $\le 1000$ | $\le 1000$ |      $=2$       |        $=0$         |
|    $9,10$    | $\le 1000$ | $\le 1000$ |      $=3$       |        $=0$         |
|     $11$     | $\le 1000$ | $\le 1000$ |      $=2$       |      $\le 10$       |
|     $12$     | $\le 1000$ | $\le 1000$ |      $=3$       |      $\le 10$       |
|   $13,14$    | $\le 10^9$ |    $=n$    |      $=2$       |        $=0$         |
|   $15,16$    | $\le 10^9$ |    $=n$    |      $=3$       |        $=0$         |
|   $17,18$    | $\le 10^9$ | $\le 10^9$ |      $=2$       |        $=0$         |
|   $19,20$    | $\le 10^9$ | $\le 10^9$ |      $=3$       |        $=0$         |
|   $21,22$    | $\le 10^9$ | $\le 10^9$ |      $=2$       | $\le 2 \times 10^4$ |
|   $23,24$    | $\le 10^9$ | $\le 10^9$ |      $=3$       | $\le 2 \times 10^4$ |
| $25$ | $\le 10^9$ | $\le 10^9$ | $2 \le k \le 3$ | $\le 2 \times 10^4$ |

对于 $100\%$ 的数据，$1 \le n,m \le 10^9$，$2 \le k \le 3$，$0 \le t \le \min(n\cdot m,2 \times 10^4)$，$1 \le x_i \le n$，$1 \le y_i \le m$，$1 \le T \le 10$。每个数据点等分值。


---

---
title: "[ICPC 2018 Qingdao R] Repair the Artwork"
layout: "post"
diff: 省选/NOI-
pid: P9891
tag: ['动态规划 DP', '2018', 'O2优化', '容斥原理', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Repair the Artwork
## 题目描述

DreamGrid has a paper strip with $n$ grids in a line and he has drawn some beautiful patterns in some grids. Unfortunately, his naughty roommate BaoBao drew some other patterns in some other grids when he wasn't at home. Now DreamGrid has to erase BaoBao's patterns without destroying his own patterns.

Let's number the grids from 1 to $n$ from left to right. Each grid either contains DreamGrid's pattern, or contains BaoBao's pattern, or is empty.

Each time, DreamGrid can select two integers $l$ and $r$ (these two integers can be different each time) such that

- $1 \le l \le r \le n$, and
- for all $l \le i \le r$, the $i$-th grid either contains BaoBao's pattern, or is empty,

and change the $i$-th grid to an empty grid for all $l \le i \le r$.

How many ways can DreamGrid change all the grids containing BaoBao's pattern to empty grids by performing the above operation exactly $m$ times? As the answer may be large, please print the answer modulo $10^9 + 7$.

Let $\{(a_1, b_1), (a_2, b_2), \dots (a_m, b_m)\}$ be a valid erasing sequence ($1 \le a_i \le b_i \le n$), where $(a_i, b_i)$ indicates that DreamGrid selects integers $a_i$ and $b_i$ in the $i$-th operation. Let $\{(c_1, d_1), (c_2, d_2), \dots, (c_m, d_m)\}$ be another valid erasing sequence ($1 \le c_i \le d_i \le n$), where $(c_i, d_i)$ indicates that DreamGrid selects integers $c_i$ and $d_i$ in the $i$-th operation. These two sequences are considered different, if there exists an integer $k$ ($1 \le k \le m$) such that $a_k \ne c_k$ or $b_k \ne d_k$.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 1000$), indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n \le 100$, $1 \le m \le 10^9$), indicating the number of grids and the number of times to perform the operation.

The second line contains $n$ integers $a_i$ ($a_i \in \{0, 1, 2\}$).

- If $a_i = 0$, the $i$-th grid is empty.
- If $a_i = 1$, the $i$-th grid contains DreamGrid's pattern.
- If $a_i = 2$, the $i$-th grid contains BaoBao's pattern.

It's guaranteed that at most 50 test cases have $n > 50$.
## 输出格式

For each test case, output one line containing the number of ways modulo $10^9 + 7$.
## 样例

### 样例输入 #1
```
3
2 2
2 0
3 2
2 1 0
3 1
2 1 0
```
### 样例输出 #1
```
8
3
1
```
## 题目翻译

给定整数 $T(1\le T\le100)$. 对于每组数据 :

给定整数 $n, m(n\le 100, m\le10^9)$. 接下来给出一个长度为 $n$ 的数组 $a$, 保证 $a_i\in \{0, 1, 2\}$.

你需要执行下面的操作恰好 $m$ 次：

- 指定正整数 $l, r \le n$, 满足 $\forall i\in \mathbf{N}$ 且 $i\in[l, r]$, 有 $a_i \ne 1$.
- 将所有满足 $i \in [l, r]$ 的 $a_i$ 赋值为 $0$.

求有多少种不同的操作方式, 使得进行所有 $m$ 次操作后, $\forall i\in[l, r], a_i \ne 2$. 由于答案可能很大，请输出答案对 $10^9 + 7$ 取模的值.

**注意 : 对于每个数据点, 至多有 50 组数据满足 $n>50$.**

Translated by @[Ja50nY0un9](/user/363302).


---

