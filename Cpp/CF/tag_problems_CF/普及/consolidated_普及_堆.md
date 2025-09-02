---
title: "XOUR"
layout: "post"
diff: 普及/提高-
pid: CF1971G
tag: ['贪心', '堆', '位运算']
---

# XOUR

## 题目描述

You are given an array $ a $ consisting of $ n $ nonnegative integers.

You can swap the elements at positions $ i $ and $ j $ if $ a_i~\mathsf{XOR}~a_j < 4 $ , where $ \mathsf{XOR} $ is the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find the lexicographically smallest array that can be made with any number of swaps.

An array $ x $ is lexicographically smaller than an array $ y $ if in the first position where $ x $ and $ y $ differ, $ x_i < y_i $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 0 \leq a_i \leq 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers — the lexicographically smallest array that can be made with any number of swaps.

## 说明/提示

For the first test case, you can swap any two elements, so we can produce the sorted array.

For the second test case, you can swap $ 2 $ and $ 1 $ (their $ \mathsf{XOR} $ is $ 3 $ ), $ 7 $ and $ 5 $ (their $ \mathsf{XOR} $ is $ 2 $ ), and $ 7 $ and $ 6 $ (their $ \mathsf{XOR} $ is $ 1 $ ) to get the lexicographically smallest array.

## 样例 #1

### 输入

```
4
4
1 0 3 2
5
2 7 1 5 6
8
1 2 1 2 1 2 1 2
4
16 4 1 64
```

### 输出

```
0 1 2 3 
1 5 2 6 7 
1 1 1 1 2 2 2 2 
16 4 1 64
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

