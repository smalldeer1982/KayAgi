---
title: "Jamie and To-do List"
layout: "post"
diff: 省选/NOI-
pid: CF916D
tag: ['线段树', '可持久化线段树', '可持久化']
---

# Jamie and To-do List

## 题目描述

“为什么我要完成这么多作业？”

Jamie 正忙于他的学校生活。

他开始忘记他必须做的作业。他决定把这些事情写在 To-Do List 上。

他为他的每项任务分配一个价值优先级(较低的价值意味着更重要)，这样他就可以决定他需要花更多的时间在哪个任务上。

几天后，Jamie 发现名单太大了，他甚至不能自己管理名单！由于您是 Jamie 的好朋友，请帮助他编写一个程序来支持待办事项列表中的以下操作:

`set ai xi`：设置任务 $a_i$ 的优先级为 $x_i$，如果该列表中没有出现则加入该任务。

`remove a_i`：删除该任务。

`query a_i`：求优先级比 $a_i$ 小的任务个数，如果没有则输出 $-1$。

`undo sum`：删除此次操作之前的 $sum$ 次操作。

在 Day 0，To-Do List 为空，在接下来 $Q$ 个日子内，Jamie 都会在四个操作中任选一个执行。

对于每个询问操作，输出对应的答案。

## 输入格式

第一行是一个整数 $Q$。

接下来的 $Q$ 行为任一个操作，第 $i$ 为第 $i$ 天的操作。

**保证最后一行是询问操作。**

## 输出格式

对于所有的查询操作，输出对应的答案。

## 说明/提示

保证输入的字符串由小写字符构成，设其长度为 $len$，则 $1\leq len\leq15$。

$1\le Q\le10^5$，并且保证对于所有的 undo 操作，$sum$ 不超过该天之前的天数。

## 样例 #1

### 输入

```
8
set chemlabreport 1
set physicsexercise 2
set chinesemockexam 3
query physicsexercise
query chinesemockexam
remove physicsexercise
query physicsexercise
query chinesemockexam

```

### 输出

```
1
2
-1
1

```

## 样例 #2

### 输入

```
8
set physicsexercise 2
set chinesemockexam 3
set physicsexercise 1
query physicsexercise
query chinesemockexam
undo 4
query physicsexercise
query chinesemockexam

```

### 输出

```
0
1
0
-1

```

## 样例 #3

### 输入

```
5
query economicsessay
remove economicsessay
query economicsessay
undo 2
query economicsessay

```

### 输出

```
-1
-1
-1

```

## 样例 #4

### 输入

```
5
set economicsessay 1
remove economicsessay
undo 1
undo 1
query economicsessay

```

### 输出

```
-1

```

