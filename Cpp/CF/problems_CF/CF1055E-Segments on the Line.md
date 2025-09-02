---
title: "Segments on the Line"
layout: "post"
diff: 省选/NOI-
pid: CF1055E
tag: []
---

# Segments on the Line

## 题目描述

You are a given a list of integers $ a_1, a_2, \ldots, a_n $ and $ s $ of its segments $ [l_j; r_j] $ (where $ 1 \le l_j \le r_j \le n $ ).

You need to select exactly $ m $ segments in such a way that the $ k $ -th order statistic of the multiset of $ a_i $ , where $ i $ is contained in at least one segment, is the smallest possible. If it's impossible to select a set of $ m $ segments in such a way that the multiset contains at least $ k $ elements, print -1.

The $ k $ -th order statistic of a multiset is the value of the $ k $ -th element after sorting the multiset in non-descending order.

## 输入格式

The first line contains four integers $ n $ , $ s $ , $ m $ and $ k $ ( $ 1 \le m \le s \le 1500 $ , $ 1 \le k \le n \le 1500 $ ) — the size of the list, the number of segments, the number of segments to choose and the statistic number.

The second line contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 10^9 $ ) — the values of the numbers in the list.

Each of the next $ s $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — the endpoints of the segments.

It is possible that some segments coincide.

## 输出格式

Print exactly one integer — the smallest possible $ k $ -th order statistic, or -1 if it's impossible to choose segments in a way that the multiset contains at least $ k $ elements.

## 说明/提示

In the first example, one possible solution is to choose the first and the third segment. Together they will cover three elements of the list (all, except for the third one). This way the $ 2 $ -nd order statistic for the covered elements is $ 2 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1055E/be333fc67d60280dc550835545d694b9e06ec26a.png)

## 样例 #1

### 输入

```
4 3 2 2
3 1 3 2
1 2
2 3
4 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 2 1 1
1 2 3 4 5
2 4
1 5

```

### 输出

```
1

```

## 样例 #3

### 输入

```
5 3 3 5
5 5 2 1 1
1 2
2 3
3 4

```

### 输出

```
-1

```

