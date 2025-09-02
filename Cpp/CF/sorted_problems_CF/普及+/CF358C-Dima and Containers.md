---
title: "Dima and Containers"
layout: "post"
diff: 普及+/提高
pid: CF358C
tag: []
---

# Dima and Containers

## 题目描述

# Dima和容器


Dima 的生日快到了！这是个重要的日子！Saryozha 送给 Dima的礼物是，他会离开房间，不打扰 Dima 和 Inna 庆祝生日。Inna 送给 Dima 的礼物是一个堆栈（stack）、一个队列（queue）和一个双端队列（deck）。

Inna 希望她的礼物能向 Dima 展示他是多么优秀的程序员。为此，她会逐个给 Dima 发送命令。有两种类型的命令：

1. 将给定的数字添加到其中一个容器中。对于队列和堆栈，你只能将元素添加到末尾。对于双端队列，你可以将元素添加到开头或末尾。
2. 从至多三个不同的容器中提取一个数字。将所有提取出的数字告诉 Inna，然后清空所有容器。对于队列容器，你只能从开头提取数字。对于堆栈容器，你只能从末尾提取数字。对于双端队列容器，你可以从开头或末尾提取数字。你不能从空容器中提取数字。

每次 Dima 执行第二类型的命令时，Inna 就会亲吻 Dima 若干次（可能为零）。Dima 非常了解 Inna，他确定这个数字等于他在此操作中从容器中提取的数字之和。

正如我们之前说的，Dima 非常了解 Inna，他知道 Inna 将给他什么命令以及命令的顺序。帮助 Dima 找到让他在生日上获得尽可能多亲吻的策略！

## 输入格式

第一行包含整数 $n\ (1\le n\le10^5) $ — Inna 的命令数量。然后是 $n$ 行，描述 Inna 的命令。每行包含一个整数：

1. 整数 $a\ (1\le a\le10^5)$ 表示 Inna 命令 Dima 将数字 $a$ 添加到其中一个容器中。
2. 整数 $0$ 表示 Inna 要求 Dima 从不同的容器中最多提取三个数字。

## 输出格式

输出的每个命令必须对应输出的一行 — Dima 的动作。

对于第一类型的命令（添加），打印一个与 Dima 的选择相对应的单词：

- pushStack — 添加到堆栈的末尾；
- pushQueue — 添加到队列的末尾；
- pushFront — 添加到双端队列的开头；
- pushBack — 添加到双端队列的末尾。

对于第二类型的命令，首先打印一个整数 $k  (0\le k\le3) $，表示提取操作的数量，然后打印 $k$ 个以空格分隔的单词。这些单词可以是：

- popStack — 从堆栈的末尾提取；
- popQueue — 从队列的开头提取；
- popFront — 从双端队列的开头提取；
- popBack — 从双端队列的末尾提取。

所打印的操作不能从空容器中提取数字。同时，它们必须从不同的容器中提取数字。

打印的行为序列必须导致亲吻次数最多。如果有多个行为序列导致亲吻次数最多，你可以打印任何一个。

## 样例 #1

### 样例输入 #1

```
10
0
1
0
1
2
0
1
2
3
0
```

### 样例输出 #1

```
0
pushStack
1 popStack
pushStack
pushQueue
2 popStack popQueue
pushStack
pushQueue
pushFront
3 popStack popQueue popFront
```

## 样例 #2

### 样例输入 #2

```
4
1
2
3
0
```

### 样例输出 #2

```
pushStack
pushQueue
pushFront
3 popStack popQueue popFront
```

by zhangsenhao6728

## 样例 #1

### 输入

```
10
0
1
0
1
2
0
1
2
3
0

```

### 输出

```
0
pushStack
1 popStack
pushStack
pushQueue
2 popStack popQueue
pushStack
pushQueue
pushFront
3 popStack popQueue popFront

```

## 样例 #2

### 输入

```
4
1
2
3
0

```

### 输出

```
pushStack
pushQueue
pushFront
3 popStack popQueue popFront

```

