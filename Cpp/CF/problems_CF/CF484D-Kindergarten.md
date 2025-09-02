---
title: "Kindergarten"
layout: "post"
diff: 提高+/省选-
pid: CF484D
tag: ['动态规划 DP', '贪心']
---

# Kindergarten

## 题目描述

In a kindergarten, the children are being divided into groups. The teacher put the children in a line and associated each child with his or her integer charisma value. Each child should go to exactly one group. Each group should be a nonempty segment of consecutive children of a line. A group's sociability is the maximum difference of charisma of two children in the group (in particular, if the group consists of one child, its sociability equals a zero).

The teacher wants to divide the children into some number of groups in such way that the total sociability of the groups is maximum. Help him find this value.

## 输入格式

The first line contains integer $n$ — the number of children in the line ($1\le n\le 10^6$).

The second line contains $n$ integers $a_i$ — the charisma of the $i$-th child ($-10^9\le a_i\le 10^9$).

## 输出格式

Print the maximum possible total sociability of all groups.

## 说明/提示

In the first test sample one of the possible variants of an division is following: the first three children form a group with sociability 2, and the two remaining children form a group with sociability 1.

In the second test sample any division leads to the same result, the sociability will be equal to 0 in each group.

## 样例 #1

### 输入

```
5
1 2 3 1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
3 3 3

```

### 输出

```
0

```

