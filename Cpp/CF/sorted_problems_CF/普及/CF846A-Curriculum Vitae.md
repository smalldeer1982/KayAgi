---
title: "Curriculum Vitae"
layout: "post"
diff: 普及/提高-
pid: CF846A
tag: []
---

# Curriculum Vitae

## 题目描述

Hideo Kojima has just quit his job at Konami. Now he is going to find a new place to work. Despite being such a well-known person, he still needs a CV to apply for a job.

During all his career Hideo has produced $ n $ games. Some of them were successful, some were not. Hideo wants to remove several of them (possibly zero) from his CV to make a better impression on employers. As a result there should be no unsuccessful game which comes right after successful one in his CV.

More formally, you are given an array $ s_{1},s_{2},...,s_{n} $ of zeros and ones. Zero corresponds to an unsuccessful game, one — to a successful one. Games are given in order they were produced, and Hideo can't swap these values. He should remove some elements from this array in such a way that no zero comes right after one.

Besides that, Hideo still wants to mention as much games in his CV as possible. Help this genius of a man determine the maximum number of games he can leave in his CV.

## 输入格式

The first line contains one integer number $ n $ ( $ 1<=n<=100 $ ).

The second line contains $ n $ space-separated integer numbers $ s_{1},s_{2},...,s_{n} $ ( $ 0<=s_{i}<=1 $ ). $ 0 $ corresponds to an unsuccessful game, $ 1 $ — to a successful one.

## 输出格式

Print one integer — the maximum number of games Hideo can leave in his CV so that no unsuccessful game comes after a successful one.

## 样例 #1

### 输入

```
4
1 1 0 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
6
0 1 0 0 1 0

```

### 输出

```
4

```

## 样例 #3

### 输入

```
1
0

```

### 输出

```
1

```

