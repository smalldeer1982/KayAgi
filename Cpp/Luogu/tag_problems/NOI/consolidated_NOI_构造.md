---
title: "「FAOI-R2」Program of atom(x) 2027"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10038
tag: ['动态规划 DP', '2024', '洛谷原创', 'Special Judge', 'O2优化', '区间 DP', '构造']
---
# 「FAOI-R2」Program of atom(x) 2027
## 题目背景

这是来自 $2027$ 年的 FAOI 的一道题目，是一道带有 SPJ 的传统题。

------------

自从 [krjt](https://www.luogu.com.cn/user/691537) 上次被 $160$ 人 [JC](https://www.luogu.com.cn/problem/T269289) 后，他换了一个「量子密码锁」，并用它锁上了自己的电脑包——打不开密码锁，就取不出包里的电脑。理论上，一旦 krjt 忘了密码，就连造这把锁的人也打不开。

然而，这把锁并非固若金汤。~~有一天，krjt 突然对化学产生了浓厚的兴趣。他拿起那把锁，放在酒精灯上加热，结果发现：~~ 在高温环境下，这把锁内的原子（严格来说是「离子」，下同）排布变得不稳定，这将导致它瘫痪。
## 题目描述

krjt 找来了密码锁的说明书：

> 在密码锁中，有一条长度为 $n$（不能更改，$n$ 的具体取值见密码锁铭牌）的链，链上共有 $n$ 个结点。每个结点上可以存放至多一个原子。初始时，$1,2,\ldots,n$ 号原子以某个顺序（可以由用户自行调整）被存放在其中，每个结点存放一个原子。
> 
> 定义 $i$ 号原子的电荷量为 $i!=1 \times 2\times 3 \times \ldots \times i$。
> 
> 现有一个计时器 $b$（单位为秒），其初值为 $0$。
>
> 密码锁被加热后，以下事件**依次循环发生**，直至达成终止条件：
> 
> 1. 位于链两端的原子被移除（**这不会使链变短**），**不再对后续事件产生影响**；
> 2. 判定终止条件：
>    - 若此时链中剩下**不多于 $1$ 个**原子（**也可以是 $0$ 个**），则**达成终止条件**，密码锁瘫痪（**此时计时器 $b$ 的值不会增加 $1$**）；
>    - 否则，将计时器 $b$ 的值增加 $1$。
> 3. 给每个原子标定运动方向（**标定的运动方向是临时的，只生效一次，在下一次标定前会被重置**）：
>    - 计算它左边所有原子的电荷量之和，设计算结果为 $x$；
>    - 计算它右边所有原子的电荷量之和，设计算结果为 $y$；
>    - 如果 $x<y$，则标定方向为「向左」；
>    - 如果 $x>y$，则标定方向为「向右」；
>    - 可以证明，$x \ne y$。
> 4. 所有原子按照所标定的运动方向，移动一条边的距离，来到相邻的结点。

此外，krjt 从铭牌上读取到了 $n$ 的值。

krjt 定义，密码锁的瘫痪用时，为它瘫痪时 $b$ 的值。当然，krjt 希望密码锁尽量安全，因此他想**最大化密码锁的瘫痪用时**。

~~为了不让更多人再次 JC krjt~~，请问：他该如何排列密码锁中 $n$ 个原子的初始顺序？
## 输入格式

一行一个正整数，$n$。
## 输出格式

一行 $n$ 个正整数，一个 $1 \sim n$ 的排列，表示你给 krjt 规划的排列方案：从左到右（或者从右到左，可以证明它们的瘫痪用时相等）依次输出 $n$ 个原子的编号。

**答案可能有多个，输出一个即可。**
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
2
```
### 样例输出 #2
```
1 2
```
### 样例输入 #3
```
3
```
### 样例输出 #3
```
2 1 3
```
### 样例输入 #4
```
4
```
### 样例输出 #4
```
4 2 3 1
```
### 样例输入 #5
```
5
```
### 样例输出 #5
```
5 4 1 2 3
```
### 样例输入 #6
```
6
```
### 样例输出 #6
```
2 4 5 1 6 3
```
## 提示

**样例解释：**

$6$ 个样例的瘫痪用时分别为 $0,0,0,1,1,2$ 秒。

实际上，枚举可知：当 $n \le 6$ 时，输出任何一个 $1 \sim n$ 的排列都能 AC。

下面对样例 $6$ 进行模拟。在链的描述中：

- $0$ 表示该结点为空；
- $i$ 表示该结点上存放着 $i$ 号原子；
- $(x,y)$ 为计算结果。

1. **初始的链**为 $\color{blue}2-4-5-1-6-3$；
2. $b$ 初始为 $0$；
3. **位于两端的原子被移除**，链变为 $\color{blue}0-4-5-1-6-0$；
4. $b$ 增加至 $1$；
5. **计算**，$4$ 个原子（从左向右）的结果分别为 $(\color{red}0\color{black},841),(\color{red}24\color{black},721),(\color{red}144\color{black},720),(145,\color{red}0\color{black})$；
6. 根据结果，左边 $3$ 个原子（$4,5,1$）**向左运动**，最右边的原子（$6$）**向右运动**，链变为 $\color{blue}4-5-1-0-0-6$；
7. **位于两端的原子被移除**，链变为 $\color{blue}0-5-1-0-0-0$；
8. $b$ 增加至 $2$；
9. **计算**，$2$ 个原子（从左向右）的结果分别为 $(\color{red}0\color{black},1),(120,\color{red}0\color{black})$；
10. 根据结果，左边的原子（$5$）**向左运动**，右边的原子（$1$）**向右运动**，链变为 $\color{blue}5-0-0-1-0-0$；
11. **位于两端的原子被移除**，链变为 $\color{blue}0-0-0-1-0-0$；
11. 此时链中只剩下 $1$ 个原子（$1$），**反应结束，密码锁瘫痪**。

综上，样例 $6$ 的瘫痪用时为 $2$ 秒。

------------

本题共 $100$ 个测试点，分别有 $n=1,2,\ldots,100$，每个 $1$ 分。

对于 $100\%$ 的数据，$1 \le n \le 100$。


---

---
title: "[THUPC 2024 决赛] 采矿"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10546
tag: ['2024', '交互题', 'Special Judge', '随机化', '构造', 'THUPC']
---
# [THUPC 2024 决赛] 采矿
## 题目背景

在精心地规划完工人的移动路线，执行完所有计划之后，你终于有钱了。你承包下了一个更大的矿坑，并购买了更先进的设备。

但是开始运行了你才发现，一部分运输矿物的通道居然装反了！还好它们本来就是可以反向的，并且中控的系统可以让你轻易地操作。

然而，现在最大的问题是，你刚刚接手这个矿坑，你甚至连它长什么样都不知道，也就更不知道每个开关是对应哪一条运输通道的。

时间就是金钱，你想要尽快摸清整个矿坑的结构以及所有开关与通道的对应关系。
## 题目描述

**这是一道交互题。**

已知你的矿坑有 $n$ 个节点，编号为 $1\sim n$。它们通过 $n-1$ 条运输通道连成一个树形结构。

运输通道都是单向的。对于一条从节点 $u$ 到节点 $v$ 的运输通道，可以将所有由节点 $u$ 产出的矿或运送到节点 $u$ 的矿以较快的速度运送到节点 $v$。如果一个节点有多条以其为起点的运输通道，那么会把这些矿平均分配给这些运输通道。

中控的系统包含 $n-1$ 个开关和一个监视器。开关的编号为 $1\sim n-1$，每个开关可以拨到 $0$ 或 $1$ 的位置。$n-1$ 个开关和 $n-1$ 条运输通道一一对应，但你并不知道它们的对应关系。你只知道，假设编号为 $i$ 的开关对应的运输通道在被装上去时是从 $u_i$ 到 $v_i$ 的，那么当开关拨到 $0$ 的时候，它的运输方向和它被装上去时相同；当开关拨到 $1$ 的时候，它的运输方向会变成从 $v_i$ 到 $u_i$。你的监视器可以监控到达每个节点的矿分别来自多少个不同的节点，也就是说，有多少个节点（包括其本身）能够通过运输通道把矿运输到这个节点。

当你调整完开关的位置后，需要等一段时间，监视器的结果才会趋于稳定，这时你的读数才是有意义的。所以为了避免浪费太多时间，你希望在 $50$ 次读数之内确定你想知道的所有信息。
## 输入格式

开始时你需要输入一个正整数 $n$。保证 $2\le n \le 10000$。

之后的输入会基于你的输出生成读数。你的读数结果是一行 $n$ 个正整数，其中第 $i$ 个表示到达节点 $i$ 的矿来自多少个不同的节点。

每个测试点中，矿坑的连接方式和所有运输通道刚装上去时的方向都是固定的，也就是说，这些不会因为你的输出而动态修改为另外一种符合之前所有回答的方案。
## 输出格式

当你需要调整开关并等待读数时，输出一行 `? s`，其中 `s` 为一个长为 $n-1$ 的 `01` 串，其中第 $i$ 位表示编号为 $i$ 的开关拨到的位置。然后交互库会在你的标准输入中给出监视器趋于稳定之后的读数结果。你最多只能读数 $50$ 次。

当你已经知道了所有通道的信息时，输出一行 `! u1 v1 ... un-1 vn-1`，其中 $u_i,v_i$ 表示编号为 $i$ 的开关对应的运输通道被装上去时的方向是从节点 $u_i$ 到节点 $v_i$ 的。

在输出一行之后，你需要刷新输出缓冲区，否则评测结果可能会变成 `TLE`。刷新输出缓冲区的方式为：

- C：`fflush(stdout);`

- C++：`fflush(stdout);` 或 `std::cout.flush();` 或使用 `std::endl` 换行

- Java：`System.out.flush();`

- Python：`sys.stdout.flush()`

## 样例

### 样例输入 #1
```
5

1 4 1 2 3

1 1 2 3 4
```
### 样例输出 #1
```

? 0110

? 0000

! 1 4 2 3 2 4 4 5
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/fuc2u4d1.png)

通道的初始方向如上图所示。通道上的数字代表和通道对应的开关的编号。

样例只是用来说明输入输出格式和读数结果，并不意味着这次读数能够推出答案。


交互库的运行时间和内存不计入时间和内存限制。

若超出读数次数限制、最后的回答错误或输出格式错误，评测结果均为 `WA`。


**来源与致谢**

来自 THUPC2024（2024年清华大学学生程序设计竞赛暨高校邀请赛）决赛。感谢 THUSAA 的提供的题目。

数据、题面、标程、题解等请参阅 THUPC 官方仓库 <https://thusaac.com/public>




---

---
title: "[COTS 2023] 平均数 Prosjek"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10830
tag: ['2023', '数论', 'Special Judge', 'O2优化', '构造', 'COCI（克罗地亚）']
---
# [COTS 2023] 平均数 Prosjek
## 题目背景



译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D1T2。$\texttt{3s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）

感谢 @Rainbow_qwq 修复交互库。警示后人：慎用 `multiset.count`（复杂度可退化至线性）。

## 题目描述


在黑板上有 $N$ 个非负整数。在一次操作中，可以选择黑板上的两个整数 $a,b$ 满足 $2\mid (a+b)$，将 $a,b$ 从黑板上擦去，然后写下 $(a+b)/2$。注意到每次操作后，黑板上的数都是整数。

试判断是否能让黑板上只剩下一个数。如果可以的话，还需要给出一组解。

## 输入格式


**本题单个测试点内有多组测试数据。**

第一行，一个正整数 $T$，代表数据组数。

接下来依次描述 $T$ 组数据。

对于每组数据，第一行，一个正整数 $N$，代表黑板上数的数量。

第二行，$N$ 个非负整数，描述黑板上的数。

## 输出格式


对于每组数据，输出若干行。

如果不可行，输出一行一个 $\texttt{-1}$；

否则，输出 $(N-1)$ 行，每行两个整数，表示每次要擦除的数。你需要保证操作的数是存在的，且它们的和能被 $2$ 整除。

## 样例

### 样例输入 #1
```
2
3
1 4 5
4
1 4 5 5
```
### 样例输出 #1
```
-1
1 5
3 5
4 4
```
### 样例输入 #2
```
1
6
1 2 3 4 5 6
```
### 样例输出 #2
```
1 5
3 3
4 6
3 5
2 4
```
## 提示


#### 样例解释

样例 $2$ 解释：$[\boldsymbol{\textcolor{red}{1}},2,3,4,\boldsymbol{\textcolor{red}{5}},6] \to [\boldsymbol{\textcolor{red}{3}},2,\boldsymbol{\textcolor{red}{3}},4,6]\to [3,2,\boldsymbol{\textcolor{red}{4}},\boldsymbol{\textcolor{red}{6}}]\to [\boldsymbol{\textcolor{red}{5}},\boldsymbol{\textcolor{red}{3}},2]\to [\boldsymbol{\textcolor{red}{4}},\boldsymbol{\textcolor{red}{2}}]\to [3]$。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le T\le 10^5$；
- $1\le N,\sum N\le 10^6$；
- $0\le a_i\le 10^{18}$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $9$  | $T\le 100$，$N\le 7$   |
| $2$  | $23$  | $T\le 100$，$a_i\le 10$  |
| $3$  | $16$  | $a_i$ 都为偶数 |
| $4$  | $52$  | 无额外约束 |





---

---
title: "[COTS 2022] 旅程 Dugput（非官方数据）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10874
tag: ['2022', 'Special Judge', 'O2优化', '构造', 'COCI（克罗地亚）']
---
# [COTS 2022] 旅程 Dugput（非官方数据）
## 题目背景

译自 [Izborne Pripreme 2022 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2022/) D2T1。$\texttt{5s,0.5G}$。


- **输入格式有微调。**
- **官方数据有误。** 部分 out 文件是使用树姐姐 [	
hhoppitree](https://www.luogu.com.cn/user/183609) 的代码生成的。如果出现了分数 $\gt 100$ 的情况，欢迎联系搬题人更新数据。

## 题目描述


构造一个 $N\times M$ 的网格图，边权均为 $1$，每条边可以存在或者不存在。

在连通的前提下，最大化 $(A,B)$ 到 $(C,D)$ 的最短路长度。

**此处路径长度定义为路径经过的节点个数。**
## 输入格式

**本题单个测试点内含有多组测试数据。**

第一行，两个整数 $\mathrm{type},T$，表示测试数据类型和测试数据组数。

接下来 $T$ 行，每行 $6$ 个整数 $N,M,A,B,C,D$，含义见题面。
## 输出格式

每组测试数据输出若干行。

- $\mathrm{type}=0$：「构造」类数据

此类数据中，你需要构造一个网格图。输出 $(2N-1)$ 行，每行 $(3M-2)$ 个字符。

其中，第 $(2i-1)$ 行的第 $(3j-2)$ 个字符代表点 $(i,j)$。当 $(i,j)=(A,B)$ 或 $(S,T)$ 时，用 `*`（ASCII 42）表示；否则用 `o`（ASCII 111）表示。

对于同一行的两个点 $(i,j),(i,j+1)$，若有边，则用 `--`（ASCII 45）填充它们之间的两个空格；否则不填充。

对于同一列的两个点 $(i,j),(i+1,j)$，若有边，则用 `|`（ASCII 124）填充它们之间的一个空格；否则不填充。

未填充的区域均用空格补齐。不要输出多余的空格和空行。

可参阅样例输出。

- $\mathrm{type}=1$：「传统」类数据

只需要输出一行一个整数，表示最短的最长路长度。
## 样例

### 样例输入 #1
```
0 2
2 3 1 1 2 2
3 3 1 1 3 3
```
### 样例输出 #1
```
*--o--o
      |
o  *--o
*  o--o
|  |  |
o  o  o
|  |  |
o--o  *
```
### 样例输入 #2
```
0 2
2 3 1 1 2 2
3 3 1 1 3 3
```
### 样例输出 #2
```
*--o  o
   |
o  *  o
*  o  o
|
o  o--o
|  |  |
o--o  *
```
### 样例输入 #3
```
1 2
2 3 1 1 2 2
3 3 1 1 3 3
```
### 样例输出 #3
```
5
9
```
## 提示



对于 $100\%$ 的数据，保证：

- $1\le N,M\le 5\, 000$；
- $1\le T\le 1\, 600$；
- $1\le A,C\le N$，$1\le B,D\le M$；
- $(A,B)\neq (C,D)$。

| 子任务编号 | $N\cdot M\in $ | $M\le $ | $\mathrm{type}=$ | 分值 | 
|:-----:|:------:| :----: | :--: | :--: |
| $1$  | $[2,100]$  | $5\, 000$ | $0$ | $20$ | 
| $2$  | $[2,1\, 000]$  | $5\, 000$  | $0$ | $25$ |
| $3$  | $[2,15\, 000]$  | $3$  | $0$ | $15$ |
| $4$  | $[2,100\, 000]$  | $5\, 000$  | $0$ | $25$ | 
| $5$  | $[2,100\, 000]$  | $5\, 000$  | $1$ | $15$ |

【评分方式】


- $\mathrm{type}=0$：「构造」类数据

记 $d_i$ 为第 $i$ 组测试数据中，你构造的方案中的最短路长度，$D_i$ 为可能的最长最短路长度。记

$$K=\frac{1}{Q}\sum_{i=1}^Q\frac{d_i}{D_i}$$

当 $K=1$ 时，该测试点得满分；否则得 $0.7\cdot K$ 倍测试点得分的分数。

每个子任务的得分为所有测试点得分的 $\min$。

例如，样例 $1$ 的输出得满分；对于样例 $2$，$\displaystyle k=\frac{1}{2}\left(\frac{3}{5}+\frac{5}{9}\right)=\frac{31}{45}$，将得到 $\displaystyle 0.7\cdot \frac{31}{45}\approx 0.482$ 倍测试点得分的分数。

- $\mathrm{type}=1$：「传统」类数据

和传统题评分方式相同。




---

---
title: "[COTS 2021] 菜 Jelo"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11192
tag: ['2021', '提交答案', 'Special Judge', 'O2优化', '群论', '线性代数', '位运算', '构造', 'COCI（克罗地亚）']
---
# [COTS 2021] 菜 Jelo
## 题目背景

译自 [Izborne Pripreme 2021 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2021/) D1T1。$\texttt{1s,0.5G}$。

由于本题特殊的 SPJ，将本题的 TL 和 ML 分别改为 $\texttt{10s,2G}$。但是对于选手程序，本题的时空限制和原题相同。

如果使用压缩包上传答案：将文件分别命名为 $\texttt{jelo-1.out}\sim \texttt{jelo-5.out}$。
## 题目描述

给定正偶数 $N$。构造一个最大的集合 $S\subseteq \{0,1,\cdots,2^{N}-1\}$，使得 $\left|\bigcup_{i,j\in S,i\lt j} \{i\oplus j\}\right|={|S|\choose 2}$ 。换言之，在 $S$ 中任意选定 $(a,b),(c,d)$（$a,b,c,d\in S$，$a\lt b$，$c\lt d$，$(a,b)\neq (c,d)$），都有 $a\oplus b\neq c\oplus d$ 成立。

其中 $\oplus$ 表示按位异或运算。
## 输入格式

一行一个正整数 $N$。
## 输出格式

第一行一个整数 $|S|$。

接下来 $|S|$ 个数描述 $S$。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
6
0 1 2 4 8 15
```
## 提示


对于 $100\%$ 的数据，保证 $1\le N\le 30$。

本题共有 $5$ 个测试点，每个测试点有三个评分参数 $t_1,t_2,t_3$，记 $t=|S|$，则得分计算方式为：

$$\mathrm{score}(t)=
\begin{cases}
2.4\cdot \frac{t}{t_1} & t\in [0,t_1) \\
2.4+3.6\cdot \frac{t-t_1}{t_2-t_1} & t\in [t_1,t_2) \\
6+12\cdot \frac{t-t_2}{t_3-t_2} & t\in [t_2,t_3) \\
20 & t\in [t_3,2^N] \\
\end{cases}$$

| 测试点编号 | $N=$ | $t_1=$   | $t_2=$   | $t_3=$    | 得分 |  
| :--: | :--: | :--: | :--: | :--: | :--: |  
| $ 1 $    | $ 18 $    | $ 267 $   | $ 283 $   | $ 512 $    | $ 20 $   |  
| $ 2 $    | $ 20 $    | $ 444 $   | $ 462 $   | $ 1024 $   | $ 20 $   |  
| $ 3 $    | $ 26 $    | $ 2019 $  | $ 2040 $  | $ 8192 $   | $ 20 $   |  
| $ 4 $    | $ 28 $    | $ 3295 $  | $ 3327 $  | $ 16384 $  | $ 20 $   |  
| $ 5 $    | $ 30 $    | $ 5377 $  | $ 5430 $  | $ 32768 $  | $ 20 $   |

【提示】请注意代码长度限制。


---

---
title: "[Code+#8 决赛] 生成树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11436
tag: ['2022', 'Special Judge', '构造', 'Ad-hoc', 'Code+']
---
# [Code+#8 决赛] 生成树
## 题目背景

搬运自 [Code+ #8 决赛](https://gitlink.org.cn/thusaa/codeplus8final)。
## 题目描述

小 I 既喜欢生成树，又喜欢他的幸运数字 $k$，所以小 I 想造出一个**可以有重边自环**的有向图，点从 $1$ 到 $n$ 编号，使得以 $1$ 为根的**外向**生成树数量**恰好**为 $k$。但小 I 太穷了，手边只有 100 条有向边，所以他请求你的帮助，请你帮他造出这样的一个有向图，或者告诉他这是不可能的。
## 输入格式

**本题有多组测试数据。**

输入的第一行包含一个正整数 $q$，表示询问次数。接下来 $q$ 行每行包含一个正整数 $k$，描述一次询问。
## 输出格式

对于每次询问，若不存在方案，只需要输出一行一个整数 `-1`。否则输出多行：第一行两个整数 $n,m$，分别表示你给出的有向图的点数和边数，你需要保证 $1 \le n \le 101, 0 \le m \le 100$。接下来 $m$ 行，第 $i$ 行两个整数 $u_i,v_i$，表示一条从 $u_i$ 到 $v_i$ 的有向边。你需要保证 $1 \le u_i, v_i \le n$。
## 样例

### 样例输入 #1
```
2
1
7
```
### 样例输出 #1
```
1 0
3 6
1 2
1 2
2 3
2 3
1 3
3 2
```
## 提示

**【数据范围】**

对于所有数据，$1 \le q \le 100$，$1 \leq k \le 7 \times 10^{15}$。

本题采用 $\text{Subtask}$ 捆绑测试。

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$3$|$k\le100$|
|$2$|$7$|存在整数 $0 \le a,b \le 20$ 使得 $k = 2^a3^b$|
|$3$|$10$|$q=1, k = 101$|
|$4$|$10$|$k \le 10^3$|
|$5$|$7$|$k \le 10^4$|
|$6$|$7$|$k \le 10^6$|
|$7$|$8$|$k \le 3 \times 10^7$|
|$8$|$8$|$k \le 8 \times 10^9$|
|$9$|$10$|$k \le 10^{12}$|
|$10$|$10$|$k \le 3 \times 10^{14}$|
|$11$|$20$|$k \le 7 \times 10^{15}$|


---

---
title: "【MX-X7-T7】[LSOT-3] 魔女与推理的轮舞曲"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11566
tag: ['O2优化', '最大公约数 gcd', '线性基', '构造', 'Ad-hoc', '分类讨论', '梦熊比赛']
---
# 【MX-X7-T7】[LSOT-3] 魔女与推理的轮舞曲
## 题目背景

原题链接：<https://oier.team/problems/X7H>。

>魔女展示了空着的左手。$\\$
把左手握上，向着那边，嘿嘿嘿。$\\$
然后打开右拳，手心里有个糖球。$\\$
那么，这是魔法呢？还是戏法呢？
## 题目描述

黄金乡中，贝阿朵和战人在新的棋盘上展开的红蓝论战，这个棋盘的规则与之前的有所不同。

具体地说，有初始全 $0$ 的一个 $n\times m$ 的棋盘（格子数为 $n\times m$），可以在棋盘上使用红色真实和蓝色真实。红色真实和蓝色真实都各代表一个矩形，分别是 $a\times b$ 和 $c\times d$，使用红色真实或蓝色真实，要选择棋盘上一个格子，然后将以这个格子为左上角的那个使用的真实所对应的矩形内的所有格子异或 $1$（如果超出棋盘则不能选择此格子）。

贝阿朵想测试一些规则是否符合她的心意，所以她会问你对于某个规则，通过使用任意次红色真实与蓝色真实可以构筑出多少种不同的棋盘。

由于答案可能过大，你仅需输出对 $10^9+7$ 取模的结果即可，贝阿朵可以通过使用魔法来复原结果。
## 输入格式

第一行，一个正整数 $T$，表示贝阿朵想要测试的规则数量。

接下来 $T$ 行，每行六个正整数 $n, m, a, b, c, d$，含义与题目中的一致。
## 输出格式

对于每个贝阿朵想测试的规则，一行，一个非负整数，表示棋盘可能数对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
10
100 100 715 1129 123 654
3 3 1 1 2 2
4 4 2 2 3 3
4 3 4 3 3 2
20 50 15 12 10 7
50 20 33 11 25 3
107151129 147744151 715 715 1129 1129
23456 54321 1992 725 12347 7913
10000000 10000000 2222 444 3333 555
10000000 10000000 7130713 4237018 7812367 1245634

```
### 样例输出 #1
```
1
512
4096
32
248906884
412057510
710040542
936321181
222744797
17474728

```
## 提示

> 没有爱，就看不见。

**【样例解释】**

对于第一种规则，无法使用红色真实或蓝色真实，故只有全是 $0$ 一种情况。

对于第二种规则，每个格子都可以独立地取 $0$ 或 $1$，故答案为 $2^{3\times 3}=512$。

对于第三种规则，一种可能的局面是：

```
1100
1011
0100
0100
```

生成方式为选择第一行第一个格子使用红色真实，选择第二行第二个格子使用蓝色真实，选择第三行第三个格子使用红色真实。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（3 分）：$a\mid c$，$b\mid d$。
- 子任务 2（4 分）：$\sum n\times m\le 20$。
- 子任务 3（16 分）：$\sum n\times m\le 1000$。
- 子任务 4（17 分）：$a=b$，$c=d$。
- 子任务 5（19 分）：$a,b,c,d$ 中任意两个数的 $\gcd$ 都为 $1$。
- 子任务 6（20 分）：$100\times(a+b+c+d)\le  \min (n,m)$。
- 子任务 7（21 分）：无特殊性质。

对于全部的数据，$1\le T\le10^6$，$1\le n,m,a,b,c,d \le 10^9$。


---

---
title: "巅峰手速"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11773
tag: ['洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 巅峰手速
## 题目背景

“老妹儿啊，今天该你做家务吧……”

龙牙哥于是自愿体验了阿绫为他量身定制的游戏，把做家务的命运推上赌桌——
## 题目描述

阿绫给了龙牙哥 $n$ 张卡牌，它们已经整齐码在了桌上，从左至右第 $i$ 张的卡牌上的数字为 $a_i$，龙牙哥需要通过一系列操作让卡牌上的数字从左至右**不降**。每次操作中，他可以抽出从左至右第 $k$（$k$ 为给定常数）张卡牌，然后将它放在这些牌的最左侧或最右侧。请帮助龙牙判断自己是否有可能完成目标，如果能，请顺便告诉他一种比较简单的操作方案。
## 输入格式

首先输入一个整数 $T$，表示数据组数。

对于每组数据，输入两行：

第一行为两个整数 $n,k$，分别表示卡牌数量和给定常数。

第二行为 $n$ 个整数，第 $i$ 个数表示第 $i$ 卡片上的数字 $a_i$。
## 输出格式

对于每组数据，输出若干行。格式如下：

- 若龙牙哥无法完成目标，只输出一行 `No`。

- 若他能够完成目标，先输出一行 `Yes`，然后若干行形如 `l c` 或 `r c`，表示他连续做了 `c` 次将第 $k$ 张卡牌放到最左侧或最右侧的操作。最后再输出一个 `o`，表示操作结束。

你的得分将与**操作方案的行数**（而非**操作次数**）有关。（详见**得分计算方式**）
## 样例

### 样例输入 #1
```
5
3 2
3 2 1
7 3
4 1 3 2 5 7 6
3 3
2 1 3
7 5
1 2 3 4 5 6 7
6 4
1 1 4 5 1 4
```
### 样例输出 #1
```
Yes
l 1
r 1
l 1
o
No
No
Yes
o
Yes
r 1
l 1
o
```
## 提示

### 样例解释

对于第一组样例：

将第二张卡牌（$2$）放到最左侧，卡牌数字变为 $2,3,1$。  
将第二张卡牌（$3$）放到最右侧，卡牌数字变为 $2,1,3$。  
将第二张卡牌（$1$）放到最左侧，卡牌数字变为 $1,2,3$。

此时卡牌上的数字不降，操作结束。

### 得分计算方式

在一个测试数据中，是否有解判断正确可获得 $20\%$ 的分数。如果操作方案也正确，则会跟据操作方案的行数（不包含最后一行的 `o`）按下表得分。

| 行数 | 得分 |
| :-----------: | :-----------: |
| $>7n$ | $40\%$ |
| $\le7n$ | $60\%$ |
| $\le5n$ | $80\%$ |
| $\le3n$ | $100\%$ |

一个测试点的得分是其中每组测试数据得分的最小值。

### 注意事项

为了方便选手调试，本题下发了校验器用于本地自测校验得分，使用方法见后。需要注意下发的校验器与实际使用校验器的可能并不相同。我们保证实际使用的校验器在输出的操作序列行数不超过 $7n$ 的情况下用时不超过 500ms。

如果输出格式有误，你将会获得 $0$ 分。因此，如果你会判断是否有解但无法给出操作方案，也需要在判断有解后输出一行 `o` 表示操作结束。

为了避免无意义的反复操作，你需要保证每一次操作均有 $1\leq c \leq n$，否则将会获得 $0$ 分。

### 校验器使用方法

下载文件 `testlib.h` 与 `checker.cpp` 并将其置于同一文件夹。在该目录下运行命令 `g++ checker.cpp -o checker -std=c++14` 编译得到可执行文件 `checker.exe` (windows) / `checker` (linux)。

假如自测输入为 `in.txt`，程序输出为 `out.txt`。由于校验器无法判断是否有解，你需要创建一个答案文件（假如叫作 `ans.txt`），并在其中每行一个地写入每组数据的有解情况。例如对于样例，答案文件应为

```plain
Yes
No
No
Yes
Yes
```

将上述提到的输入、输出、答案三个文件与刚刚编译出来的校验器可执行文件置与同一文件夹。

- 如果是 Windows Powershell，输入 `.\checker.exe in.txt out.txt ans.txt`。

- 如果是 Linux 终端，输入 `./checker in.txt out.txt ans.txt`。

校验器有三种可能的输出：`wrong answer` / `ok` / `points x`，分别表示对于该测试点你没有分 / 满分 / 获得了占比为 `x` 的分。

### 数据规模与约定

**本题采用捆绑测试并开启所有合理的子任务依赖**

对于 $100\%$ 的数据，$1\le T\le10^5$，$1\le k\le n\le 2\times10^5$，$\sum n\le5\times10^{5}$，$1\le a_i\le 10^9$。

对于不同的子任务，作如下约定：

| 子任务编号	| $n$ | $k$ | 子任务分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $=5$ | $\in[1,n]$ | $10$ |
| $2$ | $\le200$ | $\in[1,n]$ | $40$ |
| $3$ | $\le2\times10^5$ | $=2$ | $20$ |
| $4$ | $\le2\times10^5$ | $\in[1,n]$ | $30$ |


---

---
title: "[THUPC 2025 决赛] 一个 01 串，n 次三目运算符，最后值为 1（加强版）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12294
tag: ['Special Judge', '状态合并', '有限状态自动机', '构造']
---
# [THUPC 2025 决赛] 一个 01 串，n 次三目运算符，最后值为 1（加强版）
## 题目背景

关于 $a,b,c$ 的三目运算表 $s_0s_1\cdots s_7$（$s$ 仅由 `0,1` 组成）的含义是，如果 $s$ 的第 $a+2b+4c$ 位为 `1`，那么返回 $1$，否则返回 $0$。

本题参考了 [[THUPC 2025 决赛] 一个 01 串，n 次三目运算符，最后值为 1](https://www.luogu.com.cn/problem/P12055)。
## 题目描述

给定运算表 $s$ 以及 $q$ 个长为 $2n+1$ 的 01 串，你需要对于对每个 01 串分别回答：

能否操作 $n$ 次，每次将三位连续的数字替换为所对应的运算值，使得运算的结果为 $1$，或判断无解。
## 输入格式

第一行为长度为 $8$ 的字符串 $s$ 以及给定询问串数量 $q$。

接下去 $q$ 行，每行一个长为奇数的 01 串，表示给定的字符串。
## 输出格式

对于每组询问输出一行，如果无解输出 `-1`，否则，输出一个由 `0,1,(,)` 组成的字符串描述运算方式及顺序，具体而言，计算的时候，会按照括号从内到外，从左到右的顺序依次解析括号，将对应的数字替换为运算结果，你需要保证每次运算时参与计算的运算数恰好为 $3$，具体可参见样例输出。
## 样例

### 样例输入 #1
```
00011011 2
10101
00000
```
### 样例输出 #1
```
((101)01)
-1
```
### 样例输入 #2
```
00010111 4
11100
11000
10100
10000
```
### 样例输出 #2
```
(11(100))
(11(000))
-1
-1
```
## 提示

### 样例 #1 解释

本样例即为 [THUPC 2025 决赛] 一个 01 串，n 次三目运算符，最后值为 1 一题中的样例。

### 样例 #2 解释

本样例即为 [AGC022E] Median Replace 一题中的样例。

### 数据范围

本题共 $256$ 个测试点，其中测试点编号为 $i(1\le i\le256)$ 的 $s$ 为 $i-1$ 的二进制表达（低位在前，高位在后），其中每个测试点输入的单个字符串长度不超过 $10^5$，字符串长度总和不超过 $3\times10^5$。


---

---
title: "第三心脏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12336
tag: ['Special Judge', 'O2优化', '构造', 'Ad-hoc']
---
# 第三心脏
## 题目背景

[第三心脏](https://music.163.com/#/song?id=1849700898)。
## 题目描述

mikage 喜欢构造题，这天她想到了一个简单的构造题：

给定 $a$ 试构造正整数**四元组** $(a,b,c,d)$ 满足：

1. $\sqrt{a^2+b^2+c^2+d^2}=a\oplus b\oplus c\oplus d$。

2. $a<b<c<d<2^{63}$。

无解输出 $-1$，$\oplus$ 是二进制按位异或。
## 输入格式

一行，一个整数 $a$。
## 输出格式

如果有解，一行三个整数 $b,c,d$ 带空格输出。无解输出 $-1$。
## 样例

### 样例输入 #1
```
31
```
### 样例输出 #1
```
172 484 632
```
## 提示

### 样例解释

依题面得。


### 数据范围

本题开启数据捆绑，你只有通过了一个 Subtask 内所有的测试点才能获取该 Subtask 的分数。

|Subtask|$a$ 的范围|特殊性质|分数|
| :----------: | :----------: | :----------: |:--:|
|0|$a\le 10$|无|5|
|1|$a\le 300$|无|5|
|2|$a\le 4\times 10^3$|A|10|
|3|$a\le 10^7$|B|10|
|4|$a\le 2\times 10^8$|C|20|
|5|$a\le 10^9$|D|10|
|6|$a\le 10^9$|无|40|

对于所有数据有 $1\le a \le 10^9$。

特殊性质 A：存在大于等于 $2$ 的整数 $k$ 满足 $a = 2^k$。

特殊性质 B：$a \equiv 0 \pmod{4}$。

特殊性质 C：$a \equiv 1 \pmod{4}$。

特殊性质 D：存在大于等于 $2$ 的整数 $k$ 满足 $a = 2^k-1$。


---

---
title: "「HCOI-R2」Rabbit Panic (Hard Ver.)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12356
tag: ['洛谷原创', 'Special Judge', 'O2优化', '其它技巧', '构造', '洛谷月赛', 'Ad-hoc']
---
# 「HCOI-R2」Rabbit Panic (Hard Ver.)
## 题目背景

**注意在问题的这个版本中，你需要解决和 Easy Ver. 一样的问题，但是需要最小化步数。**
## 题目描述

你有一个长度为 $n$ 的排列 $\{p_n\}$，初始 $p_i = i$。每次你可以选择 $m$ 个**不同**位置的元素，并**同时**将它们改成它们的平均值（不取整）。

最后你需要使所有元素都相等。

请你构造一组操作方案，并最小化你的操作数量。无解输出 $-1$。
## 输入格式

**本题单测试数据内含有多组输入。**

第一行一个正整数 $K$ 表示数据组数。

接下来每组测试数据包含两个正整数 $n$、$m$，含义如题面所述。
## 输出格式

对于每组测试数据，你可以：

- 输出一行 $-1$ 报告无解。
- 输出一行 $P$ 表示你的操作次数，注意这个次数必须最小化。接下来的 $P$ 行，每行 $m$ 个数，表示你的操作，用空格分开。
## 样例

### 样例输入 #1
```
1
6 4
```
### 样例输出 #1
```
2
1 2 5 6
2 3 4 5
```
## 提示

### 样例解释 1

- $[1,2,3,4,5,6]\to [3.5,3.5,3,4,3.5,3.5]\to [3.5,3.5,3.5,3.5,3.5,3.5]$。
- 可以证明不存在更优的方案。

### 数据范围

**本题采用捆绑测试。**

- Subtask 0 (15pts)：$1\leq \sum n\leq 10$。
- Subtask 1 (15pts)：$1\leq \sum n\leq 10^3$。
- Subtask 2 (70pts)：无特殊限制。

对于所有数据，$1 \leq T \leq 1.2\times 10^4$，$1 \leq m \leq n \leq 2\times 10^5$，$1 \leq \sum n \leq 10^6$。


---

---
title: "基础构造练习题 1"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12417
tag: ['Special Judge', '构造']
---
# 基础构造练习题 1
## 题目背景

2025.5.6：加强操作次数限制，并调整了部分分设计。

2025.5.8：再次加强操作次数限制，并调整了部分分设计。之前的提交记录已经全部重测。

## 题目描述

有一列实数，对于**每一次**操作，可以选择两个实数，把它们同时变为两数之积。

例如，给定 $7, 4, 5$，对 $7$ 和 $5$ 进行一次操作，原数列变为 $35, 4, 35$。

给定数列的长度 $n$，你的目标是找到一种操作方案，使得对于任意长度为 $n$ 的实数列，按照该操作方式操作之后，数列的每一项数值都相同。

## 输入格式

**本题有多组测试数据。**

第一行输入数据组数 $T$。

对于每组数据有一行，包含一个正整数 $n$，表示数列长度。

## 输出格式

对于每组数据，先输出一个整数表示能否找到。若能输出 $1$，否则输出 $0$。

若能找到，还需要输出一行 $m$ 表示操作次数（你需要保证 $0 \leq m \leq 5 \times 10^5$），接下来 $m$ 行，每行包含两个整数，表示操作的两项在数列中的编号。

## 样例

### 样例输入 #1
```
3
2
3
4
```
### 样例输出 #1
```
1
1
1 2
0
1
4
1 2
3 4
1 3
2 4
```
## 提示

Idea：Milmon，Solution：Milmon & _fewq，Code：Milmon & _fewq，Data：Milmon，Check：Konata28。

对于所有测试数据，保证 $T = 20$，$2 \leq n \leq 2^{10}$。本题共包含 $3$ 个子任务：

| 子任务编号 | 分值 | 测试点数目 |
| :-: | :-: | :-: |
| $1$ | $10$ | $1$ |
| $2$ | $30$ | $1$ |
| $3$ | $60$ | $3$ |

对于子任务 1，选手只需要正确回答是否存在操作方案即可获得满分。

对于子任务 2，对于每组测试数据分别计分：对于一组测试数据，只要选手正确回答是否存在操作方案，并且给出的操作方案均合法，就可以得到该测试点 $5 \%$ 的分数。选手在该测试点得到的分数等于每组测试数据得分的总和。

对于子任务 3：

- 若存在一组测试数据，选手没有正确回答是否存在操作方案，或者给出的操作方案不合法，那么选手在该测试点不得分；
- 否则，若对于所有存在操作方案的测试数据，选手都给出了操作次数不超过 $2n - 1$ 的方案，那么选手在该测试点得到全部分数；
- 否则，设所有存在操作方案的测试数据中选手给出的最大操作次数为 $s$，定义函数：

  $$
  f(x) = \frac{2 \times 10^7}{(x + 4\,000)^{0.7}}
  $$

  则选手在该测试点的得分为：

  $$
  \frac{f(s) - f(500\,000)}{f(2\,047) - f(500\,000)} \times 55
  $$

  下表为在一些特殊的 $s$ 中选手在该测试点得到的分数：

  | $s =$ | 选手得分 |
  | :-: | :-: |
  | $500\,000$ | $0$ |
  | $400\,000$ | $0.436$ |
  | $300\,000$ | $1.106$ |
  | $200\,000$ | $2.302$ |
  | $100\,000$ | $5.258$ |
  | $50\,000$ | $9.836$ |
  | $10\,000$ | $29.402$ |
  | $5\,000$ | $41.003$ |
  | $3\,000$ | $49.391$ |
  | $2\,047$ | $55$ |

提示：若能够完成正确性判断，但是无法完成构造的，也需要按照输出格式输出，例如你可以输出一个 $m = 0$ 的构造。类似地，输出时请判定 $0 \leq m \leq 5 \times 10^5$ 是否成立，若评分时存在一组数据的 $m > 5 \times 10^5$，则你无法得到任何分数。



---

---
title: "[APIO2025] Hack!"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12541
tag: ['2025', 'APIO', '交互题', 'Special Judge', '构造', '大步小步算法 BSGS']
---
# [APIO2025] Hack!
## 题目描述

It has been an hour into a Codeforces contest, when you notice that another contestant in your room has solved a problem using an `unordered_set`. Time to hack!

You know that `unordered_set` uses a hash table with $n$ buckets, which are numbered from $0$ to $n-1$. Unfortunately, you do not know the value of $n$ and wish to recover it.

When you insert an integer $x$ into the hash table, it is inserted to the $(x \bmod n)$-th bucket. If there are $b$ elements in this bucket prior to the insertion, this will cause $b$ hash collisions to occur.

By giving $k$ distinct integers $x[0], x[1], \dots, x[k-1]$ to the interactor, you can find out the total number of hash collisions that had occurred while creating an `unordered_set` containing the numbers. However, feeding this interactor $k$ integers in one query will incur a cost of $k$.

For example, if $n = 5$, feeding the interactor with $x = [2, 15, 7, 27, 8, 30]$ would cause 4 collisions in total:

| Operation               | New collisions | Buckets                     |
|-------------------------|----------------|-----------------------------|
| initially               | $-$            | $[], [], [], [], []$        |
| insert $x[0] = 2$       | $0$            | $[], [], [2], [], []$       |
| insert $x[1] = 15$      | $0$            | $[15], [], [2], [], []$     |
| insert $x[2] = 7$       | $1$            | $[15], [], [2, 7], [], []$  |
| insert $x[3] = 27$      | $2$            | $[15], [], [2, 7, 27], [], []$ |
| insert $x[4] = 8$       | $0$            | $[15], [], [2, 7, 27], [8], []$ |
| insert $x[5] = 30$      | $1$            | $[15, 30], [], [2, 7, 27], [8], []$ |

Note that the interactor creates the hash table by inserting the elements in order into an initially empty `unordered_set`, and a new empty `unordered_set` will be created for each query. In other words, all queries are independent.

Your task is to find the number of buckets $n$ using a total cost of at most $1\,000\,000$.

### Implementation details

You should implement the following procedure:

```cpp
int hack()
```

- This procedure should return an integer – the hidden value of $n$.
- For each test case, the grader may call this function more than once. Each call should be processed as a separately new scenario.

Within this procedure, you may call the following procedure:

```cpp
long long collisions(std::vector<long long> x)
```

- $x$: an array of distinct numbers, where $1 \leq x[i] \leq 10^{18}$ for each $i$.
- This function returns the number of collisions created by inserting the elements of $x$ to an `unordered_set`.
- This procedure can be called multiple times. The sum of length of $x$ over all calls within one call to `hack()` must not exceed $1\,000\,000$.

**Note**: Since the procedure `hack()` will be called more than once, contestants need to pay attention to the impact of the remaining data of the previous call on the current call, especially the state stored in global variables.

The cost limit of $1\,000\,000$ applies to each test case. In general, if there are $t$ calls to `hack()`, you may use a total cost of no more than $t \times 1\,000\,000$, with each individual call to `hack()` using a cost no more than $1\,000\,000$.

The interactor is not adaptive, i.e. the values of $n$ are fixed before the start of interaction.
## 提示

### Example

Suppose, there are 2 multitests. The grader will make a following call:

```cpp
hack()
```

Let's say, within the function, you make following calls:

| Call                          | Returned value |
|-------------------------------|----------------|
| `collisions([2, 15, 7, 27, 8, 30])` | $4$            |
| `collisions([1, 2, 3])`             | $0$            |
| `collisions([10, 20, 30, 40, 50])` | $10$           |

After that, if you find that the value of $n$ is $5$, the procedure `hack()` should return $5$.

Then grader will make another call:

```cpp
hack()
```

Let's say, within the function, you make following calls:

| Call              | Returned value |
|-------------------|----------------|
| `collisions([1, 3])` | $1$            |
| `collisions([2, 4])` | $1$            |

The only $n$ which satisfies the queries is $2$. So, the procedure `hack()` should return $2$.

### Constraints

- $1 \leq t \leq 10$, where $t$ is the number of multitests.
- $2 \leq n \leq 10^9$
- $1 \leq x[i] \leq 10^{18}$ for each call to `collisions()`.

### Subtasks

1. (8 points) $n \leq 500\,000$
2. (17 points) $n \leq 1\,000\,000$
3. (75 points) No additional constraints.

In the last subtask, you can get partial score. Let $q$ be the maximum total cost among all invocations of `hack()` over every test case of the subtask. Your score for this subtask is calculated according to the following table:

| Condition                      | Points |
|--------------------------------|--------|
| $1\,000\,000 < q$              | $0$    |
| $110\,000 < q \leq 1\,000\,000$ | $75 \cdot \log_{50} \left( \frac{10^6}{q - 90000} \right)$ |
| $q \leq 110\,000$              | $75$   |

If, in any of the test cases, the calls to the procedure `collisions()` do not conform to the constraints described in Implementation Details, or the number returned by `hack()` is incorrect, the score of your solution for that subtask will be $0$.

### Sample Grader

The sample grader reads the input in the following format:

- line 1: $t$

Then, $t$ lines follow, each containing a value of $n$:

- line 1: $n$

For each test case, let $m$ be the return value of `hack()`, and $c$ be the total cost of all queries. The sample grader prints your answer in the following format:

- line 1: $m \, c$


---

---
title: "[GCJ Farewell Round #3] Game Sort: Part 2"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12960
tag: ['贪心', '2023', 'Special Judge', '构造', 'Google Code Jam']
---
# [GCJ Farewell Round #3] Game Sort: Part 2
## 题目描述

Note: The main parts of the statements of the problems "Game Sort: Part 1" and "Game Sort: Part 2" are identical, except for the last paragraph. The problems can otherwise be solved independently.

Amir and Badari are playing a sorting game. The game starts with a string $\mathbf{S}$ and an integer $\mathbf{P}$ being chosen by an impartial judge. Then, Amir has to split $\mathbf{S}$ into exactly $\mathbf{P}$ contiguous non-empty parts (substrings). For example, if $\mathbf{S} = \text{CODEJAM}$ was the chosen string and $\mathbf{P} = 3$, Amir could split it up as $[\text{COD}, \text{EJA}, \text{M}]$ or as $[\text{CO}, \text{D}, \text{EJAM}]$, but not as $[\text{COD}, \text{EJAM}]$, $[\text{COD}, \text{JA}, \text{M}]$, $[\text{EJA}, \text{COD}, \text{M}]$, nor as $[\text{CODE}, \text{EJA}, \text{M}]$.

Then, Badari must rearrange the letters within each part to make the list of parts be sorted in non-decreasing lexicographical order. If she can, then she wins. Otherwise, Amir wins.

Given the initial string and number of parts, can you help Amir win the game by choosing his parts in a way Badari cannot win herself? If not, say that it is not possible.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ lines follow, each describing a single test case containing an integer $\mathbf{P}$ and a string $\mathbf{S}$, the number of parts and string to be partitioned, respectively.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is either `POSSIBLE` if Amir can win the game, or `IMPOSSIBLE` if he cannot. If he can win the game, output a second line containing $t_1 t_2 \ldots t_p$ where $t_i$ is the $i$-th part of the winning partition you found for Amir. If there are multiple solutions, you may output any one of them.
## 样例

### 样例输入 #1
```
3
3 CODEJAM
2 ABABABABAAAA
3 AABBCDEEFGHIJJKLMNOPQRRSTUVWXYZZ
```
### 样例输出 #1
```
Case #1: POSSIBLE
C O DEJAM
Case #2: POSSIBLE
ABABABABA AAA
Case #3: IMPOSSIBLE
```
## 提示

**Sample Explanation**

In Sample Case #1, there is no way for Badari to rearrange $\text{DEJAM}$ to be lexicographically after $\text{O}$, so Amir guaranteed a win.

In Sample Case #2, $\text{AAA}$ is guaranteed to be earlier than any rearrangement of a string containing more than 3 letters, so Amir also wins.

In Sample Case #3, all possible partitions result in a list of parts that is already sorted in lexicographical order, so Amir cannot possibly win.

**Limits**

$1 \leq \mathbf{T} \leq 100$.

Each character of $\mathbf{S}$ is an English uppercase letter A through Z.

**Test Set 1 (8 Pts, Visible Verdict)**

- $2 \leq \mathbf{P} \leq 3$.
- $\mathbf{P} \leq \text{the length of } \mathbf{S} \leq 100$.

**Test Set 2 (20 Pts, Hidden Verdict)**

- $2 \leq \mathbf{P} \leq 100$.
- $\mathbf{P} \leq \text{the length of } \mathbf{S} \leq 10^5$.


---

---
title: "[GCJ 2022 #3] Win As Second	"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13000
tag: ['2022', '交互题', 'Special Judge', '构造', 'SG 函数', 'Google Code Jam']
---
# [GCJ 2022 #3] Win As Second	
## 题目描述

Ueli and Vreni are playing a game. The game's board is a tree with $\mathbf{N}$ vertices, all initially colored blue. They alternate turns, with Ueli going first. In each turn, a player must choose a blue vertex, together with any subset (possibly none or all) of its blue neighbors, and color all those vertices red. If at the start of a players' turn, all vertices are red, then that player loses the game and the other player wins the game.

In the example game below, Ueli colored vertex 3 red in their first turn. Then, Vreni chose vertex 2 for their turn and colored both it and its neighbor (vertex 1) red. Because all vertices are now red, Ueli loses and Vreni wins.

![](https://cdn.luogu.com.cn/upload/image_hosting/xw0xc7is.png)

Ueli and Vreni have noticed that it is much easier for Ueli to win this game because he has the first turn. Therefore they have adopted the following procedure: first, Ueli chooses an integer $\mathbf{N}$. Then, Vreni chooses any tree with $\mathbf{N}$ vertices. And then they start playing as described above, with Ueli taking the first turn.

Vreni is hopeful that being able to choose the tree can help her overcome the disadvantage of going second. Can you demonstrate how Vreni can win games in this setup?

### Interactive Protocol

This is an interactive problem. You should make sure you have read the information in the Interactive Problems section of our FAQ.

Initially, your program should read a single line containing an integer, $\mathbf{T}$, the number of test cases. Then, $\mathbf{T}$ test cases must be processed.

For each test case, your program must first read a line containing a single integer $\mathbf{N}$, the number of vertices that Ueli has chosen. Then, your program must output $\mathbf{N}-1$ lines describing the edges of the tree Vreni should choose. The nodes of the tree are numbered 1 through $\mathbf{N}$. Each line must represent a distinct edge of the tree with 2 integers between 1 and $\mathbf{N}$: the two vertices the edge connects. The edges must represent a tree. The two integers within a line may be in either order, and the $\mathbf{N}-1$ lines themselves may be in any order.

After that, your program must read a line containing a single integer $\mathbf{M}$, the number of games that you need to play on this tree. These games are played independently; in other words, all vertices of the tree are blue at the start of each game.

For each of the $\mathbf{M}$ games, you need to process some number of exchanges until the game is over. Each exchange consists of a turn from each player.

For each exchange, your program must read two lines describing Ueli's turn first. The first of those lines will contain an integer $\mathbf{K}$, denoting the number of blue vertices to be colored red. The second of those lines will contain $\mathbf{K}$ distinct integers $\mathbf{A}_1, \mathbf{A}_2, \ldots, \mathbf{A}_\mathbf{K}$ describing the blue vertices to be colored red. $\mathbf{K}$ will be at least 1, and each $\mathbf{A}_i$ will be between 1 and $\mathbf{N}$, inclusive. Vertices $\mathbf{A}_2, \mathbf{A}_3, \ldots, \mathbf{A}_\mathbf{K}$ will all be neighbors of vertex $\mathbf{A}_1$.

After that, your program must output Vreni's choice for their turn in the same format: the first line with the number of blue vertices to be colored red, followed by the second line with the numbers of those vertices, in such an order that all vertices except the first one are neighbors of the first one.

If all vertices are red after Vreni's turn, it means that Vreni has won and this game is over. The next game starts immediately if there is one. If this was the last game for this test case, then the next test case starts immediately if there is one. If this was the last test case, the judge will send no further input to your program, and the program must send no further output.

On the other hand, if all vertices are red after Ueli's move, it means that Vreni has lost and therefore your program did not pass the test case. In this case, instead of starting a new exchange by printing the last move that colors all remaining blue vertices red, the judge will print a single number -1 and will not print any further output, and will not process any further games or test cases.

If the judge receives an invalidly formatted or invalid line (like outputting an unexpected number of integers, or integers out of range, or outputting a set of edges that do not form a tree, or trying to color a vertex that is already red, or trying to color a vertex that is not a neighbor of the first vertex colored in this turn) from your program at any moment, the judge will also print a single number -1 and will not print any further output. If your program continues to wait for the judge after receiving a -1, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.

The judge is deterministic. In other words, if you make two attempts that print the same numbers, you will get the same inputs from the judge. However, of course the judge can make different moves in different games on the same tree.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
2
3



1
1
3


4



2
3
2 1 3


2
2 3


-1
```
### 样例输出 #1
```



1 2
1 3



2
1 2

1 2
2 3
2 4



1
4


1
1
```
## 提示

Note that the sample interaction does not satisfy the constraints of either test set, as its $\mathbf{N}$ values are too small. It is only presented to clarify the input and output format.

Below is an illustration of Case #2, Game #1 at the beginning and after each turn:

![](https://cdn.luogu.com.cn/upload/image_hosting/cccz3vlj.png)

Below is an illustration of Case #2, Game #2 at the beginning and after each turn:

![](https://cdn.luogu.com.cn/upload/image_hosting/0b2qkj8q.png)

**Limits**

- $1 \leq \mathbf{M} \leq 50.$

**Test Set 1 (13 Pts, Visible Verdict)**

- $\mathbf{T}=1$.
- $\mathbf{N}=30$.

**Test Set 2 (Hidden Verdict)**

- $1 \leq \mathbf{T} \leq 10.$
- $31 \leq \mathbf{N} \leq 40.$
- No two test cases use the same value of $\mathbf{N}$.


---

---
title: "[GCJ 2022 Finals] Triangles"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13005
tag: ['贪心', '计算几何', '2022', 'Special Judge', '构造', 'Google Code Jam']
---
# [GCJ 2022 Finals] Triangles
## 题目描述

You are given a set $P$ of $\mathbf{N}$ distinct points in the two-dimensional plane. You want to find a maximum set of triangles such that:

*   Each vertex of a triangle in your set is a point from $P$ and each point in $P$ is a vertex of at most one triangle in your set.
*   Each triangle in your set has positive area (i.e., its 3 vertices are not collinear).
*   For any two sides of triangles in your set, their intersection is either empty or an endpoint of one of them.
*   For any two triangles in your set, the intersection of the areas strictly inside those triangles is either empty or equal to one of them.

For example, the set of triangles depicted below meets the definition above.

![](https://cdn.luogu.com.cn/upload/image_hosting/jxq6yve2.png)

On the other hand, each pair of a yellow and a red triangle in the picture below does not meet the definition.

![](https://cdn.luogu.com.cn/upload/image_hosting/oyhps85j.png)
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing a single integer $\mathbf{N}$. Then, $\mathbf{N}$ lines follow. The $i$-th of these lines contains two integers $\mathbf{X}_i$ and $\mathbf{Y}_i$ representing the coordinates of the $i$-th point.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the maximum size of a set of triangles with the desired properties. Then, output $y$ more lines. The $j$-th of those lines must contain $p_j$ $q_j$ $r_j$ representing that the $j$-th triangle in your proposed set has the $p_j$-th, $q_j$-th, and $r_j$-th points in the input as vertices. Points in the input are numbered starting from 1.
## 样例

### 样例输入 #1
```
3
9
8 2
10 2
2 0
0 5
2 3
10 4
10 0
8 3
2 4
7
0 0
0 3
3 0
0 1
1 0
1 1
2 2
3
0 0
0 1
0 2
```
### 样例输出 #1
```
Case #1: 3
3 4 5
1 7 9
6 2 8
Case #2: 2
2 3 1
6 5 4
Case #3: 0
```
## 提示

Sample Case #1 is illustrated below. Notice that there are other valid ways to construct a maximum number of triangles.

![](https://cdn.luogu.com.cn/upload/image_hosting/x975q63y.png)

Sample Case #2 is illustrated below. As before, there are other valid ways to construct 2 triangles.

![](https://cdn.luogu.com.cn/upload/image_hosting/7ca1oxq2.png)

In Sample Case #3, the 3 given points are collinear, so it is not possible to make a valid triangle with them.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $-10^9 \leq \mathbf{X}_i \leq 10^9$, for all $i$.
- $-10^9 \leq \mathbf{Y}_i \leq 10^9$, for all $i$.
- $(\mathbf{X}_i, \mathbf{Y}_i) \neq (\mathbf{X}_j, \mathbf{Y}_j)$, for all $i \neq j$.

**Test Set 1 (8 Pts, Visible Verdict)**

- $3 \leq \mathbf{N} \leq 12$.

**Test Set 2 (42 Pts, Hidden Verdict)**

- $3 \leq \mathbf{N} \leq 3000$.


---

---
title: "[GCJ 2016 Finals] Map Reduce"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13209
tag: ['贪心', '2016', 'Special Judge', '广度优先搜索 BFS', '构造', 'Ad-hoc', 'Google Code Jam']
---
# [GCJ 2016 Finals] Map Reduce
## 题目描述

Ben the brilliant video game designer is trying to design maps for his upcoming augmented-reality mobile game. Recently, he has created a map which is represented as a matrix of $\mathbf{R}$ rows and $\mathbf{C}$ columns. The map consists of a bunch of `.` characters representing empty squares, a bunch of `#` characters representing impassable walls, a single start position represented by `S` and a single finish position represented by `F`. For example, the map could look like:

```
#############
#S..#..##...#
###.##..#.#F#
#...##.##.###
#.#.........#
#############
```

In Ben's game, a path is a sequence of steps (up, down, left or right) to go from one cell to another while not going through any impassable walls.

Ben considers a good map to have the following properties:

- There is a path between any two empty squares (including the start and finish positions).
- To preserve structural integrity, impassable walls must meet at edges and not just corners. For every $2 \times 2$ region in the map, if the region contains exactly two walls, then those walls are either in the same row or the same column. In other words, there is no $2 \times 2$ region where the walls are in one of these two configurations:
  ```
  #.   .#
  .#   #.
  ```
- The boundary consists of only impassable walls. A cell is considered part of the boundary if it is in the uppermost/lowermost rows or if it is in the leftmost/rightmost columns.

The distance of the shortest path is the minimum number of steps required to reach the finish position from the start position. For instance, the shortest path in the above example takes $17$ steps.

Being such a clever mapmaker, Ben realized that he has created a map that is too hard for his friends to solve. He would like to reduce its difficulty by removing some of the impassable walls. In particular, he wants to know whether it is possible to remove zero or more impassable walls from his map such that the shortest path from start to finish takes exactly $\mathbf{D}$ steps, and that the resulting map is still good. Note that it is not enough to simply find a path with $\mathbf{D}$ steps; $\mathbf{D}$ must be the number of steps in the shortest path.

For example, if $\mathbf{D} = 15$, we could remove the impassable wall directly below the finish position to get a good solution.

```
#############
#S..#..##...#
###.##..#.#F#
#...##.##.#.#
#.#.........#
#############
```

There is no solution if $\mathbf{D}=5$.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing three space-separated integers $\mathbf{R}$, $\mathbf{C}$ and $\mathbf{D}$: the number of rows and columns in the map, and the desired number of steps in the shortest path from start to finish after possibly removing impassable walls. $\mathbf{R}$ lines follow, each consisting of $\mathbf{C}$ characters (either ., #, S or F) representing Ben's map.

It is guaranteed that the map is good, as described in the problem statement.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the word POSSIBLE or IMPOSSIBLE, depending on whether the shortest path can be made equal to $\mathbf{D}$ by removing some number of walls such that the map is still good. If it is possible, output $\mathbf{R}$ more lines containing $\mathbf{C}$ characters each, representing the new map. In your output, replace the # characters for removed walls (if any) with . characters.

If multiple solutions are possible, you may output any of them.
## 样例

### 样例输入 #1
```
3
6 13 15
#############
#S..#..##...#
###.##..#.#F#
#...##.##.###
#.#.........#
#############
5 8 3
########
#S.....#
####...#
#F.....#
########
4 10 11
##########
#S#...#.F#
#...#...##
##########
```
### 样例输出 #1
```
Case #1: POSSIBLE
#############
#S..#..##...#
###.##..#.#F#
#...##.##.#.#
#.#.........#
#############
Case #2: IMPOSSIBLE
Case #3: POSSIBLE
##########
#S#...#.F#
#...#...##
##########
```
## 提示

**Sample Explanation**

The sample output displays one set of answers to the sample cases. Other answers may be possible.

Sample case #1 is the example in the problem statement.

In sample case #2, it is possible to remove walls to make the distance of the shortest path either 2 or 4, for example. However, there is no way to make the distance of the shortest path exactly 3.

In sample case #3, the shortest path already takes 11 steps to begin with, so there is no need to reduce the difficulty of the map.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- Each test case contains exactly one $\mathbf{S}$ and exactly one $\mathbf{F}$.
- The input file is at most 3MB in size.

**Small dataset (Test Set 1 - Visible)**

- Time limit: ~~60~~ 15 seconds.
- $3 \leq \mathbf{R} \leq 40$.
- $3 \leq \mathbf{C} \leq 40$.
- $1 \leq \mathbf{D} \leq 1600$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~300~~ 75 seconds.
- $3 \leq \mathbf{R} \leq 1000$.
- $3 \leq \mathbf{C} \leq 1000$.
- $1 \leq \mathbf{D} \leq 10^6$.
- NOTE: The Large output breaks the usual cap on Code Jam output size, but you can upload it as normal.


---

---
title: "[GCJ 2011 Finals] Program within a Program"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13384
tag: ['2011', 'Special Judge', '构造', 'Google Code Jam']
---
# [GCJ 2011 Finals] Program within a Program
## 题目描述

You have a robot on an infinite east-west highway, and it has a cake to deliver. Every mile along the highway, in both directions, there is a lamppost. You want to program the robot to move exactly N lampposts to the east, and release the cake there. The route does not have to be direct, as long as the robot eventually releases the cake in the right place.

Unfortunately, the robot comes equipped with only very little memory, and it is capable of no advanced logic. To control the robot you will have to give it a very simple program at the start that will get it to release the cake at the proper location. This program must be composed of one or more statements, each of which tells the robot what to do under certain conditions. These statements must be in the following format:

```
<S> <M> -> <action>
```

which means that if all of the following conditions are met:

1. The robot is in state $s$.
2. The robot is at a lightpost marked with number $M$.

then it will perform exactly one of the following actions:

1. Mark the current post with a new number, change state and move. To do this `<action>` must be formatted as "`<D> <NS> <NM>`", where `D` is the direction to move (use 'W' for west and 'E' for east), `NS` is the robot's new state and `NM` is the new mark for the current lightpost.
2. Release the cake at the current position and self-destruct. To do this `<action>`

If you output two or more statements with the same values of $s$ and $M$, the robot will misbehave and destroy the cake.

If at any time the robot is in a state $X$ at a lamppost marked with $Y$ such that there is no statement with $s=X$ and $M=Y$, then the robot will get confused and eat the cake.

All states and marks must be integers with absolute value no greater than one million ($10^6$). Assume that initially the robot is in state zero and all lampposts are marked with zero.

Given $N$, write a program so the robot releases the cake in the appropriate place. Your program must use at most $30$ statements, and it must terminate within $X$ steps.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case consists of a single line containing an integer $N$, which indicates the lamppost where the robot must release the cake.

## 输出格式

For each test case, first output "Case #$x$: $y$", where $x$ is the number of the test case (starting with 1) and $y$ is the number of statements you will use. Next output $y$ lines, each of which represents a statement for the robot in the format described previously.

WARNING: Judge's response might take up to 5 seconds longer than usual to appear, because your output is run as part of the validation.
## 样例

### 样例输入 #1
```
3
0
4
0
```
### 样例输出 #1
```
Case #1: 1
0 0 -> R
Case #2: 5
0 0 -> E 1 1
1 0 -> E 2 1
2 0 -> E 3 1
3 0 -> E -1 1
-1 0 -> R
Case #3: 3
0 0 -> E 1 1
0 1 -> R
1 0 -> W 0 1
```
## 提示

**Sample Explanation**

In the first case, the robot is initially in state zero, and there is a zero on the lamppost. So it executes its only statement, which is to release the cake.

In the second case, the robot has five states: $0$, $1$, $2$, $3$, and $-1$. The robot performs the following actions:

* Mark the current lamppost with a $1$, move east, and go to state $1$.
* Mark the current lamppost with a $1$, move east, and go to state $2$.
* Mark the current lamppost with a $1$, move east, and go to state $3$.
* Mark the current lamppost with a $1$, move east, and go to state $-1$.
* Release the cake.

In the third case, the robot has two states, and performs the following actions:

* Mark the current lamppost with a $1$, move east, and go to state $1$.
* Mark the current lamppost with a $1$, move west, and go to state $0$.
* Release the cake.

Note that the robot takes different actions at the two times it is in state $0$, because it sees a different mark each time.

**Limits**

- $1 \leq T \leq 15$.

**Small dataset (15 Pts, Test set 1 - Visible)**

- $0 \leq N \leq 500$.
- $X = 250,000 (2.5 \times 10^5)$.
- Time limit: 30 seconds.

**Large dataset (23 Pts, Test set 2 - Hidden)**

- $0 \leq N \leq 5000$.
- $X = 150,000 (1.5 \times 10^5)$
- Time limit: 60 seconds.


---

---
title: "【MX-X16-T7】「DLESS-3」XOR and Generalized Linear Independence"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13689
tag: ['Special Judge', 'O2优化', '群论', '线性代数', '构造', '梦熊比赛']
---
# 【MX-X16-T7】「DLESS-3」XOR and Generalized Linear Independence
## 题目描述

给定 $k$，定义集合 $U$ 广义线性无关当且仅当：

- $\forall 2\le x\le k$，不存在 $U$ 的大小为 $x$ 的子集 $V$ 使得 $V$ 的异或和为 $0$。

给定 $n,m$ 和 $k$，你需要构造一个 $\{0,1,2,\dots,2^n-1\}$ 的大小为 $m$ 的子集 $U$ 使得 $U$ 是广义线性无关的。

保证答案一定存在，请参考【**数据范围**】中的表格。

本题使用自定义校验器，任意合法的答案都会被判定为正确。
## 输入格式

仅一行，三个整数 $n,m,k$。
## 输出格式

一行 $m$ 个整数，表示一组方案。你可以以任意顺序输出这些数，你需要保证它们在 $[0, 2^n - 1]$ 之间且互不相同。

本题使用自定义校验器，若有多组方案，任意输出一组即可。
## 样例

### 样例输入 #1
```
4 4 4
```
### 样例输出 #1
```
0 1 2 4
```
### 样例输入 #2
```
9 8 5
```
### 样例输出 #2
```
0 73 474 163 236 309 382 407
```
## 提示

**【样例解释 #1】**

对于该样例，一组解为 $\{0, 1, 2, 4\}$。根据题意，$k=4$，需要检验大小为 $2,3,4$ 的子集的异或和。

- 大小为 $2$ 的子集：异或和有 $0\oplus 1=1, 0\oplus 2=2, 1\oplus 2=3, \dots$ 均不为 $0$。
- 大小为 $3$ 的子集：异或和有 $0\oplus 1\oplus 2=3, 0\oplus 1\oplus 4=5, \dots$ 均不为 $0$。
- 大小为 $4$ 的子集：异或和为 $0\oplus 1\oplus 2\oplus 4=7$，不为 $0$。

所有子集的异或和均不为 $0$，因此该构造是合法的。

**【数据范围】**

**本题各测试点不等分，详见“分值”一栏。**

对于所有数据，保证 $1\le n\le 24$，$1\le m\le 2^{20}$，$2\le k\le 8$，保证答案一定存在，更具体地，$(n, m, k)$ 一定满足下表中某个测试点的限制。

各测试点特殊限制如下：

| 测试点编号 | $n=$ | $m=$ | $k=$ | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $20$ | $2^{20}$ | $2$ | $1$ |
| $2$ | $18$ | $500$ | $3$ | $4$ |
| $3$ | $18$ | $500$ | $4$ | $4$ |
| $4$ | $24$ | $4000$ | $4$ | $22$ |
| $5$ | $24$ | $10$ | $6$ | $8$ |
| $6$ | $24$ | $250$ | $6$ | $24$ |
| $7$ | $24$ | $10$ | $8$ | $10$ |
| $8$ | $24$ | $64$ | $8$ | $27$ |


---

---
title: "[NOI2012] 骑行川藏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P2179
tag: ['数学', '2012', 'NOI', 'Special Judge', '向量', '构造', '拉格朗日乘数法']
---
# [NOI2012] 骑行川藏
## 题目描述

蛋蛋非常热衷于挑战自我，今年暑假他准备沿川藏线骑着自行车从成都前往拉萨。

川藏线的沿途有着非常美丽的风景，但在这一路上也有着很多的艰难险阻，路况变化多端，而蛋蛋的体力十分有限,因此在每天的骑行前设定好目的地，同时合理分配好自己的体力是一件非常重要的事情。

由于蛋蛋装备了一辆非常好的自行车，因此在骑行过程中可以认为他仅在克服风阻做功（不受自行车本身摩擦力以及自行车与地面的摩擦力影响）。

某一天他打算骑 $n$ 段路，每一段内的路况可视为相同：对于第 $i$ 段路,我们给出有关这段路况的 $3$ 个参数 $s_i,k_i,v_i'$，其中 $s_i$ 表示这段路的长度，$k_i$ 表示这段路的风阻系数，$v_i'$ 表示这段路上的风速（$v_i'\gt 0$ 表示在这段路上他遇到了顺风，反之则意味着他将受逆风影响）。

若某一时刻在这段路上骑车速度为 $v$，则他受到的风阻
大小为 $F=k_i(v-v_i')^2$（这样若在长度为 $s$ 的路程内保持骑行速度 $v$ 不变,则他消耗能量（做功）$E=k_i(v-v_i')^2s$ ）。

设蛋蛋在这天开始时的体能值是 $E_U$，请帮助他设计一种行车方案,使他在有限的体力内用最短的时间到达目的地。请告诉他最短的时间 $T$ 是多少。
## 输入格式

第一行包含一个正整数 $n$ 和一个实数 $E_U$，分别表示路段的数量以及蛋蛋的体能值。

接下来 $n$ 行分别描述 $n$ 个路段，每行有 $3$ 个实数 $s_i,k_i,v_i'$ 分别表示第 $i$ 段路的长度，风阻系数以及风速。
## 输出格式

输出一个实数 $T$，表示蛋蛋到达目的地消耗的最短时间，要求至少保留到小数点后 $6$ 位。
## 样例

### 样例输入 #1
```
3 10000
10000 10 5
20000 15 8
50000 5 6
```
### 样例输出 #1
```
12531.34496464
```
## 提示

### 样例说明

一种可能的方案是：蛋蛋在三段路上都采用匀速骑行的方式,其速度依次为 $5.12939919,8.03515481,6.17837967$。

### 评分方法

本题没有部分分,你程序的输出只有和标准答案的差距不超过 $10^{-6}$ 时，才能获得该测试点的满分，否则不得分。

### 数据规模与约定

对于 $10\%$  的数据，$n=1$。

对于 $40\%$  的数据，$n\le2$。

对于 $60\%$  的数据，$n\le100$。

对于 $80\%$  的数据，$n\le 1000$。

对于 $100\%$  的数据，$n\le 10^4$，$E_U\le 10^8$，$s_i\in[0,10^5]$，$k_i\in(0,15]$，$v_i'\in(-100,100)$。

数据保证最终的答案不会超过 $10^5$。

### 提示

必然存在一种最优的体力方案满足：蛋蛋在每段路上都采用匀速骑行的方式。


---

---
title: "[SCOI2012] 喵星人的入侵"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P2337
tag: ['2012', '四川', '各省省选', '构造', '插头 DP']
---
# [SCOI2012] 喵星人的入侵
## 题目描述


a180285 幸运地被选作了地球到喵星球的留学生，其实是作为特工去调查，喵星人是否有侵略地球的企图。喵星人果然打算入侵地球！从 a180285 口中得到确切消息之后，地球小组成员决定制定反侵略计划。

喵星到地球的一段必经之路可以看作 $n\times m$ 的格点，喵星人将会从地图上的 $S$ 位置出发，目的地是地球的入口 $T$。为了抵抗喵星人的入侵，地球防御小组打算在地图上的格点上放置一些炮塔（最多放置 $K$ 个），炮塔攻击周围的 $8$ 个方向（$8$ 个方向分别是：东、南、西、北、东北、西北、东南、西南）（如下图所示，中间格子的炮塔可以攻击周围的八个格子）。此外地球防御小组还可以在地图上放置无限多个障碍，使得喵星人无法从有障碍的格子经过。

![](https://cdn.luogu.com.cn/upload/image_hosting/l6ezyb3h.png)

右图是 $3\times 3$ 地图的一个示例，其中 $\tt X$ 表示炮塔，$\tt \#$ 表示障碍，有炮塔或者障碍的格子，喵星人都无法经过。在这张地图中喵星人从 $S$ 走到 $T$ 受到的伤害如下：

- 在 $S(1, 0)$ 处受到伤害为 $2$（炮塔 $(0,0)$ 和 $(2, 1)$ 能攻击到 $S$）；
- 在空地 $(1,1)$ 处受到伤害为 $3$（同时被炮塔 $(0,0),(0,2)$ 和 $(2, 1)$ 攻击）；
- 在 $T(1,2)$ 处受到伤害为 $2$（炮塔 $(0,2)$ 和 $(2, 1)$ 能攻击到 $T$）。

于是受到的总伤害为 $2+3+2=7$。

作为地球防御小组的成员，请你为喵星人布阵，使得喵星人受到的伤害最大。注意如果有多条从 $S$ 到 $T$ 的路径，喵星人会选择伤害最小的一条。
## 输入格式

第一行为三个整数 $n,m,K$，分别表示地图的长和宽，以及最多能放置的炮塔数量。

接下来的 $n$ 行，每行包含 $m$ 个字符，$\tt \#$ 表示地图上原有的障碍，$\tt .$ 表示该处为空地，数据保证在原地图上存在 $S$ 到 $T$ 的路径。
## 输出格式

输出在合理布阵下，喵星人采取最优策略后，会受到的最大伤害。

注意必须保证在布阵结束后喵星人仍然可以沿一条或以上的路径从起点 $S$ 到达终点 $T$，否则他们组织更大规模的侵略。
## 样例

### 样例输入 #1
```
3 3 1
S.T
...
...
```
### 样例输出 #1
```
7
```
## 提示

### 样例解释

样例的一种最优布局方案如下：

```plain
S#T
.X.
...
```

### 数据范围及约定

- 对于 $30\%$ 的数据，保证 $1\le n,m\leq 6$；
- 对于 $100\%$ 的数据，保证 $\min(n,m)\le 6$，$\max(n,m)\le 20$，$1\le K\le 15$ 且从 $S$ 到 $T$ 的路径必定存在。



---

---
title: "[HNOI2010] 矩阵"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3208
tag: ['2010', '湖南', '枚举', '剪枝', '构造']
---
# [HNOI2010] 矩阵
## 题目描述

小 Z 近日闲来无事，便研究起矩阵来。他先写了一个 $N\times M$ 的矩阵，每个格子里填入了一个小于 $P$ 的非负整数，然后他对于每个 $2\times 2$ 的子矩阵，算出了其中数的和。

譬如 $N=3, M=3, P=3$，小 Z 写的矩阵如下：

$$ A = \begin{pmatrix} 0 & 1 & 2 \\ 1 & 2 & 0 \\ 2 & 0 & 1 \end{pmatrix} $$

共有 $4$ 个 $2\times 2$ 的子矩阵，容易算出它们的和如下：

$$ A = \begin{pmatrix} 0 & 0 & 0 \\ 0 & 4 & 5 \\ 0 & 5 & 3 \end{pmatrix} $$

(第一行和第一列的 $0$ 是为了格式美观而添加进去的)

现在小 Z 想试一试能不能根据这些和推算出原矩阵。由于小 Z 的数学并不好，因此这个任务就交给你了。

当然，小 Z 早就发现了，解很可能不唯一，譬如下面的矩阵算出的和与 $A$ 相同：

$$ A = \begin{pmatrix} 0 & 2 & 1 \\ 0 & 2 & 0 \\ 2 & 1 & 0 \end{pmatrix} $$

示意图在有多个矩阵满足要求的情况下请你输出字典序最小的那一个。

字典序的比较方式如下：对于两个解矩阵 $X$ 和 $Y$，找到 $X$ 和 $Y$ 不同的位置中行数最小的那一个格子，若有多个则取列数最小的那个格子，该位置较小的矩阵字典序较小。

譬如上述的矩阵 $A$ 和 $B$，第一个不同的格子应是第一行第二个格子，而 $A[1][2] < B[1][2]$，故矩阵 $A$ 的字典序比 $B$ 小。

另外，小 Z 的数学还没有差到加法都做错，因此保证输入数据都是有解的。

## 输入格式

第一行包含三个正整数 $N, M, P$ 表示矩阵的行数列数以及每个数的范围，接下来 $N$ 行每行包含 $M$ 个非负整数，其中第 $i$ 行第 $j$ 个数表示以格子 $(i,j)$ 为右下角的 $2 \times 2$ 子矩阵中的数的和。保证第一行与第一列的数均为 $0$，且每个和都不超过 $4 (P-1)$。

## 输出格式

包含 $N$ 行，每行 $M$ 个整数，描述你求出的矩阵，相邻的整数用空格分开。（行末不要有多余空格）

## 样例

### 样例输入 #1
```
3 3 3
0 0 0
0 4 5
0 5 3

```
### 样例输出 #1
```
0 0 2
2 2 1
1 0 0

```
## 提示

$1 \le N, M \le 200$

$2 \le P \le 10$

感谢 @ASC\_8384 提供题面



---

---
title: "[POI 2011] OKR-Periodicity"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3526
tag: ['2011', 'POI（波兰）', '构造']
---
# [POI 2011] OKR-Periodicity
## 题目描述

Byteasar, the king of Bitotia, has ordained a reform of his subjects' names.

The names of Bitotians often contain repeating phrases,    e.g., the name Abiabuabiab has two occurrences of the phrase    abiab.  Byteasar intends to change the names of his subjects to    sequences of bits matching the lengths of their original names.

Also, he would very much like to reflect the original repetitions in the new    names.

In the following, for simplicity, we will identify the upper- and lower-case    letters in the names.  For any sequence of characters (letters or bits)    ![](http://main.edu.pl/images/OI18/okr-en-tex.1.png) we say that the integer ![](http://main.edu.pl/images/OI18/okr-en-tex.2.png) (![](http://main.edu.pl/images/OI18/okr-en-tex.3.png)) is    a period of ![](http://main.edu.pl/images/OI18/okr-en-tex.4.png) if ![](http://main.edu.pl/images/OI18/okr-en-tex.5.png) for all ![](http://main.edu.pl/images/OI18/okr-en-tex.6.png).

We denote the set of all periods of ![](http://main.edu.pl/images/OI18/okr-en-tex.7.png) by ![](http://main.edu.pl/images/OI18/okr-en-tex.8.png).

For example, ![](http://main.edu.pl/images/OI18/okr-en-tex.9.png), ![](http://main.edu.pl/images/OI18/okr-en-tex.10.png),    and ![](http://main.edu.pl/images/OI18/okr-en-tex.11.png).

Byteasar has decided that every name is to be changed to a sequence of bits    that:

has length matching that of the original name,                  has the same set of periods as the original name,                  is the smallest (lexicographically1)        sequence of bits satisfying the previous conditions.

For example, the name ABIABUABIAB should be changed to    01001101001, BABBAB to 010010, and    BABURBAB to 01000010.

Byteasar has asked you to write a program that would facilitate the    translation of his subjects' current names into new ones.

If you succeed, you may keep your current name as a reward!



## 输入格式

In the first line of the standard input there is a single integer ![](http://main.edu.pl/images/OI18/okr-en-tex.12.png)      - the number of names to be translated (![](http://main.edu.pl/images/OI18/okr-en-tex.13.png)).

The names are given in the following lines, one in each line.

Each name consists of no less than ![](http://main.edu.pl/images/OI18/okr-en-tex.14.png) and no more than ![](http://main.edu.pl/images/OI18/okr-en-tex.15.png)      upper-case (capital) letters (of the English alphabet).

In the test worth 30% of the points each name consists of at most ![](http://main.edu.pl/images/OI18/okr-en-tex.16.png)      letters.

## 输出格式

Your program should print ![](http://main.edu.pl/images/OI18/okr-en-tex.17.png) lines to the standard output.

Each successive line should hold a sequence of zeroes and ones      (without spaces in between) corresponding to the names given on the input.

If an appropriate sequence of bits does not exists for some names, then      "XXX" (without quotation marks) should be printed for that name.

## 样例

### 样例输入 #1
```
3
ABIABUABIAB
BABBAB
BABURBAB
```
### 样例输出 #1
```
01001101001
010010
01000010
```
## 提示



## 题目翻译

给定一个字符串 $S$，其长度为 $N$。

定义 $\textrm{Per}(S)$ 为 $S$ 的所有周期的集合。

多组数据，每次给一个 $S$，要求你构造一个 $01$ 串使得其 $\textrm{Per}$ 集合与 $S$ 相同。如果有多种答案，输出字典序最小的一种。

$T \leq 20$，$|S| \leq 2 \times 10^5$。


---

---
title: "[POI 2013] MUL-Multidrink"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3549
tag: ['图论', '2013', 'POI（波兰）', 'Special Judge', '构造']
---
# [POI 2013] MUL-Multidrink
## 题目描述

Byteasar lives in Byteburg, a city famous for its milk bars on every corner.

One day Byteasar came up with an idea of a "milk multidrink": he wants to  visit each milk bar for a drink exactly once.

Ideally, Byteasar would like to come up with a route such that the next bar  is always no further than two blocks (precisely: intersections) away from the  previous one.

The intersections in Byteburg are numbered from ![](http://main.edu.pl/images/OI20/mul-en-tex.1.png) to ![](http://main.edu.pl/images/OI20/mul-en-tex.2.png),  and all the streets are bidirectional.

Between each pair of intersections there is a unique direct route, ie, one  that does not visit any intersection twice.

Byteasar begins at the intersection no. ![](http://main.edu.pl/images/OI20/mul-en-tex.3.png) and finishes at the intersection  no. ![](http://main.edu.pl/images/OI20/mul-en-tex.4.png).

Your task is to find any route that satisfies Byteasar's requirements if such  a route exists.

An exemplary route satisfying the requirements is: ![](http://main.edu.pl/images/OI20/mul-en-tex.5.png)                There is no route that satisfies the requirements.

给一棵树，每次步伐大小只能为1或2，要求不重复的遍历n个节点，且起点为1，终点为n

## 输入格式

In the first line of the standard input there is a single integer ![](http://main.edu.pl/images/OI20/mul-en-tex.6.png)  (![](http://main.edu.pl/images/OI20/mul-en-tex.7.png)), denoting the number of intersections in Byteburg.

Each of the following ![](http://main.edu.pl/images/OI20/mul-en-tex.8.png) lines holds a pair of distinct integers ![](http://main.edu.pl/images/OI20/mul-en-tex.9.png)  and ![](http://main.edu.pl/images/OI20/mul-en-tex.10.png) (![](http://main.edu.pl/images/OI20/mul-en-tex.11.png)), separated by a single space, that  represent the street linking the intersections no. ![](http://main.edu.pl/images/OI20/mul-en-tex.12.png) and ![](http://main.edu.pl/images/OI20/mul-en-tex.13.png).

In tests worth ![](http://main.edu.pl/images/OI20/mul-en-tex.14.png) of all points the condition ![](http://main.edu.pl/images/OI20/mul-en-tex.15.png) holds.

## 输出格式

If there is no route satisfying Byteasar's requirements, your program  should print a single word "BRAK" (Polish for none),  without the quotation marks to the standard output.  Otherwise, your program  should print ![](http://main.edu.pl/images/OI20/mul-en-tex.16.png) lines to the standard output, the ![](http://main.edu.pl/images/OI20/mul-en-tex.17.png)-th of which should  contain the number of the ![](http://main.edu.pl/images/OI20/mul-en-tex.18.png)-th intersection on an arbitrary route  satisfying Byteasar's requirements.  Obviously, in that case the first line  should hold the number ![](http://main.edu.pl/images/OI20/mul-en-tex.19.png), and the ![](http://main.edu.pl/images/OI20/mul-en-tex.20.png)-th line - number ![](http://main.edu.pl/images/OI20/mul-en-tex.21.png).

## 样例

### 样例输入 #1
```
12
1 7
7 8
7 11
7 2
2 4
4 10
2 5
5 9
2 6
3 6
3 12

```
### 样例输出 #1
```
1
11
8
7
4
10
2
9
5
6
3
12

```
## 提示

给一棵树，每次步伐大小只能为 1 或 2，要求不重复的遍历 $n$ 个节点，且起点为 $1$，终点为 $n$。无解输出 BRAK。

$n\le 500000$



---

---
title: "[SDOI2017] 硬币游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3706
tag: ['字符串', '2017', '各省省选', '山东', 'Special Judge', '枚举', '构造']
---
# [SDOI2017] 硬币游戏
## 题目描述

周末同学们非常无聊，有人提议，咱们扔硬币玩吧，谁扔的硬币正面次数多谁胜利。


大家纷纷觉得这个游戏非常符合同学们的特色，但只是扔硬币实在是太单调了。


同学们觉得要加强趣味性，所以要找一个同学扔很多很多次硬币，其他同学记录下正反面情况。


用 $\texttt H$ 表示正面朝上，用 $\texttt T$ 表示反面朝上，扔很多次硬币后，会得到一个硬币序列。比如 $\texttt{HTT}$ 表示第一次正面朝上，后两次反面朝上。


但扔到什么时候停止呢？大家提议，选出 $n$ 个同学，每个同学猜一个长度为 $m$ 的序列，当某一个同学猜的序列在硬币序列中出现时，就不再扔硬币了，并且这个同学胜利，为了保证只有一个同学胜利，同学们猜的 $n$ 个序列两两不同。


很快，$n$ 个同学猜好序列，然后进入了紧张而又刺激的扔硬币环节。你想知道，如果硬币正反面朝上的概率相同，每个同学胜利的概率是多少。

## 输入格式

第一行两个整数 $n,m$。


接下里 $n$ 行，每行一个长度为 $m$ 的字符串，表示第 $i$ 个同学猜的序列。

## 输出格式

输出 $n$ 行，第 $i$ 行表示第 $i$ 个同学胜利的概率。选手输出与标准输出的绝对误差不超过 $10^{-6}$ 即视为正确。

## 样例

### 样例输入 #1
```
3 3
THT
TTH
HTT
```
### 样例输出 #1
```
0.3333333333
0.2500000000
0.4166666667
```
## 提示

对于 $10\%$ 的数据，$1\le n,m\le 3$。

对于 $40\%$ 的数据，$1\le n,m\le 18$。

另有 $20\%$ 的数据，$n=2$。

对于 $100\%$ 的数据，$1\le n,m\le 300$。



---

---
title: "[CTSC2008] 祭祀"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4298
tag: ['2008', '网络流', 'Special Judge', '二分图', '构造', 'CTSC/CTS']
---
# [CTSC2008] 祭祀
## 题目描述

在遥远的东方，有一个神秘的民族，自称 Y 族。他们世代居住在水面上，奉龙王为神。每逢重大庆典，Y 族都会在水面上举办盛大的祭祀活动。我们可以把 Y 族居住地水系看成一个由岔口和河道组成的网络。每条河道连接着两个岔口，并且水在河道内按照一个固定的方向流动。显然，水系中不会有环流（下图描述一个环流的例子）。

 ![](https://cdn.luogu.com.cn/upload/pic/15479.png)

由于人数众多的原因，Y 族的祭祀活动会在多个岔口上同时举行。出于对龙王的尊重，这些祭祀地点的选择必须非常慎重。准确地说，Y 族人认为，如果水流可以从一个祭祀点流到另外一个祭祀点，那么祭祀就会失去它神圣的意义。族长希望在保持祭祀神圣性的基础上，选择尽可能多的祭祀的地点。
## 输入格式

第一行包含两个用空格隔开的整数 $N$、$M$，分别表示岔口和河道的数目，岔口从 $1$ 到 $N$ 编号。

接下来 $M$ 行，每行包含两个用空格隔开的整数 $u$、$v$，描述一条连接岔口 $u$ 和岔口 $v$ 的河道，水流方向为自 $u$ 向 $v$。
## 输出格式

第一行包含一个整数 $K$，表示最多能选取的祭祀点的个数。

接下来一行输出一种可行的选取方案。对于每个岔口依次输出一个整数，如果在该岔口设置了祭祀点，那么输出一个 `1`，否则输出一个 `0`。应确保你输出的 `1` 的个数最多，且中间没有空格。

接下来一行输出，在选择最多祭祀点的前提下，每个岔口是否能够设置祭祀点。对于每个岔口依次输出一个整数，如果在该岔口能够设置祭祀点，那么输出一个 `1`，否则输出一个 `0`。

注意：多余的空格和换行可能会导致你的答案被判断为错误答案。
## 样例

### 样例输入 #1
```
4 4
1 2
3 4
3 2
4 2
```
### 样例输出 #1
```
2
1010
1011
```
## 提示

$N \le 100, M \le 1000$

在样例给出的水系中，不存在一种方法能够选择三个或者三个以上的祭祀点。包含两个祭祀点的测试点的方案有两种：

选择岔口 $1$ 与岔口 $3$（如样例输出第二行），选择岔口 $1$ 与岔口 $4$。

水流可以从任意岔口流至岔口 $2$。如果在岔口 $2$ 建立祭祀点，那么任意其他岔口都不能建立祭祀点但是在最优的一种祭祀点的选取方案中我们可以建立两个祭祀点，所以岔口 $2$ 不能建立祭祀点。对于其他岔口至少存在一个最优方案选择该岔口为祭祀点，所以输出为 `1011`。

感谢@ACdreamer 提供SPJ


---

---
title: "[ZJOI2018] 历史"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4338
tag: ['2018', '各省省选', '浙江', '树链剖分', '动态树 LCT', '构造']
---
# [ZJOI2018] 历史
## 题目背景

九条可怜是一个热爱阅读的女孩子。
## 题目描述

这个世界有 n 个城市，这 n 个城市被恰好 $n-1$ 条双向道路联通，即任意两个城市都可以 互相到达。同时城市 1 坐落在世界的中心，占领了这个城市就称霸了这个世界。

在最开始，这 n 个城市都不在任何国家的控制之下，但是随着社会的发展，一些城市会崛 起形成国家并夺取世界的霸权。为了方便，我们标记第 i 个城市崛起产生的国家为第 i 个国家。 在第 i 个城市崛起的过程中，第 i 个国家会取得城市 i 到城市 1 路径上所有城市的控制权。

新的城市的崛起往往意味着战争与死亡，若第 i 个国家在崛起中，需要取得一个原本被国 家 $j(j ≠ i)$ 控制的城市的控制权，那么国家 i 就必须向国家 j 宣战并进行战争。

现在，可怜知道了，在历史上，第 i 个城市一共崛起了 $a_i$ 次。但是这些事件发生的相对顺 序已经无从考究了，唯一的信息是，在一个城市崛起称霸世界之前，新的城市是不会崛起的。 

战争对人民来说是灾难性的。可怜定义一次崛起的灾难度为崛起的过程中会和多少不同的国家进行战争（和同一个国家进行多次战争只会被计入一次）。可怜想要知道，在所有可能的崛 起顺序中，灾难度之和最大是多少。

同时，在考古学家的努力下，越来越多的历史资料被发掘了出来，根据这些新的资料，可怜会对 $a_i$ 进行一些修正。具体来说，可怜会对 $a_i$ 进行一些操作，每次会将 $a_x$ 加上 w。她希望 在每次修改之后，都能计算得到最大的灾难度。

然而可怜对复杂的计算并不感兴趣，因此她想让你来帮她计算一下这些数值。
对题面的一些补充：

- 同一个城市多次崛起形成的国家是同一个国家，这意味着同一个城市连续崛起两次是不会 和任何国家开战的：因为这些城市原来就在它的控制之下。
- 在历史的演变过程中，第 i 个国家可能会有一段时间没有任何城市的控制权。但是这并不 意味着第 i 个国家灭亡了，在城市 i 崛起的时候，第 i 个国家仍然会取得 1 到 i 路径上的城市的控制权。
## 输入格式

第一行输入两个整数 n,m 表示城市个数和操作个数。 

第二行输入 n 个整数表示 ai 的初始值。 接下来 n − 1 行，每行输入两个整数 $u_i, v_i(1\leq ui, vi \leq n)$ 描述了一条道路。 

接下来 m 行每行输入两个整数 $x_i$, $w_i$ 表示将 $a_{x_i}$
加上 $w_i$。
## 输出格式

输出共 $m+1$ 行，第一行表示初始的 ai 的答案，接下来 m 行每行表示这次修正后的答案。
## 样例

### 样例输入 #1
```
5 3 
1 1 1 1 1 
1 2 
1 3 
2 4 
2 5 
2 1 
3 1
4 1
```
### 样例输出 #1
```
6 
7 
9
10
```
## 提示

在修正开始之前，如果按照所在城市 4, 1, 5, 3, 2 的顺序崛起，那么依次会和 0, 1, 2, 1, 2 个 国家进行战争。

这时一共会产生 6 对敌对关系。可以证明这是所有崛起顺序中的最大值。

![](https://cdn.luogu.com.cn/upload/pic/16016.png)


---

---
title: "[BJOI2018] 染色"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4429
tag: ['图论', '2018', '各省省选', '北京', 'O2优化', '排序', '拓扑排序', '构造']
---
# [BJOI2018] 染色
## 题目描述

pupil 喜欢给图的顶点染颜色。有一天，master 想刁难他，于是给了他一个无重边和自环的无向图，并且对每个点分别给了一个大小为 $2$ 的颜色集合，pupil 只能从这个集合中选一种颜色给这个点染色。master 希望 pupil 的染色方案使得没有两个有边相连的点被染了相同的颜色。

现在 pupil 想知道，是否无论 master 的颜色集合是什么，他均有办法按照要求染色。
## 输入格式

输入包含多组数据。

第一行一个正整数 $T$，表示数据组数。

之后每组数据第一行两个空格隔开的整数 $n,m$，表示这个无向图的点数和边数。

之后 $m$ 行，每行两个空格隔开的正整数 $i,j$，表示图中的一条连接点 $i$ 和点 $j$ 的边。

图的节点从 $1$ 开始标号。
## 输出格式

对于每组数据，如果 pupil 无论如何均能染色，输出一行一个字符串 `YES`，否则输出一行一个字符串 `NO`。
## 样例

### 样例输入 #1
```
3
6 9
1 2
1 4
1 6
3 2
3 4
3 6
5 2
5 4
5 6
2 1
1 2
3 3
1 2
1 3
2 3
```
### 样例输出 #1
```
NO
YES
NO
```
## 提示

### 样例解释

对于第一组数据，如果第一个点和第二个点的集合为 $\{A,B\}$，第三个点和第四个点的集合为 $\{A,C\}$，第五个点和第六个点的集合为 $\{B,C\}$，
则奇数点至少使用了两种颜色，偶数点至少使用了两种颜色，因此至少有一个奇数点和一个偶数点颜色相同。但每两个奇数点和每两个偶数点之间均有边，
因此无法满足“没有两个有边相连的点被染了相同的颜色”。

对于第二组数据，无论两个集合是什么，第一个点随便染它的集合中的其中一种颜色，第二个点染它的集合中某个与第一个点不同的颜色即可。

对于第三组数据，如果三个点的集合均是 $\{A,B\}$，那么无法满足“没有两个有边相连的点被染了相同的颜色”。

### 数据范围

- 对于 $10\%$ 的数据，$1 \leq n \leq 3$；
- 对于 $20\%$ 的数据，$1 \leq n \leq 6$；
- 对于 $50\%$ 的数据，$1 \leq n \leq 1000$，$0 \leq m \leq 2000$；
- 对于 $100\%$ 的数据，$1 \leq n \leq 10000$，$0 \leq m \leq 20000$，$1 \leq T \leq 10$。
- 另外存在 5 个不计分的 hack 数据。


---

---
title: "太极剑"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4704
tag: ['贪心', 'O2优化', '位运算', '构造', '洛谷月赛']
---
# 太极剑
## 题目描述

在学习太极之后，Bob 要求 Alice 教他太极剑。Alice 告诉他首先需要通过一项基本剑术测试。测试要求 Bob 尽可能快地切断 $n$ 根绳子。

所有绳子的端点两两不同，所以共有 $2n$ 个端点。这些端点被捆在一个圆上，等距离分布。我们把这些端点按顺时针方向编号为 $1$ 到 $2n$。

Bob 每次切割的轨迹是一条直线，可以将所有与这条直线相交的绳子切断，他想知道至少多少次可以切断所有的绳子。
## 输入格式

第一行一个整数 $n(1 \leq n \leq 2 \times 10^5)$，表示绳子的个数。

接下来 $n$ 行，每行两个整数 $a_i, b_i(1 \leq a_i, b_i \leq 2n, a_i \not= b_i)$，表示第 $i$ 根绳子的两个端点的编号。
## 输出格式

一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
2
1 2
3 4
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3
1 2
3 4
5 6
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
3
1 3
2 4
5 6
```
### 样例输出 #3
```
1
```
## 提示

样例一解释：![](https://cdn.luogu.com.cn/upload/pic/19179.png)

样例二解释：![](https://cdn.luogu.com.cn/upload/pic/19180.png)

样例三解释：![](https://cdn.luogu.com.cn/upload/pic/19181.png)


---

---
title: "多项式反三角函数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5265
tag: ['倍增', 'O2优化', '构造', '快速数论变换 NTT']
---
# 多项式反三角函数
## 题目描述

给定一个 $n-1$ 次多项式 $A(x)$，求一个 $\bmod{\:x^n}$ 下的多项式 $F(x)$，满足 $F(x)\equiv\text{asin}\:A(x)$ 或 $F(x)\equiv\text{atan}\:A(x)$。

所有运算在 $\bmod\ 998244353$ 意义下进行。
## 输入格式

第一行 **两个** 整数 $n,type$，若 $type=0$ 代表求 $\text{asin}$，若 $type=1$ 代表求 $\text{atan}$；

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
0 4 2 665496252 17 399297879 332748370 570426983
```
### 样例输入 #2
```
8 1
0 4 2 6 1 5 3 7
```
### 样例输出 #2
```
0 4 2 665496220 998244322 399297839 332748518 570424795
```
## 提示

对于 $100\%$ 的数据：$n\leq10^5$，$a_i\in[0,998244352]\cap\mathbb{Z}$。

前 $5$ 个点 $type=0$，后 $5$ 个点 $type=1$。


---

---
title: "[COCI 2019/2020 #2] Popcount"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6678
tag: ['2019', 'Special Judge', '构造', 'COCI（克罗地亚）']
---
# [COCI 2019/2020 #2] Popcount
## 题目背景

Miniature Algebraic Natural Relay 是小型可编程设备的最新技术进步。 您可以使用 MalnarScript 为此设备编写自己的程序。


## 题目描述

程序要求如下：

- 程序的输入是一个严格小于 $2^n$ 的单个非负整数。
- 程序的输出是一个严格小于 $2^n$ 的单个非负整数。
- 使用 MalnarScript 进行编程时，您只能使用一个 $n$ 位无符号整数变量 $a$。在程序的开头，此变量保存输入，并且其在程序末尾的值被视为程序的输出。
- MalnarScript 的源代码最多必须包含 $k$ 个格式为 $\texttt{a = <expr>}$ 的命令，这些命令按顺序执行，并且每个命令最多包含 $10^3$ 个字符。 

符号 $\texttt{<expr>}$ 的递归定义如下：

$$\texttt{<expr> = A | <num> | (<expr><operator><expr>)}$$

换句话说，符号 $\texttt{<expr>}$ 可以是变量 $a$ ，也可以符合符号 $\texttt{<num>}$ 的定义，或者在括号内表示二元表达式，其中每个操作数均符合相同的 $\texttt{<expr>}$ 定义。

上面定义中的符号 $\texttt{<num>}$ 表示严格小于 $2^n$ 的非负十进制整数。而符号 $\texttt{<operator>}$ 可以是 $\texttt{+}$，$\texttt{-}$，$\texttt{|}$，$\texttt{\&}$，$\texttt{<<}$ 或 $\texttt{>>}$，分别表示：加，减，按位或，按位与，左移和右移的运算。

此外，字符 $a$ 在 $\texttt{<expr>}$ 符号中最多出现 $5$ 次。

在执行加减运算时出现溢出或下溢时，MalnarScript 将以 $2^n$ 为模执行这些运算。例如，当 $n = 3$ 时，在 MalnarScript 中，$7 + 3 = 2$，$2 - 5 = 5$。

每个命令中方程式的右侧求和为一个数字，然后将其存储到 $a$ 中。为了计算右侧表达式，MalnarScript 首先将每次出现的 $a$ 替换为其当前值。 然后，像在任何数学表达式中一样进行表达式的计算，即，括号优先。请注意，运算符的优先级（按照运算顺序）是不相关的，因为最终结果完全由括号的位置定义。

您的任务是编写一个程序，该程序在 MalnarScript 中输出程序，该程序以输入值的二进制表示形式计算一个数。

## 输入格式

第一行，两个正整数 $n, k$，含义见 **题目描述**。
## 输出格式

第一行中，您应该输出产生的 MalnarScript 程序的命令数。

在其余各行中，您应该输出所需程序的命令。每个命令必须在单独的行中输出，并且必须满足任务描述中所述的 MalnarScript 语法。

重要的是，输出中不要有不必要的空行或多余的空格字符。
每行（包括最后一行）必须以换行（`\n`）结尾。
## 样例

### 样例输入 #1
```
2 2

```
### 样例输出 #1
```
1
A=(A-((A&2)>>1))

```
### 样例输入 #2
```
3 5

```
### 样例输出 #2
```
2
A=((A&4)|((A&3)-((A&2)>>1)))
A=((A&3)+((A&4)>>2))

```
## 提示

#### 数据范围及约定

| Subtask | 分数 | 数据范围及约定 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $15$ | $2 \le n \le 100$，$k = n \ − \ 1$ |
| $2$ | $15$ | $n = 500$，$k = 128$ |
| $3$ | $35$ | $1 \le n \le 40$，$k = 7$ |
| $4$ | $45$ | $100 \le n \le 500$，$k = 10$ |


#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2019-2020](https://hsin.hr/coci/archive/2019_2020/) [CONTEST #2](https://hsin.hr/coci/archive/2019_2020/contest2_tasks.pdf) *T4 Popcount*。**

感谢 @[Sprague_Garundy](https://www.luogu.com.cn/user/764746) 提供的 SPJ，SPJ 可以在题目附件处下载。

另外，由于 `testlib` 库在洛谷环境下生成随机数在 $N=31$ 时有问题，采用固定已生成随机数。部分测试点 $N$ 较大，Special Judge 程序运行较久，如下。

| 特殊测试点编号 | 时限 |
|:-:|:-:|
| 15 | 3s |
| 39 | 2s |
| 40 | 3s |
| 48 | 3s |

上述测试点时限仅用于 Special Judge 程序使用。


---

---
title: "一次函数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6690
tag: ['动态规划 DP', '2020', '洛谷原创', 'Special Judge', 'O2优化', '扩展欧几里德算法', '构造', '洛谷月赛']
---
# 一次函数
## 题目描述

给定 $n$ 个一次函数 $f_i(x) = a_ix + b_i$，其中 $x$ 为形式幂级数的占位符。

从这 $n$ 个中选出 $k$ 个 $g_i(x)$ （$1\leq i \leq k$），定义集合 $H$ 为 $g_i$ 的若干次幂的乘积模 $x^2$ 的值所构成的集合。即：

$$H=\left\{\prod_{i=1}^k g_i(x)^j\bmod x^2\middle|0 \leq a, b < p \right\}$$

其中 $j$ 是任意非负整数且对于每个 $i$ 可以有不同的 $j$。

需要注意的是，$0\cdot x+1$ 始终在集合 $H$ 中（而非 $0 \cdot x + 0$），即使 $k = 0$ 也是如此。

给定 $A, B$，求出所有满足 $Ax+B\in H$ 的集合 $H$ 的 $k$ 的最小值。

若不存在 $H$ 使得 $Ax+B\in H$，输出 `-1`。

所有运算均在模 $p$ 意义下进行。
## 输入格式

第一行四个整数 $n, p, A, B$。

接下来 $n$ 行，每行两个整数 $a_i, b_i$。
## 输出格式

第一行一个整数 $k$，表示答案。

若存在方案，接下来 $k$ 行，每行两个整数 $a, b$，需满足
$$\left(\prod f_a(x)^b\right)\bmod x^2=Ax + B$$

$a$ 的顺序可任意。
## 样例

### 样例输入 #1
```
1 997 603 648
200 61

```
### 样例输出 #1
```
1
1 140787

```
### 样例输入 #2
```
1 953 712 307
534 750

```
### 样例输出 #2
```
-1

```
### 样例输入 #3
```
3 7 6 5
3 4
5 6
4 6

```
### 样例输出 #3
```
2
2 5
1 20

```
## 提示

**另有两组大样例与 checker，下载地址见附件。**

要测试你某个测试点的答案，你需要在你本题目录下的命令行中执行：

``<checker> <input‐file> <output‐file> <answer‐file> [<report‐file>]``

其中：

* ``<checker>`` 表示校验器可执行文件；
* ``<input‐file>`` 表示该测试点的输入文件，如 ``func1.in``；
* ``<output‐file>`` 表示该测试点你的答案，如 ``func1.out``；
* ``<answer‐file>`` 表示该测试点的答案文件（只需要提供输出的第一行），如 ``func1.ans``；
* ``<report‐file>`` 为可选参数，如果没有给定该参数，校验器将输出至终端；否则将输出至该文件，如 ``report1.txt``。

对于所有数据，$2\leq p\leq 10^9$，保证 $p$ 为质数，$1\leq n \leq 5 \times 10^3$，$0\leq a_i, A < p$，$1\leq b_i, B < p$。

详细的数据限制及约定如下（留空表示和上述所有数据的约定相同）：

| 子任务编号 | 分值 | $n$ | $p$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $=1$ | $\leq 1000$ |  |
| $2$ | $5$ | $\leq 3$ | $=7$ |  |
| $3$ | $15$ | $\leq 100$ | $=31$ |  |
| $4$ | $20$ | |  | $A=B=1$ |
| $5$ | $25$ | $\leq 20$ |  |  |
| $6$ | $15$ | $\leq 500$ |  |  |
| $7$ | $15$ | |  |  |


---

---
title: "[SNOI2020] 排列"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6795
tag: ['贪心', '2020', '各省省选', 'Special Judge', '构造']
---
# [SNOI2020] 排列
## 题目描述

有一个 $n$ 阶排列 $p$，其前 $k$ 位 $p_1,p_2,\cdots,p_k$ 已经确定了。

定义排列 $p$ 中，$[l,r]$ 是一个值域连续段当且仅当：

$$\max(p_l, p_{l+1}, \dots, p_r) - \min(p_l, p_{l+1}, \dots, p_r) = r-l$$

$p$ 中值域连续段个数即所有 $1 \le l \le r \le n$ 中值域连续段的总数。

请你求出：所有可能的排列 $p$ 中，值域连续段个数的最大值，以及任意一种方案。
## 输入格式

第一行两个整数 $n,k$，分别表示排列的阶数和以及确定的位数。    
接下来一行由空格分隔的 $k$ 个正整数 $p_i$，表示排列一直的部分。（$k=0$ 则此行为空）
## 输出格式

输出第一行一个整数表示值域连续段个数的最大值。    
第二行 $n$ 个正整数表示任意一种方案。
## 样例

### 样例输入 #1
```
4 1
2
```
### 样例输出 #1
```
8
2 1 3 4
```
## 提示

#### 样例说明

对于样例 $1$，最优解为 $2,1,3,4$，有 $8$ 个值域连续段（$[1], [2], [3], [4], [1,2], [3,4], [1,3], [1,4]$）。$2,3,4,1$ 为另一个最优解。

#### 数据规模与约定

对于所有数据，$1\le n\le 2\times 10^5, 0\le k\le n$。

- 对于 $10\%$ 的数据，$n \le 10$；
- 对于另外 $20\%$ 的数据，$n \le 22$；
- 对于另外 $10\%$ 的数据，$k \le 1$；
- 对于另外 $20\%$ 的数据，$k=n$；
- 对于余下 $40\%$ 的数据，无特殊限制。


---

---
title: "[ICPC 2014 WF] Baggage"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6892
tag: ['2014', 'Special Judge', '构造', 'ICPC']
---
# [ICPC 2014 WF] Baggage
## 题目描述

An airline has two flights leaving at about the same time from ICPCity, one to city B and one to city A. The airline also has $n$ counters where passengers check their baggage. At each counter there is a pair of identical baggage bins, one for city B and one for city A.

Just before the flights depart, each pair of baggage bins is moved by a motorized cart to a sorting area. The cart always moves two bins at a time, one for city B and one for city A. After all the bins have been moved, they line up in the sorting area like this:

  B A B A B A ... B A 

That is, there are $2n$ baggage bins in a row, starting with a bin for city B, then one for city A, and so forth. The task now is to reorder them so all the baggage bins for city A precede the baggage bins for city B. Then the bins can be loaded on the appropriate aircraft.

The reordering is done by moving pairs of adjacent baggage bins (not necessarily B then A), again via the motorized cart. For proper balance, the cart must always carry two bins, never just one. A pair of bins must always be moved to an empty space that is at least two bins wide. On the left of the first bin are some empty spaces that can be used as needed during the reordering.

When the reordering process begins, the bin locations are numbered from $1$ (initially containing the leftmost B baggage bin) to $2n$ (initially containing the rightmost A baggage bin). There are $2n$ initially empty spaces to the left of the bins, numbered from $0$ to $-2n+1$, as shown in Figure 1 for the case $n=4$.
![](https://cdn.luogu.com.cn/upload/image_hosting/fwkcv2gq.png)

   Figure 1: Initial configuration of bins and empty spaces for $n = 4$ 

Given $n$, find a shortest sequence of moves that will reorder the bins so that all the A bins are to the left of all the B bins. At the end of the process, it is possible that the leftmost A bin is at some location other than $1$, but the bins must be adjacent in a sequence of $2n$ locations.
## 输入格式

The input consists of a single test case, which consists of the integer $n$ $(3 \leq n \leq 100)$.
## 输出格式

Display a shortest sequence of moves that will correctly reorder the bins. Each move is of the form “$f$ to $t$”, where $f$ and $t$ are integers representing the movement of the bins in locations $f$ and $f + 1$ to locations $t$ and $t + 1$. If multiple solutions are possible, display any one of them.
## 样例

### 样例输入 #1
```
5

```
### 样例输出 #1
```
8 to -1
3 to 8
6 to 3
0 to 6
9 to 0

```
### 样例输入 #2
```
8

```
### 样例输出 #2
```
10 to -1
3 to 10
14 to 3
7 to 14
0 to 7
11 to 0
4 to 11
15 to 4

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

有一无穷长的流水线 $a$，初始时 $\forall i\le0\text{ 和 } i>2n ,a_i=0$。**否则**，若 $i$ 为奇数，则 $a_i=2$；若 $i$ 为偶数，则 $a_i=1$。**也就是说，$a_i=2$ 和 $a_i=1$ 是交替出现的。**  

现需要进行若干次 **如下** 操作，使得 $a$ 中的所有 **非零元素** 为 **连续** 的一段且所有的 $1$ 均在 $2$ **前面**。  

选择两个位置 $p$ 和 $q$，满足 $a_p\ne0,a_{p+1}\ne0$ 且 $a_q=a_{q+1}=0$，将 $a_q$ 设为 $a_p$，$a_{q+1}$ 设为 $a_{p+1}$，并且将 $a_p$ 和 $a_{p+1}$ 均设为 $0$。**输出时将此操作表示为 ```p to q```（$p$  和 $q$ 是具体的值）**。  

最小化操作步数，并输出操作序列，出题人将用 $\text{Special Judge}$ 来评判您的答案的正确性。  


---

---
title: "「EZEC-6」游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7389
tag: ['Special Judge', 'O2优化', '构造']
---
# 「EZEC-6」游戏
## 题目描述

Alice 和 Bob 玩游戏。

Alice 初始有 $n$ 个石子，Bob 初始有 $m$ 个石子，他们进行若干轮游戏，第 $i$ 轮游戏的输者给赢者 $i$ 个石子，当某一轮输者的石子不足时，停止游戏。

给定 $n,m$，求出游戏最多进行的轮数（不包含结束轮），并构造一个只包含 `A` 与 `B` 的胜负序列，满足该序列的长度为你的答案，并且任何时刻每个人手里的石子数非负。


## 输入格式

**本题有多组数据**。

第一行一个正整数 $T$，表示数据组数。

对于每组数据：

一行 $2$ 个非负整数 $n,m$。
## 输出格式

对于每组数据：

第一行一个整数，表示游戏最多进行的轮数，记你的答案为 $x$；

第二行一个长度为 $x$ 的字符串，表示胜负序列。

若第 $i$ 轮 Alice 赢，则你的胜负序列的第 $i$ 位为 `A`，若第 $i$ 轮 Bob 赢，则你的胜负序列的第 $i$ 位为 `B`。
## 样例

### 样例输入 #1
```
3
1 1
0 3
1 3
```
### 样例输出 #1
```
2
BA
3
AAB
3
ABA
```
## 提示

**本题采用捆绑测试**。

- Subtask 1（6 points）：$n+m\le15$。
- Subtask 2（8 points）：$n=m$。
- Subtask 3（8 points）：$\sum n+m\le10^3$。
- Subtask 4（8 points）：$\sum n+m\le2\times10^4$。
- Subtask 5（25 points）：$\sum n+m\le4\times10^5$。
- Subtask 6（45 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le T\le10^3$，$0\le n,m\le2\times10^7$，$1\le n+m\le2\times10^7$，$\sum n+m\le2\times10^7$。

如果你答对了最多进行的轮数，而你构造的胜负序列不合法，你将得到该测试点 $20\%$ 的分数（下取整）。

注意，若你无法构造胜负序列，也请输出一个长度不为零的字符串。

**本题输出量较大，请使用较快的输出方法。**


---

---
title: "「EZEC-6」造树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7390
tag: ['贪心', '2021', 'O2优化', '排序', '构造', '双指针 two-pointer', 'Ad-hoc']
---
# 「EZEC-6」造树
## 题目背景

> 成体系的结论会产出“低猜想水平”的机械推导，但更多的题目中需要“高猜想水平”的灵感。

——command_block 《考前小贴士》

[](https://cdn.luogu.com.cn/upload/image_hosting/1m9hce9x.png)无脑选手出思维题。
## 题目描述

你要帮 djy 造一棵树，满足以下条件：

- 由 $n$ 个点组成。

- $i$ 号点的度数为 $a_i$。

定义一条边 $(i,j)$ 的价值为 $b_i\times b_j$，你要在满足上述两个条件下，使所有边的价值和最大。

保证存在这样的树。
## 输入格式

第一行一个整数 $type$，表示数据生成方式。

若 $type=0$：

第二行一个整数 $n$。

第三行 $n$ 个整数，第 $i$ 个数表示 $a_i$。

第四行 $n$ 个整数，第 $i$ 个数表示 $b_i$。

若 $type=1$：

给出一个数据生成器模板：

```cpp
int a[10000005],b[10000005];
unsigned seed;
unsigned rnd(unsigned x){
	x^=x<<13;
	x^=x>>17;
	x^=x<<5;
	return x;
}
int rad(int x,int y){
	seed=rnd(seed);
	return seed%(y-x+1)+x;
}
void init_data(){
	cin>>seed;
	for(int i=1;i<=n;i++)
		a[i]=1,b[i]=rad(1,500000);
	for(int i=1;i<=n-2;i++)
		a[rad(1,n)]++;
}
```

第二行一个整数 $n$。

之后调用 `init_data()`。

第三行一个整数 $seed$。
## 输出格式

一行一个整数 $ans$，表示最大的价值和。
## 样例

### 样例输入 #1
```
0
5
1 2 3 1 1 
5 3 1 7 9
```
### 样例输出 #1
```
42
```
### 样例输入 #2
```
1
10
114514
```
### 样例输出 #2
```
249899101316
```
## 提示

**本题采用捆绑测试。**

- Subtask0 (10 pts)：$n\le 6$，$type=0$；
- Subtask1 (20 pts)：$n\le 10^3$，$type=0$；
- Subtask2 (10 pts)：$n\le5\times10^5$，$b_i\le2$，$type=0$；
- Subtask3 (20 pts)：$n\le10^5$，$type=0$；
- Subtask4 (20 pts)：$n\le5\times10^5$，$type=0$；
- Subtask5 (20 pts)：$type=1$。

对于 $100\%$ 的数据，$2\le n\le10^7$，$1\le a_i\le n$，$1\le b_i\le5\times10^5$，$type\in\{0,1\}$，$0\le seed<2^{31}$。


---

---
title: "[THUSC 2016] 星露谷物语"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7449
tag: ['2016', '提交答案', 'Special Judge', '随机化', '构造', 'THUSC']
---
# [THUSC 2016] 星露谷物语
## 题目描述

最近，小葱为了忘记城市的喧嚣，来到了星露谷开始种地发家致富。但是，由于小葱把钱都拿去抽卡了，所以小葱并没有足够的钱来买种子。为了搜集足够的钱来养猪，小葱必须开始大规模的搜寻野菜工作。

星露谷是一个无限大的二维平面，你可以在这个二维平面内任意移动。小葱可能在星露谷的 $n$ 条线段上找到野菜，但是这些线段是有向的，小葱必须沿着线段的方向移动才能找到野菜。为了找到更多的野菜，小葱希望自己能把星露谷中所有可能出现野菜的地方全部走一遍。换句话说，对于每条线段，小葱都需要沿着该线段的方向将这条线段的每个点都经过一遍。当然，小葱可以选择分多次走一条线段，具体地讲，小葱可以在这条线段的任意位置离开这条线段，再从任意位置进入这条线段，只要保证路径的并集覆盖了这条有向线段即可。

小葱希望找到一条尽量短的路径，这条路径应该由 $m$ 条线段组成，并且覆盖了星露谷中的 $n$ 条有向线段。小葱可以选择星露谷的任意一个点作为路径的起点，同时它也必须是路径的终点，即小葱最终必须回到出发的位置。

现在，小葱要去写四子棋大作业了，他不知道该怎么规划自己的行走方案使得自己移动的距离尽量短，所以就把这个艰巨的任务交给聪明的你了。

**注意：如果有两条线段的某部分重合且方向相同，那么你在走过这一段的时候我们认为这两条线段的这部分都被走过了。**
## 输入格式

第一行包含一个整数 $n$，代表图中有向线段的数量。

接下来 $n$ 行，每行四个整数  $x_1,y_1,x_2,y_2$，代表这条线段是一条从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 的有向线段。
## 输出格式

第一行应包含一个整数 $m$，代表小葱所走的折线路径中点的数量，需要满足 $m\le\min(5n^2,5\times 10^6)$。 接下来 $m$ 行，按照路径的顺序依次输出路径上的点。每行应包含两个浮点数 $x,y$，用来描述一个点的横、纵坐标。其中，$x,y$ 请保留不超过 $5$ 位小数。
## 样例

### 样例输入 #1
```
3
0 0 0 100
0 100 100 100
100 100 0 0
```
### 样例输出 #1
```
4
0 0
0 100
100 100
0 0
```
### 样例输入 #2
```
3
0 0 0 100
1 51 1 49
0 100 0 0
```
### 样例输出 #2
```
5
0 0
0 100
1 51
1 49
0 100
```
## 提示

**本题为提交答案题，输入与 checker 将会在附件给出**

对于每组测试数据，如果你的输出格式不符合题目要求，或者你输出的路径并没有走完给定的条 $n$ 有向线段，那么该测试点得 $0$ 分。否则，我们会计算你给出路径的长度 $d$，并根据 $10$ 个评分参数 $a_1\ge a_2\ge...\ge a_{10}$ 计算你的得分：
$$\max\{i|d\le a_i,1\le i\le 10\}$$

数据保证 $a_1$ 足够大，以确保一个合法的方案至少可以得到 $1$ 分。
#### 样例解释
对于样例 $1$，小葱总共移动了 $200+100\sqrt2$ 的距离，这也是这组样例的最优解。

对于样例 $2$，在该组解中，小葱一共移动了 $202+\sqrt{2402}+\sqrt{2602}$ 的距离，但这并不是这组数据的最优解。



---

---
title: "[WFOI - 01] 翻转序列（requese）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7999
tag: ['洛谷原创', 'Special Judge', 'O2优化', '其它技巧', '构造', '洛谷月赛']
---
# [WFOI - 01] 翻转序列（requese）
## 题目背景

简化题意：[$\texttt{Link}$](https://www.luogu.com.cn/paste/kmmn8pyd)。

为什么做完这题你不去做做[这题](https://www.luogu.com.cn/problem/P8223)呢
## 题目描述

你需要在一台奇怪的电脑上排序一个 $1\sim n$ 的排列。

你可以选择一个数 $x$，然后你每次可以翻转一段长为 $x+1$ 或一段长为 $x-1$ 的序列。

请在 $20\times n$ 次内还原成 $1\sim n$ 的序列。

（出题人注：现在最优可以达到15000次以下，请尝试优化您的算法）
## 输入格式

输入共 $2$ 行：

第一行一个数 $n$。

第二行 $n$ 个数，表示序列 $a$。
## 输出格式

输出共 $m + 2$ 行。

前两行每行 $1$ 个数，分别是 $x,m$。$m$ 表示操作次数。

接下来 $m$ 行，每行两个数，表示翻转区间的左、右端点。

本题采用 $\text{SPJ}$，只要翻转操作正确即可给分。
## 样例

### 样例输入 #1
```
2
2 1
```
### 样例输出 #1
```
1
1
1 2
```
### 样例输入 #2
```
5
5 2 3 4 1
```
### 样例输出 #2
```
4
2
1 5
2 4
```
## 提示

- **样例 $1$ 解释：**
	
    翻转 $(1,2)$ 序列变成 $1,2$；
    
- **样例 $2$ 解释：** 

    翻转 $(1,5)$ 序列变成 $1,4,3,2,5$；

	翻转 $(2,4)$ 序列变成 $1,2,3,4,5$；
    
**本题采用 Subtask 捆绑测试。**

Subtask 编号 | 数据规模与约定
:-: | :-:
**Subtask #0** ($\texttt{1 pts}$) | $n=1$
**Subtask #1** ($\texttt{2 pts}$) | $n=2$
**Subtask #2** ($\texttt{3 pts}$) | $n=3$
**Subtask #3** ($\texttt{4 pts}$) | $n=4$
**Subtask #4** ($\texttt{20 pts}$) | $1\le n\le 50$
**Subtask #5** ($\texttt{20 pts}$) | $1\le n\le 100$
**Subtask #6** ($\texttt{50 pts}$) | $1\le n\le 10^3$

对于 $100\%$  的数据，$1\le n,a_i\le 10^3$，数据保证 $a$ 是一个 $1\sim n$ 的排列。


---

---
title: "[CEOI 2021] Newspapers"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8173
tag: ['2021', 'Special Judge', 'CEOI（中欧）', '构造', 'Ad-hoc']
---
# [CEOI 2021] Newspapers
## 题目背景

译自 CEOI2021 Day1 T3. [Newspapers](https://hsin.hr/ceoi/competition/ceoi2021_day1_tasks.pdf)。

## 题目描述

Ankica 和 Branko 在一张无向连通图上玩追逐游戏，游戏分为若干个回合，每一回合有如下两步：

- **Ankica 猜测 Branko 现在在哪个结点**。具体地，她将猜测 Branko 在某个特定的结点，如果正确，Branko 被抓住，游戏将会结束，否则：
- **Branko 穿过一条边**。换句话说，Branko将移动到一个相邻的结点，注意他**不能**不移动。

给出这张图，请求出 Ankica 是否总能在有限步内抓到 Branko 且不论 Branko 初始位置在哪以及如何移动。

更形式化地，我们把 Ankica 猜测的策略用 $A=(a_1,a_2,\dots,a_k)$ 表示，其中 $a_i$ 代表她第 $i$ 次猜测 Branko 在 $a_i$ 结点。

相似地，我们把 Branko 的移动也用 $B=(b_1,b_2,\dots,b_k)$ 表示，其中 $b_i$ 代表他在第 $i$ 回合前的位置。此外，对于 $B$ 中任意两个相邻的元素 $b_i$ 和 $b_{i+1}$（$1\leq i<k$），$b_i$ 和 $b_{i+1}$ 之间必定有一条边。注意对于 $A$ 没有这样的限制。

我们认为 Ankica 的猜测策略 $A$ 是成功的，当且仅当对于任意合法的 $B$ ，都存在 $i\in[1,k]$ 使得 $a_i=b_i$。

如果存在这样的策略，请输出使得 $k$ 最小的一组策略。
## 输入格式

输入第一行包含两个整数 $N$ 和 $M$，代表这张图的点数和边数。

接下来 $M$ 行两个整数 $u_i$，$v_i$，表示图上有一条连接 $u_i$，$v_i$ 的边。

输入保证图上无重边。
## 输出格式

如果不存在成功的策略 $A$，仅输出一行一个字符串 `NO`。

否则，第一行应输出一个字符串 `YES`。

第二行应输出该策略最小的 $k$。

第三行应包含 $k$ 个整数，其中第 $i$ 个整数表示 $a_i$。
## 样例

### 样例输入 #1
```
7 6
1 2
1 3
1 4
1 5
1 6
1 7

```
### 样例输出 #1
```
YES
2
1 1

```
### 样例输入 #2
```
6 6
1 2
2 3
3 1
1 4
2 5
3 6

```
### 样例输出 #2
```
NO

```
## 提示

#### 样例解释1

![捕获1.PNG](https://cdn.luogu.com.cn/upload/image_hosting/kajahhgy.png)

如果 Branko 初始位于 $1$ 号结点，则他会被抓住，否则他必定会移动到 $1$ 号结点，然后被抓住。

#### 样例解释2

![捕获2.PNG](https://cdn.luogu.com.cn/upload/image_hosting/rtcfz96j.png)

若 Branko 初始在环 $(1,2,3)$ 上且不与 $a_1$ 相同，则根据之后的 $a$ 必定能构造出使 $A$ 不合法的 $B$。

#### 子任务

所有测试点均满足 $1\leq N\leq 1000$，$N-1\leq M\leq \frac{N\times (N-1)}{2}$。

各子任务的约束条件如下：

| 子任务编号 | 分值 |                             限制                             |
| :--------: | :--: | :----------------------------------------------------------: |
|     $1$      |  $12$  |                       $1\leq N\leq 20$                       |
|     $2$      |  $8$   | $1\leq N\leq 1000$，$M=N-1$，且每个结点 $u\in[1，N-1]$ 都与 $u+1$ 有边 |
|     $3$      |  $80$  |                      $1\leq N\leq 1000$                      |

#### 评分细则

如果你仅能正确回答第一行，则你将得到该测试点 $50\%$ 的分数。

如果对于所有回答 `YES` 的测试点，你能提供一组 $k$ 非最小但正确的策略，你将得到该测试点 $75\%$ 的分数。注意，你提供的策略不能超过 $5N$ 轮，可以证明，任何一组最优策略都不会超出这个限制。

每个子任务的得分等于该子任务内得分最小的测试点得分。


---

---
title: "[WFOI - 02] I wanna moqueve（位移序列）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8223
tag: ['洛谷原创', 'Special Judge', 'O2优化', '随机化', '构造', '洛谷月赛']
---
# [WFOI - 02] I wanna moqueve（位移序列）
## 题目背景

> It's my fiesta.
>
> 一场前，kid 在 WFOIR1 的地图上，折戟沉沙；一场后，kid 从倒下的地方爬起。
> 
> kid 成功了，他不再是从前那个他了。

简化题意：[$\texttt{Link}$](https://www.luogu.com.cn/paste/dlxx9pm0)

为什么做完这题你不去做做[这题](https://www.luogu.com.cn/problem/P7999)呢
## 题目描述

kid 需要在一台奇怪的电脑上排序一个 $1\sim n$ 的排列，下一个存档点才会出现。

kid 可以选择一个数 $x$，然后接下来的每次操作，kid 可以向左或向右循环位移一段长为 $x$ 的序列（最左/右边的会平移至最右/左边）（位移量是 $1$）。

如果 kid 的操作次数超过了 $23\times n$，排列就会爆炸，kid 将会再次倒下。所以，请告诉 kid 一种还原序列的方案，剩下的操作就交给 €€£ 吧！
## 输入格式

输入共 $2$ 行：

第一行一个整数 $n$，表示序列长度。

第二行 $n$ 个整数，表示序列 $a$。
## 输出格式

输出共 $m + 2$ 行。

前两行每行 $1$ 个数，分别是 $x,m$。$m$ 表示操作次数。

接下来 $m$ 行，每行两个数，前一个数表示平移区间左端点，后一个数表示方向，$0$ 为向左，$1$ 为向右；

本题采用 $\text{SPJ}$，只要循环位移操作正确即可给分。
## 样例

### 样例输入 #1
```
3
2 3 1
```
### 样例输出 #1
```
2
2
2 0
1 0
```
### 样例输入 #2
```
5
4 2 3 5 1
```
### 样例输出 #2
```
3
3
3 1
1 1
2 0
```
## 提示

- **样例 $1$ 解释：**
	
    左移 $(2,3)$ 序列变成 $2,1,3$；
    
    左移 $(1,2)$ 序列变成 $1,2,3$；
    
- **样例 $2$ 解释：** 

    右移 $(3,5)$ 序列变成 $4,2,1,3,5$；

	右移 $(1,3)$ 序列变成 $1,4,2,3,5$；
    
    左移 $(2,4)$ 序列变成 $1,2,3,4,5$；
    
**本题采用 Subtask 捆绑测试。**

Subtask 编号 | 数据规模与约定
:-: | :-:
**Subtask #0** ($\texttt{1 pts}$) | $n=1$
**Subtask #1** ($\texttt{2 pts}$) | $n=2$
**Subtask #2** ($\texttt{3 pts}$) | $n=3$
**Subtask #3** ($\texttt{4 pts}$) | $n=4$
**Subtask #4** ($\texttt{20 pts}$) | $1\le n\le 50$
**Subtask #5** ($\texttt{20 pts}$) | $1\le n\le 100$
**Subtask #6** ($\texttt{50 pts}$) | $1\le n\le 10^3$

对于 $100\%$ 的数据，$1\le n,a_i\le 10^3$，数据保证 $a$ 是一个 $1\sim n$ 的排列。


---

---
title: "[WFOI - 02] I wanna cross the grid（穿越网格）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8224
tag: ['洛谷原创', '提交答案', 'Special Judge', 'O2优化', '模拟退火', '随机调整', '其它技巧', '构造', '洛谷月赛']
---
# [WFOI - 02] I wanna cross the grid（穿越网格）
## 题目背景

>  相信奇迹的人，本身比奇迹更伟大吧

突然，存档点落到了一个巨大的网格中，只有走过所有必经区域，才能出现下一个存档点...
## 题目描述

给定一张 $n$ 行 $m$ 列的网格图，行和列从 $1$ 开始编号，定义二元组 $(x,y)$ 表示第 $x$ 行第 $y$ 列的格子，每一行的第 $L$ 到第 $R$ 列的格子是必经区域，形式化地，设 $D$ 是必经区域集合，则 $D=\{(x,y)|1\leq x\leq n,L\leq y\leq R,x,y\in N_+\}$。

每次 kid 可以向上下左右四个方向走一步，且不能超过边界。形式化地，若现在 kid 现在在 $(x,y)$，则 kid 可以走到 $(x+1,y),(x,y+1),(x-1,y),(x,y-1)$。

初始时 kid 在 $(S_x,S_y)$（保证 $S_y=L$），他需要走过所有的必经区域，且任何一个格子最多只经过一次。形式化地，kid 走的路径形如一个二元组序列 $P=(x_1,y_1),(x_2,y_2)...(x_k,y_k)$，需要满足 $\forall (x_0,y_0)\in D，\exist i\in[1,k]，(x_0,y_0)=(x_i,y_i)$，且 $\forall i\not= j，(x_i,y_i)\not= (x_j,y_j)$。

同时，kid 还要记录一个通关序列 $p$，当 kid 第一次进入某一行的必经区域之后，就要把行号写在当前序列的后面，且立刻经过本行所有的必经区域。同时，$p$ 必须包含一个长度为 $L_q$ 的子序列 $q$ 才是一个合法的通关序列，从而真正通关。形式化地，$p$ 合法当且仅当存在长度为 $L_q$ 的序列 $c$ 满足 $p_{c_i}=q_i$，且 $c$ 单调上升。

同时，为了给 lindongli2004 降低操作难度，lindongli2004 希望 kid 走的步数越少越好。

给定 $n,m,L,R,S_x,S_y,q$，请你为 kid 规划一条通关路线，或者告诉他不存在一条路线。剩下的操作就交给 lindongli2004 吧！
## 输入格式

第一行 $8$ 个正整数 $n,m,L,R,S_x,S_y,L_q,s$，分别表示矩阵的行数和列数，必经区域的左边界和右边界，起点的 $x$ 坐标和 $y$ 坐标，序列 $q$ 的长度和评分参数。

第二行 $L_q$ 个不重复的正整数，表示序列 $q$ 。
## 输出格式

第一行一个字符串 `YES` 或者 `NO` 表示是否存在一条路径（不包含引号）。

若存在一条路径，第二行一个正整数 $cnt$ 表示路径长度，接下来 $cnt$ 行每行两个正整数 $x,y$ 表示路径的坐标。
## 样例

### 样例输入 #1
```
5 4 2 3 2 2 2 15
3 1
```
### 样例输出 #1
```
YES
15
2 2
2 3
3 3
3 2
4 2
4 3
5 3
5 2
5 1
4 1
3 1
2 1
1 1
1 2
1 3
```
## 提示

#### 数据范围：

$1\leq L\leq R\leq m$，$1\leq S_x\leq n$，其他详见下发文件。

#### 评分规则：

下发文件中第一行的最后一个数为 $s$，设你的操作步数为 $cnt$。那么
 - 若 $cnt\leq s$，你将获得 $10$ 分。
 - 若 $cnt> s$ 且能通关，你将获得 $9- \frac{cnt-s}{\lfloor\frac{n}{2}\rfloor}$ 分。
 - 若你不能通关，你将获得 $0$ 分。
 
#### checker：

[自取](/paste/c4omcrf2)

使用方法：在同一目录下，把下发的数据放到 data.in 中，把你的答案放到 data.out 中，编译运行即可。

注意事项：
 - 此 checker 默认存在一组方案，并 check 该方案是否合法。
 - 此 checker 的最大方案容量为 $2.5 \times 10^{8}$ ，也就是说，你的方案中不能有超过 $2.5 \times 10^{8}$ 个数。


---

---
title: "「Wdoi-6」未知之花魅知之旅"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8348
tag: ['数学', '洛谷原创', 'O2优化', '构造', '洛谷月赛']
---
# 「Wdoi-6」未知之花魅知之旅
## 题目背景

[![](https://cdn.luogu.com.cn/upload/image_hosting/glirwa55.png)](https://thwiki.cc/%E6%9C%AA%E7%9F%A5%E4%B9%8B%E8%8A%B1_%E9%AD%85%E7%9F%A5%E4%B9%8B%E6%97%85)

位于太平洋板块和亚欧板块消亡边界的日本，是世界上最多发地震的一个国家之一。2011 年 3 月 11 日，日本时间下午 2 时 46 分 18 秒，一场里氏 9 级的地震袭击了这个国家，随之而来的，是超过 10 米高的巨大海啸。妻离子散，家破人亡，是对这一悲剧性事件的最好描述。

2011 年 5 月，东方 Project 的创作者 ZUN，为地震中的灾民谱写了一张专辑，叫做《未知之花，魅知之旅》，所筹得的善款都被捐赠用于救灾赈灾之中。

-----

而到了近未来的科学世纪，莲子和梅莉在一次聊天之中，又谈论到了这场大地震。这场地震对传统宗教的摧残程度也颇深，数千所神社不同程度遭受到了损毁，也有不少神社的主殿全毁或者半毁。甚至就连外界的博丽神社，也因此被摧毁。

莲子与梅莉决定动身，前往外界的博丽神社，进入幻想乡中，通报这一消息。
## 题目描述

### 简要题意

称一个长度为 $n$ 的正整数数列是「$k$ - 好」的，当且仅当它满足以下条件：  

- 对于 $1< i< n$，满足 $a_{i-1},a_i,a_{i+1}$ 中最大的一个等于其他两个之和。
- 所有元素都不小于 $k$。

$T$ 组询问，每次询问给定 $(a_0,a_1,x,y,k)$，问是否存在「$k$ - 好」数列（长度不小于 $2$），前两项为 $a_0,a_1$ 并且有相邻两项依次为 $x,y$。

-----

### 原始题意

原本就门可罗雀的博丽神社，在地震之后，更显荒凉。莲子与梅莉紧赶慢赶来到了博丽神社，只看到了倒塌的鸟居。由于神社过于荒凉，莲子和梅莉决定先将神社给好好打扫一番，再进入幻想乡。

具体而言，神社中有若干个物件等待被整理，每个物件都有一个正整数魅力值。可以认为，每种魅力值的物件都有**足够多**个。从被遗落的绘马中，莲子得知了，在被地震摧毁前的博丽神社中的物件，应当具有如下特点：

- 每个物件都有一个**不小于** $k$ 的魅力值。
- 三个相邻物件的**最大**魅力值，是其他两个物件的魅力值**之和**。
- 前两个物件的魅力值分别为 $a_0, a_1$。
- 存在**相邻**的两个物件，魅力值依次为 $x, y$。

莲子和梅莉认为，如果能够从所有物件中选出一些进行排列，并满足如上特点的话，那么这样的神社是**美观**的，不会让她们一进入幻想乡就被灵梦退治。

很显然，由于物件的散佚，莲子和梅莉可能无法通过这些信息来使得神社变得**美观**。莲子和梅莉找到了你，希望你能告诉她们，在这样的规则下是否存在一种让神社变得**美观**的方案。

由于灵梦退治得太狠，她们担心自己的生命安全，因此她们会对你询问 $T$ 次，以确保你不是在糊弄她们。
## 输入格式

第一行输入一个正整数 $T$，表示数据组数，对于每一组数据：

- 每行输入 $5$ 个正整数，以空格隔开，分别为 $a_0,a_1,x,y,k$，含义如题目所述。
## 输出格式

- 对于每一组数据，输出一行 `yes` 或 `no`，即是否存在一种可以使得神社变得**美观**的方法。
## 样例

### 样例输入 #1
```
5
2 3 7 9 1
4 9 2 5 1
4 9 2 5 2
6 4 1 2 3
7 9 7 9 7
```
### 样例输出 #1
```
yes
yes
no
no
yes
```
## 提示

### 样例解释

- 针对第一次询问，$a_0=2,a_1=3$，莲子和梅莉可以将物件如下排列构造：$2,3,5,2,7,9,2,11,\dots$，其中 $a_5=7,a_6=9$，从而存在方案让神社变得美观。
- 针对第二次询问，$a_0=4,a_1=9$，莲子和梅莉可以将物件如下排列构造：$4,9,5,4,1,3,2,5,3,8,\dots$，其中 $a_6=2,a_7=5$，从而存在方案让神社变得美观。
- 针对第三次询问，由于要求 $a_i \geq k=2$，第二次询问中的方法失效，同时也可以证明不存在让神社变得美观的方法。
- 针对第四次询问，要求构造出的 $x=1,y=2$ 都小于等于 $3$，从而无法让神社变得美观。
- 针对第五次询问，显然 $a_0=7,a_1=9$ 就已经符合让神社变得美观的要求了。

### 数据范围

**本题采用捆绑测试。**

令 $n=\max(a_0,a_1,x,y,k)$。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|}\hline
\textbf{Subtask} & \textbf{\textsf{分值}} & \bm{T\le } & \bm{n\le }  & \textbf{\textsf{特殊性质}} & \textbf{Subtask \textsf{依赖}}\cr\hline
1 & 10 & 10 & 10  & - & - \cr\hline
2 & 20 & 300 & 1000 & \mathbf{A} & - \cr\hline
3 & 10 & 300 & 10^9 & \mathbf{B} & - \cr\hline
4 & 20 & 300 & 10^8 & \mathbf{C} & 1,2 \cr\hline
5 & 40 & 10^5 & 10^9 & - & 3,4 \cr\hline
\end{array}
$$

- 特殊性质 $\mathbf{A}$：每次询问的 $k$ 相同。
- 特殊性质 $\mathbf{B}$：$k=1$。
- 特殊性质 $\mathbf{C}$：$\sum n \leq 10^8$。

对于 $100\%$ 的数据，$1 \leq n \leq 10^9,1 \leq T \leq 10^5$。


---

---
title: "[PFOI Round1] Two Subsegments"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8381
tag: ['洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# [PFOI Round1] Two Subsegments
## 题目背景

>洛谷知名网红，€€£官方团队团主 [€€£](https://www.luogu.com.cn/user/559616) 同志，因联合省选寄，医院抢救无效，于 4 月 17 日 g 了。

> [€€£](https://www.luogu.com.cn/user/559616) 是知名洛谷人，2021年加入洛谷，同年成立 €€£ 官方团队。在他在位期间勤勤恳恳，认真整活，发奋出题，为整活革命化、现代化、正规化建设作出了贡献。

对于 [€€£](https://www.luogu.com.cn/user/559616) 的退役，[Uvocde](https://www.luogu.com.cn/user/111084) 深感悲痛。这时，他想起了 [€€£](https://www.luogu.com.cn/user/559616) 对构造的深爱，于是便出了这道题来缅怀 [€€£](https://www.luogu.com.cn/user/559616)。
## 题目描述

有 $T$ 组询问，每组询问给出一个长为 $n$ 的序列 $a$，保证 $a$ 是 $1\sim n$ 的排列。

你可以选择一个数 $x$，然后你每次可以将一段长为 $x+1$ 或一段长为 $x-1$ 的序列在原序列中前移或后移 $x$ 位，将经过的部分移到空出来的地方。

请在 $80\times n$ 次内将 $a$ 排成升序。
## 输入格式

第一行一个正整数 $T$。

接下来 $2 \times T$ 行，每两行代表一组询问。

对于每组询问，格式为：先一行一个正整数 $n$，接下来一行 $n$ 个正整数，代表 $a_1,\ldots,a_n$。
## 输出格式

输出共 $T$ 组。

一组询问如果无解，仅输出一个 $-1$。

如果有解，则输出共 $m+2$ 行：

前两行每行一个数，分别是 $x,m$，其中 $m$ 表示操作次数，$x$ 如题意。

接下来 $m$ 行，每行三个数，第一个数表示方向（向左是 $0$，向右是 $1$），接下来两个数 $l,r$ 代表平移区间的左、右端点。

你的方案需要保证：

- $2\leq x\leq n$，$0\leq m\leq 80n$；
- 对每一次操作，有：
  - $1\leq l\leq r\leq n$；
  - $r-l+1=x-1$ 或 $r-l+1=x+1$；
  - 右移时 $r\leq n-x$，左移时 $l\geq x+1$。

本题采用 $\text{SPJ}$，只要调换操作正确或正确判断无解即可给分。
## 样例

### 样例输入 #1
```
2
7
2 1 4 7 6 5 3
2
2 1
```
### 样例输出 #1
```
3
4
1 1 4
1 2 3
1 1 2
0 5 6
-1
```
## 提示

【样例解释】

对于 $2\ 1\ 4\ 7\ 6\ 5\ 3$ 这组样例：

$x$ 取 $3$，共进行 $4$ 次操作：

0. **2 1 4 7** 6 5 3，向右平移；
1. 6 **5 3** 2 1 4 7，向右平移；
2. **6 2** 1 4 5 3 7，向右平移；
3. 1 4 5 6 **2 3** 7，向左平移；
4. 1 2 3 4 5 6 7，排序完成。

 
---

【数据范围】
  
  对于 $100\%$ 的数据，$1\le T\le10^4,\ 2\le n\le 10^4,\ \sum n\le10^4$，**保证排列在所有排列中等概率随机**。  
  
 | $\text{Subtasks}$ | 测试点数 | 数据范围 |分值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $\text{Subtask0}$ | $1$ | $n\leq 5$ | $\text{2pts}$ |
| $\text{Subtask1}$ | $7$ | $n\leq 50$ |$\text{7pts}$ |
| $\text{Subtask2}$ | $9$ | $n\leq 10^3$ |$\text{27pts}$ |
| $\text{Subtask3}$ | $14$ | $n\leq 5\times 10^3$ |$\text{27pts}$ |
| $\text{Subtask4}$ | $9$ | $n\leq 10^4$ | $\text{37pts}$ |



---

---
title: "[THUPC 2022 决赛] 拯救还是毁灭"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8416
tag: ['贪心', '2022', 'Special Judge', 'O2优化', '构造', 'THUPC']
---
# [THUPC 2022 决赛] 拯救还是毁灭
## 题目描述

*有人说，它拯救了世界；也有人说，它毁灭了世界。*

这个世界危在旦夕！秩序已然一片混乱。

秩序可以抽象成一个 $n\times n$ 的矩阵，矩阵中是一个 $1\sim n^2$ 的排列。你想要拯救世界，于是请来了神，来帮忙把秩序恢复原状。然而神也不是万能的，它只能做到交换矩阵中同一行或者同一列中的两个数。而且，它并不知道要怎么交换才能复原，得听你的指导。

幸好，你不一定需要在最少的交换次数之内完成复原。你只需要不比最糟糕的情况差就好。也就是说，如果你的交换次数为 $k$，且对于所有 $1\sim n^2$ 的排列，最小交换次数的最大值为 $k_0$，你只需要满足 $k\le k_0$。

注：复原指的是将矩阵变为如下的一个矩阵：

$\begin{matrix} 1 & 2 & 3 & \cdots & n \\ n+1 & n+2 & n+3 & \cdots & 2n \\ 2n+1 & 2n+2 & 2n+3 & \cdots & 3n\\ \vdots & \vdots & \vdots & \ddots & \vdots \\ (n-1)n+1 & (n-1)n+2 & (n-1)n+3 & \cdots & n^2 \end{matrix}$
## 输入格式

接下来 $n$ 行，每行 $n$ 个正整数，表示这个 $n\times n$ 的矩阵。保证 $1\sim n^2$ 中的每个数恰好出现一次。
## 输出格式

第一行一个非负整数 $k$，表示你的交换次数。

接下来 $k$ 行，每行四个正整数 $x_1,y_1,x_2,y_2$，表示将第 $x_1$ 行 $y_1$ 列的数与第 $x_2$ 行 $y_2$ 列的数交换。

你需要保证 $x_1=x_2$ 或 $y_1=y_2$。
## 样例

### 样例输入 #1
```
2
4 2
3 1

```
### 样例输出 #1
```
3
1 1 1 2
1 2 2 2
1 1 1 2

```
### 样例输入 #2
```
2
2 1
3 4

```
### 样例输出 #2
```
3
2 1 2 2
1 1 1 2
2 1 2 2

```
### 样例输入 #3
```
2
3 2
1 4

```
### 样例输出 #3
```
2
1 1 1 1
1 1 2 1

```
### 样例输入 #4
```
2
1 2
3 4

```
### 样例输出 #4
```
0

```
## 提示

【样例 1 解释】

可以证明这是交换次数最少的方案之一，显然它符合条件。

【样例 2 解释】

对于这个输入来说，这个样例输出的方案不是交换次数最少的方案，但是我们知道存在一个 $1\sim n^2$ 的排列（即上一个样例）需要至少 $3$ 次的交换，所以这个方案也是可行的。

【样例 3 解释】

我们允许出现 $(x_1,y_1)=(x_2,y_2)$ 的情况。

【样例 4 解释】

注意 $k$ 可以等于 $0$。

【数据范围与约定】

保证 $1\le n\le 1000$。

保证输入的矩阵中 $1\sim n^2$ 恰好各出现一次。


---

---
title: "「Wdoi-2」魔力的雷云"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8542
tag: ['洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 「Wdoi-2」魔力的雷云
## 题目背景

道具会自己活动，本来温顺的妖怪突然大闹起来原来都是因为万宝槌的影响。  
唆使小人的天邪鬼虽然最后逃走了，但因为真正使用万宝槌的是小人，所以灵梦决定对其进行监视。但是总感觉也没再有什么不良企图的样子。  

但就在那时，天空再次出现了诡异的云团。  
是与逆城出现之时一样的，魔力风暴。

“那不是我干的”，少名针妙丸这样解释着  
到底，又是谁再次掀起了这样的风暴？  
灵梦她们，为了调查清楚原因，再次冲进了风暴之中。

小人的末裔、逆转的城、为反抗而反抗的天邪鬼。  
这背后又隐藏着什么呢。
## 题目描述

### 简要题意

$n$ 块磁铁排列成了一个环。每块磁铁都有磁力，用 $4^{a_i}$ 表示。相邻两块磁铁**磁力大小不同**。磁铁大小一致，长度均为 $1$ 单位长度。摆放时分为北极朝左和北极朝右。当两块磁铁互相吸引时，它们会紧紧靠拢，互相排斥时，记这两块磁铁的磁力为 $u$ 和 $v$，那么它们会相距 $u+v$ 单位长度。

目前已知**整个环**的长度（包括**每个**磁铁的长度，以及相邻磁铁之间的距离），记这个长度为 $d_0$ 个单位长度。对于第 $i$ 块磁铁，也已知若拿去这块磁铁，剩余磁铁组成的环的长度，记这个长度为 $d_i$ 个单位长度。

找到找到任意一种可能的磁铁排列方法满足这些已知的数据，（也要满足相邻两块磁铁磁力大小不同），并且可以决定所用磁铁的磁力。保证有解。

### 原始题意

在堀川雷鼓引发的雷暴中，一架架周围附带着电磁场的鼓正随着节奏摇摆着。在强大的电磁干扰下，巫女和魔法使与地面失去了联系。

这些尺寸完全相同（可以视作为单位长度 $1$）的带有磁力的鼓一共有 $n$ 架，它们排列成了一个环。为了让弹幕美观，第 $i$ 架鼓上带有的磁力是 $4^{a_i}$，而且相邻两架鼓带有的磁力大小不同。

每一架鼓都有磁性上的南北两极，而且在摆放的时候有北极朝左和北极朝右的两种情况。若两架鼓相互吸引它们会紧紧靠拢；而若它们相互排斥，这两架鼓之间的距离就是它们的磁力之和的单位长度。

灵梦记录下了整个环的长度 $d_0$，这包括了每架鼓的长度和相邻的鼓之间的距离，而魔理沙正在使用自己的火力击碎这些鼓。然而这些鼓的质量非常皮实，魔理沙一次只能击碎一个鼓，随后堀川雷鼓会用一个尺寸和磁力完全一致的鼓替代这个被击碎的鼓。但是在击碎第 $i$ 架鼓的时候，受到磁力的作用环的长度会发生变化，魔理沙会记录此时剩余的鼓组成的环的长度 $d_i$（假设磁力的作用是瞬间完成的）。

在战斗的间隙，灵梦和魔理沙希望通过她们记录下的数据，找到任意一种鼓的排布情况满足这些数据。为了降低难度，她们可以自由决定每架鼓上的磁力多少。数据保证有解。

尽快解出鼓的分布，从而结束这场异变吧！
## 输入格式

- 第一行有一个整数 $n$，表示磁铁的总个数。
- 接下来 $1$ 行一个整数，表示 $d_0$。
- 接下来 $n$ 行每行一个整数，其中第 $i$ 行的整数表示 $d_i$。
## 输出格式

- 输出共 $n$ 行。第 $i$ 行有两个整数 $f_i,a_i$，分别表示磁铁的方向与磁力。若 $f_i=0$ 则表示北极向左，否则若 $f_i=1$ 则表示北极向右。
## 样例

### 样例输入 #1
```
4
14
13
16
3
16
```
### 样例输出 #1
```
1 1
1 0
0 1
1 0
```
## 提示

### 样例 1 解释

一种合法的方案中，$c=\{1,1,0,1\}$，$a=\{1,0,1,0\}$。以下是这种方案的图解。

初始时磁铁的状态如下图所示，磁铁上方的数字是它的磁力大小（即 $4^{a_i}$ 的值），磁铁上标记的 $\textsf{N/S}$ 是它的磁极。由于笔者能力有限，无法还原出环形，只能用这种传送门的方式扭曲时空了。

![](https://cdn.luogu.com.cn/upload/image_hosting/tdbb4nqb.png)

容易发现，总长度为 $14$。

![](https://cdn.luogu.com.cn/upload/image_hosting/wmagcu24.png)

拿掉第一块磁铁后的情形如图所示。容易发现，总长度为 $13$。

![](https://cdn.luogu.com.cn/upload/image_hosting/eipnbj08.png)

拿掉第二块磁铁后的情形如图所示。由于缺少了第二块磁铁的阻挡，第一块和第三块磁铁直接相邻，产生了更大的间距。可以发现，总长度为 $16$。

![](https://cdn.luogu.com.cn/upload/image_hosting/830j9rz5.png)

拿掉第三块磁铁后的情形如图所示。值得注意的是，所有磁铁北极方向相同，于是直接互相接触，总长度为 $3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/afqw0jx4.png)

拿掉第四块磁铁后的情形如图所示。由于第三块和第一块磁铁直接相邻（因为是形成了环。在图上则是扭曲后的空间里相邻），因此形成了这种模样。总长度为 $16$。

### 数据范围及约定

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|}\hline
\textbf{Subtask} & \bm{n\le} & \textbf{特殊性质} & \textbf{分值} \\\hline
1 & 10 & - & 10 \\\hline
2 & 10^5 & - & 30 \\\hline
3 & 10^6 & \text{A} & 5 \\\hline
4 & 10^6 & - & 55 \\\hline
\end{array}$$

**特殊性质** $\textbf{A}$：保证存在一种方案，所有磁铁的方向一致。

对于所有数据，保证 $1\leq n\leq 1\times10^6$，存在至少一种合法方案。此外，保证 $d_i< 2^{63}$，你构造的 $a_i$ 大小应该在 $[0,10^9]$。


---

---
title: "「Wdoi-2」不败的无尽兵团"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8545
tag: ['数论', '洛谷原创', '提交答案', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 「Wdoi-2」不败的无尽兵团
## 题目背景

畜生界是一个被动物灵所占据的，究极的弱肉强食的空间，也是个被几个组织所支配的世界——劲牙组、鬼杰组、刚欲同盟……

在这些动物灵其中也有一些灵长类动物的灵，也就是人类灵，它们弱小但又手脚灵活，作为完完全全的奴隶苟存在灵长园这一娱乐设施中。

但人类的灵也是有信仰的，它们向神明祈求，神也回应了人类的祈求，向人类给予了信仰的偶像。然而，人类灵原本只是皈依于存在于偶像背后的神性，却逐渐开始信仰起偶像本身来。结果，自然而然地，偶像开始支配人类，使得灵长园变成一个凶恶的失控组织。

畜生界也因为灵长园的暴动变得混乱，为了打倒偶像，鬼杰组希望能够卷入地上的人类，借用人类之手毁灭灵长园。动物灵们也就来到了地上，也就是幻想乡，带领灵梦一行人一同前往地狱。
## 题目描述

### 简要题意

对于正整数 $n$（$n$ 为 $529$ 或 $625$），$A=\{1,2,\cdots,n\}$ 的 $m \ge 2$ 个子集 $B_1,B_2,\cdots,B_m(|B_i| \geq 3)$ 为好的，如果对于 $A$ 的每一个三元子集 $C$，都存在 **恰好** 一个 $i$ 使得 $C$ 为 $B_i$ 的子集。构造一个好的子集族使得 $m$ 尽量小（不超过题目给定的评分参数）。

### 原始题意

一路进入畜生界的灵梦，遭遇到了埴轮兵团的首长，杖刀偶磨弓的阻拦。

埴轮兵团由 $n$ 个战士组成，它们编号为 $1,2,\dots,n$。战士数量为 $529$ 或者 $625$。作为一个兵团，要做到最好的进攻与防守，埴轮之间存在 $m$ 组配合关系 $B_1,B_2,\dots,B_m$，每组关系包含若干个不同（但不少于 $3$ 个）的埴轮战士，但不同组的关系中包含的埴轮战士可以重复。

但是灵梦并不事先知道这些配合关系，而且由于埴轮兵团配合默契，灵梦难以强行击败它们。在动物灵的帮助之下，灵梦发现，这些埴轮满足如下特点：从埴轮兵团中任意选出 $3$ 个埴轮，都存在 **恰好** 一个 $i$，使得这三个埴轮是 $B_i$ 的一个子集。在满足这个特点的基础之上，由于磨弓的精力有限，无法同时维护太多组配合关系。因此，$m$ 是一个大于等于 $2$ 的一个正整数，且其小于等于 $m_{ans}$。

现在灵梦告诉了你埴轮兵团的总人数，请你告诉她一种可能的埴轮兵团配合的情况，帮助她打败杖刀偶磨弓，进入灵长园。
## 输入格式

第一行有一个正整数 $n$，含义如题意所示。保证 $n=529$ 或者 $625$。
## 输出格式

第一行输出一个正整数 $m$，表示你构造的方案使用的集合的总个数。应当满足 $m\ge 2$。

接下来 $m$ 行，每行输出若干个整数。第一个整数 $s$ 表示你构造的 $B_i$ 的大小，应当满足 $n\ge s>0$。接下来 $s$ 个整数描述 $B_i$ 内的元素，中间用空格隔开。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
4
3 1 2 3
3 1 2 4
3 1 3 4
3 2 3 4
```
### 样例输入 #2
```
5
```
### 样例输出 #2
```
7
4 1 2 3 4
3 1 2 5
3 1 3 5
3 1 4 5
3 2 3 5
3 2 4 5
3 3 4 5

```
## 提示

### 样例 1 解释

**样例仅供理解题意参考。实际数据中，$n$ 只会为 $529$ 或 $625$。**

由于 $m>1$，因此结果不能为 $\{\{1,2,3,4\}\}$；又因为 $|B_i|< 3$ 时 $B_i$ 无用，于是唯一的方案就是列出 $\{1,2,3,4\}$ 的所有三元子集 $\{\{1,2,3\},\{1,2,4\},\{1,3,4\},\{2,3,4\}\}$。

### 数据范围及约定

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|}\hline
\textbf{Subtask} & \bm{n=} & \bm{m_{\text{ans}}=} & \textbf{分值} \cr\hline
1 & 529 & 1.25\times 10^4 & 75 \cr\hline
2 & 625 & 1.60\times 10^4 & 25 \cr\hline
\end{array}$$

如果你输出的方案不合法，那么你将不能获得该测试点的得分。

当你构造的解符合题设，并且 $m$ 的值不超过 $m_{\text{ans}}$，你才能获得该测试点的分值。


---

---
title: "醒来"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8553
tag: ['递归', '洛谷原创', 'Special Judge', 'O2优化', '分治', '构造', '洛谷月赛']
---
# 醒来
## 题目背景


“那羡慕的烟火去哪了，那信任的朋友疏远了。

我年幼时坚持过什么，你们还记不记得。”

回想自己儿时的样子，已和现在大不相同了；但想想昨天的自己，却与今天没什么差异。这不经意的改变，让我们已经是另一个样子了。
## 题目描述

赫尔德用一个长为 $r-l+1$ 的数列 $a$ 来描述自己性格的变化。但赫尔德记忆不好，她已经记不清 $a$ 了，只记得非负整数 $l,r$，其中 $l<r$。

不过，她还记得：

1.  $l\le a_i\le r$，且 $a_i$ 互不相同。换言之，$a$ 是一个 $l\sim r$ 的排列。
2.  对于所有 $1\le i\le r-l$，有 $\operatorname{popcount}(a_i \mathbin{\mathrm{xor}} a_{i+1})=1$。换言之，$a$ 中相邻的两个数二进制下只相差一位。

请你告诉她一个可能的 $a$，或告诉她其实不存在这样的 $a$。
## 输入格式

仅一行，两个非负整数 $l,r$。
## 输出格式

第一行，若有解输出 `Yes`，若无解则输出 `No`。不区分大小写。

若你输出了 `Yes`，则你可以用以下两种格式之一输出你的构造：

1. 输出一行 $r-l+1$ 个数，表示你构造的排列。
3. 先输出一个数，表示你构造排列的第一个数。接下来输出一个长为 $r-l$ 的字符串，对于第 $i$ 个字符，若你构造排列第 $i$ 与 $i+1$ 个数相差了 $2^k$，则你应该输出第 $k+1$ 个小写英文字母，即 `(char)('a'+k)`。 

**注意，若你使用格式 1 输出，你可能无法通过最后两个子任务。若您获得了 UKE 的评测结果，请考虑修改输出答案的格式。**

---

**【评分方法】**

本题采用**自定义校验器**检测你的输出。

若你对解的存在性判断错误，你无法获得任何分数。

若你对解的存在性判断正确，你可以获得 $40\%$ 的分数；若解不存在或你给出了一组正确的构造，则你可以获得剩下 $60\%$ 的分数。
## 样例

### 样例输入 #1
```
0 7

```
### 样例输出 #1
```
Yes
0 1 3 2 6 7 5 4

```
### 样例输入 #2
```
0 7

```
### 样例输出 #2
```
yEs
0 abacaba

```
### 样例输入 #3
```
0 7

```
### 样例输出 #3
```
yes

```
### 样例输入 #4
```
3 5

```
### 样例输出 #4
```
No

```
## 提示

**【样例解释 \#1、\#2、\#3】**

样例输出 \#1 和 \#2 对应同一个数列，即 $\{ 0, 1, 3, 2, 6, 7, 5, 4 \}$，它们均能获得该测试点 $100 \%$ 的分数。

样例输出 \#3 能获得该测试点 $40 \%$ 的分数。

----

**【数据范围】**

对于所有数据，保证 $0\le l<r\le 10^7$。

设 $n=r-l+1$。

$$
\def{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline 
\textbf{子任务编号}&\bm{~~~~~~~~n\le~~~~~~~~}&~~~~\textbf{特殊限制}~~~~&\textbf{分数}\cr\hline 
\textsf1 & 10& &9\cr\hline 
\textsf2 & 20& &9 \cr\hline 
\textsf3 & 10^5&\textsf{A, B}&10\cr\hline 
\textsf4 & 10^5 &\sf A&10\cr\hline 
\textsf5 & 2000& \textsf C&25 \cr\hline
\textsf6 & 5\times 10^5&\textsf D&20\cr\hline
\textsf7 & 3\times 10^6&&10\cr\hline
\textsf8 & &&7\cr\hline
\end{array}
$$

$\textsf A$：保证 $l=0$。

$\textsf B$：保证 $n$ 是 $2$ 的整数次幂。

$\textsf C$：保证 $l$ 是偶数，$r$ 是奇数。

$\textsf D$：本子任务有 5 个测试点，从所有 $n\ge 2\times 10^5$ 且有解的数据中随机生成。

---

即使一直在改变，赫尔德也许仍似儿时的自己。


---

---
title: "[北大集训 2021] 末日魔法少女计划"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8984
tag: ['动态规划 DP', '2021', 'Special Judge', '分治', '构造']
---
# [北大集训 2021] 末日魔法少女计划
## 题目背景

CTT2021 D1T1
## 题目描述

对于给定的 $n,k$，你需要构造一个只含 $0,1$ 的矩阵 $A_{i,j}$，$0\le i,j\le n$，满足：

1. $A_{i,i}=1$；
2. $A_{i,i+1}=1$；
3. 对 $i>j$ 有 $A_{i,j}=0$；
4. 若 $A_{i,j}=1$，$j-i>1$，则存在 $i<t<j$，满足 $A_{i,t}=A_{t,j}=1$；
5. 对 $i\le j$ 有 $(A^k)_{i,j}>0$。

你需要输出满足 $A_{i,j}=1$ 且 $j-i>1$ 的每个 $(i,j)$，设这样的 $(i,j)$ 共有 $m$ 个。

若输出不满足要求，则不能得到该测试点的任何分数。若输出满足要求，则根据 $m$ 进行评分。

## 输入格式

一行，两个整数 $n,k$。

## 输出格式

第一行一个整数 $m$，接下来 $m$ 行，每行两个整数 $i,j$，依次表示每个满足 $A_{i,j}=1$ 且 $j-i>1$ 的二元组 $(i,j)$。
## 样例

### 样例输入 #1
```
3 2
```
### 样例输出 #1
```
1
0 2
```
## 提示

- $1900\le n\le 2000$；
- $2\le k\le 15$。

| $k$  |  $f(k)$  | $s(k)$ |
| :--: | :------: | :----: |
| $2$  | $7.9870$ |  $22$  |
| $3$  | $3.8085$ |  $14$  |
| $4$  | $2.3960$ |  $11$  |
| $5$  | $1.9610$ |  $9$   |
| $6$  | $1.6065$ |  $7$   |
| $7$  | $1.4515$ |  $6$   |
| $8$  | $1.2540$ |  $5$   |
| $9$  | $1.1980$ |  $5 $   |
| $10$ | $1.0995$ |  $4$   |
| $11$ | $1.0705$ |  $4 $   |
| $12$ | $1.0345$ |  $4$   |
| $13$ | $1.0120$ |  $3$   |
| $14$ | $1.0015$ |  $3 $   |
| $15$ | $0.9940$ |  $3$   |



每个 $2\le k\le 15$ 对应一个总分为 $s(k)$ 的子任务，每个子任务的得分是子任务中每个测试点的得分的最小值。

每个测试点的得分为所在子任务的总分的 $\max\left(0,1-\sqrt{\max\left(0,\frac{m}{n\cdot f(k)}-1\right)}\right)$ 倍。



---

---
title: "[集训队互测 2022] 心跳排列图"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9054
tag: ['动态规划 DP', '贪心', '集训队互测', '2022', 'Special Judge', 'O2优化', '构造', 'Ad-hoc', '分类讨论']
---
# [集训队互测 2022] 心跳排列图
## 题目背景

下发文件见附件。
## 题目描述

注：本题中所有序列下标均从 1 开始。

机器人心脏的跳动，排列成图是什么样的？

你有一个算法竞赛机器人，每分钟心跳 $n$ 次，第 $i$ 次心跳的强度为 $a_i$。这里，$a_1\sim a_n$ 恰为 $1\sim n$ 的一个排列。

设 $A_i$ 为序列 $a$ 删除第 $i$ 个元素后得到的序列，即 $A_i=[a_1,\dots,a_{i-1},a_{i+1},\dots,a_n]$。

对于元素互不相同的序列 $p$，设 $G(p)$ 为一个无向图，有 $|p|$ 个点，编号为 $1\sim |p|$。对于每对正整数 $1\le i\lt j\le |p|$，若 $\forall k\in [i,j]\cap \mathbb{Z}$，都有 $p_k\in [\min(p_i,p_j),\max(p_i,p_j)]$，则 $G(p)$ 中 $i$ 号点和 $j$ 号点有一条边。设 $F(p)$ 为 $G(p)$ 中 $1$ 号点到 $|p|$ 号点的最短路长度，这里一条路径长度定义为其边数。

设 $f(a)=[F(A_1),F(A_2),\dots,F(A_n)]$。

给定长度为 $n$ 的序列 $[b_1,\dots,b_n]$，请你求出任意一个 $1\sim n$ 的排列 $a$，使得 $f(a)=b$。**保证有解。**

在某些子任务中，算法竞赛机器人小 G 会给你一些“提示”：设 $G_0=G(a)$，设 $path_0$ 为 $G_0$ 中某条 $1$ 到 $n$ 的最短路经过的点构成的集合，设 $path_j$ 为 $G(A_j)$ 中某条起始点到结束点的最短路经过的点构成的集合（注意，为了方便，这里给出的 $path_j$ 中点的编号仍然沿用原图中点的编号，参见样例 2）。则小 G 有可能会额外告诉你所有 $path_j$（包括 $path_0$），也有可能只告诉你 $path_0$，也有可能不给你提示，详见输入格式。

保证给出的提示是正确的，也即一定存在一个满足所有提示的排列。

下发文件中有 `checker.cpp`，你可以用它来检查自己的输出是否正确。用法是 `./checker input output output`，`input` 和 `output` 分别为输入文件和你的输出。同时还下发了 `testlib.h`，请将其和 checker 置于同一目录下来编译 checker。
## 输入格式

第一行两个正整数，为子任务编号 $S$ 以及数据组数 $T$。

接下来 $T$ 组数据，每组数据格式为：第一行一个正整数 $n$，第二行 $n$ 个正整数 $b_1,\dots,b_n$。

**特别地，**

1. 若 $S=5$，每组数据还会输入 $n+1$ 行，这 $n+1$ 行里第 $i$ 行是一个长度为 $n$ 的 01 串 $c_i$，$c_{i,j}=[j\in path_{i-1}]$。
2. 若 $S=6$，每组数据还会输入第三行，包含一个长度为 $n$ 的 01 串 $c$，$c_i=[i\in path_0]$。

注意：

1. 即使你的程序不需要用到提示，在 $S=5$ 或 $S=6$ 时你仍然需要读入数组 $c$。
2. 对于一种输入的 $b$，符合条件的 $a$ 可能不唯一，进而 $c$ 可能也不唯一。**不要求**你的输出符合我们给出的 $c$ 的限制，只要符合 $b$ 的限制即视为正确。

同一行输入的不同变量用一个空格隔开。
## 输出格式

对于每组数据输出一行 $n$ 个正整数，为你求出的排列 $a$。
## 样例

### 样例输入 #1
```
9 11
4
2 2 1 1
4
2 2 2 2
4
2 1 1 2
7
5 5 4 4 4 5 5
7
1 3 2 2 2 2 4
7
3 3 2 4 4 5 3
8
2 2 3 5 3 3 3 4
8
5 4 4 4 4 6 6 5
8
4 4 4 2 4 4 2 3
9
4 7 5 5 5 5 3 4 4
9
3 4 4 4 4 4 4 4 6
```
### 样例输出 #1
```
1 2 4 3
2 1 4 3
1 3 2 4
3 1 7 2 6 4 5
3 1 6 4 2 5 7
2 3 1 6 4 7 5
5 6 3 1 7 4 2 8
1 8 2 7 3 5 6 4
6 3 2 7 4 5 1 8
5 8 6 3 7 1 9 2 4
2 9 3 1 8 5 7 6 4
```
### 样例输入 #2
```
5 1
4
2 2 1 1
1011
0111
1011
1001
1010
```
### 样例输出 #2
```
1 2 4 3
```
### 样例输入 #3
```
6 1
4
2 2 1 1
1011
```
### 样例输出 #3
```
1 2 4 3
```
## 提示

**样例 1 解释**

考虑样例中的第一组数据。一组解是 $a=[1,2,4,3]$。$A_1,A_2,A_3,A_4$ 分别为 $[2,4,3],[1,4,3],[1,2,3],[1,2,4]$。$G(A_1),G(A_2),G(A_3),G(A_4)$ 四个图中的边分别为：

- $G(A_1)$：$(1,2),(2,3)$。因此 $F(A_1)=2$。
- $G(A_2)$：$(1,2),(2,3)$。因此 $F(A_2)=2$。
- $G(A_3)$：$(1,2),(1,3),(2,3)$。因此 $F(A_3)=1$。
- $G(A_4)$：$(1,2),(1,3),(2,3)$。因此 $F(A_4)=1$。

所以 $f(a)=[2,2,1,1]$，符合输入。

符合输入的 $a$ 不唯一，比如 $a=[4,3,1,2]$ 也是正确的。

**样例 2 解释**

该样例的排列和第一个样例中第一组数据是相同的，但本样例存在子任务 5 的提示。注意在给出 $path_j$ 时仍然沿用原编号，例如删去 $1$ 后，新的最短路经过的点编号为 $2\to 3\to 4$。

**样例 3 解释**

该样例的排列和第一个样例中第一组数据是相同的，但本样例存在子任务 6 的提示。

**数据范围**

对于所有数据：$1\le T\le 4\times 10^4,4\le n\le 10^5,\sum n\le 5\times 10^5$。

- 子任务 1（$7$ 分）$T\le 250,n\le 7$。
- 子任务 2（$5$ 分）$b_i=1$。
- 子任务 3（$10$ 分）$n\ge 90000$，保证存在一组解满足 $a_1=1,a_n=n$。
- 子任务 4（$7$ 分）$n\ge 90000$，保证存在一组解满足 $a_2=1,a_{n-1}=n$。
- 子任务 5（$15$ 分）$n\le 100,\sum n^3\le 3\times 10^6$，存在所有 $path_j$ 的提示。
- 子任务 6（$15$ 分）$n\le 100,\sum n^3\le 3\times 10^6$，存在 $path_0$ 的提示。
- 子任务 7（$15$ 分）$n=100,T=3$，共 5 个测试点，输入生成方式是随机一个 $a$ 再求出 $f(a)$ 作为输入。
- 子任务 8（$25$ 分）$n\le 100,\sum n^3\le 3\times 10^6$。
- 子任务 9（$1$ 分）无特殊限制。


---

---
title: "[THUPC 2023 初赛] 喵了个喵 II"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9139
tag: ['2023', 'Special Judge', 'O2优化', '2-SAT', '可持久化线段树', '构造', 'THUPC']
---
# [THUPC 2023 初赛] 喵了个喵 II
## 题目背景

本来这题的题面和《喵了个喵》有关的。但是听说有人嫌题面长，就少说点好了。
## 题目描述

给定一个长为 $4n$ 的序列，其中 $1\sim n$ 各出现 $4$ 次。问是否能够将其划分为两个相等的子序列。
## 输入格式

第一行一个正整数 $n$。

第二行 $4n$ 个正整数，表示序列。保证 $1\sim n$ 各出现 $4$ 次。
## 输出格式

如果不能划分为两个相等的子序列，输出一行 `No`。

否则第一行输出 `Yes`。第二行输出一个长为 $4n$ 的 `01` 串。其中第 $i$ 位表示原序列的第 $i$ 个数被划分到第几个子序列。你需要保证你划分出来的两个子序列完全相等。
## 样例

### 样例输入 #1
```
2
1 1 2 1 2 2 1 2
```
### 样例输出 #1
```
Yes
10000111

```
## 提示

#### 样例解释 1

两个子序列均为 $(1,2,1,2)$。

#### 子任务

保证 $1\le n \le 5\times10^4$。

保证序列中 $1\sim n$ 各出现 $4$ 次。

#### 评分方式

你的输出的第一行需要与标准答案一致。若为 `Yes`，输出任意一种合法的划分均算正确。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。

By E.Space：由于考场上数据太弱，我于 3.12 和 3.19 两度加强了数据。


---

---
title: "[POI 2020/2021 R3] Surowa zima"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9404
tag: ['模拟', '贪心', '2020', '平衡树', 'POI（波兰）', '构造', '分类讨论']
---
# [POI 2020/2021 R3] Surowa zima
## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Surowa zima](https://szkopul.edu.pl/problemset/problem/QCCQf92wAoWAOoJ3tHoypvp3/statement/)。

d1t3。
## 题目描述

有一条长 $l$ 米的道路（数轴）。路上有 $n$ 个充电站。每天整条路上（坐标 $[0,l]$）都会落满雪。

有一台机器能扫雪。充一次电可以扫至多 $k$ 米的雪。扫雪是和移动同时进行的，详见样例解释。机器一秒能移动一米，充电不消耗时间。

简单来说，**移动不扫雪不消耗电，需要一秒；移动并扫雪消耗最大电量的 $\bold{\frac1k}$，需要一秒；扫雪必须移动。**

给出每天机器的初始位置，机器初始没电，问每天清除所有雪的最少时间。终点任意。

带修，即充电站可能损坏或修好（第一天之前都是好的），但保证每天都至少有一个好的充电站（所以不会无解）。
## 输入格式

第一行四个整数 $n,l,k,d$。

第二行 $n$ 个整数 $x_1,x_2,\dots,x_n$，表示充电站的位置，保证 $0\leq x_1<x_2<\dots<x_n\leq l$。

接下来 $3d$ 行，描述 $d$ 天的事件：

- 第一行三个整数 $z,u,p$，分别表示昨晚修好的充电站数量，损坏的数量，和机器的初始位置。
- 第二行 $z$ 个整数，表示被修好的充电站编号。
- 第三行 $u$ 个整数，表示损坏的充电站编号。
## 输出格式

$d$ 行，每行一个整数，表示每天的答案。
## 样例

### 样例输入 #1
```
3 5 2 1
2 3 5
0 1 3

2

```
### 样例输出 #1
```
9

```
### 样例输入 #2
```
5 12 1 5
1 3 6 9 11
0 1 1

1
1 1 3
1
2
1 1 6
2
3
1 1 9
3
4
1 1 11
4
5

```
### 样例输出 #2
```
33
33
36
33
33

```
### 样例输入 #3
```
11 100 1 26
0 10 20 30 40 50 60 70 80 90 100
0 5 0

2 4 6 8 10
5 6 4
2 4 6 8 10
1 3 5 7 9 11
6 5 8
1 3 5 7 9 11
2 4 6 8 10
5 6 12
2 4 6 8 10
1 3 5 7 9 11
6 5 16
1 3 5 7 9 11
2 4 6 8 10
5 6 20
2 4 6 8 10
1 3 5 7 9 11
6 5 24
1 3 5 7 9 11
2 4 6 8 10
5 6 28
2 4 6 8 10
1 3 5 7 9 11
6 5 32
1 3 5 7 9 11
2 4 6 8 10
5 6 36
2 4 6 8 10
1 3 5 7 9 11
6 5 40
1 3 5 7 9 11
2 4 6 8 10
5 6 44
2 4 6 8 10
1 3 5 7 9 11
6 5 48
1 3 5 7 9 11
2 4 6 8 10
5 6 52
2 4 6 8 10
1 3 5 7 9 11
6 5 56
1 3 5 7 9 11
2 4 6 8 10
5 6 60
2 4 6 8 10
1 3 5 7 9 11
6 5 64
1 3 5 7 9 11
2 4 6 8 10
5 6 68
2 4 6 8 10
1 3 5 7 9 11
6 5 72
1 3 5 7 9 11
2 4 6 8 10
5 6 76
2 4 6 8 10
1 3 5 7 9 11
6 5 80
1 3 5 7 9 11
2 4 6 8 10
5 6 84
2 4 6 8 10
1 3 5 7 9 11
6 5 88
1 3 5 7 9 11
2 4 6 8 10
5 6 92
2 4 6 8 10
1 3 5 7 9 11
6 5 96
1 3 5 7 9 11
2 4 6 8 10
5 6 100
2 4 6 8 10
1 3 5 7 9 11

```
### 样例输出 #3
```
1090
1096
1098
1092
1094
1100
1094
1092
1098
1096
1090
1096
1098
1092
1094
1100
1094
1092
1098
1096
1090
1096
1098
1092
1094
1100

```
### 样例输入 #4
```
见附件
```
### 样例输出 #4
```
见附件
```
### 样例输入 #5
```
见附件
```
### 样例输出 #5
```
1000000000000000000
2001007996000

```
## 提示

样例解释：$3\rightarrow2_{充电}\Rightarrow0\rightarrow2_{充电}\Rightarrow4\rightarrow5_{充电}\Rightarrow4$。$\rightarrow$ 表示移动，$\Rightarrow$ 表示移动并扫雪。

对于所有数据，$1\leq n\leq 250000$，$1\leq l\leq 10^9$，$1\leq k\leq l$，$1\leq d\leq 250000$，$\sum z,\sum u\leq 500000$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $l\leq 12$，$d\leq 50$ | 10 |
| 2 | $l\leq 500$，$d\leq 50$，$k=1$ | 12 |
| 3 | $l\leq 5000000$，$d\leq 20$ | 8 |
| 4 | $z=u=0$ | 8 |
| 5 | $z,u\leq 100$，$k\leq 50$ | 20 |
| 6 | $k=1$ | 18 |
| 7 |  | 24 |



---

---
title: "「SFCOI-3」进行一个魔的除 I"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9495
tag: ['贪心', '2023', '洛谷原创', 'O2优化', '构造', 'Ad-hoc']
---
# 「SFCOI-3」进行一个魔的除 I
## 题目背景

终于，勇士打败了魔王，他把走投无路的魔王困在了一个房间里。

魔王拥有在黑暗中随意穿行的能力，所以勇士只有把房间里所有的灯全部打开，才能找到魔王，最终彻底消灭他。
## 题目描述

房间中共有 $n$ 盏灯，初始状态可以用 $a_1\dots a_n$ 表示，其中 $\tt 0$ 表示这盏灯初始是关闭的，$\tt 1$ 表示这盏灯初始是打开的。

从第一天早晨开始，魔王与勇士轮流行动：

- 每天早晨，魔王可以选择 **连续的** 两盏灯，将它们的状态全部设定为 $\tt 0$；
- 每天晚上，勇士可以选择 **任意的** 至多三盏灯，将它们的状态全部设定为 $\tt 1$。

每次行动时选择的灯在设定前的状态任意。

假设双方均采用最优策略，不会进行任何不利于自己的行动。勇士想知道，**最少** 需要多少天（也即，他最少需要多少次操作）才能将所有灯状态设定为 $\tt 1$——这样，他才能抓到可恶的魔王，迎娶美丽的公主。
## 输入格式

第一行一个整数 $T$，表示数据组数。

对于每组数据：

+ 第一行一个整数 $n$，表示灯的总数。
+ 第二行共 $n$ 个数，依次表示 $a_1\dots a_n$。
## 输出格式

对于每组数据，一行一个整数，代表勇士抓到魔王所需要的最少天数。

特别地，如果勇士不需要任何操作，输出 $0$ 即可。
## 样例

### 样例输入 #1
```
4
5
1 0 1 0 1
5
1 0 0 1 1
9
0 0 0 0 0 0 0 0 0
13
0 1 0 0 1 0 1 0 0 0 0 0 0

```
### 样例输出 #1
```
1
2
5
8
```
## 提示

### 样例解释 1

+ 第一天早晨，魔王关闭第 $1{,}2$ 两盏灯；
+ 第一天晚上，勇士打开 $1{,}2{,}4$ 三盏灯。

### 样例解释 2

+ 第一天早晨，魔王关闭第 $4{,}5$ 两盏灯；
+ 第一天晚上，勇士打开 $2{,}3{,}4$ 三盏灯。
+ 第二天早晨，魔王关闭第 $1{,}2$ 两盏灯；
+ 第二天晚上，勇士打开 $1{,}2{,}5$ 三盏灯。

### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 0（10 points）：$n \leq 10$，$T \leq 2046$。
- Subtask 1（30 points）：$ n \leq 2000$。
- Subtask 2（10 points）：初始所有灯都是关闭的。 
- Subtask 3（20 points）：数据随机生成。
- Subtask 4（30 points）：无特殊限制。

对于所有数据，$1 \leq T \leq 10^6$，$1 \leq n \leq 10^6$，$1 \leq \sum n \leq 3 \times 10^6$。


---

---
title: "[EC Final 2021] Check Pattern is Bad"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9878
tag: ['2021', 'Special Judge', 'O2优化', '构造', 'ICPC']
---
# [EC Final 2021] Check Pattern is Bad
## 题目描述

Prof. Pang is given an $n\times m$ board. Some cells are colored black, some cells are colored white, and others are uncolored.

Prof. Pang doesn't like $\textbf{check patterns}$, so he wants to color all uncolored cells such that there is no check pattern on the board.

$4$ cells forming a $2\times 2$ square are said to have the check pattern if they are colored in one of the following ways:

```plain
BW
WB
```

```plain
WB
BW
```

Here `W` ("wakuda" in Chewa language) means the cell is colored black and `B` ("biancu" in Corsican language) means the cell is colored white.
## 输入格式

The first line contains a single integer $T$ $(1\leq T \leq 10^4)$ denoting the number of test cases.

The first line of each test case contains two integers $n$ and $m$ ($1\le n, m\le 100$) denoting the dimensions of the board.

Each of the next $n$ lines contains $m$ characters. The $j$-th character of the $i$-th line represents the status of the cell on the $i$-th row and $j$-th column of the board. The character is `W` if the cell is colored black, `B` if the cell is colored white, and `?` if the cell is uncolored. 

It is guaranteed that the sum of $nm$ over all test cases is no more than $10^6$.
## 输出格式

For each test case, output a line containing $\texttt{NO}$ if you cannot color all the uncolored cells such that there is no check pattern on the board.

Otherwise, output a line containing $\texttt{YES}$. In the next $n$ lines, output the colored board in the same format as the input. The output board should satisfy the following conditions.

- It does not have any check pattern.
- It consists of only $\texttt{B}$ and $\texttt{W}$.
- If a cell is already colored in the input, its color cannot be changed in the output.

If there are multiple solutions, output any of them.
## 样例

### 样例输入 #1
```
3
2 2
??
??
3 3
BW?
W?B
?BW
3 3
BW?
W?W
?W?
```
### 样例输出 #1
```
YES
BW
WW
NO
YES
BWB
WWW
BWB
```
## 题目翻译

$n \times m$ 的棋盘，知道一些位置是黑色的，一些位置是白色的，一些位置不知道是什么颜色。

请你构造一种方案让棋盘的每个位置被染成黑色或白色（已知的位置不能换颜色），使得棋盘上不存在子矩阵：

```
BW
WB
```

以及
```
WB
BW
```


多组询问。


---

---
title: "[POI 2023/2024 R1] Satelity"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9924
tag: ['POI（波兰）', '2023', 'Special Judge', '构造']
---
# [POI 2023/2024 R1] Satelity
## 题目背景

译自 [XXXI Olimpiada Informatyczna - I etap](https://sio2.mimuw.edu.pl/c/oi31-1/dashboard/) [Satelity](https://sio2.mimuw.edu.pl/c/oi31-1/p/sat/)。
## 题目描述

有 $2n$ 个卫星，$1\sim n$ 属于 A 公司，$n+1\sim 2n$ 属于 B 公司。

两个卫星**应当**能够通信**当且仅当**它们属于同一个公司或者有额外要求。

你需要给每个卫星分配一个等长的**独一无二**的识别码，识别码应当只包含字母 `ABC`，两个卫星**实际**能够通信**当且仅当**识别码有至少一位相同。要求你的识别码方案满足要求。输出你的方案。
## 输入格式

本题多测，读入直到文件结束。

对于每组数据，第一行三个正整数 $n,p,M$，其中 $M$ 意为你的识别码长度不得超过 $M$。

接下来 $p$ 行，每行两个正整数，表示这两个卫星有额外要求应当能够通信。
## 输出格式

对于每组数据，第一行一个正整数 $m(1\leq m\leq M)$，表示你的方案的识别码长度。

接下来 $2n$ 行，每行一个长度为 $m$ 的只含 `ABC` 的字符串，识别码。
## 样例

### 样例输入 #1
```
3 4 4
1 4
2 6
3 4
3 6

```
### 样例输出 #1
```
3
ABA
AAC
BAA
BBB
CCB
BCC

```
### 样例输入 #2
```
见附件
```
### 样例输出 #2
```
见附件
```
### 样例输入 #3
```
见附件
```
### 样例输出 #3
```
见附件
```
### 样例输入 #4
```
2 1 4
1 4

```
### 样例输出 #4
```
2
AB
AC
BA
BB

```
## 提示

单个输入文件不超过 40MB，请使用较快的输入输出方式。

对于所有测试点，$1\leq\sum n\leq 2\times 10^6$，$1\leq\sum n^2\leq10^7$。

对于所有数据，$2\leq n\leq1000$，$1\leq p\leq n^2$。

| 子任务编号 | 附加限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $n\leq100$，$M=n^2+2n$ | 7 |
| 2 | $M=3n$ | 11 |
| 3 | $M=n+2\lceil\log_2n\rceil$ | 23 |
| 4 | $M=n+2$ | 41 |
| 5 | $M=n+1$ | 18 |


---

