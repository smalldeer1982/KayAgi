---
title: "New Year Snowmen"
layout: "post"
diff: 提高+/省选-
pid: CF140C
tag: ['离散化', '优先队列', '队列']
---

# New Year Snowmen

## 题目描述

As meticulous Gerald sets the table and caring Alexander sends the postcards, Sergey makes snowmen. Each showman should consist of three snowballs: a big one, a medium one and a small one. Sergey's twins help him: they've already made $ n $ snowballs with radii equal to $ r_{1} $ , $ r_{2} $ , ..., $ r_{n} $ . To make a snowman, one needs any three snowballs whose radii are pairwise different. For example, the balls with radii $ 1 $ , $ 2 $ and $ 3 $ can be used to make a snowman but $ 2 $ , $ 2 $ , $ 3 $ or $ 2 $ , $ 2 $ , $ 2 $ cannot. Help Sergey and his twins to determine what maximum number of snowmen they can make from those snowballs.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of snowballs. The next line contains $ n $ integers — the balls' radii $ r_{1} $ , $ r_{2} $ , ..., $ r_{n} $ ( $ 1<=r_{i}<=10^{9} $ ). The balls' radii can coincide.

## 输出格式

Print on the first line a single number $ k $ — the maximum number of the snowmen. Next $ k $ lines should contain the snowmen's descriptions. The description of each snowman should consist of three space-separated numbers — the big ball's radius, the medium ball's radius and the small ball's radius. It is allowed to print the snowmen in any order. If there are several solutions, print any of them.

## 样例 #1

### 输入

```
7
1 2 3 4 5 6 7

```

### 输出

```
2
3 2 1
6 5 4

```

## 样例 #2

### 输入

```
3
2 2 3

```

### 输出

```
0

```



---

---
title: "Least Cost Bracket Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF3D
tag: ['字符串', '优先队列', '队列']
---

# Least Cost Bracket Sequence

## 题目描述

This is yet another problem on regular bracket sequences.

A bracket sequence is called regular, if by inserting "+" and "1" into it we get a correct mathematical expression. For example, sequences "(())()", "()" and "(()(()))" are regular, while ")(", "(()" and "(()))(" are not. You have a pattern of a bracket sequence that consists of characters "(", ")" and "?". You have to replace each character "?" with a bracket so, that you get a regular bracket sequence.

For each character "?" the cost of its replacement with "(" and ")" is given. Among all the possible variants your should choose the cheapest.

## 输入格式

The first line contains a non-empty pattern of even length, consisting of characters "(", ")" and "?". Its length doesn't exceed $ 5·10^{4} $ . Then there follow $ m $ lines, where $ m $ is the number of characters "?" in the pattern. Each line contains two integer numbers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=10^{6} $ ), where $ a_{i} $ is the cost of replacing the $ i $ -th character "?" with an opening bracket, and $ b_{i} $ — with a closing one.

## 输出格式

Print the cost of the optimal regular bracket sequence in the first line, and the required sequence in the second.

Print -1, if there is no answer. If the answer is not unique, print any of them.

## 样例 #1

### 输入

```
(??)
1 2
2 8

```

### 输出

```
4
()()

```



---

---
title: "Contest Balloons"
layout: "post"
diff: 提高+/省选-
pid: CF725D
tag: ['模拟', '贪心', '优先队列', '队列']
---

# Contest Balloons

## 题目描述

ACM比赛，大家都知道。AC一题会有一个气球。
现在有$n(2<=n<=300000)$ 支队伍，每支队伍的重量是$w_i$ ，拥有$t_i$ 个气球$(w_i,t_i<=10^{18})$ ，当一支队伍的气球个数比它的重量都要大时，这个队伍就会飘起来，从而被取消比赛资格。
现在你带领的是1号队，你希望你队伍的名次尽可能靠前，你是个有原则的人，不会偷气球，但你可以把气球送给别的队伍，让他们飞起来。
求最终你的队伍所获得的最好名次

## 输入格式

第一行：一个正整数$n(2<=n<=300000)$ ，队伍的总数
第二行到第$n+1$ 行：每行两个整数$t_i,w_i(0<=t_i<=w_i<=10^{18})$ ，分别表示第$i$ 个队伍气球的个数以及它的重量。你的队伍是1号队。

## 输出格式

仅有一行，输出你带领的队伍能够达到的最好名次

感谢@2016wudi 提供的翻译

## 样例 #1

### 输入

```
8
20 1000
32 37
40 1000
45 50
16 16
16 16
14 1000
2 1000

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
4 4
4 4
4 4
4 4
4 4
4 4
5 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
7
14000000003 1000000000000000000
81000000000 88000000000
5000000000 7000000000
15000000000 39000000000
46000000000 51000000000
0 1000000000
0 0

```

### 输出

```
2

```



---

---
title: "Sockets"
layout: "post"
diff: 提高+/省选-
pid: CF732E
tag: ['贪心', '优先队列', '队列']
---

# Sockets

## 题目描述

ICM ACPC 世界决赛就要来临了！不幸的是，赛事组织者因为在准备赛题时太忙碌了，他们几乎忘了一个关键点——为参赛者的工作站准备电力资源。  
  
赛场有 $n$ 台为参赛者准备的电脑，第 $i$ 台电脑拥有与正整数 $p_i$ 相等大小的电源。同时，有 $m$ 个可用的插座，第 $j$ 个插座拥有与正整数 $s_j$ 相等的电源。只有当 $p_i = s_j$ 时才可以将第 $i$ 台电脑和第 $j$ 个插座连接。一台电脑只可以接一个插座。不仅如此，如果所有的电脑与插座的电源都不同，那么没有任何电脑可以接通至插座。  
  
为了解决问题，Puch Williams 教授紧急订购了一车适配器（电源分离器）。每个适配器都有一个插头与一个插座，在它们之间还有一个分压器。在将适配器插入一个带有 $x$ 的电源后，适配器上的插座将会拥有一个 $\left \lceil \frac{x}{2} \right \rceil $ 的电源，这代表着将被插入的插座的电源除以 $2$，再取顶。例如：$\left \lceil \frac{10}{2} \right \rceil =5$，$\left \lceil \frac{15}{2} \right \rceil =8$。  
  
每个适配器只能使用一次。它可以被多次串联。例如，在将一个适配器插入一个插入带有 $10$ 电源的插座的适配器时，可以将一个带有 $3$ 电源的电脑插入这个适配器。  
  
组织者们会安装这些适配器，以确保它会同时输送给最多 $c$ 台电脑。如果有多种连接方案，组织者们想要在连接最多 $c$ 台电脑的前提下，使用最少 $u$ 个适配器的方案。  
  
你的任务是帮助组织者们计算完成这个任务最大的 $c$ 和最小的 $u$。  
  
这一车适配器是足够这个任务使用的，同时数据保证至少可以连接一台电脑。

## 输入格式

第一行包含两个整数 $n$ 和 $m$（$1 \le n,m \le 200000$），分别为电脑的数量和插座的数量。  
第二行包含 $n$ 个整数，$p_1,p_2,\ldots,p_n$（$1 \le p_i \le 10^9$），为电脑的电源。  
第三行包含 $m$ 个整数，$s_1,s_2,\ldots,s_m$（$1 \le s_i \le 10^9$），为插座的电源。

## 输出格式

第一行输出两个数字 $c$ 和 $u$，分别为最多可以连接的电脑数量与最少可以使用的适配器数量。  
第二行输出 $m$ 个数字，$a_1,a_2,\ldots,a_m$（$0 \le a_i \le 10^9$），为插在第 $i$ 个插座上的适配器数量。$a_i$ 的和应等于 $u$。  
第三行输出 $n$ 个数字，$b_1,b_2,\ldots,b_m$（$0 \le b_i \le m$），为第 $j$ 台电脑插入的插座序号。若 $b_j=0$，代表第 $j$ 台电脑不应插入任何插座。当 $b_j\ne 0$ 时，任何 $b_j$ 应不相等。在插入了 $a_{bj}$ 个适配器后，第 $j$ 台电脑的电源应与第 $b_j$ 个插座的电源相等。非 $0$ 的 $b_j$ 的数量应等于 $c$。  
如果有多组答案，请输出任意一组。

## 样例 #1

### 输入

```
2 2
1 1
2 2

```

### 输出

```
2 2
1 1
1 2

```

## 样例 #2

### 输入

```
2 1
2 100
99

```

### 输出

```
1 6
6
1 0

```



---

---
title: "Buy Low Sell High"
layout: "post"
diff: 提高+/省选-
pid: CF865D
tag: ['贪心', '优先队列', '队列']
---

# Buy Low Sell High

## 题目描述

你可以完美地预测某只股票接下来 $N$ 天的价格，你想利用这一知识盈利，但你每天只想买卖一股，这表明你每天要么什么都不干，要么买入一股，要么卖出一股。起初你没有股票，你也不能在没有股票时卖出股票。你希望在第 $N$ 天结束时不持有股票，并最大化盈利。

## 输入格式

第一行一个整数 $N$（$2 \le N \le 3 \times 10^5$），表示天数。

接下来一行 $N$ 个整数 $p_1,p_2,\dots p_N$（$1 \le p_i \le 10^6$），表示第 $i$ 天的股价。

## 输出格式

输出你第 $N$ 天结束时的最大盈利。

### 样例解释

在股价为 $5,4$ 时各买入一股，在股价为 $9,12$ 时各卖出一股，接着在股价为 $2$ 时买入一股，股价为 $10$ 时卖出一股，总收益为 $20$。

Translated by uid $408071$。

## 样例 #1

### 输入

```
9
10 5 4 7 9 12 6 2 10

```

### 输出

```
20

```

## 样例 #2

### 输入

```
20
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3 2 3 8 4

```

### 输出

```
41

```



---

---
title: "Too Easy Problems"
layout: "post"
diff: 提高+/省选-
pid: CF913D
tag: ['贪心', '排序', '优先队列']
---

# Too Easy Problems

## 题目描述

你正在准备一场关于调度理论的考试。

这场考试会持续正好 $T$ 毫秒，由 $n$ 道题目组成。

你可以用 $t_i$ 毫秒解决第 $i$ 个问题，或者忽略它并不消耗时间。你也不需要用来在做完一道题之后休息的时间。

不幸的是，你的老师认为一些题目对你来说太简单了。因此，他对于每道题 $i$ 规定了一个整数 $a_i$，表示题目 $i$ 只在你总共解决了不超过 $a_i$ 个问题（包括问题 $i$ ）的情况下为你的最终成绩加上一分。

正式地，假设你在考试中解决了问题 $p_1,p_2,\cdots,p_k$。那么，你的最终成绩 $s$ 会等于在 $1$ 到 $k$ 之间的满足 $k\le a_{p_j}$ 的 $j$ 的个数。

你已经意识到这场考试真正的第一道题目已经放在了你面前。因此，你想要选择一组题目来解决，从而最大化你的最终成绩。不要忘记这场考试有时间限制，而你必须有足够的时间来解决所有你选择的题目。如果存在多个最优解，任意输出一组即可。

## 输入格式

第一行包含 $2$ 个整数，$n$ 和 $T$，分别是考试中题目的数量和考试时长的毫秒数。

接下来的 $n$ 行每行包括两个整数 $a_i$ 和 $t_i$。题目编号从 $1$ 到 $n$。

## 输出格式

在第一行，输出一个单独的整数 $s$，表示你的可能得到的最终成绩的最大值。

在第二行，输出一个单独的整数 $k$ 表示你应该解决的问题数量。

在第三行，以任意顺序输出 $k$ 个不同整数 $p_1,p_2,\cdots,p_k$，即你应当解决的题目编号。

如果有多个最优解，你可以输出其中任意一个。

## 样例解释

在第一个样例中，你应该解决题目 $3$、$1$ 和 $4$。在这种解下你会花费 $80+100+90=270$ 毫秒，在考试的长度 $300$ms 以内（甚至给自己留出了 $30$ms 休息时间）。题目 $3$ 和题目 $1$ 会分别为你带来 $1$ 分，然而题目 $4$ 不会。你会得到 $2$ 分。

在第二个样例中，这场灾难性的考试的长度甚至不足以解决一道题目（所以你显然一分都得不到）。

在第三个样例中，你刚好有足够的时间 $(42+58=100)$ 来解决这两道题并且微笑着把答卷交给老师。

## 说明/提示

$1\le n\le 2\times10^5$

$1\le T\le10^9$

$0\le k\le n$

## 样例 #1

### 输入

```
5 300
3 100
4 150
4 80
2 90
2 300

```

### 输出

```
2
3
3 1 4

```

## 样例 #2

### 输入

```
2 100
1 787
2 788

```

### 输出

```
0
0


```

## 样例 #3

### 输入

```
2 100
2 42
2 58

```

### 输出

```
2
2
1 2

```



---

---
title: "Volleyball"
layout: "post"
diff: 提高+/省选-
pid: CF95C
tag: ['优先队列', '最短路', '队列']
---

# Volleyball

## 题目描述

Petya loves volleyball very much. One day he was running late for a volleyball match. Petya hasn't bought his own car yet, that's why he had to take a taxi. The city has $ n $ junctions, some of which are connected by two-way roads. The length of each road is defined by some positive integer number of meters; the roads can have different lengths.

Initially each junction has exactly one taxi standing there. The taxi driver from the $ i $ -th junction agrees to drive Petya (perhaps through several intermediate junctions) to some other junction if the travel distance is not more than $ t_{i} $ meters. Also, the cost of the ride doesn't depend on the distance and is equal to $ c_{i} $ bourles. Taxis can't stop in the middle of a road. Each taxi can be used no more than once. Petya can catch taxi only in the junction, where it stands initially.

At the moment Petya is located on the junction $ x $ and the volleyball stadium is on the junction $ y $ . Determine the minimum amount of money Petya will need to drive to the stadium.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=1000,0<=m<=1000) $ . They are the number of junctions and roads in the city correspondingly. The junctions are numbered from $ 1 $ to $ n $ , inclusive. The next line contains two integers $ x $ and $ y $ ( $ 1<=x,y<=n $ ). They are the numbers of the initial and final junctions correspondingly. Next $ m $ lines contain the roads' description. Each road is described by a group of three integers $ u_{i} $ , $ v_{i} $ , $ w_{i} $ ( $ 1<=u_{i},v_{i}<=n,1<=w_{i}<=10^{9} $ ) — they are the numbers of the junctions connected by the road and the length of the road, correspondingly. The next $ n $ lines contain $ n $ pairs of integers $ t_{i} $ and $ c_{i} $ ( $ 1<=t_{i},c_{i}<=10^{9} $ ), which describe the taxi driver that waits at the $ i $ -th junction — the maximum distance he can drive and the drive's cost. The road can't connect the junction with itself, but between a pair of junctions there can be more than one road. All consecutive numbers in each line are separated by exactly one space character.

## 输出格式

If taxis can't drive Petya to the destination point, print "-1" (without the quotes). Otherwise, print the drive's minimum cost.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I64d specificator.

## 说明/提示

An optimal way — ride from the junction 1 to 2 (via junction 4), then from 2 to 3. It costs 7+2=9 bourles.

## 样例 #1

### 输入

```
4 4
1 3
1 2 3
1 4 1
2 4 1
2 3 5
2 7
7 2
1 2
7 7

```

### 输出

```
9

```



---

