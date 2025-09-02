---
title: "[ROIR 2022] 跳跃机器人 (Day 1)"
layout: "post"
diff: 普及+/提高
pid: P10087
tag: ['动态规划 DP', '数学', '树形数据结构', '线段树', '线性数据结构', '树状数组', '单调队列', '2022', 'Special Judge', '\ufeff基础算法', '动态规划优化', '队列', '其它技巧', 'ROIR（俄罗斯）']
---
# [ROIR 2022] 跳跃机器人 (Day 1)
## 题目背景

翻译自 [ROIR 2022 D1T2](https://neerc.ifmo.ru/school/archive/2021-2022/ru-olymp-regional-2022-day1.pdf)。

某公司正在开发一种跳跃机器人。为了测试机器人，他们在一个多边形平台上设置了一个由 $n$ 个特殊平台组成的环形路线，平台从 $1$ 到 $n$ 编号。第 $i$ 个平台与 $i+1$ 个平台之间的距离为 $d_i$，最后一个平台与第一个平台之间的距离为 $d_n$（假设长度分别为 $d_1,d_2,\dots,d_n$ 的边可以组成一个 $n$ 边形）。

机器人配备了人工智能，在测试过程中学习跳得更远。在任何时刻，机器人通过一个整数 $a$ 来表示它的灵敏度。如果 $a$ 大于等于 $d_i$，机器人可以从平台 $i$ 跳到平台 $i+1$；同样地，如果 $a$ 大于等于 $d_n$，机器人可以从最后一个平台跳到第一个平台。每次跳跃后，机器人的灵敏度增加 $1$。
## 题目描述

机器人的开发人员选择一个平台作为起始平台。如果机器人可以完成 $n$ 次跳跃，回到原来的平台，他们认为实验是成功的。开发人员需要确定机器人的最小起始灵敏度是多少，并选择哪个平台作为起始平台。
## 输入格式

第一行包含一个整数 $n$。

第二行包含一个整数 $f$。

- 如果 $f = 1$，则第三行包含 $n$ 个整数 $d_1, d_2, \dots , d_n$，意义见题目背景。
- 如果 $f = 2$，则第三行包含一个整数 $m$，以及三个整数 $x,y,z$。第四行包含 $m$ 个整数 $c_1, c_2, \dots , c_m$。此时距离值 $d_i$ 根据以下公式计算：
   - 如果 $1 \le i \le m$，则 $d_i = c_i$。
   - 如果 $m + 1 \le i \le n$，则 $d_i = ((x \times d_{i−2} + y \times d_{i−1} + z) \bmod 10^9) + 1$。
## 输出格式

输出两个整数，即最小允许的起始灵敏度 $a$ 和可用于放置机器人的起始平台编号。如果有多个最小起始灵敏度对应的起始平台，可以输出任意一个。
## 样例

### 样例输入 #1
```
5
1
3 7 4 2 5
```
### 样例输出 #1
```
4 3
```
### 样例输入 #2
```
10
2
5 1 2 3
1 2 3 4 5
```
### 样例输出 #2
```
653 1
```
## 提示

样例说明：

在第二个示例中，距离数组为 $[1, 2, 3, 4, 5, 18, 45, 112, 273, 662]$。

根据公式计算 $d_6$ 到 $d_{10}$ 的值：

- $d_6 = ((1 \cdot d_4 + 2 \cdot d_5 + 3) \bmod 10^9) + 1 = ((1 \cdot 4 + 2 \cdot 5 + 3) \bmod 10^9) + 1 = 18$；
- $d_7 = ((1 \cdot d_5 + 2 \cdot d_6 + 3) \bmod 10^9) + 1 = ((1 \cdot 5 + 2 \cdot 18 + 3) \bmod 10^9) + 1 = 45$；
- $d_8 = ((1 \cdot d_6 + 2 \cdot d_7 + 3) \bmod 10^9) + 1 = ((1 \cdot 18 + 2 \cdot 45 + 3) \bmod 10^9) + 1 = 112$；
- $d_9 = ((1 \cdot d_7 + 2 \cdot d_8 + 3) \bmod 10^9) + 1 = ((1 \cdot 45 + 2 \cdot 112 + 3) \bmod 10^9) + 1 = 273$；
- $d_{10} = ((1 \cdot d_8 + 2 \cdot d_9 + 3) \bmod 10^9) + 1 = ((1 \cdot 112 + 2 \cdot 273 + 3) \bmod 10^9) + 1 = 662$。

本题使用捆绑测试。

| 子任务 | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $0$ | $15$ | $n\le300,f=1,d\le300$ |
| $1$ | $17$ | $n\le5000,f=2$ |
| $2$ | $10$ | $n\le100000,f=1$ 且保证从第一个平台开始跳是最佳选择 |
| $3$ | $20$ | $n\le100000,f=1$ |
| $4$ | $5$ | $f=2$ 且保证从第一个平台开始跳是最佳选择 |
| $5$ | $33$ | $f=2$ |

对于 $100\%$ 的数据，$3 \le n \le 10^7$。当 $f=1$ 时 $1 \le d_i \le 10^9$，当 $f=2$ 时 $2 \le m \le \min(n, 10^5)$，$0 \le x, y, z \le 10^9$，$1 \le c_i \le 10^9$。

注：本题的算法标签部分参考了官方题解中用到的解法。


---

---
title: "[yLCPC2024] C. 舞萌基本练习"
layout: "post"
diff: 普及+/提高
pid: P10235
tag: ['二分', '树状数组', '洛谷原创', '洛谷月赛']
---
# [yLCPC2024] C. 舞萌基本练习
## 题目描述

扶苏在游玩舞萌 dx 的过程中，发现一首歌可以分成不超过 $k$ 段分别进行练习。

具体来说，这首歌共有 $n$ 个音符，每个音符有一个难度值。第 $i$ 个音符的难度值为 $a_i$。扶苏觉得一段歌曲的音符的难度应该是尽可能变难的。因此对于音符序列的一个区间 $[l, r]$，她认为这段区间的『不优美度』是这段区间的**逆序对**数。

一个区间 $[l, r]$ 的**逆序对数**被定义为满足 $l \leq i < j \leq r$ 且 $a_i > a_j$ 的数对 $(i, j)$ 个数。

扶苏希望把这首歌划分成不超过 $k$ 个子段，满足每个音符都至少属于一个子段，使得不优美度最大的段的不优美度尽可能小。

形式化的，你需要划分出 $t \leq k$ 个区间 $[l_1, r_1], [l_2, r_2], \dots [l_t, r_t]$，满足：

- $l_1 = 1$，$r_t = n$。
- 对 $1 \leq i < t$，$r_i + 1= l_{i + 1}$。
- 对 $1 \leq i \leq t$，$l_i \leq r_i$。

定义 $f(l, r)$ 表示区间 $[l, r]$ 的不优美度，最小化 $\max\limits_{i = 1}^t f(l_i, r_i)$
## 输入格式

**本题单个测试点内有多组测试数据**。第一行是一个正整数 $T$，表示数据组数。对每组数据：

第一行是两个整数 $n,k$（$1 \leq k \leq n \leq 10^5$），表示歌曲的音符数和最多的划分段数。  
第二行有 $n$ 个整数 $a_1, a_2, \dots, a_n$（$-10^9 \leq a_i \leq 10^9$），表示每个音符的难度。

数据保证单个测试点内的 $n$ 之和不超过 $10^5$。
## 输出格式

对每组数据，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2
5 2
1 3 2 5 4
8 2
4 2 3 6 7 1 8 5
```
### 样例输出 #1
```
1
2
```


---

---
title: "[AHOI2024 初中组] 操作"
layout: "post"
diff: 普及+/提高
pid: P10374
tag: ['模拟', '线段树', '树状数组', '2024', '安徽', 'O2优化', '差分']
---
# [AHOI2024 初中组] 操作
## 题目描述

小可可有一个数组 $\{a_n\}$（初始值为 $\{a_n\}=\{0,0,\ldots,0\}$）和从左到右的 $m$ 个机器，其中第 $i$ 个机器有类别 $o_i \in \{1,2\}$ 和参数 $x_i,y_i$。第 $i$ 个机器执行的操作如下：

- 若 $o_i=1$，则将 $a_{(x_i)}$ 加上 $y_i$，此时保证 $1 \le x_i \le n$，$1 \le y_i \le 10^4$。
- 若 $o_i=2$，则执行第 $x_i \sim y_i$ 个机器的操作各一次，此时保证 $1 \le x_i \le y_i \le i-1$。
- 特别地，保证 $o_1=1$。

现在，小可可依次执行了第 $c_1,c_2,\ldots,c_k$ 个机器的操作各一次，她想知道最后得到的数组 $\{a_n\}$ 是什么。

由于数组中元素的值可能很大，你只需要帮她求出每个元素除以 $10007$ 的余数即可。
## 输入格式

第一行三个正整数 $n,m,k$。

接下来一行 $k$ 个正整数 $\{c_k\}$。

接下来 $m$ 行，第 $i$ 行三个正整数 $o_i,x_i,y_i$。
## 输出格式

一行 $n$ 个非负整数，表示数组 $\{a_n\}$ 中每个元素的值除以 $10007$ 的余数。
## 样例

### 样例输入 #1
```
2 3 3
1 2 3
1 1 2
2 1 1
2 1 2
```
### 样例输出 #1
```
8 0
```
## 提示

### 样例 1 解释

先执行第 $1$ 个机器的操作，给 $a_1$ 加上了 $2$。

然后执行第 $2$ 个机器的操作，它操作了第 $1$ 个机器，给 $a_1$ 加上了 $2$。

然后执行第 $3$ 个机器的操作。它先操作了第 $1$ 个机器，给 $a_1$ 加上了 $2$；然后操作了第 $2$ 个机器，第 $2$ 个机器又操作了第 $1$ 个机器，给 $a_1$ 加上了 $2$。

综上所述，最后得到的数组为 $\{8,0\}$。

### 数据范围


对于 $10\%$ 的数据，$n,m,k \le 10$。

对于 $30\%$ 的数据，$n,m,k \le 1000$。

对于另外 $20\%$ 的数据，$n=1$。

对于另外 $20\%$ 的数据，$k=1$。

对于 $100\%$ 的数据，$1 \le n,m,k \le 2 \times 10^5$，$1 \le c_i \le n$，$o_i \in \{1,2\}$，$o_1=1$。此外，对于第 $i$ 个机器，保证：

- 若 $o_i=1$，则 $1 \le x_i \le n$，$1 \le y_i \le 10^4$。
- 若 $o_i=2$，则 $1 \le x_i \le y_i \le i-1$。


---

---
title: "奇数码问题"
layout: "post"
diff: 普及+/提高
pid: P10454
tag: ['树状数组', '排序']
---
# 奇数码问题
## 题目描述

你一定玩过八数码游戏，它实际上是在一个 $3 \times 3$ 的网格中进行的，$1$ 个空格和 $1 \sim 8$ 这 $8$ 个数字恰好不重不漏地分布在这 $3 \times 3$ 的网格中。

例如：

    5 2 8
    1 3 _
    4 6 7
    

在游戏过程中，可以把空格与其上、下、左、右四个方向之一的数字交换（如果存在）。

例如在上例中，空格可与左、上、下面的数字交换，分别变成：

    5 2 8       5 2 _      5 2 8
    1 _ 3       1 3 8      1 3 7
    4 6 7       4 6 7      4 6 _
    

奇数码游戏是它的一个扩展，在一个 $n \times n$ 的网格中进行，其中 $n$ 为奇数，$1$ 个空格和 $1 \sim n^2-1$ 这 $n^2-1$ 个数恰好不重不漏地分布在 $n \times n$ 的网格中。

空格移动的规则与八数码游戏相同，实际上，八数码就是一个 $n=3$ 的奇数码游戏。

现在给定两个奇数码游戏的局面，请判断是否存在一种移动空格的方式，使得其中一个局面可以变化到另一个局面。
## 输入格式

多组数据，对于每组数据：

第 $1$ 行输入一个整数 $n$，$n$ 为奇数。

接下来 $n$ 行每行 $n$ 个整数，表示第一个局面。

再接下来 $n$ 行每行 $n$ 个整数，表示第二个局面。

局面中每个整数都是 $0 \sim n^2-1$ 之一，其中用 $0$ 代表空格，其余数值与奇数码游戏中的意义相同，保证这些整数的分布不重不漏。
## 输出格式

对于每组数据，若两个局面可达，输出 `TAK`，否则输出 `NIE`。

## 样例

### 样例输入 #1
```
3
1 2 3
0 4 6
7 5 8
1 2 3
4 5 6
7 8 0
1
0
0
```
### 样例输出 #1
```
TAK
TAK
```
## 提示

$1 \le n < 500$


---

---
title: "【MX-S1-T2】催化剂"
layout: "post"
diff: 普及+/提高
pid: P10673
tag: ['数学', '贪心', '线段树', '树状数组', 'O2优化', '梦熊比赛']
---
# 【MX-S1-T2】催化剂
## 题目背景

原题链接：<https://oier.team/problems/S1B>。
## 题目描述

小朋友们很喜欢糖果。

现在，小 K 有一些糖果，每个糖果上有一个数字代表它的种类。

有 $q$ 次事件，每次事件会加入一个糖果、或删除一个糖果、或提出一次询问。

每次询问会给出一个 $k$，表示小 K 现在需要将所有糖果分给 $k$ 个小朋友，并且每个小朋友都需要得到至少一个糖果。同时，小朋友们不喜欢得到相同的糖果。具体的，在一个小朋友得到了糖果 $i$ 时，如果 Ta 在这个糖果之前就已经获得过糖果 $i$，那么 Ta 就会感到非常生气，Ta 的愤怒值就会增加 $1$。

小 K 不喜欢看到小朋友们生气，但小 K 无法解决这么困难的问题，所以你需要帮小 K 求出一种分糖果的方式，最小化所有小朋友的愤怒值之和。

保证存在一种分糖果的方案，使得每个小朋友都分到至少一个糖果。

每次询问并没有真正的分糖果，即每次询问后小 K 拥有的糖果不会改变。

注意，分糖果的过程可以理解为将小 K 拥有的所有糖果划分到 $k$ 个非空序列，可以重排。
## 输入格式

第一行两个正整数 $n,q$。

第二行 $n$ 个正整数 $a_1,a_2,\dots,a_n$，描述初始时小 K 拥有的糖果。

接下来 $q$ 行，每行两个正整数，描述一次操作，共有三种可能的输入：

`1 x`：表示小 K 又拥有了一个种类为 $x$ 的糖果。

`2 x`：表示小 K 丢失了一个种类为 $x$ 的糖果，保证此时小 K 拥有至少一个种类为 $x$ 的糖果。

`3 k`：表示此时小 K 需要把糖果分给 $k$ 个小朋友，你需要求出最小的所有小朋友的愤怒值之和。令 $S$ 表示此时小 K 拥有的糖果数量，保证 $1\le k\le S$。
## 输出格式

对于每次询问，输出一行一个整数，表示你求出的答案。
## 样例

### 样例输入 #1
```
5 4
3 5 2 5 5
3 2
2 5
1 5
3 1
```
### 样例输出 #1
```
1
2
```
### 样例输入 #2
```
5 15
2 5 2 5 1
2 1
1 1
1 2
1 4
1 1
3 2
1 1
3 1
1 5
3 1
1 2
3 1
2 1
3 3
2 2

```
### 样例输出 #2
```
1
5
6
7
1

```
## 提示

__【样例解释 1】__

第一次询问时，小 K 手上的糖果为 $\{3,5,2,5,5\}$，分给 $2$ 个小朋友的糖果为 $\{2,3,5\},\{5,5\}$，小朋友的愤怒值为 $0,1$。可以证明没有愤怒值之和更小的方案。

__【数据范围】__

__本题使用子任务捆绑测试。__

对于 $100\%$ 的数据，$1\le n,q\le 10^6$，$1\le a_i,x\le n$。每次询问时，令 $S$ 表示此时小 K 拥有的糖果数量，保证 $1\le k\le S$。

| 子任务编号 | $n\le $ | $q\le $ | 特殊性质      | 分值 |
| ---------- | ------- | ------- | ------------- | ---- |
| $1$        | $5$     | $15$    | 无            | $20$ |
| $2$        | $2000$  | $2000$  | 无            | $20$ |
| $3$        | $10^5$  | $10^5$  | 无            | $20$ |
| $4$        | $10^6$  | $10^6$  | $a_i,x\le 50$ | $10$ |
| $5$        | $10^6$  | $10^6$  | $k\le 50$     | $10$ |
| $6$        | $10^6$  | $10^6$  | 无            | $20$ |



---

---
title: "【模板】离线二维数点"
layout: "post"
diff: 普及+/提高
pid: P10814
tag: ['树状数组', '扫描线', '离线处理']
---
# 【模板】离线二维数点
## 题目背景

青蛙。
## 题目描述

给你一个长为 $n$ 的序列 $a$，有 $m$ 次询问，每次询问给定 $l,r,x$，求 $[l,r]$ 区间中小于等于 $x$ 的元素个数。
## 输入格式

第一行两个数 $n,m$。

第二行 $n$ 个数表示序列 $a$。

之后 $m$ 行，每行三个数 $l,r,x$ 表示一次询问。
## 输出格式

对每个询问，输出一行一个数表示答案。
## 样例

### 样例输入 #1
```
6 4
1 1 4 5 1 4
1 6 3
1 6 4
1 1 4
1 5 4
```
### 样例输出 #1
```
3
5
1
4
```
## 提示

对于 $20\%$ 的数据，满足 $1\le n,m,a_i,l,r,x\le 100$。

对于 $40\%$ 的数据，满足 $1\le n,m,a_i,l,r,x\le 10^4$。

对于 $60\%$ 的数据，满足 $1\le n,m,a_i,l,r,x\le 10^5$。

对于 $80\%$ 的数据，满足 $1\le n,m,a_i,l,r,x\le 10^6$。

对于 $100\%$ 的数据，满足 $1\le n,m,a_i,l,r,x\le 2\times10^6$。


---

---
title: "「ALFR Round 4」B 颜料"
layout: "post"
diff: 普及+/提高
pid: P11012
tag: ['树状数组', 'O2优化', '双指针 two-pointer']
---
# 「ALFR Round 4」B 颜料
## 题目背景

在小山的观念里，画展因色彩不同而绚丽。
## 题目描述

小山一共有 $n$ 副画作，每副画作都有其主要的颜料。具体的，第 $i$ 副画作的主要颜料的种类为 $a_i$。小山可以选择一段**编号连续**的画作组成一个画展，而画展的绚丽程度为（设该画展由第 $l$ 到第 $r$ 副画组成）：$\sum_{i=1}^W\sum_{j=i+1}^W\min(c_i,c_j)$，其中 $c_i$ 表示种类为 $i$ 的颜料在画展中出现的次数，$W$ 为所有颜料种类的值域。

现在小山想知道，若要画展的绚丽程度至少为 $k$，应至少选出多少副连续的画作？若无绚丽程度至少为 $k$ 的画展，则答案为 $-1$。
## 输入格式

共两行，第一行两个整数 $n,k$，含义见**题目描述**。

第二行 $n$ 个整数，第 $i$ 个数为 $a_i$，表示第 $i$ 副画的主要颜料的种类。
## 输出格式

一行一个整数表示答案。
## 样例

### 样例输入 #1
```
10 6
2 3 4 3 3 4 2 4 9 2
```
### 样例输出 #1
```
5
```
## 提示

### 样例解释

选择第 $5$ 至第 $9$ 副画作组成画展，则 $c_1=0,c_2=1,c_3=1,c_4=2,c_5=0,c_6=0,c_7=0,c_8=0,c_9=1,\sum_{i=1}^9\sum_{j=i+1}^9\min(c_i,c_j)=6$。容易得知 $5$ 是符合要求的区间的最短长度。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | 所有的 $a_i(1\le i\le n)$ 都相同 |
| $1$ | $20$ | $n,a_i\le10^2$ |
| $2$ | $70$ | - |

对于 $100\%$ 的数据，$1\le n,a_i\le2\times10^6$，$1\le k\le 10^{15}$。


---

---
title: "[蓝桥杯 2024 省 Java B] 拼十字"
layout: "post"
diff: 普及+/提高
pid: P11048
tag: ['树形数据结构', '树状数组', '2024', '蓝桥杯省赛']
---
# [蓝桥杯 2024 省 Java B] 拼十字
## 题目背景

备注：原题（Java）时间限制 3.0s，空间限制 512 MB。
## 题目描述

在 LQ 国神秘的古老森林，有一座被称为 “拼十字” 的神秘遗迹。据传， “拼十字” 是由古代文明建造的，它是一个巨大的石头结构，由两个巨大的矩形交叉叠放在一起，形成了一个庄严而神秘的十字形状。这个遗迹被认为是连接人类和神灵之间的通道，拥有神秘的力量和能量。

![](https://cdn.luogu.com.cn/upload/image_hosting/qn9sqnae.png)

现在给出 $N$ 个矩形，其中第 $i$ 个矩形的长度和宽度分别为 $l_i$，$w_i$，并且矩形的颜色 $c_i$ 为红 $(0)$、黄 $(1)$、蓝 $(2)$ 中的一种。现在小蓝想知道在这 $N$ 个矩形中有多少对可以“拼十字”？

两个矩形可以“拼十字”的充要条件是：

1. 两个矩形的颜色不同；
2. 矩形 $1$ 的长度严格大于矩形 $2$ 的长度并且矩形 $1$ 的宽度严格小于矩形 $2$ 的宽度。

注意，矩形长度和宽度属性是固定的，是不可以通过旋转矩形而发生转变的。
## 输入格式

第一行一个整数 $N$，表示有 $N$ 个矩形。

接下来 $N$ 行，每行输入三个整数 $l$、$w$、$c$ 表示一个矩形的长、宽和颜色。
## 输出格式

输出一个整数表示答案。由于答案可能会很大，所以你需要将答案对 $10^9 + 7$ 取模之后输出。
## 样例

### 样例输入 #1
```
5
1 10 0
6 6 0
8 6 1
6 10 0
1 2 1
```
### 样例输出 #1
```
2
```
## 提示

【样例解释】

第 $3$ 个矩形可以和第 $1$ 个矩形拼十字，第 $3$ 个矩形也可以和第 $4$ 个矩形拼十字。所以一共有两对矩形可以拼十字，答案为 $2$。

【数据范围】

- 对于 $30\%$ 的评测用例：$1 \leq N \leq 5000$。
- 对于 $100 \%$ 的评测用例：$1 \leq N \leq 10^5$，$1 \leq l,w \leq 10^5$，$0 \leq c \leq 2$。


---

---
title: "中位数"
layout: "post"
diff: 普及+/提高
pid: P1168
tag: ['线段树', '二分', '堆', '树状数组']
---
# 中位数
## 题目描述

给定一个长度为 $N$ 的非负整数序列 $A$，对于前奇数项求中位数。
## 输入格式

第一行一个正整数 $N$。

第二行 $N$ 个正整数 $A_{1\dots N}$。
## 输出格式

共 $\lfloor \frac{N + 1}2\rfloor$ 行，第 $i$ 行为 $A_{1\dots 2i - 1}$ 的中位数。

## 样例

### 样例输入 #1
```
7
1 3 5 7 9 11 6
```
### 样例输出 #1
```
1
3
5
6
```
### 样例输入 #2
```
7
3 1 5 9 8 7 6
```
### 样例输出 #2
```
3
3
5
6
```
## 提示

对于 $20\%$ 的数据，$N \le 100$；

对于 $40\%$ 的数据，$N \le 3000$；

对于 $100\%$ 的数据，$1 \le N ≤ 100000$，$0 \le A_i \le 10^9$。



---

---
title: "[NOISG 2025 Finals] Thumper"
layout: "post"
diff: 普及+/提高
pid: P12016
tag: ['树状数组', '2025', 'NOISG（新加坡）']
---
# [NOISG 2025 Finals] Thumper
## 题目描述

Bunnyland has large fields where the Bunnyland Dwarf (a native species of rabbit) roams freely. One such field can be modelled as a $10^9 \times 10^9$ grid of cells. The rows of the grid are numbered $1$ to $10^9$ from north to south, and the columns of the grid are numbered $1$ to $10^9$ from west to east. We refer to the cell located at row $r$ and column $c$ of the grid as cell $(r, c)$.

In this field, there are $n$ rabbits numbered from $1$ to $n$. The $i$-th rabbit is initially located at cell $(r[i], c[i])$. **No two rabbits are initially located at the same cell**.

Rabbits lift their hind legs and kick the ground when annoyed, an action known as thumping. These $n$ rabbits will execute a sequence of $m$ thumps. At the start of the $j$-th second, rabbit $t[j]$ will thump. When a rabbit thumps, all other rabbits will move away from the thumping rabbit.

![](https://cdn.luogu.com.cn/upload/image_hosting/1auwto2s.png)

To be precise, when rabbit A thumps, rabbit B will move as follows:

- If the number of rows between A and B is less than the number of columns between A and B, B will move two columns away from A.
- If the number of rows between A and B is equal to the number of columns between A and B, B will move one column and one row away from A.
- If the number of rows between A and B is more than the number of columns between A and B, B will move two rows away from A.

It can be shown that the location of the rabbits will remain distinct after a thump has occurred.

Benson the Rabbit has come to find his brethren after his retirement from investigating toxic bacteria, but all the thumping has caused the rabbits to scatter. Help Benson determine the final locations of the $n$ rabbits after all thumps have occurred!

It is guaranteed that a rabbit will never leave the grid during the sequence of thumps. You may also assume that rabbits do not move in any other circumstances except thumping.

## 输入格式

Your program must read from standard input.

The first line of input contains two space-separated integers $n$ and $m$.

The following $n$ lines of input each contain two space-separated integers. The $i$-th of these lines contains $r[i]$ and $c[i]$.

The last line of input contains $m$ space-separated integers $t[1], t[2], \ldots, t[m]$.

## 输出格式

Your program must print to standard output.

The output should contain $n$ lines. The $i$-th of these lines should contain two space-separated integers, indicating the row and the column of rabbit $i$ after all thumps have occurred.

## 样例

### 样例输入 #1
```
2 1
1 1
2 2
1
```
### 样例输出 #1
```
1 1
3 3
```
### 样例输入 #2
```
13 1
7 7
3 7
4 4
4 10
5 6
6 4
6 8
8 7
8 10
9 3
9 5
9 9
10 6
1
```
### 样例输出 #2
```
7 7
1 7
3 3
3 11
3 6
6 2
5 9
10 7
8 12
9 1
10 4
10 10
12 6
```
### 样例输入 #3
```
3 2
1 10
1 20
1 30
1 3
```
### 样例输出 #3
```
1 8
1 20
1 32
```
## 提示

### Subtasks

For all test cases, the input will satisfy the following bounds:

- $1 \leq n, m \leq 500\,000$
- $1 \leq r[i], c[i] \leq 10^9$ for all $1 \leq i \leq n$
- $1 \leq t[j] \leq n$ for all $1 \leq j \leq m$
- $(r_i, c_i) \neq (r_j, c_j)$ for all $i \neq j$
- It is guaranteed that a rabbit will never exit the grid during the sequence of thumps.

Your program will be tested on input instances that satisfy the following restrictions:

| Subtask | Marks | Additional constraints |
| :-: | :-: | :-: |
| $0$ | $0$ | Sample test cases |
| $1$ | $18$ | $n, m \leq 2000$ |
| $2$ | $21$ | $r[i] = 1$ |
| $3$ | $32$ | $n \leq 2000$ |
| $4$ | $13$ | $n \leq 100\,000$ |
| $5$ | $16$ | No additional constraints |

### Sample Test Case 1 Explanation

This test case is valid for subtasks $1, 3, 4$, and $5$.

Rabbit $1$ is at cell $(1, 1)$ and rabbit $2$ is at cell $(2, 2)$.

Since the number of rows between rabbit $1$ and rabbit $2$ is equal to the number of columns between rabbit $1$ and rabbit $2$, when rabbit $1$ thumps, rabbit $2$ will move one column and one row away from rabbit $1$ in the southeast direction, landing at cell $(3, 3)$. The position of the thumping rabbit $1$ does not change.

### Sample Test Case 2 Explanation

This test case is valid for subtasks $1, 3, 4$, and $5$.

The diagram in the statement corresponds to this test case. The blue arrows show how the other rabbits move when rabbit $1$ at cell $(7, 7)$ thumps.

### Sample Test Case 3 Explanation

This test case is valid for all subtasks.



---

---
title: "[蓝桥杯 2023 省 Python B] 异或和"
layout: "post"
diff: 普及+/提高
pid: P12385
tag: ['树状数组', '2023', '蓝桥杯省赛']
---
# [蓝桥杯 2023 省 Python B] 异或和
## 题目描述

给一棵含有 $n$ 个结点的有根树，根结点为 $1$，编号为 $i$ 的点有点权 $a_i$ $(i \in [1, n])$。现在有两种操作，格式如下：

- $1\ x\ y$ 该操作表示将点 $x$ 的点权改为 $y$。
- $2\ x$ 该操作表示查询以结点 $x$ 为根的子树内的所有点的点权的异或和。

现有长度为 $m$ 的操作序列，请对于每个第二类操作给出正确的结果。
## 输入格式

输入的第一行包含两个正整数 $n, m$，用一个空格分隔。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$，相邻整数之间使用一个空格分隔。

接下来 $n-1$ 行，每行包含两个正整数 $u_i, v_i$，表示结点 $u_i$ 和 $v_i$ 之间有一条边。

接下来 $m$ 行，每行包含一个操作。
## 输出格式

输出若干行，每行对应一个查询操作的答案。
## 样例

### 样例输入 #1
```
4 4
1 2 3 4
1 2
1 3
2 4
2 1
1 1 0
2 1
2 2
```
### 样例输出 #1
```
4
5
6
```
## 提示

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$n, m \leq 1000$；
- 对于所有评测用例，$1 \leq n, m \leq 100000$，$0 \leq a_i, y \leq 100000$，$1 \leq u_i, v_i, x \leq n$。


---

---
title: "[UOI 2023] An Array and Medians of Subarrays"
layout: "post"
diff: 普及+/提高
pid: P12570
tag: ['线段树', '二分', '堆', '树状数组', '2023', 'UOI（乌克兰）']
---
# [UOI 2023] An Array and Medians of Subarrays
## 题目描述

Let's call the median of an array of length $(2 \cdot k + 1)$ the number that appears in position $(k + 1)$ after sorting its elements in non-decreasing order. For example, the medians of the arrays $[1]$, $[4,2,5]$, and $[6,5,1,2,3]$ are $1$, $4$, and $3$, respectively.

You are given an array of integers $a$ of **even** length $n$.

Determine whether it is possible to split $a$ into several subarrays of **odd** length such that all the medians of these subarrays are pairwise equal.

Formally, you need to determine whether there exists a sequence of integers $i_1, i_2, \ldots, i_k$ such that the following conditions are satisfied:

- $1 = i_1 < i_2 < \ldots < i_k = (n + 1)$;
- $(i_2 - i_1) \bmod 2 = (i_3 - i_2) \bmod 2 = \ldots = (i_k - i_{k - 1}) \bmod 2 = 1$;
- $f(a[i_1..(i_2-1)]) = f(a[i_2..(i_3-1)]) = \ldots = f(a[i_{k - 1}..(i_k - 1)])$, where $a[l..r]$ denotes the subarray consisting of elements $a_l, a_{l + 1}, \ldots, a_r$, and $f(a)$ denotes the median of the array $a$.
## 输入格式

The first line contains a single even integer $n$ ($2 \le n \le 2 \cdot 10^5$) --- the length of the array.

The second line contains $n$ integers $a_1,a_2,\ldots,a_n$ ($1\le a_i\le 10^9)$ --- the elements of the array.

It is guaranteed that $n$ is even.
## 输出格式

Output $\tt{Yes}$ if it is possible to divide $a$ into several subarrays of odd length in such a way that all medians of these subarrays are pairwise equal, and $\tt{No}$ otherwise.
## 样例

### 样例输入 #1
```
4
1 1 1 1
```
### 样例输出 #1
```
Yes
```
### 样例输入 #2
```
6
1 2 3 3 2 1
```
### 样例输出 #2
```
Yes
```
### 样例输入 #3
```
6
1 2 1 3 2 3
```
### 样例输出 #3
```
No
```
## 提示

In the first example, the array $[1,1,1,1]$ can be divided into the arrays $[1]$ and $[1,1,1]$ with medians equal to $1$.

In the second example, the array $[1,2,3,3,2,1]$ can be divided into the arrays $[1,2,3]$ and $[3,2,1]$ with medians equal to $2$.

In the third example, the array $[1,2,1,3,2,3]$ cannot be divided into several arrays of odd length with the same median values.

### Scoring

- ($3$ points): $n=2$;
- ($14$ points): $1 \le a_i \le 2$ for $1\le i\le n$;
- ($12$ points): $a_i \le a_{i+1}$ for $1\le i < n$;
- ($16$ points): $1 \le a_i \le 3$ for $1 \le i \le n$; each value occurs in $a$ no more than $n \over 2$ times;
- ($17$ points): $n \le 100$;
- ($18$ points): $n \le 2000$;
- ($20$ points): no additional restrictions.


---

---
title: "[蓝桥杯 2025 国 Java B] 道具摆放"
layout: "post"
diff: 普及+/提高
pid: P12890
tag: ['树状数组', '2025', '分治', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 Java B] 道具摆放
## 题目描述

小蓝是社区剧团的道具员，他负责管理一排编号为 $1$ 到 $N$ 的道具箱。平常，这些道具箱会按编号升序排列在舞台上。

今天晚上有一场重要的演出，演出开始前，导演小李递给小蓝一份清单，上面写着他想要的道具箱排列顺序：$P_1, P_2, \ldots, P_N$。导演希望小蓝在演出过程中将这排箱子调整成这个顺序。由于舞台空间狭小，每次调整只能交换相邻两个箱子的位置。且每完成一次交换，舞台灯光就会闪烁一次作为提示。

灯光系统有个特别的节奏设定：每进行 $M$ 次闪烁，灯光就会切换一种模式。为了配合这种节奏，导演强调：必须在某次灯光切换模式的那一瞬间完成所有调整工作。这意味着，小蓝完成调整所需的交换次数必须是 $M$ 的整数倍。

现在，请你帮小蓝计算一下，他最少需要多少次交换操作才能按照导演的要求完成调整。如果无论如何都无法满足要求，则输出 $-1$。

## 输入格式

第一行包含两个整数 $N$ 和 $M$，分别表示道具箱的数量和灯光模式切换的周期。

第二行包含 $N$ 个整数 $P_1, P_2, \ldots, P_N$，表示导演想要的道具箱排列顺序。
## 输出格式

输出一个整数，表示最少需要的操作次数。如果无法满足导演的要求，则输出 $-1$。
## 样例

### 样例输入 #1
```
3 2
3 1 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 3
1 2 3
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
3 2
1 3 2
```
### 样例输出 #3
```
-1
```
## 提示

**【评测用例规模与约定】**

对于 $50\%$ 的评测用例，$1 \leq N, M \leq 10^2$，$1 \leq P_i \leq N$，$P_1, P_2, \ldots, P_N$ 互不相同。

对于 $100\%$ 的评测用例，$1 \leq N \leq 10^5$，$1 \leq M \leq 10^9$，$1 \leq P_i \leq N$，$P_1, P_2, \ldots, P_N$ 互不相同。



---

---
title: "[蓝桥杯 2025 国 Java B] 智能交通信号灯"
layout: "post"
diff: 普及+/提高
pid: P12894
tag: ['树状数组', '2025', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 Java B] 智能交通信号灯
## 题目描述

蓝桥智慧城市在一条主干道上沿路安装了 $N$ 个智能交通信号灯，这些信号灯按位置从 $1$ 到 $N$ 编号。每个信号灯都有着一种控制模式，对于第 $i$ 个信号灯，其控制模式用 $A_i$ 表示，$A_i$ 是一个大于等于 $1$ 的整数。

为了评估信号灯配置的 “多样性”，交通管理专家提出了一种度量方式：对于任意两个不同位置 $x$ 和 $y$，它们的多样性分数被定义为大于等于 $1$ 的整数中，第一个既不是 $A_x$ 也不是 $A_y$ 的数值，记作 $\text{mex}(A_x, A_y)$。例如，当 $A_x = 1$ 且 $A_y = 2$ 时，$\text{mex}(1, 2) = 3$；当 $A_x = 1$ 且 $A_y = 3$ 时，$\text{mex}(1, 3) = 2$；当 $A_x = 2$ 且 $A_y = 2$ 时，$\text{mex}(2, 2) = 1$。

政府希望通过分析和调整信号灯配置，提升道路通行效率。为此，他们计划执行 $M$ 条操作指令，每条指令为以下两类之一：

- $1\ l\ r$：查询操作。计算所有满足 $l \leq i < j \leq r$ 的信号灯对 $(A_i, A_j)$，其多样性分数 $\text{mex}(A_i, A_j)$ 的总和。
- $2\ k\ x$：调整操作。将第 $k$ 个信号灯的控制模式 $A_k$ 修改为新的值 $x$。

现在，请你协助政府依次处理这 $M$ 次操作，并输出每个查询操作的结果。
## 输入格式

第一行包含两个整数 $N$ 和 $M$，分别表示信号灯的数量和操作指令的数量。

第二行包含 $N$ 个整数 $A_1, A_2, \ldots, A_N$，表示初始的信号灯控制模式。

接下来 $M$ 行，每行描述一条操作指令，格式如上所述。

## 输出格式

对于每个查询操作，输出一行包含一个整数，表示多样性分数的总和。
## 样例

### 样例输入 #1
```
5 3
1 2 3 4 5
1 1 5
2 1 2
1 1 5
```
### 样例输出 #1
```
15
10
```
## 提示

**【样例说明】**

初始时信号灯的控制模式依次为：$1, 2, 3, 4, 5$。第一次查询区间 $[1, 5]$，$\text{mex}$ 值分别为 $3, 2, 2, 2, 1, 1, 1, 1, 1, 1$，总和为 $15$。

第二次操作后，信号灯的控制模式依次为：$2, 2, 3, 4, 5$。第二次查询区间 $[1, 5]$，$\text{mex}$ 值均为 $1$，总和为 $10$。

**【评测用例规模与约定】**

对于 $10\%$ 的评测用例，$2 \leq N, M \leq 100$，$1 \leq l < r \leq N$，$1 \leq k \leq N$，$1 \leq A_i, x \leq 10^3$。

对于 $40\%$ 的评测用例，$2 \leq N, M \leq 10^3$，$1 \leq l < r \leq N$，$1 \leq k \leq N$，$1 \leq A_i, x \leq 10^5$。

对于 $100\%$ 的评测用例，$2 \leq N, M \leq 10^5$，$1 \leq l < r \leq N$，$1 \leq k \leq N$，$1 \leq A_i, x \leq 10^9$。



---

---
title: "[GCJ Farewell Round #3] Evolutionary Algorithms"
layout: "post"
diff: 普及+/提高
pid: P12958
tag: ['树状数组', '2023', 'Google Code Jam']
---
# [GCJ Farewell Round #3] Evolutionary Algorithms
## 题目描述

Ada is working on a science project for school. She is studying evolution and she would like to compare how different species of organisms would perform when trying to solve a coding competition problem.

The $\mathbf{N}$ species are numbered with integers between 1 and $\mathbf{N}$, inclusive. Species 1 has no direct ancestor, and all other species have exactly one direct ancestor each, from which they directly evolved. A (not necessarily direct) ancestor of species $x$ is any other species $y$ such that $y$ can be reached from $x$ by moving one or more times to a species direct ancestor starting from $x$. In this way, species 1 is a (direct or indirect) ancestor of every other species.

Through complex genetic simulations, she calculated the average score each of the $\mathbf{N}$ species would get in a particular coding competition. $\mathbf{S}_i$ is that average score for species $i$.

Ada is looking for interesting triplets to showcase in her presentation. An interesting triplet is defined as an ordered triplet of distinct species $(a, b, c)$ such that:

1. Species $b$ is a (direct or indirect) ancestor of species $a$.
2. Species $b$ is not a (direct or indirect) ancestor of species $c$.
3. Species $b$ has an average score strictly more than $\mathbf{K}$ times higher than both of those of $a$ and $c$. That is, $\mathbf{S}_b \geq \mathbf{K} \times \max(\mathbf{S}_a, \mathbf{S}_c) + 1$.

Given the species scores and ancestry relationships, help Ada by writing a program to count the total number of interesting triplets.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow.

The first line of each test case contains two integers $\mathbf{N}$ and $\mathbf{K}$, denoting the number of species and the factor which determines interesting triplets, respectively.

The second line of each test case contains $\mathbf{N}$ integers $\mathbf{S}_1, \mathbf{S}_2, \ldots, \mathbf{S}_\mathbf{N}$, where $\mathbf{S}_i$ denotes the average score of species $i$.

The third line of each test case contains $\mathbf{N} - 1$ integers $\mathbf{P}_2, \mathbf{P}_3, \ldots, \mathbf{P}_\mathbf{N}$, meaning species $\mathbf{P}_i$ is the direct ancestor of species $i$.
## 输出格式

For each test case, output one line containing `case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the total number of interesting triplets according to Ada's definition.
## 样例

### 样例输入 #1
```
2
5 2
3 3 6 2 2
3 1 1 3
7 3
2 4 7 2 2 1 8
6 1 7 3 1 3
```
### 样例输出 #1
```
Case #1: 1
Case #2: 7
```
## 提示

**Sample Explanation**

![](https://cdn.luogu.com.cn/upload/image_hosting/4o5vn91i.png)

In Sample Case #1, there is only one possible interesting triplet: $(5, 3, 4)$. Indeed, we can verify that:

1. Species $b = 3$ is an ancestor of species $a = 5$.
2. Species $b = 3$ is not an ancestor of species $c = 4$.
3. The score of species $b = 3$ is more than $\mathbf{K}$ times higher than the scores of both $a = 5$ and $c = 4$: $6 = \mathbf{S}_3 \geq \mathbf{K} \times \max(\mathbf{S}_4, \mathbf{S}_5) + 1 = 2 \times \max(2, 2) + 1 = 5$.

![](https://cdn.luogu.com.cn/upload/image_hosting/vi8pvu68.png)

In Sample Case #2, there are seven interesting triplets:

* $(4, 3, 1)$
* $(4, 3, 6)$
* $(4, 7, 1)$
* $(4, 7, 5)$
* $(4, 7, 6)$
* $(5, 3, 1)$
* $(5, 3, 6)$

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{K} \leq 10^9$.
- $1 \leq \mathbf{S}_i \leq 10^9$, for all $i$.
- $1 \leq \mathbf{P}_i \leq \mathbf{N}$, for all $i$.
- Species 1 is a (direct or indirect) ancestor of all other species.

**Test Set 1 (7 Pts, Visible Verdict)**

- $3 \leq \mathbf{N} \leq 1000$.

**Test Set 2 (16 Pts, Hidden Verdict)**

For at most 30 cases:

- $3 \leq \mathbf{N} \leq 2 \times 10^5$.

For the remaining cases:

- $3 \leq \mathbf{N} \leq 1000$.


---

---
title: "[GCJ 2008 #1C] Increasing Speed Limits"
layout: "post"
diff: 普及+/提高
pid: P13465
tag: ['动态规划 DP', '2008', '树状数组', 'Google Code Jam']
---
# [GCJ 2008 #1C] Increasing Speed Limits
## 题目描述

You were driving along a highway when you got caught by the road police for speeding. It turns out that they've been following you, and they were amazed by the fact that you were accelerating the whole time without using the brakes! And now you desperately need an excuse to explain that.

You've decided that it would be reasonable to say "all the speed limit signs I saw were in increasing order, that's why I've been accelerating". The police officer laughs in reply, and tells you all the signs that are placed along the segment of highway you drove, and says that's unlikely that you were so lucky just to see some part of these signs that were in increasing order.

Now you need to estimate that likelihood, or, in other words, find out how many different subsequences of the given sequence are strictly increasing. The empty subsequence does not count since that would imply you didn't look at any speed limits signs at all!

For example, $(1, 2, 5)$ is an increasing subsequence of $(1, 4, 2, 3, 5, 5)$, and we count it twice because there are two ways to select $(1, 2, 5)$ from the list.
## 输入格式

The first line of input gives the number of cases, $N$. $N$ test cases follow. The first line of each case contains $n$, $m$, $X$, $Y$ and $Z$ each separated by a space. $n$ will be the length of the sequence of speed limits. $m$ will be the length of the generating array $A$. The next $m$ lines will contain the $m$ elements of $A$, one integer per line (from $A[0]$ to $A[m-1]$).

Using $A$, $X$, $Y$ and $Z$, the following pseudocode will print the speed limit sequence in order. mod indicates the remainder operation.

```
for i = 0 to n-1
  print A[i mod m]
  A[i mod m] = (X * A[i mod m] + Y * (i + 1)) mod Z
```

Note: The way that the input is generated has nothing to do with the intended solution and exists solely to keep the size of the input files low.
## 输出格式

For each test case you should output one line containing "Case #$T$: $S$" (quotes for clarity) where $T$ is the number of the test case and $S$ is the number of non-empty increasing subsequences mod $1\ 000\ 000\ 007$.

## 样例

### 样例输入 #1
```
2
5 5 0 0 5
1
2
1
2
3
6 2 2 1000000000 6
1
2
```
### 样例输出 #1
```
Case #1: 15
Case #2: 13
```
## 提示

**Sample Explanation**

The sequence of speed limit signs for case $2$ should be $1, 2, 0, 0, 0, 4$.

**Limits**

- $1 \leq N \leq 20$
- $1 \leq m \leq 100$
- $0 \leq X \leq 10^9$
- $0 \leq Y \leq 10^9$
- $1 \leq Z \leq 10^9$
- $0 \leq A[i] < Z$

**Small dataset (15 Pts, Test set 1 - Visible)**

- $1 \leq m \leq n \leq 1000$

**Large dataset (35 Pts, Test set 2 - Hidden)**

- $1 \leq m \leq n \leq 500000$


---

---
title: "[GCJ 2008 Finals] Juice"
layout: "post"
diff: 普及+/提高
pid: P13486
tag: ['2008', '堆', '树状数组', '枚举', '排序', 'STL', 'Google Code Jam']
---
# [GCJ 2008 Finals] Juice
## 题目描述

You are holding a party. In preparation, you are making a drink by mixing together three different types of fruit juice: Apple, Banana, and Carrot. Let's name the juices $A$, $B$ and $C$.

You want to decide what fraction of the drink should be made from each type of juice, in such a way that the maximum possible number of people attending the party like it.

Each person has a minimum fraction of each of the $3$ juices they would like to have in the drink. They will only like the drink if the fraction of each of the $3$ juices in the drink is greater or equal to their minimum fraction for that juice.

Determine the maximum number of people that you can satisfy.
## 输入格式

* One line containing an integer $T$, the number of test cases in the input file.

For each test case, there will be:

* One line containing the integer $N$, the number of people going to the party.
* $N$ lines, one for each person, each containing three space-separated numbers "$A$ $B$ $C$", indicating the minimum fraction of each juice that would like in the drink. $A$, $B$ and $C$ are integers between $0$ and $10000$ inclusive, indicating the fraction in parts-per-ten-thousand. $A + B + C \leq 10000$.

## 输出格式

* $T$ lines, one for each test case in the order they occur in the input file, each containing the string "Case #$X$: $Y$" where $X$ is the number of the test case, starting from $1$, and $Y$ is the maximum number of people who will like your drink.
## 样例

### 样例输入 #1
```
3
3
10000 0 0
0 10000 0
0 0 10000
3
5000 0 0
0 2000 0
0 0 4000
5
0 1250 0
3000 0 3000
1000 1000 1000
2000 1000 2000
1000 3000 2000
```
### 样例输出 #1
```
Case #1: 1
Case #2: 2
Case #3: 5
```
## 提示

**Limits**

In the first case, for each juice, we have one person that wants the drink to be made entirely out of that juice! Clearly we can only satisfy one of them.

In the second case, we can satisfy any two of the three preferences.

In the third case, all five people will like the drink if we make it using equal thirds of each juice.

**Limits**

- $1 \leq T \leq 12$

**Small dataset (Test set 1 - Visible)**

- $1 \leq N \leq 10$

**Large dataset (Test set 2 - Hidden)**

- $1 \leq N \leq 5000$


---

---
title: "[KOI 2025 #2] 存放箱子"
layout: "post"
diff: 普及+/提高
pid: P13520
tag: ['线段树', '树状数组', '2025', '离散化', 'Dilworth 定理', 'KOI（韩国）']
---
# [KOI 2025 #2] 存放箱子
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

小郑想要在仓库里存放箱子。总共有 $N$ 个箱子，编号从 1 到 $N$。第 $i$ ($1 \le i \le N$) 号箱子的大小为 $s_i$，收纳容量为 $c_i$。所有箱子的收纳容量都比其自身的大小要小，即满足 $c_i < s_i$。

小郑觉得仓库里的箱子太多、太杂乱，因此想把一些箱子装到另一些箱子里来存放。此时，必须满足以下条件：

*   一个箱子可以装入大小**不小于**其收纳容量的箱子。
*   已经装有其他箱子的箱子，也可以被装入另一个箱子中。
*   一个箱子**直接容纳**的箱子最多只能有一个。换句话说，一个箱子内最多可以直接放入一个其他的箱子，但允许这个被放入的箱子内部还装有别的箱子。

存放箱子的成本，等于没有被装在任何其他箱子里的箱子的数量。

例如，假设 $N = 4$，四个箱子的大小和收纳容量分别如下表所示。

| **编号** | **大小** | **收纳容量** |
| :---: | :---: | :---: |
|   1   |   6   |   4   |
|   2   |   5   |   1   |
|   3   |   9   |   8   |
|   4   |   2   |   1   |

此时，如下图所示，如果将 4 号箱子放入 1 号箱子，再将 1 号箱子放入 3 号箱子，那么没有被装在其他箱子里的箱子就有 2 个 (3 号箱子和 2 号箱子)，因此存放箱子的成本为 2。

![](https://cdn.luogu.com.cn/upload/image_hosting/sxmrnti7.png)

但是，如下图所示，如果将 2 号箱子和 4 号箱子都放入 3 号箱子中，由于 3 号箱子内直接容纳了两个箱子，因此不满足条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/k8bcx8pi.png)

仓库里不必非要放下所有的箱子，所以小郑计划只保留编号较小的一部分箱子，并丢弃其余的。小郑目前还没有决定要使用多少个箱子。

请你帮助小郑，对于从 1 到 $N$ 的所有 $i$，编写一个程序来计算存放 $1, 2, \ldots, i$ 号箱子所需的最小成本。
## 输入格式

第一行给定箱子的数量 $N$。

从第二行开始的 $N$ 行，给出了各个箱子的信息。其中第 $i$ 行（指这 $N$ 行中的第 $i$ 行，即文件的第 $i+1$ 行）是关于第 $i$ 号箱子的，给出了其大小 $s_i$ 和收纳容量 $c_i$，以空格分隔。
## 输出格式

输出 $N$ 行。

第 $i$ ($1 \le i \le N$) 行输出存放 $1, 2, \ldots, i$ 号箱子所需的最小成本。
## 样例

### 样例输入 #1
```
4
6 4
5 1
9 8
2 1
```
### 样例输出 #1
```
1
2
2
2
```
### 样例输入 #2
```
6
3 2
5 4
3 2
4 3
4 3
3 2
```
### 样例输出 #2
```
1
1
2
2
2
3
```
### 样例输入 #3
```
8
13 6
7 5
9 4
11 10
4 2
15 5
16 7
8 3
```
### 样例输出 #3
```
1
2
3
3
3
4
4
5
```
## 提示

### 限制条件

*   所有给定的数都是整数。
*   $2 \le N \le 2 \times 10^5$
*   $1 \le c_i < s_i \le 10^9$ ($1 \le i \le N$)

### 子任务

1.  (7 分) $N \le 6$。
2.  (12 分) 对于所有 $i$，$s_i = c_i + 1$。
3.  (26 分) $N \le 1000$。
4.  (17 分) 对于所有 $i$，$s_i \le 100$。
5.  (38 分) 无额外限制条件。


---

---
title: "[JOIGST 2025] 电波塔 / Radio Towers"
layout: "post"
diff: 普及+/提高
pid: P13738
tag: ['动态规划 DP', '树状数组', '2025', 'O2优化', 'JOISC/JOIST（日本）']
---
# [JOIGST 2025] 电波塔 / Radio Towers
## 题目描述

在 EGOI 国，有 $N$ 座电波塔沿东西方向排列，为国民提供互联网通信服务。电波塔从西向东依次编号为 $1$ 到 $N$。每座电波塔 $i$（$1 \leq i \leq N$）具有以下功能：

- 接收西向波长范围 $[A_i, A_i + L]$ 的电波；
- 向东发射固定波长 $B_i$ 的电波。

对于两座满足 $1 \leq i_1 < i_2 \leq N$ 的塔 $i_1, i_2$，当满足 $A_{i_2} \leq B_{i_1} \leq A_{i_2} + L$ 时，信息可从塔 $i_1$ 传输到塔 $i_2$。

EGOI 国政$ $府将通信稳定性定义为**满足顺序传输条件的非空子集数量**。具体来说，如果子集 $S = {i_1, i_2, \dots, i_k}$（$i_1 < i_2 < \cdots < i_k$）满足以下条件，则 $S$ 满足顺序传输条件：

- 对于任意相邻的两座塔 $(i_j, i_{j+1})$（$1 \leq j \leq k-1$），都满足 $A_{i_{j+1}} \leq B_{i_j} \leq A_{i_{j+1}} + L$。

给定电波塔参数，计算符合条件的子集数量模 $10^9 + 7$ 的结果。
## 输入格式

输入按以下格式从标准输入给出：

> $N$ $L$  
$A_1$ $B_1$  
$A_2$ $B_2$  
$\vdots$  
$A_N$ $B_N$
## 输出格式

输出一行，表示方案数模 $10^9 + 7$ 的值。
## 样例

### 样例输入 #1
```
3 0
1 3
2 3
3 2
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
8 2
1 3
5 1
6 7
7 5
5 2
2 1
3 1
1 6
```
### 样例输出 #2
```
36
```
### 样例输入 #3
```
10 3
1 5
2 3
2 4
5 4
10 7
7 9
4 3
3 7
7 7
6 5
```
### 样例输出 #3
```
109
```
## 提示

#### 【样例解释 #1】

考虑选择电波塔 $1, 2, 3$ 的情况。

  - 由于不满足 $A_2 \leq B_1 \leq A_2 + L$，因此无法从电波塔 $1$ 向电波塔 $2$ 传输信息。
  - 由于满足 $A_3 \leq B_2 \leq A_3 + L$，因此可以从电波塔 $2$ 向电波塔 $3$ 传输信息。

所以，这种选择方式不满足条件。

考虑选择电波塔 $1, 3$ 的情况。

  - 由于满足 $A_3 \leq B_1 \leq A_3 + L$，因此可以从电波塔 $1$ 向电波塔 $3$ 传输信息。

所以，这种选择方式满足条件。

满足条件的塔的选择方式有 $\lbrace1\rbrace, \lbrace2\rbrace, \lbrace3\rbrace, \lbrace1, 3\rbrace, \lbrace2, 3\rbrace$ 这 $5$ 种。因此，输出 $5\bmod (10^9 + 7) = 5$。

此样例满足所有子任务的限制。

#### 【样例解释 #2】

该样例满足子任务 $1,2,4$ 的限制。

#### 【样例解释 #3】

该样例满足子任务 $1,2,4$ 的限制。

#### 【数据范围】

-   $2 \leq N \leq 300\,000$。
-   $0 \leq L \leq 300\,000$。
-   $1 \leq A_i \leq 300\,000$（$1\leq i \leq N$）。
-   $1 \leq B_i \leq 300\,000$（$1\leq i \leq N$）。
-   输入的所有值都是整数。

#### 【子任务】

1. （$20$ 分）$N \leq 16$。
2. （$20$ 分）$N \leq 5\,000$。
3. （$25$ 分）$L = 0$。
4. （$35$ 分）无附加限制。


---

---
title: "[CERC 2021] Single-track railway"
layout: "post"
diff: 普及+/提高
pid: P13773
tag: ['线段树', '二分', '树状数组', '2021', 'ICPC', 'CERC']
---
# [CERC 2021] Single-track railway
## 题目描述

Trains running on a single-track railway can only meet at the stations. Suppose that a pair of trains simultaneously leave in the opposite directions, one from the initial and the other from the final station, i.e. the initial station in the opposite direction. It is likely that one of the trains will have to wait for the other one at one of the stations along the railway. To minimize the delays, the trains meet at the station such that the waiting time is minimized.

We know the travel time between each two adjacent stations, equal in both directions. Unfortunately, the travel times constantly change because of the works along the railway. You are given the initial travel times and an updated travel time for the affected section after each change. Write a program that computes the shortest possible waiting time for a pair of trains leaving from the opposite ends of the railway after each of the changes.
## 输入格式

The first line specifies the number of stations, $n$. In the second line, $n-1$ numbers are given, corresponding to the initial travel times between the adjacent stations (the $i$-th number is the travel time between stations $i$ and $i+1$). The third line specifies the number of changes, $k$. This is followed by $k$ lines, each containing two numbers: the first one, $j \in [1, n-1]$, specifies the station, and the second gives the updated travel time between stations $j$ and $j+1$. Keep in mind that the first station is numbered 1 rather than 0.
## 输出格式

Output $n+1$ lines, where the $i$-th line will contain the shortest possible waiting time after $i-1$ changes (the first one should correspond to the situation before any changes).
## 样例

### 样例输入 #1
```
6
20 70 40 10 50
2
4 80
2 30
```
### 样例输出 #1
```
10
0
40
```
## 提示

### Comment

At the beginning, the trains leaving in the opposite directions should meet at station 3. The first train will reach that station in 90 minutes, and the second will arrive there in 100 minutes; the waiting time will thus be 10 minutes. Following the first change, the optimal meeting point becomes station 4. Both trains will take 130 minutes to get there, so neither will have to wait. After the second change, they will also meet at station 4. This time, however, the train that arrives first will have to wait for 40 minutes.

### Input limits

* $2 \leq n \leq 200\,000$
* $0 \leq k \leq 200\,000$
* All travel times (both the initial and the updated ones) are integers from the interval $[1, 10^6]$.


---

---
title: "无聊的数列"
layout: "post"
diff: 普及+/提高
pid: P1438
tag: ['线段树', '树状数组', '递归', '洛谷原创', '差分']
---
# 无聊的数列
## 题目背景

无聊的 YYB 总喜欢搞出一些正常人无法搞出的东西。有一天，无聊的 YYB 想出了一道无聊的题：无聊的数列。。。
## 题目描述

维护一个数列 $a_i$，支持两种操作：

 - `1 l r K D`：给出一个长度等于 $r-l+1$ 的等差数列，首项为 $K$，公差为 $D$，并将它对应加到 $[l,r]$ 范围中的每一个数上。即：令 $a_l=a_l+K,a_{l+1}=a_{l+1}+K+D\ldots a_r=a_r+K+(r-l) \times D$。

 - `2 p`：询问序列的第 $p$ 个数的值 $a_p$。
## 输入格式

第一行两个整数数 $n,m$ 表示数列长度和操作个数。

第二行 $n$ 个整数，第 $i$ 个数表示 $a_i$。

接下来的 $m$ 行，每行先输入一个整数 $opt$。

若 $opt=1$ 则再输入四个整数 $l\ r\ K\ D$；

若 $opt=2$ 则再输入一个整数 $p$。

## 输出格式

对于每个询问，一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5 2
1 2 3 4 5
1 2 4 1 2
2 3

```
### 样例输出 #1
```
6
```
## 提示

#### 数据规模与约定

对于 $100\%$ 数据，$0\le n,m \le 10^5,-200\le a_i,K,D\le 200, 1 \leq l \leq r \leq n, 1 \leq p \leq n$。


---

---
title: "三元上升子序列"
layout: "post"
diff: 普及+/提高
pid: P1637
tag: ['线段树', '树状数组', '分治']
---
# 三元上升子序列
## 题目描述

Erwin 最近对一种叫 `thair` 的东西巨感兴趣。。。

在含有 $n$ 个整数的序列 $a_1,a_2,\ldots,a_n$ 中，三个数被称作`thair`当且仅当 $i<j<k$ 且 $a_i<a_j<a_k$。

求一个序列中 `thair` 的个数。
## 输入格式

开始一行一个正整数 $n$,

以后一行 $n$ 个整数 $a_1,a_2,\ldots,a_n$。
## 输出格式

一行一个整数表示 `thair` 的个数。
## 样例

### 样例输入 #1
```
4
2 1 3 4
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5
1 2 2 3 4
```
### 样例输出 #2
```
7
```
## 提示

#### 样例2 解释

$7$ 个 `thair` 分别是：

- 1 2 3
- 1 2 4
- 1 2 3
- 1 2 4
- 1 3 4
- 2 3 4
- 2 3 4

#### 数据规模与约定

- 对于 $30\%$ 的数据 保证 $n\le100$；
- 对于 $60\%$ 的数据 保证 $n\le2000$；
- 对于 $100\%$ 的数据 保证 $1 \leq n\le3\times10^4$，$1\le a_i\leq 10^5$。


---

---
title: "统计和"
layout: "post"
diff: 普及+/提高
pid: P2068
tag: ['线段树', '树状数组']
---
# 统计和
## 题目描述

给定一个长度为 $n(n\leq 100000)$，初始值都为 $0$ 的序列，$x(x\leq 100000)$ 次的修改某些位置上的数字，每次加上一个数，然后提出 $y(y\leq 100000)$ 个问题，求每段区间的和。

## 输入格式

第一行 $1$ 个整数，表示序列的长度 $n$。

第二行 $1$ 个整数，表示操作的次数 $w$。

后面依次是 $w$ 行，分别表示加入和询问操作。

其中，加入用 `x` 表示，询问用 `y` 表示。

$x$的格式为 `x a b` 表示在序列上第 $a$ 个数加上 $b$。保证 $1 \leq a \leq n$，$1 \leq b \leq 10^9$。

$y$ 的格式为 `y a b` 表示询问 $a$ 到 $b$ 区间的加和。保证 $1 \leq a \leq b \leq n$。

## 输出格式

每行一个正整数，分别是每次询问的结果

## 样例

### 样例输入 #1
```
5
4
x 3 8
y 1 3
x 4 9
y 3 4
```
### 样例输出 #1
```
8
17

```


---

---
title: "守墓人"
layout: "post"
diff: 普及+/提高
pid: P2357
tag: ['线段树', '树状数组', '分块']
---
# 守墓人
## 题目背景

 ![](https://cdn.luogu.com.cn/upload/pic/1406.png) 

在一个荒凉的墓地上，有一个令人尊敬的守墓人， 他看守的墓地从来没有被盗过， 所以人们很放心的把自己的先人的墓安顿在他那

守墓人能看好这片墓地是必然而不是偶然……

因为……守墓人懂风水 0.0
## 题目描述

他把墓地分为主要墓碑和次要墓碑， 主要墓碑只能有 $1$ 个， 守墓人把他记为 $1$ 号， 而次要墓碑有 $n-1$ 个，守墓人将之编号为 $2,3\dots n$，所以构成了一个有 $n$ 个墓碑的墓地。

而每个墓碑有一个初始的风水值，这些风水值决定了墓地的风水的好坏，所以守墓人需要经常来查询这些墓碑。

善于运用风水的守墓人，通过一次次逆天改命，使得自己拥有了无限寿命，没人知道他活了多久。这天，你幸运的拜访到了他，他要求你和他共同见证接下来几年他的战果，但不过他每次统计风水值之和都需要你来帮他计算，算错了他会要你命 QAQ

风水也不是不可变，除非遭遇特殊情况，已知在接下来的 $2147483647$ 年里，会有 $f$ 次灾难，守墓人会有几个操作：

1. 将 $[l,r]$ 这个区间所有的墓碑的风水值增加 $k$。

2.将主墓碑的风水值增加 $k$

3.将主墓碑的风水值减少 $k$

4.统计 $[l,r]$ 这个区间所有的墓碑的风水值之和

5.求主墓碑的风水值

上面也说了，很多人会把先人的墓安居在这里，而且守墓人活了很多世纪→\_→，墓碑的数量会多的你不敢相信= =

守墓人和善的邀请你帮他完成这些操作，要不然哪天你的旅馆爆炸了，天上下刀子.....

为了活命，还是帮他吧

## 输入格式

第一行，两个正整数 $n,f$ 表示共有 $n$ 块墓碑，并且在接下来的 $2147483647 $年里，会有 $f$ 次世界末日

第二行，$n$ 个正整数，表示第 $i$ 块墓碑的风水值

接下来 $f$ 行，每行都会有一个针对世界末日的解决方案，如题所述，标记同题

## 输出格式

输出会有若干行，对 $4$ 和 $5$ 的提问做出回答

## 样例

### 样例输入 #1
```
5 7
0 0 0 0 0
1 1 5 1
1 1 3 3
2 3
3 1
4 1 5
2 1
5
```
### 样例输出 #1
```
16
7
```
## 提示

$20\%$ 的数据满足：$1\leq n\leq 100$

$50\%$ 的数据满足：$1\leq n\leq 6000$

$100\%$ 的数据满足：$1\leq n,f\leq 2 \times 10^5$，答案不超过 64 位整数。



---

---
title: "寒假作业"
layout: "post"
diff: 普及+/提高
pid: P2717
tag: ['树状数组', 'cdq 分治']
---
# 寒假作业
## 题目背景

zzs 和 zzy 正在被寒假作业折磨，然而他们有答案可以抄啊。

## 题目描述

他们共有 $n$ 项寒假作业。zzy 给每项寒假作业都定义了一个疲劳值 $a_i$，表示抄这个作业所要花的精力。

zzs 现在想要知道，有多少组连续的寒假作业的疲劳值的平均值不小于 $k$？

简单地说，给定一个长度为 $n$ 的正整数序列 $\{a_i\}$，求出有多少个**连续**子序列的平均值不小于 $k$。

## 输入格式

第一行是两个整数，分别表示序列长度 $n$ 和给定的参数 $k$。

第二行有 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个数字 $a_i$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3 2
1
2
3

```
### 样例输出 #1
```
4
```
## 提示

#### 样例 1 解释

共有 $6$ 个连续的子序列，分别是 $(1)$、$(2)$、$(3)$、$(1,2)$、$(2,3)$、$(1,2,3)$，平均值分别为 $1$、$2$、$3$、$1.5$、$2.5$、$2$，其中平均值不小于 $2$ 的共有 $4$ 个。

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 100$。
- 对于 $50\%$ 的数据，保证 $n \leq 5000$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$1 \leq a_i,k \leq 10^4$。


---

---
title: "[USACO06DEC] Milk Patterns G"
layout: "post"
diff: 普及+/提高
pid: P2852
tag: ['2006', '二分', 'USACO', '哈希 hashing', '后缀数组 SA']
---
# [USACO06DEC] Milk Patterns G
## 题目描述

Farmer John has noticed that the quality of milk given by his cows varies from day to day. On further investigation, he discovered that although he can't predict the quality of milk from one day to the next, there are some regular patterns in the daily milk quality.

To perform a rigorous study, he has invented a complex classification scheme by which each milk sample is recorded as an integer between 0 and 1,000,000 inclusive, and has recorded data from a single cow over N (1 ≤ N ≤ 20,000) days. He wishes to find the longest pattern of samples which repeats identically at least K (2 ≤ K ≤ N) times. This may include overlapping patterns -- 1 2 3 2 3 2 3 1 repeats 2 3 2 3 twice, for example.

Help Farmer John by finding the longest repeating subsequence in the sequence of samples. It is guaranteed that at least one subsequence is repeated at least K times.

## 输入格式

Line 1: Two space-separated integers: N and K


Lines 2..N+1: N integers, one per line, the quality of the milk on day i appears on the ith line.

## 输出格式

Line 1: One integer, the length of the longest pattern which occurs at least K times

## 样例

### 样例输入 #1
```
8 2
1
2
3
2
3
2
3
1
```
### 样例输出 #1
```
4
```
## 题目翻译

农夫 John 发现他的奶牛产奶的质量一直在变动。经过细致的调查，他发现：虽然他不能预见明天产奶的质量，但连续的若干天的质量有很多重叠。我们称之为一个“模式”。 John 的牛奶按质量可以被赋予一个 $0$ 到 $1000000$ 之间的数。并且 John 记录了 $N$（$1 \le N \le 2 \times 10 ^ 4$）天的牛奶质量值。他想知道最长的出现了至少 $K$（$2 \le K \le N$）次的模式的长度。比如 `1 2 3 2 3 2 3 1` 中 `2 3 2 3` 出现了两次。当 $K = 2$ 时，这个长度为 $4$。


---

---
title: "【模板】树状数组 2"
layout: "post"
diff: 普及+/提高
pid: P3368
tag: ['树状数组']
---
# 【模板】树状数组 2
## 题目描述

如题，已知一个数列，你需要进行下面两种操作：

1. 将某区间每一个数加上 $x$；

2. 求出某一个数的值。
## 输入格式


第一行包含两个整数 $N$、$M$，分别表示该数列数字的个数和操作的总个数。

第二行包含 $N$ 个用空格分隔的整数，其中第 $i$ 个数字表示数列第 $i $ 项的初始值。

接下来 $M$ 行每行包含 $2$ 或 $4$个整数，表示一个操作，具体如下：

操作 $1$： 格式：`1 x y k` 含义：将区间 $[x,y]$ 内每个数加上 $k$；

操作 $2$： 格式：`2 x` 含义：输出第 $x$ 个数的值。
## 输出格式

输出包含若干行整数，即为所有操作 $2$ 的结果。
## 样例

### 样例输入 #1
```
5 5
1 5 4 2 3
1 2 4 2
2 3
1 1 5 -1
1 3 5 7
2 4
```
### 样例输出 #1
```
6
10
```
## 提示

#### 样例 1 解释：

 ![](https://cdn.luogu.com.cn/upload/pic/2258.png) 

故输出结果为 6、10。

---

#### 数据规模与约定

对于 $30\%$ 的数据：$N\le8$，$M\le10$；

对于 $70\%$ 的数据：$N\le 10000$，$M\le10000$；

对于 $100\%$ 的数据：$1 \leq N, M\le 500000$，$1 \leq x, y \leq n$，保证任意时刻序列中任意元素的绝对值都不大于 $2^{30}$。


---

---
title: "【模板】树状数组 1"
layout: "post"
diff: 普及+/提高
pid: P3374
tag: ['树状数组']
---
# 【模板】树状数组 1
## 题目描述

如题，已知一个数列，你需要进行下面两种操作：

- 将某一个数加上 $x$

- 求出某区间每一个数的和

## 输入格式

第一行包含两个正整数 $n,m$，分别表示该数列数字的个数和操作的总个数。   
 
第二行包含 $n$ 个用空格分隔的整数，其中第 $i$ 个数字表示数列第 $i$ 项的初始值。

接下来 $m$ 行每行包含 $3$ 个整数，表示一个操作，具体如下：

- `1 x k`  含义：将第 $x$ 个数加上 $k$

- `2 x y`  含义：输出区间 $[x,y]$ 内每个数的和

## 输出格式

输出包含若干行整数，即为所有操作 $2$ 的结果。

## 样例

### 样例输入 #1
```
5 5
1 5 4 2 3
1 1 3
2 2 5
1 3 -1
1 4 2
2 1 4
```
### 样例输出 #1
```
14
16
```
## 提示

【数据范围】

对于 $30\%$ 的数据，$1 \le n \le 8$，$1\le m \le 10$；   
对于 $70\%$ 的数据，$1\le n,m \le 10^4$；   
对于 $100\%$ 的数据，$1\le n,m \le 5\times 10^5$。

数据保证对于任意时刻，$a$ 的任意子区间（包括长度为 $1$ 和 $n$ 的子区间）和均在 $[-2^{31}, 2^{31})$ 范围内。


样例说明：

 ![](https://cdn.luogu.com.cn/upload/pic/2256.png) 

故输出结果14、16



---

---
title: "[USACO17JAN] Balanced Photo G"
layout: "post"
diff: 普及+/提高
pid: P3608
tag: ['2017', 'USACO', '树状数组', '枚举', '前缀和']
---
# [USACO17JAN] Balanced Photo G
## 题目描述

Farmer John is arranging his $N$ cows in a line to take a photo ($1 \leq N \leq 100,000$). The height of the $i$th cow in sequence is $h_i$, and the heights of all cows are distinct.

As with all photographs of his cows, FJ wants this one to come out looking as nice as possible. He decides that cow $i$ looks "unbalanced" if $L_i$ and $R_i$ differ by more than factor of 2, where $L_i$ and $R_i$ are the number of cows taller than $i$ on her left and right, respectively. That is, $i$ is unbalanced if the larger of $L_i$ and $R_i$ is strictly more than twice the smaller of these two numbers. FJ is hoping that not too many of his cows are unbalanced.

Please help FJ compute the total number of unbalanced cows.


## 输入格式

The first line of input contains $N$.  The next $N$ lines contain $h_1 \ldots h_N$, each a nonnegative integer at most 1,000,000,000.


## 输出格式

Please output a count of the number of cows that are unbalanced.


## 样例

### 样例输入 #1
```
7
34
6
23
0
5
99
2
```
### 样例输出 #1
```
3
```
## 题目翻译

### 题目描述

FJ 正在安排他的 $N$ 头奶牛站成一排来拍照（$1\le N \le 10^5$）。序列中的第 $i$ 头奶牛的高度是 $h_i$，且序列中所有的奶牛的身高都不同。

就像他的所有牛的照片一样，FJ希望这张照片看上去尽可能好。他认为，如果 $L_i$ 和 $R_i$ 的数目相差 $1$ 倍以上，第 $i$ 头奶牛就是不平衡的（$L_i$ 和 $R_i$ 分别代表第 $i$ 头奶牛左右两边比她高的奶牛的数量）。也就是说，如果 $L_i$ 和 $R_i$ 中的较大数大于较小数的 $2$ 倍，第 $i$ 头奶牛就是不平衡的。FJ 不希望他有太多的奶牛不平衡。

请帮助 FJ 计算不平衡的奶牛数量。

### 输入格式

第一行一个整数 $N$。

接下 $N$ 行包括 $H_1$ 到 $H_n$，每行一个不超过 $10^9$ 的非负整数。

### 输出格式

请输出不平衡的奶牛数量。


---

---
title: "红色的幻想乡"
layout: "post"
diff: 普及+/提高
pid: P3801
tag: ['线段树', '树状数组', '洛谷原创', '容斥原理']
---
# 红色的幻想乡
## 题目背景

蕾米莉亚的红雾异变失败后，很不甘心。

## 题目描述

经过上次失败后，蕾米莉亚决定再次发动红雾异变，但为了防止被灵梦退治，她决定将红雾以奇怪的阵势释放。

我们将幻想乡看做是一个 $n \times m$的方格地区，一开始没有任何一个地区被红雾遮盖。蕾米莉亚每次站在某一个地区上，向东南西北四个方向各发出一条无限长的红雾，可以影响到整行/整列，但不会影响到她所站的那个地区。如果两阵红雾碰撞，则会因为密度过大而沉降消失。灵梦察觉到了这次异变，决定去解决它。但在解决之前，灵梦想要了解一片范围红雾的密度。可以简述为两种操作:

``1 x y`` 蕾米莉亚站在坐标 $(x,y)$ 的位置向四个方向释放无限长的红雾。

``2 x1 y1 x2 y2`` 询问左上点为$(x1,y1)$，右下点为 $(x2,y2)$ 的矩形范围内，被红雾遮盖的地区的数量。

## 输入格式

第一行三个整数 $n,m,q$，表示幻想乡大小为 $n \times m$，有 $q$ 个询问。

接下来 $q$ 行，每行 $3$ 个或 $5$ 个整数,用空格隔开，含义见题目描述。
## 输出格式

对于每一个操作 $2$，输出一行一个整数，表示对应询问的答案。
## 样例

### 样例输入 #1
```
4 4 3
1 2 2
1 4 4
2 1 1 4 4

```
### 样例输出 #1
```
8
```
## 提示

#### 样例输入输出 1 解释

用``o``表示没有红雾，``x``表示有红雾，两次释放红雾后幻想乡地图如下:

```
oxox
xoxo
oxox
xoxo
```

---

#### 数据规模与约定

- 对于 $20\%$ 的数据，$1 \le n,m,q \le 200$。
- 对于 $40\%$ 的数据，$1 \le n,m,q \le 10^3$。
- 对于 $100\%$ 的数据，$1 \le n,m,q \le 10^5$，$1 \le x_1,x_2,x \le n$，$x_1 \le x_2$，$1 \le y_1,y_2,y \le m$，$y_1 \le y_2$。


---

---
title: "[BJWC2010] 外星联络"
layout: "post"
diff: 普及+/提高
pid: P4341
tag: ['2010', '北京', '枚举', '后缀数组 SA']
---
# [BJWC2010] 外星联络
## 题目描述

小 P 在看过电影《超时空接触》(Contact)之后被深深的打动，决心致力于寻找外星人的事业。于是，他每天晚上都爬在屋顶上试图用自己的收音机收听外星人发来的信息。

虽然他收听到的仅仅是一些噪声，但是他还是按照这些噪声的高低电平将接收到的信号改写为由 `0` 和 `1` 构成的串， 并坚信外星人的信息就隐藏在其中。他认为，外星人发来的信息一定会在他接受到的 01 串中重复出现，所以他希望找到他接受到的 01 串中所有重复出现次数大于 $1$ 的子串。

但是他收到的信号串实在是太长了，于是，他希望你能编一个程序来帮助他。
## 输入格式

输入文件的第一行是一个整数$N$ ，代表小 P 接收到的信号串的长度。  
输入文件第二行包含一个长度为$N$ 的 01 串，代表小 P 接收到的信号串。
## 输出格式

输出文件的每一行包含一个出现次数大于$1$ 的子串所出现的次数。输出的顺序按对应的子串的字典序排列。
## 样例

### 样例输入 #1
```
7
1010101
```
### 样例输出 #1
```
3
3
2
2
4
3
3
2
2
```
## 提示

对于 100%的数据，满足 $0 \le N \le 3000$


---

---
title: "[BalticOI 2007] Sound 静音问题"
layout: "post"
diff: 普及+/提高
pid: P4392
tag: ['搜索', '2007', '线段树', '树状数组', 'BalticOI（波罗的海）']
---
# [BalticOI 2007] Sound 静音问题
## 题目描述

数字录音中，声音是用表示空气压力的数字序列描述的，序列中的每个值称为一个采样，每个采样之间间隔一定的时间。 

很多声音处理任务都需要将录到的声音分成由静音隔开的几段非静音段。为了避免分成过多或者过少的非静音段，静音通常是这样定义的：$m$ 个采样的序列，该序列中采样的最大值和最小值之差不超过一个特定的阈值 $c$。 

请你写一个程序，检测 $n$ 个采样中的静音。
## 输入格式

第一行有三个整数 $n,m,c$（$1\le n\le10^6$，$1\le m\le10^4$，$0\le c\le10^4$），分别表示总的采样数、静音的长度和静音中允许的最大噪音程度。

第 $2$ 行 $n$ 个整数 $a_i$（$0\le a_i\le 10^6$），表示声音的每个采样值，每两个整数之间用空格隔开。
## 输出格式

列出了所有静音的起始位置 $i$（$i$ 满足$\max\{a_i,a_{i+1}\cdots a_{i+m-1}\}-\min\{a_i,a_{i+1}\cdots a_{i+m-1}\}\le c$），每行表示一段静音的起始位置，按照出现的先后顺序输出。如果没有静音则输出 `NONE`。

## 样例

### 样例输入 #1
```
7 2 0
0 1 1 2 3 2 2
```
### 样例输出 #1
```
2
6
```


---

---
title: "Preprefix sum"
layout: "post"
diff: 普及+/提高
pid: P4868
tag: ['树状数组', '前缀和', '差分']
---
# Preprefix sum
## 题目描述

前缀和（prefix sum）$S_i=\sum_{k=1}^i a_k$。

前前缀和（preprefix sum）则把 $S_i$ 作为原序列再进行前缀和。记再次求得前缀和第 $i$ 个是 $SS_i$。

给一个长度 $n$ 的序列 $a_1, a_2, \cdots, a_n$，有两种操作：

1. `Modify i x`：把 $a_i$ 改成 $x$。
2. `Query i`：查询 $SS_i$。

## 输入格式

第一行给出两个整数 $N,M$。分别表示序列长度和操作个数。  
接下来一行有 $N$ 个数，即给定的序列 $a_1,a_2,\cdots,a_n$。  
接下来 $M$ 行，每行对应一个操作，格式见题目描述。  
## 输出格式

对于每个询问操作，输出一行，表示所询问的 $SS_i$ 的值。
## 样例

### 样例输入 #1
```
5 3
1 2 3 4 5
Query 5
Modify 3 2
Query 5
```
### 样例输出 #1
```
35
32
```
## 提示

$1\le N,M\le 10^5$，且在任意时刻 $0\le A_i\le 10^5$。


---

---
title: "Agent2"
layout: "post"
diff: 普及+/提高
pid: P4939
tag: ['树状数组', 'O2优化', '差分']
---
# Agent2
## 题目背景

炎炎夏日还没有过去，`Agent`们没有一个想出去外面搞事情的。每当`ENLIGHTENED总部`组织活动时，人人都说有空，结果到了活动日，却一个接着一个`咕咕咕`了。只有不咕鸟`Lyn_king`一个人冒着太阳等了半个多小时，然后居然看到连`ENLIGHTENED行动参谋`都`咕咕咕`了，果然`咕咕咕`是人类的本性啊。
## 题目描述

作为一个`ENLIGHTENED行动指挥`，自然不想看到这一点，于是他偷取到了那些经常`咕咕咕`的`Agent`的在下来$N$天的`活动安排表`，并且叫上了你来整理。在整理过程中，`ENLIGHTENED行动指挥`对你说了$M$条命令，命令操作如下。
1. 输入$0,a,b$，这代表在第$a$天到第$b$天，有一名`Agent`要咕咕咕。
2. 输入$1$ $a$，这代表`ENLIGHTENED行动指挥`询问你根据目前的信息，在第$a$天有多少名`Agent`会咕咕咕。

作为同是不咕鸟的你，也想要惩戒那些经常`咕咕咕`的人，所以，请协助完成`ENLIGHTENED行动指挥`完成整理，并且在他每次询问时，输出正确的答案。
## 输入格式

第一行输入两个整数输$N,M$，
下来$M$行,每行输入一个命令，命令格式见题目描述。
## 输出格式

对于每一次询问的操作，都要输出询问的答案。答案之间用换行隔开。
## 样例

### 样例输入 #1
```
5 5
0 1 2
0 1 5
1 1
0 3 5
1 5
```
### 样例输出 #1
```
2
2
```
## 提示

对于$20\%$的数据 $N,M \leq 10$

对于$40\%$的数据 $N,M \leq 10^3$

对于$60\%$的数据 $N,M \leq 10^5$

对于$100\%$的数据 $1 \leq a,b \leq N \leq 10^7,M \leq 4*10^5$


---

---
title: "[CQOI2006] 简单题"
layout: "post"
diff: 普及+/提高
pid: P5057
tag: ['2006', '重庆', '线段树', '各省省选', '树状数组']
---
# [CQOI2006] 简单题
## 题目描述

有一个 $n$ 个元素的数组，每个元素初始均为 $0$。有 $m$ 条指令，每条指令为两种操作中的一种：
1. 让其中一段连续序列数字反转；（即 $0$ 变 $1$，$1$ 变 $0$）
2. 询问某个元素的值。

例如当 $n=20$ 时，$10$ 条指令如下：

![](https://cdn.luogu.com.cn/upload/pic/44663.png)

## 输入格式

第一行包含两个整数 $n,m$，表示数组的长度和指令的条数。

接下来 $m$ 行，每行的第一个数 $t$ 表示操作的种类：

* 若 $t=1$，则接下来有两个数 $L,R$，表示反转区间 $[L,R]$ 的每个数；
* 若 $t=2$，则接下来只有一个数 $i$，表示询问的下标。
## 输出格式

每个操作 $2$ 输出一行（非 $0$ 即 $1$），表示每次操作 $2$ 的回答。
## 样例

### 样例输入 #1
```
20 10
1 1 10
2 6
2 12
1 5 12
2 6
2 15
1 6 16
1 11 17
2 12
2 6
```
### 样例输出 #1
```
1
0
0
0
1
1
```
## 提示

对于 $50\%$ 的数据，$1 \le n \le 10^3$，$1 \le m \le 10^4$；

对于 $100\%$ 的数据，$1 \le n \le 10^5$，$1 \le m \le 5 \times 10^5$，保证 $L \le R$。


---

---
title: "[USACO04OPEN] MooFest G 加强版"
layout: "post"
diff: 普及+/提高
pid: P5094
tag: ['2004', 'USACO', '树状数组']
---
# [USACO04OPEN] MooFest G 加强版
## 题目描述

每一年，约翰的 $ N $ 只奶牛参加奶牛狂欢节。这是一个全世界奶牛都参加的大联欢。狂欢节包括很多有趣的活动，比如干草堆叠大赛、跳牛栏大赛，奶牛之间有时还相互扎屁股取乐。当然，她们会排成一列嚎叫，来欢庆她们的节日。奶牛们的叫声实在刺耳，以致于每只奶牛的听力都受到不同程度的损伤。现在告诉你奶牛 $ i $ 的听力为 $ v_i $ ，这表示如果奶牛 $ j $ 想说点什么让她听到，必须用高于 $ v_i \times dis(i,j) $ 的音量。因此，如果奶牛 $ i $ 和 $ j $ 想相互交谈，她们的音量必须不小于 $ \max (v_i,v_j) \times dis(i,j) $。其中 $ dis(i,j) $ 表示她们间的距离。

现在 $ N $ 只奶牛都站在一条直线上了，每只奶牛还有一个坐标 $ x_i $。如果每对奶牛都在交谈，并且使用最小音量，那所有 $ N(N-1)/2 $ 对奶牛间谈话的音量之和为多少？
## 输入格式

第 $1$ 行输入一个整数 $ N $ 。

接下来 $ N $ 行，每行输入两个数 $ v_i $ 和 $ x_i $ ，分别代表第 $ i $ 头奶牛的听力和坐标。
## 输出格式

输出一个数，代表这 $ N(N-1)/2 $ 对奶牛谈话时的音量之和。
## 样例

### 样例输入 #1
```
4
3 1
2 5
2 6
4 3
```
### 样例输出 #1
```
57
```
## 提示

### 数据范围

因为原数据下 $O(N^2)$ 算法可以通过，所以新添加了一些增强数据。

原数据作为子任务 $1$，新添加的数据作为子任务 $2$。

- 子任务 $1$（$1$ 分）：$1 \leq N,V_i,x_i \leq 2 \times 10^4$。
- 子任务 $2$（$99$ 分）：$1 \leq N,V_i,x_i \leq 5 \times 10^4$。


---

---
title: "[USACO19JAN] Sleepy Cow Sorting G"
layout: "post"
diff: 普及+/提高
pid: P5200
tag: ['2019', 'USACO', '树状数组']
---
# [USACO19JAN] Sleepy Cow Sorting G
## 题目背景

USACO 19年一月月赛金组第二题
## 题目描述

Farmer John正在尝试将他的 $N$ 头奶牛（$1\le N\le 10^5$），方便起见编号为 $1\ldots N$，在她们前往牧草地吃早餐之前排好顺序。

当前，这些奶牛以 $p_1,p_2,p_3,\ldots,p_N$ 的顺序排成一行，Farmer John站在奶牛 $p_1$ 前面。他想要重新排列这些奶牛，使得她们的顺序变为 $1,2,3,\ldots,N$，奶牛 $1$ 在 Farmer John 旁边。

今天奶牛们有些困倦，所以任何时刻都只有直接面向 Farmer John 的奶牛会注意听 Farmer John 的指令。每一次他可以命令这头奶牛沿着队伍向后移动 $k$ 步，$k$ 可以是 $1$ 到 $N−1$ 之间的任意数。她经过的 $k$ 头奶牛会向前移动，腾出空间使得她能够插入到队伍中这些奶牛之后的位置。

例如，假设 $N=4$，奶牛们开始时是这样的顺序：

```plain
 FJ: 4 3 2 1
```

唯一注意 FJ 指令的奶牛是奶牛 $4$。当他命令她向队伍后移动 $2$ 步之后，队伍的顺序会变成：

```plain
 FJ: 3 2 4 1 
```

现在唯一注意 FJ 指令的奶牛是奶牛 $3$，所以第二次他可以给奶牛 $3$ 下命令，如此进行直到奶牛们排好了顺序。

Farmer John 急欲完成排序，这样他就可以回到他的农舍里享用他自己的早餐了。请帮助他求出一个操作序列，使得能够用最少的操作次数将奶牛们排好顺序。
## 输入格式

输入的第一行包含 $N$。第二行包含 $N$ 个空格分隔的整数：$p_1,p_2,p_3,\ldots,p_N$，表示奶牛们的起始顺序。
## 输出格式

输出的第一行包含一个整数 $K$，为将奶牛们排好顺序所需的最小操作次数。

第二行包含 $K$ 个空格分隔的整数，$c_1,c_2,\ldots,c_K$，每个数均在 $1\ldots N−1$ 之间。如果第 $i$ 次操作 FJ 命令面向他的奶牛向队伍后移动 $c_i$ 步，那么 $K$ 次操作过后奶牛们应该排好了顺序。

如果存在多种最优的操作序列，你的程序可以输出其中任何一种（不过实际上是唯一解）。
## 样例

### 样例输入 #1
```
4
1 2 4 3
```
### 样例输出 #1
```
3
2 2 3
```


---

---
title: "【模板】康托展开"
layout: "post"
diff: 普及+/提高
pid: P5367
tag: ['线段树', '平衡树', '树状数组', '康托展开']
---
# 【模板】康托展开
## 题目描述

求 $1\sim N$ 的一个给定全排列在所有 $1\sim N$ 全排列中的排名。结果对 $998244353$ 取模。
## 输入格式

第一行一个正整数 $N$。

第二行 $N$ 个正整数，表示 $1\sim N$ 的一种全排列。
## 输出格式

一行一个非负整数，表示答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
3
2 1 3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4
1 2 4 3
```
### 样例输出 #2
```
2
```
## 提示

对于$10\%$数据，$1\le N\le 10$。

对于$50\%$数据，$1\le N\le 5000$。

对于$100\%$数据，$1\le N\le 1000000$。


---

---
title: "[BJOI2016] 回转寿司"
layout: "post"
diff: 普及+/提高
pid: P5459
tag: ['2016', '线段树', '各省省选', '树状数组', '离散化', '北京', 'cdq 分治', 'O2优化']
---
# [BJOI2016] 回转寿司
## 题目描述

酷爱日料的小Z经常光顾学校东门外的回转寿司店。在这里，一盘盘寿司通过传送带依次呈现在小Z眼前。  

不同的寿司带给小Z的味觉感受是不一样的，我们定义小Z对每盘寿司都有一个满意度。  

例如小Z酷爱三文鱼，他对一盘三文鱼寿司的满意度为 $10$；小Z觉得金枪鱼没有什么味道，他对一盘金枪鱼寿司的满意度只有 $5$；小Z最近看了电影《美人鱼》，被里面的八爪鱼恶心到了，所以他对一盘八爪鱼刺身的满意度是 $-100$。   

特别地，小Z是个著名的吃货，他吃回转寿司有一个习惯，我们称之为“狂吃不止”。具体地讲，当他吃掉传送带上的一盘寿司后，他会毫不犹豫地吃掉它后面的寿司，直到他不想再吃寿司了为止。  

今天，小Z再次来到了这家回转寿司店，$N$ 盘寿司将依次经过他的面前。其中，小Z对第 $i$ 盘寿司的满意度为$a_i$。  

小Z可以选择从哪盘寿司开始吃，也可以选择吃到哪盘寿司为止。他想知道共有多少种不同的选择，使得他的满意度之和不低于 $L$，且不高于 $R$。

注意，虽然这是回转寿司，但是我们不认为这是一个环上的问题，而是一条线上的问题。即，小Z能吃到的是输入序列的一个连续子序列；最后一盘转走之后，第一盘并不会再出现一次。
## 输入格式

第一行三个正整数 $N,L,R$，表示寿司盘数，满意度的下限和上限。  
第二行包含 $N$ 个整数 $a_i$，表示小Z对寿司的满意度。  

## 输出格式

一行一个整数，表示有多少种方案可以使得小Z的满意度之和不低于 $L$ 且不高于 $R$。
## 样例

### 样例输入 #1
```
5 5 9
1 2 3 4 5
```
### 样例输出 #1
```
6
```
## 提示

【数据范围】  

$1\le N \le 10^5$  
$|a_i| \le 10^5$   
$0\le L,R \le 10^9$


---

---
title: "[POI 2000] 公共串"
layout: "post"
diff: 普及+/提高
pid: P5546
tag: ['2000', 'POI（波兰）', '字典树 Trie', '后缀数组 SA']
---
# [POI 2000] 公共串
## 题目描述

给出几个由小写字母构成的单词，求它们最长的公共子串的长度。

## 输入格式

文件的第一行是整数 $n$，$1\le n \le 5$，表示单词的数量。接下来$n$行每行一个单词，只由小写字母组成，单词的长度至少为$1$，最大为$2000$。
## 输出格式

仅一行，一个整数，最长公共子串的长度。
## 样例

### 样例输入 #1
```
3
abcb
bca
acbc
```
### 样例输出 #1
```
2
```


---

---
title: "[eJOI 2019] 异或橙子"
layout: "post"
diff: 普及+/提高
pid: P6225
tag: ['2019', '树状数组', 'eJOI（欧洲）', '位运算']
---
# [eJOI 2019] 异或橙子
## 题目描述

Janez 喜欢橙子！他制造了一个橙子扫描仪，但是这个扫描仪对于扫描的每个橙子的图像只能输出一个  $32$ 位整数。

他一共扫描了 $n$ 个橙子，但有时他也会重新扫描一个橙子，导致这个橙子的 $32$ 位整数发生更新。

Janez 想要分析这些橙子，他觉得异或操作非常有趣，他每次选取一个区间从 $l$  至 $u$，他想要得到这个区间内所有子区间的异或和的异或和。

例如 $l=2,u=4$ 的情况，记橙子序列 $A$ 中第 $i$ 个橙子的整数是 $a_i$，那么他要求的就是：

$$a_2 \oplus a_3 \oplus a_4 \oplus (a_2\oplus a_3)\oplus(a_3\oplus a_4)\oplus(a_2\oplus a_3 \oplus a_4)$$

-------------------------------------

注：式子中的 $\oplus$ 代表按位异或运算。异或的运算规则如下。

对于两个数的第 $i$ 位，记为 $x,y$，那么：

|$x$|$y$|$x\oplus y$|
| :-----------: | :-----------: | :-----------: |
|$0$|$1$|$1$|
|$1$|$0$|$1$|
|$0$|$0$|$0$|
|$1$|$1$|$0$|

例：$13\oplus 23=26$

|$13=$|$0\cdots 001101$|
| --------: | :------: |
|$23=$|$0\cdots 010111$|
|$13\oplus 23=$|$0\cdots 011010$|
## 输入格式

第一行输入两个正整数 $n,q$，表示橙子数量和操作次数。

接下来一行 $n$ 个非负整数，表示每个橙子扫描得到的数值 ，从 $1$ 开始编号。

接下来 $q$ 行，每行三个数：

- 如果第一个数是 $1$，接下来输入一个正整数 $i$ 与非负整数 $j$，表示将第 $i$ 个橙子的扫描值 $a_i$ 修改为 $j$。

- 如果第一个数是 $2$，接下来输入两个正整数 $u,l$ 表示询问这个区间的答案。
## 输出格式

对于每组询问，输出一行一个非负整数，表示所求的总异或和。
## 样例

### 样例输入 #1
```
3 3
1 2 3
2 1 3
1 1 3
2 1 3
```
### 样例输出 #1
```
2
0
```
### 样例输入 #2
```
5 6
1 2 3 4 5
2 1 3
1 1 3
2 1 5
2 4 4
1 1 1
2 4 4
```
### 样例输出 #2
```
2
5
4
4
```
## 提示

#### 输入输出样例 1 解释

- 最初，$A=[1,2,3]$，询问结果为 $1\oplus 2\oplus 3\oplus(1\oplus 2)\oplus (2\oplus 3)\oplus(1\oplus 2\oplus 3)=2$

- 修改后，第一个位置被修改为 $3$ ，询问的结果是 $3\oplus 2\oplus 3\oplus(3\oplus 2)\oplus (2\oplus 3)\oplus(3\oplus 2\oplus 3)=0$。

----------------------------

#### 数据规模与约定：

**本题采用多测试点捆绑测试，共有 5 个子任务**。

- Subtask 1(12 points)：$1\le n,q\le 10^2$，无特殊限制
- Subtask 2(18 points)：$1\le n,q\le 5\times 10^2$，且没有修改操作。
- Subtask 3(25 points)：$1\le n,q\le 5\times 10^3$，无特殊限制
- Subtask 4(20 points)：$1\le n,q\le 2\times 10^5$，且没有修改操作。
- Subtask 5(25 points)：$1\le n,q\le 2\times 10^5$，无特殊限制

对于所有数据，$0\le a_i\le 10^9,1\le n,q\le 2\times 10^5$

--------------------------

#### 说明

原题来自：[eJOI2019](http://ejoi2019.si/) Problem A. [XORanges](https://www.ejoi2019.si/static/media/uploads/tasks/xoranges-isc(1).pdf)

题面&数据来自：[LibreOJ](https://loj.ac/problem/3195)


---

---
title: "[USACO20OPEN] Haircut G"
layout: "post"
diff: 普及+/提高
pid: P6278
tag: ['2020', '线段树', 'USACO', '树状数组']
---
# [USACO20OPEN] Haircut G
## 题目描述

Farmer John 由于对整理他难以整平的头发感到疲惫，于是决定去理发。他有一排 $N$ 缕头发，第 $i$ 缕头发初始时长度为 $A_i$ 微米（$0\le A_i\le N$）。理想情况下，他想要他的头发在长度上单调递增，所以他定义他的头发的“不良度”为逆序对的数量：满足 $i < j$ 及 $A_i > A_j$ 的二元对 $(i,j)$。  
对于每一个 $j=0,1,\ldots,N-1$，Farmer John 想要知道他所有长度大于 $j$ 的头发的长度均减少到 $j$ 时他的头发的不良度。

-----

（有趣的事实：人类平均确实有大约 $10^5$ 根头发！）
## 输入格式

输入的第一行包含 $N$。  
第二行包含 $A_1,A_2,\ldots,A_N$。
## 输出格式

对于每一个 $j=0,1,\ldots,N-1$，用一行输出 Farmer John 头发的不良度。

-----

  
**注意这个问题涉及到的整数大小可能需要使用 $64$ 位整数型存储（例如，C/C++ 中的“long long”）。**
## 样例

### 样例输入 #1
```
5
5 2 3 3 0
```
### 样例输出 #1
```
0
4
4
5
7
```
## 提示

#### 样例解释：

输出的第四行描述了 Farmer John 的头发长度减少到 $3$ 时的逆序对数量。   
$A=[3,2,3,3,0]$ 有五个逆序对：$A_1>A_2,\,A_1>A_5,\,A_2>A_5,\,A_3>A_5,$ 和 $A_4>A_5$。

----

对于 $100\%$ 的数据，$1\le N\le 10^5$。

共 $13$ 个测试点，其中 $1$ 为样例，其余性质如下：
  
测试点 $2$ 满足 $N\le 100$。  
测试点 $3\sim 5$ 满足 $N\le 5000$。  
测试点 $6\sim 13$ 没有额外限制。  

-----


出题人：Dhruv Rohatgi



---

---
title: "[COCI 2011/2012 #1] SORT"
layout: "post"
diff: 普及+/提高
pid: P7629
tag: ['2011', '线段树', '树状数组', 'COCI（克罗地亚）']
---
# [COCI 2011/2012 #1] SORT
## 题目描述

考虑如下的排序算法：

```
reverse-sort(sequence a)
    while (a is not in nondecreasing order)
        partition a into the minimum number of slopes
        for every slope with length greater than one
            reverse(slope)
```

定义 `slope` 为 `a` 的递减子串，`reverse()` 将翻转一段序列。

给定一个 $1$ ~ $N$ 的排列，保证在第一次划分时每个 `slope` 的长度都为偶数，求如果使用这种排序算法对给定的排列进行排序，需要调用多少次 `reverse(slope)`。
## 输入格式

输入的第一行包含一个正整数 $N$。

第二行包含 $N$ 个互不相同的的正整数，代表待排序的排列。
## 输出格式

输出一行一个整数，表示 `reverse(slope)` 需要被调用的次数。
## 样例

### 样例输入 #1
```
2
2 1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
4
4 3 2 1
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
4
3 1 4 2
```
### 样例输出 #3
```
3
```
## 提示

#### 【数据范围】

对于 $100\%$ 的数据，$2 \le N \le 10^5$。

#### 【说明】

本题分值按 COCI 原题设置，满分 $140$。

题目译自 **[COCI2011-2012](https://hsin.hr/coci/archive/2011_2012/) [CONTEST #1](https://hsin.hr/coci/archive/2011_2012/contest1_tasks.pdf)** ___T5 SORT___。


---

---
title: "「EZEC-10」Shape"
layout: "post"
diff: 普及+/提高
pid: P7715
tag: ['树状数组', '排序']
---
# 「EZEC-10」Shape
## 题目背景

规定 $(x,y)$ 表示第 $x$ 行第 $y$ 列的格子。
## 题目描述

小 A 有一个 $n\times m$ 的网格，一些为白色格子，剩余为黑色格子。

小 A 选择四个整数 $x_1,x_2,y_1,y_2$，满足如下条件：

1. $1\le x_1<x_2\le n$ 且 $1\le y_1<y_2\le m$。
2. $x_1+x_2$ 为偶数。

若 $(x_1,y_1)\to (x_2,y_1),(x_1,y_2)\to (x_2,y_2),(\frac{x_1+x_2}{2},y_1)\to (\frac{x_1+x_2}{2},y_2)$ 这三段中的格子均为白色，则称这三段构成的图形为 H 形。

小 A 想知道，这个网格中存在多少不同的 H 形。

**两个 H 形相同，当且仅当两个 H 形的 $x_1,x_2,y_1,y_2$ 均相同。**
## 输入格式

第一行两个整数 $n,m$。

后 $n$ 行每行 $m$ 个整数表示网格，其中 $0$ 代表白色，$1$ 代表黑色。
## 输出格式

一个整数，表示不同 H 形的数量。
## 样例

### 样例输入 #1
```
3 4
1 0 0 0
1 1 0 0
1 0 0 0
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
5 3
0 1 0
0 1 0
0 0 0
0 1 0
0 1 0
```
### 样例输出 #2
```
2
```
## 提示

**【样例 1 解释】**

$(x_1,x_2,y_1,y_2)=(1,3,3,4)$ 的 H 形符合。

**【样例 2 解释】**

$(x_1,x_2,y_1,y_2)=(1,5,1,3),(2,4,1,3)$ 的 H 形符合。

**【数据规模与约定】**

**本题采用捆绑测试。**

- Subtask 1（1 point）：$n=2$。
- Subtask 2（9 points）：$ n,m\le 50$。
- Subtask 3（10 points）：$ n,m\le 100$，**时限为 $500ms$**。
- Subtask 4（30 points）：$ n,m\le 500$。
- Subtask 5（50 points）：无特殊限制。

对于 $100\%$ 的数据，$2\le n,m\le 2\times 10^3$。


---

---
title: "「Cfz Round 1」Elevator"
layout: "post"
diff: 普及+/提高
pid: P9579
tag: ['动态规划 DP', '贪心', '线段树', '树状数组', '洛谷原创', 'O2优化', '排序', '洛谷月赛']
---
# 「Cfz Round 1」Elevator
## 题目背景

电梯是一个可以让人充分思考的空间。
## 题目描述

给定两个长度为 $n$ 的数组 $a,b$。我们称序列 $p$ 是满足条件的，设 $p$ 的长度为 $m$，当且仅当：

- $p_1=1$；  
- 对于所有的 $1\le i<m$，都有 $|p_i-p_{i+1}|=1$；  
- 对于所有的 $1\le k\le n$，都存在一个有序数对 $(i,j)$，满足 $1 \le i < j \le m$ 且 $p_i=a_k$，$p_j=b_k$。

你需要输出所有满足条件的序列 $p$ 中，$p$ 的长度的最小值。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，第 $i$ 行两个整数 $a_i,b_i$。
## 输出格式

一个整数，表示所有满足条件的序列 $p$ 中，$p$ 的长度的最小值。
## 样例

### 样例输入 #1
```
2
3 2
2 5
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
4
4 7
10 8
9 11
4 2
```
### 样例输出 #2
```
18
```
## 提示

#### 【样例解释 #1】

序列 $p$ 的长度的最小值为 $7$，此时的序列 $p$ 为 $\{1,2,3,2,3,4,5\}$。

#### 【数据范围】

对于所有数据，$1 \le n \le 5\times10^5$，$1 \le a_i,b_i \le 10^9$，保证 $a_i \neq b_i$。

**本题采用捆绑测试。**

|子任务编号|分值|$n \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1$|$9$|$1$|无|
|$2$|$9$|$5\times10^5$|保证 $a_i < b_i$|
|$3$|$21$|$5\times10^5$|数据随机生成|
|$4$|$27$|$2000$|无|
|$5$|$34$|$5\times10^5$|无|


---

---
title: "「MXOI Round 2」队列"
layout: "post"
diff: 普及+/提高
pid: P9588
tag: ['线段树', '倍增', '二分', '平衡树', '树状数组', '单调队列', '洛谷原创', 'O2优化', '优先队列', '前缀和', '队列', '洛谷月赛']
---
# 「MXOI Round 2」队列
## 题目描述

小 C 有一个队列，他要对这个队列进行 $q$ 次操作。操作共四种，参数分别如下：

$1\ x$：这是第一种操作，表示从队尾依次插入 $1,2,3,\cdots,x$；

$2\ y$：这是第二种操作，表示弹出队头的前 $y$ 个元素；

$3\ z$：这是第三种操作，表示查询队列中的第 $z$ 个元素；

$4$：这是第四种操作，表示查询队列中所有元素的最大值。

你需要帮助他维护这个队列，并对于每个第三种操作和第四种操作，输出查询的答案。
## 输入格式

第一行两个整数 $c,q$，其中 $c$ 表示测试点编号。$c=0$ 表示该测试点为样例。

接下来 $q$ 行，每行 $1 \sim 2$ 个整数，表示一个操作，格式见【**题目描述**】。
## 输出格式

对于每个第三种操作和第四种操作，输出一行一个整数，表示查询的答案。
## 样例

### 样例输入 #1
```
0 9
1 5
1 3
2 2
1 4
3 6
3 8
2 4
4
3 3
```
### 样例输出 #1
```
3
2
4
1
```
## 提示

#### 【样例解释 #1】

在进行第四次操作后，队列中的元素依次为 $3,4,5,1,2,3,1,2,3,4$。

在进行第七次操作后，队列中的元素依次为 $2,3,1,2,3,4$。

#### 【样例 #2】

见附加文件中的 `queue/queue2.in` 与 `queue/queue2.ans`。

该样例满足测试点 $1$ 的限制。

#### 【样例 #3】

见附加文件中的 `queue/queue3.in` 与 `queue/queue3.ans`。

该样例满足测试点 $4$ 的限制。

#### 【样例 #4】

见附加文件中的 `queue/queue4.in` 与 `queue/queue4.ans`。

该样例满足测试点 $11$ 的限制。

#### 【样例 #5】

见附加文件中的 `queue/queue5.in` 与 `queue/queue5.ans`。

该样例满足测试点 $15$ 的限制。

#### 【样例 #6】

见附加文件中的 `queue/queue6.in` 与 `queue/queue6.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

设 $\sum x$ 表示单个测试点内 $x$ 之和。

对于 $100\%$ 的数据，$1 \le q \le 2\times 10^5$，$1 \le x,y,z \le 10^9$，$0 \le \sum x \le 2\times10^{14}$，保证在进行第二种操作前队列内元素个数不小于 $y$，在进行第三种操作前队列内元素个数不小于 $z$，在进行第四种操作前队列内元素个数大于 $0$。

|测试点编号|$q \le$|$x \le$|$\sum x \le$|特殊性质|
|:---:|:---:|:---:|:---:|:---:|
|$1\sim3$|$500$|$500$|$2\times10^5$|C|
|$4\sim8$|$5000$|$5000$|$2\times10^7$|无|
|$9\sim10$|$2\times10^5$|$10^9$|$2\times10^{14}$|AB|
|$11\sim12$|$2\times10^5$|$10^9$|$2\times10^{14}$|B|
|$13\sim14$|$2\times10^5$|$10^9$|$2\times10^9$|AC|
|$15\sim16$|$2\times10^5$|$10^9$|$2\times10^9$|C|
|$17\sim18$|$2\times10^5$|$500$|$2\times10^7$|无|
|$19$|$2\times10^5$|$10^9$|$2\times10^9$|无|
|$20$|$2\times10^5$|$10^9$|$2\times10^{14}$|无|

特殊性质 A：没有第二种操作。

特殊性质 B：没有第三种操作。

特殊性质 C：没有第四种操作。


---

