---
title: "GOSSIPER - Gossipers"
layout: "post"
diff: 普及/提高-
pid: SP2139
tag: []
---

# GOSSIPER - Gossipers

## 题目描述

Doulnee Keltchow is a small town in the middle of nowhere; what makes it so famous is the number of gossipers who live there. Every morning, each gossiper finds out a new gossip, a gossip so unique that nobody else in the town knows it. The gossipers talk, gossip and exchange rumors all day long. What happens when two gossipers meet? Of course, they exchange all the gossips they have heard so far. Your task is to determine whether every gossiper will know all the gossips by the end of the day.

## 输入格式

The input file consists of multiple test cases separated by blank lines. On the first line of every test case there are two positive integers N (1<=N<=2100) and M (1<=M<=12000), where N is the number of gossipers and M is the number of meetings. On the next N lines there are the names of the gossipers. The name of each gossiper is a single word consisting of lower- and uppercase letters. The following M lines describe the meetings in the order they happened. Each meeting is described by two distinct names of the gossipers separated by a single space. The values M=N=0 indicate the end of the input file.

## 输出格式

The output file should contain for each test case one line containing a single word "YES" if every gossiper knows all the gossips, or "NO", otherwise.

## 说明/提示

$1≤a≤2100,1≤b≤12000$

## 样例 #1

### 输入

```
3 3
Alice
Bob
Cindy
Alice Bob
Bob Cindy
Cindy Alice

4 4
Kirk
Lucy
Mike
Nancy
Kirk Lucy
Lucy Mike
Mike Nancy
Nancy Lucy

0 0
```

### 输出

```
YES
NO
```

