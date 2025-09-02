---
title: "HISIX - Hi6"
layout: "post"
diff: 难度0
pid: SP7563
tag: []
---

# HISIX - Hi6

## 题目描述

“我在某个地方读到，这个星球上的每个人都只有另外六个人分开。

## 输入格式

第一行包含一个整数T，它指定测试用例的数量。然后，将遵循T测试用例描述。每个测试用例将以一行正整数开始，N表示连接的数目。下一个N行将包含以下模式：

<name_1> <name_2> <D>

这意味着该人“<name_1>”通过进行D连接与此人“<name_2>”连接，反之亦然。请注意，通过使用其他连接，两个人可以通过较低的分离程度相互了解。

## 输出格式

对于每个输入用例，您必须打印字符串“case#i：”，其中我是测试用例编号，从1开始，然后是指定人员之间的最大分离程度。如果有人无法连接到另一个人，打印“无限”代替。

## 样例 #1

### 输入

```
\n
3\n2\njohn judy 1\nmary peter 1\n3\njohn judy 7\njohn peter 2\njudy peter 2\n7\njohn judy 3\nkatie peter 4\njohn peter 2\njudy mary 1\npeter mary 2\njohn katie 1\nkatie mary 1\n\n\n
```

### 输出

```
\n
```

