---
title: "Vasya and Robot"
layout: "post"
diff: 普及+/提高
pid: CF1073C
tag: ['二分', '枚举', '前缀和']
---

# Vasya and Robot

## 题目描述

Vasya has got a robot which is situated on an infinite Cartesian plane, initially in the cell $ (0, 0) $ . Robot can perform the following four kinds of operations:

- U — move from $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from $ (x, y) $ to $ (x + 1, y) $ .

Vasya also has got a sequence of $ n $ operations. Vasya wants to modify this sequence so after performing it the robot will end up in $ (x, y) $ .

Vasya wants to change the sequence so the length of changed subsegment is minimum possible. This length can be calculated as follows: $ maxID - minID + 1 $ , where $ maxID $ is the maximum index of a changed operation, and $ minID $ is the minimum index of a changed operation. For example, if Vasya changes RRRRRRR to RLRRLRL, then the operations with indices $ 2 $ , $ 5 $ and $ 7 $ are changed, so the length of changed subsegment is $ 7 - 2 + 1 = 6 $ . Another example: if Vasya changes DDDD to DDRD, then the length of changed subsegment is $ 1 $ .

If there are no changes, then the length of changed subsegment is $ 0 $ . Changing an operation means replacing it with some operation (possibly the same); Vasya can't insert new operations into the sequence or remove them.

Help Vasya! Tell him the minimum length of subsegment that he needs to change so that the robot will go from $ (0, 0) $ to $ (x, y) $ , or tell him that it's impossible.

## 输入格式

The first line contains one integer number $ n~(1 \le n \le 2 \cdot 10^5) $ — the number of operations.

The second line contains the sequence of operations — a string of $ n $ characters. Each character is either U, D, L or R.

The third line contains two integers $ x, y~(-10^9 \le x, y \le 10^9) $ — the coordinates of the cell where the robot should end its path.

## 输出格式

Print one integer — the minimum possible length of subsegment that can be changed so the resulting sequence of operations moves the robot from $ (0, 0) $ to $ (x, y) $ . If this change is impossible, print $ -1 $ .

## 说明/提示

In the first example the sequence can be changed to LULUU. So the length of the changed subsegment is $ 3 - 1 + 1 = 3 $ .

In the second example the given sequence already leads the robot to $ (x, y) $ , so the length of the changed subsegment is $ 0 $ .

In the third example the robot can't end his path in the cell $ (x, y) $ .

## 样例 #1

### 输入

```
5
RURUU
-2 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
RULR
1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
UUU
100 100

```

### 输出

```
-1

```



---

---
title: "Creative Snap"
layout: "post"
diff: 普及+/提高
pid: CF1111C
tag: ['二分', '递归', '剪枝']
---

# Creative Snap

## 题目描述

灭霸要摧毁复仇者们的基地！  

我们可以将复仇者的基地看成一个序列，每个位置都有可能有多个复仇者；但是每个复仇者只能占据一个位置。  
他们基地的长度刚好是$2$的整数幂，灭霸想要用最少的能量摧毁它们。他在摧毁过程中，可以选择：  
- 如果这段基地长度$\ge 2$，他可以将其分为相等长度的两半。  
- 烧掉这段基地。如果这段基地中没有复仇者，他需要消耗$A$的能量；如果有，则需要消耗$B*x*l$的能量。其中$l$是这段基地长度，$x$是这段中的复仇者数量。  

输出一个整数，表示他摧毁全部基地需要的最少能量。  
接下来一行$k$个整数，$a_i$表示第$i$个复仇者所在的位置

## 输出格式

一个整数，表示摧毁基地所需要的最少能量。

## 说明/提示

### 样例解释  
对于样例1，直接烧区间$[1,4]$需要能量为$4*2*2=16$。  
但是，如果将其分为$4$段，分别烧掉，所需能量只有$2+1+2+1=6$。  
可以证明没有更优的方案，所以输出`6`。 
对于全部数据：  
$1\le n \le 30$  
$1\le k \le 10^5$  
$1\le A,B \le 10^4$  
$1\le a_i \le 2^n$

## 样例 #1

### 输入

```
2 2 1 2
1 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3 2 1 2
1 7

```

### 输出

```
8

```



---

---
title: "Microtransactions (hard version)"
layout: "post"
diff: 普及+/提高
pid: CF1165F2
tag: ['贪心', '二分']
---

# Microtransactions (hard version)

## 题目描述

有 $n$ 种物品，对于第 $i$ $(1\le i \le n)$ 个物品，你需要买 $k_i$ 个（你每次购物是在**晚上**），每个物品在非打折日买是 $2$ 块钱，在打折日买是 $1$ 块钱，每天**早上**你可以赚 $1$ 块钱，一共有 $m$ 个打折日，在第 $d_i$ 天第 $t_i$ 种物品打折，问最少需要多少天可以买完你需要的物品。注意，你每天可以买任意多数量以及种类的商品（只要你有足够的余额）。

## 输入格式

第一行包含两个整数 $n$ 和 $m$ $(1\le n,m \le 2\times 10^5)$ 中的商品类型数和打折的天数。

输入的第二行包含 $n$ 个整数 $k_i$，其中 $k_i$ 是第 $i$ 类需要的个数。$(0 \le \sum k_i \le 2\times 10^5)$。

接下来的 $m$ 行，每行两个数 $(d_i,t_i$) $(1 \le d_i \le 2\times 10^5, 1 \le t_i \le n)$，表示第 $t_i$ 个商品在 $d_i$ 天打特价。

## 输出格式

一个整数，表示最早在哪一天能买完所有需要的商品。

## 样例 #1

### 输入

```
5 6
1 2 0 2 0
2 4
3 3
1 5
1 2
1 5
2 3

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5 3
4 2 1 3 2
3 5
4 2
2 5

```

### 输出

```
20

```



---

---
title: "Electrification"
layout: "post"
diff: 普及+/提高
pid: CF1175C
tag: ['数学', '二分']
---

# Electrification

## 题目描述

At first, there was a legend related to the name of the problem, but now it's just a formal statement.

You are given $ n $ points $ a_1, a_2, \dots, a_n $ on the $ OX $ axis. Now you are asked to find such an integer point $ x $ on $ OX $ axis that $ f_k(x) $ is minimal possible.

The function $ f_k(x) $ can be described in the following way:

- form a list of distances $ d_1, d_2, \dots, d_n $ where $ d_i = |a_i - x| $ (distance between $ a_i $ and $ x $ );
- sort list $ d $ in non-descending order;
- take $ d_{k + 1} $ as a result.

If there are multiple optimal answers you can print any of them.

## 输入格式

The first line contains single integer $ T $ ( $  1 \le T \le 2 \cdot 10^5 $ ) — number of queries. Next $ 2 \cdot T $ lines contain descriptions of queries. All queries are independent.

The first line of each query contains two integers $ n $ , $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le k < n $ ) — the number of points and constant $ k $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_1 < a_2 < \dots < a_n \le 10^9 $ ) — points in ascending order.

It's guaranteed that $ \sum{n} $ doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

Print $ T $ integers — corresponding points $ x $ which have minimal possible value of $ f_k(x) $ . If there are multiple answers you can print any of them.

## 样例 #1

### 输入

```
3
3 2
1 2 5
2 1
1 1000000000
1 0
4

```

### 输出

```
3
500000000
4

```



---

---
title: "The Parade"
layout: "post"
diff: 普及+/提高
pid: CF1250J
tag: ['贪心', '二分']
---

# The Parade

## 题目描述

**题意简述**

柏林军队正在准备一场大规模的阅兵式。参加的士兵将被分成人数相等的$k$行。

当然，排兵布阵是需要一定的规则的：同一排士兵的身高相差不应超过$1$且每个士兵的身高是$1$到$n$之间的整数。

已知每名士兵身高的你必须将所有参加阅兵的士兵排成$k$排，以满足上述条件。请你编写程序计算可以参加游行的士兵的最大数量。

## 输入格式

本题**有多组数据**。

第一行包含一个整数$t(1\le t\le 10000)$，表示数据组数。

每组数据都有两行。第一行包含两个整数$n$和$k$（$1≤n≤30000$，$1≤k≤10^{12}$）分别表示不同高度的士兵数量和士兵排数。

第二行包含$n$个整数$c_1,c_2,$ … $,c_n$（$0\le c_i\le 10^{12}$），其中$c_i$表示身高为$i$的士兵人数。

## 输出格式

输出每组数据中可以参加游行的士兵的最大数量。（每两个答案中间有一个换行）

## 说明/提示

第一组数据，士兵可以站成这样：$[3,3,3,3],[1,2,1,1],[1,1,1,1],[3,3,3,3]$（每个方括号表示一行）；

第二组数据，所有士兵可以全部站成一排；

第三组数据，士兵可以站成$3$排，每排$33$人；

第四组数据，所有士兵可以全部站成一排；

第五组数据，所有身高为$2$和$3$的可以站成一排。

## 样例 #1

### 输入

```
5
3 4
7 1 13
1 1
100
1 3
100
2 1
1000000000000 1000000000000
4 1
10 2 11 1

```

### 输出

```
16
100
99
2000000000000
13

```



---

---
title: "New Year's Problem"
layout: "post"
diff: 普及+/提高
pid: CF1619D
tag: ['二分']
---

# New Year's Problem

## 题目描述

Vlad 有 $n$ 个朋友，每个朋友需要且仅需要 $1$ 个礼物。有 $m$ 家礼物商店，如果在第 $i$ 个商店中为朋友 $j$ 买礼物，朋友 $j$ 将获得 $p_{ij}$ 的快乐值。

由于时间紧迫， Vlad 最多只会在 $n-1$ 家不同的商店中买礼物。请你使每位朋友能获得的快乐值中的最小值最大。

## 输入格式

第一行一个整数 $t$，表示有 $t$ 组测试数据。

每组测试数据之间有一个空行。对于每组测试数据，第一行两个整数 $m$ 和 $n$。接下来 $m$ 行，每行 $n$ 个整数，其中第 $i$ 行的第 $j$ 个数表示 $p_{ij}$。

保证 $t\leq10^4$，$p_{ij}\leq10^9$，$n\geq2$，且所有测试数据中 $n\cdot m$ 的和不超过 $10^5$。

## 输出格式

输出 $t$ 行，每行包含对应测试数据的答案，即 Vlad 的朋友中最小快乐值的最大值。

## 样例 #1

### 输入

```
5

2 2
1 2
3 4

4 3
1 3 1
3 1 1
1 2 2
1 1 3

2 3
5 3 4
2 5 1

4 2
7 9
8 1
9 6
10 8

2 4
6 5 2 1
7 9 7 2
```

### 输出

```
3
2
4
8
2
```



---

---
title: "Tree Infection"
layout: "post"
diff: 普及+/提高
pid: CF1665C
tag: ['贪心', '二分']
---

# Tree Infection

## 题目描述

### 题意描述
一个树是一个无环连通图。一个有根树有一个被称作“根结点”的结点。对于任意一个非根结点 $v$ ，其父结点是从根结点到结点 $v$ 最短路径上的前一个结点。结点 $v$ 的子结点包括所有以 $v$ 父结点为 $v$ 的结点。

给定一个有 $n$ 个结点的有根树。结点 $1$ 即为根结点。一开始，该树上所有结点均是“健康”的。

每一秒你会进行两次操作——先是传播操作，然后是注射操作，定义如下。

- 传播操作：对于每个结点 $v$ ，若该结点至少有一个子结点被“感染”，则你可以“感染”顶点 $v$ 任意一个其他的子结点。
- 注射：你可以选择任意一个“健康”的结点并使它变为“感染”状态。

这程每秒会重复一次知道整个树的结点都处于“感染”状态。你需要找到使整个树被“感染”的最短时间（秒数）。

## 输入格式

有多个测试数据。第一行输入整数 $t$ ，代表有 $t$ 组数据。每组数据格式如下。

第一行给定整数 $n$ ，表示整个树共有 $n$ 个结点。

第二行输入 $n-1$ 个整数 $p_{2...i-1}$ ，第 $p_i$ 个整数表示 $i$ 号结点的父节点是 $p_i$ 号结点。

## 输出格式

共 $t$ 行，每行一个整数，即使整个树被“感染”的最短时间（秒数）。

## 说明/提示

- $ 1 \le t \le 10^4 $
- $ 2 \le n \le 2 \times 10^5 $
- $ 1 \le p_i \le n $
- $ \sum \limits_{i=1} ^t n_i \le 2 \times 10^5 $

## 样例 #1

### 输入

```
5
7
1 1 1 2 2 4
5
5 5 1 4
2
1
3
3 1
6
1 1 1 1 1
```

### 输出

```
4
4
2
3
4
```



---

---
title: "Toss a Coin to Your Graph..."
layout: "post"
diff: 普及+/提高
pid: CF1679D
tag: ['二分', '拓扑排序']
---

# Toss a Coin to Your Graph...

## 题目描述

One day Masha was walking in the park and found a graph under a tree... Surprised? Did you think that this problem would have some logical and reasoned story? No way! So, the problem...

Masha has an oriented graph which $ i $ -th vertex contains some positive integer $ a_i $ . Initially Masha can put a coin at some vertex. In one operation she can move a coin placed in some vertex $ u $ to any other vertex $ v $ such that there is an oriented edge $ u \to v $ in the graph. Each time when the coin is placed in some vertex $ i $ , Masha write down an integer $ a_i $ in her notebook (in particular, when Masha initially puts a coin at some vertex, she writes an integer written at this vertex in her notebook). Masha wants to make exactly $ k - 1 $ operations in such way that the maximum number written in her notebook is as small as possible.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le m \le 2 \cdot 10^5 $ , $ 1 \le k \le 10^{18} $ ) — the number of vertices and edges in the graph, and the number of operation that Masha should make.

The second line contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 10^9 $ ) — the numbers written in graph vertices.

Each of the following $ m $ lines contains two integers $ u $ and $ v $ ( $ 1 \le u \ne v \le n $ ) — it means that there is an edge $ u \to v $ in the graph.

It's guaranteed that graph doesn't contain loops and multi-edges.

## 输出格式

Print one integer — the minimum value of the maximum number that Masha wrote in her notebook during optimal coin movements.

If Masha won't be able to perform $ k - 1 $ operations, print $ -1 $ .

## 说明/提示

Graph described in the first and the second examples is illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679D/f21a10b2a32ca5315b6d3233f4e3f1d967d3f865.png)In the first example Masha can initially put a coin at vertex $ 1 $ . After that she can perform three operations: $ 1 \to 3 $ , $ 3 \to 4 $ and $ 4 \to 5 $ . Integers $ 1, 2, 3 $ and $ 4 $ will be written in the notepad.

In the second example Masha can initially put a coin at vertex $ 2 $ . After that she can perform $ 99 $ operations: $ 2 \to 5 $ , $ 5 \to 6 $ , $ 6 \to 2 $ , $ 2 \to 5 $ , and so on. Integers $ 10, 4, 5, 10, 4, 5, \ldots, 10, 4, 5, 10 $ will be written in the notepad.

In the third example Masha won't be able to perform $ 4 $ operations.

## 样例 #1

### 输入

```
6 7 4
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 7 100
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5
```

### 输出

```
10
```

## 样例 #3

### 输入

```
2 1 5
1 1
1 2
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
1 0 1
1000000000
```

### 输出

```
1000000000
```



---

---
title: "Guess The String"
layout: "post"
diff: 普及+/提高
pid: CF1697D
tag: ['二分', '构造']
---

# Guess The String

## 题目描述

This is an interactive problem. Remember to flush your output while communicating with the testing program. You may use fflush(stdout) in C++, system.out.flush() in Java, stdout.flush() in Python or flush(output) in Pascal to flush the output. If you use some other programming language, consult its documentation. You may also refer to the guide on interactive problems: <https://codeforces.com/blog/entry/45307>.

The jury has chosen a string $ s $ consisting of $ n $ characters; each character of $ s $ is a lowercase Latin letter. Your task is to guess this string; initially, you know only its length.

You may ask queries of two types:

- $ 1 $ $ i $ — the query of the first type, where $ i $ is an integer from $ 1 $ to $ n $ . In response to this query, the jury will tell you the character $ s_i $ ;
- $ 2 $ $ l $ $ r $ — the query of the second type, where $ l $ and $ r $ are integers such that $ 1 \le l \le r \le n $ . In response to this query, the jury will tell you the number of different characters among $ s_l, s_{l+1}, \dots, s_r $ .

You are allowed to ask no more than $ 26 $ queries of the first type, and no more than $ 6000 $ queries of the second type. Your task is to restore the string $ s $ .

For each test in this problem, the string $ s $ is fixed beforehand, and will be the same for every submission.

## 输入格式

Initially, the jury program sends one integer $ n $ on a separate line — the size of $ s $ ( $ 1 \le n \le 1000 $ ).

## 输出格式

To give the answer, print one line ! s with a line break in the end, where $ s $ should be the string picked by the jury. After that, your program should flush the output and terminate gracefully.

Interaction

To ask a query, you should send one line containing the query, in one of the following formats:

- ? 1 i — for a query of the first type ( $ 1 \le i \le n $ );
- ? 2 l r — for a query of the second type ( $ 1 \le l \le r \le n $ ).

Don't forget to flush the output after sending the query line.

The answer to your query will be given on a separate line. For a query of the first type, the answer will be the character $ s_i $ . For a query of the second type, the answer will be an integer equal to the number of different characters among $ s_l, s_{l+1}, \dots, s_r $ .

You are allowed to ask no more than $ 26 $ queries of the first type, and no more than $ 6000 $ queries of the second type.

In case you ask too many queries, or the jury program fails to recognize your query format, the answer to your query will be one integer $ 0 $ . After receiving $ 0 $ as the answer, your program should terminate immediately — otherwise you may receive verdict "Runtime error", "Time limit exceeded" or some other verdict instead of "Wrong answer".

## 说明/提示

Let's analyze the example of interaction.

The string chosen by the jury is guess, so initially the jury sends one integer $ 5 $ .

1. the first query is ? 2 1 5, which means "count the number of different characters among $ s_1, s_2, \dots, s_5 $ ". The answer to it is $ 4 $ .
2. the second query is ? 1 2, which means "tell which character is $ s_2 $ ". The answer to it is u.
3. the third query is ? 2 1 2, which means "count the number of different characters among $ s_1 $ and $ s_2 $ ". The answer to it is $ 2 $ .
4. the fourth query is ? 1 1, which means "tell which character is $ s_1 $ ". The answer to it is g.
5. the fifth query is ? 1 3, which means "tell which character is $ s_3 $ ". The answer to it is e.
6. the sixth query is ? 1 4, which means "tell which character is $ s_4 $ ". The answer to it is s.
7. the seventh query is ? 2 4 5, which means "count the number of different characters among $ s_4 $ and $ s_5 $ ". The answer to it is $ 1 $ , so it's possible to deduce that $ s_4 $ is the same as $ s_5 $ .

In the end, the answer is submitted as ! guess, and it is deduced correctly.

## 样例 #1

### 输入

```
5
4
u
2
g
e
s
1
```

### 输出

```
? 2 1 5
? 1 2
? 2 1 2
? 1 1
? 1 3
? 1 4
? 2 4 5
! guess
```



---

---
title: "Doremy's IQ"
layout: "post"
diff: 普及+/提高
pid: CF1707A
tag: ['贪心', '二分']
---

# Doremy's IQ

## 题目描述

哆来咪·苏伊特参加了 $n$ 场比赛。 比赛 $i$ 只能在第 $i$ 天进行。比赛 $i$ 的难度为 $a_i$。最初，哆来咪的 IQ 为 $q$ 。 在第 $i$ 天，哆来咪将选择是否参加比赛 i。只有当她当前的 IQ 大于 $0$ 时，她才能参加比赛。

如果哆来咪选择在第 $i$ 天参加比赛 $i$，则会发生以下情况：
- 如果 $a_i>q$，哆来咪会觉得自己不够聪明，所以 $q$ 将会减 $1$；
- 否则，什么都不会改变。

如果她选择不参加比赛，一切都不会改变。哆来咪想参加尽可能多的比赛。请给哆来咪一个解决方案。

## 输入格式

第一行包含一个正整数 $t$ ($1\le t\le10^4$) ，表示测试数据的组数。

第二行包含两个整数 $n$ 和 $q$ ($1\le n\le10^5$, $1\le q\le10^9$)，表示比赛次数和哆来咪最开始时的 IQ。

第三行包含 $n$ 个整数 $a_1,a_2⋯a_n$($1\le a_i≤10^9$)，表示每场比赛的难度。

数据保证 $n$ 之和不超过 $10^5$。

## 输出格式

对于每组数据，输出一个二进制字符串 $s$，如果哆来咪应该选择参加比赛 $i$，则 $s_i=1$，否则 $s_i=0$。 字符串中 $1$ 的数量应该尽可能的多，并且当她的 IQ 为 $0$ 或更低时，她不应该参加比赛。

如果有多个解决方案，你可以输出任意一个。

## 说明/提示

在第一个测试用例中，哆来咪参加了唯一的比赛。她的 IQ 没有下降。

在第二个测试用例中，哆来咪参加了两个比赛。在参加比赛 $2$ 后，她的 IQ 下降了 $1$。

在第三个测试用例中，哆来咪参加了比赛 $1$ 和比赛 $2$。她的 IQ 在参加比赛 $2$ 后降至 $0$，因此她无法参加比赛 $3$。

## 样例 #1

### 输入

```
5
1 1
1
2 1
1 2
3 1
1 2 1
4 2
1 4 3 1
5 2
5 1 2 4 3
```

### 输出

```
1
11
110
1110
01111
```



---

---
title: "Empty Graph"
layout: "post"
diff: 普及+/提高
pid: CF1712D
tag: ['贪心', '二分']
---

# Empty Graph

## 题目描述

— Do you have a wish?



 — I want people to stop gifting each other arrays.

O_o and Another Young Boy



An array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ fell down on you from the skies, along with a positive integer $ k \le n $ .

You can apply the following operation at most $ k $ times:

- Choose an index $ 1 \le i \le n $ and an integer $ 1 \le x \le 10^9 $ . Then do $ a_i := x $ (assign $ x $ to $ a_i $ ).

Then build a [complete](https://en.wikipedia.org/wiki/Complete_graph) undirected weighted graph with $ n $ vertices numbered with integers from $ 1 $ to $ n $ , where edge $ (l, r) $ ( $ 1 \le l < r \le n $ ) has weight $ \min(a_{l},a_{l+1},\ldots,a_{r}) $ .

You have to find the maximum possible diameter of the resulting graph after performing at most $ k $ operations.

The diameter of a graph is equal to $ \max\limits_{1 \le u < v \le n}{\operatorname{d}(u, v)} $ , where $ \operatorname{d}(u, v) $ is the length of the shortest path between vertex $ u $ and vertex $ v $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 2 \le n \le 10^5 $ , $ 1 \le k \le n $ ).

The second line of each test case contains $ n $ positive integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print one integer — the maximum possible diameter of the graph after performing at most $ k $ operations.

## 说明/提示

In the first test case, one of the optimal arrays is $ [2,4,5] $ .

The graph built on this array:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1712D/6f5937a14546fd0344ab2a7ad56768b75a98a230.png) $ \operatorname{d}(1, 2) = \operatorname{d}(1, 3) = 2 $ and $ \operatorname{d}(2, 3) = 4 $ , so the diameter is equal to $ \max(2,2,4) = 4 $ .

## 样例 #1

### 输入

```
6
3 1
2 4 1
3 2
1 9 84
3 1
10 2 6
3 2
179 17 1000000000
2 1
5 9
2 2
4 2
```

### 输出

```
4
168
10
1000000000
9
1000000000
```



---

---
title: "Path Prefixes"
layout: "post"
diff: 普及+/提高
pid: CF1714G
tag: ['倍增', '二分']
---

# Path Prefixes

## 题目描述

# Path Prefixes


现有一颗以 $1$ 为根的树，节点编号从 $1$ 到 $n$ .

每条边有两个权值，分别为 $a_j$ 和 $b_j$ .

输出 $n-1$ 个数 $r_2,r_3 \cdots ,r_n$ ，其中 $r_i$ 定义如下:

考虑从根节点( $1$ 号节点 ) 到第 $i$ 号节点 $(2 \le i \le n)$ 的路径，令沿该路径 $a_j$ 的花费为 $A_i$ ， $r_i$ 为该路径的最长前缀，使该前缀的 $b_j$ 之和不大于 $A_i$ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1714G/fb21910eda699947633b658de9a5b141ee71688b.png)

以 $n=9$ 时为例，如上图，蓝色数字表示 $a_j$ 的花费，红色数字表示 $b_j$ 的花费.

在这种情况下：

- $ r_2=0 $ ， 因为到节点 $ 2 $ 的路径中有 $ a_j=5 $  ， 只有前缀为 $ 0 $ 时才可能有较小（或相等）的 $ b_j $ ；
- $ r_3=3 $ ， 因为到节点 $ 3 $ 的路径中 $ a_j $ 为 $ 5+9+5=19 $ ， 长为 $ 3 $ 的前缀使 $ b_j $ 为 $ 6+10+1=17 $ ( $ 17 \le 19 $ 符合题意 )；
- $ r_4=1 $ ， 因为到节点 $ 4 $ 的路径中 $ a_j $ 为 $ 5+9=14 $ ， 长为 $ 1 $ 的前缀使 $ b_j $ 为 $ 6 $ (这是最长的符合题意的前缀， 因为长为 $ 2 $ 的前缀的 $ b_j $ 为 $ 6+10=16 $ ， 大于 $ 14 $ )；
- $ r_5=2 $ ， 因为到节点 $ 5 $ 的路径中 $ a_j $ 为 $ 5+9+2=16 $ ， 长为 $ 2 $ 的前缀使 $ b_j $ 为 $ 6+10=16 $ (这是最长的符合题意的前缀， 因为长为 $ 3 $ 的前缀的 $ b_j $ 为 $ 6+10+1=17 $ ， 比 $ 16 $ 大 )；
- $ r_6=1 $ ， 因为到节点 $ 6 $ 的路径中 $ a_j $ 为 $ 2 $ ， 长为 $ 1 $ 的前缀使 $ b_j $ 等于 $ 1 $ ；
- $ r_7=1 $ ， 因为到节点 $ 7 $ 的路径中 $ a_j $ 为 $ 5+3=8 $ ， 长为 $ 1 $ 的前缀使 $ b_j $ 等于 $ 6 $ (这是最长的符合题意的前缀， 因为长为 $ 2 $ 的前缀的 $ b_j $ 为 $ 6+3=9 $ ， 超出了期望的 $ 8 $ )；
- $ r_8=2 $ ， 因为到节点 $ 8 $ 的路径中 $ a_j $ 为 $ 2+4=6 $ ， 长为 $ 2 $ 的前缀使 $ b_j $ 为 $ 1+3=4 $ ；
- $ r_9=3 $ ， 因为到节点 $ 9 $ 的路径中 $ a_j $ 为 $ 2+4+1=7 $ ， 长为 $ 3 $ 的前缀使 $ b_j $ 为 $ 1+3+3=7 $ .


在第二组样例中

- $ r_2=0 $ ，因为到节点 $ 2 $ 的路径中 $ a_j $ 等于 $ 1 $ ， 只有前缀为 $ 0 $ 时才可能有较小（或相等）的 $ b_j $
- $ r_3=0 $ ， 因为到节点 $ 3 $ 的路径中 $ a_j $ 为 $ 1+1=2 $ ， 长为  $ 1 $ 的前缀使 $ b_j $ 等于 $ 100 $ ( $ 100 > 2 $ )；
- $ r_4=3 $ ， 因为到节点 $ 4 $ 的路径中 of $ a_j $ 为 $ 1+1+101=103 $ ， 长为 $ 3 $ 的前缀使 $ b_j $ 为 $ 102 $  .

## 输入格式

第一行有一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) 表示测试组数.

每组样例以一个整数 $ n $ ( $ 2 \le n \le 2\cdot10^5 $ ) 开始，表示这棵树的节点数.

接下来 $ n-1 $ 行，每行有三个整数  $ p_j， a_j， b_j $ ( $ 1 \le p_j \le n $ ; $ 1 \le a_j,b_j \le 10^9 $ ) 分别表示节点 $ j $ 的祖先和从 $ p_j $ 到 $ j $  的两个边权. 

 $ j $ 的值从 $ 2 $ 到 $ n $ . 输入数据保证生成的是一颗以 $ 1 $ 根的树，且 $ n $ 不超过 $ 2\cdot10^5 $ .

## 输出格式

对于每一组输入，输出一行 $ n-1 $ 个数: $ r_2, r_3, \dots , r_n $ .

## 样例 #1

### 样例输入 #1

```
4
9
1 5 6
4 5 1
2 9 10
4 2 1
1 2 1
2 3 3
6 4 3
8 1 3
4
1 1 100
2 1 1
3 101 1
4
1 100 1
2 1 1
3 1 101
10
1 1 4
2 3 5
2 5 1
3 4 3
3 1 5
5 3 5
5 2 1
1 3 2
6 2 1
```

### 样例输出 #1

```
0 3 1 2 1 1 2 3 
0 0 3 
1 2 2 
0 1 2 1 1 2 2 1 1
```

## 样例 #1

### 输入

```
4
9
1 5 6
4 5 1
2 9 10
4 2 1
1 2 1
2 3 3
6 4 3
8 1 3
4
1 1 100
2 1 1
3 101 1
4
1 100 1
2 1 1
3 1 101
10
1 1 4
2 3 5
2 5 1
3 4 3
3 1 5
5 3 5
5 2 1
1 3 2
6 2 1
```

### 输出

```
0 3 1 2 1 1 2 3 
0 0 3 
1 2 2 
0 1 2 1 1 2 2 1 1
```



---

---
title: "Valiant's New Map"
layout: "post"
diff: 普及+/提高
pid: CF1731D
tag: ['二分', '前缀和']
---

# Valiant's New Map

## 题目描述

Game studio "DbZ Games" wants to introduce another map in their popular game "Valiant". This time, the map named "Panvel" will be based on the city of Mumbai.

Mumbai can be represented as $ n \times m $ cellular grid. Each cell $ (i, j) $ ( $ 1 \le i \le n $ ; $ 1 \le j \le m $ ) of the grid is occupied by a cuboid building of height $ a_{i,j} $ .

This time, DbZ Games want to make a map that has perfect vertical gameplay. That's why they want to choose an $ l \times l $ square inside Mumbai, such that each building inside the square has a height of at least $ l $ .

Can you help DbZ Games find such a square of the maximum possible size $ l $ ?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 1000 $ ). Description of the test cases follows.

The first line of each test case contains two positive integers $ n $ and $ m $ ( $ 1 \le n \le m $ ; $ 1 \leq n \cdot m \leq 10^6 $ ).

The $ i $ -th of next $ n $ lines contains $ m $ integers $ a_{i,1}, a_{i,2}, \dots, a_{i,m} $ ( $ 1 \leq a_{i,j} \leq 10^6 $ ) — heights of buildings on the $ i $ -th row.

It's guaranteed that the sum of $ n \cdot m $ over all test cases doesn't exceed $ 10^6 $ .

## 输出格式

For each test case, print the maximum side length $ l $ of the square DbZ Games can choose.

## 说明/提示

In the first test case, we can choose the square of side $ l = 2 $ (i. e. the whole grid) since the heights of all buildings are greater than or equal to $ 2 $ .

In the second test case, we can only choose the side as $ 1 $ , so the answer is $ 1 $ .

In the third test case, there are no squares of size $ 2 $ that have all buildings of height at least $ 2 $ , so the answer is $ 1 $ .

## 样例 #1

### 输入

```
4
2 2
2 3
4 5
1 3
1 2 3
2 3
4 4 3
2 1 4
5 6
1 9 4 6 5 8
10 9 5 8 11 6
24 42 32 8 11 1
23 1 9 69 13 3
13 22 60 12 14 17
```

### 输出

```
2
1
1
3
```



---

---
title: "Slimes"
layout: "post"
diff: 普及+/提高
pid: CF1923D
tag: ['二分', '前缀和']
---

# Slimes

## 题目描述

There are $ n $ slimes placed in a line. The slimes are numbered from $ 1 $ to $ n $ in order from left to right. The size of the $ i $ -th slime is $ a_i $ .

Every second, the following happens: exactly one slime eats one of its neighbors and increases its size by the eaten neighbor's size. A slime can eat its neighbor only if it is strictly bigger than this neighbor. If there is no slime which is strictly bigger than one of its neighbors, the process ends.

For example, suppose $ n = 5 $ , $ a = [2, 2, 3, 1, 4] $ . The process can go as follows:

- first, the $ 3 $ -rd slime eats the $ 2 $ -nd slime. The size of the $ 3 $ -rd slime becomes $ 5 $ , the $ 2 $ -nd slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 1 $ -st slime (they are neighbors since the $ 2 $ -nd slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 7 $ , the $ 1 $ -st slime is eaten.
- then, the $ 5 $ -th slime eats the $ 4 $ -th slime. The size of the $ 5 $ -th slime becomes $ 5 $ , the $ 4 $ -th slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 5 $ -th slime (they are neighbors since the $ 4 $ -th slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 12 $ , the $ 5 $ -th slime is eaten.

For each slime, calculate the minimum number of seconds it takes for this slime to be eaten by another slime (among all possible ways the process can go), or report that it is impossible.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the number of slimes.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

The sum of $ n $ over all test cases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print $ n $ integers. The $ i $ -th integer should be equal to the minimum number of seconds it takes for the $ i $ -th slime to be eaten by another slime or -1 if it is impossible.

## 样例 #1

### 输入

```
4
4
3 2 4 2
3
1 2 3
5
2 2 3 1 1
7
4 2 3 6 1 1 8
```

### 输出

```
2 1 2 1 
1 1 -1 
2 1 -1 1 2 
2 1 1 3 1 1 4
```



---

---
title: "Rudolf and Imbalance"
layout: "post"
diff: 普及+/提高
pid: CF1941F
tag: ['贪心', '二分']
---

# Rudolf and Imbalance

## 题目描述

Rudolf has prepared a set of $ n $ problems with complexities $ a_1 < a_2 < a_3 < \dots < a_n $ . He is not entirely satisfied with the balance, so he wants to add at most one problem to fix it.

For this, Rudolf came up with $ m $ models of problems and $ k $ functions. The complexity of the $ i $ -th model is $ d_i $ , and the complexity of the $ j $ -th function is $ f_j $ . To create a problem, he selects values $ i $ and $ j $ ( $ 1 \le i \le m $ , $ 1 \le j \le k $ ) and by combining the $ i $ -th model with the $ j $ -th function, he obtains a new problem with complexity $ d_i + f_j $ (a new element is inserted into the array $ a $ ).

To determine the imbalance of the set, Rudolf sorts the complexities of the problems in ascending order and finds the largest value of $ a_i - a_{i - 1} $ ( $ i > 1 $ ).

What is the minimum value of imbalance that Rudolf can achieve by adding at most one problem, created according to the described rules?

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 2 \le n \le 10^5 $ , $ 1 \le m, k \le 2 \cdot 10^5 $ ) — the number of prepared problems, the number of models, and the number of functions, respectively.

The second line of each test case contains $ n $ integers $ a_1, a_2, a_3, \dots a_n $ ( $ 1 \le a_i \le 2 \cdot 10^9 $ , $ a_i < a_{i+1} $ ) — the complexities of the prepared problems.

The third line of each test case contains $ m $ integers $ d_1, d_2, d_3, \dots d_m $ ( $ 1 \le d_i \le 10^9 $ ) — the complexities of the models.

The fourth line of each test case contains $ k $ integers $ f_1, f_2, f_3, \dots f_k $ ( $ 1 \le f_i \le 10^9 $ ) — the complexities of the functions.

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 10^5 $ .

It is guaranteed that the sum of $ m $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

It is guaranteed that the sum of $ k $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, output a single number — the minimum imbalance that Rudolf can achieve.

## 样例 #1

### 输入

```
7
5 5 5
5 10 15 20 26
11 14 16 13 8
16 4 5 3 1
7 6 5
1 4 7 10 18 21 22
2 3 5 7 4 2
6 8 9 3 2
7 6 5
1 4 7 10 18 21 22
2 3 5 7 4 2
6 8 13 3 2
5 6 3
2 10 13 20 25
11 6 10 16 14 5
6 17 15
4 2 2
11 12 14 15
19 14
10 6
8 4 2
3 10 16 18 21 22 29 30
9 13 16 15
4 2
2 4 7
4 21
4 15 14 5
20 1 15 1 12 5 11
```

### 输出

```
5
4
5
8
2
7
11
```



---

---
title: "Binary Search"
layout: "post"
diff: 普及+/提高
pid: CF1945E
tag: ['二分', '构造']
---

# Binary Search

## 题目描述

Anton got bored during the hike and wanted to solve something. He asked Kirill if he had any new problems, and of course, Kirill had one.

You are given a permutation $ p $ of size $ n $ , and a number $ x $ that needs to be found. A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

You decided that you are a cool programmer, so you will use an advanced algorithm for the search — binary search. However, you forgot that for binary search, the array must be sorted.

You did not give up and decided to apply this algorithm anyway, and in order to get the correct answer, you can perform the following operation no more than $ 2 $ times before running the algorithm: choose the indices $ i $ , $ j $ ( $ 1\le i, j \le n $ ) and swap the elements at positions $ i $ and $ j $ .

After that, the binary search is performed. At the beginning of the algorithm, two variables $ l = 1 $ and $ r = n + 1 $ are declared. Then the following loop is executed:

1. If $ r - l = 1 $ , end the loop
2. $ m = \lfloor \frac{r + l}{2} \rfloor $
3. If $ p_m \le x $ , assign $ l = m $ , otherwise $ r = m $ .

The goal is to rearrange the numbers in the permutation before the algorithm so that after the algorithm is executed, $ p_l $ is equal to $ x $ . It can be shown that $ 2 $ operations are always sufficient.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 2\cdot 10^4 $ ) — the number of test cases. Then follow the descriptions of the test cases.

The first line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le x \le n \le 2\cdot 10^5 $ ) — the length of the permutation and the number to be found.

The second line contains the permutation $ p $ separated by spaces ( $ 1 \le p_i \le n $ ).

It is guaranteed that the sum of the values of $ n $ for all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output an integer $ k $ ( $ 0 \le k \le 2 $ ) on the first line — the number of operations performed by you. In the next $ k $ lines, output $ 2 $ integers $ i $ , $ j $ ( $ 1 \le i, j \le n $ ) separated by a space, indicating that you are swapping the elements at positions $ i $ and $ j $ .

Note that you do not need to minimize the number of operations.

## 样例 #1

### 输入

```
5
6 3
1 2 3 4 5 6
6 5
3 1 6 5 2 4
5 1
3 5 4 2 1
6 3
4 3 1 5 2 6
3 2
3 2 1
```

### 输出

```
0
1
3 4
2
2 4
1 5
2
4 5
2 4
1
1 3
```



---

---
title: "Division + LCP (easy version)"
layout: "post"
diff: 普及+/提高
pid: CF1968G1
tag: ['二分', '哈希 hashing']
---

# Division + LCP (easy version)

## 题目描述

This is the easy version of the problem. In this version $ l=r $ .

You are given a string $ s $ . For a fixed $ k $ , consider a division of $ s $ into exactly $ k $ continuous substrings $ w_1,\dots,w_k $ . Let $ f_k $ be the maximal possible $ LCP(w_1,\dots,w_k) $ among all divisions.

 $ LCP(w_1,\dots,w_m) $ is the length of the Longest Common Prefix of the strings $ w_1,\dots,w_m $ .

For example, if $ s=abababcab $ and $ k=4 $ , a possible division is $ \color{red}{ab}\color{blue}{ab}\color{orange}{abc}\color{green}{ab} $ . The $ LCP(\color{red}{ab},\color{blue}{ab},\color{orange}{abc},\color{green}{ab}) $ is $ 2 $ , since $ ab $ is the Longest Common Prefix of those four strings. Note that each substring consists of a continuous segment of characters and each character belongs to exactly one substring.

Your task is to find $ f_l,f_{l+1},\dots,f_r $ . In this version $ l=r $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ , $ l $ , $ r $ ( $ 1 \le l = r \le n \le 2 \cdot 10^5 $ ) — the length of the string and the given range.

The second line of each test case contains string $ s $ of length $ n $ , all characters are lowercase English letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output $ r-l+1 $ values: $ f_l,\dots,f_r $ .

## 说明/提示

In the first sample $ n=k $ , so the only division of $ aba $ is $ \color{red}a\color{blue}b\color{orange}a $ . The answer is zero, because those strings do not have a common prefix.

In the second sample, the only division is $ \color{red}a\color{blue}a\color{orange}a $ . Their longest common prefix is one.

## 样例 #1

### 输入

```
7
3 3 3
aba
3 3 3
aaa
7 2 2
abacaba
9 4 4
abababcab
10 1 1
codeforces
9 3 3
abafababa
5 3 3
zpozp
```

### 输出

```
0
1
3
2
10
2
0
```



---

---
title: "Cutting Game"
layout: "post"
diff: 普及+/提高
pid: CF1974F
tag: ['二分', '双指针 two-pointer']
---

# Cutting Game

## 题目描述

Alice and Bob were playing a game again. They have a grid of size $ a \times b $ ( $ 1 \le a, b \le 10^9 $ ), on which there are $ n $ chips, with at most one chip in each cell. The cell at the intersection of the $ x $ -th row and the $ y $ -th column has coordinates $ (x, y) $ .

Alice made the first move, and the players took turns. On each move, a player could cut several (but not all) rows or columns from the beginning or end of the remaining grid and earn a point for each chip that was on the cut part of the grid. Each move can be described by the character 'U', 'D', 'L', or 'R' and an integer $ k $ :

- If the character is 'U', then the first $ k $ remaining rows will be cut;
- If the character is 'D', then the last $ k $ remaining rows will be cut;
- If the character is 'L', then the first $ k $ remaining columns will be cut;
- If the character is 'R', then the last $ k $ remaining columns will be cut.

Based on the initial state of the grid and the players' moves, determine the number of points earned by Alice and Bob, respectively.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains four integers $ a $ , $ b $ , $ n $ , and $ m $ ( $ 2 \le a, b \le 10^9 $ , $ 1 \le n, m \le 2 \cdot 10^5 $ ) — the dimensions of the grid, the number of chips, and the number of moves.

Each of the next $ n $ lines contain two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i \le a $ , $ 1 \le y_i \le b $ ) — the coordinates of the chips. All pairs of coordinates are distinct.

Each of the next $ m $ lines contain a character $ c_j $ and an integer $ k_j $ — the description of the $ j $ -th move. It is guaranteed that $ k $ is less than the number of rows/columns in the current grid. In other words, a player cannot cut the entire remaining grid on their move.

It is guaranteed that the sum of the values of $ n $ across all test cases in the test does not exceed $ 2 \cdot 10^5 $ . It is guaranteed that the sum of the values of $ m $ across all test cases in the test does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two integers — the number of points earned by Alice and Bob, respectively.

## 说明/提示

Below is the game from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974F/9f1554443f39a3c1eca0a96dffd50920759ede0a.png)On her turn, Alice cut $ 2 $ rows from the bottom and scored $ 2 $ points, then Bob cut $ 1 $ column from the right and scored one point. Note that if Bob had cut $ 1 $ row from the bottom, he would have also scored $ 1 $ point.

## 样例 #1

### 输入

```
6
4 4 3 2
4 1
3 3
2 4
D 2
R 1
4 4 3 3
4 1
3 2
2 3
D 1
L 1
U 2
3 5 3 2
1 3
2 2
3 3
R 2
R 2
6 4 4 2
1 4
2 3
5 3
1 1
R 1
U 1
9 3 2 1
6 1
3 3
D 8
10 10 2 5
7 5
9 1
R 1
L 2
D 1
U 4
D 1
```

### 输出

```
2 1
2 0
0 3
1 1
2 0
0 1
```



---

---
title: "Bomb"
layout: "post"
diff: 普及+/提高
pid: CF1996F
tag: ['二分']
---

# Bomb

## 题目描述

你有两个长度为 $n$ 的数组 $a$ 和 $b$。最初，你的分数是 $0$。每一次操作中，你可以选择一个 $a_i$ 加到你的分数上。然后 $a_i$ 将会更新为 $\max(0,a_i-b_i)$。

现在你只能执行 $k$ 次操作。那么你能得到的最大分数是多少？

## 输入格式

#### 本题每个测试点包含多组数据

每个测试数据的第一行输入 $t(1 \le t \le 1000)$ 表示数据组数。

每组数据的第一行包含两个整数 $n(1 \le n \le 2 \cdot 10^5)$ 和 $k(1 \le k \le 10^9)$。分别表示两个数组的长度以及操作次数。

接下来的 $2$ 行，分别输入数组 $a$ 和 $b(1 \le a_i,b_i \le 10^9)$。

保证每个测试数据中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

共 $t$ 行，第 $i$ 行表示第 $i$ 组数据执行 $k$ 次操作后分数的最大值。

## 样例 #1

### 输入

```
5
3 4
5 6 7
2 3 4
5 9
32 52 68 64 14
18 14 53 24 8
5 1000
1 2 3 4 5
5 4 3 2 1
1 1000000
1000000
1
10 6
3 3 5 10 6 8 6 8 7 7
6 1 7 4 1 1 8 9 3 1
```

### 输出

```
21
349
27
500000500000
47
```



---

---
title: "Perform Operations to Maximize Score"
layout: "post"
diff: 普及+/提高
pid: CF1998C
tag: ['贪心', '二分']
---

# Perform Operations to Maximize Score

## 题目描述

I see satyam343. I'm shaking. Please more median problems this time. I love those. Please satyam343 we believe in you.

— satyam343's biggest fan



You are given an array $ a $ of length $ n $ and an integer $ k $ . You are also given a binary array $ b $ of length $ n $ .

You can perform the following operation at most $ k $ times:

- Select an index $ i $ ( $ 1 \leq i \leq n $ ) such that $ b_i = 1 $ . Set $ a_i = a_i + 1 $ (i.e., increase $ a_i $ by $ 1 $ ).

Your score is defined to be $ \max\limits_{i = 1}^{n} \left( a_i + \operatorname{median}(c_i) \right) $ , where $ c_i $ denotes the array of length $ n-1 $ that you get by deleting $ a_i $ from $ a $ . In other words, your score is the maximum value of $ a_i + \operatorname{median}(c_i) $ over all $ i $ from $ 1 $ to $ n $ .

Find the maximum score that you can achieve if you perform the operations optimally.

For an arbitrary array $ p $ , $ \operatorname{median}(p) $ is defined as the $ \left\lfloor \frac{|p|+1}{2} \right\rfloor $ -th smallest element of $ p $ . For example, $ \operatorname{median} \left( [3,2,1,3] \right) = 2 $ and $ \operatorname{median} \left( [6,2,4,5,1] \right) = 4 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

Each test case begins with two integers $ n $ and $ k $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq k \leq 10^9 $ ) — the length of the $ a $ and the number of operations you can perform.

The following line contains $ n $ space separated integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — denoting the array $ a $ .

The following line contains $ n $ space separated integers $ b_1, b_2, \ldots, b_n $ ( $ b_i $ is $ 0 $ or $ 1 $ ) — denoting the array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum value of score you can get on a new line.

## 说明/提示

For the first test case, it is optimal to perform $ 5 $ operations on both elements so $ a = [8,8] $ . So, the maximum score we can achieve is $ \max(8 + \operatorname{median}[8], 8 + \operatorname{median}[8]) = 16 $ , as $ c_1 = [a_2] = [8] $ . It can be proven that you cannot get a better score.

For the second test case, you are not able to perform operations on any elements, so $ a $ remains $ [3,3,3] $ . So, the maximum score we can achieve is $ 3 + \operatorname{median}[3, 3] = 6 $ , as $ c_1 = [a_2, a_3] = [3, 3] $ . It can be proven that you cannot get a better score.

## 样例 #1

### 输入

```
8
2 10
3 3
1 1
3 10
3 3 3
0 0 0
4 4
2 1 5 1
0 1 0 1
5 4
7 5 2 5 4
0 0 1 0 1
5 1
5 15 15 2 11
1 0 0 1 1
5 2
10 11 4 10 15
1 1 0 1 0
4 4
1 1 2 5
1 1 0 0
2 1000000000
1000000000 1000000000
1 1
```

### 输出

```
16
6
8
13
21
26
8
3000000000
```



---

---
title: "Sakurako's Test"
layout: "post"
diff: 普及+/提高
pid: CF2008H
tag: ['数学', '二分', '前缀和']
---

# Sakurako's Test

## 题目描述

Sakurako 即将参加一场考试，这场考试可用一个整数数组 $n$ 和一个相关任务来描述：

对于给定的整数 $x$，Sakurako 可以多次执行以下操作：

- 选择一个整数 $i$，其中 $1 \le i \le n$，且满足 $a_i \ge x$；
- 将 $a_i$ 的值减少 $x$，即改为 $a_i - x$。

通过这样的操作，她需要找到数组 $a$ 的最小可能中位数 $^{\text{∗}}$。

Sakurako 已知数组的内容，但不清楚整数 $x$ 的值。不过，有人透露在接下来的考试中，$x$ 的值会是给定的 $q$ 个值之一，因此她希望你能帮忙找出每一个可能的 $x$ 所对应的最小中位数。

$^{\text{∗}}$ 对于一个长度为 $n$ 的数组，若 $n$ 是偶数，则中位数是排序后数组中第 $\frac{n+2}{2}$ 个位置的元素；若 $n$ 是奇数，则为第 $\frac{n+1}{2}$ 个位置的元素。

## 输入格式

第一行包含一个整数 $t$，表示测试用例的数量（$1 \le t \le 10^4$）。

接下来，每个测试用例的第一行包括两个整数 $n$ 和 $q$，分别表示数组的元素数量和查询数量（$1 \le n, q \le 10^5$）。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$，表示数组的内容（$1 \le a_i \le n$）。

接下来的 $q$ 行每行给出一个整数 $x$，表示一个查询（$1 \le x \le n$）。

保证所有测试用例中 $n$ 和 $q$ 的总和均不超过 $10^5$。

## 输出格式

对于每个测试用例，输出 $q$ 个整数，代表每个查询下计算出的答案。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
1
2
3
4
5
6 3
1 2 6 4 1 3
2
1
5
```

### 输出

```
0 1 1 1 2 
1 0 2
```



---

---
title: "Minimize the Difference"
layout: "post"
diff: 普及+/提高
pid: CF2013D
tag: ['二分', '前缀和']
---

# Minimize the Difference

## 题目描述

给你一个长度为 $n$ 的数 $a_1,a_2,…,a_n$ 我们可以对数组进行任意数量(可能是零)的运算。

在每次操作中，我们选择一个位置 $i$ ( $1 \le i \le n−1 $
 ) ，使 $a_i-1,a_{i+1}+1$

求 $max(a_1,a_2,…,a_n)−min(a_1,a_2,…,a_n)$ 的最小可能值。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 10^5$ ) 。测试用例说明如下:

每个测试用例的第一行都包含一个整数 $n$ ( $1 \le n \le 2 \times 10^{5}$ ) 。

每个测试用例的第二行包含 $n$ 个整数 $a_1,a_2,…,a_n$ ( $1 \le a_i \le 10^{12}$ ) 。

所有测试用例中 $n$
 的总和不超过 $2 \times 10^{5}$ 。

## 输出格式

对于每个测试用例，输出一个整数 $ans$ 表示 $max(a_1,a_2,…,a_n)−min(a_1,a_2,…,a_n)$
 的最小可能值。

## 说明/提示

在第三个测试案例中，您可以使用 $i=1$
 执行两次操作。
之后，数组为 $[2,3,2,3]$
 所以 $ans=max(2,3,2,3)−min(2,3,2,3)=3−2=1$
 。

## 样例 #1

### 输入

```
5
1
1
3
1 2 3
4
4 1 2 3
4
4 2 3 1
5
5 14 4 10 2
```

### 输出

```
0
2
1
1
3
```



---

---
title: "Sums of Segments"
layout: "post"
diff: 普及+/提高
pid: CF2026D
tag: ['二分', '前缀和']
---

# Sums of Segments

## 题目描述

You are given a sequence of integers $ [a_1, a_2, \dots, a_n] $ . Let $ s(l,r) $ be the sum of elements from $ a_l $ to $ a_r $ (i. e. $ s(l,r) = \sum\limits_{i=l}^{r} a_i $ ).

Let's construct another sequence $ b $ of size $ \frac{n(n+1)}{2} $ as follows: $ b = [s(1,1), s(1,2), \dots, s(1,n), s(2,2), s(2,3), \dots, s(2,n), s(3,3), \dots, s(n,n)] $ .

For example, if $ a = [1, 2, 5, 10] $ , then $ b = [1, 3, 8, 18, 2, 7, 17, 5, 15, 10] $ .

You are given $ q $ queries. During the $ i $ -th query, you are given two integers $ l_i $ and $ r_i $ , and you have to calculate $ \sum \limits_{j=l_i}^{r_i} b_j $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ -10 \le a_i \le 10 $ ).

The third line contains one integer $ q $ ( $ 1 \le q \le 3 \cdot 10^5 $ ).

Then $ q $ lines follow, the $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le \frac{n(n+1)}{2} $ ).

## 输出格式

Print $ q $ integers, the $ i $ -th of which should be equal to $ \sum \limits_{j=l_i}^{r_i} b_j $ .

## 样例 #1

### 输入

```
4
1 2 5 10
15
1 1
1 2
1 3
1 4
1 5
1 10
5 10
6 10
2 8
3 4
3 10
3 8
5 6
5 5
1 8
```

### 输出

```
1
4
12
30
32
86
56
54
60
26
82
57
9
2
61
```



---

---
title: "The Endspeaker (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2027D1
tag: ['动态规划 DP', '二分']
---

# The Endspeaker (Easy Version)

## 题目描述

This is the easy version of this problem. The only difference is that you only need to output the minimum total cost of operations in this version. You must solve both versions to be able to hack.

You're given an array $ a $ of length $ n $ , and an array $ b $ of length $ m $ ( $ b_i > b_{i+1} $ for all $ 1 \le i < m $ ). Initially, the value of $ k $ is $ 1 $ . Your aim is to make the array $ a $ empty by performing one of these two operations repeatedly:

- Type $ 1 $ — If the value of $ k $ is less than $ m $ and the array $ a $ is not empty, you can increase the value of $ k $ by $ 1 $ . This does not incur any cost.
- Type $ 2 $ — You remove a non-empty prefix of array $ a $ , such that its sum does not exceed $ b_k $ . This incurs a cost of $ m - k $ .

You need to minimize the total cost of the operations to make array $ a $ empty. If it's impossible to do this through any sequence of operations, output $ -1 $ . Otherwise, output the minimum total cost of the operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 3 \cdot 10^5 $ , $ \boldsymbol{1 \le n \cdot m \le 3 \cdot 10^5} $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

The third line of each test case contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i \le 10^9 $ ).

It is also guaranteed that $ b_i > b_{i+1} $ for all $ 1 \le i < m $ .

It is guaranteed that the sum of $ \boldsymbol{n \cdot m} $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, if it's possible to make $ a $ empty, then output the minimum total cost of the operations.

If there is no possible sequence of operations which makes $ a $ empty, then output a single integer $ -1 $ .

## 说明/提示

In the first test case, one optimal sequence of operations which yields a total cost of $ 1 $ is as follows:

- Perform an operation of type $ 2 $ . Choose the prefix to be $ [9] $ . This incurs a cost of $ 1 $ .
- Perform an operation of type $ 1 $ . The value of $ k $ is now $ 2 $ . This incurs no cost.
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3, 4] $ . This incurs a cost of $ 0 $ .
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3] $ . This incurs a cost of $ 0 $ .
- The array $ a $ is now empty, and the total cost of all operations is $ 1 $ .

In the second test case, it's impossible to remove any prefix of the array since $ a_1 > b_1 $ , so array $ a $ cannot be made empty by any sequence of operations.

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1
```

### 输出

```
1
-1
2
10
4
```



---

---
title: "Reverse the Rivers"
layout: "post"
diff: 普及+/提高
pid: CF2036E
tag: ['二分']
---

# Reverse the Rivers

## 题目描述

A conspiracy of ancient sages, who decided to redirect rivers for their own convenience, has put the world on the brink. But before implementing their grand plan, they decided to carefully think through their strategy — that's what sages do.

There are $ n $ countries, each with exactly $ k $ regions. For the $ j $ -th region of the $ i $ -th country, they calculated the value $ a_{i,j} $ , which reflects the amount of water in it.

The sages intend to create channels between the $ j $ -th region of the $ i $ -th country and the $ j $ -th region of the $ (i + 1) $ -th country for all $ 1 \leq i \leq (n - 1) $ and for all $ 1 \leq j \leq k $ .

Since all $ n $ countries are on a large slope, water flows towards the country with the highest number. According to the sages' predictions, after the channel system is created, the new value of the $ j $ -th region of the $ i $ -th country will be $ b_{i,j} = a_{1,j} | a_{2,j} | ... | a_{i,j} $ , where $ | $ denotes the [bitwise "OR"](http://tiny.cc/bitwise_or) operation.

After the redistribution of water, the sages aim to choose the most suitable country for living, so they will send you $ q $ queries for consideration.

Each query will contain $ m $ requirements.

Each requirement contains three parameters: the region number $ r $ , the sign $ o $ (either " $ < $ " or " $ > $ "), and the value $ c $ . If $ o $ = " $ < $ ", then in the $ r $ -th region of the country you choose, the new value must be strictly less than the limit $ c $ , and if $ o $ = " $ > $ ", it must be strictly greater.

In other words, the chosen country $ i $ must satisfy all $ m $ requirements. If in the current requirement $ o $ = " $ < $ ", then it must hold that $ b_{i,r} < c $ , and if $ o $ = " $ > $ ", then $ b_{i,r} > c $ .

In response to each query, you should output a single integer — the number of the suitable country. If there are multiple such countries, output the smallest one. If no such country exists, output $ -1 $ .

## 输入格式

The first line contains three integers $ n $ , $ k $ , and $ q $ ( $ 1 \leq n, k, q \leq 10^5 $ ) — the number of countries, regions, and queries, respectively.

Next, there are $ n $ lines, where the $ i $ -th line contains $ k $ integers $ a_{i,1}, a_{i,2}, \dots, a_{i,k} $ ( $ 1 \leq a_{i,j} \leq 10^9 $ ), where $ a_{i,j} $ is the value of the $ j $ -th region of the $ i $ -th country.

Then, $ q $ queries are described.

The first line of each query contains a single integer $ m $ ( $ 1 \leq m \leq 10^5 $ ) — the number of requirements.

Then follow $ m $ lines, each containing an integer $ r $ , a character $ o $ , and an integer $ c $ ( $ 1 \leq r \leq k $ , $ 0 \leq c \leq 2 \cdot 10^9 $ ), where $ r $ and $ c $ are the region number and the value, and $ o $ is either " $ < $ " or " $ > $ " — the sign.

It is guaranteed that $ n \cdot k $ does not exceed $ 10^5 $ and that the sum of $ m $ across all queries also does not exceed $ 10^5 $ .

## 输出格式

For each query, output a single integer on a new line — the smallest number of the suitable country, or $ -1 $ if no such country exists.

## 说明/提示

In the example, the initial values of the regions are as follows:

  $ 1 $  $ 3 $  $ 5 $  $ 9 $  $ 4 $  $ 6 $  $ 5 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 7 $ After creating the channels, the new values will look like this:

  $ 1 $  $ 3 $  $ 5 $  $ 9 $  $ 1 | 4 $  $ 3 | 6 $  $ 5 | 5 $  $ 9 | 3 $  $ 1 | 4 | 2 $  $ 3 | 6 | 1 $  $ 5 | 5 | 2 $  $ 9 | 3 | 7 $  $ \downarrow $  $ 1 $  $ 3 $  $ 5 $  $ 9 $  $ 5 $  $ 7 $  $ 5 $  $ 11 $  $ 7 $  $ 7 $  $ 7 $  $ 15 $ In the first query, it is necessary to output the minimum country number (i.e., row) where, after the redistribution of water in the first region (i.e., column), the new value will be greater than four and less than six, and in the second region it will be less than eight. Only the country with number $ 2 $ meets these requirements.

In the second query, there are no countries that meet the specified requirements.

In the third query, only the country with number $ 3 $ is suitable.

In the fourth query, all three countries meet the conditions, so the answer is the smallest number $ 1 $ .

## 样例 #1

### 输入

```
3 4 4
1 3 5 9
4 6 5 3
2 1 2 7
3
1 > 4
2 < 8
1 < 6
2
1 < 8
2 > 8
1
3 > 5
2
4 > 8
1 < 8
```

### 输出

```
2
-1
3
1
```



---

---
title: "Library of Magic"
layout: "post"
diff: 普及+/提高
pid: CF2036G
tag: ['二分', '位运算']
---

# Library of Magic

## 题目描述

This is an interactive problem.

The Department of Supernatural Phenomena at the Oxenfurt Academy has opened the Library of Magic, which contains the works of the greatest sorcerers of Redania — $ n $ ( $ 3 \leq n \leq 10^{18} $ ) types of books, numbered from $ 1 $ to $ n $ . Each book's type number is indicated on its spine. Moreover, each type of book is stored in the library in exactly two copies! And you have been appointed as the librarian.

One night, you wake up to a strange noise and see a creature leaving the building through a window. Three thick tomes of different colors were sticking out of the mysterious thief's backpack. Before you start searching for them, you decide to compute the numbers $ a $ , $ b $ , and $ c $ written on the spines of these books. All three numbers are distinct.

So, you have an unordered set of tomes, which includes one tome with each of the pairwise distinct numbers $ a $ , $ b $ , and $ c $ , and two tomes for all numbers from $ 1 $ to $ n $ , except for $ a $ , $ b $ , and $ c $ . You want to find these values $ a $ , $ b $ , and $ c $ .

Since you are not working in a simple library, but in the Library of Magic, you can only use one spell in the form of a query to check the presence of books in their place:

- "xor l r" — Bitwise XOR query with parameters $ l $ and $ r $ . Let $ k $ be the number of such tomes in the library whose numbers are greater than or equal to $ l $ and less than or equal to $ r $ . You will receive the result of the computation $ v_1 \oplus v_2 \oplus ... \oplus v_k $ , where $ v_1 ... v_k $ are the numbers on the spines of these tomes, and $ \oplus $ denotes the operation of [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng).

Since your magical abilities as a librarian are severely limited, you can make no more than $ 150 $ queries.

## 输入格式

The first line of input contains an integer $ t $ ( $ 1 \le t \le 300 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 10^{18} $ ) — the number of types of tomes.

## 输出格式

The interaction for each test case begins with reading the integer $ n $ .

Then you can make up to $ 150 $ queries.

To make a query, output a string in the format "xor l r" (without quotes) ( $ 1 \leq l \leq r \leq n $ ). After each query, read an integer — the answer to your query.

To report the answer, output a string in the format "ans a b c" (without quotes), where $ a $ , $ b $ , and $ c $ are the numbers you found as the answer to the problem. You can output them in any order.

The interactor is not adaptive, which means that the answer is known before the participant makes queries and does not depend on the queries made by the participant.

After making $ 150 $ queries, the answer to any other query will be $ -1 $ . Upon receiving such an answer, terminate the program to receive a verdict of "WA" (Wrong answer).

After outputting a query, do not forget to output a newline and flush the output buffer. Otherwise, you will receive a verdict of "IL" (Idleness limit exceeded). To flush the buffer, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- refer to the documentation for other languages.

Hacks

To make a hack, use the following format.

The first line should contain a single integer $ t $ ( $ 1 \leq t \leq 300 $ ) — the number of test cases.

The only line of each test case should contain four integers $ n $ , $ a $ , $ b $ , and $ c $ ( $ 3 \leq n \leq 10^{18} $ , $ 1 \le a, b, c \le n $ ) — the number of books in the library and the numbers of the stolen tomes. The numbers $ a $ , $ b $ , and $ c $ must be distinct.

## 说明/提示

In the first test case, the books in the library after the theft look like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2036G/fa5245a6b21b822e029654d6d78459d7dcab42ae.png)

Now consider the answers to the queries:

- For the query "xor 1 1", you receive the result $ 1 \oplus 1 = 0 $ . Two tomes satisfy the condition specified in the query — both with the number $ 1 $ .
- For the query "xor 2 2", you receive the result $ 2 $ , as only one tome satisfies the specified condition.
- For the query "xor 3 3", you receive the result $ 3 $ .
- For the query "xor 4 6", you receive the result $ 4 \oplus 6 \oplus 4 \oplus 5 \oplus 6 = 5 $ .

In the second test case, there are only $ 3 $ types of books, and it is easy to guess that the missing ones have the numbers $ 1 $ , $ 2 $ , and $ 3 $ .

## 样例 #1

### 输入

```
2
6

0

2

3

5

3
```

### 输出

```
xor 1 1

xor 2 2

xor 3 3

xor 4 6

ans 2 3 5

ans 1 2 3
```



---

---
title: "Ardent Flames"
layout: "post"
diff: 普及+/提高
pid: CF2037F
tag: ['二分', '离散化', '差分']
---

# Ardent Flames

## 题目描述

You have obtained the new limited event character Xilonen. You decide to use her in combat.

There are $ n $ enemies in a line. The $ i $ 'th enemy from the left has health $ h_i $ and is currently at position $ x_i $ . Xilonen has an attack damage of $ m $ , and you are ready to defeat the enemies with her.

Xilonen has a powerful "ground stomp" attack. Before you perform any attacks, you select an integer $ p $ and position Xilonen there ( $ p $ can be any integer position, including a position with an enemy currently). Afterwards, for each attack, she deals $ m $ damage to an enemy at position $ p $ (if there are any), $ m-1 $ damage to enemies at positions $ p-1 $ and $ p+1 $ , $ m-2 $ damage to enemies at positions $ p-2 $ and $ p+2 $ , and so on. Enemies that are at least a distance of $ m $ away from Xilonen take no damage from attacks.

Formally, if there is an enemy at position $ x $ , she will deal $ \max(0,m - |p - x|) $ damage to that enemy each hit. Note that you may not choose a different $ p $ for different attacks.

Over all possible $ p $ , output the minimum number of attacks Xilonen must perform to defeat at least $ k $ enemies. If it is impossible to find a $ p $ such that eventually at least $ k $ enemies will be defeated, output $ -1 $ instead. Note that an enemy is considered to be defeated if its health reaches $ 0 $ or below.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) – the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 1 \leq k \leq n \leq 10^5 $ , $ 1 \leq m \leq 10^9 $ ).

The following line contains $ n $ integers $ h_1, h_2, ..., h_n $ ( $ 1 \leq h_i \leq 10^9 $ ).

The last line of each testcase contains $ n $ integers $ x_1, x_2, ..., x_n $ ( $ 1\leq x_i \leq 10^9 $ , $ x_i < x_{i+1} $ for all $ 1 \leq i < n $ )

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output an integer on a new line, the minimum number of attacks that must be performed to defeat at least $ k $ enemies. If it is impossible to find a $ p $ such that eventually at least $ k $ enemies will be defeated, output $ -1 $ instead.

## 说明/提示

In the first testcase, it is optimal to select $ p=2 $ . Each attack, the first enemy takes $ 5-|2-1|=4 $ damage, the second enemy takes $ 5 $ damage, the third enemy takes $ 4 $ damage, the fourth enemy takes $ 3 $ damage, and the fifth enemy takes $ 2 $ damage. After $ 2 $ attacks, the first three enemies will be defeated. It can be shown that it is impossible to defeat $ 3 $ enemies in less than $ 2 $ attacks, no matter which $ p $ is selected.

In the second testcase, we must kill all $ 9 $ enemies. By selecting $ p=5 $ , all nine enemies will be defeated in $ 2 $ attacks.

In the third testcase, we must kill both enemies. However, it can be shown that no $ p $ selected will damage both enemies at the same time, so the answer is $ -1 $ .

In the fourth testcase, selecting $ p=1 $ will enable us to defeat the first enemy in $ 6969697 $ attacks.

In the fifth testcase, selecting $ p=10 $ will make each enemy take $ 1 $ damage per attack. Both enemies will be defeated in $ 15 $ attacks.

## 样例 #1

### 输入

```
6
5 5 3
7 7 7 7 7
1 2 3 4 5
9 5 9
2 4 6 8 10 8 6 4 2
1 2 3 4 5 6 7 8 9
2 10 2
1 1
1 20
2 10 1
69696969 420420420
1 20
2 10 2
10 15
1 19
2 2 2
1000000000 1
1 3
```

### 输出

```
2
2
-1
6969697
15
1000000000
```



---

---
title: "Kevin and Competition Memories"
layout: "post"
diff: 普及+/提高
pid: CF2048D
tag: ['贪心', '二分', '数学']
---

# Kevin and Competition Memories

## 题目描述

Kevin 曾经进入过 Rio 的记忆。在那段记忆中，曾举办过一系列的比赛。Kevin 还记得所有参赛者和比赛的问题，但具体的比赛轮次、问题分布和排名已经模糊不清。

有 $m$ 个比赛问题，第 $i$ 个问题的难度为 $b_i$。每场比赛选择 $k$ 个问题，因此总共会有 $\lfloor \frac{m}{k} \rfloor$ 场比赛。这意味着你可以任意组合选择这些比赛问题，并挑出总共 $\lfloor \frac{m}{k} \rfloor \cdot k$ 个问题参赛，每个问题最多只能被选一次，剩余 $m \bmod k$ 个问题将未被使用。例如，如果 $m = 17$ 且 $k = 3$，你将组织 $5$ 场比赛，每场 $3$ 个问题，会剩下 $2$ 个问题没有用上。

比赛有 $n$ 位参赛者，其中 Kevin 是第 1 位。第 $i$ 位参赛者的评分是 $a_i$。在比赛中，每个参赛者能解决难度不超过其评分的问题，具体来说，第 $i$ 位参赛者能解决第 $j$ 个问题，当且仅当 $a_i \geq b_j$。在每场比赛中，Kevin 的排名定义为那些比他解掉更多题目的参赛者数量加一。

对于每个 $k = 1, 2, \ldots, m$，Kevin 想知道在所有 $\lfloor \frac{m}{k} \rfloor$ 场比赛中的排名之和的最小可能值。也就是说，对于某个 $k$，你需要优化问题的选择和分配，使得 Kevin 的排名之和最小化。

不同的 $k$ 值代表的比赛是相互独立的。换言之，你可以对每个不同的 $k$ 值分别规划问题分配。

## 输入格式

输入包含多组测试数据。第一行为测试数据的组数 $t$（$1 \le t \le 5 \cdot 10^4$）。

每组测试数据的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 3 \cdot 10^5$），分别表示参赛者数量和问题数量。

接下来的行中，第二行列出 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le 10^9$）代表每个参赛者的评分。

第三行列出 $m$ 个整数 $b_1, b_2, \ldots, b_m$（$0 \le b_i \le 10^9$）代表每个问题的难度。

保证所有测试数据中的 $n$ 与 $m$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每组测试数据，输出 $m$ 个整数，分别代表对于每个 $k = 1, 2, \ldots, m$，Kevin 的排名之和的最小可能值。

## 说明/提示

考虑第一个测试数据：

- 当 $k=1$ 时，每场比赛只包含一个问题，分配方式是唯一的。例如，在包含难度为 $4$ 的第三个问题的比赛中，除了第 2 位参赛者外，所有人都能解决。因为没有人比 Kevin 解出更多的问题，他在这场比赛中排名第 1。同理，在所有 $4$ 场比赛中，Kevin 的排名分别是 $1, 3, 1, 2$，总和为 $7$。

- 当 $k=2$ 时，最佳选择是将第 1 和第 3 个问题组成一场比赛，第 2 和第 4 个问题组成另一场。在前一场比赛中，4 名选手分别解决 $2, 1, 2, 2$ 个问题，Kevin 排名第 1；在后一场比赛中，选手分别解决 $0, 0, 2, 1$ 个问题，因有 2 位选手多解题，Kevin 排名第 $3$。所以总和是 $1 + 3 = 4$。这是最优解。

- 当 $k=3$ 时，可以选择第 1、3、4 个问题组成一场比赛，Kevin 的排名是 2，为最优。

- 当 $k=4$ 时，只有一场比赛，分配方式唯一，Kevin 的排名是 3。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
4 4
4 3 7 5
2 5 4 6
5 5
5 0 4 8 6
1 3 9 2 7
6 7
1 1 4 5 1 4
1 9 1 9 8 1 0
7 6
1 9 1 9 8 1 0
1 1 4 5 1 4
```

### 输出

```
7 4 2 3
6 2 1 1 2
7 3 2 1 1 1 1
15 9 5 4 4 4
```



---

---
title: "Kevin and Bipartite Graph"
layout: "post"
diff: 普及+/提高
pid: CF2048E
tag: ['二分图', '构造']
---

# Kevin and Bipartite Graph

## 题目描述

武器工厂需要一种海报设计模式，并向 Kevin 求助。

海报设计模式是一个二分图，左半部分有 $2n$ 个顶点，右半部分有 $m$ 个顶点。左半部分的每个顶点与右半部分的每个顶点之间都有一条边，总共形成 $2nm$ 条边。

Kevin 必须用范围在 $[1, n]$ 内的正整数为每条边着色。如果二分图中没有单色环（所有边颜色相同的简单环），则该海报设计模式是良好的。

Kevin 需要你的帮助来构造一个良好的二分图，或者在不可能的情况下通知他。

**单色环**：指所有边颜色都相同的简单环。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \leq t \leq 100$）。

每个测试用例的唯一一行包含两个整数 $n$ 和 $m$（$1 \leq n, m \leq 10^3$），表示二分图左半部分有 $2n$ 个顶点，右半部分有 $m$ 个顶点。

保证所有测试用例的 $n$ 之和以及 $m$ 之和都不超过 $10^3$。

## 输出格式

对于每个测试用例，如果没有解决方案，则输出 No。

否则，首先输出 Yes，然后输出 $2n$ 行，每行包含 $m$ 个正整数。第 $i$ 行的第 $j$ 个整数表示左半部分第 $i$ 个顶点和右半部分第 $j$ 个顶点之间的边的颜色。

如果有多个答案，可以输出其中任何一个。

你可以以任何大小写形式输出每个字母（例如，字符串 yEs、yes、Yes 和 YES 都将被识别为肯定回答）。

## 说明/提示

对于第一个测试用例，图形如下所示：

对于第二个测试用例，可以证明没有有效的解决方案。

## 样例 #1

### 输入

```
3
2 2
3 7
5 4
```

### 输出

```
YES
1 2
2 1
2 2
2 1
NO
YES
1 1 1 1
1 2 2 2
1 2 3 3
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
```



---

---
title: "Palindrome Shuffle"
layout: "post"
diff: 普及+/提高
pid: CF2069D
tag: ['字符串', '贪心', '二分']
---

# Palindrome Shuffle

## 题目描述

给定一个由小写拉丁字母组成的字符串 $s$。

你可以对字符串 $s$ 执行以下操作：选择一个连续的（可能为空的）子串，并对其进行洗牌（即重新排列子串中的字符顺序）。

注意：回文是指正向和反向读取相同的字符串。例如，字符串 a、bab、acca、bcabcbacb 是回文，而 ab、abbbaa、cccb 则不是。

你的任务是确定为了将给定字符串 $s$ 转换为回文，必须进行操作的最小子串长度。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例仅包含一行字符串 $s$（$2 \le |s| \le 2 \cdot 10^5$），由小写拉丁字母组成。

输入额外约束：
- 字符串 $s$ 的长度为偶数；
- 字符串 $s$ 总能被转换为回文；
- 所有测试用例的 $s$ 长度总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——为了将字符串转换为回文必须进行操作的最小子串长度。


## 说明/提示

第一个示例中，可以按如下方式操作：baba → baab。

第二个示例中，字符串已经是回文，因此可以选择空子串进行操作。

第三个示例中，可以按如下方式操作：ddaa → adda。

第四个示例中，可以按如下方式操作：acbacddacbca → acbcaddacbca。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
baba
cc
ddaa
acbacddacbca
```

### 输出

```
2
0
3
2
```



---

---
title: "Baudelaire (easy version)"
layout: "post"
diff: 普及+/提高
pid: CF2106G1
tag: ['二分', '交互题']
---

# Baudelaire (easy version)

## 题目描述

这是该问题的简单版本。两个版本之间的唯一区别在于，在这个版本中，保证每个节点都与节点 $1$ 相邻。

本题是交互题。

波德莱尔非常富有，所以他购买了一棵大小为 $n$ 的树，这棵树以某个任意节点为根。此外，每个节点的值为 $1$ 或 $-1$。在这个版本中，每个节点都与节点 $1$ 相邻。但请注意，节点 $1$ 不一定是根节点。

书呆子牛看到了这棵树并爱上了它。然而，计算机科学的收入不足以让他买下这棵树。波德莱尔决定和书呆子牛玩一个游戏，如果他赢了，就把这棵树送给他。

书呆子牛不知道哪个节点是根，也不知道节点的值。但他可以向波德莱尔提出两种类型的查询：

1. `1 k u₁ u₂ ... uₖ`：设 $f(u)$ 为从树的根到节点 $u$ 的路径上所有节点的值之和。书呆子牛可以选择一个整数 $k$（$1 \le k \le n$）和 $k$ 个节点 $u_1, u_2, ..., u_k$，然后他会收到值 $f(u_1) + f(u_2) + ... + f(u_k)$。
2. `2 u`：波德莱尔将切换节点 $u$ 的值。具体来说，如果 $u$ 的值为 $1$，则变为 $-1$，反之亦然。

如果书呆子牛在总共 $n + 200$ 次查询内正确猜出每个节点的值（即执行查询后树的最终值），他就获胜。你能帮助他获胜吗？

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 10^3$），表示树的大小。

接下来的 $n-1$ 行每行包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$，$u \neq v$），表示树中节点 $u$ 和 $v$ 之间有一条边。在这个版本中，保证 $u = 1$ 或 $v = 1$。

保证所有测试用例的 $n$ 之和不超过 $10^3$，并且每个输入的图都是合法的树。

## 输出格式

要提出类型 $1$ 的查询，请按以下格式输出一行（不带引号）：
- `? 1 k u₁ u₂ ... uₖ`（$1 \le k, u_i \le n$）

评测机将返回一个整数，即 $f(u_1) + f(u_2) + ... + f(u_k)$。

要提出类型 $2$ 的查询，请按以下格式输出一行：
- `? 2 u`（$1 \le u \le n$）

评测机会切换节点 $u$ 的值：如果其值为 $1$，则变为 $-1$，反之亦然。

当你找到答案时，请按以下格式输出一行：
- `! v₁ v₂ ... vₙ`（$v_i = 1$ 或 $v_i = -1$，$v_i$ 是执行查询后节点 $i$ 的值）

之后，继续处理下一个测试用例，或者如果是最后一个测试用例则终止程序。输出答案不计入查询次数。

交互器不是自适应的，这意味着树的值在参与者提出查询之前就已经确定。

如果你的程序进行了超过 $n + 200$ 次查询，它应立即终止并收到 Wrong Answer 的判定。否则，你可能会得到任意判定，因为你的解决方案将继续从已关闭的流中读取数据。

在打印查询后，不要忘记输出换行符并刷新输出缓冲区。否则，你可能会得到 Idleness Limit Exceeded 的判定。可以使用以下方法刷新输出：
- C++：`fflush(stdout)` 或 `cout.flush()`
- Java：`System.out.flush()`
- Pascal：`flush(output)`
- Python：`stdout.flush()`
- 其他语言请参考相关文档。

## Hack 格式

对于 Hack 攻击，请使用以下格式：

第一行应包含一个整数 $t$（$1 \le t \le 100$）——测试用例的数量。

每个测试用例的第一行必须包含两个整数 $n$ 和 $root$（$2 \le n \le 10^3$，$1 \le root \le n$）——树的大小和树的根节点。

每个测试用例的第二行必须包含 $n$ 个整数 $a_1, a_2, ..., a_n$（$|a_i| = 1$）——其中 $a_i$ 是节点 $i$ 的值。

接下来的 $n-1$ 行每行必须包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$）——表示节点 $u$ 和 $v$ 之间有一条边。

所有测试用例的 $n$ 之和不得超过 $10^3$，并且每个输入的图必须是合法的树。对于此版本，每个节点必须与节点 $1$ 相邻。

## 说明/提示

在示例中，树的根是节点 $2$，节点的初始值为 $[-1, 1, -1, 1]$。因此，$f(1) = 0$，$f(2) = 1$，$f(3) = -1$，$f(4) = 1$。

首先，我们查询 $f(1) + f(2) + f(3)$ 的和，得到 $0$。然后，我们切换节点 $2$ 的值，此时节点的值变为 $[-1, -1, -1, 1]$。因此，$f(1) = -2$，$f(2) = -1$，$f(3) = -3$，$f(4) = -1$，$f(1) + f(2) + f(3) = -6$。

最终，我们推断出节点的值为 $[-1, -1, -1, 1]$，并输出该结果。

注意，这只是一个解释查询如何工作的示例，并不涉及具体的解题策略。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
1
4
1 2
3 1
1 4

0


-6
```

### 输出

```
? 1 3 1 2 3

? 2 2
? 1 3 1 2 3

! -1 -1 -1 1
```



---

---
title: "Fewer Batteries"
layout: "post"
diff: 普及+/提高
pid: CF2110D
tag: ['动态规划 DP', '图论', '二分']
---

# Fewer Batteries

## 题目描述

在 2077 年机器人统治世界后，它们决定进行以下比赛。

有 $n$ 个检查点，第 $i$ 个检查点包含 $b_i$ 块电池。机器人最初从第 $1$ 个检查点出发，不带任何电池，必须到达第 $n$ 个检查点。

检查点之间共有 $m$ 条单向通道。第 $i$ 条通道允许从点 $s_i$ 移动到点 $t_i$（$s_i < t_i$），但不能反向移动。此外，只有当机器人拥有至少 $w_i$ 块充满电的电池时，才能使用第 $i$ 条通道；否则它会在途中耗尽电量。

当机器人到达点 $v$ 时，可以额外获取 $0$ 到 $b_v$（含）之间的任意数量电池。而且，它会携带之前收集的所有电池，并在每个检查点为所有已收集的电池充电。

求机器人旅程结束时能够拥有的最少电池数量，如果无法从第一个检查点到达最后一个检查点，则报告不可能。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例描述。

每个测试用例的第一行包含两个整数 $n, m$（$2 \leq n \leq 2 \cdot 10^5$，$0 \leq m \leq 3 \cdot 10^5$）——分别表示检查点数量和通道数量。

第二行包含 $n$ 个数字 $b_i$（$0 \leq b_i \leq 10^9$）——第 $i$ 个检查点的电池数量。

接下来的 $m$ 行每行包含三个整数 $s_i, t_i, w_i$（$1 \leq s_i < t_i \leq n$，$1 \leq w_i \leq 10^9$）——通道的起点、终点和通过所需的最低电池数量。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。
保证所有测试用例的 $m$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出旅程结束时能够拥有的最少电池数量，如果无法到达点 $n$，则输出 $-1$。


## 说明/提示

在第一个测试用例中，需要在起点获取 $1$ 块电池，然后移动到点 $2$，再移动到点 $3$。

在第二个测试用例中，需要在起点获取 $2$ 块电池，移动到点 $2$ 再获取 $2$ 块电池，移动到点 $4$，最后移动到点 $5$。

在第三个测试用例中，没有从点 $1$ 到点 $n$ 的路径。

在第四个测试用例中，需要在起点获取 $1$ 块电池，移动到点 $2$ 再获取 $9$ 块电池，移动到点 $3$，最后移动到点 $4$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 3
2 0 0
1 2 1
2 3 1
1 3 2
5 6
2 2 5 0 1
1 2 2
1 3 1
1 4 3
3 5 5
2 4 4
4 5 3
2 0
1 1
4 4
3 10 0 0
1 2 1
1 3 3
2 3 10
3 4 5
```

### 输出

```
1
4
-1
10
```



---

---
title: "Cellular Network"
layout: "post"
diff: 普及+/提高
pid: CF702C
tag: ['二分', '差分']
---

# Cellular Network

## 题目描述

在直线上给出n个城市的位置(x坐标)和在同一直线上的m个蜂窝塔的位置(x坐标)。所有的塔都以同样的方式工作——它们为所有城市提供蜂窝网络，这些城市位于离塔不超过r的距离处才能被蜂窝网络覆盖。

你的任务是找出使得每个城市都能被蜂窝网络覆盖的最小r值，即每个城市在距离r的范围内至少有一个蜂窝塔。

如果r=0，则塔仅为其所在的位置提供蜂窝网络。一个塔可以为任意数量的城市提供蜂窝网络，但是所有这些城市都必须在距离塔不超过r的距离上。

## 输入格式

第一行包含两个正整数n和m，表示有n个城市与m个蜂窝塔。

第二行包含n个整数a[1],a[2]...a[n](a[i]>=a[i-1])，表示每个城市的位置(x坐标)

第三行包含m个整数b[1],b[2]...b[m](b[i]>=b[i-1])，表示每个蜂窝塔的位置(x坐标)

注意，允许多个城市或蜂窝塔位置相同。

## 输出格式

输出最小的r，使得每个城市都被蜂窝网络覆盖。

## 说明/提示

1<=n,m<=10^5

-10^9<=a[i]<=10^9

-10^9<=b[j]<=10^9

## 样例 #1

### 输入

```
3 2
-2 2 4
-3 0

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 3
1 5 10 14 17
4 11 15

```

### 输出

```
3

```



---

---
title: "Mahmoud and Ehab and the bipartiteness"
layout: "post"
diff: 普及+/提高
pid: CF862B
tag: ['二分图']
---

# Mahmoud and Ehab and the bipartiteness

## 题目描述

Mahmoud and Ehab continue their adventures! As everybody in the evil land knows, Dr. Evil likes bipartite graphs, especially trees.

A tree is a connected acyclic graph. A bipartite graph is a graph, whose vertices can be partitioned into $ 2 $ sets in such a way, that for each edge $ (u,v) $ that belongs to the graph, $ u $ and $ v $ belong to different sets. You can find more formal definitions of a tree and a bipartite graph in the notes section below.

Dr. Evil gave Mahmoud and Ehab a tree consisting of $ n $ nodes and asked them to add edges to it in such a way, that the graph is still bipartite. Besides, after adding these edges the graph should be simple (doesn't contain loops or multiple edges). What is the maximum number of edges they can add?

A loop is an edge, which connects a node with itself. Graph doesn't contain multiple edges when for each pair of nodes there is no more than one edge between them. A cycle and a loop aren't the same .

## 输入格式

The first line of input contains an integer $ n $ — the number of nodes in the tree ( $ 1<=n<=10^{5} $ ).

The next $ n-1 $ lines contain integers $ u $ and $ v $ ( $ 1<=u,v<=n $ , $ u≠v $ ) — the description of the edges of the tree.

It's guaranteed that the given graph is a tree.

## 输出格式

Output one integer — the maximum number of edges that Mahmoud and Ehab can add to the tree while fulfilling the conditions.

## 说明/提示

Tree definition: <a>https://en.wikipedia.org/wiki/Tree\_(graph\_theory)</a>

Bipartite graph definition: [https://en.wikipedia.org/wiki/Bipartite\_graph](https://en.wikipedia.org/wiki/Bipartite_graph)

In the first test case the only edge that can be added in such a way, that graph won't contain loops or multiple edges is $ (2,3) $ , but adding this edge will make the graph non-bipartite so the answer is 0.

In the second test case Mahmoud and Ehab can add edges $ (1,4) $ and $ (2,5) $ .

## 样例 #1

### 输入

```
3
1 2
1 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5

```

### 输出

```
2

```



---

