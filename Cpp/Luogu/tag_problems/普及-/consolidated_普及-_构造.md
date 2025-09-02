---
title: "[洛谷 202406GESP 模拟 四级] 锣鼓工厂"
layout: "post"
diff: 普及-
pid: B3999
tag: ['贪心', 'Special Judge', '排序', '构造']
---
# [洛谷 202406GESP 模拟 四级] 锣鼓工厂
## 题目描述

小苏同学是锣鼓工厂的厂长。锣鼓工厂共有 $n$ 台机器，第 $i$ 台机器工作一天可以生产 $a_i$ 个锣鼓。因为环保、资金和保养问题，在接下来的 $n$ 天里，每天只能使用一台机器进行生产，每台机器在 $n$ 天里只能被使用一次。

同时，小苏接到了 $n$ 笔订单，第 $i$ 笔订单要求交付 $b_i$ 个锣鼓。小苏同学想知道，是否存在一种合理安排机器使用和交付订单的顺序，使得她在接下来的 $n$ 天里，每天都能交付一个订单？
## 输入格式

**本题单个测试点内有多组测试数据**。第一行是一个整数 $T$（$1 \leq T \leq 10$），表示数据组数。对每组数据，按如下格式输入：

每组数据第一行是一个整数 $n$（$1 \leq n \leq 10^3$），表示机器数和订单数。  
第二行有 $n$ 个整数 $a_1, a_2, \dots a_n$（$1 \leq a_i \leq 10^4$），依次表示每台机器工作一天可以生产的锣鼓数量。  
第三行有 $n$ 个整数 $b_1, b_2, \dots b_n$（$1 \leq b_i \leq 10^4$），依次表示每个订单要求交付的锣鼓数量。  
## 输出格式

对每组数据，输出一行或三行：

- 如果不存在一种方案使得她在接下来的 $n$ 天里，每天都能交付一个订单，输出一行一个字符串 `No`。
- 否则输出三行：
  + 第一行输出 `Yes`。
  + 第二行输出 $n$ 个整数，$x_1, x_2, \dots x_n$，其中 $x_i$ 表示在第 $i$ 天使用的机器的**编号**。
  + 第三行输出 $n$ 个整数，$y_1, y_2, \dots y_n$，其中 $y_i$ 表示在第 $i$ 天交付的订单的**编号**。
  
$x_i$ 和 $y_i$ 必须是 $1 \sim n$ 范围内的整数，且每个数字在 $x_i, y_i$ 中**恰好**出现一次。

对于输出 `Yes` 的情况，可能有多种合理的方案，你可以**输出任意一种**。只要你输出的方案是正确且合理的即可得分。
## 样例

### 样例输入 #1
```
1
3
3 2 1
1 2 3
```
### 样例输出 #1
```
Yes
1 2 3
3 2 1
```
### 样例输入 #2
```
2
5
1 2 3 4 5
2 3 4 5 6
3
10 20 30
15 15 15
```
### 样例输出 #2
```
No
Yes
2 1 3
1 2 3
```
## 提示

### 样例 1 解释

- 在第一天使用编号为 $1$ 的机器生产了 $3$ 个锣鼓，交付编号为 $3$ 的订单 $3$ 个锣鼓。
- 在第二天使用编号为 $2$ 的机器生产了 $2$ 个锣鼓，交付编号为 $1$ 的订单 $2$ 个锣鼓。
- 在第三天使用编号为 $3$ 的机器生产了 $1$ 个锣鼓，交付编号为 $1$ 的订单 $1$ 个锣鼓。


### 样例 2 解释

我们解释第二组数据：

- 在第一天使用编号为 $2$ 的机器，生产了 $20$ 个锣鼓。交付编号为 $1$ 的订单 $15$ 个，剩余 $5$ 个；
- 在第二天使用编号为 $1$ 的机器，生产了 $10$ 个锣鼓，加上上一天的 $5$ 个，共 $15$ 个锣鼓，交付编号为 $2$ 的订单 $15$ 个，剩余 $0$ 个。
- 在第三天使用编号为 $3$ 的机器，生产了 $30$ 个锣鼓，共 $30$ 个锣鼓，交付编号为 $2$ 的订单 $15$ 个，剩余 $15$ 个。

### 提示

样例输出不唯一，仅供参考。


---

---
title: "[BCSP-X 2024 12 月初中组] 稳定原子"
layout: "post"
diff: 普及-
pid: B4162
tag: ['2024', '北京', 'Special Judge', '构造', 'BCSP-X']
---
# [BCSP-X 2024 12 月初中组] 稳定原子
## 题目背景

小 $\tau$ 在学结构化学。
## 题目描述

小 $\tau$ 认为一个大小为 $n$ 的原子可以抽象为一个 $n \times n$ 的矩阵，每个位置上要么有电子，要么没有电子。

并且一个原子是稳定的，当且仅当它的矩阵中的每一个位置均满足上下左右相邻的电子数恰好等于 $2$。

小 $\tau$ 想问问你，在他上述理论体系下，是否存在大小为 $n$ 的稳定原子，如果存在，输出 Yes 并给出一种稳定原子的电子排布方案；如果不存在，输出 No。

由于小 $\tau$ 非常好奇，所以他会问 $T$ 次。
## 输入格式

第一行一个正整数 $T$ 表示询问次数。

后面 $T$ 行，第 $i$ 行一个正整数 $n$，表示第 $i$ 次询问的原子大小。
## 输出格式

对于每组询问，第一行输出 Yes/No 表示是否存在稳定原子。

如果是 Yes，后面输出 $n$ 行 $n$ 列的 $0/1$ 矩阵，$1$ 表示有电子，$0$ 表示没有电子。
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
No
Yes
1 1
1 1
No
```
## 提示

对于 $100\%$ 的数据，$T=10$，$1\leq n\leq 1000$。

**声明：本题所述内容并非化学事实。**


---

---
title: "[GXPC-S 2025] 序列 / sequence"
layout: "post"
diff: 普及-
pid: B4371
tag: ['贪心', '2025', '广西', '构造']
---
# [GXPC-S 2025] 序列 / sequence
## 题目背景

题目来源：2025 年广西中小学生程序设计挑战赛复赛（进阶组[试题](https://mp.weixin.qq.com/s?__biz=MzI3NDM3MzcwNQ==&mid=2247490166&idx=5&sn=e7ba7e3bc8126027b9abd662518c208b&chksm=ea9c06dd4d18206ed9d88124cc78b947298df2555889e98620204c2ea1471f58c135c00f99fb&mpshare=1&scene=23&srcid=0724dNJdhMxpUHag1dqkhiqL&sharer_shareinfo=7e47197d6e5c044ae705613db988029c&sharer_shareinfo_first=7e47197d6e5c044ae705613db988029c#rd)）。
## 题目描述

求知的隐士将知识传授给懵懂无知的凡人，隐士每年提出 $n$ 个正确的观点和 $m$ 个错误的观点，且 $n \leq m$。其中正确的观点用数字 “1” 表示，错误的观点用数字 “0” 表示。例如，如果他提出了 3 个正确观点和 2 个错误观点，序列可能是 “11100” 或 “10101”。人们按序列的顺序讨论这些问题。

隐士定义，一条观点序列是好的：当且仅当序列中错误观点数量与正确观点数量之差为 $K$。也就是说，$K = m - n$。隐士同时注意到：当某个观点序列的所有子段中，$K$ 的最大值恰好是 $k$ 时，人们获得知识的效果最好可理解。现在隐士希望小景编写一个程序，使他不必手造观点序列。



序列需恰好包含 $n$ 个 1 和 $m$ 个 0，并且所有子段的 $K$ 的最大值恰为 $k$。保证输出的数一定存在符合要求的序列。

形式化地，设某序列 $s$ 包含 $n_s$ 个 1 和 $m_s$ 个 0，则 $K$ 为：

$$
K = t_s = m_s - n_s 
$$

所有子段构成集合 $\{ s_1, s_2, \dots, s_n \}$，此时：

$$
k = \max( t_{s_1}, t_{s_2}, \dots, t_{s_n} )
$$


---


子段：原序列中一段连续的非空子序列。例如，假定原序列为 $\texttt{abcde}$，其子段有 $\texttt{a}$，$\texttt{c}$，$\texttt{de}$，$\texttt{abc}$，$\texttt{bcde}$，$\texttt{abcde}$ 等。

字典序：对于数字，不同排列的字典序是从左到右依次对应的数字的先后决定的。例如对于 4 个数字的排列 1234 和 1243，排列 1234 在前（称为字典序更小），排列 1243 在后（称为字典序更大）。
## 输入格式

一行 3 个正整数 $n, m, k$，表示正确观点个数、错误观点个数和最优的 $K$。
## 输出格式

输出满足条件且字典序最小的 01 字符串。
## 样例

### 样例输入 #1
```
2 3 2
```
### 样例输出 #1
```
00101
```
### 样例输入 #2
```
5 10 8
```
### 样例输出 #2
```
000000001010111
```
## 提示

#### 样例解释

- 对于样例 1 的解释：

取前 2 位（$\texttt{00}$），可以取得所有子段的 $K$ 的最大值，恰为 $2$，且字典序最小。


- 对于样例 2 的解释：

取前 8 位，可以取得所有子段的 $K$ 的最大值，恰为 8，且字典序最小。

#### 数据范围

- 对于 $10\%$ 的数据：$1 \leq n, m \leq 50$；
- 对于 $60\%$ 的数据：$1 \leq n, m \leq 10^4$；


对于 $100\%$ 的数据，保证：

- $m - n \leq k \leq \max(m, n)$，$n + m \geq 1$；
- $1 \leq n, m \leq 2 \times 10^5$，且 $n \leq m$。


---

---
title: "「Cfz Round 2」How to Prove"
layout: "post"
diff: 普及-
pid: P10306
tag: ['数学', '洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 「Cfz Round 2」How to Prove
## 题目描述

给定一个正整数 $n$。

我们定义，对于一个集合 $S$，$\Omega(S)$ 为集合 $S$ 的所有的 **非空子集的元素和** 所组成的集合。

形式化地，$\Omega(S)=\{x\mid x=\sum\limits_{i\in T}i,T\subseteq S,T\neq \varnothing\}$。

例如，当 $S=\{2,0,-3,5\}$ 时，$\Omega(S)=\{-3,-1,0,2,4,5,7\}$。

你需要构造一个大小为 $n$ 的集合 $S$，满足：

- 集合 $S$ 中的所有元素均为不大于 $10^9$ 且不小于 $-10^9$ 的整数；
- $|\Omega(S)|$ 最小，即 $\Omega(S)$ 所包含的元素个数最少。
## 输入格式

**本题有多组测试数据。**

第一行输入一个整数 $T$，表示测试数据组数。

接下来依次输入每组测试数据。对于每组测试数据，输入一行一个正整数 $n$。
## 输出格式

对于每组测试数据，输出一行 $n$ 个整数，表示你构造的集合 $S$ 中的所有元素。

**所有满足要求的输出均可通过。**
## 样例

### 样例输入 #1
```
3
1
2
4
```
### 样例输出 #1
```
3
0 5
2 0 -2 4
```
## 提示

#### 「样例解释 #1」

对于第 $1$ 组数据，$S=\{3\}$，$\Omega(S)=\{3\}$。当然，$\{0\}$、$\{-2\}$ 等也为满足条件的集合 $S$。

对于第 $2$ 组数据，$S=\{0,5\}$，$\Omega(S)=\{0,5\}$。

对于第 $3$ 组数据，$S=\{2,0,-2,4\}$，$\Omega(S)=\{-2,0,2,4,6\}$。

可以证明以上构造均满足条件。

#### 「数据范围」

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有数据，$1 \le T \le 100$，$1 \le n \le 10^6$，$\sum n \le 10^6$。

**只有你通过本题的所有测试点，你才能获得本题的分数。**


---

---
title: "【MX-S1-T1】 壁垒"
layout: "post"
diff: 普及-
pid: P10672
tag: ['搜索', 'Special Judge', 'O2优化', '排列组合', '构造', '梦熊比赛']
---
# 【MX-S1-T1】 壁垒
## 题目背景

原题链接：<https://oier.team/problems/S1A>。
## 题目描述

给定一个长度为 $n$ 的仅包含正整数的数列 $a$，保证 $n$ 是偶数。你需要重排 $a$，满足对于 $a$ 的每个长度为偶数的前缀，出现的数字种类数是偶数，或断定这样的重排方式不存在。

如果有多种重排方式满足条件，输出任意一种即可。
## 输入格式

第一行一个正整数 $n$，保证 $n$ 是偶数。

第二行一个 $n$ 个正整数，描述数列 $a$。
## 输出格式

无解时输出 $-1$，否则输出一行 $n$ 个整数，描述重排后的数列 $a$。

本题使用**自定义校验器**检验你的答案是否正确，如果有多种重排方式满足条件，输出任意一种即可。
## 样例

### 样例输入 #1
```
6
2 3 3 4 1 1
```
### 样例输出 #1
```
1 3 3 1 2 4
```
### 样例输入 #2
```
2
1 1
```
### 样例输出 #2
```
-1
```
## 提示

__【样例解释 1】__

$\{1,3\},\{1,3,3,1\},\{1,3,3,1,2,4\}$ 这些集合的数字种类数都是偶数。

__【数据范围】__

__本题使用子任务捆绑测试。__

对于 $100\%$ 的数据，$2\le n\le 10^5$，$1\le a_i\le n$，保证 $n$ 是偶数。

| 子任务编号 | $n\le $ | $a_i\le $ | 分值 |
| ---------- | ------- | --------- | ---- |
| $1$        | $10$    | $n$       | $20$ |
| $2$        | $20$    | $n$       | $20$ |
| $3$        | $10^5$  | $2$       | $20$ |
| $4$        | $10^5$  | $10$      | $20$ |
| $5$        | $10^5$  | $n$       | $20$ |


---

---
title: "[NOISG 2019 Prelim] Lost Array"
layout: "post"
diff: 普及-
pid: P10733
tag: ['2019', 'Special Judge', '构造', 'NOISG（新加坡）']
---
# [NOISG 2019 Prelim] Lost Array
## 题目背景

翻译自 [NOISG2019 Prelim B.Lost Array](https://github.com/noisg/sg_noi_archive/blob/master/2019_prelim/)。

**本题已启用 Special Judge，满足题目条件的任何答案都将视为正确。**
## 题目描述

给定 $M$ 组形如 $\min (X_{A_i},X_{B_i})=C_i$ 的关系式，请构造一个长度为 $N$ 的数组 $X$，使得数组中的每个数字在 $1$ 到 $10^9$ 之间，并且该数组满足所有的关系式。

题目保证数组存在。
## 输入格式

第一行两个整数 $N,M$。

接下来 $M$ 行，每行三个数字 $A_i,B_i,C_i$。
## 输出格式

共一行 $N$ 个整数，代表你构造的数组 $X$。
## 样例

### 样例输入 #1
```
2 1
2 1 7
```
### 样例输出 #1
```
9 7
```
### 样例输入 #2
```
5 6
1 2 1
3 5 4
1 5 3
1 3 3
2 3 1
2 4 1
```
### 样例输出 #2
```
3 1 4 1 5
```
### 样例输入 #3
```
2 5
1 2 1
2 1 1
1 2 1
1 2 1
2 1 1
```
### 样例输出 #3
```
1 114514
```
### 样例输入 #4
```
5 1
1 2 123
```
### 样例输出 #4
```
123 1000000000 3 4 26311337
```
## 提示

### 【样例 #1 解释】
显然，$\min (X_2,X_1) = \min (9,7) =7$，满足题目条件。
### 【样例 #3 解释】
原题的题面没有此样例，但测试数据有。

第一个限制为 $\min (X_1,X_2) =1$，所有的条件实际上和这个限制一样。
### 【样例 #4 解释】
唯一的限制为 $\min (X_1,X_2) =123$，其余的数字可以是介于 $1$ 到 $10^9$ 之间的任何数字。
### 【数据范围】
| $\text{Subtask}$ | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $0$ | $0$ | 样例 |
| $1$ | $5$ | $N=2,M=1$ |
| $2$ | $6$ | $M\leq 3$ |
| $3$ | $20$ | $N,M\leq 1000$ |
| $4$ | $21$ | $C_i \leq 10,N \leq 5$ |
| $5$ | $48$ | 无 |

对于 $100\%$ 的数据：
- $1 \leq N,M \leq 10^5$
- $1 \leq A_i ,B_i \leq N$
- $A_i \neq B_i$
- $1 \leq C_i \leq 10^9$


---

---
title: "【MX-J1-T2】『FLA - III』Ilumina"
layout: "post"
diff: 普及-
pid: P10782
tag: ['数学', '二分', 'Special Judge', 'O2优化', '构造', '梦熊比赛']
---
# 【MX-J1-T2】『FLA - III』Ilumina
## 题目背景

原题链接：<https://oier.team/problems/J1B>。
## 题目描述

定义 $\lfloor X \rfloor$ 为最大的小于等于 $X$ 的整数，例如 $\lfloor 1.99 \rfloor = 1,\lfloor 7 \rfloor = 7$。

有五个正整数 $n,m,a,b,c$，已知 $b=\left\lfloor \frac{a}{n} \right\rfloor , c=\left\lfloor \frac{b}{m} \right\rfloor$。

给定 $a$ 和 $c$ 的值，求出一个合法的 $b$ 的值，或者报告不存在合法的 $b$ 的值。

**本题使用自定义校验器，如果存在多个合法的 $b$ 的值，输出其中一个即可。**
## 输入格式

**本题有多组测试数据。**

第一行输入一个正整数 $T$，表示测试数据组数。

对于每组测试数据，输入一行两个正整数 $a,c$。
## 输出格式

对于每组数据，输出一行一个整数。如果不存在合法的 $b$ 的值，输出 `-1`；否则输出一个合法的 $b$ 的值。

**本题使用自定义校验器，如果存在多个合法的 $b$ 的值，输出其中一个即可。**
## 样例

### 样例输入 #1
```
4
1 1
7 3
23 8
17 23

```
### 样例输出 #1
```
1
3
-1
-1

```
## 提示

**「样例解释 #1」**

对于第一组测试数据，取 $n=1,m=1$ 时可以得到 $b=1$。

对于第二组测试数据，取 $n=2,m=1$ 时可以得到 $b=3$。

对于第三、第四组测试数据，可以证明不存在合法的 $b$ 的值。

**「数据范围」**

|测试点编号|$a,c \leq$|特殊性质|
|:-:|:-:|:-:|
|$1 \sim 3$|$10$|无|
|$4 \sim 6$|$10^3$|无|
|$7 \sim 8$|$10^{18}$|有|
|$9 \sim 10$|$10^{18}$|无|

特殊性质：保证对于每组给定的 $a,c$ 一定存在合法的 $b$ 的值。

对于 $100\%$ 的数据，$1 \leq T \leq 10^5$，$1 \leq a,c \leq 10^{18}$。

2024 年 7 月 15 日：添加了 7 组 hack 数据置于 Subtask #1。


---

---
title: "[NOIP 2004 普及组] FBI 树"
layout: "post"
diff: 普及-
pid: P1087
tag: ['字符串', '搜索', '树形数据结构', '2004', '递归', 'NOIP 普及组', '构造']
---
# [NOIP 2004 普及组] FBI 树
## 题目描述

我们可以把由 0 和 1 组成的字符串分为三类：全 0 串称为 B 串，全 1 串称为 I 串，既含 0 又含 1 的串则称为 F 串。

FBI 树是一种二叉树，它的结点类型也包括 F 结点，B 结点和 I 结点三种。由一个长度为 $2^N$ 的 01 串 $S$ 可以构造出一棵 FBI 树 $T$，递归的构造方法如下：

1. $T$ 的根结点为 $R$，其类型与串 $S$ 的类型相同；
2. 若串 $S$ 的长度大于 $1$，将串 $S$ 从中间分开，分为等长的左右子串 $S_1$ 和 $S_2$；由左子串 $S_1$ 构造 $R$ 的左子树 $T_1$，由右子串 $S_2$ 构造 $R$ 的右子树 $T_2$。

现在给定一个长度为 $2^N$ 的 01 串，请用上述构造方法构造出一棵 FBI 树，并输出它的后序遍历序列。

## 输入格式

第一行是一个整数 $N(0 \le N \le 10)$，  

第二行是一个长度为 $2^N$ 的 01 串。

## 输出格式

一个字符串，即 FBI 树的后序遍历序列。

## 样例

### 样例输入 #1
```
3
10001011

```
### 样例输出 #1
```
IBFBBBFIBFIIIFF

```
## 提示

对于 $40\%$ 的数据，$N \le 2$；

对于全部的数据，$N \le 10$。


noip2004普及组第3题



---

---
title: "『STA - R7』Odtlcsu"
layout: "post"
diff: 普及-
pid: P11007
tag: ['Special Judge', 'O2优化', '构造']
---
# 『STA - R7』Odtlcsu
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/m38cxgmq.png)
## 题目描述

给定整数 $x,y$，构造一个长度不超过 $10^6$ 的整数序列使得其和为 $x$、平方和为 $y$。保证有解。
## 输入格式

一行两个整数 $x,y$。
## 输出格式

第一行一个非负整数 $n$ 表示你构造的序列长度。需要满足 $n\le 10^6$。

第二行 $n$ 个整数表示你构造出的序列。如果有多解输出任意一种即可。输出的序列所有元素必须是绝对值不大于 $10^6$ 的整数。
## 样例

### 样例输入 #1
```
100 5000
```
### 样例输出 #1
```
2
50 50
```
### 样例输入 #2
```
0 5000
```
### 样例输出 #2
```
2
50 -50
```
## 提示

**本题采用捆绑测试。**

数据范围：
- Subtask 1 (10pts)：$y\le 10$。
- Subtask 2 (40pts)：$x=0$。
- Subtask 3 (50pts)：无特殊限制。

对于全部数据，$0\le |x|,y\le10^6$，保证有解。


---

---
title: "「LAOI-6」Radiation"
layout: "post"
diff: 普及-
pid: P11020
tag: ['贪心', '洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 「LAOI-6」Radiation
## 题目背景

[English statement](https://www.luogu.com.cn/problem/T503655). You must submit your code at the Chinese version of the statement.
## 题目描述

小 T 和 小 U 在一个 $n \times m$ 的初始为空的棋盘上玩游戏。小 T 先在上面摆 $k$ 个石头，然后小 U 会使用宇宙射线毁掉所有石头。但是小 U 的宇宙射线威力有限，只能每次销毁一行或一列的石头。

小 U 不想过多用他的宇宙射线发射器，所以他会按照最优策略销毁石头。反之，小 T 偏偏想让小 U 发射最多的宇宙射线，所以他会摆放石头以做到这一点。问题来了：小 T 不会摆放了。你能够找到一种方法帮助小 T 达到目标吗？
## 输入格式

**本题有多组数据。**

第一行一个整数 $T$。

然后 $T$ 行，每行 $n,m,k$ 三个整数，表示这组数据的游戏设定。
## 输出格式

对于每组数据，输出 $n$ 行 $m$ 列共 $nm$ 个字符，第 $i$ 行第 $j$ 个字符如果为 `S` 那么代表棋盘的第 $i$ 行第 $j$ 列有石头；如果为 `.` 那么代表棋盘的第 $i$ 行第 $j$ 列没石头。

你需要保证每组数据中输出的字符 `S` 的个数为 $k$。
## 样例

### 样例输入 #1
```
2
3 5 2
5 4 7
```
### 样例输出 #1
```
S....
....S
.....
S..S
...S
S.S.
...S
.S..
```
## 提示

**本题采用捆绑测试。**

子任务 1（$20$ 分）：保证 $k \leq \min(n,m)$。

子任务 2（$12$ 分）：保证 $n = 2$。

子任务 3（$18$ 分）：保证 $T,n,m \leq 10$。

子任务 4（$20$ 分）：保证 $T \leq 10$，$n,m \leq 300$。依赖子任务 $3$。

子任务 5（$30$ 分）：无特殊限制。依赖子任务 $1 \sim 4$。

对于所有数据，保证 $1 \leq T \leq 10^4$，$1 \leq n,m \leq 2 \times 10^3$，$0 \leq k \leq nm$，$\sum nm \leq 5 \times 10^6$。


---

---
title: "「LAOI-12」命运。"
layout: "post"
diff: 普及-
pid: P12373
tag: ['洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷比赛']
---
# 「LAOI-12」命运。
## 题目背景

![](bilibili:BV1W4411z7JE)
## 题目描述

给定正整数 $n$，请你构造一个长度为 $n$ 的**排列**使得其所有区间极差之和为 $\sum\limits_{i=1}^{n-1}i^2$。

一个区间的极差定义为这个区间的最大值减最小值。
## 输入格式

**本题有多组测试数据。**

第一行输入一个正整数 $T$，表示测试数据组数。

对于每组测试数据，一行一个正整数 $n$，表示构造的排列长度。
## 输出格式

共 $T$ 行，对于每组数据输出对应的排列。
## 样例

### 样例输入 #1
```
1
3
```
### 样例输出 #1
```
3 1 2
```
## 提示

### 样例解释

对于样例一中构造的序列，共有 $6$ 个区间：

1. $[1,1]$，极差为 $0$。
2. $[2,2]$，极差为 $0$。
3. $[3,3]$，极差为 $0$。
4. $[1,2]$，极差为 $2$。
5. $[2,3]$，极差为 $1$。
6. $[1,3]$，极差为 $2$。

由于 $2+1+2=5=\sum\limits_{i=1}^{3-1}i^2$，故构造合法。
### 数据范围 
**本题采用捆绑测试。**

|子任务编号|$\sum n$|分值|
|:-:|:-:|:-:|
|$1$|$\le10$|$5$|
|$2$|$\le10^3$|$35$|
|$3$|$\le10^6$|$60$|

对于 $100\%$ 的数据，满足 $1\le T\le 10^3$，$2\le n,\sum n \le10^6$。


---

---
title: "一道搞笑的构造题"
layout: "post"
diff: 普及-
pid: P12973
tag: ['构造']
---
# 一道搞笑的构造题
## 题目背景

Many thanks to idea provider @[vegetable_king](https://www.luogu.com.cn/user/477443)!

------

构造题真的有那么难吗？
## 题目描述

设 $a$ 是一个序列，定义 $\operatorname{MEX}(a)$ 为 $a$ 中最小没有出现的正整数，$a[l, r]$ 为 $a$ 的第 $l$ 项到 $a$ 的第 $r$ 项组成的连续子序列。

给你 $n$，让你构造一个 $1 \sim n$ 的排列 $a$，使得

$$
\sum\limits_{l = 1}^n  \sum\limits_{r = l}^n \operatorname{MEX}(a[l, r])
$$

的值最大。（如果看不懂可以看题目末尾）

如果有多个 $a$ 的构造方案，请你输出字典序最小的一个。
## 输入格式

第一行一个整数 $t$，表示数据组数。

对于每组数据，第一行一个整数 $n$。
## 输出格式

对于每一个数据输出一行，表示你构造出来的 $a$。
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
1
1 2
2 1 3
```
## 提示

**【样例解释】**

对于第二组测试数据（$n=2$）：

$a[1, 1] = \{1\}$，最小没有出现的正整数是 $2$。

$a[2, 2] = \{2\}$，最小没有出现的正整数是 $1$。

$a[1, 2] = \{1, 2\}$，最小没有出现的正整数是 $3$。

上述式子的值为 $2 + 1 + 3 = 6$。

对于第三组测试数据（$n=3$）：

$a[1, 1] = \{2\}$，最小没有出现的正整数是 $1$。

$a[2, 2] = \{1\}$，最小没有出现的正整数是 $2$。

$a[3, 3] = \{3\}$，最小没有出现的正整数是 $1$。

$a[1, 2] = \{2, 1\}$，最小没有出现的正整数是 $3$。

$a[2, 3] = \{1, 3\}$，最小没有出现的正整数是 $2$。

$a[1, 3] = \{2, 1, 3\}$，最小没有出现的正整数是 $4$。

上述式子的值为 $1 + 2 + 1 + 3 + 2 + 4 = 13$。

可以证明，没有其他的排列可以使得上述式子的值比答案更大，且没有其他的排列可以使得上述式子的值与答案相等的同时字典序比答案小。

**【数据范围】**

记一个测试点所有的 $n$ 之和为 $\sum n$。

对于 $30\%$ 的数据：$\sum n \le 9$。

对于 $100\%$ 的数据：$1 \le n \le 10^6$，$1 \le t \le 10^6$，$\sum n \le 10^6$。

**【温馨提示】**

$$
\sum\limits_{l = 1}^n ( \sum\limits_{r = l}^n \operatorname{MEX}(a[l, r]))
$$


的伪代码如下：

```
for each l in range(1,n):
	for each r in range(l,n):
		result = result+MEX(l,r)
```

最终结果为 $result$。



---

---
title: "[NWERC 2023] Lateral Damage"
layout: "post"
diff: 普及-
pid: P13711
tag: ['2023', '交互题', 'Special Judge', '构造', 'ICPC']
---
# [NWERC 2023] Lateral Damage
## 题目描述

You are playing *Battleships* in a large ocean with large ships.
More precisely, there is a large square grid of size at most $100\times 100$
and inside it are up to $10$ of the largest type of ship in Battleships
-- the aircraft carrier -- which has a length of five tiles,
placed either horizontally or vertically.
The ships do not overlap, but they are allowed to be adjacent to each other.
See Figure L.1 for an example.

![](https://upload.wikimedia.org/wikipedia/commons/a/ac/Hra_n%C3%A1mo%C5%99n%C3%AD_bitva_%281%29.jpg)

:::align{center}
The original *Battleships* game, before the upgrade to a $100 \times 100$ grid. CC BY-NC 3.0 by Pavel Ševela on [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Hra_n%C3%A1mo%C5%99n%C3%AD_bitva_(1).jpg)
:::

Unfortunately, your opponent appears to bend the rules to their liking.
It looks like they do not always determine the placement of their ships before you start shooting.
You are not impressed by their attempt at cheating, and decide to try and win the game anyway.

![](https://cdn.luogu.com.cn/upload/image_hosting/0lfdcwfa.png)

:::align{center}
Figure L.1: Illustration of Sample Interaction 1 after the first four shots were fired.
:::

Your goal is to locate and sink all your opponent's aircraft carriers in at most $2500$ shots, that is, you must hit each of the five tiles of all their ships.
## 输入格式

This is an interactive problem.
Your submission will be run against an *interactor*, which reads from the standard output of your submission and writes to the standard input of your submission. This interaction needs to follow a specific protocol:

The interactor first sends one line with two integers $n$ and $k$ ($5 \le n \le 100$, $1 \le k \le 10$), the size of the grid and the number of ships. It is guaranteed that it is possible to place $k$ aircraft carriers in the grid without overlap.

Then, your program needs to start firing shots.
Each shot is fired by printing one line of the form "$\texttt{x y}$" ($1 \le x,y \le n$), indicating you shoot at position $(x, y)$. The interactor will respond with "$\texttt{hit}$" if the shot was a hit, "$\texttt{sunk}$" if the shot caused an aircraft carrier to sink, and "$\texttt{miss}$" otherwise. If you have shot the same location before, the response will be "$\texttt{miss}$".

Once you sink the last aircraft carrier, the interaction will stop and your program must exit.

The interactor is adaptive: the positions of the ships may be determined during the interaction, and may depend on where you decide to shoot.

Make sure you flush the buffer after each write.

A testing tool is provided to help you develop your solution.

Firing more than $2500$ shots will result in a wrong answer.
## 样例

### 样例输入 #1
```
7 2

miss

hit

miss

hit

hit

hit

hit

sunk

miss

miss

hit

miss

hit

hit

sunk
```
### 样例输出 #1
```

6 1

6 3

7 3

5 3

4 3

3 3

2 3

1 3

6 7

6 7

6 2

6 2

6 4

6 5

6 6
```


---

---
title: "攻击火星"
layout: "post"
diff: 普及-
pid: P1416
tag: ['模拟', '构造']
---
# 攻击火星
## 题目描述

一群外星人将要攻击火星。

火星的地图是一个 $n$ 个点的无向图。这伙外星人将按照如下方法入侵，先攻击度为 $0$ 的点（相当于从图中删除掉它），然后是度为 $1$ 的点，依此类推直到度为 $n-1$ 的点。

所有的点度统计是动态统计的。（一个点删掉后，与之相连的点的点度都会 $-1$）。外星人攻击度为某个数的点时是同时攻击的。

你需要设计这个图的边的方案来使得未被攻击的点最多。注意：你设计的图**不允许自环及重边**。


## 输入格式

输入文件包含一行一个整数 $n$。

## 输出格式

一行一个整数，表示最多的最后未被攻击的点。

## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
1
```
## 提示

【样例解释】

一种可能的方案是 $1\leftrightarrow 2\leftrightarrow 3$，这样首先删掉度为 $1$ 的点 $1$ 和点 $3$，此时点 $2$ 度数为 $0$，不会被删去。

【数据范围】

- 对于 $20\%$ 的数据 $1\le n\le 10$；
- 对于 $100\%$ 的数据 $1\le n\le 5\times 10^4$。

【题目来源】

tinylic改编



---

---
title: "无穷的序列"
layout: "post"
diff: 普及-
pid: P1795
tag: ['NOI 导刊', '枚举', '构造']
---
# 无穷的序列
## 题目描述

有一个无穷序列如下：

$\texttt{110100100010000100000}$…

请你找出这个无穷序列中指定位置上的数字。
## 输入格式

第一行一个正整数 $N$ ，表示询问次数；

接下来的 $N$ 行每行一个正整数 $A_i$，$A_i$ 表示在序列中的位置。
## 输出格式

输出为 $N$ 行，每行为 $0$ 或 $1$ ，表示序列第  $A_i$ 位上的数字。
## 样例

### 样例输入 #1
```
4
3
14
7
6 

```
### 样例输出 #1
```
0
0
1
0

```
## 提示

对于 $100\%$ 的数据，$N \leq 1\,500\,000$，$A_i≤10^9$。


---

---
title: "[USACO3.4] 美国血统 American Heritage"
layout: "post"
diff: 普及-
pid: P1827
tag: ['模拟', '树形数据结构', 'USACO', '递归', '构造']
---
# [USACO3.4] 美国血统 American Heritage
## 题目描述

农夫约翰非常认真地对待他的奶牛们的血统。然而他不是一个真正优秀的记帐员。他把他的奶牛 们的家谱作成二叉树，并且把二叉树以更线性的“树的中序遍历”和“树的前序遍历”的符号加以记录而 不是用图形的方法。

你的任务是在被给予奶牛家谱的“树中序遍历”和“树前序遍历”的符号后，创建奶牛家谱的“树的 后序遍历”的符号。每一头奶牛的姓名被译为一个唯一的字母。（你可能已经知道你可以在知道树的两 种遍历以后可以经常地重建这棵树。）显然，这里的树不会有多于 $26$ 个的顶点。

这是在样例输入和样例输出中的树的图形表达方式：


```plain
　　　　　　　　 C
　　　　　　   /  \
　　　　　　  /　　\
　　　　　　 B　　  G
　　　　　　/ \　　/
　　　　   A   D  H
　　　　　　  / \
　　　　　　 E   F

```

附注：

- 树的中序遍历是按照左子树，根，右子树的顺序访问节点；
- 树的前序遍历是按照根，左子树，右子树的顺序访问节点；
- 树的后序遍历是按照左子树，右子树，根的顺序访问节点。

## 输入格式

第一行一个字符串，表示该树的中序遍历。

第二行一个字符串，表示该树的前序遍历。

## 输出格式

单独的一行表示该树的后序遍历。

## 样例

### 样例输入 #1
```
ABEDFCHG
CBADEFGH 

```
### 样例输出 #1
```
AEFDBHGC
```
## 提示

题目翻译来自NOCOW。

USACO Training Section 3.4



---

---
title: "【XR-4】歌唱比赛"
layout: "post"
diff: 普及-
pid: P5595
tag: ['Special Judge', '构造', '洛谷月赛']
---
# 【XR-4】歌唱比赛
## 题目背景

**赛时提醒：本题不提供任何关于样例 4 以及无解的解释。**

**赛时提醒：本题不提供任何关于输出格式以及 Special Judge 的解释。**

**赛时提醒：抱歉，本题的 Special Judge 不忽略行末空格，请保证两行中没有多余字符。**

**赛时提醒：非常抱歉，本题输入数据是 Windows 格式，而非 Linux 格式，所以在末尾的 `\n` 之前有一个多余的 `\r` 字符。请使用 `scanf` 或 `cin` 读入数据，而非 `getline`，因为后者会多读入一个 `\r`。**
## 题目描述

小 X 参加了一场歌唱比赛。

经过一路鏖战，小 X 终于挺进了决赛，他的对手是小 Y。

这场歌唱比赛的冠军是由点赞数决定的，谁的点赞数高，谁就能夺冠。

小 X 和小 Y 依次演唱完自己的最后一首歌曲后，他们最终的点赞数确定了下来。

揭晓冠军的时刻终于到来了，主持人为了增加悬念，决定从小 X 与小 Y 的点赞数的最后一位开始，依次比较。

比如，小 X 的点赞数是 $37$，小 Y 的点赞数是 $28$。首先比较最后一位，小 X 是 $7$，小 Y 是 $8$，此时小 Y 暂时领先。再加上前一位，小 X 是 $37$，小 Y 是 $28$，此时小 X 暂时领先。比较结束，如果我们用 `X` 代表小 X 暂时领先，`Y` 代表小 Y 暂时领先，那么可以写下一个字符串 `XY`。

再比如，小 X 的点赞数是 $137$，小 Y 的点赞数是 $47$。如果我们再用 `Z` 表示小 X 与小 Y 的点赞数暂时一样，那么写下的字符串应该为 `XYZ`。

你作为一个精通 OI 的神仙，自然知道这种比较方式是非常不科学的，这样只是在无端拖延时间罢了，但是你却对最后写下的这个字符串很感兴趣。

现在，你得到了这个最后写下的字符串，你需要构造出一种可能的小 X 与小 Y 的点赞数。

当然，有可能不存在任何一种情况的点赞数满足这个字符串，那么你只需要输出 `-1` 即可。

为了方便你输出，请用前导零来补足位数。
## 输入格式

一行一个字符串 $s$，表示最后写下的字符串。
## 输出格式

如果有解：

- 第一行一个整数，表示小 X 的点赞数。
- 第二行一个整数，表示小 Y 的点赞数。

如果无解：

- 一行一个整数 `-1`。
## 样例

### 样例输入 #1
```
XY

```
### 样例输出 #1
```
37
28

```
### 样例输入 #2
```
XYZ

```
### 样例输出 #2
```
137
047

```
### 样例输入 #3
```
ZZZZZZ

```
### 样例输出 #3
```
000000
000000

```
### 样例输入 #4
```
XYZXYZ

```
### 样例输出 #4
```
-1

```
## 提示

**本题采用捆绑测试。**

- Subtask 1（11 points）：$\text{len}(s) = 1$。
- Subtask 2（42 points）：$s_i \in \{\texttt{X},\texttt{Y}\}$。
- Subtask 3（21 points）：数据保证有解。
- Subtask 4（26 points）：无特殊限制。

对于 $100\%$ 的数据，$s_i \in \{\texttt{X},\texttt{Y},\texttt{Z}\}$，$1 \le \text{len}(s) \le 10^6$。


---

---
title: "[NWRRC 2015] Hash Code Hacker"
layout: "post"
diff: 普及-
pid: P7055
tag: ['字符串', '2015', 'Special Judge', '哈希 hashing', '构造', 'ICPC']
---
# [NWRRC 2015] Hash Code Hacker
## 题目描述



According to Java standard library documentation, the hash code of String is computed as

$s[0] \times 31 ^ {n -1} + s[1] \times 31 ^ {n -2} + \cdots + s[n -1]$

Here $s[i]$ is the i-th character of the string, $n$ is the length of the string, and $^$ indicates exponentiation. Computation uses signed $32-bit$ integers in two's complement form.

Heather is going to hack the servers of Not Entirely Evil Recording Company $(NEERC).$ To perform an attack she needs $k$ distinct query strings that have equal hash codes. Unfortunately, NEERC servers accept query string containing lower- and uppercase English letters only.

Heather hired you to write a program that generates such query strings for her.


## 输入格式



The single line of the input file contains integer $k$ -- the number of required query strings to generate $(2 \le k \le 1000)$ .


## 输出格式



Output $k$ lines. Each line should contain a single query string. Each query string should be non-empty and its length should not exceed $1000$ characters. Query string should contain only lower- and uppercase English letters. All query strings should be distinct and should have equal hash codes.


## 样例

### 样例输入 #1
```
4

```
### 样例输出 #1
```
edHs
mENAGeS
fEHs
edIT

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

根据$Java$的标准库文件，字符串的哈希代码是这么计算的：

$$s[0]×31 ^{(n−1)}+s[1]×31^{(n−2)}+⋯+s[n−1]$$

在这里，s[i]指的是字符串中的第i位，n是字符串的长度。

这个计算过程用的是有符号的$32$位整数的二进制补码形式。

有一个人叫作 阖锕仄 $(Heather)$。他想要$hack$掉“不全是恶魔录音公司”$(NEERC)$。为了进行

一次攻击，阖锕仄需要$k$个有相同哈希代码的不同的询问字符串。不幸的是，$NEERC$的服务器

只接受只包含大小写字母的字符串。

阖锕仄请你帮忙写一个程序，以生成他需要的询问字符串。

-------

输入一个正整数$k$,代表需要的字符串的数量。

-------

输出有$k$行，每行的询问字符串都不应该为空，并且每行的字符串的长度应该小于等于1000个字符。

询问字符串的具体要求请看上文。

-------

时间限制：$2s$    

空间限制：$256MB$

翻译提供：@Trexmao


---

---
title: "天选之人"
layout: "post"
diff: 普及-
pid: P7107
tag: ['贪心', '洛谷原创', 'Special Judge', 'O2优化', '鸽笼原理', '构造', '洛谷月赛']
---
# 天选之人
## 题目背景

暑假期间，学校不提供午餐，Gnar 只好找伙计们一起点外卖。

尴尬的是，外卖很快送到却没人乐意去校门口拿，毕竟户外可是 $35\degree\!\text{C}$ 高温！此时 Gnar 想到了好主意：“我给一人捏了一张纸团，其中一张写有记号，不如我们抓阄决定，谁抽到带记号的谁去拿！”

于是 Gnar 连续拿了六天的外卖。

这可让他不服又委屈：“换个规则！一人准备三张纸团，五张有记号，每人抽三张，记号最多的去拿！”

Gnar 紧张地展开手中的纸团，两个记号赫然映在眼前。大伙们刚想放声大笑他的非酋运气，有人缓缓举起三张纸片说道：“我也抽到了两个记号……”
## 题目描述

好奇的 Gnar 想研究一般情况下抽到最多记号的人数。他给参与抓阄的 $n$ 人一人准备了 $m$ 张捏好的纸团，一共 $nm$ 张，其中恰好 $k$ 张提前写了记号。随后每个人在均匀打乱的纸团中各抽 $m$ 张。

一个人抽到最多的记号，当且仅当没有人抽到的记号比他还多。请你帮 Gnar 判断是否可能会**恰好** $\boldsymbol{p}$ **个人**抽到最多的记号。Gnar 喜欢追根问底，所以如果有可能，你还需构造每个人抽的纸团中分别有多少带记号、有多少不带记号。

形式化地，假设第 $i$ 个人抽到了 $x_i$ 张带记号的纸团和 $y_i$ 张不带记号的纸团，你的构造应满足：

- $x_i, y_i \ge 0$，$x_i + y_i = m$。
- $\displaystyle \sum_{i = 1}^{n} x_i = k$。
- **有且仅有** $\boldsymbol{p}$ **个互不相同**的 $j$ 使 $\displaystyle x_j = \max_{i = 1}^{n} \{x_i\}$。
## 输入格式

输入四个整数 $n, m, k, p$，含义详见题目描述。
## 输出格式

第一行输出 `YES` 或 `NO`（不区分大小写，`yEs` / `No` 均可），表示是否会恰好 $p$ 个人抽到最多的记号。

如果第一行输出 `YES`，接下来 $n$ 行每行输出 $x_i, y_i$，表示每个人抽到带与不带记号的纸团个数。

因答案可能不唯一，本题采用 Special Judge，只要构造符合题面中的要求均视为正确。
## 样例

### 样例输入 #1
```
3 3 5 2
```
### 样例输出 #1
```
YES
2 1
2 1
1 2
```
### 样例输入 #2
```
3 3 3 2
```
### 样例输出 #2
```
NO
```
### 样例输入 #3
```
3 3 5 3
```
### 样例输出 #3
```
NO
```
## 提示


**【样例解释 #1】**

样例给出了一种满足题述条件的构造。

**【样例解释 #2】**

不论如何，记号的分布从高到低只有三种情况：$\{3,0,0\}$，$\{2,1,0\}$，$\{1,1,1\}$，抽到最多记号的人数分别对应 $1$，$1$，$3$。因此无法构造 $p = 2$ 的方案。

----

**【数据规模与约定】**

**本题采用捆绑测试**。你必须通过 Subtask 中所有的测试点才能获得该 Subtask 的分数。

- Subtask #1 (15 points)：$n,m \le 8$。
- Subtask #2 (15 points)：$n,m \le 100$。
- Subtask #3 (20 points)：$n,m \le 10^5$。
- Subtask #4 (10 points)：$p = 1$。
- Subtask #5 (40 points)：无特殊限制。

对于所有的数据，保证 $1 \le p \le n \le {10}^5$，$1 \le m \le {10}^9$，$0 \le k \le n m$。


---

---
title: "[COCI 2015/2016 #3] ESEJ"
layout: "post"
diff: 普及-
pid: P7227
tag: ['2015', 'Special Judge', '随机化', '构造', 'COCI（克罗地亚）']
---
# [COCI 2015/2016 #3] ESEJ
## 题目描述

小 M 要写一篇文章。

- 这篇文章至少 $a$ 个词，最多 $b$ 个词，
- 每个单词至少 $1$ 个字母，最多 $15$ 个字母。
- 文章至少包含 $\dfrac{b}{2}$ 个不同的单词。

小 M 昨晚熬夜打 Codeforces，所以请你帮他写作文。

作文只能有一段（只有一行），只能使用英文字母的小写字母和空格。

**注：作文的句意可以不通顺，语法也可以不正确，只要符合要求的作文，均可以 $\color{green}\texttt{AC}$。**
## 输入格式

第一行两个正整数 $a, b$。
## 输出格式

一行，一篇作文。
## 样例

### 样例输入 #1
```
2 7

```
### 样例输出 #1
```
this shakespeare fella is good
```
## 提示

#### 数据规模及约定

对于 $100\%$ 的数据，$1\le a, b \le 10^5$。

#### 说明
- 样例 #2 和样例 #3 由于输出过长放置在了这里：[样例 #2 与样例 #3](https://www.luogu.com.cn/paste/we9k25k1)。
- 翻译自 [COCI 2015-2016 #3 B ESEJ](https://hsin.hr/coci/archive/2015_2016/contest3_tasks.pdf)，满分 80。
- 感谢 @[tiger2005](https://www.luogu.com.cn/user/60864) 提供的 checker.cpp。


---

---
title: "[THUPC 2017] 玩游戏"
layout: "post"
diff: 普及-
pid: P7427
tag: ['贪心', '2017', 'Special Judge', '构造', 'THUPC']
---
# [THUPC 2017] 玩游戏
## 题目描述

ljcc 和他的学妹在玩游戏，这个游戏共有 $n$ 轮，在第 $i$ 轮获胜会获得 $i$ 分，没有平局。

现在给出 ljcc 和学妹的得分，求是否有一种方案符合当前得分。
## 输入格式

从标准输入读入数据。

输入一行输入两个数 $a,b$ 代表 ljcc 和学妹的得分。
## 输出格式

输出到标准输出。

若有解，在一行输出一组合法的解。第一个数代表游戏总共进行了 $n$ 轮，之后若干个数表示 ljcc 在哪些局获胜了，每两个数用单个空格隔开，行末不允许有空格。若没有合法解输出 `No`。
## 样例

### 样例输入 #1
```
10 5
```
### 样例输出 #1
```
5 1 2 3 4
```
## 提示

**由于 SPJ 问题，禁止输出行末空格、回车**。

$a,b\le 2^{31}-1,1\le n\le 10^5$
#### 版权信息
来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2017。


---

---
title: "「EZEC-10」排列排序"
layout: "post"
diff: 普及-
pid: P7714
tag: ['模拟', '\ufeff基础算法', '构造', '差分', '双指针 two-pointer']
---
# 「EZEC-10」排列排序
## 题目描述

给你一个长度为 $n$ 的排列 $p_1,p_2, \cdots ,p_n$。你需要把它排序。

每次可以花区间长度，即 $r-l+1$ 的代价，选择排列中的任意一段区间 $[l,r]$，并将 $[l,r]$ 从小到大排序。

现在你可以让他进行若干次这个操作，直到 $p$ 中元素的值从 $1$ 到 $n$ 按升序排序，即对于 $1$ 到 $n$ 的每一个 $i$，都有 $p_i=i$。

求问花的代价最少为多少？
## 输入格式

本题有多组询问，第一行有一个数 $T$ 表示询问组数。

对于每组询问：

第一行给出一个整数 $n$。

第二行 $n$ 个整数，由空格隔开，代表排列 $p$ 中元素的值。
## 输出格式

$T$ 行，每行一个整数表示一组询问的答案。
## 样例

### 样例输入 #1
```
2
3
1 3 2
4
3 2 1 4
```
### 样例输出 #1
```
2
3
```
## 提示

【样例 $1$ 说明】

对于第一组数据，可选择区间 $[2,3]$ 进行排序。

对于第二组数据，可选择区间 $[1,3]$ 进行排序。

【数据规模与约定】

对于 $20\%$ 的数据，$n\leq 4$。

对于另 $30\%$ 的数据，$\sum n\leq5000$。

对于另 $10\%$ 的数据，$p_1=n$。

对于 $100\%$ 的数据，$1\le T,\sum n\le 10^6$。


---

---
title: "「EZEC-9」Yet Another Easy Problem"
layout: "post"
diff: 普及-
pid: P7852
tag: ['Special Judge', 'O2优化', '构造']
---
# 「EZEC-9」Yet Another Easy Problem
## 题目描述

给定 $n,m$，你需要输出一个长度为 $n$ 的排列，满足该排列进行不超过 $m$ 次操作可以得到的最小的字典序最大。

定义一次操作为交换排列中的两个数。

若有多个符合要求的排列，输出任意一个均可。
## 输入格式

**本题有多组数据**。

第一行一个正整数 $T$，表示数据组数。

对于每组数据，一行 $2$ 个整数 $n,m$。
## 输出格式

对于每组数据：

一行 $n$ 个正整数，表示你构造的排列。
## 样例

### 样例输入 #1
```
2
4 2
3 3

```
### 样例输出 #1
```
4 3 1 2
1 2 3

```
## 提示

【样例 $1$ 说明】

使得字典序最小的操作方案为:

$4\ 3\ 1\ 2\to1\ 3\ 4\ 2\to1\ 2\ 4\ 3$。

可以证明无法得到更小的字典序，以及其他初始排列无法得到更大的最小字典序。

【样例 $2$ 说明】

显然可以通过操作得到任何排列，输出任意长度为 $3$ 的排列均可。

【数据规模与约定】

**本题采用捆绑测试**。

- Subtask 1（10 points）：$m=0$。
- Subtask 2（10 points）：$m\ge n-1$。
- Subtask 3（25 points）：$m=1$。
- Subtask 4（25 points）：$T\le100$，$n\le6$。
- Subtask 5（30 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le n\le10^5$，$0\le m\le n$，$\sum n\le10^5$。


---

---
title: "「SWTR-7」Scores（easy version）"
layout: "post"
diff: 普及-
pid: P7873
tag: ['模拟', '2021', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 「SWTR-7」Scores（easy version）
## 题目背景

#### 本题是 Scores 的 easy 版本。注意题目限制与 [hard](https://www.luogu.com.cn/problem/P7876) 版本不同。

#### 请注意特殊的时空限制，题目描述下方有简化题意。
## 题目描述

小 A 的班上有 $n$ 个学生。最近他们进行了一场考试，共有 $m$ 个学科。第 $i$ 个学生第 $j$ 门学科的得分为**整数** $s_{i,j}\ (0\leq s_{i,j}\leq 100)$。对于学生 $i$，如果**存在另一个**学生 $j$ 满足：学生 $i$ **每门学科的成绩都不大于**学生 $j$，学生 $i$ 就会感到失落。

中秋节快到了，善良的小 A 不想让任何一个同学感到失落，他决定 hack 学校的管理系统，修改每一位同学的成绩。在做出这样危险的举动之前，小 A 希望知道自己能否达到目标。不过，由于学生和科目实在太多，他想请你帮助他构造出一种合法的方案。

如果存在一张成绩表，满足没有任何一位同学感到失落，请先输出 $\texttt{YES}$，再**任意**输出一种符合要求的成绩表；否则输出 $\texttt{NO}$。

---

**「简化题意」**

试构造一个 $n\times m$ 的矩阵 $s$，满足所有元素为 $[0,100]$ 之间的整数，且对于任意 $i,j\ (i\neq j)$ 存在一个 $k$ 使得 $s_{i,k}>s_{j,k}$。
## 输入格式

**本题有多组数据。**

第一行一个整数 $t$，**表示该测试点编号**。  
第二行一个整数 $T$，**表示数据组数**。

对于每组数据：  
一行两个整数 $n,m$。
## 输出格式

对于每组数据：

如果小 A 的要求无法实现，输出一行字符串 $\texttt{NO}$。  
否则先输出一行字符串 $\texttt{YES}$，再输出 $n$ 行，每行 $m$ 个由空格隔开的整数，第 $i+1$ 行第 $j$ 个数表示 $s_{i,j}$。
## 样例

### 样例输入 #1
```
0
4
5 3
1 10
17 1
2 7
```
### 样例输出 #1
```
YES
100 99 97
98 100 99
95 97 100
0 98 100
99 99 99
YES
1 2 3 4 5 6 7 8 9 10
NO
YES
95 99 76 88 87 51 49
72 100 80 92 100 60 60
```
## 提示

**「Special Judge」**

**本题使用 Special Judge。请认真阅读输出格式，输出格式有误可能导致 UKE。**

SPJ 首先会判断你的第一行输出是否与答案相同。  
如果相同且答案为 $\texttt{YES}$，则 SPJ 会判断你的输出是否符合小 A 的要求：

- $0\leq s_{i,j}\leq 100$ 且 $s_{i,j}$ 为整数。
- 每个学生至少有一个科目的成绩比另一个学生高。

如果有解且你输出 $\texttt{YES}$，但给出方案错误，你将获得该测试点 $50\%$ 的分数。

**「数据范围与约定」**

本题共有 6 个测试点。

- Testcase #0（1 point）：是样例。
- Testcase #1（10 points）：$n=1$。
- Testcase #2（10 points）：$m=1$。
- Testcase #3（20 points）：$m=2$。
- Testcase #4（30 points）：$n\leq m$。
- Testcase #5（29 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,m\leq 100$，$T=20$（除 Testcase #0）。  
对于所有测试点，**时间限制 200ms，空间限制 16MB。**

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51774) A1。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。


---

---
title: "[Aya Round 1 C] 文文的构造游戏"
layout: "post"
diff: 普及-
pid: P8468
tag: ['数学', '洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# [Aya Round 1 C] 文文的构造游戏
## 题目背景

**Problem Number:** [$\textit{23}$](https://www.luogu.com.cn/training/1392)

众所周知，射命丸文和琪露诺是好朋友。但是文是大妖怪，非常聪明，而琪露诺是个笨蛋。为了提升琪露诺的智商，文便给琪露诺出了一道简单的题目。
## 题目描述

对于一个长度为 $l$ 的数列 $p$，定义 $S(p)$ 为所有元素的**异或和**，其中 $\oplus$ 指[按位异或运算](https://baike.baidu.com/item/%E5%BC%82%E6%88%96%E6%93%8D%E4%BD%9C)。

给定整数 $s,m$，判断能否构造一个长度为 $n$（$n$ 值自定）的数列 $a$，满足：

- $1 \le n \le m$。
- $1 \le a_i \le s$。
- $S(a)=0$。
- $a_1+a_2+\cdots+a_n=s$。

试构造任意一组合法解或报告无解。
## 输入格式

**本题包含多组数据。**

- 第一行输入一个整数 $T$，表示数据组数。
- 接下来 $T$ 行，每行输入两个整数 $s,m$。表示一组询问。
## 输出格式

- 输出共 $T$ 行。
- 对于每组数据：
  - 若有解，首先输出一个整数 $n$，然后输出 $n$ 个整数，表示 $a$。
  - 若无解，仅输出一行一个整数 $-1$。
## 样例

### 样例输入 #1
```
2
14 9
3 3
```
### 样例输出 #1
```
3 3 5 6
-1
```
## 提示

### 样例解释

- 对于数据 $1$，容易发现 $3\oplus5\oplus6=0$，$3+5+6=14$。符合要求。
- 对于数据 $2$，发现数列 $\{3\},\{1,2\},\{1,1,1\}$ 均不符合要求，故无解。

### 数据范围与约定

对于 $100\%$ 的数据，有 $1\le s\le 10^{18}$，$1 \le m$，$1 \le \sum m \le 10^6$。

**友情提示，您可能需要使用较快的 I/O 方式。**


---

---
title: "「Wdoi-2」幻胧月睨"
layout: "post"
diff: 普及-
pid: P8536
tag: ['洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 「Wdoi-2」幻胧月睨
## 题目背景

**Problem Number:** $\textit{39}$

**背景与题目无关，选手可以直接看下面的「简要题意」。**

那是在竹取物语之后的故事了，幻想乡距离与现实隔绝也已经过去了百年时光。

地上人向月球发起了侵略战争之后，一只名叫**铃仙**的月兔舍弃了同伴，死里逃生，逃到了在幻想乡内的永远亭，来到了辉夜与永琳的身边，生活得安稳而舒适。

又过了数十年，铃仙接收到了来自月球的使唤，被要求强制返回月球。辉夜与永琳商量了下，决定不将铃仙交还予月球。但为了避免造成麻烦，辉夜与永琳决定将满月消失在地上，只留下一轮虚假的月亮。

-----

为了方便调查异变，八云紫运用自己的能力，将整个幻想乡变成了永夜。

被穿梭回异变发生当时的四组主角，共八人。除了依然留有记忆，可以来回穿梭在虚与实的境界的八云紫之外，其他的人缺乏了记忆，重新开始踏上夺回幻想乡的满月的征途。

在慧音的指引之下，她们来到了迷途竹林，在她们的面前，是一只名叫铃仙的月兔。
## 题目描述

### 简要题意

给定一个长度为 $n$ 的 01 串 $b$，要求构造一个 $n$ 阶排列 $a$，满足，对于 $a_i(2\le i\le n)$，记 $m_i=\max_{j=1}^{i-1}\{a_j\}$，则：
  - 若 $b_i=1$，则 $a_i>m_i$;
  - 否则 $a_i<m_i$。

可以证明，总存在一个数列 $a$ 满足以上条件。

**如果有多组解，输出任意一种。**

同时注意到 $b_1$ 的取值是任意的，对数列 $a$ 没有影响。

### 原始题意

铃仙拥有操纵狂气程度的能力，换而言之，就是操纵物体的波长、振幅以及相位。这种能力为主角制造了种种障碍——例如操纵光波，会让弹幕虚虚实实，甚至会出现虚假的自我，对躲避弹幕造成极大的干扰。

以符卡「幻胧月睨」为例。「幻胧月睨」中一共有 $n$ 个弹幕，每个弹幕都会有一个相位，相位非 $0$ 即 $1$。这些弹幕的相位会构成一个长度为 $n$ 的数列 $\{b_i\}$。

铃仙会操纵这些弹幕的相位，将其变得千奇百怪。具体而言，被操纵了之后的弹幕的相位是一个长度为 $n$ 的**排列** $\{a_i\}$，即 $1 \sim n$ 的数字都会**不重不漏**地出现在这个序列之中。

为了加大主角躲避弹幕的难度，铃仙会设置一个阈值。对于每一个元素 $a_i$，阈值是其**前缀**的**最大**值，即 $a_1,a_2,\dots,a_{i-1}$ 中的最大值。若原来的第 $i$ 个弹幕的相位为 $1$，则被操纵后的弹幕的相位要**大于**这个阈值，否则被操纵后的弹幕的相位要**小于**这个阈值。

显然的是，根据铃仙的操纵规则，无论原本的弹幕的相位如何，都是存在可能的操纵方案的。由于主角们失去了记忆，而找回月亮的时间已经所剩不多了，而且弹幕战对时间的把控要求极高。她们找到了你，希望你能够对铃仙原本的弹幕相位，给出**任意一种**操作后的弹幕相位，来为她们的闪避弹幕进行准备。
## 输入格式

**本题有多组数据。**

第一行一个整数 $T$，表示数据组数。

对于每组数据：

- 第一行一个整数 $n$，意义如题述。
- 第二行一个长度为 $n$ 的 01 串 $b$。
## 输出格式

对于每组数据，输出一行 $n$ 个整数，即你构造的数列 $a$。

**如果有多组解，输出任意一种。**
## 样例

### 样例输入 #1
```
3
3
111
3
101
4
0101
```
### 样例输出 #1
```
1 2 3
2 1 3
1 3 2 4
```
## 提示

### 样例解释

- 对于数据 $1$，显然 $a_2>1,a_3>2$。
- 对于数据 $2$，显然 $a_2<2,a_3>2$。
- 对于数据 $3$，显然 $a_2>1,a_3<3,a_4>3$。\
  注意到 $a=\{2,3,1,4\}$ 同样满足要求。

### 数据范围

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|}\hline
\textbf{Subtask} & \bm{n\le} & \textbf{特殊性质} & \textbf{Subtask 依赖} & \textbf{分值}\\\hline
1 & 10 & - & - & 5\\\hline
2 & 10^5 & \textbf{A} & - & 5 \\\hline
3 & 10^5 & \textbf{B} & - & 20 \\\hline
4 & 10^5 & - & 1,2,3 &70 \\\hline
\end{array}$$

- **特殊性质** $\textbf{A}$：保证 $b_i$ 都相等。
- **特殊性质** $\textbf{B}$：存在整数 $p\in[2,n]$，使得对于 $1\le i<p$，有 $b_i=1$；对于 $n\ge i\ge p$，有 $b_i=0$。

对于全部数据，满足 $1\le T\le 10^4$，$1\le n\le 10^5$，$\forall i\in[1,n],b_i\in\{0,1\}$。

保证单个测试点内 $\sum n\le 5\times 10^5$。


---

---
title: "『JROI-8』对了，还有花，少女，银河"
layout: "post"
diff: 普及-
pid: P8589
tag: ['洛谷原创', 'Special Judge', '构造', '洛谷月赛']
---
# 『JROI-8』对了，还有花，少女，银河
## 题目背景

![1663764189387.png](https://img-kysic-1258722770.file.myqcloud.com/9d24e2bd5b20f277e72914b1bc44543e/44b6413b44c70.png)

>「其一」\
即使化身白骨，也有不想忘记的东西

**已获得转载授权。**
## 题目描述

给定 $n$，请构造一个长度为 $n$ 的仅包含 $0,1$ 的数字串，满足 $01,00,10,11$ 出现的次数相等。或报告无解。

这里“出现”指与原字符串中连续的一部分完全相同。例如，在 $1011101$ 中，$01,00,10,11$ 分别出现了 $2,0,2,2$ 次。

**请注意，大样例不以文件附加形式给出，而直接放在题目的 输入输出样例 中的 样例 #3**
## 输入格式

一行一个正整数 $n$。
## 输出格式

若有解，输出一行一个长度为 $n$ 的满足条件的仅包含 $0,1$ 的数字串。

若无解，输出 `-1`。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
-1
```
### 样例输入 #2
```
5
```
### 样例输出 #2
```
00110
```
### 样例输入 #3
```
15400
```
### 样例输出 #3
```
-1
```
## 提示

【数据范围与提示】

| 测试点编号 | 分数 | $n\leq$ | 特殊性质 |
| -----------: | -----------: | -----------: | -----------: |
| $1\sim 2$ | $20$ | $5$ | 无 |
| $3\sim 4$ | $20$ | $10^6$ | $n \bmod 4 = 0$ |
| $5\sim 6$ | $20$ | $20$ | 无 |
| $7 \sim 10$ | $40$ | $10^6$ | 无 |


---

---
title: "『JROI-7』PMK 配匹串符字"
layout: "post"
diff: 普及-
pid: P8846
tag: ['字符串', '2022', '洛谷原创', 'Special Judge', '构造', '洛谷月赛']
---
# 『JROI-7』PMK 配匹串符字
## 题目背景

> 限制很宽泛，构造也就很憨批。

——command_block 《考前小贴士》
## 题目描述

对于一个字符串 $S$，记 $|S|$ 表示 $S$ 的长度，记 $S_i$ 表示 $S$ 的第 $i$ 个字符，记 $S_{l,r}$ 表示 $S_l,S_{l+1},...,S_r$ 组成的字符串。定义两个字符串相等，当且仅当他们长度相等，且每个位置的字符相同。

对于一个字符串 $S$ 和一个正整数 $i\le |S|$，若 $k$ 是满足 $k<i$ 且 $S_{1,k}=S_{i-k+1,i}$ 的最大的正整数，则 $next_i=k$。特别的，若不存在 $k$ 满足条件，则 $next_i=0$。

请你构造一个由小写字母组成的字符串 $S$，满足 $|S|=n$，且对于所有正整数 $i\le |S|$，$next_i$ 之和最小。
## 输入格式

一行一个正整数 $n$。
## 输出格式

一行一个字符串，表示你构造的 $S$。**输出任意一种方案即可。**
## 样例

### 样例输入 #1
```
5
```
### 样例输出 #1
```
abcde
```
## 提示

### 数据规模
本题采用捆绑测试。

对于 $50\%$ 的数据，$n\le 26$。

对于 $100\%$ 的数据，$1\le n\le 10^5$。


---

---
title: "[JRKSJ R5] 1-1 A"
layout: "post"
diff: 普及-
pid: P8847
tag: ['2022', '洛谷原创', 'Special Judge', '构造', '洛谷月赛']
---
# [JRKSJ R5] 1-1 A
## 题目背景

本题是 1-1 的较易版本，较难版本为 [1-1 B](https://www.luogu.com.cn/problem/P8848)。
## 题目描述

给出一个序列 $a$，$\forall i\in [1,n],a_i\in \{1,-1\}$。

你可以将序列任意重排，需最小化重排后序列的最大子段和。
## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个整数表示 $a$。
## 输出格式

一行 $n$ 个整数，以空格隔开，表示重排后的序列。

若有多解，则任意输出一个答案即可。
## 样例

### 样例输入 #1
```
4
1 1 -1 -1
```
### 样例输出 #1
```
1 -1 -1 1
```
## 提示

最大子段和的定义：序列中一段区间的和的最大值。即 $\max_{1\le l\le r\le n} \sum_{i=l}^r a_i$。

本题使用 $\text{Special Judge}$，只要你的输出满足题意即可通过。

**本题输入输出文件较大，请使用恰当的输入输出方式。**

### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | $\text{Score}$ |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $40$ |
| $2$ | $10^6$ | $60$ |

对于 $100\%$ 的数据，$1\le n\le 10^6$，$a_i\in \{1,-1\}$。


---

---
title: "Digital Fortress"
layout: "post"
diff: 普及-
pid: P8942
tag: ['2023', '洛谷原创', 'Special Judge', 'O2优化', '构造', 'Ad-hoc']
---
# Digital Fortress
## 题目背景

布林克霍夫大声喊道：“这当然是密码！这不是密码，还能是什么？还有什么原因能让友加送掉这枚戒指？到底是谁在戒指上刻一大串杂乱无章的字母？”

方丹愤怒地等了布林克霍夫一眼，使他安静了下来。

“啊……伙计们？”贝克插了一句话，似乎很不情愿卷进来一样，“你们一直说这些是杂乱无章的字母。我想我应该让你们知道……这枚戒指上刻的字母并不是杂乱无章。如果你近距离看一下，就会明白，实际上，这些字母……这个……这个是拉丁文。”

指挥台上的所有人都看向了那枚戒指。上面写道：

> Quis custodiet ipsos custiodies.  
谁来监视这些监视者……
## 题目描述

致命的变异串已经穿过了 X-11 过滤器，深入了国安局数据库。苏珊与贝克需要即时破解出密码，以关闭蠕虫病毒。

在蠕虫的文件中，他们找到了密码的一个特点：

- 共有 $n$ 位，每个数都在 $[1,m]$ 之间，并且单调不减。
- 如算出前缀异或和，那么前缀异或和也单调不减。
- 如算出后缀异或和，那么后缀异或和仍然单调不减。

除此之外，他们也找到了 $n,m$ 的值。现在，他们需要构造出一组密码，以满足所有特征。
***

#### 【形式化题意】

求是否存在长度为 $n$，所有元素都在 $[1,m]$ 范围内的单调不减正整数序列 $a$，满足：

- $\forall1<i\le n,a_1\ \text{xor}\ a_2\ \text{xor}\ \cdots\ \text{xor}\ a_{i-1}\le a_1\ \text{xor}\ a_2\ \text{xor}\ \cdots\ \text{xor}\ a_{i}$
- $\forall1\le i<n,a_n\ \text{xor}\ a_{n-1}\ \text{xor}\ \cdots\ \text{xor}\ a_{i+1}\le a_n\ \text{xor}\ a_{n-1}\ \text{xor}\ \cdots\ \text{xor}\ a_{i}$

如存在，输出一组合法解。多组数据。
## 输入格式

第一行一个正整数 $t$，表示数据组数。

对于每组数据，输入两个正整数 $n,m$。
## 输出格式

对于每组数据，如不存在满足要求的密码，输出 `No`。否则，输出 `Yes`，并在下一行输出一种合法方案。
## 样例

### 样例输入 #1
```
2
4 20
1919 114514

```
### 样例输出 #1
```
Yes
1 6 8 16
No

```
## 提示

#### 【样例解释】

对于第一组数据，密码的前缀异或和为 $\{1,7,15,31\}$，后缀异或和为 $\{16,24,30,31\}$，均为递增序列，满足题意。

对于第二组数据，不存在任何合法方案。

#### 【数据范围】

**本题开启捆绑测试。**

|$\text{Subtask}$|分值|$n\le$|$m\le$|
|:-:|:-:|:-:|:-:|
|$0$|$10$|$5$|$200$|
|$1$|$30$|$20$|$10^6$|
|$2$|$60$|$10^5$|$2^{63}-1$|

对于 $100\%$ 的数据，$1\le n\le10^5$，$1\le m\le2^{63}-1$，$1\le t\le50$。


---

---
title: "[USACO23JAN] Moo Route S"
layout: "post"
diff: 普及-
pid: P9015
tag: ['贪心', 'USACO', '2023', 'Special Judge', '构造']
---
# [USACO23JAN] Moo Route S
## 题目描述

Farmer Nhoj dropped Bessie in the middle of nowhere! At time $t=0$, Bessie is located at $x=0$ on an infinite number line. She frantically searches for an exit by moving left or right by $1$ unit each second. However, there actually is no exit and after $T$ seconds, Bessie is back at $x=0$, tired and resigned.

Farmer Nhoj tries to track Bessie but only knows how many times Bessie crosses $x=0.5,1.5,2.5, \cdots ,(N−1).5$, given by an array $A_0,A_1, \cdots ,A_{N−1} (1 \le N \le 10^5, 1 \le A_i \le 10^6, \sum A_i \le 10^6)$. Bessie never reaches $x>N$ nor $x<0$.

In particular, Bessie's route can be represented by a string of $T= \sum\limits_{i=0}^{N-1}A_i$
$L$s and $R$s where the $i$-th character represents the direction Bessie moves in during the ith second. The number of direction changes is defined as the number of occurrences of $LR$s plus the number of occurrences of $RL$s.

Please help Farmer Nhoj find any route Bessie could have taken that is consistent with A
and minimizes the number of direction changes. It is guaranteed that there is at least one valid route. 
## 输入格式

The first line contains $N$. The second line contains $A_0,A_1,\cdots ,A_{N−1}$. 
## 输出格式

Output a string $S$ of length $T=\sum\limits_{i=0}^{N-1}A_i$ where $S_i$ is `L` or `R`, indicating the direction Bessie travels in during second $i$. If there are multiple routes minimizing the number of direction changes, output any. 
## 样例

### 样例输入 #1
```
2
2 4
```
### 样例输出 #1
```
RRLRLL
```
### 样例输入 #2
```
3
2 4 4
```
### 样例输出 #2
```
RRRLLRRLLL
```
## 提示

### Explanation for Sample 1

There is only $1$ valid route, corresponding to the route $0 \rightarrow 1 \rightarrow 2 \rightarrow 1 \rightarrow 2 \rightarrow 1 \rightarrow 0$. Since this is the only possible route, it also has the minimum number of direction changes. 

### Explanation for Sample 2

There are $3$ possible routes:

RRLRRLRLLL  
RRRLRLLRLL  
RRRLLRRLLL  

The first two routes have $5$ direction changes, while the last one has only $3$. Thus the last route is the only correct output.

### Scoring

 - Inputs $3-5$: $N \le 2$
 - Inputs $3-10$: $T=A_0+A_1+ \cdots +A_{N−1} \le 5000$
 - Inputs $11-20$: No additional constraints.
## 题目翻译

奶牛贝西开始在一条数轴上原点的位置，每次会向左或向右移动一个单位长度，最后回到了原点。

给定贝西经过 $0.5,1.5,\ldots,(N-1)+0.5$ 的次数（用数组 $A$ 表示，$A_i$ 表示经过 $i+0.5$ 的次数）。

请构造出一条可能的移动路径（由 $\texttt{L}$ 和 $\texttt{R}$ 构成，表示向左 / 向右走），使得中途**改变方向的次数尽量少**。

题目保证有解，若有多解，输出**任意**一组解即可。

翻译自 @[zyc212303](https://www.luogu.com.cn/user/556366)


---

---
title: "「KDOI-04」XOR Sum"
layout: "post"
diff: 普及-
pid: P9033
tag: ['洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 「KDOI-04」XOR Sum
## 题目背景

凯文一眼秒了这题。

![](https://cdn.luogu.com.cn/upload/image_hosting/lh1xvu75.png)
## 题目描述

给定一个正整数 $n$，请构造一个长度为 $n$ 的**非负整数**序列 $a_1,a_2,\dots,a_n$，满足：

+ 对于所有 $1\le i\le n$，都有 $0\le a_i\le m$。
+ $a_1\oplus a_2\oplus\dots\oplus a_n=k$。其中 $\oplus$ 表示[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677)运算。

或者判断不存在这样的序列。
## 输入格式

**本题包含多组测试数据。**

输入的第一行包含一个正整数 $T$，表示测试数据组数。

对于每组测试数据，输入包含一行三个非负整数 $n,k,m$。
## 输出格式

对于每组测试数据，输出一行一个 $-1$ 表示没有这样的序列存在。

否则，输出 $n$ 个用空格分隔的**非负整数**，表示你所构造的序列。如果有多个合法的答案，你只需要输出其中任意一种。
## 样例

### 样例输入 #1
```
5
1 2 2
2 3 10
2 11 8
20 200000 99999
11 191 9810
```
### 样例输出 #1
```
2 
4 7 
8 3 
-1
191 191 191 191 191 191 191 191 191 191 191 
```
## 提示

**【样例解释】**

对于第 $1$ 组测试数据，有且仅有一个序列满足条件。

对于第 $2$ 组测试数据，由于 $4\oplus 7=3$ 且 $4,7\le10$，所以这是一个合法的答案。同样地，序列 $(2,1)$ 也是一个合法的答案。

对于第 $4$ 组测试数据，可以证明不存在满足要求的序列。

**【数据范围】**

记 $\sum n$ 为单个测试点中所有 $n$ 的值之和。

对于所有测试数据，保证 $1\le T\le 1~000$，$1\le n\le 2\cdot10^5$，$0\le m,k\le 10^8$，$\sum n\le 2\cdot10^5$。

**【子任务】**

**本题开启捆绑测试。**

+ Subtask 1 (18 pts)：$k\le m$。
+ Subtask 2 (82 pts)：没有额外的约束条件。


---

---
title: "[PA 2021] Zakłócenia"
layout: "post"
diff: 普及-
pid: P9048
tag: ['贪心', '2021', 'Special Judge', '构造', 'PA（波兰）']
---
# [PA 2021] Zakłócenia
## 题目描述

定义一种小写字母到 $8$ 位 01 串的映射：

- 将小写字符的 ASCII 码转为 $8$ 位二进制数，如：$a \rightarrow 97 \rightarrow 01100001$。

现在小 A 有一个长度为 $n$ 的只含小写字母的字符串 $s$，他将这个字符串映射到了一个长为 $8n$ 的 01 字符串 $t$。

他打乱了 01 串 $t$ 得到 01 串 $t'$，请你根据打乱后的结果还原出一个 $s$。
## 输入格式

第一行，一个整数 $n$；

第二行，一个长为 $8n$ 的 01 串 $t'$。
## 输出格式

如果有解，输出一行，一个长度为 $n$ 的只含小写字母的字符串 $s$；否则，输出 `NIE`。

**如有多解，输出任意一组均可。**
## 样例

### 样例输入 #1
```
2
1100000011110111
```
### 样例输出 #1
```
ao
```
### 样例输入 #2
```
8
1011111010101100011011011010001010100011111111110001001001011010

```
### 样例输出 #2
```
potyczki
```
### 样例输入 #3
```
1
00011000
```
### 样例输出 #3
```
NIE
```
## 提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$。


---

---
title: "「DROI」Round 2 构造与取模"
layout: "post"
diff: 普及-
pid: P9373
tag: ['Special Judge', '构造']
---
# 「DROI」Round 2 构造与取模
## 题目背景

与其编写苍白无力的背景，不如出更有质量的题。


## 题目描述

对于整数 $n,k$，若存在**非负整数** $x$ 与 **正整数** $y$ 满足：

$$x + y = n\ \land\ x \bmod y =k$$

则我们称有序数对 $(x,y)$ 是 $n$ 的一个 **优秀拆分**（其中 $\land$  是**并且**的意思）。

现给定非负整数 $n,k$，请你构造**任意**一组 $n$ 的优秀拆分，并分别输出你构造方案中的 $x$ 和 $y$。特殊地，若不存在这样的拆分，则输出 `-1`。
## 输入格式

**本题有多组数据。**

第一行一个正整数 $T$，表示数据组数。

接下来 $T$ 行，每行两个非负整数，分别为 $n,k$。
## 输出格式

输出共 $T$ 行，第 $i$ 行表示第 $i$ 组数据的答案。
## 样例

### 样例输入 #1
```
3
1 0
13 3
198818800000 122122200000
```
### 样例输出 #1
```
0 1
8 5
-1
```
## 提示

#### 样例解释

对于第一组数据，只存在唯一的构造方式。

对于第二组数据，$(3,10)$ 也是一组合法的构造。

对于第三组数据，可以证明不存在一组合法的构造。

------------

#### 数据范围

**「本题采用捆绑测试」**

- $\operatorname{Subtask} 1(20\%)$：$n \leq 10^6$。

- $\operatorname{Subtask} 2(40\%)$：$n \leq 10^{12}$。

- $\operatorname{Subtask} 3(40\%)$：无特殊限制。

对于 $100\%$ 的数据：$T \leq 5$，$0 \leq n,k \leq 10^{18}$。


---

---
title: "「DBOI」Round 1 DTTM"
layout: "post"
diff: 普及-
pid: P9397
tag: ['贪心', 'Special Judge', 'O2优化', '排序', '构造']
---
# 「DBOI」Round 1 DTTM
## 题目背景

张则雨和穆制程坐在天台上看着满天的星辰。在他们的世界，流行一种连接星星的活动。他们对此有一种浪漫的诠释：如果连不完，剩下的一颗星星就是身旁的人；如果连得完，那身边的人和自己都是星星。
## 题目描述

星空中有 $n$ 颗星星，第 $i$ 颗位于坐标 $(x_i,y_i)$。你需要把星星连接成满足张则雨的如下需求：

- 每一颗星星都是且仅是一条线段的端点，所有线段互不相交（包括端点）。
- 所有线段左右端点 $|x_l-x_r|$ 之和有最小值。 

然而张则雨有点笨，并不知道应该怎么连。穆制程知道你是地球上最聪明的人，于是告诉你 $n$ 颗星星的坐标，你需要输出连接方案或者报告无解。
## 输入格式

第一行 $n$ 表示星星的数量。

从第二行开始，共 $n$ 行，每行两个整数。第 $i+1$ 行表示第 $i$ 颗星星的 $(x_i,y_i)$ 坐标。 
## 输出格式

第一行输出所有线段左右端点 $|x_l-x_r|$ 的和的最小值。

接下来每一行输出两个编号，表示为了得到最小值，你每条线段连接的星星的编号。

如果有多种可能的连接方案，输出任意一种。如果无解在第一行输出 $-1$。
## 样例

### 样例输入 #1
```
4
1 3
2 2
2 1
3 4
```
### 样例输出 #1
```
2
1 4
2 3
```
### 样例输入 #2
```
6
1 5
2 3
2 4
2 5
2 -1
3 -3
```
### 样例输出 #2
```
2
1 3
4 6
2 5
```
## 提示

样例 1 的方案如图：

![](https://s1.ax1x.com/2023/04/06/ppomH5q.png)

样例 2 的方案如图：

![](https://s1.ax1x.com/2023/04/06/ppomDDH.png)

**本题使用捆绑测试与子任务依赖。**

| $\rm Subtask$ | $n\leqslant$ | $(x,y)$ | 特殊性质 | 得分 | 子任务依赖 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $10$ | $0\leqslant x,y\leqslant 20$ | 无 | $10$ | 无 |
| $2$ | $10^3$ | $0\leqslant x,y\leqslant10^3$ | 无 | $15$ | $1$ |
| $3$ | $10^3$ | $0\leqslant x,y\leqslant10^9$ | 无 | $15$ | $1,2$ |
| $4$ | $5\times10^5$ |$-10^9\leqslant x,y\leqslant10^9$  | $A$ | $5$ | 无 |
| $5$ | $5\times10^5$ | $-10^3\leqslant x,y\leqslant10^3$ | 无 | $20$ | $1,2$
| $6$ | $5\times10^5$ | $-10^9\leqslant x,y\leqslant10^9$ | 无 | $35$ | $1,2,3,4,5$


特殊性质 $A$：满足所有 $x_i$ 都相等。

保证对于 $100\%$ 的数据，$1\leqslant n\leqslant5\times 10^5$，$0\leqslant|x|,|y|\leqslant 10^9$ 且对于任意 $i\ne j$，有 $(x_i,y_i)\neq (x_j,y_j)$。


---

---
title: "「SFCOI-3」进行一个拆的解"
layout: "post"
diff: 普及-
pid: P9492
tag: ['2023', '洛谷原创', 'O2优化', '构造']
---
# 「SFCOI-3」进行一个拆的解
## 题目背景

**公告：Subtask 0 数据有误，现已更改。**

------------

三岁的小明非常不喜欢完整的东西，他甚至连序列都想要拆掉。
## 题目描述

给定序列 $a_1\dots a_n$，小明想要把它拆成两个子段 $[1, l][l + 1, n](1 \leq l \lt n)$，即 $a_1\dots a_l$ 和 $a_{l+1}\dots a_n$。

由于小明强迫症很严重，他不希望对于这两个子段，其中一个是另一个的 **子序列**，换句话说，他不希望其中一个子段可以通过删掉若干（可能为 $0$）个元素变成另一个。

在父母出门的时候，小明终于找到了把序列拆开的机会！所以，他想知道，是否存在一种拆解的方式满足：任意一个子段都不是另一个子段的子序列。
## 输入格式

第一行一个整数 $T$，表示小明总共要拆解 $T$ 个序列。接下来 $T$ 行，每行描述一个序列：

+ 每行第一个整数 $n$，表示序列长度；
+ 接下来 $n$ 个整数，依次代表序列中每一个数。
## 输出格式

输出共 $T$ 行。

对于每轮游戏，若存在满足条件的序列，输出 `YES`，否则输出 `NO`。
## 样例

### 样例输入 #1
```
2
5 1 2 1 2 1
7 1 2 1 1 2 1 0
```
### 样例输出 #1
```
NO
YES
```
## 提示

### 样例解释

对于第一个序列，所有拆分方式有：

- $\lbrace 1 \rbrace,\lbrace 2,1,2,1 \rbrace$。
- $\lbrace 1,2 \rbrace,\lbrace 1,2,1 \rbrace$。
- $\lbrace 1,2,1 \rbrace,\lbrace 2,1 \rbrace$。
- $\lbrace 1,2,1,2 \rbrace,\lbrace 1 \rbrace$。

从任何地方拆开都是不合法的——较短的那个序列都是另一个序列的子序列。

对于第二个序列，其中一种合理的拆分方式为 
$\lbrace 1,2,1,1,2 \rbrace,\lbrace 1,0 \rbrace$。

### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 0（15 points）：$a_i = 0$。
- Subtask 1（15 points）：$n = 10$，保证数据随机生成。
- Subtask 2（30 points）：$n$ 为偶数。
- Subtask 3（40 points）：无特殊限制。

对于所有数据，$1\leq T \leq 10^5$，$2 \leq n \leq 10^5$，$1 \leq \sum n \leq 10^6$，$0 \leq a_i \leq 100$。


---

---
title: "『STA - R3』存在"
layout: "post"
diff: 普及-
pid: P9508
tag: ['Special Judge', 'O2优化', '构造']
---
# 『STA - R3』存在
## 题目描述

构造一个长度为 $n$ 的序列，满足对于任意长度不小于 2 的子区间存在主元素。在此基础上，要求序列元素的种类数最大。其中序列的主元素定义为出现次数不小于序列长度的一半的数。

你构造的数列中每个元素必须是 $0$ 到 $10^9$ 之间的整数。
## 输入格式

一行一个正整数 $n$。
## 输出格式

一行 $n$ 个整数，表示你构造出的序列。如果有多种答案，输出任意一种即可。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
1 1 2
```
## 提示

**本题采用捆绑测试。**

数据范围：
- Subtask 1 (10pts)：$n\le 5$。
- Subtask 2 (40pts)：$n$ 是 $3$ 的倍数。
- Subtask 3 (50pts)：无特殊限制。

对于全部数据，$1\le n\le 10^3$。


---

---
title: "「AWOI Round 2 B」树学"
layout: "post"
diff: 普及-
pid: P9539
tag: ['字符串', '贪心', '构造']
---
# 「AWOI Round 2 B」树学
## 题目背景

HR 刚做完一个简单而又靓丽的题目，它想来试试这道题，可是它太蒻了，不会做，您能帮帮它吗？
## 题目描述

构造一个长度为 $n$ 的小写字母串，要求和给定的长度为 $n$ 的小写字母串 $s$ 的相似度在 $[l,r]$ 范围内。

定义两个长度都为 $n$ 的字符串 $a,b$ 的相似度为 $\sum^{n}_{i=1}[a_i=b_i]$。

您需要使构造出的字符串的字典序尽量小。
## 输入格式

第一行三个正整数 $n,l,r$。

接下来一行一个字符串，表示给定的小写字母串 $s$。
## 输出格式

输出一行一个字符串，表示您构造的字典序最小的可行字符串。
## 样例

### 样例输入 #1
```
3 1 2
aab
```
### 样例输出 #1
```
aaa
```
### 样例输入 #2
```
4 4 4
awoi

```
### 样例输出 #2
```
awoi
```
## 提示

**【数据规模】**


**本题使用捆绑测试。**

| 子任务编号 | $n\leqslant$ | 特殊性质 | 分值 |
| -----------: | -----------: | -----------: | -----------: |
| $1$ | $100$ | 无 | $20$ |
| $2$ | $10^6$ | A | $10$ |
| $3$ | $10^6$ | B | $10$ |
| $4$ | $10^6$ | 无 | $60$ |

特殊性质 A：$l=r=n$ 或 $l=0,r=n$。

特殊性质 B：$s$ 的每一位都为 `a` 或都不为 `a`。

对于 $100\%$ 的数据，$1 \leqslant n \leqslant 10^6$，$0 \leqslant l \leqslant r \leqslant n$，$s$ 的长度为 $n$。

**【工作人员】**
| $\text{Idea}$ | $\text{Data}$ | $\text{Check}$ | $\text{Solution}$ |
| :----------: | :----------: | :----------: | :----------: | 
| [玄学OIER荷蒻](/user/671294) | [QwQ666\_666](/user/677609) & [玄学OIER荷蒻](/user/671294) | [QwQ666\_666](/user/677609)| [玄学OIER荷蒻](/user/671294) |


---

---
title: "『GROI-R2』 紫水晶"
layout: "post"
diff: 普及-
pid: P9652
tag: ['数学', '洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 『GROI-R2』 紫水晶
## 题目描述

爱丽丝不曾忘记过她曾经存在于纸牌的世界。

于是魔法让她的手里出现了一些牌，同时魔法也让坦尼尔手里出现了一些牌，而且每张牌上都写着一个正整数——尽管他们如今所处的，是玻璃王国的世界中。

牌张很快一消而散，而他们也准备启程。爱丽丝只记住了每相邻两张牌的**最大公约数之和**，坦尼尔只记住了每相邻两张牌的**最小公倍数之和**。

你还在这个宫殿里，你想重现当时的牌张。

**形式化题面**

给定 $q$ 次询问，每次询问为以下两种之一：

- ``1 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \gcd(a_i,a_{i+1})=x$。

- ``2 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \operatorname{lcm}(a_i,a_{i+1})=x$。

且对于任意输出的 $a_i$ 不应超出 C++ 语言中 ``int`` 的存储范围。

其中 $\gcd$ 和 $\operatorname{lcm}$ 分别为最大公约数和最小公倍数，如有多解，输出任意一个即可。如果无解，输出 ``-1``。
## 输入格式

第一行输入一个正整数 $q$ 表示询问次数。

接下来 $q$ 行，每行输入三个正整数 $op,n,x$。

- 当 $op=1$ 时表示爱丽丝的牌张数为 $n$，她记住的和为 $x$，要求还原她的牌张。

- 当 $op=2$ 时表示坦尼尔的牌张数为 $n$，他记住的和为 $x$，要求还原他的牌张。
## 输出格式

一共 $q$ 行，每行输出一个整数序列对应每次询问你构造的牌张序列，序列中相邻的两个数用一个空格隔开。

如有多解，你可以输出任意一个。如果无解，输出 ``-1``。
## 样例

### 样例输入 #1
```
5
1 5 4
2 3 8
1 5 10
2 6 34
1 3 1
```
### 样例输出 #1
```
1 1 1 1 1
2 2 3
1 1 1 7 7
1 1 4 5 1 4
-1
```
## 提示

**数据范围**

**本题采用捆绑测试**。

| $\text{Subtask}$ | $\sum n\le$ | $x\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $5$ | $10$ | | $10$ |
| $2$ | $50$ | $200$ | | $20$ |
| $3$ | $5\times 10^5$ | $2^{31}-1$ | $\text{A}$ | $15$ |
| $4$ | $5\times 10^5$ | $2^{31}-1$ | $\text{B}$ | $15$ |
| $5$ | $5\times 10^5$ | $2^{31}-1$ | | $40$ |

特殊性质 $\text{A}$：保证对于任意询问满足 $op=1$。

特殊性质 $\text{B}$：保证对于任意询问满足 $op=2$。

对于 $100\%$ 的数据满足 $2\le n\le 5\times 10^5$，$2\le \sum n\le 5\times 10^5$，$1\le x \le 2^{31}-1$，$op\in\{1,2\}$。



---

---
title: "Maps."
layout: "post"
diff: 普及-
pid: P9687
tag: ['贪心', '洛谷原创', 'O2优化', '构造', '洛谷月赛']
---
# Maps.
## 题目描述

小 Y 希望得到一幅地图，这份地图有些与众不同。

这份地图是一幅长为 $n$ 个单位，宽为一个单位的网格图，每个网格必须被涂鸦成白色（$0$）或者黑色（$1$）。

你希望满足小 Y 的愿望送给他一幅这样的地图，但是这时小 Y 又提出了两点要求：

- 对于每个不在网格图两端的白色格子，恰好有 $p$ 个满足它的左右两个格子都被涂鸦成黑色。
- 在满足上述所有条件的情况下，这幅地图从左到右的字符构成的字符串的字典序最小。

你心想，这些要求也是小菜一碟，于是开始了你的创作。
## 输入格式

本题有多组数据。

第一行一个正整数 $T$，表示数据组数。

对于每组数据：

输入共一行两个整数 $n,p$，表示你需要构造的地图的长度和小 Y 对你的要求。


## 输出格式

对于每组数据：输出一行一个长度为 $n$ 的 01 字符串，表示你构造的地图；如果无法找到任何一幅地图满足小 Y 的要求，输出 $-1$。
## 样例

### 样例输入 #1
```
5
5 1
3 1
5 3
5 4
5 5
```
### 样例输出 #1
```
00101
101
-1
-1
-1
```
## 提示

#### 【样例解释 #1】

对于第一组数据：只有位于第 $4$ 个字符上的数，满足本身是 $0$，不在地图边缘且周围两个都是 $1$，因此符合条件。可以证明这是满足条件的字典序最小的方案。

对于第三组数据：可以证明没有任何一个解满足长度为 $5$ 且有 $3$ 个数本身是 $0$，不在地图边缘且周围两个字符都是 $1$。

#### 【数据范围】

对于所有测试数据，满足 $1 \le T \le 100$，$1 \le n,p \le 10^5$。

**本题开启捆绑测试，所有数据范围均相同的测试点捆绑为一个 $\text{Subtask}$。**

各测试点的附加限制如下表所示。

| 测试点 | $n,p \le$ |
| :-----------: | :-----------: |
| $1 \sim 3$ | $10$ |
| $4 \sim 5$ | $10^3$ |
| $6\sim 10$ | $10^5$ |


---

