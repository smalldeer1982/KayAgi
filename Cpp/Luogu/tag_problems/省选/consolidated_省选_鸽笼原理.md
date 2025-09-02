---
title: "[GCJ 2012 #1B] Equal Sums"
layout: "post"
diff: 省选/NOI-
pid: P13320
tag: ['2012', 'Special Judge', '鸽笼原理', '概率论', 'Google Code Jam']
---
# [GCJ 2012 #1B] Equal Sums
## 题目描述

I have a set of positive integers $\mathbf{S}$. Can you find two non-empty, distinct subsets with the same sum?

Note: A subset is a set that contains only elements from $\mathbf{S}$, and two subsets are distinct if they do not have exactly the same elements.

## 输入格式

he first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow, one per line. Each test case begins with $\mathbf{N}$, the number of positive integers in $\mathbf{S}$. It is followed by $\mathbf{N}$ distinct positive integers, all on the same line.

## 输出格式

For each test case, first output one line containing "Case #x:", where $\mathbf{x}$ is the case number (starting from 1).

* If there are two different subsets of $\mathbf{S}$ that have the same sum, then output these subsets, one per line. Each line should contain the numbers in one subset, separated by spaces.
* If it is impossible, then you should output the string "Impossible" on a single line.

If there are multiple ways of choosing two subsets with the same sum, any choice is acceptable.
## 样例

### 样例输入 #1
```
2
20 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 120 266 858 1243 1657 1771 2328 2490 2665 2894 3117 4210 4454 4943 5690 6170 7048 7125 9512 9600
```
### 样例输出 #1
```
Case #1: Possible
Case #2: Possible
```
## 提示

**Limits**

- No two numbers in $\mathbf{S}$ will be equal.
- $1 \leq \mathbf{T} \leq 10$.

**Test set 1 (6 Pts, Visible Verdict)**

- Time limit: ~~60~~ 12 seconds.
- $\mathbf{N}$ is exactly equal to $20$.
- Each number in $\mathbf{S}$ will be a positive integer less than $10^5$.

**Test set 2 (37 Pts, Hidden Verdict)**

- Time limit: ~~120~~ 24 seconds.
- $\mathbf{N}$ is exactly equal to $500$.
- Each number in $\mathbf{S}$ will be a positive integer less than $10^{12}$.


---

