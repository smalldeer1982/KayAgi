---
title: "Session in BSU"
layout: "post"
diff: 省选/NOI-
pid: CF1027F
tag: ['网络流', '连通块', '二分图']
---

# Session in BSU

## 题目描述

Polycarp studies in Berland State University. Soon he will have to take his exam. He has to pass exactly $ n $ exams.

For the each exam $ i $ there are known two days: $ a_i $ — day of the first opportunity to pass the exam, $ b_i $ — day of the second opportunity to pass the exam ( $ a_i < b_i $ ). Polycarp can pass at most one exam during each day. For each exam Polycarp chooses by himself which day he will pass this exam. He has to pass all the $ n $ exams.

Polycarp wants to pass all the exams as soon as possible. Print the minimum index of day by which Polycarp can pass all the $ n $ exams, or print -1 if he cannot pass all the exams at all.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of exams.

The next $ n $ lines contain two integers each: $ a_i $ and $ b_i $ ( $ 1 \le a_i < b_i \le 10^9 $ ), where $ a_i $ is the number of day of the first passing the $ i $ -th exam and $ b_i $ is the number of day of the second passing the $ i $ -th exam.

## 输出格式

If Polycarp cannot pass all the $ n $ exams, print -1. Otherwise print the minimum index of day by which Polycarp can do that.

## 样例 #1

### 输入

```
2
1 5
1 7

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3
5 13
1 5
1 7

```

### 输出

```
7

```

## 样例 #3

### 输入

```
3
10 40
40 80
10 80

```

### 输出

```
80

```

## 样例 #4

### 输入

```
3
99 100
99 100
99 100

```

### 输出

```
-1

```



---

---
title: "Euclid Guess"
layout: "post"
diff: 省选/NOI-
pid: CF1684G
tag: ['网络流']
---

# Euclid Guess

## 题目描述

下面是一个经过部分改动的求 $\gcd$ 的伪代码（其中 $t$ 是一个初始为空的序列）：

```plain
function Euclid(a, b):
    if a < b:
        swap(a, b)
    if b == 0:
        return a
    r = reminder from dividing a by b      (即设 r 为 a mod b)
    if r > 0:
        append r to the back of t          (即将 r 插入到 t 的尾部)
    return Euclid(b, r)
```

有一个由数对构成的序列 $p$，接下来我们对 $p$ 中每个数对都执行一次上述函数，然后把 $t$ 重新排列并给定到输入中。  
给定 $n,m$ 和长度为 $n$ 的序列 $t$。  
你需要构造一个长度不超过 $2\times10^4$ 的数对序列 $p$，满足：

- 每个数对中的元素都是不超过 $m$ 的正整数。  
- 根据序列 $p$ 可以经过上述操作得到输入中给定的 $t$。

有解输出任意一组解，无解输出 `-1`。

## 输入格式

第一行输入两个整数 $n,m(1\leq n\leq10^3;1\leq m\leq10^9)$。  
接下来一行输入 $n$ 个整数表示 $t_1,t_2,\cdots,t_n(1\leq t_i\leq m)$。

## 输出格式

如果无解，输出一行 `-1`。  
否则，首先输出一行一个整数 $k(1\leq k\leq2\times10^4)$ 表示你构造的 $p$ 的长度。  
接下来输出 $k$ 行，其中第 $i$ 行输出两个整数 $a_i,b_i(1\leq a_i,b_i\leq m)$ 表示 $p$ 中第 $i$ 个数对。

### 样例解释

对于样例一：

- 数对 $(19,11)$ 会将 $8,3,2,1$ 四个数插入到 $t$ 中。
- 数对 $(15,9)$ 会将 $6,3$ 两个数插入到 $t$ 中。
- 数对 $(3,7)$ 会将 $1$ 这个数插入到 $t$ 中。

最终 $t=[8,3,2,1,6,3,1]$，经过重新排列后可以得到输入中给定的 $[1,8,1,6,3,2,3]$。

## 样例 #1

### 输入

```
7 20
1 8 1 6 3 2 3
```

### 输出

```
3
19 11
15 9
3 7
```

## 样例 #2

### 输入

```
2 10
7 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2 15
1 7
```

### 输出

```
1
15 8
```

## 样例 #4

### 输入

```
1 1000000000
845063470
```

### 输出

```
-1
```



---

---
title: "Madoka and The First Session"
layout: "post"
diff: 省选/NOI-
pid: CF1717F
tag: ['网络流']
---

# Madoka and The First Session

## 题目描述

给出整数 $n$ 和 $m$ 对整数$(v_i,u_i)$。同时有一个序列 $B$ ,长度为 $n$ ，保证一开始全为 $0$ 。

然后对于每一对 $(v_i,u_i)$，可以执行两种操作中的一种:

1. $b_{v_i}\gets b_{v_i}-1，b_{u_i}\gets b_{u_i}+1$
2. $b_{v_i}\gets b_{v_i}+1，b_{u_i}\gets b_{u_i}-1$

然后还会给你两个序列 $A$，$S$  长度均为 $n$，保证当 $s_i=0$ 时，$a_i=0$ 。

问你在在所有操作方案中，是否有一种可以使得对于任意的 $s_i=1$，都有 $a_i=b_i$。

## 输入格式

第 $1$ 行两个整数 $n$，$m$。

第 $2$ 行 $n$ 个整数，表示 $S$ 数组。

第 $3$ 行 $n$ 个整数，表示 $A$ 数组。

第 $4\sim n-3$ 行每行 $2$ 个整数，表示 $(u_i,v_i)$。

## 输出格式

有解的话第一行输出 `YES`，然后下面 $m$ 行如果执行操作 $1$ 就输出 $(v_i,u_i)$，执行操作 $2$ 输出 $(u_i,v_i)$。如果无解则输出`NO`。

## 样例 #1

### 输入

```
5 5
1 1 1 1 1
-2 0 2 1 -1
1 5
1 4
3 5
3 4
4 5
```

### 输出

```
YES
1 5
1 4
5 3
4 3
5 4
```

## 样例 #2

### 输入

```
5 5
0 1 0 1 0
0 1 0 0 0
1 3
2 3
3 5
3 4
4 5
```

### 输出

```
YES
1 3
3 5
3 2
4 3
5 4
```

## 样例 #3

### 输入

```
4 4
1 1 1 1
0 2 -2 2
1 3
1 4
2 3
2 4
```

### 输出

```
NO
```



---

---
title: "Matching Reduction"
layout: "post"
diff: 省选/NOI-
pid: CF1721F
tag: ['网络流', '二分图']
---

# Matching Reduction

## 题目描述

You are given a bipartite graph with $ n_1 $ vertices in the first part, $ n_2 $ vertices in the second part, and $ m $ edges. The maximum matching in this graph is the maximum possible (by size) subset of edges of this graph such that no vertex is incident to more than one chosen edge.

You have to process two types of queries to this graph:

- $ 1 $ — remove the minimum possible number of vertices from this graph so that the size of the maximum matching gets reduced exactly by $ 1 $ , and print the vertices that you have removed. Then, find any maximum matching in this graph and print the sum of indices of edges belonging to this matching;
- $ 2 $ — query of this type will be asked only after a query of type $ 1 $ . As the answer to this query, you have to print the edges forming the maximum matching you have chosen in the previous query.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 输入格式

The first line contains four integers $ n_1 $ , $ n_2 $ , $ m $ and $ q $ ( $ 1 \le n_1, n_2 \le 2 \cdot 10^5 $ ; $ 1 \le m \le \min(n_1 \cdot n_2, 2 \cdot 10^5) $ ; $ 1 \le q \le 2 \cdot 10^5 $ ).

Then $ m $ lines follow. The $ i $ -th of them contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i \le n_1 $ ; $ 1 \le y_i \le n_2 $ ) meaning that the $ i $ -th edge connects the vertex $ x_i $ in the first part and the vertex $ y_i $ in the second part. There are no pairs of vertices that are connected by more than one edge.

Then $ q $ lines follow. The $ i $ -th of them contains one integer, $ 1 $ or $ 2 $ , denoting the $ i $ -th query. Additional constraints on queries:

- the number of queries of type $ 1 $ won't exceed the size of the maximum matching in the initial graph;
- the number of queries of type $ 2 $ won't exceed $ 3 $ ;
- each query of type $ 2 $ is preceded by a query of type $ 1 $ ;
- your solution is allowed to read the $ i $ -th query only after printing the answer for the $ (i-1) $ -th query and flushing the output.

## 输出格式

For a query of type $ 1 $ , print the answer in three lines as follows:

- the first line should contain the number of vertices you remove;
- the second line should contain the indices of vertices you remove, as follows: if you remove the vertex $ x $ from the left part, print $ x $ ; if you remove the vertex $ y $ from the right part, print $ -y $ (negative index);
- the third line should contain the sum of indices of edges in some maximum matching in the resulting graph. The edges are numbered from $ 1 $ to $ m $ .

For a query of type $ 2 $ , print the answer in two lines as follows:

- the first line should contain the size of the maximum matching;
- the second line should contain the indices of the edges belonging to the maximum matching. Note that the sum of these indices should be equal to the number you printed at the end of the previous query of type $ 1 $ ;

After printing the answer to a query, don't forget to flush the output.

## 说明/提示

In this problem, you may receive the verdict "Idleness Limit Exceeded" since it is in online mode. If it happens, it means that either the output format is wrong, or you don't meet some constraint of the problem. You may treat this verdict as "Wrong Answer".

For your convenience, the output for queries in the example is separated by the line ===. Don't print this line in your program, it is done only to make sure that it's easy to distinguish between answers for different queries in the statement.

## 样例 #1

### 输入

```
3 4 4 4
2 2
1 3
2 1
3 4
1
2
1
2
```

### 输出

```
1
-4
3
===
2
1 2
===
1
2
2
===
1
2
```



---

---
title: "Double Sort II"
layout: "post"
diff: 省选/NOI-
pid: CF1783F
tag: ['网络流', '二分图']
---

# Double Sort II

## 题目描述

You are given two permutations $ a $ and $ b $ , both of size $ n $ . A permutation of size $ n $ is an array of $ n $ elements, where each integer from $ 1 $ to $ n $ appears exactly once. The elements in each permutation are indexed from $ 1 $ to $ n $ .

You can perform the following operation any number of times:

- choose an integer $ i $ from $ 1 $ to $ n $ ;
- let $ x $ be the integer such that $ a_x = i $ . Swap $ a_i $ with $ a_x $ ;
- let $ y $ be the integer such that $ b_y = i $ . Swap $ b_i $ with $ b_y $ .

Your goal is to make both permutations sorted in ascending order (i. e. the conditions $ a_1 < a_2 < \dots < a_n $ and $ b_1 < b_2 < \dots < b_n $ must be satisfied) using minimum number of operations. Note that both permutations must be sorted after you perform the sequence of operations you have chosen.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 3000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ; all $ a_i $ are distinct).

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le n $ ; all $ b_i $ are distinct).

## 输出格式

First, print one integer $ k $ ( $ 0 \le k \le 2n $ ) — the minimum number of operations required to sort both permutations. Note that it can be shown that $ 2n $ operations are always enough.

Then, print $ k $ integers $ op_1, op_2, \dots, op_k $ ( $ 1 \le op_j \le n $ ), where $ op_j $ is the value of $ i $ you choose during the $ j $ -th operation.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
5
1 3 2 4 5
2 1 3 4 5
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
2
1 2
1 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
1 3 4 2
4 3 2 1
```

### 输出

```
2
3 4
```



---

---
title: "Halve or Subtract"
layout: "post"
diff: 省选/NOI-
pid: CF1799F
tag: ['贪心', '堆', '网络流']
---

# Halve or Subtract

## 题目描述

# Halve or Subtract


给定一个长度为 $n$ 的数列 $ a_1, a_2, \ldots, a_n $ ，一个正整数 $b$ 和两种操作：

1. 选一个 $i$ 满足 $ 1 \le i \le n $ ，把 $ a_i $ 变为 $ \lceil \frac{a_i}{2} \rceil $ 。
2. 选一个 $i$ 满足 $ 1 \le i \le n $ ，把 $ a_i $ 变为 $ \max(a_i - b, 0) $ 。

同时给定两个非负整数 $0 \le k_1, k_2 \le n$， 要求至多进行 $k_1$ 次操作1， $k_2$ 次操作2，同时对于每个元素，每种操作至多进行一次。 

求出进行若干次满足条件的操作后 $a_1 + a_2 + \ldots + a_n$ 的最小值。

## 输入格式

多组数据， 第一行为数据组数 $t$,( $ 1 \le t \le 5000 $ )。

每组数据的第一行有四个整数 $ n $ , $ b $ , $ k_1 $, $ k_2 $ ( $ 1 \le n \le 5000 $ , $ 1 \le b \le 10^9 $ , $ 0 \le k_1, k_2 \le n $ )。

每组数据的第二行有 $ n $ 个整数 $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ )。

保证所有数据的 $n$ 之和不超过 $5000$。

## 输出格式

对于每组数据输出一行一个整数表示 $a_i$ 的和的最小值。

## 样例 #1

### 输入

```
7
3 2 1 1
9 3 5
2 1 2 0
1000000000 1
5 3 1 1
2 8 3 19 3
6 9 4 2
1 2 3 4 5 6
3 10 3 3
1 2 3
5 1 0 0
999999999 999999999 999999999 999999999 999999999
5 5 4 3
5 9 10 7 4
```

### 输出

```
11
500000001
23
6
0
4999999995
6
```



---

---
title: "Privatization"
layout: "post"
diff: 省选/NOI-
pid: CF212A
tag: ['贪心', '网络流']
---

# Privatization

## 题目描述

There is a developed network of flights between Berland and Beerland. All of them belong to the Berland state company BerAvia. Each flight connects some Berland city with some Beerland city. For each flight airplanes fly in both directions.

Changes are coming to Berland — the state decided to privatize BerAvia, namely, to sell out all flights to $ t $ private companies. Each of these companies wants to get the maximal number of flights, so if the Berland flights are sold unevenly, Berland can be accused of partiality. Berland Government decided to sell the flights as evenly as possible between the $ t $ companies.

The unevenness of the distribution of flights between companies is calculated as follows. For each city $ i $ (both Berland and Beerland) we'll calculate the value of

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF212A/8cb4dc3a97b60ddf7de9158fd0e56414b7e627be.png) where $ a_{ij} $ is the number of flights from city $ i $ , which belong to company $ j $ . The sum of $ w_{i} $ for all cities in both countries is called the unevenness of the distribution. The distribution with the minimal unevenness is the most even one.Help the Berland government come up with the most even distribution plan of selling flights.

## 输入格式

The first input line contains four integers $ n,m,k $ and $ t $ ( $ 1<=n,m,t<=200;1<=k<=5000 $ ), where $ n,m $ are the numbers of cities in Berland and Beerland, correspondingly, $ k $ is the number of flights between them, and $ t $ is the number of private companies. Next $ k $ lines describe the flights, one per line, as pairs of positive integers $ x_{i},y_{i} $ ( $ 1<=x_{i}<=n;1<=y_{i}<=m $ ), where $ x_{i} $ and $ y_{i} $ are the indexes of cities in Berland and Beerland, correspondingly, connected by the $ i $ -th flight. There is at most one flight between any pair of cities, each flight connects cities of different countries. The cities in Berland are indexed from 1 to $ n $ , and in Beerland — from 1 to $ m $ .

## 输出格式

Print the unevenness of the sought plan on the first line. On the second line print a sequence of $ k $ integers $ c_{1},c_{2},...,c_{k} $ ( $ 1<=c_{i}<=t $ ), where $ c_{i} $ is the index of the company that should buy the $ i $ -th flight. Assume that the flights are indexed from 1 to $ k $ in the order they appear in the input. If there are multiple solutions, print any of them.

## 样例 #1

### 输入

```
3 5 8 2
1 4
1 3
3 3
1 2
1 1
2 1
1 5
2 2

```

### 输出

```
4
2 1 2 1 2 1 2 2 
```



---

---
title: "Exploration plan"
layout: "post"
diff: 省选/NOI-
pid: CF852D
tag: ['网络流', '图论建模', '最短路']
---

# Exploration plan

## 题目描述

The competitors of Bubble Cup X gathered after the competition and discussed what is the best way to get to know the host country and its cities.

After exploring the map of Serbia for a while, the competitors came up with the following facts: the country has $ V $ cities which are indexed with numbers from $ 1 $ to $ V $ , and there are $ E $ bi-directional roads that connect the cites. Each road has a weight (the time needed to cross that road). There are $ N $ teams at the Bubble Cup and the competitors came up with the following plan: each of the $ N $ teams will start their journey in one of the $ V $ cities, and some of the teams share the starting position.

They want to find the shortest time $ T $ , such that every team can move in these $ T $ minutes, and the number of different cities they end up in is at least $ K $ (because they will only get to know the cities they end up in). A team doesn't have to be on the move all the time, if they like it in a particular city, they can stay there and wait for the time to pass.

Please help the competitors to determine the shortest time $ T $ so it's possible for them to end up in at least $ K $ different cities or print -1 if that is impossible no matter how they move.

Note that there can exist multiple roads between some cities.

## 输入格式

The first line contains four integers: $ V $ , $ E $ , $ N $ and $ K\ (1<=V<=600,\ 1<=E<=20000,\ 1<=N<=min(V,200),\ 1<=K<=N) $ , number of cities, number of roads, number of teams and the smallest number of different cities they need to end up in, respectively.

The second line contains $ N $ integers, the cities where the teams start their journey.

Next $ E $ lines contain information about the roads in following format: $ A_{i}\ B_{i}\ T_{i}\ (1<=A_{i},B_{i}<=V,\ 1<=T_{i}<=10000) $ , which means that there is a road connecting cities $ A_{i} $ and $ B_{i} $ , and you need $ T_{i} $ minutes to cross that road.

## 输出格式

Output a single integer that represents the minimal time the teams can move for, such that they end up in at least $ K $ different cities or output -1 if there is no solution.

If the solution exists, result will be no greater than $ 1731311 $ .

## 说明/提示

Three teams start from city 5, and two teams start from city 2. If they agree to move for 3 minutes, one possible situation would be the following: Two teams in city 2, one team in city 5, one team in city 3 , and one team in city 1. And we see that there are four different cities the teams end their journey at.

## 样例 #1

### 输入

```
6 7 5 4
5 5 2 2 5
1 3 3
1 5 2
1 6 5
2 5 4
2 6 7
3 4 11
3 5 3

```

### 输出

```
3
```



---

---
title: "Anti-Palindromize"
layout: "post"
diff: 省选/NOI-
pid: CF884F
tag: ['字符串', '网络流']
---

# Anti-Palindromize

## 题目描述

对于一个字串 $a$，若其长度 $m$ 为偶数，且对于 $\forall i \in[1,m]$，有 $a_i \neq a_{m-i+1}$，则将其称为反回文串。

Ivan 有一个由 $n$ 个小写拉丁字母构成的字串 $s$，且 $n$ 为偶数。他想用 $s$ 的一些排列构成一些反回文串 $t$。同时他称 $i$ 的美丽值为 $b_i$，且字串 $t$ 的美丽值 $Ans=\sum_{i=1}^{len(s)} b_i[s_i=t_i]$。

请帮 Ivan 确定 $Ans$ 的最大值。

## 输入格式

第一行一个偶数 $n\ (2 \leq n \leq 100)$，表示字串 $s$ 中的字符数量。

第二行一个只含小写字母的字串 $s$，题目保证存在 $s$ 的一个排列 $t$，使得 $\forall i \in [1,n],t_i \neq t_{n-i+1}$。

第三行为数组 $b\ (1\leq b_i \leq 100)$。

## 输出格式

一个整数，$Ans$ 的最大值。

## 样例 #1

### 输入

```
8
abacabac
1 1 1 1 1 1 1 1

```

### 输出

```
8

```

## 样例 #2

### 输入

```
8
abaccaba
1 2 3 4 5 6 7 8

```

### 输出

```
26

```

## 样例 #3

### 输入

```
8
abacabca
1 2 3 4 4 3 2 1

```

### 输出

```
17

```



---

