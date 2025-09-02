---
title: "求区间所有后缀最大值的位置"
layout: "post"
diff: 普及/提高-
pid: B3667
tag: ['单调队列', 'O2优化']
---
# 求区间所有后缀最大值的位置
## 题目描述

给定一个长度为 $n$ 的数列 $a$，对于其中每个长度为 $k$ 的子区间，请你求出这个这个子区间构成的数列的所有后缀最大值的位置个数。

一个下标 $i$ 是是数列 $b$ 的后缀最大值下标当且仅当：对于所有的 $i < j \leq |b|$，都有 $b_i > b_j$，其中 $|b|$ 表示 $b$ 的元素个数。

## 输入格式

第一行是两个整数，依次表示操作次数 $n$ 和子区间长度 $k$。  
第二行有 $n$ 个整数，第 $i$ 个整数表示 $a_i$。
## 输出格式

共输出 $n - k + 1$ 行每行一个整数，按左端点从小到大的顺序依次输出每个子区间构成的数列的后缀最大值位置个数。
## 样例

### 样例输入 #1
```
5 3
2 1 3 5 4
```
### 样例输出 #1
```
1
1
2
```
## 提示

### 样例 1 解释

第一个子数列：$2, 1, 3$。其中 $3$ 是后缀最大值。  
第二个子数列：$1, 3, 5$，其中 $5$ 是后缀最大值。  
第三个子数列：$3,5,4$，其中 $5$ 和 $4$ 是后缀最大值。

### 数据规模与约定

对于全部的测试点，保证 $1 \leq k \leq n \leq 10^6$，$1 \leq x_i \lt 2^{64}$。


---

---
title: "[NOIP 2004 提高组] 合并果子"
layout: "post"
diff: 普及/提高-
pid: P1090
tag: ['贪心', '2004', '堆', 'NOIP 提高组', '优先队列']
---
# [NOIP 2004 提高组] 合并果子
## 题目描述

在一个果园里，多多已经将所有的果子打了下来，而且按果子的不同种类分成了不同的堆。多多决定把所有的果子合成一堆。

每一次合并，多多可以把两堆果子合并到一起，消耗的体力等于两堆果子的重量之和。可以看出，所有的果子经过 $n-1$ 次合并之后， 就只剩下一堆了。多多在合并果子时总共消耗的体力等于每次合并所耗体力之和。

因为还要花大力气把这些果子搬回家，所以多多在合并果子时要尽可能地节省体力。假定每个果子重量都为 $1$ ，并且已知果子的种类 数和每种果子的数目，你的任务是设计出合并的次序方案，使多多耗费的体力最少，并输出这个最小的体力耗费值。

例如有 $3$ 种果子，数目依次为 $1$ ， $2$ ， $9$ 。可以先将 $1$ 、 $2$ 堆合并，新堆数目为 $3$ ，耗费体力为 $3$ 。接着，将新堆与原先的第三堆合并，又得到新的堆，数目为 $12$ ，耗费体力为 $12$ 。所以多多总共耗费体力 $=3+12=15$ 。可以证明 $15$ 为最小的体力耗费值。
## 输入格式

共两行。  
第一行是一个整数 $n(1\leq n\leq 10000)$ ，表示果子的种类数。  

第二行包含 $n$ 个整数，用空格分隔，第 $i$ 个整数 $a_i(1\leq a_i\leq 20000)$ 是第 $i$ 种果子的数目。


## 输出格式

一个整数，也就是最小的体力耗费值。输入数据保证这个值小于 $2^{31}$ 。
## 样例

### 样例输入 #1
```
3 
1 2 9 

```
### 样例输出 #1
```
15

```
## 提示

对于 $30\%$ 的数据，保证有 $n \le 1000$：

对于 $50\%$ 的数据，保证有 $n \le 5000$；

对于全部的数据，保证有 $n \le 10000$。



---

---
title: "[NOIP 2004 提高组] 合唱队形"
layout: "post"
diff: 普及/提高-
pid: P1091
tag: ['动态规划 DP', '2004', '单调队列', 'NOIP 提高组', '线性 DP']
---
# [NOIP 2004 提高组] 合唱队形
## 题目描述

$n$ 位同学站成一排，音乐老师要请其中的 $n-k$ 位同学出列，使得剩下的 $k$ 位同学排成合唱队形。

合唱队形是指这样的一种队形：设 $k$ 位同学从左到右依次编号为 $1,2,$ … $,k$，他们的身高分别为 $t_1,t_2,$ … $,t_k$，则他们的身高满足 $t_1< \cdots <t_i>t_{i+1}>$ … $>t_k(1\le i\le k)$。

你的任务是，已知所有 $n$ 位同学的身高，计算最少需要几位同学出列，可以使得剩下的同学排成合唱队形。
## 输入格式

共二行。

第一行是一个整数 $n$（$2\le n\le100$），表示同学的总数。

第二行有 $n$ 个整数，用空格分隔，第 $i$ 个整数 $t_i$（$130\le t_i\le230$）是第 $i$ 位同学的身高（厘米）。
## 输出格式

一个整数，最少需要几位同学出列。

## 样例

### 样例输入 #1
```
8
186 186 150 200 160 130 197 220

```
### 样例输出 #1
```
4

```
## 提示

对于 $50\%$ 的数据，保证有 $n \le 20$。

对于全部的数据，保证有 $n \le 100$。



---

---
title: "[APC001] C - Not APC"
layout: "post"
diff: 普及/提高-
pid: P11138
tag: ['Special Judge', 'O2优化', '队列']
---
# [APC001] C - Not APC
## 题目背景

这题并没有什么有趣的题目背景，祝您愉快。
## 题目描述

小 A 有一个**仅由 `A`、`P`、`C` 构成**的字符串 $S$。

小 A 需要**尽可能地**不断在这个字符串中消除形如 `APC` 这样的**子序列**，直到无法消除。

最后，小 A 需要输出消除后的字符串。如果字符串可以被消除成空串，则输出 `Perfect`。

然而小 A 不会这个题，所以来找你帮忙。
## 输入格式

第一行一个数 $T$ 表示数据组数。

接下来 $T$ 行每行一个字符串 $S$.
## 输出格式

**本题使用 Special Judge。**

请输出最短的答案字符串，并给出一种删除的方案。

对于每组数据，第一行输出一个最短的答案字符串。如果可能的最短答案字符串或生成最短答案字符串的方案有多种，请输出任意一个。

接下来一行输出一个整数 $q$，表示你的删除次数。

接下来 $q$ 行每行三个整数，分别表示你在一次操作中删除的字符 `A`、`P`、`C` **在原字符串中**的位置，**下标从 $1$ 开始**。
## 样例

### 样例输入 #1
```
5
PAAAAPPPCA
CAPPCPCAPAPA
PPAAAACCAAAAAAAAC
CAPPCAAPA
APPAACPPAPPPAPAAAA
```
### 样例输出 #1
```
PAAAPPA
1
5 6 9
CPPCAPAPA
1
2 4 5
PPAAAACCAAAAAAAAC
0
CPAAPA
1
2 3 5
PAAPPAPPPAPAAAA
1
1 2 6
```
### 样例输入 #2
```
1
APC

```
### 样例输出 #2
```
Perfect
1
1 2 3
```
### 样例输入 #3
```
10
PPCPAPAAACPAPACPPCPC
APPAPPAPPCPAPPCCCPPA
APPCCPPAPPAACCPPPPPP
PACPPCAPCPPCPPPAAAAC
PPPCPPCCPACAAACCCCAC
ACAAPCPAPAAAAPPACPPC
ACACPPCCPPAACPAAAAAC
APPCPCCCAPCACPAACACC
AACPCAPACPPPCAAPCCPC
PPACPPPCCAPAAAPCPAPA

```
### 样例输出 #3
```
PPCPAAPP
4
5 6 10
7 11 15
8 13 18
9 16 20
PPPPPPPA
4
1 2 10
4 5 15
7 8 16
12 13 17
PCPPPAACPPPPPP
2
1 2 4
8 9 13
PCPPPCPPPAAAAC
2
2 4 6
7 8 9
PPPCPPCCPACAAACCCCAC
0
CAAAAAPPAPP
3
1 5 6
3 7 17
4 9 20
CCPPACAAAAA
3
1 5 7
3 6 8
11 14 20
PPCCCCAAACC
3
1 2 4
9 10 11
12 14 17
CP
6
1 4 5
2 7 9
6 10 13
8 11 17
14 16 18
15 19 20
PPCPPCAAAPPAPA
2
3 5 8
10 11 16

```
## 提示

**样例解释 #1：**  
对于第一组数据，字符串为 `PAAAAPPPCA`，下标为 $\{5,6,9\}$ 的字符串被删除，最终得到 `PAAAPPA`。

对于第二组数据，字符串为 `CAPPCPCAPAPA`，下标为 $\{2,4,5\}$ 的字符被消除，得到 `CPPCAPAPA`。

**样例解释 #2：**  
唯一的一组数据中，字符串为 `APC`，显然能被全部消除，方案也显然。

$1\leq T\leq 10$，$1\leq \sum |S|\leq 3\times 10^6$。


---

---
title: "01迷宫"
layout: "post"
diff: 普及/提高-
pid: P1141
tag: ['搜索', '广度优先搜索 BFS', '队列']
---
# 01迷宫
## 题目描述

有一个仅由数字 $0$ 与 $1$ 组成的 $n \times n$ 格迷宫。若你位于一格 $0$ 上，那么你可以移动到相邻 $4$ 格中的某一格 $1$ 上，同样若你位于一格 $1$ 上，那么你可以移动到相邻 $4$ 格中的某一格 $0$ 上。

你的任务是：对于给定的迷宫，询问从某一格开始能移动到多少个格子（包含自身）。
## 输入格式

第一行为两个正整数 $n,m$。

下面 $n$ 行，每行 $n$ 个字符，字符只可能是 $0$ 或者 $1$，字符之间没有空格。

接下来 $m$ 行，每行两个用空格分隔的正整数 $i,j$，对应了迷宫中第 $i$ 行第 $j$ 列的一个格子，询问从这一格开始能移动到多少格。
## 输出格式

$m$ 行，对于每个询问输出相应答案。

## 样例

### 样例输入 #1
```
2 2
01
10
1 1
2 2

```
### 样例输出 #1
```
4
4

```
## 提示

对于样例，所有格子互相可达。

- 对于 $20\%$ 的数据，$n \leq 10$；
- 对于 $40\%$ 的数据，$n \leq 50$；
- 对于 $50\%$ 的数据，$m \leq 5$；
- 对于 $60\%$ 的数据，$n,m \leq 100$；
- 对于 $100\%$ 的数据，$1\le n \leq 1000$，$1\le m \leq 100000$。


---

---
title: "[GESP202503 六级] 环线"
layout: "post"
diff: 普及/提高-
pid: P11963
tag: ['动态规划 DP', '单调队列', '2025', 'GESP']
---
# [GESP202503 六级] 环线
## 题目描述

小 A 喜欢坐地铁。地铁环线有 $n$ 个车站，依次以 $1,2,\cdots,n$ 标号。车站 $i\ (1\leq i<n)$ 的下一个车站是车站 $i+1$。特殊地，车站 $n$ 的下一个车站是车站 $1$。

小 A 会从某个车站出发，乘坐地铁环线到某个车站结束行程，这意味着小 A 至少会经过一个车站。小 A 不会经过一个车站多次。当小 A 乘坐地铁环线经过车站 $i$ 时，小 A 会获得 $a_i$ 点快乐值。请你安排小 A 的行程，选择出发车站与结束车站，使得获得的快乐值总和最大。
## 输入格式

第一行，一个正整数 $n$，表示车站的数量。

第二行，$n$ 个整数 $a_i$，分别表示经过每个车站时获得的快乐值。
## 输出格式

一行，一个整数，表示小 A 能获得的最大快乐值。
## 样例

### 样例输入 #1
```
4
-1 2 3 0
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
5
-3 4 -5 1 3
```
### 样例输出 #2
```
5
```
## 提示

对于 $20\%$ 的测试点，保证 $1\leq n\leq 200$。

对于 $40\%$ 的测试点，保证 $1\leq n\leq 2000$。

对于所有测试点，保证 $1\leq n\leq 2\times 10^5$，$-10^9\leq a_i\leq 10^9$。


---

---
title: "删数问题"
layout: "post"
diff: 普及/提高-
pid: P1323
tag: ['模拟', '字符串', '贪心', '优先队列', '队列']
---
# 删数问题
## 题目描述

一个集合有如下元素：$1$ 是集合元素；若 $P$ 是集合的元素，则 $2\times P+1$，$4\times P+5$ 也是集合的元素。

取出此集合中最小的 $k$ 个元素，按从小到大的顺序组合成一个多位数，现要求从中删除 $m$ 个数位上的数字，使得剩下的数字最大，编程输出删除前和删除后的多位数字。

注：不存在所有数被删除的情况。
## 输入格式

只有一行两个整数，分别代表 $k$ 和 $m$。
## 输出格式

输出为两行两个整数，第一行为删除前的数字，第二行为删除后的数字。

## 样例

### 样例输入 #1
```
5  4
```
### 样例输出 #1
```
137915
95
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $1\le k,m\le300$。
- 对于 $100\%$ 的数据，保证 $1\le k,m\le3\times10^4$。


---

---
title: "[COCI 2012/2013 #4] RAZLIKA"
layout: "post"
diff: 普及/提高-
pid: P13416
tag: ['数学', '贪心', '2012', '单调队列', '排序', '差分', 'COCI（克罗地亚）']
---
# [COCI 2012/2013 #4] RAZLIKA
## 题目描述

Mirko's newest math homework assignment is a very difficult one! Given a sequence, $V$, of $N$ integers, remove exactly $K$ of them from the sequence. Let $M$ be the largest difference of any two remaining numbers in the sequence, and $m$ the smallest such difference. Select the $K$ integers to be removed from $V$ in such a way that the sum $M + m$ is the smallest possible. Mirko isn't very good at math, so he has asked you to help him!

## 输入格式

The first line of input contains two positive integers, $N$ ($3 \leq N \leq 1\,000\,000$) and $K$ ($1 \leq K \leq N - 2$).

The second line of input contains $N$ space-separated positive integers – the sequence $V$ ($-5\,000\,000 \leq V_i \leq 5\,000\,000$).
## 输出格式

The first and only line of output must contain the smallest possible sum $M + m$.
## 样例

### 样例输入 #1
```
5 2
-3 -2 3 8 6
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
6 2
-5 8 10 1 13 -1
```
### 样例输出 #2
```
13
```
### 样例输入 #3
```
6 3
10 2 8 17 2 17
```
### 样例输出 #3
```
6
```


---

---
title: "[KOI 2025 #1] 稻草人"
layout: "post"
diff: 普及/提高-
pid: P13512
tag: ['堆', '2025', '优先队列', 'KOI（韩国）']
---
# [KOI 2025 #1] 稻草人
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

一支带有力量 $P$ 的箭从数轴上的位置 0 向右方发射。在每个整数位置 $i$ ($1 \le i \le N$)，最多可以设置一个防御力为 $A_i$ 的稻草人。当箭撞到稻草人时，如果箭的力量小于或等于稻草人的防御力，箭会立即停止。反之，如果箭的力量大于防御力，箭的力量会减去 $A_i$ 并继续前进。

对于整数 $i$，我们将 $f(i)$ 的值定义为“为了使箭在位置 $i$ 或其左侧停止所需要的**稻草人的最小数量**”。如果无法使箭停止，则值为 $-1$。

例如，假设 $N=5, P=10$ 并且 $A_1=3, A_2=6, A_3=1, A_4=1, A_5=10$。所有 $f(i)$ 的值和安装的稻草人的位置如下表所示。

| $i$ | $f(i)$ 的值 | 安装的稻草人的位置 |
| :--: | :--: | :--: |
| $i=1$ | $-1$ | 不可能 |
| $i=2$ | $-1$ | 不可能 |
| $i=3$ | $3$ | $[1, 2, 3]$ |
| $i=4$ | $3$ | 可选择 $[1, 2, 3]$ 或 $[1, 2, 4]$ 之一 |
| $i=5$ | $1$ | $[5]$ |

请编写一个程序，求出对于所有 $1 \le i \le N$ 的 $i$ 的 $f(i)$ 值。
## 输入格式

第一行给定整数 $N$ 和箭的力量 $P$，以空格分隔。

第二行给定 $N$ 个整数 $A_1, A_2, \cdots, A_N$，以空格分隔。
## 输出格式

在第一行输出 $f(1), f(2), \cdots, f(N)$ 的值，以空格分隔。
## 样例

### 样例输入 #1
```
5 10
3 6 1 1 10
```
### 样例输出 #1
```
-1 -1 3 3 1
```
### 样例输入 #2
```
3 10
20 20 20
```
### 样例输出 #2
```
1 1 1
```
### 样例输入 #3
```
1 5
3
```
### 样例输出 #3
```
-1
```
## 提示

### 限制条件

*   给定的所有数都是整数。
*   $1 \le N \le 500,000$
*   $1 \le P \le 10^9$
*   对于每个 $1 \le i \le N$ 的 $i$，都有 $1 \le A_i \le 10^9$。

### 子任务

1.  (4 分) $N \le 8$
2.  (8 分) $N \le 5000$
3.  (8 分) 对于所有 $1 \le i \le N$ 的 $i$，$A_i = 1$。
4.  (20 分) 对于所有 $1 \le i \le N$ 的 $i$，$A_i = 2$ 或 $A_i = 3$。
5.  (40 分) 对于所有 $1 \le i \le N$ 的 $i$，$A_i \le 50$。
6.  (40 分) 对于所有 $1 \le i < N$ 的 $i$，$A_i \le A_{i+1}$。
7.  (30 分) 无附加限制条件。


---

---
title: "求m区间内的最小值"
layout: "post"
diff: 普及/提高-
pid: P1440
tag: ['动态规划 DP', '单调队列', '队列']
---
# 求m区间内的最小值
## 题目描述

一个含有 $n$ 项的数列，求出每一项前的 $m$ 个数到它这个区间内的最小值。若前面的数不足 $m$ 项则从第 $1$ 个数开始，若前面没有数则输出 $0$。
## 输入格式

第一行两个整数，分别表示 $n$，$m$。

第二行，$n$ 个正整数，为所给定的数列 $a_i$。
## 输出格式

$n$ 行，每行一个整数，第 $i$ 个数为序列中 $a_i$ 之前 $m$ 个数的最小值。
## 样例

### 样例输入 #1
```
6 2
7 8 1 4 3 2

```
### 样例输出 #1
```
0
7
7
1
1
3 

```
## 提示

对于 $100\%$ 的数据，保证 $1\le m\le n\le2\times10^6$，$1\le a_i\le3\times10^7$。


---

---
title: "马的遍历"
layout: "post"
diff: 普及/提高-
pid: P1443
tag: ['搜索', 'Special Judge', '广度优先搜索 BFS', '队列']
---
# 马的遍历
## 题目描述

有一个 $n \times m$ 的棋盘，在某个点 $(x, y)$ 上有一个马，要求你计算出马到达棋盘上任意一个点最少要走几步。

## 输入格式

输入只有一行四个整数，分别为 $n, m, x, y$。

## 输出格式

一个 $n \times m$ 的矩阵，代表马到达某个点最少要走几步（不能到达则输出 $-1$）。

## 样例

### 样例输入 #1
```
3 3 1 1

```
### 样例输出 #1
```
0    3    2    
3    -1   1    
2    1    4    
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $1 \leq x \leq n \leq 400$，$1 \leq y \leq m \leq 400$。


---

---
title: "yyy loves Easter_Egg I"
layout: "post"
diff: 普及/提高-
pid: P1580
tag: ['模拟', '字符串', '洛谷原创', '队列']
---
# yyy loves Easter_Egg I
## 题目背景

Soha 的出题效率着实让人大吃一惊。OI，数学，化学的题目都出好了，物理的题还没有一道。于是，Huntfire，absi2011，redbag 对 soha 进行轮番炸，准备炸到 soha 出来，不料，人群中冲出了个 kkksc03……
## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1456.png)

![](https://cdn.luogu.com.cn/upload/pic/1455.png)

yyy loves OI（Huntfire），yyy loves Maths（redbag），yyy loves Chemistry（absi2011）对 yyy loves Physics（soha）进行轮番炸，轰炸按照顺序进行，顺序为 Huntfire，redbag，absi2011。

现在这一题中，我们不考虑太复杂的队形形式。我们认为只要这一句内含有且恰好含有一次@，@的人和上一句话一样就算为队形。

比如以下也视为队形：

- `yyy loves OI : @yyy loves Microelectronic`
- `yyy loves Maths : @yyy loves Microelectronic 我佩服soha的出题效率`
- `yyy loves OI : @yyy loves Microelectronic +1`
- `yyy loves Chemistry : +1 @yyy loves Microelectronic`

若 @ 的人与第一个人不同，就算队形被打破。若这个人在队形被打破之前出来发言了，或者就是他打破队形了，就算（油）炸成功了。

若（油）炸成功，输出 `Successful @某某某 attempt`，若队形被破坏先输出 `Unsuccessful @某某某 attempt`，再输出队形第一次被破坏的行数与第一次破坏队形的人的 $\text{id}$。

如果队形一直没被打破，就先输出 `Unsuccessful @某某某 attempt`，再输出队形的长度，最后输出 `Good Queue Shape`。

~~p.s.yyy loves Microelectronic 是 kkksc03~~


## 输入格式

$N$ 行，为轰炸开始后的一段消息记录，每行一条消息。消息格式：「消息发送者+`:`+消息内容」，每行消息长度不超过 $1000$。（中文用拼音代替）


## 输出格式

若（油）炸成功，输出 `Successful @某某某 attempt`，若队形被破坏第一行输出 `Unsuccessful @某某某 attempt`，接下来一行输出队形第一次被破坏的行数，第三行输出第一次破坏队形的人的 $\text{id}$。
如果队形一直没被打破，就先输出 `Unsuccessful @某某某 attempt`，再输出队形的长度，最后输出 `Good Queue Shape`。
## 样例

### 样例输入 #1
```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Microelectronic : ni men wu liao me 
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv


```
### 样例输出 #1
```
Unsuccessful @yyy loves Physics attempt
4
yyy loves Microelectronic

```
### 样例输入 #2
```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Physics : ni men gou le 


```
### 样例输出 #2
```
Successful @yyy loves Physics attempt

```
## 提示

**@yyy loves Physics 我佩服你的出题效率**

此题仅吐槽 soha，纪念出题者的队形，此队形长达 $91$ 行。

对于 $100\%$ 的数据,每行消息长度 $\le$ $10^3$。 

- 保证行数不超过 $5\times 10^4$；
- 保证输入文件大小不超过 $4\text{MB}$；
- 保证第一个说话的一定在 @ 某人；
- 保证大家的名字都是 $\text{yyy loves ***}$ 的格式；
- 保证每个人说的话中没有 `:`；
- 保证第一个说话的一定艾特了一个人且只 @ 了一个人；
- 保证第一个说话的一定不会艾特自己；
- 保证文件结束一定有一行空行，方便你判定文件结束；
- 并不保证后面说话的艾特了几个人 然而艾特人数不为一个人视为破坏队形；
- 并不保证后面说话是否会反复艾特同一个人；
- 并不保证被炸的人一定破坏队形；
- 并不保证这一题是或不是压轴题；
- 并不保证这一套比赛存在压轴题；
- 并不保证下一套比赛和这一套比赛一样水；
- 并不保证群里除了这 $4$ 个人和 kkksc03 以外没有别人了；
- 并不保证你没 AC 这题的情况下吐槽 soha 不会出事儿；
- AC 了可以吐槽 soha 一句，soha 不会介意。


---

---
title: "邮递员送信"
layout: "post"
diff: 普及/提高-
pid: P1629
tag: ['图论', '优先队列', '最短路', '队列']
---
# 邮递员送信
## 题目描述

有一个邮递员要送东西，邮局在节点 $1$。他总共要送 $n-1$ 样东西，其目的地分别是节点 $2$ 到节点 $n$。由于这个城市的交通比较繁忙，因此所有的道路都是单行的，共有 $m$ 条道路。这个邮递员每次只能带一样东西，并且**运送每件物品过后必须返回邮局**。求送完这 $n-1$ 样东西并且**最终回到邮局**最少需要的时间。
## 输入格式

第一行包括两个整数，$n$ 和 $m$，表示城市的节点数量和道路数量。

第二行到第 $(m+1)$ 行，每行三个整数，$u,v,w$，表示从 $u$ 到 $v$ 有一条通过时间为 $w$ 的道路。
## 输出格式

输出仅一行，包含一个整数，为最少需要的时间。
## 样例

### 样例输入 #1
```
5 10
2 3 5
1 5 5
3 5 6
1 2 8
1 3 8
5 3 4
4 1 8
4 5 3
3 5 6
5 4 2
```
### 样例输出 #1
```
83
```
## 提示

对于 $30\%$ 的数据，$1 \leq n \leq 200$。

对于 $100\%$ 的数据，$1 \leq n \leq 10^3$，$1 \leq m \leq 10^5$，$1\leq u,v \leq n$，$1 \leq w \leq 10^4$，输入保证任意两点都能互相到达。


---

---
title: "逛画展"
layout: "post"
diff: 普及/提高-
pid: P1638
tag: ['二分', 'USACO', '单调队列', '队列', '双指针 two-pointer']
---
# 逛画展
## 题目描述


博览馆正在展出由世上最佳的 $m$ 位画家所画的图画。

游客在购买门票时必须说明两个数字，$a$ 和 $b$，代表他要看展览中的第 $a$ 幅至第 $b$ 幅画（包含 $a,b$）之间的所有图画，而门票的价钱就是一张图画一元。

Sept 希望入场后可以看到所有名师的图画。当然，他想最小化购买门票的价格。

请求出他购买门票时应选择的 $a,b$，数据保证一定有解。

若存在多组解，**输出 $a$ 最小的那组**。
## 输入格式

第一行两个整数 $n,m$，分别表示博览馆内的图画总数及这些图画是由多少位名师的画所绘画的。

第二行包含 $n$ 个整数 $a_i$，代表画第 $i$ 幅画的名师的编号。

## 输出格式

一行两个整数 $a,b$。
## 样例

### 样例输入 #1
```
12 5
2 5 3 1 3 2 4 1 1 5 4 3

```
### 样例输出 #1
```
2 7
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，有 $n\le200$，$m\le20$。
- 对于 $60\%$ 的数据，有 $n\le10^5$，$m\le10^3$。
- 对于 $100\%$ 的数据，有 $1\leq n\le10^6$，$1 \leq a_i \leq m\le2\times10^3$。


---

---
title: "切蛋糕"
layout: "post"
diff: 普及/提高-
pid: P1714
tag: ['单调队列', '前缀和', '队列', 'ST 表']
---
# 切蛋糕
## 题目描述

今天是小 Z 的生日，同学们为他带来了一块蛋糕。这块蛋糕是一个长方体，被用不同色彩分成了 $n$ 个相同的小块，每小块都有对应的幸运值。

小 Z 作为寿星，自然希望吃到的蛋糕的幸运值总和最大，但小 Z 最多又只能吃 $m(m\le n)$ 小块的蛋糕。

请你帮他从这 $n$ 小块中找出**连续**的 $k(1 \le k\le m)$ 块蛋糕，使得其上的总幸运值最大。

**形式化地**，在数列 $\{p_n\}$ 中，找出一个子段 $[l,r](r-l+1\le m)$，最大化 $\sum\limits_{i=l}^rp_i$。
## 输入格式

第一行两个整数 $n,m$。分别代表共有 $n$ 小块蛋糕，小 Z 最多只能吃 $m$ 小块。

第二行 $n$ 个整数，第 $i$ 个整数 $p_i$ 代表第 $i$ 小块蛋糕的幸运值。
## 输出格式

仅一行一个整数，即小 Z 能够得到的最大幸运值。
## 样例

### 样例输入 #1
```
5 2
1 2 3 4 5
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
6 3
1 -2 3 -4 5 -6
```
### 样例输出 #2
```
5
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，有 $1\le n\le100$。
- 对于 $100\%$ 的数据，有 $1\le n\le5\times 10^5$，$|p_i|≤500$。

保证答案的绝对值在 $[0,2^{31}-1]$ 之内。


---

---
title: "采购特价商品"
layout: "post"
diff: 普及/提高-
pid: P1744
tag: ['图论', '最短路', '队列']
---
# 采购特价商品
## 题目背景

《爱与愁的故事第三弹·shopping》第一章。
## 题目描述

中山路店山店海，成了购物狂爱与愁大神的“不归之路”。中山路上有 $n$（$n \leq 100$）家店，每家店的坐标均在 $-10000$ 至 $10000$ 之间。其中的 $m$ 家店之间有通路。若有通路，则表示可以从一家店走到另一家店，通路的距离为两点间的直线距离。现在爱与愁大神要找出从一家店到另一家店之间的最短距离。你能帮爱与愁大神算出吗？
## 输入格式

共 $n+m+3$ 行：

第一行：整数 $n$。 

接下来 $n$ 行：每行两个整数 $x$ 和 $y$，描述了一家店的坐标。 

接下来一行：整数 $m$。 

接下来 $m$ 行：每行描述一条通路，由两个整数 $i$ 和 $j$ 组成，表示第 $i$ 家店和第 $j$ 家店之间有通路。

接下来一行：两个整数 $s$ 和 $t$，分别表示原点和目标店。 
## 输出格式

仅一行：一个实数（保留两位小数），表示从 $s$ 到 $t$ 的最短路径长度。
## 样例

### 样例输入 #1
```
5

0 0

2 0

2 2

0 2

3 1

5

1 2

1 3

1 4

2 5

3 5

1 5
```
### 样例输出 #1
```
3.41
```
## 提示

对于 $100 \%$ 的数据：$2 \le n \leq 100$，$1 \le i, j, s, t \le n$，$1 \le m \leq 1000$。 


---

---
title: "[USACO3.2] 香甜的黄油 Sweet Butter"
layout: "post"
diff: 普及/提高-
pid: P1828
tag: ['图论', 'USACO', '队列']
---
# [USACO3.2] 香甜的黄油 Sweet Butter
## 题目描述

Farmer John 发现了做出全威斯康辛州最甜的黄油的方法：糖。

把糖放在一片牧场上，他知道 $N$ 只奶牛会过来舔它，这样就能做出能卖好价钱的超甜黄油。当然，他将付出额外的费用在奶牛上。

Farmer John 很狡猾。像以前的 Pavlov，他知道他可以训练这些奶牛，让它们在听到铃声时去一个特定的牧场。他打算将糖放在那里然后下午发出铃声，以至他可以在晚上挤奶。

Farmer John 知道每只奶牛都在各自喜欢的牧场（一个牧场不一定只有一头牛）。给出各头牛在的牧场和牧场间的路线，找出使所有牛到达的路程和最短的牧场（他将把糖放在那）。
## 输入格式

第一行包含三个整数 $N,P,C$，分别表示奶牛数、牧场数和牧场间道路数。

第二行到第 $N+1$ 行，每行一个整数，其中第 $i$ 行的整数表示第 $i-1$ 头奶牛所在的牧场号。

第 $N+2$ 行到第 $N+C+1$ 行，每行包含三个整数 $A,B,D$，表示牧场号为 $A$ 和 $B$ 的两个牧场之间有一条长度为 $D$ 的双向道路相连。
## 输出格式

输出一行一个整数，表示奶牛必须行走的最小的距离和。
## 样例

### 样例输入 #1
```
3 4 5
2
3
4
1 2 1
1 3 5
2 3 7
2 4 3
3 4 5
```
### 样例输出 #1
```
8
```
## 提示

**数据范围**

对于所有数据，$1 \le N \le 500$，$2 \le P \le 800$，$1 \le A,B \le P$，$1 \le C \le 1450$，$1 \le D \le 255$。

---

**样例解释**

作图如下：

```cpp
          P2  
P1 @--1--@ C1
         |
         | 
       5  7  3
         |   
         |     C3
       C2 @--5--@
          P3    P4
```

把糖放在4号牧场最优。


---

---
title: "滑动窗口 /【模板】单调队列"
layout: "post"
diff: 普及/提高-
pid: P1886
tag: ['模拟', '线段树', '单调队列', '队列']
---
# 滑动窗口 /【模板】单调队列
## 题目描述

有一个长为 $n$ 的序列 $a$，以及一个大小为 $k$ 的窗口。现在这个从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最大值和最小值。

例如，对于序列 $[1,3,-1,-3,5,3,6,7]$ 以及 $k = 3$，有如下过程：

$$\def\arraystretch{1.2}
\begin{array}{|c|c|c|}\hline
\textsf{窗口位置} & \textsf{最小值} & \textsf{最大值} \\ \hline
\verb![1   3  -1] -3   5   3   6   7 ! & -1 & 3 \\ \hline
\verb! 1  [3  -1  -3]  5   3   6   7 ! & -3 & 3 \\ \hline
\verb! 1   3 [-1  -3   5]  3   6   7 ! & -3 & 5 \\ \hline
\verb! 1   3  -1 [-3   5   3]  6   7 ! & -3 & 5 \\ \hline
\verb! 1   3  -1  -3  [5   3   6]  7 ! & 3 & 6 \\ \hline
\verb! 1   3  -1  -3   5  [3   6   7]! & 3 & 7 \\ \hline
\end{array}
$$
## 输入格式

输入一共有两行，第一行有两个正整数 $n,k$。
第二行 $n$ 个整数，表示序列 $a$

## 输出格式

输出共两行，第一行为每次窗口滑动的最小值   
第二行为每次窗口滑动的最大值 

## 样例

### 样例输入 #1
```
8 3
1 3 -1 -3 5 3 6 7
```
### 样例输出 #1
```
-1 -3 -3 -3 3 3
3 3 5 5 6 7
```
## 提示

【数据范围】    
对于 $50\%$ 的数据，$1 \le n \le 10^5$；  
对于 $100\%$ 的数据，$1\le k \le n \le 10^6$，$a_i \in [-2^{31},2^{31})$。



---

---
title: "扫描"
layout: "post"
diff: 普及/提高-
pid: P2032
tag: ['单调队列']
---
# 扫描
## 题目描述

有一个 $1 \times n$ 的矩阵，有 $n$ 个整数。

现在给你一个可以盖住连续 $k$ 个数的木板。

一开始木板盖住了矩阵的第 $1 \sim k$ 个数，每次将木板向右移动一个单位，直到右端与第 $n$ 个数重合。

每次移动前输出被覆盖住的数字中最大的数是多少。
## 输入格式

第一行两个整数 $n,k$，表示共有 $n$ 个数，木板可以盖住 $k$ 个数。

第二行 $n$ 个整数，表示矩阵中的元素。  
## 输出格式

共 $n - k + 1$ 行，每行一个整数。

第 $i$ 行表示第 $i \sim i + k - 1$ 个数中最大值是多少。  
## 样例

### 样例输入 #1
```
5 3
1 5 3 4 2

```
### 样例输出 #1
```
5
5
4

```
## 提示

对于 $20\%$ 的数据，$1 \leq k \leq n \leq 10^3$。

对于 $50\%$ 的数据，$1 \leq k \leq n \leq 10^4$。

对于 $100\%$ 的数据，$1 \leq k \leq n \leq 2 \times 10^6$，矩阵中的元素大小不超过 $10^4$ 并且均为正整数。 


---

---
title: "最小函数值"
layout: "post"
diff: 普及/提高-
pid: P2085
tag: ['数学', '堆', '排序', '优先队列']
---
# 最小函数值
## 题目描述

有 $n$ 个函数，分别为 $F_1,F_2,\dots,F_n$。定义 $F_i(x)=A_ix^2+B_ix+C_i(x\in\mathbb N*)$。给定这些 $A_i$、$B_i$ 和 $C_i$，请求出所有函数的所有函数值中最小的 $m$ 个（如有重复的要输出多个）。
## 输入格式

第一行输入两个正整数 $n$ 和 $m$。  

以下 $n$ 行每行三个正整数，其中第 $i$ 行的三个数分别为 $A_i$、$B_i$ 和 $C_i$。
## 输出格式

输出将这 $n$ 个函数所有可以生成的函数值排序后的前 $m$ 个元素。这 $m$ 个数应该输出到一行，用空格隔开。
## 样例

### 样例输入 #1
```
3 10
4 5 3
3 4 5
1 7 1

```
### 样例输出 #1
```
9 12 12 19 25 29 31 44 45 54
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n,m\le10000$，$1 \leq A_i\le10,B_i\le100,C_i\le10^4$。


---

---
title: "最后的迷宫"
layout: "post"
diff: 普及/提高-
pid: P2199
tag: ['搜索', '枚举', '广度优先搜索 BFS', '队列']
---
# 最后的迷宫
## 题目背景

哈利•波特作为三强争霸赛的第四名选手，历尽艰险闯到了最后一关——迷宫。

现在，迷宫里只剩下哈利和塞德里克了，哈利只有在塞德里克前面拿到奖杯，才能赢得比赛。哈利只要能看到奖杯，就可以用飞来咒拿到它，所以，现在的问题是哈利如何能尽早地看到奖杯。

## 题目描述

哈利的视力非常好，他能从迷宫的一端沿直线看到迷宫的另一端（但他只能看八个方向——东北，东，东南，南，西南……），而且他跑得非常快，跑一步（向上、下、左、右移动一格）只需要 $1\text{s}$。但迷宫是不透光的，而且，要烧掉迷宫的墙也不容易，所以哈利决定绕到一个能够看到奖杯的地方。现在，哈利希望你能帮他确定最短需要多长时间才能拿到奖杯。

## 输入格式

第一行为 $2$ 个数 $N,M$ 表示迷宫的规模（$N$ 为高，$M$ 为宽）

接下来是 $N \times M$ 的迷宫，$\texttt{O}$ 表示空地，$\texttt{X}$ 表示墙。

最后是多对数据，分别是奖杯坐标及哈利的坐标（显然不可能在墙上），每对占一行，$0$ 为结束标志。

## 输出格式

根据每对数据，计算哈利拿到奖杯的最短时间，每对一行。如果魔法部有意难为选手，用墙将奖杯包围了起来，输出 $\texttt{Poor Harry}$。

## 样例

### 样例输入 #1
```
3 4
OXXO
XXOO
XOOO
3 2 2 4
3 3 1 1
0 0 0 0

```
### 样例输出 #1
```
1
Poor Harry

```
## 提示

对于 $30\%$ 的数据，有 $N\times M\le100$；

对于 $60\%$ 的数据，有 $N\times M\le1600$；

对于 $100\%$ 的数据，有 $N\times M\le16384$。

询问数据对数不超过 $512$。



---

---
title: "质量检测"
layout: "post"
diff: 普及/提高-
pid: P2251
tag: ['数学', '单调队列', 'ST 表']
---
# 质量检测
## 题目描述

为了检测生产流水线上总共 $N$ 件产品的质量，我们首先给每一件产品打一个分数 $A$ 表示其品质，然后统计前 $M$ 件产品中质量最差的产品的分值 $Q[m] = min\{A_1, A_2, ... A_m\}$，以及第 2 至第 $M + 1$ 件的 $Q[m + 1], Q[m + 2] $... 最后统计第 $N - M + 1$ 至第 $N$ 件的 $Q[n]$。根据 $Q$ 再做进一步评估。

请你尽快求出 $Q$ 序列。

## 输入格式

输入共两行。

第一行共两个数 $N$、$M$，由空格隔开。含义如前述。

第二行共 $N$ 个数，表示 $N$ 件产品的质量。

## 输出格式

输出共 $N - M + 1$ 行。

第 1 至 $N - M + 1$ 行每行一个数，第 $i$ 行的数 $Q[i + M - 1]$。含义如前述。

## 样例

### 样例输入 #1
```
10 4
16 5 6 9 5 13 14 20 8 12

```
### 样例输出 #1
```
5
5
5
5
5
8
8

```
## 提示

[数据范围]

30%的数据，$N \le 1000$

100%的数据，$N \le 100000$

100%的数据，$M \le N, A \le 1 000 000$



---

---
title: "化学1（chem1）- 化学合成"
layout: "post"
diff: 普及/提高-
pid: P2784
tag: ['图论', '洛谷原创', '队列']
---
# 化学1（chem1）- 化学合成
## 题目背景

蒟蒻 HansBug 在化学考场上，挠了无数次的头，可脑子里还是一片空白。
## 题目描述

眼下出现在蒟蒻 HansBug 面前的是一个化学合成题，据他所知，一般答案如下面这样的格式：

![](https://cdn.luogu.com.cn/upload/pic/2223.png) （接下一行）

![](https://cdn.luogu.com.cn/upload/pic/2221.png) 

简单解释下：每种化合物可以通过一步反应生成另一个化合物（将这称作一步反应，设为 $A\rightarrow B$），现在假设每个 $A\rightarrow B$ 中，理论上 $1$ 个单位的 $A$ 都仅可以生成 $1$ 个单位的 $B$。然而实际实验表明，并不存在绝对完全的化学转化，设转化率为 $C$（即 $1$ 个单位 $A$ 实际可以生成 $C$ 个单位的 $B$，$0<C<1$）。

现在蒟蒻 HansBug 的知识体系中有 $N$ 个这样 $A\rightarrow B$ 的转化。然而题目中蒟蒻 HansBug 要由 $1$ 个单位的化合物 $S$ 生成化合物 $T$，可是他脑细胞和 RP 已经消耗殆尽，所以找到最终产量最高的合成路线的艰巨任务就交给你啦！
## 输入格式

第一行为四个整数：$N,M,S,T$，分别表示总共出现的化合物个数、HansBug 所知道的反应个数、起始的化合物序号、终末的化合物序号（$1\le S,T\le N$）。

第 $2 \sim M+1$ 行每行为两个整数和一个实数：$A_i,B_i,C_i$，分别表示第 $i$ 个反应为由 $1$ 个单位的 $A_i$ 化合物生成 $C_i$ 单位的 $B_i$ 化合物。
## 输出格式

一行，包含一个实数，为最佳路线下最终的产量（四舍五入保留 $4$ 位小数），如果没有可行路线的话，输出 `orz`。
## 样例

### 样例输入 #1
```
3 3 1 3
1 3 0.8
1 2 0.9
2 3 0.9

```
### 样例输出 #1
```
0.8100
```
### 样例输入 #2
```
3 3 2 1
1 3 0.8
1 2 0.9
2 3 0.9

```
### 样例输出 #2
```
orz
```
## 提示

样例 1 和样例 2 中，两条合成路线分别为 $1\rightarrow3$、$1\rightarrow2$、$2\rightarrow3$，产率分别为 $0.8$、$0.9$、$0.9$。

在样例 1 中，有两种可行的路线 $1\rightarrow3$ 和 $1\rightarrow2\rightarrow3$ ，最终产量分别为 $0.8$、$0.9\times0.9=0.81$，故第二条路线更优，产量为 $0.8100$。

样例 2 中，$2$ 只能生成 $3$，$3$ 无法生成别的化合物，故无法生成，蒟蒻 HansBug 只好选择 `orz`。

**【数据范围】**

![](https://cdn.luogu.com.cn/upload/pic/2220.png)



---

---
title: "[USACO08FEB] Eating Together S"
layout: "post"
diff: 普及/提高-
pid: P2896
tag: ['动态规划 DP', '递推', '2008', 'USACO', '队列']
---
# [USACO08FEB] Eating Together S
## 题目描述

The cows are so very silly about their dinner partners. They have organized themselves into three groups (conveniently numbered 1, 2, and 3) that insist upon dining together. The trouble starts when they line up at the barn to enter the feeding area.

Each cow i carries with her a small card upon which is engraved Di (1 ≤ Di ≤ 3) indicating her dining group membership. The entire set of N (1 ≤ N ≤ 30,000) cows has lined up for dinner but it's easy for anyone to see that they are not grouped by their dinner-partner cards.

FJ's job is not so difficult. He just walks down the line of cows changing their dinner partner assignment by marking out the old number and writing in a new one. By doing so, he creates groups of cows like 111222333 or 333222111 where the cows' dining groups are sorted in either ascending or descending order by their dinner cards.

FJ is just as lazy as the next fellow. He's curious: what is the absolute mminimum number of cards he must change to create a proper grouping of dining partners? He must only change card numbers and must not rearrange the cows standing in line.

FJ的奶牛们在吃晚饭时很傻。他们把自己组织成三组（方便编号为1, 2和3），坚持一起用餐。当他们在谷仓排队进入喂食区时，麻烦就开始了。


每头奶牛都随身带着一张小卡片，小卡片上刻的是Di（1≤Di≤3）表示她属于哪一组。所有的N（1≤N≤30000）头奶牛排队吃饭，但他们并不能按卡片上的分组站好。


FJ的工作并不是那么难。他只是沿着牛的路线走下去，把旧的号码标出来，换上一个新的。通过这样做，他创造了一群奶牛，比如111222333或333222111，奶牛的就餐组按他们的晚餐卡片按升序或降序排列。


FJ就像任何人一样懒惰。他很好奇：怎样他才能进行适当的分组，使得他只要修改最少次数的数字？由于奶牛们已经很长时间没有吃到饭了，所以“哞哞”的声音到处都是，FJ只好更换卡号，而不能重新排列已经排好队的奶牛。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line i describes the i-th cow's current dining group with a single integer: Di

- 第1行：一个整数：n

- 第2~n+1行：第i-1行描述第i个奶牛目前分组。

## 输出格式

\* Line 1: A single integer representing the minimum number of changes that must be made so that the final sequence of cows is sorted in either ascending or descending order

一个整数，表示必须做出的最小变化数，以便以升序或降序排序最终序列。

## 样例

### 样例输入 #1
```
5
1
3
2
1
1

```
### 样例输出 #1
```
1

```
## 提示

感谢@一思千年 提供翻译



---

---
title: "[USACO11NOV] Cow Lineup S"
layout: "post"
diff: 普及/提高-
pid: P3029
tag: ['2011', 'USACO', '单调队列', '离散化', '队列', '双指针 two-pointer']
---
# [USACO11NOV] Cow Lineup S
## 题目描述

Farmer John has hired a professional photographer to take a picture of some of his cows.  Since FJ's cows represent a variety of different breeds, he would like the photo to contain at least one cow from each distinct breed present in his herd.

FJ's N cows are all standing at various positions along a line, each described by an integer position (i.e., its x coordinate) as well as an integer breed ID.  FJ plans to take a photograph of a contiguous range of cows along the line.  The cost of this photograph is equal its size -- that is, the difference between the maximum and minimum x coordinates of the cows in the range of the photograph.

Please help FJ by computing the minimum cost of a photograph in which there is at least one cow of each distinct breed appearing in FJ's herd.

## 输入格式

\* Line 1: The number of cows, N (1 <= N <= 50,000). 

\* Lines 2..1+N: Each line contains two space-separated positive integers specifying the x coordinate and breed ID of a single cow.  Both numbers are at most 1 billion.

## 输出格式

\* Line 1: The smallest cost of a photograph containing each distinct breed ID.

## 样例

### 样例输入 #1
```
6 
25 7 
26 1 
15 1 
22 3 
20 1 
30 1 

```
### 样例输出 #1
```
4 

```
## 提示

There are 6 cows, at positions 25,26,15,22,20,30, with respective breed IDs 7,1,1,3,1,1.


The range from x=22 up through x=26 (of total size 4) contains each of the distinct breed IDs 1, 3, and 7 represented in FJ's herd.

## 题目翻译

### 问题描述

农民约翰雇一个专业摄影师给他的部分牛拍照。由于约翰的牛有好多品种，他喜欢他的照片包含每个品种的至少一头牛。

约翰的牛都站在一条沿线的不同地方， 每一头牛由一个整数位置 $X_i$ 以及整数品种编号 $ID_i$ 表示。

约翰想拍一张照片，这照片由沿线的奶牛的连续范围组成。照片的成本与规模相当，这就意味着，在一系列照片中的最大和最小 $X$ 坐标的差距决定了照片的成本。

请帮助约翰计算最小的照片成本，这些照片中有每个不同的品种的至少一头牛，没有两头牛愿意站在同一个地点的。


### 输入格式 


第 $1$ 行：牛的数量 $N$；


第 $2..1+N$ 行：每行包含 2 个以空格分隔的正整数 $X_i$ 和 $ID_i$；意义如题目描述；


### 输出格式 


输出共一行，包含每个不同品种 $\rm ID$ 的照片的最低成本。


---

---
title: "[POI 2010] PIL-Pilots"
layout: "post"
diff: 普及/提高-
pid: P3512
tag: ['2010', '单调队列', 'POI（波兰）', '队列']
---
# [POI 2010] PIL-Pilots
## 题目描述

In the Byteotian Training Centre, the pilots prepare for missions requiring extraordinary precision and control.

One measure of a pilot's capability is the duration he is able to fly along a desired route without deviating too much -    simply put, whether he can fly steadily. This is not an easy task, as the simulator is so sensitive that it registers    even a slightest move of the yoke1.

At each moment the simulator stores a single parameter describing the yoke's position.

Before each training session a certain tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.1.png) is set.

The pilots' task then is to fly as long as they can in such a way that all the yoke's position measured during the    flight differ by at most ![](http://main.edu.pl/images/OI17/pil-en-tex.2.png). In other words, a fragment of the flight starting at time ![](http://main.edu.pl/images/OI17/pil-en-tex.3.png) and ending at time ![](http://main.edu.pl/images/OI17/pil-en-tex.4.png)    is within tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.5.png) if the position measurements, starting with ![](http://main.edu.pl/images/OI17/pil-en-tex.6.png)-th and ending with ![](http://main.edu.pl/images/OI17/pil-en-tex.7.png)-th,    form such a sequence ![](http://main.edu.pl/images/OI17/pil-en-tex.8.png) that for all elements ![](http://main.edu.pl/images/OI17/pil-en-tex.9.png) of this sequence, the inequality ![](http://main.edu.pl/images/OI17/pil-en-tex.10.png) holds.

Your task is to write a program that, given a number ![](http://main.edu.pl/images/OI17/pil-en-tex.11.png) and the sequence of yoke's position measurements,    determines the length of the longest fragment of the flight that is within the tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.12.png).

给定 $n, k$ 和一个长度为 $n$ 的序列，求最长的最大值最小值相差不超过 $k$ 的子段。
## 输入格式

In the first line of the standard input two integers are given, ![](http://main.edu.pl/images/OI17/pil-en-tex.13.png) and ![](http://main.edu.pl/images/OI17/pil-en-tex.14.png)      (![](http://main.edu.pl/images/OI17/pil-en-tex.15.png), ![](http://main.edu.pl/images/OI17/pil-en-tex.16.png)), separated by a single space,      denoting the tolerance level and the number of yoke's position measurements taken.

The second line gives those measurements, separated by single spaces. Each measurement      is an integer from the interval from ![](http://main.edu.pl/images/OI17/pil-en-tex.17.png) to ![](http://main.edu.pl/images/OI17/pil-en-tex.18.png).

第一行两个由空格隔开的整数 $k, n$（$0\leq k\leq 2\times 10 ^ 9$，$1\leq n\leq 3\times 10 ^ 6$），$k$ 表示设定的极差的最大值，$n$ 表示序列的长度。

第二行 $n$ 个由空格隔开的整数 $a_i$（$1\leq a_i\leq 2\times 10^ 9$）表示序列。

## 输出格式

Your program should print a single integer to the standard output:

the maximum length of a fragment of the flight that is within the given tolerance level.

一个整数表示符合条件的子段的长度最大值。

## 样例

### 样例输入 #1
```
3 9
5 1 3 5 8 6 6 9 10
```
### 样例输出 #1
```
4
```
## 提示

样例解释：$5, 8, 6, 6$ 和 $8, 6, 6, 9$ 都是满足条件长度为 $4$ 的子段。


---

---
title: "[USACO17FEB] Why Did the Cow Cross the Road II S"
layout: "post"
diff: 普及/提高-
pid: P3662
tag: ['2017', 'USACO', '枚举', '前缀和', '队列']
---
# [USACO17FEB] Why Did the Cow Cross the Road II S
## 题目描述

The long road through Farmer John's farm has $N$ crosswalks across it, conveniently numbered $1 \ldots N$ ($1 \leq N \leq 100,000$). To allow cows to cross at these crosswalks, FJ installs electric crossing signals, which light up with a green cow icon when it is ok for the cow to cross, and red otherwise. Unfortunately, a large electrical storm has damaged some of his signals. Given a list of the damaged signals, please compute the minimum number of signals that FJ needs to repair in order for there to exist some contiguous block of at least $K$ working signals.
## 输入格式

The first line of input contains $N$, $K$, and $B$ ($1 \leq B, K \leq N$). The next $B$ lines each describe the ID number of a broken signal.
## 输出格式

Please compute the minimum number of signals that need to be repaired in order for there to be a contiguous block of $K$ working signals somewhere along the road.

## 样例

### 样例输入 #1
```
10 6 5
2
10
1
5
9
```
### 样例输出 #1
```
1
```
## 题目翻译

### 题目描述

穿过 Farmer John 农场的长路上有 $N$ 个人行横道，方便地用编号 $1 \ldots N$ 标识（$1 \leq N \leq 100,000$）。为了让奶牛能够通过这些横道过马路，FJ 安装了电子过马路信号灯，当奶牛可以安全过马路时，信号灯会显示绿色的奶牛图标，否则显示红色。不幸的是，一场大雷暴损坏了他的一些信号灯。给定损坏信号灯的列表，请计算 FJ 需要修复的最少信号灯数量，以便存在至少 $K$ 个连续的信号灯正常工作。

### 输入格式

输入的第一行包含 $N$、$K$ 和 $B$（$1 \leq B, K \leq N$）。接下来的 $B$ 行每行描述一个损坏信号灯的 ID 编号。

### 输出格式

请计算需要修复的最少信号灯数量，以便在道路上某处存在一个长度为 $K$ 的连续正常工作信号灯块。


---

---
title: "道路重建"
layout: "post"
diff: 普及/提高-
pid: P3905
tag: ['图论', '最短路', '队列']
---
# 道路重建
## 题目描述

从前，在一个王国中，在 $n$ 个城市间有 $m$ 条道路连接，而且任意两个城市之间至多有一条道路直接相连。在经过一次严重的战争之后，有 $d$ 条道路被破坏了。国王想要修复国家的道路系统，现在有两个重要城市 $A$ 和 $B$ 之间的交通中断，国王希望尽快的恢复两个城市之间的连接。你的任务就是修复一些道路使 $A$ 与 $B$ 之间的连接恢复，并要求修复的道路长度最小。
## 输入格式

输入文件第一行为一个整数 $n\ (2<n\le 100)$，表示城市的个数。这些城市编号从 $1$ 到 $n$。

第二行为一个整数 $m\ (n-1\le m\le \dfrac{1}{2}n(n-1))$，表示道路的数目。

接下来的 $m$ 行，每行 $3$ 个整数 $i,j,k\ (1 \le i,j \le n,i\neq j,0<k \le 100)$，表示城市 $i$ 与 $j$ 之间有一条长为 $k$ 的道路相连。

接下来一行为一个整数 $d\ (1\le d\le m)$，表示战后被破坏的道路的数目。在接下来的 $d$ 行中，每行两个整数 $i$ 和 $j$，表示城市 $i$ 与 $j$ 之间直接相连的道路被破坏。

最后一行为两个整数 $A$ 和 $B$，代表需要恢复交通的两个重要城市。
## 输出格式

输出文件仅一个整数，表示恢复 $A$ 与 $B$ 间的交通需要修复的道路总长度的最小值。

## 样例

### 样例输入 #1
```
3
2
1 2 1
2 3 2
1
1 2
1 3
```
### 样例输出 #1
```
1
```


---

---
title: "[Code+#1] 木材"
layout: "post"
diff: 普及/提高-
pid: P4058
tag: ['二分', 'O2优化', '优先队列', 'Code+']
---
# [Code+#1] 木材
## 题目描述

有 $n$ 棵树，初始时每棵树的高度为 $H_i$，第 $i$ 棵树每月都会长高 $A_i$。现在有个木料长度总量为 $S$ 的订单，客户要求每块木料的长度不能小于  $L$，而且木料必须是整棵树（即不能为树的一部分）。现在问你最少需要等多少个月才能满足订单。

## 输入格式

第一行 $3$ 个用空格隔开的非负整数 $n,S,L$，表示树的数量、订单总量和单块木料长度限制。

第二行 $n$ 个用空格隔开的非负整数，依次为 $H_1,H_2, ... ,H_n$。

第三行 $n$ 个用空格隔开的非负整数，依次为 $A_1,A_2, ... ,A_n$。

## 输出格式

输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
3 74 51
2 5 2
2 7 9

```
### 样例输出 #1
```
7
```
## 提示

对于样例，在六个月后，各棵树的高度分别为 $14,47,56$，此时无法完成订单。

在七个月后，各棵树的高度分别为 $16,54,65$，此时可以砍下第 $2$ 和第 $3$ 棵树完成订单了。

 ![](https://cdn.luogu.com.cn/upload/pic/12821.png) 

来自 CodePlus 2017 11 月赛，清华大学计算机科学与技术系学生算法与竞赛协会 荣誉出品。

Credit：idea/郑林楷 命题/郑林楷 验题/王聿中

Git Repo：https://git.thusaac.org/publish/CodePlus201711

感谢腾讯公司对此次比赛的支持。



---

---
title: "【模板】单源最短路径（标准版）"
layout: "post"
diff: 普及/提高-
pid: P4779
tag: ['图论', '优先队列', '最短路']
---
# 【模板】单源最短路径（标准版）
## 题目背景

2018 年 7 月 19 日，某位同学在 [NOI Day 1 T1 归程](https://www.luogu.org/problemnew/show/P4768) 一题里非常熟练地使用了一个广为人知的算法求最短路。

然后呢？

$100 \rightarrow 60$；

$\text{Ag} \rightarrow \text{Cu}$；

最终，他因此没能与理想的大学达成契约。

小 F 衷心祝愿大家不再重蹈覆辙。
## 题目描述

给定一个 $n$ 个点，$m$ 条有向边的带非负权图，请你计算从 $s$ 出发，到每个点的距离。

数据保证你能从 $s$ 出发到任意点。
## 输入格式

第一行为三个正整数 $n, m, s$。
第二行起 $m$ 行，每行三个非负整数 $u_i, v_i, w_i$，表示从 $u_i$ 到 $v_i$ 有一条权值为 $w_i$ 的有向边。
## 输出格式

输出一行 $n$ 个空格分隔的非负整数，表示 $s$ 到每个点的距离。
## 样例

### 样例输入 #1
```
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4
```
### 样例输出 #1
```
0 2 4 3
```
## 提示

样例解释请参考 [数据随机的模板题](https://www.luogu.org/problemnew/show/P3371)。

$1 \leq n \leq 10^5$；

$1 \leq m \leq 2\times 10^5$；

$s = 1$；

$1 \leq u_i, v_i\leq n$；

$0 \leq w_i \leq 10 ^ 9$,

$0 \leq \sum w_i \leq 10 ^ 9$。

本题数据可能会持续更新，但不会重测，望周知。

2018.09.04 数据更新 from @zzq


---

---
title: "[COCI 2014/2015 #7] PROSJEK"
layout: "post"
diff: 普及/提高-
pid: P7795
tag: ['2014', '二分', '单调队列', 'Special Judge', 'COCI（克罗地亚）']
---
# [COCI 2014/2015 #7] PROSJEK
## 题目描述

给定一个有 $n$ 个整数的数列 $a$。请找出一个长度至少为 $k$ 的连续子序列，使这个子序列的所有数的平均值最大。
## 输入格式

输入共 $2$ 行。

第一行输入两个整数 $n,k$。  
第二行输入 $n$ 个整数 $a_1,a_2,\dots,a_n$，表示数列 $a$ 的所有数。
## 输出格式

输出仅一行，一个实数，表示长度至少为 $k$ 的连续子序列的数的最大平均值。

在每个测试点中，只要你的程序给出的答案和标准答案的相对误差不超过 $10^{-3}$，你的程序就可以通过该测试点。
## 样例

### 样例输入 #1
```
4 1
1 2 3 4
```
### 样例输出 #1
```
4.000000
```
### 样例输入 #2
```
4 2
2 4 3 4
```
### 样例输出 #2
```
3.666666
```
### 样例输入 #3
```
6 3
7 1 2 1 3 6
```
### 样例输出 #3
```
3.333333
```
## 提示

**【数据范围】**

对于 $30\%$ 的数据，保证 $n\leqslant 5000$。  
对于所有数据，$1\leqslant k\leqslant n\leqslant 3\times 10^5$，$1\leqslant a_i\leqslant 10^6$。

**【题目来源】**

本题来源自 **_[COCI 2014-2015](https://hsin.hr/coci/archive/2014_2015/) [CONTEST 7](https://hsin.hr/coci/archive/2014_2015/contest7_tasks.pdf) T5 PROSJEK_**，按照原题数据配置，满分 $140$ 分。

由 [Eason_AC](https://www.luogu.com.cn/user/112917) 翻译整理提供。


---

---
title: "[COCI 2007/2008 #5] AVOGADRO"
layout: "post"
diff: 普及/提高-
pid: P7935
tag: ['模拟', '2007', '枚举', '队列', 'COCI（克罗地亚）']
---
# [COCI 2007/2008 #5] AVOGADRO
## 题目描述

Luka 画了一张 $3$ 行 $N$ 列的表格，然后将整数 $1$ 到 $N$ 写进表格。对于表格第一行，每个整数只出现一次。对于其余两行，每个数字可以出现任意次或者不出现。

Luka 现在可以删去任意一些列。完成后，他对这个表的每一行进行升序排序。

他希望得到一张表，使得表中的三行在升序排序后完全相同。请您求出他至少需要删去多少列。
## 输入格式

第一行，一个整数 $N$，表示表中数字的列数。

接下来三行，每行包含 $N$ 个整数。这些整数都在 $1$ 到 $N$ 之间，第一行每个数字有且仅出现一次。
## 输出格式

一行，一个整数，表示 Luka 至少需要删除的列数。
## 样例

### 样例输入 #1
```
7
5 4 3 2 1 6 7
5 5 1 1 3 4 7
3 7 1 4 5 6 2 
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
9
1 3 5 9 8 6 2 4 7
2 1 5 6 4 9 3 4 7
3 5 1 9 8 6 2 8 7
```
### 样例输出 #2
```
2
```
## 提示

对于 $40\%$ 的测试点，$N\le 100$。

对于 $70\%$ 的测试点，$N\le 10000$。

对于 $100\%$ 的测试点，$1\le N\le 10^5$。

### 样例 1 解释：

对于样例 1，Luka 需要删除第二、第四、第六和第七列。删除并排序后，这三行都只包含 $1,3,5$ 三个整数。

本题分值按照原比赛设置，满分 $60$ 分。


---

---
title: "[蓝桥杯 2018 省 B] 日志统计"
layout: "post"
diff: 普及/提高-
pid: P8661
tag: ['2018', '单调队列', '蓝桥杯省赛']
---
# [蓝桥杯 2018 省 B] 日志统计
## 题目描述

小明维护着一个程序员论坛。现在他收集了一份“点赞”日志，日志共有 $N$ 行。其中每一行的格式是 `ts id`，表示在 $ts$ 时刻编号 $id$ 的帖子收到一个“赞”。

现在小明想统计有哪些帖子曾经是“热帖”。如果一个帖子曾在任意一个长度为 $D$ 的时间段内收到不少于 $K$ 个赞，小明就认为这个帖子曾是“热帖”。

具体来说，如果存在某个时刻 $T$ 满足该帖在 $[T,T+D)$ 这段时间内（注意是左闭右开区间）收到不少于 $K$ 个赞，该帖就曾是“热帖”。

给定日志，请你帮助小明统计出所有曾是“热帖”的帖子编号。
## 输入格式

第一行包含三个整数 $N$、$D$ 和 $K$。

以下 $N$ 行每行一条日志，包含两个整数 $ts$ 和 $id$。


## 输出格式

按从小到大的顺序输出热帖 $id$。每个 $id$ 一行。
## 样例

### 样例输入 #1
```
7 10 2  
0 1  
0 10    
10 10  
10 1  
9 1
100 3  
100 3  
```
### 样例输出 #1
```
1  
3  
```
## 提示

对于 $50\%$ 的数据，$1 \le K \le N \le 1000$。

对于 $100\%$ 的数据，$1 \le K \le N \le 10^5$，$0 \le id, ts \le 10^5$。

时限 1 秒, 256M。蓝桥杯 2018 年第九届省赛


---

---
title: "[蓝桥杯 2023 国 B] 合并数列"
layout: "post"
diff: 普及/提高-
pid: P9422
tag: ['2023', '队列', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 B] 合并数列
## 题目描述

小明发现有很多方案可以把一个很大的正整数拆成若干正整数的和。他采取了其中两种方案，分别将他们列为两个数组 $\{a_1, a_2, \cdots a_n\}$ 和 $\{b_1, b_2, \cdots b_m\}$。两个数组的和相同。

定义一次合并操作可以将某数组内相邻的两个数合并为一个新数，新数的值是原来两个数的和。小明想通过若干次合并操作将两个数组变成一模一样，即 $n = m$ 且对于任意下标 $i$ 满足 $a_i = b_i$。请计算至少需要多少次合并操作可以完成小明的目标。
## 输入格式

输入共 $3$ 行。

第一行为两个正整数 $n, m$。

第二行为 $n$ 个由空格隔开的整数 $a_1, a_2, \cdots, a_n$。

第三行为 $m$ 个由空格隔开的整数 $b_1, b_2, \cdots, b_m$。
## 输出格式

输出共 $1$ 行，一个整数。
## 样例

### 样例输入 #1
```
4 3
1 2 3 4
1 5 4
```
### 样例输出 #1
```
1
```
## 提示

### 样例说明

只需要将 $a_2$ 和 $a_3$ 合并，数组 $a$ 变为 $\{1,5,4\}$，即和 $b$ 相同。

### 评测用例规模与约定

 - 对于 $20\%$ 的数据，保证 $n,m \le 10^3$。
 - 对于 $100\%$ 的数据，保证 $n, m \le 10^5$，$0 < a_i, b_i \le 10^5$。
 
第十四届蓝桥杯大赛软件赛决赛 C/C++ 大学 B 组 D 题


---

---
title: "queue"
layout: "post"
diff: 普及/提高-
pid: P9518
tag: ['模拟', '洛谷原创', 'O2优化', '队列']
---
# queue
## 题目背景

你说的对，但是舞萌 DX 是一款后面忘了。
## 题目描述

**补充说明：这里的排队和传统的排队有出入。正在游玩的人为队列的前两位，所以正在游玩视为正在排队。**

机厅里有一台游戏机，每次可供最多两人同时游玩。但是来玩的人显然不止两个！这个时候他们就需要排队了，而你需要写一个程序维护这个队列，并在他人游玩结束后通知接下来上场的人。在整个过程中，有以下几种事件可能发生：

- `start`：一局游戏开始。若这不是第一局游戏，则上一局的参与者**在这一局游戏开始前一瞬间**按照原本的顺序回到队尾。此时你应该按在队列中的顺序输出这一局上场的人的名字（正常来讲是队列前两位或者唯一一个人），若有两个则以空格分割。若这一局无人上场，则输出 `Error` 并忽略这条事件。

- `arrive x`：$x$ 到达机厅并且将自己加入队尾，此时 $x$ 不应该在排队，否则输出 `Error` 并忽略这条事件。若该事件成功执行则输出 `OK`。

- `leave x`：$x$ 离开机厅并离开队列。此时 $x$ 应该在排队但不应该在游玩，否则输出 `Error` 并忽略这条事件。若该事件成功执行则输出 `OK`。

你需要维护队列信息，并输出上述事件中要求的输出。
## 输入格式

第一行一个整数 $n$，表示事件条数。

接下来 $n$ 行，每行表示一条事件。
## 输出格式

按照题目要求输出 $n$ 行，表示程序对事件的响应。
## 样例

### 样例输入 #1
```
14
start
arrive A
start
arrive B
arrive C
arrive D
start
leave C
leave D
start
arrive A
arrive D
leave E
start
```
### 样例输出 #1
```
Error
OK
A
OK
OK
OK
B C
Error
OK
A B
Error
OK
Error
C D
```
### 样例输入 #2
```
3
arrive A
arrive B
arrive C
```
### 样例输出 #2
```
OK
OK
OK
```
## 提示

**【样例说明】**

样例 $1$ 中发生了如下的事件：

- 第一次 `start` 时队列并没有任何人，输出 `Error`。
- `A` 随即加入队列。
- 第二次 `start` 时仅有 `A` 一个人，所以输出 `A`。
- `B, C, D` 随即依次加入队列。
- 第三次 `start` 时 `B, C` 上场。
- `C` 试图离开，但是他在游玩。所以输出 `Error`。
- `D` 成功离开。
- 第四次 `start` 时 `A, B` 上场。
- `A` 试图加入队列，但是他已经在队列中。输出 `Error`。
- `D` 重新加入队列。
- `E` 试图离开，但是他根本不在排队，输出 `Error`。
- 第五次 `start` 时 `C, D` 上场。

样例 $2$ 中，`A, B, C` 依次入队，操作合法，输出三个 `OK`。

**【数据范围】**

对于 $20\%$ 的数据，保证 $n=1$。

对于 $40\%$ 的数据，保证 $n\le 2000$。

对于另外 $20\%$ 的数据，保证没有 `leave` 操作。

对于另外 $20\%$ 的数据，人名只有可能是单个大写字母。

对于 $100\%$ 的数据，保证 $1 \le n\le 10^5$，人名仅含有大小写字母且长度不超过 $10$。

**本题输入输出量较大，请注意使用合理的输入输出方式。**


---

