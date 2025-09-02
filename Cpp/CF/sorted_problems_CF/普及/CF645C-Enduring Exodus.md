---
title: "Enduring Exodus"
layout: "post"
diff: 普及/提高-
pid: CF645C
tag: []
---

# Enduring Exodus

## 题目描述

In an attempt to escape the Mischievous Mess Makers' antics, Farmer John has abandoned his farm and is traveling to the other side of Bovinia. During the journey, he and his $ k $ cows have decided to stay at the luxurious Grand Moo-dapest Hotel. The hotel consists of $ n $ rooms located in a row, some of which are occupied.

Farmer John wants to book a set of $ k+1 $ currently unoccupied rooms for him and his cows. He wants his cows to stay as safe as possible, so he wishes to minimize the maximum distance from his room to the room of his cow. The distance between rooms $ i $ and $ j $ is defined as $ |j-i| $ . Help Farmer John protect his cows by calculating this minimum possible distance.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=k&lt;n<=100000 $ ) — the number of rooms in the hotel and the number of cows travelling with Farmer John.

The second line contains a string of length $ n $ describing the rooms. The $ i $ -th character of the string will be '0' if the $ i $ -th room is free, and '1' if the $ i $ -th room is occupied. It is guaranteed that at least $ k+1 $ characters of this string are '0', so there exists at least one possible choice of $ k+1 $ rooms for Farmer John and his cows to stay in.

## 输出格式

Print the minimum possible distance between Farmer John's room and his farthest cow.

## 说明/提示

In the first sample, Farmer John can book room $ 3 $ for himself, and rooms $ 1 $ and $ 4 $ for his cows. The distance to the farthest cow is $ 2 $ . Note that it is impossible to make this distance $ 1 $ , as there is no block of three consecutive unoccupied rooms.

In the second sample, Farmer John can book room $ 1 $ for himself and room $ 3 $ for his single cow. The distance between him and his cow is $ 2 $ .

In the third sample, Farmer John books all three available rooms, taking the middle room for himself so that both cows are next to him. His distance from the farthest cow is $ 1 $ .

## 样例 #1

### 输入

```
7 2
0100100

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 1
01010

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 2
000

```

### 输出

```
1

```

