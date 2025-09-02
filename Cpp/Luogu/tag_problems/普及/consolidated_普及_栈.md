---
title: "求数列所有后缀最大值的位置"
layout: "post"
diff: 普及/提高-
pid: B3666
tag: ['O2优化', '单调栈']
---
# 求数列所有后缀最大值的位置
## 题目描述

给定一个数列 $a$，初始为空。有 $n$ 次操作，每次在 $a$ 的末尾添加一个正整数 $x$。

每次操作结束后，请你找到当前 $a$ 所有的后缀最大值的下标（下标从 1 开始）。一个下标 $i$ 是当前 $a$ 的后缀最大值下标当且仅当：对于所有的 $i < j \leq |a|$，都有 $a_i > a_j$，其中 $|a|$ 表示当前 $a$ 的元素个数。

为了避免输出过大，请你**每次操作结束后都输出一个整数**，表示**当前数列**所有后缀最大值的下标的按位异或和。
## 输入格式

第一行是一个整数，表示操作次数 $n$。  
第二行有 $n$ 个整数，依次表示 $n$ 次操作所添加的整数 $x_i$。
## 输出格式

每次操作后请输出一行一个整数，表示当前数列所有后缀最大值下标的按位异或和。
## 样例

### 样例输入 #1
```
5
2 1 3 5 4
```
### 样例输出 #1
```
1
3
3
4
1
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 10^6$，$1 \leq x_i \lt 2^{64}$。


---

---
title: "[信息与未来 2019] 堆栈计算机"
layout: "post"
diff: 普及/提高-
pid: B3753
tag: ['2019', '江苏', 'Special Judge', '进制', '栈', '构造', '信息与未来']
---
# [信息与未来 2019] 堆栈计算机
## 题目描述

有一种新型的堆栈计算机，计算机的内存是一个初始为空的数列，计算机支持三种操作：
- $\tt 1$ - 将整数 $1$ 放入数列的尾部。任意时刻都可执行此操作。
- $\tt dup$ - 将数列尾部的数字复制一份，放入数列尾部。只有数列非空时才能执行此操作。
- $\tt add$ - 取出（并删除）数列尾部的两个数字，相加后放回数列的尾部。只有数列中至少有两个数字时才能执行此操作。

给定一个正整数，你需要输出一个长度不超过 $200$ 的程序（操作的序列），它在执行结束后，恰好得到一个长度为 $1$ 的数列，并且数列中的数字恰好为 $n$。下图展示了一个最终得到 $8$ 的程序。

![](https://cdn.luogu.com.cn/upload/image_hosting/unim6xbj.png)


## 输入格式

输入一行一个正整数 $n$，表示希望输出的数字。
## 输出格式

输出一个若干行（不超过 $200$ 行，否则判为不正确）的满足上述要求的程序。如有多种方案，输出任意一种即可。注意 $\tt dup$ 和 $\tt add$ 均为小写。
## 样例

### 样例输入 #1
```
1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
8
```
### 样例输出 #2
```
1
1
add
dup
add
dup
add
```
## 提示

对于 $60\%$ 的测试数据，有 $1\le n\le10^4$。

对于 $100\%$ 的测试数据，有 $1\le n\le10^9$。
> 本题原始满分为 $15\text{pts}$。


---

---
title: "[蓝桥杯 2023 国 C] 最大区间"
layout: "post"
diff: 普及/提高-
pid: P12241
tag: ['2023', '蓝桥杯国赛', '单调栈']
---
# [蓝桥杯 2023 国 C] 最大区间
## 题目描述

给定一个长度为 $n$ 的序列 $A_i$，求 $L, R$ 使 $(R - L + 1) \cdot \min(A_L, A_{L+1}, \ldots, A_R)$ 尽可能大，其中 $\min$ 表示最小值。

你只需要输出最大的值即可，不需要输出具体的 $L, R$。
## 输入格式

输入的第一行包含一个整数 $n$。

第二行包含 $n$ 个整数，分别表示 $A_1, A_2, \ldots, A_n$，相邻两个整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
5
1 1 3 3 1
```
### 样例输出 #1
```
6
```
## 提示

### 评测用例规模与约定

对于 $40\%$ 的评测用例，$1 \leq n \leq 5000$，$1 \leq A_i \leq 5000$；

对于所有评测用例，$1 \leq n \leq 3 \times 10^5$，$1 \leq A_i \leq 10^9$。


---

---
title: "[GCJ 2013 #2] Ticket Swapping"
layout: "post"
diff: 普及/提高-
pid: P13294
tag: ['贪心', '2013', '排序', '栈', 'Google Code Jam']
---
# [GCJ 2013 #2] Ticket Swapping
## 题目描述

The city has built its first subway line, with a grand total of $N$ stations, and introduced a new way of paying for travel. Instead of just paying for one ticket and making an arbitrary journey, the price you pay is now based on entry cards.

When entering the subway, each passenger collects an entry card, which specifies the station the passenger entered at. When leaving the subway, the passenger has to give up the entry card, and is charged depending on the distance (in stations traveled) between the entry station specified on the entry card, and the exit station on which the entry card is surrendered. The payment depends on the distance between these stations as follows:

* if they are the same station, you don't pay;
* if they are adjacent stations, you pay $N$ pounds;
* if the distance is two stations, you pay $2N - 1$: a charge $N$ for the first stop and $N - 1$ for the second;
* the third station costs $N-2$ (so you pay $3N - 3$ for a three-station-long trip), the fourth stop $N-3$, and the $i$th stop $N + 1 - i$;
* thus, if you travel from one end of the subway to the other (a distance of $N-1$ stations), you pay $2$ pounds for the last station traveled, and a grand total of $(N^2 + N - 2) / 2$ in total.

After introducing this system the city noticed their gains are not as big as they expected. They figured out this might be due to people swapping their entry cards — so, for instance, if one person enters at station $A$, travels two stations to $B$ and exits, while another person enters at $B$, travels three stations to $C$ and exits, they would normally pay (in total) $2N - 1 + 3N - 3 = 5N - 4$. But if the two people swapped their entry cards at station $B$, then the first one would travel for free (as he would surrender an entry card specifying the station $B$ while exiting a station $B$, and so register a distance of zero); while the second person will exit at station $C$ and surrender an entry card specifying station $A$, which is $5$ stations away, and pays $5N - 10$, at a net loss of six pounds to the city!

The city now wants to learn how much they can possibly lose if this practice becomes widespread. We will consider only one direction (from station $1$ to station $N$, passing through all the stations in order) of the subway, and only one train on this line. We assume a passenger travelling from $o$ to $e$ obtains an entry card at $o$, can swap her entry card any number of times with any other passengers anywhere between $o$ and $e$, including swapping with people who leave at $o$ or those who enter at $e$, and then exit the train at $e$ with some entry card (it is necessary to surrender some entry card to exit the subway). We also assume the passenger will not exit the train in the meantime (that is, will not surrender the currently held card and obtain a new one).

You are given a map of traffic (specifying how many passengers travel this train from which station to which), and you should calculate the city's financial loss, assuming passengers swap their cards to maximize this loss.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case contains the number $N$ of stops (the stops are numbered $1$ to $N$), and the number $M$ of origin-endpoint pairs given. The next $M$ lines contain three numbers each: the origin stop $o_i$, the end stop $e_i$ and $p_i$: the number of passengers that make this journey.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from $1$) and $y$ is the total loss the city can observe due to ticket swapping, modulo $1000002013$.

## 样例

### 样例输入 #1
```
3
6 2
1 3 1
3 6 1
6 2
1 3 2
4 6 1
10 2
1 7 2
6 9 1
```
### 样例输出 #1
```
Case #1: 6
Case #2: 0
Case #3: 10
```
## 提示

**Sample Explanation**

The first test case is the case described in the problem statement - two passengers meet at station 3 and swap tickets. In the second test case the two passengers don't meet at all, so they can't swap tickets (and so the city incurs no loss). In the third case, only one of the early passengers can swap tickets with the later passenger.

**Limits**

- $1 \leq T \leq 20$.
- $1 \leq o_i < e_i \leq N$

**Small dataset (8 Pts, Test set 1 - Visible)**

- $2 \leq N \leq 100$.
- $1 \leq M \leq 100$.
- $1 \leq p_i \leq 100$.

**Large dataset (11 Pts, Test set 2 - Hidden)**

- $2 \leq N \leq 10^9$.
- $1 \leq M \leq 1000$.
- $1 \leq p_i \leq 10^9$.


---

---
title: "[SWERC 2023] Nicest view"
layout: "post"
diff: 普及/提高-
pid: P13796
tag: ['2023', 'ICPC', '单调栈']
---
# [SWERC 2023] Nicest view
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/93613cfd23ca0223b6f9aa573bf5381a7646cd95.png)

:::

Paris is so crowded with tourists during the Olympic games! You want to escape the city and go on a hike on a linear trail path, going from left to right. Every kilometre on that trail, including at start and end, is a milestone, on which is written the stone's altitude. The slope between two consecutive stones is constant, and no two stones have the same altitude.


Planning to come back with your friends, you try to identify the point of the hike at which you had the nicest view. The beauty of a point of view is defined as the distance (measured in kilometres) between your position and the leftmost position that you can see on your hike and that is at the same altitude as you are. If such a previous position fails to exist, it means that you can see the city and its smog, and the beauty of that view is zero.


You have listed the altitudes of the milestones. What is the maximal beauty on your hike?
## 输入格式

The input consists of two lines. The first line contains a single integer $N$, which is the number of milestones on the trail path. The second line contains $N$ space-separated integers $H_1, H_2, \dots, H_N$; each integer $H_k$ is the altitude (measured in metres) of the $k^\text{th}$ milestone on the path.


**Limits**

- $1 \leq N \leq 100~000$;
- $0 \leq H_k \leq 1~000~000$ for all $k \leq N$;
- the integers $H_k$ are pairwise distinct.

## 输出格式

The output should contain a single line, consisting of a single number $S$: the best beauty score on your hike. This number is written either as an integer or as an irreducible fraction $N/D$ for which $D \geq 2$; we recall that a fraction $N/D$ is irreducible when the greatest common divisor of $N$ and $D$ is $1$.
## 样例

### 样例输入 #1
```
7
0 5 3 1 4 8 2
```
### 样例输出 #1
```
13/4
```
### 样例输入 #2
```
5
3 5 8 7 1
```
### 样例输出 #2
```
0
```


---

---
title: "[yLOI2018] 树上的链"
layout: "post"
diff: 普及/提高-
pid: P1612
tag: ['2018', '二分', 'O2优化', '栈']
---
# [yLOI2018] 树上的链
## 题目描述

给定一棵有 $n$ 个节点的树。每个节点有一个点权和一个参数。节点 $i$ 的权值为 $w_i$，参数为 $c_i$。$1$ 是这棵树的根。

现在，对每个节点 $u$（$1 \leq u \leq n$），请在树上你找到最长的一条链 $v_1, v_2, \dots v_m$，满足如下条件：

1. $v_1 = u$。
2. 对 $2 \leq i \leq m$， 有 $v_i$ 是 $v_{i - 1}$ 的父节点。
3. 链上节点的点权和不超过 $c_u$，即 $\sum_{j = 1}^m w_{v_j} \leq c_u$。 
## 输入格式

第一行是一个整数，表示树的节点数 $n$。  
第二行有 $n - 1$ 个整数 $p_2, p_3, \dots p_n$，其中 $p_i$ 表示节点 $i$ 的父节点。  
第三行有 $n$ 个整数，第 $i$ 个整数表示节点 $i$ 的权值 $w_i$。  
第四行有 $n$ 个整数，第 $i$ 个整数表示节点 $i$ 的参数 $c_i$。
## 输出格式

输出一行 $n$ 个用空格隔开的整数，第 $i$ 个整数表示节点 $i$ 对应的链的最长长度。
## 样例

### 样例输入 #1
```
5
1 1 2 2
1 2 3 4 5
1 3 3 6 8
```
### 样例输出 #1
```
1 2 1 2 3
```
## 提示

### 数据规模与约定

对全部的测试点，保证 $1 \leq u, v \leq n \leq 10^5$，$1 \leq p_i \lt i$，$1 \leq w_i \leq c_i \leq 10^9$。


---

---
title: "发射站"
layout: "post"
diff: 普及/提高-
pid: P1901
tag: ['NOI 导刊', '栈', '单调栈']
---
# 发射站
## 题目描述

某地有 $N$ 个能量发射站排成一行，每个发射站 $i$ 都有不相同的高度 $H_i$，并能向两边（两端的发射站只能向一边）同时发射能量值为 $V_i$ 的能量，发出的能量只被两边**最近的且比它高**的发射站接收。显然，每个发射站发来的能量有可能被 $0$ 或 $1$ 或 $2$ 个其他发射站所接受。

请计算出接收最多能量的发射站接收的能量是多少。

## 输入格式

第 $1$ 行一个整数 $N$。

第 $2$ 到 $N+1$ 行，第 $i+1$ 行有两个整数 $H_i$ 和 $V_i$，表示第 $i$ 个发射站的高度和发射的能量值。
## 输出格式

输出仅一行，表示接收最多能量的发射站接收到的能量值。答案不超过 32 位带符号整数的表示范围。

## 样例

### 样例输入 #1
```
3
4 2 
3 5 
6 10

```
### 样例输出 #1
```
7
```
## 提示

对于 $40\%$ 的数据，$1\le N\le 5000,1\le H_i\le 10^5,1\le V_i\le 10^4$。

对于 $70\%$ 的数据，$1\le N\le 10^5,1\le H_i\le 2\times 10^9,1\le V_i\le 10^4$。

对于 $100\%$ 的数据，$1\le N\le 10^6,1\le H_i\le 2\times 10^9,1\le V_i\le 10^4$。


---

---
title: "[USACO06NOV] Bad Hair Day S"
layout: "post"
diff: 普及/提高-
pid: P2866
tag: ['2006', 'USACO', '栈', 'ST 表', '单调栈']
---
# [USACO06NOV] Bad Hair Day S
## 题目描述


农夫约翰有 $N$ 头奶牛正在过乱头发节。

每一头牛都站在同一排面朝右，它们被从左到右依次编号为 $1, 2, \cdots, N$。编号为 $i$ 的牛身高为 $h_i$。第 $N$ 头牛在最前面，而第 $1$ 头牛在最后面。

对于第 $i$ 头牛**前面**的第 $j$ 头牛，如果 $h_i>h_{i+1}, h_i>h_{i+2}, \cdots, h_i>h_j$，那么认为第 $i$ 头牛可以看到第 $i+1$ 到第 $j$ 头牛。

定义 $C_i$ 为第 $i$ 头牛所能看到的牛的数量。请帮助农夫约翰求出 $C _ 1 + C _ 2 + \cdots + C _ N$。

## 输入格式

输入共 $N + 1$ 行。

第一行为一个整数 $N$，代表牛的个数。  
接下来 $N$ 行，每行一个整数 $a _ i$，分别代表第 $1, 2, \cdots, N$ 头牛的身高。
## 输出格式

输出共一行一个整数，代表 $C _ 1 + C _ 2 + \cdots + C _ N$。
## 样例

### 样例输入 #1
```
6
10
3
7
4
12
2
```
### 样例输出 #1
```
5
```
## 提示

### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq N \leq 8 \times 10 ^ 4$，$1 \leq h _ i \leq 10 ^ 9$。


---

---
title: "[USACO09MAR] Look Up S"
layout: "post"
diff: 普及/提高-
pid: P2947
tag: ['2009', 'USACO', '单调栈']
---
# [USACO09MAR] Look Up S
## 题目描述

Farmer John's N (1 <= N <= 100,000) cows, conveniently numbered 1..N, are once again standing in a row. Cow i has height H\_i (1 <= H\_i <= 1,000,000).

Each cow is looking to her left toward those with higher index numbers. We say that cow i 'looks up' to cow j if i < j and H\_i < H\_j. For each cow i, FJ would like to know the index of the first cow in line looked up to by cow i.

Note: about 50% of the test data will have N <= 1,000. 

约翰的 $N(1\le N\le10^5)$ 头奶牛站成一排，奶牛 $i$ 的身高是 $H_i(1\le H_i\le10^6)$。现在，每只奶牛都在向右看齐。对于奶牛 $i$，如果奶牛 $j$ 满足 $i<j$ 且 $H_i<H_j$，我们可以说奶牛 $i$ 可以仰望奶牛 $j$。 求出每只奶牛离她最近的仰望对象。

Input
## 输入格式

1. \* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 contains the single integer: H\_i

第 $1$ 行输入 $N$，之后每行输入一个身高 $H_i$。

## 输出格式

\* Lines 1..N: Line i contains a single integer representing the smallest index of a cow up to which cow i looks. If no such cow exists, print 0.

共 $N$ 行，按顺序每行输出一只奶牛的最近仰望对象，如果没有仰望对象，输出 $0$。

## 样例

### 样例输入 #1
```
6 
3 
2 
6 
1 
1 
2 

```
### 样例输出 #1
```
3 
3 
0 
6 
6 
0 

```
## 提示

FJ has six cows of heights 3, 2, 6, 1, 1, and 2.


Cows 1 and 2 both look up to cow 3; cows 4 and 5 both look up to cow 6; and cows 3 and 6 do not look up to any cow.

【输入说明】$6$ 头奶牛的身高分别为 3,2,6,1,1,2。

【输出说明】奶牛 #1,#2 仰望奶牛 #3，奶牛 #4,#5 仰望奶牛 #6，奶牛 #3 和 #6 没有仰望对象。

【数据规模】

对于 $20\%$ 的数据：$1\le N\le10$；

对于 $50\%$ 的数据：$1\le N\le10^3$；

对于 $100\%$ 的数据：$1\le N\le10^5,1\le H_i\le10^6$。



---

---
title: "[USACO11FEB] Best Parenthesis S"
layout: "post"
diff: 普及/提高-
pid: P3015
tag: ['模拟', '字符串', '2011', 'USACO', '栈']
---
# [USACO11FEB] Best Parenthesis S
## 题目描述

Recently, the cows have been competing with strings of balanced parentheses and comparing them with each other to see who has the best one.

Such strings are scored as follows (all strings are balanced): the string '()' has score 1; if 'A' has score s(A) then '(A)' has score 2\*s(A); and if 'A' and 'B' have scores s(A) and s(B), respectively, then 'AB' has score s(A)+s(B). For example, s('(())()') = s('(())')+s('()') = 2\*s('()')+1 = 2\*1+1 = 3.

Bessie wants to beat all of her fellow cows, so she needs to calculate the score of some strings. Given a string of balanced parentheses of length N (2 <= N <= 100,000), help Bessie compute its score.

给定一个只包含左右括号的字符串，得分规则如下：

如果一对括号内没有括号，那么这对括号的得分为1；如果两对括号互不包含（即并列存在），那这两对括号的得分相加；如果括号内包含一对括号，那么这个括号的得分纪为内部括号序列的得分\*2。

例如：对于这样一个字符串："() ()"，两对括号并列存在，则得分为1+1=2;

而对于这样一个字符串："(())"，最外层的括号内层包含一对括号，则得分为2\*1=2.


Bessie想击败所有同事的牛，所以她需要计算某个字符串的评分。给定一个长度为n、只包含括号的字符串（2≤N≤100000），计算其得分帮助Bessie。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N + 1: Line i+1 will contain 1 integer: 0 if the ith character of the string is '(',  and 1 if the ith character of the string is ')'

## 输出格式

\* Line 1: The score of the string. Since this number can get quite large, output the  score modulo 12345678910.

## 样例

### 样例输入 #1
```
6 
0 
0 
1 
1 
0 
1 

```
### 样例输出 #1
```
3 

```
## 提示

This corresponds to the string "(())()". 

As discussed above.

输出答案要mod12345678910



---

---
title: "[POI 2008] PLA-Postering"
layout: "post"
diff: 普及/提高-
pid: P3467
tag: ['2008', 'POI（波兰）', '栈']
---
# [POI 2008] PLA-Postering
## 题目描述

All the buildings in the east district of Byteburg were built    in accordance with the old arbitecture:

they stand next to each other with no spacing inbetween.

Together they form a very long chain of buildings of diverse    height, extending from east to west.

The mayor of Byteburg, Byteasar, has decided to have the north face    of the chain covered with posters.

Byteasar ponders over the minimum number of posters sufficient to    cover the whole north face.

The posters have rectangular shape with vertical and horizontal sides.

They cannot overlap, but may touch each other, i.e. have common points    on the sides.

Every poster has to entirely adjoin the walls of certain buildings    and the whole surface of the north face has to be covered.

Task      Write a programme that:

reads the description of buildings from the standard input,                      determines the minimum number of posters needed to entirely cover their north faces,                      writes out the outcome to the standard output.

Byteburg市东边的建筑都是以旧结构形式建造的:建筑互相紧挨着,之间没有空间.它们共同形成了一条长长的,从东向西延伸的建筑物链(建筑物的高度不一).Byteburg市的市长Byteasar,决定将这个建筑物链的一侧用海报覆盖住.并且想用最少的海报数量,海报是矩形的.海报与海报之间不能重叠,但是可以相互挨着(即它们具有公共边),每一个海报都必须贴近墙并且建筑物链的整个一侧必须被覆盖(意思是:海报需要将一侧全部覆盖,并且不能超出建筑物链)

## 输入格式

The first line of the standard input contains one integer $n$ ($1\le n\le 250\ 000$), denoting the number of buildings the chain      comprises of.

Each of the following $n$ lines contains two integers $d_i$ and $w_i$ ($1\le d_i,w_i\le 1\ 000\ 000\ 000$),      separated by a single space, denoting respectively the length and height      of the $i^{th}$ building in the row.

第一行为一个整数n(1≤n≤250000),表示有n个建筑,接下来n行中,第i行表示第i个建筑物的宽di与高wi(1≤di,wi≤1 000 000 000),中间由一个空格隔开

## 输出格式

The first and only line of the standard output should contain one integer,      the minimum number of rectangular posters that suffice to cover the north faces      of the buildings.

第一个为一个整数,表示最少需要几张海报.

## 样例

### 样例输入 #1
```
5
1 2
1 3
2 2
2 5
1 4
```
### 样例输出 #1
```
4
```
## 提示

题目简述：N个矩形,排成一排. 现在希望用尽量少的矩形海报Cover住它们.

感谢@\_\_乱世魇华 提供翻译



---

---
title: "【深基15.习9】验证栈序列"
layout: "post"
diff: 普及/提高-
pid: P4387
tag: ['栈']
---
# 【深基15.习9】验证栈序列
## 题目描述

给出两个序列 pushed 和 poped 两个序列，其取值从 1 到 $n(n\le100000)$。已知入栈序列是 pushed，如果出栈序列有可能是 poped，则输出 `Yes`，否则输出 `No`。为了防止骗分，每个测试点有多组数据，不超过 $5$ 组。
## 输入格式

第一行一个整数 $q$，询问次数。

接下来 $q$ 个询问，对于每个询问：

第一行一个整数 $n$ 表示序列长度；

第二行 $n$ 个整数表示入栈序列；

第三行 $n$ 个整数表示出栈序列；
## 输出格式

对于每个询问输出答案。
## 样例

### 样例输入 #1
```
2
5
1 2 3 4 5
5 4 3 2 1
4
1 2 3 4
2 4 1 3
```
### 样例输出 #1
```
Yes
No
```


---

---
title: "【模板】单调栈"
layout: "post"
diff: 普及/提高-
pid: P5788
tag: ['线性数据结构', '栈', '单调栈']
---
# 【模板】单调栈
## 题目背景

模板题，无背景。  

2019.12.12 更新数据，放宽时限，现在不再卡常了。
## 题目描述

给出项数为 $n$ 的整数数列 $a_{1 \dots n}$。

定义函数 $f(i)$ 代表数列中第 $i$ 个元素之后第一个大于 $a_i$ 的元素的**下标**，即 $f(i)=\min_{i<j\leq n, a_j > a_i} \{j\}$。若不存在，则 $f(i)=0$。

试求出 $f(1\dots n)$。
## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数 $a_{1\dots n}$。
## 输出格式

一行 $n$ 个整数表示 $f(1), f(2), \dots, f(n)$ 的值。  
## 样例

### 样例输入 #1
```
5
1 4 2 3 5

```
### 样例输出 #1
```
2 5 4 5 0

```
## 提示

【数据规模与约定】

对于 $30\%$ 的数据，$n\leq 100$；

对于 $60\%$ 的数据，$n\leq 5 \times 10^3$ ；

对于 $100\%$ 的数据，$1 \le n\leq 3\times 10^6$，$1\leq a_i\leq 10^9$。


---

---
title: "[USACO19FEB] Dishwashing G"
layout: "post"
diff: 普及/提高-
pid: P6099
tag: ['2019', '二分', 'USACO', '栈']
---
# [USACO19FEB] Dishwashing G
## 题目背景

Bessie 和 Elsie 正在帮助 Farmer John 洗碗，这是一个比人们想象的更复杂的过程。
## 题目描述

两头奶牛决定 Bessie 负责涂肥皂，Elsie 负责冲洗。

刚开始的时候，$N$ 个脏盘子（保证是从 $1$ 到 $N$ 的一个排列）堆在 Bessie 那里，而 Elsie 这边的堆是空的。而在她们俩之间，则有一张专门放涂过肥皂的盘子的桌子。

每个冲洗步骤需要执行以下两个操作之一：

- Bessie 从脏盘子堆顶取出一个盘子，涂上肥皂，然后放在桌子上。将这个盘子放在桌子上时，Bessie 只能放在现有的非空盘堆的顶端，或是在最右边新增一个盘堆。
- Elsie 从桌子最左边的盘堆的顶端拿起盘子，将它冲洗后放在干净的盘堆顶端。

她们希望干净的盘堆能按编号排序，编号最小的在底端，编号最大的在顶端。然而她们发现有的时候这并不可能做到。现在给定脏盘子的堆叠顺序，请你求出一个最大前缀，使得该前缀的所有盘子洗干净后，能按上面的要求堆叠。
## 输入格式

第一行一个整数 $N$（$1 \leq N \leq 10^5$）。

接下来 $N$ 行，每行一个整数，代表 Bessie 的脏盘子堆的堆叠顺序。输入的第一个盘子在堆的顶部。
## 输出格式

输出该序列的最大前缀长度，使得该前缀的所有盘子洗干净后，能按小号在下，大号在上的规则堆叠。
## 样例

### 样例输入 #1
```
5
4
5
2
3
1
```
### 样例输出 #1
```
4
```


---

---
title: "「Wdoi-4」兔已着陆"
layout: "post"
diff: 普及/提高-
pid: P7870
tag: ['2021', '洛谷原创', '栈', '洛谷月赛']
---
# 「Wdoi-4」兔已着陆
## 题目背景

铃瑚和清兰是从月之都到达幻想乡的两只月兔。正因为降落到了幻想乡进行调查，因此她们通过开团子屋制作团子出售的方式，在幻想乡生活。

为了应对越发繁荣的市场，她们向河城荷取购置了一台团子机器，可以高效地生产出五颜六色的团子。不同颜色的团子的售价不尽相同。由于每天顾客数量很多，购买的团子数量也不少，所以清兰总是搞不清楚一大堆团子的售价如何。

清兰找到了你，希望你能告诉她每次售出团子时，这些团子的总价格。
## 题目描述

清兰使用河童的机器可以生产出各种各样颜色的团子。她发现，**对于颜色为** $\bm c$ **的团子，它的售价为** $\bm c$。同时，团子机器有个特性，那就是生产出来的团子的颜色必然是一段连续的整数。

为了储存已经生产出来的团子，清兰使用了一种类似于「栈」的结构。在一天的开始，这个栈为空栈。现在有 $n$ 次操作，分为两种：

1. $\colorbox{f0f0f0}{\verb!1 l r!}$ ：团子机器生产出来了颜色为 $l,l+1,\cdots r-1,r$ 的团子。清兰将这些团子**依次**入栈。也就是在栈顶依次加入 $l,l+1,l+2,\cdots r-1,r$ 。
2. $\colorbox{f0f0f0}{\verb!2 k!}$ ：有一位客人想要购买 $k$ 个团子。此时清兰会**依次**从栈顶取出 $k$ 个团子并售出。保证 $k$ 不大于当前栈内的团子个数。

你要做的，就是对于每个操作 $2$ 输出这些团子的总价格。
## 输入格式

第一行有一个整数 $n$，表示操作的个数。  
接下来 $n$ 行描述一组询问。第一个整数 $op$ 表示询问的种类，若为 $1$ 则为操作 $1$，为 $2$ 则为操作 $2$。

- 对于操作 $1$，接下来有两个整数 $l,r$，含义如题面所示。
- 对于操作 $2$，接下来有一个整数 $k$，含义如题面所示。
## 输出格式

若干行。对于每次操作 $2$，输出这些团子的售价之和。
## 样例

### 样例输入 #1
```
6
1 1 14
2 5
1 14 19
1 1 9
2 8
2 10
```
### 样例输出 #1
```
60
44
124

```
## 提示

样例 $2$ 见下发的附件 $\textbf{\textit{stack2.in}/\textit{stack2.out}}$。

---

### 数据范围

- 对于前 $30\%$ 的数据，$n,l,r\le100$。
- 对于另外 $20\%$ 的数据，$l=r$。
- 对于另外 $20\%$ 的数据，$k\le 10$。
- 对于 $100\%$ 的数据，$1\le n\le 5\times 10^5$，$0\le l\le r \le 10^6$，$1\le k \le 10^{12}$。


---

---
title: "[USACO22JAN] Cow Frisbee S"
layout: "post"
diff: 普及/提高-
pid: P8094
tag: ['USACO', '2022', '单调栈']
---
# [USACO22JAN] Cow Frisbee S
## 题目描述

Farmer John 的 $N\ (N\le 3\times 10^5)$ 头奶牛的高度为 $1, 2, \ldots, N$。一天，奶牛以某个顺序排成一行玩飞盘；令 $h_1 \ldots h_N$ 表示此顺序下奶牛们的高度（因此 $h$ 是 $1 \ldots N$ 的一个排列）。

队伍中位于位置 $i$ 和 $j$ 的两头奶牛可以成功地来回扔飞盘当且仅当她们之间的每头奶牛的高度都低于 $\min(h_i, h_j)$。

请计算所有可以成功地来回扔飞盘的奶牛所在的位置对 $i\le j$ 之间的距离总和。位置 $i$ 和 $j$ 之间的距离为 $j-i+1$。
## 输入格式

输入的第一行包含一个整数 $N$。第二行包含 $h_1 \ldots h_N$，用空格分隔。
## 输出格式

输出可以成功地来回扔飞盘的奶牛所在的位置对 $i\le j$ 之间的距离总和。注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C 或 C++ 中的 "long long"）。
## 样例

### 样例输入 #1
```
7
4 3 1 2 5 6 7
```
### 样例输出 #1
```
24
```
## 提示

【样例解释】

这个例子中可以成功的位置对如下：

```
(1, 2), (1, 5), (2, 3), (2, 4), (2, 5), (3, 4), (4, 5), (5, 6), (6, 7)
```

【数据范围】

- 测试点 1-3 满足 $N\le 5000$。

- 测试点 4-11 没有额外限制。


---

