---
title: "「QMSOI R1」 三服同构"
layout: "post"
diff: 提高+/省选-
pid: P11070
tag: ['动态规划 DP', 'Special Judge', 'O2优化', '概率论', '期望']
---
# 「QMSOI R1」 三服同构
## 题目背景

前不久，三国杀上线了一位三服同构的赛事专属武将...

[那这道题与SP孙策的关系呢？](https://www.luogu.com.cn/paste/g68kquaa)

![](https://patchwiki.biligame.com/images/sgs/thumb/4/46/ekgr28n00suo1zkuksp047802wfl4a6.png/401px-SP%E5%AD%99%E7%AD%96-%E7%BB%8F%E5%85%B8%E5%BD%A2%E8%B1%A1.png)
## 题目描述

现在有 $4$ 种扑克牌：红桃 A，红桃 K，黑桃 A，黑桃 K，小 Q 的手上现在有 $n$ 张黑桃牌，$m$ 张红桃牌，其中有 $u$ 张黑桃 A，$v$ 张红桃 A，而对手有 $k$ 张牌。

现在小 Q 知道对手第 $i$ 张牌点数为 A 的概率为 $a_i$，接下来他将持续执行以下操作，直到他的回合结束。

1. 若你手中有至少 $1$ 张红桃 A 或红桃 K，则你**必须**等概率随机弃置 $1$ 张花色为红桃的牌，并与对手进行决斗。
2. 否则，你结束你的回合。

决斗的流程如下：

从对手开始，双方交替进行以下操作：

1. 若其手上有至少 $1$ 张红桃 A 或黑桃 A，则其**必须**等概率随机弃置 $1$ 张点数为 A 的牌。
2. 否则，其受到 $1$ 点伤害,并结束此次决斗。

现在你想要知道在你的回合结束前，对手期望会受到多少点伤害。
## 输入格式

第一行 $5$ 个整数分别表示 $n,m,u,v,k$。

第二行 $k$ 个实数，依次表示 $a_1,a_2,\cdots,a_k$。
## 输出格式

输出一行一个实数，表示期望伤害。

**本题使用 Special Judge 进行评测**，只要你的答案与标准输出**绝对误差**在 $10^{-6}$ 以内，则判定答案正确。
## 样例

### 样例输入 #1
```
2 2 1 1 2
0.2 0.8
```
### 样例输出 #1
```
1.670000000
```
## 提示

### 样例解释

可以得出对手牌中有 $0,1,2$ 张 A 的概率分别为 $0.16,0.68,0.16$。

当对手牌中有 $0$ 张 A 时，无论小 Q 每次耗费的哪张红色牌，都能对对手造成伤害，所以这种情况期望伤害为 $0.16*2=0.32$。

当对手牌中有 $1$ 张 A 时，假设小 Q 第一次耗费的是 A 进行决斗，那对手打出 A 后，小 Q 就会打出一张黑桃 A，对手没 A 了就会受到伤害，而小 Q 的另一张红桃 K 依然能被耗费，以进行决斗对对手造成伤害，所以这种情况期望伤害为 $0.68*0.5*2=0.68$。

当对手牌中有 $1$ 张 A 时，假设小 Q 第一次耗费的是 K 进行决斗，那对手打出 A 后，小 Q 打出黑桃 A 或红桃 A 的概率就是相等的，然后对手没 A 了就会受到伤害，但是如果打出的是红桃 A 就无法再进行决斗了，而打出黑桃 A 另一张红桃 A 依然被耗费，进行决斗对对手造成伤害，所以这种情况期望伤害为 $0.68*0.5*0.5*1+0.68*0.5*0.5*2=0.51$。

当对手牌中有 $2$ 张 A，这时如果小 Q 先耗费的 A 进行决斗，那对手打出 A 后，小 Q 就会打出一张黑桃 A，对手再打出 A 后，小 Q 就会受到伤害，而小 Q 的另一张红桃 K 依然能被耗费，以进行决斗对对手造成伤害，所以这种情况期望伤害为 $0.16*0.5*1=0.08$。

当对手牌中有 $2$ 张 A，这时如果小 Q 先耗费的 K 进行决斗，双方就会各打出两张 A，然后敌人受到伤害，小 Q 就不能再进行决斗了，所以这种情况期望伤害同样为 $0.16*0.5*1=0.08$。

所以对手受到的期望伤害就是 $0.32+0.68+0.51+0.08+0.08=1.67$。

### 数据范围
**本题使用 subtask 进行捆绑测试**，每个 subtask 的具体分值如下：
| 子任务 | 值域 | 分值 |
| :----------: | :----------: | :----------: |
| $0$ | $1\le n,m\le 10$ | $30$ |
| $1$ | $1\le n,m\le 2000$ | $70$ |

对于所有的数据，满足 $1 \leq n,m,k \leq 2000,1\le u<n,1\le v <m$。


---

---
title: "校园跑"
layout: "post"
diff: 提高+/省选-
pid: P11469
tag: ['Special Judge', 'O2优化', '矩阵加速', '期望']
---
# 校园跑
## 题目背景

你正要进行校园跑。
## 题目描述

校园跑软件会随机生成若干个点位，共有 $m$ 种不同的点位序列，通过第 $i$ 种点位序列的所需的最小跑动距离为 $a_i$，每次获取点位生成第 $i$ 种点位序列的概率为 $p_i$。

你共有 $n$ 次获取点位的机会，每次获取点位后，你可以选择按当前点位开始跑步，也可以选择重新获取点位，如果已经没有获取点位的机会，则只能按当前点位开始跑步。

你想使自己最后跑动距离的期望尽量小，求这个最小的期望。

你的答案与标准答案的绝对误差或相对误差不超过 $10^{-4}$ 即视为正确。形式化的，如果你的答案是 $a$，评测用的标准答案为 $b$，那么你的答案会且仅会在 $\frac{|a-b|}{\max(1,|b|)}\le10^{-4}$ 的情况下通过。
## 输入格式

**本题有多组数据**。

第一行一个正整数 $T$，表示数据组数。

对于每组数据：

第一行两个正整数 $n,m$。

第二行 $m$ 个正整数，第 $i$ 个正整数表示 $a_i$。

第三行 $m$ 个正整数，设第 $i$ 个正整数为 $b_i$，这 $m$ 个正整数的和为 $s$，则 $p_i=\frac{b_i}{s}$。
## 输出格式

对于每组数据：

输出一行一个浮点数，表示你的答案。

你的答案与标准答案的绝对误差或相对误差不超过 $10^{-4}$ 即视为正确。
## 样例

### 样例输入 #1
```
3
5 3
3 2 1
3 1 1
10 10
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 9 10
2 3
1 2 2
1 1 1

```
### 样例输出 #1
```
1.527360
3.535155
1.444444

```
## 提示

$1\le T\le2\times10^5$，$1\le n,a_i\le10^9$，$1\le m,\sum m\le2\times10^5$，$1\le b_i\le10^4$。


---

---
title: "[USTCPC 2025] 公平抉择"
layout: "post"
diff: 提高+/省选-
pid: P12040
tag: ['2025', '数论', '概率论', '期望', '高校校赛']
---
# [USTCPC 2025] 公平抉择
## 题目背景

考虑到评测机性能差异，改为 400ms 时限。USTCPC 时限为 600ms。

**请注意本题非常规时空限制！**

所以要“费厄”，最好是首先看清对手，倘是些不配承受“费厄”的，大可以老实不客气；待到它也“费厄”了，然后再与它讲“费厄”不迟。(节选自鲁迅《论“费厄泼赖”应该缓行》)

克露丝卡尔酱选择困难！她甚至无法抉择午饭去吃什么，作为她的朋友，你需要和她一起完整**公平的抉择**。
## 题目描述

克露丝卡尔酱在做选择，食堂共有 $n$ 种菜品可选，而她手里只有一个 $k$ 面的骰子(如果 $k = 2$ 则为硬币)。

为了落实公平抉择的理念，她希望她的策略选择到每个菜品的概率相等。

求她期望投掷次数的最小值，**答案对质数 $M$ 取模**。
## 输入格式

一行三个正整数 $n, k, M$ ,分别表示选项数、骰子面数和模数。

$2 \le k \le n \le 3 \times 10^6$，$10^8 \le M \le 10^9$，**保证 $M$ 为质数且对于任意 $1 \le i \le n,k^i \bmod M > 1$**。
## 输出格式

一个整数表示模意义下的答案。

关于分数取模：设答案为 $\dfrac{q}{p}$ 且 $M \nmid p,q$，那么取模结果 $x$ 为 唯一 $x\in[0,M)$ 使得 $px\equiv q\pmod M$。
## 样例

### 样例输入 #1
```
3 2 998244353
```
### 样例输出 #1
```
665496238
```
### 样例输入 #2
```
10 2 998244353
```
### 样例输出 #2
```
798595487
```
## 提示

在样例 $1$ 中，不妨设答案为 $E$。考虑扔两次硬币，得到四种情况，出现概率各为 $\dfrac{1}4$。前三种情况分配给三种菜品，第四种情况重投。故 $E=2+\dfrac{E}4$，解得 $E=\dfrac{8}3$。


---

---
title: "DerrickLo's Buildings (UBC002D)"
layout: "post"
diff: 提高+/省选-
pid: P12181
tag: ['数论', 'O2优化', '期望', '整除分块']
---
# DerrickLo's Buildings (UBC002D)
## 题目描述

在某游戏中，DerrickLo 的任务是操作一堆建筑。这些建筑被摆放在了编号为 $1$ 到 $M$ 的空位上，它们的高度也分别为 $1$ 到 $M$。一开始，对于所有 $i = 1, 2, \dots, M$，高度为 $i$ 的建筑被摆在了 $i$ 号位置上。

在这个游戏中，有 $M$ 个挑战。具体地，第 $i$ 个挑战都会指定一个高度因数 $l = i$ 和目标长度 $N$，这个挑战的**得分**为在重新摆放建筑后，对于所有 $j = 1, 2, \dots N$，满足高度为 $j$ 的建筑被摆在了 $j \times l$ 号位置的数量。**注意：所有挑战的目标长度都是相同的，但高度因数是互不相同的。**

为了重新摆放这些建筑，DerrickLo 需要指定一个调换排列 $v$，每执行一次调换，就会**同时**将位置 $i$ 上的建筑移到 $v(i)$ 处。

由于 DerrickLo 并不是很看重得分是否最高，因此他指定的排列 $v$ 将是从所有 $1$ 到 $M$ 的排列中**等概率**选取的一个。不过，他还是很好奇，对于每一个挑战 $i$，在他分别调换 $1, 2, \dots, V$ 次时，他的期望得分是多少。

由于挑战的个数以及调换的次数实在太多，DerrickLo 希望你告诉所有这些得分之和模 $998244353$ 之后的结果。即：
$$
\left(\sum_{i=1}^M\sum_{k=1}^VE\left(\sum_{j=1}^N[v_k(j) = i \times j]\right)\right)\bmod 998244353
$$
其中 $v_k(j)$ 表示根据排列 $v$ 调换了 $k$ 次之后，高度为 $j$ 的建筑所在的位置编号。
## 输入格式

**本题有多组测试数据。**

第一行，一个正整数 $T$，表示测试数据的个数。

接下来 $T$ 行，每行三个整数 $N, M, V$，描述一个测试数据。

**注意：输入数据不一定在 `int` 范围内。**

## 输出格式

共 $T$ 行，每行一个整数，表示答案。

## 样例

### 样例输入 #1
```
1
1 2 1
```
### 样例输出 #1
```
1
```
## 提示

在样例中，$v$ 只有 $\{1, 2\}$ 与 $\{2, 1\}$ 两种取值。你需要计算：
$$
\sum_{i=1}^2E([v(1) = i])
$$
当 $i=1$ 时，$E([v(1) = 1]) = \frac 1 2$；当 $i=2$ 时，$E([v(1) = 2]) = \frac 1 2$。因此，求和之后是 $\frac{1 + 1}{2} = 1$。

---

对于所有测试数据：

- $1 \le T \le 5$。
- $1 \le N \le M \le 10^{12}$。
- $2 \le (M \bmod 998244353)$。
- $1 \le V \le 10^{12}$。

**注意：输入数据不一定在 `int` 范围内。**



---

---
title: "[GCJ 2022 #3] Revenge of GoroSort"
layout: "post"
diff: 提高+/省选-
pid: P12997
tag: ['数学', '2022', '交互题', 'Special Judge', '期望', 'Google Code Jam']
---
# [GCJ 2022 #3] Revenge of GoroSort
## 题目描述

**In this problem, when something is said to be chosen at random, it means uniformly at random from among all valid possibilities, and independently of any other choice.**

Code Jam contestants once helped the mighty Goro sort an array of integers. (You do not need to read that problem to solve this one.) Once again, Goro needs your help. He has $\mathbf{N}$ boxes lined up on the table in a single row, numbered 1 through $\mathbf{N}$ from left to right. Each box has exactly one ball inside. Balls are also numbered 1 through $\mathbf{N}$. Goro wants ball $i$ to end up in box $i$, for all $i$. That is, he wants to leave the balls in sorted order. Unfortunately, that is not initially the case.

When Goro bumps the table with his powerful fists, balls pop up in the air and fall back in boxes. Goro can do this so accurately that exactly one ball falls into each box. A ball may fall into the same box it came out of, or into a different one.

Better yet, Goro also has the ability to assign colors to boxes before each bump. Then, he can bump the table in such a way that balls coming out of a box of color $c$ always fall into a box of color $c$. As impressive as this accuracy is, Goro does not have any more control than that. Within each color, balls end up assigned to boxes at random.

For example, suppose the balls appear in the order $1, 4, 3, 6, 5, 2$ (as seen above). He might choose — not necessarily optimally — to give the first box the color red, the second and sixth boxes the color green, and the third through fifth boxes the color blue. Then, after Goro bumps the table,

- The 1 in the first box falls back into the same box, because that is the only red box.
- The 4 and 2 in the second and sixth boxes remain in place with probability $\frac{1}{2}$, and switch places with probability $\frac{1}{2}$.
- The 3, 6, 5 in the third, fourth, and fifth boxes end up in one of the following orders, each with probability $\frac{1}{6}$:
  - $3, 6, 5$
  - $3, 5, 6$
  - $6, 3, 5$
  - $6, 5, 3$
  - $5, 3, 6$
  - $5, 6, 3$

So, for example, the probability of the bump leaving the balls in the order $1, 2, 3, 5, 6, 4$ is $\frac{1}{12}$. If Goro got this or some other non-sorted result, he would have to designate a set of box colors for the next round, and so on, until he eventually arrives at the sorted $1, 2, 3, 4, 5, 6$. Goro can assign colors to boxes in any way before each bump, regardless of previous assignments.

Can you help Goro implement a better strategy that will efficiently sort the balls? It is guaranteed that the balls start in a random non-sorted order.

### Interactive Protocol

This is an interactive problem.

Initially, your program should read a single line containing three integers, $T$ $N$ $K$: the number of test cases, the number of boxes per test case, and the total number of bumps allowed for all test cases combined. Then, $T$ test cases must be processed.

Each test case begins with the judge sending one line with $N$ integers, with each integer from 1 to $N$ appearing exactly once, and with the list chosen at random from all non-sorted lists. Then you must engage in a series of interactions with the judge. Each interaction works as follows:

- You send one line of $N$ integers $C_1, C_2, \ldots, C_N$, in which each integer is between 1 and $N$, inclusive. Each $C_i$ represents that you are assigning color $C_i$ to box $i$ for the next bump. You may choose how many colors there are and how they are numbered, but you must assign a color to each box.
- The judge simulates the bump as explained in the statement. If this results in the balls being in sorted order:
    - If this interaction was the $K$-th interaction across all test cases, and this was not the last test case, the judge sends one line with the integer $-1$ and does not output anything further.
    - Otherwise, the judge sends one line with the integer 1 and then immediately begins the next test case, if there is one. If this was the last test case, your program must exit without error and without sending anything further.
- Otherwise, the balls are not sorted, and:
    - If this interaction was the $K$-th across all test cases, or if you provided an invalid line (e.g., too few integers, or color numbers out of range), the judge sends one line with the integer $-1$ and does not output anything further.
    - If this was not your $K$-th interaction, the judge sends one line with the integer 0, and then another line with $N$ integers, with each integer from 1 to $N$ appearing exactly once, and in non-sorted order, representing the new order of the balls, that is, the $i$-th of these integers is the ball that fell into box $i$. Then you must begin another interaction.

As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment. Also, if your program continues to wait for the judge after receiving a $-1$, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error.

Be advised that the judge uses the same source of randomness each time, so in the absence of other errors (e.g. Time Limit Exceeded, Memory Limit Exceeded), submitting the exact same code twice will yield the same outcome twice.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
2 4 8
1 4 3 2

0
1 4 3 2

1
2 1 4 3

1
```
### 样例输出 #1
```


1 2 3 2


1 2 3 2


4 4 4 4
```
## 提示

**Sample Explanation**

Note that the sample interaction does not satisfy the constraints of any of the test sets. It is only presented to clarify the input and output format.

**Limits**

- $\mathbf{T} = 1000$.
- $\mathbf{N} = 100$.

**Test Set 1 (8 Pts, Visible Verdict)**

- $\mathbf{K} = 16500$.

**Test Set 2 (10 Pts, Visible Verdict)**

- $\mathbf{K} = 12500$.

**Test Set 3 (3 Pts, Visible Verdict)**

- $\mathbf{K} = 11500$.


---

---
title: "[GCJ 2012 #3] Perfect Game"
layout: "post"
diff: 提高+/省选-
pid: P13328
tag: ['数学', '贪心', '2012', '期望', 'Google Code Jam']
---
# [GCJ 2012 #3] Perfect Game
## 题目描述

You're playing a video game, in which you will get an achievement if you complete all of the levels consecutively without dying. You can play the levels in any order, and each time you play a level you'll either complete it or die. Each level has some probability that you'll complete it, and takes some amount of time. In what order should you play the levels so that the expected time it takes you to get the achievement is minimized? Assume that it takes equally long to beat a level or to die in it, and that you will start again from the first level in your ordering as soon as you die.

Note: If you fail to complete a level, you do not personally die—only your character in the game dies. If that were not the case, only a few people would try to earn this achievement.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, each of which consists of three lines. The first line of each test case contains a single integer $N$, the number of levels. The second line contains $N$ space-separated integers $L_i$. $L_i$ is the number of seconds level $i$ lasts, which is independent of whether you complete the level or die. The third line contains $N$ space-separated integers $P_i$. $P_i$ is the percent chance that you will die in any given attempt to complete level $i$.

## 输出格式

For each test case, output one line containing "Case #$x$: ", where $x$ is the case number (starting from 1), followed by $N$ space-separated integers. The $j^{th}$ integer in the list should be the index of the $j^{th}$ level you should attempt to beat in order to minimize the amount of time you expect to spend earning the achievement.

Indices go from 0 to $N-1$. If there are multiple orderings that would give the same expected time, output the lexicographically least ordering. Out of two orderings, the lexicographically smaller one is the one with the smaller index at the first location where they differ; out of many orderings, the lexicographically least one is the one that is lexicographically smaller than every other ordering.
## 样例

### 样例输入 #1
```
3
4
1 1 1 1
50 0 20 20
3
100 10 1
0 50 0
3
100 80 50
40 20 80
```
### 样例输出 #1
```
Case #1: 0 2 3 1
Case #2: 1 0 2
Case #3: 2 0 1
```
## 提示

**Sample Explanation**

Note that the second and third samples do not satisfy the constraints for the small input.

**Limits**

$1 \leq T \leq 100$.

$0 \leq P_i < 100$.

**Test set 1 (3 Pts, Visible Verdict)**

- $1 \leq N \leq 20$.
- $L_i = 1$.

**Test set 2 (7 Pts, Hidden Verdict)**

- $1 \leq N \leq 1000$.
- $1 \leq L_i \leq 100$.


---

---
title: "[GCJ 2011 Qualification] GoroSort"
layout: "post"
diff: 提高+/省选-
pid: P13364
tag: ['数学', '2011', 'Special Judge', '期望', 'Google Code Jam']
---
# [GCJ 2011 Qualification] GoroSort
## 题目描述

Goro has 4 arms. Goro is very strong. You don't mess with Goro. Goro needs to sort an array of $N$ different integers. Algorithms are not Goro's strength; strength is Goro's strength. Goro's plan is to use the fingers on two of his hands to hold down several elements of the array and hit the table with his third and fourth fists as hard as possible. This will make the unsecured elements of the array fly up into the air, get shuffled randomly, and fall back down into the empty array locations.

Goro wants to sort the array as quickly as possible. How many hits will it take Goro to sort the given array, on average, if he acts intelligently when choosing which elements of the array to hold down before each hit of the table? Goro has an infinite number of fingers on the two hands he uses to hold down the array.

More precisely, before each hit, Goro may choose any subset of the elements of the array to freeze in place. He may choose differently depending on the outcomes of previous hits. Each hit permutes the unfrozen elements uniformly at random. Each permutation is equally likely.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one will consist of two lines. The first line will give the number $N$. The second line will list the $N$ elements of the array in their initial order.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the expected number of hit-the-table operations when following the best hold-down strategy. Answers with an absolute or relative error of at most $10^{-6}$ will be considered correct.
## 样例

### 样例输入 #1
```
3
2
2 1
3
1 3 2
4
2 1 4 3
```
### 样例输出 #1
```
Case #1: 2.000000
Case #2: 2.000000
Case #3: 4.000000
```
## 提示

**Sample Explanation**

In test case #3, one possible strategy is to hold down the two leftmost elements first. Elements 3 and 4 will be free to move. After a table hit, they will land in the correct order $[3, 4]$ with probability $1/2$ and in the wrong order $[4, 3]$ with probability $1/2$. Therefore, on average it will take 2 hits to arrange them in the correct order. After that, Goro can hold down elements 3 and 4 and hit the table until 1 and 2 land in the correct order, which will take another 2 hits, on average. The total is then $2 + 2 = 4$ hits.

**Limits**

- $1 \leq T \leq 100$;
- The second line of each test case will contain a permutation of the $N$ smallest positive integers.

**Small dataset (10 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 10$;
- Time limit: ~~30~~ 3 seconds.

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 1000$;
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[GCJ 2009 Finals] Year of More Code Jam"
layout: "post"
diff: 提高+/省选-
pid: P13448
tag: ['动态规划 DP', '2009', '期望', 'Google Code Jam']
---
# [GCJ 2009 Finals] Year of More Code Jam
## 题目描述

A new year brings a new calendar, new challenges, and a lot of new fun in life. Some things, however, never change. There are still many great programming contests to be held, and our heroine Sphinny's passion for them remains unchanged.

There are several tournaments Sphinny is interested in. Each tournament will consist of a number of rounds. The organizer of each tournament has not decided on what date the tournament will start, but has decided how many rounds there will be in the tournament and how many days after the start date each round will be.

In some situations, two or more rounds (from different tournaments) can be scheduled on the same day. As Sphinny is so keen on problem solving, she will be happier if more rounds are scheduled on the same day. Her happiness value is computed as follows: for each day on which there are $S$ rounds, her happiness will be increased by $S^2$. Her happiness starts at $0$ (don't worry — $0$ is a happy place to start).

In the picture below there are three tournaments, each represented by a different color, and Sphinny's total happiness is $20$. One tournament starts on the second day of the year, one starts on the fifth day of the year, and one starts on the sixth day of the year.

![](https://cdn.luogu.com.cn/upload/image_hosting/qyyc8jir.png)

There are $N$ days in the year. Each tournament will begin on any of the $N$ days with equal probability. The big question for this year is what the expected value of Sphinny's happiness is.

As a perfectionist, she is not going to solve the problem approximately. Instead, she wants to know the result exactly. The number of tournaments is $T$, and there are $N^T$ equally likely ways to select the start dates of the tournaments. She is going to express her expected happiness as $K + A/B$, where $K$ and $B$ are positive integers and $A$ is a non-negative integer less than $B$. If $A$ is zero then $B$ must be one, otherwise $A$ and $B$ must not have a common factor greater than one.

If a tournament starts late enough in the year, some of its rounds might be scheduled during the next year. Those rounds do not contribute to Sphinny's happiness this year.
## 输入格式

The first line of the input is a single integer $C$, the number of test cases. $C$ tests follow. The first line of each test case is in the form

$N \ T$

where $N$ is the number of days in the year, and $T$ is the number of tournaments. $T$ lines then follow, one for each tournament, in the format

$m \ d_2 \ d_3 \ \ldots \ d_m$

indicating that there are $m$ rounds, and the $i$-th round will be held on day $d_i$ of the tournament. The first round of a tournament is held on day $1$ ($d_1 = 1$).

## 输出格式

For each test, output one line of the form

Case #$X$: $K+A/B$

where $X$ is the case number, starting from $1$, and $K$, $A$ and $B$ are as described above.
## 样例

### 样例输入 #1
```
2
1 1
2 2
4 2
3 2 4
2 3
```
### 样例输出 #1
```
Case #1: 1+0/1
Case #2: 5+1/8
```
## 提示

**Limits**

- $1 \leq C \leq 50$
- $1 \leq N \leq 10^{9}$
- $2 \leq m \leq 50$
- $1 < d_2 < d_3 < \ldots < d_m \leq 10000$

**Small dataset(5 Pts)**

- $1 \leq T \leq 2$

**Large dataset(12 Pts)**

- $1 \leq T \leq 50$



---

---
title: "WJMZBMR打osu! / Easy"
layout: "post"
diff: 提高+/省选-
pid: P1365
tag: ['期望']
---
# WJMZBMR打osu! / Easy
## 题目背景

原 维护队列 参见 P1903
## 题目描述

某一天 WJMZBMR 在打 osu，~~但是他太弱了，有些地方完全靠运气:(~~。

我们来简化一下这个游戏的规则

有 $n$ 次点击要做，成功了就是 `o`，失败了就是 `x`，分数是按 combo 计算的，连续 $a$ 个 combo 就有 $a\times a$ 分，combo 就是极大的连续 `o`。

比如`ooxxxxooooxxx`，分数就是 $2 \times 2 + 4 \times 4 = 4 +16=20$。

Sevenkplus 闲的慌就看他打了一盘，有些地方跟运气无关要么是 `o` 要么是 `x`，有些地方 `o` 或者 `x` 各有 $50\%$ 的可能性，用 `?` 号来表示。

比如 `oo?xx` 就是一个可能的输入。
那么 WJMZBMR 这场 osu 的期望得分是多少呢？

比如 `oo?xx` 的话，`?` 是 `o` 的话就是 `oooxx`（$9$），是x的话就是 `ooxxx`（$4$），期望自然就是 $(4+9)/2 =6.5$ 了。
## 输入格式

第一行一个整数 $n$（$n\le3\times10^5$），表示点击的个数

接下来一个字符串，每个字符都是 `o`，`x`，`?` 中的一个

## 输出格式

一行一个浮点数表示答案

四舍五入到小数点后 $4$ 位

如果害怕精度跪建议用 long double 或者 extended。
## 样例

### 样例输入 #1
```
4
????
```
### 样例输出 #1
```
4.1250
```


---

---
title: "[NOIP 2016 提高组] 换教室"
layout: "post"
diff: 提高+/省选-
pid: P1850
tag: ['动态规划 DP', '2016', 'NOIP 提高组', '期望']
---
# [NOIP 2016 提高组] 换教室
## 题目背景

NOIP2016 提高组 D1T3
## 题目描述

对于刚上大学的牛牛来说，他面临的第一个问题是如何根据实际情况申请合适的课程。


在可以选择的课程中，有 $2n$ 节课程安排在 $n$ 个时间段上。在第 $i$（$1 \leq i \leq n$）个时间段上，两节内容相同的课程同时在不同的地点进行，其中，牛牛预先被安排在教室 $c_i$ 上课，而另一节课程在教室 $d_i$ 进行。


在不提交任何申请的情况下，学生们需要按时间段的顺序依次完成所有的 $n$ 节安排好的课程。如果学生想更换第 $i$ 节课程的教室，则需要提出申请。若申请通过，学生就可以在第 $i$ 个时间段去教室 $d_i$ 上课，否则仍然在教室 $c_i$ 上课。


由于更换教室的需求太多，申请不一定能获得通过。通过计算，牛牛发现申请更换第 $i$ 节课程的教室时，申请被通过的概率是一个已知的实数 $k_i$，并且对于不同课程的申请，被通过的概率是互相独立的。


学校规定，所有的申请只能在学期开始前一次性提交，并且每个人只能选择至多 $m$ 节课程进行申请。这意味着牛牛必须一次性决定是否申请更换每节课的教室，而不能根据某些课程的申请结果来决定其他课程是否申请；牛牛可以申请自己最希望更换教室的 $m$ 门课程，也可以不用完这 $m$ 个申请的机会，甚至可以一门课程都不申请。


因为不同的课程可能会被安排在不同的教室进行，所以牛牛需要利用课间时间从一间教室赶到另一间教室。


牛牛所在的大学有 $v$ 个教室，有 $e$ 条道路。每条道路连接两间教室，并且是可以双向通行的。由于道路的长度和拥堵程度不同，通过不同的道路耗费的体力可能会有所不同。 当第 $i$（$1 \leq i \leq n-1$）节课结束后，牛牛就会从这节课的教室出发，选择一条耗费体力最少的路径前往下一节课的教室。


现在牛牛想知道，申请哪几门课程可以使他因在教室间移动耗费的体力值的总和的期望值最小，请你帮他求出这个最小值。

## 输入格式

第一行四个整数 $n,m,v,e$。$n$ 表示这个学期内的时间段的数量；$m$ 表示牛牛最多可以申请更换多少节课程的教室；$v$ 表示牛牛学校里教室的数量；$e$ 表示牛牛的学校里道路的数量。


第二行 $n$ 个正整数，第 $i$（$1 \leq i \leq n$）个正整数表示 $c_i$，即第 $i$ 个时间段牛牛被安排上课的教室；保证 $1 \le c_i \le v$。


第三行 $n$ 个正整数，第 $i$（$1 \leq i \leq n$）个正整数表示 $d_i$，即第 $i$ 个时间段另一间上同样课程的教室；保证 $1 \le d_i \le v$。


第四行 $n$ 个实数，第 $i$（$1 \leq i \leq n$）个实数表示 $k_i$，即牛牛申请在第 $i$ 个时间段更换教室获得通过的概率。保证 $0 \le k_i \le 1$。


接下来 $e$ 行，每行三个正整数 $a_j, b_j, w_j$，表示有一条双向道路连接教室 $a_j, b_j$，通过这条道路需要耗费的体力值是 $w_j$；保证 $1 \le a_j, b_j \le v$，$1 \le w_j \le 100$。


保证 $1 \leq n \leq 2000$，$0 \leq m \leq 2000$，$1 \leq v \leq 300$，$0 \leq e \leq 90000$。


保证通过学校里的道路，从任何一间教室出发，都能到达其他所有的教室。


保证输入的实数最多包含 $3$ 位小数。

## 输出格式

输出一行，包含一个实数，四舍五入精确到小数点后恰好 $2$ 位，表示答案。你的输出必须和标准输出完全一样才算正确。

测试数据保证四舍五入后的答案和准确答案的差的绝对值不大于 $4 \times 10^{-3}$。（如果你不知道什么是浮点误差，这段话可以理解为：对于大多数的算法，你可以正常地使用浮点数类型而不用对它进行特殊的处理）

## 样例

### 样例输入 #1
```
3 2 3 3
2 1 2
1 2 1
0.8 0.2 0.5 
1 2 5
1 3 3
2 3 1

```
### 样例输出 #1
```
2.80
```
## 提示

**样例 1 说明**

所有可行的申请方案和期望收益如下：

- 不作申请，耗费的体力值的期望为 $8.0$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     无      |  $1.0$  |  $8$  |

- 申请更换第 $1$ 个时间段的上课教室，耗费的体力值的期望为 $4.8$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $1$      |  $0.8$  |  $4$  |
|     无      |  $0.2$  |  $8$  |

- 申请更换第 $2$ 个时间段的上课教室，耗费的体力值的期望为 $6.4$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $2$      |  $0.2$  |  $0$  |
|     无      |  $0.8$  |  $8$  |

- 申请更换第 $3$ 个时间段的上课教室，耗费的体力值的期望为 $6.0$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $3$      |  $0.5$  |  $4$  |
|     无      |  $0.5$  |  $8$  |

- 申请更换第 $1,2$ 个时间段的上课教室，耗费的体力值的期望为 $4.48$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $1,2$      |  $0.16$  |  $4$  |
|     $1$      |  $0.64$  |  $4$  |
|     $2$     |  $0.04$  |  $0$  |
|     无      |  $0.16$  |  $8$  |

- 申请更换第 $1,3$ 个时间段的上课教室，耗费的体力值的期望为 $2.8$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $1,3$      |  $0.4$  |  $0$  |
|     $1$      |  $0.4$  |  $4$  |
|     $3$     |  $0.1$  |  $4$  |
|     无      |  $0.1$  |  $8$  |

- 申请更换第 $2,3$ 个时间段的上课教室，耗费的体力值的期望为 $5.2$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $2,3$      |  $0.1$  |  $4$  |
|     $2$      |  $0.1$  |  $0$  |
|     $3$     |  $0.4$  |  $4$  |
|     无      |  $0.4$  |  $8$  |

因此，最优方案为：申请更换第 $1,3$ 个时间段的上课教室。耗费的体力值的期望为 $2.8$。 

**提示**

1. 道路中可能会有多条双向道路连接相同的两间教室。 也有可能有道路两端连接的是同一间教室。
2. 请注意区分 $n,m,v,e$ 的意义, $n$ 不是教室的数量, $m$ 不是道路的数量。

**数据范围与说明**

| 测试点编号 | $n\le$ | $m\le$ | $v\le$ | 是否具有特殊性质 1 | 是否具有特殊性质 2 |
| :--------: | :----: | :----: | :----: | :----------------: | :----------------: |
|     1      |  $1$   |  $1$   | $300$  |      $\times$      |      $\times$      |
|     2      |  $2$   |  $0$   |  $20$  |      $\times$      |      $\times$      |
|     3      |  $2$   |  $1$   | $100$  |      $\times$      |      $\times$      |
|     4      |  $2$   |  $2$   | $300$  |      $\times$      |      $\times$      |
|     5      |  $3$   |  $0$   |  $20$  |      $\surd$       |      $\surd$       |
|     6      |  $3$   |  $1$   | $100$  |      $\surd$       |      $\times$      |
|     7      |  $3$   |  $2$   | $300$  |      $\times$      |      $\times$      |
|     8      |  $10$  |  $0$   | $300$  |      $\surd$       |      $\surd$       |
|     9      |  $10$  |  $1$   |  $20$  |      $\surd$       |      $\times$      |
|     10     |  $10$  |  $2$   | $100$  |      $\times$      |      $\times$      |
|     11     |  $10$  |  $10$  | $300$  |      $\times$      |      $\surd$       |
|     12     |  $20$  |  $0$   |  $20$  |      $\surd$       |      $\times$      |
|     13     |  $20$  |  $1$   | $100$  |      $\times$      |      $\times$      |
|     14     |  $20$  |  $2$   | $300$  |      $\surd$       |      $\times$      |
|     15     |  $20$  |  $20$  | $300$  |      $\times$      |      $\surd$       |
|     16     | $300$  |  $0$   |  $20$  |      $\times$      |      $\times$      |
|     17     | $300$  |  $1$   | $100$  |      $\times$      |      $\times$      |
|     18     | $300$  |  $2$   | $300$  |      $\surd$       |      $\surd$       |
|     19     | $300$  | $300$  | $300$  |      $\times$      |      $\surd$       |
|     20     | $2000$ |  $0$   |  $20$  |      $\times$      |      $\times$      |
|     21     | $2000$ |  $1$   |  $20$  |      $\times$      |      $\times$      |
|     22     | $2000$ |  $2$   | $100$  |      $\times$      |      $\times$      |
|     23     | $2000$ | $2000$ | $100$  |      $\times$      |      $\times$      |
|     24     | $2000$ | $2000$ | $300$  |      $\times$      |      $\times$      |
|     25     | $2000$ | $2000$ | $300$  |      $\times$      |      $\times$      |
 

特殊性质 1：图上任意不同的两点 $u,v$ 间，存在一条耗费体力最少的路径只包含一条道路。

特殊性质 2：对于所有的 $1≤ i≤ n,\ k_i= 1$。



---

---
title: "[HAOI2012] 高速公路"
layout: "post"
diff: 提高+/省选-
pid: P2221
tag: ['2012', '河南', '线段树', '各省省选', 'O2优化', '最大公约数 gcd', '期望']
---
# [HAOI2012] 高速公路
## 题目背景

Y901 高速公路是一条重要的交通纽带，政府部门建设初期的投入以及使用期间的养护费用都不低，因此政府在这条高速公路上设立了许多收费站。
## 题目描述

Y901 高速公路是一条由 $n-1$ 段路以及 $n$ 个收费站组成的东西向的链，我们按照由西向东的顺序将收费站依次编号为 $1 \sim n$，从收费站 $i$ 行驶到 $i+1$（或从 $i+1$ 行驶到 $i$）需要收取 $v_i$ 的费用。高速路刚建成时所有的路段都是免费的，即所有 $v_i = 0$。

政府部门根据实际情况，会不定期地对连续路段的收费标准进行调整，根据政策涨价或降价。

无聊的小 A 同学总喜欢研究一些稀奇古怪的问题，他开车在这条高速路上行驶时想到了这样一个问题：对于给定的 $l,r$，在第 $l$ 个到第 $r$ 个收费站里等概率随机取出两个不同的收费站 $a$ 和 $b$，那么从 $a$ 行驶到 $b$ 将期望花费多少费用呢?

## 输入格式

第一行有两个整数，分别表示收费站个数 $n$，和询问与调整费用的总数 $m$。

接下来 $m$ 行，每行表示一次调整或询问，首先有一个字符 $op$。

- 若 $op$ 为 `C`，则后面有三个整数 $l, r, v$，表示将第 $l$ 个收费站到第 $r$ 个收费站之间所有**道路**的通行费用增加 $v$。
- 若 $op$ 为 `Q`，则后面有两个整数 $l, r$，对于给定的 $l, r$，请回答小 A 的问题。
## 输出格式

对于每次询问，输出一行一个既约分数表示答案。

若答案为一个整数 $a$，请输出 `a/1`。
## 样例

### 样例输入 #1
```
4 5
C 1 4 2
C 1 2 -1
Q 1 2
Q 2 4
Q 1 4

```
### 样例输出 #1
```
1/1
8/3
17/6

```
## 提示

#### 数据规模与约定

本题共 $10$ 个测试点，各测试点数据规模如下表所示


| 测试点编号 | $n=$ | $m=$ |
| :------: | :---: | :-: |
|$1$| $10$ |$10$|
|$2$|    $100$ |    $100$ |
|$3$  |  $1000$ |   $1000$|
|$4$   | $10000$ |   $10000$|
|$5$    |$50000$  |  $50000$|
|$6$  |  $60000$   | $60000$|
|$7$   | $70000$ |   $70000$|
|$8$   | $80000$  |  $80000$|
|$9$    |$90000$   | $90000$|
|$10$   | $100000$  |  $100000$|

对于全部的测试点，保证 $1 \leq n, m \leq 10^5$，$op \in \{\texttt C, \texttt Q\}$，$1 \leq l \leq r \leq n$，$-10^4 \leq v \leq 10^4$，在任何时刻，$0\leq v_i \leq 10^4$。


---

---
title: "小学数学题"
layout: "post"
diff: 提高+/省选-
pid: P3921
tag: ['动态规划 DP', '洛谷原创', 'O2优化', '广度优先搜索 BFS', '期望']
---
# 小学数学题
## 题目背景

露米娅：我来先考你一道小学数学题吧！

琪露诺：好！小学的题我肯定都会！

## 题目描述

露米娅：有 $ n $ 只妖精要跨过雾之湖，由于湖边大雾弥漫，妖精们看不清湖到底有多大，不想从边上绕过去。

湖上有一~~条船~~个传送器，且这个传送器每次只能载 $ r $ 只妖精跨过湖面（注意传送器可以同时把两侧的妖精分别运到对岸，但每次运送的总妖精数不能超过 $ r $ ）。

这些妖精还很喜欢搞事，所以在任何时刻，都需要满足一些条件，其中第一种条件有 $ m_1 $ 个，第二种条件有 $ m_2 $ 个。

第一种条件形如 妖精 $ a $ 和妖精 $ b $ 必须要在湖的同一侧；

第二种条件形如 当妖精 $ a $ 在湖的一侧时，妖精 $ b $ 和妖精 $ c $ 不能同时在湖的另一侧。


现在给出这些条件，求：

1. 至少需要传送器几次才能让所有妖精到湖的对岸

2. 在保证次数最少的前提下，求过河方案数

## 输入格式

第一行四个整数 $ n , m_1 , m_2 , r $

接下来 $ m_1 $ 行每行2个整数 $ a , b $，代表第一种条件

接下来 $ m_2 $ 行每行3个整数 $ a , b , c $， 代表第二种条件

## 输出格式

两个整数，分别为最少使用传送器次数和方案数，用空格分隔

若无法全部过河，输出"-1 0"（不含引号）

## 样例

### 样例输入 #1
```
1 0 0 1

```
### 样例输出 #1
```
1 1

```
### 样例输入 #2
```
5 0 0 2

```
### 样例输出 #2
```
3 90

```
### 样例输入 #3
```
3 1 0 1
1 2

```
### 样例输出 #3
```
-1 0

```
## 提示

对于 $ 30 \% $ 的数据， $ n \leq 10 $

对于另外 $ 10 \% $ 的数据， $ m_1 = m_2 = 0 $

对于 $ 100 \% $ 的数据， $ a,b,c \leq n \leq 15 $， $ m_1 , m_2 \leq 50 $， $ r \leq 10^9 $


请不要相信洛谷评测机的速度，如果得了80分以上，可以等人少的时候再交一次。但如果得了60分以下，说明可能写的不是正解，就不要再虐萌萌哒评测机啦



---

---
title: "康娜的线段树"
layout: "post"
diff: 提高+/省选-
pid: P3924
tag: ['线段树', '洛谷原创', 'O2优化', '前缀和', '期望', '洛谷月赛']
---
# 康娜的线段树
## 题目描述

小林是个程序媛，不可避免地康娜对这种人类的“魔法”产生了浓厚的兴趣，于是小林开始教她OI。

 ![](https://cdn.luogu.com.cn/upload/pic/8043.png) 

今天康娜学习了一种叫做线段树的神奇魔法，这种魔法可以维护一段区间的信息，是非常厉害的东西。康娜试着写了一棵维护区间和的线段树。由于她不会打标记，因此所有的区间加操作她都是暴力修改的。具体的代码如下：

```cpp
struct Segment_Tree{
#define lson (o<<1)
#define rson (o<<1|1)
    int sumv[N<<2],minv[N<<2];
    inline void pushup(int o){sumv[o]=sumv[lson]+sumv[rson];}
    inline void build(int o,int l,int r){
        if(l==r){sumv[o]=a[l];return;}
        int mid=(l+r)>>1;
        build(lson,l,mid);build(rson,mid+1,r);
        pushup(o);
    }
    inline void change(int o,int l,int r,int q,int v){
        if(l==r){sumv[o]+=v;return;}
        int mid=(l+r)>>1;
        if(q<=mid)change(lson,l,mid,q,v);
        else change(rson,mid+1,r,q,v);
        pushup(o);
    }
}T; 
```

在修改时，她会这么写：

```cpp
for(int i=l;i<=r;i++)T.change(1,1,n,i,addv);
```
显然，这棵线段树每个节点有一个值，为该节点管辖区间的区间和。

康娜是个爱思考的孩子，于是她突然想到了一个问题：

如果每次在线段树区间加操作做完后，从根节点开始等概率的选择一个子节点进入，直到进入叶子结点为止，将一路经过的节点权值累加，最后能得到的期望值是多少？

康娜每次会给你一个值 $qwq$ ，保证你求出的概率乘上 $qwq$ 是一个整数。

这个问题太简单了，以至于聪明的康娜一下子就秒了。

现在她想问问你，您会不会做这个题呢？

## 输入格式

第一行整数 $n,m,qwq$ 表示线段树维护的原序列的长度，询问次数，分母。

第二行 $n$ 个数，表示原序列。

接下来 $m$ 行，每行三个数 $l,r,x$ 表示对区间$[l,r]$ 加上 $x$

## 输出格式

共 $m$ 行，表示期望的权值和乘上qwq结果。

## 样例

### 样例输入 #1
```
8 2 1
1 2 3 4 5 6 7 8
1 3 4
1 8 2

```
### 样例输出 #1
```
90
120
```
## 提示

对于30%的数据，保证 $1 \leq n,m \leq 100$

对于70%的数据，保证 $1 \leq n,m, \leq 10^{5}$

对于100%的数据，保证$1 \leq n,m \leq 10^6 $

$-1000 \leq a_i,x \leq 1000$



---

---
title: "[NOI2005] 聪聪与可可"
layout: "post"
diff: 提高+/省选-
pid: P4206
tag: ['搜索', '2005', 'NOI', '广度优先搜索 BFS', '深度优先搜索 DFS', '记忆化搜索', '期望']
---
# [NOI2005] 聪聪与可可
## 题目描述

在一个魔法森林里，住着一只聪明的小猫聪聪和一只可爱的小老鼠可可。虽然灰姑娘非常喜欢她们俩，但是，聪聪终究是一只猫，而可可终究是一只老鼠，同样不变的是，聪聪成天想着要吃掉可可。

一天，聪聪意外得到了一台非常有用的机器，据说是叫 GPS，对可可能准确的定位。有了这台机器，聪聪要吃可可就易如反掌了。于是，聪聪准备马上出发，去找可可。而可怜的可可还不知道大难即将临头，仍在森林里无忧无虑的玩耍。小兔子乖乖听到这件事，马上向灰姑娘报告。灰姑娘决定尽快阻止聪聪，拯救可可，可她不知道还有没有足够的时间。

整个森林可以认为是一个无向图，图中有 $N$ 个美丽的景点，景点从 $1$ 至 $N$ 编号。小动物们都只在景点休息、玩耍。在景点之间有一些路连接。

当聪聪得到 GPS 时，可可正在景点 $M$（$M \le N$）处。以后的每个时间单位，可可都会选择去相邻的景点（可能有多个）中的一个或停留在原景点不动。而去这些地方所发生的概率是相等的。假设有 $P$ 个景点与景点 $M$ 相邻，它们分别是景点 $R$、景点 $S$、……、景点 $Q$，在时刻 $T$ 可可处在景点 $M$，则在 $(T+1)$ 时刻，可可有 $1/(1 +P)$ 的可能在景点 $R$，有 $1/(1 +P)$ 的可能在景点 $S$，……，有 $1/(1 +P)$ 的可能在景点 $Q$，还有$1/(1 +P)$的可能停在景点 $M$。

我们知道，聪聪是很聪明的，所以，当她在景点 $C$ 时，她会选一个更靠近可可的景点，如果这样的景点有多个，她会选一个标号最小的景点。由于聪聪太想吃掉可可了，如果走完第一步以后仍然没吃到可可，她还可以在本段时间内再向可可走近一步。

在每个时间单位，假设聪聪先走，可可后走。在某一时刻，若聪聪和可可位于同一个景点，则可怜的可可就被吃掉了。

灰姑娘想知道，平均情况下，聪聪几步就可能吃到可可。而你需要帮助灰姑娘尽快的找到答案。
## 输入格式

数据的第 1 行为两个整数 $N$ 和 $E$，以空格分隔，分别表示森林中的景点数和连接相邻景点的路的条数。

第 2 行包含两个整数 $C$ 和 $M$，以空格分隔，分别表示初始时聪聪和可可所在的景点的编号。

接下来 E 行，每行两个整数，第 $i+2$ 行的两个整数 $A_i$ 和 $B_i$ 表示景点 $A_i$ 和景点 $B_i$ 之间有一条路。所有的路都是无向的，即：如果能从 A 走到 B，就可以从 B 走到 A。

输入保证任何两个景点之间不会有多于一条路直接相连，且聪聪和可可之间必有路直接或间接的相连。
## 输出格式

输出 1 个实数，四舍五入保留三位小数，表示平均多少个时间单位后聪聪会把可可吃掉。
## 样例

### 样例输入 #1
```
4 3 
1 4 
1 2 
2 3 
3 4
```
### 样例输出 #1
```
1.500 

```
### 样例输入 #2
```
9 9 
9 3 
1 2 
2 3 
3 4 
4 5 
3 6 
4 6 
4 7 
7 8 
8 9
```
### 样例输出 #2
```
2.167
```
## 提示

【样例说明 1】 

开始时，聪聪和可可分别在景点 1 和景点 4。 

第一个时刻，聪聪先走，她向更靠近可可(景点 4)的景点走动，走到景点 2， 然后走到景点 3；假定忽略走路所花时间。 

可可后走，有两种可能： 第一种是走到景点 3，这样聪聪和可可到达同一个景点，可可被吃掉，步数为 $1$，概率为$0.5$。
 
第二种是停在景点 4，不被吃掉。概率为 $0.5$。

到第二个时刻，聪聪向更靠近可可(景点 4)的景点走动，只需要走一步即和 可可在同一景点。因此这种情况下聪聪会在两步吃掉可可。 所以平均的步数是 $1\times 1/2 + 2\times 1/2 =1.5$ 步。

【样例说明 2】

森林如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/8uiq0ltc.png)

对于 50%的数据，$1≤N≤50$。  
对于所有的数据，$1≤N,E≤1000$。 


---

---
title: "收集邮票"
layout: "post"
diff: 提高+/省选-
pid: P4550
tag: ['递推', '期望']
---
# 收集邮票
## 题目描述

有 $n$ 种不同的邮票，皮皮想收集所有种类的邮票。唯一的收集方法是到同学凡凡那里购买，每次只能买一张，并且买到的邮票究竟是 $n$ 种邮票中的哪一种是等概率的，概率均为 $1/n$。但是由于凡凡也很喜欢邮票，所以皮皮购买第 $k$ 次邮票需要支付 $k$ 元钱。

现在皮皮手中没有邮票，皮皮想知道自己得到所有种类的邮票需要花费的钱数目的期望。
## 输入格式

一行，一个数字 $N$（$N \le 10000$）。
## 输出格式

输出要付出多少钱，保留二位小数。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
21.25
```


---

---
title: "[JXOI2018] 游戏"
layout: "post"
diff: 提高+/省选-
pid: P4562
tag: ['数学', '2018', '各省省选', '组合数学', '期望']
---
# [JXOI2018] 游戏
## 题目背景

九条可怜是一个富有的女孩子。
## 题目描述

她长大以后创业了，开了一个公司。 但是管理公司是一个很累人的活，员工们经常背着可怜偷懒，可怜需要时不时对办公室进行检查。

可怜公司有 $n$ 个办公室，办公室编号是 $l$ 到 $l+n-1$ ，可怜会事先制定一个顺序，按照这个顺序依次检查办公室。一开始的时候，所有办公室的员工都在偷懒，当她检查完编号是 $i$ 的办公室时候，这个办公室的员工会认真工作，并且这个办公室的员工通知所有办公室编号是 $i$ 的倍数的办公室，通知他们老板来了，让他们认真工作。因此，可怜检查完第 $i$ 个办公室的时候，所有编号是 $i$ 的倍数(包括 $i$ )的办公室的员工会认真工作。

可怜发现了员工们通风报信的行为，她发现，对于每种不同的顺序 $p$ ，都存在一个最小的 $t(p)$ ，使得可怜按照这个顺序检查完前 $t(p)$ 个办公室之后，所有的办公室都会开始认真工作。她把这个 $t(p)$ 定义为 $p$ 的检查时间。

可怜想知道所有 $t(p)$ 的和。

但是这个结果可能很大，她想知道和对 $10^9+7$ 取模后的结果。
## 输入格式

第一行输入两个整数 $l,r$ 表示编号范围，题目中的 $n$ 就是 $r-l+1$ 。
## 输出格式

一个整数，表示所有 $t(p)$ 的和。
## 样例

### 样例输入 #1
```
2 4
```
### 样例输出 #1
```
16

```
## 提示

### 样例解释

考虑所有办公室被检查的相对顺序:

{2 3 4} ,时间是 2 。
{3 2 4} ,时间是 2 。
{4 2 3} ,时间是 3 。
{4 3 2} ,时间是 3 。
{2 4 3} ,时间是 3 。
{3 4 2} ,时间是 3 。

和是 $16$ 。

### 数据范围

对于 20% 的数据，$r-l+1\leq 8$。  
对于另 10% 的数据，$l=1$。  
对于另 10% 的数据，$l=2$。  
对于另 30% 的数据，$l\leq 200$。  
对于 100% 的数据，$1\leq l\leq r\leq 10^7$。


---

---
title: "[1007] 梦美与线段树"
layout: "post"
diff: 提高+/省选-
pid: P4927
tag: ['线段树', '概率论', '期望', '洛谷月赛']
---
# [1007] 梦美与线段树
## 题目背景

欢迎大家光临星象馆

这里有着无论何时永远不会消失

美丽的无穷光辉

满天的星星等候着大家的到来
## 题目描述

梦美为了研究星象馆的星星，用巨型投影机——耶拿将星星排成了一个序列，接着梦美将这个星星序列建成了一棵线段树。

这是一棵维护区间和的线段树，每个节点的权值是该节点所对应的区间中，所有星星的权值和。有的时候梦美会从这棵线段树的根节点开始在星空游历。当她要进入子节点的时候，假设左右子树对应区间的权值和分别为 $sum_l$  和 $sum_r$，当前节点的权值为 $sum_{cur}$ ，梦美会以 $\frac{sum_l}{sum_{cur}}$ 的概率进入左子树，否则进入右子树。

游历的时候，梦美会把她经过的节点的权值累加起来，现在她希望您帮她设计一个算法求出这个权值期望下是多少。

当然，如果星星都是不变的梦美会觉得很没有意思，因此她会发出一些指令，每个指令是，对下标在 $[l,r]$ 的星星，权值加上 $v$ 。不过由于馆里的工作人员全都离开了，因此没有人教梦美在线段树上维护懒标记，所以梦美的每次指令都会实时更新所有的线段树节点。

为了解决线段树写法不一的问题，此处给出梦美维护这个问题时的部分代码：
```cpp
const int N = 100010, MOD = 998244353;
int a[N], sum[N << 2];
#define lson (o << 1)
#define rson (o << 1 | 1)
void pushup(int o) {
	sum[o] = (sum[lson] + sum[rson]) % MOD;
}
void build(int o, int l, int r) {
	if (l == r) {
		sum[o] = a[l];
	} else {
		int mid = (l + r) >> 1;
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(o);
	}
}
void change(int o, int l, int r, int q, int v) {
	if (l == r) {
		sum[o] = (sum[o] + v) % MOD;
		return;
	}
	int mid = (l + r) >> 1;
	if (q <= mid) change(lson, l, mid, q, v);
	else change(rson, mid + 1, r, q, v);
	pushup(o);
}
void add_to_interval(int l, int r, int v) {
	for (int i = l; i <= r; i ++) {
		change(1, 1, n, i, v);
	}
}
```
其中 `a` 数组表示每个星星的权值，`sum` 数组表示每个线段树节点的权值，`add_to_interval` 函数表示一次操作。
## 输入格式

第一行两个整数 $n,m$，表示序列长度和操作次数。

第二行 $n$ 个整数，表示这个序列。

接下来 $m$ 行，每行为

$1 \ l \ r \ v$，表示区间 $[l,r]$ 的节点加上了 $v$；

$2$ ，表示一次询问。
## 输出格式

对于每一个 $2$ 操作，输出一个答案。令答案化成最简分数为 $\frac{p}{q}$（保证 $q$ 不是 $998244353$ 的倍数），则输出 $p\cdot q^{-1}\mod 998244353$。
## 样例

### 样例输入 #1
```
4 3
1 2 3 4
2
1 1 3 1
2
```
### 样例输出 #1
```
399297760
844668322
```
## 提示

对于 $30\%$ 的数据，保证 $1 \leq n,m\leq 100$；

对于另外 $20\%$ 的数据，满足所有操作 1 中 $l=r$；

对于 $100\%$ 的数据，保证 $1\leq n,m \leq 10^5,1 \leq a_i,v \leq 10^9,1\le l\le r\le n$。

样例答案实际是 $\frac{94}{5}$ 和 $\frac{303}{13}$。


---

---
title: "水の造题"
layout: "post"
diff: 提高+/省选-
pid: P5011
tag: ['素数判断,质数,筛法', '期望', '逆元']
---
# 水の造题
## 题目背景

第一分钟,$CYJian$说:"要有样子."于是便有了$k$种动作..

第二分钟,$CYJian$说:"要有活力."于是便有了$k$种动作组成的总动作数为$N$的搏击操.

第三分钟,$CYJian$说:"要有数学."于是便有了一套搏击操的威力.

第四分钟,$CYJian$说:"数字要小."于是便有了一个伟大的模数$19491001$.

第五分钟,$CYJian$说:"要有规律."于是便有了一套搏击操威力的计算方法.

第六分钟,$CYJian$说:"要有限制."于是便有了时空限制以及数据范围.

第七分钟,$CYJian$说:"要有答案."于是便有了这道题让你做掉.

...

第*分钟,巨佬$Imagine$说:"数据太水."于是蒟蒻出题人疯了..(详见数据范围)
## 题目描述

现在有一套由$k$种动作组成的动作总数为$N$的搏击操.

已知第$1$,$2$...$k$个动作的威力为$a[1...k]$

且如果第一个动作后紧接着第二个动作,则威力会额外加上$a[1]+a[2]$

如果第二个动作后紧接着第三个动作,则威力会额外加上$a[2]+a[3]$

...

如果第$k$个动作后紧接着第一个动作,则威力会额外加上$a[k]+a[1]$

请求出最后动作的期望威力..

当然,还是要用伟大的模数$19491001$来膜一膜的...
## 输入格式

第一行,一个正整数$N$

第二行,一个正整数$k$

第三行,$k$个正整数$a[1...k]$
## 输出格式

一行,一个正整数表示期望的威力模$19491001$的值.
## 样例

### 样例输入 #1
```
2
6
1 2 3 4 5 6

```
### 样例输出 #1
```
16242509

```
## 提示

样例解释：

```
x-y 表示第一个动作为x，第二个动作为y

1-1 : 1+1=2
1-2 : 1+2+(1+2)=6
1-3 : 1+3=4
1-4 : 1+4=5
1-5 : 1+5=6
1-6 : 1+6=7
2-1 : 2+1=3
2-2 : 2+2=4
2-3 : 2+3+(2+3)=10
2-4 : 2+4=6
2-5 : 2+5=7
2-6 : 2+6=8
3-1 : 3+1=4
3-2 : 3+2=5
3-3 : 3+3=6
3-4 : 3+4+(3+4)=14
3-5 : 3+5=8
3-6 : 3+6=9
4-1 : 4+1=5
4-2 : 4+2=6
4-3 : 4+3=7
4-4 : 4+4=8
4-5 : 4+5+(4+5)=18
4-6 : 4+6=10
5-1 : 5+1=6
5-2 : 5+2=7
5-3 : 5+3=8
5-4 : 5+4=9
5-5 : 5+5=10
5-6 : 5+6+(5+6)=22
6-1 : 6+1+(6+1)=14
6-2 : 6+2=8
6-3 : 6+3=9
6-4 : 6+4=10
6-5 : 6+5=11
6-6 : 6+6=12

2+6+4+5+6+7+3+4+10+6+7+8+4+5+6+14+8+9+5+6+7+8+18+10+6+7+8+9+10+22+14+8+9+10+11+12=294

294/36=49/6

1/6 = 16242501 (mod 19491001)

ans = 49 * 16242501 mod 19491001 = 16242509
```

$Subtask 1$($20 pts$):$1 \leq N \leq 10 \qquad 1 \leq k \leq 7$ 

$Subtask 2$($20 pts$):$1 \leq N \leq 10^6 \qquad 1 \leq k \leq 7$ 

$Subtask 3$($20 pts$):$1 \leq N \leq 10^{40000} \qquad 1 \leq k \leq 7$ 

$Subtask 4$($20 pts$):$1 \leq N \leq 10^{10^6} \qquad 1 \leq k \leq 7$ 

$Subtask 5$($20 pts$):$1 \leq N \leq 10^{10^6} \qquad 1 \leq k \leq 10^6$ 

保证所有的数据: $1 \leq a[i] \leq 10^7$

## 注意:本题捆绑测试

小提示：

可以用下面的inv(x)求出x的逆元：

```
long long mod = 19491001;

long long quick_pow(long long x, int k) {
    long long res = 1;
    while(k) {
        if(k & 1) res = res * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return res;
}

long long inv(long long x) {
    return quick_pow(x, mod - 2);
}
```


---

---
title: "纯粹容器"
layout: "post"
diff: 提高+/省选-
pid: P6046
tag: ['动态规划 DP', '数学', '2020', '期望']
---
# 纯粹容器
## 题目背景

白王正在挑选容器。
## 题目描述

白王制造了 $n$ 个容器，并将它们排成了一队，从左到右依次编号为 $1 \sim n$。第 $i$ 个容器的**强度**为 $a_i$，保证 $a_i$ 互不相同。为了挑选出最纯粹的容器，白王会进行 $n-1$ 轮操作，每轮操作中，他会等概率随机挑选两个 **位置相邻** 且 **未被击倒** 的容器，令它们进行决斗，在一次决斗中，强度较小的容器将会被击倒并移出队列。

显然最后留下的是强度最大的容器，但是，可怜的容器们很想知道自己能够活多久，于是，它们请你对每个容器求出它存活轮数的期望。答案对 $998244353$ 取模。

一个容器的存活轮数为最大的非负整数 $x < n$ 满足它在第 $x$ 轮未被击倒。

两个容器 $i$ 和 $j$ 位置相邻当且仅当不存在 $k$ 满足 $i<k<j$ 且 $k$ 号容器未被击倒。
## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个整数 $a_1, a_2,\cdots,a_n$，意义见题目描述。
## 输出格式

一行 $n$ 个整数，第 $i$ 个整数表示第 $i$ 个容器的存活轮数的期望。为了避免浮点误差，保证答案可以表示为最简分数 $\frac{p}{q}$，你只需要输出一个 $x (0 \leq x < 998244353)$ 使得 $qx \equiv p \pmod {998244353}$。

## 样例

### 样例输入 #1
```
3
3 1 2
```
### 样例输出 #1
```
2 0 1
```
### 样例输入 #2
```
3
1 2 3
```
### 样例输出 #2
```
499122177 499122177 2
```
### 样例输入 #3
```
5
1 4 2 3 5
```
### 样例输出 #3
```
499122178 249561091 665496236 582309207 4
```
## 提示

#### 样例解释

在第一组样例中，第一个容器无论如何不可能被击倒，第二个容器在第一轮一定会被击倒，第三个容器第一轮一定不被击倒，第二轮一定被击倒。

第二组样例的真实答案为 $\frac{1}{2}$，$\frac{1}{2}$，$2$。

---

#### 数据范围

对于所有测试点，保证 $1 \leq n \leq 50$，$1 \leq a_i \leq n$，$a_i$ 两两不同。

$\text{Subtask 1 (2 pts)}$ $n \leq 2$。

$\text{Subtask 2 (23 pts)}$ $n \leq 6$。

$\text{Subtask 3 (31 pts)}$ $n \leq 18$。

$\text{Subtask 4 (19 pts)}​$ $a_i = i$。

$\text{Subtask 5 (25 pts)}$ 无特殊限制。

---

#### 提示

如果你不知道怎么对分数取模，可以参考[这里](https://www.luogu.com.cn/problem/P3811)。


---

---
title: "[Cnoi2020] 线形生物"
layout: "post"
diff: 提高+/省选-
pid: P6835
tag: ['动态规划 DP', '2020', 'O2优化', '期望', '洛谷月赛']
---
# [Cnoi2020] 线形生物
## 题目背景

> 为了能够在冥界过上这种愉快的生活而不是被判入地狱，人类们摒弃了自行结束生命的做法，拼尽全力地生活着。如此看来，人类似乎也显得有些积极与可爱了呢。  （射命丸 文） 

线形生物沿着一维的阶梯向着冥界单向地前行着。

照这样的话，它只需要一级一级地，走 $n$ 步就能够到达白玉楼。

但 Cirno 觉得这样太单调了，于是，一维的壁垒被打破，链状的道路生出了花椰菜状的枝桠。


## 题目描述

线形生物要从 $1$ 号台阶走到 $n+1$ 号台阶。

最开始，$1,2,3,\ldots,n$ 号台阶都有一条连向下一台阶的有向边 $i\rightarrow i+1$。

之后 Cirno 加入了 $m$ 条**返祖边** $u_i \rightarrow v_i (u_i \ge v_i)$，它们构成了一个**返祖图**。

线形生物每步会 **等概率地** 选取当前台阶的一条出边并走向对应的台阶。

当走到 $n+1$ 号台阶时，线形生物就会停止行走。

同时，Cirno 会统计线性生物总共走的步数，记作 $\delta$。

Cirno 想知道 $E(\delta)$（即 $\delta$ 的**数学期望**）对 $998244353$ 取模后的结果。
## 输入格式

第一行三个整数 $id$，$n$，$m$。

以下 $m$ 行，每行两个整数 $u_i$，$v_i$。

$id$ 表示 subtask 编号，其它字母含义同上文。
## 输出格式

一行，一个整数 $E(\delta)$，字母含义同上文。
## 样例

### 样例输入 #1
```
1 5 5
1 1
2 2
3 3
4 4
5 5
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
2 5 5
1 1
2 1
3 2
4 3
5 4
```
### 样例输出 #2
```
30
```
### 样例输入 #3
```
3 5 5
1 1
2 1
3 1
4 1
5 1
```
### 样例输出 #3
```
62
```
### 样例输入 #4
```
4 5 5
1 1
3 1
4 2
5 1
5 5
```
### 样例输出 #4
```
35
```
## 提示

## 后置数学知识
 - **可能用到的幂级数求和** : 若 $x>1$，则有 $\sum\limits_{i=1}^{\infty}\big(\frac{1}{x}\big)^i=\frac{1}{x}+\frac{1}{x^2}+\frac{1}{x^3}+\cdots=\frac{1}{x-1}$。
 - **数学期望** : 随机试验中每次可能结果的概率乘以其结果的总和，反映随机变量平均取值的大小。
 - **离散期望公式** : $E(x)=\sum\limits_{k=1}^{\infty}x_kp_k$。
 
## 数据范围与约定

对于 $100\%$ 的数据，保证：$id \in \{1,2,3,4,5\}$，$0 < n,m \le 10^6$，$1 \le v_i \le u_i \le n$。

#### 子任务「本题采用捆绑测试」

 - Subtask1（$10\%$）: 返祖图中所有点都有自环且所有边均为自环(未画出)，总图形如 :  
 ![](https://cdn.luogu.com.cn/upload/image_hosting/6fikv6ft.png)
   
 - Subtask2（$10\%$）: 返祖图中所有点均向且仅向自己的前驱连边，特别地，$1$ 号节点的前驱是 $1$ 号节点，总图形如 :  
   ![](https://cdn.luogu.com.cn/upload/image_hosting/6rc9dazb.png)
 
 - Subtask3（$10\%$）: 返祖图中所有点均向且仅向 $1$ 号节点连边，总图形如 :  
 ![](https://cdn.luogu.com.cn/upload/image_hosting/wup1ctvu.png)
 
 - Subtask4（$10\%$）: $n \le 100$，$m \le 1000$。
 
 - Subtask5（$60\%$）: 无特殊限制。
 
 ## 后记
 
  题目名称出自 th17 东方鬼形兽 6 Boss 埴安神袿姬 Hard / Lunatic 难度符卡 線形「リニアクリーチャー」。
  


---

---
title: "[USACO22FEB] Cow Camp G"
layout: "post"
diff: 提高+/省选-
pid: P8190
tag: ['动态规划 DP', 'USACO', '2022', 'Special Judge', '期望', '矩阵乘法']
---
# [USACO22FEB] Cow Camp G
## 题目描述

To qualify for cow camp, Bessie needs to earn a good score on the last problem of the USACOW Open contest. This problem has $T$ distinct test cases $(2≤T≤10^3)$ weighted equally, with the first test case being the sample case. Her final score will equal the number of test cases that her last submission passes.
Unfortunately, Bessie is way too tired to think about the problem, but since the answer to each test case is either "yes" or "no," she has a plan! Precisely, she decides to repeatedly submit the following nondeterministic solution:
```
if input == sample_input:
  print sample_output
else:
  print "yes" or "no" each with probability 1/2, independently for each test case
```
Note that for all test cases besides the sample, this program may produce a different output when resubmitted, so the number of test cases that it passes will vary.

Bessie knows that she cannot submit more than $K$ $(1≤K≤10^9)$ times in total because then she will certainly be disqualified. What is the maximum possible expected value of Bessie's final score, assuming that she follows the optimal strategy?
## 输入格式

The only line of input contains two space-separated integers $T$ and $K$.
## 输出格式

The answer as a decimal that differs by at most $10^{−6}$ absolute or relative error from the actual answer.
## 样例

### 样例输入 #1
```
2 3
```
### 样例输出 #1
```
1.875
```
### 样例输入 #2
```
4 2
```
### 样例输出 #2
```
2.8750000000000000000
```
## 提示

【样例解释 1】

In this example, Bessie should keep resubmitting until she has reached 3 submissions or she receives full credit. Bessie will receive full credit with probability $\frac 78$ and half credit with probability $\frac 18$, so the expected value of Bessie's final score under this strategy is $\frac 78\cdot 2+\frac 18\cdot 1=\frac {15}{8}=1.875$. As we see from this formula, the expected value of Bessie's score can be calculated by taking the sum over $x$ of $p(x)\cdot x$, where $p(x)$ is the probability of receiving a score of $x$.

【样例解释 2】

Here, Bessie should only submit twice if she passes fewer than 3 test cases on her first try.

【数据范围】

- Test cases 3-6 satisfy $T≤25$ and $K≤100$.
- Test cases 7-9 satisfy $K≤10^6$.
- Test cases 10-17 satisfy no additional constraints.
## 题目翻译

### 题目描述

为了获得参加奶牛训练营的资格，Bessie 需要在 USACOW 公开赛的最后一题中取得好成绩。这道题有 $T$ 个独立的测试用例（$2 \leq T \leq 10^3$），权重相同，其中第一个测试用例是样例。她的最终得分将等于她最后一次提交通过的测试用例数量。

不幸的是，Bessie 太累了，无法思考这个问题，但由于每个测试用例的答案要么是“yes”，要么是“no”，她想到了一个计划！具体来说，她决定反复提交以下非确定性解决方案：

```
if input == sample_input:
    print sample_output
else:
    print "yes" or "no" each with probability 1/2, independently for each test case
```

注意，对于除样例之外的所有测试用例，这个程序在重新提交时可能会产生不同的输出，因此它通过的测试用例数量会有所不同。

Bessie 知道她总共不能提交超过 $K$ 次（$1 \leq K \leq 10^9$），否则她肯定会被取消资格。假设 Bessie 遵循最优策略，她的最终得分的最大可能期望值是多少？

### 输入格式

输入只有一行，包含两个用空格分隔的整数 $T$ 和 $K$。

### 输出格式

输出一个十进制数，表示答案，与实际答案的绝对误差或相对误差不超过 $10^{-6}$。

### 样例解释 1

在这个例子中，Bessie 应该继续重新提交，直到她提交了 3 次或获得了满分。Bessie 获得满分的概率是 $\frac{7}{8}$，获得一半分数的概率是 $\frac{1}{8}$，因此在这种策略下，Bessie 的最终得分的期望值是 $\frac{7}{8} \cdot 2 + \frac{1}{8} \cdot 1 = \frac{15}{8} = 1.875$。从这个公式可以看出，Bessie 得分的期望值可以通过对所有可能的得分 $x$ 求和 $p(x) \cdot x$ 来计算，其中 $p(x)$ 是获得得分 $x$ 的概率。

### 样例解释 2

在这里，Bessie 应该只在第一次尝试通过少于 3 个测试用例时才提交第二次。

### 数据范围

- 测试用例 3-6 满足 $T \leq 25$ 且 $K \leq 100$。
- 测试用例 7-9 满足 $K \leq 10^6$。
- 测试用例 10-17 没有额外限制。


---

---
title: "[THUPC 2022 初赛] 骰子旅行"
layout: "post"
diff: 提高+/省选-
pid: P8208
tag: ['动态规划 DP', '2022', 'O2优化', '期望', 'THUPC']
---
# [THUPC 2022 初赛] 骰子旅行
## 题目描述

在乐队 f 开巡演之前，按照惯例是要先组织乐队成员进行骰子旅行放松身心的。一次骰子旅行包括 $N$ 个地点，这些地点分别标号为 $1, 2, \cdots, N$。乐队成员们事先约好在 $s_0$ 处集合；而到了骰子旅行当天，大家都来到了集合地点 $s_0$，骰子旅行就算正式开始了。

骰子旅行的一大乐趣就是由骰子决定旅行的下一个目的地。当然，这个骰子不一定非得是六面的。我们可以认为，如果当前乐队成员们位于地点 $i$，那么下一个目的地会等概率地从 $m_i$ 个互不相同的候选地点中产生，这些候选地点分别是 $l_{i, 1}, l_{i, 2}, \cdots, l_{i, m_i}$。我们记第 $t$ 次投掷的结果是 $s_t$，那么第 $(t+1)$ 次将会前往 $s_t$ 处掷骰子。第 1 次投掷在起点 $s_0$ 处进行；而由于乐队之后还需要为了巡演排练，事先约定无论前往了哪些地点，投掷完第 $T$ 次骰子，前往 $s_T$ 后骰子旅行都得结束。

当然，享受 $s_0, s_1, \cdots, s_T$ 这些景点也是骰子旅行的一大乐趣。无论是否之前来过，每次到一个地点 $s_t$，乐队成员们都会尽情地浏览美景，品尝美食。只是如果之前来过 $s_t$，负责掷骰子的键盘手 S 在掷这第 $(t+1)$ 次骰子之前一定会说：“上次来到 $s_t$ 仿佛还是上一次 $t'$，上一次在这里掷出了 $s_{t'+1}$，不知道这一次会掷出什么结果。”鼓手 Y 特别喜欢废话梗，所以每次 S 说这句话时，他都会把 $s_{t'+1}$ 记下来。特别地，如果 $s_T$ 是之前经过的地点，那么 S 会说：“上次来到 $s_t$ 仿佛还是上一次 $t'$，上一次在这里掷出了 $s_{t'+1}$，不过这一次就不投掷了，因为骰子旅行到这里就要告一段落了。”当然，Y 也会把这个 $s_{t'+1}$ 记下来。

作为这次骰子旅行的总结，Y 会把所有记录下来的 $s_{t'+1}$ 加起来，作为 S 的废话指数。

f 的下一次巡演马上就要开始了，于是 S 又盘算着带大家去参加骰子旅行。听说你是 f 的粉丝，S 找到了你，希望你能帮他算一下他这次骰子旅行的废话指数的期望值。
## 输入格式

输入的第一行包括三个正整数 $N, s_0, T$，分别表示可能涉及地点的个数，骰子旅行的起点和骰子旅行中投掷骰子的次数。

接下来 $N$ 行，第 $i\ (1\le i\le N)$ 行先输入一个正整数 $m_i$，表示地点 $i$ 的下一个目的地的候选地点数；接着输入 $m_i$ 个正整数，表示这 $m_i$ 个地点 $l_{i, 1}, l_{i, 2}, \cdots, l_{i, m_i}$。保证对于任意 $i$，$m_i$ 个输入的地点互不相同。
## 输出格式

输出一个数表示废话指数的期望。假设废话指数的期望化为最简分式后的形式为 $p/q$（即其中 $p, q$ 互质），请输出 $x$ 使得 $qx\equiv p \pmod{998,244,353}$ 且 $0\le x<998,244,353$。可以证明，在本题数据范围下，$x$ 存在且唯一。
## 样例

### 样例输入 #1
```
5 1 2
3 2 3 4
2 1 5
2 1 5
2 1 5
3 2 3 4
```
### 样例输出 #1
```
499122178
```
### 样例输入 #2
```
7 1 4
6 2 3 4 5 6 7
6 1 3 4 5 6 7
6 1 2 4 5 6 7
6 1 2 3 5 6 7
6 1 2 3 4 6 7
6 1 2 3 4 5 7
6 1 2 3 4 5 6
```
### 样例输出 #2
```
274979351
```
## 提示

【样例解释 1】

对答案有贡献的方案为：从点 $1$ 出发走到 $2, 3, 4$ 中的任意一个点并返回点 $1$。对于某个点 $i (i=2, 3, 4)$，走到点 $i$ 并返回点 $1$ 的概率为 $1/6$，而贡献为 $i$，故期望为 

$$\frac{1}{6} \times (2+3+4) = \frac{3}{2} .$$

由 $499122178 \times 2 = 998244356 \equiv 3 \pmod {998244353}$ 可知 $3/2$ 在模 $998,244,353$ 意义下为 $499,122,178$，所以正确输出为 $499,122,178$。

【样例解释 2】

转换前的答案为 $1625/432\approx 3.761574$，而 $432\times 274979351 = 118791079632 \equiv 1625 \pmod{998244353}$，所以模意义下的答案为 $274979351$。

【样例 3】

见附件。

【数据范围】

对于 $100\%$ 的数据，保证 $1\le N\le 100$，$1\le T\le 100$，$1\le s_0\le N$，$1\le m_i\le N$，$\sum_{i=1}^N m_i\le 5000$，$1\le l_{i, j}\le N$，且 $\forall 1\le i\le N, \forall 1\le j_1<j_2\le m_i, l_{i, j_1}\ne l_{i, j_2}$。


---

---
title: "[CoE R5] 罚球"
layout: "post"
diff: 提高+/省选-
pid: P8580
tag: ['动态规划 DP', '数学', '洛谷原创', 'O2优化', '期望', '高斯消元', '洛谷月赛']
---
# [CoE R5] 罚球
## 题目描述

有 $n$ 个人在玩罚球游戏，游戏规则如下：
- 每个人编号为 $1,2,\dots,n$，最开始由 $1$ 号罚球，接下来让下一个没有出局的人罚球。特殊地，$n$ 号的下一个是 $1$ 号。
- 如果罚球者没有碰到篮板，那么直接出局。
- 如果罚球者碰到篮板但没有进球，那么如果上一个人进球了，这个人就会出局，否则不会出局。
- 游戏结束的条件是最后只剩下一个人。

注意最开始的那个人碰到篮板但没有进球不出局。

这 $n$ 个人中，第 $i$ 个人碰不到篮板的概率为 $\dfrac{a_i}{1000}$，碰到篮板但没有进球的概率为 $\dfrac{b_i}{1000}$，求游戏结束时所有人总共罚球数量的期望值。
## 输入格式

第一行两个整数 $n,t$，为人数和子任务编号。  
接下来 $n$ 行，每行两个整数，为 $a_i,b_i$，保证 $0\le a_i+b_i\le1000$。
## 输出格式

输出一行，为所有人总共罚球数量的期望值，如果永远不会结束，那么输出 $-1$。否则，输出对 $10^6+33$ 取模的值。
## 样例

### 样例输入 #1
```
2 8
200 400
200 400
```
### 样例输出 #1
```
888921
```
### 样例输入 #2
```
7 8
321 637
321 637
321 637
321 637
321 637
321 637
321 637
```
### 样例输出 #2
```
818968
```
### 样例输入 #3
```
6 10
338 270
229 413
132 133
141 173
157 686
616 250
```
### 样例输出 #3
```
315860
```
### 样例输入 #4
```
8 10
338 270
229 413
132 133
141 173
157 686
616 250
0 0
0 0
```
### 样例输出 #4
```
-1
```
## 提示

**关于取模**

不会有理数取模的看[这里](https://www.luogu.com.cn/problem/P2613)。



------------
**样例说明**

输入 $\#1$：

所有人碰不到篮板的概率都是 $\dfrac{1}{5}$，碰到篮板但不进球的概率都是 $\dfrac{2}{5}$，罚球数量的期望值为 $\dfrac{25}{9}$。

计算如下（黑色表示出局，红色表示没进球但不出局，蓝色表示进球）：
$$\dfrac{1}{5}+\red{\dfrac{2}{5}}\times(\dfrac{1}{5}+\red{\dfrac{2}{5}}\times(...)+\blue{\dfrac{2}{5}}\times(...))+\blue{\dfrac{2}{5}}\times(\dfrac{3}{5}+\blue{\dfrac{2}{5}}\times(...))=\dfrac{25}{9}$$

输入 $\#2$：

所有人碰不到篮板的概率都是 $\dfrac{321}{1000}$，碰到篮板但不进球的概率都是 $\dfrac{637}{1000}$，罚球数量的期望值为 $\dfrac{1000000}{57959}$。

------------

**数据范围**

**本题采用捆绑测试**。

测试点性质：
| $t=$ | 性质 | 分数 |
| :----------: | :----------: | :----------: |
| $1$ | $n=1$ | $2$ |
| $2$ | $a_i=b_i=0$ | $2$ |
| $3$ | $a_i=1000$ | $4$ |
| $4$ | $b_i=1000$ | $4$ |
| $5$ | $a_i=0,b_1=0,\forall i>1,b_i=1000$ | $6$ |
| $6$ | $a_i=b_i=500$ | $6$ |
| $7$ | $a_i=0,b_i=500$ | $6$ |
| $8$ | $a_i,b_i$ 均为定值，且答案不为 $-1$ | $19$ |
| $9$ | $1 \le n \le 11$ | $26$ |
| $10$ | $1 \le n \le 15$ | $8$ |
| $11$ | 无特殊性质 | $17$ |

**对于** $100\%$ **的数据**，$1 \le n \le 18$，$0 \le a_i,b_i,a_i+b_i \le 1000$。

本题的 $\text{Subtask 10}$ 分为两部分计分，对应 $t \in \{10,11\}$。

保证不存在分母为 $10^6+33$ 的倍数的情况。


---

---
title: "[_-0 A] 考试"
layout: "post"
diff: 提高+/省选-
pid: P9475
tag: ['O2优化', '组合数学', '二项式定理', '概率论', '期望']
---
# [_-0 A] 考试
## 题目背景

小 $\mathfrak{g}$ 参加一场考试时，不小心把答题卡填反了。
## 题目描述

答题卡有 $n (1 \le n \le 10^9)$ 行，$m (1 \le m \le 10^9)$ 列，共 $nm$ 道题，**从左到右，从上到下，横向排列**。

每道题有 $c (4 \le c \le 10^9)$ 个选项。其中，前 $k(0 \le k \le nm)$ 道题为单选题，**有且仅有一个**正确选项；后 $nm - k$ 道题为多选题，正确选项个数**严格大于** $1$ 且**严格小于** $c$。

小 $\mathfrak{g}$ 正确地回答了所有题，但是她不小心把答题卡的方向看反了，从而她的答案排列方式为**从上到下，从左到右，纵向排列**。

题目的评分方式为：选项完全正确得 $1$ 分，多选或错选得 $0$ 分，漏选按比例给分。

形式化地说，若 $A$ 为某道题正确答案选项的集合，$B$ 为答题卡上选项的集合（均为 $\{1,2,3,\cdots,c\}$ 的子集），则该题得分为：

$$\begin{cases}\frac{\lvert B \rvert}{\lvert A \rvert}&\text{if\quad}
B\sube A\\0&\text{otherwise}\end{cases}$$

小 $\mathfrak{g}$ 忘记考试的正确答案是什么了，于是她去问小 $\mathfrak{f}$，如果考试的正确答案在合法范围内等概率随机，那么自己期望得分是多少。由于结果可能很大，她只需要知道结果对 $10^9+7$ 取模的值。

**题目保证 $c$ 和 $2^c-c-2$ 都不是 $10^9+7$ 的倍数。**


但是小 $\mathfrak{f}$ 也不会，所以他来求助万能的你。
## 输入格式

一行，四个用空格分隔的整数 $n,m,k,c$，分别表示答题卡的行数，列数，单选题的数量和每道题的选项个数。
## 输出格式

一行，一个整数，表示期望得分，对 $10^9+7$ 取模。
## 样例

### 样例输入 #1
```
2 3 3 4
```
### 样例输出 #1
```
760000008
```
### 样例输入 #2
```
314159265 358979323 84626433832795028 841971693
```
### 样例输出 #2
```
465094894
```
## 提示

**样例 $1$ 解释：**

得分的期望为 $\frac{67}{25}$，对 $10^9+7$ 取模为 $760000008$。

一种可能的考试的正确答案依次为：

$\texttt{C,D,B,AD,ABD,BC}$

那么答题卡上应该填写：

| $\texttt{C}$ | $\texttt{D}$ | $\texttt{B}$ |
| :----------: | :----------: | :----------: |
| $\texttt{AD}$ | $\texttt{ABD}$ | $\texttt{BC}$ |

实际填写：

| $\texttt{C}$ | $\texttt{B}$ | $\texttt{ABD}$ |
| :----------: | :----------: | :----------: |
| $\texttt{D}$ | $\texttt{AD}$ | $\texttt{BC}$ |

答案为 $\texttt{C}$，填写 $\texttt{C}$，得 $1$ 分。

答案为 $\texttt{D}$，填写 $\texttt{B}$，得 $0$ 分。

答案为 $\texttt{B}$，填写 $\texttt{ABD}$，得 $0$ 分。

答案为 $\texttt{AD}$，填写 $\texttt{D}$，得 $\frac{1}{2}$ 分。

答案为 $\texttt{ABD}$，填写 $\texttt{AD}$，得 $\frac{2}{3}$ 分。

答案为 $\texttt{BC}$，填写 $\texttt{BC}$，得 $1$ 分。

综上，这种情况下，考试得分为：

$1+0+0+\frac{1}{2}+\frac{2}{3}+1=
\frac{19}{6}$ 分。

**本题采用捆绑测试且使用子任务依赖。**

| 编号 | 分值 | $n,m\le$ | $c\le$ | 性质 | 依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $0$ | N/A| N/A | 样例 | 无 |
| $1$ | $5$ | $10^9$ | $10^9$ | A | 无 |
| $2$ | $5$ | $2$ | $4$ | 无 | 无 |
| $3$ | $20$ | $10^3$ | $10$ | 无 | $2$ |
| $4$ | $15$ | $10^9$ | $10$ | 无 | $2,3$ |
| $5$ | $15$ | $10^3$ | $10^3$ | 无 | $2,3$ |
| $6$ | $15$ | $10^3$ | $10^5$ | 无 | $2,3,5$ |
| $7$ | $10$ | $10^3$ | $10^9$ | B | 无 |
| $8$ | $10$ | $10^3$ | $10^9$ | 无 | $2,3,5,6,7$ |
| $9$ | $5$ | $10^9$ | $10^9$ | 无 | $0,1,2,3,4,5,6,7,8$ |

特殊性质 A：$n=1$ 或 $m=1$

特殊性质 B：$k=nm-2$


---

---
title: "「PFLOI R1」PFL 团主的 PFL 操作"
layout: "post"
diff: 提高+/省选-
pid: P9590
tag: ['动态规划 DP', '洛谷原创', 'O2优化', '矩阵加速', '期望']
---
# 「PFLOI R1」PFL 团主的 PFL 操作
## 题目背景

比赛结束后，智力、旸麦、花猫邀来碓瑘，四人从此结交为友。

--------------------

实际上，不光碓瑘，智力、旸麦、花猫都曾是 OI 界中最强的存在。一次又一次 AK 一场又一场 Trash Round 后，它们厌倦了，从此销声匿迹，退出江湖。

今天看到碓瑘才气不减当年，它们又念想起那些和 OI 作伴的时光……兴意，顿生心头。

于是它们找到了 PFLOI 团长珺珺，请求珺珺给它们再次辉煌的机会——出一场属于自己的比赛。

听完它们的事迹后，珺珺颇为感动，欣然同意。5 人就此相聚在 PFLOI。

但是旸麦进入 PFLOI 后~~乱出题~~太调皮了，珺珺可不乐意了，于是：

![](https://cdn.luogu.com.cn/upload/image_hosting/9m9343n9.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/znp6x2ta.png)
## 题目描述

有 $n$ 次操作，每次操作会等概率地进行以下事件中的一个：

1. 将 $a_i$ 加入团队，操作后 $a_i$ 为成员。
2. 将 $a_i$ 踢出团队。
3. 将 $a_i$ 设置为管理员。
4. 将 $a_i$ 设置为成员。

**注意：**

+ 开始时没有人在团队里。  
+ 如果 $a_i$ 不在团队中，则 2、3、4 操作无效果。  
+ 如果 $a_i$ 为成员，则 1、4 操作无效果。  
+ 如果 $a_i$ 是管理员，则 1、2、3 操作无效果。  

最后输出团队中管理员个数的期望，答案对 $998244353$ 取模。
## 输入格式

第一行一个整数 $\text{type}$。  
如果 $\text{type}$ 为 $1$，则采用**第一种输入方式**，否则采用**第二种输入方式**。

### 第一种输入方式：

第一行一个正整数 $n$。  
第二行共 $n$ 个整数表示数组 $a$。

### 第二种输入方式：

共一行四个整数分别是 $n,a_0,p,q$。    

**注意：第二种输入方式中，数组 $a$ 需要你计算得出，满足 $a_i=(a_{i-1}\times p+p)\bmod q+ 1$ $ (i \geq 1)$。**
## 输出格式

输出一个整数表示团队中管理员个数的期望，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
1
6
1 1 2 1 2 1

```
### 样例输出 #1
```
760381441
```
### 样例输入 #2
```
2
11 4 5 14
```
### 样例输出 #2
```
686292993
```
## 提示

**本题采用捆绑测试**。

| 子任务编号	 | $\text{type}=$ | $n$ | $a_i$ | 分值 |
| :---: | :---: | :---: | :---: | :---: |
| $1$ | $1$ | $n\le 100$ | $1\le a_i\le10$ | $25$ |
| $2$ | $1$ | $n\le 5\times 10^5$ | $1\le a_i\le 10^{18}$ | $35$ |

| 子任务编号	 | $\text{type}=$ | $n$ | $a_0,p,q$ | 分值 |
|:---------:|:------:|:---:|:-----:|:-----:|
| $3$ | $2$ | $n\le 10^6$ | $1\le a_0,p<q\le 20$ | $10$ |
| $4$ | $2$ | $n\le 10^{18}$ | $1\le a_0,p<q\le 3\times 10^5$ | $30$ |

对于所有数据，$1\le n\le 10^{18}$。


---

