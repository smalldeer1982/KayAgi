---
title: "「XSOI-R1」原神数"
layout: "post"
diff: 普及+/提高
pid: P10404
tag: ['洛谷原创', 'O2优化', '素数判断,质数,筛法']
---
# 「XSOI-R1」原神数
## 题目描述

原神数 $x$ 需要同时满足以下条件：

- $x$ 为质数。

- $x$ 的十进制位两两不同。

比如 $131$ 不是原神数，因为他的百位和个位相等；$42$ 也不是，因为不是质数；$17$ 就是一个原神数。

有 $q$ 次询问，现在要你求出 $l$ 到 $r$ 之间的原神数数量。
## 输入格式

第一行一个正整数 $q$。

接下来 $q$ 行每行两个正整数 $l$，$r$。
## 输出格式

$q$ 行 $q$ 个正整数，表示答案。
## 样例

### 样例输入 #1
```
4
45 66
100 140
2 90
114514 1919810
```
### 样例输出 #1
```
4
6
23
13321
```
## 提示

**【样例解释 #1】**

在 $100 \sim 140$ 之间的原神数有 $103,107,109,127,137,139$，共 $6$ 个。

### 数据规模与约定

**本题采用捆绑测试。**

- subtask 0（15 pts）：$1 \le l \le r \le 10^2$。

- subtask 1（15 pts）：$1 \le l \le r \le 10^4$。

- subtask 2（35 pts）：$1 \le l \le r \le 10^7$。

- subtask 3（35 pts）：$1 \le l \le r \le 10^{18}$。

对于所有数据，保证 $1 \leq l \leq r \leq 10^{18}$，$1 \leq q\leq 10^5$。


---

---
title: "[NOIP 2009 普及组] 细胞分裂"
layout: "post"
diff: 普及+/提高
pid: P1069
tag: ['数学', '2009', 'NOIP 普及组', '素数判断,质数,筛法']
---
# [NOIP 2009 普及组] 细胞分裂
## 题目描述

Hanks 博士是 BT（Bio-Tech，生物技术）领域的知名专家。现在，他正在为一个细胞实验做准备工作：培养细胞样本。

Hanks 博士手里现在有 $N$ 种细胞，编号从 $1 \sim N$，一个第 $i$ 种细胞经过 $1$ 秒钟可以分裂为 $S_i$ 个同种细胞（$S_i$ 为正整数）。现在他需要选取某种细胞的一个放进培养皿，让其自由分裂，进行培养。一段时间以后，再把培养皿中的所有细胞平均分入 $M$ 个试管，形成 $M$ 份样本，用于实验。Hanks 博士的试管数 $M$ 很大，普通的计算机的基本数据类型无法存储这样大的 $M$ 值，但万幸的是，$M$ 总可以表示为 $m_1$ 的 $m_2$ 次方，即 $M = m_1^{m_2}$，其中 $m_1,m_2$ 均为基本数据类型可以存储的正整数。

注意，整个实验过程中不允许分割单个细胞，比如某个时刻若培养皿中有 $4$ 个细胞，Hanks 博士可以把它们分入 $2$ 个试管，每试管内 $2$ 个，然后开始实验。但如果培养皿中有 $5$ 个细胞，博士就无法将它们均分入 $2$ 个试管。此时，博士就只能等待一段时间，让细胞们继续分裂，使得其个数可以均分，或是干脆改换另一种细胞培养。

为了能让实验尽早开始，Hanks 博士在选定一种细胞开始培养后，总是在得到的细胞“刚好可以平均分入 $M$ 个试管”时停止细胞培养并开始实验。现在博士希望知道，选择哪种细胞培养，可以使得实验的开始时间最早。

## 输入格式

第一行，有一个正整数 $N$，代表细胞种数。

第二行，有两个正整数 $m_1,m_2$，以一个空格隔开，即表示试管的总数 $M = m_1^{m_2}$。

第三行有 $N$ 个正整数，第 $i$ 个数 $S_i$ 表示第 $i$ 种细胞经过 $1$ 秒钟可以分裂成同种细胞的个数。

## 输出格式

一个整数，表示从开始培养细胞到实验能够开始所经过的最少时间（单位为秒）。

如果无论 Hanks 博士选择哪种细胞都不能满足要求，则输出整数 $-1$。

## 样例

### 样例输入 #1
```
1 
2 1 
3

```
### 样例输出 #1
```
-1

```
### 样例输入 #2
```
2
24 1
30 12

```
### 样例输出 #2
```
2

```
## 提示

【输入输出样例 \#1 说明】

经过 $1$ 秒钟，细胞分裂成 $3$ 个，经过 $2$ 秒钟，细胞分裂成 $9$个，……，可以看出无论怎么分裂，细胞的个数都是奇数，因此永远不能分入 $2$ 个试管。

【输入输出样例 \#2 说明】

第 $1$ 种细胞最早在 $3$ 秒后才能均分入 $24$ 个试管，而第 $2$ 种最早在 $2$ 秒后就可以均分（每试管 $144 / {24}^1 = 6$ 个）。故实验最早可以在 $2$ 秒后开始。

【数据范围】

对于 $50 \%$ 的数据，有 $m_1^{m_2} \le 30000$。

对于所有的数据，有 $1 \le N \le 10000$，$1 \le m_1 \le 30000$，$1 \le m_2 \le 10000$，$1 \le S_i \le 2 \times {10}^9$。


NOIP 2009 普及组 第三题



---

---
title: "[EC Final 2020] Square"
layout: "post"
diff: 普及+/提高
pid: P10827
tag: ['2020', 'O2优化', '素数判断,质数,筛法', 'ICPC']
---
# [EC Final 2020] Square
## 题目描述

Father Study loves math very much.

Given a sequence of integers $a_1,a_2,...,a_n$, Father Study wants to calculate another sequence of integers $t_1,t_2,...,t_n$ satisifing 
- For each $i~(1 \le i \le n)$, $t_i > 0$.
- For each $i~(1\le i < n)$, $a_i \times t_i \times a_{i+1} \times t_{i+1}$ is a square number. (In mathematics, a square number or perfect square is an integer that is the square of an integer, in other words, it is the product of some integer with itself.)
- $\prod_{i=1}^{n}{t_i}$ is minimized.


Please help Father Study to calculate the answer --- the minimum value of $\prod_{i=1}^{n}{t_i}$. Because the answer is too large, please output the answer modulo $1000000007$.

## 输入格式

The first line contains a single integer $n$ ($1\le n \le 100000$).

The second line contains $n$ integers $a_1, a_2, ..., a_n$ ($1 \le a_i \le 1000000$) separated by single spaces.
## 输出格式

Output one integer -- the answer modulo $1000000007$. 
## 样例

### 样例输入 #1
```
3
2 3 6
```
### 样例输出 #1
```
6
```


---

---
title: "在小小的奶龙山里面挖呀挖呀挖"
layout: "post"
diff: 普及+/提高
pid: P12001
tag: ['洛谷原创', 'O2优化', '最近公共祖先 LCA', '素数判断,质数,筛法', '洛谷月赛']
---
# 在小小的奶龙山里面挖呀挖呀挖
## 题目背景

夏天快要到了，去兴绍奶龙山参加 ION5202 的 0p 决定探究奶龙山的性质。
## 题目描述

奶龙山内部存在复杂的奶龙山隧道，但是聪明的 0p 一眼就看出了 $n-1$ 条奶龙山隧道的结构是一颗树。其中任意两个隧道只在 $n$ 个休息点处相交，两两休息点之间都有路径联通，第 $i$ 个休息点有一个权值 $a_i$，对于每一个素数 $p$，若 $p\mid a_i$ 则说明 $p$ 公司参与了休息点建设。想要经过一个休息点，就必须和所有参与了休息点建设的公司搞好关系。

0p 有 $q$ 条心仪的路线，第 $i$ 条是从休息点 $u$ 走到休息点 $v$，对于每一条路线，0p 想知道，他需要与多少公司搞好关系才可以成功地走完这一条路线。


**请注意算法常数对时间效率的影响**。
## 输入格式

第一行，两个正整数 $n,q$。

第二行，共 $n$ 个正整数，第 $i$ 个正整数表示 $a_i$。

接下来 $n-1$ 行，每行两个正整数 $u,v$，表示一条树边。

接下来 $q$ 行，每行两个正整数 $u,v$，表示一条路线。
## 输出格式

输出共 $q$ 行，对于每一条路线，输出所求的答案。
## 样例

### 样例输入 #1
```
3 1
7 2 1
1 2
1 3
2 3
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
10 7
9 9 8 2 4 4 3 5 3 97
1 2
1 3
3 4
5 2
6 4
7 5
9 1
10 2
3 8
4 5
2 3
4 6
2 4
1 2
4 10
1 1
```
### 样例输出 #2
```
2
2
1
2
1
3
1
```
## 提示

对于 $20\%$ 的数据，满足 $n,q\leq 100$。

对于 $70\%$ 的数据，满足 $n,q\leq 1000$。

对于 $100\%$ 的数据，满足 $1\leq n,q\leq 5\times 10^4$，$1\leq a_i\leq 10^5$，$1\leq u,v\leq n$，保证给出的树合法。


---

---
title: "[蓝桥杯 2023 国 Java A] 质数排序"
layout: "post"
diff: 普及+/提高
pid: P12237
tag: ['2023', '素数判断,质数,筛法', '组合数学', '排列组合', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Java A] 质数排序
## 题目描述

我们定义质数排序为将一个序列中的所有下标为质数的位置进行升序排序，其它位置上的数不变。

例如，对 $8, 7, 6, 5, 4, 3, 2, 1$ 进行质数排序会得到 $8, 2, 4, 5, 6, 3, 7, 1$。给定 $n$，求 $1 \sim n$ 的每个排列进行质数排序后的逆序对的数量的和。由于结果很大，你只需要输出答案对 $998244353$ 取模的结果即可。
## 输入格式

输入一行包含一个整数 $n$。

## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
6
```
## 提示

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$n \leq 10$；
- 对于所有评测用例，$1 \leq n \leq 10^6$。


---

---
title: "[蓝桥杯 2024 国 Java B] 园丁"
layout: "post"
diff: 普及+/提高
pid: P12255
tag: ['2024', '数论', '树的遍历', '素数判断,质数,筛法', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Java B] 园丁
## 题目描述

小明是一位尽职尽责的园丁。这天他负责维护一棵树，树上有 $n$ 个结点 $1, 2, \ldots, n$，根结点为 $1$，结点 $i$ 的权值为 $a_i$。他需要更改一些结点的权值为任意正整数，使得对于任意一个至少有 $2$ 个儿子结点的结点 $i$ 满足：任意两个 $i$ 的儿子结点的权值的乘积都不是完全平方数。请问小明至少需要修改多少个结点的权值？
## 输入格式

输入共 $n+1$ 行。

第一行为一个正整数 $n$。

第二行为 $n$ 个由空格分开的正整数 $a_1, a_2, \ldots, a_n$。

后面 $n-1$ 行，每行两个正整数表示树上的一条边。
## 输出格式

输出共 $1$ 行，一个整数表示答案。
## 样例

### 样例输入 #1
```
6
1 2 9 8 4 4
1 2
1 3
1 4
2 5
2 6
```
### 样例输出 #1
```
2
```
## 提示

### 样例说明

其中一种方案：将结点 $2, 5$ 的权值分别修改为 $3, 2$。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，保证 $n \leq 10^3$。
- 对于 $100\%$ 的评测用例，保证 $1\leq n \leq 10^5$，$1 \leq a_i \leq 10^9$。


---

---
title: "[GCJ 2011 #2] Expensive Dinner"
layout: "post"
diff: 普及+/提高
pid: P13376
tag: ['数学', '2011', '二分', '数论', '素数判断,质数,筛法', 'Google Code Jam']
---
# [GCJ 2011 #2] Expensive Dinner
## 题目描述

Your friends are all going to a restaurant for dinner tonight. They're all very good at math, but they're all very strange: your $a^{\text{th}}$ friend (starting from 1) will be unhappy unless the total cost of the meal is a positive integer, and is divisible by $a$.

Your friends enter the restaurant one at a time. As soon as someone enters the restaurant, if that person is unhappy then the group will call a waiter immediately.

As long as there is at least one unhappy person in the restaurant, one of those unhappy people will buy the lowest-cost item that will make him or her happy. This will continue until nobody in the restaurant is unhappy, and then the waiter will leave. Fortunately, the restaurant sells food at every integer price. See the explanation of the first test case for an example.

Your friends could choose to enter the restaurant in any order. After the waiter has been called, if there is more than one unhappy person in the restaurant, any one of those unhappy people could choose to buy something first. The way in which all of those choices are made could have an effect on how many times the group calls a waiter.

As the owner of the restaurant, you employ some very tired waiters. You want to calculate the spread of your friends: the difference between the maximum number of times they might call a waiter and the minimum number of times they might call a waiter.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, each on its own line. Each test case will contain one integer $N$, the number of friends you have.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the spread for that test case.
## 样例

### 样例输入 #1
```
4
1
3
6
16
```
### 样例输出 #1
```
Case #1: 0
Case #2: 1
Case #3: 2
Case #4: 5
```
## 提示

**Sample Explanation**

In Case #2, suppose your friends arrive in the order $[1, 2, 3]$. Then #1 arrives; is unhappy; calls a waiter; and buys something costing $1$. Now nobody is unhappy. #2 arrives next; is unhappy; calls a waiter; and buys something costing $1$ (for a total of $2$). Now nobody is unhappy. #3 arrives next; is unhappy; calls a waiter; and buys something costing $1$ (for a total of $3$). Now #2 is unhappy, and buys something costing $1$ (for a total of $4$). Now #3 is unhappy, and buys something costing $2$ (for a total of $6$). Finally nobody is unhappy, and a waiter was called three times.

Suppose instead that your friends arrived in the order $[3, 1, 2]$. Then #3 arrives; is unhappy; calls a waiter; and buys something costing $3$. Now nobody is unhappy. #1 arrives next; nobody is unhappy. #2 arrives next; is unhappy; calls a waiter; and buys something costing $1$ (for a total of $4$). Now #3 is unhappy, and buys something costing $2$ (for a total of $6$). Now nobody is unhappy, and a waiter was called two times. The spread is $1$.

**Limits**

**Small dataset (13 Pts, Test set 1 - Visible)**

- $1 \leq T \leq 100$.
- $1 \leq N \leq 1000$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (17 Pts, Test set 2 - Hidden)**

- $1 \leq T \leq 1000$.
- $1 \leq N \leq 10^{12}$.
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[GCJ 2008 #1B] Number Sets"
layout: "post"
diff: 普及+/提高
pid: P13461
tag: ['2008', '并查集', '素数判断,质数,筛法', 'Google Code Jam']
---
# [GCJ 2008 #1B] Number Sets
## 题目描述

You start with a sequence of consecutive integers. You want to group them into sets.

You are given the interval, and an integer $P$. Initially, each number in the interval is in its own set.

Then you consider each pair of integers in the interval. If the two integers share a prime factor which is at least $P$, then you merge the two sets to which the two integers belong.

How many different sets there will be at the end of this process?
## 输入格式

One line containing an integer $C$, the number of test cases in the input file.

For each test case, there will be one line containing three single-space-separated integers $A$, $B$, and $P$. $A$ and $B$ are the first and last integers in the interval, and $P$ is the number as described above.

## 输出格式

For each test case, output one line containing the string "Case #$X$: $Y$" where $X$ is the number of the test case, starting from 1, and $Y$ is the number of sets.
## 样例

### 样例输入 #1
```
2
10 20 5
10 20 3
```
### 样例输出 #1
```
Case #1: 9
Case #2: 7
```
## 提示

**Small dataset (10 Pts, Test set 1 - Visible)**

- $1 \leq C \leq 10$
- $1 \leq A \leq B \leq 1000$
- $2 \leq P \leq B$

**Large dataset (25 Pts, Test set 2 - Hidden)**

- $1 \leq C \leq 100$
- $1 \leq A \leq B \leq 10^{12}$
- $B \leq A + 1000000$
- $2 \leq P \leq B$



---

---
title: "[NOI2012] 随机数生成器"
layout: "post"
diff: 普及+/提高
pid: P2044
tag: ['数学', '贪心', '2012', '矩阵运算', 'NOI', '素数判断,质数,筛法', '矩阵乘法']
---
# [NOI2012] 随机数生成器
## 题目描述

栋栋最近迷上了随机算法，而随机数是生成随机算法的基础。栋栋准备使用线性同余法（Linear Congruential Method）来生成一个随机数列，这种方法需要设置四个非负整数参数 $m,a,c,X_0$，按照下面的公式生成出一系列随机数 $\{X_n\}$：
$$X_{n+1}=(aX_n +c)\bmod m$$

其中 $\bmod m$ 表示前面的数除以 $m$ 的余数。从这个式子可以看出，这个序列的下一个数总是由上一个数生成的。

用这种方法生成的序列具有随机序列的性质，因此这种方法被广泛地使用，包括常用的 C++ 和 Pascal 的产生随机数的库函数使用的也是这种方法。

栋栋知道这样产生的序列具有良好的随机性，不过心急的他仍然想尽快知道 $X_n$ 是多少。由于栋栋需要的随机数是 $0,1,\dots,g-1$ 之间的，他需要将 $X_n$ 除以 $g$ 取余得到他想要的数，即 $X_n \bmod g$，你只需要告诉栋栋他想要的数 $X_n \bmod g$ 是多少就可以了。

## 输入格式

一行 $6$ 个用空格分割的整数 $m,a,c,X_0,n$ 和 $g$，其中 $a,c,X_0$ 是非负整数，$m,n,g$ 是正整数。

## 输出格式

输出一个数，即 $X_n \bmod g$。

## 样例

### 样例输入 #1
```
11 8 7 1 5 3
```
### 样例输出 #1
```
2
```
## 提示

计算得 $X_n=X_5=8$，故$(X_n \bmod g) = (8 \bmod 3) = 2$。

对于 $100\%$ 的数据，$n,m,a,c,X_0\leq 10^{18}$，$1\leq g\leq 10^8$，$n,m\geq 1$，$a,c,X_0\geq 0$。



---

---
title: "数字游戏"
layout: "post"
diff: 普及+/提高
pid: P2092
tag: ['素数判断,质数,筛法']
---
# 数字游戏
## 题目描述

KC 邀请他的两个小弟 K 和 C 玩起了数字游戏。游戏是 K 和 C 轮流操作进行的，K 为先手。KC 会先给定一个数字 $Q$，每次操作玩家必须写出当前数字的一个因数来代替当前数字，但是这个因数不能是 $1$ 和它本身。例如当前数字为 $6$，那么可以用 $2, 3$ 来代替，但是 $1$ 和 $6$ 就不行。现在规定第一个没有数字可以写出的玩家为胜者。K 在已知 $Q$ 的情况，想知道自己作为先手能不能胜利，若能胜利，那么第一次写出的可以制胜的最小数字是多少呢？整个游戏过程我们认为 K 和C用的都是最优策略。
## 输入格式

仅一行，一个正整数 $Q$。
## 输出格式

第一行是 $1$ 或 $2$，$1$ 表示 K 能胜利，$2$ 表示 C 能胜利。

若 K 能胜利，则在第二行输出第一次写出的可以制胜的最小数字。

若是第一次就无法写出数字，则认为第一次写出的可以制胜的最小数字为 $0$。
## 样例

### 样例输入 #1
```
6

```
### 样例输出 #1
```
2

```
### 样例输入 #2
```
30

```
### 样例输出 #2
```
1
6

```
## 提示

对于 $30 \%$ 的数据，$Q \le 50$；  
对于 $100 \%$ 的数据，$2 \le Q \le {10}^{13}$。


---

---
title: "三素数数"
layout: "post"
diff: 普及+/提高
pid: P2359
tag: ['动态规划 DP', '高级数据结构', '洛谷原创', '素数判断,质数,筛法']
---
# 三素数数
## 题目背景

蛟川书院的一道练习题QAQ

## 题目描述

如果一个数的所有连续三位数字都是大于100的素数，则该数称为三素数数。比如113797是一个6位的三素数数。

## 输入格式

一个整数n（3 ≤ n ≤ 10000），表示三素数数的位数。

## 输出格式

一个整数，表示n位三素数的个数m，要求输出m除以10^9 + 9的余数。

## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
204
```
## 提示

区域动归QAQ



---

---
title: "角色属性树"
layout: "post"
diff: 普及+/提高
pid: P2441
tag: ['数学', '树形数据结构', '枚举', '素数判断,质数,筛法', '栈']
---
# 角色属性树
## 题目描述

绪萌同人社是一个有趣的组织，该组织结构是一个树形结构。有一个社长，直接下属一些副社长。每个副社长又直接下属一些部长……。

每个成员都有一个萌点的属性，萌点属性是由一些质数的萌元素乘积构成（例如，猫耳的值是 $2$，弱气的值是 $3$，黄毛的值是 $5$，病娇的值是 $7$，双马尾的值是 $11$ 等等）

举个例子，正妹是双份的猫耳，而且有一份弱气，她的属性值为 $2\times 2\times 3=12$。

现在组员关心一个问题，希望知道离自己最近且有相同萌元素上司是谁，例如，属性值为 $2、4、6、45$ 这样的属性值都算是和正妹有相同的属性。


然而，组员可能会随时变化自己的属性。啊。。感觉好麻烦啊。。

## 输入格式

第一行，$n,k$ 表示成员数与询问的次数

第二行，$n$ 个数，分别是 $1$ 到 $n$ 号成员的属性值

接下来 $n-1$ 行，$x_i,y_i$ 表示 $x_i$ 是 $y_i$ 的上司。

接下来来 $k$ 行，有两种情况

$1\ u_i$：询问离 $u_i$ 成员最近且有相同萌元素上司。

$2\ u_i$：$a$ 更改 $u_i$ 的属性值为 $a$。

## 输出格式

对于每个 $1$ 类型的询问，输出符合要求的编号。如果没有符合要求的编号，输出 $-1$。

## 样例

### 样例输入 #1
```
4 6

10 8 4 3

1 2

2 3

3 4

1 1

1 2

1 3

1 4

2 1 9

1 4
```
### 样例输出 #1
```
-1

1

2

-1

1
```
## 提示

对于 $20\%$ 的数据，没有修改的操作。

对于 $50\%$ 的数据，$n\le 100$，修改次数 $<10$。

对于 $100\%$ 的数据，$n\le 200000$，$k<100000$，修改次数 $\le 50,a\_i\le 2^{31}-1$

UPD：本题测试数据随机，可能是假题。


---

---
title: "[AHOI2018初中组] 根式化简"
layout: "post"
diff: 普及+/提高
pid: P4446
tag: ['数学', '2018', '安徽', '枚举', '素数判断,质数,筛法']
---
# [AHOI2018初中组] 根式化简
## 题目描述

小可可在学习“立方根”的知识时碰到这样的问题：

将下面根式化简为最简根式：

(1) $\sqrt[3]{125}$ (2) $\sqrt[3]{81}$ (3) $\sqrt[3]{52}$

这个问题对于小可可来说太简单了，他很快就算出了答案：

(1) $5$ (2) 3$\sqrt[3]{3}$ (3) $\sqrt[3]{52}$

小可可知道任意形如$\sqrt[3]{x}$ 的根式，化简后一定可以被写成形如$a\sqrt[3]{b}$的最简根式。他觉得这很有趣，就仿照出了不少题，但没一会儿就被密密麻麻的根式绕晕了，于是他向你求助：

给定 $n$ 个形如 $\sqrt[3]{x}$ 的根式，请你将它们化简为形如$a\sqrt[3]{b}$的最简形式，为了方便，你只需要输出其中的$a$ 即可。

如果你没有学过这部分数学知识，你可以认为题意是：给你$n$ 个正整数$x$，对于每一个$x$，你需要求出整数$a,b$ 使得$a^3 \times b = x$，输出最大的整数$a$ 即可。
## 输入格式

输入有两行：

第一行一个整数$n$，表示有$n$ 个形如$\sqrt[3]{x}$ 的根式； 
第二行$n$ 个正整数，依次给出每个$x$。 
## 输出格式

输出$n$ 行，每行一个正整数，第$i$ 行正整数表示你对输入中第$i$ 个$x$ 给出的答案。
## 样例

### 样例输入 #1
```
3
125 81 52
```
### 样例输出 #1
```
5
3
1
```
## 提示

对于100%的数据满足：$1≤n≤10000$，$1≤x≤10^{18}$。

本题共10 个测试点，编号为1~10，每个测试点额外保证如下：

测试点编号n 的范围x 的范围  
1~2 $n≤10, x≤10^6$  
3~4 $n≤10, x≤10^9$  
5~6 $n≤100, x≤10^{18}$ 且$x$ 为完全立方数  
7~8 $n≤500, x≤10^{18}$  
9~10 $n≤10000, x≤10^{18}$


---

---
title: "Divided Prime"
layout: "post"
diff: 普及+/提高
pid: P4752
tag: ['O2优化', '排序', '素数判断,质数,筛法', '洛谷月赛']
---
# Divided Prime
## 题目描述

给定一个数字$A$，这个$A$由$a_1,a_2,\cdots,a_N$相乘得到。

给定一个数字$B$，这个$B$由$b_1,b_2,\cdots,b_M$相乘得到。

如果$\frac{A}{B}$是一个质数，请输出`YES`，否则输出`NO`。


## 输入格式

每个测试点包含多组数据，第一行读入一个整数 $T$ 表示数据组数，对于每组数据：

第一行输入两个整数 $N,M$，分别表示 $A$ 由 $N$ 个数字相乘得到，$B$ 由 $M$ 个数字相乘得到。

第二行输入 $N$ 个整数，分别表示组成 $A$ 的 $N$ 个数字。

第三行输入 $M$ 个整数，分别表示组成 $B$ 的 $M$ 个数字。

保证对于一个数字，其在 ${b_i}$ 中出现的次数不多于在 ${a_i}$ 中出现的次数。
## 输出格式

对于每组数据：
如果 $\frac{A}{B}$ 是一个质数，请输出 `YES`，否则输出 `NO`。
在输出 `YES` 或 `NO` 后输出一个换行符。
## 样例

### 样例输入 #1
```
2
3 2
5 7 7
5 7
4 2
5 7 7 7
5 7
```
### 样例输出 #1
```
YES
NO
```
## 提示

$1 \le N \le 100000$

$0 \le M \le N$

$1 \le a_i,b_i \le 10^{12}$

$1 \le T \le 10$

$\sum N \le 100000$


---

---
title: "[JRKSJ R2] Upper"
layout: "post"
diff: 普及+/提高
pid: P7810
tag: ['动态规划 DP', '线段树', '2021', '洛谷原创', 'O2优化', '素数判断,质数,筛法']
---
# [JRKSJ R2] Upper
## 题目描述

有 $n$ 张扑克，第 $i$ 张扑克上写有一个正整数 $a_i$。

现在要把扑克划分成若干个合法的连续子段，其中，一个连续子段 $[l,r]$ “合法”当且仅当这个子段同时满足两个条件： 

* $a_l< a_r$
* $\gcd(a_l,a_r)>1$ 

请问最多能划分多少段。如果没有合法的划分方案，输出 $-1$ 即可。

如果您不知道 $\gcd$ 是什么意思，请看“提示”部分。
## 输入格式

第一行一个整数 $n$。\
第二行 $n$ 个整数表示序列 $a$。
## 输出格式

一个整数，如题目描述所示。
## 样例

### 样例输入 #1
```
5
2 1 8 3 9
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5
5 4 3 2 1
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
20
20 9 36 36 40 8 3 10 9 20 18 12 30 20 30 15 8 9 27 45
```
### 样例输出 #3
```
7
```
## 提示

### 数据范围
本题采用捆绑测试。

对于 $100\%$ 的数据，$2\le n\le 10^5$，$1\le a_i\le 10^9$。

| $\text{Subtask}$ | $n\le$ | $a_i\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $10^9$ | 无 | $5$ |
| $2$ | $3\times10^3$ | $10^9$ | 无 | $15$ |
| $3$ | $2\times10^4$ | $10^6$ | 无 | $20$ |
| $4$ | $2\times 10^4$ | $10^9$ | 无 | $10$ |
| $5$ | $10^5$ | $10^9$ | 数据随机 | $10$ |
| $6$ | $10^5$ | $10^9$ | 无 | $40$ |

### 样例解释
对于样例 $1$，有且仅有一种划分方案 $\{2,1,8\},\{3,9\}$。\
对于样例 $2$，无合法的划分方案。

### 提示
对于两个正整数 $a,b$，$\gcd(a,b)$ 为它们的最大公因数，即满足既是 $a$ 的因数又是 $b$ 的因数的数中最大的数。


---

---
title: "[蓝桥杯 2022 省 A] 数的拆分"
layout: "post"
diff: 普及+/提高
pid: P8778
tag: ['2022', '数论', '素数判断,质数,筛法', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 A] 数的拆分
## 题目描述

给定 $T$ 个正整数 $a_{i}$，分别问每个 $a_{i}$ 能否表示为 $x_{1}^{y_{1}} \cdot x_{2}^{y_{2}}$ 的形式，其中 $x_{1}, x_{2}$ 为正整数，$y_{1}, y_{2}$ 为大于等于 $2$ 的正整数。
## 输入格式

输入第一行包含一个整数 $T$ 表示询问次数。

接下来 $T$ 行，每行包含一个正整数 $a_{i}$ 。
## 输出格式

对于每次询问，如果 $a_{i}$ 能够表示为题目描述的形式则输出 `yes`，否则输出 `no`。
## 样例

### 样例输入 #1
```
7
2
6
12
4
8
24
72
```
### 样例输出 #1
```
no
no
no
yes
yes
no
yes
```
## 提示

**【样例说明】**

第 $4,5,7$ 个数分别可以表示为:

$$
\begin{aligned}
&a_{4}=2^{2} \times 1^{2} ; \\
&a_{5}=2^{3} \times 1^{2} ; \\
&a_{7}=2^{3} \times 3^{2} 。
\end{aligned}
$$

**【评测用例规模与约定】**

对于 $10 \%$ 的评测用例，$1 \leq T \leq 200, a_{i} \leq 10^{9}$;

对于 $30 \%$ 的评测用例，$1 \leq T \leq 300, a_{i} \leq 10^{18}$;

对于 $60 \%$ 的评测用例，$1 \leq T \leq 10000, a_{i} \leq 10^{18}$;

对于所有评测用例，$1 \leq T \leq 100000,1 \leq a_{i} \leq 10^{18}$ 。 

蓝桥杯 2022 省赛 A 组 I 题。


---

---
title: "[传智杯 #4 初赛] 小卡与质数 2"
layout: "post"
diff: 普及+/提高
pid: P8842
tag: ['素数判断,质数,筛法', '位运算', '传智杯']
---
# [传智杯 #4 初赛] 小卡与质数 2
## 题目背景

小卡迷上了质数！
## 题目描述

小卡最近迷上了质数，所以他想把任何一个数都转化为质数！

小卡有 $T$ 次询问，每次给你一个数字 $x$，问有多少个比 $x$ 小的非负整数 $y$，使得 $x\oplus y$ 是质数，其中 $\oplus$ 表示按位异或。
## 输入格式

第一行一个正整数 $T(1\le T\le10^5)$，表示有 $T$ 组询问。

接下来 $T$ 行，每行一个正整数 $x(1\le x\le 10^6)$。
## 输出格式

对于每组询问，输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
9
5
6
7
8
9
10
100
1000
10000
```
### 样例输出 #1
```
2
4
4
2
2
4
22
163
1132
```


---

---
title: "[SNCPC2019] To the Park"
layout: "post"
diff: 普及+/提高
pid: P9647
tag: ['2019', 'Special Judge', 'O2优化', '陕西', '素数判断,质数,筛法', 'XCPC']
---
# [SNCPC2019] To the Park
## 题目描述

BaoBao and his $(n-1)$ classmates are going to the park. For convenience, their teacher DreamGrid has numbered the students from 1 to $n$ and decides to form the students into some groups, where each group consists of exactly two students.

For some reason, DreamGrid requires that the indices of the two students in the same group should have a common divisor greater than 1. Note that each student can only belong to at most one group, and it's not necessary that every student belongs to a group.

Please help DreamGrid form as many groups as possible.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first and only line contains an integer $n$ ($1 \le n \le 10^5$), indicating the number of students.

It's guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.

## 输出格式

For each test case output one line. The line first contains an integer $k$ indicating the number of groups, then $2k$ integers $a_1, a_2, \dots, a_{2k}$ follow, indicating that student $a_1$ and $a_2$ belong to the same group, student $a_3$ and $a_4$ belong to the same group, ..., student $a_{2k-1}$ and $a_{2k}$ belong to the same group. The integers in a line are separated by a space. If there are multiple valid answers, you can print any of them.

Please, DO NOT output extra spaces at the end of each line, or your solution may be considered incorrect!
## 样例

### 样例输入 #1
```
3
1
4
6

```
### 样例输出 #1
```
0
1 2 4
2 2 4 3 6

```
## 题目翻译

**【题目描述】**

宝宝和他的 $(n-1)$ 个同学要去公园。为了方便，他们的老师梦想格子将学生从 1 到 $n$ 编号，并决定将学生分成一些小组，每组恰好由两个学生组成。

由于某种原因，梦想格子要求同组的两个学生的编号必须有一个大于 1 的公约数。注意，每个学生最多只能属于一个小组，并且不需要每个学生都属于一个小组。

请帮助梦想格子组成尽可能多的小组。


**【输入格式】**

有多个测试用例。输入的第一行包含一个整数 $T$，表示测试用例的数量。对于每个测试用例：

第一行且唯一一行包含一个整数 $n$ ($1 \le n \le 10^5$)，表示学生的数量。

保证所有测试用例的 $n$ 之和不超过 $10^6$。

**【输出格式】**

对于每个测试用例，输出一行。该行首先包含一个整数 $k$，表示小组的数量，然后是 $2k$ 个整数 $a_1, a_2, \dots, a_{2k}$，表示学生 $a_1$ 和 $a_2$ 属于同一小组，学生 $a_3$ 和 $a_4$ 属于同一小组，以此类推。行内的整数由空格分隔。如果有多个有效答案，可以输出其中任何一个。

请不要在每行的末尾输出多余的空格，否则你的解决方案可能会被认为不正确！

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

