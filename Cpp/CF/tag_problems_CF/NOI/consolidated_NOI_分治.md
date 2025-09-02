---
title: "Freezing with Style"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF150E
tag: ['点分治', '单调队列', '分治']
---

# Freezing with Style

## 题目描述

This winter is so... well, you've got the idea :-) The Nvodsk road system can be represented as $ n $ junctions connected with $ n-1 $ bidirectional roads so that there is a path between any two junctions. The organizers of some event want to choose a place to accommodate the participants (junction $ v $ ), and the place to set up the contests (junction $ u $ ). Besides, at the one hand, they want the participants to walk about the city and see the neighbourhood (that's why the distance between $ v $ and $ u $ should be no less than $ l $ ). On the other hand, they don't want the participants to freeze (so the distance between $ v $ and $ u $ should be no more than $ r $ ). Besides, for every street we know its beauty — some integer from $ 0 $ to $ 10^{9} $ . Your task is to choose the path that fits in the length limits and has the largest average beauty. We shall define the average beauty as a median of sequence of the beauties of all roads along the path.

We can put it more formally like that: let there be a path with the length $ k $ . Let $ a_{i} $ be a non-decreasing sequence that contains exactly $ k $ elements. Each number occurs there exactly the number of times a road with such beauty occurs along on path. We will represent the path median as number $ a_{⌊k/2⌋} $ , assuming that indexation starting from zero is used. $ ⌊x⌋ $ — is number $ х $ , rounded down to the nearest integer.

For example, if $ a={0,5,12} $ , then the median equals to $ 5 $ , and if $ a={0,5,7,12} $ , then the median is number $ 7 $ .

It is guaranteed that there will be at least one path with the suitable quantity of roads.

## 输入格式

The first line contains three integers $ n $ , $ l $ , $ r $ ( $ 1\le l\le r,n\le 10^{5} $ ).

Next $ n-1 $ lines contain descriptions of roads of the Nvodsk, each line contains three integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ 0<=c_{i}<=10^{9} $ , $ a_{i}≠b_{i} $ ) — junctions $ a_{i} $ and $ b_{i} $ are connected with a street whose beauty equals $ c_{i} $ .

## 输出格式

Print two integers — numbers of the junctions, where to accommodate the participants and set up the contests, correspondingly. If there are multiple optimal variants, print any of them.

## 说明/提示

In the first sample all roads have the same beauty. That means that all paths of the positive length have the same median. Thus, any path with length from $ 3 $ to $ 4 $ , inclusive will be valid for us.

In the second sample the city looks like that: 1 - 2 - 3 - 4 - 5 - 6. Two last roads are more valuable and we should choose any path that contains both of them and has the suitable length. It is either the path between $ 2 $ and $ 6 $ or the path between $ 3 $ and $ 6 $ .

## 样例 #1

### 输入

```
6 3 4
1 2 1
2 3 1
3 4 1
4 5 1
5 6 1

```

### 输出

```
4 1

```

## 样例 #2

### 输入

```
6 3 4
1 2 1
2 3 1
3 4 1
4 5 2
5 6 2

```

### 输出

```
6 3

```

## 样例 #3

### 输入

```
5 1 4
1 2 1
1 3 4
3 4 7
3 5 2

```

### 输出

```
4 3

```

## 样例 #4

### 输入

```
8 3 6
1 2 9
2 3 7
3 4 7
4 5 8
5 8 2
3 6 3
2 7 4

```

### 输出

```
5 1

```



---

---
title: "Problems for Codeforces"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1580F
tag: ['分治', '快速傅里叶变换 FFT']
---

# Problems for Codeforces

## 题目描述

XYMXYM 与 CQXYM 将为 Codeforces 准备 $n$ 个题目。第 $i$ 个题目的难度为整数 $a_i$ 且 $a_i\geq 0$。所有题目的难度必须满足 $a_i+a_{i+1}\lt m\,\space(1\leq i\lt n)$ 且 $a_1+a_n\lt m$，其中 $m$ 为一个固定整数。XYMXYM 想知道题目难度有多少种可能的方案，结果对 $998244353$ 取模。

两种题目难度的方案 $a$ 和 $b$ 是不同的当且仅当存在一个整数 $i,\space (1\leq i\leq n)$ 满足 $a_i\neq b_i$。

## 输入格式

一行包含两个整数 $n$ 和 $m$ $(2\leq n\leq 50\,000,1\leq m\leq 10^9)$。

## 输出格式

输出一个整数为方案数，对 $998244353$ 取模。

## 说明/提示

在第一个样例中，合法的方案为 $[0,0,0],[0,0,1],[0,1,0],[1,0,0]$，而 $[1,0,1]$ 不合法因为 $a_1+a_n\geq m$。

## 样例 #1

### 输入

```
3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 9
```

### 输出

```
8105
```

## 样例 #3

### 输入

```
21038 3942834
```

### 输出

```
338529212
```



---

---
title: "Hard Cut"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1684H
tag: ['数学', '分治']
---

# Hard Cut

## 题目描述

给定一个 `01` 字符串 $s$。  
你需要对其进行划分，使得最终把每一段当做二进制数加起来后得到的数是 $2$ 的幂。  
有解输出任意一组解，无解输出 `-1`。

## 输入格式

第一行输入一个整数 $t(1\leq t\leq10^5)$ 表示数据组数。接下来对于每组数据：  
输入一行一个 `01` 字符串 $s(1\leq |s|,\sum |s|\leq10^6)$。

## 输出格式

对于每组数据：    
如果无解，输出 `-1`。  
否则，首先输出一行一个整数 $k$ 表示划分的子段数。  
接下来输出 $k$ 行，第 $i$ 行两个整数 $l_i,r_i(1\leq l_i\leq r_i\leq n)$ 表示你划分出的子段。  
你划分的子段应该两两不相交，且包含 $s$ 中的每个字符。

### 样例解释

对于第二组数据，样例将 $\texttt{"01101"}$ 划分成了 $\texttt{"011","0","1"}$。  
因为 $(011)_2+(0)_2+(1)_2=3+0+1=4=2^2$，因此满足要求。

## 样例 #1

### 输入

```
4
00000
01101
0111011001011
000111100111110
```

### 输出

```
-1

3
1 3
4 4
5 5

8
1 2
3 3
4 4
5 6
7 7
8 10
11 12
13 13

5
1 5
6 7
8 11
12 14
15 15
```



---

---
title: "Optimizations From Chelsu"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1916G
tag: ['点分治']
---

# Optimizations From Chelsu

## 题目描述

You are given a tree with $ n $ vertices, whose vertices are numbered from $ 1 $ to $ n $ . Each edge is labeled with some integer $ w_i $ .

Define $ len(u, v) $ as the number of edges in the simple path between vertices $ u $ and $ v $ , and $ gcd(u, v) $ as the Greatest Common Divisor of all numbers written on the edges of the simple path between vertices $ u $ and $ v $ . For example, $ len(u, u) = 0 $ and $ gcd(u, u) = 0 $ for any $ 1 \leq u \leq n $ .

You need to find the maximum value of $ len(u, v) \cdot gcd(u, v) $ over all pairs of vertices in the tree.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. This is followed by their description.

The first line of each test case contains the number $ n $ ( $ 2 \leq n \leq 10^5 $ ) — the number of vertices in the tree.

The next $ n-1 $ lines specify the edges in the format $ u $ , $ v $ , $ w $ ( $ 1 \leq u, v \leq n $ , $ 1 \leq w \leq 10^{12} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single number equal to the maximum value of $ len(u, v) \cdot gcd(u, v) $ over all pairs of vertices in the tree.

## 样例 #1

### 输入

```
4
2
1 2 1000000000000
4
3 2 6
2 1 10
2 4 6
8
1 2 12
2 3 9
3 4 9
4 5 6
5 6 12
6 7 4
7 8 9
12
1 2 12
2 3 12
2 4 6
2 5 9
5 6 6
1 7 4
4 8 12
8 9 4
8 10 12
2 11 9
7 12 9
```

### 输出

```
1000000000000
12
18
24
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
title: "Complex Segments (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2018E1
tag: ['贪心', '根号分治']
---

# Complex Segments (Easy Version)

## 题目描述

这是这个问题的简单版本。在这个版本中， $n$ 的范围和时间限制都较低。

当一个区间的集合可以被分割成一些子集并满足以下条件时，这个集合是复杂的：

- 所有的子集的大小相同
- 当且仅当两个区间在同一子集内时，这两个区间相交。

$t$ 组数据，每组数据给你一个集合包含 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]$。求出最大的子集满足其为复杂的，输出这个集合的大小。

## 输入格式

第一行输入数据个数 $t(1 \le t \le 10^3)$。

每个数据的第一行包含一个整数 $n(1 \le n \le 2 \cdot 10^4)$，集合的区间个数。

每个数据的第二行包含 $n$ 个整数 $l_1, l_2, \ldots, l_n(1 \le l_i \le 2n)$，分别表示这 $n$ 个区间的左端点。

每个数据的第三行包含 $n$ 个整数 $r_1, r_2, \ldots, r_n(l_i \leq r_i \le 2n)$，分别表示这 $n$ 个区间的右端点。

保证所有数据 $n$ 的总和不超过 $2 \cdot 10^4$。

## 输出格式

对于每个数据输出一行表示最大的复杂的子集的大小。

## 样例 #1

### 输入

```
3
3
1 2 3
5 4 6
5
1 2 3 6 8
5 4 7 9 10
5
3 1 4 1 5
7 2 6 5 10
```

### 输出

```
3
4
4
```



---

---
title: "Complex Segments (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2018E2
tag: ['贪心', '分治']
---

# Complex Segments (Hard Version)

## 题目描述

这是这个问题的困难版本。在这个版本中， $n$ 的范围和时间限制都变高了。

当一个区间的集合可以被分割成一些子集并满足以下条件时，这个集合是复杂的：

- 所有的子集的大小相同
- 当且仅当两个区间在同一子集内时，这两个区间相交。

$t$ 组数据，每组数据给你一个集合包含 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]$。求出最大的子集满足其为复杂的，输出这个集合的大小。

## 输入格式

第一行输入数据个数 $t(1 \le t \le 10^3)$。

每个数据的第一行包含一个整数 $n(1 \le n \le 3 \cdot 10^5)$，集合的区间个数。

每个数据的第二行包含 $n$ 个整数 $l_1, l_2, \ldots, l_n(1 \le l_i \le 2n)$，分别表示这 $n$ 个区间的左端点。

每个数据的第三行包含 $n$ 个整数 $r_1, r_2, \ldots, r_n(l_i \leq r_i \le 2n)$，分别表示这 $n$ 个区间的右端点。

保证所有数据 $n$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个数据输出一行表示最大的复杂的子集的大小。

## 样例 #1

### 输入

```
3
3
1 2 3
5 4 6
5
1 2 3 6 8
5 4 7 9 10
5
3 1 4 1 5
7 2 6 5 10
```

### 输出

```
3
4
4
```



---

---
title: "Furukawa Nagisa's Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF434E
tag: ['点分治', '素数判断,质数,筛法', '逆元']
---

# Furukawa Nagisa's Tree

## 题目背景

有一天冈崎朋也和送给古河渚一棵树作为渚的生日礼物。（因为渚的生日是 12.24 啊~）。这是一棵奇奇怪怪的树，每一个节点都有一个权值 $v_i$。现在渚和朋也想在这棵树上玩一个游戏。


设 $ (s,e) $ 为从节点  $s$ 到节点 $e$ 的路径，我们可以写下路径 $ (s,e) $ 上的节点值序列，并将此序列表示为 $ S(s,e) $。  
可爱的渚这样定义了一个序列的权值： $G(S(s,e)) $。假设这个序列是 $ z_{0},z_{1}...z_{l-1} $，此处 $ l $ 是序列长度，定义 $ G(S(s,e))=z_{0}\times k^{0}+z_{1}\times k^{1} + \cdots + z_{l-1} \times k^{l-1} $。  
如果这条序列满足 $G(S(s, e)) \equiv x \pmod y$，那么这条路径 $ (s,e) $ 属于古河渚，反之属于冈崎朋也。


渚觉得计算谁拥有更多的路径实在是太简单了，所以她想要尝试一些难一点的。渚认为如果路径 $ (p_{1},p_{2}) $ 和 $ (p_{2},p_{3}) $ 属于她，那么$ (p_{1},p_{3}) $ 的路径也会属于她。同理，如果路径 $ (p_{1},p_{2}) $ 和 $ (p_{2},p_{3}) $ 属于朋也，那么路径 $ (p_{1},p_{3}) $ 也属于朋也。但是实际上，渚的这一结论并不是一直都是正确的。渚现在想知道有多少三元组 $ (p_{1},p_{2},p_{3}) $ 满足她的结论，这就是你的任务啦！


翻译者：永远喜欢 Furukawa Nagisa 的 zcysky。

## 题目描述

One day, Okazaki Tomoya has bought a tree for Furukawa Nagisa's birthday. The tree is so strange that every node of the tree has a value. The value of the $ i $ -th node is $ v_{i} $ . Now Furukawa Nagisa and Okazaki Tomoya want to play a game on the tree.

Let $ (s,e) $ be the path from node $ s $ to node $ e $ , we can write down the sequence of the values of nodes on path $ (s,e) $ , and denote this sequence as $ S(s,e) $ . We define the value of the sequence $ G(S(s,e)) $ as follows. Suppose that the sequence is $ z_{0},z_{1}...z_{l-1} $ , where $ l $ is the length of the sequence. We define $ G(S(s,e))=z_{0}×k^{0}+z_{1}×k^{1}+...+z_{l-1}×k^{l-1} $ . If the path $ (s,e) $ satisfies ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF434E/90c086b3cd66d72f064774200cc642323d3ee403.png), then the path $ (s,e) $ belongs to Furukawa Nagisa, otherwise it belongs to Okazaki Tomoya.

Calculating who has more paths is too easy, so they want to play something more difficult. Furukawa Nagisa thinks that if paths $ (p_{1},p_{2}) $ and $ (p_{2},p_{3}) $ belong to her, then path $ (p_{1},p_{3}) $ belongs to her as well. Also, she thinks that if paths $ (p_{1},p_{2}) $ and $ (p_{2},p_{3}) $ belong to Okazaki Tomoya, then path $ (p_{1},p_{3}) $ belongs to Okazaki Tomoya as well. But in fact, this conclusion isn't always right. So now Furukawa Nagisa wants to know how many triplets $ (p_{1},p_{2},p_{3}) $ are correct for the conclusion, and this is your task.

## 输入格式

The first line contains four integers $ n $ , $ y $ , $ k $ and $ x (1<=n<=10^{5}; 2<=y<=10^{9}; 1<=k&lt;y; 0<=x&lt;y) $ — $ n $ being the number of nodes on the tree. It is guaranteed that $ y $ is a prime number.

The second line contains $ n $ integers, the $ i $ -th integer is $ v_{i} (0<=v_{i}&lt;y) $ .

Then follow $ n-1 $ lines, each line contains two integers, denoting an edge of the tree. The nodes of the tree are numbered from 1 to $ n $ .

## 输出格式

Output a single integer — the number of triplets that are correct for Furukawa Nagisa's conclusion.

## 样例 #1

### 输入

```
1 2 1 0
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 5 2 1
4 3 1
1 2
2 3

```

### 输出

```
14

```

## 样例 #3

### 输入

```
8 13 8 12
0 12 7 4 12 0 8 12
1 8
8 4
4 6
6 2
2 3
8 5
2 7

```

### 输出

```
341

```



---

