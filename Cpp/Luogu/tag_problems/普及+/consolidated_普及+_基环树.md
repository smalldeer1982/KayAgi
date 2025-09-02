---
title: "[ROIR 2019] 探险队 (Day 2)"
layout: "post"
diff: 普及+/提高
pid: P11501
tag: ['动态规划 DP', '2019', 'Special Judge', '树形 DP', '基环树', 'ROIR（俄罗斯）']
---
# [ROIR 2019] 探险队 (Day 2)
## 题目背景

翻译自 [ROIR 2019 D2T3](https://neerc.ifmo.ru/school/archive/2018-2019/ru-olymp-regional-2019-day2.pdf)。
## 题目描述

需要派遣一支探险队前去探索邻近的星系。共有 $n$ 名候选人，编号从 $1$ 到 $n$，探险队成员需要从中选出。

在候选人中进行了一次调查，每个人可以指出一个他不愿意与之一起参加探险的候选人。对于第 $i$ 个候选人，调查结果是一个整数 $a_{i}$，表示他不愿意与编号为 $a_i$ 的人一起参加探险。如果 $i$ 号候选人愿意与任何人一起参加探险，则 $a_{i} = -1$。

你需要求出在满足所有派遣出的候选人的意愿的情况下，最大的可以派遣的人数。
## 输入格式

第一行输入一个整数 $n$。

接下来 $n$ 行，每行输入一个整数，分别是 $a_1,a_2,\dots,a_n$。
## 输出格式

输出一个整数，表示最大可以派遣的人数。
## 样例

### 样例输入 #1
```
4
2
4
2
1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3
2
-1
2
```
### 样例输出 #2
```
2
```
## 提示

数据中 Subtask 0 为样例。

| 子任务 | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $1$ | $19$ | $n\le20$ |
| $2$ | $10$ | $a_1=-1$，$\forall i>1,a_i=i-1$ |
| $3$ | $15$ | $a_i<i$ |
| $4$ | $13$ | $1\le n\le2000$ |
| $5$ | $43$ | 无特殊性质 |

对于 $100\%$ 的数据，$n\le3\times10^5$，$a_i=-1$ 或 $1\le a_i\le n$，且 $a_i\ne i$。


---

---
title: "[POI 2004] SZP"
layout: "post"
diff: 普及+/提高
pid: P1543
tag: ['搜索', '贪心', '2004', 'POI（波兰）', '树形 DP', '拓扑排序', '基环树']
---
# [POI 2004] SZP
## 题目背景

一班班花 [$\color{red}{\texttt{y}}\color{black}{\texttt{hb}}$](/user/835809) 十分可爱。
## 题目描述

班花 [$\color{red}{\texttt{y}}\color{black}{\texttt{hb}}$](/user/835809) 作为某日的值日班长，在自习课上管理着 $n$ 名同学。除了她以外每一名同学都监视着另一名同学。现在班花 [$\color{red}{\texttt{y}}\color{black}{\texttt{hb}}$](/user/835809) 需要选择尽量多的同学去搬卷子和答题卡，且使得对于这些同学中的每一名同学，至少有一位监视她的同学没有被选中。问班花 [$\color{red}{\texttt{y}}\color{black}{\texttt{hb}}$](/user/835809) 最多可以选择多少同学。

由于班花 [$\color{red}{\texttt{y}}\color{black}{\texttt{hb}}$](/user/835809) 太可爱了，所以没有人监视她，也可以认为她的学号是 $0$。

如果一个人没有被监视，那么她就不能被选择。

## 输入格式

第一行只有一个整数，$n$ 代表同学的数量。同学的学号从 $1$ 到 $n$ 编号。

接下来 $n$ 行每行一个整数 $a_k$ 表示同学 $k$ 将要监视同学 $a_k$，$1 \le k \le n$，$1 \le a_k \le n$，$a_k \ne k$。
## 输出格式

一个数，最多能有多少同学参加入这个任务。
## 样例

### 样例输入 #1
```
6
2
3
1
3
6
5

```
### 样例输出 #1
```
3
```
## 提示

对于 $100\%$ 的数据，$1\le k,a_k\le n\le 10^6$。


---

---
title: "Ryoku 的探索"
layout: "post"
diff: 普及+/提高
pid: P6037
tag: ['2020', '深度优先搜索 DFS', '基环树']
---
# Ryoku 的探索
## 题目背景

Ryoku 对自己所处的世界充满了好奇，她希望能够在她「死」之前尽可能能多地探索世界。

这一天，Ryoku 得到了一张这个世界的地图，她十分高兴。然而，Ryoku 并不知道自己所处的位置到底在哪里，她也不知道她会什么时候死去。她想要知道如何才能尽可能多的探索这个世界。
## 题目描述

Ryoku 所处的世界可以抽象成一个有 $n$ 个点， $n$ 条边的带权无向连通图 $G$。每条边有美观度和长度。

Ryoku 会使用这样一个策略探索世界：在每个点寻找一个**端点她未走过**的边中**美观度最高**的走，如果没有边走，就沿着她前往这个点的边返回，类似于图的**深度优先遍历**。

探索的一个方案的长度是这个方案所经过的所有边长度的和（返回时经过的长度不用计算）。

她想知道，对于每一个起点 $s=1,2,\cdots,n$，她需要走过的长度是多少？


## 输入格式

输入包含 $n + 1$  行，其中第一行包含一个整数 $n$。  
接下来 $n$ 行每行包含四个整数 $u,v,w,p$，描述了一条连接 $u$ 和 $v$，长度为 $w$，美观度为 $p$ 的无向边。
## 输出格式

输出包含 $n$ 行，每行一个整数，第 $i$ 行为 $s=i$ 时的答案。
## 样例

### 样例输入 #1
```
5
4 1 2 1
1 2 3 2
3 1 1 4
3 5 2 5
2 3 2 3

```
### 样例输出 #1
```
7
7
8
7
8
```
## 提示

**【样例 1 说明】**

以下为输入输出样例 1 中的图： （边上红色数组为 $p$，黑色为 $w$）

![](https://cdn.luogu.com.cn/upload/image_hosting/rmk07281.png)

若起点为 $1$，顺序为 $1\to3\to5\to2\to4$，长度之和为 $7$。  
若起点为 $2$，顺序为 $2\to3\to5\to1\to4$，长度之和为 $7$。  
若起点为 $3$，顺序为 $3\to5\to1\to2\to4$，长度之和为 $8$。  
若起点为 $4$，顺序为 $4\to1\to3\to5\to2$，长度之和为 $7$。  
若起点为 $5$，顺序为 $5\to3\to1\to2\to4$，长度之和为 $8$。  

---

**【数据规模与约定】**

对于 $40\%$ 的数据，$n\le 10^3$。    
对于 $100\%$ 的数据，$3 \le n \le 10^6$，$1 \le u,v,p \le n$，$0\le w\le 10^9$，保证 $p$ 互不相同。


---

---
title: "[USACO22OPEN] Visits S"
layout: "post"
diff: 普及+/提高
pid: P8269
tag: ['USACO', '2022', '拓扑排序', '连通块', '强连通分量', '基环树']
---
# [USACO22OPEN] Visits S
## 题目描述

Bessie 的 $N$（$2\le N\le 10^5$）个奶牛伙伴（编号为 $1\cdots N$）每一个都拥有自己的农场。对于每个 $1\le i\le N$，伙伴 i 想要访问伙伴 $a_i$（$a_i\neq i$）。

给定 $1\ldots N$ 的一个排列 $(p_1,p_2,\ldots, p_N)$，访问按以下方式发生。

对于 $1$ 到 $N$ 的每一个 $i$：

- 如果伙伴 $a_{p_i}$ 已经离开了她的农场，则伙伴 $p_i$ 仍然留在她的农场。
- 否则，伙伴 $p_i$ 离开她的农场去访问伙伴 $a_{p_i}$ 的农场。这次访问会产生快乐的哞叫 $v_{p_i}$ 次（$0\le v_{p_i}\le 10^9$）。


对于所有可能的排列 $p$，计算所有访问结束后可能得到的最大哞叫次数。
## 输入格式

输入的第一行包含 $N$。

对于每一个 $1\le i\le N$，第 $i+1$ 行包含两个空格分隔的整数 $a_i$ 和 $v_i$。
## 输出格式

输出一个整数，为所求的答案。

**注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C/C++ 中的 "long long"）。**
## 样例

### 样例输入 #1
```
4
2 10
3 20
4 30
1 40
```
### 样例输出 #1
```
90
```
## 提示

【样例解释】


如果 $p=(1,4,3,2)$，则

- 伙伴 $1$ 访问伙伴 $2$ 的农场，产生 $10$ 次哞叫。
- 伙伴 $4$ 看到伙伴 $1$ 已经离开了农场，所以无事发生。
- 伙伴 $3$ 访问伙伴 $4$ 的农场，又产生 $30$ 次哞叫。
- 伙伴 $2$ 看到伙伴 $3$ 已经离开了农场，所以无事发生。

这样总计得到了 $10+30=40$ 次哞叫。

另一方面，如果 $p=(2,3,4,1)$，则

- 伙伴 $2$ 访问伙伴 $3$ 的农场，产生 $20$ 次哞叫。
- 伙伴 $3$ 访问伙伴 $4$ 的农场，产生 $30$ 次哞叫。
- 伙伴 $4$ 访问伙伴 $1$ 的农场，产生 $40$ 次哞叫。
- 伙伴 $1$ 看到伙伴 $2$ 已经离开了农场，所以无事发生。

这样总计得到了 $20+30+40=90$ 次哞叫。可以证明这是所有可能的排列 $p$ 中访问结束后得到的最大可能的哞叫次数。


---

---
title: "[USACO23JAN] Find and Replace S"
layout: "post"
diff: 普及+/提高
pid: P9013
tag: ['USACO', '2023', '图论建模', '基环树']
---
# [USACO23JAN] Find and Replace S
## 题目描述

Bessie is using the latest and greatest innovation in text-editing software, miV! She starts with an input string consisting solely of upper and lowercase English letters and wishes to transform it into some output string. With just one keystroke, miV allows her to replace all occurrences of one English letter $c_1$ in the string with another English letter $c_2$. For example, given the string `aAbBa`, if Bessie selects $c_1$ as `a` and $c_2$ as `B`, the given string transforms into `BAbBB`.

Bessie is a busy cow, so for each of $T
(1 \le T \le 10)$ independent test cases, output the minimum number of keystrokes required to transform her input string into her desired output string. 
## 输入格式

The first line contains $T$, the number of independent test cases.

The following $T$ pairs of lines contain an input and output string of equal length. All characters are upper or lowercase English letters (either `A` through `Z` or `a` through `z`). The sum of the lengths of all strings does not exceed $10^5$. 
## 输出格式

For each test case, output the minimum number of keystrokes required to change the input string into the output string, or $−1$ if it is impossible to do so. 
## 样例

### 样例输入 #1
```
4
abc
abc
BBC
ABC
abc
bbc
ABCD
BACD
```
### 样例输出 #1
```
0
-1
1
3
```
## 提示

### Explanation for Sample 1

The first input string is the same as its output string, so no keystrokes are required.

The second input string cannot be changed into its output string because Bessie cannot change one `B`' to `A` while keeping the other as `B`.

The third input string can be changed into its output string by changing `a` to `b`.

The last input string can be changed into its output string like so: $\texttt{ABCD} \rightarrow \texttt{EBCD} \rightarrow \texttt{EACD} \rightarrow \texttt{BACD}$.

### Scoring

 - Inputs $2-6$: Every string has a length at most $50$.
 - Inputs $7-9$: All strings consist only of lowercase letters `a` through `e`
 - Inputs $10-15$: No additional constraints.
## 题目翻译

### 题目描述

Bessie 正在使用世界上最先进最伟大的文本编辑器：miV！她想将一个仅由大写和小写英文字母组成的字符串转换为一个新的字符串。每一次操作，miV 可以将字符串中所有的字母  $c_1$ 替换成另一种字母 $c_2$。例：对于字符串`aAbBa`, 如果将其中的 `a` 替换成 `B`, 那么字符串会变为`BAbBB`。

Bessie 非常地忙碌, 所以对于给出的 $T
(1 \le T \le 10)$ 组测试数据, 请输出她至少需要多少次操作才能把原字符串转换为新字符串。

### 输入格式

第一行是一个整数 $T$, 表示测试数据的数量。

接下来有 $T$ 对长度相等的字符串。字符串中所有的字符都是大写或小写的字母。字符串的长度不会超过 $10^5$。

### 输出格式

对于每组测试数据，输出转换字符串需要的最小操作数。

如果这不可能做到，输出 $-1$。

### 样例 1 解释

第一组数据：两个字符串相等，所以不需要任何操作。

第二组数据：你不可能在把其中一个 `B` 转换为 `A`的同时保持剩下一个 `B` 不变。

第三组数据：你可以把字符串中所有的 `a` 转换为 `b`。

第四组数据：你可以按 $\texttt{ABCD} \rightarrow \texttt{EBCD} \rightarrow \texttt{EACD} \rightarrow \texttt{BACD}$ 的方式转换。

### 数据范围

 - 对于 $ 40 \% $ 的数据，字符串的长度不超过 $50$。
 - 对于另外 $ 20\% $ 的数据，所有的字符串仅包含从 `a` 到 `e` 的小写字母。
 - 对于 $ 100\% $ 的数据，字符串的长度不超过 $10^5$，$1 \le T \le 10$。


---

---
title: "[NOIP2023] 三值逻辑"
layout: "post"
diff: 普及+/提高
pid: P9869
tag: ['并查集', '2023', 'NOIP 提高组', 'O2优化', '二分图', '基环树']
---
# [NOIP2023] 三值逻辑
## 题目描述

小 L 今天学习了 Kleene 三值逻辑。

在三值逻辑中，一个变量的值可能为：真（$\mathit{True}$，简写作 $\mathit{T}$）、假（$\mathit{False}$，简写作 $\mathit{F}$）或未确定（$\mathit{Unknown}$，简写作 $\mathit{U}$）。

在三值逻辑上也可以定义逻辑运算。由于小 L 学习进度很慢，只掌握了逻辑非运算 $\lnot$，其运算法则为：
$$\lnot \mathit{T} = \mathit{F}, \lnot \mathit{F} = \mathit{T}, \lnot\mathit{U} = \mathit{U}.$$

现在小 L 有 $n$ 个三值逻辑变量 $x_1,\cdots, x_n$。小 L 想进行一些有趣的尝试，于是他写下了 $m$ 条语句。语句有以下三种类型，其中 $\leftarrow$ 表示赋值：

1. $x_i \leftarrow v$，其中 $v$ 为 $\mathit{T}, \mathit{F}, \mathit{U}$ 的一种；
2. $x_i \leftarrow x_j$；
3. $x_i \leftarrow \lnot x_j$。

一开始，小 L 会给这些变量赋初值，然后按顺序运行这 $m$ 条语句。

小 L 希望执行了所有语句后，所有变量的最终值与初值都相等。在此前提下，小 L 希望初值中 $\mathit{Unknown}$ 的变量尽可能少。

在本题中，你需要帮助小 L 找到 $\mathit{Unknown}$ 变量个数最少的赋初值方案，使得执行了所有语句后所有变量的最终值和初始值相等。小 L 保证，至少对于本题的所有测试用例，这样的赋初值方案都必然是存在的。
## 输入格式

**本题的测试点包含有多组测试数据。**

输入的第一行包含两个整数 $c$ 和 $t$，分别表示测试点编号和测试数据组数。对于样例，$c$ 表示该样例与测试点 $c$ 拥有相同的限制条件。

接下来，对于每组测试数据：

- 输入的第一行包含两个整数 $n$ 和 $m$，分别表示变量个数和语句条数。
- 接下来 $m$ 行，按运行顺序给出每条语句。
  - 输入的第一个字符 $v$ 描述这条语句的类型。保证 $v$ 为 `TFU+-` 的其中一种。
  - 若 $v$ 为 `TFU` 的某一种时，接下来给出一个整数 $i$，表示该语句为 $x_i \leftarrow v$；
  - 若 $v$ 为 `+`，接下来给出两个整数 $i,j$，表示该语句为 $x_i \leftarrow x_j$；
  - 若 $v$ 为 `-`，接下来给出两个整数 $i,j$，表示该语句为 $x_i \leftarrow \lnot x_j$。
## 输出格式

对于每组测试数据输出一行一个整数，表示所有符合条件的赋初值方案中，$\mathit{Unknown}$ 变量个数的最小值。
## 样例

### 样例输入 #1
```
1 3
3 3
- 2 1
- 3 2
+ 1 3
3 3
- 2 1
- 3 2
- 1 3
2 2
T 2
U 2

```
### 样例输出 #1
```
0
3
1

```
## 提示

**【样例解释 #1】**

第一组测试数据中，$m$ 行语句依次为

- $x_2 \leftarrow \lnot x_1$；
- $x_3 \leftarrow \lnot x_2$；
- $x_1 \leftarrow x_3$。

一组合法的赋初值方案为 $x_1 = \mathit{T}, x_2 = \mathit{F}, x_3 = \mathit{T}$，共有 $0$ 个$\mathit{Unknown}$ 变量。因为不存在赋初值方案中有小于 $0$ 个$\mathit{Unknown}$ 变量，故输出为 $0$。

第二组测试数据中，$m$ 行语句依次为

- $x_2 \leftarrow \lnot x_1$；
- $x_3 \leftarrow \lnot x_2$；
- $x_1 \leftarrow \lnot x_3$。

唯一的赋初值方案为 $x_1 = x_2 = x_3 = \mathit{U}$，共有 $3$ 个$\mathit{Unknown}$ 变量，故输出为 $3$。

第三组测试数据中，$m$ 行语句依次为

- $x_2 \leftarrow \mathit{T}$；
- $x_2 \leftarrow \mathit{U}$；

一个最小化 $\mathit{Unknown}$ 变量个数的赋初值方案为 $x_1 = \mathit{T}, x_2 = \mathit{U}$。$x_1 = x_2 = \mathit{U}$ 也是一个合法的方案，但它没有最小化 $\mathit{Unknown}$ 变量的个数。

**【样例解释 #2】**

该组样例满足测试点 $2$ 的条件。

**【样例解释 #3】**

该组样例满足测试点 $5$ 的条件。

**【样例解释 #4】**

该组样例满足测试点 $8$ 的条件。

**【数据范围】**

对于所有测试数据，保证：

- $1 \le t \le 6$，$1 \le n,m \le 10 ^ 5$；
- 对于每个操作，$v$ 为 `TFU+-` 中的某个字符，$1 \le i,j \le n$。

| 测试点编号 | $n,m\leq$ | $v$ 可能的取值 |
| :----------: | :----------: | :----------: |
| $1,2$ | $10$ | $\mathit{TFU+-}$ |
| $3$ | $10^3$ | $\mathit{TFU}$ |
| $4$ | $10^5$ | $\mathit{TFU}$ |
| $5$ | $10^3$ | $\mathit{U+}$ |
| $6$ | $10^5$ | $\mathit{U+}$ |
| $7$ | $10^3$ | $\mathit{+-}$ |
| $8$ | $10^5$ | $\mathit{+-}$ |
| $9$ | $10^3$ | $\mathit{TFU+-}$ |
| $10$ | $10^5$ | $\mathit{TFU+-}$ |


---

