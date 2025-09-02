---
title: "Robot's Task"
layout: "post"
diff: 普及-
pid: CF583B
tag: []
---

# Robot's Task

## 题目描述

Robot Doc is located in the hall, with $ n $ computers stand in a line, numbered from left to right from $ 1 $ to $ n $ . Each computer contains exactly one piece of information, each of which Doc wants to get eventually. The computers are equipped with a security system, so to crack the $ i $ -th of them, the robot needs to collect at least $ a_{i} $ any pieces of information from the other computers. Doc can hack the computer only if he is right next to it.

The robot is assembled using modern technologies and can move along the line of computers in either of the two possible directions, but the change of direction requires a large amount of resources from Doc. Tell the minimum number of changes of direction, which the robot will have to make to collect all $ n $ parts of information if initially it is next to computer with number $ 1 $ .

It is guaranteed that there exists at least one sequence of the robot's actions, which leads to the collection of all information. Initially Doc doesn't have any pieces of information.

## 输入格式

The first line contains number $ n $ ( $ 1<=n<=1000 $ ). The second line contains $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}&lt;n $ ), separated by a space. It is guaranteed that there exists a way for robot to collect all pieces of the information.

## 输出格式

Print a single number — the minimum number of changes in direction that the robot will have to make in order to collect all $ n $ parts of information.

## 说明/提示

In the first sample you can assemble all the pieces of information in the optimal manner by assembling first the piece of information in the first computer, then in the third one, then change direction and move to the second one, and then, having 2 pieces of information, collect the last piece.

In the second sample to collect all the pieces of information in the optimal manner, Doc can go to the fourth computer and get the piece of information, then go to the fifth computer with one piece and get another one, then go to the second computer in the same manner, then to the third one and finally, to the first one. Changes of direction will take place before moving from the fifth to the second computer, then from the second to the third computer, then from the third to the first computer.

In the third sample the optimal order of collecting parts from computers can look like that: 1->3->4->6->2->5->7.

## 样例 #1

### 输入

```
3
0 2 0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
4 2 3 0 1

```

### 输出

```
3

```

## 样例 #3

### 输入

```
7
0 3 1 0 5 2 6

```

### 输出

```
2

```

