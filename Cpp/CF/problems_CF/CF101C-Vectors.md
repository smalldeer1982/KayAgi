---
title: "Vectors"
layout: "post"
diff: 普及+/提高
pid: CF101C
tag: []
---

# Vectors

## 题目描述

At a geometry lesson Gerald was given a task: to get vector $ B $ out of vector $ A $ . Besides, the teacher permitted him to perform the following operations with vector $ А $ :

- Turn the vector by $ 90 $ degrees clockwise.
- Add to the vector a certain vector $ C $ .

Operations could be performed in any order any number of times.

Can Gerald cope with the task?

## 输入格式

The first line contains integers $ x_{1} $ и $ y_{1} $ — the coordinates of the vector $ A $ ( $ -10^{8}<=x_{1},y_{1}<=10^{8} $ ). The second and the third line contain in the similar manner vectors $ B $ and $ C $ (their coordinates are integers; their absolute value does not exceed $ 10^{8} $ ).

## 输出格式

Print "YES" (without the quotes) if it is possible to get vector $ B $ using the given operations. Otherwise print "NO" (without the quotes).

## 样例 #1

### 输入

```
0 0
1 1
0 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
0 0
1 1
1 1

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
0 0
1 1
2 2

```

### 输出

```
NO

```

