---
title: "Conan and Agasa play a Card Game"
layout: "post"
diff: 普及/提高-
pid: CF914B
tag: []
---

# Conan and Agasa play a Card Game

## 题目描述

题目简要描述

有 $n$ 张卡牌，第 $i$ 张上写着 $a_i$。Conan 和 Agasa 轮流操作，Conan 先手。每回合中，玩家选择一张卡牌，然后移除它本身和所有点数严格小于它的卡牌。如果玩家需要操作时已经没有卡牌了，他就输了。

假设双方玩家决顶聪明，请判断谁会赢。

## 输入格式

第一行输入一个整数 $n(1\le n\le 10^5)$。

第二行输入 $n$ 个整数，表示 $a_1,a_2,\dots a_n(1\le a_i\le 10^5)$。

## 输出格式

输出赢家的名字(没有引号)

## 样例 #1

### 输入

```
3
4 5 7

```

### 输出

```
Conan

```

## 样例 #2

### 输入

```
2
1 1

```

### 输出

```
Agasa

```

