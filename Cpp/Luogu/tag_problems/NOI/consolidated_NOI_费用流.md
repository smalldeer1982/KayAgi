---
title: "[GCJ 2012 #3] Lost Password"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13331
tag: ['2012', '模拟费用流', 'Google Code Jam']
---
# [GCJ 2012 #3] Lost Password
## 题目描述

Ashish has forgotten his password. He remembers that he used the following algorithm to create his password: Ashish took up to $k$ consecutive words from a passage of text, and took the first letter from each word. Then, he might have changed some of the letters to their "l33tspeak" equivalents. Specifically, he might have changed "o" to "0", "i" to "1", "e" to "3", "a" to "4", "s" to "5", "t" to "7", "b" to "8" and/or "g" to "9".

For example, if Ashish took his password from the first sentence of The Fellowship of the Ring -- "This book is largely concerned with Hobbits, and from its pages a reader may discover much of their character and a little of their history" -- Ashish would have reduced that to "tbilcwhafiparmdmotcaaloth". Then the password might be "tbilcwh", "7b1lcwh4f", "a", "4", or "4al07h", etc.

Ashish has a special extension installed in his browser that will prevent his computer from uploading any string that contains his password. In order to figure out which passage of text he took his password from, Ashish has created a webpage to take advantage of this extension. Every second, the webpage will tell the browser to post a "password string" for a new passage of text: a string that contains all of the possible passwords that Ashish could have chosen from that passage of text. As soon as his browser fails to post such a string, Ashish will know where he took his password from.

For example, if $k = 2$ and the passage of text contains words starting with the letters "google", then one password string for that passage is "goo0og00gle9o909l3". All substrings of length $\leq 2$ from the original string, and all of their l33tspeak equivalents, are contained in the new string.

Given the first letters of the words in a passage of text, what is the minimum number of characters in the "password string" of that passage?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case consists of two lines. The first line contains the integer $k$. The second line contains a string $S$, representing the first letters of the words in a passage of text. $S$ contains only the characters 'a' - 'z', with no spaces.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the minimum number of characters in the password string for $S$.
## 样例

### 样例输入 #1
```
4
2
poppop
2
google
2
tbilcwhafiparmdmotcaaloth
10
tbilcwhafiparmdmotcaaloth
```
### 样例输出 #1
```
Case #1: 6
Case #2: 18
Case #3: 53
Case #4: 1136
```
## 提示

**Sample Explanation**

- In the first sample input, one possible password string is "0ppop0".
- In the second sample input, one possible password string is "goo0og00gle9o909l3".

**Limits**

- $1 \leq T \leq 20.$
- $S$ will contain at least $2 \times k$ characters.
- There will exist a password string with at most $10^{18}$ characters.

**Test set 1 (7 Pts, Visible Verdict)**

- $S$ will contain at most 1000 characters.
- $k = 2.$

**Test set 2 (36 Pts, Hidden Verdict)**

- $S$ will contain at most 5000 characters.
- $2 \leq k \leq 500.$


---

---
title: "无限之环"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4003
tag: ['2017', '网络流', '费用流', 'CTT（清华集训/北大集训）']
---
# 无限之环
## 题目描述

曾经有一款流行的游戏，叫做 Infinity Loop，先来简单的介绍一下这个游戏：

游戏在一个 $n \times m$ 的网格状棋盘上进行，其中有些小方格中会有水管，水管可能在格某些方向的边界的中点有接口，所有水管的粗细都相同，所以如果两个相邻方格的共边界的中点都有接头，那么可以看作这两个接头互相连接。水管有以下 $15$ 种形状：

 ![](https://cdn.luogu.com.cn/upload/pic/12049.png) 

游戏开始时，棋盘中水管可能存在漏水的地方。

形式化地：如果存在某个接头，没有和其它接头相连接，那么它就是一个漏水的地方。

玩家可以进行一种操作：选定一个含有**非直线型**水管的方格，将其中的水管绕方格中心顺时针或逆时针旋转 $90$ 度。

直线型水管是指左图里中间一行的两种水管。

现给出一个初始局面，请问最少进行多少次操作可以使棋盘上不存在漏水的地方。

## 输入格式

第一行两个正整数 $n$, $m$, 代表网格的大小。

接下来 $n$ 行每行 $m$ 个数，每个数是 $[0,15]$ 中的一个，你可以将其看作一个 $4$ 位的二进制数，从低到高每一位分别代表初始局面中这个格子上、右、下、左方向上是否有水管接头。

特别地，如果这个数是 $0$ ，则意味着这个位置没有水管。

比如 $3(0011_{(2)})$ 代表上和右有接头，也就是一个 $L$ 型，而 $12(1100_{(2)})$ 代表下和左有接头，也就是将 $L$ 型旋转 $180$ 度。

## 输出格式

输出共一行，表示最少操作次数。如果无法达成目标，输出 $-1$。

## 样例

### 样例输入 #1
```
2 3
3 14 12
3 11 12
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 2
1 8
5 10
2 4
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
3 3
9 11 3
13 15 7
12 14 6
```
### 样例输出 #3
```
16
```
## 提示

【样例 1 解释】

样例 1 棋盘如下:

旋转方法很显然，先将左上角虚线方格内的水管顺时针转 $90$ 度

 ![](https://cdn.luogu.com.cn/upload/pic/12050.png) 

然后右下角虚线方格内的水管逆时针旋转 $90$ 度，这样就使得水管封闭了

【样例 2 解释】

样例 2 为题目描述中的第一张图片，无法达成目标。

【样例 3 解释】

样例 3 为题目描述中的第二张图片，将除了中心方格以外的每个方格内的水管都转 $180$ 度即可。


 ![](https://cdn.luogu.com.cn/upload/pic/12051.png) 




---

---
title: "[CTSC2010] 产品销售"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4217
tag: ['2010', '线段树', '模拟费用流', 'CTSC/CTS']
---
# [CTSC2010] 产品销售
## 题目描述

A 公司正在热销某计算机产品，作为 A 公司 CEO 的小 A 打算为接下来连续的 $N$ 个销售季度制定一份具体的生产和销售方案。 已知第 $i$ 个销售季度该产品的订购量为 $D_i$，在第 $i$ 个季度，A 公司会通过如下几种方式来解决用户的订购需求：

○ 在第 $i$ 个季度生产新的产品来销售。

○ 若在第 $i$ 个季度以前库存还有多余的产品，则可以直接在第 $i$ 个季度销售(注意第一个季度之前没有任何库存产品)。

○ 在第 $i$ 个季度可以不完成全部的订购需求，而将未完成的订购需求推迟，归入到下一个季度$(i + 1)$的产品订购需求中。

A 公司需要考虑以下几种耗费： 生产新产品的成本耗费、库存产品的额外储存耗费以及推迟订购需求而需要赔偿给用户的损失费。另外由于劳力和资源的限制，每个销售季度能够生产新产品的数量是有限的，各季度的耗费和可以生产的产品上限数也不尽相同，具体如下：

○ 在第 $i$ 个季度最多可以生产 $U_i$ 件新的产品，每一件的成本为 $P_i$。

○ 第 $i$ 个季度保存下来的产品，可以用于以后季度的销售。对于每一件产品，若从第 $i$ 季度保存到第 $i + 1$ 季度， 需要额外支付 $M_i$ 的存储费用(注意产品保存到下个季度后可能再次库存)。

○ 对于第 $i$ 个季度需要推迟而归入到下一个季度订购需求的每一件产品， A
公司需要赔偿给用户损失费 $C_i$(注意延迟到下个季度可能再次被延迟, 费
用按后面季度的延迟费用计)。

在第 $N$ 个季度结束后， A 公司必须解决之前所有的用户订单。可以保证， A公司能够生产的产品总数不会低于总订购量， 也就是说一定存在一组生产和销售方案使得满足所有的用户订购需求。小 A 想知道如何来安排产品的生产和销售，使得在满足所有订购需求的前提下公司总的耗费最小。
## 输入格式

输入文件 $\tt{product.in}$ 第一行是一个正整数 $N$，表示有 $N$ 个销售季度。

第二行有 $N$ 个非负整数 $D_1$, $D_2$, .., $D_N$，表示第 $i$ 个季度的订购量。

第三行有 $N$ 个非负整数 $U_1$, $U_2$, .., $U_N$，表示第 $i$ 个季度最多可以生产的新的产品数。

第四行有 $N$ 个非负整数 $P_1$, $P_2$, .., $P_N$，表示第 $i$ 个季度生产一件新产品的成本。

第五行有 $N - 1$ 个非负整数 $M_1$, $M_2$, ..,$M_{N-1}$，表示将一件产品从第 $i$ 个季度保存到第 $i +1$ 个季度所需要的额外的耗费。

第六行有 $N-1$ 个非负整数 $C_1$, $C_2$, .., $C_{N-1}$，表示一件产品的订购需求在第 $i$ 个季度没有完成而归入到第 $i +1$ 个季度的订购量中，需要赔偿给用户的损失费。
## 输出格式

输出文件 $\tt{product.out}$ 仅包含一个非负整数，表示公司的最小总耗费。
## 样例

### 样例输入 #1
```
4
3 2 1 2
2 5 2 2
5 1 5 5
1 2 1
5 3 3
```
### 样例输出 #1
```
30
```
## 提示

【样例说明】

第一个季度生产 $2$ 件产品，第二个季度生产 $5$ 件产品，第三个季度不生产产品，第四个季度生产 $1$ 件产品，成本为 $2 * 5 + 5 * 1 + 0 * 5 + 1 * 5 = 20$。

因为第一个季度最多只能生产 $2$ 件产品，无法满足 $3$ 件的订购量，因此将 $1$件产品的订购量推迟到第二个季度，赔偿给用户的损失费为 $5$。

第二个季度由于第一个季度推迟了一件产品的订购需求， 因而订购量变为 $3$。该季度生产了 $5$ 件产品，剩下的 $2$ 件保存下来。第三个季度直接销售库存的产品，再多出来的 $1$ 件产品继续储存到第四个季度，加上第四个季度生产了 $1$ 件产品，因此满足了所有订单需求。总的储存费用为 $2 * 2 + 1 * 1 = 5$。

总的费用为 $20 + 5 + 5 = 30$。

【数据规模】

对于 $30\%$的数据， $N \leq 1,000$。

对于 $100\%$的数据， $1 \leq N \leq 100,000$， $1 \leq D_i, U_i, P_i, M_i,C_i \leq  10,000$。


---

---
title: "[WC2007] 剪刀石头布"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4249
tag: ['图论', '2007', 'Special Judge', 'O2优化', '图论建模', '费用流', '差分', 'WC']
---
# [WC2007] 剪刀石头布
## 题目描述

在一些一对一游戏的比赛（如下棋、乒乓球和羽毛球的单打）中，我们经常会遇到 $A$ 胜过 $B$，$B$ 胜过 $C$ 而 $C$ 又胜过 $A$ 的有趣情况，不妨形象的称之为剪刀石头布情况。有的时候，无聊的人们会津津乐道于统计有多少这样的剪刀石头布情况发生，即有多少对无序三元组 $(A,B,C)$，满足其中的一个人在比赛中赢了另一个人，另一个人赢了第三个人而第三个人又胜过了第一个人。注意这里无序的意思是说三元组中元素的顺序并不重要，将 $(A, B, C)$、$(A, C, B)$、$(B, A, C)$、$(B, C, A)$、$(C, A, B)$ 和 $(C, B, A)$ 视为相同的情况。

有 $N$ 个人参加一场这样的游戏的比赛，赛程规定任意两个人之间都要进行一场比赛：这样总共有 $\frac{N*(N-1)}{2}$ 场比赛。比赛已经进行了一部分，我们想知道在极端情况下，比赛结束后最多会发生多少剪刀石头布情况。即给出已经发生的比赛结果，而你可以任意安排剩下的比赛的结果，以得到尽量多的剪刀石头布情况。

## 输入格式

输入文件的第 $1$ 行是一个整数 $N$，表示参加比赛的人数。

之后是一个 $N$ 行 $N$ 列的数字矩阵：一共 $N$ 行，每行 $N$ 列，数字间用空格隔开。

在第 $(i+1)$ 行的第 $j$ 列的数字如果是 $1$，则表示 $i$ 在已经发生的比赛中赢了 $j$；该数字若是 $0$，则表示在已经发生的比赛中 $i$ 败于 $j$；该数字是
 $2$，表示 $i$ 和 $j$ 之间的比赛尚未发生。数字矩阵对角线上的数字，即第 $(i+1)$ 行第 $i$ 列的数字都是 $0$，它们仅仅是占位符号，没有任何意义。

输入文件保证合法，不会发生矛盾，当 $i \neq j$ 时，第 $(i+1)$ 行第 $j$ 列和第 $(j+1)$ 行第 $i$ 列的两个数字要么都是 $2$，要么一个是 $0$ 一个是 $1$。

## 输出格式

输出文件的第 $1$ 行是一个整数，表示在你安排的比赛结果中，出现了多少剪刀石头布情况。

输出文件的第 $2$  行开始有一个和输入文件中格式相同的 $N$ 行 $N$ 列的数字矩阵。第 $(i+1)$ 行第 $j$ 个数字描述了 $i$ 和 $j$ 之间的比赛结果，$1$ 表示 $i$ 赢了 $j$，$0$ 表示 $i$ 负于 $j$，与输入矩阵不同的是，在这个矩阵中没有表示比赛尚未进行的数字 $2$；对角线上的数字都是 $0$。输出矩阵要保证合法，不能发生矛盾。

## 样例

### 样例输入 #1
```
3
0 1 2
0 0 2
2 2 0

```
### 样例输出 #1
```
1
0 1 0
0 0 1
1 0 0

```
## 提示

### 【评分标准】
对于每个测试点，仅当你的程序的输出第一行的数字和标准答案一致，且给出了一个与之一致的合法方案，你才能得到该测试点的满分，否则该测试点得 $0$ 分。
### 【数据范围】
$30\%$ 的数据中，$N \leq 6$；

$100\%$ 的数据中，$N \leq 100$。



---

---
title: "[ZJOI2011] 营救皮卡丘"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4542
tag: ['2011', '各省省选', '浙江', '图论建模', '最短路', '费用流']
---
# [ZJOI2011] 营救皮卡丘
## 题目描述

皮卡丘被火箭队用邪恶的计谋抢走了！这三个坏家伙还给小智留下了赤果果的挑衅！为了皮卡丘，也为了正义，小智和他的朋友们义不容辞的踏上了营救皮卡丘的道路。

火箭队一共有$N$个据点，据点之间存在$M$条双向道路。据点分别从$1$到$N$标号。小智一行$K$人从真新镇出发，营救被困在$N$号据点的皮卡丘。为了方便起见，我们将真新镇视为$0$号据点，一开始$K$个人都在$0$号点。

由于火箭队的重重布防，要想摧毁$K$号据点，必须按照顺序先摧毁$1$到$K-1$号据点，并且，如果$K-1$号据点没有被摧毁，由于防御的连锁性，小智一行任何一个人进入据点$K$，都会被发现，并产生严重后果。因此，在$K-1$号据点被摧毁之前，任何人是不能够经过$K$号据点的。

为了简化问题，我们忽略战斗环节，小智一行任何一个人经过$K$号据点即认为$K$号据点被摧毁。被摧毁的据点依然是可以被经过的。

$K$个人是可以分头行动的，只要有任何一个人在$K-1$号据点被摧毁之后，经过$K$号据点，$K$号据点就被摧毁了。显然的，只要$N$号据点被摧毁，皮卡丘就得救了。

野外的道路是不安全的，因此小智一行希望在摧毁$N$号据点救出皮卡丘的同时，使得$K$个人所经过的道路的长度总和最少。

请你帮助小智设计一个最佳的营救方案吧！
## 输入格式

第一行包含三个正整数$N,M,K$。表示一共有$N+1$个据点，分别从$0$到$N$编号，以及$M$条无向边。一开始小智一行共$K$个人均位于$0$号点。 

接下来$M$行，每行三个非负整数，第i行的整数为$A_i$，$B_i$，$L_i$。表示存在一条从$A_i$号据点到$B_i$号据点的长度为$L_i$的道路。
## 输出格式

仅包含一个整数$S$，为营救皮卡丘所需要经过的最小的道路总和。
## 样例

### 样例输入 #1
```
3 4 2
0 1 1
1 2 1
2 3 100
0 3 1
```
### 样例输出 #1
```
3
```
## 提示

【样例说明】

小智和小霞一起前去营救皮卡丘。在最优方案中，小智先从真新镇前往1号点，接着前往2号据点。当小智成功摧毁2号据点之后，小霞从真新镇出发直接前往3号据点，救出皮卡丘。

对于100%的数据满足$N ≤ 150, M ≤ 20 000, 1 ≤ K ≤ 10, L_i ≤ 10 000$, 保证小智一行一定能够救出皮卡丘。

至于为什么$K ≤ 10$，你可以认为最终在小智的号召下，小智，小霞，小刚，小建，小遥，小胜，小光，艾莉丝，天桐，还有去日本旅游的黑猫警长，一同前去大战火箭队。


---

---
title: "[NOI2019] 序列"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5470
tag: ['贪心', '2019', 'NOI', 'O2优化', '优先队列', '模拟费用流']
---
# [NOI2019] 序列
## 题目描述

给定两个长度为 $n$ 的正整数序列 $\{a_i\}$ 与 $\{b_i\}$，序列的下标为 $1, 2, \cdots , n$。现在你需要分别对两个序列各指定**恰好** $K$ 个下标，要求**至少**有 $L$ 个下标在两个序列中都被指定，使得这 $2K$ 个下标在序列中对应的元素的总和**最大**。

形式化地说，你需要确定两个长度为 $K$ 的序列 $\{c_i\}, \{d_i\}$，其中
$1 \leq c_1 < c_2 < \cdots < c_K \leq n , 1 \leq d_1 < d_2 < \cdots < d_K \leq n$

并要求 $\{c_1, c_2, \cdots , c_K\} \cap \{d_1, d_2, · · · , d_K\}\geq L$

目标是最大化 $\sum^{K}_{i=1} a_{c_i} +\sum^{K}_{i=1} b_{d_i}$

## 输入格式

**本题输入文件包含多组数据**。

第一行一个正整数 $T$ 表示数据组数。接下来每三行表示一组数据。

每组数据第一行三个整数 $n, K, L$，变量意义见题目描述。

每组数据第二行 $n$ 个整数表示序列 $\{a_i\}$。

每组数据第三行 $n$ 个整数表示序列 $\{b_i\}$。
## 输出格式

对于每组数据输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
5
1 1 1
7
7
3 2 1
4 1 2
1 4 2
5 2 1
4 5 5 8 4
2 1 7 2 7
6 4 1
1 5 8 3 2 4
2 6 9 3 1 7
7 5 4
1 6 6 6 5 9 1
9 5 3 9 1 4 2
```
### 样例输出 #1
```
14
12
27
45
62

```
## 提示

### 更多样例

您可以通过附加文件获得更多样例。

#### 样例 2

见选手目录下的 `sequence/sequence2.in` 与 `sequence/sequence2.ans`。

#### 样例 3

见选手目录下的 `sequence/sequence3.in` 与 `sequence/sequence3.ans`。

### 样例 1 解释

第一组数据选择的下标为：$\{c_i\} = \{1\} , \{d_i\} = \{1\}$。

第二组数据选择的下标为：$\{c_i\} = \{1, 3\} , \{d_i\} = \{2, 3\}$

第三组数据选择的下标为：$\{c_i\} = \{3, 4\} , \{d_i\} = \{3, 5\}$。

第四组数据选择的下标为：$\{c_i\} = \{2, 3, 4, 6\} , \{d_i\} = \{2, 3, 4, 6\}$。

第五组数据选择的下标为：$\{c_i\} = \{2, 3, 4, 5, 6\} , \{d_i\} = \{1, 2, 3, 4, 6\}$。

### 数据范围

对于所有测试点：$T \leq 10 , 1 \leq \sum n \leq 10^6, 1 \leq L \leq K \leq n \leq 2 \times 10^5, 1 \leq a_i, b_i \leq 10^9$。

| 测试点编号 | $n\le$ | $\sum n \le$ |
| :----------: | :----------: | :----------: |
| $1\sim3$ | $10$ | $3\times 10^5$ |
| $4\sim5$ | $18$ | $3\times 10^5$ |
| $6\sim7$ | $30$ | $3\times 10^5$ |
| $8\sim10$ | $150$ | $3\times 10^5$ |
| $11\sim16$ | $2\times 10^3$ | $3\times 10^5$ |
| $17\sim21$ | $2\times 10^5$ | $3\times 10^5$ |
| $22\sim25$ | $2\times 10^5$ | $10^6$ |


---

---
title: "[THUWC 2017] 大葱的神力"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6849
tag: ['动态规划 DP', '搜索', '2017', '提交答案', 'Special Judge', '剪枝', '模拟退火', '背包 DP', '费用流', '随机化', 'THUWC']
---
# [THUWC 2017] 大葱的神力
## 题目背景

**本题为提交答案题。**

大葱是我国自古以来的美食，像我国传统美食北京烤鸭，用鸭子点缀出大葱的香味，令人赞不绝口。民间也流传着有「每天一棵葱，不当单身狗」的说法。

然而，大葱要发挥出独属于自己的神力，也是有条件的。
## 题目描述

现在小葱同学有 $N$ 棵大葱和 $M$ 个抽屉，将第 $i$ 棵大葱放到第 $j$ 个抽屉里面会产生 $w_{i,j}$ 的神力。自然小葱同学希望获得尽量多的神力，但是抽屉有着容积的限制，大葱也有着自己的体积。第 $i$ 棵大葱的体积为 $a_i$，第 $j$ 个抽屉的容积为 $b_j$。一个抽屉里面装着的大葱的体积之和不能超过这个抽屉的容积，一棵大葱不能拆分放到两个抽屉中。

小葱同学现在想知道，在这样的条件下，这些大葱最多会产生多少的神力？
## 输入格式

**本题为提交答案题**，输入文件为 `drawer1.in ~ drawer10.in`，详见附加文件。

第一行两个整数 $N,M$，代表大葱的个数和抽屉的个数。

接下来一行 $N$ 个整数，代表每棵大葱的体积。

接下来一行 $M$ 个整数，代表每个抽屉的容积。

接下来 $N$ 行每行 $M$ 个整数，第 $i$ 行第 $j$ 个数代表第 $i$ 棵大葱放到第 $j$ 个抽屉中会产生的神力。
## 输出格式

输出文件为 `drawer1.out ~ drawer10.out`，分别对应相应的输入文件。

对于每组输入数据，输出 $N$ 行每行一个整数，第 $i$ 个数代表第 $i$ 棵大葱被放到了哪个抽屉里面。如果第 $i$ 棵大葱没有被放到任何一个抽屉里面，则输出 $0$。
## 样例

### 样例输入 #1
```
3 4
1 1 2
2 1 2 3
1 2 1 1
2 1 2 1
3 1 0 1
```
### 样例输出 #1
```
2
0
1
```
## 提示

#### 样例说明

样例只是一种合法情况，获得的总神力值为 $2+3=5$。

#### 评分方式

**本题使用 Special Judge**，对于每个测试点，我们都有 $10$ 个参数 $a_1,a_2,\cdots,a_{10}$，如果你的输出所产生的的神力 $v$ 满足 $v \ge a_i$，则我们保证该测试点你至少会得到 $i$ 分。

#### 如何测试你的输出

在附加文件中，我们提供了 `scorer.cpp`，请自行编译来测试输出，这个程序将用于评判你的输出能够产生多少的神力。

若编译后文件名称为 `scorer`，在终端（Linux）中，输入以下命令：

```plain
./scorer <input_name> <output_name>
```

或在命令提示符（Windows）中，输入以下命令：
```plain
scorer <input_name> <output_name>
```
来对你的输出进行评判。其中 `<input_name>` 为输入文件名称，`<output_name>` 为输出文件名称。


---

