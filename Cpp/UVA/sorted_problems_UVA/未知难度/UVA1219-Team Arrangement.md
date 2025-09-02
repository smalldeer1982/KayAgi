---
title: "Team Arrangement"
layout: "post"
diff: 难度0
pid: UVA1219
tag: []
---

# Team Arrangement

## 题目描述

一支足球队有 $22$ 名球员，给出每名球员的号码、名字、场上位置以及为球队效力的时间段。

现在你要为一场比赛安排 $11$ 名首发球员。你会得到一个阵容，包含三个数，形如 `a-b-c`，表示场上必须要有 $a$ 个后卫，$b$ 个中场，$c$ 个前锋（当然还得有 $1$ 个门将，也就是说，$a + b + c = 10$，保证不会出现 `4-2-3-1` 一类的包含四个数的阵型）。对于每个位置的球员，你必须选择按号码从小到大选择球员。

此外，你还要在首发 $11$ 人中选出队长。队长必须是为球队效力时间最长的人。若有多个人效力时长相同，则队长为号码最大的人。

## 输入格式

多组数据，每组数据：

- 前 $22$ 行，每行代表一个人，包含号码、名字、位置和效力时间段（一人可能有多个时间段）。场上位置 `G` 是门将（Goalkeeper），`D` 是后卫（Defender），`M` 是中场（Midfielder）以及 `S` 是前锋（Striker）。

- 第 $23$ 行，输入为 `a-b-c` 格式，代表球队阵型。

输入以一行 $0$ 结尾。

## 输出格式

对于每组测试数据，输出 $11$ 行，代表选中的首发球员。

- 对于每个人，输出他的号码、名字和位置。

- 第一行是队长。

- 随后 $10$ 行按照 “G-D-M-S” 的顺序输出每个人的信息，每个位置的人按照号码升序排列。

如果无法所有球员无法组成 $11$ 人首发，输出 `IMPOSSIBLE TO ARRANGE`。

**每一组测试数据结束后要额外输出一行空行。**

translated by [Ray662](https://www.luogu.com.cn/user/502658).

## 样例 #1

### 输入

```
9 PlayerA M 2000-2001 2003-2006
2 PlayerB M 2004-2006
10 PlayerC D 2001-2005
1 PlayerD D 2000-2001 2002-2004
11 PlayerE S 2003-2006
8 PlayerF M 2005-2006
22 PlayerG S 2005-2006
25 PlayerH G 2000-2001 2002-2003 2005-2006
6 PlayerI D 2003-2006
26 PlayerJ D 2003-2004 2000-2001
18 PlayerK M 2003-2004
19 PlayerL M 2000-2001 2003-2006
7 PlayerM S 2003-2006 1999-2001
21 PlayerN S 2003-2006
13 PlayerO S 2005-2006
15 PlayerP G 2001-2006
14 PlayerQ D 2003-2004
5 PlayerR S 2000-2005
20 PlayerS G 2000-2002 2003-2003
12 PlayerT M 2004-2005
3 PlayerU D 2000-2005
4 PlayerV M 2001-2004
4-4-2
0
```

### 输出

```
7 PlayerM S
15 PlayerP G
1 PlayerD D
3 PlayerU D
6 PlayerI D
10 PlayerC D
2 PlayerB M
4 PlayerV M
8 PlayerF M
9 PlayerA M
5 PlayerR S
```

