---
title: "神龙喝水 Enter The Dragon"
layout: "post"
diff: 省选/NOI-
pid: UVA1623
tag: []
---

# 神龙喝水 Enter The Dragon

## 题目描述

# 神龙喝水 Enter The Dragon


[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4498

[PDF](https://uva.onlinejudge.org/external/16/p1623.pdf)

The capital of Ardenia is surrounded by several lakes, and each of them is initially full of water.
Currently, heavy rainfalls are expected over the land. Such a rain falls to one of the lakes: if the lake is
dry and empty, then it will be filled with water; if the lake is already full, then it will overflow, which
will result in a natural disaster. Fortunately, the citizens have a dragon at their disposal (and they
will not hesitate to use it). The dragon may drink the whole water from a lake in one sitting. Also,
the mages of Ardenia already predicted the weather conditions for the next couple of years. The only
question is: from which lake and when should the dragon drink to prevent a catastrophe?

## 题面翻译

某个国家周围有 $n$ 个湖泊，每个湖泊最初都充满了水。目前，该地区预计将有大量降雨。如果降雨落在干燥的空湖上，则会将湖填满水，如果降雨落在已经充满水的湖上，则会发生水灾。

幸运的是，市民们拥有一条龙，龙每天可以喝掉一个湖中的所有水，但龙只能在不下雨的时候喝水，下雨时则不能。现在已经知道了未来 $m$ 天的降雨情况，问龙应该以怎样的顺序喝水才能避免水灾的发生。

## 输入格式

该题为多组输入，第一行为数据组数 $T$。

接下来对于每组数据：

第一行为两个数 $n,m$，含义见题面。

第二行共 $n$ 个数 $a_1,a_2...a_i$，表示在第 $i$ 天时第 $a_i$ 个湖上空会降水。若 $a_i=0$ 则表示第 $i$ 天不降水。

## 输出格式

对于每组数据：

若不能阻止洪水发生，则输出一行 ``NO``。

若可以则输出一行 ``YES``，随后在下一行按照龙喝水的顺序输出湖泊编号。

## 输入输出样例

### 输入 #1

```
4
2 4
0 0 1 1
2 4
0 1 0 2
2 3
0 1 2
2 4
0 0 0 1
```

### 输出 #1

```
NO
YES
1 2
NO
YES
0 1 0
```

