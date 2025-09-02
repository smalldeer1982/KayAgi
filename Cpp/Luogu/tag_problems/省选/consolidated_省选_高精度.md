---
title: "血缘关系"
layout: "post"
diff: 省选/NOI-
pid: P1235
tag: ['动态规划 DP', '高精度']
---
# 血缘关系
## 题目描述

我们正在研究妖怪家族的血缘关系。每个妖怪都有相同数量的基因，但是不同的妖怪的基因可能是不同的。我们希望知道任意给定的两个妖怪之间究竟有多少相同的基因。由于基因数量相当庞大，直接检测是行不通的。但是，我们知道妖怪家族的家谱，所以我们可以根据家谱来估算两个妖怪之间相同基因的数量。

妖怪之间的基因继承关系相当简单：如果妖怪 $C$ 是妖怪 $A$ 和 $B$ 的孩子，则 $C$ 的任意一个基因只能是继承 $A$ 或 $B$ 的基因，继承 $A$ 或 $B$ 的概率各占 $50\%$。所有基因可认为是相互独立的，每个基因的继承关系不受别的基因影响。

现在，我们来定义两个妖怪 $X$ 和 $Y$ 的基因相似程度。例如，有一个家族，这个家族中有两个毫无关系（没有相同基因）的妖怪 $A$ 和 $B$，及它们的孩子 $C$ 和 $D$。那么 $C$ 和 $D$ 相似程度是多少呢？因为 $C$ 和 $D$ 的基因都来自 $A$ 和 $B$，从概率来说，各占 $50\%$。所以，依概率计算 $C$ 和 $D$ 平均有 $50\%$ 的相同基因，$C$ 和 $D$ 的基因相似程度为 $50\%$。需要注意的是，如果 $A$ 和 $B$ 之间存在相同基因的话，$C$ 和 $D$ 的基因相似程度就不再是 $50\%$ 了。

你的任务是写一个程序，对于给定的家谱以及成对出现的妖怪，计算它们之间的基因相似程度。
## 输入格式

第一行两个整数 $n\ (2 \le n \le 300)$ 和 $k$。表示家族中成员数，它们分别用 $1,2,\cdots,n$ 来表示。$k\ (0 \le k \le n-2)$ 表示这个家族中有父母的妖怪数量（其他的妖怪没有父母，它们之间可以认为毫无关系，即没有任何相同基因）。

接下来的 $k$ 行，每行三个整数 $a,b,c$，表示妖怪 $a$ 是妖怪 $b$ 的孩子。

然后是一行一个整数 $m$（$1 \le m \le n_2$），表示需要计算基因相似程度的妖怪对数。

接下来的 $m$ 行，每行两个整数，表示需要计算基因相似程度的两个妖怪。

你可以认为这里给出的家谱总是合法的。具体来说就是，没有任何的妖怪会成为自己的祖先，并且你也不必担心会存在性别错乱问题。
## 输出格式

共 $m$ 行。可 $k$ 行表示第 $k$ 对妖怪之间的基因相似程度。你必须按百分比输出，有多少精度就输出多少，而且必须准确，但不允许出现多余的 $0$（注意，$0.001$ 的情况应输出 $\verb!0.1%!$，而不是 $\verb!.1%!$）。具体格式参见样例。
## 样例

### 样例输入 #1
```
7 4                                                    

4 1 2                                          

5 2 3                                          

6 4 5                                          

7 5 6

4

1 2

2 6

7 5

3 3


```
### 样例输出 #1
```
0%

50%

81.25%

100%


```


---

---
title: "[GCJ 2021 Finals] Cutting Cake"
layout: "post"
diff: 省选/NOI-
pid: P13043
tag: ['数学', '高精度', '2021', '扫描线', 'Google Code Jam']
---
# [GCJ 2021 Finals] Cutting Cake
## 题目描述

Today is your and your twin sibling's birthday. To celebrate, you got a rectangular cake to share. The cake is decorated with $\mathbf{N}$ triangular patches of icing (which may overlap). All the icing patches were created with the same triangular mold, so they have the same shape and orientation. Although you and your twin are very similar, your tastes in icing are much different. This difference is formalized by each of you having a different enjoyment value for each patch of icing. Specifically, your enjoyment value for eating the entire $i$-th patch of icing is $\mathbf{A}_i$, and your twin's is $\mathbf{B}_i$. If someone eats part of a patch, they get enjoyment proportional to the eaten area. For example, if you eat $\frac{2}{3}$ of the area of the $i$-th icing patch, you would get $\frac{2\mathbf{A}_i}{3}$ enjoyment from it. Note that there may be some flavors of icing that you or your twin do not enjoy, so the $\mathbf{A}_i$ and/or $\mathbf{B}_i$ values can be negative.

![](https://cdn.luogu.com.cn/upload/image_hosting/bb02prmd.png)

You will cut the cake into two rectangular pieces by making a single vertical cut (parallel to the Y-axis). After cutting the cake, you will eat the left piece and your twin will eat the right piece. Your total enjoyment is the sum of the enjoyment you get from all icing to the left of the cut. Similarly, your twin's enjoyment is the sum of the enjoyment they get from all icing to the right of the cut.

To be as fair as possible, you want to cut the cake such that the absolute value of the difference between your total enjoyment and your twin's total enjoyment is as small as possible. Given the $\mathbf{N}$ triangular icing patches on a rectangular cake, what is the minimum possible absolute value of the difference between your and your twin's total enjoyments you can get?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing three positive integers, $\mathbf{N}$, $\mathbf{W}$, and $\mathbf{H}$, representing the number of icing patches on the cake and the width and height of the top of the cake, respectively. The bottom-left corner of the cake is located at $(0,0)$ and the top-right corner is at $(\mathbf{W}, \mathbf{H})$. Then, a line describing the icing patch mold follows. This line contains four integers: $\mathbf{P}$, $\mathbf{Q}$, $\mathbf{R}$, and $\mathbf{S}$. The icing patch mold is a triangle with vertices at $(0,0)$, $(\mathbf{P}, \mathbf{Q})$, and $(\mathbf{R}, \mathbf{S})$. Then, $\mathbf{N}$ lines follow. The $i$-th of these lines contains four integers $\mathbf{X}_i$, $\mathbf{Y}_i$, $\mathbf{A}_i$, and $\mathbf{B}_i$. The $i$-th patch is a triangle with vertices at $(\mathbf{X}_i, \mathbf{Y}_i)$, $(\mathbf{X}_i + \mathbf{P}, \mathbf{Y}_i + \mathbf{Q})$, and $(\mathbf{X}_i + \mathbf{R}, \mathbf{Y}_i + \mathbf{S})$. You would get $\mathbf{A}_i$ enjoyment from eating it and your twin would get $\mathbf{B}_i$ enjoyment.
## 输出格式

For each test case, output one line containing `Case #x: y/z`, where $x$ is the test case number (starting from 1) and $\frac{y}{z}$ is the minimum absolute value of the difference between your and your twin's total enjoyment that can be achieved with a single vertical cut as an irreducible fraction (that is, $z$ must be positive and of minimum possible value).
## 样例

### 样例输入 #1
```
4
1 5 5
3 -1 2 2
1 2 -10 5
2 100000000 50000000
80000000 0 40000000 40000000
5000001 2500000 500 -501
15000000 5000000 501 -400
2 10 10
0 2 4 2
2 2 -4 5
4 6 -6 5
3 622460462 608203753
486076103 36373156 502082214 284367873
98895371 126167607 823055173 -740793281
26430289 116311281 -398612375 -223683435
46950301 278229490 766767410 -550292032
```
### 样例输出 #1
```
Case #1: 5/1
Case #2: 288309900002019999899/320000000000000000
Case #3: 37/4
Case #4: 216757935773010988373334129808263414106891/187470029508637421883991794137967
```
## 提示

**Sample Explanation**

In Sample Case #1, there is a single icing patch. The optimal cut is to the left of the patch. You will eat no icing and receive 0 enjoyment. Your twin will eat all of the icing patch and receive 5 enjoyment from it. The absolute value of the difference between your and your twin's enjoyments is $|0 - 5| = 5$.

![](https://cdn.luogu.com.cn/upload/image_hosting/0l7tbto8.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/nfrgziry.png)

In Sample Case #2, there are two icing patches. The optimal cut is at $X = 15099999.99$. Notice that the numerator and denominator of the answer can get very large.

![](https://cdn.luogu.com.cn/upload/image_hosting/wer6hjfq.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/bjelfqv7.png)

In Sample Case #3, there are two icing patches. The optimal cut is at $X = 4$. You will eat 75% of the first icing patch and receive $-3$ enjoyment from it. Your twin will eat 25% of the first icing patch and all of the second icing patch getting $5 \cdot 0.25 + 5 = 6.25$ enjoyment. The absolute value of the difference between your and your twin's enjoyments is $|-3 - 6.25| = 9.25 = \frac{37}{4}$.

Notice that cutting at $X = 1$ would give you $0$ enjoyment and your twin $10$ enjoyment. While both of those values are greater than the corresponding enjoyment when cutting at $X = 4$, the difference between them is $10 > 9.25$, which means cutting at $X = 4$ is preferable anyway.

![](https://cdn.luogu.com.cn/upload/image_hosting/x0dpaoy4.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/kgtk2lkh.png)

In Sample Case #4, there are three icing patches. The optimal cut is at $X \approx 521241077.6027$.

**Test Set 1 (20 Pts, Visible Verdict)**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{N} \leq 100$.
- $3 \leq \mathbf{W} \leq 10^{9}$.
- $3 \leq \mathbf{H} \leq 10^{9}$.
- $-10^{9} \leq \mathbf{A}_{i} \leq 10^{9}$, for all $i$.
- $-10^{9} \leq \mathbf{B}_{i} \leq 10^{9}$, for all $i$.
- $0 \leq \mathbf{P} \leq 10^{9}$.
- $-10^{9} \leq \mathbf{Q} \leq 10^{9}$.
- $0 \leq \mathbf{R} \leq 10^{9}$.
- $-10^{9} \leq \mathbf{S} \leq 10^{9}$.
- The three vertices of the mold $(0, 0)$, $(\mathbf{P}, \mathbf{Q})$, and $(\mathbf{R}, \mathbf{S})$ are not collinear.
- The three vertices of each triangular icing patch are strictly inside the cake's borders. Formally:
  - $1 \leq \mathbf{X}_{i} \leq \mathbf{W} - \max(\mathbf{P}, \mathbf{R}) - 1$, for all $i$, and
  - $\max(0, -\mathbf{Q}, -\mathbf{S}) + 1 \leq \mathbf{Y}_{i} \leq \mathbf{H} - \max(0, \mathbf{Q}, \mathbf{S}) - 1$, for all $i$.



---

---
title: "[CEOI 2007] 树的匹配 Treasury"
layout: "post"
diff: 省选/NOI-
pid: P1623
tag: ['动态规划 DP', '高精度', '树形数据结构', '2007', 'CEOI（中欧）']
---
# [CEOI 2007] 树的匹配 Treasury
## 题目描述

给一棵树，你可以匹配有边相连的两个点，问你这棵树的最大匹配是多少，并且计算出有多少种最大匹配。
## 输入格式

第一行一个整数 $N$，表示有多少个结点。

接下来 $N$ 行，每行第一个整数，表示要描述的那个结点。然后一个整数 $m$，表示这个结点有 $m$ 个儿子，接下来 $m$ 个整数，表示它的 $m$   个儿子的编号。
## 输出格式

输出两行，第一行输出最大匹配数，第二行输出最大匹配方案数。

## 样例

### 样例输入 #1
```
7
1 3 2 4 7
2 1 3
4 1 6
3 0
7 1 5
5 0
6 0
```
### 样例输出 #1
```
3
4
```
## 提示

$1\leq N\leq 10^3$，其中 $40\%$ 的数据答案不超过 $10^8$。


---

---
title: "【模板】高精度乘法 | A*B Problem 升级版"
layout: "post"
diff: 省选/NOI-
pid: P1919
tag: ['高精度', 'O2优化', '分治', '快速傅里叶变换 FFT']
---
# 【模板】高精度乘法 | A*B Problem 升级版
## 题目背景

本题数据已加强，请使用 FFT 或分治乘法。
## 题目描述

给你两个正整数 $a,b$，求 $a \times b$。
## 输入格式

第一行一个正整数，表示 $a$；  
第二行一个正整数，表示 $b$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
83517934
327830610

```
### 样例输出 #1
```
27379735249159740

```
## 提示

【数据范围】   
$1\le a,b \le 10^{1000000}$

可能需要一定程度的常数优化。  
数据由 NaCly_Fish 重造


---

---
title: "拯救世界"
layout: "post"
diff: 省选/NOI-
pid: P2000
tag: ['数学', '高精度', 'O2优化']
---
# 拯救世界
## 题目背景

公元 2000 年，根据预言家诺查丹玛斯的预言，世界就要毁灭了！！！

## 题目描述

为了拯救世界，小 a 和 uim 决定召唤出 kkksc03 大神和 lzn 大神。根据古籍记载，召唤出任何一位大神，都需要使用金木水火土五种五行神石来摆一个特定的大阵。而在古籍中，记载是这样的：

kkksc03 大神召唤方法：

- 金神石的块数必须是 $6$ 的倍数；
- 木神石最多用 $9$ 块；
- 水神石最多用 $5$ 块；
- 火神石的块数必须是 $4$ 的倍数；
- 土神石最多用 $7$ 块。

lzn 大神召唤方法:

- 金神石的块数必须是 $2$ 的倍数；
- 木神石最多用 $1$ 块；
- 水神石的块数必须是 $8$ 的倍数；
- 火神石的块数必须是 $10$ 的倍数；
- 土神石最多用 $3$ 块。

现在是公元 $1999$ 年 $12$ 月 $31$ 日，小 a 和 uim 从 $00{:}00{:}00$ 开始找，一直找到 $23{:}00{:}00$，终于，还是没找到神石。

不过，他们在回到家后在自家地窖里发现了一些奇怪的东西，一查古籍，哎呦妈呀，怎么不早点来呢？这里有一些混沌之石，可以通过敲击而衰变成五行神石。于是，他们拼命地敲，终于敲出了 $n$ 块神石，在 $23{:}59{:}59$ 完成了两座大阵。

然而，kkksc03 大神和 lzn 大神确实出现了，但是由于能量不够，无法发挥神力。只有把所有用 $n$ 块神石可能摆出的大阵都摆出来，才能给他们充满能量。这下小 a 和 uim 傻了眼了，赶快联系上了你，让你帮忙算一下，一共有多少种大阵。

## 输入格式

输入一个正整数 $n$。

## 输出格式

输出用 $n$ 块混沌之石能摆出的大阵的种数。

## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
15
```
## 提示

### 数据范围及约定

对于全部数据，$10^{99999}\leq n\lt 10^{100000}$。

### 提示

由于现在已经是 $23{:}59{:}59$，所以你只有 $0.5$ 秒时间。（小 a 与 uim 需要 $0.5\texttt s$ 排出所有阵法）。



---

---
title: "[FJOI2007] 轮状病毒"
layout: "post"
diff: 省选/NOI-
pid: P2144
tag: ['动态规划 DP', '高精度', '递推', '2007', '各省省选', '福建']
---
# [FJOI2007] 轮状病毒
## 题目描述

轮状病毒有很多变种。许多轮状病毒都是由一个轮状基产生。一个 $n$ 轮状基由圆环上 $n$ 个不同的基原子和圆心的一个核原子构成。$2$ 个原子之间的边表示这 $2$ 个原子之间的信息通道，如图 1 所示。

$n$ 轮状病毒的产生规律是在 $n$ 轮状基中删除若干边，使各原子之间有唯一一条信息通道。例如，共有 $16$ 个不同的 $3$ 轮状病毒，如图 2 所示。

给定 $n\ (n\le100)$，编程计算有多少个不同的 $n$ 轮状病毒。

![](https://cdn.luogu.com.cn/upload/pic/1408.png)

## 输入格式

第一行有 $1$ 个正整数 $n$。

## 输出格式

共 $1$ 行，表示不同的 $n$ 轮状病毒数。

## 样例

### 样例输入 #1
```
3

```
### 样例输出 #1
```
16
```


---

---
title: "[HNOI2002] Kathy函数"
layout: "post"
diff: 省选/NOI-
pid: P2235
tag: ['动态规划 DP', '高精度', '2002', '各省省选', '湖南', '数位 DP']
---
# [HNOI2002] Kathy函数
## 题目描述

Tiger 非常喜欢数学，所以他参加了学校组织的数学课外兴趣小组。在兴趣小组的学习当中，老师向 Tiger 介绍了 Kathy 函数，Kathy 函数是这样定义的：

$$
\left\{
\begin{aligned}
&f(1)=1\\
&f(3)=3\\
&f(2n)=f(n)\\
&f(4n+1)=2f(2n+1)-f(n)\\
&f(4n+3)=3f(2n+1)-2f(n)
\end{aligned}
\right.
$$

Tiger 对 Kathy 函数产生了浓厚的兴趣，他通过研究发现有很多的数 $n$ 都满足 $f(n)=n$。

对于一个给定的数 $m$，他希望你求出所有的满足 $f(n)=n$ 的正整数 $n$ 的个数，其中 $n\leq m$。
## 输入格式

输入只有一行一个整数，表示 $m$。
## 输出格式

输出一行一个整数，表示 $n$。
## 样例

### 样例输入 #1
```
5
```
### 样例输出 #1
```
3
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq m \leq 10^{100}$。


---

---
title: "[HNOI2004] 高精度开根"
layout: "post"
diff: 省选/NOI-
pid: P2293
tag: ['高精度', '2004', '各省省选', '湖南', 'O2优化']
---
# [HNOI2004] 高精度开根
## 题目描述

晓华所在的工作组正在编写一套高精度科学计算的软件，一些简单的部分如高精度加减法、乘除法早已写完了，现在就剩下晓华所负责的部分：实数的高精度开m次根。

因为一个有理数开根之后可能得到一个无理数，所以这项工作是有较大难度的。现在要做的只是这项工作的第一步：只对自然数进行开整数次根，求出它的一个非负根，并且不考虑结果的小数部分，只要求把结果截断取整即可。

程序需要根据给定的输入，包括需要开根的次数，以及被开根的整数；计算出它的非负根取整后的结果。

## 输入格式

输入文件共有两行，每行都有一个整数，并且输入中没有多余的空格：

第一行有一个正整数m (1 <= m <= 50)，表示要开的根次；

第二行有一个整数n (0<=n <= 10^10000)，表示被开根的数。

## 输出格式

输出文件只有一行，包括一个数，即为开根取整后的结果。

## 样例

### 样例输入 #1
```
3
1000000000

```
### 样例输出 #1
```
1000
```


---

---
title: "non天平"
layout: "post"
diff: 省选/NOI-
pid: P2405
tag: ['动态规划 DP', '数学', '高精度', '线段树', '洛谷原创', '进制']
---
# non天平
## 题目背景

non 最近正在为自己的体重而苦恼，他想称量自己的体重。于是，他找来一个天平与许多砝码。
## 题目描述

砝码的重量均是 $n$ 的幂次，$n^1, n^2, n^3, n^4, n^5$ 的……non 想知道至少要多少个砝码才可以称出他的重量 $m$。注意砝码可以放左边，也可以放右边。
## 输入格式

第一行一个正整数 $m$，表示 non 的重量；

第二行一个正整数 $n$，表示砝码重量幂次的底。
## 输出格式

一个整数表示最少所需的砝码数。

## 样例

### 样例输入 #1
```
99

10


```
### 样例输出 #1
```
2
```
## 提示

### 数据范围及约定

对于 $30\%$ 的数据点，$m \le 2^{63}-1$。

对于 $100\%$ 的数据点，$0 \le m \le 10^{10000}$，$0<n \le 10000$。


---

---
title: "[ZJOI2012] 数列"
layout: "post"
diff: 省选/NOI-
pid: P2609
tag: ['数学', '高精度', '2012', '各省省选', '递归', '浙江']
---
# [ZJOI2012] 数列
## 题目描述

小白和小蓝在一起上数学课，下课后老师留了一道作业，求下面这个数列的通项公式：

$$a_0=0,a_1=1,a_{2i}=a_i,a_{2i+1}=a_i+a_{i+1}$$

小白作为一个数学爱好者，很快就计算出了这个数列的通项公式。于是，小白告诉小蓝自己已经做出来了，但为了防止小蓝抄作业，小白并不想把公式公布出来。于是小白为了向小蓝证明自己的确做出来了此题以达到其炫耀的目的，想出了一个绝妙的方法：即让小蓝说一个正整数 $n$，小白则说出 $a_n$ 的值，如果当 $n$ 很大时小白仍能很快的说出正确答案，这就说明小白的确得到了公式。但这个方法有一个很大的漏洞：小蓝自己不会做，没法验证小白的答案是否正确。作为小蓝的好友，你能帮帮小蓝吗？
## 输入格式

输入文件第一行有且只有一个正整数 $T$，表示测试数据的组数。

接下来 $T$ 行，每行一个整数 $n$。
## 输出格式

对于每组数据：输出一行一个整数代表 $a_n$。
## 样例

### 样例输入 #1
```
3
1
3
10

```
### 样例输出 #1
```
1
2
3

```
## 提示

- 对于 $20\%$ 的数据，$1 \le n \le 10^8$。 
- 对于 $50\%$ 的数据，$1 \le n \le 10^{12}$。
- 对于 $100\%$ 的数据，$1 \le T \le 20$，$1 \le n \le 10^{100}$。


---

---
title: "[NOI2017] 整数"
layout: "post"
diff: 省选/NOI-
pid: P3822
tag: ['高精度', '2017', '线段树', 'NOI', 'O2优化', '进制']
---
# [NOI2017] 整数
## 题目背景

在人类智慧的山巅，有着一台字长为 $1\,048\,576$ 位（此数字与解题无关）的超级计算机，著名理论计算机科学家 P 博士正用它进行各种研究。不幸的是，这天台风切断了电力系统，超级计算机无法工作，而 P 博士明天就要交实验结果了，只好求助于学过 OI 的你...

## 题目描述

P 博士将他的计算任务抽象为对一个整数的操作。

具体来说，有一个整数 $x$，一开始为 $0$。

接下来有 $n$ 个操作，每个操作都是以下两种类型中的一种：

- `1 a b`：将 $x$ 加上整数 $a\cdot 2^b$，其中 $a$ 为一个整数，$b$ 为一个非负整数

- `2 k` ：询问 $x$ 在用二进制表示时，位权为 $2^k$ 的位的值（即这一位上的 $1$ 代表 $2^k$）

保证在任何时候，$x\geqslant 0$。
## 输入格式

输入的第一行包含四个正整数 $n,t_1,t_2,t_3$，$n$ 的含义见题目描述，$t_1$，$t_2$，$t_3$ 的具体含义见子任务。

接下来 $n$ 行，每行给出一个操作，具体格式和含义见题目描述。
## 输出格式

对于每个询问操作，输出一行，表示该询问的答案（$0$ 或 $1$）。对于加法操作，没有任何输出。

## 样例

### 样例输入 #1
```
10 3 1 2
1 100 0
1 2333 0
1 -233 0
2 5
2 7
2 15
1 5 15
2 15
1 -1 12
2 15
```
### 样例输出 #1
```
0
1
0
1
0
```
## 提示

在所有测试点中，$1\leqslant t_1 \leqslant 3, 1 \leqslant t_2 \leqslant 4, 1 \leqslant t_3 \leqslant 2$。不同的 $t_1, t_2, t_3$ 对应的特殊限制如下：

- 对于 $t_1 = 1$ 的测试点，满足 $a = 1$；
- 对于 $t_1 = 2$ 的测试点，满足 $|a| = 1$；
- 对于 $t_1 = 3$ 的测试点，满足 $|a| \leqslant 10^9$；
- 对于 $t_2 = 1$ 的测试点，满足 $0 \leqslant b, k \leqslant 30$；
- 对于 $t_2 = 2$ 的测试点，满足 $0 \leqslant b, k \leqslant 100$；
- 对于 $t_2 = 3$ 的测试点，满足 $0 \leqslant b, k \leqslant n$；
- 对于 $t_2 = 4$ 的测试点，满足 $0 \leqslant b, k \leqslant 30n$；
- 对于 $t_3 = 1$ 的测试点，保证所有询问操作都在所有修改操作之后；
- 对于 $t_3 = 2$ 的测试点，不保证询问操作和修改操作的先后顺序。

本题共 25 个测试点，每个测试点 4 分。各个测试点的数据范围如下：

| 测试点编号 | $n \le$ | $t_1$ | $t_2$ | $t_3$ |
|:-:|:-:|:-:|:-:|:-:|
| $1$ | $10$ | $3$ | $1$ | $2$ |
| $2$ | $100$ | $3$ | $2$ | $2$ |
| $3$ | $2000$ | $3$ | $2$ | $2$ |
| $4$ | $4000$ | $1$ | $3$ | $2$ |
| $5$ | $6000$ | $3$ | $3$ | $1$ |
| $6$ | $8000$ | $2$ | $3$ | $2$ |
| $7$ | $9000$ | $3$ | $4$ | $2$ |
| $8$ | $10000$ | $3$ | $3$ | $2$ |
| $9$ | $30000$ | $3$ | $4$ | $2$ |
| $10$ | $50000$ | $3$ | $4$ | $1$ |
| $11$ | $60000$ | $3$ | $3$ | $2$ |
| $12$ | $65000$ | $2$ | $4$ | $2$ |
| $13$ | $70000$ | $3$ | $4$ | $2$ |
| $14$ | $200000$ | $3$ | $4$ | $2$ |
| $15$ | $300000$ | $2$ | $4$ | $2$ |
| $16$ | $400000$ | $3$ | $4$ | $2$ |
| $17$ | $500000$ | $3$ | $3$ | $2$ |
| $18$ | $600000$ | $3$ | $4$ | $2$ |
| $19$ | $700000$ | $3$ | $4$ | $2$ |
| $20$ | $800000$ | $1$ | $4$ | $2$ |
| $21$ | $900000$ | $2$ | $4$ | $2$ |
| $22$ | $930000$ | $3$ | $3$ | $2$ |
| $23$ | $960000$ | $3$ | $4$ | $1$ |
| $24$ | $990000$ | $3$ | $3$ | $2$ |
| $25$ | $1000000$ | $3$ | $4$ | $2$ |


---

---
title: "中学数学题"
layout: "post"
diff: 省选/NOI-
pid: P3922
tag: ['数学', '高精度', '洛谷原创', '期望']
---
# 中学数学题
## 题目背景

琪露诺：我知道了！答案是-1 0，因为幻想乡没有传送器！

露米娅：真拿你没办法。。算了，再来一道中学数学题吧

说着，露米娅写下了一个数列

$ 1 , 2 , 4 , 8 , 16 , 32 , 64 , 128 , \cdots , 2048 , 4096 , 8192 , 16384 , \cdots $

## 题目描述

露米娅：这个数列的通项公式是 $ x_n = 2^{n-1} $

那么你来求一下前 $ k+1 $ 项中有多少个第一位为4吧（比如4096）


输入经过“加密”

详细输入方式见【输入格式】

## 输入格式

一行两个正整数，$ t $ 和 $ k_0 $

若 $ t = 1 $ 说明实际的k就是 $ k_0 $

若 $ t = 0 $ 说明实际的k是 $ 10^{k_0} $

## 输出格式

一个整数 $ ans $ ，表示有多少个数第一位为 4

## 样例

### 样例输入 #1
```
1 3

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
0 1

```
### 样例输出 #2
```
1

```
### 样例输入 #3
```
1 10

```
### 样例输出 #3
```
1

```
## 提示

对于30%的数据， $ k_0 \leq 10^7, t = 1 $

对于70%的数据， $ k_0 \leq 10^9, t = 1 $

对于另外30%的数据， $ k_0 \leq 233 , t = 0 $

对于100%的数据，$ k_0 \geq 1 $



---

---
title: "[SHOI2006] 仙人掌"
layout: "post"
diff: 省选/NOI-
pid: P4129
tag: ['动态规划 DP', '高精度', '2006', '各省省选', '上海', '仙人掌']
---
# [SHOI2006] 仙人掌
## 题目背景

#本题不同于bzoj1023
bzoj1023快捷通道：[[SHOI2008] cactus仙人掌图(II)](https://www.luogu.org/problemnew/show/P4244)
## 题目描述

仙人掌图（cactus）是一种无向连通图，它的每条边最多只能出现在一个简单回路（simple cycle）里面。从直观上说，可以把仙人掌图理解为允许存在回路的树。但是仙人掌图和树之间有个本质的不同，仙人掌图可以拥有多个支撑子图（spanning subgraph），而树的支撑子图只有一个（它自身），我们把仙人掌图的支撑子图的数目称为“仙人数”。你的任务就是计算给定图的“仙人数”。

一些关于仙人掌图的举例：

 ![](https://cdn.luogu.com.cn/upload/pic/13241.png) 

第一张图是一个仙人掌图，第二张图的边（2，3）在两个不同的回路里面，所以不是仙人掌图，第三张图不是一个连通图，所以也不是仙人掌图。


以下是对一些术语的解释：


简单回路（simple cycle）：简单回路是原图的一条路径，这条路径的边集构成了回路，回路中顶点只能出现一次。比如对于上例中第二个图来说，它一共有三个简单回路，分别是（4，3，2，1，6，5）、（7，8，9，10，2，3）和（4，3，7，8，9，10，2，1，6，5）


支撑子图（spanning subgraph）：支撑子图也是原图的子图，这种子图可以比原来少一些边，但是不能破坏图的连通性，也不能去除原来图上的任何顶点。“支撑”的概念类似于我们熟知的“最小支撑树”，对于上例中的第一张图来说，任意去除回路I中的图或回路II中的一条边都能构成一个支撑子图，所以它的支撑子图一共有6 + 4 + 6 × 4 + 1 = 35种（注意图自身也是自己的一个子图）

## 输入格式

输入文件的第一行是两个整数n和m（1≤n≤20000, 0≤m≤1000）。n代表图的顶点数，顶点的编号总是从1到n表示的。

接下来一共有m行。每行都代表了图上的一条路径（注意：这里所表示的一条路径可不一定是一条回路）。这些行的格式是首先有一个整数ki（2≤ki≤1000）代表这条路径通过了几个顶点，接下来是ki个在1到n之间的数字，其中每个数字代表了图上的一个顶点，相邻的顶点之间就定义了一条边。一条路径上可能通过一个顶点好几次，比如对于第一个例子，第一条路径从2经过3，又从8返回到了3，但是我们保证所有的边都会出现在某条路径上，而且不会重复出现在两条路径上，或者在一条路径上出现两次。

## 输出格式

输出这张图的“仙人数”，如果它不是一张仙人掌图，输出0。注意最后的答案可能是一个很大很大的数。

## 样例

### 样例输入 #1
```
14 3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
2 2 14
```
### 样例输出 #1
```
35
```
### 样例输入 #2
```
10 2
7 1 2 3 4 5 6 1
6 3 7 8 9 10 2
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
5 1
4 1 2 3 4
```
### 样例输出 #3
```
0
```


---

---
title: "[NOI2006] 神奇口袋"
layout: "post"
diff: 省选/NOI-
pid: P4204
tag: ['高精度', '2006', 'NOI', '排序']
---
# [NOI2006] 神奇口袋
## 题目描述

Pòlya 获得了一个奇妙的口袋，上面写着人类难以理解的符号。Pòlya 看得入了迷，冥思苦想，发现了一个神奇的模型（被后人称为 Pòlya 模型)。为了生动地讲授这个神奇的模型，他带着学生们做了一个虚拟游戏：游戏开始时，袋中装入 $a_1$ 个颜色为 $1$ 的球，$a_2$ 个颜色为 $2$ 的球，……，$a_t$ 个颜色为 $t$ 的球，其中 $a_i \in \mathbb Z^+$（$1 \le i \le t$）。

游戏开始后，每次严格进行如下的操作：

从袋中随机的抽出一个小球（袋中所有小球被抽中的概率相等），Pòlya 独自观察这个小球的颜色后将其放回，然后再把 $d$ 个与其颜色相同的小球放到口袋中。

设 $c_i$ 表示第 $i$ 次抽出的小球的颜色（$1 \le C_i \le t$），一个游戏过程将会产生一个颜色序列（$c_1, c_2, \ldots, c_n, \ldots$）。Pòlya 把游戏开始时 $t$ 种颜色的小球每一种的个数 $a_1, a_2, \ldots, a_t$ 告诉了所有学生。然后他问学生：一次游戏过程产生的颜色序列满足下列条件的概率有多大？ 

$$c_{x_1}=y_1, c_{x_2}=y_2, \ldots, c_{x_n}=y_n$$

其中 $0 < x_1 < x_2 < \cdots < x_n$，$1 \le y_i \le t$。换句话说，已知 $(t, n, d, a_1, a_2, \ldots, a_t, x_1, y_1, x_2, y_2, \ldots, x_n, y_n)$，你要回答有多大的可能性会发生下面的事件：“对所有 $k$（$1 \le k \le n$），第 $x_k$ 次抽出的球的颜色为 $y_k$”。
## 输入格式

第一行有三个正整数 $t, n, d$；

第二行有 $t$ 个正整数 $a_1, a_2, \ldots, a_t$，表示游戏开始时口袋里 $t$ 种颜色的球，每种球的个数。

以下 $n$ 行，每行有两个正整数 $x_i, y_i$，表示第 $x_i$ 次抽出颜色为的 $y_i$ 球。
## 输出格式

要求用分数形式输出（显然此概率为有理数）。输出文件包含一行，格式为：`分子/分母`。同时要求输出最简形式（分子分母互质）。特别的，概率为 $0$ 应输出 `0/1`，概率为 $1$ 应输出 `1/1`。
## 样例

### 样例输入 #1
```
2 3 1
1 1
1 1
2 2
3 1

```
### 样例输出 #1
```
1/12

```
### 样例输入 #2
```
3 1 2
1 1 1
5 1

```
### 样例输出 #2
```
1/3

```
## 提示

**【样例解释 #1】**

初始时，两种颜色球数分别为 $(1, 1)$，取出色号为 $1$ 的球的概率为 $1/2$；第二次取球之前，两种颜色球数分别为 $(2, 1)$，取出色号为 $2$ 的球的概率为 $1/3$；第三次取球之前，两种颜色球数分别为 $(2, 2)$，取出色号为 $1$ 的球的概率为 $1/2$，所以三次取球的总概率为 $1/12$。

**【数据规模和约定】**

对于 $100 \%$ 的数据，$1 \le t, n \le 1000$，$1 \le a_k, d \le 10$，$1 \le x_1 < x_2 < \cdots < x_n \le 10000$，$1 \le y_k \le t$。


---

---
title: "[SCOI2003] 严格N元树"
layout: "post"
diff: 省选/NOI-
pid: P4295
tag: ['高精度', '2003', '四川', '各省省选', '前缀和', '差分']
---
# [SCOI2003] 严格N元树
## 题目描述

如果一棵树的所有非叶节点都恰好有 $n$ 个儿子，那么我们称它为严格 $n$ 元树。如果该树中最底层的节点深度为 $d$（根的深度为 $0$），那么我们称它为一棵深度为 $d$ 的严格 $n$ 元树。例如，深度为２的严格２元树有三个，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/um9mtoxb.png)
 
给出 $n,d$，编程数出深度为 $d$ 的 $n$ 元树数目。
## 输入格式

仅包含两个整数 $n,d(0<n \le 32,0 \le d \le 16)$。输入数据保证你不需要考虑某一层多于 $1024$ 个节点的树（即 $nd \le 1024$）。提示：答案保证不超过 $200$ 位十进制数。
## 输出格式

仅包含一个数，即深度为 $d$ 的 $n$ 元树的数目。
## 样例

### 样例输入 #1
```
2 2
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
2 3
```
### 样例输出 #2
```
21
```
### 样例输入 #3
```
3 5
```
### 样例输出 #3
```
58871587162270592645034001

```


---

---
title: "[FJOI2016] 所有公共子序列问题"
layout: "post"
diff: 省选/NOI-
pid: P4608
tag: ['字符串', '高精度', '2016', '各省省选', '福建', '有限状态自动机']
---
# [FJOI2016] 所有公共子序列问题
## 题目描述

一个给定序列的子序列是在该序列中删去若干元素后得到的序列。确切地说，若给定序列 $X=x_1x_2\ldots x_m$，则另一序列 $Z=z_1z_2\ldots z_k$ 是 $X$ 的子序列是指存在一个严格递增下标序列 $i_1,i_2, \ldots ,i_k$ 使得对于所有 $j=1,2,…,k$ 有 $z_j=x_{i_j}$。

例如，序列 $Z=$``GACT`` 是序列 $X=$``GCTACT`` 的子序列，相应的递增下标序列为 $1,4,5,6$。给定两个序列 $X$ 和 $Y$，当另一序列 $Z$ 既是 $X$ 的子序列又是 $Y$ 的子序列时，称 $Z$ 是序列 $X$ 和 $Y$ 的公共子序列。例如，若 $X=$``GCTACT``， $Y=$``GATCCT``，序列 $T$ 是 $X$ 和 $Y$ 的一个公共子序列，序列 ``GACT`` 也是 $X$ 和 $Y$ 的一个公共子序列。注意对于任何给定的序列 $X$ 和 $Y$，空序列总是它们的一个公共子序列。

所有公共子序列问题是要求对于给定的 $2$ 个序列 $X=x_1x_2\ldots x_m$ 和 $Y=y_1y_2\ldots y_m$，找出 $X$ 和 $Y$ 的所有不同的公共子序列。
## 输入格式

文件的第一行有两个正整数 $m$ 和 $n$，分别表示 $2$ 个输入序列 $X$ 和 $Y$ 的长度。

接下来的两行分别给出输入序列 $X=x_1x_2\cdots x_m$ 和 $Y=y_1y_2\cdots y_m$，其中序列中每个元素均为二十六个英文大小写字母。

文件的最后一行给出一个非负整数 $k$。

$k$ 的值为 $1$ 时，表示计算结果要输出 $X$ 和 $Y$ 的所有不同的公共子序列，以及 $X$ 和 $Y$ 有多少个不同的公共子序列。

$k$ 的值为 $0$ 时，表示计算结果只要输出 $X$ 和 $Y$ 有多少个不同的公共子序列。
## 输出格式

将计算出的 $X$ 和 $Y$ 的所有不同的公共子序列，或 $X$ 和 $Y$ 有多少个不同的公共子序列输出到文件中。当 $k=1$ 时，先输出 $X$ 和 $Y$ 的所有不同的公共子序列，每行输出一个公共子序列，按字典序从小到大输出。最后输出不同的公共子序列的个数。当 $k=0$ 时，只要输出不同的公共子序列的个数。
## 样例

### 样例输入 #1
```
6 6
GCTACT
GATCCT 1
```
### 样例输出 #1
```
A
AC
ACT
AT 
C  
CC 
CCT
CT 
G  
GA 
GAC
GACT
GAT 
GC  
GCC 
GCCT
GCT 
GT  
GTC 
GTCT
GTT 
T   
TC  
TCT 
TT  
26
```
## 提示

$1 \leq m,n \leq 3010$

答案....很大啦


---

---
title: "「SWTR-2」Magical Gates"
layout: "post"
diff: 省选/NOI-
pid: P5674
tag: ['高精度', '数位 DP']
---
# 「SWTR-2」Magical Gates
## 题目背景

小 $\mathrm{A}$ 找到了一张藏宝图。

他顺着藏宝图上的路线来到了一扇古老的大门前，门上有六芒星的图案。

他把手轻轻地放在六芒星上……

霎时间，六芒星光芒大放，四周亮如白昼。

（新增一组大样例）
## 题目描述

小 $\mathrm{A}$ 面前出现了 $10^{1000}$ 扇门，每个门上都写着它自己的编号，分别为 $1,2,3,\dots,10^{1000}$。

这时，守门人小 $\mathrm{M}$  向小 $\mathrm{A}$ 走来。

“这些门，并不普通，它有魔力。”

“我会给你一些区间 $l,r$，请你求出区间 $[l,r]$ 里所有门的魔力值之**和**与魔力值之**积**。”

“因为结果可能很大，请你将结果 $mod\ p$。 ”

“如果你正确地回答了所有询问，你将会拥有这扇门后的所有宝藏。”

“哦，对了，一扇门的魔力值就是其在二进制下 $1$ 的个数。”

简单来说，记第 $i$ 扇门的魔力值为 $d_i$，给定的区间为 $[l,r]$，请求出：

$$\sum_{l}^{r}d_i\bmod\ p \quad \prod_{l}^{r}d_i\bmod\ p$$

由于门的数量实在太多，小 $\mathrm{A}$ 决定向你请求帮助。
## 输入格式

第一行三个正整数 $T,p,n$（$n$ 会在数据范围中说明）。

接下来 $T$ 行，第 $i$ 行两个**正整数** $l_i,r_i$。
## 输出格式

输出 $T$ 行，每行 $2$ 个数，由空格隔开，第 $i$ 行分别为：

$$\sum_{l}^{r}d_i\bmod\ p \quad \prod_{l}^{r}d_i\bmod\ p$$
## 样例

### 样例输入 #1
```
7 1000000007 0
3 7
1 10
1 1048576
20180815 20180830
20180632 20180639
123456789 987654321
123456789987654321 123456789987654321123456789987654321
```
### 样例输出 #1
```
10 24
17 96
10485761 64327945
255 803716286
124 290111979
996409842 54001814
253678327 263109263
```
## 提示

---

### 样例说明

数据 $1$：

$$\sum_{3}^{7}d_i=2+1+2+2+3=10$$

$$\prod_{3}^{7}d_i=2\times 1\times 2\times 2\times 3=24$$

数据 $2$：

$$\sum_{1}^{10}d_i=1+1+2+1+2+2+3+1+2+2=17$$

$$\prod_{1}^{10}d_i=1\times 1\times 2\times 1\times 2\times 2\times 3\times 1\times 2\times 2=96$$

---

### 数据范围与约定

![](https://cdn.luogu.com.cn/upload/image_hosting/zv6ppsk4.png)

为了方便拿部分分，输入格式中的 $n$ 为**该测试点的编号**。

所有具有特殊性质的测试点一共 $31\%$。

对于 $100\%$ 的数据，有 $1\leq n\leq 27,1\leq T \leq 10,10^9 \leq p \leq 1.001\times 10^9,1\leq l\leq r\leq 10^{1000}$，**保证 $p$ 为质数**。

---

对于测试点 $1-20$，时限 $300ms$，剩下的 $7$ 个测试点时限 $2s$。

对于所有测试点，空间限制 $256MB$

---

“吱嘎”一声，封尘千年的大门缓缓打开。

刺眼的金光照了出来……


---

---
title: "[NEERC 2015] Binary vs Decimal"
layout: "post"
diff: 省选/NOI-
pid: P6124
tag: ['高精度', '2015', '广度优先搜索 BFS', 'ICPC']
---
# [NEERC 2015] Binary vs Decimal
## 题目描述

一个正数 $A$，如果它只包含 `0` 或 `1`，且它转成二进制后的 $B$，$A$ 是 $B$ 的后缀，这个数就是我们所要的。

现在给出数字 $N$，求第 $N$ 个这样的数。
## 输入格式

一行一个数 $N$。
## 输出格式

一行一个数，第 $N$ 个数。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
10
```
### 样例输出 #2
```
1100
```
## 提示

$1 \le N \le 10^4$。

|原数|二进制|评论|
| :-----------: | :-----------: | :-----------: |
|$1$|$1$|√|
|$10$|$1010$|√|
|$11$|$1011$|√|
|$100$|$1100100$|√|
|$101$|$1100101$|√|
|$110$|$1101110$|√|
|$111$|$1101111$|√|
|$1000$|$1111101000$|√|
|$1001$|$1111101001$|√|
|$1010$|$1111110010$|×|
|$1011$|$1111110011$|×|
|$1100$|$10001001100$|√| 


---

---
title: "[THUPC 2023 初赛] 拧螺丝"
layout: "post"
diff: 省选/NOI-
pid: P9134
tag: ['模拟', '高精度', '2023', 'O2优化', 'THUPC']
---
# [THUPC 2023 初赛] 拧螺丝
## 题目背景

张华考上了北京大学；李萍进了中等技术学校；~~小 E 在工地搬砖~~：他们都有光明的前途。

由于搬砖太累，小 E 决定进厂拧螺丝。但是小 E 遇到了一个各种刁难人的老板。
## 题目描述

加工一个模块需要拧 $n$ 个螺丝。但是，每隔 $10$ 分钟，小 E 的老板就会到小 E 的工位上收走一个未完工的模块。在这期间，只够小 E 拧 $k$ 个螺丝。

小 E 的老板刚刚离开。问老板接下来第几次来的时候小 E 才可能有一个完工的模块？假设小 E 的老板极力不想让小 E 达成这件事。
## 输入格式

一行两个正整数，$n,k$。
## 输出格式

如果小 E 无论如何也不能有一个完工的模块，那么输出一行 `Poor E.S.!`。

否则输出一行一个正整数，表示答案。
## 样例

### 样例输入 #1
```
3 2

```
### 样例输出 #1
```
2

```
## 提示

#### 样例解释 1

小 E 先选择两个模块各拧上一个螺丝，然后老板来了拿走一个。接下来小 E 只需要在剩下的那个零件上面拧两个螺丝就可以完工了。所以老板第二次来的时候小 E 就有了一个完工的模块。注意小 E 在老板来的时候不能有只拧上了一半的螺丝，不然老板看到了会说小 E 加工不合格。

#### 子任务

保证 $1\le k \le n \le 10^5$。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。


---

