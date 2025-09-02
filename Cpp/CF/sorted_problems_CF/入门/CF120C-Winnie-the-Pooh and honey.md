---
title: "Winnie-the-Pooh and honey"
layout: "post"
diff: 入门
pid: CF120C
tag: []
---

# Winnie-the-Pooh and honey

## 题目描述

As we all know, Winnie-the-Pooh just adores honey. Ones he and the Piglet found out that the Rabbit has recently gotten hold of an impressive amount of this sweet and healthy snack. As you may guess, Winnie and the Piglet asked to come at the Rabbit's place. Thus, there are $ n $ jars of honey lined up in front of Winnie-the-Pooh, jar number $ i $ contains $ a_{i} $ kilos of honey. Winnie-the-Pooh eats the honey like that: each time he chooses a jar containing most honey. If the jar has less that $ k $ kilos of honey or if Winnie-the-Pooh has already eaten from it three times, he gives the jar to Piglet. Otherwise he eats exactly $ k $ kilos of honey from the jar and puts it back. Winnie does so until he gives all jars to the Piglet. Count how much honey Piglet will overall get after Winnie satisfies his hunger.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100,1<=k<=100 $ ). The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ , separated by spaces ( $ 1<=a_{i}<=100 $ ).

## 输出格式

Print a single number — how many kilos of honey gets Piglet.

## 样例 #1

### 输入

```
3 3
15 8 10

```

### 输出

```
9

```

