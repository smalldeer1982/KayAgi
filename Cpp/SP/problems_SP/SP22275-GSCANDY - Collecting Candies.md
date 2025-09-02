---
title: "GSCANDY - Collecting Candies"
layout: "post"
diff: 难度0
pid: SP22275
tag: []
---

# GSCANDY - Collecting Candies

## 题目描述

Jonathan Irvin Gunawan is a very handsome living person. You have to admit it to live in this world.

To become more handsome, Jonathan the Handsome have to collect candies (no relation, indeed). In front of him, there are N candies with different level of sweetness. Jonathan will collect the candies one by one. Jonathan can collect any number of candies, but he must collect the candy in the increasing order of level of sweetness (no two candies will have the same level of sweetness).

Every candy has their own color, which will be represented by a single integer between 0 and 10 $ ^{9} $ inclusive.

If Jonathan collects the first candy, or a candy that has different color with the previous candy he take, he will get 1 point.

If Jonathan collects the candy that has the same color with the previous candy, he will get a combo. Combo-x means that he has collected x candies of the same color consecutively. In other words, if he collect a candy and get combo-(x-1) and he collect a candy with the same color again, he will get combo-(x). And then if he collects a candy with different color, the combo will vanish and back to combo- 1.

(Note : previous candy means the last candy he take)

Every time he get combo-x, he will get x points. Jonathan wants to count how many maximum total points he can get. You are a fan of Jonathan the Handsome have to help him.

## 输入格式

The first line consists of a single integer T, indicating the number of

## 输出格式

For every case, output a single integer consist of the maximum total points Jonathan can get.

## 样例 #1

### 输入

```
2
4 
1 1 2 1 
4 
1 2 3 1
```

### 输出

```
6
4
```

