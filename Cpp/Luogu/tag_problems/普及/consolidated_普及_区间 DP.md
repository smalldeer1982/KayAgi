---
title: "石子合并（弱化版）"
layout: "post"
diff: 普及/提高-
pid: P1775
tag: ['动态规划 DP', '区间 DP']
---
# 石子合并（弱化版）
## 题目描述

设有 $N(N \le 300)$ 堆石子排成一排，其编号为 $1,2,3,\cdots,N$。每堆石子有一定的质量 $m_i\ (m_i \le 1000)$。现在要将这 $N$ 堆石子合并成为一堆。每次只能合并相邻的两堆，合并的代价为这两堆石子的质量之和，合并后与这两堆石子相邻的石子将和新堆相邻。合并时由于选择的顺序不同，合并的总代价也不相同。试找出一种合理的方法，使总的代价最小，并输出最小代价。
## 输入格式

第一行，一个整数 $N$。

第二行，$N$ 个整数 $m_i$。
## 输出格式

输出文件仅一个整数，也就是最小代价。

## 样例

### 样例输入 #1
```
4
2 5 3 1
```
### 样例输出 #1
```
22
```


---

---
title: "[USACO06FEB] Treats for the Cows G/S"
layout: "post"
diff: 普及/提高-
pid: P2858
tag: ['动态规划 DP', '2006', 'USACO', '区间 DP']
---
# [USACO06FEB] Treats for the Cows G/S
## 题目描述

FJ has purchased N (1 <= N <= 2000) yummy treats for the cows who get money for giving vast amounts of milk. FJ sells one treat per day and wants to maximize the money he receives over a given period time.


The treats are interesting for many reasons:The treats are numbered 1..N and stored sequentially in single file in a long box that is open at both ends. On any day, FJ can retrieve one treat from either end of his stash of treats.Like fine wines and delicious cheeses, the treats improve with age and command greater prices.The treats are not uniform: some are better and have higher intrinsic value. Treat i has value v(i) (1 <= v(i) <= 1000).Cows pay more for treats that have aged longer: a cow will pay v(i)\*a for a treat of age a.Given the values v(i) of each of the treats lined up in order of the index i in their box, what is the greatest value FJ can receive for them if he orders their sale optimally?


The first treat is sold on day 1 and has age a=1. Each subsequent day increases the age by 1.

约翰经常给产奶量高的奶牛发特殊津贴，于是很快奶牛们拥有了大笔不知该怎么花的钱。为此，约翰购置了 $N$（$1 \leq N \leq 2000$） 份美味的零食来卖给奶牛们。每天约翰售出一份零食。当然约翰希望这些零食全部售出后能得到最大的收益，这些零食有以下这些有趣的特性：
+ 零食按照 $1, \ldots, N$ 编号，它们被排成一列放在一个很长的盒子里。盒子的两端都有开口，约翰每天可以从盒子的任一端取出最外面的一个。
+ 与美酒与好吃的奶酪相似，这些零食储存得越久就越好吃。当然，这样约翰就可以把它们卖出更高的价钱。
+ 每份零食的初始价值不一定相同。约翰进货时，第i份零食的初始价值为 $V_i$（$1 \leq V \leq 1000$）。
+ 第i份零食如果在被买进后的第 $a$ 天出售，则它的售价是 $V_i \times a$。

$V_i$ 的是从盒子顶端往下的第i份零食的初始价值。约翰告诉了你所有零食的初始价值，并希望你能帮他计算一下，在这些零食全被卖出后，他最多能得到多少钱。
## 输入格式

Line 1: A single integer, N

Lines 2..N+1: Line i+1 contains the value of treat v(i)

## 输出格式

Line 1: The maximum revenue FJ can achieve by selling the treats

## 样例

### 样例输入 #1
```
5
1
3
1
5
2
```
### 样例输出 #1
```
43
```
## 提示

Explanation of the sample:




Five treats. On the first day FJ can sell either treat #1 (value 1) or treat #5 (value 2).




FJ sells the treats (values 1, 3, 1, 5, 2) in the following order of indices: 1, 5, 2, 3, 4, making 1x1 + 2x2 + 3x3 + 4x1 + 5x5 = 43.



---

---
title: "[CCC 2023 S2] Symmetric Mountains"
layout: "post"
diff: 普及/提高-
pid: P9325
tag: ['模拟', '2023', '枚举', 'CCC（加拿大）', '区间 DP', '双指针 two-pointer']
---
# [CCC 2023 S2] Symmetric Mountains
## 题目描述

Rebecca is a tour guide and is trying to market the Rocky Mountains for her magazine. She recently took a beautiful picture consisting of $N$ mountains where the $i\text{-th}$ mountain from the left has a height $h_i$. She will crop this picture for her magazine, by possibly removing some mountains from the left side of the picture and possibly removing some mountains from the right side of the picture. That is, a crop consists of consecutive mountains starting from the $l\text{-th}$ to the $r\text{-th}$ mountain where $l \leq r$. To please her magazine readers, Rebecca will try to find the most symmetric crop.

We will measure the $asymmetric\ value$ of a crop as the sum of the absolute difference for every pair of mountains equidistant from the midpoint of the crop. To help understand that definition, note that the absolute value of $a$ number $v$, written as $|v|$, is the non-negative value of v: for example $\lvert -6 \rvert = 6$ and $|14| = 14$. The asymmetric value of a crop is the sum of all $|h_{l+i} - h_{r-i}|$ for $0 \leq i \leq \frac{r-l}{2}$. To put that formula in a different way, we pair up the mountains working from the outside in toward the centre, calculate the absolute difference in height of each of these pairs, and sum them up.

Because Rebecca does not know how wide the picture needs to be, for all possible crop lengths, find the asymmetric value of the most symmetric crop (the crop with the minimum asymmetric value).
## 输入格式

The first line consists of an integer $N$, representing the number of mountains in the picture.

The second line consists of $N$ space-separated integers, where the $i\text{-th}$ integer from the left represents $h_i$.

The following table shows how the available 15 marks are distributed:

| Marks | Bounds on $N$ | Bounds on $h_i$ | Additional Constraints |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $5$ | $1 \leq N \leq 300$ | $0 \leq h_i \leq 10^5$ | None. |
| $5$ | $1 \leq N \leq 5000$ | $0 \leq h_i \leq 10^5$ | Height of mountains are in non-decreasing order from left to right. |
| $5$ | $1 \leq N \leq 5000$ | $0 \leq h_i \leq 10^5$ | None. |

## 输出格式

Output on one line $N$ space-separated integers, where the $i\text{-th}$ integer from the left is the asymmetric value of the most symmetric picture of crops of length $i$.
## 样例

### 样例输入 #1
```
7
3 1 4 1 5 9 2
```
### 样例输出 #1
```
0 2 0 5 2 10 10
```
### 样例输入 #2
```
4
1 3 5 6
```
### 样例输出 #2
```
0 1 3 7
```
## 提示

Explanation of Output for Sample Input $1$:

We will show why the fifth value from the left is $2$.Let us try to compute all the asymmetric values of crops with length $5$.

The height of the mountains in the first crop is $[3, 1, 4, 1, 5]$. The asymmetric value of this crop is $|3 - 5| + |1 - 1| + |4 - 4| = 2$.

The height of the mountains in the second crop is $[1, 4, 1, 5, 9]$. The asymmetric value of this crop is $|1 - 9| + |4 - 5| + |1 - 1| = 9$.

The height of the mountains in the last crop is $[4, 1, 5, 9, 2]$. The asymmetric value of this crop is $|4 - 2| + |1 - 9| + |5 - 5| = 10$.

Hence, the most symmetric crop of length $5$ is $2$.

Explanation of Output for Sample Input $2$:

This sample satisfies the second subtask. Note that the only crop of length $4$ is $[1, 3, 5, 6]$ which has asymmetric value of $|1 - 6| + |3 - 5| = 7$.

**本题采用捆绑测试**：

- Subtask 1（5 points）：$1\leq N \leq 300$，$0\leq h_i \leq 10^5$。

- Subtask 2（5 points）：$1 \leq N \leq 5000$，$0 \leq h_i \leq 10^5$，保证山的高度从左到右单调不减。

- Subtask 3（5 points）：$1\leq N\leq 5000$，$0 \leq h_i \leq 10^5$。
## 题目翻译

Rebecca 有一张落基山脉的照片，上面排列着 $N(1\leq N \leq 5000)$ 座山，从左向右的第 $i$ 座山的高度是 $h_i(1\leq h_i \leq 10^5)$。Rebecca 截图保留照片的一个连续段，这张截图的不对称性定义为：处于截图上对称位置的山的高度差的绝对值之和（截图最左和最右的山的高度差，左数第二和右数第二的山的高度差，诸如此类的和）。

Rebecca 想要知道对于长度为 $i$ 的截图，拥有的最小不对称性。请你对于 $1\leq i \leq N$，输出这个值。


---

