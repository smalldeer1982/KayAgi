---
title: "Collecting Beats is Fun"
layout: "post"
diff: 普及-
pid: CF373A
tag: []
---

# Collecting Beats is Fun

## 题目描述

Cucumber boy is fan of Kyubeat, a famous music game.

Kyubeat has $ 16 $ panels for playing arranged in $ 4×4 $ table. When a panel lights up, he has to press that panel.

Each panel has a timing to press (the preffered time when a player should press it), and Cucumber boy is able to press at most $ k $ panels in a time with his one hand. Cucumber boy is trying to press all panels in perfect timing, that is he wants to press each panel exactly in its preffered time. If he cannot press the panels with his two hands in perfect timing, his challenge to press all the panels in perfect timing will fail.

You are given one scene of Kyubeat's panel from the music Cucumber boy is trying. Tell him is he able to press all the panels in perfect timing.

## 输入格式

The first line contains a single integer $ k $ ( $ 1<=k<=5 $ ) — the number of panels Cucumber boy can press with his one hand.

Next 4 lines contain 4 characters each (digits from 1 to 9, or period) — table of panels. If a digit $ i $ was written on the panel, it means the boy has to press that panel in time $ i $ . If period was written on the panel, he doesn't have to press that panel.

## 输出格式

Output "YES" (without quotes), if he is able to press all the panels in perfect timing. If not, output "NO" (without quotes).

## 说明/提示

In the third sample boy cannot press all panels in perfect timing. He can press all the panels in timing in time 1, but he cannot press the panels in time 2 in timing with his two hands.

## 样例 #1

### 输入

```
1
.135
1247
3468
5789

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
5
..1.
1111
..1.
..1.

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
1
....
12.1
.2..
.2..

```

### 输出

```
NO

```

