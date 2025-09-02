---
title: "Football"
layout: "post"
diff: 入门
pid: CF96A
tag: ['模拟', '字符串']
---

# Football

## 题目描述

Petya loves football very much. One day, as he was watching a football match, he was writing the players' current positions on a piece of paper. To simplify the situation he depicted it as a string consisting of zeroes and ones. A zero corresponds to players of one team; a one corresponds to players of another team. If there are at least $ 7 $ players of some team standing one after another, then the situation is considered dangerous. For example, the situation $ 00100110111111101 $ is dangerous and $ 11110111011101 $ is not. You are given the current situation. Determine whether it is dangerous or not.

## 输入格式

The first input line contains a non-empty string consisting of characters "0" and "1", which represents players. The length of the string does not exceed $ 100 $ characters. There's at least one player from each team present on the field.

## 输出格式

Print "YES" if the situation is dangerous. Otherwise, print "NO".

## 样例 #1

### 输入

```
001001

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
1000000001

```

### 输出

```
YES

```

