---
title: "[NOISG 2022 Qualification] Dragonfly"
layout: "post"
diff: 省选/NOI-
pid: P11295
tag: ['2022', '树链剖分', '整体二分', 'NOISG（新加坡）']
---
# [NOISG 2022 Qualification] Dragonfly
## 题目背景

在植物园和碧山公园周围的池塘中，经常可以看到蜻蜓。在一个更密集的森林区域中，Benson 记录了 $n$ 个池塘，以及蜻蜓可以捕食的昆虫数量和种类。

在池塘 $i$，共有 $b_i$ 只昆虫，这些昆虫属于种类 $s_i$。

此外，还有 $n-1$ 条小径，每条小径连接两池塘 $u_j$ 和 $v_j$（双向）。

Benson 抓住了 $d$ 只蜻蜓，并计划依次释放到池塘 $1$。每只蜻蜓有一个目标池塘 $h_k \neq 1$，会沿着最短路径飞到目标池塘，并在经过的每个池塘中捕食昆虫（包括池塘 $1$）。

每次捕食会减少池塘中 $1$ 只昆虫（如果昆虫数量不为 $0$）。需要帮助 Benson 计算每只蜻蜓的飞行过程中捕食到的不同种类昆虫的数量。
## 题目描述

请确定每只蜻蜓的飞行过程中捕食到的不同种类昆虫的数量。
## 输入格式

- 第一行包含两个整数 $n$ 和 $d$，分别表示池塘数量和蜻蜓数量。
- 第二行包含 $n$ 个整数 $b_1, b_2, \dots, b_n$，表示每个池塘的昆虫数量。
- 第三行包含 $n$ 个整数 $s_1, s_2, \dots, s_n$，表示每个池塘昆虫的种类。
- 第四行包含 $d$ 个整数 $h_1, h_2, \dots, h_d$，表示每只蜻蜓的目标池塘。
- 接下来 $n-1$ 行，每行包含两个整数 $u_j$ 和 $v_j$，表示一条连接池塘 $u_j$ 和 $v_j$ 的小径。
## 输出格式

输出一行包含 $d$ 个整数，第 $k$ 个整数表示第 $k$ 只蜻蜓捕食到的不同种类昆虫数量。
## 样例

### 样例输入 #1
```
5 6
4 1 0 3 1
1 3 2 2 1
2 5 4 3 4 2
5 2
2 1
1 4
1 3
```
### 样例输出 #1
```
2 1 2 1 1 0
```
### 样例输入 #2
```
7 4
0 2 4 4 0 1 3
6 1 6 2 2 2 1
7 5 2 4
4 1
4 5
6 2
1 6
1 3
6 7
```
### 样例输出 #2
```
2 1 1 1
```
## 提示

【样例解释】

对于样例 $1$，第一只蜻蜓飞向池塘 $2$，捕食 $1$ 只种类 $1$ 的昆虫和 $1$ 只种类 $2$ 的昆虫。第二只蜻蜓飞向池塘 $5$，捕食种类 $1$ 的昆虫，总共捕食 $1$ 个种类。  

对于样例 $2$，每只蜻蜓飞行后捕食到的不同种类分别是 $2, 1, 1, 1$。

【数据范围】

- $2 \leq n \leq 2 \times 10^5$
- $1 \leq d \leq 2 \times 10^6$
- $1 \leq s_i \leq n$，$0 \leq b_i \leq d$，$1 \leq u_j, v_j < n$

| 子任务编号 | 分值 | 额外限制条件                              |
| :--------: | :--: | :---------------------------------------: |
| $1$        | $10$ | $n, d \leq 1000$                          |
| $2$        | $10$ | $b_i = d$                                 |
| $3$        | $12$ | $b_i \leq 10$                             |
| $4$        | $12$ | $u_j = j$, $v_j = j + 1$                  |
| $5$        | $37$ | $s_i = i$                                 |
| $6$        | $16$ | $d \leq 2 \times 10^5$                    |
| $7$        |  $3$ | 无额外限制                                |


---

---
title: "[国家集训队] 矩阵乘法"
layout: "post"
diff: 省选/NOI-
pid: P1527
tag: ['集训队互测', 'O2优化', '整体二分']
---
# [国家集训队] 矩阵乘法
## 题目描述

给你一个 $n \times n$ 的矩阵，不用算矩阵乘法，但是每次询问一个子矩形的第 $k$ 小数。

## 输入格式

第一行有两个整数，分别表示矩阵大小 $n$ 和询问组数 $q$。

第 $2$ 到第 $(n + 1)$ 行，每行 $n$ 个整数，表示这个矩阵。第 $(i + 1)$ 行的第 $j$ 个数表示矩阵第 $i$ 行第 $j$ 列的数 $a_{i, j}$。

接下来 $q$ 行，每行五个整数 $x_1, y_1, x_2, y_2, k$，表示一组询问，要求找到以 $(x_1, y_1)$ 为左上角，$(x_2, y_2)$ 为右下角的子矩形中的第 $k$ 小数。
## 输出格式

对于每组询问，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2 2
2 1
3 4
1 2 1 2 1
1 1 2 2 3

```
### 样例输出 #1
```
1
3
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 100$，$q \leq 10^3$。
- 对于 $40\%$ 的数据，保证 $n \leq 300$，$q \leq 10^4$。
- 对于 $60\%$ 的数据，保证 $n \leq 400$，$q \leq 3 \times 10^4$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 500$，$1 \leq q \leq 6 \times 10^4$，$0 \leq a_{i, j} \leq 10^9$。


---

---
title: "[ZJOI2013] K大数查询"
layout: "post"
diff: 省选/NOI-
pid: P3332
tag: ['2013', '线段树', '浙江', '树套树', '整体二分']
---
# [ZJOI2013] K大数查询
## 题目描述

你需要维护 $n$ 个可重整数集，集合的编号从 $1$ 到 $n$。  
这些集合初始都是空集，有 $m$ 个操作：  

- `1 l r c`：表示将 $c$ 加入到编号在 $[l,r]$ 内的集合中  
- `2 l r c`：表示查询编号在 $[l,r]$ 内的集合的并集中，第 $c$ 大的数是多少。  

注意可重集的并是不去除重复元素的，如 $\{1,1,4\}\cup\{5,1,4\}=\{1,1,4,5,1,4\}$。

## 输入格式

第一行两个正整数 $n,m$，表示集合个数和操作个数。  
接下来 $m$ 行，每行四个整数表示一次操作。

## 输出格式

对于每个 $2$ 操作，输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
2 5
1 1 2 1
1 1 2 2
2 1 1 2
2 1 1 1
2 1 2 3
```
### 样例输出 #1
```
1
2
1
```
## 提示

【样例说明】   
第 $1$ 次操作在 $1,2$ 号集合中分别加入了一个  $1$。    
第 $2$ 次操作在 $1,2$ 号集合中分别加入了一个 $2$。   
第 $3$ 次操作查询 $1$ 号集合中第 $2$ 大的数，答案为 $1$。  
第 $4$ 次操作查询 $1$ 号集合中第 $1$ 大的数，答案为 $2$。    
第 $5$ 次操作查询 $1,2$ 号集合的并集 $\{1,2,1,2\}$ 中第 $3$ 大的数，答案为 $1$。

【数据范围】  
$1 \le n,m \le 5\times 10^4$   
$1\le l,r \le n$   
$1$ 操作中 $|c|\le n$   
$2$ 操作中 $1\le c < 2^{63}$，第 $c$ 大的数存在

---

$\text{upd 2023.8.23}$：新增加一组 Hack 数据。


---

---
title: "[POI 2011] MET-Meteors"
layout: "post"
diff: 省选/NOI-
pid: P3527
tag: ['2011', '二分', '树状数组', 'POI（波兰）', 'O2优化', '整体二分', '离线处理']
---
# [POI 2011] MET-Meteors
## 题目描述

Byteotian Interstellar Union (BIU) has recently discovered a new planet in a nearby galaxy.  The planet is unsuitable for colonisation due to strange  meteor showers, which on the other hand make it an exceptionally interesting  object of study.

The member states of BIU have already placed space stations close to the  planet's orbit.  The stations' goal is to take samples of the rocks flying by.

The BIU Commission has partitioned the orbit into $m$ sectors, numbered  from $1$ to $m$, where the sectors $1$ and $m$ are adjacent.  In each sector  there is a single space station, belonging to one of the $n$ member states.

Each state has declared a number of meteor samples it intends to gather before  the mission ends.  Your task is to determine, for each state, when it can  stop taking samples, based on the meter shower predictions for the years to  come.



## 输入格式

The first line of the standard input gives two integers, $n$ and $m$ ($1\le n,m\le 300\ 000$), separated by a single space, that denote,respectively, the number of BIU member states and the number of sectors    the orbit has been partitioned into.

In the second line there are $m$ integers $o_i$ ($1\le o_i\le n$),separated by single spaces, that denote the states owning stations in    successive sectors.

In the third line there are $n$ integers $p_i$ ($1\le p_i\le 10^9$),separated by single spaces, that denote the numbers of meteor samples that the successive states intend to gather.

In the fourth line there is a single integer $k$ ($1\le k\le 300\ 000$) that denotes the number of meteor showers predictions. The following $k$ lines specify the (predicted) meteor showers chronologically. The $i$-th of these lines holds three integers $l_i,r_i,a_i$ (separated by single spaces), which denote that a meteor shower is expected in sectors $l_i,l_{i+1},...,r_i$(if $l_i\le r_i$) or sectors $l_i,l_{i+1},...,m,1,...,r_i$ (if $l_i>r_i$) , which should provide each station in those sectors with $a_i$ meteor samples ($1\le a_i\le 10^9$).

## 输出格式

Your program should print $n$ lines on the standard output.

The $i$-th of them should contain a single integer $w_i$, denoting the number of shower after which the stations belonging to the $i$-th state are    expected to gather at least $p_i$ samples, or the word NIE (Polish for no) if that state is not expected to gather enough samples in the foreseeable future.

## 样例

### 样例输入 #1
```
3 5
1 3 2 1 3
10 5 7
3
4 2 4
1 3 1
3 5 2
```
### 样例输出 #1
```
3
NIE
1
```
## 题目翻译

Byteotian Interstellar Union 

有 $n​$ 个成员国。现在它发现了一颗新的星球，这颗星球的轨道被分为 $m​$ 份（第 $m​$ 份和第 $1​$ 份相邻），第 $i​$ 份上有第 $a_i​$ 个国家的太空站。

这个星球经常会下陨石雨。BIU 已经预测了接下来 $k$ 场陨石雨的情况。

BIU 的第 $i$ 个成员国希望能够收集 $p_i$ 单位的陨石样本。你的任务是判断对于每个国家，它需要在第几次陨石雨之后，才能收集足够的陨石。

#### 输入格式

第一行是两个数 $n,m$。

第二行有 $m$ 个数，第 $i$ 个数 $o_i$ 表示第 $i$ 段轨道上有第 $o_i$ 个国家的太空站。

第三行有 $n$ 个数，第 $i$ 个数 $p_i$ 表示第 $i$ 个国家希望收集的陨石数量。

第四行有一个数 $k$，表示 BIU 预测了接下来的 $k$ 场陨石雨。 接下来 $k$ 行，每行有三个数 $l_i,r_i,a_i$ ，表示第 $k$ 场陨石雨的发生地点在从 $l_i$ 顺时针到 $r_i$ 的区间中（如果 $l_i \leq r_i$，则是 $l_i, l_i + 1 
\cdots, r_i$，否则就是 $l_i, l_i + 1, 
\cdots m - 1, m, 1, 2, \cdots r_i$），向区间中的每个太空站提供 $a_i$ 单位的陨石样本。

#### 输出格式

输出 $n$ 行。第 $i$ 行的数 $w_i$ 表示第 $i$ 个国家在第 $w_i$ 波陨石雨之后能够收集到足够的陨石样本。如果到第 $k$ 波结束后仍然收集不到，输出 `NIE`。

#### 数据范围

$1\le n,m,k\le 3\cdot10^5$；

$1\le p_i,a_i\le 10^9$；


---

---
title: "【模板】三维偏序（陌上花开）"
layout: "post"
diff: 省选/NOI-
pid: P3810
tag: ['树状数组', 'cdq 分治', 'O2优化', '分治', '排序', '整体二分', 'K-D Tree']
---
# 【模板】三维偏序（陌上花开）
## 题目背景

这是一道模板题，可以使用 bitset，CDQ 分治，KD-Tree 等方式解决。
## 题目描述

有 $ n $ 个元素，第 $ i $ 个元素有 $ a_i,b_i,c_i $ 三个属性，设 $ f(i) $ 表示满足 $ a_j \leq a_i $ 且 $ b_j \leq b_i $ 且 $ c_j \leq c_i $ 且 $ j \ne i $ 的 $j$ 的数量。

对于 $ d \in [0, n) $，求 $ f(i) = d $ 的数量。
## 输入格式

第一行两个整数 $ n,k $，表示元素数量和最大属性值。

接下来 $ n $ 行，每行三个整数 $ a_i ,b_i,c_i $，分别表示三个属性值。
## 输出格式

$ n $ 行，第 $ d + 1 $ 行表示 $ f(i) = d $ 的 $ i $ 的数量。
## 样例

### 样例输入 #1
```
10 3
3 3 3
2 3 3
2 3 1
3 1 1
3 1 2
1 3 1
1 1 2
1 2 2
1 3 2
1 2 1

```
### 样例输出 #1
```
3
1
3
0
1
0
1
0
0
1

```
## 提示

$ 1 \leq n \leq 10^5$，$1 \leq a_i, b_i, c_i \le k \leq 2 \times 10^5 $。



---

---
title: "[CTSC2018] 混合果汁"
layout: "post"
diff: 省选/NOI-
pid: P4602
tag: ['2018', '线段树', 'O2优化', '可持久化', '整体二分', 'CTSC/CTS']
---
# [CTSC2018] 混合果汁
## 题目描述

小 R 热衷于做黑暗料理，尤其是混合果汁。

商店里有 $n$ 种果汁，编号为 $0,1,\cdots,n-1$ 。$i$ 号果汁的美味度是 $d_i$，每升价格为 $p_i$。小 R 在制作混合果汁时，还有一些特殊的规定，即在一瓶混合果汁中，$i$ 号果汁最多只能添加 $l_i$ 升。

现在有 $m$ 个小朋友过来找小 R 要混合果汁喝，他们都希望小 R 用商店里的果汁制作成一瓶混合果汁。其中，第 $j$ 个小朋友希望他得到的混合果汁总价格不大于 $g_j$，体积不小于 $L_j$。在上述这些限制条件下，小朋友们还希望混合果汁的美味度尽可能地高，一瓶混合果汁的美味度等于所有参与混合的果汁的美味度的最小值。请你计算每个小朋友能喝到的最美味的混合果汁的美味度。
## 输入格式

输入第一行包含两个正整数 $n, m$，表示果汁的种数和小朋友的数量。

接下来 $n$ 行，每行三个正整数 $d_i, p_i, l_i$，表示 $i$ 号果汁的美味度为 $d_i$，每升价格为 $p_i$，在一瓶果汁中的添加上限为 $l_i$。

接下来 $m$ 行依次描述所有小朋友：每行两个数正整数 $g_j, L_j$ 描述一个小朋友，表示他最多能支付 $g_j$ 元钱，他想要至少 $L_j$ 升果汁。
## 输出格式

对于所有小朋友依次输出：对于每个小朋友，输出一行，包含一个整数，表示他能喝到的最美味的混合果汁的美味度。如果无法满足他的需求，则输出 $-1$。

## 样例

### 样例输入 #1
```
3 4
1 3 5
2 1 3
3 2 5
6 3
5 3
10 10
20 10
```
### 样例输出 #1
```
3
2
-1
1
```
## 提示

对于所有的测试数据，保证 $n, m \le 100000$，$1 \le d_i,p_i,l_i \le 10^5$，$1 \le g_j, L_j \le 10^{18}$。

测试点编号|$n=$|$m=$|其他限制
-|-|-|-
$1,2,3$|$10$|$10$|无
$4,5,6$|$500$|$500$|无
$7,8,9$|$5000$|$5000$|无
$10,11,12$|$100000$|$100000$|$p_i=1$
$13,14,15$|$100000$|$100000$|$l_i=1$
$16,17,18,19,20$|$100000$|$100000$|无


---

---
title: "[THUPC 2017] 天天爱射击"
layout: "post"
diff: 省选/NOI-
pid: P7424
tag: ['2017', '树状数组', '可持久化线段树', '可持久化', '分块', '整体二分', 'THUPC']
---
# [THUPC 2017] 天天爱射击
## 题目描述

小 C 爱上了一款名字叫做《天天爱射击》的游戏。如图所示，这个游戏有一些平行于 $x$ 轴的木板。现在有一些子弹，按顺序沿着 $y$ 轴方向向这些木板射去。第 $i$ 块木板被 $S_i$ 个子弹贯穿以后，就会碎掉消失。一个子弹可以贯穿其弹道上的全部木板，特别的，如果一个子弹触碰到木板的边缘，也视为贯穿木板。

小 C 现在知道了游戏中 $n$ 块木板位置，以及知道了 $m$ 个子弹射击位置。现在问你每个子弹射出去以后，有多少木板会碎掉？
## 输入格式

从标准输入读入数据。

第一行两个整数 $n$ 和 $m$，表示木板数量和子弹数量。其中 $1\le n,m\le 2\times 10^5$。

接下来 $n$ 行，每行三个整数 $x_1,x_2,s$，表示每块木板的左端点 $x$ 坐标、右端点 $x$ 坐标，以及贯穿多少次会碎掉。其中保证 $1\le x_1\le x_2\le2\times 10^5,1\le s\le 2\times 10^5$。

接下来 $m$ 行，每行一个整数 ，表示每个子弹的 $x$ 坐标。子弹按照发射顺序给出。其中保证 $1\le x\le2\times 10^5$。
## 输出格式

输出到标准输出。

$m$ 行，每行一个整数。表示每颗子弹射出去后，有多少木板碎掉。
## 样例

### 样例输入 #1
```
3 2
1 3 1
2 4 2
3 4 1
2
3
```
### 样例输出 #1
```
1
2
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/ocqlbnl3.png)
#### 版权信息
来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2017。

$\text{upd}2021.7.6$：感谢 @[jiangbowen](https://www.luogu.com.cn/user/366807) 提供的一组 hack 数据，不计分，但若不通过 hack 数据则不算通过此题。


---

