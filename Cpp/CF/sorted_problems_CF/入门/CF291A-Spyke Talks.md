---
title: "Spyke Talks"
layout: "post"
diff: 入门
pid: CF291A
tag: []
---

# Spyke Talks

## 题目描述

Polycarpus is the director of a large corporation. There are $ n $ secretaries working for the corporation, each of them corresponds via the famous Spyke VoIP system during the day. We know that when two people call each other via Spyke, the Spyke network assigns a unique ID to this call, a positive integer session number.

One day Polycarpus wondered which secretaries are talking via the Spyke and which are not. For each secretary, he wrote out either the session number of his call or a 0 if this secretary wasn't talking via Spyke at that moment.

Help Polycarpus analyze these data and find out the number of pairs of secretaries that are talking. If Polycarpus has made a mistake in the data and the described situation could not have taken place, say so.

Note that the secretaries can correspond via Spyke not only with each other, but also with the people from other places. Also, Spyke conferences aren't permitted — that is, one call connects exactly two people.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{3}) $ — the number of secretaries in Polycarpus's corporation. The next line contains $ n $ space-separated integers: $ id_{1},id_{2},...,id_{n} $ $ (0<=id_{i}<=10^{9}) $ . Number $ id_{i} $ equals the number of the call session of the $ i $ -th secretary, if the secretary is talking via Spyke, or zero otherwise.

Consider the secretaries indexed from 1 to $ n $ in some way.

## 输出格式

Print a single integer — the number of pairs of chatting secretaries, or -1 if Polycarpus's got a mistake in his records and the described situation could not have taken place.

## 说明/提示

In the first test sample there are two Spyke calls between secretaries: secretary 2 and secretary 4, secretary 3 and secretary 5.

In the second test sample the described situation is impossible as conferences aren't allowed.

## 样例 #1

### 输入

```
6
0 1 7 1 7 10

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
1 1 1

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
1
0

```

### 输出

```
0

```

