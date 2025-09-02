---
title: "CORNET - Corporative Network"
layout: "post"
diff: 普及+/提高
pid: SP264
tag: ['并查集', '递归']
---

# CORNET - Corporative Network

## 题目描述

原本有 $n$ 个节点，最初每个节点的父亲都是自己。

现在给你若干操作，共分为两种，操作格式如下：

1. `I x y`（大写字母`I`）

将 $x$ 的父亲变为 $y$，而且令 $x$ 与 $y$ 之间的距离为 $\lvert x-y \rvert \bmod 1000$。

2. `E x` 询问x点到其根节点的距离

数据保证对于所有的 $1$ 操作合法，即保证之前 $y$ 不是 $x$ 的父亲、

## 输入格式

第一行输入一个整数 $T$，表示每个数据点的数据组数。


第一行包含一个正整数 $n$，表示原有的节点个数


`I x y` 或`E x` 分别代表以上的两种操作

对于这些操作，以输入一个`O`（大写字母`O`）为终止。

## 输出格式

一共若干行，表示对于每一组测试数据中的 `E` 操作输出答案。

## 样例 #1

### 输入

```
1
4
E 3
I 3 1
E 3
I 1 2
E 3
I 2 4
E 3
O
```

### 输出

```
0
2
3
5
```



---

---
title: "BUGLIFE - A Bug&#8217;s Life"
layout: "post"
diff: 普及+/提高
pid: SP3377
tag: ['并查集', '拓扑排序', '二分图']
---

# BUGLIFE - A Bug&#8217;s Life

## 题目描述

Professor Hopper is researching the sexual behavior of a rare species of bugs. He assumes that they feature two different genders and that they only interact with bugs of the opposite gender. In his experiment, individual bugs and their interactions were easy to identify, because numbers were printed on their backs.  
  
 Given a list of bug interactions, decide whether the experiment supports his assumption of two genders with no homosexual bugs or if it contains some bug interactions that falsify it.

## 输入格式

The first line of the input contains the number of scenarios. Each scenario starts with one line giving the number of bugs (at least one, and up to 2000) and the number of interactions (up to 1000000) separated by a single space. In the following lines, each interaction is given in the form of two distinct bug numbers separated by a single space. Bugs are numbered consecutively starting from one.

## 输出格式

The output for every scenario is a line containing “Scenario #i:”, where i is the number of the scenario starting at 1, followed by one line saying either “No suspicious bugs found!” if the experiment is consistent with his assumption about the bugs’ sexual behavior, or “Suspicious bugs found!” if Professor Hopper’s assumption is definitely wrong.

## 样例 #1

### 输入

```
2

3 3

1 2

2 3

1 3

4 2

1 2

3 4
```

### 输出

```
Scenario #1:

Suspicious bugs found!

Scenario #2:

No suspicious bugs found!
```



---

