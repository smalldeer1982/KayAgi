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

