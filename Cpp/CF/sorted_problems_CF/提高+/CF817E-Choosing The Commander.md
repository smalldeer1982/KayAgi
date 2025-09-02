---
title: "Choosing The Commander"
layout: "post"
diff: 提高+/省选-
pid: CF817E
tag: []
---

# Choosing The Commander

## 题目描述

As you might remember from the previous round, Vova is currently playing a strategic game known as Rage of Empires.

Vova managed to build a large army, but forgot about the main person in the army - the commander. So he tries to hire a commander, and he wants to choose the person who will be respected by warriors.

Each warrior is represented by his personality — an integer number $ p_{i} $ . Each commander has two characteristics — his personality $ p_{j} $ and leadership $ l_{j} $ (both are integer numbers). Warrior $ i $ respects commander $ j $ only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817E/b16f95ca4b565c33ddcd184eb553a25fa59f1c3f.png) (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) is the bitwise excluding OR of $ x $ and $ y $ ).

Initially Vova's army is empty. There are three different types of events that can happen with the army:

- $ 1 p_{i} $ — one warrior with personality $ p_{i} $ joins Vova's army;
- $ 2 p_{i} $ — one warrior with personality $ p_{i} $ leaves Vova's army;
- $ 3 p_{i} l_{i} $ — Vova tries to hire a commander with personality $ p_{i} $ and leadership $ l_{i} $ .

For each event of the third type Vova wants to know how many warriors (counting only those who joined the army and haven't left yet) respect the commander he tries to hire.

## 输入格式

The first line contains one integer $ q $ ( $ 1<=q<=100000 $ ) — the number of events.

Then $ q $ lines follow. Each line describes the event:

- $ 1 p_{i} $ ( $ 1<=p_{i}<=10^{8} $ ) — one warrior with personality $ p_{i} $ joins Vova's army;
- $ 2 p_{i} $ ( $ 1<=p_{i}<=10^{8} $ ) — one warrior with personality $ p_{i} $ leaves Vova's army (it is guaranteed that there is at least one such warrior in Vova's army by this moment);
- $ 3 p_{i} l_{i} $ ( $ 1<=p_{i},l_{i}<=10^{8} $ ) — Vova tries to hire a commander with personality $ p_{i} $ and leadership $ l_{i} $ . There is at least one event of this type.

## 输出格式

For each event of the third type print one integer — the number of warriors who respect the commander Vova tries to hire in the event.

## 说明/提示

In the example the army consists of two warriors with personalities $ 3 $ and $ 4 $ after first two events. Then Vova tries to hire a commander with personality $ 6 $ and leadership $ 3 $ , and only one warrior respects him (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817E/81a0cabf14dad3e87bbace6c754e37623e351c09.png), and $ 2&lt;3 $ , but ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817E/9023c8bab139f08429005ae47d2d497f5795be9b.png), and $ 5>=3 $ ). Then warrior with personality $ 4 $ leaves, and when Vova tries to hire that commander again, there are no warriors who respect him.

## 样例 #1

### 输入

```
5
1 3
1 4
3 6 3
2 4
3 6 3

```

### 输出

```
1
0

```

