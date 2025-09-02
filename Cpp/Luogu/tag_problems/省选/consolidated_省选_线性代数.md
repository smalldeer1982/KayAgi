---
title: "理性（Rationality）"
layout: "post"
diff: 省选/NOI-
pid: P10323
tag: ['数学', '洛谷原创', 'O2优化', '期望', '线性代数', '微积分', '洛谷比赛']
---
# 理性（Rationality）
## 题目背景

数学之善，统治宇宙的根本原理 —— 理性。
****
「理性之光」伊奥，是古代精灵图形术士。已经千岁的她总能不受感情的干扰，以理性做出最优的决策。   
## 题目描述

赛时更新：请注意，对于一组确定的 $v_1,\cdots,v_n$，都可以求出 $\text{RSS}$ 的最小值。**它是关于随机变量  $v_1,\cdots,v_n$ 的一个随机变量**，将其记为 $X$，则要求的是 $\mathbb E[X]$。   
笔误改正：残差平方和的英文为 $\text{RSS}$。
****
伊奥的思绪回到了千年前的一场大战中。

她记得那场战斗中有 $n$ 个敌人，第 $i$ 个敌人在距离她 $d_i$（$d_i$ 之间互不相同）的位置上。这些敌人都带有一个**正整数**标记 $v_i$，只要以**恰好** $v_i$ 的攻击力击中它就可以将其消灭。

她只要设定一个一次函数 $f(x)=ax+b$，就能在距离她 $d_i$ 的位置放出 $f(d_i)$ 的攻击力。好在她的队友会辅助她攻击，她只用考虑确定 $a,b$ 使得 $f(x)$ 的效果最优，即最小化 $\text{RSS}$（残差平方和）：
$$\text{RSS}=\sum_{i=1}^n(f(d_i)-v_i)^2$$
当然了，这只是她的回忆。她能清晰记得每个敌人到她的距离 $d_i$，而对于 $v_i$ 她只记得满足 $l_i\leq v_i \leq r_i$。

她想知道假设每个 $v_i$ 都对应在 $[l_i,r_i]$ 范围内**均匀随机**的情况下，「$\text{RSS}$ **的最小值」的期望**。   
可以证明答案总是有理数，你只需要告诉她答案对 $998244353$ 取模的结果即可。
## 输入格式

第一行一个正整数 $n$，表示敌人的个数。  
接下来 $n$ 行，每行三个正整数 $d_i,l_i,r_i$，分别表示第 $i$ 个敌人到伊奥的距离，其标记 $v_i$ 的下界和上界。

为了方便你的计算，伊奥保证 $d_i< d_{i+1}$（$1\leq i <n$），并且：

$$n\sum_{i=1}^nd_i^2 \not \equiv \left(\sum_{i=1}^nd_i \right)^2 \pmod{998244353}$$
**即确保答案在模 $998244353$ 意义下一定存在。**
## 输出格式

输出一行一个整数，表示所有情况下 $\text{RSS}$ 最小值的期望。
## 样例

### 样例输入 #1
```
3
1 4 4
3 7 7
5 10 10
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
5
1 4 4
2 5 5
3 7 7
4 8 8
9 8 8
```
### 样例输出 #2
```
488831003
```
### 样例输入 #3
```
5
1 1 4
2 2 5
3 3 7
4 2 8
9 3 8
```
### 样例输出 #3
```
884183796
```
### 样例输入 #4
```
10
123 1 10
234 11 14
345 10 20
456 6 6
567 20 30
678 84 90
789 1 3
8910 8 15
91011 123 129
101112 56 64
```
### 样例输出 #4
```
483360041
```
## 提示

【样例 $1$ 解释】

此样例中有 $l_i=r_i$，即情况已经确定，只需要求出此时最优的 $a,b$ 即可。容易发现 $(1,4),(3,7),(5,10)$ 这三组数据可以用一次函数完美拟合：即 $f(x)=\dfrac 32 x+\dfrac{5}{2}$，与每个点偏差都是 $0$，故 $\text{RSS}$ 最小值的期望，也就是答案为 $0$。

【样例 $2$ 解释】

这里同样有 $l_i=r_i$。$5$ 个敌人的数据 $(d_i,v_i)$ 分别为 $(1,4),(2,5),(3,7),(4,8),(9,8)$，可以证明取
$$a=\frac{87}{194} \ , \ b=\frac{911}{194}$$
是一组使得 $\text{RSS}$ 最小的解，代入计算得
$$\text{RSS}=\sum_{i=1}^n\left( \frac{87}{194}d_i+\frac{911}{194}-v_i\right)^2=\frac{1047}{194}$$
在模 $998244353$ 意义下答案为 $488831003$。

【数据范围】

**本题采用捆绑测试。**

Subtask 1（10 pts）：$n \leq 3$；  
Subtask 2（10 pts）：$l_i=r_i$；  
Subtask 3（15 pts）：$n\le500$，$r_i\leq 500$；  
Subtask 4（15 pts）：$n\le 5000$；  
Subtask 5（20 pts）：$n\le 10^5$；  
Subtask 6（30 pts）：无特殊限制。

对于全部的数据，$2\le n \le 5\times 10^5$，$1\leq l_i \leq r_i \leq 10^8$，$1\leq d_i \leq 10^8$， $d_i<d_{i+1}$（$1\leq i <n$），并且有：
$$n\sum_{i=1}^nd_i^2 \not \equiv \left(\sum_{i=1}^nd_i \right)^2 \pmod{998244353}$$

【提示】

题目中要求出「$\text{RSS}$ 的最小值」期望值。对于离散随机变量 $X$，假设其可以取值为 $a_1,a_2,\cdots,a_n$，对应概率为 $p_1,p_2,\cdots,p_n$（$p_1+\cdots+p_n=1$），则其期望值可以定义为：
$$\mathbb E[X]=\sum_{i=1}^np_i a_i$$
对于计算有理数取模的方法，请参考[模板题](https://www.luogu.com.cn/problem/P2613)。


---

---
title: "[COTS 2024] 奇偶南瓜 Tikvani"
layout: "post"
diff: 省选/NOI-
pid: P10682
tag: ['2024', 'O2优化', '线性代数', '线性基', 'COCI（克罗地亚）']
---
# [COTS 2024] 奇偶南瓜 Tikvani
## 题目背景

译自 [Izborne Pripreme 2024 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2024/) D1T3。$\texttt{0.5s,1G}$。
## 题目描述

给定有向图 $G=(V,E)$，其中 $|V|=N,|E|=M$，满足 $\forall (u,v)\in E$，都有 $u\lt v$。

定义边的一种**着色方案**为一种给每条边分配 $0/1$ 权值的方式。记 $(u,v)$ 边权为 $w(u,v)$。

定义节点 $(u,v)$ 的路径为一个序列 $(a_1,a_2,\cdots,a_k)$，满足 $a_1=u,a_k=v$，且 $\forall 1\le i\lt k$，都有 $(a_i,a_{i+1})\in E$。定义路径的权值为其上所有边的权值之和，即 $\displaystyle \sum_{i=1}^{k-1} w(a_{i},a_{i+1})$。

定义一种着色方案是好的，当且仅当对于每一对 $(u,v)$，都有 $(u,v)$ 间的所有路径的权值模 $2$ 后的余数相等。

求出好的着色方案数，对 $(10^9+7)$ 取模。
## 输入格式

第一行，两个正整数，$N,M$，含义见题面。

接下来 $M$ 行，每行两个正整数 $u,v$，表示 $(u,v)\in E$。
## 输出格式

输出一行一个整数，表示答案对 $(10^9+7)$ 取模后的结果。
## 样例

### 样例输入 #1
```
4 4
1 2
2 3
3 4
1 4
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
4 4
1 3
1 4
2 3
2 4
```
### 样例输出 #2
```
16
```
## 提示


#### 样例解释

样例 $1$ 解释：显然只有 $1,4$ 间有两条路径 $(1,2,3,4),(1,4)$。

当 $w(1,4)=0$ 时，$(1,2,3,4)$ 路径上只能取 $0$ 或 $2$ 条边边权为 $1$，方案数为 $4$；

当 $w(1,4)=1$ 时，$(1,2,3,4)$ 路径上只能取 $1$ 或 $3$ 条边边权为 $1$，方案数为 $4$。

所以答案为 $8$。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le N\le 400$，$0\le M\le 400$；
- $1\le u\lt v\le n$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $21$  | $N \leq 6$   |
| $2$  | $20$  | $N \leq 13$  |
| $3$  | $37$  | $N, M \leq 50$ |
| $4$  | $22$  | 无额外约束 |




---

---
title: "「CMOI R1」We Want To Run / Nilpotent"
layout: "post"
diff: 省选/NOI-
pid: P11173
tag: ['动态规划 DP', '数学', '2024', '洛谷原创', 'O2优化', '动态规划优化', '图论建模', '线性代数']
---
# 「CMOI R1」We Want To Run / Nilpotent
## 题目背景

![](bilibili:BV1qW4y1Q7Ce)

$\small\color{white}54^{\text{th}}\text{Problem by ArCu}.$
## 题目描述

对于 $n\times n$ 矩阵 $A$，定义 $f(A)$ 为最小的满足 $A^b=O$ 的正整数 $b$，若不存在这样的数则 $f(A)=0$。其中 $O$ 是零矩阵，即所有元素都是 $0$ 的矩阵。

给定 $n,a$，每个元素都是 $[0,a)$ 中整数的 $n\times n$ 矩阵有 $a^{n^2}$ 种。对所有 $a^{n^2}$ 种可能的矩阵 $A$ 求 $f(A)$ 之和。

答案对 $202407031$ 取模。
## 输入格式

一行两个整数 $n,a(1\leq n\leq 600,0<a<2^{64})$。
## 输出格式

一行一个整数，表示你求得的答案。
## 样例

### 样例输入 #1
```
2 2
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
3 4
```
### 样例输出 #2
```
793
```
### 样例输入 #3
```
5 10
```
### 样例输出 #3
```
59350891
```
### 样例输入 #4
```
18 15932416
```
### 样例输出 #4
```
52138206
```
### 样例输入 #5
```
1 1
```
### 样例输出 #5
```
1
```
## 提示

$\text{Sample 1 Explanation}:$

注意到对于任意正整数 $b$，$\begin{bmatrix}1&0\\1&1\end{bmatrix}^b\neq O$，所以 $f\left(\begin{bmatrix}1&0\\1&1\end{bmatrix}\right)=0$。而 $\begin{bmatrix}0&0\\1&0\end{bmatrix}^2=O$，所以 $f\left(\begin{bmatrix}0&0\\1&0\end{bmatrix}\right)=2$。

一共有 $2^4=16$ 种可能的矩阵。其中 $f(A)$ 不为 $0$ 的只有

$$f\left(\begin{bmatrix}0&0\\0&0\end{bmatrix}\right)=1,f\left(\begin{bmatrix}0&0\\1&0\end{bmatrix}\right)=f\left(\begin{bmatrix}0&1\\0&0\end{bmatrix}\right)=2$$

答案即为 $1+2+2=5$。

$\text{Details of Subtasks}:$

所有数据满足 $1\leq n\leq 600,0<a<2^{64}$。

| $\text{Subtask}$ | $\text{Special Constraints}$ | $\text{Score}$ |
| :----------: | :----------: | :----------: | 
| $1$ | $n\leq 5,a\leq 2$ | $3$ |
| $2$ | $n\leq 5$ | $7$ | 
| $3$ | $n\leq 10$ | $10$ | 
| $4$ | $n\leq 40$ | $20$ | 
| $5$ | $n\leq 200$ | $30$ |
| $6$ |  | $30$ |

$\text{Hint}:202407031=13009\times 15559.$


---

---
title: "[USTCPC 2025] Algorithm Duel"
layout: "post"
diff: 省选/NOI-
pid: P12044
tag: ['2025', 'Special Judge', '线性代数', '高斯消元', '线性基', '构造', '高校校赛', 'bitset']
---
# [USTCPC 2025] Algorithm Duel
## 题目背景

考虑到评测机性能差异，改为 1s 时限。USTCPC 时限为 3s。
## 题目描述

Algorithm Duel （在线算法题单挑）是大家非常喜欢的活动之一。而这样的团建活动称为  Algorithm Duel 团建活动（以下简称**团建活动**）。

社团群内共有 $n$ 位群友。克露丝卡尔酱从题库中挑选了 $m=3n-3$ 道题目，**每位群友都有至少其中的一些题没有做过**。①

一场**标准的团建活动**定义如下：对于 $m$ 道题目中的任意一道题目，有偶数位群友没有做过这道题目，这样他们能两两配对举行 Algorithm Duel。

克露丝卡尔酱很遗憾地发现无论从 $n$ 位群友挑选任何非空子集，都不能进行一场**标准的团建活动**。②

但是，她还是非常想举办一场 Algorithm Duel 团建活动，她作为活动负责人只能亲自加入该场活动。为了尽可能保证活动的公正性，她可以任意选择 $n\sim m-n+1$ 道题目给一位群友送分（即这些题目可以有奇数位位群友没有做过这道题目）。这样的活动称为**非标准的团建活动**。

好了，现在请帮助她决定应该邀请哪些群友参加这场活动能成为一场**非标准的团建活动**吧？应该能有解的，不是吗？
## 输入格式

第一行一个整数 $n(2\le n\le 1000)$。$m=3n-3$。

接下来 $n$ 行长度为 $m$ 的 01 串 $s$。**若 $s_j=1$ 则表示编号为 $i$ 的群友没有做过题目 $j$；$s_j=0$ 则表示编号为 $i$ 的群友做过题目 $j$**。

保证输入的数据满足题面中①②的条件。
## 输出格式

输出的第一行一个正整数 $k(1\le k\le n)$，表示邀请的群友的数目。

输出的第二行 $k$ 个正整数 $x_1,x_2,\dots,x_k$，表示邀请了编号为 $x_1,x_2,\dots x_k$ 的群友参加活动。

要求 $1\le x_i\le n$ 且 $x_i$ 两两不同。
## 样例

### 样例输入 #1
```
2
011
110
```
### 样例输出 #1
```
2
1 2
```
### 样例输入 #2
```
4
110000000
001100000
000011000
000000111
```
### 样例输出 #2
```
2
3 4
```
## 提示

对于样例 $1$，邀请所有群友后，有题目 $1$ 和 $3$ 两道题目只有奇数个群友没有做过。$n=2$ 时，**非标准的团建活动**必须恰好 $2$ 道题目有奇数个群友没有做过，满足条件。


---

---
title: "[Aboi 2077] SL2(Z/NZ)"
layout: "post"
diff: 省选/NOI-
pid: P1951
tag: ['群论', '线性代数']
---
# [Aboi 2077] SL2(Z/NZ)
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/gdzfpiv1.png)
## 题目描述

求模 $N$ 意义下行列式为 $1$ 的 $2\times2$ 矩阵数量。

即：
$$
\sum_{a=0}^{N-1}\sum_{b=0}^{N-1}\sum_{c=0}^{N-1}\sum_{d=0}^{N-1}[ad-bc\equiv1\ (\bmod\ N)]
$$
## 输入格式

多组数据，第一行一个正整数 $T$ 表示数据组数。

之后 $T$ 行，每行一个正整数 $N$，表示该组数据的模数。
## 输出格式

对于每组数据，输出答案模 $998244353$ 的值。
## 样例

### 样例输入 #1
```
10
2
5
11
23
101
64
128
114514
1919810
1145141919810
```
### 样例输出 #1
```
6
120
1320
12144
1030200
196608
1572864
173069674
546691096
761755430
```
## 提示

| 子任务编号 | $N$ | 分值 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $\le50$ | $10$ |
| $2$ | $\le200$ | $10$ |
| $3$ | $\le10^3$ | $20$ |
| $4$ | $\le10^6$ | $20$ |
| $5$ | $\le10^9$ | $20$ |
| $6$ | $\le10^{18}$ | $20$ |


对于所有数据，$1\le T\le10$，$1\le N\le10^{18}$。


---

---
title: "[POI 2014] LAM-Solar lamps"
layout: "post"
diff: 省选/NOI-
pid: P3578
tag: ['2014', 'POI（波兰）', '树套树', '线性代数']
---
# [POI 2014] LAM-Solar lamps
## 题目描述

Byteasar has a large and pretty garden.

As he would like to be able to appreciate its beauty even after dusk,he installed lamps across the garden.

The lamps are directional, i.e., they illuminate only a certain angle, common to them all.

Moreover, Byteasar has aligned them so that they all face the same direction.

Last but not least, these are solar lamps, i.e., they come with solar panelsbut no batteries, strangely enough!  You might think the panels are thus useless,and each lamp will require electricity at night, but not quite: A lamp will produce lightif a sufficient number of lamps illuminate it.

By now, Byteasar has even come up with an order he is going supply the lamps with electricity,thus turning them on.

For simplicity, we number the lamps from 1 to $n$ in this order, i.e., the lamp no. $i$ is supplied with electricity at time $i$.  The only thing left for Byteasar (and you, of course!) is tofigure out when exactly each lamp will start emitting light.  Help Byteasar by writing a programthat will determine the answer to this question.

给N盏灯，没盏灯能照到的角度范围是相同的，第i盏灯在第i秒或者被ki盏灯照到后都会亮起，问所有灯都在什么时刻亮起

## 输入格式

The first line of the standard input contains a single integer $n$($1\le n\le 200\ 000$): the number of lamps Byteasar installed.

In the second line of input, there are four integers $X_1,Y_1,X_2,Y_2$ ($-10^9\le X_i,Y_i\le 10^9$, $(X_i,Y_i)\ne(0,0)$), separated by single spaces,that describe the area illuminated by every lamp.

Namely, if there is a lamp located at the point $(x,y)$, then it illuminatesthe area (together with its edge) within the smaller of the two angles formed by tworays that both originate at $(x,y)$ such that the i-th (for $i=1,2$) ray passes through $(x+X_i,y+Y_i)$. This angle is always smaller than 180 degrees.

The $n$ input lines that follow specify the locations of the lamps: the $i$-th such line contains two integers $x_i,y_i$ ($-10^9\le x_i,y_i\le 10^9$) separated by a single space, that indicate that the lamp no.$i$ is located at the point $(x_i,y_i)$. You may assume that no two lamps share their location.

The last line of the input contains $n$ integers $k_1,k_2,\cdots,k_n$ ($1\le k_i\le n$), separated by single spaces, that signify that if the lamp no. i is in the area illuminated by at least $k_i$ other lamps, then it will start emitting light as well.

## 输出格式

Your program should print out to the standard output a single line with $n$ integers $t_1,t_2,\cdots,t_n$, separated by single spaces.

The number $t_i$ should be the time when the lamp no. $i$ starts producing light.

## 样例

### 样例输入 #1
```
5
3 1 1 3
2 1
1 4
3 4
5 6
5 2
1 2 1 3 2

```
### 样例输出 #1
```
1 2 1 2 5

```
## 提示

给N盏灯，没盏灯能照到的角度范围是相同的，第i盏灯在第i秒或者被ki盏灯照到后都会亮起，问所有灯都在什么时刻亮起



---

---
title: "【模板】一般图最大匹配"
layout: "post"
diff: 省选/NOI-
pid: P6113
tag: ['Special Judge', '一般图的最大匹配', '线性代数']
---
# 【模板】一般图最大匹配
## 题目背景

模板题，无背景。
## 题目描述

给出一张 $n$ 个点 $m$ 条边的无向图，求该图的最大匹配。
## 输入格式

第一行两个正整数 $n$ 和 $m$，分别表示图的点数和边数。

接下来 $m$ 行，每行两个正整数 $u$ 和 $v$，表示图中存在一条连接 $u$ 和 $v$ 的无向边。
## 输出格式

第一行一个整数，表示最大匹配数。

第二行 $n$ 个整数，第 $i$ 个数表示与结点 $i$ 匹配的结点编号，若该结点无匹配则输出 $0$。

如有多解输出任意解即可。
## 样例

### 样例输入 #1
```
10 10
4 3
3 1
4 7
2 10
2 9
3 10
5 9
4 6
1 10
1 7

```
### 样例输出 #1
```
4
7 9 10 6 0 4 1 0 2 3 
```
## 提示

对于 $50\%$ 的数据，$n\le500$。

对于 $100\%$ 的数据，$2\le n\le10^3$，$1\le m\le5\times10^4$。

本题有 5 组 extra test。

####  提示
为了方便你调试你的程序，出题人在[这里](https://www.luogu.com.cn/paste/vf7dlo6r)为你提供了一个~~写的很丑的~~数据生成器。


---

---
title: "[THUPC 2017] 气氛"
layout: "post"
diff: 省选/NOI-
pid: P7429
tag: ['计算几何', '2017', '线性代数', '高斯消元', 'THUPC']
---
# [THUPC 2017] 气氛
## 题目描述

北大街，在中国是一个非常常见的地名，比较著名的有上海北大街，西安北大街，成都北大街，太原北大街，中关村北大街等。

我们都知道，北的意思是自由民主，大的意思是兼收并蓄，所以住在北大街的人也性情迥异，我们假设在北大街住了 $n$ 个人。

有人向住在北大街的这 $n$ 个人提了 $n-1$ 个问题，比如：

「用不用筷子？」

「吃不吃红烧肉？」

「写代码用 tab 还是 space」

「大括号换不换行？」

「……」

根据每个人的回答，他会被分配一个 $n-1$ 维的零一坐标，也就是一个点。这样 $n$ 个点可以恰好构成一个 $n-1$ 维空间中的凸包。

北大街的居民认为，在这个多面体内，便是华夏；多面体之外，便是蛮夷。我们可以很容易的计算出华夏部分的广义凸包体积。

有一天，清华路的 B 君来北大街玩，听说了这个故事觉得很有趣，于是也试着给出了这 $n-1$ 个问题的答案，

清华路的 B 君，当然认为自己属于华夏，但是北大街表示在 $n-1$ 维空间中如果有 $n+1$ 个点的话，华夏部分的体积难以计算。

这下子气氛突然僵化。所以这个问题就留给你了，输入 $n-1$ 维度空间中的 $n+1$ 个点，求广义凸包的体积。

由于这个体积可能不是整数，你只需要输出体积乘以 $n-1$ 的阶乘，然后对 $10^9+7$ 取模的结果。
## 输入格式

从标准输入读入数据。

第一行一个整数 $T$ 表示组数，接下来是 $T$ 组数据

每组数据的第一行是一个整数 $n$ 。

接下来 $n+1$ 行，每行 $n-1$ 个整数，表示在 $n-1$ 维空间中的一个点。
## 输出格式

输出到标准输出。

对于每组数据，输出一行一个整数表示答案。

输入 $n+1$ 个点的凸包体积乘以 $n-1$ 的阶乘，然后对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
1
3
0 0
0 1
1 0
1 1
```
### 样例输出 #1
```
2
```
## 提示

$1\le t\le 100,3\le n\le35$

点的坐标一定是 $0$ 或者 $1$。
#### 版权信息
来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2017。


---

---
title: "既见君子"
layout: "post"
diff: 省选/NOI-
pid: P7437
tag: ['O2优化', '生成树', '线性代数', '高斯消元', '状压 DP']
---
# 既见君子
## 题目背景

友情客串：wygz（无忧公主）

wygz 每次从进校到机房，都要尽量避开“屠夫”老师。然而，有一天，她忽然发现一些门上居然贴了“请勿从此门进出”的标签！
## 题目描述

校园可以抽象成一张 $n$ 个点 $m$ 条无向边（可能有重边，无自环）的**连通**无向图，点从 $1$ 标号到 $n$。校门在 $1$ 号点，而机房在 $n$ 号点，屠老师的办公室在点 $z$（$z\ne 1,n$）。

然而，工作人员（~~其实是樱初音~~）封锁了其中的 $m-n+1$ 条边，使得剩余的图（包括所有点以及剩余的边）仍然连通，此时任意两点之间有且仅有一条简单路径。工作人员会**等概率地**选择一种封锁方案。（若 $m=n-1$ 则不封锁任何边，保持不变）

wygz 当然不希望屠老师的办公室出现在她的必经之路上。她希望你算出从校门到机房的路径**必须**经过屠老师的办公室的概率。答案对 $998244353$ 取模。
## 输入格式

第一行三个正整数 $n$、$m$ 和 $z$，表示点数、边数和屠老师的办公室的位置。

以下 $m$ 行，每行两个正整数 $u$、$v$，表示一条连接 $u$ 和 $v$ 的无向边。
## 输出格式

一行一个非负整数，表示答案对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
4 5 2
1 2
1 3
2 3
2 4
3 4
```
### 样例输出 #1
```
374341633
```
### 样例输入 #2
```
6 8 4
1 2
1 3
2 3
2 4
2 5
4 5
4 6
5 6
```
### 样例输出 #2
```
374341633
```
## 提示

#### 样例解释：
样例 #1：生成树共 $8$ 个，有 $5$ 个满足 $1$ 到 $4$ 经过 $2$。$\dfrac 5 8\equiv 374341633\pmod {998244353}$。

样例 #2：生成树共 $24$ 个，有 $15$ 个满足 $1$ 到 $6$ 经过 $4$。$\dfrac {15} {24}\equiv 374341633\pmod {998244353}$。

#### 数据范围：

| 数据点编号 | $n$ | $m$ |
| :----------: | :----------: | :----------: |
| $1$ | $=3$ | $\le 5$ |
| $2$ | $=3$ | $\le 10^5$ |
| $3,4$ | $=7$ | $\le 15$ |
| $5,6$ | $=7$ | $\le 10^5$ |
| $7$ | $=20$ | $=n-1$ |
| $8,9$ | $=20$ | $=n$ |
| $10,11,12$ | $=18$ | $\le 10^5$ |
| $13,14,15,16$ | $=19$ | $\le 10^5$ |
| $17,18,19,20$ | $=20$ | $\le 10^5$ |

对 $100\%$ 的数据，$3\le n\le 20$，$n-1\le m\le 10^5$，$z\ne 1$ 且 $z\ne n$。

**数据保证输入的图的生成树个数模 $998244353$ 非零。**


---

---
title: "【模板】特征多项式"
layout: "post"
diff: 省选/NOI-
pid: P7776
tag: ['线性代数', '高斯消元']
---
# 【模板】特征多项式
## 题目背景

这是一道模板题。
## 题目描述

给出 $n$ 和一个 $n\times n$ 的矩阵 $A$，在模 $998244353$ 意义下求其特征多项式。
## 输入格式

第一行一个正整数 $n$。\
接下来 $n$ 行每行 $n$ 个非负整数，表示矩阵 $A$。
## 输出格式

输出一行 $n+1$ 个正整数，表示其特征多项式 $p_A(x)$ 从低到高的系数。
## 样例

### 样例输入 #1
```
3
1 2 3
4 5 6
7 8 9
```
### 样例输出 #1
```
0 998244335 998244338 1 
```
## 提示

对于一个 $n\times n$ 的矩阵 $A$，设其特征多项式为 $p_A(x)$，满足
$$p_A(x)=\det(xI_n-A)$$
其中，$I_n$ 为一个 $n\times n$ 的单位矩阵。

对于 $10\%$ 的数据，$1\le n\le 5$；\
对于 $40\%$ 的数据，$1\le n\le 50$；\
对于另外 $10\%$ 的数据，$\forall1\le i\le n,1\le j\le i-1,A_{i,j}=0$，即 $A$ 为上三角矩阵；\
对于另外 $20\%$ 的数据，$\forall1\le i\le n,1\le j\le i-2,A_{i,j}=0$，即 $A$ 为上海森堡矩阵；\
对于 $100\%$ 的数据，$1\le n\le 500$，$A_{i,j}\in[0,998244352]$。


---

