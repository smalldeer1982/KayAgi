---
title: "BZOJ1278 向量 vector"
layout: "post"
diff: 省选/NOI-
pid: P10671
tag: ['计算几何', 'O2优化', '随机化']
---
# BZOJ1278 向量 vector
## 题目描述

一个二维向量 $(x,y)$ 的权定义为 $x^2+y^2$。已知一个由 $n$ 个二维向量组成的集合，求该集合的一个子集，使该子集中的向量和的权尽可能大。
## 输入格式

第 $1$ 行一个正整数 $n$，表示 $n$ 个向量。

下面 $n$ 行，每行 $2$ 个实数，表示 $n$ 个向量 $(x_i,y_i)$。
## 输出格式

输出 $1$ 个实数，即向量和最大的权，精确到小数点后 $3$ 位。
## 样例

### 样例输入 #1
```
3
1 1
1 0
0 -1
```
### 样例输出 #1
```
5.000
```
## 提示

数据保证，$1\leq n\leq 100000$。


---

---
title: "[COTS 2023] 三角形 Trokuti"
layout: "post"
diff: 省选/NOI-
pid: P10831
tag: ['2023', '交互题', 'Special Judge', 'O2优化', '概率论', '随机化', 'COCI（克罗地亚）']
---
# [COTS 2023] 三角形 Trokuti
## 题目背景

译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D1T3。$\texttt{1s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）
## 题目描述

有一个隐藏的简单无向图 $G$，其中恰有 $N=100$ 个节点。试通过以下询问重建 $G$：

> **询问** 给定两两不同的节点 $u,v,w$，回答这三个节点的导出子图（induced subgraph）的边数。注意到答案只会是 $0,1,2,3$。

【实现细节】

你的程序通过标准输入输出与交互库交互。

- $\texttt{? u v w}$：发起一次询问，回答 $u,v,w$ 的导出子图的边数（从标准输入读取），注意到答案只会是 $0,1,2,3$。

    你需要保证 $1\le u,v,w\le 100$，$u,v,w$ 两两不同。最多询问 $161\, 700$ 次。
- $\texttt{!}$：回答答案。在输出 $\texttt{!}$ 后换行，接下来输出 $N$ 行，每行一个长度为 $N$ 的 $\texttt{01}$ 字符串。

    第 $i$ 行第 $j$ 个字符如果是 $\texttt{1}$，代表 $(i,j)$ 间有边；否则代表 $(i,j)$ 间无边。

每次输出后，你需要刷新缓冲区。如：C++ 中的 `cout.flush()`。

## 输入格式

见【实现细节】。
## 输出格式

见【实现细节】。
## 样例

### 样例输入 #1
```

0

2

2
```
### 样例输出 #1
```
? 1 2 3

? 1 2 4

? 1 3 4

!
0001
0001
0001
1110
```
## 提示


#### 评分方式

记 $Q$ 为你程序询问的最多次数。

若 $Q\gt 161\, 700$，得 $0$ 分。

否则，你的得分将由下表确定：

| $Q$ | 得分 |
|:-----:|:------:|
| $9\, 900\le Q\le 161\, 700$  | $\displaystyle 10+10\cdot \frac{161\, 700-Q}{161\, 700-9\, 900}$  | 
| $4\, 950 \le Q\le 9\, 900$  | $\displaystyle 20+10\cdot \frac{9\, 900-Q}{9\,900-4\,500}$  |
| $3\, 400\le Q\le 4\, 950$  | $\displaystyle 30+70\cdot \frac{4\,950-Q}{4\,950-3\,400}$  |
| $Q\le 3\, 400$  | $100$  |




---

---
title: "[COCI 2024/2025 #2] 三角 / Trokuti"
layout: "post"
diff: 省选/NOI-
pid: P11433
tag: ['2024', '网络流', 'Special Judge', '随机化', 'COCI（克罗地亚）']
---
# [COCI 2024/2025 #2] 三角 / Trokuti
## 题目背景

译自 [COCI 2024/2025 #2](https://hsin.hr/coci/) T5。$\texttt{4s,0.5G}$。满分为 $120$。

## 题目描述


给定一张 $6n$ 个节点 $m$ 条边的无向图。保证这张图可以被**划分**成 $2n$ 个 $K_3$（大小为 $3$ 的完全图）。

求出这张图中的 $n$ 个 $K_3$，不能有重复顶点。
## 输入格式


**本题单个测试点内有多组测试数据。**

第一行，一个正整数 $T$，表示测试数据组数。

接下来描述 $T$ 组数据：

第一行，两个整数 $n,m$。

接下来 $m$ 行，每行两个正整数 $u,v$，表示图中的一条无向边。
## 输出格式

每组数据输出 $n$ 行，每行三个整数，表示 $K_3$ 的三个顶点。

## 样例

### 样例输入 #1
```
1
1 6
1 2
2 3
1 3
4 5
4 6
5 6
```
### 样例输出 #1
```
1 2 3
```
### 样例输入 #2
```
1
3 26
4 7
4 9
7 9
4 5
4 8
5 8
4 12
4 18
12 18
3 7
3 9
15 5
15 8
6 13
6 1
13 1
6 14
6 17
14 17
6 2
6 10
2 10
16 13
16 1
11 14
11 17
```
### 样例输出 #2
```
1 6 13
3 7 9
4 5 8
```
## 提示



对于 $100\%$ 的数据，保证：

- $1\le T\le 100$；
- $1\le n,\sum n\le 300$；  
- $0\le m\le 10^6$；
- $1\le u,v\le 6n$。


| 子任务编号 | $n,\sum n$ |  特殊性质 | 得分 |  
| :--: | :--: | :--: |:--: | 
| $ 1 $    | $\le 300$ | A |   $ 13 $   |  
| $ 2 $    | $=3$ | B |  $ 18 $   |  
| $ 3 $    | $=6$ | B |  $ 18 $   |  
| $ 4 $    | $\le 300$ |   |  $ 71 $   |  

- 特殊性质 A：$m=6n$。
- 特殊性质 B：$T=1$。


---

---
title: "[科大国创杯初中组 2023] 石子"
layout: "post"
diff: 省选/NOI-
pid: P11953
tag: ['2023', '安徽', '栈', '随机化', '科大国创杯']
---
# [科大国创杯初中组 2023] 石子
## 题目描述

小可可面前有 $n$ 堆石子，第 $i$ 堆石子有 $a_i$ 个石子。小可可想要在开始选择一堆石子，然后从它开始，每次合并这堆石子左边的那堆石子或者右边的那堆石子。合并两堆石子个数为 $x, y$ 的石子堆需要花 $x + y$ 的力气，并且会合并成一堆 $x + y$ 个石子的石子堆。

小可可想花费最小的力气从最初选择的那堆石子开始，将所有石子都合并完。小可可想知道，如果他选择编号在 $[l, r]$ 里面的每一堆石子作为最初的石子，那么他将 $n$ 堆石子合并成一堆花的最小力气是多少。

小可可不想太为难你，所以他保证所有的 $a_i$ 是随机的。
## 输入格式

第一行输入一行三个整数 $n, l, r$，石子堆数和最开始选择的那堆石子的编号区间。

第二行输入 $n$ 个整数 $a_1, a_2, \cdots, a_n$，表示每堆石子的石子个数。
## 输出格式

输出一行 $r - l + 1$ 个整数，第 $i$ 个整数表示小可可选择编号为 $l - 1 + i$ 的石子堆作为最开始的那堆石子时，将所有石子都合并完花的最少力气。
## 样例

### 样例输入 #1
```
4 1 4
5 1 3 1
```
### 样例输出 #1
```
25 19 19 19
```
## 提示

### 样例 1 解释

对于第 $1$ 堆石子作为初始的石子堆，最优（也是唯一）的合并策略是先合并第 $2$ 堆，再合并第 $3$ 堆，随后合并第 $4$ 堆，花费力气为 $25$；

对于第 $2$ 堆石子作为初始的石子堆，最优的合并策略是先合并第 $3$ 堆，再合并第 $4$ 堆，随后合并第 $1$ 堆，花费力气为 $19$；

对于第 $3$ 堆石子作为初始的石子堆，最优的合并策略是先合并第 $2$ 堆，再合并第 $4$ 堆，随后合并第 $1$ 堆，花费力气为 $19$；

对于第 $4$ 堆石子作为初始的石子堆，最优（也是唯一）的合并策略是先合并第 $3$ 堆，再合并第 $2$ 堆，随后合并第 $1$ 堆，花费力气为 $19$。

### 数据规模与约定

对于 $20 \%$ 的数据，满足 $n \leq 10$；

对于 $40 \%$ 的数据，满足 $n \leq 300$；

对于 $60 \%$ 的数据，满足 $n \leq 5000$；

对于另外 $20 \%$ 的数据，满足 $n \leq 10^5, r - l + 1 \leq 50$；

对于 $100 \%$ 的数据，有 $1 \leq l \leq r \leq n \leq 10^5, 1 \leq a_i \leq 10^8$。保证 $a_i$ 随机。随机方式为：先选择一个所有 $a_i$ 的上界 $v$，对于每个 $a_i$，它在 $[1, v]$ 中的所有整数中等概率随机选取一个。


---

---
title: "[GCPC 2023] Highway Combinatorics"
layout: "post"
diff: 省选/NOI-
pid: P13673
tag: ['2023', '数论', 'Special Judge', 'Fibonacci 数列', '随机化', 'ICPC', '折半搜索 meet in the middle']
---
# [GCPC 2023] Highway Combinatorics
## 题目描述

You are the new minister of transport in Berland.
Recently, you allowed free parking on a two lane road segment of $200$ metres length.
Since then, that road segment has constantly been jammed by parked cars due to some
genius drivers who had the idea to park their cars across both lanes...

![](https://cdn.luogu.com.cn/upload/image_hosting/x81bkouf.png)

:::align{center}
Jam caused by parking bus, [Nevermind2](https://commons.wikimedia.org/wiki/File:Moscow_traffic_congestion.JPG)
:::


However, this is not your concern.
You are more interested in parking some of your own cars on the road segment while it is empty.
More specifically, you want to park some of your cars in such a way that the number of different ways to fill the remaining empty space with cars is congruent to your lucky number $n$ modulo $10^9+7$.

![](https://cdn.luogu.com.cn/upload/image_hosting/ntad7154.png)

:::align{center}
Figure H.1: Visualization of Sample Output 1.
:::

Each car has a size of $1\times2$ metres, each of the two lanes is $1$ metre wide and $200$ metres long. You own more than $200$ cars which you could park on the road segment.

## 输入格式

The input consists of:
- One line with one integer $n$ ($0\leq n<10^9+7$), the desired number of possible ways to fill the road modulo $10^9+7$.

It can be proven that at least one valid solution exists for each possible value of $n$.

## 输出格式

Output the state of the two lanes in two lines.
Print "$\texttt{\#}$" for an occupied spot and "$\texttt{.}$" for an empty spot. Note that the two lines should have the same length of at least $1$ metre and at most $200$ metres, and the occupied spots must correspond to some parked cars. If your solution uses a road segment shorter than $200$ metres, the remaining part of the road segment is assumed to be blocked by parked cars. 
## 样例

### 样例输入 #1
```
10
```
### 样例输出 #1
```
##..#.......
....#.##....
```
### 样例输入 #2
```
27
```
### 样例输出 #2
```
...##........
........##...
```


---

---
title: "[AHOI2012] 信号塔"
layout: "post"
diff: 省选/NOI-
pid: P2533
tag: ['计算几何', '2012', '各省省选', '安徽', '随机化']
---
# [AHOI2012] 信号塔
## 题目描述

在野外训练中，为了确保每位参加集训的成员安全，实时的掌握和收集周边环境和队员信息非常重要，集训队采用的方式是在训练所在地散布 $N$ 个小型传感器来收集并传递信息，这些传感器只与设在集训地中的信号塔进行通信，信号塔接收信号的覆盖范围是圆形，可以接收到所有分布在该集训区域内所有 $N$ 个小型传感器（包括在该圆形的边上）发出的信号。信号塔的功率与信号塔接收范围半径的大小成正比，因为是野外训练，只能使用事先储备好的蓄电设备，因此在可以收集所有传感器信息的基础上，还应使得信号塔的功率最小。小龙帮助教官确定了一种信号塔设置的方案，既可以收集到所有 $N$ 个传感器的信号，又可以保证这个信号塔的功率是最小的。同学们，你们知道，这个信号塔的信号收集半径有多大，它应该设置在何处吗?
## 输入格式

共 $N+1$ 行，第一行为正整数 $N$，表示队员个数。接下来 $N$ 行，每行两个实数用空格分开，分别是第 $i$ 个队员的坐标 $x_i$ 和 $y_i$ （$x_i,y_i$ 不超过双精度范围）。
## 输出格式

一行，共三个实数（中间用空格隔开），分别是信号塔的坐标，和信号塔覆盖的半径。
## 样例

### 样例输入 #1
```
5
1.200 1.200
2.400 2.400
3.800 4.500
2.500 3.100
3.900 1.300
```
### 样例输出 #1
```
2.50 2.85 2.10
```
## 提示

队员是否在边界上的判断应该符合他到圆心的距离与信号塔接受半径的差的绝对值小于 $10^{-6}$，最终结果保留 $2$ 位小数。

对于 $30\%$ 的数据，满足 $1\le N \le 10^4$  
对于 $70\%$ 的数据，满足 $1\le N \le 2\times10^4$  
对于 $100\%$ 的数据，满足 $1\le N \le 10^6$

本题存在 hack 数据，计 0 分。


---

---
title: "[HNOI2011] 任务调度"
layout: "post"
diff: 省选/NOI-
pid: P3212
tag: ['搜索', '2011', '各省省选', '湖南', '随机化']
---
# [HNOI2011] 任务调度
## 题目描述


有 $n$ 个任务和两台机器 A 与 B。每个任务都需要既在机器 A 上执行，又在机器 B 上执行，

第 $i$ 个任务需要在机器 A 上执行时间 $a_i$，且需要在机器 B 上执行时间 $b_i$。最终的目标是所有任务在 A 和 B 上都执行完，且希望执行完所有任务的总时间尽量少。当然问题没有这么简单，有些任务对于先在机器 A 上执行还是先在机器 B 上执行有一定的限制。据此可将所有任务分为三类：

1. 任务必须先在机器 A 上执行完然后再在机器 B 上执行。
2. 任务必须先在机器 B 上执行完然后再在机器 A 上执行。
3. 任务没有限制，既可先在机器 A 上执行，也可先在机器 B 上执行。

现在给定每个任务的类别和需要在机器 A 和机器 B 上分别执行的时间，问使所有任务都能按规定完成所需要的最少总时间是多少。
## 输入格式

输入的第一行只有一个正整数 $n$，表示任务的个数。

接下来的 $n$ 行，每行是用空格隔开的三个正整数 $t_i,a_i,b_i$，分别表示第 $i$ 个任务的类别（类别 $1$，$2$，$3$ 的定义如上）以及第 $i$ 个任务需要在机器 A 和机器 B 上分别执行的时间。
## 输出格式

输出仅包含一个正整数，表示所有任务都执行完所需要的最少总时间。
## 样例

### 样例输入 #1
```
3
3 5 7
1 6 1 
2 2 6

```
### 样例输出 #1
```
14
```
## 提示

#### 样例 1 解释

一种最优任务调度方案为：

机器 A 上执行的各任务依次安排如下：

任务 $1\ (0\to 5)$，任务 $2\ (5\to 11)$, 任务 $3\ (11\to 13)$；

机器 B 上执行的各任务依次安排如下：

任务 $3\ (0 \to 6)$, 任务 $1\ (6 \to 13)$, 任务 $2\ (13 \to14)$，

这样，所有任务都执行完所需要的总时间为 $14$。

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1\le n\le 20$，$1\le a_i\le 10^3$，$1\le t_i\le 3$，并保证 $t_i=3$ 的 $i$ 不超过 $10$ 个。


---

---
title: "[BJ United Round #3] 观察星象"
layout: "post"
diff: 省选/NOI-
pid: P5549
tag: ['计算几何', '二分', '北京', 'Special Judge', '随机化']
---
# [BJ United Round #3] 观察星象
## 题目描述

EI 在用望远镜观察星星，星空中共有  $n$ 个星星，每个星星观察起来有一个二维直角坐标 $(x,y)$。  

他的望远镜如果定位在 $(x_0,y_0)$ 处，可以看到所有 $(x_0-x)^2 + (y_0-y)^2 \le r^2$ 的星星。  

望远镜的大小 $r$ 是可以调整的，EI 想知道如果他要至少看到 $m$ 个星星，至少需要把 $r$ 设置到多大？
## 输入格式

第一行两个正整数 $n,m$，表示星星的数量和要求看到的星星数量。  
接下来 $n$ 行，每行两个整数 $x,y$，表示一个星星的坐标。  
保证星星坐标两两不同。
## 输出格式

输出一行一个正实数，表示望远镜的最小半径。  
令你的答案为 $a$，标准答案为 $b$，若 $\frac{|a-b|}{\max(1,b)} \le 10^{-6}$  
( 即绝对误差或者相对误差不超过 $10^{-6}$ ) 即为正确。
## 样例

### 样例输入 #1
```
4 3
0 0
1 1
2 3
3 3
```
### 样例输出 #1
```
1.41421356
```
## 提示

| 子任务编号 | $n$ | $m$ | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leq 50$ | $\leq n$ | $10$ |
| $2$ | $\leq 200$ | $\leq n$ | $15$ |
| $3$ | $\leq 700$ | $\leq n$ | $15$ |
| $4$ | $\leq 2000$ | $= n$ | $20$ |
| $5$ | $\leq 2000$ | $\leq n$ | $40$ |


对于 $100\%$ 的数据，保证：  
$2 \le m \le n  \le 2000$  
$|x|,|y| \le 10^4$

By：EntropyIncreaser


---

---
title: "[ICPC 2014 WF] Sensor Network"
layout: "post"
diff: 省选/NOI-
pid: P6900
tag: ['2014', 'Special Judge', '随机化', 'ICPC']
---
# [ICPC 2014 WF] Sensor Network
## 题目描述


A wireless sensor network consists of autonomous sensors scattered in an environment where they monitor conditions such as temperature, sound, and pressure. 

Samantha is a researcher working on the Amazon Carbon-dioxide Measurement (ACM) project. In this project, a wireless sensor network in the Amazon rainforest gathers environmental information. The Amazon rainforest stores an amount of carbon equivalent to a decade of global fossil fuel emissions, and it plays a crucial role in the world’s oxygen-transfer processes. Because of the huge size of this forest, changes in the forest affect not only the local environment but also global climate by altering wind and ocean current patterns. The goal of the ACM project is to help scientists better understand earth’s complex ecosystems and the impact of human activities.

Samantha has an important hypothesis and to test her hypothesis, she needs to find a subset of sensors in which each pair of sensors can communicate directly with each other. A sensor can communicate directly with any other sensor having distance at most $d$ from it. In order for her experiments to be as accurate as possible, Samantha wants to choose as many sensors as possible.

As one does not simply walk into the Amazon, Samantha cannot add new sensors or move those that are currently in place. So given the current locations of the sensors, she needs your help to find the largest subset satisfying her criteria. For simplicity, represent the location of each sensor as a point in a two-dimensional plane with the distance between two points being the usual Euclidean distance.
## 输入格式

The input consists of a single test case. The first line contains two integers $n$ and $d$ ($1 \le n \le 100$ and $1 \le d \le 10\, 000$), where $n$ is the number of sensors available and $d$ is the maximum distance between sensors that can communicate directly. Sensors are numbered $1$ to $n$. Each of the next $n$ lines contains two integers $x$ and $y$ ($-10\, 000\le x, y \le 10\, 000$) indicating the sensor coordinates, starting with the first sensor.
## 输出格式

Display a maximum subset of sensors in which each pair of sensors can communicate directly. The first line of output should be the size of the subset. The second line of output should be the (one-based) indices of the sensors in the subset. If there are multiple such subsets, any one of them will be accepted.
## 样例

### 样例输入 #1
```
4 1
0 0
0 1
1 0
1 1

```
### 样例输出 #1
```
2
1 2

```
### 样例输入 #2
```
5 20
0 0
0 2
100 100
100 110
100 120

```
### 样例输出 #2
```
3
4 3 5

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

无线传感器网络由分散在环境中的自主传感器组成，它们监控温度、声音和压力等条件。

萨曼莎是亚马逊二氧化碳测量 (Amazon Carbon-dioxide Measurement, ACM) 项目的研究员。在这个项目中，亚马逊雨林的无线传感器网络收集环境信息。亚马逊雨林储存了相当于十年全球化石燃料排放量的碳，它在世界的氧气转移过程中扮演着至关重要的角色。由于这片森林面积巨大，森林的变化不仅会影响当地环境，还会通过改变风和洋流模式来影响全球气候。ACM 项目的目标是帮助科学家更好地了解地球复杂的生态系统和人类活动的影响。

萨曼莎有一个重要的猜想，为了验证她的猜想，她需要找到传感器的一个子集，在这些传感器中，每对传感器都可以直接相互通信。传感器可以与距离它不超过 $d$ 的任何其他传感器直接通信。为了让她的实验尽可能准确，萨曼莎希望选择尽可能多的传感器。

因为人们不能简单地走进亚马逊，萨曼莎不能添加新的传感器，也不能移动那些目前设置好的传感器。因此，给出传感器目前的位置，她需要你的帮助来找到满足她标准的最大子集。为简单起见，每个传感器的位置被表示为二维平面中的一个点，两点之间的距离为通常的欧几里德距离。


#### 输入

第一行两个整数 $n$ 和 $d$ ($1\le n\le 100$, $1\le d\le 10\,000$)，其中 $n$ 表示传感器的个数，$d$ 表示传感器能直接通信的最大距离。传感器从 $1$ 到 $n$ 编号。接下来的 $n$ 行，每行两个整数 $x$, $y$ ($-10\,000\le x,y\le 10\,000$)，表示每个传感器的坐标，从第一个传感器开始。

#### 输出

输出满足要求的一个最大子集。第一行输出子集的大小。第二行输出子集中传感器的编号 (从 $1$ 开始编号)。如果有多个满足要求的最大子集，输出任意一个均可。


---

---
title: "[JOISC 2020] 伝説の団子職人"
layout: "post"
diff: 省选/NOI-
pid: P7218
tag: ['2020', '提交答案', 'Special Judge', '模拟退火', '随机化', 'JOI（日本）']
---
# [JOISC 2020] 伝説の団子職人
## 题目背景

您是做团子带师，您太强了。
## 题目描述

您面前有一个 $R \times C$ 的网格，每一个格子里有一个团子，您可以横向，竖向，斜向地将三个连续的团子按顺序串起来，按顺序指可以串上中下，下中上之类的，但是不能串中下上，上下中之类的。

如果一串团子的颜色为绿，白，粉或者粉，白，绿，那么称这串团子叫 AK IOI 串。

求串最多 AK IOI 串的方法（我坚信做了几个 AK IOI 串就会 AK 几次 IOI）。
## 输入格式

第一行两个整数 $R,C$ 代表网格大小。    
接下来 $R$ 行每行 $C$ 个字符代表网格：

- `P` 代表粉色团子
- `W` 代表白色团子
- `G` 代表绿色团子
## 输出格式

$R$ 行每行 $C$ 个字符代表串好的网格：

- 可以为 `-`，`|`，`/`，`\`，代表一个团子串
- 如果不是以上四种线，那么原样输出

输出文件应为 `01.ans` ~ `06.ans`。
## 样例

### 样例输入 #1
```
3 4
PWGP
WGPW
GWPG
```
### 样例输出 #1
```
P-GP
WGP|
G-PG
```
### 样例输入 #2
```
3 4
PWWP
WWWW
PGGP
```
### 样例输出 #2
```
PWWP
W\/W
PGGP
```
## 提示

#### 样例 1 解释

您做了 $3$ 个 AK IOI 串。

#### 样例 2 解释

您做了 $2$ 个 AK IOI 串。

#### 数据规模与约定

**本题为提交答案题。**

**本题使用 Special Judge。**

一共有 $6$ 组数据，保证 $3 \le R,C \le 500$，输入文件可在附加文件中得到，具体数据表格如下：

|数据点|分数 $S$|及格线 $X$|良好线 $Y$|优秀线 $Z$|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$15$|$44000$|$47000$|$47220$|
|$2$|$15$|$39000$|$41700$|$41980$|
|$3$|$15$|$45000$|$51000$|$51390$|
|$4$|$15$|$18000$|$19000$|$19120$|
|$5$|$20$|$43000$|$48200$|$48620$|
|$6$|$20$|$44000$|$46000$|$46500$|

假设 $N$ 为得到的 AK IOI 串个数，那么评分标准为（四舍五入）：

- $N<X$，$0$ 分
- $X \le N <Y$，$\dfrac{N-X}{2(Y-X)} \times S$ 分
- $Y \le N < Z$，$\left(\dfrac{1}{2}+\dfrac{N-Y}{2(Z-Y)}\right) \times S$ 分
- $Z \le N$，$S$ 分

如果输出格式有误或输出无效，判 $0$ 分。

#### 说明

翻译自 [第１９回日本情報オリンピック　春季トレーニング合宿](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/index.html) [Day4 B 伝説の団子職人 ](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/day4/dango2.pdf)。


---

---
title: "[THUPC 2021] 混乱邪恶"
layout: "post"
diff: 省选/NOI-
pid: P7606
tag: ['2021', 'O2优化', '背包 DP', '随机化', 'THUPC']
---
# [THUPC 2021] 混乱邪恶
## 题目背景

出题人分为 $9$ 种阵营：守序善良、守序中立、守序邪恶、中立善良、绝对中立、中立邪恶、混乱善良、混乱中立和混乱邪恶。真正的出题人，就要能够在阵营之间不断切换，而又不迷失在境界之中。

境界是一个无限大的三角形网格。网格如下图，每个交叉点都有 $6$ 个相邻的交叉点。你从某一个交叉点出发，每次给一个出题 idea 设定风格都会使你在境界中移动一步。

![](https://cdn.luogu.com.cn/upload/image_hosting/dwgwh04i.png)
## 题目描述

每个出题人都有一个守序指数 $L$ 和善良指数 $G$。对于一个 idea，从题面、样例或数据范围的角度，可以从 $6$ 个方向中选择恰好一个作为这个 idea 对应的题目的特有风格，同时会在境界中沿着所选的箭头方向移动一步：

![](https://cdn.luogu.com.cn/upload/image_hosting/5k7jqygw.png)

你现在一共有 $n$ 个 idea，你知道你给每个 idea 设定某一个风格时你的 $L$ 指数和 $G$ 指数的变化。具体地，对于第 $i$ 个idea有 $12$ 个参数 $tl_{i,l},tl_{i,g},l_{i,l},l_{i,g},bl_{i,l},bl_{i,g},br_{i,l},br_{i,g},r_{i,l},r_{i,g},tr_{i,l},tr_{i,g}$：

如果选择“简洁的题面”，那么 $L$ 变成 $L+tl_{i,l}$，$G$ 变成 $G+tl_{i,g}$；

如果选择“平凡无用的样例”，那么 $L$ 变成 $L+l_{i,l}$，$G$ 变成 $G+l_{i,g}$；

如果选择“宽松的数据范围”，那么 $L$ 变成 $L+bl_{i,l}$，$G$ 变成 $G+bl_{i,g}$；

如果选择“复杂的题面”，那么 $L$ 变成 $L+br_{i,l}$，$G$ 变成 $G+br_{i,g}$；

如果选择“无私馈赠的样例”，那么 $L$ 变成 $L+r_{i,l}$，$G$ 变成 $G+r_{i,g}$；

如果选择“松松松的数据范围”，那么 $L$ 变成 $L+tr_{i,l}$，$G$ 变成 $G+tr_{i,g}$。

这里所有的加法都在模 $p$ 意义下进行。

进入混乱邪恶阵营的要求很苛刻，需要 $L$ 恰好等于 $L^*$ 且 $G$ 恰好等于 $G^*$。

你的 $L$ 指数和 $G$ 指数开始时都为 $0$。请问是否存在一种设定风格的方式使得设定完全部 $n$ 个 idea 的风格后你仍在境界中原来的位置，但是能够进入混乱邪恶阵营。
## 输入格式

第一行两个正整数 $n,p$。

接下来 $n$ 行，每行 $12$ 个非负整数 $tl_{i,l},tl_{i,g},l_{i,l},l_{i,g},bl_{i,l},bl_{i,g},br_{i,l},br_{i,g},r_{i,l},r_{i,g},tr_{i,l},tr_{i,g}$。参数的顺序与题目描述中的一致，无需额外检查。

最后一行两个非负整数 $L^*,G^*$。
## 输出格式

如果能，输出一行 `Chaotic Evil`。

如果不能，输出一行 `Not a true problem setter`。
## 样例

### 样例输入 #1
```
3 10
3 5 1 4 9 3 0 0 0 0 0 0
0 0 0 0 0 0 3 5 1 4 9 3
3 5 1 4 9 3 3 5 1 4 9 3
3 2

```
### 样例输出 #1
```
Chaotic Evil

```
## 提示

**【样例解释】**

给第 $1$ 个 idea 设定风格为”简洁的题面“，此时你的守序指数为 $0+3=3$，善良指数为 $0+5=5$。你往左上方移动一步。

给第 $3$ 个 idea 设定风格为”宽松的数据范围“，此时你的守序指数为 $3+9=2$，善良指数为 $5+3=8$。你往左下方移动一步。

给第 $2$ 个 idea 设定风格为”无私馈赠的样例“，此时你的守序指数为 $2+1=3$，善良指数为 $8+4=2$。你往右边移动一步。此时你回到了原点并且守序指数为 $3$，善良指数为 $2$。所以你可以进入混乱邪恶阵营。

**【数据范围】**

保证 $1 \le n \le 100$，$1 \le p \le 100$。

保证其他输入数据在 $0$ 到 $p-1$ 之间。

**【题目来源】**

来自 2021 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2021）。

题解等资源可在 [https://github.com/yylidiw/thupc_1/tree/master](https://github.com/yylidiw/thupc_1/tree/master) 查看。


---

---
title: "[JRKSJ R2] Dark Forest"
layout: "post"
diff: 省选/NOI-
pid: P7812
tag: ['2021', '洛谷原创', '提交答案', 'Special Judge', '模拟退火', '遗传算法', '随机化']
---
# [JRKSJ R2] Dark Forest
## 题目背景

**本题为提交答案题。**
## 题目描述

给你一个长为 $n$ 的序列 $a$，定义 $1\dots n$ 的排列 $p$ 的权值为

$$\sum_{i=1}^n p_i a_{p_{i-1}} a_{p_i}a_{p_{i+1}}$$

你可以理解为这个排列是一个环，即 $p_{0}=p_n,p_{n+1}=p_1$。

请构造一个权值**尽量大**的 $1\dots n$ 的排列。
## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个整数表示序列 $a$。
## 输出格式

一行 $n$ 个整数表示排列。
## 样例

### 样例输入 #1
```
5
1 4 3 2 5
```
### 样例输出 #1
```
1 3 5 2 4
```
## 提示

注意是 `a[p[i-1]] a[p[i+1]]`，数据有一定梯度。

### 数据范围

对于 $100\%$ 的数据，$1\le n,a_i\le 10^3$。

### 样例解释

该排列的权值为 $1\times2\times1\times3+3\times1\times3\times5+5\times3\times5\times4+2\times5\times4\times2+4\times4\times2\times1=463$，可以证明这是最优的排列之一。

### 评分方式

**本题使用 Special Judge**，每个测试点都有 $10$ 个参数 $v_1,v_2,\dots v_{10}$。如果你的输出的权值 $V\ge v_i$，则该测试点您至少会获得 $i$ 分。

特别的，如果您的输出不是一个 $1\dots n$ 的排列，您会在该测试点获得 $0$ 分。

评分参数已经放至附件。


---

---
title: "[集训队互测 2022] 在路上"
layout: "post"
diff: 省选/NOI-
pid: P9056
tag: ['集训队互测', '2022', '交互题', 'Special Judge', 'O2优化', '树论', '随机化']
---
# [集训队互测 2022] 在路上
## 题目背景

滥用本题评测者封号。

dottle bot。
## 题目描述

**这是一道交互题，仅支持 C++ 提交**。

有一棵未知的树，**保证树的大小为奇数，你需要找到这棵树重心的编号**。

你可以进行询问，每次询问你可以询问三个点 $(x,y,z)$，若不存在一条简单路径同时经过三个点，则交互器会返回 $0$，否则若存在，那么交互器会返回三个点在路径上相对顺序中间的一个点。

令 $dis(a,b)$ 表示 $a,b$ 两点在树上最短路径经过的边数，你也可以理解为:

若 $dis(x,y)+dis(x,z)=dis(y,z)$，则交互器会返回 $x$。

否则若 $dis(y,x)+dis(y,z)=dis(x,z)$，交互器会返回 $y$。

否则若 $dis(z,x)+dis(z,y)=dis(x,y)$，交互器会返回 $z$。

否则交互器会返回 $0$。

在最终的测试中，每个测试点会包含 $T$ 组测试数据，和一个常数 $M$，表示你在所有测试数据中询问次数总和的上限，具体细则见 输入格式 以及 数据范围。

#### 实现细节

~~你需要引用 `path.h` 头文件。~~ 本题中你只需要把 `path.h` 头文件的内容粘贴到程序开头即可，不要引用 `path.h` 头文件。

你需要实现下面的函数：

```
int centroid(int id,int N,int M);
```

其中 $id$ 为当前子任务的编号，$N$ 为当前询问树的大小，$M$ 为当前测试点剩余的询问次数，函数的返回值为当前树的重心编号。

具体的，在第一次调用时 $M$ 为当前测试点的询问次数上限，每次调用结束之后 $M$ 会减去当前测试点使用的询问次数。

你可以调用下面的函数：

```
int ask(int x,int y,int z);
```

表示你进行了一次询问，交互器会返回当前询问的答案，特别的，若询问次数已经超过了上限，交互器会返回 $-1$。

注意同一个测试点中 `centroid` 函数可能会被多次调用，请注意数组清空等情况。

**下发文件中有样例交互库，该交互库的实现与评测时的交互库几乎一致，如果对交互方式有不理解可以参照交互库的代码理解**。

## 输入格式

样例评测库将读入如下格式的输入数据：

第一行三个整数 $id,T,M$，表示当前的子任务编号以及测试数据的数量，以及询问次数的上界。

对于每一组测试数据，第一行一个正整数 $n$，表示当前测试数据中树的大小。

之后一行 $n-1$ 个正整数，第 $i$ 个数表示 $i+1$ 在以 $1$ 为根意义下的父亲节点。

数据的答案将在交互库内部计算。
## 输出格式

具体信息见交互库。
## 提示

#### 数据范围

![](https://cdn.luogu.com.cn/upload/image_hosting/f3d6b2zv.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

特殊性质 $A$：保证树的形态为一条链，即每个点的度数均不超过 $2$。

保证每个 Subtask 里的测试数据数量均不超过 $20$。**请仔细阅读每一档子任务及其限制**。

#### 时空限制

Subtask 5 时限为 3s。

Subtask 7,8 时限为 4s。

其余 Subtask 时限为 1s。

空间限制：512MB。

保证最终交互库的时间使用不超过  2s，空间使用不超过 64MB。

#### 下发文件

下发文件中有一个样例交互库，提供的交互头文件，一份示例代码，以及一个满足子任务 $4$ 性质的样例，选手也可以按照题目的输入格式构造其他样例。

另外也有一份洛谷样式的交互库。

保证下发的交互库和最终使用的交互库除反作弊之外没有区别，你可以使用这个交互库输出调试信息。


---

---
title: "「不死鸟附体」"
layout: "post"
diff: 省选/NOI-
pid: P9211
tag: ['字符串', 'Special Judge', '随机化', '传智杯']
---
# 「不死鸟附体」
## 题目背景

死而复生，生而复死。所谓的不死鸟就是这样的一种生物，在无尽的时间里无尽地循环往复。

果然最好还是别获得不老不死的能力吧。
## 题目描述

不死鸟的「一生」可以被看成一个长度不超过 $l_{\max}$ 的字符串 $S_0$。在无尽的轮回后形成了一个无限长的字符串 $S_{\mathrm{inf}}=S_0+S_0+S_0+\cdots$。现在截取 $S_{\mathrm{inf}}$ 前 $l$ 个字符，作为可观测时间里不死鸟的生命 $S_{\mathrm{fin}}$。

然而所谓的轮回并不是机械死板的循环往复。因此，$S_\mathrm{fin}$ 当中会有**不超过 $n$ 个字符**被修改成了别的字符，变成了 $S_{\mathrm{real}}$。

现在观测到了 $S_{\mathrm{real}}$，我们希望找到这轮回的周期 $S_0$。然而由于不死鸟的轮回太过漫长，我们只希望找到这样一个 $S_0'$，使得由它生成的 $S_\mathrm{fin}'$ 修改**不超过 $m$ 个字符**后就可以变成 $S_{\mathrm{real}}$。

## 输入格式

第一行有四个正整数 $l,l_{\max},n,m$。

第二行描述观测到的长度为 $l$ 的字符串 $S_{\mathrm{real}}$。
## 输出格式

第一行输出一个正整数 $l_0$，表示你所找到的 $S_0$ 的长度。你应当保证 $1\le l_0\le l_{\max}$。

第二行输出一个长度为 $l_0$ 的字符串 $S_0$，表示你所找到的字符串。
## 样例

### 样例输入 #1
```
25 8 5 10
aaacdaabbbaabccaabcdaabcd

```
### 样例输出 #1
```
5
aaacd
```
## 提示

### 样例解释

样例仅供理解题意，**不符合数据范围的约束**。具体约束请参见「数据范围及约定」。

生成 $S_{\mathrm{real}}$ 所用的 $S_0=\verb!aabcd!$。

- 由此生成 $S_{\mathrm{inf}}=\verb!aabcdaabcdaabcdaabcdaabcd!\cdots$；
- 由此生成 $S_{\mathrm{fin}}=\verb!aabcdaabcdaabcdaabcdaabcd!$；
- 由此生成 $S_{\mathrm{real}\kern{-2.5pt}}=\verb!aaacdaabbbaabccaabcdaabcd!$。

样例输出给出了一个可能的 $S_0'=\verb!aaacd!$。由此计算出 $S_{\mathrm{fin}}'$ 与 $S_{\mathrm{real}}$ 的差距：

$$\begin{aligned}
S_{\mathrm{fin}}'=&\texttt{aaacdaa\textcolor{red}a\textcolor{red}c\textcolor{red}daa\textcolor{red}ac\textcolor{red}daa\textcolor{red}acdaa\textcolor{red}acd}\cr
S_{\mathrm{real}}=&\texttt{aaacdaabbbaabccaabcdaabcd}\cr
\end{aligned}$$

相差为 $7$，不超过 $m=10$，可以被接受。

### 数据范围及约定

对于全部数据，保证 $l=3\times 10^5$，$n=3\times 10^3$，$m=10^4$，$1\le l_{\max} \le 10^5$。


---

---
title: "「DROI」Round 2  进制与操作"
layout: "post"
diff: 省选/NOI-
pid: P9376
tag: ['莫队', '树状数组', 'O2优化', '可持久化线段树', '随机化']
---
# 「DROI」Round 2  进制与操作
## 题目背景

与其编写苍白无力的背景，不如出更有质量的题。
## 题目描述

定义数 $x$ 在 $B$ 进制下的一次操作为以下两种操作中的任意一种：

- 令 $x \rightarrow \lfloor \dfrac{x}{B} \rfloor$。

- 令 $x \rightarrow x \times B + t $。其中 $t \in [0,B-1]$。

现给定长度为 $n$ 的序列 $A$。$m$ 次询问，每次询问形如：

- `l r B` 表示询问将序列 $A$ 中下标在 $[l,r]$ 之内的数在 $B$ 进制下操作，至少多少次才能将所有数变为相同（注：每次操作是对**一个数**进行操作）。

**询问间相互独立，即操作不会真的进行。**


## 输入格式

第一个两个整数，分别表示 $n,m$。

第二行一行 $n$ 个数，表示序列 $A$。

接下来 $m$ 行，每行三个数，分别表示这次询问的 $l,r,B$。
## 输出格式

输出共 $m$ 行，其中第 $i$ 行表示第 $i$ 次询问的答案。
## 样例

### 样例输入 #1
```
5 5
7 6 5 8 9
1 3 2
2 5 2
4 4 6
3 5 4
1 5 3
```
### 样例输出 #1
```
5
8
0
5 
10
```
### 样例输入 #2
```
8 4
10 14 7 11 19 13 7 18 
1 7 4
3 8 2
1 4 4
1 4 2

```
### 样例输出 #2
```
15
18
8
11

```
## 提示

### 样例解释

对于样例一，五次询问分别将区间内所有数变为 $3$、$4$、$8$、$4$、$6$ 是一种最优操作。

------------

### 数据范围 

**「本题采用捆绑测试」**

- $\operatorname{Subtask} 1(10\%)$：$n,m \leq 1000$。

- $\operatorname{Subtask} 2(20\%)$：保证所有询问 $B=2$。

- $\operatorname{Subtask} 3(40\%)$：$n,m \leq 3 \times 10^4$。

- $\operatorname{Subtask} 4(30\%)$：无特殊限制。

对于 $100\%$ 的数据：$1 \leq n,m \leq 10^5$，$2 \leq A_i,B \leq 10^8$。



---

