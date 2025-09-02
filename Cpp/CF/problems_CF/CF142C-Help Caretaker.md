---
title: "Help Caretaker"
layout: "post"
diff: 提高+/省选-
pid: CF142C
tag: []
---

# Help Caretaker

## 题目描述

Autumn came late to the kingdom of Far Far Away. The harvest was exuberant and it is now time to get ready for the winter. As most people celebrate the Harvest festival, Simon the Caretaker tries to solve a very non-trivial task of how to find place for the agricultural equipment in the warehouse.

He's got problems with some particularly large piece of equipment, which is, of course, turboplows. The problem is that when a turboplow is stored, it takes up not some simply rectangular space. It takes up a T-shaped space like on one of the four pictures below (here character "\#" stands for the space occupied by the turboplow and character "." stands for the free space):

   `###      ..#      .#.      #..<br></br>.#.      ###      .#.      ###<br></br>.#.      ..#      ###      #..<br></br>`  Simon faced a quite natural challenge: placing in the given $ n×m $ cells warehouse the maximum number of turboplows. As one stores the turboplows, he can rotate them in any manner (so that they take up the space like on one of the four pictures above). However, two turboplows cannot "overlap", that is, they cannot share the same cell in the warehouse.

Simon feels that he alone cannot find the optimal way of positioning the plugs in the warehouse that would maximize their quantity. Can you help him?

## 输入格式

The only line contains two space-separated integers $ n $ and $ m $ — the sizes of the warehouse ( $ 1<=n,m<=9 $ ).

## 输出格式

In the first line print the maximum number of turboplows that can be positioned in the warehouse. In each of the next $ n $ lines print $ m $ characters. Use "." (dot) to mark empty space and use successive capital Latin letters ("A" for the first turboplow, "B" for the second one and so on until you reach the number of turboplows in your scheme) to mark place for the corresponding turboplows considering that they are positioned in the optimal manner in the warehouse. The order in which you number places for the turboplows does not matter. If there are several optimal solutions for a warehouse of the given size, print any of them.

## 样例 #1

### 输入

```
3 3

```

### 输出

```
1
AAA
.A.
.A.

```

## 样例 #2

### 输入

```
5 6

```

### 输出

```
4
A..C..
AAAC..
ABCCCD
.B.DDD
BBB..D

```

## 样例 #3

### 输入

```
2 2

```

### 输出

```
0
..
..

```

