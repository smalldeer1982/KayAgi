---
title: "Big Segment"
layout: "post"
diff: 入门
pid: CF242B
tag: []
---

# Big Segment

## 题目描述

A coordinate line has $ n $ segments, the $ i $ -th segment starts at the position $ l_{i} $ and ends at the position $ r_{i} $ . We will denote such a segment as $ [l_{i},r_{i}] $ .

You have suggested that one of the defined segments covers all others. In other words, there is such segment in the given set, which contains all other ones. Now you want to test your assumption. Find in the given set the segment which covers all other segments, and print its number. If such a segment doesn't exist, print -1.

Formally we will assume that segment $ [a,b] $ covers segment $ [c,d] $ , if they meet this condition $ a<=c<=d<=b $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of segments. Next $ n $ lines contain the descriptions of the segments. The $ i $ -th line contains two space-separated integers $ l_{i},r_{i} $ ( $ 1<=l_{i}<=r_{i}<=10^{9} $ ) — the borders of the $ i $ -th segment.

It is guaranteed that no two segments coincide.

## 输出格式

Print a single integer — the number of the segment that covers all other segments in the set. If there's no solution, print -1.

The segments are numbered starting from $ 1 $ in the order in which they appear in the input.

## 样例 #1

### 输入

```
3
1 1
2 2
3 3

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
6
1 5
2 3
1 10
7 10
7 7
10 10

```

### 输出

```
3

```

