---
title: "TEMPLEQ - Temple Queues"
layout: "post"
diff: 难度0
pid: SP8406
tag: []
---

# TEMPLEQ - Temple Queues

## 题目描述

![main-destinations-tirupati](http://farm6.static.flickr.com/5056/5472021008_bcb05d7fb5.jpg) 蒂鲁马拉寺是世界上最繁忙的宗教场所，每天都有大量朝圣者前来。为了管理好庞大的参拜者队伍，寺庙负责人需要全天候监控排队系统。今天是一个好日子，他已经开始工作了。在寺庙入口处，一共有 $N$ 条队伍，有些队伍中已经排满了朝圣者。每个队伍的入口都有一个金属门通向寺庙。门每次打开时，只允许一名朝圣者进入，随后它会立即关闭。

随着越来越多的朝圣者加入队伍，负责人需要时刻掌握每个队伍的情况，决定哪些门该打开。无论什么时候，他想知道当前有多少个队伍至少有 $X$ 名朝圣者。同时，他还会设定一个整数 $Y$，并决定打开所有至少有 $Y$ 名朝圣者的队伍的门，使得每个这样的队伍中一名朝圣者进入寺庙。你，就是这个排队系统的控制员，需要按照他的指令行事。迅速完成任务，你就能获得他的奖励——一块大大的拉杜（甜点）。

## 输入格式

第一行包含两个整数 $N$ 和 $Q$，分别表示队伍的数量（$1 \le N \le 100,000$）和查询的数量（$0 \le Q \le 500,000$）。第二行包含 $N$ 个整数，分别表示各队伍的初始人数。第 $i$ 个整数表示第 $i$ 个队伍的初始人数（$0 \le \text{初始人数} \le 100,000,000$）。

接下来的 $Q$ 行是以下三种类型之一的命令：

1. `1 A`：表示有一名朝圣者加入第 $A$ 个队伍（$1 \le A \le N$）。
2. `2 X`：表示查询当前有多少个队伍至少有 $X$ 名朝圣者（$0 \le X \le 1,000,000,000$）。
3. `3 Y`：表示打开所有至少有 $Y$ 名朝圣者的队伍的门，从而允许每个这样的队伍中一名朝圣者进入寺庙（$1 \le Y \le 1,000,000,000$）。

## 输出格式

对于每条类型为 `2 X` 的查询，输出结果，以下一行展示。

## 说明/提示

- $1 \le N \le 100,000$
- $0 \le Q \le 500,000$
- $0 \le \text{初始人数} \le 100,000,000$
- $1 \le A \le N$
- $0 \le X \le 1,000,000,000$
- $1 \le Y \le 1,000,000,000$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n5 6\n20 30 10 50 40\n2 31\n1 2\n2 31\n3 11\n2 20\n2 50\n\n
```

### 输出

```
\n2\n3\n3\n0\n\nNote : Ideal time limit should be 2s. It has been increased to 7s, to let Java solutions pass, as the i/o is huge.\n\n* There are multiple test sets, and the judge shows the sum of the time taken over all test sets of your submission, if Accepted.
```

