---
title: "TRIBE2 - Tribe Council"
layout: "post"
diff: 难度0
pid: SP3390
tag: []
---

# TRIBE2 - Tribe Council

## 题目描述

有一个部族有N个人，这里有一个他们的家族树，1是根节点表示父亲和儿子的关系。节点1是树根。他们要在神圣的山的西边进行一个奇特的会议，就坐在一排桌子旁边，如下图。每个人都尽可能的往前面的桌子坐，如果那个桌子上当前没有他的儿子或者父亲。
现在让你确定一个他们就坐的顺序，使得他们占的桌子数最多

## 输入格式

第一行是人数N


以下N-1行每行两个整数x,y，表示x是y的父亲

## 输出格式

一个数，即能占有的最多桌子数

样例

Input
5

1 4

3 2

1 3

3 5

Output

3

## 说明/提示

1< N≤100 000

30%的数据N≤1000

每张桌子有无限的容量



Hint

样例可以以这种顺序入座 2 4 1 5 3

2 到桌1

4 到桌1

1 有孩子 (4) 在桌1, 所以去桌2

5 到桌1

3 有2个孩子在桌1 (2 and 5) 而且有父亲 (1)在桌2,所以去桌3.

## 样例 #1

### 输入

```
5
1 4
3 2
1 3
3 5
```

### 输出

```
3


Explanation: 
If men arrive in the order 2 4 1 5 3, the following happens:
2 goes to the first table4 goes to the first table1 has a son (4) at the first table, so he goes to the second table5 goes to the first table3 has two sons at the first table (2 and 5) and his father (1) is at
the second table, so he goes to the third table
```

