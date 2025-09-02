

---

---
title: "STC02 - Antisymmetry"
layout: "post"
diff: 提高+/省选-
pid: SP15569
tag: ['二分', '枚举', '哈希 hashing', 'Manacher 算法']
---

# STC02 - Antisymmetry

## 题目描述

对于一个 01 字符串，如果将这个字符串 0 和 1 取反后，再将整个串反过来和原串一样，就称作「反对称」字符串。比如 00001111 和 010101 就是反对称的，而 1001 就不是。 现在给出一个长度为 n 的 01 字符串，求它有多少个子串是反对称的，注意这里相同的子串出现在不同的位置会被重复计算。

## 输出格式

Translated by @xzjds



---

---
title: "NETADMIN - Smart Network Administrator"
layout: "post"
diff: 提高+/省选-
pid: SP287
tag: ['二分', '网络流']
---

# NETADMIN - Smart Network Administrator

## 题目描述

 The citizens of a small village are tired of being the only inhabitants around without a connection to the Internet. After nominating the future network administrator, his house was connected to the global network. All users that want to have access to the Internet must be connected directly to the admin's house by a single cable (every cable may run underground along streets only, from the admin's house to the user's house). Since the newly appointed administrator wants to have everything under control, he demands that cables of different colors should be used. Moreover, to make troubleshooting easier, he requires that no two cables of the same color go along one stretch of street.

 Your goal is to find the minimum number of cable colors that must be used in order to connect every willing person to the Internet.

## 输入格式

 _t_ \[the number of test cases, t<=500\]  
_n m k_ \[_n_ <=500 the number of houses (the index of the admin's house is 1)\]  
 \[_m_ the number of streets, _k_ the number of houses to connect\]  
_h_ $ _{1} $ _h_ $ _{2} $ ... _h $ _{k} $_  \[a list of _k_ houses wanting to be conected to the network, 2<=_h $ _{i} $_ <=_n_\]  
 \[The next _m_ lines contain pairs of house numbers describing street ends\]  
_e_ $ _{11} $ _e_ $ _{12} $   
_e_ $ _{21} $ _e_ $ _{22} $   
 ...  
_e_ $ _{m1} $ _e_ $ _{m2} $   
 \[next cases\]

## 输出格式

 For each test case print the minimal number of cable colors necessary to make all the required connections.

## 样例 #1

### 输入

```
2

5 5 4

2 3 4 5

1 2

1 3

2 3

2 4

3 5

8 8 3

4 5 7

1 2

1 8

8 7

1 3

3 6

3 2

2 4

2 5
```

### 输出

```
2

1
```



---



---

# 题号列表

- SP15569 - STC02 - Antisymmetry
- SP287 - NETADMIN - Smart Network Administrator


---

---
title: "RACETIME - Race Against Time"
layout: "post"
diff: 提高+/省选-
pid: SP3261
tag: ['枚举', '排序', '分块']
---

# RACETIME - Race Against Time

## 题目描述

现在有$n(1<=n<=1e5)$只奶牛站成一排，每只奶牛手中都拿着一个数字$A_i(0<=A_i<=1e9)$

现在$FJ$要执行$Q(1<=Q<=50000)$个操作，每个操作可能是下面两种操作之一：

$1.$ $M$ $i$ $X$ ：将第$i$只奶牛手上的数字$A_i$替换为$X$

$2.$ $C$ $l$ $r$ $K$：询问区间$[l,r]$内有多少只奶牛手上拿的数字$A_i\le K$

作为$FJ$的好朋友，请你对每一个$2$操作输出答案

由于$FJ$非常蕉♂躁，所以他只允许你在$1s$内回答这些问题

## 输入格式

第一行输入两个正整数$n,Q$，含义如上

接下来$n$行，每一行输入一个正整数$A_i$，表示初始时第$i$只奶牛手上拿的数字$A_i$

接下来有$Q$行输入，代表$FJ$接下来要进行的$Q$个操作，格式如上文

## 输出格式

对于每一个$2$操作，请你输出满足条件的奶牛个数。每个答案占一行

## 样例 #1

### 输入

```
4 6

3

4

1

7

C 2 4 4

M 4 1

C 2 4 4

C 1 4 5

M 2 10

C 1 3 9
```

### 输出

```
2

3

4

2
```



---



---

# 题号列表

- SP3261 - RACETIME - Race Against Time


---

---
title: "GSS1 - Can you answer these queries I"
layout: "post"
diff: 提高+/省选-
pid: SP1043
tag: ['线段树', '分治', '前缀和']
---

# GSS1 - Can you answer these queries I

## 题目描述

You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:   
 Query(x,y) = Max { a\[i\]+a\[i+1\]+...+a\[j\] ; x ≤ i ≤ j ≤ y }.   
 Given M queries, your program must output the results of these queries.

## 输入格式

- The first line of the input file contains the integer N.
- In the second line, N numbers follow.
- The third line contains the integer M.
- M lines follow, where line i contains 2 numbers xi and yi.

## 输出格式

 Your program should output the results of the M queries, one query per line.

## 样例 #1

### 输入

```
3 
-1 2 3
1
1 2
```

### 输出

```
2
```



---

---
title: "DCEPC14D - Finding GP"
layout: "post"
diff: 提高+/省选-
pid: SP23878
tag: ['根号分治']
---

# DCEPC14D - Finding GP

## 题目描述

There is an array A of n elements . You need to tell the number of subsets of size greater than 1 which can form geometric progressions having integral common ratios.

**Constraints:**

1<=N<=1\*10^4  
1<=A\[i\]<=1000000

## 输入格式

The first line contains a single integer denoting the number of integers in the array (N). The second line contains N space separated integers representing the elements of the array.

## 输出格式

The output should contain a single line with the answer to this problem MODULUS 1000000007 .

## 样例 #1

### 输入

```
7\n2 4 4 2 8 16 8
```

### 输出

```
\n\n41
```



---

---
title: "CLOSEST - Closest Triplet"
layout: "post"
diff: 提高+/省选-
pid: SP7209
tag: ['分治']
---

# CLOSEST - Closest Triplet

## 题目描述

### 题意
多组询问，每组询问给出二维平面上的 $n$ 个点，在这 $n$ 个点中选出3个点，使这3个点两两之间的距离的和最小，输出这个最小距离。

## 输入格式

对于每组数据，第一行一个整数 $n$，接下来的 $n$ 行，每行两个整数 $x , y$，表示这 $n$ 个点的坐标。

当输入的 $n$ 为 $-1$ 时，输入结束。

## 输出格式

对于每组数据，输出一行一个浮点数，表示最小距离和，保留三位小数。

## 说明/提示

$3 \le n \le 3000$

$1 \le x,y \le 10^6$

## 样例 #1

### 输入

```
\n4\n1 1\n4 1\n1 5\n1000 1000\n9\n100000 200000\n200000 200000\n150000 286603\n60000 140000\n240000 140000\n150000 340000\n1 340000\n300000 340000\n150000 87087\n-1\n\n
```

### 输出

```
12.000\n300000.796
```



---



---

# 题号列表

- SP1043 - GSS1 - Can you answer these queries I
- SP23878 - DCEPC14D - Finding GP
- SP7209 - CLOSEST - Closest Triplet


---

---
title: "GSS1 - Can you answer these queries I"
layout: "post"
diff: 提高+/省选-
pid: SP1043
tag: ['线段树', '分治', '前缀和']
---

# GSS1 - Can you answer these queries I

## 题目描述

You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:   
 Query(x,y) = Max { a\[i\]+a\[i+1\]+...+a\[j\] ; x ≤ i ≤ j ≤ y }.   
 Given M queries, your program must output the results of these queries.

## 输入格式

- The first line of the input file contains the integer N.
- In the second line, N numbers follow.
- The third line contains the integer M.
- M lines follow, where line i contains 2 numbers xi and yi.

## 输出格式

 Your program should output the results of the M queries, one query per line.

## 样例 #1

### 输入

```
3 
-1 2 3
1
1 2
```

### 输出

```
2
```



---

---
title: "TLE - Time Limit Exceeded"
layout: "post"
diff: 提高+/省选-
pid: SP2829
tag: ['枚举', '状态合并', '前缀和']
---

# TLE - Time Limit Exceeded

## 题目描述

Given integers N (1 ≤ N ≤ 50) and M (1 ≤ M ≤ 15), compute the number of sequences a $ _{1} $ , ..., a $ _{N} $ such that:

- 0 ≤ a $ _{i} $ < 2 $ ^{M} $
- a $ _{i} $ is not divisible by c $ _{i} $ (0 < c $ _{i} $ ≤ 2 $ ^{M} $ )
- a $ _{i} $ & a $ _{i+1} $ = 0 (that is, a $ _{i} $ and a $ _{i+1} $ have no common bits in their binary representation)

## 输入格式

The first line contains the number of test cases, T (1 ≤ T ≤ 10). For each test case, the first line contains the integers N and M, and the second line contains the integers c $ _{1} $ , ..., c $ _{N} $ .

## 输出格式

For each test case, output a single integer: the number of sequences described above, modulo 1,000,000,000.

## 样例 #1

### 输入

```
1

2 2

3 2
```

### 输出

```
1
```



---



---

# 题号列表

- SP1043 - GSS1 - Can you answer these queries I
- SP2829 - TLE - Time Limit Exceeded


---

---
title: "ROADS - Roads"
layout: "post"
diff: 提高+/省选-
pid: SP338
tag: ['枚举', '剪枝']
---

# ROADS - Roads

## 题目描述

题面描述  
有标号为1……n的城市与单行道相连。对于每条道路有两个与之相关的参数：道路的长度以及需要支付的费用（用硬币的数量表示）  
鲍勃和爱丽丝曾经生活在城市1。在注意到爱丽丝在他们喜欢玩的卡牌游戏中作弊后，鲍勃决定与爱丽丝分手并搬走——去城市n。他希望尽快到达那里——越快越好，然而他现在有些现金短缺。
我们希望帮助鲍勃找到从城市1到城市n的一条最短路径——但他必须用他现有的钱支付得起。

## 输入格式

输入的第一行含有一个整数t代表测试样例的组数。下面是t组测试样例。  
对于每组测试数据，第一行含有一个整数K（0<=K<=10000)，代表鲍勃所能支付得起的最大费用。  
第二行含有一个整数N（2<=N<=100)，代表城市总数。  
第三行含有一个整数R（1<=R<=10000)，代表道路的总数。  
接下来R行每行用四个整数S,D,L,T，以单个空格分隔：  
S表示出发点城市标号（1<=S<=N)；  
D表示目的地城市标号（1<=D<=N)；  
L是该道路的长度（1<=L<=100)；
T表示经过该道路的费用(0<=T<=100)。  
注意不同的道路可能拥有相同的起点和终点。

## 输出格式

对于每组测试样例，输出单独的一行表示当花费小于等于K时最短路径的长度。如果不存在这样的路径，输出-1。

## 样例 #1

### 输入

```
2

5

6

7

1 2 2 3

2 4 3 3

3 4 2 4

1 3 4 1

4 6 2 1

3 5 2 0

5 4 3 2

0

4

4

1 4 5 2

1 2 1 0

2 3 1 1

3 4 1 0
```

### 输出

```
11

-1
```



---



---

# 题号列表

- SP338 - ROADS - Roads


---

---
title: "MUTDNA - DNA"
layout: "post"
diff: 提高+/省选-
pid: SP13105
tag: ['字符串', '动态规划 DP', '数学', '栈']
---

# MUTDNA - DNA

## 题目描述

我们发现了一种新型 $DNA$ ,这种 $DNA$ 只由 $N$ 个字母 $A$ 构成,在一次辐射中这种 $dna$  变成了由总共 $N$ 个字母  $A$ 和 $B$ 构成,在辐射中只会发生两种异变： 1.将某个任意位置字母反转 ,例如：将第 $K$  位置的 $A$ 变为 $B$ ，或将  $B$ 变为  $A$ . 2.将  $1$ 到 $K$ 位置上的所有字母反转， $1≤K≤N$ 并且  $K$  可以任选. 请你计算将全  $A$  序列转化为最终序列需要最少多少次异变.每发生一个  $1$  异变或  $2$  异变都计入一次总异变数.

## 输入格式

第一行包含正整数  $N(1≤N≤1 000 000)$ ,代表  $DNA$ 的长度. 第二行输入包含一个有  $N$ 个字符的字符串，每个字符都是  $A$ 或  $B$ .

## 输出格式

一行一个数字代表最小的异变数.

感谢@不许雷同 提供的翻译

## 样例 #1

### 输入

```
1:
4
ABBA
```

### 输出

```
1:
2
```



---

---
title: "KOSARE - KOSARE"
layout: "post"
diff: 提高+/省选-
pid: SP13106
tag: ['动态规划 DP', '状态合并', '容斥原理']
---

# KOSARE - KOSARE

## 题目描述

Mirko found N boxes with various forgotten toys at his attic. There are M different toys, numbered 1

## 输入格式

The first line of input contains two integers N and M (1

Each of the following N lines contains an integer K $ _{i} $ (0

interval \[1, M\], representing the toys in that box.

## 输出格式

The first and only line of output should contain the requested number of ways modulo 1 000 000 007.

## 样例 #1

### 输入

```
1:

3 3

3 1 2 3

3 1 2 3

3 1 2 3
```

### 输出

```
1:

7
```



---

---
title: "IE4 - Endless Knight"
layout: "post"
diff: 提高+/省选-
pid: SP16639
tag: ['动态规划 DP', '容斥原理', 'Lucas 定理']
---

# IE4 - Endless Knight

## 题目描述

马从 $(1, 1)$ 跳到 $(h, w)$，只能往右下跳，不能跳到给定的 $r$ 个点，输出方案数。结果对 $10007$ 取模。

## 输入格式

第一行 $n,(0\le n\le100)$ 为数据组数，每组数组第一行三整数 $h,w,(0\le h,w\le10^8),r,(0\le r\le10)$，此后 $r$ 行为禁止点的坐标。

## 输出格式

输出 $n$ 行，每行格式为 `Case #<序号>: <答案>`，序号从一开始。

## 样例 #1

### 输入

```
5
1 1 0
4 4 1
2 1
3 3 0
7 10 2
1 2
7 1
4 4 1
3 2
```

### 输出

```
Case #1: 1
Case #2: 2
Case #3: 0
Case #4: 5
Case #5: 1
```



---

---
title: "INTDSET - Chiaki With Intervals"
layout: "post"
diff: 提高+/省选-
pid: SP34032
tag: ['动态规划 DP', '线段树']
---

# INTDSET - Chiaki With Intervals

## 题目描述

给你一个有 $n$ 个区间的集合 $A$，求有多少个子集 $S$ 满足条件：任意区间 $a \in A$ 且 $a \notin S$ 均与 $S$ 的至少一个子集有交集。

答案对 $10^9+7$ 取模。

注意 $A$ 本身是一个合法的答案。

## 输入格式

第一行输入整数 $T$ ，代表数据组数。

对于每组数据，先输入整数 $n$，代表区间的个数，接下来是 $n$ 行，每行2个整数 $l_i,r_i$，代表一个区间。

## 输出格式

对于每组数据，输出一个整数。

## 样例 #1

### 输入

```
2
3
1 2
3 4
5 6
3
1 4
2 4
3 4
```

### 输出

```
1
7
```



---

---
title: "ZUMA - ZUMA"
layout: "post"
diff: 提高+/省选-
pid: SP6340
tag: ['动态规划 DP', '搜索', '区间 DP']
---

# ZUMA - ZUMA

## 题目描述

祖玛游戏是这样的：有一列$ N$ 个有颜色的珠子，如果触碰连续 $K$ 个或更多同色的珠子，那么它们就会消失，其余的珠子按照原来顺序接在一起。

现在你每次可以发射任意颜色的珠子，发射在任意位置（开头、结尾以及任意两个之间）。

注意，如果有连续 $K$ 个或更多同色的珠子，你可以不立即消去他们。

问最少需要几发可以消掉所有的珠子。

## 输入格式

第一行 $N,K$

第二行 $N$ 个数 $a_i$，不同的数表示不同的颜色

## 输出格式

一个答案。

【数据规模】
对于所有数据，$1≤N≤100,2≤K≤5,1≤a_i≤100$

## 样例 #1

### 输入

```
2 5
1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 4
3 3 3 3 2 3 1 1 1 3
```

### 输出

```
4
```



---

---
title: "VOCV - Con-Junctions"
layout: "post"
diff: 提高+/省选-
pid: SP666
tag: ['动态规划 DP', '背包 DP', '概率论']
---

# VOCV - Con-Junctions

## 题目描述

给一个 $n$ 个节点和 $n - 1$ 条边的树，现在要在一些节点放置灯最终点亮所有的边。

当一个节点上放置了一盏灯时，所有与它相连的边都会被点亮，且每一条边只需一个端点被点亮即认为被点亮。

试求最少的放灯数量和当放灯数量最少时的方案数。请将方案数结果模 $10007$ 输出。

数据范围：$n \le 100010$。

## 输入格式

在文件的第一行，一个整数 $t(t \le 20)$，表示该测试点中有 $t$ 组测试数据。

接下来若干行描述每个测试数据中树的情况：

首先包含一个 $n$，代表这个测试数据中树的节点个数。

接下来 $n - 1$ 行，每一行有两个整数 $x,y$，代表有一条双向边连接着两个节点 $x$ 和 $y$。

## 输出格式

对于每一个测试数据，请输出最少的放灯数量和当放灯数量最少时的方案数。请将方案数结果模 $10007$ 输出。

## 样例 #1

### 输入

```
2
4
1 2
2 3
3 4
3
1 2
1 3
```

### 输出

```
2 3
1 1
```



---



---

# 题号列表

- SP13105 - MUTDNA - DNA
- SP13106 - KOSARE - KOSARE
- SP16639 - IE4 - Endless Knight
- SP34032 - INTDSET - Chiaki With Intervals
- SP6340 - ZUMA - ZUMA
- SP666 - VOCV - Con-Junctions


---

---
title: "STC02 - Antisymmetry"
layout: "post"
diff: 提高+/省选-
pid: SP15569
tag: ['二分', '枚举', '哈希 hashing', 'Manacher 算法']
---

# STC02 - Antisymmetry

## 题目描述

对于一个 01 字符串，如果将这个字符串 0 和 1 取反后，再将整个串反过来和原串一样，就称作「反对称」字符串。比如 00001111 和 010101 就是反对称的，而 1001 就不是。 现在给出一个长度为 n 的 01 字符串，求它有多少个子串是反对称的，注意这里相同的子串出现在不同的位置会被重复计算。

## 输出格式

Translated by @xzjds



---



---

# 题号列表

- SP15569 - STC02 - Antisymmetry


---

---
title: "INTERVAL - Intervals"
layout: "post"
diff: 提高+/省选-
pid: SP116
tag: ['图论建模', '差分约束', '差分']
---

# INTERVAL - Intervals

## 题目描述

有 $n$ 个区间，在区间 $[a_i,b_i]$ 中至少取任意互不相同的 $c_i$ 个整数。求在满足 $n$ 个区间的情况下，至少要取多少个正整数。

## 输入格式

**本题有多组数据**。

第一行的一个整数 $T$ 表示数据个数。

对于每组数据：

第一行包含一个整数 $n(1\leq n\leq 50000)$ 表示区间数。

以下 $n$ 行描述区间。

输入的第 $i+1$ 行包含三个整数 $a_i,b_i,c_i$，由空格分开。其中 $0\leq a_i\leq b_i\leq 50000，1\leq c_i\leq b_i-a_i+1$。

## 输出格式

对于每组数据，输出一个对于 $n$ 个区间 $[a_i,b_i]$ 
至少取 $c_i$ 个不同整数的数的总个数。

### 样例

input：

```
1
5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1
```

output：

```
6
```


### 样例解释

可以取 $3,4,5,8,9,10$，为符合条件且取数个数最少的一组解。

## 样例 #1

### 输入

```
1
5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1
```

### 输出

```
6
```



---

---
title: "TRSTAGE - Traveling by Stagecoach"
layout: "post"
diff: 提高+/省选-
pid: SP1700
tag: ['状态合并', '图论建模', '最短路']
---

# TRSTAGE - Traveling by Stagecoach

## 题目描述

Once upon a time, there was a traveler.   
  
 He plans to travel using stagecoaches (horse wagons). His starting point and destination are fixed, but he cannot determine his route. Your job in this problem is to write a program which determines the route for him.   
  
 There are several cities in the country, and a road network connecting them. If there is a road between two cities, one can travel by a stagecoach from one of them to the other. A coach ticket is needed for a coach ride. The number of horses is specified in each of the tickets. Of course, with more horses, the coach runs faster.   
  
 At the starting point, the traveler has a number of coach tickets. By considering these tickets and the information on the road network, you should find the best possible route that takes him to the destination in the shortest time. The usage of coach tickets should be taken into account.   
  
 The following conditions are assumed.

- A coach ride takes the traveler from one city to another directly connected by a road. In other words, on each arrival to a city, he must change the coach.
- Only one ticket can be used for a coach ride between two cities directly connected by a road.
- Each ticket can be used only once.
- The time needed for a coach ride is the distance between two cities divided by the number of horses.
- The time needed for the coach change should be ignored.

## 输入格式

The input consists of multiple datasets, each in the following format. The last dataset is followed by a line containing five zeros (separated by a space).   
  
 n m p a b  
 t1 t2 ... tn  
 x1 y1 z1  
 x2 y2 z2  
 ...  
 xp yp zp  
  
  
 Every input item in a dataset is a non-negative integer. If a line contains two or more input items, they are separated by a space.  
  
 n is the number of coach tickets. You can assume that the number of tickets is between 1 and 8. m is the number of cities in the network. You can assume that the number of cities is between 2 and 30. p is the number of roads between cities, which may be zero.   
  
 a is the city index of the starting city. b is the city index of the destination city. a is not equal to b. You can assume that all city indices in a dataset (including the above two) are between 1 and m.   
  
 The second line of a dataset gives the details of coach tickets. ti is the number of horses specified in the i-th coach ticket (1<=i<=n). You can assume that the number of horses is between 1 and 10.   
  
 The following p lines give the details of roads between cities. The i-th road connects two cities with city indices xi and yi, and has a distance zi (1<=i<=p). You can assume that the distance is between 1 and 100.   
  
 No two roads connect the same pair of cities. A road never connects a city with itself. Each road can be traveled in both directions.

## 输出格式

 For each dataset in the input, one line should be output as specified below. An output line should not contain extra characters such as spaces.   
  
 If the traveler can reach the destination, the time needed for the best route (a route with the shortest time) should be printed. The answer should not have an error greater than 0.001. You may output any number of digits after the decimal point, provided that the above accuracy condition is satisfied.   
  
 If the traveler cannot reach the destination, the string "Impossible" should be printed. One cannot reach the destination either when there are no routes leading to the destination, or when the number of tickets is not sufficient. Note that the first letter of "Impossible" is in uppercase, while the other letters are in lowercase.

## 样例 #1

### 输入

```
3 4 3 1 4

3 1 2

1 2 10

2 3 30

3 4 20

2 4 4 2 1

3 1

2 3 3

1 3 3

4 1 2

4 2 5

2 4 3 4 1

5 5

1 2 10

2 3 10

3 4 10

1 2 0 1 2

1

8 5 10 1 5

2 7 1 8 4 5 6 3

1 2 5

2 3 4

3 4 7

4 5 3

1 3 25

2 4 23

3 5 22

1 4 45

2 5 51

1 5 99

0 0 0 0 0
```

### 输出

```
30.000

3.667

Impossible

Impossible

2.856



Since the number of digits after the decimal point is

not specified, the above result is not the only

solution. For example, the following result is also acceptable.



30.0

3.66667

Impossible

Impossible

2.85595
```



---



---

# 题号列表

- SP116 - INTERVAL - Intervals
- SP1700 - TRSTAGE - Traveling by Stagecoach


---

---
title: "MUTDNA - DNA"
layout: "post"
diff: 提高+/省选-
pid: SP13105
tag: ['字符串', '动态规划 DP', '数学', '栈']
---

# MUTDNA - DNA

## 题目描述

我们发现了一种新型 $DNA$ ,这种 $DNA$ 只由 $N$ 个字母 $A$ 构成,在一次辐射中这种 $dna$  变成了由总共 $N$ 个字母  $A$ 和 $B$ 构成,在辐射中只会发生两种异变： 1.将某个任意位置字母反转 ,例如：将第 $K$  位置的 $A$ 变为 $B$ ，或将  $B$ 变为  $A$ . 2.将  $1$ 到 $K$ 位置上的所有字母反转， $1≤K≤N$ 并且  $K$  可以任选. 请你计算将全  $A$  序列转化为最终序列需要最少多少次异变.每发生一个  $1$  异变或  $2$  异变都计入一次总异变数.

## 输入格式

第一行包含正整数  $N(1≤N≤1 000 000)$ ,代表  $DNA$ 的长度. 第二行输入包含一个有  $N$ 个字符的字符串，每个字符都是  $A$ 或  $B$ .

## 输出格式

一行一个数字代表最小的异变数.

感谢@不许雷同 提供的翻译

## 样例 #1

### 输入

```
1:
4
ABBA
```

### 输出

```
1:
2
```



---

---
title: "SP263 - PERIOD - Period"
layout: "post"
diff: 提高+/省选-
pid: SP263
tag: ['字符串']
---

# SP263 - PERIOD - Period

## 题目描述

如果一个字符串 $S$ 是由一个字符串 $T$ 重复 $K$ 次形成的，则称 $T$ 是 $S$ 的循环元。使 $K$ 最大的字符串 $T$ 称为 $S$ 的最小循环元，此时的 $K$ 称为最大循环次数。

现给一个给定长度为 $N$ 的字符串 $S$，对 $S$ 的每一个前缀 $S[1\sim i]$，如果它的最大循环次数大于 $1$，则输出该前缀的长度和最大循环次数。

## 输入格式

第一行将仅包含测试用例的数量 $T (1 \le T \le 10)$。

每个测试用例包含两行。

第一行一个整数 $N (2 \le N \le 1\times 10^6)$ 表示字符串 $S$ 的长度，第二行一个字符串 $S$。

## 输出格式

对于每个测试用例，第一行输出 `Test case #` 和测试点编号。接下来对于每个长度为 $i$ 且 $K > 1$ 的前缀，输出前缀大小 $i$ 和循环次数 $K$，前缀大小按递增顺序排列。在每个测试点后打印一个空白行。

## 说明/提示

Translate by [@qifan_maker](/user/706607).

## 样例 #1

### 输入

```
2
3
aaa
12
aabaabaabaab
```

### 输出

```
Test case #1
2 2
3 3

Test case #2
2 2
6 2
9 3
12 4
```



---

---
title: "TRIP - Trip"
layout: "post"
diff: 提高+/省选-
pid: SP33
tag: ['字符串', '递归', '枚举']
---

# TRIP - Trip

## 题目描述

Alice and Bob want to go on holiday. Each of them has drawn up a list of cities to be visited in turn. A list may contain a city more than once. As they want to travel together, they have to agree upon a common route. No one wants to change the order of the cities on his list or add other cities. Therefore they have no choice but to remove some cities from the list. Of course the common route is to involve as much sight-seeing in cities as possible. There are exactly 26 cities in the region. Therefore they are encoded on the lists as lower case letters from 'a' to 'z'.

## 输入格式

The first line of input contains a number T <= 10 that indicates the number of test cases to follow. Each test case consists of two lines; the first line is the list of Alice, the second line is the list of Bob. Each list consists of 1 to 80 lower case letters.

## 输出格式

The output for each test case should contain all different trips exactly once that meet the conditions described above. There is at least one such trip, but never more than 1000 different ones. You should order the trips in lexicographic order. Print one blank line between the output of different test cases.

## 样例 #1

### 输入

```
1
abcabcaa
acbacba
```

### 输出

```
ababa
abaca
abcba
acaba
acaca
acbaa
acbca
```



---

---
title: "TWINSNOW - Snowflakes"
layout: "post"
diff: 提高+/省选-
pid: SP4354
tag: ['字符串']
---

# TWINSNOW - Snowflakes

## 题目描述

你可能听说过，没有两片雪花是相同的。你要写一个程序，判断这是不是真的。你的程序会读到一些有关于这些雪花的信息，找到一对完全相同的雪花。每片雪花有六个角。对于每个雪花，你的程序会获得每个角的长度。我们认为两片雪花相同，当且仅当它们各自从某一个角开始，逆时针或顺时针记录长度，能得到两个相同的六元组。

## 输入格式

-第一行只有一个数字n，代表雪花的数量。

-接下来会有n行，每一行描述了一片雪花。每片雪花会按逆时针或顺时针给出六个角的长度a1,a2...a6。我们认为两片雪花相同，当且仅当它们各自从某一个角开始，逆时针或顺时针记录长度，能得到两个相同的六元组。例如，同一片雪花可以被描述为1 2 3 4 5 6 或 4 3 2 1 6 5。

## 输出格式

如果没有两片雪花是相同的，请输出  :  
_No two snowflakes are alike. _

否则，请输出：

_Twin snowflakes found._

# 输入输出样例
暂无测试点



---

---
title: "CF25E - Test"
layout: "post"
diff: 提高+/省选-
pid: SP7155
tag: ['字符串', '枚举', 'KMP 算法']
---

# CF25E - Test

## 题目描述

### 题目翻译

Bob 出了一道字符串题，题目的输入是一个字符串。

毒瘤的 Bob 写了 $3$ 个程序，但他发现了一个悲剧：

1. 当输入的字符串有子串 $s_1$ 时，程序 $1$ 会 WA；

1. 当输入的字符串有子串 $s_2$ 时，程序 $2$ 会死循环；

1. 当输入的字符串有子串 $s_3$ 时，程序 $3$ 会 MLE。

当然，可以假定其他情况下程序不会出锅。

Bob 非常毒瘤，他想找一个最短的输入字符串 $ss$，使得 $3$ 个程序都过不了。请输出最小的长度。

## 输入格式

**多组数据**，每组数据 $3$ 行，每行一个字符串，分别代表 $s_1,s_2,s_3$，只含小写字母。

## 输出格式

对于每组数据，输出一个整数代表最小长度，然后换行。

#### 数据规模与约定

对于 $100\%$ 的数据， $1\leq |s_1|,|s_2|,|s_3|\leq 10^5$。

## 样例 #1

### 输入

```
ab
bc
cd
abacaba
abaaba
x

```

### 输出

```
4
11

```



---



---

# 题号列表

- SP13105 - MUTDNA - DNA
- SP263 - SP263 - PERIOD - Period
- SP33 - TRIP - Trip
- SP4354 - TWINSNOW - Snowflakes
- SP7155 - CF25E - Test


---

---
title: "INTERVAL - Intervals"
layout: "post"
diff: 提高+/省选-
pid: SP116
tag: ['图论建模', '差分约束', '差分']
---

# INTERVAL - Intervals

## 题目描述

有 $n$ 个区间，在区间 $[a_i,b_i]$ 中至少取任意互不相同的 $c_i$ 个整数。求在满足 $n$ 个区间的情况下，至少要取多少个正整数。

## 输入格式

**本题有多组数据**。

第一行的一个整数 $T$ 表示数据个数。

对于每组数据：

第一行包含一个整数 $n(1\leq n\leq 50000)$ 表示区间数。

以下 $n$ 行描述区间。

输入的第 $i+1$ 行包含三个整数 $a_i,b_i,c_i$，由空格分开。其中 $0\leq a_i\leq b_i\leq 50000，1\leq c_i\leq b_i-a_i+1$。

## 输出格式

对于每组数据，输出一个对于 $n$ 个区间 $[a_i,b_i]$ 
至少取 $c_i$ 个不同整数的数的总个数。

### 样例

input：

```
1
5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1
```

output：

```
6
```


### 样例解释

可以取 $3,4,5,8,9,10$，为符合条件且取数个数最少的一组解。

## 样例 #1

### 输入

```
1
5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1
```

### 输出

```
6
```



---



---

# 题号列表

- SP116 - INTERVAL - Intervals


---

---
title: "SOLIT - Solitaire"
layout: "post"
diff: 提高+/省选-
pid: SP120
tag: ['广度优先搜索 BFS', '折半搜索 meet in the middle']
---

# SOLIT - Solitaire

## 题目描述

Solitaire是一款在8x8棋盘上玩的游戏。棋盘的行和列分别为1到8，从顶部到底部以及从左到右依次编号。

棋盘上有4个相同的棋子。在每一次移动中，一个棋子可以：

- 移动一格到一个相邻的空格（向上、向下、向左或向右）

- 跳过另一个相邻的棋子到与之相邻一个空格（向上、向下、向左或向右）

## 输入格式

输入数据以一个整数t开头，表示测试案例数。然后是t个案例。

对于每个案例，两行中每一行包含8个整数a1,a2,...,a8，每个数之间由一个空格分开，以描述每个棋盘上棋子的分布。整数a（2j-1）和a（2j）(1 <= j <= 4) 分别描述了一个棋子的行与列的位置。

## 输出格式

对于每个测试案例，输出数据应当包含一个单词——

如果由输入数据第一行所描述的棋盘分布可以在8次移动之内转变为第二行所描述的棋盘分布，则输出“YES”，否则输出“NO”。

## 样例 #1

### 输入

```
1

4 4 4 5 5 4 6 5

2 4 3 3 3 6 4 6
```

### 输出

```
YES
```



---



---

# 题号列表

- SP120 - SOLIT - Solitaire


---

---
title: "RACETIME - Race Against Time"
layout: "post"
diff: 提高+/省选-
pid: SP3261
tag: ['枚举', '排序', '分块']
---

# RACETIME - Race Against Time

## 题目描述

现在有$n(1<=n<=1e5)$只奶牛站成一排，每只奶牛手中都拿着一个数字$A_i(0<=A_i<=1e9)$

现在$FJ$要执行$Q(1<=Q<=50000)$个操作，每个操作可能是下面两种操作之一：

$1.$ $M$ $i$ $X$ ：将第$i$只奶牛手上的数字$A_i$替换为$X$

$2.$ $C$ $l$ $r$ $K$：询问区间$[l,r]$内有多少只奶牛手上拿的数字$A_i\le K$

作为$FJ$的好朋友，请你对每一个$2$操作输出答案

由于$FJ$非常蕉♂躁，所以他只允许你在$1s$内回答这些问题

## 输入格式

第一行输入两个正整数$n,Q$，含义如上

接下来$n$行，每一行输入一个正整数$A_i$，表示初始时第$i$只奶牛手上拿的数字$A_i$

接下来有$Q$行输入，代表$FJ$接下来要进行的$Q$个操作，格式如上文

## 输出格式

对于每一个$2$操作，请你输出满足条件的奶牛个数。每个答案占一行

## 样例 #1

### 输入

```
4 6

3

4

1

7

C 2 4 4

M 4 1

C 2 4 4

C 1 4 5

M 2 10

C 1 3 9
```

### 输出

```
2

3

4

2
```



---



---

# 题号列表

- SP3261 - RACETIME - Race Against Time


---

---
title: "SUBSET - Balanced Cow Subsets"
layout: "post"
diff: 提高+/省选-
pid: SP11469
tag: ['搜索', '折半搜索 meet in the middle']
---

# SUBSET - Balanced Cow Subsets

## 题目描述

Farmer John's owns N cows (2 <= N <= 20), where cow i produces M(i) units of milk each day (1 <= M(i) <= 100,000,000).

 FJ wants to streamline the process of milking his cows every day, so he installs a brand new milking machine in his barn.

Unfortunately, the machine turns out to be far too sensitive: it only works properly if the cows on the left side of the

barn have the exact same total milk output as the cows on the right side of the barn!

Let us call a subset of cows "balanced" if it can be partitioned into two groups having equal milk output.

 Since only a balanced subset of cows can make the milking machine work, FJ wonders how many subsets of his N cows are balanced.

 Please help him compute this quantity.

 `INPUT FORMAT:` `* Line 1: The integer N.` `* Lines 2..1+N: Line i+1 contains M(i).` `SAMPLE INPUT` `4 ` `1 ` `2 ` `3 ` `4` `INPUT DETAILS:` `There are 4 cows, with milk outputs 1, 2, 3, and 4.` `OUTPUT FORMAT: ` `* Line 1: The number of balanced subsets of cows. ` `SAMPLE OUTPUT:` `3` `OUTPUT DETAILS: ` `There are three balanced subsets: the subset {1,2,3}, which can be partitioned into {1,2} and {3}, the subset {1,3,4}, ` `which can be partitioned into {1,3} and {4}, and the subset {1,2,3,4} which can be partitioned into {1,4} and {2,3}.`



---

---
title: "SOLIT - Solitaire"
layout: "post"
diff: 提高+/省选-
pid: SP120
tag: ['广度优先搜索 BFS', '折半搜索 meet in the middle']
---

# SOLIT - Solitaire

## 题目描述

Solitaire是一款在8x8棋盘上玩的游戏。棋盘的行和列分别为1到8，从顶部到底部以及从左到右依次编号。

棋盘上有4个相同的棋子。在每一次移动中，一个棋子可以：

- 移动一格到一个相邻的空格（向上、向下、向左或向右）

- 跳过另一个相邻的棋子到与之相邻一个空格（向上、向下、向左或向右）

## 输入格式

输入数据以一个整数t开头，表示测试案例数。然后是t个案例。

对于每个案例，两行中每一行包含8个整数a1,a2,...,a8，每个数之间由一个空格分开，以描述每个棋盘上棋子的分布。整数a（2j-1）和a（2j）(1 <= j <= 4) 分别描述了一个棋子的行与列的位置。

## 输出格式

对于每个测试案例，输出数据应当包含一个单词——

如果由输入数据第一行所描述的棋盘分布可以在8次移动之内转变为第二行所描述的棋盘分布，则输出“YES”，否则输出“NO”。

## 样例 #1

### 输入

```
1

4 4 4 5 5 4 6 5

2 4 3 3 3 6 4 6
```

### 输出

```
YES
```



---

---
title: "BST - Binary Search Tree"
layout: "post"
diff: 提高+/省选-
pid: SP3544
tag: ['模拟', '搜索', '平衡树']
---

# BST - Binary Search Tree

## 题目描述

众所周知，二叉搜索树是一棵树，其中每个节点最多具有两个子节点（左子节点和右子节点）。

二叉搜索树的每个节点都有一个权值。对于每个节点如果存在一个权值$X$，则其左子树中的权值小于$X$，右子树中的权值大于$X$.

现在给你一个$1$~$N$（包括$N$）之间的整数序列，其中保证每个数字在序列中只出现一次。

请你将序列建成一颗二叉搜索树，我们规定将第一个数字的值存在根节点中，并按给定的序列顺序插入其他数字。

换句话说，你需要对每个插入的数字运行函数$insert(X$，$root)$：

该函数伪代码如下：

	插入（编号X，节点N）

 		将计数器C增加1      

    	 if X小于节点N中的权值        

        	if N没有左子节点           

            	创建一个权值为X的新节点，并将其设置为节点N的左子节点          
        	else insert（X，节点N的左子节点） 
    	 else if （X大于节点N中的权值） 

        	if N没有右子节点              

            	创建一个权值为X的新节点，并将其设置为节点N的右子节点      

        	else insert（X，节点N的右子节点） 

请你编写一个程序，计算在依次插入每个数字后计数器$C$的值并输出。计数器$C$最初为$0$。

## 输入格式

第一行包含一个正整数$N(1<=N<=300000)$

之后有$N$行，每行一个数字，代表给定的序列。

输入数据保证这些数都是区间$[1,N]$中的整数且不会出现重复

## 输出格式

一共$N$行，每行一个数字，表示按给定序列顺序插入每个数字之后计数器$C$的值

感谢@___new2zy___ 提供的翻译

## 样例 #1

### 输入

```
8
3
5
1
6
8
7
2
4
```

### 输出

```
0
1
2
4
7
11
13
15
```



---

---
title: "ZUMA - ZUMA"
layout: "post"
diff: 提高+/省选-
pid: SP6340
tag: ['动态规划 DP', '搜索', '区间 DP']
---

# ZUMA - ZUMA

## 题目描述

祖玛游戏是这样的：有一列$ N$ 个有颜色的珠子，如果触碰连续 $K$ 个或更多同色的珠子，那么它们就会消失，其余的珠子按照原来顺序接在一起。

现在你每次可以发射任意颜色的珠子，发射在任意位置（开头、结尾以及任意两个之间）。

注意，如果有连续 $K$ 个或更多同色的珠子，你可以不立即消去他们。

问最少需要几发可以消掉所有的珠子。

## 输入格式

第一行 $N,K$

第二行 $N$ 个数 $a_i$，不同的数表示不同的颜色

## 输出格式

一个答案。

【数据规模】
对于所有数据，$1≤N≤100,2≤K≤5,1≤a_i≤100$

## 样例 #1

### 输入

```
2 5
1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 4
3 3 3 3 2 3 1 1 1 3
```

### 输出

```
4
```



---

---
title: "QTREE2 - Query on a tree II"
layout: "post"
diff: 提高+/省选-
pid: SP913
tag: ['倍增', '深度优先搜索 DFS', '最近公共祖先 LCA']
---

# QTREE2 - Query on a tree II

## 题目描述

 You are given a tree (an undirected acyclic connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1. Each edge has an integer value assigned to it, representing its length.

 We will ask you to perfrom some instructions of the following form:

- **DIST a b** : ask for the distance between node **a** and node **b**  
   or
- **KTH a b k** : ask for the **k**-th node on the path from node **a** to node **b**

 **Example:**  
**N** = 6   
 1 2 1 // edge connects node 1 and node 2 has cost 1   
 2 4 1   
 2 5 2   
 1 3 1   
 3 6 2   
  
 Path from node 4 to node 6 is 4 -> 2 -> 1 -> 3 -> 6   
**DIST 4 6** : answer is 5 (1 + 1 + 1 + 2 = 5)   
**KTH 4 6 4** : answer is 3 (the 4-th node on the path from node 4 to node 6 is 3)

## 输入格式

 The first line of input contains an integer **t**, the number of test cases (**t** <= 25). **t** test cases follow.

For each test case:

- In the first line there is an integer **N** (**N** <= 10000)
- In the next **N**-1 lines, the i-th line describes the i-th edge: a line with three integers **a b c** denotes an edge between **a**, **b** of cost **c** (**c** <= 100000)
- The next lines contain instructions **"DIST a b"** or **"KTH a b k"**
- The end of each test case is signified by the string "**DONE**".

There is one blank line between successive tests.

## 输出格式

For each **"DIST"** or **"KTH"** operation, write one integer representing its result.

Print one blank line after each test.

## 样例 #1

### 输入

```
1

6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
DIST 4 6
KTH 4 6 4
DONE
```

### 输出

```
5
3
```



---



---

# 题号列表

- SP11469 - SUBSET - Balanced Cow Subsets
- SP120 - SOLIT - Solitaire
- SP3544 - BST - Binary Search Tree
- SP6340 - ZUMA - ZUMA
- SP913 - QTREE2 - Query on a tree II


---

---
title: "MUTDNA - DNA"
layout: "post"
diff: 提高+/省选-
pid: SP13105
tag: ['字符串', '动态规划 DP', '数学', '栈']
---

# MUTDNA - DNA

## 题目描述

我们发现了一种新型 $DNA$ ,这种 $DNA$ 只由 $N$ 个字母 $A$ 构成,在一次辐射中这种 $dna$  变成了由总共 $N$ 个字母  $A$ 和 $B$ 构成,在辐射中只会发生两种异变： 1.将某个任意位置字母反转 ,例如：将第 $K$  位置的 $A$ 变为 $B$ ，或将  $B$ 变为  $A$ . 2.将  $1$ 到 $K$ 位置上的所有字母反转， $1≤K≤N$ 并且  $K$  可以任选. 请你计算将全  $A$  序列转化为最终序列需要最少多少次异变.每发生一个  $1$  异变或  $2$  异变都计入一次总异变数.

## 输入格式

第一行包含正整数  $N(1≤N≤1 000 000)$ ,代表  $DNA$ 的长度. 第二行输入包含一个有  $N$ 个字符的字符串，每个字符都是  $A$ 或  $B$ .

## 输出格式

一行一个数字代表最小的异变数.

感谢@不许雷同 提供的翻译

## 样例 #1

### 输入

```
1:
4
ABBA
```

### 输出

```
1:
2
```



---

---
title: "GCDEX - GCD Extreme"
layout: "post"
diff: 提高+/省选-
pid: SP3871
tag: ['数学', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCDEX - GCD Extreme

## 题目描述

得定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数 $n$ ，如果 $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 10^6$，不超过 $20000$ 组数据。

## 样例 #1

### 输入

```
10
100
200000
0
```

### 输出

```
67
13015
143295493160

Time limit has been changed. Some AC solutions get TLE
```



---



---

# 题号列表

- SP13105 - MUTDNA - DNA
- SP3871 - GCDEX - GCD Extreme


---

---
title: "TRSTAGE - Traveling by Stagecoach"
layout: "post"
diff: 提高+/省选-
pid: SP1700
tag: ['状态合并', '图论建模', '最短路']
---

# TRSTAGE - Traveling by Stagecoach

## 题目描述

Once upon a time, there was a traveler.   
  
 He plans to travel using stagecoaches (horse wagons). His starting point and destination are fixed, but he cannot determine his route. Your job in this problem is to write a program which determines the route for him.   
  
 There are several cities in the country, and a road network connecting them. If there is a road between two cities, one can travel by a stagecoach from one of them to the other. A coach ticket is needed for a coach ride. The number of horses is specified in each of the tickets. Of course, with more horses, the coach runs faster.   
  
 At the starting point, the traveler has a number of coach tickets. By considering these tickets and the information on the road network, you should find the best possible route that takes him to the destination in the shortest time. The usage of coach tickets should be taken into account.   
  
 The following conditions are assumed.

- A coach ride takes the traveler from one city to another directly connected by a road. In other words, on each arrival to a city, he must change the coach.
- Only one ticket can be used for a coach ride between two cities directly connected by a road.
- Each ticket can be used only once.
- The time needed for a coach ride is the distance between two cities divided by the number of horses.
- The time needed for the coach change should be ignored.

## 输入格式

The input consists of multiple datasets, each in the following format. The last dataset is followed by a line containing five zeros (separated by a space).   
  
 n m p a b  
 t1 t2 ... tn  
 x1 y1 z1  
 x2 y2 z2  
 ...  
 xp yp zp  
  
  
 Every input item in a dataset is a non-negative integer. If a line contains two or more input items, they are separated by a space.  
  
 n is the number of coach tickets. You can assume that the number of tickets is between 1 and 8. m is the number of cities in the network. You can assume that the number of cities is between 2 and 30. p is the number of roads between cities, which may be zero.   
  
 a is the city index of the starting city. b is the city index of the destination city. a is not equal to b. You can assume that all city indices in a dataset (including the above two) are between 1 and m.   
  
 The second line of a dataset gives the details of coach tickets. ti is the number of horses specified in the i-th coach ticket (1<=i<=n). You can assume that the number of horses is between 1 and 10.   
  
 The following p lines give the details of roads between cities. The i-th road connects two cities with city indices xi and yi, and has a distance zi (1<=i<=p). You can assume that the distance is between 1 and 100.   
  
 No two roads connect the same pair of cities. A road never connects a city with itself. Each road can be traveled in both directions.

## 输出格式

 For each dataset in the input, one line should be output as specified below. An output line should not contain extra characters such as spaces.   
  
 If the traveler can reach the destination, the time needed for the best route (a route with the shortest time) should be printed. The answer should not have an error greater than 0.001. You may output any number of digits after the decimal point, provided that the above accuracy condition is satisfied.   
  
 If the traveler cannot reach the destination, the string "Impossible" should be printed. One cannot reach the destination either when there are no routes leading to the destination, or when the number of tickets is not sufficient. Note that the first letter of "Impossible" is in uppercase, while the other letters are in lowercase.

## 样例 #1

### 输入

```
3 4 3 1 4

3 1 2

1 2 10

2 3 30

3 4 20

2 4 4 2 1

3 1

2 3 3

1 3 3

4 1 2

4 2 5

2 4 3 4 1

5 5

1 2 10

2 3 10

3 4 10

1 2 0 1 2

1

8 5 10 1 5

2 7 1 8 4 5 6 3

1 2 5

2 3 4

3 4 7

4 5 3

1 3 25

2 4 23

3 5 22

1 4 45

2 5 51

1 5 99

0 0 0 0 0
```

### 输出

```
30.000

3.667

Impossible

Impossible

2.856



Since the number of digits after the decimal point is

not specified, the above result is not the only

solution. For example, the following result is also acceptable.



30.0

3.66667

Impossible

Impossible

2.85595
```



---



---

# 题号列表

- SP1700 - TRSTAGE - Traveling by Stagecoach


---

---
title: "STC02 - Antisymmetry"
layout: "post"
diff: 提高+/省选-
pid: SP15569
tag: ['二分', '枚举', '哈希 hashing', 'Manacher 算法']
---

# STC02 - Antisymmetry

## 题目描述

对于一个 01 字符串，如果将这个字符串 0 和 1 取反后，再将整个串反过来和原串一样，就称作「反对称」字符串。比如 00001111 和 010101 就是反对称的，而 1001 就不是。 现在给出一个长度为 n 的 01 字符串，求它有多少个子串是反对称的，注意这里相同的子串出现在不同的位置会被重复计算。

## 输出格式

Translated by @xzjds



---

---
title: "TLE - Time Limit Exceeded"
layout: "post"
diff: 提高+/省选-
pid: SP2829
tag: ['枚举', '状态合并', '前缀和']
---

# TLE - Time Limit Exceeded

## 题目描述

Given integers N (1 ≤ N ≤ 50) and M (1 ≤ M ≤ 15), compute the number of sequences a $ _{1} $ , ..., a $ _{N} $ such that:

- 0 ≤ a $ _{i} $ < 2 $ ^{M} $
- a $ _{i} $ is not divisible by c $ _{i} $ (0 < c $ _{i} $ ≤ 2 $ ^{M} $ )
- a $ _{i} $ & a $ _{i+1} $ = 0 (that is, a $ _{i} $ and a $ _{i+1} $ have no common bits in their binary representation)

## 输入格式

The first line contains the number of test cases, T (1 ≤ T ≤ 10). For each test case, the first line contains the integers N and M, and the second line contains the integers c $ _{1} $ , ..., c $ _{N} $ .

## 输出格式

For each test case, output a single integer: the number of sequences described above, modulo 1,000,000,000.

## 样例 #1

### 输入

```
1

2 2

3 2
```

### 输出

```
1
```



---

---
title: "RACETIME - Race Against Time"
layout: "post"
diff: 提高+/省选-
pid: SP3261
tag: ['枚举', '排序', '分块']
---

# RACETIME - Race Against Time

## 题目描述

现在有$n(1<=n<=1e5)$只奶牛站成一排，每只奶牛手中都拿着一个数字$A_i(0<=A_i<=1e9)$

现在$FJ$要执行$Q(1<=Q<=50000)$个操作，每个操作可能是下面两种操作之一：

$1.$ $M$ $i$ $X$ ：将第$i$只奶牛手上的数字$A_i$替换为$X$

$2.$ $C$ $l$ $r$ $K$：询问区间$[l,r]$内有多少只奶牛手上拿的数字$A_i\le K$

作为$FJ$的好朋友，请你对每一个$2$操作输出答案

由于$FJ$非常蕉♂躁，所以他只允许你在$1s$内回答这些问题

## 输入格式

第一行输入两个正整数$n,Q$，含义如上

接下来$n$行，每一行输入一个正整数$A_i$，表示初始时第$i$只奶牛手上拿的数字$A_i$

接下来有$Q$行输入，代表$FJ$接下来要进行的$Q$个操作，格式如上文

## 输出格式

对于每一个$2$操作，请你输出满足条件的奶牛个数。每个答案占一行

## 样例 #1

### 输入

```
4 6

3

4

1

7

C 2 4 4

M 4 1

C 2 4 4

C 1 4 5

M 2 10

C 1 3 9
```

### 输出

```
2

3

4

2
```



---

---
title: "TRIP - Trip"
layout: "post"
diff: 提高+/省选-
pid: SP33
tag: ['字符串', '递归', '枚举']
---

# TRIP - Trip

## 题目描述

Alice and Bob want to go on holiday. Each of them has drawn up a list of cities to be visited in turn. A list may contain a city more than once. As they want to travel together, they have to agree upon a common route. No one wants to change the order of the cities on his list or add other cities. Therefore they have no choice but to remove some cities from the list. Of course the common route is to involve as much sight-seeing in cities as possible. There are exactly 26 cities in the region. Therefore they are encoded on the lists as lower case letters from 'a' to 'z'.

## 输入格式

The first line of input contains a number T <= 10 that indicates the number of test cases to follow. Each test case consists of two lines; the first line is the list of Alice, the second line is the list of Bob. Each list consists of 1 to 80 lower case letters.

## 输出格式

The output for each test case should contain all different trips exactly once that meet the conditions described above. There is at least one such trip, but never more than 1000 different ones. You should order the trips in lexicographic order. Print one blank line between the output of different test cases.

## 样例 #1

### 输入

```
1
abcabcaa
acbacba
```

### 输出

```
ababa
abaca
abcba
acaba
acaca
acbaa
acbca
```



---

---
title: "ROADS - Roads"
layout: "post"
diff: 提高+/省选-
pid: SP338
tag: ['枚举', '剪枝']
---

# ROADS - Roads

## 题目描述

题面描述  
有标号为1……n的城市与单行道相连。对于每条道路有两个与之相关的参数：道路的长度以及需要支付的费用（用硬币的数量表示）  
鲍勃和爱丽丝曾经生活在城市1。在注意到爱丽丝在他们喜欢玩的卡牌游戏中作弊后，鲍勃决定与爱丽丝分手并搬走——去城市n。他希望尽快到达那里——越快越好，然而他现在有些现金短缺。
我们希望帮助鲍勃找到从城市1到城市n的一条最短路径——但他必须用他现有的钱支付得起。

## 输入格式

输入的第一行含有一个整数t代表测试样例的组数。下面是t组测试样例。  
对于每组测试数据，第一行含有一个整数K（0<=K<=10000)，代表鲍勃所能支付得起的最大费用。  
第二行含有一个整数N（2<=N<=100)，代表城市总数。  
第三行含有一个整数R（1<=R<=10000)，代表道路的总数。  
接下来R行每行用四个整数S,D,L,T，以单个空格分隔：  
S表示出发点城市标号（1<=S<=N)；  
D表示目的地城市标号（1<=D<=N)；  
L是该道路的长度（1<=L<=100)；
T表示经过该道路的费用(0<=T<=100)。  
注意不同的道路可能拥有相同的起点和终点。

## 输出格式

对于每组测试样例，输出单独的一行表示当花费小于等于K时最短路径的长度。如果不存在这样的路径，输出-1。

## 样例 #1

### 输入

```
2

5

6

7

1 2 2 3

2 4 3 3

3 4 2 4

1 3 4 1

4 6 2 1

3 5 2 0

5 4 3 2

0

4

4

1 4 5 2

1 2 1 0

2 3 1 1

3 4 1 0
```

### 输出

```
11

-1
```



---

---
title: "FENCE3 - Electric Fences"
layout: "post"
diff: 提高+/省选-
pid: SP4587
tag: ['模拟', '枚举', '模拟退火']
---

# FENCE3 - Electric Fences

## 题目描述

　　农夫约翰已经决定建造电网。他已经把他的农田围成一些奇怪的形状，现在必须找出安放电源的最佳位置。
  
　　对于段电网都必须从电源拉出一条电线。电线可以穿过其他电网或者跨过其他电线。电线能够以任意角度铺设，从电源连接到一段电网的任意一点上（也就是，这段电网的端点上或者在其之间的任意一点上）。这里所说的“一段电网”指的是呈一条线段状的电网，并不是连在一起的几段电网。若几段电网连在一起，那么也要分别给这些电网提供电力。
  
　　已知所有的 F（1 <= F <= 150）段电网的位置（电网总是和坐标轴平行，并且端点的坐标总是整数，0 <= X,Y <= 100）。你的程序要计算连接电源和每段电网所需的电线的最小总长度，还有电源的最佳坐标。
  
　　电源的最佳坐标可能在农夫约翰的农田中的任何一个位置，并不一是整数。

## 输入格式

　　第一行包括 F ——电网的数量。
　　下面的 F 行每行包括两个 X，Y 对，表示这段电网的两个端点。

## 输出格式

只有一行，输出三个浮点数，相邻两个之间留一个空格。

假定你的电脑的输出库会正确地对小数进行四舍五入。
这三个数是： 电源最佳坐标的 X 值，
电源最佳坐标的 Y 值，和
需要的电线的总长度（要最小）。

## 样例 #1

### 输入

```
3

0 0 0 1

2 0 2 1

0 3 2 3
```

### 输出

```
1.0 1.6 3.7
```



---

---
title: "SAM - Toy Cars"
layout: "post"
diff: 提高+/省选-
pid: SP688
tag: ['贪心', '枚举']
---

# SAM - Toy Cars

## 题目描述

Jasio 是一个只有三岁的小男孩，他喜欢玩玩具车。他有 $n$ 辆玩具车被保存在书架上。

架子上的玩具车 Jasio 拿不到，但地板上的他可以拿到。Jasio 的母亲会帮 Jasio 拿架子上的玩具车到地板上。

地板最多只能放 $k$ 辆玩具车。

当地板已经放了 $k$ 辆玩具车时，Jasio 的母亲都会从地板上先拿走一个玩具车放回书架，再拿来 Jasio 想要的玩具车。

现在 Jasio 一共想依次玩 $p$ 个玩具车，问 Jasio 的母亲最少需要拿几次玩具车。（只算拿下来的，不算拿上去的）

## 输入格式

第一行一个整数 $t$，表示有 $t$ 组数据。

接下来一行有三个整数 $n,k$ 和 $p$。

接下来 $p$ 行，每一行有且仅有一个整数 $a_i$，表示 Jasio 想玩的玩具玩家车编号。

## 输出格式

输出一行一个整数，表示最少 Jasio 的母亲最少需要拿玩家车的次数。

## 说明/提示

对于 $100\%$ 的数据：$1\le t\le 16$，$1\le k\le n\le 10^5$，$1\le p\le 5\times 10^5$，$1\le a_i\le n$。

感谢 @Utilokasteinn 提供的翻译。

## 样例 #1

### 输入

```
1
3 2 7
1
2
3
1
3
1
2
```

### 输出

```
4
```



---

---
title: "CF25E - Test"
layout: "post"
diff: 提高+/省选-
pid: SP7155
tag: ['字符串', '枚举', 'KMP 算法']
---

# CF25E - Test

## 题目描述

### 题目翻译

Bob 出了一道字符串题，题目的输入是一个字符串。

毒瘤的 Bob 写了 $3$ 个程序，但他发现了一个悲剧：

1. 当输入的字符串有子串 $s_1$ 时，程序 $1$ 会 WA；

1. 当输入的字符串有子串 $s_2$ 时，程序 $2$ 会死循环；

1. 当输入的字符串有子串 $s_3$ 时，程序 $3$ 会 MLE。

当然，可以假定其他情况下程序不会出锅。

Bob 非常毒瘤，他想找一个最短的输入字符串 $ss$，使得 $3$ 个程序都过不了。请输出最小的长度。

## 输入格式

**多组数据**，每组数据 $3$ 行，每行一个字符串，分别代表 $s_1,s_2,s_3$，只含小写字母。

## 输出格式

对于每组数据，输出一个整数代表最小长度，然后换行。

#### 数据规模与约定

对于 $100\%$ 的数据， $1\leq |s_1|,|s_2|,|s_3|\leq 10^5$。

## 样例 #1

### 输入

```
ab
bc
cd
abacaba
abaaba
x

```

### 输出

```
4
11

```



---



---

# 题号列表

- SP15569 - STC02 - Antisymmetry
- SP2829 - TLE - Time Limit Exceeded
- SP3261 - RACETIME - Race Against Time
- SP33 - TRIP - Trip
- SP338 - ROADS - Roads
- SP4587 - FENCE3 - Electric Fences
- SP688 - SAM - Toy Cars
- SP7155 - CF25E - Test


---

---
title: "MUTDNA - DNA"
layout: "post"
diff: 提高+/省选-
pid: SP13105
tag: ['字符串', '动态规划 DP', '数学', '栈']
---

# MUTDNA - DNA

## 题目描述

我们发现了一种新型 $DNA$ ,这种 $DNA$ 只由 $N$ 个字母 $A$ 构成,在一次辐射中这种 $dna$  变成了由总共 $N$ 个字母  $A$ 和 $B$ 构成,在辐射中只会发生两种异变： 1.将某个任意位置字母反转 ,例如：将第 $K$  位置的 $A$ 变为 $B$ ，或将  $B$ 变为  $A$ . 2.将  $1$ 到 $K$ 位置上的所有字母反转， $1≤K≤N$ 并且  $K$  可以任选. 请你计算将全  $A$  序列转化为最终序列需要最少多少次异变.每发生一个  $1$  异变或  $2$  异变都计入一次总异变数.

## 输入格式

第一行包含正整数  $N(1≤N≤1 000 000)$ ,代表  $DNA$ 的长度. 第二行输入包含一个有  $N$ 个字符的字符串，每个字符都是  $A$ 或  $B$ .

## 输出格式

一行一个数字代表最小的异变数.

感谢@不许雷同 提供的翻译

## 样例 #1

### 输入

```
1:
4
ABBA
```

### 输出

```
1:
2
```



---

---
title: "CTGAME - City Game"
layout: "post"
diff: 提高+/省选-
pid: SP277
tag: ['栈']
---

# CTGAME - City Game

## 题目描述

Bob is a strategy game programming specialist. In his new city building game the gaming environment is as follows: a city is built up by areas, in which there are streets, trees, factories and buildings. There is still some space in the area that is unoccupied. The strategic task of his game is to win as much rent money from these free spaces. To win rent money you must erect buildings, that can only be rectangular, as long and wide as you can. Bob is trying to find a way to build the biggest possible building in each area. But he comes across some problems - he is not allowed to destroy already existing buildings, trees, factories and streets in the area he is building in.

Each area has its width and length. The area is divided into a grid of equal square units.The rent paid for each unit on which you're building stands is 3$.

Your task is to help Bob solve this problem. The whole city is divided into **K** areas. Each one of the areas is rectangular and has a different grid size with its own length **M** and width **N**. The existing occupied units are marked with the symbol **R**. The unoccupied units are marked with the symbol **F**.

## 输入格式

The first line of the input contains an integer **K** - determining the number of datasets. Next lines contain the area descriptions. One description is defined in the following way: The first line contains two integers-area length **M**<=1000 and width **N**<=1000, separated by a blank space. The next **M** lines contain **N** symbols that mark the reserved or free grid units,separated by a blank space. The symbols used are:

**R** - reserved unit

**F** - free unit

In the end of each area description there is a separating line.

## 输出格式

For each data set in the input print on a separate line, on the standard output, the integer that represents the profit obtained by erecting the largest building in the area encoded by the data set.

## 样例 #1

### 输入

```
2

5 6

R F F F F F

F F F F F F

R R R F F F

F F F F F F

F F F F F F



5 5

R R R R R

R R R R R

R R R R R

R R R R R

R R R R R
```

### 输出

```
45

0
```



---



---

# 题号列表

- SP13105 - MUTDNA - DNA
- SP277 - CTGAME - City Game


---

---
title: "USUBQSUB - Update Sub-Matrix & Query Sub-Matrix"
layout: "post"
diff: 提高+/省选-
pid: SP15914
tag: ['树状数组']
---

# USUBQSUB - Update Sub-Matrix & Query Sub-Matrix

## 题目描述

Updating and querying 1 dimensional arrays is a popular question. How about updating and quering sub-matrices of a matrix?

A sub-matrix will be depicted as (a, b), (c, d). This implies that it will include all the cells (x, y) such that a<=x<=c and b<=y<=d.

The matrix is indexed from \[1..N\]\[1..N\], where N is the size.

You are given a matrix of size NxN, with each element initially set to 0. There are M queries and each query can be of one of the two types:

1 x1 y1 x2 y2: This query asks you to return the sum of all the elements in the sub-matrix (x1, y1), (x2, y2).

2 x1 y1 x2 y2 K: This query asks you to add K to each element in the sub-matrix (x1, y1), (x2, y2).

## 输入格式

The first line of input contains N, M.

The next M lines contain queries in the same forms as stated above.

You may assume that x1<=x2 and y1<=y2 for all queries.

Also N<=1000 and M<=10 $ ^{5} $ . K<=10 $ ^{9} $

## 输出格式

The answer to all the queries wherein you need to return the sum of elements in the sub-matrix, i.e., all the queries of type 1.



---

---
title: "DQUERY - D-query"
layout: "post"
diff: 提高+/省选-
pid: SP3267
tag: ['莫队', '线段树', '树状数组', '可持久化线段树']
---

# DQUERY - D-query

## 题目描述

[English](/problems/DQUERY/en/) [Vietnamese](/problems/DQUERY/vn/)Given a sequence of n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ .

## 输入格式

- Line 1: n (1 ≤ n ≤ 30000).
- Line 2: n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ (1 ≤ a $ _{i} $ ≤ 10 $ ^{6} $ ).
- Line 3: q (1 ≤ q ≤ 200000), the number of d-queries.
- In the next q lines, each line contains 2 numbers i, j representing a d-query (1 ≤ i ≤ j ≤ n).

## 输出格式

- For each d-query (i, j), print the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ in a single line.

## 样例 #1

### 输入

```
5
1 1 2 1 3
3
1 5
2 4
3 5
```

### 输出

```
3
2
3
```



---



---

# 题号列表

- SP15914 - USUBQSUB - Update Sub-Matrix & Query Sub-Matrix
- SP3267 - DQUERY - D-query


---

---
title: "VOCV - Con-Junctions"
layout: "post"
diff: 提高+/省选-
pid: SP666
tag: ['动态规划 DP', '背包 DP', '概率论']
---

# VOCV - Con-Junctions

## 题目描述

给一个 $n$ 个节点和 $n - 1$ 条边的树，现在要在一些节点放置灯最终点亮所有的边。

当一个节点上放置了一盏灯时，所有与它相连的边都会被点亮，且每一条边只需一个端点被点亮即认为被点亮。

试求最少的放灯数量和当放灯数量最少时的方案数。请将方案数结果模 $10007$ 输出。

数据范围：$n \le 100010$。

## 输入格式

在文件的第一行，一个整数 $t(t \le 20)$，表示该测试点中有 $t$ 组测试数据。

接下来若干行描述每个测试数据中树的情况：

首先包含一个 $n$，代表这个测试数据中树的节点个数。

接下来 $n - 1$ 行，每一行有两个整数 $x,y$，代表有一条双向边连接着两个节点 $x$ 和 $y$。

## 输出格式

对于每一个测试数据，请输出最少的放灯数量和当放灯数量最少时的方案数。请将方案数结果模 $10007$ 输出。

## 样例 #1

### 输入

```
2
4
1 2
2 3
3 4
3
1 2
1 3
```

### 输出

```
2 3
1 1
```



---



---

# 题号列表

- SP666 - VOCV - Con-Junctions


---

---
title: "BST - Binary Search Tree"
layout: "post"
diff: 提高+/省选-
pid: SP3544
tag: ['模拟', '搜索', '平衡树']
---

# BST - Binary Search Tree

## 题目描述

众所周知，二叉搜索树是一棵树，其中每个节点最多具有两个子节点（左子节点和右子节点）。

二叉搜索树的每个节点都有一个权值。对于每个节点如果存在一个权值$X$，则其左子树中的权值小于$X$，右子树中的权值大于$X$.

现在给你一个$1$~$N$（包括$N$）之间的整数序列，其中保证每个数字在序列中只出现一次。

请你将序列建成一颗二叉搜索树，我们规定将第一个数字的值存在根节点中，并按给定的序列顺序插入其他数字。

换句话说，你需要对每个插入的数字运行函数$insert(X$，$root)$：

该函数伪代码如下：

	插入（编号X，节点N）

 		将计数器C增加1      

    	 if X小于节点N中的权值        

        	if N没有左子节点           

            	创建一个权值为X的新节点，并将其设置为节点N的左子节点          
        	else insert（X，节点N的左子节点） 
    	 else if （X大于节点N中的权值） 

        	if N没有右子节点              

            	创建一个权值为X的新节点，并将其设置为节点N的右子节点      

        	else insert（X，节点N的右子节点） 

请你编写一个程序，计算在依次插入每个数字后计数器$C$的值并输出。计数器$C$最初为$0$。

## 输入格式

第一行包含一个正整数$N(1<=N<=300000)$

之后有$N$行，每行一个数字，代表给定的序列。

输入数据保证这些数都是区间$[1,N]$中的整数且不会出现重复

## 输出格式

一共$N$行，每行一个数字，表示按给定序列顺序插入每个数字之后计数器$C$的值

感谢@___new2zy___ 提供的翻译

## 样例 #1

### 输入

```
8
3
5
1
6
8
7
2
4
```

### 输出

```
0
1
2
4
7
11
13
15
```



---

---
title: "FENCE3 - Electric Fences"
layout: "post"
diff: 提高+/省选-
pid: SP4587
tag: ['模拟', '枚举', '模拟退火']
---

# FENCE3 - Electric Fences

## 题目描述

　　农夫约翰已经决定建造电网。他已经把他的农田围成一些奇怪的形状，现在必须找出安放电源的最佳位置。
  
　　对于段电网都必须从电源拉出一条电线。电线可以穿过其他电网或者跨过其他电线。电线能够以任意角度铺设，从电源连接到一段电网的任意一点上（也就是，这段电网的端点上或者在其之间的任意一点上）。这里所说的“一段电网”指的是呈一条线段状的电网，并不是连在一起的几段电网。若几段电网连在一起，那么也要分别给这些电网提供电力。
  
　　已知所有的 F（1 <= F <= 150）段电网的位置（电网总是和坐标轴平行，并且端点的坐标总是整数，0 <= X,Y <= 100）。你的程序要计算连接电源和每段电网所需的电线的最小总长度，还有电源的最佳坐标。
  
　　电源的最佳坐标可能在农夫约翰的农田中的任何一个位置，并不一是整数。

## 输入格式

　　第一行包括 F ——电网的数量。
　　下面的 F 行每行包括两个 X，Y 对，表示这段电网的两个端点。

## 输出格式

只有一行，输出三个浮点数，相邻两个之间留一个空格。

假定你的电脑的输出库会正确地对小数进行四舍五入。
这三个数是： 电源最佳坐标的 X 值，
电源最佳坐标的 Y 值，和
需要的电线的总长度（要最小）。

## 样例 #1

### 输入

```
3

0 0 0 1

2 0 2 1

0 3 2 3
```

### 输出

```
1.0 1.6 3.7
```



---



---

# 题号列表

- SP3544 - BST - Binary Search Tree
- SP4587 - FENCE3 - Electric Fences


---

---
title: "QTREE2 - Query on a tree II"
layout: "post"
diff: 提高+/省选-
pid: SP913
tag: ['倍增', '深度优先搜索 DFS', '最近公共祖先 LCA']
---

# QTREE2 - Query on a tree II

## 题目描述

 You are given a tree (an undirected acyclic connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1. Each edge has an integer value assigned to it, representing its length.

 We will ask you to perfrom some instructions of the following form:

- **DIST a b** : ask for the distance between node **a** and node **b**  
   or
- **KTH a b k** : ask for the **k**-th node on the path from node **a** to node **b**

 **Example:**  
**N** = 6   
 1 2 1 // edge connects node 1 and node 2 has cost 1   
 2 4 1   
 2 5 2   
 1 3 1   
 3 6 2   
  
 Path from node 4 to node 6 is 4 -> 2 -> 1 -> 3 -> 6   
**DIST 4 6** : answer is 5 (1 + 1 + 1 + 2 = 5)   
**KTH 4 6 4** : answer is 3 (the 4-th node on the path from node 4 to node 6 is 3)

## 输入格式

 The first line of input contains an integer **t**, the number of test cases (**t** <= 25). **t** test cases follow.

For each test case:

- In the first line there is an integer **N** (**N** <= 10000)
- In the next **N**-1 lines, the i-th line describes the i-th edge: a line with three integers **a b c** denotes an edge between **a**, **b** of cost **c** (**c** <= 100000)
- The next lines contain instructions **"DIST a b"** or **"KTH a b k"**
- The end of each test case is signified by the string "**DONE**".

There is one blank line between successive tests.

## 输出格式

For each **"DIST"** or **"KTH"** operation, write one integer representing its result.

Print one blank line after each test.

## 样例 #1

### 输入

```
1

6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
DIST 4 6
KTH 4 6 4
DONE
```

### 输出

```
5
3
```



---



---

# 题号列表

- SP913 - QTREE2 - Query on a tree II


---

---
title: "MDST - Minimum Diameter Spanning Tree"
layout: "post"
diff: 提高+/省选-
pid: SP735
tag: ['生成树', '树的直径']
---

# MDST - Minimum Diameter Spanning Tree

## 题目描述

求最小直径生成树的直径。

## 输入格式

T:T组测试数据



n:接下来有n行数据，每行第一个数是结点，第二个数m表示有m个结点与第一个数表示的结点相连。

## 输出格式

每行输出一个数据，表示这个图的最小直径生成树的直径。

## 样例 #1

### 输入

```
6



10

1 3 2 3 4

2 3 1 5 7

3 3 1 5 6

4 3 1 6 8

5 3 2 3 9

6 3 3 4 10

7 1 2

8 1 4

9 1 5

10 1 6



10

1 4 4 5 7 9

2 1 8

3 4 4 7 8 10

4 3 1 3 9

5 2 1 9

6 2 8 9

7 4 1 3 8 9

8 5 2 3 6 7 9

9 7 1 4 5 6 7 8 10

10 2 3 9



1

1 0



2

1 1 2

2 1 1



3

1 1 2

2 2 1 3

3 1 2



5

1 2 2 4

2 3 1 3 4

3 1 2

4 3 2 5 1

5 1 4
```

### 输出

```
5

3

0

1

2

3
```



---



---

# 题号列表

- SP735 - MDST - Minimum Diameter Spanning Tree


---

---
title: "ADAFEAR - Ada and Primal Fear"
layout: "post"
diff: 提高+/省选-
pid: SP33999
tag: ['费用流', '素数判断,质数,筛法']
---

# ADAFEAR - Ada and Primal Fear

## 题目描述

As you might already know, Ada the Ladybug is a farmer. She grows many vegetables. During past months, her crop was attacked by colony of parasites. Each vegetable was attacked by **A $ _{i} $**  parasites. Ada has only limited answer for this. She bought a few bottles with **Primal Fear**, which is a mixture agains parasites.

**Primal Fear** works in following way: Each **Primal Fear** bottle has a power assigned to it (which is coincidentally a prime number). If it is applied to a vegetable with  **N**  parasites on it, either the **N** is divisible by its **power**, then the size of colony is reduced to **N/power**, or - if the size is not divisible - then it has no effect. Also, as soon as you apply mixture against a colony, the rest of colony will become immune agains **Primal Fear**.

Ada didn't know what to buy so she bought one bottle of every possible **power**. Can you find out the best strategy to fight agains parasites?

## 输入格式

The first line of input will contain **1 , the number of vegetable.**

The line will contain **N** numbers **1 , the size of colony on **i $ ^{th} $**  vegetable.**

## 输出格式

Print the minimum sum of sizes of colonies which could be achieved after applying **Primal Fear** optimally.



---

---
title: "GCDEX - GCD Extreme"
layout: "post"
diff: 提高+/省选-
pid: SP3871
tag: ['数学', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCDEX - GCD Extreme

## 题目描述

得定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数 $n$ ，如果 $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 10^6$，不超过 $20000$ 组数据。

## 样例 #1

### 输入

```
10
100
200000
0
```

### 输出

```
67
13015
143295493160

Time limit has been changed. Some AC solutions get TLE
```



---



---

# 题号列表

- SP33999 - ADAFEAR - Ada and Primal Fear
- SP3871 - GCDEX - GCD Extreme


---

---
title: "ADAFEAR - Ada and Primal Fear"
layout: "post"
diff: 提高+/省选-
pid: SP33999
tag: ['费用流', '素数判断,质数,筛法']
---

# ADAFEAR - Ada and Primal Fear

## 题目描述

As you might already know, Ada the Ladybug is a farmer. She grows many vegetables. During past months, her crop was attacked by colony of parasites. Each vegetable was attacked by **A $ _{i} $**  parasites. Ada has only limited answer for this. She bought a few bottles with **Primal Fear**, which is a mixture agains parasites.

**Primal Fear** works in following way: Each **Primal Fear** bottle has a power assigned to it (which is coincidentally a prime number). If it is applied to a vegetable with  **N**  parasites on it, either the **N** is divisible by its **power**, then the size of colony is reduced to **N/power**, or - if the size is not divisible - then it has no effect. Also, as soon as you apply mixture against a colony, the rest of colony will become immune agains **Primal Fear**.

Ada didn't know what to buy so she bought one bottle of every possible **power**. Can you find out the best strategy to fight agains parasites?

## 输入格式

The first line of input will contain **1 , the number of vegetable.**

The line will contain **N** numbers **1 , the size of colony on **i $ ^{th} $**  vegetable.**

## 输出格式

Print the minimum sum of sizes of colonies which could be achieved after applying **Primal Fear** optimally.



---

---
title: "GCDEX - GCD Extreme"
layout: "post"
diff: 提高+/省选-
pid: SP3871
tag: ['数学', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCDEX - GCD Extreme

## 题目描述

得定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数 $n$ ，如果 $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 10^6$，不超过 $20000$ 组数据。

## 样例 #1

### 输入

```
10
100
200000
0
```

### 输出

```
67
13015
143295493160

Time limit has been changed. Some AC solutions get TLE
```



---



---

# 题号列表

- SP33999 - ADAFEAR - Ada and Primal Fear
- SP3871 - GCDEX - GCD Extreme


---

---
title: "GSS1 - Can you answer these queries I"
layout: "post"
diff: 提高+/省选-
pid: SP1043
tag: ['线段树', '分治', '前缀和']
---

# GSS1 - Can you answer these queries I

## 题目描述

You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:   
 Query(x,y) = Max { a\[i\]+a\[i+1\]+...+a\[j\] ; x ≤ i ≤ j ≤ y }.   
 Given M queries, your program must output the results of these queries.

## 输入格式

- The first line of the input file contains the integer N.
- In the second line, N numbers follow.
- The third line contains the integer M.
- M lines follow, where line i contains 2 numbers xi and yi.

## 输出格式

 Your program should output the results of the M queries, one query per line.

## 样例 #1

### 输入

```
3 
-1 2 3
1
1 2
```

### 输出

```
2
```



---

---
title: "GSS3 - Can you answer these queries III"
layout: "post"
diff: 提高+/省选-
pid: SP1716
tag: ['线段树', '矩阵乘法', '动态 DP']
---

# GSS3 - Can you answer these queries III

## 题目描述

You are given a sequence A of N (N <= 50000) integers between -10000 and 10000. On this sequence you have to apply M (M <= 50000) operations:   
 modify the i-th element in the sequence or for given x y print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.

## 输入格式

The first line of input contains an integer N. The following line contains N integers, representing the sequence A1..AN.   
 The third line contains an integer M. The next M lines contain the operations in following form:  
 0 x y: modify Ax into y (|y|<=10000).  
 1 x y: print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.

## 输出格式

For each query, print an integer as the problem required.

## 样例 #1

### 输入

```
4
1 2 3 4
4
1 1 3
0 3 -3
1 2 4
1 3 3
```

### 输出

```
6
4
-3
```



---

---
title: "GSS4 - Can you answer these queries IV"
layout: "post"
diff: 提高+/省选-
pid: SP2713
tag: ['线段树']
---

# GSS4 - Can you answer these queries IV

## 题目描述

You are given a sequence A of N(N <= 100,000) positive integers. There sum will be less than 10 $ ^{18} $ . On this sequence you have to apply M (M <= 100,000) operations:

(A) For given x,y, for each elements between the x-th and the y-th ones (inclusively, counting from 1), modify it to its positive square root (rounded down to the nearest integer).

(B) For given x,y, query the sum of all the elements between the x-th and the y-th ones (inclusively, counting from 1) in the sequence.

## 输入格式

Multiple test cases, please proceed them one by one. Input terminates by EOF.

For each test case:

The first line contains an integer N. The following line contains N integers, representing the sequence A $ _{1} $ ..A $ _{N} $ .   
 The third line contains an integer M. The next M lines contain the operations in the form "i x y".i=0 denotes the modify operation, i=1 denotes the query operation.

## 输出格式

For each test case:

Output the case number (counting from 1) in the first line of output. Then for each query, print an integer as the problem required.

Print an blank line after each test case.

See the sample output for more details.

## 样例 #1

### 输入

```
5
1 2 3 4 5
5
1 2 4
0 2 4
1 2 4
0 4 5
1 1 5
4
10 10 10 10
3
1 1 4
0 2 3
1 1 4
```

### 输出

```
Case #1:
9
4
6

Case #2:
40
26
```



---

---
title: "ADAAPPLE - Ada and Apple"
layout: "post"
diff: 提高+/省选-
pid: SP30785
tag: ['线段树', '树链剖分']
---

# ADAAPPLE - Ada and Apple

## 题目描述

Ada the Ladybug is currently on a trip on apple [tree](https://en.wikipedia.org/wiki/Tree_(data_structure)). There are many apples on the tree connected with branches. Each apple is inhabited by either Psylloideas or by Woolly Apple Aphids. Psylloideas and Aphids doesn't like each other, so it is strictly prohibited to walk from apple of Psylloideas to apple of aphids (and vice versa). Ada has some questions, whether it is possible to go from node **I** to node **J**.

Anyway note, that as Aphids and Psyllodeas doesn't like each other, they sometime conquer an apple of the others. Also note, that it is a real apple tree (not some bush) so no apple is connected with more than 50 other apples.

## 输入格式

The first line contains **1 , number apples on tree and number for queries.**

The next line contains **N** characters (either 0 or 1), indicating whether **i** $ ^{th} $ apple belongs to Psyllodeas or to Aphids.

Next **N-1** lines contains two numbers, the branches (edges) of apple tree (**0 , **I ≠ J**).**

Each of following **Q** lines contains one of following types of queries:

 **0 I**, **0 , meaning that ownership of **I** $ ^{th} $ apple has changed.**

 **1 I J**, **0 , question, whether it is possible to go from **I** $ ^{th} $ to **J** $ ^{th} $ apple.**

## 输出格式

For each query of second kind (1) print "YES", if it is possible or "NO" if it is impossible!



---

---
title: "DQUERY - D-query"
layout: "post"
diff: 提高+/省选-
pid: SP3267
tag: ['莫队', '线段树', '树状数组', '可持久化线段树']
---

# DQUERY - D-query

## 题目描述

[English](/problems/DQUERY/en/) [Vietnamese](/problems/DQUERY/vn/)Given a sequence of n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ .

## 输入格式

- Line 1: n (1 ≤ n ≤ 30000).
- Line 2: n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ (1 ≤ a $ _{i} $ ≤ 10 $ ^{6} $ ).
- Line 3: q (1 ≤ q ≤ 200000), the number of d-queries.
- In the next q lines, each line contains 2 numbers i, j representing a d-query (1 ≤ i ≤ j ≤ n).

## 输出格式

- For each d-query (i, j), print the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ in a single line.

## 样例 #1

### 输入

```
5
1 1 2 1 3
3
1 5
2 4
3 5
```

### 输出

```
3
2
3
```



---

---
title: "INTDSET - Chiaki With Intervals"
layout: "post"
diff: 提高+/省选-
pid: SP34032
tag: ['动态规划 DP', '线段树']
---

# INTDSET - Chiaki With Intervals

## 题目描述

给你一个有 $n$ 个区间的集合 $A$，求有多少个子集 $S$ 满足条件：任意区间 $a \in A$ 且 $a \notin S$ 均与 $S$ 的至少一个子集有交集。

答案对 $10^9+7$ 取模。

注意 $A$ 本身是一个合法的答案。

## 输入格式

第一行输入整数 $T$ ，代表数据组数。

对于每组数据，先输入整数 $n$，代表区间的个数，接下来是 $n$ 行，每行2个整数 $l_i,r_i$，代表一个区间。

## 输出格式

对于每组数据，输出一个整数。

## 样例 #1

### 输入

```
2
3
1 2
3 4
5 6
3
1 4
2 4
3 4
```

### 输出

```
1
7
```



---

---
title: "QTREE - Query on a tree"
layout: "post"
diff: 提高+/省选-
pid: SP375
tag: ['线段树', '最近公共祖先 LCA', '树链剖分']
---

# QTREE - Query on a tree

## 题目描述

You are given a tree (an acyclic undirected connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1.

We will ask you to perfrom some instructions of the following form:

- **CHANGE i ti** : change the cost of the i-th edge to ti  
   or
- **QUERY a b** : ask for the maximum edge cost on the path from node a to node b

## 输入格式

The first line of input contains an integer **t**, the number of test cases (**t** <= 20). t test cases follow.

For each test case:

- In the first line there is an integer **N** (**N** <= 10000),
- In the next **N**-1 lines, the i-th line describes the i-th edge: a line with three integers **a b c** denotes an edge between **a**, **b** of cost **c** (**c** <= 1000000),
- The next lines contain instructions **"CHANGE i ti"** or **"QUERY a b"**,
- The end of each test case is signified by the string "**DONE**".

There is one blank line between successive tests.

## 输出格式

For each "**QUERY**" operation, write one integer representing its result.

## 样例 #1

### 输入

```
1

3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE
```

### 输出

```
1
3
```



---

---
title: "MKTHNUM - K-th Number"
layout: "post"
diff: 提高+/省选-
pid: SP3946
tag: ['线段树', '可持久化线段树', '可持久化']
---

# MKTHNUM - K-th Number

## 题目描述

题目大意：

给你 $n$ 个数，多次询问某段区间中第 $k$ 小的数。

## 输入格式

第一行有两个整数 $n,m$，分别为整数个数、询问次数。

第二行有 $n$ 个整数，其中第 $i$ 个为 $a_i$。

接下来 $m$ 行，每行三个整数 $i,j,k$，询问第 $i$ 个数到第 $j$ 个数中第 $k$ 小的数。

## 输出格式

输出共 $m$ 行，为对每次询问的回答。

## 说明/提示

$1\le n \le 100000$ , $1 \le m \le 5000$ , $-10^9 \le a_i \le 10^9$。

~~注意：简单的做法可是过不了的。~~

 感谢 @gjc1124646822  提供的翻译。
 
 Fixed by @AnEasySong



---

---
title: "CPAIR - Counting pairs"
layout: "post"
diff: 提高+/省选-
pid: SP5542
tag: ['线段树']
---

# CPAIR - Counting pairs

## 题目描述

给出一个长度为 $N$ 的非负整数序列 $A$，回答 $Q$ 个询问。每个询问包含 $3$ 个数：$v,a,b$，回答序列 $A$ 中有多少个区间的最小值 $\ge v$，且区间的长度在 $[a,b]$ 范围内。

## 输入格式

第一行输入两个整数，包含 $N$ 和 $Q$

第二行输入 $N$ 个整数，表示序列 $A$

接下来 $Q$ 行，每行输入三个整数 $v,a,b$，含义同上

## 输出格式

输出共 $Q$ 行，每行一个整数，为每个询问的答案

## 说明/提示

- $1 \le N,Q \le 10^5$
- $1 \le a \le b \le N$
- $0 \le v,A_i \le 10^9$

## 样例 #1

### 输入

```
5 3

5 3 2 7 4

3 2 3

2 2 5

4 1 1
```

### 输出

```
2

10

3
```



---



---

# 题号列表

- SP1043 - GSS1 - Can you answer these queries I
- SP1716 - GSS3 - Can you answer these queries III
- SP2713 - GSS4 - Can you answer these queries IV
- SP30785 - ADAAPPLE - Ada and Apple
- SP3267 - DQUERY - D-query
- SP34032 - INTDSET - Chiaki With Intervals
- SP375 - QTREE - Query on a tree
- SP3946 - MKTHNUM - K-th Number
- SP5542 - CPAIR - Counting pairs


---

---
title: "LOPOV - Lopov"
layout: "post"
diff: 提高+/省选-
pid: SP16409
tag: ['背包 DP', '优先队列', '队列']
---

# LOPOV - Lopov

## 题目描述

国家经济形势艰难，政府的农业补贴资金减少，Mirko不得不再次转行，这次他的职业是——小偷。



他的第一票是打劫一家珠宝店。

这家珠宝店有$N$件首饰，每件首饰都有它的质量$M[i]$和价值$V[i]$。Mirko有$K$个袋子来存放他的战利品。每个袋子可以容纳的最大质量是$C[i]$。他计划将所有的战利品存放在这些袋子中，为了防止逃跑时首饰之间互相磨损，每个袋子只放一件首饰。



请你计算出Mirko可以偷到的最大珠宝价值。

## 输入格式

第1行输入包含两个整数$N$和$K$。

以下N行中的每一行包含一对数字$M[i]$和$V[i]$。以下K行中的每一行包含数字$C[i]$。

## 输出格式

输出共一行一个整数，即最大的珠宝总价值。



## 【输入样例1】

```

2 1

5 10

10

0 100

11

```

## 【输出样例1】

```

10

```

## 【输入样例2】

```

3 2

1 65

5 23

2 99

10

2

```

## 【输出样例2】

```

164

```

## 说明/提示

Mirko将第一件首饰放入第二个包，第三件放入第一个包。

## 【数据规模】

对于15%的数据：$1\le N,K\le 1,000$；



对于25%的数据：$1\le N,K\le 50,000$；



对于100%的数据：$1\le N,K\le 300,000$；$0\le M[i],V[i]\le 1,000,000$；$1\le C[i]\le 100,000,000$；

## 样例 #1

### 输入

```
2 1 

5 10 

100 100 

11
```

### 输出

```
10
```



---

---
title: "VOCV - Con-Junctions"
layout: "post"
diff: 提高+/省选-
pid: SP666
tag: ['动态规划 DP', '背包 DP', '概率论']
---

# VOCV - Con-Junctions

## 题目描述

给一个 $n$ 个节点和 $n - 1$ 条边的树，现在要在一些节点放置灯最终点亮所有的边。

当一个节点上放置了一盏灯时，所有与它相连的边都会被点亮，且每一条边只需一个端点被点亮即认为被点亮。

试求最少的放灯数量和当放灯数量最少时的方案数。请将方案数结果模 $10007$ 输出。

数据范围：$n \le 100010$。

## 输入格式

在文件的第一行，一个整数 $t(t \le 20)$，表示该测试点中有 $t$ 组测试数据。

接下来若干行描述每个测试数据中树的情况：

首先包含一个 $n$，代表这个测试数据中树的节点个数。

接下来 $n - 1$ 行，每一行有两个整数 $x,y$，代表有一条双向边连接着两个节点 $x$ 和 $y$。

## 输出格式

对于每一个测试数据，请输出最少的放灯数量和当放灯数量最少时的方案数。请将方案数结果模 $10007$ 输出。

## 样例 #1

### 输入

```
2
4
1 2
2 3
3 4
3
1 2
1 3
```

### 输出

```
2 3
1 1
```



---



---

# 题号列表

- SP16409 - LOPOV - Lopov
- SP666 - VOCV - Con-Junctions


---

---
title: "ADAFEAR - Ada and Primal Fear"
layout: "post"
diff: 提高+/省选-
pid: SP33999
tag: ['费用流', '素数判断,质数,筛法']
---

# ADAFEAR - Ada and Primal Fear

## 题目描述

As you might already know, Ada the Ladybug is a farmer. She grows many vegetables. During past months, her crop was attacked by colony of parasites. Each vegetable was attacked by **A $ _{i} $**  parasites. Ada has only limited answer for this. She bought a few bottles with **Primal Fear**, which is a mixture agains parasites.

**Primal Fear** works in following way: Each **Primal Fear** bottle has a power assigned to it (which is coincidentally a prime number). If it is applied to a vegetable with  **N**  parasites on it, either the **N** is divisible by its **power**, then the size of colony is reduced to **N/power**, or - if the size is not divisible - then it has no effect. Also, as soon as you apply mixture against a colony, the rest of colony will become immune agains **Primal Fear**.

Ada didn't know what to buy so she bought one bottle of every possible **power**. Can you find out the best strategy to fight agains parasites?

## 输入格式

The first line of input will contain **1 , the number of vegetable.**

The line will contain **N** numbers **1 , the size of colony on **i $ ^{th} $**  vegetable.**

## 输出格式

Print the minimum sum of sizes of colonies which could be achieved after applying **Primal Fear** optimally.



---

---
title: "GCDEX - GCD Extreme"
layout: "post"
diff: 提高+/省选-
pid: SP3871
tag: ['数学', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCDEX - GCD Extreme

## 题目描述

得定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数 $n$ ，如果 $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 10^6$，不超过 $20000$ 组数据。

## 样例 #1

### 输入

```
10
100
200000
0
```

### 输出

```
67
13015
143295493160

Time limit has been changed. Some AC solutions get TLE
```



---



---

# 题号列表

- SP33999 - ADAFEAR - Ada and Primal Fear
- SP3871 - GCDEX - GCD Extreme


---

---
title: "FN16SWAP - Swap Space"
layout: "post"
diff: 提高+/省选-
pid: SP27102
tag: ['贪心']
---

# FN16SWAP - Swap Space

## 题目描述

你有许多电脑，它们的硬盘用不同的文件系统储存数据。你想要通过格式化来统一文件系统。格式化硬盘可能使它的容量发生变化。为了格式化，你需要买额外的硬盘。当然，你想要买容量最小的额外储存设备以便省钱。你可以按任意顺序格式化硬盘。格式化之前，你要把该硬盘上所有数据移到一个或更多的其他硬盘上（可以分割数据）。格式化后，该硬盘可以立刻开始使用。你没有必要把数据放到它原来所在的硬盘上。数据也可以被放到你额外买的硬盘上。举个例子，假设你有4个硬盘A、B、C、D，容量分别为6、1、3、3(GB)。新的文件系统下，它们的容量变为6、7、5、5(GB)。如果你只买1GB额外空间，你可以把B硬盘的数据放过去然后格式化硬盘B。现在你的B硬盘有7GB容量了，那么你就可以把A的数据放过去然后格式化A，最后把C、D的数据放到A上，再格式化C和D。

## 输入格式

第一行一个数n(1≤n≤1,000,000)，表示你的硬盘数。接下来n行，每行两个数a和b，分别表示该硬盘的原容量和新文件系统下的容量。所有容量都以GB为单位，且1≤a,b≤1,000,000,000。

## 输出格式

输出如果要格式化所有硬盘，你最少需要购买多少额外空间(GB)。

Translated by @XHRlyb_2001

## 样例 #1

### 输入

```
4

6 6

1 7

3 5

3 5

4

2 2

3 3

5 1

5 10
```

### 输出

```
1

5
```



---

---
title: "SAM - Toy Cars"
layout: "post"
diff: 提高+/省选-
pid: SP688
tag: ['贪心', '枚举']
---

# SAM - Toy Cars

## 题目描述

Jasio 是一个只有三岁的小男孩，他喜欢玩玩具车。他有 $n$ 辆玩具车被保存在书架上。

架子上的玩具车 Jasio 拿不到，但地板上的他可以拿到。Jasio 的母亲会帮 Jasio 拿架子上的玩具车到地板上。

地板最多只能放 $k$ 辆玩具车。

当地板已经放了 $k$ 辆玩具车时，Jasio 的母亲都会从地板上先拿走一个玩具车放回书架，再拿来 Jasio 想要的玩具车。

现在 Jasio 一共想依次玩 $p$ 个玩具车，问 Jasio 的母亲最少需要拿几次玩具车。（只算拿下来的，不算拿上去的）

## 输入格式

第一行一个整数 $t$，表示有 $t$ 组数据。

接下来一行有三个整数 $n,k$ 和 $p$。

接下来 $p$ 行，每一行有且仅有一个整数 $a_i$，表示 Jasio 想玩的玩具玩家车编号。

## 输出格式

输出一行一个整数，表示最少 Jasio 的母亲最少需要拿玩家车的次数。

## 说明/提示

对于 $100\%$ 的数据：$1\le t\le 16$，$1\le k\le n\le 10^5$，$1\le p\le 5\times 10^5$，$1\le a_i\le n$。

感谢 @Utilokasteinn 提供的翻译。

## 样例 #1

### 输入

```
1
3 2 7
1
2
3
1
3
1
2
```

### 输出

```
4
```



---



---

# 题号列表

- SP27102 - FN16SWAP - Swap Space
- SP688 - SAM - Toy Cars


---

---
title: "TRIP - Trip"
layout: "post"
diff: 提高+/省选-
pid: SP33
tag: ['字符串', '递归', '枚举']
---

# TRIP - Trip

## 题目描述

Alice and Bob want to go on holiday. Each of them has drawn up a list of cities to be visited in turn. A list may contain a city more than once. As they want to travel together, they have to agree upon a common route. No one wants to change the order of the cities on his list or add other cities. Therefore they have no choice but to remove some cities from the list. Of course the common route is to involve as much sight-seeing in cities as possible. There are exactly 26 cities in the region. Therefore they are encoded on the lists as lower case letters from 'a' to 'z'.

## 输入格式

The first line of input contains a number T <= 10 that indicates the number of test cases to follow. Each test case consists of two lines; the first line is the list of Alice, the second line is the list of Bob. Each list consists of 1 to 80 lower case letters.

## 输出格式

The output for each test case should contain all different trips exactly once that meet the conditions described above. There is at least one such trip, but never more than 1000 different ones. You should order the trips in lexicographic order. Print one blank line between the output of different test cases.

## 样例 #1

### 输入

```
1
abcabcaa
acbacba
```

### 输出

```
ababa
abaca
abcba
acaba
acaca
acbaa
acbca
```



---



---

# 题号列表

- SP33 - TRIP - Trip


---

---
title: "RESTACK - Restacking haybales 2012"
layout: "post"
diff: 提高+/省选-
pid: SP11117
tag: ['递推', '线性递推']
---

# RESTACK - Restacking haybales 2012

## 题目描述

Farmer John has just ordered a large number of bales of hay. He would like  
to organize these into N piles (1 <= N <= 100,000) arranged in a circle,  
where pile i contains B\_i bales of hay. Unfortunately, the truck driver  
delivering the hay was not listening carefully when Farmer John provided  
this information, and only remembered to leave the hay in N piles arranged  
in a circle. After delivery, Farmer John notes that pile i contains A\_i  
bales of hay. Of course, the A\_i's and the B\_i's have the same sum.

Farmer John would like to move the bales of hay from their current  
configuration (described by the A\_i's) into his desired target  
configuration (described by the B\_i's). It takes him x units of work to  
move one hay bale from one pile to a pile that is x steps away around the  
circle. Please help him compute the minimum amount of work he will need to  
spend.

## 输入格式

\* Line 1: The single integer N.

\* Lines 2..1+N: Line i+1 contains the two integers A\_i and B\_i (1 <=  
 A\_i, B\_i <= 1000).

Example:

4  
7 1  
3 4  
9 2  
1 13



---

---
title: "SETNJA - Setnja"
layout: "post"
diff: 提高+/省选-
pid: SP3362
tag: ['递推']
---

# SETNJA - Setnja

## 题目描述

在二叉树中：

每个节点都有两个孩子——一个左孩子和一个右孩子。
如果节点标记为整数 $x$ ，则其左子节点标记为 $2x$ ，右子节点标记为 $2x+1$ 。
树的根标为 $1$ 。
在二叉树上从根开始遍历。遍历中的每一步要么是跳到左孩子上，要么是跳到右孩子上，或暂停休息（停留在同一节点上）。

用由字符 $L，R$ 和 $P$ 组成的字符串描述遍历过程。

$L$ 表示跳到左孩子；
$R$ 表示跳到右孩子；
$P$ 表示暂停一轮操作。

$walk$ 的值是我们最终到达的节点的标签。例如，$LR$ 的 $walk$ 值为 5，而 $RPP$ 的 $walk$ 值为 3。

一次遍历由 $L，R，P$ 和 $* $ 描述。每个 $*$ 可以是三个动作中的任何一个。 例如， $L*R$ 可能代表 $LLR，LRR$ 和 $LPR$。集合 $ ** $ 可能代表$ LL，LR，LP，RL，RR，RP，PL，PR$ 和 $PP$。
最后，一次遍历后的 $walk$ 的总值是该次遍历中所有可能的遍历顺序的每一步所形成的 $walk$ 的值的总和。

计算给定遍历顺序后的 $walk$ 的总值。

## 输入格式

一行一个字符串，表示遍历顺序。

## 输出格式

一行一个整数，表示 $walk$
 的总值。
## 输入输出样例
### 输入 #1 
```
L*R
```
### 输出 #1
```
25
```

## 样例 #1

### 输入

```
L*R
```

### 输出

```
25
```



---



---

# 题号列表

- SP11117 - RESTACK - Restacking haybales 2012
- SP3362 - SETNJA - Setnja


---

---
title: "LOPOV - Lopov"
layout: "post"
diff: 提高+/省选-
pid: SP16409
tag: ['背包 DP', '优先队列', '队列']
---

# LOPOV - Lopov

## 题目描述

国家经济形势艰难，政府的农业补贴资金减少，Mirko不得不再次转行，这次他的职业是——小偷。



他的第一票是打劫一家珠宝店。

这家珠宝店有$N$件首饰，每件首饰都有它的质量$M[i]$和价值$V[i]$。Mirko有$K$个袋子来存放他的战利品。每个袋子可以容纳的最大质量是$C[i]$。他计划将所有的战利品存放在这些袋子中，为了防止逃跑时首饰之间互相磨损，每个袋子只放一件首饰。



请你计算出Mirko可以偷到的最大珠宝价值。

## 输入格式

第1行输入包含两个整数$N$和$K$。

以下N行中的每一行包含一对数字$M[i]$和$V[i]$。以下K行中的每一行包含数字$C[i]$。

## 输出格式

输出共一行一个整数，即最大的珠宝总价值。



## 【输入样例1】

```

2 1

5 10

10

0 100

11

```

## 【输出样例1】

```

10

```

## 【输入样例2】

```

3 2

1 65

5 23

2 99

10

2

```

## 【输出样例2】

```

164

```

## 说明/提示

Mirko将第一件首饰放入第二个包，第三件放入第一个包。

## 【数据规模】

对于15%的数据：$1\le N,K\le 1,000$；



对于25%的数据：$1\le N,K\le 50,000$；



对于100%的数据：$1\le N,K\le 300,000$；$0\le M[i],V[i]\le 1,000,000$；$1\le C[i]\le 100,000,000$；

## 样例 #1

### 输入

```
2 1 

5 10 

100 100 

11
```

### 输出

```
10
```



---



---

# 题号列表

- SP16409 - LOPOV - Lopov


---

---
title: "VECTAR9 - Mangu Numbers"
layout: "post"
diff: 普及/提高-
pid: SP27319
tag: ['二分', '容斥原理']
---

# VECTAR9 - Mangu Numbers

## 题目描述

 When Changu was introduced to the concept of prime numbers, he was so glad that, after one days happy work, he was able to generate the first thirteen prime numbers. He has the ability that, given any number, he can tell whether or not it is divisible by any of the first thirteen primes. The first thirteen prime numbers are 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, and 41; their product is 304250263527210. A number is called 'mangu' if it is divisible by at least one of the first thirteen primes. Thus, the first number that is not 'mangu' is 1, and the second is 43. Changu wrote all the 'mangu' numbers in ascending order in a list.

 Your task is to find out, given k, what is the k-th element in the list.

## 输入格式

The first line contains T (not more than 500), the number of test cases. In each case there is a single number k.

## 输出格式

For each test case, output the k-th mangu number on a single line. You may assume that the answer is never bigger than 304250263527210.

## 样例 #1

### 输入

```
2

2

3
```

### 输出

```
3

4
```



---



---

# 题号列表

- SP27319 - VECTAR9 - Mangu Numbers


---

---
title: "ARRPRM - Prime is fun"
layout: "post"
diff: 普及/提高-
pid: SP30394
tag: ['动态规划 DP', '素数判断,质数,筛法', '前缀和']
---

# ARRPRM - Prime is fun

## 题目描述

给定一个长为 $n$ 的序列 $a$，从 $a$ 中选出若干个互不相连的长度均为质数的连续段，使这些连续段中的数的和最大。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

第一行，一个整数 $n$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$。

## 输出格式

对于每组数据：

一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
4
1 2 3 4
10
10 1 1 1 1 1 1 2 2 2
```
#### 输出 #1
```
9
21
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T \leq 100$，$1 \leq n \leq 2 \times 10^3$，$1 \leq a_i \leq 10^6$。



---



---

# 题号列表

- SP30394 - ARRPRM - Prime is fun


---

---
title: "DCEPC11J - Jailbreak"
layout: "post"
diff: 普及/提高-
pid: SP16212
tag: ['动态规划 DP']
---

# DCEPC11J - Jailbreak

## 题目描述

The great King Kapish has prisoned Pushap, for he loves the princess Padmavati. To make sure that Pushap and Padmavati never meet again, King Kapish has kept Pushap in his most mysterious of jail.

This jail is built in a 2D rectangular grid fashion, containing M\*N prison cells. The entrance gate for jail is at bottom left corner (0,0). The mysteriousness of this jail comes from the fact that once a prisoner is taken from entrance gate (0,0) to any prison cell, then that prisoner can escape only if he comes back to the entrance visiting the cells used on his way from entrance to his prison cell. Note that in the escape, it is not required for the prisoner to trace the exact path or visit all the cells used on his way up, rather the condition is to use/visit only those prison cells used on his way up. Additionally, when the prisoner is taken from entrance (0,0) to a prison cell, they can fathom upto 2 cells in a single move/step in either upward direction or right direction. And when the prisoner is escaping, he can fathom upto 2 cells in a single move/step in either downward or left direction.

King Kapish orders to jail prisoner Pushap in cell (M-1,N-1).

You, being a common friend to Pushap and Padmavati, have to help Pushap escape the prison. **Tell him the number of ways in which he can go up to cell (M-1,N-1) and then come back following the procedure described above. Please refer explanation part to know more.**

## 输入格式

First line contains T, the number of test cases.

Each test case contains 2 space separated integers, M and N.

## 输出格式

Output exactly T lines, each containing the required answer modulo 10^9 + 7.

## 说明/提示

**【样例解释】**

对于第二组数据，一种可能的路径如下：

$(0,0) \to (0,1) \to (0,2) \to (1,2) \to (0,2) \to (0,0)$。

## 样例 #1

### 输入

```
3
2 2
2 3
3 4

```

### 输出

```
2
7
66

```



---

---
title: "SCUBADIV - Scuba diver"
layout: "post"
diff: 普及/提高-
pid: SP181
tag: ['动态规划 DP', '背包 DP']
---

# SCUBADIV - Scuba diver

## 题目描述

A scuba diver uses a special equipment for diving. He has a cylinder with two containers: one with oxygen and the other with nitrogen. Depending on the time he wants to stay under water and the depth of diving the scuba diver needs various amount of oxygen and nitrogen. The scuba diver has at his disposal a certain number of cylinders. Each cylinder can be described by its weight and the volume of gas it contains. In order to complete his task the scuba diver needs specific amount of oxygen and nitrogen. What is the minimal total weight of cylinders he has to take to complete the task?

## 输入格式

The number of test cases _c_ is in the first line of input, then _c_ test cases follow separated by an empty line.

In the first line of a test case there are two integers _t_, _a_ separated by a single space, 1 <= _t_ <= 21 and 1 <= _a_ <= 79. They denote volumes of oxygen and nitrogen respectively, needed to complete the task. The second line contains one integer _n_, 1 <= _n_ <= 1000, which is the number of accessible cylinders. The following _n_ lines contain descriptions of cylinders; _i_-th line contains three integers _t_ _$ _{i} $_ , _a_ _$ _{i} $_ , _w_ _$ _{i} $_  separated by single spaces, (1 <= _t_ _$ _{i} $_  <= 21, 1 <= _a_ _$ _{i} $_  <= 79, 1 <= _w_ _$ _{i} $_  <= 800). These are respectively: volume of oxygen and nitrogen in the _i_-th cylinder and the weight of this cylinder.

## 输出格式

For each test case your program should output one line with the minimal total weight of cylinders the scuba diver should take to complete the task.

## 样例 #1

### 输入

```
1
5 60
5
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119

```

### 输出

```
249

```



---

---
title: "ARRPRM - Prime is fun"
layout: "post"
diff: 普及/提高-
pid: SP30394
tag: ['动态规划 DP', '素数判断,质数,筛法', '前缀和']
---

# ARRPRM - Prime is fun

## 题目描述

给定一个长为 $n$ 的序列 $a$，从 $a$ 中选出若干个互不相连的长度均为质数的连续段，使这些连续段中的数的和最大。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

第一行，一个整数 $n$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$。

## 输出格式

对于每组数据：

一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
4
1 2 3 4
10
10 1 1 1 1 1 1 2 2 2
```
#### 输出 #1
```
9
21
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T \leq 100$，$1 \leq n \leq 2 \times 10^3$，$1 \leq a_i \leq 10^6$。



---

---
title: "BOOKS1 - Copying Books"
layout: "post"
diff: 普及/提高-
pid: SP43
tag: ['动态规划 DP', '贪心', '进制']
---

# BOOKS1 - Copying Books

## 样例 #1

### 输入

```
2

9 3

100 200 300 400 500 600 700 800 900

5 4

100 100 100 100 100
```

### 输出

```
100 200 300 400 500 / 600 700 / 800 900

100 / 100 / 100 / 100 100
```



---

---
title: "EDIST - Edit distance"
layout: "post"
diff: 普及/提高-
pid: SP6219
tag: ['动态规划 DP']
---

# EDIST - Edit distance

## 题目描述

给定两个字符串 $A$ 和 $B$。回答将 $A$ 转换为 $B$ 需要的最少操作次数是多少？

操作包括：

1. 从一个字符串中删除一个字母
2. 向一个字符串中插入一个字母
3. 将一个字符串中的一个字母替换为另一个字母

## 输入格式

$T$ - 测试用例的数量。

对于每个测试用例：

- 字符串 $A$
- 字符串 $B$

两个字符串只包含大写字符，且长度不超过 $2000$ 个字符。

数据集中有 $10$ 个测试用例。

## 输出格式

对于每个测试用例，输出一行，表示最少操作次数。

---

Translated by User 735713.

## 样例 #1

### 输入

```
1

FOOD

MONEY
```

### 输出

```
4
```



---



---

# 题号列表

- SP16212 - DCEPC11J - Jailbreak
- SP181 - SCUBADIV - Scuba diver
- SP30394 - ARRPRM - Prime is fun
- SP43 - BOOKS1 - Copying Books
- SP6219 - EDIST - Edit distance


---

---
title: "PT07Y - Is it a tree"
layout: "post"
diff: 普及/提高-
pid: SP1436
tag: ['图论', '并查集', '拓扑排序']
---

# PT07Y - Is it a tree

## 题目描述

有一个N个点M条边的图。 请问，该图是否为树。

## 输入格式

第1行2个数N,M。

接下来M行，每行2个数A,B，表示一条边（A,B）。

## 输出格式

如果该图为树，输出“YES”，否则输出“NO”。

数据范围： 0<N<=10000 0<=M<=20000

感谢@qq1010903229 提供的翻译

## 样例 #1

### 输入

```
3 2
1 2
2 3
```

### 输出

```
YES
```



---

---
title: "ADATRIP - Ada and Trip"
layout: "post"
diff: 普及/提高-
pid: SP30669
tag: ['图论', '最短路']
---

# ADATRIP - Ada and Trip

## 题目描述

瓢虫 Ada 热爱旅游。她一边拍照，买纪念品，一边周游世界。这星期她去了布干达。普通游客会选择在主城区和一些大都市游玩。但是 Ada 不这么认为。她想走尽可能远的路（因为远离市中心的地方所拍摄的照片更有价值）。

问题来了，布干达非常大，她几乎猜不着哪个城市离她最远（通过最短路）。幸运的是，你在她身旁，于是，她向聪明博学的你发出了求救。你能告诉她最远的城市距离她的距离，以及有多少个这样的城市吗？

## 输入格式

第一行有 $3$ 个整数 $N,M,Q$。$1\le N\le 5 \times10^5,0\le M\le 10^6$。分别表示：城市数量，道路数量，提问数量。

接下来 $M$ 行一行 $3$ 个整数 $A,B,L$。$0\le A,B < N,0\le L\le 10$，表示有一条从 $A$ 市 到 $B$ 市距离为 $L$ 的无向边。

接下来 $Q$ 行，一行一个整数 $0\le Q_i < N$，表示出发的城市。

**保证输入数据满足 $\max({N,M})\times Q \le 10^7$。注意城市的编号从 $0$ 开始。**

**温馨提示：因为我们身处的是现实世界而非所谓的“图”，因此可能出现重边和自环。**

## 输出格式

共 $Q$ 行。一行两个整数，分别表示最远的距离，以及城市数量。

## 说明/提示

距离每个询问城市最远的城市编号如下：
```plain
0
2 3
3
2
8
4 8
4 8
4 8
4
4 8
```

## 样例 #1

### 输入

```
10 10 10
1 1 1
1 2 1
1 2 3 
3 1 1
5 4 10
8 5 10
5 6 5
6 7 3
6 9 3
9 7 4
0
1
2
3
4
5
6
7
8
9
```

### 输出

```
0 1
1 2
2 1
2 1
20 1
10 2
15 2
18 2
20 1
18 2
```



---



---

# 题号列表

- SP1436 - PT07Y - Is it a tree
- SP30669 - ADATRIP - Ada and Trip


---

---
title: "PHONELST - Phone List"
layout: "post"
diff: 普及/提高-
pid: SP4033
tag: ['字符串', '字典树 Trie']
---

# PHONELST - Phone List

## 题目描述

**【题目来源】**

	Poj3630

**【问题描述】**

	给定n个长度不超过10的数字串，问其中是否存在两个数字串S，T，使得S是T的前缀。有多组数据，数据组数不超过40。n<=10000。

## 输入格式

第一行，一个整数T，表示数据组数。
	对于每组数据，第一行一个数n，接下去n行，输入n个数字串。

## 输出格式

对于每组数据，若存在两个数字串S，T，使得S是T的前缀，则输出“NO”，否则输出“YES”。

**【数据规模】**

	n<=10000

## 样例 #1

### 输入

```
2
3
911
97625999
91125426
5
113
12340
123440
12345
98346
```

### 输出

```
NO
YES
```



---

---
title: "PALIN - The Next Palindrome"
layout: "post"
diff: 普及/提高-
pid: SP5
tag: ['字符串', '数学', '枚举']
---

# PALIN - The Next Palindrome

## 题目描述

A positive integer is called a _palindrome_ if its representation in the decimal system is the same when read from left to right and from right to left. For a given positive integer _K_ of not more than 1000000 digits, write the value of the smallest palindrome larger than _K_ to output. Numbers are always displayed without leading zeros.

## 输入格式

The first line contains integer _t_, the number of test cases. Integers _K_ are given in the next _t_ lines.

## 输出格式

For each _K_, output the smallest palindrome larger than _K_.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages**

## 样例 #1

### 输入

```
2

808

2133
```

### 输出

```
818

2222
```



---

---
title: "JULKA - Julka"
layout: "post"
diff: 普及/提高-
pid: SP54
tag: ['字符串', '数学', '高精度']
---

# JULKA - Julka

## 题目描述

 Julka surprised her teacher at preschool by solving the following riddle:

  _Klaudia and Natalia have 10 apples together, but Klaudia has two apples more than Natalia. How many apples does each of he girls have?_

 Julka said without thinking: Klaudia has 6 apples and Natalia 4 apples. The teacher tried to check if Julka's answer wasn't accidental and repeated the riddle every time increasing the numbers. Every time Julka answered correctly. The surprised teacher wanted to continue questioning Julka, but with big numbers she could't solve the riddle fast enough herself. Help the teacher and write a program which will give her the right answers.

   
Task
----

 Write a program which

- reads from standard input the number of apples the girls have together and how many more apples Klaudia has,
- counts the number of apples belonging to Klaudia and the number of apples belonging to Natalia,
- writes the outcome to standard output

## 输入格式

 Ten test cases (given one under another, you have to process all!). Every test case consists of two lines. The first line says how many apples both girls have together. The second line says how many more apples Klaudia has. Both numbers are positive integers. It is known that both girls have no more than 10 $ ^{100} $ (1 and 100 zeros) apples together. As you can see apples can be very small.

## 输出格式

For every test case your program should output two lines. The first line should contain the number of apples belonging to Klaudia. The second line should contain the number of apples belonging to Natalia.

## 样例 #1

### 输入

```
10

2

[and 9 test cases more]
```

### 输出

```
6

4

[and 9 test cases more]
```



---



---

# 题号列表

- SP4033 - PHONELST - Phone List
- SP5 - PALIN - The Next Palindrome
- SP54 - JULKA - Julka


---

---
title: "HAYBALE - Haybale stacking"
layout: "post"
diff: 普及/提高-
pid: SP10500
tag: ['树状数组', '概率论', '差分']
---

# HAYBALE - Haybale stacking

## 题目描述

Feeling sorry for all the mischief she has caused around the farm recently,



---



---

# 题号列表

- SP10500 - HAYBALE - Haybale stacking


---

---
title: "PT07Y - Is it a tree"
layout: "post"
diff: 普及/提高-
pid: SP1436
tag: ['图论', '并查集', '拓扑排序']
---

# PT07Y - Is it a tree

## 题目描述

有一个N个点M条边的图。 请问，该图是否为树。

## 输入格式

第1行2个数N,M。

接下来M行，每行2个数A,B，表示一条边（A,B）。

## 输出格式

如果该图为树，输出“YES”，否则输出“NO”。

数据范围： 0<N<=10000 0<=M<=20000

感谢@qq1010903229 提供的翻译

## 样例 #1

### 输入

```
3 2
1 2
2 3
```

### 输出

```
YES
```



---



---

# 题号列表

- SP1436 - PT07Y - Is it a tree


---

---
title: "KOZE - Sheep"
layout: "post"
diff: 普及/提高-
pid: SP12880
tag: ['广度优先搜索 BFS', '队列']
---

# KOZE - Sheep

## 题目描述

$a$ 行 $b$ 列（$3 \leq a,b \leq250$）的矩阵中：

- 字符 `.` 表示空白字段。

- 字符 `#` 表示一个围栏。

- 字符 `k` 代表绵羊。

- 字符 `v` 代表狼。

狼和羊存活的规则为：
1. 如果一片区域中羊比狼多，全部狼会死掉，**否则**全部羊会死掉。

2. 如果一个地方可以不通过围栏走出矩阵，该地区羊和狼**都会存活**。

求最后能有几只羊与狼。

## 输入格式

第1行：两个由空格分开的整数，R ,C (3≤R ,C≤250) 代表院子的长与宽；
      第2到R+1行: 给出院子情况图。

## 输出格式

仅一行，输出院子里最后会有几只羊与狼的数目，先输出羊，中间用一个空格格开。

【样例】
koze.in
8 8 
.######. 
#..k...# 
#.####.# 
#.#v.#.# 
#.#.k#k# 
#k.##..# 
#.v..v.# 
.######.	koze.out
3  1


【试题来源】
本题来源于克罗地亚2005年分区赛高年级组第三题，翻译来源于海州高中。

## 样例 #1

### 输入

```
\n8 8  \n.######.  \n#..k...#  \n#.####.#  \n#.#v.#.#  \n#.#.k#k#  \n#k.##..#  \n#.v..v.#  \n.######.
```

### 输出

```
3 1
```



---

---
title: "SHOP - Shopping"
layout: "post"
diff: 普及/提高-
pid: SP96
tag: ['广度优先搜索 BFS']
---

# SHOP - Shopping

## 题目描述

![Crowd in the supermarket](https://cdn.luogu.com.cn/upload/vjudge_pic/SP96/df9f7ec95f8af0b2332c4f2457bc0d39793311a7.png)The old tube screen to your computer turned out to be the cause of your chronic headaches. You therefore decide to buy one of these new flat TFT monitors. At the entrance of the computer shop you see that it is quite full with customers.

In fact, the shop is rather packed with customers and moving inside involves a certain amount of elbowing. Since you want to return home quickly to complete your half finished SPOJ tasks, you want to sidestep the crowd as much as possible. You examine the situation somewhat closer and realise that the crowding is less in some parts of the shop. Thus, there is reason for hope that you can reach your goal in due time, provided that you take the shortest way. But which way is the shortest way?

You sketch the situation on a piece of paper but even so, it is still a tricky affair. You take out your notebook from your pocket and start to write a program which will find the shortest way for you.

## 输入格式

The first line of the input specifies the width w and height h of the shop. Neither dimension exceeds 25.

The following h lines contain w characters each. A letter X symbolises a shelf, the letter S marks your starting position, and the letter D marks the destination (i.e. the square in front of the monitors). All free squares are marked with a digit from 1 to 9, meaning the number of seconds needed to pass this square.

There are many test cases separated by an empty line. Input terminates with width and height equal 0 0.

## 输出格式

Your program is to output the minimum number of seconds needed to reach to destination square. Each test case in a separate line. Movements can only be vertical and horizontal. Of course, all movements must take place inside the grid. There will always be a way to reach the destination.

## 样例 #1

### 输入

```
4 3

X1S3

42X4

X1D2



5 5

S5213

2X2X5

51248

4X4X2

1445D



0 0
```

### 输出

```
4

23
```



---



---

# 题号列表

- SP12880 - KOZE - Sheep
- SP96 - SHOP - Shopping


---

---
title: "PT07Y - Is it a tree"
layout: "post"
diff: 普及/提高-
pid: SP1436
tag: ['图论', '并查集', '拓扑排序']
---

# PT07Y - Is it a tree

## 题目描述

有一个N个点M条边的图。 请问，该图是否为树。

## 输入格式

第1行2个数N,M。

接下来M行，每行2个数A,B，表示一条边（A,B）。

## 输出格式

如果该图为树，输出“YES”，否则输出“NO”。

数据范围： 0<N<=10000 0<=M<=20000

感谢@qq1010903229 提供的翻译

## 样例 #1

### 输入

```
3 2
1 2
2 3
```

### 输出

```
YES
```



---

---
title: "STAMPS - Stamps"
layout: "post"
diff: 普及/提高-
pid: SP3375
tag: ['贪心', '排序']
---

# STAMPS - Stamps

## 题目描述

大家都讨厌Raymond。他是地球上最大的邮票收藏家，正因为如此，他总是在集邮聚会上取笑其他人。幸运的是，每个人都爱露西，她有自己的计划。她私下问她的朋友们是否可以借给她一些邮票，这样她就可以通过展示比Raymond更大的藏品来让Raymond难堪。Raymond对自己的优越性很有把握，所以他总是说他要展示多少邮票。露西知道她拥有多少邮票，所以她知道她还需要多少邮票。她也知道有多少朋友会借给她一些邮票。但她喜欢向尽可能少的朋友借邮票，如果她需要向太多的朋友借邮票，那么她宁愿根本不去与Raymond比。你能告诉她需要向多少朋友借邮票吗？

## 输入格式

第一行包含方案的数量。每个场景都描述了一个收藏家聚会，它的第一行告诉你露西需要借多少邮票(1 ~ 1000000)，还有多少朋友(1 ~ 1000)提供给她一些邮票。在第二行，你将得到邮票的数量(1 ~ 10000)，她的每个朋友提供的身份证(?)。

## 输出格式

每个场景的输出以包含**"Scenario #i:"**的一行开始，其中我是从1开始的场景数。然后用最少的朋友数量打印一行，露西需要向他们借邮票。如果这是不可能的，即使她从每个人那里借来了一切，那就写"**impossible**  "。**用空行终止方案的输出**

## 样例 #1

### 输入

```
3

100 6

13 17 42 9 23 57

99 6

13 17 42 9 23 57

1000 3

314 159 265
```

### 输出

```
Scenario #1:

3



Scenario #2:

2



Scenario #3:

impossible
```



---

---
title: "CODESPTB - Insertion Sort"
layout: "post"
diff: 普及/提高-
pid: SP9722
tag: ['排序']
---

# CODESPTB - Insertion Sort

## 题目描述

给定一个长度为 $n$ 的序列，求使其交换至有序（从小到大）的最少交换次数（逆序对）

## 输入格式

本题有多组数据

输入一个正整数 $T$，表示有 $T$ 组数据

对于每组数据

一个正整数 $n$

$n$ 个正整数表示这个序列

## 输出格式

换行输出每组序列的最小交换次数

## 说明/提示

$1 \le T \le 5$，$1 \le n \le {10}^5$，$1 \le a_i \le {10}^6$。

## 样例 #1

### 输入

```
2
5
1 1 1 2 2
5
2 1 3 1 2

```

### 输出

```
0
4

```



---



---

# 题号列表

- SP1436 - PT07Y - Is it a tree
- SP3375 - STAMPS - Stamps
- SP9722 - CODESPTB - Insertion Sort


---

---
title: "KOZE - Sheep"
layout: "post"
diff: 普及/提高-
pid: SP12880
tag: ['广度优先搜索 BFS', '队列']
---

# KOZE - Sheep

## 题目描述

$a$ 行 $b$ 列（$3 \leq a,b \leq250$）的矩阵中：

- 字符 `.` 表示空白字段。

- 字符 `#` 表示一个围栏。

- 字符 `k` 代表绵羊。

- 字符 `v` 代表狼。

狼和羊存活的规则为：
1. 如果一片区域中羊比狼多，全部狼会死掉，**否则**全部羊会死掉。

2. 如果一个地方可以不通过围栏走出矩阵，该地区羊和狼**都会存活**。

求最后能有几只羊与狼。

## 输入格式

第1行：两个由空格分开的整数，R ,C (3≤R ,C≤250) 代表院子的长与宽；
      第2到R+1行: 给出院子情况图。

## 输出格式

仅一行，输出院子里最后会有几只羊与狼的数目，先输出羊，中间用一个空格格开。

【样例】
koze.in
8 8 
.######. 
#..k...# 
#.####.# 
#.#v.#.# 
#.#.k#k# 
#k.##..# 
#.v..v.# 
.######.	koze.out
3  1


【试题来源】
本题来源于克罗地亚2005年分区赛高年级组第三题，翻译来源于海州高中。

## 样例 #1

### 输入

```
\n8 8  \n.######.  \n#..k...#  \n#.####.#  \n#.#v.#.#  \n#.#.k#k#  \n#k.##..#  \n#.v..v.#  \n.######.
```

### 输出

```
3 1
```



---

---
title: "最近公共祖先（LCA）"
layout: "post"
diff: 普及/提高-
pid: SP14932
tag: ['搜索', '倍增', '最近公共祖先 LCA']
---

# 最近公共祖先（LCA）

## 题目描述

> 树是一种简单无向图，图中任意两个节点仅被一条边连接。所有连通无环无向图都是一棵树。
>
> 最近公共祖先（LCA）是图论和计算机科学中的一个概念。设 $\text{T}$ 是一个有 $N$ 个节点的有根树，树上有两个节点 $v$ 和 $w$，而这两个节点的最近公共祖先是 $u$，那么 $u$ 是 $v$ 和 $w$ 在 $\text{T}$ 上的祖先（允许自己是自己的祖先），且在满足上面的前提的所有节点中，其在 $T$ 上的高度最低。
> 
>——摘自维基百科

现在，你需要对于给定的树 $\text{T}$ 以及两个节点 $v$ 和 $w$，求出它们的最近公共祖先。

如下图所示，图中 $9$ 号节点与 $12$ 号节点的最近公共祖先为 $3$ 号节点。

![](https://cdn.luogu.org/upload/vjudge_pic/SP14932/0b23f0487b06b8d674d23253a6db517f49ca3acf.png)

## 输入格式

输入共有 $T$ 组数据。

对于每一组数据：  
第一行输入一个整数 $N$ 表示节点个数（节点编号为 $1 \to N$ 中的一个数字）。  
接下来 $N$ 行，每行开头是一个整数 $M_i$，表示 $i$ 号节点的子节点数量，后面的 $M_i$ 个整数分别表示子节点编号。  
随后一行输入一个整数 $Q$，表示询问的 $v_i$ 及 $w_i$ 的组数。  
最后 $Q$ 行，每行输入两个整数 $v_i$ 和 $w_i$，代表要询问的两个节点。

## 输出格式

输出共有 $T$ 组数据。

对于每一组数据：  
第一行输出一个形如 `Case X:` 的字符串，其中的 `X` 表示第几组数据。  
接下来 $Q$ 行（每组数据不一），输出每组 $v_i$ 和 $w_i$ 的最近公共祖先。

## 说明/提示

### 样例解释

**样例输入 1**

```plain
1
7
3 2 3 4
0
3 5 6 7
0
0
0
0
2
5 7
2 7
```

**样例输出 1**

```plain
Case 1:
3
1
```

此样例在【题目描述】中有解释。

### 数据范围

对于 $100\%$ 的数据，$1 \le N \le 1000,0 \le M \le N - 1,1 \le Q \le 1000$。



---

---
title: "ABCDEF - ABCDEF"
layout: "post"
diff: 普及/提高-
pid: SP4580
tag: ['搜索', '枚举']
---

# ABCDEF - ABCDEF

## 题目描述

You are given a set S of integers between -30000 and 30000 (inclusive).

Find the total number of sextuples ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/60da4a6ec7452a0168508bec756f9c6a0109d346.png) that satisfy:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/5ae23b14079f628cec1090fc74b452939c2ffbe4.png)

### Input

The first line contains integer N (1

Elements of S are given in the next N lines, one integer per line. Given numbers will be distinct.

## 输出格式

Output the total number of plausible sextuples.

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
2
3

```

### 输出

```
4
```

## 样例 #3

### 输入

```
2
-1
1

```

### 输出

```
24
```

## 样例 #4

### 输入

```
3
5
7
10

```

### 输出

```
10
```



---

---
title: "SHOP - Shopping"
layout: "post"
diff: 普及/提高-
pid: SP96
tag: ['广度优先搜索 BFS']
---

# SHOP - Shopping

## 题目描述

![Crowd in the supermarket](https://cdn.luogu.com.cn/upload/vjudge_pic/SP96/df9f7ec95f8af0b2332c4f2457bc0d39793311a7.png)The old tube screen to your computer turned out to be the cause of your chronic headaches. You therefore decide to buy one of these new flat TFT monitors. At the entrance of the computer shop you see that it is quite full with customers.

In fact, the shop is rather packed with customers and moving inside involves a certain amount of elbowing. Since you want to return home quickly to complete your half finished SPOJ tasks, you want to sidestep the crowd as much as possible. You examine the situation somewhat closer and realise that the crowding is less in some parts of the shop. Thus, there is reason for hope that you can reach your goal in due time, provided that you take the shortest way. But which way is the shortest way?

You sketch the situation on a piece of paper but even so, it is still a tricky affair. You take out your notebook from your pocket and start to write a program which will find the shortest way for you.

## 输入格式

The first line of the input specifies the width w and height h of the shop. Neither dimension exceeds 25.

The following h lines contain w characters each. A letter X symbolises a shelf, the letter S marks your starting position, and the letter D marks the destination (i.e. the square in front of the monitors). All free squares are marked with a digit from 1 to 9, meaning the number of seconds needed to pass this square.

There are many test cases separated by an empty line. Input terminates with width and height equal 0 0.

## 输出格式

Your program is to output the minimum number of seconds needed to reach to destination square. Each test case in a separate line. Movements can only be vertical and horizontal. Of course, all movements must take place inside the grid. There will always be a way to reach the destination.

## 样例 #1

### 输入

```
4 3

X1S3

42X4

X1D2



5 5

S5213

2X2X5

51248

4X4X2

1445D



0 0
```

### 输出

```
4

23
```



---



---

# 题号列表

- SP12880 - KOZE - Sheep
- SP14932 - 最近公共祖先（LCA）
- SP4580 - ABCDEF - ABCDEF
- SP96 - SHOP - Shopping


---

---
title: "FAST2 - Fast Sum of two to an exponent"
layout: "post"
diff: 普及/提高-
pid: SP11383
tag: ['数学', '高精度']
---

# FAST2 - Fast Sum of two to an exponent

## 题目描述

There is people that really like to do silly thinks, one of them is sum the numbers from 2^0 to 2^n, task is actually really simple, just do a ultra fast sum of term 2^0 to 2^n

## 输入格式

the first line starts with a number, T, wich is the number of test cases, T lines will follow

each line contains a number "n" that is the nth term of the sum from 2^0 to 2^n

0<=n<=500

## 输出格式

Output the sum from 2^0 to 2^n MODULO 1298074214633706835075030044377087

## 样例 #1

### 输入

```
3\n0\n1\n2\n\n
```

### 输出

```
1\n3\n7 \n\nExtra: TLE is equal to 0.15s\n
```



---

---
title: "ADATEAMS - Ada and Teams"
layout: "post"
diff: 普及/提高-
pid: SP28304
tag: ['组合数学', '逆元']
---

# ADATEAMS - Ada and Teams

## 题目描述

有 $N$ 所学校，要从中选择 $A$ 所学校出来参赛。每一所学校中一共有 $B$ 名学生，每所参赛的学校会从中选择$D$ 名学生参赛，问一共有多少种不同的选择方案。

## 输入格式

多组数据，每组数据一行，包含 $N, A, B, D (1 \le A \le N ≤ 10^6, 1 \le D \le B \le 10^6)$ 四个整数。

## 输出格式

输出答案对 $10^9+7$ 取模的结果。



---

---
title: "JGTLE - Jalil Got TLE"
layout: "post"
diff: 普及/提高-
pid: SP34011
tag: ['数学', '枚举']
---

# JGTLE - Jalil Got TLE

## 题目描述

Ananta Jalil 是一个多才多艺的人。他可以完成任何对别人来说不可能的任务。最近，他学会了编程基础。在一个问题中，他提交了以下解决方案：

```cpp
#include <stdio.h>

int main()
{
   int t;
   scanf("%d", &t);
   for(int tc = 1; tc <= t; ++tc) {
       int a, b, c;
       scanf("%d %d %d", &a, &b, &c);
       long long result = 0;
       for(int i = 1; i <= a; ++i) {
           for(int j = 1; j <= b; ++j) {
               for(int k = 1; k <= c; ++k) {
                   result += j * k;
               }
           }
       }
       printf("Case %d: %lld\n", tc, result);
   }
   return 0;
}
```

但由于他是编程新手，他得到了 TLE（Time Limit Exceeded，超出时间限制）。因此他的解决方案效率不高。所以，你需要为 Jalil 编写一个优化的解决方案，以获得相同的输出。

## 输入格式

输入的第一行将包含一个正整数 $T$，表示测试用例的数量。

在每个测试用例中，将有 $3$ 个正整数 $a$、$b$ 和 $c$。

## 输出格式

对于每个测试用例，打印与上述程序相同的输出。


---

Translated by User 735713.

## 样例 #1

### 输入

```
3
1 4 3
3 4 2
143 342 777
```

### 输出

```
Case 1: 60
Case 2: 90
Case 3: 2535110464887
```



---

---
title: "PALIN - The Next Palindrome"
layout: "post"
diff: 普及/提高-
pid: SP5
tag: ['字符串', '数学', '枚举']
---

# PALIN - The Next Palindrome

## 题目描述

A positive integer is called a _palindrome_ if its representation in the decimal system is the same when read from left to right and from right to left. For a given positive integer _K_ of not more than 1000000 digits, write the value of the smallest palindrome larger than _K_ to output. Numbers are always displayed without leading zeros.

## 输入格式

The first line contains integer _t_, the number of test cases. Integers _K_ are given in the next _t_ lines.

## 输出格式

For each _K_, output the smallest palindrome larger than _K_.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages**

## 样例 #1

### 输入

```
2

808

2133
```

### 输出

```
818

2222
```



---

---
title: "JULKA - Julka"
layout: "post"
diff: 普及/提高-
pid: SP54
tag: ['字符串', '数学', '高精度']
---

# JULKA - Julka

## 题目描述

 Julka surprised her teacher at preschool by solving the following riddle:

  _Klaudia and Natalia have 10 apples together, but Klaudia has two apples more than Natalia. How many apples does each of he girls have?_

 Julka said without thinking: Klaudia has 6 apples and Natalia 4 apples. The teacher tried to check if Julka's answer wasn't accidental and repeated the riddle every time increasing the numbers. Every time Julka answered correctly. The surprised teacher wanted to continue questioning Julka, but with big numbers she could't solve the riddle fast enough herself. Help the teacher and write a program which will give her the right answers.

   
Task
----

 Write a program which

- reads from standard input the number of apples the girls have together and how many more apples Klaudia has,
- counts the number of apples belonging to Klaudia and the number of apples belonging to Natalia,
- writes the outcome to standard output

## 输入格式

 Ten test cases (given one under another, you have to process all!). Every test case consists of two lines. The first line says how many apples both girls have together. The second line says how many more apples Klaudia has. Both numbers are positive integers. It is known that both girls have no more than 10 $ ^{100} $ (1 and 100 zeros) apples together. As you can see apples can be very small.

## 输出格式

For every test case your program should output two lines. The first line should contain the number of apples belonging to Klaudia. The second line should contain the number of apples belonging to Natalia.

## 样例 #1

### 输入

```
10

2

[and 9 test cases more]
```

### 输出

```
6

4

[and 9 test cases more]
```



---

---
title: "TDKPRIME - Finding the Kth Prime"
layout: "post"
diff: 普及/提高-
pid: SP6470
tag: ['数学', '素数判断,质数,筛法']
---

# TDKPRIME - Finding the Kth Prime

## 题目描述

The problem statement is really simple. There are some queries. You are to give the answers.

## 输入格式

An integer stating the number of queries Q(equal to 50000), and Q lines follow, each containing one integer K between 1 and 5000000 inclusive.

## 输出格式

Q lines with the answer of each query: the Kth prime number.

## 样例 #1

### 输入

```
7

1

10

100

1000

10000

100000

1000000
```

### 输出

```
2

29

541

7919

104729

1299709

15485863
```



---



---

# 题号列表

- SP11383 - FAST2 - Fast Sum of two to an exponent
- SP28304 - ADATEAMS - Ada and Teams
- SP34011 - JGTLE - Jalil Got TLE
- SP5 - PALIN - The Next Palindrome
- SP54 - JULKA - Julka
- SP6470 - TDKPRIME - Finding the Kth Prime


---

---
title: "DIGOKEYS - Find the Treasure"
layout: "post"
diff: 普及/提高-
pid: SP15849
tag: ['最短路']
---

# DIGOKEYS - Find the Treasure

## 题目描述

一个喜欢玩锁和钥匙游戏并且逻辑很好的通灵者 Digo 有一天买了一套包含 $N$ 个盒子的装置，每个盒子都有一个从 $1$ 到 $N$（包括 $1$ 和 $N$）之间的唯一编号。除了第 $N$ 个盒子装有宝藏外，其他每个盒子里都有一把钥匙。由于制造缺陷，大多数钥匙可以打开多个盒子。

规则是每把钥匙只能用来打开一个盒子。除了第一个盒子外，所有盒子都是上锁的。Digo 急于得到宝藏，请求你找到一种方法，从第一个盒子里的钥匙开始，以最少的步骤打开最后一个盒子。

## 输入格式

第一行是一个整数 $T$，表示测试用例的数量。

对于每一个测试用例：

- 第一行是一个整数 $N$，表示盒子的数量。
- 接下来的 $N-1$ 行，第 $i$ 行有一个整数 $M_i$，表示第 $i$ 个盒子里的钥匙可以打开的盒子数量，随后是 $M_i$ 个整数，表示这些盒子的编号。

## 输出格式

对于每一个测试用例：

- 第一行是一个整数 $q$，表示打开盒子的最小数量。
- 第二行是按顺序打开的盒子编号，用空格隔开。如果有多种解法，输出字典序最小的一种。
- 如果无法到达最后一个盒子，输出 `-1`。

每个测试用例之间应有一个空行。

## 说明/提示

- $1 \le T \le 10$
- $2 \le N \le 100000$
- $1 \le M_i \le 10$

**样例输入**

```
2

3

1 2

1 3

4

2 2 3

1 1

2 2 4
```

**样例输出**

```
2

1 2

2

1 3
```



---

---
title: "ADATRIP - Ada and Trip"
layout: "post"
diff: 普及/提高-
pid: SP30669
tag: ['图论', '最短路']
---

# ADATRIP - Ada and Trip

## 题目描述

瓢虫 Ada 热爱旅游。她一边拍照，买纪念品，一边周游世界。这星期她去了布干达。普通游客会选择在主城区和一些大都市游玩。但是 Ada 不这么认为。她想走尽可能远的路（因为远离市中心的地方所拍摄的照片更有价值）。

问题来了，布干达非常大，她几乎猜不着哪个城市离她最远（通过最短路）。幸运的是，你在她身旁，于是，她向聪明博学的你发出了求救。你能告诉她最远的城市距离她的距离，以及有多少个这样的城市吗？

## 输入格式

第一行有 $3$ 个整数 $N,M,Q$。$1\le N\le 5 \times10^5,0\le M\le 10^6$。分别表示：城市数量，道路数量，提问数量。

接下来 $M$ 行一行 $3$ 个整数 $A,B,L$。$0\le A,B < N,0\le L\le 10$，表示有一条从 $A$ 市 到 $B$ 市距离为 $L$ 的无向边。

接下来 $Q$ 行，一行一个整数 $0\le Q_i < N$，表示出发的城市。

**保证输入数据满足 $\max({N,M})\times Q \le 10^7$。注意城市的编号从 $0$ 开始。**

**温馨提示：因为我们身处的是现实世界而非所谓的“图”，因此可能出现重边和自环。**

## 输出格式

共 $Q$ 行。一行两个整数，分别表示最远的距离，以及城市数量。

## 说明/提示

距离每个询问城市最远的城市编号如下：
```plain
0
2 3
3
2
8
4 8
4 8
4 8
4
4 8
```

## 样例 #1

### 输入

```
10 10 10
1 1 1
1 2 1
1 2 3 
3 1 1
5 4 10
8 5 10
5 6 5
6 7 3
6 9 3
9 7 4
0
1
2
3
4
5
6
7
8
9
```

### 输出

```
0 1
1 2
2 1
2 1
20 1
10 2
15 2
18 2
20 1
18 2
```



---



---

# 题号列表

- SP15849 - DIGOKEYS - Find the Treasure
- SP30669 - ADATRIP - Ada and Trip


---

---
title: "JGTLE - Jalil Got TLE"
layout: "post"
diff: 普及/提高-
pid: SP34011
tag: ['数学', '枚举']
---

# JGTLE - Jalil Got TLE

## 题目描述

Ananta Jalil 是一个多才多艺的人。他可以完成任何对别人来说不可能的任务。最近，他学会了编程基础。在一个问题中，他提交了以下解决方案：

```cpp
#include <stdio.h>

int main()
{
   int t;
   scanf("%d", &t);
   for(int tc = 1; tc <= t; ++tc) {
       int a, b, c;
       scanf("%d %d %d", &a, &b, &c);
       long long result = 0;
       for(int i = 1; i <= a; ++i) {
           for(int j = 1; j <= b; ++j) {
               for(int k = 1; k <= c; ++k) {
                   result += j * k;
               }
           }
       }
       printf("Case %d: %lld\n", tc, result);
   }
   return 0;
}
```

但由于他是编程新手，他得到了 TLE（Time Limit Exceeded，超出时间限制）。因此他的解决方案效率不高。所以，你需要为 Jalil 编写一个优化的解决方案，以获得相同的输出。

## 输入格式

输入的第一行将包含一个正整数 $T$，表示测试用例的数量。

在每个测试用例中，将有 $3$ 个正整数 $a$、$b$ 和 $c$。

## 输出格式

对于每个测试用例，打印与上述程序相同的输出。


---

Translated by User 735713.

## 样例 #1

### 输入

```
3
1 4 3
3 4 2
143 342 777
```

### 输出

```
Case 1: 60
Case 2: 90
Case 3: 2535110464887
```



---

---
title: "ABCDEF - ABCDEF"
layout: "post"
diff: 普及/提高-
pid: SP4580
tag: ['搜索', '枚举']
---

# ABCDEF - ABCDEF

## 题目描述

You are given a set S of integers between -30000 and 30000 (inclusive).

Find the total number of sextuples ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/60da4a6ec7452a0168508bec756f9c6a0109d346.png) that satisfy:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/5ae23b14079f628cec1090fc74b452939c2ffbe4.png)

### Input

The first line contains integer N (1

Elements of S are given in the next N lines, one integer per line. Given numbers will be distinct.

## 输出格式

Output the total number of plausible sextuples.

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
2
3

```

### 输出

```
4
```

## 样例 #3

### 输入

```
2
-1
1

```

### 输出

```
24
```

## 样例 #4

### 输入

```
3
5
7
10

```

### 输出

```
10
```



---

---
title: "PALIN - The Next Palindrome"
layout: "post"
diff: 普及/提高-
pid: SP5
tag: ['字符串', '数学', '枚举']
---

# PALIN - The Next Palindrome

## 题目描述

A positive integer is called a _palindrome_ if its representation in the decimal system is the same when read from left to right and from right to left. For a given positive integer _K_ of not more than 1000000 digits, write the value of the smallest palindrome larger than _K_ to output. Numbers are always displayed without leading zeros.

## 输入格式

The first line contains integer _t_, the number of test cases. Integers _K_ are given in the next _t_ lines.

## 输出格式

For each _K_, output the smallest palindrome larger than _K_.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages**

## 样例 #1

### 输入

```
2

808

2133
```

### 输出

```
818

2222
```



---

---
title: "NOSQ - No Squares Numbers"
layout: "post"
diff: 普及/提高-
pid: SP8496
tag: ['枚举', '素数判断,质数,筛法']
---

# NOSQ - No Squares Numbers

## 题目描述

A square free number is defined as a number which is not divisible by any square number.

For example, 13, 15, 210 are square free numbers, where as 25 (divisible by 5\*5), 108 (divisible by 6\*6), 18 (divisible by 3\*3) are not square free numbers. However number 1 is not considered to be a square and is a squarefree number.

Now you must find how many numbers from number a to b, are square free and also have a digit d inside it.

For example for in the range 10 to 40 te squarefree numbers having digit 3 are 13, 23, 30, 31, 33, 34, 35, 37, 38, 39

## 输入格式

The first line contains an integer T, which is the number of test-cases

Then follow T lines, each containing 3 integers a, b and d.

1 <= T <= 20,000

1 <= a <= b <= 100,000

0 <= d <= 9

## 输出格式

Print one integer which is the required number as described in the problem statement.

## 样例 #1

### 输入

```
3
10 40 3
1 100 4
1 100000 7
```

### 输出

```
10
9
26318
```



---



---

# 题号列表

- SP34011 - JGTLE - Jalil Got TLE
- SP4580 - ABCDEF - ABCDEF
- SP5 - PALIN - The Next Palindrome
- SP8496 - NOSQ - No Squares Numbers


---

---
title: "HAYBALE - Haybale stacking"
layout: "post"
diff: 普及/提高-
pid: SP10500
tag: ['树状数组', '概率论', '差分']
---

# HAYBALE - Haybale stacking

## 题目描述

Feeling sorry for all the mischief she has caused around the farm recently,



---



---

# 题号列表

- SP10500 - HAYBALE - Haybale stacking


---

---
title: "HAYBALE - Haybale stacking"
layout: "post"
diff: 普及/提高-
pid: SP10500
tag: ['树状数组', '概率论', '差分']
---

# HAYBALE - Haybale stacking

## 题目描述

Feeling sorry for all the mischief she has caused around the farm recently,



---



---

# 题号列表

- SP10500 - HAYBALE - Haybale stacking


---

---
title: "ULM09 - Dark roads"
layout: "post"
diff: 普及/提高-
pid: SP15650
tag: ['生成树']
---

# ULM09 - Dark roads

## 题目描述

Economic times these days are tough, even in Byteland. To reduce the operating costs, the government of Byteland has decided to optimize the road lighting. Till now every road was illuminated all night long, which costs 1 Bytelandian Dollar per meter and day. To save money, they decided to no longer illuminate every road, but to switch off the road lighting of some streets. To make sure that the inhabitants of Byteland still feel safe, they want to optimize the lighting in such a way, that after darkening some streets at night, there will still be at least one illuminated path from every junction in Byteland to every other junction.

What is the maximum daily amount of money the government of Byteland can save, without making their inhabitants feel unsafe?

#### Input Specification

The input file contains several test cases. Each test case starts with two numbers **_m_** and **_n_**, the number of junctions in Byteland and the number of roads in Byteland, respectively. Input is terminated by **_m=n=0_**. Otherwise, **_1_**  and **_m-1_** . Then follow **_n_** integer triples **_x, y, z_** specifying that there will be a bidirectional road between **_x_** and **_y_** with length **_z_** meters (0  and **_x ≠ y_**). The graph specified by each test case is connected. The total length of all roads in each test case is less than 2 $ ^{31} $ .

#### Output Specification

For each test case print one line containing the maximum daily amount the government can save.

#### Sample Input

 ```
7 11
0 1 7
0 3 5
1 2 8
1 3 9
1 4 7
2 4 5
3 4 15
3 5 6
4 5 8
4 6 9
5 6 11
0 0
```
#### Sample Output

51



---



---

# 题号列表

- SP15650 - ULM09 - Dark roads


---

---
title: "SNGPG - Prime Generator The Easiest Question Ever"
layout: "post"
diff: 普及/提高-
pid: SP15891
tag: ['数论', '素数判断,质数,筛法']
---

# SNGPG - Prime Generator The Easiest Question Ever

## 题目描述

给定区间 $[a, b]$，求该区间中满足 $p^2 + 1$ 或 $p^2 + 2$ 为质数的质数 $p$ 的数量。特别地，我们认为 $0$ 和 $1$ 也为质数。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

一行，两个整数 $a, b$。

## 输出格式

对于每组数据，输出一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
0 1
4 5
```
#### 输出 #1
```
2
0
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T < 100$，$0 \leq a \leq 5 \times 10^4$，$1 \leq b \leq 10^5$，$a < b$。

## 样例 #1

### 输入

```
2\n0 1\n4 5
```

### 输出

```
2\n0\n\n[Consider 0 and 1 as prime numbers for this question]
```



---

---
title: "ARRPRM - Prime is fun"
layout: "post"
diff: 普及/提高-
pid: SP30394
tag: ['动态规划 DP', '素数判断,质数,筛法', '前缀和']
---

# ARRPRM - Prime is fun

## 题目描述

给定一个长为 $n$ 的序列 $a$，从 $a$ 中选出若干个互不相连的长度均为质数的连续段，使这些连续段中的数的和最大。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

第一行，一个整数 $n$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$。

## 输出格式

对于每组数据：

一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
4
1 2 3 4
10
10 1 1 1 1 1 1 2 2 2
```
#### 输出 #1
```
9
21
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T \leq 100$，$1 \leq n \leq 2 \times 10^3$，$1 \leq a_i \leq 10^6$。



---

---
title: "TDKPRIME - Finding the Kth Prime"
layout: "post"
diff: 普及/提高-
pid: SP6470
tag: ['数学', '素数判断,质数,筛法']
---

# TDKPRIME - Finding the Kth Prime

## 题目描述

The problem statement is really simple. There are some queries. You are to give the answers.

## 输入格式

An integer stating the number of queries Q(equal to 50000), and Q lines follow, each containing one integer K between 1 and 5000000 inclusive.

## 输出格式

Q lines with the answer of each query: the Kth prime number.

## 样例 #1

### 输入

```
7

1

10

100

1000

10000

100000

1000000
```

### 输出

```
2

29

541

7919

104729

1299709

15485863
```



---

---
title: "NOSQ - No Squares Numbers"
layout: "post"
diff: 普及/提高-
pid: SP8496
tag: ['枚举', '素数判断,质数,筛法']
---

# NOSQ - No Squares Numbers

## 题目描述

A square free number is defined as a number which is not divisible by any square number.

For example, 13, 15, 210 are square free numbers, where as 25 (divisible by 5\*5), 108 (divisible by 6\*6), 18 (divisible by 3\*3) are not square free numbers. However number 1 is not considered to be a square and is a squarefree number.

Now you must find how many numbers from number a to b, are square free and also have a digit d inside it.

For example for in the range 10 to 40 te squarefree numbers having digit 3 are 13, 23, 30, 31, 33, 34, 35, 37, 38, 39

## 输入格式

The first line contains an integer T, which is the number of test-cases

Then follow T lines, each containing 3 integers a, b and d.

1 <= T <= 20,000

1 <= a <= b <= 100,000

0 <= d <= 9

## 输出格式

Print one integer which is the required number as described in the problem statement.

## 样例 #1

### 输入

```
3
10 40 3
1 100 4
1 100000 7
```

### 输出

```
10
9
26318
```



---



---

# 题号列表

- SP15891 - SNGPG - Prime Generator The Easiest Question Ever
- SP30394 - ARRPRM - Prime is fun
- SP6470 - TDKPRIME - Finding the Kth Prime
- SP8496 - NOSQ - No Squares Numbers


---

---
title: "SNGPG - Prime Generator The Easiest Question Ever"
layout: "post"
diff: 普及/提高-
pid: SP15891
tag: ['数论', '素数判断,质数,筛法']
---

# SNGPG - Prime Generator The Easiest Question Ever

## 题目描述

给定区间 $[a, b]$，求该区间中满足 $p^2 + 1$ 或 $p^2 + 2$ 为质数的质数 $p$ 的数量。特别地，我们认为 $0$ 和 $1$ 也为质数。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

一行，两个整数 $a, b$。

## 输出格式

对于每组数据，输出一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
0 1
4 5
```
#### 输出 #1
```
2
0
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T < 100$，$0 \leq a \leq 5 \times 10^4$，$1 \leq b \leq 10^5$，$a < b$。

## 样例 #1

### 输入

```
2\n0 1\n4 5
```

### 输出

```
2\n0\n\n[Consider 0 and 1 as prime numbers for this question]
```



---

---
title: "ARRPRM - Prime is fun"
layout: "post"
diff: 普及/提高-
pid: SP30394
tag: ['动态规划 DP', '素数判断,质数,筛法', '前缀和']
---

# ARRPRM - Prime is fun

## 题目描述

给定一个长为 $n$ 的序列 $a$，从 $a$ 中选出若干个互不相连的长度均为质数的连续段，使这些连续段中的数的和最大。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

第一行，一个整数 $n$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$。

## 输出格式

对于每组数据：

一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
4
1 2 3 4
10
10 1 1 1 1 1 1 2 2 2
```
#### 输出 #1
```
9
21
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T \leq 100$，$1 \leq n \leq 2 \times 10^3$，$1 \leq a_i \leq 10^6$。



---

---
title: "TDKPRIME - Finding the Kth Prime"
layout: "post"
diff: 普及/提高-
pid: SP6470
tag: ['数学', '素数判断,质数,筛法']
---

# TDKPRIME - Finding the Kth Prime

## 题目描述

The problem statement is really simple. There are some queries. You are to give the answers.

## 输入格式

An integer stating the number of queries Q(equal to 50000), and Q lines follow, each containing one integer K between 1 and 5000000 inclusive.

## 输出格式

Q lines with the answer of each query: the Kth prime number.

## 样例 #1

### 输入

```
7

1

10

100

1000

10000

100000

1000000
```

### 输出

```
2

29

541

7919

104729

1299709

15485863
```



---

---
title: "NOSQ - No Squares Numbers"
layout: "post"
diff: 普及/提高-
pid: SP8496
tag: ['枚举', '素数判断,质数,筛法']
---

# NOSQ - No Squares Numbers

## 题目描述

A square free number is defined as a number which is not divisible by any square number.

For example, 13, 15, 210 are square free numbers, where as 25 (divisible by 5\*5), 108 (divisible by 6\*6), 18 (divisible by 3\*3) are not square free numbers. However number 1 is not considered to be a square and is a squarefree number.

Now you must find how many numbers from number a to b, are square free and also have a digit d inside it.

For example for in the range 10 to 40 te squarefree numbers having digit 3 are 13, 23, 30, 31, 33, 34, 35, 37, 38, 39

## 输入格式

The first line contains an integer T, which is the number of test-cases

Then follow T lines, each containing 3 integers a, b and d.

1 <= T <= 20,000

1 <= a <= b <= 100,000

0 <= d <= 9

## 输出格式

Print one integer which is the required number as described in the problem statement.

## 样例 #1

### 输入

```
3
10 40 3
1 100 4
1 100000 7
```

### 输出

```
10
9
26318
```



---



---

# 题号列表

- SP15891 - SNGPG - Prime Generator The Easiest Question Ever
- SP30394 - ARRPRM - Prime is fun
- SP6470 - TDKPRIME - Finding the Kth Prime
- SP8496 - NOSQ - No Squares Numbers


---

---
title: "ADATEAMS - Ada and Teams"
layout: "post"
diff: 普及/提高-
pid: SP28304
tag: ['组合数学', '逆元']
---

# ADATEAMS - Ada and Teams

## 题目描述

有 $N$ 所学校，要从中选择 $A$ 所学校出来参赛。每一所学校中一共有 $B$ 名学生，每所参赛的学校会从中选择$D$ 名学生参赛，问一共有多少种不同的选择方案。

## 输入格式

多组数据，每组数据一行，包含 $N, A, B, D (1 \le A \le N ≤ 10^6, 1 \le D \le B \le 10^6)$ 四个整数。

## 输出格式

输出答案对 $10^9+7$ 取模的结果。



---



---

# 题号列表

- SP28304 - ADATEAMS - Ada and Teams


---

---
title: "ADATEAMS - Ada and Teams"
layout: "post"
diff: 普及/提高-
pid: SP28304
tag: ['组合数学', '逆元']
---

# ADATEAMS - Ada and Teams

## 题目描述

有 $N$ 所学校，要从中选择 $A$ 所学校出来参赛。每一所学校中一共有 $B$ 名学生，每所参赛的学校会从中选择$D$ 名学生参赛，问一共有多少种不同的选择方案。

## 输入格式

多组数据，每组数据一行，包含 $N, A, B, D (1 \le A \le N ≤ 10^6, 1 \le D \le B \le 10^6)$ 四个整数。

## 输出格式

输出答案对 $10^9+7$ 取模的结果。



---



---

# 题号列表

- SP28304 - ADATEAMS - Ada and Teams


---

---
title: "SCUBADIV - Scuba diver"
layout: "post"
diff: 普及/提高-
pid: SP181
tag: ['动态规划 DP', '背包 DP']
---

# SCUBADIV - Scuba diver

## 题目描述

A scuba diver uses a special equipment for diving. He has a cylinder with two containers: one with oxygen and the other with nitrogen. Depending on the time he wants to stay under water and the depth of diving the scuba diver needs various amount of oxygen and nitrogen. The scuba diver has at his disposal a certain number of cylinders. Each cylinder can be described by its weight and the volume of gas it contains. In order to complete his task the scuba diver needs specific amount of oxygen and nitrogen. What is the minimal total weight of cylinders he has to take to complete the task?

## 输入格式

The number of test cases _c_ is in the first line of input, then _c_ test cases follow separated by an empty line.

In the first line of a test case there are two integers _t_, _a_ separated by a single space, 1 <= _t_ <= 21 and 1 <= _a_ <= 79. They denote volumes of oxygen and nitrogen respectively, needed to complete the task. The second line contains one integer _n_, 1 <= _n_ <= 1000, which is the number of accessible cylinders. The following _n_ lines contain descriptions of cylinders; _i_-th line contains three integers _t_ _$ _{i} $_ , _a_ _$ _{i} $_ , _w_ _$ _{i} $_  separated by single spaces, (1 <= _t_ _$ _{i} $_  <= 21, 1 <= _a_ _$ _{i} $_  <= 79, 1 <= _w_ _$ _{i} $_  <= 800). These are respectively: volume of oxygen and nitrogen in the _i_-th cylinder and the weight of this cylinder.

## 输出格式

For each test case your program should output one line with the minimal total weight of cylinders the scuba diver should take to complete the task.

## 样例 #1

### 输入

```
1
5 60
5
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119

```

### 输出

```
249

```



---



---

# 题号列表

- SP181 - SCUBADIV - Scuba diver


---

---
title: "SNGPG - Prime Generator The Easiest Question Ever"
layout: "post"
diff: 普及/提高-
pid: SP15891
tag: ['数论', '素数判断,质数,筛法']
---

# SNGPG - Prime Generator The Easiest Question Ever

## 题目描述

给定区间 $[a, b]$，求该区间中满足 $p^2 + 1$ 或 $p^2 + 2$ 为质数的质数 $p$ 的数量。特别地，我们认为 $0$ 和 $1$ 也为质数。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

一行，两个整数 $a, b$。

## 输出格式

对于每组数据，输出一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
0 1
4 5
```
#### 输出 #1
```
2
0
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T < 100$，$0 \leq a \leq 5 \times 10^4$，$1 \leq b \leq 10^5$，$a < b$。

## 样例 #1

### 输入

```
2\n0 1\n4 5
```

### 输出

```
2\n0\n\n[Consider 0 and 1 as prime numbers for this question]
```



---

---
title: "ARRPRM - Prime is fun"
layout: "post"
diff: 普及/提高-
pid: SP30394
tag: ['动态规划 DP', '素数判断,质数,筛法', '前缀和']
---

# ARRPRM - Prime is fun

## 题目描述

给定一个长为 $n$ 的序列 $a$，从 $a$ 中选出若干个互不相连的长度均为质数的连续段，使这些连续段中的数的和最大。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

第一行，一个整数 $n$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$。

## 输出格式

对于每组数据：

一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
4
1 2 3 4
10
10 1 1 1 1 1 1 2 2 2
```
#### 输出 #1
```
9
21
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T \leq 100$，$1 \leq n \leq 2 \times 10^3$，$1 \leq a_i \leq 10^6$。



---

---
title: "TDKPRIME - Finding the Kth Prime"
layout: "post"
diff: 普及/提高-
pid: SP6470
tag: ['数学', '素数判断,质数,筛法']
---

# TDKPRIME - Finding the Kth Prime

## 题目描述

The problem statement is really simple. There are some queries. You are to give the answers.

## 输入格式

An integer stating the number of queries Q(equal to 50000), and Q lines follow, each containing one integer K between 1 and 5000000 inclusive.

## 输出格式

Q lines with the answer of each query: the Kth prime number.

## 样例 #1

### 输入

```
7

1

10

100

1000

10000

100000

1000000
```

### 输出

```
2

29

541

7919

104729

1299709

15485863
```



---

---
title: "NOSQ - No Squares Numbers"
layout: "post"
diff: 普及/提高-
pid: SP8496
tag: ['枚举', '素数判断,质数,筛法']
---

# NOSQ - No Squares Numbers

## 题目描述

A square free number is defined as a number which is not divisible by any square number.

For example, 13, 15, 210 are square free numbers, where as 25 (divisible by 5\*5), 108 (divisible by 6\*6), 18 (divisible by 3\*3) are not square free numbers. However number 1 is not considered to be a square and is a squarefree number.

Now you must find how many numbers from number a to b, are square free and also have a digit d inside it.

For example for in the range 10 to 40 te squarefree numbers having digit 3 are 13, 23, 30, 31, 33, 34, 35, 37, 38, 39

## 输入格式

The first line contains an integer T, which is the number of test-cases

Then follow T lines, each containing 3 integers a, b and d.

1 <= T <= 20,000

1 <= a <= b <= 100,000

0 <= d <= 9

## 输出格式

Print one integer which is the required number as described in the problem statement.

## 样例 #1

### 输入

```
3
10 40 3
1 100 4
1 100000 7
```

### 输出

```
10
9
26318
```



---



---

# 题号列表

- SP15891 - SNGPG - Prime Generator The Easiest Question Ever
- SP30394 - ARRPRM - Prime is fun
- SP6470 - TDKPRIME - Finding the Kth Prime
- SP8496 - NOSQ - No Squares Numbers


---

---
title: "SNGINT - Encode Integer"
layout: "post"
diff: 普及/提高-
pid: SP18273
tag: ['贪心']
---

# SNGINT - Encode Integer

## 题目描述

Given an integer N **(0 <= N < 10 $ ^{7} $ )**. Encode N into another possible smallest integer M **(M > 0)**, such that product of digits of M equals to N.

## 输入格式

First line input is T **(total no. of test cases)**, followed by T **(T < 10001)** lines containing integer N.

## 输出格式

For each N output M or -1 **(if encoding is not possible)** in each line.

## 样例 #1

### 输入

```
3

24

5

11
```

### 输出

```
38

5

-1
```



---

---
title: "STAMPS - Stamps"
layout: "post"
diff: 普及/提高-
pid: SP3375
tag: ['贪心', '排序']
---

# STAMPS - Stamps

## 题目描述

大家都讨厌Raymond。他是地球上最大的邮票收藏家，正因为如此，他总是在集邮聚会上取笑其他人。幸运的是，每个人都爱露西，她有自己的计划。她私下问她的朋友们是否可以借给她一些邮票，这样她就可以通过展示比Raymond更大的藏品来让Raymond难堪。Raymond对自己的优越性很有把握，所以他总是说他要展示多少邮票。露西知道她拥有多少邮票，所以她知道她还需要多少邮票。她也知道有多少朋友会借给她一些邮票。但她喜欢向尽可能少的朋友借邮票，如果她需要向太多的朋友借邮票，那么她宁愿根本不去与Raymond比。你能告诉她需要向多少朋友借邮票吗？

## 输入格式

第一行包含方案的数量。每个场景都描述了一个收藏家聚会，它的第一行告诉你露西需要借多少邮票(1 ~ 1000000)，还有多少朋友(1 ~ 1000)提供给她一些邮票。在第二行，你将得到邮票的数量(1 ~ 10000)，她的每个朋友提供的身份证(?)。

## 输出格式

每个场景的输出以包含**"Scenario #i:"**的一行开始，其中我是从1开始的场景数。然后用最少的朋友数量打印一行，露西需要向他们借邮票。如果这是不可能的，即使她从每个人那里借来了一切，那就写"**impossible**  "。**用空行终止方案的输出**

## 样例 #1

### 输入

```
3

100 6

13 17 42 9 23 57

99 6

13 17 42 9 23 57

1000 3

314 159 265
```

### 输出

```
Scenario #1:

3



Scenario #2:

2



Scenario #3:

impossible
```



---

---
title: "BOOKS1 - Copying Books"
layout: "post"
diff: 普及/提高-
pid: SP43
tag: ['动态规划 DP', '贪心', '进制']
---

# BOOKS1 - Copying Books

## 样例 #1

### 输入

```
2

9 3

100 200 300 400 500 600 700 800 900

5 4

100 100 100 100 100
```

### 输出

```
100 200 300 400 500 / 600 700 / 800 900

100 / 100 / 100 / 100 100
```



---



---

# 题号列表

- SP18273 - SNGINT - Encode Integer
- SP3375 - STAMPS - Stamps
- SP43 - BOOKS1 - Copying Books


---

---
title: "BOOKS1 - Copying Books"
layout: "post"
diff: 普及/提高-
pid: SP43
tag: ['动态规划 DP', '贪心', '进制']
---

# BOOKS1 - Copying Books

## 样例 #1

### 输入

```
2

9 3

100 200 300 400 500 600 700 800 900

5 4

100 100 100 100 100
```

### 输出

```
100 200 300 400 500 / 600 700 / 800 900

100 / 100 / 100 / 100 100
```



---

---
title: "NEG2 - The Moronic Cowmpouter"
layout: "post"
diff: 普及/提高-
pid: SP739
tag: ['进制']
---

# NEG2 - The Moronic Cowmpouter

## 题目描述

Inexperienced in the digital arts, the cows tried to build a calculating engine (yes, it's a cowmpouter) using binary numbers (base 2) but instead built one based on base negative 2! They were quite pleased since numbers expressed in base -2 do not have a sign bit.

 You know number bases have place values that start at 1 (base to the 0 power) and proceed right-to-left to base^1, base^2, and so on. In base -2, the place values are 1, -2, 4, -8, 16, -32, ... (reading from right to left). Thus, counting from 1 goes like this: 1, 110, 111, 100, 101, 11010, 11011, 11000, 11001, and so on.

 Eerily, negative numbers are also represented with 1's and 0's but no sign. Consider counting from -1 downward: 11, 10, 1101, 1100, 1111, and so on.

 Please help the cows convert ordinary decimal integers (range -2,000,000,000 .. 2,000,000,000) to their counterpart representation in base -2.

## 输入格式

A single integer to be converted to base -2

## 输出格式

A single integer with no leading zeroes that is the input integer converted to base -2. The value 0 is expressed as 0, with exactly one 0.

## 样例 #1

### 输入

```
-13
```

### 输出

```
110111
```



---



---

# 题号列表

- SP43 - BOOKS1 - Copying Books
- SP739 - NEG2 - The Moronic Cowmpouter


---

---
title: "KOZE - Sheep"
layout: "post"
diff: 普及/提高-
pid: SP12880
tag: ['广度优先搜索 BFS', '队列']
---

# KOZE - Sheep

## 题目描述

$a$ 行 $b$ 列（$3 \leq a,b \leq250$）的矩阵中：

- 字符 `.` 表示空白字段。

- 字符 `#` 表示一个围栏。

- 字符 `k` 代表绵羊。

- 字符 `v` 代表狼。

狼和羊存活的规则为：
1. 如果一片区域中羊比狼多，全部狼会死掉，**否则**全部羊会死掉。

2. 如果一个地方可以不通过围栏走出矩阵，该地区羊和狼**都会存活**。

求最后能有几只羊与狼。

## 输入格式

第1行：两个由空格分开的整数，R ,C (3≤R ,C≤250) 代表院子的长与宽；
      第2到R+1行: 给出院子情况图。

## 输出格式

仅一行，输出院子里最后会有几只羊与狼的数目，先输出羊，中间用一个空格格开。

【样例】
koze.in
8 8 
.######. 
#..k...# 
#.####.# 
#.#v.#.# 
#.#.k#k# 
#k.##..# 
#.v..v.# 
.######.	koze.out
3  1


【试题来源】
本题来源于克罗地亚2005年分区赛高年级组第三题，翻译来源于海州高中。

## 样例 #1

### 输入

```
\n8 8  \n.######.  \n#..k...#  \n#.####.#  \n#.#v.#.#  \n#.#.k#k#  \n#k.##..#  \n#.v..v.#  \n.######.
```

### 输出

```
3 1
```



---



---

# 题号列表

- SP12880 - KOZE - Sheep


---

---
title: "FAST2 - Fast Sum of two to an exponent"
layout: "post"
diff: 普及/提高-
pid: SP11383
tag: ['数学', '高精度']
---

# FAST2 - Fast Sum of two to an exponent

## 题目描述

There is people that really like to do silly thinks, one of them is sum the numbers from 2^0 to 2^n, task is actually really simple, just do a ultra fast sum of term 2^0 to 2^n

## 输入格式

the first line starts with a number, T, wich is the number of test cases, T lines will follow

each line contains a number "n" that is the nth term of the sum from 2^0 to 2^n

0<=n<=500

## 输出格式

Output the sum from 2^0 to 2^n MODULO 1298074214633706835075030044377087

## 样例 #1

### 输入

```
3\n0\n1\n2\n\n
```

### 输出

```
1\n3\n7 \n\nExtra: TLE is equal to 0.15s\n
```



---

---
title: "FCTRL2 - Small factorials"
layout: "post"
diff: 普及/提高-
pid: SP24
tag: ['高精度']
---

# FCTRL2 - Small factorials

## 题目描述

要求计算小的正整数的阶乘。

## 输入格式

一个正整数 $t(1\leq t\leq100)$，表示数据个数。接下来 $t$ 行，每行一个正整数 $n(1\leq n\leq 100)$。

## 输出格式

对于每个输入的正整数 $n$，输出一行结果表示 $n$ 的阶乘。


Translated by @leylee @PC_DOS

## 样例 #1

### 输入

```
4
1
2
5
3
```

### 输出

```
1
2
120
6
```



---

---
title: "JULKA - Julka"
layout: "post"
diff: 普及/提高-
pid: SP54
tag: ['字符串', '数学', '高精度']
---

# JULKA - Julka

## 题目描述

 Julka surprised her teacher at preschool by solving the following riddle:

  _Klaudia and Natalia have 10 apples together, but Klaudia has two apples more than Natalia. How many apples does each of he girls have?_

 Julka said without thinking: Klaudia has 6 apples and Natalia 4 apples. The teacher tried to check if Julka's answer wasn't accidental and repeated the riddle every time increasing the numbers. Every time Julka answered correctly. The surprised teacher wanted to continue questioning Julka, but with big numbers she could't solve the riddle fast enough herself. Help the teacher and write a program which will give her the right answers.

   
Task
----

 Write a program which

- reads from standard input the number of apples the girls have together and how many more apples Klaudia has,
- counts the number of apples belonging to Klaudia and the number of apples belonging to Natalia,
- writes the outcome to standard output

## 输入格式

 Ten test cases (given one under another, you have to process all!). Every test case consists of two lines. The first line says how many apples both girls have together. The second line says how many more apples Klaudia has. Both numbers are positive integers. It is known that both girls have no more than 10 $ ^{100} $ (1 and 100 zeros) apples together. As you can see apples can be very small.

## 输出格式

For every test case your program should output two lines. The first line should contain the number of apples belonging to Klaudia. The second line should contain the number of apples belonging to Natalia.

## 样例 #1

### 输入

```
10

2

[and 9 test cases more]
```

### 输出

```
6

4

[and 9 test cases more]
```



---



---

# 题号列表

- SP11383 - FAST2 - Fast Sum of two to an exponent
- SP24 - FCTRL2 - Small factorials
- SP54 - JULKA - Julka


---

---
title: "SUMFOUR - 4 values whose sum is 0"
layout: "post"
diff: 普及+/提高
pid: SP1296
tag: ['搜索', '二分', '枚举']
---

# SUMFOUR - 4 values whose sum is 0

## 题目描述

The SUM problem can be formulated as follows: given four lists A, B, C, D of integer values, compute how many quadruplet (a, b, c, d ) belongs to A x B x C x D are such that a + b + c + d = 0 . In the following, we assume that all lists have the same size n

## 输入格式

 The first line of the input file contains the size of the lists n (this value can be as large as 4000). We then have n lines containing four integer values (with absolute value as large as 2 $ ^{28} $ ) that belong respectively to A, B, C and D .

(**Edited:** n <= 2500)

## 输出格式

Output should be printed on a single line.

## 样例 #1

### 输入

```
6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45
```

### 输出

```
5
```



---

---
title: "BUGLIFE - A Bug&#8217;s Life"
layout: "post"
diff: 普及+/提高
pid: SP3377
tag: ['并查集', '拓扑排序', '二分图']
---

# BUGLIFE - A Bug&#8217;s Life

## 题目描述

Professor Hopper is researching the sexual behavior of a rare species of bugs. He assumes that they feature two different genders and that they only interact with bugs of the opposite gender. In his experiment, individual bugs and their interactions were easy to identify, because numbers were printed on their backs.  
  
 Given a list of bug interactions, decide whether the experiment supports his assumption of two genders with no homosexual bugs or if it contains some bug interactions that falsify it.

## 输入格式

The first line of the input contains the number of scenarios. Each scenario starts with one line giving the number of bugs (at least one, and up to 2000) and the number of interactions (up to 1000000) separated by a single space. In the following lines, each interaction is given in the form of two distinct bug numbers separated by a single space. Bugs are numbered consecutively starting from one.

## 输出格式

The output for every scenario is a line containing “Scenario #i:”, where i is the number of the scenario starting at 1, followed by one line saying either “No suspicious bugs found!” if the experiment is consistent with his assumption about the bugs’ sexual behavior, or “Suspicious bugs found!” if Professor Hopper’s assumption is definitely wrong.

## 样例 #1

### 输入

```
2

3 3

1 2

2 3

1 3

4 2

1 2

3 4
```

### 输出

```
Scenario #1:

Suspicious bugs found!

Scenario #2:

No suspicious bugs found!
```



---



---

# 题号列表

- SP1296 - SUMFOUR - 4 values whose sum is 0
- SP3377 - BUGLIFE - A Bug&#8217;s Life


---

---
title: "LITE - Light Switching"
layout: "post"
diff: 普及+/提高
pid: SP7259
tag: ['线段树', '递归', '分块']
---

# LITE - Light Switching

## 题目描述

  
Farmer John tries to keep the cows sharp by letting them play with intellectual toys. One of the larger toys is the lights in the barn. Each of the N (2 <= N <= 100,000) cow stalls conveniently numbered 1..N has a colorful light above it.  
  
At the beginning of the evening, all the lights are off. The cows control the lights with a set of N pushbutton switches that toggle the lights; pushing switch i changes the state of light i from off to on or from on to off.  
  
The cows read and execute a list of M (1 <= M <= 100,000) operations expressed as one of two integers (0 <= operation <= 1).  
  
The first kind of operation (denoted by a 0 command) includes two subsequent integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) that indicate a starting switch and ending switch. They execute the operation by pushing each pushbutton from S\_i through E\_i inclusive exactly once.  
  
The second kind of operation (denoted by a 1 command) asks the cows to count how many lights are on in the range given by two integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) which specify the inclusive range in which the cows should count the number of lights that are on.  
  
Help FJ ensure the cows are getting the correct answer by processing the list and producing the proper counts.

## 输入格式

  
Line 1: Two space-separated integers: N and M  
Lines 2..M+1: Each line represents an operation with three space-separated integers: operation, S\_i, and E\_i

## 输出格式

Lines 1..number of queries: For each output query, print the count as an integer by itself on a single line.

## 样例 #1

### 输入

```
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4

```

### 输出

```
1
2
```



---



---

# 题号列表

- SP7259 - LITE - Light Switching


---

---
title: "TRT - Treats for the Cows"
layout: "post"
diff: 普及+/提高
pid: SP740
tag: ['前缀和']
---

# TRT - Treats for the Cows

## 题目描述

FJ经常给产奶量高的奶牛发特殊津贴，于是很快奶牛们拥有了大笔不知该怎么花的钱．为此，约翰购置了N(1≤N≤2000)份美味的零食来卖给奶牛们．每天FJ售出一份零食．当然FJ希望这些零食全部售出后能得到最大的收益．这些零食有以下这些有趣的特性：

•零食按照1．．N编号，它们被排成一列放在一个很长的盒子里．盒子的两端都有开口，FJ每天可以从盒子的任一端取出最外面的一个．

•与美酒与好吃的奶酪相似，这些零食储存得越久就越好吃．当然，这样FJ就可以把它们卖出更高的价钱．

•每份零食的初始价值不一定相同．FJ进货时，第i份零食的初始价值为Vi(1≤Vi≤1000)(Vi指的是从盒子顶端往下的第i份零食的初始价值)．

•第i份零食如果在被买进后的第a天出售，则它的售价是vi×a．

FJ告诉了你所有零食的初始价值，并希望你能帮他计算一下，在这些零食全被卖出后，他最多能得到多少钱．

## 输入格式

第一行：一个整数n。
接下来的n行：每行一个整数Vi。

## 输出格式

FJ通过出售零食最多能得到的钱数。

## 样例 #1

### 输入

```
5
1
3
1
5
2
```

### 输出

```
43
```



---



---

# 题号列表

- SP740 - TRT - Treats for the Cows


---

---
title: "PR003004 - Digit Sum"
layout: "post"
diff: 普及+/提高
pid: SP17247
tag: ['动态规划 DP', '数位 DP']
---

# PR003004 - Digit Sum

## 题目描述

For a pair of integers a and b, the digit sum of the interval \[a,b\] is defined as the sum of all digits occurring in all numbers between (and including) a and b. For example, the digit sum of \[28, 31\] can be calculated as:

## 输入格式

On the first line one positive number: the number of test cases, at most 100.

After that per test case:

- one line with two space-separated integers, a and b (0 <= a <= b <= 10^15).

## 输出格式

Per test case:

- one line with an integer: the digit sum of \[a,b\];

## 样例 #1

### 输入

```
3

0 10

28 31

1234 56789
```

### 输出

```
46

28

1128600
```



---

---
title: "NAPTIME - Naptime"
layout: "post"
diff: 普及+/提高
pid: SP283
tag: ['动态规划 DP']
---

# NAPTIME - Naptime

## 题目描述

在某个星球上，一天由 $n$ 小时构成。我们称 $0 \sim 1$ 点为第一个小时，$1 \sim 2$ 点为第二个小时，以此类推。在第 $i$ 个小时睡觉能恢复 $U_i$ 点体力。在这座星球上住着一头牛，它每天要休息 $B$ 个小时，它休息的这 $B$ 个小时可以不连续，可以分成若干段，但是在每一段的第一个小时不能恢复体力，从第二个小时开始才可以恢复体力。
为了身体健康，这头牛希望遵循生物钟，每天采用相同的睡觉计划。另外，因为时间是连续的，每天的第 $n$ 个小时与下一天的第一个小时是相连的，这头牛只需要在 $n$ 个小时内休息 $B$ 个小时就够了。
请你给这头牛安排一个任务计划，使得它每天恢复的体力最多。

## 输入格式

第一行一个整数 $T$ 表示有 $T$ 组测试数据
对于每一组测试数据，第一行为两个整数 $n$ 与 $B$，接下来 $n$ 行每行一个整数 $U_i$。$2 \le B < N \le 3830 , 0 \le Ui \le 2 \times 10^5$。

## 输出格式

对于每组输入数据，对应一行输出一个整数，表示答案。（注意：两组输出之间没有空行）

## 样例 #1

### 输入

```
1

5 3

2

0

3

1

4
```

### 输出

```
6



Input/Output details:

The day is divided into 5 periods, with utilities 2, 0, 3, 1, 4 in that 

order. Goneril must pick 3 periods.



Goneril can get total utility 6 by being in bed during periods 4,

5, and 1, with utilities 0 [getting to sleep], 4, and 2

respectively.
```



---

---
title: "MDIGITS - Counting Digits"
layout: "post"
diff: 普及+/提高
pid: SP3928
tag: ['动态规划 DP', '数位 DP']
---

# MDIGITS - Counting Digits

## 题目描述

给定两个整数 $a$ 和 $b$，我们在列表中写出 $a$ 和 $b$ 之间的数字。您的任务是计算每个数字的出现次数。

例如，如果 $a = 1024$ 且 $b = 1032$，则列表将为 $\begin{bmatrix} 1024 &1025& 1026& 1027& 1028& 1029& 1030& 1031& 1032 \end{bmatrix}$，列表中有 $10$ 个 $0$，$10$ 个 $ 1$，$7$ 个 $2$，$3$ 个 $3$ 等。

## 输入格式

输入最多包含 $500$ 行。每行包含两个数字 $a$ 和 $b$，其中 $0 <a, b <10 ^ 8$。输入由 `0 0` 终止。

## 输出格式

对于每对输入，输出包含由单个空格分隔的十个数字的行。第一个数字是数字 $0$ 的出现次数，第二个数字是数字 $1$ 的出现次数……以此类推。

Translated by @留守新手村



---



---

# 题号列表

- SP17247 - PR003004 - Digit Sum
- SP283 - NAPTIME - Naptime
- SP3928 - MDIGITS - Counting Digits


---

---
title: "NAJPF - Pattern Find"
layout: "post"
diff: 普及+/提高
pid: SP21524
tag: ['模拟', '字符串', 'KMP 算法']
---

# NAJPF - Pattern Find

## 题目描述

### 题意：

给出两个字符串 $A,B$ ，求 $B$ 在 $A$ 中所有出现的次数和每一次出现的位置。假如没有出现输出`Not Found`。

## 输入格式

本题有多组数据。

第一行一个整数 $T（ 1≤T≤50）$，表示数据组数。

对于每组数据：

每行两个字符串 $A,B$。所有字符均为小写英文字符， $1≤| A |,| B |≤{10^6}$
 。

## 输出格式

对于每次询问，第一行一个整数 $n$，表示 $B$ 在 $A$ 中出现的次数。

第二行 $n$ 个整数,表示每一次出现的位置。

如果没有出现，输出`Not Found`。

每次询问之间有一个空行。

### 输入输出样例
#### 输入 #1
```
3
ababab ab
aaaaa bbb
aafafaasf aaf
```

#### 输出 #1
```
3
1 3 5

Not Found

1
1
```



---



---

# 题号列表

- SP21524 - NAJPF - Pattern Find


---

---
title: "CORNET - Corporative Network"
layout: "post"
diff: 普及+/提高
pid: SP264
tag: ['并查集', '递归']
---

# CORNET - Corporative Network

## 题目描述

原本有 $n$ 个节点，最初每个节点的父亲都是自己。

现在给你若干操作，共分为两种，操作格式如下：

1. `I x y`（大写字母`I`）

将 $x$ 的父亲变为 $y$，而且令 $x$ 与 $y$ 之间的距离为 $\lvert x-y \rvert \bmod 1000$。

2. `E x` 询问x点到其根节点的距离

数据保证对于所有的 $1$ 操作合法，即保证之前 $y$ 不是 $x$ 的父亲、

## 输入格式

第一行输入一个整数 $T$，表示每个数据点的数据组数。


第一行包含一个正整数 $n$，表示原有的节点个数


`I x y` 或`E x` 分别代表以上的两种操作

对于这些操作，以输入一个`O`（大写字母`O`）为终止。

## 输出格式

一共若干行，表示对于每一组测试数据中的 `E` 操作输出答案。

## 样例 #1

### 输入

```
1
4
E 3
I 3 1
E 3
I 1 2
E 3
I 2 4
E 3
O
```

### 输出

```
0
2
3
5
```



---

---
title: "BUGLIFE - A Bug&#8217;s Life"
layout: "post"
diff: 普及+/提高
pid: SP3377
tag: ['并查集', '拓扑排序', '二分图']
---

# BUGLIFE - A Bug&#8217;s Life

## 题目描述

Professor Hopper is researching the sexual behavior of a rare species of bugs. He assumes that they feature two different genders and that they only interact with bugs of the opposite gender. In his experiment, individual bugs and their interactions were easy to identify, because numbers were printed on their backs.  
  
 Given a list of bug interactions, decide whether the experiment supports his assumption of two genders with no homosexual bugs or if it contains some bug interactions that falsify it.

## 输入格式

The first line of the input contains the number of scenarios. Each scenario starts with one line giving the number of bugs (at least one, and up to 2000) and the number of interactions (up to 1000000) separated by a single space. In the following lines, each interaction is given in the form of two distinct bug numbers separated by a single space. Bugs are numbered consecutively starting from one.

## 输出格式

The output for every scenario is a line containing “Scenario #i:”, where i is the number of the scenario starting at 1, followed by one line saying either “No suspicious bugs found!” if the experiment is consistent with his assumption about the bugs’ sexual behavior, or “Suspicious bugs found!” if Professor Hopper’s assumption is definitely wrong.

## 样例 #1

### 输入

```
2

3 3

1 2

2 3

1 3

4 2

1 2

3 4
```

### 输出

```
Scenario #1:

Suspicious bugs found!

Scenario #2:

No suspicious bugs found!
```



---



---

# 题号列表

- SP264 - CORNET - Corporative Network
- SP3377 - BUGLIFE - A Bug&#8217;s Life


---

---
title: "KATHTHI - KATHTHI"
layout: "post"
diff: 普及+/提高
pid: SP22393
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# KATHTHI - KATHTHI

## 题目描述

```
         Kathiresan is initially locked at cell (0,0) in a highly guarded rectangular prison of order RxC. He must reach the gate at (R-1,C-1) in order to escape from the prison. Kathiresan can move from any cell, to any of it's 4 adjacent cells (North, East, West and South). If Kathiresan is currently at (x1,y1), then he can move to (x2,y2) if and only if abs(x2-x1)+abs(y2-y1) == 1 and 0<=x2<R and 0<=y2<CKathiresan somehow manages to get the map of the prison.
If map[x1][y1] == map[x2][y2] then Kathiresan can move from (x1,y1) to (x2,y2) without killing any guards.
If map[x1][y1] != map[x2][y2], then Kathiresan can move from (x1,y1) to (x2,y2) by killing a guard.

Given the map of the prison, find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input:
The first line consists of an integer t, the number of test cases. For each test case, the first line consists of two integers R and C representing the order of the rectangular prison followed by R strings representing the map of the rectangular prison.
 
Output:
For each test case find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input Constraints:
1 <= t <= 10
2 <= R <= 1000
2 <= C <= 1000
'a' <= map[i][j] <= 'z'
Sample Input:
4
2 2
aa
aa
2 3
abc
def6 6akacccaaacfcamdfccaokhddzyxwdpzyxwdd5 5abbbcabaccaaaccaefcicdgdd Sample Output:
0
322
```

## 样例 #1

### 输入

```
4
2 2
aa
aa
2 3
abc
def
6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd
5 5
abbbc
abacc
aaacc
aefci
cdgdd

```

### 输出

```
0
3
2
2
```



---

---
title: "PUBLICAT - Publication"
layout: "post"
diff: 普及+/提高
pid: SP9255
tag: ['广度优先搜索 BFS']
---

# PUBLICAT - Publication

## 题目描述

Orizondo 数用于衡量某个科学家与 Rodrigo Orizondo 在学术论文合著中的“合作距离”。Rodrigo Orizondo 的 Orizondo 数是零。要获得有限的 Orizondo 数，科学家必须与至少一个已有有限 Orizondo 数的科学家共同发表论文。一个科学家的 Orizondo 数是他所有合作者中最低的 Orizondo 数加一。论文发表的顺序和编号分配顺序无关，因为每次发表后，系统会自动更新所有作者的 Orizondo 数。

你将得到一组 **论文** 数据，每篇论文包含一组作者，格式为 “AUTHOR\_1 AUTHOR\_2 ... AUTHOR\_N”（引号仅为明确表示）。其中，Rodrigo Orizondo 用 “ORIZONDO” 表示。

请输出所有作者的 Orizondo 数。输出格式为 “AUTHOR NUMBER”，若无法为某作者赋予有限的 Orizondo 数，仅输出 “AUTHOR”。作者的输出顺序应按字典序排列。

## 输入格式

第一行输入一个整数 \( C \)，表示测试用例的数量（\( 0 < C \)）。

每个测试用例首先包含一个整数 \( N \)，表示论文的数量，接着是 \( N \) 行，每行包含一组用空格分隔的作者姓名。

## 输出格式

对于每个测试用例，输出一行，包含每个作者及其 Orizondo 数，信息之间用空格分隔。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
1
ORIZONDO
2
KLEITMAN LANDER
ORIZONDO KLEITMAN
4
ORIZONDO B
A B C
B A E
D F
```

### 输出

```
ORIZONDO 0
KLEITMAN 1 LANDER 2 ORIZONDO 0
A 2 B 1 C 2 D E 2 F ORIZONDO 0
```



---



---

# 题号列表

- SP22393 - KATHTHI - KATHTHI
- SP9255 - PUBLICAT - Publication


---

---
title: "BUGLIFE - A Bug&#8217;s Life"
layout: "post"
diff: 普及+/提高
pid: SP3377
tag: ['并查集', '拓扑排序', '二分图']
---

# BUGLIFE - A Bug&#8217;s Life

## 题目描述

Professor Hopper is researching the sexual behavior of a rare species of bugs. He assumes that they feature two different genders and that they only interact with bugs of the opposite gender. In his experiment, individual bugs and their interactions were easy to identify, because numbers were printed on their backs.  
  
 Given a list of bug interactions, decide whether the experiment supports his assumption of two genders with no homosexual bugs or if it contains some bug interactions that falsify it.

## 输入格式

The first line of the input contains the number of scenarios. Each scenario starts with one line giving the number of bugs (at least one, and up to 2000) and the number of interactions (up to 1000000) separated by a single space. In the following lines, each interaction is given in the form of two distinct bug numbers separated by a single space. Bugs are numbered consecutively starting from one.

## 输出格式

The output for every scenario is a line containing “Scenario #i:”, where i is the number of the scenario starting at 1, followed by one line saying either “No suspicious bugs found!” if the experiment is consistent with his assumption about the bugs’ sexual behavior, or “Suspicious bugs found!” if Professor Hopper’s assumption is definitely wrong.

## 样例 #1

### 输入

```
2

3 3

1 2

2 3

1 3

4 2

1 2

3 4
```

### 输出

```
Scenario #1:

Suspicious bugs found!

Scenario #2:

No suspicious bugs found!
```



---



---

# 题号列表

- SP3377 - BUGLIFE - A Bug&#8217;s Life


---

---
title: "SUMFOUR - 4 values whose sum is 0"
layout: "post"
diff: 普及+/提高
pid: SP1296
tag: ['搜索', '二分', '枚举']
---

# SUMFOUR - 4 values whose sum is 0

## 题目描述

The SUM problem can be formulated as follows: given four lists A, B, C, D of integer values, compute how many quadruplet (a, b, c, d ) belongs to A x B x C x D are such that a + b + c + d = 0 . In the following, we assume that all lists have the same size n

## 输入格式

 The first line of the input file contains the size of the lists n (this value can be as large as 4000). We then have n lines containing four integer values (with absolute value as large as 2 $ ^{28} $ ) that belong respectively to A, B, C and D .

(**Edited:** n <= 2500)

## 输出格式

Output should be printed on a single line.

## 样例 #1

### 输入

```
6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45
```

### 输出

```
5
```



---

---
title: "FREQUENT - Frequent values"
layout: "post"
diff: 普及+/提高
pid: SP1684
tag: ['搜索', '未知标签231']
---

# FREQUENT - Frequent values

## 题目描述

You are given a sequence of **n** integers **a $ _{1} $ , a $ _{2} $ , ... , a $ _{n} $**  in non-decreasing order. In addition to that, you are given several queries consisting of indices **i** and **j** (_1 ≤ i ≤ j ≤ n_). For each query, determine the most frequent value among the integers **a $ _{i} $ , ... , a $ _{j} $** .

   
#### Input Specification

 The input consists of several test cases. Each test case starts with a line containing two integers **n** and **q** (_1 ≤ n, q ≤ 100000_). The next line contains **n** integers **a $ _{1} $ , ... , a $ _{n} $**  (_-100000 ≤ a $ _{i} $ ≤ 100000_, for each _i ∈ {1, ..., n}_) separated by spaces. You can assume that for each _i ∈ {1, ..., n-1}: a $ _{i} $ ≤ a $ _{i+1} $_ . The following **q** lines contain one query each, consisting of two integers **i** and **j** (_1 ≤ i ≤ j ≤ n_), which indicate the boundary indices for the query.

 The last test case is followed by a line containing a single 0.

   
#### Output Specification

 For each query, print one line with one integer: The number of occurrences of the most frequent value within the given range.

   
#### Sample Input

 ```
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
0
```
   
#### Sample Output

 ```
1
4
3
```
- - - - - -

_A naive algorithm may not run in time!_



---

---
title: "KATHTHI - KATHTHI"
layout: "post"
diff: 普及+/提高
pid: SP22393
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# KATHTHI - KATHTHI

## 题目描述

```
         Kathiresan is initially locked at cell (0,0) in a highly guarded rectangular prison of order RxC. He must reach the gate at (R-1,C-1) in order to escape from the prison. Kathiresan can move from any cell, to any of it's 4 adjacent cells (North, East, West and South). If Kathiresan is currently at (x1,y1), then he can move to (x2,y2) if and only if abs(x2-x1)+abs(y2-y1) == 1 and 0<=x2<R and 0<=y2<CKathiresan somehow manages to get the map of the prison.
If map[x1][y1] == map[x2][y2] then Kathiresan can move from (x1,y1) to (x2,y2) without killing any guards.
If map[x1][y1] != map[x2][y2], then Kathiresan can move from (x1,y1) to (x2,y2) by killing a guard.

Given the map of the prison, find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input:
The first line consists of an integer t, the number of test cases. For each test case, the first line consists of two integers R and C representing the order of the rectangular prison followed by R strings representing the map of the rectangular prison.
 
Output:
For each test case find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input Constraints:
1 <= t <= 10
2 <= R <= 1000
2 <= C <= 1000
'a' <= map[i][j] <= 'z'
Sample Input:
4
2 2
aa
aa
2 3
abc
def6 6akacccaaacfcamdfccaokhddzyxwdpzyxwdd5 5abbbcabaccaaaccaefcicdgdd Sample Output:
0
322
```

## 样例 #1

### 输入

```
4
2 2
aa
aa
2 3
abc
def
6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd
5 5
abbbc
abacc
aaacc
aefci
cdgdd

```

### 输出

```
0
3
2
2
```



---

---
title: "YOKOF - Power Calculus"
layout: "post"
diff: 普及+/提高
pid: SP7579
tag: ['搜索']
---

# YOKOF - Power Calculus

## 题目描述

（略过没有营养的题干）

**题目大意**：
  给出正整数n,若只能使用乘法或除法，输出使x经过运算（自己乘或除自己，以及乘或除运算过程中产生的中间结果）变成x^n的最少步数

## 输入格式

若干行数据，每行一个正整数n，数据以单独成行的0结束

## 输出格式

若干行数据，对应每行输入的n所需的步数

## 样例 #1

### 输入

```
1
31
70
91
473
512
811
953
0
```

### 输出

```
0
6
8
9
11
9
13
12
```



---

---
title: "PUBLICAT - Publication"
layout: "post"
diff: 普及+/提高
pid: SP9255
tag: ['广度优先搜索 BFS']
---

# PUBLICAT - Publication

## 题目描述

Orizondo 数用于衡量某个科学家与 Rodrigo Orizondo 在学术论文合著中的“合作距离”。Rodrigo Orizondo 的 Orizondo 数是零。要获得有限的 Orizondo 数，科学家必须与至少一个已有有限 Orizondo 数的科学家共同发表论文。一个科学家的 Orizondo 数是他所有合作者中最低的 Orizondo 数加一。论文发表的顺序和编号分配顺序无关，因为每次发表后，系统会自动更新所有作者的 Orizondo 数。

你将得到一组 **论文** 数据，每篇论文包含一组作者，格式为 “AUTHOR\_1 AUTHOR\_2 ... AUTHOR\_N”（引号仅为明确表示）。其中，Rodrigo Orizondo 用 “ORIZONDO” 表示。

请输出所有作者的 Orizondo 数。输出格式为 “AUTHOR NUMBER”，若无法为某作者赋予有限的 Orizondo 数，仅输出 “AUTHOR”。作者的输出顺序应按字典序排列。

## 输入格式

第一行输入一个整数 \( C \)，表示测试用例的数量（\( 0 < C \)）。

每个测试用例首先包含一个整数 \( N \)，表示论文的数量，接着是 \( N \) 行，每行包含一组用空格分隔的作者姓名。

## 输出格式

对于每个测试用例，输出一行，包含每个作者及其 Orizondo 数，信息之间用空格分隔。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
1
ORIZONDO
2
KLEITMAN LANDER
ORIZONDO KLEITMAN
4
ORIZONDO B
A B C
B A E
D F
```

### 输出

```
ORIZONDO 0
KLEITMAN 1 LANDER 2 ORIZONDO 0
A 2 B 1 C 2 D E 2 F ORIZONDO 0
```



---



---

# 题号列表

- SP1296 - SUMFOUR - 4 values whose sum is 0
- SP1684 - FREQUENT - Frequent values
- SP22393 - KATHTHI - KATHTHI
- SP7579 - YOKOF - Power Calculus
- SP9255 - PUBLICAT - Publication


---

---
title: "KATHTHI - KATHTHI"
layout: "post"
diff: 普及+/提高
pid: SP22393
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# KATHTHI - KATHTHI

## 题目描述

```
         Kathiresan is initially locked at cell (0,0) in a highly guarded rectangular prison of order RxC. He must reach the gate at (R-1,C-1) in order to escape from the prison. Kathiresan can move from any cell, to any of it's 4 adjacent cells (North, East, West and South). If Kathiresan is currently at (x1,y1), then he can move to (x2,y2) if and only if abs(x2-x1)+abs(y2-y1) == 1 and 0<=x2<R and 0<=y2<CKathiresan somehow manages to get the map of the prison.
If map[x1][y1] == map[x2][y2] then Kathiresan can move from (x1,y1) to (x2,y2) without killing any guards.
If map[x1][y1] != map[x2][y2], then Kathiresan can move from (x1,y1) to (x2,y2) by killing a guard.

Given the map of the prison, find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input:
The first line consists of an integer t, the number of test cases. For each test case, the first line consists of two integers R and C representing the order of the rectangular prison followed by R strings representing the map of the rectangular prison.
 
Output:
For each test case find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input Constraints:
1 <= t <= 10
2 <= R <= 1000
2 <= C <= 1000
'a' <= map[i][j] <= 'z'
Sample Input:
4
2 2
aa
aa
2 3
abc
def6 6akacccaaacfcamdfccaokhddzyxwdpzyxwdd5 5abbbcabaccaaaccaefcicdgdd Sample Output:
0
322
```

## 样例 #1

### 输入

```
4
2 2
aa
aa
2 3
abc
def
6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd
5 5
abbbc
abacc
aaacc
aefci
cdgdd

```

### 输出

```
0
3
2
2
```



---



---

# 题号列表

- SP22393 - KATHTHI - KATHTHI


---

---
title: "SUMFOUR - 4 values whose sum is 0"
layout: "post"
diff: 普及+/提高
pid: SP1296
tag: ['搜索', '二分', '枚举']
---

# SUMFOUR - 4 values whose sum is 0

## 题目描述

The SUM problem can be formulated as follows: given four lists A, B, C, D of integer values, compute how many quadruplet (a, b, c, d ) belongs to A x B x C x D are such that a + b + c + d = 0 . In the following, we assume that all lists have the same size n

## 输入格式

 The first line of the input file contains the size of the lists n (this value can be as large as 4000). We then have n lines containing four integer values (with absolute value as large as 2 $ ^{28} $ ) that belong respectively to A, B, C and D .

(**Edited:** n <= 2500)

## 输出格式

Output should be printed on a single line.

## 样例 #1

### 输入

```
6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45
```

### 输出

```
5
```



---



---

# 题号列表

- SP1296 - SUMFOUR - 4 values whose sum is 0


---

---
title: "HISTOGRA - Largest Rectangle in a Histogram"
layout: "post"
diff: 普及+/提高
pid: SP1805
tag: ['栈']
---

# HISTOGRA - Largest Rectangle in a Histogram

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP1805/b9567e3483620f1fe679470ac44083eae9842e79.png)

如图所示，在一条水平线上有  $n$ 个宽为  $1$ 的矩形，求包含于这些矩形的最大子矩形面积（图中的阴影部分的面积即所求答案）。

## 输入格式

有多组测试数据，每组数据占一行。输入零时读入结束。

每行开头为一个数字  $n(1\le n\le 10^5)$，接下来在同一行给出  $n$ 个数字  $h_1,h_2,\cdots, h_n (0\le hi\le 10^9)$，表示每个矩形的高度。

## 输出格式

对于每组数据，输出最大子矩阵面积，一组数据输出一行。

## 样例 #1

### 输入

```
7 2 1 4 5 1 3 3
4 1000 1000 1000 1000
0
```

### 输出

```
8
4000
```



---



---

# 题号列表

- SP1805 - HISTOGRA - Largest Rectangle in a Histogram


---

---
title: "ADARAIN - Ada and Rain"
layout: "post"
diff: 普及+/提高
pid: SP28265
tag: ['线段树', '树状数组']
---

# ADARAIN - Ada and Rain

## 题目描述

瓢虫 Ada 正在种植植物。她有一条非常长的种植沟，这条沟长到雨水通常只能落在它的一部分区域。为了不让植物枯萎，Ada 详细记录了每场雨的降水区域，以了解每颗植物得到了多少雨水。然而，雨下得太多，她一个人忙不过来！

起初，你会得到 $N$ 个查询，每个查询是一个区间 $[L,R]$。第 $i$ 个区间表示第 $i$ 场雨覆盖的范围。随后有 $M$ 个查询，每个查询要求知道在第 $i$ 株植物上落了多少场雨。

## 输入格式

第一行包含三个整数 $N,M,W$，分别表示降雨次数、查询次数和种植沟的总长度；

接下来的 $N$ 行，每行包含两个整数 $L,R$，表示第 $i$ 场雨落在区间 $[L,R]$ 上；

接下来的 $M$ 行，每行包含一个整数 $a$，表示查询第 $a$ 株植物上落了多少场雨。

## 输出格式

输出 $M$ 行，每行一个整数，表示对应查询的植物接收到的降雨次数。

## 说明/提示

对于 $100\%$ 的数据，保证：

* $0 < N,M \le 10^5$

* $0 \le W \le 10^6$

* $0 \le L \le R < W$

* $0 \le a < W$

请注意序列起始位置。



---



---

# 题号列表

- SP28265 - ADARAIN - Ada and Rain


---

---
title: "DISQUERY - Distance Query"
layout: "post"
diff: 普及+/提高
pid: SP3978
tag: ['最近公共祖先 LCA', '树链剖分', '概率论']
---

# DISQUERY - Distance Query

## 题目描述

 [English](/problems/DISQUERY/en/) [Vietnamese](/problems/DISQUERY/vn/)The traffic network in a country consists of N cities (labeled with integers from 1 to N) and N-1 roads connecting the cities. There is a unique path between each pair of different cities, and we know the exact length of each road.

Write a program that will, for each of the K given pairs of cities, find the length of the shortest and the length of the longest road on the path between the two cities.

### Input

The first line of input contains an integer N, 2

The length of each road will be a positive integer less than or equal to 1 000 000.   
 The next line contains an integer K, 1

### Output

Each of the K lines of output should contain two integers – the lengths from the task description for the corresponding pair of the cities.


## 样例 #1

### 输入

```
5
2 3 100
4 3 200
1 5 150
1 3 50
3
2 4
3 5
1 2

```

### 输出

```
100 200
50 150
50 100

```

## 样例 #2

### 输入

```
7
3 6 4
1 7 1
1 3 2
1 2 6
2 5 4
2 4 4
5
6 4
7 6
1 2
1 3
3 5

```

### 输出

```
2 6
1 4
6 6
2 2
2 6

```



---



---

# 题号列表

- SP3978 - DISQUERY - Distance Query


---

---
title: "NAJPF - Pattern Find"
layout: "post"
diff: 普及+/提高
pid: SP21524
tag: ['模拟', '字符串', 'KMP 算法']
---

# NAJPF - Pattern Find

## 题目描述

### 题意：

给出两个字符串 $A,B$ ，求 $B$ 在 $A$ 中所有出现的次数和每一次出现的位置。假如没有出现输出`Not Found`。

## 输入格式

本题有多组数据。

第一行一个整数 $T（ 1≤T≤50）$，表示数据组数。

对于每组数据：

每行两个字符串 $A,B$。所有字符均为小写英文字符， $1≤| A |,| B |≤{10^6}$
 。

## 输出格式

对于每次询问，第一行一个整数 $n$，表示 $B$ 在 $A$ 中出现的次数。

第二行 $n$ 个整数,表示每一次出现的位置。

如果没有出现，输出`Not Found`。

每次询问之间有一个空行。

### 输入输出样例
#### 输入 #1
```
3
ababab ab
aaaaa bbb
aafafaasf aaf
```

#### 输出 #1
```
3
1 3 5

Not Found

1
1
```



---

---
title: "CIJEVI - Cijevi"
layout: "post"
diff: 普及+/提高
pid: SP3882
tag: ['模拟']
---

# CIJEVI - Cijevi

## 题目描述

为了设计从俄罗斯向克罗地亚输送天然气的新管道，萨格勒布和莫斯科正在使用一款名为《管道狂人》的电脑游戏。在该游戏中，欧洲被划分为 $R$ 行 $C$ 列的网格。每个小格子可能是空的，或者包含下图中的7种基本管道构建块之一：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3882/678f6ebd902db14c54549869b81af41b0e76e108.png)

天然气从莫斯科流向萨格勒布，可以双向通过这些构建块流动。特别地，构建块 '+' 必须在垂直和水平方向上都能导通，如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3882/ed558c8ede3b8c091a8e0b6d010d1a23c7e411a2.png)

在新的管道实施计划中，有人恶意删除了一个构建块，将其变成了一个空单元格。

请编写一个程序，找出被删除的构建块位置及其类型。

## 输入格式

第一行包含两个整数 $R$ 和 $C$，表示欧洲地图的行数和列数（$1 \le R, C \le 100$）。

接下来的 $R$ 行表示管道布局，每行包含恰好 $C$ 个字符，表示不同的内容：

- '.'（句点），表示空单元格；
- '|' （竖线）、'-'、'+'、'1'、'2'、'3'、'4'，表示构建块类型；
- 'M' 和 'Z'，分别代表莫斯科和萨格勒布。每个字母在布局中仅出现一次。

管道的天然气流向在输入数据中是唯一确定的；每个构建块的一端仅连接到莫斯科或萨格勒布之一。此外，所有构建块在填补缺失块之后必须全部被使用。

输入保证有且仅有一个解决方案。

## 输出格式

输出需被恢复的构建块的行和列位置，以及其类型（7种构建块中的一种）。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 7

.......

.M-.-Z.

.......
```

### 输出

```
2 4 -





Input

3 5

..1-M

1-+..

Z.23.



Output

2 4 4





Input

6 10

Z.1----4..

|.|....|..

|..14..M..

2-+++4....

..2323....

..........



Output

3 3 |
```



---



---

# 题号列表

- SP21524 - NAJPF - Pattern Find
- SP3882 - CIJEVI - Cijevi


---

---
title: "ALICESIE - Alice Sieve"
layout: "post"
diff: 普及+/提高
pid: SP10565
tag: ['素数判断,质数,筛法', '期望']
---

# ALICESIE - Alice Sieve

## 题目描述

Alice 最近学会了使用 Eratosthenes 筛法，这是一种古老的算法，用于找出小于某个上界的所有素数。正如预期的那样，她对这个算法的简洁和优雅感到非常印象深刻。

现在，她决定设计自己的筛法：Alice 筛法；在给定了某个上界 $N$ 的情况下的 Alice 筛法被形式化地定义为以下过程：

1. 创建一个从 $N$ 到 $2$ 的连续整数列表 $(N, N - 1, N - 2, \cdots, 3, 2)$。所有这 $N - 1$ 个数字最初都是未标记的。
2. 最初，让 $P$ 等于 $N$，并保持这个数字未标记。
3. 标记 $P$ 的所有正约数（即 $P$ 保持未标记）。
4. 从 $2$ 到 $P - 1$ 中找到最大的未标记数字，然后让 $P$ 等于这个数字。
5. 如果列表中不再有未标记的数字，则停止。否则，从第 $3$ 步开始重复。

不幸的是，Alice 还没有找到她的筛法的应用。但她仍然想知道，对于给定的上界 $N$，有多少整数会是未标记的。

## 输入格式

第一行包含一个整数 $T$，表示测试用例的数量（$1 \le T \le 10 ^ 4$）。接下来的 $T$ 行中的每一行都包含一个整数 $N$（$2 \le N \le 10 ^ 6$）。

## 输出格式

输出 $T$ 行，每个测试用例一行，包含所需的答案。

---

Translated by User 735713.

## 样例 #1

### 输入

```
3
2
3
5
```

### 输出

```
1
2
3
```



---

---
title: "CNTPRIME - Counting Primes"
layout: "post"
diff: 普及+/提高
pid: SP13015
tag: ['颜色段均摊（珂朵莉树 ODT）', '素数判断,质数,筛法']
---

# CNTPRIME - Counting Primes

## 题目描述

给你一个 $n$ 个数的数组和 $m$ 个操作：

- $0\ x\ y\ v$ 将 $x$ 到 $y$ 之间的所有数改成 $v$。

- $1\ x\ y$ 求 $x$ 到 $y$ 之间的质数个数。

数组下标为 $1$ 到 $n$。

## 输入格式

第一行是一个整数 $T$，表示数据组数。

每组数据包含两个整数 $n$，$q$。

下一行是 $n$ 个整数表示数组 $a_i$。接下来的 $q$ 行，每行包含一个操作。形如：

- $0\ x\ y\ v$

- $1\ x\ y$

$1 \le n \le {10}^4$，$1 \le q \le 2 \times {10}^4$，$2 \le x,y,v,a_i \le 10^6$

## 输出格式

对于每组数据，先输出数据编号。然后对于每一个 $1\ x\ y$ 的询问，输出 $x$ 到 $y$ 之间的质数个数。

## 说明/提示

- 使用较快的输入输出方式，如 `scanf` 和 `printf`。

- 一个质数是一个除了 $1$ 和它本身意外没有其他正因数的大于 $1$ 的自然数。前几个质数是 $2,3,5,7,11...$

## 样例 #1

### 输入

```
1
5 3
78 2 13 12 3
1 1 2
0 4 4 5
1 1 5
```

### 输出

```
Case 1:
1
4
```



---



---

# 题号列表

- SP10565 - ALICESIE - Alice Sieve
- SP13015 - CNTPRIME - Counting Primes


---

---
title: "ALICESIE - Alice Sieve"
layout: "post"
diff: 普及+/提高
pid: SP10565
tag: ['素数判断,质数,筛法', '期望']
---

# ALICESIE - Alice Sieve

## 题目描述

Alice 最近学会了使用 Eratosthenes 筛法，这是一种古老的算法，用于找出小于某个上界的所有素数。正如预期的那样，她对这个算法的简洁和优雅感到非常印象深刻。

现在，她决定设计自己的筛法：Alice 筛法；在给定了某个上界 $N$ 的情况下的 Alice 筛法被形式化地定义为以下过程：

1. 创建一个从 $N$ 到 $2$ 的连续整数列表 $(N, N - 1, N - 2, \cdots, 3, 2)$。所有这 $N - 1$ 个数字最初都是未标记的。
2. 最初，让 $P$ 等于 $N$，并保持这个数字未标记。
3. 标记 $P$ 的所有正约数（即 $P$ 保持未标记）。
4. 从 $2$ 到 $P - 1$ 中找到最大的未标记数字，然后让 $P$ 等于这个数字。
5. 如果列表中不再有未标记的数字，则停止。否则，从第 $3$ 步开始重复。

不幸的是，Alice 还没有找到她的筛法的应用。但她仍然想知道，对于给定的上界 $N$，有多少整数会是未标记的。

## 输入格式

第一行包含一个整数 $T$，表示测试用例的数量（$1 \le T \le 10 ^ 4$）。接下来的 $T$ 行中的每一行都包含一个整数 $N$（$2 \le N \le 10 ^ 6$）。

## 输出格式

输出 $T$ 行，每个测试用例一行，包含所需的答案。

---

Translated by User 735713.

## 样例 #1

### 输入

```
3
2
3
5
```

### 输出

```
1
2
3
```



---

---
title: "CNTPRIME - Counting Primes"
layout: "post"
diff: 普及+/提高
pid: SP13015
tag: ['颜色段均摊（珂朵莉树 ODT）', '素数判断,质数,筛法']
---

# CNTPRIME - Counting Primes

## 题目描述

给你一个 $n$ 个数的数组和 $m$ 个操作：

- $0\ x\ y\ v$ 将 $x$ 到 $y$ 之间的所有数改成 $v$。

- $1\ x\ y$ 求 $x$ 到 $y$ 之间的质数个数。

数组下标为 $1$ 到 $n$。

## 输入格式

第一行是一个整数 $T$，表示数据组数。

每组数据包含两个整数 $n$，$q$。

下一行是 $n$ 个整数表示数组 $a_i$。接下来的 $q$ 行，每行包含一个操作。形如：

- $0\ x\ y\ v$

- $1\ x\ y$

$1 \le n \le {10}^4$，$1 \le q \le 2 \times {10}^4$，$2 \le x,y,v,a_i \le 10^6$

## 输出格式

对于每组数据，先输出数据编号。然后对于每一个 $1\ x\ y$ 的询问，输出 $x$ 到 $y$ 之间的质数个数。

## 说明/提示

- 使用较快的输入输出方式，如 `scanf` 和 `printf`。

- 一个质数是一个除了 $1$ 和它本身意外没有其他正因数的大于 $1$ 的自然数。前几个质数是 $2,3,5,7,11...$

## 样例 #1

### 输入

```
1
5 3
78 2 13 12 3
1 1 2
0 4 4 5
1 1 5
```

### 输出

```
Case 1:
1
4
```



---



---

# 题号列表

- SP10565 - ALICESIE - Alice Sieve
- SP13015 - CNTPRIME - Counting Primes


---

---
title: "PRMQUER - Prime queries"
layout: "post"
diff: 普及+/提高
pid: SP19568
tag: ['线段树']
---

# PRMQUER - Prime queries

## 题目描述

&#8195;这是一个简单的题目

&#8195;给定 $N$ 个数，你需要对它们依次进行 $Q$ 次操作。每次操作的格式如下。

 1. 三个整数 $A$ $V$ $l$ 表示给第 $l$ 个数加上 $V$ 。
 
 2. 四个整数 $R$ $a$ $l$ $r$ 表示把区间 $[l,r]$ 的数都变为 $a$ 。
 
 3. 三个整数 $Q$ $l$ $r$ 表示询问区间 $[l,r]$ 里，小于等于 $10^7$ 的素数有多少个。
 
 &#8195;数据保证任何时刻这 $N$ 个数都不会有一个数大于 $10^9$ 。

## 输出格式

&#8195;对于每个操作 $3$ 输出一行整数表示这个操作的答案。

## 说明/提示

- $1\leq N\leq10^5$

- $1\leq Q\leq10^5$
 
- $V\leq10^3$

- $A[i] \leq10^8$

- $a \leq10^7$

- $1\leq l\leq r \leq N$

## 样例 #1

### 输入

```
5 10

1 2 3 4 5

A 3 1

Q 1 3

R 5 2 4

A 1 1

Q 1 1

Q 1 2

Q 1 4

A 3 5

Q 5 5

Q 1 5
```

### 输出

```
2

1

2

4

0

4
```



---

---
title: "ADARAIN - Ada and Rain"
layout: "post"
diff: 普及+/提高
pid: SP28265
tag: ['线段树', '树状数组']
---

# ADARAIN - Ada and Rain

## 题目描述

瓢虫 Ada 正在种植植物。她有一条非常长的种植沟，这条沟长到雨水通常只能落在它的一部分区域。为了不让植物枯萎，Ada 详细记录了每场雨的降水区域，以了解每颗植物得到了多少雨水。然而，雨下得太多，她一个人忙不过来！

起初，你会得到 $N$ 个查询，每个查询是一个区间 $[L,R]$。第 $i$ 个区间表示第 $i$ 场雨覆盖的范围。随后有 $M$ 个查询，每个查询要求知道在第 $i$ 株植物上落了多少场雨。

## 输入格式

第一行包含三个整数 $N,M,W$，分别表示降雨次数、查询次数和种植沟的总长度；

接下来的 $N$ 行，每行包含两个整数 $L,R$，表示第 $i$ 场雨落在区间 $[L,R]$ 上；

接下来的 $M$ 行，每行包含一个整数 $a$，表示查询第 $a$ 株植物上落了多少场雨。

## 输出格式

输出 $M$ 行，每行一个整数，表示对应查询的植物接收到的降雨次数。

## 说明/提示

对于 $100\%$ 的数据，保证：

* $0 < N,M \le 10^5$

* $0 \le W \le 10^6$

* $0 \le L \le R < W$

* $0 \le a < W$

请注意序列起始位置。



---

---
title: "LITE - Light Switching"
layout: "post"
diff: 普及+/提高
pid: SP7259
tag: ['线段树', '递归', '分块']
---

# LITE - Light Switching

## 题目描述

  
Farmer John tries to keep the cows sharp by letting them play with intellectual toys. One of the larger toys is the lights in the barn. Each of the N (2 <= N <= 100,000) cow stalls conveniently numbered 1..N has a colorful light above it.  
  
At the beginning of the evening, all the lights are off. The cows control the lights with a set of N pushbutton switches that toggle the lights; pushing switch i changes the state of light i from off to on or from on to off.  
  
The cows read and execute a list of M (1 <= M <= 100,000) operations expressed as one of two integers (0 <= operation <= 1).  
  
The first kind of operation (denoted by a 0 command) includes two subsequent integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) that indicate a starting switch and ending switch. They execute the operation by pushing each pushbutton from S\_i through E\_i inclusive exactly once.  
  
The second kind of operation (denoted by a 1 command) asks the cows to count how many lights are on in the range given by two integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) which specify the inclusive range in which the cows should count the number of lights that are on.  
  
Help FJ ensure the cows are getting the correct answer by processing the list and producing the proper counts.

## 输入格式

  
Line 1: Two space-separated integers: N and M  
Lines 2..M+1: Each line represents an operation with three space-separated integers: operation, S\_i, and E\_i

## 输出格式

Lines 1..number of queries: For each output query, print the count as an integer by itself on a single line.

## 样例 #1

### 输入

```
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4

```

### 输出

```
1
2
```



---



---

# 题号列表

- SP19568 - PRMQUER - Prime queries
- SP28265 - ADARAIN - Ada and Rain
- SP7259 - LITE - Light Switching


---

---
title: "ALICESIE - Alice Sieve"
layout: "post"
diff: 普及+/提高
pid: SP10565
tag: ['素数判断,质数,筛法', '期望']
---

# ALICESIE - Alice Sieve

## 题目描述

Alice 最近学会了使用 Eratosthenes 筛法，这是一种古老的算法，用于找出小于某个上界的所有素数。正如预期的那样，她对这个算法的简洁和优雅感到非常印象深刻。

现在，她决定设计自己的筛法：Alice 筛法；在给定了某个上界 $N$ 的情况下的 Alice 筛法被形式化地定义为以下过程：

1. 创建一个从 $N$ 到 $2$ 的连续整数列表 $(N, N - 1, N - 2, \cdots, 3, 2)$。所有这 $N - 1$ 个数字最初都是未标记的。
2. 最初，让 $P$ 等于 $N$，并保持这个数字未标记。
3. 标记 $P$ 的所有正约数（即 $P$ 保持未标记）。
4. 从 $2$ 到 $P - 1$ 中找到最大的未标记数字，然后让 $P$ 等于这个数字。
5. 如果列表中不再有未标记的数字，则停止。否则，从第 $3$ 步开始重复。

不幸的是，Alice 还没有找到她的筛法的应用。但她仍然想知道，对于给定的上界 $N$，有多少整数会是未标记的。

## 输入格式

第一行包含一个整数 $T$，表示测试用例的数量（$1 \le T \le 10 ^ 4$）。接下来的 $T$ 行中的每一行都包含一个整数 $N$（$2 \le N \le 10 ^ 6$）。

## 输出格式

输出 $T$ 行，每个测试用例一行，包含所需的答案。

---

Translated by User 735713.

## 样例 #1

### 输入

```
3
2
3
5
```

### 输出

```
1
2
3
```



---

---
title: "CNTPRIME - Counting Primes"
layout: "post"
diff: 普及+/提高
pid: SP13015
tag: ['颜色段均摊（珂朵莉树 ODT）', '素数判断,质数,筛法']
---

# CNTPRIME - Counting Primes

## 题目描述

给你一个 $n$ 个数的数组和 $m$ 个操作：

- $0\ x\ y\ v$ 将 $x$ 到 $y$ 之间的所有数改成 $v$。

- $1\ x\ y$ 求 $x$ 到 $y$ 之间的质数个数。

数组下标为 $1$ 到 $n$。

## 输入格式

第一行是一个整数 $T$，表示数据组数。

每组数据包含两个整数 $n$，$q$。

下一行是 $n$ 个整数表示数组 $a_i$。接下来的 $q$ 行，每行包含一个操作。形如：

- $0\ x\ y\ v$

- $1\ x\ y$

$1 \le n \le {10}^4$，$1 \le q \le 2 \times {10}^4$，$2 \le x,y,v,a_i \le 10^6$

## 输出格式

对于每组数据，先输出数据编号。然后对于每一个 $1\ x\ y$ 的询问，输出 $x$ 到 $y$ 之间的质数个数。

## 说明/提示

- 使用较快的输入输出方式，如 `scanf` 和 `printf`。

- 一个质数是一个除了 $1$ 和它本身意外没有其他正因数的大于 $1$ 的自然数。前几个质数是 $2,3,5,7,11...$

## 样例 #1

### 输入

```
1
5 3
78 2 13 12 3
1 1 2
0 4 4 5
1 1 5
```

### 输出

```
Case 1:
1
4
```



---



---

# 题号列表

- SP10565 - ALICESIE - Alice Sieve
- SP13015 - CNTPRIME - Counting Primes


---

---
title: "CORNET - Corporative Network"
layout: "post"
diff: 普及+/提高
pid: SP264
tag: ['并查集', '递归']
---

# CORNET - Corporative Network

## 题目描述

原本有 $n$ 个节点，最初每个节点的父亲都是自己。

现在给你若干操作，共分为两种，操作格式如下：

1. `I x y`（大写字母`I`）

将 $x$ 的父亲变为 $y$，而且令 $x$ 与 $y$ 之间的距离为 $\lvert x-y \rvert \bmod 1000$。

2. `E x` 询问x点到其根节点的距离

数据保证对于所有的 $1$ 操作合法，即保证之前 $y$ 不是 $x$ 的父亲、

## 输入格式

第一行输入一个整数 $T$，表示每个数据点的数据组数。


第一行包含一个正整数 $n$，表示原有的节点个数


`I x y` 或`E x` 分别代表以上的两种操作

对于这些操作，以输入一个`O`（大写字母`O`）为终止。

## 输出格式

一共若干行，表示对于每一组测试数据中的 `E` 操作输出答案。

## 样例 #1

### 输入

```
1
4
E 3
I 3 1
E 3
I 1 2
E 3
I 2 4
E 3
O
```

### 输出

```
0
2
3
5
```



---

---
title: "LITE - Light Switching"
layout: "post"
diff: 普及+/提高
pid: SP7259
tag: ['线段树', '递归', '分块']
---

# LITE - Light Switching

## 题目描述

  
Farmer John tries to keep the cows sharp by letting them play with intellectual toys. One of the larger toys is the lights in the barn. Each of the N (2 <= N <= 100,000) cow stalls conveniently numbered 1..N has a colorful light above it.  
  
At the beginning of the evening, all the lights are off. The cows control the lights with a set of N pushbutton switches that toggle the lights; pushing switch i changes the state of light i from off to on or from on to off.  
  
The cows read and execute a list of M (1 <= M <= 100,000) operations expressed as one of two integers (0 <= operation <= 1).  
  
The first kind of operation (denoted by a 0 command) includes two subsequent integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) that indicate a starting switch and ending switch. They execute the operation by pushing each pushbutton from S\_i through E\_i inclusive exactly once.  
  
The second kind of operation (denoted by a 1 command) asks the cows to count how many lights are on in the range given by two integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) which specify the inclusive range in which the cows should count the number of lights that are on.  
  
Help FJ ensure the cows are getting the correct answer by processing the list and producing the proper counts.

## 输入格式

  
Line 1: Two space-separated integers: N and M  
Lines 2..M+1: Each line represents an operation with three space-separated integers: operation, S\_i, and E\_i

## 输出格式

Lines 1..number of queries: For each output query, print the count as an integer by itself on a single line.

## 样例 #1

### 输入

```
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4

```

### 输出

```
1
2
```



---



---

# 题号列表

- SP264 - CORNET - Corporative Network
- SP7259 - LITE - Light Switching


---

---
title: "DIFERENC - DIFERENCIJA"
layout: "post"
diff: 普及+/提高
pid: SP10622
tag: ['单调队列']
---

# DIFERENC - DIFERENCIJA

## 题目描述

Mirko discovered what Slavko did in previous task, and decided to deal with something completely



---

---
title: "KATHTHI - KATHTHI"
layout: "post"
diff: 普及+/提高
pid: SP22393
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# KATHTHI - KATHTHI

## 题目描述

```
         Kathiresan is initially locked at cell (0,0) in a highly guarded rectangular prison of order RxC. He must reach the gate at (R-1,C-1) in order to escape from the prison. Kathiresan can move from any cell, to any of it's 4 adjacent cells (North, East, West and South). If Kathiresan is currently at (x1,y1), then he can move to (x2,y2) if and only if abs(x2-x1)+abs(y2-y1) == 1 and 0<=x2<R and 0<=y2<CKathiresan somehow manages to get the map of the prison.
If map[x1][y1] == map[x2][y2] then Kathiresan can move from (x1,y1) to (x2,y2) without killing any guards.
If map[x1][y1] != map[x2][y2], then Kathiresan can move from (x1,y1) to (x2,y2) by killing a guard.

Given the map of the prison, find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input:
The first line consists of an integer t, the number of test cases. For each test case, the first line consists of two integers R and C representing the order of the rectangular prison followed by R strings representing the map of the rectangular prison.
 
Output:
For each test case find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input Constraints:
1 <= t <= 10
2 <= R <= 1000
2 <= C <= 1000
'a' <= map[i][j] <= 'z'
Sample Input:
4
2 2
aa
aa
2 3
abc
def6 6akacccaaacfcamdfccaokhddzyxwdpzyxwdd5 5abbbcabaccaaaccaefcicdgdd Sample Output:
0
322
```

## 样例 #1

### 输入

```
4
2 2
aa
aa
2 3
abc
def
6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd
5 5
abbbc
abacc
aaacc
aefci
cdgdd

```

### 输出

```
0
3
2
2
```



---



---

# 题号列表

- SP10622 - DIFERENC - DIFERENCIJA
- SP22393 - KATHTHI - KATHTHI


---

---
title: "MDOLLS - Nested Dolls"
layout: "post"
diff: 普及-
pid: SP3943
tag: ['贪心', '二分', '排序']
---

# MDOLLS - Nested Dolls

## 题目描述

[English](/problems/MDOLLS/en/) [Vietnamese](/problems/MDOLLS/vn/) ```

Dilworth is the world's most prominent collector of Russian nested dolls:
he literally has thousands of them! You know, the wooden hollow dolls of 
different sizes of which the smallest doll is contained in the second smallest,
and this doll is in turn contained in the next one and so forth. One day he
wonders if there is another way of nesting them so he will end up with
fewer nested dolls? After all, that would make his collection even 
more magnificent! He unpacks each nested doll and measures the width 
and height of each contained doll. A doll with width w1 and height h1 will
fit in another doll of width w2 and height h= if and only if w1 < w2 and 
h1 < h2. Can you help him calculate the smallest number of nested dolls 
possible to assemble from his massive list of measurements? 
```

## 输入格式

```

On the first line of input is a single positive integer 1 ≤ t ≤ 20 specifying
the number of test cases to follow. Each test case begins with a positive 
integer 1 ≤ m ≤ 20000 on a line of itself telling the number of dolls 
in the test case. Next follow 2m positive integers w1, h1,w2, h2, ... ,wm, 
hm, where wi is the width and hi is the height of doll number i. 
1 ≤ wi, hi ≤ 10000 for all i.

SAMPLE INPUT
4
3
20 30 40 50 30 40
4
20 30 10 10 30 20 40 50
3
10 30 20 20 30 10
4
10 10 20 30 40 50 39 51
```

## 输出格式

```
 
For each test case there should be one line of output containing the minimum
number of nested dolls possible.

SAMPLE OUTPUT
1
2
3
2
```



---



---

# 题号列表

- SP3943 - MDOLLS - Nested Dolls


---

---
title: "GLJIVE - GLJIVE"
layout: "post"
diff: 普及-
pid: SP8319
tag: ['模拟', '前缀和']
---

# GLJIVE - GLJIVE

## 题目描述

 In front of Super Mario there are **10 mushrooms**, arranged in a row. A certain amount of points is awarded for picking each of the mushrooms. Super Mario must pick mushrooms **in order** they appear, but is not required to pick them all – his goal is to score a number of points **as close as possible to 100**.

In case there exist two such numbers which are equally close to 100 (e.g. 98 and 102), Mario will pick the **greater** one (in this case 102).

Help Super Mario and tell him how many points he will score.

## 输入格式

Input consists of 10 lines, each of which contains one positive integer less than or equal to 100, denoting the scores awarded for picking each mushroom, in the order that Mario can pick them in.

## 输出格式

The first and only line of output must contain the required number of points.

## 样例 #1

### 输入

```
10

20

30

40

50

60

70

80

90

100
```

### 输出

```
100
```



---



---

# 题号列表

- SP8319 - GLJIVE - GLJIVE


---

---
title: "TAKIN - Taskin and apple tree"
layout: "post"
diff: 普及-
pid: SP33795
tag: ['枚举', '剪枝', '背包 DP']
---

# TAKIN - Taskin and apple tree

## 题目描述

# TAKIN - Taskin和苹果树


Taskin有一个苹果园，每天早上他都会去果园采摘苹果。他有一个篮子，可以携带**不超过 M个**苹果。Taskin将所摘的苹果放入篮子里，对于每一棵树，他要么将这棵树上的所有苹果摘完，要么跳过这棵树不摘。现在让你制定一个方案，使Taskin所摘的苹果数量最多。

## 输入格式

在第一行输入一个整数T，表示有T个测试数据。

每组测试数据以两个整数 M 和 N 开始，分别表示果园中的苹果树的数量和篮子最多能装的苹果数。

接下来有N个整数：a[1],a[2],a[3],...,a[n],其中a[i]表示第i棵苹果树所结苹果的个数。

## 输出格式

输出一个整数，表示所能摘的最大的苹果数。

## 输入输出样例
### 输入样例＃1：

```cpp
2 
5 6 
2 1 2 7 8 
5 10 
1 2 4 4 6
```
### 输出样例＃1：

```cpp
5 
10
```

## 说明/提示

T<=10,N<=20,M<=2*10^10,a[i]<=10^9

翻译提供者：right_cat

## 样例 #1

### 输入

```
2
5 6
2 1 2 7 8
5 10
1 2 4 4 6
```

### 输出

```
5
10
```



---



---

# 题号列表

- SP33795 - TAKIN - Taskin and apple tree


---

---
title: "IITKWPCE - Let us play with strings"
layout: "post"
diff: 普及-
pid: SP15558
tag: ['动态规划 DP', '哈希 hashing']
---

# IITKWPCE - Let us play with strings

## 题目描述

 Feluda likes palindromes very much. He is so fond of palindromes that if you give him any string, he will try to break it into continous palindromes.  
 As Feluda is a smart boy, he will do try to break the string into minimum no of such continuous palindromes. You have to help Prabhu. Find out the answer for the problem if he is given a string s.

## 输入格式

T : number of test cases (T <= 100)  
next T lines contain a string s (length of s <= 2000)

## 输出格式

For every test case print one line having answer as given in the problem statement.

## 样例 #1

### 输入

```
4
abacdc
ababa
ababbacababbad
abcd

```

### 输出

```
2
1
5
4

```



---



---

# 题号列表

- SP15558 - IITKWPCE - Let us play with strings


---

---
title: "IITKWPCE - Let us play with strings"
layout: "post"
diff: 普及-
pid: SP15558
tag: ['动态规划 DP', '哈希 hashing']
---

# IITKWPCE - Let us play with strings

## 题目描述

 Feluda likes palindromes very much. He is so fond of palindromes that if you give him any string, he will try to break it into continous palindromes.  
 As Feluda is a smart boy, he will do try to break the string into minimum no of such continuous palindromes. You have to help Prabhu. Find out the answer for the problem if he is given a string s.

## 输入格式

T : number of test cases (T <= 100)  
next T lines contain a string s (length of s <= 2000)

## 输出格式

For every test case print one line having answer as given in the problem statement.

## 样例 #1

### 输入

```
4
abacdc
ababa
ababbacababbad
abcd

```

### 输出

```
2
1
5
4

```



---



---

# 题号列表

- SP15558 - IITKWPCE - Let us play with strings


---

---
title: "SBANK - Sorting Bank Accounts"
layout: "post"
diff: 普及-
pid: SP27
tag: ['模拟', '字符串', '排序']
---

# SBANK - Sorting Bank Accounts

## 题目描述

 In one of the internet banks thousands of operations are being performed every day. Since certain customers do business more actively than others, some of the bank accounts occur many times in the list of operations. Your task is to sort the bank account numbers in ascending order. If an account appears twice or more in the list, write the number of repetitions just after the account number. The format of accounts is as follows: **2** control digits, an **8**-digit code of the bank, **16** digits identifying the owner (written in groups of four digits), for example (at the end of each line there is exactly one space):

**30 10103538 2222 1233 6160 0142**  **Banks are real-time institutions and they need FAST solutions. If you feel you can meet the challenge within a very stringent time limit, go ahead!** A well designed sorting algorithm in a fast language is likely to succeed.

## 输入格式

   
_t_ \[the number of tests <= **5**\]   
_n_ \[the number of accounts<= **100 000**\]   
\[list of accounts\]   
\[empty line\]   
\[next test cases\]

## 输出格式

   
\[sorted list of accounts with the number of repeated accounts\]   
\[empty line\]   
\[other results\]

## 样例 #1

### 输入

```
2
6
03 10103538 2222 1233 6160 0142 
03 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 

5
30 10103538 2222 1233 6160 0144 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0145 
30 10103538 2222 1233 6160 0146 
30 10103538 2222 1233 6160 0143
```

### 输出

```
03 10103538 2222 1233 6160 0141 1
03 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0141 2
30 10103538 2222 1233 6160 0142 2

30 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0143 1
30 10103538 2222 1233 6160 0144 1
30 10103538 2222 1233 6160 0145 1
30 10103538 2222 1233 6160 0146 1
```



---

---
title: "NUMOFPAL - Number of Palindromes"
layout: "post"
diff: 普及-
pid: SP7586
tag: ['字符串', '概率论']
---

# NUMOFPAL - Number of Palindromes

## 题目描述

Each palindrome can be always created from the other palindromes, if a single character is also a palindrome. For example, the string "malayalam" can be created by some ways:

  
\* malayalam = m + ala + y + ala + m  
\* malayalam = m + a + l + aya + l + a + m  
  
We want to take the value of function NumPal(s) which is the number of different palindromes that can be created using the string S by the above method. If the same palindrome occurs more than once then all of them should be counted separately.

## 输入格式

The string S.

## 输出格式

The value of function NumPal(s).

## 说明/提示

**Limitations**

0 < |s| <= 1000

## 样例 #1

### 输入

```
malayalam
```

### 输出

```
15
```



---

---
title: "NY10A - Penney Game"
layout: "post"
diff: 普及-
pid: SP8612
tag: ['模拟', '字符串']
---

# NY10A - Penney Game

## 题目描述

Penney’s game is a simple game typically played by two players. One version of the game calls for each player to choose a unique three-coin sequence such as **HEADS TAILS HEADS (HTH)**. A fair coin is tossed sequentially some number of times until one of the two sequences appears. The player who chose the first sequence to appear wins the game.

For this problem, you will write a program that implements a variation on the Penney Game. You willread a sequence of 40 coin tosses and determine how many times each three-coin sequence appears. Obviously there are eight such three-coin sequences: **TTT**, **TTH**, **THT**, **THH**, **HTT**, **HTH**, **HHT** and **HHH**. Sequences may overlap. For example, if all 40 coin tosses are heads, then the sequence HHH appears 38 times.

## 输入格式

The first line of input contains a single integer P, (1

## 输出格式

For each data set there is one line of output. It contains the data set number followed by a single space, followed by the number of occurrences of each three-coin sequence, in the order shown above, with a space between each one. There should be a total of 9 space separated decimal integers on each output line.

## 样例 #1

### 输入

```
\n4\n1\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n2\nTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n3\nHHTTTHHTTTHTHHTHHTTHTTTHHHTHTTHTTHTTTHTH\n4\nHTHTHHHTHHHTHTHHHHTTTHTTTTTHHTTTTHTHHHHT\n\n
```

### 输出

```
\n1 0 0 0 0 0 0 0 38\n2 38 0 0 0 0 0 0 0\n3 4 7 6 4 7 4 5 1\n4 6 3 4 5 3 6 5 6
```



---



---

# 题号列表

- SP27 - SBANK - Sorting Bank Accounts
- SP7586 - NUMOFPAL - Number of Palindromes
- SP8612 - NY10A - Penney Game


---

---
title: "UPDATEIT - Update the array !"
layout: "post"
diff: 普及-
pid: SP16487
tag: ['差分']
---

# UPDATEIT - Update the array !

## 题目描述

你有一个 $n$ 个元素的数组，初始全为 $0$，编号为 $0,\dots,n-1$。  
你需要对其做 $u$ 次修改操作。每个修改操作你需要把区间 $[l,r]$ 内的元素加上一个值 $val$。  
之后，会有 $q$ 次查询，每次查询下标为 $i$ 的数。

## 输入格式

第一行，一个整数 $t(1 \le t \le 10)$，表示测试数据的组数。

每组测试数据的第一行，两个整数 $n,u(1 \le n \le 10^4,1 \le u \le 10^5)$，分别表示数组中元素的个数及修改操作的次数。  
以下 $u$ 行，三个整数 $l,r,val(0 \le l,r < n,0 \le val \le 10^4)$，代表一次修改操作。  
下一行，一个整数 $q(1 \le q \le 10^4)$，代表查询的次数。  
以下 $q$ 行，每行一个整数 $i(0 \le i < n)$，表示一次查询。

## 输出格式

对于每组数据，每行输出一次查询的结果。

## 样例 #1

### 输入

```
1
5 3
0 1 7
2 4 6
1 3 2
3
0
3
4
```

### 输出

```
7
8
6
```



---



---

# 题号列表

- SP16487 - UPDATEIT - Update the array !


---

---
title: "UCV2013H - Slick"
layout: "post"
diff: 普及-
pid: SP15436
tag: ['广度优先搜索 BFS']
---

# UCV2013H - Slick

## 题目描述

一片大小为 $n\times m$ 的海面发生了石油泄漏，石油表示为 $1$，海水表示为 $0$。

求石油组成的连通块总数，以及每种面积连通块的个数。

**本题多测**

## 输入格式

对于每组测试数据，第一行两个整数 $n$ 和 $m$，表示海面的大小。

后跟一个 $n\times m$ 大小的字符矩阵，表示海面的石油泄漏情况。

当 $n = m = 0$ 时，终止程序。

## 输出格式

对于每组测试数据，第 $1$ 行输出一个整数 $k$，表示石油组成的连通块总数。

第 $2$ 至 $k$ 行每行两个整数 $i, j$，表示面积为 $i$ 的连通块有 $j$ 个。

**【数据范围及约定】**

对于 $100\%$ 的数据，$1 \le n, m\le250$。

Translated by @[159号程序员](https://www.luogu.com.cn/user/334586)。

## 样例 #1

### 输入

```
10 10
1 1 1 1 1 1 1 1 1 1
1 1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 1 1 1
1 1 0 0 1 0 0 1 1 1
1 0 1 0 0 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0
```

### 输出

```
7
1 2
2 1
6 1
10 2
20 1
```



---



---

# 题号列表

- SP15436 - UCV2013H - Slick


---

---
title: "FASHION - Fashion Shows"
layout: "post"
diff: 普及-
pid: SP1025
tag: ['数学', '排序']
---

# FASHION - Fashion Shows

## 题目描述

A fashion show rates participants according to their level of hotness. Two different fashion shows were organized, one for men and the other for women. A date for the third is yet to be decided ;) .

Now the results of both fashion shows are out. The participants of both the fashion shows have decided to date each other, but as usual they have difficuly in choosing their partners. The Maximum Match dating serive (MMDS) comes to their rescue and matches them in such a way that that maximizes the hotness bonds for all couples.

If a man has been rated at hotness level x and a women at hotness level y, the value of their hotness bond is x\*y.

Both fashion shows contain **N** participants each. MMDS has done its job and your job is to find the sum of hotness bonds for all the couples that MMDS has proposed.

## 输入格式

The first line of the input contains an integer **t**, the number of test cases. **t** test cases follow.

Each test case consists of 3 lines:

- The first line contains a single integer **N** (1 <= **N** <= 1000).
- The second line contains **N** integers separated by single spaces denoting the hotness levels of the men.
- The third line contains **N** integers separated by single spaces denoting the hotness levels of the women.

All hotness ratings are on a scale of 0 to 10.

## 输出格式

For each test case output a single line containing a single integer denoting the sum of the hotness bonds for all pairs that MMDS has proposed.

## 样例 #1

### 输入

```
2

2

1 1

3 2

3

2 3 2

1 3 2
```

### 输出

```
5

15
```



---

---
title: "SBANK - Sorting Bank Accounts"
layout: "post"
diff: 普及-
pid: SP27
tag: ['模拟', '字符串', '排序']
---

# SBANK - Sorting Bank Accounts

## 题目描述

 In one of the internet banks thousands of operations are being performed every day. Since certain customers do business more actively than others, some of the bank accounts occur many times in the list of operations. Your task is to sort the bank account numbers in ascending order. If an account appears twice or more in the list, write the number of repetitions just after the account number. The format of accounts is as follows: **2** control digits, an **8**-digit code of the bank, **16** digits identifying the owner (written in groups of four digits), for example (at the end of each line there is exactly one space):

**30 10103538 2222 1233 6160 0142**  **Banks are real-time institutions and they need FAST solutions. If you feel you can meet the challenge within a very stringent time limit, go ahead!** A well designed sorting algorithm in a fast language is likely to succeed.

## 输入格式

   
_t_ \[the number of tests <= **5**\]   
_n_ \[the number of accounts<= **100 000**\]   
\[list of accounts\]   
\[empty line\]   
\[next test cases\]

## 输出格式

   
\[sorted list of accounts with the number of repeated accounts\]   
\[empty line\]   
\[other results\]

## 样例 #1

### 输入

```
2
6
03 10103538 2222 1233 6160 0142 
03 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 

5
30 10103538 2222 1233 6160 0144 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0145 
30 10103538 2222 1233 6160 0146 
30 10103538 2222 1233 6160 0143
```

### 输出

```
03 10103538 2222 1233 6160 0141 1
03 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0141 2
30 10103538 2222 1233 6160 0142 2

30 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0143 1
30 10103538 2222 1233 6160 0144 1
30 10103538 2222 1233 6160 0145 1
30 10103538 2222 1233 6160 0146 1
```



---

---
title: "MDOLLS - Nested Dolls"
layout: "post"
diff: 普及-
pid: SP3943
tag: ['贪心', '二分', '排序']
---

# MDOLLS - Nested Dolls

## 题目描述

[English](/problems/MDOLLS/en/) [Vietnamese](/problems/MDOLLS/vn/) ```

Dilworth is the world's most prominent collector of Russian nested dolls:
he literally has thousands of them! You know, the wooden hollow dolls of 
different sizes of which the smallest doll is contained in the second smallest,
and this doll is in turn contained in the next one and so forth. One day he
wonders if there is another way of nesting them so he will end up with
fewer nested dolls? After all, that would make his collection even 
more magnificent! He unpacks each nested doll and measures the width 
and height of each contained doll. A doll with width w1 and height h1 will
fit in another doll of width w2 and height h= if and only if w1 < w2 and 
h1 < h2. Can you help him calculate the smallest number of nested dolls 
possible to assemble from his massive list of measurements? 
```

## 输入格式

```

On the first line of input is a single positive integer 1 ≤ t ≤ 20 specifying
the number of test cases to follow. Each test case begins with a positive 
integer 1 ≤ m ≤ 20000 on a line of itself telling the number of dolls 
in the test case. Next follow 2m positive integers w1, h1,w2, h2, ... ,wm, 
hm, where wi is the width and hi is the height of doll number i. 
1 ≤ wi, hi ≤ 10000 for all i.

SAMPLE INPUT
4
3
20 30 40 50 30 40
4
20 30 10 10 30 20 40 50
3
10 30 20 20 30 10
4
10 10 20 30 40 50 39 51
```

## 输出格式

```
 
For each test case there should be one line of output containing the minimum
number of nested dolls possible.

SAMPLE OUTPUT
1
2
3
2
```



---



---

# 题号列表

- SP1025 - FASHION - Fashion Shows
- SP27 - SBANK - Sorting Bank Accounts
- SP3943 - MDOLLS - Nested Dolls


---

---
title: "UCV2013H - Slick"
layout: "post"
diff: 普及-
pid: SP15436
tag: ['广度优先搜索 BFS']
---

# UCV2013H - Slick

## 题目描述

一片大小为 $n\times m$ 的海面发生了石油泄漏，石油表示为 $1$，海水表示为 $0$。

求石油组成的连通块总数，以及每种面积连通块的个数。

**本题多测**

## 输入格式

对于每组测试数据，第一行两个整数 $n$ 和 $m$，表示海面的大小。

后跟一个 $n\times m$ 大小的字符矩阵，表示海面的石油泄漏情况。

当 $n = m = 0$ 时，终止程序。

## 输出格式

对于每组测试数据，第 $1$ 行输出一个整数 $k$，表示石油组成的连通块总数。

第 $2$ 至 $k$ 行每行两个整数 $i, j$，表示面积为 $i$ 的连通块有 $j$ 个。

**【数据范围及约定】**

对于 $100\%$ 的数据，$1 \le n, m\le250$。

Translated by @[159号程序员](https://www.luogu.com.cn/user/334586)。

## 样例 #1

### 输入

```
10 10
1 1 1 1 1 1 1 1 1 1
1 1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 1 1 1
1 1 0 0 1 0 0 1 1 1
1 0 1 0 0 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0
```

### 输出

```
7
1 2
2 1
6 1
10 2
20 1
```



---

---
title: "PRIMPERM - Prime Permutations"
layout: "post"
diff: 普及-
pid: SP8591
tag: ['深度优先搜索 DFS', '素数判断,质数,筛法']
---

# PRIMPERM - Prime Permutations

## 题目描述

$t$ 组数据，每组数据给定一个整数 $n$，求 $n$ 的排列中有多少个排列是质数。

## 输入格式

共 $t+1$ 行：

第一行为一个整数 $t$。

第 $2\sim t+1$ 行每行一个整数 $n$。

## 输出格式

共 $t$ 行，每行一个整数表示 $n$ 的排列中有多少个排列是质数。

## 说明/提示

$t<10^4$，$n<10^7$

## 样例 #1

### 输入

```
2

13

110
```

### 输出

```
2

1
```



---



---

# 题号列表

- SP15436 - UCV2013H - Slick
- SP8591 - PRIMPERM - Prime Permutations


---

---
title: "FASHION - Fashion Shows"
layout: "post"
diff: 普及-
pid: SP1025
tag: ['数学', '排序']
---

# FASHION - Fashion Shows

## 题目描述

A fashion show rates participants according to their level of hotness. Two different fashion shows were organized, one for men and the other for women. A date for the third is yet to be decided ;) .

Now the results of both fashion shows are out. The participants of both the fashion shows have decided to date each other, but as usual they have difficuly in choosing their partners. The Maximum Match dating serive (MMDS) comes to their rescue and matches them in such a way that that maximizes the hotness bonds for all couples.

If a man has been rated at hotness level x and a women at hotness level y, the value of their hotness bond is x\*y.

Both fashion shows contain **N** participants each. MMDS has done its job and your job is to find the sum of hotness bonds for all the couples that MMDS has proposed.

## 输入格式

The first line of the input contains an integer **t**, the number of test cases. **t** test cases follow.

Each test case consists of 3 lines:

- The first line contains a single integer **N** (1 <= **N** <= 1000).
- The second line contains **N** integers separated by single spaces denoting the hotness levels of the men.
- The third line contains **N** integers separated by single spaces denoting the hotness levels of the women.

All hotness ratings are on a scale of 0 to 10.

## 输出格式

For each test case output a single line containing a single integer denoting the sum of the hotness bonds for all pairs that MMDS has proposed.

## 样例 #1

### 输入

```
2

2

1 1

3 2

3

2 3 2

1 3 2
```

### 输出

```
5

15
```



---

---
title: "MATHLOVE - Math is Love"
layout: "post"
diff: 普及-
pid: SP31290
tag: ['数学']
---

# MATHLOVE - Math is Love

## 输入格式

第一行 一个正整数T(1<=T<=100000)，表示有T组数据

第2-T+1行 每行一个正整数Y(1<=Y<=$3*10^9$)

## 输出格式

对于每个Y，如果有正整数k满足$\sum_{i=1}^ki$ =y，则输出k的值，否则输出NAI（换行）



---



---

# 题号列表

- SP1025 - FASHION - Fashion Shows
- SP31290 - MATHLOVE - Math is Love


---

---
title: "GGD - Mr Toothless and His GCD Operation"
layout: "post"
diff: 普及-
pid: SP19786
tag: ['最大公约数 gcd', '构造']
---

# GGD - Mr Toothless and His GCD Operation

## 题目描述

You are given **N**. You have to find two numbers **a** and **b** such that **GCD (a, b)** is as maximum as possible where **1<=a<b<=N**.

**Input**

Input starts with an integer **T (, denoting the number of test cases.**

Each case contains an integer **N (2 .**

**Output**

For each case, print the case number and then print **a** and **b**. If there exists multiple solutions print the one where **a+b** is maximum.

**Sample Input/Output**

 **Sample Input**

  **Sample Output**

  1

2

  Case 1: 1 2

 **_Problem Setter: Md Abdul Alim, Department of CSE, Bangladesh University of Business & Technology_**



---



---

# 题号列表

- SP19786 - GGD - Mr Toothless and His GCD Operation


---

---
title: "PRIME1 - Prime Generator"
layout: "post"
diff: 普及-
pid: SP2
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# PRIME1 - Prime Generator

## 题目描述

 Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

## 输入格式

 The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

## 输出格式

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)**   
Information
-----------

 After cluster change, please consider [PRINT](http://www.spoj.com/problems/PRINT/) as a more challenging problem.

## 样例 #1

### 输入

```
2
1 10
3 5
```

### 输出

```
2
3
5
7

3
5
```



---

---
title: "TAKIN - Taskin and apple tree"
layout: "post"
diff: 普及-
pid: SP33795
tag: ['枚举', '剪枝', '背包 DP']
---

# TAKIN - Taskin and apple tree

## 题目描述

# TAKIN - Taskin和苹果树


Taskin有一个苹果园，每天早上他都会去果园采摘苹果。他有一个篮子，可以携带**不超过 M个**苹果。Taskin将所摘的苹果放入篮子里，对于每一棵树，他要么将这棵树上的所有苹果摘完，要么跳过这棵树不摘。现在让你制定一个方案，使Taskin所摘的苹果数量最多。

## 输入格式

在第一行输入一个整数T，表示有T个测试数据。

每组测试数据以两个整数 M 和 N 开始，分别表示果园中的苹果树的数量和篮子最多能装的苹果数。

接下来有N个整数：a[1],a[2],a[3],...,a[n],其中a[i]表示第i棵苹果树所结苹果的个数。

## 输出格式

输出一个整数，表示所能摘的最大的苹果数。

## 输入输出样例
### 输入样例＃1：

```cpp
2 
5 6 
2 1 2 7 8 
5 10 
1 2 4 4 6
```
### 输出样例＃1：

```cpp
5 
10
```

## 说明/提示

T<=10,N<=20,M<=2*10^10,a[i]<=10^9

翻译提供者：right_cat

## 样例 #1

### 输入

```
2
5 6
2 1 2 7 8
5 10
1 2 4 4 6
```

### 输出

```
5
10
```



---



---

# 题号列表

- SP2 - PRIME1 - Prime Generator
- SP33795 - TAKIN - Taskin and apple tree


---

---
title: "ONP - Transform the Expression"
layout: "post"
diff: 普及-
pid: SP4
tag: ['模拟', '递归', '栈']
---

# ONP - Transform the Expression

## 题目描述

请你将 $n$ 个中缀表达式转换为后缀表达式。

## 输入格式

第一行一个整数 $n$ 代表中缀表达式个数。

接下来 $n$ 行代表 $n$ 个中缀表达式。

## 输出格式

$n$ 行代表每个中缀表达式转换过来的后缀表达式。

## 说明/提示

对于 $100\%$ 的数据，$n \le 100$ , 表达式长度 $\le 400$ 。

Translated by @[稀神探女](/user/85216)

## 样例 #1

### 输入

```
3

(a+(b*c))

((a+b)*(z+x))

((a+t)*((b+(a+c))^(c+d)))
```

### 输出

```
abc*+

ab+zx+*

at+bac++cd+^*
```



---



---

# 题号列表

- SP4 - ONP - Transform the Expression


---

---
title: "NUMOFPAL - Number of Palindromes"
layout: "post"
diff: 普及-
pid: SP7586
tag: ['字符串', '概率论']
---

# NUMOFPAL - Number of Palindromes

## 题目描述

Each palindrome can be always created from the other palindromes, if a single character is also a palindrome. For example, the string "malayalam" can be created by some ways:

  
\* malayalam = m + ala + y + ala + m  
\* malayalam = m + a + l + aya + l + a + m  
  
We want to take the value of function NumPal(s) which is the number of different palindromes that can be created using the string S by the above method. If the same palindrome occurs more than once then all of them should be counted separately.

## 输入格式

The string S.

## 输出格式

The value of function NumPal(s).

## 说明/提示

**Limitations**

0 < |s| <= 1000

## 样例 #1

### 输入

```
malayalam
```

### 输出

```
15
```



---



---

# 题号列表

- SP7586 - NUMOFPAL - Number of Palindromes


---

---
title: "JAVAC - Java vs C &#43&#43"
layout: "post"
diff: 普及-
pid: SP1163
tag: ['模拟']
---

# JAVAC - Java vs C &#43&#43

## 题目描述

Apologists of Java and C++ can argue for hours proving each other that their programming language is the best one. Java people will tell that their programs are clearer and less prone to errors, while C++ people will laugh at their inability to instantiate an array of generics or tell them that their programs are slow and have long source code.

  
 Another issue that Java and C++ people could never agree on is identifier naming. In Java a multiword identifier is constructed in the following manner: the first word is written starting from the small letter, and the following ones are written starting from the capital letter, no separators are used. All other letters are small. Examples of a Java identifier are javaIdentifier, longAndMnemonicIdentifier, name, nEERC.

  
 Unlike them, C++ people use only small letters in their identifiers. To separate words they use underscore character ‘\_’. Examples of C++ identifiers are c\_identifier, long\_and\_mnemonic\_identifier, name (you see that when there is just one word Java and C++ people agree), n\_e\_e\_r\_c.

  
 You are writing a translator that is intended to translate C++ programs to Java and vice versa. Of course, identifiers in the translated program must be formatted due to its language rules — otherwise people will never like your translator.

  
 The first thing you would like to write is an identifier translation routine. Given an identifier, it would detect whether it is Java identifier or C++ identifier and translate it to another dialect. If it is neither, then your routine should report an error. Translation must preserve the order of words and must only change the case of letters and/or add/remove underscores.

## 输入格式

The input file consists of several lines that contains an identifier. It consists of letters of the English alphabet and underscores. Its length does not exceed 100.

## 输出格式

If the input identifier is Java identifier, output its C++ version. If it is C++ identifier, output its Java version. If it is none, output 'Error!' instead.

## 样例 #1

### 输入

```
long_and_mnemonic_identifier

anotherExample

i

bad_Style
```

### 输出

```
longAndMnemonicIdentifier

another_example

i

Error!
```



---

---
title: "ULM02 - The Sierpinski Fractal"
layout: "post"
diff: 普及-
pid: SP15728
tag: ['模拟', '递归']
---

# ULM02 - The Sierpinski Fractal

## 题目描述

Consider a regular triangular area, divide it into four equal triangles of half height and remove the one in the middle. Apply the same operation recursively to each of the three remaining triangles. If we repeated this procedure infinite times, we'd obtain something with an area of zero. The fractal that evolves this way is called the Sierpinski Triangle. Although its topological dimension is _2_, its Hausdorff-Besicovitch dimension is_log(3)/log(2)~1.58_, a fractional value (that's why it is called a fractal). By the way, the Hausdorff-Besicovitch dimension of the Norwegian coast is approximately _1.52_, its topological dimension being _1_.

For this problem, you are to outline the Sierpinski Triangle up to a certain recursion depth, using just ASCII characters. Since the drawing resolution is thus fixed, you'll need to grow the picture appropriately. Draw the smallest triangle (that is not divided any further) with two slashes, to backslashes and two underscores like this:

 /\\



---

---
title: "PRIME1 - Prime Generator"
layout: "post"
diff: 普及-
pid: SP2
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# PRIME1 - Prime Generator

## 题目描述

 Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

## 输入格式

 The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

## 输出格式

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)**   
Information
-----------

 After cluster change, please consider [PRINT](http://www.spoj.com/problems/PRINT/) as a more challenging problem.

## 样例 #1

### 输入

```
2
1 10
3 5
```

### 输出

```
2
3
5
7

3
5
```



---

---
title: "SBANK - Sorting Bank Accounts"
layout: "post"
diff: 普及-
pid: SP27
tag: ['模拟', '字符串', '排序']
---

# SBANK - Sorting Bank Accounts

## 题目描述

 In one of the internet banks thousands of operations are being performed every day. Since certain customers do business more actively than others, some of the bank accounts occur many times in the list of operations. Your task is to sort the bank account numbers in ascending order. If an account appears twice or more in the list, write the number of repetitions just after the account number. The format of accounts is as follows: **2** control digits, an **8**-digit code of the bank, **16** digits identifying the owner (written in groups of four digits), for example (at the end of each line there is exactly one space):

**30 10103538 2222 1233 6160 0142**  **Banks are real-time institutions and they need FAST solutions. If you feel you can meet the challenge within a very stringent time limit, go ahead!** A well designed sorting algorithm in a fast language is likely to succeed.

## 输入格式

   
_t_ \[the number of tests <= **5**\]   
_n_ \[the number of accounts<= **100 000**\]   
\[list of accounts\]   
\[empty line\]   
\[next test cases\]

## 输出格式

   
\[sorted list of accounts with the number of repeated accounts\]   
\[empty line\]   
\[other results\]

## 样例 #1

### 输入

```
2
6
03 10103538 2222 1233 6160 0142 
03 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 

5
30 10103538 2222 1233 6160 0144 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0145 
30 10103538 2222 1233 6160 0146 
30 10103538 2222 1233 6160 0143
```

### 输出

```
03 10103538 2222 1233 6160 0141 1
03 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0141 2
30 10103538 2222 1233 6160 0142 2

30 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0143 1
30 10103538 2222 1233 6160 0144 1
30 10103538 2222 1233 6160 0145 1
30 10103538 2222 1233 6160 0146 1
```



---

---
title: "ARMY - Army Strength"
layout: "post"
diff: 普及-
pid: SP2727
tag: ['模拟']
---

# ARMY - Army Strength

## 题目描述

The next MechaGodzilla invasion is on its way to Earth. And once again, Earth will be the battleground for an epic war.

MechaGodzilla's army consists of many nasty alien monsters, such as Space Godzilla, King Gidorah, and MechaGodzilla herself.

To stop them and defend Earth, Godzilla and her friends are preparing for the battle.

## 样例 #1

### 输入

```
2

1 1
1
1

3 2
1 3 2
5 5
```

### 输出

```
Godzilla
MechaGodzilla
```



---

---
title: "CNTDO - Count Doubles"
layout: "post"
diff: 普及-
pid: SP27303
tag: ['模拟']
---

# CNTDO - Count Doubles

## 题目描述

给你一个整数数组，您的任务是确定数组中的某个整数是同一数组中其他整数的两倍的数的个数。例如，考虑一个数组 $a=\{1,3,4,7,9,2,18\}$，答案是 $3$，因为 $2$ 是 $1$ 的两倍，$4$ 是 $2$ 的两倍， $18$ 是 $9$ 的两倍。

## 输入格式

第一行一个整数 $T$（$T\leq1000$），表示数据组数。  
每组数据包含两行：  
第一行一个整数 $N$（$1\leq N\leq 1000$），表示给定数组中不同整数的数量。  
第二行包含 $N$ 个整数，每个整数的绝对值不大于 $10000$。

## 输出格式

共一行，输出是其他整数的两倍的整数的个数。  

翻译 By [wangzl](https://www.luogu.com.cn/user/222039)



---

---
title: "ONP - Transform the Expression"
layout: "post"
diff: 普及-
pid: SP4
tag: ['模拟', '递归', '栈']
---

# ONP - Transform the Expression

## 题目描述

请你将 $n$ 个中缀表达式转换为后缀表达式。

## 输入格式

第一行一个整数 $n$ 代表中缀表达式个数。

接下来 $n$ 行代表 $n$ 个中缀表达式。

## 输出格式

$n$ 行代表每个中缀表达式转换过来的后缀表达式。

## 说明/提示

对于 $100\%$ 的数据，$n \le 100$ , 表达式长度 $\le 400$ 。

Translated by @[稀神探女](/user/85216)

## 样例 #1

### 输入

```
3

(a+(b*c))

((a+b)*(z+x))

((a+t)*((b+(a+c))^(c+d)))
```

### 输出

```
abc*+

ab+zx+*

at+bac++cd+^*
```



---

---
title: "ANARC07C - Rotating Rings"
layout: "post"
diff: 普及-
pid: SP4568
tag: ['模拟']
---

# ANARC07C - Rotating Rings

## 题目描述

任何方形网格都可以看作一个或多个环，一个套在一个里面。例如，如图 (a) 所示，一个 5 x 5 的网格由三个环组成，编号为 1、2 和 3（从外到内）。一个大小为 $N$ 的方形网格被称为有序的，如果它包含从 1 到 $N^2$ 的值，并且按行优先顺序排列，如图 (b) 所示，其中 $N = 4$。我们希望确定给定的方形网格是否可以通过仅旋转其环来排序。例如，图 (c) 中的网格可以通过将第一个环逆时针旋转两个位置，并将第二个环顺时针旋转一个位置来排序。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4568/de2efad7acfbae02d1e24e4c5bae5c3fbd72210c.png)

## 输入格式

你的程序将被测试在一个或多个测试用例上。每个测试用例的第一行是一个整数 $N$，表示网格的大小。接下来有 $N$ 行，每行包含 $N$ 个整数值，按行优先顺序指定网格中的值。注意 $0 < N \leq 1000$。

测试用例以一个虚拟测试用例结束，该测试用例的 $N = 0$。

## 输出格式

对于每个测试用例，在单独的一行上输出结果，使用以下格式：

`k. 结果`

其中 $k$ 是测试用例编号（从 1 开始），结果是 "YES" 或 "NO"（不带双引号），并且在 "." 和 "结果" 之间有一个空格。

## 样例

```
输入
4
9 5 1 2
13 7 11 3
14 6 10 4
15 16 12 8
3
1 2 3
5 6 7
8 9 4
0

输出
1. YES
2. NO
```



---

---
title: "GLJIVE - GLJIVE"
layout: "post"
diff: 普及-
pid: SP8319
tag: ['模拟', '前缀和']
---

# GLJIVE - GLJIVE

## 题目描述

 In front of Super Mario there are **10 mushrooms**, arranged in a row. A certain amount of points is awarded for picking each of the mushrooms. Super Mario must pick mushrooms **in order** they appear, but is not required to pick them all – his goal is to score a number of points **as close as possible to 100**.

In case there exist two such numbers which are equally close to 100 (e.g. 98 and 102), Mario will pick the **greater** one (in this case 102).

Help Super Mario and tell him how many points he will score.

## 输入格式

Input consists of 10 lines, each of which contains one positive integer less than or equal to 100, denoting the scores awarded for picking each mushroom, in the order that Mario can pick them in.

## 输出格式

The first and only line of output must contain the required number of points.

## 样例 #1

### 输入

```
10

20

30

40

50

60

70

80

90

100
```

### 输出

```
100
```



---

---
title: "NY10A - Penney Game"
layout: "post"
diff: 普及-
pid: SP8612
tag: ['模拟', '字符串']
---

# NY10A - Penney Game

## 题目描述

Penney’s game is a simple game typically played by two players. One version of the game calls for each player to choose a unique three-coin sequence such as **HEADS TAILS HEADS (HTH)**. A fair coin is tossed sequentially some number of times until one of the two sequences appears. The player who chose the first sequence to appear wins the game.

For this problem, you will write a program that implements a variation on the Penney Game. You willread a sequence of 40 coin tosses and determine how many times each three-coin sequence appears. Obviously there are eight such three-coin sequences: **TTT**, **TTH**, **THT**, **THH**, **HTT**, **HTH**, **HHT** and **HHH**. Sequences may overlap. For example, if all 40 coin tosses are heads, then the sequence HHH appears 38 times.

## 输入格式

The first line of input contains a single integer P, (1

## 输出格式

For each data set there is one line of output. It contains the data set number followed by a single space, followed by the number of occurrences of each three-coin sequence, in the order shown above, with a space between each one. There should be a total of 9 space separated decimal integers on each output line.

## 样例 #1

### 输入

```
\n4\n1\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n2\nTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n3\nHHTTTHHTTTHTHHTHHTTHTTTHHHTHTTHTTHTTTHTH\n4\nHTHTHHHTHHHTHTHHHHTTTHTTTTTHHTTTTHTHHHHT\n\n
```

### 输出

```
\n1 0 0 0 0 0 0 0 38\n2 38 0 0 0 0 0 0 0\n3 4 7 6 4 7 4 5 1\n4 6 3 4 5 3 6 5 6
```



---



---

# 题号列表

- SP1163 - JAVAC - Java vs C &#43&#43
- SP15728 - ULM02 - The Sierpinski Fractal
- SP2 - PRIME1 - Prime Generator
- SP27 - SBANK - Sorting Bank Accounts
- SP2727 - ARMY - Army Strength
- SP27303 - CNTDO - Count Doubles
- SP4 - ONP - Transform the Expression
- SP4568 - ANARC07C - Rotating Rings
- SP8319 - GLJIVE - GLJIVE
- SP8612 - NY10A - Penney Game


---

---
title: "PRIMPERM - Prime Permutations"
layout: "post"
diff: 普及-
pid: SP8591
tag: ['深度优先搜索 DFS', '素数判断,质数,筛法']
---

# PRIMPERM - Prime Permutations

## 题目描述

$t$ 组数据，每组数据给定一个整数 $n$，求 $n$ 的排列中有多少个排列是质数。

## 输入格式

共 $t+1$ 行：

第一行为一个整数 $t$。

第 $2\sim t+1$ 行每行一个整数 $n$。

## 输出格式

共 $t$ 行，每行一个整数表示 $n$ 的排列中有多少个排列是质数。

## 说明/提示

$t<10^4$，$n<10^7$

## 样例 #1

### 输入

```
2

13

110
```

### 输出

```
2

1
```



---



---

# 题号列表

- SP8591 - PRIMPERM - Prime Permutations


---

---
title: "PRIME1 - Prime Generator"
layout: "post"
diff: 普及-
pid: SP2
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# PRIME1 - Prime Generator

## 题目描述

 Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

## 输入格式

 The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

## 输出格式

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)**   
Information
-----------

 After cluster change, please consider [PRINT](http://www.spoj.com/problems/PRINT/) as a more challenging problem.

## 样例 #1

### 输入

```
2
1 10
3 5
```

### 输出

```
2
3
5
7

3
5
```



---

---
title: "VECTAR8 - Primal Fear"
layout: "post"
diff: 普及-
pid: SP27318
tag: ['素数判断,质数,筛法']
---

# VECTAR8 - Primal Fear

## 题目描述

Changu 和 Mangu 对质数感到害怕，但他们并不是害怕所有的质数。他们只畏惧一种特殊的质数：这种质数不含数字 0，并且无论去掉多少个前导数字，剩下的部分依然是质数。举个例子，他们会害怕 4632647，因为它不包含数字 0，而且它的每一个前导截断（632647、32647、2647、647、47 和 7）都是质数。

你的任务是，对于给定的数字 $N$，找出有多少个不大于 $N$ 且被 Changu 和 Mangu 害怕的质数。

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量。接下来有 $T$ 行，每行包含一个整数 $N$。

## 输出格式

对于每个测试用例，输出一行结果，表示不大于 $N$ 的 Changu 和 Mangu 害怕的质数的个数。

## 说明/提示

$1 \le T \le 100$

$1 \le N \le 10^6$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3

2

3

4
```

### 输出

```
1

2

2
```



---

---
title: "PRIMPERM - Prime Permutations"
layout: "post"
diff: 普及-
pid: SP8591
tag: ['深度优先搜索 DFS', '素数判断,质数,筛法']
---

# PRIMPERM - Prime Permutations

## 题目描述

$t$ 组数据，每组数据给定一个整数 $n$，求 $n$ 的排列中有多少个排列是质数。

## 输入格式

共 $t+1$ 行：

第一行为一个整数 $t$。

第 $2\sim t+1$ 行每行一个整数 $n$。

## 输出格式

共 $t$ 行，每行一个整数表示 $n$ 的排列中有多少个排列是质数。

## 说明/提示

$t<10^4$，$n<10^7$

## 样例 #1

### 输入

```
2

13

110
```

### 输出

```
2

1
```



---



---

# 题号列表

- SP2 - PRIME1 - Prime Generator
- SP27318 - VECTAR8 - Primal Fear
- SP8591 - PRIMPERM - Prime Permutations


---

---
title: "PRIME1 - Prime Generator"
layout: "post"
diff: 普及-
pid: SP2
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# PRIME1 - Prime Generator

## 题目描述

 Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

## 输入格式

 The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

## 输出格式

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)**   
Information
-----------

 After cluster change, please consider [PRINT](http://www.spoj.com/problems/PRINT/) as a more challenging problem.

## 样例 #1

### 输入

```
2
1 10
3 5
```

### 输出

```
2
3
5
7

3
5
```



---

---
title: "VECTAR8 - Primal Fear"
layout: "post"
diff: 普及-
pid: SP27318
tag: ['素数判断,质数,筛法']
---

# VECTAR8 - Primal Fear

## 题目描述

Changu 和 Mangu 对质数感到害怕，但他们并不是害怕所有的质数。他们只畏惧一种特殊的质数：这种质数不含数字 0，并且无论去掉多少个前导数字，剩下的部分依然是质数。举个例子，他们会害怕 4632647，因为它不包含数字 0，而且它的每一个前导截断（632647、32647、2647、647、47 和 7）都是质数。

你的任务是，对于给定的数字 $N$，找出有多少个不大于 $N$ 且被 Changu 和 Mangu 害怕的质数。

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量。接下来有 $T$ 行，每行包含一个整数 $N$。

## 输出格式

对于每个测试用例，输出一行结果，表示不大于 $N$ 的 Changu 和 Mangu 害怕的质数的个数。

## 说明/提示

$1 \le T \le 100$

$1 \le N \le 10^6$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3

2

3

4
```

### 输出

```
1

2

2
```



---

---
title: "PRIMPERM - Prime Permutations"
layout: "post"
diff: 普及-
pid: SP8591
tag: ['深度优先搜索 DFS', '素数判断,质数,筛法']
---

# PRIMPERM - Prime Permutations

## 题目描述

$t$ 组数据，每组数据给定一个整数 $n$，求 $n$ 的排列中有多少个排列是质数。

## 输入格式

共 $t+1$ 行：

第一行为一个整数 $t$。

第 $2\sim t+1$ 行每行一个整数 $n$。

## 输出格式

共 $t$ 行，每行一个整数表示 $n$ 的排列中有多少个排列是质数。

## 说明/提示

$t<10^4$，$n<10^7$

## 样例 #1

### 输入

```
2

13

110
```

### 输出

```
2

1
```



---



---

# 题号列表

- SP2 - PRIME1 - Prime Generator
- SP27318 - VECTAR8 - Primal Fear
- SP8591 - PRIMPERM - Prime Permutations


---

---
title: "TAKIN - Taskin and apple tree"
layout: "post"
diff: 普及-
pid: SP33795
tag: ['枚举', '剪枝', '背包 DP']
---

# TAKIN - Taskin and apple tree

## 题目描述

# TAKIN - Taskin和苹果树


Taskin有一个苹果园，每天早上他都会去果园采摘苹果。他有一个篮子，可以携带**不超过 M个**苹果。Taskin将所摘的苹果放入篮子里，对于每一棵树，他要么将这棵树上的所有苹果摘完，要么跳过这棵树不摘。现在让你制定一个方案，使Taskin所摘的苹果数量最多。

## 输入格式

在第一行输入一个整数T，表示有T个测试数据。

每组测试数据以两个整数 M 和 N 开始，分别表示果园中的苹果树的数量和篮子最多能装的苹果数。

接下来有N个整数：a[1],a[2],a[3],...,a[n],其中a[i]表示第i棵苹果树所结苹果的个数。

## 输出格式

输出一个整数，表示所能摘的最大的苹果数。

## 输入输出样例
### 输入样例＃1：

```cpp
2 
5 6 
2 1 2 7 8 
5 10 
1 2 4 4 6
```
### 输出样例＃1：

```cpp
5 
10
```

## 说明/提示

T<=10,N<=20,M<=2*10^10,a[i]<=10^9

翻译提供者：right_cat

## 样例 #1

### 输入

```
2
5 6
2 1 2 7 8
5 10
1 2 4 4 6
```

### 输出

```
5
10
```



---



---

# 题号列表

- SP33795 - TAKIN - Taskin and apple tree


---

---
title: "PRIME1 - Prime Generator"
layout: "post"
diff: 普及-
pid: SP2
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# PRIME1 - Prime Generator

## 题目描述

 Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

## 输入格式

 The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

## 输出格式

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)**   
Information
-----------

 After cluster change, please consider [PRINT](http://www.spoj.com/problems/PRINT/) as a more challenging problem.

## 样例 #1

### 输入

```
2
1 10
3 5
```

### 输出

```
2
3
5
7

3
5
```



---

---
title: "VECTAR8 - Primal Fear"
layout: "post"
diff: 普及-
pid: SP27318
tag: ['素数判断,质数,筛法']
---

# VECTAR8 - Primal Fear

## 题目描述

Changu 和 Mangu 对质数感到害怕，但他们并不是害怕所有的质数。他们只畏惧一种特殊的质数：这种质数不含数字 0，并且无论去掉多少个前导数字，剩下的部分依然是质数。举个例子，他们会害怕 4632647，因为它不包含数字 0，而且它的每一个前导截断（632647、32647、2647、647、47 和 7）都是质数。

你的任务是，对于给定的数字 $N$，找出有多少个不大于 $N$ 且被 Changu 和 Mangu 害怕的质数。

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量。接下来有 $T$ 行，每行包含一个整数 $N$。

## 输出格式

对于每个测试用例，输出一行结果，表示不大于 $N$ 的 Changu 和 Mangu 害怕的质数的个数。

## 说明/提示

$1 \le T \le 100$

$1 \le N \le 10^6$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3

2

3

4
```

### 输出

```
1

2

2
```



---

---
title: "PRIMPERM - Prime Permutations"
layout: "post"
diff: 普及-
pid: SP8591
tag: ['深度优先搜索 DFS', '素数判断,质数,筛法']
---

# PRIMPERM - Prime Permutations

## 题目描述

$t$ 组数据，每组数据给定一个整数 $n$，求 $n$ 的排列中有多少个排列是质数。

## 输入格式

共 $t+1$ 行：

第一行为一个整数 $t$。

第 $2\sim t+1$ 行每行一个整数 $n$。

## 输出格式

共 $t$ 行，每行一个整数表示 $n$ 的排列中有多少个排列是质数。

## 说明/提示

$t<10^4$，$n<10^7$

## 样例 #1

### 输入

```
2

13

110
```

### 输出

```
2

1
```



---



---

# 题号列表

- SP2 - PRIME1 - Prime Generator
- SP27318 - VECTAR8 - Primal Fear
- SP8591 - PRIMPERM - Prime Permutations


---

---
title: "COWCAR - Cow Cars"
layout: "post"
diff: 普及-
pid: SP2714
tag: ['贪心', '队列']
---

# COWCAR - Cow Cars

## 题目描述

N (1 ≤ N ≤ 50,000) cows conveniently numbered 1, ..., N are driving in separate cars along a highway in Cowtopia. Cow i can drive in any of M different high lanes (1 ≤ M ≤ N) and can travel at a maximum speed of S $ _{i} $ (1 ≤ S $ _{i} $ ≤ 1,000,000) km/hour.

After their other bad driving experience, the cows hate collisions and take extraordinary measures to avoid them. On this highway, cow i reduces its speed by D (0 ≤ D ≤ 5,000) km/hour for each cow in front of it on the highway (though never below 0 km/hour). Thus, if there are K cows in front of cow i, the cow will travel at a speed of max(S $ _{i} $ - D\*K, 0). While a cow might actually travel faster than a cow directly in front of it, the cows are spaced far enough apart so crashes will not occur once cows slow down as described.

Cowtopia has a minimum speed law which requires everyone on the highway to travel at a a minimum speed of L (1 ≤ L ≤ 1,000,000) km/hour, so sometimes some of the cows will be unable to take the highway if they follow the rules above. Write a program that will find the maximum number of cows that can drive on the highway while obeying the minimum speed limit law.

## 输入格式

The first line contains the four integers N, M, D, and L. For the next N lines, line i+1 contains the integer S $ _{i} $ .

## 输出格式

Print a single integer denoting the maximum number of cows that can take the highway.

## 样例 #1

### 输入

```
3 1 1 5

5

7

5
```

### 输出

```
2
```



---

---
title: "MDOLLS - Nested Dolls"
layout: "post"
diff: 普及-
pid: SP3943
tag: ['贪心', '二分', '排序']
---

# MDOLLS - Nested Dolls

## 题目描述

[English](/problems/MDOLLS/en/) [Vietnamese](/problems/MDOLLS/vn/) ```

Dilworth is the world's most prominent collector of Russian nested dolls:
he literally has thousands of them! You know, the wooden hollow dolls of 
different sizes of which the smallest doll is contained in the second smallest,
and this doll is in turn contained in the next one and so forth. One day he
wonders if there is another way of nesting them so he will end up with
fewer nested dolls? After all, that would make his collection even 
more magnificent! He unpacks each nested doll and measures the width 
and height of each contained doll. A doll with width w1 and height h1 will
fit in another doll of width w2 and height h= if and only if w1 < w2 and 
h1 < h2. Can you help him calculate the smallest number of nested dolls 
possible to assemble from his massive list of measurements? 
```

## 输入格式

```

On the first line of input is a single positive integer 1 ≤ t ≤ 20 specifying
the number of test cases to follow. Each test case begins with a positive 
integer 1 ≤ m ≤ 20000 on a line of itself telling the number of dolls 
in the test case. Next follow 2m positive integers w1, h1,w2, h2, ... ,wm, 
hm, where wi is the width and hi is the height of doll number i. 
1 ≤ wi, hi ≤ 10000 for all i.

SAMPLE INPUT
4
3
20 30 40 50 30 40
4
20 30 10 10 30 20 40 50
3
10 30 20 20 30 10
4
10 10 20 30 40 50 39 51
```

## 输出格式

```
 
For each test case there should be one line of output containing the minimum
number of nested dolls possible.

SAMPLE OUTPUT
1
2
3
2
```



---



---

# 题号列表

- SP2714 - COWCAR - Cow Cars
- SP3943 - MDOLLS - Nested Dolls


---

---
title: "TAP2014B - Balanced base-3"
layout: "post"
diff: 普及-
pid: SP21169
tag: ['进制']
---

# TAP2014B - Balanced base-3

## 题目描述

历史上，已经发展出许多种计数系统。其中，有些系统如罗马数字，由于不够方便，几乎已被淘汰。而其他更独特的系统，如用于排列编号的阶乘数，仅在特定领域中应用。今天，我们要探讨一种叫做「平衡三进制」的计数系统，这种系统常自然出现于分析平衡秤相关的数学问题中。

平衡三进制与我们熟悉的十进制或其他进制系统相似，因为它都属于「位置计数法」。位置计数法中，数字的位置决定了其对应基数的幂。例如，在十进制中，数字 123 可表示为：

123 = **1** × 10 $ ^{2} $ + **2** × 10 $ ^{1} $ + **3** × 10 $ ^{0} $ 。

在标准位置计数系统中，允许的数字范围是从 0 到 **B-1**，这里的 **B** 是系统的基数。因此，十进制的 123 在标准三进制中可以写为 **"11120"**，因为

**1** × 3 $ ^{4} $ + **1** × 3 $ ^{3} $ + **1** × 3 $ ^{2} $ + **2** × 3 $ ^{1} $ + 0 × 3 $ ^{0} $ = 123。

平衡三进制与标准三进制的区别在于，平衡三进制系统允许的数字是 0、**1** 和 **-1**，我们分别用 **'0'**、**'+'** 和 **'-'** 表示。所以，十进制的 123 用平衡三进制表示则为 **"+----0"**，其计算过程为：

**1** × 3 $ ^{5} $ + (**-1**) × 3 $ ^{4} $ + (**-1**) × 3 $ ^{3} $ + (**-1**) × 3 $ ^{2} $ + (**-1**) × 3 $ ^{1} $ + 0 × 3 $ ^{0} $ = 123。

从十进制转换到平衡三进制虽然过程比较机械且繁琐，但相对简单。因此，我们需要编写一个程序来帮我们做这个转换。你能完成这个任务吗？

## 输入格式

第一行包含一个整数 **T**，表示测试用例的个数（1 ≤ T ≤ 100）。接下来是 **T** 个测试用例。

每个测试用例由一行组成，包含一个正整数 **N**，代表我们要转换成平衡三进制的十进制数（1 ≤ N ≤ 1000）。

## 输出格式

对每个测试用例，输出一行，由字符 **'0'**、**'+'** 和 **'-'** 组成的字符串，不以 **'0'** 开头，表示数字 **N** 在平衡三进制下的唯一表示。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2

123

729
```

### 输出

```
+----0

+000000
```



---



---

# 题号列表

- SP21169 - TAP2014B - Balanced base-3


---

---
title: "ULM02 - The Sierpinski Fractal"
layout: "post"
diff: 普及-
pid: SP15728
tag: ['模拟', '递归']
---

# ULM02 - The Sierpinski Fractal

## 题目描述

Consider a regular triangular area, divide it into four equal triangles of half height and remove the one in the middle. Apply the same operation recursively to each of the three remaining triangles. If we repeated this procedure infinite times, we'd obtain something with an area of zero. The fractal that evolves this way is called the Sierpinski Triangle. Although its topological dimension is _2_, its Hausdorff-Besicovitch dimension is_log(3)/log(2)~1.58_, a fractional value (that's why it is called a fractal). By the way, the Hausdorff-Besicovitch dimension of the Norwegian coast is approximately _1.52_, its topological dimension being _1_.

For this problem, you are to outline the Sierpinski Triangle up to a certain recursion depth, using just ASCII characters. Since the drawing resolution is thus fixed, you'll need to grow the picture appropriately. Draw the smallest triangle (that is not divided any further) with two slashes, to backslashes and two underscores like this:

 /\\



---

---
title: "KUSAC - Kusac"
layout: "post"
diff: 普及-
pid: SP16244
tag: ['递归']
---

# KUSAC - Kusac

## 题目描述

Mirko has given up on the difficult coach job and switched to food tasting instead. Having skipped 

breakfast like a professional connoisseur, he is visiting a Croatian cured meat festival. The most 

renowned cook at the festival, Marijan Bajs, has prepared N equal sausages which need to be 

distributed to M tasters such that each taster gets a precisely equal amount. He will use his trusted knife 

to cut them into pieces. 

In order to elegantly divide the sausages, the number of cuts splitting individual sausages must be as 

small as possible. For instance, if there are two sausages and six tasters (the first test case below), it is 

sufficient to split each sausage into three equal parts, making a total of four cuts. On the other hand, if 

there are three sausages and four tasters (the second test case below), one possibility is cutting off three 

quarters of each sausage. Those larger parts will each go to one of the tasrers, while the fourth taster 

will get the three smaller pieces (quarters) left over. 

Mirko wants to try the famous sausages, so he volunteered to help Bajs. Help them calculate the 

minimum total number of cuts needed to carry out the desired division. 

## 输入格式

The first and only line of input contains two positive integers, N and M (1

of sausages and tasters, respectively.

## 输出格式

The first and only line of output must contain the required minimum number of cuts.

## 样例 #1

### 输入

```
2 6
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4

```

### 输出

```
3

```



---

---
title: "ONP - Transform the Expression"
layout: "post"
diff: 普及-
pid: SP4
tag: ['模拟', '递归', '栈']
---

# ONP - Transform the Expression

## 题目描述

请你将 $n$ 个中缀表达式转换为后缀表达式。

## 输入格式

第一行一个整数 $n$ 代表中缀表达式个数。

接下来 $n$ 行代表 $n$ 个中缀表达式。

## 输出格式

$n$ 行代表每个中缀表达式转换过来的后缀表达式。

## 说明/提示

对于 $100\%$ 的数据，$n \le 100$ , 表达式长度 $\le 400$ 。

Translated by @[稀神探女](/user/85216)

## 样例 #1

### 输入

```
3

(a+(b*c))

((a+b)*(z+x))

((a+t)*((b+(a+c))^(c+d)))
```

### 输出

```
abc*+

ab+zx+*

at+bac++cd+^*
```



---



---

# 题号列表

- SP15728 - ULM02 - The Sierpinski Fractal
- SP16244 - KUSAC - Kusac
- SP4 - ONP - Transform the Expression


---

---
title: "COWCAR - Cow Cars"
layout: "post"
diff: 普及-
pid: SP2714
tag: ['贪心', '队列']
---

# COWCAR - Cow Cars

## 题目描述

N (1 ≤ N ≤ 50,000) cows conveniently numbered 1, ..., N are driving in separate cars along a highway in Cowtopia. Cow i can drive in any of M different high lanes (1 ≤ M ≤ N) and can travel at a maximum speed of S $ _{i} $ (1 ≤ S $ _{i} $ ≤ 1,000,000) km/hour.

After their other bad driving experience, the cows hate collisions and take extraordinary measures to avoid them. On this highway, cow i reduces its speed by D (0 ≤ D ≤ 5,000) km/hour for each cow in front of it on the highway (though never below 0 km/hour). Thus, if there are K cows in front of cow i, the cow will travel at a speed of max(S $ _{i} $ - D\*K, 0). While a cow might actually travel faster than a cow directly in front of it, the cows are spaced far enough apart so crashes will not occur once cows slow down as described.

Cowtopia has a minimum speed law which requires everyone on the highway to travel at a a minimum speed of L (1 ≤ L ≤ 1,000,000) km/hour, so sometimes some of the cows will be unable to take the highway if they follow the rules above. Write a program that will find the maximum number of cows that can drive on the highway while obeying the minimum speed limit law.

## 输入格式

The first line contains the four integers N, M, D, and L. For the next N lines, line i+1 contains the integer S $ _{i} $ .

## 输出格式

Print a single integer denoting the maximum number of cows that can take the highway.

## 样例 #1

### 输入

```
3 1 1 5

5

7

5
```

### 输出

```
2
```



---



---

# 题号列表

- SP2714 - COWCAR - Cow Cars


---

---
title: "SUMPRIM2 - Sum of primes (reverse mode)"
layout: "post"
diff: 省选/NOI-
pid: SP18932
tag: ['二分', '数论', '素数判断,质数,筛法', '其它技巧']
---

# SUMPRIM2 - Sum of primes (reverse mode)

## 题目描述

XerK had prepared his new problem with some sums of primes up to some bounds. His results are well here, but he forgot the bounds. Your task is to find which was the last prime in the sum. This problem is extremely simple, but you have to be extremely fast.

## 输入格式

The lonely line of input contains an integer **_S_**.

## 输出格式

You have to print the last prime **_P_** such that **_sum(prime from 2 to P) = S_**.



---

---
title: "NTHPRIME - Nth Prime"
layout: "post"
diff: 省选/NOI-
pid: SP25024
tag: ['数学', '二分', '素数判断,质数,筛法']
---

# NTHPRIME - Nth Prime

## 题目描述

There is no tedious description for this problem. You are just required to calculate and output the **Nth** prime number.

## 输入格式

The input consists of a single line containing an integer **N,** **N** **10^9**.

## 输出格式

For each input file, output the **Nth** prime number.

## 样例 #1

### 输入

```
4
```

### 输出

```
7
```



---

---
title: "KNIGHTS - Knights of the Round Table"
layout: "post"
diff: 省选/NOI-
pid: SP2878
tag: ['二分图']
---

# KNIGHTS - Knights of the Round Table

## 题目描述

### 题目大意

有 $n$ 个骑士经常举行圆桌会议，商讨大事。每次圆桌会议至少有 $3$ 个骑士参加，且相互憎恨的骑士不能坐在圆桌的相邻位置。如果发生意见分歧，则需要举手表决，因此参加会议的骑士数目必须是大于 $1$ 的奇数，以防止赞同和反对票一样多。知道骑士之间相互憎恨的关系后，请你帮忙统计有多少骑士参加不了任意一个会议。

## 输入格式

**本题包含多组数据。**

对于每组数据， 第一行为两个整数 $n$ 和 $m$。


接下来 $m$ 行每行两个整数 $k_1$ 和 $k_2$，表示骑士 $k_1$ 和 $k_2$ 相互憎恨。 

$n=m=0$ 为数据末尾的标记，无需处理这组数据。

## 输出格式

对于每组数据，输出一行一个整数，表示无法参加任何会议的骑士数量。

感谢@hicc0305 提供的翻译

## 说明/提示

$1\leq n \leq 10^3$，$1\leq m\leq10^6$。保证 $1\leq k_1,k_2\leq n$。

$\small{\text{Statement fixed by @Starrykiller.}}$

## 样例 #1

### 输入

```
5 5
1 4
1 5
2 5
3 4
4 5
0 0
```

### 输出

```
2
```



---



---

# 题号列表

- SP18932 - SUMPRIM2 - Sum of primes (reverse mode)
- SP25024 - NTHPRIME - Nth Prime
- SP2878 - KNIGHTS - Knights of the Round Table


---

---
title: "MOD - Power Modulo Inverted"
layout: "post"
diff: 省选/NOI-
pid: SP3105
tag: ['枚举', '分块']
---

# MOD - Power Modulo Inverted

## 题目描述

Given 3 positive integers _x_, _y_ and _z_, you can find _k = x $ ^{y} $ %z_ easily, by fast power-modulo algorithm. Now your task is the inverse of this algorithm. Given 3 positive integers _x_, _z_ and _k_, find the smallest non-negative integer _y_, such that _k%z = x $ ^{y} $ %z_.

## 输入格式

About 600 test cases.

Each test case contains one line with 3 integers _x_, _z_ and _k_.(1<= _x_, _z_, _k_ <=10 $ ^{9} $ )

Input terminates by three zeroes.

## 输出格式

For each test case, output one line with the answer, or "No Solution"(without quotes) if such an integer doesn't exist.

## 样例 #1

### 输入

```
5 58 33
2 4 3
0 0 0
```

### 输出

```
9
No Solution
```



---

---
title: "PRIMES2 - Printing some primes (Hard)"
layout: "post"
diff: 省选/NOI-
pid: SP6488
tag: ['数学', '素数判断,质数,筛法', '分块']
---

# PRIMES2 - Printing some primes (Hard)

## 题目描述

The problem statement is really simple (the constraints maybe not). You are to write all primes less than 10^9.

## 输入格式

There is not input.

## 输出格式

To make the problem less output related write out only the 1st, 501st, 1001st, ... 1st mod 500.

## 样例 #1

### 输入

```

```

### 输出

```
2

3581

7927

...

999978527

999988747

999999151
```



---

---
title: "VLATTICE - Visible Lattice Points"
layout: "post"
diff: 省选/NOI-
pid: SP7001
tag: ['数学', '莫比乌斯反演', '整除分块']
---

# VLATTICE - Visible Lattice Points

## 题目描述

Consider a N\*N\*N lattice. One corner is at (0,0,0) and the opposite one is at (N,N,N). How many lattice points are visible from corner at (0,0,0) ? A point X is visible from point Y iff no other lattice point lies on the segment joining X and Y.   
   
Input :   
The first line contains the number of test cases T. The next T lines contain an interger N   
   
Output :   
Output T lines, one corresponding to each test case.   
   
Sample Input :   
3   
1   
2   
5   
   
Sample Output :   
7   
19   
175   
   
Constraints :   
T <= 50   
1 <= N <= 1000000



---



---

# 题号列表

- SP3105 - MOD - Power Modulo Inverted
- SP6488 - PRIMES2 - Printing some primes (Hard)
- SP7001 - VLATTICE - Visible Lattice Points


---

---
title: "NORMA2 - Norma"
layout: "post"
diff: 省选/NOI-
pid: SP22343
tag: ['分治', '前缀和', '概率论']
---

# NORMA2 - Norma

## 题目描述

Mirko got an array of integers for his birthday from his grandmother Norma. As any other kid, he was hoping for some money, but got an array. Luckily, in his town there is a pawn shop that buys up arrays. The cost of an array of integers is **min** \* **max** \* **L** kunas, where **min** is the minimal integer in the array, **max** is the maximal and **L** is the array length. Mirko is going to sell a subsequence of consecutive numbers from his array. He calculated the average price of all such subsequences.

In order to check his result, he wants you to do the same. He will be pleased with only the last 9 digits of the sum of all prices, so you don’t need to bother with large and real numbers.

## 输入格式

The first line of input contains an integer N (1

Each of the following N lines contains a member of Mirko’s array. The members of the array will be integers from the interval \[1, 10 $ ^{8} $ \].

## 输出格式

The first and only line of output must contain an integer, the last 9 digits of the required sum from the task. **You don’t need to output** the leading zeroes of that 9-digit integer.

## 样例 #1

### 输入

```
2\n1\n3 
```

### 输出

```
16
```



---

---
title: "QTREE4 - Query on a tree IV"
layout: "post"
diff: 省选/NOI-
pid: SP2666
tag: ['递归', '分治', '动态树 LCT', '概率论']
---

# QTREE4 - Query on a tree IV

## 题目描述

You are given a tree (an acyclic undirected connected graph) with $N$ nodes, and nodes numbered $1,2,3\ldots,N$. Each edge has an integer value assigned to it (note that the value can be negative). Each node has a color, white or black. We define $dist(a, b)$ as the sum of the value of the edges on the path from node $a$ to node $b$.

All the nodes are white initially.

We will ask you to perfrom some instructions of the following form:

- `C a` : change the color of node $a$.(from black to white or from white to black)
- `A` : ask for the maximum $dist(a, b)$, both of node a and node $b$ must be white ($a$ can be equal to $b$). Obviously, as long as there is a white node, the result will alway be non negative.

## 输入格式

- In the first line there is an integer $N$. ($N \leq 100000$)
- In the next $N-1$ lines, the $i$-th line describes the $i$-th edge: a line with three integers $a,b,c$ denotes an edge between $a, b$ of value $c$. ($-10^3 \leq c \leq 10^3$)
- In the next line, there is an integer $Q$ denotes the number of instructions. ($Q \leq 100000$)
- In the next $Q$ lines, each line contains an instruction `C a` or `A`.

## 输出格式

For each `A` operation, write one integer representing its result. If there is no white node in the tree, you should write `They have disappeared.`.

## 样例 #1

### 输入

```
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A
```

### 输出

```
2
2
0
They have disappeared.
```



---



---

# 题号列表

- SP22343 - NORMA2 - Norma
- SP2666 - QTREE4 - Query on a tree IV


---

---
title: "RATAR - Ratar"
layout: "post"
diff: 省选/NOI-
pid: SP16180
tag: ['枚举', '前缀和', '概率论']
---

# RATAR - Ratar

## 题目描述

Unexpected problems with law enforcement have convinced Mirko to take up a less lucrative but less

## 输入格式

The first line of input contains the positive integer N (1

land plot.

Each of the following N lines contains N space-separated numbers Aij (-1000 < Aij < 1000), the income

provided by the respective cell.

## 输出格式

The first and only line of output must contain the total number of plot pairs satisfying the given

condition.

## 样例 #1

### 输入

```
3

1 2 3

2 3 4

3 4 8
```

### 输出

```
7
```



---

---
title: "NORMA2 - Norma"
layout: "post"
diff: 省选/NOI-
pid: SP22343
tag: ['分治', '前缀和', '概率论']
---

# NORMA2 - Norma

## 题目描述

Mirko got an array of integers for his birthday from his grandmother Norma. As any other kid, he was hoping for some money, but got an array. Luckily, in his town there is a pawn shop that buys up arrays. The cost of an array of integers is **min** \* **max** \* **L** kunas, where **min** is the minimal integer in the array, **max** is the maximal and **L** is the array length. Mirko is going to sell a subsequence of consecutive numbers from his array. He calculated the average price of all such subsequences.

In order to check his result, he wants you to do the same. He will be pleased with only the last 9 digits of the sum of all prices, so you don’t need to bother with large and real numbers.

## 输入格式

The first line of input contains an integer N (1

Each of the following N lines contains a member of Mirko’s array. The members of the array will be integers from the interval \[1, 10 $ ^{8} $ \].

## 输出格式

The first and only line of output must contain an integer, the last 9 digits of the required sum from the task. **You don’t need to output** the leading zeroes of that 9-digit integer.

## 样例 #1

### 输入

```
2\n1\n3 
```

### 输出

```
16
```



---

---
title: "GSS5 - Can you answer these queries V"
layout: "post"
diff: 省选/NOI-
pid: SP2916
tag: ['线段树', '前缀和']
---

# GSS5 - Can you answer these queries V

## 题目描述

 You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| <= 10000 , 1 <= N <= 10000 ). A query is defined as follows: Query(x1,y1,x2,y2) = Max { A\[i\]+A\[i+1\]+...+A\[j\] ; x1 <= i <= y1 , x2 <= j <= y2 and x1 <= x2 , y1 <= y2 }. Given M queries (1 <= M <= 10000), your program must output the results of these queries.

## 输入格式

 The first line of the input consist of the number of tests cases <= 5. Each case consist of the integer N and the sequence A. Then the integer M. M lines follow, contains 4 numbers x1, y1, x2 y2.

## 输出格式

 Your program should output the results of the M queries for each test case, one query per line.

## 样例 #1

### 输入

```
2
6 3 -2 1 -4 5 2
2
1 1 2 3
1 3 2 5
1 1
1
1 1 1 1
```

### 输出

```
2
3
1
```



---



---

# 题号列表

- SP16180 - RATAR - Ratar
- SP22343 - NORMA2 - Norma
- SP2916 - GSS5 - Can you answer these queries V


---

---
title: "VIDEO - Video game combos"
layout: "post"
diff: 省选/NOI-
pid: SP10502
tag: ['字符串', '动态规划 DP']
---

# VIDEO - Video game combos

## 题目描述

 Bessie is playing a video game! In the game, the three letters 'A', 'B', and 'C' are the only valid buttons. Bessie may press the buttons in any order she likes. However, there are only N distinct combos possible (1 <= N <= 20). Combo i is represented as a string S\_i which has a length between 1 and 15 and contains only the letters 'A', 'B', and 'C'.

 Whenever Bessie presses a combination of letters that matches with a combo, she gets one point for the combo. Combos may overlap with each other or even finish at the same time! For example if N = 3 and the three possible combos are "ABA", "CB", and "ABACB", and Bessie presses "ABACB", she will end with 3 points. Bessie may score points for a single combo more than once.

 Bessie of course wants to earn points as quickly as possible. If she presses exactly K buttons (1 <= K <= 1,000), what is the maximum number of points she can earn?

## 样例 #1

### 输入

```
3 7
ABA
CB
ABACB
```

### 输出

```
4
```



---

---
title: "SEQPAR2 - Sequence Partitioning II"
layout: "post"
diff: 省选/NOI-
pid: SP1748
tag: ['动态规划 DP', '线段树']
---

# SEQPAR2 - Sequence Partitioning II

## 题目描述

Given a sequence of _N_ ordered pairs of positive integers (_A $ _{i} $_ , _B $ _{i} $_ ), you have to partition it into several contiguous parts. Let _p_ be the number of these parts, whose boundaries are (_l_ $ _{1} $ , _r_ $ _{1} $ ), (_l_ $ _{2} $ , _r_ $ _{2} $ ), ... ,(_l $ _{p} $_ , _r $ _{p} $_ ), which satisfy _l $ _{i} $_ = _r $ _{i-} $_  $ _{1} $ + 1, _l $ _{i} $_ <= _r $ _{i} $_ , _l_ $ _{1} $ = 1, _r $ _{p} $_ = _n_. The parts themselves also satisfy the following restrictions:

1. For any two pairs (_A $ _{p} $_ , _B $ _{p} $_ ), (_A $ _{q} $_ , _B $ _{q} $_ ), where (_A $ _{p} $_ , _B $ _{p} $_ ) is belongs to the _T $ _{p} $_ th part and (_A $ _{q} $_ , _B $ _{q} $_ ) the _T $ _{q} $_ th part. If _T $ _{p} $_ < _T $ _{q} $_ , then _B $ _{p} $_ > _A $ _{q} $_ .
2. Let _M $ _{i} $_  be the maximum _A_-component of elements in the _i_th part, say
  
  _M $ _{i} $_  = max {_A $ _{li} $_ , _A $ _{li+} $_  $ _{1} $ , ..., _A $ _{ri} $_ }, 1 <= _i_ <= _p_
  
  it is provided that
  
  ![](../../content/crazyb0y:SEQPAR2_1.bmp)  
   where Limit is a given integer.

Let _S $ _{i} $_  be the sum of _B_-components of elements in the _i_th part.

Now I want to minimize the value

max{_S $ _{i} $_ :1 <= _i_ <= p}

Could you tell me the minimum?

## 输入格式

The input contains exactly one test case. The first line of input contains two positive integers N (N <= 50000), Limit (Limit <= 2 $ ^{31} $ -1). Then follow N lines each contains a positive integers pair (_A_, _B_). It's always guaranteed that

 max{_A_ $ _{1} $ , _A_ $ _{2} $ , ..., _A $ _{n} $_ } <= Limit  
![](../../content/crazyb0y:SEQPAR2_2.bmp)

## 输出格式

Output the minimum target value.

## 样例 #1

### 输入

```
4 6
4 3
3 5
2 5
2 4
```

### 输出

```
9
```



---

---
title: "PERIODNI - Periodni"
layout: "post"
diff: 省选/NOI-
pid: SP3734
tag: ['动态规划 DP']
---

# PERIODNI - Periodni

## 题目描述

 [English](/problems/PERIODNI/en/) [Vietnamese](/problems/PERIODNI/vn/)Luka is bored in chemistry class so he is staring at a large periodic table of chemical elements hanging from a wall above the blackboard. To kill time, Luka decided to make his own table completely different from the one in the classroom.

His table consists of N columns, each with some height, aligned at the bottom (see example below). After he draws the table he needs to fill it with elements. He first decided to enter the noble gases of which there are K. Luka must put them in the table so that no two noble gases are close to each other.

Two squares in the table are close to each other if they are in the same column or row, and all squares between them exist. In the example below, the 'a' squares are not close, but the 'b' squares are.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3734/87f0da7d42d32cf3ae36c86030240397dce7472a.png)

Write a program that, given N, K and the heights of the N columns, calculates the total number of ways for Luka to place the noble gases into the table. This number can be large, so output it modulo 1 000 000 007.

## 输入格式

The first line contains the integers N and K separated by a space (1

The next line contains N positive integers, separated by spaces. These are heights of the columns from left to right. The heights will be at most 1 000 000.

## 输出格式

Output the number of ways for Luka to fill his table with noble gases, modulo 1 000 000 007.

## 样例 #1

### 输入

```
5 2
2 3 1 2 4
```

### 输出

```
43
```



---

---
title: "PSTRING - Remove The String"
layout: "post"
diff: 省选/NOI-
pid: SP704
tag: ['动态规划 DP', 'KMP 算法']
---

# PSTRING - Remove The String

## 题目描述

给你两个字符串$X$和$Y$。在$X$中删除最少的字符，使得$Y$不为$X$的子串。

## 输入格式

输入包含多组测试数据。



每个测试数据的第一行为$X$,而第二行为$Y$。（保证$X$的长度小于等于10000,$Y$的长度小于等于1000）

## 输出格式

对于每一组数据，输出一个整数，也就是最少删除字符的数量。

## 样例 #1

### 输入

```
ababaa

aba
```

### 输出

```
1
```



---

---
title: "AMR10B - Regex Edit Distance"
layout: "post"
diff: 省选/NOI-
pid: SP8056
tag: ['动态规划 DP', '有限状态自动机']
---

# AMR10B - Regex Edit Distance

## 题目描述

在这道题目中，我们使用正则表达式来描述一组字符串。题目限定的字母表是 'a' 和 'b'。一个正则表达式 $R$ 满足以下任一条件时即为合法：

1. $R$ 为 "a" 或 "b"
2. $R$ 可以写成 "(R1R2)" 形式，其中 R1 和 R2 都是正则表达式
3. $R$ 可以写成 "(R1|R2)" 形式，其中 R1 和 R2 都是正则表达式
4. $R$ 可以写成 "(R1*)" 形式，其中 R1 是正则表达式

识别的字符串集合由 $R$ 描述如下：

1. 当 $R$ 为 "a" 时，识别的字符串集合为 {a}
2. 当 $R$ 为 "b" 时，识别的字符串集合为 {b}
3. 若 $R$ 的形式是 "(R1R2)"，识别的字符串集合是所有能由 R1 识别的字符串 s1 和由 R2 识别的字符串 s2 连同起来得到的字符串
4. 若 $R$ 的形式是 "(R1|R2)"，识别的字符串集合是 R1 和 R2 识别集合的并集
5. 若 $R$ 的形式是 "(R1\*)" ，识别的字符串集合包括空字符串以及任意多个 R1 识别的字符串连接起来得到的字符串

字符串 s1 和 s2 之间的编辑距离是指将 s1 通过最少的字符插入、删除或替换操作变成 s2 所需的步数。

给定两个正则表达式 $R1$ 和 $R2$，求在所有由 $R1$ 识别的字符串 s1 和由 $R2$ 识别的字符串 s2 之间的最小编辑距离。

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量。接下来是 $T$ 个测试用例。
每个测试用例由两行组成，分别包含一个正则表达式 $R1$ 和 $R2$。每个测试用例之间用一个空行分隔。

## 输出格式

输出 $T$ 行，每行对应一个测试用例的最小编辑距离。

## 说明/提示

- $T \leq 100$
- $1 \leq \text{length}(R1), \text{length}(R2) \leq 50$
- 保证 $R1$ 和 $R2$ 完全符合题目给出的定义。

**样例输入**
```
2
((a|b)*)
(a(b(aa)))

(a((ab)*))
(a(b(((ab)b)b)))
```

**样例输出**
```
0
2
```

**解释**
- 对于第一个测试用例，$R1$ 能识别所有由 'a' 和 'b' 组成的字符串，因此它也识别字符串 "abaa"，这个字符串同样被 $R2$ 识别。
- 对于第二个测试用例，字符串 "aababab" 和 "ababbb" 分别被 $R1$ 和 $R2$ 识别，而它们之间的编辑距离为 2。

 **本翻译由 AI 自动生成**



---



---

# 题号列表

- SP10502 - VIDEO - Video game combos
- SP1748 - SEQPAR2 - Sequence Partitioning II
- SP3734 - PERIODNI - Periodni
- SP704 - PSTRING - Remove The String
- SP8056 - AMR10B - Regex Edit Distance


---

---
title: "STAMMER - Stammering Aliens"
layout: "post"
diff: 省选/NOI-
pid: SP10079
tag: ['哈希 hashing', '后缀数组 SA']
---

# STAMMER - Stammering Aliens

## 题目描述

Dr. Ellie Arroway has established contact with an extraterrestrial civilization. However, all efforts to decode their messages have failed so far because, as luck would have it, they have stumbled upon a race of stuttering aliens! Her team has found out that, in every long enough message, the most important words appear repeated a certain number of times as a sequence of consecutive characters, even in the middle of other words. Furthermore, sometimes they use contractions in an obscure manner. For example, if they need to say _bab_ twice, they might just send the message _babab_, which has been abbreviated because the second _b_ of the first word can be reused as the first _b_ of the second one.

Thus, the message contains possibly overlapping repetitions of the same words over and over again. As a result, Ellie turns to you, S.R. Hadden, for help in identifying the gist of the message.

Given an integer _m_, and a string _s_, representing the message, your task is to find the longest substring of _s_ that appears at least _m_ times. For example, in the message _baaaababababbababbab_, the length-5 word _babab_ is contained 3 times, namely at positions 5, 7 and 12 (where indices start at zero). No substring appearing 3 or more times is longer (see the first example from the sample input). On the other hand, no substring appears 11 times or more (see example 2).

In case there are several solutions, the substring with the rightmost occurrence is preferred (see example 3).

  
  
**Input**

The input contains several test cases. Each test case consists of a line with an integer _m_ (_m_ >= 1), the minimum number of repetitions, followed by a line containing a string _s_ of length between _m_ and 40 000, inclusive. All characters in _s_ are lowercase characters from “a” to “z”. The last test case is denoted by _m_ = 0 and must not be processed.

  
  
**Output**

Print one line of output for each test case. If there is no solution, output none; otherwise, print two integers in a line, separated by a space. The first integer denotes the maximum length of a substring appearing at least _m_ times; the second integer gives the rightmost possible starting position of such a substring.

  
  
**Sample Input**

 ```
<pre class="verbatim">3
baaaababababbababbab
11
baaaababababbababbab
3
cccccc
0
```



---



---

# 题号列表

- SP10079 - STAMMER - Stammering Aliens


---

---
title: "VIDEO - Video game combos"
layout: "post"
diff: 省选/NOI-
pid: SP10502
tag: ['字符串', '动态规划 DP']
---

# VIDEO - Video game combos

## 题目描述

 Bessie is playing a video game! In the game, the three letters 'A', 'B', and 'C' are the only valid buttons. Bessie may press the buttons in any order she likes. However, there are only N distinct combos possible (1 <= N <= 20). Combo i is represented as a string S\_i which has a length between 1 and 15 and contains only the letters 'A', 'B', and 'C'.

 Whenever Bessie presses a combination of letters that matches with a combo, she gets one point for the combo. Combos may overlap with each other or even finish at the same time! For example if N = 3 and the three possible combos are "ABA", "CB", and "ABACB", and Bessie presses "ABACB", she will end with 3 points. Bessie may score points for a single combo more than once.

 Bessie of course wants to earn points as quickly as possible. If she presses exactly K buttons (1 <= K <= 1,000), what is the maximum number of points she can earn?

## 样例 #1

### 输入

```
3 7
ABA
CB
ABACB
```

### 输出

```
4
```



---

---
title: "LCS - Longest Common Substring"
layout: "post"
diff: 省选/NOI-
pid: SP1811
tag: ['字符串', '后缀自动机 SAM', '后缀数组 SA', '构造']
---

# LCS - Longest Common Substring

## 题目描述

A string is finite sequence of characters over a non-empty finite set Σ.

In this problem, Σ is the set of lowercase letters.

Substring, also called factor, is a consecutive sequence of characters occurrences at least once in a string.

Now your task is simple, for two given strings, find the length of the longest common substring of them.

Here common substring means a substring of two or more strings.

## 输入格式

The input contains exactly two lines, each line consists of no more than 250000 lowercase letters, representing a string.

## 输出格式

The length of the longest common substring. If such string doesn't exist, print "0" instead.

## 样例 #1

### 输入

```
alsdfkjfjkdsal
fdjskalajfkdsla
```

### 输出

```
3
```



---

---
title: "LCS2 - Longest Common Substring II"
layout: "post"
diff: 省选/NOI-
pid: SP1812
tag: ['字符串', '后缀自动机 SAM', '后缀数组 SA']
---

# LCS2 - Longest Common Substring II

## 题目描述

题面描述
给定一些字符串，求出它们的最长公共子串

## 输入格式

输入至多$10$ 行，每行包含不超过$100000$ 个的小写字母，表示一个字符串

## 输出格式

一个数，最长公共子串的长度
若不存在最长公共子串，请输出$0$ 。

## 样例 #1

### 输入

```
alsdfkjfjkdsal
fdjskalajfkdsla
aaaajfaaaa
```

### 输出

```
2
```



---

---
title: "WORDRING - Word Rings"
layout: "post"
diff: 省选/NOI-
pid: SP2885
tag: ['字符串', '队列']
---

# WORDRING - Word Rings

## 题目描述

如果字符串A的**结尾两个**字符与字符串B的**开头两个**字符相匹配，我们称A与B能 **“ 相连 ”** ( 注意：A与B能相连，不代表B与A能相连 ) 

 当若干个串首尾 “ 相连 ” 成一个环时，我们称之为一个环串（一个串首尾相连也算） 

 我们希望从给定的全小写字符串中找出一个环串，使这个环串的平均长度最长     
 
```
 intercommunicational
 alkylbenzenesulfonate
 tetraiodophenolphthalein
```

如上例：第一个串能与第二个串相连，第二个串能与第三个串相连，第三个串又能与第一个串相连。按此顺序连接，便形成了一个环串。

长度为 20+21+24=65 ( **首尾重复部分需计算两次** ) ，总共使用了3个串，所以平均长度是 65/3≈21.6666

## 输入格式

多组数据  
 每组数据第一行一个整数n，表示字符串数量   
 接下来n行每行一个长度**小于等于1000**的字符串  
 读入以n=0结束

## 输出格式

若不存在环串，输出"No solution."。否则输出最长的环串平均长度。

Translated by @远藤沙椰

## 样例 #1

### 输入

```
3
intercommunicational
alkylbenzenesulfonate
tetraiodophenolphthalein
0
```

### 输出

```
21.66
```



---



---

# 题号列表

- SP10502 - VIDEO - Video game combos
- SP1811 - LCS - Longest Common Substring
- SP1812 - LCS2 - Longest Common Substring II
- SP2885 - WORDRING - Word Rings


---

---
title: "GSS2 - Can you answer these queries II"
layout: "post"
diff: 省选/NOI-
pid: SP1557
tag: ['线段树', '排序']
---

# GSS2 - Can you answer these queries II

## 题目描述

Being a completist and a simplist, kid Yang Zhe cannot solve but get Wrong Answer from most of the OI problems. And he refuse to write two program of same kind at all. So he always failes in contests.

When having a contest, Yang Zhe looks at the score of every problems first. For the problems of the same score, Yang Zhe will do only one of them. If he's lucky enough, he can get all the scores wanted.

Amber is going to hold a contest in SPOJ. She has made a list of _N_ candidate problems, which fit Yang Zhe very well. So Yang Zhe can solve any problem he want. Amber lined up the problems, began to select. She will select a subsequence of the list as the final problems. Being A girl of great compassion, she'd like to select such a subsequence (can be empty) that Yang Zhe will get the maximal score over all the possible subsequences.

Amber found the subsequence easily after a few minutes. To make things harder, Amber decided that, Yang Zhe can take this contest only if Yang Zhe can answer her _Q_ questions. The question is: if the final problems are limited to be a subsequence of _list_\[_X_.._Y_\] (1 <= _X_ <= _Y_ <= N), what's the maximal possible score Yang Zhe can get?

As we know, Yang Zhe is a bit idiot (so why did he solve the problem with a negative score?), he got Wrong Answer again... Tell him the correct answer!

## 输入格式

- Line 1: integer _N_ (1 <= _N_ <= 100000);
- Line 2: _N_ integers denoting the score of each problem, each of them is a integer in range \[-100000, 100000\];
- Line 3: integer _Q_ (1 <= _Q_ <= 100000);
- Line 3+_i_ (1 <= _i_ <= _Q_): two integers _X_ and _Y_ denoting the _i_th question.

## 输出格式

- Line _i_: a single integer, the answer to the _i_th question.

## 样例 #1

### 输入

```
9
4 -2 -2 3 -1 -4 2 2 -6
3
1 2
1 5
4 9
```

### 输出

```
4
5
3
```



---



---

# 题号列表

- SP1557 - GSS2 - Can you answer these queries II


---

---
title: "COT2 - Count on a tree II"
layout: "post"
diff: 省选/NOI-
pid: SP10707
tag: ['莫队', '深度优先搜索 DFS']
---

# COT2 - Count on a tree II

## 题目描述

You are given a tree with **N** nodes. The tree nodes are numbered from **1** to **N**. Each node has an integer weight.

We will ask you to perform the following operation:

- **u v** : ask for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

## 输入格式

In the first line there are two integers **N** and **M**. (**N** <= 40000, **M** <= 100000)

In the second line there are **N** integers. The i-th integer denotes the weight of the i-th node.

In the next **N-1** lines, each line contains two integers **u** **v**, which describes an edge (**u**, **v**).

In the next **M** lines, each line contains two integers **u** **v**, which means an operation asking for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

## 输出格式

For each operation, print its result.

## 样例 #1

### 输入

```
8 2
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5
7 8
```

### 输出

```
4
4
```



---

---
title: "PT07J - Query on a tree III"
layout: "post"
diff: 省选/NOI-
pid: SP1487
tag: ['深度优先搜索 DFS', '可持久化线段树']
---

# PT07J - Query on a tree III

## 题目描述

你被给定一棵带点权的 $n$ 个点的有根树，点从 $1$ 到 $n$ 编号。

定义查询 $q(x,k)$：寻找以 $x$ 为根的子树中的第 $k$ 小点的编号（从小到大排序第 $k$ 个点）。

保证没有两个相同的点权。

## 样例 #1

### 输入

```
5
1 3 5 2 7
1 2
2 3
1 4
3 5
4
2 3
4 1
3 2
3 2
```

### 输出

```
5
4
5
5
```



---



---

# 题号列表

- SP10707 - COT2 - Count on a tree II
- SP1487 - PT07J - Query on a tree III


---

---
title: "NTHPRIME - Nth Prime"
layout: "post"
diff: 省选/NOI-
pid: SP25024
tag: ['数学', '二分', '素数判断,质数,筛法']
---

# NTHPRIME - Nth Prime

## 题目描述

There is no tedious description for this problem. You are just required to calculate and output the **Nth** prime number.

## 输入格式

The input consists of a single line containing an integer **N,** **N** **10^9**.

## 输出格式

For each input file, output the **Nth** prime number.

## 样例 #1

### 输入

```
4
```

### 输出

```
7
```



---

---
title: "PAGAIN - Prime Again"
layout: "post"
diff: 省选/NOI-
pid: SP3587
tag: ['数学', '枚举']
---

# PAGAIN - Prime Again

## 题目描述

[English](/problems/PAGAIN/en/) [Vietnamese](/problems/PAGAIN/vn/)In this problem, you have to find the nearest prime number smaller than N. (3 <= N <= 2^32)

## 输入格式

The first line contains an integer T specifying the number of test cases. (T <= 10000)

T lines follow, each line contains an integer N.

## 输出格式

For each test case, output the result on one line.

## 样例 #1

### 输入

```
3

5 

10

17
```

### 输出

```
3

7

13
```



---

---
title: "MSKYCODE - Sky Code"
layout: "post"
diff: 省选/NOI-
pid: SP4191
tag: ['数学']
---

# MSKYCODE - Sky Code

## 题目描述

Stancu likes space travels but he is a poor software developer and will never be able to buy his own spacecraft. That is why he is preparing to steal the spacecraft of Petru. There is only one problem – Petru has locked the spacecraft with a sophisticated cryptosystem based on the ID numbers of the stars from the Milky Way Galaxy. For breaking the system Stancu has to check each subset of four stars such that the only common divisor of their numbers is $1$. Nasty, isn’t it?

Fortunately, Stancu has succeeded to limit the number of the interesting stars to $n$ but, any way, the possible subsets of four stars can be too many. Help him to find their number and to decide if there is a chance to break the system.

## 输入格式

In the input file several test cases are given. For each test case on the first line the number $n$ of interesting stars is given $(1 \leq n \leq 10000)$.

The second line of the test case contains the list of ID numbers of the interesting stars, separated by spaces. Each ID is a positive integer which is no greater than $10000$. The input data terminate with the end of file.

## 输出格式

For each test case the program should print one line with the number of subsets with the asked property.

## 样例 #1

### 输入

```
4
2 3 4 5
4
2 4 6 8
7
2 3 4 5 7 6 8
```

### 输出

```
1
0
34
```



---

---
title: "PRIMES2 - Printing some primes (Hard)"
layout: "post"
diff: 省选/NOI-
pid: SP6488
tag: ['数学', '素数判断,质数,筛法', '分块']
---

# PRIMES2 - Printing some primes (Hard)

## 题目描述

The problem statement is really simple (the constraints maybe not). You are to write all primes less than 10^9.

## 输入格式

There is not input.

## 输出格式

To make the problem less output related write out only the 1st, 501st, 1001st, ... 1st mod 500.

## 样例 #1

### 输入

```

```

### 输出

```
2

3581

7927

...

999978527

999988747

999999151
```



---

---
title: "VLATTICE - Visible Lattice Points"
layout: "post"
diff: 省选/NOI-
pid: SP7001
tag: ['数学', '莫比乌斯反演', '整除分块']
---

# VLATTICE - Visible Lattice Points

## 题目描述

Consider a N\*N\*N lattice. One corner is at (0,0,0) and the opposite one is at (N,N,N). How many lattice points are visible from corner at (0,0,0) ? A point X is visible from point Y iff no other lattice point lies on the segment joining X and Y.   
   
Input :   
The first line contains the number of test cases T. The next T lines contain an interger N   
   
Output :   
Output T lines, one corresponding to each test case.   
   
Sample Input :   
3   
1   
2   
5   
   
Sample Output :   
7   
19   
175   
   
Constraints :   
T <= 50   
1 <= N <= 1000000



---



---

# 题号列表

- SP25024 - NTHPRIME - Nth Prime
- SP3587 - PAGAIN - Prime Again
- SP4191 - MSKYCODE - Sky Code
- SP6488 - PRIMES2 - Printing some primes (Hard)
- SP7001 - VLATTICE - Visible Lattice Points


---

---
title: "PT07C - The GbAaY Kingdom"
layout: "post"
diff: 省选/NOI-
pid: SP1479
tag: ['最短路', '生成树', '树的直径']
---

# PT07C - The GbAaY Kingdom

## 题目描述

给定一个 $n$ 个点 $m$ 条边的带权无向图.

现求一生成树,使得任意两结点间最长距离(直径)最短.

## 输入格式

输入的第一行包含两个正整数 $n,m (1 \le n \le 200,n - 1 \le m \le 20000)$ ,代表点数和边数.

接下来 $m$ 行每行三个正整数 $u,v,w$,代表一条从 $u$ 连向 $v$ 边权为 $w$,保证 $u \ne v,1 \le w \le 10^5$

## 输出格式

输出第一行包含一个整数，表示生成树直径.

接下来输出 $n - 1$ 行,每行两个数代表生成树的一条边.

如果有多解,输出任意一个.

### 输入输出样例


#### 输入 #1

```
3 3
1 2 1
2 3 1
1 3 1
```

#### 输出 #1

```
2
1 2
1 3
```

## 样例 #1

### 输入

```
3 3

1 2 1

2 3 1

1 3 1
```

### 输出

```
2

1 2

1 3
```



---

---
title: "INGRED - Ingredients"
layout: "post"
diff: 省选/NOI-
pid: SP18187
tag: ['最短路', '进制', '队列']
---

# INGRED - Ingredients

## 题目描述

 You are given **n** cities with **m** bi-directional roads connecting them and the length of each road. There are two friends living in different cities who wish to collect some ingredients available at different stores to make cake. There are s such stores. They need not come back home after purchasing the ingredients. Petrol is expensive and they would hence like to travel minimum total distance (sum of distance distance traveled by both kids). Help them find out what this distance is.



---



---

# 题号列表

- SP1479 - PT07C - The GbAaY Kingdom
- SP18187 - INGRED - Ingredients


---

---
title: "LCS - Longest Common Substring"
layout: "post"
diff: 省选/NOI-
pid: SP1811
tag: ['字符串', '后缀自动机 SAM', '后缀数组 SA', '构造']
---

# LCS - Longest Common Substring

## 题目描述

A string is finite sequence of characters over a non-empty finite set Σ.

In this problem, Σ is the set of lowercase letters.

Substring, also called factor, is a consecutive sequence of characters occurrences at least once in a string.

Now your task is simple, for two given strings, find the length of the longest common substring of them.

Here common substring means a substring of two or more strings.

## 输入格式

The input contains exactly two lines, each line consists of no more than 250000 lowercase letters, representing a string.

## 输出格式

The length of the longest common substring. If such string doesn't exist, print "0" instead.

## 样例 #1

### 输入

```
alsdfkjfjkdsal
fdjskalajfkdsla
```

### 输出

```
3
```



---

---
title: "SUBST1 - New Distinct Substrings"
layout: "post"
diff: 省选/NOI-
pid: SP705
tag: ['后缀数组 SA', '构造']
---

# SUBST1 - New Distinct Substrings

## 题目描述

 Given a string, we need to find the total number of its distinct substrings.

## 输入格式

 T- number of test cases. T<=20; Each test case consists of one string, whose length is <= 50000

## 输出格式

 For each test case output one number saying the number of distinct substrings.

## 样例 #1

### 输入

```
2
CCCCC
ABABA
```

### 输出

```
5
9
```



---



---

# 题号列表

- SP1811 - LCS - Longest Common Substring
- SP705 - SUBST1 - New Distinct Substrings


---

---
title: "RATAR - Ratar"
layout: "post"
diff: 省选/NOI-
pid: SP16180
tag: ['枚举', '前缀和', '概率论']
---

# RATAR - Ratar

## 题目描述

Unexpected problems with law enforcement have convinced Mirko to take up a less lucrative but less

## 输入格式

The first line of input contains the positive integer N (1

land plot.

Each of the following N lines contains N space-separated numbers Aij (-1000 < Aij < 1000), the income

provided by the respective cell.

## 输出格式

The first and only line of output must contain the total number of plot pairs satisfying the given

condition.

## 样例 #1

### 输入

```
3

1 2 3

2 3 4

3 4 8
```

### 输出

```
7
```



---

---
title: "QTREE6 - Query on a tree VI"
layout: "post"
diff: 省选/NOI-
pid: SP16549
tag: ['枚举', '连通块', '动态树 LCT']
---

# QTREE6 - Query on a tree VI

## 题目描述

给你一棵 $n$ 个点的树，编号 $1\sim n$。每个点可以是黑色，可以是白色。初始时所有点都是黑色。下面有两种操作：

* `0 u`：询问有多少个节点 $v$ 满足路径 $u$ 到 $v$ 上所有节点（包括 $u$）都拥有相同的颜色。

* `1 u`：翻转 $u$ 的颜色。

## 输入格式

第一行一个整数 $n(1\le n\le 10^5)$。

接下来 $n-1$ 行，每行两个整数表示一条边。

接下来一行一个整数 $m(1\le m\le 10^5)$ 表示操作次数。

接下来 $m$ 行，每行两个整数分别表示操作类型和被操作节点。

## 输出格式

对每个询问操作输出相应的结果。

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
1 5
3
0 1
1 1
0 1
```

### 输出

```
5
1
```



---

---
title: "MOD - Power Modulo Inverted"
layout: "post"
diff: 省选/NOI-
pid: SP3105
tag: ['枚举', '分块']
---

# MOD - Power Modulo Inverted

## 题目描述

Given 3 positive integers _x_, _y_ and _z_, you can find _k = x $ ^{y} $ %z_ easily, by fast power-modulo algorithm. Now your task is the inverse of this algorithm. Given 3 positive integers _x_, _z_ and _k_, find the smallest non-negative integer _y_, such that _k%z = x $ ^{y} $ %z_.

## 输入格式

About 600 test cases.

Each test case contains one line with 3 integers _x_, _z_ and _k_.(1<= _x_, _z_, _k_ <=10 $ ^{9} $ )

Input terminates by three zeroes.

## 输出格式

For each test case, output one line with the answer, or "No Solution"(without quotes) if such an integer doesn't exist.

## 样例 #1

### 输入

```
5 58 33
2 4 3
0 0 0
```

### 输出

```
9
No Solution
```



---

---
title: "PAGAIN - Prime Again"
layout: "post"
diff: 省选/NOI-
pid: SP3587
tag: ['数学', '枚举']
---

# PAGAIN - Prime Again

## 题目描述

[English](/problems/PAGAIN/en/) [Vietnamese](/problems/PAGAIN/vn/)In this problem, you have to find the nearest prime number smaller than N. (3 <= N <= 2^32)

## 输入格式

The first line contains an integer T specifying the number of test cases. (T <= 10000)

T lines follow, each line contains an integer N.

## 输出格式

For each test case, output the result on one line.

## 样例 #1

### 输入

```
3

5 

10

17
```

### 输出

```
3

7

13
```



---

---
title: "LPERMUT - Longest Permutation"
layout: "post"
diff: 省选/NOI-
pid: SP744
tag: ['莫队', '枚举', '可持久化线段树']
---

# LPERMUT - Longest Permutation

## 题目描述

You are given a sequence A of n integer numbers (1<=A $ _{i} $ <=n). A subsequence of A has the form A $ _{u} $ , A $ _{u+1} $ ... , A $ _{v} $ (1<=u<=v<=n). We are interested in subsequences that are permutations of 1, 2, .., k (k is the length of the subsequence).

 Your task is to find the longest subsequence of this type.

## 输入格式

- Line 1: n (1<=n<=100000)
- Line 2: n numbers A $ _{1} $ , A $ _{2} $ , ... ,A $ _{n} $ (1<=A $ _{i} $ <=n)

## 输出格式

A single integer that is the length of the longest permutation

## 样例 #1

### 输入

```
5

4 1 3 1 2
```

### 输出

```
3
```



---



---

# 题号列表

- SP16180 - RATAR - Ratar
- SP16549 - QTREE6 - Query on a tree VI
- SP3105 - MOD - Power Modulo Inverted
- SP3587 - PAGAIN - Prime Again
- SP744 - LPERMUT - Longest Permutation


---

---
title: "RATAR - Ratar"
layout: "post"
diff: 省选/NOI-
pid: SP16180
tag: ['枚举', '前缀和', '概率论']
---

# RATAR - Ratar

## 题目描述

Unexpected problems with law enforcement have convinced Mirko to take up a less lucrative but less

## 输入格式

The first line of input contains the positive integer N (1

land plot.

Each of the following N lines contains N space-separated numbers Aij (-1000 < Aij < 1000), the income

provided by the respective cell.

## 输出格式

The first and only line of output must contain the total number of plot pairs satisfying the given

condition.

## 样例 #1

### 输入

```
3

1 2 3

2 3 4

3 4 8
```

### 输出

```
7
```



---

---
title: "RNG - Random Number Generator"
layout: "post"
diff: 省选/NOI-
pid: SP2002
tag: ['计算几何', '容斥原理', '概率论', '微积分']
---

# RNG - Random Number Generator

## 题目描述

LoadingTime got a RNG (_Random Number Generator_) from his classmate several weeks ago. And he spent a lot of time study it. He found that RNG can generate a real number in range \[-**S**,**S**\] by executing following steps. First RNG generates n integer **X** $ _{1} $ ..**X** $ _{n} $ , the sum of which is equal to **S**. Then for each **X** $ _{i} $ , it generates a real number in range \[-**X** $ _{i} $ ,**X** $ _{i} $ \] randomly. The output (a real number) of RNG will be the sum of the **N** generated real numbers. LoadingTime noticed that the distribution of the output was very interesting, and he wanted to know: for given **N** and **X**, what's the probability that the generated number is in range \[**A**,**B**\]. Could you help him?

## 输入格式

The first line contains an integer T representing the number of test cases.

For each test case, the first line contains three integers **N**, **A**, **B**(1 ≤ **N** ≤ 10, -100 ≤ **A** ≤ **B** ≤ 100) In the second line of the test case, you are given **X** $ _{1} $ ...**X** $ _{n} $ (1 ≤ **X** $ _{i} $ ≤ 10).

## 输出格式

For each test case, print a line contains a real number representing the probablity as the problem required. It must be printed with exactly nine decimal places.

## 样例 #1

### 输入

```
5

1 -100 100

10

1 10 90

10

1 -20 5

10

2 -20 5

5 5

5 -5 10

1 2 3 4 5
```

### 输出

```
1.000000000

0.000000000

0.750000000

0.875000000

0.864720052
```



---

---
title: "NORMA2 - Norma"
layout: "post"
diff: 省选/NOI-
pid: SP22343
tag: ['分治', '前缀和', '概率论']
---

# NORMA2 - Norma

## 题目描述

Mirko got an array of integers for his birthday from his grandmother Norma. As any other kid, he was hoping for some money, but got an array. Luckily, in his town there is a pawn shop that buys up arrays. The cost of an array of integers is **min** \* **max** \* **L** kunas, where **min** is the minimal integer in the array, **max** is the maximal and **L** is the array length. Mirko is going to sell a subsequence of consecutive numbers from his array. He calculated the average price of all such subsequences.

In order to check his result, he wants you to do the same. He will be pleased with only the last 9 digits of the sum of all prices, so you don’t need to bother with large and real numbers.

## 输入格式

The first line of input contains an integer N (1

Each of the following N lines contains a member of Mirko’s array. The members of the array will be integers from the interval \[1, 10 $ ^{8} $ \].

## 输出格式

The first and only line of output must contain an integer, the last 9 digits of the required sum from the task. **You don’t need to output** the leading zeroes of that 9-digit integer.

## 样例 #1

### 输入

```
2\n1\n3 
```

### 输出

```
16
```



---

---
title: "QTREE4 - Query on a tree IV"
layout: "post"
diff: 省选/NOI-
pid: SP2666
tag: ['递归', '分治', '动态树 LCT', '概率论']
---

# QTREE4 - Query on a tree IV

## 题目描述

You are given a tree (an acyclic undirected connected graph) with $N$ nodes, and nodes numbered $1,2,3\ldots,N$. Each edge has an integer value assigned to it (note that the value can be negative). Each node has a color, white or black. We define $dist(a, b)$ as the sum of the value of the edges on the path from node $a$ to node $b$.

All the nodes are white initially.

We will ask you to perfrom some instructions of the following form:

- `C a` : change the color of node $a$.(from black to white or from white to black)
- `A` : ask for the maximum $dist(a, b)$, both of node a and node $b$ must be white ($a$ can be equal to $b$). Obviously, as long as there is a white node, the result will alway be non negative.

## 输入格式

- In the first line there is an integer $N$. ($N \leq 100000$)
- In the next $N-1$ lines, the $i$-th line describes the $i$-th edge: a line with three integers $a,b,c$ denotes an edge between $a, b$ of value $c$. ($-10^3 \leq c \leq 10^3$)
- In the next line, there is an integer $Q$ denotes the number of instructions. ($Q \leq 100000$)
- In the next $Q$ lines, each line contains an instruction `C a` or `A`.

## 输出格式

For each `A` operation, write one integer representing its result. If there is no white node in the tree, you should write `They have disappeared.`.

## 样例 #1

### 输入

```
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A
```

### 输出

```
2
2
0
They have disappeared.
```



---



---

# 题号列表

- SP16180 - RATAR - Ratar
- SP2002 - RNG - Random Number Generator
- SP22343 - NORMA2 - Norma
- SP2666 - QTREE4 - Query on a tree IV


---

---
title: "COT2 - Count on a tree II"
layout: "post"
diff: 省选/NOI-
pid: SP10707
tag: ['莫队', '深度优先搜索 DFS']
---

# COT2 - Count on a tree II

## 题目描述

You are given a tree with **N** nodes. The tree nodes are numbered from **1** to **N**. Each node has an integer weight.

We will ask you to perform the following operation:

- **u v** : ask for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

## 输入格式

In the first line there are two integers **N** and **M**. (**N** <= 40000, **M** <= 100000)

In the second line there are **N** integers. The i-th integer denotes the weight of the i-th node.

In the next **N-1** lines, each line contains two integers **u** **v**, which describes an edge (**u**, **v**).

In the next **M** lines, each line contains two integers **u** **v**, which means an operation asking for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

## 输出格式

For each operation, print its result.

## 样例 #1

### 输入

```
8 2
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5
7 8
```

### 输出

```
4
4
```



---

---
title: "PT07J - Query on a tree III"
layout: "post"
diff: 省选/NOI-
pid: SP1487
tag: ['深度优先搜索 DFS', '可持久化线段树']
---

# PT07J - Query on a tree III

## 题目描述

你被给定一棵带点权的 $n$ 个点的有根树，点从 $1$ 到 $n$ 编号。

定义查询 $q(x,k)$：寻找以 $x$ 为根的子树中的第 $k$ 小点的编号（从小到大排序第 $k$ 个点）。

保证没有两个相同的点权。

## 样例 #1

### 输入

```
5
1 3 5 2 7
1 2
2 3
1 4
3 5
4
2 3
4 1
3 2
3 2
```

### 输出

```
5
4
5
5
```



---



---

# 题号列表

- SP10707 - COT2 - Count on a tree II
- SP1487 - PT07J - Query on a tree III


---

---
title: "PT07C - The GbAaY Kingdom"
layout: "post"
diff: 省选/NOI-
pid: SP1479
tag: ['最短路', '生成树', '树的直径']
---

# PT07C - The GbAaY Kingdom

## 题目描述

给定一个 $n$ 个点 $m$ 条边的带权无向图.

现求一生成树,使得任意两结点间最长距离(直径)最短.

## 输入格式

输入的第一行包含两个正整数 $n,m (1 \le n \le 200,n - 1 \le m \le 20000)$ ,代表点数和边数.

接下来 $m$ 行每行三个正整数 $u,v,w$,代表一条从 $u$ 连向 $v$ 边权为 $w$,保证 $u \ne v,1 \le w \le 10^5$

## 输出格式

输出第一行包含一个整数，表示生成树直径.

接下来输出 $n - 1$ 行,每行两个数代表生成树的一条边.

如果有多解,输出任意一个.

### 输入输出样例


#### 输入 #1

```
3 3
1 2 1
2 3 1
1 3 1
```

#### 输出 #1

```
2
1 2
1 3
```

## 样例 #1

### 输入

```
3 3

1 2 1

2 3 1

1 3 1
```

### 输出

```
2

1 2

1 3
```



---



---

# 题号列表

- SP1479 - PT07C - The GbAaY Kingdom


---

---
title: "SUMPRIM2 - Sum of primes (reverse mode)"
layout: "post"
diff: 省选/NOI-
pid: SP18932
tag: ['二分', '数论', '素数判断,质数,筛法', '其它技巧']
---

# SUMPRIM2 - Sum of primes (reverse mode)

## 题目描述

XerK had prepared his new problem with some sums of primes up to some bounds. His results are well here, but he forgot the bounds. Your task is to find which was the last prime in the sum. This problem is extremely simple, but you have to be extremely fast.

## 输入格式

The lonely line of input contains an integer **_S_**.

## 输出格式

You have to print the last prime **_P_** such that **_sum(prime from 2 to P) = S_**.



---

---
title: "NTHPRIME - Nth Prime"
layout: "post"
diff: 省选/NOI-
pid: SP25024
tag: ['数学', '二分', '素数判断,质数,筛法']
---

# NTHPRIME - Nth Prime

## 题目描述

There is no tedious description for this problem. You are just required to calculate and output the **Nth** prime number.

## 输入格式

The input consists of a single line containing an integer **N,** **N** **10^9**.

## 输出格式

For each input file, output the **Nth** prime number.

## 样例 #1

### 输入

```
4
```

### 输出

```
7
```



---

---
title: "PRIMES2 - Printing some primes (Hard)"
layout: "post"
diff: 省选/NOI-
pid: SP6488
tag: ['数学', '素数判断,质数,筛法', '分块']
---

# PRIMES2 - Printing some primes (Hard)

## 题目描述

The problem statement is really simple (the constraints maybe not). You are to write all primes less than 10^9.

## 输入格式

There is not input.

## 输出格式

To make the problem less output related write out only the 1st, 501st, 1001st, ... 1st mod 500.

## 样例 #1

### 输入

```

```

### 输出

```
2

3581

7927

...

999978527

999988747

999999151
```



---



---

# 题号列表

- SP18932 - SUMPRIM2 - Sum of primes (reverse mode)
- SP25024 - NTHPRIME - Nth Prime
- SP6488 - PRIMES2 - Printing some primes (Hard)


---

---
title: "SUMPRIM2 - Sum of primes (reverse mode)"
layout: "post"
diff: 省选/NOI-
pid: SP18932
tag: ['二分', '数论', '素数判断,质数,筛法', '其它技巧']
---

# SUMPRIM2 - Sum of primes (reverse mode)

## 题目描述

XerK had prepared his new problem with some sums of primes up to some bounds. His results are well here, but he forgot the bounds. Your task is to find which was the last prime in the sum. This problem is extremely simple, but you have to be extremely fast.

## 输入格式

The lonely line of input contains an integer **_S_**.

## 输出格式

You have to print the last prime **_P_** such that **_sum(prime from 2 to P) = S_**.



---

---
title: "NTHPRIME - Nth Prime"
layout: "post"
diff: 省选/NOI-
pid: SP25024
tag: ['数学', '二分', '素数判断,质数,筛法']
---

# NTHPRIME - Nth Prime

## 题目描述

There is no tedious description for this problem. You are just required to calculate and output the **Nth** prime number.

## 输入格式

The input consists of a single line containing an integer **N,** **N** **10^9**.

## 输出格式

For each input file, output the **Nth** prime number.

## 样例 #1

### 输入

```
4
```

### 输出

```
7
```



---

---
title: "PRIMES2 - Printing some primes (Hard)"
layout: "post"
diff: 省选/NOI-
pid: SP6488
tag: ['数学', '素数判断,质数,筛法', '分块']
---

# PRIMES2 - Printing some primes (Hard)

## 题目描述

The problem statement is really simple (the constraints maybe not). You are to write all primes less than 10^9.

## 输入格式

There is not input.

## 输出格式

To make the problem less output related write out only the 1st, 501st, 1001st, ... 1st mod 500.

## 样例 #1

### 输入

```

```

### 输出

```
2

3581

7927

...

999978527

999988747

999999151
```



---



---

# 题号列表

- SP18932 - SUMPRIM2 - Sum of primes (reverse mode)
- SP25024 - NTHPRIME - Nth Prime
- SP6488 - PRIMES2 - Printing some primes (Hard)


---

---
title: "COT - Count on a tree"
layout: "post"
diff: 省选/NOI-
pid: SP10628
tag: ['可持久化线段树']
---

# COT - Count on a tree

## 题目描述

# 本题必须使用 C++98 提交

给你一棵有n个结点的树，节点编号为1~n。

每个节点都有一个权值。              

要求执行以下操作：

U V K：求从节点u到节点v的第k小权值。

## 输入格式

第一行有两个整数n和m（n，m≤100000）
第二行有n个整数。
第i个整数表示第i个节点的权值。              

接下来的n-1行中，每行包含两个整数u v，表示u和v之间有一条边。              

接下来的m行，每行包含三个整数U V K，进行一次操作。

## 输出格式

对于每个操作，输出结果。

## 样例 #1

### 输入

```
8 5
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5 1
2 5 2
2 5 3
2 5 4
7 8 2 
```

### 输出

```
2
8
9
105
7 
```



---

---
title: "TTM - To the moon"
layout: "post"
diff: 省选/NOI-
pid: SP11470
tag: ['线段树', '可持久化线段树', '可持久化']
---

# TTM - To the moon

## 题目描述

一个长度为 $N$ 的数组 $\{A\}$，$4$ 种操作 ：

- `C l r d`：区间 $[l,r]$ 中的数都加 $d$ ，同时当前的时间戳加 $1$。

- `Q l r`：查询当前时间戳区间 $[l,r]$ 中所有数的和 。

- `H l r t`：查询时间戳 $t$ 区间 $[l,r]$ 的和 。

- `B t`：将当前时间戳置为 $t$ 。

　　所有操作均合法 。

ps：刚开始时时间戳为 $0$

## 输出格式

数据保证：$1\le N,M\le 10^5$，$|A_i|\le 10^9$，$1\le l \le r \le N$，$|d|\le10^4$。在刚开始没有进行操作的情况下时间戳为 $0$，且保证 `B` 操作不会访问到未来的时间戳。

由 @bztMinamoto @yzy1 提供翻译

## 样例 #1

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4
```

### 输出

```
4
55
9
15

```

## 样例 #2

### 输入

```
2 4
0 0
C 1 1 1
C 2 2 -1
Q 1 2
H 1 2 1
```

### 输出

```
0
1
```



---

---
title: "GOT - Gao on a tree"
layout: "post"
diff: 省选/NOI-
pid: SP11985
tag: ['线段树', '树链剖分']
---

# GOT - Gao on a tree

## 题目描述

 There's a tree, with each vertex assigned a number. For each query (a, b, c), you are asked whether there is a vertex on the path from a to b, which is assigned number c?

## 输入格式

There are multiple cases, end by EOF.

For each case, the first line contains n (n <= 100000) and m (m <= 200000), representing the number of vertexes (numbered from 1 to n) and the number of queries.

Then n integers follows, representing the number assigned to the i-th vertex.

Then n-1 lines, each of which contains a edge of the tree.

Then m lines, each of which contains three integers a, b and c (0 <= c <= n), representing a query.

## 输出格式

You should output "`Find`" or "`NotFind`" for every query on one line.

Output a blank line AFTER every case.

## 样例 #1

### 输入

```
5 5

1 2 3 4 5

1 2

1 3

3 4

3 5

2 3 4

2 4 3

2 4 5

4 5 1

4 5 3
```

### 输出

```
NotFind

Find

NotFind

NotFind

Find
```



---

---
title: "PT07J - Query on a tree III"
layout: "post"
diff: 省选/NOI-
pid: SP1487
tag: ['深度优先搜索 DFS', '可持久化线段树']
---

# PT07J - Query on a tree III

## 题目描述

你被给定一棵带点权的 $n$ 个点的有根树，点从 $1$ 到 $n$ 编号。

定义查询 $q(x,k)$：寻找以 $x$ 为根的子树中的第 $k$ 小点的编号（从小到大排序第 $k$ 个点）。

保证没有两个相同的点权。

## 样例 #1

### 输入

```
5
1 3 5 2 7
1 2
2 3
1 4
3 5
4
2 3
4 1
3 2
3 2
```

### 输出

```
5
4
5
5
```



---

---
title: "GSS2 - Can you answer these queries II"
layout: "post"
diff: 省选/NOI-
pid: SP1557
tag: ['线段树', '排序']
---

# GSS2 - Can you answer these queries II

## 题目描述

Being a completist and a simplist, kid Yang Zhe cannot solve but get Wrong Answer from most of the OI problems. And he refuse to write two program of same kind at all. So he always failes in contests.

When having a contest, Yang Zhe looks at the score of every problems first. For the problems of the same score, Yang Zhe will do only one of them. If he's lucky enough, he can get all the scores wanted.

Amber is going to hold a contest in SPOJ. She has made a list of _N_ candidate problems, which fit Yang Zhe very well. So Yang Zhe can solve any problem he want. Amber lined up the problems, began to select. She will select a subsequence of the list as the final problems. Being A girl of great compassion, she'd like to select such a subsequence (can be empty) that Yang Zhe will get the maximal score over all the possible subsequences.

Amber found the subsequence easily after a few minutes. To make things harder, Amber decided that, Yang Zhe can take this contest only if Yang Zhe can answer her _Q_ questions. The question is: if the final problems are limited to be a subsequence of _list_\[_X_.._Y_\] (1 <= _X_ <= _Y_ <= N), what's the maximal possible score Yang Zhe can get?

As we know, Yang Zhe is a bit idiot (so why did he solve the problem with a negative score?), he got Wrong Answer again... Tell him the correct answer!

## 输入格式

- Line 1: integer _N_ (1 <= _N_ <= 100000);
- Line 2: _N_ integers denoting the score of each problem, each of them is a integer in range \[-100000, 100000\];
- Line 3: integer _Q_ (1 <= _Q_ <= 100000);
- Line 3+_i_ (1 <= _i_ <= _Q_): two integers _X_ and _Y_ denoting the _i_th question.

## 输出格式

- Line _i_: a single integer, the answer to the _i_th question.

## 样例 #1

### 输入

```
9
4 -2 -2 3 -1 -4 2 2 -6
3
1 2
1 5
4 9
```

### 输出

```
4
5
3
```



---

---
title: "SEQPAR2 - Sequence Partitioning II"
layout: "post"
diff: 省选/NOI-
pid: SP1748
tag: ['动态规划 DP', '线段树']
---

# SEQPAR2 - Sequence Partitioning II

## 题目描述

Given a sequence of _N_ ordered pairs of positive integers (_A $ _{i} $_ , _B $ _{i} $_ ), you have to partition it into several contiguous parts. Let _p_ be the number of these parts, whose boundaries are (_l_ $ _{1} $ , _r_ $ _{1} $ ), (_l_ $ _{2} $ , _r_ $ _{2} $ ), ... ,(_l $ _{p} $_ , _r $ _{p} $_ ), which satisfy _l $ _{i} $_ = _r $ _{i-} $_  $ _{1} $ + 1, _l $ _{i} $_ <= _r $ _{i} $_ , _l_ $ _{1} $ = 1, _r $ _{p} $_ = _n_. The parts themselves also satisfy the following restrictions:

1. For any two pairs (_A $ _{p} $_ , _B $ _{p} $_ ), (_A $ _{q} $_ , _B $ _{q} $_ ), where (_A $ _{p} $_ , _B $ _{p} $_ ) is belongs to the _T $ _{p} $_ th part and (_A $ _{q} $_ , _B $ _{q} $_ ) the _T $ _{q} $_ th part. If _T $ _{p} $_ < _T $ _{q} $_ , then _B $ _{p} $_ > _A $ _{q} $_ .
2. Let _M $ _{i} $_  be the maximum _A_-component of elements in the _i_th part, say
  
  _M $ _{i} $_  = max {_A $ _{li} $_ , _A $ _{li+} $_  $ _{1} $ , ..., _A $ _{ri} $_ }, 1 <= _i_ <= _p_
  
  it is provided that
  
  ![](../../content/crazyb0y:SEQPAR2_1.bmp)  
   where Limit is a given integer.

Let _S $ _{i} $_  be the sum of _B_-components of elements in the _i_th part.

Now I want to minimize the value

max{_S $ _{i} $_ :1 <= _i_ <= p}

Could you tell me the minimum?

## 输入格式

The input contains exactly one test case. The first line of input contains two positive integers N (N <= 50000), Limit (Limit <= 2 $ ^{31} $ -1). Then follow N lines each contains a positive integers pair (_A_, _B_). It's always guaranteed that

 max{_A_ $ _{1} $ , _A_ $ _{2} $ , ..., _A $ _{n} $_ } <= Limit  
![](../../content/crazyb0y:SEQPAR2_2.bmp)

## 输出格式

Output the minimum target value.

## 样例 #1

### 输入

```
4 6
4 3
3 5
2 5
2 4
```

### 输出

```
9
```



---

---
title: "GSS5 - Can you answer these queries V"
layout: "post"
diff: 省选/NOI-
pid: SP2916
tag: ['线段树', '前缀和']
---

# GSS5 - Can you answer these queries V

## 题目描述

 You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| <= 10000 , 1 <= N <= 10000 ). A query is defined as follows: Query(x1,y1,x2,y2) = Max { A\[i\]+A\[i+1\]+...+A\[j\] ; x1 <= i <= y1 , x2 <= j <= y2 and x1 <= x2 , y1 <= y2 }. Given M queries (1 <= M <= 10000), your program must output the results of these queries.

## 输入格式

 The first line of the input consist of the number of tests cases <= 5. Each case consist of the integer N and the sequence A. Then the integer M. M lines follow, contains 4 numbers x1, y1, x2 y2.

## 输出格式

 Your program should output the results of the M queries for each test case, one query per line.

## 样例 #1

### 输入

```
2
6 3 -2 1 -4 5 2
2
1 1 2 3
1 3 2 5
1 1
1
1 1 1 1
```

### 输出

```
2
3
1
```



---

---
title: "GSS7 - Can you answer these queries VII"
layout: "post"
diff: 省选/NOI-
pid: SP6779
tag: ['线段树', '树链剖分', '动态树 LCT']
---

# GSS7 - Can you answer these queries VII

## 题目描述

给定一棵树，有$N(N \le 100000)$个节点，每一个节点都有一个权值$x_i (|x_i| \le 10000)$

你需要执行$Q (Q \le 100000)$次操作：

1. `1 a b` 查询`(a,b)`这条链上的最大子段和，可以为空（即输出$0$）
2. `2 a b c` 将`(a,b)`这条链上的所有点权变为`c` $(|c| <= 10000)$

## 输入格式

第一行一个整数$N$

接下来一行有$N$个整数表示$x_i$

接下来$N-1$行，每行两个整数$u,v$表示$u$和$v$之间有一条边相连

接下来一行一个整数$Q$

之后有$Q$行，每行诸如`1 a b`或者`2 a b c`

## 输出格式

对于每一个询问，输出答案

# 输入样例

``` plain
5
-3 -2 1 2 3
1 2
2 3
1 4
4 5
3
1 2 5
2 3 4 2
1 2 5
```

# 输出样例

``` plain
5
9
```

## 样例 #1

### 输入

```
5
-3 -2 1 2 3
1 2
2 3
1 4
4 5
3
1 2 5
2 3 4 2
1 2 5
```

### 输出

```
5
9
```



---

---
title: "LPERMUT - Longest Permutation"
layout: "post"
diff: 省选/NOI-
pid: SP744
tag: ['莫队', '枚举', '可持久化线段树']
---

# LPERMUT - Longest Permutation

## 题目描述

You are given a sequence A of n integer numbers (1<=A $ _{i} $ <=n). A subsequence of A has the form A $ _{u} $ , A $ _{u+1} $ ... , A $ _{v} $ (1<=u<=v<=n). We are interested in subsequences that are permutations of 1, 2, .., k (k is the length of the subsequence).

 Your task is to find the longest subsequence of this type.

## 输入格式

- Line 1: n (1<=n<=100000)
- Line 2: n numbers A $ _{1} $ , A $ _{2} $ , ... ,A $ _{n} $ (1<=A $ _{i} $ <=n)

## 输出格式

A single integer that is the length of the longest permutation

## 样例 #1

### 输入

```
5

4 1 3 1 2
```

### 输出

```
3
```



---



---

# 题号列表

- SP10628 - COT - Count on a tree
- SP11470 - TTM - To the moon
- SP11985 - GOT - Gao on a tree
- SP1487 - PT07J - Query on a tree III
- SP1557 - GSS2 - Can you answer these queries II
- SP1748 - SEQPAR2 - Sequence Partitioning II
- SP2916 - GSS5 - Can you answer these queries V
- SP6779 - GSS7 - Can you answer these queries VII
- SP744 - LPERMUT - Longest Permutation


---

---
title: "SUMPRIM2 - Sum of primes (reverse mode)"
layout: "post"
diff: 省选/NOI-
pid: SP18932
tag: ['二分', '数论', '素数判断,质数,筛法', '其它技巧']
---

# SUMPRIM2 - Sum of primes (reverse mode)

## 题目描述

XerK had prepared his new problem with some sums of primes up to some bounds. His results are well here, but he forgot the bounds. Your task is to find which was the last prime in the sum. This problem is extremely simple, but you have to be extremely fast.

## 输入格式

The lonely line of input contains an integer **_S_**.

## 输出格式

You have to print the last prime **_P_** such that **_sum(prime from 2 to P) = S_**.



---

---
title: "NTHPRIME - Nth Prime"
layout: "post"
diff: 省选/NOI-
pid: SP25024
tag: ['数学', '二分', '素数判断,质数,筛法']
---

# NTHPRIME - Nth Prime

## 题目描述

There is no tedious description for this problem. You are just required to calculate and output the **Nth** prime number.

## 输入格式

The input consists of a single line containing an integer **N,** **N** **10^9**.

## 输出格式

For each input file, output the **Nth** prime number.

## 样例 #1

### 输入

```
4
```

### 输出

```
7
```



---

---
title: "PRIMES2 - Printing some primes (Hard)"
layout: "post"
diff: 省选/NOI-
pid: SP6488
tag: ['数学', '素数判断,质数,筛法', '分块']
---

# PRIMES2 - Printing some primes (Hard)

## 题目描述

The problem statement is really simple (the constraints maybe not). You are to write all primes less than 10^9.

## 输入格式

There is not input.

## 输出格式

To make the problem less output related write out only the 1st, 501st, 1001st, ... 1st mod 500.

## 样例 #1

### 输入

```

```

### 输出

```
2

3581

7927

...

999978527

999988747

999999151
```



---



---

# 题号列表

- SP18932 - SUMPRIM2 - Sum of primes (reverse mode)
- SP25024 - NTHPRIME - Nth Prime
- SP6488 - PRIMES2 - Printing some primes (Hard)


---

---
title: "BOXES - Boxes"
layout: "post"
diff: 省选/NOI-
pid: SP371
tag: ['贪心', 'POI（波兰）', '网络流', '费用流', '1996']
---

# BOXES - Boxes

## 题目描述

### 题目大意
$n$ 个盒子围成一圈（$1\le n\le 1000$）。 第 $i$ 个盒子初始时有 $a_i$ 个小球，小球数量总和满足 $\displaystyle\sum_{i=1}^{n}{a_i \leq n}$。  
每次可以把一个小球从一个盒子移到相邻的两个盒子之一。求最少需要移动多少次，使得每个盒子中小球的个数不超过 $1$。

## 输入格式

输入包含多组数据。

第一行 $1$ 个数 $t$（$1\le t\le 20$），表示数据组数。

接下来每组数据包含 $2$ 行，第一行包括一个数 $n$ ，表示盒子数量，第二行包含 $n$ 个非负整数 $a_i$ ，第 $i$ 个数表示第 $i$ 个盒子里初始的小球数量。

## 输出格式

输出包含 $t$ 行。

对于输入的每组数据，你需要输出 $1$ 行，包含 $1$ 个正整数，表示最少移动次数。

## 样例 #1

### 输入

```
1
12
0 0 2 4 3 1 0 0 0 0 0 1
```

### 输出

```
19
```



---



---

# 题号列表

- SP371 - BOXES - Boxes


---

---
title: "INGRED - Ingredients"
layout: "post"
diff: 省选/NOI-
pid: SP18187
tag: ['最短路', '进制', '队列']
---

# INGRED - Ingredients

## 题目描述

 You are given **n** cities with **m** bi-directional roads connecting them and the length of each road. There are two friends living in different cities who wish to collect some ingredients available at different stores to make cake. There are s such stores. They need not come back home after purchasing the ingredients. Petrol is expensive and they would hence like to travel minimum total distance (sum of distance distance traveled by both kids). Help them find out what this distance is.



---



---

# 题号列表

- SP18187 - INGRED - Ingredients


---

---
title: "QTREE4 - Query on a tree IV"
layout: "post"
diff: 省选/NOI-
pid: SP2666
tag: ['递归', '分治', '动态树 LCT', '概率论']
---

# QTREE4 - Query on a tree IV

## 题目描述

You are given a tree (an acyclic undirected connected graph) with $N$ nodes, and nodes numbered $1,2,3\ldots,N$. Each edge has an integer value assigned to it (note that the value can be negative). Each node has a color, white or black. We define $dist(a, b)$ as the sum of the value of the edges on the path from node $a$ to node $b$.

All the nodes are white initially.

We will ask you to perfrom some instructions of the following form:

- `C a` : change the color of node $a$.(from black to white or from white to black)
- `A` : ask for the maximum $dist(a, b)$, both of node a and node $b$ must be white ($a$ can be equal to $b$). Obviously, as long as there is a white node, the result will alway be non negative.

## 输入格式

- In the first line there is an integer $N$. ($N \leq 100000$)
- In the next $N-1$ lines, the $i$-th line describes the $i$-th edge: a line with three integers $a,b,c$ denotes an edge between $a, b$ of value $c$. ($-10^3 \leq c \leq 10^3$)
- In the next line, there is an integer $Q$ denotes the number of instructions. ($Q \leq 100000$)
- In the next $Q$ lines, each line contains an instruction `C a` or `A`.

## 输出格式

For each `A` operation, write one integer representing its result. If there is no white node in the tree, you should write `They have disappeared.`.

## 样例 #1

### 输入

```
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A
```

### 输出

```
2
2
0
They have disappeared.
```



---



---

# 题号列表

- SP2666 - QTREE4 - Query on a tree IV


---

---
title: "INGRED - Ingredients"
layout: "post"
diff: 省选/NOI-
pid: SP18187
tag: ['最短路', '进制', '队列']
---

# INGRED - Ingredients

## 题目描述

 You are given **n** cities with **m** bi-directional roads connecting them and the length of each road. There are two friends living in different cities who wish to collect some ingredients available at different stores to make cake. There are s such stores. They need not come back home after purchasing the ingredients. Petrol is expensive and they would hence like to travel minimum total distance (sum of distance distance traveled by both kids). Help them find out what this distance is.



---

---
title: "WORDRING - Word Rings"
layout: "post"
diff: 省选/NOI-
pid: SP2885
tag: ['字符串', '队列']
---

# WORDRING - Word Rings

## 题目描述

如果字符串A的**结尾两个**字符与字符串B的**开头两个**字符相匹配，我们称A与B能 **“ 相连 ”** ( 注意：A与B能相连，不代表B与A能相连 ) 

 当若干个串首尾 “ 相连 ” 成一个环时，我们称之为一个环串（一个串首尾相连也算） 

 我们希望从给定的全小写字符串中找出一个环串，使这个环串的平均长度最长     
 
```
 intercommunicational
 alkylbenzenesulfonate
 tetraiodophenolphthalein
```

如上例：第一个串能与第二个串相连，第二个串能与第三个串相连，第三个串又能与第一个串相连。按此顺序连接，便形成了一个环串。

长度为 20+21+24=65 ( **首尾重复部分需计算两次** ) ，总共使用了3个串，所以平均长度是 65/3≈21.6666

## 输入格式

多组数据  
 每组数据第一行一个整数n，表示字符串数量   
 接下来n行每行一个长度**小于等于1000**的字符串  
 读入以n=0结束

## 输出格式

若不存在环串，输出"No solution."。否则输出最长的环串平均长度。

Translated by @远藤沙椰

## 样例 #1

### 输入

```
3
intercommunicational
alkylbenzenesulfonate
tetraiodophenolphthalein
0
```

### 输出

```
21.66
```



---

---
title: "C2CRNI - Crni"
layout: "post"
diff: 省选/NOI-
pid: SP7884
tag: ['单调队列', '容斥原理']
---

# C2CRNI - Crni

## 题目描述

尽管Mirko找到了所有最有趣的游乐设施，但他的热情仍然没有消失，于是他无聊地打开了方格笔记本，开始给方块涂色，于是一个新的甚至更难的问题浮现了出来。

现在有个$N\times N$的矩阵，每个格子被填充了黑色或者白色。如果这个矩形的一个子矩形内的所有格子均为黑色并且由至少两个格子组成，则这个子矩形称为**黑矩形**。

![](https://cdn.luogu.com.cn/upload/image_hosting/hidn0vrp.png)

左图框选了两个不是黑矩形的子矩形。1号子矩形不是黑矩形，因为它包含了白色的格子；2号子矩形不是黑矩形，因为它仅包含一个格子。右图框选了三个有效的黑矩形。

现在Mirko想知道找出两个不相交的黑矩形的方案的总数目。由于结果可能非常大，因此你的答案需要对$10007$取模。

## 输入格式

第一行为一个整数$N$

接下来$N$行每行$N$个字母表示矩阵每个格子的颜色。`C`为黑色，`B`为白色。

## 输出格式

不相交黑矩形对的数量对$10007$取模后的值。

### 样例

#### 样例#1
输入：
```
2
CC
CC
```

输出：
```
2
```

#### 样例#2
输入：
```
3
CCB
CCB
CBB
```
输出：
```
5
```

#### 样例#3

输入：
```
5
BCCBB
BBCBB
BCCBB
BBBBB
CCBBB
```

输出：
```
8
```

## 样例 #1

### 输入

```
\n2 \nCC \nCC\n\n
```

### 输出

```
\n2\n\nInput:\n3 \nCCB \nCCB \nCBB\n\nOutput:\n5\n\nInput:\n5\nBCCBB\nBBCBB\nBCCBB\nBBBBB\nCCBBB\n\nOutput:\n8
```



---



---

# 题号列表

- SP18187 - INGRED - Ingredients
- SP2885 - WORDRING - Word Rings
- SP7884 - C2CRNI - Crni


---

