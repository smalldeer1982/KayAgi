---
title: "Alex and broken contest"
layout: "post"
diff: 入门
pid: CF877A
tag: []
---

# Alex and broken contest

## 题目描述

One day Alex was creating a contest about his friends, but accidentally deleted it. Fortunately, all the problems were saved, but now he needs to find them among other problems.

But there are too many problems, to do it manually. Alex asks you to write a program, which will determine if a problem is from this contest by its name.

It is known, that problem is from this contest if and only if its name contains one of Alex's friends' name exactly once. His friends' names are "Danil", "Olya", "Slava", "Ann" and "Nikita".

Names are case sensitive.

## 输入格式

The only line contains string from lowercase and uppercase letters and "\_" symbols of length, not more than $ 100 $ — the name of the problem.

## 输出格式

Print "YES", if problem is from this contest, and "NO" otherwise.

## 样例 #1

### 输入

```
Alex_and_broken_contest

```

### 输出

```
NO
```

## 样例 #2

### 输入

```
NikitaAndString

```

### 输出

```
YES
```

## 样例 #3

### 输入

```
Danil_and_Olya

```

### 输出

```
NO
```

