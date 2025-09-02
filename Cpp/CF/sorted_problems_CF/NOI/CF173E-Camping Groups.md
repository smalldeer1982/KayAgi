---
title: "Camping Groups"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF173E
tag: []
---

# Camping Groups

## 题目描述

A club wants to take its members camping. In order to organize the event better the club directors decided to partition the members into several groups.

Club member $ i $ has a responsibility value $ r_{i} $ and an age value $ a_{i} $ . A group is a non-empty subset of club members with one member known as group leader. A group leader should be one of the most responsible members of the group (his responsibility value is not less than responsibility of any other group member) and his age absolute difference with any other group member should not exceed $ k $ .

Some club members are friends and want to be in the same group. They also like their group to be as large as possible. Now you should write a program that answers a series of questions like "What's the largest size of a group containing club member $ x $ and club member $ y $ ?". It's possible for $ x $ or $ y $ to be the group leader.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2<=n<=10^{5},0<=k<=10^{9} $ ) — the number of club members and the age restriction for one group.

The next line contains integer numbers $ r_{1},r_{2},...,r_{n} $ ( $ 1<=r_{i}<=10^{9} $ ) separated by space: $ r_{i} $ denotes the $ i $ -th club member's responsibility. In the same way there are integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) in the third line: $ a_{i} $ denotes the $ i $ -th club member's age.

The next line contains an integer $ q $ denoting the number of questions that you should answer ( $ 1<=q<=10^{5} $ ). The next $ q $ lines describe the questions. Each line contains two space-separated integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=n,x_{i}≠y_{i} $ ) — the indices of the club members that should end up in the same group.

## 输出格式

For each question print the maximum size of the group in a line. If making such a group is impossible print -1 instead.

## 说明/提示

In the first query the largest group with members 3 and 5 is $ {1,3,4,5} $ where member 3 is the leader.

In the second query member 2 should be the leader so the group will be $ {1,2,3} $ .

In the third query the leader of the group should have age 3 so the only leader can be member 3, who is less responsible than member 2. So making a group is impossible.

The group for the fourth query is the same as first query.

## 样例 #1

### 输入

```
5 1
1 5 4 1 2
4 4 3 2 2
4
5 3
2 3
2 5
4 1

```

### 输出

```
4
3
-1
4

```

