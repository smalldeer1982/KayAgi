---
title: "Quest"
layout: "post"
diff: 提高+/省选-
pid: CF542F
tag: []
---

# Quest

## 题目描述

Polycarp is making a quest for his friends. He has already made $ n $ tasks, for each task the boy evaluated how interesting it is as an integer $ q_{i} $ , and the time $ t_{i} $ in minutes needed to complete the task.

An interesting feature of his quest is: each participant should get the task that is best suited for him, depending on his preferences. The task is chosen based on an interactive quiz that consists of some questions. The player should answer these questions with "yes" or "no". Depending on the answer to the question, the participant either moves to another question or goes to one of the tasks that are in the quest. In other words, the quest is a binary tree, its nodes contain questions and its leaves contain tasks.

We know that answering any of the questions that are asked before getting a task takes exactly one minute from the quest player. Polycarp knows that his friends are busy people and they can't participate in the quest for more than $ T $ minutes. Polycarp wants to choose some of the $ n $ tasks he made, invent the corresponding set of questions for them and use them to form an interactive quiz as a binary tree so that no matter how the player answers quiz questions, he spends at most $ T $ minutes on completing the whole quest (that is, answering all the questions and completing the task). Specifically, the quest can contain zero questions and go straight to the task. Each task can only be used once (i.e., the people who give different answers to questions should get different tasks).

Polycarp wants the total "interest" value of the tasks involved in the quest to be as large as possible. Help him determine the maximum possible total interest value of the task considering that the quest should be completed in $ T $ minutes at any variant of answering questions.

## 输入格式

The first line contains two integers $ n $ and $ T $ ( $ 1<=n<=1000 $ , $ 1<=T<=100 $ ) — the number of tasks made by Polycarp and the maximum time a quest player should fit into.

Next $ n $ lines contain two integers $ t_{i},q_{i} $ ( $ 1<=t_{i}<=T $ , $ 1<=q_{i}<=1000 $ ) each — the time in minutes needed to complete the $ i $ -th task and its interest value.

## 输出格式

Print a single integer — the maximum possible total interest value of all the tasks in the quest.

## 说明/提示

In the first sample test all the five tasks can be complemented with four questions and joined into one quest.

In the second sample test it is impossible to use all the five tasks, but you can take two of them, the most interesting ones.

In the third sample test the optimal strategy is to include only the second task into the quest.

Here is the picture that illustrates the answers to the sample tests. The blue circles represent the questions, the two arrows that go from every circle represent where a person goes depending on his answer to that question. The tasks are the red ovals.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542F/36ecc7c1e696b10017232771921b21126dc31b0b.png)

## 样例 #1

### 输入

```
5 5
1 1
1 1
2 2
3 3
4 4

```

### 输出

```
11

```

## 样例 #2

### 输入

```
5 5
4 1
4 2
4 3
4 4
4 5

```

### 输出

```
9

```

## 样例 #3

### 输入

```
2 2
1 1
2 10

```

### 输出

```
10

```

