---
title: "Greg's Workout"
layout: "post"
diff: 入门
pid: CF255A
tag: []
---

# Greg's Workout

## 题目描述

Greg is a beginner bodybuilder. Today the gym coach gave him the training plan. All it had was $ n $ integers $ a_{1},a_{2},...,a_{n} $ . These numbers mean that Greg needs to do exactly $ n $ exercises today. Besides, Greg should repeat the $ i $ -th in order exercise $ a_{i} $ times.

Greg now only does three types of exercises: "chest" exercises, "biceps" exercises and "back" exercises. Besides, his training is cyclic, that is, the first exercise he does is a "chest" one, the second one is "biceps", the third one is "back", the fourth one is "chest", the fifth one is "biceps", and so on to the $ n $ -th exercise.

Now Greg wonders, which muscle will get the most exercise during his training. We know that the exercise Greg repeats the maximum number of times, trains the corresponding muscle the most. Help Greg, determine which muscle will get the most training.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=20) $ . The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=25) $ — the number of times Greg repeats the exercises.

## 输出格式

Print word "chest" (without the quotes), if the chest gets the most exercise, "biceps" (without the quotes), if the biceps gets the most exercise and print "back" (without the quotes) if the back gets the most exercise.

It is guaranteed that the input is such that the answer to the problem is unambiguous.

## 说明/提示

In the first sample Greg does 2 chest, 8 biceps and zero back exercises, so the biceps gets the most exercises.

In the second sample Greg does 5 chest, 1 biceps and 10 back exercises, so the back gets the most exercises.

In the third sample Greg does 18 chest, 12 biceps and 8 back exercises, so the chest gets the most exercise.

## 样例 #1

### 输入

```
2
2 8

```

### 输出

```
biceps

```

## 样例 #2

### 输入

```
3
5 1 10

```

### 输出

```
back

```

## 样例 #3

### 输入

```
7
3 3 2 7 9 6 8

```

### 输出

```
chest

```

