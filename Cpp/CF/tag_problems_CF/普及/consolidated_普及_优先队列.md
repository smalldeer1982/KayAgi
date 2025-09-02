---
title: "Maximal Intersection"
layout: "post"
diff: 普及/提高-
pid: CF1029C
tag: ['贪心', '枚举', '优先队列']
---

# Maximal Intersection

## 题目描述

给定n个闭区间,现在要求从这些闭区间中删除一个区间，使得剩下的（n-1）个区间的交集的长度最大，求这个最大值。

（p.s.：若这个区间为空集或它的左端点与右端点重合，则长度为0；否则其长度为右端点在数轴上表示的数-左端点在数轴上表示的数）

## 输入格式

第一行输入一个正整数n（2<=n<=3e5）。

后面的n行中每行输入两个自然数l、r，表示一个闭区间[l,r]（0<=l<=r<=1e9）。

## 输出格式

输出一个数，表示这个最大值。

Translated by @lhy930

## 样例 #1

### 输入

```
4
1 3
2 6
0 4
3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
2 6
1 3
0 4
1 20
0 4

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3
4 5
1 2
9 20

```

### 输出

```
0

```

## 样例 #4

### 输入

```
2
3 10
1 5

```

### 输出

```
7

```



---

---
title: "Sharky Surfing"
layout: "post"
diff: 普及/提高-
pid: CF2037D
tag: ['贪心', '堆', '优先队列']
---

# Sharky Surfing

## 题目描述

Mualani 喜欢在她的大鲨鱼冲浪板上冲浪！

Mualani 的冲浪路径可以用一个数轴来表示。她从位置 $1$ 开始，路径的终点是位置 $L$。当她处于位置 $x$ 且跳跃能力为 $k$ 时，她可以跳到区间 $[x, x+k]$ 内的任意整数位置。最初，她的跳跃能力为 $1$。

然而，她的冲浪路径并不完全平坦。她的路径上有 $n$ 个障碍物。每个障碍物由一个区间 $[l, r]$ 表示，意味着她不能跳到区间 $[l, r]$ 内的任何位置。

在路径上还有 $m$ 个能量提升点。第 $i$ 个能量提升点位于位置 $x_i$，其值为 $v_i$。当 Mualani 处于位置 $x_i$ 时，她可以选择收集该能量提升点，将她的跳跃能力增加 $v_i$。在同一个位置可能有多个能量提升点。当她处于有多个能量提升点的位置时，她可以选择收集或忽略每个单独的能量提升点。没有能量提升点位于任何障碍物的区间内。

Mualani 必须收集最少的能量提升点数才能到达位置 $L$ 完成冲浪路径。如果无法完成冲浪路径，则输出 $-1$。

## 输入格式

第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$) — 测试用例的数量。

每个测试用例的第一行包含三个整数 $n$, $m$, 和 $L$ ($1 \leq n, m \leq 2 \cdot 10^5, 3 \leq L \leq 10^9$) — 障碍物的数量，能量提升点的数量，以及终点的位置。

接下来的 $n$ 行每行包含两个整数 $l_i$ 和 $r_i$ ($2 \leq l_i \leq r_i \leq L-1$) — 第 $i$ 个障碍物的区间边界。保证对于所有 $1 \leq i < n$，有 $r_i + 1 < l_{i+1}$（即所有障碍物都是非重叠的，按递增位置排序，并且前一个障碍物的终点与下一个障碍物的起点不连续）。

接下来的 $m$ 行每行包含两个整数 $x_i$ 和 $v_i$ ($1 \leq x_i, v_i \leq L$) — 第 $i$ 个能量提升点的位置和值。在所有测试用例中，能量提升点的数量总和不超过 $2 \cdot 10^5$。保证对于所有 $1 \leq i < m$，有 $x_i \leq x_{i+1}$（即能量提升点按非递减位置排序），并且没有能量提升点位于任何障碍物的区间内。

## 输出格式

对于每个测试用例，输出她必须收集的最少能量提升点数才能到达位置 $L$。如果无法完成，则输出 $-1$。

## 样例 #1

### 输入

```
4
2 5 50
7 14
30 40
2 2
3 1
3 5
18 2
22 32
4 3 50
4 6
15 18
20 26
34 38
1 2
8 2
10 2
1 4 17
10 14
1 6
1 2
1 2
16 9
1 2 10
5 9
2 3
2 2
```

### 输出

```
4
-1
1
2
```



---

---
title: "Merge Equals"
layout: "post"
diff: 普及/提高-
pid: CF962D
tag: ['排序', '优先队列', '队列']
---

# Merge Equals

## 题目描述

You are given an array of positive integers. While there are at least two equal elements, we will perform the following operation. We choose the smallest value $ x $ that occurs in the array $ 2 $ or more times. Take the first two occurrences of $ x $ in this array (the two leftmost occurrences). Remove the left of these two occurrences, and the right one is replaced by the sum of this two values (that is, $ 2 \cdot x $ ).

Determine how the array will look after described operations are performed.

For example, consider the given array looks like $ [3, 4, 1, 2, 2, 1, 1] $ . It will be changed in the following way: $ [3, 4, 1, 2, 2, 1, 1]~\rightarrow~[3, 4, 2, 2, 2, 1]~\rightarrow~[3, 4, 4, 2, 1]~\rightarrow~[3, 8, 2, 1] $ .

If the given array is look like $ [1, 1, 3, 1, 1] $ it will be changed in the following way: $ [1, 1, 3, 1, 1]~\rightarrow~[2, 3, 1, 1]~\rightarrow~[2, 3, 2]~\rightarrow~[3, 4] $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 150\,000 $ ) — the number of elements in the array.

The second line contains a sequence from $ n $ elements $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{9} $ ) — the elements of the array.

## 输出格式

In the first line print an integer $ k $ — the number of elements in the array after all the performed operations. In the second line print $ k $ integers — the elements of the array after all the performed operations.

## 说明/提示

The first two examples were considered in the statement.

In the third example all integers in the given array are distinct, so it will not change.

## 样例 #1

### 输入

```
7
3 4 1 2 2 1 1

```

### 输出

```
4
3 8 2 1 

```

## 样例 #2

### 输入

```
5
1 1 3 1 1

```

### 输出

```
2
3 4 

```

## 样例 #3

### 输入

```
5
10 40 20 50 30

```

### 输出

```
5
10 40 20 50 30 

```



---

