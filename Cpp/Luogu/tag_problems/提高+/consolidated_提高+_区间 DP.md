---
title: "BZOJ4350 括号序列再战猪猪侠"
layout: "post"
diff: 提高+/省选-
pid: P10600
tag: ['O2优化', '区间 DP']
---
# BZOJ4350 括号序列再战猪猪侠
## 题目背景

题目来自原 BZOJ，我们承认题面及原数据的版权均属于原 BZOJ 或将题目授权给 BZOJ 使用的出题人。如果您是版权所有者且认为我们侵犯了您的权益，可联系我们。
## 题目描述

括号序列是一个仅由 `()` 构成的序列。以下的括号序列是合法的：
1. `()` 是一个合法序列。
2. 如果 `A` 是一个合法序列，则 `(A)`  也是一个合法序列。
3. 如果 `A` 和 `B` 都是合法序列，则 `AB` 也是一个合法序列。

定义 $match_i$ 表示从左往右数第 $i$ 个左括号所对应的是第几个右括号。

现在得到了一个长度为 $2n$ 的括号序列，提供 $m$ 个信息，第 $i$ 个信息形如 $a_i,b_i$，表示 $match_{a_i}<match_{b_i}$。

现问，若根据这些信息还原出合法括号序列的方案数一共有多少？答案对 $998244353$ 取模。
## 输入格式

第一行一个正整数 $T$，表示数据组数。

对于每组数据，第一行两个正整数 $n,m$。其中 $n$ 表示有几个左括号，$m$ 表示信息数。

接下来 $m$ 行，每行两个正整数 $a_i,b_i$。
## 输出格式

对于每组数据，输出一个数表示答案。
## 样例

### 样例输入 #1
```
5
1 0
5 0
3 2
1 2
2 3
3 2
2 1
2 3
3 3
1 2
2 3
3 1
```
### 样例输出 #1
```
1
42
1
2
0
```
## 提示

对于所有数据，保证 $1\leq T\leq 5$，$1\leq n\leq 300$，$1\leq a_i,b_i\leq n$。


---

---
title: "[Code+#6] 祖玛"
layout: "post"
diff: 提高+/省选-
pid: P11444
tag: ['动态规划 DP', '区间 DP', 'Code+']
---
# [Code+#6] 祖玛
## 题目背景

搬运自 [Code+ 第 6 次网络赛](https://gitlink.org.cn/thusaa/codeplus6/)。

------------


小粽还是一个小粽子的时候，特别喜欢玩一款叫作祖玛的游戏。现在，小粽长大了。为了纪念她的童年时光，她开发了一款新型祖玛游戏，并为你准备了一个问题。
## 题目描述

小粽的祖玛游戏的游戏规则可以抽象为如下模型：

初始时，有一段长度为 $n$ 的正整数序列 $a_1,a_2,\dots,a_n$。游戏过程中，小粽会对这个序列进行一系列规则相同的操作：从序列中选取连续且相同的一段数，设这段数的长度为 $X$，如果这些数的值都相等，那么小粽可以把这些数从序列中删除，并将序列从删除的位置接起来，例如，对于序列 `2 3 3 3 1`，可以删除中间的 `3 3 3`，得到 `2 1`。

不过，小粽觉得只是这样太简单了，于是她选择了两个数 $X_{min},X_{max}$，并且要求每次删除的那段数的长度 $X$ 要满足 $X_{min}\le X\le X_{max}$。

显然小粽能进行的操作次数是有限的，甚至她有可能不能把整个序列删除完。现在，小粽想要知道，她每次删除的数的长度的平方和是多少。即，设 $X_i$ 为第 $i$ 次删除的数的长度，最大化 $\sum X_i^2$。

出题固然很爽，但是小粽发现自己现在不会做了。请你帮小粽求出这个最大值吧！
## 输入格式

输入第一行为一个正整数 $n$，表示初始时序列的长度。

接下来一行包含 $n$ 个正整数，描述这个序列，第 $i$ 个数为 $a_i$。

输入的第三行为两个正整数 $X_{min},X_{max}$。

对于所有的输入数据都满足 $1\le n\le 100$，$1\le a_i\le n$，$1\le X_{min}\le X_{max}\le n$。
## 输出格式

输出一行一个整数，表示 $\sum X_i^2$ 的最大值。
## 样例

### 样例输入 #1
```
8
2 1 1 1 2 2 1 2
1 2
```
### 样例输出 #1
```
16
```
## 提示

### 样例解释

**【样例 1】**

最优策略为，先删除中间的两个 `2 2`，然后删除连续删除两个 `1 1`，最后删除剩下的 `2 2`。注意，由于 $x_{max}$ 的限制，无法删除 `1 1 1`。

**【样例 2】**

见题目目录下的 `2.in` 与 `2.ans`。

### 数据范围

对于所有的输入数据都满足 $1\le n\le 100$，$1\le a_i\le n$，$1\le X_{min}\le X_{max}\le n$。


---

---
title: "关路灯"
layout: "post"
diff: 提高+/省选-
pid: P1220
tag: ['动态规划 DP', '搜索', '区间 DP']
---
# 关路灯
## 题目描述

某一村庄在一条路线上安装了 $n$ 盏路灯，每盏灯的功率有大有小（即同一段时间内消耗的电量有多有少）。老张就住在这条路中间某一路灯旁，他有一项工作就是每天早上天亮时一盏一盏地关掉这些路灯。

为了给村里节省电费，老张记录下了每盏路灯的位置和功率，他每次关灯时也都是尽快地去关，但是老张不知道怎样去关灯才能够最节省电。他每天都是在天亮时首先关掉自己所处位置的路灯，然后可以向左也可以向右去关灯。开始他以为先算一下左边路灯的总功率再算一下右边路灯的总功率，然后选择先关掉功率大的一边，再回过头来关掉另一边的路灯，而事实并非如此，因为在关的过程中适当地调头有可能会更省一些。

现在已知老张走的速度为 $1m/s$，每个路灯的位置（是一个整数，即距路线起点的距离，单位：$m$）、功率（$W$），老张关灯所用的时间很短而可以忽略不计。

请你为老张编一程序来安排关灯的顺序，使从老张开始关灯时刻算起所有灯消耗电最少（灯关掉后便不再消耗电了）。
## 输入格式

第一行是两个数字 $n$（表示路灯的总数）和 $c$（老张所处位置的路灯号）；

接下来 $n$ 行，每行两个数据，表示第 $1$ 盏到第 $n$ 盏路灯的位置和功率。数据保证路灯位置单调递增。
## 输出格式

一个数据，即最少的功耗（单位：$J$，$1J=1W\times s$）。
## 样例

### 样例输入 #1
```
5 3
2 10
3 20
5 20
6 30
8 10
```
### 样例输出 #1
```
270  
```
## 提示

### 样例解释

此时关灯顺序为 `3 4 2 1 5`。

### 数据范围

$1\le n\le50$，$1\le c\le n$，$1\le W_i \le 100$。


---

---
title: "[蓝桥杯 2023 省 Java B] 合并石子"
layout: "post"
diff: 提高+/省选-
pid: P12330
tag: ['2023', '区间 DP', '蓝桥杯省赛']
---
# [蓝桥杯 2023 省 Java B] 合并石子
## 题目描述

在桌面从左至右横向摆放着 $N$ 堆石子。每一堆石子都有着相同的颜色，颜色可能是颜色 $0$，颜色 $1$ 或者颜色 $2$ 中的其中一种。现在要对石子进行合并，规定每次只能选择位置相邻并且颜色相同的两堆石子进行合并。合并后新堆的相对位置保持不变，新堆的石子数目为所选择的两堆石子数目之和，并且新堆石子的颜色也会发生循环式的变化。具体来说：两堆颜色 $0$ 的石子合并后的石子堆为颜色 $1$，两堆颜色 $1$ 的石子合并后的石子堆为颜色 $2$，两堆颜色 $2$ 的石子合并后的石子堆为颜色 $0$。本次合并的花费为所选择的两堆石子的数目之和。

给出 $N$ 堆石子以及他们的初始颜色，请问最少可以将它们合并为多少堆石子？如果有多种答案，选择其中合并总花费最小的一种，合并总花费指的是在所有的合并操作中产生的合并花费的总和。
## 输入格式

第一行一个正整数 $N$ 表示石子堆数。

第二行包含 $N$ 个用空格分隔的正整数，表示从左至右每一堆石子的数目。

第三行包含 $N$ 个值为 $0$ 或 $1$ 或 $2$ 的整数表示每堆石头的颜色。
## 输出格式

一行包含两个整数，用空格分隔。其中第一个整数表示合并后数目最少的石头堆数，第二个整数表示对应的最小花费。
## 样例

### 样例输入 #1
```
5
5 10 1 8 6
1 1 0 2 2
```
### 样例输出 #1
```
2 44
```
## 提示

### 样例说明

![](https://cdn.luogu.com.cn/upload/image_hosting/bifee2mb.png)

上图显示了两种不同的合并方式。其中节点中标明了每一堆的石子数目，在方括号中标注了当前堆石子的颜色属性。左图的这种合并方式最终剩下了两堆石子，所产生的合并总花费为 $15 + 14 + 15 = 44$；右图的这种合并方式最终也剩下了两堆石子，但产生的合并总花费为 $14 + 15 + 25 = 54$。综上所述，我们选择合并花费为 $44$ 的这种方式作为答案。

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$1 \leq N \leq 10$。
- 对于 $50\%$ 的评测用例，$1 \leq N \leq 50$。
- 对于 $100\%$ 的评测用例，$1 \leq N \leq 300$，$1 \leq$ 每堆石子的数目 $\leq 1000$。


---

---
title: "[NERC 2021] Job Lookup"
layout: "post"
diff: 提高+/省选-
pid: P12823
tag: ['2021', 'Special Judge', '区间 DP', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Job Lookup
## 题目描述

Julia's $n$ friends want to organize a startup in a new country they moved to. They assigned each other numbers from 1 to $n$ according to the jobs they have, from the most front-end tasks to the most back-end ones. They also estimated a matrix $c$, where $c_{ij} = c_{ji}$ is the average number of messages per month between people doing jobs $i$ and $j$.

Now they want to make a hierarchy tree. It will be a $\textbf{binary tree}$ with each node containing one member of the team. Some member will be selected as a leader of the team and will be contained in the root node. In order for the leader to be able to easily reach any subordinate, for each node $v$ of the tree, the following should apply: all members in its left subtree must have smaller numbers than $v$, and all members in its right subtree must 
have larger numbers than $v$.

After the hierarchy tree is settled, people doing jobs $i$ and $j$ will be communicating via the shortest path in the tree between their nodes. Let's denote the length of this path as $d_{ij}$. Thus, the cost of their communication is $c_{ij} \cdot d_{ij}$.

Your task is to find a hierarchy tree that minimizes the total cost of communication over all pairs: $\sum_{1 \le i < j \le n} c_{ij} \cdot d_{ij}$.
## 输入格式

The first line contains an integer $n$ ($1 \le n \le 200$) -- the number of team members organizing a startup.

The next $n$ lines contain $n$ integers each, $j$-th number in $i$-th line is $c_{ij}$ ---
the estimated number of messages per month between team members $i$ and $j$ ($0 \le c_{ij} \le 10^9; c_{ij} = c_{ji}; c_{ii} = 0$).
## 输出格式

Output a description of a hierarchy tree that minimizes the total cost of communication. To do so, for each team member from 1 to $n$ output the number of the member in its parent node, or 0 for the leader. If there are many optimal trees, output a description of any one of them.

## 样例

### 样例输入 #1
```
4
0 566 1 0
566 0 239 30
1 239 0 1
0 30 1 0
```
### 样例输出 #1
```
2 4 2 0
```
## 提示

The minimal possible total cost is $566 \cdot 1+239 \cdot 1+30 \cdot 1+1 \cdot 2+1 \cdot 2=839$:

![](https://cdn.luogu.com.cn/upload/image_hosting/isxizhg5.png)


---

---
title: "[SDOI2008] Sue 的小球"
layout: "post"
diff: 提高+/省选-
pid: P2466
tag: ['动态规划 DP', '2008', '各省省选', '山东', '区间 DP']
---
# [SDOI2008] Sue 的小球
## 题目描述

Sue 和 Sandy 最近迷上了一个电脑游戏，这个游戏的故事发在美丽神秘并且充满刺激的大海上，Sue 有一支轻便小巧的小船。然而，Sue 的目标并不是当一个海盗，而是要收集空中漂浮的彩蛋，Sue 有一个秘密武器，只要她将小船划到一个彩蛋的正下方，然后使用秘密武器便可以在瞬间收集到这个彩蛋。然而，彩蛋有一个魅力值，这个魅力值会随着彩蛋在空中降落的时间而降低，Sue 要想得到更多的分数，必须尽量在魅力值高的时候收集这个彩蛋，而如果一个彩蛋掉入海中，它的魅力值将会变成一个负数，但这并不影响 Sue 的兴趣，因为每一个彩蛋都是不同的，Sue 希望收集到所有的彩蛋。

然而 Sandy 就没有 Sue 那么浪漫了，Sandy 希望得到尽可能多的分数，为了解决这个问题，他先将这个游戏抽象成了如下模型：

将大海近似的看做 $x$ 轴，以 Sue 所在的初始位置作为坐标原点建立一个竖直的平面直角坐标系。

一开始空中有 $N$ 个彩蛋，对于第 $i$ 个彩蛋，他的初始位置用整数坐标 $(x_{i}, y_{i})$ 表示，游戏开始后，它匀速沿 $y$ 轴负方向下落,速度为 $v_{i}$ 单位距离/单位时间。Sue 的初始位置为 $(x_{0}, 0)$，Sue 可以沿 $x$ 轴的正方向或负方向移动，Sue 的移动速度是 $1$ 单位距离/单位时间，使用秘密武器得到一个彩蛋是瞬间的，得分为当前彩蛋的 $y$ 坐标的千分之一。

现在，Sue 和 Sandy 请你来帮忙，为了满足 Sue 和 Sandy 各自的目标，你决定在收集到所有彩蛋的基础上，得到的分数最高。
## 输入格式

第一行为两个整数 $N$, $x_{0}$ 用一个空格分隔，表示彩蛋个数与 Sue 的初始位置。

第二行为 $N$ 个整数 $x_{i}$，每两个数用一个空格分隔，第 $i$ 个数表示第 $i$ 个彩蛋的初始横坐标。

第三行为 $N$ 个整数 $y_{i}$，每两个数用一个空格分隔，第 $i$ 个数表示第 $i$ 个彩蛋的初始纵坐标。

第四行为 $N$ 个整数 $v_{i}$，每两个数用一个空格分隔，第 $i$ 个数表示第 $i$ 个彩蛋匀速沿 $y$ 轴负方向下落的的速度。

## 输出格式

一个实数，保留三位小数，为收集所有彩蛋的基础上，可以得到最高的分数。

## 样例

### 样例输入 #1
```
3 0
-4 -2 2
22 30 26
1 9 8

```
### 样例输出 #1
```
0.000
```
## 提示

对于 $30\%$ 的数据， $N\leq 20$。

对于 $60\%$ 的数据， $N\leq 100$。

对于 $100\%$ 的数据，$-10^4 \leq x_{i},y_{i},v_{i} \leq 10^4$，$N \leq 1000$


---

---
title: "[USACO16OPEN] 262144 P"
layout: "post"
diff: 提高+/省选-
pid: P3147
tag: ['动态规划 DP', '贪心', '2016', 'USACO', '区间 DP']
---
# [USACO16OPEN] 262144 P
## 题目描述

Bessie likes downloading games to play on her cell phone, even though she  doesfind the small touch screen rather cumbersome to use with her large hooves.


She is particularly intrigued by the current game she is playing.The game starts with a sequence of $N$ positive integers ($2 \leq N\leq 262,144$), each in the range $1 \ldots 40$.  In one move, Bessiecan take two adjacent numbers with equal values and replace them asingle number of value one greater (e.g., she might replace twoadjacent 7s with an 8). The goal is to maximize the value of thelargest number present in the sequence at the end of the game.  Pleasehelp Bessie score as highly as possible!
## 输入格式

The first line of input contains $N$, and the next $N$ lines give the sequence

of $N$ numbers at the start of the game.

## 输出格式

Please output the largest integer Bessie can generate.

## 样例

### 样例输入 #1
```
4
1
1
1
2
```
### 样例输出 #1
```
3
```
## 提示

In this example shown here, Bessie first merges the second and third 1s to obtain the sequence 1 2 2, and then she merges the 2s into a 3. Note that it is not optimal to join the first two 1s.
## 题目翻译

### 题目描述

贝西喜欢在手机上下载游戏来玩，尽管她确实觉得对于自己巨大的蹄子来说，小小的触摸屏用起来相当笨拙。

她对当前正在玩的这个游戏特别感兴趣。游戏开始时给定一个包含 $N$ 个正整数的序列（$2 \leq N \leq 262,144$），每个数的范围在 $1 \ldots 40$ 之间。在一次操作中，贝西可以选择两个相邻且相等的数，将它们替换为一个比原数大 1 的数（例如，她可以将两个相邻的 7 替换为一个 8）。游戏的目标是最大化最终序列中的最大数值。请帮助贝西获得尽可能高的分数！

### 输入格式

第一行输入包含 $N$，接下来的 $N$ 行给出游戏开始时序列的 $N$ 个数字。

### 输出格式

请输出贝西能生成的最大整数。

### 说明/提示

在示例中，贝西首先合并第二个和第三个 1，得到序列 1 2 2，然后将两个 2 合并为 3。注意，合并前两个 1 并不是最优策略。


---

---
title: "[CQOI2007] 涂色"
layout: "post"
diff: 提高+/省选-
pid: P4170
tag: ['字符串', '2007', '重庆', '各省省选', '枚举', '区间 DP']
---
# [CQOI2007] 涂色
## 题目描述

假设你有一条长度为 $5$ 的木板，初始时没有涂过任何颜色。你希望把它的 $5$ 个单位长度分别涂上红、绿、蓝、绿、红色，用一个长度为 $5$ 的字符串表示这个目标：$\texttt{RGBGR}$。

每次你可以把一段连续的木板涂成一个给定的颜色，后涂的颜色覆盖先涂的颜色。例如第一次把木板涂成 $\texttt{RRRRR}$，第二次涂成 $\texttt{RGGGR}$，第三次涂成 $\texttt{RGBGR}$，达到目标。

用尽量少的涂色次数达到目标。

## 输入格式

输入仅一行，包含一个长度为 $n$ 的字符串，即涂色目标。字符串中的每个字符都是一个大写字母，不同的字母代表不同颜色，相同的字母代表相同颜色。

## 输出格式

仅一行，包含一个数，即最少的涂色次数。

## 样例

### 样例输入 #1
```
AAAAA
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
RGBGR
```
### 样例输出 #2
```
3
```
## 提示

$40\%$ 的数据满足 $1\le n\le 10$。

$100\%$ 的数据满足 $1\le n\le 50$。




---

---
title: "[SCOI2003] 字符串折叠"
layout: "post"
diff: 提高+/省选-
pid: P4302
tag: ['字符串', '动态规划 DP', '搜索', '2003', '四川', '各省省选', '枚举', '区间 DP']
---
# [SCOI2003] 字符串折叠
## 题目描述

折叠的定义如下：

1. 一个字符串可以看成它自身的折叠。记作 ```S = S```

2. ```X(S)``` 是 $X$ 个 ```S``` 连接在一起的串的折叠。记作 ```X(S) = SSSS…S```。

3. 如果 ```A = A’```, ```B = B’```，则 ```AB = A’B’ ```。例如：因为 ```3(A) = AAA```, ```2(B) = BB```，所以 ```3(A)C2(B) = AAACBB```，而 ```2(3(A)C)2(B) = AAACAAACBB```

给一个字符串，求它的最短折叠。

例如 ```AAAAAAAAAABABABCCD``` 的最短折叠为：```9(A)3(AB)CCD```。
## 输入格式

仅一行，即字符串 `S`，长度保证不超过 $100$。
## 输出格式

仅一行，即最短的折叠长度。
## 样例

### 样例输入 #1
```
NEERCYESYESYESNEERCYESYESYES
```
### 样例输出 #1
```
14
```
## 提示

一个最短的折叠为：`2(NEERC3(YES))`


---

---
title: "[CERC2014] Outer space invaders"
layout: "post"
diff: 提高+/省选-
pid: P4766
tag: ['动态规划 DP', '2014', '离散化', 'O2优化', '区间 DP']
---
# [CERC2014] Outer space invaders
## 题目描述

The aliens from outer space have (finally!) invaded Earth. Defend yourself, or be disintegrated!

Or assimilated. Or eaten. We are not yet sure.

The aliens follow a known attack pattern. There are $n$ attackers, the $i-th$ one appears at time $a_i$, at distance $d_i$ from you. He must be destroyed no later than at time $b_i$, or else he will fire his weapon, which will definitely end the fight.

Your weapon is an area-blaster, which can be set to any given power. If fired with power $R$,it momentarily destroys all aliens at distance $R$ or smaller. It also consumes $R$ fuel cells.

Determine the minimal cost (measured in fuel cells) of destroying all the aliens, without being killed.
## 输入格式

The first line of input contains the number of test cases $T$. The descriptions of the test cases follow:

Each test case starts with a line containing the number of aliens $n(1 \le n \le 300)$. Of the next $n$ lines, the $i-th$ one contains three integers $a_i, b_i, d_i, (1 \le a_i < b_i \le 10 000, 1 \le d_i \le 10 000)$.

The $i-th$ alien appears at time $a_i$, is idle until $b_i$, and his distance from you is $d_i$.

## 输出格式

For each test case, output one line containing the minimum number of cells needed to destroy all the aliens.

## 样例

### 样例输入 #1
```
1
3
1 4 4
4 7 5
3 4 7

```
### 样例输出 #1
```
7
```
## 题目翻译

### 题目描述
来自外太空的外星人（最终）入侵了地球。保卫自己，或者解体，被他们同化，或者成为食物。迄今为止，我们无法确定。

外星人遵循已知的攻击模式。有 $N$ 个外星人进攻，第 $i$ 个进攻的外星人会在时间 $a_i$ 出现，距离你的距离为 $d_i$，它必须在时间 $b_i$ 前被消灭，否则被消灭的会是你。

你的武器是一个区域冲击波器，可以设置任何给定的功率。如果被设置了功率 $R$，它会瞬间摧毁与你的距离在 $R$ 以内的所有外星人（可以等于），同时它也会消耗 $R$ 单位的燃料电池。

求摧毁所有外星人的最低成本（消耗多少燃料电池），同时保证自己的生命安全。

### 输入格式

第一行输入一个数 $T$,表示有 $T$ 组数据。

每组数据的第一行为外星人的数量 $n$（$1\leq n\leq 300$）。

接下来 $n$ 行，每行有三个数 $a_i,b_i,d_i$，表示这个外星人在时间 $a_i$ 出现，距离你 $d_i$，在 $b_i$ 前时刻死亡。

### 输出格式

共 $T$ 行，每行输出摧毁所有外星人的最低成本。


---

---
title: "[CCC 2016] 合并饭团"
layout: "post"
diff: 提高+/省选-
pid: P4805
tag: ['动态规划 DP', '2016', 'CCC（加拿大）', '区间 DP', '双指针 two-pointer']
---
# [CCC 2016] 合并饭团
## 题目描述

**译自 [CCC2016](https://cemc.math.uwaterloo.ca/contests/computing/2016/index.html) Senior T4「[Combining Riceballs](https://cemc.math.uwaterloo.ca/contests/computing/2016/stage%201/seniorEn.pdf)」**

Alphonse 有 $N$ 个美味的饭团，它们大小不一，摆放成一行。他想把最大的饭团让给自己的基友。他可以执行以下操作：

 - 如果两个**相邻的**饭团大小相同，Alphonse 可以把它们合并成一个新的饭团。新饭团的大小是两个原饭团大小之和。它将占据两个原饭团先前占据的位置。

 - 如果两个饭团大小相同，且它们之间只有一个饭团，Alphonse 也可以把它们合并成一个新的饭团。（中间的饭团大小没有规定。）新饭团的大小是三个原饭团大小之和，并占据三个原饭团先前的位置。

Alphonse 可以按照他的意愿执行任意次操作。

在执行 0 或更多次操作后，确定他应该把哪个饭团让给基友。
## 输入格式

第一行，一个整数 $N(1 \le N \le 400)$。

第二行，$N$ 个以空格分隔的整数，表示每个饭团的大小，按照从左到右的顺序给出。每个整数的上界为 $1\ 000\ 000$。
## 输出格式

输出 Alphonse 可以得到的最大的饭团大小。
## 样例

### 样例输入 #1
```
7
47 12 12 3 9 9 3
```
### 样例输出 #1
```
48
```
### 样例输入 #2
```
4
1 2 3 1
```
### 样例输出 #2
```
3
```
## 提示

#### 样例解释 1
有一种可能的合并方案为：合并大小同为 $12$ 的两个饭团，得到一个大小为 $24$ 的饭团。然后合并大小同为 $9$ 的两个饭团，得到一个大小为 $18$。接着合并大小为 $3,18$ 和 $3$ 的三个饭团，得到一个大小为 $24$ 的饭团。最后合并大小同为 $24$ 的两个饭团，得到一个大小为 $48$ 的饭团。

#### 样例解释 2
我们无法进行操作，所以答案为 $3$。

对于 $\frac1{15}$ 的数据，$N = 4$。

对于另外 $\frac2{15}$ 的数据，$N \le 10$。

对于另外 $\frac5{15}$ 的数据，$N \le 50$。


---

---
title: "[JLOI2010] 世界杯租房"
layout: "post"
diff: 提高+/省选-
pid: P5486
tag: ['动态规划 DP', '2010', '各省省选', '吉林', '区间 DP']
---
# [JLOI2010] 世界杯租房
## 题目描述

南非世界杯组委会指定了在此期间可提供的一些旅馆供球迷租赁，名为阿凡达的即是其中一所。因为阿凡达旅馆房子的数目不超过$26$，所以它们可以用$26$个大写字母表示。  
有一天，刘经理的电话响了，他接到了一个租赁房屋的请求，要求从$6$月$12$日晚起租到$6$月$19$日中午。于是他察看了预定表，但是并没有发现一间房屋能够直接满足要求。比如房主可能因为一些私人原因需要留在自己的房子中，所以这个游客不得不在其中的一间先住上几天再搬到另一间住上几天。他详细检查了预定表后，对旅客说：“我将你先在$B$安置$3$天，再将你安排到$F$去度过剩余的旅途。”  
你的目标是使得游客从一间房屋搬到另一间房屋的次数最少。  
注意在旅馆的计费中，总是将某一天的晚上到第二天的中午视作一天。  
## 输入格式

输入文件包括多组数据。每组数据输入文件第一行包括两个整数$M$和$N$。$M$表示日程表上的天数，$N$表示公寓的数目。天数不超过$100$天，从1开始计数，公寓不超过$26$个，从$A$开始计数。  
接下来$M$行，每行包括$N$个字母，表示从第i天晚到次日中午，该公寓是否已经被出租，$X$代表被出租，$O$代表未被出租。  
最后一行包括两个整数$s,t$，代表旅客从第$s$天晚入住到第$(t+1)$天中午结束旅行。$1\leq s<t\leq M+1$。  
$M=N=0$标志着文件的结束。  
## 输出格式

对于每一组数据，首先打印测试数据的编号，冒号和一个空行。接下来输出换房次数最少的方案，每一行使用如下格式：
$<unit>: <start date>-<end date>$
其中$<unit>$为房屋编号，$<start data>$和$<end data>$分别为该旅客入住和离开该房屋时间。
注意，如果存在多种方案满足换房次数最少，输出其中字典序最小的方案。  
如不存在这样的方案，输出一行”$Not\ available$”。  
每两组输出之间以一个空行隔开。输出文件的末尾不要加空行。  
## 样例

### 样例输入 #1
```
10 7
XXXXXXX
XOXXXXO
XOXXXXO
XOXXXOX
OXXOXOX
XOXOXOX
OXXOXOX
OXXXXOX
XXXXXXX
XXXXXXX
2 9
0 0
```
### 样例输出 #1
```
Case 1:

B: 2-5
F: 5-9
```


---

---
title: "[USACO19DEC] Greedy Pie Eaters P"
layout: "post"
diff: 提高+/省选-
pid: P5851
tag: ['动态规划 DP', '2019', 'USACO', '区间 DP']
---
# [USACO19DEC] Greedy Pie Eaters P
## 题目背景

Farmer John has $M$ cows, conveniently labeled $1 \ldots M$, who enjoy the occasional change of pace
from eating grass.  As a treat for the cows, Farmer John has baked $N$ pies ($1 \leq N \leq 300$), labeled
$1 \ldots N$.  Cow $i$ enjoys pies with labels in the range $[l_i, r_i]$ (from $l_i$ to $r_i$ inclusive),
and no two cows enjoy the exact same range of pies.  Cow $i$ also has a weight, $w_i$, which 
is an integer in the range $1 \ldots 10^6$.

Farmer John may choose a sequence of cows $c_1,c_2,\ldots, c_K,$ after which the
selected cows will take turns eating in that order. Unfortunately, the cows 
don't know how to share! When it is cow $c_i$'s turn to eat, she will consume
all of the  pies that she enjoys --- that is, all remaining pies in the interval
$[l_{c_i},r_{c_i}]$.  Farmer John would like to avoid the awkward situation
occurring when it is a cows turn to eat but all of the pies she enjoys have already been
consumed. Therefore, he wants you to compute the largest possible total weight
($w_{c_1}+w_{c_2}+\ldots+w_{c_K}$) of a sequence $c_1,c_2,\ldots, c_K$ for which each cow in the
sequence eats at least one pie.
## 题目描述

Farmer John 有 $M$ 头奶牛，为了方便，编号为 $1,\dots,M$。这些奶牛平时都吃青草，但是喜欢偶尔换换口味。Farmer John 一天烤了 $N$ 个派请奶牛吃，这 $N$ 个派编号为 $1,\dots,N$。第 $i$ 头奶牛喜欢吃编号在 $\left[ l_i,r_i \right]$ 中的派（包括两端），并且没有两头奶牛喜欢吃相同范围的派。第 $i$ 头奶牛有一个体重 $w_i$，这是一个在 $\left[ 1,10^6 \right]$ 中的正整数。

Farmer John 可以选择一个奶牛序列 $c_1,c_2,\dots,c_K$，并让这些奶牛按这个顺序轮流吃派。不幸的是，这些奶牛不知道分享！当奶牛  吃派时，她会把她喜欢吃的派都吃掉——也就是说，她会吃掉编号在 $[l_{c_i},r_{c_i}]$ 中所有剩余的派。Farmer John 想要避免当轮到一头奶牛吃派时，她所有喜欢的派在之前都被吃掉了这样尴尬的情况。因此，他想让你计算，要使奶牛按 $c_1,c_2,\dots,c_K$ 的顺序吃派，轮到这头奶牛时她喜欢的派至少剩余一个的情况下，这些奶牛的最大可能体重（$w_{c_1}+w_{c_2}+\ldots+w_{c_K}$）是多少。
## 输入格式

第一行包含两个正整数 $N,M$；

接下来 $M$ 行，每行三个正整数 $w_i,l_i,r_i$。
## 输出格式

输出对于一个合法的序列，最大可能的体重值。
## 样例

### 样例输入 #1
```
2 2
100 1 2
100 1 1

```
### 样例输出 #1
```
200

```
## 提示

#### 样例解释
在这个样例中，如果奶牛 $1$ 先吃，那么奶牛 $2$ 就吃不到派了。然而，先让奶牛 $2$ 吃，然后奶牛 $1$ 只吃编号为 $2$ 的派，仍可以满足条件。

对于全部数据，$1 \le N \le 300,1 \le M \le \dfrac{N(N-1)}{2},1 \le l_i,r_i \le N,1 \le w_i \le 10^6$。
#### 数据范围
对于测试点 $2-5$，满足 $N \le 50,M \le 20$；

对于测试点 $6-9$，满足 $N \le 50$。

USACO 2019 December 铂金组T1


---

---
title: "[USACO20JAN] Farmer John Solves 3SUM G"
layout: "post"
diff: 提高+/省选-
pid: P6006
tag: ['2020', 'USACO', '区间 DP', '前缀和']
---
# [USACO20JAN] Farmer John Solves 3SUM G
## 题目描述

Farmer John 相信他在算法设计上实现了一个重大突破：他声称他发现了一个 3SUM 问题的近似线性时间算法，这是一个有名的算法问题，尚未发现比运行速度比平方时间明显更优的解法。3SUM 问题的一个形式是：给定一个整数数组 $s_1,\ldots,s_m$，计算不同索引组成的无序不重三元对 $i,j,k$ 的数量，使得 $s_i+s_j+s_k=0$（$i, j, k$ 互不相同）。

为了测试 Farmer John 的断言，Bessie 提供了一个 $N$ 个整数组成的数组 $A$（$1 \leq N \leq 5000$）。Bessie 还会进行 $Q$ 次询问（$1 \leq Q \leq 10^5$），每个询问由两个索引 $1 \leq a_i \leq b_i \leq N$ 组成。对于每个询问，Farmer John 必须在子数组 $A[a_i \ldots b_i]$ 上求解 3SUM 问题。

不幸的是，Farmer John 刚刚发现了他的算法中的一个错误。他很自信他能修复这个算法，但同时，他请你帮他先通过 Bessie 的测试！
## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $Q$。

第二行包含空格分隔的数组 $A$ 的元素 $A_1,\ldots ,A_N$。

以下 $Q$ 行每行包含两个空格分隔的整数 $a_i$ 和 $b_i$，表示一个询问。

保证对于每个数组元素 $A_i$ 有 $-10^6 \leq A_i \leq 10^6$。
## 输出格式

输出包含 $Q$ 行，第 $i$ 行包含一个整数，为第 $i$ 个询问的结果。**注意你需要使用 64 位整数型来避免溢出。**
## 样例

### 样例输入 #1
```
7 3
2 0 -1 1 -2 3 3
1 5
2 4
1 7
```
### 样例输出 #1
```
2
1
4
```
## 提示

### 样例解释

对于第一个询问，所有的三元对为 $(A_1,A_2,A_5)$ 和 $(A_2,A_3,A_4)$。

### 子任务

- 测试点 $2 \sim 4$ 满足 $N \leq 500$。
- 测试点 $5 \sim 7$ 满足 $N \leq 2000$。
- 测试点 $8 \sim 15$ 没有额外限制。


---

---
title: "[POI 1997] Genotype"
layout: "post"
diff: 提高+/省选-
pid: P6701
tag: ['1997', 'POI（波兰）', '区间 DP']
---
# [POI 1997] Genotype
## 题目背景

Genotype 是一个独特的基因串。
## 题目描述

我们可以用大写英文字母 $A-Z$ 来描述 Genotype，每个字母就代表一个基因。

规定一种「分裂」规则，由三个大写字母 $A_1A_2A_3$ 组成，代表 $A_1$ 可以「分裂」为 $A_2A_3$。

现在给定 $n$ 个「分裂」规则和 $k$ 个 Genotype，判断这些 Genotype 是否能从一个特定的 **只包含大写字母 $S$ 的** 串通过「分裂」规则得到，如果可以的话输出特定的串的长度的最小值，如果不可以的话输出 `NIE`。
## 输入格式

第一行一个整数 $n$ 代表「分裂」规则数。     
接下来 $n$ 行每行三个大写字母 $A_1,A_2,A_3$ 代表一个「分裂」规则。         
接下来一行一个整数 $k$ 代表给定的 Genotype 数。     
接下来 $k$ 行每行若干个大写字母表示一个 Genotype。
## 输出格式

$k$ 行：

- 如果没有特定的串通过「分裂」规则得到这个 Genotype，输出 `NIE`。
- 如果有特定的串通过「分裂」规则得到这个 Genotype，输出这个特定的串的最小长度。
## 样例

### 样例输入 #1
```
6
SAB
SBC
SAA
ACA
BCC
CBC
3
ABBCAAABCA
CCC
BA
```
### 样例输出 #1
```
3
1
NIE
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le n,k \le 2000$，Genotype 的长度最大为 $100$。


---

---
title: "[JOI 2020 Final] スタンプラリー 3"
layout: "post"
diff: 提高+/省选-
pid: P6879
tag: ['动态规划 DP', '2020', '区间 DP', 'JOI（日本）']
---
# [JOI 2020 Final] スタンプラリー 3
## 题目描述

给定一个周长为 $L$ 的圆，从一个点出发，有 $N$ 个黑白熊雕像，编号为 $1$ 到 $N$，第 $i$ 个雕像在顺时针 $X_i$ 米处，如果你没有在 $T_i$ 秒内收集到这个黑白熊雕像，那么这个雕像就会发出“唔噗噗噗”的声音然后爆炸。

现在 JOI 君在这个点，他每一秒可以移动一米，并且他可以顺时针或者逆时针的移动。

JOI 君想问，他最多能收集到多少个黑白熊雕像？
## 输入格式

第一行两个整数 $N,L$ 代表雕像数和圆的周长。      
第二行 $N$ 个整数 $X_i$ 代表每个雕像在顺时针多少米处。       
第三行 $N$ 个整数 $T_i$ 代表每个雕像需要在多少秒内拿到。
## 输出格式

一行一个整数代表答案。
## 样例

### 样例输入 #1
```
6 25
3 4 7 17 21 23
11 7 17 10 8 10
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5 20
4 5 8 13 17
18 23 15 7 10

```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
4 19
3 7 12 14
2 0 5 4

```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
10 87
9 23 33 38 42 44 45 62 67 78
15 91 7 27 31 53 12 91 89 46

```
### 样例输出 #4
```
5
```
## 提示

#### 样例 1 解释

JOI 君可以按照如下策略拿到 $4$ 个黑白熊雕像：

|方向|路程|总时间|第几个雕像|能否拿到|
|:-:|:-:|:-:|:-:|:-:|
|逆时针|$2$ 米|$2$ 秒|$6$|$\sqrt{}$|
|逆时针|$2$ 米|$4$ 秒|$5$|$\sqrt{}$|
|顺时针|$7$ 米|$11$ 秒|$1$|$\sqrt{}$|
|顺时针|$1$ 米|$12$ 秒|$2$|$\times$|
|顺时针|$3$ 米|$15$ 秒|$3$|$\sqrt{}$|

#### 样例 2 解释

JOI 君可以直接一直逆时针走。

#### 样例 3 解释

JOI 君无法得到任何一个雕像。

#### 数据规模与约定

**本题采用捆绑测试。**
- Subtask 1（5 pts）：$N \le 12$，$L \le 200$，$X_i \le 200$。
- Subtask 2（10 pts）：$N \le 15$。
- Subtask 3（10 pts）：$L \le 200$，$T_i \le 200$。
- Subtaks 4（75 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $1 \le N \le 200$。
- $2 \le L \le 10^9$。
- $1 \le X_i<L$。
- $X_i < X_{i+1}$。
- $0 \le T_i \le 10^9$。

#### 说明

翻译自 [第19回日本情報オリンピック　本選](https://www.ioi-jp.org/joi/2019/2020-ho/index.html) [C スタンプラリー 3](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t3.pdf)。


---

---
title: "[CSP-S 2021] 括号序列"
layout: "post"
diff: 提高+/省选-
pid: P7914
tag: ['动态规划 DP', '2021', 'O2优化', '区间 DP', 'CSP-S 提高级']
---
# [CSP-S 2021] 括号序列
## 题目描述

小 w 在赛场上遇到了这样一个题：一个长度为 $n$ 且符合规范的括号序列，其有些位置已经确定了，有些位置尚未确定，求这样的括号序列一共有多少个。

身经百战的小 w 当然一眼就秒了这题，不仅如此，他还觉得一场正式比赛出这么简单的模板题也太小儿科了，于是他把这题进行了加强之后顺手扔给了小 c。

具体而言，小 w 定义“超级括号序列”是由字符 `(`、`)`、`*` 组成的字符串，并且对于某个给定的常数 $k$，给出了“符合规范的超级括号序列”的定义如下：

1. `()`、`(S)` 均是符合规范的超级括号序列，其中 `S` 表示任意一个仅由**不超过** $\bm{k}$ **个**字符 `*` 组成的非空字符串（以下两条规则中的 `S` 均为此含义）；
2. 如果字符串 `A` 和 `B` 均为符合规范的超级括号序列，那么字符串 `AB`、`ASB` 均为符合规范的超级括号序列，其中 `AB` 表示把字符串 `A` 和字符串 `B` 拼接在一起形成的字符串；
3. 如果字符串 `A` 为符合规范的超级括号序列，那么字符串 `(A)`、`(SA)`、`(AS)` 均为符合规范的超级括号序列。
4. 所有符合规范的超级括号序列均可通过上述 3 条规则得到。

例如，若 $k = 3$，则字符串 `((**()*(*))*)(***)` 是符合规范的超级括号序列，但字符串 `*()`、`(*()*)`、`((**))*)`、`(****(*))` 均不是。特别地，空字符串也不被视为符合规范的超级括号序列。

现在给出一个长度为 $n$ 的超级括号序列，其中有一些位置的字符已经确定，另外一些位置的字符尚未确定（用 `?` 表示）。小 w 希望能计算出：有多少种将所有尚未确定的字符一一确定的方法，使得得到的字符串是一个符合规范的超级括号序列？

可怜的小 c 并不会做这道题，于是只好请求你来帮忙。
## 输入格式

第一行，两个正整数 $n, k$。

第二行，一个长度为 $n$ 且仅由 `(`、`)`、`*`、`?` 构成的字符串 $S$。
## 输出格式

输出一个非负整数表示答案对 ${10}^9 + 7$ 取模的结果。
## 样例

### 样例输入 #1
```
7 3
(*??*??

```
### 样例输出 #1
```
5

```
### 样例输入 #2
```
10 2
???(*??(?)

```
### 样例输出 #2
```
19

```
### 样例输入 #3
```
见附件中的 bracket/bracket3.in
```
### 样例输出 #3
```
见附件中的 bracket/bracket3.ans
```
### 样例输入 #4
```
见附件中的 bracket/bracket4.in
```
### 样例输出 #4
```
见附件中的 bracket/bracket4.ans
```
## 提示

**【样例解释 #1】**

如下几种方案是符合规范的：

```plain
(**)*()
(**(*))
(*(**))
(*)**()
(*)(**)
```

**【数据范围】**

| 测试点编号 | $n \le$ | 特殊性质 |
|:-:|:-:|:-:|
| $1 \sim 3$ | $15$ | 无 |
| $4 \sim 8$ | $40$ | 无 |
| $9 \sim 13$ | $100$ | 无 |
| $14 \sim 15$ | $500$ | $S$ 串中仅含有字符 `?` |
| $16 \sim 20$ | $500$ | 无 |

对于 $100 \%$ 的数据，$1 \le k \le n \le 500$。


---

---
title: "「SFCOI-3」进行一个列的排"
layout: "post"
diff: 提高+/省选-
pid: P9493
tag: ['动态规划 DP', '2023', '洛谷原创', 'O2优化', '区间 DP']
---
# 「SFCOI-3」进行一个列的排
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/8v9kbxjs.png)

（其实这题原来叫 I must say No，不过出于某些显然的原因就改题目名了 /kk）

You must say Yes.

（题目背景图片来自 Phigros 曲绘，如有侵权，请告知出题人。）
## 题目描述

小 R 有一个长度为 $n$ 的排列 $p_1\dots p_n$。换句话说，$p_1\dots p_n$ 包含 $0 \sim (n - 1)$ 之间的数，并且满足对于 $0 \sim (n - 1)$ 这 $n$ 个数，每个数在 $p$ 中出现且仅出现一次。

小 R 有 $n$ 个限制，其中第 $i(0 \leq i \leq n - 1)$ 个用一个![](cnm,shabierLeasier)**正整数** $L_i$ 描述，表示至少有一个长度为 $L_i$ 的区间 $[l, r]$（即 $r - l + 1 = L_i$）满足 $\operatorname{mex}_{k=l}^r p_k = i$。

小 R 丢失了排列 $p_1\dots p_n$，不过幸运的是她仍然记得这 $n$ 条限制。请你帮她求出总共有多少个初始的合法排列，答案对 $998244353$ 取模。
## 输入格式

**本题每个测试点有多组数据。**

第一行一个整数 $T$ 表示数据组数。对于每组数据：

+ 第一行一个整数 $n$。
+ 第二行 $n$ 个整数依次表示 $L_0\dots L_{n-1}$。
## 输出格式

共 $T$ 行，每行一个整数表示答案。
## 样例

### 样例输入 #1
```
4
4
1 1 3 3
5
2 1 3 3 4
6
1 1 2 5 4 5
10
3 2 3 4 7 6 8 8 8 9
```
### 样例输出 #1
```
4
12
8
96
```
## 提示

### 定义

+ 一个序列的 $\operatorname{mex}$ 是其中没有出现过的最小非负整数，如 $\operatorname{mex}\{1, 3, 4\} = 0$，$\operatorname{mex}\{0, 1, 1, 2, 5\} = 3$，$\operatorname{mex}\{3, 1, 0, 2\} = 4$。

### 数据规模与约定

+ Subtask 0（10 pts）：$n \leq 10$。
+ Subtask 1（30 pts）：$n \leq 18$。
+ Subtask 2（15 pts）：$n \leq 300$。
+ Subtask 3（45 pts）：无特殊限制。

对于所有数据，$1 \leq T \leq 10$，$1 \leq n \leq 5 \times 10^3$，$1 \leq L_i \leq n$。


---

