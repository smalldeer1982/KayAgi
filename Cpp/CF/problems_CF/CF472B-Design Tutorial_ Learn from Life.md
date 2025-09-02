---
title: "Design Tutorial: Learn from Life"
layout: "post"
diff: 普及/提高-
pid: CF472B
tag: []
---

# Design Tutorial: Learn from Life

## 题目描述

One way to create a task is to learn from life. You can choose some experience in real life, formalize it and then you will get a new task.

Let's think about a scene in real life: there are lots of people waiting in front of the elevator, each person wants to go to a certain floor. We can formalize it in the following way. We have $ n $ people standing on the first floor, the $ i $ -th person wants to go to the $ f_{i} $ -th floor. Unfortunately, there is only one elevator and its capacity equal to $ k $ (that is at most $ k $ people can use it simultaneously). Initially the elevator is located on the first floor. The elevator needs $ |a-b| $ seconds to move from the $ a $ -th floor to the $ b $ -th floor (we don't count the time the people need to get on and off the elevator).

What is the minimal number of seconds that is needed to transport all the people to the corresponding floors and then return the elevator to the first floor?

## 输入格式

One way to create a task is to learn from life. You can choose some experience in real life, formalize it and then you will get a new task.

Let's think about a scene in real life: there are lots of people waiting in front of the elevator, each person wants to go to a certain floor. We can formalize it in the following way. We have $ n $ people standing on the first floor, the $ i $ -th person wants to go to the $ f_{i} $ -th floor. Unfortunately, there is only one elevator and its capacity equal to $ k $ (that is at most $ k $ people can use it simultaneously). Initially the elevator is located on the first floor. The elevator needs $ |a-b| $ seconds to move from the $ a $ -th floor to the $ b $ -th floor (we don't count the time the people need to get on and off the elevator).

What is the minimal number of seconds that is needed to transport all the people to the corresponding floors and then return the elevator to the first floor?

## 输出格式

Output a single integer — the minimal time needed to achieve the goal.

## 说明/提示

In first sample, an optimal solution is:

1. The elevator takes up person #1 and person #2.
2. It goes to the 2nd floor.
3. Both people go out of the elevator.
4. The elevator goes back to the 1st floor.
5. Then the elevator takes up person #3.
6. And it goes to the 2nd floor.
7. It picks up person #2.
8. Then it goes to the 3rd floor.
9. Person #2 goes out.
10. Then it goes to the 4th floor, where person #3 goes out.
11. The elevator goes back to the 1st floor.

## 样例 #1

### 输入

```
3 2
2 3 4

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4 2
50 100 50 100

```

### 输出

```
296

```

## 样例 #3

### 输入

```
10 3
2 2 2 2 2 2 2 2 2 2

```

### 输出

```
8

```

