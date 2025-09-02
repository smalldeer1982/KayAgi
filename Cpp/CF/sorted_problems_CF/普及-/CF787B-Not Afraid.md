---
title: "Not Afraid"
layout: "post"
diff: 普及-
pid: CF787B
tag: []
---

# Not Afraid

## 题目描述

Since the giant heads have appeared in the sky all humanity is in danger, so all Ricks and Mortys from all parallel universes are gathering in groups to find a solution to get rid of them.

There are $ n $ parallel universes participating in this event ( $ n $ Ricks and $ n $ Mortys). I. e. each of $ n $ universes has one Rick and one Morty. They're gathering in $ m $ groups. Each person can be in many groups and a group can contain an arbitrary number of members.

Ricks and Mortys have registered online in these groups. So, a person can have joined a group more than once (developer of this website hadn't considered this possibility).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787B/dcab08f4f41338897a1e46a0544bffe9ab994433.png)Summer from universe #1 knows that in each parallel universe (including hers) exactly one of Rick and Morty from that universe is a traitor and is loyal, but no one knows which one. She knows that we are doomed if there's a group such that every member in that group is a traitor (they will plan and destroy the world).

Summer knows that if there's a possibility that world ends (there's a group where all members are traitors) she should immediately cancel this event. So she wants to know if she should cancel the event. You have to tell her yes if and only if there's at least one scenario (among all $ 2^{n} $ possible scenarios, $ 2 $ possible scenarios for who a traitor in each universe) such that in that scenario the world will end.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{4} $ ) — number of universes and number of groups respectively.

The next $ m $ lines contain the information about the groups. $ i $ -th of them first contains an integer $ k $ (number of times someone joined $ i $ -th group, $ k&gt;0 $ ) followed by $ k $ integers $ v_{i,1},v_{i,2},...,v_{i,k} $ . If $ v_{i,j} $ is negative, it means that Rick from universe number $ -v_{i,j} $ has joined this group and otherwise it means that Morty from universe number $ v_{i,j} $ has joined it.

Sum of $ k $ for all groups does not exceed $ 10^{4} $ .

## 输出格式

In a single line print the answer to Summer's question. Print "YES" if she should cancel the event and "NO" otherwise.

## 说明/提示

In the first sample testcase, $ 1 $ st group only contains the Rick from universe number $ 3 $ , so in case he's a traitor, then all members of this group are traitors and so Summer should cancel the event.

## 样例 #1

### 输入

```
4 2
1 -3
4 -2 3 2 -3

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
5 2
5 3 -2 1 -1 5
3 -5 2 5

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
7 2
3 -1 6 7
7 -5 4 2 4 7 -3 4

```

### 输出

```
YES

```

