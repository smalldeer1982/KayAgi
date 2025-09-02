---
title: "Nezzar and Tournaments"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1477E
tag: ['数学', '线段树']
---

# Nezzar and Tournaments

## 题目描述

In the famous Oh-Suit-United tournament, two teams are playing against each other for the grand prize of precious pepper points.

The first team consists of $ n $ players, and the second team consists of $ m $ players. Each player has a potential: the potential of the $ i $ -th player in the first team is $ a_i $ , and the potential of the $ i $ -th player in the second team is $ b_i $ .

In the tournament, all players will be on the stage in some order. There will be a scoring device, initially assigned to an integer $ k $ , which will be used to value the performance of all players.

The scores for all players will be assigned in the order they appear on the stage. Let the potential of the current player be $ x $ , and the potential of the previous player be $ y $ ( $ y $ equals $ x $ for the first player). Then, $ x-y $ is added to the value in the scoring device, Afterwards, if the value in the scoring device becomes negative, the value will be reset to $ 0 $ . Lastly, the player's score is assigned to the current value on the scoring device. The score of a team is the sum of the scores of all its members.

As an insane fan of the first team, Nezzar desperately wants the biggest win for the first team. He now wonders what is the maximum difference between scores of the first team and the second team.

Formally, let the score of the first team be $ score_f $ and the score of the second team be $ score_s $ . Nezzar wants to find the maximum value of $ score_f - score_s $ over all possible orders of players on the stage.

However, situation often changes and there are $ q $ events that will happen. There are three types of events:

- $ 1 $ $ pos $ $ x $ — change $ a_{pos} $ to $ x $ ;
- $ 2 $ $ pos $ $ x $ — change $ b_{pos} $ to $ x $ ;
- $ 3 $ $ x $ — tournament is held with $ k = x $ and Nezzar wants you to compute the maximum value of $ score_f - score_s $ .

Can you help Nezzar to answer the queries of the third type?

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ q $ ( $ 1 \le n,m \le 2 \cdot 10^5, 1 \le q \le 5 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^6 $ ).

The third line contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 0 \le b_i \le 10^6 $ ).

The following $ q $ lines contain descriptions of events, described in the statement, each in one of the three possible formats:

- $ 1 $ $ pos $ $ x $ ( $ 1 \le pos \le n $ , $ 0 \le x \le 10^6 $ );
- $ 2 $ $ pos $ $ x $ ( $ 1 \le pos \le m $ , $ 0 \le x \le 10^6 $ );
- $ 3 $ $ x $ ( $ 0 \le x \le 10^6 $ ).

## 输出格式

For each query of the third type print the answer to this query.

## 说明/提示

In the first query of the first test, the tournament is held with $ k = 5 $ . It would be optimal to arrange players in such way (here their potentials are written):

 $ \underline{7} $ , $ 3 $ , $ 5 $ , $ 4 $ , $ 6 $ , $ \underline{1} $ , $ \underline{2} $ (underlined numbers are potentials of players that are from the first team).

The individual scores of players, numbered in the order of their appearance, are:

- $ \max(5 + (7 - 7), 0) = 5 $ for the $ \underline{1} $ -st player;
- $ \max(5 + (3 - 7), 0) = 1 $ for the $ 2 $ -nd player;
- $ \max(1 + (5 - 3), 0) = 3 $ for the $ 3 $ -rd player;
- $ \max(3 + (4 - 5), 0) = 2 $ for the $ 4 $ -th player;
- $ \max(2 + (6 - 4), 0) = 4 $ for the $ 5 $ -th player;
- $ \max(4 + (1 - 6), 0) = 0 $ for the $ \underline{6} $ -th player;
- $ \max(0 + (2 - 1), 0) = 1 $ for the $ \underline{7} $ -th player.

So, $ score_f = 5 + 0 + 1 = 6 $ and $ score_s = 1 + 3 + 2 + 4 = 10 $ . The score difference is $ 6 - 10 = -4 $ . It can be proven, that it is the maximum possible score difference.

## 样例 #1

### 输入

```
3 4 3
1 2 7
3 4 5 6
3 5
1 1 10
3 5
```

### 输出

```
-4
9
```

## 样例 #2

### 输入

```
7 8 12
958125 14018 215153 35195 90380 30535 204125
591020 930598 252577 333333 999942 1236 9456 82390
3 123458
2 4 444444
3 123456
1 2 355555
3 123478
3 1111
2 6 340324
3 1111
2 8 999999
2 7 595959
3 222222
3 100
```

### 输出

```
1361307
1361311
1702804
1879305
1821765
1078115
1675180
```



---

---
title: "Fishingprince Plays With Array Again"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1696G
tag: ['动态规划 DP', '线段树', '线性规划']
---

# Fishingprince Plays With Array Again

## 题目描述

Suppose you are given a 1-indexed sequence $ a $ of non-negative integers, whose length is $ n $ , and two integers $ x $ , $ y $ . In consecutive $ t $ seconds ( $ t $ can be any positive real number), you can do one of the following operations:

- Select $ 1\le i<n $ , decrease $ a_i $ by $ x\cdot t $ , and decrease $ a_{i+1} $ by $ y\cdot t $ .
- Select $ 1\le i<n $ , decrease $ a_i $ by $ y\cdot t $ , and decrease $ a_{i+1} $ by $ x\cdot t $ .

Define the minimum amount of time (it might be a real number) required to make all elements in the sequence less than or equal to $ 0 $ as $ f(a) $ .

For example, when $ x=1 $ , $ y=2 $ , it takes $ 3 $ seconds to deal with the array $ [3,1,1,3] $ . We can:

- In the first $ 1.5 $ seconds do the second operation with $ i=1 $ .
- In the next $ 1.5 $ seconds do the first operation with $ i=3 $ .

We can prove that it's not possible to make all elements less than or equal to $ 0 $ in less than $ 3 $ seconds, so $ f([3,1,1,3])=3 $ .

Now you are given a 1-indexed sequence $ b $ of positive integers, whose length is $ n $ . You are also given positive integers $ x $ , $ y $ . Process $ q $ queries of the following two types:

- 1 k v: change $ b_k $ to $ v $ .
- 2 l r: print $ f([b_l,b_{l+1},\dots,b_r]) $ .

## 输入格式

The first line of input contains two integers $ n $ and $ q $ ( $ 2\le n\le 2\cdot 10^5 $ , $ 1\le q\le 2\cdot 10^5 $ ).

The second line of input contains two integers $ x $ and $ y $ ( $ 1\le x,y\le 10^6 $ ).

The third line of input contains $ n $ integers $ b_1,b_2,\ldots,b_n $ ( $ 1\le b_i\le 10^6 $ ).

This is followed by $ q $ lines. Each of these $ q $ lines contains three integers. The first integer $ op $ is either $ 1 $ or $ 2 $ .

- If it is $ 1 $ , it is followed by two integers $ k $ , $ v $ ( $ 1\le k\le n $ , $ 1\le v\le 10^6 $ ). It means that you should change $ b_k $ to $ v $ .
- If it is $ 2 $ , it is followed by two integers $ l $ , $ r $ ( $ 1\le l<r\le n $ ). It means that you should print $ f([b_l,b_{l+1},\dots,b_r]) $ .

## 输出格式

For each query of type $ 2 $ , print one real number — the answer to the query. Your answer is considered correct if its absolute error or relative error does not exceed $ 10^{-9} $ .

## 说明/提示

Let's analyse the sample.

In the first query, we are asked to compute $ f([3,1,1,4]) $ . The answer is $ 3.5 $ . One optimal sequence of operations is:

- In the first $ 1.5 $ seconds do the second operation with $ i=1 $ .
- In the next $ 2 $ seconds do the first operation with $ i=3 $ .

In the third query, we are asked to compute $ f([1,1,1]) $ . The answer is $ 1 $ . One optimal sequence of operations is:

- In the first $ 0.5 $ seconds do the second operation with $ i=1 $ .
- In the next $ 0.5 $ seconds do the first operation with $ i=2 $ .

## 样例 #1

### 输入

```
4 3
1 2
3 1 1 4
2 1 4
1 1 1
2 1 3
```

### 输出

```
3.500000000000000
1.000000000000000
```



---

---
title: "Bugaboo"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1707F
tag: ['动态规划 DP', '线段树']
---

# Bugaboo

## 题目描述

A transformation of an array of positive integers $ a_1,a_2,\dots,a_n $ is defined by replacing $ a $ with the array $ b_1,b_2,\dots,b_n $ given by $ b_i=a_i\oplus a_{(i\bmod n)+1} $ , where $ \oplus $ denotes the bitwise XOR operation.

You are given integers $ n $ , $ t $ , and $ w $ . We consider an array $ c_1,c_2,\dots,c_n $ ( $ 0 \le c_i \le 2^w-1 $ ) to be bugaboo if and only if there exists an array $ a_1,a_2,\dots,a_n $ such that after transforming $ a $ for $ t $ times, $ a $ becomes $ c $ .

For example, when $ n=6 $ , $ t=2 $ , $ w=2 $ , then the array $ [3,2,1,0,2,2] $ is bugaboo because it can be given by transforming the array $ [2,3,1,1,0,1] $ for $ 2 $ times:

 $ $$$ [2,3,1,1,0,1]\to [2\oplus 3,3\oplus 1,1\oplus 1,1\oplus 0,0\oplus 1,1\oplus 2]=[1,2,0,1,1,3]; \\ [1,2,0,1,1,3]\to [1\oplus 2,2\oplus 0,0\oplus 1,1\oplus 1,1\oplus 3,3\oplus 1]=[3,2,1,0,2,2].  $ $ </p><p>And the array  $ \[4,4,4,4,0,0\] $  is not bugaboo because  $ 4 &gt; 2^2 - 1 $ . The array  $ \[2,3,3,3,3,3\] $  is also not bugaboo because it can't be given by transforming one array for  $ 2 $  times.</p><p>You are given an array  $ c $  with some positions lost (only  $ m $  positions are known at first and the remaining positions are lost). And there are  $ q $  modifications, where each modification is changing a position of  $ c $ . A modification can possibly change whether the position is lost or known, and it can possibly redefine a position that is already given.</p><p>You need to calculate how many possible arrays  $ c $  (with arbitrary elements on the lost positions) are bugaboos after each modification. Output the  $ i $ -th answer modulo  $ p\_i $  ( $ p\_i $  is a given array consisting of  $ q$$$ elements).

## 输入格式

The first line contains four integers $ n $ , $ m $ , $ t $ and $ w $ ( $ 2\le n\le 10^7 $ , $ 0\le m\le \min(n, 10^5) $ , $ 1\le t\le 10^9 $ , $ 1\le w\le 30 $ ).

The $ i $ -th line of the following $ m $ lines contains two integers $ d_i $ and $ e_i $ ( $ 1\le d_i\le n $ , $ 0\le e_i< 2^w $ ). It means the position $ d_i $ of the array $ c $ is given and $ c_{d_i}=e_i $ . It is guaranteed that $ 1\le d_1<d_2<\ldots<d_m\le n $ .

The next line contains only one number $ q $ ( $ 1\le q\le 10^5 $ ) — the number of modifications.

The $ i $ -th line of the following $ q $ lines contains three integers $ f_i $ , $ g_i $ , $ p_i $ ( $ 1\le f_i\le n $ , $ -1\le g_i< 2^w $ , $ 11\le p_i\le 10^9+7 $ ). The value $ g_i=-1 $ means changing the position $ f_i $ of the array $ c $ to a lost position, otherwise it means changing the position $ f_i $ of the array $ c $ to a known position, and $ c_{f_i}=g_i $ . The value $ p_i $ means you need to output the $ i $ -th answer modulo $ p_i $ .

## 输出格式

The output contains $ q $ lines, denoting your answers.

## 说明/提示

In the first example, $ n=3 $ , $ t=1 $ , and $ w=1 $ . Let $ ? $ denote a lost position of $ c $ .

In the first query, $ c=[1,0,1] $ . The only possible array $ [1,0,1] $ is bugaboo because it can be given by transforming $ [0,1,1] $ once. So the answer is $ 1\bmod 123\,456\,789 = 1 $ .

In the second query, $ c=[1,1,1] $ . The only possible array $ [1,1,1] $ is not bugaboo. So the answer is $ 0\bmod 111\,111\,111 = 0 $ .

In the third query, $ c=[?,1,1] $ . There are two possible arrays $ [1,1,1] $ and $ [0,1,1] $ . Only $ [0,1,1] $ is bugaboo because it can be given by transforming $ [1,1,0] $ once. So the answer is $ 1\bmod 987\,654\,321=1 $ .

In the fourth query, $ c=[?,1,?] $ . There are four possible arrays. $ [0,1,1] $ and $ [1,1,0] $ are bugaboos. $ [1,1,0] $ can be given by performing $ [1,0,1] $ once. So the answer is $ 2\bmod 555\,555\,555=2 $ .

## 样例 #1

### 输入

```
3 2 1 1
1 1
3 1
4
2 0 123456789
2 1 111111111
1 -1 987654321
3 -1 555555555
```

### 输出

```
1
0
1
2
```

## 样例 #2

### 输入

```
24 8 5 4
4 4
6 12
8 12
15 11
16 7
20 2
21 9
22 12
13
2 13 11
3 15 12
5 7 13
9 3 14
10 5 15
11 15 16
13 14 17
14 1 18
18 9 19
19 6 20
23 10 21
24 8 22
21 13 23
```

### 输出

```
1
4
9
2
1
0
1
10
11
16
16
0
16
```



---

---
title: "Game in Tree (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2013F2
tag: ['贪心', '线段树', '根号分治']
---

# Game in Tree (Hard Version)

## 题目描述

这是问题的困难版本。在这一版本中，不要求 $u = v$。只有当两个版本的问题都成功解决后，你才能进行 hack。

Alice 和 Bob 在一棵树上玩一个有趣的游戏。这棵树有 $n$ 个顶点，编号从 $1$ 到 $n$。回顾一下，一棵有 $n$ 个顶点的树是一个有 $n - 1$ 条边的无向连通图。

游戏规则是 Alice 和 Bob 轮流移动，Alice 先行动，每位玩家在自己的回合中，必须从当前所在的顶点移动到一个尚未被访问过的相邻顶点。如果某个玩家无法移动，则他输掉比赛。

给定两个顶点 $u$ 和 $v$。从顶点 $u$ 到顶点 $v$ 的简单路径用数组表示为 $p_1, p_2, p_3, \ldots, p_m$，其中 $p_1 = u$，$p_m = v$，并且每对相邻的顶点 $p_i$ 和 $p_{i+1}$之间都有一条边（$1 \le i < m$）。

你的任务是，判断在 Alice 从顶点 $1$ 开始，而 Bob 从路径中的顶点 $p_j$（$1 \le j \le m$）开始的情况下，谁将获胜。

## 输入格式

输入包含多个测试用例。第一行为测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来每个测试用例进行描述。

每个测试用例的第一行是一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示树中顶点的个数。

接下来的 $n - 1$ 行，每行包含两个整数 $a$ 和 $b$（$1 \le a, b \le n$），表示顶点 $a$ 和 $b$ 之间连接着一条无向边。这些边保证组成一棵树。

测试用例的最后一行包含两个整数 $u$ 和 $v$（$2 \le u, v \le n$），保证从 $u$ 到 $v$ 的路径不通过顶点 $1$。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $m$ 行。

在第 $i$ 行输出结果，如果 Alice 从顶点 $1$ 开始而 Bob 从顶点 $p_i$ 开始时，游戏的赢家是谁。如果 Alice 赢，则输出“Alice”；否则输出“Bob”。

## 说明/提示

在第一个例子中，路径是（$2, 3$）。如果 Bob 开始时位于顶点 $2$，Alice 在第一回合就无法移动，只能输掉比赛。而如果 Bob 从顶点 $3$ 开始，Alice 会移动到顶点 $2$，此时 Bob 就没有顶点可动并会输掉比赛。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3
1 2
2 3
2 3
6
1 2
1 3
2 4
2 5
1 6
4 5
4
1 2
1 3
2 4
2 4
```

### 输出

```
Bob
Alice
Alice
Bob
Alice
Bob
Alice
```



---

---
title: "Hills and Pits"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2023F
tag: ['线段树', '前缀和', '扫描线']
---

# Hills and Pits

## 题目描述

在一个地势起伏的沙漠城市中，市政府计划购置一辆自卸卡车来平整道路。道路按从左到右的顺序被分为 $ n $ 段，编号为 $ 1 $ 到 $ n $。第 $ i $ 段道路的初始高度是 $ a_i $ 。如果某段道路的高度高于 $ 0 $，则需要自卸卡车从中移走部分沙子；如果低于 $ 0 $，则需要用沙子填平。所有路段在开始时的高度都不为 $ 0 $。

当卡车在第 $ i $ 段时，它可以取走 $ x $ 单位的沙子，使该段高度减少 $ x $，或者可以填入 $ x $ 单位的沙子（前提是车上至少有 $ x $ 单位沙子），使该段高度增加 $ x $。

卡车可以从任一段开始工作。移动到相邻的下一段或上一段需要花费 $ 1 $ 分钟，而装填和卸料的时间则可以忽略不计。卡车有无限容量，最初是空车。

你的任务是计算出将每个路段高度调整为 $ 0 $ 所需的最短时间。注意，完成所有操作后，车上可能仍残留沙子。你需要单独解决每个从 $ l_i $ 到 $ r_i $ 段的沙子调整问题，且只能使用指定段内的沙子。

## 输入格式

第一行输入一个整数 $ t $ （$ 1 \le t \le 10^4 $）表示测试用例的数量。紧随其后的是每组测试用例的具体描述。

每个测试用例的第一行包含两个整数 $ n $ 和 $ q $ （$ 1 \le n, q \le 3 \cdot 10^5 $）—— 分别表示路段数量和查询次数。

第二行给出 $ n $ 个整数 $ a_1, a_2, \ldots, a_n $ （$ -10^9 \le a_i \le 10^9 $，且 $ a_i \neq 0 $），代表每个路段的初始高度。

接下来 $ q $ 行中，每行两个整数 $ l_i $ 和 $ r_i $ （$ 1 \le l_i \le r_i \le n $），表示需要寻找最短时间的区间。

保证所有测试用例中 $ n $ 的总和以及 $ q $ 的总和不超过 $ 3 \cdot 10^5 $。

## 输出格式

对于每个查询，输出调整区间 $ [l_i, r_i] $ 的沙子高度至 $ 0 $ 所需的最短时间，如果无法完成，输出 $ -1 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
1 1
-179
1 1
5 3
-2 2 -1 3 -1
2 4
1 5
1 3
7 1
1 1 1 -4 1 1 1
1 7
7 2
2 -2 2 -2 1 2 -1
1 7
2 7
4 4
1000000000 1000000000 999999999 -1000000000
2 4
3 4
2 3
1 3
```

### 输出

```
-1
2
5
-1
8
6
6
2
-1
1
2
```



---

---
title: "Aquatic Dragon"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2045D
tag: ['动态规划 DP', '线段树']
---

# Aquatic Dragon

## 题目描述

你居住在一个由 $N$ 个岛屿组成的群岛中，这些岛屿排列成一条直线。岛屿从 $1$ 开始依次编号到 $N$。相邻的岛屿 $i$ 和 $i+1$ 之间有单向水下隧道：一条从岛 $i$ 到 $i+1$，另一条反向。而每条隧道只能走一次。

你和一条龙同行。龙的耐力以非负整数表示，用来施展游泳和飞行能力。初始时，其耐力为 $0$。

每个岛上都有一个魔法神社，当你第一次到达某岛时，会立即将龙的耐力增加 $P_i$（无论龙身处何地）。这个过程无需时间。

在某个岛上，你可以做以下三种移动：

- 如果你和你的龙在同一岛上，可以让龙游到相邻岛屿，前提是龙的耐力至少是 $D$。该操作会消耗耐力 $D$，耗时 $T_s$ 秒。
- 如果你和你的龙在同一岛上，可以让龙飞到相邻岛屿，前提是龙的耐力不为零。此举会将耐力归零，耗时 $T_f$ 秒。
- 你可以单独通过水下隧道步行到相邻岛屿，这需要花费 $T_w$ 秒。一旦你通过这条隧道，就不能再次使用。

请注意，游泳和飞行时不使用隧道。

你和龙当前在岛屿 $1$ 上。你的任务是带着龙到达岛屿 $N$，请计算出任务完成的最短时间。

## 输入格式

第一行包含五个整数 $N$、$D$、$T_s$、$T_f$ 和 $T_w$，其中 $2 \leq N \leq 200,000$，$1 \leq D, T_s, T_f, T_w \leq 200,000$。  
第二行包含 $N$ 个整数 $P_i$，满足 $1 \leq P_i \leq 200,000$。

## 输出格式

输出一个整数，为到达岛屿 $N$ 的最短时间。

## 说明/提示

### 示例解释 #1

以下是完成任务的最短事件序列：

1. 在岛 $1$ 的神社将龙的耐力增加到 $1$。
2. 带龙飞到岛 $2$，神社令龙的耐力增至 $2$。
3. 单独走到岛 $3$，神社令龙的耐力增至 $6$。
4. 单独走到岛 $4$，神社令龙的耐力增至 $8$。
5. 单独走回岛 $3$。
6. 单独走回岛 $2$。
7. 带龙游回岛 $3$，此时龙的耐力为 $4$。
8. 带龙游到岛 $4$，此时龙的耐力为 $0$。
9. 单独走到岛 $5$，神社令龙的耐力增至 $1$。
10. 单独走回岛 $4$。
11. 带龙飞到岛 $5$。

### 示例解释 #2

对于 $1 \leq i < 5$，重复以下过程：在岛 $i$ 的神社增加龙的耐力，然后带龙飞到岛 $i+1$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5 4 2 9 1
1 2 4 2 1
```

### 输出

```
28
```

## 样例 #2

### 输入

```
5 4 2 1 1
1 2 4 2 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 4 2 10 1
3 1 2
```

### 输出

```
16
```



---

---
title: "The Classic Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF464E
tag: ['最短路', '可持久化线段树', '哈希 hashing']
---

# The Classic Problem

## 题目描述

You are given a weighted undirected graph on $ n $ vertices and $ m $ edges. Find the shortest path from vertex $ s $ to vertex $ t $ or else state that such path doesn't exist.

## 输入格式

The first line of the input contains two space-separated integers — $ n $ and $ m $ ( $ 1<=n<=10^{5} $ ; $ 0<=m<=10^{5} $ ).

Next $ m $ lines contain the description of the graph edges. The $ i $ -th line contains three space-separated integers — $ u_{i} $ , $ v_{i} $ , $ x_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ; $ 0<=x_{i}<=10^{5} $ ). That means that vertices with numbers $ u_{i} $ and $ v_{i} $ are connected by edge of length $ 2^{x_{i}} $ (2 to the power of $ x_{i} $ ).

The last line contains two space-separated integers — the numbers of vertices $ s $ and $ t $ .

The vertices are numbered from $ 1 $ to $ n $ . The graph contains no multiple edges and self-loops.

## 输出格式

In the first line print the remainder after dividing the length of the shortest path by $ 1000000007 (10^{9}+7) $ if the path exists, and -1 if the path doesn't exist.

If the path exists print in the second line integer $ k $ — the number of vertices in the shortest path from vertex $ s $ to vertex $ t $ ; in the third line print $ k $ space-separated integers — the vertices of the shortest path in the visiting order. The first vertex should be vertex $ s $ , the last vertex should be vertex $ t $ . If there are multiple shortest paths, print any of them.

## 说明/提示

A path from vertex $ s $ to vertex $ t $ is a sequence $ v_{0} $ , ..., $ v_{k} $ , such that $ v_{0}=s $ , $ v_{k}=t $ , and for any $ i $ from 0 to $ k-1 $ vertices $ v_{i} $ and $ v_{i+1} $ are connected by an edge.

The length of the path is the sum of weights of edges between $ v_{i} $ and $ v_{i+1} $ for all $ i $ from 0 to $ k-1 $ .

The shortest path from $ s $ to $ t $ is the path which length is minimum among all possible paths from $ s $ to $ t $ .

## 样例 #1

### 输入

```
4 4
1 4 2
1 2 0
2 3 0
3 4 0
1 4

```

### 输出

```
3
4
1 2 3 4 

```

## 样例 #2

### 输入

```
4 3
1 2 4
2 3 5
3 4 6
1 4

```

### 输出

```
112
4
1 2 3 4 

```

## 样例 #3

### 输入

```
4 2
1 2 0
3 4 1
1 4

```

### 输出

```
-1

```



---

---
title: "Cool Slogans"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF700E
tag: ['线段树', '后缀自动机 SAM', '后缀数组 SA']
---

# Cool Slogans

## 题目描述

Bomboslav set up a branding agency and now helps companies to create new logos and advertising slogans. In term of this problems, slogan of the company should be a non-empty substring of its name. For example, if the company name is "hornsandhoofs", then substrings "sand" and "hor" could be its slogans, while strings "e" and "hornss" can not.

Sometimes the company performs rebranding and changes its slogan. Slogan $ A $ is considered to be cooler than slogan $ B $ if $ B $ appears in $ A $ as a substring at least twice (this occurrences are allowed to overlap). For example, slogan $ A= $ "abacaba" is cooler than slogan $ B= $ "ba", slogan $ A= $ "abcbcbe" is cooler than slogan $ B= $ "bcb", but slogan $ A= $ "aaaaaa" is not cooler than slogan $ B= $ "aba".

You are given the company name $ w $ and your task is to help Bomboslav determine the length of the longest sequence of slogans $ s_{1},s_{2},...,s_{k} $ , such that any slogan in the sequence is cooler than the previous one.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the length of the company name that asks Bomboslav to help. The second line contains the string $ w $ of length $ n $ , that consists of lowercase English letters.

## 输出格式

Print a single integer — the maximum possible length of the sequence of slogans of the company named $ w $ , such that any slogan in the sequence (except the first one) is cooler than the previous

## 样例 #1

### 输入

```
3
abc

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
ddddd

```

### 输出

```
5

```

## 样例 #3

### 输入

```
11
abracadabra

```

### 输出

```
3

```



---

---
title: "New Year and Binary Tree Paths"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF750G
tag: ['动态规划 DP', '线段树', '枚举']
---

# New Year and Binary Tree Paths

## 题目描述

The New Year tree is an infinite perfect binary tree rooted in the node $ 1 $ . Each node $ v $ has two children: nodes indexed $ (2·v) $ and $ (2·v+1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/5f3fba6843b56e8c74120fa68d53319463f26696.png)Polar bears love decorating the New Year tree and Limak is no exception. As he is only a little bear, he was told to decorate only one simple path between some pair of nodes. Though he was given an opportunity to pick the pair himself! Now he wants to know the number of unordered pairs of indices $ (u,v) $ ( $ u<=v $ ), such that the sum of indices of all nodes along the simple path between $ u $ and $ v $ (including endpoints) is equal to $ s $ . Can you help him and count this value?

## 输入格式

The only line of the input contains a single integer $ s $ ( $ 1<=s<=10^{15} $ ).

## 输出格式

Print one integer, denoting the number of unordered pairs of nodes indices defining simple paths with the sum of indices of vertices equal to $ s $ .

## 说明/提示

In sample test, there are $ 4 $ paths with the sum of indices equal to $ 10 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/c83b62a188e719702078b419fb6e934500dacd07.png)

## 样例 #1

### 输入

```
10

```

### 输出

```
4

```



---

