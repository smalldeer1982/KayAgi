---
title: "[COTS 2024] 奇偶矩阵 Tablica"
layout: "post"
diff: 省选/NOI-
pid: P10681
tag: ['动态规划 DP', '递推', '2024', 'O2优化', '生成函数', '线性递推', 'COCI（克罗地亚）']
---
# [COTS 2024] 奇偶矩阵 Tablica
## 题目背景

译自 [Izborne Pripreme 2024 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2024/) D1T2。$\texttt{1s,1G}。$
## 题目描述

考虑只包含 $0$ 和 $1$ 的 $N\times M$ 矩阵 $A$。

我们称满足以下条件的矩阵是好的：

- $\forall 1\le i\le N$，$\displaystyle \sum_{j=1}^M A_{i,j}\in \{1,2\}$；
- $\forall 1\le j\le M$，$\displaystyle \sum_{i=1}^N A_{i,j}\in \{1,2\}$。

求出 $N$ 行 $M$ 列的好的矩阵的数量，对 $(10^9+7)$ 取模。


## 输入格式

输入共一行两个正整数，即 $N,M$。
## 输出格式

输出一行一个整数，表示答案对 $(10^9+7)$ 取模后的结果。

## 样例

### 样例输入 #1
```
2 2
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
3 3
```
### 样例输出 #2
```
102
```
### 样例输入 #3
```
15 20
```
### 样例输出 #3
```
415131258
```
## 提示


#### 样例解释

样例 $1$ 解释如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/xufx7ad6.png)

#### 数据范围

对于 $100\%$ 的数据，$1\le N,M\le 3\, 000$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $10$  | $N, M \leq 6$   |
| $2$  | $18$  | $N, M \leq 50$  |
| $3$  | $31$  | $N, M \leq 200$ |
| $4$  | $41$  | 无额外约束 |




---

---
title: "[JLOI2015] 有意义的字符串"
layout: "post"
diff: 省选/NOI-
pid: P3263
tag: ['2015', '吉林', '矩阵乘法', '线性递推']
---
# [JLOI2015] 有意义的字符串
## 题目描述

B 君有两个好朋友，他们叫宁宁和冉冉。有一天，冉冉遇到了一个有趣的题目：输入三个非负整数 $b,d,n$，求

$$\left\lfloor \left ( \frac{b+\sqrt{d}}{2} \right ) ^n \right\rfloor \bmod p$$

其中 $p=7,528,443,412,579,576,937$
## 输入格式

一行三个非负整数 $b$，$d$，$n$。
## 输出格式

一行一个数表示模 $7,528,443,412,579,576,937$ 之后的结果。
## 样例

### 样例输入 #1
```
3 13 5

```
### 样例输出 #1
```
393

```
### 样例输入 #2
```
5 29 114514

```
### 样例输出 #2
```
4997196309027367968

```
## 提示

保证 $0<b^2 \le d<(b+1)^2 \le 10^{18}$，$n \le 10^{18}$，并且 $b\equiv 1\pmod 2$，$d\equiv 1\pmod 4$。



---

---
title: "[POI 2012] PRE-Prefixuffix"
layout: "post"
diff: 省选/NOI-
pid: P3546
tag: ['字符串', '2012', 'POI（波兰）', '哈希 hashing', '线性递推', 'KMP 算法']
---
# [POI 2012] PRE-Prefixuffix
## 题目描述

We consider strings consisting of lowercase letters of the English alphabet in this problem.

An initial fragment of a given string is called its prefix.

A final (terminal) fragment of a given string is called its suffix.

In particular, the empty string is both a prefix and a suffix of any string.

Two strings are cyclically equivalent if one of them can be obtained from another by    moving its certain suffix from the end of the string to its beginning.

For example, the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.1.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.2.png) are cyclically equivalent, whereas the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.3.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.4.png) are not.

In particular, every string is cyclically equivalent to itself.

A string ![](http://main.edu.pl/images/OI19/pre-en-tex.5.png) consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.6.png) letters is given.

We are looking for its prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.7.png) and suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.8.png) of equal length such that:

![](http://main.edu.pl/images/OI19/pre-en-tex.9.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.10.png) are cyclically equivalent,                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.11.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.12.png) does not exceed ![](http://main.edu.pl/images/OI19/pre-en-tex.13.png)        (i.e., the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.14.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.15.png) do not overlap in ![](http://main.edu.pl/images/OI19/pre-en-tex.16.png)), and                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.17.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.18.png) is maximized.

对于两个串 $S_1, S_2$，如果能够将 $S_1$ 的一个后缀移动到开头后变成 $S_2$，就称 $S_1$ 和 $S_2$ 循环相同。例如串 ababba 和串 abbaab 是循环相同的。

给出一个长度为 $n$ 的串 $S$，求满足下面条件的最大的 $L(L\leq \frac n 2)$：$S$ 的 $L$ 前缀和 $S$ 的 $L$ 后缀是循环相同的。
## 输入格式

The first line of the standard input contains a single integer ![](http://main.edu.pl/images/OI19/pre-en-tex.19.png)      (![](http://main.edu.pl/images/OI19/pre-en-tex.20.png)) denoting the length of the string ![](http://main.edu.pl/images/OI19/pre-en-tex.21.png).

The second line of input contains the string ![](http://main.edu.pl/images/OI19/pre-en-tex.22.png) itself, consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.23.png) lowercase letters of the English alphabet.

In tests worth 30% of the points the condition ![](http://main.edu.pl/images/OI19/pre-en-tex.24.png) holds in addition.

In tests worth 50% of the points the condition ![](http://main.edu.pl/images/OI19/pre-en-tex.25.png) holds in addition.

## 输出格式

Your program should print a single integer in the first and only line of the standard output,      namely the common length of the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.26.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.27.png) that we are looking for.

## 样例

### 样例输入 #1
```
15
ababbabababbaab
```
### 样例输出 #1
```
6
```
## 提示

数据范围：

- 对于 $30\%$ 的数据，保证 $n\le 500$；
- 对于 $50\%$ 的数据，保证 $n\le 5000$；
- 对于 $100\%$ 数据，保证 $1\le n\le 10^6$。


---

---
title: "[TJOI2015] 组合数学"
layout: "post"
diff: 省选/NOI-
pid: P3974
tag: ['数学', '递推', '2015', '各省省选', '线性递推', '天津']
---
# [TJOI2015] 组合数学
## 题目描述

为了提高智商，ZJY 开始学习组合数学。某一天她解决了这样一个问题：给一个网格图，其中某些格子有财宝。每次从左上角出发，只能往右或下走。问至少要走几次才可能把财宝全捡完。

但是她还不知足，想到了这个问题的一个变形：假设每个格子中有好多块财宝，而每一次经过一个格子至多只能捡走一块财宝，其他条件不变，至少要走几次才可能把财宝全捡完？

这次她不会做了，你能帮帮她吗？
## 输入格式

第一行为一个正整数 $t$，表示数据组数。

每组数据的第一行是两个正整数 $n$ 和 $m$，表示这个网格图有 $n$ 行 $m$ 列。

接下来 $n$ 行，每行 $m$ 个非负整数，表示这个格子中的财宝数量（$0$ 表示没有财宝）。
## 输出格式

对于每组数据，输出一个整数，表示至少走的次数。

## 样例

### 样例输入 #1
```
1
3 3
0 1 5
5 0 0
1 0 0
```
### 样例输出 #1
```
10
```
## 提示

### 数据范围

对于 $30\%$ 的数据，$n \le 5$，$m \le 5$，每个格子中的财宝数不超过 $5$ 块。

对于 $50\%$ 的数据，$n \le 100$，$m \le 100$，每个格子中的财宝数不超过 $1000$ 块。

对于 $100\%$ 的数据，$1\le t\le 2$，$1\le n \le 1000$，$1\le m \le 1000$，每个格子中的财宝不超过 $10^6$ 块。


---

---
title: "[SHOI2008] 汉诺塔"
layout: "post"
diff: 省选/NOI-
pid: P4285
tag: ['递推', '2008', '各省省选', '递归', '上海', '线性递推']
---
# [SHOI2008] 汉诺塔
## 题目描述

汉诺塔由三根柱子（分别用A、B、C表示）和n个大小互不相同的空心盘子组成。一开始n个盘子都摞在柱子A上，大的在下面，小的在上面，形成了一个塔状的锥形体。
    对汉诺塔的一次合法的操作是指：从一根柱子的最上层拿一个盘子放到另一根柱子的最上层，同时要保证被移动的盘子一定放在比它更大的盘子上面（如果移动到空柱子上就不需要满足这个要求）。我们可以用两个字母来描述一次操作：第一个字母代表起始柱子，第二个字母代表目标柱子。例如，AB就是把柱子A最上面的那个盘子移到柱子B。汉诺塔的游戏目标是将所有的盘子从柱子A移动到柱子B或柱子C上面。
有一种非常简洁而经典的策略可以帮助我们完成这个游戏。首先，在任何操作执行之前，我们以任意的次序为六种操作（AB、AC、BA、BC、CA和CB）赋予不同的优先级，然后，我们总是选择符合以下两个条件的操作来移动盘子，直到所有的盘子都从柱子A移动到另一根柱子：
（1）这种操作是所有合法操作中优先级最高的；
（2）这种操作所要移动的盘子不是上一次操作所移动的那个盘子。
可以证明，上述策略一定能完成汉诺塔游戏。现在你的任务就是假设给定了每种操作的优先级，计算按照上述策略操作汉诺塔移动所需要的步骤数。

![](https://cdn.luogu.com.cn/upload/pic/21997.png)

## 输入格式

输入有两行。第一行为一个整数n（1≤n≤30），代表盘子的个数。第二行是一串大写的ABC字符，代表六种操作的优先级，靠前的操作具有较高的优先级。每种操作都由一个空格隔开。
## 输出格式

只需输出一个数，这个数表示移动的次数。我们保证答案不会超过10的18次方。
## 样例

### 样例输入 #1
```
3
AB BC CA BA CB AC
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
2
AB BA CA BC CB AC
```
### 样例输出 #2
```
5
```
## 提示

对于20%的数据，n ≤ 10。
对于100%的数据，n ≤ 30。


---

---
title: "[国家集训队] 整数的lqp拆分"
layout: "post"
diff: 省选/NOI-
pid: P4451
tag: ['递推', '斐波那契数列', '生成函数', '线性递推']
---
# [国家集训队] 整数的lqp拆分
## 题目背景

来源：2011中国国家集训队命题答辩
## 题目描述

lqp在为出题而烦恼，他完全没有头绪，好烦啊…

他首先想到了整数拆分。整数拆分是个很有趣的问题。给你一个正整数 $N$ ，对于N的一个整数拆分就是满足任意 $m>0$，$a_1 ,a_2 ,a_3…a_m>0$，且 $a_1+a_2+a_3+…+a_m=n$ 的一个有序集合。通过长时间的研究我们发现了计算对于 $n$ 的整数拆分的总数有一个很简单的递推式，但是因为这个递推式实在太简单了，如果出这样的题目，大家会对比赛毫无兴趣的。  

然后 lqp 又想到了斐波那契数。定义 $F_0=0,F_1=1,F_n=F_{n-1}+F_{n-2} (n>1)$，$F_n$就是斐波那契数的第$n$项。但是求出第 $n$ 项斐波那契数似乎也不怎么困难…

lqp 为了增加选手们比赛的欲望，于是绞尽脑汁，想出了一个有趣的整数拆分，我们暂且叫它：整数的lqp拆分。

和一般的整数拆分一样，整数的 lqp 拆分是满足任意 $m>0$，$a_1 ,a_2 ,a_3…a_m>0$，且 $a_1+a_2+a_3+…+a_m=n$ 的一个有序集合。但是整数的lqp拆分要求的不是拆分总数，相对更加困难一些。

对于每个拆分，lqp 定义这个拆分的权值 $F_{a_1}F_{a_2}…F_{a_m}$，他想知道对于所有的拆分，他们的权值之和是多少？

简单来说，就是求  
$\sum\prod_{i=1}^m F_{a_i}$   
$m>0$    
$a_1,a_2...a_m>0$   
$a_1+a_2+...+a_m=n$     
由于答案可能非常大，所以要对 $10^9 + 7$ 取模。
## 输入格式

输入的第一行包含一个整数 $n$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
5
```
## 提示

【数据范围】  
对于 $60\%$ 的数据，$1\le n \le 10^9$；  
对于 $100\%$ 的数据，$1\le n \le 10^{10000}$。

【样例解释】  
$F_0=0,F_1=1,F_2=1,F_3=2$。

对于 $n=3$，有这样几种 lqp 拆分：

$3=1+1+1$，权值是 $F_1\times F_1\times F_1=1\times1\times1=1$

$3=1+2$，权值是 $F_1\times F_2=1\times1=1$

$3=2+1$，权值是 $F_2\times F_1=1\times1=1$

$3=3$，权值是 $F_3=2$

所以答案是 $1+1+1+2=5$


---

---
title: "[FJOI2016] 建筑师"
layout: "post"
diff: 省选/NOI-
pid: P4609
tag: ['数学', '递推', '2016', '各省省选', '福建', '线性递推']
---
# [FJOI2016] 建筑师
## 题目描述

小 Z 是一个很有名的建筑师，有一天他接到了一个很奇怪的任务：在数轴上建 $n$ 个建筑，每个建筑的高度是 $1$ 到 $n$ 之间的一个整数。

小 Z 有很严重的强迫症，他不喜欢有两个建筑的高度相同。另外小 Z 觉得如果从最左边（所有建筑都在右边）看能看到 $A$ 个建筑，从最右边（所有建筑都在左边）看能看到 $B$ 个建筑，这样的建筑群有着独特的美感。现在，小 Z 想知道满足上述所有条件的建筑方案有多少种？

如果建筑 $i$ 的左(右)边没有任何建造比它高，则建筑 $i$ 可以从左(右)边看到。两种方案不同，当且仅当存在某个建筑在两种方案下的高度不同。
## 输入格式

第一行一个整数 $T$，代表 $T$ 组数据。
接下来 $T$ 行，每行三个整数 $n,A,B$。
## 输出格式

对于每组数据输出一行答案 $\text{mod } 10^9+7$。
## 样例

### 样例输入 #1
```
2
3 2 2
3 1 2
```
### 样例输出 #1
```
2
1
```
## 提示

对于 $10 \%$ 的数据 ： $1 \leq n \leq 10$。

对于 $20 \%$ 的数据 ： $1 \leq n \leq 100$。

对于 $40 \%$ 的数据 ： $1 \leq n \leq 50000, \ 1 \leq T \leq 5$。

对于 $100 \%$ 的数据 ：$1 \leq n \leq 50000, \ 1 \leq A, B \leq 100, \ 1 \leq T \leq 200000$。


---

---
title: "黑暗打击"
layout: "post"
diff: 省选/NOI-
pid: P4967
tag: ['2018', 'O2优化', '矩阵加速', '线性递推', '构造']
---
# 黑暗打击
## 题目背景

注，此题和 CQOI 的鼹鼠不一样，请仔细看题！本题只是借用背景！

在茫茫宇宙中……
## 题目描述

有一群生物 ccj，他们在上次的星系中，发现了一群低等生物，于是想进行一波黑暗森林打击。这群低等生物即是 $\mathsf{Hilbert}$ 鼹鼠，生活在 $\mathsf{Hilbert}$ 星球，住在 $\mathsf{Hilbert}$ 曲线土壤内。  
这群生物决定用最傻的办法——灌水，来淹死他们。现在“高等”生物想知道，对于 $n$ 阶的 $\mathsf{Hilbert}$ 曲线，从上往下灌水，能淹没几个单位面积？

这是 $1 \sim 4$ 阶的 $\mathsf{Hilbert}$ 曲线：  

![](https://cdn.luogu.com.cn/upload/pic/28912.png)

$h_1$，如最左图所示，是一个缺上口的正方形，这个正方形的边长为 $1$。 从$h_2$ 开始，按照以下方法构造曲线 $h_i$： 将 $h_{i-1}$ 复制四份，按 $2\times2$ 摆放。  
把左上一份逆时针转 $90^{\circ }$，右上一份顺时针转 $90^{\circ }$，然后用三条单位线段将四分曲线按照左上-左下-右下-右上的顺序连接起来。如图所示，分别展示的是 $h_2$，$h_3$，$h_4$。加粗的线段是额外用于连接的线段。

灌水方式：

（显然这个是 $h_3$ 的灌水面积）绿色即为无法被灌到的地方，红色为可以灌到的地方，灰色为墙，所以答案是 $26$，即为样例1。

![](https://cdn.luogu.com.cn/upload/pic/40229.png)

一个方格有水当且仅当在它的上，左，右方格中有至少一个方格有水，最上面一层的空格都有水。

注，此题要求对 $9223372036854775783$ 取模
## 输入格式

一个整数 $n$，表示这个洞穴是 $n$ 阶的 $\mathsf{Hilbert}$ 曲线。
## 输出格式

一个整数 $ans$，表示有 $ans$ 个单位面积被淹没。
## 样例

### 样例输入 #1
```
3

```
### 样例输出 #1
```
26

```
### 样例输入 #2
```
4

```
### 样例输出 #2
```
100

```
### 样例输入 #3
```
12
```
### 样例输出 #3
```
2137408
```
## 提示

**样例解释：**

自己数一数嘛……

$n \le 10^{10000}$

详细范围参见“标程”

数据均为手动构造，请注意常数！


---

---
title: "[MtOI2019] 幻想乡数学竞赛"
layout: "post"
diff: 省选/NOI-
pid: P5517
tag: ['数学', '2019', '洛谷原创', 'O2优化', '矩阵加速', '生成函数', '线性递推']
---
# [MtOI2019] 幻想乡数学竞赛
## 题目背景

一年一度的幻想乡数学竞赛 (thMO) 又要开始了。

幻想乡中学习数学的少 (lao) 女 (tai) 们 (po) 和冰之妖精 baka 一起准备着 thMO。

但是在那一刻，幻想乡日复一日的宁静被打破了。

广播里，播放起了死亡的歌曲！

在那一刻，人们又回想起了被算数支配的恐惧。  

就剩下 baka，baka，baka，baka 的声音在幻想乡里回荡。  
 

---  

河城 荷取 (Kawashiro Nitori) 正坐在 thMO2019 的考场上！  
因为荷取有着她的[超级计算机](https://www.luogu.org/problemnew/show/P4911)，在成功地用光学迷彩覆盖了计算机之后，荷取在 thMO2019 的考场上所向披靡。  

* 荷取用她的超级计算机 $0 \,\mathrm{ms}$ 跑出了这么一道题：  

  * $\exists \{ a_n\} (n=0,1,\cdots ,10^{18})$，已知 $a_0=2,a_1=5,a_{n+2}=3a_{n+1}-2a_n$，求 $a_n\bmod 10^{9}+7$

* 荷取：显然，这个题可以用矩阵乘法 + 快速幂，可以 $O(\log n)$ 水过去，差不多就这样：

$$
\begin{bmatrix} a_n & a_{n+1} \end{bmatrix}=\begin{bmatrix} a_0 & a_1 \end{bmatrix} \times \begin{bmatrix} 3 & 1 \\ -2 & 0 \end{bmatrix}^n
$$      
  
但是荷取遇到了一道她不会的题，她正在寻求你的帮助呢！ 
## 题目描述

存在一个数列 $\{ a_n\} (n\in \{ 0,1,2,\cdots ,2^{64}-1\} )$。  
已知 $a_0=-3,a_1=-6,a_2=-12,a_n=3a_{n-1}+a_{n-2}-3a_{n-3}+3^n$。  

* 现在给你一个非负整数 $n$ ，令 $p=10^{9}+7$，请你求出 $a_n \bmod p$。 

* **注：若 $a_n<0$ ，请输出 $(a_n \bmod p+p)\bmod p$。**    
  
  
为了更充分地考验你的水平，荷取设置了 $T$ 组询问。

* 为了在某种程度上减少你的输入和输出量，我们采用以下的代码来生成询问：  
  
```cpp
namespace Mker
{
//  Powered By Kawashiro_Nitori
//  Made In Gensokyo, Nihon
	#include<climits>
	#define ull unsigned long long
	#define uint unsigned int
	ull sd;int op;
	inline void init() {scanf("%llu %d", &sd, &op);}
	inline ull ull_rand()
	{
		sd ^= sd << 43;
		sd ^= sd >> 29;
		sd ^= sd << 34;
		return sd;
	}
	inline ull rand()
	{
		if (op == 0) return ull_rand() % USHRT_MAX + 1;
		if (op == 1) return ull_rand() % UINT_MAX + 1; 
		if (op == 2) return ull_rand();
	}
}
```  

在调用 `Mker::init()` 函数之后，你第 $i$ 次调用 `Mker::rand()` 函数时返回的便是第 $i$ 次询问的 $n_i$。

在这里给出 $op$ 的限制：

* 如果 $op=0$，满足 $n_i \leq 2^{16}$。

* 如果 $op=1$，满足 $n_i \leq 2^{32}$。

* 如果 $op=2$，满足 $n_i \leq 2^{64}-1$。

为了减少你的输出量，你只需要输出所有询问答案的**异或和**。




## 输入格式

第一行三个整数，输入 $T$ ， $seed$ 和 $op$。
## 输出格式

第一行一个整数，输出 $T$ 组询问的答案的**异或和**。  
## 样例

### 样例输入 #1
```
142857 1145141919 0
```
### 样例输出 #1
```
562611141
```
### 样例输入 #2
```
142857 1145141919 1
```
### 样例输出 #2
```
894946216
```
### 样例输入 #3
```
142857 1145141919 2
```
### 样例输出 #3
```
771134436
```
## 提示

### 子任务  

![png](https://i.loli.net/2019/04/19/5cb9bb2c6c1d6.png)  

### 题目来源

[迷途之家 2019 联赛](https://www.luogu.org/contest/20135)(MtOI2019) T4

出题人：disangan233

验题人：suwakow



---

