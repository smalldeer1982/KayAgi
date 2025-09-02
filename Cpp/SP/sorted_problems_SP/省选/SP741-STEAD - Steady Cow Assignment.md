---
title: "STEAD - Steady Cow Assignment"
layout: "post"
diff: 省选/NOI-
pid: SP741
tag: []
---

# STEAD - Steady Cow Assignment

## 题目描述

Farmer John's N (1 <= N <= 1000) cows each reside in one of B (1 <= B <= 20) barns which, of course, have limited capacity. Some cows really like their current barn, and some are not so happy.

FJ would like to rearrange the cows such that the cows are as equally happy as possible, even if that means all the cows hate their assigned barn.

Each cow gives FJ the order in which she prefers the barns. A cow's happiness with a particular assignment is her ranking of her barn. Your job is to find an assignment of cows to barns such that no barn's capacity is exceeded and the size of the range (i.e., one more than the positive difference between the the highest-ranked barn chosen and that lowest-ranked barn chosen) of barn rankings the cows give their assigned barns is as small as possible.

## 输入格式

Line 1: Two space-separated integers, N and B

Lines 2..N+1: Each line contains B space-separated integers which are exactly 1..B sorted into some order. The first integer on line i+1 is the number of the cow i's top-choice barn, the second integer on that line is the number of the i'th cow's second-choice barn, and so on.

Line N+2: B space-separated integers, respectively the capacity of the first barn, then the capacity of the second, and so on. The sum of these numbers is guaranteed to be at least N.

## 输出格式

One integer, the size of the minimum range of barn rankings the cows give their assigned barns, including the endpoints

## 样例 #1

### 输入

```
6 4
1 2 3 4
2 3 1 4
4 2 3 1
3 1 2 4
1 3 4 2
1 4 2 3
2 1 3 2
```

### 输出

```
2
```

