---
title: "Vladik and Courtesy"
layout: "post"
diff: 普及-
pid: CF811A
tag: []
---

# Vladik and Courtesy

## 题目描述

在一次正规的比赛后Vladik和Valera分别赢得了$a$ 个糖果和$b$  个糖果。Vladik将$1$ 个他的糖果给Valera。然后Valera将$2$ 个的糖果给Vladik，所以没有人认为他不是那么慷慨大方。接下来Vladik因为同样的原因将$3$ 个糖果给Valera。

更确切的说，每个人给对方比上一次自己收到的更多一个糖果

这种情况直到他们其中有人给不出足够的糖果为止。他们从对方那里得到的糖果不被认为是自己的。你需要直到谁是给不出糖果的人。

## 输入格式

输入仅一行包含两个用空格分开的整数$a,b$  （$1\leq a,b\leq10^9$  ）— 分别为Vladik和Valera的糖果数

## 输出格式

输出一行"Vladik"，如果是Vladik首先给不出糖果，同理或者是"Valera"。

（译者注：强烈建议好好看看说明中的样例解释的图）

Translated by Khassar

## 样例 #1

### 输入

```
1 1

```

### 输出

```
Valera

```

## 样例 #2

### 输入

```
7 6

```

### 输出

```
Vladik

```

