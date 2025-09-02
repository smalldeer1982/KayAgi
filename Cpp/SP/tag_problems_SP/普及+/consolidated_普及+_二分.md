---
title: "SUMFOUR - 4 values whose sum is 0"
layout: "post"
diff: 普及+/提高
pid: SP1296
tag: ['搜索', '二分', '枚举']
---

# SUMFOUR - 4 values whose sum is 0

## 题目描述

The SUM problem can be formulated as follows: given four lists A, B, C, D of integer values, compute how many quadruplet (a, b, c, d ) belongs to A x B x C x D are such that a + b + c + d = 0 . In the following, we assume that all lists have the same size n

## 输入格式

 The first line of the input file contains the size of the lists n (this value can be as large as 4000). We then have n lines containing four integer values (with absolute value as large as 2 $ ^{28} $ ) that belong respectively to A, B, C and D .

(**Edited:** n <= 2500)

## 输出格式

Output should be printed on a single line.

## 样例 #1

### 输入

```
6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45
```

### 输出

```
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

