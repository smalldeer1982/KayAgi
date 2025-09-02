---
title: "三只小猪"
layout: "post"
diff: 普及+/提高
pid: P3904
tag: ['高精度', '递推', '组合数学', '排列组合', '线性递推']
---
# 三只小猪
## 题目背景

你听说过三只小猪的故事吗？这是一个经典的故事。很久很久以前，有三只小猪。第一只小猪用稻草建的房子，第二个小猪用木棍建的房子，第三个小猪则使用砖做为材料。一只大灰狼想吃掉它们并吹倒了稻草和木棍建的房子。但是砖盖的房子很结实，狼最终也没有破坏掉，最后小猪们战胜了大灰狼并把它尾巴烧掉了。

## 题目描述

为了自己的安全，小猪们又建造了一个新砖房。但是现在问题出现了，怎样把三个小猪分配到两个房子里呢？第三只小猪是三只小猪中最聪明的一只，为了不浪费任何一个房子，它总共考虑了三种方案，如下图

 ![](https://cdn.luogu.com.cn/upload/pic/6862.png) 

“但是将来怎么办呢？”第三只小猪知道将来随着成员的增多，它们将会盖更多的房子。它想知道给定了房子和猪的数目后，房子的分配方案有多少，但这个问题对于它来说，很明显有点难了，你能帮小猪解决这个问题吗？

## 输入格式

输入文件piggy.in，仅有一行，包含两个整数n和m，分别表示小猪的数目和房间数（1≤n≤50，0≤m≤50）。

## 输出格式

输出文件piggy.out，仅一个整数，表示将n只小猪安置在m个房间且没有房间空闲的方案数。

## 样例

### 样例输入 #1
```
4 2
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
6 7
```
### 样例输出 #2
```
0
```


---

---
title: "[USACO23FEB] Equal Sum Subarrays G"
layout: "post"
diff: 普及+/提高
pid: P9127
tag: ['USACO', '2023', '排序', '线性递推']
---
# [USACO23FEB] Equal Sum Subarrays G
## 题目描述

**Note: The time limit for this problem is 3s, 1.5x the default.** 

FJ gave Bessie an array $a$ of length $N(2 \le N \le 500,−10^{15} \le a_i \le 10^{15})$ with all $\dfrac{N(N+1)}{2}$ contiguous subarray sums distinct. For each index $i \in [1,N]$, help Bessie compute the minimum amount it suffices to change ai by so that there are two different contiguous subarrays of a with equal sum. 
## 输入格式

The first line contains $N$.

The next line contains $a_1, \cdots ,a_N$
(the elements of $a$, in order). 
## 输出格式

One line for each index $i \in [1,N]$. 
## 样例

### 样例输入 #1
```
2
2 -3
```
### 样例输出 #1
```
2
3
```
### 样例输入 #2
```
3
3 -10 4
```
### 样例输出 #2
```
1
6
1
```
## 提示

### Explanation for Sample 1

Decreasing $a_1$ by $2$ would result in $a_1+a_2=a_2$. Similarly, increasing $a_2$ by $3$ would result in $a_1+a_2=a_1$. 

### Explanation for Sample 2

Increasing a1 or decreasing $a_3$ by $1$ would result in $a_1=a_3$. Increasing $a_2$ by $6$ would result in $a_1=a_1+a_2+a_3$. 

### SCORING

 - Input $3$: $N \le 40$
 - Input $4$: $N \le 80$
 - Inputs $5-7$: $N \le 200$
 - Inputs 8-16: No additional constraints.
## 题目翻译

### 题目描述

注意：本题的时间限制为 3 秒，为默认时间的 1.5 倍。

FJ 给了 Bessie 一个长度为 $N$ 的数组 $a$（$2 \leq N \leq 500, -10^{15} \leq a_i \leq 10^{15}$），其中所有 $\dfrac{N(N+1)}{2}$ 个连续子数组的和都是不同的。对于每个下标 $i \in [1,N]$，帮助 Bessie 计算最小的改变量，使得数组中存在两个不同的连续子数组的和相等。

### 输入格式

第一行包含一个整数 $N$，表示数组的长度。

第二行包含 $a_1,\cdots,a_N$，即数组 $a$ 的元素，按顺序给出。

### 输出格式

对于每个下标 $i \in [1,N]$，输出一行一个整数，表示改变 $a_i$ 的最小改变量。

### 样例 1 的解释

将 $a_1$ 减少 $2$，可以使得 $a_1+a_2=a_2$。类似地，将 $a_2$ 增加 $3$，可以使得 $a_1+a_2=a_1$。

### 样例 2 的解释

将 $a_1$ 增加 $1$ 或将 $a_3$ 减少 $1$，可以使得 $a_1=a_3$。将 $a_2$ 增加 $6$，可以使得 $a_1=a_1+a_2+a_3$。

### 评分标准

- 测试点 $3$：$N \leq 40$
- 测试点 $4$：$N \leq 80$
- 测试点 $5-7$：$N \leq 200$
- 测试点 $8-16$：无额外限制。


---

