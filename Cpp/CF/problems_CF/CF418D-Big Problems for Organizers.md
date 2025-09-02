---
title: "Big Problems for Organizers"
layout: "post"
diff: 省选/NOI-
pid: CF418D
tag: []
---

# Big Problems for Organizers

## 题目描述

The Finals of the "Russian Code Cup" 2214 will be held in $ n $ hotels. Two hotels (let's assume that they are the main hotels), will host all sorts of events, and the remaining hotels will accommodate the participants. The hotels are connected by $ n-1 $ roads, you can get from any hotel to any other one.

The organizers wonder what is the minimum time all the participants need to get to the main hotels, if each participant goes to the main hotel that is nearest to him and moving between two hotels connected by a road takes one unit of time.

The hosts consider various options for the location of the main hotels. For each option help the organizers to find minimal time.

## 输入格式

The first line contains an integer $ n $ ( $ 2<=n<=100000 $ ) — the number of hotels. The next $ n-1 $ lines contain two integers each — the numbers of the hotels that have a road between them. Consider hotels are numbered from $ 1 $ to $ n $ .

The next line contains an integer $ m $ ( $ 1<=m<=100000 $ ) — the number of queries. The following $ m $ lines contains two distinct integers each — the numbers of the hotels we assume to be the main.

## 输出格式

For each request of the organizers print a single integer — the time that all participants need to reach the main hotels.

## 样例 #1

### 输入

```
3
2 3
3 1
3
2 1
2 3
3 1

```

### 输出

```
1
1
1

```

## 样例 #2

### 输入

```
4
1 4
1 2
2 3
3
1 4
1 3
2 3

```

### 输出

```
2
1
2

```

