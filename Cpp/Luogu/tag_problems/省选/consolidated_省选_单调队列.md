---
title: "[NOI2011] NOI 嘉年华"
layout: "post"
diff: 省选/NOI-
pid: P1973
tag: ['动态规划 DP', '2011', '单调队列', 'NOI', 'Special Judge']
---
# [NOI2011] NOI 嘉年华
## 题目描述

NOI2011 在吉林大学开始啦！为了迎接来自全国各地最优秀的信息学选手，吉林大学决定举办两场盛大的 NOI 嘉年华活动，分在两个不同的地点举办。每个嘉年华可能包含很多个活动，而每个活动只能在一个嘉年华中举办。

现在嘉年华活动的组织者小安一共收到了 $n$ 个活动的举办申请，其中第 $i$ 个活动的起始时间为 $S_i$，活动的持续时间为 $T_i$。这些活动都可以安排到任意一个嘉年华的会场，也可以不安排。

小安通过广泛的调查发现，如果某个时刻，两个嘉年华会场同时有活动在进行（不包括活动的开始瞬间和结束瞬间），那么有的选手就会纠结于到底去哪个会场，从而变得不开心。所以，为了避免这样不开心的事情发生，小安要求不能有两个活动在两个会场同时进行（同一会场内的活动可以任意进行）。

另外，可以想象，如果某一个嘉年华会场的活动太少，那么这个嘉年华的吸引力就会不足，容易导致场面冷清。所以小安希望通过合理的安排，使得活动相对较少的嘉年华的活动数量最大。

此外，有一些活动非常有意义，小安希望能举办，他希望知道，如果第 $i$ 个活动必须举办（可以安排在两场嘉年华中的任何一个），活动相对较少的嘉年华的活动数量的最大值。

## 输入格式

输入的第一行包含一个整数 $n$，表示申请的活动个数。

接下来 $n$ 行描述所有活动，其中第 $i$ 行包含两个整数 $S_i,T_i$，表示第 $i$ 个活动从时刻 $S_i$ 开始，持续 $T_i$ 的时间。

## 输出格式

输出的第一行包含一个整数，表示在没有任何限制的情况下，活动较少的嘉年华的活动数的最大值。

接下来 $n$ 行每行一个整数，其中第 $i$ 行的整数表示在必须选择第 $i$ 个活动的前提下，活动较少的嘉年华的活动数的最大值。

## 样例

### 样例输入 #1
```
5 
8 2 
1 5 
5 3 
3 2 
5 3 
```
### 样例输出 #1
```
2 
2 
1 
2 
2 
2 
```
## 提示

### 样例解释

在没有任何限制的情况下，最优安排可以在一个嘉年华安排活动 $1, 4$，而在另一个嘉年华安排活动 $3, 5$，活动 $2$ 不安排。

对于 $10\%$ 的数据，$1\leq n\leq 10$。

对于 $30\%$ 的数据，$1\leq n\leq 40$。

对于 $100\%$ 的数据，$1\leq n\leq 200$，$0\leq S_i\leq 10^9$，$1\leq T_i\leq 10^9$。

如果输出格式不正确（比如输出不足 $n+1$ 行），得 $0$ 分；

如果输出文件第一行不正确，而且后 $n$ 行至少有一行不正确，得 $0$ 分；

如果输出文件第一行正确，但后 $n$ 行至少有一行不正确，得 $4$ 分；

如果输出文件第一行不正确，但后 $n$ 行均正确，得 $6$ 分；

如果输出文件中的 $n+1$ 行均正确，得 $10$ 分。



---

---
title: "[USACO13JAN] Seating G"
layout: "post"
diff: 省选/NOI-
pid: P3071
tag: ['2013', 'USACO', '单调队列', '离散化', '队列']
---
# [USACO13JAN] Seating G
## 题目描述

To earn some extra money, the cows have opened a restaurant in their barn specializing in milkshakes.  The restaurant has N seats (1 <= N <= 500,000) in a row. Initially, they are all empty.

Throughout the day, there are M different events that happen in sequence at the restaurant (1 <= M <= 300,000).  The two types of events that can happen are:

1. A party of size p arrives (1 <= p <= N). Bessie wants to seat the party in a contiguous block of p empty seats. If this is possible, she does so in the lowest position possible in the list of seats.  If it is impossible, the party is turned away.

2. A range [a,b] is given (1 <= a <= b <= N), and everybody in that range of seats leaves.

Please help Bessie count the total number of parties that are turned away over the course of the day.

有一排n个座位，m次操作。A操作：将a名客人安置到最左的连续a个空位中，没有则不操作。L操作：[a,b]的客人离开。

求A操作的失败次数。

## 输入格式

\* Line 1: Two space-separated integers, N and M.

\* Lines 2..M+1: Each line describes a single event.  It is either a line of the form "A p" (meaning a party of size p arrives) or "L a b" (meaning that all cows in the range [a, b] leave).

## 输出格式

\* Line 1: The number of parties that are turned away.

## 样例

### 样例输入 #1
```
10 4 
A 6 
L 2 4 
A 5 
A 2 

```
### 样例输出 #1
```
1 

```
## 提示

There are 10 seats, and 4 events.  First, a party of 6 cows arrives.  Then all cows in seats 2..4 depart.  Next, a party of 5 arrives, followed by a party of 2.


Party #3 is turned away.  All other parties are seated.



---

---
title: "[USACO13OPEN] Photo G"
layout: "post"
diff: 省选/NOI-
pid: P3084
tag: ['2013', '线段树', 'USACO', '单调队列', '差分约束', '队列']
---
# [USACO13OPEN] Photo G
## 题目描述

Farmer John has decided to assemble a panoramic photo of a lineup of his N cows (1 <= N <= 200,000), which, as always, are conveniently numbered from 1..N.  Accordingly, he snapped M (1 <= M <= 100,000) photos, each covering a contiguous range of cows: photo i contains cows a\_i through b\_i inclusive.  The photos collectively may not necessarily cover every single cow.

After taking his photos, FJ notices a very interesting phenomenon: each photo he took contains exactly one cow with spots!  FJ was aware that he had some number of spotted cows in his herd, but he had never actually counted them.  Based on his photos, please determine the maximum possible number of spotted cows that could exist in his herd.  Output -1 if there is no possible assignment of spots to cows consistent with FJ's photographic results.

农夫约翰决定给站在一条线上的N(1 <= N <= 200,000)头奶牛制作一张全家福照片，N头奶牛编号1到N。


于是约翰拍摄了M(1 <= M <= 100,000)张照片，每张照片都覆盖了连续一段奶牛：第i张照片中包含了编号a\_i 到 b\_i的奶牛。但是这些照片不一定把每一只奶牛都拍了进去。


在拍完照片后，约翰发现了一个有趣的事情：每张照片中都**有且仅有**一只身上带有斑点的奶牛。约翰意识到他的牛群中有一些斑点奶牛，但他从来没有统计过它们的数量。 根据照片，请你帮约翰估算在他的牛群中最多可能有多少只斑点奶牛。如果无解，输出“-1”。


Input
## 输入格式

\* Line 1: Two integers N and M.

\* Lines 2..M+1: Line i+1 contains a\_i and b\_i.

## 输出格式

\* Line 1: The maximum possible number of spotted cows on FJ's farm, or -1 if there is no possible solution.

## 样例

### 样例输入 #1
```
5 3 
1 4 
2 5 
3 4 

```
### 样例输出 #1
```
1 

```
## 提示

There are 5 cows and 3 photos.  The first photo contains cows 1 through 4, etc.


From the last photo, we know that either cow 3 or cow 4 must be spotted. By choosing either of these, we satisfy the first two photos as well.



---

---
title: "[HNOI2008] 玩具装箱"
layout: "post"
diff: 省选/NOI-
pid: P3195
tag: ['动态规划 DP', '2008', '单调队列', '湖南', '斜率优化']
---
# [HNOI2008] 玩具装箱
## 题目描述

P 教授要去看奥运，但是他舍不下他的玩具，于是他决定把所有的玩具运到北京。他使用自己的压缩器进行压缩，其可以将任意物品变成一堆，再放到一种特殊的一维容器中。

P 教授有编号为 $1 \cdots n$ 的 $n$ 件玩具，第 $i$ 件玩具经过压缩后的一维长度为 $C_i$。

为了方便整理，P 教授要求：

- 在一个一维容器中的玩具编号是连续的。

- 同时如果一个一维容器中有多个玩具，那么两件玩具之间要加入一个单位长度的填充物。形式地说，如果将第 $i$ 件玩具到第 $j$ 个玩具放到一个容器中，那么容器的长度将为 $x=j-i+\sum\limits_{k=i}^{j}C_k$。

制作容器的费用与容器的长度有关，根据教授研究，如果容器长度为 $x$，其制作费用为 $(x-L)^2$。其中 $L$ 是一个常量。P 教授不关心容器的数目，他可以制作出任意长度的容器，甚至超过 $L$。但他希望所有容器的总费用最小。
## 输入格式

第一行有两个整数，用一个空格隔开，分别代表 $n$ 和 $L$。

第 $2$ 到 第 $(n + 1)$ 行，每行一个整数，第 $(i + 1)$ 行的整数代表第 $i$ 件玩具的长度 $C_i$。
## 输出格式

输出一行一个整数，代表所有容器的总费用最小是多少。
## 样例

### 样例输入 #1
```
5 4
3
4
2
1
4
```
### 样例输出 #1
```
1
```
## 提示

对于全部的测试点，$1 \leq n \leq 5 \times 10^4$，$1 \leq L \leq 10^7$，$1 \leq C_i \leq 10^7$。


---

---
title: "[POI 2006] ZAB-Frogs"
layout: "post"
diff: 省选/NOI-
pid: P3438
tag: ['2006', '二分', '单调队列', 'POI（波兰）', '广度优先搜索 BFS']
---
# [POI 2006] ZAB-Frogs
## 题目描述

A scourge of frogs destroying all the crop has started in Byteotia. A farmer named Byteasar has decided to fight the vermin with peculiar "scarefrogs", that he has set up at certain points of his field. While moving from one place to another, every frog tries to keep as far of them as possible, i.e. maximizes the distance to the closest scarefrog.

The field that belongs to Byteasar has rectangular shape. The frogs leap in directions parallel to the field's sides and their leaps are unitary (of length 1). The scarefrogs-distance, for a given frog's route, is the minimum of all distances from all scarefrogs at all inter-leap-points of the route.

Byteasar already knows the most common starting and destination points of the frogs' routes, therefore he experiments with various deployments of the scarefrogs. He asks you for help, namely he would like you to write a programme that calculates the maximum (over all routes) scarefrogs-distance for a given deployment of scarefrogs - which we call in short the frogshold distance.

TaskWrite a programme that:

reads from the standard input the size of the field, the coordinates of the screfrogs and the source and target position of a frog,determines the frogshold distance (the maximum scarefrogs-distance a frog may achieve while still being able to reach the target point)writes the square of this number to the standard output.

给定一个网格图，其中有一些坏点，要求使起点到终点的路径上的所有点到离该点最近的坏点的最小距离距离最大，求这个最大值。

## 输入格式

The first line of the input contains two integers: $w_x$ and $w_y$ separated by a single space - the breadth and length of the field ($2 \le w_x, w_y \le 1000$). The second line of the input contains four integers: $p_x$, $p_y$, $k_x$ and $k_y$ separated by single spaces; $(p_x, p_y)$ is the initial position of the frog, $(k_x, k_y)$is the target (final) position of the frog ($1 \le p_x, k_x \le w_x$, $1 \le p_y, k_y \le w_y$). The third line of the standard input contains one integer $n$ - these are the coordinates of the ith scarefrog ($1 \le n \le w_x \cdot w_y$). No two scarefrogs occupy the same position and none of them is at the point $(p_x, p_y)$ nor $(k_x, k_y)$.

## 输出格式

In the first and only line of the standard output one integer should be written, namely the square of the frogshold distance. If the frog cannot avoid leaping directly on some scarefrog the result is 0.

## 样例

### 样例输入 #1
```
5 5
1 1 5 5
2
3 3
4 2
```
### 样例输出 #1
```
4
```


---

---
title: "[POI 2008] BBB-BBB"
layout: "post"
diff: 省选/NOI-
pid: P3470
tag: ['2008', '单调队列', 'POI（波兰）']
---
# [POI 2008] BBB-BBB
## 题目描述

Byteasar has an account at The Byteotian Bit Bank (BBB in short).

At the beginning there were $p$ and at the end $q$ bythalers in the account.

Each transaction was either a deposit or a withdrawal of one bythaler.

The account's balance was never negative.

A bank teller has prepared a bank statement: a strip of paper with a sequence of pluses and minuses in it   (a plus denotes a deposit while minus a withdrawal of one bythaler).

Soon it turned out, that some transactions were not entered correctly.

The bank teller cannot print another statement, but has to correct the   one already printed instead.

The statement needs not be consistent with the truth, it will suffice if the sequence of transactions satisfies the following two conditions:

the final balance is consistent with the initial balance and the sequence of transactions in the statement, according to the sequence of transactions in the statement, the account's balance was never negative.

You are to calculate the minimum amount of time the bank teller needs to   correct the bank statement.

The bank teller can:

- in $x$ seconds turn an arbitrarily chosen transaction to its opposite, or 
- in $y$ seconds remove the last transaction and put it at the beginning of the statement.

If, for example, $p=2,q=3$, then `--++-+-++-+-+` is a correct   statement.

On the other hand the statement `---++++++` is incorrect, because the account's balance would become negative after the third transaction, and furthermore the final balance should be 3, not 5.

It can be, however, corrected by turning the second to last symbol to its opposite and placing the last transaction at the beginning of the statement.

### Task

Write a programme that:

- reads the current bank statement for Byteasar's account (a sequence of pluses and minuses) as well as the numbers $p,q,x$ and $y$ from the standard input.
- writes out to the standard output the minimum number of seconds needed to correct the statement in a way such that the initial and final balance are consistent and that the balance is never negative.

## 输入格式

The first line contains 5 integers $n,p,q,x$ and $y\ (1\le n\le 1\ 000\ 000$, $0\le p,q\le 1\ 000\ 000$, $1\le x,y\le 1000$), separated by single spaces and denoting respectively:

the number of transactions done by Byteasar, initial and final account     balance and the number of seconds needed to perform a single turn     (change of sign) and move of transaction to the beginning.

The second line contains a sequence of ![](http://main.edu.pl/images/OI15/bbb-en-tex.18.png) signs (each a plus     or a minus), with no spaces in-between.

## 输出格式

The first and last output line should contain one integer,     the minimum number of seconds needed to correct the statement. If no     corrections are necessary, the number is zero.

You may assume that a proper sequence of modifications exists for each     test data.

## 样例

### 样例输入 #1
```
9 2 3 2 1
---++++++

```
### 样例输出 #1
```
3

```
## 题目翻译

给定一个由 $+1$ 和 $-1$ 构成的长度为 $n$ 的序列，提供两种操作：

1. 将某一位取反，花销为 $x$；
2. 将最后一位移动到第一位，花销为 $y$。

要求最终 $p+S_n=q$，且 $p+S_i≥0\ (1≤i≤n)$，求最小花销。其中 $S_i=a_1+a_2+\cdots+a_i$。


---

---
title: "[POI 2008] KUP-Plot purchase"
layout: "post"
diff: 省选/NOI-
pid: P3474
tag: ['贪心', '2008', '单调队列', 'POI（波兰）', 'Special Judge']
---
# [POI 2008] KUP-Plot purchase
## 题目描述

Byteasar is going to buy an industrial plot.

His fortune is estimated at $k$ bythalers and this is exactly the amount    Byteasar would like to spend on the parcel.

Finding a parcel worth exactly $k$ bythalers, however, is not an easy task.

For this reason Byteasar is ready to buy a more expensive plot.

He considers taking out a loan. The Byteotian Credit Bank will grant him    a loan of up to $k$ bythalers. Thus, Byteasar can spend no more than $2k$    bythalers on the parcel and he would like to spend no less than $k$ bythalers.

The area in which Byteasar wants to buy his parcel is a square with side    length of $n$ metres. The current landlords have set up various prices per square metre. Byteasar has spoken to each one of them and has then prepared a price map    of the area. The map depicts the price of every metre by metre square. Clearly, there    are $n^2$ such squares. Now is the time to find the dream parcel. It has to be rectangular and consist of whole unit squares. Byteasar has already started looking for the plot on the map,    but after many hours he was still unable to find a suitable one. Be a chap and help him!

<Task> 

Write a programme that:

reads the numbers $k$ and $n$ from the standard input,  along with the price map of the area, determines a parcel with price in the interval $[k,2k]$ or states that no such parcel exists, writes out the result to the standard output.


## 输入格式

The first line of the standard input contains two integers, $k$ and $n$, separated by a single space, $1\le k\le 10^9$, $1\le n\le 2000$.

Each of the following $n$ lines contains $n$ non-negative integers, separated by single spaces.

$i^\mathrm{th}$ number in the line no. $j+1$ denotes the price of unit square with coordinates $(i,j)$.

The price of one square metre does not exceed $2{,}000{,}000{,}000$ bythalers.

## 输出格式

If no plot with price in the interval $[k,2k]$ exists, your programme should output exactly one line with word `NIE` (NO in Polish).

Otherwise it should print out one line with four positive integers $x_1,y_1,x_2,y_2$ separated by single spaces and denoting the rectangle's      coordinates.

$(x_1,y_1)$ denotes the upper left rectangle corner, while $(x_2,y_2)$ the lower right corner.

Then it consists of the squares: $\{x,y\mid x_1\le x\le x_2,y_1\le y\le y_2\}$.

The sum $c$ of prices of the squares forming up this rectangle should satisfy the inequality $k\le c\le 2k$.

If more than one rectangular parcel satisfies this condition, pick one arbitrarily.

## 样例

### 样例输入 #1
```
8 4
1 2 1 3
25 1 2 1
4 20 3 3
3 30 12 2
```
### 样例输出 #1
```
2 1 4 2
```
## 提示


给定 $k,n$ 和 $n\times n$ 的矩阵，求一个子矩形满足权值和在 $[k,2k]$ 之间。

$n<2000$，$1\le k\le10^9$，每个价格都是不大于$2 \times 10^9$ 的非负整数。

感谢@cn：苏卿念 提供的spj


---

---
title: "[POI 2014] BAR-Salad Bar"
layout: "post"
diff: 省选/NOI-
pid: P3564
tag: ['2014', '二分', '单调队列', 'POI（波兰）']
---
# [POI 2014] BAR-Salad Bar
## 题目描述

Bytea went to a salad bar.

There are $n$ fruits one next to another on the bar counter.

Specifically, these are apples and oranges.

Bytea can pick any contiguous part of the line of fruits for her salad.

The fruits she chooses will be added to the salad either from left to right or from right to left.

As Bytea loves oranges, she requires that throughout the salad making process, the number of oranges    in it should always be no smaller than the number of apples, regardless of whether these are added %    from left to right or from right to left.

Help Bytea out by writing a program that will find the longest contiguous part of the line of fruits    that satisfies her requirements.

有一个长度为n的字符串，每一位只会是p或j。求一个最长子串，使得不管是从左往右还是从右往左取，都保证每时每刻已取出的p的个数不小于j的个数。

## 输入格式

The first line of the standard input contains a single integer $n$ ($1\le n\le 1\ 000\ 000$), denoting the number of fruits.

The next line contains a string of $n$ characters $a_1,a_2,\cdots,a_n$ ($a_i\in \{j,p\}$).

These stand for Polish names of apples and oranges: jab\l{ka} and pomara\'ncze).

Consequently, if $a_i=j$, then the $i$-th fruit in a line is an apple,      and otherwise it is an orange.

## 输出格式

The first and only line of the standard output should contain a single integer equal to the number of fruits in the longest contiguous part of the line that satisfies Bytea's requirements.

Note that it could be the case that $0$ is the correct result.

## 样例

### 样例输入 #1
```
6
jpjppj

```
### 样例输出 #1
```
4

```
## 提示

有一个长度为n的字符串，每一位只会是p或j。求一个最长子串，使得不管是从左往右还是从右往左取，都保证每时每刻已取出的p的个数不小于j的个数。



---

---
title: "[POI 2015] POD"
layout: "post"
diff: 省选/NOI-
pid: P3587
tag: ['2015', '单调队列', 'POI（波兰）', '哈希 hashing']
---
# [POI 2015] POD
## 题目描述

长度为 $n$ 的一串项链，每颗珠子是 $k$ 种颜色之一。第 $i$ 颗与第 $i-1,i+1$ 颗珠子相邻，第 $n$ 颗与第 $1$ 颗也相邻。

切两刀，把项链断成两条链。要求每种颜色的珠子只能出现在其中一条链中。

求方案数量（保证至少存在一种），以及切成的两段长度之差绝对值的最小值。
## 输入格式

第一行 $n,k$（$2\leq k\leq n\leq 10^6$）。颜色从 $1$ 到 $k$ 标号。

接下来 $n$ 个数，按顺序表示每颗珠子的颜色。（保证 $k$ 种颜色各出现至少一次）。 
## 输出格式

一行两个整数：方案数量，和长度差的最小值。
## 样例

### 样例输入 #1
```
9 5
2 5 3 2 2 4 1 1 3
```
### 样例输出 #1
```
4 3
```
## 提示

**【样例解释】**

四种方法中较短的一条分别是 $(5),(4),(1,1),(4,1,1)$。相差最小值 $6-3=3$。 

----

原题名称：Podział naszyjnika。 


---

---
title: "[APIO2010] 特别行动队"
layout: "post"
diff: 省选/NOI-
pid: P3628
tag: ['动态规划 DP', '2010', '单调队列', 'APIO', '斜率优化', '前缀和', '队列']
---
# [APIO2010] 特别行动队
## 题目描述

你有一支由 $n$ 名预备役士兵组成的部队，士兵从 $1$ 到 $n$ 编号，你要将他们拆分成若干特别行动队调入战场。出于默契的考虑，同一支特别行动队中队员的编号**应该连续**，即为形如 $(i, i + 1, \cdots i + k)$的序列。所有的队员都应该属于且仅属于一支特别行动队。

编号为 $i$ 的士兵的初始战斗力为 $x_i$ ，一支特别行动队的初始战斗力 $X$ 为队内士兵初始战斗力之和，即 $X = x_i + x_{i+1} + \cdots + x_{i+k}$。

通过长期的观察，你总结出对于一支初始战斗力为 $X$ 的特别行动队，其修正战斗力 $X'= aX^2+bX+c$，其中 $a,~b,~c$ 是已知的系数（$a < 0$）。 作为部队统帅，现在你要为这支部队进行编队，使得所有特别行动队的修正战斗力之和最大。试求出这个最大和。
## 输入格式

输入的第一行是一个整数 $n$，代表士兵的人数。

输入的第二行有三个用空格隔开的整数，依次代表 $a,~b,~c$，即修正战斗力的系数。

输入的第三行有 $n$ 个用空格隔开的整数，第 $i$ 个整数代表编号为 $i$ 的士兵的初始战斗力 $x_i$。
## 输出格式

输出一行一个整数，代表最大的所有特别行动队战斗力之和。
## 样例

### 样例输入 #1
```
4 
-1 10 -20 
2 2 3 4 
```
### 样例输出 #1
```
9
```
## 提示

#### 样例输入输出 $1$ 解释

你有 $4$ 名士兵，$x_1 = 2,~x_2 = 2,~x_3 = 3,~x_4=4$。修正战斗力公式中的参数为  $a = -1,~b = 10,~c = -20$。

此时，最佳方案是将士兵组成 $3$ 个特别行动队：第一队包含士兵 $1$ 和士兵 $2$，第二队包含士兵 $3$，第三队包含士兵 $4$。特别行动队的初始战斗力分别为 $4,~3,~4$，修正后的战斗力分别为 $-4^2 + 10 \times 4 -20 = 4$，$-3^2 + 10 \times 3 - 20 = 1$，$-4^2 + 10 \times 4 -20 = 4$。修正后的战斗力和为 $4 + 1 + 4 = 9$，没有其它方案能使修正后的战斗力和更大。


#### 数据范围与约定

对于 $20\%$ 的数据，$n \leq 10^3$。

对于 $50\%$ 的数据，$n \leq 10^4$

对于 $100\%$ 的数据，$1 \leq n \leq 10^6$，$-5 \leq a \leq -1$，$-10^7 \leq b \leq 10^7$，$-10^7 \leq c \leq 10^7$，$1 \leq x_i \leq 100$。


---

---
title: "[BJOI2017] 树的难题"
layout: "post"
diff: 省选/NOI-
pid: P3714
tag: ['2017', '各省省选', '点分治', '单调队列', '分治', '深度优先搜索 DFS']
---
# [BJOI2017] 树的难题
## 题目描述

给你一棵 $n$ 个点的无根树。

树上的每条边具有颜色。一共有 $m$ 种颜色，编号为 $1$ 到 $m$，第 $i$ 种颜色的权值为 $c_i$。

对于一条树上的简单路径，路径上经过的所有边按顺序组成一个颜色序列，序列可以划分成若干个相同颜色段。定义路径权值为颜色序列上每个同颜色段的颜色权值之和。

请你计算，经过边数在 $l$ 到 $r$ 之间的所有简单路径中，路径权值的最大值。
## 输入格式

第一行，四个整数 $n, m, l, r$。

第二行，$m$ 个整数 $c_1, c_2, \ldots, c_m$，由空格隔开，依次表示每个颜色的权值。

接下来 $n-1$ 行，每行三个整数 $u, v, c$，表示点 $u$ 和点 $v$ 之间有一条颜色为 $c$ 的边。
## 输出格式

输出一行，一个整数，表示答案。

## 样例

### 样例输入 #1
```
5 3 1 4
-1 -5 -2
1 2 1
1 3 1
2 4 2
2 5 3
```
### 样例输出 #1
```
-1
```
### 样例输入 #2
```
8 4 3 4
-7 9 6 1
1 2 1
1 3 2
1 4 1
2 5 1
5 6 2
3 7 1
3 8 3
```
### 样例输出 #2
```
11
```
## 提示

### 样例解释 1
颜色权值均为负，最优路径为 $(1, 2)$ 或 $(1, 3)$。

### 样例解释 2
最优路径为 $(3, 1, 2, 5, 6)$，其颜色序列为 $(2, 1, 1, 2)$。

### 数据范围
| 测试点编号 | $n$ | $m$ | 特殊限制 |
|-|-|-|-|
| $1$ | $=10^3$ | $\le n$ | 无特殊限制 |
| $2$ | $=10^4$ | $=2$ | 无特殊限制 |
| $3$ | $=10^5$ | $\le n$ | 所有点的度数不超过 $2$ |
| $4$ | $=2\times10^5$ | $\le n$ | 所有点的度数不超过 $2$ |
| $5$ | $=10^5$ | $=10$ | $l=1$，$r=n-1$ |
| $6$ | $=2\times10^5$ | $\le n$ | $l=1$，$r=n-1$ |
| $7$ | $=10^5$ | $=50$ | 无特殊限制 |
| $8$ | $=10^5$ | $\le n$ | 无特殊限制 |
| $9$ | $=2\times 10^5$ | $=100$ | 无特殊限制 |
| $10$ | $=2\times 10^5$ | $\le n$ | 无特殊限制 |

对于 $100\%$ 的数据，$1 \leq n, m \leq 2 \times 10^5$，$1 \leq l \leq r \leq n$，$\mid c_i \mid \leq 10^4$。保证树上至少存在一条经过边数在 $l$ 到 $r$ 之间的路径。


---

---
title: "高速公路（疑似错题）"
layout: "post"
diff: 省选/NOI-
pid: P3994
tag: ['单调队列', 'O2优化', '斜率优化', '队列']
---
# 高速公路（疑似错题）
## 题目描述

C 国拥有一张四通八达的高速公路树。

C 国有 $n$ 个城市，城市之间由一共 $n-1$ 条高速公路连接。除了首都 $1$ 号城市，每个城市都有一家本地的客运公司，可以发车前往全国各地。你可以把它认作以 $1$ 为根的树。两城市的距离定义为它们之间简单路径的长度。

假设有一个人要从 $i$ 号城市坐车出发前往与其距离为 $D$ 的 $j$ 号城市，那么他要花费 $P_i \times D+Q_i$ 元。由于距离首都越远，国家的监管就越松，所以距离首都越远，客运公司的 $P_i$ 越大，如果 $i$ 号城市是 $j$ 号城市的某个祖先，那么一定存在 $P_i \leq P_j$。

小 T 成为了国家统计局的调查人员，他需要对现在的高速路网进行一次调查，了解从其他每一个城市到达首都 $1$ 号城市所花费的金钱。

因为可能出现多转车（或不转车）的抵达首都的方法，所以人工计算这个结果是十分复杂的。大宁非常的懒，所以请你编写一个程序解决它。
## 输入格式

第 $1$ 行包含一个整数 $n$，表示城市的个数。

第 $2$ 到 $n$ 行，每行描述一个除首都之外的城市。其中第 $i$ 行包含 $4$ 个整数 $F_i,S_i,P_i,Q_i$，分别表示 $i$ 号城市的父亲城市，它到父亲城市高速公路的长度，以及乘车价格的两个参数。
## 输出格式

输出包含 $n-1$ 行，每行包含一个整数。

其中第 $i$ 行表示从 $i+1$ 号城市出发，到达首都最少的乘车费用。
## 样例

### 样例输入 #1
```
6
1 9 3 0
1 17 1 9
1 1 1 6
4 13 2 15
4 9 2 4

```
### 样例输出 #1
```
27
26
7
43
24

```
## 提示

#### 数据规模与约定

- 对于前 $40\%$ 的数据 $n \leq 1000$。
- 对于另外 $20\%$ 的数据，$F_i=i-1$
- 对于所有的数据，$1 \leq n \leq 10^6$，$0 \leq Pi,Qi \lt 2^{31}$，保证结果不会大于 $2^{63}-1$。


---

---
title: "[SDOI2016] 征途"
layout: "post"
diff: 省选/NOI-
pid: P4072
tag: ['2016', '各省省选', '单调队列', '山东', 'O2优化', '斜率优化', '前缀和', '凸包']
---
# [SDOI2016] 征途
## 题目描述

Pine 开始了从 $S$ 地到 $T$ 地的征途。

从 $S$ 地到 $T$ 地的路可以划分成 $n$ 段，相邻两段路的分界点设有休息站。

Pine 计划用 $m$ 天到达 $T$ 地。除第 $m$ 天外，每一天晚上 Pine 都必须在休息站过夜。所以，一段路必须在同一天中走完。

Pine 希望每一天走的路长度尽可能相近，所以他希望每一天走的路的长度的方差尽可能小。

帮助 Pine 求出最小方差是多少。

设方差是 $v$，可以证明，$v\times m^2$ 是一个整数。为了避免精度误差，输出结果时输出 $v\times m^2$。
## 输入格式

第一行两个数 $n, m$。

第二行 $n$ 个数，表示 $n$ 段路的长度。
## 输出格式

一个数，最小方差乘以 $m^2$ 后的值。
## 样例

### 样例输入 #1
```
5 2
1 2 5 8 6
```
### 样例输出 #1
```
36
```
## 提示

### 数据范围及约定

- 对于 $30\%$ 的数据，$1 \le n \le 10$；
- 对于 $60\%$ 的数据，$1 \le n \le 100$；
- 对于 $100\%$ 的数据，$1 \le n \le 3000$。

保证从 $S$ 到 $T$ 的总路程不超过 $3\times 10^4$。

$2 \leq m \leq n+1$，每段路的长度为不超过 $3 \times 10^4$ 的**正整数**。


---

---
title: "[USACO18JAN] Lifeguards P"
layout: "post"
diff: 省选/NOI-
pid: P4182
tag: ['动态规划 DP', '2018', 'USACO', '单调队列', '枚举', '队列']
---
# [USACO18JAN] Lifeguards P
## 题目描述

Farmer John has opened a swimming pool for his cows, figuring it will help them relax and produce more milk.

To ensure safety, he hires $N$ cows as lifeguards, each of which has a shift that covers some contiguous interval of time during the day. For simplicity, the pool is open from time $0$ until time $10^9$ on a daily basis, so each shift can be described by two integers, giving the time at which a cow starts and ends her shift. For example, a lifeguard starting at time $t = 4$ and ending at time $t = 7$ covers three units of time (note that the endpoints are "points" in time).


Unfortunately, Farmer John hired $K$ more lifeguards than he has the funds to support. Given that he must fire exactly $K$ lifeguards, what is the maximum amount of time that can still be covered by the shifts of the remaining lifeguards? An interval of time is covered if at least one lifeguard is present.

## 输入格式

The first line of input contains $N$ and $K$ ($K \leq N \leq 100,000, 1 \leq K \leq 100$). Each of the next $N$ lines describes a lifeguard in terms of two integers in the range $0 \ldots 10^9$, giving the starting and ending point of a lifeguard's shift. All such endpoints are distinct. Shifts of different lifeguards might overlap.

## 输出格式

Please write a single number, giving the maximum amount of time that can still be covered if Farmer John fires $K$ lifeguards.

## 样例

### 样例输入 #1
```
3 2
1 8
7 15
2 14
```
### 样例输出 #1
```
12

```
## 提示

In this example, FJ should fire the lifeguards covering $1 \ldots 8$ and $7 \ldots 15$.


## 题目翻译

### 题目描述

Farmer John 为他的奶牛们开设了一个游泳池，认为这将帮助它们放松并产更多的奶。

为了确保安全，他雇佣了 $N$ 头奶牛作为救生员，每头奶牛的班次覆盖一天中的某个连续时间段。为简单起见，游泳池每天从时间 $0$ 开放到时间 $10^9$，因此每个班次可以用两个整数描述，分别表示奶牛开始和结束其班次的时间。例如，一头救生员从时间 $t = 4$ 开始到时间 $t = 7$ 结束，覆盖了 $3$ 个单位的时间（注意端点表示时间点）。

不幸的是，Farmer John 多雇佣了 $K$ 名救生员，超出了他的资金支持范围。鉴于他必须解雇恰好 $K$ 名救生员，剩下的救生员的班次能够覆盖的最长时间是多少？如果至少有一名救生员在场，则某个时间段被视为被覆盖。

### 输入格式

输入的第一行包含 $N$ 和 $K$（$K \leq N \leq 100,000$，$1 \leq K \leq 100$）。接下来的 $N$ 行每行描述一名救生员，用两个范围在 $0 \ldots 10^9$ 的整数表示该救生员班次的开始和结束时间。所有端点都是唯一的。不同救生员的班次可能会重叠。

### 输出格式

请输出一个数字，表示如果 Farmer John 解雇 $K$ 名救生员后，剩下的救生员的班次能够覆盖的最长时间。

### 提示

在这个例子中，Farmer John 应该解雇覆盖 $1 \ldots 8$ 和 $7 \ldots 15$ 的救生员。


---

---
title: "[Code+#3] 寻找车位"
layout: "post"
diff: 省选/NOI-
pid: P4259
tag: ['线段树', '单调队列', '枚举', 'Code+']
---
# [Code+#3] 寻找车位
## 题目描述

access_globe 有一个巨大的停车场，这个停车场有 $n$ 行，每行有 $m$ 个车位。为了美观，access_globe 在建立这个停车场时，规定这个停车场必须是长条形的，即 $n\ge m$。每个车位都是一个正方形的区域。

最近，access_globe 正在为抽不到 Missing Poster 而苦恼，因此他请你帮他维护这个停车场。你需要支持两个个事件：

- 一辆车停到某一个车位中，或一辆车从某个车位开走
- 查询一个矩形区域内最大的只包含空车位的正方形区域

如果你能帮 access_globe 高效地解决这个问题，access_globe 一定会好好奖励你的。

## 输入格式

第一行包含三个正整数 $n$、$m$、$q$，表示停车场的大小和事件的个数；

接下来 $n$ 行，每行 $m$ 个 0 或 1 的数，如果第 $i$ 行第 $j$ 的数**为 $1$**，则表示第 $i$ 行第 $j$ 列的车位**为空**，否则表示这个车位**非空**；

接下来 $q$ 行，每行表示一个事件，有以下两种形式：

- $0$ $x$ $y$ ：第 $x$ 行第 $y$ 列的车位的停车情况改变，即若此事件发生前这个车位为空，则此事件后这个车位非空，否则此事件后这个车位为空，保证 $1\le x\le n$，$1\le y\le m$
- $1$ $l$ $s$ $r$ $t$：询问以 $(l, s)$ 和 $(r,t)$ 为对角的矩形区域中，最大的全空正方形区域的边长，保证 $1\le l\le r\le n$，$1\le s\le t\le m$

## 输出格式

对每个询问输出一行一个整数，表示该询问的全空正方形的边长。
## 样例

### 样例输入 #1
```
5 4 10
1 1 1 0
1 1 1 1
1 1 0 1
1 0 1 0
1 1 0 0
1 1 1 5 4
1 3 1 3 1
1 3 3 3 3
1 2 3 5 3
0 2 2
1 1 4 2 4
1 1 3 3 3
0 5 1
1 2 3 2 4
1 1 2 2 4

```
### 样例输出 #1
```
2
1
0
1
1
1
1
1
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/15114.png)

所有子任务的分值均等分布。

对于所有数据，保证 $n\times m\le4\times 10^6$，$q\le 2000$。

Credit：https://www.luogu.org/discuss/show?postid=35727


---

---
title: "[CEOI 2004] 锯木厂选址"
layout: "post"
diff: 省选/NOI-
pid: P4360
tag: ['模拟', '动态规划 DP', '2004', '单调队列', 'CEOI（中欧）', '模拟退火', '斜率优化']
---
# [CEOI 2004] 锯木厂选址
## 题目描述

从山顶上到山底下沿着一条直线种植了 $n$ 棵老树。当地的政府决定把他们砍下来。为了不浪费任何一棵木材，树被砍倒后要运送到锯木厂。 

木材只能朝山下运。山脚下有一个锯木厂。另外两个锯木厂将新修建在山路上。你必须决定在哪里修建这两个锯木厂，使得运输的费用总和最小。假定运输每公斤木材每米需要一分钱。 

你的任务是编写一个程序，从输入文件中读入树的个数和他们的重量与位置，计算最小运输费用。
## 输入格式

输入的第一行为一个正整数 $n$ ——树的个数 $(2\leq n\leq 20000)$。树从山顶到山脚按照 $1,2,\dots,n$ 标号。 

接下来 $n$ 行，每行有两个正整数（用空格分开）。 

第 $i+1$ 行含有：$w_i$ ——第 $i$ 棵树的重量（公斤为单位）和 $d_i$——第 $i$ 棵树和第 $i+1$ 棵树之间的距离， $1\leq w_i\leq 10000,0\leq d_i\leq 10000$。 

最后一颗树的 $d_n$，表示第 $n$ 棵树到山脚的锯木厂的距离。保证所有树运到山脚的锯木厂所需要的费用小于 $2\times 10^9$ 分。
## 输出格式

输出最小的运输费用。
## 样例

### 样例输入 #1
```
9 
1 2 
2 1 
3 3 
1 1 
3 2 
1 6 
2 1 
1 2 
1 1

```
### 样例输出 #1
```
26
```
## 提示

样例图示，黑点为锯木厂

![](https://cdn.luogu.com.cn/upload/pic/16339.png)

本题共有 $13$ 个测试点，每个测试点的数据范围如下

测试点 $1\sim 5$：$n\leq 200$；

测试点 $6\sim7$：$n\leq 1000$；

测试点 $7\sim13$：$2\leq n\leq 20000$；


---

---
title: "[Wind Festival] Iron Man"
layout: "post"
diff: 省选/NOI-
pid: P4744
tag: ['单调队列']
---
# [Wind Festival] Iron Man
## 题目背景

[Midnight - 23:59]

在风筝节上交到了老铁(并不是 Nishikino)，接触了 OI，gyx 全身的热情都被点燃啦！！为了更好地参与到下一届风筝节的工作中去，gyx 准备开始为期一年的学习。

## 题目描述

gyx 想用全部的时间学(tui)OI(fei)!!!

gyx 为了合理的利用所有时间学 OI，他开始规划自己的学习计划。

首先，gyx 的眼里每年有 $n$ 天，因为 gyx 实在是太想学习啦，所以他并没有留下玩耍的时间（每天都全部用来学 OI 或者文化课），gyx 划分天数的原则是，在每一天中，gyx 对 OI 的感兴趣程度相同。但是，未免 gyx 也会因生活琐事而没法静心学习，所以某些天 gyx 对 OI 的兴趣程度有可能是负的。

然后，gyx 开始安排学习 OI 的时间，gyx 统计出他要学习的OI 知识有 $k$ 种。因为 gyx 是一个追求完美的人，他认为对于每一种 OI 知识，知识体系的完整性是必要的，某一个部分的 OI 知识学习过程中一旦停下来会影响自己的学习效果，所以他会用连续的一些天来学习一个部分的知识，期间不能停下来学习文化课，也不会穿插着进行几种知识的学习。

但是注意，gyx 在进行每部分 OI 知识的学习之间可以留出一些时间段用来学文化课。并且，gyx 并不介意各个部分 OI 知识间学习的顺序，因为他对每一部分的 OI 知识兴趣程度是相同的。

现在，gyx 想知道他总共用于学 OI 的日子兴趣值之和是多少，因为 gyx 还没有学习过高级的规划算法，所以 gyx 将他学习计划的规划交给你，你可以选择任意一个小于等于 $n$ 的一个正整数 $i$，使他从第 $i$ 天开始，进行长 $n$ 天的学习（不一定一开始就必须学 OI），但在这一年中他一定要把清单中所有的知识都学完，gyx 相信你一定能给出兴趣值之和最高的方法。


## 输入格式

两个正整数 $n,k$，分别代表 gyx 眼中一年有 $n$ 天，gyx 要学习的知识有 $k$ 种。

接下来一行有 $n$ 个整数，第 $i$ 个数 $a_i$ 代表 gyx 第 $i$ 天对 OI 的兴趣程度。
## 输出格式

输出一个整数，代表他总共学 OI 的所有日子兴趣值之和最大是多少。
## 样例

### 样例输入 #1
```
6 2
2 -4 3 -1 2 3

```
### 样例输出 #1
```
10
```
## 提示

### 样例解释

从第 $3$ 个时间段开始学习，那么他学 OI 的这一年兴趣程度的序列便为：

- $[3,-1,2,3,2,-4]$。

用于学习两个知识的时间段分别是新序列的第 $1$ 个和第 $3,4,5$ 个，于是 $ans=3+(2+3+2)=10$。

### 数据范围

- 对于 $10\%$ 的数据，满足 $k=1$；
- 对于另 $30\%$ 的数据，满足 $k=2$；
- 对于$100\%$ 的数据，满足：$1\le k\le50$，$k\le n\le10^5$，$|a_i|\le 10^4$。


---

---
title: "yyf hates choukapai"
layout: "post"
diff: 省选/NOI-
pid: P4852
tag: ['动态规划 DP', '2018', '单调队列', '洛谷原创', 'Special Judge', '前缀和', '期望', '队列']
---
# yyf hates choukapai
## 题目背景

非酋yyf总是抽不到自己想要的卡，因此还十分讨厌抽卡。但玩sif不可能不抽卡，于是他去请教了一下欧皇dew。dew告诉了他关于抽卡的秘密，然而yyf还是不知道如何让自己欧气尽量地大，于是他找到了你。
## 题目描述

dew告诉yyf，人在抽每张卡时欧气值都是固定的，第 $i$ 张卡的欧气值为 $a_i$ ，而在连抽时，欧气值等于第一张卡的欧气值。

“每次抽卡的欧气之和”指每次单抽的欧气之和加上每次连抽的欧气之和，一次连抽的欧气不加权，只计算一次

yyf想 $c$ 连抽（连续抽 $c$ 张卡） $n$ 次，单抽 $m$ 次，因为一直单抽太累，**yyf不想连续单抽超过 $d$ 次（可以连续单抽恰好 $d$ 次）**。共有 $c*n+m$ 张卡，抽卡的顺序不能改变，每张卡都必须且只能抽一次，只能改变哪几张卡连抽、哪几张卡单抽。那么yyf每次抽卡的欧气之和最多能达到多少，又如何实现呢？
## 输入格式

第 $1$ 行 $4$ 个正整数 $n\ m\ c\ d$

第 $2$ 行 $c*n+m$ 个正整数，其中第 $i$ 个正整数 $a_i$ 代表第 $i$ 张卡的欧气值
## 输出格式

第 $1$ 行一个正整数代表yyf每次抽卡的欧气之和的最大值

第 $2$ 行 $n$ 个正整数代表每次连抽的第一张卡的编号，如果有多种方案满足要求任意输出一种 （如果不会输出方案也请在第二行随意输出 $n$ 个整数，否则可能 $0$ 分）

方案请升序输出
## 样例

### 样例输入 #1
```
3 3 3 3
2 7 1 4 5 3 6 8 5 1 2 9
```
### 样例输出 #1
```
36
2 5 9
```
### 样例输入 #2
```
2 5 2 2
7 3 3 7 7 5 1 10 2
```
### 样例输出 #2
```
41
2 6 
```
## 提示

$20\%$的数据有$1 \le n \le 5$，$1 \le m \le 5$，$2 \le c \le 5$

$50\%$的数据有$1 \le n \le 40$，$1 \le m \le 200$，$2 \le c \le 20$

另有$20\%$的数据有$d=m$

$100\%$的数据有$1 \le n \le 40$，$1 \le m \le 80000$，$2 \le c \le 3000$，$1 \le a_i \le 10000$，$1 \le d \le m$，$d*(n+1) \ge m$

共 $10$ 个测试点，每个测试点答案错误 $0$ 分，答案正确方案错误 $6$ 分，答案正确方案正确 $10$ 分。

样例解释：输出的方案就是样例解释了QAQ

样例一：单抽 $1$ ，连抽 $2$~$4$，连抽 $5$~$7$，单抽 $8$，连抽 $9$~$11$，单抽 $12$，欧气值总和为 $2+7+5+8+5+9=36$

样例二：单抽 $1$ ，连抽 $2$~$3$，单抽 $4$，单抽 $5$，连抽 $6$~$7$，单抽 $8$，单抽 $9$，欧气值总和为 $7+3+7+7+5+10+2=41$

可以证明在满足条件的情况下上述两种方案是欧气值总和最大的


---

---
title: "[CSP-S2019] 划分"
layout: "post"
diff: 省选/NOI-
pid: P5665
tag: ['贪心', '2019', '单调队列', 'CSP-S 提高级']
---
# [CSP-S2019] 划分
## 题目描述

2048 年，第三十届 CSP 认证的考场上，作为选手的小明打开了第一题。这个题的样例有 $n$ 组数据，数据从 $1 \sim n$ 编号，$i$ 号数据的规模为 $a_i$。

小明对该题设计出了一个暴力程序，对于一组规模为 $u$ 的数据，该程序的**运行时间**为 $u^2$。然而这个程序运行完一组规模为 $u$ 的数据之后，它将在任何一组规模**小于** $u$ 的数据上运行错误。样例中的 $a_i$ 不一定递增，但小明又想在不修改程序的情况下正确运行样例，于是小明决定使用一种非常原始的解决方案：将所有数据划分成若干个数据段，段内数据编号**连续**，接着将同一段内的数据合并成新数据，其规模等于段内原数据的**规模之和**，小明将让新数据的规模能够递增。

也就是说，小明需要找到一些分界点 $1 \leq k_1 \lt k_2 \lt \cdots \lt k_p \lt n$，使得

$$ \sum_{i=1}^{k_1} a_i \leq \sum_{i=k_1+1}^{k_2} a_i \leq \cdots \leq \sum_{i=k_p+1}^{n} a_i $$

注意 $p$ 可以为 $0$ 且此时 $k_0 = 0$，也就是小明可以将所有数据合并在一起运行。

小明希望他的程序在正确运行样例情况下，运行时间也能尽量小，也就是**最小化**

$$ (\sum_{i=1}^{k_1} a_i)^2 + (\sum_{i=k_1+1}^{k_2} a_i)^2 + \cdots + (\sum_{i=k_p+1}^{n} a_i)^2 $$

小明觉得这个问题非常有趣，并向你请教：给定 $n$ 和 $a_i$，请你求出最优划分方案下，小明的程序的最小运行时间。

## 输入格式

**由于本题的数据范围较大，部分测试点的 $a_i$ 将在程序内生成。**

第一行两个整数 $n, type$。$n$ 的意义见题目描述，$type$ 表示输入方式。
1. 若 $type = 0$，则该测试点的 $a_i$ **直接给出**。输入文件接下来：第二行 $n$ 个以空格分隔的整数 $a_i$，表示每组数据的规模。
2. 若 $type = 1$，则该测试点的 $a_i$ 将**特殊生成**，生成方式见后文。输入文件接下来：第二行六个以空格分隔的整数 $x, y, z, b_1, b_2, m$。接下来 $m$ 行中，第 $i (1 \leq i \leq m)$ 行包含三个以空格分隔的正整数 $p_i, l_i, r_i$。

对于 $type = 1$ 的 23~25 号测试点，$a_i$ 的生成方式如下：

给定整数 $x, y, z, b_1, b_2, m$，以及 $m$ 个三元组 $(p_i, l_i, r_i)$。

保证 $n \geq 2$。若 $n \gt 2$，则 $\forall 3 \leq i \leq n, b_i = (x \times b_{i−1} + y \times b_{i−2} + z) \mod 2^{30}$。

保证 $1 \leq p_i \leq n, p_m = n$。令 $p_0 = 0$，则 $p_i$ 还满足 $\forall 0 \leq i \lt m$ 有 $p_i \lt p_{i+1}$。

对于所有 $1 \leq j \leq m$，若下标值 $i (1 \leq i \leq n)$满足 $p_{j−1} \lt i \leq p_j$，则有

$$a_i = \left(b_i \mod \left( r_j − l_j + 1 \right) \right) + l_j$$

**上述数据生成方式仅是为了减少输入量大小，标准算法不依赖于该生成方式。**

## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
5 0
5 1 7 9 9
```
### 样例输出 #1
```
247
```
### 样例输入 #2
```
10 0
5 6 7 7 4 6 2 13 19 9
```
### 样例输出 #2
```
1256
```
### 样例输入 #3
```
10000000 1
123 456 789 12345 6789 3
2000000 123456789 987654321
7000000 234567891 876543219
10000000 456789123 567891234
```
### 样例输出 #3
```
4972194419293431240859891640
```
## 提示

【样例 1 解释】

最优的划分方案为 $\{5,1\}, \{7\}, \{9\}, \{9\}$。由 $5 + 1 \leq 7 \leq 9 \leq 9$ 知该方案合法。

答案为 $(5 + 1)^2 + 7^2 + 9^2 + 9^2 = 247$。

虽然划分方案 $\{5\}, \{1\}, \{7\}, \{9\}, \{9\}$ 对应的运行时间比 $247$ 小，但它不是一组合法方案，因为 $5 \gt 1$。

虽然划分方案 $\{5\}, \{1,7\}, \{9\}, \{9\}$ 合法，但该方案对应的运行时间为 $251$，比 $247$ 大。

【样例 2 解释】

最优的划分方案为 $\{5\}, \{6\}, \{7\}, \{7\}, \{4,6,2\}, \{13\}, \{19,9\}$。

【数据范围】

| 测试点编号 | $n \leq$ | $a_i \leq$ | $type =$ |
| :----------- | :----------- | :----------- | :----------- |
| $1 \sim 3$ | $10$ | $10$ | 0 |
| $4 \sim 6$ | $50$ | $10^3$ | 0 |
| $7 \sim 9$ | $400$ | $10^4$ | 0 |
| $10 \sim 16$ | $5000$ | $10^5$ | 0 |
| $17 \sim 22$ | $5 \times 10^5$ | $10^6$ | 0 |
| $23 \sim 25$ | $4 \times 10^7$ | $10^9$ | 1 |

对于$type=0$的所有测试点,保证最后输出的答案$\leq 4 \times 10^{18}$

所有测试点满足：$type \in \{0,1\}$，$2 \leq n \leq 4 \times 10^7$，$1 \leq a_i \leq 10^9$，$1 \leq m \leq 10^5$，$1 \leq l_i \leq r_i \leq 10^9$，$0 \leq x,y,z,b_1,b_2 \lt 2^{30}$。


---

---
title: "[SDOI2012] 任务安排"
layout: "post"
diff: 省选/NOI-
pid: P5785
tag: ['动态规划 DP', '2012', '二分', '各省省选', '单调队列', '山东', '斜率优化']
---
# [SDOI2012] 任务安排
## 题目描述

机器上有 $n$ 个需要处理的任务，它们构成了一个序列。这些任务被标号为 $1$ 到 $n$，因此序列的排列为 $1 , 2 , 3 \cdots n$。这 $n$ 个任务被分成若干批，每批包含相邻的若干任务。从时刻 $0$ 开始，这些任务被分批加工，第 $i$ 个任务单独完成所需的时间是 $T_i$。在每批任务开始前，机器需要启动时间 $s$，而完成这批任务所需的时间是各个任务需要时间的总和。

**注意，同一批任务将在同一时刻完成**。每个任务的费用是它的完成时刻乘以一个费用系数 $C_i$。

请确定一个分组方案，使得总费用最小。
## 输入格式

第一行一个整数 $n$。
第二行一个整数 $s$。

接下来 $n$ 行，每行有一对整数，分别为 $T_i$ 和 $C_i$，表示第 $i$ 个任务单独完成所需的时间是 $T_i$ 及其费用系数 $C_i$。
## 输出格式

一行，一个整数，表示最小的总费用。
## 样例

### 样例输入 #1
```
5
1
1 3
3 2
4 3
2 3
1 4

```
### 样例输出 #1
```
153

```
## 提示

对于 $100\%$ 数据，$1 \le n \le 3 \times 10^5$，$1 \le s \le 2^8$，$ \left| T_i \right| \le 2^8$，$0 \le C_i \le 2^8$。


---

---
title: "[JSOI2015] 送礼物"
layout: "post"
diff: 省选/NOI-
pid: P6087
tag: ['2015', '二分', '各省省选', '单调队列', '江苏', '分数规划']
---
# [JSOI2015] 送礼物
## 题目背景

JYY 和 CX 的结婚纪念日即将到来，JYY 来到萌萌开的礼品店选购纪念礼物。

萌萌的礼品店很神奇，所有出售的礼物都按照特定的顺序都排成一列，而且相邻
的礼物之间有一种神秘的美感。于是，JYY 决定从中挑选连续的一些礼物，但究
竟选哪些呢？
## 题目描述

假设礼品店一共有 $N$ 件礼物排成一列，每件礼物都有它的美观度。排在第 $i\ (1\leq i\leq N)$ 个位置的礼物美观度为正整数 $A_i$。JYY 决定选出其中连续的一段，即编号为 $i,i+1,\cdots,j-1,j$ 的礼物。选出这些礼物的美观程度定义为

$$\frac{M(i,j)-m(i,j)}{j-i+K}$$

其中 $M(i,j)$ 表示 $\max\{A_i,A_{i+1},\cdots,A_j\}$，$m(i,j)$ 表示 $\min\{A_i,A_{i+1},\cdots,A_j\}$，$K$ 为给定的正整数。
由于不能显得太小气，所以 JYY 所选礼物的件数最少为 $L$ 件；同时，选得太多也不好拿，因此礼物最多选 $R$ 件。JYY 应该如何选择，才能得到最大的美观程度？由于礼物实在太多挑花眼，JYY 打算把这个问题交给会编程的你。


## 输入格式

**本题每个测试点有多组数据。**

输入第一行包含一个正整数 $T$，表示有 $T$ 组数据。

每组数据包含两行。第一行四个非负整数 $N,K,L,R$。第二行包含 $N$ 个正整数，依次表示 $A_1,A_2,\cdots,A_n$。
## 输出格式

输出 $T$ 行，每行一个非负实数，依次对应每组数据的答案，数据保证答案不
会超过 $10^3$。输出四舍五入保留 $4$ 位小数。
## 样例

### 样例输入 #1
```
1
5 1 2 4
1 2 3 4 5
```
### 样例输出 #1
```
0.7500
```
## 提示

对于 $100\%$ 的数据，$T\leq 10$，$N,K\leq 5\times 10^4$，$1\leq A_i\leq 10^8$，$2\leq L,R\leq N$。


---

---
title: "Shopping"
layout: "post"
diff: 省选/NOI-
pid: P6326
tag: ['点分治', '单调队列', 'O2优化', '背包 DP']
---
# Shopping
## 题目描述

马上就是小苗的生日了，为了给小苗准备礼物，小葱兴冲冲地来到了商店街。商店街有 $n$ 个商店，并且它们之间的道路构成了一棵树的形状。

第 $i$ 个商店只卖第 $i$ 种物品，小苗对于这种物品的喜爱度是 $w_i$，物品的价格为 $c_i$，物品的库存是 $d_i$。但是商店街有一项奇怪的规定：如果在商店 $u,v$ 买了东西，并且有一个商店 $p$ 在 $u$ 到 $v$ 的路径上，那么必须要在商店 $p$ 买东西。小葱身上有 $m$ 元钱，他想要尽量让小苗开心，所以他希望最大化小苗对买到物品的喜爱度之和。

这种小问题对于小葱来说当然不在话下，但是他的身边没有电脑，于是他打电话给同为OI选手的你，你能帮帮他吗？


## 输入格式

输入第一行一个正整数 $T$ ，表示测试数据组数。

对于每组数据，

第一行两个正整数 $n,m$  。

第二行 $n$ 个非负整数 $w_1,w_2...w_n$ 。

第三行 $n$ 个正整数 $c_1,c_2...c_n$ 。

第四行 $n$ 个正整数 $d_1,d_2...d_n$ 。

接下来 $n-1$ 行每行两个正整数 $u,v$ 表示 $u$ 和 $v$之间有一条道路。
## 输出格式

输出共 $T$ 行，每行一个整数，表示最大的喜爱度之和。
## 样例

### 样例输入 #1
```
1
3 2
1 2 3
1 1 1
1 2 1
1 2
1 3
```
### 样例输出 #1
```
4
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1\leq n\le 500$，$1\le m\le 4000$，$1\le T \le 5$，$0\le w_i\le 4000$，$1 \leq c_i \leq m$，$1\le d_i\le 2000$。

#### 说明

题目来源：BZOJ4182。


---

---
title: "[SBCOI2020] 一直在你身旁"
layout: "post"
diff: 省选/NOI-
pid: P6563
tag: ['动态规划 DP', '单调队列', 'O2优化']
---
# [SBCOI2020] 一直在你身旁
## 题目背景

转眼间，又到春天...  
站在这里，我才发现，  
原来，我的心，  
已与那座被光玉守护的小镇相连。   
......  
“又到了一年春天啊...”  
“看来，你已经准备留在这里了呢。”  
“其实，我也没有什么远大的理想，只是努力地维持着现状...”  
“不过，只要能实现自己的梦想，这又有什么关系啊...”  
“但是现在，我真的是非常的开心。就像你说的那样，找到了很多快乐的事情...”  
“我也和你一样，处在同一个世界。世界上没有一成不变的事物。
所以只要以其他方式找到自己的快乐就行了...”  
“对啊，是时候开始新的生活了呢......”

![](https://cdn.luogu.com.cn/upload/image_hosting/frgxpnaw.png)  

“你对这个小镇真是执着呢...”  
“因为，这里满是我不想忘记的回忆啊...”  
## 题目描述

回到这座小镇后，她的新工作是维修电线。    
现在，有一根电线坏了。已知电线长度可能为 $1,2,\cdots,n$ 中的一个数。现在，她需要知道电线的长度。  
她可以花费 $a_i$ 块钱购买长度为 $i$ 的电线。购买这根电线后，她能知道所需要的电线长度是否 **大于** $i$。  
保证 $a_1 \le a_2 \le \cdots \le a_n \le 10^9$。  
问她至少要花多少钱才能保证知道需要电线的长度。  
## 输入格式

**本题有多组数据**。

第一行为一个正整数 $T$ 表示数据组数。

接下来，每组数据，一行一个整数 $n$，接下来一行 $n$ 个整数 $a_1,a_2,\cdots,a_n$。
## 输出格式

$T$ 行，每行输出一个答案。
## 样例

### 样例输入 #1
```
1
2
1 2
```
### 样例输出 #1
```
1
```
## 提示

【样例解释】

买一根长度为 $1$ 的电线，就能知道需要的长度是否大于 $1$，也就能确定是 $1$ 还是 $2$，所以答案就是 $1$。

大样例[链接](https://www.luogu.com.cn/paste/csusv11e)。

【数据范围】

本题捆绑测试，共有 $4$ 个子任务。

$(Subtask 1)(10\%)$，$n \le 15$。


$(Subtask 2)(10\%)$，$n \le 500$。

$(Subtask 3)(30\%)$，$n \le 2000$。


$(Subtask 4)(50\%)$，没有任何额外限制。

对于100%的数据点, $ 1 \le n,\sum n \leq 7100,T \leq 500 $。$\sum n$ 表示所有数据中 $n$ 的和。


---

---
title: "『JROI-3』1÷0"
layout: "post"
diff: 省选/NOI-
pid: P7894
tag: ['模拟', '单调队列', '2021', 'O2优化', '洛谷月赛']
---
# 『JROI-3』1÷0
## 题目背景

```
1÷0=梦恋
```
```
   在距离遥远的山丘上，看得见彼方宛如天地崩毁的光景。

    「——『设计体』传来报告——以功率《七二·八％》重现设计成功——开始同步。」

    一机机凯种的女性体这么告知里克，然后举起手。

    「【典开】——Org.0000——『真典·弑星者』——拜托您了。」

    ——出现在虚空中的是，外形有如小型的塔，刺在地上的一把枪。

    方才目睹的，有如让世界终结的暴力漩涡。

```
## 题目描述

空想用跳棋模拟「圣战」中机凯种的移动方式。

一条**无限长**的数轴上有 $n$ 个不能动的跳棋，空会询问把一颗可以动的跳棋放在一个位置可以**最多**进行几次跳跃。空会问很多次，每次询问**互相独立**。

设第 $i$ 颗不能动的棋子的坐标为 $x_i\left(\forall i\in\left[1,n\right]\right)$.

则跳棋移动的规则如下：

- 这颗跳棋必须是允许移动的。
- 若这颗棋子位于 $a$，目标位置为 $b$，则应**仅有一颗**棋子位于二个位置之间且中间棋子到 $a,b$ 的距离相等。

形式化的讲应有：

$$\sum_{k=1}^n \left[x_k\in\left[b,a\right]\right]=1$$

且 $\exists k\ x_k=\dfrac{a+b}{2}$.


- 出题人过于良心（，你只能向左边跳。

## 输入格式

第一行两个整数 $n,q$，同题意。

接下来一行 $n$ 个整数，第 $i$ 个表示 $x_i$。

接下来一行 $q$ 个数 $x_0$，表示放置可以动的棋子的位置。
## 输出格式

$q$ 行，每行一个整数，第 $i$ 行表示第 $i$ 次询问的结果。
## 样例

### 样例输入 #1
```
3 3
3 5 8
4 6 7
```
### 样例输出 #1
```
1
2
0
```
## 提示

#### 样例解释 1

$$\Huge\Box\Box\blacksquare{\color{red}{\Box}}\blacksquare{\color{red}{\Box}}{\color{red}{\Box}}\blacksquare\Box\Box$$

从左到右的三个红色方块是询问的位置。

- 对于第一个询问，可以跳 $1$ 步，从 4 跳到 2。
- 对于第二个询问，可以跳 $2$ 步，从 6 跳到 4 跳到 2。
- 对于第三个询问，棋子不能向左移动，因为左边同距离位置有一颗不能动的棋子。

对于 $100\%$ 的数据满足 $1\le n\leq 3\times 10^6$，$1\le q\leq3\times 10^5$，$1\le x\le 10^{18}$，$x_i+1\lt x_{i+1}(\forall i \in [1,n-1])$。

| Subtask 编号 | $n\le$ | $q\le$ | 时限 | 空间限制 | 特殊限制 |
| :-----------: | :-----: | :---: | :--: | :------:| :------: |
| Subtask 0 (10 pts) | $10^3$ | $10^3$ |  $1000\ \rm\small ms$ | $\rm512.00\small\  MB$ |  |
| Subtask 1 (30 pts) |  |  | $1000\ \rm\small ms$ | $\rm512.00\small\  MB$ | $\rm A$|
| Subtask 2 (25 pts) |  |  | $1000\ \rm\small ms$ | $\rm512.00\small\  MB$ | $\rm B$ |
| Subtask 3 (25 pts) | $3 \times 10^5$ |  | $400\ \rm\small ms$ | $\rm512.00\small\  MB$ |
| Subtask 4 (10 pts) |  |  | $400\ \rm\small ms$ | $\rm512.00\small\  MB$ |

- 限制 $\text{A}$： $x_n\le2\times 10^5$。
- 限制 $\text{B}$：有不超过 $50$ 个 $i$ 不满足 $x_i-x_{i-1}\le 100$ ，其余 $i$ 满足 $\sum_{i}{x_i-x_{i-1}} \le 2\times 10^5$。


---

