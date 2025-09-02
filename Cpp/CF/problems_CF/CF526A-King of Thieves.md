---
title: "King of Thieves"
layout: "post"
diff: 普及/提高-
pid: CF526A
tag: []
---

# King of Thieves

## 题目描述

In this problem you will meet the simplified model of game King of Thieves.

In a new ZeptoLab game called "King of Thieves" your aim is to reach a chest with gold by controlling your character, avoiding traps and obstacles on your way.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526A/527857f6180736c7bf1bfc93b9cfb6aa3a26550b.png)An interesting feature of the game is that you can design your own levels that will be available to other players. Let's consider the following simple design of a level.

A dungeon consists of $ n $ segments located at a same vertical level, each segment is either a platform that character can stand on, or a pit with a trap that makes player lose if he falls into it. All segments have the same length, platforms on the scheme of the level are represented as '\*' and pits are represented as '.'.

One of things that affects speedrun characteristics of the level is a possibility to perform a series of consecutive jumps of the same length. More formally, when the character is on the platform number $ i_{1} $ , he can make a sequence of jumps through the platforms $ i_{1}&lt;i_{2}&lt;...&lt;i_{k} $ , if $ i_{2}-i_{1}=i_{3}-i_{2}=...=i_{k}-i_{k-1} $ . Of course, all segments $ i_{1},i_{2},...\ i_{k} $ should be exactly the platforms, not pits.

Let's call a level to be good if you can perform a sequence of four jumps of the same length or in the other words there must be a sequence $ i_{1},i_{2},...,i_{5} $ , consisting of five platforms so that the intervals between consecutive platforms are of the same length. Given the scheme of the level, check if it is good.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the number of segments on the level.

Next line contains the scheme of the level represented as a string of $ n $ characters '\*' and '.'.

## 输出格式

If the level is good, print the word "yes" (without the quotes), otherwise print the word "no" (without the quotes).

## 说明/提示

In the first sample test you may perform a sequence of jumps through platforms $ 2,5,8,11,14 $ .

## 样例 #1

### 输入

```
16
.**.*..*.***.**.

```

### 输出

```
yes
```

## 样例 #2

### 输入

```
11
.*.*...*.*.

```

### 输出

```
no
```

