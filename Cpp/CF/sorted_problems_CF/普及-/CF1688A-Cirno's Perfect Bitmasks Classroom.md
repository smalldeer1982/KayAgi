---
title: "Cirno's Perfect Bitmasks Classroom"
layout: "post"
diff: 普及-
pid: CF1688A
tag: ['位运算']
---

# Cirno's Perfect Bitmasks Classroom

## 题目描述

> 就算是很简单的问题，她一定也答不上来。——《东方求闻史纪》   

琪露诺的完美位运算教室开始了！    
琪露诺给了她的学生一个正整数 $x$，作为作业题，她的学生需要找到一个满足以下两个条件的，最小的正整数 $y$。
- $x \operatorname{and} y>0$     
- $x \operatorname{xor} y>0$ 

这里的 $\operatorname{and}$ 和 $\operatorname{xor}$ 都是位运算。      
她的学生米斯蒂娅对这个问题束手无策，请你来帮帮她。

## 输入格式

第一行输入一个正整数 $t(1 \leq t \leq 10^3)$，表示输入数据组数。    
对于每一组数据，输入一个正整数 $x$。

## 输出格式

对于每一组数据，输出符合题目要求的 $y$。

## 样例 #1

### 输入

```
7
1
2
5
9
16
114514
1000000
```

### 输出

```
3
3
1
1
17
2
64
```

