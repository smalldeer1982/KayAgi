---
title: "GLASNICI - Glasnici"
layout: "post"
diff: 提高+/省选-
pid: SP2715
tag: []
---

# GLASNICI - Glasnici

## 题目描述

A long straight road connects two villages. Along the road, N messengers are stationed and, when needed, they exchange messages using mostly their legs, but also their vocal cords and ears. The first messenger (the closest to the first village) has a radio-receiver which he uses to keep track of current ongoings in the country. When he finds out who has been evicted from whichever reality show is currently popular, he starts running as fast as he can to share the unfortunate (or fortunate) news with everyone else. While running, he shouts the name of the evicted person so that any fellow messengers that are close enough can hear him. Meanwhile, the remaining messengers do not merely sit and wait, but also run themselves, all with the selfless goal of sharing the news with everyone as fast as possible. The running and shouting proceeds as follows:

- Each of the messengers may run whenever, in either direction, at a speed of at most 1 unit per second, or may decide not to run at all and stand still.
- All messengers that know the news shout it at all times. One messenger can hear another messenger shouting (and learn the news) if the distance between them is at most K units.

Write a program that, given the initial locations of the messengers, determines the least amount of time (in seconds) needed for all messengers to learn the news. The location of every messenger is given with a positive real number – the distance from the first village. As mentioned above, initially only the first messenger knows the news.

## 输入格式

The first line contains the integer T (1 ≤ T ≤ 25), the number of test cases. Then for each test case, the first line contains the real number K (0 ≤ K ≤ 1,000,000), the largest distance at which two messengers can hear each other, and the integer N (1 ≤ N ≤ 100,000), the number of messengers. Each of the following N lines contains one real number D (0 ≤ D ≤ 1,000,000,000), the distance of one messenger from the first village. The distances will be sorted in ascending order. It is possible for multiple messengers to be at the same location.

## 输出格式

For each test case, output a real number, the least time for all messengers to learn the news. Your output needs to be within 0.01 of the official output.

## 样例 #1

### 输入

```
2
3.000 2
0.000
6.000
2.000 4
0.000
4.000
4.000
8.000
```

### 输出

```
1.500
1.000
```

