---
title: "Forbidden Value"
layout: "post"
diff: 省选/NOI-
pid: CF1455G
tag: []
---

# Forbidden Value

## 题目描述

### 题意简述
已知初始值$x=0$，给定下面2种命令：
1. `set` $y$ $v$，令$x=y$，或花费$v$元钱删除该命令；
2. `if` $y$ ... `end`，如果$x==y$，执行`if...end`中的命令，否则跳过该`if...end`。

你需要使用最少的花费，使得无论运行到哪里，都有$x \neq s$。

## 输入格式

第一行：两个整数$n$，$s$；
接下来$n$行：给定即将运行的代码，每行格式见下：
1. `set` $y$ $v$
2. `if` $y$
3. end

保证每个`end`都与一个`if`对应。

## 输出格式

输出使使得无论运行到哪里，都有$x \neq s$的最小花费。

Translated by [Cym10x](/user/354015).

## 样例 #1

### 输入

```
5 1
set 1 10
set 2 15
if 2
set 1 7
end
```

### 输出

```
17
```

## 样例 #2

### 输入

```
7 2
set 3 4
if 3
set 10 4
set 2 7
set 10 1
end
set 4 2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
9 200
if 0
set 5 5
if 5
set 100 13
end
if 100
set 200 1
end
end
```

### 输出

```
1
```

## 样例 #4

### 输入

```
1 10
set 1 15
```

### 输出

```
0
```

