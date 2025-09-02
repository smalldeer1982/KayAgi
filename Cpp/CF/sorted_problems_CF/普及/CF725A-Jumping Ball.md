---
title: "Jumping Ball"
layout: "post"
diff: 普及/提高-
pid: CF725A
tag: []
---

# Jumping Ball

## 题目描述

In a new version of the famous Pinball game, one of the most important parts of the game field is a sequence of $ n $ bumpers. The bumpers are numbered with integers from $ 1 $ to $ n $ from left to right. There are two types of bumpers. They are denoted by the characters '<' and '>'. When the ball hits the bumper at position $ i $ it goes one position to the right (to the position $ i+1 $ ) if the type of this bumper is '>', or one position to the left (to $ i-1 $ ) if the type of the bumper at position $ i $ is '<'. If there is no such position, in other words if $ i-1&lt;1 $ or $ i+1&gt;n $ , the ball falls from the game field.

Depending on the ball's starting position, the ball may eventually fall from the game field or it may stay there forever. You are given a string representing the bumpers' types. Calculate the number of positions such that the ball will eventually fall from the game field if it starts at that position.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the length of the sequence of bumpers. The second line contains the string, which consists of the characters '<' and '>'. The character at the $ i $ -th position of this string corresponds to the type of the $ i $ -th bumper.

## 输出格式

Print one integer — the number of positions in the sequence such that the ball will eventually fall from the game field if it starts at that position.

## 说明/提示

In the first sample, the ball will fall from the field if starts at position $ 1 $ or position $ 2 $ .

In the second sample, any starting position will result in the ball falling from the field.

## 样例 #1

### 输入

```
4
<<><

```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
>>>>>
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4
>><<

```

### 输出

```
0
```

