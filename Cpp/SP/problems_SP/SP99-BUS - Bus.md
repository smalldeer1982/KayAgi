---
title: "BUS - Bus"
layout: "post"
diff: 难度0
pid: SP99
tag: []
---

# BUS - Bus

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP99/5d325264e1a9fb4c47600ca0cdf0153be045b4e1.png)The city Buscelona (as the name suggests) has a great bus transport system. All buses have circular lines. The bus drivers in Buscelona like to chat. Fortunately most bus lines have some stops in common. If a bus driver meets a colleague on a bus stop they chat a bit and exchange all news they know.

The operation of buses is highly synchronized. The time necessary to get from one stop to the next stop is always exactly 1 minute.

Each morning each bus driver has some important news that only he knows. When a busdriver meets a colleague he will tell him all news he knows. If two bus drivers share the same start station, they will exchange their news there already (before they start working). Note that exchanging news and stopping does not take any time.

## 输入格式

The first line of a test case contains the number of bus lines _n_ (0 < _n_ < 50). The following _n_ lines start with a number _s_ (0 < _s_ < 50) indicating the stops of a busline. On the same line follow _s_ numbers representing a bus station each. A bus starts at the first station. When a bus reaches the last station, the bus will drive to the first station again.

There are many test cases separated by an empty line. Input data terminates with _n_ = 0.

## 输出格式

For each test case you should output the time in minutes which it takes until all bus drivers know all news. If that never happens, your program should write the word "NEVER" (without quotes).

## 样例 #1

### 输入

```
3
3 1 2 3
3 2 3 1
4 2 3 4 5

2
2 1 2
2 5 8

0
```

### 输出

```
12
NEVER
```

