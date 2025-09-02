---
title: "【MX-X1-T4】「KDOI-05」简单的字符串问题"
layout: "post"
diff: 省选/NOI-
pid: P10716
tag: ['字符串', '倍增', '树上启发式合并', 'O2优化', 'KMP 算法', '梦熊比赛']
---
# 【MX-X1-T4】「KDOI-05」简单的字符串问题
## 题目背景

原题链接：<https://oier.team/problems/X1D>。
## 题目描述

你有一个字符串 $S$。$q$ 个询问，每次给出 $(i,k)$，求有多少个非空字符串 $A$，使得存在可空字符串 $B_1,B_2,\dots,B_{k-1}$ 满足：

$$S[1,i]=AB_1AB_2A\dots AB_{k-1}A$$

其中 $S[1,i]$ 表示 $S$ 的长度为 $i$ 的前缀。
## 输入格式

第一行一个正整数 $n$ 表示 $S$ 的长度。

接下来一个长度为 $n$ 且仅包含小写字母的字符串表示 $S$。

接下来一行一个正整数表示 $q$。

接下来 $q$ 行，每行两个正整数表示一个询问的 $i,k$。
## 输出格式

输出 $q$ 行，每行一个非负整数表示答案。
## 样例

### 样例输入 #1
```
10
aabaacaaaa
5
5 3
5 2
6 1
10 4
10 5
```
### 样例输出 #1
```
1
2
1
2
1
```
### 样例输入 #2
```
10
bababababa
10
6 1
6 2
6 3
6 4
6 5
10 2
10 3
9 4
5 5
4 2
```
### 样例输出 #2
```
1
1
1
0
0
2
1
1
0
1

```
## 提示

**【样例解释 \#1】**

对于第一次询问 $(5,3)$，可以取 $A=\texttt{a}$，$B_1=\varepsilon$，$B_2=\texttt{ba}$，其中 $\varepsilon$ 表示空串。可以证明有且仅有一个合法的 $A$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | 分值 | $n,q\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|
| $1$ | $5$ | $500$ | 无 |
| $2$ | $10$ | $5000$ | 无 |
| $3$ | $10$ | $2\times10^5$ | $S$ 中字符从 $\tt a,b$ 中随机生成 |
| $4$ | $20$ | $2\times10^5$ | 每个询问的 $k$ 相同 |
| $5$ | $20$ | $5\times10^4$ | 无 |
| $6$ | $35$ | $2\times10^5$ | 无 |

对于 $100\%$ 的数据：$1\leq k\leq i\leq n\leq 2\times 10^5$，$1\leq q\leq 2\times 10^5$，$s$ 仅包含小写字母。


---

---
title: "[NOIP 2012 提高组] 开车旅行"
layout: "post"
diff: 省选/NOI-
pid: P1081
tag: ['2012', '倍增', 'NOIP 提高组']
---
# [NOIP 2012 提高组] 开车旅行
## 题目描述

小 $\text{A}$ 和小 $\text{B}$ 决定利用假期外出旅行，他们将想去的城市从 $1 $ 到 $n$ 编号，且编号较小的城市在编号较大的城市的西边，已知各个城市的海拔高度互不相同，记城市 $i$ 的海拔高度为$h_i$，城市 $i$ 和城市 $j$ 之间的距离 $d_{i,j}$ 恰好是这两个城市海拔高度之差的绝对值，即 $d_{i,j}=|h_i-h_j|$。
 
旅行过程中，小 $\text{A}$ 和小 $\text{B}$ 轮流开车，第一天小 $\text{A}$ 开车，之后每天轮换一次。他们计划选择一个城市 $s$ 作为起点，一直向东行驶，并且最多行驶 $x$ 公里就结束旅行。    

小 $\text{A}$ 和小 $\text{B}$ 的驾驶风格不同，小 $\text{B}$ 总是沿着前进方向选择一个最近的城市作为目的地，而小 $\text{A}$ 总是沿着前进方向选择第二近的城市作为目的地（注意：本题中如果当前城市到两个城市的距离相同，则认为离海拔低的那个城市更近）。如果其中任何一人无法按照自己的原则选择目的城市，或者到达目的地会使行驶的总距离超出 $x$ 公里，他们就会结束旅行。

在启程之前，小 $\text{A}$ 想知道两个问题：

1、 对于一个给定的 $x=x_0$，从哪一个城市出发，小 $\text{A}$ 开车行驶的路程总数与小 $\text{B}$ 行驶的路程总数的比值最小（如果小 $\text{B}$ 的行驶路程为 $0$，此时的比值可视为无穷大，且两个无穷大视为相等）。如果从多个城市出发，小 $\text{A}$ 开车行驶的路程总数与小 $\text{B}$ 行驶的路程总数的比值都最小，则输出海拔最高的那个城市。

2、对任意给定的 $x=x_i$ 和出发城市 $s_i$，小 $\text{A}$ 开车行驶的路程总数以及小 $\text B$ 行驶的路程总数。

## 输入格式

第一行包含一个整数 $n$，表示城市的数目。

第二行有 $n$ 个整数，每两个整数之间用一个空格隔开，依次表示城市 $1$ 到城市 $n$ 的海拔高度，即 $h_1,h_2 ... h_n$，且每个 $h_i$ 都是互不相同的。

第三行包含一个整数 $x_0$。

第四行为一个整数 $m$，表示给定 $m$ 组 $s_i$ 和 $x_i$。

接下来的 $m$ 行，每行包含 $2$ 个整数 $s_i$ 和 $x_i$，表示从城市$s_i$ 出发，最多行驶 $x_i$ 公里。
## 输出格式

输出共 $m+1$ 行。

第一行包含一个整数 $s_0$，表示对于给定的 $x_0$，从编号为 $s_0$ 的城市出发，小 $\text A$ 开车行驶的路程总数与小 $\text B$ 行驶的路程总数的比值最小。

接下来的 $m$ 行，每行包含 $2$ 个整数，之间用一个空格隔开，依次表示在给定的 $s_i$ 和 $x_i$ 下小 $\text A$ 行驶的里程总数和小 $\text B$ 行驶的里程总数。

## 样例

### 样例输入 #1
```
4 
2 3 1 4 
3 
4 
1 3 
2 3 
3 3 
4 3

```
### 样例输出 #1
```
1 
1 1 
2 0 
0 0 
0 0 
```
### 样例输入 #2
```
10 
4 5 6 1 2 3 7 8 9 10 
7 
10 
1 7 
2 7 
3 7 
4 7 
5 7 
6 7 
7 7 
8 7 
9 7 
10 7
```
### 样例输出 #2
```
2 
3 2 
2 4 
2 1 
2 4 
5 1 
5 1 
2 1 
2 0 
0 0 
0 0
```
## 提示

【样例1说明】

![](https://cdn.luogu.com.cn/upload/image_hosting/zgms0k7y.png)

各个城市的海拔高度以及两个城市间的距离如上图所示。

如果从城市 $1$ 出发，可以到达的城市为 $2,3,4$，这几个城市与城市 $1$ 的距离分别为 $1,1,2$，但是由于城市 $3$ 的海拔高度低于城市 $2$，所以我们认为城市 $3$ 离城市 $1$ 最近，城市 $2$ 离城市 $1$ 第二近，所以小A会走到城市 $2$。到达城市 $2$ 后，前面可以到达的城市为 $3,4$，这两个城市与城市 $2$  的距离分别为 $2,1$，所以城市 $4$ 离城市 $2$ 最近，因此小B会走到城市$4$。到达城市 $4$ 后，前面已没有可到达的城市，所以旅行结束。

如果从城市 $2$ 出发，可以到达的城市为 $3,4$，这两个城市与城市 $2$ 的距离分别为 $2,1$，由于城市 $3$ 离城市 $2$ 第二近，所以小 $\text A$ 会走到城市 $3$。到达城市 $3$ 后，前面尚未旅行的城市为 $4$，所以城市 $4$ 离城市 $3$ 最近，但是如果要到达城市 $4$，则总路程为 $2+3=5>3$，所以小 $\text B$ 会直接在城市 $3$ 结束旅行。

如果从城市 $3$ 出发，可以到达的城市为 $4$，由于没有离城市 $3$ 第二近的城市，因此旅行还未开始就结束了。

如果从城市 $4$ 出发，没有可以到达的城市，因此旅行还未开始就结束了。


【样例2说明】

当 $x=7$ 时，如果从城市 $1$ 出发，则路线为 $1 \to 2 \to 3 \to 8 \to 9$，小 $\text A$ 走的距离为 $1+2=3$，小 $\text B$ 走的距离为 $1+1=2$。（在城市 $1$ 时，距离小 $\text A$ 最近的城市是 $2$ 和 $6$，但是城市 $2$ 的海拔更高，视为与城市 $1$ 第二近的城市，所以小 $\text A$ 最终选择城市 $2$；走到$9$ 后，小 $\text A$ 只有城市 $10$ 可以走，没有第二选择可以选，所以没法做出选择，结束旅行）

如果从城市 $2$ 出发，则路线为 $2 \to 6 \to 7$，小 $\text A$ 和小 $\text B$ 走的距离分别为 $2,4$。

如果从城市 $3$ 出发，则路线为 $3 \to 8 \to 9$，小 $\text A$ 和小 $\text B$ 走的距离分别为$2,1$。

如果从城市 $4$ 出发，则路线为 $4 \to 6 \to 7$，小 $\text A$ 和小 $\text B$ 走的距离分别为 $2,4$。

如果从城市 $5$ 出发，则路线为 $5 \to 7 \to 8$，小 $\text A$ 和小 $\text B$ 走的距离分别为 $5,1$。

如果从城市 $6$ 出发，则路线为 $6 \to 8 \to 9$，小 $\text A$ 和小 $\text B$ 走的距离分别为$5,1$。

如果从城市 $7$ 出发，则路线为 $7 \to 9 \to 10$，小 $\text A$ 和小 $\text B$ 走的距离分别为$2,1$。

如果从城市 $8$ 出发，则路线为 $8 \to 10$，小 $\text A$ 和小 $\text B$ 走的距离分别为$2,0$。

如果从城市 $9$ 出发，则路线为 $9$，小 $\text A$ 和小 $\text B$ 走的距离分别为 $0,0$（旅行一开始就结束了）。

如果从城市 $10$ 出发，则路线为 $10$，小 $\text A$ 和小 $\text B$ 走的距离分别为$0,0$。

从城市 $2$ 或者城市 $4$ 出发小 $\text A$ 行驶的路程总数与小 $\text B$ 行驶的路程总数的比值都最小，但是城市 $2$ 的海拔更高，所以输出第一行为 $2$。

【数据范围与约定】  

对于 $30\%$ 的数据，有$1\le n \le 20,1\le m\le 20$；  
对于$40\%$ 的数据，有$1\le n \le 100,1\le m\le 100$；  
对于 $50\%$ 的数据，有$1\le n \le 100,1\le m\le 1000$；  
对于 $70\%$ 的数据，有$1\le n \le 1000,1\le m\le 10^4$；   
对于 $100\%$ 的数据：$1\le n,m \le 10^5$，$-10^9 \le h_i≤10^9$，$1 \le s_i \le n$，$0 \le x_i \le 10^9$   
数据保证 $h_i$ 互不相同。



---

---
title: "[NOIP 2012 提高组] 疫情控制"
layout: "post"
diff: 省选/NOI-
pid: P1084
tag: ['贪心', '树形数据结构', '2012', '倍增', '二分', 'NOIP 提高组', '排序']
---
# [NOIP 2012 提高组] 疫情控制
## 题目描述

H 国有 $n $ 个城市，这 $n$ 个城市用 $ n-1 $ 条双向道路相互连通构成一棵树，$1 $ 号城市是首都，也是树中的根节点。

H 国的首都爆发了一种危害性极高的传染病。当局为了控制疫情，不让疫情扩散到边境城市（叶子节点所表示的城市），决定动用军队在一些城市建立检查点，使得从首都到边境城市的每一条路径上都至少有一个检查点，边境城市也可以建立检查点。但特别要注意的是，首都是不能建立检查点的。

现在，在 H 国的一些城市中已经驻扎有军队，且一个城市可以驻扎多个军队。一支军队可以在有道路连接的城市间移动，并在除首都以外的任意一个城市建立检查点，且只能在一个城市建立检查点。一支军队经过一条道路从一个城市移动到另一个城市所需要的时间等于道路的长度（单位：小时）。

请问最少需要多少个小时才能控制疫情。注意：不同的军队可以同时移动。

## 输入格式

第一行一个整数 $ n$，表示城市个数。

接下来的 $n-1$ 行，每行 $ 3 $ 个整数，$u,v,w$，每两个整数之间用一个空格隔开，表示从城市 $u $ 到城市 $ v$ 有一条长为 $w$ 的道路。数据保证输入的是一棵树，且根节点编号为 $1$。

接下来一行一个整数 $m$，表示军队个数。

接下来一行 $m $ 个整数，每两个整数之间用一个空格隔开，分别表示这 $m$ 个军队所驻扎的城市的编号。

## 输出格式

一个整数，表示控制疫情所需要的最少时间。如果无法控制疫情则输出 $-1$。

## 样例

### 样例输入 #1
```
4 
1 2 1 
1 3 2 
3 4 3 
2 
2 2
```
### 样例输出 #1
```
3
```
## 提示

【输入输出样例说明】

第一支军队在 $2$ 号点设立检查点，第二支军队从 $2$ 号点移动到$ 3$ 号点设立检查点，所需时间为 $3$ 个小时。

 
【数据范围】

保证军队不会驻扎在首都。

- 对于 $20\%$ 的数据，$2 \le n\le 10$；
- 对于 $40\%$ 的数据，$2 \le n\le 50$，$0<w <10^5$；
- 对于 $60\%$ 的数据，$2 \le n\le 1000$，$0<w <10^6$；
- 对于 $80\%$ 的数据，$2 \le n\le 10^4$；
- 对于 $100\%$ 的数据，$2\le m\le n≤5\times 10^4$，$0<w <10^9$。


NOIP 2012 提高组 第二天 第三题



---

---
title: "【MX-S6-T3】「KDOI-11」简单的字符串问题 2"
layout: "post"
diff: 省选/NOI-
pid: P11291
tag: ['字符串', '贪心', '倍增', 'Special Judge', 'O2优化', '哈希 hashing', '前缀和', 'KMP 算法', '梦熊比赛']
---
# 【MX-S6-T3】「KDOI-11」简单的字符串问题 2
## 题目背景

原题链接：<https://oier.team/problems/S6C>。
## 题目描述

给定 $n$ 个字符串 $S_1, \ldots, S_n$ 以及一个字符串 $T$。

对于一个字符串 $R$，定义 $|R|$ 表示 $R$ 的长度、$R_{[l,r]}$ 表示 $R$ 的第 $l\sim r$ 个字符组成的字符串。字符串 $R'$ 是字符串 $R$ 的前缀当且仅当存在 $1\leq p\leq |R|$ 且 $p$ 为整数使得 $R'=R_{[1,p]}$。

定义一个字符串 $R$ 是**好的**当且仅当它是某个 $S_i$ 的前缀**或** $R$ **为空**。

对于若干字符串 $R_1,R_2,\dots,R_k$，定义 $R_1+R_2+\dots+R_k$ 为 $R_1,R_2,\dots,R_k$ 顺次拼接得到的字符串。

定义一个三元组 $(l,r,k)$（$l,r,k$ 均为整数）是好的当且仅当 $1\leq l\leq r\leq|T|$，$1\leq k\leq K$ 且存在 $k$ 个**好的**字符串 $R_1,R_2,\dots,R_k$ 使得 $R_1+R_2+\dots+R_k=T_{[l,r]}$。

请你求出好的三元组的数量，并对于每个 $i$ 求出有多少好的三元组 $(l,r,k)$ 满足 $l\leq i\leq r$。如果你只能求出两者中其一，也可以获得部分分数，见【**输出格式**】。
## 输入格式

第一行，三个非负整数 $id,n,K$，其中 $id$ 表示测试点编号（所有样例满足 $id=0$），$n$ 表示字符串数量，$K$ 表示对好的三元组的限制。

接下来 $n$ 行，每行一个字符串 $S_i$。

接下来一行，一个字符串 $T$。
## 输出格式

第一行，一个非负整数，表示好的三元组的数量。

第二行，$\lvert T\rvert$ 个非负整数，第 $i$ 个表示满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量。

本题使用**自定义校验器**进行评分，对于每个测试点：

* 如果你的程序正确地求出了好的三元组的数量并正确地对于每个 $1\leq i\leq |T|$ 求出了满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量，你可以获得该测试点 $100\%$ 的分数。
* 如果你的程序未能正确地求出了好的三元组的数量但正确地对于每个 $1\leq i\leq |T|$ 求出了满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量，你可以获得该测试点 $80\%$ 的分数。
* 如果你的程序正确地求出了好的三元组的数量但未能正确地对于每个 $1\leq i\leq |T|$ 求出了满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量，你可以获得该测试点 $60\%$ 的分数。
* 否则，你不能获得该测试点的任何分数。

注意，即使你希望获得某测试点 $80\%$ 或 $60\%$ 的分数，你也需要在第一行输出一个数并在第二行输出 $\lvert T\rvert$ 个数。
## 样例

### 样例输入 #1
```
0 1 2
ab
abaab
```
### 样例输出 #1
```
13
5 3 5 6 3
```
### 样例输入 #2
```
0 3 2
abc
ac
b
bacabcab
```
### 样例输出 #2
```
27
4 9 6 11 10 5 6 5
```
### 样例输入 #3
```
0 10 10
wooogpgpoo
owpwgwwp
ooogpgpooo
gppwppgwoo
wooogpgpoo
wowooogpgp
gwwp
ggggogwgpp
wowooogpgp
pgpoooowpw
pgwgwggggggogwgppwppgwooggoogwowooogpgpoooowpwgwwp
```
### 样例输出 #3
```
7698
183 390 577 792 990 1213 1422 1651 1780 1889 1984 2099 2235 2355 2491 2458 2435 2426 2439 2466 2478 2498 2503 2489 2481 2477 2477 2483 2491 2527 2532 2559 2571 2540 2489 2433 2372 2276 2163 2041 1932 1803 1662 1491 1308 1111 900 702 486 252
```
## 提示

**【样例解释 #1】**

符合要求的 $(l,r,k)$ 有以下 $13$ 组：

* $(1,1,1)$；
* $(1,1,2)$；
* $(1,2,1)$；
* $(1,2,2)$；
* $(1,3,2)$；
* $(3,3,1)$；
* $(3,3,2)$；
* $(3,4,2)$；
* $(3,5,2)$；
* $(4,4,1)$；
* $(4,4,2)$；
* $(4,5,1)$；
* $(4,5,2)$。

**【样例 #4】**

见附件中的 `string/string4.in` 与 `string/string4.ans`。

该组样例满足测试点 $1\sim3$ 的约束条件。

**【样例 #5】**

见附件中的 `string/string5.in` 与 `string/string5.ans`。

该组样例满足测试点 $4\sim6$ 的约束条件。

**【样例 #6】**

见附件中的 `string/string6.in` 与 `string/string6.ans`。

该组样例满足测试点 $7\sim10$ 的约束条件。

**【样例 #7】**

见附件中的 `string/string7.in` 与 `string/string7.ans`。

该组样例满足测试点 $13\sim14$ 和测试点 $16\sim17$ 的约束条件。

**【样例 #8】**

见附件中的 `string/string8.in` 与 `string/string8.ans`。

该组样例满足测试点 $18\sim20$ 的约束条件。

**【数据范围】**

对于所有测试数据，保证：$1\leq n\leq10$，$1\leq |S_i|\leq5\times10^4$，$1\leq |T|,K\leq5\times10^5$，字符串仅包含小写英文字母 $\texttt{a}\sim\texttt{z}$。

| 测试点编号 | $n\leq$ | $\lvert S_i\rvert\leq$ |  $\lvert T\rvert\leq$ | $K\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|:--:|
| $1\sim3$ | $10$ | $50$ | $50$ | $50$ | 无 |
| $4\sim6$ | $10$ | $100$ | $300$ | $300$ | 无 |
| $7\sim10$ | $10$ | $1000$ | $5000$ | $5000$ | 无 |
| $11\sim12$ | $10$ | $5\times10^4$ | $5\times10^5$ | $1$ | 无 |
| $13\sim14$ | $10$ | $5\times10^4$ | $5\times10^5$ | $10$ | 无 |
| $15$ | $10$ | $5\times10^4$ | $5\times10^5$ | $5\times10^5$ | 所有字符均为 $\texttt{a}$ |
| $16\sim17$ | $10$ | $5\times10^4$ | $5\times10^5$ | $5\times10^5$ | 所有字符在 $\{\texttt{a},\texttt{b}\}$ 中独立均匀随机生成 |
| $18\sim20$ | $10$ | $5\times10^4$ | $5\times10^5$ | $5\times10^5$ | 无 |


---

---
title: "[COTS 2016] 搜索树 Jelka"
layout: "post"
diff: 省选/NOI-
pid: P11306
tag: ['2016', '线段树', '倍增', '树状数组', '树的遍历', '树链剖分', 'COCI（克罗地亚）']
---
# [COTS 2016] 搜索树 Jelka
## 题目背景

译自 [Izborne Pripreme 2016 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2016/) D2T1。$\texttt{1s,0.5G}$。

## 题目描述


给定一棵 $n$ 个点的二叉树，点有点权，其中 $1$ 号点为根节点。

$m$ 次操作修改某个点的点权。在每次修改后询问：这棵树上有多少个节点的子树（包含自身）是二叉搜索树（BST）？

我们给定 BST 的定义：

- 含有一个节点的树是 BST。
- 对于大于一个节点的树，它是 BST 当且仅当：
	- 根节点的左子树为空，或者左子树是二叉搜索树，且左子树内所有点的点权均**不大于**根节点的点权；
   - 根节点的右子树为空，或者右子树是二叉搜索树，且右子树内所有点的点权均**不小于**根节点的点权。


## 输入格式


第一行，两个正整数 $n,m$。

接下来 $n$ 行，每行两个整数 $l_i,r_i$，表示 $i$ 号点的左儿子和右儿子编号。
- 特别地，若不存在，则为 $0$。

接下来一行，$n$ 个整数 $a_1,\cdots,a_n$，表示每个点的点权。

接下来 $m$ 行，每行两个整数 $x,v$，表示一次操作 $a_x\gets v$。

## 输出格式

输出 $m$ 行 $m$ 个整数，表示答案。

## 样例

### 样例输入 #1
```
6 5
2 3
4 0
5 6
0 0
0 0
0 0
4 1 3 2 2 5
3 3
2 2
3 5
5 4
6 1
```
### 样例输出 #1
```
4
5
5
6
4
```
### 样例输入 #2
```
8 10
4 5
8 0
0 0
3 7
0 6
0 0
2 0
0 0
7 0 9 3 6 0 6 2
3 0
4 0
8 2
2 3
7 6
1 6
5 7
6 9
1 1
1 7
```
### 样例输出 #2
```
3
3
3
6
6
6
6
8
7
8
```
## 提示


#### 样例解释

样例 $1$ 解释如图所示。

其中节点内的数字表示 BST 权值，节点外的数字表示节点编号。

![](https://cdn.luogu.com.cn/upload/image_hosting/yabnaj75.png)

#### 数据范围

对于 $100\%$ 的数据，保证：
- $1\le n,m\le 2\times 10^5$；
- $0\le a_i,v\le 10^9$；
- 操作和树的形态均合法。


| 子任务编号 | $n,m\le  $ | 特殊性质 | 得分 |  
| :--: | :--: | :--: | :--: |
| $ 1 $    | $ 5\, 000$    |  | $ 16 $   |  
| $ 2 $    | $ 2\times 10^5 $   | A |  $ 24 $   |  
| $ 3 $    | $ 2\times 10^5$ | | $ 60 $   |  

特殊性质 A：$\forall 1\le i\le n$，$l_i=0\lor r_i=0$。




---

---
title: "[KOI 2021 Round 2] 美食推荐"
layout: "post"
diff: 省选/NOI-
pid: P12730
tag: ['动态规划 DP', '倍增', '点分治', '2021', 'KOI（韩国）']
---
# [KOI 2021 Round 2] 美食推荐
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

KOI 国有 $N$ 个城市。每个城市编号从 1 到 $N$。

KOI 国的结构很特别，把城市看作图的顶点、道路看作无向边，则这个国家的结构可以表示为一个包含 $N$ 个顶点的**树**。树是一个无环的连通图。

KOI 国共有 $M$ 家美食餐厅，每家餐厅编号从 1 到 $M$。某些城市可能没有餐厅，也可能有两个以上的餐厅，请特别注意这一点。

第 $i$ 家餐厅（$1 \leq i \leq M$）位于城市 $c_i$，配送范围为距离不超过 $d_i$ 的城市，且其客户偏好度为 $g_i$。

第 $i$ 家餐厅可以向从城市 $c_i$ 出发，经过至多 $d_i$ 条道路所能到达的所有城市配送。即，第 $i$ 家餐厅的配送范围为：

$$
R_i = \{ j \mid d(c_i, j) \leq d_i \}
$$

其中，$d(a, b)$ 表示从城市 $a$ 到城市 $b$ 之间的最短路径长度（即需要经过的最少道路数）。

你是一名外卖推荐平台的运营者。为了避免服务重叠，你希望从 $M$ 家餐厅中选出一个子集 $S$，满足以下条件：

- 对于任意城市 $p$，它不能同时被 $S$ 中的两个或多个餐厅包含在其配送范围内。也就是说，对于 $S$ 中任意不同的两家餐厅 $i$ 和 $j$，都有 $R_i \cap R_j = \emptyset$。

请从所有满足上述条件的子集 $S$ 中，选出客户偏好度总和最大的一个，并输出该最大值。

## 输入格式

第一行包含两个整数 $N$ 和 $M$，中间用一个空格分隔。

接下来的 $N-1$ 行中，每行包含两个整数 $a$ 和 $b$，表示城市 $a$ 和城市 $b$ 之间有一条道路相连。

接下来的 $M$ 行中，每行包含三个整数 $c_i$、$d_i$ 和 $g_i$，表示第 $i$ 家餐厅所在城市、配送距离上限与客户偏好度。

## 输出格式

输出一个整数，表示满足条件的餐厅集合中客户偏好度之和的最大值。

## 样例

### 样例输入 #1
```
8 5
1 2
2 3
3 4
4 5
5 6
4 7
4 8
3 2 40
6 0 5
8 0 5
2 1 16
5 1 32
```
### 样例输出 #1
```
53
```
## 提示

**约束条件**

- 所有输入数据均为整数。
- $1 \leq N \leq 10^5$
- $1 \leq M \leq 10^5$
- 对于所有 $i$（$1 \leq i \leq M$），满足 $0 \leq d_i \leq N - 1$，$1 \leq g_i \leq 10^9$

**子任务**

1. （9 分）对于 $1 \leq i \leq N - 1$，城市 $i$ 与城市 $i+1$ 之间有一条道路相连。
2. （11 分）$N, M \leq 20$
3. （17 分）$N, M \leq 2\,000$
4. （10 分）$N \leq 2\,000$
5. （8 分）对于 $2 \leq i \leq N$，城市 $\lfloor i/2 \rfloor$ 与城市 $i$ 之间有一条道路相连。
6. （12 分）图中度数大于等于 3 的顶点最多只有一个。
7. （33 分）无额外约束条件。


---

---
title: "[POI 2016 R2] 圣诞灯链 Christmas chain"
layout: "post"
diff: 省选/NOI-
pid: P12736
tag: ['2016', '倍增', '并查集', 'POI（波兰）']
---
# [POI 2016 R2] 圣诞灯链 Christmas chain
## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5032)。
## 题目描述

**题目译自 [XXIII Olimpiada Informatyczna — II etap](https://sio2.mimuw.edu.pl/c/oi23-2/dashboard/) [Świąteczny łańcuch](https://szkopul.edu.pl/problemset/problem/cSa80AKpjHR8FlWE4BCpLGT3/statement/)**

每年圣诞节，Bajtazar 都会用五彩缤纷的灯链装点他的家。今年，他决定亲自挑选灯链的颜色，打造一串独一无二的装饰。他对灯链的美学有特定要求：某些灯链片段的颜色排列需与另一些片段完全相同。同时，他的妻子希望今年的灯链尽量丰富多彩，也就是说，灯链应包含尽可能多的不同颜色。请帮助 Bajtazar 计算，他需要购买多少种颜色的灯泡。
## 输入格式

第一行包含两个整数 $n, m$ $(n \geq 2, m \geq 1)$，分别表示灯链中灯泡的数量和 Bajtazar 的美学要求数量。灯泡按顺序编号为 $1$ 至 $n$。

接下来的 $m$ 行描述美学要求，每行包含三个整数 $a_i, b_i, l_i$ $(1 \leq a_i, b_i, l_i; a_i \neq b_i; a_i, b_i \leq n - l_i + 1)$，表示灯链片段 $\{a_i, \ldots, a_i + l_i - 1\}$ 和 $\{b_i, \ldots, b_i + l_i - 1\}$ 应具有相同颜色。即，灯泡 $a_i$ 与 $b_i$ 颜色相同，$a_i + 1$ 与 $b_i + 1$ 颜色相同，依此类推，直至 $a_i + l_i - 1$ 与 $b_i + l_i - 1$。
## 输出格式

输出一个正整数 $k$，表示满足所有美学要求时，灯链中可包含的最大不同颜色数。
## 样例

### 样例输入 #1
```
10 3
1 6 3
5 7 4
3 8 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4 2
1 2 2
2 3 2
```
### 样例输出 #2
```
1
```
## 提示

**样例 1 解释**

设 $a, b, c$ 表示三种不同颜色的灯泡。一个满足 Bajtazar 及其妻子要求的灯链为 $\texttt{abacbababa}$。

**附加样例**

1. $n=2000, m=2$，要求片段 $\{1, \ldots, 1000\}$ 与 $\{1001, \ldots, 2000\}$ 相同，$\{1, \ldots, 500\}$ 与 $\{501, \ldots, 1000\}$ 相同，最大颜色数为 $500$。
2. $n=500000, m=499900$，第 $i$ 个要求为 $a_i=i, b_i=i+100, l_i=1$，最大颜色数为 $100$。
3. $n=80000, m=79995$，第 $i$ 个要求为 $a_i=i, b_i=i+2, l_i=4$，最大颜色数为 $2$。
4. $n=50000, m=25000$，第 $i$ 个要求为 $a_i=1, b_i=i+1, l_i=9$，灯链只能使用单一颜色。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n, m \leq 2000$         | $30$ |
| $2$    | $n, m \leq 500000$，所有 $l_i = 1$ | $20$ |
| $3$    | $n, m \leq 80000$        | $30$ |
| $4$    | $n, m \leq 500000$       | $20$ |


---

---
title: "[ZJOI2012] 灾难"
layout: "post"
diff: 省选/NOI-
pid: P2597
tag: ['2012', '倍增', '各省省选', '浙江', 'O2优化', '拓扑排序', '最近公共祖先 LCA']
---
# [ZJOI2012] 灾难
## 题目背景

阿米巴是小强的好朋友。

阿米巴和小强在草原上捉蚂蚱。小强突然想，如果蚂蚱被他们捉灭绝了，那么吃蚂蚱的小鸟就会饿死，而捕食小鸟的猛禽也会跟着灭绝，从而引发一系列的生态灾难。

学过生物的阿米巴告诉小强，草原是一个极其稳定的生态系统。如果蚂蚱灭绝了，小鸟照样可以吃别的虫子，所以一个物种的灭绝并不一定会引发重大的灾难。
## 题目描述

我们现在从专业一点的角度来看这个问题。我们用一种叫做食物网的有向图来描述生物之间的关系：

- 一个食物网有 $n$ 个点，代表 $n$ 种生物，生物从 $1$ 到 $n$ 编号。
- 如果生物 $x$ 可以吃生物 $y$，那么从 $y$ 向 $x$ 连一个有向边。
- 这个图没有环。
- 图中有一些点没有连出边，这些点代表的生物都是生产者，可以通过光合作用来生存。
- 而有连出边的点代表的都是消费者，它们必须通过吃其他生物来生存。
- 如果某个消费者的所有食物都灭绝了，它会跟着灭绝。

我们定义一个生物在食物网中的“灾难值”为，如果它突然灭绝，那么会跟着一起灭绝的生物的种数。

举个例子：在一个草场上，生物之间的关系如下

![](https://cdn.luogu.com.cn/upload/image_hosting/oiw4lh97.png)

如果小强和阿米巴把草原上所有的羊都给吓死了，那么狼会因为没有食物而灭绝，而小强和阿米巴可以通过吃牛、牛可以通过吃草来生存下去。所以，羊的灾难值是 $1$。但是，如果草突然灭绝，那么整个草原上的 $5$ 种生物都无法幸免，所以，草的灾难值是 $4$。

给定一个食物网，你要求出每个生物的灾难值。
## 输入格式

第一行有一个整数，表示食物网的结点个数 $n$。

第 $2$ 到第 $(n + 1)$ 行，每行若干个互不相同的整数，第 $(i + 1)$ 行的整数 $a_{i, j}$ 表示编号为 $i$ 的生物可以吃编号为 $a_{i, j}$ 的生物。每行结尾有一个整数 $0$ 表示本行结束。
## 输出格式

输出 $n$ 行，每行一个整数，第 $i$ 行输出编号为 $i$ 的生物的灾难值。
## 样例

### 样例输入 #1
```
5
0
1 0
1 0
2 3 0
2 0

```
### 样例输出 #1
```
4
1
0
0
0
```
## 提示

### 样例 1 解释

样例输入描述了题目描述中举的例子。

### 数据规模与约定

- 对于 $50\%$ 的数据，保证 $n \leq 10^4$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 65534$，$1 \leq a_{i, j} \leq n$，输入的文件大小不超过 1 MB，且图上不存在环。


---

---
title: "[HNOI2014] 世界树"
layout: "post"
diff: 省选/NOI-
pid: P3233
tag: ['动态规划 DP', '2014', '倍增', '湖南', '最近公共祖先 LCA', '虚树']
---
# [HNOI2014] 世界树
## 题目描述

世界树是一棵无比巨大的树，它伸出的枝干构成了整个世界。在这里，生存着各种各样的种族和生灵，他们共同信奉着绝对公正公平的女神艾莉森，在他们的信条里，公平是使世界树能够生生不息、持续运转的根本基石。

世界树的形态可以用一个数学模型来描述：世界树中有 $n$ 个种族，种族的编号分别从 $1$ 到 $n$，分别生活在编号为 $1$ 到 $n$ 的聚居地上，种族的编号与其聚居地的编号相同。有的聚居地之间有双向的道路相连，道路的长度为 $1$。保证连接的方式会形成一棵树结构，即所有的聚居地之间可以互相到达，并且不会出现环。定义两个聚居地之间的距离为连接他们的道路的长度；例如，若聚居地 $a$ 和 $b$ 之间有道路，$b$ 和 $c$ 之间有道路，因为每条道路长度为 $1$ 而且又不可能出现环，所以 $a$ 与 $c$ 之间的距离为 $2$。

出于对公平的考虑，第 $i$ 年，世界树的国王需要授权 $m_i$ 个种族的聚居地为临时议事处。对于某个种族 $x$（$x$ 为种族的编号），如果距离该种族最近的临时议事处为 $y$（$y$ 为议事处所在聚居地的编号），则种族 $x$ 将接受 $y$ 议事处的管辖（如果有多个临时议事处到该聚居地的距离一样，则 $y$ 为其中编号最小的临时议事处）。

现在国王想知道，在 $q$ 年的时间里，每一年完成授权后，当年每个临时议事处将会管理多少个种族（议事处所在的聚居地也将接受该议事处管理）。 现在这个任务交给了以智慧著称的灵长类的你：程序猿。请帮国王完成这个任务吧。
## 输入格式

第一行为一个正整数 $n$，表示世界树中种族的个数。接下来 $n-1$ 行，每行两个正整数 $x，y$，表示 $x$ 聚居地与 $y$ 聚居地之间有一条长度为 $1$ 的双向道路。接下来一行为一个正整数 $q$，表示国王询问的年数。接下来 $q$ 块，每块两行：第 $i$ 块的第一行为 $1$ 个正整数 $m_i$，表示第 $i$ 年授权的临时议事处的个数。第 $i$ 块的第二行为 $m_i$ 个正整数 $h_1, h_2,\ldots,h_{m_i}$，表示被授权为临时议事处的聚居地编号（保证互不相同）。

## 输出格式

输出包含 $q$ 行，第 $i$ 行为 $m_i$ 个整数，该行的第 $j$ ($j=1, 2,\ldots, m_i$) 个数表示第 $i$ 年被授权的聚居地 $h_j$ 的临时议事处管理的种族个数。

## 样例

### 样例输入 #1
```
10
2 1
3 2
4 3
5 4
6 1
7 3
8 3
9 4
10 1
5
2
6 1
5
2 7 3 6 9
1
8
4
8 7 10 3
5
2 9 3 5 8
```
### 样例输出 #1
```
1 9   
3 1 4 1 1   
10  
1 1 3 5   
4 1 3 1 1
```
## 提示

对于 $100\%$ 的数据，$N\leq 300000$, $q\leq 300000$, $\sum^q_{i=1}m_i \leq 300000$。



---

---
title: "[SCOI2013] 摩托车交易"
layout: "post"
diff: 省选/NOI-
pid: P3280
tag: ['模拟', '2013', '四川', '倍增', '生成树']
---
# [SCOI2013] 摩托车交易
## 题目描述

mzry1992 在打完吊针出院之后，买了辆新摩托车，开始了在周边城市的黄金运送生意。在 mzry1992 生活的地方，城市之间是用双向高速公路连接的。另外，每条高速公路有一个载重上限，即在不考虑驾驶员和摩托车重量的情况下，如果所载货物的量超过某个值，则不能驶上该条高速公路。

今年，mzry1992 一共收到了来自 $n$ 个不同城市的 $n$ 份定订单，每个订单要求卖出上限为一定量的黄金，或是要求买入上限为一定量的黄金。由于订单并不是同时发来的，为了维护生意上的名声，mzry1992 不得不按照订单发来的顺序与客户进行交易。他与第i 个客户进行交易的具体步骤是：

1. 前往第 $i$ 个客户所在城市。当然，中途是完全允许经过其他城市的。 
2. 与第 $i$ 个客户进行交易，在此过程中他希望有限制的让交易额尽量大。具体的限制有两个：    
(a) 他希望与最后一个客户完成交易后，手上没有剩余黄金。  
(b) 由于黄金是很贵重的物品，不能出现因为买入过多黄金而造成在以后的运送过程中不得不丢弃黄金的情况。

一开始，mzry1992 位于第一个订单客户所在的城市。现在有一个好消息，有人提供了 mzry1992 免费试用周边城市的列车系统的资格。具体来讲，如果mzry1992希望从 $A$ 城市到达 $B$ 城市，且 $A$、$B$ 城市均有列车站的话，他可以携带着黄金与摩托车从 $A$ 城市乘坐列车到 $B$ 城市，这里假定乘坐列车没有载重限制。

现在已知城市间的交通系统情况和订单情况，请帮助 mzry1992 计算每个向 mzry1992 购买黄金的客户的购买量。

## 输入格式

输入的第一行有三个整数 $n,m,q$，分别表示城市数，连通城市的高速公路数和有列车站的城市数。

接下来的一行有 $n$ 个数，每个数均不相同，且值介于 $1$ 到 $n$ 之间，代表订单的顺序。

第三行有 $n$ 个数，第 $i$ 个数表示 $i$ 号城市的订单的上限额 $b_i$，$b_i$ 为正值表示该订单为买入交易（针对mzry1992 而言），上限为 $b_i$，$b_i$ 为负值表示该订单为卖出交易（同样针对mzry1992 而言）上限为 $-b_i$。

接下来的 $m$ 行每行有三个数，$u, v, w$，表示城市 $u$ 和城市 $v$ 之间有一条载重上限为 $w$ 的高速公路，这里假定所有高速公路都是双向的，城市的序号是从 $1$ 到 $n$ 的。

输入的最后一行有 $q$ 个数，代表有列车站城市的序号。

## 输出格式

按照订单顺序对于每个卖出交易，输出一行，该行只有一个整数 $x$，表示卖出黄金的量。

## 样例

### 样例输入 #1
```
Sample #1
3 3 2
2 3 1
-6 5 -3
1 3 5
2 3 2
2 1 6
1 3

```
### 样例输出 #1
```
3
2


```
### 样例输入 #2
```
4 4 0
1 2 3 4
5 4 -6 -1
1 2 4
2 3 100
3 4 1
4 1 4
```
### 样例输出 #2
```
6
1 

```
## 提示

### 样例解释

第一组样例：其中一种合法的方案是最初从 $2$ 号城市买入 $5$ 单位的黄金，先走第三条高速公路到 $1$ 号城市，然后再坐列车到 $3$ 号城市，在 $3$ 号城市卖出 $3$ 单位的黄金，然后乘坐列车到 $1$ 城市，在 $1$ 号城市卖出 $2$ 单位的黄金。


第二组样例：其中一种合法的方案是最初从 $1$ 号城市买入 $4$ 单位的黄金，走第一条高速公路，在 $2$ 号城市买入 $3$ 单位的黄金，走第二条高速公路，在三城市点卖出 $6$ 单位的黄金，走第三条高速公路，在 $4$ 号城市卖出 $1$ 单位的黄金。

### 数据范围与约定

- 对于 $20\%$ 数据，$n \le 100$，$m \le 200$。
- 对于 $50\%$ 数据，$n \le 3000$，$m \le 6000$。
- 对于 $100\%$ 数据，$1 \le n \le 10^5$，$n - 1 \le m \le 2\times 10^5$，$0 \le q \le n$，$0 < |b_i| < 10^9$，$0 < w < 10^9$，保证任意两个城市之间是通过高速公路连通的。



---

---
title: "[SCOI2016] 幸运数字"
layout: "post"
diff: 省选/NOI-
pid: P3292
tag: ['2016', '四川', '倍增', '线性基']
---
# [SCOI2016] 幸运数字
## 题目描述


A 国共有 $n$ 座城市，这些城市由 $n - 1$ 条道路相连，使得任意两座城市可以互达，且路径唯一。每座城市都有一个幸运数字，以纪念碑的形式矗立在这座城市的正中心，作为城市的象征。

一些旅行者希望游览 A 国。旅行者计划乘飞机降落在 $x$ 号城市，沿着 $x$ 号城市到 $y$ 号城市之间那条唯一的路径游览，最终从 $y$ 城市起飞离开 A 国。在经过每一座城市时，游览者就会有机会与这座城市的幸运数字拍照，从而将这份幸运保存到自己身上。然而，幸运是不能简单叠加的，这一点游览者也十分清楚。他们迷信着幸运数字是以异或的方式保留在自己身上的。

例如，游览者拍了 $3$ 张照片，幸运值分别是 $5, 7, 11$，那么最终保留在自己身上的幸运值就是 $5 \operatorname{xor} 7 \operatorname{xor} 11 = 9$。

有些聪明的游览者发现，只要选择性地进行拍照，便能获得更大的幸运值。例如在上述三个幸运值中，只选择 $5$ 和 $11$ ，可以保留的幸运值为 $14$ 。现在，一些游览者找到了聪明的你，希望你帮他们计算出在他们的行程安排中可以保留的最大幸运值是多少。
## 输入格式

第一行包含 $2$ 个正整数 $n, q$，分别表示城市的数量和旅行者数量。

第二行包含 $n$ 个非负整数，其中第 $i$ 个整数 $G_i$ 表示 $i$ 号城市的幸运值。

随后 $n - 1$ 行，每行包含两个正整数 $x, y$，表示 $x$ 号城市和 $y$ 号城市之间有一条道路相连。

随后 $q$ 行，每行包含两个正整数 $x, y$，表示这名旅行者的旅行计划是从 $x$ 号城市到 $y$ 号城市。
## 输出格式

输出需要包含 $q$ 行，每行包含 $1$ 个非负整数，表示这名旅行者可以保留的最大幸运值。
## 样例

### 样例输入 #1
```
4 2
11 5 7 9
1 2
1 3
1 4
2 3
1 4
```
### 样例输出 #1
```
14 
11
```
## 提示

对于 $100 \%$ 的数据，保证 $n \leq 2 \times 10^4, q \leq 2 \times 10^5, G_i \leq 2^{60}$。


---

---
title: "[POI 2011] WYK-Plot"
layout: "post"
diff: 省选/NOI-
pid: P3517
tag: ['2011', '倍增', '二分', 'POI（波兰）', 'Special Judge']
---
# [POI 2011] WYK-Plot
## 题目描述

We call any sequence of points in the plane a plot.

We intend to replace a given plot $(P_1,\cdots,P_n)$ with another that will    have at most $m$ points ($m\le n$) in such a way that it "resembles" the    original plot best.

The new plot is created as follows. The sequence of points $P_1,\cdots,P_n$ can be partitioned into $s$ ($s\le m$) contiguous subsequences:

$(P_{k_0+1},\cdots,P_{k_1}),(P_{k_1+1},\cdots,P_{k_2}),\cdots,(P_{k_{s-1}+1},\cdots,P_{k_s})$ where $0=k_0<k_1<k_2<\cdots<k_s=n$,and afterwards each subsequence $(P_{k_{i-1}+1},\cdots,P_{k_i})$, for $i=1,\cdots,s$,is replaced by a new point $Q_i$.

In that case we say that each of the points $P_{k_{i-1}+1},\cdots,P_{k_i}$ has been contracted to the point $Q_i$.

As a result a new plot, represented by the points $Q_1,\cdots,Q_s$, is created.

The measure of such plot's resemblance to the original is the maximum distance of all the points $P_1,\cdots,P_n$ to the point it has been contracted to:

$max_{i=1,\cdots,s}(max_{j=k_{i-1}+1,\cdots,k_i}(d(P_j,Q_i)))$    where $d(P_j,Q_i)$ denotes the distance between $P_j$ and $Q_i$, given by the well-known formula:

$d((x_1,y_1),(x_2,y_2))=\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}$

 ![](https://cdn.luogu.com.cn/upload/pic/6975.png) 

An exemplary plot $P_1,\cdots,P_7$ and the new plot $(Q_1,Q_2)$, where $(P_1,\cdots,P_4)$ are contracted to $Q_1$, whereas $(P_5,P_6,P_7)$ to $Q_2$.

For a given plot consisting of $n$ points, you are to find the plot that    resembles it most while having at most $m$ points,    where the partitioning into contiguous subsequences is arbitrary.

Due to limited precision of floating point operations, a result is deemed    correct if its resemblance to the given plot is larger than the optimum    resemblance by at most $0.000001$.
## 输入格式

In the first line of the standard input there are two integers $n$ and $m$,      $1\le m\le n\le 100\ 000$, separated by a single space.

Each of the following $n$ lines holds two integers, separated by a single space.

The $(i+1)$-th line gives $x_i$,$y_i$,$-1\ 000\ 000\le x_i,y_i\le 1\ 000\ 000$ denoting the coordinates $(x_i,y_i)$ of the point $P_i$.

## 输出格式

In the first line of the standard output one real number $d$ should be printed out,      the resemblance measure of the plot found to the original one.

In the second line of the standard output there should be another integer $s$, $1\le s\le m$.

Next, the following $s$ lines should specify the coordinates of the points $Q_1,\cdots,Q_s$,one point per line.

Thus the $(i+2)$-th line should give two real numbers $u_i$ and $v_i$,      separated by a single space, that denote the coordinates $(u_i,v_i)$ of the point $Q_i$.All the real numbers should be printed with at most 15 digits after the decimal point.

## 样例

### 样例输入 #1
```
7 2
2 0
0 4
4 4
4 2
8 2
11 3
14 2
```
### 样例输出 #1
```
3.00000000
2
2.00000000 1.76393202
11.00000000 1.99998199
```
## 题目翻译

### 题目描述

**译自 POI 2011 Round 1. E「[Plot](https://szkopul.edu.pl/problemset/problem/mzrTn1kzVBOAwVYn55LUeAai/site/?key=statement)」**

给定 $n$ 个点 $ \left( P_1, \ldots, P_n \right) $，将其分成不多于 $m$ 个连续的段：

$$ \left( P_{k_0 + 1}, \ldots, P_{k_1} \right), \left( P_{k_1 + 1}, \ldots, P_{k_2} \right), \ldots, \left( P_{k_{s - 1}+ 1}, \ldots, P_{k_s} \right), $$

其中 $ 0 = k_0 \lt k_1 \lt k_2 \lt \ldots \lt k_s = n $，且对于 $ i = 1, \ldots, s $，子序列 $ \left( P_{k_{i - 1}+ 1}, \ldots, P_{k_i} \right) $ 用一个新点 $Q_i$ 替代。这时我们说 $ P_{k_i - 1}, \ldots, P_{k_i} $ 这些点被「收缩」到了点 $Q_i$，从而产生一个新的点集 $ Q_1, \ldots, Q_s $。两个点集的相似度定义为 $ P_1, \ldots, P_n $ 这些点与其对应的「收缩」后的点距离的最大值：

$$ \max_{i = 1, \ldots, s} \left( \max_{j = k_{i-1}+1, \ldots, k_i}\left( d\left( P_j, Q_i \right) \right) \right) ,$$

其中 $ d\left( P_j, Q_i \right) $ 表示 $P_j$ 和 $Q_i$ 之间的距离，公式为：

$$ d \left( \left(x_1, y_1 \right), \left( x_2, y_2 \right) \right) = \sqrt{ \left( x_2 - x_1 \right)^2 + \left( y_2 - y_1 \right)^2 } $$

 ![](https://cdn.luogu.com.cn/upload/pic/6975.png) 

上图为一个将 $ (P_1, \ldots, P_7) $ 收缩为 $ ( Q_1, Q_2 ) $ 的例子，其中 $ (P_1, \ldots, P_4) $ 被收缩为 $ Q_1 $，$ (P_5, P_6, P_7) $ 被收缩为 $Q_2$.

给定 $n$ 个点组成的序列，你需要将其「收缩」为最多 $m$ 个点，使得相似度最小。原序列可以任意切割。受限于浮点数的精度限制，只要答案比最优解多出不超过 $ 0.000001$ 即算正确。

### 输入格式

第一行两个整数 $n$ 和 $m$，$ 1 \le m \le n \le 100000 $，用一个空格分开。

接下来 $n$ 行每行两个整数，用一个空格分开。第 $i+1$ 行两个整数 $x_i, y_i$（$ -1000000 \le x_i,y_i \le 1000000$），表示 $P_i$ 的坐标为 $(x_i, y_i)$.

### 输出格式

第一行一个实数 $d$，表示与原序列的相似度。

接下来一个整数 $s$，表示收缩后点集的大小。

接下来 $s$ 行表示 $Q_i, \ldots, Q_s$ 的坐标。每行两个整数 $u_i$ 和 $v_i$ 表示 $Q_i$ 的坐标 $ (u_i, v_i) $。

翻译来自于 [LibreOJ](https://loj.ac/p/2159)。


---

---
title: "[POI 2012] RAN-Rendezvous"
layout: "post"
diff: 省选/NOI-
pid: P3533
tag: ['2012', '倍增', 'POI（波兰）', '最近公共祖先 LCA']
---
# [POI 2012] RAN-Rendezvous
## 题目描述

Byteasar is a ranger who works in the Arrow Cave - a famous rendezvous destination among lovers.

The cave consists of $n$ chambers connected with one-way corridors.

In each chamber exactly one outgoing corridor is marked with an arrow.

Every corridor leads directly to some (not necessarily different) chamber.

The enamoured couples that agree to meet in the Arrow Cave are notorious for forgetting to agree upon    specific chamber, and consequently often cannot find their dates.

In the past this led to many mix-ups and misunderstandings\dots    But ever since each chamber is equipped with an emergency telephone line to the ranger on duty,    helping the enamoured find their dates has become the rangers' main occupation.

The rangers came up with the following method.

Knowing where the enamoured are, they tell each of them how many times they should follow the corridor marked with an arrow in order to meet their date.

The lovers obviously want to meet as soon as possible - after all, they came to the cave to spend time together, not to wander around alone!

Most rangers are happy to oblige: they do their best to give each couple a valid pair of numbers such that their maximum is minimal.

But some rangers, among their numbers Byteasar, grew tired of this extracurricular activity and ensuing puzzles.  Byteasar has asked you to write a program    that will ease the process.  The program, given a description of the cave and the current location of $k$ couples,    should determine $k$ pairs of numbers $x_i$ and $y_i$ such that if the $i$-th couple follows respectively: he $x_i$ and she $y_i$ corridors marked with arrows,then they will meet in a single chamber of the cave $max(x_i,y_i)$ is minimal,subject to above $min(x_i,y_i)$ is minimal,if above conditions do not determine a unique solution, then the woman should cover smaller distance ($x_i\ge y_i$).

It may happen that such numbers $x_i$ and $y_i$ do not exist - then let $x_i=y_i=-1$.  Note that it is fine for several couples    to meet in a single chamber.  Once the lovers have found their dates, they will be happy to lose themselves in the cave again...
## 输入格式

In the first line of the standard input there are two positive integers $n$ and $k$($1\le n,k\le 500\ 000$), separated by a single space, that denote   the number of chambers in the Arrow Cave and the number of couples who want to find their dates, respectively.

The chambers are numbered from 1 to $n$, while the enamoured couples are numbered from 1 to $k$.

The second line of input contains $n$ positive integers separated by single spaces:

the $i$-th such integer determines the number of chamber to which the corridor marked with an arrow going out of chamber $i$ leads.

The following $k$ lines specify the queries by the separated couples. Each such query consists of two positive integers separated by a single space - these denote the numbers of chambers where the lovers are - first him, then her.

In the tests worth 40% of the total points it additionally holds that $n,k\le 2\ 000$.

## 输出格式

Your program should print exactly $k$ lines to the standard output,   one line per each couple specified in the input:

the $i$-th line of the output should give the instructions for the $i$-th couple on the input.

I.e., the $i$-th line of output should contain the integers $x_i,y_i$, separated by a single space.

## 样例

### 样例输入 #1
```
12 5
4 3 5 5 1 1 12 12 9 9 7 1
7 2
8 11
1 2
9 10
10 5
```
### 样例输出 #1
```
2 3
1 2
2 2
0 1
-1 -1
```
## 题目翻译

### 题目描述

**译自 POI 2012 Stage 1. 「[Rendezvous](https://szkopul.edu.pl/problemset/problem/MZTXfOVnJmac175TTH5Lr9Q3/site/?key=statement)」**

给定一个有 $n$ 个顶点的有向图，每个顶点有且仅有一条出边。每次询问给出两个顶点 $a_i$ 和 $b_i$，求满足以下条件的 $x_i$ 和 $y_i$：
* 从顶点 $a_i$ 沿出边走 $x_i$ 步与从顶点 $b_i$ 沿出边走 $y_i$ 步到达的顶点相同。
* $\max(x_i, y_i)$ 最小。
* 满足以上条件的情况下 $\min(x_i, y_i)$ 最小。
* 如果以上条件没有给出一个唯一的解，则还需要满足 $x_i \ge y_i$.

如果不存在这样的 $x_i$ 和 $y_i$，则 $x_i = y_i = -1$.

### 输入格式

第一行两个正整数 $n$ 和 $k$（$1 \le n \le 500\ 000,1 \le k \le 500\ 000$），表示顶点数和询问个数。

接下来一行 $n$ 个正整数，第 $i$ 个数表示 $i$ 号顶点出边指向的顶点。

接下来 $k$ 行表示询问，每行两个整数 $a_i$ 和 $b_i$.

### 输出格式

对每组询问输出两个整数 $x_i$ 和 $y_i$.

### 数据范围

对于 $40\%$ 的数据，$n \le 2000,k \le 2000$.

对于 $100\%$ 的数据，$1 \le n \le 500\ 000,1 \le k \le 500\ 000$.


---

---
title: "[POI 2014] DOO-Around the world"
layout: "post"
diff: 省选/NOI-
pid: P3575
tag: ['搜索', '2014', '倍增', 'POI（波兰）', '栈']
---
# [POI 2014] DOO-Around the world
## 题目描述

After trying hard for many years, Byteasar has finally received a pilot license.

To celebrate the fact, he intends to buy himself an airplane and fly around the planet  3-SATurn (as you may have guessed, this is the planet on which Byteotia is located).

Specifically, Byteasar plans to fly along the equator.

Unfortunately, the equator is rather long, necessitating refuels.

  The flight range (on full tank) of each aircraft is known.

There is a number of airports along the equator, and a plane can be refueled when it lands on one.

Since buying an airplane is a big decision, Byteasar asks your help.

He is about to present you with a list of different plane models he is considering.

Naturally, these differ in their flight range.

For each plane model, he would like to know the minimum number of landings  (including the final one) he would have to make in order to complete the journey.

Note that for each airplane model, the journey may start at a different airport.

通过几年的努力，Byteasar最终拿到了飞行员驾驶证。为了庆祝这一事实，他打算买一架飞机并且绕Byteotia星球赤道飞行一圈。但不幸的是赤道非常长所以需要中途加几次油。现在已知赤道上面所有飞机场，所有飞机从飞机场起飞降落也可以加油。因为买飞机是个十分重大的决定，Byteasar决定寻求你的帮助。他将会让你模拟不同的飞行路线。自然这些飞机一次能走的航程是不同的。对于每次模拟，他想要知道最少需要降落多少次（包括最后一次）。需要注意的是起点可以任意选取。

## 输入格式

The first line of the standard input contains two integers $n$ and $s$ ($2\le n\le 1\ 000\ 000$, $1\le s\le 100$),separated by a single space,  denoting the number of airports along the equator and the number of airplane models Byteasar is considering.

The second line contains $n$ positive integers $l_1,l_2,\cdots,l_n$ ($l_1+l_2+\cdots+l_n\le 10^9$), separated by single spaces, specifying the distances between successive airports along the equator.

The number $l_i$ is the distance between the $i$-th and $(i+1)$-st (or $n$-th and first if $i=n$) in kilometers.

The third line contains $s$ integers $d_1,d_2,\cdots,d_s$ ($1\le d_i\le l_1+l_2+\cdots+l_n$), separated by single spaces. The number $d_i$ is the $i$-th airplane model's flight range in kilometers, i.e., the maximum distance it can fly before landing and refueling.

## 输出格式

Your program should print $s$ lines to the standard output: the $i$-th of these should contain a single integer, namely, the minimum lumber of flight segments (and thus also landings) necessary to fly the $i$-th airplane around the planet 3-SATurn along the equator, starting at an airport of choice, or the word NIE (Polish for no) if it is impossible to complete the journey with this airplane.

## 样例

### 样例输入 #1
```
6 4
2 2 1 3 3 1
3 2 4 11

```
### 样例输出 #1
```
4
NIE
3
2

```
## 提示

通过几年的努力，Byteasar最终拿到了飞行员驾驶证。为了庆祝这一事实，他打算买一架飞机并且绕Byteotia星球赤道飞行一圈。但不幸的是赤道非常长所以需要中途加几次油。现在已知赤道上面所有飞机场，所有飞机从飞机场起飞降落也可以加油。因为买飞机是个十分重大的决定，Byteasar决定寻求你的帮助。他将会让你模拟不同的飞行路线。自然这些飞机一次能走的航程是不同的。对于每次模拟，他想要知道最少需要降落多少次（包括最后一次）。需要注意的是起点可以任意选取。



---

---
title: "遥远的国度"
layout: "post"
diff: 省选/NOI-
pid: P3979
tag: ['线段树', '倍增', '最近公共祖先 LCA', '树链剖分']
---
# 遥远的国度
## 题目描述

`zcwwzdjn` 在追杀 `zhx` ，而 `zhx` 逃入了一个遥远的国度。当 `zcwwzdjn` 准备进入遥远的国度继续追杀时，守护神 `RapiD` 阻拦了 `zcwwzdjn` 的去路，他需要 `zcwwzdjn` 完成任务后才能进入遥远的国度继续追杀。

问题是这样的：遥远的国度有 $n$ 个城市，这些城市之间由一些路连接且这些城市构成了一颗树。这个国度有一个首都，我们可以把这个首都看做整棵树的根，但遥远的国度比较奇怪，首都是随时有可能变为另外一个城市的。遥远的国度的每个城市有一个防御值，第 $i$ 个的防御值为 $val_i$，有些时候 `RapiD` 会使得某两个城市之间的路径上的所有城市的防御值都变为某个值。

`RapiD` 想知道在某个时候，如果把首都看做整棵树的根的话，那么以某个城市为根的子树的所有城市的防御值最小是多少。

由于 `RapiD` 无法解决这个问题，所以他拦住了 `zcwwzdjn` 希望他能帮忙。但 `zcwwzdjn` 还要追杀 `zhx`，所以这个重大的问题就被转交到了你的手上。
## 输入格式

第 $1$ 行两个整数 $n\ m$，代表城市个数和操作数。

第 $2$ 行至第 $n$ 行，每行两个整数 $u\ v$，代表城市 $u$ 和城市 $v$ 之间有一条路。

第 $n+1$ 行，有 $n$ 个整数，第 $i$ 个代表第 $i$ 个点的初始防御值 $val_i$。

第 $n+2$ 行一个整数 $id$，代表初始的首都为 $id$。

第 $n+3$ 行至第 $n+m+2$ 行，首先有一个整数 $opt$。

如果 $opt=1$，接下来有一个整数 $id$，代表把首都修改为 $id$；

如果 $opt=2$，接下来有三个整数 $x\ y\ v$，代表将 $x\ y$ 路径上的所有城市的防御值修改为 $v$；

如果 $opt=3$，接下来有一个整数 $id$，代表询问以城市 $id$ 为根的子树中的最小防御值。
## 输出格式

对于每个 $opt=3$ 的操作，输出一行代表对应子树的最小点权值。
## 样例

### 样例输入 #1
```
3 7
1 2
1 3
1 2 3
1
3 1
2 1 1 6
3 1
2 2 2 5
3 1
2 3 3 4
3 1
```
### 样例输出 #1
```
1
2
3
4
```
## 提示

对于 $20\%$ 的数据，$n\le 1000,m\le 1000$。

对于另外 $10\%$ 的数据，$n\le 100000,m\le 100000$，保证修改为单点修改。

对于另外 $10\%$ 的数据，$n\le100000,m \le 100000$，保证树为一条链。

对于另外 $10\%$ 的数据，$n\le 100000,m\le100000$，没有修改首都的操作。

对于 $100\%$ 的数据，$1 \leq n\le 100000,1 \leq m \le 100000,0<val_i<2^{31}$。


---

---
title: "[HEOI2014] 大工程"
layout: "post"
diff: 省选/NOI-
pid: P4103
tag: ['2014', '倍增', '各省省选', '河北', '虚树', '栈']
---
# [HEOI2014] 大工程
## 题目描述

国家有一个大工程，要给一个非常大的交通网络里建一些新的通道。

我们这个国家位置非常特殊，可以看成是一个单位边权的树，城市位于顶点上。

在 $2$ 个国家 $a,b$ 之间建一条新通道需要的代价为树上 $a,b$ 的最短路径的长度。

现在国家有很多个计划，每个计划都是这样，我们选中了 $k$ 个点，然后在它们两两之间 新建 $\dbinom{k}{2}$ 条新通道。

现在对于每个计划，我们想知道： 
1. 这些新通道的代价和。
2. 这些新通道中代价最小的是多少。
3. 这些新通道中代价最大的是多少。
## 输入格式

第一行 $n$ 表示点数。

接下来 $n-1$ 行，每行两个数 $a,b$ 表示 $a$ 和 $b$ 之间有一条边。点从 $1$ 开始标号。

接下来一行 $q$ 表示计划数。对每个计划有 $2$ 行，第一行 $k$ 表示这个计划选中了几个点。

第二行用空格隔开的 $k$ 个互不相同的数表示选了哪 $k$ 个点。
## 输出格式

输出 $q$ 行，每行三个数分别表示代价和，最小代价，最大代价。

## 样例

### 样例输入 #1
```
10 
2 1 
3 2 
4 1 
5 2 
6 4 
7 5 
8 6 
9 7 
10 9 
5 
2 
5 4 
2
10 4 
2 
5 2 
2
6 1 
2 
6 1
```
### 样例输出 #1
```
3 3 3 
6 6 6 
1 1 1 
2 2 2 
2 2 2
```
## 提示

对于 $100\%$ 的数据，$1\le n\le 10^6,1\le q\le 5\times 10^4,\sum k\le 2\times n$。

每个测试点的具体限制见下表：

| 测试点编号 | $n$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: |
| $1\sim 2$ | $\le 10^4$ |  |
|$3\sim 5$  | $\le 10^5$ | 树的形态是链 |
| $6\sim 7$ | $\le 10^5$ |  |
| $8\sim 10$ | $\le 10^6$ |  |


---

---
title: "[BJWC2010] 严格次小生成树"
layout: "post"
diff: 省选/NOI-
pid: P4180
tag: ['2010', '倍增', '各省省选', '北京', 'O2优化', '生成树']
---
# [BJWC2010] 严格次小生成树
## 题目描述

小 C 最近学了很多最小生成树的算法，Prim 算法、Kruskal 算法、消圈算法等等。正当小 C 洋洋得意之时，小 P 又来泼小 C 冷水了。小 P 说，让小 C 求出一个无向图的次小生成树，而且这个次小生成树还得是严格次小的，也就是说：如果最小生成树选择的边集是 $E_M$，严格次小生成树选择的边集是 $E_S$，那么需要满足：($value(e)$ 表示边 $e$ 的权值) $\sum_{e \in E_M}value(e)<\sum_{e \in E_S}value(e)$。

这下小 C 蒙了，他找到了你，希望你帮他解决这个问题。

## 输入格式

第一行包含两个整数 $N$ 和 $M$，表示无向图的点数与边数。

接下来 $M$ 行，每行 $3$ 个数 $x,y,z$ 表示，点 $x$ 和点 $y$ 之间有一条边，边的权值为 $z$。

## 输出格式

包含一行，仅一个数，表示严格次小生成树的边权和。

## 样例

### 样例输入 #1
```
5 6
1 2 1 
1 3 2 
2 4 3 
3 5 4 
3 4 3 
4 5 6 
```
### 样例输出 #1
```
11
```
## 提示

数据中无向图**不保证无自环**。

对于 $50\%$ 的数据， $N\le 2000$，$M\le 3000$。

对于 $80\%$ 的数据， $N\le 5\times 10^4$，$M\le 10^5$。

对于 $100\%$ 的数据， $N\le 10^5$，$M\le 3\times10^5$，边权  $\in [0,10^9]$，数据保证必定存在严格次小生成树。


---

---
title: "Peaks"
layout: "post"
diff: 省选/NOI-
pid: P4197
tag: ['倍增', '生成树', '可持久化线段树']
---
# Peaks
## 题目描述

在 Bytemountains 有 $n$ 座山峰，每座山峰有他的高度 $h_i$。有些山峰之间有双向道路相连，共 $m$ 条路径，每条路径有一个困难值，这个值越大表示越难走。  

现在有 $q$ 组询问，每组询问询问从点 $v$ 开始只经过困难值小于等于 $x$ 的路径所能到达的山峰中第 $k$ 高的山峰，如果无解输出 $-1$。
## 输入格式

第一行三个数 $n,m,q$。
第二行 $n$ 个数，第 $i$ 个数为 $h_i$。

接下来 $m$ 行，每行三个整数 $a,b,c$，表示从 $a \to b$ 有一条困难值为 $c$ 的双向路径。
接下来 $q$ 行，每行三个数 $v,x,k$，表示一组询问。
## 输出格式

对于每组询问，输出一个整数表示能到达的山峰中第 $k$ 高的山峰的高度。
## 样例

### 样例输入 #1
```
10 11 4
1 2 3 4 5 6 7 8 9 10
1 4 4
2 5 3
9 8 2
7 8 10
7 1 4
6 7 1
6 4 8
2 1 5
10 8 10
3 4 7
3 4 6
1 5 2
1 5 6
1 5 8
8 9 2
```
### 样例输出 #1
```
6
1
-1
8

```
## 提示

### 数据规模与约定
对于 $100\%$ 的数据，$n \le 10^5$，$0 \le m,q \le 5\times 10^5$，$h_i,c,x \le 10^9$。


---

---
title: "【模板】多项式乘法逆"
layout: "post"
diff: 省选/NOI-
pid: P4238
tag: ['数学', '递推', '倍增', '递归', '逆元', '快速傅里叶变换 FFT']
---
# 【模板】多项式乘法逆
## 题目背景

注意：本题并不属于中国计算机学会划定的提高组知识点考察范围。
## 题目描述

给定一个多项式 $F(x)$ ，请求出一个多项式 $G(x)$， 满足 $F(x) * G(x) \equiv 1 \pmod{x^n}$。系数对 $998244353$ 取模。


## 输入格式

首先输入一个整数 $n$， 表示输入多项式的项数。  
接着输入 $n$ 个整数，第 $i$ 个整数 $a_i$ 代表 $F(x)$ 次数为 $i-1$ 的项的系数。  
## 输出格式

输出 $n$ 个数字，第 $i$ 个整数 $b_i$ 代表 $G(x)$ 次数为 $i-1$ 的项的系数。保证有解。
## 样例

### 样例输入 #1
```
5
1 6 3 4 9
```
### 样例输出 #1
```
1 998244347 33 998244169 1020
```
## 提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$ 0 \leq a_i \leq 10^9$。


---

---
title: "[CTSC2011] 幸福路径"
layout: "post"
diff: 省选/NOI-
pid: P4308
tag: ['2011', '倍增', '枚举', 'CTSC/CTS']
---
# [CTSC2011] 幸福路径
## 题目描述

有向图 $G$ 有 $n$ 个顶点 $1, 2, \cdots, n$，点 $i$ 的权值为 $w(i)$。

现在有一只蚂蚁，从给定的起点 $v_0$ 出发，沿着图 $G$ 的边爬行。开始时，它的体力为 $1$。每爬过一条边，它的体力都会下降为原来的 $\rho$ 倍，其中 $\rho$ 是一个给定的小于 $1$ 的正常数。而蚂蚁爬到某个顶点时的幸福度，是它当时的体力与该点权值的乘积。 

我们把蚂蚁在爬行路径上幸福度的总和记为 $H$。很显然，对于不同的爬行路径，$H$ 的值也可能不同。小 Z 对 $H$ 值的最大可能值很感兴趣，你能帮助他计算吗？注意，蚂蚁爬行的路径长度可能是无穷的。
## 输入格式

每一行中两个数之间用一个空格隔开。 

输入文件第一行包含两个正整数 $n,m$，分别表示 $G$ 中顶点的个数和边的条数。 

第二行包含 $n$ 个非负实数，依次表示 $n$ 个顶点权值  $w(1), w(2), \cdots, w(n)$。

第三行包含一个正整数 $v_0$，表示给定的起点。

第四行包含一个实数 $\rho$，表示给定的小于 $1$ 的正常数。 

接下来 $m$ 行，每行两个正整数 $x, y$，表示 $(x, y)$ 是 $G$ 的一条有向边。可能有自环，但不会有重边。
## 输出格式

仅包含一个实数，即 $H$ 值的最大可能值，四舍五入到小数点后一位。
## 样例

### 样例输入 #1
```
5 5 
10.0 8.0 8.0 8.0 15.0 
1 
0.5 
1 2 
2 3 
3 4 
4 2 
4 5
```
### 样例输出 #1
```
18.0
```
## 提示

对于 $100\%$ 的数据，$1\leq n \le 100$，$1\leq m \le 1000$，$0 < \rho \le 1 - 10^{-6}$，$0\leq w(i) \leq 100$。


---

---
title: "道路相遇"
layout: "post"
diff: 省选/NOI-
pid: P4320
tag: ['图论', '倍增', 'O2优化', '树链剖分', '圆方树']
---
# 道路相遇
## 题目描述

在 H 国的小 w 决定到从城市 $u$ 到城市 $v$ 旅行，但是此时小 c 由于各种原因不在城市 $u$，但是小 c 决定到在中途与小 w 相遇

由于 H 国道路的原因，小 w 从城市 $u$ 到城市 $v$ 的路线不是固定的，为了合理分配时间，小 c 想知道从城市 $u$ 到城市 $v$ 有多少个城市小 w 一定会经过，特别地，$u, v$ 也必须被算进去，也就是说无论如何答案不会小于 2

由于各种特殊的原因，小 c 并不知道小 w 的起点和终点，但是小 c 知道小 w 的起点和终点只有 $q$ 种可能，所以对于这 $q$ 种可能，小 c 都想知道小 w 一定会经过的城市数

H 国所有的边都是无向边，两个城市之间最多只有一条道路直接相连，没有一条道路连接相同的一个城市

任何时候，H 国不存在城市 $u$ 和城市 $v$ 满足从 $u$ 无法到达 $v$
## 输入格式

第一行两个正整数 $n,m$，表示 H 国的城市数，以及道路数。

下面 $m$ 行，每行两个不同的正整数 $u, v$，表示城市 $u$ 到城市 $v$ 之间有一条边。

然后一行一个正整数 $q$。
接下来 $q$ 行，每行两个正整数 $u, v$ 表示小 w 旅行的一种可能的路线
## 输出格式

输出共 $q$ 行，每行一个正整数
## 样例

### 样例输入 #1
```
5 6
1 2
1 3
2 3
3 4
4 5
3 5
1
1 5
```
### 样例输出 #1
```
3
```
## 提示

从城市 $1$ 到城市 $5$ 总共有 $4$ 种可能 : 

$1 \to 2 \to 3 \to 4 \to 5$

$1 \to 2 \to 3 \to 5$

$1 \to 3 \to 4 \to 5$

$1 \to 3 \to 5$

可以发现小 w 总会经过城市 $1,3,5$，所以答案为 $3$

你可以认为小 w 不会经过相同的城市两次，当然，如果你认为可以经过相同的城市两次也不会影响答案

subtask1 : 15分，$m = 5, q = 50$

subtask2 : 15分，$n = 100, q = 5000$

subtask3 : 20分，$n = 3000, q = 5\times 10^5$

subtask4 : 20分，$n = 499999, q = 5 \times 10^5, m = n-1$

subtask5 : 30分，$n = q = 5 \times 10^5$

对于所有数据 : $1\leq n\leq 5 \times 10^5, 1\leq q\leq 5\times 10^5, 1\leq m\leq \min(\frac{n(n-1)}{2}, 10^6)$


---

---
title: "【模板】多项式指数函数（多项式 exp）"
layout: "post"
diff: 省选/NOI-
pid: P4726
tag: ['倍增', '递归', 'O2优化', '快速傅里叶变换 FFT', '构造']
---
# 【模板】多项式指数函数（多项式 exp）
## 题目描述

给出 $n-1$ 次多项式 $A(x)$，求一个 $\bmod{\:x^n}$ 下的多项式 $B(x)$，满足 $B(x) \equiv \text e^{A(x)}$。系数对 $998244353$ 取模。
## 输入格式

第一行一个整数 $n$.

下一行有 $n$ 个整数，依次表示多项式的系数 $a_0, a_1, \cdots, a_{n-1}$.

保证 $a_0 = 0$.
## 输出格式

输出 $n$ 个整数，表示答案多项式中的系数 $a_0, a_1, \cdots, a_{n-1}$.
## 样例

### 样例输入 #1
```
6
0 927384623 817976920 427326948 149643566 610586717
```
### 样例输出 #1
```
1 927384623 878326372 3882 273455637 998233543
```
## 提示

对于 $100\%$ 的数据，$n \le 10^5$.


---

---
title: "[CERC2017] Donut Drone"
layout: "post"
diff: 省选/NOI-
pid: P4739
tag: ['2017', '线段树', '倍增']
---
# [CERC2017] Donut Drone
## 题目描述

You are building a simulation in which a drone explores a volatile torus-shaped planet. Technically,the drone is moving across a toroidal grid — a rectangular grid that wraps around circularly in both dimensions. The grid consists of cells organized into $r$ rows numbered $1$ through $r$ top to bottom and $c$
columns numbered $1$ through $c$ left to right. Each grid cell has a certain elevation — a positive integer.

![](https://cdn.luogu.com.cn/upload/image_hosting/c7d7xb1p.png)

The drone is initially located in the cell in the first row and first column. In each step the drone considers three cells: the cell directly to the right, the cell diagonally right-down and the cell diagonally right-up (wrapping around if necessary). The drone flies to the cell with the largest elevation of the three.

Two types of events may happen during the simulation:
   - “``move k``” — The drone makes $k$ steps.
   - “``change a b e``” — The elevation of the cell in row $a$ column $b$ changes to $e$.

Find the drone’s position immediately after each ``move`` event. You may assume that at each point in time, no sequence of three circularly consecutive cells in the same column will have the same elevation.
Hence, each drone step is well defined.

## 输入格式

The first line contains two integers $r$ and $c(3 \le r,c \le 2 000)$ — the number of rows and the number of columns of the toroidal grid. The $i-th$ of the following $r$ lines contains a sequence of $c$ integers $e_{i,1},e_{i,2},...,e_{i,c}(1 \le e_{i,j} \le 10^9)$ — the initial elevations of cells in row $i$.

The following line contains an integer $m(1 \le m \le 5 000)$ — the number of events. The $j-th$ of the following $m$ lines contains the $j-th$ event and is either of the form “``move k``” where $k$ is an integer such that $1 \le k \le 10^9$ or “``change a b e``” where $a,b$ and $e$ are integers such that $1 \le a \le r, 1 \le b \le c$ and $1 \le e \le 10^9$.

## 输出格式

Output $w$ lines where $w$ is the number of ``move`` events in the input — the $j-th$ line should contain the drone’s position (row and column numbers) after the $j-th$ ``move`` event in the input.

## 样例

### 样例输入 #1
```
4 4
1 2 9 3
3 5 4 8
4 3 2 7
5 8 1 6
4
move 1
move 1
change 1 4 100
move 1

```
### 样例输出 #1
```
4 2
1 3
1 4

```
### 样例输入 #2
```
3 4
10 20 30 40
50 60 70 80
90 93 95 99
3
move 4
change 2 1 100
move 4

```
### 样例输出 #2
```
3 1
2 1

```
## 题目翻译

输入一个循环矩阵（即第一行的上一行是最后一行，最后一行的下一行是第一行，最后一列的下一列是第一列）。你的初始位置在 $(1,1)$，每一步会走向右上、右、右下三个格子中权值最大的一个格子。

支持两种操作：

- 修改一个格子的权值
- 从当前位置走 $k$ 步，并输出目标位置


---

---
title: "[NOIP 2018 提高组] 保卫王国"
layout: "post"
diff: 省选/NOI-
pid: P5024
tag: ['动态规划 DP', '2018', '倍增', 'NOIP 提高组', '树链剖分', '动态 DP', '全局平衡二叉树']
---
# [NOIP 2018 提高组] 保卫王国
## 题目背景

NOIP2018 提高组 D2T3
## 题目描述

Z 国有 $n$ 座城市，$(n - 1)$ 条双向道路，每条双向道路连接两座城市，且任意两座城市都能通过若干条道路相互到达。  

Z 国的国防部长小 Z 要在城市中驻扎军队。驻扎军队需要满足如下几个条件： 

- 一座城市可以驻扎一支军队，也可以不驻扎军队。   
- 由道路直接连接的两座城市中至少要有一座城市驻扎军队。   
- 在城市里驻扎军队会产生花费，在编号为 $i$ 的城市中驻扎军队的花费是 $p_i$。      

小 Z 很快就规划出了一种驻扎军队的方案，使总花费最小。但是国王又给小 Z 提出了 $m$ 个要求，每个要求规定了其中两座城市是否驻扎军队。小 Z 需要针对每个要求逐一给出回答。具体而言，如果国王提出的第 $j$ 个要求能够满足上述驻扎条件（不需要考虑第 $j$ 个要求之外的其它要求），则需要给出在此要求前提下驻扎军队的最小开销。如果国王提出的第 $j$ 个要求无法满足，则需要输出 $-1$。现在请你来帮助小 Z。 
## 输入格式

第一行有两个整数和一个字符串，依次表示城市数 $n$，要求数 $m$ 和数据类型 $type$。$type$ 是一个由大写字母 `A`，`B` 或 `C` 和一个数字 `1`，`2`，`3` 组成的字符串。它可以帮助你获得部分分。你可能不需要用到这个参数。这个参数的含义在【数据规模与约定】中 有具体的描述。

第二行有 $n$ 个整数，第 $i$ 个整数表示编号 $i$ 的城市中驻扎军队的花费 $p_i$。

接下来 $(n - 1)$ 行，每行两个整数 $u,v$，表示有一条 $u$ 到 $v$ 的双向道路。 

接下来 $m$ 行，每行四个整数 $a, x, b, y$，表示一个要求是在城市 $a$ 驻扎 $x$ 支军队，在城市 $b$ 驻扎 $y$ 支军队。其中，$x,y$ 的取值只有 $0$ 或 $1$：
- 若 $x$ 为 $0$，表示城市 $a$ 不得驻扎军队。
- 若 $x$ 为 $1$，表示城市 $a$ 必须驻扎军队。
- 若 $y$ 为 $0$，表示城市 $b$ 不得驻扎军队。
- 若 $y$ 为 $1$，表示城市 $b$ 必须驻扎军队。    

输入文件中每一行相邻的两个数据之间均用一个空格分隔。 
## 输出格式

输出共 $m$ 行，每行包含一个个整数，第 $j$ 行表示在满足国王第 $j$ 个要求时的最小开销， 如果无法满足国王的第 $j$ 个要求，则该行输出 $-1$。 
## 样例

### 样例输入 #1
```
5 3 C3 
2 4 1 3 9 
1 5 
5 2 
5 3 
3 4 
1 0 3 0 
2 1 3 1 
1 0 5 0

```
### 样例输出 #1
```
12 
7 
-1
```
## 提示

#### 样例 1 解释

- 对于第一个要求，在 $4$ 号和 $5$ 号城市驻扎军队时开销最小。
- 对于第二个要求，在 $1$ 号、$2$ 号、$3$ 号城市驻扎军队时开销最小。   
- 第三个要求是无法满足的，因为在 $1$ 号、$5$ 号城市都不驻扎军队就意味着由道路直接连 接的两座城市中都没有驻扎军队。  

#### 数据规模与约定  

| 测试点编号 | $\text{type}$ | $n = m=$ |
|:-:|:-:|:-:|
| $1,2$ | `A3` | $10$ |
| $3,4$ | `C3` | $10$ |
| $5,6$ | `A3` | $100$ |
| $7$ | `C3` | $100$ |
| $8,9$ | `A3` | $2\times 10^3$ |
| $10,11$ | `C3` | $2\times 10^3$ |
| $12,13$ | `A1` | $10^5$ |
| $14, 15, 16$ | `A2` | $10^5$ |
| $17$ | `A3` | $10^5$ |
| $18,19$ | `B1` | $10^5$ |
| $20,21$ | `C1` | $10^5$ |
| $22$ | `C2` | $10^5$ |
| $23, 24, 25$ | `C3` | $10^5$ |

数据类型的含义：   

- `A`：城市 $i$ 与城市 $i + 1$ 直接相连。    
- `B`：任意城市与城市 $1$ 的距离不超过 $100$（距离定义为最短路径上边的数量），即如果这 棵树以 $1$ 号城市为根，深度不超过 $100$。   
- `C`：在树的形态上无特殊约束。   
- `1`：询问时保证 $a = 1,x = 1$，即要求在城市 $1$ 驻军。对 $b,y$ 没有限制。   
- `2`：询问时保证 $a,b$ 是相邻的（由一条道路直接连通）  
- `3`：在询问上无特殊约束。

对于 $100\%$的数据，保证 $1 \leq n,m ≤ 10^5$，$1 ≤ p_i ≤ 10^5$，$1 \leq u, v, a, b \leq n$，$a \neq b$，$x, y \in \{0, 1\}$。


---

---
title: "多项式三角函数"
layout: "post"
diff: 省选/NOI-
pid: P5264
tag: ['倍增', 'O2优化', '构造', '快速数论变换 NTT']
---
# 多项式三角函数
## 题目描述

给定一个 $n-1$ 次多项式 $A(x)$，求一个 $\bmod{\:x^n}$ 下的多项式 $F(x)$，满足 $F(x)\equiv\sin{A(x)}$ 或 $F(x)\equiv\cos{A(x)}$。

所有运算在 $\bmod\ 998244353$ 意义下进行。
## 输入格式

第一行 **两个** 整数 $n,type$，若 $type=0$ 代表求 $\sin$，若 $type=1$ 代表求 $\cos$；

第二行 $n$ 个整数，依次表示多项式的系数 $a_0,a_1,\cdots,a_{n-1}$。

保证 $a_0=0$。
## 输出格式

输出一行 $n$ 个整数，表示答案多项式中的系数 $f_0,f_1,\cdots,f_{n-1}$。
## 样例

### 样例输入 #1
```
8 0
0 4 2 6 1 5 3 7
```
### 样例输出 #1
```
0 4 2 332748113 998244338 931694687 998244320 72887640
```
### 样例输入 #2
```
8 1
0 4 2 6 1 5 3 7
```
### 样例输出 #2
```
1 0 998244345 998244345 665496220 332748123 44366450 133099314
```
## 提示

对于 $100\%$ 的数据：$n\leq10^5$，$a_i\in[0,998244352]\cap\mathbb{Z}$。

前 $5$ 个点 $type=0$，后 $5$ 个点 $type=1$。


---

---
title: "【XR-1】逛森林"
layout: "post"
diff: 省选/NOI-
pid: P5344
tag: ['倍增', '洛谷原创', 'O2优化', '最短路', '最近公共祖先 LCA', 'ST 表']
---
# 【XR-1】逛森林
## 题目背景

NaCly_Fish 和 PinkRabbit 是好朋友。

有一天她去森林里游玩，回去跟 PinkRabbit 说：“我发现好多棵会动的树耶！”

PinkRabbit 动了动一只兔耳朵：“这有什么好稀奇的，我用一只兔耳朵就能维护每棵树的形态。”

NaCly_Fish 不服：“不止这样，我还看到有一些传送门，能从一条树枝跳到另一条树枝上呢！”

PinkRabbit 动了动另一只兔耳朵：“这有什么好稀奇的，我用两只兔耳朵就能统计每个传送门的信息。”

![](https://cdn.luogu.com.cn/upload/pic/57782.png)

于是 NaCly_Fish 很郁闷，她向你求助，请帮帮她吧。

什么？你不愿意帮？

那她就不给你这题的分了。
## 题目描述

给你 $n$ 个节点的森林，初始没有边。

有 $m$ 个操作，分为两种：

$1\ u_1\ v_1\ u_2\ v_2\ w$：表示构建一个单向传送门，从 $u_1 \rightarrow v_1$ 简单路径上的所有节点，可以花费 $w$ 的代价，到达 $u_2 \rightarrow v_2$ 简单路径上的所有节点。若 $u_1$ 到 $v_1$ 或 $u_2$ 到 $v_2$ 不连通(由 $2$ 操作产生的边不连通)，则忽略此次操作。

$2\ u\ v\ w$：表示将 $u$ 和 $v$ 节点间连一条花费为 $w$ 的无向边，若 $u$ 和 $v$ 之间已连通(由 $2$ 操作产生的边连通)则忽略此次操作。

经过这 $m$ 次操作后，请你求出从 $s$ 节点出发，到每个节点的最小花费。
## 输入格式

第一行三个正整数 $n, m, s$，分别表示树的节点数、操作数、和起始节点。

接下来 $m$ 行，每行若干个正整数，表示一次操作。
## 输出格式

输出一行 $n$ 个整数，第 $i$ 个整数表示从 $s$ 节点出发，到 $i$ 节点的最小花费。特别地，若不能到达$i$节点，则输出 `-1`。
## 样例

### 样例输入 #1
```
9 11 5
2 2 1 2
2 3 1 5
2 4 2 10
2 5 3 9
2 6 5 3
2 7 6 6
2 8 7 2
2 9 4 2
1 1 1 4 9 2
1 8 5 1 6 1
1 3 6 9 6 1
```
### 样例输出 #1
```
1 1 1 1 0 1 7 9 1
```
## 提示

【样例说明】

这是样例中给出的树（严格来讲，这棵树也是一条链）：

![](https://cdn.luogu.com.cn/upload/image_hosting/g1kmzdbv.png)

有三个传送门，其中两个是这样的：

- 从 $1$ 号点可以花费 $2$ 的代价到达 $4 \rightarrow 9$ 简单路径上的所有节点（即 $4, 9$ 号点）。
- 从 $8 \rightarrow 5$ 简单路径上的所有节点（即 $8, 7, 6, 5$ 号点）可以花费 $1$ 的代价到达 $1 \rightarrow 6$ 简单路径上的所有节点（即 $1, 3, 5, 6$ 号点）。

容易看出从 $5$ 号节点出发，到达其它节点的最小花费分别为：$1, 1, 1, 1, 0, 1, 7, 9, 1$。

【数据规模与约定】

对于第 $1, 2$ 个测试点，$1 \le n \le 100$，$1 \le m \le 300$。

对于第 $3, 4$ 个测试点，$1 \le n \le 1000$，$1 \le m \le 3000$。

对于 $100\%$ 的数据，$1\le n \le 50000$，$1\le m \le 10^6$，$1\le u,v \le n$，$1\le w \le 100$。

对于第 $1$ ~ $10$ 个测试点，每个 $5$ 分。

对于第 $11, 12$ 个测试点，每个 $25$ 分。


---

---
title: "【XR-1】柯南家族"
layout: "post"
diff: 省选/NOI-
pid: P5346
tag: ['倍增', '离散化', 'O2优化', '可持久化线段树', '可持久化', '后缀数组 SA']
---
# 【XR-1】柯南家族
## 题目背景

xht37 最近沉迷于名侦探柯南。

在某集中，小兰又在怀疑柯南的真实身份了。为了让小兰不再怀疑，柯南编造出自己的家族背景来应对小兰的询问。
## 题目描述

这个家族一开始只有一个人，后来不断有人有了孩子，直到现在，这个家族有 $n$ 个人，第 $n$ 个人正是柯南。易知这个家族构成了一个 $n$ 个点的树形结构。

柯南为了使自己编造的家庭背景更加真实，他给家族中的每个人赋予了一个**智商值**。但是，一个人的**聪明程度**不仅仅只与他的**智商值**有关，还可能与他**祖先的聪明程度**及他**出生的时代**有关。

具体来说，在这个家族中，A 比 B 聪明**当且仅当** A 和 B 满足下面三种情况中的某一种：

1. A 的智商值比 B 的智商值高；
2. A 的智商值与 B 的智商值一样且 A 和 B 有不同的父亲，A 的父亲比 B 的父亲聪明；
3. A 的智商值与 B 的智商值一样且 A 和 B 的父亲是同一个人或某一个人没有父亲，A 比 B 后出生。

有一个很显然的结论是，这个家族中不会有两个人一样聪明。

柯南需要回答小兰的 $q$ 个询问。为了方便说明，假设第 $i$ 个出生的人编号为 $i$。

每个询问是下面三种情况中的某一种：

1. `1 x`：询问编号为 $x$ 的人在整个家族中聪明程度排第几。
2. `2 x k`：询问编号为 $x$ 的人及其祖先中第 $k$ 聪明的人的编号。
3. `3 x k`：询问编号为 $x$ 的人及其后代中第 $k$ 聪明的人的编号。

柯南还有许多案子要办，他不想在回答小兰的问题上浪费时间，他希望你能编程帮他回答小兰的所有询问。
## 输入格式

第 $1$ 行包含两个数 $n, q$，分别表示人数和询问次数。

第 $2$ 行包含 $n-1$ 个数 $f_{2 \dots n}$，其中 $f_i$ 表示 $i$ 的父亲。

第 $3$ 行包含 $n$ 个数 $a_{1 \dots n}$，其中 $a_i$ 表示 $i$ 的智商值。

接下来 $q$ 行每行两个或三个数表示一个合法询问，其中第一个数表示询问种类，后面一个或两个数为询问参数。
## 输出格式

输出 $q$ 行，每行一个数表示询问的答案。
## 样例

### 样例输入 #1
```
5 11
1 1 3 2
1 2 2 1 1
1 1
1 2
1 3
1 4
1 5
2 4 1
2 5 3
3 1 1
3 1 2
3 1 3
3 1 4
```
### 样例输出 #1
```
5
2
1
3
4
3
1
3
2
4
5
```
## 提示

【样例说明】

形成的树如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/eie1mrxb.png)

首先比较编号为 $2,3$ 的两个人，由于** $3$ 号的智商值与 $2$ 号的智商值一样且他们的父亲是同一个人，$3$ 号比 $2$ 号后出生**满足第 $3$ 种情况，因此 $3$ 号比 $2$ 号聪明。

再比较编号为 $4,5$ 的两个人，由于** $4$ 号的智商值与 $5$ 号的智商值一样且他们有不同的父亲，$4$ 号的父亲 $3$ 号比 $5$ 号的父亲 $2$ 号聪明**满足第 $2$ 种情况，因此 $4$ 号比 $5$ 号聪明。

再比较编号为 $1,5$ 的两个人，由于** $5$ 号的智商值与 $1$ 号的智商值一样且 $1$ 号没有父亲，$5$ 号比 $1$ 号后出生**满足第 $3$ 种情况，因此 $5$ 号比 $1$ 号聪明。

再根据第 $1$ 种情况比较编号为 $2,4$ 的两个人，可对 $5$ 人的聪明程度排序：$3 > 2 > 4 > 5 > 1$。

【数据规模与约定】

一共 $10$ 个测试点。

对于前 $20\%$ 的数据，$1 \le n, q \le 10 ^ 3$，每个测试点 $7$ 分，时限 1s。

对于另 $20\%$ 的数据，保证一个人最多只有一个儿子，每个测试点 $9$ 分，时限 4s。

对于另 $20\%$ 的数据，$1 \le n, q \le 10 ^ 5$，每个测试点 $9$ 分，时限 1.5s。

对于另 $20\%$ 的数据，保证只有第一种询问，每个测试点 $12$ 分，时限 1.5s。

对于 $100\%$ 的数据，$1 \le n, q \le 5 \times 10 ^ 5$，$1 \le a_i \le 10 ^ 9$，每个测试点 $13$ 分，时限 2.5s。


---

---
title: "树上后缀排序"
layout: "post"
diff: 省选/NOI-
pid: P5353
tag: ['字符串', '倍增', 'O2优化', '后缀数组 SA']
---
# 树上后缀排序
## 题目描述

给定一棵以 $1$ 为根包含 $n$ 个节点的树，保证对于 $2 \sim n$ 的每个节点，其父亲的编号均小于自己的编号。

每个节点上有一个的字符，一个节点所代表的字符串定义为从当前节点一直到根节点的简单路径上经过的所有字符连起来形成的字符串。

请你给这些字符串按照字典序排序。

特别地，如果两个节点所代表的字符串完全相同，它们的大小由它们父亲排名的大小决定，即谁的父亲排名大谁就更大；如果仍相同，则由它们编号的大小决定，即谁的编号大谁就更大。
## 输入格式

第一行包含一个正整数 $n$。

第二行包含 $n-1$ 个数 $f_{2 \dots n}$，其中 $f_i$ 表示 $i$ 的父亲。

第三行为一个包含 $n$ 个**小写字母**的字符串 $s$，其中 $s_i$ 表示编号为 $i$ 的节点上的字符。
## 输出格式

输出一行 $n$ 个正整数，第 $i$ 个正整数表示代表**排名第 $i$ 的字符串**的节点编号。
## 样例

### 样例输入 #1
```
5
1 1 3 2
abbaa
```
### 样例输出 #1
```
1 5 4 2 3
```
## 提示

对于 $20\%$ 的数据，$n \le 10 ^ 3$。

对于 $50\%$ 的数据，$n \le 10 ^ 5$。

对于 $100\%$ 的数据，$1 \le n \le 5 \times 10 ^ 5$。


---

---
title: "心上秋"
layout: "post"
diff: 省选/NOI-
pid: P5558
tag: ['动态规划 DP', '倍增', 'O2优化', '矩阵加速', '树链剖分']
---
# 心上秋
## 题目背景

辗转经由他人唇齿

多少日夜听闻你的故事

难道这情之一字

竟连抛生死亦不可探知

听说北国的那座城池

被冬雪覆了终日

等到故人长诀渐行渐远

转眼已隔两世

谁向生而死 谁患得患失

相顾也再无多时

画中人暗自 竟心荡神痴

一滴泪氤氲满纸

挥墨描眉目 提笔勾鬓丝

寥寥几笔竟如此

夜半无人处 对月展卷时

忽然看懂这相思

落款谁提了名字

————《心上秋》
## 题目描述

竟宁元年（前33年）正月，昭君出塞前一晚。

画师跌跌撞撞地来到昭君居住的宫殿。

     听说北国的那座城池
     被冬雪覆了终日
     等到故人长诀渐行渐远
     转眼已隔两世
                ——《心上秋》

如果再也不能相见的话，画师想着，他想给昭君留下些什么。

他想把他的画笔送给昭君。

**昭君的宫殿里有$N$个房间，有$N-1$条道路连接这些房间。**

**画师现在在宫殿的入口大厅$S$房间，他依稀记得，昭君的房间在$T$号。**

窗外，风雨大作，宫内忽暗忽明，一个人影也没有。

画家走进晦暗的通道，每条通道里的墙壁上都画有若干片枫叶，这是之前昭君让画师画的。昭君说，她特别喜欢秋天，尤其喜欢秋天的枫叶。

      并肩长谈过多少往事，恍然间黄昏已至    ——《心上秋》

通道内晦暗无比，画师想点亮通道内备好的蜡烛，他记得昭君有个习惯，**每个通道内的蜡烛数量就是墙上枫叶的数量。昭君若想点燃一条通道内的蜡烛，就会全部点燃，此时昭君认为这条通道已被点亮，并且不会再点亮任何枫叶数少于这条通道的通道**。

这应该是最后一次来到这个地方了，画师想着，他要按昭君的习惯，走到昭君的房间。

**现在画师想知道，他从宫殿大厅$S$走到昭君房间$T$，最多可以点亮多少通道。**
## 输入格式

第一行一个数$N$，表示宫殿房间数量。

接下来有$N-1$行，每行三个数$u_{i},v_{i},leaf_{i}$，表示$u,v$之间有一条通道，通道上画有$leaf_{i}$片枫叶。

接下来一个数$M$。

最后$M$行，每行两个数$S_{i},T_{i}$
## 输出格式

输出$M$行，对于每组$S_{i},T_{i}$，输出最多能够点亮的通道数。
## 样例

### 样例输入 #1
```
5
1 2 5
2 3 1
1 4 1
3 5 4
3
2 1
4 2
1 1

```
### 样例输出 #1
```
1
2
0

```
### 样例输入 #2
```
7
1 2 1
1 3 5
2 4 1
4 5 4
5 6 1
1 7 1
5
7 5
7 6
2 7
1 1
2 4
```
### 样例输出 #2
```
4
4
2
0
1

```
### 样例输入 #3
```
20
1 2 1
1 3 3
2 4 5
1 5 1
5 6 5
1 7 5
1 8 4
7 9 1
8 10 2
1 11 1
2 12 5
3 13 1
3 14 3
3 15 3
10 16 1
5 17 1
12 18 5
7 19 4
7 20 5
10
10 3
17 16
11 9
4 6
16 17
11 16
11 11
13 11
2 1
10 11
```
### 样例输出 #3
```
2
3
2
3
3
2
0
2
1
2

```
## 提示

| 数据编号 | N | M | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $100$ | $100$ | 无 |
| $2$ | $100$ | $100$ | 无 |
| $3$ | $100$ | $1000$ | 无 |
| $4$ | $10000$ | $10000$ | 无 |
| $5$ | $10000$ | $10000$ | $1$ |
| $6$ | $10000$ | $10000$ | $1,2$ |
| $7$ | $10000$ | $10000$ | $1,2$ |
| $8$ | $30000$ | $100000$ | 无 |
| $9$ | $30000$ | $100000$ | 无 |
| $10$ | $30000$ |$300000$  | 无 |
特殊性质$1$：$1<=leaf_{i}<=2$

特殊性质$2$：$u_{i}+1=v_{i}$

对于所有的数据，保证$1<=leaf_{i}<=5$

样例一解析：

![](https://cdn.luogu.com.cn/upload/image_hosting/eaxwdth6.png)

询问$1$：从$2$走到$1$最多点亮$1$条通道（$2-1$）

询问$2$：从$4$走到$2$最多点亮$2$条通道（$4-1,1-2$）

询问$3$：显然无法点亮通道。

样例二解析：

![](https://cdn.luogu.com.cn/upload/image_hosting/8z9tovt5.png))

询问$1$：从$7$走到$5$，可以点亮$4$个通道（$7-1,1-2,2-4,4-5$）

询问$2$：从$7$走到$6$，可以点亮$4$个通道（$7-1,1-2,2-4,4-5$），不点亮（$5-6$）是因为已经点亮（$4-5$）后无法点亮比枫叶数小于$4$的通道，易知这样是最优的，或者不点亮（$4-5$）而点亮（$5-6$），这同样是最优解。

询问$3$：从$2$走到$7$，可以点亮$2$个通道（$2-1$,$1-7$）

询问$4$：不经过任何通道。

询问$5$：经过$1$条通道（$2-4$）


     何处合成愁。离人心上秋。纵芭蕉，不雨也飕飕。都道晚凉天气好，有明月，怕登楼。

     年事梦中休。花空烟水流。燕辞归，客尚淹留。垂柳不萦裙带住。漫长是，系行舟。



---

---
title: "[USACO20JAN] Falling Portals P"
layout: "post"
diff: 省选/NOI-
pid: P6010
tag: ['贪心', '2020', '倍增', '二分', 'USACO', '凸包']
---
# [USACO20JAN] Falling Portals P
## 题目描述

有 $N$（$2 \leq N \leq 2 \times 10^5$）个世界，每个世界有一个传送门。初始时，世界 $i$（对于 $1 \leq i \leq N$）位于 $x$ 坐标 $i$，$y$ 坐标 $A_i$（$1 \leq A_i \leq 10^9$）。每个世界里还有一头奶牛。在时刻 $0$，所有的 $y$ 坐标各不相同，然后这些世界开始坠落：世界 $i$ 沿着 $y$ 轴负方向以 $i$ 单位每秒的速度移动。

在任意时刻，如果两个世界在某一时刻 $y$ 坐标相同（可能是非整数时刻），传送门之间就会“同步”，使得其中一个世界的奶牛可以选择瞬间传送到另一个世界。

对于每一个 $i$，在世界 $i$ 的奶牛想要去往世界 $Q_i$（$Q_i \neq i$）。帮助每头奶牛求出如果她以最优方案移动需要多少时间。

每个询问的输出是一个分数 $a/b$，其中 $a$ 和 $b$ 为互质的正整数，或者 $-1$，如果不可能到达。
## 输入格式

输入的第一行包含一个整数 $N$。

下一行包含 $N$ 个空格分隔的整数 $A_1,A_2,\ldots,A_N$。

下一行包含 $N$ 个空格分隔的整数 $Q_1,Q_2,\ldots,Q_N$。
## 输出格式

输出 $N$ 行，第 $i$ 行包含奶牛 $i$ 的旅程的时间。
## 样例

### 样例输入 #1
```
4
3 5 10 2
3 3 2 1
```
### 样例输出 #1
```
7/2
7/2
5/1
-1
```
## 提示

### 样例解释

考虑原先在世界 $2$ 的奶牛的答案。在时刻 $2$ 世界 $1$ 和世界 $2$ 同步，所以奶牛可以前往世界 $1$。在时刻 $\frac{7}{2}$ 世界 $1$ 和世界 $3$ 同步，所以奶牛可以前往世界 $3$。

### 子任务

- 测试点 $2 \sim 3$ 满足 $N \leq 100$。
- 测试点 $4 \sim 5$ 满足 $N \leq 2000$。
- 测试点 $6 \sim 14$ 没有额外限制。


---

---
title: "「ACOI2020」惊吓路径"
layout: "post"
diff: 省选/NOI-
pid: P6038
tag: ['2020', '线段树', '倍增', '二分', 'O2优化', 'ST 表']
---
# 「ACOI2020」惊吓路径
## 题目背景

![T6](https://s2.ax1x.com/2020/01/12/lopZpq.png)

3 年 E 班的同学们赢得了去南方的冲绳小岛的机会，在渚打败了鹰冈之后，他们受杀老师的邀请参加“试胆大会”。

试胆大会在一个黑漆漆的洞窟里面进行。赤羽 業（Akabane Karma）现在和奧田 愛美站在洞窟的门口。突然，業想到了一个事情。。。
## 题目描述

杀老师告诉过他们，洞窟可以近似地看成 $n$ 个点的外向树，因为地形原因，所以一个点到另一个点的边是有方向的，且边的方向都是同向的。这棵树的树根为入度为 $0$ 的点。每个点都有一个惊吓值，给出每个点的惊吓值 $a_i$。

杀老师告诉他们，这个洞穴有很多惊吓路径。如果两个节点 $u,v$ 构成的路径是一条惊吓路径的话，满足以下条件：

- $v$ 一定在 $u$ 的子树中。

- $u, v$ 这条路径上的所有的点的惊吓值的或值 $\geq k$。

走过一条惊吓路径就会收到杀老师的惊喜大礼。杀老师已经提前准备好了惊喜大礼，但是業当然已经知道杀老师有一些下流的意图，更别说惊喜大礼的数量可能不够！杀老师已经承诺有多少条惊吓路径就有多少个惊喜大礼。業已经通过一些神奇的途径知道了杀老师准备的惊喜大礼的个数，现在他想知道有多少条惊吓路径，也就是杀老师最少需要准备惊喜大礼的个数。如果不够，他就会揭穿杀老师的意图。现在業当然想赚，好好捉弄一下杀老师。所以他~~作弊~~提前得到了杀老师的地图，想问这个图里面有多少条惊吓路径？
## 输入格式

第一行两个整数 $n,k$。

第二行 $n$ 个整数，表示每个点的惊吓值。

接下来 $n-1$ 行，每行有两个整数 $u,v$ 表示节点 $u,v$ 之间有一条有向边，节点 $u$ 可以到达节点 $v$，**节点 $v$ 不可以到达节点 $u$**。




## 输出格式

一行一个整数，表示这个洞穴的惊吓路径条数。
## 样例

### 样例输入 #1
```
5 10
5 9 6 4 2
3 1
3 4
1 2
1 5

```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
7 5
6 7 4 5 7 8 9
1 2
2 3
2 4
1 5
5 6
5 7

```
### 样例输出 #2
```
16
```
### 样例输入 #3
```
8 5
4 3 2 5 6 7 6 2
1 2
1 5
2 3
2 4
5 6
5 7
6 8

```
### 样例输出 #3
```
16
```
## 提示

#### 样例解释 #1

![](https://cdn.luogu.com.cn/upload/image_hosting/lqu4ejku.png)

只有两条路径满足条件：

1. $3\to 1\to 2$，这条路径的所有点的惊吓值的或值是 $6\operatorname{or}5\operatorname{or}9=15$。

2. $1 \to 2$，这条路径的所有点的惊吓值的或值是 $5\operatorname{or}9=13$。

------------
#### 数据范围 
**本题采用捆绑测试**。

- Subtask 1（10 points）：$n \leq 5 \times 10^3$，$k \leq 10^5$。    
- Subtask 2（30 points）：对于任意一条边，$v=u+1$，$n \leq 10^6$，$k,a_i \leq 10^9$。     
- Subtask 3（20 points）：$n \leq 10^5$，$k,a_i \leq 10^9$。    
- Subtask 4（40 points）：$n \leq 5 \times 10^5$，$k,a_i \leq 10^9$。

对于 $100\%$ 的数据，$1 \leq n \leq 10^6$，$1 \leq k,a_i \leq 10^9$。

------------
#### 提示
**第四个子任务中的测试点空间 256MB，其余子任务中的测试点空间 128MB。**


---

---
title: "Count on a tree II/【模板】树分块"
layout: "post"
diff: 省选/NOI-
pid: P6177
tag: ['倍增', '最近公共祖先 LCA', '树链剖分', '可持久化', '分块']
---
# Count on a tree II/【模板】树分块
## 题目背景

原 bzoj2589。
## 题目描述

给定一个 $n$ 个节点的树，每个节点上有一个整数，$i$ 号点的整数为 $val_i$。

有 $m$ 次询问，每次给出 $u',v$，您需要将其解密得到 $u,v$，并查询 $u$ 到 $v$ 的路径上有多少个不同的整数。

解密方式：$u=u' \operatorname{xor} lastans$。

$lastans$ 为上一次询问的答案，若无询问则为 $0$。
## 输入格式

第一行有两个整数 $n$ 和 $m$。

第二行有 $n$ 个整数。第 $i$ 个整数表示 $val_i$。

在接下来的 $n-1$ 行中，每行包含两个整数 $u,v$，描述一条边。

在接下来的 $m$ 行中，每行包含两个整数 $u',v$，描述一组询问。
## 输出格式

对于每个询问，一行一个整数表示答案。
## 样例

### 样例输入 #1
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
3 8
```
### 样例输出 #1
```
4
4
```
## 提示

对于 $100\%$ 的数据，$1\le u,v\le n\le 4\times 10^4$，$1\le m\le 10^5$，$0\le u',val_i<2^{31}$。


---

---
title: "[NOI Online #1 入门组] 魔法"
layout: "post"
diff: 省选/NOI-
pid: P6190
tag: ['动态规划 DP', '图论', '2020', '倍增', '矩阵加速', '最短路', 'NOI Online']
---
# [NOI Online #1 入门组] 魔法
## 题目描述

C 国由 $n$ 座城市与 $m$ 条有向道路组成，城市与道路都从 $1$ 开始编号，经过 $i$ 号道路需要 $t_i$ 的费用。

现在你要从 $1$ 号城市出发去 $n$ 号城市，你可以施展最多 $k$ 次魔法，使得通过下一条道路时，需要的费用变为原来的相反数，即费用从 $t_i$ 变为 $-t_i$。请你算一算，你至少要花费多少费用才能完成这次旅程。

注意：使用魔法只是改变一次的花费，而不改变一条道路自身的 $t_i$；最终的费用可以为负，并且一个城市可以经过多次（包括 $n$ 号城市）。 
## 输入格式

输入的第一行有三个整数，分别代表城市数 $n$，道路数 $m$ 和魔法次数限制 $k$。

第 $2$ 到第 $(m + 1)$ 行，每行三个整数。第 $(i + 1)$ 行的整数 $u_i, v_i, t_i$ 表示存在一条从 $u_i$ 到 $v_i$ 的单向道路，经过它需要花费 $t_i$。
## 输出格式

输出一行一个整数表示最小的花费。
## 样例

### 样例输入 #1
```
4 3 2
1 2 5
2 3 4
3 4 1

```
### 样例输出 #1
```
-8
```
### 样例输入 #2
```
2 2 2
1 2 10
2 1 1

```
### 样例输出 #2
```
-19
```
## 提示

#### 输入输出样例 1 解释

依次经过 $1$ 号道路、$2$ 号道路、$3$ 号道路，并在经过 $1,2$ 号道路前使用魔法。 

#### 输入输出样例 2 解释

依次经过 $1$ 号道路、$2$ 号道路、$1$ 号道路，并在两次经过 $1$ 号道路前都使用魔法。 

#### 数据规模与约定

本题共 $20$ 个测试点，各测试点信息见下表。

| 测试点编号 | $n \leq$ | $m \leq$ | $k \leq$ | 无环 |
| :----------: | :--------: | :---------: | :--------: | :----: |
| $1 \sim 2$ | $5$ | $20$ | $0$ | 不保证 |
| $3 \sim 4$ | $10$ | $20$ | $50$ | 不保证 |
| $5 \sim 6$ | $10$ | $20$ | $0$| 不保证 |
| $7 \sim 8$ | $20$ | $200$ | $50$ | 是 |
| $9 \sim 10$ | $20$ | $200$ | $0$ | 不保证 |
| $11 \sim 12$ | $100$ | $200$ | $50$ | 是 |
| $13 \sim 14$ | $100$ | $200$ | $50$ | 不保证 |
| $15 \sim 18$ | $100$ | $2500$ | $1000$ | 不保证 |
| $19 \sim 20$ | $100$ | $2500$ | $10^6$ | 不保证 |

对于【无环】一栏为“是”的测试点，保证给出的图是一张有向无环图，否则不对图的形态做任何保证。

对于全部的测试点，保证：
- $1 \leq n \leq 100$，$1 \leq m \leq 2500$，$0 \leq k \leq 10^6$。
- $1 \leq u_i, v_i \leq n$，$1 \leq t_i \leq 10^9$。
- 给出的图无重边和自环，且至少存在一条能从 $1$ 到达 $n$ 的路径。

**民间数据使用 [CYaRon](https://github.com/luogu-dev/cyaron) 在 5 分钟内生成。如果发现数据有问题，请在讨论版发帖或私信 @[StudyingFather](/user/22030)**


---

---
title: "要有光"
layout: "post"
diff: 省选/NOI-
pid: P6396
tag: ['字符串', '动态规划 DP', '图论', '贪心', '2020', '倍增', '最短路', '回文自动机 PAM']
---
# 要有光
## 题目背景

$$ \text{Der mir zeigt wo ich bin}$$   
$$_\texttt{告诉我身在何方}  $$
$$\text{Divano}$$   
$$_\texttt{神啊}$$  
$$\text{Sei mein Licht}  $$
$$_\texttt{做我的光}$$
$$\text{Ich sm chte mich dir schenken}$$  
$$_\texttt{我愿将自己赐予与你}$$
$$\text{Noch vor dem Sonnenaufgang}$$  
$$_\texttt{在晨曦来临之前}$$


&emsp;&emsp;那时正值春深，丛林里生灵闹哄哄地雀跃，享受着空气中升腾的灵气。  
&emsp;&emsp;“嗖”的一声，一团银灰色的小东西突然从她眼前的地面划过，要不是腾起的尘土在阳光下悠闲地闪烁，她甚至怀疑是自己花了眼。  
&emsp;&emsp;紧接着，又“嗖”的一声，这次她看清楚了，是一只雪白的幼龄狐妖，“还……有点可爱。”  
&emsp;&emsp;“真走运，捉了这只，就可以交差啦。”她，虽年少却赫赫有名的除妖师，绫，急忙跟了上去。
## 题目描述

万物有灵，法术亦是如此。任何法术都等价为一段**仅包括大小写字母**的字符串 $S=s_1s_2\dots s_n$，现规定如下几种法术记号：

- **元素**。即字符串中的每个字符。在本题中，元素仅为大小写字母。
- **法术大小**。即字符串长度。记号为 $|S|$ 。
- **空法术**。大小为 $0$ 的法术为空法术。
- **等法术**。对于法术 $S,T$ 。当且仅当 $|S|=|T|,\forall i \leq |S| , s_i = t_i$ 时，称 $S$ 与 $T$ 为等法术，记为 $S=T$  。
- **逆法术**。设现有法术 $S=s_1s_2\dots s_n$，称法术 $T$ 是 $S$ 的逆法术，当且仅当 $|S|=|T|$ 且 $\forall i \leq |S| , s_i=t_{n-i+1}$。本题将 $T$ 记作 $S_r$。
- **逆法术对**。称两法术 $S$，$T$ 构成逆法术对 $(S,T)$，当且仅当 $T=S_r$。
- **归法术**。设现有法术 $S$，称 $S$ 为归法术当且仅当 $S$ 对应的字符串为**回文串**。特别地，**空法术被视作归法术**。
- **子法术**。设现有法术 $S$ ，则对于 $1\le i\le j\le |S|$ ，称 $T=s_is_{i+1}\dots s_j$ 为 $S$ 的子法术，并规定子法术的记号 $S[i,j]$ 。当 $i>j$ 时，$S[i,j]$ 为空法术。

---

现在，绫有一个法术源 $S_0$, 而她已经凝练出了一个初始的法术 $S=S_0$。对于每种妖魔，都有一个法术弱点  $T$。绫的法术性火，而火系法术又以淬光之术为上等。所以绫想要练习淬光之术。只要绫通过以下淬光法术变换使 $S=T$，就能轻易击败妖魔：

- **光归**。对于**任意非空法术** $S$，保留其**最大归法术后缀**。若$|S|=n$即取一个最小的 $i \in [1,n]$ 使得 $S[i+1,n]$ 为归法术，并令 $S \leftarrow T$。**允许 $T$ 为空法术**。消耗时间 $A$。
- **光辉**。对于**归法术** $S$，在 $S_0$ 中寻找一个**子归法术** $T$，满足 $S$ 为 $T$ 的**最大归法术后缀**（其定义见 "光归" ），并令 $S\leftarrow T$。**空法术**被认为是**任何法术的后缀**。消耗时间 $B$。
- **光隐**。对于**非空归法术** $S$，$|S|=n$ 删去其长度相等且长度**不大于 $k$ **的**前缀与后缀**。即取一个 $i\in[1,\min\{k,\lfloor\frac{n-1}2\rfloor\}]$，使 $T=S[1+i,n-i]$，并令 $S\leftarrow T$。特别地，$T$ **不可以为空法术**，消耗时间 $C$。
- **光腾**。对于**非空归法术** $S,|S|=n$，在其左右加上一对逆法术对。即取一逆法术对 $(P,Q)$，设 $|P|=|Q|=l$，使 $T=p_1p_2\dots p_ls_1s_2\dots s_nq_1q_2\dots q_l$，且 $T$ **须为 $S_{0}$ 的子法术** ，并令 $S\leftarrow T$。消耗时间 $D$。
- **光弋**。对于**任意非空法术** $S,|S|=n$ ，在其前端加入任意元素。即取一个元素 $a$，使 $T=as_1s_2\dots s_n$，并令 $S\leftarrow T$，消耗时间 $E$。光弋变换玄妙莫测，绫还没有熟练掌握此法术变换。所以**在使用此变换之后，无法再使用其它类型的法术变换**。

现在绫想知道，对于不同妖魔的法术弱点 $T$，自己至少要消耗多少时间进行如上法术变换使 $S=T$。**每组询问间互不干扰**。

## 输入格式

第一行输入一个**仅包含大小写字母**的字符串，表示绫的法术源 $S_0$。由题意，初始法术 $S=S_0$。  

第二行输入一个正整数 $k$，表示**光隐**变换所允许删去前缀后缀的最长长度。  

第三行输入五个正整数 $A,B,C,D,E$，表示每种法术变换的消耗时间。   

第四行一个正整数 $q$，表示询问组数。  

接下来 $q$ 行，每行包含两个正整数 $l,r$，表示一种妖魔的法术弱点为 $T=S_0[l,r]$。

## 输出格式

对于每个询问，输出一行一个整数，表示第 $i$ 个询问的答案。
## 样例

### 样例输入 #1
```
ababa
2
3 2 4 2 1
3
1 5
2 3
1 3
```
### 样例输出 #1
```
0
5
3
```
### 样例输入 #2
```
aaaaaa
1
3 1 4 1 10
2
2 4
2 3
```
### 样例输出 #2
```
7
8
```
## 提示

#### 样例解释 #1

对于第一个询问，因为 $T=\texttt{"ababa"}=S$，不需要操作。

对于第二个询问，$T=\texttt{"ba"}$，最优策略为先使用一次**光隐**，得到 $S'=\texttt{"a"}$；接着使用一次**光弋**，在 $S'$ 前添加元素 $\texttt{'b'}$ 得到 $S''=\texttt{"ba"}=T$，耗时 $4+1=5$。
 
对于第三个询问，$T=\texttt{"aba"}$，最优策略为使用一次**光归**，得到 $S'=\texttt{"aba"}=T$。耗时 $3$。

------------
#### 数据范围
对于不同的测试点，我们约定数据规模如下:

| 测试点编号 | $\left\vert S \right\vert,\left\vert T \right\vert \le$ | $q\le$ | 特殊限制 |
|:-:|:-:|:-:|:-:|
| $1 \sim 5$ | $10^3$ | $10^3$ | 无 |
| $6 \sim 9$ | $10^5$ | $10^5$ | 初始法术只有一种元素 |
| $10 \sim 20$ | $10^5$ | $10^5$ | 无 |

对于 $100\%$ 的数据，$1 \le q,|S| \leq 10^5$，$1 \leq A,B,C,D,E \leq 10^9$，$1 \leq l \leq r \leq |S|$，$1 \leq k \leq 5$。

------------
### 题目背景 ( 续 )
&emsp;&emsp;这边，绫还在摸索着变换法术，却感觉腰间的令牌被抓了一下。“喂？！”  
&emsp;&emsp;只见一个披头散发的少女正半跪着扒在她的腰间，左手还提着银灰色毛发的小兔子的一对耳朵，“你……是刚才那只狐狸？”绫尴尬地收回法术，不自觉地伸出手揉了揉少女头顶雪白的兽耳，心想着这只狐狸精得有多傻。“我可是除妖师哟，你不怕吗？”  
&emsp;&emsp;“……绫？”少女并没有理会绫的话，只是努力地认出了令牌上刻着的名字。  
&emsp;&emsp;绫好奇的目光撞上了少女璀璨的碧绿双眸，又不经意间扫过小巧的鼻梁，玲珑的小嘴，白皙的脖子，但再随着如凝的肌肤滑下……  
&emsp;&emsp;一直被视作男儿的绫哪见过这般风景，只觉得自己大脑当了机，还隐约嗅到出自鼻腔的铁锈味儿，身体便向后靠倒在一棵树干上，连忙用双手捂住滚烫的脸颊。  
&emsp;&emsp;“绫？绫？你怎么啦？！”少女心急地凑上去，绫吓得下意识往后退，却忘记身后是一棵粗壮的树干。“欸，绫手上的，是血吗……”双眼紧闭的绫听得出来少女像是被吓到了，看来还是一只没开过荤的狐狸精呢。  
&emsp;&emsp;“绫……你没事吧……”少女分明带着哭腔，小心翼翼地学着自己还是小狐狸的时候妈妈照顾自己的方式，在绫的身上东摸西摸。  
&emsp;&emsp;“我，我没事……”绫已经不敢想象究竟是哪些部位在触碰自己的皮肤了，“你……你先变回狐狸……快！”绫当然想把少女推开，却又怎么敢伸出手触碰少女呢？  
&emsp;&emsp;少女闻言，一怔，但还是乖乖变回了一只狐狸，还不忘叼起几欲逃走的兔子。  
&emsp;&emsp;绫赶忙收拾了自己的窘相，惊恐地扶着树干，确认自己的人身安全后，轻轻捏住小狐狸的后颈，提起在地上的两小只。  
&emsp;&emsp;“以后不许再胡乱变成人形了，听到没有！”绫后怕地警告着小狐狸，却见右手的小狐狸直勾勾地盯着左手的小兔子，而左手的小兔子好像想钻进自己的手心里，哪有听她的话呀……  
&emsp;&emsp;“哎，算了……”绫把小狐狸放在肩头，把似乎吓晕的小兔子递给她，“一会儿再吃哦。”（雨兔兔：我好难qwq。）  
&emsp;&emsp;“就算……捡了一只宠物吧。”绫心里想着。  

&emsp;&emsp;（未完待续www……）


---

---
title: "[省选联考 2020 A 卷] 树"
layout: "post"
diff: 省选/NOI-
pid: P6623
tag: ['2020', '倍增', '各省省选', '字典树 Trie', '位运算']
---
# [省选联考 2020 A 卷] 树
## 题目描述

给定一棵 $n$ 个结点的有根树 $T$，结点从 $1$ 开始编号，根结点为 $1$ 号结点，每个结点有一个正整数权值 $v_i$。

设 $x$ 号结点的子树内（包含 $x$ 自身）的所有结点编号为 $c_1,c_2,\dots,c_k$，定义 $x$ 的价值为：

$
val(x)=(v_{c_1}+d(c_1,x)) \oplus (v_{c_2}+d(c_2,x)) \oplus \cdots \oplus (v_{c_k}+d(c_k, x))
$

其中 $d(x,y)$ 表示树上 $x$ 号结点与 $y$ 号结点间唯一简单路径所包含的边数，$d(x, x) = 0$。$\oplus$ 表示异或运算。

请你求出 $\sum\limits_{i=1}^n val(i)$ 的结果。

## 输入格式

第一行一个正整数 $n$ 表示树的大小。

第二行 $n$ 个正整数表示 $v_i$。

接下来一行 $n-1$ 个正整数，依次表示 $2$ 号结点到 $n$ 号结点，每个结点的父亲编号 $p_i$。

## 输出格式

仅一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5
5 4 1 2 3
1 1 2 2
```
### 样例输出 #1
```
12
```
## 提示

【样例解释 $1$】

$val(1)=(5+0)\oplus(4+1)\oplus(1+1)\oplus(2+2)\oplus(3+2)=3$。

$val(2)=(4+0)\oplus(2+1)\oplus(3+1) = 3$。

$val(3)=(1+0)=1$。

$val(4)=(2+0)=2$。

$val(5)=(3+0)=3$。

和为 $12$。

【数据范围】

对于 $10\%$ 的数据：$1\leq n\leq 2501$；

对于 $40\%$ 的数据：$1\leq n\leq 152501$；

另有 $20\%$ 的数据：所有 $p_i=i-1$（$2\leq i\leq n$）；

另有 $20\%$ 的数据：所有 $v_i=1$（$1\leq i\leq n$）；

对于 $100\%$ 的数据：$1\leq n,v_i \leq 525010$，$1\leq p_i\leq n$。


---

---
title: "「StOI-2」简单的树"
layout: "post"
diff: 省选/NOI-
pid: P6798
tag: ['数学', '倍增', '前缀和']
---
# 「StOI-2」简单的树
## 题目描述

给定一棵以 $1$ 为根，由 $n$ 个点组成的有根树，每个点有点权 $c_{i}$ 。

定义每个点的 $val$ 值为：以它为根的子树内所有 $c_{i}$ 的最大值。

定义函数 $f(x,y)$ 表示将 $c_{x}$ 改为 $y$ 后整棵树的 $val$ 值之和。

现在请您回答 $q$ 组询问，每次询问给定 $3$ 个量 $(l,r,a)$ ，请求出 $\sum\limits_{i=l}^{r}{f(a,i)}$ 对 $998,244,353$ 取模的结果。
## 输入格式

**本题强制在线**

第一行三个正整数，$n$、$q$ 和 $opt$，分别表示树的点数、询问数和控制强制在线的量。

第二行 $n$ 个正整数，表示每个点的点权。

接下来 $n-1$ 行，每行两个正整数 $u_{i}$ 和 $v_{i}$，表示树的每一条边。

接下来 $q$ 行，每行三个正整数 $l',r',a'$ ，请计算出真实的 $l,r,a$ 后完成询问。

- $l = (( l' + opt \times lastans )\bmod n )$ $+ 1$
- $r = (( r' + opt \times lastans )\bmod n )$ $+ 1$
- $a = (( a' + opt \times lastans )\bmod n )$ $+ 1$

其中 $lastans$ 表示上一组询问的答案，初始为 $0$ 。

如果此时出现 $l > r$ 的情况，请交换 $l$ 和 $r$ 。
## 输出格式

对于每组询问，输出最终的答案。
## 样例

### 样例输入 #1
```
5 3 0
5 3 4 2 1
1 2
1 3
2 4
2 5
1 3 5
2 4 1
1 3 4
```
### 样例输出 #1
```
42
48
52
```
## 提示

## 样例解释

真实的 $(l,r,a)$ 为：

- $(2,4,1)$
- $(3,5,2)$
- $(2,4,5)$

---

## 数据范围

对于 $10\%$ 的数据：$1 \leq n,q \leq 100 $ 。   
对于 $20\%$ 的数据：$1 \leq n,q \leq 3000 $ 。   
对于另 $20\%$ 的数据：$1 \leq l',r',c_{i} \leq 2 $ 。   
对于另 $20\%$ 的数据：$l'=r'$ 。   
对于前 $80\%$ 的数据：$opt=0$ 。   
对于 $100\%$ 的数据：$1 \leq n,q \leq 5 \times 10^{5} ，1 \leq c_{i} , a' , l' , r' \leq n$ 。


---

---
title: "[JOISC 2020] 首都"
layout: "post"
diff: 省选/NOI-
pid: P7215
tag: ['2020', '倍增', '点分治', 'JOI（日本）']
---
# [JOISC 2020] 首都
## 题目背景

JOI 国是一个庞大的国度。
## 题目描述

JOI 国拥有 $N$ 个城镇，编号为 $1$ 到 $N$，这些城镇由 $N-1$ 条双向道路连接。

JOI 国还拥有 $K$ 个城市，编号为 $1$ 到 $K$，第 $i$ 个城镇属于第 $C_i$ 个城市。

现在 JOI 国的总理 JOI 君 114514 世要挑选一个城市作为首都，从首都中的任一个城镇到达另一个首都中的城镇可以只经过首都中的城镇，但这明显是不合理的。

所以 JOI 君 114514 世要进行合并城市，合并城市 $x$ 和城市 $y$ 就会把城市 $y$ 里的所有小镇归为城市 $x$。

求能找到首都的最小合并次数。
## 输入格式

第一行两个整数 $N,K$ 代表城镇数和城市数。    
接下来 $N-1$ 行每行两个整数 $u,v$ 代表一条双向边。   
接下来 $N$ 行第 $i$ 行一个整数 $C_i$ 代表第 $i$ 个城镇属于第 $C_i$ 个城市。
## 输出格式

一行一个整数代表最小的合并次数。
## 样例

### 样例输入 #1
```
6 3
2 1
3 5
6 2
3 4
2 3
1
3
1
2
3
2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
8 4
4 1
1 3
3 6
6 7
7 2
2 5
5 8
2
4
3
1
1
2
3
4
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
12 4
7 9
1 3
4 6
2 4
10 12
1 2
2 10
11 1
2 8
5 3
6 7
3
1
1
2
4
3
3
2
2
3
4
4
```
### 样例输出 #3
```
2
```
## 提示

#### 样例 1 解释

可以将城市 $1$ 和 $3$ 合并，然后选择城市 $1$ 作为首都。

#### 子任务

|子任务|特殊性质|分数|
|:-:|:-:|:-:|
|$1$|$N \le 20$|$1$|
|$2$|$N \le 2000$|$10$|
|$3$|每个城镇最多与两个城镇相连|$30$|
|$4$|无|$59$|

对于 $100\%$ 的数据，$1 \le K,u,v \le N \le 2 \times 10^5$，保证从任何一个城镇出发都能到达其他城镇，$1 \le C_i \le K$。

#### 说明

翻译自 [第１９回日本情報オリンピック　春季トレーニング合宿](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/index.html) [Day4 A 首都](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/day4/capital_city.pdf)。


---

---
title: "[省选联考 2021 A/B 卷]  宝石"
layout: "post"
diff: 省选/NOI-
pid: P7518
tag: ['倍增', '二分', '各省省选', '2021', '数据结构', 'O2优化', '可持久化线段树']
---
# [省选联考 2021 A/B 卷]  宝石
## 题目背景

**链的部分分官方数据有误。这里已经修改，如仍有误请反馈。**
## 题目描述

欧艾大陆上有 $n$ 座城市，城市从 $1 \sim n$ 编号，所有城市经由 $n - 1$ 条无向道路互相连通，即 $n$ 座城市与 $n - 1$ 条道路构成了一棵树。

每座城市的集市上都会出售宝石，总共有 $m$ 种不同的宝石，用 $1 \sim m$ 编号。$i$ 号城市的集市出售的是第 $w_i$ 种宝石，一种宝石可能会在多座城市的集市出售。

K 神有一个宝石收集器。这个宝石收集器能按照顺序收集至多 $c$ 颗宝石，其收集宝石的顺序为：$P_1, P_2, \ldots , P_c$。更具体地，收集器需要先放入第 $P_1$ 种宝石，然后才能再放入第 $P_2$ 种宝石，之后再能放入第 $P_3$ 种宝石，以此类推。其中 $P_1, P_2, \ldots , P_c$ 互不相等。

K 神到达一个城市后，如果该城市的集市上出售的宝石种类和当前收集器中需要放入的种类相同，则他可以在该城市的集市上购买一颗宝石并放入宝石收集器中；否则他只会路过该城市什么都不做。

现在 K 神给了你 $q$ 次询问，每次给出起点 $s_i$ 与终点 $t_i$，他想知道如果从 $s_i$ 号城市出发，沿最短路线走到 $t_i$ 号城市后，他的收集器中最多能收集到几个宝石？（在每次询问中，收集器内初始时没有任何宝石。起点与终点城市集市上的宝石可以尝试被收集）
## 输入格式

第一行，包含三个正整数 $n, m, c$，分别表示城市数，宝石种类数，收集器的容量。  
第二行，包含 $c$ 个正整数 $P_i$。数据保证 $1 \le P_i \le m$ 且这些数互不相等。  
第三行，包含 $n$ 个正整数 $w_i$，表示每个城市集市上出售的宝石种类。  
接下来 $n - 1$ 行，每行两个正整数 $u_i, v_i$，表示一条连接 $u_i$ 和 $v_i$ 号城市的道路。  
接下来一行，包含一个正整数 $q$，表示询问次数。  
接下来 $q$ 行，每行两个正整数 $s_i, t_i$，表示该次询问的起点与终点。
## 输出格式

按输入顺序输出 $q$ 行，每行一个整数，表示询问的答案。
## 样例

### 样例输入 #1
```
7 3 3
2 3 1
2 1 3 3 2 1 3
1 2
2 3
1 4
4 5
4 6
6 7
5
3 5
1 3
7 3
5 7
7 5

```
### 样例输出 #1
```
2
2
2
3
1

```
### 样例输入 #2
```
见附件中的 gem/gem2.in
```
### 样例输出 #2
```
见附件中的 gem/gem2.ans
```
### 样例输入 #3
```
见附件中的 gem/gem3.in
```
### 样例输出 #3
```
见附件中的 gem/gem3.ans
```
## 提示

**【数据范围】**

对于所有测试数据：$1 \le n, q \le 2 \times {10}^5$，$1 \le c \le m \le 5 \times {10}^4$，$1 \le w_i \le m$。

每个测试点的具体限制见下表：

| 测试点编号 | $n, q \le$ | 特殊限制 |
|:-:|:-:|:-:|
| $1 \sim 2$ | $10$ | 无 |
| $3 \sim 5$ | $1000$ | 无 |
| $6 \sim 10$ | $2 \times {10}^5$ | $m \le 300$ |
| $11 \sim 14$ | $2 \times {10}^5$ | $u_i = i$，$v_i = i + 1$ |
| $15 \sim 20$ | $2 \times {10}^5$ | 无 |


---

---
title: "[JOISC 2021] イベント巡り 2 (Event Hopping 2) (Day4)"
layout: "post"
diff: 省选/NOI-
pid: P7562
tag: ['贪心', '倍增', '2021', '颜色段均摊（珂朵莉树 ODT）', 'JOI（日本）']
---
# [JOISC 2021] イベント巡り 2 (Event Hopping 2) (Day4)
## 题目背景

**因洛谷限制，本题不予评测每个 Subtask 的第 1 ~ 20 个测试点，您可以 [点此](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/event2-data.zip) 下载所有数据自行评测或在 [这里](https://www.luogu.com.cn/problem/U159034) 测试，若您希望写本题题解，建议您在通过 [本题](https://www.luogu.com.cn/problem/P7562) 与 [每个 Subtask 前 20 个测试点](https://www.luogu.com.cn/problem/U159034) 之后再写题解。**

## 题目描述

IOI Park 将有 $n$ 场活动。

这些活动的编号从 $1$ 到 $n$。 活动 $i$ 从时间 $L_i+10^{-1}$ 到时间 $R_i-10^{-1}$ 举行。数据保证 $L_i$ 和 $R_i$ 是整数。

JOI 君决定参加其中的 $k$ 个活动。但是，JOI 君不能在中间加入或离开每个活动。**在两个活动场所间移动的时间忽略不计**。

JOI 君希望参加编号较小的活动。严格来说，JOI 君参加的 $k$ 个活动的编号依次为 $a_1,\cdots,a_k$，其中 $1 \le a_1 < \cdots < a_k \le n$。如果序列 $(a_1, \cdots, a_k)$ 的编号小于 $(b_1, \cdots, b_k)$，当且仅当存在 $j\ (1 \le j \le k)$ 满足在区间 $[1,j-1]$ 里的所有 $l$ 都有 $a_l=b_l$ 和 $a_j<b_j$。



给出每个活动的信息和 JOI 君参加的活动个数 $k$，判断 JOI 君是否可以参加 $k$ 个活动，如果可以，输出所有的 $k$ 个活动的编号。


## 输入格式

第一行，两个正整数 $n,k$。

第 $2 \sim n + 1$ 行，每行 $2$ 个正整数，$L_i, R_i$。
## 输出格式

如果 JOI 君可以参加 $k$ 个活动：
- 输出 $k$ 行。
- 我们设 JOI 君参与的 $k$ 个活动的编号为 $a_1, a_2, \cdots, a_k\ (1\le a_1 < \cdots < a_k \le n）$，你需要在第 $j$ 行输出 $a_j\ (1\le j \le k)$。 请注意，序列 $(a_1, \cdots, a_k)$ 必须是 **最小字典序**。




如果 JOI 君无法参加 $k$ 个活动，输出 $\texttt{-1}$。
## 样例

### 样例输入 #1
```
5 4
1 3
2 5
8 9
6 8
10 15

```
### 样例输出 #1
```
1
3
4
5

```
### 样例输入 #2
```
4 3
1 4
3 5
4 9
7 10

```
### 样例输出 #2
```
-1

```
### 样例输入 #3
```
10 6
77412002 93858605
244306432 318243514
280338037 358494212
439397354 492065507
485779890 529132783
571714810 632053254
659767854 709114867
718405631 733610573
786950301 815106357
878719468 899999649

```
### 样例输出 #3
```
1
2
4
6
7
8

```
### 样例输入 #4
```
20 16
250732298 258217736
26470443 34965880
252620676 260043105
692063405 697656580
497457675 504191511
391372149 397942668
858168758 867389085
235756850 241022021
585764751 593366541
207824318 217052204
661682908 671226688
886273261 892279963
770109416 778960597
264372562 270395107
176883483 186662376
509929119 519063796
109491630 118520141
162731982 168101507
662727316 668317158
757072772 765493222

```
### 样例输出 #4
```
1
2
4
5
6
7
8
9
10
11
12
13
14
15
16
17

```
## 提示

#### 样例 #1 解释

有 $2$ 种方式可以参加正好 $4$ 个活动。

- 参加 $1, 3, 4, 5$；
- 参加 $2, 3, 4, 5$。

数列 $(1,3,4,5)$ 比数列 $(2, 3, 4, 5)$ 字典序小，所以输出 $1, 3, 4, 5$。

#### 样例 #2 解释

无论怎么选择都不可能正好参加 $3$ 个活动，所以输出 $\tt -1$。

#### 样例 #3 解释

本样例满足所有 Subtask 的条件。

#### 数据规模与约定

**因洛谷限制，本题不予评测每个 Subtask 的第 $1\sim 20$ 个测试点。**

**本题采用 Subtask 计分法。**

| Subtask | 分值占比百分率 | $n$ | $L_i$ |
| :----: | :----: | :----: | :----:|
| $1$ | $7\%$ | / | $L_i \le L_{i+1}\ (1 \le i \le n − 1)$ |
| $2$ | $1\%$ | $\le20$ | / |
| $3$ | $31\%$ | $\le 3 \times 10^3$ |/ |
| $4$ | $61\%$ | / | / |

**注：斜线表示无特殊限制。**

对于 $100\%$ 的数据：
- $1\le n\le 10^5$；
- $1 \le k \le n$；
- $1\le L_i < R_i \le 10^9 (1\le i \le n)$。


#### 说明

本题译自 [第２０回日本情報オリンピック 2020/2021春季トレーニング合宿 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/index.html) [競技 4 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/2021-sp-d4-notice.pdf) [T1 日文题面](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/event2.pdf)。



---

---
title: "[ONTAK2010] Peaks 加强版"
layout: "post"
diff: 省选/NOI-
pid: P7834
tag: ['2010', '倍增', 'Kruskal 重构树', '深度优先搜索 DFS', '可持久化线段树']
---
# [ONTAK2010] Peaks 加强版
## 题目背景

原题链接：[P4197 Peaks](https://www.luogu.com.cn/problem/P4197)
## 题目描述

给定一张 $n$ 个点、$m$ 条边的无向图，第 $i$ 个点的权值为 $a_i$，边有边权。

有 $q$ 组询问，每组询问给定三个整数 $u, x, k$，求从 $u$ 开始只经过权值 $\leq x$ 的边所能到达的权值第 $k$ 大的点的权值，如果不存在输出 $-1$。

**本题强制在线。即：每次查询输入的是 $u', x', k'$，则 $u = (u' \operatorname{xor} \text{lastans}) \bmod n + 1$，$k$ 的解密方式与之相同，$x = x' \operatorname{xor} \text{lastans}$**。
## 输入格式

第一行，三个整数 $n, m, q$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$；

接下来 $m$ 行，每行三个整数 $s, t, w$，表示一条边的两个端点和权值；

接下来 $q$ 行，每行三个整数 $u', x', k'$。

**注意：处理第一组数据和无解时的 $\text{lastans} = 0$。**
## 输出格式

对于每组询问，输出一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
10 11 3
1 2 3 4 5 6 7 8 9 10
1 4 4
2 5 3
9 8 2
7 8 10
7 1 4
6 7 1
6 4 8
2 1 5
10 8 10
3 4 7
3 4 6
0 5 5
1 6 8
7 8 1
```
### 样例输出 #1
```
1
-1
8
```
## 提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq m, q \leq 5 \times 10^5$，$1 \leq s, t \leq n$，$1 \leq a_i, w \leq 10^9$，$0 \leq u', x', k' < 2^{31}$。


---

---
title: "[JOI 2022 Final] 铁路旅行 2 (Railway Trip 2)"
layout: "post"
diff: 省选/NOI-
pid: P8163
tag: ['倍增', '2022', 'O2优化', 'JOI（日本）']
---
# [JOI 2022 Final] 铁路旅行 2 (Railway Trip 2)
## 题目描述

IOI 铁路公司在一条铁轨上运营线路。铁轨为一条直线，该铁轨上有 $N$ 个车站，编号为 $1 \sim N$。车站 $i$ 与车站 $i + 1$ 之间由一条铁轨直接连接。

IOI 铁路公司正在运营 $M$ 条线路，编号为 $1 \sim M$。线路 $j$ 的起点为 $A_j$，终点为 $B_j$，列车在每一站均会停靠，即如果 $A_j < B_j$，一列 $j$ 号线的列车会按顺序在车站 $A_j, A_j + 1, \ldots, B_j$ 停靠。如果 $A_j > B_j$，一列 $j$ 号线的列车会按顺序在车站 $A_j, A_j - 1, \ldots, B_j$ 停靠。

JOI 君是一个旅行者。他有 $Q$ 个旅行计划。在第 $k$ 个旅行计划中他计划从车站 $S_k$ 通过乘坐列车前往车站 $T_k$。

然而，JOI 君因长途跋涉而疲惫不堪。他希望他乘坐的列车均有空座以便休息。因此 JOI 君决定，只有当某条线路的起点站是第 $K$ 个或更早的车站时，他才会在该站乘坐该条线路的列车。换句话说，对于线路 $j$，如果 $A_j < B_j$，那么他只会在车站 $A_j, A_j + 1, \ldots, \min \{ A_j + K - 1, B_j - 1 \}$ 乘上线路 $j$ 的列车。如果 $A_j > B_j$，那么他只会在车站 $A_j, A_j - 1, \ldots, \max \{ A_j - K + 1, B_j + 1 \}$ 乘上线路 $j$ 的列车。

在这些条件下，JOI 君希望尽量减少乘坐火车的次数。

给出 IOI 铁路公司的线路信息和 JOI 君的计划，写一个程序计算对于 JOI 君的每一个计划，他所需的最小乘车次数。
## 输入格式

第一行，两个正整数 $N, K$。

第二行，一个正整数 $M$。

接下来 $M$ 行，第 $j$ 行两个正整数 $A_j, B_j$。

接下来一行，一个正整数 $Q$。

接下来 $Q$ 行，第 $k$ 行两个正整数 $S_k, T_k$。
## 输出格式

输出 $Q$ 行，第 $k$ 行一个数，表示对于 JOI 君的第 $k$ 个计划，他实现该计划所需的最小乘车次数。如果无论如何无法实现第 $k$ 个计划，则输出 `-1`。
## 样例

### 样例输入 #1
```
5 2
2
5 1
3 5
3
5 3
3 2
2 1

```
### 样例输出 #1
```
1
2
-1

```
### 样例输入 #2
```
6 3
2
1 6
5 1
4
5 1
6 3
3 6
2 1

```
### 样例输出 #2
```
1
-1
1
2

```
### 样例输入 #3
```
6 5
4
3 1
2 4
5 3
4 6
5
1 5
3 2
2 6
6 3
5 4

```
### 样例输出 #3
```
-1
1
2
-1
1

```
### 样例输入 #4
```
12 1
5
1 7
10 12
3 5
8 10
5 9
7
2 11
5 8
3 12
4 6
1 9
9 10
1 4

```
### 样例输出 #4
```
-1
1
4
-1
2
-1
1

```
## 提示

**【样例解释 \#1】**

对于第一个计划，JOI 君要从车站 $5$ 前往车站 $3$。具体地，此计划可以通过如下方式实现：JOI 君在车站 $5$ 乘上 $1$ 号线的列车，并在车站 $3$ 下车。JOI 君总共乘坐了一次列车。由于不可能花费比 $1$ 更少的乘车次数实现该计划，在第一行输出 $1$。

对于第二个计划，JOI 君要从车站 $3$ 前往车站 $2$。具体地，此计划可以通过如下方式实现：JOI 君在车站 $3$ 乘上 $2$ 号线的列车，并在车站 $4$ 下车；然后在车站 $4$ 乘上 $1$ 号线的列车，并在车站 $2$ 下车。JOI 君总共乘坐了两次列车。由于不可能花费比 $2$ 更少的乘车次数实现该计划，在第二行输出 $2$。

对于第一个计划，JOI 君要从车站 $2$ 前往车站 $1$。由于无论如何无法实现该计划，在第三行输出 `-1`。

这个样例满足子任务 $1, 2, 6$ 的限制。

**【样例解释 \#2】**

这个样例满足子任务 $1, 2, 6$ 的限制。

**【样例解释 \#3】**

这个样例满足子任务 $1, 2, 4, 6$ 的限制。

**【样例解释 \#4】**

这个样例满足子任务 $1, 2, 5, 6$ 的限制。

----

**【数据范围】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，$2 \le N \le {10}^5$，$1 \le K \le N - 1$，$1 \le M \le 2 \times {10}^5$，$1 \le Q \le 5 \times {10}^4$，$1 \le A_j, B_j, S_k, T_k \le N$，$A_j \ne B_j$，$S_k \ne T_k$，$(A_j, B_j) \ne (A_k, B_k)$（$j \ne k$），$(S_k, T_k) \ne (S_l, T_l)$（$k \ne l$）。

- 子任务 $1$（$8$ 分）：$N, M, Q \le 300$。
- 子任务 $2$（$8$ 分）：$N, M, Q \le 2000$。
- 子任务 $3$（$11$ 分）：$Q = 1$。
- 子任务 $4$（$25$ 分）：$K = N - 1$。
- 子任务 $5$（$35$ 分）：$A_j < B_j$，$S_k < T_k$。
- 子任务 $6$（$13$ 分）：无特殊限制。

----

**译自 [JOI 2022 Final](https://www.ioi-jp.org/joi/2021/2022-ho/index.html) T4「[鉄道旅行 2 ](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t4.pdf) / [Railway Trip 2](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t4-en.pdf)」**


---

---
title: "「Wdoi-2」死亡之后愈发愉悦"
layout: "post"
diff: 省选/NOI-
pid: P8541
tag: ['倍增', '二分', '洛谷原创', '交互题', 'Special Judge', 'O2优化', '洛谷月赛']
---
# 「Wdoi-2」死亡之后愈发愉悦
## 题目背景

落樱缤纷春不待，如果错过了这次机会，可能得等到紫藤绽放的春夏之际才能赏花了。  
但是两人依然无心在樱花树下席地而宴。

因为正体不明的灵体在两人面前倏现骤消的飘浮着。  
后来才明白这些四处飘浮的正体不明灵体，既非普通幽灵，也不是前阵子出现的怨灵。  
这些是神灵。本应超脱为神的灵体。

一般而言，神灵多半居住在神社里，其实它们是随处可见的没有固定型态的灵体。  
这些神灵让她们困惑不已。

超乎常人的强烈人欲、想法、恐惧与情感，是神灵出现的原因。一般而言，神灵很少危害人类，如果没有强烈的欲望。例如祈求丰收，或是除厄避邪等，是不会产生神灵的……

小神灵指引着灵梦与魔理沙深入命莲寺的地底，与千年复苏的敌人交手。从命莲寺墓地到莲池中央的梦殿大祀庙，从彷徨的亡灵到极具传说色彩的圣德太子，从欲望加速到小小的欲望星空，一切都显得那么不可思议。

「死亡之后，才能得到更加绚烂的重生。」
## 题目描述

**【这是一道交互题】**

定义 $f(x)$ 表示严格大于 $x$ 的最小的完全平方数，定义 $g(x)$ 为小于等于 $x$ 的最大的完全平方数。例如，$f(1)=f(2)=g(4)=g(8)=4$。

一个正整数是“可爱”的，当且仅当 $x-g(x)<f(x)-x$，例如，$1,5,11$ 是可爱的正整数，而 $3,8,15$ 不是。

为了倾听小神灵的愿望，主角组需要向神子询问。小神灵有一个最喜欢的正整数 $a$，神子可以根据灵梦给出的 $x\quad(x\in[0,10^9])$，向小神灵询问，而小神灵只能回答她，$a+x$ 是不是可爱的正整数（$\text{cute number}$）。

请通过适当的询问找出 $a$。
## 输入格式

第一行有一个正整数 $T$，表示数据组数。每一组之间互相独立。

接下来，对于每一组数据，你将可以进行以下两种操作：

- $\verb!? x!$：询问 $a+x$ 是否是 $\text{cute number}$。要注意，$x$ 的值应当在 $[0,10^9]$ 以内。对于正确的询问，交互库会返回一个数字 $1$ 或者 $0$，表示 $a+x$ 是/不是 $\text{cute number}$。
- $\verb|! a|$：报告你发现的 $a$。如果你给出的 $a$ 正确，该组数据结束。注意：报告操作不计入询问操作的总次数。

如果你的询问次数超过了 $100$，或者 $x$ 不符合数据范围，或者你报告的 $a$ 不正确，交互库会返回一个数字 $-1$。此时你应当立即结束程序，否则可能发生不可预知的错误。
## 样例

### 样例输入 #1
```
1

1

1

1

1

1

0

0

1
```
### 样例输出 #1
```

? 0

? 1

? 2

? 3

? 10

? 100

? 233

? 1919810

! 114514
```
## 提示

### 样例解释

样例当中的过程仅供参考。

样例当中，$a=114514$，是 $\text{cute number}$（因为 $338^2\le 114514 <339^2$，而 $114514-338^2=270<339^2-114514=407$）。

同样地，$a+0,a+1,a+2,a+3,a+10$ 均为 $\text{cute number}$。而 $a+100=114614$ 不是 $\text{cute number}$，因为 $338^2\le 114614 <339^2$，而 $114614-338^2=370\ge 339^2-114614=307$。

### 数据范围及约定

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|}\hline
\textbf{Subtask} & \bm{a\le } & \bm{T\le} & \textbf{特殊性质} & \textbf{分值}\\\hline
1 & 100 & 100 & - & 10\\\hline
3 & 10^9 & 2\times 10^3 & -  & 20\\\hline
2 & 10^{12} & 2\times 10^3 & \textbf{A}  & 30\\\hline
4 & 10^{12} & 2\times 10^3 & -  & 40\\\hline
\end{array}
$$

**特殊性质** $\textbf{A}$：保证 $a$ 是 $\text{cute number}$。

对于全部数据，保证 $1\le a\le 10^{12}$。你发起的询问当中，$x$ 的值应当在 $[0,10^9]$ 以内。

---

此外，你每个测试点的得分还与该测试点所有询问次数的最大值有关。具体而言，设某个测试点你询问操作一共进行了 $\text{max\_count}$ 次。

- 若 $\text{max\_count}< 64$，你将获得该测试点 $100\%$ 的分数；
- 若 $64\le \text{max\_count}< 81$，你将获得该测试点 $50\%$ 的分数；
- 若 $81\le \text{max\_count}< 100$，你将获得该测试点 $20\%$ 的分数；
- 若 $\text{max\_count}\ge 100$，你将不能获得该测试点的分数。


---

---
title: "动态图连通性"
layout: "post"
diff: 省选/NOI-
pid: P8860
tag: ['贪心', '倍增', '洛谷原创', 'O2优化', '最短路', '可持久化线段树', '洛谷月赛']
---
# 动态图连通性
## 题目描述

给定一张 $n$ 点 $m$ 边的**有向图**，初始时存在一条从 $1$ 到 $n$ 的路径。  

你需要处理 $q$ 组询问，每组询问给定一个 $[1,m]$ 中的正整数 $x$，如果原图中的第 $x$ 条边仍存在且当前的图中删去原图中的第 $x$ 条边后仍有一条从 $1$ 到 $n$ 的路径，则删除原图中的第 $x$ 条边。  

你需要报告每组询问中是否删去了第 $x$ 条边。 

**请注意：一组询问中删除某条边后，这条边会被永远删除。也就是询问之间会相互影响。**
## 输入格式

输入第一行三个正整数 $n,m,q$，分别表示有向图的点数，边数以及询问个数。   

接下来 $m$ 行，第 $i$ 行两个正整数 $u_i,v_i$，表示第 $i$ 条边由 $u_i$ 连向 $v_i$。  

接下来 $q$ 行，每行一个正整数 $x$，具体含义同题目描述。
## 输出格式

输出共 $q$ 行，每行一个正整数 $0$ 或 $1$。 

如果在这组询问中删去了第 $x$ 条边，输出 $1$，否则输出 $0$。
## 样例

### 样例输入 #1
```
5 6 5
1 2
2 3
3 5
2 4
4 5
5 1
1
2
3
4
5
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
10 11 8
1 2
2 7
2 5
1 4
4 5
4 8
8 9
9 5
3 2
3 6
5 10
10
5
11
10
3
7
1
4

```
### 样例输出 #2
```
1
1
0
0
1
0
1
0
```
## 提示

#### 【样例解释】

在第一组样例中：

初始时，图中边集为 $\{ (1,2),(2,3),(3,5),(2,4),(4,5),(5,1) \}$。

若删去原图中的第 $1$ 条边 $(1,2)$，图中就没有 $1$ 到 $n$ 的路径，所以不能删除第 $1$ 条边。

若删去原图中的第 $2$ 条边 $(2,3)$，图中存在路径 $1 \to 2 \to 4 \to 5$，所以可以删去第 $2$ 条边，图中边集变为 $\{ (1,2),(3,5),(2,4),(4,5),(5,1) \}$。

若删去原图中的第 $3$ 条边 $(3,5)$，图中存在路径 $1 \to 2 \to 4 \to 5$，所以可以删去第 $3$ 条边，图中边集变为 $\{ (1,2),(2,4),(4,5),(5,1) \}$。

若删去原图中的第 $4$ 条边 $(2,4)$，图中就没有 $1$ 到 $n$ 的路径，所以不能删除第 $4$ 条边。

若删去原图中的第 $5$ 条边 $(4,5)$，图中就没有 $1$ 到 $n$ 的路径，所以不能删除第 $5$ 条边。

#### 【数据范围】

|  测试点编号  |    $n,m \leq$   |     $q \leq$    |            特殊限制           |
|:------------:|:---------------:|:---------------:|:-------------------------------:|
|  $1 \sim 2$  |      $1000$     |      $1000$     |                无               |
|  $3 \sim 6$  |      $5000$     | $2 \times 10^5$ |                无               |
|  $7 \sim 8$  | $2 \times 10^5$ | $2 \times 10^5$ | 保证所有询问中最多有 $1$ 条边没有被删除 |
| $9 \sim 12$ | $2 \times 10^5$ | $2 \times 10^5$ | 保证所有询问中最多有 $5$ 条边没有被删除 |
| $13 \sim 16$ | $2 \times 10^5$ | $2 \times 10^5$ |         将有向图视作无向图仍能得到正确答案        |
| $17 \sim 20$ | $2 \times 10^5$ | $2 \times 10^5$ |                无               |

对于所有数据，$1 \leq n,m,q \leq 2 \times 10^5$，给定的图无重边、自环，且存在一条 $1$ 到 $n$ 的路径。

**给出的两组大样例分别满足测试点 1 和测试点 13 的限制。**


---

---
title: "[USACO23JAN] Tractor Paths P"
layout: "post"
diff: 省选/NOI-
pid: P9019
tag: ['贪心', '倍增', 'USACO', '2023', '最短路']
---
# [USACO23JAN] Tractor Paths P
## 题目描述

**Note: The time limit for this problem is 4s, twice the default. The memory limit for this problem is 512MB, twice the default.**

Farmer John has $N
(2 \le N \le 2 \cdot 10^5)$ tractors, where the $i$-th tractor can only be used within the inclusive interval $[l_i,r_i]$. The tractor intervals have left endpoints $l_1<l_2<\cdots <l_N$ and right endpoints $r_1<r_2< \cdots <r_N$. Some of the tractors are special.

Two tractors $i$ and $j$ are said to be adjacent if $[l_i,r_i]$ and $[l_j,r_j]$ intersect. Farmer John can transfer from one tractor to any adjacent tractor. A path between two tractors $a$ and $b$ consists of a sequence of transfers such that the first tractor in the sequence is $a$, the last tractor in the sequence is $b$, and every two consecutive tractors in the sequence are adjacent. It is guaranteed that there is a path between tractor $1$ and tractor $N$. The length of a path is the number of transfers (or equivalently, the number of tractors within it minus one). 

You are given $Q (1 \le Q \le 2 \cdot 10^5)$ queries, each specifying a pair of tractors $a$ and $b (1 \le a<b \le N)$. For each query, output two integers: 

 - The length of any shortest path between tractor $a$ to tractor $b$.
 - The number of special tractors such that there exists at least one shortest path from tractor $a$ to tractor $b$ containing it. 
## 输入格式

The first line contains $N$ and $Q$.

The next line contains a string of length $2N$ consisting of Ls and Rs, representing the left and right endpoints in sorted order. It is guaranteed that for each proper prefix of this string, the number of Ls exceeds the number of Rs.

The next line contains a bit string of length $N$, representing for each tractor whether it is special or not.

The next $Q$ lines each contain two integers $a$ and $b$, specifying a query. 
## 输出格式

 For each query, the two quantities separated by spaces. 
## 样例

### 样例输入 #1
```
8 10
LLLLRLLLLRRRRRRR
11011010
1 2
1 3
1 4
1 5
1 6
1 7
1 8
2 3
2 4
2 5
```
### 样例输出 #1
```
1 2
1 1
1 2
2 4
2 3
2 4
2 3
1 1
1 2
1 2
```
## 提示

### Explanation for Sample 1

The $8$ tractor intervals, in order, are $[1,5],[2,10],[3,11],[4,12],[6,13],[7,14],[8,15],[9,16]$.

For the 4th query, there are three shortest paths between the 1st and 5th tractor: $1$ to $2$ to $5$, $1$ to $3$ to $5$, and $1$ to $4$ to $5$. These shortest paths all have length $2$.

Additionally, every tractor $1,2,3,4,5$
is part of one of the three shortest paths mentioned earlier, and since $1,2,4,5$ are special, there are $4$ special tractors such that there exists at least one shortest path from tractor $1$ to $5$ containing it. 

### Scoring

 - Inputs $2-3$: $N,Q \le 5000$
 - Inputs $4-7$: There are at most $10$ special tractors.
 - Inputs $8-16$: No additional constraints.
## 题目翻译

### 题目描述

**注意：这个问题的时间限制是4秒，内存限制是512MB，是默认值的两倍。**

农民约翰有 $N
(2 \le N \le 2 \cdot 10^5)$ 台拖拉机, 其中第 $i$ 台拖拉机只能在序列 $[l_i,r_i]$ 内使用。拖拉机有左端点 $l_1<l_2<\cdots <l_N$ 和右端点 $r_1<r_2< \cdots <r_N$. 有一些拖拉机是特别的。

如果 $[l_i,r_i]$ 和 $[l_j,r_j]$ 相交，则两台拖拉机 $i$ 和 $j$ 是相邻的。 约翰可以从一辆拖拉机转移到任何相邻的拖拉机上。两台拖拉机 $a$ 和 $b$ 之间的路径由一个传输序列组成，这样序列中的第一个拖拉机是 $a$，序列中的最后一个拖拉机是 $b$，并且序列中的每两个连续的拖拉机相邻。 保证拖拉机 $1$ 和 拖拉机 $N$ 之间有一条路径。路径的长度是转移的数量 (或等价地，其中拖拉机的数量减去 $1$)。

给定 $Q (1 \le Q \le 2 \cdot 10^5)$ 组询问，每次给定 $a$ 和 $b (1 \le a<b \le N)$。 对于每组询问，你需要回答两个问题：

 - $a$ 到 $b$ 的最短路径。
 - 在保证传送次数的最少的情况下，有多少个特殊拖拉机的区间可能被某条最短路经过。

### 输入格式

第一行输入两个整数 $N$ 和 $Q$，表示有 $N$ 台拖拉机和 $Q$ 次询问。

第二行输入一个长度为 $2N$ 的字符串，由大写字母 `L` 和 `R` 组成，保证这个字符串的每个前缀中 `L` 的数量大于 `R` 的数量。

第三行输入一个长度为 $N$ 的字符串, 表示每个拖拉机是否特殊。

接下来 $Q$ 行输入两个整数 $a$ 和 $b$, 表示一次查询。

### 输出格式

对于每一组数据，一行两个数，表示答案。

### 提示

### 样例 $1$ 解释

$8$ 个拖拉机的时间间隔，按顺序，是 $[1,5],[2,10],[3,11],[4,12],[6,13],[7,14],[8,15],[9,16]$。

对于第四个查询, 第 $1$ 台和第 $5$ 台拖拉机之间有三条最短路径: $1 \rightarrow 2 \rightarrow 5$, $1 \rightarrow 3 \rightarrow 5$, 和 $1 \rightarrow 4 \rightarrow 5$。这些最短路径的长度都为 $2$。

另外, 拖拉机 $1,2,3,4,5$
都是前面提到的三条最短路径之一的一部分, 由于 $1,2,4,5$ 是特殊的，因此有 $4$ 台特殊拖拉机，这样存在至少一条包含拖拉机 $1$ 到 $5$ 的最短路径。

### 数据范围

 - 数据点 $2-3$： $N,Q \le 5000$
 - 数据点 $4-7$： 最多 $10$ 台特别的拖拉机。
 - 数据点 $8-16$： 没有额外的约束。
 
 翻译提供者：[shuqiang](https://www.luogu.com.cn/user/685964)


---

---
title: "[THUPC 2023 初赛] 公平合作"
layout: "post"
diff: 省选/NOI-
pid: P9138
tag: ['动态规划 DP', '博弈论', '倍增', '2023', 'Special Judge', 'O2优化', 'THUPC']
---
# [THUPC 2023 初赛] 公平合作
## 题目描述

在大地的尽头，一座灰白的灯塔矗立在漫长的海岸线上。这一片海域海流复杂、礁石嶙峋，却又是不少航线的必经之路。若没有如此高耸而明亮的灯塔为过路的船只照亮航路，或许会有更多不幸的生命葬身海底。为了看管好这一座海上明灯，一批训练有素的守望人轮流值守于此。日复一日的工作枯燥乏味却又不能有丝毫闪失，紧绷的神经直到下一班守望人到来才得以放松。

在电力普及之前，灯塔通常使用煤油灯为过往的水手指引前行的方向。每次为这座灯塔添加燃油时，需要两位守望人各自搬运一个容积为 $L$ 的油桶；而每次轮到 Y 和 S 所在的班组照料这座灯塔时，总是由 Y 和 S 负责为灯塔加油。将煤油搬运至灯室时，如果不装满油桶，对灯塔的正常运转也没有太大影响，无非是需要多来回搬运几趟。但是，如果两位守望人都想着偷懒，问题恐怕就不只是多几趟那么简单。Y 和 S 想到了一个好办法：互相为对方的油桶装油。

灯塔里有 $N$ 个用于将储存的煤油转移到油桶中的容器，其中第 $i$ 个容器的容积为 $a_i$。Y 和 S 先想办法决定由谁先装油。两人先后装油；轮到其中一位守望人装油时，这位守望人每次从所有容器中等概率地随机选出一个容器，将其装满油，并全部倒入对方的油桶中。两位守望人都可以在操作任意多次（可以是 0 次）后结束装油，但后手必须等先手结束后才能开始装油。Y 和 S 先后装完煤油后，两人会比一下谁把对方的油桶装得更满，再各自把自己的油桶搬运到灯室。但是，如果有谁某次选出一个容器后，把对方的油桶装满了，但容器里还有没倒出的煤油，那么这位倒霉的守望人就必须把两个油桶都独自搬到灯室——这也算是为单调的生活平添了几分乐趣。显然，如果先手某次随机选中的容器会使得油桶溢出，那么后手可以往先手的油桶里面装任意量的煤油，然后幸灾乐祸；因此我们约定：当先手溢出时，必定由先手搬两个油桶。

现在只剩下了一个问题：当 Y 和 S 都采取最优策略，使得对方搬的煤油尽可能地比自己多的时候，先手搬的煤油不多于后手的概率是多大？
## 输入格式

输入的第一行包括两个正整数 $N$ 和 $L$，分别表示转移用的容器数量和油桶的容积。

输入的第二行包括 $N$ 个正整数 $a_1, \cdots, a_N$，分别表示每个转移用的容器的容积。
## 输出格式

输出一个实数，表示先手搬的煤油不多于后手的概率。当你的输出与标准输出的绝对误差不超过 $10^{-6}$ 时，我们认为你的输出是正确的。
## 样例

### 样例输入 #1
```
2 4
1 2
```
### 样例输出 #1
```
0.687500000000000000

```
### 样例输入 #2
```
见附件中的 2.in
```
### 样例输出 #2
```
见附件中的 2.out
```
### 样例输入 #3
```
见附件中的 3.in
```
### 样例输出 #3
```
见附件中的 3.out
```
## 提示

#### 样例解释 1

可以证明，此时先手的策略一定是装满对方的油桶，且装满时必胜。经过若干次随机抽取后，能恰好将对方的油桶装满的概率为：

$$
\left(\frac{1}{2}\right)^2 + \binom{3}{1}\left(\frac{1}{2}\right)^3 + \left(\frac{1}{2}\right)^4 = \frac{11}{16}=0.6875
$$

#### 数据范围

对于 $100\%$ 的数据，保证 $1\le N\le 2\times 10^3$，$1\le L\le 10^9$，$1\le a_i\le 2\times 10^3$。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。


---

---
title: "「DBOI」Round 1 人生如树"
layout: "post"
diff: 省选/NOI-
pid: P9399
tag: ['倍增', '二分', 'O2优化', '树链剖分', '树论', '哈希 hashing']
---
# 「DBOI」Round 1 人生如树
## 题目背景

> _永远这么酷 永远永远这么酷_\
_像个冒险家一样 不断探着山顶的路_\
——《Hustle》

张均好望着窗外，朱芝心走过来坐在他旁边，折了一架纸飞机飞出去。他对张均好说，要带着对未来的期待，往前走，别回头。

正如 [命运](https://www.luogu.com.cn/problem/P6773) 所述，每个人的人生都是一棵树。它总在无限的随机与缘分中伸展，有的枝丫茂盛了，有些却也不可避免地枯萎。
## 题目描述

朱芝心用魔法得到了张均好的人生树。

这是一棵 $n$ 个节点的树，节点 $i$ 上有权值 $w_i$。

朱芝心想要观测 $m$ 次张均好的人生：

设**当前**张均好人生树上的节点数量为 $s$。

1. 输入四个整数 $u_1,v_1,u_2,v_2$。令 $u_1\to v_1$ 的简单路径上**顺次组成**的数组为 $a$，$u_2\to v_2$ 的简单路径上**顺次组成**的数组为 $b$。朱芝心认为张均好这两段人生的相似度是 $LRP(a,b)$，希望你求出它。保证 $1\leq u_1,v_1,u_2,v_2 \leq s$。

2. 输入两个整数 $u,w'$。朱芝心观测到了张均好的另外一种可能，因此你需要新建一个点权为 $w'$ 的节点，编号为 $s+1$，建立一条 $(s+1,u)$ 的无向边，其中 $u\leq s$。显然，此后 $s\leftarrow s+1$。

对于两个数组 $a,b$，设它们的相似度 $LRP(a,b)$ 表示最大的 $i$ 满足 $i\leq \min\{|a|, |b|\}$ 且**对于所有** $1\leq j\leq i$，都有 $b_j=a_j+j$。其中 $|a|$ 表示数组 $a$ 的长度。特殊地，若不存在这样的 $i$，则 $LRP(a,b) = 0$。

## 输入格式

第一行三个正整数 $n,m,idx$，分别表示树的节点数量，操作数量和该测试点所在 Subtask 编号。对于样例，有 $idx = 0$。

接下来一行 $n$ 个整数，第 $i$ 个整数表示 $w_i$，即点 $i$ 上的权值。

接下来 $n - 1$ 行，每行两个正整数 $u_i,v_i$，表示有一条 $(u_i,v_i)$ 的无向边。

接下来 $m$ 行，每行一个操作。每行第一个整数是 $opt$，后面的若干整数表示操作的具体内容。$opt=1$ 时表示是操作 $1$，$opt=2$ 时表示是操作 $2$。
## 输出格式

对于每个操作 $1$，输出一行，表示当前询问的 $LRP(a, b)$。
## 样例

### 样例输入 #1
```
9 3 0
7 3 2 4 6 5 5 3 7
1 2
2 3
2 4
4 5
4 6
1 7
7 8
7 9
2 9 10
1 3 5 8 10
1 3 6 8 10
```
### 样例输出 #1
```
4
3
```
### 样例输入 #2
```
13 5 0
15 12 9 11 5 6 16 14 15 10 12 1 2
7 8
5 6
2 9
1 2
4 5
8 2
9 10
2 3
10 11
3 4
3 13
3 12
1 1 6 7 11
1 12 12 13 13
2 1 10
2 2 11
1 14 14 15 15
```
### 样例输出 #2
```
6
1
1
```
## 提示

### 样例解释

对于样例一，第一个操作结束后，$w_{10}=10$，树如图所示：

![](https://s1.ax1x.com/2023/04/26/p9MV9pV.png)

- 对于第二个操作，第一条路径为 $3\to 2\to 4\to 5$，故 $a=\{2, 3, 4, 6\}$，第二条路径为 $8\to 7\to 9\to 10$，故 $b=\{3, 5, 7, 10\}$，由于 $3=2+1$，$5=3+2$，$7=4+3$，$10=6+4$，所以答案为 $4$；
- 对于第三个操作，$a=\{2, 3, 4, 5\}$，$b=\{3, 5, 7, 10\}$，由于 $3=2+1$，$5=3+2$，$7=4+3$，$10\ne 5+4$，所以答案为 $3$。

对于样例二，初始的树如图所示：

![](https://s1.ax1x.com/2023/04/26/p9MVZkR.png)


| Subtask | $n \le$ | $m \le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| Subtask 1 | $5000$ | $5000$ | 无 | $10$ |
| Subtask 2 | $10^5$ | $5\times{10}^4$ | A & B | $30$ |
| Subtask 3 | $10^5$ | $5\times{10}^4$ | B | $30$ |
| Subtask 4 | $10^5$ | $5 \times {10}^4$ | 无 | $20$ | 
| Subtask 5 | $10^5$ | $10^5$ | 无 | $10$ |

特殊性质 A：$v_i=u_i+1$。

特殊性质 B：保证无操作 2。

对于 $100\%$ 的数据，$1\leq n,m\leq 10^5$，$1\leq w_i,w'\leq 10^6$，$1\leq u_i,v_i\leq n$。  



---

---
title: "「SFCOI-3」进行一个走的行"
layout: "post"
diff: 省选/NOI-
pid: P9494
tag: ['倍增', '平衡树', '2023', '洛谷原创', 'O2优化', '差分']
---
# 「SFCOI-3」进行一个走的行
## 题目背景

**公告：注意存在 $l_i > r_i$ 的情况，此时操作无效。**

------------

小 L 热衷于行走。
## 题目描述

小 L 来到了一处景点，他想要在这里的主干道上行走。

主干道上有若干关键点，他可以将其抽象为一个长为 $n$ 的序列 $a$，每个 $a_i$ 都是一个三元组，可以表示为 $(l_i, r_i, v_i)$，其具体含义形如：

- 若 $r_i = -1$，表示一个需要买票进入的景点，票价为 $l_i$ 代币，游览完成后他会得到 $v_i$ 的愉悦值。
- 若 $r_i \neq -1$，表示一个礼品派发点，若他持有的代币面值之和 $x$ 满足 $l_i \leq x \leq r_i$，他可以领取一份礼品，并会得到 $v_i$ 的愉悦值。

他打算在这条主干道上行走 $m$ 次，每次他给出了行走起点 $l$ 和终点 $r$，一开始他持有的代币面值之和为 $x$，初始愉悦值为 $0$。

他将从 $l$ 开始向右依次经过 $i \in [l, r]$，他会做如下操作：

- 若 $r_i = -1$，如果他持有的代币在支付完当前景点门票费用后还有剩余，他会游览这个景点。
- 若 $r_i \neq -1$，如果可以，他会领取一份礼品。

请你帮他快速求出每次行走结束后他的愉悦值。
## 输入格式

第一行，两个整数 $n, m$；

接下来 $n$ 行，其中第 $i$ 行有三个整数 $l_i, r_i, v_i$；

接下来 $m$ 行，每行三个整数 $l, r, x$，表示一个询问。
## 输出格式

$m$ 行，每行一个整数，表示行走结束后他的愉悦值。
## 样例

### 样例输入 #1
```
4 10
1 1 4
5 -1 4
1 9 19
8 -1 10
1 1 11
2 2 4
3 3 5
4 4 14
1 2 1
2 3 9
3 4 1
1 3 9
2 4 8
1 4 10
```
### 样例输出 #1
```
0
0
19
10
4
23
19
23
23
23
```
## 提示

**本题开启捆绑测试。**

- Subtask 1（10 pts）：$1 \leq n, m \leq 5 \times 10^3$。
- Subtask 2（10 pts）：$r_i \neq -1$。
- Subtask 3（20 pts）：$r_i = -1$。
- Subtask 4（10 pts）：$1 \leq n, m \leq 7.5 \times 10^4$，性质 A。
- Subtask 5（20 pts）：$1 \leq n, m \leq 7.5 \times 10^4$。
- Subtask 6（10 pts）：数据在范围内随机生成，性质 B。
- Subtask 7（20 pts）：无特殊限制。

性质 A：$1 \leq l_i \leq 7.5 \times 10^4$，$r_i = -1$ 或 $1 \leq r_i \leq 7.5 \times 10^4$，$1 \leq x \leq 7.5 \times 10^4$。

性质 B：$r_i = -1$ 时 $1 \leq l_i \leq 2 \times 10^5$。

对于 $100\%$ 的数据：

- $1 \leq n, m \leq 2 \times 10^5$。
- $1 \leq l_i \leq 10^9$，$r_i = -1$ 或 $1 \leq r_i \leq 10^9$。
- $1 \leq v_i \leq 10^9$。
- $1 \leq l \leq r \leq n$，$1 \leq x \leq 10^9$。


---

---
title: "[CERC2019] Be Geeks!"
layout: "post"
diff: 省选/NOI-
pid: P9607
tag: ['2019', '线段树', '倍增', 'ST 表', 'ICPC', '笛卡尔树', '单调栈']
---
# [CERC2019] Be Geeks!
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Be Geeks!](https://contest.felk.cvut.cz/19cerc/solved/begeeks.pdf)」**
## 题目描述

音乐乐队 Be Geeks! 的名字并非偶然，因为所有成员都是真正的数学怪才。除此之外，他们喜欢研究数列的各种性质。下面是他们感兴趣的一个例子：
- 设 $A$ 是一个非空正整数序列，$A=(a_1, a_2, \dots, a_N)$。
- $G(i, j)=\gcd (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $M(i, j)=\max (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $P(i, j)=G(i, j)\times M(i, j)$，其中 $1\le i\le j\le N$。
- $F(A)=\sum P(i, j)[1\le i\le j\le N]$。

给出一个序列 $A$，你需要求出 $F(A)\bmod 1\,000\,000\,007$ 的值。
## 输入格式

第一行包含一个整数 $N\ (1\le N\le 2\times 10^5)$，代表序列 $A$ 的长度。

第二行包含 $N$ 个整数 $a_1, a_2, \dots, a_N\ (1\le a_i\le 10^9)$，代表序列 $A$。
## 输出格式

输出一个整数，代表 $F(A)\bmod 1\,000\,000\,007$ 的值。
## 样例

### 样例输入 #1
```
4
1 2 3 4

```
### 样例输出 #1
```
50

```
### 样例输入 #2
```
5
2 4 6 12 3

```
### 样例输出 #2
```
457

```


---

