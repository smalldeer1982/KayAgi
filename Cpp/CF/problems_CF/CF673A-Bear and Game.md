---
title: "Bear and Game"
layout: "post"
diff: 普及-
pid: CF673A
tag: []
---

# Bear and Game

## 题目描述

Bear Limak likes watching sports on TV. He is going to watch a game today. The game lasts $ 90 $ minutes and there are no breaks.

Each minute can be either interesting or boring. If $ 15 $ consecutive minutes are boring then Limak immediately turns TV off.

You know that there will be $ n $ interesting minutes $ t_{1},t_{2},...,t_{n} $ . Your task is to calculate for how many minutes Limak will watch the game.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1<=n<=90 $ ) — the number of interesting minutes.

The second line contains $ n $ integers $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{1}&lt;t_{2}&lt;...\ t_{n}<=90 $ ), given in the increasing order.

## 输出格式

Print the number of minutes Limak will watch the game.

## 说明/提示

In the first sample, minutes $ 21,22,...,35 $ are all boring and thus Limak will turn TV off immediately after the $ 35 $ -th minute. So, he would watch the game for $ 35 $ minutes.

In the second sample, the first $ 15 $ minutes are boring.

In the third sample, there are no consecutive $ 15 $ boring minutes. So, Limak will watch the whole game.

## 样例 #1

### 输入

```
3
7 20 88

```

### 输出

```
35

```

## 样例 #2

### 输入

```
9
16 20 30 40 50 60 70 80 90

```

### 输出

```
15

```

## 样例 #3

### 输入

```
9
15 20 30 40 50 60 70 80 90

```

### 输出

```
90

```

