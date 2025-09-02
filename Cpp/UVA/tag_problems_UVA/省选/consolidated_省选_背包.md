---
title: "团队分组 Team them up!"
layout: "post"
diff: 省选/NOI-
pid: UVA1627
tag: ['背包 DP', '二分图']
---

# 团队分组 Team them up!

## 题目描述

你的任务是按照以下要求将一些人员划分到两个队伍中。

1. 每个人都属于其中的一个队伍。

2. 每个队伍至少包含一个人。

3. 每个人都认识几个人，而同一个队伍中的人必须两两认识。

4. 两个队伍的人数尽可能的接近。

这个任务可能有多组解或无解，你只需要输出其中的任意一种或者宣布无解。

## 输入格式

第一行一个整数 t 表示共有 t 组测试数据

接下来 t 组数据，对于每组数据

第一行一个整数 n 表示一共有 n 个人且每个人的编号分别为1-n。

对于接下来 n 行，输入若干个整数，以输入'0'结束，第 i 行表示编号为 i 的人认识的人。

## 输出格式

对于每组数据以一个空行为间隔。

如果无解则输出'No solution'(不包括引号)。否则输出两行，分别表示两个队伍中的人员编号(编号之间以空格隔开)。你可以以任意的顺序输出方案。



---

---
title: "Jury Compromise"
layout: "post"
diff: 省选/NOI-
pid: UVA323
tag: ['枚举', '背包 DP', '状态合并']
---

# Jury Compromise

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=259

[PDF](https://uva.onlinejudge.org/external/3/p323.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/c7b6c683e8d99d641e6ceda5403d2046b1543157.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/549f8f7966cff47368b778a0f8cc36bf7e06dada.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/3a147f526328df86970adad2cdf916382d1282db.png)

## 样例 #1

### 输入

```
4 2
1 2
2 3
4 1
6 2
0 0

```

### 输出

```
Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3

```



---

