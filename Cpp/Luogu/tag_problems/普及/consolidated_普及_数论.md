---
title: "[NICA #1] 乘只因"
layout: "post"
diff: 普及/提高-
pid: B3801
tag: ['数论', 'O2优化', '素数判断,质数,筛法', 'Stirling 数']
---
# [NICA #1] 乘只因
## 题目背景

咯咯咯（只因叫）。
## 题目描述


给定 $n,k$，请统计有多少个长度为 $k$ 的序列 $[a_1,a_2,\dots,a_k]$ 满足：

- $a_1\times a_2\times a_3\times \dots\times a_k=n$。
- $1<a_1\leq a_2\leq a_3\leq \dots\leq a_k$。
- 这 $k$ 个数的最小公倍数等于 $n$。

## 输入格式

本题多测，共 $T$ 组数据。

第一行一个正整数 $T$，表示数据组数。

对于每组数据，包含一行两个正整数 $n, k$。

## 输出格式

共 $T$ 行。

每行一个数，第 $i$ 行表示第 $i$ 组数据的答案。

## 样例

### 样例输入 #1
```
1
10 2

```
### 样例输出 #1
```
1
```
## 提示

#### 【样例解释】

- 只能拆分为 $2\times 5$。
- $2$ 和 $5$ 的最小公倍数为 $10$。

#### 【数据范围】

对于 $100\%$ 的数据，满足 $n,k\leq 10^7$，$T\leq 10^5$。


---

---
title: "[NICA #2] 亘久不变"
layout: "post"
diff: 普及/提高-
pid: B3831
tag: ['数论', 'O2优化', '基环树']
---
# [NICA #2] 亘久不变
## 题目背景

此世间，亘久不变之物若显真容，其必似华鸟风月般庄严凛然、隽美无二。
## 题目描述

给定 $n$ 个正整数 $a_i$ 与三个正整数 $x,y,p$，定义一次对**非负整数** $t$ 的变换为：

- 将 $t$ 替换为 $(xt+y)\bmod p$。

定义数 $t$ 是“$k$-不变”的，当且仅当其经过 $k$ 次变换后值不变。

小 Ran 希望知道给定的数组 $a$ 中有多少数是“$k$-不变”的，为了更加准确的知道答案，她会给出 $q$ 组 $k$ 进行询问。
## 输入格式

第一行四个正整数 $n,x,y,p$，意义同题目描述。

第二行 $n$ 个正整数，其中第 $i$ 个正整数为 $a_i$，意义同题目描述。

第三行一个正整数 $q$，意义同题目描述。

接下来 $q$ 行每行一个正整数 $k_i$，代表询问 $a$ 中有多少数是“$k_i$-不变”的。
## 输出格式

对每个询问输出一行一个正整数，表示答案。
## 样例

### 样例输入 #1
```
5 2 3 7
2 3 4 5 6
5
1
2
3
4
5
```
### 样例输出 #1
```
1
1
5
1
1

```
### 样例输入 #2
```
5 3 8 4
2 3 4 5 1
5
1
2
3
4
5
```
### 样例输出 #2
```
1
3
1
3
1
```
## 提示

数据保证，$1\le n\le 10^5$，$1\le p,q\le 10^3$，$1\le a_i,x,y,k_i\le 10^9$。

**注意 $p$ 不一定是质数。**


---

---
title: "[GESP202409 五级] 挑战怪物"
layout: "post"
diff: 普及/提高-
pid: B4050
tag: ['贪心', '2024', '数论', 'GESP']
---
# [GESP202409 五级] 挑战怪物
## 题目描述

小杨正在和一个怪物战斗，怪物的血量为 $h$，只有当怪物的血量**恰好**为 $0$ 时小杨才能够成功击败怪物。

小杨有两种攻击怪物的方式：
- 物理攻击。假设当前为小杨第  $i$ 次使用物理攻击，则会对怪物造成 $2^{i - 1}$ 点伤害。
- 魔法攻击。小杨选择任意一个质数 $x$（ 不能超过怪物当前血量），对怪物造成 $x$ 点伤害。由于小杨并不擅长魔法，他只能使用**至多一次**魔法攻击。

小杨想知道自己能否击败怪物，如果能，小杨想知道自己最少需要多少次攻击。
## 输入格式

**本题单个测试点内有多组测试数据**。第一行包含一个正整数 $t$，代表测试用例组数。

接下来是 $t$ 组测试用例。对于每组测试用例，只有一行一个整数 $h$，代表怪物血量。
## 输出格式

对于每组测试用例，如果小杨能够击败怪物，输出一个整数，代表小杨需要的最少攻击次数，如果不能击败怪物，
输出 $-1$。
## 样例

### 样例输入 #1
```
3
6
188
9999
```
### 样例输出 #1
```
2
4
-1
```
## 提示

### 样例 1 解释

对于第一组测试用例，一种可能的最优方案为，小杨先对怪物使用魔法攻击，选择质数 $5$ 造成 $5$ 点伤害，之后对怪
物使用第 $1$ 次物理攻击，造成 $2^{1 - 1} = 1$ 点伤害，怪物血量恰好为 $0$，小杨成功击败怪物。

### 数据规模与约定

| 子任务编号 | 分数占比 | $t$ | $h$ |
| :-: | :-: | :-: | :-: |
| $1$ | $20\%$ | $\leq 5$ | $\leq 10$ |
| $2$ | $20\%$ | $\leq 10$ | $\leq 100$ |
| $3$ | $60\%$ | $\leq 10$ | $10^5$ |

对于全部的测试数据，保证 $1 \leq t \leq 10$，$1 \leq h \leq 10^5$。


---

---
title: "[蓝桥杯青少年组省赛 2022] 组合"
layout: "post"
diff: 普及/提高-
pid: B4284
tag: ['数学', '2022', '数论', '蓝桥杯青少年组']
---
# [蓝桥杯青少年组省赛 2022] 组合
## 题目描述

某商店将一种糖果按照数量打包成 $N$ 和 $M$ 两种规格来售卖（$N$ 和 $M$ 为互质数，且 $N$ 和 $M$ 有无数包）。这样的售卖方式会限制一些数量的糖果不能买到。现在给出 $N$ 和 $M$ 的值，请你计算出最多不能买到的糖果数量。

## 输入格式

输入两个正整数 $N$ 和 $M$（$2 < N < M < 100$，$N$ 和 $M$ 为互质数），表示这两种规格的糖果数量，正整数之间用一个空格隔开。
## 输出格式

输出一个整数，表示最多不能买到的糖果数量。
## 样例

### 样例输入 #1
```
3 5
```
### 样例输出 #1
```
7
```


---

---
title: "[蓝桥杯青少年组省赛 2022] 组合"
layout: "post"
diff: 普及/提高-
pid: B4290
tag: ['动态规划 DP', '2022', '数论', '蓝桥杯青少年组']
---
# [蓝桥杯青少年组省赛 2022] 组合
## 题目描述

某商家将一种汤圆按照数量不同，分装成 $N$ 种规格来售卖。这样的售卖方式会限制一些数量的汤圆买不到。

例如：
- 当 $N=2$ 时，$2$ 种规格的汤圆分别装 $3$ 个和 $5$ 个，这种情况下限制了 $1$、$2$、$4$、$7$ 四种数量的汤圆不能买到。

给出 $N$ 及 $N$ 种规格的汤圆数量，请计算出有多少种数量的汤圆不能买到。如果有无限种数量的汤圆不能买到，就输出 $-1$。
## 输入格式

第一行输入一个正整数 $N$（$1 \leq N \leq 20$），表示有 $N$ 种规格的汤圆。

第二行输入 $N$ 个各不相同的正整数（$1 \leq$ 每个数 $\leq 100$），表示每种规格的汤圆数量，且正整数之间以一个空格隔开。

## 输出格式

输出在这种情况下有多少种汤圆数量是不能买到的。如果有无限种数量的汤圆不能买到，则输出 $-1$。
## 样例

### 样例输入 #1
```
2
3 5
```
### 样例输出 #1
```
4
```


---

---
title: "「FAOI-R2」Paint (A)"
layout: "post"
diff: 普及/提高-
pid: P10035
tag: ['2024', '数论', '洛谷原创', 'O2优化', 'Ad-hoc']
---
# 「FAOI-R2」Paint (A)
## 题目背景

小 Y 是一个胖子，他最爱下楼梯了，因为下楼梯很省力气，但是他却有强迫症。

由于刷漆工人 HG 的油漆不够，每一层台阶都只刷了一半——左边或右边，好让小 Y 下楼时不踩到油漆。（~~众人：这是什么逻辑？~~）
## 题目描述

整个楼梯共 $3^N$ 级台阶。

HG 刷漆的规律是：对于**从上到下**第 $I$ 级台阶，若 $V_3(I)$ 是奇数，则刷在左边，否则刷在右边。**$V_3(I)$ 的定义请见提示。**

小 Y 因为强迫症，要求自己不能踩到油漆。

现在他来求助你，他最少会踩到油漆多少次？

- 一次只能下一级台阶。
- 如果小 Y 站在当前台阶的左边，则他必须站在下一级台阶的右边，反之亦然。
- 如果油漆在当前台阶左边，那么需要站在当前台阶右边才算没踩到油漆，反之亦然。
- 小 Y 唯一可以控制的是：他在第 $1$ 级台阶上站在哪边。也就是说，小 Y 只有 $2$ 种下楼梯的方案供选择。

答案对 $10^9+7$ 取模。

### 形式化题意

给定三个 01 串 $A,B,C$，长度均为 $3^N$。字符串下标从 $1$ 开始。

其中：

- $A=\texttt{101010101\ldots101}$；
- $B=\texttt{010101010\ldots010}$；
- $C=\texttt{001001000\ldots}$；具体来说，第 $I$ 个字符为 $V_3(I) \bmod 2$。**$V_3(I)$ 的定义请见提示。**

记 $\operatorname{mc}(X,Y)$ 为字符串 $X$ 和 $Y$ 中匹配的字符的个数。

试求：

$$\min\{\operatorname{mc}(A,C),\operatorname{mc}(B,C)\}$$

答案对 $10^9+7$ 取模。
## 输入格式

**本题有多组数据。**

第一行，一个正整数 $T$，代表数据组数。

下面 $T$ 行，每行一个正整数 $N$。
## 输出格式

每组数据一行，输出踩到油漆的最少次数，即 $\min\{\operatorname{mc}(A,C),\operatorname{mc}(B,C)\}$。

**答案对 $10^9+7$ 取模。**
## 样例

### 样例输入 #1
```
1
1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3
494699
494699494699
494699494699494699
```
### 样例输出 #2
```
994161775
899186285
348815909
```
## 提示

样例 $1$ 解释：

- $A=\texttt{101}$；
- $B=\texttt{010}$；
- $C=\texttt{001}$；
- $\operatorname{mc}(A,C)=2$；
- $\operatorname{mc}(B,C)=1$；
- $\min\{\operatorname{mc}(A,C),\operatorname{mc}(B,C)\}=1$。

------------

| 测试点编号 | $T \le$ | $N \le$ | 分值 |
| :-: | :-: | :-: | :-: |
| $1$ | $10$ | $10$ | $50$ |
| $2$ | $10^5$ | $10^{18}$ | $50$ |

对于 $100\%$ 的数据，$1 \le T \le 10^{5}$，$1 \le N \le 10^{18}$。

> **提示：** $V_3(X)$ 指 $X$ 中质因数 $3$ 的个数。例如，$V_3(14)=0$，$V_3(18)=2$。


---

---
title: "「QFOI R2」树色尤含残雨"
layout: "post"
diff: 普及/提高-
pid: P10411
tag: ['数学', '贪心', '数论', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「QFOI R2」树色尤含残雨
## 题目描述

小 R 是一个可爱的女孩子，她喜欢分解质因数。

她有一个正整数 $x$。每次操作可以选择 $p_1,\alpha_1,p_2,\alpha_2$ 满足 $p_1,p_2$ 为两不同质数且 $\alpha_1,\alpha_2$ 为正整数，若 $x$ 是 $p_1^{\alpha_1}p_2^{\alpha_2}$ 的整数倍，就将 $x$ 除以 $p_1^{\alpha_1}p_2^{\alpha_2}$，否则操作无效。

请你求出通过若干次操作可以得到的最小的 $x$。
## 输入格式

一行一个整数 $x$。
## 输出格式

一个整数，表示可以得到的最小的 $x$。
## 样例

### 样例输入 #1
```
9
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
120
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
2310
```
### 样例输出 #3
```
2
```
## 提示

**样例 $1$ 解释**

无法进行任何有效操作。

---

**样例 $2$ 解释**

可以进行以下两次操作：

- 令 $p_1=2,\alpha_1=1,p_2=3,\alpha_2=1$，将 $x$ 除以 $p_1^{\alpha_1}p_2^{\alpha_2}=2^13^1=6$，得到 $x=20$。
- 令 $p_1=2,\alpha_1=2,p_2=5,\alpha_2=1$，将 $x$ 除以 $p_1^{\alpha_1}p_2^{\alpha_2}=2^25^1=20$，得到 $x=1$。

---

**数据范围**

**本题采用捆绑测试。只有通过子任务中所有测试点以及所有依赖的子任务，才能获得相应的分数。**

对于全部数据：$2\le x\le 10^9$。

- 子任务一（$10$ 分）：$x\le 10$。
- 子任务二（$20$ 分）：$x$ 为“无平方因子数”$^\dagger$。
- 子任务三（$20$ 分）：$x$ 为一个质数的正整数次幂。
- 子任务四（$20$ 分）：$x\le 10^5$。依赖子任务一。
- 子任务五（$30$ 分）：无特殊限制。依赖子任务一、二、三、四。

$\dagger$ 称一个数 $x$ 为“无平方因子数”，当且仅当不存在大于一的整数 $k$，使得 $x$ 是 $k^2$ 的整数倍。


---

---
title: "[SNCPC2024] 下棋"
layout: "post"
diff: 普及/提高-
pid: P10702
tag: ['2024', '数论', 'O2优化', '陕西', '进制', 'XCPC']
---
# [SNCPC2024] 下棋
## 题目描述

LNC 喜欢所有 $k$ 进制下所有数位的乘积为自身因子的数。他称之为 LNC 数。例如：

当 $k = 10$ 时，$y = (36)_{10}$ 是 LNC 数，因为 $(3 \times 6) \mid 36$。

当 $k = 4$ 时，$y = (12)_4$ 是 LNC 数，因为转换成十进制后 $(12)_4 = (6)_{10}$，而 $(1 \times 2) \mid 6$。

当 $k = 2$ 时，$y = (1101)_2$ 不是 LNC 数，因为转换成十进制后 $(1101)_2 = (13)_{10}$，而 $0$ 不是 $13$ 的因子。

LNC 在和 LJJ 玩一个游戏，LJJ 给出 $x$ 枚棋子，然后 LNC 选定一个整数 $k$ ($k \geq 2$)。随后他们交替取走若干枚棋子，要求取走的棋子数量是 $k$ 进制意义下的 LNC 数。LNC 先手，先取完的获胜。两个人都绝顶聪明，故都会选择最优的策略。

LJJ 觉得这个游戏很不公平，他们一共玩了 $T$ 局游戏，对于每局游戏他给出的 $x$，他希望知道最小的 $k$ 使得 LNC 先手必胜。
## 输入格式

输入第一行一个正整数 $T$ ($1 \le T \le 1 \times 10^2$)，表示数据组数。

接下来 $T$ 行每行一个正整数 $x$ ($3 \le x \le 10^{18}$)，表示 LJJ 给出的数 $x$。
## 输出格式

输出 $T$ 行每行一个正整数 $k$，表示每个询问的最小的 $k$，使 LNC 先手必胜。
## 样例

### 样例输入 #1
```
3
9
5
10

```
### 样例输出 #1
```
2
2
3

```
## 提示



当 $x=5$ 的时候，LNC 可以选择 $k=2$。$x=(5)_{10}=(101)_2$。

LNC 先手拿掉 $(11)_2$，此时 $x=(10)_2$，LJJ 只能拿走 $(1)_2$，LNC 拿走最后的 $(1)_2$ 获胜。

又因为 $k=2$ 已经不能再小了，所以最终答案为 $k=2$。 


---

---
title: "「SFMOI Round I」Strange Madoka Game"
layout: "post"
diff: 普及/提高-
pid: P11144
tag: ['数论', '洛谷原创', '交互题', 'Special Judge', 'O2优化', '不定方程', '洛谷月赛']
---
# 「SFMOI Round I」Strange Madoka Game
## 题目背景

[English statement](https://www.luogu.com.cn/problem/T510969). **You must submit your code at the Chinese version of the statement.**

> いつも君の側にいるから / 无论何时我都与你同在 \
> 儚すぎて / 世界如此虚幻 \
> 消えて行きそうな世界 / 似乎随时随地都会消失 \
> だけど君がいる / 然而只要有你 \
> それだけで守りたいと思った / 我就心甘情愿将它守护
## 题目描述


**本题和 B2 是不同的问题，请分别仔细阅读两题题面。**

**这是一道交互题。**

**提示**：我们在题目描述的最后提供了一份简要的、形式化描述的题面。

圆和焰在玩游戏。

圆在心中想了一个非负整数 $m$，让焰猜出 $m$ 的值。当然，圆不会为难焰，所以 $\textcolor{red}{0}\le m\le 10^{17}$。圆不会作弊，也就是说，**圆不会悄悄更换想好的数字。**

焰可以问圆：对于**正**整数 $x$，$m\bmod x$ 的值是多少。焰需要用最少的询问次数来猜出 $m$ 的值。（为了得到全部分数，最多只能使用 $2$ 次询问。）

圆一共和焰玩了 $T$ 次游戏。然而，焰的数学很差，于是她找来了你，来帮她猜出这 $T$ 次游戏的答案。



**形式化地**：有一个隐藏的非负整数 $m\in [\textcolor{red}{0},10^{17}]$。每次询问给定**正**整数 $x$，回答 $m\bmod x$。用最少的询问次数找出 $m$。共有 $T$ 组测试数据。$m$ 的数值在事先确定，不会根据询问变化，也就是说，**交互库是非适应性的**。

【实现细节】

对于每个测试点，输入一行一个正整数 $T$，表示游戏次数。

对于每组测试数据，你可以用以下的格式发起一次询问：

- $\texttt{? }x$：询问 $m\bmod x$ 的值。你需要保证 $x$ 是**正**整数，且 $x \in \textcolor{red} {[1,4\times 10^8]}$。

	从标准输入流读入一个整数表示答案。特别地，若整数是 $\texttt{-1}$，你的程序已经被判定为 $\texttt{Wrong Answer}$，此时你需要立刻终止程序。

你可以用以下的格式回答答案：

- $\texttt{! }m$：回答 $m$ 的值。

在发起询问后，需要刷新缓冲区，否则可能导致 TLE。

- 在 C++ 中，使用 `fflush(stdout)` 或 `cout.flush()`。 特别地，利用 `std::endl` 来换行也会刷新缓冲区。
- 在 Pascal 中，使用 `flush(output)`。  
- 在 Python 中，使用 `stdout.flush()`。  
- 对于其它语言，可自行查阅文档。
## 输入格式

见【实现细节】。
## 输出格式

见【实现细节】。
## 样例

### 样例输入 #1
```
1

1

2
```
### 样例输出 #1
```

? 2

? 3

! 5
```
## 提示


#### 数据范围

对于 $100\%$ 的数据，保证 $1\le T\le 100$，$m$ 为非负整数，$\textcolor{red}{0}\le m\le 10^{17}$。

#### 评分方式

记单个测试点中，你的询问次数的最大值为 $Q$。则得分 $\mathrm{score}$ 如下所示：

$$
\begin{aligned}
\mathrm{score}=\begin{cases}
0, & Q\in [81,+\infty) \\
10, & Q\in [11,81) \\
25, & Q\in [3,11) \\
50, & Q\in [0,3) \\
\end{cases}
\end{aligned}
$$

本题得分为所有测试点得分的最小值。

本题数据点的范围是非严格单调递增的。


---

---
title: "[GESP202412 八级] 排队"
layout: "post"
diff: 普及/提高-
pid: P11380
tag: ['图论', '2024', '数论', '图论建模', '组合数学', '排列组合', 'GESP']
---
# [GESP202412 八级] 排队
## 题目描述

小杨所在班级共有 $n$ 位同学，依次以 $1,2,\dots,n$ 标号。这 $n$ 位同学想排成一行队伍，其中有些同学之间关系非常好，在队伍里需要排在相邻的位置。具体来说，有 $m$ 对这样的关系（$m$ 是一个非负整数）。当 $m\geq 1$ 时，第 $i$ 对关系（$1\leq i\leq m$）给出 $a_i,b_i$，表示排队时编号为 $a_i$ 的同学需要排在编号为 $b_i$ 的同学前面，并且两人在队伍中相邻。

现在小杨想知道总共有多少种排队方式。由于答案可能很大，你只需要求出答案对 $10^9+7$ 取模的结果。
## 输入格式

第一行，两个整数 $n,m$，分别表示同学们的数量与关系数量。

接下来 $m$ 行，每行两个整数 $a_i,b_i$，表示一对关系。
## 输出格式

一行，一个整数，表示答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
4 2
1 3
2 4
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 0
```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
3 2
1 2
2 1
```
### 样例输出 #3
```
0
```
## 提示

对于 $20\%$ 的测试数据点，保证 $1\leq n\leq 8$，$0\leq m\leq 10$。

对于另外 $20\%$ 的测试数据点，保证 $1\leq n\leq 10^3$，$0\leq m\leq 1$。

对于所有测试数据点，保证 $1\leq n\leq 2\times 10^5$，$0\leq m\leq 2\times 10^5$。


---

---
title: "[蓝桥杯 2025 省 Python B] A · B Problem"
layout: "post"
diff: 普及/提高-
pid: P12174
tag: ['2025', '数论', '蓝桥杯省赛', '调和级数']
---
# [蓝桥杯 2025 省 Python B] A · B Problem
## 题目描述

设有两个二维向量 $\overrightarrow{A}(X_A, Y_A), \overrightarrow{B}(X_B, Y_B)$。给定 $L$，求 $(X_A, Y_A), (X_B, Y_B)$ 有多少种不同的取值，使得：

1. $X_A, Y_A, X_B, Y_B$ 均为正整数；
2. $\overrightarrow{A} \cdot \overrightarrow{B} \leq L$，其中 $\overrightarrow{A} \cdot \overrightarrow{B}$ 表示 $\overrightarrow{A}, \overrightarrow{B}$ 的内积，即 $X_A \cdot X_B + Y_A \cdot Y_B$。
## 输入格式

输入的第一行包含一个正整数 $L$，表示题目描述中的限制条件。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3
```
### 样例输出 #2
```
5
```
## 提示

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$L \leq 50$；
- 对于 $80\%$ 的评测用例，$L \leq 5000$；
- 对于所有评测用例，$1 \leq L \leq 2^{20}$。


---

---
title: "[蓝桥杯 2023 国 Java B] 逆元"
layout: "post"
diff: 普及/提高-
pid: P12217
tag: ['2023', '数论', '逆元', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Java B] 逆元
## 题目描述

数论中的逆元是一个可以把除法转换为乘法的工具。若自然数 $a, I_a$ 满足 $a \times I_a \equiv 1 \pmod{M}$，则称 $a$ 在模 $M$ 的意义下的逆元为 $I_a$，这样在模 $M$ 下计算除法时，可以把除以 $a$ 的运算转化为乘以其逆元 $I_a$。

给定质数模数 $M = 2\,146\,516\,019$，根据费马小定理对于不是 $M$ 倍数的正整数 $a$，有 $a^{(M-1)} \equiv 1 \pmod{M}$，求出 $[1, 233\,333\,333]$ 内所有自然数的逆元。则所有逆元的异或和为多少？
## 输出格式

这是一道结果填空的题，你只需要算出结果后提交即可。本题的结果为一个整数，在提交答案时只需要**编写一个程序输出这个整数**，输出多余的内容将无法得分。


---

---
title: "[蓝桥杯 2023 国 Java B] 序列"
layout: "post"
diff: 普及/提高-
pid: P12221
tag: ['数学', '2023', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Java B] 序列
## 题目描述

给定一个长度为 $n$ 的正整数序列 $a_1, a_2, \ldots, a_n$，同时有一个首项为 $d$，公差为 $d$，项数为 $n$ 的等差数列 $\{b_1 = d, b_2 = 2d, \ldots, b_n = nd\}$。

定义 $S_d = \displaystyle \sum_{a_i | b_i} 1$，即 $S_d$ 表示当公差为 $d$ 时有多少对 $(a_i, b_i)$ 满足 $b_i$ 被 $a_i$ 整除，请求出 $\displaystyle \sum_{i=1}^{n} S_i$。
## 输入格式

输入共 $2$ 行。

第一行为一个正整数 $n$。

第二行为 $n$ 个由空格隔开的正整数 $a_1, a_2, \ldots, a_n$。
## 输出格式

输出共 $1$ 行，一个整数。
## 样例

### 样例输入 #1
```
4
2 2 3 1
```
### 样例输出 #1
```
14
```
## 提示

### 样例说明

- 当公差等于 $1$：$b = \{1, 2, 3, 4\}$, 有 3 对 $(a_i, b_i)$ 满足条件，$S_1 = 3$。
- 当公差等于 $2$：$b = \{2, 4, 6, 8\}$, 有 4 对 $(a_i, b_i)$ 满足条件，$S_2 = 4$。
- 当公差等于 $3$：$b = \{3, 6, 9, 12\}$, 有 3 对 $(a_i, b_i)$ 满足条件，$S_3 = 3$。
- 当公差等于 $4$：$b = \{4, 8, 12, 16\}$, 有 4 对 $(a_i, b_i)$ 满足条件，$S_4 = 4$。

所以答案为 $3 + 4 + 3 + 4 = 14$。

### 评测用例规模与约定

- 对于 $20\%$ 的数据, 保证 $n \leq 10^3$。
- 对于 $100\%$ 的数据, 保证 $1\leq n \leq 10^5$，$1\leq a_i \leq n$。



---

---
title: "[蓝桥杯 2024 国 Python B] 儿童数"
layout: "post"
diff: 普及/提高-
pid: P12267
tag: ['2024', '数论', '素数判断,质数,筛法', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Python B] 儿童数
## 题目描述

若一个正整数 $n$ 满足 $n^{61}$ 整除 $2024!$，即 $2024!$ 除以 $n^{61}$ 的余数为 $0$，则称 $n$ 为“儿童数”。其中 $2024!$ 表示 2024 的阶乘，即 $1 \times 2 \times \cdots \times 2024$。

现在，请你计算在区间 $[1, \infty)$ 内一共有多少个“儿童数”。
## 输出格式

这是一道结果填空的题，你只需要算出结果后提交即可。本题的结果为一个整数，在提交答案时只需要**编写一个程序输出这个整数**，输出多余的内容将无法得分。


---

---
title: "[蓝桥杯 2024 国 C] 六一儿童节"
layout: "post"
diff: 普及/提高-
pid: P12312
tag: ['数学', '2024', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 C] 六一儿童节
## 题目描述

在蓝桥小镇，每年的六一儿童节是许多孩子最期待的日子。在这一天，神秘的数字精灵会出现，为孩子们带来惊喜和祝福。

今年的六一儿童节格外特别，因为数字精灵带来了一项有趣的挑战给小镇上的孩子们。

挑战的内容是：从数字 $1$ 至 $20240601$ 中找出两个不同的整数 $x$ 和 $y$，使得 $x, y$ 满足 $x$ 小于 $y$，且 $x^x + y^y$ 能够被 $6421$ 整除。成功找到这样一对数字的孩子们将会得到数字精灵准备的豪华大礼包。

对此，请你帮助孩子们计算出所有符合条件的整数对 $(x, y)$ 的数量，帮助小镇上的孩子们解决数字精灵的挑战，让他们能够在六一儿童节收获满满的快乐和难忘的回忆！
## 输出格式

这是一道结果填空的题，你只需要算出结果后提交即可。本题的结果为一个整数，在提交答案时只需要**编写一个程序输出这个整数**，输出多余的内容将无法得分。


---

---
title: "[蓝桥杯 2025 国 B] 新型锁"
layout: "post"
diff: 普及/提高-
pid: P12830
tag: ['动态规划 DP', '2025', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 B] 新型锁
## 题目描述

密码学家小蓝受邀参加国际密码学研讨会，为此他设计了一种新型锁，巧妙地融合了数学的严谨性与密码学的安全性。这把锁包含 2025 个连续的数字格，每个格子需填入一个正整数，从而形成一个长度为 2025 的序列 $\{a_1, a_2, \ldots, a_{2025}\}$，其中 $a_i$ 表示第 $i$ 个格子上的数字。

要想解锁，该序列需满足以下条件：任意两个相邻格子中的数字，其最小公倍数（LCM）均为 2025。即对于所有的 $i$（$1 \leq i \leq 2024$），需满足：

$$\text{LCM}(a_i, a_{i+1}) = 2025$$

现在，请你计算有多少个不同的序列能够解开这把锁。由于答案可能很大，你只需输出其对 $10^9 + 7$ 取余后的结果即可。
## 输出格式

这是一道结果填空的题，你只需要算出结果后提交即可。本题的结果为一个整数，在提交答案时只填写这个整数，填写多余的内容将无法得分。


---

---
title: "[蓝桥杯 2025 国 B] 互质藏卡"
layout: "post"
diff: 普及/提高-
pid: P12831
tag: ['2025', '数论', '素数判断,质数,筛法', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 B] 互质藏卡
## 题目描述

小蓝整理着阁楼上的旧物，偶然发现了一个落满灰尘的卡片箱。打开箱子，里面整齐地摆放着 17600 张卡片，每张卡片上都写有一个数字，恰好包含了从 1 到 17600 的所有正整数。

儿时的他热衷于收集各种卡牌，数量之多令人咋舌。如今，再次翻阅这些尘封的记忆，小蓝不禁感慨万千。他想起收藏家前辈的箴言：“收藏的魅力在于精粹，而非数量”。于是，他决定从这些卡牌中选取 $2025$ 张，组成一套“互质藏卡”。

“互质藏卡”的特点在于：任意两张卡片上的数字之间互质，即它们的最大公约数恒为 $1$。现在，请你帮小蓝计算，共有多少种不同的选取方案，使得选出的 $2025$ 张卡片满足“互质藏卡”的条件。由于答案可能很大，你只需给出其对 $10^9 + 7$ 取余后的结果即可。

注意：两个选取方案被认为是不同的，当且仅当它们所包含的数字集合不完全相同。即，若存在至少一个数字出现在其中一个集合但不出现在另一个集合中，则这两个方案被视为不同。
## 输出格式

这是一道结果填空的题，你只需要算出结果后提交即可。本题的结果为一个整数，在提交答案时只填写这个整数，填写多余的内容将无法得分。


---

---
title: "[蓝桥杯 2025 国 B] 数字轮盘"
layout: "post"
diff: 普及/提高-
pid: P12832
tag: ['数学', '2025', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 B] 数字轮盘
## 题目描述

“数字轮盘”是一款益智游戏，基于一个带有指针的圆形轮盘展开。轮盘边缘按顺时针刻有数字 1 至 $N$，初始时指针指向 1。

游戏分为两阶段：旋转轮盘和恢复轮盘。

第一阶段，将轮盘顺时针旋转 $K$ 次。每次旋转，数字依次后移一位，指针指向的数字随之改变。例如，对于 $N = 4$ 的轮盘，初始状态为 1, 2, 3, 4（指针指向 1），旋转一次变为 4, 1, 2, 3（指针指向 4），再旋转一次变为 3, 4, 1, 2（指针指向 3），依此类推。

第二阶段，小蓝需通过操作恢复初始状态，每次操作包含以下两步：
- 第一步：翻转以指针为起点、顺时针方向的前 $N - 1$ 个数字的顺序。
- 第二步：翻转除指针外的 $N - 1$ 个数字的顺序。

例如，对 $N = 4$，状态为 4, 1, 2, 3（指针指向 4）进行一次操作：
- 第一步：翻转 4, 1, 2，变为 2, 1, 4, 3（指针指向 2）。
- 第二步：翻转 1, 4, 3，变为 2, 3, 4, 1（指针指向 2）。

现在，给定轮盘的数字个数 $N$ 和旋转次数 $K$，请计算小蓝最少需要几次操作才能恢复初始状态。如果无法恢复初始状态，则输出 -1。

## 输入格式

输入的第一行包含一个整数 $T$，表示测试用例的数量。

接下来 $T$ 行，每行包含两个整数 $N$ 和 $K$，分别表示轮盘上的数字个数和旋转次数。
## 输出格式

输出共 $T$ 行，每行包含一个整数，表示最少需要的操作次数。如果无法恢复初始状态，则输出 $-1$。
## 样例

### 样例输入 #1
```
2
3 2
4 1
```
### 样例输出 #1
```
2
-1
```
## 提示

**【评测用例规模与约定】**

对于 30% 的评测用例，$1 \leq T \leq 10^2$，$2 \leq N \leq 500$，$0 \leq K \leq 500$。

对于 100% 的评测用例，$1 \leq T \leq 10^5$，$2 \leq N \leq 10^9$，$0 \leq K \leq 10^9$。


---

---
title: "[GESP202506 六级] 最大因数"
layout: "post"
diff: 普及/提高-
pid: P13016
tag: ['图论', '2025', '数论', '最近公共祖先 LCA', 'GESP']
---
# [GESP202506 六级] 最大因数
## 题目描述



给定一棵有 $10^9$ 个结点的有根树，这些结点依次以 $1, 2, \dots, 10^9$ 编号，根结点的编号为 $1$。对于编号为 $k$（$2 \leq k \leq 10^9$）的结点，其父结点的编号为 $k$ 的因数中除 $k$ 以外最大的因数。

现在有 $q$ 组询问，第 $i$（$1 \leq i \leq q$）组询问给定 $x_i, y_i$，请你求出编号分别为 $x_i, y_i$ 的两个结点在这棵树上的距离。两个结点之间的距离是连接这两个结点的简单路径所包含的边数。

## 输入格式


第一行，一个正整数 $q$，表示询问组数。

接下来 $q$ 行，每行两个正整数 $x_i, y_i$，表示询问结点的编号。
## 输出格式


输出共 $q$ 行，每行一个整数，表示结点 $x_i, y_i$ 之间的距离。
## 样例

### 样例输入 #1
```
3
1 3
2 5
4 8
```
### 样例输出 #1
```
1
2
1
```
### 样例输入 #2
```
1
120 650
```
### 样例输出 #2
```
9
```
## 提示


对于 $60\%$ 的测试点，保证 $1 \leq x_i, y_i \leq 1000$。

对于所有测试点，保证 $1 \leq q \leq 1000$，$1 \leq x_i, y_i \leq 10^9$。


---

---
title: "[GCJ 2014 #1C] Part Elf"
layout: "post"
diff: 普及/提高-
pid: P13253
tag: ['数学', '2014', '数论', 'Google Code Jam']
---
# [GCJ 2014 #1C] Part Elf
## 题目描述

Vida says she's part Elf: that at least one of her ancestors was an Elf. But she doesn't know if it was a parent (1 generation ago), a grandparent (2 generations ago), or someone from even more generations ago. Help her out!

Being part Elf works the way you probably expect. People who are Elves, Humans and part-Elves are all created in the same way: two parents get together and have a baby. If one parent is $\frac{A}{B}$ Elf, and the other parent is $\frac{C}{D}$ Elf, then their baby will be $\frac{(A/B + C/D)}{2}$ Elf. For example, if someone who is $\frac{0}{1}$ Elf and someone who is $\frac{1}{2}$ Elf have a baby, that baby will be $\frac{1}{4}$ Elf.

Vida is certain about one thing: 40 generations ago, she had $2^{40}$ different ancestors, and each one of them was $\frac{1}{1}$ Elf or $\frac{0}{1}$ Elf.

Vida says she's $\frac{P}{Q}$ Elf. Tell her what is the minimum number of generations ago that there could have been a $\frac{1}{1}$ Elf in her family. If it is not possible for her to be $\frac{P}{Q}$ Elf, tell her that she must be wrong!
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow. Each contains a fraction of the form $\frac{P}{Q}$, where $P$ and $Q$ are integers.
## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from 1) and $y$ is the minimum number of generations ago a $\frac{1}{1}$ Elf in her family could have been if she is $\frac{P}{Q}$ Elf. If it's impossible that Vida could be $\frac{P}{Q}$ Elf, $y$ should be the string "impossible" (without the quotes).
## 样例

### 样例输入 #1
```
5
1/2
3/4
1/4
2/23
123/31488
```
### 样例输出 #1
```
Case #1: 1
Case #2: 1
Case #3: 2
Case #4: impossible
Case #5: 8
```
## 提示

Note that the fifth sample case does not meet the limits for the Small input. Even if you don't solve it correctly, you might still have solved the Small input correctly.

**Explanation of sample cases**

In the first sample case, Vida could have a $\frac{1}{1}$ Elf parent and a $\frac{0}{1}$ Elf parent. That means she could have had a $\frac{1}{1}$ Elf one generation ago, so the answer is $1$.

In the second sample case, Vida could have had a $\frac{1}{1}$ Elf parent and a $\frac{1}{2}$ Elf parent. That means she could have had a $\frac{1}{1}$ Elf one generation ago, so the answer is $1$.

In the third sample case, Vida could have had a $\frac{0}{1}$ Elf parent and a $\frac{1}{2}$ Elf parent. The $\frac{1}{2}$ Elf parent could have had a $\frac{1}{1}$ Elf parent and a $\frac{0}{1}$ Elf parent. That means she could have had a $\frac{1}{1}$ Elf two generations ago, so the answer is $2$.

In the fourth sample case, it's impossible to be exactly $\frac{2}{23}$ Elf if your ancestors 40 generations ago were all $\frac{0}{1}$ Elf or $\frac{1}{1}$ Elf.

**Note**

Yes, Vida has a lot of ancestors. If that is the part of the problem that seems the most unrealistic to you, please re-read the part about Elves.

**Limits**

- $1 \leq T \leq 100$.

**Small dataset(8 Pts)**

- Time limit: ~~60~~ 3 seconds.
- $1 \leq P < Q \leq 1000$.
- $P$ and $Q$ have no common factors. That means $P/Q$ is a fraction in lowest terms.

**Large dataset(12 Pts)**

- Time limit: ~~120~~ 5 seconds.
- $1 \leq P < Q \leq 10^{12}$.
- $P$ and $Q$ may have common factors. $P/Q$ is not guaranteed to be a fraction in lowest terms.



---

---
title: "[GCJ 2011 #1A] FreeCell Statistics"
layout: "post"
diff: 普及/提高-
pid: P13365
tag: ['数学', '2011', '数论', 'Google Code Jam']
---
# [GCJ 2011 #1A] FreeCell Statistics
## 题目描述

I played $D$ ($D > 0$) games of FreeCell today. Each game of FreeCell ends in one of two ways -- I either win, or I lose. I've been playing for many years, and have so far played $G$ games in total (obviously, $G \geq D$).

At the end of the day, I look at the game statistics to see how well I have played. It turns out that I have won exactly $P_D$ percent of the $D$ games today, and exactly $P_G$ percent of $G$ total games I had ever played. Miraculously, there is no rounding necessary -- both percentages are exact! Unfortunately, I don't remember the exact number of games that I have played today ($D$), or the exact number of games that I have played in total ($G$). I do know that I could not have played more than $N$ games today ($D \leq N$).

Are the percentages displayed possible, or is the game statistics calculator broken?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow. Each line contains 3 integers -- $N$, $P_D$ and $P_G$.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is either "Possible" or "Broken".
## 样例

### 样例输入 #1
```
3
1 100 50
10 10 100
9 80 56
```
### 样例输出 #1
```
Case #1: Possible
Case #2: Broken
Case #3: Possible
```
## 提示

**Sample Explanation**

In Case #3, I could have played $5$ games today ($D = 5$) and $25$ games in total ($G = 25$), and won $4$ games today ($80\%$ of $5$) and $14$ games in total ($56\%$ of $25$).

**Limits**

- $0 \leq P_D \leq 100$;
- $0 \leq P_G \leq 100$.

**Small dataset (6 Pts, Test set 1 - Visible)**

- $1 \leq T \leq 100$;
- $1 \leq N \leq 10$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (14 Pts, Test set 2 - Hidden)**

- $1 \leq T \leq 2000$;
- $1 \leq N \leq 10^{15}$.
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[USACO22FEB] Sleeping in Class B"
layout: "post"
diff: 普及/提高-
pid: P8183
tag: ['数学', 'USACO', '2022', '数论']
---
# [USACO22FEB] Sleeping in Class B
## 题目描述

Bessie the cow was excited to recently return to in-person learning! Unfortunately, her instructor, Farmer John, is a very boring lecturer, and so she ends up falling asleep in class often.
Farmer John has noticed that Bessie has not been paying attention in class. He has asked another student in class, Elsie, to keep track of the number of times Bessie falls asleep in a given class. There are $N$ class periods $(1\le N\le 10^5)$, and Elsie logs that Bessie fell asleep $a_i$ times $(0\le a_i\le 10^6)$ in the $i$-th class period. The total number of times Bessie fell asleep across all class periods is at most $10^6$.

Elsie, feeling very competitive with Bessie, wants to make Farmer John feel like Bessie is consistently falling asleep the same number of times in every class -- making it appear that the issue is entirely Bessie's fault, with no dependence on Farmer John's sometimes-boring lectures. The only way Elsie may modify the log is by combining two adjacent class periods. For example, if $a=[1,2,3,4,5]$, then if Elsie combines the second and third class periods the log will become $[1,5,4,5]$.

Help Elsie compute the minimum number of modifications to the log that she needs to make so that she can make all the numbers in the log equal.
## 输入格式

Each input will contain $T$ $(1\le T\le 10)$ test cases that should be solved independently.

The first line contains $T$, the number of test cases to be solved. The $T$ test cases follow, each described by a pair of lines. The first line of each pair contains $N$, and the second contains $a_1,a_2,\ldots,a_N$. 

It is guaranteed that within each test case, the sum of all values in $a$ is at most $10^6$. It is also guaranteed that the sum of $N$ over all test cases is at most $10^5$.
## 输出格式

Please write $T$ lines of output, giving the minimum number of modifications Elsie could perform to make all the log entries equal for each case.
## 样例

### 样例输入 #1
```
3
6
1 2 3 1 1 1
3
2 2 3
5
0 0 0 0 0
```
### 样例输出 #1
```
3
2
0
```
## 提示

【样例解释】

For the first test case in this example, Elsie can change her log to consist solely of 3s with 3 modifications.
```
   1 2 3 1 1 1
-> 3 3 1 1 1
-> 3 3 2 1
-> 3 3 3
```
For the second test case, Elsie can change her log to 7 with 2 modifications.
```
   2 2 3
-> 2 5
-> 7
```
For the last test case, Elsie doesn’t need to perform any operations; the log already consists of equal entries.
## 题目翻译

### 题目描述

奶牛 Bessie 最近很高兴能够重返线下课堂！不幸的是，她的老师 Farmer John 讲课非常无聊，因此她经常在课堂上睡着。  
Farmer John 注意到 Bessie 在课堂上没有专心听讲。他让班上的另一位学生 Elsie 记录 Bessie 在每节课上睡着的次数。总共有 $N$ 节课（$1 \leq N \leq 10^5$），Elsie 记录到 Bessie 在第 $i$ 节课上睡着了 $a_i$ 次（$0 \leq a_i \leq 10^6$）。所有课程中 Bessie 睡着的总次数不超过 $10^6$。

Elsie 对 Bessie 感到非常竞争，她希望让 Farmer John 觉得 Bessie 在每节课上睡着的次数是一致的——让问题看起来完全是 Bessie 的错，而与 Farmer John 有时无聊的讲课无关。Elsie 修改记录的唯一方式是将两节相邻的课合并。例如，如果 $a = [1,2,3,4,5]$，那么如果 Elsie 合并第二和第三节课，记录将变为 $[1,5,4,5]$。

请帮助 Elsie 计算她需要对记录进行的最少修改次数，以使记录中的所有数字相等。

### 输入格式

每个输入包含 $T$（$1 \leq T \leq 10$）个需要独立解决的测试用例。

第一行包含 $T$，表示测试用例的数量。接下来的 $T$ 组测试用例，每组由两行描述。每组的第一行包含 $N$，第二行包含 $a_1, a_2, \ldots, a_N$。

保证每个测试用例中，$a$ 的所有值之和不超过 $10^6$。同时，所有测试用例的 $N$ 之和不超过 $10^5$。

### 输出格式

请输出 $T$ 行，每行表示 Elsie 为使记录中的所有数字相等所需的最少修改次数。

### 提示

对于第一个测试用例，Elsie 可以通过 3 次修改将记录改为全为 $3$：
```
   1 2 3 1 1 1
-> 3 3 1 1 1
-> 3 3 2 1
-> 3 3 3
```

对于第二个测试用例，Elsie 可以通过 2 次修改将记录改为全为 $7$：
```
   2 2 3
-> 2 5
-> 7
```

对于最后一个测试用例，Elsie 不需要进行任何操作，因为记录已经由相同的数字组成。


---

---
title: "「Wdoi-5」樱点收集"
layout: "post"
diff: 普及/提高-
pid: P8226
tag: ['模拟', '数论', '洛谷原创', '洛谷月赛']
---
# 「Wdoi-5」樱点收集
## 题目背景

119 季 5 月，明明本应是樱花盛开的春天，幻想乡却依然下着大雪。异变的主谋**西行寺幽幽子**在古书上看到，只要使妖樱西行妖满开便会有什么人复活，便出于兴趣命令妖梦收集幻想乡中的春度，一手策划成了这场异变。在收集春度的过程中散落的能量在西行妖的影响下化为**樱点**，散落在幻想乡各处。

出发解决**春雪异变**的灵梦将前往冥界旅途划分为了若干段，每一段都可以收集到一定的樱点。收集齐一定程度的樱点，就会立即开出樱之结界。开出樱之结界后可以短暂地屏蔽一切攻击，并且获得相应的增益。

但是樱之结界何时开放仅由樱点的收集情况所决定，她不得不对樱点进行「规划」。通过某些途径规避某一段路上樱点的收集，借此使得在将来的某几段路程里，灵梦得以恰好在该段的末尾开放樱之结界。  

但是现实往往不尽人意。也就是说，可能有某些要求无法达成。灵梦希望找出一个方案，使得她可以达成的要求最多。灵梦委托八云紫帮忙决策，于是这个重任就被一条懒紫交给了式神八云蓝。尽管八云蓝擅长计算，但是八云紫睡觉去了没有给她编程，因而现在这个任务就落到了你的手上。
## 题目描述

灵梦当前拥有的樱点可以使用一个**变量** $c$ 存储，初始时为 $0$。当樱点在某个瞬间**恰好**变为了 $k$，灵梦就会展开樱之结界，同时 $c$ 变为 $0$。

现在她把路程**依次**划分为了 $n$ 个关卡，其中第 $i$ 关上，灵梦一共可以获得 $a_i$ 点樱点。这些樱点是均匀分布在这关的路程上的。也就是说，随着这段路程的进行，灵梦的樱点个数会依次增加，每次增加 $1$ 个单位（$c\gets c+1$），恰好在这段路程结束的瞬间会收集到这关中第 $a_i$ 点樱点。

![](https://cdn.luogu.com.cn/upload/image_hosting/3yuiywt0.png)

**【需要注意的是，这只是图示参考，不满足实际的数据限制。】**

在这个例子里，灵梦将路径划分为了四个关卡。这四个关卡的樱点个数分别为 $2,0,3,1$。

灵梦提出了 $m$ 个要求。第 $i$ 个要求 $b_i$ 表示灵梦希望在第 $b_i$ 段路程结束的瞬间，**恰好**展开樱之结界（如果在这段路程的中途展开但是结束的瞬间没有展开，那就不算达成了要求）。

灵梦可以选择在某个关卡开头放 bomb，**跳过**整个关卡的樱点收集。这样的机会**有且仅有**一次（当然，灵梦可以选择不使用 bomb）。

现在需要求出，在最优的选择下，灵梦**最多**可以达成多少个要求。
## 输入格式

- 第一行共有三个整数 $n,m,k$，分别表示关卡数、要求个数，以及常量 $k$。
- 第二行 $m$ 个整数 $b_1,b_2,\cdots b_m$，描述了灵梦的 $m$ 个要求。**保证 $\bm{b_i}$ 单调递增**。
- 第三行 $n$ 个整数 $a_1,a_2,\cdots a_n$，描述了第 $i$ 关可以获得的樱点个数。
## 输出格式

- 共一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
4 3 2
1 3 4
1 1 2 1
```
### 样例输出 #1
```
1
```
## 提示

样例 $2$ 见下发的附件 $\textbf{\textit{sukura2.in/sakura2.ans}}$。该样例约束与测试点 $1\sim 8$ 一致。  
样例 $3$ 见下发的附件 $\textbf{\textit{sukura3.in/sakura3.ans}}$。该样例约束与测试点 $9\sim 14$ 一致。  
样例 $4$ 见下发的附件 $\textbf{\textit{sukura4.in/sakura4.ans}}$。该样例约束与测试点 $15\sim 20$ 一致。

#### 样例 1 解释

- 在不使用 bomb 时，灵梦会在第 $2$、$3$ 关开出樱之结界，其中第 $3$ 关在统计序列中，满足要求数为 $1$。
- 在第 $1$ 关使用 bomb，灵梦会在第 $4$ 关开出樱之结界，且第 $4$ 关在统计序列中，满足要求数为 $1$。
- 在第 $2$ 关使用 bomb，灵梦会在第 $4$ 关开出樱之结界，且第 $4$ 关在统计序列中，满足要求数为 $1$。
- 在第 $3$ 关使用 bomb，灵梦会在第 $2$ 关开出樱之结界，且第 $2$ 关不在统计序列中，满足要求数为 $0$。
- 在第 $4$ 关使用 bomb，灵梦会在第 $2$、$3$ 关开出樱之结界，其中第 $3$ 关在序列中，满足要求数为 $1$。

#### 数据范围及约定

本题共有 $20$ 个测试点，每个测试点 $5$ 分。最终分数为所有测试点分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \bm{n\le } & \bm{k\le} \cr\hline
1\sim 8 & 200 & 10^3 \cr\hline
9\sim 14 & 2\times 10^3 & 10^5 \cr\hline
15\sim 20 & 3\times 10^5 & 10^6 \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，保证 $1\le m\le n\le 3\times 10^5$，$1\le k\le 10^6$，$1\le a_i\le 10^9$，$1 \le b_i \le n$，$b$ 序列递增。


---

---
title: "[蓝桥杯 2016 省 AB] 最大比例"
layout: "post"
diff: 普及/提高-
pid: P8636
tag: ['2016', '数论', '蓝桥杯省赛']
---
# [蓝桥杯 2016 省 AB] 最大比例
## 题目描述

X 星球的某个大奖赛设了 $M$ 级奖励。每个级别的奖金是一个正整数。

并且，相邻的两个级别间的比例是个固定值。

也就是说：所有级别的奖金数构成了一个等比数列。比如：

$$16,24,36,54$$

其等比值为：$3/2$。

现在，我们随机调查了一些获奖者的奖金数。

请你据此推算可能的最大的等比值。
## 输入格式

第一行为数字 $N(0<N<100)$，表示接下的一行包含 $N$ 个正整数。

第二行 $N$ 个正整数 $X_i(X_i<10^{12})$，用空格分开。每个整数表示调查到的某人的奖金数额。

## 输出格式

一个形如 $A/B$ 的分数，要求 $A$、$B$ 互质。表示可能的最大比例系数。

测试数据保证了输入格式正确，并且最大比例是存在的。
## 样例

### 样例输入 #1
```
3
1250 200 32
```
### 样例输出 #1
```
25/4
```
### 样例输入 #2
```
4
3125 32 32 200
```
### 样例输出 #2
```
5/2
```
### 样例输入 #3
```
3
549755813888 524288 2
```
### 样例输出 #3
```
4/1
```
## 提示

时限 3 秒, 256M。蓝桥杯 2016 年第七届省赛

蓝桥杯 2016 年省赛 A 组 J 题（B 组 J 题）。


---

---
title: "[蓝桥杯 2017 省 AB] 包子凑数"
layout: "post"
diff: 普及/提高-
pid: P8646
tag: ['2017', '数论', '背包 DP', '蓝桥杯省赛']
---
# [蓝桥杯 2017 省 AB] 包子凑数
## 题目描述

小明几乎每天早晨都会在一家包子铺吃早餐。他发现这家包子铺有 $N$ 种蒸笼，其中第 $i$ 种蒸笼恰好能放 $A_i$ 个包子。每种蒸笼都有非常多笼，可以认为是无限笼。

每当有顾客想买 $X$ 个包子，卖包子的大叔就会迅速选出若干笼包子来，使得这若干笼中恰好一共有 $X$ 个包子。比如一共有 $3$ 种蒸笼，分别能放 $3$ 、 $4$ 和 $5$ 个包子。当顾客想买 $11$ 个包子时，大叔就会选 $2$ 笼 $3$ 个的再加 $1$ 笼 $5$ 个的（也可能选出 $1$ 笼 $3$ 个的再加 $2$ 笼 $4$ 个的）。

当然有时包子大叔无论如何也凑不出顾客想买的数量。比如一共有 $3$ 种蒸笼，分别能放 $4$ 、 $5$ 和 $6$ 个包子。而顾客想买 $7$ 个包子时，大叔就凑不出来了。

小明想知道一共有多少种数目是包子大叔凑不出来的。
## 输入格式


第一行包含一个整数 $N$。$(1 \le N \le 100)$。

以下 $N$ 行每行包含一个整数 $A_i$。$(1 \le A_i \le 100)$。
## 输出格式

一个整数代表答案。如果凑不出的数目有无限多个，输出 `INF`。
## 样例

### 样例输入 #1
```
2  
4  
5  
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
2  
4  
6   
```
### 样例输出 #2
```
INF
```
## 提示

对于样例 $1$，凑不出的数目包括：$1,2,3,6,7,11$。

对于样例 $2$，所有奇数都凑不出来，所以有无限多个。

蓝桥杯 2017 省赛 A 组 H 题。


---

---
title: "[蓝桥杯 2022 国 B] 齿轮"
layout: "post"
diff: 普及/提高-
pid: P8799
tag: ['2022', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2022 国 B] 齿轮
## 题目描述

这天，小明在组装齿轮。

他一共有 $n$ 个齿轮，第 $i$ 个齿轮的半径为 $r_{i}$, 他需要把这 $n$ 个齿轮按一定顺序从左到右组装起来，这样最左边的齿轮转起来之后，可以传递到最右边的齿轮，并且这些齿轮能够起到提升或者降低转速（角速度）的作用。

![](https://luogu.oss-cn-hangzhou.aliyuncs.com/upload/vjudge_pic/lanqiao/2022_09_29_8ee8d95d6d0319bca20dg-17.jpg)

小明看着这些齿轮，突然有 $Q$ 个疑问: 能否按一定顺序组装这些齿轮使得最右边的齿轮的转速是最左边的齿轮的 $q_{i}$ 倍?

## 输入格式

输入共 $Q+2$ 行，第一行为两个正整数 $n, Q$, 表示齿轮数量和询问数量。

第二行为 $n$ 个正整数 $r_{1}, r_{2}, \ldots, r_{n}$，表示每个齿轮的半径。

后面 $Q$ 行，每行一个正整数 $q_{i}$ 表示询问。

## 输出格式

$Q$ 行，对于每个询问，如果存在至少一种组装方案满足条件，输出 `YES`, 否则输出 `NO`。
## 样例

### 样例输入 #1
```
5 3
4 2 3 3 1
2
4
6
```
### 样例输出 #1
```
YES
YES
NO
```
## 提示

**【样例说明】**

询问 $1$ 方案之一：`23341`。

询问 $2$ 方案之一：`42331`。

询问 $3$ 没有方案。

**【评测用例规模与约定】**

对于 $15 \%$ 的数据，保证 $n, Q \leq 100$;

对于 $30 \%$ 的数据，保证 $n, Q \leq 2000$;

对于 $100 \%$ 的数据，保证 $n\ge 2,n, Q \leq 2 \times 10^{5} ; a_{i}, q_{i} \leq 2 \times 10^{5}$。

蓝桥杯 2022 国赛 B 组 I 题。


---

---
title: "[蓝桥杯 2022 国 C] 取模"
layout: "post"
diff: 普及/提高-
pid: P8807
tag: ['2022', '数论', '枚举', '鸽笼原理', '蓝桥杯国赛']
---
# [蓝桥杯 2022 国 C] 取模
## 题目描述

给定 $n, m$，问是否存在两个不同的数 $x,y$ 使得 $1 \le x < y \le m$ 且 $n \bmod x = n \bmod ⁡y$。
## 输入格式

输入包含多组独立的询问。

第一行包含一个整数 $T$ 表示询问的组数。

接下来 $T$ 行每行包含两个整数 $n,m$，用一个空格分隔，表示一组询问。
## 输出格式

  输出 $T$ 行，每行依次对应一组询问的结果。如果存在，输出单词 `Yes`；如果不存在，输出单词 `No`。
## 样例

### 样例输入 #1
```
3
1 2
5 2
999 99
```
### 样例输出 #1
```
No
No
Yes
```
## 提示

对于 $20\%$ 的评测用例，$T \le 100$，$n, m \le 1000$；

对于 $50\%$ 的评测用例，$T \le 10000$，$n, m \le 10^5$；

对于所有评测用例，$1\le T \le 10^5$，$1\le n\le 10^9$，$2\le m \le 10^9$。

蓝桥杯 2022 国赛 C 组 C 题。


---

