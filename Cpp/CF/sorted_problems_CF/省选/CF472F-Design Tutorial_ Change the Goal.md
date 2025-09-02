---
title: "Design Tutorial: Change the Goal"
layout: "post"
diff: 省选/NOI-
pid: CF472F
tag: []
---

# Design Tutorial: Change the Goal

## 题目描述

There are some tasks which have the following structure: you are given a model, and you can do some operations, you should use these operations to achive the goal. One way to create a new task is to use the same model and same operations, but change the goal.

Let's have a try. I have created the following task for Topcoder SRM 557 Div1-Hard: you are given $ n $ integers $ x_{1},x_{2},...,x_{n} $ . You are allowed to perform the assignments (as many as you want) of the following form $ x_{i} $ ^= $ x_{j} $ (in the original task $ i $ and $ j $ must be different, but in this task we allow $ i $ to equal $ j $ ). The goal is to maximize the sum of all $ x_{i} $ .

Now we just change the goal. You are also given $ n $ integers $ y_{1},y_{2},...,y_{n} $ . You should make $ x_{1},x_{2},...,x_{n} $ exactly equal to $ y_{1},y_{2},...,y_{n} $ . In other words, for each $ i $ number $ x_{i} $ should be equal to $ y_{i} $ .

## 输入格式

There are some tasks which have the following structure: you are given a model, and you can do some operations, you should use these operations to achive the goal. One way to create a new task is to use the same model and same operations, but change the goal.

Let's have a try. I have created the following task for Topcoder SRM 557 Div1-Hard: you are given $ n $ integers $ x_{1},x_{2},...,x_{n} $ . You are allowed to perform the assignments (as many as you want) of the following form $ x_{i} $ ^= $ x_{j} $ (in the original task $ i $ and $ j $ must be different, but in this task we allow $ i $ to equal $ j $ ). The goal is to maximize the sum of all $ x_{i} $ .

Now we just change the goal. You are also given $ n $ integers $ y_{1},y_{2},...,y_{n} $ . You should make $ x_{1},x_{2},...,x_{n} $ exactly equal to $ y_{1},y_{2},...,y_{n} $ . In other words, for each $ i $ number $ x_{i} $ should be equal to $ y_{i} $ .

## 输出格式

There are some tasks which have the following structure: you are given a model, and you can do some operations, you should use these operations to achive the goal. One way to create a new task is to use the same model and same operations, but change the goal.

Let's have a try. I have created the following task for Topcoder SRM 557 Div1-Hard: you are given $ n $ integers $ x_{1},x_{2},...,x_{n} $ . You are allowed to perform the assignments (as many as you want) of the following form $ x_{i} $ ^= $ x_{j} $ (in the original task $ i $ and $ j $ must be different, but in this task we allow $ i $ to equal $ j $ ). The goal is to maximize the sum of all $ x_{i} $ .

Now we just change the goal. You are also given $ n $ integers $ y_{1},y_{2},...,y_{n} $ . You should make $ x_{1},x_{2},...,x_{n} $ exactly equal to $ y_{1},y_{2},...,y_{n} $ . In other words, for each $ i $ number $ x_{i} $ should be equal to $ y_{i} $ .

## 说明/提示

Assignment $ a $ ^= $ b $ denotes assignment $ a $ = $ a $ ^ $ b $ , where operation "^" is bitwise XOR of two integers.

## 样例 #1

### 输入

```
2
3 5
6 0

```

### 输出

```
2
1 2
2 2

```

## 样例 #2

### 输入

```
5
0 0 0 0 0
1 2 3 4 5

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
3
4 5 6
1 2 3

```

### 输出

```
5
3 1
1 2
2 2
2 3
3 1

```

## 样例 #4

### 输入

```
3
1 2 3
4 5 6

```

### 输出

```
-1

```

