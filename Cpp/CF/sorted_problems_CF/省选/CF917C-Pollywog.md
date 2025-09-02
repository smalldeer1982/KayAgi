---
title: "Pollywog"
layout: "post"
diff: 省选/NOI-
pid: CF917C
tag: []
---

# Pollywog

## 题目描述

As we all know, Dart is some kind of creature from Upside Down world. For simplicity, we call their kind pollywogs. Dart and $ x-1 $ other pollywogs are playing a game. There are $ n $ stones in a row, numbered from $ 1 $ through $ n $ from left to right. At most $ 1 $ pollywog may be sitting on each stone at a time. Initially, the pollywogs are sitting on the first $ x $ stones (one pollywog on each stone).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917C/a0a82f5f6337291f52388ae32f43260aec71496f.png)Dart and his friends want to end up on the last $ x $ stones. At each second, the leftmost pollywog should jump to the right. A pollywog can jump at most $ k $ stones; more specifically, a pollywog can jump from stone number $ i $ to stones $ i+1,i+2,...\ i+k $ . A pollywog can't jump on an occupied stone. Jumping a distance $ i $ takes $ c_{i} $ amounts of energy from the pollywog.

Also, $ q $ stones are special Each time landing on a special stone $ p $ , takes $ w_{p} $ amounts of energy (in addition to the energy for jump) from the pollywog. $ w_{p} $ could be negative, in this case, it means the pollywog absorbs $ |w_{p}| $ amounts of energy.

Pollywogs want to spend as little energy as possible (this value could be negative).

They're just pollywogs, so they asked for your help. Tell them the total change in their energy, in case they move optimally.

## 输入格式

The first line of input contains four integers, $ x,k,n $ and $ q $ ( $ 1<=x<=k<=8 $ , $ k<=n<=10^{8} $ , $ 0<=q<=min(25,n-x) $ ) — the number of pollywogs, the maximum length of jump, the number of stones and the number of special stones.

The next line contains $ k $ integers, $ c_{1},c_{2},...\ c_{k} $ , separated by spaces ( $ 1<=c_{i}<=10^{9} $ ) — the energetic costs of jumps.

The next $ q $ lines contain description of the special stones. Each line contains two integers $ p $ and $ w_{p} $ ( $ x+1<=p<=n $ , $ |w_{p}|<=10^{9} $ ). All $ p $ are distinct.

## 输出格式

Print the minimum amount of energy they need, in the first and only line of output.

## 样例 #1

### 输入

```
2 3 10 2
1 2 3
5 -10
6 1000

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 7 85 3
17 5 28 4 52 46 6
59 -76
33 -69
19 2018

```

### 输出

```
135

```

