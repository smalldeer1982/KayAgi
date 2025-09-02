---
title: "Island of Logic"
layout: "post"
diff: 难度0
pid: UVA592
tag: []
---

# Island of Logic

## 题目描述

在逻辑之岛上，有3种居民，而且岛上的所有居民都互相认识：

神明：他们永远都说真话

恶灵：他们永远都说假话

人类：他们白天说真话，晚上说假话

一个社会科学家来到了岛上，因为他不知道那些居民是那些，所以他要你来给他做一个测谎仪，来让他知道那些是真话，那些是假话，还有说这些话的人是那种人

## 输入格式

输入当中有多组数据，每组数据都是下面的格式，当输入是0时，输入结束

每组数据的第一行都有一个整数n，然后接下来n行，每行都是这些格式中的一种：

X: I am [not] (divine|evil|human|lying)

X说：我是（不是）神明|恶灵|人类|在撒谎

X is [not] (divine|evil|human|lying)

X说：X是（不是）神明|恶灵|人类|在撒谎

It is (day|night)

X说：现在是白天|晚上

其中，X代表A，B，C，D，E五个人当中的一个

## 输出格式

输出包括多行，第一行输出 conversation #（现在是第几组数据），然后接下来的每一行输出你得出的信息，信息可以是一下的任意一种：

This is impossible

这种话不可能出现

No facts are deductible

无法判断

X is divine|evil|human

X 是 神明|恶灵|人类

It is day|night

现在是白天|晚上

## 样例 #1

### 输入

```
1
A: I am divine.
1
A: I am lying.
1
A: I am evil.
3
A: B is human.
B: A is evil.
A: B is evil.
0
```

### 输出

```
Conversation #1
No facts are deducible.
Conversation #2
This is impossible.
Conversation #3
A is human.
It is night.
Conversation #4
A is evil.
B is divine.
```

