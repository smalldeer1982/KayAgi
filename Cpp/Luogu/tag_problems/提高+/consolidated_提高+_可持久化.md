---
title: "[HBCPC2024] Enchanted"
layout: "post"
diff: 提高+/省选-
pid: P10863
tag: ['树状数组', '2024', 'O2优化', '可持久化线段树', 'XCPC', '湖北']
---
# [HBCPC2024] Enchanted
## 题目描述

In Minecraft, one way to become stronger is to have the armors and weapons enchanted. Enchanted books play an important role.

![](https://cdn.luogu.com.cn/upload/image_hosting/pc5cf4e8.png)

The most important attribute of an enchanted book is its level. The higher the level is, the better the book is. We could merge two books with the same level  $l$ into one new book(the older two will disappear). The level of the new book is $l+1$ and the merger costs $2^{l+1}$.

Now, Steve has $n$ enchanted books numbered from $1$ to $n$. Initially, the $i$-th book's level is $a_i$. Steve asks you to help him with the following four operations.

1. Given two integers $l,r(1 \le l \le r \le n)$, calculate the maximum level Steve can reach by merging books numbered from $l$ to $r$.
2.  Given three integers $l,r(1 \le l \le r \le n)$ and $k$, then follow the steps:   
Step $1$: Steve merges all the books numbered from $l$ to $r$ until there does not exist two books with the same level.    
Step $2$: Steve adds one new book with level $k$ to the books he gets in Step $1$.     
Step $3$: Steve needs to merge books he gets in Step $2$ and he wants to maximize the times he merges the books.    
Please calculate and output the total cost modulo $10^9+7$ in Step $3$.     
$\textbf{Note that, after calculating, the sequence is restored. That is, this operation does NOT actually change the sequence.}$

3. Given two integers $pos,k$, Steve changes the level of the book numbered $pos$ to $k$.

4. Given one integer $t$, Steve restores the sequence to the state after the $t$-th operation. If $t=0$, then Steve restores the sequence to the beginning state.
## 输入格式

The first and the only line contains 5 integers $n,m,A,p,q$.($1 \leq n \leq 10^6$, $1 \leq m \leq 10^6$, $1 \leq A \leq 19\,260\,817$, $1 \leq p \leq 4$, $1 \leq q \leq 30$)

Please pay attention! To avoid large input file, the true input is constructed through the following strategy:

$\textbf{Function rnd():}\ \ \ \\
A \leftarrow (7A+13) \bmod 19\,260\,817\ \ \ \\ \textbf{return } A$

Firstly, $n$ integers $a_1,a_2,\cdots,a_n$ are generated in turn, $a_i \leftarrow rnd() \bmod q + 1$.

Then, the parameters of all operations are generated.

For each operation, the number of operation(representing by $opt$) is firstly generated, $opt \leftarrow rnd() \bmod p + 1$.

According to the number of operation, the different method is applied to generate parameters for different operation.

- For operation 1: we need to get $l$ and $r$ by using:
  - $L \leftarrow rnd() \bmod n + 1$
  - $R \leftarrow rnd() \bmod n + 1$
  - $l \leftarrow \min(L,R)$
  - $r \leftarrow \max(L,R)$

- For operation 2: we need to get $l,r$ and $k$ by using:
  - $L \leftarrow rnd() \bmod n + 1$
  - $R \leftarrow rnd() \bmod n + 1$
  - $l \leftarrow \min(L,R)$
  - $r \leftarrow \max(L,R)$
  - $k \leftarrow rnd() \bmod q + 1$

- For operation 3: we need to get $pos$ and $k$ by using:
  - $pos \leftarrow rnd() \bmod n + 1$
  - $k \leftarrow rnd() \bmod q + 1$

- For operation 4: we need to get $t$ by using:

  - $t \leftarrow rnd() \bmod i$

Here, $i$ represents the $i$-th operation.
## 输出格式

For each operation 1 and 2, you need to output one single line with an integer, representing the answer to operation 1 and 2 modulo $10^9 + 7$.
## 样例

### 样例输入 #1
```
6 3 2 1 3
```
### 样例输出 #1
```
1
3
2
```
### 样例输入 #2
```
10 15 5 4 7
```
### 样例输出 #2
```
0
9
9
0
64
0
0
```
## 提示

Function `max` means the maximum one between the parameters. Function `min` means the minimum one between the parameters.

In example 1, the initial books are $[1,2,3,1,2,3]$. The three operations' ranges are $[4,4]$, $[1,3]$ and $[4,5]$.


---

---
title: "[COTS 2018] 题日 Zapatak"
layout: "post"
diff: 提高+/省选-
pid: P11262
tag: ['2018', '莫队', '线段树', '可持久化线段树', '哈希 hashing', 'COCI（克罗地亚）']
---
# [COTS 2018] 题日 Zapatak
## 题目背景


译自 [Izborne Pripreme 2018 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2018/) D1T2。$\texttt{1s,1G}$。

关于题目名：原文如此（「题目」的克罗地亚语是「zadatak」）。
## 题目描述


定义长度均为 $k$ 的数列 $[a_1,a_2,\ldots,a_k]$ 和 $[b_1,b_2,\ldots,b_k]$ **几乎相等**，当且仅当存在**恰好一个** $1\le p\le k$，使得 $a_p\neq b_p$。

定义长度均为 $k$ 的数列 $[a_1,a_2,\ldots,a_k]$ 和 $[b_1,b_2,\ldots,b_k]$ **相似**，当且仅当可以通过重排使得 $a,b$ **几乎相等**。

给定长度为 $n$ 的数列 $[a_1,a_2,\ldots,a_n]$。$m$ 次询问，每次询问给定 $l_1,r_1,l_2,r_2$，问 $[a_{l_1},a_{{l_1}+1},\ldots,a_{r_1}]$ 与 $[a_{l_2},a_{{l_2}+1},\ldots,a_{r_2}]$ 是否相似。
## 输入格式


第一行，两个正整数 $n,m$。

第二行，$n$ 个非负整数 $a_1,a_2,\ldots,a_n$。

接下来 $m$ 行，每行四个正整数 $l_1,r_1,l_2,r_2$，描述一次询问。保证 $r_1-l_1=r_2-l_2$。

## 输出格式


对于每个询问，输出一行：

如果答案为是的话，输出 $\texttt{DA}$（克罗地亚语「是」）；

否则输出 $\texttt{NE}$（克罗地亚语「否」）。
## 样例

### 样例输入 #1
```
6 4
1 3 2 3 1 2
1 1 2 2
2 3 3 4
2 3 4 5
1 3 2 4
```
### 样例输出 #1
```
DA
NE
DA
DA
```
### 样例输入 #2
```
10 5
3 3 3 1 2 2 1 2 2 1
2 3 5 6
9 10 5 6
5 6 4 5
5 8 3 6
3 7 5 9
```
### 样例输出 #2
```
NE
DA
DA
DA
NE
```
## 提示



对于 $100\%$ 的数据，保证：

- $1\le n,m\le 10^5$；
- $0\le a_i\le 10^9$；
- $1\le l_1\le r_1\le n$，$1\le l_2\le r_2\le n$；
- $r_1-l_1=r_2-l_2$。


| 子任务编号 | $n\le $ |  $m\le $ | $a_i\le$   | 得分 |  
| :--: | :--: | :--: | :--: |  :--: |    
| $ 1 $    | $ 1\, 000 $    |  $1\, 000$ | $ 10^9$ | $ 10 $   |  
| $ 2 $    | $ 5\times 10^4 $   |  $5\times 10^4$ | $30$ | $ 15 $   |  
| $ 3 $    | $ 10^5$ | $10^4$ | $10^9$  | $ 30 $   |  
| $ 4 $    | $ 10^5$ | $10^5$ | $10^9$ | $  45 $   |    



---

---
title: "[PA 2017] 抄作业"
layout: "post"
diff: 提高+/省选-
pid: P11807
tag: ['2017', '二分', '可持久化线段树', '哈希 hashing', 'PA（波兰）']
---
# [PA 2017] 抄作业
## 题目背景


译自 [PA 2017](https://sio2.mimuw.edu.pl/c/pa-2017-1/) R3T2。

TL=5~10s，ML=512MB。

「你抄就抄吧，但是稍微改改，别和我的一模一样就行。」

## 题目描述

有 $m$ 个长度为 $n$ 的非负整数序列。第 $i$ 个序列的第 $j$ 项为 $a_{i,j}$。

给定 $a_{1,1},a_{1,2},\cdots,a_{1,n}$。

对于 $2\le i\le m$，给定 $p_i,x_i$，表示：

- $\forall 1\le j\le n$ 满足 $j\neq p_i$，有 $a_{i,j}=a_{i-1,j}$；
- $a_{i,p_i}=x_i$。

将这 $m$ 个序列以字典序为第一关键字，编号为第二关键字排序，输出排序后的序列编号。

## 输入格式

第一行，两个正整数 $n,m$。

第二行，$n$ 个非负整数 $a_{1,1},a_{1,2},\cdots,a_{1,n}$。

接下来 $(m-1)$ 行，第 $i$ 行两个整数 $p_{i+1},x_{i+1}$。
## 输出格式

输出一行 $m$ 个正整数，第 $i$ 个数表示排名为 $i$ 的序列的编号。
## 样例

### 样例输入 #1
```
5 8
4 2 1 7 3
3 6
1 2
2 5
5 5
1 5
1 4
1 5
```
### 样例输出 #1
```
3 4 5 1 2 7 6 8
```
## 提示

- $1\le n\le 5\times 10^5$；
- $2\le m\le 5\times 10^5$；
- $0\le a_{1,i},x_i\le 10^9$；
- $1\le p_i\le n$。


---

---
title: "「RiOI-6」flos"
layout: "post"
diff: 提高+/省选-
pid: P12393
tag: ['倍增', '洛谷原创', 'O2优化', '可持久化线段树', '洛谷比赛']
---
# 「RiOI-6」flos
## 题目背景

![](bilibili:BV1Gi4y1g77Q)

即使是像萝卜这样不起眼的小木头，也有被人喜欢的日子呢！

帽子的表白真是突如其来，小萝卜拼尽全力才战胜了自己上扬的嘴角，没有在上课划水的时候笑出来。

今年的 2.14，终于！可以！两个人过了！
## 题目描述

帽子要摘一些小萝卜最喜欢的花装点礼物。

小萝卜最喜欢的花长在一棵根为 $1$ 的树上，其中每个节点都有一朵花。当帽子从点 $u$ 开始摘花时，花的芳香度 $w_v$ 定义为 $\operatorname{dis}(u,v)$，也即 $u$ 到 $v$ 的最短距离。帽子只能摘下一朵花。

帽子只有 $t$ 秒的时间。具体的，他从 $u$ 开始沿着边移动，当他向上爬一条边（即**远离根**）时消耗 $1$ 单位时间，向下滑一条边（即**接近根**）时不消耗时间，全过程中剩余时间不能少于 $0$。

小萝卜有 $q$ 个问题，每次形如：帽子从点 $x_i$ 出发，有 $t_i$ 时间，摘的花的最大芳香度是多少。各个询问相互独立。

特别的，有时候小萝卜会在帽子摘完花后才会问下一个问题，所以在一些测试点中你需要强制在线。
## 输入格式

第一行两个正整数 $n,q,d$，表示树的节点个数、询问个数、与是否强制在线。

接下来 $n-1$ 行，每行两个正整数 $u_i,v_i$，表示树上 $u_i,v_i$ 之间有一条边。

接下来 $q$ 行，每行两个非负整数 $x_i,t_i$，表示一组询问。特别的，若 $d=1$，设上一组询问的答案为 $ans$（第一组询问为 $0$），你需要将 $x_i,t_i$ 异或上 $ans$ 得到真实询问。
## 输出格式

$q$ 行每行一个非负整数，表示每个询问的答案。
## 样例

### 样例输入 #1
```
5 3 0
1 2
1 3
3 4
4 5
1 2
1 4
2 2

```
### 样例输出 #1
```
2
3
3

```
### 样例输入 #2
```
10 5 1
1 2
1 3
3 4
2 5
4 6
4 7
7 8
8 9
9 10
1 0
4 2
2 4
2 1
8 0

```
### 样例输出 #2
```
0
4
3
2
8

```
## 提示

#### 【样例解释】

对于样例 $1$，三个询问分别如下：

- 从 $1$ 出发，体力值为 $2$。此时能摘下的其中一朵芳香度最大的花是 $4$，芳香度为 $2$。帽子可以向上爬 $2$ 条边到达 $4$。
- 从 $1$ 出发，体力值为 $4$。此时能摘下的其中一朵芳香度最大的花是 $5$，芳香度为 $3$。帽子可以向上爬 $3$ 条边到达 $5$。
- 从 $2$ 出发，体力值为 $2$。此时能摘下的其中一朵芳香度最大的花是 $4$，芳香度为 $3$。帽子可以先向下滑一条边到 $1$，再向上爬 $2$ 条边到达 $4$。

对于样例 $2$，暂时不能给你一个明确的答复。

#### 【数据范围】

**本题开启捆绑测试。**

|子任务|分数|$n,q\le$|$d=$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$20$|$10^3$|$0$||
|$2$|$10$|$2\times10^5$|$0$|$\forall i,u_i+1=v_i$|
|$3$|$20$|$2\times10^5$|$0$|$\forall i,t_i=n$|
|$4$|$20$|$2\times10^5$|$0$||
|$5$|$30$|$2\times10^5$|$1$||

对于 $100\%$ 的数据，$1\le n,q\le 2\times10^5,d\in\{0,1\},1\le x_i\le n,0\le t_i\le n$。


---

---
title: "高级打字机"
layout: "post"
diff: 提高+/省选-
pid: P1383
tag: ['倍增', '福建省历届夏令营', '可持久化线段树', '可持久化']
---
# 高级打字机
## 题目描述

早苗入手了最新的高级打字机。最新款自然有着与以往不同的功能，那就是它具备撤销功能，厉害吧。

请为这种高级打字机设计一个程序，支持如下 $3$ 种操作：

1. `T x`：Type 操作，表示在文章末尾打下一个小写字母 $x$。
2. `U x`：Undo 操作，表示撤销最后的 $x$ 次修改操作。
3. `Q x`：Query 操作，表示询问当前文章中第 $x$ 个字母并输出。请注意 Query 操作并不算修改操作。

文章一开始可以视为空串。
## 输入格式

第 $1$ 行：一个整数 $n$，表示操作数量。

以下 $n$ 行，每行一个命令。保证输入的命令合法。
## 输出格式

每行输出一个字母，表示 Query 操作的答案。


## 样例

### 样例输入 #1
```
7
T a
T b
T c
Q 2
U 2
T c
Q 2

```
### 样例输出 #1
```
b
c

```
## 提示

对于前 $20\%$ 的数据，$n\le 200$。

对于前 $50\%$ 的数据，保证 Undo 操作不会撤销 Undo 操作。

对于 $100\%$ 的数据，$n\le 10^5$。


---

---
title: "[SDOI2009] HH的项链"
layout: "post"
diff: 提高+/省选-
pid: P1972
tag: ['2009', '各省省选', '树状数组', '山东', 'O2优化', '可持久化线段树', '前缀和', '离线处理']
---
# [SDOI2009] HH的项链
## 题目描述

HH 有一串由各种漂亮的贝壳组成的项链。HH 相信不同的贝壳会带来好运，所以每次散步完后，他都会随意取出一段贝壳，思考它们所表达的含义。HH 不断地收集新的贝壳，因此，他的项链变得越来越长。  

有一天，他突然提出了一个问题：某一段贝壳中，包含了多少种不同的贝壳？这个问题很难回答…… 因为项链实在是太长了。于是，他只好求助睿智的你，来解决这个问题。

## 输入格式

一行一个正整数 $n$，表示项链长度。   
第二行 $n$ 个正整数 $a_i$，表示项链中第 $i$ 个贝壳的种类。

第三行一个整数 $m$，表示 HH 询问的个数。   
接下来 $m$ 行，每行两个整数 $l,r$，表示询问的区间。

## 输出格式

输出 $m$ 行，每行一个整数，依次表示询问对应的答案。

## 样例

### 样例输入 #1
```
6
1 2 3 4 3 5
3
1 2
3 5
2 6

```
### 样例输出 #1
```
2
2
4
```
## 提示

【数据范围】  

对于 $20\%$ 的数据，$1\le n,m\leq 5000$；   
对于 $40\%$ 的数据，$1\le n,m\leq 10^5$；   
对于 $60\%$ 的数据，$1\le n,m\leq 5\times 10^5$；  
对于 $100\%$ 的数据，$1\le n,m,a_i \leq 10^6$，$1\le l \le r \le n$。

本题可能需要较快的读入方式，最大数据点读入数据约 20MB


---

---
title: "[SDOI2008] 郁闷的小 J"
layout: "post"
diff: 提高+/省选-
pid: P2464
tag: ['2008', '莫队', '各省省选', '树状数组', '可持久化线段树']
---
# [SDOI2008] 郁闷的小 J
## 题目描述

小 J 是国家图书馆的一位图书管理员，他的工作是管理一个巨大的书架。虽然他很能吃苦耐劳，但是由于这个书架十分巨大，所以他的工作效率总是很低，以致他面临着被解雇的危险，这也正是他所郁闷的。

具体说来，书架由 $N$ 个书位组成，编号从 $1$ 到 $N$。每个书位放着一本书，每本书有一个特定的编码。

小 J 的工作有两类：

1. 图书馆经常购置新书，而书架任意时刻都是满的，所以只得将某位置的书拿掉并换成新购的书。

2. 小 J 需要回答顾客的查询，顾客会询问某一段连续的书位中某一特定编码的书有多少本。

例如，共 $5$ 个书位，开始时书位上的书编码为 $1, 2, 3, 4, 5$。

一位顾客询问书位 $1$ 到书位 $3$ 中编码为“$2$”的书共多少本，得到的回答为：$1$。

一位顾客询问书位 $1$ 到书位 $3$ 中编码为“$1$”的书共多少本，得到的回答为：$1$。

此时，图书馆购进一本编码为“$1$”的书，并将它放到 $2$ 号书位。

一位顾客询问书位 $1$ 到书位 $3$ 中编码为“$2$”的书共多少本，得到的回答为：$0$。

一位顾客询问书位 $1$ 到书位 $3$ 中编码为“$1$”的书共多少本，得到的回答为：$2$。

……

你的任务是写一个程序来回答每个顾客的询问。
## 输入格式

第一行两个整数 $N, M$，表示一共 $N$ 个书位，$M$ 个操作。

接下来一行共 $N$ 个整数数 $A_1, A_2, \ldots , A_N$，$A_i$ 表示开始时位置 $i$ 上的书的编码。

接下来 $M$ 行，每行表示一次操作，每行开头一个字符。

若字符为 `C`，表示图书馆购进新书，后接两个整数 $A, P$（$1 \le A \le N$），表示这本书被放在位置 $A$ 上，以及这本书的编码为 $P$。

若字符为 `Q`，表示一个顾客的查询，后接三个整数 $A, B, K$（$1 \le A \le B \le N$），表示查询从第 $A$ 书位到第 $B$ 书位（包含 $A$ 和 $B$）中编码为 $K$ 的书共多少本。
## 输出格式

对每一个顾客的查询，输出一个整数，表示顾客所要查询的结果。
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
Q 1 3 2
Q 1 3 1
C 2 1
Q 1 3 2
Q 1 3 1

```
### 样例输出 #1
```
1
1
0
2

```
## 提示

对于 $40 \%$ 的数据，$1 \le N, M \le 5000$。

对于 $100 \%$ 的数据，$1 \le N, M \le {10}^5$。

对于 $100 \%$ 的数据，所有出现的书的编码为不大于 $2^{31} - 1$ 的正数。


---

---
title: "[POI 2014] KUR-Couriers"
layout: "post"
diff: 提高+/省选-
pid: P3567
tag: ['2014', '线段树', 'POI（波兰）', '可持久化线段树', '可持久化']
---
# [POI 2014] KUR-Couriers
## 题目描述

Byteasar works for the BAJ company, which sells computer games.

The BAJ company cooperates with many courier companies    that deliver the games sold by the BAJ company to its customers.

Byteasar is inspecting the cooperation of the BAJ company with the couriers.

He has a log of successive packages with the courier company that made the delivery    specified for each package.

He wants to make sure that no courier company had an unfair advantage over the others.

If a given courier company delivered more than half of all packages sent in some period of time,    we say that it dominated in that period.

Byteasar wants to find out which courier companies dominated in certain periods of time, if any.

Help Byteasar out!

Write a program that determines a dominating courier company or that there was none.

给一个数列，每次询问一个区间内有没有一个数出现次数超过一半

## 输入格式

The first line of the standard input contains two integers, ![](http://main.edu.pl/images/OI21/kur-en-tex.1.png) and ![](http://main.edu.pl/images/OI21/kur-en-tex.2.png) (![](http://main.edu.pl/images/OI21/kur-en-tex.3.png)),    separated by a single space, that are the number of packages shipped by the BAJ company    and the number of time periods for which the dominating courier is to be determined, respectively.

The courier companies are numbered from ![](http://main.edu.pl/images/OI21/kur-en-tex.4.png) to (at most) ![](http://main.edu.pl/images/OI21/kur-en-tex.5.png).

The second line of input contains ![](http://main.edu.pl/images/OI21/kur-en-tex.6.png) integers, ![](http://main.edu.pl/images/OI21/kur-en-tex.7.png) (![](http://main.edu.pl/images/OI21/kur-en-tex.8.png)),    separated by single spaces;    ![](http://main.edu.pl/images/OI21/kur-en-tex.9.png) is the number of the courier company that delivered the ![](http://main.edu.pl/images/OI21/kur-en-tex.10.png)-th package (in shipment chronology).

The ![](http://main.edu.pl/images/OI21/kur-en-tex.11.png) lines that follow specify the time period queries, one per line.

Each query is specified by two integers, ![](http://main.edu.pl/images/OI21/kur-en-tex.12.png) and ![](http://main.edu.pl/images/OI21/kur-en-tex.13.png) (![](http://main.edu.pl/images/OI21/kur-en-tex.14.png)),    separated by a single space.

These mean that the courier company dominating in the period between the shipments of the    ![](http://main.edu.pl/images/OI21/kur-en-tex.15.png)-th and the ![](http://main.edu.pl/images/OI21/kur-en-tex.16.png)-th package, including those, is to be determined.

In tests worth ![](http://main.edu.pl/images/OI21/kur-en-tex.17.png) of total score, the condition ![](http://main.edu.pl/images/OI21/kur-en-tex.18.png) holds,    and in tests worth ![](http://main.edu.pl/images/OI21/kur-en-tex.19.png) of total score ![](http://main.edu.pl/images/OI21/kur-en-tex.20.png).

## 输出格式

The answers to successive queries should be printed to the standard output, one per line.

(Thus a total of ![](http://main.edu.pl/images/OI21/kur-en-tex.21.png) lines should be printed.)    Each line should hold a single integer: the number of the courier company that dominated    in the corresponding time period, or ![](http://main.edu.pl/images/OI21/kur-en-tex.22.png) if there was no such company.

## 样例

### 样例输入 #1
```
7 5
1 1 3 2 3 4 3
1 3
1 4
3 7
1 7
6 6

```
### 样例输出 #1
```
1
0
3
0
4

```
## 题目翻译

给一个长度为 $n$ 的正整数序列 $a$。共有 $m$ 组询问，每次询问一个区间 $[l,r]$ ，是否存在一个数在 $[l,r]$ 中出现的次数严格大于一半。如果存在，输出这个数，否则输出 $0$。

$1 \leq n,m \leq 5 \times 10^5$，$1 \leq a_i \leq n$。


---

---
title: "【模板】可持久化线段树 2"
layout: "post"
diff: 提高+/省选-
pid: P3834
tag: ['线段树', '离散化', 'O2优化', '可持久化线段树', '可持久化']
---
# 【模板】可持久化线段树 2
## 题目背景

这是个非常经典的可持久化权值线段树入门题——静态区间第 $k$ 小。

**数据已经过加强，请使用可持久化权值线段树。同时请注意常数优化**。

## 题目描述

如题，给定 $n$ 个整数构成的序列 $a$，将对于指定的闭区间 $[l, r]$ 查询其区间内的第 $k$ 小值。

## 输入格式

第一行包含两个整数，分别表示序列的长度 $n$ 和查询的个数 $m$。  
第二行包含 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个元素 $a_i$。   
接下来 $m$ 行每行包含三个整数 $ l, r, k$ , 表示查询区间 $[l, r]$ 内的第 $k$ 小值。

## 输出格式

对于每次询问，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5 5
25957 6405 15770 26287 26465 
2 2 1
3 4 1
4 5 1
1 2 2
4 4 1

```
### 样例输出 #1
```
6405
15770
26287
25957
26287

```
## 提示

### 样例 1 解释

$n=5$，数列长度为 $5$，数列从第一项开始依次为$\{25957, 6405, 15770, 26287, 26465\}$。

- 第一次查询为 $[2, 2]$ 区间内的第一小值，即为 $6405$。
- 第二次查询为 $[3, 4]$ 区间内的第一小值，即为 $15770$。
- 第三次查询为 $[4, 5]$ 区间内的第一小值，即为 $26287$。
- 第四次查询为 $[1, 2]$ 区间内的第二小值，即为 $25957$。
- 第五次查询为 $[4, 4]$ 区间内的第一小值，即为 $26287$。


### 数据规模与约定

- 对于 $20\%$ 的数据，满足 $1 \leq n,m \leq 10$。
- 对于 $50\%$ 的数据，满足 $1 \leq n,m \leq 10^3$。
- 对于 $80\%$ 的数据，满足 $1 \leq n,m \leq 10^5$。
- 对于 $100\%$ 的数据，满足 $1 \leq n,m \leq 2\times 10^5$，$0\le a_i \leq 10^9$，$1 \leq l \leq r \leq n$，$1 \leq k \leq r - l + 1$。


---

---
title: "【模板】可持久化线段树 1（可持久化数组）"
layout: "post"
diff: 提高+/省选-
pid: P3919
tag: ['线段树', '平衡树', '递归', 'O2优化', '可持久化线段树', '可持久化']
---
# 【模板】可持久化线段树 1（可持久化数组）
## 题目背景

**UPDATE : 最后一个点时间空间已经放大**

2021.9.18 增添一组 hack 数据 by @panyf

标题即题意

有了可持久化数组，便可以实现很多衍生的可持久化功能（例如：可持久化并查集）

## 题目描述

如题，你需要维护这样的一个长度为 $ N $ 的数组，支持如下几种操作


1. 在某个历史版本上修改某一个位置上的值

2. 访问某个历史版本上的某一位置的值


此外，每进行一次操作（**对于操作2，即为生成一个完全一样的版本，不作任何改动**），就会生成一个新的版本。版本编号即为当前操作的编号（从1开始编号，版本0表示初始状态数组）


## 输入格式

输入的第一行包含两个正整数 $ N, M $， 分别表示数组的长度和操作的个数。

第二行包含$ N $个整数，依次为初始状态下数组各位的值（依次为 $ a_i $，$ 1 \leq i \leq N $）。

接下来$ M $行每行包含3或4个整数，代表两种操作之一（$ i $为基于的历史版本号）：

1. 对于操作1，格式为$ v_i \ 1 \ {loc}_i \ {value}_i $，即为在版本$ v_i $的基础上，将 $ a_{{loc}_i} $ 修改为 $ {value}_i $。

2. 对于操作2，格式为$ v_i \ 2 \ {loc}_i $，即访问版本$ v_i $中的 $ a_{{loc}_i} $的值，注意：**生成一样版本的对象应为 $v_i$**。

## 输出格式

输出包含若干行，依次为每个操作2的结果。

## 样例

### 样例输入 #1
```
5 10
59 46 14 87 41
0 2 1
0 1 1 14
0 1 1 57
0 1 1 88
4 2 4
0 2 5
0 2 4
4 2 1
2 2 2
1 1 5 91
```
### 样例输出 #1
```
59
87
41
87
88
46
```
## 提示

数据规模：

对于30%的数据：$ 1 \leq N, M \leq {10}^3 $

对于50%的数据：$ 1 \leq N, M \leq {10}^4 $

对于70%的数据：$ 1 \leq N, M \leq {10}^5 $

对于100%的数据：$ 1 \leq N, M \leq {10}^6, 1 \leq {loc}_i \leq N, 0 \leq v_i < i, -{10}^9 \leq a_i, {value}_i  \leq {10}^9$

**经测试，正常常数的可持久化数组可以通过，请各位放心**

~~数据略微凶残，请注意常数不要过大~~

~~另，此题I/O量较大，如果实在TLE请注意I/O优化~~

询问生成的版本是指你访问的那个版本的复制

样例说明：

一共11个版本，编号从0-10，依次为：

\* **0** : 59 46 14 87 41

\* **1** : 59 46 14 87 41

\* **2** : 14 46 14 87 41

\* **3** : 57 46 14 87 41

\* **4** : 88 46 14 87 41

\* **5** : 88 46 14 87 41

\* **6** : 59 46 14 87 41

\* **7** : 59 46 14 87 41

\* **8** : 88 46 14 87 41

\* **9** : 14 46 14 87 41

\* **10** : 59 46 14 87 91



---

---
title: "[TJOI2013] 奖学金"
layout: "post"
diff: 提高+/省选-
pid: P3963
tag: ['贪心', '2013', '各省省选', '堆', '枚举', '优先队列', '可持久化线段树', '天津']
---
# [TJOI2013] 奖学金
## 题目背景

小张最近发表了一篇论文，有一个神秘人物要给小张学院发奖学金。
## 题目描述

小张学院有 $c$ 名学生，第 $i$ 名学生的成绩为 $a_i$，要获得的奖学金金额为 $b_i$。  
要从这 $c$ 名学生中挑出 $n$ 名学生发奖学金。这个神秘人物爱好奇特，他希望得到奖学金的同学的**成绩**的**中位数**尽可能大，但同时，他们的**奖学金总额**不能超过 $f$。

## 输入格式

第一行有三个整数，分别表示要挑出的学生人数 $n$，学生总人数 $c$ 和奖学金总额的最大值 $f$，**保证 $n$ 为奇数**。  

第 $2$ 到第 $(c + 1)$ 行，每行两个整数，第 $(i + 1)$ 行的整数依次表示第 $i$ 名学生的成绩 $a_i$ 和如果要给他发奖学金，则需要发的金额数 $b_i$。
## 输出格式

输出一行一个整数表示答案。如果无法满足神秘人的条件，请输出 $-1$。
## 样例

### 样例输入 #1
```
3 5 70
30 25
50 21
20 20
5 18
35 30

```
### 样例输出 #1
```
35
```
### 样例输入 #2
```
5 6 9
4 0
4 1
6 3
8 0
10 4
10 5

```
### 样例输出 #2
```
6
```
## 提示

### 样例 1 解释

选择成绩为 $5$，$35$，$50$ 的三名同学，奖金总额为 $18 + 30 + 21 = 69$。

### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n \leq 10^3$，$c \leq 2 \times 10^3$。
- 对于 $100\%$ 的数据，保证 $3 \leq n  \leq 10^5$，$n \leq c \leq 2 \times 10^5$，$0 \leq f \leq 2\times 10^9$，$0 \leq a_i \leq 2 \times 10^9$，$0 \leq b_i \leq 10^5$。


---

---
title: "[HEOI2012] 采花"
layout: "post"
diff: 提高+/省选-
pid: P4113
tag: ['2012', '各省省选', '树状数组', '河北', '排序', '可持久化线段树', '前缀和']
---
# [HEOI2012] 采花
## 题目描述

萧薰儿是古国的公主，平时的一大爱好是采花。

今天天气晴朗，阳光明媚，公主清晨便去了皇宫中新建的花园采花。

花园足够大，容纳了 $n$ 朵花，共有 $c$ 种颜色，用整数 $1 \sim c$ 表示。且花是排成一排的，以便于公主采花。公主每次采花后会统计采到的花的颜色数，颜色数越多她会越高兴。同时，她有一癖好，她不允许最后自己采到的花中，某一颜色的花只有一朵。为此，公主每采一朵花，要么此前已采到此颜色的花，要么有相当正确的直觉告诉她，她必能再次采到此颜色的花。

由于时间关系，公主只能走过花园连续的一段进行采花，便让女仆福涵洁安排行程。福涵洁综合各种因素拟定了 $m$ 个行程，然后一一向你询问公主能采到的花共有几种不同的颜色。
## 输入格式

输入的第一行是三个用空格隔开的整数，分别代表花的个数 $n$，花的颜色数 $c$，以及行程数 $m$。

输入的第二行是 $n$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 朵花的颜色 $x_i$。

第 $3$ 行到第 $(m + 2)$ 行，每行两个整数 $l, r$，第 $(i + 2)$ 行的数字代表第 $i$ 次行程为第 $l$ 到第 $r$ 朵花。
## 输出格式

共输出 $m$ 行，每行一个整数。第 $i$ 行的整数代表第 $i$ 次行程公主能采到的花共有几种不同的颜色。
## 样例

### 样例输入 #1
```
5 3 5
1 2 2 3 1
1 5
1 2
2 2
2 3
3 5
```
### 样例输出 #1
```
2
0
0
1
0

```
## 提示

#### 输入输出样例 $1$ 解释

共有五朵花，颜色分别为 $1,~2,~2,~3,~1$。

对于第一次行程，公主采花的区间为 $[1, 5]$，可以采位置 $1,~2,~3,~5$ 处的花，共有 $1$ 和 $2$ 两种不同的颜色。

对于第二次行程，公主采花的区间为 $[1, 2]$，但是颜色为 $1$ 和 $2$ 的花都只出现了一次，因此公主无花可采。

对于第三次行程，公主采花的区间为 $[2, 2]$，但是颜色为 $2$ 的花只出现了一次，公主无花可采。

对于第四次行程，公主采花的区间为 $[2, 3]$，可以采 $2,~3$ 位置的花，只有 $2$ 这一种颜色。

对于第五次行程，公主采花的区间为 $[3,5]$，但是颜色为 $1, 2, 3$ 的花都只出现了一次，因此公主无花可采。

#### 数据范围与约定

**本题采用多测试点捆绑测试，共有两个子任务**。

对于子任务 $1$，分值为 $100$ 分，保证 $1 \leq n, c, m \leq 3 \times 10^5$。

对于子任务 $2$，分值为 $100$ 分，保证 $1 \leq n, c, m \leq 2 \times 10^6$。

对于全部的测试点，保证 $1 \leq x_i \leq c$，$1 \leq l \leq r \leq n$。


---

---
title: "【模板】子序列自动机"
layout: "post"
diff: 提高+/省选-
pid: P5826
tag: ['字符串', '线段树', 'O2优化', '可持久化', '有限状态自动机']
---
# 【模板】子序列自动机
## 题目背景

本题中，若 $x$ 是 $y$ 的子序列，则等价于存在一个**单调递增**序列 $z$，满足 $|z| = |x|$，$z_{|x|} \leq |y|$，且 $\forall i \in [1, ~|x|],~y_{z_i} = x_i$。其中 $|x|,~|y|,~|z|$ 分别代表序列 $x,~y,~z$ 的长度，$x_i,~y_i,~z_i$ 分别代表序列 $x,~y,~z$ 的第 $i$ 项。

这是一道在 ``yLOI2020`` 备选题里被毙掉的题目。
## 题目描述

给定一个长度为 $n$ 的正整数序列 $a$ ，有 $q$ 次询问，第 $i$ 次询问给定一个长度为 $L_i$ 的序列 $b_i$，请你判断 $b_i$ 是不是 $a$ 的子序列。序列 $a$ 和所有 $b_i$ 中的元素都不大于一个给定的正整数 $m$。
## 输入格式

每个测试点有且仅有一组数据。

输入的第一行是四个用空格隔开的整数，分别代表 $type,~n,~q,~m$。其中 $type$ 代表测试点所在的子任务编号，其余变量的含义见【题目描述】。

输入的第二行是 $n$ 个用空格隔开的整数，第 $i$ 个数字代表序列 $a$ 的第 $i$ 个元素 $a_i$。

第 $3$ 行至第 $(q + 2)$ 行，每行代表一次询问。第 $(i + 2)$ 行的输入格式为：

- 第 $(i + 2)$ 行的行首有一个整数 $l_i$，代表第 $i$ 次询问的序列长度。一个空格后有 $l_i$ 个用空格隔开的整数。该行的第 $(j + 1)$ 个整数代表序列 $b_i$ 的第 $j$ 个元素 $b_{i, j}$。
## 输出格式

对于每次询问，输出一行一个字符串，若给定的序列是 $a$ 的子序列，则输出 `Yes`，否则输出 `No`。
## 样例

### 样例输入 #1
```
0 5 5 5
1 3 2 2 4
3 1 5 2
2 3 2
3 1 2 3
3 1 2 4
5 1 3 2 2 4

```
### 样例输出 #1
```
No
Yes
No
Yes
Yes
```
## 提示

#### 样例 1 解释

- 对于第一次询问，原序列中没有 $5$，所以给定序列显然不是原序列的子序列。
- 对于第二次询问，存在两个合法的序列 $z$，分别是 $\{2,~3\}$ 和 $\{2,~4\}$。即 $a_{2} = b_{2, 1},~a_3 = b_{2, 2}$ 或 $a_2 = b_{2, 1},~a_{4} = b_{2, 2}$。这里 $b_{i, j}$ 代表序列 $b_i$ 的第 $j$ 个元素，序列 $z$ 的含义见【题目背景】，下同。
- 对于第三次询问，不存在合法的序列 $z$。
- 对于第四次询问，存在两个合法的序列 $z$，分别是 $\{1,~3,~5\}$ 和 $\{1,~4,~5\}$。
- 对于第五次询问，存在一个合法的序列 $z$，为 $\{1,~2,~3,~4,~5\}$。

#### 数据范围与约定

**本题采用多测试点捆绑测试，共有 3 个子任务**。

- Subtask 1（20 points）：$type = 1$，$n, q, m \leq 100$，$\sum_{i = 1}^{q} l_i \leq 10^3$。
- Subtask 2（35 points）：$type = 2$，$n,q \leq 10^5$，$m \leq 26$，$\sum_{i = 1}^{q} l_i \leq 10^6$。
- Subtask 3（45 points）：$type = 3$，$n,q,m \leq 10^5$，$\sum_{i = 1}^q L_i \leq 10^6$。

对于全部的测试点，保证 $1 \leq n, m, q \leq 10^5$，$1 \leq a_i, b_{i, j} \leq m$，$1 \leq l_i \leq 10^6$，$\sum_{i = 1}^{q} l_i \leq 10^6$。


### 提示

- 请注意常数因子对程序效率造成的影响。
- 本题输入规模较大，请注意数据读入对程序效率造成的影响。
- 请注意输入第一行的顺序为先输入询问次数 $q$，再输入序列元素最大值 $m$。


---

---
title: "[YsOI2020] 幼儿园"
layout: "post"
diff: 提高+/省选-
pid: P6592
tag: ['图论', '二分', '可持久化线段树']
---
# [YsOI2020] 幼儿园
## 题目描述

Ysuperman 热爱在 TA 的幼儿园里散步，为了更方便散步， TA 把幼儿园抽象成 $n$ 个点，$m$ 条边的**有向图**。 散步得多了， TA 就给了每一条边**无与伦比**的亲密程度：$1,2,\cdots,m$，越大代表越亲密。 TA 也给了每一个点无与伦比的编号：$1,2,\cdots,n$，其中 $1$ 代表着幼儿园大门，但是每个**点是没有亲密程度的**。

接下来 $k$ 天，Ysuperman 每天会有一次散步计划。具体而言， TA 希望从 $x_i$ 号点出发，只经过**亲密程度属于区间 $[l_i,r_i]$ 的边**，走到幼儿园大门 $1$ 号点，期间经过的边的亲密程度必须**单调递减**，不然会因为 TA 有强迫症而不能回家。


Ysuperman 看着自己刚刚画的草稿脑子一团浆糊， TA 发现 TA 始终没有办法规划出这么多合理路线，现在 TA 想请你帮 TA 。具体而言，对于每一天的计划，如果可行，则输出 `1`，反之输出 `0`。

当然啦，有的时候 Ysuperman 很着急，需要你立马回复，有的时候 TA 可以等等你，先把所有问题问完再等你回复。
## 输入格式

第一行三个整数 $n,m,k,w$，分别表示节点个数、边个数、Ysuperman 的计划个数，和 Ysuperman 的焦急程度，此处的 $w$ 在后续输入中有用。

此后 $m$ 行的第 $i$ 行有两个整数 $u_i,v_i$，表示 Ysuperman 的幼儿园里有一条 $u_i$ 号点到 $v_i$ 号点的单向边，且**亲密程度为** $i$。

此后 $k$ 行的第 $i$ 行有三个整数 $x_i,l_i,r_i$，表示 Ysuperman 的第 $i$ 个计划。

此处如果 $w=0$，则 $x_i,l_i,r_i$ 为明文，可以直接使用。

如果 $w=1$，则 $x_i,l_i,r_i$ 为密文，你需要将它解密。解密操作是：令 $L$ 为之前所有询问的输出之和（没有询问过则为 $0$），你需要将 $x_i ,l_i,r_i$ 都异或 $L$。
## 输出格式

$k$ 行，每行只可能是 `1` 或 `0`，第 $i$ 行的数表示第 $i$ 个计划是否可行。
## 样例

### 样例输入 #1
```
5 7 5 0
3 2
1 2
4 3
5 4
3 1
5 3
5 1
3 1 4
1 2 2
5 5 6
4 5 7
2 1 7

```
### 样例输出 #1
```
0
1
1
0
0

```
### 样例输入 #2
```
5 12 10 0
4 2
4 2
5 3
3 3
1 5
1 4
4 4
2 4
5 3
1 5
2 2
4 1
4 3 5
4 2 3
1 4 5
3 1 8
3 1 4
3 5 5
2 1 12
4 10 12
2 5 5
1 1 3

```
### 样例输出 #2
```
0
0
1
0
0
0
0
1
0
1

```
### 样例输入 #3
```
5 12 10 1
4 2
4 2
5 3
3 3
1 5
1 4
4 4
2 4
5 3
1 5
2 2
4 1
4 3 5
4 2 3
1 4 5
2 0 9
2 0 5
2 4 4
3 0 13
5 11 13
0 7 7
3 3 1
```
### 样例输出 #3
```
0
0
1
0
0
0
0
1
0
1

```
## 提示

### 样例说明

#### 样例说明 $1$

![](https://cdn.luogu.com.cn/upload/image_hosting/wxji6w6f.png)

对于第 $2$ 条计划，Ysuperman 已经站在门口，所以计划可行。

对于第 $3$ 条计划，Ysuperman 只能通过路径 $5 \overset{6}{\rightarrow}3 \overset{5}{\rightarrow} 1$。（箭头上方数字表示的是边的亲密程度）。

其他计划都是不可行的。

#### 样例说明 $3$

样例三为加密后的样例二。

----

### 数据范围

**本题采用捆绑测试。**

| $\mathrm{subtask}$ |     $n$     |       $m$        |        $k$        |  特殊性质   | 分数  |
| :----------------: | :---------: | :--------------: | :---------------: | :---------: | :---: |
|        $1 $        |   $\le17$   |     $\le17$      | $\le 2\cdot 10^5$ |      /      | $ 5$  |
|        $2$         |  $\le500$   |     $\le500$     |     $\le500 $     |      /      | $17$  |
|        $3 $        | $\le 3000$  |   $\le 3000 $    |    $\le 3000 $    |      /      | $18 $ |
|       $ 4 $        |  $\le10^5$  | $\le2\cdot10^5$  |  $\le2\cdot10^5$  |   $v_i=1$   | $13$  |
|        $5 $        | $\le 10^5$  | $\le 2\cdot10^5$ |    $\le 10^5$     | $l_i=1,w=0$ | $ 7 $ |
|        $6$         | $\le10^5 $  | $\le2\cdot10^5$  |    $\le 10^5$     |   $w=0 $    | $13 $ |
|        $7$         | $ \le 10^5$ | $\le 2\cdot10^5$ | $\le 2\cdot10^5$  |      /      | $27$  |

对于 $100\%$ 的数据，满足 $1 \le n \le 10^5 ,1 \le m \le 2\cdot10^5 ,0 \le k \le 2\cdot10^5$。

$w\in\{0,1\},1 \le u_i,v_i \le n$。

$x_i,l_i,r_i$ 在解密后保证 $1\le x \le n ,1 \le l_i,r_i \le m $。

### 提示

**不保证不出现重边自环，不保证图联通**。


---

---
title: "[YsOI2020] 制高"
layout: "post"
diff: 提高+/省选-
pid: P6655
tag: ['动态规划 DP', '树状数组', '可持久化线段树']
---
# [YsOI2020] 制高
## 题目背景

Ysuperman 特别喜欢玩战略游戏。
## 题目描述

游戏地图是一棵 $n$ 个点的有根树，根节点是 $1$ ，除节点 $1$ 外其他节点都有唯一的父亲节点。

每个节点有一个高度，第 $i$ 个节点的高度为 $h_i$ ，我们认为一个节点 $v$ 是“制高点”，当且仅当 $v$ 是根节点或者其父亲节点 $u$ 是“制高点”并且 $h_v\ge h_u$ 。

但是， Ysuperman 并不知道每个节点的父亲具体是哪个，只知道它的父亲编号可能在的区间，其中，节点 $i$ 的父亲可能在的编号范围为 $[l_i,r_i]$ ，保证 $1\le l_i\le r_i<i$ 。

现在， Ysuperman 想知道对于**所有可能的情况**，“制高点”的数量之和是多少。

因为这个结果可能会很大，所以你只需要输出结果 $\bmod \ {998244353}$ 的值即可。
## 输入格式

输入共 $n+1$ 行。

第一行一个正整数 $n$ 。

接下来一行 $n$ 个非负整数，第 $i$ 个整数描述 $h_i$ 。

接下来 $n-1$ 行，每行两个正整数，分别描述 $l_2,r_2,\cdots,l_n,r_n$ 。

保证 $1\le l_i\le r_i<i$ 。
## 输出格式

一行一个整数，即答案。
## 样例

### 样例输入 #1
```
3
1 3 2
1 1
1 2

```
### 样例输出 #1
```
5

```
### 样例输入 #2
```
10
1 1 1 0 5 2 11 12 17 7
1 1
1 2
2 2
1 3
1 1
1 4
1 2
6 7
1 5

```
### 样例输出 #2
```
4044

```
### 样例输入 #3
```
50
1 0 0 6 2 5 0 2 16 15 14 8 20 22 23 21 7 24 27 17 1 13 39 40 31 38 40 16 25 48 2 0 15 7 0 47 58 11 22 54 11 78 30 32 31 35 44 56 59 85
1 1
2 2
1 2
2 3
3 3
1 6
2 6
3 5
5 9
3 4
1 4
3 12
1 12
5 7
5 13
1 10
7 9
4 11
12 12
16 17
3 9
8 15
15 16
1 19
9 10
10 12
8 10
4 10
6 13
10 13
11 30
11 21
2 30
13 23
4 24
32 34
8 29
4 22
2 26
29 33
28 38
18 31
19 36
15 32
8 14
15 32
4 33
30 45
8 25

```
### 样例输出 #3
```
904672069

```
## 提示

样例一解释：

共有两种情况，情况一： $2$ 的父亲节点是 $1$ ， $3$ 的父亲节点是 $1$ ，此时 $1,2,3$ 均是“制高点”；情况二： $2$ 的父亲节点是 $1$ ， $3$ 的父亲节点是 $2$ ，由于 $h_2>h_3$ ，所以 $3$ 不是“制高点”，此时 $1,2$ 均是“制高点”。

所以所有情况“制高点”数量的和为 $5$ 。

| $\text{测试点编号}$ |   $n$    | $\prod_{i=2}^n(r_i-l_i+1)$ | $\text{特殊性质}$ |
| :-----------------: | :------: | :------------------------: | :---------------: |
|      $1\sim 2$      |  $=10$   |         $\le 10^6$         |    $\text{无}$    |
|         $3$         | $= 10^5$ |         $\le 10^6$         |    $\text{无}$    |
|         $4$         | $= 10^5$ |             \\             | $h_i\le h_{i+1}$  |
|         $5$         | $= 10^5$ |             \\             |   $h_i>h_{i+1}$   |
|     $6\sim 12$      | $= 10^3$ |             \\             |    $\text{无}$    |
|     $13\sim 20$     | $=10^5$  |             \\             |    $\text{无}$    |

题目数据保证 $h_i$ 在 `int` 能表示的最大范围内， $1\le l_i\le r_i<i$ 。

题目并不难。


---

---
title: "「CGOI-1」收税"
layout: "post"
diff: 提高+/省选-
pid: P7768
tag: ['树状数组', 'Special Judge', 'O2优化', '可持久化线段树', '差分']
---
# 「CGOI-1」收税
## 题目背景

~~签到题~~

由于举办选丑大赛消耗了太多钱财，ac 决定派出 Push_Y 去收税。
## 题目描述

丑国由 $n$ 座城市组成，编号 $1$ 的为首都。这 $n$ 座城市由 $n-1$ 条长度为 $1$ 的双向道路连接。从编号为 $x$ 的城市出发，往**远离**首都的方向（即往儿子节点走），距离不超过 $h$ 的就是这座城市要收税的范围。

第 $i$ 座城市将要上缴 $a_i$ **元**的所得税。但由于收税官 Push_Y 很喜欢异或，因此每座城市最终上缴的所得税将是在其收税范围内每座城市**应缴税额**的异或和。

Push_Y 将向你提出 $m$ 个询问，他将问你城市 $x$ 在收税距离为 $h$ 时将收到多少**千元**的所得税。

**简化版题意：**

给定一棵 $n$ 个点的树，根节点为 $1$ 号点，第 $i$ 个点的点权为 $a_i$，$dep_u$ 表示 $u$ 点的深度，根节点的深度为 $1$，$q$ 次询问，每次给定两个整数 $x,h$，表示询问 $\bigoplus_{u\in son(x)\land dep_u-dep_x\le h}a_i$ 除以 $1000$ 后的值。

其中 $\bigoplus_{i=1}^ni$ 表示 $1\operatorname{xor} 2\operatorname{xor}\cdots\operatorname{xor} n$。

此处 $\land$ 是“且”，$\operatorname{xor}$ 是异或。
## 输入格式

第一行两个正整数 $n,m$，表示城市数和询问数。

第二行 $n$ 个正整数 $a_i$， 表示每座城市应缴的所得税额。

第三行 $n-1$ 个正整数，其中第 $i$ 个数 $f_i$ 表示城市 $i+1$ 与城市 $f_i$ 有一条路相连。

从第 $4$ 行开始 $m$ 行，每行两个正整数 $x,h$，表示一组询问。
## 输出格式

对于每组询问，输出一行，一个实数，表示这座城市收取的税额。

**答案保留三位小数。**
## 样例

### 样例输入 #1
```
6 3
604 545 402 378 25 13
1 2 2 3 3
1 2
3 0
2 4
```
### 样例输出 #1
```
0.149
0.402
0.733
```
### 样例输入 #2
```
6 3
6 5 4 3 2 1
1 2 2 3 3
1 2
3 0
2 4
```
### 样例输出 #2
```
0.004
0.004
0.001
```
## 提示

对于 $30\%$ 的数据，$1\le n,m\le 10^3$。

对于 $70\%$ 的数据，$1\le n,m\le5 \times 10^4$。其中有 $20\%$ 的数据是链。

对于 $100\%$ 的数据，$1\le n,m\le 10^6$，$1 \le a_i \le 10^9$，$1\le x \le n$，$0 \le h \le n$。


---

---
title: "「CGOI-1」丑国旅游"
layout: "post"
diff: 提高+/省选-
pid: P7770
tag: ['O2优化', '可持久化线段树']
---
# 「CGOI-1」丑国旅游
## 题目背景

丑国风景优美，是远近闻名的旅游胜地（并不）。来丑国旅游的人很多。
## 题目描述

丑国的一角排列着编号从 $1$ 到 $n$ 的 $n$ 个城市。当一个人在第 $i$ 个城市时，能且仅能走到第 $i+1$ 个城市。

第 $i$ 个城市中的人们最讨厌丑值为 $a_i$ 的人。当一个丑值为 $x$ 的人从第 $i$ 个城市走到第 $i+1$ 个城市时，他会获得 $|x-a_i|\times|x-a_{i+1}|$ 的舒适值。

现在有 $m$ 个人要来丑国旅游，第 $i$ 个人的丑值为 $x_i$，要从城市 $l_i$ 走到 $r_i$，问他得到的舒适值之和是多少。

**由于这个数可能很大，你需要求出对 $10^9+7$ 取模后的值**。

由于你不能预知到下一次旅游，我们会强制你在线。

**简化版题意：**

给出 $n$ 及 $n$ 个整数 $a_1,\,a_2,\,\dots,\,a_n$。

$m$ 次在线询问，每次询问给出 $x,\,l,\,r$，求 $\sum\limits_{i=l}^{r-1}|x-a_i|\times|x-a_{i+1}|$。
## 输入格式

第一行输入两个整数 $n,m$，分别表示城市数与旅游人数。

第二行输入 $n$ 个整数，第 $i$ 个数表示 $a_i$，含义如上所述。

接下来 $m$ 行，每行输入三个整数 $X,\,L,\,R$，记上一次的旅游的总舒适值对 $10^9+7$ 取模后为 $s$（若是第一次询问，则 $s=0$），则 $x_i=X\operatorname{xor}s,\;l_i=L\operatorname{xor}s,\;r_i=R\operatorname{xor}s$，其中 $\operatorname{xor}$ 表示异或，而 $x_i,\,l_i,\,r_i$ 的含义如上所述。
## 输出格式

输出 $m$ 行，第 $i$ 行的数表示第 $i$ 个人的总舒适值对 $10^9+7$ 取模后的值。
## 样例

### 样例输入 #1
```
5 2
1 2 3 4 5
1 1 3
6 1 7
```
### 样例输出 #1
```
2
0
```
## 提示

#### 样例说明：

对于第一次询问，从城 $1$ 走到城 $2$，获得舒适值为 $|1-1|\times|1-2|=0$；从城 $2$ 走到城 $3$，获得舒适值为 $|1-2|\times|1-3|=2$，故总舒适值为 $2$。

对于第二次询问，解密后的 $x,\,l,\,r$ 分别是 $4,3,5$。从城 $3$ 走到城 $4$，获得舒适值为 $|4-3|\times|4-4|=0$；从城 $4$ 走到城 $5$，舒适值为 $|4-4|\times|4-5|=0$，总舒适值为 $0$。

---

#### 数据范围：

**本题采用捆绑测试。**

| 编号 | 特殊限制 | 分值 |时限|
| :-: | :-: | :-: |:-:|
| Subtask0 | $n,\,m\le 10^4$ | 20pts |1s|
| Subtask1 | $a_i,\,x\le 10$ | 10pts |2s|
| Subtask2 | $a_i$ 单调递增 | 10pts |2s|
| Subtask3 | 无特殊限制 | 60pts |2s|

对于 $100\%$ 的数据，$1 \le n,\,m \le 3 \times 10^5$，$1 \le a_i,\,x_i \le 10^9$，$1 \le l_i < r_i \le n$。


---

---
title: "[蓝桥杯 2019 国 B] 第八大奇迹"
layout: "post"
diff: 提高+/省选-
pid: P8701
tag: ['2019', '可持久化线段树', '蓝桥杯国赛']
---
# [蓝桥杯 2019 国 B] 第八大奇迹
## 题目背景

在一条 R 河流域，繁衍着一个古老的名族 Z。他们世代沿河而居，也在河边发展出了璀璨的文明。

Z 族在 R 河沿岸修建了很多建筑，最近，他们热衷攀比起来。他们总是在比谁的建筑建得最奇特。

幸好 Z 族人对奇特的理解都差不多，他们很快给每栋建筑都打了分，这样评选谁最奇特就轻而易举了。

于是，根据分值，大家很快评出了最奇特的建筑，称为大奇迹。后来他们又陆续评选了第二奇特、第二奇特、……、第七奇特的建筑，依次称为第二大奇迹、第三大奇迹、……、第七大奇迹。

最近，他们开始评选第八奇特的建筑，准备命名为第八大奇迹。在评选中，他们遇到了一些问题。
## 题目描述

首先，Z 族一直在发展，有的建筑被拆除又建了新的建筑，新建筑的奇特值和原建筑不一样，这使得评选不那么容易了。

其次，Z 族的每个人所生活的范围可能不一样，他们见过的建筑并不是所有的建筑，他们坚持他们自己所看到的第八奇特的建筑就是第八大奇迹。

Z 族首领最近很头疼这个问题，他害怕因为意见不一致导致 Z 族发生分歧。他找到你，他想先了解一下，民众自己认为的奇迹是怎样的。

现在告诉在 R 河周边的建筑的变化情况，以及在变化过程中一些人的生活范围，请编程求出每个人认为的第八大奇迹的奇特值是多少。
## 输入格式

输入的第一行包含两个整数 $L$, $N$，分别表示河流的长度和要你处理的信息的数量。开始时河流沿岸没有建筑，或者说所有的奇特值为 $0$。接下来 $N$ 行，每行一条你要处理的信息。

如果信息为 `C p x`，表示流域中第 $p$ 个位置 $(1 \le p \le L)$ 建立了一个建筑，其奇特值为 $x$。如果这个位置原来有建筑，原来的建筑会被拆除。

如果信息为 `Q a b`，表示有个人生活的范围是河流的第 $a$ 到 $b$ 个位置（包含 $a$ 和 $b$，$a \le b$），这时你要算出这个区间的第八大奇迹的奇特值，并输出。如果找不到第八大奇迹，输出 $0$。

## 输出格式

对于每个为 $Q$ 的信息，你需要输出一个整数，表示区间中第八大奇迹的奇特值。
## 样例

### 样例输入 #1
```
10 15
C 1 10
C 2 20
C 3 30
C 4 40
C 5 50
C 6 60
C 7 70
C 8 80
C 9 90
C 10 100
Q 1 2
Q 1 10
Q 1 8
C 10 1
Q 1 10
```
### 样例输出 #1
```
0
30
10
20

```
## 提示

对于 $20\%$ 的评测用例，$1 \le L \le 1000$，$1 \le N \le 1000$。

对于 $40\%$ 的评测用例，$1 \le L \le 10000$，$1 \le N \le 10000$。

对于 $100\%$ 的评测用例，$1 \le L \le 10^5$，$1 \le N \le 10^5$。所有奇特值为不超过 $10^9$ 的非负整数。

蓝桥杯 2019 年国赛 B 组 I 题。


---

---
title: "[蓝桥杯 2022 国 A] 三角序列"
layout: "post"
diff: 提高+/省选-
pid: P8797
tag: ['莫队', '2022', '可持久化线段树', '分块', '蓝桥杯国赛']
---
# [蓝桥杯 2022 国 A] 三角序列
## 题目背景

感谢 [Lotuses](https://www.luogu.com.cn/user/414231) 提供的数据
## 题目描述

给定 $n$ 组成对的数 $a_i, b_i$，每组数表示一个 $a_i$ 行 $a_i$ 列的如图所示的三角形：

![](https://cdn.luogu.com.cn/upload/image_hosting/hp3n8ozb.png)

其中 $b_i$ 为 $0$ 时左边较低，为 $1$ 时右边较低。

将每组数对应的三角按数的顺序从左到右拼接起来。

现给出 $m$ 组询问 $l_i, r_i, v_i$，对每组询问求最低高度 $h_i$ 使得 $l_i$ 到 $r_i$ 列之间的高度在 $h_i$ 以内的 $o$ 的数量大于等于 $v_i$。
## 输入格式

输入的第一行包含两个整数 $n, m$，用一个空格分隔。

接下来 $n$ 行，每行包含两个整数 $a_i, b_i$，用一个空格分隔。

接下来 $m$ 行，每行包含三个整数 $l_i,r_i,v_i$，相邻两个整数之间用一个空格分隔。
## 输出格式

输出一行包含一个字符串表示答案。
## 样例

### 样例输入 #1
```
6 6
3 0
4 0
2 1
3 1
5 0
1 1
3 9 12
3 9 13
3 4 4
14 16 7
9 15 12
1 18 42
```
### 样例输出 #1
```
2
3
3
3
3
-1
```
## 提示

**【样例说明】**

第一个询问对应的范围如图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/iu9yky3i.png)

**【评测用例规模与约定】**

- 对于 $30\%$ 的评测用例，$1 \leq n, m, a_i \leq 500$；
- 对于 $50\%$ 的评测用例，$1 \leq n, m, a_i \leq 5000$；
- 对于所有评测用例，$1 \leq n, m \leq 2\times10^5$，$1 \leq a_i \leq 10^6$，$0 \leq b_i \leq 1$，$1 \leq l_i \leq r_i \leq \sum a_i$，$1 \leq v_i \leq 10^{18}$。

蓝桥杯 2022 国赛 A 组 I 题。


---

