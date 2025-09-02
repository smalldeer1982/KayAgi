---
title: "[yLCPC2024] A. dx 分计算"
layout: "post"
diff: 普及-
pid: P10233
tag: ['洛谷原创', '前缀和', '差分', '洛谷月赛']
---
# [yLCPC2024] A. dx 分计算
## 题目背景

你说的对，但舞萌 DX 是一款由 SEGA 开发，华立科技代理，形似洗衣机的街机音乐游戏。

只要看准时机拍到所有的音符就好啦！
## 题目描述

在舞萌 DX 中，每个音符根据完成击打的时刻，会得到如下五种判定：

- `Critical Perfect`：简记为 `P`，可得 $3$ 分 dx 分。
- `Perfect`：简记为 `p`，可得 $2$ 分 dx 分。
- `Great`：简记为 `G`，可得 $1$ 分 dx 分。
- `Good`：简记为 `g`，不能得到 dx 分。
- `Miss`：简记为 `m`，不能得到 dx 分。

扶苏游玩了一局舞萌 DX，她将她各个音符的判定情况按顺序使用上面的简记规则记为了一个字符串 $s$。规定这个字符串最左边的字符表示第一个音符的判定结果，最右边的字符表示第 $|s|$ 个音符的判定结果，这里 $|s|$ 表示字符串 $|s|$ 的长度，也即整首歌的音符数。

现在，扶苏有 $q$ 次询问，每次询问会给出两个整数 $l, r$，对每个询问你需要回答：这首歌的第 $l$ 个音符到第 $r$ 个音符（包含第 $l$ 个和第 $r$ 个）的判定结果共能得到多少 dx 分数？

乐曲一段区间内的音符得到的 dx 分数是这些音符分别能得到的 dx 分数之和。
## 输入格式

**本题单个测试点内有多组测试数据**，输入的第一行是一个正整数，表示数据组数 $T$。对每组测试数据：

第一行是一个字符串 $s$（$1 \leq |s| \leq 10^7$），表示一首歌各个音符的判定结果。保证 $s$ 中只含字符 `P`，`p`，`G`，`g`，`m`。  
第二行有一个整数 $q$（$1 \leq q \leq 10^4$），表示询问的数量。  
接下来 $q$ 行，每行两个整数 $l, r$（$1 \leq l \leq r \leq |s|$），表示一组询问。

数据保证单个测试点内 $s$ 的长度之和不超过 $10^7$，$q$ 之和不超过 $10^4$。
## 输出格式

对每组测试数据，按询问的顺序依次给出每个询问的答案。每个询问输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2
PpGgm
2
1 5
4 5
PPppGGgm
5
1 2
3 4
5 6
7 7
8 8
```
### 样例输出 #1
```
6
0
6
4
2
0
0
```


---

---
title: "[CSP-J2022 山东] 植树节"
layout: "post"
diff: 普及-
pid: P11853
tag: ['2022', '山东', '差分', 'CSP-J 入门级']
---
# [CSP-J2022 山东] 植树节
## 题目背景

受疫情影响，山东省取消了 CSP-J 2022 认证活动，并于次年三月重新命题，在省内补办比赛。
## 题目描述

植树节快要到了，学校要组织志愿者去给树苗浇水。

有一排树苗，编号依次是 $0,1,2,\dots$。

现有 $n$ 个志愿者去给树苗浇水，第 $i$ 个志愿者选定了一个区间 $\left[a_{i},b_{i}\right]$ ，表示第 $i$ 个志愿者将 $\left[a_{i},b_{i}\right]$ 这一区间内的每一棵树都浇一次水。

如某个志愿者选择的浇水区间为 $\left[4,9\right]$ ，表示他将给编号为 $4,5,6,7,8,9$ 的树各浇水一次。

当所有的志愿者完成各自所选区间的浇水后，可能有些树苗被不同的志愿者浇水多次，也可能有的树苗一次也没被浇过水。

请你求出浇水最多的树苗被浇了多少次。
## 输入格式

第 $1$ 行，一个整数 $n$ ，表示志愿者的人数。

第 $2$ 行到第 $n+1$ 行，每行两个整数 $a_{i},b_{i} $（$i=0,1,2,\dots n-1$），表示志愿者 $i$ 选择的浇水区间。
## 输出格式

输出 $1$ 行， $1$ 个整数，表示浇水最多的树苗被浇水的次数。
## 样例

### 样例输入 #1
```
4
0 2
2 4
1 4
6 7
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4
1000000 1000000
1000000 1000000
0 1000000
1 1000000
```
### 样例输出 #2
```
4
```
## 提示

### 数据范围
* 对于所有的数据： $n<10^{5}$；$0\le a_{i}\le b_{i}\le 10^{6}$。  

|测试点编号|$a_{i}\le$|$b_{i}\le$|$n_{i}\le$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1,2,3$|$10^{3}$|$10^{3}$|$10^{3}$|无|
|$4,5,6,7$|$10^{6}$|$10^{6}$|$10^{5}$|无|
|$8$|$10^{6}$|$10^{6}$|$10^{5}$|$a_{i}=b_{i}$|
|$9$|$10^{6}$|$10^{6}$|$10^{5}$|$a_{i}=1,b_{i}=10^{3}$|
|$10$|$10^{6}$|$10^{6}$|$10^{5}$|无|



---

---
title: "[Algo Beat Contest 002 C] Counting Square Numbers"
layout: "post"
diff: 普及-
pid: P12716
tag: ['O2优化', '前缀和', '差分']
---
# [Algo Beat Contest 002 C] Counting Square Numbers
## 题目背景

| Problem | Score | Idea | Std | Data | Check | Solution |
| :----------------------------------: | :---: | :---------------------------------------------------: | :---------------------------------------------------: | :---------------------------------------------: | :-------------------------------------------------: | :----------------------------------------------------------: |
|     $\text{C - Counting Square Numbers}$      | $300$ | [wenqinghua1001](https://www.luogu.com.cn/user/976198) | [wenqinghua1001](https://www.luogu.com.cn/user/976198) | [joe_zxq](https://www.luogu.com.cn/user/623577) | [joe_zxq](https://www.luogu.com.cn/user/623577) |     [Link](https://www.luogu.com.cn/article/75je5m51) by [joe_zxq](https://www.luogu.com.cn/user/623577)     |
## 题目描述

wtr1 和 wqh 是一对好朋友。

wqh 给了 wtr1 一个长度为 $n$ 的数组 $A$。对于 $i=1,2,\dots,n$，需要 wtr1 给出包含了位置 $i$ 且区间和为完全平方数的子数组个数。由于最近 wtr1 很忙，请聪明的你帮帮他吧！

若一个数是一个整数的平方，则称这个数是**完全平方数**。

原数组中某段下标连续的元素按原顺序构成的数组称为**子数组**。
## 输入格式

第一行输入一个正整数 $n$，表示数组 $A$ 的长度。

第二行输入 $n$ 个整数 $A_1,\dots,A_n$，表示 $A$ 中的元素。
## 输出格式

输出 $n$ 行，每行包含一个非负整数，表示符合条件的区间数。
## 样例

### 样例输入 #1
```
5
1 2 3 4 5
```
### 样例输出 #1
```
1
1
1
3
1

```
## 提示

**【样例解释 #1】**

包含位置 $2$ 的区间和为完全平方数是 $2+3+4=9$，只有 $1$ 个。

包含位置 $4$ 的区间和为完全平方数是 $2+3+4=9$，$4+5=9$ 以及 $4$ 本身，共 $3$ 个。

**【数据范围】**

- $1 \le n \le 5 \times 10^3$。
- $0 \le a_i \le 10^9$。


---

---
title: "语文成绩"
layout: "post"
diff: 普及-
pid: P2367
tag: ['差分']
---
# 语文成绩
## 题目背景

语文考试结束了，成绩还是一如既往地有问题。

## 题目描述

语文老师总是写错成绩，所以当她修改成绩的时候，总是累得不行。她总是要一遍遍地给某些同学增加分数，又要注意最低分是多少。你能帮帮她吗？

## 输入格式

第一行有两个整数 $n$，$p$，代表学生数与增加分数的次数。

第二行有 $n$ 个数，$a_1 \sim a_n$，代表各个学生的初始成绩。

接下来 $p$ 行，每行有三个数，$x$，$y$，$z$，代表给第 $x$ 个到第 $y$ 个学生每人增加 $z$ 分。
## 输出格式

输出仅一行，代表更改分数后，全班的最低分。

## 样例

### 样例输入 #1
```
3 2
1 1 1
1 2 1
2 3 1
```
### 样例输出 #1
```
2

```
## 提示

对于 $40\%$ 的数据，有 $n \le 10^3$。

对于 $60\%$ 的数据，有 $n \le 10^4$。

对于 $80\%$ 的数据，有 $n \le 10^5$。

对于 $100\%$ 的数据，有 $n \le 5\times 10^6$，$p \le n$，学生初始成绩 $ \le 100$，$z \le 100$。


---

---
title: "[USACO18DEC] The Bucket List B"
layout: "post"
diff: 普及-
pid: P5117
tag: ['模拟', '2018', 'USACO', '差分']
---
# [USACO18DEC] The Bucket List B
## 题目描述

Farmer John 正在考虑改变他给奶牛挤奶的时候分配牛奶桶的方式。他认为这最终能使得他使用数量更少的桶，然而他不清楚具体是多少。请帮助他！

Farmer John 有 $N$ 头奶牛（$1\le N\le 100$），方便起见编号为 $1\dots N$。 第 $i$ 头奶牛需要从时间 $s_i$ 到时间 $t_i$ 之间挤奶，并且挤奶过程中需要用到 $b_i$ 个桶。于是多头奶牛可能在同一时刻都在挤奶；如果这样，他们不能使用相同的桶。也就是说，一个在第 $i$ 头奶牛挤奶时用的桶不可以被任何在时间 $s_i$ 到时间 $t_i$ 之间挤奶的其他奶牛使用。当然，这个桶在这段时间之外可以被其他奶牛所使用。为了简化他的工作，FJ 保证在任一时刻，至多只有一头奶牛开始或是结束挤奶（也就是说，所有的 $s_i$ 和 $t_i$ 各不相同）。

FJ 有一个储藏室，里面有依次编号为 $1$、$2$、$3$、……的桶。在他的挤奶策略中，当某一头奶牛（比如说，奶牛 $i$）开始挤奶（在时间 $s_i$），FJ 就跑到储藏室取出编号最小的 $b_i$ 个桶分配给第i头奶牛用来挤奶。

请求出 FJ 需要在储藏室中存放多少个桶才能使得他能够顺利地给所有奶牛挤奶。

## 输入格式

输入的第一行包含 $N$。以下 $N$ 行，每行描述了一头奶牛，包含三个空格分隔的数 $s_i$，$t_i$，和 $b_i$。 其中 $s_i$ 和 $t_i$ 均为 $1\dots 1000$ 之间的整数，$b_i$ 为 $1\dots 10$ 之间的整数。
## 输出格式

输出一个整数，为 FJ 需要的桶的数量。
## 样例

### 样例输入 #1
```
3
4 10 1
8 13 3
2 6 2
```
### 样例输出 #1
```
4
```
## 提示

在这个例子中，FJ 需要 $4$ 个桶：他用桶 $1$ 和桶 $2$ 来给奶牛 $3$ 挤奶（从时间 $2$ 开始）。他用桶 $3$ 给奶牛 $1$ 挤奶（从时间 $4$ 开始）。当奶牛 $2$ 在时间 $8$ 开始挤奶时，桶 $1$ 和桶 $2$ 可以再次利用，然而桶 $3$ 不可以，所以他会使用桶 $1$、桶 $2$ 和桶 $4$。


---

---
title: "「EZEC-10」排列排序"
layout: "post"
diff: 普及-
pid: P7714
tag: ['模拟', '\ufeff基础算法', '构造', '差分', '双指针 two-pointer']
---
# 「EZEC-10」排列排序
## 题目描述

给你一个长度为 $n$ 的排列 $p_1,p_2, \cdots ,p_n$。你需要把它排序。

每次可以花区间长度，即 $r-l+1$ 的代价，选择排列中的任意一段区间 $[l,r]$，并将 $[l,r]$ 从小到大排序。

现在你可以让他进行若干次这个操作，直到 $p$ 中元素的值从 $1$ 到 $n$ 按升序排序，即对于 $1$ 到 $n$ 的每一个 $i$，都有 $p_i=i$。

求问花的代价最少为多少？
## 输入格式

本题有多组询问，第一行有一个数 $T$ 表示询问组数。

对于每组询问：

第一行给出一个整数 $n$。

第二行 $n$ 个整数，由空格隔开，代表排列 $p$ 中元素的值。
## 输出格式

$T$ 行，每行一个整数表示一组询问的答案。
## 样例

### 样例输入 #1
```
2
3
1 3 2
4
3 2 1 4
```
### 样例输出 #1
```
2
3
```
## 提示

【样例 $1$ 说明】

对于第一组数据，可选择区间 $[2,3]$ 进行排序。

对于第二组数据，可选择区间 $[1,3]$ 进行排序。

【数据规模与约定】

对于 $20\%$ 的数据，$n\leq 4$。

对于另 $30\%$ 的数据，$\sum n\leq5000$。

对于另 $10\%$ 的数据，$p_1=n$。

对于 $100\%$ 的数据，$1\le T,\sum n\le 10^6$。


---

---
title: "[蓝桥杯 2022 省 A] 求和"
layout: "post"
diff: 普及-
pid: P8772
tag: ['2022', '前缀和', '差分', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 A] 求和
## 题目描述

给定 $n$ 个整数 $a_{1}, a_{2}, \cdots, a_{n}$, 求它们两两相乘再相加的和，即

$$
S=a_{1} \cdot a_{2}+a_{1} \cdot a_{3}+\cdots+a_{1} \cdot a_{n}+a_{2} \cdot a_{3}+\cdots+a_{n-2} \cdot a_{n-1}+a_{n-2} \cdot a_{n}+a_{n-1} \cdot a_{n}
$$

## 输入格式

输入的第一行包含一个整数 $n$ 。

第二行包含 $n$ 个整数 $a_{1}, a_{2}, \cdots a_{n}$ 。

## 输出格式

输出一个整数 $S$，表示所求的和。请使用合适的数据类型进行运算。
## 样例

### 样例输入 #1
```
4
1 3 6 9
```
### 样例输出 #1
```
117
```
## 提示

对于 $30 \%$ 的数据, $1 \leq n \leq 1000,1 \leq a_{i} \leq 100$ 。

对于所有评测用例, $1 \leq n \leq 2\times10^5,1 \leq a_{i} \leq 1000$ 。 

蓝桥杯 2022 省赛 A 组 C 题。


---

---
title: "[USACO23JAN] Air Cownditioning II B"
layout: "post"
diff: 普及-
pid: P9011
tag: ['USACO', '2023', '深度优先搜索 DFS', '差分']
---
# [USACO23JAN] Air Cownditioning II B
## 题目描述

With the hottest recorded summer ever at Farmer John's farm, he needs a way to cool down his cows. Thus, he decides to invest in some air conditioners.

Farmer John's $N$ cows $(1 \le N \le 20)$ live in a barn that contains a sequence of stalls in a row, numbered $1 \cdots 100$. Cow $i$ occupies a range of these stalls, starting from stall $s_i$ and ending with stall $t_i$. The ranges of stalls occupied by different cows are all disjoint from each-other. Cows have different cooling requirements. Cow $i$ must be cooled by an amount $c_i$, meaning every stall occupied by cow $i$ must have its temperature reduced by at least $c_i$ units.

The barn contains $M$ air conditioners, labeled $1 \cdots M (1 \le M \le 10)$. The $i$-th air conditioner costs $m_i$ units of money to operate $(1 \le m_i \le 1000)$ and cools the range of stalls starting from stall $a_i$ and ending with stall $b_i$. If running, the $i$-th air conditioner reduces the temperature of all the stalls in this range by $p_i (1 \le p_i \le 10^6)$. Ranges of stalls covered by air conditioners may potentially overlap.

Running a farm is no easy business, so FJ has a tight budget. Please determine the minimum amount of money he needs to spend to keep all of his cows comfortable. It is guaranteed that if FJ uses all of his conditioners, then all cows will be comfortable. 
## 输入格式

The first line of input contains $N$ and $M$.

The next $N$ lines describe cows. The ith of these lines contains $s_i, t_i$, and $c_i$.

The next $M$ lines describe air conditioners. The ith of these lines contains $a_i, b_i, p_i$, and $m_i$.

For every input other than the sample, you can assume that $M=10$. 
## 输出格式

Output a single integer telling the minimum amount of money FJ needs to spend to operate enough air conditioners to satisfy all his cows (with the conditions listed above). 
## 样例

### 样例输入 #1
```
2 4
1 5 2
7 9 3
2 9 2 3
1 6 2 8
1 2 4 2
6 9 1 5
```
### 样例输出 #1
```
10
```
## 提示

### Explanation for Sample 1

One possible solution that results in the least amount of money spent is to select those that cool the intervals $[2,9], [1,2]$, and $[6,9]$, for a cost of $3+2+5=10$. 
## 题目翻译

## 题目描述

农夫约翰的 $N$ 头奶牛 $(1≤N≤20)$ 住在一个谷仓里，谷仓里有连续的牛栏，编号为 $1-100$ 。 奶牛 $i$ 占据了编号 $[s_i,t_i]$ 的牛栏。 不同奶牛占据的牛栏范围是互不相交的。 奶牛有不同的冷却要求，奶牛 $i$ 占用的每个牛栏的温度必须至少降低 $c_i$ 单位。

谷仓包含 $M$ 台空调，标记为 $1-M$ $(1\le M\le10)$。第 $i$ 台空调需要花费 $m_i$ 单位的金钱来运行 $(1\le m_i \le 1000)$ ，如果运行，第 $i$ 台空调将牛栏 $[a_i,b_i]$ 所有牛栏的温度降低 $p_i$（$1\le p_i\le10^6）$。 空调覆盖的牛栏范围可能会重叠。

请帮助农夫约翰求出满足所有奶牛需求要花费的最少金钱。

## 输入格式

第一行两个整数，分别为 $N$ 和 $M$。

第 $2$ 至 $(N+1)$ 行，每行三个整数，分别为 $s_i$、$t_i$ 和 $c_i$ 。

第 $(N+2)$ 至 $(M+N+1)$ 行，每行四个整数， 分别为 $a_i$、$b_i$、$p_i$ 和 $m_i$。

## 输出格式

一个整数，表示最少花费的金钱。



## 提示

### 样例解释 1

一种花费最少的可能解决方案是选择那些冷却区间为 $[2,9]$ 、$[1,2]$ 和 $[6,9]$ 的空调，成本为 $ 3+2+5=10$ .

### 数据范围

对于 $100\%$ 的数据，$1 \le N \le 20$， $1 \le M \le 10$, $ 1 \le a_i, b_i, s_i, t_i \le 100$, $1 \le c_i, p_i \le 10^6$， $1 \le m_i \le 1000$。


---

---
title: "[PA 2020] Mieszanie kolorów"
layout: "post"
diff: 普及-
pid: P9094
tag: ['2020', '前缀和', '差分', 'PA（波兰）']
---
# [PA 2020] Mieszanie kolorów
## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 1 [Mieszanie kolorów](https://sio2.mimuw.edu.pl/c/pa-2020-1/p/kol/)**

Byteasar 正准备给栅栏涂漆。他已经准备了 $n$ 罐白色油漆，他把这些油漆排列成一排，从 $1$ 到 $n$ 编号。他想用这些油漆，但他不想把栅栏涂成白色。他委托了调色专家，调色专家有三种颜料：黄色、蓝色和红色。专家进行了 $m$ 次操作，其中第 $i$ 次操作是向编号在 $l_i$ 到 $r_i$ 之间（包括两端）的所有罐子中加入某种颜料。

油漆的最终颜色取决于被添加到其中的颜料。添加的颜料按照下表和图示进行混合。

|        颜料        | 颜色 |
| :----------------: | :--: |
|         无         | 白色 |
|        黄色        | 黄色 |
|        蓝色        | 蓝色 |
|        红色        | 红色 |
|    黄色 + 蓝色     | 绿色 |
|    黄色 + 红色     | 橙色 |
|    蓝色 + 红色     | 紫色 |
| 黄色 + 蓝色 + 红色 | 棕色 |

![](https://cdn.luogu.com.cn/upload/image_hosting/zow92g6w.png)

Byteasar 想要给栅栏涂成一种颜色。思来想去，他选择了绿色，因为绿色代表了你常会在算法竞赛中看到的 Accepted。他想知道现在有多少罐油漆是绿色的，请帮他数数。
## 输入格式

第一行两个整数 $n,m$，分别表示油漆的罐数和专家进行的操作数。

接下来 $m$ 行，每行三个整数 $l_i,r_i,k_i$，表示在第 $i$ 次操作中向编号在 $l_i$ 到 $r_i$ 之间（包括两端）的罐子中加入颜料。加入的颜料是黄色（$k_i=1$），蓝色（$k_i=2$）或红色（$k_i=3$）中的一种。
## 输出格式

输出一行一个整数，表示在所有操作之后绿色油漆的罐数。
## 样例

### 样例输入 #1
```
9 5
2 8 1
4 5 2
6 7 3
5 6 2
1 2 2
```
### 样例输出 #1
```
3
```
## 提示

#### 样例 1 解释

操作结束后，这些油漆分别是蓝色、绿色、黄色、绿色、绿色、棕色、橙色、黄色和白色的。因此，只有三罐油漆是绿色。

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1\le n,m\le 10^6$，$1\le l_i\le r_i\le n$，$1\le k_i\le 3$。


---

